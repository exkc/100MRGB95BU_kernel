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
#define DEMOD_TAG "[L1] "

#include <DBB_DEMOD_typedefs.h>
#include <demod_util.h>

#include "DBB_DEMOD_L1_Properties.h"
#include "DBB_DEMOD_L1_Commands.h"

#include "DBB_DEMOD_L1_API.h"

#include "DBB_DEMOD_L1_IPC_Prototypes.h"
#include "DBB_DEMOD_L1_Commands_Prototypes.h"
#include "DBB_DEMOD_L1_Properties_Functions.h"

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_XTENSA)
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)
#endif


/***********************************************************************************************************************
  DEMOD_L1_API_Init function
  Use:        software initialisation function
              Used to initialize the software context
  Returns:    0 if no error
  Comments:   It should be called first and once only when starting the application
  Parameter:  *core         a pointer to the context to initialize
  Parameter:  addr          the LGDBB I2C address
  Porting:    Allocation errors need to be properly managed.
  Porting:    I2C initialization needs to be adapted to use the available I2C functions
 ***********************************************************************************************************************/
int DEMOD_L1_API_Init (LX_DEMOD_L1_Context * core, UINT32 addr)
{
	DEMOD_L0_Init(core->chip);
	DEMOD_L0_SetAddress(core->chip, addr, 2);

	// Set the propertyWriteMode to DEMOD_DOWNLOAD_ON_CHANGE to only download property settings on change (recommended)
	//      if propertyWriteMode is set to DEMOD_DOWNLOAD_ALWAYS the properties will be downloaded regardless of change
	core->propertyWriteMode = DEMOD_DD_DOWNLOAD_ON_CHANGE;//DEMOD_DD_DOWNLOAD_ON_CHANGE ; // DEMOD_DD_DOWNLOAD_ALWAYS;
	// SPI download default values

#if (DEMOD_PLATFORM != DEMOD_PLATFORM_GUI)
	DEMOD_L0_InitDevice(core->chip);
#endif

	DEMOD_L1_IPC_Reset(core);

	core->fw_state = DEMOD_FW_STATE_STOP;
	return NO_DEMOD_ERROR;
}

/***********************************************************************************************************************
  DEMOD_L1_API_SelectFirmware function
  Use:        set fw file to load
  Returns:    0 if no error
  Parameter:  *core         a pointer to the context to initialize
  Parameter:  *iram         f/w of iram
  Parameter:  *dram         f/w of dram
 ***********************************************************************************************************************/
/*
int DEMOD_L1_API_SelectFirmware (LX_DEMOD_L1_Context * core, LX_DEMOD_FW_STRUCT * iram, LX_DEMOD_FW_STRUCT * dram)
{
	core->fwiram = iram;
	core->fwdram = dram;

	return NO_DEMOD_ERROR;
}
*/

/***********************************************************************************************************************
  DEMOD_L1_API_Patch_I function
  Use:        Patch information function
              Used to send a number of bytes to the DBB. Useful to download the firmware.
  Returns:    0 if no error
  Parameter:  error_code the error code.
  Porting:    Useful for application development for debug purposes.
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
int DEMOD_L1_API_Patch_I (LX_DEMOD_L1_Context * core, UINT16 addr, UINT32 iNbBytes, UINT8 *pucDataBuffer)
{
//	UINT8 wrData[4] = {0, };
//	UINT8 rdData[4] = {0, };

	UINT32 wtemp;
	SINT32 j=0,k=0;

	j = iNbBytes;
	k = 0;

	addr = 0x0;
	core->chip->i2c_indirect = 0;

	wtemp = 0x40000000;
	if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_I2C_HBASE, 4, &wtemp))
		return -ERROR_DEMOD_LOADING_FIRMWARE;

	while(j > 0)
	{
		core->chip->i2c_indirect = 3;

		if(j >= 0xfc) {
			if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, addr, 0xfc, pucDataBuffer+k))
				return -ERROR_DEMOD_LOADING_FIRMWARE;
		} else {
			if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, addr, j, pucDataBuffer+k))
				return -ERROR_DEMOD_LOADING_FIRMWARE;
		}

		addr += 0xfc;
		k += 0xfc;
		j -= 0xfc;
	}
	core->chip->i2c_indirect = 0;

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
int DEMOD_L1_API_Patch_D (LX_DEMOD_L1_Context * core, UINT16 addr, UINT32 iNbBytes, UINT8 *pucDataBuffer)
{
//	UINT8 wrData[4] = {0, };
//	UINT8 rdData[4] = {0, };

	UINT32 wtemp;
	SINT32 j=0,k=0;

	j = iNbBytes;
	k = 0;
	addr = 0x0;
	core->chip->i2c_indirect = 0;

	wtemp = 0x3FFE0000;
	if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_I2C_HBASE, 4, &wtemp))
		return -ERROR_DEMOD_LOADING_FIRMWARE;

	while(j > 0) {
		core->chip->i2c_indirect = 3;

		if(j >= 0xfc) {
			if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, addr, 0xfc, pucDataBuffer + k))
				return -ERROR_DEMOD_LOADING_FIRMWARE;
		} else {
			if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, addr, j, pucDataBuffer + k))
				return -ERROR_DEMOD_LOADING_FIRMWARE;
		}

		addr += 0xfc;
		k += 0xfc;
		j -= 0xfc;
	}
	core->chip->i2c_indirect = 0;

	return NO_DEMOD_ERROR;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_API_LoadFirmware_IRAM.
 * deprecated in O20
 */
