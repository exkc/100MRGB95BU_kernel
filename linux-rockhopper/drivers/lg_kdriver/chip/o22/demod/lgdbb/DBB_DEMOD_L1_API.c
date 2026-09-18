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
#define DEMOD_TAG "[L1.API] "

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
	memset(core->cmd, 0, sizeof(LX_DEMOD_L1_CmdObj));
	memset(core->rsp, 0, sizeof(LX_DEMOD_L1_CmdReplyObj));
	memset(core->prop, 0, sizeof(LX_DEMOD_L1_PropObj));

	DEMOD_L1_IPC_Reset(core);

	core->fw_state = DEMOD_FW_STATE_STOP;

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

	DEMOD_PRINT("Start\n");

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
			DEMOD_DEBUG("fw download is Done\n");
		} else if (DEMOD_L0_system_time() - load_start_ms >= 50) {
			DEMOD_ERROR("fw download timeout\n");
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

	DEMOD_INFO("took %u ms\n", DEMOD_L0_system_time() - load_start_ms);

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

	demod_fw_status_t demod_fw_status;
	memset(&demod_fw_status, 0, sizeof(demod_fw_status_t));

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

	//dbgidx += SPRINTF(dbglog + dbgidx, "\n");
	if (NO_DEMOD_ERROR == DEMOD_L0_ReadCommandBytes(core->chip, DDR_ERROR_INFO_BASE + 16,  16, temp)) {
		dbgidx += SPRINTF(dbglog + dbgidx, "pkt %u, %u, %u, %u, ", temp[0], temp[1], temp[2], temp[3]);
	} else {
		dbgidx += SPRINTF(dbglog + dbgidx, "pkt err,");
	}

	if (NO_DEMOD_ERROR == DEMOD_L0_ReadCommandBytes(core->chip, DDR_ERROR_INFO_BASE,  16, temp)) {
		dbgidx += SPRINTF(dbglog + dbgidx, "err %u, %u, %u, %u", temp[0], temp[1], temp[2], temp[3]);
	} else {
		dbgidx += SPRINTF(dbglog + dbgidx, "err err");
	}
	dbgidx += SPRINTF(dbglog + dbgidx, ", ");

	if (NO_DEMOD_ERROR == DEMOD_L0_ReadCommandBytes(core->chip, DDR_DEBUG_INFO_BASE,  sizeof(demod_fw_status_t), &demod_fw_status)) {
		dbgidx += SPRINTF(dbglog + dbgidx, "fw mod 0x%02x, lock %u, %u, pe %u, rst 0x%04x, ps 0x%x,",
												demod_fw_status.modulation,
												demod_fw_status.lock_fec, demod_fw_status.neverLock,
												demod_fw_status.pe,
												demod_fw_status.reset_flag,
												demod_fw_status.power_save);
		dbgidx += SPRINTF(dbglog + dbgidx, "fw rst cnt  %u, %u, %u, %u, %u, %u, %u, %u, %u, self cnt %u, %u, %u, %u, %u, %u, %u, %u, ",
												demod_fw_status.reset_cnt.MAIN, demod_fw_status.reset_cnt.SYNC, demod_fw_status.reset_cnt.SYNC3A,
												demod_fw_status.reset_cnt.SYNC3B, demod_fw_status.reset_cnt.SYNC3C, demod_fw_status.reset_cnt.SAT_EQ,
												demod_fw_status.reset_cnt.SAT_SIGSRCH, demod_fw_status.reset_cnt.T2_PLPSEL, demod_fw_status.reset_cnt.TPRST,
												demod_fw_status.selfrst_cnt.selfrst1, demod_fw_status.selfrst_cnt.selfrst2, demod_fw_status.selfrst_cnt.selfrst3, demod_fw_status.selfrst_cnt.selfrst4,
												demod_fw_status.selfrst_cnt.selfrst5, demod_fw_status.selfrst_cnt.selfrst6, demod_fw_status.selfrst_cnt.selfrst7, demod_fw_status.selfrst_cnt.selfrst8);
		dbgidx += SPRINTF(dbglog + dbgidx, "fw last cmd %02x, %u, %u,",
												demod_fw_status.last_cmd, demod_fw_status.last_cmd_seq, demod_fw_status.last_cmd_state);

	} else {
		dbgidx += SPRINTF(dbglog + dbgidx, "get fw status err\n");
	}
	dbgidx += SPRINTF(dbglog + dbgidx, "\n");

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

	demod_fw_status_t demod_fw_status;
	memset(&demod_fw_status, 0, sizeof(demod_fw_status_t));

	dbgidx += SPRINTF(dbglog + dbgidx,
		"DEMOD_L1_COMMAND :\n"
		"\tapi standard %s(0x%X)\n"
		"\trsp standard %s(0x%X), lock_fec 0x%X, never_lock 0x%X\n\n",
		DEMOD_L1_API_Modulation_Text(core->standard), core->standard,
		DEMOD_L1_API_Modulation_Text(core->rsp->dd_status.reply_operMod), core->rsp->dd_status.reply_operMod,
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


	dbgidx += SPRINTF(dbglog + dbgidx, "\nPacket Monitor :\n");
	if (NO_DEMOD_ERROR == DEMOD_L0_ReadCommandBytes(core->chip, DDR_ERROR_INFO_BASE + 16,  16, temp)) {
		dbgidx += SPRINTF(dbglog + dbgidx, "\tpktcnt %8u, %8u, %8u, %8u\n", temp[0], temp[1], temp[2], temp[3]);
	} else {
		dbgidx += SPRINTF(dbglog + dbgidx, "\tfailed get pktcnt\n");
	}

	if (NO_DEMOD_ERROR == DEMOD_L0_ReadCommandBytes(core->chip, DDR_ERROR_INFO_BASE,  16, temp)) {
		dbgidx += SPRINTF(dbglog + dbgidx, "\terrcnt %8u, %8u, %8u, %8u\n", temp[0], temp[1], temp[2], temp[3]);
	} else {
		dbgidx += SPRINTF(dbglog + dbgidx, "\tfailed get errcnt\n");
	}
	dbgidx += SPRINTF(dbglog + dbgidx, "\n");

	dbgidx += SPRINTF(dbglog + dbgidx, "\nFW Status :\n");
	if (NO_DEMOD_ERROR == DEMOD_L0_ReadCommandBytes(core->chip, DDR_DEBUG_INFO_BASE,  sizeof(demod_fw_status_t), &demod_fw_status)) {
		dbgidx += SPRINTF(dbglog + dbgidx, "\t" "mod 0x%02x, lock %u, %u, pe %u, rst 0x%04x, ps 0x%x\n",
												demod_fw_status.modulation,
												demod_fw_status.lock_fec, demod_fw_status.neverLock,
												demod_fw_status.pe,
												demod_fw_status.reset_flag,
												demod_fw_status.power_save);
		dbgidx += SPRINTF(dbglog + dbgidx, "\t" "rst cnt  %u, %u, %u, %u, %u, %u, %u, %u, %u\n",
												demod_fw_status.reset_cnt.MAIN, demod_fw_status.reset_cnt.SYNC, demod_fw_status.reset_cnt.SYNC3A,
												demod_fw_status.reset_cnt.SYNC3B, demod_fw_status.reset_cnt.SYNC3C, demod_fw_status.reset_cnt.SAT_EQ,
												demod_fw_status.reset_cnt.SAT_SIGSRCH, demod_fw_status.reset_cnt.T2_PLPSEL, demod_fw_status.reset_cnt.TPRST);
		dbgidx += SPRINTF(dbglog + dbgidx, "\t" "self cnt %u, %u, %u, %u, %u, %u, %u, %u\n",
												demod_fw_status.selfrst_cnt.selfrst1, demod_fw_status.selfrst_cnt.selfrst2, demod_fw_status.selfrst_cnt.selfrst3, demod_fw_status.selfrst_cnt.selfrst4,
												demod_fw_status.selfrst_cnt.selfrst5, demod_fw_status.selfrst_cnt.selfrst6, demod_fw_status.selfrst_cnt.selfrst7, demod_fw_status.selfrst_cnt.selfrst8);
		dbgidx += SPRINTF(dbglog + dbgidx, "\t" "last cmd %02x, %u, %u\n",
												demod_fw_status.last_cmd, demod_fw_status.last_cmd_seq, demod_fw_status.last_cmd_state);

	} else {
		dbgidx += SPRINTF(dbglog + dbgidx, "\tfailed get fw status\n");
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

	if ((fw_ver > 0x20a00000) && (fw_ver < 0xa0000000) && (fw_date > 0x20190101) && (fw_date < 0x20991231)) {
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
	UINT32 systime = (UINT32)(DEMOD_L0_SystemClock() / 1000000);

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

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	/* workaround for boot time system crash */
	/* if tuner is activated before demod ip & fw ready, demod ip can access invalid address */
	/* have to set axi baseaddr of all modulations as allocated DDR address */
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_ISDBT_BADDR, 4, &gMemCfgDEMOD.memory_base))
		return -ERROR_DEMOD_WRITE;
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_T2_BADDR, 4, &gMemCfgDEMOD.memory_base))
		return -ERROR_DEMOD_WRITE;
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_DJB_BADDR, 4, &gMemCfgDEMOD.memory_base))
		return -ERROR_DEMOD_WRITE;
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_RISIC_W_BADDR, 4, &gMemCfgDEMOD.memory_base))
		return -ERROR_DEMOD_WRITE;
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_RISIC_R_BADDR, 4, &gMemCfgDEMOD.memory_base))
		return -ERROR_DEMOD_WRITE;
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_DTMB_BADDR, 4, &gMemCfgDEMOD.memory_base))
		return -ERROR_DEMOD_WRITE;
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_ATSC3_CSTS_BADDR, 4, &gMemCfgDEMOD.memory_base))
		return -ERROR_DEMOD_WRITE;
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_ATSC3_FDI_BADDR, 4, &gMemCfgDEMOD.memory_base))
		return -ERROR_DEMOD_WRITE;
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_ATSC3_L1D_BADDR, 4, &gMemCfgDEMOD.memory_base))
		return -ERROR_DEMOD_WRITE;
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_ATSC3_NOTDI_BADDR, 4, &gMemCfgDEMOD.memory_base))
		return -ERROR_DEMOD_WRITE;
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_ATSC3_CTDI0_BADDR, 4, &gMemCfgDEMOD.memory_base))
		return -ERROR_DEMOD_WRITE;
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_ATSC3_CTDI1_BADDR, 4, &gMemCfgDEMOD.memory_base))
		return -ERROR_DEMOD_WRITE;
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_ATSC3_CTBDI_BADDR, 4, &gMemCfgDEMOD.memory_base))
		return -ERROR_DEMOD_WRITE;
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_ATSC3_CDL_BADDR, 4, &gMemCfgDEMOD.memory_base))
		return -ERROR_DEMOD_WRITE;
