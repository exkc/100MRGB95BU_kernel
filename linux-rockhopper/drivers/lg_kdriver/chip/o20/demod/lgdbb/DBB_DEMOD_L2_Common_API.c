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
#define DEMOD_TAG "[L2.COMMON] "

#include <DBB_DEMOD_typedefs.h>
#include <demod_util.h>

#include <DBB_DEMOD_L2_Common_API.h>

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_XTENSA)

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
#include <asm/div64.h> //do_div
extern unsigned int intlog10(u32 value);
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
#include <math.h>
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)

#endif

LX_DEMOD_SQI_CN_ATSC3P1_T  SqiCnAtsc3P1[72] =
{
	/* Hierachy mode */ 	             /* bsetHP */ /* RF mode  */ /* Code rate*/	   /*CN ref */
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_QPSK,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_2_15, 000 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_QPSK,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_3_15, 000 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_QPSK,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_4_15, 100 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_QPSK,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_5_15, 200 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_QPSK,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_6_15, 300 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_QPSK,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_7_15, 400 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_QPSK,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_8_15, 500 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_QPSK,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_9_15, 600 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_QPSK,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_10_15, 700},
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_QPSK,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_11_15, 800 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_QPSK,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_12_15, 800 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_QPSK,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_13_15, 1000 },

	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_16QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_2_15, 0 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_16QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_3_15, 0 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_16QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_4_15, 0 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_16QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_5_15, 300 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_16QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_6_15, 300 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_16QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_7_15, 400 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_16QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_8_15, 600 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_16QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_9_15, 600 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_16QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_10_15, 700 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_16QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_11_15, 900 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_16QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_12_15, 100 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_16QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_13_15, 1100 },

	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_64QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_2_15, 0 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_64QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_3_15, 0 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_64QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_4_15, 300 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_64QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_5_15, 600 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_64QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_6_15, 700 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_64QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_7_15, 900 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_64QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_8_15, 1000 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_64QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_9_15, 1100 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_64QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_10_15, 1200 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_64QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_11_15, 1400 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_64QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_12_15, 1500 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_64QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_13_15, 1600 },

	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_256QAM_NUC, DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_2_15, 000 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_256QAM_NUC, DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_3_15, 300 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_256QAM_NUC, DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_4_15, 600 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_256QAM_NUC, DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_5_15, 800 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_256QAM_NUC, DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_6_15, 1000 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_256QAM_NUC, DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_7_15, 1200 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_256QAM_NUC, DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_8_15, 1400 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_256QAM_NUC, DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_9_15, 1500 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_256QAM_NUC, DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_10_15, 1700 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_256QAM_NUC, DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_11_15, 1900 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_256QAM_NUC, DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_12_15, 2000 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_256QAM_NUC, DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_13_15, 2200 },

	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_1024QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_2_15, 300 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_1024QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_3_15, 600 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_1024QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_4_15, 900 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_1024QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_5_15, 1100 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_1024QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_6_15, 1300 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_1024QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_7_15, 1500 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_1024QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_8_15, 1700 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_1024QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_9_15, 1900 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_1024QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_10_15, 2100 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_1024QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_11_15, 2400 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_1024QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_12_15, 2700 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_1024QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_13_15, 2900 },

	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_4096QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_2_15, 700 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_4096QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_3_15, 1000 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_4096QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_4_15, 1300 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_4096QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_5_15, 1500 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_4096QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_6_15, 1800 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_4096QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_7_15, 2000 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_4096QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_8_15, 2300 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_4096QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_9_15, 2500 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_4096QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_10_15, 2800 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_4096QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_11_15, 3000 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_4096QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_12_15, 3200 },
	{ DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_4096QAM_NUC,  DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_13_15, 3500 },
};

/* Allowing compatibility with previous parts (also reflected in DEMOD_L2_PowerUpWithPatch) */

#define DEMOD_BYTES_PER_LINE 			8

SINT64 _DEMOD_do_div64_32 (SINT64 dividend, SINT32 divisor)
{
#ifdef __KERNEL__
	do_div(dividend, divisor) ;
#else
	dividend =  (SINT64)(dividend / divisor) ;
#endif
	return dividend;
}