int DEMOD_L1_API_LoadFirmware_IRAM (LX_DEMOD_L1_Context * core, LX_DEMOD_FW_STRUCT fw_table[], UINT8 nbLines)
{
    DEMOD_INFO("deprecated\n");
    return NO_DEMOD_ERROR;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_API_LoadFirmware_DRAM.
 * deprecated in O20
 */
int DEMOD_L1_API_LoadFirmware_DRAM (LX_DEMOD_L1_Context * core, LX_DEMOD_FW_STRUCT fw_table[], UINT8 nbLines)
{
	DEMOD_INFO("deprecated\n");
	return NO_DEMOD_ERROR;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_API_LoadFirmware_External.
 * Load firmware from FIRMWARE_TABLE array in DBB_Firmware_x_y_build_z.h file into external DBB modulator IRAM & DRAM.
 *
 * @param *core		[IN] LX_DEMOD_L1_Context
 * @param *fw_table	[IN] LX_DEMOD_FW_STRUCT
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_API_LoadFirmware_EXT (LX_DEMOD_L1_Context * core, LX_DEMOD_FW_STRUCT * fw_table)
{
	int return_code = NO_DEMOD_ERROR;
	int load_start_ms;

	int fw_iram_size = 0x10000;
	int fw_dram_size = 0x8000; //fw_table->firmware_size - fw_iram_size;

	load_start_ms = DEMOD_L0_system_time();

	if (fw_table->firmware_size > 0) {  /* don't download if length is 0 , e.g. dummy firmware */
		return_code = DEMOD_L1_API_Patch_I(core, 0, fw_iram_size, &fw_table->firmware_table[0]);
		if (return_code != 0) {
		  	DEMOD_ERROR("[DEMOD_API] Error 0x%02x patching %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
			return -ERROR_DEMOD_LOADING_FIRMWARE;
		}
		return_code = DEMOD_L1_API_Patch_D(core, 0, fw_dram_size, &fw_table->firmware_table[fw_iram_size]);
		if (return_code != 0) {
		  	DEMOD_ERROR("[DEMOD_API] Error 0x%02x patching %s\n", return_code, DEMOD_L1_API_Error_Text(return_code) );
			return -ERROR_DEMOD_LOADING_FIRMWARE;
		}
	}


	if (DEMOD_L0_system_time() - load_start_ms > 8000)
	{
		DEMOD_WARN("[DEMOD_API] line 1 took too much time\n");
	}

	DEMOD_INFO ("[DEMOD_API] Manual loading took %4d ms\n", DEMOD_L0_system_time() - load_start_ms);
	return NO_DEMOD_ERROR;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_API_LoadFirmware_MEM.
 * Load firmware from DDR MEMORY.
 *
 * @param *core		[IN] LX_DEMOD_L1_Context
 * @param fw_table[] 	[IN] LX_DEMOD_FW_STRUCT
 * @param nbLines 	[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_API_LoadFirmware_MEM (LX_DEMOD_L1_Context * core, UINT32 baseAddr)
{
	UINT32 wtemp = 0;
	UINT32 load_start_ms = 0;

	int ret = NO_DEMOD_ERROR;

#if defined(DEMOD_SPEND_TIME_CHECK)
	UINT64			start_clock;
	UINT64			spend_clock;
	UINT32			spend_us;
	UINT32			spend_ms;
	
	start_clock = DEMOD_L0_SystemClock();
#endif

	DEMOD_PRINT("[DEMOD_API] Start\n");

	load_start_ms = DEMOD_L0_system_time();

	if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_FW_DL_ADDR, 4, &baseAddr))
		return -ERROR_DEMOD_LOADING_FIRMWARE;

#if defined(DEMOD_SPEND_TIME_CHECK)
	spend_clock = DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us);
	if (spend_ms > 1)
		DEMOD_INFO("TC: LoadFirmware_MEM, dl_addr , spend %3u.%03ums\n",spend_ms, spend_us);
	start_clock = DEMOD_L0_SystemClock();
#endif

	/* set fwdn_en */
	if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(core->chip, REG_FW_DL_CTRL, 4, &wtemp))
		return -ERROR_DEMOD_LOADING_FIRMWARE;

#if defined(DEMOD_SPEND_TIME_CHECK)
	spend_clock = DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us);
	if (spend_ms > 1)
		DEMOD_INFO("TC: LoadFirmware_MEM, dl_ctrl_0, spend %3u.%03ums\n",spend_ms, spend_us);
	start_clock = DEMOD_L0_SystemClock();
#endif

	wtemp |= 0x1;

	if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_FW_DL_CTRL, 4, &wtemp))
		return -ERROR_DEMOD_LOADING_FIRMWARE;

#if defined(DEMOD_SPEND_TIME_CHECK)
	spend_clock = DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us);
	if (spend_ms > 1)
		DEMOD_INFO("TC: LoadFirmware_MEM, dl_ctrl_1, spend %3u.%03ums\n",spend_ms, spend_us);
	start_clock = DEMOD_L0_SystemClock();
#endif

	/* wait fwdn_done until 50ms */
	wtemp = 0;
	do {
	//while(1) {
		DEMOD_L0_ReadCommandBytes(core->chip, REG_TRACE_FWDN_DONE, 4, &wtemp);
		if(wtemp & 0x100) { // check fwdn_done
			DEMOD_DEBUG("[DEMOD_API] fw download is Done\n");
		} else if (DEMOD_L0_system_time() - load_start_ms >= 50) {
			DEMOD_ERROR("[DEMOD_API] fw download timeout\n");
			ret = -ERROR_DEMOD_LOADING_FIRMWARE;
		}
		DEMOD_L0_system_wait(1);
	} while (((wtemp & 0x100) != 0x100) && (ret == NO_DEMOD_ERROR));
	
