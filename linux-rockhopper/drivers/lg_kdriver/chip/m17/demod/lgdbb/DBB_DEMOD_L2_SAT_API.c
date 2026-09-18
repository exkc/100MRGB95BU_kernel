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
**  Name:DBB_DEMOD_L2_SAT_API.c
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

 /** @file LG_DEMOD_L2_API.c
  *
  *  LG Firmware Demod functions.
  *
  *  @author	 Jeongpil Yun(jeongpill.yun@lge.com)
  *  @version	 0.1
  *  @date	 2015.1.27
  *  @note
  *  @see
  */

/* LGFDEMOD API Specific Includes */
/* Before including the headers, define SiLevel and SiTAG */

#include "DBB_DEMOD_L2_SAT_API.h"               /* Include file for this code */

/*****************************************************************************************/
/*               LGDBB demodulator API functions (demod and tuner)                      */
/*****************************************************************************************/


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_SAT_SW_Init.
 * software initialization function for DVBS/DVBS2
 *  Used to initialize the demodulator and tuner structures
 *
 * @param *front_end 		[IN] LX_DEMOD_L2_Context, a pointer to LX_DEMOD_L2_Context context to be initialized
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/

UINT8  DEMOD_L2_SAT_SW_Init        (LX_DEMOD_L2_Context *front_end)
{
	UINT8 return_code = NO_DEMOD_ERROR;
	DBB_PRINT("DEMOD_L2_SW_Init starting...\n");

#ifdef DEMOD_SATELLITE_FRONT_END
	front_end->satellite_init_done       = 0;
	front_end->auto_detect_SAT     = 1;

	front_end->satellite_blind_search = 0;	//lgit
	front_end->satellite_spectrum_inversion = 0;
#endif

    DBB_PRINT("DEMOD_L2_EVB_SW_Init complete\n");
    return return_code;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_SAT_set_demod.
 * sets the demod for locking the satellite signals
 *
 * @param *front_end 			[IN] LX_DEMOD_L2_Context
 * @param standard 			[IN] UINT8
 * @param freq 				[IN] UINT32
 * @param tuneMode 			[IN] UINT8
 * @param specInv_Auto_Enable 	[IN] UINT8
 * @param specInv 			[IN] UINT8
 * @param sat_bandwidth_KHz 	[IN] UINT16
 * @param opratingMode 		[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8   DEMOD_L2_SAT_set_demod   (LX_DEMOD_L2_Context *front_end
								, UINT8 standard
								, UINT32 freq
								, UINT8 tuneMode
								, UINT8 specInv_Auto_Enable
								, UINT8 specInv
								, UINT16 symbol_rate_Kbps
								, UINT8 operatingMode
	)
{
	UINT8 return_code = NO_DEMOD_ERROR;
	UINT32  startTime;           /* startTime is used to measure internal durations. It is set in various places, whenever required                                                */

	front_end->demod->prop->dd_mode.tuneMode            = tuneMode;
	front_end->demod->prop->dd_mode.specinvauto         = specInv_Auto_Enable;
	front_end->demod->prop->dd_mode.specinv             = specInv;
	front_end->demod->prop->dd_mode.modulation          = DEMOD_DD_MODE_PROP_MODULATION_DVBS;//standard;
	front_end->demod->prop->dd_mode.bw                	= (UINT8) symbol_rate_Kbps;
	front_end->demod->prop->dd_dvbs_opm_sel.opmSel		= operatingMode;
	front_end->demod->prop->dd_if_freq.if_freq			= DEMOD_DD_IF_FREQ_PROP_IF_FREQ_0MHZ;

#ifdef FPGA_CPBOX
	front_end->demod->prop->dd_clk_mode.clk_mode 	= DEMOD_DD_CLOCK_MODE_PROP_15P2MHZ;
	front_end->demod->prop->dd_adc_sel.adcClk 		= DEMOD_DD_ADC_PROP_ADCCLK_60P8MHZ;

#else
	front_end->demod->prop->dd_clk_mode.clk_mode 	= DEMOD_DD_CLOCK_MODE_PROP_24MHZ;
	//front_end->demod->prop->dd_adc_sel.adcClk 		= DEMOD_DD_ADC_PROP_ADCCLK_24MHZ;
	front_end->demod->prop->dd_adc_sel.adcClk 		= DEMOD_DD_ADC_PROP_ADCCLK_124MHZ;
#endif

	DBB_PRINT ("lock to %s at %d KHz\n", DEMOD_L1_API_StandardName(standard), freq);
	DBB_PRINT ("symbol_rate_Kbps %d KHz\n", symbol_rate_Kbps);

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

	return_code = DEMOD_L1_Set_Property(front_end->demod, DEMOD_DD_DVBS_OPMSEL_PROP);
	if(return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}

	startTime = DEMOD_L0_system_time();

	return_code = DEMOD_L1_SET_DD_Tune(front_end->demod);
	if(return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}
	DBB_PRINT   ("DEMOD_lock_to_carrier 'reset' took %3d ms\n", DEMOD_L0_system_time() - startTime);

/*
	if(front_end->demod->prop->dd_mode.tuneMode != DEMOD_DD_MODE_PROP_TUNEMODE_NORMAL)
	{
 			DEMOD_L0_system_wait(30);
	}
	else
	{
			DEMOD_L0_system_wait(30);
	}
*/
	DEMOD_L0_system_wait(30);

	/* Setting demod for locking on required standard */
	switch (standard)
	{
		case DEMOD_DD_MODE_PROP_MODULATION_DVBS :
		case DEMOD_DD_MODE_PROP_MODULATION_DVBS2:
			{
#if 1
				//if(front_end->demod->prop->dd_dvbs_opm_sel.opmSel == DEMOD_DD_DVBS_OPM_SEL_PROP_BLIND_LOCK_MODE)
				if(front_end->demod->prop->dd_dvbs_opm_sel.opmSel == DEMOD_DD_DVBS_OPM_SEL_PROP_NORMAL_MODE)
					front_end->demod->cmd->dvbs_sym_rate.srd_en_s       = DEMOD_DD_DVBC_SRD_CMD_AUTO_EN_DISABLE;
				else if(front_end->demod->prop->dd_dvbs_opm_sel.opmSel == DEMOD_DD_DVBS_OPM_SEL_PROP_BLIND_LOCK_MODE)
					front_end->demod->cmd->dvbs_sym_rate.srd_en_s       = DEMOD_DD_DVBC_SRD_CMD_AUTO_EN_DISABLE;// = DEMOD_DD_DVBC_SRD_CMD_AUTO_EN_ENABLE;
				else
					front_end->demod->cmd->dvbs_sym_rate.srd_en_s       = DEMOD_DD_DVBC_SRD_CMD_AUTO_EN_ENABLE;

				front_end->demod->cmd->dvbs_sym_rate.sym_rate        =	symbol_rate_Kbps ;

				if (front_end->auto_detect_SAT)
				{
					DBB_PRINT("DVB-S/S2 auto detect enable\n");
					front_end->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_DVBS_DVBS2_ENABLE;

					return_code = DEMOD_L1_Set_Property(front_end->demod, DEMOD_DD_AUTO_MODE_PROP_CODE);
					if(return_code != NO_DEMOD_ERROR)
					{
						DBB_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
						return return_code;
					}
				}
				else
				{
					DBB_PRINT("DVB-S/S2 auto detect disable\n");
					if (standard == DEMOD_DD_MODE_PROP_MODULATION_DVBS )
					{
						front_end->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_DVBS_ONLY_ENABLE;
					}
					else if(standard == DEMOD_DD_MODE_PROP_MODULATION_DVBS2)
					{
						front_end->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_DVBS2_ONLY_ENABLE;
					}
					return_code = DEMOD_L1_Set_Property(front_end->demod, DEMOD_DD_AUTO_MODE_PROP_CODE);
					if(return_code != NO_DEMOD_ERROR)
					{
						DBB_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
						return return_code;
					}
				}

				return_code = DEMOD_L1_SET_DD_SymbolRate_Detect(front_end->demod, front_end->demod->cmd->dvbs_sym_rate.srd_en_s, symbol_rate_Kbps);

				if(return_code != NO_DEMOD_ERROR)
				{
					DBB_PRINT ("DEMOD_L1_SET_DD_SymbolRate_Detect error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
					return return_code;
				}
				DBB_PRINT("sr %d bps\n", symbol_rate_Kbps);
#endif
			}
			break;

		default : /* ATV */
			{
				DBB_PRINT("'%d' standard (%s) is not managed by DEMOD_lock_to_carrier\n", standard, DEMOD_L1_API_StandardName(standard));
				return 0;
			 }
			break;
	}

	return return_code;
}


/***********************************************************************************************************************
  DEMOD_L2_SAT_send_diseqc_sequence
  Use:      DiSEqC sequence preparation function
            Used to prepare a DiSEqC sequence, checking the bus readiness and preparing all registers
  Returns:      0 if OK
  Parameter:  *front_end, the front-end handle
  Parameter:   sequence_length  the number of bytes to send
  Parameter:   sequenceBuffer   a buffer containing the DiSeqEc bytes
  Parameter:   cont_tone  a flag for continuous tone control: 0 = OFF, 1 = ON. When set to ON, a continuous tone is present before and after the message or the sequence of messages and/or tone burst.
  Parameter:   tone_burst a flag for tone burst control: 0 = OFF, 1 = ON. Used to send a Tone Burst sequence.
  Parameter:   burst_sel  a flag for tone burst selection: 0 = SA, 1 = SB. Selects which satellite is selected in the Tone Burst sequence.
  Parameter:   end_seq    a flag for end of sequence control: 0 = NOT_END, 1 = END. When set to END, Diseqc sequence is resumed after the current message. When set to NOT_END, current message is not the end of the full sequence. It's used in the case of sequence composed of repeated messages
 ***********************************************************************************************************************/
UINT8  DEMOD_L2_SAT_send_diseqc_sequence(LX_DEMOD_L2_Context *front_end, UINT8 sequence_length, UINT8 *sequenceBuffer, UINT8 cont_tone, UINT8 tone_burst, UINT8 burst_sel, UINT8 repeatEn)
{
	UINT8 i = 0;
	UINT8   msg_byte1;
	UINT8   msg_byte2;
	UINT8   msg_byte3;
	UINT8   msg_byte4;
	UINT8   msg_byte5;
	UINT8   msg_byte6;

	
	if (i<sequence_length) { msg_byte1 = sequenceBuffer[i++];} else {msg_byte1 = 0x00;}
	if (i<sequence_length) { msg_byte2 = sequenceBuffer[i++];} else {msg_byte2 = 0x00;}
	if (i<sequence_length) { msg_byte3 = sequenceBuffer[i++];} else {msg_byte3 = 0x00;}
	if (i<sequence_length) { msg_byte4 = sequenceBuffer[i++];} else {msg_byte4 = 0x00;}
	if (i<sequence_length) { msg_byte5 = sequenceBuffer[i++];} else {msg_byte5 = 0x00;}
	if (i<sequence_length) { msg_byte6 = sequenceBuffer[i++];} else {msg_byte6 = 0x00;}

	if(sequence_length >= 3)
	{
		front_end->demod->cmd->dd_diseqc_send.diseqc_en  = DEMOD_DD_DISEQC_SEND_CMD_DISEQC_ENABLE;
		front_end->demod->cmd->dd_diseqc_send.msg_length = sequence_length - 3;
	}
	else
	{
		front_end->demod->cmd->dd_diseqc_send.diseqc_en  = DEMOD_DD_DISEQC_SEND_CMD_DISEQC_DISABLE;
		front_end->demod->cmd->dd_diseqc_send.msg_length = 0;
	}

	front_end->demod->cmd->dd_diseqc_send.send_framing  = msg_byte1;
	front_end->demod->cmd->dd_diseqc_send.send_address  = msg_byte2;
	front_end->demod->cmd->dd_diseqc_send.send_command  = msg_byte3;
	front_end->demod->cmd->dd_diseqc_send.send_data0  = msg_byte4;
	front_end->demod->cmd->dd_diseqc_send.send_data1  = msg_byte5;
	front_end->demod->cmd->dd_diseqc_send.send_data2  = msg_byte6;
	front_end->demod->cmd->dd_diseqc_send.cont_tone  = (cont_tone == 1) ? DEMOD_DD_DISEQC_SEND_CMD_CONT_TONE_ENABLE : DEMOD_DD_DISEQC_SEND_CMD_CONT_TONE_DISABLE ;
	front_end->demod->cmd->dd_diseqc_send.tone_burst =  (tone_burst == 1) ? DEMOD_DD_DISEQC_SEND_CMD_TONE_BURST_ENABLE : DEMOD_DD_DISEQC_SEND_CMD_TONE_BURST_DISABLE;
	front_end->demod->cmd->dd_diseqc_send.burst_sel  =  (burst_sel == 1) ? DEMOD_DD_DISEQC_SEND_CMD_BURST_SEL_MODULATED : DEMOD_DD_DISEQC_SEND_CMD_BURST_SEL_UNMODUALTED;
/*
	DBB_PRINT ("dd_diseqc_send 		diseqc_en 0x%02x\n", front_end->demod->cmd->dd_diseqc_send.diseqc_en);
	DBB_PRINT ("dd_diseqc_send		tone_burst 0x%02x\n", front_end->demod->cmd->dd_diseqc_send.tone_burst);
	DBB_PRINT ("dd_diseqc_send		cont_tone 0x%02x\n", front_end->demod->cmd->dd_diseqc_send.cont_tone);
	DBB_PRINT ("dd_diseqc_send 		burst_sel 0x%02x\n", front_end->demod->cmd->dd_diseqc_send.burst_sel);
	DBB_PRINT ("dd_diseqc_send 		msg_length 0x%02x\n", front_end->demod->cmd->dd_diseqc_send.msg_length);
	DBB_PRINT ("dd_diseqc_send 		send_framing 0x%02x\n", front_end->demod->cmd->dd_diseqc_send.send_framing);
	DBB_PRINT ("dd_diseqc_send 		send_address 0x%02x\n", front_end->demod->cmd->dd_diseqc_send.send_address);
	DBB_PRINT ("dd_diseqc_send 		send_command 0x%02x\n", front_end->demod->cmd->dd_diseqc_send.send_command);
	DBB_PRINT ("dd_diseqc_send 		send_data0 0x%02x\n", front_end->demod->cmd->dd_diseqc_send.send_data0);
	DBB_PRINT ("dd_diseqc_send 		send_data1 0x%02x\n", front_end->demod->cmd->dd_diseqc_send.send_data1);
	DBB_PRINT ("dd_diseqc_send 		send_data2 0x%02x\n", front_end->demod->cmd->dd_diseqc_send.send_data2);
*/

	return DEMOD_L1_SET_DD_DISEQC_Send(front_end->demod,
													front_end->demod->cmd->dd_diseqc_send.diseqc_en,
													front_end->demod->cmd->dd_diseqc_send.tone_burst,
													front_end->demod->cmd->dd_diseqc_send.cont_tone,
													front_end->demod->cmd->dd_diseqc_send.burst_sel,
													front_end->demod->cmd->dd_diseqc_send.msg_length,
													front_end->demod->cmd->dd_diseqc_send.send_framing,
													front_end->demod->cmd->dd_diseqc_send.send_address,
													front_end->demod->cmd->dd_diseqc_send.send_command,
													front_end->demod->cmd->dd_diseqc_send.send_data0,
													front_end->demod->cmd->dd_diseqc_send.send_data1,
													front_end->demod->cmd->dd_diseqc_send.send_data2 );




}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_SatAutoModeDetectOn.
 * Set the DBB in Sat Auto Detect mode.
 *
 * @param *front_end 			[IN] LX_DEMOD_L2_Context
 * @return front_end->auto_detect_SAT
 * @see
 * @author
*/
UINT8  DEMOD_L2_SAT_AutoModeDetectOn         (LX_DEMOD_L2_Context *front_end)
{
    front_end->auto_detect_SAT = 1;
    switch (front_end->demod->standard)
    {
	case DEMOD_DD_MODE_PROP_MODULATION_DVBS    :
	case DEMOD_DD_MODE_PROP_MODULATION_DVBS2   :
		{
	       	front_end->demod->prop->dd_auto_mode.auto_detect  = DEMOD_DD_AUTO_MODE_PROP_DET_DVBS_DVBS2_ENABLE;
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
 * DEMOD_L2_SatAutoModeDetectOff.
 * Set the DBB in Sat Auto Detect 'off' mode.
 *
 * @param *front_end 			[IN] LX_DEMOD_L2_Context
 * @return : front_end->auto_detect_SAT
 * @see
 * @author
*/
UINT8  DEMOD_L2_SAT_AutoModeDetectOff      (LX_DEMOD_L2_Context *front_end)
{
  	front_end->auto_detect_SAT = 0;
	 switch (front_end->demod->standard)
    {
	case DEMOD_DD_MODE_PROP_MODULATION_DVBS    :
		{
	       	front_end->demod->prop->dd_auto_mode.auto_detect  = DEMOD_DD_AUTO_MODE_PROP_DET_DVBS_ONLY_ENABLE;
	    }
		break;
	case DEMOD_DD_MODE_PROP_MODULATION_DVBS2   :
		{
	       	front_end->demod->prop->dd_auto_mode.auto_detect  = DEMOD_DD_AUTO_MODE_PROP_DET_DVBS2_ONLY_ENABLE;
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
 * DEMOD_L2_SAT_Blind_Info.
 * software initialization function for DVBT/DVBT2/DVBC/DVBC2/DVBS/DVBS2
 *  Used to initialize the demodulator and tuner structures
 *
 * @param *front_end 		[IN] LX_DEMOD_L2_Context, a pointer to LX_DEMOD_L2_Context context to be initialized
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/

UINT8  DEMOD_L2_SAT_Blind_Info        (LX_DEMOD_L2_Context *front_end)
{
	UINT8 return_code = NO_DEMOD_ERROR;

	return_code = DEMOD_L1_GET_DD_SIGSRCH_INFO(front_end->demod);
	if(return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L1_GET_DD_SIGSRCH_INFO error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}
    return return_code;
}



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_SAT_Blind_Status.
 * software initialization function for DVBT/DVBT2/DVBC/DVBC2/DVBS/DVBS2
 *  Used to initialize the demodulator and tuner structures
 *
 * @param *front_end 		[IN] LX_DEMOD_L2_Context, a pointer to LX_DEMOD_L2_Context context to be initialized
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/

UINT8  DEMOD_L2_SAT_Blind_Status        (LX_DEMOD_L2_Context *front_end)
{
	UINT8 return_code = NO_DEMOD_ERROR;

	return_code = DEMOD_L1_GET_DD_BLIND_Status(front_end->demod);
	if(return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L1_GET_DD_BLIND_Status error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}
	DBB_PRINT("Symbol_rate	 : %d\n", front_end->demod->rsp->blind_status.symRate);
    return return_code;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_SAT_Blind_Init.
 * software initialization function for DVBT/DVBT2/DVBC/DVBC2/DVBS/DVBS2
 *  Used to initialize the demodulator and tuner structures
 *
 * @param *front_end 		[IN] LX_DEMOD_L2_Context, a pointer to LX_DEMOD_L2_Context context to be initialized
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/

UINT8  DEMOD_L2_SAT_Blind_Init        (LX_DEMOD_L2_Context *front_end, UINT32 startFreq, UINT32 endFreq)
{
	UINT8 return_code = NO_DEMOD_ERROR;

	startFreq = 970000;
	DBB_PRINT ("DEMOD_L2_SAT_Blind_Init startFreq : %d, endFreq : %d\n", startFreq, endFreq);
	return_code = DEMOD_L1_GET_DD_BLIND_Init(front_end->demod, startFreq, endFreq);
	if(return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L1_GET_DD_BLIND_Init error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}
    return return_code;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_SAT_Blind_End.
 * software initialization function for DVBT/DVBT2/DVBC/DVBC2/DVBS/DVBS2
 *  Used to initialize the demodulator and tuner structures
 *
 * @param *front_end 		[IN] LX_DEMOD_L2_Context, a pointer to LX_DEMOD_L2_Context context to be initialized
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/

UINT8  DEMOD_L2_SAT_Blind_End        (LX_DEMOD_L2_Context *front_end)
{
	UINT8 return_code = NO_DEMOD_ERROR;

	return_code = DEMOD_L1_GET_DD_BLIND_End(front_end->demod);
	if(return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L1_GET_DD_BLIND_End error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}
    return return_code;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_SAT_Blind_FoundInfo.
 * software initialization function for DVBT/DVBT2/DVBC/DVBC2/DVBS/DVBS2
 *  Used to initialize the demodulator and tuner structures
 *
 * @param *front_end 		[IN] LX_DEMOD_L2_Context, a pointer to LX_DEMOD_L2_Context context to be initialized
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/

UINT8  DEMOD_L2_SAT_Blind_FoundInfo        (LX_DEMOD_L2_Context *front_end)
{
	UINT8 return_code = NO_DEMOD_ERROR;

	return_code = DEMOD_L1_GET_DD_BLIND_FoundInfo(front_end->demod);
	if(return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L2_SAT_Blind_FoundInfo error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}
    return return_code;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_SAT_Blind_SymbolRate_Detect.
 * software initialization function for DVBT/DVBT2/DVBC/DVBC2/DVBS/DVBS2
 *  Used to initialize the demodulator and tuner structures
 *
 * @param *front_end 		[IN] LX_DEMOD_L2_Context, a pointer to LX_DEMOD_L2_Context context to be initialized
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/

UINT8  DEMOD_L2_SAT_Blind_SymbolRate_Detect        (LX_DEMOD_L2_Context *front_end)
{
	UINT8 return_code = NO_DEMOD_ERROR;

	return_code = DEMOD_L1_SET_DD_SymbolRate_Detect(front_end->demod, DEMOD_DD_DVBC_SRD_CMD_AUTO_EN_ENABLE, front_end->demod->rsp->dd_sigsrch_info.bw_idx);
	if(return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L1_SET_DD_SymbolRate_Detect error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}
    return return_code;
}
