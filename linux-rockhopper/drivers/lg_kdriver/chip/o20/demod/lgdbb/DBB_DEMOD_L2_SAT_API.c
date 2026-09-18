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
#define DEMOD_TAG "[L2.SAT] "

#include <DBB_DEMOD_typedefs.h>
#include <demod_util.h>

#include <DBB_DEMOD_L2_SAT_API.h>

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_XTENSA)

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
#include <asm/div64.h> //do_div
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
#include <math.h>
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)

#endif

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
 * @param *frontend 	[IN] LX_DEMOD_L2_Context, a pointer to LX_DEMOD_L2_Context context to be initialized
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/

int DEMOD_L2_SAT_SW_Init (LX_DEMOD_L2_Context * frontend, UINT32 demodAddr)
{
	int retc = NO_DEMOD_ERROR;

	frontend->satellite_init_done		= 0;
	frontend->auto_detect_SAT		= 1;

	frontend->satellite_blind_search	= 0;	//lgit
	frontend->satellite_spectrum_inversion = 0;

	/* Calling underlying SW initialization functions */
	retc =  DEMOD_L1_API_Init (frontend->demod,  demodAddr);
	if (NO_DEMOD_ERROR != retc) {
		DEMOD_ERROR("DEMOD_L1_API_Init() error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
	}
	return retc;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_SAT_set_demod.
 * sets the demod for locking the satellite signals
 *
 * @param *frontend 		[IN] LX_DEMOD_L2_Context
 * @param standard 		[IN] UINT8
 * @param freq 			[IN] UINT32
 * @param tuneMode 		[IN] UINT8
 * @param specInv_Auto_Enable 	[IN] UINT8
 * @param specInv 		[IN] UINT8
 * @param sat_bandwidth_KHz 	[IN] UINT16
 * @param opratingMode 		[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_SAT_set_demod (LX_DEMOD_L2_Context * frontend
							, UINT8 standard
							, UINT32 freq
							, UINT8 tuneMode
							, UINT8 specInv_Auto_Enable
							, UINT8 specInv
							, UINT16 symbol_rate_Kbps
							, UINT8 operatingMode
)
{
	int retc = NO_DEMOD_ERROR;
	UINT32  startTime;           /* startTime is used to measure internal durations. It is set in various places, whenever required                                                */

	frontend->demod->prop->dd_mode.tuneMode	= tuneMode;
	frontend->demod->prop->dd_mode.specinvauto	= specInv_Auto_Enable;
	frontend->demod->prop->dd_mode.specinv		= specInv;
	frontend->demod->prop->dd_mode.modulation	= DEMOD_DD_MODE_PROP_MODULATION_DVBS;//standard;
	frontend->demod->prop->dd_mode.bw		= (UINT8) symbol_rate_Kbps;
	frontend->demod->prop->dd_dvbs_opm_sel.opmSel	= operatingMode;
	frontend->demod->prop->dd_if_freq.if_freq	= DEMOD_DD_IF_FREQ_PROP_IF_FREQ_0MHZ;

#if defined(DEMOD_CONFIG_CROSS_PLATFORM)
#ifdef DEMOD_DD_CLOCK_MODE_PROP
	frontend->demod->prop->dd_clk_mode.clk_mode	= DEMOD_DD_ADC_PROP_ADCCLK_80MHZ;
#endif
	frontend->demod->prop->dd_adc_sel.adcClk	= DEMOD_DD_ADC_PROP_ADCCLK_80MHZ;
#else
#ifdef DEMOD_DD_CLOCK_MODE_PROP
	frontend->demod->prop->dd_clk_mode.clk_mode	= DEMOD_DD_CLOCK_MODE_PROP_124MHZ;
#endif
	frontend->demod->prop->dd_adc_sel.adcClk	= DEMOD_DD_ADC_PROP_ADCCLK_124MHZ;
#endif

	DEMOD_NOTI("[DEMOD_API] Lock to %s at %d KHz\n", DEMOD_L1_API_StandardName(standard), freq);
	DEMOD_NOTI("[DEMOD_API] Symbol Rate = %d Kbps\n", symbol_rate_Kbps);

	retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_MODE_PROP_CODE);
	if(retc != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_Set_Property(DEMOD_DD_MODE_PROP_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

#ifdef DEMOD_DD_CLOCK_MODE_PROP
	retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_CLOCK_MODE_PROP_CODE);
	if(retc != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_Set_Property(DEMOD_DD_CLOCK_MODE_PROP_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}
#endif

	retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_ADC_PROP_CODE);
	if(retc != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_Set_Property(DEMOD_DD_ADC_PROP_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

	retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_IF_FREQ_PROP_CODE);
	if(retc != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_Set_Property(DEMOD_DD_IF_FREQ_PROP_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

	retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_DVBS_OPMSEL_PROP);
	if(retc != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_Set_Property(DEMOD_DD_DVBS_OPMSEL_PROP) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

//	DEMOD_L2_Set_SoftRst(frontend, 1, 1, 1, 1, 1, 1, 1);
//	DEMOD_L2_Set_SoftRst(frontend, 1, 0, 0, 0, 0, 0, 0);
//	DEMOD_L0_system_wait(100);

	startTime = DEMOD_L0_system_time();

	retc = DEMOD_L1_SET_DD_Tune(frontend->demod);
	if(retc != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_SET_DD_Tune() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}
	DEMOD_NOTI("[DEMOD_API] Reset took %3d ms\n", DEMOD_L0_system_time() - startTime);

	/* Setting demod for locking on required standard */
	switch (standard)
	{
		case DEMOD_DD_MODE_PROP_MODULATION_DVBS :
		case DEMOD_DD_MODE_PROP_MODULATION_DVBS2:
			{
#if 1
				//if(frontend->demod->prop->dd_dvbs_opm_sel.opmSel == DEMOD_DD_DVBS_OPM_SEL_PROP_BLIND_LOCK_MODE)
				if(frontend->demod->prop->dd_dvbs_opm_sel.opmSel == DEMOD_DD_DVBS_OPM_SEL_PROP_NORMAL_MODE)
					frontend->demod->cmd->dvbs_sym_rate.srd_en_s       = DEMOD_DD_DVBC_SRD_CMD_AUTO_EN_DISABLE;
				else if(frontend->demod->prop->dd_dvbs_opm_sel.opmSel == DEMOD_DD_DVBS_OPM_SEL_PROP_BLIND_LOCK_MODE)
					frontend->demod->cmd->dvbs_sym_rate.srd_en_s       = DEMOD_DD_DVBC_SRD_CMD_AUTO_EN_DISABLE;// = DEMOD_DD_DVBC_SRD_CMD_AUTO_EN_ENABLE;
				else
					frontend->demod->cmd->dvbs_sym_rate.srd_en_s       = DEMOD_DD_DVBC_SRD_CMD_AUTO_EN_ENABLE;

				frontend->demod->cmd->dvbs_sym_rate.sym_rate =	symbol_rate_Kbps ;

				if (frontend->auto_detect_SAT)
				{
					DEMOD_NOTI("[DEMOD_API] DVB-S/S2 auto detect Enable\n");
					frontend->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_DVBS_DVBS2_ENABLE;

					retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_AUTO_MODE_PROP_CODE);
					if(retc != NO_DEMOD_ERROR)
					{
						DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_Set_Property(DEMOD_DD_AUTO_MODE_PROP_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
						return retc;
					}
				}
				else
				{
					DEMOD_NOTI("[DEMOD_API] DVB-S/S2 auto detect Disable\n");
					if (standard == DEMOD_DD_MODE_PROP_MODULATION_DVBS )
					{
						frontend->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_DVBS_ONLY_ENABLE;
					}
					else if(standard == DEMOD_DD_MODE_PROP_MODULATION_DVBS2)
					{
						frontend->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_DVBS2_ONLY_ENABLE;
					}
					retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_AUTO_MODE_PROP_CODE);
					if(retc != NO_DEMOD_ERROR)
					{
						DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_Set_Property(DEMOD_DD_AUTO_MODE_PROP_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
						return retc;
					}
				}

				retc = DEMOD_L1_SET_DD_SymbolRate_Detect(frontend->demod, frontend->demod->cmd->dvbs_sym_rate.srd_en_s, symbol_rate_Kbps);

				if(retc != NO_DEMOD_ERROR)
				{
					DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_SET_DD_SymbolRate_Detect() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
					return retc;
				}
				DEMOD_NOTI("[DEMOD_API] Symbol Rate = %d Kbps\n", symbol_rate_Kbps);
#endif
			}
			break;

		default : /* ATV */
			{
				DEMOD_NOTI("[DEMOD_API] '%d' standard (%s) is not managed by DEMOD_lock_to_carrier\n", standard, DEMOD_L1_API_StandardName(standard));
				return 0;
			 }
			break;
	}

	return retc;
}


/***********************************************************************************************************************
  DEMOD_L2_SAT_send_diseqc_sequence
  Use:      DiSEqC sequence preparation function
            Used to prepare a DiSEqC sequence, checking the bus readiness and preparing all registers
  Returns:      0 if OK
  Parameter:  *frontend, the front-end handle
  Parameter:   sequence_length  the number of bytes to send
  Parameter:   sequenceBuffer   a buffer containing the DiSeqEc bytes
  Parameter:   cont_tone  a flag for continuous tone control: 0 = OFF, 1 = ON. When set to ON, a continuous tone is present before and after the message or the sequence of messages and/or tone burst.
  Parameter:   tone_burst a flag for tone burst control: 0 = OFF, 1 = ON. Used to send a Tone Burst sequence.
  Parameter:   burst_sel  a flag for tone burst selection: 0 = SA, 1 = SB. Selects which satellite is selected in the Tone Burst sequence.
  Parameter:   end_seq    a flag for end of sequence control: 0 = NOT_END, 1 = END. When set to END, Diseqc sequence is resumed after the current message. When set to NOT_END, current message is not the end of the full sequence. It's used in the case of sequence composed of repeated messages
 ***********************************************************************************************************************/
int DEMOD_L2_SAT_send_diseqc_sequence(LX_DEMOD_L2_Context * frontend, UINT8 sequence_length, UINT8 *sequenceBuffer, UINT8 cont_tone, UINT8 tone_burst, UINT8 burst_sel, UINT8 repeatEn)
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
		frontend->demod->cmd->dd_diseqc_send.diseqc_en  = DEMOD_DD_DISEQC_SEND_CMD_DISEQC_ENABLE;
		frontend->demod->cmd->dd_diseqc_send.msg_length = sequence_length - 3;
	}
	else
	{
		frontend->demod->cmd->dd_diseqc_send.diseqc_en  = DEMOD_DD_DISEQC_SEND_CMD_DISEQC_DISABLE;
		frontend->demod->cmd->dd_diseqc_send.msg_length = 0;
	}

	frontend->demod->cmd->dd_diseqc_send.send_framing  = msg_byte1;
	frontend->demod->cmd->dd_diseqc_send.send_address  = msg_byte2;
	frontend->demod->cmd->dd_diseqc_send.send_command  = msg_byte3;
	frontend->demod->cmd->dd_diseqc_send.send_data0  = msg_byte4;
	frontend->demod->cmd->dd_diseqc_send.send_data1  = msg_byte5;
	frontend->demod->cmd->dd_diseqc_send.send_data2  = msg_byte6;
	frontend->demod->cmd->dd_diseqc_send.cont_tone  = (cont_tone == 1) ? DEMOD_DD_DISEQC_SEND_CMD_CONT_TONE_ENABLE : DEMOD_DD_DISEQC_SEND_CMD_CONT_TONE_DISABLE ;
	frontend->demod->cmd->dd_diseqc_send.tone_burst =  (tone_burst == 1) ? DEMOD_DD_DISEQC_SEND_CMD_TONE_BURST_ENABLE : DEMOD_DD_DISEQC_SEND_CMD_TONE_BURST_DISABLE;
	frontend->demod->cmd->dd_diseqc_send.burst_sel  =  (burst_sel == 1) ? DEMOD_DD_DISEQC_SEND_CMD_BURST_SEL_MODULATED : DEMOD_DD_DISEQC_SEND_CMD_BURST_SEL_UNMODUALTED;
/*
	DEMOD_PRINT ("dd_diseqc_send 		diseqc_en 0x%02x\n", frontend->demod->cmd->dd_diseqc_send.diseqc_en);
	DEMOD_PRINT ("dd_diseqc_send		tone_burst 0x%02x\n", frontend->demod->cmd->dd_diseqc_send.tone_burst);
	DEMOD_PRINT ("dd_diseqc_send		cont_tone 0x%02x\n", frontend->demod->cmd->dd_diseqc_send.cont_tone);
	DEMOD_PRINT ("dd_diseqc_send 		burst_sel 0x%02x\n", frontend->demod->cmd->dd_diseqc_send.burst_sel);
	DEMOD_PRINT ("dd_diseqc_send 		msg_length 0x%02x\n", frontend->demod->cmd->dd_diseqc_send.msg_length);
	DEMOD_PRINT ("dd_diseqc_send 		send_framing 0x%02x\n", frontend->demod->cmd->dd_diseqc_send.send_framing);
	DEMOD_PRINT ("dd_diseqc_send 		send_address 0x%02x\n", frontend->demod->cmd->dd_diseqc_send.send_address);
	DEMOD_PRINT ("dd_diseqc_send 		send_command 0x%02x\n", frontend->demod->cmd->dd_diseqc_send.send_command);
	DEMOD_PRINT ("dd_diseqc_send 		send_data0 0x%02x\n", frontend->demod->cmd->dd_diseqc_send.send_data0);
	DEMOD_PRINT ("dd_diseqc_send 		send_data1 0x%02x\n", frontend->demod->cmd->dd_diseqc_send.send_data1);
	DEMOD_PRINT ("dd_diseqc_send 		send_data2 0x%02x\n", frontend->demod->cmd->dd_diseqc_send.send_data2);
*/

	return DEMOD_L1_SET_DD_DISEQC_Send(frontend->demod,
							frontend->demod->cmd->dd_diseqc_send.diseqc_en,
							frontend->demod->cmd->dd_diseqc_send.tone_burst,
							frontend->demod->cmd->dd_diseqc_send.cont_tone,
							frontend->demod->cmd->dd_diseqc_send.burst_sel,
							frontend->demod->cmd->dd_diseqc_send.msg_length,
							frontend->demod->cmd->dd_diseqc_send.send_framing,
							frontend->demod->cmd->dd_diseqc_send.send_address,
							frontend->demod->cmd->dd_diseqc_send.send_command,
							frontend->demod->cmd->dd_diseqc_send.send_data0,
							frontend->demod->cmd->dd_diseqc_send.send_data1,
							frontend->demod->cmd->dd_diseqc_send.send_data2 );
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_SAT_Blind_Info.
 * software initialization function for DVBT/DVBT2/DVBC/DVBC2/DVBS/DVBS2
 *  Used to initialize the demodulator and tuner structures
 *
 * @param *frontend 		[IN] LX_DEMOD_L2_Context, a pointer to LX_DEMOD_L2_Context context to be initialized
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/

int DEMOD_L2_SAT_Blind_Info (LX_DEMOD_L2_Context * frontend)
{
	int retc = NO_DEMOD_ERROR;

	retc = DEMOD_L1_GET_DD_SIGSRCH_INFO(frontend->demod);
	if(retc != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_SIGSRCH_INFO() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

	return retc;
}



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_SAT_Blind_Status.
 * software initialization function for DVBT/DVBT2/DVBC/DVBC2/DVBS/DVBS2
 *  Used to initialize the demodulator and tuner structures
 *
 * @param *frontend 		[IN] LX_DEMOD_L2_Context, a pointer to LX_DEMOD_L2_Context context to be initialized
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/

int DEMOD_L2_SAT_Blind_Status (LX_DEMOD_L2_Context * frontend)
{
	int retc = NO_DEMOD_ERROR;

	retc = DEMOD_L1_GET_DD_BLIND_Status(frontend->demod);
	if(retc != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_BLIND_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}
	DEMOD_NOTI("[DEMOD_API] Symbol_rate : %d\n", frontend->demod->rsp->blind_status.symRate);
	return retc;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_SAT_Blind_Init.
 * software initialization function for DVBT/DVBT2/DVBC/DVBC2/DVBS/DVBS2
 *  Used to initialize the demodulator and tuner structures
 *
 * @param *frontend 		[IN] LX_DEMOD_L2_Context, a pointer to LX_DEMOD_L2_Context context to be initialized
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/

int DEMOD_L2_SAT_Blind_Init (LX_DEMOD_L2_Context * frontend, UINT32 startFreq, UINT32 endFreq)
{
	int retc = NO_DEMOD_ERROR;

	startFreq = 970000;
	DEMOD_NOTI("[DEMOD_API] StartFreq : %d, EndFreq : %d\n", startFreq, endFreq);
	retc = DEMOD_L1_GET_DD_BLIND_Init(frontend->demod, startFreq, endFreq);
	if(retc != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_BLIND_Init() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}
	return retc;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_SAT_Blind_End.
 * software initialization function for DVBT/DVBT2/DVBC/DVBC2/DVBS/DVBS2
 *  Used to initialize the demodulator and tuner structures
 *
 * @param *frontend 		[IN] LX_DEMOD_L2_Context, a pointer to LX_DEMOD_L2_Context context to be initialized
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/

int DEMOD_L2_SAT_Blind_End (LX_DEMOD_L2_Context * frontend)
{
	int retc = NO_DEMOD_ERROR;

	retc = DEMOD_L1_GET_DD_BLIND_End(frontend->demod);
	if(retc != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_BLIND_End() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}
	return retc;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_SAT_Blind_FoundInfo.
 * software initialization function for DVBT/DVBT2/DVBC/DVBC2/DVBS/DVBS2
 *  Used to initialize the demodulator and tuner structures
 *
 * @param *frontend 		[IN] LX_DEMOD_L2_Context, a pointer to LX_DEMOD_L2_Context context to be initialized
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/

int DEMOD_L2_SAT_Blind_FoundInfo (LX_DEMOD_L2_Context * frontend)
{
	int retc = NO_DEMOD_ERROR;

	retc = DEMOD_L1_GET_DD_BLIND_FoundInfo(frontend->demod);
	if(retc != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_BLIND_FoundInfo() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}
	return retc;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_SAT_Blind_SymbolRate_Detect.
 * software initialization function for DVBT/DVBT2/DVBC/DVBC2/DVBS/DVBS2
 *  Used to initialize the demodulator and tuner structures
 *
 * @param *frontend 		[IN] LX_DEMOD_L2_Context, a pointer to LX_DEMOD_L2_Context context to be initialized
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/

int DEMOD_L2_SAT_Blind_SymbolRate_Detect (LX_DEMOD_L2_Context * frontend)
{
	int retc = NO_DEMOD_ERROR;

	retc = DEMOD_L1_SET_DD_SymbolRate_Detect(frontend->demod, DEMOD_DD_DVBC_SRD_CMD_AUTO_EN_ENABLE, frontend->demod->rsp->dd_sigsrch_info.bw_idx);
	if(retc != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_SET_DD_SymbolRate_Detect() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}
	return retc;
}

