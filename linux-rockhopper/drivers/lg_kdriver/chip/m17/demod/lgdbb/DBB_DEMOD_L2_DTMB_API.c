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
**  Name:DBB_DEMOD_L2_DTMB_API.c
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

#include "DBB_DEMOD_L2_DTMB_API.h"               /* Include file for this code */


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_DTMB_SW_Init.
 * software initialization function for VSB/QAM/ISDBT/ATSC3.0
 *  Used to initialize the demodulator
 *
 * @param *front_end 		[IN] LX_DEMOD_L2_Context, a pointer to LX_DEMOD_L2_Context context to be initialized
 * @param demodAdd 		[IN] int, the I2C address of the demod
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8 DEMOD_L2_DTMB_SW_Init  (LX_DEMOD_L2_Context *front_end, UINT32 demodAdd)
{
	UINT8 return_code = NO_DEMOD_ERROR;

	//DBB_PRINT("DEMOD_L2_ATSC_SW_Init starting...\n");

	/* Pointers initialization */
	front_end->demod     				= &(front_end->demodObj);
	front_end->demod_init_done    		= 0;
	front_end->demod->bIsStandby   	= 0;
	front_end->standard 				= DEMOD_DD_MODE_PROP_MODULATION_DTMB;
	front_end->detected_rf 			= 0;
	front_end->centerFrq				= 0;

	/* Calling underlying SW initialization functions */
	return_code =  DEMOD_L1_API_Init (front_end->demod,  demodAdd);


    //DBB_PRINT("DEMOD_L2_ATSC_SW_Init complete\n");

    return return_code;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_DTMB_Set_demod.
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
UINT8  DEMOD_L2_DTMB_Set_demod   (LX_DEMOD_L2_Context *front_end
								, UINT8  standard
								, UINT32 freq
								, UINT8  tuneMode
								, UINT8  specInv_Auto_Enable
								, UINT8  specInv
								, UINT16  ter_bandwidth_KHz )
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
	front_end->demod->prop->dd_if_freq.if_freq = DEMOD_DD_IF_FREQ_PROP_IF_FREQ_5MHZ;
	DBB_PRINT ("ter_bandwidth_KHz : %d\t, bw : %d\n", ter_bandwidth_KHz, front_end->demod->prop->dd_mode.bw );

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
		case DEMOD_DD_MODE_PROP_MODULATION_DTMB:
		{
			//front_end->demod->prop->dd_clk_mode.clk_mode = DEMOD_DD_CLOCK_MODE_PROP_24MHZ;
			//front_end->demod->prop->dd_adc_sel.adcClk 	  = DEMOD_DD_ADC_PROP_ADCCLK_24MHZ;

			DBB_PRINT("Modulation  = DTMB\n");
			break;
		}

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
	startTime = DEMOD_L0_system_time();
	
	return_code = DEMOD_L1_Set_Property(front_end->demod, DEMOD_DD_IF_FREQ_PROP_CODE);
	if(return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}

	return_code = DEMOD_L1_SET_DD_Tune (front_end->demod);
	if(return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L1_SET_DD_Tune error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}

	DBB_PRINT   ("DEMOD 'reset' took %3d ms\n", DEMOD_L0_system_time() - startTime);

	return return_code;
}

/**/
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_DTMB_Set_BaseAddr_AXI Address for AXI_memory write.
 * Set Set_Base Address for DTMB AXI_memory
 *
 * @param *front_end 			[IN] LX_DEMOD_L2_Context
 * @param baseAddr1 			[IN] UINT32
 * @param baseAddr2 			[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L2_DTMB_Set_BaseAddr_AXI(LX_DEMOD_L2_Context *frontend, UINT32 baseAddr )
{
	UINT8 return_code;
	// baseAddr1 : baseAddress
	return_code =  DEMOD_L1_API_DTMB_BaseAddr_AXI(frontend->demod, baseAddr);

	return return_code;

}



