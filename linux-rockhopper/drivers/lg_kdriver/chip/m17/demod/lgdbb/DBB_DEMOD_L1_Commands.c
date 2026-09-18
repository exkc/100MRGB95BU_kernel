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
**  Name:DBB_DEMOD_L1_Commands.c
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
#ifdef __KERNEL__
#include <asm/div64.h> //do_div
#else
#include <math.h>
#endif

#include "DBB_DEMOD_typedefs.h"
#include "DBB_DEMOD_L1_API.h"
#include "DBB_DEMOD_L1_Commands_Prototypes.h"
#include "DBB_DEMOD_L1_Properties_Functions.h"

#include <asm/io.h>					/**< For ioremap_nocache */

#if 1
static volatile unsigned int *gMapped_address;
#define DEMOD_APB_REG_WR(address,data)   \
	gMapped_address=(volatile UINT32 *)ioremap(address, sizeof(UINT32));\
	do{\
		if(gMapped_address == NULL) break;\
		*gMapped_address = data;\
		iounmap((void *)gMapped_address);\
	}while(0);\

#define DEMOD_APB_REG_RD(address,data)   \
	gMapped_address = (volatile UINT32 *)ioremap(address, sizeof(UINT32));\
	do{\
		if(gMapped_address == NULL) {data = 0; break;}\
		data = (unsigned int)*gMapped_address;\
		iounmap((void *)gMapped_address);\
	}while(0);\

#endif


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_CurrentRspStatus.
 * gets MCU firmware response after sending commands
 *
 * @param *front_end 	[IN] LX_DEMOD_L2_Context
 * @param ptDataBuffer 	[OUT] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8 DEMOD_L1_Process (LX_DEMOD_L1_Context *api, UINT8 cmdByte, UINT8 *cmdByteBuffer, UINT8 rspByte, UINT8 *rspByteBuffer)
{
	UINT8 err=0, command=0;
	UINT8 wrData[4]={0,};
//	UINT32 pucWordData = 0;

//	DEMOD_L0_system_wait(50);
	err = DEMOD_L0_WriteCommandBytes(api->i2c, api->i2c->cmdAddr, cmdByte, cmdByteBuffer);
	command = cmdByteBuffer[0];
	//DBB_PRINT("cmdAddr %x, cmdByte %d, command %x\n", api->i2c->cmdAddr, cmdByte, command);
	//DBB_PRINT("\n [DEMOD_L1_Process] command = 0x%x\n", command);

	switch(command)
	{
	case DEMOD_DD_POWER_SAVE_CMD:
		{
			if(api->i2c->chipVer >= L18F)
			{
				if(cmdByteBuffer[1])	//powersave
				{
					if(err == NO_DEMOD_ERROR)
						err = DEMOD_L1_SetInt(api);
#ifndef __EVAL_GUI__
					DEMOD_L0_system_wait(1);
#endif
					if(err == NO_DEMOD_ERROR)
						err = DEMOD_L1_GetCts(api, command);

					DEMOD_L0_WordToByte (0x00000001, wrData);

					if(err == NO_DEMOD_ERROR)
						err = DEMOD_L0_WriteCommandBytes(api->i2c, 0xF004, 4, wrData);
				}
				else
				{
					DEMOD_L0_WordToByte (0x00000000, wrData);

					if(err == NO_DEMOD_ERROR)
						err = DEMOD_L0_WriteCommandBytes(api->i2c, 0xF004, 4, wrData);

					if(err == NO_DEMOD_ERROR)
						err = DEMOD_L1_SetInt(api);
#ifndef __EVAL_GUI__
					DEMOD_L0_system_wait(1);
#endif
					if(err == NO_DEMOD_ERROR)
						err = DEMOD_L1_GetCts(api, command);
				}
			}
			else
			{
				if(err == NO_DEMOD_ERROR)
					err = DEMOD_L1_SetInt(api);
#ifndef __EVAL_GUI__
				DEMOD_L0_system_wait(1);
#endif
				if(err == NO_DEMOD_ERROR)
					err = DEMOD_L1_GetCts(api, command);
			}
		}
		break;

	case DEMOD_DD_SET_REG_CMD:
	case DEMOD_DD_SET_PROP_CMD:
	case DEMOD_DD_SOFT_RESET_CMD:
	case DEMOD_DD_RESTART_CMD:
	case DEMOD_DD_SET_TUNE_CMD:
	case DEMOD_DD_ATSC3_PLP_SELECT_CMD:
	case DEMOD_DD_DVBT2_PLP_SELECT_CMD:
	case DEMOD_DD_DVBC2_STARTFREQUENCY_CMD:
	case DEMOD_DD_DVBC2_PLP_SELECT_CMD:
	case DEMOD_DD_DISEQC_SEND_CMD:
	case DEMOD_DD_DVBS_OPERATING_MODE_CMD:
	case DEMOD_DD_SELFRST_CMD:
	case DEMOD_DD_BLIND_INIT_CMD:
	case DEMOD_DD_BLIND_END_CMD:

		{
			if(err == NO_DEMOD_ERROR)
				err = DEMOD_L1_SetInt(api);
#ifndef __EVAL_GUI__
			DEMOD_L0_system_wait(1);
#endif
			//DBB_PRINT   ("5 'reset' took %3d ms\n", DEMOD_L0_system_time() - api->start_time);
			if(err == NO_DEMOD_ERROR)
				err = DEMOD_L1_GetCts(api, command);
		}
		break;

	case DEMOD_DD_GET_PROP_CMD:
	case DEMOD_DD_GET_REG_CMD:
	case DEMOD_DD_VSB_STATUS_CMD:
	case DEMOD_DD_QAM_STATUS_CMD:
	case DEMOD_DD_GET_PART_INFO_CMD:
	case DEMOD_DD_STATUS_CMD:
	case DEMOD_DD_ATSC3_STATUS_CMD:
	case DEMOD_DD_ATSC3_PLP_ID_CMD:
	case DEMOD_DD_ATSC3_PLP_INFO_CMD:
	case DEMOD_DD_ISDBT_BASEADDR_AXI_CMD:
	case DEMOD_DD_DVBC_SRD_CMD:
	case DEMOD_DD_DVBT2_STATUS_CMD:
	case DEMOD_DD_GET_DVBT2_PLP_ID_CMD:
	case DEMOD_DD_DVBT_STATUS_CMD:
	case DEMOD_DD_ISDBT_STATUS_CMD:
	case DEMOD_DD_ISDBT_TMCC_INFO_CMD:
	case DEMOD_DD_DVBC_STATUS_CMD:
	case DEMOD_DD_DVBC2_STATUS_CMD:
	case DEMOD_DD_DVBS_STATUS_CMD:
	case DEMOD_DD_DVBS2_STATUS_CMD:
	case DEMOD_DD_LOCKTIME_CMD:
	case DEMOD_DD_GET_DD_SIGSRCH_NUM_CMD:
	case DEMOD_DD_GET_DD_SIGSRCH_INFO_CMD:
	case DEMOD_DD_BLIND_STATUS_CMD:
	case DEMOD_DD_BLIND_FOUNDINFO_CMD:
	case DEMOD_DD_DVBT2_BASEADDR_AXI_CMD:		
	case DEMOD_DD_DVB_BASEADDR_AXI_CMD:
	case DEMOD_DD_DTMB_STATUS_CMD:
	case DEMOD_DD_DTMB_BASEADDR_AXI_CMD:

		{
			if(err == NO_DEMOD_ERROR)
				err = DEMOD_L1_SetInt(api);
#ifndef __EVAL_GUI__
			DEMOD_L0_system_wait(1);
#endif
			if(err == NO_DEMOD_ERROR)
				err = DEMOD_L1_GetCts(api, command);

			if(err == NO_DEMOD_ERROR)
			{
				err = DEMOD_L1_PollForRsp(api, rspByte, rspByteBuffer);
				//DBB_PRINT("\n ########## DEMOD_L1_PollForRsp rspByteBuffer = %x ########## \n\n", *rspByteBuffer);
			}
		}
		break;

	default:
		break;
	}

	return  err;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_CurrentRspStatus.
 * gets MCU firmware response after sending commands
 *
 * @param *front_end 	[IN] LX_DEMOD_L2_Context
 * @param ptDataBuffer 	[OUT] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8 DEMOD_L1_CurrentRspStatus (LX_DEMOD_L1_Context *api, UINT8 ptDataBuffer)
{
	api->status->cts     = ptDataBuffer;
	return  NO_DEMOD_ERROR;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GetCts.
 * gets MCU firmware CTS(Clear To Send) response  after sending commands
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @param cmdCode 		[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8 DEMOD_L1_GetCts(LX_DEMOD_L1_Context *api, UINT8 cmdCode)
{
	UINT32 start_time=0;
	UINT8 rspByteBuffer[4]={0,};
	UINT8 dataByteBuffer[4] = {0,};
	UINT8 result = NO_DEMOD_ERROR;
	UINT32	debugValues;
		
	start_time = DEMOD_L0_system_time();
	while ((DEMOD_L0_system_time() - start_time) < 1000)
	{ /* wait a maximum of 1000ms */
		if(api->i2c->chipVer >= L18F)
		{
			if (api->i2c->chipVer >= M16P3)
			{
				api->i2c->inDirect = 1;
			}
			else
			{
				api->i2c->inDirect = 0;
			}
			if(NO_DEMOD_ERROR == DEMOD_L0_ReadCommandBytes(api->i2c, 0xF0D0, 4, rspByteBuffer))
			{
				if(rspByteBuffer[0] == cmdCode)
				{
					api->i2c->inDirect = 0;
		
					DEMOD_L0_WordToByte(0x00000000, dataByteBuffer);
					if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(api->i2c, 0xF0D0, 4, dataByteBuffer))
					{
						return ERROR_DEMOD_WRITE;
					}		
					return result;
				}
			}
			else		
			{
				return ERROR_DEMOD_POLLING_RESPONSE;
			}
		}
		else
		{
			if(NO_DEMOD_ERROR == DEMOD_L0_ReadCommandBytes(api->i2c, 0x7090, 1, rspByteBuffer))
			{
				if(rspByteBuffer[0] == cmdCode)
				{
					return DEMOD_L1_CurrentRspStatus(api, rspByteBuffer[0]);
				}
			}
			else		
			{
				return ERROR_DEMOD_POLLING_RESPONSE;
			}
		}
		DEMOD_L0_system_wait(1);
	}

	if(api->i2c->chipVer >= L18F)
	{
		if(api->i2c->chipVer < M16P3)
		{
			DEMOD_APB_REG_WR(0xC600F010, 0x01);
			DEMOD_APB_REG_RD(0xC600F0D8, debugValues);
			DEMOD_PRINT_ALWAYS("Debug Value 0xC600F0D8 = 0x%x\n ",debugValues);
			DEMOD_APB_REG_RD(0xC600F01C, debugValues);
			DEMOD_PRINT_ALWAYS("Debug Value 0xC600F01C = 0x%x\n ",debugValues);
			DEMOD_APB_REG_WR(0xC600F010, 0x00);
		}
	}	
	return ERROR_DEMOD_CTS_TIMEOUT;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_PollForRsp.
 * gets required informations from MCU Firmware
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @param nbBytes 		[IN] UINT8
 * @param *pByteBuffer 	[OUT] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8 DEMOD_L1_PollForRsp(LX_DEMOD_L1_Context *api, UINT8 nbBytes, UINT8 *pByteBuffer)
{
	if(api->i2c->chipVer >= L18F)
	{
		UINT8 nByte=0, i=0;
		UINT8 extend[4]={0, 3, 2, 1};

		if (api->i2c->chipVer >= M16P3)
		{
			api->i2c->inDirect = 1;
		}
		else
		{
			api->i2c->inDirect = 0;
		}
		nByte = nbBytes + extend[nbBytes%4];

		for(i=0;i<nByte/4;i++)
		{
#ifndef __EVAL_GUI__
			DEMOD_L0_system_wait(1);
#endif
			if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(api->i2c, (api->i2c->rspAddr)+4*i, 4, pByteBuffer+4*i))
			{
				return ERROR_DEMOD_POLLING_RESPONSE;
			}
		}
	}
	else
	{
		if (NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(api->i2c, api->i2c->rspAddr, nbBytes, pByteBuffer))
		{
			return ERROR_DEMOD_POLLING_RESPONSE;
		}
	}
  return NO_DEMOD_ERROR;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_SetInt.
 * sends interruption signal to MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8 DEMOD_L1_SetInt(LX_DEMOD_L1_Context *api)
{
	if(api->i2c->chipVer >= L18F)
	{
		UINT8 dataByteBuffer[4]={0, };
		if (api->i2c->chipVer >= M16P3)
		{
			api->i2c->inDirect = 1;
		}
		else
		{
			api->i2c->inDirect = 0;
		}

		DEMOD_L0_WordToByte (0x00000001, dataByteBuffer);
		if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(api->i2c, 0xF044, 4, dataByteBuffer))
		{
			return ERROR_DEMOD_WRITE;
		}

		DEMOD_L0_WordToByte (0x00000001, dataByteBuffer);
		if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(api->i2c, 0xF040, 4, dataByteBuffer))
		{
			return ERROR_DEMOD_WRITE;
		}
	}
	else
	{
		UINT8 dataByteBuffer[1]={0};

		if (NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(api->i2c, 0x7000, 1, dataByteBuffer))
		{
			return ERROR_DEMOD_READ;
		}

		dataByteBuffer[0] |= 0x08;

		if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(api->i2c, 0x7000, 1, dataByteBuffer) )
		{
		 	return ERROR_DEMOD_WRITE;
		}
	}

	return NO_DEMOD_ERROR;
}


