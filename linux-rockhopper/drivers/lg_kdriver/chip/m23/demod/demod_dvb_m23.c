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
#define DEMOD_TAG "[M23.DVB] "

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
#include <linux/delay.h>

#include <linux/timer.h>

#include "demod_impl.h"
#include "demod_common_m23.h"
#include "demod_dvb_m23.h"

/***********************************************************************************
	Global Type Definitions
 ************************************************************************************/
extern UINT8 	gLGDBB_PowerOnInit;

/***********************************************************************************
	Static Variable & Function Prototypes Declarations
 ************************************************************************************/
static UINT32 _PowerOnInitSTartTime	= 0;

const static UINT8  _DVBC_Unlock_Count_Threshold = 4 * THR_ADJ;
const static UINT8  _DVBT_Unlock_Count_Threshold = 4 * THR_ADJ;
const static UINT8  _DVBT2_Unlock_Count_Threshold = 4 * THR_ADJ;

static UINT16 _DVB_Full_Pkerr_Count	= 0;

const static UINT16 _DVBC_Full_Pkerr_Count_Threshold = 9 * THR_ADJ;// orignal value is 9
const static UINT16 _DVBT_Full_Pkerr_Count_Threshold = 9 * THR_ADJ;// orignal value is 9
const static UINT16 _DVBT2_Full_Pkerr_Count_Threshold = 12 * THR_ADJ;// orignal value is 9

static UINT16 _DVB_Full_Pkerr_Threshold	= DVB_FULL_PACKET_ERROR;

int _DEMOD_M23_DVBC_CheckTuneMode (DEMOD_CTX_T *pDemodInfo)
{
	UINT8  new_tuneMode;

	switch (pDemodInfo->setCfgParam.dvbc.tuneMode)
	{
		case	LX_DEMOD_TUNE_NORMAL:			new_tuneMode = DEMOD_PROP_MODE_TUNE_NORMAL; break;
		case	LX_DEMOD_TUNE_AUTO: 			new_tuneMode = DEMOD_PROP_MODE_TUNE_AUTO; break;
		case	LX_DEMOD_TUNE_MANUAL: 			new_tuneMode = DEMOD_PROP_MODE_TUNE_MANUAL ; break;
		case	LX_DEMOD_TUNE_SPEC_DVBC_FIXED_DATA:	new_tuneMode = DEMOD_PROP_MODE_TUNE_FIXED_DATA; break;

		default:					new_tuneMode = DEMOD_PROP_MODE_TUNE_AUTO; break;
	}

	return new_tuneMode;
}

int _DEMOD_M23_DVBT_CheckTuneMode (DEMOD_CTX_T *pDemodInfo)
{
	UINT8  new_tuneMode;

	switch (pDemodInfo->setCfgParam.dvbt.tuneMode)
	{
		case	LX_DEMOD_TUNE_NORMAL:			new_tuneMode = DEMOD_PROP_MODE_TUNE_NORMAL; break;
		case	LX_DEMOD_TUNE_AUTO: 			new_tuneMode = DEMOD_PROP_MODE_TUNE_AUTO; break;
		case	LX_DEMOD_TUNE_MANUAL: 			new_tuneMode = DEMOD_PROP_MODE_TUNE_MANUAL ; break;
		case	LX_DEMOD_TUNE_SPEC_DVBC_FIXED_DATA:	new_tuneMode = DEMOD_PROP_MODE_TUNE_FIXED_DATA; break;

		default:					new_tuneMode = DEMOD_PROP_MODE_TUNE_AUTO; break;
	}
	return new_tuneMode;
}

int _DEMOD_M23_DVBT2_CheckTuneMode (DEMOD_CTX_T *pDemodInfo)
{
	UINT8  new_tuneMode;

	switch (pDemodInfo->setCfgParam.dvbt2.tuneMode)
	{
		case	LX_DEMOD_TUNE_NORMAL:			new_tuneMode = DEMOD_PROP_MODE_TUNE_NORMAL; break;
		case	LX_DEMOD_TUNE_AUTO: 			new_tuneMode = DEMOD_PROP_MODE_TUNE_AUTO; break;
		case	LX_DEMOD_TUNE_MANUAL: 			new_tuneMode = DEMOD_PROP_MODE_TUNE_MANUAL ; break;
		case	LX_DEMOD_TUNE_SPEC_DVBC_FIXED_DATA:	new_tuneMode = DEMOD_PROP_MODE_TUNE_FIXED_DATA; break;

		default:					new_tuneMode = DEMOD_PROP_MODE_TUNE_AUTO; break;
	}
	return new_tuneMode;
}

int _DEMOD_M23_DVBC_SetDemod (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_L2_Context *	pFrontend;

	UINT8  			dvbt_hpSel;
	UINT8  			dvb_c_constellation;
	UINT8  			new_tuneMode;

	UINT32 			freq_Khz = 0;
	UINT16 			dvb_c_bandwidth_Khz = 0;
	UINT16 			symbol_rate_Kbps = 0;

	pFrontend 		= DEMOD_Get_LGDBB_Context();

	dvbt_hpSel 		= DEMOD_PROP_DVBT_HIERARCHY_HIERHPSEL_HIGH;
	new_tuneMode 		= _DEMOD_M23_DVBC_CheckTuneMode(pDemodInfo);
	symbol_rate_Kbps 	= pDemodInfo->setCfgParam.dvbc.symbolRate;// KSym/s

	if(RET_OK != DEMOD_M23_Get_BW(pDemodInfo, &dvb_c_bandwidth_Khz))
	{
		DEMOD_ERROR("Fail, DEMOD_M23_Get_BW()\n");
		return RET_ERROR;
	}
	 DEMOD_PRINT("bandwidth_KHz[%d]\n", dvb_c_bandwidth_Khz);

	if (pDemodInfo->setCfgParam.dvbc.tuneMode == LX_DEMOD_TUNE_AUTO_FULL)
	{
		DEMOD_PRINT("tuneMode is LX_DEMOD_TUNE_AUTO_FULL\n");
		pFrontend->cable_blind_scan = TRUE;
	}
	else
	{
		pFrontend->cable_blind_scan = FALSE;
	}

	switch (pDemodInfo->setCfgParam.dvbc.qamMode)
	{

		case LX_DEMOD_16QAM:
			dvb_c_constellation = DEMOD_CONSTELLATION_QAM16;
			break;

		case LX_DEMOD_32QAM:
			dvb_c_constellation = DEMOD_CONSTELLATION_QAM32;
			break;

		case LX_DEMOD_64QAM:
			dvb_c_constellation = DEMOD_CONSTELLATION_QAM64;
			break;

		case LX_DEMOD_128QAM:
			dvb_c_constellation = DEMOD_CONSTELLATION_QAM128;
			break;

		case LX_DEMOD_256QAM:
			dvb_c_constellation = DEMOD_CONSTELLATION_QAM256;
			break;

		default:
			dvb_c_constellation = DEMOD_CONSTELLATION_UNKNOWN;
			break;
	}

	DEMOD_L2_DVB_Set_demod(	pFrontend,
				DEMOD_MODULATION_DVBC,
				freq_Khz,
				new_tuneMode,
				DEMOD_PROP_MODE_SPECINVAUTO_MANUAL,
				DEMOD_PROP_MODE_SPECINV_NORMAL,
				dvb_c_bandwidth_Khz,
				dvbt_hpSel,
				symbol_rate_Kbps,
				dvb_c_constellation,
				0,
				DEMOD_PROP_DVBT2_MODE_LOCK_MODE_BASE_ONLY); // T2-Base
	return RET_OK;

}

int _DEMOD_M23_DVBT_SetDemod (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_L2_Context *	pFrontend;

	UINT8  			standard;
	UINT8  			dvbt_hpSel;
	UINT8  			dvb_t_constellation;
	UINT8  			new_tuneMode;
	UINT16			dvbt2_PLPId;

	UINT32 			freq_Khz = 0;
	UINT16 			dvb_t_bandwidth_Khz = 0;
	UINT16 			symbol_rate_Kbps = 0;

	pFrontend 		= DEMOD_Get_LGDBB_Context();

	standard 		= DEMOD_MODULATION_DVBT;
	dvbt_hpSel		= DEMOD_PROP_DVBT_HIERARCHY_HIERHPSEL_HIGH;
	dvb_t_constellation	= DEMOD_CONSTELLATION_UNKNOWN;
	dvbt2_PLPId		= 255;

	new_tuneMode		= _DEMOD_M23_DVBT_CheckTuneMode(pDemodInfo);

	DEMOD_NOTI("Start\n");

	if(RET_OK != DEMOD_M23_Get_BW(pDemodInfo, &dvb_t_bandwidth_Khz))
	{
		DEMOD_ERROR("Fail, DEMOD_M23_Get_BW()\n");
		return RET_ERROR;
	}
	 DEMOD_PRINT("dvb_t_bandwidth_Khz %d\n", dvb_t_bandwidth_Khz);

	dvbt_hpSel = (pDemodInfo->setCfgParam.dvbt.bSetHp) ? DEMOD_PROP_DVBT_HIERARCHY_HIERHPSEL_HIGH : DEMOD_PROP_DVBT_HIERARCHY_HIERHPSEL_LOW;

	DEMOD_L2_DVB_Set_demod( pFrontend,
				standard,
				freq_Khz,
				new_tuneMode,
				DEMOD_PROP_MODE_SPECINVAUTO_AUTO,
				DEMOD_PROP_MODE_SPECINV_NORMAL,
				dvb_t_bandwidth_Khz,
				dvbt_hpSel,
				symbol_rate_Kbps,
				dvb_t_constellation,
				dvbt2_PLPId,
				DEMOD_PROP_DVBT2_MODE_LOCK_MODE_BASE_ONLY); // T2-Base
	return RET_OK;

}

int _DEMOD_M23_DVBT2_SetDemod (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_L2_Context *	pFrontend;

	UINT8  			standard;
	UINT8  			dvbt2_constellation;
	UINT8  			new_tuneMode;
	UINT16			dvbt2_PLPId;

	UINT32 			freq_Khz = 0;
	UINT16 			dvbt2_bandwidth_Khz = 0;
	UINT16 			symbol_rate_Kbps = 0;

	pFrontend 		= DEMOD_Get_LGDBB_Context();

	standard 		= DEMOD_MODULATION_DVBT2;

	dvbt2_constellation	= DEMOD_CONSTELLATION_UNKNOWN;
	dvbt2_PLPId		= pDemodInfo->setCfgParam.dvbt2.unPLP;

	new_tuneMode		= _DEMOD_M23_DVBT2_CheckTuneMode(pDemodInfo);

	DEMOD_NOTI("Start\n");

	if(RET_OK != DEMOD_M23_Get_BW(pDemodInfo, &dvbt2_bandwidth_Khz))
	{
		DEMOD_ERROR("Fail, DEMOD_M23_Get_BW()\n");
		return RET_ERROR;
	}
	DEMOD_PRINT("dvbt2_bandwidth_Khz[%d]\n", dvbt2_bandwidth_Khz);
	DEMOD_PRINT("new_tuneMode : 0x%02x\n", new_tuneMode);

	DEMOD_L2_DVB_Set_demod( pFrontend,
				standard,
				freq_Khz,
				new_tuneMode,
				DEMOD_PROP_MODE_SPECINVAUTO_AUTO,
				DEMOD_PROP_MODE_SPECINV_NORMAL,
				dvbt2_bandwidth_Khz,
				DEMOD_PROP_DVBT_HIERARCHY_HIERHPSEL_HIGH,
				symbol_rate_Kbps,
				dvbt2_constellation,
				dvbt2_PLPId,
				DEMOD_PROP_DVBT2_MODE_LOCK_MODE_BASE_ONLY); // T2-Base

	DEMOD_PRINT("PLP ID = 0x%02x\n", dvbt2_PLPId);
	return RET_OK;

}


int _DEMOD_M23_DVB_CheckSignalState (DEMOD_CTX_T *pDemodInfo)
{

	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	pFrontend = DEMOD_Get_LGDBB_Context();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;;
	}

	#if 0
	printk("[op_mode: %d]\n"		, signalStatus.operatingMode);
	printk("[if_agc: %d]\n"			, signalStatus.if_agc);
	printk("[mse_info: %d]\n"		,signalStatus.mse_info_eq);
	printk("[snr: %d]\n"			,signalStatus.snr_eq);
	printk("[dl: %d]\n"				, signalStatus.demodLock);
	printk("[ber: %d]\n"			, signalStatus.ber);
	printk("[pe: %d]\n"			, signalStatus.packetError);
	printk("[afc_freq: %d]\n"		, signalStatus.offsetFrq_Hz);
	printk("[constellation: %d]\n"	, signalStatus.constellation);
	printk("[sp_inv: %d]\n"			,signalStatus.spInv);
	printk("[constPwr: %d]\n"			,signalStatus.constPwr);
	printk("[packet error : %d]\n"			, signalStatus.packetError);
	#endif
	pDemodInfo->signalStatus.packetError 	= signalStatus.packetError;
	pDemodInfo->signalStatus.ber			= signalStatus.ber;
	pDemodInfo->signalStatus.agc			= signalStatus.if_agc;
	pDemodInfo->signalStatus.m.mse		= signalStatus.mse_info_demod;
	pDemodInfo->signalStatus.m.constPwr	= signalStatus.constPwr;
	pDemodInfo->freqOffset 				= signalStatus.offsetFrq_Hz / 1000;
	pDemodInfo->signalStatus.operMode 	= pDemodInfo->operMode;
	pDemodInfo->signalStatus.rfMode		= pDemodInfo->systemMode;
	pDemodInfo->signalStatus.cellID		= signalStatus.cell_id;

	return RET_OK;

}

