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
#define DEMOD_TAG "[L2.DTMB] "

#include <DBB_DEMOD_typedefs.h>
#include <demod_util.h>

#include <DBB_DEMOD_L2_DTMB_API.h>

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
 * DEMOD_L2_DTMB_SW_Init.
 * software initialization function for VSB/QAM/ISDBT/ATSC3.0
 *  Used to initialize the demodulator
 *
 * @param *frontend 		[IN] LX_DEMOD_L2_Context, a pointer to LX_DEMOD_L2_Context context to be initialized
 * @param demodAdd 		[IN] int, the I2C address of the demod
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_DTMB_SW_Init  (LX_DEMOD_L2_Context * frontend, UINT32 demodAddr)
{
	int retc;

	frontend->demod->bIsStandby   	= 0;
//	frontend->standard 		= DEMOD_MODULATION_DTMB;
	frontend->detected_rf 		= 0;
	frontend->centerFrq		= 0;

	/* Calling underlying SW initialization functions */
	retc =  DEMOD_L1_API_Init (frontend->demod,  demodAddr);
	if (NO_DEMOD_ERROR != retc) {
		DEMOD_ERROR("DEMOD_L1_API_Init() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
	}
	return retc;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_DTMB_Set_demod.
 * sets the demod for locking signals
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
int DEMOD_L2_DTMB_Set_demod   (LX_DEMOD_L2_Context *frontend
								, UINT8  standard
								, UINT32 freq
								, UINT8  tuneMode
								, UINT8  specInv_Auto_Enable
								, UINT8  specInv
								, UINT16  ter_bandwidth_KHz )
{
	int retc = NO_DEMOD_ERROR;
	/* startTime is used to measure internal durations. It is set in various places, whenever required */
	UINT32  startTime = DEMOD_L0_system_time();
	UINT32	checkTime = startTime;

	DEMOD_NOTI("Lock to %s at %d KHz\n", DEMOD_L1_API_Modulation_Text(standard), freq);
	frontend->centerFrq= freq;

	frontend->demod->prop->dd_mode.tuneMode            = tuneMode;
	frontend->demod->prop->dd_mode.specinvauto         = specInv_Auto_Enable;
	frontend->demod->prop->dd_mode.specinv               = specInv;
	frontend->demod->prop->dd_mode.modulation          = standard;
	frontend->demod->prop->dd_mode.bw                	= (UINT8)(ter_bandwidth_KHz/1000);
	frontend->demod->prop->dd_if_freq.if_freq = DEMOD_PROP_IF_FREQ_IF_FREQ_5MHZ;
	DEMOD_NOTI("Received BW = %d KHz\t, Setting BW = %d MHz\n", ter_bandwidth_KHz, frontend->demod->prop->dd_mode.bw );

	DEMOD_NOTI("Tune Mode = %s\n", (frontend->demod->prop->dd_mode.tuneMode == DEMOD_PROP_MODE_TUNE_AUTO) ? "Auto scan" : "Normal");
	DEMOD_NOTI("Spectrum Inversion Auto  = %s\n", (frontend->demod->prop->dd_mode.specinvauto == DEMOD_PROP_MODE_SPECINVAUTO_AUTO) ? "Auto" : "Manual");

	if(frontend->demod->prop->dd_mode.specinvauto != DEMOD_PROP_MODE_SPECINVAUTO_AUTO)
	{
		DEMOD_NOTI("Spectrum = %s\n",( frontend->demod->prop->dd_mode.specinv == DEMOD_PROP_MODE_SPECINV_INVERSION) ? "Inversion" : "Not Inversion");
	}

	/* Setting demod for locking on required standard */
	switch (standard)
	{
		case DEMOD_MODULATION_DTMB:
		{
			DEMOD_NOTI("Modulation  = DTMB \n");
			break;
		}

		default : /* ATV */
		{
			DEMOD_NOTI("'%d' standard (%s) is not supported\n", standard, DEMOD_L1_API_Modulation_Text(standard));
			return 0;
		}
		break;
	}

	retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_PROP_MODE_CODE);
	if(NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("FAIL, DEMOD_L1_Set_Property(DEMOD_PROP_MODE_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

	retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_PROP_IF_FREQ_CODE);
	if(NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("FAIL, DEMOD_L1_Set_Property(DEMOD_PROP_IF_FREQ_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

	DEMOD_INFO("tune prepare took %3d ms\n", DEMOD_L0_system_time() - checkTime);
	checkTime = DEMOD_L0_system_time();

	retc = DEMOD_L1_SET_DD_SoftRst (frontend->demod, 1, 0, 0, 0, 0, 0, 0);
	if(NO_DEMOD_ERROR != retc)
	{
		DEMOD_PRINT ("DEMOD_L1_SET_DD_SoftRst error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

	DEMOD_INFO("reset for tune took %3d ms\n", DEMOD_L0_system_time() - checkTime);
	checkTime = DEMOD_L0_system_time();

	retc = DEMOD_L1_SET_DD_Tune (frontend->demod);
	if(NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("FAIL, DEMOD_L1_SET_DD_Tune 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}
	DEMOD_INFO("tune took %3d ms\n", DEMOD_L0_system_time() - checkTime);
	DEMOD_NOTI("total tune took %3d ms\n", DEMOD_L0_system_time() - startTime);

	return retc;
}

/**/
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_DTMB_Set_BaseAddr_AXI Address for AXI_memory write.
 * Set Set_Base Address for DTMB AXI_memory
 *
 * @param *frontend 			[IN] LX_DEMOD_L2_Context
 * @param baseAddr1 			[IN] UINT32
 * @param baseAddr2 			[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_DTMB_Set_BaseAddr_AXI(LX_DEMOD_L2_Context *frontend, UINT32 baseAddr )
{
	int retc = NO_DEMOD_ERROR;
	DEMOD_PRINT("Start\n");

	retc = DEMOD_L1_SET_DD_DTMB_BASEADDR_AXI(frontend->demod, baseAddr);

	if (retc != NO_DEMOD_ERROR) {
		DEMOD_ERROR("FAIL, DEMOD_L1_SET_DD_DTMB_BASEADDR_AXI() BecauseOf %s\n", DEMOD_L1_API_Error_Text(retc));
		return -ERROR_DEMOD_WRITE;
	}

	return retc;
}