#endif

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

	DEMOD_PRINT("Start\n");

	retc = DEMOD_L1_SET_DD_ISDBT_BASEADDR_AXI(core, baseAddr);

	if (retc != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, DEMOD_L1_SET_DD_ISDBT_BASEADDR_AXI() BecauseOf %s\n", DEMOD_L1_API_Error_Text(retc));
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

	DEMOD_PRINT("Start\n");

	retc = DEMOD_L1_GET_DD_Reg(core,  0x00, 0xde, 1);

	*eAlarm = (core->rsp->dd_get_reg.mData[0] >> 5) & 0x1;

	if (retc != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, BecauseOf %s\n", DEMOD_L1_API_Error_Text(retc));
	  	return -ERROR_DEMOD_WRITE;
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
const char * DEMOD_L1_API_Error_Text (int error_code)
{
	if (error_code < 0)
		error_code = -error_code;

	switch (error_code) {
	case NO_DEMOD_ERROR:							return "No DEMOD error";
	case ERROR_DEMOD_ALLOCATING_CONTEXT:			return "Error while allocating DEMOD context";
	case ERROR_DEMOD_SENDING_COMMAND:				return "Error while sending DEMOD command";
	case ERROR_DEMOD_CTS_TIMEOUT:					return "DEMOD CTS timeout";
	case ERROR_DEMOD_ERROR:							return "DEMOD Error (status 'err' bit 1)";
	case ERROR_DEMOD_POLLING_CTS:					return "DEMOD Error while polling CTS";
	case ERROR_DEMOD_POLLING_RESPONSE:				return "DEMOD Error while polling response";
	case ERROR_DEMOD_LOADING_FIRMWARE:				return "DEMOD Error while loading firmware";
	case ERROR_DEMOD_LOADING_BOOTBLOCK:				return "DEMOD Error while loading bootblock";
	case ERROR_DEMOD_STARTING_FIRMWARE:				return "DEMOD Error while starting firmware";
	case ERROR_DEMOD_SW_RESET:						return "DEMOD Error during software reset";
	case ERROR_DEMOD_INCOMPATIBLE_PART:				return "DEMOD Error Incompatible part";
	case ERROR_DEMOD_DISEQC_BUS_NOT_READY:			return "DISEQC but not ready";
	case ERROR_DEMOD_OS_LOCK:						return "OS Lock failed";
	case ERROR_DEMOD_PARAMETER:						return "DEMOD Parameter Error";
	case ERROR_DEMOD_PARAMETER_OUT_OF_RANGE:		return "DEMOD parameter(s) out of range";
	case ERROR_DEMOD_RESULT:						return "DEMOD Result Error";
	case ERROR_DEMOD_RESULT_NOT_READY:				return "DEMOD Result Not Ready";
	case ERROR_DEMOD_RESULT_UNKNOWN:				return "DEMOD Result Unknown";
	case ERROR_DEMOD_IPC:							return "IPC error";
	case ERROR_DEMOD_IPC_BUSY:						return "IPC busyr";
	case ERROR_DEMOD_IPC_EMPTY:						return "IPC buffer empty";
	case ERROR_DEMOD_IPC_TIMEOUT:					return "IPC timeout";
	case ERROR_DEMOD_IPC_INVALID:					return "IPC invalid";
	case ERROR_DEMOD_IPC_NOT_SUPPORT:				return "IPC not support";
	case ERROR_DEMOD_IPC_FALUT:						return "IPC fault";
	case ERROR_DEMOD_FW:							return "FW error";
	case ERROR_DEMOD_FW_INIT:						return "FW error init";
	case ERROR_DEMOD_FW_NOT_READY:					return "FW is not ready";
	case ERROR_DEMOD_FW_TIMEOUT:					return "FW timeout";
	case ERROR_DEMOD_FW_FAULT:						return "FW fault";
	case ERROR_DEMOD_INVALID:						return "DEMOD invalid";
	case ERROR_DEMOD_UNKNOWN_COMMAND:				return "DEMOD Error unknown command";
	case ERROR_DEMOD_UNKNOWN_PROPERTY:				return "DEMOD Error unknown property";
	case ERROR_DEMOD_READ:							return "DEMOD Error read";
	case ERROR_DEMOD_WRITE:							return "DEMOD Error write";
	case ERROR_DEMOD_PTRNULL:						return "DEMOD Error ptrnull";
	case ERROR_DEMOD_FAULT:							return "DEMOD fault";
	default:
		return "Unknown DEMOD error code";
	}
}

const char * DEMOD_L1_API_Modulation_Text (int modulation)
{
	switch ((DEMOD_MODULATION)modulation) {
	case DEMOD_MODULATION_VSB:						return "VSB";
	case DEMOD_MODULATION_QAM:						return "QAM";
	case DEMOD_MODULATION_ISDBT:					return "ISDB-T";
	case DEMOD_MODULATION_ATSC3:					return "ATSC3";
	case DEMOD_MODULATION_DVBT:						return "DVB-T";
	case DEMOD_MODULATION_DVBT2:					return "DVB-T2";
	case DEMOD_MODULATION_DVBC:						return "DVB-C";
	case DEMOD_MODULATION_DVBC2:					return "DVB-C2";
	case DEMOD_MODULATION_DVBS:						return "DVB-S";
	case DEMOD_MODULATION_DVBS2:					return "DVB-S2";
	case DEMOD_MODULATION_DTMB:						return "DTMB";
	default:
		return "UNKNOWN";
	}
}

const char * DEMOD_L1_API_Constellation_Text(int constellation) {
	switch((DEMOD_CONSTELLATION)constellation) {
	case DEMOD_CONSTELLATION_QPSK:					return "QPSK";
	case DEMOD_CONSTELLATION_DQPSK:					return "DQPSK";
	case DEMOD_CONSTELLATION_QAM16:					return "16QAM";
	case DEMOD_CONSTELLATION_QAM32:					return "32QAM";
	case DEMOD_CONSTELLATION_QAM64:					return "64QAM";
	case DEMOD_CONSTELLATION_QAM128:				return "128QAM";
	case DEMOD_CONSTELLATION_QAM256:				return "256QAM";
	case DEMOD_CONSTELLATION_QAM1024:				return "1024QAM";
	case DEMOD_CONSTELLATION_QAM4096:				return "4096QAM";
	case DEMOD_CONSTELLATION_PSK8:					return "8PSK";
	case DEMOD_CONSTELLATION_VSB8:					return "VSB";
	case DEMOD_CONSTELLATION_QAM4:					return "4QAM";
	case DEMOD_CONSTELLATION_APSK16:				return "16APSK";
	case DEMOD_CONSTELLATION_APSK32:				return "32APSK";
	case DEMOD_CONSTELLATION_QAM4NR:				return "4QAM NR";
	default:
		return "INVALID";
	}
}

const char * DEMOD_L1_API_FFT_Mode_Text(int fft_mode)
{
	switch((DEMOD_FFT_MODE)fft_mode) {
	case DEMOD_FFT_MODE_2K:							return "2K";
	case DEMOD_FFT_MODE_8K:							return "8K";
	case DEMOD_FFT_MODE_4K:							return "4K";
	case DEMOD_FFT_MODE_1K:							return "1K";
	case DEMOD_FFT_MODE_16K:						return "16K";
	case DEMOD_FFT_MODE_32K:						return "32K";
	case DEMOD_FFT_MODE_512K:						return "512K";
	case DEMOD_FFT_MODE_256K:						return "256K";
	default:
		return "INVALID";
	}
}

const char * DEMOD_L1_API_Coderate_Text(int modulation, int coderate)
{
	int cnt = 0;

	switch(modulation) {
	case DEMOD_MODULATION_DVBS:
	case DEMOD_MODULATION_DVBS2:
	case DEMOD_MODULATION_DTMB:
		switch ((DEMOD_CODERATE_DVBS_DVBS2_DTMB)coderate) {
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_1_2:		return "1/2";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_1_3:		return "1/3";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_2_3:		return "2/3";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_1_4:		return "1/4";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_3_4:		return "3/4";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_2_5:		return "2/5";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_3_5:		return "3/5";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_4_5:		return "4/5";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_5_6:		return "5/6";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_7_8:		return "7/8";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_8_9:		return "8/9";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_9_10:		return "9/10";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_13_45:		return "13/45";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_9_20:		return "9/20";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_90_180:		return "90/180";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_96_180:		return "96/180";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_11_20:		return "11/20";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_100_180:	return "100/180";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_104_180:	return "104/180";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_18_30:		return "18/30";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_28_45:		return "28/45";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_23_36:		return "23/36";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_20_30:		return "20/30";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_25_36:		return "25/36";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_128_180:	return "128/180";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_13_18:		return "13/18";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_132_180:	return "132/180";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_140_180:	return "140/180";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_154_180:	return "154/180";
		case DEMOD_CODERATE_DVBS_DVBS2_DTMB_UNKNOWN:	return "UNKNOWN";
		default:
			return "Invalid";
		}
		break;
	case DEMOD_MODULATION_ATSC3:
		switch ((DEMOD_CODERATE_ATSC3)coderate) {
		case DEMOD_CODERATE_ATSC3_2_15:					return "2/15";
		case DEMOD_CODERATE_ATSC3_3_15:					return "3/15";
		case DEMOD_CODERATE_ATSC3_4_15:					return "4/15";
		case DEMOD_CODERATE_ATSC3_5_15:					return "5/15";
		case DEMOD_CODERATE_ATSC3_6_15:					return "6/15";
		case DEMOD_CODERATE_ATSC3_7_15:					return "7/15";
		case DEMOD_CODERATE_ATSC3_8_15:					return "8/15";
		case DEMOD_CODERATE_ATSC3_9_15:					return "9/15";
		case DEMOD_CODERATE_ATSC3_10_15:				return "10/15";
		case DEMOD_CODERATE_ATSC3_11_15:				return "11/15";
		case DEMOD_CODERATE_ATSC3_12_15:				return "12/15";
		case DEMOD_CODERATE_ATSC3_13_15:				return "13/15";
		default:
			return "Invalid";
		}
		break;
	case DEMOD_MODULATION_DVBT:
	case DEMOD_MODULATION_ISDBT:
		switch((DEMOD_CODERATE_DVBT_ISDBT)coderate) {
		case DEMOD_CODERATE_DVBT_ISDBT_1_2:				return "1_2";
		case DEMOD_CODERATE_DVBT_ISDBT_2_3:				return "2_3";
		case DEMOD_CODERATE_DVBT_ISDBT_3_4:				return "3_4";
		case DEMOD_CODERATE_DVBT_ISDBT_5_6:				return "5_6";
		case DEMOD_CODERATE_DVBT_ISDBT_7_8:				return "7_8";
		default:
			return "Invalid";
		}
		break;
	case DEMOD_MODULATION_DVBT2:
		switch((DEMOD_CODERATE_DVBT2)coderate) {
		case DEMOD_CODERATE_DVBT2_1_2:					return "1_2";
		case DEMOD_CODERATE_DVBT2_3_5:					return "3_5";
		case DEMOD_CODERATE_DVBT2_2_3:					return "2_3";
		case DEMOD_CODERATE_DVBT2_3_4:					return "3_4";
		case DEMOD_CODERATE_DVBT2_4_5:					return "4_5";
		case DEMOD_CODERATE_DVBT2_5_6:					return "5_6";
		default:
			return "Invalid";
		}
		break;
	default:
		return "N/A";
	}
}
