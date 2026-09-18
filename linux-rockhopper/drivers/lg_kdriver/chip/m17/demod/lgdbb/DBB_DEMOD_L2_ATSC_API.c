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
**  Name:DBB_DEMOD_L2_ATSC_API.c
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

/* LGFDEMOD API Specific Includes */
/* Before including the headers, define SiLevel and SiTAG */

#include "DBB_DEMOD_L2_ATSC_API.h"               /* Include file for this code */


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_ATSC_SW_Init.
 * software initialization function for VSB/QAM/ISDBT/ATSC3.0
 *  Used to initialize the demodulator
 *
 * @param *front_end 		[IN] LX_DEMOD_L2_Context, a pointer to LX_DEMOD_L2_Context context to be initialized
 * @param demodAdd 		[IN] int, the I2C address of the demod
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8 DEMOD_L2_ATSC_SW_Init  (LX_DEMOD_L2_Context *front_end  , UINT32 demodAdd)
{

	UINT8 return_code = NO_DEMOD_ERROR;

	//DBB_PRINT("DEMOD_L2_ATSC_SW_Init starting...\n");

	/* Pointers initialization */
	front_end->demod     				= &(front_end->demodObj);
	front_end->demod_init_done    		= 0;
	front_end->demod->bIsStandby   	= 0;
	front_end->standard 				= DEMOD_DD_MODE_PROP_MODULATION_VSB;
	front_end->detected_rf 			= 0;
	front_end->centerFrq				= 0;

	front_end->num_PLP_total 		= 0;
	front_end->set_PLP_ID 		= 0;

	/* Calling underlying SW initialization functions */
	return_code =  DEMOD_L1_API_Init (front_end->demod,  demodAdd);


    //DBB_PRINT("DEMOD_L2_ATSC_SW_Init complete\n");

    return return_code;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_ATSC_Set_demod.
 * sets the demod for locking signals
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
UINT8  DEMOD_L2_ATSC_Set_demod   (LX_DEMOD_L2_Context *front_end
								, UINT8  standard
								, UINT32 freq
								, UINT8  tuneMode
								, UINT8  specInv_Auto_Enable
								, UINT8  specInv
								, UINT16  ter_bandwidth_KHz
								, UINT16  plp_id

	)
{
	UINT8 return_code = NO_DEMOD_ERROR;
	UINT32 startTime;           /* startTime is used to measure internal durations. It is set in various places, whenever required                                                */

	DBB_PRINT ("relock to %s at %d KHz\n", DEMOD_L1_API_StandardName(standard), freq);
	front_end->centerFrq= freq;

	front_end->demod->prop->dd_mode.tuneMode            = tuneMode;
	front_end->demod->prop->dd_mode.specinvauto         = specInv_Auto_Enable;
	front_end->demod->prop->dd_mode.specinv               = specInv;
	front_end->demod->prop->dd_mode.modulation          = standard;
	front_end->demod->prop->dd_mode.bw                	= (UINT8)(ter_bandwidth_KHz/1000);

	DBB_PRINT("Tune Mode = %s\n", (front_end->demod->prop->dd_mode.tuneMode == DEMOD_DD_MODE_PROP_TUNEMODE_AUTO) ? "Auto scan" : "Normal");
	DBB_PRINT("Spectrum Inversion Auto  = %s\n", (front_end->demod->prop->dd_mode.specinvauto == DEMOD_DD_MODE_PROP_SPECINV_AUTO) ? "Auto" : "Manual");

	if(front_end->demod->prop->dd_mode.specinvauto != DEMOD_DD_MODE_PROP_SPECINV_AUTO)
	{
		DBB_PRINT("Spectrum = %s\n",( front_end->demod->prop->dd_mode.specinv == DEMOD_DD_MODE_PROP_SPECINV_INVERSION) ? "Inversion" : "Not Inversion");
	}
	DBB_PRINT("Bandwidth = %d [MHz]\n", front_end->demod->prop->dd_mode.bw);

	/* Setting demod for locking on required standard */
	switch (standard)
	{
		case DEMOD_DD_MODE_PROP_MODULATION_ATSC3:
		{
			DBB_PRINT("Modulation  = ATSC3\n");
			front_end->demod->prop->dd_clk_mode.clk_mode	= DEMOD_DD_CLOCK_MODE_PROP_24MHZ;
			front_end->demod->prop->dd_adc_sel.adcClk		= DEMOD_DD_ADC_PROP_ADCCLK_24MHZ;
			front_end->demod->prop->dd_if_freq.if_freq			= DEMOD_DD_IF_FREQ_PROP_IF_FREQ_6MHZ;
			if (plp_id != 256)
			{
				front_end->demod->cmd->atsc3_plp_select.plp_id_sel_mode = DEMOD_DD_ATSC3_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MANUAL;
				front_end->demod->cmd->atsc3_plp_select.plp_id = (UINT8)plp_id;
				front_end->set_PLP_ID = (UINT8)plp_id;
			}
			else
			{
				front_end->demod->cmd->atsc3_plp_select.plp_id_sel_mode = DEMOD_DD_ATSC3_PLP_SELECT_CMD_PLP_ID_SEL_MODE_AUTO;
				front_end->demod->cmd->atsc3_plp_select.plp_id = 0;
				front_end->set_PLP_ID = 0;
			}
			return_code = DEMOD_L1_SET_DD_ATSC3_PLP_Select (front_end->demod, front_end->demod->cmd->atsc3_plp_select.plp_id , front_end->demod->cmd->atsc3_plp_select.plp_id_sel_mode);
			if(return_code != NO_DEMOD_ERROR)
			{
				DBB_PRINT ("DEMOD_L1_SET_DD_ATSC3_PLP_Select  error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
				return return_code;
			}

		}
		break;

	case DEMOD_DD_MODE_PROP_MODULATION_VSB:
		{
			front_end->demod->prop->dd_clk_mode.clk_mode 	= DEMOD_DD_CLOCK_MODE_PROP_24MHZ;
			front_end->demod->prop->dd_adc_sel.adcClk 	  	= DEMOD_DD_ADC_PROP_ADCCLK_24MHZ;
			front_end->demod->prop->dd_if_freq.if_freq 		= DEMOD_DD_IF_FREQ_PROP_IF_FREQ_6MHZ;
		}
		break;
	case DEMOD_DD_MODE_PROP_MODULATION_QAM :
		{
			front_end->demod->prop->dd_clk_mode.clk_mode 	= DEMOD_DD_CLOCK_MODE_PROP_24MHZ;
			front_end->demod->prop->dd_adc_sel.adcClk 	  	= DEMOD_DD_ADC_PROP_ADCCLK_24MHZ;
			front_end->demod->prop->dd_if_freq.if_freq 		= DEMOD_DD_IF_FREQ_PROP_IF_FREQ_6MHZ;
		}
		break;
	case DEMOD_DD_MODE_PROP_MODULATION_ISDBT :
		{
			#ifdef FPGA_CPBOX
			front_end->demod->prop->dd_clk_mode.clk_mode	= DEMOD_DD_CLOCK_MODE_PROP_20MHZ;
			front_end->demod->prop->dd_adc_sel.adcClk 	  	= DEMOD_DD_ADC_PROP_ADCCLK_20MHZ;
			#else
			front_end->demod->prop->dd_clk_mode.clk_mode 	= DEMOD_DD_CLOCK_MODE_PROP_24MHZ;
			front_end->demod->prop->dd_adc_sel.adcClk 	  	= DEMOD_DD_ADC_PROP_ADCCLK_24MHZ;
			#endif
			front_end->demod->prop->dd_if_freq.if_freq 		= DEMOD_DD_IF_FREQ_PROP_IF_FREQ_5MHZ;
		}
		break;


	default : /* ATV */
		{
			DBB_PRINT("'%d' standard (%s) is not supported\n", standard, DEMOD_L1_API_StandardName(standard));
			return 0;
		}
		break;
	}

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

	return_code = DEMOD_L1_SET_DD_Tune (front_end->demod);
	if(return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L1_SET_DD_Tune error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}

	DBB_PRINT   ("DEMOD 'reset' took %3d ms\n", DEMOD_L0_system_time() - startTime);

	return return_code;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_ATSC_Set_PLP_Select.
 * Selects the PLP ID for ATSC3.0
 *
 * @param *front_end 			[IN] LX_DEMOD_L2_Context
 * @param index 				[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L2_ATSC_Set_PLP_Select(LX_DEMOD_L2_Context *frontend, UINT8 plp_id, UINT8 plp_id_sel_mode)
{
	UINT8 return_code;

	return_code =  DEMOD_L1_SET_DD_ATSC3_PLP_Select(frontend->demod, plp_id, plp_id_sel_mode);
	if(return_code == NO_DEMOD_ERROR)
		return_code = DEMOD_L1_SET_DD_Tune (frontend->demod);

	return return_code;

}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_ATSC_Get_PLP_Info.
 * gets the PLP infomations
 *
 * @param *front_end 			[IN] LX_DEMOD_L2_Context
 * @param index 				[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L2_ATSC_Get_PLP_Info   (LX_DEMOD_L2_Context *front_end, UINT8 index, LX_DEMOD_L2_ATSC3_PLP_INFO_T *plpInfo)
{

	UINT8 return_code;

	front_end->demod->cmd->atsc3_plp_info.plp_index = index;
	return_code = DEMOD_L1_GET_DD_ATSC3_PLP_Info(front_end->demod, front_end->demod->cmd->atsc3_plp_info.plp_index);
	if(return_code == NO_DEMOD_ERROR)
	{
		plpInfo->l1b_num_subframes				= front_end->demod->rsp->atsc3_plp_info.l1b_num_subframes;
		plpInfo->l1b_pre_num_symbols				= front_end->demod->rsp->atsc3_plp_info.l1b_pre_num_symbols;
		plpInfo->l1b_first_sub_fft_size				= front_end->demod->rsp->atsc3_plp_info.l1b_first_sub_fft_size;
		plpInfo->l1b_first_num_ofdm_symbols		= front_end->demod->rsp->atsc3_plp_info.l1b_first_num_ofdm_symbols;
		plpInfo->l1b_first_sub_gi					= front_end->demod->rsp->atsc3_plp_info.l1b_first_sub_gi;
		plpInfo->l1b_first_reduce_carr				= front_end->demod->rsp->atsc3_plp_info.l1b_first_reduce_carr;
		plpInfo->l1b_first_sub_scatt_pp				= front_end->demod->rsp->atsc3_plp_info.l1b_first_sub_scatt_pp;
		plpInfo->l1b_first_sub_scatt_pb				= front_end->demod->rsp->atsc3_plp_info.l1b_first_sub_scatt_pb;
		plpInfo->l1b_first_sub_sbs_first				= front_end->demod->rsp->atsc3_plp_info.l1b_first_sub_sbs_first;
		plpInfo->l1b_first_sub_sbs_last				= front_end->demod->rsp->atsc3_plp_info.l1b_first_sub_sbs_last;
		plpInfo->l1d_num_plp						= front_end->demod->rsp->atsc3_plp_info.l1d_num_plp;
		plpInfo->l1d_plp_fec_type					= front_end->demod->rsp->atsc3_plp_info.l1d_plp_fec_type;
		plpInfo->l1d_plp_ti_mode					= front_end->demod->rsp->atsc3_plp_info.l1d_plp_ti_mode;
		plpInfo->l1d_plp_mod						= front_end->demod->rsp->atsc3_plp_info.l1d_plp_mod;
		plpInfo->l1d_plp_cr						= front_end->demod->rsp->atsc3_plp_info.l1d_plp_cr;
		plpInfo->l1d_plp_cti_depth					= front_end->demod->rsp->atsc3_plp_info.l1d_plp_cti_depth;
		plpInfo->l1d_plp_hti_inter_subframe			= front_end->demod->rsp->atsc3_plp_info.l1d_plp_hti_inter_subframe;
		plpInfo->l1d_plp_cti_start_row				= front_end->demod->rsp->atsc3_plp_info.l1d_plp_cti_start_row;
		plpInfo->l1d_plp_hti_num_ti_blocks			= front_end->demod->rsp->atsc3_plp_info.l1d_plp_hti_num_ti_blocks;
		plpInfo->l1d_plp_hti_num_fec_blocks_max	= front_end->demod->rsp->atsc3_plp_info.l1d_plp_hti_num_fec_blocks_max;
		plpInfo->l1d_plp_hti_num_fec_blocks		= front_end->demod->rsp->atsc3_plp_info.l1d_plp_hti_num_fec_blocks;
		plpInfo->l1d_mimo							= front_end->demod->rsp->atsc3_plp_info.l1d_mimo;
		plpInfo->l1d_miso							= front_end->demod->rsp->atsc3_plp_info.l1d_miso;

		plpInfo->bs_pre_str							= front_end->demod->rsp->atsc3_plp_info.bs_pre_str;
		plpInfo->bs_l1b_mod							= front_end->demod->rsp->atsc3_plp_info.bs_l1b_mod;

	}
	else
	{
		return return_code;
	}

	DBB_PRINT( "Plp index = %d\n", index);

	return NO_DEMOD_ERROR;

}



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_ATSC_Get_PLP_ID.
 * gets the PLP infomations
 *
 * @param *front_end 			[IN] LX_DEMOD_L2_Context
 * @param *pPlpParams 		[OUT] LX_DEMOD_L2_ATSC3_MULTI_PLP_ID_T
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L2_ATSC_Get_PLP_ID   (LX_DEMOD_L2_Context *front_end, LX_DEMOD_L2_ATSC3_MULTI_PLP_ID_T *pPlpParams)
{
//	UINT8	num_plp = 0;
	UINT8	index;
	UINT8	PLPCount =0;

	UINT8 return_code;

	for (index = 0; index <64; index++)
	{
		front_end->demod->cmd->atsc3_plp_id.plp_index = index;
		return_code = DEMOD_L1_GET_DD_ATSC3_PLP_ID(front_end->demod, front_end->demod->cmd->atsc3_plp_id.plp_index);
		if(return_code == NO_DEMOD_ERROR)
		{
			if((front_end->demod->rsp->atsc3_plp_id.l1d_plp_id_flag == 1) && (front_end->demod->rsp->atsc3_plp_id.l1d_slt_flag == 1))
			{
				pPlpParams->plpID[PLPCount] = index;
				PLPCount++;

			}
			else
				continue;
		}
		else
		{
			return return_code;
		}
	}

		pPlpParams->plpCount_Including_channInfo = PLPCount;
		DBB_PRINT( "Valid num_plp = %d\n",PLPCount);

	return NO_DEMOD_ERROR;

}


/**/



