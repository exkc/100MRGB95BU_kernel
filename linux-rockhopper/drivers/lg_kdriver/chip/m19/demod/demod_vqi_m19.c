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
//#include "demod_reg_m19.h"
#include "demod_common_m19.h"
#include "demod_vqi_m19.h"

#if 0
#endif


/***********************************************************************************
	Global Type Definitions
 ************************************************************************************/

extern LX_DEMOD_L2_Context gM19_LGDBB_Frontend;

extern UINT8 gM19GBB_PowerOnInit;
unsigned int gM19GBB_PowerOnInitStartTimeISDBT = 0;


/***********************************************************************************
	Static Variable & Function Prototypes Declarations
 ************************************************************************************/
UINT16	_gM19GBB_VQI_UnlockCount_full_packeterr = 0;
UINT16 	_gM19GBB_FullVQIPkerrCount = 7;
UINT16 	_gM19GBB_FullVQPkerrThreshold = 300;
UINT16 	_gM19GBB_FullISDBTPkerrThreshold = 200;

BOOLEAN _gM19GBB_ISDBT_Mem_set = FALSE;


static int _DEMOD_M19_LGDBB_VSB_CheckSignalState(DEMOD_CTX_T *pDemodInfo);


/******************************************************************************
	Global Variables & Function Prototypes Declarations
******************************************************************************/
extern	int 	SYS_IO_ReadRegArray(UINT32 addr, UINT32 size, void *data);
extern	int 	SYS_IO_WriteRegArray(UINT32 addr, UINT32 size, const void *data);



#if 0
#endif