#if defined(DEMOD_SPEND_TIME_CHECK)
	spend_clock = DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us);
	if (spend_ms > 1)
		DEMOD_INFO("TC: LoadFirmware_MEM, dl_ctrl_1, spend %3u.%03ums\n",spend_ms, spend_us);
	start_clock = DEMOD_L0_SystemClock();
#endif

	//DEMOD_L0_system_wait(10); // change time 1 to 10 because of M19 TER/SAT change issue
	DEMOD_L0_system_wait(1);

	/* clear fwdn_en */
	if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(core->chip, REG_FW_DL_CTRL, 4, &wtemp))
		return -ERROR_DEMOD_LOADING_FIRMWARE;
#if defined(DEMOD_SPEND_TIME_CHECK)
	spend_clock = DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us);
	if (spend_ms > 1)
		DEMOD_INFO("TC: LoadFirmware_MEM, dl_ctrl_2, spend %3u.%03ums\n",spend_ms, spend_us);
	start_clock = DEMOD_L0_SystemClock();
#endif

	wtemp &= ~0x1; // clear fwdn_en

	if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_FW_DL_CTRL, 4, &wtemp))
		return -ERROR_DEMOD_LOADING_FIRMWARE;

#if defined(DEMOD_SPEND_TIME_CHECK)
	spend_clock = DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us);
	if (spend_ms > 1)
		DEMOD_INFO("TC: LoadFirmware_MEM, dl_ctrl_3, spend %3u.%03ums\n",spend_ms, spend_us);
	start_clock = DEMOD_L0_SystemClock();
#endif

	DEMOD_INFO("[DEMOD_API] took %u ms\n", DEMOD_L0_system_time() - load_start_ms);

	return ret;
}

/***********************************************************************************************************************
  DEMOD_L1_API_STATUS function
  Use:        make log message about DEMOD configuration & Status
  Returns:    log message length
  Parameter:  error_code the error code.
 ***********************************************************************************************************************/

int DEMOD_L1_API_Debug (LX_DEMOD_L1_Context * core, char * dbglog) {
	int dbgidx = 0;
	UINT32 temp[4] = {0, 0, 0, 0};

	dbgidx += SPRINTF(dbglog + dbgidx, "M x%X, Lock %u, Never %u",
		core->rsp->dd_status.reply_operMod, core->rsp->dd_status.lock_fec, core->rsp->dd_status.neverLock);

	dbgidx += SPRINTF(dbglog + dbgidx, ", FW %u", core->fw_state);

	dbgidx += SPRINTF(dbglog + dbgidx,", req %u,%u,%u,%u,%u,%u, res %u,%u,%u,%u,%u,%u",
		core->cmd_req_cnt, core->cmd_req_err_cnt, core->cmd_req_out_cnt, core->cmd_req_val_cnt, core->cmd_req_inv_cnt, core->cmd_req_ret_cnt,
		core->cmd_res_cnt, core->cmd_res_err_cnt, core->cmd_res_out_cnt, core->cmd_res_val_cnt, core->cmd_res_inv_cnt, core->cmd_res_skp_cnt);

	if (NO_DEMOD_ERROR == DEMOD_L0_ReadCommandBytes(core->chip, REG_FW_STATE, 4, temp)) {
		dbgidx += SPRINTF(dbglog + dbgidx, ", S x%08X", temp[0]);
	} else {
		dbgidx += SPRINTF(dbglog + dbgidx, ", S err");
	}

	if (NO_DEMOD_ERROR == DEMOD_L0_ReadCommandBytes(core->chip, REG_INFO_CODE_0,  16, temp)) {
		dbgidx += SPRINTF(dbglog + dbgidx, ", C x%08X", temp[0]);
	} else {
		dbgidx += SPRINTF(dbglog + dbgidx, ", C err");
	}

	if (NO_DEMOD_ERROR == DEMOD_L0_ReadCommandBytes(core->chip, REG_INFO_ERROR_0,  16, temp)) {
		dbgidx += SPRINTF(dbglog + dbgidx, ", E x%08X", temp[0]);
		if (temp[0] != 0)
			dbgidx += SPRINTF(dbglog + dbgidx, ", x%08X, %u, %08X, %08X, %08X", temp[0] >> 16, temp[0] & 0xFFFF, temp[1], temp[2], temp[3]);
	} else {
		dbgidx += SPRINTF(dbglog + dbgidx, ", E err");
	}

	return dbgidx;
}

/***********************************************************************************************************************
  DEMOD_L1_API_STATUS function
  Use:        make log message about DEMOD configuration & Status
  Returns:    log message length
  Parameter:  error_code the error code.
 ***********************************************************************************************************************/

