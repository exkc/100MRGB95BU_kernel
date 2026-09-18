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
**  Name:DBB_DEMOD_L2_Common_API.c
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

#include "DBB_DEMOD_L2_Common_API.h"               /* Include file for this code */


#ifdef __KERNEL__
#include <asm/div64.h> //do_div
//#include "L18F_DEMOD_firmware_0_0_1.h"
#else
#include <math.h>
#include "M19_SAT_DEMOD_firmware_A_0_1.h"
#include "M19_TER_DEMOD_firmware_A_0_1.h"
#include "L18F_DEMOD_firmware_0_0_1.h"
#endif

LX_DEMOD_SQI_CN_ATSC3P1_T  SqiCnAtsc3P1[72] =
{
	/* Hierachy mode */ 	             /* bsetHP */ /* RF mode  */ /* Code rate*/	   /*CN ref */
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_QPSK,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_2_15, 000 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_QPSK,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_3_15, 000 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_QPSK,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_4_15, 100 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_QPSK,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_5_15, 200 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_QPSK,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_6_15, 300 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_QPSK,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_7_15, 400 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_QPSK,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_8_15, 500 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_QPSK,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_9_15, 600 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_QPSK,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_10_15, 700},
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_QPSK,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_11_15, 800 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_QPSK,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_12_15, 800 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_QPSK,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_13_15, 1000 },

	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_16QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_2_15, 100 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_16QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_3_15, 400 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_16QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_4_15, 500 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_16QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_5_15, 700 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_16QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_6_15, 800 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_16QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_7_15, 900 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_16QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_8_15, 1000 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_16QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_9_15, 1100 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_16QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_10_15, 1200 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_16QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_11_15, 1400 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_16QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_12_15, 1500 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_16QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_13_15, 1600 },

	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_64QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_2_15, 400 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_64QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_3_15, 600 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_64QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_4_15, 800 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_64QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_5_15, 1000 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_64QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_6_15, 1200 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_64QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_7_15, 1300 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_64QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_8_15, 1400 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_64QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_9_15, 1600 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_64QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_10_15, 1700 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_64QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_11_15, 1800 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_64QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_12_15, 2000 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_64QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_13_15, 2100 },

	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_256QAM_NUC, DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_2_15, 000 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_256QAM_NUC, DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_3_15, 800 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_256QAM_NUC, DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_4_15, 1100 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_256QAM_NUC, DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_5_15, 1300 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_256QAM_NUC, DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_6_15, 1500 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_256QAM_NUC, DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_7_15, 1600 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_256QAM_NUC, DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_8_15, 1800 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_256QAM_NUC, DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_9_15, 2000 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_256QAM_NUC, DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_10_15, 2100 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_256QAM_NUC, DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_11_15, 2300 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_256QAM_NUC, DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_12_15, 2400 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_256QAM_NUC, DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_13_15, 2600 },

	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_1024QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_2_15, 700 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_1024QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_3_15, 1000 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_1024QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_4_15, 1300 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_1024QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_5_15, 1500 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_1024QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_6_15, 1700 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_1024QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_7_15, 1900 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_1024QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_8_15, 2100 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_1024QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_9_15, 2300 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_1024QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_10_15, 2500 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_1024QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_11_15, 2700 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_1024QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_12_15, 3000 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_1024QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_13_15, 3200 },

	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_4096QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_2_15, 900 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_4096QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_3_15, 1200 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_4096QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_4_15, 1500 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_4096QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_5_15, 1700 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_4096QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_6_15, 2000 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_4096QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_7_15, 2200 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_4096QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_8_15, 2500 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_4096QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_9_15, 2700 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_4096QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_10_15, 3000 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_4096QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_11_15, 3200 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_4096QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_12_15, 3400 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_4096QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_13_15, 3700 },



};



/* Allowing compatibility with previous parts (also reflected in DEMOD_L2_PowerUpWithPatch) */

#define DEMOD_BYTES_PER_LINE 			8

#ifdef __KERNEL__
#define DEMOD_DEBUG_TRACE                  printk
#else
#define DEMOD_DEBUG_TRACE                  printf
#endif


SINT64 _DEMOD_do_div64_32(SINT64 dividend, SINT32 divisor)
{
#ifdef __KERNEL__

	 do_div(dividend, divisor) ;

#else
   	dividend =  (SINT64)(dividend / divisor) ;
#endif
	return dividend;

}

