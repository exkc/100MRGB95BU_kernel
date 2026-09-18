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
**  Name:DBB_DEMOD_L1_API.c
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

#include "DBB_DEMOD_L1_API.h"
#include "DBB_DEMOD_L1_Properties_Functions.h"
#include "DBB_DEMOD_L1_Commands_Prototypes.h"


/***********************************************************************************************************************
  DEMOD_L1_API_Init function
  Use:        software initialisation function
              Used to initialize the software context
  Returns:    0 if no error
  Comments:   It should be called first and once only when starting the application
  Parameter:   **ppapi         a pointer to the api context to initialize
  Parameter:  add            the LGDBB I2C address
  Porting:    Allocation errors need to be properly managed.
  Porting:    I2C initialization needs to be adapted to use the available I2C functions
 ***********************************************************************************************************************/
UINT8    DEMOD_L1_API_Init      (LX_DEMOD_L1_Context *api, UINT32 add)
{
    api->i2c = &(api->i2cObj);

    DEMOD_L0_Init(api->i2c);
    DEMOD_L0_SetAddress(api->i2c, add, 2);

    api->cmd               	= &(api->cmdObj);
    api->rsp               	= &(api->rspObj);
    api->prop              	= &(api->propObj);
    api->status            	= &(api->statusObj);
    api->propShadow   	= &(api->propShadowObj);
    // Set the propertyWriteMode to DEMOD_DOWNLOAD_ON_CHANGE to only download property settings on change (recommended)
    //      if propertyWriteMode is set to DEMOD_DOWNLOAD_ALWAYS the properties will be downloaded regardless of change
    api->propertyWriteMode = DEMOD_DD_DOWNLOAD_ON_CHANGE;//DEMOD_DD_DOWNLOAD_ON_CHANGE ; // DEMOD_DD_DOWNLOAD_ALWAYS;
    // SPI download default values

	DEMOD_L0_InitDevice();

    return NO_DEMOD_ERROR;
}




