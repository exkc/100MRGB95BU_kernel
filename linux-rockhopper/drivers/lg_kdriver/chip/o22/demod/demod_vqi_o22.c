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
#define DEMOD_TAG "[CHIP.VQI] "

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
#include "demod_util.h"

#include "demod_common_o22.h"
#include "demod_vqi_o22.h"

/***********************************************************************************
	Global Type Definitions
 ************************************************************************************/

#define _ATSC3_PLP_AUTO_DETECT  0xFF

extern UINT8 gLGDBB_PowerOnInit;

/***********************************************************************************
	Static Variable & Function Prototypes Declarations
 ************************************************************************************/
static UINT32 _PowerOnInitSTartTime = 0;

const static UINT8  _VSB_Unlock_Count_Threshold = 4;
const static UINT8  _QAM_Unlock_Count_Threshold = 4;
const static UINT8  _ATSC3_Unlock_Count_Threshold = 4;
const static UINT8 _ISDBT_Unlock_Count_Threshold = 2;

static UINT16 _VQI_Full_Pkerr_Count = 0;
const static UINT16 _VQI_Full_Pkerr_Count_Threshold = 7;

//const static UINT16 _VSB_Full_Pkerr_Threshold = 300;
//const static UINT16 _QAM_Full_Pkerr_Threshold = 300;
//const static UINT16 _ATSC3_Full_Pkerr_Threshold = 300;
const static UINT16 _ISDBT_Full_Pkerr_Threshold = 200;

/******************************************************************************
	Global Variables & Function Prototypes Declarations
******************************************************************************/
extern	int 	SYS_IO_ReadRegArray(UINT32 addr, UINT32 size, void *data);
extern	int 	SYS_IO_WriteRegArray(UINT32 addr, UINT32 size, const void *data);

extern void DEMOD_RegisterMemMap(char* mode);

int DEMOD_O22_ATSC_SW_Init (void)
{
	LX_DEMOD_L2_Context * 	pFrontend;

	DEMOD_PRINT("Start\n");

	pFrontend = DEMOD_O22_GetContext();

	DEMOD_RegisterMemMap("atsc3");

	g_demod_ctx_info[0].bSetParams   = FALSE;

	//if(DEMOD_L2_ATSC_SW_Init(pFrontend, 0x26) != NO_DEMOD_ERROR)  // CPBOX
	if(DEMOD_L2_ATSC_SW_Init(pFrontend, DEMOD_CHIP_ID) != NO_DEMOD_ERROR)    // SOC
	{
		DEMOD_ERROR("Fail, DEMOD_L2_ATSC_SW_Init()\n");
		return RET_ERROR;
	}

	return RET_OK;
}

int _DEMOD_O22_VSB_CheckSignalState (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	pFrontend = DEMOD_O22_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}

#if 0
	printk("[op_mode: %d]\n",		signalStatus.operatingMode);
	printk("[if_agc: %d]\n",		signalStatus.if_agc);
	printk("[mse_info: %d]\n",		signalStatus.mse_info_eq);
	printk("[snr: %d]\n",			signalStatus.snr_eq);
	printk("[dl: %d]\n",			signalStatus.demodLock);
	printk("[ber: %d]\n",			signalStatus.ber);
	printk("[pe: %d]\n",			signalStatus.packetError);
	printk("[afc_freq: %d]\n",		signalStatus.offsetFrq_Hz);
	printk("[constellation: %d]\n",		signalStatus.constellation);
	printk("[sp_inv: %d]\n",		signalStatus.spInv);
	printk("[constPwr: %d]\n",		signalStatus.constPwr);
	printk("[packet error : %d]\n",	signalStatus.packetError);
#endif

	pDemodInfo->signalStatus.packetError 	= signalStatus.packetError;
	pDemodInfo->signalStatus.ber		= signalStatus.ber;
	pDemodInfo->signalStatus.agc		= signalStatus.if_agc;
	pDemodInfo->signalStatus.m.mse		= signalStatus.mse_info_eq;
	pDemodInfo->signalStatus.m.constPwr	= signalStatus.constPwr;
	pDemodInfo->freqOffset 			= signalStatus.offsetFrq_Hz;

	pDemodInfo->signalStatus.operMode 	= pDemodInfo->operMode;
	pDemodInfo->signalStatus.rfMode		= pDemodInfo->systemMode;

	if (signalStatus.packetError > 0) {
		DEMOD_NOTI("packet error occured, agc %d, mse %u, pe %d\n", signalStatus.if_agc, signalStatus.mse_info_eq, signalStatus.packetError);
	}

	return RET_OK;
}


int _DEMOD_O22_VSB_CheckTuneMode (DEMOD_CTX_T *pDemodInfo)
{
	UINT8  new_tuneMode;

	switch (pDemodInfo->setCfgParam.vsb.tuneMode)
	{
		case LX_DEMOD_TUNE_NORMAL:		new_tuneMode = DEMOD_PROP_MODE_TUNE_NORMAL; break;
		case LX_DEMOD_TUNE_AUTO: 		new_tuneMode = DEMOD_PROP_MODE_TUNE_AUTO; break;
		case LX_DEMOD_TUNE_MANUAL: 		new_tuneMode = DEMOD_PROP_MODE_TUNE_MANUAL ; break;
//		case TU_TUNE_SPEC_DVBC_FIXED_DATA:	new_tuneMode = DEMOD_PROP_MODE_TUNE_FIXED_DATA; break;
		default:				new_tuneMode = DEMOD_PROP_MODE_TUNE_AUTO; break;
	}

	return new_tuneMode;
}



