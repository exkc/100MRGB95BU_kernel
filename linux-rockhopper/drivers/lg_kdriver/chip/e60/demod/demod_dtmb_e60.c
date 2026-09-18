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
#include "demod_common_e60.h"
#include "demod_dtmb_e60.h"

/***********************************************************************************
	Global Type Definitions
 ************************************************************************************/

static UINT16	gE60GBB_FullDTMBPkerrCount 		= 12;
static UINT16 	gE60GBB_FullDTMBPkerrThreshold 		= 255;
static UINT16	gE60GBB_DTMB_UnlockCount_full_packeterr	= 0;

/***********************************************************************************
	Static Variable & Function Prototypes Declarations
 ************************************************************************************/
int _DEMOD_E60_DTMB_CheckTuneMode (DEMOD_CTX_T *pDemodInfo)
{
	UINT8  new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_AUTO;

	switch (pDemodInfo->setCfgParam.dtmb.tuneMode)
	{
		case	LX_DEMOD_TUNE_NORMAL:			new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_NORMAL; break;
		case	LX_DEMOD_TUNE_AUTO: 			new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_AUTO; break;
		case	LX_DEMOD_TUNE_MANUAL:			new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_MANUAL; break;
		case	LX_DEMOD_TUNE_SPEC_DVBC_FIXED_DATA: 	new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_FIXED_DATA; break;
		default:					new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_AUTO; break;
	}

	return new_tuneMode;
}

int _DEMOD_E60_LGDBB_DTMB_SetDemod (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_L2_Context * 	pFrontend;

	UINT8  			standard = 		DEMOD_DD_MODE_PROP_MODULATION_DTMB;
	UINT32 			freq_Khz = 		0;
	UINT16 			dtmb_bandwidth_Khz = 	0;
	UINT8  			tuneMode = 		DEMOD_DD_MODE_PROP_TUNEMODE_AUTO;

	pFrontend = DEMOD_E60_GetContext();

	tuneMode = _DEMOD_E60_DTMB_CheckTuneMode(pDemodInfo);

	if(RET_OK != DEMOD_E60_Get_BW(pDemodInfo, &dtmb_bandwidth_Khz))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_BW() \n");
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

int _DEMOD_E60_LGDBB_DTMB_CheckSignalState (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	pFrontend = DEMOD_E60_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
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
	DEMOD_PRINT("[DEMOD_CHIP] Packet error : %d\n", signalStatus.packetError);

	pDemodInfo->signalStatus.packetError 	= signalStatus.packetError;
	pDemodInfo->signalStatus.ber			= signalStatus.ber;
	pDemodInfo->signalStatus.agc			= signalStatus.if_agc;
	pDemodInfo->signalStatus.m.mse			= signalStatus.mse_info;
	pDemodInfo->signalStatus.m.constPwr		= signalStatus.constPwr;
	pDemodInfo->freqOffset 					= signalStatus.offsetFrq_Hz / 1000;
	pDemodInfo->signalStatus.operMode 		= pDemodInfo->operMode;
	pDemodInfo->signalStatus.rfMode			= pDemodInfo->systemMode;
	pDemodInfo->signalStatus.cellID			= signalStatus.cell_id;

	return RET_OK;

}

#if 0
#endif

int DEMOD_E60_DTMB_SW_Init (void)
{
	LX_DEMOD_L2_Context *	pFrontend;

	DEMOD_NOTI("[DEMOD_CHIP] Start\n");

	pFrontend = DEMOD_E60_GetContext();

	if(lx_chip() == LX_CHIP_E60)
	{
		extern void DEMOD_RegisterMemMap(char* mode);
		DEMOD_RegisterMemMap("dtmb");
	}

//	if(DEMOD_L2_DTMB_SW_Init(pFrontend, 0x26) != NO_DEMOD_ERROR)   // CPBOX
	if(DEMOD_L2_DTMB_SW_Init(pFrontend, 0xb2) != NO_DEMOD_ERROR)     // SOC
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] Fail, DEMOD_E60_DTMB_SW_Init()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DTMB_Get_CarrierMode
 * Get the information of LP code rate on DVB-T2.
 *
 * @param *pLpCodeRate[OUT] LX_DEMOD_CARRIERMODE_T - carrier mode : signal , multi
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jinwoo.han (Jinwoo.han@lge.com)
*/
int DEMOD_E60_DTMB_Get_CarrierMode (LX_DEMOD_CARRIERMODE_T *pCarrierMode)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	pFrontend = DEMOD_E60_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
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

	DEMOD_PRINT("[DEMOD_CHIP] signalStatus.carr_mode : 0x%02x \n",signalStatus.carr_mode);
	return RET_OK;

}