int DEMOD_L1_API_Status (LX_DEMOD_L1_Context * core, char * dbglog) {
	int dbgidx = 0;
	UINT32 temp[4] = {0, 0, 0, 0};

	dbgidx += SPRINTF(dbglog + dbgidx,
		"DEMOD_L1_COMMAND :\n"
		"\tapi standard %s(0x%X)\n"
		"\trsp standard %s(0x%X), lock_fec 0x%X, never_lock 0x%X\n\n",
		DEMOD_L1_API_StandardName(core->standard), core->standard,
		DEMOD_L1_API_StandardName(core->rsp->dd_status.reply_operMod), core->rsp->dd_status.reply_operMod,
		core->rsp->dd_status.lock_fec, core->rsp->dd_status.neverLock);

	dbgidx += SPRINTF(dbglog + dbgidx,
		"\tcmd req %8u, err %8u, out %8u, val %8u, inv %8u, ret %8u\n"
		"\tcmd res %8u, err %8u, out %8u, val %8u, inv %8u, skip %7u\n\n",
		core->cmd_req_cnt, core->cmd_req_err_cnt, core->cmd_req_out_cnt, core->cmd_req_val_cnt, core->cmd_req_inv_cnt, core->cmd_req_ret_cnt,
		core->cmd_res_cnt, core->cmd_res_err_cnt, core->cmd_res_out_cnt, core->cmd_res_val_cnt, core->cmd_res_inv_cnt, core->cmd_res_skp_cnt);


	dbgidx += SPRINTF(dbglog + dbgidx,
		"\tfw start %7u, load %7u, state %6u\n\n", core->fw_start_cnt, core->fw_load_cnt, core->fw_state);

	dbgidx += SPRINTF(dbglog + dbgidx, "DEMOD_L1_API :\n\t");
#if defined(DEMOD_CONFIG_EXT)
	dbgidx += SPRINTF(dbglog + dbgidx, "Ext ");
#endif
#if defined(DEMOD_CONFIG_SOC)
	dbgidx += SPRINTF(dbglog + dbgidx, "SoC ");
#endif

	dbgidx += SPRINTF(dbglog + dbgidx, "IPC ");

	dbgidx += SPRINTF(dbglog + dbgidx, "DDR ");

#if defined(DEMOD_CONFIG_POLL)
	dbgidx += SPRINTF(dbglog + dbgidx, "POLL ");
#endif
	dbgidx += SPRINTF(dbglog + dbgidx, "\n\n");

	if (NO_DEMOD_ERROR == DEMOD_L0_ReadCommandBytes(core->chip, REG_FW_VER, 4, temp)) {
		dbgidx += SPRINTF(dbglog + dbgidx, "\tVER   0x%08X (@0x%04X)\n", temp[0], REG_FW_VER);
	} else {
		dbgidx += SPRINTF(dbglog + dbgidx, "\tfailed get VER\n");
	}

	if (NO_DEMOD_ERROR == DEMOD_L0_ReadCommandBytes(core->chip, REG_FW_DATE, 4, temp)) {
		dbgidx += SPRINTF(dbglog + dbgidx, "\tDATE  0x%08X (@0x%04X)\n", temp[0], REG_FW_DATE);
	} else {
		dbgidx += SPRINTF(dbglog + dbgidx, "\tfailed get DATE\n");
	}

	if (NO_DEMOD_ERROR == DEMOD_L0_ReadCommandBytes(core->chip, REG_FW_STATE, 4, temp)) {
		dbgidx += SPRINTF(dbglog + dbgidx, "\tSTATE 0x%08X (@0x%04X)\n", temp[0], REG_FW_STATE);
	} else {
		dbgidx += SPRINTF(dbglog + dbgidx, "\tfailed get STATE\n");
	}

	dbgidx += SPRINTF(dbglog + dbgidx, "\n");

	if (NO_DEMOD_ERROR == DEMOD_L0_ReadCommandBytes(core->chip, REG_INFO_CODE_0,  16, temp)) {
		dbgidx += SPRINTF(dbglog + dbgidx, "\tCODE  0x%04X, %4u, 0x%08X, 0x%08X, 0x%08X\n", temp[0] >> 16, temp[0] & 0xFFFF, temp[1], temp[2], temp[3]);
	} else {
		dbgidx += SPRINTF(dbglog + dbgidx, "\tfailed get CODE\n");
	}

	if (NO_DEMOD_ERROR == DEMOD_L0_ReadCommandBytes(core->chip, REG_INFO_ERROR_0, 16, temp)) {
		if ((temp[0] >> 16) == 0xFFFF)
			dbgidx += SPRINTF(dbglog + dbgidx, "\tERROR 0x%08X, 0x%08X, 0x%08X, 0x%08X\n", temp[0], temp[1], temp[2], temp[3]);
		else
			dbgidx += SPRINTF(dbglog + dbgidx, "\tERROR 0x%04X, %4u, 0x%08X, 0x%08X, 0x%08X\n", temp[0] >> 16, temp[0] & 0xFFFF, temp[1], temp[2], temp[3]);

	} else {
		dbgidx += SPRINTF(dbglog + dbgidx, "\tfailed get ERROR\n");
	}

	dbgidx += SPRINTF(dbglog + dbgidx, "\n\t");

	dbgidx += SPRINTF(dbglog + dbgidx, "DDR ");

	if (NO_DEMOD_ERROR == DEMOD_L0_ReadCommandBytes(core->chip, REG_CLK_TYPE, 4, temp)) {
		switch (temp[0]) {
		case 0:
			dbgidx += SPRINTF(dbglog + dbgidx, "clk type Invalid, 0x%x (@0x%04x)\n", temp[0], REG_CLK_TYPE);
			break;
		case 1:
			dbgidx += SPRINTF(dbglog + dbgidx, "clk type TER, 0x%x (@0x%04x)\n", temp[0], REG_CLK_TYPE);
			break;
		case 2:
			dbgidx += SPRINTF(dbglog + dbgidx, "clk type SAT, 0x%x (@0x%04x)\n", temp[0], REG_CLK_TYPE);
			break;
		default:
			dbgidx += SPRINTF(dbglog + dbgidx, "clk type ALL, %u (@0x%04x)\n", temp[0], REG_CLK_TYPE);
			break;
		}
	} else {
		dbgidx += SPRINTF(dbglog + dbgidx, "failed get clk type\n");
	}


	dbgidx += SPRINTF(dbglog + dbgidx, "\n");

	return dbgidx;
}


