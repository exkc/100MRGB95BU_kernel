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
#include <linux/delay.h>

#include <linux/timer.h>


#include "demod_impl.h"
//#include "demod_reg_E60.h"
#include "demod_common_e60.h"
#include "demod_dvb_e60.h"

/***********************************************************************************
	Global Type Definitions
 ************************************************************************************/

UINT16 		gE60GBB_FullDefaultPkerrCount		= 9;// orignal value is 9
UINT16 		gE60GBB_FullDVBT2PkerrCount		= 12;// orignal value is 9
UINT16 		gE60GBB_FullDVBPkerrThreshold		= DVB_FULL_PACKET_ERROR;

extern 	UINT8 	gE60GBB_PowerOnInit;
unsigned int 	gE60GBB_PowerOnInitStartTimeDVB	= 0;

/***********************************************************************************
	Static Variable & Function Prototypes Declarations
 ************************************************************************************/
static	UINT16	gE60GBB_DVB_UnlockCount_full_packeterr	= 0;

int _DEMOD_E60_DVBC_CheckTuneMode (DEMOD_CTX_T *pDemodInfo)
{
	UINT8  new_tuneMode;

	switch (pDemodInfo->setCfgParam.dvbc.tuneMode)
	{
		case	LX_DEMOD_TUNE_NORMAL:			new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_NORMAL; break;
		case	LX_DEMOD_TUNE_AUTO: 			new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_AUTO; break;
		case	LX_DEMOD_TUNE_MANUAL: 			new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_MANUAL ; break;
		case	LX_DEMOD_TUNE_SPEC_DVBC_FIXED_DATA:	new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_FIXED_DATA; break;

		default:					new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_AUTO; break;
	}

	return new_tuneMode;
}

int _DEMOD_E60_DVBT_CheckTuneMode (DEMOD_CTX_T *pDemodInfo)
{
	UINT8  new_tuneMode;

	switch (pDemodInfo->setCfgParam.dvbt.tuneMode)
	{
		case	LX_DEMOD_TUNE_NORMAL:			new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_NORMAL; break;
		case	LX_DEMOD_TUNE_AUTO: 			new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_AUTO; break;
		case	LX_DEMOD_TUNE_MANUAL: 			new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_MANUAL ; break;
		case	LX_DEMOD_TUNE_SPEC_DVBC_FIXED_DATA:	new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_FIXED_DATA; break;

		default:					new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_AUTO; break;
	}
	return new_tuneMode;
}

int _DEMOD_E60_DVBT2_CheckTuneMode (DEMOD_CTX_T *pDemodInfo)
{
	UINT8  new_tuneMode;

	switch (pDemodInfo->setCfgParam.dvbt2.tuneMode)
	{
		case	LX_DEMOD_TUNE_NORMAL:			new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_NORMAL; break;
		case	LX_DEMOD_TUNE_AUTO: 			new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_AUTO; break;
		case	LX_DEMOD_TUNE_MANUAL: 			new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_MANUAL ; break;
		case	LX_DEMOD_TUNE_SPEC_DVBC_FIXED_DATA:	new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_FIXED_DATA; break;

		default:					new_tuneMode = DEMOD_DD_MODE_PROP_TUNEMODE_AUTO; break;
	}
	return new_tuneMode;
}

int _DEMOD_E60_LGDBB_DVBC_SetDemod (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_L2_Context *	pFrontend;

	UINT8  			dvbt_hpSel;
	UINT8  			dvb_c_constellation;
	UINT8  			new_tuneMode;

	UINT32 			freq_Khz = 0;
	UINT16 			dvb_c_bandwidth_Khz = 0;
	UINT16 			symbol_rate_Kbps = 0;

	pFrontend 		= DEMOD_E60_GetContext();

	dvbt_hpSel 		= DEMOD_DD_DVBT_HIERARCHY_PROP_HIERHPSEL_HIGH;
	new_tuneMode 		= _DEMOD_E60_DVBC_CheckTuneMode(pDemodInfo);
	symbol_rate_Kbps 	= pDemodInfo->setCfgParam.dvbc.symbolRate;// KSym/s

	if(RET_OK != DEMOD_E60_Get_BW(pDemodInfo, &dvb_c_bandwidth_Khz))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_BW() \n");
		DEMOD_RETURN_FAIL(__F__);
	}
	 DEMOD_PRINT("[DEMOD_CHIP] SetDemod DVBC check bandwidth_KHz[%d] \n", dvb_c_bandwidth_Khz);

	if (pDemodInfo->setCfgParam.dvbc.tuneMode == LX_DEMOD_TUNE_AUTO_FULL)
	{
		DEMOD_PRINT("[DEMOD_CHIP] tuneMode is LX_DEMOD_TUNE_AUTO_FULL \n");
		pFrontend->cable_blind_scan = TRUE;
	}
	else
	{
		pFrontend->cable_blind_scan = FALSE;
	}

	switch (pDemodInfo->setCfgParam.dvbc.qamMode)
	{

		case LX_DEMOD_16QAM:
			dvb_c_constellation = DEMOD_DD_CONSTELATION_PROP_16QAM;
			break;

		case LX_DEMOD_32QAM:
			dvb_c_constellation = DEMOD_DD_CONSTELATION_PROP_32QAM;
			break;

		case LX_DEMOD_64QAM:
			dvb_c_constellation = DEMOD_DD_CONSTELATION_PROP_64QAM;
			break;

		case LX_DEMOD_128QAM:
			dvb_c_constellation = DEMOD_DD_CONSTELATION_PROP_128QAM;
			break;

		case LX_DEMOD_256QAM:
			dvb_c_constellation = DEMOD_DD_CONSTELATION_PROP_256QAM;
			break;

		default:
			dvb_c_constellation = DEMOD_DD_CONSTELATION_PROP_AUTO;
			break;
	}

	DEMOD_L2_DVB_Set_demod(	pFrontend,
				DEMOD_DD_MODE_PROP_MODULATION_DVBC,
				freq_Khz,
				new_tuneMode,
				DEMOD_DD_MODE_PROP_SPECINV_MANUAL,
				DEMOD_DD_MODE_PROP_SPECINV_NORMAL,
				dvb_c_bandwidth_Khz,
				dvbt_hpSel,
				symbol_rate_Kbps,
				dvb_c_constellation,
				0,
				DEMOD_DD_DVBT2_MODE_PROP_LOCK_MODE_BASE_ONLY); // T2-Base
	return RET_OK;

}

int _DEMOD_E60_LGDBB_DVBT_SetDemod (DEMOD_CTX_T *pDemodInfo)
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

	pFrontend 		= DEMOD_E60_GetContext();

	standard 		= DEMOD_DD_MODE_PROP_MODULATION_DVBT;
	dvbt_hpSel		= DEMOD_DD_DVBT_HIERARCHY_PROP_HIERHPSEL_HIGH;
	dvb_t_constellation	= DEMOD_DD_CONSTELATION_PROP_AUTO;
	dvbt2_PLPId		= 255;

	new_tuneMode		= _DEMOD_E60_DVBT_CheckTuneMode(pDemodInfo);

	DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] Start\n");

	if(RET_OK != DEMOD_E60_Get_BW(pDemodInfo, &dvb_t_bandwidth_Khz))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_BW()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
	 DEMOD_PRINT("[DEMOD_CHIP] SetDemod DVBT check dvb_t_bandwidth_Khz[%d] \n", dvb_t_bandwidth_Khz);

	dvbt_hpSel = (pDemodInfo->setCfgParam.dvbt.bSetHp) ? DEMOD_DD_DVBT_HIERARCHY_PROP_HIERHPSEL_HIGH : DEMOD_DD_DVBT_HIERARCHY_PROP_HIERHPSEL_LOW;

	DEMOD_L2_DVB_Set_demod( pFrontend,
				standard,
				freq_Khz,
				new_tuneMode,
				DEMOD_DD_MODE_PROP_SPECINV_AUTO,
				DEMOD_DD_MODE_PROP_SPECINV_NORMAL,
				dvb_t_bandwidth_Khz,
				dvbt_hpSel,
				symbol_rate_Kbps,
				dvb_t_constellation,
				dvbt2_PLPId,
				DEMOD_DD_DVBT2_MODE_PROP_LOCK_MODE_BASE_ONLY); // T2-Base
	return RET_OK;

}

int _DEMOD_E60_LGDBB_DVBT2_SetDemod (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_L2_Context *	pFrontend;

	UINT8  			standard;
	UINT8  			dvbt2_constellation;
	UINT8  			new_tuneMode;
	UINT16			dvbt2_PLPId;

	UINT32 			freq_Khz = 0;
	UINT16 			dvbt2_bandwidth_Khz = 0;
	UINT16 			symbol_rate_Kbps = 0;

	pFrontend 		= DEMOD_E60_GetContext();

	standard 		= DEMOD_DD_MODE_PROP_MODULATION_DVBT2;

	dvbt2_constellation	= DEMOD_DD_CONSTELATION_PROP_AUTO;
	dvbt2_PLPId		= pDemodInfo->setCfgParam.dvbt2.unPLP;

	new_tuneMode		= _DEMOD_E60_DVBT2_CheckTuneMode(pDemodInfo);

	DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] Start\n");

	if(RET_OK != DEMOD_E60_Get_BW(pDemodInfo, &dvbt2_bandwidth_Khz))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_BW() \n");
		DEMOD_RETURN_FAIL(__F__);
	}
	DEMOD_PRINT("[DEMOD_CHIP] SetDemod DVBT2 check dvbt2_bandwidth_Khz[%d] \n", dvbt2_bandwidth_Khz);
	DEMOD_PRINT("[DEMOD_CHIP] new_tuneMode : 0x%02x \n", new_tuneMode);

	DEMOD_L2_DVB_Set_demod( pFrontend,
				standard,
				freq_Khz,
				new_tuneMode,
				DEMOD_DD_MODE_PROP_SPECINV_AUTO,
				DEMOD_DD_MODE_PROP_SPECINV_NORMAL,
				dvbt2_bandwidth_Khz,
				DEMOD_DD_DVBT_HIERARCHY_PROP_HIERHPSEL_HIGH,
				symbol_rate_Kbps,
				dvbt2_constellation,
				dvbt2_PLPId,
				DEMOD_DD_DVBT2_MODE_PROP_LOCK_MODE_BASE_ONLY); // T2-Base

	DEMOD_PRINT("[DEMOD_CHIP] _DEMOD_E60_LGDBB_DVBT2_SetDemod => PLP ID = 0x%02x \n", dvbt2_PLPId);
	return RET_OK;

}


int _DEMOD_E60_LGDBB_DVB_CheckSignalState (DEMOD_CTX_T *pDemodInfo)
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
	printk("[[E60] packet error : %d]\n"			, signalStatus.packetError);
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