int DEMOD_M23_DVB_SW_Init (void)
{
	LX_DEMOD_L2_Context *	pFrontend;

	DEMOD_PRINT("Start\n");

	pFrontend = DEMOD_Get_LGDBB_Context();

	//if(DEMOD_L2_DVB_SW_Init(pFrontend, 0x26) != NO_DEMOD_ERROR)   // CPBOX
	if(DEMOD_L2_DVB_SW_Init(pFrontend, DEMOD_CHIP_ID) != NO_DEMOD_ERROR)     // SOC
	{
		DEMOD_ERROR("Fail, DEMOD_M23_DVB_SW_Init\n");
		return RET_ERROR;
	}

	if(DEMOD_L2_SAT_SW_Init(pFrontend, DEMOD_CHIP_ID) != NO_DEMOD_ERROR)     // SOC
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SAT_SW_Init\n");
		return RET_ERROR;
	}

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBC_AutoSymbolRateDet
 * Enable/Diable automatic symbol rate detection on DVB-C mode.
 *
 * @param  benable - BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBC_AutoSymbolRateDet (LX_DEMOD_SYMRDET_MODE_T symrateMode, UINT16 SymbolRate )
{
	LX_DEMOD_L2_Context *	pFrontend;

	int 			retc = NO_DEMOD_ERROR;

	pFrontend = DEMOD_Get_LGDBB_Context();

	switch(symrateMode)
	{
		case LX_DEMOD_SYMR_FIXED_MODE:
			{
				retc = DEMOD_L2_DVBC_Set_SymbolRate_Detect(pFrontend, DEMOD_CMD_DVBC_SRD_AUTO_EN_DISABLE, SymbolRate);
				if(retc != NO_DEMOD_ERROR)
				{
					DEMOD_ERROR("Fail, DEMOD_L2_DVBC_Set_SymbolRate_Detect() error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
					return retc;
				}
			}
			break;
		case LX_DEMOD_SYMR_FULL_SCAN_MODE:
			{
				retc = DEMOD_L2_DVBC_Set_SymbolRate_Detect(pFrontend, DEMOD_CMD_DVBC_SRD_AUTO_EN_ENABLE, SymbolRate);
				if(retc != NO_DEMOD_ERROR)
				{
					DEMOD_ERROR("Fail, DEMOD_L2_DVBC_Set_SymbolRate_Detect() error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
					return retc;
				}
			}
			break;
		default :
			break;
	}
	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBC_IsSymbolRateAuto
 * Enable/Diable automatic symbol rate detection on DVB-C mode.
 *
 * @param  *bAuto - BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBC_IsSymbolRateAuto (BOOLEAN *bAuto)
{
	LX_DEMOD_L2_Context *	pFrontend;

	pFrontend = DEMOD_Get_LGDBB_Context();

	if(pFrontend->demod->cmd->dvbc_sym_rate.auto_en == 1)
	{
		*bAuto = TRUE;
	}
	else
	{
		*bAuto = FALSE;
	}

	DEMOD_PRINT("SymbolRateAuto = %s\n", (pFrontend->demod->cmd->dvbc_sym_rate.auto_en == 1)?"Enable":"Disable");

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBC_IsQammodeAutoDet
 * Control automatic setting of DVBC config.
 *
 * @param *bAutoQam 	[IN] BOOLEAN - automatic setting (TRUE) / manual setting(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBC_IsQammodeAutoDet (BOOLEAN *bAutoQam)
{
	LX_DEMOD_L2_Context *	pFrontend;

	pFrontend = DEMOD_Get_LGDBB_Context();

	if(pFrontend->demod->prop->dd_constel.constel_autodet == 0)
	{
		*bAutoQam = TRUE;
	}
	else
	{
		*bAutoQam = FALSE;
	}

	DEMOD_PRINT("QammodeAutoDet = %s\n", (pFrontend->demod->prop->dd_constel.constel_autodet == 0)?"Enable":"Disable");
//	*bAutoQam = FALSE;

	return RET_OK;
}
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBC_Set_DefaultRegisterValue
 * Set defualt register value on DVB-T.
 * This function is applied only to A0 version, not to A1 version.
 * @param none
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBC_Set_DefaultRegisterValue (void)
{
	_DVB_Full_Pkerr_Count = 0;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBC_Set_Config_auto
 * Control automatic setting of DVBC config.
 *
 * @param bAutoDetect 	[IN] BOOLEAN - automatic setting (TRUE) / manual setting(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBC_Set_Config_auto (BOOLEAN bAutoDetect)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBC_Set_QamMode
 * Set DVBC config parameters manually.
 *
 * @param SymbolRate 	[IN] UINT16 - symbol rate : unit: KHz.
 * @param constel 		[IN] UINT8 - QAM mode : 16QAM(0), 32QAM(1), 64QAM(2), 128QAM(3), 256QAM(4).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBC_Set_QamMode (LX_DEMOD_RF_MODE_T constel)
{
	LX_DEMOD_L2_Context *	pFrontend;

	UINT8  			dvb_c_constellation = DEMOD_CONSTELLATION_UNKNOWN;
	int 			retc = RET_OK;

	pFrontend = DEMOD_Get_LGDBB_Context();

	switch (constel)
	{
		case LX_DEMOD_16QAM:
			dvb_c_constellation = DEMOD_CONSTELLATION_QAM16;
			break;

		case LX_DEMOD_32QAM:
			dvb_c_constellation = DEMOD_CONSTELLATION_QAM32;
			break;

		case LX_DEMOD_64QAM:
			dvb_c_constellation = DEMOD_CONSTELLATION_QAM64;
			break;

		case LX_DEMOD_128QAM:
			dvb_c_constellation = DEMOD_CONSTELLATION_QAM128;
			break;

		case LX_DEMOD_256QAM:
			dvb_c_constellation = DEMOD_CONSTELLATION_QAM256;
			break;

		default:
			dvb_c_constellation = DEMOD_CONSTELLATION_UNKNOWN;
			break;
	}

	pFrontend->demod->prop->dd_constel.constellation	= dvb_c_constellation;
	pFrontend->demod->prop->dd_constel.constel_autodet	= DEMOD_PROP_CONSTEL_AUTO_DET_ENABLE;

	retc = DEMOD_L1_Set_Property(pFrontend->demod, DEMOD_PROP_CONSTEL_CODE);

	if(retc != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("Fail, DEMOD_L1_Set_Property() error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
		return retc;
	}
	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBC_Set_NeverLockWaitTime
 * Set neverlock waiting period.
 *
 * @param waitMs 	[IN] UINT32 - unit: ms
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBC_Set_NeverLockWaitTime (UINT32 waitMs)
{
	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBC_Get_SymbolRateDetect
 * Get symbol rate in KHz (Don't use this function until revision A1)
 *
 * @param *pSymbolRate 	[OUT] UINT16 - symbol rate : unit: KHz.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBC_Get_SymbolRateDetect (UINT16 *pSymbolRate)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS 	signalStatus;

	pFrontend = DEMOD_Get_LGDBB_Context();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}

	*pSymbolRate = signalStatus.sym_rate ;
	DEMOD_PRINT("sym_rate: %d\n", *pSymbolRate);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBC_Get_SymbolRateStatus
 * Get symbol rate detection state on DVB-C
 *
 * @param *pSymbolRateDet 	[OUT] SYMBOLRATE_STATE_T - status and detected symbol rate .
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBC_Get_SymbolRateStatus (LX_DEMOD_SYMBOLRATE_STATE_T *pSymbolRateDet)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS 	signalStatus;

	pFrontend = DEMOD_Get_LGDBB_Context();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}

	pSymbolRateDet->status 		= LX_DEMOD_DETECTED;
	pSymbolRateDet->symbolRate 	= signalStatus.sym_rate ;
	DEMOD_PRINT("pSymbolRateDetStatus : %s, symbolRate: %d\n", "LX_DEMOD_DETECTED", pSymbolRateDet->symbolRate);

	return RET_OK;

}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBC_Get_QamModeDetectStatus
 * Get QAM mode detection state and detected QAM mode on DVB-C
 *
 * @param *pQamModeDet 	[OUT] SYMBOLRATE_STATE_T - status and detected QAM mode .
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBC_Get_QamModeDetectStatus (LX_DEMOD_QAMMODE_STATE_T *pQamModeDet)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS 	signalStatus;

	LX_DEMOD_LOCK_STATE_T	lockState;
	LX_DEMOD_RF_MODE_T	qam_mode;

	pFrontend = DEMOD_Get_LGDBB_Context();

	if(RET_OK != DEMOD_M23_Get_Lock(LX_DEMOD_FEC_LOCK, &lockState))
	{
		DEMOD_ERROR("Fail, DEMOD_M23_Get_Lock()\n");
		return RET_ERROR;
	}

	if (lockState != LX_DEMOD_LOCKED)
	{
		return RET_OK;
	}

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}

	DEMOD_PRINT("Constellation: %d\n", pFrontend->demod->rsp->dvbc_status.constellation);

	switch (signalStatus.constellation)
	{
		case DEMOD_CONSTELLATION_QAM16	:
			qam_mode = LX_DEMOD_16QAM;
			break;

		case DEMOD_CONSTELLATION_QAM32	:
			qam_mode = LX_DEMOD_32QAM;
			break;

		case DEMOD_CONSTELLATION_QAM64	:
			qam_mode = LX_DEMOD_64QAM;
			break;

		case DEMOD_CONSTELLATION_QAM128  :
			qam_mode = LX_DEMOD_128QAM;
			break;

		case DEMOD_CONSTELLATION_QAM256  :
			qam_mode = LX_DEMOD_256QAM;
			break;

		default  :
			qam_mode = LX_DEMOD_UNKOWN_MODE;
			break;

	}
	pQamModeDet->status 	= LX_DEMOD_DETECTED;
	pQamModeDet->qamMode = qam_mode;

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBC_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_M23_DVBC_Obtaining_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS 	signalStatus;

	static LX_DEMOD_FLAG_T 	scanProcessing = LX_DEMOD_FLAG_START;
	static LX_DEMOD_LOCK_STATE_T lockState = LX_DEMOD_UNLOCKED;
	static unsigned int 	sigStablestartTime = 0;

	pFrontend = DEMOD_Get_LGDBB_Context();

	switch (pDemodInfo->controlState)
	{
		/***************************************************/
		/***** Configure tuner for desired channel No. *****/
		/***************************************************/
		case LX_DEMOD_TUNE_START:
			{

				if(RET_OK != _DEMOD_M23_DVBC_SetDemod(pDemodInfo))
				{
					DEMOD_PRINT("Fail, _DEMOD_M23_DVBC_SetDemod()\n");
					return RET_ERROR;
				}

				if((LX_DEMOD_TUNE_NORMAL != pDemodInfo->setCfgParam.dvbc.tuneMode) &&
					(LX_DEMOD_TUNE_SPEC_DVBC_FIXED_DATA != pDemodInfo->setCfgParam.dvbc.tuneMode))
				{

					if(RET_OK != DEMOD_M23_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_ON, &scanProcessing, &lockState))
					{
						DEMOD_PRINT("Fail, DEMOD_M23_NeverlockScan()\n");
						return RET_ERROR;
					}
					pDemodInfo->controlState 		= LX_DEMOD_TUNE_SCAN;
					_DVB_Full_Pkerr_Threshold 		= DVB_FULL_PACKET_ERROR;
					DEMOD_PRINT("LX_DEMOD_SYNC_CHECKING(AUTO or Manual SCAN) : Going to LX_DEMOD_TUNE_SCAN..... ^0^\n");
				}
				else
				{
					pDemodInfo->scanJobFlag 	  	= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState 		= LX_DEMOD_SIGNAL_STABLE;
					_DVB_Full_Pkerr_Threshold 		= DVB_UNCHECK_PACKET_ERROR;

					DEMOD_PRINT("LX_DEMOD_SYNC_CHECKING(NORMAL SCAN) : Going to LX_DEMOD_SIGNAL_STABLE..... ^0^\n");
				}
			}
			break;

		/***************************************************/
		/***** Configure demod for scan mode. *****/
		/***************************************************/
		case LX_DEMOD_TUNE_SCAN:
			{
				unsigned int currentTime 	= 0;
				unsigned int elapsedTime 	= 0;

				if((LX_DEMOD_FLAG_COMPLETE == pDemodInfo->scanJobFlag) || (LX_DEMOD_FLAG_FINISH == pDemodInfo->scanJobFlag))
				{
					pDemodInfo->controlState 		= LX_DEMOD_SIGNAL_STABLE;

					DEMOD_PRINT("Already Done\n");
					DEMOD_PRINT("LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
					return RET_OK;
				}

				if(RET_OK != DEMOD_M23_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_OFF, &scanProcessing, &lockState))
				{
					DEMOD_ERROR("Fail, DEMOD_M23_NeverlockScan()\n");
					return RET_ERROR;
				}

				if((LX_DEMOD_FLAG_FINISH == scanProcessing) && (LX_DEMOD_LOCKED == lockState))
				{
					pDemodInfo->scanJobFlag 		= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState 		= LX_DEMOD_SIGNAL_STABLE;

					DEMOD_PRINT("Signal is Found\n");
					DEMOD_PRINT("LX_DEMOD_SYNC_CHECKING : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
				}
				else if((LX_DEMOD_FLAG_FINISH == scanProcessing)&& (LX_DEMOD_UNLOCKED == lockState))
				{
					pDemodInfo->scanJobFlag 		= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->bNotifiedUnlock		= TRUE;
					pDemodInfo->bNotifiedLock		= FALSE;
					pDemodInfo->lockStatus			= LX_DEMOD_UNLOCKED;
					pDemodInfo->signalStatus.bSignalValid 	= FALSE;
					pDemodInfo->controlState 		= LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK;
					currentTime 				= jiffies_to_msecs(jiffies);
					elapsedTime 				= currentTime - g_RetuneStartTime;

					DEMOD_NOTI("LX_DEMOD_TUNE_SCAN : MSG_DVBC_FRONT_END_NOT_LOCKED by Scan Fail\n") ;
					DEMOD_NOTI("LX_DEMOD_TUNE_SCAN : Elapse time is %d msec\n", elapsedTime) ;

					DEMOD_PRINT("Signal is NOT Found\n");
				}
				else
				{
					pDemodInfo->scanJobFlag 		= LX_DEMOD_FLAG_ING;
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

				if(RET_OK != DEMOD_M23_Get_Lock(LX_DEMOD_FEC_LOCK, &lockState))
				{
					DEMOD_ERROR("Fail, DEMOD_M23_Get_Lock()\n");
					return RET_ERROR;
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					pDemodInfo->controlState		= LX_DEMOD_SIGNAL_STABLE;
					sigStablestartTime 			= jiffies_to_msecs(jiffies);

					DEMOD_PRINT("LX_DEMOD_SYNC_CHECKING : Going to LX_DEMOD_SIGNAL_STABLE..... %d [ms] ^0^\n",sigStablestartTime);
				}
				else
				{
				 	/* nothing to do so far */
				}
			}
			break;

		/********************************************/
	   	/***** Attempting to obtain signal stability *****/
	   	/********************************************/
	   	case LX_DEMOD_SIGNAL_STABLE:
			{
				LX_DEMOD_LOCK_STATE_T lockState;
//				SINT32 freqOffset;
				unsigned int elapsedTime;
//				UINT32 packetError;
//				LX_DEMOD_SYMBOLRATE_STATE_T symbolRateDet;
//				UINT16 symbolRateDiff;

				if(RET_OK != DEMOD_M23_Get_Lock(LX_DEMOD_FEC_LOCK, &lockState))
				{
					DEMOD_ERROR("Fail, DEMOD_M23_Get_Lock()\n");
					return RET_ERROR;
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
					{
						DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
						return RET_ERROR;
					}

					if (LX_DEMOD_TUNE_NORMAL == pDemodInfo->setCfgParam.dvbc.tuneMode)
					{
						pDemodInfo->bNotifiedLock		= TRUE;
						pDemodInfo->bNotifiedUnlock 		= FALSE;
						pDemodInfo->lockStatus			= LX_DEMOD_LOCKED;
						pDemodInfo->signalStatus.bSignalValid	= TRUE;

						pDemodInfo->freqOffset			= signalStatus.offsetFrq_Hz/1000;
						pDemodInfo->controlState		= LX_DEMOD_SIGNAL_LOCKED;
						elapsedTime 				= jiffies_to_msecs(jiffies) - g_RetuneStartTime;

						DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE :  MSG_DVBC_FRONT_END_LOCKED_On_Normal_Tunemode\n");
						DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms]\n", elapsedTime);
						DEMOD_PRINT("LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz]\n", pDemodInfo->freqOffset);
					}
					else
					{
						pDemodInfo->bNotifiedLock		= TRUE;
						pDemodInfo->bNotifiedUnlock 		= FALSE;
						pDemodInfo->lockStatus			= LX_DEMOD_LOCKED;
						pDemodInfo->signalStatus.bSignalValid 	= TRUE;

						pDemodInfo->freqOffset 			= signalStatus.offsetFrq_Hz/1000;
						pDemodInfo->controlState		= LX_DEMOD_SIGNAL_LOCKED;
						elapsedTime 				= jiffies_to_msecs(jiffies) - g_RetuneStartTime;

						DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : MSG_DVBC_FRONT_END_LOCKED_On_Other_Tunemode\n");
						DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms]\n", elapsedTime);
						DEMOD_PRINT("LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz]\n", pDemodInfo->freqOffset);
					}

					if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
					{
						DEMOD_ERROR("Fail, DEMOD_Get_TunedCFG()\n");
						return RET_ERROR;
					}

					if (RET_OK != _DEMOD_M23_DVB_CheckSignalState(pDemodInfo))
					{
						DEMOD_ERROR("Fail, _DEMOD_M23_DVB_CheckSignalState()\n");
						return RET_ERROR;
					}
				}
				else
				{
//					pDemodInfo->controlState	= LX_DEMOD_SIGNAL_STABLE;
//					DEMOD_PRINT("LX_DEMOD_SIGNAL_STABLE : Going back to LX_DEMOD_SIGNAL_STABLE.....\n");
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
 * DEMOD_M23_DVBC_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_M23_DVBC_Monitoring_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{

	LX_DEMOD_LOCK_STATE_T lockState;

	if(RET_OK != DEMOD_M23_Get_Lock(LX_DEMOD_FEC_LOCK, &lockState))
	{
		DEMOD_ERROR("Fail, DEMOD_M23_Get_Lock()\n");
		return RET_ERROR;
	}

	if(LX_DEMOD_LOCKED == lockState)
	{
		pDemodInfo->unLockCount = 0;

		if (RET_OK != _DEMOD_M23_DVB_CheckSignalState(pDemodInfo))
		{
			DEMOD_ERROR("Fail, _DEMOD_M23_DVB_CheckSignalState()\n");
			return RET_ERROR;
		}

		if(pDemodInfo->signalStatus.packetError >= _DVB_Full_Pkerr_Threshold)
		{
			_DVB_Full_Pkerr_Count++;
			DEMOD_PRINT("_DVB_Full_Pkerr_Count = %d\n",_DVB_Full_Pkerr_Count);

			if(_DVB_Full_Pkerr_Count == _DVBC_Full_Pkerr_Count_Threshold)
			{
				DEMOD_NOTI("Oops !! Force to NOT LOCK by Full Packet error Count !!\n");
				_DVB_Full_Pkerr_Count = 0;

				if(RET_OK != DEMOD_M23_SoftwareReset())
				{
					DEMOD_ERROR("Fail, DEMOD_M23_SoftwareReset()\n");
					return RET_ERROR;
				}

				DEMOD_PRINT("Success, DEMOD_M23_SoftwareReset()\n");

				pDemodInfo->lockStatus				= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedUnlock 			= TRUE;
				pDemodInfo->bNotifiedLock			= FALSE;
				pDemodInfo->signalStatus.bSignalValid		= FALSE;
				DEMOD_NOTI("MSG_DVBC_FRONT_END_NOT_LOCKED by Full packet error ..... -_-;;\n");
			}
		}
		else
		{
			_DVB_Full_Pkerr_Count = 0;

			if((LX_DEMOD_LOCKED != pDemodInfo->lockStatus)  && (TRUE != pDemodInfo->bNotifiedLock))
			{
				pDemodInfo->lockCount++;

			}
			if(pDemodInfo->lockCount == 2)
			{
				pDemodInfo->lockStatus				= LX_DEMOD_LOCKED;
				pDemodInfo->bNotifiedLock 			= TRUE;
				pDemodInfo->bNotifiedUnlock 			= FALSE;
				pDemodInfo->signalStatus.bSignalValid 		= TRUE;
				pDemodInfo->lockCount 				= 0;

				DEMOD_NOTI("MSG_DVBC_FRONT_END_LOCKED by Lock Count\n");

				if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
				{
					pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;
				}
			}

			if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
			{
				DEMOD_ERROR("Fail, DEMOD_Get_TunedCFG()\n");
				return RET_ERROR;
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

			if(pDemodInfo->unLockCount == _DVBC_Unlock_Count_Threshold)
			{
				pDemodInfo->lockStatus 					= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedUnlock 			= TRUE;
				pDemodInfo->bNotifiedLock				= FALSE;
				pDemodInfo->signalStatus.bSignalValid 	= FALSE;
				_DVB_Full_Pkerr_Count 					= 0;
				pDemodInfo->unLockCount 				= 0;

				DEMOD_NOTI("MSG_DVBC_FRONT_END_NOT_LOCKED by unLockCount..... -_-\n");
			}
/*
			if(pDemodInfo->unLockCount >= 4)
			{
				pDemodInfo->unLockCount = 0;
			}
*/
		}
	}
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBC_Get_DvbInfo
 * Get all information on DVB-C for debug
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBC_Get_DvbInfo (void)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	BOOLEAN 		isAutoSymbol = FALSE;
	BOOLEAN 		isAutoQammode = FALSE;

	LX_DEMOD_MSE_T		sigMse;
	LX_DEMOD_SYMBOLRATE_STATE_T symbolRateDet;
	LX_DEMOD_QAMMODE_STATE_T qamModeDet;
	LX_DEMOD_LOCK_STATE_T	lockState;
	LX_DEMOD_LOCK_STATE_T	spectrumAuto;

	pFrontend = DEMOD_Get_LGDBB_Context();

	DEMOD_PRINT("Start\n");

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}

	DEMOD_PRINT("IF AGC Gain = 0x%x\n", signalStatus.if_agc);

 	//NeverLock status
	if (RET_OK != DEMOD_M23_Get_NeverLockStatus(LX_DEMOD_DVBC, &lockState))
	{
		DEMOD_ERROR("Fail, DEMOD_M23_Get_NeverLockStatus()\n");
		return RET_ERROR;
	}

	switch(lockState)
	{
		case LX_DEMOD_DETECTION_PROCESSING :
			DEMOD_PRINT("Signal Checking process\n");
			break;

		case LX_DEMOD_DETECTED :
			DEMOD_PRINT("normal State (available channel)\n");
			break;

		case LX_DEMOD_DETECTION_FAIL :
			DEMOD_PRINT("neverlock state (empty channel)\n");
			break;

		default :
			DEMOD_PRINT("INVALID neverLockStatus\n");
			break;
	}

	// Carrier LOCK status  and offset monitoring

	if (RET_OK != DEMOD_M23_Get_Lock(LX_DEMOD_CARR_LOCK, &lockState) )
	{
		DEMOD_ERROR("Fail, DEMOD_M23_Get_Lock()\n");
		return RET_ERROR;
	}

	if(lockState == LX_DEMOD_LOCKED)
	{
		DEMOD_PRINT("DVB CARRIER is LOCKED\n");
	}
	else
	{
		DEMOD_PRINT("DVB CARRIER is NOT LOCKED\n");
	}

	// Sampling frequency LOCK status and offset monitoring
	if (RET_OK != DEMOD_M23_Get_Lock( LX_DEMOD_TR_LOCK, &lockState))
	{
		DEMOD_ERROR("Fail, DEMOD_M23_Get_Lock()\n");
		return RET_ERROR;
	}

	if(lockState == LX_DEMOD_LOCKED)
	{
		DEMOD_PRINT("Sampling frequency is Locked\n");
	}
	else
	{
		DEMOD_PRINT("Sampling frequency is NOT Locked\n");
	}

	//Symbol rate detection
	if (RET_OK != DEMOD_M23_DVBC_IsSymbolRateAuto(&isAutoSymbol))
	{
		DEMOD_ERROR("Fail, DEMOD_M23_DVBC_IsSymbolRateAuto()\n");
		return RET_ERROR;
	}

	if(TRUE == isAutoSymbol)
	{
		symbolRateDet.status 		= LX_DEMOD_DETECTED;
		symbolRateDet.symbolRate 	= signalStatus.sym_rate ;

		DEMOD_PRINT("Symbol rate  is detected\n");
		DEMOD_PRINT("Symbol rate = %d [KHz]\n",symbolRateDet.symbolRate);
	}


	// QAM mode detect status and mode monitoring
	if (RET_OK != DEMOD_M23_DVBC_IsQammodeAutoDet(&isAutoQammode))
	{
		DEMOD_ERROR("Fail, DEMOD_M23_DVBC_IsQammodeAutoDet()\n");
		return RET_ERROR;
	}

	if(TRUE == isAutoQammode)
	{
		if (RET_OK != DEMOD_M23_DVBC_Get_QamModeDetectStatus(&qamModeDet))
		{
			DEMOD_ERROR("Fail, DEMOD_M23_DVBC_Get_QamModeDetectStatus()\n");
			return RET_ERROR;
		}

		switch(qamModeDet.status)
		{
			case LX_DEMOD_IDLE :
			{
				DEMOD_PRINT("QAM mode detect is idle status\n");
				break;
			}
			case LX_DEMOD_DETECTED :
			{
				DEMOD_PRINT("QAM mode is detected\n");
				DEMOD_PRINT("QAM mode is %s\n",
									(qamModeDet.qamMode == LX_DEMOD_16QAM) ? "16QAM" :
									(qamModeDet.qamMode == LX_DEMOD_32QAM) ? "32QAM" :
									(qamModeDet.qamMode == LX_DEMOD_64QAM) ? "64QAM" :
									(qamModeDet.qamMode == LX_DEMOD_128QAM) ? "128QAM" :
									(qamModeDet.qamMode == LX_DEMOD_256QAM) ? "256QAM" :
									("UNKOWN"));
			break;
			}
			case LX_DEMOD_DETECTION_PROCESSING :
			{
				DEMOD_PRINT("QAM mode detection is processing\n");
				break;
			}
			case LX_DEMOD_DETECTION_FAIL :
			{
				DEMOD_PRINT("QAM mode detection is failed\n");
				break;
			}
			case LX_DEMOD_DETECTION_MANUAL :
			{
				DEMOD_PRINT("Manual QAM mode detection mode\n");
				break;
			}
			default :
			{
				DEMOD_PRINT("INVALID QAM mode detection\n");
				break;
			}
		}
	}

 	//spectrum inversion status
	if (RET_OK !=  DEMOD_M23_Get_SpectrumStatus(&spectrumAuto, &lockState))
	{
		DEMOD_WARN("Fail, DEMOD_M23_Get_SpectrumStatus()\n");
		lockState = LX_DEMOD_UNKOWN_STATE;
	}

	if(lockState == LX_DEMOD_INVERSION)
	{
		DEMOD_PRINT("Spectrum Inversion\n");
	}
	else
	{
		DEMOD_PRINT("Spectrum Normal\n");
	}

	//Frame lock status
	if (RET_OK != DEMOD_M23_Get_Lock(LX_DEMOD_FEC_LOCK, &lockState) )
	{
		DEMOD_ERROR("Fail, DEMOD_M23_Get_Lock()\n");
		return RET_ERROR;
	}

	if(lockState != LX_DEMOD_LOCKED)
	{
		DEMOD_PRINT("DVB FEC is not locked\n");
	}
	else
	{
		DEMOD_PRINT("DVB FEC is locked\n");
	}

	sigMse.bMse 		= 0;
	sigMse.mse 		= signalStatus.mse_info_eq;
	sigMse.constPwr		= signalStatus.constPwr;

	DEMOD_PRINT("mse = %d, constPwr = %d\n", sigMse.mse, sigMse.constPwr);
	DEMOD_PRINT("vBER = %d\n", signalStatus.ber);
	DEMOD_PRINT("TP Error Count= %d\n", signalStatus.packetError);

	return RET_OK;
}

#if 0
#endif

/**
 * DEMOD_M23_DVBT_Set_DefaultRegisterValue
 * Set defualt register value on DVB-T.
 * This function is applied only to A0 version, not to A1 version.
 *
 * @param none
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT_Set_DefaultRegisterValue (LX_DEMOD_BWMODE_T band)
{
	_DVB_Full_Pkerr_Count 	= 0;

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBT_Set_Config_auto
 * Control automatic setting of DVB-T config.
 *
 * @param bAutoDetect 	[IN] BOOLEAN - automatic setting (TRUE) / manual setting(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT_Set_Config_auto (BOOLEAN bAutoDetect)
{
	DEMOD_INFO("deprecated\n");
/*
	LX_DEMOD_L2_Context *	pFrontend;

	pFrontend = DEMOD_Get_LGDBB_Context();

	DEMOD_NOTI("Set to %s\n", (bAutoDetect == TRUE)?"AUTO":"MANUAL");

	if(bAutoDetect == TRUE)
	{
		if(DEMOD_L2_DVB_AutoModeDetectOn(pFrontend))
		{
			DEMOD_ERROR("Fail, DEMOD_L2_DVB_AutoModeDetectOn()\n");
			return RET_ERROR;;
		}
	}
	else
	{
		if(DEMOD_L2_DVB_AutoModeDetectOff(pFrontend))
		{
			DEMOD_ERROR("Fail, DEMOD_L2_DVB_AutoModeDetectOff()\n");
			return RET_ERROR;;
		}
	}
*/
	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBT_Set_PartialConfig
 * Set hierachical signal path and bandwidth.
 * This function is used when LX_DEMOD_M23_DVBT_Set_Config_auto is enabled.
 *
 * @param *pDvbtConfigParam 	[IN] LX_DEMOD_DVBT_CONFIG_T - DVB-T config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT_Set_PartialConfig (LX_DEMOD_DVBT_CONFIG_T *pDvbtConfigParam)
{
	LX_DEMOD_L2_Context *	pFrontend;

	pFrontend = DEMOD_Get_LGDBB_Context();

	pFrontend->demod->prop->dd_dvbt_hp_sel.hierhpsel  	= pDvbtConfigParam->bSetHp;
	if(DEMOD_L2_Set_Property(pFrontend, DEMOD_PROP_DVBT_HIERARCHY_CODE) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("Fail, DEMOD_L2_Set_Property(DEMOD_DD_DVBT_HIERARCHY_PROP_CODE)\n");
		return RET_ERROR;;
	}

	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBT_Set_FullConfig
 * Set all config parameters on DVB-T.
 * This function is used when LX_DEMOD_M23_DVBT_Set_Config_auto is disabled.
 *
 * @param *pDvbtConfigParam 	[IN] LX_DEMOD_DVBT_CONFIG_T - DVB-T config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT_Set_FullConfig (LX_DEMOD_DVBT_CONFIG_T *pDvbtConfigParam)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBT_Set_NeverLockWaitTime
 * Set neverlock waiting period.
 *
 * @param waitMs 	[IN] UINT32 - unit: ms
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT_Set_NeverLockWaitTime (UINT32 waitMs)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBT_Set_TafcWaitSymbol
 * Set TAFC wait symbol number.
 *
 * @param bDelayed 	[IN] BOOLEAN
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT_Set_TafcWaitSymbol (BOOLEAN bDelayed)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBT_Set_CrGearshEn
 * enable/disable Carrier recovery bandwidth gear shift
 *
 * @param bEnable 	[IN] BOOLEAN
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT_Set_CrGearshEn (BOOLEAN bEnable)
{
	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBT_Get_PreGhostDetection
 * Set Cir Power level and NR level
 *
 * @param *pIsExist 	[IN] BOOLEAN
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT_Get_PreGhostDetection (BOOLEAN *pIsExist)
{
	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBT_Get_DelaySpreadStatus
 * Get delay spread state on DVB-T.
 *
 * @param *pDelaySpread 	[OUT] UINT16.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT_Get_DelaySpreadStatus (UINT16 *pDelaySpread)
{
	return RET_OK;
}



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBT_Get_Hierach_HPSel
 * Get the information if the hierachical HP is selected.
 *
 * @param *pBSetHp 	[OUT] BOOLEAN - HP (TRUE) / LP(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT_Get_Hierach_HPSel (BOOLEAN *pBSetHp)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("Start\n");

	pFrontend = DEMOD_Get_LGDBB_Context();

	*pBSetHp = TRUE;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}

	if(signalStatus.hierarchy_sel == DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_SEL_HP)
		*pBSetHp = TRUE;
	else
		*pBSetHp = FALSE;

	return RET_OK;

}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBT_Get_FFTMode
 * Get the information of bandwidth on DVB-T.
 *
 * @param *pTxModeLock 	[OUT] LX_DEMOD_LOCK_STATE_T - FFT mode lock state.
 * @param *pFftMode 	[OUT] LX_DEMOD_FFTMODE_T - detected FFT mode.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT_Get_FFTMode (LX_DEMOD_LOCK_STATE_T *pTxModeLock, LX_DEMOD_FFTMODE_T *pFftMode)
{

	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("Start\n");

	pFrontend = DEMOD_Get_LGDBB_Context();

	*pTxModeLock = LX_DEMOD_LOCKED;
	*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}

	switch(signalStatus.fftMode)
	{
		case DEMOD_FFT_MODE_2K :
			*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_2K;
			break;

		case DEMOD_FFT_MODE_4K:
			*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_4K;
			break;

		case DEMOD_FFT_MODE_8K:
			*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_8K;
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
 * DEMOD_M23_DVBT_Get_GuradIntervalMode
 * Get the information of guard interval on DVB-T.
 *
 * @param *pGIMode 	[OUT] LX_DEMOD_GIMODE_T - 1/32, 1/16, 1/8 and 1/4.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT_Get_GuradIntervalMode (LX_DEMOD_GIMODE_T *pGIMode)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("Start\n");

	pFrontend = DEMOD_Get_LGDBB_Context();

	*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_UNKNOWN;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}

	switch(signalStatus.guardInterval)
	{
		case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_32 :
			*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_32;
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_16:
			*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_16;
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_8 :
			*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_8;
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_4:
			*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_4;
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_128:
			*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_128;
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_19_128:
			*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_19_128;
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_19_256:
			*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_19_256;
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_64:
			*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_64;
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
 * DEMOD_M23_DVBT_Get_HierachyMode
 * Get the information of hierachical mode on DVB-T.
 *
 * @param *pHierachMode[OUT] DEMOD_M23_DVB_TPS_HIERACHY_T - alpha = none, 1, 2 and 4.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT_Get_HierachyMode (LX_DEMOD_DVB_TPS_HIERACHY_T *pHierachMode)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("Start\n");

	pFrontend = DEMOD_Get_LGDBB_Context();

	*pHierachMode = LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}

	switch(signalStatus.hierarchy)
	{
		case DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_NONE :
			*pHierachMode = LX_DEMOD_DVB_TPS_HIERACHY_NONE;
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_ALFA1:
			*pHierachMode = LX_DEMOD_DVB_TPS_HIERACHY_1;
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_ALFA2 :
			*pHierachMode = LX_DEMOD_DVB_TPS_HIERACHY_2;
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_ALFA4:
			*pHierachMode = LX_DEMOD_DVB_TPS_HIERACHY_4;
			break;
		default :
			*pHierachMode = LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN;
			break;
	}

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBT_Get_LpCoderRate
 * Get the information of LP code rate on DVB-T.
 *
 * @param *pLpCodeRate[OUT] LX_DEMOD_CODERATE_T - code rate : 1/2, 2/3, 3/4, 5/6 and 7/8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT_Get_LpCoderRate (LX_DEMOD_CODERATE_T *pLpCodeRate)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("Start\n");

	pFrontend = DEMOD_Get_LGDBB_Context();

	*pLpCodeRate = LX_DEMOD_CODE_UNKNOWN;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}

	if(signalStatus.hierarchy_sel == DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_SEL_LP)
	{
		switch(signalStatus.codeRate)
		{
			case DEMOD_CODERATE_DVBT_ISDBT_1_2 :
				*pLpCodeRate = LX_DEMOD_CODE_1_2;
				break;
			case DEMOD_CODERATE_DVBT_ISDBT_2_3:
				*pLpCodeRate = LX_DEMOD_CODE_2_3;
				break;
			case DEMOD_CODERATE_DVBT_ISDBT_3_4 :
				*pLpCodeRate = LX_DEMOD_CODE_3_4;
				break;
			case DEMOD_CODERATE_DVBT_ISDBT_5_6:
				*pLpCodeRate = LX_DEMOD_CODE_5_6;
				break;
			case DEMOD_CODERATE_DVBT_ISDBT_7_8:
				*pLpCodeRate = LX_DEMOD_CODE_7_8;
				break;
			default :
				*pLpCodeRate = LX_DEMOD_CODE_UNKNOWN;
				break;
		}
	}
	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBT_Get_HpCoderRate
 * Get the information of HP code rate on DVB-T.
 *
 * @param *pLpCodeRate[OUT] LX_DEMOD_CODERATE_T - code rate : 1/2, 2/3, 3/4, 5/6 and 7/8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT_Get_HpCoderRate (LX_DEMOD_CODERATE_T *pHpCodeRate)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("Start\n");

	pFrontend = DEMOD_Get_LGDBB_Context();

	*pHpCodeRate = LX_DEMOD_CODE_UNKNOWN;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}

	if(signalStatus.hierarchy_sel == DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_SEL_HP)
	{
		switch(signalStatus.codeRate)
		{
			case DEMOD_CODERATE_DVBT_ISDBT_1_2 :
				*pHpCodeRate = LX_DEMOD_CODE_1_2;
				break;
			case DEMOD_CODERATE_DVBT_ISDBT_2_3:
				*pHpCodeRate = LX_DEMOD_CODE_2_3;
				break;
			case DEMOD_CODERATE_DVBT_ISDBT_3_4 :
				*pHpCodeRate = LX_DEMOD_CODE_3_4;
				break;
			case DEMOD_CODERATE_DVBT_ISDBT_5_6:
				*pHpCodeRate = LX_DEMOD_CODE_5_6;
				break;
			case DEMOD_CODERATE_DVBT_ISDBT_7_8:
				*pHpCodeRate = LX_DEMOD_CODE_7_8;
				break;
			default :
				*pHpCodeRate = LX_DEMOD_CODE_UNKNOWN;
				break;
		}
	}

	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBT_GetCellId
 * Get TPS cell ID on DVB-T.
 *
 * @param *pCellIDLength[OUT] UINT8 - cell ID length.
 * @param *cell_id[OUT] UINT16.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT_Get_CellId (UINT8 *pCellIDLength, UINT16 *cell_id)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("Start\n");

	pFrontend = DEMOD_Get_LGDBB_Context();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}

	*cell_id = signalStatus.cell_id;

	DEMOD_PRINT("Cell ID = 0x%x\n", *cell_id);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBT_Get_TpsInfo
 * Get TPS information on DVB-T
 *
 * @param *pTpsParams [OUT] LX_DEMOD_DVBT_CONFIG_T - TPS data structure.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT_Get_TpsInfo (LX_DEMOD_DVBT_CONFIG_T *pTpsParams)
{
	LX_DEMOD_L2_Context * 	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	BOOLEAN 		bSetHp = TRUE;
	LX_DEMOD_BWMODE_T 	channelBW = LX_DEMOD_BW_UNKNOWN;
	LX_DEMOD_FFTMODE_T 	FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN ;
	LX_DEMOD_GIMODE_T 	gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_UNKNOWN;
	LX_DEMOD_DVB_TPS_HIERACHY_T 	hierachMode = LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN;
	LX_DEMOD_CODERATE_T 	lpCodeRate = LX_DEMOD_CODE_UNKNOWN;
	LX_DEMOD_CODERATE_T 	hpCodeRate = LX_DEMOD_CODE_UNKNOWN;
	LX_DEMOD_RF_MODE_T 	qamMode = LX_DEMOD_UNKOWN_MODE;


	DEMOD_PRINT("Start\n");

	pFrontend = DEMOD_Get_LGDBB_Context();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}

	if(NULL == pTpsParams)
	{
		DEMOD_ERROR("ERROR DEMOD_M23_DVBT_CONFIG_T TpsParams is NULL\n");
		return RET_ERROR;
	}

	if(signalStatus.hierarchy_sel == DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_SEL_HP)
	{
		bSetHp = TRUE;
		DEMOD_PRINT("Set HP selection = %s\n", " HP Mode");
	}
	else
	{
		bSetHp = FALSE;
		DEMOD_PRINT("Set HP selection = %s\n", " LP Mode");
	}

	pTpsParams->bSetHp = bSetHp;

	switch(signalStatus.bandwidth)
	{
		case 0x08:
			channelBW = LX_DEMOD_BW_8MHZ;
			DEMOD_PRINT("Bandwidth = %s\n", "LX_DEMOD_BW_8MHZ" );
			break;

		case 0x07:
			channelBW = LX_DEMOD_BW_7MHZ;
			DEMOD_PRINT("Bandwidth = %s\n", "LX_DEMOD_BW_7MHZ" );
			break;

		case 0x06:
			channelBW = LX_DEMOD_BW_6MHZ;
			DEMOD_PRINT("Bandwidth = %s\n", "LX_DEMOD_BW_6MHZ" );
			break;

		case 0x05:
			channelBW = LX_DEMOD_BW_5MHZ;
			DEMOD_PRINT("Bandwidth = %s\n", "LX_DEMOD_BW_5MHZ" );
			break;

		default:
			channelBW = LX_DEMOD_BW_UNKNOWN;
			DEMOD_PRINT("Bandwidth = %s\n", "LX_DEMOD_BW_UNKNOWN" );
			break;

	}

	pTpsParams->channelBW = channelBW;

	switch(signalStatus.fftMode)
	{
		case DEMOD_FFT_MODE_2K :
			FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_2K;
			DEMOD_PRINT(" FFTMode = %s\n","FFT_2K");
			break;

		case DEMOD_FFT_MODE_4K:
			FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_4K;
			DEMOD_PRINT("FFTMode = %s\n","FFT_4K");
			break;

		case DEMOD_FFT_MODE_8K:
			FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_8K;
			DEMOD_PRINT("FFTMode = %s\n","FFT_8K");
			break;

		default :
			FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN;
			DEMOD_PRINT("FFTMode = %s\n","FFT_UNKNOWN");
			break;
	}

	pTpsParams->FFTMode = FFTMode;

	switch(signalStatus.guardInterval)
	{
		case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_32 :
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_32;
			DEMOD_PRINT("Guard Interval = %s\n", "1_32" );
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_16:
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_16;
			DEMOD_PRINT("Guard Interval = %s\n", "1_16" );
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_8 :
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_8;
			DEMOD_PRINT("Guard Interval = %s\n", "1_8" );
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_4:
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_4;
			DEMOD_PRINT("Guard Interval = %s\n", "1_4" );
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_128:
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_128;
			DEMOD_PRINT("Guard Interval = %s\n", "1_128" );
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_19_128:
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_19_128;
			DEMOD_PRINT("Guard Interval = %s\n", "19_128" );
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_19_256:
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_19_256;
			DEMOD_PRINT("Guard Interval = %s\n", "19_256" );
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_64:
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_64;
			DEMOD_PRINT("Guard Interval = %s\n", "1_62" );
			break;
		default :
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_UNKNOWN;
			DEMOD_PRINT("Guard Interval = %s\n", "UNKNOWN" );
			break;
	}

	pTpsParams->gIMode = gIMode;

	switch(signalStatus.hierarchy)
	{
		case DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_NONE :
			hierachMode = LX_DEMOD_DVB_TPS_HIERACHY_NONE;
			DEMOD_PRINT("Hierachical Mode = %s\n", "NON Hierachical" );
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_ALFA1:
			hierachMode = LX_DEMOD_DVB_TPS_HIERACHY_1;
			DEMOD_PRINT("Hierachical Mode = %s\n", "alpha = 1" );
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_ALFA2 :
			hierachMode = LX_DEMOD_DVB_TPS_HIERACHY_2;
			DEMOD_PRINT("Hierachical Mode = %s\n", "alpha = 2" );
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_ALFA4:
			hierachMode = LX_DEMOD_DVB_TPS_HIERACHY_4;
			DEMOD_PRINT("Hierachical Mode = %s\n", "alpha = 3" );
			break;
		default :
			hierachMode = LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN;
			DEMOD_PRINT("Hierachical Mode = %s\n", "UNKNOWN MODE" );
			break;
	}
	pTpsParams->hierachMode = hierachMode;

	if(signalStatus.hierarchy_sel == DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_SEL_LP)
	{
		switch(signalStatus.codeRate)
		{
			case DEMOD_CODERATE_DVBT_ISDBT_1_2 :
				lpCodeRate = LX_DEMOD_CODE_1_2;
				DEMOD_PRINT("LP code rate = %s\n", "Code_1_2" );
				break;
			case DEMOD_CODERATE_DVBT_ISDBT_2_3:
				lpCodeRate = LX_DEMOD_CODE_2_3;
				DEMOD_PRINT("LP code rate = %s\n", "Code_2_3" );
				break;
			case DEMOD_CODERATE_DVBT_ISDBT_3_4 :
				lpCodeRate = LX_DEMOD_CODE_3_4;
				DEMOD_PRINT("LP code rate = %s\n", "Code_3_4" );
				break;
			case DEMOD_CODERATE_DVBT_ISDBT_5_6:
				lpCodeRate = LX_DEMOD_CODE_5_6;
				DEMOD_PRINT("LP code rate = %s\n", "Code_5_6" );
				break;
			case DEMOD_CODERATE_DVBT_ISDBT_7_8:
				lpCodeRate = LX_DEMOD_CODE_7_8;
				DEMOD_PRINT("LP code rate = %s\n", "Code_7_8" );
				break;
			default :
				lpCodeRate = LX_DEMOD_CODE_UNKNOWN;
				DEMOD_PRINT("LP code rate = %s\n", "Code UNKNOWN" );
				break;
		}
	}
	else
	{
		lpCodeRate = LX_DEMOD_CODE_UNKNOWN;
		DEMOD_PRINT("LP code rate = %s\n", "Code UNKNOWN" );
	}

	pTpsParams->lpCodeRate = lpCodeRate;

	if(signalStatus.hierarchy_sel == DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_SEL_HP)
	{
		switch(signalStatus.codeRate)
		{
			case DEMOD_CODERATE_DVBT_ISDBT_1_2 :
				hpCodeRate = LX_DEMOD_CODE_1_2;
				DEMOD_PRINT("HP code rate = %s\n", "Code_1_2" );
				break;
			case DEMOD_CODERATE_DVBT_ISDBT_2_3:
				hpCodeRate = LX_DEMOD_CODE_2_3;
				DEMOD_PRINT("HP code rate = %s\n", "Code_2_3" );
				break;
			case DEMOD_CODERATE_DVBT_ISDBT_3_4 :
				hpCodeRate = LX_DEMOD_CODE_3_4;
				DEMOD_PRINT("HP code rate = %s\n", "Code_3_4" );
				break;
			case DEMOD_CODERATE_DVBT_ISDBT_5_6:
				hpCodeRate = LX_DEMOD_CODE_5_6;
				DEMOD_PRINT("HP code rate = %s\n", "Code_5_6" );
				break;
			case DEMOD_CODERATE_DVBT_ISDBT_7_8:
				hpCodeRate = LX_DEMOD_CODE_7_8;
				DEMOD_PRINT("HP code rate = %s\n", "Code_7_8" );
				break;
			default :
				hpCodeRate = LX_DEMOD_CODE_UNKNOWN;
				DEMOD_PRINT("HP code rate = %s\n", "Code UNKNOWN" );
				break;
		}
	}
	else
	{
		hpCodeRate = LX_DEMOD_CODE_UNKNOWN;
		DEMOD_PRINT("HP code rate = %s\n", "Code UNKNOWN" );
	}
	pTpsParams->hpCodeRate = hpCodeRate;

	// get QAM mode
	if (RET_OK != DEMOD_M23_Get_QAMMode(&qamMode ))
	{
		DEMOD_ERROR("Fail, DEMOD_M23_Get_QAMMode()\n");
		return RET_ERROR;
	}

	pTpsParams->qamMode = qamMode;
	DEMOD_PRINT("modulation  = %s\n",
		(qamMode == LX_DEMOD_QPSK) ?   "QPSK"  :
		(qamMode == LX_DEMOD_16QAM) ?  "16QAM" :
		(qamMode == LX_DEMOD_64QAM) ?  "64QAM" : " UNKOWN MODE" );

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBT_Get_TotalInfo
 * Get all information on DVB-T for debug
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT_Get_TotalInfo (void)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	UINT16 			ifagcValue = 0;
	UINT32 			errorCount;
	SINT32 			FreqOff;
	LX_DEMOD_DVBT_CONFIG_T 	tppsParams;
	LX_DEMOD_LOCK_STATE_T 	agcLockStatus;
	LX_DEMOD_LOCK_STATE_T 	neverLockStatus;
	LX_DEMOD_LOCK_STATE_T 	txModeLock;
	LX_DEMOD_FFTMODE_T 	fftMode;
	LX_DEMOD_LOCK_STATE_T 	spectrumAuto;
	LX_DEMOD_LOCK_STATE_T 	spectrumInv;
	LX_DEMOD_MSE_T 		sigMse;

	DEMOD_PRINT("Start\n");

	pFrontend = DEMOD_Get_LGDBB_Context();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}


	if (RET_OK != DEMOD_M23_Get_Lock(LX_DEMOD_AGC_LOCK, &agcLockStatus))
	{
		DEMOD_WARN("Fail, DEMOD_M23_Get_Lock()\n");
		agcLockStatus = LX_DEMOD_UNKOWN_STATE;
	}
	if(LX_DEMOD_LOCKED == agcLockStatus)
	{
		ifagcValue = signalStatus.if_agc;
	}

	if (RET_OK != DEMOD_M23_Get_NeverLockStatus(LX_DEMOD_DVBT, &neverLockStatus))
	{
		DEMOD_WARN("Fail, DEMOD_M23_Get_NeverLockStatus()\n");
		neverLockStatus = LX_DEMOD_UNKOWN_STATE;
	}

	if (RET_OK !=  DEMOD_M23_Get_SpectrumStatus(&spectrumAuto, &spectrumInv))
	{
		DEMOD_WARN("Fail, DEMOD_M23_Get_SpectrumStatus()\n");
		spectrumInv = LX_DEMOD_UNKOWN_STATE;
	}

	switch(signalStatus.fftMode)
	{
		case DEMOD_FFT_MODE_2K :
			fftMode = LX_DEMOD_DVBT_ISDBT_FFT_2K;
			DEMOD_PRINT("FFTMode = %s\n","FFT_2K");
			break;
		case DEMOD_FFT_MODE_4K:
			fftMode = LX_DEMOD_DVBT_ISDBT_FFT_4K;
			DEMOD_PRINT("FFTMode = %s\n","FFT_4K");
			break;
		case DEMOD_FFT_MODE_8K:
			fftMode = LX_DEMOD_DVBT_ISDBT_FFT_8K;
			DEMOD_PRINT("FFTMode = %s\n","FFT_8K");
			break;
		default :
			fftMode = LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN;
			DEMOD_PRINT("FFTMode = %s\n","UNKNOWN");
			break;
	}

	errorCount = signalStatus.packetError;
	DEMOD_PRINT("TP Error Count= %d\n",errorCount);

	FreqOff 		= signalStatus.offsetFrq_Hz/1000;

	sigMse.bMse 		= 0;
	sigMse.mse 		= signalStatus.mse_info_eq;
	sigMse.constPwr 	= signalStatus.constPwr;
	txModeLock 		= signalStatus.demodLock ;

	DEMOD_PRINT("AGC LOCK is %s\n",(agcLockStatus == LX_DEMOD_LOCKED) ? " Locked" : " NOT Locked");
	DEMOD_PRINT("IF AGC value = %d(0x%x)\n",ifagcValue,ifagcValue);
	DEMOD_PRINT("Neverlock is %s\n",(neverLockStatus == LX_DEMOD_DETECTED) ? " Locked" : " NOT Locked");
	DEMOD_PRINT("Spectrum auto = %s, Inversion  = %s\n",(spectrumAuto == LX_DEMOD_AUTO) ? " Auto" : " Manual",
																					(spectrumInv == LX_DEMOD_INVERSION) ? " Inverted" : " Normal" );
	DEMOD_PRINT("FFT mode LOCK = %s\n",(txModeLock == LX_DEMOD_LOCKED) ? " Locked" : " NOT Locked");
	DEMOD_PRINT("offset = %d [KHz]\n",FreqOff);
	DEMOD_PRINT("mse = %d, constPwr = %d,\n",sigMse.mse, sigMse.constPwr);

	if (RET_OK != DEMOD_M23_DVBT_Get_TpsInfo( &tppsParams))
	{
		DEMOD_ERROR("Fail, DEMOD_M23_DVBT_Get_TpsInfo()\n");
		return RET_ERROR;
	}

	return RET_OK;
}




/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBT_Get_IFO_LOCK
 * Get IFO lock on DVB-T.
 *
 * @param *pSnr [OUT] BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT_Get_IFO_LOCK (BOOLEAN *pIfoLock)
{
	*pIfoLock = FALSE;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBT_EqualizereReset.
 * Reset DVB EQ module by software.
 *
 * @param  NONE
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT_EqualizereReset (void)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBT_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_M23_DVBT_Obtaining_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{
	static LX_DEMOD_FLAG_T 		scanProcessing = LX_DEMOD_FLAG_START;
	static LX_DEMOD_LOCK_STATE_T 	lockState = LX_DEMOD_UNLOCKED;
	static unsigned int 		sigStablestartTime = 0;
	LX_DEMOD_OPER_MODE_T 		operMode;
	unsigned int 			elapsedTime = 0;


	switch (pDemodInfo->controlState)
	{
		/***************************************************/
		/***** Configure tuner for desired channel No. *****/
		/***************************************************/
		case LX_DEMOD_TUNE_START:
			{
				elapsedTime = jiffies_to_msecs(jiffies)  - g_RetuneStartTime;
				DEMOD_PRINT("START_TIME (%d ms)\n", elapsedTime);

				if(RET_OK != _DEMOD_M23_DVBT_SetDemod(pDemodInfo))
				{
					DEMOD_ERROR("Fail, _DEMOD_M23_DVBT_SetDemod()\n");
					return RET_ERROR;
				}

				if(LX_DEMOD_TUNE_NORMAL != pDemodInfo->setCfgParam.dvbt.tuneMode)
				{
					if(RET_OK != DEMOD_M23_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_ON, &scanProcessing, &lockState))
					{
						DEMOD_ERROR("Fail, DEMOD_M23_NeverlockScan()\n");
						return RET_ERROR;
					}
					pDemodInfo->controlState 		= LX_DEMOD_TUNE_SCAN;
					_DVB_Full_Pkerr_Threshold 		= DVB_FULL_PACKET_ERROR;
					DEMOD_PRINT("LX_DEMOD_TUNE_START(AUTO or Manual SCAN) : Going to LX_DEMOD_TUNE_SCAN..... ^0^\n");
				}
				else
				{
					pDemodInfo->scanJobFlag 		= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState 		= LX_DEMOD_SYNC_CHECKING;
					_DVB_Full_Pkerr_Threshold 		= DVB_UNCHECK_PACKET_ERROR;
					DEMOD_PRINT("LX_DEMOD_TUNE_START(NORMAL SCAN) : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
				}
				elapsedTime = jiffies_to_msecs(jiffies) - g_RetuneStartTime;
				DEMOD_PRINT("END_TIME (%d ms)\n", elapsedTime);
			}

			break;
						/***************************************************/
						/***** Configure demod for scan mode. *****/
		case LX_DEMOD_TUNE_SCAN:	/***************************************************/
			{
				if((LX_DEMOD_FLAG_COMPLETE == pDemodInfo->scanJobFlag) || (LX_DEMOD_FLAG_FINISH == pDemodInfo->scanJobFlag))
				{
					pDemodInfo->controlState = LX_DEMOD_SYNC_CHECKING;
					DEMOD_PRINT("Already Done\n");
					DEMOD_PRINT("LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
					return RET_OK;
				}

				if(RET_OK != DEMOD_M23_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_OFF, &scanProcessing, &lockState))
				{
					DEMOD_ERROR("Fail, DEMOD_M23_NeverlockScan()\n");
					return RET_ERROR;
				}

				if((LX_DEMOD_FLAG_FINISH == scanProcessing) && (LX_DEMOD_LOCKED == lockState))
				{
					pDemodInfo->operMode 			= LX_DEMOD_DVBT;
					pDemodInfo->scanJobFlag 		= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState 		= LX_DEMOD_SYNC_CHECKING;

					DEMOD_PRINT("Signal is Found\n");
					DEMOD_PRINT("LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
				}
				else if((LX_DEMOD_FLAG_FINISH == scanProcessing)&& (LX_DEMOD_UNLOCKED == lockState))
				{
					pDemodInfo->scanJobFlag 		= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->bNotifiedUnlock		= TRUE;
					pDemodInfo->bNotifiedLock		= FALSE;
					pDemodInfo->lockStatus			= LX_DEMOD_UNLOCKED;
					pDemodInfo->signalStatus.bSignalValid 	= FALSE;
					pDemodInfo->controlState 		= LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK;

					elapsedTime 				= jiffies_to_msecs(jiffies) - g_RetuneStartTime;

					DEMOD_NOTI("LX_DEMOD_TUNE_SCAN : MSG_DVBT_FRONT_END_NOT_LOCKED..\n") ;
					DEMOD_NOTI("LX_DEMOD_TUNE_SCAN : Elapse time is %d msec\n", elapsedTime) ;
					DEMOD_PRINT("Signal is NOT Found\n");
				}
				else
				{
					pDemodInfo->scanJobFlag 		= LX_DEMOD_FLAG_ING;
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
				if(RET_OK != DEMOD_M23_Get_OperMode(&operMode))
				{
					DEMOD_ERROR("Fail, DEMOD_M23_Get_OperMode()\n");
					return RET_ERROR;

				}

				DEMOD_PRINT("[DEMOD ] LX_DEMOD_SYNC_CHECKING() operMode = 0x%x!!!\n", operMode);

				if(LX_DEMOD_DVBT2 == operMode)
				{
					DEMOD_PRINT("Before pDemodInfo->setCfgParam.dvbt2.unPLP = %d\n", pDemodInfo->setCfgParam.dvbt2.unPLP);

					pDemodInfo->operMode 						= LX_DEMOD_DVBT2;
					pDemodInfo->setCfgParam.dvbt2.tuneMode 	= pDemodInfo->setCfgParam.dvbt.tuneMode;
					pDemodInfo->setCfgParam.dvbt2.channelBW	= pDemodInfo->setCfgParam.dvbt.channelBW;

					if(pDemodInfo->setCfgParam.dvbt2.tuneMode != LX_DEMOD_TUNE_NORMAL)			pDemodInfo->setCfgParam.dvbt2.unPLP = 255;
					DEMOD_PRINT("After pDemodInfo->setCfgParam.dvbt2.tuneMode = %d\n", pDemodInfo->setCfgParam.dvbt2.tuneMode);
					DEMOD_PRINT("After pDemodInfo->setCfgParam.dvbt2.unPLP = %d\n", pDemodInfo->setCfgParam.dvbt2.unPLP);

					DEMOD_PRINT("LX_DEMOD_SYNC_CHECKING :Set PLP ID to 0x%x.....\n",pDemodInfo->setCfgParam.dvbt2.unPLP);
					DEMOD_PRINT("LX_DEMOD_SYNC_CHECKING(DVBT) : Going to LX_DEMOD_SYNC_CHECKING(DVBT2 forcely)..... ^0^\n");

					return RET_OK;
				}

				if(RET_OK != DEMOD_M23_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
				{
					DEMOD_ERROR("Fail, DEMOD_M23_Get_Lock()\n");
					return RET_ERROR;
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					pDemodInfo->controlState		= LX_DEMOD_SIGNAL_STABLE;
					sigStablestartTime 			= jiffies_to_msecs(jiffies);

					DEMOD_PRINT("LX_DEMOD_SYNC_CHECKING : Going to LX_DEMOD_SIGNAL_STABLE..... ^0^\n");
				}
				else
				{
				 	/* nothing to do so far */
				}
			}
		   break;

	   	/********************************************/
	   	/***** Attempting to obtain signal stability *****/
		/********************************************/
	   	case LX_DEMOD_SIGNAL_STABLE:
			{
				SINT32			freqOffset;

				if(RET_OK != DEMOD_M23_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
				{
					DEMOD_ERROR("Fail, DEMOD_M23_Get_Lock()\n");
					return RET_ERROR;
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					pDemodInfo->lockStatus			= LX_DEMOD_LOCKED;
					pDemodInfo->signalStatus.bSignalValid	= TRUE;
					pDemodInfo->bNotifiedLock		= TRUE;
					pDemodInfo->bNotifiedUnlock		= FALSE;
					elapsedTime 				= jiffies_to_msecs(jiffies) - g_RetuneStartTime;

					DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : MSG_DVBT_FRONT_END_LOCKED..... ^^^0^^^\n");
					DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^^^0^^^\n", elapsedTime);


					if (RET_OK != DEMOD_M23_Get_CarrierFreqOffset(&freqOffset))
					{
						DEMOD_ERROR("Fail, DEMOD_M23_Get_CarrierFreqOffset()\n");
						return RET_ERROR;
					}
					pDemodInfo->freqOffset 			= freqOffset;
					pDemodInfo->controlState				= LX_DEMOD_SIGNAL_LOCKED;
					DEMOD_PRINT("LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^^^0^^^\n", freqOffset);

					if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
					{
						DEMOD_ERROR("Fail, DEMOD_Get_TunedCFG()\n");
						return RET_ERROR;
					}

					if (RET_OK != _DEMOD_M23_DVB_CheckSignalState(pDemodInfo))
					{
						DEMOD_ERROR("Fail, _DEMOD_M23_DVB_CheckSignalState()\n");
						return RET_ERROR;
					}

				}
				else
				{
//					pDemodInfo->controlState		= LX_DEMOD_SYNC_CHECKING;
//					DEMOD_PRINT("LX_DEMOD_SIGNAL_STABLE : Going back to LX_DEMOD_SYNC_CHECKING.....\n");
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
 * DEMOD_M23_DVBT_Monitoring_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_M23_DVBT_Monitoring_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_LOCK_STATE_T			lockState;
	LX_DEMOD_OPER_MODE_T 			operMode;

	if(RET_OK != DEMOD_M23_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
	{
		DEMOD_ERROR("Fail, DEMOD_M23_Get_Lock()\n");
		return RET_ERROR;
	}

	if(LX_DEMOD_LOCKED == lockState)
	{
		pDemodInfo->unLockCount = 0;

		if (RET_OK != _DEMOD_M23_DVB_CheckSignalState(pDemodInfo))
		{
			DEMOD_ERROR("Fail, _DEMOD_M23_DVB_CheckSignalState()\n");
			return RET_ERROR;
		}

		if(pDemodInfo->signalStatus.packetError >= _DVB_Full_Pkerr_Threshold)
		{
			_DVB_Full_Pkerr_Count++;
			DEMOD_PRINT("_DVB_Full_Pkerr_Count = %d\n",_DVB_Full_Pkerr_Count);

			if(_DVB_Full_Pkerr_Count == _DVBT_Full_Pkerr_Count_Threshold)
			{
				DEMOD_WARN("Oops !! Force to NOT LOCK by Full Packet error Count !!\n");
				_DVB_Full_Pkerr_Count = 0;

				if(RET_OK != DEMOD_M23_SoftwareReset())
				{
					DEMOD_ERROR("Fail, DEMOD_M23_SoftwareReset()\n");
					return RET_ERROR;
				}
				DEMOD_PRINT("SUCCESS DEMOD_M23_SoftwareReset()\n");

				pDemodInfo->lockStatus				= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedUnlock 			= TRUE;
				pDemodInfo->bNotifiedLock			= FALSE;
				pDemodInfo->signalStatus.bSignalValid 		= FALSE;

				DEMOD_NOTI("MSG_DVBT_FRONT_END_NOT_LOCKED by Full packet error ..... -_-;;\n");
			}
		}
		else
		{
			if(RET_OK != DEMOD_M23_Get_OperMode(&operMode))
			{
				DEMOD_ERROR("Fail, DEMOD_M23_Get_OperMode()\n");
				return RET_ERROR;
			}

			if(operMode == LX_DEMOD_DVBT2)
			{
				pDemodInfo->operMode 				= LX_DEMOD_DVBT2;
				pDemodInfo->setCfgParam.dvbt2.tuneMode 		= pDemodInfo->setCfgParam.dvbt.tuneMode;
				pDemodInfo->setCfgParam.dvbt2.channelBW		= pDemodInfo->setCfgParam.dvbt.channelBW;

				DEMOD_PRINT("Fail, forcely changed to DVBT2 mode\n");
				DEMOD_PRINT("tuneMode(DVBT2)  = %d\n", pDemodInfo->setCfgParam.dvbt2.tuneMode);
				_DVB_Full_Pkerr_Count 		= 0;

				return RET_OK;
			}

			if((LX_DEMOD_LOCKED != pDemodInfo->lockStatus)	&& (TRUE != pDemodInfo->bNotifiedLock))
			{
				pDemodInfo->lockCount++;
				DEMOD_PRINT("pDemodInfo->lockCount = %d\n",pDemodInfo->lockCount);
			}
			if(pDemodInfo->lockCount == 1)
			{
				pDemodInfo->lockStatus				= LX_DEMOD_LOCKED;
				pDemodInfo->bNotifiedLock			= TRUE;
				pDemodInfo->bNotifiedUnlock 			= FALSE;
				pDemodInfo->signalStatus.bSignalValid 		= TRUE;
				pDemodInfo->lockCount 				= 0;

				DEMOD_NOTI("MSG_DVBT_FRONT_END_LOCKED..... ^0^\n");

				if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
				{
					pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;
				}
			}

			if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
			{
				DEMOD_ERROR("Fail, DEMOD_Get_TunedCFG()\n");
				return RET_ERROR;
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
			DEMOD_PRINT("pDemodInfo->unLockCount = %d\n",pDemodInfo->unLockCount);

			if(pDemodInfo->unLockCount == _DVBT_Unlock_Count_Threshold)
			{
				pDemodInfo->lockStatus 				= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedUnlock 			= TRUE;
				pDemodInfo->bNotifiedLock			= FALSE;
				pDemodInfo->signalStatus.bSignalValid 		= FALSE;
				_DVB_Full_Pkerr_Count 		= 0;
				pDemodInfo->unLockCount 			= 0;

				DEMOD_NOTI("MSG_DVBT_FRONT_END_NOT_LOCKED by unLockCount..... -_-\n");
			}

		}
	}
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBT2_Set_Config_auto
 * Control automatic setting of DVB-T config.
 *
 * @param bAutoDetect 	[IN] BOOLEAN - automatic setting (TRUE) / manual setting(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT2_Set_Config_auto (BOOLEAN bAutoDetect)
{
	DEMOD_INFO("deprecated\n");
/*
	LX_DEMOD_L2_Context *	pFrontend;

	DEMOD_PRINT("Start\n");
	DEMOD_NOTI("Set to %s\n", (bAutoDetect == TRUE)?"AUTO":"MANUAL");

	pFrontend = DEMOD_Get_LGDBB_Context();


	if(bAutoDetect == TRUE)
	{
		if(DEMOD_L2_DVB_AutoModeDetectOn(pFrontend))
		{
			DEMOD_ERROR("Fail, DEMOD_L2_DVB_AutoModeDetectOn()\n");
			return RET_ERROR;
		}
	}
	else
	{
		if(DEMOD_L2_DVB_AutoModeDetectOff(pFrontend))
		{
			DEMOD_ERROR("Fail, DEMOD_L2_DVB_AutoModeDetectOff()\n");
			return RET_ERROR;
		}
	}
*/
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 DEMOD_M23_DVBT2_Set_PartialConfig
 * Set all config parameters on DVB-T.
 * This function is used when LX_DEMOD_M23_DVBT_Set_Config_auto is disabled.
 *
 * @param *pDvbtConfigParam 	[IN] LX_DEMOD_DVBT_CONFIG_T - DVB-T config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT2_Set_PartialConfig (LX_DEMOD_DVBT2_CONFIG_T *pDvbt2ConfigParam)
{
	LX_DEMOD_L2_Context * 	pFrontend;
//	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	UINT8			plp_id = pDvbt2ConfigParam->unPLP;
	int			retc = NO_DEMOD_ERROR;

	DEMOD_PRINT("Start\n");
	DEMOD_PRINT("DVBT2_PLP ID = [0x%x]\n",  plp_id);

	pFrontend = DEMOD_Get_LGDBB_Context();

	retc = DEMOD_L2_DVB_Set_PLP_Select(pFrontend,  plp_id, DEMOD_CMD_DVBT2_PLP_SELECT_PLP_ID_SEL_MODE_MANUAL);

	if(retc != NO_DEMOD_ERROR)
	{
		DEMOD_PRINT ("[DEMOD_CHIP] ERROR, DEMOD_L2_DVB_Set_PLP_Select error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return RET_ERROR;
	}

	pFrontend->set_PLP_ID 			= plp_id;
	_DVB_Full_Pkerr_Threshold 		= DVB_UNCHECK_PACKET_ERROR;

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBT2_Get_FFTMode
 * Get the information of bandwidth on DVB-T.
 *
 * @param *pTxModeLock 	[OUT] LX_DEMOD_LOCK_STATE_T - FFT mode lock state.
 * @param *pFftMode 	[OUT] LX_DEMOD_FFTMODE_T - detected FFT mode.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT2_Get_FFTMode (LX_DEMOD_LOCK_STATE_T *pTxModeLock, LX_DEMOD_FFTMODE_T *pFftMode)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("Start\n");

	pFrontend 	= DEMOD_Get_LGDBB_Context();
	*pTxModeLock 	= LX_DEMOD_LOCKED;
	*pFftMode 	= LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}

	switch(signalStatus.fftMode)
	{
		case DEMOD_FFT_MODE_2K :
			*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_2K;
			break;

		case DEMOD_FFT_MODE_8K:
			*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_8K;
			break;

		case DEMOD_FFT_MODE_4K:
			*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_4K;
			break;

		case DEMOD_FFT_MODE_1K:
			*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_1K;
			break;

		case DEMOD_FFT_MODE_16K:
			*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_16K;
			break;

		case DEMOD_FFT_MODE_32K:
			*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_32K;
			break;

		default :
			*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN;
			break;
	}

	if(signalStatus.bw_Ext)
	{
		DEMOD_PRINT("Extended .....FFT mode\n");
	}
	else
	{
		DEMOD_PRINT("Normal .....FFT mode\n");
	}

	return RET_OK;

}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBT2_Get_GuradIntervalMode
 * Get the information of guard interval on DVB-T.
 *
 * @param *pGIMode 	[OUT] LX_DEMOD_GIMODE_T - 1/32, 1/16, 1/8 and 1/4.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT2_Get_GuradIntervalMode (LX_DEMOD_GIMODE_T *pGIMode)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("Start\n");

	pFrontend = DEMOD_Get_LGDBB_Context();
	*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_UNKNOWN;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}
	switch(signalStatus.guardInterval)
	{
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_4 :
			*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_4;
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_8 :
			*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_8;
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_16 :
			*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_16;
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_32 :
			*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_32;
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_19_128 :
			*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_19_128;
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_19_256:
			*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_19_256;
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_128:
			*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_128;
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_64:
			*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_64;
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
 * DEMOD_M23_DVBT2_Get_CoderRate
 * Get the information of LP code rate on DVB-T2.
 *
 * @param *pLpCodeRate[OUT] LX_DEMOD_CODERATE_T - code rate : 1/2, 2/3, 3/4, 5/6 and 7/8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT2_Get_CoderRate (LX_DEMOD_CODERATE_T *pCodeRate)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("Start\n");

	pFrontend = DEMOD_Get_LGDBB_Context();
	*pCodeRate = LX_DEMOD_CODE_UNKNOWN;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}

	switch(signalStatus.codeRate)
	{
		case DEMOD_CODERATE_DVBT2_1_2 :
			*pCodeRate = LX_DEMOD_CODE_1_2;
			break;
		case DEMOD_CODERATE_DVBT2_3_5:
			*pCodeRate = LX_DEMOD_CODE_3_5;
			break;
		case DEMOD_CODERATE_DVBT2_2_3 :
			*pCodeRate = LX_DEMOD_CODE_2_3;
			break;
		case DEMOD_CODERATE_DVBT2_3_4:
			*pCodeRate = LX_DEMOD_CODE_3_4;
			break;
		case DEMOD_CODERATE_DVBT2_4_5:
			*pCodeRate = LX_DEMOD_CODE_4_5;
			break;
		case DEMOD_CODERATE_DVBT2_5_6:
			*pCodeRate = LX_DEMOD_CODE_5_6;
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
 * DEMOD_M23_DVBT2_Get_CurrentPLP_ID
 * Get current PLP ID on DVB-T2.
 *
 * @param *pCurrPlpID 	[OUT] UINT8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT2_Get_CurrentPLP_ID (UINT8 *pCurrPlpID)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("Start\n");

	pFrontend = DEMOD_Get_LGDBB_Context();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}

	*pCurrPlpID = signalStatus.current_plp_id;

	DEMOD_PRINT("Current PLP ID = %d\n",signalStatus.current_plp_id);

	return RET_OK;
}
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBT2_Get_PlpInfo
 * Get TPS information on DVB-T
 *
 * @param *pTpsParams [OUT] LX_DEMOD_DVBT_CONFIG_T - TPS data structure.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT2_Get_PlpInfo (LX_DEMOD_DVBT2_CONFIG_T *pPlpParams)
{
	LX_DEMOD_L2_Context * 	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	LX_DEMOD_BWMODE_T 	channelBW 	= LX_DEMOD_BW_UNKNOWN;
	LX_DEMOD_FFTMODE_T 	FFTMode 	= LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN ;
	LX_DEMOD_GIMODE_T 	gIMode 		= LX_DEMOD_DVBT_ISDBT_GIMODE_UNKNOWN;
	LX_DEMOD_CODERATE_T 	codeRate 	= LX_DEMOD_CODE_UNKNOWN;
	LX_DEMOD_RF_MODE_T 	qamMode 	= LX_DEMOD_UNKOWN_MODE;

	DEMOD_PRINT("Start\n");

	pFrontend = DEMOD_Get_LGDBB_Context();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_SignalStatus()\n");
		return RET_ERROR;
	}

	if(NULL == pPlpParams)
	{
		DEMOD_ERROR("Fail, DEMOD_M23_DVBT_CONFIG_T TpsParams is NULL\n");
		return RET_ERROR;
	}

	switch(signalStatus.bandwidth)
	{
		case 0x08:
			channelBW = LX_DEMOD_BW_8MHZ;
			DEMOD_PRINT("Bandwidth = 8MHz\n");
			break;
		case 0x07:
			channelBW = LX_DEMOD_BW_7MHZ;
			DEMOD_PRINT("Bandwidth = 7MHz\n");
			break;
		case 0x06:
			channelBW = LX_DEMOD_BW_6MHZ;
			DEMOD_PRINT("Bandwidth = 6MHz\n");
			break;
		case 0x05:
			channelBW = LX_DEMOD_BW_5MHZ;
			DEMOD_PRINT("Bandwidth = 5MHz\n");
			break;
		default:
			channelBW = LX_DEMOD_BW_UNKNOWN;
			DEMOD_PRINT("Bandwidth = UNKNOWN\n");
			break;
	}

	pPlpParams->channelBW = channelBW;

	switch(signalStatus.fftMode)
	{
		case DEMOD_FFT_MODE_2K :
			FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_2K;
			DEMOD_PRINT("FFTMode = FFT_2K\n");
			break;
		case DEMOD_FFT_MODE_8K:
			FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_8K;
			DEMOD_PRINT("FFTMode = FFT_8K\n");
			break;
		case DEMOD_FFT_MODE_4K:
			FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_4K;
			DEMOD_PRINT("FFTMode = FFT_4K\n");
			break;
		case DEMOD_FFT_MODE_1K:
			FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_1K;
			DEMOD_PRINT("FFTMode = FFT_1K\n");
			break;
		case DEMOD_FFT_MODE_16K:
			FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_16K;
			DEMOD_PRINT("FFTMode = FFT_16K\n");
			break;
		case DEMOD_FFT_MODE_32K:
			FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_32K;
			DEMOD_PRINT("FFTMode = FFT_32K\n");
			break;
		default :
			FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN;
			DEMOD_PRINT("FFTMode = FFT_UNKNOWN\n");
			break;
	}

	pPlpParams->FFTMode = FFTMode;

	switch(signalStatus.guardInterval)
	{
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_4 :
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_4;
			DEMOD_PRINT("Guard Interval = 1_4\n");
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_8 :
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_8;
			DEMOD_PRINT("Guard Interval = 1_8\n");
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_16 :
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_16;
			DEMOD_PRINT("Guard Interval = 1_16\n");
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_32 :
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_32;
			DEMOD_PRINT("Guard Interval = 1_32\n");
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_19_128 :
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_19_128;
			DEMOD_PRINT("Guard Interval = 19_128\n");
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_19_256:
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_19_256;
			DEMOD_PRINT("Guard Interval = 19_256\n");
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_128:
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_128;
			DEMOD_PRINT("Guard Interval = 1_128\n");
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_64:
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_64;
			DEMOD_PRINT("Guard Interval = 1_64\n");
			break;
		default :
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_UNKNOWN;
			DEMOD_PRINT("Guard Interval = UNKNOWN\n");
			break;
	}

	pPlpParams->gIMode = gIMode;

	switch(signalStatus.codeRate)
	{
		case DEMOD_CODERATE_DVBT2_1_2 :
			codeRate = LX_DEMOD_CODE_1_2;
			DEMOD_PRINT("code rate = LX_DEMOD_CODE_1_2\n");
			break;
		case DEMOD_CODERATE_DVBT2_3_5:
			codeRate = LX_DEMOD_CODE_3_5;
			DEMOD_PRINT("code rate = LX_DEMOD_CODE_3_5\n");
			break;
		case DEMOD_CODERATE_DVBT2_2_3 :
			codeRate = LX_DEMOD_CODE_2_3;
			DEMOD_PRINT("code rate = LX_DEMOD_CODE_2_3\n");
			break;
		case DEMOD_CODERATE_DVBT2_3_4:
			codeRate = LX_DEMOD_CODE_3_4;
			DEMOD_PRINT("code rate = LX_DEMOD_CODE_3_4\n");
			break;
		case DEMOD_CODERATE_DVBT2_4_5:
			codeRate = LX_DEMOD_CODE_4_5;
			DEMOD_PRINT("code rate = LX_DEMOD_CODE_4_5\n");
			break;
		case DEMOD_CODERATE_DVBT2_5_6:
			codeRate = LX_DEMOD_CODE_5_6;
			DEMOD_PRINT("code rate = LX_DEMOD_CODE_5_6\n");
			break;
		default :
			codeRate = LX_DEMOD_CODE_UNKNOWN;
			DEMOD_PRINT("code rate = UNKNOWN\n");
			break;
	}
	pPlpParams->codeRate = codeRate;

	switch(signalStatus.constellation)
	{
		case DEMOD_CONSTELLATION_QPSK :
			qamMode = LX_DEMOD_QPSK;
			DEMOD_PRINT("modulation = LX_DEMOD_QPSK\n");
			break;
		case DEMOD_CONSTELLATION_QAM16 :
			qamMode = LX_DEMOD_16QAM;
			DEMOD_PRINT("modulation = LX_DEMOD_16QAM\n");
			break;
		case DEMOD_CONSTELLATION_QAM32:
			qamMode = LX_DEMOD_32QAM;
			DEMOD_PRINT("modulation = LX_DEMOD_32QAM\n");
			break;
		case DEMOD_CONSTELLATION_QAM64 :
			qamMode = LX_DEMOD_64QAM;
			DEMOD_PRINT("modulation = LX_DEMOD_64QAM\n");
			break;
		case DEMOD_CONSTELLATION_QAM128 :
			qamMode = LX_DEMOD_128QAM;
			DEMOD_PRINT("modulation = LX_DEMOD_128QAM\n");
			break;
		case DEMOD_CONSTELLATION_QAM256 :
			qamMode = LX_DEMOD_256QAM;
			DEMOD_PRINT("modulation = LX_DEMOD_256QAM\n");
			break;
		default :
			qamMode = LX_DEMOD_UNKOWN_MODE;
			DEMOD_PRINT("modulation = LX_DEMOD_UNKOWN_MODE\n");
			break;
	}

	pPlpParams->qamMode = qamMode;
	pPlpParams->unPLP = signalStatus.current_plp_id;

	DEMOD_PRINT("current PLP ID = 0x%x set PLP ID = 0x%x\n",pPlpParams->unPLP, pFrontend->set_PLP_ID);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBT2_Get_multiPLP_ID
 * Get TPS information on DVB-T
 *
 * @param *pTpsParams [OUT] LX_DEMOD_DVBT_CONFIG_T - TPS data structure.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT2_Get_multiPLP_ID (LX_DEMOD_DVBT2_MULTI_PLP_INFO_T *pPlpParams)
{
	LX_DEMOD_L2_Context *	pFrontend;

	LX_DEMOD_L2_MULTI_PLP_ID_T 	PlpParams;
	UINT8 plpCount;
	int retc;
	int i ;
	
	DEMOD_PRINT("Start\n");

	pFrontend = DEMOD_Get_LGDBB_Context();

	// get multi-plp Id
	retc = DEMOD_L2_DVB_Get_PLP_ID(pFrontend, &PlpParams);

	for ( i = 0 ; i < 10 ; i++)
	{
		if (PlpParams.plpTotalCount == 0)
		{
			DEMOD_NOTI("DEMOD_L2_DVB_Get_PLP_ID updateing (returnvalue is %d)\n", retc);			
			retc = DEMOD_L2_DVB_Get_PLP_ID(pFrontend, &PlpParams);
		}
		else
		{
			DEMOD_NOTI("DEMOD_L2_DVB_Get_PLP_ID Update Done (%d)\n", i );
			break;
		}
		usleep_range(10000,11000);	/* 10ms ~ 11ms */
	}

	if (RET_OK != retc)
	{
		DEMOD_ERROR("Fail, DEMOD_L2_DVB_Get_PLP_ID() (returnvalue is %d)\n", retc);
		return RET_ERROR;
	}

	pPlpParams->plpTotalCount = PlpParams.plpTotalCount; //htlim 0119

	for(plpCount = 0; plpCount < PlpParams.plpCount_Including_channInfo; plpCount++  )
	{
		pPlpParams->plpDataID[plpCount] = PlpParams.plpID[plpCount];
		pPlpParams->plpDatacount = plpCount + 1;
	}

	for(plpCount = 0; plpCount < (PlpParams.plpTotalCount - PlpParams.plpCount_Including_channInfo); plpCount++  )
	{
		pPlpParams->commonPlpID[plpCount] = PlpParams.plpID[plpCount+PlpParams.plpCount_Including_channInfo]; // htlim 0116
		pPlpParams->commonPlpCount = plpCount + 1;
	}

	if(PlpParams.plpCount_Including_channInfo == 0)
	{
		pPlpParams->plpDatacount = 0;
	}

	if(PlpParams.plpTotalCount - PlpParams.plpCount_Including_channInfo == 0)
	{
		pPlpParams->commonPlpCount = 0;
	}

	DEMOD_PRINT("PLP TotalCount = %d\n",pPlpParams->plpTotalCount);
	DEMOD_PRINT("PlpParams.plpCount_Including_channInfo = %d\n",PlpParams.plpCount_Including_channInfo);
	DEMOD_PRINT("PLP Datacount = %d\n",pPlpParams->plpDatacount);
	DEMOD_PRINT("PLP CommonPlpCount = %d\n",pPlpParams->commonPlpCount);

	for(plpCount=0; plpCount < pPlpParams->plpDatacount; plpCount++)
	{
		DEMOD_PRINT("PLP Data ID[%d] = 0x%x\n",plpCount, pPlpParams->plpDataID[plpCount]);

	}
	for(plpCount=0; plpCount < pPlpParams->commonPlpCount; plpCount++)
	{
		DEMOD_PRINT("PLP Common PLP ID[%d] = 0x%x\n",plpCount, pPlpParams->commonPlpID[plpCount]);
	}

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBT2_Get_TotalInfo
 * Get all information on DVB-T for debug
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_M23_DVBT2_Get_TotalInfo (void)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	UINT16 			ifagcValue = 0;
	UINT32 			errorCount;
	SINT32 			FreqOff;

	LX_DEMOD_DVBT2_CONFIG_T plpParams;
	LX_DEMOD_LOCK_STATE_T 	agcLockStatus;
	LX_DEMOD_LOCK_STATE_T 	neverLockStatus;
	LX_DEMOD_LOCK_STATE_T 	spectrumAuto;
	LX_DEMOD_LOCK_STATE_T 	spectrumInv;
	LX_DEMOD_MSE_T 		sigMse;
	LX_DEMOD_DVBT2_MULTI_PLP_INFO_T plpInfo;

	DEMOD_PRINT("Start\n");

	pFrontend = DEMOD_Get_LGDBB_Context();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_ERROR("Fail, DEMOD_L2_DVB_Get_PLP_ID()\n");
		return RET_ERROR;
	}

	if (RET_OK != DEMOD_M23_Get_Lock(LX_DEMOD_AGC_LOCK, &agcLockStatus))
	{
		DEMOD_WARN("Fail, DEMOD_M23_Get_Lock()\n");
		agcLockStatus = LX_DEMOD_UNKOWN_STATE;
	}

	if(LX_DEMOD_LOCKED == agcLockStatus)
	{
		ifagcValue = signalStatus.if_agc;
	}

	if (RET_OK != DEMOD_M23_Get_NeverLockStatus(LX_DEMOD_DVBT2, &neverLockStatus))
	{
		DEMOD_WARN("Fail, DEMOD_M23_Get_NeverLockStatus()\n");
		neverLockStatus = LX_DEMOD_UNKOWN_STATE;
	}

	if (RET_OK !=  DEMOD_M23_Get_SpectrumStatus(&spectrumAuto, &spectrumInv))
	{
		DEMOD_WARN("Fail, DEMOD_M23_Get_SpectrumStatus()\n");
		spectrumInv = LX_DEMOD_UNKOWN_STATE;
	}

	errorCount = signalStatus.packetError;
	DEMOD_PRINT("TP Error Count= %d\n",errorCount);

	FreqOff = signalStatus.offsetFrq_Hz/1000;

	sigMse.bMse = 0;
	sigMse.mse = signalStatus.mse_info_eq;
	sigMse.constPwr = signalStatus.constPwr;

	DEMOD_PRINT("IF AGC value = %d(0x%x)\n",ifagcValue,ifagcValue);
	DEMOD_PRINT("Neverlock is %s\n",(neverLockStatus == LX_DEMOD_DETECTED) ? " Locked" : " NOT Locked");
	DEMOD_PRINT("Spectrum auto = %s, Inversion  = %s\n",(spectrumAuto == LX_DEMOD_AUTO) ? " Auto" : " Manual",
																					(spectrumInv == LX_DEMOD_INVERSION) ? " Inverted" : " Normal" );
	DEMOD_PRINT("offset = %d [KHz]\n",FreqOff);
	DEMOD_PRINT("mse = %d, constPwr = %d\n",sigMse.mse, sigMse.constPwr);

	if (RET_OK != DEMOD_M23_DVBT2_Get_PlpInfo( &plpParams))
	{
		DEMOD_ERROR("Fail, DEMOD_M23_DVBT2_Get_PlpInfo()\n");
		return RET_ERROR;
	}
	if (RET_OK != DEMOD_M23_DVBT2_Get_multiPLP_ID(&plpInfo))
	{
		DEMOD_ERROR("Fail, DEMOD_M23_DVBT2_Get_multiPLP_ID()\n");
		return RET_ERROR;
	}

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_M23_DVBT2_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_M23_DVBT2_Obtaining_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{

	static LX_DEMOD_FLAG_T 		scanProcessing = LX_DEMOD_FLAG_START;
	static LX_DEMOD_LOCK_STATE_T 	lockState = LX_DEMOD_UNLOCKED;
	static unsigned int 		sigStablestartTime = 0;
	LX_DEMOD_OPER_MODE_T 		operMode;
	unsigned int 			elapsedTime = 0;

	switch (pDemodInfo->controlState)
	{
		/***************************************************/
		/***** Configure tuner for desired channel No. *****/
		/***************************************************/
		case LX_DEMOD_TUNE_START:
			{
				if(RET_OK != _DEMOD_M23_DVBT2_SetDemod(pDemodInfo))
				{
					DEMOD_ERROR("Fail, _DEMOD_M23_DVBT2_SetDemod()\n");
					return RET_ERROR;
				}

				if(LX_DEMOD_TUNE_NORMAL != pDemodInfo->setCfgParam.dvbt2.tuneMode)
				{
					if(RET_OK != DEMOD_M23_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_ON, &scanProcessing, &lockState))
					{
						DEMOD_ERROR("Fail, DEMOD_M23_NeverlockScan()\n");
						return RET_ERROR;
					}
					pDemodInfo->controlState 	= LX_DEMOD_TUNE_SCAN;
					_DVB_Full_Pkerr_Threshold 	= DVB_FULL_PACKET_ERROR;
					DEMOD_PRINT("LX_DEMOD_TUNE_START(AUTO or Manual SCAN) : Going to LX_DEMOD_TUNE_SCAN..... ^0^\n");
				}
				else
				{
					pDemodInfo->scanJobFlag 	= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState 	= LX_DEMOD_SYNC_CHECKING;
					_DVB_Full_Pkerr_Threshold 	= DVB_UNCHECK_PACKET_ERROR;
					DEMOD_PRINT("LX_DEMOD_TUNE_START(NORMAL SCAN) : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
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
					DEMOD_PRINT("Already Done\n");
					DEMOD_PRINT("LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
					return RET_OK;
				}

				if(RET_OK != DEMOD_M23_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_OFF, &scanProcessing, &lockState))
				{
					DEMOD_ERROR("Fail, DEMOD_M23_NeverlockScan()\n");
					return RET_ERROR;
				}

				if((LX_DEMOD_FLAG_FINISH == scanProcessing) && (LX_DEMOD_LOCKED == lockState))
				{
					pDemodInfo->operMode 		= LX_DEMOD_DVBT2;
					pDemodInfo->scanJobFlag 	= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState 	= LX_DEMOD_SYNC_CHECKING;

					DEMOD_PRINT("Signal is Found\n");
					DEMOD_PRINT("LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
				}
				else if((LX_DEMOD_FLAG_FINISH == scanProcessing)&& (LX_DEMOD_UNLOCKED == lockState))
				{
					pDemodInfo->scanJobFlag 	= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->bNotifiedUnlock	= TRUE;
					pDemodInfo->bNotifiedLock	= FALSE;
					pDemodInfo->lockStatus		= LX_DEMOD_UNLOCKED;
					pDemodInfo->controlState 	= LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK;
					elapsedTime 			= jiffies_to_msecs(jiffies) - g_NewTuneReqeustTime;

					DEMOD_NOTI("LX_DEMOD_TUNE_SCAN : MSG_DVBT_FRONT_END_NOT_LOCKED..\n") ;
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
				if(RET_OK != DEMOD_M23_Get_OperMode(&operMode))
				{
					DEMOD_ERROR("Fail, DEMOD_M23_Get_OperMode()\n");
					return RET_ERROR;
				}
				DEMOD_PRINT("LX_DEMOD_SYNC_CHECKING : operMode = 0x%x\n", operMode);

				if(LX_DEMOD_DVBT == operMode)
				{
					pDemodInfo->operMode 			= LX_DEMOD_DVBT;
					pDemodInfo->setCfgParam.dvbt.tuneMode 	= pDemodInfo->setCfgParam.dvbt2.tuneMode;
					pDemodInfo->setCfgParam.dvbt.channelBW 	= pDemodInfo->setCfgParam.dvbt2.channelBW;
					pDemodInfo->setCfgParam.dvbt.bSetHp 	= 1;

					if(RET_OK != DEMOD_M23_DVBT_Set_PartialConfig(&(pDemodInfo->setCfgParam.dvbt)))
					{
						DEMOD_ERROR("Fail, DEMOD_M23_DVBT_Set_PartialConfig()\n");
						return RET_ERROR;
					}
					DEMOD_PRINT("LX_DEMOD_SYNC_CHECKING(DVBT2) : Going to LX_DEMOD_SYNC_CHECKING(DVBT forcely)..... ^0^\n");
					return RET_OK;
				}

				if(RET_OK != DEMOD_M23_Get_Lock(LX_DEMOD_L1_DONE, &lockState))
				{
					DEMOD_ERROR("Fail, DEMOD_M23_DVBT_Set_PartialConfig()\n");
					return RET_ERROR;
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					pDemodInfo->controlState		= LX_DEMOD_SIGNAL_STABLE;
					sigStablestartTime 			= jiffies_to_msecs(jiffies);
					DEMOD_PRINT("LX_DEMOD_SYNC_CHECKING : Going to LX_DEMOD_SIGNAL_STABLE..... ^0^\n");
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
				SINT32			freqOffset;

				if(RET_OK != DEMOD_M23_Get_Lock(LX_DEMOD_FEC_DEC_EN, &lockState))
				{
					DEMOD_ERROR("Fail, DEMOD_M23_Get_Lock()\n");
					return RET_ERROR;
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					pDemodInfo->lockStatus			= LX_DEMOD_LOCKED;
					pDemodInfo->signalStatus.bSignalValid 	= TRUE;
					pDemodInfo->bNotifiedLock		= TRUE;
					pDemodInfo->bNotifiedUnlock		= FALSE;
					elapsedTime 				= jiffies_to_msecs(jiffies) - g_RetuneStartTime;

					DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : MSG_DVBT_FRONT_END_LOCKED..... ^^^0^^^\n");
					DEMOD_NOTI("LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^^^0^^^\n", elapsedTime);

					if (RET_OK != DEMOD_M23_Get_CarrierFreqOffset(&freqOffset))
					{
						DEMOD_ERROR("Fail, DEMOD_M23_Get_CarrierFreqOffset()\n");
						return RET_ERROR;
					}
					pDemodInfo->freqOffset 			= freqOffset;
					pDemodInfo->controlState		= LX_DEMOD_SIGNAL_LOCKED;

					DEMOD_PRINT("LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^^^0^^^\n", freqOffset);

					if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
					{
						DEMOD_ERROR("Fail, DEMOD_Get_TunedCFG()\n");
						return RET_ERROR;
					}

					if (RET_OK != _DEMOD_M23_DVB_CheckSignalState(pDemodInfo))
					{
						DEMOD_ERROR("Fail, _DEMOD_M23_DVB_CheckSignalState()\n");
						return RET_ERROR;
					}


				}
				else
				{
#if 0
					pDemodInfo->controlState	= LX_DEMOD_SYNC_CHECKING;
					DEMOD_PRINT( "^R^[DEMOD ] LX_DEMOD_SIGNAL_STABLE : Going back to LX_DEMOD_SYNC_CHECKING..... **;\n");
#endif
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
 * DEMOD_M23_DVBT2_Monitoring_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_M23_DVBT2_Monitoring_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{

	LX_DEMOD_LOCK_STATE_T	lockState;
	LX_DEMOD_OPER_MODE_T 	operMode;

	if(RET_OK != DEMOD_M23_Get_OperMode(&operMode))
	{
		DEMOD_ERROR("Fail, DEMOD_M23_Get_OperMode()\n");
		return RET_ERROR;
	}

	if((operMode == LX_DEMOD_DVBT))
	{
		pDemodInfo->operMode 			= LX_DEMOD_DVBT;
		pDemodInfo->setCfgParam.dvbt.tuneMode 	= pDemodInfo->setCfgParam.dvbt2.tuneMode;
		pDemodInfo->setCfgParam.dvbt.channelBW 	= pDemodInfo->setCfgParam.dvbt2.channelBW;
		pDemodInfo->setCfgParam.dvbt.bSetHp 	= 1;

		if(RET_OK != DEMOD_M23_DVBT_Set_PartialConfig(&(pDemodInfo->setCfgParam.dvbt)))
		{
			DEMOD_ERROR("Fail, DEMOD_M23_DVBT_Set_PartialConfig()\n");
			return RET_ERROR;
		}

		DEMOD_PRINT("Fail, forcely changed to DVBT mode\n");
		DEMOD_PRINT("tuneMode (DVBT)  = %d\n", pDemodInfo->setCfgParam.dvbt.tuneMode);

		return RET_OK;
	}

	if(RET_OK != DEMOD_M23_Get_Lock(LX_DEMOD_FEC_DEC_EN, &lockState))
	{
		DEMOD_ERROR("Fail, DEMOD_M23_Get_Lock()\n");
		return RET_ERROR;
	}
#if 0
	DEMOD_PRINT( " pDemodInfo->lockStatus = %d, pDemodInfo->bNotifiedLock = %d, (lockCount = %d)\n",pDemodInfo->lockStatus,pDemodInfo->bNotifiedLock,pDemodInfo->lockCount);
	DEMOD_PRINT( " pDemodInfo->lockStatus = %d, pDemodInfo->bNotifiedUnlock = %d,(unlockCnt = %d)\n",pDemodInfo->lockStatus,pDemodInfo->bNotifiedUnlock,pDemodInfo->unLockCount);
	DEMOD_PRINT( " lockState = %d)\n",lockState);
#endif
	if(LX_DEMOD_LOCKED == lockState)
	{
		pDemodInfo->unLockCount = 0;

		if (RET_OK != _DEMOD_M23_DVB_CheckSignalState(pDemodInfo))
		{
			DEMOD_ERROR("Fail, _DEMOD_M23_DVB_CheckSignalState()\n");
			return RET_ERROR;
		}

		DEMOD_PRINT("pDemodInfo->signalStatus.packetError = %d\n",pDemodInfo->signalStatus.packetError);
		DEMOD_PRINT("_DVB_Full_Pkerr_Threshold = %d\n", _DVB_Full_Pkerr_Threshold);

		if(pDemodInfo->signalStatus.packetError >= _DVB_Full_Pkerr_Threshold)
		{
			_DVB_Full_Pkerr_Count++;
			DEMOD_PRINT("_DVB_Full_Pkerr_Count = %d\n",_DVB_Full_Pkerr_Count);

			if(_DVB_Full_Pkerr_Count == _DVBT2_Full_Pkerr_Count_Threshold)
			{
				DEMOD_WARN("Oops !! Force to NOT LOCK by Full Packet error Count !!\n");
				_DVB_Full_Pkerr_Count = 0;

				if(RET_OK != DEMOD_M23_SoftwareReset())
				{
					DEMOD_ERROR("Fail, DEMOD_M23_SoftwareReset()\n");
					return RET_ERROR;
				}
				DEMOD_PRINT("Success, DEMOD_M23_SoftwareReset()\n");

				pDemodInfo->lockStatus			= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedUnlock 		= TRUE;
				pDemodInfo->bNotifiedLock		= FALSE;
				pDemodInfo->signalStatus.bSignalValid 	= FALSE;
				DEMOD_NOTI("MSG_DVBT_FRONT_END_NOT_LOCKED..... -_-;;\n");
			}
		}
		else
		{
			if(RET_OK != DEMOD_M23_Get_OperMode(&operMode))
			{
				DEMOD_ERROR("Fail, DEMOD_M23_Get_OperMode()\n");
				return RET_ERROR;
			}

			if((operMode == LX_DEMOD_DVBT))
			{
				pDemodInfo->operMode 			= LX_DEMOD_DVBT;
				pDemodInfo->setCfgParam.dvbt.tuneMode 	= pDemodInfo->setCfgParam.dvbt2.tuneMode;
				pDemodInfo->setCfgParam.dvbt.channelBW 	= pDemodInfo->setCfgParam.dvbt2.channelBW;
				pDemodInfo->setCfgParam.dvbt.bSetHp 	= 1;
				_DVB_Full_Pkerr_Count 	= 0;

				DEMOD_PRINT("Fail, forcely changed to DVBT mode\n");
				DEMOD_PRINT("tuneMode (DVBT2)  = %d\n", pDemodInfo->setCfgParam.dvbt.tuneMode);

				return RET_OK;
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
				pDemodInfo->signalStatus.bSignalValid		= TRUE;
				pDemodInfo->lockCount				= 0;

				DEMOD_NOTI("MSG_DVBT_FRONT_END_LOCKED by LockCount\n");

				if(pauseTimeDemod != LX_DEMOD_LOCKED_PAUSE_TIME )
				{
					pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;
				}
			}

			if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
			{
				DEMOD_ERROR("Fail, DEMOD_Get_TunedCFG()\n");
				return RET_ERROR;
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

			if(pDemodInfo->unLockCount == _DVBT2_Unlock_Count_Threshold)
			{
				pDemodInfo->lockStatus 					= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedUnlock 			= TRUE;
				pDemodInfo->bNotifiedLock				= FALSE;
				pDemodInfo->signalStatus.bSignalValid 	= FALSE;
				_DVB_Full_Pkerr_Count 					= 0;
				pDemodInfo->unLockCount 				= 0;

				DEMOD_NOTI("MSG_DVBT_FRONT_END_NOT_LOCKED by unLockCount..... -_-\n");
			}
		}
	}
	return RET_OK;
}