#ifdef    DEMOD_DD_SET_REG_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_SET_DD_Reg.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @param addressMsb 	[IN] UINT8
 * @param addressLsb 	[IN] UINT8
 * @param length 		[IN] UINT8
 * @param data 			[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8 DEMOD_L1_SET_DD_Reg(LX_DEMOD_L1_Context *api, UINT8 addressMsb, UINT8 addressLsb, UINT8 length, UINT32 data)
{

	UINT8 err=0;
	UINT8 i=0;
	UINT8 cmdByteBuffer[128]={0,};
	UINT8 rspByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	if(api->i2c->chipVer >= L18F)
	{
		cmdByte = 4+length;
		cmdByteBuffer[0] = DEMOD_DD_SET_REG_CMD;
		cmdByteBuffer[1] = ( ( addressMsb & DEMOD_DD_SET_REG_CMD_ADDRMSB_MASK ) << DEMOD_DD_SET_REG_CMD_ADDRMSB_LSB);
		cmdByteBuffer[2] = ( ( addressLsb & DEMOD_DD_SET_REG_CMD_ADDRLSB_MASK ) << DEMOD_DD_SET_REG_CMD_ADDRLSB_LSB);
		cmdByteBuffer[3] = ( ( length & DEMOD_DD_SET_REG_CMD_LENGTH_MASK ) << DEMOD_DD_SET_REG_CMD_LENGTH_LSB);
	}
	else
	{
		cmdByte = 5+length;
		cmdByteBuffer[0] = DEMOD_DD_SET_REG_CMD;
		cmdByteBuffer[1] = 0;
		cmdByteBuffer[2] = ( ( addressMsb & DEMOD_DD_SET_REG_CMD_ADDRMSB_MASK ) << DEMOD_DD_SET_REG_CMD_ADDRMSB_LSB);
		cmdByteBuffer[3] = ( ( addressLsb & DEMOD_DD_SET_REG_CMD_ADDRLSB_MASK ) << DEMOD_DD_SET_REG_CMD_ADDRLSB_LSB);
		cmdByteBuffer[4] = ( ( length & DEMOD_DD_SET_REG_CMD_LENGTH_MASK ) << DEMOD_DD_SET_REG_CMD_LENGTH_LSB);
	}

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_SET_DD_Reg ########## \n\n");
#endif

	for (i=0;i<length;i++)
	{
		if(api->i2c->chipVer >= L18F)
		{
			//cmdByteBuffer[4+i] = *(wrData+i);
			cmdByteBuffer[4+i] = (UINT8)((data >> (i * 8 )) & 0xff) ;
		}
		else
		{
			cmdByteBuffer[5+i] = (UINT8)((data >> (i * 8 )) & 0xff) ;
		}

		//DBB_PRINT("cmdByteBuffer[%d] = 0x%x\n", 5+i, cmdByteBuffer[5+i]);
	}

	err = DEMOD_L1_Process (api, cmdByte , cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /*DEMOD_DD_SET_REG_CMD */


#ifdef DEMOD_DD_SET_PROP_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_SET_DD_Prop.
 * sets demoduator properties
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @param prop 			[IN] UINT16
 * @param data 			[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8 DEMOD_L1_SET_DD_Prop(LX_DEMOD_L1_Context *api, UINT16 prop, UINT32 data)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[8]={0,};
	UINT8 rspByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	if(api->i2c->chipVer >= L18F)
	{
		cmdByte = 8;
		cmdByteBuffer[0] = DEMOD_DD_SET_PROP_CMD;
		cmdByteBuffer[1] = (UINT8) ((( prop     & DEMOD_DD_SET_PROP_CMD_PROP_MASK     ) << DEMOD_DD_SET_PROP_CMD_PROP_LSB    )>>8);
		cmdByteBuffer[2] = (UINT8) ( ( prop     & DEMOD_DD_SET_PROP_CMD_PROP_MASK     ) << DEMOD_DD_SET_PROP_CMD_PROP_LSB    );
		cmdByteBuffer[3] = 0;
		cmdByteBuffer[4] = (UINT8) ((( data     & DEMOD_DD_SET_PROP_CMD_DATA_MASK     ) << DEMOD_DD_SET_PROP_CMD_DATA_LSB    )>>0);
		cmdByteBuffer[5] = (UINT8) ((( data     & DEMOD_DD_SET_PROP_CMD_DATA_MASK     ) << DEMOD_DD_SET_PROP_CMD_DATA_LSB    )>>8);
		cmdByteBuffer[6] = (UINT8) ((( data     & DEMOD_DD_SET_PROP_CMD_DATA_MASK     ) << DEMOD_DD_SET_PROP_CMD_DATA_LSB    )>>16);
		cmdByteBuffer[7] = (UINT8) ((( data     & DEMOD_DD_SET_PROP_CMD_DATA_MASK     ) << DEMOD_DD_SET_PROP_CMD_DATA_LSB    )>>24);
	}
	else
	{
		cmdByte = 7;
		cmdByteBuffer[0] = DEMOD_DD_SET_PROP_CMD;
		cmdByteBuffer[1] = (UINT8) ((( prop     & DEMOD_DD_SET_PROP_CMD_PROP_MASK     ) << DEMOD_DD_SET_PROP_CMD_PROP_LSB    )>>8);
		cmdByteBuffer[2] = (UINT8) ( ( prop     & DEMOD_DD_SET_PROP_CMD_PROP_MASK     ) << DEMOD_DD_SET_PROP_CMD_PROP_LSB    );
		cmdByteBuffer[3] = (UINT8) ((( data     & DEMOD_DD_SET_PROP_CMD_DATA_MASK     ) << DEMOD_DD_SET_PROP_CMD_DATA_LSB    )>>24);
		cmdByteBuffer[4] = (UINT8) ((( data     & DEMOD_DD_SET_PROP_CMD_DATA_MASK     ) << DEMOD_DD_SET_PROP_CMD_DATA_LSB    )>>16);
		cmdByteBuffer[5] = (UINT8) ((( data     & DEMOD_DD_SET_PROP_CMD_DATA_MASK     ) << DEMOD_DD_SET_PROP_CMD_DATA_LSB    )>>8);
		cmdByteBuffer[6] = (UINT8) ( ( data     & DEMOD_DD_SET_PROP_CMD_DATA_MASK     ) << DEMOD_DD_SET_PROP_CMD_DATA_LSB    );
	}

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_DD_SET_PROP_CMD ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_SET_PROP_CMD */


#ifdef DEMOD_DD_SET_REPEAT_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_SET_DD_Repeat.
 * Tuner i2c bus connection
 * Used to allow communication with the tuners
 *
 * @param *i2c 			[IN] LX_DEMOD_L0_Context
 * @param rptEn 		[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8 DEMOD_L1_SET_DD_Repeat(LX_DEMOD_L0_Context *i2c, UINT8 rptEn)
{

	UINT8 wrData;
	UINT8 err;
	LX_DEMOD_L0_Context repeatI2c;

	DEMOD_L0_LockDevice();

	repeatI2c.slvAddr=0xE0;
	repeatI2c.indexSize=2;
	repeatI2c.handle=(i2c->handle & 0xffffff00) + repeatI2c.slvAddr;

	if(rptEn == 1)
	{
		wrData=0x0;
		err = DEMOD_L0_WriteBytes(&repeatI2c, 0x7000, 1, &wrData);
	}
	else
	{
		wrData=0x3;
		err = DEMOD_L0_WriteBytes(&repeatI2c, 0x7000, 1, &wrData);
	}

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_SET_REPEAT_CMD */


#ifdef DEMOD_DD_SOFT_RESET_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_SET_DD_SoftRst.
 * resets the demodulator by software
 * Used to allow communication with the tuners
 *
 * @param *i2c 				[IN] LX_DEMOD_L1_Context
 * @param softrstb 			[IN] UINT8
 * @param softrstsyncb 		[IN] UINT8
 * @param softrsteq1b 		[IN] UINT8
 * @param softrsteq2b 		[IN] UINT8
 * @param softrstdiseqcb 	[IN] UINT8
 * @param softrstfecb 		[IN] UINT8
 * @param softrsttpifb 		[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_SET_DD_SoftRst(LX_DEMOD_L1_Context *api, UINT8 softrstb, UINT8 softrstsyncb, UINT8 softrsteq1b, UINT8 softrsteq2b, UINT8 softrstdiseqcb, UINT8 softrstfecb, UINT8 softrsttpifb)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	cmdByte=2;
	cmdByteBuffer[0] = DEMOD_DD_SOFT_RESET_CMD;
   	cmdByteBuffer[1] = (UINT8) (	( softrstb & DEMOD_DD_SOFT_RESET_CMD_SOFTRSTB_MASK ) << DEMOD_DD_SOFT_RESET_CMD_SOFTRSTB_LSB |
					                                ( softrstsyncb & DEMOD_DD_SOFT_RESET_CMD_SOFTRSTSYNCB_MASK ) << DEMOD_DD_SOFT_RESET_CMD_SOFTRSTSYNCB_LSB |
					                                ( softrsteq1b & DEMOD_DD_SOFT_RESET_CMD_SOFTRSTEQ1B_MASK ) << DEMOD_DD_SOFT_RESET_CMD_SOFTRSTEQ1B_LSB |
					                                ( softrsteq2b & DEMOD_DD_SOFT_RESET_CMD_SOFTRSTEQ2B_MASK ) << DEMOD_DD_SOFT_RESET_CMD_SOFTRSTEQ2B_LSB |
					                                ( softrstdiseqcb & DEMOD_DD_SOFT_RESET_CMD_SOFTRSTDISEQCB_MASK ) << DEMOD_DD_SOFT_RESET_CMD_SOFTRSTDISEQCB_LSB |
					                                ( softrstfecb & DEMOD_DD_SOFT_RESET_CMD_SOFTRSTFECB_MASK ) << DEMOD_DD_SOFT_RESET_CMD_SOFTRSTFECB_LSB |
					                                ( softrsttpifb & DEMOD_DD_SOFT_RESET_CMD_SOFTRSTTPIFB_MASK ) << DEMOD_DD_SOFT_RESET_CMD_SOFTRSTTPIFB_LSB );

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_SET_DD_SOFT_RESET ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_SOFT_RESET_CMD */


#ifdef DEMOD_DD_POWER_SAVE_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_SET_DD_Power_Save.
 * power off the demod IP for power save
 *
 * @param *i2c 			[IN] LX_DEMOD_L1_Context
 * @param power_save 	[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_SET_DD_Power_Save(LX_DEMOD_L1_Context *api, UINT8 power_save)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	cmdByte=2;
	cmdByteBuffer[0] = DEMOD_DD_POWER_SAVE_CMD;
	cmdByteBuffer[1] = power_save;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_SET_DD_Power_Save ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_POWER_SAVE_CMD */


#ifdef DEMOD_DD_RESTART_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_SET_DD_Restart.
 * restarts
 *
 * @param *i2c 			[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_SET_DD_Restart(LX_DEMOD_L1_Context *api)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	cmdByte=1;
	cmdByteBuffer[0] = DEMOD_DD_RESTART_CMD;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_SET_DD_Restart ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_RESTART_CMD */


#ifdef DEMOD_DD_GET_REG_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_Reg.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @param addressMsb 	[IN] UINT8
 * @param addressLsb 	[IN] UINT8
 * @param length 		[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8 DEMOD_L1_GET_DD_Reg(LX_DEMOD_L1_Context *api,  UINT8 addressMsb, UINT8 addressLsb, UINT8 length)
{

	UINT8 err=0, readCount=0;
	UINT8 cmdByteBuffer[8]={0,};
	UINT8 rspByteBuffer[64]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	if(api->i2c->chipVer >= L18F)
	{
		cmdByte = 4;
		cmdByteBuffer[0] = DEMOD_DD_GET_REG_CMD;
		cmdByteBuffer[1] = ( ( addressMsb & DEMOD_DD_GET_REG_CMD_ADDRMSB_MASK ) << DEMOD_DD_GET_REG_CMD_ADDRMSB_LSB);
		cmdByteBuffer[2] = ( ( addressLsb & DEMOD_DD_GET_REG_CMD_ADDRLSB_MASK ) << DEMOD_DD_GET_REG_CMD_ADDRLSB_LSB);
		cmdByteBuffer[3] = ( ( length & DEMOD_DD_GET_REG_CMD_LENGTH_MASK ) << DEMOD_DD_GET_REG_CMD_LENGTH_LSB);
	}
	else
	{
		cmdByte = 5;
		cmdByteBuffer[0] = DEMOD_DD_GET_REG_CMD;
		cmdByteBuffer[1] = 0;
		cmdByteBuffer[2] = ( ( addressMsb & DEMOD_DD_GET_REG_CMD_ADDRMSB_MASK ) << DEMOD_DD_GET_REG_CMD_ADDRMSB_LSB);
		cmdByteBuffer[3] = ( ( addressLsb & DEMOD_DD_GET_REG_CMD_ADDRLSB_MASK ) << DEMOD_DD_GET_REG_CMD_ADDRLSB_LSB);
		cmdByteBuffer[4] = ( ( length & DEMOD_DD_GET_REG_CMD_LENGTH_MASK ) << DEMOD_DD_GET_REG_CMD_LENGTH_LSB);
	}
	rspByte = length;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_Reg ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	for(readCount=0;readCount <length; readCount++ )
	{
		api->rsp->dd_get_reg.mData[readCount] = rspByteBuffer[readCount];
	}

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_GET_REG_CMD */

UINT8 DEMOD_L1_GET_DD_Reg_Map(LX_DEMOD_L1_Context *api,  UINT8 addressMsb, UINT8 addressLsb, UINT8 length, UINT8* rspByteBuffer)
{
	UINT8 err=0;
	UINT8 cmdByteBuffer[8]={0,};
	//UINT8 rspByteBuffer[64]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;
	
	DEMOD_L0_LockDevice();

	if(api->i2c->chipVer >= L18F)
	{
		cmdByte = 4;
		cmdByteBuffer[0] = DEMOD_DD_GET_REG_CMD;
		cmdByteBuffer[1] = ( ( addressMsb & DEMOD_DD_GET_REG_CMD_ADDRMSB_MASK ) << DEMOD_DD_GET_REG_CMD_ADDRMSB_LSB);
		cmdByteBuffer[2] = ( ( addressLsb & DEMOD_DD_GET_REG_CMD_ADDRLSB_MASK ) << DEMOD_DD_GET_REG_CMD_ADDRLSB_LSB);
		cmdByteBuffer[3] = ( ( length & DEMOD_DD_GET_REG_CMD_LENGTH_MASK ) << DEMOD_DD_GET_REG_CMD_LENGTH_LSB);
	}
	else
	{
		cmdByte = 5;
		cmdByteBuffer[0] = DEMOD_DD_GET_REG_CMD;
		cmdByteBuffer[1] = 0;
		cmdByteBuffer[2] = ( ( addressMsb & DEMOD_DD_GET_REG_CMD_ADDRMSB_MASK ) << DEMOD_DD_GET_REG_CMD_ADDRMSB_LSB);
		cmdByteBuffer[3] = ( ( addressLsb & DEMOD_DD_GET_REG_CMD_ADDRLSB_MASK ) << DEMOD_DD_GET_REG_CMD_ADDRLSB_LSB);
		cmdByteBuffer[4] = ( ( length & DEMOD_DD_GET_REG_CMD_LENGTH_MASK ) << DEMOD_DD_GET_REG_CMD_LENGTH_LSB);
	}
	rspByte = length;

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice();
	return err;
}

#ifdef DEMOD_DD_GET_PROP_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_Prop.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @param prop		 	[IN] UINT16
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8 DEMOD_L1_GET_DD_Prop(LX_DEMOD_L1_Context *api, UINT16 prop)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;
	
	DEMOD_L0_LockDevice();

	rspByte=4;
	cmdByte=3;
	cmdByteBuffer[0] = DEMOD_DD_GET_PROP_CMD;
	cmdByteBuffer[1] = (UINT8) ((( prop     & DEMOD_DD_GET_PROP_CMD_PROP_MASK     ) << DEMOD_DD_GET_PROP_CMD_PROP_LSB    ) >> 8);
	cmdByteBuffer[2] = (UINT8) ( ( prop     & DEMOD_DD_GET_PROP_CMD_PROP_MASK     ) << DEMOD_DD_GET_PROP_CMD_PROP_LSB    );

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_Prop ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);
	api->rsp->get_property.data =  (((rspByteBuffer[3] <<24 | rspByteBuffer[2] <<16 | rspByteBuffer[1] <<8 | (rspByteBuffer[0])) >> DEMOD_DD_GET_PROP_CMD_PROP_LSB) & DEMOD_DD_GET_PROP_CMD_PROP_MASK);

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_GET_PROP_CMD */


#ifdef DEMOD_DD_VSB_STATUS_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_VSB_Status.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_GET_DD_VSB_Status(LX_DEMOD_L1_Context *api)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[20]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;
	UINT8 rdData1=0, rdData2=0, rdData3=0, rdData4=0, rdData5=0, rdData6=0;

	DEMOD_L0_LockDevice();

	rspByte=17;
	cmdByte=1;
	cmdByteBuffer[0] =	DEMOD_DD_VSB_STATUS_CMD;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_VSB_Status ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	api->rsp->vsb_status.if_agc 	= (( ( (rspByteBuffer[1]  ) |(rspByteBuffer[0]	<< 8 )) >> DEMOD_DD_VSB_STATUS_RESPONSE_IF_AGC_LSB		) & DEMOD_DD_VSB_STATUS_RESPONSE_IF_AGC_MASK);
	api->rsp->vsb_status.mse_info		= (( ( (rspByteBuffer[3]  ) | (rspByteBuffer[2]  << 8 )) >> DEMOD_DD_VSB_STATUS_RESPONSE_MSE_INFO_LSB  ) & DEMOD_DD_VSB_STATUS_RESPONSE_MSE_INFO_MASK) ;
	api->rsp->vsb_status.ber			= (( ( (rspByteBuffer[6]  ) | (rspByteBuffer[5] <<8 ) | (rspByteBuffer[4]  << 16 )) >> DEMOD_DD_VSB_STATUS_RESPONSE_BER_LSB 	 ) & DEMOD_DD_VSB_STATUS_RESPONSE_BER_MASK);
	api->rsp->vsb_status.cfo			= (( ( (rspByteBuffer[9]  ) | (rspByteBuffer[8]  << 8 ) | (rspByteBuffer[7]  << 16 )) >> DEMOD_DD_VSB_STATUS_RESPONSE_CFO_LSB	  ) & DEMOD_DD_VSB_STATUS_RESPONSE_CFO_MASK 	);
	api->rsp->vsb_status.op_mode		= ((rspByteBuffer[10] >> DEMOD_DD_VSB_STATUS_RESPONSE_OP_MODE_LSB		 ) & DEMOD_DD_VSB_STATUS_RESPONSE_OP_MODE_MASK		  );
	api->rsp->vsb_status.pe 		= ((rspByteBuffer[11] >> DEMOD_DD_VSB_STATUS_RESPONSE_PE_LSB		) & DEMOD_DD_VSB_STATUS_RESPONSE_PE_MASK		);
	api->rsp->vsb_status.spInv			= ((rspByteBuffer[12] >> DEMOD_DD_VSB_STATUS_RESPONSE_SPECINV_LSB		 ) & DEMOD_DD_VSB_STATUS_RESPONSE_SPECINV_MASK		  );
	api->rsp->vsb_status.sfo			= (( ( (rspByteBuffer[15]  ) | (rspByteBuffer[14]  << 8 ) | (rspByteBuffer[13]	<< 16 )) >> DEMOD_DD_VSB_STATUS_RESPONSE_SFO_LSB	 ) & DEMOD_DD_VSB_STATUS_RESPONSE_SFO_MASK	   );
	api->rsp->vsb_status.lock_carr		= ((rspByteBuffer[16]  >> DEMOD_DD_VSB_STATUS_RESPONSE_LOCK_CARR_LSB		 ) & DEMOD_DD_VSB_STATUS_RESPONSE_LOCK_CARR_MASK		 );
	api->rsp->vsb_status.lock_fec		= ((rspByteBuffer[16]  >> DEMOD_DD_VSB_STATUS_RESPONSE_LOCK_FEC_LSB 	 ) & DEMOD_DD_VSB_STATUS_RESPONSE_LOCK_FEC_MASK 	 );

	if(api->i2c->chipVer < L18F)
	{
		err |= DEMOD_L0_ReadCommandBytes(api->i2c, 0x709c, 1, &rdData1);
		if(err == NO_DEMOD_ERROR)
		{
			api->rsp->vsb_status.pe 	= ((rdData1 >> DEMOD_DD_VSB_STATUS_RESPONSE_PE_LSB		  ) & DEMOD_DD_VSB_STATUS_RESPONSE_PE_MASK		  );
		}

		err |= DEMOD_L0_ReadCommandBytes(api->i2c, 0x7095, 1, &rdData2);
		err |= DEMOD_L0_ReadCommandBytes(api->i2c, 0x7096, 1, &rdData3);
		err |= DEMOD_L0_ReadCommandBytes(api->i2c, 0x7097, 1, &rdData4);

		if(err == NO_DEMOD_ERROR)
		{
			api->rsp->vsb_status.ber		= (( ( rdData4 | (rdData3 <<8 ) | (rdData2	<< 16 )) >> DEMOD_DD_VSB_STATUS_RESPONSE_BER_LSB	  ) & DEMOD_DD_VSB_STATUS_RESPONSE_BER_MASK);
		}

		err |= DEMOD_L0_ReadCommandBytes(api->i2c, 0x7093, 1, &rdData5);
		err |= DEMOD_L0_ReadCommandBytes(api->i2c, 0x7094, 1, &rdData6);

		if(err == NO_DEMOD_ERROR)
		{
			api->rsp->vsb_status.mse_info		= (( ( rdData6 | (rdData5  << 8 )) >> DEMOD_DD_VSB_STATUS_RESPONSE_MSE_INFO_LSB  ) & DEMOD_DD_VSB_STATUS_RESPONSE_MSE_INFO_MASK) ;
		}
	}

	//printk("***wh***	vsb_status.pe = 0x%x\n", api->rsp->vsb_status.pe);
	//printk("***wh***	vsb_status.ber = 0x%x\n", api->rsp->vsb_status.ber);

	DEMOD_L0_UnlockDevice();
	return err;
}

#endif /* DEMOD_DD_VSB_STATUS_CMD */


#ifdef DEMOD_DD_QAM_STATUS_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_QAM_Status.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_GET_DD_QAM_Status(LX_DEMOD_L1_Context *api)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[20]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;
//	UINT8 rdData[3]={0,};
	UINT8 rdData1=0, rdData2=0, rdData3=0, rdData4=0, rdData5=0, rdData6=0;

	DEMOD_L0_LockDevice();

	rspByte=19;
	cmdByte=1;
	cmdByteBuffer[0] =	DEMOD_DD_QAM_STATUS_CMD;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_QAM_Status ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	api->rsp->qam_status.if_agc 	= (( ( (rspByteBuffer[1]  ) |(rspByteBuffer[0]	<< 8 )) >> DEMOD_DD_QAM_STATUS_RESPONSE_IF_AGC_LSB		) & DEMOD_DD_QAM_STATUS_RESPONSE_IF_AGC_MASK);
	api->rsp->qam_status.mse_info		= (( ( (rspByteBuffer[3]  ) | (rspByteBuffer[2]  << 8 )) >> DEMOD_DD_QAM_STATUS_RESPONSE_MSE_INFO_LSB  ) & DEMOD_DD_QAM_STATUS_RESPONSE_MSE_INFO_MASK) ;
	api->rsp->qam_status.ber			= (( ( (rspByteBuffer[6]  ) | (rspByteBuffer[5] <<8 ) | (rspByteBuffer[4]  << 16 )) >> DEMOD_DD_QAM_STATUS_RESPONSE_BER_LSB 	 ) & DEMOD_DD_QAM_STATUS_RESPONSE_BER_MASK);
	api->rsp->qam_status.cfo			= (( ( (rspByteBuffer[9]  ) | (rspByteBuffer[8]  << 8 ) | (rspByteBuffer[7]  << 16 )) >> DEMOD_DD_QAM_STATUS_RESPONSE_CFO_LSB	  ) & DEMOD_DD_QAM_STATUS_RESPONSE_CFO_MASK 	);
	api->rsp->qam_status.op_mode		= ((rspByteBuffer[10] >> DEMOD_DD_QAM_STATUS_RESPONSE_OP_MODE_LSB		 ) & DEMOD_DD_QAM_STATUS_RESPONSE_OP_MODE_MASK		  );
	api->rsp->qam_status.pe 		= ((rspByteBuffer[11] >> DEMOD_DD_QAM_STATUS_RESPONSE_PE_LSB		) & DEMOD_DD_QAM_STATUS_RESPONSE_PE_MASK		);
	api->rsp->qam_status.spInv		= ((rspByteBuffer[12] >> DEMOD_DD_QAM_STATUS_RESPONSE_SPECINV_LSB		 ) & DEMOD_DD_QAM_STATUS_RESPONSE_SPECINV_MASK		  );
	api->rsp->qam_status.constellation	= (( rspByteBuffer[12] >> DEMOD_DD_QAM_STATUS_RESPONSE_CONSTELLATION_LSB		) & DEMOD_DD_QAM_STATUS_RESPONSE_CONSTELLATION_MASK 	   );
	api->rsp->qam_status.sym_rate		= ((( (rspByteBuffer[14]  ) | (rspByteBuffer[13]  << 8 )) >> DEMOD_DD_QAM_STATUS_RESPONSE_SYM_RATE_LSB		) & DEMOD_DD_QAM_STATUS_RESPONSE_SYM_RATE_MASK);
	api->rsp->qam_status.sfo			= (( ( (rspByteBuffer[17]  ) | (rspByteBuffer[16]  << 8 ) | (rspByteBuffer[15]	<< 16 )) >> DEMOD_DD_QAM_STATUS_RESPONSE_SFO_LSB	 ) & DEMOD_DD_QAM_STATUS_RESPONSE_SFO_MASK	   );
	api->rsp->qam_status.lock_carr		= ((rspByteBuffer[18]  >> DEMOD_DD_QAM_STATUS_RESPONSE_LOCK_CARR_LSB		 ) & DEMOD_DD_QAM_STATUS_RESPONSE_LOCK_CARR_MASK		 );
	api->rsp->qam_status.lock_fec		= ((rspByteBuffer[18]  >> DEMOD_DD_QAM_STATUS_RESPONSE_LOCK_FEC_LSB 	 ) & DEMOD_DD_QAM_STATUS_RESPONSE_LOCK_FEC_MASK 	 );

	if(api->i2c->chipVer < L18F)
	{
		err |= DEMOD_L0_ReadCommandBytes(api->i2c, 0x709c, 1, &rdData1);
		if(err == NO_DEMOD_ERROR)
		{
			api->rsp->qam_status.pe 	= ((rdData1 >> DEMOD_DD_QAM_STATUS_RESPONSE_PE_LSB		  ) & DEMOD_DD_QAM_STATUS_RESPONSE_PE_MASK		  );
		}

		err |= DEMOD_L0_ReadCommandBytes(api->i2c, 0x7095, 1, &rdData2);
		err |= DEMOD_L0_ReadCommandBytes(api->i2c, 0x7096, 1, &rdData3);
		err |= DEMOD_L0_ReadCommandBytes(api->i2c, 0x7097, 1, &rdData4);

		if(err == NO_DEMOD_ERROR)
		{
			api->rsp->qam_status.ber		= (( ( rdData4 | (rdData3 <<8 ) | (rdData2	<< 16 )) >> DEMOD_DD_QAM_STATUS_RESPONSE_BER_LSB	  ) & DEMOD_DD_QAM_STATUS_RESPONSE_BER_MASK);
		}

		err |= DEMOD_L0_ReadCommandBytes(api->i2c, 0x7093, 1, &rdData5);
		err |= DEMOD_L0_ReadCommandBytes(api->i2c, 0x7094, 1, &rdData6);

		if(err == NO_DEMOD_ERROR)
		{
			api->rsp->qam_status.mse_info		= (( ( rdData6 | (rdData5  << 8 )) >> DEMOD_DD_QAM_STATUS_RESPONSE_MSE_INFO_LSB  ) & DEMOD_DD_QAM_STATUS_RESPONSE_MSE_INFO_MASK) ;
		}
	}

	//printk("***wh***	qam_status.pe = 0x%x\n", api->rsp->qam_status.pe);
	//printk("***wh***	qam_status.ber = 0x%x\n", api->rsp->qam_status.ber);

	DEMOD_L0_UnlockDevice();
	return err;
}

#endif /* DEMOD_DD_QAM_STATUS_CMD */


#ifdef DEMOD_DD_GET_PART_INFO_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_PartInfo.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_GET_DD_PartInfo(LX_DEMOD_L1_Context *api)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[8]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	rspByte=7;
	cmdByte=1;
	cmdByteBuffer[0] =  DEMOD_DD_GET_PART_INFO_CMD;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_PartInfo ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	api->rsp->part_info.fw_major 	= ((rspByteBuffer[0]  >> DEMOD_DD_GET_PART_INFO_FW_MAJOR_LSB     ) & DEMOD_DD_GET_PART_INFO_FW_MAJOR_MASK    );
	api->rsp->part_info.fw_minor 	= ((rspByteBuffer[1]  >> DEMOD_DD_GET_PART_INFO_FW_MINOR_LSB     ) & DEMOD_DD_GET_PART_INFO_FW_MINOR_MASK    );
	api->rsp->part_info.fw_year	= ((rspByteBuffer[2]  >> DEMOD_DD_GET_PART_INFO_FW_YEAR_LSB      ) & DEMOD_DD_GET_PART_INFO_FW_YEAR_MASK     );
	api->rsp->part_info.fw_month 	= ((rspByteBuffer[3]  >> DEMOD_DD_GET_PART_INFO_FW_MONTH_LSB     ) & DEMOD_DD_GET_PART_INFO_FW_MONTH_MASK    );
	api->rsp->part_info.fw_day   	= ((rspByteBuffer[4]  >> DEMOD_DD_GET_PART_INFO_FW_DAY_LSB       ) & DEMOD_DD_GET_PART_INFO_FW_DAY_MASK      );
	api->rsp->part_info.chip_rev  	= ((rspByteBuffer[5]  >> DEMOD_DD_GET_PART_INFO_FW_CHIP_REV_LSB  ) & DEMOD_DD_GET_PART_INFO_FW_CHIP_REV_MASK );
	api->rsp->part_info.reserved 	= ((rspByteBuffer[6]  >> DEMOD_DD_GET_PART_INFO_FW_RESERVED_LSB  ) & DEMOD_DD_GET_PART_INFO_FW_RESERVED_MASK );

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_GET_PART_INFO_CMD */


#ifdef DEMOD_DD_SET_TUNE_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_SET_DD_Tune.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_SET_DD_Tune(LX_DEMOD_L1_Context *api)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	cmdByte=1;
	cmdByteBuffer[0] =  DEMOD_DD_SET_TUNE_CMD;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_SET_DD_Tune ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_SET_TUNE_CMD */


#ifdef DEMOD_DD_STATUS_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_Status.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_GET_DD_Status(LX_DEMOD_L1_Context *api)
{

	UINT8 err=0, i=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;
//	UINT32 pucWordData = 0;

	DEMOD_L0_LockDevice();

	rspByte=2;
	cmdByte=1;
	cmdByteBuffer[0] =	DEMOD_DD_STATUS_CMD;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_Status ########## \n\n");
#endif

//	DEMOD_APB_Read(0x90, &pucWordData);
//	DBB_PRINT("\n ########## 1 : DEMOD_APB_Read pucWordData = 0x%x	address = 0x%x########## \n\n", pucWordData, rspByteBuffer);

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	api->rsp->dd_status.reply_operMod	= ((rspByteBuffer[0]  >> DEMOD_DD_STATUS_RESPONSE_MODULATION_LSB ) & DEMOD_DD_STATUS_RESPONSE_MODULATION_MASK);
	api->rsp->dd_status.lock_fec		= ((rspByteBuffer[1]  >> DEMOD_DD_STATUS_RESPONSE_LOCK_FEC_LSB ) & DEMOD_DD_STATUS_RESPONSE_LOCK_FEC_MASK);
	api->rsp->dd_status.neverLock		= ((rspByteBuffer[1]  >> DEMOD_DD_STATUS_RESPONSE_NEVERLOCK_LSB ) & DEMOD_DD_STATUS_RESPONSE_NEVERLOCK_MASK);

	if(api->i2c->chipVer < L18F)
	{
		for(i=0;i<5;i++)
		{
			//err |= DEMOD_I2C_Read(0x7092, 1, &rdata);

			if(((rspByteBuffer[1] >> 4) & 0x0f) <= 0x03)
			{
				//printk("\n ########## fix  rspByteBuffer[1] = 0x%x ###### err = 0x%x #### \n\n", rspByteBuffer[1], err);
				if(err == NO_DEMOD_ERROR)
				{
					api->rsp->dd_status.lock_fec		= ((rspByteBuffer[1]  >> DEMOD_DD_STATUS_RESPONSE_LOCK_FEC_LSB ) & DEMOD_DD_STATUS_RESPONSE_LOCK_FEC_MASK);
					api->rsp->dd_status.neverLock		= ((rspByteBuffer[1]  >> DEMOD_DD_STATUS_RESPONSE_NEVERLOCK_LSB ) & DEMOD_DD_STATUS_RESPONSE_NEVERLOCK_MASK);
				}
				break;
			}
			else
			{
				err |= DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);
			}
			DEMOD_L0_system_wait(20);
//			printk("\n ####################### wrong check value (20ms  DEMOD_L1_Process wait)   rspByteBuffer[1] = 0x%x ###### err = 0x%x #### \n\n", rspByteBuffer[1], err);
		}
	}

//	printk("\n ########## fix  rspByteBuffer[1] = 0x%x ###### err = 0x%x #### \n\n", rdData1, err);
//	DEMOD_APB_Read(0x90, &pucWordData);
//	DBB_PRINT("\n ########## 3 : DEMOD_APB_Read pucWordData = 0x%x address = 0x%x########## \n\n", pucWordData, rspByteBuffer);

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_STATUS_CMD */



#ifdef DEMOD_DD_ATSC3_PLP_SELECT_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_SET_DD_ATSC3_PLP_Select.
 * sets demoduator register through MCU
 *
 * @param *api 				[IN] LX_DEMOD_L1_Context
 * @param plp_id			[IN] UINT8
 * @param plp_id_sel_mode	[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_SET_DD_ATSC3_PLP_Select(LX_DEMOD_L1_Context *api,  UINT8 plp_id, UINT8  plp_id_sel_mode)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;
	
	DEMOD_L0_LockDevice();

	cmdByte=3;
	cmdByteBuffer[0] = DEMOD_DD_ATSC3_PLP_SELECT_CMD;
	cmdByteBuffer[1] =(UINT8)( ( plp_id & DEMOD_DD_ATSC3_PLP_SELECT_CMD_PLP_ID_MASK     ) << DEMOD_DD_ATSC3_PLP_SELECT_CMD_PLP_ID_LSB );
	cmdByteBuffer[2] = (UINT8)( ( plp_id_sel_mode & DEMOD_DD_ATSC3_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MASK     ) << DEMOD_DD_ATSC3_PLP_SELECT_CMD_PLP_ID_SEL_MODE_LSB );

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_SET_DD_ATSC3_PLP_Select ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice();
	return err;

}
#endif /* DEMOD_DD_ATSC3_PLP_SELECT_CMD */


#ifdef DEMOD_DD_ATSC3_STATUS_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_ATSC3_Status.
 * sets demoduator register through MCU
 *
 * @param *api 				[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_GET_DD_ATSC3_Status(LX_DEMOD_L1_Context *api)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[32]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	rspByte=31;
	cmdByte=1;
	cmdByteBuffer[0] =  DEMOD_DD_ATSC3_STATUS_CMD;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_ATSC3_Status ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	api->rsp->atsc3_status.if_agc			= ((((rspByteBuffer[1]  ) | (rspByteBuffer[0]  << 8 )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_IF_AGC_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_IF_AGC_MASK);
	api->rsp->atsc3_status.ctf_pwr			= (( ((rspByteBuffer[5]  ) | (rspByteBuffer[4]  << 8 ) | (rspByteBuffer[3]  << 16 ) | (rspByteBuffer[2]  << 24 )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_CTF_PWR_LSB     ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_CTF_PWR_MASK     );
	api->rsp->atsc3_status.num_plp			=   (( ( (rspByteBuffer[6] )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_TOTAL_NUM_PLP_LSB        ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_TOTAL_NUM_PLP_MASK        );
	api->rsp->atsc3_status.mse_info		= (( ((rspByteBuffer[9]  ) | (rspByteBuffer[8]  << 8 ) | (rspByteBuffer[7]  << 16 ) | (rspByteBuffer[6]  << 24 )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_MSE_INFO_LSB     ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_MSE_INFO_MASK     );
	api->rsp->atsc3_status.ber				= (( ( (rspByteBuffer[12]  ) | (rspByteBuffer[11]  << 8 ) | (rspByteBuffer[10]  << 16 )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_BER_LSB     ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_BER_MASK     );
	api->rsp->atsc3_status.cfo				=   (( ( (rspByteBuffer[15]  ) | (rspByteBuffer[14]  << 8 ) | (rspByteBuffer[13]  << 16 )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_CFO_LSB     ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_CFO_MASK     );
	api->rsp->atsc3_status.op_mode		=   (( ( (rspByteBuffer[16] )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_OP_MODE_LSB        ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_OP_MODE_MASK        );
	api->rsp->atsc3_status.pe				= (( ( (rspByteBuffer[18]  ) | (rspByteBuffer[17]  << 8 )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_PE_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_PE_MASK);
	api->rsp->atsc3_status.lock_carr		=   (( ( (rspByteBuffer[19]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_LOCK_CARR_LSB         ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_LOCK_CARR_MASK         );
	api->rsp->atsc3_status.lock_fec			=   (( ( (rspByteBuffer[19]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_LOCK_FEC_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_LOCK_FEC_MASK      );
	api->rsp->atsc3_status.done_bs_dec		=   (( ( (rspByteBuffer[19]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_DONE_BS_DEC_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_DONE_BS_DEC_MASK      );
	api->rsp->atsc3_status.done_acq		=   (( ( (rspByteBuffer[19]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_DONE_ACQ_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_DONE_ACQ_MASK      );
	api->rsp->atsc3_status.en_fsto_track		=   (( ( (rspByteBuffer[19]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_EN_FSTO_TRACK_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_EN_FSTO_TRACK_MASK      );
	api->rsp->atsc3_status.lock_l1b			=   (( ( (rspByteBuffer[19]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_LOCK_L1B_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_LOCK_L1B_MASK      );
	api->rsp->atsc3_status.lock_l1d			=   (( ( (rspByteBuffer[19]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_LOCK_L1D_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_LOCK_L1D_MASK      );
	api->rsp->atsc3_status.sfo				=   (( ( (rspByteBuffer[22]  ) | (rspByteBuffer[21]  << 8 ) | (rspByteBuffer[20]  << 16 )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_SFO_LSB     ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_SFO_MASK     );
	api->rsp->atsc3_status.mse_info_demod	=   (( ( (rspByteBuffer[26]  ) | (rspByteBuffer[25]  << 8 ) | (rspByteBuffer[24]  << 16 ) | (rspByteBuffer[23]  << 24 )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_MSE_INFO_DEMOD_LSB     ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_MSE_INFO_DEMOD_MASK     );
	api->rsp->atsc3_status.ldpc_err			=   (( ( (rspByteBuffer[28]  ) | (rspByteBuffer[27]  << 8 )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_LDPC_ERR_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_LDPC_ERR_MASK);
	api->rsp->atsc3_status.spInv			=   (( ( (rspByteBuffer[29] )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_SPECINV_LSB        ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_SPECINV_MASK        );
	api->rsp->atsc3_status.fft_mode		=   (( ( (rspByteBuffer[29]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_FFT_MODE_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_FFT_MODE_MASK      );
	api->rsp->atsc3_status.gi				=   (( ( (rspByteBuffer[29]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_LSB     ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_MASK     );
	api->rsp->atsc3_status.bandwidth		=   (( ( (rspByteBuffer[30]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_BANDWIDTH_LSB     ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_BANDWIDTH_MASK     );
	api->rsp->atsc3_status.num_plp 		+= 1;

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_ATSC3_STATUS_CMD */

#ifdef DEMOD_DD_ATSC3_PLP_ID_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_ATSC3_PLP_ID.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @param index			[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_GET_DD_ATSC3_PLP_ID(LX_DEMOD_L1_Context *api, UINT8 index)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	rspByte=1;
	cmdByte=2;
	cmdByteBuffer[0] =  DEMOD_DD_ATSC3_PLP_ID_CMD;
	cmdByteBuffer[1] =  index;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_ATSC3_PLP_ID ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	api->rsp->atsc3_plp_id.l1d_plp_id_flag	=(((rspByteBuffer[0] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_L1D_PLP_ID_FLAG_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_L1D_PLP_ID_FLAG_MASK        );
	api->rsp->atsc3_plp_id.l1d_slt_flag		=(((rspByteBuffer[0] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_L1D_PLP_SLT_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_L1D_PLP_SLT_MASK        );

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_ATSC3_PLP_ID_CMD */

#ifdef DEMOD_DD_ATSC3_PLP_INFO_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_ATSC3_PLP_Info.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @param index			[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_GET_DD_ATSC3_PLP_Info(LX_DEMOD_L1_Context *api, UINT8 index)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[16]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	rspByte=15;
	cmdByte=2;
	cmdByteBuffer[0] =  DEMOD_DD_ATSC3_PLP_INFO_CMD;
	cmdByteBuffer[1] =  index;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_ATSC3_PLP_Info ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	api->rsp->atsc3_plp_info.l1b_num_subframes 				=((( rspByteBuffer[0] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_NUM_SUBFRAMES_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_NUM_SUBFRAMES_MASK        );
	api->rsp->atsc3_plp_info.l1b_pre_num_symbols			=(((rspByteBuffer[1] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_PRE_NUM_SYMBOLS_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_PRE_NUM_SYMBOLS_MASK        );
	api->rsp->atsc3_plp_info.l1b_first_sub_fft_size				=(((rspByteBuffer[1] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_FFT_SIZE_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_FFT_SIZE_MASK        );
	api->rsp->atsc3_plp_info.l1b_first_num_ofdm_symbols		=((((rspByteBuffer[2]  ) | (rspByteBuffer[1] << 8 )) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_NUM_OFDM_SYMBOLS_LSB      ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_NUM_OFDM_SYMBOLS_MASK);
	api->rsp->atsc3_plp_info.l1b_first_sub_gi					=(((rspByteBuffer[3] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_GI_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_GI_MASK        );
	api->rsp->atsc3_plp_info.l1b_first_reduce_carr				=(((rspByteBuffer[3] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_REDUCE_CARR_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_REDUCE_CARR_MASK        );
	api->rsp->atsc3_plp_info.l1b_first_sub_scatt_pp			=(((rspByteBuffer[4] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SCATT_PP_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SCATT_PP_MASK        );
	api->rsp->atsc3_plp_info.l1b_first_sub_scatt_pb			=(((rspByteBuffer[4] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SCATT_PB_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SCATT_PB_MASK        );
	api->rsp->atsc3_plp_info.l1b_first_sub_sbs_first			=(((rspByteBuffer[5] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SBS_FIRST_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SBS_FIRST_MASK        );
	api->rsp->atsc3_plp_info.l1b_first_sub_sbs_last			=(((rspByteBuffer[5] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SBS_LAST_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SBS_LAST_MASK        );
	api->rsp->atsc3_plp_info.l1d_num_plp					=(((rspByteBuffer[5] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_NUM_PLP_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_NUM_PLP_MASK        );
	api->rsp->atsc3_plp_info.l1d_plp_fec_type				=(((rspByteBuffer[6] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_FEC_TYPE_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_FEC_TYPE_MASK        );
	api->rsp->atsc3_plp_info.l1d_plp_ti_mode					=(((rspByteBuffer[6] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_TI_MODE_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_TI_MODE_MASK        );
	api->rsp->atsc3_plp_info.l1d_plp_mod					=(((rspByteBuffer[7] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_MASK        );
	api->rsp->atsc3_plp_info.l1d_plp_cr						=(((rspByteBuffer[7] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_MASK        );
	api->rsp->atsc3_plp_info.l1d_plp_cti_depth				=(((rspByteBuffer[8] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CTI_DEPTH_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CTI_DEPTH_MASK        );
	api->rsp->atsc3_plp_info.l1d_plp_hti_inter_subframe		=(((rspByteBuffer[8] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_HTI_INTER_SUBFRAMES_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_HTI_INTER_SUBFRAMES_MASK        );
	api->rsp->atsc3_plp_info.l1d_plp_cti_start_row				=((((rspByteBuffer[9] ) | (rspByteBuffer[8]  << 8 )) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CTI_START_ROW_LSB      ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CTI_START_ROW_MASK);
	api->rsp->atsc3_plp_info.l1d_plp_hti_num_ti_blocks			=(((rspByteBuffer[10] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_HTI_NUM_TI_BLOCKS_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_HTI_NUM_TI_BLOCKS_MASK        );
	api->rsp->atsc3_plp_info.l1d_plp_hti_num_fec_blocks_max	=((((rspByteBuffer[11]  ) | (rspByteBuffer[10]  << 8 )) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_HTI_NUM_FEC_BLOCKS_MAX_LSB      ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_HTI_NUM_FEC_BLOCKS_MAX_MASK);
	api->rsp->atsc3_plp_info.l1d_mimo						=(((rspByteBuffer[12] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_MIMO_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_MIMO_MASK        );
	api->rsp->atsc3_plp_info.l1d_miso						=(((rspByteBuffer[12] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_MISO_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_MISO_MASK        );
	api->rsp->atsc3_plp_info.l1d_plp_hti_num_fec_blocks		=((((rspByteBuffer[13]  ) | (rspByteBuffer[12]  << 8 )) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_HTI_NUM_FEC_BLOCKS_LSB      ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_HTI_NUM_FEC_BLOCKS_MASK);
	api->rsp->atsc3_plp_info.bs_pre_str						=(( ( (rspByteBuffer[14]  )) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_BS_PRE_STR_LSB     ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_BS_PRE_STR_MASK     );
	api->rsp->atsc3_plp_info.bs_l1b_mod					=(( ( (rspByteBuffer[14]  )) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_BS_L1B_MOD_LSB     ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_BS_L1B_MOD_MASK     );

	api->rsp->atsc3_plp_info.l1b_num_subframes				+= 1;
	api->rsp->atsc3_plp_info.l1b_pre_num_symbols			+= 1;
	api->rsp->atsc3_plp_info.l1b_first_num_ofdm_symbols		+= 1;
	api->rsp->atsc3_plp_info.l1d_num_plp					+= 1;
	api->rsp->atsc3_plp_info.l1d_plp_hti_num_ti_blocks			+= 1;
	api->rsp->atsc3_plp_info.l1d_plp_hti_num_fec_blocks		+= 1;
	api->rsp->atsc3_plp_info.bs_pre_str						= api->rsp->atsc3_plp_info.bs_pre_str + (api->rsp->atsc3_plp_info.bs_l1b_mod * 17);
	api->rsp->atsc3_plp_info.bs_l1b_mod					+= 1;

	DEMOD_L0_UnlockDevice();
	return err;

}
#endif /* DEMOD_DD_ATSC3_PLP_INFO_CMD */


#if 0
#endif

/*************************************************************************************/
/*************************************************************************************/
/*********ISDB-T/ DVBC / DVBC2/ DVBT / DVBT2/DVBS / DVBS2 / DEBUG/ functions **********/
/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/

#ifndef LG3307_API

#ifdef DEMOD_DD_ISDBT_BASEADDR_AXI_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_SET_DD_ISDBT_BASEADDR_AXI.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @param baseAddr		[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_SET_DD_ISDBT_BASEADDR_AXI(LX_DEMOD_L1_Context *api, UINT32 baseAddr)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[8]={0,};
	UINT8 rspByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	rspByte=1;
	if(api->i2c->chipVer >= L18F)
	{
		cmdByte = 8;
		cmdByteBuffer[0] =  DEMOD_DD_ISDBT_BASEADDR_AXI_CMD;
		cmdByteBuffer[1] =  0;
		cmdByteBuffer[2] =  0;
		cmdByteBuffer[3] =  0;
		cmdByteBuffer[4] =  (UINT8) ( (baseAddr & DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_BASEADDR_LSB );
		cmdByteBuffer[5] =  (UINT8) (((baseAddr & DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 8);
		cmdByteBuffer[6] =  (UINT8) (((baseAddr & DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 16);
		cmdByteBuffer[7] =  (UINT8) (((baseAddr & DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 24);
	}
	else
	{
		cmdByte = 5;
		cmdByteBuffer[0] =  DEMOD_DD_ISDBT_BASEADDR_AXI_CMD;
		cmdByteBuffer[1] =  (UINT8) (((baseAddr & DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 24);
		cmdByteBuffer[2] =  (UINT8) (((baseAddr & DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 16);
		cmdByteBuffer[3] =  (UINT8) (((baseAddr & DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 8);
		cmdByteBuffer[4] =  (UINT8) ( (baseAddr & DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_BASEADDR_LSB );
	}

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_SET_DD_ISDBT_BASEADDR_AXI ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice();
	return err;

}
#endif /* DEMOD_DD_ISDBT_BASEADDR_AXI_CMD */

#ifdef DEMOD_DD_DTMB_BASEADDR_AXI_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_SET_DD_DTMB_BASEADDR_AXI.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @param baseAddr		[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_SET_DD_DTMB_BASEADDR_AXI(LX_DEMOD_L1_Context *api, UINT32 baseAddr)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[8]={0,};
	UINT8 rspByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	rspByte=1;
	if(api->i2c->chipVer >= L18F)
	{
		cmdByte = 8;
		cmdByteBuffer[0] =  DEMOD_DD_DTMB_BASEADDR_AXI_CMD;
		cmdByteBuffer[1] =  0;
		cmdByteBuffer[2] =  0;
		cmdByteBuffer[3] =  0;
		cmdByteBuffer[4] =  (UINT8) ( (baseAddr & DEMOD_DD_DTMB_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DTMB_BASEADDR_AXI_CMD_BASEADDR_LSB );
		cmdByteBuffer[5] =  (UINT8) (((baseAddr & DEMOD_DD_DTMB_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DTMB_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 8);
		cmdByteBuffer[6] =  (UINT8) (((baseAddr & DEMOD_DD_DTMB_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DTMB_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 16);
		cmdByteBuffer[7] =  (UINT8) (((baseAddr & DEMOD_DD_DTMB_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DTMB_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 24);
	}
	else
	{
		cmdByte = 5;
		cmdByteBuffer[0] =  DEMOD_DD_DTMB_BASEADDR_AXI_CMD;
		cmdByteBuffer[1] =  (UINT8) (((baseAddr & DEMOD_DD_DTMB_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DTMB_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 24);
		cmdByteBuffer[2] =  (UINT8) (((baseAddr & DEMOD_DD_DTMB_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DTMB_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 16);
		cmdByteBuffer[3] =  (UINT8) (((baseAddr & DEMOD_DD_DTMB_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DTMB_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 8);
		cmdByteBuffer[4] =  (UINT8) ( (baseAddr & DEMOD_DD_DTMB_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DTMB_BASEADDR_AXI_CMD_BASEADDR_LSB );
	}

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_SET_DD_DTMB_BASEADDR_AXI ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice();
	return err;

}
#endif /* DEMOD_DD_DTMB_BASEADDR_AXI_CMD */

#ifdef DEMOD_DD_DVBC_SRD_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_SET_DD_SymbolRate_Detect.
 * detects the symbol rate automatically or manually.
 *
 * @param *i2c 			[IN] LX_DEMOD_L1_Context
 * @param auto_en 		[IN] UINT8
 * @param sym_rate 		[IN] UINT16
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_SET_DD_SymbolRate_Detect(LX_DEMOD_L1_Context *api, UINT8 auto_en, UINT16 sym_rate)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	rspByte=2;
	cmdByte=4;
	cmdByteBuffer[0] = DEMOD_DD_DVBC_SRD_CMD;
	cmdByteBuffer[1] = (UINT8) ( ( auto_en & DEMOD_DD_DVBC_SRD_CMD_AUTO_EN_MASK ) << DEMOD_DD_DVBC_SRD_CMD_AUTO_EN_LSB );
	cmdByteBuffer[2] = (UINT8) ( ( sym_rate & DEMOD_DD_DVBC_SRD_CMD_SYM_RATE1_MASK ) >> DEMOD_DD_DVBC_SRD_CMD_SYM_RATE1_SHIFT );
	cmdByteBuffer[3] = (UINT8) ( ( sym_rate & DEMOD_DD_DVBC_SRD_CMD_SYM_RATE2_MASK ) >> DEMOD_DD_DVBC_SRD_CMD_SYM_RATE2_LSB );

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_SET_DD_SymbolRate_Detect ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_DVBC_SRD_CMD */


#ifdef DEMOD_DD_DVBT2_PLP_SELECT_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_SET_DD_DVBT2_PLP_Select.
 * sets demoduator register through MCU
 *
 * @param *api 				[IN] LX_DEMOD_L1_Context
 * @param plp_id			[IN] UINT8
 * @param plp_id_sel_mode	[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_SET_DD_DVBT2_PLP_Select(LX_DEMOD_L1_Context *api,  UINT8 plp_id, UINT8   plp_id_sel_mode)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	cmdByte=3;
	cmdByteBuffer[0] = DEMOD_DD_DVBT2_PLP_SELECT_CMD;
	cmdByteBuffer[1] =(UINT8)( ( plp_id & DEMOD_DD_DVBT2_PLP_SELECT_CMD_PLP_ID_MASK     ) << DEMOD_DD_DVBT2_PLP_SELECT_CMD_PLP_ID_LSB );
	cmdByteBuffer[2] = (UINT8)( ( plp_id_sel_mode & DEMOD_DD_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MASK     ) << DEMOD_DD_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_LSB );

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_SET_DD_DVBT2_PLP_Select ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_DVBT2_PLP_SELECT_CMD */


#ifdef DEMOD_DD_DVBC2_STARTFREQUENCY_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_SET_DD_DVBC2_StartFrequency.
 * sets demoduator register through MCU
 *
 * @param *api 				[IN] LX_DEMOD_L1_Context
 * @param freq				[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_SET_DD_DVBC2_StartFrequency(LX_DEMOD_L1_Context *api, UINT32 freq)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[8]={0,};
	UINT8 rspByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	cmdByte=5;
	cmdByteBuffer[0] = DEMOD_DD_DVBC2_STARTFREQUENCY_CMD;
	cmdByteBuffer[1] = (UINT8) (( ( freq & DEMOD_DD_DVBC2_STARTFREQUENCY_CMD_FREQ_MASK ) << DEMOD_DD_DVBC2_STARTFREQUENCY_CMD_FREQ_LSB ) >> 24);
   	cmdByteBuffer[2] = (UINT8) (( ( freq & DEMOD_DD_DVBC2_STARTFREQUENCY_CMD_FREQ_MASK ) << DEMOD_DD_DVBC2_STARTFREQUENCY_CMD_FREQ_LSB ) >> 16);
   	cmdByteBuffer[3] = (UINT8) (( ( freq & DEMOD_DD_DVBC2_STARTFREQUENCY_CMD_FREQ_MASK ) << DEMOD_DD_DVBC2_STARTFREQUENCY_CMD_FREQ_LSB ) >> 8);
   	cmdByteBuffer[4] = (UINT8) (( ( freq & DEMOD_DD_DVBC2_STARTFREQUENCY_CMD_FREQ_MASK ) << DEMOD_DD_DVBC2_STARTFREQUENCY_CMD_FREQ_LSB ) >> 0);

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_SET_DD_DVBC2_StartFrequency ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_DVBC2_STARTFREQUENCY_CMD */


#ifdef DEMOD_DD_DVBC2_PLP_SELECT_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_SET_DD_DVBC2_PLP_Select.
 * sets demoduator register through MCU
 *
 * @param *api 				[IN] LX_DEMOD_L1_Context
 * @param plp_id			[IN] UINT8
 * @param plp_id_mode		[IN] UINT8
 * @param ds_id				[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_SET_DD_DVBC2_PLP_Select(LX_DEMOD_L1_Context *api,  UINT8 plp_id, UINT8 plp_id_mode, UINT8 ds_id)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	cmdByte=4;
	cmdByteBuffer[0] = DEMOD_DD_DVBC2_PLP_SELECT_CMD;
	cmdByteBuffer[1] = (UINT8) (( plp_id_mode & DEMOD_DD_DVBC2_PLP_SELECT_CMD_PLP_ID_MODE_MASK ) << DEMOD_DD_DVBC2_PLP_SELECT_CMD_PLP_ID_MODE_LSB );
	cmdByteBuffer[2] = (UINT8)( ( plp_id & DEMOD_DD_DVBC2_PLP_SELECT_CMD_PLP_ID_MASK     ) << DEMOD_DD_DVBC2_PLP_SELECT_CMD_PLP_ID_LSB );
	cmdByteBuffer[3] = (UINT8) (( ds_id & DEMOD_DD_DVBC2_PLP_SELECT_CMD_DS_ID_MASK ) << DEMOD_DD_DVBC2_PLP_SELECT_CMD_DS_ID_LSB );

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_SET_DD_DVBC2_PLP_Select ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_DVBC2_PLP_SELECT_CMD */


#ifdef DEMOD_DD_DISEQC_SEND_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_SET_DD_DISEQC_Send.
 * sets demoduator register through MCU
 *
 * @param *api 				[IN] LX_DEMOD_L1_Context
 * @param diseqc_en			[IN] UINT8
 * @param tone_burst		[IN] UINT8
 * @param cont_tone			[IN] UINT8
 * @param burst_sel			[IN] UINT8
 * @param msg_length		[IN] UINT8
 * @param send_framing		[IN] UINT8
 * @param send_address		[IN] UINT8
 * @param send_command		[IN] UINT8
 * @param send_data0		[IN] UINT8
 * @param send_data1		[IN] UINT8
 * @param send_data2		[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_SET_DD_DISEQC_Send(LX_DEMOD_L1_Context *api,
												UINT8 diseqc_en,
												UINT8 tone_burst,
												UINT8 cont_tone,
												UINT8 burst_sel,
												UINT8 msg_length,
												UINT8 send_framing,
												UINT8 send_address,
												UINT8 send_command,
												UINT8 send_data0,
												UINT8 send_data1,
												UINT8 send_data2 )
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[8]={0,};
	UINT8 rspByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;
	
	DEMOD_L0_LockDevice();

	cmdByte=8;
	cmdByteBuffer[0] = DEMOD_DD_DISEQC_SEND_CMD;
	cmdByteBuffer[1] = (UINT8) ( ( diseqc_en & DEMOD_DD_DISEQC_SEND_CMD_DISEQC_EN_MASK ) << DEMOD_DD_DISEQC_SEND_CMD_DISEQC_EN_LSB |
                                         ( tone_burst & DEMOD_DD_DISEQC_SEND_CMD_TONE_BURST_MASK ) << DEMOD_DD_DISEQC_SEND_CMD_TONE_BURST_LSB |
                                         ( cont_tone & DEMOD_DD_DISEQC_SEND_CMD_CONT_TONE_MASK ) << DEMOD_DD_DISEQC_SEND_CMD_CONT_TONE_LSB |
                                         ( burst_sel& DEMOD_DD_DISEQC_SEND_CMD_BURST_SEL_MASK ) << DEMOD_DD_DISEQC_SEND_CMD_BURST_SEL_LSB |
                                         ( msg_length     & DEMOD_DD_DISEQC_SEND_CMD_MSG_LENGTH_MASK     ) << DEMOD_DD_DISEQC_SEND_CMD_MSG_LENGTH_LSB);

	cmdByteBuffer[2] = (UINT8) ( ( send_framing & DEMOD_DD_DISEQC_SEND_CMD_SEND_FRAMING_MASK ) << DEMOD_DD_DISEQC_SEND_CMD_SEND_FRAMING_LSB );
	cmdByteBuffer[3] = (UINT8)	( ( send_address & DEMOD_DD_DISEQC_SEND_CMD_SEND_ADDRESS_MASK ) << DEMOD_DD_DISEQC_SEND_CMD_SEND_ADDRESS_LSB );
	cmdByteBuffer[4] = (UINT8)	( ( send_command & DEMOD_DD_DISEQC_SEND_CMD_SEND_COMMAND_MASK ) << DEMOD_DD_DISEQC_SEND_CMD_SEND_COMMAND_LSB );
	cmdByteBuffer[5] = (UINT8)	( ( send_data0 & DEMOD_DD_DISEQC_SEND_CMD_SEND_DATA0_MASK ) << DEMOD_DD_DISEQC_SEND_CMD_SEND_DATA0_LSB );
	cmdByteBuffer[6] = (UINT8)	( ( send_data1 & DEMOD_DD_DISEQC_SEND_CMD_SEND_DATA1_MASK ) << DEMOD_DD_DISEQC_SEND_CMD_SEND_DATA1_LSB );
	cmdByteBuffer[7] = (UINT8)	( ( send_data2 & DEMOD_DD_DISEQC_SEND_CMD_SEND_DATA2_MASK ) << DEMOD_DD_DISEQC_SEND_CMD_SEND_DATA2_LSB );

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_SET_DD_DISEQC_Send ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_DISEQC_SEND_CMD */


#ifdef DEMOD_DD_DVBS_OPERATING_MODE_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_SET_DD_DVBS_Blind_Scan_Mode.
 * sets demoduator register through MCU
 *
 * @param *api 				[IN] LX_DEMOD_L1_Context
 * @param opmSel			[IN] UINT8
 * @param symbolRate_Khz	[IN] UINT32
 * @param tuneFreq_Khz		[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_SET_DD_DVBS_Blind_Scan_Mode(	LX_DEMOD_L1_Context *api, UINT8 opmSel, UINT32 symbolRate_Khz, UINT32 tuneFreq_Khz)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[12]={0,};
	UINT8 rspByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	cmdByte=10;
	cmdByteBuffer[0] = DEMOD_DD_DVBS_OPERATING_MODE_CMD;
  	cmdByteBuffer[1] = (UINT8) ( ( opmSel & DEMOD_DD_DVBS_OPERATING_MODE_CMD_OPM_SEL_MASK ) << DEMOD_DD_DVBS_OPERATING_MODE_CMD_OPM_SEL_LSB );
	cmdByteBuffer[2] = (UINT8) (( ( symbolRate_Khz & DEMOD_DD_DVBS_OPERATING_MODE_CMD_SYMBOL_RATE_MASK ) << DEMOD_DD_DVBS_OPERATING_MODE_CMD_SYMBOL_RATE_LSB ) >> 24);
	cmdByteBuffer[3] = (UINT8) (( ( symbolRate_Khz & DEMOD_DD_DVBS_OPERATING_MODE_CMD_SYMBOL_RATE_MASK ) << DEMOD_DD_DVBS_OPERATING_MODE_CMD_SYMBOL_RATE_LSB ) >> 16);
	cmdByteBuffer[4] = (UINT8) (( ( symbolRate_Khz & DEMOD_DD_DVBS_OPERATING_MODE_CMD_SYMBOL_RATE_MASK ) << DEMOD_DD_DVBS_OPERATING_MODE_CMD_SYMBOL_RATE_LSB ) >> 8);
	cmdByteBuffer[5] = (UINT8) (  ( symbolRate_Khz & DEMOD_DD_DVBS_OPERATING_MODE_CMD_SYMBOL_RATE_MASK ) << DEMOD_DD_DVBS_OPERATING_MODE_CMD_SYMBOL_RATE_LSB );
	cmdByteBuffer[6] = (UINT8) (( ( tuneFreq_Khz & DEMOD_DD_DVBS_OPERATING_MODE_CMD_TUNE_FREQ3_MASK ) << DEMOD_DD_DVBS_OPERATING_MODE_CMD_TUN_FREQ3_LSB ) >> 24);
	cmdByteBuffer[7] = (UINT8) (( ( tuneFreq_Khz & DEMOD_DD_DVBS_OPERATING_MODE_CMD_TUNE_FREQ2_MASK ) << DEMOD_DD_DVBS_OPERATING_MODE_CMD_TUN_FREQ2_LSB ) >> 16);
	cmdByteBuffer[8] = (UINT8) (( ( tuneFreq_Khz & DEMOD_DD_DVBS_OPERATING_MODE_CMD_TUNE_FREQ1_MASK ) << DEMOD_DD_DVBS_OPERATING_MODE_CMD_TUN_FREQ1_LSB ) >> 8);
	cmdByteBuffer[9] = (UINT8) (  ( tuneFreq_Khz & DEMOD_DD_DVBS_OPERATING_MODE_CMD_TUNE_FREQ0_MASK ) << DEMOD_DD_DVBS_OPERATING_MODE_CMD_TUN_FREQ0_LSB );

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_SET_DD_DVBS_Blind_Scan_Mode ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_DVBS_OPERATING_MODE_CMD */


#ifdef DEMOD_DD_SELFRST_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_SET_DD_SelfRst.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @param rst_arg		[IN] UINT8
 * @param rst_time1		[IN] UINT16
 * @param rst_time2		[IN] UINT16
 * @param rst_time3		[IN] UINT16
 * @param rst_time4		[IN] UINT16
 * @param rst_cnt		[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_SET_DD_SelfRst(LX_DEMOD_L1_Context *api, UINT8  rst_arg, UINT16 rst_time1, UINT16 rst_time2, UINT16 rst_time3, UINT16 rst_time4, UINT8 rst_cnt)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[20]={0,};
	UINT8 rspByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	cmdByte=11;
	cmdByteBuffer[0] = DEMOD_DD_SELFRST_CMD;
	cmdByteBuffer[1] = (UINT8) ( ( rst_arg	& DEMOD_DD_SELFRST_CMD_RST_ARG_MASK	  ) >> DEMOD_DD_SELFRST_CMD_RST_ARG_LSB );
	cmdByteBuffer[2] = (UINT8) ( ( rst_time1 & DEMOD_DD_SELFRST_CMD_RST_TIME1_MASK ) >> DEMOD_DD_SELFRST_CMD_RST_TIME1_LSB );
	cmdByteBuffer[3] = (UINT8) ( ( rst_time1 & DEMOD_DD_SELFRST_CMD_RST_TIME2_MASK ) >> DEMOD_DD_SELFRST_CMD_RST_TIME2_LSB );
	cmdByteBuffer[4] = (UINT8) ( ( rst_time2 & DEMOD_DD_SELFRST_CMD_RST_TIME1_MASK ) >> DEMOD_DD_SELFRST_CMD_RST_TIME1_LSB );
	cmdByteBuffer[5] = (UINT8) ( ( rst_time2 & DEMOD_DD_SELFRST_CMD_RST_TIME2_MASK ) >> DEMOD_DD_SELFRST_CMD_RST_TIME2_LSB );
	cmdByteBuffer[6] = (UINT8) ( ( rst_time3 & DEMOD_DD_SELFRST_CMD_RST_TIME1_MASK ) >> DEMOD_DD_SELFRST_CMD_RST_TIME1_LSB );
	cmdByteBuffer[7] = (UINT8) ( ( rst_time3 & DEMOD_DD_SELFRST_CMD_RST_TIME2_MASK ) >> DEMOD_DD_SELFRST_CMD_RST_TIME2_LSB );
	cmdByteBuffer[8] = (UINT8) ( ( rst_time4 & DEMOD_DD_SELFRST_CMD_RST_TIME1_MASK ) >> DEMOD_DD_SELFRST_CMD_RST_TIME1_LSB );
	cmdByteBuffer[9] = (UINT8) ( ( rst_time4 & DEMOD_DD_SELFRST_CMD_RST_TIME2_MASK ) >> DEMOD_DD_SELFRST_CMD_RST_TIME2_LSB );
	cmdByteBuffer[10] = (UINT8) ( ( rst_cnt	& DEMOD_DD_SELFRST_CMD_RST_ARG_MASK	  ) >> DEMOD_DD_SELFRST_CMD_RST_ARG_LSB );

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_SET_DD_SelfRst ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_SELFRST_CMD */


#ifdef DEMOD_DD_DVBT2_STATUS_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_DVBT2_Status.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_GET_DD_DVBT2_Status(LX_DEMOD_L1_Context *api)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
//	UINT8 rspByteBuffer[24]={0,};
	UINT8 rspByteBuffer[28]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();
	//rspByte=26;
	rspByte=28;
	//rspByte=23;
	cmdByte=1;
	cmdByteBuffer[0] =  DEMOD_DD_DVBT2_STATUS_CMD;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_DVBT2_Status ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	api->rsp->dvbt2_status.if_agc				= (( ( (rspByteBuffer[1]  ) | (rspByteBuffer[0]  << 8 )) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_IF_AGC_LSB      ) & DEMOD_DD_DVBT2_STATUS_RESPONSE_IF_AGC_MASK);
	api->rsp->dvbt2_status.mse_info			= (( ( (rspByteBuffer[3]  ) | (rspByteBuffer[2]  << 8 )) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_MSE_INFO_LSB      ) & DEMOD_DD_DVBT2_STATUS_RESPONSE_MSE_INFO_MASK);
	api->rsp->dvbt2_status.ber					= (( (rspByteBuffer[6] << 0 ) | ( (rspByteBuffer[5] << 8 ) | (rspByteBuffer[4]  << 16 )) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_BER_LSB      ) & DEMOD_DD_DVBT2_STATUS_RESPONSE_BER_MASK);
	api->rsp->dvbt2_status.cfo					= (( ( (rspByteBuffer[9]  ) | (rspByteBuffer[8]  << 8 ) | (rspByteBuffer[7]  << 16 )) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_CFO_LSB     ) & DEMOD_DD_DVBT2_STATUS_RESPONSE_CFO_MASK     );
	api->rsp->dvbt2_status.op_mode			= (( ( (rspByteBuffer[10] )) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_OP_MODE_LSB        ) & DEMOD_DD_DVBT2_STATUS_RESPONSE_OP_MODE_MASK        );
	api->rsp->dvbt2_status.pe					= (( ( (rspByteBuffer[11] )) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_PE_LSB        ) & DEMOD_DD_DVBT2_STATUS_RESPONSE_PE_MASK        );
	api->rsp->dvbt2_status.spInv				= (( ( (rspByteBuffer[12] )) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_SPECINV_LSB        ) & DEMOD_DD_DVBT2_STATUS_RESPONSE_SPECINV_MASK        );
	api->rsp->dvbt2_status.fft_mode			= (( ( (rspByteBuffer[12]  )) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_FFT_MODE_LSB      ) & DEMOD_DD_DVBT2_STATUS_RESPONSE_FFT_MODE_MASK      );
	api->rsp->dvbt2_status.gi					= (( ( (rspByteBuffer[12]  )) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_LSB     ) & DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_MASK     );
	api->rsp->dvbt2_status.constellation			= (( ( (rspByteBuffer[13] )) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_CONSTELLATION_LSB        ) & DEMOD_DD_DVBT2_STATUS_RESPONSE_CONSTELLATION_MASK        );
	api->rsp->dvbt2_status.constellation_cm		= (( ( (rspByteBuffer[13] )) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_CONSTELLATION_CM_LSB        ) & DEMOD_DD_DVBT2_STATUS_RESPONSE_CONSTELLATION_CM_MASK        );
	api->rsp->dvbt2_status.cr   				= (( ( (rspByteBuffer[14] )) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_LSB     ) & DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_MASK     );
	api->rsp->dvbt2_status.cr_cm   				= (( ( (rspByteBuffer[14] )) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_CM_LSB     ) & DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_CM_MASK     );
	api->rsp->dvbt2_status.current_plp_id		= (( ( (rspByteBuffer[15] )) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_CURRENT_PLP_ID_LSB        ) & DEMOD_DD_DVBT2_STATUS_RESPONSE_CURRENT_PLP_ID_MASK        );
	api->rsp->dvbt2_status.current_plp_id_cm	= (( ( (rspByteBuffer[16] )) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_CURRENT_PLP_ID_CM_LSB        ) & DEMOD_DD_DVBT2_STATUS_RESPONSE_CURRENT_PLP_ID_CM_MASK        );
	api->rsp->dvbt2_status.num_plp			= (( ( (rspByteBuffer[17] )) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_NUM_PLP_LSB        ) & DEMOD_DD_DVBT2_STATUS_RESPONSE_NUM_PLP_MASK        );
	api->rsp->dvbt2_status.num_dplp			= (( ( (rspByteBuffer[18] )) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_NUM_DPLP_LSB        ) & DEMOD_DD_DVBT2_STATUS_RESPONSE_NUM_DPLP_MASK        );
	api->rsp->dvbt2_status.sfo					= (( ( (rspByteBuffer[21]  ) | (rspByteBuffer[20]  << 8 ) | (rspByteBuffer[19]  << 16 )) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_SFO_LSB     ) & DEMOD_DD_DVBT2_STATUS_RESPONSE_SFO_MASK     );
	api->rsp->dvbt2_status.lock_carr			= (( ( (rspByteBuffer[22]  )) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_LOCK_CARR_LSB         ) & DEMOD_DD_DVBT2_STATUS_RESPONSE_LOCK_CARR_MASK         );
	api->rsp->dvbt2_status.lock_fec				= (( ( (rspByteBuffer[22]  )) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_LOCK_FEC_LSB      ) & DEMOD_DD_DVBT2_STATUS_RESPONSE_LOCK_FEC_MASK      );
	api->rsp->dvbt2_status.mse_info_demod		= (( ( (rspByteBuffer[25]  ) | (rspByteBuffer[24] << 8)) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_MSE_INFO_DEMOD_LSB      ) & DEMOD_DD_DVBT2_STATUS_RESPONSE_MSE_INFO_DEMOD_MASK      );
	api->rsp->dvbt2_status.cell_id				= (( ( (rspByteBuffer[27]  ) | (rspByteBuffer[26] << 8)) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_CELL_ID_LSB      ) & DEMOD_DD_DVBT2_STATUS_RESPONSE_CELL_ID_MASK      );

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_DVBT2_STATUS_CMD */


#ifdef DEMOD_DD_GET_DVBT2_PLP_ID_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_DVBT2_PLP_ID.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @param index			[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_GET_DD_DVBT2_PLP_ID(LX_DEMOD_L1_Context *api, UINT8 index)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	rspByte=2;
	cmdByte=2;
	cmdByteBuffer[0] =  DEMOD_DD_GET_DVBT2_PLP_ID_CMD;
	cmdByteBuffer[1] =  index;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_DVBT2_PLP_ID ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	api->rsp->dvbt2_plp_id.plp_id				=(((rspByteBuffer[0] ) >> DEMOD_DD_GET_DVBT2_PLP_ID_RESPONSE_PLP_ID_LSB        ) & DEMOD_DD_GET_DVBT2_PLP_ID_RESPONSE_PLP_ID_MASK        );
	api->rsp->dvbt2_plp_id.plp_conf				=(((rspByteBuffer[1] ) >> DEMOD_DD_GET_DVBT2_PLP_ID_RESPONSE_PLP_CONF_LSB        ) & DEMOD_DD_GET_DVBT2_PLP_ID_RESPONSE_PLP_CONF_MASK        );

	DEMOD_L0_UnlockDevice();
	return err;

}
#endif /* DEMOD_DD_GET_DVBT2_PLP_ID_CMD */


#ifdef DEMOD_DD_DVBT_STATUS_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_DVBT_Status.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_GET_DD_DVBT_Status(LX_DEMOD_L1_Context *api)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[24]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	rspByte=24;
	cmdByte=1;
	cmdByteBuffer[0] =  DEMOD_DD_DVBT_STATUS_CMD;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_DVBT_Status ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	api->rsp->dvbt_status.if_agc			= (( ( (rspByteBuffer[1]  ) |(rspByteBuffer[0]  << 8 )) >> DEMOD_DD_DVBT_STATUS_RESPONSE_IF_AGC_LSB      ) & DEMOD_DD_DVBT_STATUS_RESPONSE_IF_AGC_MASK);
	api->rsp->dvbt_status.mse_info			= (( ( (rspByteBuffer[3]  ) | (rspByteBuffer[2]  << 8 )) >> DEMOD_DD_DVBT_STATUS_RESPONSE_MSE_INFO_LSB  ) & DEMOD_DD_DVBT_STATUS_RESPONSE_MSE_INFO_MASK) ;
	api->rsp->dvbt_status.ber				= (( ( (rspByteBuffer[6]  ) | (rspByteBuffer[5] <<8 ) | (rspByteBuffer[4]  << 16 )) >> DEMOD_DD_DVBT_STATUS_RESPONSE_BER_LSB      ) & DEMOD_DD_DVBT_STATUS_RESPONSE_BER_MASK);
	api->rsp->dvbt_status.cfo				= (( ( (rspByteBuffer[9]  ) | (rspByteBuffer[8]  << 8 ) | (rspByteBuffer[7]  << 16 )) >> DEMOD_DD_DVBT_STATUS_RESPONSE_CFO_LSB     ) & DEMOD_DD_DVBT_STATUS_RESPONSE_CFO_MASK     );
	api->rsp->dvbt_status.op_mode			= ((rspByteBuffer[10] >> DEMOD_DD_DVBT_STATUS_RESPONSE_OP_MODE_LSB        ) & DEMOD_DD_DVBT_STATUS_RESPONSE_OP_MODE_MASK        );
	api->rsp->dvbt_status.pe				= ((rspByteBuffer[11] >> DEMOD_DD_DVBT_STATUS_RESPONSE_PE_LSB        ) & DEMOD_DD_DVBT_STATUS_RESPONSE_PE_MASK        );
	api->rsp->dvbt_status.spInv			= ((rspByteBuffer[12] >> DEMOD_DD_DVBT_STATUS_RESPONSE_SPECINV_LSB        ) & DEMOD_DD_DVBT_STATUS_RESPONSE_SPECINV_MASK        );
	api->rsp->dvbt_status.fft_mode    		= ((rspByteBuffer[12] >> DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_LSB      ) & DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_MASK      );
	api->rsp->dvbt_status.gi				= ((rspByteBuffer[12] >> DEMOD_DD_DVBT_STATUS_RESPONSE_GI_LSB     ) & DEMOD_DD_DVBT_STATUS_RESPONSE_GI_MASK     );
	api->rsp->dvbt_status.tps_length		= ((rspByteBuffer[13] >> DEMOD_DD_DVBT_STATUS_RESPONSE_TPS_LENGTH_LSB    ) & DEMOD_DD_DVBT_STATUS_RESPONSE_TPS_LENGTH_MASK);
	api->rsp->dvbt_status.cell_id			= (( ( (rspByteBuffer[15]  ) |(rspByteBuffer[14]  << 8 )) >> DEMOD_DD_DVBT_STATUS_RESPONSE_CELL_ID_LSB      ) & DEMOD_DD_DVBT_STATUS_RESPONSE_CELL_ID_MASK);
	api->rsp->dvbt_status.hierarchy			= ((rspByteBuffer[16] >> DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_LSB     ) & DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_MASK     );
	api->rsp->dvbt_status.constellation		= ((rspByteBuffer[16] >> DEMOD_DD_DVBT_STATUS_RESPONSE_CONSTELLATION_LSB        ) & DEMOD_DD_DVBT_STATUS_RESPONSE_CONSTELLATION_MASK        );
	api->rsp->dvbt_status.hp_cr			= ((rspByteBuffer[17] >> DEMOD_DD_DVBT_STATUS_RESPONSE_HP_CR_LSB       ) & DEMOD_DD_DVBT_STATUS_RESPONSE_HP_CR_MASK       );
	api->rsp->dvbt_status.lp_cr			= ((rspByteBuffer[17] >> DEMOD_DD_DVBT_STATUS_RESPONSE_LP_CR_LSB       ) & DEMOD_DD_DVBT_STATUS_RESPONSE_LP_CR_MASK       );
	api->rsp->dvbt_status.hierarchy_sel		= ((rspByteBuffer[17] >> DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_SEL_LSB     ) & DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_SEL_MASK     );
	api->rsp->dvbt_status.sfo				= (( ( (rspByteBuffer[20]  ) | (rspByteBuffer[19]  << 8 ) | (rspByteBuffer[18]  << 16 )) >> DEMOD_DD_DVBT_STATUS_RESPONSE_SFO_LSB     ) & DEMOD_DD_DVBT_STATUS_RESPONSE_SFO_MASK     );
	api->rsp->dvbt_status.lock_carr			= ((rspByteBuffer[21] >> DEMOD_DD_DVBT_STATUS_RESPONSE_LOCK_CARR_LSB         ) & DEMOD_DD_DVBT_STATUS_RESPONSE_LOCK_CARR_MASK         );
	api->rsp->dvbt_status.lock_fec			= ((rspByteBuffer[21] >> DEMOD_DD_DVBT_STATUS_RESPONSE_LOCK_FEC_LSB      ) & DEMOD_DD_DVBT_STATUS_RESPONSE_LOCK_FEC_MASK      );
	api->rsp->dvbt_status.mse_info_demod		= (( ( (rspByteBuffer[23]  ) | (rspByteBuffer[22] << 8)) >> DEMOD_DD_DVBT_STATUS_RESPONSE_MSE_INFO_DEMOD_LSB      ) & DEMOD_DD_DVBT_STATUS_RESPONSE_MSE_INFO_DEMOD_MASK      );

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_DVBT_STATUS_CMD */


#ifdef DEMOD_DD_ISDBT_STATUS_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_ISDBT_Status.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_GET_DD_ISDBT_Status(LX_DEMOD_L1_Context *api)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[20]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;
//	UINT8 rdData[3]={0,};
	UINT8 rdData1=0, rdData2=0, rdData3=0, rdData4=0, rdData5=0, rdData6=0;

	DEMOD_L0_LockDevice();

	rspByte=20;
	cmdByte=1;
	cmdByteBuffer[0] =	DEMOD_DD_ISDBT_STATUS_CMD;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_ISDBT_Status ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	api->rsp->isdbt_status.if_agc			= (( ( (rspByteBuffer[1]  ) |(rspByteBuffer[0]	<< 8 )) >> DEMOD_DD_ISDBT_STATUS_RESPONSE_IF_AGC_LSB	  ) & DEMOD_DD_ISDBT_STATUS_RESPONSE_IF_AGC_MASK);
	api->rsp->isdbt_status.mse_info 		= (( ( (rspByteBuffer[3]  ) | (rspByteBuffer[2]  << 8 )) >> DEMOD_DD_ISDBT_STATUS_RESPONSE_MSE_INFO_LSB  ) & DEMOD_DD_ISDBT_STATUS_RESPONSE_MSE_INFO_MASK) ;
	api->rsp->isdbt_status.ber				= (( ( (rspByteBuffer[6]  ) | (rspByteBuffer[5] <<8 ) | (rspByteBuffer[4]  << 16 )) >> DEMOD_DD_ISDBT_STATUS_RESPONSE_BER_LSB	   ) & DEMOD_DD_ISDBT_STATUS_RESPONSE_BER_MASK);
	api->rsp->isdbt_status.cfo				= (( ( (rspByteBuffer[9]  ) | (rspByteBuffer[8]  << 8 ) | (rspByteBuffer[7]  << 16 )) >> DEMOD_DD_ISDBT_STATUS_RESPONSE_CFO_LSB 	) & DEMOD_DD_ISDBT_STATUS_RESPONSE_CFO_MASK 	);
	api->rsp->isdbt_status.op_mode			= ((rspByteBuffer[10] >> DEMOD_DD_ISDBT_STATUS_RESPONSE_OP_MODE_LSB 	   ) & DEMOD_DD_ISDBT_STATUS_RESPONSE_OP_MODE_MASK		  );
	api->rsp->isdbt_status.pe				= ((rspByteBuffer[11] >> DEMOD_DD_ISDBT_STATUS_RESPONSE_PE_LSB		  ) & DEMOD_DD_ISDBT_STATUS_RESPONSE_PE_MASK		);
	api->rsp->isdbt_status.spInv			= ((rspByteBuffer[12] >> DEMOD_DD_ISDBT_STATUS_RESPONSE_SPECINV_LSB 	   ) & DEMOD_DD_ISDBT_STATUS_RESPONSE_SPECINV_MASK		  );
	api->rsp->isdbt_status.sfo				= (( ( (rspByteBuffer[15]  ) | (rspByteBuffer[14]  << 8 ) | (rspByteBuffer[13]	<< 16 )) >> DEMOD_DD_ISDBT_STATUS_RESPONSE_SFO_LSB	   ) & DEMOD_DD_ISDBT_STATUS_RESPONSE_SFO_MASK	   );
	api->rsp->isdbt_status.lock_carr			=	((rspByteBuffer[16]  >> DEMOD_DD_ISDBT_STATUS_RESPONSE_LOCK_CARR_LSB		 ) & DEMOD_DD_ISDBT_STATUS_RESPONSE_LOCK_CARR_MASK		   );
	api->rsp->isdbt_status.lock_fec 		=	((rspByteBuffer[16]  >> DEMOD_DD_ISDBT_STATUS_RESPONSE_LOCK_FEC_LSB 	 ) & DEMOD_DD_ISDBT_STATUS_RESPONSE_LOCK_FEC_MASK	   );
	if(api->i2c->chipVer >= M16P3)
	{
		api->rsp->isdbt_status.mse_info_demod		= (( ( (rspByteBuffer[18]  ) | (rspByteBuffer[17] << 8)) >> DEMOD_DD_ISDBT_STATUS_RESPONSE_MSE_INFO_DEMOD_LSB      ) & DEMOD_DD_ISDBT_STATUS_RESPONSE_MSE_INFO_DEMOD_MASK      );
	}
	else if(api->i2c->chipVer < L18F)
	{
		err |= DEMOD_L0_ReadCommandBytes(api->i2c, 0x709c, 1, &rdData1);
		if(err == NO_DEMOD_ERROR)
		{
			api->rsp->isdbt_status.pe		= ((rdData1 >> DEMOD_DD_ISDBT_STATUS_RESPONSE_PE_LSB		) & DEMOD_DD_ISDBT_STATUS_RESPONSE_PE_MASK		  );
		}

		err |= DEMOD_L0_ReadCommandBytes(api->i2c, 0x7095, 1, &rdData2);
		err |= DEMOD_L0_ReadCommandBytes(api->i2c, 0x7096, 1, &rdData3);
		err |= DEMOD_L0_ReadCommandBytes(api->i2c, 0x7097, 1, &rdData4);

		if(err == NO_DEMOD_ERROR)
		{
			api->rsp->isdbt_status.ber		= (( ( rdData4 | (rdData3 <<8 ) | (rdData2	<< 16 )) >> DEMOD_DD_ISDBT_STATUS_RESPONSE_BER_LSB		) & DEMOD_DD_ISDBT_STATUS_RESPONSE_BER_MASK);
		}

		err |= DEMOD_L0_ReadCommandBytes(api->i2c, 0x7093, 1, &rdData5);
		err |= DEMOD_L0_ReadCommandBytes(api->i2c, 0x7094, 1, &rdData6);

		if(err == NO_DEMOD_ERROR)
		{
			api->rsp->isdbt_status.mse_info		= (( ( rdData6 | (rdData5  << 8 )) >> DEMOD_DD_ISDBT_STATUS_RESPONSE_MSE_INFO_LSB  ) & DEMOD_DD_ISDBT_STATUS_RESPONSE_MSE_INFO_MASK) ;
		}
	}

	//printk("***wh***	isdbt_status.pe = 0x%x\n", api->rsp->isdbt_status.pe);
	//printk("***wh***	isdbt_status.ber = 0x%x\n", api->rsp->isdbt_status.ber);

	DEMOD_L0_UnlockDevice();
	return err;
}

#endif /* DEMOD_DD_ISDBT_STATUS_CMD */


#ifdef DEMOD_DD_ISDBT_TMCC_INFO_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_ISDBT_TMCC_Info.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_GET_DD_ISDBT_TMCC_Info(LX_DEMOD_L1_Context *api)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[8]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	rspByte=7;
	cmdByte=1;
	cmdByteBuffer[0] =  DEMOD_DD_ISDBT_TMCC_INFO_CMD;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_ISDBT_TMCC_Info ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	api->rsp->isdbt_tmcc_info.fft_mode    		= ((rspByteBuffer[0]  >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_FFT_MODE_LSB      ) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_FFT_MODE_MASK      );
	api->rsp->isdbt_tmcc_info.gi				= ((rspByteBuffer[0]  >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_LSB     ) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_MASK     );
	api->rsp->isdbt_tmcc_info.oqama      		=   (( ( (rspByteBuffer[1]  )) >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OQAMA_LSB      ) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OQAMA_MASK      );
	api->rsp->isdbt_tmcc_info.ocra    	  		=   (( ( (rspByteBuffer[1]  )) >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OCRA_LSB      ) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OCRA_MASK      );
	api->rsp->isdbt_tmcc_info.oila    	  		=   (( ( (rspByteBuffer[2]  )) >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OILA_LSB      ) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OILA_MASK      );
	api->rsp->isdbt_tmcc_info.onsega     		=   (( ( (rspByteBuffer[2]  )) >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_ONSEGA_LSB      ) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_ONSEGA_MASK      );
	api->rsp->isdbt_tmcc_info.oqamb      		=   (( ( (rspByteBuffer[3]  )) >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OQAMB_LSB      ) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OQAMB_MASK      );
	api->rsp->isdbt_tmcc_info.ocrb     			=   (( ( (rspByteBuffer[3]  )) >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OCRB_LSB      ) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OCRB_MASK      );
	api->rsp->isdbt_tmcc_info.oilb      			=   (( ( (rspByteBuffer[4]  )) >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OILB_LSB      ) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OILB_MASK      );
	api->rsp->isdbt_tmcc_info.onsegb     		=   (( ( (rspByteBuffer[4]  )) >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_ONSEGA_LSB      ) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_ONSEGA_MASK      );
	api->rsp->isdbt_tmcc_info.oqamc      		=   (( ( (rspByteBuffer[5]  )) >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OQAMC_LSB      ) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OQAMC_MASK      );
	api->rsp->isdbt_tmcc_info.ocrc      			=   (( ( (rspByteBuffer[5]  )) >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OCRC_LSB      ) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OCRC_MASK      );
	api->rsp->isdbt_tmcc_info.oilc      			=   (( ( (rspByteBuffer[6]  )) >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OILC_LSB      ) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OILC_MASK      );
	api->rsp->isdbt_tmcc_info.onsegc     			=   (( ( (rspByteBuffer[6]  )) >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_ONSEGC_LSB      ) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_ONSEGC_MASK      );

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_ISDBT_STATUS_CMD */


#ifdef DEMOD_DD_DVBC_STATUS_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_DVBC_Status.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_GET_DD_DVBC_Status(LX_DEMOD_L1_Context *api)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[20]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	rspByte=19;
	cmdByte=1;
	cmdByteBuffer[0] =  DEMOD_DD_DVBC_STATUS_CMD;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_DVBC_Status ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	api->rsp->dvbc_status.if_agc			= (( ( (rspByteBuffer[1]  ) |(rspByteBuffer[0]  << 8 )) >> DEMOD_DD_DVBC_STATUS_RESPONSE_IF_AGC_LSB      ) & DEMOD_DD_DVBC_STATUS_RESPONSE_IF_AGC_MASK);
	api->rsp->dvbc_status.mse_info			= (( ( (rspByteBuffer[3]  ) | (rspByteBuffer[2]  << 8 )) >> DEMOD_DD_DVBC_STATUS_RESPONSE_MSE_INFO_LSB  ) & DEMOD_DD_DVBC_STATUS_RESPONSE_MSE_INFO_MASK) ;
	api->rsp->dvbc_status.ber				= (( ( (rspByteBuffer[6]  ) | (rspByteBuffer[5] <<8 ) | (rspByteBuffer[4]  << 16 )) >> DEMOD_DD_DVBC_STATUS_RESPONSE_BER_LSB      ) & DEMOD_DD_DVBC_STATUS_RESPONSE_BER_MASK);
	api->rsp->dvbc_status.cfo				= (( ( (rspByteBuffer[9]  ) | (rspByteBuffer[8]  << 8 ) | (rspByteBuffer[7]  << 16 )) >> DEMOD_DD_DVBC_STATUS_RESPONSE_CFO_LSB     ) & DEMOD_DD_DVBC_STATUS_RESPONSE_CFO_MASK     );
	api->rsp->dvbc_status.op_mode			= ((rspByteBuffer[10] >> DEMOD_DD_DVBC_STATUS_RESPONSE_OP_MODE_LSB        ) & DEMOD_DD_DVBC_STATUS_RESPONSE_OP_MODE_MASK        );
	api->rsp->dvbc_status.pe				= ((rspByteBuffer[11] >> DEMOD_DD_DVBC_STATUS_RESPONSE_PE_LSB        ) & DEMOD_DD_DVBC_STATUS_RESPONSE_PE_MASK        );
	api->rsp->dvbc_status.spInv			= ((rspByteBuffer[12] >> DEMOD_DD_DVBC_STATUS_RESPONSE_SPECINV_LSB        ) & DEMOD_DD_DVBC_STATUS_RESPONSE_SPECINV_MASK        );
	api->rsp->dvbc_status.constellation		= ((rspByteBuffer[12] >> DEMOD_DD_DVBC_STATUS_RESPONSE_CONSTELLATION_LSB        ) & DEMOD_DD_DVBC_STATUS_RESPONSE_CONSTELLATION_MASK        );
	api->rsp->dvbc_status.sym_rate      		= ((((rspByteBuffer[14]  ) | (rspByteBuffer[13]  << 8 )) >> DEMOD_DD_DVBC_STATUS_RESPONSE_SYM_RATE_LSB      ) & DEMOD_DD_DVBC_STATUS_RESPONSE_SYM_RATE_MASK);
	api->rsp->dvbc_status.sfo				= (( ( (rspByteBuffer[17]  ) | (rspByteBuffer[16]  << 8 ) | (rspByteBuffer[15]  << 16 )) >> DEMOD_DD_DVBC_STATUS_RESPONSE_SFO_LSB     ) & DEMOD_DD_DVBC_STATUS_RESPONSE_SFO_MASK     );
	api->rsp->dvbc_status.lock_carr			=  ((rspByteBuffer[18]   >> DEMOD_DD_DVBC_STATUS_RESPONSE_LOCK_CARR_LSB         ) & DEMOD_DD_DVBC_STATUS_RESPONSE_LOCK_CARR_MASK         );
	api->rsp->dvbc_status.lock_fec			=  (( rspByteBuffer[18]   >> DEMOD_DD_DVBC_STATUS_RESPONSE_LOCK_FEC_LSB      ) & DEMOD_DD_DVBC_STATUS_RESPONSE_LOCK_FEC_MASK      );

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_DVBC_STATUS_CMD */


#ifdef DEMOD_DD_DVBC2_STATUS_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_DVBC2_Status.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_GET_DD_DVBC2_Status(LX_DEMOD_L1_Context *api)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[20]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	rspByte=18;
	cmdByte=1;
	cmdByteBuffer[0] =  DEMOD_DD_DVBC2_STATUS_CMD;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_DVBC2_Status ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	api->rsp->dvbc2_status.if_agc			= (((( ( (rspByteBuffer[1]  ) | (rspByteBuffer[0]  << 8 )) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_IF_AGC_LSB      ) & DEMOD_DD_DVBC2_STATUS_RESPONSE_IF_AGC_MASK) <<DEMOD_DD_DVBC2_STATUS_RESPONSE_IF_AGC_SHIFT ) >>DEMOD_DD_DVBC2_STATUS_RESPONSE_IF_AGC_SHIFT  );
	api->rsp->dvbc2_status.mse_info		= (((( ( (rspByteBuffer[3]  ) | (rspByteBuffer[2]  << 8 )) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_MSE_INFO_LSB      ) & DEMOD_DD_DVBC2_STATUS_RESPONSE_MSE_INFO_MASK) <<DEMOD_DD_DVBC2_STATUS_RESPONSE_MSE_INFO_SHIFT ) >>DEMOD_DD_DVBC2_STATUS_RESPONSE_MSE_INFO_SHIFT  );
	api->rsp->dvbc2_status.ber			= (((( ( (rspByteBuffer[5]  ) | (rspByteBuffer[4]  << 8 )) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_BER_LSB      ) & DEMOD_DD_DVBC2_STATUS_RESPONSE_BER_MASK) <<DEMOD_DD_DVBC2_STATUS_RESPONSE_BER_SHIFT ) >>DEMOD_DD_DVBC2_STATUS_RESPONSE_BER_SHIFT  );
	api->rsp->dvbc2_status.cfo				=   (( ( (rspByteBuffer[9]  ) | (rspByteBuffer[8]  << 8 ) | (rspByteBuffer[7]  << 16 ) | (rspByteBuffer[6]  << 24 )) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_CFO_LSB     ) & DEMOD_DD_DVBC2_STATUS_RESPONSE_CFO_MASK     );
	api->rsp->dvbc2_status.op_mode		=   (( ( (rspByteBuffer[10] )) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_OP_MODE_LSB        ) & DEMOD_DD_DVBC2_STATUS_RESPONSE_OP_MODE_MASK        );
	api->rsp->dvbc2_status.pe				=   (( ( (rspByteBuffer[11] )) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_PE_LSB        ) & DEMOD_DD_DVBC2_STATUS_RESPONSE_PE_MASK        );
	api->rsp->dvbc2_status.constellation		=   (( ( (rspByteBuffer[12] )) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_CONSTELLATION_LSB        ) & DEMOD_DD_DVBC2_STATUS_RESPONSE_CONSTELLATION_MASK        );
	api->rsp->dvbc2_status.spInv			=   (( ( (rspByteBuffer[12] )) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_SPECINV_LSB        ) & DEMOD_DD_DVBC2_STATUS_RESPONSE_SPECINV_MASK        );
	api->rsp->dvbc2_status.lock_tr			=   (( ( (rspByteBuffer[13]  )) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_LOCK_TR_LSB        ) & DEMOD_DD_DVBC2_STATUS_RESPONSE_LOCK_TR_MASK        );
	api->rsp->dvbc2_status.lock_carr		=   (( ( (rspByteBuffer[13]  )) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_LOCK_CARR_LSB         ) & DEMOD_DD_DVBC2_STATUS_RESPONSE_LOCK_CARR_MASK         );
	api->rsp->dvbc2_status.lock_psync		=   (( ( (rspByteBuffer[13]  )) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_LOCK_PSYNC_LSB        ) & DEMOD_DD_DVBC2_STATUS_RESPONSE_LOCK_PSYNC_MASK        );
	api->rsp->dvbc2_status.lock_fec		=   (( ( (rspByteBuffer[13]  )) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_LOCK_FEC_LSB      ) & DEMOD_DD_DVBC2_STATUS_RESPONSE_LOCK_FEC_MASK      );
	api->rsp->dvbc2_status.neverlock		=   (( ( (rspByteBuffer[13]  )) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_NEVERLOCK_LSB        ) & DEMOD_DD_DVBC2_STATUS_RESPONSE_NEVERLOCK_MASK        );
	api->rsp->dvbc2_status.cr    			=   (( ( (rspByteBuffer[14] )) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_CR_LSB     ) & DEMOD_DD_DVBC2_STATUS_RESPONSE_CR_MASK     );
	api->rsp->dvbc2_status.current_plp_id	=   (( ( (rspByteBuffer[15] )) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_CURRENT_PLP_ID_LSB        ) & DEMOD_DD_DVBC2_STATUS_RESPONSE_CURRENT_PLP_ID_MASK        );
	api->rsp->dvbc2_status.start_plp_id		=   (( ( (rspByteBuffer[16] )) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_START_PLP_ID_LSB        ) & DEMOD_DD_DVBC2_STATUS_RESPONSE_START_PLP_ID_MASK        );
	api->rsp->dvbc2_status.multi_plp_id		=   (( ( (rspByteBuffer[17] )) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_MULTI_PLP_ID_LSB        ) & DEMOD_DD_DVBC2_STATUS_RESPONSE_MULTI_PLP_ID_MASK        );

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_DVBC2_STATUS_CMD */


#ifdef DEMOD_DD_DTMB_STATUS_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_DTMB_Status.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_GET_DD_DTMB_Status(LX_DEMOD_L1_Context *api)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[20]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	rspByte=20;
	cmdByte=1;
	cmdByteBuffer[0] =  DEMOD_DD_DTMB_STATUS_CMD;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_DVBS_Status ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	api->rsp->dtmb_status.if_agc			= (( ( (rspByteBuffer[1]  ) |(rspByteBuffer[0]  << 8 )) >> DEMOD_DD_DTMB_STATUS_RESPONSE_IF_AGC_LSB      ) & DEMOD_DD_DTMB_STATUS_RESPONSE_IF_AGC_MASK);
	api->rsp->dtmb_status.mse_info			= (( ( (rspByteBuffer[3]  ) | (rspByteBuffer[2]  << 8 )) >> DEMOD_DD_DTMB_STATUS_RESPONSE_MSE_INFO_LSB  ) & DEMOD_DD_DTMB_STATUS_RESPONSE_MSE_INFO_MASK) ;
	api->rsp->dtmb_status.ber				= (( ( (rspByteBuffer[6]  ) | (rspByteBuffer[5] <<8 ) | (rspByteBuffer[4]  << 16 )) >> DEMOD_DD_DTMB_STATUS_RESPONSE_BER_LSB      ) & DEMOD_DD_DTMB_STATUS_RESPONSE_BER_MASK);
	api->rsp->dtmb_status.cfo				= (( ( (rspByteBuffer[9]  ) | (rspByteBuffer[8]  << 8 ) | (rspByteBuffer[7]  << 16 )) >> DEMOD_DD_DTMB_STATUS_RESPONSE_CFO_LSB     ) & DEMOD_DD_DTMB_STATUS_RESPONSE_CFO_MASK     );
	api->rsp->dtmb_status.op_mode			= ((rspByteBuffer[10] >> DEMOD_DD_DTMB_STATUS_RESPONSE_OP_MODE_LSB        ) & DEMOD_DD_DTMB_STATUS_RESPONSE_OP_MODE_MASK        );
	api->rsp->dtmb_status.pe				= ((rspByteBuffer[11] >> DEMOD_DD_DTMB_STATUS_RESPONSE_PE_LSB        ) & DEMOD_DD_DTMB_STATUS_RESPONSE_PE_MASK        );
	api->rsp->dtmb_status.spInv				= ((rspByteBuffer[12] >> DEMOD_DD_DTMB_STATUS_RESPONSE_SPECINV_LSB        ) & DEMOD_DD_DTMB_STATUS_RESPONSE_SPECINV_MASK        );
	api->rsp->dtmb_status.sfo				= (( ( (rspByteBuffer[15]  ) | (rspByteBuffer[14]  << 8 ) | (rspByteBuffer[13]  << 16 )) >> DEMOD_DD_DTMB_STATUS_RESPONSE_SFO_LSB     ) & DEMOD_DD_DTMB_STATUS_RESPONSE_SFO_MASK     );
	api->rsp->dtmb_status.il_mode			= ((rspByteBuffer[16]  >> DEMOD_DD_DTMB_STATUS_RESPONSE_IL_MODE_LSB         ) & DEMOD_DD_DTMB_STATUS_RESPONSE_IL_MODE_MASK         );
	api->rsp->dtmb_status.constellation		= ((rspByteBuffer[16] >> DEMOD_DD_DTMB_STATUS_RESPONSE_CONSTELLATION_LSB        ) & DEMOD_DD_DTMB_STATUS_RESPONSE_CONSTELLATION_MASK        );
	api->rsp->dtmb_status.carr_mode			= ((rspByteBuffer[17] >> DEMOD_DD_DTMB_STATUS_RESPONSE_CARR_MODE_LSB        ) & DEMOD_DD_DTMB_STATUS_RESPONSE_CARR_MODE_MASK        );
	api->rsp->dtmb_status.pn_const			= ((rspByteBuffer[17] >> DEMOD_DD_DTMB_STATUS_RESPONSE_PN_CONST_LSB        ) & DEMOD_DD_DTMB_STATUS_RESPONSE_PN_CONST_MASK        );
	api->rsp->dtmb_status.pn_mode			= ((rspByteBuffer[17] >> DEMOD_DD_DTMB_STATUS_RESPONSE_PN_MODE_LSB        ) & DEMOD_DD_DTMB_STATUS_RESPONSE_PN_MODE_MASK        );
	api->rsp->dtmb_status.cr				= ((rspByteBuffer[17]  >> DEMOD_DD_DTMB_STATUS_RESPONSE_CR_LSB         ) & DEMOD_DD_DTMB_STATUS_RESPONSE_CR_MASK         );
	api->rsp->dtmb_status.lock_carr			= ((rspByteBuffer[18]  >> DEMOD_DD_DTMB_STATUS_RESPONSE_LOCK_CARR_LSB         ) & DEMOD_DD_DTMB_STATUS_RESPONSE_LOCK_CARR_MASK         );
	api->rsp->dtmb_status.lock_fec			= ((rspByteBuffer[18]  >> DEMOD_DD_DTMB_STATUS_RESPONSE_LOCK_FEC_LSB      ) & DEMOD_DD_DTMB_STATUS_RESPONSE_LOCK_FEC_MASK      );

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_DTMB_STATUS_CMD */


#ifdef DEMOD_DD_DISEQC_STATUS_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_DISEQC_Status.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_GET_DD_DISEQC_Status(LX_DEMOD_L1_Context *api)
{
	//TO DO
	return NO_DEMOD_ERROR;
}
#endif /*DEMOD_DD_DISEQC_STATUS_CMD*/


#ifdef DEMOD_DD_DVBS_STATUS_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_DVBS_Status.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_GET_DD_DVBS_Status(LX_DEMOD_L1_Context *api)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[20]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	rspByte=20;
	cmdByte=1;
	cmdByteBuffer[0] =  DEMOD_DD_DVBS_STATUS_CMD;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_DVBS_Status ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	api->rsp->dvbs_status.if_agc			= (( ( (rspByteBuffer[1]  ) |(rspByteBuffer[0]  << 8 )) >> DEMOD_DD_DVBS_STATUS_RESPONSE_IF_AGC_LSB      ) & DEMOD_DD_DVBS_STATUS_RESPONSE_IF_AGC_MASK);
	api->rsp->dvbs_status.mse_info			= (( ( (rspByteBuffer[3]  ) | (rspByteBuffer[2]  << 8 )) >> DEMOD_DD_DVBS_STATUS_RESPONSE_MSE_INFO_LSB  ) & DEMOD_DD_DVBS_STATUS_RESPONSE_MSE_INFO_MASK) ;
	api->rsp->dvbs_status.ber				= (( ( (rspByteBuffer[6]  ) | (rspByteBuffer[5] <<8 ) | (rspByteBuffer[4]  << 16 )) >> DEMOD_DD_DVBS_STATUS_RESPONSE_BER_LSB      ) & DEMOD_DD_DVBS_STATUS_RESPONSE_BER_MASK);
	api->rsp->dvbs_status.cfo				= (( ( (rspByteBuffer[9]  ) | (rspByteBuffer[8]  << 8 ) | (rspByteBuffer[7]  << 16 )) >> DEMOD_DD_DVBS_STATUS_RESPONSE_CFO_LSB     ) & DEMOD_DD_DVBS_STATUS_RESPONSE_CFO_MASK     );
	api->rsp->dvbs_status.op_mode			= ((rspByteBuffer[10] >> DEMOD_DD_DVBS_STATUS_RESPONSE_OP_MODE_LSB        ) & DEMOD_DD_DVBS_STATUS_RESPONSE_OP_MODE_MASK        );
	api->rsp->dvbs_status.pe				= ((rspByteBuffer[11] >> DEMOD_DD_DVBS_STATUS_RESPONSE_PE_LSB        ) & DEMOD_DD_DVBS_STATUS_RESPONSE_PE_MASK        );
	api->rsp->dvbs_status.spInv			= ((rspByteBuffer[12] >> DEMOD_DD_DVBS_STATUS_RESPONSE_SPECINV_LSB        ) & DEMOD_DD_DVBS_STATUS_RESPONSE_SPECINV_MASK        );
	api->rsp->dvbs_status.constellation		= ((rspByteBuffer[12] >> DEMOD_DD_DVBS_STATUS_RESPONSE_CONSTELLATION_LSB        ) & DEMOD_DD_DVBS_STATUS_RESPONSE_CONSTELLATION_MASK        );
	api->rsp->dvbs_status.sym_rate     	 	= ((( (rspByteBuffer[14]  ) | (rspByteBuffer[13]  << 8 )) >> DEMOD_DD_DVBS_STATUS_RESPONSE_SYM_RATE_LSB      ) & DEMOD_DD_DVBS_STATUS_RESPONSE_SYM_RATE_MASK);
	api->rsp->dvbs_status.sfo				= (( ( (rspByteBuffer[17]  ) | (rspByteBuffer[16]  << 8 ) | (rspByteBuffer[15]  << 16 )) >> DEMOD_DD_DVBS_STATUS_RESPONSE_SFO_LSB     ) & DEMOD_DD_DVBS_STATUS_RESPONSE_SFO_MASK     );
	api->rsp->dvbs_status.cr				= ((rspByteBuffer[18]  >> DEMOD_DD_DVBS_STATUS_RESPONSE_CR_LSB         ) & DEMOD_DD_DVBS_STATUS_RESPONSE_CR_MASK         );
	api->rsp->dvbs_status.lock_carr			= ((rspByteBuffer[19]  >> DEMOD_DD_DVBS_STATUS_RESPONSE_LOCK_CARR_LSB         ) & DEMOD_DD_DVBS_STATUS_RESPONSE_LOCK_CARR_MASK         );
	api->rsp->dvbs_status.lock_fec			= ((rspByteBuffer[19]  >> DEMOD_DD_DVBS_STATUS_RESPONSE_LOCK_FEC_LSB      ) & DEMOD_DD_DVBS_STATUS_RESPONSE_LOCK_FEC_MASK      );

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_DVBS_STATUS_CMD */


#ifdef DEMOD_DD_DVBS2_STATUS_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_DVBS2_Status.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_GET_DD_DVBS2_Status(LX_DEMOD_L1_Context *api)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[20]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	rspByte=20;
	cmdByte=1;
	cmdByteBuffer[0] =  DEMOD_DD_DVBS2_STATUS_CMD;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_DVBS2_Status ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	api->rsp->dvbs2_status.if_agc			= (( ( (rspByteBuffer[1]  ) |(rspByteBuffer[0]  << 8 )) >> DEMOD_DD_DVBS2_STATUS_RESPONSE_IF_AGC_LSB      ) & DEMOD_DD_DVBS2_STATUS_RESPONSE_IF_AGC_MASK);
	api->rsp->dvbs2_status.mse_info		= (( ( (rspByteBuffer[3]  ) | (rspByteBuffer[2]  << 8 )) >> DEMOD_DD_DVBS2_STATUS_RESPONSE_MSE_INFO_LSB  ) & DEMOD_DD_DVBS2_STATUS_RESPONSE_MSE_INFO_MASK) ;
	api->rsp->dvbs2_status.ber			= (( ( (rspByteBuffer[6]  ) | (rspByteBuffer[5] <<8 ) | (rspByteBuffer[4]  << 16 )) >> DEMOD_DD_DVBS2_STATUS_RESPONSE_BER_LSB      ) & DEMOD_DD_DVBS2_STATUS_RESPONSE_BER_MASK);
	api->rsp->dvbs2_status.cfo				= (( ( (rspByteBuffer[9]  ) | (rspByteBuffer[8]  << 8 ) | (rspByteBuffer[7]  << 16 )) >> DEMOD_DD_DVBS2_STATUS_RESPONSE_CFO_LSB     ) & DEMOD_DD_DVBS2_STATUS_RESPONSE_CFO_MASK     );
	api->rsp->dvbs2_status.op_mode		= ((rspByteBuffer[10] >> DEMOD_DD_DVBS2_STATUS_RESPONSE_OP_MODE_LSB        ) & DEMOD_DD_DVBS2_STATUS_RESPONSE_OP_MODE_MASK        );
	api->rsp->dvbs2_status.pe				= ((rspByteBuffer[11] >> DEMOD_DD_DVBS2_STATUS_RESPONSE_PE_LSB        ) & DEMOD_DD_DVBS2_STATUS_RESPONSE_PE_MASK        );
	api->rsp->dvbs2_status.spInv			= ((rspByteBuffer[12] >> DEMOD_DD_DVBS2_STATUS_RESPONSE_SPECINV_LSB        ) & DEMOD_DD_DVBS2_STATUS_RESPONSE_SPECINV_MASK        );
	api->rsp->dvbs2_status.constellation		= ((rspByteBuffer[12] >> DEMOD_DD_DVBS2_STATUS_RESPONSE_CONSTELLATION_LSB        ) & DEMOD_DD_DVBS2_STATUS_RESPONSE_CONSTELLATION_MASK        );
	api->rsp->dvbs2_status.sym_rate      	= ((( (rspByteBuffer[14]  ) | (rspByteBuffer[13]  << 8 )) >> DEMOD_DD_DVBS2_STATUS_RESPONSE_SYM_RATE_LSB      ) & DEMOD_DD_DVBS2_STATUS_RESPONSE_SYM_RATE_MASK);
	api->rsp->dvbs2_status.sfo				= (( ( (rspByteBuffer[17]  ) | (rspByteBuffer[16]  << 8 ) | (rspByteBuffer[15]  << 16 )) >> DEMOD_DD_DVBS2_STATUS_RESPONSE_SFO_LSB     ) & DEMOD_DD_DVBS2_STATUS_RESPONSE_SFO_MASK     );
	api->rsp->dvbs2_status.pp				= ((rspByteBuffer[18]  >> DEMOD_DD_DVBS2_STATUS_RESPONSE_PP_LSB         ) & DEMOD_DD_DVBS2_STATUS_RESPONSE_PP_MASK         );
	api->rsp->dvbs2_status.cr				= ((rspByteBuffer[18]  >> DEMOD_DD_DVBS2_STATUS_RESPONSE_CR_LSB         ) & DEMOD_DD_DVBS2_STATUS_RESPONSE_CR_MASK         );
	api->rsp->dvbs2_status.lock_carr		= ((rspByteBuffer[19]  >> DEMOD_DD_DVBS2_STATUS_RESPONSE_LOCK_CARR_LSB         ) & DEMOD_DD_DVBS2_STATUS_RESPONSE_LOCK_CARR_MASK         );
	api->rsp->dvbs2_status.lock_fec		= ((rspByteBuffer[19]  >> DEMOD_DD_DVBS2_STATUS_RESPONSE_LOCK_FEC_LSB      ) & DEMOD_DD_DVBS2_STATUS_RESPONSE_LOCK_FEC_MASK      );

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_DVBS2_STATUS_CMD */


#ifdef DEMOD_DD_LOCKTIME_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_LOCKTIME.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8 DEMOD_L1_GET_DD_LOCKTIME(LX_DEMOD_L1_Context *api)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[24]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	rspByte=24;
	cmdByte=1;
	cmdByteBuffer[0] = DEMOD_DD_LOCKTIME_CMD;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_LOCKTIME ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DBB_DUMP_PRINT("timeStamp1 : %x\n", ((rspByteBuffer[ 3] << 24) | (rspByteBuffer[ 2] << 16) | (rspByteBuffer[ 1] << 8) | rspByteBuffer[ 0]));
	DBB_DUMP_PRINT("timeStamp2 : %x\n", ((rspByteBuffer[ 7] << 24) | (rspByteBuffer[ 6] << 16) | (rspByteBuffer[ 5] << 8) | rspByteBuffer[ 4]));
	DBB_DUMP_PRINT("timeStamp3 : %x\n", ((rspByteBuffer[11] << 24) | (rspByteBuffer[10] << 16) | (rspByteBuffer[ 9] << 8) | rspByteBuffer[ 8]));
	DBB_DUMP_PRINT("timeLock1  : %x\n", ((rspByteBuffer[15] << 24) | (rspByteBuffer[14] << 16) | (rspByteBuffer[13] << 8) | rspByteBuffer[12]));
	DBB_DUMP_PRINT("timeLock2  : %x\n", ((rspByteBuffer[19] << 24) | (rspByteBuffer[18] << 16) | (rspByteBuffer[17] << 8) | rspByteBuffer[16]));
	DBB_DUMP_PRINT("timeLock3  : %x\n", ((rspByteBuffer[23] << 24) | (rspByteBuffer[22] << 16) | (rspByteBuffer[21] << 8) | rspByteBuffer[20]));

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_LOCKTIME_CMD */


#ifdef DEMOD_DD_GET_DD_SIGSRCH_NUM_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_SIGSRCH_NUM.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_GET_DD_SIGSRCH_NUM(LX_DEMOD_L1_Context *api)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	rspByte=1;
	cmdByte=1;
	cmdByteBuffer[0] =  DEMOD_DD_GET_DD_SIGSRCH_NUM_CMD;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_SIGSRCH_NUM ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	api->rsp->dd_sigsrch_num.ch_num			= ((rspByteBuffer[0]  >> DEMOD_DD_GET_DD_SIGSRCH_NUM_RESPONSE_CH_NUM_LSB         ) & DEMOD_DD_GET_DD_SIGSRCH_NUM_RESPONSE_CH_NUM_MASK         );

	DBB_PRINT("Blind search : %d found\n", api->rsp->dd_sigsrch_num.ch_num);

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_GET_DD_SIGSRCH_NUM_CMD */


#ifdef DEMOD_DD_GET_DD_SIGSRCH_INFO_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_SIGSRCH_INFO.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_GET_DD_SIGSRCH_INFO(LX_DEMOD_L1_Context *api)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[64]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	rspByte=64;
	cmdByte=1;
	cmdByteBuffer[0] =  DEMOD_DD_GET_DD_SIGSRCH_INFO_CMD;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_SIGSRCH_INFO ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

api->rsp->dd_sigsrch_info.bw_idx		= ((( (rspByteBuffer[1]  ) | (rspByteBuffer[0]  << 8 )) >> DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_BW_IDX_LSB      ) & DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_BW_IDX_MASK);
	api->rsp->dd_sigsrch_info.center_idx	= ((( (rspByteBuffer[5] ) | (rspByteBuffer[4]  << 8 ) | (rspByteBuffer[3] << 16 ) | (rspByteBuffer[2]  << 24 )) >> DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_CENTER_IDX_LSB      ) & DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_CENTER_IDX_MASK);

	
	api->rsp->blind_status.channel_num		= rspByteBuffer[6] & 0x0f;
	api->rsp->blind_status.channel_num_cnt	= (rspByteBuffer[6] >> 4) & 0x0f;
	api->rsp->blind_status.symbolFlg		= (rspByteBuffer[7] >> 4) & 0x01;

	api->rsp->blind_status.falling_idx[0]	= (rspByteBuffer[8] << 8 | rspByteBuffer[9])   ;
	api->rsp->blind_status.falling_idx[1]	= (rspByteBuffer[12] << 8 | rspByteBuffer[13]) ;
	api->rsp->blind_status.falling_idx[2]	= (rspByteBuffer[16] << 8 | rspByteBuffer[17]) ;
	api->rsp->blind_status.falling_idx[3]	= (rspByteBuffer[20] << 8 | rspByteBuffer[21]) ;
	api->rsp->blind_status.falling_idx[4]	= (rspByteBuffer[24] << 8 | rspByteBuffer[25]) ;
	api->rsp->blind_status.falling_idx[5]	= (rspByteBuffer[28] << 8 | rspByteBuffer[29]) ;
	api->rsp->blind_status.falling_idx[6]	= (rspByteBuffer[32] << 8 | rspByteBuffer[33]) ;
	api->rsp->blind_status.falling_idx[7]	= (rspByteBuffer[36] << 8 | rspByteBuffer[37]) ;
	api->rsp->blind_status.falling_idx[8]	= (rspByteBuffer[40] << 8 | rspByteBuffer[41]) ;
	api->rsp->blind_status.falling_idx[9]	= (rspByteBuffer[44] << 8 | rspByteBuffer[45]) ;
	
	api->rsp->blind_status.rising_idx[0]	= (rspByteBuffer[10] << 8 | rspByteBuffer[11]) ;
	api->rsp->blind_status.rising_idx[1]	= (rspByteBuffer[14] << 8 | rspByteBuffer[15]) ;
	api->rsp->blind_status.rising_idx[2]	= (rspByteBuffer[18] << 8 | rspByteBuffer[19]) ;
	api->rsp->blind_status.rising_idx[3]	= (rspByteBuffer[22] << 8 | rspByteBuffer[23]) ;
	api->rsp->blind_status.rising_idx[4]	= (rspByteBuffer[26] << 8 | rspByteBuffer[27]) ;
	api->rsp->blind_status.rising_idx[5]	= (rspByteBuffer[30] << 8 | rspByteBuffer[31]) ;
	api->rsp->blind_status.rising_idx[6]	= (rspByteBuffer[34] << 8 | rspByteBuffer[35]) ;
	api->rsp->blind_status.rising_idx[7]	= (rspByteBuffer[38] << 8 | rspByteBuffer[39]) ;
	api->rsp->blind_status.rising_idx[8]	= (rspByteBuffer[42] << 8 | rspByteBuffer[43]) ;
	api->rsp->blind_status.rising_idx[9]	= (rspByteBuffer[46] << 8 | rspByteBuffer[47]) ;
	
	api->rsp->blind_status.srdCnt			= (rspByteBuffer[48]>> 4)  & 0x0f;
	api->rsp->blind_status.sigsrchCnt		= rspByteBuffer[48] & 0x0f;
	api->rsp->blind_status.debug1			= rspByteBuffer[49];
	api->rsp->blind_status.debug2			= rspByteBuffer[50];
	api->rsp->blind_status.debug3			= rspByteBuffer[51];
	api->rsp->blind_status.realSnum_L		= rspByteBuffer[52] & 0x0f;
	api->rsp->blind_status.realSnum_M		= (rspByteBuffer[52]>> 4)  & 0x0f;
	api->rsp->blind_status.realSnum_H		= rspByteBuffer[53] & 0x0f;
	api->rsp->blind_status.realSnum_All 	= (rspByteBuffer[53]>> 4)  & 0x0f;
	api->rsp->blind_status.overLapEn		= rspByteBuffer[54] & 0x0f;
	api->rsp->blind_status.jumpCnt			= (rspByteBuffer[54]>> 4)  & 0x0f;
	api->rsp->blind_status.lockcheckEn		= rspByteBuffer[55] & 0x02;
	api->rsp->blind_status.clearJumpBuffer	= (rspByteBuffer[55]>> 4)  & 0x0f;
	
	api->rsp->blind_status.diffBwKhz		= (((rspByteBuffer[59] ) | (rspByteBuffer[58]  << 8 ) | (rspByteBuffer[57] << 16 ) | (rspByteBuffer[56]  << 24 )) & DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_CENTER_IDX_MASK);

	api->rsp->blind_status.siginfoStatus	= rspByteBuffer[60];
	//rspByteBuffer[61]
	api->rsp->blind_status.lowSearchEn		= rspByteBuffer[62] & 0x0f;
	api->rsp->blind_status.searchRange		= (rspByteBuffer[62]>> 4) & 0x0f;

	api->rsp->blind_status.uniCableEn		= rspByteBuffer[63] & 0x01;
	api->rsp->blind_status.uniCnt			= (rspByteBuffer[63]>> 1) & 0x03;
	api->rsp->blind_status.uniCableLockCheck= (rspByteBuffer[63]>> 4) & 0x0f;
	
#if 0
	api->rsp->blind_status.crCenter 		= (((rspByteBuffer[67] ) | (rspByteBuffer[66] << 8 ) | (rspByteBuffer[65] << 16 ) | (rspByteBuffer[64] << 24 )) & DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_CENTER_IDX_MASK);
	api->rsp->blind_status.trCenter 		= (((rspByteBuffer[71] ) | (rspByteBuffer[70] << 8 ) | (rspByteBuffer[69] << 16 ) | (rspByteBuffer[68] << 24 )) & DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_CENTER_IDX_MASK);
	
	api->rsp->blind_status.uniFreq0 		= (((rspByteBuffer[75] ) | (rspByteBuffer[74] << 8 ) | (rspByteBuffer[73] << 16 ) | (rspByteBuffer[72] << 24 )) & DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_CENTER_IDX_MASK);
	api->rsp->blind_status.uniFreqT 		= (((rspByteBuffer[79] ) | (rspByteBuffer[78] << 8 ) | (rspByteBuffer[77] << 16 ) | (rspByteBuffer[76] << 24 )) & DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_CENTER_IDX_MASK);		
	api->rsp->blind_status.ubFreqC			= (((rspByteBuffer[83] ) | (rspByteBuffer[82] << 8 ) | (rspByteBuffer[81] << 16 ) | (rspByteBuffer[80] << 24 )) & DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_CENTER_IDX_MASK);		
	api->rsp->blind_status.ubFreq			= (((rspByteBuffer[87] ) | (rspByteBuffer[86] << 8 ) | (rspByteBuffer[85] << 16 ) | (rspByteBuffer[84] << 24 )) & DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_CENTER_IDX_MASK);		
	
	api->rsp->blind_status.uniCalDone		= (rspByteBuffer[88]>> 6) & 0x03;
	api->rsp->blind_status.ubCnt			= (rspByteBuffer[88]>> 0) & 0x3f;
	api->rsp->blind_status.ubFreqStep		= (((rspByteBuffer[90]	) | (rspByteBuffer[89]	<< 8 )) & DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_BW_IDX_MASK);
	api->rsp->blind_status.ubLock			= (rspByteBuffer[91]>> 0) & 0x0f;
	api->rsp->blind_status.ubLockPre		= (rspByteBuffer[91]>> 4) & 0x0f;
	api->rsp->blind_status.uniFreq0_cfo 	= (((rspByteBuffer[95] ) | (rspByteBuffer[94] << 8 ) | (rspByteBuffer[93] << 16 ) | (rspByteBuffer[92] << 24 )) & DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_CENTER_IDX_MASK);
	api->rsp->blind_status.sigCeterKhz		= (((rspByteBuffer[99] ) | (rspByteBuffer[98] << 8 ) | (rspByteBuffer[97] << 16 ) | (rspByteBuffer[96] << 24 )) & DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_CENTER_IDX_MASK);

	api->rsp->blind_status.refCenterKhz 	= (((rspByteBuffer[103] ) | (rspByteBuffer[102] << 8 ) | (rspByteBuffer[101] << 16 ) | (rspByteBuffer[100] << 24 )) & DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_CENTER_IDX_MASK);
	api->rsp->blind_status.sig_crcenter		= (((rspByteBuffer[107] ) | (rspByteBuffer[106] << 8 ) | (rspByteBuffer[105] << 16 ) | (rspByteBuffer[104] << 24 )) & DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_CENTER_IDX_MASK);
	api->rsp->blind_status.diffBw_rIdx		= (((rspByteBuffer[109] ) | (rspByteBuffer[108] << 8 )) & DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_BW_IDX_MASK);
	api->rsp->blind_status.diffBw_fIdx		= (((rspByteBuffer[111] ) | (rspByteBuffer[110] << 8 )) & DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_BW_IDX_MASK);
	api->rsp->blind_status.realCenterKhz	= (((rspByteBuffer[115] ) | (rspByteBuffer[114] << 8 ) | (rspByteBuffer[113] << 16 ) | (rspByteBuffer[112] << 24 )) & DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_CENTER_IDX_MASK);
	api->rsp->blind_status.diffBw_bw		= (((rspByteBuffer[119] ) | (rspByteBuffer[118] << 8 ) | (rspByteBuffer[117] << 16 ) | (rspByteBuffer[116] << 24 )) & DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_CENTER_IDX_MASK);
	api->rsp->blind_status.nbw_val		 	= rspByteBuffer[120];
	//rspByteBuffer[121]
	//rspByteBuffer[122]
	//rspByteBuffer[123]

	api->rsp->blind_status.tempUpFidx		= (rspByteBuffer[125] << 8 | rspByteBuffer[124]) ;
	api->rsp->blind_status.tempUpRidx		= (rspByteBuffer[127] << 8 | rspByteBuffer[126]) ;	

#endif

	DEMOD_PRINT("\n ########## DEMOD_L1_GET_DD_SIGSRCH_INFO ########## \n\n");
	DEMOD_PRINT("DEMOD_L2_SAT_Blind_Info TunerCenterFreqKhz : %d\n", api->rsp->dd_sigsrch_info.center_idx);
	DEMOD_PRINT("DEMOD_L2_SAT_Blind_Info TunerCutOffFreqKhz : %d\n", api->rsp->dd_sigsrch_info.bw_idx);
	
	DEMOD_PRINT("* Falling idx[0] = %d /// Rising  idx[0] = %d \n", api->rsp->blind_status.falling_idx[0], api->rsp->blind_status.rising_idx[0]);
	DEMOD_PRINT("* Falling idx[1] = %d /// Rising  idx[1] = %d \n", api->rsp->blind_status.falling_idx[1], api->rsp->blind_status.rising_idx[1]);
	DEMOD_PRINT("* Falling idx[2] = %d /// Rising  idx[2] = %d \n", api->rsp->blind_status.falling_idx[2], api->rsp->blind_status.rising_idx[2]);
	DEMOD_PRINT("* Falling idx[3] = %d /// Rising  idx[3] = %d \n", api->rsp->blind_status.falling_idx[3], api->rsp->blind_status.rising_idx[3]);
	DEMOD_PRINT("* Falling idx[4] = %d /// Rising  idx[4] = %d \n", api->rsp->blind_status.falling_idx[4], api->rsp->blind_status.rising_idx[4]);
	DEMOD_PRINT("* Falling idx[5] = %d /// Rising  idx[5] = %d \n", api->rsp->blind_status.falling_idx[5], api->rsp->blind_status.rising_idx[5]);
	DEMOD_PRINT("* Falling idx[6] = %d /// Rising  idx[6] = %d \n", api->rsp->blind_status.falling_idx[6], api->rsp->blind_status.rising_idx[6]);
	DEMOD_PRINT("* Falling idx[7] = %d /// Rising  idx[7] = %d \n", api->rsp->blind_status.falling_idx[7], api->rsp->blind_status.rising_idx[7]);
	DEMOD_PRINT("* Falling idx[8] = %d /// Rising  idx[8] = %d \n", api->rsp->blind_status.falling_idx[8], api->rsp->blind_status.rising_idx[8]);
	DEMOD_PRINT("* Falling idx[9] = %d /// Rising  idx[9] = %d \n", api->rsp->blind_status.falling_idx[9], api->rsp->blind_status.rising_idx[9]);

	DEMOD_PRINT("00 debug1 : %d // debug2 : %d // debug3 : %d \n", api->rsp->blind_status.debug1, api->rsp->blind_status.debug2, api->rsp->blind_status.debug3);
	DEMOD_PRINT("01 overLapEn %d // jumpCnt %d\n", api->rsp->blind_status.overLapEn, api->rsp->blind_status.jumpCnt);
	DEMOD_PRINT("02 sigsrchCnt %d / srdCnt %d \n", api->rsp->blind_status.sigsrchCnt, api->rsp->blind_status.srdCnt);
	DEMOD_PRINT("03 realSnum_All : %d // realSnum_L : %d // realSnum_M : %d // realSnum_H : %d\n", api->rsp->blind_status.realSnum_All, api->rsp->blind_status.realSnum_L, api->rsp->blind_status.realSnum_M, api->rsp->blind_status.realSnum_H);
	DEMOD_PRINT("04 channel_num %d // channel_num_cnt %d\n", api->rsp->blind_status.channel_num,	api->rsp->blind_status.channel_num_cnt);
	DEMOD_PRINT("05 siginfoStatus %d // symbolFlg %d \n", api->rsp->blind_status.siginfoStatus, api->rsp->blind_status.symbolFlg);
	DEMOD_PRINT("06 diffBwKhz %d // clearJumpBuffer %d\n", api->rsp->blind_status.diffBwKhz, api->rsp->blind_status.clearJumpBuffer);	
	DEMOD_PRINT("07 lockcheckEn %d // lowSearchEn %d // searchRange %d\n", api->rsp->blind_status.lockcheckEn, api->rsp->blind_status.lowSearchEn, api->rsp->blind_status.searchRange);
	DEMOD_PRINT("08 sigCeterKhz %d // refCenterKhz %d \n", api->rsp->blind_status.sigCeterKhz, api->rsp->blind_status.refCenterKhz);
	DEMOD_PRINT("09 sigCRCenterKhz 0x%08x \n", api->rsp->blind_status.sig_crcenter);		
	DEMOD_PRINT("10 diffBw_rIdx %d // diffBw_fIdx %d\n", api->rsp->blind_status.diffBw_rIdx, api->rsp->blind_status.diffBw_fIdx);
	DEMOD_PRINT("11 realCenterKhz %d // diffBwKhz bandwidth %d \n", api->rsp->blind_status.realCenterKhz, api->rsp->blind_status.diffBw_bw);
	DEMOD_PRINT("12 nbw_val %d \n", api->rsp->blind_status.nbw_val);
	DEMOD_PRINT("13 tempUpRidx %d // tempUpFidx %d\n", api->rsp->blind_status.tempUpRidx, api->rsp->blind_status.tempUpFidx);

	DEMOD_PRINT("-----Unicable-----\n");
	DEMOD_PRINT("14 uniCableEn : %d // uniCnt : %d // uniCableLockCheck : %d \n", api->rsp->blind_status.uniCableEn, api->rsp->blind_status.uniCnt, api->rsp->blind_status.uniCableLockCheck);
	
#if 0
	DEMOD_PRINT("15 UnicrCenter 0x%08x // trCenter 0x%08x\n", api->rsp->blind_status.crCenter, api->rsp->blind_status.trCenter);
	DEMOD_PRINT("16 uniFreq0 %d // uniFreqT %d\n", api->rsp->blind_status.uniFreq0, api->rsp->blind_status.uniFreqT);
	DEMOD_PRINT("17 ubFreqC %d // ubFreq %d\n", api->rsp->blind_status.ubFreqC, api->rsp->blind_status.ubFreq);
	DEMOD_PRINT("18 uniCalDone %d // ubCnt %d // ubFreqStep %d\n", api->rsp->blind_status.uniCalDone, api->rsp->blind_status.ubCnt, api->rsp->blind_status.ubFreqStep);
	DEMOD_PRINT("19 ubLock %d // ubLockPre %d\n", api->rsp->blind_status.ubLock, api->rsp->blind_status.ubLockPre);
	DEMOD_PRINT("20 uniFreq0_cfo %d \n", api->rsp->blind_status.uniFreq0_cfo);
	DEMOD_PRINT("------------------\n");
#endif

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_GET_DD_SIGSRCH_INFO_CMD */


#ifdef DEMOD_DD_BLIND_STATUS_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_BLIND_Status.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_GET_DD_BLIND_Status(LX_DEMOD_L1_Context *api)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[16]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	rspByte=16;
	cmdByte=1;
	cmdByteBuffer[0] =  DEMOD_DD_BLIND_STATUS_CMD;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_BLIND_Status ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	api->rsp->blind_status.blindStatus			= ((rspByteBuffer[0]  >> DEMOD_DD_BLIND_STATUS_RESPONSE_BLINDSTATUS_LSB        ) & DEMOD_DD_BLIND_STATUS_RESPONSE_BLINDSTATUS_MASK      );
	api->rsp->blind_status.blindDone				= ((rspByteBuffer[0]  >> DEMOD_DD_BLIND_STATUS_RESPONSE_BLINDDONE_LSB         ) & DEMOD_DD_BLIND_STATUS_RESPONSE_BLINDDONE_MASK         );
	api->rsp->blind_status.blindLock				= ((rspByteBuffer[0]  >> DEMOD_DD_BLIND_STATUS_RESPONSE_BLINDLOCK_LSB         ) & DEMOD_DD_BLIND_STATUS_RESPONSE_BLINDLOCK_MASK         );

	api->rsp->blind_status.symRate					= ((( (rspByteBuffer[2]  ) | (rspByteBuffer[1]  << 8 )) >> DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_BW_IDX_LSB      ) & DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_BW_IDX_MASK);
	api->rsp->blind_status.srdDone					= rspByteBuffer[3] & 0x03;
	api->rsp->blind_status.symbolFlg				= (rspByteBuffer[3] >> 2 ) & 0x03;
	api->rsp->blind_status.channel_num_cnt	= (rspByteBuffer[3] >> 4 ) & 0x0f;
	api->rsp->blind_status.channel_num			= rspByteBuffer[4];
	api->rsp->blind_status.resetFlag				= rspByteBuffer[5];
	api->rsp->blind_status.srdFlg						= rspByteBuffer[6];
	api->rsp->blind_status.pwrcoeDone				= rspByteBuffer[7];
	api->rsp->blind_status.specCenter				= ((( (rspByteBuffer[11] ) | (rspByteBuffer[10]  << 8 ) | (rspByteBuffer[9] << 16 ) | (rspByteBuffer[8]  << 24 )) >> DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_CENTER_IDX_LSB	   ) & DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_CENTER_IDX_MASK);

	api->rsp->blind_status.rdData1					= rspByteBuffer[12];
	api->rsp->blind_status.rdData2					= rspByteBuffer[13];

	DEMOD_PRINT("###status 00 blindStatus %d // blindLock %d // blindDone %d\n", api->rsp->blind_status.blindStatus, api->rsp->blind_status.blindLock, api->rsp->blind_status.blindDone);
	DEMOD_PRINT("###status 01 specCenter %d // symRate %d \n", api->rsp->blind_status.specCenter, api->rsp->blind_status.symRate);
	DEMOD_PRINT("###status 02 srdDone %d // srdFlg %d \n", api->rsp->blind_status.srdDone, api->rsp->blind_status.srdFlg);
	DEMOD_PRINT("###status 03 symbolFlg %d // pwrcoeDone %d\n", api->rsp->blind_status.symbolFlg, api->rsp->blind_status.pwrcoeDone);
	DEMOD_PRINT("###status 04 channel_num %d // channel_num_cnt %d // resetFlag 0x%08x\n", api->rsp->blind_status.channel_num, api->rsp->blind_status.channel_num_cnt, api->rsp->blind_status.auto_chnum_cnt);
	DEMOD_PRINT("###status 05 rdData1 %x // rdData2 %x\n", api->rsp->blind_status.rdData1, api->rsp->blind_status.rdData2);

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_BLIND_STATUS_CMD */


#ifdef DEMOD_DD_BLIND_INIT_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_BLIND_Init.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @param startFreq		[IN] UINT32
 * @param endFreq		[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_GET_DD_BLIND_Init(LX_DEMOD_L1_Context *api, UINT32 startFreq, UINT32 endFreq)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[12]={0,};
	UINT8 rspByteBuffer[12]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	cmdByte=9;
	if(api->i2c->chipVer >= L18F)
	{
		cmdByteBuffer[0] =  DEMOD_DD_BLIND_INIT_CMD;
		cmdByteBuffer[1] = (UINT8) ((( startFreq  & DEMOD_DD_BLIND_INIT_CMD_STARTFREQ_MASK     ) << DEMOD_DD_BLIND_INIT_CMD_STARTFREQ_LSB    )>>0);
		cmdByteBuffer[2] = (UINT8) ((( startFreq  & DEMOD_DD_BLIND_INIT_CMD_STARTFREQ_MASK     ) << DEMOD_DD_BLIND_INIT_CMD_STARTFREQ_LSB    )>>8);
		cmdByteBuffer[3] = (UINT8) ((( startFreq  & DEMOD_DD_BLIND_INIT_CMD_STARTFREQ_MASK     ) << DEMOD_DD_BLIND_INIT_CMD_STARTFREQ_LSB    )>>16);
		cmdByteBuffer[4] = (UINT8) ((( startFreq  & DEMOD_DD_BLIND_INIT_CMD_STARTFREQ_MASK     ) << DEMOD_DD_BLIND_INIT_CMD_STARTFREQ_LSB    )>>24);
		cmdByteBuffer[5] = (UINT8) ((( endFreq    & DEMOD_DD_BLIND_INIT_CMD_ENDFREQ_MASK     ) << DEMOD_DD_BLIND_INIT_CMD_ENDFREQ_LSB    )>>0);
		cmdByteBuffer[6] = (UINT8) ((( endFreq    & DEMOD_DD_BLIND_INIT_CMD_ENDFREQ_MASK     ) << DEMOD_DD_BLIND_INIT_CMD_ENDFREQ_LSB    )>>8);
		cmdByteBuffer[7] = (UINT8) ((( endFreq    & DEMOD_DD_BLIND_INIT_CMD_ENDFREQ_MASK     ) << DEMOD_DD_BLIND_INIT_CMD_ENDFREQ_LSB    )>>16);
		cmdByteBuffer[8] = (UINT8) ((( endFreq    & DEMOD_DD_BLIND_INIT_CMD_ENDFREQ_MASK     ) << DEMOD_DD_BLIND_INIT_CMD_ENDFREQ_LSB    )>>24);

	}
	else
	{
		cmdByteBuffer[0] =  DEMOD_DD_BLIND_INIT_CMD;
		cmdByteBuffer[1] = (UINT8) ((( startFreq  & DEMOD_DD_BLIND_INIT_CMD_STARTFREQ_MASK     ) << DEMOD_DD_BLIND_INIT_CMD_STARTFREQ_LSB    )>>24);
		cmdByteBuffer[2] = (UINT8) ((( startFreq  & DEMOD_DD_BLIND_INIT_CMD_STARTFREQ_MASK     ) << DEMOD_DD_BLIND_INIT_CMD_STARTFREQ_LSB    )>>16);
		cmdByteBuffer[3] = (UINT8) ((( startFreq  & DEMOD_DD_BLIND_INIT_CMD_STARTFREQ_MASK     ) << DEMOD_DD_BLIND_INIT_CMD_STARTFREQ_LSB    )>>8);
		cmdByteBuffer[4] = (UINT8) ( ( startFreq  & DEMOD_DD_BLIND_INIT_CMD_STARTFREQ_MASK     ) << DEMOD_DD_BLIND_INIT_CMD_STARTFREQ_LSB    );
		cmdByteBuffer[5] = (UINT8) ((( endFreq    & DEMOD_DD_BLIND_INIT_CMD_ENDFREQ_MASK     ) << DEMOD_DD_BLIND_INIT_CMD_ENDFREQ_LSB    )>>24);
		cmdByteBuffer[6] = (UINT8) ((( endFreq    & DEMOD_DD_BLIND_INIT_CMD_ENDFREQ_MASK     ) << DEMOD_DD_BLIND_INIT_CMD_ENDFREQ_LSB    )>>16);
		cmdByteBuffer[7] = (UINT8) ((( endFreq    & DEMOD_DD_BLIND_INIT_CMD_ENDFREQ_MASK     ) << DEMOD_DD_BLIND_INIT_CMD_ENDFREQ_LSB    )>>8);
		cmdByteBuffer[8] = (UINT8) ( ( endFreq    & DEMOD_DD_BLIND_INIT_CMD_ENDFREQ_MASK     ) << DEMOD_DD_BLIND_INIT_CMD_ENDFREQ_LSB    );
	}

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_BLIND_Init ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_BLIND_INIT_CMD */


#ifdef DEMOD_DD_BLIND_END_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_BLIND_End.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_GET_DD_BLIND_End(LX_DEMOD_L1_Context *api)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	cmdByte=1;
	cmdByteBuffer[0] =  DEMOD_DD_BLIND_END_CMD;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_BLIND_End ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_BLIND_INIT_CMD */


#ifdef DEMOD_DD_BLIND_FOUNDINFO_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_BLIND_FoundInfo.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_GET_DD_BLIND_FoundInfo(LX_DEMOD_L1_Context *api)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 rspByteBuffer[8]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	rspByte=7;
	cmdByte=1;
	cmdByteBuffer[0] =  DEMOD_DD_BLIND_FOUNDINFO_CMD;

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_GET_DD_BLIND_FoundInfo ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	api->rsp->blind_foundinfo.symrate		= ((( (rspByteBuffer[1]) | (rspByteBuffer[0] << 8 )) >> DEMOD_DD_BLIND_FOUNDINFO_RESPONSE_SYMRATE_LSB      ) & DEMOD_DD_BLIND_FOUNDINFO_RESPONSE_SYMRATE_MASK);
	api->rsp->blind_foundinfo.center		= ((( (rspByteBuffer[5]) | (rspByteBuffer[4] << 8 ) | (rspByteBuffer[3] << 16 ) | (rspByteBuffer[2] << 24 )) >> DEMOD_DD_BLIND_FOUNDINFO_RESPONSE_CENTER_LSB      ) & DEMOD_DD_BLIND_FOUNDINFO_RESPONSE_CENTER_MASK);//TO DO
	api->rsp->blind_status.auto_en			= rspByteBuffer[6]& 0x01;

	DEMOD_L0_UnlockDevice();
	return err;
}
#endif /* DEMOD_DD_BLIND_FOUNDINFO_CMD */


#ifdef DEMOD_DD_DVBT2_BASEADDR_AXI_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_SET_DD_DVBT2_BASEADDR_AXI.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @param baseAddr1		[IN] UINT32
 * @param baseAddr2		[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_SET_DD_DVBT2_BASEADDR_AXI(LX_DEMOD_L1_Context *api, UINT32 baseAddr1, UINT32 baseAddr2)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[12]={0,};
	UINT8 rspByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	rspByte=1;
	cmdByte = 12;
	cmdByteBuffer[0]  =  DEMOD_DD_DVBT2_BASEADDR_AXI_CMD;
	cmdByteBuffer[1]  =  0;
	cmdByteBuffer[2]  =  0;
	cmdByteBuffer[3]  =  0;
	cmdByteBuffer[4]  =  (UINT8) ( (baseAddr1 & DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_LSB );
	cmdByteBuffer[5]  =  (UINT8) (((baseAddr1 & DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 8);
	cmdByteBuffer[6]  =  (UINT8) (((baseAddr1 & DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 16);
	cmdByteBuffer[7]  =  (UINT8) (((baseAddr1 & DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 24);
	cmdByteBuffer[8]  =  (UINT8) ( (baseAddr2 & DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_LSB );
	cmdByteBuffer[9]  =  (UINT8) (((baseAddr2 & DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 8);
	cmdByteBuffer[10] =  (UINT8) (((baseAddr2 & DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 16);
	cmdByteBuffer[11] =  (UINT8) (((baseAddr2 & DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 24);

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_SET_DD_DVBT2_BASEADDR_AXI ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice();
	return err;

}
#endif /* DEMOD_DD_DVBT2_BASEADDR_AXI_CMD */


#ifdef DEMOD_DD_DVB_BASEADDR_AXI_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_SET_DD_DVB_BASEADDR_AXI.
 * sets demoduator register through MCU
 *
 * @param *api 			[IN] LX_DEMOD_L1_Context
 * @param baseAddr1		[IN] UINT32
 * @param baseAddr2		[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L1_SET_DD_DVB_BASEADDR_AXI(LX_DEMOD_L1_Context *api, UINT32 baseAddr1, UINT32 baseAddr2, UINT32 baseAddr3)
{

	UINT8 err=0;
	UINT8 cmdByteBuffer[16]={0,};
	UINT8 rspByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	DEMOD_L0_LockDevice();

	rspByte=1;
	cmdByte = 16;
	cmdByteBuffer[0]  =  DEMOD_DD_DVB_BASEADDR_AXI_CMD;
	cmdByteBuffer[1]  =  0;
	cmdByteBuffer[2]  =  0;
	cmdByteBuffer[3]  =  0;
	cmdByteBuffer[4]  =  (UINT8) ( (baseAddr1 & DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_LSB );
	cmdByteBuffer[5]  =  (UINT8) (((baseAddr1 & DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 8);
	cmdByteBuffer[6]  =  (UINT8) (((baseAddr1 & DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 16);
	cmdByteBuffer[7]  =  (UINT8) (((baseAddr1 & DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 24);
	cmdByteBuffer[8]  =  (UINT8) ( (baseAddr2 & DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_LSB );
	cmdByteBuffer[9]  =  (UINT8) (((baseAddr2 & DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 8);
	cmdByteBuffer[10] =  (UINT8) (((baseAddr2 & DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 16);
	cmdByteBuffer[11] =  (UINT8) (((baseAddr2 & DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 24);
	cmdByteBuffer[12] =  (UINT8) ( (baseAddr3 & DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_LSB );
	cmdByteBuffer[13] =  (UINT8) (((baseAddr3 & DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 8);
	cmdByteBuffer[14] =  (UINT8) (((baseAddr3 & DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 16);
	cmdByteBuffer[15] =  (UINT8) (((baseAddr3 & DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_MASK ) << DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_LSB ) >> 24);

#ifdef	FPGA_RDK_M17_PRINT
	DBB_PRINT("\n ########## DEMOD_L1_SET_DD_DVB_BASEADDR_AXI ########## \n\n");
#endif

	err = DEMOD_L1_Process (api, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice();
	return err;

}
#endif /* DEMOD_DD_DVBT2_BASEADDR_AXI_CMD */

#endif


  /* --------------------------------------------*/
  /* SEND_COMMAND2 FUNCTION                      */
  /* --------------------------------------------*/
UINT8   DEMOD_L1_SendCommand2(LX_DEMOD_L1_Context *api, UINT32 cmd_code)
{
	switch (cmd_code)
	{
		#ifdef        DEMOD_DD_SET_REG_CMD
		 case         DEMOD_DD_SET_REG_CMD_CODE:
		   	return DEMOD_L1_SET_DD_Reg (api, api->cmd->dd_set_reg.addressMsb, api->cmd->dd_set_reg.addressLsb, api->cmd->dd_set_reg.length, api->cmd->dd_set_reg.data );
		 break;
		#endif /*     DEMOD_DD_SET_REG_CMD */

		#ifdef	      DEMOD_DD_SET_PROP_CMD
		 case         DEMOD_DD_SET_PROP_CMD_CODE:
		   return DEMOD_L1_SET_DD_Prop (api, api->cmd->set_property.prop,  api->cmd->set_property.data);
		 break;
		#endif /*     DEMOD_DD_SET_PROP_CMD */

		#ifdef		  DEMOD_DD_SET_REPEAT_CMD
		 case         DEMOD_DD_SET_REPEAT_CMD_CODE:
		   return DEMOD_L1_SET_DD_Repeat (api->i2c, api->cmd->dd_set_repeat.repeatEn );
		 break;
		#endif /*     DEMOD_DD_SET_REPEAT_CMD */

		#ifdef        DEMOD_DD_SOFT_RESET_CMD
		 case         DEMOD_DD_SOFT_RESET_CMD_CODE:
		   return DEMOD_L1_SET_DD_SoftRst (api, api->cmd->dd_soft_reset.softrstb, api->cmd->dd_soft_reset.softrstsyncb, api->cmd->dd_soft_reset.softrsteq1b, api->cmd->dd_soft_reset.softrsteq2b, api->cmd->dd_soft_reset.softrstdiseqcb, api->cmd->dd_soft_reset.softrstfecb, api->cmd->dd_soft_reset.softrsttpifb);
	 	break;
		#endif /*     DEMOD_DD_SOFT_RESET_CMD */

		#ifdef       DEMOD_DD_POWER_SAVE_CMD
		 case        DEMOD_DD_POWER_SAVE_CMD_CODE:
		   return DEMOD_L1_SET_DD_Power_Save (api, api->cmd->power_save.power_save);
		 break;
		#endif /*     DEMOD_DD_POWER_SAVE_CMD */

		#ifdef        DEMOD_DD_RESTART_CMD
		 case         DEMOD_DD_RESTART_CMD_CODE:
		   return DEMOD_L1_SET_DD_Restart (api);
		 break;
		#endif /*     DEMOD_DD_RESTART_CMD */

		#ifdef        DEMOD_DD_ATSC3_PLP_SELECT_CMD
		 case         DEMOD_DD_ATSC3_PLP_SELECT_CMD_CODE:
		   return DEMOD_L1_SET_DD_ATSC3_PLP_Select (api, api->cmd->atsc3_plp_select.plp_id, api->cmd->atsc3_plp_select.plp_id_sel_mode);
		 break;
		#endif /*     DEMOD_DD_ATSC3_PLP_SELECT_CMD */

		#ifdef        DEMOD_DD_SELFRST_CMD
		 case         DEMOD_DD_SELFRST_CMD_CODE:
			 return DEMOD_L1_SET_DD_SelfRst (api, api->cmd->dd_selfrst.rst_arg, api->cmd->dd_selfrst.rst_time1, api->cmd->dd_selfrst.rst_time2, api->cmd->dd_selfrst.rst_time3, api->cmd->dd_selfrst.rst_time4, api->cmd->dd_selfrst.rst_cnt);
		 break;
		#endif /*     DEMOD_DD_SELFRST_CMD */

		#ifdef        DEMOD_DD_GET_REG_CMD
		 case         DEMOD_DD_GET_REG_CMD_CODE:
		   		return DEMOD_L1_GET_DD_Reg (api,  api->cmd->dd_get_reg.addressMsb, api->cmd->dd_get_reg.addressLsb, api->cmd->dd_get_reg.length);
		 break;
		#endif /*     DEMOD_DD_GET_REG_CMD */

		#ifdef        DEMOD_DD_GET_PROP_CMD
		 case         DEMOD_DD_GET_PROP_CMD_CODE:
		   return DEMOD_L1_GET_DD_Prop (api, api->cmd->get_property.prop );
		 break;
		#endif /*     DEMOD_DD_GET_PROP_CMD */

		#ifdef        DEMOD_DD_STATUS_CMD
		 case         DEMOD_DD_STATUS_CMD_CODE:
		   return DEMOD_L1_GET_DD_Status (api);
		 break;
		#endif /*     DEMOD_DD_STATUS_CMD */

		#ifdef        DEMOD_DD_ATSC3_STATUS_CMD
		 case         DEMOD_DD_ATSC3_STATUS_CMD_CODE:
		   return DEMOD_L1_GET_DD_ATSC3_Status (api);
		 break;
		#endif /*     DEMOD_DD_ATSC3_STATUS_CMD */

		#ifdef        DEMOD_DD_ATSC3_PLP_ID_CMD
		 case         DEMOD_DD_ATSC3_PLP_ID_CMD_CODE:
		   return DEMOD_L1_GET_DD_ATSC3_PLP_ID (api, api->cmd->atsc3_plp_id.plp_index);
		 break;
		 #endif /*DEMOD_DD_ATSC3_PLP_ID_CMD*/

		#ifdef        DEMOD_DD_ATSC3_PLP_INFO_CMD
		 case         DEMOD_DD_ATSC3_PLP_INFO_CMD_CODE:
		   return DEMOD_L1_GET_DD_ATSC3_PLP_Info (api, api->cmd->atsc3_plp_info.plp_index);
		 break;
		 #endif /*DEMOD_DD_ATSC3_PLP_INFO_CMD*/

		#ifdef        DEMOD_DD_VSB_STATUS_CMD
		 case         DEMOD_DD_VSB_STATUS_CMD_CODE:
		   return DEMOD_L1_GET_DD_VSB_Status (api );
		 break;
		#endif /*     DEMOD_DD_VSB_STATUS_CMD */

		#ifdef        DEMOD_DD_QAM_STATUS_CMD
		 case         DEMOD_DD_QAM_STATUS_CMD_CODE:
		   return DEMOD_L1_GET_DD_QAM_Status (api);
		 break;
		#endif /*     DEMOD_DD_QAM_STATUS_CMD */

		#ifdef        DEMOD_DD_GET_PART_INFO_CMD
		 case         DEMOD_DD_GET_PART_INFO_CMD_CODE:
		   return DEMOD_L1_GET_DD_PartInfo (api );
		 break;
		#endif /*     DEMOD_DD_GET_PART_INFO_CMD */

		#ifdef        DEMOD_DD_SET_TUNE_CMD
		 case         DEMOD_DD_SET_TUNE_CMD_CODE:
		   return DEMOD_L1_SET_DD_Tune (api );
		 break;
		#endif /*     DEMOD_DD_SET_TUNE_CMD */

		#ifdef	     DEMOD_DD_LOCKTIME_CMD
		 case	     DEMOD_DD_LOCKTIME_CMD_CODE:
			 return DEMOD_L1_GET_DD_LOCKTIME(api );
		 break;
		#endif


#ifndef LG3307_API
		#ifdef        DEMOD_DD_ISDBT_BASEADDR_AXI_CMD
		 case         DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_CODE:
			 return DEMOD_L1_SET_DD_ISDBT_BASEADDR_AXI (api, api->cmd->isdbt_baseaddr_axi.baseAddr);
		 break;
		#endif /*     DEMOD_DD_ISDBT_BASEADDR_AXI_CMD */

		#ifdef        DEMOD_DD_DVBC_SRD_CMD
		 case         DEMOD_DD_DVBC_SRD_CMD_CODE:
		   return DEMOD_L1_SET_DD_SymbolRate_Detect (api, api->cmd->dvbc_sym_rate.auto_en,  api->cmd->dvbc_sym_rate.sym_rate);
		 break;
		#endif /*     DEMOD_DD_DVBC_SRD_CMD */

		#ifdef        DEMOD_DD_DVBT2_PLP_SELECT_CMD
		 case         DEMOD_DD_DVBT2_PLP_SELECT_CMD_CODE:
		   return DEMOD_L1_SET_DD_DVBT2_PLP_Select (api, api->cmd->dvbt2_plp_select.plp_id, api->cmd->dvbt2_plp_select.plp_id_sel_mode);
		 break;
		#endif /*     DEMOD_DD_DVBT2_PLP_SELECT_CMD */

		#ifdef		  DEMOD_DD_GET_DVBT2_PLP_ID_CMD
		 case		  DEMOD_DD_GET_DVBT2_PLP_ID_CMD_CODE:
			 return DEMOD_L1_GET_DD_DVBT2_PLP_ID(api, api->cmd->dvbt2_plp_id.plp_index);
		 break;
		#endif /*	  DEMOD_DD_GET_DVBT2_PLP_ID_CMD */

		#ifdef        DEMOD_DD_DVBC2_STARTFREQUENCY_CMD
		 case         DEMOD_DD_DVBC2_STARTFREQUENCY_CMD_CODE:
		   return DEMOD_L1_SET_DD_DVBC2_StartFrequency (api, api->cmd->dvbc2_start_frequency.freq);
		 break;
		#endif /*     DEMOD_DD_DVBC2_STARTFREQUENCY_CMD */

		#ifdef        DEMOD_DD_DVBC2_PLP_SELECT_CMD
		 case         DEMOD_DD_DVBC2_PLP_SELECT_CMD_CODE:
		   return DEMOD_L1_SET_DD_DVBC2_PLP_Select (api, api->cmd->dvbc2_plp_info.plp_id, api->cmd->dvbc2_plp_info.plp_id_mode, api->cmd->dvbc2_plp_info.ds_id );
		 break;
		#endif /*     DEMOD_DD_DVBC2_PLP_SELECT_CMD */

		#ifdef        DEMOD_DD_DISEQC_SEND_CMD
		 case         DEMOD_DD_DISEQC_SEND_CMD_CODE:
		   return DEMOD_L1_SET_DD_DISEQC_Send (api, api->cmd->dd_diseqc_send.diseqc_en, api->cmd->dd_diseqc_send.tone_burst, api->cmd->dd_diseqc_send.cont_tone, api->cmd->dd_diseqc_send.tone_burst, api->cmd->dd_diseqc_send.msg_length, api->cmd->dd_diseqc_send.send_framing, api->cmd->dd_diseqc_send.send_address, api->cmd->dd_diseqc_send.send_command, api->cmd->dd_diseqc_send.send_data0, api->cmd->dd_diseqc_send.send_data1, api->cmd->dd_diseqc_send.send_data2);
		 break;
		#endif /*     DEMOD_DD_DISEQC_SEND_CMD */

		#ifdef        DEMOD_DD_DVBS_OPERATING_MODE_CMD
		 case         DEMOD_DD_DVBS_OPERATING_MODE_CMD_CODE:
		   return DEMOD_L1_SET_DD_DVBS_Blind_Scan_Mode (api, api->cmd->operate_mode.opmSel, api->cmd->operate_mode.symbolRate, api->cmd->operate_mode.tuneFreq_Khz );
		 break;
		#endif /*     DEMOD_DD_DVBS_OPERATING_MODE_CMD */

		#ifdef        DEMOD_DD_DVBT2_STATUS_CMD
		 case         DEMOD_DD_DVBT2_STATUS_CMD_CODE:
		   return DEMOD_L1_GET_DD_DVBT2_Status (api);
		 break;
		#endif /*     DEMOD_DD_DVBT2_STATUS_CMD */

		#ifdef        DEMOD_DD_DVBT_STATUS_CMD
		 case         DEMOD_DD_DVBT_STATUS_CMD_CODE:
		   return DEMOD_L1_GET_DD_DVBT_Status (api);
		 break;
		#endif /*     DEMOD_DD_DVBT_STATUS_CMD */

		#ifdef        DEMOD_DD_ISDBT_STATUS_CMD
		 case         DEMOD_DD_ISDBT_STATUS_CMD_CODE:
		   return DEMOD_L1_GET_DD_ISDBT_Status (api);
		 break;
		#endif /*     DEMOD_DD_ISDBT_STATUS_CMD */

		#ifdef        DEMOD_DD_ISDBT_TMCC_INFO_CMD
		 case         DEMOD_DD_ISDBT_TMCC_INFO_CMD_CODE:
		   return DEMOD_L1_GET_DD_ISDBT_TMCC_Info (api);
		 break;
		#endif /*     DEMOD_DD_ISDBT_STATUS_CMD */

		#ifdef        DEMOD_DD_DVBC_STATUS_CMD
		 case         DEMOD_DD_DVBC_STATUS_CMD_CODE:
		   return DEMOD_L1_GET_DD_DVBC_Status (api);
		 break;
		#endif /*     DEMOD_DD_DVBC_STATUS_CMD */

		#ifdef        DEMOD_DD_DVBC2_STATUS_CMD
		 case         DEMOD_DD_DVBC2_STATUS_CMD_CODE:
		   return DEMOD_L1_GET_DD_DVBC2_Status (api);
		 break;
		#endif /*     DEMOD_DD_DVBC2_STATUS_CMD */

		#ifdef        DEMOD_DD_DISEQC_STATUS_CMD
		 case         DEMOD_DD_DISEQC_STATUS_CMD_CODE:
		   return DEMOD_L1_GET_DD_DISEQC_Status (api);
		 break;
		#endif /*     DEMOD_DD_DISEQC_STATUS_CMD */

		#ifdef        DEMOD_DD_DVBS_STATUS_CMD
		 case         DEMOD_DD_DVBS_STATUS_CMD_CODE:
		   return DEMOD_L1_GET_DD_DVBS_Status (api);
		 break;
		#endif /*     DEMOD_DD_DVBS_STATUS_CMD */

		#ifdef        DEMOD_DD_DVBS2_STATUS_CMD
		 case         DEMOD_DD_DVBS2_STATUS_CMD_CODE:
		   return DEMOD_L1_GET_DD_DVBS2_Status (api);
		 break;
		#endif /*     DEMOD_DD_DVBS2_STATUS_CMD */

		 #ifdef		 DEMOD_DD_GET_DD_SIGSRCH_INFO_CMD
		 case		 DEMOD_DD_GET_DD_SIGSRCH_INFO_CMD_CODE:
			 return DEMOD_L1_GET_DD_SIGSRCH_INFO(api);
		 #endif /*     DEMOD_DD_GET_DD_SIGSRCH_INFO_CMD */

		 #ifdef		 DEMOD_DD_BLIND_STATUS_CMD
		 case		 DEMOD_DD_BLIND_STATUS_CMD_CODE:
			 return DEMOD_L1_GET_DD_BLIND_Status(api);
		 #endif /*		DEMOD_DD_BLIND_STATUS_CMD */

		 #ifdef		 DEMOD_DD_BLIND_INIT_CMD
		 case		 DEMOD_DD_BLIND_INIT_CMD_CODE:
			 return DEMOD_L1_GET_DD_BLIND_Init(api, api->cmd->blind_init.startFreq, api->cmd->blind_init.endFreq );
		 #endif /*		DEMOD_DD_BLIND_INIT_CMD */

		#ifdef		 DEMOD_DD_BLIND_FOUNDINFO_CMD
		 case		 DEMOD_DD_BLIND_FOUNDINFO_CMD_CODE:
			 return DEMOD_L1_GET_DD_BLIND_FoundInfo(api);
		 #endif /*		DEMOD_DD_BLIND_FOUNDINFO_CMD */

		#ifdef        DEMOD_DD_DVBT2_BASEADDR_AXI_CMD
		 case         DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_CODE:
			 return DEMOD_L1_SET_DD_DVBT2_BASEADDR_AXI (api, api->cmd->dvbt2_baseaddr_axi.baseAddr1, api->cmd->dvbt2_baseaddr_axi.baseAddr2);
		 break;
		#endif /*     DEMOD_DD_ISDBT_BASEADDR_AXI_CMD */

		 #ifdef      DEMOD_DD_DTMB_STATUS_CMD
		 case        DEMOD_DD_DTMB_STATUS_CMD_CODE:
		   return DEMOD_L1_GET_DD_DTMB_Status (api );
		 break;
		#endif /*     DEMOD_DD_DTMB_STATUS_CMD */
#endif
		default :
		break;
    }
     return NO_DEMOD_ERROR;
  }


/***********************************************************************************************************************
  DEMOD_L1_CommandText function
  Use:        command text function
              Used to turn the command data into clear text.
  Parameter: *rsp     the DEMOD_CmdReplyObj structure (containing all commands)
  Parameter: rsp_code the command Id (used to know which command to use)
  Returns:    NO_DEMOD_ERROR if successful.
 ***********************************************************************************************************************/
UINT8  DEMOD_L1_CommandText          (LX_DEMOD_L1_CmdReplyObj   *rsp, UINT32 cmd_code)
{
	switch (cmd_code)
	{
		#ifdef        DEMOD_DD_STATUS_CMD
		 case         DEMOD_DD_STATUS_CMD_CODE:
		 	{
				switch(rsp->dd_status.reply_operMod)
				{
					case	DEMOD_DD_STATUS_RESPONSE_MODULATION_VSB:
						DBB_DUMP_PRINT(" [DD_STATUS] OP_MODE : VSB \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_MODULATION_QAM:
						DBB_DUMP_PRINT(" [DD_STATUS] OP_MODE : QAM \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_MODULATION_ATSC3:
						DBB_DUMP_PRINT(" [DD_STATUS] OP_MODE : ATSC3.0 \n");
						break;

					case	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBT:
						DBB_DUMP_PRINT(" [DD_STATUS] OP_MODE : DVBT \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBT2:
						DBB_DUMP_PRINT(" [DD_STATUS] OP_MODE : DVBT2 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBC:
						DBB_DUMP_PRINT(" [DD_STATUS] OP_MODE : DVBC \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBC2:
						DBB_DUMP_PRINT(" [DD_STATUS] OP_MODE : DVBC2 \n");
						break;

					case	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBS:
						DBB_DUMP_PRINT(" [DD_STATUS] OP_MODE : DVBS \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_MODULATION_DVBS2:
						DBB_DUMP_PRINT(" [DD_STATUS] OP_MODE : DVBS2 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_MODULATION_DTMB:
						DBB_DUMP_PRINT(" [DD_STATUS] OP_MODE : DTMB \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_STATUS] OP_MODE : Unknown \n");
						break;

				}

				if(rsp->dd_status.lock_fec == DEMOD_DD_STATUS_RESPONSE_LOCK_FEC_LOCKED)
					DBB_DUMP_PRINT(" [DD_STATUS] FEC_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_STATUS] FEC_LOCK : UNLOCKED \n") ;

				if(rsp->dd_status.neverLock == DEMOD_DD_STATUS_RESPONSE_NEVERLOCK_LOCKED)
					DBB_DUMP_PRINT(" [DD_STATUS] NEVER_LOCK : LOCKED \n");
				else if(rsp->dd_status.neverLock == DEMOD_DD_STATUS_RESPONSE_NEVERLOCK_PROCESSING)
					DBB_DUMP_PRINT(" [DD_STATUS] NEVER_LOCK : PROCESSING \n");
				else
					DBB_DUMP_PRINT(" [DD_STATUS] NEVER_LOCK : UNLOCKED \n") ;

		 	}
		 	break;
		#endif

		#ifdef        DEMOD_DD_ATSC3_STATUS_CMD
		 case         DEMOD_DD_ATSC3_STATUS_CMD_CODE:
		 	{

				DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] IF_AGC : %d \n", 			rsp->atsc3_status.if_agc);
				DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] CTF_PWR : %d \n", 		rsp->atsc3_status.ctf_pwr);
				DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] NUM_PLP : %d \n", 		rsp->atsc3_status.num_plp);
				DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] MSE_INFO : %d \n", 		rsp->atsc3_status.mse_info);
				DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] BER : %d \n", 			rsp->atsc3_status.ber);
				DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] CFO_VALUE : 0x%x \n", 	rsp->atsc3_status.cfo);
				DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] SFO_VALUE : 0x%x \n", 	rsp->atsc3_status.sfo);
				DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] PACKET_ERROR : %d \n",	rsp->atsc3_status.pe);

				if(rsp->atsc3_status.spInv == DEMOD_DD_ATSC3_STATUS_RESPONSE_SPECINV_NORMAL)
					DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] SPECINV : NORMAL  \n");
				else
					 DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] SPECINV : INVERTED \n") ;


				if(rsp->atsc3_status.lock_fec == DEMOD_DD_ATSC3_STATUS_RESPONSE_LOCK_FEC_LOCKED)
					DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] FEC_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] FEC_LOCK : UNLOCKED \n") ;

				if(rsp->atsc3_status.lock_carr == DEMOD_DD_ATSC3_STATUS_RESPONSE_LOCK_CARR_LOCKED)
					DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] CARR_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] CARR_LOCK : UNLOCKED \n") ;

				if(rsp->atsc3_status.done_bs_dec == DEMOD_DD_ATSC3_STATUS_RESPONSE_DONE_BS_DEC_DONE)
					DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] CARR_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] CARR_LOCK : UNLOCKED \n") ;

				if(rsp->atsc3_status.done_acq == DEMOD_DD_ATSC3_STATUS_RESPONSE_DONE_ACQ_DONE)
					DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] CARR_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] CARR_LOCK : UNLOCKED \n") ;

				if(rsp->atsc3_status.en_fsto_track == DEMOD_DD_ATSC3_STATUS_RESPONSE_EN_FSTO_TRACK_ENABLE)
					DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] CARR_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] CARR_LOCK : UNLOCKED \n") ;

				if(rsp->atsc3_status.lock_l1b == DEMOD_DD_ATSC3_STATUS_RESPONSE_LOCK_L1B_LOCKED)
					DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] CARR_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] CARR_LOCK : UNLOCKED \n") ;

				if(rsp->atsc3_status.lock_l1d == DEMOD_DD_ATSC3_STATUS_RESPONSE_LOCK_L1D_LOCKED)
					DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] CARR_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] CARR_LOCK : UNLOCKED \n") ;

				DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] SFO_VALUE : %d \n", 		rsp->atsc3_status.sfo);
				DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] MSE_INFO_DEMOD : %d \n", 	rsp->atsc3_status.mse_info_demod);
				DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] LDPC_ERROR : %d \n", 		rsp->atsc3_status.ldpc_err);



				switch(rsp->atsc3_status.fft_mode)
				{
					case	DEMOD_DD_ATSC3_STATUS_RESPONSE_FFT_MODE_8K:
						DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] FFT_MODE : 8K \n");
						break;

					case 	DEMOD_DD_ATSC3_STATUS_RESPONSE_FFT_MODE_16K:
						DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] FFT_MODE : 16K \n");
						break;

					case 	DEMOD_DD_ATSC3_STATUS_RESPONSE_FFT_MODE_32K:
						DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] FFT_MODE : 32K \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] FFT_MODE : Reserved \n");
						break;
				}


				switch(rsp->atsc3_status.gi)
				{
					case	DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_1_192:
						DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] GI : 1 / 192 \n");
						break;

					case 	DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_2_384:
						DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] GI : 2 / 384 \n");
						break;

					case 	DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_3_512:
						DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] GI : 3 / 512 \n");
						break;

					case	DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_4_768:
						DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] GI : 4 / 768 \n");
						break;

					case 	DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_5_1024:
						DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] GI : 5 / 1024 \n");
						break;

					case 	DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_6_1536:
						DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] GI : 6 / 1536 \n");
						break;

					case	DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_7_2048:
						DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] GI : 7 / 2048 \n");
						break;

					case 	DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_8_2432:
						DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] GI : 8 / 2432 \n");
						break;

					case 	DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_9_3072:
						DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] GI : 9 / 3072 \n");
						break;

					case	DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_10_368:
						DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] GI : 10 / 368 \n");
						break;

					case 	DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_11_4096:
						DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] GI : 11 / 4096 \n");
						break;

					case 	DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_12_4864:
						DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] GI : 12 / 4864 \n");
						break;

					default:
						break;
				}


				switch(rsp->atsc3_status.bandwidth)
				{
					case	DEMOD_DD_ATSC3_STATUS_RESPONSE_BANDWIDTH_6MHZ:
						DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] BANDWHIDTH : 6MHZ \n");
						break;

					case 	DEMOD_DD_ATSC3_STATUS_RESPONSE_BANDWIDTH_7MHZ:
						DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] BANDWHIDTH : 7MHZ \n");
						break;

					case 	DEMOD_DD_ATSC3_STATUS_RESPONSE_BANDWIDTH_8MHZ:
						DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] BANDWHIDTH : 8MHZ \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] BANDWHIDTH : GREATER THAN 8MHZ \n");
						break;
				}

				DBB_DUMP_PRINT(" [DD_ATSC3_STATUS] NUM_PLP : %d \n", rsp->atsc3_status.num_plp);

				break;
		 	}
		 break;
		#endif

		#ifdef 	DEMOD_DD_VSB_STATUS_CMD
		 case 	DEMOD_DD_VSB_STATUS_CMD_CODE:
	 		{

				DBB_DUMP_PRINT(" [DD_VSB_STATUS] IF_AGC : %d \n", 		rsp->vsb_status.if_agc);
				DBB_DUMP_PRINT(" [DD_VSB_STATUS] MSE_INFO : %d \n", 		rsp->vsb_status.mse_info);
				DBB_DUMP_PRINT(" [DD_VSB_STATUS] BER : %d \n", 			rsp->vsb_status.ber);
				DBB_DUMP_PRINT(" [DD_VSB_STATUS] CFO_VALUE : 0x%x \n", 	rsp->vsb_status.cfo);
				DBB_DUMP_PRINT(" [DD_VSB_STATUS] SFO_VALUE : 0x%x \n", 	rsp->vsb_status.sfo);
				DBB_DUMP_PRINT(" [DD_VSB_STATUS] PACKET_ERROR : %d \n",	rsp->vsb_status.pe);

				if(rsp->vsb_status.spInv == DEMOD_DD_VSB_STATUS_RESPONSE_SPECINV_NORMAL)
					DBB_DUMP_PRINT(" [DD_VSB_STATUS] SPECINV : NORMAL  \n");
				else
					DBB_DUMP_PRINT(" [DD_VSB_STATUS] SPECINV : INVERTED \n") ;

				if(rsp->vsb_status.lock_fec == DEMOD_DD_VSB_STATUS_RESPONSE_LOCK_FEC_LOCKED)
					DBB_DUMP_PRINT(" [DD_VSB_STATUS] FEC_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_VSB_STATUS] FEC_LOCK : UNLOCKED \n") ;

				if(rsp->vsb_status.lock_carr == DEMOD_DD_VSB_STATUS_RESPONSE_LOCK_CARR_LOCKED)
					DBB_DUMP_PRINT(" [DD_VSB_STATUS] CARR_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_VSB_STATUS] CARR_LOCK : UNLOCKED \n") ;
		 	}
		 break;
		 #endif

		#ifdef 	DEMOD_DD_QAM_STATUS_CMD
		 case 	DEMOD_DD_QAM_STATUS_CMD_CODE:
	 		{

				DBB_DUMP_PRINT(" [DD_QAM_STATUS] IF_AGC : %d \n", 			rsp->qam_status.if_agc);
				DBB_DUMP_PRINT(" [DD_QAM_STATUS] MSE_INFO : %d \n", 			rsp->qam_status.mse_info);
				DBB_DUMP_PRINT(" [DD_QAM_STATUS] BER : %d \n", 				rsp->qam_status.ber);
				DBB_DUMP_PRINT(" [DD_QAM_STATUS] CFO_VALUE : 0x%x \n", 		rsp->qam_status.cfo);
				DBB_DUMP_PRINT(" [DD_QAM_STATUS] SFO_VALUE : 0x%x \n", 		rsp->qam_status.sfo);
				DBB_DUMP_PRINT(" [DD_QAM_STATUS] PACKET_ERROR : %d \n",		rsp->qam_status.pe);
				DBB_DUMP_PRINT(" [DD_QAM_STATUS] SYMBOL_RATE : %d KHz \n",	rsp->qam_status.sym_rate);

				if(rsp->qam_status.constellation== DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64)
					DBB_DUMP_PRINT(" [DD_QAM_STATUS] CONSTELLATION : 64QAM  \n");
				else if(rsp->qam_status.constellation== DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM256)
					DBB_DUMP_PRINT(" [DD_QAM_STATUS] CONSTELLATION : 256QAM  \n");
				else
					DBB_DUMP_PRINT(" [DD_QAM_STATUS] SPECINV : UNKNOWN \n") ;

				if(rsp->qam_status.spInv == DEMOD_DD_QAM_STATUS_RESPONSE_SPECINV_NORMAL)
					DBB_DUMP_PRINT(" [DD_QAM_STATUS] SPECINV : NORMAL  \n");
				else
					DBB_DUMP_PRINT(" [DD_QAM_STATUS] SPECINV : INVERTED \n") ;

				if(rsp->qam_status.lock_fec == DEMOD_DD_QAM_STATUS_RESPONSE_LOCK_FEC_LOCKED)
					DBB_DUMP_PRINT(" [DD_QAM_STATUS] FEC_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_QAM_STATUS] FEC_LOCK : UNLOCKED \n") ;

				if(rsp->qam_status.lock_carr == DEMOD_DD_QAM_STATUS_RESPONSE_LOCK_CARR_LOCKED)
					DBB_DUMP_PRINT(" [DD_QAM_STATUS] CARR_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_QAM_STATUS] CARR_LOCK : UNLOCKED \n") ;
		 	}
		break;
		#endif

		#ifdef 	DEMOD_DD_DVBC_STATUS_CMD
		 case 	DEMOD_DD_DVBC_STATUS_CMD_CODE:
	 		{

				DBB_DUMP_PRINT(" [DD_DVBC_STATUS] IF_AGC : %d \n", 			rsp->dvbc_status.if_agc);
				DBB_DUMP_PRINT(" [DD_DVBC_STATUS] MSE_INFO : %d \n", 		rsp->dvbc_status.mse_info);
				DBB_DUMP_PRINT(" [DD_DVBC_STATUS] BER : %d \n", 				rsp->dvbc_status.ber);
				DBB_DUMP_PRINT(" [DD_DVBC_STATUS] CFO_VALUE : 0x%x \n", 		rsp->dvbc_status.cfo);
				DBB_DUMP_PRINT(" [DD_DVBC_STATUS] SFO_VALUE : 0x%x \n", 		rsp->dvbc_status.sfo);
				DBB_DUMP_PRINT(" [DD_DVBC_STATUS] PACKET_ERROR : %d \n",	rsp->dvbc_status.pe);
				DBB_DUMP_PRINT(" [DD_DVBC_STATUS] SYMBOL_RATE : %d KHz \n",	rsp->dvbc_status.sym_rate);

				switch(rsp->dvbc_status.constellation)
				{
					case	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16 :
						DBB_DUMP_PRINT(" [DD_DVBC_STATUS] CONSTELLATION : 16QAM  \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM32  :
						DBB_DUMP_PRINT(" [DD_DVBC_STATUS] CONSTELLATION : 32QAM  \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64  :
						DBB_DUMP_PRINT(" [DD_DVBC_STATUS] CONSTELLATION : 64QAM  \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM128  :
						DBB_DUMP_PRINT(" [DD_DVBC_STATUS] CONSTELLATION : 128QAM  \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM256  :
						DBB_DUMP_PRINT(" [DD_DVBC_STATUS] CONSTELLATION : 256QAM  \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_DVBC_STATUS] CONSTELLATION : UNKNOWN  \n");
						break;
				}

				if(rsp->dvbc_status.spInv == DEMOD_DD_DVBC_STATUS_RESPONSE_SPECINV_NORMAL)
					DBB_DUMP_PRINT(" [DD_DVBC_STATUS] SPECINV : NORMAL  \n");
				else
					DBB_DUMP_PRINT(" [DD_DVBC_STATUS] SPECINV : INVERTED \n") ;

				if(rsp->dvbc_status.lock_fec == DEMOD_DD_DVBC_STATUS_RESPONSE_LOCK_FEC_LOCKED)
					DBB_DUMP_PRINT(" [DD_DVBC_STATUS] FEC_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_DVBC_STATUS] FEC_LOCK : UNLOCKED \n") ;

				if(rsp->dvbc_status.lock_carr == DEMOD_DD_DVBC_STATUS_RESPONSE_LOCK_CARR_LOCKED)
					DBB_DUMP_PRINT(" [DD_DVBC_STATUS] CARR_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_DVBC_STATUS] CARR_LOCK : UNLOCKED \n") ;
		 	}
		break;
		#endif

		#ifdef DEMOD_DD_GET_PART_INFO_CMD
		 case DEMOD_DD_GET_PART_INFO_CMD_CODE:
			 {
				DBB_DUMP_PRINT(" [DD_PART_INFO] FW_VERSION : %d.%d.0 \n",rsp->part_info.fw_major, rsp->part_info.fw_minor);
				DBB_DUMP_PRINT(" [DD_PART_INFO] FW_DATE : %d/%d/%d \n",rsp->part_info.fw_year, rsp->part_info.fw_month, rsp->part_info.fw_day);
				DBB_DUMP_PRINT(" [DD_PART_INFO] FW_CHIP_REV : %d\n", rsp->part_info.chip_rev);
			 }
			 break;
		#endif

		#ifdef 	DEMOD_DD_ATSC3_PLP_INFO_CMD
		 case 	DEMOD_DD_ATSC3_PLP_INFO_CMD_CODE:
	 		{

				DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] BS_PRE_STRUCTURE : %d \n",					rsp->atsc3_plp_info.bs_pre_str);
				DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] BS_L1B_MOD : %d \n",						rsp->atsc3_plp_info.bs_l1b_mod);
				DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1B_NUM_SUBFRAMES : %d \n", 				rsp->atsc3_plp_info.l1b_num_subframes);
				DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1B_PRE_NUM_SYMBOLS : %d \n", 				rsp->atsc3_plp_info.l1b_pre_num_symbols);
				DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1B_FIRST_NUM_OFDM_SYMBOLS : %d \n", 		rsp->atsc3_plp_info.l1b_first_num_ofdm_symbols);
				DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_NUM_PLP : %d \n", 						rsp->atsc3_plp_info.l1d_num_plp);
				DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_HTI_NUM_TI_BLOCKS : %d \n",			rsp->atsc3_plp_info.l1d_plp_hti_num_ti_blocks);
				DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_HTI_NUM_FEC_BLOCKS : %d \n",		rsp->atsc3_plp_info.l1d_plp_hti_num_fec_blocks);
				DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_HTI_NUM_FEC_BLOCKS_MAX : %d \n",	rsp->atsc3_plp_info.l1d_plp_hti_num_fec_blocks_max);
				DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1B_FIRST_REDUCE_CARR : %d \n",				rsp->atsc3_plp_info.l1b_first_reduce_carr);
				DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1B_FIRST_SUB_SCATT_PB : %d \n",			rsp->atsc3_plp_info.l1b_first_sub_scatt_pb);
				DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_CTI_START_ROW : %d \n",				rsp->atsc3_plp_info.l1d_plp_cti_start_row);
				DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_HTI_INTER_SUBFRAMES : %d \n",		rsp->atsc3_plp_info.l1d_plp_hti_inter_subframe);


				switch(rsp->atsc3_plp_info.l1b_first_sub_fft_size)
				{
					case	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_FFT_SIZE_8K:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] FFT_MODE : 8K \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_FFT_SIZE_16K:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] FFT_MODE : 16K \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_FFT_SIZE_32K:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] FFT_MODE : 32K \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] FFT_MODE : Reserved \n");
						break;
				}

				switch(rsp->atsc3_plp_info.l1b_first_sub_gi)
				{
					case	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_GI_1_192:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] GI : 1 / 192 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_GI_2_384:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] GI : 2 / 384 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_GI_3_512:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] GI : 3 / 512 \n");
						break;

					case	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_GI_4_768:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] GI : 4 / 768 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_GI_5_1024:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] GI : 5 / 1024 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_GI_6_1536:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] GI : 6 / 1536 \n");
						break;

					case	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_GI_7_2048:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] GI : 7 / 2048 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_GI_8_2432:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] GI : 8 / 2432 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_GI_9_3072:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] GI : 9 / 3072 \n");
						break;

					case	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_GI_10_3648:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] GI : 10 / 368 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_GI_11_4096:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] GI : 11 / 4096 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_GI_12_4864:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] GI : 12 / 4864 \n");
						break;

					default:
						break;
				}

				switch(rsp->atsc3_plp_info.l1b_first_sub_scatt_pp)
				{
					case	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SCATT_PP_3_2:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] PP : 3_2 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SCATT_PP_3_4:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] PP : 3_4 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SCATT_PP_4_2:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] PP : 4_2 \n");
						break;

					case	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SCATT_PP_4_4:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] PP : 4_4 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SCATT_PP_6_2:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] PP : 6_2 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SCATT_PP_6_4:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] PP : 6_4 \n");
						break;

					case	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SCATT_PP_8_2:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] PP : 8_2 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SCATT_PP_8_4:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] PP : 8_4 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SCATT_PP_12_2:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] PP : 12_2 \n");
						break;

					case	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SCATT_PP_12_4:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] PP : 12_4 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SCATT_PP_16_2:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] PP : 16_2 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SCATT_PP_16_4:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] PP : 16_4 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SCATT_PP_24_2:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] PP : 24_2 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SCATT_PP_24_4:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] GI : 24_4 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SCATT_PP_32_2:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] GI : 32_2 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SCATT_PP_32_4:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] GI : 32_4 \n");
						break;

					default:
						break;
				}


				if(rsp->atsc3_plp_info.l1b_first_sub_sbs_first == DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SBS_FIRST_SBS)
					DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] FIRST SBS : SBS \n");
				else
					DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] FIRST SBS : NO_SBS \n") ;

				if(rsp->atsc3_plp_info.l1b_first_sub_sbs_last == DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_FIRST_SUB_SBS_LAST_SBS)
					DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] LAST SBS : SBS \n");
				else
					DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] LAST SBS : NO_SBS \n") ;

				switch(rsp->atsc3_plp_info.l1d_plp_ti_mode)
				{
					case	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_TI_MODE_NO_TI_MODE:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_TI_MODE : NO_TI_MODE \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_TI_MODE_CTI_MODE:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_TI_MODE : CTI_MODE \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_TI_MODE_HTI_MODE:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_TI_MODE : HTI_MODE \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_TI_MODE : Reserved \n");
						break;
				}

				switch(rsp->atsc3_plp_info.l1d_plp_fec_type)
				{
					case	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_FEC_TYPE_BCH_16K_LDPC:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_FEC_TYPE : BCH_16K_LDPC \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_FEC_TYPE_BCH_64K_LDPC:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_FEC_TYPE : BCH_64K_LDPC \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_FEC_TYPE_CRC_16K_LDPC:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_FEC_TYPE : CRC_16K_LDPC \n");
						break;

					case	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_FEC_TYPE_CRC_64K_LDPC:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_FEC_TYPE : CRC_64K_LDPC \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_FEC_TYPE_16K_LDPC:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_FEC_TYPE : 16K_LDPC \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_FEC_TYPE_64K_LDPC:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_FEC_TYPE : 64K_LDPC \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_FEC_TYPE : Reserved \n");
						break;
				}

				switch(rsp->atsc3_plp_info.l1d_plp_mod)
				{
					case	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_QPSK:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_MOD : QPSK \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_16QAM_NUC:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_MOD : 16QAM_NUC \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_64QAM_NUC:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_MOD : 64QAM_NUC \n");
						break;

					case	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_256QAM_NUC:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_MOD : 256QAM_NUC \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_1024QAM_NUC:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_MOD : 1024QAM_NUC \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_MOD_4096QAM_NUC:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_MOD : 4096QAM_NUC \n");
						break;

					default:
						break;
				}


				switch(rsp->atsc3_plp_info.l1d_plp_cr)
				{
					case	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_2_15:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_CR : 2_15 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_3_15:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_CR : 3_15 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_4_15:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_CR : 4_15 \n");
						break;

					case	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_5_15:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_CR : 5_15 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_6_15:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_CR : 6_15 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_7_15:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_CR : 7_15 \n");
						break;

					case	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_8_15:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_CR : 8_15 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_9_15:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_CR : 9_15 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_10_15:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_CR : 64QAM_NUC \n");
						break;

					case	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_11_15:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_CR : 11_15 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_12_15:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_CR : 12_15 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CR_13_15:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_CR : 13_15 \n");
						break;

					default:
						break;
				}

				switch(rsp->atsc3_plp_info.l1d_plp_cti_depth)
				{
					case	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CTI_DEPTH_512:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_CTI_DEPTH : 512 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CTI_DEPTH_724:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_CTI_DEPTH : 724 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CTI_DEPTH_887_1254:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_CTI_DEPTH : 887_1254 \n");
						break;

					case	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CTI_DEPTH_1024_1448:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_CTI_DEPTH : 1024_1448 \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_PLP_CTI_DEPTH : Reserved \n");
						break;
				}

				if(rsp->atsc3_plp_info.l1d_mimo == DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_MIMO_USED)
					DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_MIMO : USED \n");
				else
					DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_MIMO : UNUSED \n") ;


				switch(rsp->atsc3_plp_info.l1d_miso)
				{
					case	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_MISO_NOMISO:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_MISO : NOMISO \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_MISO_MISO64:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_MISO : MISO64 \n");
						break;

					case 	DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_MISO_MISO256:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_MISO : MISO256 \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_ATSC3_PLP_INFO] L1D_MISO : Reserved \n");
						break;
				}
		 	}
		break;
		#endif

		#ifdef 	DEMOD_DD_ISDBT_STATUS_CMD
		 case 	DEMOD_DD_ISDBT_STATUS_CMD_CODE:
	 		{

				DBB_DUMP_PRINT(" [DD_ISDBT_STATUS] IF_AGC : %d \n", 			rsp->isdbt_status.if_agc);
				DBB_DUMP_PRINT(" [DD_ISDBT_STATUS] MSE_INFO : %d \n", 		rsp->isdbt_status.mse_info);
				DBB_DUMP_PRINT(" [DD_ISDBT_STATUS] BER : %d \n", 				rsp->isdbt_status.ber);
				DBB_DUMP_PRINT(" [DD_ISDBT_STATUS] CFO_VALUE : 0x%x \n", 	rsp->isdbt_status.cfo);
				DBB_DUMP_PRINT(" [DD_ISDBT_STATUS] SFO_VALUE : 0x%x \n", 	rsp->isdbt_status.sfo);
				DBB_DUMP_PRINT(" [DD_ISDBT_STATUS] PACKET_ERROR : %d \n",	rsp->isdbt_status.pe);

				if(rsp->isdbt_status.spInv == DEMOD_DD_ISDBT_STATUS_RESPONSE_SPECINV_NORMAL)
					DBB_DUMP_PRINT(" [DD_ISDBT_STATUS] SPECINV : NORMAL  \n");
				else
					DBB_DUMP_PRINT(" [DD_ISDBT_STATUS] SPECINV : INVERTED \n") ;

				if(rsp->isdbt_status.lock_fec == DEMOD_DD_ISDBT_STATUS_RESPONSE_LOCK_FEC_LOCKED)
					DBB_DUMP_PRINT(" [DD_ISDBT_STATUS] FEC_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_ISDBT_STATUS] FEC_LOCK : UNLOCKED \n") ;

				if(rsp->isdbt_status.lock_carr == DEMOD_DD_ISDBT_STATUS_RESPONSE_LOCK_CARR_LOCKED)
					DBB_DUMP_PRINT(" [DD_ISDBT_STATUS] CARR_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_ISDBT_STATUS] CARR_LOCK : UNLOCKED \n") ;

		 	}
		break;
		#endif


		#ifdef 	DEMOD_DD_ISDBT_TMCC_INFO_CMD
		 case 	DEMOD_DD_ISDBT_TMCC_INFO_CMD_CODE:
	 		{
				switch(rsp->isdbt_tmcc_info.gi)
				{
					case	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_1_32:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] GI : 1_32 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_1_16:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] GI : 1_16 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_1_8:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] GI : 1_8 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_1_4:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] GI : 1_4 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_1_128:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] GI : 1_128 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_19_128:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] GI : 19_128 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_19_256:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] GI : 19_256 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_1_64:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] GI : 1_64 \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] GI : Reserved \n");
						break;
				}

				switch(rsp->isdbt_tmcc_info.fft_mode)
				{
					case	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_FFT_MODE_2K:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] FFT_MODE : 2K \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_FFT_MODE_8K:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] FFT_MODE : 8K \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_FFT_MODE_4K:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] FFT_MODE : 4K \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_FFT_MODE_1K:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] FFT_MODE : 1K \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_FFT_MODE_16K:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] FFT_MODE : 16K \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_FFT_MODE_32K:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] FFT_MODE : 32K \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_FFT_MODE_512K:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] FFT_MODE : 512K \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_FFT_MODE_256K:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] FFT_MODE : 256K \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] FFT_MODE : Reserved \n");
						break;
				}

				switch(rsp->isdbt_tmcc_info.oqama)
				{
					case	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QPSK:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO]  Layer A Constellation : QPSK \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_DQPSK   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Constellation : DQPSK \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Constellation : QAM16 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM32  :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Constellation : QAM32 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Constellation : QAM64 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM128  :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Constellation : QAM128 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM256  :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Constellation : QAM256 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM1024  :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Constellation : QAM1024 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM4096    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Constellation : QAM4096 \n");
						break;


					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_PSK8    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Constellation : PSK8 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_VSB8    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Constellation : VSB8 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM4    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Constellation : QAM4 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_APSK16      :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Constellation : APSK16 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_APSK32      :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Constellation : APSK32 \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Constellation : Reserved \n");
						break;

				}

				switch(rsp->isdbt_tmcc_info.ocra)
				{
					case	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_1_2 :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Code rate : 1_2 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_2_3  :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Code rate : 2_3 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_3_4  :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Code rate : 3_4 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_5_6  :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Code rate : 5_6 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_7_8  :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Code rate : 7_8 \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Code rate : Reserved \n");
						break;
				}

				switch(rsp->isdbt_tmcc_info.onsega)
				{

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_1   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Segment : 1 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_2    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Segment : 2 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_3    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Segment : 3 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_4    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Segmente : 4 \n");
						break;

					case	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_5   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Segment : 5 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_6    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Segment : 6 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_7    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Segment : 7 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_8    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Segment : 8 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_9    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Segment : 9 \n");
						break;

					case	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_10   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Segment : 10 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_11   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Segment : 11 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_12   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Segment : 12 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_13   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Segment : 13 \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Segment : Reserved \n");
						break;
				}


				switch(rsp->isdbt_tmcc_info.oila)
				{

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_0_0_0	:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Interleaving : 0_0_0 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_4_2_1    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Interleaving : 4_2_1 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_8_4_2    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Interleaving : 8_4_2 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_16_8_4    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Interleaving : 16_8_4 \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer A Interleaving : Reserved \n");
						break;
				}


				switch(rsp->isdbt_tmcc_info.oqamb)
				{
					case	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QPSK:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO]  Layer B Constellation : QPSK \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_DQPSK   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Constellation : DQPSK \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Constellation : QAM16 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM32  :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Constellation : QAM32 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Constellation : QAM64 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM128  :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Constellation : QAM128 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM256  :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Constellation : QAM256 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM1024  :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Constellation : QAM1024 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM4096    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Constellation : QAM4096 \n");
						break;


					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_PSK8    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Constellation : PSK8 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_VSB8    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Constellation : VSB8 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM4    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Constellation : QAM4 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_APSK16      :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Constellation : APSK16 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_APSK32      :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Constellation : APSK32 \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Constellation : Reserved \n");
						break;

				}

				switch(rsp->isdbt_tmcc_info.ocrb)
				{
					case	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_1_2 :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Code rate : 1_2 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_2_3  :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Code rate : 2_3 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_3_4  :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Code rate : 3_4 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_5_6  :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Code rate : 5_6 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_7_8  :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Code rate : 7_8 \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Code rate : Reserved \n");
						break;
				}

				switch(rsp->isdbt_tmcc_info.onsegb)
				{

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_1   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Segment : 1 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_2    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Segment : 2 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_3    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Segment : 3 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_4    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Segmente : 4 \n");
						break;

					case	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_5   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Segment : 5 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_6    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Segment : 6 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_7    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Segment : 7 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_8    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Segment : 8 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_9    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Segment : 9 \n");
						break;

					case	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_10   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Segment : 10 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_11   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Segment : 11 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_12   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Segment : 12 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_13   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Segment : 13 \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Segment : Reserved \n");
						break;
				}


				switch(rsp->isdbt_tmcc_info.oilb)
				{

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_0_0_0	:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Interleaving : 0_0_0 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_4_2_1    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Interleaving : 4_2_1 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_8_4_2    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Interleaving : 8_4_2 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_16_8_4    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Interleaving : 16_8_4 \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer B Interleaving : Reserved \n");
						break;
				}


				switch(rsp->isdbt_tmcc_info.oqamc)
				{
					case	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QPSK:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO]  Layer C Constellation : QPSK \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_DQPSK   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Constellation : DQPSK \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Constellation : QAM16 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM32  :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Constellation : QAM32 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Constellation : QAM64 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM128  :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Constellation : QAM128 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM256  :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Constellation : QAM256 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM1024  :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Constellation : QAM1024 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM4096    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Constellation : QAM4096 \n");
						break;


					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_PSK8    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Constellation : PSK8 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_VSB8    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Constellation : VSB8 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM4    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Constellation : QAM4 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_APSK16      :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Constellation : APSK16 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_APSK32      :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Constellation : APSK32 \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Constellation : Reserved \n");
						break;

				}

				switch(rsp->isdbt_tmcc_info.ocrc)
				{
					case	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_1_2 :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Code rate : 1_2 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_2_3  :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Code rate : 2_3 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_3_4  :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Code rate : 3_4 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_5_6  :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Code rate : 5_6 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_7_8  :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Code rate : 7_8 \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Code rate : Reserved \n");
						break;
				}

				switch(rsp->isdbt_tmcc_info.onsegc)
				{

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_1   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Segment : 1 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_2    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Segment : 2 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_3    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Segment : 3 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_4    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Segmente : 4 \n");
						break;

					case	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_5   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Segment : 5 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_6    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Segment : 6 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_7    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Segment : 7 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_8    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Segment : 8 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_9    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Segment : 9 \n");
						break;

					case	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_10   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Segment : 10 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_11   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Segment : 11 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_12   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Segment : 12 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_13   :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Segment : 13 \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Segment : Reserved \n");
						break;
				}


				switch(rsp->isdbt_tmcc_info.oilc)
				{

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_0_0_0	:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Interleaving : 0_0_0 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_4_2_1    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Interleaving : 4_2_1 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_8_4_2    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Interleaving : 8_4_2 \n");
						break;

					case 	DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_16_8_4    :
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Interleaving : 16_8_4 \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_ISDBT_TMCC_INFO] Layer C Interleaving : Reserved \n");
						break;
				}




		 	}
		break;
		#endif

		#ifdef 	DEMOD_DD_DVBS_STATUS_CMD
		 case 	DEMOD_DD_DVBS_STATUS_CMD_CODE:
	 		{

				DBB_DUMP_PRINT(" [DD_DVBS_STATUS] IF_AGC : %d \n", 			rsp->dvbs_status.if_agc);
				DBB_DUMP_PRINT(" [DD_DVBS_STATUS] MSE_INFO : %d \n", 		rsp->dvbs_status.mse_info);
				DBB_DUMP_PRINT(" [DD_DVBS_STATUS] BER : %d \n", 				rsp->dvbs_status.ber);
				DBB_DUMP_PRINT(" [DD_DVBS_STATUS] CFO_VALUE : 0x%x \n", 		rsp->dvbs_status.cfo);
				DBB_DUMP_PRINT(" [DD_DVBS_STATUS] SFO_VALUE : 0x%x \n", 		rsp->dvbs_status.sfo);
				DBB_DUMP_PRINT(" [DD_DVBS_STATUS] PACKET_ERROR : %d \n",	rsp->dvbs_status.pe);
				DBB_DUMP_PRINT(" [DD_DVBS_STATUS] SYMBOL_RATE : %d KHz \n",	rsp->dvbs_status.sym_rate);

				if(rsp->dvbs_status.constellation== DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QPSK)
					DBB_DUMP_PRINT(" [DD_DVBS_STATUS] CONSTELLATION : QPSK  \n");
				else
					DBB_DUMP_PRINT(" [DD_DVBS_STATUS] SPECINV : UNKNOWN \n") ;

				if(rsp->dvbs_status.spInv == DEMOD_DD_DVBS_STATUS_RESPONSE_SPECINV_NORMAL)
					DBB_DUMP_PRINT(" [DD_DVBS_STATUS] SPECINV : NORMAL  \n");
				else
					DBB_DUMP_PRINT(" [DD_DVBS_STATUS] SPECINV : INVERTED \n") ;

				switch(rsp->dvbs_status.cr)
				{
					case	DEMOD_DD_STATUS_RESPONSE_CODERATE_1_2 :
						DBB_DUMP_PRINT(" [DD_DVBS_STATUS] Code rate : 1_2 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CODERATE_2_3  :
						DBB_DUMP_PRINT(" [DD_DVBS_STATUS] Code rate : 2_3 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CODERATE_3_4  :
						DBB_DUMP_PRINT(" [DD_DVBS_STATUS] Code rate : 3_4 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CODERATE_5_6  :
						DBB_DUMP_PRINT(" [DD_DVBS_STATUS] Code rate : 5_6 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CODERATE_7_8  :
						DBB_DUMP_PRINT(" [DD_DVBS_STATUS] Code rate : 7_8 \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_DVBS_STATUS] Code rate : Reserved \n");
						break;
				}


				if(rsp->dvbs_status.lock_fec == DEMOD_DD_DVBS2_STATUS_RESPONSE_LOCK_FEC_LOCKED)
					DBB_DUMP_PRINT(" [DD_DVBS_STATUS] FEC_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_DVBS_STATUS] FEC_LOCK : UNLOCKED \n") ;

				if(rsp->dvbs_status.lock_carr == DEMOD_DD_DVBS2_STATUS_RESPONSE_LOCK_CARR_LOCKED)
					DBB_DUMP_PRINT(" [DD_DVBS_STATUS] CARR_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_DVBS_STATUS] CARR_LOCK : UNLOCKED \n") ;
		 	}
		break;
		#endif

		#ifdef 	DEMOD_DD_DVBS2_STATUS_CMD
		 case 	DEMOD_DD_DVBS2_STATUS_CMD_CODE:
	 		{

				DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] IF_AGC : %d \n", 				rsp->dvbs2_status.if_agc);
				DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] MSE_INFO : %d \n", 			rsp->dvbs2_status.mse_info);
				DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] BER : %d \n", 				rsp->dvbs2_status.ber);
				DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] CFO_VALUE : 0x%x \n", 		rsp->dvbs2_status.cfo);
				DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] SFO_VALUE : 0x%x \n", 		rsp->dvbs2_status.sfo);
				DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] PACKET_ERROR : %d \n",		rsp->dvbs2_status.pe);
				DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] SYMBOL_RATE : %d KHz \n",	rsp->dvbs2_status.sym_rate);
				DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] PILOT_PATTERN : %d \n",		rsp->dvbs2_status.pp);

				switch(rsp->dvbs2_status.constellation)
				{
					case	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QPSK :
						DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] CONSTELLATION : QPSK  \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_PSK8  :
						DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] CONSTELLATION : PSK  \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_APSK16  :
						DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] CONSTELLATION : 16APSK  \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_APSK32  :
						DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] CONSTELLATION : 32APSK  \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] CONSTELLATION : UNKNOWN  \n");
						break;
				}

				if(rsp->dvbs2_status.spInv == DEMOD_DD_DVBS2_STATUS_RESPONSE_SPECINV_NORMAL)
					DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] SPECINV : NORMAL  \n");
				else
					DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] SPECINV : INVERTED \n") ;

				switch(rsp->dvbs2_status.cr)
				{
					case	DEMOD_DD_STATUS_RESPONSE_CODERATE_1_4 :
						DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] Code rate : 1_4 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CODERATE_1_3  :
						DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] Code rate : 1_3 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CODERATE_2_5  :
						DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] Code rate : 2_5 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CODERATE_1_2  :
						DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] Code rate : 1_2 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CODERATE_3_5  :
						DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] Code rate : 3_5 \n");
						break;

					case	DEMOD_DD_STATUS_RESPONSE_CODERATE_2_3 :
						DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] Code rate : 2_3 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CODERATE_3_4  :
						DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] Code rate : 3_4 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CODERATE_4_5  :
						DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] Code rate : 4_5 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CODERATE_5_6  :
						DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] Code rate : 5_6 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CODERATE_8_9  :
						DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] Code rate : 8_9 \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CODERATE_9_10  :
						DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] Code rate : 9_10 \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] Code rate : Reserved \n");
						break;
				}


				if(rsp->dvbs2_status.lock_fec == DEMOD_DD_DVBS2_STATUS_RESPONSE_LOCK_FEC_LOCKED)
					DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] FEC_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] FEC_LOCK : UNLOCKED \n") ;

				if(rsp->dvbs2_status.lock_carr == DEMOD_DD_DVBS2_STATUS_RESPONSE_LOCK_CARR_LOCKED)
					DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] CARR_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_DVBS2_STATUS] CARR_LOCK : UNLOCKED \n") ;
		 	}
		break;
		#endif

		#ifdef 	DEMOD_DD_DVBT_STATUS_CMD
		 case 	DEMOD_DD_DVBT_STATUS_CMD_CODE:
	 		{
				DBB_DUMP_PRINT(" [DD_DVBT_STATUS] IF_AGC : %d \n", 			rsp->dvbt_status.if_agc);
				DBB_DUMP_PRINT(" [DD_DVBT_STATUS] MSE_INFO : %d \n", 		rsp->dvbt_status.mse_info);
				DBB_DUMP_PRINT(" [DD_DVBT_STATUS] BER : %d \n", 				rsp->dvbt_status.ber);
				DBB_DUMP_PRINT(" [DD_DVBT_STATUS] CFO_VALUE : 0x%x \n", 		rsp->dvbt_status.cfo);//
				DBB_DUMP_PRINT(" [DD_DVBT_STATUS] SFO_VALUE : 0x%x \n", 		rsp->dvbt_status.sfo);//
				DBB_DUMP_PRINT(" [DD_DVBT_STATUS] PACKET_ERROR : %d \n",	rsp->dvbt_status.pe);
				DBB_DUMP_PRINT(" [DD_DVBT_STATUS] CELL_ID : %d \n",			rsp->dvbt_status.cell_id);
				DBB_DUMP_PRINT(" [DD_DVBT_STATUS] HIERARCHY : %d \n",		rsp->dvbt_status.hierarchy);
				DBB_DUMP_PRINT(" [DD_DVBT_STATUS] HIERARCHY_SEL : %d \n",	rsp->dvbt_status.hierarchy_sel);

				if(rsp->dvbt_status.hierarchy_sel == DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_SEL_HP)
				{
					switch(rsp->dvbt_status.hp_cr)
					{

						case 	DEMOD_DD_DVBT_STATUS_RESPONSE_HP_CR_HP_1_2	:
							DBB_DUMP_PRINT(" [DD_DVBT_STATUS] HP_CR = 1_2 \n");
							break;

						case 	DEMOD_DD_DVBT_STATUS_RESPONSE_HP_CR_HP_2_3	:
							DBB_DUMP_PRINT(" [DD_DVBT_STATUS] HP_CR = 2_3 \n");
							break;

						case	DEMOD_DD_DVBT_STATUS_RESPONSE_HP_CR_HP_3_4	:
							DBB_DUMP_PRINT(" [DD_DVBT_STATUS] HP_CR = 3_4 \n");
							break;

						case	DEMOD_DD_DVBT_STATUS_RESPONSE_HP_CR_HP_5_6	:
							DBB_DUMP_PRINT(" [DD_DVBT_STATUS] HP_CR = 5_6 \n");
							break;

						case	DEMOD_DD_DVBT_STATUS_RESPONSE_HP_CR_HP_7_8	:
							DBB_DUMP_PRINT(" [DD_DVBT_STATUS] HP_CR = 7_8 \n");
							break;

						default:
							DBB_DUMP_PRINT(" [DD_DVBT_STATUS] HP_CR = = UNKNOWN \n");
							break;
					}
				}
				else
				{
					switch(rsp->dvbt_status.lp_cr)
					{

						case 	DEMOD_DD_DVBT_STATUS_RESPONSE_LP_CR_1_2	:
							DBB_DUMP_PRINT(" [DD_DVBT_STATUS] LP_CR = 1_2 \n");
							break;

						case 	DEMOD_DD_DVBT_STATUS_RESPONSE_LP_CR_2_3	:
							DBB_DUMP_PRINT(" [DD_DVBT_STATUS] LP_CR = 2_3 \n");
							break;

						case	DEMOD_DD_DVBT_STATUS_RESPONSE_LP_CR_3_4	:
							DBB_DUMP_PRINT(" [DD_DVBT_STATUS] LP_CR = 3_4 \n");
							break;

						case	DEMOD_DD_DVBT_STATUS_RESPONSE_LP_CR_5_6	:
							DBB_DUMP_PRINT(" [DD_DVBT_STATUS] LP_CR = 5_6 \n");
							break;

						case	DEMOD_DD_DVBT_STATUS_RESPONSE_LP_CR_7_8	:
							DBB_DUMP_PRINT(" [DD_DVBT_STATUS] LP_CR = 7_8 \n");
							break;

						default:
							DBB_DUMP_PRINT(" [DD_DVBT_STATUS] LP_CR = UNKNOWN \n");
							break;
					}
				}


				switch(rsp->dvbt_status.constellation)
				{

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QPSK	:
						DBB_DUMP_PRINT(" [DD_DVBT_STATUS] CONSTELLATION = QPSK \n");
						break;

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16	:
						DBB_DUMP_PRINT(" [DD_DVBT_STATUS] CONSTELLATION = 16QAM \n");
						break;

					case	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64	:
						DBB_DUMP_PRINT(" [DD_DVBT_STATUS] CONSTELLATION = 64QAM \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_DVBT_STATUS] CONSTELLATION = UNKNOWN \n");
						break;
				}

				switch(rsp->dvbt_status.gi)
				{

					case 	DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_32	:
						DBB_DUMP_PRINT(" [DD_DVBT_STATUS] GUARD INTERVAL = 1/32 \n");
						break;

					case 	DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_16	:
						DBB_DUMP_PRINT(" [DD_DVBT_STATUS] GUARD INTERVAL = 1/16 \n");
						break;

					case	DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_8	:
						DBB_DUMP_PRINT(" [DD_DVBT_STATUS] GUARD INTERVAL = 1/8 \n");
						break;

					case	DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_4	:
						DBB_DUMP_PRINT(" [DD_DVBT_STATUS] GUARD INTERVAL = 1/4 \n");
						break;

					case	DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_128	:
						DBB_DUMP_PRINT(" [DD_DVBT_STATUS] GUARD INTERVAL = 1/128 \n");
						break;

					case	DEMOD_DD_DVBT_STATUS_RESPONSE_GI_19_128	:
						DBB_DUMP_PRINT(" [DD_DVBT_STATUS] GUARD INTERVAL = 19/128 \n");
						break;

					case	DEMOD_DD_DVBT_STATUS_RESPONSE_GI_19_256	:
						DBB_DUMP_PRINT(" [DD_DVBT_STATUS] GUARD INTERVAL = 19/256 \n");
						break;

					case	DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_64	:
						DBB_DUMP_PRINT(" [DD_DVBT_STATUS] GUARD INTERVAL = 1/64 \n");
						break;


					default:
						DBB_DUMP_PRINT(" [DD_DVBT_STATUS] GUARD INTERVAL = UNKNOWN \n");
						break;
				}

				switch(rsp->dvbt_status.fft_mode)
				{
					case 	DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_2K	:
						DBB_DUMP_PRINT(" [DD_DVBT_STATUS] FFT_MODE = 2K \n");
						break;

					case 	DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_8K	:
						DBB_DUMP_PRINT(" [DD_DVBT_STATUS] FFT_MODE =  8K \n");
						break;

					case	DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_4K	:
						DBB_DUMP_PRINT(" [DD_DVBT_STATUS] FFT_MODE =  4K \n");
						break;

					case	DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_1K	:
						DBB_DUMP_PRINT(" [DD_DVBT_STATUS] FFT_MODE =  1K \n");
						break;

					case	DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_16K	:
						DBB_DUMP_PRINT(" [DD_DVBT_STATUS] FFT_MODE =  16K \n");
						break;

					case	DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_32K	:
						DBB_DUMP_PRINT(" [DD_DVBT_STATUS] FFT_MODE =  32K \n");
						break;

					case	DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_512K	:
						DBB_DUMP_PRINT(" [DD_DVBT_STATUS] FFT_MODE =  512 \n");
						break;

					case	DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_256K	:
						DBB_DUMP_PRINT(" [DD_DVBT_STATUS] FFT_MODE =  256 \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_DVBT_STATUS] FFT_MODE =  UNKNOWN \n");
						break;
				}



				if(rsp->dvbt_status.spInv == DEMOD_DD_DVBT_STATUS_RESPONSE_SPECINV_NORMAL)
					DBB_DUMP_PRINT(" [DD_DVBT_STATUS] SPECINV : NORMAL  \n");
				else
					DBB_DUMP_PRINT(" [DD_DVBT_STATUS] SPECINV : INVERTED \n") ;


				if(rsp->dvbt_status.lock_fec == DEMOD_DD_DVBT_STATUS_RESPONSE_LOCK_FEC_LOCKED)
					DBB_DUMP_PRINT(" [DD_DVBT_STATUS] FEC_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_DVBT_STATUS] FEC_LOCK : UNLOCKED \n") ;

				if(rsp->dvbt_status.lock_carr == DEMOD_DD_DVBT_STATUS_RESPONSE_LOCK_CARR_LOCKED)
					DBB_DUMP_PRINT(" [DD_DVBT_STATUS] CARR_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_DVBT_STATUS] CARR_LOCK : UNLOCKED \n") ;
		 	}
		 break;
		 #endif

		 #ifdef 	DEMOD_DD_DVBT2_STATUS_CMD
		 case 	DEMOD_DD_DVBT2_STATUS_CMD_CODE:
	 		{
				DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] IF_AGC : %d \n", 		rsp->dvbt2_status.if_agc);
				DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] MSE_INFO : %d \n", 		rsp->dvbt2_status.mse_info);
				DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] BER : %d \n", 			rsp->dvbt2_status.ber);
				DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] CFO_VALUE : 0x%x \n", 	rsp->dvbt2_status.cfo);//
				DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] SFO_VALUE : 0x%x \n", 	rsp->dvbt2_status.sfo);//
				DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] PACKET_ERROR : %d \n",	rsp->dvbt2_status.pe);
				DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] NUM_PLP : %d \n",		rsp->dvbt2_status.num_plp);
				DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] NUM_DPLP : %d \n",		rsp->dvbt2_status.num_dplp);
				DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] BW_EXT : %d \n",			rsp->dvbt2_status.bw_ext);

				switch(rsp->dvbt2_status.cr)
				{

					case 	DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_1_2	:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] CR = 1_2 \n");
						break;

					case 	DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_3_5	:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] CR = 3_5 \n");
						break;

					case	DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_2_3	:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] CR = 2_3 \n");
						break;

					case	DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_3_4	:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] CR = 3_4 \n");
						break;

					case	DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_4_5	:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] CR = 4_5 \n");
						break;

					case	DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_5_6	:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] CR = 5_6 \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] CR = UNKNOWN \n");
						break;
				}



				switch(rsp->dvbt2_status.constellation)
				{

					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QPSK	:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] CONSTELLATION = QPSK \n");
						break;


					case 	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16	:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] CONSTELLATION = 16QAM \n");
						break;


					case	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64	:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] CONSTELLATION = 64QAM \n");
						break;

					case	DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM256	:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] CONSTELLATION = 256QAM \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] CONSTELLATION = UNKNOWN \n");
						break;
				}

				switch(rsp->dvbt2_status.gi)
				{

					case 	DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_32	:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] GUARD INTERVAL = 1/32 \n");
						break;

					case 	DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_16	:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] GUARD INTERVAL = 1/16 \n");
						break;

					case	DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_8	:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] GUARD INTERVAL = 1/8 \n");
						break;

					case	DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_4	:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] GUARD INTERVAL = 1/4 \n");
						break;

					case	DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_128	:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] GUARD INTERVAL = 1/128 \n");
						break;

					case	DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_19_128	:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] GUARD INTERVAL = 19/128 \n");
						break;

					case	DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_19_256	:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] GUARD INTERVAL = 19/256 \n");
						break;

					case	DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_64	:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] GUARD INTERVAL = 1/64 \n");
						break;


					default:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] GUARD INTERVAL = UNKNOWN \n");
						break;
				}

				switch(rsp->dvbt2_status.fft_mode)
				{
					case 	DEMOD_DD_DVBT2_STATUS_RESPONSE_FFT_MODE_2K	:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] FFT_MODE = 2K \n");
						break;

					case 	DEMOD_DD_DVBT2_STATUS_RESPONSE_FFT_MODE_8K	:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] FFT_MODE =  8K \n");
						break;

					case	DEMOD_DD_DVBT2_STATUS_RESPONSE_FFT_MODE_4K	:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] FFT_MODE =  4K \n");
						break;

					case	DEMOD_DD_DVBT2_STATUS_RESPONSE_FFT_MODE_1K	:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] FFT_MODE =  1K \n");
						break;

					case	DEMOD_DD_DVBT2_STATUS_RESPONSE_FFT_MODE_16K	:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] FFT_MODE =  16K \n");
						break;

					case	DEMOD_DD_DVBT2_STATUS_RESPONSE_FFT_MODE_32K	:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] FFT_MODE =  32K \n");
						break;

					case	DEMOD_DD_DVBT2_STATUS_RESPONSE_FFT_MODE_512 :
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] FFT_MODE =  512 \n");
						break;

					case	DEMOD_DD_DVBT2_STATUS_RESPONSE_FFT_MODE_256 :
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] FFT_MODE =  256 \n");
						break;

					default:
						DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] FFT_MODE =  UNKNOWN \n");
						break;
				}



				if(rsp->dvbt2_status.spInv == DEMOD_DD_DVBT2_STATUS_RESPONSE_SPECINV_NORMAL)
					DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] SPECINV : NORMAL  \n");
				else
					DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] SPECINV : INVERTED \n") ;


				if(rsp->dvbt2_status.lock_fec == DEMOD_DD_DVBT2_STATUS_RESPONSE_LOCK_FEC_LOCKED)
					DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] FEC_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] FEC_LOCK : UNLOCKED \n") ;

				if(rsp->dvbt2_status.lock_carr == DEMOD_DD_DVBT2_STATUS_RESPONSE_LOCK_CARR_LOCKED)
					DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] CARR_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_DVBT2_STATUS] CARR_LOCK : UNLOCKED \n") ;
		 	}
		 break;
		 #endif

		#ifdef 	DEMOD_DD_DTMB_STATUS_CMD
		 case 	DEMOD_DD_DTMB_STATUS_CMD_CODE:
	 		{

				DBB_DUMP_PRINT(" [DD_DTMB_STATUS] IF_AGC : %d \n", 			rsp->dtmb_status.if_agc);
				DBB_DUMP_PRINT(" [DD_DTMB_STATUS] MSE_INFO : %d \n", 		rsp->dtmb_status.mse_info);
				DBB_DUMP_PRINT(" [DD_DTMB_STATUS] BER : %d \n", 				rsp->dtmb_status.ber);
				DBB_DUMP_PRINT(" [DD_DTMB_STATUS] CFO_VALUE : 0x%x \n", 		rsp->dtmb_status.cfo);
				DBB_DUMP_PRINT(" [DD_DTMB_STATUS] SFO_VALUE : 0x%x \n", 		rsp->dtmb_status.sfo);
				DBB_DUMP_PRINT(" [DD_DTMB_STATUS] PACKET_ERROR : %d \n",	rsp->dtmb_status.pe);

				if(rsp->dtmb_status.spInv == DEMOD_DD_DTMB_STATUS_RESPONSE_SPECINV_NORMAL)
					DBB_DUMP_PRINT(" [DD_DTMB_STATUS] SPECINV : NORMAL  \n");
				else
					DBB_DUMP_PRINT(" [DD_DTMB_STATUS] SPECINV : INVERTED \n") ;

				if(rsp->dtmb_status.lock_fec == DEMOD_DD_DTMB_STATUS_RESPONSE_LOCK_FEC_LOCKED)
					DBB_DUMP_PRINT(" [DD_DTMB_STATUS] FEC_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_DTMB_STATUS] FEC_LOCK : UNLOCKED \n") ;

				if(rsp->dtmb_status.lock_carr == DEMOD_DD_DTMB_STATUS_RESPONSE_LOCK_CARR_LOCKED)
					DBB_DUMP_PRINT(" [DD_DTMB_STATUS] CARR_LOCK : LOCKED \n");
				else
					DBB_DUMP_PRINT(" [DD_DTMB_STATUS] CARR_LOCK : UNLOCKED \n") ;
		 	}
		 break;
		 default:
			 break;

		 #endif


		}
	return NO_DEMOD_ERROR;
}