int DEMOD_E60_DVB_SW_Init (void)
{
	LX_DEMOD_L2_Context *	pFrontend;

	DEMOD_NOTI("[DEMOD_CHIP] Start\n");

	pFrontend = DEMOD_E60_GetContext();

	if(lx_chip() == LX_CHIP_E60)
	{
		extern void DEMOD_RegisterMemMap(char* mode);
		DEMOD_RegisterMemMap("dvb");
	}

	//if(DEMOD_L2_DVB_SW_Init(pFrontend, 0x26) != NO_DEMOD_ERROR)   // CPBOX
	if(DEMOD_L2_DVB_SW_Init(pFrontend, 0xb2) != NO_DEMOD_ERROR)     // SOC
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_DVB_SW_Init \n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if(DEMOD_L2_SAT_SW_Init(pFrontend, 0xb2) != NO_DEMOD_ERROR)     // SOC
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SAT_SW_Init \n");
		DEMOD_RETURN_FAIL(__F__);
	}

	DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] SUCCESS, DEMOD_E60_DVB_SW_Init \n");

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBC_AutoSymbolRateDet
 * Enable/Diable automatic symbol rate detection on DVB-C mode.
 *
 * @param  benable - BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBC_AutoSymbolRateDet (LX_DEMOD_SYMRDET_MODE_T symrateMode, UINT16 SymbolRate )
{
	LX_DEMOD_L2_Context *	pFrontend;

	int 			retc = NO_DEMOD_ERROR;

	pFrontend = DEMOD_E60_GetContext();

	switch(symrateMode)
	{
		case LX_DEMOD_SYMR_FIXED_MODE:
			{
				retc = DEMOD_L2_DVBC_Set_SymbolRate_Detect(pFrontend, DEMOD_DD_DVBC_SRD_CMD_AUTO_EN_DISABLE, SymbolRate);
				if(retc != NO_DEMOD_ERROR)
				{
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_DVBC_Set_SymbolRate_Detect() error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
					return retc;
				}
			}
			break;
		case LX_DEMOD_SYMR_FULL_SCAN_MODE:
			{
				retc = DEMOD_L2_DVBC_Set_SymbolRate_Detect(pFrontend, DEMOD_DD_DVBC_SRD_CMD_AUTO_EN_ENABLE, SymbolRate);
				if(retc != NO_DEMOD_ERROR)
				{
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_DVBC_Set_SymbolRate_Detect() error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
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
 * DEMOD_E60_DVBC_IsSymbolRateAuto
 * Enable/Diable automatic symbol rate detection on DVB-C mode.
 *
 * @param  *bAuto - BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBC_IsSymbolRateAuto (BOOLEAN *bAuto)
{
	LX_DEMOD_L2_Context *	pFrontend;

	pFrontend = DEMOD_E60_GetContext();

	if(pFrontend->demod->cmd->dvbc_sym_rate.auto_en == 1)
	{
		*bAuto = TRUE;
	}
	else
	{
		*bAuto = FALSE;
	}

	DEMOD_PRINT("[DEMOD_CHIP] SymbolRateAuto = %s \n", (pFrontend->demod->cmd->dvbc_sym_rate.auto_en == 1)?"Enable":"Disable");

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBC_IsQammodeAutoDet
 * Control automatic setting of DVBC config.
 *
 * @param *bAutoQam 	[IN] BOOLEAN - automatic setting (TRUE) / manual setting(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBC_IsQammodeAutoDet (BOOLEAN *bAutoQam)
{
	LX_DEMOD_L2_Context *	pFrontend;

	pFrontend = DEMOD_E60_GetContext();

	if(pFrontend->demod->prop->dd_constel.constel_autodet == 0)
	{
		*bAutoQam = TRUE;
	}
	else
	{
		*bAutoQam = FALSE;
	}

	DEMOD_PRINT("[DEMOD_CHIP] QammodeAutoDet = %s \n", (pFrontend->demod->prop->dd_constel.constel_autodet == 0)?"Enable":"Disable");
//	*bAutoQam = FALSE;

	return RET_OK;
}
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBC_Set_DefaultRegisterValue
 * Set defualt register value on DVB-T.
 * This function is applied only to A0 version, not to A1 version.
 * @param none
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBC_Set_DefaultRegisterValue (void)
{
	gE60GBB_DVB_UnlockCount_full_packeterr = 0;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBC_Set_Config_auto
 * Control automatic setting of DVBC config.
 *
 * @param bAutoDetect 	[IN] BOOLEAN - automatic setting (TRUE) / manual setting(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBC_Set_Config_auto (BOOLEAN bAutoDetect)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBC_Set_QamMode
 * Set DVBC config parameters manually.
 *
 * @param SymbolRate 	[IN] UINT16 - symbol rate : unit: KHz.
 * @param constel 		[IN] UINT8 - QAM mode : 16QAM(0), 32QAM(1), 64QAM(2), 128QAM(3), 256QAM(4).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBC_Set_QamMode (LX_DEMOD_RF_MODE_T constel)
{
	LX_DEMOD_L2_Context *	pFrontend;

	UINT8  			dvb_c_constellation = DEMOD_DD_CONSTELATION_PROP_AUTO;
	int 			retc = RET_OK;

	pFrontend = DEMOD_E60_GetContext();

	switch (constel)
	{
		case LX_DEMOD_16QAM:
			dvb_c_constellation = DEMOD_DD_CONSTELATION_PROP_16QAM;
			break;

		case LX_DEMOD_32QAM:
			dvb_c_constellation = DEMOD_DD_CONSTELATION_PROP_32QAM;
			break;

		case LX_DEMOD_64QAM:
			dvb_c_constellation = DEMOD_DD_CONSTELATION_PROP_64QAM;
			break;

		case LX_DEMOD_128QAM:
			dvb_c_constellation = DEMOD_DD_CONSTELATION_PROP_128QAM;
			break;

		case LX_DEMOD_256QAM:
			dvb_c_constellation = DEMOD_DD_CONSTELATION_PROP_256QAM;
			break;

		default:
			dvb_c_constellation = DEMOD_DD_CONSTELATION_PROP_AUTO;
			break;
	}

	pFrontend->demod->prop->dd_constel.constellation	= dvb_c_constellation;
	pFrontend->demod->prop->dd_constel.constel_autodet	= DEMOD_DD_CONSTELATION_PROP_AUTO_DET_ENABLE;

	retc = DEMOD_L1_Set_Property(pFrontend->demod, DEMOD_DD_CONSTEL_PROP_CODE);

	if(retc != NO_DEMOD_ERROR)
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L1_Set_Property() error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
		return retc;
	}
	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBC_Set_NeverLockWaitTime
 * Set neverlock waiting period.
 *
 * @param waitMs 	[IN] UINT32 - unit: ms
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBC_Set_NeverLockWaitTime (UINT32 waitMs)
{
	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBC_Get_SymbolRateDetect
 * Get symbol rate in KHz (Don't use this function until revision A1)
 *
 * @param *pSymbolRate 	[OUT] UINT16 - symbol rate : unit: KHz.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBC_Get_SymbolRateDetect (UINT16 *pSymbolRate)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS 	signalStatus;

	pFrontend = DEMOD_E60_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		DEMOD_RETURN_FAIL(__F__);
	}

	*pSymbolRate = signalStatus.sym_rate ;
	DEMOD_PRINT("[DEMOD_CHIP] sym_rate: %d \n", *pSymbolRate);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBC_Get_SymbolRateStatus
 * Get symbol rate detection state on DVB-C
 *
 * @param *pSymbolRateDet 	[OUT] SYMBOLRATE_STATE_T - status and detected symbol rate .
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBC_Get_SymbolRateStatus (LX_DEMOD_SYMBOLRATE_STATE_T *pSymbolRateDet)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS 	signalStatus;

	pFrontend = DEMOD_E60_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		DEMOD_RETURN_FAIL(__F__);
	}

	pSymbolRateDet->status 		= LX_DEMOD_DETECTED;
	pSymbolRateDet->symbolRate 	= signalStatus.sym_rate ;
	DEMOD_PRINT("[DEMOD_CHIP] pSymbolRateDetStatus : %s, symbolRate: %d \n", "LX_DEMOD_DETECTED", pSymbolRateDet->symbolRate);

	return RET_OK;

}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBC_Get_QamModeDetectStatus
 * Get QAM mode detection state and detected QAM mode on DVB-C
 *
 * @param *pQamModeDet 	[OUT] SYMBOLRATE_STATE_T - status and detected QAM mode .
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBC_Get_QamModeDetectStatus (LX_DEMOD_QAMMODE_STATE_T *pQamModeDet)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS 	signalStatus;

	LX_DEMOD_LOCK_STATE_T	lockState;
	LX_DEMOD_RF_MODE_T	qam_mode;

	pFrontend = DEMOD_E60_GetContext();

	if(RET_OK != DEMOD_E60_Get_Lock(LX_DEMOD_FEC_LOCK, &lockState))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_Lock() \n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if (lockState != LX_DEMOD_LOCKED)
	{
		return RET_OK;
	}

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		DEMOD_RETURN_FAIL(__F__);
	}

	DEMOD_PRINT("[DEMOD_CHIP] Constellation: %d\n", pFrontend->demod->rsp->dvbc_status.constellation);

	switch (signalStatus.constellation)
	{
		case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16	:
			qam_mode = LX_DEMOD_16QAM;
			break;

		case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM32	:
			qam_mode = LX_DEMOD_32QAM;
			break;

		case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64	:
			qam_mode = LX_DEMOD_64QAM;
			break;

		case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM128  :
			qam_mode = LX_DEMOD_128QAM;
			break;

		case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM256  :
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
 * DEMOD_E60_DVBC_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_E60_DVBC_Obtaining_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS 	signalStatus;

	static LX_DEMOD_FLAG_T 	scanProcessing = LX_DEMOD_FLAG_START;
	static LX_DEMOD_LOCK_STATE_T lockState = LX_DEMOD_UNLOCKED;
	static unsigned int 	sigStablestartTime = 0;

	pFrontend = DEMOD_E60_GetContext();

	switch (pDemodInfo->controlState)
	{
		/***************************************************/
		/***** Configure tuner for desired channel No. *****/
		/***************************************************/
		case LX_DEMOD_TUNE_START:
			{

				if(RET_OK != _DEMOD_E60_LGDBB_DVBC_SetDemod(pDemodInfo))
				{
					DEMOD_PRINT("[DEMOD_CHIP] FAIL, _DEMOD_E60_LGDBB_DVBC_SetDemod() \n");
					DEMOD_RETURN_FAIL(__F__);
				}

				if((LX_DEMOD_TUNE_NORMAL != pDemodInfo->setCfgParam.dvbc.tuneMode) &&
					(LX_DEMOD_TUNE_SPEC_DVBC_FIXED_DATA != pDemodInfo->setCfgParam.dvbc.tuneMode))
				{

					if(RET_OK != DEMOD_E60_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_ON, &scanProcessing, &lockState))
					{
						DEMOD_PRINT("[DEMOD_CHIP] FAIL, DEMOD_E60_NeverlockScan() \n");
						DEMOD_RETURN_FAIL(__F__);
					}
					pDemodInfo->controlState 		= LX_DEMOD_TUNE_SCAN;
					gE60GBB_FullDVBPkerrThreshold 		= DVB_FULL_PACKET_ERROR;
					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_SYNC_CHECKING(AUTO or Manual SCAN) : Going to LX_DEMOD_TUNE_SCAN..... ^0^\n");
				}
				else
				{
					pDemodInfo->scanJobFlag 	  	= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState 		= LX_DEMOD_SIGNAL_STABLE;
					gE60GBB_FullDVBPkerrThreshold 		= DVB_UNCHECK_PACKET_ERROR;

					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_SYNC_CHECKING(NORMAL SCAN) : Going to LX_DEMOD_SIGNAL_STABLE..... ^0^\n");
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
					pDemodInfo->scanJobFlag 		= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState 		= LX_DEMOD_SIGNAL_STABLE;

					DEMOD_PRINT( "[DEMOD_CHIP] Signal is Found \n");
					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_SYNC_CHECKING : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
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

					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] LX_DEMOD_TUNE_SCAN : MSG_DVBC_FRONT_END_NOT_LOCKED by Scan Fail\n") ;
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] LX_DEMOD_TUNE_SCAN : Elapse time is %d msec\n", elapsedTime) ;

					DEMOD_PRINT( "[DEMOD_CHIP] Signal is NOT Found \n");
				}
				else
				{
					pDemodInfo->scanJobFlag 		= LX_DEMOD_FLAG_ING;
//					DEMOD_PRINT( "[DEMOD_CHIP] Detection is on processing\n");
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

				if(RET_OK != DEMOD_E60_Get_Lock(LX_DEMOD_FEC_LOCK, &lockState))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_Lock() \n");
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					pDemodInfo->controlState		= LX_DEMOD_SIGNAL_STABLE;
					sigStablestartTime 			= jiffies_to_msecs(jiffies);

					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_SYNC_CHECKING : Going to LX_DEMOD_SIGNAL_STABLE..... %d [ms] ^0^\n",sigStablestartTime);
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

				if(RET_OK != DEMOD_E60_Get_Lock(LX_DEMOD_FEC_LOCK, &lockState))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_Lock() \n");
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
					{
						DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
						DEMOD_RETURN_FAIL(__F__);
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

						DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE :  MSG_DVBC_FRONT_END_LOCKED_On_Normal_Tunemode\n");
						DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms]\n", elapsedTime);
						DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz]\n", pDemodInfo->freqOffset);
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

						DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : MSG_DVBC_FRONT_END_LOCKED_On_Other_Tunemode\n");
						DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms]\n", elapsedTime);
						DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz]\n", pDemodInfo->freqOffset);
					}

					if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
					{
						DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_Get_TunedCFG() \n");
						DEMOD_RETURN_FAIL(__F__);
					}

					if (RET_OK != _DEMOD_E60_LGDBB_DVB_CheckSignalState(pDemodInfo))
					{
						DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, _DEMOD_E60_LGDBB_DVB_CheckSignalState() \n");
						DEMOD_RETURN_FAIL(__F__);
					}
				}
				else
				{
//					pDemodInfo->controlState	= LX_DEMOD_SIGNAL_STABLE;
//					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : Going back to LX_DEMOD_SIGNAL_STABLE.....\n");
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
 * DEMOD_E60_DVBC_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_E60_DVBC_Monitoring_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{

	LX_DEMOD_LOCK_STATE_T lockState;

	if(RET_OK != DEMOD_E60_Get_Lock(LX_DEMOD_FEC_LOCK, &lockState))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_Lock() \n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if(LX_DEMOD_LOCKED == lockState)
	{
		pDemodInfo->unLockCount = 0;

		if (RET_OK != _DEMOD_E60_LGDBB_DVB_CheckSignalState(pDemodInfo))
		{
			DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, _DEMOD_E60_LGDBB_DVB_CheckSignalState() \n");
			DEMOD_RETURN_FAIL(__F__);
		}

		if(pDemodInfo->signalStatus.packetError >= gE60GBB_FullDVBPkerrThreshold)
		{
			gE60GBB_DVB_UnlockCount_full_packeterr++;
			DEMOD_PRINT( "[DEMOD_CHIP] gE60GBB_DVB_UnlockCount_full_packeterr = %d\n",gE60GBB_DVB_UnlockCount_full_packeterr);

			if(gE60GBB_DVB_UnlockCount_full_packeterr == gE60GBB_FullDefaultPkerrCount)
			{
				DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] Oops !! Force to NOT LOCK by Full Packet error Count !!\n");
				gE60GBB_DVB_UnlockCount_full_packeterr = 0;

				if(RET_OK != DEMOD_E60_SoftwareReset())
				{
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_SoftwareReset() \n");
					DEMOD_RETURN_FAIL(__F__);
				}

				DEMOD_PRINT("[DEMOD_CHIP] SUCCESS, DEMOD_E60_SoftwareReset() \n");

				pDemodInfo->lockStatus				= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedUnlock 			= TRUE;
				pDemodInfo->bNotifiedLock			= FALSE;
				pDemodInfo->signalStatus.bSignalValid		= FALSE;
				DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] MSG_DVBC_FRONT_END_NOT_LOCKED by Full packet error ..... -_-;;\n");
			}
		}
		else
		{
			gE60GBB_DVB_UnlockCount_full_packeterr = 0;

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

				DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] MSG_DVBC_FRONT_END_LOCKED by Lock Count\n");

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
				pDemodInfo->lockStatus 				= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedUnlock 			= TRUE;
				pDemodInfo->bNotifiedLock			= FALSE;
				pDemodInfo->signalStatus.bSignalValid 		= FALSE;
				gE60GBB_DVB_UnlockCount_full_packeterr 		= 0;
				pDemodInfo->unLockCount 			= 0;

				DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] MSG_DVBC_FRONT_END_NOT_LOCKED by unLockCount..... -_-\n");
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
 * DEMOD_E60_DVBC_Get_DvbInfo
 * Get all information on DVB-C for debug
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBC_Get_DvbInfo (void)
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

	pFrontend = DEMOD_E60_GetContext();

	DEMOD_PRINT("[DEMOD_CHIP] Start \n");

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		return RET_ERROR;
	}

	DEMOD_PRINT("[DEMOD_CHIP] IF AGC Gain = 0x%x \n", signalStatus.if_agc);

 	//NeverLock status
	if (RET_OK != DEMOD_E60_Get_NeverLockStatus(LX_DEMOD_DVBC, &lockState))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_NeverLockStatus() \n");
		return RET_ERROR;
	}

	switch(lockState)
	{
		case LX_DEMOD_DETECTION_PROCESSING :
			DEMOD_PRINT("[DEMOD_CHIP] Signal Checking process \n");
			break;

		case LX_DEMOD_DETECTED :
			DEMOD_PRINT("[DEMOD_CHIP] normal State (available channel) \n");
			break;

		case LX_DEMOD_DETECTION_FAIL :
			DEMOD_PRINT("[DEMOD_CHIP] neverlock state (empty channel) \n");
			break;

		default :
			DEMOD_PRINT("[DEMOD_CHIP] INVALID neverLockStatus \n");
			break;
	}

	// Carrier LOCK status  and offset monitoring

	if (RET_OK != DEMOD_E60_Get_Lock(LX_DEMOD_CARR_LOCK, &lockState) )
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_Lock() \n");
		return RET_ERROR;
	}

	if(lockState == LX_DEMOD_LOCKED)
	{
		DEMOD_PRINT("[DEMOD_CHIP] DVB CARRIER is LOCKED \n");
	}
	else
	{
		DEMOD_PRINT("[DEMOD_CHIP] DVB CARRIER is NOT LOCKED \n");
	}

	// Sampling frequency LOCK status and offset monitoring
	if (RET_OK != DEMOD_E60_Get_Lock( LX_DEMOD_TR_LOCK, &lockState))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_Lock() \n");
		return RET_ERROR;
	}

	if(lockState == LX_DEMOD_LOCKED)
	{
		DEMOD_PRINT("[DEMOD_CHIP] Sampling frequency is Locked \n");
	}
	else
	{
		DEMOD_PRINT("[DEMOD_CHIP] Sampling frequency is NOT Locked \n");
	}

	//Symbol rate detection
	if (RET_OK != DEMOD_E60_DVBC_IsSymbolRateAuto(&isAutoSymbol))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_DVBC_IsSymbolRateAuto() \n");
		return RET_ERROR;
	}

	if(TRUE == isAutoSymbol)
	{
		symbolRateDet.status 		= LX_DEMOD_DETECTED;
		symbolRateDet.symbolRate 	= signalStatus.sym_rate ;

		DEMOD_PRINT("[DEMOD_CHIP] Symbol rate  is detected\n");
		DEMOD_PRINT("[DEMOD_CHIP] Symbol rate = %d [KHz]\n",symbolRateDet.symbolRate);
	}


	// QAM mode detect status and mode monitoring
	if (RET_OK != DEMOD_E60_DVBC_IsQammodeAutoDet(&isAutoQammode))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_DVBC_IsQammodeAutoDet() \n");
		return RET_ERROR;
	}

	if(TRUE == isAutoQammode)
	{
		if (RET_OK != DEMOD_E60_DVBC_Get_QamModeDetectStatus(&qamModeDet))
		{
			DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_DVBC_Get_QamModeDetectStatus() \n");
			return RET_ERROR;
		}

		switch(qamModeDet.status)
		{
			case LX_DEMOD_IDLE :
			{
				DEMOD_PRINT("[DEMOD_CHIP] QAM mode detect is idle status \n");
				break;
			}
			case LX_DEMOD_DETECTED :
			{
				DEMOD_PRINT("[DEMOD_CHIP] QAM mode is detected \n");
				DEMOD_PRINT("[DEMOD_CHIP] QAM mode is %s \n",
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
				DEMOD_PRINT("[DEMOD_CHIP] QAM mode detection is processing \n");
				break;
			}
			case LX_DEMOD_DETECTION_FAIL :
			{
				DEMOD_PRINT("[DEMOD_CHIP] QAM mode detection is failed \n");
				break;
			}
			case LX_DEMOD_DETECTION_MANUAL :
			{
				DEMOD_PRINT("[DEMOD_CHIP] Manual QAM mode detection mode \n");
				break;
			}
			default :
			{
				DEMOD_PRINT("[DEMOD_CHIP] INVALID QAM mode detection \n");
				break;
			}
		}
	}

 	//spectrum inversion status
	if (RET_OK !=  DEMOD_E60_Get_SpectrumStatus(&spectrumAuto, &lockState))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_SpectrumStatus() \n");
		lockState = LX_DEMOD_UNKOWN_STATE;
	}

	if(lockState == LX_DEMOD_INVERSION)
	{
		DEMOD_PRINT("[DEMOD_CHIP] Spectrum Inversion \n");
	}
	else
	{
		DEMOD_PRINT("[DEMOD_CHIP] Spectrum Normal \n");
	}

	//Frame lock status
	if (RET_OK != DEMOD_E60_Get_Lock(LX_DEMOD_FEC_LOCK, &lockState) )
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_Lock() \n");
		return RET_ERROR;
	}

	if(lockState != LX_DEMOD_LOCKED)
	{
		DEMOD_PRINT("[DEMOD_CHIP] DVB FEC IS NOT LOCKED  \n");
	}
	else
	{
		DEMOD_PRINT("[DEMOD_CHIP] DVB FEC LOCK OK  \n");
	}

	sigMse.bMse 		= 0;
	sigMse.mse 		= signalStatus.mse_info;
	sigMse.constPwr		= signalStatus.constPwr;

	DEMOD_PRINT("[DEMOD_CHIP] mse = %d, constPwr = %d  \n",sigMse.mse, sigMse.constPwr);
	DEMOD_PRINT("[DEMOD_CHIP] vBER = %d  \n",signalStatus.ber);
	DEMOD_PRINT("[DEMOD_CHIP] TP Error Count= %d  \n",signalStatus.packetError);

	return RET_OK;
}