/***********************************************************************************************************************
  DEMOD_L1_API_DUMP function
  Use:        kdriver <-> mcu memroy dump
  Returns:    log message length
  Parameter:  error_code the error code.
 ***********************************************************************************************************************/

int DEMOD_L1_API_Dump (LX_DEMOD_L1_Context * core, char * dbglog) {
	static char btmp[DEMOD_REGMAP_SIZE];
	int dbgidx = 0;

	UINT32 * wptr = (UINT32 *)btmp;

	memset(btmp, 0, DEMOD_REGMAP_SIZE);
	if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(core->chip, DEMOD_REGMAP_BASE, DEMOD_REGMAP_SIZE, wptr))
		return -ERROR_DEMOD_READ;

	dbgidx += SPRINTF(dbglog + dbgidx, "memory dump sz %d\n", DEMOD_REGMAP_SIZE);

	dbgidx += DEMOD_DUMP_WORD(dbglog + dbgidx, wptr, DEMOD_REGMAP_SIZE);

	return dbgidx;
}

/***********************************************************************************************************************
  DEMOD_L1_API_ISREADY function
  Use:        check for firmware code start & ready
  Returns:    0 if fw start & ready
  Parameter:  error_code the error code.
 ***********************************************************************************************************************/

int DEMOD_L1_API_IsReady(LX_DEMOD_L1_Context * core) {
	UINT32 fw_ver 	= 0;
	UINT32 fw_date 	= 0;
	UINT32 fw_state = 0;

	if (NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(core->chip, REG_FW_STATE, 4, &fw_state))
		return -ERROR_DEMOD_READ;

	if (NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(core->chip, REG_FW_VER, 4, &fw_ver))
		return -ERROR_DEMOD_READ;

	if (NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(core->chip, REG_FW_DATE, 4, &fw_date))
		return -ERROR_DEMOD_READ;

	//DEMOD_INFO("ready: ver 0x%08x (@0x%04x), date %08x (@0x%04x)), state 0x%x (@0x%04x))\n", fw_ver, REG_FW_VER, fw_date, REG_FW_DATE, fw_state, REG_FW_STATE);

	if ((fw_ver > 0x20a00000) && (fw_date > 0x20190101)) {
		//DEMOD_NOTI("ready: ver 0x%08x (@0x%04x), date %08x (@0x%04x)), state 0x%x (@0x%04x))\n", fw_ver, REG_FW_VER, fw_date, REG_FW_DATE, fw_state, REG_FW_STATE);
		core->fw_ver = fw_ver;
		core->fw_date = fw_date;
		return NO_DEMOD_ERROR;
	}
	return -ERROR_DEMOD_STARTING_FIRMWARE;
}

/***********************************************************************************************************************
  DEMOD_L1_SET_FREQUENCY function
  Use:        set firmware ref freq instead of DEMOD_L1_API_SetType
  Returns:    0 if no error
  Parameter:  error_code the error code.
 ***********************************************************************************************************************/

int DEMOD_L1_API_SetFrequency (LX_DEMOD_L1_Context * core, UINT32 fw_clk, UINT32 adc_clk) {
	/* get kdrv time since boot */
	unsigned int systime = DEMOD_L0_SystemClock() / 1000000;

	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_SYS_TIME, 4, &systime))
		return -ERROR_DEMOD_WRITE;
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_ADC_TYPE, 4, &adc_clk))
		return -ERROR_DEMOD_WRITE;

	/* have to write fw_clk after sys_time & adc_type */
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_CLK_TYPE, 4, &fw_clk))
		return -ERROR_DEMOD_WRITE;

	return NO_DEMOD_ERROR;
}

/***********************************************************************************************************************
  DEMOD_L1_SET_DEBUG function
  Use:        set FW debug mode & log levle
  Returns:    0 if no error
  Parameter:  error_code the error code.
 ***********************************************************************************************************************/

int DEMOD_L1_API_SetDebug(LX_DEMOD_L1_Context * core, demod_fw_debug mode, demod_fw_loglevel loglevel) {
	UINT32 wtemp;

	wtemp = mode;
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_DEBUG_MODE, 4, &wtemp))
		return -ERROR_DEMOD_WRITE;
	wtemp = loglevel;
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_DEBUG_FLAG, 4, &wtemp))
		return -ERROR_DEMOD_WRITE;

	return NO_DEMOD_ERROR;
}

/***********************************************************************************************************************
  DEMOD_L1_START_FIRMWARE function
  Use:        Patch information function
              Used to send a number of bytes to the LGDBB. Useful to download the firmware.
  Returns:    0 if no error
  Parameter:  error_code the error code.
 ***********************************************************************************************************************/

int DEMOD_L1_API_StartFirmware (LX_DEMOD_L1_Context * core)
{
	UINT32 wtemp;

	core->chip->i2c_indirect = 0;
	core->chip->fw_done = 1;

	wtemp = 0;
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_MCU_STALL, 4, &wtemp))
		return -ERROR_DEMOD_STARTING_FIRMWARE;
	wmb();
	
	core->fw_state = DEMOD_FW_STATE_START;
	core->fw_start_cnt++;

	return NO_DEMOD_ERROR;
}

/***********************************************************************************************************************
  DEMOD_L1_INIT_FIRMWARE function
  Use:        Init Firmware Information Register
  Returns:    0 if no error
  Parameter:  error_code the error code.
 ***********************************************************************************************************************/

int DEMOD_L1_API_InitFirmware (LX_DEMOD_L1_Context * core, UINT32 fw_clk, UINT32 adc_clk)
{
	UINT32 wtemp[4] = {0, 0, 0, 0};
	UINT32 fw_type = 0;

	/* clear inforamation register */
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_INFO_CODE_0, 16, wtemp))
		return -ERROR_DEMOD_WRITE;

	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_INFO_ERROR_0, 16, wtemp))
		return -ERROR_DEMOD_WRITE;

