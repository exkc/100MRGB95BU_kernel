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


#include "DBB_DEMOD_L2_DVB_API.h"               /* Include file for this code */


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_DVB_SW_Init.
 * software initialization function for DVBT/DVBT2/DVBC/DVBC2/DVBS/DVBS2
 *  Used to initialize the demodulator and tuner structures
 *
 * @param *front_end 		[IN] LX_DEMOD_L2_Context, a pointer to LX_DEMOD_L2_Context context to be initialized
 * @param demodAdd 		[IN] int, the I2C address of the demod
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8 DEMOD_L2_DVB_SW_Init            (LX_DEMOD_L2_Context *front_end  , UINT32 demodAdd)
{
	UINT8 return_code = NO_DEMOD_ERROR;
	DBB_PRINT("DEMOD_L2_DVB_SW_Init starting...\n");

	/* Pointers initialization */
	front_end->demod     = &(front_end->demodObj);
	front_end->demod_init_done    = 0;
	front_end->auto_detect_DVBT_T2     = 1;
	front_end->demod->bIsStandby   = 0;
	front_end->cable_blind_scan = 0;

	front_end->standard = DEMOD_DD_MODE_PROP_MODULATION_DVBT;

	front_end->detected_rf = 0;
	front_end->centerFrq= 0;

	front_end->num_PLP_total= 0;
	front_end->set_PLP_ID= 0;

	/* Calling underlying SW initialization functions */
	return_code = DEMOD_L1_API_Init      (front_end->demod,     demodAdd);

    DBB_PRINT("DEMOD_L2_DVB_SW_Init complete\n");
    return return_code;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_DVB_Set_demod.
 * sets the demod for locking the signals
 *
 * @param *front_end 			[IN] LX_DEMOD_L2_Context
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
UINT8   DEMOD_L2_DVB_Set_demod   (LX_DEMOD_L2_Context *front_end
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
	UINT8 return_code = NO_DEMOD_ERROR;
	UINT32 startTime;           /* startTime is used to measure internal durations. It is set in various places, whenever required                                                */


	DBB_PRINT ("relock to %s at %d KHz\n", DEMOD_L1_API_StandardName(standard), freq);
	startTime = DEMOD_L0_system_time();

	front_end->centerFrq= freq;

	front_end->demod->prop->dd_mode.tuneMode            = tuneMode;
	front_end->demod->prop->dd_mode.specinvauto         = specInv_Auto_Enable;
	front_end->demod->prop->dd_mode.specinv               = specInv;
	front_end->demod->prop->dd_mode.modulation          = standard;
	front_end->demod->prop->dd_mode.bw                	= (UINT8)(ter_bandwidth_KHz/1000);
	front_end->demod->prop->dd_if_freq.if_freq = DEMOD_DD_IF_FREQ_PROP_IF_FREQ_5MHZ;
	DBB_PRINT ("ter_bandwidth_KHz : %d\t, bw : %d\n", ter_bandwidth_KHz, front_end->demod->prop->dd_mode.bw );
	DBB_PRINT ("front_end->demod->prop->dd_mode.tuneMode : 0x%02x\n", front_end->demod->prop->dd_mode.tuneMode);

	//if(front_end->centerFrq == 474000)		DEMOD_L2_SET_REG(front_end,  0x4077, 1, TRUE);
	//else									DEMOD_L2_SET_REG(front_end,  0x4077, 1, FALSE);
		
	
/*
	if(front_end->demod->prop->dd_mode.tuneMode != DEMOD_DD_MODE_PROP_TUNEMODE_NORMAL)
	{
 	//		DEMOD_L0_system_wait(50);
 			DEMOD_L0_system_wait(20);
	}
	else
	{
//			DEMOD_L0_system_wait(30);
			DEMOD_L0_system_wait(20);
	}
*/
	switch (standard)
	{
		case DEMOD_DD_MODE_PROP_MODULATION_DVBT2:
		case DEMOD_DD_MODE_PROP_MODULATION_DVBT :
		{
#ifdef FPGA_CPBOX
			front_end->demod->prop->dd_clk_mode.clk_mode 	= DEMOD_DD_CLOCK_MODE_PROP_20MHZ;
			front_end->demod->prop->dd_adc_sel.adcClk 		= DEMOD_DD_ADC_PROP_ADCCLK_20MHZ;
#else
			front_end->demod->prop->dd_clk_mode.clk_mode 	= DEMOD_DD_CLOCK_MODE_PROP_24MHZ;
			front_end->demod->prop->dd_adc_sel.adcClk 		= DEMOD_DD_ADC_PROP_ADCCLK_24MHZ;
#endif
			
			front_end->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_DVBT_DVBT2_ENABLE;
			return_code = DEMOD_L1_Set_Property(front_end->demod, DEMOD_DD_AUTO_MODE_PROP);
			if(return_code != NO_DEMOD_ERROR)
			{
				DBB_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
				return return_code;
			}
			
			if (ter_bandwidth_KHz == 1700)
			{
				front_end->demod->prop->dd_mode.bw              = DEMOD_DD_MODE_PROP_BW_BW_1D7MHZ;
			}
			//if (front_end->auto_detect_DVBT_T2)
			
			//else
			//{
			if (standard == DEMOD_DD_MODE_PROP_MODULATION_DVBT )
			{
				front_end->demod->prop->dd_dvbt_hp_sel.hierhpsel  	= dvbt_hpSel;
				return_code = DEMOD_L1_Set_Property(front_end->demod, DEMOD_DD_DVBT_HIERARCHY_PROP_CODE);
				if(return_code != NO_DEMOD_ERROR)
				{
					DBB_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
					return return_code;
				}

				front_end->demod->prop->dd_mode.modulation  = DEMOD_DD_MODE_PROP_MODULATION_DVBT;
				
				front_end->demod->prop->dd_dvbt2_lock_mode.lock_mode= T2_lock_mode;
				return_code = DEMOD_L1_Set_Property(front_end->demod, DEMOD_DD_DVBT2_MODE_PROP);
				if(return_code != NO_DEMOD_ERROR)
				{
					DBB_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
					return return_code;
				}
				//DBB_PRINT ("T2_lock_mode %d\n",T2_lock_mode);			
				
				if(front_end->demod->prop->dd_mode.tuneMode != DEMOD_DD_MODE_PROP_TUNEMODE_NORMAL) // autoscan
				{
					DBB_PRINT("DVB-T/T2 auto scan\n");						

					front_end->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_DVBT_DVBT2_ENABLE;
					return_code = DEMOD_L1_Set_Property(front_end->demod, DEMOD_DD_AUTO_MODE_PROP_CODE);
					if(return_code != NO_DEMOD_ERROR)
					{
						DBB_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
						return return_code;
					}
					DBB_PRINT("front_end->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_DVBT_DVBT2_ENABLE\n");

					front_end->demod->cmd->dvbt2_plp_select.plp_id_sel_mode = DEMOD_DD_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MANUAL;
					front_end->demod->cmd->dvbt2_plp_select.plp_id = 0xff;
					front_end->set_PLP_ID = plp_id;

					return_code = DEMOD_L1_SET_DD_DVBT2_PLP_Select    (front_end->demod, front_end->demod->cmd->dvbt2_plp_select.plp_id , front_end->demod->cmd->dvbt2_plp_select.plp_id_sel_mode);
					if(return_code != NO_DEMOD_ERROR)
					{
						DBB_PRINT ("DEMOD_L1_SET_DD_DVBT2_PLP_Select error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
						return return_code;
					}
					
				}
				else // not auto scan
				{
					front_end->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_DVBT_ONLY_ENABLE;
					return_code = DEMOD_L1_Set_Property(front_end->demod, DEMOD_DD_AUTO_MODE_PROP_CODE);
					if(return_code != NO_DEMOD_ERROR)
					{
						DBB_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
						return return_code;
					}
					DBB_PRINT("front_end->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_DVBT_ONLY_ENABLE\n");
						
				}					
			}
			if (standard == DEMOD_DD_MODE_PROP_MODULATION_DVBT2)
			{
				front_end->demod->prop->dd_dvbt_hp_sel.hierhpsel  	= dvbt_hpSel;
				return_code = DEMOD_L1_Set_Property(front_end->demod, DEMOD_DD_DVBT_HIERARCHY_PROP_CODE);
				if(return_code != NO_DEMOD_ERROR)
				{
					DBB_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
					return return_code;
				}
				//DBB_PRINT ("T2_lock_mode %d\n",T2_lock_mode);

				front_end->demod->prop->dd_dvbt2_lock_mode.lock_mode= T2_lock_mode;
				return_code = DEMOD_L1_Set_Property(front_end->demod, DEMOD_DD_DVBT2_MODE_PROP);
				if(return_code != NO_DEMOD_ERROR)
				{
					DBB_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
					return return_code;
				}
				DBB_PRINT ("T2_lock_mode %d\n",T2_lock_mode);

				front_end->demod->prop->dd_mode.modulation  = DEMOD_DD_MODE_PROP_MODULATION_DVBT2;

				if(front_end->demod->prop->dd_mode.tuneMode != DEMOD_DD_MODE_PROP_TUNEMODE_NORMAL) // autoscan
				{					
					front_end->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_DVBT_DVBT2_ENABLE;
					return_code = DEMOD_L1_Set_Property(front_end->demod, DEMOD_DD_AUTO_MODE_PROP_CODE);
					if(return_code != NO_DEMOD_ERROR)
					{
						DBB_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
						return return_code;
					}
					DBB_PRINT("front_end->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_DVBT_DVBT2_ENABLE\n");
				}
				else
				{
					front_end->demod->prop->dd_mode.modulation  = DEMOD_DD_MODE_PROP_MODULATION_DVBT2;
					front_end->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_DVBT2_ONLY_ENABLE;
					return_code = DEMOD_L1_Set_Property(front_end->demod, DEMOD_DD_AUTO_MODE_PROP_CODE);
					if(return_code != NO_DEMOD_ERROR)
					{
						DBB_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
						return return_code;
					}

					
					front_end->demod->cmd->dvbt2_plp_select.plp_id_sel_mode = DEMOD_DD_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MANUAL;
					front_end->demod->cmd->dvbt2_plp_select.plp_id = (UINT8)plp_id;
					front_end->set_PLP_ID = plp_id;

					return_code = DEMOD_L1_SET_DD_DVBT2_PLP_Select    (front_end->demod, front_end->demod->cmd->dvbt2_plp_select.plp_id , front_end->demod->cmd->dvbt2_plp_select.plp_id_sel_mode);
					if(return_code != NO_DEMOD_ERROR)
					{
						DBB_PRINT ("DEMOD_L1_SET_DD_DVBT2_PLP_Select error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
						return return_code;
					}
				}

			}
			//}
			DBB_PRINT("BW %d KHz\n", ter_bandwidth_KHz);
		}
		break;
	case DEMOD_DD_MODE_PROP_MODULATION_DVBC :
		{
			front_end->demod->prop->dd_clk_mode.clk_mode 	= DEMOD_DD_CLOCK_MODE_PROP_24MHZ;
			front_end->demod->prop->dd_adc_sel.adcClk 		= DEMOD_DD_ADC_PROP_ADCCLK_24MHZ;

			if (front_end->demod->prop->dd_mode.tuneMode == DEMOD_DD_MODE_PROP_TUNEMODE_FIXED_DATA)
			{
//				tempSrdCalc = 42949672960000;  // (40000/4) * 2^32
//				tempSrdCalc = _DEMOD_do_div64_32(tempSrdCalc,symbol_rate_Kbps);
//				tempSrdCalc = tempSrdCalc - 4294967296; // 2^32 = 4294967296

				front_end->demod->cmd->dvbc_sym_rate.sym_rate     = symbol_rate_Kbps;
				front_end->demod->cmd->dvbc_sym_rate.auto_en	= DEMOD_DD_DVBC_SRD_CMD_AUTO_EN_DISABLE;
#if 0
				return_code = DEMOD_L1_SET_DD_SymbolRate_Detect(front_end->demod, front_end->demod->cmd->dvbc_sym_rate.auto_en, symbol_rate_Kbps);
				if(return_code != NO_DEMOD_ERROR)
				{
					DBB_PRINT ("DEMOD_L1_SET_DD_SymbolRate_Detect error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
					return return_code;
				}
#endif
				front_end->demod->prop->dd_constel.constellation = dvb_c_constellation;
				front_end->demod->prop->dd_constel.constel_autodet = DEMOD_DD_CONSTELATION_PROP_AUTO_DET_DISABLE;
				return_code = DEMOD_L1_Set_Property(front_end->demod, DEMOD_DD_CONSTEL_PROP_CODE);
				if(return_code != NO_DEMOD_ERROR)
				{
					DBB_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
					return return_code;
				}
			}
			else
			{
				front_end->demod->cmd->dvbc_sym_rate.sym_rate       = 0;
				front_end->demod->cmd->dvbc_sym_rate.auto_en	= DEMOD_DD_DVBC_SRD_CMD_AUTO_EN_ENABLE;
#if 0
				return_code = DEMOD_L1_SET_DD_SymbolRate_Detect(front_end->demod, front_end->demod->cmd->dvbc_sym_rate.auto_en, symbol_rate_Kbps);
				if(return_code != NO_DEMOD_ERROR)
				{
					DBB_PRINT ("DEMOD_L1_SET_DD_SymbolRate_Detect error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
					return return_code;
				}
#endif
				front_end->demod->prop->dd_constel.constellation = dvb_c_constellation;
				front_end->demod->prop->dd_constel.constel_autodet = DEMOD_DD_CONSTELATION_PROP_AUTO_DET_ENABLE;
				return_code = DEMOD_L1_Set_Property(front_end->demod, DEMOD_DD_CONSTEL_PROP_CODE);
				if(return_code != NO_DEMOD_ERROR)
				{
					DBB_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
					return return_code;
				}

			}

			DBB_PRINT("sr %d kbps, constel %d\n", symbol_rate_Kbps, dvb_c_constellation);
		}
		break;

	case DEMOD_DD_MODE_PROP_MODULATION_DVBC2 :
		{
			DBB_PRINT("NOT SUPPORTED !!\n");
		}
		break;

	default : /* ATV */
		{
			DBB_PRINT("'%d' standard (%s) is not managed by DEMOD_lock_to_carrier\n", standard, DEMOD_L1_API_StandardName(standard));
			return 0;
		  }
		break;
	}
	DBB_PRINT("SET PROP BW AT L2_DVB= %d\n", front_end->demod->prop->dd_mode.bw);
	return_code = DEMOD_L1_Set_Property(front_end->demod, DEMOD_DD_MODE_PROP_CODE);
	if(return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}
	return_code = DEMOD_L1_Set_Property(front_end->demod, DEMOD_DD_CLOCK_MODE_PROP_CODE);
	if(return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}
	
	return_code = DEMOD_L1_Set_Property(front_end->demod, DEMOD_DD_ADC_PROP_CODE);
	if(return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}

	return_code = DEMOD_L1_Set_Property(front_end->demod, DEMOD_DD_IF_FREQ_PROP_CODE);
	if(return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}

	if(front_end->demod->prop->dd_mode.tuneMode != DEMOD_DD_MODE_PROP_TUNEMODE_NORMAL)
	{	
		if(freq <= 870000)
					DEMOD_L0_system_wait(20);
		else
					DEMOD_L0_system_wait(40);
	}
	
	startTime = DEMOD_L0_system_time();

	return_code = DEMOD_L1_SET_DD_Tune  (front_end->demod);
	if(return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L1_SET_DD_Tune error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}
	
	if (standard == DEMOD_DD_MODE_PROP_MODULATION_DVBC)
	{
		return_code = DEMOD_L1_SET_DD_SymbolRate_Detect(front_end->demod, front_end->demod->cmd->dvbc_sym_rate.auto_en, symbol_rate_Kbps);
		if(return_code != NO_DEMOD_ERROR)
		{
			DBB_PRINT ("DEMOD_L1_SET_DD_SymbolRate_Detect error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
			return return_code;
		}
	}

	DBB_PRINT   ("DEMOD_lock_to_carrier 'reset' took %3d ms\n", DEMOD_L0_system_time() - startTime);

	return return_code;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_DVB_AutoModeDetectOn.
 * Set the DVB in Ter Auto Detect mode.
 *
 * @param *front_end 			[IN] LX_DEMOD_L2_Context
 * @return front_end->auto_detect_DVBT_T2
 * @see
 * @author
*/
UINT8  DEMOD_L2_DVB_AutoModeDetectOn         (LX_DEMOD_L2_Context *front_end)
{
  	front_end->auto_detect_DVBT_T2 = 1;
    switch (front_end->demod->standard)
    {
	case DEMOD_DD_MODE_PROP_MODULATION_DVBT    :
	case DEMOD_DD_MODE_PROP_MODULATION_DVBT2   :
		{
			front_end->demod->prop->dd_auto_mode.auto_detect  = DEMOD_DD_AUTO_MODE_PROP_DET_DVBT_DVBT2_ENABLE;
	      	}
		break;

	default :
		{

		}
		break;
    }

  	return DEMOD_L1_Set_Property(front_end->demod, DEMOD_DD_AUTO_MODE_PROP);
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_DVB_AutoModeDetectOff.
 * Set the LGDBB in Ter Auto Detect 'off' mode.
 *
 * @param *front_end 			[IN] LX_DEMOD_L2_Context
 * @return front_end->auto_detect_DVBT_T2
 * @see
 * @author
*/
UINT8  DEMOD_L2_DVB_AutoModeDetectOff      (LX_DEMOD_L2_Context *front_end)
{
  	front_end->auto_detect_DVBT_T2 = 0;
	 switch (front_end->demod->standard)
    {
	case DEMOD_DD_MODE_PROP_MODULATION_DVBT    :
		{
			front_end->demod->prop->dd_auto_mode.auto_detect  = DEMOD_DD_AUTO_MODE_PROP_DET_DVBT_ONLY_ENABLE;
	  	}
		break;
	case DEMOD_DD_MODE_PROP_MODULATION_DVBT2   :
		{
			front_end->demod->prop->dd_auto_mode.auto_detect  = DEMOD_DD_AUTO_MODE_PROP_DET_DVBT2_ONLY_ENABLE;
	  	}
		break;

	default :
		{

		}
		break;
    }

  	return DEMOD_L1_Set_Property(front_end->demod, DEMOD_DD_AUTO_MODE_PROP);
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_DVB_Set_PLP_Select
 *
 * @param *front_end 			[IN] LX_DEMOD_L2_Context
 * @param plp_id 				[IN] UINT8
 * @param plp_id_sel_mode 		[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L2_DVB_Set_PLP_Select(LX_DEMOD_L2_Context *frontend,  UINT8 plp_id, UINT8   plp_id_sel_mode)
{
	UINT8 return_code = NO_DEMOD_ERROR;
/*
	frontend->demod->prop->dd_mode.modulation  = DEMOD_DD_MODE_PROP_MODULATION_DVBT2;
	frontend->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_DVBT2_ONLY_ENABLE;
	return_code = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_AUTO_MODE_PROP_CODE);
	if(return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}
	DEMOD_L0_system_wait(10);
*/
	frontend->set_PLP_ID = plp_id;
//	frontend->demod->cmd->dvbt2_plp_select.plp_id_sel_mode = DEMOD_DD_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MANUAL;
	frontend->demod->cmd->dvbt2_plp_select.plp_id = (UINT8)plp_id;

	return_code = DEMOD_L1_SET_DD_DVBT2_PLP_Select    (frontend->demod, frontend->demod->cmd->dvbt2_plp_select.plp_id , plp_id_sel_mode);

	return return_code;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_DVBC_Set_SymbolRate_Detect
 *
 * @param *front_end 			[IN] LX_DEMOD_L2_Context
 * @param autoEn 				[IN] UINT8
 * @param symbol_rate_Kbps		[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L2_DVBC_Set_SymbolRate_Detect(LX_DEMOD_L2_Context *frontend,  UINT8 autoEn, UINT8   symbol_rate_Kbps)
{
	UINT8 return_code = NO_DEMOD_ERROR;

	frontend->demod->cmd->dvbc_sym_rate.sym_rate     = symbol_rate_Kbps;
	frontend->demod->cmd->dvbc_sym_rate.auto_en	= autoEn;

	if(DEMOD_L1_SET_DD_SymbolRate_Detect(frontend->demod, frontend->demod->cmd->dvbc_sym_rate.auto_en, symbol_rate_Kbps) != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L1_SET_DD_SymbolRate_Detect error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}

	return return_code;

}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_DVB_Get_PLP_ID
 *
 * @param *front_end 			[IN] LX_DEMOD_L2_Context
 * @param *pPlpParams 			[IN] LX_DEMOD_L2_DVB_MULTI_PLP_ID_T
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L2_DVB_Get_PLP_ID   (LX_DEMOD_L2_Context *front_end, LX_DEMOD_L2_DVB_MULTI_PLP_ID_T *pPlpParams)
{
	UINT8	num_cplp = 0;
	UINT8	num_dplp = 0;
	UINT8	index;
	UINT8	PLPCount =0;

	UINT8 return_code;
	DBB_PRINT("DEMOD_L2_DVB_Get_PLP_ID()\n");
	return_code = DEMOD_L1_GET_DD_DVBT2_Status   (front_end->demod);
	if(return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L1_GET_DD_DVBT2_Status error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}
	
	pPlpParams->plpTotalCount = front_end->demod->rsp->dvbt2_status.num_plp;

	if(pPlpParams->plpTotalCount == 0) return ERROR_DEMOD_ERROR;

	for (index = 0; index <	pPlpParams->plpTotalCount; index++) 
	{
		front_end->demod->cmd->dvbt2_plp_id.plp_index = index;
		return_code = DEMOD_L1_GET_DD_DVBT2_PLP_ID(front_end->demod, front_end->demod->cmd->dvbt2_plp_id.plp_index);
//		DBB_PRINT("function call\n");
		if(return_code == NO_DEMOD_ERROR)
		{
//			DBB_PRINT("function call\n");
			DBB_PRINT("front_end->demod->rsp->dvbt2_plp_id.plp_id = 0x%02x\n", front_end->demod->rsp->dvbt2_plp_id.plp_id);
			pPlpParams->plpID[PLPCount] = front_end->demod->rsp->dvbt2_plp_id.plp_id;
			DBB_PRINT("pPlpParams->plpID[%d] = %02x\tindex = %d\n", PLPCount, pPlpParams->plpID[PLPCount], index);
			pPlpParams->plpconf[PLPCount] = front_end->demod->rsp->dvbt2_plp_id.plp_conf;
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
			return return_code;
		}
	}

	DBB_PRINT( "Valid num_plp = %d\n",PLPCount);
	DBB_PRINT("pPlpParams->plpCount_Including_channInfo = %d(num_dplp = %d, num_cplp = %d)\n", pPlpParams->plpCount_Including_channInfo, num_dplp, num_cplp );

	return NO_DEMOD_ERROR;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_DVBT2_Set_BaseAddr_AXI Address for AXI_memory write.
 * Set Set_Base Address for DVBT2/S2 AXI_memory
 *
 * @param *front_end 			[IN] LX_DEMOD_L2_Context
 * @param baseAddr1 			[IN] UINT32
 * @param baseAddr2 			[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L2_DVBT2_Set_BaseAddr_AXI(LX_DEMOD_L2_Context *frontend, UINT32 baseAddr1, UINT32 baseAddr2 )
{
	UINT8 return_code;
	// baseAddr1 : TDI
	// baseAddr2 : DJB
	return_code =  DEMOD_L1_API_DVBT2_BaseAddr_AXI(frontend->demod, baseAddr1, baseAddr2);

	return return_code;

}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_DVB_Set_BaseAddr_AXI Address for AXI_memory write.
 * Set Set_Base Address for DVB AXI_memory
 *
 * @param *front_end 			[IN] LX_DEMOD_L2_Context
 * @param baseAddr1 			[IN] UINT32
 * @param baseAddr2 			[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L2_DVB_Set_BaseAddr_AXI(LX_DEMOD_L2_Context *frontend, UINT32 baseAddr1, UINT32 baseAddr2, UINT32 baseAddr3 )
{
	UINT8 return_code;
	// baseAddr1 : TDI
	// baseAddr2 : DJB
	// baseAddr3 : RISIC
	return_code =  DEMOD_L1_API_DVB_BaseAddr_AXI(frontend->demod, baseAddr1, baseAddr2, baseAddr3);

	return return_code;

}