#if 0
#endif

/**
 * DEMOD_E60_DVBT_Set_DefaultRegisterValue
 * Set defualt register value on DVB-T.
 * This function is applied only to A0 version, not to A1 version.
 *
 * @param none
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT_Set_DefaultRegisterValue (LX_DEMOD_BWMODE_T band)
{
	gE60GBB_DVB_UnlockCount_full_packeterr 	= 0;

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBT_Set_Config_auto
 * Control automatic setting of DVB-T config.
 *
 * @param bAutoDetect 	[IN] BOOLEAN - automatic setting (TRUE) / manual setting(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT_Set_Config_auto (BOOLEAN bAutoDetect)
{
	DEMOD_INFO("deprecated\n");
/*
	LX_DEMOD_L2_Context *	pFrontend;

	pFrontend = DEMOD_E60_GetContext();

	DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] Set to %s \n", (bAutoDetect == TRUE)?"AUTO":"MANUAL");

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
 * DEMOD_E60_DVBT_Set_PartialConfig
 * Set hierachical signal path and bandwidth.
 * This function is used when LX_DEMOD_E60_DVBT_Set_Config_auto is enabled.
 *
 * @param *pDvbtConfigParam 	[IN] LX_DEMOD_DVBT_CONFIG_T - DVB-T config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT_Set_PartialConfig (LX_DEMOD_DVBT_CONFIG_T *pDvbtConfigParam)
{
	LX_DEMOD_L2_Context *	pFrontend;

	pFrontend = DEMOD_E60_GetContext();

	pFrontend->demod->prop->dd_dvbt_hp_sel.hierhpsel  	= pDvbtConfigParam->bSetHp;
	if(DEMOD_L2_Set_Property(pFrontend, DEMOD_DD_DVBT_HIERARCHY_PROP_CODE) != NO_DEMOD_ERROR)
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_Set_Property(DEMOD_DD_DVBT_HIERARCHY_PROP_CODE) \n");
		return RET_ERROR;;
	}

	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBT_Set_FullConfig
 * Set all config parameters on DVB-T.
 * This function is used when LX_DEMOD_E60_DVBT_Set_Config_auto is disabled.
 *
 * @param *pDvbtConfigParam 	[IN] LX_DEMOD_DVBT_CONFIG_T - DVB-T config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT_Set_FullConfig (LX_DEMOD_DVBT_CONFIG_T *pDvbtConfigParam)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBT_Set_NeverLockWaitTime
 * Set neverlock waiting period.
 *
 * @param waitMs 	[IN] UINT32 - unit: ms
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT_Set_NeverLockWaitTime (UINT32 waitMs)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBT_Set_TafcWaitSymbol
 * Set TAFC wait symbol number.
 *
 * @param bDelayed 	[IN] BOOLEAN
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT_Set_TafcWaitSymbol (BOOLEAN bDelayed)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBT_Set_CrGearshEn
 * enable/disable Carrier recovery bandwidth gear shift
 *
 * @param bEnable 	[IN] BOOLEAN
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT_Set_CrGearshEn (BOOLEAN bEnable)
{
	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBT_Get_PreGhostDetection
 * Set Cir Power level and NR level
 *
 * @param *pIsExist 	[IN] BOOLEAN
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT_Get_PreGhostDetection (BOOLEAN *pIsExist)
{
	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBT_Get_DelaySpreadStatus
 * Get delay spread state on DVB-T.
 *
 * @param *pDelaySpread 	[OUT] UINT16.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT_Get_DelaySpreadStatus (UINT16 *pDelaySpread)
{
	return RET_OK;
}



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBT_Get_Hierach_HPSel
 * Get the information if the hierachical HP is selected.
 *
 * @param *pBSetHp 	[OUT] BOOLEAN - HP (TRUE) / LP(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT_Get_Hierach_HPSel (BOOLEAN *pBSetHp)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("[DEMOD_CHIP] Start \n");

	pFrontend = DEMOD_E60_GetContext();

	*pBSetHp = TRUE;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		DEMOD_RETURN_FAIL(__F__);
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
 * DEMOD_E60_DVBT_Get_FFTMode
 * Get the information of bandwidth on DVB-T.
 *
 * @param *pTxModeLock 	[OUT] LX_DEMOD_LOCK_STATE_T - FFT mode lock state.
 * @param *pFftMode 	[OUT] LX_DEMOD_FFTMODE_T - detected FFT mode.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT_Get_FFTMode (LX_DEMOD_LOCK_STATE_T *pTxModeLock, LX_DEMOD_FFTMODE_T *pFftMode)
{

	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("[DEMOD_CHIP] Start \n");

	pFrontend = DEMOD_E60_GetContext();

	*pTxModeLock = LX_DEMOD_LOCKED;
	*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		DEMOD_RETURN_FAIL(__F__);
	}

	switch(signalStatus.fftMode)
	{
		case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_2K :
			*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_2K;
			break;

		case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_4K:
			*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_4K;
			break;

		case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_8K:
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
 * DEMOD_E60_DVBT_Get_GuradIntervalMode
 * Get the information of guard interval on DVB-T.
 *
 * @param *pGIMode 	[OUT] LX_DEMOD_GIMODE_T - 1/32, 1/16, 1/8 and 1/4.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT_Get_GuradIntervalMode (LX_DEMOD_GIMODE_T *pGIMode)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("[DEMOD_CHIP] Start \n");

	pFrontend = DEMOD_E60_GetContext();

	*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_UNKNOWN;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		DEMOD_RETURN_FAIL(__F__);
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
 * DEMOD_E60_DVBT_Get_HierachyMode
 * Get the information of hierachical mode on DVB-T.
 *
 * @param *pHierachMode[OUT] DEMOD_E60_DVB_TPS_HIERACHY_T - alpha = none, 1, 2 and 4.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT_Get_HierachyMode (LX_DEMOD_DVB_TPS_HIERACHY_T *pHierachMode)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("[DEMOD_CHIP] Start \n");

	pFrontend = DEMOD_E60_GetContext();

	*pHierachMode = LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		DEMOD_RETURN_FAIL(__F__);
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
 * DEMOD_E60_DVBT_Get_LpCoderRate
 * Get the information of LP code rate on DVB-T.
 *
 * @param *pLpCodeRate[OUT] LX_DEMOD_CODERATE_T - code rate : 1/2, 2/3, 3/4, 5/6 and 7/8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT_Get_LpCoderRate (LX_DEMOD_CODERATE_T *pLpCodeRate)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("[DEMOD_CHIP] Start \n");

	pFrontend = DEMOD_E60_GetContext();

	*pLpCodeRate = LX_DEMOD_CODE_UNKNOWN;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if(signalStatus.hierarchy_sel == DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_SEL_LP)
	{
		switch(signalStatus.codeRate)
		{
			case DEMOD_DD_DVBT_STATUS_RESPONSE_LP_CR_1_2 :
				*pLpCodeRate = LX_DEMOD_CODE_1_2;
				break;
			case DEMOD_DD_DVBT_STATUS_RESPONSE_LP_CR_2_3:
				*pLpCodeRate = LX_DEMOD_CODE_2_3;
				break;
			case DEMOD_DD_DVBT_STATUS_RESPONSE_LP_CR_3_4 :
				*pLpCodeRate = LX_DEMOD_CODE_3_4;
				break;
			case DEMOD_DD_DVBT_STATUS_RESPONSE_LP_CR_5_6:
				*pLpCodeRate = LX_DEMOD_CODE_5_6;
				break;
			case DEMOD_DD_DVBT_STATUS_RESPONSE_LP_CR_7_8:
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
 * DEMOD_E60_DVBT_Get_HpCoderRate
 * Get the information of HP code rate on DVB-T.
 *
 * @param *pLpCodeRate[OUT] LX_DEMOD_CODERATE_T - code rate : 1/2, 2/3, 3/4, 5/6 and 7/8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT_Get_HpCoderRate (LX_DEMOD_CODERATE_T *pHpCodeRate)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("[DEMOD_CHIP] Start \n");

	pFrontend = DEMOD_E60_GetContext();

	*pHpCodeRate = LX_DEMOD_CODE_UNKNOWN;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if(signalStatus.hierarchy_sel == DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_SEL_HP)
	{
		switch(signalStatus.codeRate)
		{
			case DEMOD_DD_DVBT_STATUS_RESPONSE_HP_CR_HP_1_2 :
				*pHpCodeRate = LX_DEMOD_CODE_1_2;
				break;
			case DEMOD_DD_DVBT_STATUS_RESPONSE_HP_CR_HP_2_3:
				*pHpCodeRate = LX_DEMOD_CODE_2_3;
				break;
			case DEMOD_DD_DVBT_STATUS_RESPONSE_HP_CR_HP_3_4 :
				*pHpCodeRate = LX_DEMOD_CODE_3_4;
				break;
			case DEMOD_DD_DVBT_STATUS_RESPONSE_HP_CR_HP_5_6:
				*pHpCodeRate = LX_DEMOD_CODE_5_6;
				break;
			case DEMOD_DD_DVBT_STATUS_RESPONSE_HP_CR_HP_7_8:
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
 * DEMOD_E60_DVBT_GetCellId
 * Get TPS cell ID on DVB-T.
 *
 * @param *pCellIDLength[OUT] UINT8 - cell ID length.
 * @param *cell_id[OUT] UINT16.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT_Get_CellId (UINT8 *pCellIDLength, UINT16 *cell_id)
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

	*cell_id = signalStatus.cell_id;

	DEMOD_PRINT("[DEMOD_CHIP] Cell ID = 0x%x \n", *cell_id);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBT_Get_TpsInfo
 * Get TPS information on DVB-T
 *
 * @param *pTpsParams [OUT] LX_DEMOD_DVBT_CONFIG_T - TPS data structure.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT_Get_TpsInfo (LX_DEMOD_DVBT_CONFIG_T *pTpsParams)
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


	DEMOD_PRINT("[DEMOD_CHIP] Start \n");

	pFrontend = DEMOD_E60_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if(NULL == pTpsParams)
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] ERROR DEMOD_E60_DVBT_CONFIG_T TpsParams is NULL \n");
		return RET_ERROR;
	}

	if(signalStatus.hierarchy_sel == DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_SEL_HP)
	{
		bSetHp = TRUE;
		DEMOD_PRINT("[DEMOD_CHIP] Set HP selection = %s \n", " HP Mode");
	}
	else
	{
		bSetHp = FALSE;
		DEMOD_PRINT("[DEMOD_CHIP] Set HP selection = %s \n", " LP Mode");
	}

	pTpsParams->bSetHp = bSetHp;

	switch(signalStatus.bandwidth)
	{
		case 0x08:
			channelBW = LX_DEMOD_BW_8MHZ;
			DEMOD_PRINT("[DEMOD_CHIP] Bandwidth = %s \n", "LX_DEMOD_BW_8MHZ" );
			break;

		case 0x07:
			channelBW = LX_DEMOD_BW_7MHZ;
			DEMOD_PRINT("[DEMOD_CHIP] Bandwidth = %s \n", "LX_DEMOD_BW_7MHZ" );
			break;

		case 0x06:
			channelBW = LX_DEMOD_BW_6MHZ;
			DEMOD_PRINT("[DEMOD_CHIP] Bandwidth = %s \n", "LX_DEMOD_BW_6MHZ" );
			break;

		case 0x05:
			channelBW = LX_DEMOD_BW_5MHZ;
			DEMOD_PRINT("[DEMOD_CHIP] Bandwidth = %s \n", "LX_DEMOD_BW_5MHZ" );
			break;

		default:
			channelBW = LX_DEMOD_BW_UNKNOWN;
			DEMOD_PRINT("[DEMOD_CHIP] Bandwidth = %s \n", "LX_DEMOD_BW_UNKNOWN" );
			break;

	}

	pTpsParams->channelBW = channelBW;

	switch(signalStatus.fftMode)
	{
		case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_2K :
			FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_2K;
			DEMOD_PRINT("[DEMOD_CHIP]  FFTMode = %s \n","FFT_2K");
			break;

		case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_4K:
			FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_4K;
			DEMOD_PRINT("[DEMOD_CHIP] FFTMode = %s \n","FFT_4K");
			break;

		case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_8K:
			FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_8K;
			DEMOD_PRINT("[DEMOD_CHIP] FFTMode = %s \n","FFT_8K");
			break;

		default :
			FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN;
			DEMOD_PRINT("[DEMOD_CHIP] FFTMode = %s \n","FFT_UNKNOWN");
			break;
	}

	pTpsParams->FFTMode = FFTMode;

	switch(signalStatus.guardInterval)
	{
		case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_32 :
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_32;
			DEMOD_PRINT("[DEMOD_CHIP] Guard Interval = %s \n", "1_32" );
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_16:
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_16;
			DEMOD_PRINT("[DEMOD_CHIP] Guard Interval = %s \n", "1_16" );
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_8 :
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_8;
			DEMOD_PRINT("[DEMOD_CHIP] Guard Interval = %s \n", "1_8" );
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_4:
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_4;
			DEMOD_PRINT("[DEMOD_CHIP] Guard Interval = %s \n", "1_4" );
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_128:
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_128;
			DEMOD_PRINT("[DEMOD_CHIP] Guard Interval = %s \n", "1_128" );
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_19_128:
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_19_128;
			DEMOD_PRINT("[DEMOD_CHIP] Guard Interval = %s \n", "19_128" );
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_19_256:
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_19_256;
			DEMOD_PRINT("[DEMOD_CHIP] Guard Interval = %s \n", "19_256" );
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_64:
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_64;
			DEMOD_PRINT("[DEMOD_CHIP] Guard Interval = %s \n", "1_62" );
			break;
		default :
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_UNKNOWN;
			DEMOD_PRINT("[DEMOD_CHIP] Guard Interval = %s \n", "UNKNOWN" );
			break;
	}

	pTpsParams->gIMode = gIMode;

	switch(signalStatus.hierarchy)
	{
		case DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_NONE :
			hierachMode = LX_DEMOD_DVB_TPS_HIERACHY_NONE;
			DEMOD_PRINT("[DEMOD_CHIP] Hierachical Mode = %s \n", "NON Hierachical" );
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_ALFA1:
			hierachMode = LX_DEMOD_DVB_TPS_HIERACHY_1;
			DEMOD_PRINT("[DEMOD_CHIP] Hierachical Mode = %s \n", "alpha = 1" );
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_ALFA2 :
			hierachMode = LX_DEMOD_DVB_TPS_HIERACHY_2;
			DEMOD_PRINT("[DEMOD_CHIP] Hierachical Mode = %s \n", "alpha = 2" );
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_ALFA4:
			hierachMode = LX_DEMOD_DVB_TPS_HIERACHY_4;
			DEMOD_PRINT("[DEMOD_CHIP] Hierachical Mode = %s \n", "alpha = 3" );
			break;
		default :
			hierachMode = LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN;
			DEMOD_PRINT("[DEMOD_CHIP] Hierachical Mode = %s \n", "UNKNOWN MODE" );
			break;
	}
	pTpsParams->hierachMode = hierachMode;

	if(signalStatus.hierarchy_sel == DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_SEL_LP)
	{
		switch(signalStatus.codeRate)
		{
			case DEMOD_DD_DVBT_STATUS_RESPONSE_LP_CR_1_2 :
				lpCodeRate = LX_DEMOD_CODE_1_2;
				DEMOD_PRINT("[DEMOD_CHIP] LP code rate = %s \n", "Code_1_2" );
				break;
			case DEMOD_DD_DVBT_STATUS_RESPONSE_LP_CR_2_3:
				lpCodeRate = LX_DEMOD_CODE_2_3;
				DEMOD_PRINT("[DEMOD_CHIP] LP code rate = %s \n", "Code_2_3" );
				break;
			case DEMOD_DD_DVBT_STATUS_RESPONSE_LP_CR_3_4 :
				lpCodeRate = LX_DEMOD_CODE_3_4;
				DEMOD_PRINT("[DEMOD_CHIP] LP code rate = %s \n", "Code_3_4" );
				break;
			case DEMOD_DD_DVBT_STATUS_RESPONSE_LP_CR_5_6:
				lpCodeRate = LX_DEMOD_CODE_5_6;
				DEMOD_PRINT("[DEMOD_CHIP] LP code rate = %s \n", "Code_5_6" );
				break;
			case DEMOD_DD_DVBT_STATUS_RESPONSE_LP_CR_7_8:
				lpCodeRate = LX_DEMOD_CODE_7_8;
				DEMOD_PRINT("[DEMOD_CHIP] LP code rate = %s \n", "Code_7_8" );
				break;
			default :
				lpCodeRate = LX_DEMOD_CODE_UNKNOWN;
				DEMOD_PRINT("[DEMOD_CHIP] LP code rate = %s \n", "Code UNKNOWN" );
				break;
		}
	}
	else
	{
		lpCodeRate = LX_DEMOD_CODE_UNKNOWN;
		DEMOD_PRINT("[DEMOD_CHIP] LP code rate = %s \n", "Code UNKNOWN" );
	}

	pTpsParams->lpCodeRate = lpCodeRate;

	if(signalStatus.hierarchy_sel == DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_SEL_HP)
	{
		switch(signalStatus.codeRate)
		{
			case DEMOD_DD_DVBT_STATUS_RESPONSE_HP_CR_HP_1_2 :
				hpCodeRate = LX_DEMOD_CODE_1_2;
				DEMOD_PRINT("[DEMOD_CHIP] HP code rate = %s \n", "Code_1_2" );
				break;
			case DEMOD_DD_DVBT_STATUS_RESPONSE_HP_CR_HP_2_3:
				hpCodeRate = LX_DEMOD_CODE_2_3;
				DEMOD_PRINT("[DEMOD_CHIP] HP code rate = %s \n", "Code_2_3" );
				break;
			case DEMOD_DD_DVBT_STATUS_RESPONSE_HP_CR_HP_3_4 :
				hpCodeRate = LX_DEMOD_CODE_3_4;
				DEMOD_PRINT("[DEMOD_CHIP] HP code rate = %s \n", "Code_3_4" );
				break;
			case DEMOD_DD_DVBT_STATUS_RESPONSE_HP_CR_HP_5_6:
				hpCodeRate = LX_DEMOD_CODE_5_6;
				DEMOD_PRINT("[DEMOD_CHIP] HP code rate = %s \n", "Code_5_6" );
				break;
			case DEMOD_DD_DVBT_STATUS_RESPONSE_HP_CR_HP_7_8:
				hpCodeRate = LX_DEMOD_CODE_7_8;
				DEMOD_PRINT("[DEMOD_CHIP] HP code rate = %s \n", "Code_7_8" );
				break;
			default :
				hpCodeRate = LX_DEMOD_CODE_UNKNOWN;
				DEMOD_PRINT("[DEMOD_CHIP] HP code rate = %s \n", "Code UNKNOWN" );
				break;
		}
	}
	else
	{
		hpCodeRate = LX_DEMOD_CODE_UNKNOWN;
		DEMOD_PRINT("[DEMOD_CHIP] HP code rate = %s \n", "Code UNKNOWN" );
	}
	pTpsParams->hpCodeRate = hpCodeRate;

	// get QAM mode
	if (RET_OK != DEMOD_E60_Get_QAMMode(&qamMode ))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_QAMMode() \n");
		return RET_ERROR;
	}

	pTpsParams->qamMode = qamMode;
	DEMOD_PRINT("[DEMOD_CHIP] modulation  = %s \n",
		(qamMode == LX_DEMOD_QPSK) ?   "QPSK"  :
		(qamMode == LX_DEMOD_16QAM) ?  "16QAM" :
		(qamMode == LX_DEMOD_64QAM) ?  "64QAM" : " UNKOWN MODE" );

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBT_Get_TotalInfo
 * Get all information on DVB-T for debug
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT_Get_TotalInfo (void)
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

	if (RET_OK != DEMOD_E60_Get_NeverLockStatus(LX_DEMOD_DVBT, &neverLockStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_NeverLockStatus() \n");
		neverLockStatus = LX_DEMOD_UNKOWN_STATE;
	}

	if (RET_OK !=  DEMOD_E60_Get_SpectrumStatus(&spectrumAuto, &spectrumInv))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_SpectrumStatus() \n");
		spectrumInv = LX_DEMOD_UNKOWN_STATE;
	}

	switch(signalStatus.fftMode)
	{
		case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_2K :
			fftMode = LX_DEMOD_DVBT_ISDBT_FFT_2K;
			DEMOD_PRINT("[DEMOD_CHIP] FFTMode = %s \n","FFT_2K");
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_4K:
			fftMode = LX_DEMOD_DVBT_ISDBT_FFT_4K;
			DEMOD_PRINT("[DEMOD_CHIP] FFTMode = %s \n","FFT_4K");
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_8K:
			fftMode = LX_DEMOD_DVBT_ISDBT_FFT_8K;
			DEMOD_PRINT("[DEMOD_CHIP] FFTMode = %s \n","FFT_8K");
			break;
		default :
			fftMode = LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN;
			DEMOD_PRINT("[DEMOD_CHIP] FFTMode = %s \n","UNKNOWN");
			break;
	}

	errorCount = signalStatus.packetError;
	DEMOD_PRINT("[DEMOD_CHIP] TP Error Count= %d \n",errorCount);

	FreqOff 		= signalStatus.offsetFrq_Hz/1000;

	sigMse.bMse 		= 0;
	sigMse.mse 		= signalStatus.mse_info;
	sigMse.constPwr 	= signalStatus.constPwr;
	txModeLock 		= signalStatus.demodLock ;

	DEMOD_PRINT("[DEMOD_CHIP] AGC LOCK is %s \n",(agcLockStatus == LX_DEMOD_LOCKED) ? " Locked" : " NOT Locked");
	DEMOD_PRINT("[DEMOD_CHIP] IF AGC value = %d(0x%x) \n",ifagcValue,ifagcValue);
	DEMOD_PRINT("[DEMOD_CHIP] Neverlock is %s \n",(neverLockStatus == LX_DEMOD_DETECTED) ? " Locked" : " NOT Locked");
	DEMOD_PRINT("[DEMOD_CHIP] Spectrum auto = %s, Inversion  = %s \n",(spectrumAuto == LX_DEMOD_AUTO) ? " Auto" : " Manual",
																					(spectrumInv == LX_DEMOD_INVERSION) ? " Inverted" : " Normal" );
	DEMOD_PRINT("[DEMOD_CHIP] FFT mode LOCK = %s \n",(txModeLock == LX_DEMOD_LOCKED) ? " Locked" : " NOT Locked");
	DEMOD_PRINT("[DEMOD_CHIP] offset = %d [KHz]\n",FreqOff);
	DEMOD_PRINT("[DEMOD_CHIP] mse = %d, constPwr = %d, \n",sigMse.mse, sigMse.constPwr);

	if (RET_OK != DEMOD_E60_DVBT_Get_TpsInfo( &tppsParams))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_DVBT_Get_TpsInfo() \n");
		return RET_ERROR;
	}

	return RET_OK;
}




/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBT_Get_IFO_LOCK
 * Get IFO lock on DVB-T.
 *
 * @param *pSnr [OUT] BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT_Get_IFO_LOCK (BOOLEAN *pIfoLock)
{
	*pIfoLock = FALSE;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBT_EqualizereReset.
 * Reset DVB EQ module by software.
 *
 * @param  NONE
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT_EqualizereReset (void)
{
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBT_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_E60_DVBT_Obtaining_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{
	static LX_DEMOD_FLAG_T 			scanProcessing = LX_DEMOD_FLAG_START;
	static LX_DEMOD_LOCK_STATE_T 	lockState = LX_DEMOD_UNLOCKED;
	static unsigned int 			sigStablestartTime = 0;
	LX_DEMOD_OPER_MODE_T 			operMode;
	unsigned int 					elapsedTime = 0;


	switch (pDemodInfo->controlState)
	{
		/***************************************************/
		/***** Configure tuner for desired channel No. *****/
		/***************************************************/
		case LX_DEMOD_TUNE_START:
			{
				elapsedTime = jiffies_to_msecs(jiffies)  - g_RetuneStartTime;
				DEMOD_PRINT("[DEMOD_CHIP] START_TIME (%d ms) \n", elapsedTime);

				if(RET_OK != _DEMOD_E60_LGDBB_DVBT_SetDemod(pDemodInfo))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, _DEMOD_E60_LGDBB_DVBT_SetDemod() \n");
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_TUNE_NORMAL != pDemodInfo->setCfgParam.dvbt.tuneMode)
				{
					if(RET_OK != DEMOD_E60_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_ON, &scanProcessing, &lockState))
					{
						DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_NeverlockScan() \n");
						DEMOD_RETURN_FAIL(__F__);
					}
					pDemodInfo->controlState 		= LX_DEMOD_TUNE_SCAN;
					gE60GBB_FullDVBPkerrThreshold 		= DVB_FULL_PACKET_ERROR;
					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_TUNE_START(AUTO or Manual SCAN) : Going to LX_DEMOD_TUNE_SCAN..... ^0^\n");
				}
				else
				{
					pDemodInfo->scanJobFlag 		= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState 		= LX_DEMOD_SYNC_CHECKING;
					gE60GBB_FullDVBPkerrThreshold 		= DVB_UNCHECK_PACKET_ERROR;
					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_TUNE_START(NORMAL SCAN) : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
				}
				elapsedTime = jiffies_to_msecs(jiffies) - g_RetuneStartTime;
				DEMOD_PRINT("[DEMOD_CHIP] END_TIME (%d ms) \n", elapsedTime);
			}

			break;
									/***************************************************/
									/***** Configure demod for scan mode. *****/
		case LX_DEMOD_TUNE_SCAN:	/***************************************************/
			{
				if((LX_DEMOD_FLAG_COMPLETE == pDemodInfo->scanJobFlag) || (LX_DEMOD_FLAG_FINISH == pDemodInfo->scanJobFlag))
				{
					pDemodInfo->controlState = LX_DEMOD_SYNC_CHECKING;
					DEMOD_PRINT( "[DEMOD_CHIP] Already Done \n");
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
					pDemodInfo->operMode 			= LX_DEMOD_DVBT;
					pDemodInfo->scanJobFlag 		= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState 		= LX_DEMOD_SYNC_CHECKING;

					DEMOD_PRINT( "[DEMOD_CHIP] Signal is Found \n");
					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_TUNE_SCAN : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
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

					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] LX_DEMOD_TUNE_SCAN : MSG_DVBT_FRONT_END_NOT_LOCKED..\n") ;
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] LX_DEMOD_TUNE_SCAN : Elapse time is %d msec\n", elapsedTime) ;
					DEMOD_PRINT( "[DEMOD_CHIP] Signal is NOT Found \n");
				}
				else
				{
					pDemodInfo->scanJobFlag 		= LX_DEMOD_FLAG_ING;
//					DEMOD_PRINT( "[DEMOD_CHIP] Detection is on processing \n");
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
				if(RET_OK != DEMOD_E60_Get_OperMode(&operMode))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_OperMode() \n");
					DEMOD_RETURN_FAIL(__F__);

				}

				DEMOD_PRINT("[DEMOD ] LX_DEMOD_SYNC_CHECKING() operMode = 0x%x!!!\n", operMode);

				if(LX_DEMOD_DVBT2 == operMode)
				{
					DEMOD_PRINT("[DEMOD_CHIP] Before pDemodInfo->setCfgParam.dvbt2.unPLP = %d \n", pDemodInfo->setCfgParam.dvbt2.unPLP);

					pDemodInfo->operMode 						= LX_DEMOD_DVBT2;
					pDemodInfo->setCfgParam.dvbt2.tuneMode 	= pDemodInfo->setCfgParam.dvbt.tuneMode;
					pDemodInfo->setCfgParam.dvbt2.channelBW	= pDemodInfo->setCfgParam.dvbt.channelBW;

					if(pDemodInfo->setCfgParam.dvbt2.tuneMode != LX_DEMOD_TUNE_NORMAL)			pDemodInfo->setCfgParam.dvbt2.unPLP = 255;
					DEMOD_PRINT("[DEMOD_CHIP] After pDemodInfo->setCfgParam.dvbt2.tuneMode = 0x%x \n", pDemodInfo->setCfgParam.dvbt2.tuneMode);
					DEMOD_PRINT("[DEMOD_CHIP] After pDemodInfo->setCfgParam.dvbt2.unPLP = %d \n", pDemodInfo->setCfgParam.dvbt2.unPLP);

					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_SYNC_CHECKING :Set PLP ID to %d..... \n",pDemodInfo->setCfgParam.dvbt2.unPLP);
					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_SYNC_CHECKING(DVBT) : Going to LX_DEMOD_SYNC_CHECKING(DVBT2 forcely)..... ^0^\n");

					return RET_OK;
				}

				if(RET_OK != DEMOD_E60_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_Lock() \n");
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					pDemodInfo->controlState		= LX_DEMOD_SIGNAL_STABLE;
					sigStablestartTime 			= jiffies_to_msecs(jiffies);

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
		/********************************************/
	   	case LX_DEMOD_SIGNAL_STABLE:
			{
				SINT32			freqOffset;

				if(RET_OK != DEMOD_E60_Get_Lock(LX_DEMOD_PSYNC_LOCK, &lockState))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_Lock() \n");
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					pDemodInfo->lockStatus					= LX_DEMOD_LOCKED;
					pDemodInfo->signalStatus.bSignalValid	= TRUE;
					pDemodInfo->bNotifiedLock				= TRUE;
					pDemodInfo->bNotifiedUnlock				= FALSE;
					elapsedTime 							= jiffies_to_msecs(jiffies) - g_RetuneStartTime;

					DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : MSG_DVBT_FRONT_END_LOCKED..... ^^^0^^^\n");
					DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^^^0^^^\n", elapsedTime);


					if (RET_OK != DEMOD_E60_Get_CarrierFreqOffset(&freqOffset))
					{
						DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_CarrierFreqOffset() \n");
						DEMOD_RETURN_FAIL(__F__);
					}
					pDemodInfo->freqOffset 			= freqOffset;
					pDemodInfo->controlState		= LX_DEMOD_SIGNAL_LOCKED;
					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^^^0^^^\n", freqOffset);

					if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
					{
						DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_Get_TunedCFG() \n");
						DEMOD_RETURN_FAIL(__F__);
					}

					if (RET_OK != _DEMOD_E60_LGDBB_DVB_CheckSignalState(pDemodInfo))
					{
						DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, _DEMOD_E60_LGDBB_DVB_CheckSignalState() \n");
						DEMOD_RETURN_FAIL(__F__);
					}

				}
				else
				{
//					pDemodInfo->controlState		= LX_DEMOD_SYNC_CHECKING;
//					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : Going back to LX_DEMOD_SYNC_CHECKING.....\n");
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
 * DEMOD_E60_DVBT_Monitoring_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_E60_DVBT_Monitoring_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
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
		pDemodInfo->unLockCount = 0;

		if (RET_OK != _DEMOD_E60_LGDBB_DVB_CheckSignalState(pDemodInfo))
		{
			DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, _DEMOD_E60_LGDBB_DVB_CheckSignalState() \n");
			DEMOD_RETURN_FAIL(__F__);
		}

		if(pDemodInfo->signalStatus.packetError >= gE60GBB_FullDVBPkerrThreshold)
		{
			gE60GBB_DVB_UnlockCount_full_packeterr++;
			DEMOD_PRINT( "[DEMOD_CHIP] gE60GBB_DVB_UnlockCount_full_packeterr = %d \n",gE60GBB_DVB_UnlockCount_full_packeterr);

			if(gE60GBB_DVB_UnlockCount_full_packeterr == gE60GBB_FullDefaultPkerrCount) //gE60GBB_FullDVBTPkerrCount
			{
				DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] Oops !! Force to NOT LOCK by Full Packet error Count !!\n");
				gE60GBB_DVB_UnlockCount_full_packeterr = 0;

				if(RET_OK != DEMOD_E60_SoftwareReset())
				{
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_SoftwareReset() \n");
					DEMOD_RETURN_FAIL(__F__);
				}
				DEMOD_PRINT("[DEMOD_CHIP] SUCCESS DEMOD_E60_SoftwareReset() \n");

				pDemodInfo->lockStatus					= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedUnlock 			= TRUE;
				pDemodInfo->bNotifiedLock				= FALSE;
				pDemodInfo->signalStatus.bSignalValid 	= FALSE;

				DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] MSG_DVBT_FRONT_END_NOT_LOCKED by Full packet error ..... -_-;;\n");
			}
		}
		else
		{
			if(RET_OK != DEMOD_E60_Get_OperMode(&operMode))
			{
				DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_OperMode() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if(operMode == LX_DEMOD_DVBT2)
			{
				pDemodInfo->operMode 				= LX_DEMOD_DVBT2;
				pDemodInfo->setCfgParam.dvbt2.tuneMode 		= pDemodInfo->setCfgParam.dvbt.tuneMode;
				pDemodInfo->setCfgParam.dvbt2.channelBW		= pDemodInfo->setCfgParam.dvbt.channelBW;

				DEMOD_PRINT("[DEMOD_CHIP] FAIL, forcely changed to DVBT2 mode \n");
				DEMOD_PRINT("[DEMOD_CHIP] tuneMode(DVBT2)  = %d \n", pDemodInfo->setCfgParam.dvbt2.tuneMode);
				gE60GBB_DVB_UnlockCount_full_packeterr 		= 0;

				return RET_OK;
			}

			if((LX_DEMOD_LOCKED != pDemodInfo->lockStatus)	&& (TRUE != pDemodInfo->bNotifiedLock))
			{
				pDemodInfo->lockCount++;
				DEMOD_PRINT( "[DEMOD_CHIP] pDemodInfo->lockCount = %d \n",pDemodInfo->lockCount);
			}
			if(pDemodInfo->lockCount == 1)
			{
				pDemodInfo->lockStatus					= LX_DEMOD_LOCKED;
				pDemodInfo->bNotifiedLock				= TRUE;
				pDemodInfo->bNotifiedUnlock 			= FALSE;
				pDemodInfo->signalStatus.bSignalValid 	= TRUE;
				pDemodInfo->lockCount 					= 0;

				DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] MSG_DVBT_FRONT_END_LOCKED..... ^0^\n");

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
			DEMOD_PRINT( "[DEMOD_CHIP] pDemodInfo->unLockCount = %d \n",pDemodInfo->unLockCount);

			if(pDemodInfo->unLockCount == 4)
			{
				pDemodInfo->lockStatus 					= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedUnlock 			= TRUE;
				pDemodInfo->bNotifiedLock				= FALSE;
				pDemodInfo->signalStatus.bSignalValid 	= FALSE;
				pDemodInfo->unLockCount 				= 0;
				gE60GBB_DVB_UnlockCount_full_packeterr 	= 0;

				DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] MSG_DVBT_FRONT_END_NOT_LOCKED by unLockCount..... -_-\n");
			}

		}
	}
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBT2_Set_Config_auto
 * Control automatic setting of DVB-T config.
 *
 * @param bAutoDetect 	[IN] BOOLEAN - automatic setting (TRUE) / manual setting(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT2_Set_Config_auto (BOOLEAN bAutoDetect)
{
	DEMOD_INFO("deprecated\n");
/*
	LX_DEMOD_L2_Context *	pFrontend;

	DEMOD_PRINT("[DEMOD_CHIP] Start \n");
	DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] Set to %s \n", (bAutoDetect == TRUE)?"AUTO":"MANUAL");

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
 DEMOD_E60_DVBT2_Set_PartialConfig
 * Set all config parameters on DVB-T.
 * This function is used when LX_DEMOD_E60_DVBT_Set_Config_auto is disabled.
 *
 * @param *pDvbtConfigParam 	[IN] LX_DEMOD_DVBT_CONFIG_T - DVB-T config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT2_Set_PartialConfig (LX_DEMOD_DVBT2_CONFIG_T *pDvbt2ConfigParam)
{
	LX_DEMOD_L2_Context * 	pFrontend;
//	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	UINT8			plp_id = pDvbt2ConfigParam->unPLP;
	int			retc = NO_DEMOD_ERROR;

	DEMOD_PRINT("[DEMOD_CHIP] Start \n");
	DEMOD_PRINT("[DEMOD_CHIP] E60_DVBT2_PLP ID = [0x%x] \n",  plp_id);

	pFrontend = DEMOD_E60_GetContext();

	retc = DEMOD_L2_DVB_Set_PLP_Select(pFrontend,  plp_id, DEMOD_DD_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MANUAL);

	if(retc != NO_DEMOD_ERROR)
	{
		DEMOD_PRINT ("[DEMOD_CHIP] ERROR, DEMOD_L2_DVB_Set_PLP_Select error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return RET_ERROR;
	}

	pFrontend->set_PLP_ID 			= plp_id;
	gE60GBB_FullDVBPkerrThreshold 		= DVB_UNCHECK_PACKET_ERROR;

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBT2_Get_FFTMode
 * Get the information of bandwidth on DVB-T.
 *
 * @param *pTxModeLock 	[OUT] LX_DEMOD_LOCK_STATE_T - FFT mode lock state.
 * @param *pFftMode 	[OUT] LX_DEMOD_FFTMODE_T - detected FFT mode.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT2_Get_FFTMode (LX_DEMOD_LOCK_STATE_T *pTxModeLock, LX_DEMOD_FFTMODE_T *pFftMode)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("[DEMOD_CHIP] Start \n");

	pFrontend 	= DEMOD_E60_GetContext();
	*pTxModeLock 	= LX_DEMOD_LOCKED;
	*pFftMode 	= LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		DEMOD_RETURN_FAIL(__F__);
	}

	switch(signalStatus.fftMode)
	{
		case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_2K :
			*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_2K;
			break;

		case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_8K:
			*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_8K;
			break;

		case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_4K:
			*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_4K;
			break;

		case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_1K:
			*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_1K;
			break;

		case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_16K:
			*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_16K;
			break;

		case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_32K:
			*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_32K;
			break;

		default :
			*pFftMode = LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN;
			break;
	}

	if(signalStatus.bw_Ext)
	{
		DEMOD_PRINT("[DEMOD_CHIP] Extended .....FFT mode \n");
	}
	else
	{
		DEMOD_PRINT("[DEMOD_CHIP] Normal .....FFT mode \n");
	}

	return RET_OK;

}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBT2_Get_GuradIntervalMode
 * Get the information of guard interval on DVB-T.
 *
 * @param *pGIMode 	[OUT] LX_DEMOD_GIMODE_T - 1/32, 1/16, 1/8 and 1/4.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT2_Get_GuradIntervalMode (LX_DEMOD_GIMODE_T *pGIMode)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("[DEMOD_CHIP] Start \n");

	pFrontend = DEMOD_E60_GetContext();
	*pGIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_UNKNOWN;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		DEMOD_RETURN_FAIL(__F__);
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
 * DEMOD_E60_DVBT2_Get_CoderRate
 * Get the information of LP code rate on DVB-T2.
 *
 * @param *pLpCodeRate[OUT] LX_DEMOD_CODERATE_T - code rate : 1/2, 2/3, 3/4, 5/6 and 7/8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT2_Get_CoderRate (LX_DEMOD_CODERATE_T *pCodeRate)
{
	LX_DEMOD_L2_Context *	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	DEMOD_PRINT("[DEMOD_CHIP] Start \n");

	pFrontend = DEMOD_E60_GetContext();
	*pCodeRate = LX_DEMOD_CODE_UNKNOWN;

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		DEMOD_RETURN_FAIL(__F__);
	}

	switch(signalStatus.codeRate)
	{
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_1_2 :
			*pCodeRate = LX_DEMOD_CODE_1_2;
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_3_5:
			*pCodeRate = LX_DEMOD_CODE_3_5;
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_2_3 :
			*pCodeRate = LX_DEMOD_CODE_2_3;
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_3_4:
			*pCodeRate = LX_DEMOD_CODE_3_4;
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_4_5:
			*pCodeRate = LX_DEMOD_CODE_4_5;
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_5_6:
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
 * DEMOD_E60_DVBT2_Get_CurrentPLP_ID
 * Get current PLP ID on DVB-T2.
 *
 * @param *pCurrPlpID 	[OUT] UINT8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT2_Get_CurrentPLP_ID (UINT8 *pCurrPlpID)
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

	*pCurrPlpID = signalStatus.current_plp_id;

	DEMOD_PRINT("[DEMOD_CHIP] Current PLP ID = %d \n",signalStatus.current_plp_id);

	return RET_OK;
}
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBT2_Get_PlpInfo
 * Get TPS information on DVB-T
 *
 * @param *pTpsParams [OUT] LX_DEMOD_DVBT_CONFIG_T - TPS data structure.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT2_Get_PlpInfo (LX_DEMOD_DVBT2_CONFIG_T *pPlpParams)
{
	LX_DEMOD_L2_Context * 	pFrontend;
	LX_DEMOD_L2_SIG_STATUS	signalStatus;

	LX_DEMOD_BWMODE_T 	channelBW 	= LX_DEMOD_BW_UNKNOWN;
	LX_DEMOD_FFTMODE_T 	FFTMode 	= LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN ;
	LX_DEMOD_GIMODE_T 	gIMode 		= LX_DEMOD_DVBT_ISDBT_GIMODE_UNKNOWN;
	LX_DEMOD_CODERATE_T 	codeRate 	= LX_DEMOD_CODE_UNKNOWN;
	LX_DEMOD_RF_MODE_T 	qamMode 	= LX_DEMOD_UNKOWN_MODE;

	DEMOD_PRINT("[DEMOD_CHIP] Start \n");

	pFrontend = DEMOD_E60_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_SignalStatus() \n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if(NULL == pPlpParams)
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_DVBT_CONFIG_T TpsParams is NULL \n");
		return RET_ERROR;
	}

	switch(signalStatus.bandwidth)
	{
		case 0x08:
			channelBW = LX_DEMOD_BW_8MHZ;
			DEMOD_PRINT("[DEMOD_CHIP] Bandwidth = 8MHz\n");
			break;
		case 0x07:
			channelBW = LX_DEMOD_BW_7MHZ;
			DEMOD_PRINT("[DEMOD_CHIP] Bandwidth = 7MHz\n");
			break;
		case 0x06:
			channelBW = LX_DEMOD_BW_6MHZ;
			DEMOD_PRINT("[DEMOD_CHIP] Bandwidth = 6MHz\n");
			break;
		case 0x05:
			channelBW = LX_DEMOD_BW_5MHZ;
			DEMOD_PRINT("[DEMOD_CHIP] Bandwidth = 5MHz\n");
			break;
		default:
			channelBW = LX_DEMOD_BW_UNKNOWN;
			DEMOD_PRINT("[DEMOD_CHIP] Bandwidth = UNKNOWN\n");
			break;
	}

	pPlpParams->channelBW = channelBW;

	switch(signalStatus.fftMode)
	{
		case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_2K :
			FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_2K;
			DEMOD_PRINT("[DEMOD_CHIP] FFTMode = FFT_2K \n");
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_8K:
			FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_8K;
			DEMOD_PRINT("[DEMOD_CHIP] FFTMode = FFT_8K \n");
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_4K:
			FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_4K;
			DEMOD_PRINT("[DEMOD_CHIP] FFTMode = FFT_4K \n");
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_1K:
			FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_1K;
			DEMOD_PRINT("[DEMOD_CHIP] FFTMode = FFT_1K \n");
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_16K:
			FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_16K;
			DEMOD_PRINT("[DEMOD_CHIP] FFTMode = FFT_16K \n");
			break;
		case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_32K:
			FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_32K;
			DEMOD_PRINT("[DEMOD_CHIP] FFTMode = FFT_32K \n");
			break;
		default :
			FFTMode = LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN;
			DEMOD_PRINT("[DEMOD_CHIP] FFTMode = FFT_UNKNOWN \n");
			break;
	}

	pPlpParams->FFTMode = FFTMode;

	switch(signalStatus.guardInterval)
	{
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_4 :
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_4;
			DEMOD_PRINT("[DEMOD_CHIP] Guard Interval = 1_4\n");
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_8 :
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_8;
			DEMOD_PRINT("[DEMOD_CHIP] Guard Interval = 1_8\n");
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_16 :
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_16;
			DEMOD_PRINT("[DEMOD_CHIP] Guard Interval = 1_16\n");
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_32 :
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_32;
			DEMOD_PRINT("[DEMOD_CHIP] Guard Interval = 1_32\n");
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_19_128 :
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_19_128;
			DEMOD_PRINT("[DEMOD_CHIP] Guard Interval = 19_128\n");
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_19_256:
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_19_256;
			DEMOD_PRINT("[DEMOD_CHIP] Guard Interval = 19_256\n");
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_128:
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_128;
			DEMOD_PRINT("[DEMOD_CHIP] Guard Interval = 1_128\n");
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_64:
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_64;
			DEMOD_PRINT("[DEMOD_CHIP] Guard Interval = 1_64\n");
			break;
		default :
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_UNKNOWN;
			DEMOD_PRINT("[DEMOD_CHIP] Guard Interval = UNKNOWN\n");
			break;
	}

	pPlpParams->gIMode = gIMode;

	switch(signalStatus.codeRate)
	{
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_1_2 :
			codeRate = LX_DEMOD_CODE_1_2;
			DEMOD_PRINT("[DEMOD_CHIP] code rate = LX_DEMOD_CODE_1_2 \n");
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_3_5:
			codeRate = LX_DEMOD_CODE_3_5;
			DEMOD_PRINT("[DEMOD_CHIP] code rate = LX_DEMOD_CODE_3_5 \n");
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_2_3 :
			codeRate = LX_DEMOD_CODE_2_3;
			DEMOD_PRINT("[DEMOD_CHIP] code rate = LX_DEMOD_CODE_2_3 \n");
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_3_4:
			codeRate = LX_DEMOD_CODE_3_4;
			DEMOD_PRINT("[DEMOD_CHIP] code rate = LX_DEMOD_CODE_3_4 \n");
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_4_5:
			codeRate = LX_DEMOD_CODE_4_5;
			DEMOD_PRINT("[DEMOD_CHIP] code rate = LX_DEMOD_CODE_4_5 \n");
			break;
		case DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_5_6:
			codeRate = LX_DEMOD_CODE_5_6;
			DEMOD_PRINT("[DEMOD_CHIP] code rate = LX_DEMOD_CODE_5_6 \n");
			break;
		default :
			codeRate = LX_DEMOD_CODE_UNKNOWN;
			DEMOD_PRINT("[DEMOD_CHIP] code rate = UNKNOWN \n");
			break;
	}
	pPlpParams->codeRate = codeRate;

	switch(signalStatus.constellation)
	{
		case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QPSK :
			qamMode = LX_DEMOD_QPSK;
			DEMOD_PRINT("[DEMOD_CHIP] modulation = LX_DEMOD_QPSK \n");
			break;
		case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16 :
			qamMode = LX_DEMOD_16QAM;
			DEMOD_PRINT("[DEMOD_CHIP] modulation = LX_DEMOD_16QAM \n");
			break;
		case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM32:
			qamMode = LX_DEMOD_32QAM;
			DEMOD_PRINT("[DEMOD_CHIP] modulation = LX_DEMOD_32QAM \n");
			break;
		case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64 :
			qamMode = LX_DEMOD_64QAM;
			DEMOD_PRINT("[DEMOD_CHIP] modulation = LX_DEMOD_64QAM \n");
			break;
		case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM128 :
			qamMode = LX_DEMOD_128QAM;
			DEMOD_PRINT("[DEMOD_CHIP] modulation = LX_DEMOD_128QAM \n");
			break;
		case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM256 :
			qamMode = LX_DEMOD_256QAM;
			DEMOD_PRINT("[DEMOD_CHIP] modulation = LX_DEMOD_256QAM \n");
			break;
		default :
			qamMode = LX_DEMOD_UNKOWN_MODE;
			DEMOD_PRINT("[DEMOD_CHIP] modulation = LX_DEMOD_UNKOWN_MODE \n");
			break;
	}

	pPlpParams->qamMode = qamMode;
	pPlpParams->unPLP = signalStatus.current_plp_id;

	DEMOD_PRINT("[DEMOD_CHIP] current PLP ID = 0x%x set PLP ID = 0x%x \n",pPlpParams->unPLP, pFrontend->set_PLP_ID);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBT2_Get_multiPLP_ID
 * Get TPS information on DVB-T
 *
 * @param *pTpsParams [OUT] LX_DEMOD_DVBT_CONFIG_T - TPS data structure.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT2_Get_multiPLP_ID (LX_DEMOD_DVBT2_MULTI_PLP_INFO_T *pPlpParams)
{
	LX_DEMOD_L2_Context *	pFrontend;

	LX_DEMOD_L2_MULTI_PLP_ID_T 	PlpParams;
	UINT8 plpCount;
	int retc;
	int i ;
	
	DEMOD_PRINT("[DEMOD_CHIP] Start \n");

	pFrontend = DEMOD_E60_GetContext();

	// get multi-plp Id
	retc = DEMOD_L2_DVB_Get_PLP_ID(pFrontend, &PlpParams);

	for ( i = 0 ; i < 10 ; i++)
	{
		if (PlpParams.plpTotalCount == 0)
		{
			DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] DEMOD_L2_DVB_Get_PLP_ID updateing (returnvalue is %d) \n", retc);			
			retc = DEMOD_L2_DVB_Get_PLP_ID(pFrontend, &PlpParams);
		}
		else
		{
			DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] DEMOD_L2_DVB_Get_PLP_ID Update Done (%d)\n", i );
			break;
		}
		usleep_range(10000,11000);	/* 10ms ~ 11ms */
	}

	if (RET_OK != retc)
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_DVB_Get_PLP_ID() (returnvalue is %d)\n", retc);
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

	DEMOD_PRINT("[DEMOD_CHIP] PLP TotalCount = %d \n",pPlpParams->plpTotalCount);
	DEMOD_PRINT("[DEMOD_CHIP] PlpParams.plpCount_Including_channInfo = %d \n",PlpParams.plpCount_Including_channInfo);
	DEMOD_PRINT("[DEMOD_CHIP] PLP Datacount = %d \n",pPlpParams->plpDatacount);
	DEMOD_PRINT("[DEMOD_CHIP] PLP CommonPlpCount = %d \n",pPlpParams->commonPlpCount);

	for(plpCount=0; plpCount < pPlpParams->plpDatacount; plpCount++)
	{
		DEMOD_PRINT("[DEMOD_CHIP] PLP Data ID[%d] = 0x%x \n",plpCount, pPlpParams->plpDataID[plpCount]);

	}
	for(plpCount=0; plpCount < pPlpParams->commonPlpCount; plpCount++)
	{
		DEMOD_PRINT("[DEMOD_CHIP] PLP Common PLP ID[%d] = 0x%x \n",plpCount, pPlpParams->commonPlpID[plpCount]);
	}

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBT2_Get_TotalInfo
 * Get all information on DVB-T for debug
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_E60_DVBT2_Get_TotalInfo (void)
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

	DEMOD_PRINT("[DEMOD_CHIP] Start \n");

	pFrontend = DEMOD_E60_GetContext();

	if (DEMOD_L2_SignalStatus(pFrontend, &signalStatus))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_L2_DVB_Get_PLP_ID() \n");
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

	if (RET_OK != DEMOD_E60_Get_NeverLockStatus(LX_DEMOD_DVBT2, &neverLockStatus))
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

	sigMse.bMse = 0;
	sigMse.mse = signalStatus.mse_info;
	sigMse.constPwr = signalStatus.constPwr;

	DEMOD_PRINT("[DEMOD_CHIP] IF AGC value = %d(0x%x)\n",ifagcValue,ifagcValue);
	DEMOD_PRINT("[DEMOD_CHIP] Neverlock is %s\n",(neverLockStatus == LX_DEMOD_DETECTED) ? " Locked" : " NOT Locked");
	DEMOD_PRINT("[DEMOD_CHIP] Spectrum auto = %s, Inversion  = %s\n",(spectrumAuto == LX_DEMOD_AUTO) ? " Auto" : " Manual",
																					(spectrumInv == LX_DEMOD_INVERSION) ? " Inverted" : " Normal" );
	DEMOD_PRINT("[DEMOD_CHIP] offset = %d [KHz]\n",FreqOff);
	DEMOD_PRINT("[DEMOD_CHIP] mse = %d, constPwr = %d\n",sigMse.mse, sigMse.constPwr);

	if (RET_OK != DEMOD_E60_DVBT2_Get_PlpInfo( &plpParams))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_DVBT2_Get_PlpInfo() \n");
		return RET_ERROR;
	}
	if (RET_OK != DEMOD_E60_DVBT2_Get_multiPLP_ID(&plpInfo))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_DVBT2_Get_multiPLP_ID() \n");
		return RET_ERROR;
	}

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_E60_DVBT2_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_E60_DVBT2_Obtaining_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
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
				if(RET_OK != _DEMOD_E60_LGDBB_DVBT2_SetDemod(pDemodInfo))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, _DEMOD_E60_LGDBB_DVBT2_SetDemod() \n");
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_TUNE_NORMAL != pDemodInfo->setCfgParam.dvbt2.tuneMode)
				{
					if(RET_OK != DEMOD_E60_NeverlockScan(pDemodInfo, LX_DEMOD_FLAG_ON, &scanProcessing, &lockState))
					{
						DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_NeverlockScan() \n");
						DEMOD_RETURN_FAIL(__F__);
					}
					pDemodInfo->controlState 	= LX_DEMOD_TUNE_SCAN;
					gE60GBB_FullDVBPkerrThreshold 	= DVB_FULL_PACKET_ERROR;
					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_TUNE_START(AUTO or Manual SCAN) : Going to LX_DEMOD_TUNE_SCAN..... ^0^\n");
				}
				else
				{
					pDemodInfo->scanJobFlag 	= LX_DEMOD_FLAG_FINISH;
					pDemodInfo->controlState 	= LX_DEMOD_SYNC_CHECKING;
					gE60GBB_FullDVBPkerrThreshold 	= DVB_UNCHECK_PACKET_ERROR;
					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_TUNE_START(NORMAL SCAN) : Going to LX_DEMOD_SYNC_CHECKING..... ^0^\n");
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
					DEMOD_PRINT( "[DEMOD_CHIP] Already Done \n");
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
					pDemodInfo->operMode 		= LX_DEMOD_DVBT2;
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
					elapsedTime 			= jiffies_to_msecs(jiffies) - g_NewTuneReqeustTime;

					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] LX_DEMOD_TUNE_SCAN : MSG_DVBT_FRONT_END_NOT_LOCKED..\n") ;
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

				if(LX_DEMOD_DVBT == operMode)
				{
					pDemodInfo->operMode 			= LX_DEMOD_DVBT;
					pDemodInfo->setCfgParam.dvbt.tuneMode 	= pDemodInfo->setCfgParam.dvbt2.tuneMode;
					pDemodInfo->setCfgParam.dvbt.channelBW 	= pDemodInfo->setCfgParam.dvbt2.channelBW;
					pDemodInfo->setCfgParam.dvbt.bSetHp 	= 1;

					if(RET_OK != DEMOD_E60_DVBT_Set_PartialConfig(&(pDemodInfo->setCfgParam.dvbt)))
					{
						DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_DVBT_Set_PartialConfig() \n");
						DEMOD_RETURN_FAIL(__F__);
					}
					DEMOD_PRINT("[DEMOD_CHIP] LX_DEMOD_SYNC_CHECKING(DVBT2) : Going to LX_DEMOD_SYNC_CHECKING(DVBT forcely)..... ^0^\n");
					return RET_OK;
				}

				if(RET_OK != DEMOD_E60_Get_Lock(LX_DEMOD_L1_DONE, &lockState))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_DVBT_Set_PartialConfig() \n");
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					pDemodInfo->controlState		= LX_DEMOD_SIGNAL_STABLE;
					sigStablestartTime 			= jiffies_to_msecs(jiffies);
					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_SYNC_CHECKING : Going to LX_DEMOD_SIGNAL_STABLE..... ^0^\n");
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

				if(RET_OK != DEMOD_E60_Get_Lock(LX_DEMOD_FEC_DEC_EN, &lockState))
				{
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_Lock() \n");
					DEMOD_RETURN_FAIL(__F__);
				}

				if(LX_DEMOD_LOCKED == lockState)
				{
					pDemodInfo->lockStatus			= LX_DEMOD_LOCKED;
					pDemodInfo->signalStatus.bSignalValid 	= TRUE;
					pDemodInfo->bNotifiedLock		= TRUE;
					pDemodInfo->bNotifiedUnlock		= FALSE;
					elapsedTime 				= jiffies_to_msecs(jiffies) - g_RetuneStartTime;

					DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : MSG_DVBT_FRONT_END_LOCKED..... ^^^0^^^\n");
					DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : Elapsed Time = %d [ms] ..... ^^^0^^^\n", elapsedTime);

					if (RET_OK != DEMOD_E60_Get_CarrierFreqOffset(&freqOffset))
					{
						DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_CarrierFreqOffset() \n");
						DEMOD_RETURN_FAIL(__F__);
					}
					pDemodInfo->freqOffset 			= freqOffset;
					pDemodInfo->controlState		= LX_DEMOD_SIGNAL_LOCKED;

					DEMOD_PRINT( "[DEMOD_CHIP] LX_DEMOD_SIGNAL_STABLE : Frequency offset = %d [KHz] ..... ^^^0^^^\n", freqOffset);

					if (RET_OK != DEMOD_Get_TunedCFG(pDemodInfo))
					{
						DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_Get_TunedCFG() \n");
						DEMOD_RETURN_FAIL(__F__);
					}

					if (RET_OK != _DEMOD_E60_LGDBB_DVB_CheckSignalState(pDemodInfo))
					{
						DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, _DEMOD_E60_LGDBB_DVB_CheckSignalState() \n");
						DEMOD_RETURN_FAIL(__F__);
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
 * DEMOD_E60_DVBT2_Monitoring_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_E60_DVBT2_Monitoring_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{

	LX_DEMOD_LOCK_STATE_T	lockState;
	LX_DEMOD_OPER_MODE_T 	operMode;

	if(RET_OK != DEMOD_E60_Get_OperMode(&operMode))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_OperMode() \n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if((operMode == LX_DEMOD_DVBT))
	{
		pDemodInfo->operMode 			= LX_DEMOD_DVBT;
		pDemodInfo->setCfgParam.dvbt.tuneMode 	= pDemodInfo->setCfgParam.dvbt2.tuneMode;
		pDemodInfo->setCfgParam.dvbt.channelBW 	= pDemodInfo->setCfgParam.dvbt2.channelBW;
		pDemodInfo->setCfgParam.dvbt.bSetHp 	= 1;

		if(RET_OK != DEMOD_E60_DVBT_Set_PartialConfig(&(pDemodInfo->setCfgParam.dvbt)))
		{
			DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_DVBT_Set_PartialConfig() \n");
			DEMOD_RETURN_FAIL(__F__);
		}

		DEMOD_PRINT("[DEMOD_CHIP] FAIL, forcely changed to DVBT mode \n");
		DEMOD_PRINT("[DEMOD_CHIP] tuneMode (DVBT)  = %d \n", pDemodInfo->setCfgParam.dvbt.tuneMode);

		return RET_OK;
	}

	if(RET_OK != DEMOD_E60_Get_Lock(LX_DEMOD_FEC_DEC_EN, &lockState))
	{
		DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_Lock() \n");
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

		if (RET_OK != _DEMOD_E60_LGDBB_DVB_CheckSignalState(pDemodInfo))
		{
			DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, _DEMOD_E60_LGDBB_DVB_CheckSignalState() \n");
			DEMOD_RETURN_FAIL(__F__);
		}

		DEMOD_PRINT( "[DEMOD_CHIP] pDemodInfo->signalStatus.packetError = %d\n",pDemodInfo->signalStatus.packetError);
		DEMOD_PRINT( "[DEMOD_CHIP] gE60GBB_FullDVBPkerrThreshold = %d \n", gE60GBB_FullDVBPkerrThreshold);

		if(pDemodInfo->signalStatus.packetError >= gE60GBB_FullDVBPkerrThreshold)
		{
			gE60GBB_DVB_UnlockCount_full_packeterr++;
			DEMOD_PRINT( "[DEMOD_CHIP] gE60GBB_DVB_UnlockCount_full_packeterr = %d \n",gE60GBB_DVB_UnlockCount_full_packeterr);

			if(gE60GBB_DVB_UnlockCount_full_packeterr == gE60GBB_FullDVBT2PkerrCount)
			{
				DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] Oops !! Force to NOT LOCK by Full Packet error Count !!\n");
				gE60GBB_DVB_UnlockCount_full_packeterr = 0;

				if(RET_OK != DEMOD_E60_SoftwareReset())
				{
					DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_SoftwareReset() \n");
					DEMOD_RETURN_FAIL(__F__);
				}
				DEMOD_PRINT("[DEMOD_CHIP] SUCCESS DEMOD_E60_SoftwareReset() \n");

				pDemodInfo->lockStatus			= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedUnlock 		= TRUE;
				pDemodInfo->bNotifiedLock		= FALSE;
				pDemodInfo->signalStatus.bSignalValid 	= FALSE;
				DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] MONITORING FUNC : MSG_DVBT_FRONT_END_NOT_LOCKED..... -_-;;\n");
			}
		}
		else
		{
			if(RET_OK != DEMOD_E60_Get_OperMode(&operMode))
			{
				DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] FAIL, DEMOD_E60_Get_OperMode() \n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if((operMode == LX_DEMOD_DVBT))
			{
				pDemodInfo->operMode 			= LX_DEMOD_DVBT;
				pDemodInfo->setCfgParam.dvbt.tuneMode 	= pDemodInfo->setCfgParam.dvbt2.tuneMode;
				pDemodInfo->setCfgParam.dvbt.channelBW 	= pDemodInfo->setCfgParam.dvbt2.channelBW;
				pDemodInfo->setCfgParam.dvbt.bSetHp 	= 1;
				gE60GBB_DVB_UnlockCount_full_packeterr 	= 0;

				DEMOD_PRINT("[DEMOD_CHIP] FAIL, forcely changed to DVBT mode \n");
				DEMOD_PRINT("[DEMOD_CHIP] tuneMode (DVBT2)  = %d \n", pDemodInfo->setCfgParam.dvbt.tuneMode);

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

				DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] MONITORING FUNC : MSG_DVBT_FRONT_END_LOCKED by LockCount\n");

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
				pDemodInfo->lockStatus 				= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedUnlock 			= TRUE;
				pDemodInfo->bNotifiedLock			= FALSE;
				pDemodInfo->signalStatus.bSignalValid 		= FALSE;
				gE60GBB_DVB_UnlockCount_full_packeterr 		= 0;
				pDemodInfo->unLockCount 			= 0;

				DEMOD_PRINT_ALWAYS( "[DEMOD_CHIP] MSG_DVBT_FRONT_END_NOT_LOCKED by unLockCount..... -_-\n");
			}
		}
	}
	return RET_OK;
}