int DEMOD_M19_ATSC_SW_Init(void)
{
	LX_DEMOD_L2_Context *pFrontend;

	pFrontend = &gM19_LGDBB_Frontend;
	g_demod_ctx_info[0].bSetParams   = FALSE;

	//if(DEMOD_L2_ATSC_SW_Init(pFrontend, 0x26) != NO_DEMOD_ERROR)  // CPBOX
	if(DEMOD_L2_ATSC_SW_Init(pFrontend, 0xb2) != NO_DEMOD_ERROR)    // SOC
	{
		printk("[M19 LGDBB] (%s:%d) DEMOD_L2_ATSC_SW_Init  Fail!! \n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}

	//printk("##########check chungiii[0720] DEMOD_L2_ATSC_SW_Init\n");

	return RET_OK;
}



int _DEMOD_M19_LGDBB_VSB_CheckSignalState(DEMOD_CTX_T *pDemodInfo)
{

	LX_DEMOD_L2_Context *pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

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
	printk("[[M19P] packet error : %d]\n"			, signalStatus.packetError);
	#endif


	pDemodInfo->signalStatus.packetError 	= signalStatus.packetError;
	pDemodInfo->signalStatus.ber			= signalStatus.ber;
	pDemodInfo->signalStatus.agc			= signalStatus.if_agc;
	pDemodInfo->signalStatus.m.mse			= signalStatus.mse_info;
	pDemodInfo->signalStatus.m.constPwr		= signalStatus.constPwr;
	pDemodInfo->freqOffset 					= signalStatus.offsetFrq_Hz;

	pDemodInfo->signalStatus.operMode 	= pDemodInfo->operMode;
	pDemodInfo->signalStatus.rfMode	= pDemodInfo->systemMode;

	return RET_OK;

}


int _DEMOD_M19_VSB_CheckTuneMode(DEMOD_CTX_T *pDemodInfo)
{
	UINT8  new_tuneMode;

	switch (pDemodInfo->setCfgParam.vsb.tuneMode)
	{
		case	LX_DEMOD_TUNE_NORMAL:		new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_NORMAL; break;
		case	LX_DEMOD_TUNE_AUTO: 			new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_AUTO; break;
		case	LX_DEMOD_TUNE_MANUAL: 		new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_MANUAL ; break;
	//	case	TU_TUNE_SPEC_DVBC_FIXED_DATA:		new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_FIXED_DATA; break;

		default:						return DEMOD_DD_MODE_PROP_TUNEMODE_AUTO; break;
	}

	return new_tuneMode;
}



int DEMOD_M19_LGDBB_VSB_SetDemod(DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_L2_Context 	*pFrontend;
	UINT8	new_tuneMode;
	UINT32 	freq_Khz;
	UINT16 	ter_bandwidth_KHz;

	pFrontend		= &gM19_LGDBB_Frontend;

	freq_Khz = 0;

	//printk("[M19 LGDBB][0716] ################### chungiii SetDemod VSB \n");

	new_tuneMode = _DEMOD_M19_VSB_CheckTuneMode(pDemodInfo);

	if(RET_OK != DEMOD_M19_Get_BW(pDemodInfo, &ter_bandwidth_KHz))
	{
		DEMOD_PRINT("[DEMOD M19 DBB] FAIL (%s:%d) DEMOD_M19_Get_BW !!!\n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}
	 //printk("[M19 LGDBB] ################### chungiii SetDemod VSB check ter_bandwidth_KHz[%d] \n", ter_bandwidth_KHz);

		DEMOD_L2_ATSC_Set_demod(pFrontend,
							DEMOD_DD_MODE_PROP_MODULATION_VSB,
							freq_Khz,
							new_tuneMode,
							DEMOD_DD_MODE_PROP_SPECINV_MANUAL,
							DEMOD_DD_MODE_PROP_SPECINV_NORMAL,
							ter_bandwidth_KHz,
							0
							);

	return RET_OK;

}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_VSB_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_M19_VSB_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{

	static LX_DEMOD_FLAG_T 			scanProcessing = LX_DEMOD_FLAG_START;
	static LX_DEMOD_LOCK_STATE_T 	scanLock = LX_DEMOD_UNLOCKED;
	static unsigned int 			sigStablestartTime;


	switch (pDemodInfo->controlState)
	{
											/***************************************************/
											/***** Configure demod for tune start. *****/
		case LX_DEMOD_TUNE_START:			/***************************************************/
			{

				#if 0
				printk("\n/**********************************************************/\n");
				printk("check  setCfgParam.vsb.tuneMode[%d]\n",pDemodInfo->setCfgParam.vsb.tuneMode);
				printk("check  setCfgParam.vsb.channelBW[%d]\n",pDemodInfo->setCfgParam.vsb.channelBW );
				printk("check  setCfgParam.vsb.bSpectrumInv[%d]\n",pDemodInfo->setCfgParam.vsb.bSpectrumInv );
				printk("check  systemMode[%d]\n",pDemodInfo->systemMode );
				#endif



				if(RET_OK != DEMOD_M19_LGDBB_VSB_SetDemod(pDemodInfo))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD M19 LGDBB] FAIL (%s:%d) DEMOD_M19_LGDBB_VSB_SetDemod() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_TUNE_NORMAL != pDemodInfo->setCfgParam.vsb.tuneMode)
				{
					if(RET_OK != DEMOD_M19_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_ON, &scanProcessing, &scanLock))
					{
						DEMOD_PRINT("[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_M14B0_NeverlockScan() !!!\n", __F__, __L__);
						DEMOD_RETURN_FAIL(__F__);
					}
					pDemodInfo->controlState = LX_DEMOD_TUNE_SCAN;
					DEMOD_PRINT( "^R^[DEMOD M14B0 GBB] LX_DEMOD_TUNE_START : Going to LX_DEMOD_TUNE_SCAN..... ^0^\n");

				}
				else
				{
					if (RET_OK != DEMOD_M19_TPOutEnable(TRUE))
					{
						DEMOD_PRINT( "^r^[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_M19_TPOutEnable(FALSE) !!!\n", __F__, __L__);
						DEMOD_RETURN_FAIL(__F__);
					}

					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState = LX_DEMOD_SIGNAL_STABLE;
					DEMOD_PRINT( "^R^[DEMOD M19 GBB] LX_DEMOD_TUNE_START : Going to LX_DEMOD_SIGNAL_STABLE for SYNC CHECK DIRECTLY... ^0^\n");
				}

			}

			break;

											/***************************************************/
											/***** Configure demod for scan mode. *****/
		case LX_DEMOD_TUNE_SCAN:			/***************************************************/
			{

				unsigned int currentTime = 0;
				unsigned int elapsedTime = 0;

				if((LX_DEMOD_FLAG_COMPLETE == pDemodInfo->scanJobFlag) || (LX_DEMOD_FLAG_FINISH == pDemodInfo->scanJobFlag))
				{

					pDemodInfo->controlState = LX_DEMOD_SIGNAL_STABLE;

					DEMOD_PRINT( "^c^[DEMOD M19 GBB] ERR (%s:%d) Already Done !!!\n", __F__, __L__);
					DEMOD_PRINT( "^R^[DEMOD M19 GBB] LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
					return RET_OK;
				}

				if(RET_OK != DEMOD_M19_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_OFF, &scanProcessing, &scanLock))
				{
					DEMOD_PRINT("[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_M19_NeverlockScan() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}

				if((LX_DEMOD_FLAG_FINISH == scanProcessing) && (LX_DEMOD_LOCKED == scanLock))
				{
					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState = LX_DEMOD_SIGNAL_STABLE;

					DEMOD_PRINT( "^G^[DEMOD M19 GBB] (%s:%d) Signal is Found  !!!\n", __F__, __L__);
					DEMOD_PRINT_ALWAYS( "^R^[DEMOD M19 GBB] SCANNING !!! FIRST LOCK! : Going to LX_DEMOD_SIGNAL_STABLE..... ^0^\n");
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

					DEMOD_PRINT_ALWAYS("\nLX_DEMOD_TUNE_SCAN : MSG_ATSC_FRONT_END_NOT_LOCKED..\n") ;
					DEMOD_PRINT_ALWAYS("LX_DEMOD_TUNE_SCAN : Elapse time is %d msec\n", elapsedTime) ;

					DEMOD_PRINT( "^G^[DEMOD M14B0 GBB] (%s:%d) Signal is NOT Found  !!!\n", __F__, __L__);


				}
				else
				{
					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_ING;
					DEMOD_PRINT( "^G^[DEMOD M14B0 GBB] (%s:%d) Detection is on processing	!!!\n", __F__, __L__);
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

				LX_DEMOD_LOCK_STATE_T			lockState;

				if(RET_OK != DEMOD_M19_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
				{
					DEMOD_PRINT("[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_M19_Get_Lock() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					pDemodInfo->controlState	= LX_DEMOD_SIGNAL_STABLE;
					sigStablestartTime = jiffies_to_msecs(jiffies);
					DEMOD_PRINT( "^R^[DEMOD M19 GBB] LX_DEMOD_SYNC_CHECKING : Going to LX_DEMOD_SIGNAL_STABLE..... ^0^\n");
				}
				else
				{
					if(RET_OK != DEMOD_M19_Get_Lock(LX_DEMOD_CARR_LOCK, &lockState))
					{
						DEMOD_PRINT("[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_M19_Get_Lock() !!!\n", __F__, __L__);
						DEMOD_RETURN_FAIL(__F__);
					}

					if(LX_DEMOD_LOCKED == lockState)
					{
						DEMOD_PRINT( "^R^[DEMOD M19 GBB] LX_DEMOD_SYNC_CHECKING : catch only carrier lock..... ^0^\n");
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

										   	/********************************************/
										   	/***** Attempting to obtain signal stability *****/
	   	case LX_DEMOD_SIGNAL_STABLE: 		/********************************************/
			{
				LX_DEMOD_LOCK_STATE_T			lockState;
				SINT32							freqOffset=0;
				unsigned int 					elapsedTime;
				UINT32 							packetError;


				if(RET_OK != DEMOD_M19_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
				{
					DEMOD_PRINT("[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_M19_Get_Lock() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					if (LX_DEMOD_TUNE_NORMAL == pDemodInfo->setCfgParam.vsb.tuneMode)
					{
						elapsedTime = jiffies_to_msecs(jiffies) - sigStablestartTime;

						if(RET_OK != DEMOD_M19_Get_Packet_Error(&packetError))
						{
							DEMOD_PRINT("[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_M19_Get_Packet_Error() !!!\n", __F__, __L__);
							DEMOD_RETURN_FAIL(__F__);
						}
						else
						{
							pDemodInfo->bNotifiedLock	= TRUE;
							pDemodInfo->bNotifiedUnlock	= FALSE;
							pDemodInfo->lockStatus		= LX_DEMOD_LOCKED;
							pDemodInfo->signalStatus.bSignalValid = TRUE;

							pDemodInfo->controlState	= LX_DEMOD_SIGNAL_LOCKED;

							elapsedTime = jiffies_to_msecs(jiffies) - g_RetuneStartTime;

							DEMOD_PRINT_ALWAYS( "[DEMOD M19 GBB] LX_DEMOD_SIGNAL_STABLE[0716] : MSG_ATSC_FRONT_END_LOCKED..... ^^^0^^^\n");
							DEMOD_PRINT_ALWAYS( "[DEMOD M19 GBB] LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^^^0^^^\n", elapsedTime);

							if (RET_OK != DEMOD_M19_TPOutEnable(TRUE))
							{
								DEMOD_PRINT( "^r^[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_M19_TPOutEnable(FALSE) !!!\n", __F__, __L__);
								DEMOD_RETURN_FAIL(__F__);
							}

							if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
							{
								DEMOD_PRINT( "^r^[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_Get_CarrierFreqOffset() !!!\n", __F__, __L__);
								DEMOD_RETURN_FAIL(__F__);
							}

							if (RET_OK != _DEMOD_M19_LGDBB_VSB_CheckSignalState(pDemodInfo))
							{
								DEMOD_PRINT( "^r^[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_Get_signal_status() !!!\n", __F__, __L__);
								DEMOD_RETURN_FAIL(__F__);
							}

						}


					}
					else
					{
						pDemodInfo->bNotifiedLock	= TRUE;
						pDemodInfo->bNotifiedUnlock = FALSE;
						pDemodInfo->lockStatus		= LX_DEMOD_LOCKED;
						pDemodInfo->signalStatus.bSignalValid = TRUE;

						if (RET_OK != DEMOD_M19_Get_CarrierFreqOffset(&freqOffset))
						{
							DEMOD_PRINT( "^r^[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_M19_Get_CarrierFreqOffset() !!!\n", __F__, __L__);
							DEMOD_RETURN_FAIL(__F__);
						}
						pDemodInfo->freqOffset = freqOffset;

						pDemodInfo->controlState	= LX_DEMOD_SIGNAL_LOCKED;

						elapsedTime = jiffies_to_msecs(jiffies) - g_RetuneStartTime;

						DEMOD_PRINT_ALWAYS( "[DEMOD M19 GBB] LX_DEMOD_SIGNAL_STABLE : MSG_ATSC_FRONT_END_LOCKED..... ^0^\n");
						DEMOD_PRINT_ALWAYS( "[DEMOD M19 GBB] LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^0^\n", elapsedTime);
						DEMOD_PRINT( "^R^[DEMOD M19 GBB] LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^0^\n", freqOffset);

						if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
						{
							DEMOD_PRINT( "^r^[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_Get_CarrierFreqOffset() !!!\n", __F__, __L__);
							DEMOD_RETURN_FAIL(__F__);
						}
						if (RET_OK != _DEMOD_M19_LGDBB_VSB_CheckSignalState(pDemodInfo))
						{
							DEMOD_PRINT( "^r^[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_Get_signal_status() !!!\n", __F__, __L__);
							DEMOD_RETURN_FAIL(__F__);
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
 * DEMOD_M19_VSB_Monitoring_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_M19_VSB_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{

	LX_DEMOD_LOCK_STATE_T			lockState;

	if(RET_OK != DEMOD_M19_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
	{
		DEMOD_PRINT("[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_Get_Lock() !!!\n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}

#if 1
	if(RET_OK != DEMOD_M19_VSB_Monitor(pDemodInfo))
	{
		DEMOD_PRINT("[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_M19_VSB_Monitor() !!!\n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}
#endif

	if(LX_DEMOD_LOCKED == lockState)
	{
		pDemodInfo->unLockCount = 0;
		pDemodInfo->unLockLongCount	= 0;

//		if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
//			pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;

		if (RET_OK != _DEMOD_M19_LGDBB_VSB_CheckSignalState(pDemodInfo))
		{
			DEMOD_PRINT( "^r^[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_Get_signal_status() !!!\n", __F__, __L__);
			DEMOD_RETURN_FAIL(__F__);
		}

		#if 0    // modify chungiii 2016_0319
		if (RET_OK != DEMOD_Get_signal_status(pDemodInfo))
		{
			DEMOD_PRINT( "^r^[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_Get_signal_status() !!!\n", __F__, __L__);
			DEMOD_RETURN_FAIL(__F__);
		}
		#endif

		if(pDemodInfo->bIsTPoutEn == TRUE)
		{
			if (RET_OK != DEMOD_M19_TPOutEnable(TRUE))
			{
				DEMOD_PRINT( "^r^[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_M19_TPOutEnable(TRUE) !!!\n", __F__, __L__);
				DEMOD_RETURN_FAIL(__F__);
			}
		}
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

			DEMOD_PRINT_ALWAYS( "[DEMOD M19 GBB] MONITORING FUNC : MSG_ATSC_FRONT_END_LOCKED..... ^0^\n");

			if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
				pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;

		}
		if(pDemodInfo->lockCount >= 2)
		{
			pDemodInfo->lockCount = 0;
		}

		if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
		{
			DEMOD_PRINT( "^r^[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_Get_TunedCFG() !!!\n", __F__, __L__);
			DEMOD_RETURN_FAIL(__F__);
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

			if(pDemodInfo->unLockCount == 4)
			{
				pDemodInfo->lockStatus = LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedLock = FALSE;
				pDemodInfo->bNotifiedUnlock = TRUE;
				pDemodInfo->signalStatus.bSignalValid = FALSE;

				DEMOD_PRINT_ALWAYS( "[DEMOD M19 GBB] MONITORING FUNC : MSG_ATSC_FRONT_END_NOT_LOCKED..... -_-\n");

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

int _DEMOD_M19_LGDBB_QAM_CheckSignalState(DEMOD_CTX_T *pDemodInfo)
{

	LX_DEMOD_L2_Context *pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

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
	printk("[sym_rate: %d]\n"			,signalStatus.sym_rate);
	printk("[constPwr: %d]\n"			,signalStatus.constPwr);
	//printk("[unsnr: %d]\n"			,signalStatus.snr));
#endif

	pDemodInfo->signalStatus.packetError 	= signalStatus.packetError;
	pDemodInfo->signalStatus.ber			= signalStatus.ber;
	pDemodInfo->signalStatus.agc			= signalStatus.if_agc;
	//pDemodInfo->signalStatus.m.mse			= signalStatus.mse;
	pDemodInfo->signalStatus.m.mse			= signalStatus.mse_info;
	pDemodInfo->signalStatus.m.constPwr		= signalStatus.constPwr;

	pDemodInfo->freqOffset 					= signalStatus.offsetFrq_Hz;

	pDemodInfo->signalStatus.operMode 	= pDemodInfo->operMode;
	pDemodInfo->signalStatus.rfMode	= pDemodInfo->systemMode;


	return RET_OK;

}


int _DEMOD_M19_QAM_CheckTuneMode(DEMOD_CTX_T *pDemodInfo)
{
	UINT8  new_tuneMode;

	switch (pDemodInfo->setCfgParam.qam.tuneMode)
	{
		case	LX_DEMOD_TUNE_NORMAL:		new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_NORMAL; break;
		case	LX_DEMOD_TUNE_AUTO: 			new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_AUTO; break;
		case	LX_DEMOD_TUNE_MANUAL: 		new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_MANUAL ; break;
	//	case	TU_TUNE_SPEC_DVBC_FIXED_DATA:		new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_FIXED_DATA; break;

		default:						return DEMOD_DD_MODE_PROP_TUNEMODE_AUTO; break;
	}

	return new_tuneMode;
}


int DEMOD_M19_LGDBB_QAM_SetDemod(DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_L2_Context 	*pFrontend;
	UINT8	new_tuneMode;
	UINT32 	freq_Khz;
	UINT16 	ter_bandwidth_KHz;
	pFrontend		= &gM19_LGDBB_Frontend;

	freq_Khz = 0;

	// printk("[M19 LGDBB][0716] ################### chungiii SetDemod QAM \n");

	new_tuneMode = _DEMOD_M19_QAM_CheckTuneMode(pDemodInfo);

	if(RET_OK != DEMOD_M19_Get_BW(pDemodInfo, &ter_bandwidth_KHz))
	{
		DEMOD_PRINT("[DEMOD M19 DBB] FAIL (%s:%d) DEMOD_M19_Get_BW !!!\n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}
	// printk("[M19 LGDBB] ################### chungiii SetDemod QAM check ter_bandwidth_KHz[%d] \n", ter_bandwidth_KHz);

		DEMOD_L2_ATSC_Set_demod(pFrontend,
							DEMOD_DD_MODE_PROP_MODULATION_QAM,
							freq_Khz,
							new_tuneMode,
							DEMOD_DD_MODE_PROP_SPECINV_AUTO,
							DEMOD_DD_MODE_PROP_SPECINV_NORMAL,
							ter_bandwidth_KHz,
							0
							);

	return RET_OK;

}



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_QAM_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_M19_QAM_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{

	static LX_DEMOD_FLAG_T 			scanProcessing = LX_DEMOD_FLAG_START;
	static LX_DEMOD_LOCK_STATE_T 	scanLock = LX_DEMOD_UNLOCKED;
	static unsigned int 			sigStablestartTime = 0;
	static unsigned int 			manualOperationTime = 0;
	static LX_DEMOD_TUNE_MODE_T		realTuneMode = LX_DEMOD_TUNE_UNKNOWN;


	switch (pDemodInfo->controlState)
	{
											/***************************************************/
											/***** Configure tuner for desired channel No. *****/
		case LX_DEMOD_TUNE_START:			/***************************************************/
			{

				if(RET_OK != DEMOD_M19_LGDBB_QAM_SetDemod(pDemodInfo))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD M19 LGDBB] FAIL (%s:%d) DEMOD_M19_LGDBB_QAM_SetDemod() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}

				if (RET_OK != DEMOD_M19_TPOutEnable(TRUE))
				{
					DEMOD_PRINT( "^r^[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_M19_TPOutEnable(FALSE) !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_TUNE_NORMAL != pDemodInfo->setCfgParam.qam.tuneMode)
				{
					realTuneMode = LX_DEMOD_TUNE_AUTO;

					if(RET_OK != DEMOD_M19_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_ON, &scanProcessing, &scanLock))
					{
						DEMOD_PRINT("[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_M19_NeverlockScan() !!!\n", __F__, __L__);
						DEMOD_RETURN_FAIL(__F__);
					}
					pDemodInfo->controlState = LX_DEMOD_TUNE_SCAN;
					DEMOD_PRINT( "[DEMOD M19 GBB] LX_DEMOD_TUNE_START : (auto) Going to LX_DEMOD_TUNE_SCAN..... ^0^\n");

				}
				else
				{
					realTuneMode = LX_DEMOD_TUNE_NORMAL;
					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState = LX_DEMOD_SYNC_CHECKING;
					manualOperationTime = jiffies_to_msecs(jiffies);

					DEMOD_PRINT( "[DEMOD M19 GBB] LX_DEMOD_TUNE_START :(manual) Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");

				}


			}

			break;


											/***************************************************/
											/***** Configure demod for scan mode. *****/
		case LX_DEMOD_TUNE_SCAN:			/***************************************************/
			{

				unsigned int currentTime = 0;
				unsigned int elapsedTime = 0;

				if((LX_DEMOD_FLAG_COMPLETE == pDemodInfo->scanJobFlag) || (LX_DEMOD_FLAG_FINISH == pDemodInfo->scanJobFlag))
				{

					pDemodInfo->controlState = LX_DEMOD_SIGNAL_STABLE;

					DEMOD_PRINT( "^c^[DEMOD M19 GBB] ERR (%s:%d) Already Done !!!\n", __F__, __L__);
					DEMOD_PRINT( "^R^[DEMOD M19 GBB] LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
					return RET_OK;
				}

				if(RET_OK != DEMOD_M19_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_OFF, &scanProcessing, &scanLock))
				{
					DEMOD_PRINT("[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_M19_NeverlockScan() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}

				if((LX_DEMOD_FLAG_FINISH == scanProcessing) && (LX_DEMOD_LOCKED == scanLock))
				{
					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState = LX_DEMOD_SIGNAL_STABLE;

					DEMOD_PRINT( "^G^[DEMOD M19 GBB] (%s:%d) Signal is Found  !!!\n", __F__, __L__);
					DEMOD_PRINT( "^R^[DEMOD M19 GBB] LX_DEMOD_SYNC_CHECKING : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");

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

					DEMOD_PRINT_ALWAYS("\nLX_DEMOD_TUNE_SCAN : MSG_QAM_FRONT_END_NOT_LOCKED..\n") ;
					DEMOD_PRINT_ALWAYS("LX_DEMOD_TUNE_SCAN : Elapse time is %d msec\n", elapsedTime) ;

					DEMOD_PRINT( "^G^[DEMOD M19 GBB] (%s:%d) Signal is NOT Found  !!!\n", __F__, __L__);


				}
				else
				{
					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_ING;
					DEMOD_PRINT( "^G^[DEMOD M19 GBB] (%s:%d) Detection is on processing	!!!\n", __F__, __L__);
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
				unsigned int 			elapsedTime;

				if (RET_OK != _DEMOD_M19_LGDBB_QAM_CheckSignalState(pDemodInfo))
				{
						DEMOD_PRINT( "^r^[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_Get_signal_status() !!!\n", __F__, __L__);
						DEMOD_RETURN_FAIL(__F__);
				}

				if(RET_OK != DEMOD_M19_Get_Lock(LX_DEMOD_FEC_LOCK, &lockState))
				{
					DEMOD_PRINT("[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_M19_Get_Lock() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_LOCKED == lockState)
				{

					if(RET_OK != DEMOD_M19_QAM_EQ_Signal_Detector(FALSE))
					{
						DEMOD_PRINT("[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_M19_QAM_EQ_Signal_Detector() !!!\n", __F__, __L__);
						DEMOD_RETURN_FAIL(__F__);
					}

					pDemodInfo->controlState	= LX_DEMOD_SIGNAL_STABLE;

					sigStablestartTime = jiffies_to_msecs(jiffies);

					DEMOD_PRINT( "^R^[DEMOD M19 GBB] LX_DEMOD_SYNC_CHECKING : Going to LX_DEMOD_SIGNAL_STABLE..... ^0^\n");
				}
				else
				{
					if(LX_DEMOD_TUNE_NORMAL == realTuneMode)
					{
						elapsedTime = jiffies_to_msecs(jiffies) - manualOperationTime;


						if(elapsedTime > LX_DEMOD_LOCK_DEALY_300)
						{
							if(RET_OK != DEMOD_M19_QAM_ModeAutoDetection(TRUE))
							{
								DEMOD_PRINT("[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_M19_QAM_ModeAutoDetection() !!!\n", __F__, __L__);
								DEMOD_RETURN_FAIL(__F__);
							}
							#if 0
							if(RET_OK != DEMOD_M19_SoftwareReset())
							{
								DEMOD_PRINT("[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_M19_SoftwareReset() !!!\n", __F__, __L__);
								DEMOD_RETURN_FAIL(__F__);
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
	   	case LX_DEMOD_SIGNAL_STABLE: 		/********************************************/
			{
				LX_DEMOD_LOCK_STATE_T			lockState;
				SINT32							freqOffset;
				unsigned int 					elapsedTime;
				UINT32 							packetError;

				if(RET_OK != DEMOD_M19_Get_Lock(LX_DEMOD_FEC_LOCK, &lockState))
				{
					DEMOD_PRINT("[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_M19_Get_Lock() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
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
							if(RET_OK != DEMOD_M19_Get_Packet_Error(&packetError))
							{
								DEMOD_PRINT("[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_M19_Get_Packet_Error() !!!\n", __F__, __L__);
								DEMOD_RETURN_FAIL(__F__);
							}
							else
							{
								if(packetError < LX_DEMOD_PACKET_ERROR_THD)
								{
									pDemodInfo->bNotifiedLock	= TRUE;
									pDemodInfo->bNotifiedUnlock	= FALSE;
									pDemodInfo->lockStatus		= LX_DEMOD_LOCKED;
									pDemodInfo->signalStatus.bSignalValid = TRUE;

									if (RET_OK != DEMOD_M19_Get_CarrierFreqOffset(&freqOffset))
									{
										DEMOD_PRINT( "^r^[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_M19_Get_CarrierFreqOffset() !!!\n", __F__, __L__);
										DEMOD_RETURN_FAIL(__F__);
									}
									pDemodInfo->freqOffset = freqOffset;

									pDemodInfo->controlState	= LX_DEMOD_SIGNAL_LOCKED;

									elapsedTime = jiffies_to_msecs(jiffies) - g_RetuneStartTime;

									DEMOD_PRINT_ALWAYS( "[DEMOD M19 GBB] LX_DEMOD_SIGNAL_STABLE : MSG_QAM_FRONT_END_LOCKED..... ^^^0^^^\n");
									DEMOD_PRINT_ALWAYS( "[DEMOD M19 GBB] LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^^^0^^^\n", elapsedTime);
									DEMOD_PRINT( "^R^[DEMOD M19 GBB] LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^0^\n", freqOffset);

									if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
									{
										DEMOD_PRINT( "^r^[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_Get_TunedCFG() !!!\n", __F__, __L__);
										DEMOD_RETURN_FAIL(__F__);
									}
									if (RET_OK != _DEMOD_M19_LGDBB_QAM_CheckSignalState(pDemodInfo))
									{
										DEMOD_PRINT( "^r^[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_Get_signal_status() !!!\n", __F__, __L__);
										DEMOD_RETURN_FAIL(__F__);
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

										if (RET_OK != DEMOD_M19_Get_CarrierFreqOffset(&freqOffset))
										{
											DEMOD_PRINT( "^r^[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_M19_Get_CarrierFreqOffset() !!!\n", __F__, __L__);
											DEMOD_RETURN_FAIL(__F__);
										}
										pDemodInfo->freqOffset = freqOffset;

										pDemodInfo->controlState	= LX_DEMOD_SIGNAL_LOCKED;

										elapsedTime = jiffies_to_msecs(jiffies) - g_RetuneStartTime;

										DEMOD_PRINT_ALWAYS( "[DEMOD M19 GBB] LX_DEMOD_SIGNAL_STABLE : MSG_QAM_FRONT_END_LOCKED..... ^^0^^\n");
										DEMOD_PRINT_ALWAYS( "[DEMOD M19 GBB] LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^^0^^\n", elapsedTime);
										DEMOD_PRINT( "^R^[DEMOD M19 GBB] LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^^0^^\n", freqOffset);

										if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
										{
											DEMOD_PRINT( "^r^[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_Get_TunedCFG() !!!\n", __F__, __L__);
											DEMOD_RETURN_FAIL(__F__);
										}
										if (RET_OK != _DEMOD_M19_LGDBB_QAM_CheckSignalState(pDemodInfo))
										{
											DEMOD_PRINT( "^r^[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_Get_signal_status() !!!\n", __F__, __L__);
											DEMOD_RETURN_FAIL(__F__);
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

						if (RET_OK != DEMOD_M19_Get_CarrierFreqOffset(&freqOffset))
						{
							DEMOD_PRINT( "^r^[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_M19_Get_CarrierFreqOffset() !!!\n", __F__, __L__);
							DEMOD_RETURN_FAIL(__F__);
						}
						pDemodInfo->freqOffset = freqOffset;

						pDemodInfo->controlState	= LX_DEMOD_SIGNAL_LOCKED;

						elapsedTime = jiffies_to_msecs(jiffies) - g_RetuneStartTime;

						DEMOD_PRINT_ALWAYS( "[DEMOD M19 GBB] LX_DEMOD_SIGNAL_STABLE : MSG_QAM_FRONT_END_LOCKED..... ^0^\n");
						DEMOD_PRINT_ALWAYS( "[DEMOD M19 GBB] LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^0^\n", elapsedTime);
						DEMOD_PRINT( "^R^[DEMOD M19 GBB] LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^0^\n\n", freqOffset);

						//DEMOD_M19_Get_Dump();

						if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
						{
							DEMOD_PRINT( "^r^[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_Get_TunedCFG() !!!\n", __F__, __L__);
							DEMOD_RETURN_FAIL(__F__);
						}
						if (RET_OK != DEMOD_Get_signal_status(pDemodInfo))
						{
							DEMOD_PRINT( "^r^[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_Get_signal_status() !!!\n", __F__, __L__);
							DEMOD_RETURN_FAIL(__F__);
						}

					}



				}
				else
				{
					pDemodInfo->controlState	= LX_DEMOD_SYNC_CHECKING;
					DEMOD_PRINT( "^R^[DEMOD M19 GBB] LX_DEMOD_SYNC_CHECKING : Going back to LX_DEMOD_SYNC_CHECKING..... **;\n");

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
 * DEMOD_M19_QAM_Monitoring_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_M19_QAM_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{

	LX_DEMOD_LOCK_STATE_T			lockState;

	if(RET_OK != DEMOD_M19_Get_Lock(LX_DEMOD_FEC_LOCK, &lockState))
	{
		DEMOD_PRINT("[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_Get_Lock() !!!\n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}

#if 0
	DEMOD_PRINT( " pDemodInfo->lockStatus = %d, pDemodInfo->bNotifiedLock = %d, (lockCount = %d) \n",pDemodInfo->lockStatus,pDemodInfo->bNotifiedLock,pDemodInfo->lockCount);
	DEMOD_PRINT( " pDemodInfo->lockStatus = %d, pDemodInfo->bNotifiedUnlock = %d,(unlockCnt = %d) \n",pDemodInfo->lockStatus,pDemodInfo->bNotifiedUnlock,pDemodInfo->unLockCount);
	DEMOD_PRINT( " lockState = %d) \n",lockState);
#endif
	if(LX_DEMOD_LOCKED == lockState)
	{
		pDemodInfo->unLockCount = 0;
		pDemodInfo->unLockLongCount	= 0;


//		if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
//			pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;


		if (RET_OK != _DEMOD_M19_LGDBB_QAM_CheckSignalState(pDemodInfo))
		{
			DEMOD_PRINT( "^r^[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_Get_signal_status() !!!\n", __F__, __L__);
			DEMOD_RETURN_FAIL(__F__);
		}

		if((LX_DEMOD_LOCKED != pDemodInfo->lockStatus)  && (TRUE != pDemodInfo->bNotifiedLock))
		{
			pDemodInfo->lockCount++;
		}
		if(pDemodInfo->lockCount == 2)
		{

			pDemodInfo->lockStatus 		= LX_DEMOD_LOCKED;
			pDemodInfo->bNotifiedLock 	= TRUE;
			pDemodInfo->bNotifiedUnlock = FALSE;
				pDemodInfo->signalStatus.bSignalValid = TRUE;

				DEMOD_PRINT_ALWAYS( "[DEMOD M19 GBB] MONITORING FUNC : MSG_QAM_FRONT_END_LOCKED..... ^0^\n");

			if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
				pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;

		}
		if(pDemodInfo->lockCount >= 2)
		{
			pDemodInfo->lockCount = 0;
		}

		if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
		{
			DEMOD_PRINT( "^r^[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_Get_TunedCFG() !!!\n", __F__, __L__);
			DEMOD_RETURN_FAIL(__F__);
		}



	}
	else
	{

		pDemodInfo->lockCount = 0;
		_gM19GBB_VQI_UnlockCount_full_packeterr = 0;

		if(pauseTimeDemod != LX_DEMOD_LOCK_FAIL_PAUSE_TIME )
			pauseTimeDemod = LX_DEMOD_LOCK_FAIL_PAUSE_TIME;


		if((LX_DEMOD_UNLOCKED != pDemodInfo->lockStatus)  && (TRUE != pDemodInfo->bNotifiedUnlock))
		{
			pDemodInfo->unLockCount++;

			if(pDemodInfo->unLockCount == 4)
			{
				pDemodInfo->lockStatus 		= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedLock	= FALSE;
				pDemodInfo->bNotifiedUnlock = TRUE;
				pDemodInfo->signalStatus.bSignalValid = FALSE;

				DEMOD_PRINT_ALWAYS( "[DEMOD M19 GBB] MONITORING FUNC : MSG_QAM_FRONT_END_NOT_LOCKED..... -_-\n");

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

int _DEMOD_M19_LGDBB_ISDB_CheckSignalState(DEMOD_CTX_T *pDemodInfo)
{

	LX_DEMOD_L2_Context 	*pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;
	UINT32					ber = 0;

	pFrontend = &gM19_LGDBB_Frontend;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT("(%s) FAIL, DEMOD_L2_SignalStatus() \n", __F__);
		return RET_ERROR;;
	}

#if 0
	printk("[dd_status] results \n");

	printk("[neverlock: %d]\n"	, pFrontend->demod->rsp->dd_status.neverLock);
	printk("[modulation: %d]\n"	, pFrontend->demod->rsp->dd_status.reply_operMod);


	printk("[ISDBT_status] results \n");

	printk("[if_agc: %d]\n"			, pFrontend->demod->rsp->isdbt_status.if_agc);
	printk("[mse_info: %d]\n"			, pFrontend->demod->rsp->isdbt_status.mse_info);
	printk("[op_mode: %d]\n" 		, pFrontend->demod->rsp->isdbt_status.op_mode);
	printk("[dl: %d]\n"			, pFrontend->demod->rsp->isdbt_status.lock_fec);
	printk("[ber: %d]\n" 		, pFrontend->demod->rsp->isdbt_status.ber);
	printk("[pe: %d]\n"		, pFrontend->demod->rsp->isdbt_status.pe);
	printk("[afc_freq: %d]\n"	, pFrontend->demod->rsp->isdbt_status.cfo);
	printk("[constellation: %d]\n"	, pFrontend->demod->rsp->isdbt_status.constellation);
	printk("[sp_inv: %d]\n"		, pFrontend->demod->rsp->isdbt_status.spInv);
	printk("[fft_mode: %d]\n"	, pFrontend->demod->rsp->isdbt_status.fft_mode);
	printk("[guard_int: %d]\n"	, pFrontend->demod->rsp->isdbt_status.gi);

	printk("[A. QAM mode : %d]\n"	, pFrontend->demod->rsp->isdbt_status.oqama);
	printk("[A. code rate : %d]\n"	, pFrontend->demod->rsp->isdbt_status.ocra);
	printk("[A. segment num : %d]\n" , pFrontend->demod->rsp->isdbt_status.onsega);
	printk("[A. interleaving length : %d]\n" , pFrontend->demod->rsp->isdbt_status.oila);

	printk("[B. QAM mode : %d]\n"	, pFrontend->demod->rsp->isdbt_status.oqamb);
	printk("[B. code rate : %d]\n"	, pFrontend->demod->rsp->isdbt_status.ocrb);
	printk("[B. segment num : %d]\n" , pFrontend->demod->rsp->isdbt_status.onsegb);
	printk("[B. interleaving length : %d]\n" , pFrontend->demod->rsp->isdbt_status.oilb);

	printk("[C. QAM mode : %d]\n"	, pFrontend->demod->rsp->isdbt_status.oqamc);
	printk("[C. code rate : %d]\n"	, pFrontend->demod->rsp->isdbt_status.ocrc);
	printk("[C. segment num : %d]\n" , pFrontend->demod->rsp->isdbt_status.onsegc);
	printk("[C. interleaving length : %d]\n" , pFrontend->demod->rsp->isdbt_status.oilc);
#endif


    #if 0
	printk("[dd_status] results \n");

	printk("[neverlock: %d]\n"	, pFrontend->demod->rsp->dd_status.neverLock);
	printk("[modulation: %d]\n"	, pFrontend->demod->rsp->dd_status.reply_operMod);

	printk("[ISDBT_status] results \n");

	printk("[op_mode: %d]\n"		,signalStatus.operatingMode);
	printk("[if_agc: %d]\n"			,signalStatus.if_agc);
	printk("[mse_info: %d]\n"		,signalStatus.mse_info);
	printk("[snr: %d]\n"			,signalStatus.snr);
	printk("[dl: %d]\n"				,signalStatus.demodLock);
	printk("[ber: %d]\n"			,signalStatus.ber);
	printk("[pe: %d]\n"				,signalStatus.packetError);
	printk("[afc_freq: %d]\n"		,signalStatus.offsetFrq_Hz);//signalStatus.offsetFrq_Hz / 1000);
	printk("[constellation: %d]\n"	,signalStatus.constellation);
	printk("[sp_inv: %d]\n"			,signalStatus.spInv);
	printk("[bandwidth: %d]\n"		,signalStatus.bandwidth);
	printk("[constPwr: %d]\n"		,signalStatus.constPwr);
    #endif

	ber =  (UINT32)(pFrontend->demod->rsp->isdbt_status.ber);

	pDemodInfo->signalStatus.packetError 	= (UINT32)(pFrontend->demod->rsp->isdbt_status.pe);
	pDemodInfo->signalStatus.ber			= (UINT32)(ber);//(UINT32)(ber * 1000000);
	pDemodInfo->signalStatus.agc			= signalStatus.if_agc;
	//pDemodInfo->signalStatus.m.mse			= signalStatus.mse;
	//pDemodInfo->signalStatus.m.mse			= pFrontend->demod->rsp->isdbt_status.mse_info;
	pDemodInfo->signalStatus.m.mse			= signalStatus.mse_info;
	pDemodInfo->signalStatus.m.constPwr		= signalStatus.constPwr;

	pDemodInfo->freqOffset 					= signalStatus.offsetFrq_Hz;

	pDemodInfo->signalStatus.operMode 		= pDemodInfo->operMode;
	pDemodInfo->signalStatus.rfMode			= pDemodInfo->systemMode;


	return RET_OK;

}


int _DEMOD_M19_ISDB_CheckTuneMode(DEMOD_CTX_T *pDemodInfo)
{
	UINT8  new_tuneMode;

	switch (pDemodInfo->setCfgParam.isdbt.tuneMode)
	{
		case	LX_DEMOD_TUNE_NORMAL:		new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_NORMAL; break;
		case	LX_DEMOD_TUNE_AUTO: 			new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_AUTO; break;
		case	LX_DEMOD_TUNE_MANUAL: 		new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_MANUAL ; break;
	//	case	TU_TUNE_SPEC_DVBC_FIXED_DATA:		new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_FIXED_DATA; break;

		default:						return DEMOD_DD_MODE_PROP_TUNEMODE_AUTO; break;
	}

	return new_tuneMode;
}


int DEMOD_M19_LGDBB_ISDB_SetDemod(DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_L2_Context 	*pFrontend;
	UINT8	new_tuneMode;
	UINT32 	freq_Khz;
	UINT16 	ter_bandwidth_KHz;

	pFrontend		= &gM19_LGDBB_Frontend;

	freq_Khz = 0;

	// printk("[M19 LGDBB] ################### chungiii SetDemod ISDBT \n");

	new_tuneMode = _DEMOD_M19_ISDB_CheckTuneMode(pDemodInfo);
	//printk("[M19 LGDBB] ################### chungiii SetDemod ISDBT new_tuneMode[%d] \n", new_tuneMode);

	if(RET_OK != DEMOD_M19_Get_BW(pDemodInfo, &ter_bandwidth_KHz))
	{
		DEMOD_PRINT("[DEMOD M19 DBB] FAIL (%s:%d) DEMOD_M19_Get_BW !!!\n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}
	 //printk("[M19 LGDBB] ################### chungiii SetDemod ISDB check ter_bandwidth_KHz[%d] \n", ter_bandwidth_KHz);

		DEMOD_L2_ATSC_Set_demod(pFrontend,
							DEMOD_DD_MODE_PROP_MODULATION_ISDBT,
							freq_Khz,
							new_tuneMode,
							DEMOD_DD_MODE_PROP_SPECINV_MANUAL,
							DEMOD_DD_MODE_PROP_SPECINV_NORMAL,
							ter_bandwidth_KHz,
							0
							);

	return RET_OK;

}


int DEMOD_M19_ISDBT_TDI_Enable(BOOLEAN bEnable)
{

	LX_DEMOD_L2_Context *pFrontend;

	UINT16 addr;
	UINT8 vqData;

	pFrontend = &gM19_LGDBB_Frontend;

	addr = 0x406a;

	//printk("[DEMOD M19p]   DEMOD_M19_TDI_Enable  ###### chungiii \n");

	pFrontend->demod->cmd->dd_get_reg.addressMsb = (UINT8)((addr >> 8) & 0xff);
	pFrontend->demod->cmd->dd_get_reg.addressLsb =  (UINT8)((addr >> 0) & 0xff);
	pFrontend->demod->cmd->dd_get_reg.length = 1;

	if(RET_OK != DEMOD_L2_SendCommand(pFrontend, DEMOD_DD_GET_REG_CMD_CODE))
	{
		DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_I2C_Read() !!!\n", __F__, __L__);
		return RET_ERROR;
	}

	vqData = (UINT8)(pFrontend->demod->rsp->dd_get_reg.mData[0]);

	if(bEnable == TRUE)
		vqData = vqData & 0x7f;
	else
		vqData = vqData | 0x80;

	//printk("[DEMOD M19p]   DEMOD_M19_TDI_Enable  ###### chungiii  check TDI data[0x%x] \n", vqData);


	pFrontend->demod->cmd->dd_set_reg.addressMsb = (UINT8)((addr >> 8) & 0xff);
	pFrontend->demod->cmd->dd_set_reg.addressLsb =	(UINT8)((addr >> 0) & 0xff);
	pFrontend->demod->cmd->dd_set_reg.length = 1;
	pFrontend->demod->cmd->dd_set_reg.data= (UINT32)vqData;

	if(RET_OK != DEMOD_L2_SendCommand(pFrontend, DEMOD_DD_SET_REG_CMD_CODE))
	{
		DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_DBB_I2C_Write() !!!\n", __F__, __L__);
		return RET_ERROR;
	}


	return RET_OK;

}




int DEMOD_M19_ISDBT_Set_MemSconfig(void)
{

	LX_DEMOD_L2_Context *pFrontend;

	UINT32	st_mem;

	pFrontend = &gM19_LGDBB_Frontend;

	st_mem = gMemCfgDEMOD.memory_base;

	if(st_mem == 0)
	{
		printk("######[0629] Error M19 DEMOD Wrong Memory Base Address ##### !!!!!!!!!!!!!!!!!!!!!!!\n");
	}
	else
	{
		printk("######[0629] first call DEMOD_M19_ISDBT_Set_MemSconfig addr[0x%x] ##### !!!!!!\n", st_mem );
		if(RET_OK != DEMOD_L2_ISDB_Set_BaseAddr_AXI(pFrontend, st_mem))
		{
			DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_L2_ATSC_Set_BaseAddr_AXI() !!!\n", __F__, __L__);
			return RET_ERROR;
		}
	}



	return RET_OK;


}


int DEMOD_M19_ISDBT_GetEmergencyAlertFlagStatus(BOOLEAN *pEalarm)
{

	LX_DEMOD_L2_Context 	*pFrontend;
	UINT8 					balarm;

	pFrontend = &gM19_LGDBB_Frontend;

	if(RET_OK != DEMOD_L2_ISDB_Get_Emergency_Alarm(pFrontend, &balarm))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD] FAIL (%s:%d) DEMOD_L2_ATSC_Get_Emergency_Alarm() !!!\n", __F__, __L__);
		return RET_ERROR;
	}

	if(balarm == 1)
	{
		DEMOD_PRINT("^R^[DEMOD] EWBS is operated!!![0x%x]\n", balarm);
		*pEalarm = TRUE;
	}
	else
	{
		DEMOD_PRINT("^G^[DEMOD] EWBS is not operated[0x%x]\n", balarm);
		*pEalarm = FALSE;
	}




	return RET_OK;


}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_ISDBT_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_M19_ISDBT_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{

	static LX_DEMOD_FLAG_T 			scanProcessing = LX_DEMOD_FLAG_START;
	static LX_DEMOD_LOCK_STATE_T 	scanLock = LX_DEMOD_UNLOCKED;
	static unsigned int 			sigStablestartTime = 0;


	switch (pDemodInfo->controlState)
	{

											/***************************************************/
											/***** Configure tuner for desired channel No. *****/
		case LX_DEMOD_TUNE_START:			/***************************************************/
			{


				if(RET_OK != DEMOD_M19_LGDBB_ISDB_SetDemod(pDemodInfo))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD M19 LGDBB] FAIL (%s:%d) DEMOD_M19_LGDBB_ISDB_SetDemod() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}

				#if 1   // FALSE(0x88) = only when using FPGA board , TRUE(0x08) = only when using SOC
				if(RET_OK != DEMOD_M19_ISDBT_TDI_Enable(TRUE))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD M19 LGDBB] FAIL (%s:%d) DEMOD_M19_TDI_Enable() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}
				#endif


				if(LX_DEMOD_TUNE_NORMAL != pDemodInfo->setCfgParam.isdbt.tuneMode)
				{

					if(RET_OK != DEMOD_M19_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_ON, &scanProcessing, &scanLock))
					{
						DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_M19_NeverlockScan() !!!\n", __F__, __L__);
						DEMOD_RETURN_FAIL(__F__);
					}
					pDemodInfo->controlState = LX_DEMOD_TUNE_SCAN;
					DEMOD_PRINT( "^R^[DEMOD] LX_DEMOD_TUNE_START : Going to LX_DEMOD_TUNE_SCAN..... ^0^\n");


				}
				else
				{

					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState = LX_DEMOD_SYNC_CHECKING;

					DEMOD_PRINT( "^R^[DEMOD] LX_DEMOD_TUNE_START : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
				}


			}

			break;


											/***************************************************/
											/***** Configure demod for scan mode. *****/
		case LX_DEMOD_TUNE_SCAN:			/***************************************************/
			{

				unsigned int currentTime = 0;
				unsigned int elapsedTime = 0;

				if((LX_DEMOD_FLAG_COMPLETE == pDemodInfo->scanJobFlag) || (LX_DEMOD_FLAG_FINISH == pDemodInfo->scanJobFlag))
				{

					pDemodInfo->controlState = LX_DEMOD_SIGNAL_STABLE;

					DEMOD_PRINT( "^c^[DEMOD] ERR (%s:%d) Already Done !!!\n", __F__, __L__);
					DEMOD_PRINT( "^R^[DEMOD] LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");

					return RET_OK;
				}

				if(RET_OK != DEMOD_M19_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_OFF, &scanProcessing, &scanLock))
				{
					DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_M19_NeverlockScan() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}

				if((LX_DEMOD_FLAG_FINISH == scanProcessing) && (LX_DEMOD_LOCKED == scanLock))
				{
					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState = LX_DEMOD_SYNC_CHECKING;

					DEMOD_PRINT( "^G^[DEMOD] (%s:%d) Signal is Found  !!!\n", __F__, __L__);
					DEMOD_PRINT( "^R^[DEMOD] LX_DEMOD_SYNC_CHECKING : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");

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

					DEMOD_PRINT_ALWAYS("\nLX_DEMOD_TUNE_SCAN : MSG_ISDBT_FRONT_END_NOT_LOCKED..\n") ;
					DEMOD_PRINT_ALWAYS("LX_DEMOD_TUNE_SCAN : Elapse time is %d msec\n", elapsedTime) ;


					DEMOD_PRINT( "^G^[DEMOD M19] (%s:%d) Signal is NOT Found  !!!\n", __F__, __L__);


				}
				else
				{
					pDemodInfo->scanJobFlag = LX_DEMOD_FLAG_ING;
					DEMOD_PRINT( "^G^[DEMOD] (%s:%d) Detection is on processing	!!!\n", __F__, __L__);
				}

			}
			break;

													/********************************************/
													/***** Attempting to finish the tuning state machine *****/
		case LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK :		/********************************************/
			{


			}
			break;
											/********************************************/
											/***** Attempting to obtain synch lock *****/
		case LX_DEMOD_SYNC_CHECKING : 		/********************************************/
			{

				LX_DEMOD_LOCK_STATE_T	lockState;

				if(RET_OK != DEMOD_M19_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
				{
					DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_M19_Get_Lock() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					pDemodInfo->controlState	= LX_DEMOD_SIGNAL_STABLE;
					pDemodInfo->unLockLongCount = 0;

					sigStablestartTime = jiffies_to_msecs(jiffies);

					DEMOD_PRINT( "^R^[DEMOD] LX_DEMOD_SYNC_CHECKING : Going to LX_DEMOD_SIGNAL_STABLE..... ^0^\n");
				}
				else
				{

#if 0 //yunj
					if(pDemodInfo->bNotifiedUnlock == TRUE)
					{

						pDemodInfo->unLockLongCount++;
						if((pDemodInfo->unLockLongCount & 0x3) == 0x3)
						{

							if(RET_OK != DEMOD_M19_ISDBT_SafetyReset())
							{
								DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_SoftwareReset() !!!\n", __F__, __L__);
								DEMOD_RETURN_FAIL(__F__);
							}
							DEMOD_PRINT("[DEMOD M19](%s) DEMOD_SoftwareReset() !!!\n", __F__);
						}
						if(pDemodInfo->unLockLongCount > 250) pDemodInfo->unLockLongCount = 1;


					}
#endif
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

				if(RET_OK != DEMOD_M19_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
				{
					DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_M19_Get_Lock() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
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
							if(RET_OK != DEMOD_M19_Get_Packet_Error(&packetError))
							{
								DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_M19_Get_Packet_Error() !!!\n", __F__, __L__);
								DEMOD_RETURN_FAIL(__F__);
							}
							else
							{
#if 0
								if(RET_OK != DEMOD_M19_ISDBT_Set_PhaseNoiseEnhancement(TRUE))
								{
									DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_M19_ISDBT_Set_PhaseNoiseEnhancement() !!!\n", __F__, __L__);
									DEMOD_RETURN_FAIL(__F__);
								}
#endif
								if(packetError < LX_DEMOD_PACKET_ERROR_THD)
								{
									pDemodInfo->bNotifiedLock	= TRUE;
									pDemodInfo->bNotifiedUnlock	= FALSE;
									pDemodInfo->lockStatus		= LX_DEMOD_LOCKED;
									pDemodInfo->signalStatus.bSignalValid = TRUE;

									if (RET_OK != DEMOD_M19_Get_CarrierFreqOffset(&freqOffset))
									{
										DEMOD_PRINT( "^r^[DEMOD] FAIL (%s:%d) DEMOD_M19_Get_CarrierFreqOffset() !!!\n", __F__, __L__);
										DEMOD_RETURN_FAIL(__F__);
									}
									pDemodInfo->freqOffset = freqOffset;

									pDemodInfo->controlState	= LX_DEMOD_SIGNAL_LOCKED;

									elapsedTime = jiffies_to_msecs(jiffies) - g_RetuneStartTime;

									DEMOD_PRINT_ALWAYS( "[DEMOD M19] LX_DEMOD_SIGNAL_STABLE : MSG_ISDBT_FRONT_END_LOCKED..... ^^^0^^^\n");
									DEMOD_PRINT_ALWAYS( "[DEMOD M19] LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^^^0^^^\n", elapsedTime);
									DEMOD_PRINT( "^R^[DEMOD M19] LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^^^0^^^\n", freqOffset);

									if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
									{
										DEMOD_PRINT( "^r^[DEMOD] FAIL (%s:%d) DEMOD_Get_CarrierFreqOffset() !!!\n", __F__, __L__);
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
									elapsedTime = jiffies_to_msecs(jiffies) - sigStablestartTime;
									if(elapsedTime > LX_DEMOD_LOCK_DEALY_100)
									{
										pDemodInfo->bNotifiedLock	= TRUE;
										pDemodInfo->bNotifiedUnlock = FALSE;
										pDemodInfo->lockStatus		= LX_DEMOD_LOCKED;
										pDemodInfo->signalStatus.bSignalValid = TRUE;

										if (RET_OK != DEMOD_M19_Get_CarrierFreqOffset(&freqOffset))
										{
											DEMOD_PRINT( "^r^[DEMOD] FAIL (%s:%d) DEMOD_M19_Get_CarrierFreqOffset() !!!\n", __F__, __L__);
											DEMOD_RETURN_FAIL(__F__);
										}
										pDemodInfo->freqOffset = freqOffset;

										pDemodInfo->controlState	= LX_DEMOD_SIGNAL_LOCKED;

										elapsedTime = jiffies_to_msecs(jiffies) - g_RetuneStartTime;

										DEMOD_PRINT_ALWAYS( "[DEMOD M19][0720] LX_DEMOD_SIGNAL_STABLE : MSG_ISDBT_FRONT_END_LOCKED..... ^^0^^\n");
										DEMOD_PRINT_ALWAYS( "[DEMOD M19] LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^^0^^\n", elapsedTime);
										DEMOD_PRINT( "^R^[DEMOD M19] LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^^0^^\n", freqOffset);

										if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
										{
											DEMOD_PRINT( "^r^[DEMOD] FAIL (%s:%d) DEMOD_Get_CarrierFreqOffset() !!!\n", __F__, __L__);
											DEMOD_RETURN_FAIL(__F__);
										}
										if (RET_OK != DEMOD_Get_signal_status(pDemodInfo))
										{
											DEMOD_PRINT( "^r^[DEMOD M19] FAIL (%s:%d) DEMOD_Get_signal_status() !!!\n", __F__, __L__);
											DEMOD_RETURN_FAIL(__F__);
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

						if (RET_OK != DEMOD_M19_Get_CarrierFreqOffset(&freqOffset))
						{
							DEMOD_PRINT( "^r^[DEMOD] FAIL (%s:%d) DEMOD_M19_Get_CarrierFreqOffset() !!!\n", __F__, __L__);
							DEMOD_RETURN_FAIL(__F__);
						}
						pDemodInfo->freqOffset = freqOffset;

						pDemodInfo->controlState	= LX_DEMOD_SIGNAL_LOCKED;

						elapsedTime = jiffies_to_msecs(jiffies) - g_RetuneStartTime;


						DEMOD_PRINT_ALWAYS( "[DEMOD M19] LX_DEMOD_SIGNAL_STABLE : MSG_ISDBT_FRONT_END_LOCKED..... ^0^\n");
						DEMOD_PRINT_ALWAYS( "[DEMOD M19] LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^0^\n", elapsedTime);
						DEMOD_PRINT( "^R^[DEMOD M19] LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^0^\n", freqOffset);

						if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
						{
							DEMOD_PRINT( "^r^[DEMOD] FAIL (%s:%d) DEMOD_Get_CarrierFreqOffset() !!!\n", __F__, __L__);
							DEMOD_RETURN_FAIL(__F__);
						}
						if (RET_OK != DEMOD_Get_signal_status(pDemodInfo))
						{
							DEMOD_PRINT( "^r^[DEMOD M19] FAIL (%s:%d) DEMOD_Get_signal_status() !!!\n", __F__, __L__);
							DEMOD_RETURN_FAIL(__F__);
						}

					}




				}
				else
				{
					pDemodInfo->controlState	= LX_DEMOD_SYNC_CHECKING;
					DEMOD_PRINT( "^R^[DEMOD] LX_DEMOD_SYNC_CHECKING : Going back to LX_DEMOD_SYNC_CHECKING..... **;\n");

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
 * DEMOD_M19_ISDBT_Monitoring_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_M19_ISDBT_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{

	LX_DEMOD_LOCK_STATE_T			lockState;
	unsigned int			powerOnElapsedTime;


	if(RET_OK != DEMOD_M19_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
	{
		DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_Get_Lock() !!!\n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}
#if 0
	DEMOD_PRINT( " pDemodInfo->lockStatus = %d, pDemodInfo->bNotifiedLock = %d, (lockCount = %d) \n",pDemodInfo->lockStatus,pDemodInfo->bNotifiedLock,pDemodInfo->lockCount);
	DEMOD_PRINT( " pDemodInfo->lockStatus = %d, pDemodInfo->bNotifiedUnlock = %d,(unlockCnt = %d) \n",pDemodInfo->lockStatus,pDemodInfo->bNotifiedUnlock,pDemodInfo->unLockCount);
	DEMOD_PRINT( " lockState = %d) \n",lockState);
#endif
	if(LX_DEMOD_LOCKED == lockState)
	{
		pDemodInfo->unLockCount = 0;
		pDemodInfo->unLockLongCount	= 0;

//		if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
//			pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;

		if (RET_OK != _DEMOD_M19_LGDBB_ISDB_CheckSignalState(pDemodInfo))
		{
			DEMOD_PRINT( "^r^[DEMOD M19] FAIL (%s:%d) DEMOD_Get_signal_status() !!!\n", __F__, __L__);
			DEMOD_RETURN_FAIL(__F__);
		}

		if(pDemodInfo->signalStatus.packetError >= _gM19GBB_FullISDBTPkerrThreshold)
		{
			_gM19GBB_VQI_UnlockCount_full_packeterr++;
			DEMOD_PRINT( "^r^[DEMOD M19](%s) _gM19GBB_VQI_UnlockCount_full_packeterr = %d !!!\n", __F__,_gM19GBB_VQI_UnlockCount_full_packeterr);

			if(_gM19GBB_VQI_UnlockCount_full_packeterr == _gM19GBB_FullVQIPkerrCount)
			{
				DEMOD_PRINT( "^r^[DEMOD M19] oops !! (%s) Force to NOT LOCK !!\n", __F__);

				_gM19GBB_VQI_UnlockCount_full_packeterr = 0;


				if(RET_OK != DEMOD_M19_ISDBT_SafetyReset())
				{
					DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_ISDBT_SafetyReset() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}
				DEMOD_PRINT("[DEMOD M19](%s) DEMOD_SoftwareReset() !!!\n", __F__);

				pDemodInfo->lockStatus		= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedUnlock = TRUE;
				pDemodInfo->bNotifiedLock	= FALSE;
				pDemodInfo->signalStatus.bSignalValid = FALSE;

			}

		}
		else
		{
			_gM19GBB_VQI_UnlockCount_full_packeterr = 0;

			if(gM19GBB_PowerOnInit == 2)
			{

				powerOnElapsedTime = jiffies_to_msecs(jiffies) - gM19GBB_PowerOnInitStartTimeISDBT;

				DEMOD_PRINT("[DEMOD M19](%s:%d) powerOnElapsedTime = %d !!!\n", __F__, __L__,powerOnElapsedTime);

				if(powerOnElapsedTime >= 15000)
				{
					gM19GBB_PowerOnInit = 0;

					if (RET_OK != DEMOD_M19_ISDBT_Set_CrGearshEn(TRUE ))
					{
						DEMOD_PRINT("[DEMOD M19] FAIL (%s:%d) DEMOD_M19_ISDBT_Set_CrGearshEn() !!!\n", __F__, __L__);
						DEMOD_RETURN_FAIL(__F__);
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

					DEMOD_PRINT_ALWAYS( "[DEMOD M19] MONITORING FUNC : MSG_ISDBT_FRONT_END_LOCKED..... ^0^\n");

				if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
					pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;

			}
			if(pDemodInfo->lockCount >= 1)
			{
				pDemodInfo->lockCount = 0;
			}

#if 0
			if(RET_OK != DEMOD_M19_ISDBT_Set_PhaseNoiseEnhancement(TRUE))
			{
				DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_M19_ISDBT_Set_PhaseNoiseEnhancement() !!!\n", __F__, __L__);
				DEMOD_RETURN_FAIL(__F__);
			}
#endif



			if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
			{
				DEMOD_PRINT( "^r^[DEMOD M19] FAIL (%s:%d) DEMOD_Get_TunedCFG() !!!\n", __F__, __L__);
				DEMOD_RETURN_FAIL(__F__);
			}

		}

	}

	else
	{
		pDemodInfo->lockCount = 0;
		_gM19GBB_VQI_UnlockCount_full_packeterr = 0;

		if(pauseTimeDemod != LX_DEMOD_LOCK_FAIL_PAUSE_TIME )
			pauseTimeDemod = LX_DEMOD_LOCK_FAIL_PAUSE_TIME;

		if((LX_DEMOD_UNLOCKED != pDemodInfo->lockStatus)  && (TRUE != pDemodInfo->bNotifiedUnlock))
		{
			pDemodInfo->unLockCount++;

			if(pDemodInfo->unLockCount == 2)
			{
				pDemodInfo->lockStatus 		= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedUnlock = TRUE;
				pDemodInfo->bNotifiedLock	= FALSE;
				pDemodInfo->signalStatus.bSignalValid = FALSE;

				if(RET_OK != DEMOD_M19_ISDBT_SafetyReset())
				{
					DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_M19_ISDBT_SafetyReset() !!!\n", __F__, __L__);
					DEMOD_RETURN_FAIL(__F__);
				}


				DEMOD_PRINT_ALWAYS( "[DEMOD M19] MONITORING FUNC : MSG_ISDBT_FRONT_END_NOT_LOCKED..... -_-\n");

			}
			if(pDemodInfo->unLockCount >= 2)
			{
				pDemodInfo->unLockCount = 0;
			}
		}




	}


	return RET_OK;



}


#if 0
#endif




#if 0
#endif











#if 0
#endif

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_QAM_SoftwareResetFEC.
 * Reset QAM FEC module.
 *
 * @param [in] NONE
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_QAM_SoftwareResetFEC(void)
{

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_QAM_Monitor.
 * Monitoring
 *
 * @param  NONE [IN] void .
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_M19_QAM_Monitor(void)
{

	return RET_OK;

}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_QAM_ModeAutoDetection.
 * Enable/Disable the detection of QAM mode
 *
 * @param  bEnable [IN] - BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR.
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_QAM_ModeAutoDetection(BOOLEAN bEnable)
{


	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_QAM_64Mode.
 * Set the QAM mode to QAM64 manually
 *
 * @param  NONE [IN/OUT].
 * @return if Succeeded - RET_OK else-RET_ERROR.
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_QAM_64Mode(void)
{

	return RET_OK;


}
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_QAM_256Mode.
 * Set the QAM mode to QAM256 manually
 *
 * @param  NONE [IN/OUT].
 * @return if Succeeded - RET_OK else-RET_ERROR.
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_QAM_256Mode(void)
{


	return RET_OK;

}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_QAM_Set_DefaultRegisterValue.
 * Initialize LG1150 GBB for QAM mode.
 *
 * @param  NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR.
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_QAM_Set_DefaultRegisterValue(void)
{


	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_QAM_Set_NeverLockWaitTime
 * Set neverlock waiting period.
 *
 * @param waitMs 	[IN] UINT32 - unit: ms
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_QAM_Set_NeverLockWaitTime(UINT32 waitMs)
{

	return RET_OK;


}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_QAM_Get_TotalInfo
 * Get all information on QAM for debug
 *
 * @param NONE [IN / OUT].
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_QAM_Get_TotalInfo( void)
{

	return RET_OK;

}



/**
 * DEMOD_M19_QAM_EQ_Signal_Detector.
 * Disable no signal detector function
 *
 * @param [in] NONE
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_QAM_EQ_Signal_Detector(BOOLEAN OnOff)
{

	return RET_OK;

}



/**
 * DEMOD_M19_QAM_Set_Frame_resynchronizaiton.
 * Disable frame sync position auto re-synchronizaiton
 *
 * @param [in] NONE
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_QAM_Set_Frame_resynchronizaiton(BOOLEAN OnOff)
{

	return RET_OK;

}


#if 0
#endif



/**
 * DEMOD_M19_ISDBT_SetDefaultRegisterValue
 * Set defualt register value on DVB-T.
 *
 * @param none
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/


int DEMOD_M19_ISDBT_Set_DefaultRegisterValue(void)
{

	return RET_OK;

}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_ISDBT_Set_Config_auto
 * Control automatic setting of DVB-T config.
 *
 * @param bAutoDetect 	[IN] BOOLEAN - automatic setting (TRUE) / manual setting(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_ISDBT_Set_Config_auto (BOOLEAN bAutoDetect)

{

	return RET_OK;


}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_ISDBT_Set_PartialConfig
 * Set hierachical signal path and bandwidth.
 * This function is used when DEMOD_M19_ISDBT_Set_Config_auto is enabled.
 *
 * @param *pIsdbtConfigParam 	[IN] LX_DEMOD_ISDBT_CONFIG_T - ISDBT config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_ISDBT_Set_PartialConfig (LX_DEMOD_ISDBT_CONFIG_T *pIsdbtConfigParam)
{


	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_ISDBT_Set_FullConfig
 * Set all config parameters on DVB-T.
 * This function is used when DEMOD_M19_ISDBT_Set_Config_auto is disabled.
 *
 * @param *pIsdbtConfigParam 	[IN] LX_DEMOD_ISDBT_CONFIG_T - ISDB-T config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_ISDBT_Set_FullConfig (LX_DEMOD_ISDBT_CONFIG_T *pIsdbtConfigParam)
{

	return RET_OK;

}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_ISDBT_Set_NeverLockWaitTime
 * Set neverlock waiting period.
 *
 * @param waitMs 	[IN] UINT32 - unit: ms
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_ISDBT_Set_NeverLockWaitTime(UINT32 waitMs)
{

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_ISDBT_Set_CrGearshEn
 * enable/disable Carrier recovery bandwidth gear shift
 *
 * @param bEnable 	[IN] BOOLEAN
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_ISDBT_Set_CrGearshEn(BOOLEAN bEnable)
{

	return RET_OK;

}



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_ISDBT_Set_PhaseNoiseEnhancement
 * Get delay spread state on ISDBT.
 *
 * @param [IN] bEnhanced - BOOLEAN 	[OUT] UINT16.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_ISDBT_Set_PhaseNoiseEnhancement(BOOLEAN bEnhanced)
{

	return RET_OK;

}



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_ISDBT_Get_DelaySpreadStatus
 * Get delay spread state on ISDB-T.
 *
 * @param *pDelaySpread 	[OUT] UINT16.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_ISDBT_Get_DelaySpreadStatus(UINT16 *pDelaySpread)
{

	return RET_OK;


}




/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_ISDBT_Get_FFTMode
 * Get the information of bandwidth on ISDB-T.
 *
 * @param *pTxModeLock 	[OUT] LX_DEMOD_LOCK_STATE_T - FFT mode lock state.
 * @param *pFftMode 	[OUT] LX_DEMOD_FFTMODE_T - detected FFT mode.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_ISDBT_Get_FFTMode( LX_DEMOD_LOCK_STATE_T *pTxModeLock, LX_DEMOD_FFTMODE_T *pFftMode )
{

	LX_DEMOD_DD_ISDBT_STATUS_CMD_REPLY_struct	isdbt_status;
	LX_DEMOD_L2_Context 	*pFrontend;
//	LX_DEMOD_LOCK_STATE_T	lockState;

//	UINT8	modelock_di;
//	UINT8	fftmoder_di_1_0;
	LX_DEMOD_L2_TMCC_INFO tmcc;

	UINT8 ret;

	pFrontend = &gM19_LGDBB_Frontend;

	isdbt_status		= pFrontend->demod->rsp->isdbt_status;

	*pTxModeLock = LX_DEMOD_UNLOCKED;
	*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN;

	#if 0
	if(RET_OK != DEMOD_M19_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
	{
		DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_M19_Get_Lock() !!!\n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}
	#endif

	#if 0
	if(RET_OK != DEMOD_L2_ISDB_Get_TMCC_Info(pFrontend, &tmcc))
	{
		DEMOD_PRINT_ALWAYS( "(%s) FAIL, DEMOD_L2_ISDB_Get_TMCC_Info() \n", __F__);
		return RET_ERROR;
	}
	#endif

	ret = DEMOD_L2_ISDB_Get_TMCC_Info(pFrontend, &tmcc);

	if(RET_OK != ret)
	{
		DEMOD_PRINT_ALWAYS( "(%s) FAIL, DEMOD_L2_ISDB_Get_TMCC_Info() [%d] \n", __F__, ret);
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



	switch (tmcc.fft_mode)
	{
		case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_FFT_MODE_2K :
			*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_2K;
			break;

		case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_FFT_MODE_8K:
			*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_8K;
			break;

		case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_FFT_MODE_4K:
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
 * DEMOD_M19_ISDBT_Get_GuradIntervalMode
 * Get the information of guard interval on ISDB-T.
 *
 * @param *pGIMode 	[OUT] LX_DEMOD_GIMODE_T - 1/32, 1/16, 1/8 and 1/4.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_ISDBT_Get_GuradIntervalMode( LX_DEMOD_GIMODE_T *pGIMode )
{

	LX_DEMOD_DD_ISDBT_STATUS_CMD_REPLY_struct	isdbt_status;
	LX_DEMOD_L2_Context 	*pFrontend;

//	LX_DEMOD_LOCK_STATE_T	lockState;
	LX_DEMOD_L2_TMCC_INFO 	tmcc;
	UINT8	ret;
	
	pFrontend = &gM19_LGDBB_Frontend;

	isdbt_status		= pFrontend->demod->rsp->isdbt_status;

	*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_UNKNOWN;


	#if 0
	if(RET_OK != DEMOD_M19_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
	{
		DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_M19_Get_Lock() !!!\n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}

	#endif

	#if 0
	if(RET_OK != DEMOD_L2_ISDB_Get_TMCC_Info(pFrontend, &tmcc))
	{
		DEMOD_PRINT_ALWAYS( "(%s) FAIL, DEMOD_L2_ISDB_Get_TMCC_Info() \n", __F__);
		return RET_ERROR;
	}

	#endif


	ret = DEMOD_L2_ISDB_Get_TMCC_Info(pFrontend, &tmcc);

	if(RET_OK != ret)
	{
		DEMOD_PRINT_ALWAYS( "(%s) FAIL, DEMOD_L2_ISDB_Get_TMCC_Info() [%d] \n", __F__, ret);
		return RET_ERROR;
	}


	if (tmcc.isLock != LX_DEMOD_LOCKED)
	{
		*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_UNKNOWN;

		return RET_OK;
	}


	switch (tmcc.gi)
	{
		case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_1_4 :
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

		default :
			*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_UNKNOWN;
			break;
	}

	return RET_OK;

}



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_ISDBT_Get_TMCCInfo
 * Get TPS information on ISDBT
 *
 * @param *pTpsParams [OUT] LX_DEMOD_ISDBT_TMCC_CONFIG_T - TMCC data structure.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_ISDBT_Get_TMCCInfo( LX_DEMOD_ISDBT_TMCC_CONFIG_T *pTmccParams)
{

	LX_DEMOD_DD_ISDBT_STATUS_CMD_REPLY_struct   isdbt_status;
	LX_DEMOD_L2_Context	  *pFrontend;
//	LX_DEMOD_LOCK_STATE_T   lockState;
	LX_DEMOD_L2_TMCC_INFO 	tmcc;

	UINT8	ret;
	
	pFrontend = &gM19_LGDBB_Frontend;

	isdbt_status = pFrontend->demod->rsp->isdbt_status;

	ret = DEMOD_L2_ISDB_Get_TMCC_Info(pFrontend, &tmcc);

	if(RET_OK != ret)
	{
	  DEMOD_PRINT_ALWAYS( "(%s) FAIL, DEMOD_L2_ISDB_Get_TMCC_Info() [%d] \n", __F__, ret);
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

	  switch (tmcc.codeRate_a)
	  {
		  case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_1_2  :
		  		pTmccParams->layerACodeRate = LX_DEMOD_CODE_1_2;
		  break;

		  case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_2_3  :
		  		pTmccParams->layerACodeRate = LX_DEMOD_CODE_2_3;
		  break;

		  case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_3_4  :
		  		pTmccParams->layerACodeRate = LX_DEMOD_CODE_3_4;
		  break;

		  case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_5_6  :
		  		pTmccParams->layerACodeRate = LX_DEMOD_CODE_5_6;
		  break;

		  case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_7_8  :
		  		pTmccParams->layerACodeRate = LX_DEMOD_CODE_7_8;
		  break;

		  default:
		  		pTmccParams->layerACodeRate = LX_DEMOD_CODE_UNKNOWN;
			  break;

	  }

	  switch (tmcc.qamMode_a)
	  {
		  case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_DQPSK  :
		  		pTmccParams->layerAQamMode = LX_DEMOD_DQPSK ;
		  break;
		  case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QPSK  :
		  		pTmccParams->layerAQamMode = LX_DEMOD_QPSK;
		  break;

		  case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16  :
		  		pTmccParams->layerAQamMode = LX_DEMOD_16QAM;
		  break;

		  case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64  :
		  		pTmccParams->layerAQamMode = LX_DEMOD_64QAM;
		  break;

		  default  :
		  		pTmccParams->layerAQamMode = LX_DEMOD_UNKOWN_MODE;
		  break;
	  }


  }

  else if((tmcc.segNum_b > tmcc.segNum_a) && (tmcc.segNum_b > tmcc.segNum_c))
  {

	  switch (tmcc.codeRate_b)
	  {
		  case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_1_2  :
		  		pTmccParams->layerBCodeRate = LX_DEMOD_CODE_1_2;
		  break;

		  case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_2_3  :
		  		pTmccParams->layerBCodeRate = LX_DEMOD_CODE_2_3;
		  break;

		  case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_3_4  :
		  		pTmccParams->layerBCodeRate = LX_DEMOD_CODE_3_4;
		  break;

		  case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_5_6  :
		  		pTmccParams->layerBCodeRate = LX_DEMOD_CODE_5_6;
		  break;

		  case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_7_8  :
		  		pTmccParams->layerBCodeRate = LX_DEMOD_CODE_7_8;
		  break;

		  default:
		  		pTmccParams->layerBCodeRate = LX_DEMOD_CODE_UNKNOWN;
			  break;

	  }

	  switch (tmcc.qamMode_b)
	  {
		  case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_DQPSK  :
		  		pTmccParams->layerBQamMode = LX_DEMOD_DQPSK ;
		  break;
		  case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QPSK  :
		  		pTmccParams->layerBQamMode = LX_DEMOD_QPSK;
		  break;

		  case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16  :
		  		pTmccParams->layerBQamMode = LX_DEMOD_16QAM;
		  break;

		  case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64  :
		  		pTmccParams->layerBQamMode = LX_DEMOD_64QAM;
		  break;

		  default  :
		  		pTmccParams->layerBQamMode = LX_DEMOD_UNKOWN_MODE;
		  break;
	  }

  }
  else if((tmcc.segNum_c > tmcc.segNum_a) && (tmcc.segNum_c > tmcc.segNum_b))
  {

	  switch (tmcc.codeRate_c)
	  {
		  case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_1_2  :
		  		pTmccParams->layerCCodeRate = LX_DEMOD_CODE_1_2;
		  break;

		  case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_2_3  :
		  		pTmccParams->layerCCodeRate = LX_DEMOD_CODE_2_3;
		  break;

		  case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_3_4  :
		  		pTmccParams->layerCCodeRate = LX_DEMOD_CODE_3_4;
		  break;

		  case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_5_6  :
		  		pTmccParams->layerCCodeRate = LX_DEMOD_CODE_5_6;
		  break;

		  case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_7_8  :
		  		pTmccParams->layerCCodeRate = LX_DEMOD_CODE_7_8;
		  break;

		  default:
		  		pTmccParams->layerCCodeRate = LX_DEMOD_CODE_UNKNOWN;
			  break;

	  }


	  switch (tmcc.qamMode_c)
	  {
		  case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_DQPSK  :
		  		pTmccParams->layerCQamMode = LX_DEMOD_DQPSK ;
		  break;
		  case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QPSK  :
		  		pTmccParams->layerCQamMode = LX_DEMOD_QPSK;
		  break;

		  case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16  :
		  		pTmccParams->layerCQamMode = LX_DEMOD_16QAM;
		  break;

		  case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64  :
		  		pTmccParams->layerCQamMode = LX_DEMOD_64QAM;
		  break;

		  default  :
		  		pTmccParams->layerCQamMode = LX_DEMOD_UNKOWN_MODE;
		  break;
	  }

  }
  else
  {
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
 * DEMOD_M19_ISDBT_Get_TotalInfo
 * Get all information on ISDB-T for debug
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_ISDBT_Get_TotalInfo( void)
{
	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_ISDBT_Get_IFO_LOCK
 * Get IFO lock on ISDB-T.
 *
 * @param *pSnr [OUT] BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_ISDBT_Get_IFO_LOCK( BOOLEAN *pIfoLock)
{

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_ISDBT_Get_CochanDetIndicator
 * Get co-channel detection indicator  on ISDB-T.
 *
 * @param *pDetStatus  [OUT] BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_ISDBT_Get_CochanDetIndicator( BOOLEAN *pDetStatus)
{


	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_ISDBT_EqualizereReset.
 * Reset DVB EQ module by software.
 *
 * @param  NONE
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_ISDBT_EqualizereReset(void)
{

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_ISDBT_SafetyReset.
 * Reset ISDB-T module by software.
 *
 * @param  NONE
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_ISDBT_SafetyReset(void)
{

#if 0
	DEMOD_M19_FecReset(TRUE);
	OS_MsecSleep(5);

	if(RET_OK != DEMOD_M19_SoftwareReset())
	{
		DEMOD_PRINT("[DEMOD M19 GBB] FAIL (%s:%d) DEMOD_M19_SoftwareReset() !!!\n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}

	OS_MsecSleep(5);
	DEMOD_M19_FecReset(FALSE);

#endif


	return RET_OK;


}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_ISDBT_MemoryBusCheck.
 * Check ISDB-T memory Bus.
 *
 * @param  NONE
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_ISDBT_MemoryBusCheck(void)
{


//	UINT32 busCountSec = 0xBCD3D80; //1sec
//	UINT32 busCountSec = 0x179A7B00; //2ssec

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

		printk("**********************************************************   \n");
		printk("*********** M1 Bus DEAD **********************************   \n");
		printk("**********  M1 Bus DEAD **********************************   \n");
		printk("**********  M1 Bus DEAD **********************************   \n");
		printk("**********************************************************	 \n");

	}

	return RET_OK;


}


int DEMOD_M19_ISDBT_Set_MemBus_flushing(void)
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
		printk("###################chungiii(%s:%d) check flush_end = %d  \n",__F__, __L__, flush_end);
		if (flush_end) break;
		} while (1);

	bflush = 0x0;
	SYS_IO_WriteRegArray(0xc830E548  , 4, &bflush);

	bus_gating = 0x3;
	SYS_IO_WriteRegArray(0xc830E540 , 4, &bus_gating);


	return RET_OK;
}


#if 0
#endif


#if 1
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_VSB_Set_DefaultRegisterValue.
 * Initialize GBB VSB module .
 *
 * @param  NONE [IN] void
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_VSB_Set_DefaultRegisterValue(void)
{
	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_VSB_Set_NeverLockWaitTime
 * Set neverlock waiting period.
 *
 * @param waitMs 	[IN] UINT32 - unit: ms
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_VSB_Set_NeverLockWaitTime(UINT32 waitMs)
{
	return RET_OK;
}



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_VSB_CochannelExist.
 * Get the informantion if co-channel(NTSC) signal exists or not on VSB mode.
 *
 * @param  *pCochannel [OUT] BOOLEAN - exists /doesn't exist.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_VSB_CochannelExist(BOOLEAN *pCochannel)
{
	return RET_OK;
}






/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_VSB_PreMonitor.
 * Set registers against  various noise conditions before  monitoring.
 *
 * @param  NONE [IN] void .
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/


int DEMOD_M19_VSB_PreMonitor(void)
{

	DEMOD_TRACE("[DEMOD M19 DTV] @ %s =====\n",__F__);

	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_VSB_Monitor.
 * Monitoring
 *
 * @param  NONE [IN] void .
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_M19_VSB_Monitor(DEMOD_CTX_T *pDemodInfo)
{

	return RET_OK;


}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_VSB_Get_MSEdynStatus.
 * Get the flag whether MSE would be under operation limit (snr > 16dB : TRUE)
 *
 * @param  *pbEnable [OUT] BOOLEAN - get signal noise ratio
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_M19_VSB_Get_MSEdynStatus(BOOLEAN *pbEnable)
{

	return RET_OK;


}





/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M19_VSB_Get_TotalInfo
 * Get all information on VSB for debug
 *
 * @param NONE [IN].
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M19_VSB_Get_TotalInfo( void)
{

	return RET_OK;

}

#endif




#if 0
#endif

int DEMOD_M19_LGDBB_VSB_SetDemod_Simple(void)
{
	LX_DEMOD_L2_Context 	*pFrontend;
	UINT8	new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_NORMAL;
	UINT32	freq_Khz;
	UINT16	ter_bandwidth_KHz = 6000;

	pFrontend		= &gM19_LGDBB_Frontend;

	freq_Khz = 0;

	//printk("[O18 LGDBB][0716] ################### chungiii SetDemod VSB \n");

	DEMOD_L2_ATSC_Set_demod(pFrontend,
							DEMOD_DD_MODE_PROP_MODULATION_VSB,
							freq_Khz,
							new_tuneMode,
							DEMOD_DD_MODE_PROP_SPECINV_MANUAL,
							DEMOD_DD_MODE_PROP_SPECINV_NORMAL,
							ter_bandwidth_KHz,
							0
							);

	return RET_OK;
	
}




#if 0
#endif








