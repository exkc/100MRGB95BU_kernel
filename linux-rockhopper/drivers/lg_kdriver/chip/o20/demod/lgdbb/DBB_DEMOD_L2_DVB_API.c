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

/*****************************************************************************
**
**  Name:DBB_DEMOD_L2_DVB_API.c
**
**  Description:    .
**
**  Functions
**  Implemented:
**
**  References:
**
**  Exports:
**
**  Dependencies:
**
**
**  Revision History:
**
**     Date        Author          Description
**  -------------------------------------------------------------------------
**   20-01-2016  Jeongpil Yun    Initial draft.
**
*****************************************************************************/
#define DEMOD_TAG "[L2.DVB] "

#include <DBB_DEMOD_typedefs.h>
#include <demod_util.h>

#include <DBB_DEMOD_L2_DVB_API.h>

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_XTENSA)

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
#include <asm/div64.h> //do_div
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
#include <math.h>
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)

#endif



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_DVB_SW_Init.
 * software initialization function for DVBT/DVBT2/DVBC/DVBC2/DVBS/DVBS2
 *  Used to initialize the demodulator and tuner structures
 *
 * @param *frontend 		[IN] LX_DEMOD_L2_Context, a pointer to LX_DEMOD_L2_Context context to be initialized
 * @param demodAddr 		[IN] int, the I2C address of the demod
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_DVB_SW_Init (LX_DEMOD_L2_Context * frontend  , UINT32 demodAddr)
{
	int retc = NO_DEMOD_ERROR;

	frontend->auto_detect_DVBT_T2     = 1;
	frontend->demod->bIsStandby   = 0;
	frontend->cable_blind_scan = 0;

//	frontend->standard = DEMOD_DD_MODE_PROP_MODULATION_DVBT;

	frontend->detected_rf = 0;
	frontend->centerFrq= 0;

	frontend->num_PLP_total= 0;
	frontend->set_PLP_ID= 0;

	/* Calling underlying SW initialization functions */
	retc =  DEMOD_L1_API_Init (frontend->demod,  demodAddr);
	if (NO_DEMOD_ERROR != retc) {
		DEMOD_ERROR("DEMOD_L1_API_Init failed with %d\n", retc);
	}
	return retc;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_DVB_Set_demod.
 * sets the demod for locking the signals
 *
 * @param *frontend 			[IN] LX_DEMOD_L2_Context
 * @param standard 			[IN] UINT8
 * @param freq 				[IN] UINT32
 * @param tuneMode 			[IN] UINT8
 * @param specInv_Auto_Enable 	[IN] UINT8
 * @param specInv 			[IN] UINT8
 * @param ter_bandwidth_KHz 	[IN] UINT16
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_DVB_Set_demod   (LX_DEMOD_L2_Context *frontend
								, UINT8 standard
								, UINT32 freq
								, UINT8 tuneMode
								, UINT8 specInv_Auto_Enable
								, UINT8 specInv
								, UINT16 ter_bandwidth_KHz
								, UINT8 dvbt_hpSel
								, UINT16 symbol_rate_Kbps
								, UINT8 dvb_c_constellation
								, UINT8  plp_id
								, UINT8 T2_lock_mode
	)
{
	int retc = NO_DEMOD_ERROR;
	UINT32 startTime;           /* startTime is used to measure internal durations. It is set in various places, whenever required                                                */

	startTime = DEMOD_L0_system_time();

	frontend->centerFrq= freq;

	frontend->demod->prop->dd_mode.tuneMode		= tuneMode;
	frontend->demod->prop->dd_mode.specinvauto	= specInv_Auto_Enable;
	frontend->demod->prop->dd_mode.specinv		= specInv;
	frontend->demod->prop->dd_mode.modulation	= standard;
	frontend->demod->prop->dd_mode.bw		= (UINT8)(ter_bandwidth_KHz/1000);
	frontend->demod->prop->dd_if_freq.if_freq	= DEMOD_DD_IF_FREQ_PROP_IF_FREQ_5MHZ;

	DEMOD_NOTI("[DEMOD_API] Lock to %s at %d KHz\n", DEMOD_L1_API_StandardName(standard), freq);
	DEMOD_NOTI("[DEMOD_API] Received BW = %d KHz\t, Setting BW = %d MHz\n", ter_bandwidth_KHz, frontend->demod->prop->dd_mode.bw );
	DEMOD_NOTI("[DEMOD_API] TuneMode : 0x%02x\n", frontend->demod->prop->dd_mode.tuneMode);

	switch (standard)
	{
		case DEMOD_DD_MODE_PROP_MODULATION_DVBT2:
		case DEMOD_DD_MODE_PROP_MODULATION_DVBT :
		{
#ifdef DEMOD_DD_CLOCK_MODE_PROP
			frontend->demod->prop->dd_clk_mode.clk_mode 	= DEMOD_DD_CLOCK_MODE_PROP_96MHZ;
#endif
			frontend->demod->prop->dd_adc_sel.adcClk 	= DEMOD_DD_ADC_PROP_ADCCLK_24MHZ;

			frontend->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_DVBT_DVBT2_ENABLE;

			retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_AUTO_MODE_PROP);
			if(NO_DEMOD_ERROR != retc)
			{
				DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_Set_Property(DEMOD_DD_AUTO_MODE_PROP) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}

			if (1700 == ter_bandwidth_KHz)
			{
				frontend->demod->prop->dd_mode.bw              = DEMOD_DD_MODE_PROP_BW_BW_1D7MHZ;
			}

			if (DEMOD_DD_MODE_PROP_MODULATION_DVBT == standard)
			{
				frontend->demod->prop->dd_dvbt_hp_sel.hierhpsel  	= dvbt_hpSel;
				retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_DVBT_HIERARCHY_PROP_CODE);
				if(NO_DEMOD_ERROR != retc)
				{
					DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_Set_Property(DEMOD_DD_DVBT_HIERARCHY_PROP_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
					return retc;
				}

				frontend->demod->prop->dd_mode.modulation  = DEMOD_DD_MODE_PROP_MODULATION_DVBT;

				frontend->demod->prop->dd_dvbt2_lock_mode.lock_mode= T2_lock_mode;
				retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_DVBT2_MODE_PROP);
				if(NO_DEMOD_ERROR != retc)
				{
					DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_Set_Property(DEMOD_DD_DVBT2_MODE_PROP) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
					return retc;
				}

				if(DEMOD_DD_MODE_PROP_TUNEMODE_NORMAL != frontend->demod->prop->dd_mode.tuneMode) // autoscan
				{
					DEMOD_NOTI("[DEMOD_API] DVB-T/T2 auto scan \n");

					frontend->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_DVBT_DVBT2_ENABLE;
					retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_AUTO_MODE_PROP_CODE);
					if(NO_DEMOD_ERROR != retc)
					{
						DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_Set_Property(DEMOD_DD_AUTO_MODE_PROP_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
						return retc;
					}

					frontend->demod->cmd->dvbt2_plp_select.plp_id_sel_mode = DEMOD_DD_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MANUAL;
					frontend->demod->cmd->dvbt2_plp_select.plp_id = 0xff;
					frontend->set_PLP_ID = plp_id;

					retc = DEMOD_L1_SET_DD_DVBT2_PLP_Select(frontend->demod, frontend->demod->cmd->dvbt2_plp_select.plp_id , frontend->demod->cmd->dvbt2_plp_select.plp_id_sel_mode);
					if(NO_DEMOD_ERROR != retc)
					{
						DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_SET_DD_DVBT2_PLP_Select 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
						return retc;
					}

				}
				else // not auto scan
				{
					frontend->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_DVBT_ONLY_ENABLE;
					retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_AUTO_MODE_PROP_CODE);
					if(NO_DEMOD_ERROR != retc)
					{
						DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_Set_Property(DEMOD_DD_AUTO_MODE_PROP_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
						return retc;
					}
				}
			}
			if (DEMOD_DD_MODE_PROP_MODULATION_DVBT2 == standard)
			{
				frontend->demod->prop->dd_dvbt_hp_sel.hierhpsel  	= dvbt_hpSel;
				retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_DVBT_HIERARCHY_PROP_CODE);
				if(NO_DEMOD_ERROR != retc)
				{
					DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_Set_Property(DEMOD_DD_DVBT_HIERARCHY_PROP_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
					return retc;
				}

				frontend->demod->prop->dd_dvbt2_lock_mode.lock_mode= T2_lock_mode;
				retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_DVBT2_MODE_PROP);
				if(NO_DEMOD_ERROR != retc)
				{
					DEMOD_ERROR ("[DEMOD_API] FAIL, DEMOD_L1_Set_Property(DEMOD_DD_DVBT2_MODE_PROP) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
					return retc;
				}
				DEMOD_INFO("[DEMOD_API] T2_lock_mode %d\n",T2_lock_mode);

				frontend->demod->prop->dd_mode.modulation  = DEMOD_DD_MODE_PROP_MODULATION_DVBT2;

				if(DEMOD_DD_MODE_PROP_TUNEMODE_NORMAL != frontend->demod->prop->dd_mode.tuneMode) // autoscan
				{
					frontend->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_DVBT_DVBT2_ENABLE;
					retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_AUTO_MODE_PROP_CODE);
					if(NO_DEMOD_ERROR != retc)
					{
						DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_Set_Property(DEMOD_DD_AUTO_MODE_PROP_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
						return retc;
					}
//					DEMOD_PRINT_ALWAYS("frontend->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_DVBT_DVBT2_ENABLE\n");
				}
				else
				{
					frontend->demod->prop->dd_mode.modulation  = DEMOD_DD_MODE_PROP_MODULATION_DVBT2;
					frontend->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_DVBT2_ONLY_ENABLE;
					retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_AUTO_MODE_PROP_CODE);
					if(NO_DEMOD_ERROR != retc)
					{
						DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_Set_Property(DEMOD_DD_AUTO_MODE_PROP_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
						return retc;
					}


					frontend->demod->cmd->dvbt2_plp_select.plp_id_sel_mode = DEMOD_DD_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MANUAL;
					frontend->demod->cmd->dvbt2_plp_select.plp_id = (UINT8)plp_id;
					frontend->set_PLP_ID = plp_id;

					retc = DEMOD_L1_SET_DD_DVBT2_PLP_Select    (frontend->demod, frontend->demod->cmd->dvbt2_plp_select.plp_id , frontend->demod->cmd->dvbt2_plp_select.plp_id_sel_mode);
					if(NO_DEMOD_ERROR != retc)
					{
						DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_SET_DD_DVBT2_PLP_Select() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
						return retc;
					}
				}

			}
			DEMOD_NOTI("[DEMOD_API] DVB-T/T2 : BW %d KHz\n", ter_bandwidth_KHz);
		}
		break;
	case DEMOD_DD_MODE_PROP_MODULATION_DVBC :
		{
#ifdef DEMOD_DD_CLOCK_MODE_PROP
			frontend->demod->prop->dd_clk_mode.clk_mode 	= DEMOD_DD_CLOCK_MODE_PROP_96MHZ;
#endif
			frontend->demod->prop->dd_adc_sel.adcClk 	= DEMOD_DD_ADC_PROP_ADCCLK_24MHZ;

			if (DEMOD_DD_MODE_PROP_TUNEMODE_FIXED_DATA == frontend->demod->prop->dd_mode.tuneMode)
			{
//				tempSrdCalc = 42949672960000;  // (40000/4) * 2^32
//				tempSrdCalc = _DEMOD_do_div64_32(tempSrdCalc,symbol_rate_Kbps);
//				tempSrdCalc = tempSrdCalc - 4294967296; // 2^32 = 4294967296

				frontend->demod->cmd->dvbc_sym_rate.sym_rate	= symbol_rate_Kbps;
				frontend->demod->cmd->dvbc_sym_rate.auto_en	= DEMOD_DD_DVBC_SRD_CMD_AUTO_EN_DISABLE;

				frontend->demod->prop->dd_constel.constellation = dvb_c_constellation;
				frontend->demod->prop->dd_constel.constel_autodet = DEMOD_DD_CONSTELATION_PROP_AUTO_DET_DISABLE;
				retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_CONSTEL_PROP_CODE);
				if(NO_DEMOD_ERROR != retc)
				{
					DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_Set_Property(DEMOD_DD_CONSTEL_PROP_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
					return retc;
				}
			}
			else
			{
				frontend->demod->cmd->dvbc_sym_rate.sym_rate	= 0;
				frontend->demod->cmd->dvbc_sym_rate.auto_en	= DEMOD_DD_DVBC_SRD_CMD_AUTO_EN_ENABLE;

				frontend->demod->prop->dd_constel.constellation = dvb_c_constellation;
				frontend->demod->prop->dd_constel.constel_autodet = DEMOD_DD_CONSTELATION_PROP_AUTO_DET_ENABLE;
				retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_CONSTEL_PROP_CODE);
				if(NO_DEMOD_ERROR != retc)
				{
					DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_Set_Property(DEMOD_DD_CONSTEL_PROP_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
					return retc;
				}

			}

			DEMOD_NOTI("[DEMOD_API] DVB-C : sr %d kbps, constel %d\n", symbol_rate_Kbps, dvb_c_constellation);
		}
		break;

	case DEMOD_DD_MODE_PROP_MODULATION_DVBC2 :
		{
			DEMOD_NOTI("[DEMOD_API] DVB-C2 : Not Supported\n");
		}
		break;

	default : /* ATV */
		{
			DEMOD_NOTI("[DEMOD_API] '%d' standard (%s) is not managed by DEMOD_lock_to_carrier\n", standard, DEMOD_L1_API_StandardName(standard));
			return 0;
		  }
		break;
	}
	DEMOD_NOTI("[DEMOD_API] Setting BW is %d MHz\n", frontend->demod->prop->dd_mode.bw);
	retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_MODE_PROP_CODE);
	if(NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_Set_Property(DEMOD_DD_MODE_PROP_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}
#ifdef DEMOD_DD_CLOCK_MODE_PROP
	retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_CLOCK_MODE_PROP_CODE);
	if(NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_Set_Property(DEMOD_DD_CLOCK_MODE_PROP_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}
#endif
	retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_ADC_PROP_CODE);
	if(NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_Set_Property(DEMOD_DD_ADC_PROP_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

	retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_IF_FREQ_PROP_CODE);
	if(NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_Set_Property(DEMOD_DD_IF_FREQ_PROP_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

	if(DEMOD_DD_MODE_PROP_TUNEMODE_NORMAL != frontend->demod->prop->dd_mode.tuneMode)
	{
		if(freq <= 870000)
			DEMOD_L0_system_wait(20);
		else
			DEMOD_L0_system_wait(40);
	}

	startTime = DEMOD_L0_system_time();

	retc = DEMOD_L1_SET_DD_Tune(frontend->demod);
	if(NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_SET_DD_Tune() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

	if (DEMOD_DD_MODE_PROP_MODULATION_DVBC == standard)
	{
		retc = DEMOD_L1_SET_DD_SymbolRate_Detect(frontend->demod, frontend->demod->cmd->dvbc_sym_rate.auto_en, symbol_rate_Kbps);
		if(NO_DEMOD_ERROR != retc)
		{
			DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_SET_DD_SymbolRate_Detect() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
			return retc;
		}
	}

	DEMOD_NOTI("[DEMOD_API] DVB Lock took %3d ms\n", DEMOD_L0_system_time() - startTime);

	return retc;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_DVB_AutoModeDetectOn.
 * deprecated
 */

int DEMOD_L2_DVB_AutoModeDetectOn (LX_DEMOD_L2_Context *frontend)
{
	DEMOD_INFO("deprecated\n");
	return NO_DEMOD_ERROR;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_DVB_AutoModeDetectOff.
 * deprecated
 */

int DEMOD_L2_DVB_AutoModeDetectOff (LX_DEMOD_L2_Context *frontend)
{
	DEMOD_INFO("deprecated\n");
	return NO_DEMOD_ERROR;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_DVB_Set_PLP_Select
 *
 * @param *frontend 			[IN] LX_DEMOD_L2_Context
 * @param plp_id 				[IN] UINT8
 * @param plp_id_sel_mode 		[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_DVB_Set_PLP_Select(LX_DEMOD_L2_Context *frontend,  UINT8 plp_id, UINT8   plp_id_sel_mode)
{
	int retc = NO_DEMOD_ERROR;
/*
	frontend->demod->prop->dd_mode.modulation  = DEMOD_DD_MODE_PROP_MODULATION_DVBT2;
	frontend->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_DVBT2_ONLY_ENABLE;
	retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_AUTO_MODE_PROP_CODE);
	if(NO_DEMOD_ERROR != retc)
	{
		DEMOD_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}
	DEMOD_L0_system_wait(10);
*/
	frontend->set_PLP_ID = plp_id;
//	frontend->demod->cmd->dvbt2_plp_select.plp_id_sel_mode = DEMOD_DD_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MANUAL;
	frontend->demod->cmd->dvbt2_plp_select.plp_id = (UINT8)plp_id;

	retc = DEMOD_L1_SET_DD_DVBT2_PLP_Select    (frontend->demod, frontend->demod->cmd->dvbt2_plp_select.plp_id , plp_id_sel_mode);

	return retc;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_DVBC_Set_SymbolRate_Detect
 *
 * @param *frontend 			[IN] LX_DEMOD_L2_Context
 * @param autoEn 				[IN] UINT8
 * @param symbol_rate_Kbps		[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_DVBC_Set_SymbolRate_Detect(LX_DEMOD_L2_Context *frontend,  UINT8 autoEn, UINT8   symbol_rate_Kbps)
{
	int retc = NO_DEMOD_ERROR;

	frontend->demod->cmd->dvbc_sym_rate.sym_rate     = symbol_rate_Kbps;
	frontend->demod->cmd->dvbc_sym_rate.auto_en	= autoEn;

	retc = DEMOD_L1_SET_DD_SymbolRate_Detect(frontend->demod, frontend->demod->cmd->dvbc_sym_rate.auto_en, symbol_rate_Kbps);
	if(NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_SET_DD_SymbolRate_Detect() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

	return retc;

}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_DVB_Get_PLP_ID
 *
 * @param *frontend 			[IN] LX_DEMOD_L2_Context
 * @param *pPlpParams 			[IN] LX_DEMOD_L2_MULTI_PLP_ID_T
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_DVB_Get_PLP_ID   (LX_DEMOD_L2_Context *frontend, LX_DEMOD_L2_MULTI_PLP_ID_T *pPlpParams)
{
	UINT8 num_cplp = 0;
	UINT8 num_dplp = 0;
	UINT8 index;
	UINT8 PLPCount =0;

	int retc = NO_DEMOD_ERROR;

	DEMOD_PRINT("[DEMOD_API] Start\n");

	retc = DEMOD_L1_GET_DD_DVBT2_Status   (frontend->demod);
	if(NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_DVBT2_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

	pPlpParams->plpTotalCount = frontend->demod->rsp->dvbt2_status.num_plp;

	if(0 == pPlpParams->plpTotalCount) return -ERROR_DEMOD_RESULT_NOT_READY;

	for (index = 0; index <	pPlpParams->plpTotalCount; index++)
	{
		frontend->demod->cmd->dvbt2_plp_id.plp_index = index;
		retc = DEMOD_L1_GET_DD_DVBT2_PLP_ID(frontend->demod, frontend->demod->cmd->dvbt2_plp_id.plp_index);
		if(retc == NO_DEMOD_ERROR)
		{
			DEMOD_NOTI("[DEMOD_API] Get plp_id = 0x%02x\n", frontend->demod->rsp->dvbt2_plp_id.plp_id);
			pPlpParams->plpID[PLPCount] = frontend->demod->rsp->dvbt2_plp_id.plp_id;
			DEMOD_NOTI("[DEMOD_API] plpID[%d] = %02x\tIndex = %d\n", PLPCount, pPlpParams->plpID[PLPCount], index);
			pPlpParams->plpconf[PLPCount] = frontend->demod->rsp->dvbt2_plp_id.plp_conf;
			if(pPlpParams->plpconf[PLPCount] == 0)
			{
				num_cplp++;
			}
			else if((pPlpParams->plpconf[PLPCount] == 1) ||(pPlpParams->plpconf[PLPCount] == 2))
			{
				num_dplp++;
			}
			pPlpParams->plpCount_Including_channInfo = num_dplp;
			PLPCount++;
		}
		else
		{
			DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_DVBT2_PLP_ID() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
			return retc;
		}
	}

	DEMOD_NOTI("[DEMOD_API] Valid num_plp = %d\n",PLPCount);
	DEMOD_NOTI("[DEMOD_API] plpCount_Including_channInfo = %d(num_dplp = %d, num_cplp = %d)\n", pPlpParams->plpCount_Including_channInfo, num_dplp, num_cplp );

	return NO_DEMOD_ERROR;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_DVBT2_Set_BaseAddr_AXI Address for AXI_memory write.
 * Set Set_Base Address for DVBT2/S2 AXI_memory
 *
 * @param *frontend 			[IN] LX_DEMOD_L2_Context
 * @param baseAddr1 			[IN] UINT32
 * @param baseAddr2 			[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_DVBT2_Set_BaseAddr_AXI(LX_DEMOD_L2_Context *frontend, UINT32 baseAddr1, UINT32 baseAddr2 )
{
	int retc;
	// baseAddr1 : TDI
	// baseAddr2 : DJB
	retc =  DEMOD_L1_API_DVBT2_BaseAddr_AXI(frontend->demod, baseAddr1, baseAddr2);

	return retc;

}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_DVB_Set_BaseAddr_AXI Address for AXI_memory write.
 * Set Set_Base Address for DVB AXI_memory
 *
 * @param *frontend 			[IN] LX_DEMOD_L2_Context
 * @param baseAddr1 			[IN] UINT32
 * @param baseAddr2 			[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_DVB_Set_BaseAddr_AXI(LX_DEMOD_L2_Context *frontend, UINT32 baseAddr1, UINT32 baseAddr2, UINT32 baseAddr3 )
{
	int retc;
	// baseAddr1 : TDI
	// baseAddr2 : DJB
	// baseAddr3 : RISIC
	retc =  DEMOD_L1_API_DVB_BaseAddr_AXI(frontend->demod, baseAddr1, baseAddr2, baseAddr3);

	return retc;

}