SINT64 _DEMOD_do_div64_64 (SINT64 dividend, SINT64 divisor)
{
#ifdef __KERNEL__
	SINT32  d;
	SINT32 high;
	unsigned int shift;

	high = (divisor >> 32);

	if (high) {
		shift = fls(high);
		d = divisor >> shift;
		dividend >>= shift;
	} else {
		d = divisor;
	}

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
int DEMOD_L2_Configure (LX_DEMOD_L2_Context * frontend)
{
	int retc = NO_DEMOD_ERROR;

	//Do Top control
	/* Storing Properties startup configuration in propShadow                              */
	/* !! Do NOT change the content of DEMOD_L1_Store_Properties_Defaults                   !! */
	/* !! It should reflect the part internal property settings after firmware download !! */

	/* Edit the procedure below if you have any properties settings different from the standard defaults */
	//DEMOD_PRINT ("DEMOD_L1_Store_Properties_Defaults\n");
	DEMOD_L1_Store_Properties_Defaults (frontend->demod->propShadow);

	//DEMOD_PRINT("DEMOD_L1_Store_User_Properies\n");
	DEMOD_L1_Store_User_Properies (frontend->demod->prop);

	/* Download properties different from 'default' */
	retc = DEMOD_L1_Download_All_Properties(frontend->demod);
	if (NO_DEMOD_ERROR != retc) {
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_Download_All_Properties() 0x%02x: %s\n",
				retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

	return NO_DEMOD_ERROR;
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
int DEMOD_L2_Opermode_Configure (LX_DEMOD_L2_Context *frontend , LX_DEMOD_OPER_MODE_T operMode)
{
	int retc = NO_DEMOD_ERROR;

	DEMOD_NOTI("[DEMOD_API] Operation Mode is 0x%02x\n", operMode);

	frontend->demod->propertyWriteMode = DEMOD_DD_DOWNLOAD_ALWAYS;

//	DEMOD_L1_Store_Properties_Defaults (frontend->demod->propShadow);
	DEMOD_L1_Store_User_Properies (frontend->demod->prop);
	retc = DEMOD_L1_Download_All_Properties(frontend->demod);
	if (NO_DEMOD_ERROR != retc) {
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_Download_All_Properties() 0x%02x: %s\n",
				retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

	switch(operMode)
	{
		case LX_DEMOD_DVBT:
		{
			retc = DEMOD_L1_Download_DVBT_Properties(frontend->demod);
		}
		break;
		case LX_DEMOD_DVBT2:
		{
			retc =DEMOD_L1_Download_DVBT2_Properties(frontend->demod);
		}
		break;
		case LX_DEMOD_DVBS:
		{
			retc =DEMOD_L1_Download_DVBS_Properties(frontend->demod);
		}
		break;
		case LX_DEMOD_DVBS2:
		{
			retc =DEMOD_L1_Download_DVBS2_Properties(frontend->demod);
		}
		break;
		case LX_DEMOD_DVBC:
		{
			retc =DEMOD_L1_Download_DVBC_Properties(frontend->demod);
		}
		break;
		case LX_DEMOD_DTMB:
		{
			retc =DEMOD_L1_Download_DTMB_Properties(frontend->demod);
		}
		break;

		case LX_DEMOD_ATSC3:
			retc = DEMOD_L1_Download_ATSC3_Properties(frontend->demod);
		break;

		default:
		{
			retc = NO_DEMOD_ERROR;
		}
		break;
	}

	if (NO_DEMOD_ERROR != retc) {
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_Download_XXX(%d)_Properties() 0x%02x: %s\n",
				operMode, retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

	frontend->demod->propertyWriteMode = DEMOD_DD_DOWNLOAD_ON_CHANGE;

	return retc;
}

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

int DEMOD_L2_PowerUpWithPatch (LX_DEMOD_L2_Context *frontend)
{
	LX_DEMOD_FW_STRUCT * fw_table = NULL;

	int retc = NO_DEMOD_ERROR;

	/* load selected firmware */
	fw_table = (LX_DEMOD_FW_STRUCT *)frontend->baseAddr;

	frontend->demod->chip->fw_done = 0;

	retc = DEMOD_L1_API_LoadFirmware_EXT(frontend->demod, fw_table);

	if (NO_DEMOD_ERROR != retc) {
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_API_LoadFirmware_EXT() 0x%02x: %s\n",
			retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

	DEMOD_INFO("[DEMOD_API] SUCCESS, DEMOD_L1_API_LoadFirmware_EXT()\n");

	frontend->demod->chip->fw_done = 1;

	retc = DEMOD_L1_API_StartFirmware(frontend->demod) ;
	if (NO_DEMOD_ERROR != retc) {
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_API_StartFirmware() 0x%02x: %s\n",
				retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
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
int DEMOD_L2_Init (LX_DEMOD_L2_Context *frontend)
{
	int retc = NO_DEMOD_ERROR;

	DEMOD_NOTI("[DEMOD_API] Start\n");
	frontend->demod->fw_state = DEMOD_FW_STATE_RUN;

	/* At this point, FW is loaded and started.  */
	retc = DEMOD_L2_Configure(frontend);
	if(NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L2_Configure() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
		return retc;
	}

	frontend->demod_init_done = 1;

	DEMOD_NOTI("[DEMOD_API] End\n");
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
int DEMOD_L2_Standby (LX_DEMOD_L2_Context *frontend)
{
	DEMOD_NOTI("[DEMOD_API] Start\n");
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
int DEMOD_L2_WakeUp (LX_DEMOD_L2_Context *frontend)
{
	DEMOD_NOTI("[DEMOD_API] Start\n");
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
int DEMOD_L2_Media (LX_DEMOD_L2_Context *frontend, UINT8 modulation)
{
	switch (modulation) {
	case DEMOD_DD_MODE_PROP_MODULATION_AUTO_DETECT:
		switch (frontend->demod->prop->dd_auto_mode.auto_detect) {
		case DEMOD_DD_AUTO_MODE_PROP_DET_DVBT_DVBT2_ENABLE:
		case DEMOD_DD_AUTO_MODE_PROP_DET_DVBT_ONLY_ENABLE:
		case DEMOD_DD_AUTO_MODE_PROP_DET_DVBT2_ONLY_ENABLE:
			return DEMOD_DD_TERRESTRIAL;

		case DEMOD_DD_AUTO_MODE_PROP_DET_DVBC_DVBC2_ENABLE:
		case DEMOD_DD_AUTO_MODE_PROP_DET_DVBC_ONLY_ENABLE:
		case DEMOD_DD_AUTO_MODE_PROP_DET_DVBC2_ONLY_ENABLE:
			return DEMOD_DD_CABLE;

		case DEMOD_DD_AUTO_MODE_PROP_DET_DVBS_DVBS2_ENABLE:
		case DEMOD_DD_AUTO_MODE_PROP_DET_DVBS_ONLY_ENABLE:
		case DEMOD_DD_AUTO_MODE_PROP_DET_DVBS2_ONLY_ENABLE:
			return DEMOD_DD_SATELLITE;

		default:
			DEMOD_WARN("[DEMOD_API] Unknown Media\n");
			break;
		}
      		break;

	case DEMOD_DD_MODE_PROP_MODULATION_DVBT:
	case DEMOD_DD_MODE_PROP_MODULATION_DVBT2:
	case DEMOD_DD_MODE_PROP_MODULATION_VSB:
	case DEMOD_DD_MODE_PROP_MODULATION_ATSC3:
		return DEMOD_DD_TERRESTRIAL;

	case DEMOD_DD_MODE_PROP_MODULATION_DVBC:
	case DEMOD_DD_MODE_PROP_MODULATION_DVBC2:
	case DEMOD_DD_MODE_PROP_MODULATION_QAM:
		return DEMOD_DD_CABLE;

	case DEMOD_DD_MODE_PROP_MODULATION_DVBS:
	case DEMOD_DD_MODE_PROP_MODULATION_DVBS2:
		return DEMOD_DD_SATELLITE;
	default:
		DEMOD_WARN("[DEMOD_API] Unknown Media\n");
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
 * @param *frontend 		[IN] LX_DEMOD_L2_Context
 * @param new_standard 	[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_Switch_to_standard (LX_DEMOD_L2_Context *frontend, UINT8 new_standard)
{
	int retc = NO_DEMOD_ERROR;

	frontend->demod->standard = new_standard;

	/* ------------------------------------------------------------ */
	/* Set media for new standard                                   */
	/* ------------------------------------------------------------ */
	frontend->demod->prop->dd_mode.modulation = new_standard;
	frontend->demod->media = DEMOD_L2_Media(frontend, frontend->demod->prop->dd_mode.modulation);

	if(DEMOD_DD_MODE_PROP_MODULATION_ANALOG == new_standard || DEMOD_DD_MODE_PROP_MODULATION_SLEEP == new_standard)
	{

		if(!frontend->demod->bIsStandby)
		{
			retc = DEMOD_L2_Standby (frontend);
			if(NO_DEMOD_ERROR != retc)
			{
				DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L2_Standby() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}
			frontend->demod->bIsStandby = 1;
		}
	}
	else
	{
		if(frontend->demod->bIsStandby)
		{
			retc = DEMOD_L2_WakeUp (frontend);
			if(NO_DEMOD_ERROR != retc)
			{
				DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L2_WakeUp() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
				return retc;
			}
			frontend->demod->bIsStandby = 0;
		}

		frontend->demod->prop->dd_mode.modulation = new_standard;

		retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_MODE_PROP_CODE);
		if(NO_DEMOD_ERROR != retc)
		{
			DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_Set_Property() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
			return -ERROR_DEMOD_ERROR;
		}

	}

	return NO_DEMOD_ERROR;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_Check_NeverLock_state.
 * Check neverLock status. used for searching channels automatically
 *
 * @param *frontend 		[IN] LX_DEMOD_L2_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_Check_NeverLock_state (LX_DEMOD_L2_Context *frontend)
{
	int retc = NO_DEMOD_ERROR;
	UINT8 lock = 2;

	retc = DEMOD_L1_GET_DD_Status(frontend->demod);
	if (NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
		return lock;
	}

	switch (frontend->demod->rsp->dd_status.neverLock) {
	case DEMOD_DD_STATUS_RESPONSE_NEVERLOCK_LOCKED:
		DEMOD_NOTI("[DEMOD_API] DEMOD_lock_to_carrier: locked on a %s signal\n", DEMOD_L1_API_StandardName(frontend->demod->rsp->dd_status.reply_operMod));
		lock = 1;
		break;
	case DEMOD_DD_STATUS_RESPONSE_NEVERLOCK_NO_LOCK:
		DEMOD_WARN("[DEMOD_API] No SIgnal detected\n");
		lock = 0;
		break;
	default:
		lock = 2;
		break;
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
 * @param *frontend 		[IN] LX_DEMOD_L2_Context
 * @param new_standard 	[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_Check_lock_loop (LX_DEMOD_L2_Context *frontend, UINT8 standard)
{
	UINT32 searchStartTime;
	UINT32 min_lock_time_ms = 0;
	UINT32 max_lock_time_ms = 0;
	UINT32 searchDelay = 0;
	UINT8  lock = 0;

	/* Set min_lock_time_ms and max_lock_time_ms*/
	switch (standard) {
	case DEMOD_DD_MODE_PROP_MODULATION_VSB :
		min_lock_time_ms = DEMOD_DD_VSB_MIN_LOCK_TIME;
		max_lock_time_ms = DEMOD_DD_VSB_MAX_LOCK_TIME;
		break;

	case DEMOD_DD_MODE_PROP_MODULATION_QAM:
		min_lock_time_ms = DEMOD_DD_QAM_MIN_LOCK_TIME;
		max_lock_time_ms =DEMOD_DD_QAM_MAX_LOCK_TIME;
		break;

	case DEMOD_DD_MODE_PROP_MODULATION_ATSC3 :
		min_lock_time_ms = DEMOD_DD_ATSC3_MIN_LOCK_TIME;
		max_lock_time_ms = DEMOD_DD_ATSC3_MAX_LOCK_TIME;
		break;

	case DEMOD_DD_MODE_PROP_MODULATION_ISDBT :
		min_lock_time_ms = DEMOD_DD_ISDBT_MIN_LOCK_TIME;
		max_lock_time_ms = DEMOD_DD_ISDBT_MAX_LOCK_TIME;
		break;

	case DEMOD_DD_MODE_PROP_MODULATION_DVBT :
		if (frontend->auto_detect_DVBT_T2) {
			min_lock_time_ms = DEMOD_DD_DVBT_MIN_LOCK_TIME;
			max_lock_time_ms = DEMOD_DD_DVBT2_MAX_LOCK_TIME;
		} else {
			min_lock_time_ms = DEMOD_DD_DVBT_MIN_LOCK_TIME;
			max_lock_time_ms = DEMOD_DD_DVBT_MAX_LOCK_TIME;
		}
		break;

	case DEMOD_DD_MODE_PROP_MODULATION_DVBT2:
		min_lock_time_ms = DEMOD_DD_DVBT2_MIN_LOCK_TIME;
		max_lock_time_ms = DEMOD_DD_DVBT2_MAX_LOCK_TIME;
		break;

	case DEMOD_DD_MODE_PROP_MODULATION_DVBC :
		min_lock_time_ms = DEMOD_DD_DVBC_MIN_LOCK_TIME;
		max_lock_time_ms = DEMOD_DD_DVBC_MAX_LOCK_TIME;
		break;

	case DEMOD_DD_MODE_PROP_MODULATION_DVBS:
		if (frontend->auto_detect_SAT) {
			min_lock_time_ms = DEMOD_DD_DVBS2_MIN_LOCK_TIME;
			max_lock_time_ms = DEMOD_DD_DVBS2_MAX_LOCK_TIME*2;
		} else {
		    	min_lock_time_ms = DEMOD_DD_DVBS_MIN_LOCK_TIME;
			max_lock_time_ms = DEMOD_DD_DVBS_MAX_LOCK_TIME;
		}
		break;

	case DEMOD_DD_MODE_PROP_MODULATION_DVBS2:
		if (frontend->auto_detect_SAT) {
			min_lock_time_ms = DEMOD_DD_DVBS2_MIN_LOCK_TIME;
			max_lock_time_ms = DEMOD_DD_DVBS2_MAX_LOCK_TIME*2;
		} else {
			min_lock_time_ms = DEMOD_DD_DVBS2_MIN_LOCK_TIME;
			max_lock_time_ms =DEMOD_DD_DVBS2_MAX_LOCK_TIME;
		}
		break;

	case DEMOD_DD_MODE_PROP_MODULATION_DTMB :
		min_lock_time_ms = DEMOD_DD_DTMB_MIN_LOCK_TIME;
		max_lock_time_ms = DEMOD_DD_DTMB_MAX_LOCK_TIME;
		break;
	default:
		return 0;
	}

	searchStartTime = DEMOD_L0_system_time();

	/* as we will not lock in less than min_lock_time_ms, wait a while...*/
	DEMOD_L0_system_wait(min_lock_time_ms);

	while (1) {
		/* Check the status for the current modulation */
		if (NO_DEMOD_ERROR != DEMOD_L1_GET_DD_Status(frontend->demod))
		{
			DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_Status\n");
			return lock;
		}
		lock = frontend->demod->rsp->dd_status.lock_fec;

		if (lock == 1)
		{
			  DEMOD_NOTI("[DEMOD_API] Fec_Lock took %3d ms\n", searchDelay);
			  return lock;
		}
	   	searchDelay = DEMOD_L0_system_time() - searchStartTime;

		/* timeout management (this should never happen if timeout values are correctly set) */
		if (searchDelay >= max_lock_time_ms)
		{
			DEMOD_WARN("[DEMOD_API] Lock Loop timeout(%d) after %d ms\n", max_lock_time_ms,searchDelay);
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
 * @param *frontend 		[IN] LX_DEMOD_L2_Context
 * @param new_standard 	[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_Check_NeverLock_loop (LX_DEMOD_L2_Context *frontend, UINT8 standard)
{
	int retc = NO_DEMOD_ERROR;

	UINT32 searchStartTime;
	UINT32 min_lock_time_ms = 0;
	UINT32 max_lock_time_ms = 0;
	UINT32 neverLock_time_ms = 0;
	UINT32 fecLock_time_ms = 0;
	UINT32 searchDelay = 0;
	UINT8  neverLock = 0;
	UINT8 fecLock = 0;

	/* Set min_lock_time_ms and max_lock_time_ms*/
	switch (standard) {
	case DEMOD_DD_MODE_PROP_MODULATION_VSB:
		min_lock_time_ms = DEMOD_DD_VSB_MIN_LOCK_TIME;
		max_lock_time_ms = DEMOD_DD_VSB_MAX_LOCK_TIME;
		neverLock_time_ms = DEMOD_DD_VSB_MAX_SEARCH_TIME;
		break;
	case DEMOD_DD_MODE_PROP_MODULATION_QAM:
		min_lock_time_ms = DEMOD_DD_QAM_MIN_LOCK_TIME;
		max_lock_time_ms = DEMOD_DD_QAM_MAX_LOCK_TIME;
		neverLock_time_ms = DEMOD_DD_QAM_MAX_SEARCH_TIME;
		break;
	case DEMOD_DD_MODE_PROP_MODULATION_ATSC3:
		min_lock_time_ms = DEMOD_DD_ATSC3_MIN_LOCK_TIME;
		max_lock_time_ms = DEMOD_DD_ATSC3_MAX_LOCK_TIME;
		neverLock_time_ms = DEMOD_DD_ATSC3_MAX_SEARCH_TIME;
		fecLock_time_ms = DEMOD_DD_ATSC3_MAX_FEC_LOCK_TIME;
		break;
	case DEMOD_DD_MODE_PROP_MODULATION_ISDBT:
		min_lock_time_ms = DEMOD_DD_ISDBT_MIN_LOCK_TIME;
		max_lock_time_ms = DEMOD_DD_ISDBT_MAX_LOCK_TIME;
		neverLock_time_ms = DEMOD_DD_ISDBT_MAX_SEARCH_TIME;
		break;
	case DEMOD_DD_MODE_PROP_MODULATION_DVBT:
		if (frontend->auto_detect_DVBT_T2) {
			min_lock_time_ms = DEMOD_DD_DVBT_MIN_LOCK_TIME;
			max_lock_time_ms = DEMOD_DD_DVBT2_MAX_LOCK_TIME;
			neverLock_time_ms = DEMOD_DD_DVBT2_MAX_SEARCH_TIME;
		} else {
			min_lock_time_ms = DEMOD_DD_DVBT_MIN_LOCK_TIME;
			max_lock_time_ms = DEMOD_DD_DVBT_MAX_LOCK_TIME;
			neverLock_time_ms = DEMOD_DD_DVBT_MAX_SEARCH_TIME;
		}
		break;
	case DEMOD_DD_MODE_PROP_MODULATION_DVBT2:
		if (frontend->auto_detect_DVBT_T2) {
			min_lock_time_ms = DEMOD_DD_DVBT_MIN_LOCK_TIME;
			max_lock_time_ms = DEMOD_DD_DVBT2_MAX_LOCK_TIME;
			neverLock_time_ms = DEMOD_DD_DVBT_MAX_SEARCH_TIME;
		} else {
			min_lock_time_ms = DEMOD_DD_DVBT2_MIN_LOCK_TIME;
			max_lock_time_ms = DEMOD_DD_DVBT2_MAX_LOCK_TIME;
			neverLock_time_ms = DEMOD_DD_DVBT2_MAX_SEARCH_TIME;
		}
		break;
	case DEMOD_DD_MODE_PROP_MODULATION_DVBC:
			min_lock_time_ms = DEMOD_DD_DVBC_MIN_LOCK_TIME;
			max_lock_time_ms = DEMOD_DD_DVBC_MAX_LOCK_TIME;
			neverLock_time_ms = DEMOD_DD_DVBC_MAX_SEARCH_TIME;
		break;

	case DEMOD_DD_MODE_PROP_MODULATION_DVBS :
		if (frontend->auto_detect_SAT) {
			min_lock_time_ms = DEMOD_DD_DVBS_MIN_LOCK_TIME;
			max_lock_time_ms = DEMOD_DD_DVBS_MAX_LOCK_TIME * 2;
			neverLock_time_ms = DEMOD_DD_DVBS_MAX_SEARCH_TIME;
		} else {
			min_lock_time_ms = DEMOD_DD_DVBS_MIN_LOCK_TIME;
			max_lock_time_ms = DEMOD_DD_DVBS_MAX_LOCK_TIME;
			neverLock_time_ms = DEMOD_DD_DVBS_MAX_SEARCH_TIME;
		}
		break;
	case DEMOD_DD_MODE_PROP_MODULATION_DVBS2:
		if (frontend->auto_detect_SAT) {
			min_lock_time_ms = DEMOD_DD_DVBS_MIN_LOCK_TIME;
			max_lock_time_ms = DEMOD_DD_DVBS_MAX_LOCK_TIME * 2;
			neverLock_time_ms = DEMOD_DD_DVBS_MAX_SEARCH_TIME;
		} else {
			min_lock_time_ms = DEMOD_DD_DVBS2_MIN_LOCK_TIME;
			max_lock_time_ms = DEMOD_DD_DVBS2_MAX_LOCK_TIME;
			neverLock_time_ms = DEMOD_DD_DVBS2_MAX_SEARCH_TIME;
		}
		break;

	case DEMOD_DD_MODE_PROP_MODULATION_DTMB :
		min_lock_time_ms = DEMOD_DD_DTMB_MIN_LOCK_TIME;
		max_lock_time_ms = DEMOD_DD_DTMB_MAX_LOCK_TIME;
		neverLock_time_ms = DEMOD_DD_DTMB_MAX_SEARCH_TIME;
		break;
	default :
		return NO_DEMOD_ERROR;
	}


	searchStartTime = DEMOD_L0_system_time();

	/* as we will not lock in less than min_lock_time_ms, wait a while...*/
	DEMOD_L0_system_wait(min_lock_time_ms);

	while (1)
	{
		if(neverLock != 1)
		{
			/* Check the status for the current modulation */
		   	 neverLock = DEMOD_L2_Check_NeverLock_state(frontend);

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
				DEMOD_NOTI("[DEMOD_API] NerverLock took %3d ms\n", searchDelay);
			}
			else if (neverLock == 0)
			{
				//max_lock_time_ms = DEMOD_DD_VSB_MAX_LOCK_TIME;
				searchDelay = DEMOD_L0_system_time() - searchStartTime;
				DEMOD_WARN("[DEMOD_API] FAIL, NerverLock took %3d ms\n", searchDelay);
				neverLock = 0;
				//break;
				return NO_DEMOD_ERROR;
			}
			else
			{
				if (searchDelay >= neverLock_time_ms)
				{
					DEMOD_WARN("[DEMOD_API] FAIL, NeverLock timeout(%d) after %d ms\n",  neverLock_time_ms, searchDelay);
					neverLock = 0;
					//break;
					return NO_DEMOD_ERROR;
				}
			}
		}
		else
		{
			/* Call the standard-specific status function */
			retc = DEMOD_L1_GET_DD_Status(frontend->demod);
			if (NO_DEMOD_ERROR != retc)
			{
				DEMOD_WARN("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
				fecLock = 0;
			} else {
				fecLock = frontend->demod->rsp->dd_status.lock_fec;
			}

			if(fecLock == 1)
			{
				searchDelay = DEMOD_L0_system_time() - searchStartTime;
				DEMOD_NOTI("[DEMOD_API] FEC Lock took %3d ms\n", searchDelay);
				return fecLock;

			}
			else
			{
				searchDelay = DEMOD_L0_system_time() - searchStartTime;
				if (searchDelay >= neverLock_time_ms)
				{
					DEMOD_WARN("[DEMOD_API] FAIL, FEC Lock Timeout took %3d ms\n", searchDelay);
					fecLock = 0;
					return NO_DEMOD_ERROR;
				}
			}

		}

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
 * @param *frontend 		[IN] LX_DEMOD_L2_Context
 * @param new_standard 	[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_Check_BlindLock_loop (LX_DEMOD_L2_Context *frontend, UINT8 standard)
{
	UINT32 searchStartTime;
	UINT32 min_lock_time_ms = 0;
	UINT32 max_lock_time_ms = 0;
	UINT32 blindLock_time_ms = 0;
	UINT32 searchDelay = 0;
	UINT8  blindLock = 0;
//	UINT8  fecLock = 0;

	/* Set min_lock_time_ms and max_lock_time_ms*/
	switch (standard) {
	case DEMOD_DD_MODE_PROP_MODULATION_DVBC :
		min_lock_time_ms = DEMOD_DD_DVBC_MIN_LOCK_TIME;
		max_lock_time_ms = DEMOD_DD_DVBC_MAX_LOCK_TIME;
		blindLock_time_ms = DEMOD_DD_DVBC_MAX_SEARCH_TIME;
		break;

	case DEMOD_DD_MODE_PROP_MODULATION_DVBS :
		if (frontend->auto_detect_SAT) {
			min_lock_time_ms = 10;
			max_lock_time_ms = 100;
			blindLock_time_ms = 1000;
		} else {
			min_lock_time_ms = 10;
			max_lock_time_ms = 100;
			blindLock_time_ms = 1000;
		}
		break;

	case DEMOD_DD_MODE_PROP_MODULATION_DVBS2:
		if (frontend->auto_detect_SAT) {
			min_lock_time_ms = 10;
			max_lock_time_ms = 100;
			blindLock_time_ms = 1000;
		} else {
			min_lock_time_ms = 10;
			max_lock_time_ms = 100;
			blindLock_time_ms = 1000;
		}
		break;

	default :
		return NO_DEMOD_ERROR;
		break;
	}

	searchStartTime = DEMOD_L0_system_time();

	/* as we will not lock in less than min_lock_time_ms, wait a while...*/
	DEMOD_L0_system_wait(min_lock_time_ms);

	while (1) {
		if(blindLock != 1) {
			/* Check the status for the current modulation */
		   	 blindLock = DEMOD_L2_Check_BlindLock_state(frontend);

			if (blindLock == 1)
			{
				//max_lock_time_ms = DEMOD_DD_VSB_MAX_LOCK_TIME;
				searchDelay = DEMOD_L0_system_time() - searchStartTime;
				DEMOD_NOTI("[DEMOD_API] Blind Lock took %3d ms\n", searchDelay);
				break;
			}
			else if (blindLock == 2)
			{
				//max_lock_time_ms = DEMOD_DD_VSB_MAX_LOCK_TIME;
				searchDelay = DEMOD_L0_system_time() - searchStartTime;
				DEMOD_NOTI("[DEMOD_API] Blind UnLock took %3d ms\n", searchDelay);
				blindLock = 0;
				break;
				//return NO_DEMOD_ERROR;
			}
			else
			{
				searchDelay = DEMOD_L0_system_time() - searchStartTime;
				if (searchDelay >= blindLock_time_ms)
				{
					DEMOD_WARN("[DEMOD_API] Blind Lock timeout(%d) after %d ms\n", blindLock_time_ms, searchDelay);
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
 * @param *frontend 		[IN] LX_DEMOD_L2_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_Check_BlindLock_state (LX_DEMOD_L2_Context *frontend)
{
	int retc = NO_DEMOD_ERROR;
	UINT8 lock = 2;

	retc = DEMOD_L1_GET_DD_BLIND_Status(frontend->demod);
	if (NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_BLIND_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
		return lock;
	}

	switch (frontend->demod->rsp->blind_status.blindLock) {
	case DEMOD_DD_BLIND_STATUS_RESPONSE_BLINDLOCK_LOCKED:
		lock = 1;
		DEMOD_NOTI("[DEMOD_API] locked on a %s signal\n", DEMOD_L1_API_StandardName(frontend->demod->rsp->dd_status.reply_operMod));
		break;
	case DEMOD_DD_BLIND_STATUS_RESPONSE_BLINDLOCK_NOTLOCKED:
		lock = 2;
		DEMOD_WARN("[DEMOD_API] No SIgnal detected !!\n");
		break;
	default:
		lock = 0;
		//DEMOD_INFO("Processing !!\n");
		break;
	}

	return lock;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_Set_Invert_Spectrum. (used only for satellite mode)
 * return the required invert_spectrum value depending on the settings.
 *
 * @param *frontend 			[IN] LX_DEMOD_L2_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_Set_Invert_Spectrum (LX_DEMOD_L2_Context *frontend)
{
	UINT8 inversion;
	inversion = 0; /* to avoid compile error */

	if (frontend->demod->media == DEMOD_DD_TERRESTRIAL)
	{
		 inversion = DEMOD_DD_MODE_PROP_SPECINV_NORMAL;
	}

	if (frontend->demod->media == DEMOD_DD_SATELLITE  )
	{
		inversion = frontend->satellite_spectrum_inversion;

		#ifdef   DEMOD_UNICABLE_COMPATIBLE
		if (frontend->lnb_type == UNICABLE_LNB_TYPE_UNICABLE)
		{
		 	 if (frontend->unicable_spectrum_inversion) inversion = !inversion;
		}
		#endif /* DEMOD_UNICABLE_COMPATIBLE */
  	}

  	return inversion;

}

/************************************************************************************************************************
  DEMOD_L2_Get_LockStatus function
  Use:        standard text retrieval function
              Used to retrieve the standard text used by the Si2169C
  Parameter:  standard, the value of the standard
************************************************************************************************************************/
int DEMOD_L2_Get_LockStatus (LX_DEMOD_L2_Context *frontend, UINT8 *pOperMode,  UINT8 *pFecLock)
{
	int retc = 0;

	retc = DEMOD_L1_GET_DD_Status(frontend->demod);

	if(NO_DEMOD_ERROR != retc) {
		*pOperMode = DEMOD_DD_MODE_PROP_MODULATION_UNKNOWN ;
		*pFecLock = DEMOD_DD_STATUS_RESPONSE_LOCK_FEC_NO_LOCKED;
		return retc;
	}

	*pOperMode = frontend->demod->rsp->dd_status.reply_operMod ;
	*pFecLock = frontend->demod->rsp->dd_status.lock_fec;

	return NO_DEMOD_ERROR;
}

 /************************************************************************************************************************
   DEMOD_L2_Get_OperMode function
   Use: 	   standard text retrieval function
			   Used to retrieve the standard text used by the Si2169C
   Parameter:  standard, the value of the standard
 ************************************************************************************************************************/
 int DEMOD_L2_Get_OperMode (LX_DEMOD_L2_Context *frontend, LX_DEMOD_OPER_MODE_T *reply_opmode)
 {
 	int retc = NO_DEMOD_ERROR;

	retc = DEMOD_L1_GET_DD_Status(frontend->demod);
	if (NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
		return retc;
	}

	switch (frontend->demod->rsp->dd_status.reply_operMod) {
	case DEMOD_DD_MODE_PROP_MODULATION_VSB:			*reply_opmode = LX_DEMOD_ATSC;	break;
	case DEMOD_DD_MODE_PROP_MODULATION_ATSC3:		*reply_opmode = LX_DEMOD_ATSC3;	break;
	case DEMOD_DD_MODE_PROP_MODULATION_QAM: 		*reply_opmode = LX_DEMOD_QAM;	break;
	case DEMOD_DD_MODE_PROP_MODULATION_ISDBT: 		*reply_opmode = LX_DEMOD_ISDBT;	break;
	case DEMOD_DD_MODE_PROP_MODULATION_DVBT:		*reply_opmode = LX_DEMOD_DVBT;	break;
	case DEMOD_DD_MODE_PROP_MODULATION_DVBT2:		*reply_opmode = LX_DEMOD_DVBT2;	break;
	case DEMOD_DD_MODE_PROP_MODULATION_DVBC:		*reply_opmode = LX_DEMOD_DVBC;	break;
	case DEMOD_DD_MODE_PROP_MODULATION_DVBC2:		*reply_opmode = LX_DEMOD_DVBC2;	break;
	case DEMOD_DD_MODE_PROP_MODULATION_DVBS:		*reply_opmode = LX_DEMOD_DVBS;	break;
	case DEMOD_DD_MODE_PROP_MODULATION_DVBS2:		*reply_opmode = LX_DEMOD_DVBS2;	break;
	case DEMOD_DD_MODE_PROP_MODULATION_DTMB:		*reply_opmode = LX_DEMOD_DTMB;	break;

	default:
		DEMOD_ERROR("[DEMOD_API] LX_DEMOD_UNKNOWN_OPMODE with value : %02x\n", frontend->demod->rsp->dd_status.reply_operMod);
		return ERROR_DEMOD_RESULT_UNKNOWN;
	}

	DEMOD_DEBUG("DEMOD_L2_Get_OperMode : 0x%02x\n", *reply_opmode);

	return NO_DEMOD_ERROR;
 }

 /************************************************************************************************************************
  NAME: DEMOD_L2_Status
  DESCRIPTION: Calls the DBB global status function (DD_STATUS) and then the standard-specific status functions
  Porting:    Remove the un-necessary functions calls, if any. (Checking the TPS status may not be required)

  Parameter:  Pointer to DEMOD Context
  Returns:    1 if the current modulation is valid, 0 otherwise
************************************************************************************************************************/
int DEMOD_L2_SignalStatus (LX_DEMOD_L2_Context *frontend, LX_DEMOD_L2_SIG_STATUS *pSignalStatus)
{
	int retc = NO_DEMOD_ERROR;
	UINT32	constPwr;
	SINT64 offsetFrq_KHz_val;
	UINT64 temp_snr = 0x0000000000000000;

#ifndef __KERNEL__
	double calcValue = 0;
#else
	SINT64 calcValue = 0;
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

	pSignalStatus->cell_id = 0;
	pSignalStatus->il_mode = 0;
	pSignalStatus->pn_const = 0;
	pSignalStatus->pn_mode = 0;
	pSignalStatus->carr_mode = 0;

	/* Call the demod global status function */
	retc = DEMOD_L1_GET_DD_Status (frontend->demod);
	if(NO_DEMOD_ERROR != retc) {
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
		return retc;
	}

	/* Call the standard-specific status function */
	switch (frontend->demod->rsp->dd_status.reply_operMod) {

	case DEMOD_DD_MODE_PROP_MODULATION_VSB: {
		retc = DEMOD_L1_GET_DD_VSB_Status(frontend->demod);
		if(NO_DEMOD_ERROR != retc) {
			DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_VSB_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
			return retc;
		}
		pSignalStatus->ber = frontend->demod->rsp->vsb_status.ber;
		pSignalStatus->constellation = frontend->demod->rsp->vsb_status.constellation;
		pSignalStatus->if_agc = frontend->demod->rsp->vsb_status.if_agc;
		pSignalStatus->mse_info = frontend->demod->rsp->vsb_status.mse_info;
		pSignalStatus->operatingMode = frontend->demod->rsp->vsb_status.op_mode;
		pSignalStatus->packetError = (UINT32)(frontend->demod->rsp->vsb_status.pe);
		pSignalStatus->spInv = frontend->demod->rsp->vsb_status.spInv;
		pSignalStatus->demodLock = frontend->demod->rsp->vsb_status.lock_fec;

		if(pSignalStatus->mse_info == 0) {
			DEMOD_PRINT("Fail to get the MSE value(mse = %d)\n", pSignalStatus->mse_info);
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
		} break;

	case DEMOD_DD_MODE_PROP_MODULATION_QAM: {
		retc = DEMOD_L1_GET_DD_QAM_Status(frontend->demod);
		if(NO_DEMOD_ERROR != retc) {
			DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_QAM_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
			return retc;
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
		pSignalStatus->offsetFrq_Hz = (SINT32)(offsetFrq_KHz_val * 1000);	//Hz

		if(pSignalStatus->mse_info == 0) {
			DEMOD_PRINT("Fail to get the MSE value(mse = %d)\n",pSignalStatus->mse_info);
			pSignalStatus->mse_info = 1;
		}

		if(pSignalStatus->constellation == DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64)
			pSignalStatus->constPwr = 688128;
		else
			pSignalStatus->constPwr = 696320;

		offsetFrq_KHz_val = (frontend->demod->rsp->qam_status.sfo & 0x800000) ? (0xffffffffff000000 | frontend->demod->rsp->qam_status.sfo) : frontend->demod->rsp->qam_status.sfo;
		pSignalStatus->sam_offsetFrq_Hz = (SINT32) _DEMOD_do_div64_32 ((offsetFrq_KHz_val * pSignalStatus->sym_rate*1000), 8388608);	//Hz

#ifdef __KERNEL__
		pSignalStatus->snr = 0;
#else
		calcValue =  (double)(pSignalStatus->constPwr) / (double)(pSignalStatus->mse_info);
		pSignalStatus->snr  = (UINT32)(10 * log10 (calcValue));
#endif
		} break;

	case DEMOD_DD_MODE_PROP_MODULATION_ATSC3: {
		UINT8 		i;
		UINT32 		sn_atsc3_p1 = 0, sn_atsc3_p1_temp = 0; // 191010 test
		UINT8 		berSQI = 1;
		SINT32 		snRel;
		//SINT32 		tempQual = 0;
		UINT8		plp0_en = 0, plp1_en = 0, plp2_en = 0, plp3_en = 0; // 191010 test
		UINT8		plp_num_dec = 0, j = 0; // 191010 test
		UINT8		sqi_mod = 0, sqi_cod = 0; // 191010 test			
		SINT64		offset_temp;

		retc = DEMOD_L1_GET_DD_ATSC3_Status(frontend->demod);
		if(NO_DEMOD_ERROR != retc) {
			DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_ATSC3_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
			return retc;
		}

		DEMOD_L1_GET_DD_ATSC3_PLP_Info(frontend->demod, frontend->demod->cmd->atsc3_plp_info.plp_index);
		if(retc != NO_DEMOD_ERROR)
		{
			DEMOD_PRINT ("DEMOD_L1_GET_DD_ATSC3_PLP_Info  error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		}
		pSignalStatus->ber = frontend->demod->rsp->atsc3_status.ber;
		pSignalStatus->if_agc = frontend->demod->rsp->atsc3_status.if_agc;
		pSignalStatus->mse_info = frontend->demod->rsp->atsc3_status.mse_info;
			pSignalStatus->mse_info_demod = frontend->demod->rsp->atsc3_status.mse_info_demod;
		pSignalStatus->operatingMode = frontend->demod->rsp->atsc3_status.op_mode;

		if(frontend->demod->rsp->atsc3_plp_info.plp_fec_type <4)			pSignalStatus->packetError = frontend->demod->rsp->atsc3_status.plp_outer_err;
		else if(frontend->demod->rsp->atsc3_plp_info.plp_fec_type < 6)		pSignalStatus->packetError = frontend->demod->rsp->atsc3_status.ldpc_err;
		else																pSignalStatus->packetError = 0x00000000;

		pSignalStatus->spInv = frontend->demod->rsp->atsc3_status.spInv;
		pSignalStatus->demodLock = frontend->demod->rsp->dd_status.lock_fec;
		pSignalStatus->lock_l1b= frontend->demod->rsp->atsc3_status.lock_l1b;
		pSignalStatus->lock_l1d= frontend->demod->rsp->atsc3_status.lock_l1d;
		pSignalStatus->bandwidth = (frontend->demod->rsp->atsc3_status.bandwidth) + 6;
		pSignalStatus->plp_exist = frontend->demod->rsp->atsc3_status.plp_exist;
		pSignalStatus->plp_Err_msg = frontend->demod->rsp->atsc3_status.plp_err_msg;

		pSignalStatus->plp_pkerr_0 = frontend->demod->rsp->atsc3_status.plp_pkerr_0;
		pSignalStatus->plp_pkerr_1 = frontend->demod->rsp->atsc3_status.plp_pkerr_1;
		pSignalStatus->plp_pkerr_2 = frontend->demod->rsp->atsc3_status.plp_pkerr_2;
		pSignalStatus->plp_pkerr_3 = frontend->demod->rsp->atsc3_status.plp_pkerr_3;

		if(pSignalStatus->mse_info == 0)
		{
			DEMOD_PRINT("Fail to get the MSE value(mse = %d) \n",pSignalStatus->mse_info);
			pSignalStatus->mse_info = 1;
		}

		if(pSignalStatus->mse_info_demod == 0)
		{
			DEMOD_PRINT("Fail to get the MSE value(mse = %d) \n",pSignalStatus->mse_info_demod);
			pSignalStatus->mse_info_demod = 1;
		}

#ifdef __KERNEL__

		offsetFrq_KHz_val = (frontend->demod->rsp->atsc3_status.cfo & 0x800000) ? (0xff000000 | frontend->demod->rsp->atsc3_status.cfo) : frontend->demod->rsp->atsc3_status.cfo;
		offset_temp = (SINT32) _DEMOD_do_div64_32((offsetFrq_KHz_val * 6912 * 1000), 8388608); //Hz
		pSignalStatus->offsetFrq_Hz = offset_temp;

		offsetFrq_KHz_val = (frontend->demod->rsp->atsc3_status.sfo & 0x800000) ? (0xff000000 | frontend->demod->rsp->atsc3_status.sfo) : frontend->demod->rsp->atsc3_status.sfo;
		offset_temp = (SINT32) _DEMOD_do_div64_32((offsetFrq_KHz_val * 6912 * 1000), 8388608); //Hz
		pSignalStatus->sam_offsetFrq_Hz = offset_temp;

		calcValue =  ((int)((frontend->demod->rsp->atsc3_status.ctf_pwr) * 10)) / ((int)(pSignalStatus->mse_info_demod));

		if(calcValue < 1)
		{
			pSignalStatus->demod_snr = -10;
		}
		else
		{
			//pSignalStatus->snr = (int)(10 * (intlog10((u32)calcValue) / (16777216)));   //16777216 = 2^24;
			temp_snr = intlog10((u32)calcValue);
			temp_snr = (temp_snr-16777216) * 10;
			pSignalStatus->demod_snr = (u32)(temp_snr >> 24);
		}

		constPwr = 65536;
		pSignalStatus->constPwr = constPwr;
		calcValue =  ((int)((pSignalStatus->constPwr) * 10)) / ((int)(pSignalStatus->mse_info));

		if(calcValue < 1)
		{
			pSignalStatus->snr = -10;
		}
		else
		{
			//pSignalStatus->demod_snr(int)(10 * (intlog10((u32)calcValue) / (16777216)));   //16777216 = 2^24;
			temp_snr = (u32)intlog10((u32)calcValue);
			temp_snr = (temp_snr-16777216) * 10;
			pSignalStatus->snr = (u32)(temp_snr >> 24);
		}

#else

		offsetFrq_KHz_val = (frontend->demod->rsp->atsc3_status.cfo & 0x800000) ? (0xff000000 | frontend->demod->rsp->atsc3_status.cfo) : frontend->demod->rsp->atsc3_status.cfo;
		offset_temp =(SINT64) 6912 * offsetFrq_KHz_val * 1000 / 8388608;	//Hz
		pSignalStatus->offsetFrq_Hz = (SINT32) offset_temp;

		//DEMOD_PRINT("offsetFrq_KHz_val = %d\n",offsetFrq_KHz_val);
		//DEMOD_PRINT("offset_temp = %d\n",offset_temp);
		//DEMOD_PRINT("pSignalStatus->offsetFrq_Hz = %d\n",pSignalStatus->offsetFrq_Hz);

		offsetFrq_KHz_val = (frontend->demod->rsp->atsc3_status.sfo & 0x800000) ? (0xff000000 | frontend->demod->rsp->atsc3_status.sfo) : frontend->demod->rsp->atsc3_status.sfo;
		offset_temp =(SINT64) 6912 * offsetFrq_KHz_val * 1000 / 8388608;	//Hz
		pSignalStatus->sam_offsetFrq_Hz = (SINT32) offset_temp;

		// pSignalStatus->snr <== DEMOD SNR information // 160930
		// pSignalStatus->demod_snr <== DEMOD SNR information // 180913
		calcValue =  ((double)(frontend->demod->rsp->atsc3_status.ctf_pwr)) / ((double)(pSignalStatus->mse_info_demod));
		//ORG : //if(calcValue < 0.1)				pSignalStatus->demod_snr = -10;
		//ORG : //else							pSignalStatus->demod_snr  = (SINT32)(10 * log10 ((double)calcValue));
		if(calcValue < 0.1)				pSignalStatus->demod_snr = -10;
		else							pSignalStatus->demod_snr  = (SINT32)(10 * log10 ((double)calcValue));

		constPwr = 65536;
		calcValue =  (double)constPwr / ((double)(pSignalStatus->mse_info));
		pSignalStatus->constPwr = constPwr;
		// pSignalStatus->demod_snr <== EQ SNR information // 160930
		// pSignalStatus->snr <== EQ SNR information // 180913
		//ORG : //if(calcValue < 0.1)				pSignalStatus->snr = -10;
		//ORG : //else							pSignalStatus->snr  = (SINT32)(10 * log10 ((double)calcValue));
		if(calcValue < 0.1)				pSignalStatus->snr = -10;
		else							pSignalStatus->snr  = (SINT32)(10 * log10 ((double)calcValue));
#endif

		pSignalStatus->guardInterval 	= frontend->demod->rsp->atsc3_status.gi;
		pSignalStatus->fftMode 		= frontend->demod->rsp->atsc3_status.fft_mode;
		pSignalStatus->num_PLP 			= frontend->demod->rsp->atsc3_plp_info.num_plp_total;


		if(DEMOD_L2_SendCommand(frontend, DEMOD_DD_ATSC3_PLP_INFO_CMD_CODE) == NO_DEMOD_ERROR)
		{
			pSignalStatus->codeRate = frontend->demod->rsp->atsc3_plp_info.plp_cr;
			pSignalStatus->constellation = frontend->demod->rsp->atsc3_plp_info.plp_mod;
		}

		plp0_en = !((frontend->demod->last_plp0 >>6) & 0x01);
		plp1_en = !((frontend->demod->last_plp1 >>6) & 0x01);
		plp2_en = !((frontend->demod->last_plp2 >>6) & 0x01);
		plp3_en = !((frontend->demod->last_plp3 >>6) & 0x01);
			
		if(plp3_en == 1)
		{
			plp_num_dec = 4;
		}
		else if(plp2_en == 1) 
		{
			plp_num_dec = 3;
		}
		else if(plp1_en == 1)
		{
			plp_num_dec = 2;
		}
		else
		{
			plp_num_dec = 1;
		}

		for(j = 0; j < plp_num_dec; j++)
		{
			DEMOD_L1_GET_DD_ATSC3_PLP_Info(frontend->demod, j);
			for(i = 0; i < sizeof(SqiCnAtsc3P1) / sizeof(LX_DEMOD_SQI_CN_ATSC3P1_T); i++)
			{
				if ( (frontend->demod->rsp->atsc3_plp_info.plp_mod == SqiCnAtsc3P1[i].constel) && (frontend->demod->rsp->atsc3_plp_info.plp_cr == SqiCnAtsc3P1[i].code_rate))
				{
					sn_atsc3_p1_temp = SqiCnAtsc3P1[i].sn_ref;

					if(sn_atsc3_p1 <= sn_atsc3_p1_temp)
					{
						sn_atsc3_p1 = sn_atsc3_p1_temp;
						sqi_mod = frontend->demod->rsp->atsc3_plp_info.plp_mod;
						sqi_cod = frontend->demod->rsp->atsc3_plp_info.plp_cr;
							
					}
					break;
					//i = sizeof(SqiCnAtsc3P1) / sizeof(LX_DEMOD_SQI_CN_ATSC3P1_T);
				}
			}
		}

		snRel = (SINT32)((pSignalStatus->snr * 100) - sn_atsc3_p1);

		if((sqi_mod == DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_16QAM_NUC) && (sqi_cod == DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_2_15))
		{
			snRel = snRel - 100;
		}

		if ( snRel > 600 )			// BER > 5x1e-2
		{
			berSQI = 100;
		}
		else  if ( snRel > 500 )	//  BER > 1e-1
		{
			berSQI = 90;
		}
		else  if ( snRel > 400 )	//  BER > 1e-1
		{
			berSQI = 80;
		}
		else  if ( snRel > 300 )	//  BER > 1e-1
		{
			berSQI = 70;
		}
		else  if ( snRel > 200 )	//  BER > 1e-1
		{
			berSQI = 60;
		}
		else  if ( snRel > 100 )	//  BER > 1e-1
		{
			berSQI = 50;
		}
		else  if ( snRel > 0 )	//  BER > 1e-1
		{
			berSQI = 40;
		}
		else  if ( snRel > -100 )	//  BER > 1e-1
		{
			berSQI = 30;
		}
		else  if ( snRel > -200 )	//  BER > 1e-1
		{
			berSQI = 20;
		}
		else
		{
			berSQI = 10;
		}

		if(pSignalStatus->packetError > 0)
			pSignalStatus->signalQuality = berSQI - 10;
		else
			pSignalStatus->signalQuality = berSQI;


		if(pSignalStatus->signalQuality > 100) pSignalStatus->signalQuality = 100;


	//#endif

		pSignalStatus->ldpc_err = frontend->demod->rsp->atsc3_status.ldpc_err;
		pSignalStatus->plp_outer_err = frontend->demod->rsp->atsc3_status.plp_outer_err;
		pSignalStatus->plp_ldpc_iter = frontend->demod->rsp->atsc3_status.plp_ldpc_iter;
		pSignalStatus->l1b_ldpc_iter = frontend->demod->rsp->atsc3_status.l1b_ldpc_iter;
		pSignalStatus->l1d_ldpc_iter = frontend->demod->rsp->atsc3_status.l1d_ldpc_iter;
		} break;

	case DEMOD_DD_MODE_PROP_MODULATION_ISDBT: {
		UINT8 segNum_a;
		UINT8 segNum_b;
		UINT8 segNum_c;

		retc = DEMOD_L1_GET_DD_ISDBT_Status(frontend->demod);
		if(NO_DEMOD_ERROR != retc) {
			DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_ISDBT_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
			return retc;
		}

  		retc = DEMOD_L1_GET_DD_ISDBT_TMCC_Info(frontend->demod);
		if(NO_DEMOD_ERROR != retc) {
			DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_ISDBT_TMCC_Info() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
			return retc;
		}

		segNum_a = frontend->demod->rsp->isdbt_tmcc_info.onsega;
		segNum_b = frontend->demod->rsp->isdbt_tmcc_info.onsegb;
		segNum_c = frontend->demod->rsp->isdbt_tmcc_info.onsegc;

		pSignalStatus->ber = frontend->demod->rsp->isdbt_status.ber;
		pSignalStatus->if_agc = frontend->demod->rsp->isdbt_status.if_agc;

		pSignalStatus->mse_info_eq = frontend->demod->rsp->isdbt_status.mse_info; // 171123
		if(pSignalStatus->mse_info_eq == 0) {
//			DEMOD_WARN("[DEMOD_API] FAIL, get the MSE_EQ value(mse_eq = %d)\n", pSignalStatus->mse_info_eq);
			pSignalStatus->mse_info_eq = 1;
		}

		pSignalStatus->constPwr_eq = 16384;
		pSignalStatus->constPwr = pSignalStatus->constPwr_eq;
		pSignalStatus->mse_info = pSignalStatus->mse_info_eq;

		pSignalStatus->mse_info_demod = frontend->demod->rsp->isdbt_status.mse_info_demod; // 171123
		if(pSignalStatus->mse_info_demod == 0) {
//			DEMOD_WARN("[DEMOD_API] FAIL, get the MSE_DEMOD value(mse_demod = %d)\n",pSignalStatus->mse_info_demod);
			pSignalStatus->mse_info_demod = 1;
		}

		pSignalStatus->constPwr = 3024;
		pSignalStatus->mse_info = pSignalStatus->mse_info_demod;
		pSignalStatus->operatingMode = frontend->demod->rsp->isdbt_status.op_mode;
		pSignalStatus->packetError = (UINT32)(frontend->demod->rsp->isdbt_status.pe);
		pSignalStatus->spInv = frontend->demod->rsp->isdbt_status.spInv;
		pSignalStatus->demodLock = frontend->demod->rsp->isdbt_status.lock_fec;

		if((segNum_a > segNum_b) && (segNum_a > segNum_c)) {
			pSignalStatus->constellation = frontend->demod->rsp->isdbt_tmcc_info.oqama;
		} else if((segNum_b > segNum_a) && (segNum_b > segNum_c)) {
			pSignalStatus->constellation = frontend->demod->rsp->isdbt_tmcc_info.oqamb;

		} else if((segNum_c > segNum_a) && (segNum_c > segNum_b)) {
			pSignalStatus->constellation =frontend->demod->rsp->isdbt_tmcc_info.oqamc;

		} else {
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

		if(calcValue < 0.1)
			pSignalStatus->snr_eq = -10;
		else
			pSignalStatus->snr_eq = (UINT32)(10*log10(calcValue));
		calcValue =  (double)(pSignalStatus->constPwr) / (double)(pSignalStatus->mse_info_demod);

		if(calcValue < 0.1)
			pSignalStatus->snr_demod = -10;
		else
			pSignalStatus->snr_demod = (UINT32)(10*log10(calcValue));
#endif
		pSignalStatus->snr = pSignalStatus->snr_demod;
		} break;

	case DEMOD_DD_MODE_PROP_MODULATION_DVBT : {
  		retc = DEMOD_L1_GET_DD_DVBT_Status(frontend->demod);
		if(NO_DEMOD_ERROR != retc) {
			DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_DVBT_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
			return retc;
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

		if(pSignalStatus->hierarchy_sel == DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_SEL_HP) {
			pSignalStatus->codeRate = frontend->demod->rsp->dvbt_status.hp_cr;
		} else {
			pSignalStatus->codeRate = frontend->demod->rsp->dvbt_status.lp_cr;
		}

		if(pSignalStatus->mse_info_eq == 0) {
			DEMOD_PRINT("Fail to get the MSE_EQ value(mse_eq = %d)\n",pSignalStatus->mse_info_eq);
			pSignalStatus->mse_info_eq = 1;
		}

		if(pSignalStatus->mse_info_demod == 0) {
			DEMOD_PRINT("Fail to get the MSE_DEMOD value(mse_demod = %d)\n",pSignalStatus->mse_info_demod);
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

		if(calcValue < 0.1)
			pSignalStatus->snr_eq = -10;
		else
			pSignalStatus->snr_eq = (UINT32)(10*log10(calcValue));

		calcValue =  (double)(pSignalStatus->constPwr) / (double)(pSignalStatus->mse_info_demod);

		if(calcValue < 0.1)
			pSignalStatus->snr_demod = -10;
		else
			pSignalStatus->snr_demod = (UINT32)(10*log10(calcValue));
#endif
		pSignalStatus->snr = pSignalStatus->snr_demod;
		} break;

	case DEMOD_DD_MODE_PROP_MODULATION_DVBT2 : {
		retc = DEMOD_L1_GET_DD_DVBT2_Status(frontend->demod);
		if(NO_DEMOD_ERROR != retc) {
			DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_DVBT2_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
			return retc;
		}

		pSignalStatus->ber 		= frontend->demod->rsp->dvbt2_status.ber;
		pSignalStatus->constellation 	= frontend->demod->rsp->dvbt2_status.constellation;
		pSignalStatus->if_agc 		= frontend->demod->rsp->dvbt2_status.if_agc;

		pSignalStatus->mse_info_eq 	= frontend->demod->rsp->dvbt2_status.mse_info;
		pSignalStatus->mse_info_demod 	= frontend->demod->rsp->dvbt2_status.mse_info_demod;

		pSignalStatus->operatingMode 	= frontend->demod->rsp->dvbt2_status.op_mode;
		pSignalStatus->packetError 	= (UINT32)(frontend->demod->rsp->dvbt2_status.pe);
		pSignalStatus->spInv 		= frontend->demod->rsp->dvbt2_status.spInv;
		pSignalStatus->demodLock 	= frontend->demod->rsp->dvbt2_status.lock_fec;
		pSignalStatus->guardInterval 	= frontend->demod->rsp->dvbt2_status.gi;
		pSignalStatus->codeRate 	= frontend->demod->rsp->dvbt2_status.cr;
		pSignalStatus->fftMode 		= frontend->demod->rsp->dvbt2_status.fft_mode;
		pSignalStatus->offsetFrq_Hz 	= (frontend->demod->rsp->dvbt2_status.cfo & 0x800000) ? (0xff000000 | frontend->demod->rsp->dvbt2_status.cfo) : frontend->demod->rsp->dvbt2_status.cfo;
		pSignalStatus->bandwidth 	= frontend->demod->prop->dd_mode.bw;
		pSignalStatus->num_PLP 		= frontend->demod->rsp->dvbt2_status.num_plp;
		pSignalStatus->bw_Ext		= frontend->demod->rsp->dvbt2_status.bw_ext;
		pSignalStatus->current_plp_id	= frontend->demod->rsp->dvbt2_status.current_plp_id;
		pSignalStatus->cell_id		= frontend->demod->rsp->dvbt2_status.cell_id;

		if(pSignalStatus->mse_info_eq == 0) {
			DEMOD_PRINT("Fail to get the MSE_EQ value(mse_eq = %d)\n",pSignalStatus->mse_info_eq);
			pSignalStatus->mse_info_eq = 1;
		}

		if(pSignalStatus->mse_info_demod == 0) {
			DEMOD_PRINT("Fail to get the MSE_DEMOD value(mse_demod = %d)\n",pSignalStatus->mse_info_demod);
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

		if(calcValue < 0.1)
			pSignalStatus->snr_eq = -10;
		else
			pSignalStatus->snr_eq = (UINT32)(10*log10(calcValue));
		calcValue =  (double)(pSignalStatus->constPwr) / (double)(pSignalStatus->mse_info_demod);

		if(calcValue < 0.1)
			pSignalStatus->snr_demod = -10;
		else
			pSignalStatus->snr_demod = (UINT32)(10*log10(calcValue));
#endif
		pSignalStatus->snr = pSignalStatus->snr_demod;
		} break;

	case DEMOD_DD_MODE_PROP_MODULATION_DVBC : {
		retc = DEMOD_L1_GET_DD_DVBC_Status(frontend->demod);
		if(NO_DEMOD_ERROR != retc) {
			DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_DVBC_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
			return retc;
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

		if(pSignalStatus->mse_info == 0) {
			DEMOD_PRINT("Fail to get the MSE value(mse = %d)\n",pSignalStatus->mse_info);
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
		} break;

	case DEMOD_DD_MODE_PROP_MODULATION_DVBC2 : {
		retc = DEMOD_L1_GET_DD_DVBC2_Status(frontend->demod );
		if(NO_DEMOD_ERROR != retc) {
			DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_DVBC2_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
			return retc;
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
		} break;

	case DEMOD_DD_MODE_PROP_MODULATION_DVBS : {
		retc = DEMOD_L1_GET_DD_DVBS_Status(frontend->demod);
		if(NO_DEMOD_ERROR != retc) {
			DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_DVBS_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
			return retc;
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

		if(pSignalStatus->mse_info == 0) {
			DEMOD_PRINT("Fail to get the MSE value(mse = %d)\n",pSignalStatus->mse_info);
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
		} break;

	case DEMOD_DD_MODE_PROP_MODULATION_DVBS2: {
		retc = DEMOD_L1_GET_DD_DVBS2_Status(frontend->demod);
		if(NO_DEMOD_ERROR != retc) {
			DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_DVBS2_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
			return retc;
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

		if(pSignalStatus->mse_info == 0) {
			DEMOD_PRINT("Fail to get the MSE value(mse = %d)\n",pSignalStatus->mse_info);
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
		break;

	case DEMOD_DD_MODE_PROP_MODULATION_DTMB :
		retc = DEMOD_L1_GET_DD_DTMB_Status(frontend->demod );
		if(NO_DEMOD_ERROR != retc) {
			DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_DTMB_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
			return retc;
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

		if(pSignalStatus->mse_info == 0) {
			DEMOD_PRINT("Fail to get the MSE value(mse = %d)\n",pSignalStatus->mse_info);
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
		} break;

	default :
  		return -ERROR_DEMOD_ERROR;
	}

	return NO_DEMOD_ERROR;
}


/************************************************************************************************************************
  DEMOD_L2_Get_TsClkStatus function
  Use:        standard text retrieval function
  Parameter:  standard, the value of the standard
************************************************************************************************************************/
int DEMOD_L2_Get_TsClkStatus (LX_DEMOD_L2_Context *frontend, UINT32 *pTsClkRate)
{
	int retc = 0;

	retc = DEMOD_L1_GET_DD_TSCLK_Status(frontend->demod);

	if(NO_DEMOD_ERROR != retc) {
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_TSCLK_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
		*pTsClkRate = DEMOD_DD_TSCLK_STATUS_RESPONSE_TSCLKRATE_UNKNOWN ;
		return retc;
	}

	*pTsClkRate = frontend->demod->rsp->dd_tsclk_status.tsClkRate ;

	DEMOD_NOTI("[DEMOD_API]  *pTsClkRate = %d , frontend->demod->rsp->dd_tsclk_status.tsClkRate = %d\n", *pTsClkRate , frontend->demod->rsp->dd_tsclk_status.tsClkRate);


	return NO_DEMOD_ERROR;
}



/************************************************************************************************************************
  DEMOD_L2_SendCommand function
  Use:        Sends commands
  Parameter:  standard, the value of the standard
************************************************************************************************************************/
int DEMOD_L2_SendCommand (LX_DEMOD_L2_Context *frontend, UINT32 cmd_code)
{
	return DEMOD_L1_SendCommand2(frontend->demod, cmd_code);

}
/************************************************************************************************************************
  DEMOD_L2_Set_Property function
  Use:        Sets up property
  Parameter:  standard, the value of the standard
************************************************************************************************************************/
int DEMOD_L2_Set_Property (LX_DEMOD_L2_Context *frontend, UINT32 prop_code)
{
	return DEMOD_L1_Set_Property(frontend->demod, prop_code);
}

/************************************************************************************************************************
  DEMOD_L2_Set_Property function
  Use:        Sets up property
  Parameter:  standard, the value of the standard
************************************************************************************************************************/
int DEMOD_L2_Get_Property (LX_DEMOD_L2_Context *frontend, UINT32 prop_code)
{
	return DEMOD_L1_Get_Packed_Property(frontend->demod, prop_code);
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_GET_REG.
 * reads the DBB registers
 *
 * @param *frontend 		[IN] LX_DEMOD_L2_Context
 * @param addr 			[IN] UINT16
 * @param length 			[IN] UINT8
 * @param *readData 		[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_GET_REG (LX_DEMOD_L2_Context *frontend, UINT16  addr, UINT8 length, UINT8 *readData)
{
	int retc = NO_DEMOD_ERROR;

	UINT8 addrMsb = 0;
	UINT8 addrLsb = 0;

	UINT8 rdCount;

	addrMsb = (UINT8)((addr >> 8) & 0xff);
	addrLsb = (UINT8)(addr & 0xff);

	retc = DEMOD_L1_GET_DD_Reg(frontend->demod, addrMsb, addrLsb, length);

	if (NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_Reg() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
		return -ERROR_DEMOD_READ;
	}

	for(rdCount =0; rdCount < length; rdCount++)
	{
		//DEMOD_PRINT(" Register [0x%x] = 0x%x \n", addr + rdCount, frontend->demod->rsp->dd_get_reg.mData[rdCount]);
		readData[rdCount] =  frontend->demod->rsp->dd_get_reg.mData[rdCount];
	}
	return NO_DEMOD_ERROR;
}


int DEMOD_L2_GET_REG_MAP (LX_DEMOD_L2_Context *frontend, UINT16  addr, UINT16 length, UINT8 *readData)
{
	int retc = NO_DEMOD_ERROR;

	UINT8 addrMsb = 0;
	UINT8 addrLsb = 0;

	addrMsb = (UINT8)((addr >> 8) & 0xff);
	addrLsb = (UINT8)(addr & 0xff);

	retc = DEMOD_L1_GET_DD_Reg_Map(frontend->demod, addrMsb, addrLsb, length, readData);

	if (NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_Reg_Map() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
		return -ERROR_DEMOD_READ;
	}

	return NO_DEMOD_ERROR;
}
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_SET_REG.
 * writes the DBB registers
 *
 * @param *frontend 		[IN] LX_DEMOD_L2_Context
 * @param addr 			[IN] UINT16
 * @param length 			[IN] UINT8
 * @param wrData 			[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_SET_REG (LX_DEMOD_L2_Context *frontend,  UINT16  addr, UINT8 length, UINT32   wrData)
{
	int retc = NO_DEMOD_ERROR;

	UINT8 addrMsb = 0;
	UINT8 addrLsb = 0;

	addrMsb = (UINT8)((addr >> 8) & 0xff);
	addrLsb = (UINT8)(addr & 0xff);

	retc = DEMOD_L1_SET_DD_Reg(frontend->demod, addrMsb, addrLsb, length, wrData);
	if (NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_SET_DD_Reg() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
		return -ERROR_DEMOD_WRITE;
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
int DEMOD_L2_Tuner_I2C_Enable (LX_DEMOD_L2_Context *frontend)
{
	return DEMOD_L1_SET_DD_Repeat(frontend->demod->chip, DEMOD_DD_GET_REPEAT_CMD_ENABLE);
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

int DEMOD_L2_Tuner_I2C_Disable (LX_DEMOD_L2_Context *frontend)
{
	return DEMOD_L1_SET_DD_Repeat(frontend->demod->chip, DEMOD_DD_GET_REPEAT_CMD_DISABLE);
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

int DEMOD_L2_Get_PartInfo (LX_DEMOD_L2_Context *frontend, LX_DEMOD_L2_PART_INFO *fwInfo)
{
	int retc = 0;

	retc = DEMOD_L1_GET_DD_PartInfo(frontend->demod);

	if(NO_DEMOD_ERROR != retc)
	{
		fwInfo->fw_major = 0x0;
		fwInfo->fw_minor = 0x0;
		fwInfo->fw_year = 0x0;
		fwInfo->fw_month = 0x0;
		fwInfo->fw_day = 0x0;
		fwInfo->chip_type = 0xff;
		fwInfo->chip_rev = 0xff;

		return retc;
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

int DEMOD_L2_GetDump (LX_DEMOD_L2_Context *frontend)
{
	int retc = NO_DEMOD_ERROR;

	DEMOD_DEBUG("____________________DUMP____________________\n");
	DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_DD_BER_RESOL_PROP_CODE);
	DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_DD_IF_FREQ_PROP_CODE);
#ifdef DEMOD_DD_CLOCK_MODE_PROP
	DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_DD_CLOCK_MODE_PROP_CODE);
#endif
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

	retc = DEMOD_L1_GET_DD_Status(frontend->demod);
	if (NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_GET_DD_Status() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
	}

	DEMOD_L1_CommandText(frontend->demod->rsp, DEMOD_DD_STATUS_CMD);

	switch (frontend->demod->rsp->dd_status.reply_operMod)
	{
	 	case DEMOD_DD_MODE_PROP_MODULATION_VSB :
			DEMOD_L1_GET_DD_VSB_Status(frontend->demod);
			DEMOD_L1_CommandText          (frontend->demod->rsp, DEMOD_DD_VSB_STATUS_CMD);
			break;

		case DEMOD_DD_MODE_PROP_MODULATION_ATSC3:
			DEMOD_L1_GET_DD_ATSC3_Status(frontend->demod);
			DEMOD_L1_CommandText          (frontend->demod->rsp, DEMOD_DD_ATSC3_STATUS_CMD);
			DEMOD_L1_GET_DD_ATSC3_PLP_Info(frontend->demod, frontend->set_PLP_ID);
			DEMOD_L1_CommandText          (frontend->demod->rsp, DEMOD_DD_ATSC3_PLP_INFO_CMD);
			break;

		case DEMOD_DD_MODE_PROP_MODULATION_QAM:
			DEMOD_L1_GET_DD_QAM_Status(frontend->demod);
			DEMOD_L1_CommandText          (frontend->demod->rsp, DEMOD_DD_QAM_STATUS_CMD);
			break;

		case DEMOD_DD_MODE_PROP_MODULATION_ISDBT:
			DEMOD_L1_GET_DD_ISDBT_Status(frontend->demod);
			DEMOD_L1_CommandText          (frontend->demod->rsp, DEMOD_DD_ISDBT_STATUS_CMD);
			DEMOD_L1_GET_DD_ISDBT_TMCC_Info(frontend->demod);
			DEMOD_L1_CommandText          (frontend->demod->rsp, DEMOD_DD_ISDBT_TMCC_INFO_CMD);
			break;

		case DEMOD_DD_MODE_PROP_MODULATION_DVBT:
			DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_DD_DVBT_HIERARCHY_PROP_CODE);
			DEMOD_L1_GET_DD_DVBT_Status(frontend->demod);
			DEMOD_L1_CommandText          (frontend->demod->rsp, DEMOD_DD_DVBT_STATUS_CMD);
			break;

		case DEMOD_DD_MODE_PROP_MODULATION_DVBT2:
			DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_DD_DVBT2_MODE_PROP_CODE);
			DEMOD_L1_GET_DD_DVBT2_Status(frontend->demod);
			DEMOD_L1_CommandText          (frontend->demod->rsp, DEMOD_DD_DVBT2_STATUS_CMD);
			break;

	 	case DEMOD_DD_MODE_PROP_MODULATION_DVBC:
			DEMOD_L1_GET_DD_DVBC_Status(frontend->demod);
			DEMOD_L1_CommandText          (frontend->demod->rsp, DEMOD_DD_DVBC_STATUS_CMD);
			break;

		case DEMOD_DD_MODE_PROP_MODULATION_DVBS:
			DEMOD_L1_PropertyText(frontend->demod->prop, DEMOD_DD_DVBS_OPMSEL_PROP_CODE);
			DEMOD_L1_GET_DD_DVBS_Status(frontend->demod);
			DEMOD_L1_CommandText          (frontend->demod->rsp, DEMOD_DD_DVBS_STATUS_CMD);
			break;

		case DEMOD_DD_MODE_PROP_MODULATION_DVBS2:
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

int DEMOD_L2_Set_ChipInfo (LX_DEMOD_L2_Context *frontend, UINT16 chip_ver, UINT8 chip_if)
{
	//DEMOD_PRINT("+++++++++++++++ chip_ver = %x++++++++++++++++\n",chip_ver);
	frontend->demod->chip->chip_ver 	= (UINT8) ((chip_ver >> 8) & 0xff);
	frontend->demod->chip->chip_rev 	= (UINT8) ((chip_ver >> 0) & 0xff);

	/* select interface IF_SOC(0) or IF_EXT(1) */
	frontend->demod->chip->chip_if		= chip_if & 0x1;

	return NO_DEMOD_ERROR;
}

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
int DEMOD_L2_Set_MemAddr (LX_DEMOD_L2_Context *frontend, UINT64 baseAddr)
{
	int retc = NO_DEMOD_ERROR;

	DEMOD_INFO("[DEMOD_API] Start\n");

	/* Pointers initialization */
	frontend->baseAddr = baseAddr;

	return retc;
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
int DEMOD_L2_PowerUpWithMem (LX_DEMOD_L2_Context *frontend)
{
	int retc = NO_DEMOD_ERROR;
	retc = NO_DEMOD_ERROR;

	/* Before patching, set POWER_UP values for 'RESET' and 'BOOTLOADER' */

	retc = DEMOD_L1_API_LoadFirmware_MEM(frontend->demod, (UINT32)frontend->baseAddr);

	if (NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("[DEMOD_API] ERROR DEMOD_L1_API_LoadFirmware_MEM() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

/*
	retc = DEMOD_L1_API_StartFirmware(frontend->demod) ;
	if (NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("[DEMOD_API] ERROR DEMOD_L1_API_StartFirmware() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}
*/

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
int DEMOD_L2_InitMem (LX_DEMOD_L2_Context *frontend)
{
	int retc = NO_DEMOD_ERROR;
	DEMOD_INFO("[DEMOD_API] Start\n");

	if ((retc = DEMOD_L2_PowerUpWithMem(frontend)) != NO_DEMOD_ERROR)
	{   /* PowerUp into bootloader */
		DEMOD_ERROR("[DEMOD_API] ERROR DEMOD_L2_PowerUpWithMem() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

	DEMOD_L0_system_wait(10);

	/* At this point, FW is loaded and started.  */
	retc = DEMOD_L2_Configure(frontend);
	if(NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("[DEMOD_API] ERROR DEMOD_L2_Configure() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

	frontend->demod_init_done = 1;

	DEMOD_INFO("[DEMOD_API] End\n");
	return NO_DEMOD_ERROR;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_Set_SoftRst.
 * send SoftReset cmd to MCU
 *
 * @param *frontend [IN] LX_DEMOD_L2_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_Set_SoftRst (LX_DEMOD_L2_Context * frontend, UINT8 softrstb, UINT8 softrstsyncb, UINT8 softrsteq1b, UINT8 softrsteq2b, UINT8 softrstdiseqcb, UINT8 softrstfecb, UINT8 softrsttpifb)
{
	int retc = NO_DEMOD_ERROR;

	DEMOD_INFO("[DEMOD_API] Start\n");

	retc = DEMOD_L1_SET_DD_SoftRst(frontend->demod, 1,0,0,0,0,0,0);

	return retc;
}

/**/