//	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_DEAD_0, 4, wtemp))
//		return -ERROR_DEMOD_WRITE;

	/* MCU FW control register init */
	DEMOD_L1_API_SetFrequency(core, fw_clk, adc_clk);

	DEMOD_L1_API_SetDebug(core, DEMOD_FW_DEBUG_IPC, DEMOD_FW_LOGLV_DEFAULT);

	if (NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(core->chip, REG_CLK_TYPE, 4, (UINT8*)&fw_type))
		return -ERROR_DEMOD_READ;
	DEMOD_INFO("check: type %d\n", fw_type);

	return NO_DEMOD_ERROR;
}


/***********************************************************************************************************************
  DEMOD_L1_INIT_FIRMWARE_DDR function
  Use:        Init Firmware Information Register
  Returns:    0 if no error
  Parameter:  error_code the error code.
 ***********************************************************************************************************************/

int DEMOD_L1_API_InitFirmware_DDR (LX_DEMOD_L1_Context * core, UINT32 fw_clk, UINT32 adc_clk)
{
	int ret;
	UINT32 wtemp = 0;

	ret = DEMOD_L1_API_InitFirmware(core, fw_clk, adc_clk);
	if (NO_DEMOD_ERROR != ret)
		return ret;

	/* only set fw_start in 1st fw init with DEMOD_CONFIG_DDR */
	/* xtensa fw address */
	wtemp = 0x50000000;
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_FW_DL_BASE, 4, &wtemp))	/* 0x5430 */
		return -ERROR_DEMOD_WRITE;

	/* fw loaded address @ddr, cpu side */
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_FW_DL_ADDR, 4, &gMemCfgDEMOD_FW.memory_base))
		return -ERROR_DEMOD_WRITE;
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_FW_DL_ADDR, 4, &wtemp)) /* 0x5448 */
		return -ERROR_DEMOD_WRITE;
#endif

	/* select start vector 0 (xtensa start @0x50000000) */

	if (NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(core->chip, REG_MCU_STARTVECSEL, 4, &wtemp))
		return -ERROR_DEMOD_READ;
	wtemp &= ~0x1;	// clear 0th bit
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_MCU_STARTVECSEL, 4, &wtemp))
		return -ERROR_DEMOD_WRITE;

	/* InitFirmware_DDR called only at FW load & init (not FW reset) */
	core->fw_load_cnt++;

	return NO_DEMOD_ERROR;
}

/***********************************************************************************************************************
  DEMOD_L1_CLEAR_FIRMWARE function
  Use:        DEMOD MCU set stall to MCU STOP
  Returns:    0 if no error
  Parameter:  error_code the error code.
 ***********************************************************************************************************************/
int DEMOD_L1_API_FinishFirmware (LX_DEMOD_L1_Context * core)
{
	UINT32 wtemp = 0;

	/* fw state set to STOP */
	core->fw_state = DEMOD_FW_STATE_STOP;
	core->fw_ver = 0;
	core->fw_date = 0;

	//DEMOD_L1_IPC_Wait_Cancel(core);
	//DEMOD_L0_system_wait(10);

	/* clear fw_clk, adc_clk */
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_CLK_TYPE, 4, &wtemp))
		return -ERROR_DEMOD_WRITE;

	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_ADC_TYPE, 4, &wtemp))
		return -ERROR_DEMOD_WRITE;

	/* clear fw state, fw ver, fw date*/
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_FW_STATE, 4, &wtemp))
		return -ERROR_DEMOD_WRITE;

	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_FW_VER, 4, &wtemp))
		return -ERROR_DEMOD_WRITE;

	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_FW_DATE, 4, &wtemp))
		return -ERROR_DEMOD_WRITE;

	return NO_DEMOD_ERROR;
}

/***********************************************************************************************************************
  DEMOD_L1_STOP_FIRMWARE function
  Use:        DEMOD MCU set stall to MCU STOP
  Returns:    0 if no error
  Parameter:  error_code the error code.
 ***********************************************************************************************************************/
int DEMOD_L1_API_StopFirmware (LX_DEMOD_L1_Context * core)
{
	UINT32 wtemp = 0;

	/* MCU set stall */
	wtemp = 1;
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_MCU_STALL, 4, &wtemp))
		return -ERROR_DEMOD_WRITE;

	return NO_DEMOD_ERROR;
}

/***********************************************************************************************************************
  DEMOD_L1_SET_TRACE function
  Use:        enable MCU fw program counter trace
  Returns:    0 if no error
  Parameter:  error_code the error code.
 ***********************************************************************************************************************/

int DEMOD_L1_API_SetTrace (LX_DEMOD_L1_Context * core, UINT32 enable)
{
	UINT32 wtemp;
	if (enable)
		wtemp = 1;
	else
		wtemp = 0;

	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_TRACE_EN, 4, &wtemp))
		return -ERROR_DEMOD_FAULT;

	return NO_DEMOD_ERROR;
}

/***********************************************************************************************************************
  DEMOD_L1_SET_TRACE function
  Use:        enable MCU fw program counter trace
  Returns:    0 if no error
  Parameter:  error_code the error code.
 ***********************************************************************************************************************/