/***********************************************************************************************************************
  DEMOD_L1_API_Patch_I function
  Use:        Patch information function
              Used to send a number of bytes to the DBB. Useful to download the firmware.
  Returns:    0 if no error
  Parameter:  error_code the error code.
  Porting:    Useful for application development for debug purposes.
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
UINT8    DEMOD_L1_API_Patch_I     (LX_DEMOD_L1_Context *api, UINT16 addr, UINT32 iNbBytes, UINT8 *pucDataBuffer)
{
	SINT32 j=0,k=0;
	UINT8 *addr_org = pucDataBuffer;
	UINT8 rdData=0;

	j=iNbBytes;
	k=0;

	pucDataBuffer = addr_org;

#ifdef FPGA_CPBOX

	UINT8 chip_id=0;

	if(api->i2c->chipVer >= L18F)
	{
		chip_id=0xb2;
	}
	else
	{
		chip_id=0x26;
	}

	api->i2c->slvAddr=chip_id;
	api->i2c->handle = (api->i2c->handle & 0xffffff00) + api->i2c->slvAddr;
#endif

	if(api->i2c->chipVer >= L18F)
	{
		UINT8 wrData[4] = {0, };

		addr = 0x0;
		api->i2c->inDirect = 0;
		DEMOD_L0_WordToByte (0x40000000, wrData);
		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(api->i2c, 0xF024, 1, wrData)) return ERROR_DEMOD_LOADING_FIRMWARE;

		while(j>0)
		{
			api->i2c->inDirect = 1;

			if(j >= 0xfc)
			{
				if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(api->i2c, addr, 0xfc, pucDataBuffer+k)) return ERROR_DEMOD_LOADING_FIRMWARE;
			}
			else
			{
				if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(api->i2c, addr, j, pucDataBuffer+k)) return ERROR_DEMOD_LOADING_FIRMWARE;
			}

			addr += 0xfc;
			k += 0xfc;
			j -= 0xfc;

		}
		api->i2c->inDirect = 0;

	}

	else
	{
		UINT8 wrData = 0;

		if(NO_DEMOD_ERROR != DEMOD_L0_Fast_ReadCommandBytes(api->i2c, 0x7000, 1, &rdData)) return ERROR_DEMOD_LOADING_FIRMWARE;
		wrData = rdData & 0xef;
		if(NO_DEMOD_ERROR != DEMOD_L0_Fast_WriteCommandBytes(api->i2c, 0x7000, 1, &wrData)) return ERROR_DEMOD_LOADING_FIRMWARE;

		if(NO_DEMOD_ERROR != DEMOD_L0_Fast_ReadCommandBytes(api->i2c, 0x7005, 1, &rdData)) return ERROR_DEMOD_LOADING_FIRMWARE;
		wrData = rdData | 0x80;
		if(NO_DEMOD_ERROR != DEMOD_L0_Fast_WriteCommandBytes(api->i2c, 0x7005, 1, &wrData)) return ERROR_DEMOD_LOADING_FIRMWARE;


		while(j>0)
		{

			addr = ((k /0x100+0x80)<<8) |(k%0x100);

			if(j >= 0xff)
			{
				if(NO_DEMOD_ERROR != DEMOD_L0_Fast_WriteCommandBytes(api->i2c, addr, 0xff, pucDataBuffer+k)) return ERROR_DEMOD_LOADING_FIRMWARE;
			}
			else
			{
				if(NO_DEMOD_ERROR != DEMOD_L0_Fast_WriteCommandBytes(api->i2c, addr, j, pucDataBuffer+k)) return ERROR_DEMOD_LOADING_FIRMWARE;
			}

			k += 0xff;
			j -= 0xff;

		}

		if(NO_DEMOD_ERROR != DEMOD_L0_Fast_ReadCommandBytes(api->i2c, 0x7005, 1, &rdData)) return ERROR_DEMOD_LOADING_FIRMWARE;
		wrData = rdData & 0x7f;
		if(NO_DEMOD_ERROR != DEMOD_L0_Fast_WriteCommandBytes(api->i2c, 0x7005, 1, &wrData)) return ERROR_DEMOD_LOADING_FIRMWARE;
	}

	//DBB_PRINT("IRAM Download Done : \n");

    return NO_DEMOD_ERROR;
}


/***********************************************************************************************************************
  DEMOD_L1_API_Patch_D function
  Use:        Patch information function
              Used to send a number of bytes to the DBB. Useful to download the firmware.
  Returns:    0 if no error
  Parameter:  error_code the error code.
  Porting:    Useful for application development for debug purposes.
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
UINT8    DEMOD_L1_API_Patch_D     (LX_DEMOD_L1_Context *api, UINT16 addr, UINT32 iNbBytes, UINT8 *pucDataBuffer)
{
	SINT32 j=0,k=0;
	UINT8 *addr_org = pucDataBuffer;
	UINT8 wrData=0;
	UINT8 rdData=0;

	j=iNbBytes;
	k=0;
	pucDataBuffer = addr_org;

#ifdef FPGA_CPBOX
	
	UINT8 chip_id=0;
	if(api->i2c->chipVer >= L18F)
	{
		chip_id=0xb2;
	}
	else
	{
		chip_id=0x26;
	}

	api->i2c->slvAddr=chip_id;
	api->i2c->handle = (api->i2c->handle & 0xffffff00) + api->i2c->slvAddr;
#endif

	if(api->i2c->chipVer >= L18F)
	{
		UINT8 wrData[4] = {0, };
		addr = 0x0;
		api->i2c->inDirect = 0;
		DEMOD_L0_WordToByte (0x3FFE0000, wrData);
		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(api->i2c, 0xF024, 1, wrData)) return ERROR_DEMOD_LOADING_FIRMWARE;

		while(j>0)
		{
			api->i2c->inDirect = 1;

			if(j >= 0xfc)
			{
				if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(api->i2c, addr, 0xfc, pucDataBuffer+k)) return ERROR_DEMOD_LOADING_FIRMWARE;
			}
			else
			{
				if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(api->i2c, addr, j, pucDataBuffer+k)) return ERROR_DEMOD_LOADING_FIRMWARE;
			}

			addr += 0xfc;
			k += 0xfc;
			j -= 0xfc;

		}
		api->i2c->inDirect = 0;

	}
	else
	{
		if(NO_DEMOD_ERROR != DEMOD_L0_Fast_ReadCommandBytes(api->i2c, 0x7000, 1, &rdData)) return ERROR_DEMOD_LOADING_FIRMWARE;
		wrData = rdData & 0xef;
		if(NO_DEMOD_ERROR != DEMOD_L0_Fast_WriteCommandBytes(api->i2c, 0x7000, 1, &wrData)) return ERROR_DEMOD_LOADING_FIRMWARE;

		if(NO_DEMOD_ERROR != DEMOD_L0_Fast_ReadCommandBytes(api->i2c, 0x7005, 1, &rdData)) return ERROR_DEMOD_LOADING_FIRMWARE;
		wrData = rdData | 0x80;
		if(NO_DEMOD_ERROR != DEMOD_L0_Fast_WriteCommandBytes(api->i2c, 0x7005, 1, &wrData)) return ERROR_DEMOD_LOADING_FIRMWARE;

		while(j>0)
		{

			addr = ((k /0x100)<<8) |(k%0x100);

			if(j >= 0xff)
			{
				if(NO_DEMOD_ERROR != DEMOD_L0_Fast_WriteCommandBytes(api->i2c, addr, 0xff, pucDataBuffer+k)) return ERROR_DEMOD_LOADING_FIRMWARE;
			}
			else
			{
				if(NO_DEMOD_ERROR != DEMOD_L0_Fast_WriteCommandBytes(api->i2c, addr, j, pucDataBuffer+k)) return ERROR_DEMOD_LOADING_FIRMWARE;
			}

			k += 0xff;
			j -= 0xff;

		}

		if(NO_DEMOD_ERROR != DEMOD_L0_Fast_ReadCommandBytes(api->i2c, 0x7005, 1, &rdData)) return ERROR_DEMOD_LOADING_FIRMWARE;
		wrData = rdData & 0x7f;
		if(NO_DEMOD_ERROR != DEMOD_L0_Fast_WriteCommandBytes(api->i2c, 0x7005, 1, &wrData)) return ERROR_DEMOD_LOADING_FIRMWARE;
	}

    return NO_DEMOD_ERROR;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_API_LoadFirmware_IRAM.
 * Load firmware from FIRMWARE_TABLE array in DBB_Firmware_x_y_build_z.h file into DBB modulator IRAM.
 *
 * @param *api 		[IN] LX_DEMOD_L1_Context
 * @param fw_table[] 	[IN] LX_DEMOD_FIRMWARE_STRUCT
 * @param nbLines 	[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_API_LoadFirmware_IRAM	(LX_DEMOD_L1_Context *api, LX_DEMOD_FIRMWARE_STRUCT fw_table[], UINT8 nbLines)
{
    int return_code;
    int line, load_start_ms;


    //DBB_PRINT ("DEMOD_LoadFirmware IRAM starting...\n");
    //DBB_PRINT ("DEMOD_LoadFirmware IRAM nbLines %d\n", nbLines);
    load_start_ms = DEMOD_L0_system_time();

    /* for each line in fw_table */
    for (line = 0; line < nbLines; line++)
    {
		if (fw_table[line].firmware_size > 0)  /* don't download if length is 0 , e.g. dummy firmware */
		{
			//DBB_PRINT(" fw_table[%x].firmware_size : %x\n", line,fw_table[line].firmware_size);
			return_code = DEMOD_L1_API_Patch_I(api, fw_table[line].firmware_addr, fw_table[line].firmware_size, fw_table[line].firmware_table);
			if (return_code != 0)
			{
			  	DBB_PRINT("DEMOD_L2_LoadFirmware_IRAM error 0x%02x patching line %d: %s\n", return_code, line, DEMOD_L1_API_Error_Text(return_code) );
				return ERROR_DEMOD_LOADING_FIRMWARE;
			}

		}

		if (line==0)
		{
			if (DEMOD_L0_system_time() - load_start_ms > 200)
			{
				DBB_PRINT ("DEMOD_LoadFirmware line 1 took too much time!\n");
			}
			//DBB_PRINT ("DEMOD_LoadFirmware line 1 took %4d ms\n", DEMOD_L0_system_time() - load_start_ms);
		}

    }

    DBB_PRINT ("DEMOD_LoadFirmware IRAM took %4d ms\n", DEMOD_L0_system_time() - load_start_ms);
    return NO_DEMOD_ERROR;
}