SINT64 _DEMOD_do_div64_64(SINT64 dividend, SINT64 divisor)
 {
#ifdef __KERNEL__
	SINT32  d;
	SINT32 high;
	unsigned int shift;

   	high = (divisor >> 32);

    	if (high)
	{
        shift = fls(high);
        d = divisor >> shift;
        dividend >>= shift;
   	}
	else
       	d = divisor;

   dividend = _DEMOD_do_div64_32(dividend, d);
#else
   dividend = dividend / divisor;
#endif

   	return dividend;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_Configure.
 * Sets up common properties startup
 *
 * @param *frontend [IN] LX_DEMOD_L2_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8 DEMOD_L2_Configure           (LX_DEMOD_L2_Context *frontend)
{
    UINT8 return_code;
    return_code = NO_DEMOD_ERROR;

	//Do Top control
	/* Storing Properties startup configuration in propShadow                              */
	/* !! Do NOT change the content of DEMOD_L1_Store_Properties_Defaults                   !! */
	/* !! It should reflect the part internal property settings after firmware download !! */

    /* Edit the procedure below if you have any properties settings different from the standard defaults */
	//DBB_PRINT ("DEMOD_L1_Store_Properties_Defaults\n");
	DEMOD_L1_Store_Properties_Defaults (frontend->demod->propShadow);

    //DBB_PRINT("DEMOD_L1_Store_User_Properies\n");
    DEMOD_L1_Store_User_Properies (frontend->demod->prop);
    /* Download properties different from 'default' */
    return_code |=DEMOD_L1_Download_All_Properties(frontend->demod);


    return return_code;
}

#ifndef __EVAL_GUI__
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_Configure.
 * Sets up common properties startup
 *
 * @param *frontend [IN] LX_DEMOD_L2_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8 DEMOD_L2_Opermode_Configure           (LX_DEMOD_L2_Context *frontend , LX_DEMOD_OPER_MODE_T operMode)
{
    UINT8 return_code;
    return_code = NO_DEMOD_ERROR;
	
	DBB_PRINT ("DEMOD_L2_Opermode_Configure 0x%02x\n", operMode );

	frontend->demod->propertyWriteMode = DEMOD_DD_DOWNLOAD_ALWAYS;

//EMOD_L1_Store_Properties_Defaults (frontend->demod->propShadow);
	DEMOD_L1_Store_User_Properies (frontend->demod->prop);
	return_code = DEMOD_L1_Download_All_Properties(frontend->demod);

	switch(operMode)
	{
		case LX_DEMOD_DVBT: 
		{
			return_code |= DEMOD_L1_Download_DVBT_Properties(frontend->demod);
		}
		break;
		
		case LX_DEMOD_DVBT2: 
		{
			return_code |=DEMOD_L1_Download_DVBT2_Properties(frontend->demod);
		}
		break;
		
		case LX_DEMOD_DVBS:
		{
			return_code |=DEMOD_L1_Download_DVBS_Properties(frontend->demod);
		}
		break;
		case LX_DEMOD_DVBS2:
		{
			return_code |=DEMOD_L1_Download_DVBS2_Properties(frontend->demod);
		}
		break;
		case LX_DEMOD_DVBC:
		{
			return_code |=DEMOD_L1_Download_DVBC_Properties(frontend->demod);
		}
		break;
		case LX_DEMOD_DTMB:
		{
			return_code |=DEMOD_L1_Download_DTMB_Properties(frontend->demod);
		}
		break;
		
		default:
		{
			return_code |= NO_DEMOD_ERROR;	
		}
		break;
	}

	frontend->demod->propertyWriteMode = DEMOD_DD_DOWNLOAD_ON_CHANGE;

    return return_code;
}
#endif

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_PowerUpWithPatch.
 * Sends download commands and binary firmware images to MCU bootloader .
 *
 * @param *frontend [IN] LX_DEMOD_L2_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8 DEMOD_L2_PowerUpWithPatch    (LX_DEMOD_L2_Context *frontend)
{
	int return_code;
	int fw_loaded;
	return_code = NO_DEMOD_ERROR;
	fw_loaded   = 0;

	/* Before patching, set POWER_UP values for 'RESET' and 'BOOTLOADER' */
	#ifndef __KERNEL__
	return_code = DEMOD_L1_API_InitFirmware(frontend->demod) ;
	if (return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L1_API_InitFirmware error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}
	#endif

	#ifdef __KERNEL__
	//return_code = DEMOD_L1_API_LoadFirmware_IRAM(frontend->demod, L18F_DEMOD_FW_IRAM_0_0_1 , 1);
	#else
	if(frontend->demod->i2c->chipVer >= M16P3)
	{
		frontend->demod->i2c->fwDone = 0;
		if((frontend->standard == DEMOD_DD_MODE_PROP_MODULATION_DVBS) || (frontend->standard == DEMOD_DD_MODE_PROP_MODULATION_DVBS2))
		{
			return_code = DEMOD_L1_API_LoadFirmware_IRAM(frontend->demod, M19_SAT_DEMOD_FW_IRAM_a_0_1 , 1);
			DBB_PRINT("M19_SAT_DEMOD_FW_IRAM_a_0_1 done");

		}
		else
		{
			return_code = DEMOD_L1_API_LoadFirmware_IRAM(frontend->demod, M19_TER_DEMOD_FW_IRAM_a_0_1 , 1);
			DBB_PRINT("M19_TER_DEMOD_FW_IRAM_a_0_1 done");
		}
	}
	else
	{
		return_code = DEMOD_L1_API_LoadFirmware_IRAM(frontend->demod, L18F_DEMOD_FW_IRAM_0_0_1 , 1);
	}

	if (return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L1_API_LoadFirmware_IRAM error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}
	#endif



	#ifdef __KERNEL__
	//return_code = DEMOD_L1_API_LoadFirmware_DRAM(frontend->demod, L18F_DEMOD_FW_DRAM_0_0_1 , 1);
	#else
	if(frontend->demod->i2c->chipVer >= M16P3)
	{
		if((frontend->standard == DEMOD_DD_MODE_PROP_MODULATION_DVBS) || (frontend->standard == DEMOD_DD_MODE_PROP_MODULATION_DVBS2))
		{
			return_code = DEMOD_L1_API_LoadFirmware_DRAM(frontend->demod, M19_SAT_DEMOD_FW_DRAM_a_0_1 , 1);
			DBB_PRINT("M19_SAT_DEMOD_FW_DRAM_a_0_1 done");
		}
		else
		{
			return_code = DEMOD_L1_API_LoadFirmware_DRAM(frontend->demod, M19_TER_DEMOD_FW_DRAM_a_0_1 , 1);
			DBB_PRINT("M19_TER_DEMOD_FW_DRAM_a_0_1 done");
		}
	}
	else
	{
		return_code = DEMOD_L1_API_LoadFirmware_DRAM(frontend->demod, L18F_DEMOD_FW_DRAM_0_0_1 , 1);
	}

	if (return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L1_API_LoadFirmware_DRAM error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}
	#endif

	return_code = DEMOD_L1_API_StartFirmware(frontend->demod) ;
	if (return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L1_API_StartFirmware error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}


    return NO_DEMOD_ERROR;
}



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_Init.
 * Reset and Initialize DBB mdulator
 *
 * @param *frontend 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8 DEMOD_L2_Init  (LX_DEMOD_L2_Context *frontend)
{
	UINT8 return_code;
	DBB_PRINT("DEMOD_L2_Init starting...\n");

#ifndef __KERNEL__
	if ((return_code = DEMOD_L2_PowerUpWithPatch(frontend)) != NO_DEMOD_ERROR)
	{   /* PowerUp into bootloader */
	    DBB_PRINT ("DEMOD_L2_PowerUpWithPatch error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
	    return return_code;
	}
#endif

	/* At this point, FW is loaded and started.  */
	return_code = DEMOD_L2_Configure(frontend);
	if(return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L2_Configure error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}

	frontend->demod_init_done = 1;

	DBB_PRINT("DEMOD_L2_Init complete...\n");
	return NO_DEMOD_ERROR;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_Standby.
 * Setup power save mode
 *
 * @param *frontend [IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8 DEMOD_L2_Standby  (LX_DEMOD_L2_Context *frontend)
{
	DBB_PRINT ("DEMOD_L2_Standby \n");
	return DEMOD_L1_SET_DD_Power_Save (frontend->demod, TRUE);
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_WakeUp.
 * Wakes up the DBB demodulator.
 *
 * @param *frontend [IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8 DEMOD_L2_WakeUp              (LX_DEMOD_L2_Context *frontend)
{
	DBB_PRINT ("DEMOD_L2_WakeUp \n");
	return DEMOD_L1_SET_DD_Power_Save (frontend->demod, FALSE);
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_Media.
 * media retrieval function
 * Used to retrieve the media used by the LGDBB
 *
 * @param *frontend 		[IN] LX_DEMOD_L1_Context
 * @param modulation		[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8 DEMOD_L2_Media  (LX_DEMOD_L2_Context *frontend, UINT8 modulation)
{
 	switch (modulation)
  	{
	    	case DEMOD_DD_MODE_PROP_MODULATION_AUTO_DETECT :
		{
		      	switch (frontend->demod->prop->dd_auto_mode.auto_detect)
			{
			        case DEMOD_DD_AUTO_MODE_PROP_DET_DVBT_DVBT2_ENABLE		:
			        case DEMOD_DD_AUTO_MODE_PROP_DET_DVBT_ONLY_ENABLE     	:
			        case DEMOD_DD_AUTO_MODE_PROP_DET_DVBT2_ONLY_ENABLE    	:
					{
						return DEMOD_DD_TERRESTRIAL;
			        	}
					break;

			        case DEMOD_DD_AUTO_MODE_PROP_DET_DVBC_DVBC2_ENABLE     	:
			        case DEMOD_DD_AUTO_MODE_PROP_DET_DVBC_ONLY_ENABLE     	:
			        case DEMOD_DD_AUTO_MODE_PROP_DET_DVBC2_ONLY_ENABLE     	:
					{
						return DEMOD_DD_CABLE;
			        	}
					break;

			        case DEMOD_DD_AUTO_MODE_PROP_DET_DVBS_DVBS2_ENABLE     	:
			        case DEMOD_DD_AUTO_MODE_PROP_DET_DVBS_ONLY_ENABLE     	:
			        case DEMOD_DD_AUTO_MODE_PROP_DET_DVBS2_ONLY_ENABLE     	:
					{
						return DEMOD_DD_SATELLITE;
			        	}
					break;
				default : 
		 	 		DBB_PRINT("UNKNOWN media!\n");
		  		break;
	      		}
	      		break;
	   	 }
		case DEMOD_DD_MODE_PROP_MODULATION_DVBT :
		case DEMOD_DD_MODE_PROP_MODULATION_DVBT2:
		case DEMOD_DD_MODE_PROP_MODULATION_VSB:
		case DEMOD_DD_MODE_PROP_MODULATION_ATSC3:
			{
				return DEMOD_DD_TERRESTRIAL;
	        	}
			break;

		case DEMOD_DD_MODE_PROP_MODULATION_DVBC 	  :
		case DEMOD_DD_MODE_PROP_MODULATION_DVBC2 :
		case DEMOD_DD_MODE_PROP_MODULATION_QAM :
			{
				return DEMOD_DD_CABLE;
	        	}
			break;

		case DEMOD_DD_MODE_PROP_MODULATION_DVBS :
		case DEMOD_DD_MODE_PROP_MODULATION_DVBS2:
			{
				return DEMOD_DD_SATELLITE;
	        	}
			break;
		default : 
		  	DBB_PRINT("UNKNOWN media!\n");
		  	break;
  }

  return NO_DEMOD_ERROR;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_Switch_to_standard.
 * Sets media for new standard
 *
 * @param *front_end 		[IN] LX_DEMOD_L2_Context
 * @param new_standard 	[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L2_Switch_to_standard (LX_DEMOD_L2_Context *front_end, UINT8 new_standard)
{
	UINT8 return_code = NO_DEMOD_ERROR;

	front_end->demod->standard = new_standard;

	/* ------------------------------------------------------------ */
	/* Set media for new standard                                   */
	/* ------------------------------------------------------------ */
	front_end->demod->prop->dd_mode.modulation = new_standard;
	front_end->demod->media = DEMOD_L2_Media(front_end, front_end->demod->prop->dd_mode.modulation);

	if(DEMOD_DD_MODE_PROP_MODULATION_ANALOG == new_standard || DEMOD_DD_MODE_PROP_MODULATION_SLEEP == new_standard)
	{

		if(!front_end->demod->bIsStandby)
		{
			return_code = DEMOD_L2_Standby (front_end);
			if(return_code != NO_DEMOD_ERROR)
			{
				DBB_PRINT ("DEMOD_L2_Standby error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
				return return_code;
			}
				front_end->demod->bIsStandby = 1;
		}
	}
	else
	{
		if(front_end->demod->bIsStandby)
		{
			return_code = DEMOD_L2_WakeUp (front_end);
			if(return_code != NO_DEMOD_ERROR)
			{
				DBB_PRINT ("DEMOD_L2_WakeUp error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
				return return_code;
			}
			front_end->demod->bIsStandby = 0;
		}

#if 0
#ifndef LG3307_API

		 #ifdef   DEMOD_SATELLITE_FRONT_END
			if(front_end->tuner_sat->i2c->address != NULL)
			{
				front_end->demod->prop->dd_mode.specinv = DEMOD_L2_Set_Invert_Spectrum(front_end);
			}
		#endif
#endif
#endif
		front_end->demod->prop->dd_mode.modulation = new_standard;

		if(NO_DEMOD_ERROR != DEMOD_L1_Set_Property(front_end->demod, DEMOD_DD_MODE_PROP_CODE))
			//DEMOD_L1_SET_DD_Restart(front_end->demod);
			return ERROR_DEMOD_ERROR;
		//else
		//	return ERROR_DEMOD_ERROR;
	}

	return NO_DEMOD_ERROR;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_Check_NeverLock_state.
 * Check neverLock status. used for searching channels automatically
 *
 * @param *front_end 		[IN] LX_DEMOD_L2_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8   DEMOD_L2_Check_NeverLock_state   (LX_DEMOD_L2_Context *front_end)
{
	UINT8 return_code;
	UINT8 lock = 2;

	return_code = DEMOD_L1_GET_DD_Status(front_end->demod);
	if (return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT("DEMOD_lock_to_carrier: DEMOD_L1_DD_STATUS error\n");
		return lock;
	}
	if(front_end->demod->rsp->dd_status.neverLock  == DEMOD_DD_STATUS_RESPONSE_NEVERLOCK_LOCKED   )
	{
		lock = 1;

		DBB_PRINT("DEMOD_lock_to_carrier: locked on a %s signal\n", DEMOD_L1_API_StandardName(front_end->demod->rsp->dd_status.reply_operMod));
	}
	else if(front_end->demod->rsp->dd_status.neverLock  == DEMOD_DD_STATUS_RESPONSE_NEVERLOCK_NO_LOCK)
	{
		lock = 0;
		DBB_PRINT("No SIgnal detected !!\n");
		DBB_PRINT("DEMOD_L2_check_neverlock_loop neverlock(mcu) = %d, neverlock(neverlock_state) = %d, feclock = %d\n", front_end->demod->rsp->dd_status.neverLock, lock, front_end->demod->rsp->dd_status.lock_fec);

	}
	else
	{
		lock = 2;
//		DBB_PRINT("Processing !!\n");
//		DBB_PRINT("***^^^()^^^***DEMOD_L2_check_neverlock_loop neverlock(mcu) = %d, neverlock(neverlock_state) = %d, feclock = %d***^1111111^^()^^^***\n", front_end->demod->rsp->dd_status.neverLock, lock, front_end->demod->rsp->dd_status.lock_fec);

	}

	return lock;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_Check_lock_loop.
 * Checks lock status.
 *  used for manual channel scan and channel change
 *
 * @param *front_end 		[IN] LX_DEMOD_L2_Context
 * @param new_standard 	[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8   DEMOD_L2_Check_lock_loop   (LX_DEMOD_L2_Context *front_end, UINT8 standard)
{
  UINT32 searchStartTime;
  UINT32 min_lock_time_ms = 0;
  UINT32 max_lock_time_ms = 0;
  UINT32 searchDelay = 0;
  UINT8  lock = 0;

    /* Set min_lock_time_ms and max_lock_time_ms*/
  switch (standard)
  {
	case DEMOD_DD_MODE_PROP_MODULATION_VSB :
	{
		min_lock_time_ms = DEMOD_DD_VSB_MIN_LOCK_TIME;
		max_lock_time_ms = DEMOD_DD_VSB_MAX_LOCK_TIME;

		}
	  break;

	case DEMOD_DD_MODE_PROP_MODULATION_QAM:
	{
		min_lock_time_ms = DEMOD_DD_QAM_MIN_LOCK_TIME;
		max_lock_time_ms =DEMOD_DD_QAM_MAX_LOCK_TIME;

		}
	  break;

	case DEMOD_DD_MODE_PROP_MODULATION_ATSC3 :
	{
		min_lock_time_ms = DEMOD_DD_ATSC3_MIN_LOCK_TIME;
		max_lock_time_ms = DEMOD_DD_ATSC3_MAX_LOCK_TIME;

		}
	  break;


#ifndef LG3307_API


	case DEMOD_DD_MODE_PROP_MODULATION_ISDBT :
	{
		min_lock_time_ms = DEMOD_DD_ISDBT_MIN_LOCK_TIME;
		max_lock_time_ms = DEMOD_DD_ISDBT_MAX_LOCK_TIME;

		}
	  break;

	case DEMOD_DD_MODE_PROP_MODULATION_DVBT :
	{
		min_lock_time_ms = DEMOD_DD_DVBT_MIN_LOCK_TIME;
	    max_lock_time_ms = DEMOD_DD_DVBT_MAX_LOCK_TIME;
		if (front_end->auto_detect_DVBT_T2)
		{
			min_lock_time_ms = DEMOD_DD_DVBT_MIN_LOCK_TIME;
			max_lock_time_ms = DEMOD_DD_DVBT2_MAX_LOCK_TIME;
		}
		else
		{
			min_lock_time_ms = DEMOD_DD_DVBT_MIN_LOCK_TIME;
			max_lock_time_ms = DEMOD_DD_DVBT_MAX_LOCK_TIME;
		}
	}
	break;
	case DEMOD_DD_MODE_PROP_MODULATION_DVBT2:
	{
		 min_lock_time_ms = DEMOD_DD_DVBT2_MIN_LOCK_TIME;
		 max_lock_time_ms = DEMOD_DD_DVBT2_MAX_LOCK_TIME;

  }
  break;

  case DEMOD_DD_MODE_PROP_MODULATION_DVBC :
	{
		min_lock_time_ms = DEMOD_DD_DVBC_MIN_LOCK_TIME;
		max_lock_time_ms = DEMOD_DD_DVBC_MAX_LOCK_TIME;

    	}
      break;

 #ifdef   DEMOD_SATELLITE_FRONT_END
    case DEMOD_DD_MODE_PROP_MODULATION_DVBS :
    case DEMOD_DD_MODE_PROP_MODULATION_DVBS2:
	{
		if (front_end->auto_detect_SAT)
		{
		  min_lock_time_ms = DEMOD_DD_DVBS2_MIN_LOCK_TIME;
		  max_lock_time_ms = DEMOD_DD_DVBS2_MAX_LOCK_TIME*2;
		}
		else
		{
			if (standard == DEMOD_DD_MODE_PROP_MODULATION_DVBS )
			{
			    	min_lock_time_ms = DEMOD_DD_DVBS_MIN_LOCK_TIME;
				max_lock_time_ms = DEMOD_DD_DVBS_MAX_LOCK_TIME;
			}
			if (standard == DEMOD_DD_MODE_PROP_MODULATION_DVBS2)
			{
			    min_lock_time_ms = DEMOD_DD_DVBS2_MIN_LOCK_TIME;
			    max_lock_time_ms =DEMOD_DD_DVBS2_MAX_LOCK_TIME;
			}
		}
   	 }
      	break;
#endif

	case DEMOD_DD_MODE_PROP_MODULATION_DTMB :
	{
		min_lock_time_ms = DEMOD_DD_DTMB_MIN_LOCK_TIME;
		max_lock_time_ms = DEMOD_DD_DTMB_MAX_LOCK_TIME;

		}
	  break;

#endif

    default :
	{
      		return 0;
    	}
      break;

  }

  searchStartTime = DEMOD_L0_system_time();

  /* as we will not lock in less than min_lock_time_ms, wait a while...*/
  DEMOD_L0_system_wait(min_lock_time_ms);

  while (1)
  {
    /* Check the status for the current modulation */
	if (NO_DEMOD_ERROR != DEMOD_L1_GET_DD_Status(front_end->demod))
	{
		DBB_PRINT("DEMOD_lock_to_carrier: DEMOD_L1_DD_STATUS error\n");
		return lock;
	}
	lock = front_end->demod->rsp->dd_status.lock_fec;

	if (lock == 1)
	{
		  DBB_PRINT ("DEMOD_lock_to_carrier 'lock'  took %3d ms\n" , searchDelay);
		  return lock;
	}
   	searchDelay = DEMOD_L0_system_time() - searchStartTime;

    /* timeout management (this should never happen if timeout values are correctly set) */
	if (searchDelay >= max_lock_time_ms)
	{
		DBB_PRINT ("DEMOD_L2_check_lock_loop timeout(%d) after %d ms\n", max_lock_time_ms,searchDelay);
		break;
    }

    /* Check status every 10 ms */
    DEMOD_L0_system_wait(10);
  }

  return lock;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_Check_NeverLock_loop.
 * Checks never lock and demod lock status.
 * used for searching channels automatically
 *
 * @param *front_end 		[IN] LX_DEMOD_L2_Context
 * @param new_standard 	[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8   DEMOD_L2_Check_NeverLock_loop   (LX_DEMOD_L2_Context *front_end, UINT8 standard)
{
  UINT32 searchStartTime;
  UINT32 min_lock_time_ms = 0;
  UINT32 max_lock_time_ms = 0;
  UINT32 neverLock_time_ms = 0;
  UINT32 searchDelay = 0;
  UINT8  neverLock = 0;
  UINT8 fecLock = 0;

    /* Set min_lock_time_ms and max_lock_time_ms*/
  switch (standard)
  {
	case DEMOD_DD_MODE_PROP_MODULATION_VSB :
	{
		min_lock_time_ms = DEMOD_DD_VSB_MIN_LOCK_TIME;
		max_lock_time_ms = DEMOD_DD_VSB_MAX_LOCK_TIME;
		neverLock_time_ms = DEMOD_DD_VSB_MAX_SEARCH_TIME;

		}
	  break;

	case DEMOD_DD_MODE_PROP_MODULATION_QAM:
	{
		min_lock_time_ms = DEMOD_DD_QAM_MIN_LOCK_TIME;
		max_lock_time_ms = DEMOD_DD_QAM_MAX_LOCK_TIME;
		neverLock_time_ms = DEMOD_DD_QAM_MAX_SEARCH_TIME;
		}
	  break;

	case DEMOD_DD_MODE_PROP_MODULATION_ATSC3 :
	{
		min_lock_time_ms = DEMOD_DD_ATSC3_MIN_LOCK_TIME;
		max_lock_time_ms = DEMOD_DD_ATSC3_MAX_LOCK_TIME;
		neverLock_time_ms = DEMOD_DD_ATSC3_MAX_SEARCH_TIME;

		}
	  break;


#ifndef LG3307_API

	case DEMOD_DD_MODE_PROP_MODULATION_ISDBT :
	{
		min_lock_time_ms = DEMOD_DD_ISDBT_MIN_LOCK_TIME;
		max_lock_time_ms = DEMOD_DD_ISDBT_MAX_LOCK_TIME;
		neverLock_time_ms = DEMOD_DD_ISDBT_MAX_SEARCH_TIME;

		}
	  break;

	case DEMOD_DD_MODE_PROP_MODULATION_DVBT :
	{
		if (front_end->auto_detect_DVBT_T2)
		{
			min_lock_time_ms = DEMOD_DD_DVBT_MIN_LOCK_TIME;
			max_lock_time_ms = DEMOD_DD_DVBT2_MAX_LOCK_TIME;
			neverLock_time_ms = DEMOD_DD_DVBT2_MAX_SEARCH_TIME;
		}
		else
		{
			min_lock_time_ms = DEMOD_DD_DVBT_MIN_LOCK_TIME;
			max_lock_time_ms = DEMOD_DD_DVBT_MAX_LOCK_TIME;
			neverLock_time_ms = DEMOD_DD_DVBT_MAX_SEARCH_TIME;
		}
	}
	break;

	case DEMOD_DD_MODE_PROP_MODULATION_DVBT2:
	{
		if (front_end->auto_detect_DVBT_T2)
		{
			min_lock_time_ms = DEMOD_DD_DVBT_MIN_LOCK_TIME;
			max_lock_time_ms = DEMOD_DD_DVBT2_MAX_LOCK_TIME;
			neverLock_time_ms = DEMOD_DD_DVBT_MAX_SEARCH_TIME;
		}
		else
		{
				min_lock_time_ms = DEMOD_DD_DVBT2_MIN_LOCK_TIME;
				max_lock_time_ms = DEMOD_DD_DVBT2_MAX_LOCK_TIME;
				neverLock_time_ms = DEMOD_DD_DVBT2_MAX_SEARCH_TIME;
		}
      }
      break;

    case DEMOD_DD_MODE_PROP_MODULATION_DVBC :
	{
		min_lock_time_ms =DEMOD_DD_DVBC_MIN_LOCK_TIME;
		max_lock_time_ms = DEMOD_DD_DVBC_MAX_LOCK_TIME;
		neverLock_time_ms = DEMOD_DD_DVBC_MAX_SEARCH_TIME;

    	}
      break;

 #ifdef   DEMOD_SATELLITE_FRONT_END
    case DEMOD_DD_MODE_PROP_MODULATION_DVBS :
    case DEMOD_DD_MODE_PROP_MODULATION_DVBS2:
	{
		if (front_end->auto_detect_SAT)
		{
		  min_lock_time_ms = DEMOD_DD_DVBS_MIN_LOCK_TIME;
		  max_lock_time_ms = DEMOD_DD_DVBS_MAX_LOCK_TIME * 2;
		  neverLock_time_ms = DEMOD_DD_DVBS_MAX_SEARCH_TIME;
		}
		else
		{
			if (standard == DEMOD_DD_MODE_PROP_MODULATION_DVBS )
			{
			    	min_lock_time_ms = DEMOD_DD_DVBS_MIN_LOCK_TIME;
				max_lock_time_ms = DEMOD_DD_DVBS_MAX_LOCK_TIME;
				neverLock_time_ms = DEMOD_DD_DVBS_MAX_SEARCH_TIME;
			}
			if (standard == DEMOD_DD_MODE_PROP_MODULATION_DVBS2)
			{
			    min_lock_time_ms = DEMOD_DD_DVBS2_MIN_LOCK_TIME;
				max_lock_time_ms = DEMOD_DD_DVBS2_MAX_LOCK_TIME;
				neverLock_time_ms = DEMOD_DD_DVBS2_MAX_SEARCH_TIME;
			}
		}
   	 }
      	break;
#endif

	case DEMOD_DD_MODE_PROP_MODULATION_DTMB :
	{
		min_lock_time_ms = DEMOD_DD_DTMB_MIN_LOCK_TIME;
		max_lock_time_ms = DEMOD_DD_DTMB_MAX_LOCK_TIME;
		neverLock_time_ms = DEMOD_DD_DTMB_MAX_SEARCH_TIME;

		}
	  break;

#endif

    default :
	{
      		return NO_DEMOD_ERROR;
    	}
      break;

  }

  searchStartTime = DEMOD_L0_system_time();

  /* as we will not lock in less than min_lock_time_ms, wait a while...*/
  DEMOD_L0_system_wait(min_lock_time_ms);

  while (1)
  {
	if(neverLock != 1)
	{
		/* Check the status for the current modulation */
	   	 neverLock = DEMOD_L2_Check_NeverLock_state(front_end);

		if(standard == DEMOD_DD_MODE_PROP_MODULATION_ATSC3)
		 {
		 	if (neverLock == 0)
			{
		 		neverLock = 2;
		 	}
		 }

		if (neverLock == 1)
		{
			//max_lock_time_ms = DEMOD_DD_VSB_MAX_LOCK_TIME;
			searchDelay = DEMOD_L0_system_time() - searchStartTime;
			DBB_PRINT ("DEMOD_lock_to_carrier 'neverLock'  took %3d ms\n" , searchDelay);
		}
		else if (neverLock == 0)
		{
			//max_lock_time_ms = DEMOD_DD_VSB_MAX_LOCK_TIME;
			searchDelay = DEMOD_L0_system_time() - searchStartTime;
			DBB_PRINT ("DEMOD_unlock_to_neverlock   took %3d ms\n" , searchDelay);
			neverLock = 0;
			//break;
			return NO_DEMOD_ERROR;
		}
		else
		{
			if (searchDelay >= neverLock_time_ms)
			{
				DBB_PRINT ("DEMOD_L2_check_neverlock_loop timeout(%d) after %d ms\n", neverLock_time_ms, searchDelay);
				neverLock = 0;
				//break;
				return NO_DEMOD_ERROR;
			}
		}
	}
	else
	{
		/* Call the standard-specific status function */
		if (NO_DEMOD_ERROR != DEMOD_L1_GET_DD_Status(front_end->demod))
		{
			DBB_PRINT("DEMOD_lock_to_carrier: DEMOD_L1_DD_STATUS error\n");
			fecLock = 0;
		}

		fecLock = front_end->demod->rsp->dd_status.lock_fec;

		if(fecLock == 1)
		{
			searchDelay = DEMOD_L0_system_time() - searchStartTime;
			DBB_PRINT ("DEMOD_lock_to_carrier 'fecLock'  took %3d ms\n" , searchDelay);
			return fecLock;

		}

		else
		{
			searchDelay = DEMOD_L0_system_time() - searchStartTime;
			if (searchDelay >= neverLock_time_ms)
			{
				DBB_PRINT ("DEMOD_L2_check_lock_loop timeout(%d) after %d ms\n", neverLock_time_ms,searchDelay);
				fecLock = 0;
				//break;
				return NO_DEMOD_ERROR;
			}
		}

    }
//   	searchDelay = DEMOD_L0_system_time() - searchStartTime;

    /* Check status every 10 ms */
    DEMOD_L0_system_wait(10);
  }

  return fecLock;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_Check_BlindLock_loop.
 * Checks never lock and demod lock status.
 * used for searching channels automatically
 *
 * @param *front_end 		[IN] LX_DEMOD_L2_Context
 * @param new_standard 	[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8   DEMOD_L2_Check_BlindLock_loop   (LX_DEMOD_L2_Context *front_end, UINT8 standard)
{
  UINT32 searchStartTime;
  UINT32 min_lock_time_ms = 0;
  UINT32 max_lock_time_ms = 0;
  UINT32 blindLock_time_ms = 0;
  UINT32 searchDelay = 0;
  UINT8  blindLock = 0;
//  UINT8 fecLock = 0;

    /* Set min_lock_time_ms and max_lock_time_ms*/
  switch (standard)
  {
#ifndef LG3307_API
    case DEMOD_DD_MODE_PROP_MODULATION_DVBC :
	{
		min_lock_time_ms =DEMOD_DD_DVBC_MIN_LOCK_TIME;
		max_lock_time_ms = DEMOD_DD_DVBC_MAX_LOCK_TIME;
		blindLock_time_ms = DEMOD_DD_DVBC_MAX_SEARCH_TIME;

    	}
      break;

 #ifdef   DEMOD_SATELLITE_FRONT_END
    case DEMOD_DD_MODE_PROP_MODULATION_DVBS :
    case DEMOD_DD_MODE_PROP_MODULATION_DVBS2:
	{
		if (front_end->auto_detect_SAT)
		{
		  min_lock_time_ms = 10;
		  max_lock_time_ms = 100;
		  blindLock_time_ms = 1000;
		}
		else
		{
			if (standard == DEMOD_DD_MODE_PROP_MODULATION_DVBS )
			{
			   	min_lock_time_ms = 10;
				max_lock_time_ms = 100;
				blindLock_time_ms = 1000;
			}
			if (standard == DEMOD_DD_MODE_PROP_MODULATION_DVBS2)
			{
			    min_lock_time_ms = 10;
				max_lock_time_ms = 100;
				blindLock_time_ms = 1000;
			}
		}
   	 }
      	break;
#endif

#endif

    default :
	{
      		return NO_DEMOD_ERROR;
    	}
      break;

  }

  searchStartTime = DEMOD_L0_system_time();

  /* as we will not lock in less than min_lock_time_ms, wait a while...*/
  DEMOD_L0_system_wait(min_lock_time_ms);

  while (1)
  {
	if(blindLock != 1)
	{
		/* Check the status for the current modulation */
	   	 blindLock = DEMOD_L2_Check_BlindLock_state(front_end);

		if (blindLock == 1)
		{
			//max_lock_time_ms = DEMOD_DD_VSB_MAX_LOCK_TIME;
			searchDelay = DEMOD_L0_system_time() - searchStartTime;
			DBB_PRINT ("DEMOD_lock_to_carrier 'blindLock'  took %3d ms\n" , searchDelay);
			break;
		}
		else if (blindLock == 2)
		{
			//max_lock_time_ms = DEMOD_DD_VSB_MAX_LOCK_TIME;
			searchDelay = DEMOD_L0_system_time() - searchStartTime;
			DBB_PRINT ("DEMOD_unlock_to_blindlock   took %3d ms\n" , searchDelay);
			blindLock = 0;
			break;
			//return NO_DEMOD_ERROR;
		}
		else
		{
			searchDelay = DEMOD_L0_system_time() - searchStartTime;
			if (searchDelay >= blindLock_time_ms)
			{
				DBB_PRINT ("DEMOD_L2_check_blindlock_loop timeout(%d) after %d ms\n", blindLock_time_ms, searchDelay);
				blindLock = 0;
				//break;
				return NO_DEMOD_ERROR;
			}
		}
	}

    /* Check status every 10 ms */
    DEMOD_L0_system_wait(10);
  }

  return blindLock;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_Check_BlindLock_state.
 * Check neverLock status. used for searching channels automatically
 *
 * @param *front_end 		[IN] LX_DEMOD_L2_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8   DEMOD_L2_Check_BlindLock_state   (LX_DEMOD_L2_Context *front_end)
{
	UINT8 return_code;
	UINT8 lock = 2;

	return_code = DEMOD_L1_GET_DD_BLIND_Status(front_end->demod);
	if (return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT("DEMOD_lock_to_carrier: DEMOD_L1_DD_STATUS error\n");
		return lock;
	}
	if(front_end->demod->rsp->blind_status.blindLock  == DEMOD_DD_BLIND_STATUS_RESPONSE_BLINDLOCK_LOCKED   )
	{
		lock = 1;

		DBB_PRINT("DEMOD_lock_to_carrier: locked on a %s signal\n", DEMOD_L1_API_StandardName(front_end->demod->rsp->dd_status.reply_operMod));
	}
	else if(front_end->demod->rsp->blind_status.blindLock  == DEMOD_DD_BLIND_STATUS_RESPONSE_BLINDLOCK_NOTLOCKED)
	{
		lock = 2;
		DBB_PRINT("No SIgnal detected !!\n");

	}
	else
	{
		lock = 0;
		//DBB_PRINT("Processing !!\n");
	}

	return lock;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_Set_Invert_Spectrum. (used only for satellite mode)
 * return the required invert_spectrum value depending on the settings.
 *
 * @param *front_end 			[IN] LX_DEMOD_L2_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8 DEMOD_L2_Set_Invert_Spectrum (LX_DEMOD_L2_Context *front_end)
{
	UINT8 inversion;
	inversion = 0; /* to avoid compile error */
	#ifdef    DEMOD_TERRESTRIAL_FRONT_END
	if (front_end->demod->media == DEMOD_DD_TERRESTRIAL)
	{
		 inversion = DEMOD_DD_MODE_PROP_SPECINV_NORMAL;
	}
	#endif /* DEMOD_TERRESTRIAL_FRONT_END */


#ifndef LG3307_API

	#ifdef    DEMOD_SATELLITE_FRONT_END
	if (front_end->demod->media == DEMOD_DD_SATELLITE  )
	{
		inversion = front_end->satellite_spectrum_inversion;

		#ifdef   DEMOD_UNICABLE_COMPATIBLE
		if (front_end->lnb_type == UNICABLE_LNB_TYPE_UNICABLE)
		{
		 	 if (front_end->unicable_spectrum_inversion) inversion = !inversion;
		}
		#endif /* DEMOD_UNICABLE_COMPATIBLE */
  	}
	#endif
#endif

  	return inversion;

}

/************************************************************************************************************************
  DEMOD_L2_Get_LockStatus function
  Use:        standard text retrieval function
              Used to retrieve the standard text used by the Si2169C
  Parameter:  standard, the value of the standard
************************************************************************************************************************/
UINT8  DEMOD_L2_Get_LockStatus(LX_DEMOD_L2_Context *frontend, UINT8 *pOperMode,  UINT8 *pFecLock)
{
	UINT8 retCode = 0;

	retCode = DEMOD_L1_GET_DD_Status(frontend->demod);

	if(NO_DEMOD_ERROR != retCode)
	{
		*pOperMode = DEMOD_DD_STATUS_RESPONSE_MODULATION_UNKNOWN ;
		*pFecLock = DEMOD_DD_STATUS_RESPONSE_LOCK_FEC_NO_LOCKED;
		return retCode;
	}

	*pOperMode = frontend->demod->rsp->dd_status.reply_operMod ;
	*pFecLock = frontend->demod->rsp->dd_status.lock_fec;

	return NO_DEMOD_ERROR;

}

#ifndef __EVAL_GUI__
 /************************************************************************************************************************
   DEMOD_L2_Get_OperMode function
   Use: 	   standard text retrieval function
			   Used to retrieve the standard text used by the Si2169C
   Parameter:  standard, the value of the standard
 ************************************************************************************************************************/
 UINT8	DEMOD_L2_Get_OperMode(LX_DEMOD_L2_Context *frontend, LX_DEMOD_OPER_MODE_T *reply_opmode)
 {
	 if(NO_DEMOD_ERROR != DEMOD_L1_GET_DD_Status(frontend->demod))
	 {
		 return ERROR_DEMOD_ERROR;
	 }

	 switch (frontend->demod->rsp->dd_status.reply_operMod)
	{
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_VSB:		*reply_opmode = LX_DEMOD_ATSC;	break;
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_QAM: 		*reply_opmode = LX_DEMOD_QAM;		break;
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_ISDBT: 		*reply_opmode = LX_DEMOD_ISDBT;	break;
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBT:		*reply_opmode = LX_DEMOD_DVBT;	break;
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBT2:		*reply_opmode = LX_DEMOD_DVBT2;	break;
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBC:		*reply_opmode = LX_DEMOD_DVBC;	break;
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBC2:		*reply_opmode = LX_DEMOD_DVBC2;	break;
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBS:		*reply_opmode = LX_DEMOD_DVBS;	break;
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBS2:		*reply_opmode = LX_DEMOD_DVBS2;	break;
		case	DEMOD_DD_STATUS_RESPONSE_MODULATION_DTMB:		*reply_opmode = LX_DEMOD_DTMB;	break;

		default :
			DEMOD_PRINT_ALWAYS("[DEMOD O18](%s,%d) LX_DEMOD_UNKNOWN_OPMODE!!!value : %02x\n",__F__, __L__, frontend->demod->rsp->dd_status.reply_operMod);
			return RET_ERROR;
	}
	
//	DBB_PRINT ("DEMOD_L2_Get_OperMode : 0x%02x\n",*reply_opmode );

	return NO_DEMOD_ERROR;
 
 }
#endif

 /************************************************************************************************************************
  NAME: DEMOD_L2_Status
  DESCRIPTION: Calls the DBB global status function (DD_STATUS) and then the standard-specific status functions
  Porting:    Remove the un-necessary functions calls, if any. (Checking the TPS status may not be required)

  Parameter:  Pointer to DEMOD Context
  Returns:    1 if the current modulation is valid, 0 otherwise
************************************************************************************************************************/
UINT8 DEMOD_L2_SignalStatus     (LX_DEMOD_L2_Context *frontend, LX_DEMOD_L2_SIG_STATUS *pSignalStatus)
{
	UINT8 return_code = NO_DEMOD_ERROR;
	SINT64  offsetFrq_KHz_val;

#ifndef __KERNEL__
	double calcValue = 0;
#endif

	pSignalStatus->ber = 0xffff;
	pSignalStatus->constellation = 0;
	pSignalStatus->if_agc = 0;
	pSignalStatus->mse_info = 0xffffffff;
	pSignalStatus->mse_info_eq = 0xffffffff;
	pSignalStatus->mse_info_demod = 0xffffffff;

	pSignalStatus->constPwr = 0;
	pSignalStatus->constPwr_eq = 0;
	pSignalStatus->offsetFrq_Hz = 0;
	pSignalStatus->operatingMode = 0;
	pSignalStatus->snr = 0;
	pSignalStatus->snr_eq = 0;
	pSignalStatus->snr_demod = 0;
	pSignalStatus->packetError = 0xffff;
	pSignalStatus->spInv = 0;
	pSignalStatus->demodLock = 0;
	pSignalStatus->bandwidth = 0;
	pSignalStatus->sym_rate = 0;
	pSignalStatus->signalQuality = 0;

#ifndef LG3307_API

	pSignalStatus->cell_id = 0;
	pSignalStatus->il_mode = 0;
	pSignalStatus->pn_const = 0;
	pSignalStatus->pn_mode = 0;
	pSignalStatus->carr_mode = 0;

#endif

	/* Call the demod global status function */
	return_code = DEMOD_L1_GET_DD_Status (frontend->demod);
	if(return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L1_GET_DD_Status error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}

	/* Call the standard-specific status function */
	switch (frontend->demod->rsp->dd_status.reply_operMod)
	{
	  case DEMOD_DD_STATUS_RESPONSE_MODULATION_VSB :
		{
	  		return_code = DEMOD_L1_GET_DD_VSB_Status  (frontend->demod );
			if(return_code != NO_DEMOD_ERROR)
			{
				DBB_PRINT ("DEMOD_L1_GET_DD_VSB_Status error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
				return return_code;
			}
			pSignalStatus->ber = frontend->demod->rsp->vsb_status.ber;
			pSignalStatus->constellation = frontend->demod->rsp->vsb_status.constellation;
			pSignalStatus->if_agc = frontend->demod->rsp->vsb_status.if_agc;
			pSignalStatus->mse_info = frontend->demod->rsp->vsb_status.mse_info;
			pSignalStatus->operatingMode = frontend->demod->rsp->vsb_status.op_mode;
			pSignalStatus->packetError = (UINT32)(frontend->demod->rsp->vsb_status.pe);
			pSignalStatus->spInv = frontend->demod->rsp->vsb_status.spInv;
			pSignalStatus->demodLock = frontend->demod->rsp->vsb_status.lock_fec;

			if(pSignalStatus->mse_info == 0)
			{
//				DBB_PRINT("Fail to get the MSE value(mse = %d) \n",pSignalStatus->mse_info);
				pSignalStatus->mse_info = 1;
			}

			offsetFrq_KHz_val = (frontend->demod->rsp->vsb_status.cfo & 0x800000) ? (0xffffffffff000000 | frontend->demod->rsp->vsb_status.cfo) : frontend->demod->rsp->vsb_status.cfo;
			pSignalStatus->offsetFrq_Hz =(SINT32) _DEMOD_do_div64_32((5381 * offsetFrq_KHz_val * 1000) , 8388608);	//Hz

			offsetFrq_KHz_val = (frontend->demod->rsp->vsb_status.sfo & 0x800000) ? (0xffffffffff000000 | frontend->demod->rsp->vsb_status.sfo) : frontend->demod->rsp->vsb_status.sfo;
			pSignalStatus->sam_offsetFrq_Hz = (SINT32)_DEMOD_do_div64_32 ((5381 * offsetFrq_KHz_val * 1000) , 8388608); //Hz

			pSignalStatus->constPwr = 21504; // (1024 * 21)

#ifdef __KERNEL__
			pSignalStatus->snr  = 0;
#else
			calcValue =  (double)(pSignalStatus->constPwr) / (double)(pSignalStatus->mse_info);
			pSignalStatus->snr  = (UINT32)(10 * log10 (calcValue));
#endif

	  	}
	    	break;

	  case DEMOD_DD_STATUS_RESPONSE_MODULATION_QAM:
		{
	  		return_code = DEMOD_L1_GET_DD_QAM_Status  (frontend->demod );
			if(return_code != NO_DEMOD_ERROR)
			{
				DBB_PRINT ("DEMOD_L1_GET_DD_QAM_Status error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
				return return_code;
			}
			pSignalStatus->ber = frontend->demod->rsp->qam_status.ber;
			pSignalStatus->constellation = frontend->demod->rsp->qam_status.constellation;
			pSignalStatus->if_agc = frontend->demod->rsp->qam_status.if_agc;
			pSignalStatus->mse_info = frontend->demod->rsp->qam_status.mse_info;
			pSignalStatus->operatingMode = frontend->demod->rsp->qam_status.op_mode;
			pSignalStatus->packetError = (UINT32)(frontend->demod->rsp->qam_status.pe);
			pSignalStatus->spInv = frontend->demod->rsp->qam_status.spInv;
			pSignalStatus->demodLock = frontend->demod->rsp->qam_status.lock_fec;
			pSignalStatus->sym_rate = frontend->demod->rsp->qam_status.sym_rate;

			offsetFrq_KHz_val = (frontend->demod->rsp->qam_status.cfo & 0x00800000) ? (frontend->demod->rsp->qam_status.cfo | 0xffffffffff000000) : frontend->demod->rsp->qam_status.cfo;
			pSignalStatus->offsetFrq_Hz = offsetFrq_KHz_val * 1000;	//Hz

			if(pSignalStatus->mse_info == 0)
			{
//				DBB_PRINT("Fail to get the MSE value(mse = %d) \n",pSignalStatus->mse_info);
				pSignalStatus->mse_info = 1;
			}

			if(pSignalStatus->constellation == DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64)  pSignalStatus->constPwr = 688128;
			else pSignalStatus->constPwr = 696320;

			offsetFrq_KHz_val = (frontend->demod->rsp->qam_status.sfo & 0x800000) ? (0xffffffffff000000 | frontend->demod->rsp->qam_status.sfo) : frontend->demod->rsp->qam_status.sfo;
			pSignalStatus->sam_offsetFrq_Hz = (SINT32) _DEMOD_do_div64_32 ((offsetFrq_KHz_val * pSignalStatus->sym_rate*1000), 8388608);	//Hz

#ifdef __KERNEL__
			pSignalStatus->snr  = 0;
#else
			calcValue =  (double)(pSignalStatus->constPwr) / (double)(pSignalStatus->mse_info);
			pSignalStatus->snr  = (UINT32)(10 * log10 (calcValue));
#endif

		}
	    	break;

	  case DEMOD_DD_STATUS_RESPONSE_MODULATION_ATSC3 :
		{
#ifndef __KERNEL__
			UINT8 		i;
			UINT32 		sn_atsc3_p1 = 0;
			SINT32 		berSQI = 1;
			SINT32 		snRel;
			//SINT32 		tempQual = 0;
			UINT32		ber = 0;
#endif
		  	return_code = DEMOD_L1_GET_DD_ATSC3_Status  (frontend->demod );
			if(return_code != NO_DEMOD_ERROR)
			{
				DBB_PRINT ("DEMOD_L1_GET_DD_ATSC3_Status error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
				return return_code;
			}
			pSignalStatus->ber = frontend->demod->rsp->atsc3_status.ber;
			pSignalStatus->if_agc = frontend->demod->rsp->atsc3_status.if_agc;
			pSignalStatus->mse_info = frontend->demod->rsp->atsc3_status.mse_info;
			pSignalStatus->operatingMode = frontend->demod->rsp->atsc3_status.op_mode;
			pSignalStatus->packetError = (UINT32)(frontend->demod->rsp->atsc3_status.pe);
			pSignalStatus->spInv = frontend->demod->rsp->atsc3_status.spInv;
			pSignalStatus->demodLock = frontend->demod->rsp->atsc3_status.lock_carr;
			pSignalStatus->lock_l1b= frontend->demod->rsp->atsc3_status.lock_l1b;
			pSignalStatus->lock_l1d= frontend->demod->rsp->atsc3_status.lock_l1d;
			pSignalStatus->bandwidth = frontend->demod->rsp->atsc3_status.bandwidth;
			pSignalStatus->guardInterval 	= frontend->demod->rsp->atsc3_status.gi;
			pSignalStatus->fftMode 		= frontend->demod->rsp->atsc3_status.fft_mode;
			pSignalStatus->num_PLP 		= frontend->demod->rsp->atsc3_status.num_plp;
			frontend->demod->cmd->atsc3_plp_info.plp_index = frontend->set_PLP_ID;
			if(DEMOD_L2_SendCommand(frontend, DEMOD_DD_ATSC3_PLP_INFO_CMD_CODE) == NO_DEMOD_ERROR)
			{
				pSignalStatus->codeRate = frontend->demod->rsp->atsc3_plp_info.l1d_plp_cr;
				pSignalStatus->constellation = frontend->demod->rsp->atsc3_plp_info.l1d_plp_mod;
			}

			if(pSignalStatus->mse_info == 0)
			{
//				DBB_PRINT("Fail to get the MSE value(mse = %d) \n",pSignalStatus->mse_info);
				pSignalStatus->mse_info = 1;
			}

			offsetFrq_KHz_val = (frontend->demod->rsp->atsc3_status.cfo & 0x800000) ? (0xffffffffff000000 | frontend->demod->rsp->atsc3_status.cfo) : frontend->demod->rsp->atsc3_status.cfo;
			pSignalStatus->offsetFrq_Hz = (SINT32) _DEMOD_do_div64_32((offsetFrq_KHz_val * 6912 * 1000), 8388608); //Hz

			offsetFrq_KHz_val = (frontend->demod->rsp->atsc3_status.sfo & 0x800000) ? (0xffffffffff000000 | frontend->demod->rsp->atsc3_status.sfo) : frontend->demod->rsp->atsc3_status.sfo;
			pSignalStatus->sam_offsetFrq_Hz = (SINT32) _DEMOD_do_div64_32((offsetFrq_KHz_val * 6912 * 1000), 8388608); //Hz

			pSignalStatus->constPwr = 65536;

#ifdef __KERNEL__
			pSignalStatus->snr  = 0;

#else
			calcValue =  (double)(pSignalStatus->constPwr) / (double)(pSignalStatus->mse_info);
			pSignalStatus->snr  = (UINT32)(10 * log10 (calcValue));
#endif

#ifndef __KERNEL__
			ber = frontend->demod->rsp->atsc3_status.ber;
			for(i = 0; i < sizeof(SqiCnAtsc3P1) / sizeof(LX_DEMOD_SQI_CN_ATSC3P1_T); i++)
			{
				if ( (frontend->demod->rsp->atsc3_plp_info.l1d_plp_mod == SqiCnAtsc3P1[i].constel) && (frontend->demod->rsp->atsc3_plp_info.l1d_plp_cr == SqiCnAtsc3P1[i].code_rate))
				{
					sn_atsc3_p1 = SqiCnAtsc3P1[i].sn_ref;
					break;
				}
			}

			snRel = (SINT32)((pSignalStatus->snr * 100) - sn_atsc3_p1);
			ber = frontend->demod->rsp->atsc3_status.ber ;

			if ( ber < 5000 )			// BER > 5x1e-2
			{
				berSQI = 100;
			}
			else  if ( ber > 99900 )	//  BER > 1e-1
			{
				berSQI = 0 ;
			}
			else
			{
				berSQI = (SINT32)((500 - 100 *  (log10 ((double)ber)))*100)/130 ;
			}


			if (snRel > (3* 100) )
			{
				pSignalStatus->signalQuality = berSQI + 20;
			}

			else  if ( snRel <= (-5 * 100) )
			{
				pSignalStatus->signalQuality = 10; ;
			}
			else
			{
				pSignalStatus->signalQuality = berSQI + 15; ;
			}

			if(pSignalStatus->signalQuality > 100) pSignalStatus->signalQuality = 100;

#endif

		}
		break;


#ifndef LG3307_API

	  case DEMOD_DD_STATUS_RESPONSE_MODULATION_ISDBT :
		{
			UINT8 segNum_a;
			UINT8 segNum_b;
			UINT8 segNum_c;

	  		return_code = DEMOD_L1_GET_DD_ISDBT_Status  (frontend->demod );
			if(return_code != NO_DEMOD_ERROR)
			{
				DBB_PRINT ("DEMOD_L1_GET_DD_ISDBT_Status error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
				return return_code;
			}

	  		return_code = DEMOD_L1_GET_DD_ISDBT_TMCC_Info (frontend->demod );
			if(return_code != NO_DEMOD_ERROR)
			{
				DBB_PRINT ("DEMOD_L1_GET_DD_ISDBT_Status error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
				return return_code;
			}

			segNum_a = frontend->demod->rsp->isdbt_tmcc_info.onsega;
			segNum_b = frontend->demod->rsp->isdbt_tmcc_info.onsegb;
			segNum_c = frontend->demod->rsp->isdbt_tmcc_info.onsegc;

			pSignalStatus->ber = frontend->demod->rsp->isdbt_status.ber;
			pSignalStatus->if_agc = frontend->demod->rsp->isdbt_status.if_agc;

			
			pSignalStatus->mse_info_eq = frontend->demod->rsp->isdbt_status.mse_info; // 171123
			if(pSignalStatus->mse_info_eq == 0)
			{
//				DBB_PRINT("Fail to get the MSE_EQ value(mse_eq = %d) \n",pSignalStatus->mse_info_eq);
				pSignalStatus->mse_info_eq = 1;
			}
			pSignalStatus->constPwr_eq = 16384;
			pSignalStatus->constPwr = pSignalStatus->constPwr_eq; 
			pSignalStatus->mse_info = pSignalStatus->mse_info_eq;				
			
			
			if(frontend->demod->i2c->chipVer >= M16P3)
			{
				pSignalStatus->mse_info_demod = frontend->demod->rsp->isdbt_status.mse_info_demod; // 171123
				if(pSignalStatus->mse_info_demod == 0)
				{
		//			DBB_PRINT("Fail to get the MSE_DEMOD value(mse_demod = %d) \n",pSignalStatus->mse_info_demod);
					pSignalStatus->mse_info_demod = 1;				
				}
				pSignalStatus->constPwr = 3024; 
				pSignalStatus->mse_info = pSignalStatus->mse_info_demod;
			}

			pSignalStatus->operatingMode = frontend->demod->rsp->isdbt_status.op_mode;
			pSignalStatus->packetError = (UINT32)(frontend->demod->rsp->isdbt_status.pe);
			pSignalStatus->spInv = frontend->demod->rsp->isdbt_status.spInv;
			pSignalStatus->demodLock = frontend->demod->rsp->isdbt_status.lock_fec;

			if((segNum_a > segNum_b) && (segNum_a > segNum_c))
			{
				pSignalStatus->constellation = frontend->demod->rsp->isdbt_tmcc_info.oqama;
			}
			else if((segNum_b > segNum_a) && (segNum_b > segNum_c))
			{
				pSignalStatus->constellation = frontend->demod->rsp->isdbt_tmcc_info.oqamb;

			}
 			else if((segNum_c > segNum_a) && (segNum_c > segNum_b))
			{
				pSignalStatus->constellation =frontend->demod->rsp->isdbt_tmcc_info.oqamc;

			}
			else
			{
				pSignalStatus->constellation = DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_UNKNOWN;
			}


			offsetFrq_KHz_val = (frontend->demod->rsp->isdbt_status.cfo & 0x00800000) ? (frontend->demod->rsp->isdbt_status.cfo | 0xffffffffff000000) : frontend->demod->rsp->isdbt_status.cfo;
			pSignalStatus->offsetFrq_Hz = (SINT32) _DEMOD_do_div64_32((offsetFrq_KHz_val * 8127 * 1000), 8388608); //Hz

			offsetFrq_KHz_val = (frontend->demod->rsp->isdbt_status.sfo & 0x800000) ? (0xffffffffff000000 | frontend->demod->rsp->isdbt_status.sfo) : frontend->demod->rsp->isdbt_status.sfo;
			pSignalStatus->sam_offsetFrq_Hz = (SINT32) _DEMOD_do_div64_32((offsetFrq_KHz_val * 8127 * 1000), 8388608); //Hz

			frontend->detected_rf = frontend->centerFrq + pSignalStatus->offsetFrq_Hz;

			//if(pSignalStatus->constellation == DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16)  pSignalStatus->constPwr = 655360;
			//else pSignalStatus->constPwr = 688128;
			

#ifdef __KERNEL__
			
			pSignalStatus->snr_eq  = 0;
			pSignalStatus->snr_demod = 0;
			
#else		
			calcValue =  (double)(pSignalStatus->constPwr_eq) / (double)(pSignalStatus->mse_info_eq);

			if(calcValue < 0.1)			pSignalStatus->snr_eq = -10;
			else						pSignalStatus->snr_eq = (UINT32)(10*log10(calcValue));		
			calcValue =  (double)(pSignalStatus->constPwr) / (double)(pSignalStatus->mse_info_demod);

			if(calcValue < 0.1)			pSignalStatus->snr_demod = -10;
			else						pSignalStatus->snr_demod = (UINT32)(10*log10(calcValue));		
#endif
			pSignalStatus->snr = pSignalStatus->snr_demod;



		}
	    	break;

	  case DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBT :
		{

	  		return_code = DEMOD_L1_GET_DD_DVBT_Status  (frontend->demod);
			if(return_code != NO_DEMOD_ERROR)
			{
				DBB_PRINT ("DEMOD_L1_GET_DD_DVBT_Status error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
				return return_code;
			}
			pSignalStatus->ber = frontend->demod->rsp->dvbt_status.ber;
			pSignalStatus->constellation = frontend->demod->rsp->dvbt_status.constellation;
			pSignalStatus->if_agc = frontend->demod->rsp->dvbt_status.if_agc;

			pSignalStatus->mse_info_eq = frontend->demod->rsp->dvbt_status.mse_info;
			pSignalStatus->mse_info_demod = frontend->demod->rsp->dvbt_status.mse_info_demod;

			pSignalStatus->operatingMode = frontend->demod->rsp->dvbt_status.op_mode;
			pSignalStatus->packetError = (UINT32)(frontend->demod->rsp->dvbt_status.pe);
			pSignalStatus->spInv = frontend->demod->rsp->dvbt_status.spInv;
			pSignalStatus->demodLock = frontend->demod->rsp->dvbt_status.lock_fec;
			pSignalStatus->cell_id = frontend->demod->rsp->dvbt_status.cell_id;
			pSignalStatus->bandwidth = frontend->demod->prop->dd_mode.bw;
			pSignalStatus->guardInterval 	= frontend->demod->rsp->dvbt_status.gi;
			pSignalStatus->fftMode 		= frontend->demod->rsp->dvbt_status.fft_mode;
			pSignalStatus->hierarchy		= frontend->demod->rsp->dvbt_status.hierarchy;
			pSignalStatus->hierarchy_sel	= frontend->demod->rsp->dvbt_status.hierarchy_sel;

			if(pSignalStatus->hierarchy_sel == DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_SEL_HP)
			{
				pSignalStatus->codeRate 		= frontend->demod->rsp->dvbt_status.hp_cr;
			}
			else
			{
				pSignalStatus->codeRate 		= frontend->demod->rsp->dvbt_status.lp_cr;
			}
			if(pSignalStatus->mse_info_eq == 0)
			{
//				DBB_PRINT("Fail to get the MSE_EQ value(mse_eq = %d) \n",pSignalStatus->mse_info_eq);
				pSignalStatus->mse_info_eq = 1;
			}
				
			if(pSignalStatus->mse_info_demod == 0)
			{
//				DBB_PRINT("Fail to get the MSE_DEMOD value(mse_demod = %d) \n",pSignalStatus->mse_info_demod);
				pSignalStatus->mse_info_demod = 1;				
			}
				
			pSignalStatus->constPwr_eq = 16384;				
			pSignalStatus->constPwr = 3024; 
			pSignalStatus->mse_info = pSignalStatus->mse_info_demod;
			

			offsetFrq_KHz_val = (frontend->demod->rsp->dvbt_status.cfo & 0x00800000) ? (frontend->demod->rsp->dvbt_status.cfo | 0xffffffffff000000) : frontend->demod->rsp->dvbt_status.cfo;
			pSignalStatus->offsetFrq_Hz = (SINT32) _DEMOD_do_div64_32((offsetFrq_KHz_val * pSignalStatus->bandwidth * 1143 * 1000), 8388608); //Hz

			offsetFrq_KHz_val = (frontend->demod->rsp->dvbt_status.sfo & 0x800000) ? (0xffffffffff000000 | frontend->demod->rsp->dvbt_status.sfo) : frontend->demod->rsp->dvbt_status.sfo;
			pSignalStatus->sam_offsetFrq_Hz = (SINT32) _DEMOD_do_div64_32((offsetFrq_KHz_val * pSignalStatus->bandwidth * 1143 * 1000), 8388608); //Hz

			frontend->detected_rf = frontend->centerFrq + pSignalStatus->offsetFrq_Hz;


		
#ifdef __KERNEL__
			
			pSignalStatus->snr_eq  = 0;
			pSignalStatus->snr_demod = 0;
			
#else		
			calcValue =  (double)(pSignalStatus->constPwr_eq) / (double)(pSignalStatus->mse_info_eq);

			if(calcValue < 0.1)			pSignalStatus->snr_eq = -10;
			else						pSignalStatus->snr_eq = (UINT32)(10*log10(calcValue));		
			calcValue =  (double)(pSignalStatus->constPwr) / (double)(pSignalStatus->mse_info_demod);

			if(calcValue < 0.1)			pSignalStatus->snr_demod = -10;
			else						pSignalStatus->snr_demod = (UINT32)(10*log10(calcValue));		
#endif
			pSignalStatus->snr = pSignalStatus->snr_demod;
		}
	    	break;

	  case DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBT2 :
		{
	  		return_code = DEMOD_L1_GET_DD_DVBT2_Status   (frontend->demod);
			if(return_code != NO_DEMOD_ERROR)
			{
				DBB_PRINT ("DEMOD_L1_GET_DD_DVBT2_Status error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
				return return_code;
			}
			pSignalStatus->ber = frontend->demod->rsp->dvbt2_status.ber;
			pSignalStatus->constellation = frontend->demod->rsp->dvbt2_status.constellation;
			pSignalStatus->if_agc = frontend->demod->rsp->dvbt2_status.if_agc;

			pSignalStatus->mse_info_eq = frontend->demod->rsp->dvbt2_status.mse_info;
			pSignalStatus->mse_info_demod = frontend->demod->rsp->dvbt2_status.mse_info_demod;

			pSignalStatus->operatingMode 		= frontend->demod->rsp->dvbt2_status.op_mode;
			pSignalStatus->packetError 			= (UINT32)(frontend->demod->rsp->dvbt2_status.pe);
			pSignalStatus->spInv 				= frontend->demod->rsp->dvbt2_status.spInv;
			pSignalStatus->demodLock 			= frontend->demod->rsp->dvbt2_status.lock_fec;
			pSignalStatus->guardInterval 		= frontend->demod->rsp->dvbt2_status.gi;
			pSignalStatus->codeRate 			= frontend->demod->rsp->dvbt2_status.cr;
			pSignalStatus->fftMode 				= frontend->demod->rsp->dvbt2_status.fft_mode;
			pSignalStatus->offsetFrq_Hz 		= (frontend->demod->rsp->dvbt2_status.cfo & 0x800000) ? (0xff000000 | frontend->demod->rsp->dvbt2_status.cfo) : frontend->demod->rsp->dvbt2_status.cfo;
			pSignalStatus->bandwidth 			= frontend->demod->prop->dd_mode.bw;
			pSignalStatus->num_PLP 				= frontend->demod->rsp->dvbt2_status.num_plp;
			pSignalStatus->bw_Ext				= frontend->demod->rsp->dvbt2_status.bw_ext;
			pSignalStatus->current_plp_id		= frontend->demod->rsp->dvbt2_status.current_plp_id;
			pSignalStatus->cell_id		= frontend->demod->rsp->dvbt2_status.cell_id;


			if(pSignalStatus->mse_info_eq == 0)
			{
//				DBB_PRINT("Fail to get the MSE_EQ value(mse_eq = %d) \n",pSignalStatus->mse_info_eq);
				pSignalStatus->mse_info_eq = 1;
			}
				
			if(pSignalStatus->mse_info_demod == 0)
			{
//				DBB_PRINT("Fail to get the MSE_DEMOD value(mse_demod = %d) \n",pSignalStatus->mse_info_demod);
				pSignalStatus->mse_info_demod = 1;				
			}
				
			pSignalStatus->constPwr_eq = 16384;				
			pSignalStatus->constPwr = 3024; 
			pSignalStatus->mse_info = pSignalStatus->mse_info_demod;
			
			offsetFrq_KHz_val = (frontend->demod->rsp->dvbt2_status.cfo & 0x00800000) ? (frontend->demod->rsp->dvbt2_status.cfo | 0xffffffffff000000) : frontend->demod->rsp->dvbt2_status.cfo;
			pSignalStatus->offsetFrq_Hz = (SINT32) _DEMOD_do_div64_32((offsetFrq_KHz_val * pSignalStatus->bandwidth * 1143 * 1000), 8388608); //Hz

			offsetFrq_KHz_val = (frontend->demod->rsp->dvbt2_status.sfo & 0x800000) ? (0xffffffffff000000 | frontend->demod->rsp->dvbt2_status.sfo) : frontend->demod->rsp->dvbt2_status.sfo;
			pSignalStatus->sam_offsetFrq_Hz = (SINT32) _DEMOD_do_div64_32((offsetFrq_KHz_val * pSignalStatus->bandwidth * 1143 * 1000), 8388608); //Hz

			frontend->detected_rf = frontend->centerFrq + pSignalStatus->offsetFrq_Hz;

			pSignalStatus->constPwr_eq = 16384;
			
			
#ifdef __KERNEL__
			pSignalStatus->snr_eq  = 0;
			pSignalStatus->snr_demod = 0;
#else		
			calcValue =  (double)(pSignalStatus->constPwr_eq) / (double)(pSignalStatus->mse_info_eq);

			if(calcValue < 0.1)			pSignalStatus->snr_eq = -10;
			else						pSignalStatus->snr_eq = (UINT32)(10*log10(calcValue));		
			calcValue =  (double)(pSignalStatus->constPwr) / (double)(pSignalStatus->mse_info_demod);

			if(calcValue < 0.1)			pSignalStatus->snr_demod = -10;
			else						pSignalStatus->snr_demod = (UINT32)(10*log10(calcValue));		
#endif
			pSignalStatus->snr = pSignalStatus->snr_demod;

			
			

		}
	    	break;

	    case DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBC :
		{
	  		return_code = DEMOD_L1_GET_DD_DVBC_Status  (frontend->demod);
			if(return_code != NO_DEMOD_ERROR)
			{
				DBB_PRINT ("DEMOD_L1_GET_DD_DVBC_Status error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
				return return_code;
			}
			pSignalStatus->ber = frontend->demod->rsp->dvbc_status.ber;
			pSignalStatus->constellation = frontend->demod->rsp->dvbc_status.constellation;
			pSignalStatus->if_agc = frontend->demod->rsp->dvbc_status.if_agc;
			pSignalStatus->mse_info = frontend->demod->rsp->dvbc_status.mse_info;
			pSignalStatus->operatingMode = frontend->demod->rsp->dvbc_status.op_mode;
			pSignalStatus->packetError = (UINT32)(frontend->demod->rsp->dvbc_status.pe);
			pSignalStatus->spInv = frontend->demod->rsp->dvbc_status.spInv;
			pSignalStatus->sym_rate = frontend->demod->rsp->dvbc_status.sym_rate;
			pSignalStatus->demodLock = frontend->demod->rsp->dvbc_status.lock_fec;

			if(pSignalStatus->mse_info == 0)
			{
//				DBB_PRINT("Fail to get the MSE value(mse = %d) \n",pSignalStatus->mse_info);
				pSignalStatus->mse_info = 1;
			}

			if(pSignalStatus->constellation == DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16)  pSignalStatus->constPwr = 655360;
			else if(pSignalStatus->constellation == DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM32)  pSignalStatus->constPwr = 737280;
			else if(pSignalStatus->constellation == DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64)  pSignalStatus->constPwr = 688128;
			else if(pSignalStatus->constellation == DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM128)  pSignalStatus->constPwr = 755712;
			else pSignalStatus->constPwr = 696320;

			offsetFrq_KHz_val = (frontend->demod->rsp->dvbc_status.cfo & 0x800000) ? (frontend->demod->rsp->dvbc_status.cfo | 0xffffffffff000000) : frontend->demod->rsp->dvbc_status.cfo;
			pSignalStatus->offsetFrq_Hz = (SINT32) (offsetFrq_KHz_val * 1000);	//Hz

			offsetFrq_KHz_val = (frontend->demod->rsp->dvbc_status.sfo & 0x800000) ? (0xffffffffff000000 | frontend->demod->rsp->dvbc_status.sfo) : frontend->demod->rsp->dvbc_status.sfo;
			pSignalStatus->sam_offsetFrq_Hz = (SINT32) _DEMOD_do_div64_32((offsetFrq_KHz_val * pSignalStatus->sym_rate*1000) , 8388608);	//Hz

			frontend->detected_rf = frontend->centerFrq + pSignalStatus->offsetFrq_Hz;

#ifdef __KERNEL__
			pSignalStatus->snr = 0;
#else
			calcValue =  (double)(pSignalStatus->constPwr) / (double)(pSignalStatus->mse_info);
			pSignalStatus->snr  = (UINT32)(10 * log10 (calcValue));
#endif
		}
	    	break;
	  case DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBC2 :
		{
	  		return_code = DEMOD_L1_GET_DD_DVBC2_Status   (frontend->demod );
			if(return_code != NO_DEMOD_ERROR)
			{
				DBB_PRINT ("DEMOD_L1_GET_DD_DVBC2_Status error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
				return return_code;
			}
			pSignalStatus->ber = frontend->demod->rsp->dvbc2_status.ber;
			pSignalStatus->constellation = frontend->demod->rsp->dvbc2_status.constellation;
			pSignalStatus->if_agc = frontend->demod->rsp->dvbc2_status.if_agc;
			pSignalStatus->mse_info = frontend->demod->rsp->dvbc2_status.mse_info;
			pSignalStatus->operatingMode = frontend->demod->rsp->dvbc2_status.op_mode;
			pSignalStatus->packetError = (UINT32)(frontend->demod->rsp->dvbc2_status.pe);
			pSignalStatus->spInv = frontend->demod->rsp->dvbc2_status.spInv;
			pSignalStatus->demodLock = frontend->demod->rsp->dvbc2_status.lock_fec;

			pSignalStatus->offsetFrq_Hz = (frontend->demod->rsp->dvbc2_status.cfo & 0x800000) ? (0xff000000 | frontend->demod->rsp->dvbc2_status.cfo) : frontend->demod->rsp->dvbc2_status.cfo;
			frontend->detected_rf = frontend->centerFrq + pSignalStatus->offsetFrq_Hz;

			pSignalStatus->snr = 0;
		}
	    	break;
	  case DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBS :
		{
	  		return_code = DEMOD_L1_GET_DD_DVBS_Status  (frontend->demod);
			if(return_code != NO_DEMOD_ERROR)
			{
				DBB_PRINT ("DEMOD_L1_GET_DD_DVBS_Status error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
				return return_code;
			}
			pSignalStatus->ber = frontend->demod->rsp->dvbs_status.ber;
			pSignalStatus->constellation = frontend->demod->rsp->dvbs_status.constellation;
			pSignalStatus->if_agc = frontend->demod->rsp->dvbs_status.if_agc;
			pSignalStatus->mse_info = frontend->demod->rsp->dvbs_status.mse_info;
			pSignalStatus->operatingMode = frontend->demod->rsp->dvbs_status.op_mode;
			pSignalStatus->packetError = (UINT32)(frontend->demod->rsp->dvbs_status.pe);
			pSignalStatus->spInv = frontend->demod->rsp->dvbs_status.spInv;
			pSignalStatus->demodLock = frontend->demod->rsp->dvbs_status.lock_fec;
			pSignalStatus->sym_rate = frontend->demod->rsp->dvbs_status.sym_rate;
			pSignalStatus->codeRate =  frontend->demod->rsp->dvbs_status.cr;

			if(pSignalStatus->mse_info == 0)
			{
//				DBB_PRINT("Fail to get the MSE value(mse = %d) \n",pSignalStatus->mse_info);
				pSignalStatus->mse_info = 1;
			}

			pSignalStatus->constPwr = 1024;

			offsetFrq_KHz_val = (frontend->demod->rsp->dvbs_status.cfo & 0x800000) ? (0xffffffffff000000 | frontend->demod->rsp->dvbs_status.cfo) : frontend->demod->rsp->dvbs_status.cfo;
			pSignalStatus->offsetFrq_Hz = (SINT32) _DEMOD_do_div64_32 ((offsetFrq_KHz_val * pSignalStatus->sym_rate*1000), 8388608);	//Hz

			offsetFrq_KHz_val = (frontend->demod->rsp->dvbs_status.sfo & 0x800000) ? (0xffffffffff000000 | frontend->demod->rsp->dvbs_status.sfo) : frontend->demod->rsp->dvbs_status.sfo;
			pSignalStatus->sam_offsetFrq_Hz = (SINT32) _DEMOD_do_div64_32 ((offsetFrq_KHz_val * pSignalStatus->sym_rate*1000), 8388608);	//Hz

			frontend->detected_rf = frontend->centerFrq + pSignalStatus->offsetFrq_Hz;

#ifdef __KERNEL__
			pSignalStatus->snr  = 0;
#else
			calcValue =  (double)(pSignalStatus->constPwr) / (double)(pSignalStatus->mse_info);
			pSignalStatus->snr  = (UINT32)(10 * log10 (calcValue));
#endif

		}
	    	break;

	  case DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBS2:
		{
	  		return_code = DEMOD_L1_GET_DD_DVBS2_Status  (frontend->demod);
			if(return_code != NO_DEMOD_ERROR)
			{
				DBB_PRINT ("DEMOD_L1_GET_DD_DVBS2_Status error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
				return return_code;
			}
			pSignalStatus->ber = frontend->demod->rsp->dvbs2_status.ber;
			pSignalStatus->constellation = frontend->demod->rsp->dvbs2_status.constellation;
			pSignalStatus->if_agc = frontend->demod->rsp->dvbs2_status.if_agc;
			pSignalStatus->mse_info = frontend->demod->rsp->dvbs2_status.mse_info;
			pSignalStatus->operatingMode = frontend->demod->rsp->dvbs2_status.op_mode;
			pSignalStatus->packetError = (UINT32)(frontend->demod->rsp->dvbs2_status.pe);
			pSignalStatus->spInv = frontend->demod->rsp->dvbs2_status.spInv;
			pSignalStatus->demodLock = frontend->demod->rsp->dvbs2_status.lock_fec;
			pSignalStatus->sym_rate =  frontend->demod->rsp->dvbs2_status.sym_rate;
			pSignalStatus->codeRate =  frontend->demod->rsp->dvbs2_status.cr;
			pSignalStatus->pp =  frontend->demod->rsp->dvbs2_status.pp;

			if(pSignalStatus->mse_info == 0)
			{
//				DBB_PRINT("Fail to get the MSE value(mse = %d) \n",pSignalStatus->mse_info);
				pSignalStatus->mse_info = 1;
			}

			pSignalStatus->constPwr = 1024;

			offsetFrq_KHz_val = (frontend->demod->rsp->dvbs2_status.cfo & 0x800000) ? (0xffffffffff000000 | frontend->demod->rsp->dvbs2_status.cfo) : frontend->demod->rsp->dvbs2_status.cfo;
			pSignalStatus->offsetFrq_Hz = (SINT32) _DEMOD_do_div64_32 ((offsetFrq_KHz_val * pSignalStatus->sym_rate*1000), 8388608);	//Hz

			offsetFrq_KHz_val = (frontend->demod->rsp->dvbs2_status.sfo & 0x800000) ? (0xffffffffff000000 | frontend->demod->rsp->dvbs2_status.sfo) : frontend->demod->rsp->dvbs2_status.sfo;
			pSignalStatus->sam_offsetFrq_Hz = (SINT32) _DEMOD_do_div64_32 ((offsetFrq_KHz_val * pSignalStatus->sym_rate*1000), 8388608);	//Hz

			frontend->detected_rf = frontend->centerFrq + pSignalStatus->offsetFrq_Hz;

#ifdef __KERNEL__
			pSignalStatus->snr = 0;
#else
			calcValue =  (double)(pSignalStatus->constPwr) / (double)(pSignalStatus->mse_info);
			pSignalStatus->snr  = (UINT32)(10 * log10 (calcValue));
#endif
		}
	    	break;

	 case DEMOD_DD_STATUS_RESPONSE_MODULATION_DTMB :
		{
	  		return_code = DEMOD_L1_GET_DD_DTMB_Status  (frontend->demod );
			if(return_code != NO_DEMOD_ERROR)
			{
				DBB_PRINT ("DEMOD_L1_GET_DD_DTMB_Status error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
				return return_code;
			}
			pSignalStatus->ber = frontend->demod->rsp->dtmb_status.ber;
			pSignalStatus->constellation = frontend->demod->rsp->dtmb_status.constellation;
			pSignalStatus->if_agc = frontend->demod->rsp->dtmb_status.if_agc;
			pSignalStatus->mse_info = frontend->demod->rsp->dtmb_status.mse_info;
			pSignalStatus->operatingMode = frontend->demod->rsp->dtmb_status.op_mode;
			pSignalStatus->packetError = (UINT32)(frontend->demod->rsp->dtmb_status.pe);
			pSignalStatus->spInv = frontend->demod->rsp->dtmb_status.spInv;
			pSignalStatus->carr_mode = frontend->demod->rsp->dtmb_status.carr_mode;
			pSignalStatus->il_mode = frontend->demod->rsp->dtmb_status.il_mode;
			pSignalStatus->pn_const = frontend->demod->rsp->dtmb_status.pn_const;
			pSignalStatus->pn_mode = frontend->demod->rsp->dtmb_status.pn_mode;
			pSignalStatus->codeRate = frontend->demod->rsp->dtmb_status.cr;
			pSignalStatus->demodLock = frontend->demod->rsp->dd_status.lock_fec;

			if(pSignalStatus->mse_info == 0)
			{
//				DBB_PRINT("Fail to get the MSE value(mse = %d) \n",pSignalStatus->mse_info);
				pSignalStatus->mse_info = 1;
			}

			if(pSignalStatus->carr_mode == 0)	//SC
				pSignalStatus->constPwr = 65536;
			else
				pSignalStatus->constPwr = 12096;

			offsetFrq_KHz_val = (frontend->demod->rsp->dtmb_status.cfo & 0x800000) ? (0xffffffffff000000 | frontend->demod->rsp->dtmb_status.cfo) : frontend->demod->rsp->dtmb_status.cfo;
			pSignalStatus->offsetFrq_Hz =(SINT32) _DEMOD_do_div64_32((7560 * offsetFrq_KHz_val * 1000) , 8388608);	//Hz

			offsetFrq_KHz_val = (frontend->demod->rsp->dtmb_status.sfo & 0x800000) ? (0xffffffffff000000 | frontend->demod->rsp->dtmb_status.sfo) : frontend->demod->rsp->dtmb_status.sfo;
			pSignalStatus->sam_offsetFrq_Hz = (SINT32)_DEMOD_do_div64_32 ((7560 * offsetFrq_KHz_val * 1000) , 8388608); //Hz
			
#ifdef __KERNEL__
			pSignalStatus->snr  = 0;
#else
			calcValue =  (double)(pSignalStatus->constPwr) / (double)(pSignalStatus->mse_info);
			pSignalStatus->snr  = (UINT32)(10 * log10 (calcValue));
#endif
	  	}
	    	break;

#endif
	  default :
		{
	  		return ERROR_DEMOD_ERROR;
		}
	    	break;
	}

	return NO_DEMOD_ERROR;

}

/************************************************************************************************************************
  DEMOD_L2_SendCommand function
  Use:        Sends commands
  Parameter:  standard, the value of the standard
************************************************************************************************************************/
UINT8  DEMOD_L2_SendCommand(LX_DEMOD_L2_Context *frontend, UINT32 cmd_code)
{
	return DEMOD_L1_SendCommand2(frontend->demod, cmd_code);

}
/************************************************************************************************************************
  DEMOD_L2_Set_Property function
  Use:        Sets up property
  Parameter:  standard, the value of the standard
************************************************************************************************************************/
UINT8  DEMOD_L2_Set_Property(LX_DEMOD_L2_Context *frontend, UINT32 prop_code)
{
	return DEMOD_L1_Set_Property(frontend->demod, prop_code);
}

/************************************************************************************************************************
  DEMOD_L2_Set_Property function
  Use:        Sets up property
  Parameter:  standard, the value of the standard
************************************************************************************************************************/
UINT8  DEMOD_L2_Get_Property(LX_DEMOD_L2_Context *frontend, UINT32 prop_code)
{
	return DEMOD_L1_Get_Packed_Property(frontend->demod, prop_code);
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_GET_REG.
 * reads the DBB registers
 *
 * @param *front_end 		[IN] LX_DEMOD_L2_Context
 * @param addr 			[IN] UINT16
 * @param length 			[IN] UINT8
 * @param *readData 		[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8   DEMOD_L2_GET_REG(LX_DEMOD_L2_Context *front_end, UINT16  addr, UINT8 length, UINT8   *readData)
{
	UINT8 addrMsb = 0;
	UINT8 addrLsb = 0;

	UINT8 rdCount;

	addrMsb = (UINT8)((addr >> 8) & 0xff);
	addrLsb = (UINT8)(addr & 0xff);

	if (DEMOD_L1_GET_DD_Reg(front_end->demod, addrMsb, addrLsb, length) != NO_DEMOD_ERROR)
	{
		DBB_PRINT("Error calling DEMOD_L1_GET_DD_Reg\n");
		return ERROR_DEMOD_READ;
	}
	for(rdCount =0; rdCount < length; rdCount++)
	{
		//DBB_PRINT(" Register [0x%x] = 0x%x  \n", addr + rdCount, front_end->demod->rsp->dd_get_reg.mData[rdCount]);
		readData[rdCount] =  front_end->demod->rsp->dd_get_reg.mData[rdCount];
	}
	return NO_DEMOD_ERROR;
}


UINT8   DEMOD_L2_GET_REG_MAP(LX_DEMOD_L2_Context *front_end, UINT16  addr, UINT8 length, UINT8 *readData)
{
	UINT8 addrMsb = 0;
	UINT8 addrLsb = 0;

	addrMsb = (UINT8)((addr >> 8) & 0xff);
	addrLsb = (UINT8)(addr & 0xff);

	if (DEMOD_L1_GET_DD_Reg_Map(front_end->demod, addrMsb, addrLsb, length, readData) != NO_DEMOD_ERROR)
	{
		DBB_PRINT("Error calling DEMOD_L1_GET_DD_Reg\n");
		return ERROR_DEMOD_READ;
	}
	
	return NO_DEMOD_ERROR;
}
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_SET_REG.
 * writes the DBB registers
 *
 * @param *front_end 		[IN] LX_DEMOD_L2_Context
 * @param addr 			[IN] UINT16
 * @param length 			[IN] UINT8
 * @param wrData 			[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8   DEMOD_L2_SET_REG(LX_DEMOD_L2_Context *front_end,  UINT16  addr, UINT8 length, UINT32   wrData)
{
	UINT8 addrMsb = 0;
	UINT8 addrLsb = 0;


	addrMsb = (UINT8)((addr >> 8) & 0xff);
	addrLsb = (UINT8)(addr & 0xff);

	if (DEMOD_L1_SET_DD_Reg(front_end->demod, addrMsb, addrLsb, length, wrData) != NO_DEMOD_ERROR)
	{
		DBB_PRINT("Error calling DEMOD_L1_SET_DD_Reg\n");
		return ERROR_DEMOD_WRITE;
	}


	return NO_DEMOD_ERROR;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_Tuner_I2C_Enable.
 * Tuner i2c bus connection
 * Used to allow communication with the tuners
 *
 * @param *i2c 		[IN] LX_DEMOD_L0_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8   DEMOD_L2_Tuner_I2C_Enable (LX_DEMOD_L2_Context *frontend)
{
    return DEMOD_L1_SET_DD_Repeat(frontend->demod->i2c, DEMOD_DD_GET_REPEAT_CMD_ENABLE);
}
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_Tuner_I2C_Enable.
 * Tuner i2c bus connection
 * Used to disconnect i2c communication with the tuners
 *
 * @param *i2c 		[IN] LX_DEMOD_L0_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/

UINT8   DEMOD_L2_Tuner_I2C_Disable(LX_DEMOD_L2_Context *frontend)
{
    return DEMOD_L1_SET_DD_Repeat(frontend->demod->i2c, DEMOD_DD_GET_REPEAT_CMD_DISABLE);
}

/************************************************************************************************************************
  DEMOD_L2_Get_PartInfo function
  Use:       Gets firmware information.
  Parameter:  standard, the value of the standard
************************************************************************************************************************/
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_Get_PartInfo.
 * Gets firmware information.
 *
 * @param *frontend 		[IN] LX_DEMOD_L2_Context
 * @param *fwInfo 		[OUT] LX_DEMOD_L2_PART_INFO
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/

UINT8  DEMOD_L2_Get_PartInfo(LX_DEMOD_L2_Context *frontend, LX_DEMOD_L2_PART_INFO *fwInfo)
{
	UINT8 retCode = 0;

	retCode = DEMOD_L1_GET_DD_PartInfo(frontend->demod);

	if(NO_DEMOD_ERROR != retCode)
	{
		fwInfo->fw_major = 0x0;
		fwInfo->fw_minor = 0x0;
		fwInfo->fw_year = 0x0;
		fwInfo->fw_month = 0x0;
		fwInfo->fw_day = 0x0;
		fwInfo->chip_type = 0xff;
		fwInfo->chip_rev = 0xff;

		return retCode;
	}

	fwInfo->fw_major  = frontend->demod->rsp->part_info.fw_major;
	fwInfo->fw_minor = frontend->demod->rsp->part_info.fw_minor;
	fwInfo->fw_year = frontend->demod->rsp->part_info.fw_year;
	fwInfo->fw_month = frontend->demod->rsp->part_info.fw_month;
	fwInfo->fw_day = frontend->demod->rsp->part_info.fw_day;
	fwInfo->chip_type = frontend->demod->rsp->part_info.reserved;
	fwInfo->chip_rev = frontend->demod->rsp->part_info.chip_rev;

	return NO_DEMOD_ERROR;

}



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_GetDump.
 * Used to get the total informations of setting parameters for chip operation and transmitted signal status .
 * Used for debugging.
 *
 * @param *frontend 		[IN] LX_DEMOD_L2_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/

UINT8   DEMOD_L2_GetDump(LX_DEMOD_L2_Context *frontend)
{
	DBB_DUMP_PRINT("____________________DUMP____________________\n");
	DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_DD_BER_RESOL_PROP_CODE);
	DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_DD_IF_FREQ_PROP_CODE);
	DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_DD_CLOCK_MODE_PROP_CODE);
	DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_DD_MODE_PROP_CODE);
	DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_DD_AUTO_MODE_PROP_CODE);
	DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_DD_TS_MODE_PROP_CODE);
	DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_DD_ADC_PROP_CODE);
	DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_DD_AGC_PROP_CODE);
	DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_DD_TPOUT_MODE_PROP_CODE);
	//DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_DD_CONSTEL_PROP_CODE);
	//DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_DD_DISEQC_CONFIG_PROP_CODE);
	//DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_DD_DVBS_AFC_RANGE_PROP_CODE);


	/*
	DEMOD_L1_GET_DD_DVBT_Status(frontend->demod);
	DEMOD_L1_GET_DD_DISEQC_Status(frontend->demod);
	DEMOD_L1_GET_DD_DVBC_Status(frontend->demod);
	DEMOD_L1_GET_DD_DVBC2_Status(frontend->demod);
	DEMOD_L1_GET_DD_DVBS_Status(frontend->demod);
	DEMOD_L1_GET_DD_DVBS2_Status(frontend->demod);
	DEMOD_L1_GET_DD_DVBS2_Status(frontend->demod);
	DEMOD_L1_GET_DD_DVBT2_Status(frontend->demod);
	DEMOD_L1_GET_DD_ISDBT_Status(frontend->demod);
	*/

	if (DEMOD_L1_GET_DD_Status(frontend->demod) != NO_DEMOD_ERROR)
	{
		DBB_PRINT("Error calling DEMOD_L1_GET_DD_Status\n");
	}

	DEMOD_L1_CommandText          (frontend->demod->rsp, DEMOD_DD_STATUS_CMD);

	switch (frontend->demod->rsp->dd_status.reply_operMod)
	{
	 	case DEMOD_DD_STATUS_RESPONSE_MODULATION_VSB :
			DEMOD_L1_GET_DD_VSB_Status(frontend->demod);
			DEMOD_L1_CommandText          (frontend->demod->rsp, DEMOD_DD_VSB_STATUS_CMD);
			break;

		case DEMOD_DD_STATUS_RESPONSE_MODULATION_ATSC3:
			DEMOD_L1_GET_DD_ATSC3_Status(frontend->demod);
			DEMOD_L1_CommandText          (frontend->demod->rsp, DEMOD_DD_ATSC3_STATUS_CMD);
			DEMOD_L1_GET_DD_ATSC3_PLP_Info(frontend->demod, frontend->set_PLP_ID);
			DEMOD_L1_CommandText          (frontend->demod->rsp, DEMOD_DD_ATSC3_PLP_INFO_CMD);
			break;

		case DEMOD_DD_STATUS_RESPONSE_MODULATION_QAM:
			DEMOD_L1_GET_DD_QAM_Status(frontend->demod);
			DEMOD_L1_CommandText          (frontend->demod->rsp, DEMOD_DD_QAM_STATUS_CMD);
			break;

		case DEMOD_DD_STATUS_RESPONSE_MODULATION_ISDBT:
			DEMOD_L1_GET_DD_ISDBT_Status(frontend->demod);
			DEMOD_L1_CommandText          (frontend->demod->rsp, DEMOD_DD_ISDBT_STATUS_CMD);
			DEMOD_L1_GET_DD_ISDBT_TMCC_Info(frontend->demod);
			DEMOD_L1_CommandText          (frontend->demod->rsp, DEMOD_DD_ISDBT_TMCC_INFO_CMD);
			break;

		case DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBT:
			DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_DD_DVBT_HIERARCHY_PROP_CODE);
			DEMOD_L1_GET_DD_DVBT_Status(frontend->demod);
			DEMOD_L1_CommandText          (frontend->demod->rsp, DEMOD_DD_DVBT_STATUS_CMD);
			break;

		case DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBT2:
			DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_DD_DVBT2_MODE_PROP_CODE);
			DEMOD_L1_GET_DD_DVBT2_Status(frontend->demod);
			DEMOD_L1_CommandText          (frontend->demod->rsp, DEMOD_DD_DVBT2_STATUS_CMD);
			break;

	 	case DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBC:
			DEMOD_L1_GET_DD_DVBC_Status(frontend->demod);
			DEMOD_L1_CommandText          (frontend->demod->rsp, DEMOD_DD_DVBC_STATUS_CMD);
			break;

		case DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBS:
			DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_DD_DVBS_OPMSEL_PROP_CODE);
			DEMOD_L1_GET_DD_DVBS_Status(frontend->demod);
			DEMOD_L1_CommandText          (frontend->demod->rsp, DEMOD_DD_DVBS_STATUS_CMD);
			break;

		case DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBS2:
			DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_DD_DVBS_OPMSEL_PROP_CODE);
			DEMOD_L1_GET_DD_DVBS2_Status(frontend->demod);
			DEMOD_L1_CommandText          (frontend->demod->rsp, DEMOD_DD_DVBS2_STATUS_CMD);
			break;

		default:
			break;
	}


	DEMOD_L1_GET_DD_PartInfo(frontend->demod);
	DEMOD_L1_CommandText          (frontend->demod->rsp, DEMOD_DD_GET_PART_INFO_CMD);

    return NO_DEMOD_ERROR;
}


/************************************************************************************************************************
  DEMOD_L2_Set_ChipVersion function
  Use:       Gets firmware information.
  Parameter:  standard, the value of the standard
************************************************************************************************************************/
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_Set_ChipVersion.
 * Gets firmware information.
 *
 * @param *frontend 		[IN] LX_DEMOD_L2_Context
 * @param *fwInfo 		[OUT] LX_DEMOD_L2_PART_INFO
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/

UINT8  DEMOD_L2_Set_ChipInfo(LX_DEMOD_L2_Context *frontend, UINT16 chipVer)
{
	//DBB_PRINT("+++++++++++++++ chipVer = %x++++++++++++++++\n",chipVer);
	frontend->demod->i2c->chipVer 	= (UINT8) ((chipVer >> 8) & 0xff);
	frontend->demod->i2c->chipRev 	= (UINT8) (chipVer & 0xff);

	if(frontend->demod->i2c->chipVer >= L18F)
	{
		frontend->demod->i2c->cmdAddr	= 0xF050;
		frontend->demod->i2c->rspAddr	= 0xF090;
	}
	else
	{
		frontend->demod->i2c->cmdAddr	= 0x7010;
		frontend->demod->i2c->rspAddr	= 0x7091;
	}
	DBB_PRINT("++++++++++++++++++ cmdAddr = %x, rspAddr = %x++++++++++++++++++\n", frontend->demod->i2c->cmdAddr, frontend->demod->i2c->rspAddr);

	return NO_DEMOD_ERROR;

}

/**/

#ifndef LG3307_API


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_Set_MemAddr.
 * Set Base address for AXI I/F (refer to SoC MEM Map)
 *
 * @param *frontend 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8 DEMOD_L2_Set_MemAddr  (LX_DEMOD_L2_Context *frontend, UINT32 baseAddr)
{
	UINT8 return_code = NO_DEMOD_ERROR;

	DBB_PRINT("DEMOD_L2_Set_MemAddr starting...\n");

	/* Pointers initialization */
	frontend->baseAddr = baseAddr;

	return return_code;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_PowerUpWithMem.
 * Load commands and binary firmware images from AXI to MCU bootloader .
 *
 * @param *frontend [IN] LX_DEMOD_L2_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8 DEMOD_L2_PowerUpWithMem    (LX_DEMOD_L2_Context *frontend)
{
	int return_code;
	int fw_loaded;
	return_code = NO_DEMOD_ERROR;
	fw_loaded   = 0;

	/* Before patching, set POWER_UP values for 'RESET' and 'BOOTLOADER' */

	return_code = DEMOD_L1_API_LoadFirmware_MEM(frontend->demod, frontend->baseAddr);

	if (return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L1_API_LoadFirmware_MEM error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}

//	return_code = DEMOD_L1_API_LoadFirmware_IRAM(frontend->demod, M16P_DEMOD_FW_IRAM_0_1_0_R , 1);

//	return_code = DEMOD_L1_API_LoadFirmware_DRAM(frontend->demod, M16P_DEMOD_FW_DRAM_0_1_0_R , 1);

	return_code = DEMOD_L1_API_StartFirmware(frontend->demod) ;
	if (return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L1_API_StartFirmware error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}


    return NO_DEMOD_ERROR;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_InitMem.
 * Reset and Initialize DBB mdulator
 *
 * @param *frontend 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8 DEMOD_L2_InitMem  (LX_DEMOD_L2_Context *frontend)
{
	UINT8 return_code;
	DBB_PRINT("DEMOD_L2_Init starting...\n");

	if ((return_code = DEMOD_L2_PowerUpWithMem(frontend)) != NO_DEMOD_ERROR)
	{   /* PowerUp into bootloader */
	    DBB_PRINT ("DEMOD_L2_PowerUpWithPatch error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
	    return return_code;
	}
	
	DEMOD_L0_system_wait(10);

	/* At this point, FW is loaded and started.  */
	return_code = DEMOD_L2_Configure(frontend);
	if(return_code != NO_DEMOD_ERROR)
	{
		DBB_PRINT ("DEMOD_L2_Configure error 0x%02x: %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
		return return_code;
	}

	frontend->demod_init_done = 1;

	DBB_PRINT("DEMOD_L2_Init complete...\n");
	return NO_DEMOD_ERROR;
}


#endif


UINT8  DEMOD_L2_Set_SoftRst(LX_DEMOD_L2_Context *api, UINT8 softrstb, UINT8 softrstsyncb, UINT8 softrsteq1b, UINT8 softrsteq2b, UINT8 softrstdiseqcb, UINT8 softrstfecb, UINT8 softrsttpifb)
{
	UINT8 err = NO_DEMOD_ERROR;
	err = DEMOD_L1_SET_DD_SoftRst(api->demod, 1,0,0,0,0,0,0);
	
	return err;
}

/**/