int DEMOD_L1_API_GetTrace (LX_DEMOD_L1_Context * core, UINT32 * ptrace, UINT32 *pdata, UINT32 *pstate)
{
	UINT32 wtemp;
	if (NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(core->chip, REG_TRACE_EN, 4, &wtemp))
		return -ERROR_DEMOD_FAULT;

	if (!wtemp) {
		DEMOD_NOTI("Trace is not activated\n");
	}

	if (NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(core->chip, REG_TRACE_PC, 4, ptrace))
		return -ERROR_DEMOD_FAULT;

	if (NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(core->chip, REG_TRACE_DATA, 4, pdata))
		return -ERROR_DEMOD_FAULT;

	if (NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(core->chip, REG_TRACE_FWDN_DONE, 4, pstate))
		return -ERROR_DEMOD_FAULT;

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
char * DEMOD_L1_API_Error_Text (int error_code)
{
	if (error_code < 0) error_code = -error_code;

	switch (error_code)
	{
		case NO_DEMOD_ERROR                     	: {return (char*)"No DEMOD error";}
		case ERROR_DEMOD_ALLOCATING_CONTEXT   		: {return (char*)"Error while allocating DEMOD context";}
		case ERROR_DEMOD_SENDING_COMMAND        	: {return (char*)"Error while sending DEMOD command";}
		case ERROR_DEMOD_CTS_TIMEOUT            	: {return (char*)"DEMOD CTS timeout";}
		case ERROR_DEMOD_ERROR                 		: {return (char*)"DEMOD Error (status 'err' bit 1)";}
		case ERROR_DEMOD_POLLING_CTS            	: {return (char*)"DEMOD Error while polling CTS";}
		case ERROR_DEMOD_POLLING_RESPONSE      		: {return (char*)"DEMOD Error while polling response";}
		case ERROR_DEMOD_LOADING_FIRMWARE       	: {return (char*)"DEMOD Error while loading firmware";}
		case ERROR_DEMOD_LOADING_BOOTBLOCK      	: {return (char*)"DEMOD Error while loading bootblock";}
		case ERROR_DEMOD_STARTING_FIRMWARE      	: {return (char*)"DEMOD Error while starting firmware";}
		case ERROR_DEMOD_SW_RESET              		: {return (char*)"DEMOD Error during software reset";}
		case ERROR_DEMOD_INCOMPATIBLE_PART      	: {return (char*)"DEMOD Error Incompatible part";}
		case ERROR_DEMOD_DISEQC_BUS_NOT_READY		: {return (char*)"DISEQC but not ready";}
		case ERROR_DEMOD_OS_LOCK			: {return (char*)"OS Lock failed";}
		case ERROR_DEMOD_PARAMETER			: {return (char*)"DEMOD Parameter Error";}
		case ERROR_DEMOD_PARAMETER_OUT_OF_RANGE		: {return (char*)"DEMOD parameter(s) out of range";}
		case ERROR_DEMOD_RESULT				: {return (char*)"DEMOD Result Error";}
		case ERROR_DEMOD_RESULT_NOT_READY		: {return (char*)"DEMOD Result Not Ready";}
		case ERROR_DEMOD_RESULT_UNKNOWN			: {return (char*)"DEMOD Result Unknown";}
		case ERROR_DEMOD_IPC				: {return (char*)"IPC error";}
		case ERROR_DEMOD_IPC_BUSY			: {return (char*)"IPC busyr";}
		case ERROR_DEMOD_IPC_EMPTY			: {return (char*)"IPC buffer empty";}
		case ERROR_DEMOD_IPC_TIMEOUT			: {return (char*)"IPC timeout";}
		case ERROR_DEMOD_IPC_INVALID			: {return (char*)"IPC invalid";}
		case ERROR_DEMOD_IPC_NOT_SUPPORT		: {return (char*)"IPC not support";}
		case ERROR_DEMOD_IPC_FALUT			: {return (char*)"IPC fault";}
		case ERROR_DEMOD_FW				: {return (char*)"FW error";}
		case ERROR_DEMOD_FW_INIT			: {return (char*)"FW error init";}
		case ERROR_DEMOD_FW_NOT_READY			: {return (char*)"FW is not ready";}
		case ERROR_DEMOD_FW_TIMEOUT			: {return (char*)"FW timeout";}
		case ERROR_DEMOD_FW_FAULT			: {return (char*)"FW fault";}
		case ERROR_DEMOD_INVALID			: {return (char*)"DEMOD invalid";}
		case ERROR_DEMOD_UNKNOWN_COMMAND      		: {return (char*)"DEMOD Error unknown command";}
		case ERROR_DEMOD_UNKNOWN_PROPERTY     		: {return (char*)"DEMOD Error unknown property";}
		case ERROR_DEMOD_READ				: {return (char*)"DEMOD Error read";}
		case ERROR_DEMOD_WRITE				: {return (char*)"DEMOD Error write";}
		case ERROR_DEMOD_PTRNULL			: {return (char*)"DEMOD Error ptrnull";}
		case ERROR_DEMOD_FAULT				: {return (char*)"DEMOD fault";}
		default                                		: {return (char*)"Unknown DEMOD error code";}
	}
}

/************************************************************************************************************************
  DEMOD_L1_API_StandardName function
  Use:        standard text retrieval function
              Used to retrieve the standard text used by the Si2169C
  Parameter:  standard, the value of the standard
************************************************************************************************************************/
char * DEMOD_L1_API_StandardName (UINT8 standard)
{
	switch (standard)
	{
		case DEMOD_DD_MODE_PROP_MODULATION_VSB   	: {return (char*)"VSB";}
		case DEMOD_DD_MODE_PROP_MODULATION_QAM   	: {return (char*)"QAM";}
		case DEMOD_DD_MODE_PROP_MODULATION_ISDBT  	: {return (char*)"ISDB-T";}
		case DEMOD_DD_MODE_PROP_MODULATION_ATSC3	: {return (char*)"ATSC3";}
		case DEMOD_DD_MODE_PROP_MODULATION_DVBT 	: {return (char*)"DVB-T";}
		case DEMOD_DD_MODE_PROP_MODULATION_DVBT2	: {return (char*)"DVB-T2";}
		case DEMOD_DD_MODE_PROP_MODULATION_DVBC		: {return (char*)"DVB-C";}
		case DEMOD_DD_MODE_PROP_MODULATION_DVBC2	: {return (char*)"DVB-C2";}
		case DEMOD_DD_MODE_PROP_MODULATION_DVBS		: {return (char*)"DVB-S";}
		case DEMOD_DD_MODE_PROP_MODULATION_DVBS2	: {return (char*)"DVB-S2";}
		case DEMOD_DD_MODE_PROP_MODULATION_DTMB		: {return (char*)"DTMB";}
		default						: {return (char*)"UNKNOWN";}
	}
}




/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_API_BaseAddr_AXI.
 * Set base address for AXI memory write.
 *
 * @param *core		[IN] LX_DEMOD_L1_Context
 * @param fw_table[] 	[IN] LX_DEMOD_FW_STRUCT
 * @param baseAddr 	[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_API_BaseAddr_AXI (LX_DEMOD_L1_Context * core, UINT32 baseAddr)
{
	int retc;

	DEMOD_PRINT("[DEMOD_API] Start\n");

	retc = DEMOD_L1_SET_DD_ISDBT_BASEADDR_AXI(core, baseAddr);

	if (retc != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_SET_DD_ISDBT_BASEADDR_AXI() BecauseOf %s\n", DEMOD_L1_API_Error_Text(retc));
	  	return -ERROR_DEMOD_WRITE;
	}

	return NO_DEMOD_ERROR;
}



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_API_EMERGENCY_ALARM.
 * Get the emergency alarm flag.
 *
 * @param *core		[IN] LX_DEMOD_L1_Context
 * @param fw_table[] 	[IN] LX_DEMOD_FW_STRUCT
 * @param eAlarm 	[IN] UINT8*
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_API_Emergency_Alarm (LX_DEMOD_L1_Context * core, UINT8 *eAlarm)
{
	int retc;

	DEMOD_PRINT("[DEMOD_API] Start\n");

	retc = DEMOD_L1_GET_DD_Reg(core,  0x00, 0xde, 1);

	*eAlarm = (core->rsp->dd_get_reg.mData[0] >> 5) & 0x1;

	if (retc != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, BecauseOf %s\n", DEMOD_L1_API_Error_Text(retc));
	  	return -ERROR_DEMOD_WRITE;
	}

	return NO_DEMOD_ERROR;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_API_DVBT2_BaseAddr_AXI.
 * Set base address for AXI memory write.
 *
 * @param *core 	[IN] LX_DEMOD_L1_Context
 * @param fw_table[] 	[IN] LX_DEMOD_FW_STRUCT
 * @param baseAddr1	[IN] UINT32
 * @param baseAddr2	[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_API_DVBT2_BaseAddr_AXI (LX_DEMOD_L1_Context * core, UINT32 baseAddr1, UINT32 baseAddr2)
{
	int retc;

	DEMOD_PRINT("[DEMOD_API] Start\n");

	retc = DEMOD_L1_SET_DD_DVBT2_BASEADDR_AXI(core, baseAddr1, baseAddr2);

	if (retc != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_SET_DD_DVBT2_BASEADDR_AXI() BecauseOf %s\n", DEMOD_L1_API_Error_Text(retc));
	  	return -ERROR_DEMOD_WRITE;
	}

	return NO_DEMOD_ERROR;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_API_DVB_BaseAddr_AXI.
 * Set base address for AXI memory write.
 *
 * @param *core 	[IN] LX_DEMOD_L1_Context
 * @param fw_table[] 	[IN] LX_DEMOD_FW_STRUCT
 * @param baseAddr1	[IN] UINT32
 * @param baseAddr2	[IN] UINT32
 * @param baseAddr3	[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_API_DVB_BaseAddr_AXI (LX_DEMOD_L1_Context * core, UINT32 baseAddr1, UINT32 baseAddr2, UINT32 baseAddr3)
{
	int retc;

	DEMOD_PRINT("[DEMOD_API] Start\n");

	retc = DEMOD_L1_SET_DD_DVB_BASEADDR_AXI(core, baseAddr1, baseAddr2, baseAddr3);

	if (retc != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_SET_DD_DVB_BASEADDR_AXI() BecauseOf %s\n", DEMOD_L1_API_Error_Text(retc));
	  	return -ERROR_DEMOD_WRITE;
	}

	return NO_DEMOD_ERROR;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_API_DTMB_BaseAddr_AXI.
 * Set base address for AXI memory write.
 *
 * @param *core 	[IN] LX_DEMOD_L1_Context
 * @param fw_table[] 	[IN] LX_DEMOD_FW_STRUCT
 * @param baseAddr 	[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_API_DTMB_BaseAddr_AXI (LX_DEMOD_L1_Context * core, UINT32 baseAddr)
{
	int retc;

	DEMOD_PRINT("[DEMOD_API] Start\n");

	retc = DEMOD_L1_SET_DD_DTMB_BASEADDR_AXI(core, baseAddr);

	if (retc != NO_DEMOD_ERROR) {
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_SET_DD_DTMB_BASEADDR_AXI() BecauseOf %s\n", DEMOD_L1_API_Error_Text(retc));
	  	return -ERROR_DEMOD_WRITE;
	}

	return NO_DEMOD_ERROR;
}