/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_API_LoadFirmware_DRAM.
 * Load firmware from FIRMWARE_TABLE array in DBB_Firmware_x_y_build_z.h file into DBB modulator DRAM.
 *
 * @param *api 		[IN] LX_DEMOD_L1_Context
 * @param fw_table[] 	[IN] LX_DEMOD_FIRMWARE_STRUCT
 * @param nbLines 	[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_API_LoadFirmware_DRAM(LX_DEMOD_L1_Context *api, LX_DEMOD_FIRMWARE_STRUCT fw_table[], UINT8 nbLines)
{
    int return_code;
    int line, load_start_ms;

    //DBB_PRINT ("DEMOD_LoadFirmware DRAM starting...\n");
    //DBB_PRINT ("DEMOD_LoadFirmware DRAM nbLines %d\n", nbLines);
    load_start_ms = DEMOD_L0_system_time();

    /* for each line in fw_table */
    for (line = 0; line < nbLines; line++)
    {
		if (fw_table[line].firmware_size > 0)  /* don't download if length is 0 , e.g. dummy firmware */
		{
			/* send firmware_len bytes (up to 16) to Si2158B */
			return_code = DEMOD_L1_API_Patch_D(api, fw_table[line].firmware_addr, fw_table[line].firmware_size, fw_table[line].firmware_table);
			if (return_code != 0)
			{
			  	DBB_PRINT("DEMOD_L1_LoadFirmware_DRAM error 0x%02x patching line %d: %s\n", return_code, line, DEMOD_L1_API_Error_Text(return_code) );
				return ERROR_DEMOD_LOADING_FIRMWARE;
			}

		}

		if (line==0)
		{
			if (DEMOD_L0_system_time() - load_start_ms > 200)
			{
				DBB_PRINT ("DEMOD_LoadFirmware line 1 took too much time!\n");
			}
			//DBB_PRINT ("DEMOD_LoadFirmware line 1 took %4d ms\n", DEMOD_L0_system_time() - load_start_ms);
		}
    }

	 DBB_PRINT ("DEMOD_LoadFirmware DRAM took %4d ms\n", DEMOD_L0_system_time() - load_start_ms);
    return NO_DEMOD_ERROR;
}


/***********************************************************************************************************************
  DEMOD_L1_START_FIRMWARE function
  Use:        Patch information function
              Used to send a number of bytes to the LGDBB. Useful to download the firmware.
  Returns:    0 if no error
  Parameter:  error_code the error code.
  Porting:    Useful for application development for debug purposes.
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
UINT8 DEMOD_L1_API_StartFirmware(LX_DEMOD_L1_Context *api)
{
	UINT8 rdData=0;

	//DBB_PRINT(" %s starting....\n", __F__);

#ifdef FPGA_CPBOX
	UINT8 chip_id=0;

	if(api->i2c->chipVer >= L18F)
	{
		chip_id=0xb2;
	}
	else
	{
		chip_id=0x26;
	}

	api->i2c->slvAddr = chip_id;
	api->i2c->handle = (api->i2c->handle & 0xffffff00) + api->i2c->slvAddr;

#endif

	if(api->i2c->chipVer >= L18F)
	{
		UINT8 wrData[4] ={0,};
		api->i2c->inDirect = 0;

		if (api->i2c->chipVer >= M16P3)
		{
			DEMOD_L0_WordToByte(0xF0040000, wrData);
			
			if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(api->i2c, 0xF024, 1, wrData))
			{
				DEMOD_PRINT("[DEMOD_L1_API_StartFirmware] FAIL (%s:%d) DEMOD_L0_WriteCommandBytes !!!\n", __F__, __L__);
				return ERROR_DEMOD_WRITE;
			}

			api->i2c->inDirect = 1;
			//DEMOD_L0_WordToByte(0x00000000, wrData);
			//if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(api->i2c, 0x5404, 1, wrData)) return ERROR_DEMOD_STARTING_FIRMWARE;
			api->i2c->fwDone = 1;
		}

		DEMOD_L0_WordToByte(0x00000000, wrData);
		
		if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(api->i2c, 0xF004, 1, wrData)) return ERROR_DEMOD_STARTING_FIRMWARE;

	}
	else
	{
		UINT8 wrData = 0;
		if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(api->i2c, 0x7000, 1, &rdData)) return ERROR_DEMOD_STARTING_FIRMWARE;
		wrData = rdData | 0x80;
		if(NO_DEMOD_ERROR !=  DEMOD_L0_WriteCommandBytes(api->i2c, 0x7000, 1, &wrData)) return ERROR_DEMOD_STARTING_FIRMWARE;
	}

    	return NO_DEMOD_ERROR;
}


/***********************************************************************************************************************
  DEMOD_L1_INIT_FIRMWARE function
  Use:        Patch information function
              Used to send a number of bytes to the LGDBB. Useful to download the firmware.
  Returns:    0 if no error
  Parameter:  error_code the error code.
  Porting:    Useful for application development for debug purposes.
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
UINT8 DEMOD_L1_API_InitFirmware(LX_DEMOD_L1_Context *api)
{
	UINT8 wrData=0;
	//DBB_PRINT(" %s Initializing....\n", __F__);

#ifdef FPGA_CPBOX
	UINT8 chip_id=0;

	if(api->i2c->chipVer >= L18F)
	{
		chip_id=0xb2;
	}
	else
	{
		chip_id=0x26;
	}

	api->i2c->slvAddr = chip_id;
	api->i2c->handle = (api->i2c->handle & 0xffffff00) + api->i2c->slvAddr;

#endif

	if(api->i2c->chipVer >= L18F)
	{

	}
	else
	{
		wrData = 0x14;
		if(NO_DEMOD_ERROR !=  DEMOD_L0_WriteCommandBytes(api->i2c, 0x7000, 1, &wrData)) return ERROR_DEMOD_WRITE;
	}

    	return NO_DEMOD_ERROR;
}


/***********************************************************************************************************************
  DEMOD_L1_API_Error_Text function
  Use:        Error information function
              Used to retrieve a text based on an error code
  Returns:    the error text
  Parameter:  error_code the error code.
  Porting:    Useful for application development for debug purposes.
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
char*   DEMOD_L1_API_Error_Text(UINT8 error_code)
{

	switch (error_code)
	{

	        case NO_DEMOD_ERROR                     			: {return (char*)"No DEMOD error";}
	        case ERROR_DEMOD_ALLOCATING_CONTEXT   	: {return (char*)"Error while allocating DEMOD context";}
	        case ERROR_DEMOD_PARAMETER_OUT_OF_RANGE : {return (char*)"DEMOD parameter(s) out of range";}
	        case ERROR_DEMOD_SENDING_COMMAND        	: {return (char*)"Error while sending DEMOD command";}
	        case ERROR_DEMOD_CTS_TIMEOUT            		: {return (char*)"DEMOD CTS timeout";}
	        case ERROR_DEMOD_ERROR                    		: {return (char*)"DEMOD Error (status 'err' bit 1)";}
	        case ERROR_DEMOD_POLLING_CTS            		: {return (char*)"DEMOD Error while polling CTS";}
	        case ERROR_DEMOD_POLLING_RESPONSE       	: {return (char*)"DEMOD Error while polling response";}
	        case ERROR_DEMOD_LOADING_FIRMWARE       	: {return (char*)"DEMOD Error while loading firmware";}
	        case ERROR_DEMOD_LOADING_BOOTBLOCK      	: {return (char*)"DEMOD Error while loading bootblock";}
	        case ERROR_DEMOD_STARTING_FIRMWARE      	: {return (char*)"DEMOD Error while starting firmware";}
	        case ERROR_DEMOD_SW_RESET              		: {return (char*)"DEMOD Error during software reset";}
	        case ERROR_DEMOD_INCOMPATIBLE_PART      	: {return (char*)"DEMOD Error Incompatible part";}
	        case ERROR_DEMOD_UNKNOWN_COMMAND      	: {return (char*)"DEMOD Error unknown command";}
	        case ERROR_DEMOD_UNKNOWN_PROPERTY     	: {return (char*)"DEMOD Error unknown property";}
	        case ERROR_DEMOD_READ						: {return (char*)"DEMOD Error read";}
	        case ERROR_DEMOD_WRITE					: {return (char*)"DEMOD Error write";}
			default                                 				: {return (char*)"Unknown DEMOD error code";}
    }

}

/************************************************************************************************************************
  DEMOD_L1_API_StandardName function
  Use:        standard text retrieval function
              Used to retrieve the standard text used by the Si2169C
  Parameter:  standard, the value of the standard
************************************************************************************************************************/
char* DEMOD_L1_API_StandardName (UINT8 standard)
{
  switch (standard)
  {
	case DEMOD_DD_MODE_PROP_MODULATION_VSB    	: {return (char*)"VSB"		;}
	case DEMOD_DD_MODE_PROP_MODULATION_QAM    	: {return (char*)"QAM"		;}
	case DEMOD_DD_MODE_PROP_MODULATION_ISDBT    : {return (char*)"ISDB-T"	;}
	case DEMOD_DD_MODE_PROP_MODULATION_ATSC3   	: {return (char*)"ATSC3"	;}
	case DEMOD_DD_MODE_PROP_MODULATION_DVBT    	: {return (char*)"DVB-T"	;}
	case DEMOD_DD_MODE_PROP_MODULATION_DVBT2   	: {return (char*)"DVB-T2"	;}
	case DEMOD_DD_MODE_PROP_MODULATION_DVBC    	: {return (char*)"DVB-C"	;}
	case DEMOD_DD_MODE_PROP_MODULATION_DVBC2    : {return (char*)"DVB-C2"   ;}
	case DEMOD_DD_MODE_PROP_MODULATION_DVBS    	: {return (char*)"DVB-S"	;}
	case DEMOD_DD_MODE_PROP_MODULATION_DVBS2   	: {return (char*)"DVB-S2"	;}
	case DEMOD_DD_MODE_PROP_MODULATION_DTMB   	: {return (char*)"DTMB"		;}
	default                                     : {return (char*)"UNKNOWN"	;}
  }
}


/****************************************************************************************************************/
#ifndef LG3307_API

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_API_LoadFirmware_MEM.
 * Load firmware from DDR MEMORY.
 *
 * @param *api 		[IN] LX_DEMOD_L1_Context
 * @param fw_table[] 	[IN] LX_DEMOD_FIRMWARE_STRUCT
 * @param nbLines 	[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_API_LoadFirmware_MEM	(LX_DEMOD_L1_Context *api, UINT32 baseAddr)
{
	int load_start_ms;
	DBB_PRINT ("DEMOD_L1_API_LoadFirmware_MEM starting...(20190131)\n");
	load_start_ms = DEMOD_L0_system_time();

	if(api->i2c->chipVer >= L18F)
	{
	    UINT8 wrData[4]={0,};
	    UINT8 rdData[4]={0,};
	    UINT32 wrData32=0;

	#ifdef FPGA_CPBOX
		UINT8 chip_id=0x26;

		api->i2c->slvAddr = chip_id;
		api->i2c->handle = (api->i2c->handle & 0xffffff00) + api->i2c->slvAddr;

	#else

	#endif

		DEMOD_L0_WordToByte (baseAddr, wrData);
		//DBB_PRINT ("baseAddr : %x, %x, %x, %x, %x \n", baseAddr, wrData[3], wrData[2], wrData[1], wrData[0]);
		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(api->i2c, 0xF048, 4, wrData)) return ERROR_DEMOD_LOADING_FIRMWARE;

		//if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(api->i2c, 0xF048, 1, &rdData)) return ERROR_DEMOD_LOADING_FIRMWARE;
		//DBB_PRINT ("0xF048 : %x, %x, %x, %x \n", rdData[3], rdData[2], rdData[1], rdData[0]);

		if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(api->i2c, 0xF04C, 4, rdData)) return ERROR_DEMOD_LOADING_FIRMWARE;
		wrData32 = (rdData[3] << 24) | (rdData[2] << 16) | (rdData[1] << 8) | (rdData[0] | 0x01);
		DEMOD_L0_WordToByte (wrData32, wrData);
		//DBB_PRINT ("0xF04C : %x, %x, %x, %x, %x \n", wrData32, wrData[3], wrData[2], wrData[1], wrData[0]);
		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(api->i2c, 0xF04C, 4, wrData)) return ERROR_DEMOD_LOADING_FIRMWARE;

//		if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(api->i2c, 0xF04C, 1, rdData)) return ERROR_DEMOD_LOADING_FIRMWARE;
//		DBB_PRINT ("0xF04C : %x, %x, %x, %x \n", rdData[3], rdData[2], rdData[1], rdData[0]);

		while(1)
		{
			DEMOD_L0_ReadCommandBytes(api->i2c, 0xF014, 4, rdData);
			rdData[1] &= 0x01;

			if(rdData[1] == 0x01)
			{
//				printk("DEMOD FW download is Done 0x%x !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", rdData[1]);
				break;
			}
			else if (DEMOD_L0_system_time() - load_start_ms >= 50)
			{				
				if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(api->i2c, 0xF04C, 4, rdData)) return ERROR_DEMOD_LOADING_FIRMWARE;
				printk("DEMOD FW download is fail~~~0x%x!!!!!!!!!!!!!!!! by AXI timeout \n", rdData[0]);
				wrData32 = (rdData[3] << 24) | (rdData[2] << 16) | (rdData[1] << 8) | (rdData[0] & 0xfe);
				DEMOD_L0_WordToByte (wrData32, wrData);
				if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(api->i2c, 0xF04C, 4, wrData)) return ERROR_DEMOD_LOADING_FIRMWARE;
				
				return ERROR_DEMOD_LOADING_FIRMWARE;
			}
			DEMOD_L0_system_wait(5);
		}
		
		DEMOD_L0_system_wait(10); // change time 1 to 10 because of M19 TER/SAT change issue 

		//DEMOD_L0_ReadCommandBytes(api->i2c, 0xF014, 1, &rdData);
		//DBB_PRINT ("0xF014 : %x, %x, %x, %x \n", rdData[3], rdData[2], rdData[1], rdData[0]);

		if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(api->i2c, 0xF04C, 4, rdData)) return ERROR_DEMOD_LOADING_FIRMWARE;
		wrData32 = (rdData[3] << 24) | (rdData[2] << 16) | (rdData[1] << 8) | (rdData[0] & 0xfe);
		DEMOD_L0_WordToByte (wrData32, wrData);
		//DBB_PRINT ("0xF04C : %x, %x, %x, %x, %x \n", wrData32, wrData[3], wrData[2], wrData[1], wrData[0]);
		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(api->i2c, 0xF04C, 4, wrData)) return ERROR_DEMOD_LOADING_FIRMWARE;

	}
	else
	{
	    UINT8 wrData=0;
	    UINT8 rdData=0;

	#ifdef FPGA_CPBOX
		UINT8 chip_id=0x26;

		api->i2c->slvAddr = chip_id;
		api->i2c->handle = (api->i2c->handle & 0xffffff00) + api->i2c->slvAddr;

	#else

	#endif

		if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(api->i2c, 0x7000, 1, &rdData)) return ERROR_DEMOD_LOADING_FIRMWARE;

		if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(api->i2c, 0x7000, 1, &rdData)) return ERROR_DEMOD_LOADING_FIRMWARE;
		wrData = rdData & 0xef;
		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(api->i2c, 0x7000, 1, &wrData)) return ERROR_DEMOD_LOADING_FIRMWARE;


		wrData = (UINT8) (baseAddr >> 24) & 0xff;;
		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(api->i2c, 0x7001, 1, &wrData)) return ERROR_DEMOD_LOADING_FIRMWARE;

		wrData = (UINT8) (baseAddr >> 16) & 0xff;;
		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(api->i2c, 0x7002, 1, &wrData)) return ERROR_DEMOD_LOADING_FIRMWARE;

		wrData = (UINT8) (baseAddr >> 8) & 0xff;;
		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(api->i2c, 0x7003, 1, &wrData)) return ERROR_DEMOD_LOADING_FIRMWARE;

		wrData = (UINT8) baseAddr & 0xff;;
		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(api->i2c, 0x7004, 1, &wrData)) return ERROR_DEMOD_LOADING_FIRMWARE;


		if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(api->i2c, 0x7005, 1, &rdData)) return ERROR_DEMOD_LOADING_FIRMWARE;
		wrData = rdData | 0x40;
		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(api->i2c, 0x7005, 1, &wrData)) return ERROR_DEMOD_LOADING_FIRMWARE;

		while(1)
		{
			DEMOD_L0_ReadCommandBytes(api->i2c, 0x7080, 1, &rdData);
			rdData &= 0x40;

			if(rdData == 0x40)	break;
			else if (DEMOD_L0_system_time() - load_start_ms >= 500)
			{
				printk("DEMOD FW download is fail~~!!!!!!!!!!!!!!!! by AXI timeout \n");
				break;
			}
		}

		if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(api->i2c, 0x7005, 1, &rdData)) return ERROR_DEMOD_LOADING_FIRMWARE;
		wrData = rdData & 0xbf;
		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(api->i2c, 0x7005, 1, &wrData)) return ERROR_DEMOD_LOADING_FIRMWARE;

	}

	DBB_PRINT ("DEMOD_LoadFirmware took %4d ms\n", DEMOD_L0_system_time() - load_start_ms);

    return NO_DEMOD_ERROR;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_API_BaseAddr_AXI.
 * Set base address for AXI memory write.
 *
 * @param *api 		[IN] LX_DEMOD_L1_Context
 * @param fw_table[] 	[IN] LX_DEMOD_FIRMWARE_STRUCT
 * @param baseAddr 	[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_API_BaseAddr_AXI	(LX_DEMOD_L1_Context *api, UINT32 baseAddr)
{
    int res;

    DBB_PRINT ("DEMOD_Set BASE_ADDR_AXI\n");

#ifdef FPGA_CPBOX
	UINT8 chip_id=0x26;

	api->i2c->slvAddr = chip_id;
	api->i2c->handle = (api->i2c->handle & 0xffffff00) + api->i2c->slvAddr;

#else

#endif

	res = DEMOD_L1_SET_DD_ISDBT_BASEADDR_AXI(api, baseAddr);

	if (res != NO_DEMOD_ERROR)
	{
		DBB_PRINT("FAIL,  %s\n", DEMOD_L1_API_Error_Text(res));

	  	return ERROR_DEMOD_WRITE;
	}

    return NO_DEMOD_ERROR;
}



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_API_EMERGENCY_ALARM.
 * Get the emergency alarm flag.
 *
 * @param *api 		[IN] LX_DEMOD_L1_Context
 * @param fw_table[] 	[IN] LX_DEMOD_FIRMWARE_STRUCT
 * @param eAlarm	 	[IN] UINT8*
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_API_Emergency_Alarm	(LX_DEMOD_L1_Context *api, UINT8 *eAlarm)
{
    int res;

#ifdef FPGA_CPBOX
	UINT8 chip_id=0x26;

	api->i2c->slvAddr = chip_id;
	api->i2c->handle = (api->i2c->handle & 0xffffff00) + api->i2c->slvAddr;

#else

#endif

	res = DEMOD_L1_GET_DD_Reg(api,  0x00, 0xde, 1);

	*eAlarm = (api->rsp->dd_get_reg.mData[0] >> 5) & 0x1;

	if (res != NO_DEMOD_ERROR)
	{
		DBB_PRINT("FAIL,  %s\n", DEMOD_L1_API_Error_Text(res));

	  	return ERROR_DEMOD_WRITE;
	}

    return NO_DEMOD_ERROR;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_API_DVBT2_BaseAddr_AXI.
 * Set base address for AXI memory write.
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @param fw_table[] 	[IN] LX_DEMOD_FIRMWARE_STRUCT
 * @param baseAddr1		[IN] UINT32
 * @param baseAddr2		[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_API_DVBT2_BaseAddr_AXI	(LX_DEMOD_L1_Context *api, UINT32 baseAddr1, UINT32 baseAddr2)
{
    int res;

    DBB_PRINT ("DEMOD_Set BASE_ADDR_AXI\n");

#ifdef FPGA_CPBOX
	UINT8 chip_id=0x26;

	api->i2c->slvAddr = chip_id;
	api->i2c->handle = (api->i2c->handle & 0xffffff00) + api->i2c->slvAddr;

#else

#endif

	res = DEMOD_L1_SET_DD_DVBT2_BASEADDR_AXI(api, baseAddr1, baseAddr2);

	if (res != NO_DEMOD_ERROR)
	{
		DBB_PRINT("FAIL,  %s\n", DEMOD_L1_API_Error_Text(res));

	  	return ERROR_DEMOD_WRITE;
	}

    return NO_DEMOD_ERROR;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_API_DVB_BaseAddr_AXI.
 * Set base address for AXI memory write.
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @param fw_table[] 	[IN] LX_DEMOD_FIRMWARE_STRUCT
 * @param baseAddr1		[IN] UINT32
 * @param baseAddr2		[IN] UINT32
 * @param baseAddr3		[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_API_DVB_BaseAddr_AXI	(LX_DEMOD_L1_Context *api, UINT32 baseAddr1, UINT32 baseAddr2, UINT32 baseAddr3)
{
    int res;

    DBB_PRINT ("DEMOD_Set BASE_ADDR_AXI\n");

#ifdef FPGA_CPBOX
	UINT8 chip_id=0x26;

	api->i2c->slvAddr = chip_id;
	api->i2c->handle = (api->i2c->handle & 0xffffff00) + api->i2c->slvAddr;

#else

#endif

	res = DEMOD_L1_SET_DD_DVB_BASEADDR_AXI(api, baseAddr1, baseAddr2, baseAddr3);

	if (res != NO_DEMOD_ERROR)
	{
		DBB_PRINT("FAIL,  %s\n", DEMOD_L1_API_Error_Text(res));

	  	return ERROR_DEMOD_WRITE;
	}

    return NO_DEMOD_ERROR;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_API_DTMB_BaseAddr_AXI.
 * Set base address for AXI memory write.
 *
 * @param *api 		[IN] LX_DEMOD_L1_Context
 * @param fw_table[] 	[IN] LX_DEMOD_FIRMWARE_STRUCT
 * @param baseAddr 	[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_API_DTMB_BaseAddr_AXI	(LX_DEMOD_L1_Context *api, UINT32 baseAddr)
{
    int res;

    DBB_PRINT ("DEMOD_Set DTMB_BASE_ADDR_AXI\n");

#ifdef FPGA_CPBOX
	UINT8 chip_id=0x26;

	api->i2c->slvAddr = chip_id;
	api->i2c->handle = (api->i2c->handle & 0xffffff00) + api->i2c->slvAddr;

#else

#endif

	res = DEMOD_L1_SET_DD_DTMB_BASEADDR_AXI(api, baseAddr);

	if (res != NO_DEMOD_ERROR)
	{
		DBB_PRINT("FAIL,  %s\n", DEMOD_L1_API_Error_Text(res));

	  	return ERROR_DEMOD_WRITE;
	}

    return NO_DEMOD_ERROR;
}

#endif