int DEMOD_E60_DTMB_Get_Time_Interval (BOOLEAN *pbM720)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	pFrontend = DEMOD_E60_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		DEMOD_RETURN_FAIL(__F__);
	}

	*pbM720 = FALSE;

	DEMOD_PRINT("[DEMOD_CHIP] Time Interval : 0x%02x \n",signalStatus.il_mode);

	if(signalStatus.il_mode == DEMOD_DD_DTMB_STATUS_RESPONSE_IL_MODE_720) *pbM720 = TRUE;

	return RET_OK;

}

int DEMOD_E60_DTMB_Get_Pn_Mode (LX_DEMOD_PNMODE_T *pPnMode)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	pFrontend = DEMOD_E60_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		DEMOD_RETURN_FAIL(__F__);
	}

	*pPnMode = LX_DEMOD_TPS_GUARD_UNKNOWN;

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

int DEMOD_E60_DTMB_Get_CodeRate (LX_DEMOD_CODERATE_T *pCodeRate)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	pFrontend = DEMOD_E60_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		DEMOD_RETURN_FAIL(__F__);
	}

	*pCodeRate = LX_DEMOD_CODE_UNKNOWN;

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

int DEMOD_E60_DTMB_Get_Constellation (LX_DEMOD_RF_MODE_T *pConstellation)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	pFrontend = DEMOD_E60_GetContext();

	*pConstellation = LX_DEMOD_UNKOWN_MODE;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		DEMOD_RETURN_FAIL(__F__);
	}

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
 * DEMOD_E60_DTMB_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_E60_DTMB_Obtaining_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{

	static LX_DEMOD_FLAG_T 		scanProcessing 		= LX_DEMOD_FLAG_START;
	static LX_DEMOD_LOCK_STATE_T 	lockState 		= LX_DEMOD_UNLOCKED;
//	static unsigned int 		sigStablestartTime 	= 0;
	LX_DEMOD_OPER_MODE_T 		operMode 		= LX_DEMOD_UNKOWN_OPMODE;
	unsigned int 			elapsedTime		= 0;


	switch (pDemodInfo->controlState)
	{
						/***************************************************/
						/***** Configure tuner for desired channel No. *****/
		case LX_DEMOD_TUNE_START:	/***************************************************/
			{
				if(RET_OK != _DEMOD_E60_LGDBB_DTMB_SetDemod(pDemodInfo))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, _DEMOD_E60_LGDBB_DTMB_SetDemod() \n");
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_TUNE_NORMAL != pDemodInfo->setCfgParam.dtmb.tuneMode)
				{
					if(RET_OK != DEMOD_E60_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_ON, &scanProcessing, &lockState))
					{
						DEMOD_PRINT("[DEMOD_CHIP] FAIL, DEMOD_E60_NeverlockScan() \n");
						DEMOD_RETURN_FAIL(__F__);
					}
					pDemodInfo->controlState 		= LX_DEMOD_TUNE_SCAN;
					gE60GBB_FullDTMBPkerrThreshold 	= 255;
					gE60GBB_FullDTMBPkerrCount 		= 9;

					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_TUNE_START : Going to LX_DEMOD_TUNE_SCAN..... ^0^\n");
				}
				else
				{
					pDemodInfo->scanJobFlag 		= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState 		= LX_DEMOD_SYNC_CHECKING;
					gE60GBB_FullDTMBPkerrThreshold 	= 300;
					gE60GBB_FullDTMBPkerrCount 		= 9;

					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_TUNE_START : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
				}
				gE60GBB_DTMB_UnlockCount_full_packeterr = 0;
			}
			break;
						/***************************************************/
						/***** Configure demod for scan mode. *****/
		case LX_DEMOD_TUNE_SCAN:	/***************************************************/
			{
				if((LX_DEMOD_FLAG_COMPLETE == pDemodInfo->scanJobFlag) || (LX_DEMOD_FLAG_FINISH == pDemodInfo->scanJobFlag))
				{
					pDemodInfo->controlState 	= LX_DEMOD_SYNC_CHECKING;
					DEMOD_PRINT( "[DEMOD_CHIP] Error, Already Done \n");
					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
					return RET_OK;
				}

				if(RET_OK != DEMOD_E60_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_OFF, &scanProcessing, &lockState))
				{
					DEMOD_PRINT("[DEMOD_CHIP] FAIL, DEMOD_E60_NeverlockScan() \n");
					DEMOD_RETURN_FAIL(__F__);
				}

				if((LX_DEMOD_FLAG_FINISH == scanProcessing) && (LX_DEMOD_LOCKED == lockState))
				{
					pDemodInfo->operMode 		= LX_DEMOD_DTMB;
					pDemodInfo->scanJobFlag 	= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState 	= LX_DEMOD_SYNC_CHECKING;

					DEMOD_PRINT( "[DEMOD_CHIP] Signal is Found \n");
					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");

				}
				else if((LX_DEMOD_FLAG_FINISH == scanProcessing)&& (LX_DEMOD_UNLOCKED == lockState))
				{
					pDemodInfo->scanJobFlag 	= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->bNotifiedUnlock	= TRUE;
					pDemodInfo->bNotifiedLock	= FALSE;
					pDemodInfo->lockStatus		= LX_DEMOD_UNLOCKED;
					pDemodInfo->controlState 	= LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK;
					elapsedTime 				= jiffies_to_msecs(jiffies) - g_NewTuneReqeustTime;

					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] LX_DEMOD_TUNE_SCAN : MSG_DTMB_FRONT_END_NOT_LOCKED..\n") ;
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] LX_DEMOD_TUNE_SCAN : Elapse time is %d msec\n", elapsedTime) ;
					DEMOD_PRINT( "[DEMOD_CHIP] Signal is NOT Found\n");
				}
				else
				{
					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_ING;
//					DEMOD_PRINT( "[DEMOD_CHIP] Detection is on processing\n");
				}

			}
			break;
							/********************************************/
							/***** Attempting to finish the tuning state machine *****/
		case LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK : /********************************************/
			{

			}
			break;
						/********************************************/
						/***** Attempting to obtain synch lock *****/
		case LX_DEMOD_SYNC_CHECKING : 	/********************************************/
			{
				if(RET_OK != DEMOD_E60_Get_OperMode(&operMode))
				{
					DEMOD_PRINT("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_OperMode()\n");
					DEMOD_RETURN_FAIL(__F__);
				}
				DEMOD_PRINT("[DEMOD_CHIP] LX_DEMOD_SYNC_CHECKING() operMode = 0x%x\n", operMode);

				if(RET_OK != DEMOD_E60_Get_Lock(LX_DEMOD_CARR_LOCK, &lockState))
				{
					DEMOD_PRINT("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_Lock()\n");
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					pDemodInfo->controlState		= LX_DEMOD_SIGNAL_STABLE;
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
	   	case LX_DEMOD_SIGNAL_STABLE: 	/********************************************/
			{
				if(RET_OK != DEMOD_E60_Get_Lock(LX_DEMOD_FEC_LOCK, &lockState))
				{
					DEMOD_PRINT("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_Lock()\n");
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					pDemodInfo->lockStatus					= LX_DEMOD_LOCKED;
					pDemodInfo->signalStatus.bSignalValid 	= TRUE;
					pDemodInfo->controlState				= LX_DEMOD_SIGNAL_LOCKED;

					elapsedTime = jiffies_to_msecs(jiffies) - g_RetuneStartTime;

					DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : MSG_DTMB_FRONT_END_LOCKED..... ^^^0^^^\n");
					DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^^^0^^^\n", elapsedTime);

					if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
					{
						DEMOD_PRINT( "[DEMOD_CHIP] FAIL, DEMOD_Get_TunedCFG() \n");
						DEMOD_RETURN_FAIL(__F__);
					}

					if (RET_OK != _DEMOD_E60_LGDBB_DTMB_CheckSignalState(pDemodInfo))
					{
						DEMOD_PRINT( "[DEMOD_CHIP] FAIL, _DEMOD_E60_LGDBB_DTMB_CheckSignalState()\n");
						DEMOD_RETURN_FAIL(__F__);
					}

					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^^^0^^^\n", pDemodInfo->freqOffset);
					pDemodInfo->bNotifiedLock	= TRUE;
					pDemodInfo->bNotifiedUnlock	= FALSE;

				}
				else
				{
					pDemodInfo->controlState	= LX_DEMOD_SYNC_CHECKING;
					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : Going back to LX_DEMOD_SYNC_CHECKING.....\n");
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
 * DEMOD_E60_DTMB_Monitoring_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_E60_DTMB_Monitoring_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_LOCK_STATE_T lockState;

	if(RET_OK != DEMOD_E60_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
	{
		DEMOD_PRINT("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_Lock()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if(LX_DEMOD_LOCKED == lockState)
	{
		pDemodInfo->unLockCount 	= 0;
		pDemodInfo->unLockLongCount	= 0;

		if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
		{
			pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;
		}

		if (RET_OK != _DEMOD_E60_LGDBB_DTMB_CheckSignalState(pDemodInfo))
		{
			DEMOD_PRINT( "[DEMOD_CHIP] FAIL, _DEMOD_E60_LGDBB_DTMB_CheckSignalState()\n");
			DEMOD_RETURN_FAIL(__F__);
		}

		if(pDemodInfo->signalStatus.packetError >= gE60GBB_FullDTMBPkerrThreshold)
		{
			gE60GBB_DTMB_UnlockCount_full_packeterr++;
			DEMOD_PRINT( "[DEMOD_CHIP] gE60GBB_DTMB_UnlockCount_full_packeterr = %d \n",gE60GBB_DTMB_UnlockCount_full_packeterr);

			if(gE60GBB_DTMB_UnlockCount_full_packeterr == gE60GBB_FullDTMBPkerrCount)
			{
				DEMOD_PRINT( "[DEMOD_CHIP] Force to NOT LOCK by Packet Error Count \n");

				if(RET_OK != DEMOD_E60_SoftwareReset())
				{
					DEMOD_PRINT("[DEMOD_CHIP] FAIL, DEMOD_E60_SoftwareReset() \n");
					DEMOD_RETURN_FAIL(__F__);
				}
				DEMOD_PRINT("[DEMOD_CHIP] SUCCESS, DEMOD_E60_SoftwareReset()\n");

				pDemodInfo->lockStatus			= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedUnlock 		= TRUE;
				pDemodInfo->bNotifiedLock		= FALSE;
				pDemodInfo->signalStatus.bSignalValid 	= FALSE;
				gE60GBB_DTMB_UnlockCount_full_packeterr = 0;
				DEMOD_WARN( "[DEMOD_CHIP] MONITORING FUNC : MSG_DTMB_FRONT_END_NOT_LOCKED by Packeterror Count\n");
			}
		}
		else
		{
			gE60GBB_DTMB_UnlockCount_full_packeterr 	= 0;

			if(pDemodInfo->bIsTPoutEn == TRUE)
			{
				if (RET_OK != DEMOD_E60_TPOutEnable(TRUE))
				{
					DEMOD_PRINT( "[DEMOD_CHIP] FAIL, DEMOD_E60_TPOutEnable(TRUE)\n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
			if((LX_DEMOD_LOCKED != pDemodInfo->lockStatus)  && (TRUE != pDemodInfo->bNotifiedLock))
			{
				pDemodInfo->lockCount++;
			}

			if(pDemodInfo->lockCount == 2)
			{
				pDemodInfo->lockStatus 			= LX_DEMOD_LOCKED;
				pDemodInfo->bNotifiedLock 		= TRUE;
				pDemodInfo->bNotifiedUnlock 		= FALSE;
				pDemodInfo->signalStatus.bSignalValid 	= TRUE;
				pDemodInfo->lockCount 			= 0;

				DEMOD_NOTI( "[DEMOD_CHIP] MONITORING FUNC : MSG_DTMB_FRONT_END_LOCKED by lockCount\n");

				if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
				{
					pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;
				}
			}

			if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
			{
				DEMOD_PRINT( "[DEMOD_CHIP] FAIL, DEMOD_Get_TunedCFG() \n");
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
				pDemodInfo->lockStatus 			= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedLock 		= FALSE;
				pDemodInfo->bNotifiedUnlock 		= TRUE;
				pDemodInfo->signalStatus.bSignalValid 	= FALSE;
				gE60GBB_DTMB_UnlockCount_full_packeterr = 0;
				pDemodInfo->unLockCount 		= 0;

				DEMOD_WARN( "[DEMOD_CHIP] MONITORING FUNC : MSG_DTMB_FRONT_END_NOT_LOCKED by Unlock Count\n");
			}
		}

	}

	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DTMB_Set_Config_auto
 * Control automatic setting of DVB-T config.
 *
 * @param bAutoDetect 	[IN] BOOLEAN - automatic setting (TRUE) / manual setting(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DTMB_Set_Config_auto (BOOLEAN bAutoDetect)
{
	LX_DEMOD_L2_Context *	pFrontend;

	pFrontend = DEMOD_E60_GetContext();

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
 DEMOD_E60_DTMB_Set_PartialConfig
 * Set all config parameters on DVB-T.
 * This function is used when LX_DEMOD_E60_DVBT_Set_Config_auto is disabled.
 *
 * @param *pDvbtConfigParam 	[IN] LX_DEMOD_DVBT_CONFIG_T - DVB-T config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DTMB_Set_PartialConfig (LX_DEMOD_DTMB_CONFIG_T *pDtmbConfigParam)
{
	LX_DEMOD_L2_Context *	pFrontend;
	int retc = NO_DEMOD_ERROR;

	pFrontend = DEMOD_E60_GetContext();
#if 0
	retc = DEMOD_L2_DVB_Set_PLP_Select(pFrontend,  plp_id, DEMOD_DD_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_AUTO);
	if(retc != NO_DEMOD_ERROR)
	{
		DEMOD_PRINT ("DEMOD_L2_DVB_Set_PLP_Select error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return RET_ERROR;
	}
	pFrontend->current_PLP_ID = plp_id;

	if(DEMOD_L2_DVB_AutoModeDetectOn(pFrontend))
	{
		DEMOD_PRINT("(%s) FAIL, DEMOD_L2_DVB_AutoModeDetectOn \n", __F__);
		return RET_ERROR;;
	}
#endif

	return retc;

}

int DEMOD_E60_DTMB_Set_MemSconfig (void)
{
	LX_DEMOD_L2_Context *	pFrontend;
	UINT32 base_st_mem = gMemCfgDEMOD_DTMB.memory_base;

	pFrontend = DEMOD_E60_GetContext();

	if(base_st_mem == 0)
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] ERROR, E60 DEMOD DTMB Wrong Memory Base Address \n");
		return RET_ERROR;
	}
	else
	{
		DEMOD_PRINT("[DEMOD_CHIP] DEMOD_E60_DTMB_Set_MemSconfig Base_addr[0x%x] \n", base_st_mem );
		if(RET_OK != DEMOD_L2_DTMB_Set_BaseAddr_AXI(pFrontend, base_st_mem ))
		{
			DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_DTMB_Set_BaseAddr_AXI() \n");
			return RET_ERROR;
		}
	}

	return RET_OK;

}
#if 0
#endif