int DEMOD_O22_VSB_SetDemod (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_L2_Context *	pFrontend;

	UINT8			new_tuneMode;
	UINT32 			freq_Khz = 0;
	UINT16 			ter_bandwidth_KHz;

	pFrontend = DEMOD_O22_GetContext();

	new_tuneMode = _DEMOD_O22_VSB_CheckTuneMode(pDemodInfo);

	if(RET_OK != DEMOD_O22_Get_BW(pDemodInfo, &ter_bandwidth_KHz))
	{
		DEMOD_ERROR("Fail, DEMOD_O22_Get_BW()\n");
		return RET_ERROR;
	}

	DEMOD_L2_ATSC_Set_demod(pFrontend,
				DEMOD_MODULATION_VSB,
				freq_Khz,
				new_tuneMode,
				DEMOD_PROP_MODE_SPECINVAUTO_MANUAL,
				DEMOD_PROP_MODE_SPECINV_NORMAL,
				ter_bandwidth_KHz,
				0, 0, 0, 0
				);

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_VSB_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O22_VSB_Obtaining_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{

	static LX_DEMOD_FLAG_T 		scanProcessing = LX_DEMOD_FLAG_START;
	static LX_DEMOD_LOCK_STATE_T 	scanLock = LX_DEMOD_UNLOCKED;
	static unsigned int 		sigStablestartTime;

	switch (pDemodInfo->controlState)
	{
		/*********************************************************/
		/***** Configure demod for tune start.               *****/
		/*********************************************************/
		case LX_DEMOD_TUNE_START:
			{
				#if 0
				printk("\n/**********************************************************/\n");
				printk("check  setCfgParam.vsb.tuneMode[%d]\n", pDemodInfo->setCfgParam.vsb.tuneMode);
				printk("check  setCfgParam.vsb.channelBW[%d]\n", pDemodInfo->setCfgParam.vsb.channelBW );
				printk("check  setCfgParam.vsb.bSpectrumInv[%d]\n", pDemodInfo->setCfgParam.vsb.bSpectrumInv );
				printk("check  systemMode[%d]\n", pDemodInfo->systemMode );
				#endif

				if(RET_OK != DEMOD_O22_VSB_SetDemod(pDemodInfo))
				{
					DEMOD_ERROR("Fail, DEMOD_O22_VSB_SetDemod()\n");
					return RET_ERROR;
				}

				if(LX_DEMOD_TUNE_NORMAL != pDemodInfo->setCfgParam.vsb.tuneMode)
				{
					if(RET_OK != DEMOD_O22_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_ON, &scanProcessing, &scanLock))
					{
						DEMOD_ERROR("Fail, DEMOD_O22_NeverlockScan()\n");
						return RET_ERROR;
					}
					pDemodInfo->controlState = LX_DEMOD_TUNE_SCAN;
					DEMOD_PRINT("LX_DEMOD_TUNE_START : Going to LX_DEMOD_TUNE_SCAN..... ^0^\n");
				}
				else
				{
					if (RET_OK != DEMOD_O22_TPOutEnable(TRUE))
					{
						DEMOD_ERROR("Fail, DEMOD_O22_TPOutEnable()\n");
						return RET_ERROR;
					}

					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState = LX_DEMOD_SIGNAL_STABLE;
					DEMOD_PRINT("LX_DEMOD_TUNE_START : Going to LX_DEMOD_SIGNAL_STABLE for SYNC CHECK DIRECTLY... ^0^\n");
				}
			}
			break;

		/*********************************************************/
		/***** Configure demod for scan mode.                *****/
		/*********************************************************/
		case LX_DEMOD_TUNE_SCAN:
			{
				unsigned int currentTime = 0;
				unsigned int elapsedTime = 0;

				if((LX_DEMOD_FLAG_COMPLETE == pDemodInfo->scanJobFlag) || (LX_DEMOD_FLAG_FINISH == pDemodInfo->scanJobFlag))
				{
					pDemodInfo->controlState = LX_DEMOD_SIGNAL_STABLE;

					DEMOD_PRINT("Already Done\n");
					DEMOD_PRINT("LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
					return RET_OK;
				}

				if(RET_OK != DEMOD_O22_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_OFF, &scanProcessing, &scanLock))
				{
					DEMOD_ERROR("Fail, DEMOD_O22_NeverlockScan()\n");
					return RET_ERROR;
				}

				if((LX_DEMOD_FLAG_FINISH == scanProcessing) && (LX_DEMOD_LOCKED == scanLock))
				{
					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState = LX_DEMOD_SIGNAL_STABLE;

					DEMOD_PRINT("Signal is Found\n");
					DEMOD_NOTI("SCANNING FIRST LOCK! : Going to LX_DEMOD_SIGNAL_STABLE..... ^0^\n");
				}
				else if((LX_DEMOD_FLAG_FINISH == scanProcessing)&& (LX_DEMOD_UNLOCKED == scanLock))
				{
					pDemodInfo->scanJobFlag 	= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->bNotifiedUnlock	= TRUE;
					pDemodInfo->bNotifiedLock	= FALSE;
					pDemodInfo->lockStatus 		= LX_DEMOD_UNLOCKED;
					pDemodInfo->signalStatus.bSignalValid = FALSE;

					pDemodInfo->controlState 	= LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK;

					currentTime = jiffies_to_msecs(jiffies);
					elapsedTime = currentTime - g_RetuneStartTime;

					DEMOD_NOTI("LX_DEMOD_TUNE_SCAN : MSG_ATSC_FRONT_END_NOT_LOCKED..\n") ;
					DEMOD_NOTI("LX_DEMOD_TUNE_SCAN : Elapse time is %d msec\n", elapsedTime) ;

					DEMOD_PRINT("Signal is NOT Found\n");
				}
				else
				{
					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_ING;
//					DEMOD_PRINT("Detection is on processing\n");
				}
			}
			break;

		/*********************************************************/
		/***** Attempting to finish the tuning state machine *****/
		/*********************************************************/
		case LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK :
			{


			}
			break;

		/*********************************************************/
		/***** Attempting to obtain synch lock               *****/
		/*********************************************************/
		case LX_DEMOD_SYNC_CHECKING :
			{
				LX_DEMOD_LOCK_STATE_T			lockState;

				if(RET_OK != DEMOD_O22_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
				{
					DEMOD_ERROR("Fail, DEMOD_O22_Get_Lock()\n");
					return RET_ERROR;
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					pDemodInfo->controlState	= LX_DEMOD_SIGNAL_STABLE;
					sigStablestartTime = jiffies_to_msecs(jiffies);
					DEMOD_PRINT("LX_DEMOD_SYNC_CHECKING : Going to LX_DEMOD_SIGNAL_STABLE..... ^0^\n");
				}
				else
				{
					if(RET_OK != DEMOD_O22_Get_Lock(LX_DEMOD_CARR_LOCK, &lockState))
					{
						DEMOD_ERROR("Fail, DEMOD_O22_Get_Lock()\n");
						return RET_ERROR;
					}

					if(LX_DEMOD_LOCKED == lockState)
					{
						DEMOD_PRINT("LX_DEMOD_SYNC_CHECKING : catch only carrier lock..... ^0^\n");
						notifyinglockTimeOut = LX_DEMOD_LOCK_DEALY_2000 + LX_DEMOD_LOCK_DEALY_800;
						/* extending max delay */
					}
					else
					{
						/* nothing to do so far */
					}
				}
			}
		   break;

	   	/*********************************************************/
	   	/***** Attempting to obtain signal stability         *****/
		/*********************************************************/
	   	case LX_DEMOD_SIGNAL_STABLE:
			{
				LX_DEMOD_LOCK_STATE_T		lockState;
				SINT32				freqOffset=0;
				unsigned int 			elapsedTime;
				UINT32 				packetError;

				if(RET_OK != DEMOD_O22_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
				{
					DEMOD_ERROR("Fail, DEMOD_O22_Get_Lock()\n");
					return RET_ERROR;
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					if (LX_DEMOD_TUNE_NORMAL == pDemodInfo->setCfgParam.vsb.tuneMode)
					{
						elapsedTime = jiffies_to_msecs(jiffies) - sigStablestartTime;

						if(RET_OK != DEMOD_O22_Get_Packet_Error(&packetError))
						{
							DEMOD_ERROR("Fail, DEMOD_O22_Get_Packet_Error()\n");
							return RET_ERROR;
						}
						else
						{
							pDemodInfo->bNotifiedLock	= TRUE;
							pDemodInfo->bNotifiedUnlock	= FALSE;
							pDemodInfo->lockStatus		= LX_DEMOD_LOCKED;
							pDemodInfo->signalStatus.bSignalValid = TRUE;

							pDemodInfo->controlState	= LX_DEMOD_SIGNAL_LOCKED;

							elapsedTime = jiffies_to_msecs(jiffies) - g_RetuneStartTime;

							DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : MSG_ATSC_FRONT_END_LOCKED..... ^^^0^^^\n");
							DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^^^0^^^\n", elapsedTime);

							if (RET_OK != DEMOD_O22_TPOutEnable(TRUE))
							{
								DEMOD_ERROR("Fail, DEMOD_O22_TPOutEnable()\n");
								return RET_ERROR;
							}

							if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
							{
								DEMOD_ERROR("Fail, DEMOD_Get_TunedCFG()\n");
								return RET_ERROR;
							}

							if (RET_OK != _DEMOD_O22_VSB_CheckSignalState(pDemodInfo))
							{
								DEMOD_ERROR("Fail, _DEMOD_O22_VSB_CheckSignalState()\n");
								return RET_ERROR;
							}
						}
					}
					else
					{
						pDemodInfo->bNotifiedLock	= TRUE;
						pDemodInfo->bNotifiedUnlock = FALSE;
						pDemodInfo->lockStatus		= LX_DEMOD_LOCKED;
						pDemodInfo->signalStatus.bSignalValid = TRUE;

						if (RET_OK != DEMOD_O22_Get_CarrierFreqOffset(&freqOffset))
						{
							DEMOD_ERROR("Fail, DEMOD_O22_Get_CarrierFreqOffset()\n");
							return RET_ERROR;
						}
						pDemodInfo->freqOffset = freqOffset;

						pDemodInfo->controlState	= LX_DEMOD_SIGNAL_LOCKED;

						elapsedTime = jiffies_to_msecs(jiffies) - g_RetuneStartTime;

						DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : MSG_ATSC_FRONT_END_LOCKED..... ^0^\n");
						DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^0^\n", elapsedTime);
						DEMOD_PRINT("LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^0^\n", freqOffset);

						if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
						{
							DEMOD_ERROR("Fail, DEMOD_Get_TunedCFG()\n");
							return RET_ERROR;
						}
						if (RET_OK != _DEMOD_O22_VSB_CheckSignalState(pDemodInfo))
						{
							DEMOD_ERROR("Fail, _DEMOD_O22_VSB_CheckSignalState()\n");
							return RET_ERROR;
						}
					}
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
 * DEMOD_O22_VSB_Monitoring_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O22_VSB_Monitoring_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{

	LX_DEMOD_LOCK_STATE_T			lockState;

	if(RET_OK != DEMOD_O22_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
	{
		DEMOD_ERROR("Fail, DEMOD_O22_Get_Lock()\n");
		return RET_ERROR;
	}

#if 1
	if(RET_OK != DEMOD_O22_VSB_Monitor(pDemodInfo))
	{
		DEMOD_ERROR("Fail, DEMOD_O22_VSB_Monitor()\n");
		return RET_ERROR;
	}
#endif

	if(LX_DEMOD_LOCKED == lockState)
	{
		pDemodInfo->unLockCount = 0;
		pDemodInfo->unLockLongCount = 0;

//		if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
//			pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;

		if (RET_OK != _DEMOD_O22_VSB_CheckSignalState(pDemodInfo))
		{
			DEMOD_ERROR("Fail, _DEMOD_O22_VSB_CheckSignalState()\n");
			return RET_ERROR;
		}

		#if 0    // modify chungiii 2016_0319
		if (RET_OK != DEMOD_Get_signal_status(pDemodInfo))
		{
			DEMOD_ERROR("Fail, DEMOD_Get_signal_status()\n");
			return RET_ERROR;
		}
		#endif
/*
		if(pDemodInfo->bIsTPoutEn == TRUE)
		{
			if (RET_OK != DEMOD_O22_TPOutEnable(TRUE))
			{
				DEMOD_ERROR("Fail, DEMOD_O22_TPOutEnable()\n");
				return RET_ERROR;
			}
		}
*/
		if((LX_DEMOD_LOCKED != pDemodInfo->lockStatus)  && (TRUE != pDemodInfo->bNotifiedLock))
		{
			pDemodInfo->lockCount++;
		}

		if(pDemodInfo->lockCount == 2)
		{
			pDemodInfo->lockStatus = LX_DEMOD_LOCKED;
			pDemodInfo->bNotifiedLock = TRUE;
			pDemodInfo->bNotifiedUnlock = FALSE;
			pDemodInfo->signalStatus.bSignalValid = TRUE;

			DEMOD_NOTI("MSG_ATSC_FRONT_END_LOCKED..... ^0^\n");

			if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
				pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;

		}
		if(pDemodInfo->lockCount >= 2)
		{
			pDemodInfo->lockCount = 0;
		}

		if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
		{
			DEMOD_ERROR("Fail, DEMOD_Get_TunedCFG()\n");
			return RET_ERROR;
		}


	}
	else
	{
		pDemodInfo->lockCount = 0;

		if(pauseTimeDemod != LX_DEMOD_LOCK_FAIL_PAUSE_TIME )
			pauseTimeDemod = LX_DEMOD_LOCK_FAIL_PAUSE_TIME;

		if((LX_DEMOD_UNLOCKED != pDemodInfo->lockStatus)  && (TRUE != pDemodInfo->bNotifiedUnlock))
		{
			pDemodInfo->unLockCount++;

			if(pDemodInfo->unLockCount == _VSB_Unlock_Count_Threshold)
			{
				pDemodInfo->lockStatus = LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedLock = FALSE;
				pDemodInfo->bNotifiedUnlock = TRUE;
				pDemodInfo->signalStatus.bSignalValid = FALSE;

				DEMOD_NOTI("MSG_ATSC_FRONT_END_NOT_LOCKED..... -_-\n");
			}
			if(pDemodInfo->unLockCount >= 4)
			{
				pDemodInfo->unLockCount = 0;
			}
		}
	}

	return RET_OK;
}

int _DEMOD_O22_QAM_CheckSignalState (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	pFrontend = DEMOD_O22_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}

#if 0
	printk("[op_mode: %d]\n",		signalStatus.operatingMode);
	printk("[if_agc: %d]\n",		signalStatus.if_agc);
	printk("[mse_info: %d]\n",		signalStatus.mse_info_eq);
	printk("[snr: %d]\n",			signalStatus.snr_eq);
	printk("[dl: %d]\n",			signalStatus.demodLock);
	printk("[ber: %d]\n",			signalStatus.ber);
	printk("[pe: %d]\n",			signalStatus.packetError);
	printk("[afc_freq: %d]\n",		signalStatus.offsetFrq_Hz);
	printk("[constellation: %d]\n",		signalStatus.constellation);
	printk("[sp_inv: %d]\n",		signalStatus.spInv);
	printk("[constPwr: %d]\n",		signalStatus.constPwr);
	printk("[packet error : %d]\n",	signalStatus.packetError);
#endif

	pDemodInfo->signalStatus.packetError 	= signalStatus.packetError;
	pDemodInfo->signalStatus.ber		= signalStatus.ber;
	pDemodInfo->signalStatus.agc		= signalStatus.if_agc;
	pDemodInfo->signalStatus.m.mse		= signalStatus.mse_info_eq;
	pDemodInfo->signalStatus.m.constPwr	= signalStatus.constPwr;
	pDemodInfo->freqOffset 			= signalStatus.offsetFrq_Hz;

	pDemodInfo->signalStatus.operMode 	= pDemodInfo->operMode;
	pDemodInfo->signalStatus.rfMode		= pDemodInfo->systemMode;

	if (signalStatus.packetError > 0) {
		DEMOD_NOTI("packet error occured, agc %d, mse %u, pe %d\n", signalStatus.if_agc, signalStatus.mse_info_eq, signalStatus.packetError);
	}

	return RET_OK;
}

int _DEMOD_O22_QAM_CheckTuneMode (DEMOD_CTX_T *pDemodInfo)
{
	UINT8  new_tuneMode;

	switch (pDemodInfo->setCfgParam.qam.tuneMode)
	{
		case	LX_DEMOD_TUNE_NORMAL:		new_tuneMode = DEMOD_PROP_MODE_TUNE_NORMAL; break;
		case	LX_DEMOD_TUNE_AUTO: 		new_tuneMode = DEMOD_PROP_MODE_TUNE_AUTO; break;
		case	LX_DEMOD_TUNE_MANUAL: 		new_tuneMode = DEMOD_PROP_MODE_TUNE_MANUAL ; break;
	//	case	TU_TUNE_SPEC_DVBC_FIXED_DATA:	new_tuneMode = DEMOD_PROP_MODE_TUNE_FIXED_DATA; break;

		default:				new_tuneMode = DEMOD_PROP_MODE_TUNE_AUTO; break;
	}

	return new_tuneMode;
}

int DEMOD_O22_QAM_SetDemod (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_L2_Context * 	pFrontend;
	UINT8			new_tuneMode;
	UINT32 			freq_Khz = 0;
	UINT16 			ter_bandwidth_KHz;

	pFrontend = DEMOD_O22_GetContext();
	new_tuneMode = _DEMOD_O22_QAM_CheckTuneMode(pDemodInfo);

	if(RET_OK != DEMOD_O22_Get_BW(pDemodInfo, &ter_bandwidth_KHz))
	{
		DEMOD_ERROR("Fail, DEMOD_O22_Get_BW()\n");
		return RET_ERROR;
	}

	DEMOD_L2_ATSC_Set_demod(pFrontend,
				DEMOD_MODULATION_QAM,
				freq_Khz,
				new_tuneMode,
				DEMOD_PROP_MODE_SPECINVAUTO_AUTO,
				DEMOD_PROP_MODE_SPECINV_NORMAL,
				ter_bandwidth_KHz,
				0, 0, 0, 0
				);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_QAM_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O22_QAM_Obtaining_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{

	static LX_DEMOD_FLAG_T 		scanProcessing = LX_DEMOD_FLAG_START;
	static LX_DEMOD_LOCK_STATE_T 	scanLock = LX_DEMOD_UNLOCKED;
	static unsigned int 		sigStablestartTime = 0;
	static unsigned int 		manualOperationTime = 0;
	static LX_DEMOD_TUNE_MODE_T	realTuneMode = LX_DEMOD_TUNE_UNKNOWN;

	switch (pDemodInfo->controlState)
	{
		/***************************************************/
		/***** Configure tuner for desired channel No. *****/
		/***************************************************/
		case LX_DEMOD_TUNE_START:
			{
				if(RET_OK != DEMOD_O22_QAM_SetDemod(pDemodInfo))
				{
					DEMOD_ERROR("Fail, DEMOD_O22_QAM_SetDemod()\n");
					return RET_ERROR;
				}

				if (RET_OK != DEMOD_O22_TPOutEnable(TRUE))
				{
					DEMOD_ERROR("Fail, DEMOD_O22_TPOutEnable()\n");
					return RET_ERROR;
				}

				if(LX_DEMOD_TUNE_NORMAL != pDemodInfo->setCfgParam.qam.tuneMode)
				{
					realTuneMode = LX_DEMOD_TUNE_AUTO;

					if(RET_OK != DEMOD_O22_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_ON, &scanProcessing, &scanLock))
					{
						DEMOD_ERROR("Fail, DEMOD_O22_NeverlockScan()\n");
						return RET_ERROR;
					}
					pDemodInfo->controlState = LX_DEMOD_TUNE_SCAN;
					DEMOD_PRINT("LX_DEMOD_TUNE_START : (auto) Going to LX_DEMOD_TUNE_SCAN..... ^0^\n");

				}
				else
				{
					realTuneMode = LX_DEMOD_TUNE_NORMAL;
					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState = LX_DEMOD_SYNC_CHECKING;
					manualOperationTime = jiffies_to_msecs(jiffies);

					DEMOD_PRINT("LX_DEMOD_TUNE_START :(Manual) Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");

				}


			}

			break;


		/***************************************************/
		/***** Configure demod for scan mode. *****/
		/***************************************************/
		case LX_DEMOD_TUNE_SCAN:
			{

				unsigned int currentTime = 0;
				unsigned int elapsedTime = 0;

				if((LX_DEMOD_FLAG_COMPLETE == pDemodInfo->scanJobFlag) || (LX_DEMOD_FLAG_FINISH == pDemodInfo->scanJobFlag))
				{

					pDemodInfo->controlState = LX_DEMOD_SIGNAL_STABLE;

					DEMOD_PRINT("Already Done\n");
					DEMOD_PRINT("LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
					return RET_OK;
				}

				if(RET_OK != DEMOD_O22_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_OFF, &scanProcessing, &scanLock))
				{
					DEMOD_ERROR("Fail, DEMOD_O22_NeverlockScan()\n");
					return RET_ERROR;
				}

				if((LX_DEMOD_FLAG_FINISH == scanProcessing) && (LX_DEMOD_LOCKED == scanLock))
				{
					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState = LX_DEMOD_SIGNAL_STABLE;

					DEMOD_PRINT("Signal is Found\n");
					DEMOD_PRINT("LX_DEMOD_SYNC_CHECKING : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");

				}
				else if((LX_DEMOD_FLAG_FINISH == scanProcessing)&& (LX_DEMOD_UNLOCKED == scanLock))
				{
					pDemodInfo->scanJobFlag 	= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->bNotifiedUnlock	= TRUE;
					pDemodInfo->bNotifiedLock	= FALSE;
					pDemodInfo->lockStatus		= LX_DEMOD_UNLOCKED;
					pDemodInfo->signalStatus.bSignalValid = FALSE;

					pDemodInfo->controlState 	= LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK;


					currentTime = jiffies_to_msecs(jiffies);
					elapsedTime = currentTime - g_RetuneStartTime;

					DEMOD_NOTI("LX_DEMOD_TUNE_SCAN : MSG_QAM_FRONT_END_NOT_LOCKED..\n") ;
					DEMOD_NOTI("LX_DEMOD_TUNE_SCAN : Elapse time is %d msec\n", elapsedTime) ;

					DEMOD_PRINT("Signal is NOT Found\n");


				}
				else
				{
					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_ING;
//					DEMOD_PRINT("Detection is on processing\n");
				}

			}
			break;




		/********************************************/
		/***** Attempting to finish the tuning state machine *****/
		/********************************************/
		case LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK :
			{


			}
			break;
		/********************************************/
		/***** Attempting to obtain synch lock *****/
		/********************************************/
		case LX_DEMOD_SYNC_CHECKING :
			{

				LX_DEMOD_LOCK_STATE_T	lockState;
				unsigned int 			elapsedTime;

				if (RET_OK != _DEMOD_O22_QAM_CheckSignalState(pDemodInfo))
				{
					DEMOD_ERROR("Fail, _DEMOD_O22_QAM_CheckSignalState()\n");
					return RET_ERROR;
				}

				if(RET_OK != DEMOD_O22_Get_Lock(LX_DEMOD_FEC_LOCK, &lockState))
				{
					DEMOD_ERROR("Fail, DEMOD_O22_Get_Lock()\n");
					return RET_ERROR;
				}

				if(LX_DEMOD_LOCKED == lockState)
				{

					if(RET_OK != DEMOD_O22_QAM_EQ_Signal_Detector(FALSE))
					{
						DEMOD_ERROR("Fail, DEMOD_O22_QAM_EQ_Signal_Detector()\n");
						return RET_ERROR;
					}

					pDemodInfo->controlState	= LX_DEMOD_SIGNAL_STABLE;

					sigStablestartTime = jiffies_to_msecs(jiffies);

					DEMOD_PRINT("LX_DEMOD_SYNC_CHECKING : Going to LX_DEMOD_SIGNAL_STABLE..... ^0^\n");
				}
				else
				{
					if(LX_DEMOD_TUNE_NORMAL == realTuneMode)
					{
						elapsedTime = jiffies_to_msecs(jiffies) - manualOperationTime;


						if(elapsedTime > LX_DEMOD_LOCK_DEALY_300)
						{
							if(RET_OK != DEMOD_O22_QAM_ModeAutoDetection(TRUE))
							{
								DEMOD_ERROR("Fail, DEMOD_O22_QAM_ModeAutoDetection()\n");
								return RET_ERROR;
							}
							#if 0
							if(RET_OK != DEMOD_O22_SoftwareReset())
							{
								DEMOD_ERROR("Fail, DEMOD_O22_SoftwareReset() !!!\n");
								return RET_ERROR;
							}
							#endif


							realTuneMode = LX_DEMOD_TUNE_AUTO;
						}

					}


				}
			}


		   break;

	   	/********************************************/
	   	/***** Attempting to obtain signal stability *****/
		/********************************************/
	   	case LX_DEMOD_SIGNAL_STABLE:
			{
				LX_DEMOD_LOCK_STATE_T			lockState;
				SINT32							freqOffset;
				unsigned int 					elapsedTime;
				UINT32 							packetError;

				if(RET_OK != DEMOD_O22_Get_Lock(LX_DEMOD_FEC_LOCK, &lockState))
				{
					DEMOD_ERROR("Fail, DEMOD_O22_Get_Lock()\n");
					return RET_ERROR;
				}

				if(LX_DEMOD_LOCKED == lockState)
				{

					if (LX_DEMOD_TUNE_NORMAL == pDemodInfo->setCfgParam.qam.tuneMode)
					{
						elapsedTime = jiffies_to_msecs(jiffies) - sigStablestartTime;

						//if(elapsedTime < LX_DEMOD_QAM_SIG_STABLE_WAIT_TIMEOUT)
						if(0)
						{
							break;
						}
						else
						{
							if(RET_OK != DEMOD_O22_Get_Packet_Error(&packetError))
							{
								DEMOD_ERROR("Fail, DEMOD_O22_Get_Packet_Error()\n");
								return RET_ERROR;
							}
							else
							{
								if(packetError < LX_DEMOD_PACKET_ERROR_THD)
								{
									pDemodInfo->bNotifiedLock	= TRUE;
									pDemodInfo->bNotifiedUnlock	= FALSE;
									pDemodInfo->lockStatus		= LX_DEMOD_LOCKED;
									pDemodInfo->signalStatus.bSignalValid = TRUE;

									if (RET_OK != DEMOD_O22_Get_CarrierFreqOffset(&freqOffset))
									{
										DEMOD_ERROR("Fail, DEMOD_O22_Get_CarrierFreqOffset()\n");
										return RET_ERROR;
									}
									pDemodInfo->freqOffset = freqOffset;

									pDemodInfo->controlState	= LX_DEMOD_SIGNAL_LOCKED;

									elapsedTime = jiffies_to_msecs(jiffies) - g_RetuneStartTime;

									DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : MSG_QAM_FRONT_END_LOCKED..... ^^^0^^^\n");
									DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^^^0^^^\n", elapsedTime);
									DEMOD_PRINT("LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^0^\n", freqOffset);

									if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
									{
										DEMOD_ERROR("Fail, DEMOD_Get_TunedCFG()\n");
										return RET_ERROR;
									}
									if (RET_OK != _DEMOD_O22_QAM_CheckSignalState(pDemodInfo))
									{
										DEMOD_ERROR("Fail, _DEMOD_O22_QAM_CheckSignalState()\n");
										return RET_ERROR;
									}

								}
								else
								{
									elapsedTime = jiffies_to_msecs(jiffies) - sigStablestartTime;
									if(elapsedTime > LX_DEMOD_LOCK_DEALY_100)
									{
										pDemodInfo->bNotifiedLock	= TRUE;
										pDemodInfo->bNotifiedUnlock = FALSE;
										pDemodInfo->lockStatus		= LX_DEMOD_LOCKED;
										pDemodInfo->signalStatus.bSignalValid = TRUE;

										if (RET_OK != DEMOD_O22_Get_CarrierFreqOffset(&freqOffset))
										{
											DEMOD_ERROR("Fail, DEMOD_O22_Get_CarrierFreqOffset()\n");
											return RET_ERROR;
										}
										pDemodInfo->freqOffset = freqOffset;

										pDemodInfo->controlState	= LX_DEMOD_SIGNAL_LOCKED;

										elapsedTime = jiffies_to_msecs(jiffies) - g_RetuneStartTime;

										DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : MSG_QAM_FRONT_END_LOCKED..... ^^0^^\n");
										DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^^0^^\n", elapsedTime);
										DEMOD_PRINT("LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^^0^^\n", freqOffset);

										if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
										{
											DEMOD_ERROR("Fail, DEMOD_Get_TunedCFG()\n");
											return RET_ERROR;
										}
										if (RET_OK != _DEMOD_O22_QAM_CheckSignalState(pDemodInfo))
										{
											DEMOD_ERROR("Fail, _DEMOD_O22_QAM_CheckSignalState()\n");
											return RET_ERROR;
										}


									}

								}

							}

						}
					}
					else
					{


						pDemodInfo->bNotifiedLock	= TRUE;
						pDemodInfo->bNotifiedUnlock = FALSE;
						pDemodInfo->lockStatus		= LX_DEMOD_LOCKED;
						pDemodInfo->signalStatus.bSignalValid = TRUE;

						if (RET_OK != DEMOD_O22_Get_CarrierFreqOffset(&freqOffset))
						{
							DEMOD_ERROR("Fail, DEMOD_O22_Get_CarrierFreqOffset()\n");
							return RET_ERROR;
						}
						pDemodInfo->freqOffset = freqOffset;

						pDemodInfo->controlState	= LX_DEMOD_SIGNAL_LOCKED;

						elapsedTime = jiffies_to_msecs(jiffies) - g_RetuneStartTime;

						DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : MSG_QAM_FRONT_END_LOCKED..... ^0^\n");
						DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^0^\n", elapsedTime);
						DEMOD_PRINT("LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^0^\n\n", freqOffset);

						//DEMOD_O22_Get_Dump();

						if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
						{
							DEMOD_ERROR("Fail, DEMOD_Get_TunedCFG()\n");
							return RET_ERROR;
						}
						if (RET_OK != DEMOD_Get_signal_status(pDemodInfo))
						{
							DEMOD_ERROR("Fail, DEMOD_Get_signal_status()\n");
							return RET_ERROR;
						}
					}
				}
				else
				{
					pDemodInfo->controlState	= LX_DEMOD_SYNC_CHECKING;
					DEMOD_PRINT("LX_DEMOD_SYNC_CHECKING : Going back to LX_DEMOD_SYNC_CHECKING.....\n");
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
 * DEMOD_O22_QAM_Monitoring_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O22_QAM_Monitoring_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_LOCK_STATE_T			lockState;

	if(RET_OK != DEMOD_O22_Get_Lock(LX_DEMOD_FEC_LOCK, &lockState))
	{
		DEMOD_ERROR("Fail, DEMOD_O22_Get_Lock()\n");
		return RET_ERROR;
	}
#if 0
	DEMOD_PRINT("pDemodInfo->lockStatus = %d, pDemodInfo->bNotifiedLock = %d, (lockCount = %d) \n",pDemodInfo->lockStatus,pDemodInfo->bNotifiedLock,pDemodInfo->lockCount);
	DEMOD_PRINT("pDemodInfo->lockStatus = %d, pDemodInfo->bNotifiedUnlock = %d,(unlockCnt = %d) \n",pDemodInfo->lockStatus,pDemodInfo->bNotifiedUnlock,pDemodInfo->unLockCount);
	DEMOD_PRINT("lockState = %d) \n",lockState);
#endif
	if(LX_DEMOD_LOCKED == lockState)
	{
		pDemodInfo->unLockCount = 0;
		pDemodInfo->unLockLongCount = 0;


//		if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
//			pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;


		if (RET_OK != _DEMOD_O22_QAM_CheckSignalState(pDemodInfo))
		{
			DEMOD_ERROR("Fail, _DEMOD_O22_QAM_CheckSignalState()\n");
			return RET_ERROR;
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

			DEMOD_NOTI("MSG_QAM_FRONT_END_LOCKED..... ^0^\n");

			if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
				pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;

		}
		if(pDemodInfo->lockCount >= 2)
		{
			pDemodInfo->lockCount = 0;
		}

		if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
		{
			DEMOD_ERROR("Fail, DEMOD_Get_TunedCFG()\n");
			return RET_ERROR;
		}
	}
	else
	{
		pDemodInfo->lockCount = 0;
		_VQI_Full_Pkerr_Count = 0;

		if(pauseTimeDemod != LX_DEMOD_LOCK_FAIL_PAUSE_TIME )
			pauseTimeDemod = LX_DEMOD_LOCK_FAIL_PAUSE_TIME;

		if((LX_DEMOD_UNLOCKED != pDemodInfo->lockStatus)  && (TRUE != pDemodInfo->bNotifiedUnlock))
		{
			pDemodInfo->unLockCount++;

			if(pDemodInfo->unLockCount == _QAM_Unlock_Count_Threshold)
			{
				pDemodInfo->lockStatus 		= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedLock	= FALSE;
				pDemodInfo->bNotifiedUnlock = TRUE;
				pDemodInfo->signalStatus.bSignalValid = FALSE;

				DEMOD_NOTI("MSG_QAM_FRONT_END_NOT_LOCKED..... -_-\n");

			}
			if(pDemodInfo->unLockCount >= 4)
			{
				pDemodInfo->unLockCount = 0;
			}
		}
	}

	return RET_OK;
}



#if 0
#endif

int _DEMOD_O22_ISDB_CheckSignalState (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	UINT32			ber = 0;

	pFrontend = DEMOD_O22_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}

#if 0
	printk("[dd_status] results\n");

	printk("[neverlock: %d]\n",			pFrontend->demod->rsp->dd_status.neverLock);
	printk("[modulation: %d]\n",			pFrontend->demod->rsp->dd_status.reply_operMod);


	printk("[ISDBT_status] results\n");

	printk("[if_agc: %d]\n",			pFrontend->demod->rsp->isdbt_status.if_agc);
	printk("[mse_info: %d]\n",			pFrontend->demod->rsp->isdbt_status.mse_info_eq);
	printk("[op_mode: %d]\n",			pFrontend->demod->rsp->isdbt_status.op_mode);
	printk("[dl: %d]\n",				pFrontend->demod->rsp->isdbt_status.lock_fec);
	printk("[ber: %d]\n",				pFrontend->demod->rsp->isdbt_status.ber);
	printk("[pe: %d]\n",				pFrontend->demod->rsp->isdbt_status.pe);
	printk("[afc_freq: %d]\n",			pFrontend->demod->rsp->isdbt_status.cfo);
	printk("[constellation: %d]\n", 		pFrontend->demod->rsp->isdbt_status.constellation);
	printk("[sp_inv: %d]\n",			pFrontend->demod->rsp->isdbt_status.spInv);
	printk("[fft_mode: %d]\n",			pFrontend->demod->rsp->isdbt_status.fft_mode);
	printk("[guard_int: %d]\n",			pFrontend->demod->rsp->isdbt_status.gi);

	printk("[A. QAM mode : %d]\n",			pFrontend->demod->rsp->isdbt_status.oqama);
	printk("[A. code rate : %d]\n", 		pFrontend->demod->rsp->isdbt_status.ocra);
	printk("[A. segment num : %d]\n",		pFrontend->demod->rsp->isdbt_status.onsega);
	printk("[A. interleaving length : %d]\n",	pFrontend->demod->rsp->isdbt_status.oila);

	printk("[B. QAM mode : %d]\n",			pFrontend->demod->rsp->isdbt_status.oqamb);
	printk("[B. code rate : %d]\n", 		pFrontend->demod->rsp->isdbt_status.ocrb);
	printk("[B. segment num : %d]\n",		pFrontend->demod->rsp->isdbt_status.onsegb);
	printk("[B. interleaving length : %d]\n",	pFrontend->demod->rsp->isdbt_status.oilb);

	printk("[C. QAM mode : %d]\n",			pFrontend->demod->rsp->isdbt_status.oqamc);
	printk("[C. code rate : %d]\n", 		pFrontend->demod->rsp->isdbt_status.ocrc);
	printk("[C. segment num : %d]\n",		pFrontend->demod->rsp->isdbt_status.onsegc);
	printk("[C. interleaving length : %d]\n",	pFrontend->demod->rsp->isdbt_status.oilc);
#endif

#if 0
	printk("[dd_status] results\n");

	printk("[neverlock: %d]\n",			pFrontend->demod->rsp->dd_status.neverLock);
	printk("[modulation: %d]\n",			pFrontend->demod->rsp->dd_status.reply_operMod);

	printk("[ISDBT_status] results\n");

	printk("[op_mode: %d]\n",			signalStatus.operatingMode);
	printk("[if_agc: %d]\n",			signalStatus.if_agc);
	printk("[mse_info: %d]\n",			signalStatus.mse_info_eq);
	printk("[snr: %d]\n",				signalStatus.snr_eq);
	printk("[dl: %d]\n",				signalStatus.demodLock);
	printk("[ber: %d]\n",				signalStatus.ber);
	printk("[pe: %d]\n",				signalStatus.packetError);
	printk("[afc_freq: %d]\n",			signalStatus.offsetFrq_Hz);//signalStatus.offsetFrq_Hz / 1000);
	printk("[constellation: %d]\n", 		signalStatus.constellation);
	printk("[sp_inv: %d]\n",			signalStatus.spInv);
	printk("[bandwidth: %d]\n",			signalStatus.bandwidth);
	printk("[constPwr: %d]\n",			signalStatus.constPwr);
#endif

	ber =  (UINT32)(pFrontend->demod->rsp->isdbt_status.ber);

	pDemodInfo->signalStatus.packetError 		= (UINT32)(pFrontend->demod->rsp->isdbt_status.pe);
	pDemodInfo->signalStatus.ber			= (UINT32)(ber);//(UINT32)(ber * 1000000);
	pDemodInfo->signalStatus.agc			= signalStatus.if_agc;
	//pDemodInfo->signalStatus.m.mse		= signalStatus.mse;
	//pDemodInfo->signalStatus.m.mse		= pFrontend->demod->rsp->isdbt_status.mse_info_eq;
	pDemodInfo->signalStatus.m.mse			= signalStatus.mse_info_demod;
	pDemodInfo->signalStatus.m.constPwr		= signalStatus.constPwr;

	pDemodInfo->freqOffset 				= signalStatus.offsetFrq_Hz;

	pDemodInfo->signalStatus.operMode 		= pDemodInfo->operMode;
	pDemodInfo->signalStatus.rfMode			= pDemodInfo->systemMode;

	if (signalStatus.packetError > 0) {
		DEMOD_NOTI("packet error occured, agc %d, mse %u, pe %d\n", signalStatus.if_agc, signalStatus.mse_info_demod, pDemodInfo->signalStatus.packetError);
	}

	return RET_OK;
}


int _DEMOD_O22_ISDB_CheckTuneMode (DEMOD_CTX_T *pDemodInfo)
{
	UINT8  new_tuneMode;

	switch (pDemodInfo->setCfgParam.isdbt.tuneMode)
	{
		case	LX_DEMOD_TUNE_NORMAL:		new_tuneMode = DEMOD_PROP_MODE_TUNE_NORMAL; break;
		case	LX_DEMOD_TUNE_AUTO: 		new_tuneMode = DEMOD_PROP_MODE_TUNE_AUTO; break;
		case	LX_DEMOD_TUNE_MANUAL: 		new_tuneMode = DEMOD_PROP_MODE_TUNE_MANUAL ; break;
	//	case	TU_TUNE_SPEC_DVBC_FIXED_DATA:	new_tuneMode = DEMOD_PROP_MODE_TUNE_FIXED_DATA; break;

		default:				new_tuneMode = DEMOD_PROP_MODE_TUNE_AUTO; break;
	}

	return new_tuneMode;
}


int DEMOD_O22_ISDB_SetDemod (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_L2_Context *	pFrontend;

	UINT8			new_tuneMode = 0;
	UINT32 			freq_Khz = 0;
	UINT16 			ter_bandwidth_KHz = 0;

	pFrontend = DEMOD_O22_GetContext();

	new_tuneMode = _DEMOD_O22_ISDB_CheckTuneMode(pDemodInfo);

	if(RET_OK != DEMOD_O22_Get_BW(pDemodInfo, &ter_bandwidth_KHz))
	{
		DEMOD_ERROR("Fail, DEMOD_O22_Get_BW()\n");
		return RET_ERROR;
	}

	DEMOD_L2_ATSC_Set_demod(pFrontend,
				DEMOD_MODULATION_ISDBT,
				freq_Khz,
				new_tuneMode,
				DEMOD_PROP_MODE_SPECINVAUTO_MANUAL,
				DEMOD_PROP_MODE_SPECINV_NORMAL,
				ter_bandwidth_KHz,
				0, 0, 0, 0
				);

	return RET_OK;
}

int DEMOD_O22_ISDBT_Set_MemSconfig (void)
{
	LX_DEMOD_L2_Context *	pFrontend;

	UINT32			st_mem = gMemCfgDEMOD_ISDBT.memory_base;

	pFrontend = DEMOD_O22_GetContext();

	if(st_mem == 0)
	{
		DEMOD_WARN("Wrong Memory Base Address\n");
	}
	else
	{
		DEMOD_PRINT("st_mem[0x%x] \n", st_mem);
		if(RET_OK != DEMOD_L2_ISDB_Set_BaseAddr_AXI(pFrontend, st_mem))
		{
			DEMOD_ERROR("Fail, DEMOD_L2_ISDB_Set_BaseAddr_AXI()\n");
			return RET_ERROR;
		}
	}

	return RET_OK;
}


int DEMOD_O22_ISDBT_GetEmergencyAlertFlagStatus (BOOLEAN *pEalarm)
{
	LX_DEMOD_L2_Context *	pFrontend;
	UINT8 			balarm;

	pFrontend = DEMOD_O22_GetContext();

	if(RET_OK != DEMOD_L2_ISDB_Get_Emergency_Alarm(pFrontend, &balarm))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_ISDB_Get_Emergency_Alarm()\n");
		return RET_ERROR;
	}

	if(balarm == 1)
	{
		DEMOD_PRINT("EWBS is operated[0x%x]\n", balarm);
		*pEalarm = TRUE;
	}
	else
	{
		DEMOD_PRINT("EWBS is not operated[0x%x]\n", balarm);
		*pEalarm = FALSE;
	}

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_ISDBT_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O22_ISDBT_Obtaining_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{
	static LX_DEMOD_FLAG_T 		scanProcessing = LX_DEMOD_FLAG_START;
	static LX_DEMOD_LOCK_STATE_T 	scanLock = LX_DEMOD_UNLOCKED;
	static unsigned int 		sigStablestartTime = 0;

	switch (pDemodInfo->controlState)
	{
		/***************************************************/
		/***** Configure tuner for desired channel No. *****/
		/***************************************************/
		case LX_DEMOD_TUNE_START:
			{
				if(RET_OK != DEMOD_O22_ISDB_SetDemod(pDemodInfo))
				{
					DEMOD_ERROR("Fail, DEMOD_O22_ISDB_SetDemod()\n");
					return RET_ERROR;
				}

				if(LX_DEMOD_TUNE_NORMAL != pDemodInfo->setCfgParam.isdbt.tuneMode)
				{
					if(RET_OK != DEMOD_O22_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_ON, &scanProcessing, &scanLock))
					{
						DEMOD_ERROR("Fail, DEMOD_O22_NeverlockScan()\n");
						return RET_ERROR;
					}
					pDemodInfo->controlState = LX_DEMOD_TUNE_SCAN;
					DEMOD_PRINT("LX_DEMOD_TUNE_START : Going to LX_DEMOD_TUNE_SCAN..... ^0^\n");
				}
				else
				{
					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState = LX_DEMOD_SYNC_CHECKING;

					DEMOD_PRINT("LX_DEMOD_TUNE_START : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
				}
			}
			break;

		/***************************************************/
		/***** Configure demod for scan mode. *****/
		/***************************************************/
		case LX_DEMOD_TUNE_SCAN:
			{
				unsigned int currentTime = 0;
				unsigned int elapsedTime = 0;

				if((LX_DEMOD_FLAG_COMPLETE == pDemodInfo->scanJobFlag) || (LX_DEMOD_FLAG_FINISH == pDemodInfo->scanJobFlag))
				{

					pDemodInfo->controlState = LX_DEMOD_SIGNAL_STABLE;

					DEMOD_PRINT("Already Done\n");
					DEMOD_PRINT("LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");

					return RET_OK;
				}

				if(RET_OK != DEMOD_O22_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_OFF, &scanProcessing, &scanLock))
				{
					DEMOD_ERROR("Fail, DEMOD_O22_NeverlockScan()\n");
					return RET_ERROR;
				}

				if((LX_DEMOD_FLAG_FINISH == scanProcessing) && (LX_DEMOD_LOCKED == scanLock))
				{
					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState = LX_DEMOD_SYNC_CHECKING;

					DEMOD_PRINT("Signal is Found\n");
					DEMOD_PRINT("LX_DEMOD_SYNC_CHECKING : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
				}

				else if((LX_DEMOD_FLAG_FINISH == scanProcessing)&& (LX_DEMOD_UNLOCKED == scanLock))
				{
					pDemodInfo->scanJobFlag 	= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->bNotifiedUnlock	= TRUE;
					pDemodInfo->bNotifiedLock	= FALSE;
					pDemodInfo->lockStatus		= LX_DEMOD_UNLOCKED;
					pDemodInfo->signalStatus.bSignalValid = FALSE;

					pDemodInfo->controlState 	= LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK;

					currentTime = jiffies_to_msecs(jiffies);
					elapsedTime = currentTime - g_RetuneStartTime;

					DEMOD_NOTI("LX_DEMOD_TUNE_SCAN : MSG_ISDBT_FRONT_END_NOT_LOCKED..\n") ;
					DEMOD_NOTI("LX_DEMOD_TUNE_SCAN : Elapse time is %d msec\n", elapsedTime) ;

					DEMOD_PRINT("Signal is NOT Found\n");
				}
				else
				{
					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_ING;
					DEMOD_PRINT("Detection is on processing\n");
				}

			}
			break;

		/********************************************/
		/***** Attempting to finish the tuning state machine *****/
		/********************************************/
		case LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK :
			{


			}
			break;

		/********************************************/
		/***** Attempting to obtain synch lock *****/
		/********************************************/
		case LX_DEMOD_SYNC_CHECKING :
			{

				LX_DEMOD_LOCK_STATE_T	lockState;

				if(RET_OK != DEMOD_O22_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
				{
					DEMOD_ERROR("Fail, DEMOD_O22_NeverlockScan()\n");
					return RET_ERROR;
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					pDemodInfo->controlState	= LX_DEMOD_SIGNAL_STABLE;
					pDemodInfo->unLockLongCount = 0;

					sigStablestartTime = jiffies_to_msecs(jiffies);

					DEMOD_PRINT("LX_DEMOD_SYNC_CHECKING : Going to LX_DEMOD_SIGNAL_STABLE..... ^0^\n");
				}
				else
				{
				}
			}
			break;

	   	/********************************************/
	   	/***** Attempting to obtain signal stability *****/
		/********************************************/
	   	case LX_DEMOD_SIGNAL_STABLE:
			{
				LX_DEMOD_LOCK_STATE_T	lockState;
				SINT32			freqOffset;
				unsigned int 		elapsedTime;
				UINT32 			packetError;

				if(RET_OK != DEMOD_O22_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
				{
					DEMOD_ERROR("Fail, DEMOD_O22_Get_Lock()\n");
					return RET_ERROR;
				}

				if(LX_DEMOD_LOCKED == lockState)
				{

					if (LX_DEMOD_TUNE_NORMAL == pDemodInfo->setCfgParam.isdbt.tuneMode)
					{
						elapsedTime = jiffies_to_msecs(jiffies) - sigStablestartTime;

						if(elapsedTime < LX_DEMOD_ISDBT_SIG_STABLE_WAIT_TIMEOUT)
						{
							break;
						}
						else
						{
							if(RET_OK != DEMOD_O22_Get_Packet_Error(&packetError))
							{
								DEMOD_ERROR("Fail, DEMOD_O22_Get_Packet_Error()\n");
								return RET_ERROR;
							}
							else
							{
#if 0
								if(RET_OK != DEMOD_O22_ISDBT_Set_PhaseNoiseEnhancement(TRUE))
								{
									DEMOD_ERROR("Fail, DEMOD_O22_ISDBT_Set_PhaseNoiseEnhancement()\n");
									return RET_ERROR;
								}
#endif
								if(packetError < LX_DEMOD_PACKET_ERROR_THD)
								{
									pDemodInfo->bNotifiedLock	= TRUE;
									pDemodInfo->bNotifiedUnlock	= FALSE;
									pDemodInfo->lockStatus		= LX_DEMOD_LOCKED;
									pDemodInfo->signalStatus.bSignalValid = TRUE;

									if (RET_OK != DEMOD_O22_Get_CarrierFreqOffset(&freqOffset))
									{
										DEMOD_ERROR("Fail, DEMOD_O22_Get_CarrierFreqOffset()\n");
										return RET_ERROR;
									}
									pDemodInfo->freqOffset = freqOffset;

									pDemodInfo->controlState	= LX_DEMOD_SIGNAL_LOCKED;

									elapsedTime = jiffies_to_msecs(jiffies) - g_RetuneStartTime;

									DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : MSG_ISDBT_FRONT_END_LOCKED..... ^^^0^^^\n");
									DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^^^0^^^\n", elapsedTime);
									DEMOD_PRINT("LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^^^0^^^\n", freqOffset);

									if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
									{
										DEMOD_ERROR("Fail, DEMOD_Get_TunedCFG()\n");
										return RET_ERROR;
									}
									if (RET_OK != DEMOD_Get_signal_status(pDemodInfo))
									{
										DEMOD_ERROR("Fail, DEMOD_Get_signal_status()\n");
										return RET_ERROR;
									}

								}
								else
								{
									elapsedTime = jiffies_to_msecs(jiffies) - sigStablestartTime;
									if(elapsedTime > LX_DEMOD_LOCK_DEALY_100)
									{
										pDemodInfo->bNotifiedLock	= TRUE;
										pDemodInfo->bNotifiedUnlock = FALSE;
										pDemodInfo->lockStatus		= LX_DEMOD_LOCKED;
										pDemodInfo->signalStatus.bSignalValid = TRUE;

										if (RET_OK != DEMOD_O22_Get_CarrierFreqOffset(&freqOffset))
										{
											DEMOD_ERROR("Fail, DEMOD_O22_Get_CarrierFreqOffset()\n");
											return RET_ERROR;
										}
										pDemodInfo->freqOffset = freqOffset;

										pDemodInfo->controlState	= LX_DEMOD_SIGNAL_LOCKED;

										elapsedTime = jiffies_to_msecs(jiffies) - g_RetuneStartTime;

										DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : MSG_ISDBT_FRONT_END_LOCKED..... ^^0^^\n");
										DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^^0^^\n", elapsedTime);
										DEMOD_PRINT("LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^^0^^\n", freqOffset);

										if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
										{
											DEMOD_ERROR("Fail, DEMOD_Get_TunedCFG()\n");
											return RET_ERROR;
										}
										if (RET_OK != DEMOD_Get_signal_status(pDemodInfo))
										{
											DEMOD_ERROR("Fail, DEMOD_Get_signal_status()\n");
											return RET_ERROR;
										}
									}
								}
							}
						}
					}
					else
					{
						pDemodInfo->bNotifiedLock	= TRUE;
						pDemodInfo->bNotifiedUnlock = FALSE;
						pDemodInfo->lockStatus		= LX_DEMOD_LOCKED;
						pDemodInfo->signalStatus.bSignalValid = TRUE;

						if (RET_OK != DEMOD_O22_Get_CarrierFreqOffset(&freqOffset))
						{
							DEMOD_ERROR("Fail, DEMOD_O22_Get_CarrierFreqOffset()\n");
							return RET_ERROR;
						}
						pDemodInfo->freqOffset = freqOffset;

						pDemodInfo->controlState	= LX_DEMOD_SIGNAL_LOCKED;

						elapsedTime = jiffies_to_msecs(jiffies) - g_RetuneStartTime;


						DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : MSG_ISDBT_FRONT_END_LOCKED..... ^0^\n");
						DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^0^\n", elapsedTime);
						DEMOD_PRINT("LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^0^\n", freqOffset);

						if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
						{
							DEMOD_ERROR("Fail, DEMOD_Get_TunedCFG()\n");
							return RET_ERROR;
						}
						if (RET_OK != DEMOD_Get_signal_status(pDemodInfo))
						{
							DEMOD_ERROR("Fail, DEMOD_Get_signal_status()\n");
							return RET_ERROR;
						}
					}
				}
				else
				{
					pDemodInfo->controlState	= LX_DEMOD_SYNC_CHECKING;
					DEMOD_PRINT("LX_DEMOD_SYNC_CHECKING : Going back to LX_DEMOD_SYNC_CHECKING.....\n");
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
 * DEMOD_O22_ISDBT_Monitoring_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O22_ISDBT_Monitoring_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{

	LX_DEMOD_LOCK_STATE_T		lockState;
	unsigned int			powerOnElapsedTime;

	if(RET_OK != DEMOD_O22_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState)) {
		DEMOD_ERROR("Fail, DEMOD_O22_Get_Lock()\n");
		return RET_ERROR;
	}
#if 0
	DEMOD_PRINT("pDemodInfo->lockStatus = %d, pDemodInfo->bNotifiedLock = %d, (lockCount = %d) \n",pDemodInfo->lockStatus,pDemodInfo->bNotifiedLock,pDemodInfo->lockCount);
	DEMOD_PRINT("pDemodInfo->lockStatus = %d, pDemodInfo->bNotifiedUnlock = %d,(unlockCnt = %d) \n",pDemodInfo->lockStatus,pDemodInfo->bNotifiedUnlock,pDemodInfo->unLockCount);
	DEMOD_PRINT("lockState = %d) \n",lockState);
#endif
	if(LX_DEMOD_LOCKED == lockState) {
		pDemodInfo->unLockCount = 0;
		pDemodInfo->unLockLongCount	= 0;

//		if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
//			pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;

		if (RET_OK != _DEMOD_O22_ISDB_CheckSignalState(pDemodInfo)) {
			DEMOD_ERROR("Fail, _DEMOD_O22_ISDB_CheckSignalState()\n");
			return RET_ERROR;
		}

		if(pDemodInfo->signalStatus.packetError >= _ISDBT_Full_Pkerr_Threshold) {
			_VQI_Full_Pkerr_Count++;
			DEMOD_PRINT("_VQI_Full_Pkerr_Count = %d !!!\n", _VQI_Full_Pkerr_Count);

			if(_VQI_Full_Pkerr_Count == _VQI_Full_Pkerr_Count_Threshold)
			{
				DEMOD_ERROR("Oops !! Force to NOT LOCK by Full Packet error Count\n");

				_VQI_Full_Pkerr_Count = 0;

				pDemodInfo->lockStatus		= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedUnlock = TRUE;
				pDemodInfo->bNotifiedLock	= FALSE;
				pDemodInfo->signalStatus.bSignalValid = FALSE;

			}

		} else {
			_VQI_Full_Pkerr_Count = 0;

			if(gLGDBB_PowerOnInit == 2)
			{
				powerOnElapsedTime = jiffies_to_msecs(jiffies) - _PowerOnInitSTartTime;

				DEMOD_PRINT("powerOnElapsedTime = %d \n",powerOnElapsedTime);

				if(powerOnElapsedTime >= 15000)
				{
					gLGDBB_PowerOnInit = 0;

					if (RET_OK != DEMOD_O22_ISDBT_Set_CrGearshEn(TRUE ))
					{
						DEMOD_ERROR("Fail, DEMOD_O22_ISDBT_Set_CrGearshEn()\n");
						return RET_ERROR;
					}
				}
			}

			if((LX_DEMOD_LOCKED != pDemodInfo->lockStatus)  && (TRUE != pDemodInfo->bNotifiedLock))
			{
				pDemodInfo->lockCount++;
			}
			if(pDemodInfo->lockCount == 1)
			{
				pDemodInfo->lockStatus		= LX_DEMOD_LOCKED;
				pDemodInfo->bNotifiedLock 	= TRUE;
				pDemodInfo->bNotifiedUnlock = FALSE;
					pDemodInfo->signalStatus.bSignalValid = TRUE;

				DEMOD_NOTI("MSG_ISDBT_FRONT_END_LOCKED..... ^0^\n");

				if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
					pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;
			}
			if(pDemodInfo->lockCount >= 1)
			{
				pDemodInfo->lockCount = 0;
			}

#if 0
			if(RET_OK != DEMOD_O22_ISDBT_Set_PhaseNoiseEnhancement(TRUE))
			{
				DEMOD_ERROR("Fail, DEMOD_O22_ISDBT_Set_PhaseNoiseEnhancement() !!!\n");
				return RET_ERROR;
			}
#endif
			if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
			{
				DEMOD_ERROR("Fail, DEMOD_Get_TunedCFG()\n");
				return RET_ERROR;
			}
		}
	} else {
		pDemodInfo->lockCount = 0;
		_VQI_Full_Pkerr_Count = 0;

		if(pauseTimeDemod != LX_DEMOD_LOCK_FAIL_PAUSE_TIME )
			pauseTimeDemod = LX_DEMOD_LOCK_FAIL_PAUSE_TIME;

		if((LX_DEMOD_UNLOCKED != pDemodInfo->lockStatus)  && (TRUE != pDemodInfo->bNotifiedUnlock))
		{
			pDemodInfo->unLockCount++;

			if(pDemodInfo->unLockCount == _ISDBT_Unlock_Count_Threshold)
			{
				pDemodInfo->lockStatus 		= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedUnlock = TRUE;
				pDemodInfo->bNotifiedLock	= FALSE;
				pDemodInfo->signalStatus.bSignalValid = FALSE;

				DEMOD_NOTI("MSG_ISDBT_FRONT_END_NOT_LOCKED..... -_-\n");
			}
			if(pDemodInfo->unLockCount >= 2)
			{
				pDemodInfo->unLockCount = 0;
			}
		}
	}

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_QAM_SoftwareResetFEC.
 * Reset QAM FEC module.
 *
 * @param [in] NONE
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_QAM_SoftwareResetFEC (void)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_QAM_Monitor.
 * Monitoring
 *
 * @param  NONE [IN] void .
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O22_QAM_Monitor (void)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_QAM_ModeAutoDetection.
 * Enable/Disable the detection of QAM mode
 *
 * @param  bEnable [IN] - BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR.
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_QAM_ModeAutoDetection (BOOLEAN bEnable)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_QAM_64Mode.
 * Set the QAM mode to QAM64 manually
 *
 * @param  NONE [IN/OUT].
 * @return if Succeeded - RET_OK else-RET_ERROR.
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_QAM_64Mode (void)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_QAM_256Mode.
 * Set the QAM mode to QAM256 manually
 *
 * @param  NONE [IN/OUT].
 * @return if Succeeded - RET_OK else-RET_ERROR.
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_QAM_256Mode (void)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_QAM_Set_DefaultRegisterValue.
 * Initialize LG1150 GBB for QAM mode.
 *
 * @param  NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR.
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_QAM_Set_DefaultRegisterValue (void)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_QAM_Set_NeverLockWaitTime
 * Set neverlock waiting period.
 *
 * @param waitMs 	[IN] UINT32 - unit: ms
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_QAM_Set_NeverLockWaitTime (UINT32 waitMs)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_QAM_Get_TotalInfo
 * Get all information on QAM for debug
 *
 * @param NONE [IN / OUT].
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_QAM_Get_TotalInfo (void)
{
	return RET_OK;
}

/**
 * DEMOD_O22_QAM_EQ_Signal_Detector.
 * Disable no signal detector function
 *
 * @param [in] NONE
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_QAM_EQ_Signal_Detector (BOOLEAN OnOff)
{
	return RET_OK;
}

/**
 * DEMOD_O22_ISDBT_SetDefaultRegisterValue
 * Set defualt register value on DVB-T.
 *
 * @param none
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O22_ISDBT_Set_DefaultRegisterValue (void)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_ISDBT_Set_Config_auto
 * Control automatic setting of DVB-T config.
 *
 * @param bAutoDetect 	[IN] BOOLEAN - automatic setting (TRUE) / manual setting(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_ISDBT_Set_Config_auto (BOOLEAN bAutoDetect)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_ISDBT_Set_PartialConfig
 * Set hierachical signal path and bandwidth.
 * This function is used when DEMOD_O22_ISDBT_Set_Config_auto is enabled.
 *
 * @param *pIsdbtConfigParam 	[IN] LX_DEMOD_ISDBT_CONFIG_T - ISDBT config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_ISDBT_Set_PartialConfig (LX_DEMOD_ISDBT_CONFIG_T *pIsdbtConfigParam)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_ISDBT_Set_FullConfig
 * Set all config parameters on DVB-T.
 * This function is used when DEMOD_O22_ISDBT_Set_Config_auto is disabled.
 *
 * @param *pIsdbtConfigParam 	[IN] LX_DEMOD_ISDBT_CONFIG_T - ISDB-T config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_ISDBT_Set_FullConfig (LX_DEMOD_ISDBT_CONFIG_T *pIsdbtConfigParam)
{
	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_ISDBT_Set_NeverLockWaitTime
 * Set neverlock waiting period.
 *
 * @param waitMs 	[IN] UINT32 - unit: ms
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_ISDBT_Set_NeverLockWaitTime (UINT32 waitMs)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_ISDBT_Set_CrGearshEn
 * enable/disable Carrier recovery bandwidth gear shift
 *
 * @param bEnable 	[IN] BOOLEAN
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_ISDBT_Set_CrGearshEn (BOOLEAN bEnable)
{
	return RET_OK;
}



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_ISDBT_Set_PhaseNoiseEnhancement
 * Get delay spread state on ISDBT.
 *
 * @param [IN] bEnhanced - BOOLEAN 	[OUT] UINT16.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_ISDBT_Set_PhaseNoiseEnhancement (BOOLEAN bEnhanced)
{
	return RET_OK;
}



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_ISDBT_Get_DelaySpreadStatus
 * Get delay spread state on ISDB-T.
 *
 * @param *pDelaySpread 	[OUT] UINT16.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_ISDBT_Get_DelaySpreadStatus (UINT16 *pDelaySpread)
{
	return RET_OK;
}




/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_ISDBT_Get_FFTMode
 * Get the information of bandwidth on ISDB-T.
 *
 * @param *pTxModeLock 	[OUT] LX_DEMOD_LOCK_STATE_T - FFT mode lock state.
 * @param *pFftMode 	[OUT] LX_DEMOD_FFTMODE_T - detected FFT mode.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_ISDBT_Get_FFTMode (LX_DEMOD_LOCK_STATE_T *pTxModeLock, LX_DEMOD_FFTMODE_T *pFftMode)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_TMCC_INFO 	tmcc;

	LX_DEMOD_CMD_ISDBT_STATUS_REPLY_struct	isdbt_status;

	int			ret;

	pFrontend = DEMOD_O22_GetContext();

//	LX_DEMOD_LOCK_STATE_T	lockState;

//	UINT8	modelock_di;
//	UINT8	fftmoder_di_1_0;

	isdbt_status = pFrontend->demod->rsp->isdbt_status;

	*pTxModeLock = LX_DEMOD_UNLOCKED;
	*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN;

#if 0
	if(RET_OK != DEMOD_O22_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
	{
		DEMOD_ERROR("Fail, DEMOD_O22_Get_Lock() !!!\n");
		return RET_ERROR;
	}
#endif

#if 0
	if(RET_OK != DEMOD_L2_ISDB_Get_TMCC_Info(pFrontend, &tmcc))
	{
		DEMOD_NOTI("Fail, DEMOD_L2_ISDB_Get_TMCC_Info()\n");
		return RET_ERROR;
	}
#endif

	ret = DEMOD_L2_ISDB_Get_TMCC_Info(pFrontend, &tmcc);

	if(RET_OK != ret)
	{
		DEMOD_ERROR("Fail, DEMOD_L2_ISDB_Get_TMCC_Info()\n");
		return RET_ERROR;
	}

#if 0
	printk(" tmcc.isLock [%d]\n", tmcc.isLock);
	printk(" tmcc.fft_mode [%d]\n", tmcc.fft_mode);
#endif

	if (tmcc.isLock != LX_DEMOD_LOCKED)
	{
		*pTxModeLock = LX_DEMOD_UNLOCKED;
		*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN;

		return RET_OK;
	}

	*pTxModeLock = LX_DEMOD_LOCKED;

	switch (tmcc.fft_mode) {
	case DEMOD_FFT_MODE_2K :
		*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_2K;
		break;

	case DEMOD_FFT_MODE_8K:
		*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_8K;
		break;

	case DEMOD_FFT_MODE_4K:
		*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_4K;
		break;

	default :
		*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN;
		break;
	}

	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_ISDBT_Get_GuradIntervalMode
 * Get the information of guard interval on ISDB-T.
 *
 * @param *pGIMode 	[OUT] LX_DEMOD_GIMODE_T - 1/32, 1/16, 1/8 and 1/4.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_ISDBT_Get_GuradIntervalMode (LX_DEMOD_GIMODE_T *pGIMode)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_TMCC_INFO	tmcc;

	LX_DEMOD_CMD_ISDBT_STATUS_REPLY_struct	isdbt_status;

	int			ret;

	pFrontend = DEMOD_O22_GetContext();

	isdbt_status = pFrontend->demod->rsp->isdbt_status;

	*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_UNKNOWN;

#if 0
	if(RET_OK != DEMOD_O22_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
	{
		DEMOD_ERROR("Fail, DEMOD_O22_Get_Lock()\n");
		return RET_ERROR;
	}

#endif

#if 0
	if(RET_OK != DEMOD_L2_ISDB_Get_TMCC_Info(pFrontend, &tmcc))
	{
		DEMOD_NOTI("Fail, DEMOD_L2_ISDB_Get_TMCC_Info()\n");
		return RET_ERROR;
	}

#endif

	ret = DEMOD_L2_ISDB_Get_TMCC_Info(pFrontend, &tmcc);

	if(RET_OK != ret)
	{
		DEMOD_ERROR("Fail, DEMOD_L2_ISDB_Get_TMCC_Info()\n");
		return RET_ERROR;
	}

	if (tmcc.isLock != LX_DEMOD_LOCKED)
	{
		*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_UNKNOWN;

		return RET_OK;
	}

	switch (tmcc.gi) {
	case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_1_4:
		*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_4;
		break;

	case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_1_8:
		*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_8;
		break;

	case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_1_16:
		*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_16;
		break;

	case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_1_32:
		*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_32;
		break;

	default:
		*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_UNKNOWN;
		break;
	}

	return RET_OK;

}



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_ISDBT_Get_TMCCInfo
 * Get TPS information on ISDBT
 *
 * @param *pTpsParams [OUT] LX_DEMOD_ISDBT_TMCC_CONFIG_T - TMCC data structure.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_ISDBT_Get_TMCCInfo (LX_DEMOD_ISDBT_TMCC_CONFIG_T *pTmccParams)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_TMCC_INFO	tmcc;

	LX_DEMOD_CMD_ISDBT_STATUS_REPLY_struct	isdbt_status;

	int			ret;

	pFrontend = DEMOD_O22_GetContext();

	isdbt_status = pFrontend->demod->rsp->isdbt_status;

	ret = DEMOD_L2_ISDB_Get_TMCC_Info(pFrontend, &tmcc);

	if(RET_OK != ret)
	{
	  DEMOD_ERROR("Fail, DEMOD_L2_ISDB_Get_TMCC_Info()\n");
	  return RET_ERROR;
	}

	if (tmcc.isLock  != LX_DEMOD_LOCKED)
	{
		pTmccParams->layerACodeRate = LX_DEMOD_CODE_UNKNOWN;
		pTmccParams->layerAQamMode = LX_DEMOD_UNKOWN_MODE;

		pTmccParams->layerBCodeRate = LX_DEMOD_CODE_UNKNOWN;
		pTmccParams->layerBQamMode = LX_DEMOD_UNKOWN_MODE;

		pTmccParams->layerCCodeRate = LX_DEMOD_CODE_UNKNOWN;
		pTmccParams->layerCQamMode = LX_DEMOD_UNKOWN_MODE;

		return RET_OK;
	}

	pTmccParams->layerASegmentNum = tmcc.segNum_a;
	pTmccParams->layerBSegmentNum = tmcc.segNum_b;
	pTmccParams->layerCSegmentNum = tmcc.segNum_c;

	if((tmcc.segNum_a > tmcc.segNum_b) && (tmcc.segNum_a > tmcc.segNum_c))
	{
		switch (tmcc.codeRate_a) {
		case DEMOD_CODERATE_DVBT_ISDBT_1_2:
			pTmccParams->layerACodeRate = LX_DEMOD_CODE_1_2;
			break;

		case DEMOD_CODERATE_DVBT_ISDBT_2_3:
			pTmccParams->layerACodeRate = LX_DEMOD_CODE_2_3;
			break;

		case DEMOD_CODERATE_DVBT_ISDBT_3_4:
			pTmccParams->layerACodeRate = LX_DEMOD_CODE_3_4;
			break;

		case DEMOD_CODERATE_DVBT_ISDBT_5_6:
			pTmccParams->layerACodeRate = LX_DEMOD_CODE_5_6;
			break;

		case DEMOD_CODERATE_DVBT_ISDBT_7_8:
			pTmccParams->layerACodeRate = LX_DEMOD_CODE_7_8;
			break;

		default:
			pTmccParams->layerACodeRate = LX_DEMOD_CODE_UNKNOWN;
			break;
		}

		switch (tmcc.qamMode_a) {
		case DEMOD_CONSTELLATION_DQPSK:
			pTmccParams->layerAQamMode = LX_DEMOD_DQPSK;
			break;

		case DEMOD_CONSTELLATION_QPSK:
			pTmccParams->layerAQamMode = LX_DEMOD_QPSK;
			break;

		case DEMOD_CONSTELLATION_QAM16:
			pTmccParams->layerAQamMode = LX_DEMOD_16QAM;
			break;

		case DEMOD_CONSTELLATION_QAM64:
			pTmccParams->layerAQamMode = LX_DEMOD_64QAM;
			break;

		default:
			pTmccParams->layerAQamMode = LX_DEMOD_UNKOWN_MODE;
			break;
		}
	} else if((tmcc.segNum_b > tmcc.segNum_a) && (tmcc.segNum_b > tmcc.segNum_c)) {
		switch (tmcc.codeRate_b) {
		case DEMOD_CODERATE_DVBT_ISDBT_1_2:
			pTmccParams->layerBCodeRate = LX_DEMOD_CODE_1_2;
			break;

		case DEMOD_CODERATE_DVBT_ISDBT_2_3:
			pTmccParams->layerBCodeRate = LX_DEMOD_CODE_2_3;
			break;

		case DEMOD_CODERATE_DVBT_ISDBT_3_4:
			pTmccParams->layerBCodeRate = LX_DEMOD_CODE_3_4;
			break;

		case DEMOD_CODERATE_DVBT_ISDBT_5_6:
			pTmccParams->layerBCodeRate = LX_DEMOD_CODE_5_6;
			break;

		case DEMOD_CODERATE_DVBT_ISDBT_7_8:
			pTmccParams->layerBCodeRate = LX_DEMOD_CODE_7_8;
			break;

		default:
			pTmccParams->layerBCodeRate = LX_DEMOD_CODE_UNKNOWN;
			break;

		}

		switch (tmcc.qamMode_b) {
		case DEMOD_CONSTELLATION_DQPSK:
			pTmccParams->layerBQamMode = LX_DEMOD_DQPSK ;
			break;
		case DEMOD_CONSTELLATION_QPSK:
			pTmccParams->layerBQamMode = LX_DEMOD_QPSK;
			break;

		case DEMOD_CONSTELLATION_QAM16:
			pTmccParams->layerBQamMode = LX_DEMOD_16QAM;
			break;

		case DEMOD_CONSTELLATION_QAM64:
			pTmccParams->layerBQamMode = LX_DEMOD_64QAM;
			break;

		default:
			pTmccParams->layerBQamMode = LX_DEMOD_UNKOWN_MODE;
			break;
		}

	} else if((tmcc.segNum_c > tmcc.segNum_a) && (tmcc.segNum_c > tmcc.segNum_b)) {

		switch (tmcc.codeRate_c) {
		case DEMOD_CODERATE_DVBT_ISDBT_1_2:
			pTmccParams->layerCCodeRate = LX_DEMOD_CODE_1_2;
			break;

		case DEMOD_CODERATE_DVBT_ISDBT_2_3:
			pTmccParams->layerCCodeRate = LX_DEMOD_CODE_2_3;
			break;

		case DEMOD_CODERATE_DVBT_ISDBT_3_4:
			pTmccParams->layerCCodeRate = LX_DEMOD_CODE_3_4;
			break;

		case DEMOD_CODERATE_DVBT_ISDBT_5_6:
			pTmccParams->layerCCodeRate = LX_DEMOD_CODE_5_6;
			break;

		case DEMOD_CODERATE_DVBT_ISDBT_7_8:
			pTmccParams->layerCCodeRate = LX_DEMOD_CODE_7_8;
			break;

		default:
			pTmccParams->layerCCodeRate = LX_DEMOD_CODE_UNKNOWN;
			break;
		}


		switch (tmcc.qamMode_c) {
		case DEMOD_CONSTELLATION_DQPSK:
			pTmccParams->layerCQamMode = LX_DEMOD_DQPSK ;
			break;

		case DEMOD_CONSTELLATION_QPSK:
			pTmccParams->layerCQamMode = LX_DEMOD_QPSK;
			break;

		case DEMOD_CONSTELLATION_QAM16:
			pTmccParams->layerCQamMode = LX_DEMOD_16QAM;
			break;

		case DEMOD_CONSTELLATION_QAM64:
			pTmccParams->layerCQamMode = LX_DEMOD_64QAM;
			break;

		default:
			pTmccParams->layerCQamMode = LX_DEMOD_UNKOWN_MODE;
			break;
		}

	} else {
		pTmccParams->layerACodeRate = LX_DEMOD_CODE_UNKNOWN;
		pTmccParams->layerAQamMode = LX_DEMOD_UNKOWN_MODE;

		pTmccParams->layerBCodeRate = LX_DEMOD_CODE_UNKNOWN;
		pTmccParams->layerBQamMode = LX_DEMOD_UNKOWN_MODE;

		pTmccParams->layerCCodeRate = LX_DEMOD_CODE_UNKNOWN;
		pTmccParams->layerCQamMode = LX_DEMOD_UNKOWN_MODE;
	}
#if 0
	printk("pTmccParams->layerACodeRate=[%d]\n", pTmccParams->layerACodeRate);
	printk("pTmccParams->layerAQamMode=[%d]\n",pTmccParams->layerAQamMode );
	printk("pTmccParams->layerBCodeRate=[%d]\n", pTmccParams->layerBCodeRate);
	printk("pTmccParams->layerBQamMode=[%d]\n",pTmccParams->layerBQamMode );
	printk("pTmccParams->layerCCodeRate=[%d]\n", pTmccParams->layerCCodeRate);
	printk("pTmccParams->layerCQamMode=[%d]\n",pTmccParams->layerCQamMode );


	printk("pTmccParams->layerASegmentNum=[%d]\n",tmcc.segNum_a);
	printk("pTmccParams->layerBSegmentNum=[%d]\n", tmcc.segNum_b);
	printk("pTmccParams->layerCSegmentNum=[%d]\n",tmcc.segNum_c );
#endif

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_ISDBT_Get_TotalInfo
 * Get all information on ISDB-T for debug
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O22_ISDBT_Get_TotalInfo (void)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_ISDBT_Get_IFO_LOCK
 * Get IFO lock on ISDB-T.
 *
 * @param *pSnr [OUT] BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O22_ISDBT_Get_IFO_LOCK (BOOLEAN *pIfoLock)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_ISDBT_Get_CochanDetIndicator
 * Get co-channel detection indicator  on ISDB-T.
 *
 * @param *pDetStatus  [OUT] BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O22_ISDBT_Get_CochanDetIndicator (BOOLEAN *pDetStatus)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_ISDBT_MemoryBusCheck.
 * Check ISDB-T memory Bus.
 *
 * @param  NONE
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O22_ISDBT_MemoryBusCheck (void)
{
	UINT32 m1_prevW = 0x0;
	UINT32 m1_prevR = 0x0;
	UINT32 m1_currW = 0x0;
	UINT32 m1_currR = 0x0;

	DEMOD_PRINT("*********** %s ***********************	 \n", __F__);

	SYS_IO_ReadRegArray(0xC81014A0 , 4, &m1_prevW);
	SYS_IO_ReadRegArray(0xC81014A4 , 4, &m1_prevR);
	SYS_IO_ReadRegArray(0xC81014A8 , 4, &m1_currW);
	SYS_IO_ReadRegArray(0xC81014AC , 4, &m1_currR);

	DEMOD_PRINT("m1_prevW = 0x%x, m1_prevR = 0x%x \n",(int)m1_prevW,(int)m1_prevR);
	DEMOD_PRINT("m1_currW = 0x%x, m1_currR = 0x%x \n",(int)m1_currW,(int)m1_currR);

	if((m1_prevW == 0)&& (m1_prevR == 0) && (m1_currW == 0) && (m1_currR == 0))
	{
		DEMOD_ERROR("**********************************************************\n");
		DEMOD_ERROR("*********** M1 Bus DEAD **********************************\n");
		DEMOD_ERROR("**********  M1 Bus DEAD **********************************\n");
		DEMOD_ERROR("**********  M1 Bus DEAD **********************************\n");
		DEMOD_ERROR("**********************************************************\n");
	}

	return RET_OK;
}

int DEMOD_O22_ISDBT_Set_MemBus_flushing (void)
{
	UINT32 bus_gating;
	UINT32 bflush;
	UINT32 flush_end = 0x0;

	bus_gating = 0x0;
	SYS_IO_WriteRegArray(0xc830E540 , 4, &bus_gating);
	bflush = 0x1;
	SYS_IO_WriteRegArray(0xc830E548  , 4, &bflush);

	do {
		SYS_IO_ReadRegArray(0xc830E54C , 4,	&flush_end);
		flush_end = (flush_end)&0x00000001;
		DEMOD_WARN("Check flush_end = %d  \n", flush_end);
		if (flush_end) break;
	} while (1);

	bflush = 0x0;
	SYS_IO_WriteRegArray(0xc830E548  , 4, &bflush);

	bus_gating = 0x3;
	SYS_IO_WriteRegArray(0xc830E540 , 4, &bus_gating);


	return RET_OK;
}

#if 1
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_VSB_Set_DefaultRegisterValue.
 * Initialize GBB VSB module .
 *
 * @param  NONE [IN] void
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O22_VSB_Set_DefaultRegisterValue (void)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_VSB_Set_NeverLockWaitTime
 * Set neverlock waiting period.
 *
 * @param waitMs 	[IN] UINT32 - unit: ms
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O22_VSB_Set_NeverLockWaitTime (UINT32 waitMs)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_VSB_CochannelExist.
 * Get the informantion if co-channel(NTSC) signal exists or not on VSB mode.
 *
 * @param  *pCochannel [OUT] BOOLEAN - exists /doesn't exist.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O22_VSB_CochannelExist (BOOLEAN *pCochannel)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_VSB_PreMonitor.
 * Set registers against  various noise conditions before  monitoring.
 *
 * @param  NONE [IN] void .
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O22_VSB_PreMonitor (void)
{
	DEMOD_TRACE("start\n");

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_VSB_Monitor.
 * Monitoring
 *
 * @param  NONE [IN] void .
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O22_VSB_Monitor (DEMOD_CTX_T *pDemodInfo)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_VSB_Get_MSEdynStatus.
 * Get the flag whether MSE would be under operation limit (snr > 16dB : TRUE)
 *
 * @param  *pbEnable [OUT] BOOLEAN - get signal noise ratio
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O22_VSB_Get_MSEdynStatus (BOOLEAN *pbEnable)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_VSB_Get_TotalInfo
 * Get all information on VSB for debug
 *
 * @param NONE [IN].
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O22_VSB_Get_TotalInfo (void)
{
	return RET_OK;
}

#endif

int DEMOD_O22_VSB_SetDemod_Simple (void)
{
	LX_DEMOD_L2_Context *	pFrontend;

	UINT8			new_tuneMode = DEMOD_PROP_MODE_TUNE_NORMAL;
	UINT32			freq_Khz = 0;
	UINT16			ter_bandwidth_KHz = 6000;

	pFrontend = DEMOD_O22_GetContext();

	DEMOD_L2_ATSC_Set_demod(pFrontend,
				DEMOD_MODULATION_VSB,
				freq_Khz,
				new_tuneMode,
				DEMOD_PROP_MODE_SPECINVAUTO_MANUAL,
				DEMOD_PROP_MODE_SPECINV_NORMAL,
				ter_bandwidth_KHz,
				0, 0, 0, 0
				);

	return RET_OK;
}


#if 1
#endif

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_ATSC3_Get_GuradIntervalMode
 * Get the information of guard interval on ATSC3.
 *
 * @param *pGIMode 	[OUT] LX_DEMOD_GIMODE_T - 1/32, 1/16, 1/8 and 1/4.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_ATSC3_Get_GuradIntervalMode (LX_DEMOD_ATSC3_GIMODE_T *pGIMode)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("Start\n");

	pFrontend = DEMOD_O22_GetContext();

	*pGIMode = LX_DEMOD_GUARD_ATSC3_UNKNOWN;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}

	switch(signalStatus.guardInterval)
	{
		case DEMOD_ATSC3_PLP_INFO_L1B_SUB_GI_1_192:		*pGIMode = LX_DEMOD_GUARD_ATSC3_1_192; 		break;
		case DEMOD_ATSC3_PLP_INFO_L1B_SUB_GI_2_384: 	*pGIMode = LX_DEMOD_GUARD_ATSC3_2_384; 		break;
		case DEMOD_ATSC3_PLP_INFO_L1B_SUB_GI_3_512: 	*pGIMode = LX_DEMOD_GUARD_ATSC3_3_512; 		break;
		case DEMOD_ATSC3_PLP_INFO_L1B_SUB_GI_4_768: 	*pGIMode = LX_DEMOD_GUARD_ATSC3_4_768; 		break;
		case DEMOD_ATSC3_PLP_INFO_L1B_SUB_GI_5_1024:	*pGIMode = LX_DEMOD_GUARD_ATSC3_5_1024; 	break;
		case DEMOD_ATSC3_PLP_INFO_L1B_SUB_GI_6_1536: 	*pGIMode = LX_DEMOD_GUARD_ATSC3_6_1536; 	break;
		case DEMOD_ATSC3_PLP_INFO_L1B_SUB_GI_7_2048: 	*pGIMode = LX_DEMOD_GUARD_ATSC3_7_2048; 	break;
		case DEMOD_ATSC3_PLP_INFO_L1B_SUB_GI_8_2432: 	*pGIMode = LX_DEMOD_GUARD_ATSC3_8_2432; 	break;
		case DEMOD_ATSC3_PLP_INFO_L1B_SUB_GI_9_3072: 	*pGIMode = LX_DEMOD_GUARD_ATSC3_9_3072; 	break;
		case DEMOD_ATSC3_PLP_INFO_L1B_SUB_GI_10_3648: 	*pGIMode = LX_DEMOD_GUARD_ATSC3_10_368; 	break;
		case DEMOD_ATSC3_PLP_INFO_L1B_SUB_GI_11_4096: 	*pGIMode = LX_DEMOD_GUARD_ATSC3_11_4096; 	break;
		case DEMOD_ATSC3_PLP_INFO_L1B_SUB_GI_12_4864: 	*pGIMode = LX_DEMOD_GUARD_ATSC3_12_4864; 	break;
		default:										*pGIMode = LX_DEMOD_GUARD_ATSC3_UNKNOWN; 	break;

	}

	return RET_OK;
}


int DEMOD_O22_ATSC3_Get_FFTMode (LX_DEMOD_FFTMODE_T *pFftMode)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("Start\n");

	pFrontend = DEMOD_O22_GetContext();

	*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}

	switch(signalStatus.fftMode)
	{
		case DEMOD_ATSC3_PLP_INFO_SUBFRAME_FFT_SIZE_8K:
			*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_8K;
			break;

		case DEMOD_ATSC3_PLP_INFO_SUBFRAME_FFT_SIZE_16K:
			*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_16K;
			break;

		case DEMOD_ATSC3_PLP_INFO_SUBFRAME_FFT_SIZE_32K:
			*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_32K;
			break;

		default:
			*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN;
			break;
	}
	return RET_OK;
}


int DEMOD_O22_ATSC3_Get_CodeRate (LX_DEMOD_ATSC3_CODERATE_T *pCodeRate)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("Start\n");

	pFrontend = DEMOD_O22_GetContext();

	*pCodeRate = LX_DEMOD_ATSC3_CODE_UNKNOWN;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}

	switch(signalStatus.codeRate)
	{
		case DEMOD_CODERATE_ATSC3_2_15:		*pCodeRate = LX_DEMOD_ATSC3_CODE_2_15;		break;
		case DEMOD_CODERATE_ATSC3_3_15:		*pCodeRate = LX_DEMOD_ATSC3_CODE_3_15;		break;
		case DEMOD_CODERATE_ATSC3_4_15:		*pCodeRate = LX_DEMOD_ATSC3_CODE_4_15;		break;
		case DEMOD_CODERATE_ATSC3_5_15:		*pCodeRate = LX_DEMOD_ATSC3_CODE_5_15;		break;
		case DEMOD_CODERATE_ATSC3_6_15:		*pCodeRate = LX_DEMOD_ATSC3_CODE_6_15;		break;
		case DEMOD_CODERATE_ATSC3_7_15:		*pCodeRate = LX_DEMOD_ATSC3_CODE_7_15;		break;
		case DEMOD_CODERATE_ATSC3_8_15:		*pCodeRate = LX_DEMOD_ATSC3_CODE_8_15;		break;
		case DEMOD_CODERATE_ATSC3_9_15:		*pCodeRate = LX_DEMOD_ATSC3_CODE_9_15;		break;
		case DEMOD_CODERATE_ATSC3_10_15:	*pCodeRate = LX_DEMOD_ATSC3_CODE_10_15; 	break;
		case DEMOD_CODERATE_ATSC3_11_15:	*pCodeRate = LX_DEMOD_ATSC3_CODE_11_15; 	break;
		case DEMOD_CODERATE_ATSC3_12_15:	*pCodeRate = LX_DEMOD_ATSC3_CODE_12_15; 	break;
		case DEMOD_CODERATE_ATSC3_13_15:	*pCodeRate = LX_DEMOD_ATSC3_CODE_13_15; 	break;
		default:							*pCodeRate = LX_DEMOD_ATSC3_CODE_UNKNOWN;	break;

	}
	return RET_OK;

}


int DEMOD_O22_ATSC3_Get_Constellation (LX_DEMOD_ATSC3_CONSTELLATION_T *pConstellation)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("Start\n");

	pFrontend = DEMOD_O22_GetContext();

	*pConstellation = LX_DEMOD_CONST_ATSC3_UNKNOWN;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}

	switch(signalStatus.constellation)
	{
		case DEMOD_ATSC3_PLP_INFO_PLP_MOD_QPSK		  : *pConstellation = LX_DEMOD_CONST_ATSC3_QPSK;		break;
		case DEMOD_ATSC3_PLP_INFO_PLP_MOD_16QAM_NUC   : *pConstellation = LX_DEMOD_CONST_ATSC3_QAM_16;		break;
		case DEMOD_ATSC3_PLP_INFO_PLP_MOD_64QAM_NUC   : *pConstellation = LX_DEMOD_CONST_ATSC3_QAM_64;		break;
		case DEMOD_ATSC3_PLP_INFO_PLP_MOD_256QAM_NUC  : *pConstellation = LX_DEMOD_CONST_ATSC3_QAM_256; 	break;
		case DEMOD_ATSC3_PLP_INFO_PLP_MOD_1024QAM_NUC : *pConstellation = LX_DEMOD_CONST_ATSC3_QAM_1024;	break;
		case DEMOD_ATSC3_PLP_INFO_PLP_MOD_4096QAM_NUC : *pConstellation = LX_DEMOD_CONST_ATSC3_QAM_4096;	break;
		default  :										*pConstellation = LX_DEMOD_CONST_ATSC3_UNKNOWN; 	break;
	}
	return RET_OK;

}




int _DEMOD_O22_ATSC3_CheckSignalState (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	pFrontend = DEMOD_O22_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}

	pDemodInfo->signalStatus.operMode		= signalStatus.operatingMode;
	pDemodInfo->signalStatus.agc			= signalStatus.if_agc;
	pDemodInfo->signalStatus.m.mse			= signalStatus.mse_info_eq;
	pDemodInfo->signalStatus.ber			= signalStatus.ber;
	pDemodInfo->signalStatus.packetError	= signalStatus.packetError;
	pDemodInfo->signalStatus.unSNR			= signalStatus.snr_eq;
	pDemodInfo->freqOffset 					= signalStatus.offsetFrq_Hz / 1000;
	pDemodInfo->signalStatus.sigQ			= signalStatus.signalQuality;
	pDemodInfo->signalStatus.rfMode			= pDemodInfo->systemMode;

	DEMOD_PRINT("[op_mode       : %d]\n",	signalStatus.operatingMode);
	DEMOD_PRINT("[if_agc        : %d]\n",	signalStatus.if_agc);
	DEMOD_PRINT("[mse_info      : %d]\n",	signalStatus.mse_info_eq);
	DEMOD_PRINT("[snr           : %d]\n",	signalStatus.snr_eq);
	DEMOD_PRINT("[dl            : %d]\n",	signalStatus.demodLock);
	DEMOD_PRINT("[ber           : %u]\n",	signalStatus.ber / 10000000);
	DEMOD_PRINT("[packet error  : %d]\n",	signalStatus.packetError);
	DEMOD_PRINT("[afc_Khz       : %d]\n",	signalStatus.offsetFrq_Hz / 1000);
	DEMOD_PRINT("[constellation : %d]\n",	signalStatus.constellation);
	DEMOD_PRINT("[sp_inv        : %d]\n",	signalStatus.spInv);
	DEMOD_PRINT("[num_plp       : %d]\n",	signalStatus.num_PLP);
	DEMOD_PRINT("[code_rate     : %d]\n",	signalStatus.codeRate);
	DEMOD_PRINT("[fft_mode      : %d]\n",	signalStatus.fftMode);
	DEMOD_PRINT("[guard_int     : %d]\n",	signalStatus.guardInterval);
	DEMOD_PRINT("[signalQuality : %d]\n",	signalStatus.signalQuality);

	if (signalStatus.packetError > 0) {
		DEMOD_NOTI("packet error occured, agc %d, mse %u, snr %d, pe %d %d %d %d\n", signalStatus.if_agc, signalStatus.mse_info_eq, signalStatus.snr_eq, signalStatus.plp_pkerr_0, signalStatus.plp_pkerr_1, signalStatus.plp_pkerr_2, signalStatus.plp_pkerr_3);
	}

	return RET_OK;

}


int _DEMOD_O22_ATSC3_CheckTuneMode (DEMOD_CTX_T *pDemodInfo)
{
	UINT8  new_tuneMode;

	switch (pDemodInfo->setCfgParam.atsc3.tuneMode)
	{
		case	LX_DEMOD_TUNE_NORMAL:		new_tuneMode = DEMOD_PROP_MODE_TUNE_NORMAL; break;
		default:							new_tuneMode = DEMOD_PROP_MODE_TUNE_AUTO; break;
	}

	return new_tuneMode;
}


int DEMOD_O22_ATSC3_SetDemodExpand (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_L2_Context * 	pFrontend;

	//UINT8  			standard = 		DEMOD_MODULATION_ATSC3;
	UINT32 			freq_Khz = 		0;
	UINT16 			atsc3_bandwidth_Khz = 	6000;
	UINT8  			tuneMode = 		DEMOD_PROP_MODE_TUNE_AUTO;
	UINT8           plpID[4];
	

	pFrontend = DEMOD_O22_GetContext();

	tuneMode = _DEMOD_O22_ATSC3_CheckTuneMode(pDemodInfo);


	plpID[0] = pDemodInfo->setCfgParam.atsc3.plpData[0];
	plpID[1] = pDemodInfo->setCfgParam.atsc3.plpData[1];
	plpID[2] = pDemodInfo->setCfgParam.atsc3.plpData[2];
	plpID[3] = pDemodInfo->setCfgParam.atsc3.plpData[3];
	
    if(tuneMode == DEMOD_PROP_MODE_TUNE_NORMAL)
	{	
		if (((plpID[0] == 0x40) && (plpID[1] == 0x40) && (plpID[2] == 0x40) && (plpID[3] == 0x40)) || \
			((plpID[0] == 0) && (plpID[1] == 0) && (plpID[2] == 0) && (plpID[3] == 0)))
		{
			plpID[0] = _ATSC3_PLP_AUTO_DETECT;
			plpID[1] = 0x40;
			plpID[2] = 0x40;
			plpID[3] = 0x40;
			DEMOD_PRINT("set plpID[0] = 0x%X because this channel's plpID was not deteced and stored\n", plpID[0]);
		}
    }
	else
	{
		plpID[0] = _ATSC3_PLP_AUTO_DETECT;
		plpID[1] = 0x40;
		plpID[2] = 0x40;
		plpID[3] = 0x40;
		
		DEMOD_PRINT("set Demod for Auto Tuning plpID[0] = 0x%X\n", plpID[0]);
	}		

	DEMOD_L2_ATSC_Set_demod(pFrontend,
							DEMOD_MODULATION_ATSC3,
							freq_Khz,
							tuneMode,
							DEMOD_PROP_MODE_SPECINVAUTO_MANUAL,
							DEMOD_PROP_MODE_SPECINV_NORMAL,
							atsc3_bandwidth_Khz,
							plpID[0],
							plpID[1],
							plpID[2],
							plpID[3]
							);


	return RET_OK;
}



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_ATSC3_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O22_ATSC3_Obtaining_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{

	static LX_DEMOD_FLAG_T 		scanProcessing = LX_DEMOD_FLAG_START;
	static LX_DEMOD_LOCK_STATE_T 	scanLock = LX_DEMOD_UNLOCKED;
	static unsigned int 		sigStablestartTime;

	switch (pDemodInfo->controlState)
	{
		/*********************************************************/
		/***** Configure demod for tune start.               *****/
		/*********************************************************/
		case LX_DEMOD_TUNE_START:
			{
				#if 1
				//printk("\n/******Obtaining*****ATSC3 LX_DEMOD_TUNE_START ******************************/\n");
				printk("check  setCfgParam.atsc3.tuneMode[%d]\n",pDemodInfo->setCfgParam.atsc3.tuneMode);
				printk("check  setCfgParam.atsc3.bSpectrumInv[%d]\n",pDemodInfo->setCfgParam.atsc3.bSpectrumInv );
				printk("check  systemMode[%d][20210527]\n",pDemodInfo->systemMode );
				#endif

				if(RET_OK != DEMOD_O22_ATSC3_SetDemodExpand(pDemodInfo))
				{
					DEMOD_ERROR("Fail, DEMOD_O22_VSB_SetDemod()\n");
					return RET_ERROR;
				}

				if(LX_DEMOD_TUNE_NORMAL != pDemodInfo->setCfgParam.atsc3.tuneMode)
				{
					if(RET_OK != DEMOD_O22_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_ON, &scanProcessing, &scanLock))
					{
						DEMOD_ERROR("Fail, DEMOD_O22_NeverlockScan()\n");
						return RET_ERROR;
					}
					pDemodInfo->controlState = LX_DEMOD_TUNE_SCAN;
					DEMOD_PRINT("LX_DEMOD_TUNE_START : Going to LX_DEMOD_TUNE_SCAN..... ^0^\n");
				}
				else
				{
/*				
					if (RET_OK != DEMOD_O22_TPOutEnable(TRUE))
					{
						DEMOD_ERROR("Fail, DEMOD_O22_TPOutEnable()\n");
						return RET_ERROR;
					}
*/
					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState = LX_DEMOD_SIGNAL_STABLE;
					DEMOD_PRINT("LX_DEMOD_TUNE_START : Going to LX_DEMOD_SIGNAL_STABLE for SYNC CHECK DIRECTLY... ^0^\n");
				}
			}
			break;

		/*********************************************************/
		/***** Configure demod for scan mode.                *****/
		/*********************************************************/
		case LX_DEMOD_TUNE_SCAN:
			{
				unsigned int currentTime = 0;
				unsigned int elapsedTime = 0;

				if((LX_DEMOD_FLAG_COMPLETE == pDemodInfo->scanJobFlag) || (LX_DEMOD_FLAG_FINISH == pDemodInfo->scanJobFlag))
				{
					pDemodInfo->controlState = LX_DEMOD_SIGNAL_STABLE;

					DEMOD_PRINT("Already Done\n");
					DEMOD_PRINT("LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
					return RET_OK;
				}

				if(RET_OK != DEMOD_O22_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_OFF, &scanProcessing, &scanLock))
				{
					DEMOD_ERROR("Fail, DEMOD_O22_NeverlockScan()\n");
					return RET_ERROR;
				}

				if((LX_DEMOD_FLAG_FINISH == scanProcessing) && (LX_DEMOD_LOCKED == scanLock))
				{
					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState = LX_DEMOD_SIGNAL_STABLE;

					DEMOD_PRINT("Signal is Found\n");
					DEMOD_NOTI("SCANNING FIRST LOCK! : Going to LX_DEMOD_SIGNAL_STABLE..... ^0^\n");
				}
				else if((LX_DEMOD_FLAG_FINISH == scanProcessing)&& (LX_DEMOD_UNLOCKED == scanLock))
				{
					pDemodInfo->scanJobFlag 	= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->bNotifiedUnlock	= TRUE;
					pDemodInfo->bNotifiedLock	= FALSE;
					pDemodInfo->lockStatus 		= LX_DEMOD_UNLOCKED;
					pDemodInfo->signalStatus.bSignalValid = FALSE;

					pDemodInfo->controlState 	= LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK;

					currentTime = jiffies_to_msecs(jiffies);
					elapsedTime = currentTime - g_RetuneStartTime;

					DEMOD_NOTI("LX_DEMOD_TUNE_SCAN : MSG_ATS3C_FRONT_END_NOT_LOCKED..\n") ;
					DEMOD_NOTI("LX_DEMOD_TUNE_SCAN : Elapse time is %d msec\n", elapsedTime) ;

					DEMOD_PRINT("Signal is NOT Found\n");
				}
				else
				{
					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_ING;
//					DEMOD_PRINT("Detection is on processing\n");
				}
			}
			break;

		/*********************************************************/
		/***** Attempting to finish the tuning state machine *****/
		/*********************************************************/
		case LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK :
			{


			}
			break;

		/*********************************************************/
		/***** Attempting to obtain synch lock               *****/
		/*********************************************************/
		case LX_DEMOD_SYNC_CHECKING :
			{
				LX_DEMOD_LOCK_STATE_T			lockState;

				if(RET_OK != DEMOD_O22_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
				{
					DEMOD_ERROR("Fail, DEMOD_O22_Get_Lock()\n");
					return RET_ERROR;
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					pDemodInfo->controlState	= LX_DEMOD_SIGNAL_STABLE;
					sigStablestartTime = jiffies_to_msecs(jiffies);
					DEMOD_PRINT("LX_DEMOD_SYNC_CHECKING : Going to LX_DEMOD_SIGNAL_STABLE..... ^0^\n");
				}
				else
				{
					if(RET_OK != DEMOD_O22_Get_Lock(LX_DEMOD_CARR_LOCK, &lockState))
					{
						DEMOD_ERROR("Fail, DEMOD_O22_Get_Lock()\n");
						return RET_ERROR;
					}

					if(LX_DEMOD_LOCKED == lockState)
					{
						DEMOD_PRINT("LX_DEMOD_SYNC_CHECKING : catch only carrier lock..... ^0^\n");
						notifyinglockTimeOut = LX_DEMOD_LOCK_DEALY_2000 + LX_DEMOD_LOCK_DEALY_800;
						/* extending max delay */
					}
					else
					{
						/* nothing to do so far */
					}
				}
			}
		   break;

	   	/*********************************************************/
	   	/***** Attempting to obtain signal stability         *****/
		/*********************************************************/
	   	case LX_DEMOD_SIGNAL_STABLE:
			{
				LX_DEMOD_LOCK_STATE_T		lockState;
				SINT32				freqOffset=0;
				unsigned int 			elapsedTime;
				UINT32 				packetError;

//				printk("\n/******LX_DEMOD_SIGNAL_STABLE1  *****ATSC3 LX_DEMOD_SIGNAL_STABLE ******************************/\n");

				if(RET_OK != DEMOD_O22_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
				{
					DEMOD_ERROR("Fail, DEMOD_O22_Get_Lock()\n");
					return RET_ERROR;
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					if (LX_DEMOD_TUNE_NORMAL == pDemodInfo->setCfgParam.atsc3.tuneMode)
					{
						elapsedTime = jiffies_to_msecs(jiffies) - sigStablestartTime;

						if(RET_OK != DEMOD_O22_Get_Packet_Error(&packetError))
						{
							DEMOD_ERROR("Fail, DEMOD_O22_Get_Packet_Error()\n");
							return RET_ERROR;
						}
						else
						{
							pDemodInfo->bNotifiedLock	= TRUE;
							pDemodInfo->bNotifiedUnlock	= FALSE;
							pDemodInfo->lockStatus		= LX_DEMOD_LOCKED;
							pDemodInfo->signalStatus.bSignalValid = TRUE;

							pDemodInfo->controlState	= LX_DEMOD_SIGNAL_LOCKED;

							elapsedTime = jiffies_to_msecs(jiffies) - g_RetuneStartTime;

							DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : MSG_ATSC3_FRONT_END_LOCKED..... ^^^0^^^\n");
							DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^^^0^^^\n", elapsedTime);

							if (RET_OK != DEMOD_O22_TPOutEnable(TRUE))
							{
								DEMOD_ERROR("Fail, DEMOD_O22_TPOutEnable()\n");
								return RET_ERROR;
							}

							if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
							{
								DEMOD_ERROR("Fail, DEMOD_Get_TunedCFG()\n");
								return RET_ERROR;
							}

							if (RET_OK != _DEMOD_O22_ATSC3_CheckSignalState(pDemodInfo))
							{
								DEMOD_ERROR("Fail, _DEMOD_O22_VSB_CheckSignalState()\n");
								return RET_ERROR;
							}
						}
					}
					else
					{
						pDemodInfo->bNotifiedLock	= TRUE;
						pDemodInfo->bNotifiedUnlock = FALSE;
						pDemodInfo->lockStatus		= LX_DEMOD_LOCKED;
						pDemodInfo->signalStatus.bSignalValid = TRUE;

						if (RET_OK != DEMOD_O22_Get_CarrierFreqOffset(&freqOffset))
						{
							DEMOD_ERROR("Fail, DEMOD_O22_Get_CarrierFreqOffset()\n");
							return RET_ERROR;
						}
						pDemodInfo->freqOffset = freqOffset;

						pDemodInfo->controlState	= LX_DEMOD_SIGNAL_LOCKED;

						elapsedTime = jiffies_to_msecs(jiffies) - g_RetuneStartTime;

						DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : MSG_ATSC3_FRONT_END_LOCKED..... ^0^\n");
						DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^0^\n", elapsedTime);
						DEMOD_PRINT("LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^0^\n", freqOffset);

						if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
						{
							DEMOD_ERROR("Fail, DEMOD_Get_TunedCFG()\n");
							return RET_ERROR;
						}
						if (RET_OK != _DEMOD_O22_ATSC3_CheckSignalState(pDemodInfo))
						{
							DEMOD_ERROR("Fail, _DEMOD_O22_VSB_CheckSignalState()\n");
							return RET_ERROR;
						}
					}
				}
	   		}
			break;

		case LX_DEMOD_SIGNAL_LOCKED:	break;

		default: pDemodInfo->controlState = LX_DEMOD_TUNE_START; break;
	}

	return RET_OK;
}


/**
 * DEMOD_O22_ATSC3_Monitoring_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_O22_ATSC3_Monitoring_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_LOCK_STATE_T			lockState;

	if(RET_OK != DEMOD_O22_Get_Lock(LX_DEMOD_FEC_LOCK, &lockState))
	{
		DEMOD_ERROR("Fail, DEMOD_O22_Get_Lock()\n");
		return RET_ERROR;
	}
#if 0
	DEMOD_PRINT("pDemodInfo->lockStatus = %d, pDemodInfo->bNotifiedLock = %d, (lockCount = %d) \n",pDemodInfo->lockStatus,pDemodInfo->bNotifiedLock,pDemodInfo->lockCount);
	DEMOD_PRINT("pDemodInfo->lockStatus = %d, pDemodInfo->bNotifiedUnlock = %d,(unlockCnt = %d) \n",pDemodInfo->lockStatus,pDemodInfo->bNotifiedUnlock,pDemodInfo->unLockCount);
	DEMOD_PRINT("lockState = %d) \n",lockState);
#endif
	if(LX_DEMOD_LOCKED == lockState)
	{
		pDemodInfo->unLockCount = 0;
		pDemodInfo->unLockLongCount = 0;


//		if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
//			pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;


		if (RET_OK != _DEMOD_O22_ATSC3_CheckSignalState(pDemodInfo))
		{
			DEMOD_ERROR("Fail, _DEMOD_O22_ATSC3_CheckSignalState()\n");
			return RET_ERROR;
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

			DEMOD_NOTI("MSG_ATSC3_FRONT_END_LOCKED..... ^0^\n");

			if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
				pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;

		}
		if(pDemodInfo->lockCount >= 2)
		{
			pDemodInfo->lockCount = 0;
		}

		if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
		{
			DEMOD_ERROR("Fail, DEMOD_Get_TunedCFG()\n");
			return RET_ERROR;
		}
	}
	else
	{
		pDemodInfo->lockCount = 0;
		_VQI_Full_Pkerr_Count = 0;

		if(pauseTimeDemod != LX_DEMOD_LOCK_FAIL_PAUSE_TIME )
			pauseTimeDemod = LX_DEMOD_LOCK_FAIL_PAUSE_TIME;

		if((LX_DEMOD_UNLOCKED != pDemodInfo->lockStatus)  && (TRUE != pDemodInfo->bNotifiedUnlock))
		{
			pDemodInfo->unLockCount++;

			if(pDemodInfo->unLockCount == _ATSC3_Unlock_Count_Threshold)
			{
				pDemodInfo->lockStatus 		= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedLock	= FALSE;
				pDemodInfo->bNotifiedUnlock = TRUE;
				pDemodInfo->signalStatus.bSignalValid = FALSE;

				DEMOD_NOTI("MSG_ATSC3_FRONT_END_NOT_LOCKED..... -_-\n");

			}
			if(pDemodInfo->unLockCount >= 4)
			{
				pDemodInfo->unLockCount = 0;
			}
		}
	}

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_O22_ATSC3_Set_PLP
 * Set PLP on ATSC3.
 *
 * @param 
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_ATSC3_Set_PLP (LX_DEMOD_ATSC3_CONFIG_T *pAtsc3ConfigParam)
{
	LX_DEMOD_L2_Context *	pFrontend;

	//pAtsc3ConfigParam->plpData[0] = 0x00;   //temp
	DEMOD_PRINT("Start\n");

	pFrontend = DEMOD_O22_GetContext();

	//pFrontend->demod->cmd->atsc3_plp_select.plp_id_sel_mode = DEMOD_DD_ATSC3_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MANUAL;
	DEMOD_L2_ATSC_Set_PLP_Select (pFrontend, pAtsc3ConfigParam->plpData[0], pAtsc3ConfigParam->plpData[1], pAtsc3ConfigParam->plpData[2], pAtsc3ConfigParam->plpData[3]);

	return RET_OK;

}


/**
 * DEMOD_O22_ATSC3_Set_PLP
 * Set PLP on ATSC3.
 *
 * @param 
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_O22_ATSC3_Change_PLP (UINT8 unPLP)
{
	LX_DEMOD_L2_Context *	pFrontend;

	DEMOD_PRINT("Start\n");

	pFrontend = DEMOD_O22_GetContext();

	printk("############chungiii DEMOD_O22_ATSC3_Change_PLP[%d] \n", unPLP);
	if (RET_OK != DEMOD_L2_ATSC_Set_PLP_Select(pFrontend, unPLP, 0x40, 0x40, 0x40))
	{
		DEMOD_ERROR("Fail, DEMOD_O22_ATSC3_Change_PLP\n");
		return RET_ERROR;
	}

	
	

	return RET_OK;

}



int DEMOD_O22_ATSC3_Get_MPLP_Info (LX_DEMOD_ATSC3_MULTI_PLP_ID_T *pAtsc3mPLPInfo, LX_DEMOD_ATSC3_MULTI_PLP_ID_SEL_T plpSel)
{

	UINT8	index;
	
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_MULTI_PLP_ID_T pPlpParams;
	
	memset(&pPlpParams, 0, sizeof(pPlpParams));
	DEMOD_PRINT("Start\n");

	pFrontend = DEMOD_O22_GetContext();

	if (RET_OK != DEMOD_L2_ATSC_Get_PLP_ID(pFrontend, &pPlpParams, plpSel))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_ATSC_Get_PLP_ID\n");
		return RET_ERROR;
	}

	for (index = 0; index <64; index++)
	{
		pAtsc3mPLPInfo->plpDataID[index] = pPlpParams.plpID[index];		
	}

	pAtsc3mPLPInfo->plpDatacount = pPlpParams.plpCount;
	pAtsc3mPLPInfo->plpTotalCount = pPlpParams.plpTotalCount;
	memcpy(pAtsc3mPLPInfo->plpDataID, pPlpParams.plpID, 64);
	
	return RET_OK;

}

int DEMOD_O22_ATSC3_Set_MemSconfig (void)
{
	LX_DEMOD_L2_Context *	pFrontend;

	UINT32			st_mem = gMemCfgDEMOD_ATSC3.memory_base;

	pFrontend = DEMOD_O22_GetContext();

	if(st_mem == 0)
	{
		DEMOD_WARN("Wrong Memory Base Address\n");
	}
	else
	{
		DEMOD_INFO("st_mem[0x%x] \n", st_mem);

		//TO DO 
		if(RET_OK != DEMOD_L2_ATSC3_Set_BaseAddr_AXI(pFrontend, st_mem))
		{
			DEMOD_ERROR("Fail, DEMOD_L2_ATSC3_Set_BaseAddr_AXI()\n");
			return RET_ERROR;
		}
	}

	return RET_OK;


}

