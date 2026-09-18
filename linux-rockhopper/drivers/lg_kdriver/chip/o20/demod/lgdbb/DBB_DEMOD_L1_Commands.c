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
#define DEMOD_TAG "[L1.CMD] "

#include <DBB_DEMOD_typedefs.h>
#include <demod_util.h>

#include "DBB_DEMOD_L1_IPC.h"

#include "DBB_DEMOD_L1_Properties.h"
#include "DBB_DEMOD_L1_Commands.h"

#include "DBB_DEMOD_L1_API.h"

#include "DBB_DEMOD_L1_IPC_Prototypes.h"
#include "DBB_DEMOD_L1_Commands_Prototypes.h"
#include "DBB_DEMOD_L1_Properties_Functions.h"

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_XTENSA)
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/spinlock.h>

#include "demod_impl.h"
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)
#endif

static UINT8 	rspByteBuffer[PAYLOAD_BMAX] = {0,};

#if defined(DEMOD_CONFIG_IPC)
char check_point[4][1024];

int DEMOD_L1_Process_Dump(LX_DEMOD_L1_Context * core, char * dbglog) {
	int dbgidx = 0;

	return dbgidx;
}

#if (DEMOD_COMM == DEMOD_COMM_APB)
#define SPEND_TIME_WARNING	1000
#define SPEND_TIME_LIMIT	3000
#elif (DEMOD_COMM == DEMOD_COMM_I2C)
#define SPEND_TIME_WARNING	1000
#define SPEND_TIME_LIMIT	3000
#elif (DEMOD_COMM == DEMOD_COMM_FPGA)
#define SPEND_TIME_WARNING	2000
#define SPEND_TIME_LIMIT	6000
#else
#define SPEND_TIME_WARNING	1000
#define SPEND_TIME_LIMIT	3000
#endif

#if defined(DEMOD_SPEND_TIME_CHECK)
UINT32 _cmd_req_ms, _cmd_req_us;
UINT32 _cmd_res_ms, _cmd_res_us;
#endif

static int _DEMOD_L1_CommandRequest(LX_DEMOD_L1_Context * core, UINT8 cmd, UINT8 * preq, UINT32 len) {
	UINT64 start_clock;
	UINT64 spend_clock;
	UINT32 spend_us;
	UINT32 spend_ms;

	int state = CBUF_STATE_UNKNOWN;
	int err = NO_DEMOD_ERROR;
	int retry = 5;

	start_clock = DEMOD_L0_SystemClock();

	DEMOD_DEBUG("Tx REQ x%02x(%3d), %d, %s\n", cmd, core->cmd_req_cnt, len, dbb_debug_byte_to_hexstr((UINT8 *)preq, len));
	do {
		core->cmd_req_cnt++;
		err = DEMOD_L1_IPC_Send(core, CMD_TYPE(CMD_MAJOR_TYPE_API, cmd), core->cmd_req_cnt, (char *)preq, len);
		if (err != NO_DEMOD_ERROR) {
			DEMOD_ERROR("DEMOD_L1_IPC_Send Error 0x%02x, %s\n", -err, DEMOD_L1_API_Error_Text(err));

			core->cmd_req_err_cnt++;
			return err;
		}


#if defined(DEMOD_CONFIG_IPC_RETRANSMIT)
		/* w/ IPC Retransmit */
		DEMOD_L0_system_wait(1);
		DEMOD_L1_IPC_Send_GetState(core, &state);

		spend_clock = DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us);

		do {
			DEMOD_L0_system_wait(1);
			DEMOD_L1_IPC_Send_GetState(core, &state);

			spend_clock = DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us);
		} while ((state <= CBUF_STATE_START) && (spend_ms < SPEND_TIME_LIMIT));

		if (state == CBUF_STATE_DONE) {
			break;
		} else if (state == CBUF_STATE_INVALID) {
			if ((retry--) && (spend_ms < SPEND_TIME_LIMIT)) {
				core->cmd_req_ret_cnt++;
				DEMOD_NOTI("resend, x%02x(%3u), retry %d, tx state %d, tooks %3u.%03ums\n", cmd, core->cmd_req_cnt & 0xFF, retry, state, spend_ms, spend_us);
			} else {
				err = -ERROR_DEMOD_IPC_TIMEOUT;
				core->cmd_req_out_cnt++;
				break;
			}
		} else {
			err = -ERROR_DEMOD_IPC_INVALID;
			core->cmd_req_inv_cnt++;
			break;
		}
#else
		/* w/o IPC Retransmit */
		UINT32 send_count;
		do {
			DEMOD_L0_system_wait(1);

			send_count = DEMOD_L1_IPC_Send_Count(core);
			spend_clock = DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us);
		} while ((send_count > 0)  && (spend_ms < SPEND_TIME_LIMIT));
		break;
#endif
	} while (1);

	//spend_clock = DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us);

#if defined(DEMOD_SPEND_TIME_CHECK)
	_cmd_req_ms = spend_ms;
	_cmd_req_us = spend_us;
#endif

	if (err < 0) {
		DEMOD_ERROR("Send Fail, x%02x(%3u), retry %d, tx state %d, tooks %3u.%03ums, len %d, err 0x%02X, %s\n", cmd, core->cmd_req_cnt & 0xFF, retry, state, spend_ms, spend_us, len, -err, DEMOD_L1_API_Error_Text(err));
	} else
		core->cmd_req_val_cnt++;

	return err;
}

static int _DEMOD_L1_CommandResponse(LX_DEMOD_L1_Context * core, UINT8 *pcmd, UINT8 *pseq, UINT8 *prsp, int *plen) {
	UINT64 start_clock;
	UINT64 spend_clock;
	UINT32 spend_us;
	UINT32 spend_ms;

	UINT32 typ = 0;
	UINT32 seq = 0;

	int err = NO_DEMOD_ERROR;

	*plen = 0;
	*pcmd = 0;
	*pseq = 0;

	core->cmd_res_cnt++;

	start_clock = DEMOD_L0_SystemClock();

	if (DEMOD_L1_IPC_Recv_Count(core) == 0) {
		DEMOD_L1_IPC_Wait(core, 5);
	}

	if (DEMOD_L1_IPC_Recv_Count(core) > 0) {
		err = DEMOD_L1_IPC_Recv(core, &typ, &seq, (char *)prsp);
		if (err < 0) {
			core->cmd_res_err_cnt++;
		} else if (err >= 0) {
			*pcmd = CMD_MINOR_TYPE(typ);
			*pseq = seq;
			*plen = err;
			err = NO_DEMOD_ERROR;
		}
	} else {
		core->cmd_res_out_cnt++;
		err = -ERROR_DEMOD_IPC_EMPTY;
	}

	spend_clock = DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us);

	if (err < 0) {
		DEMOD_WARN("Recv Resp, err 0x%02X, %s, tooks %3u.%03u\n", -err, DEMOD_L1_API_Error_Text(err), spend_ms, spend_us);
	} else {
		DEMOD_DEBUG("Recv Resp, tooks %3u.%03u ms, typ x%04x, cmd x%02x, seq %3u, len %2u, with err 0x%02X\n", spend_ms, spend_us, typ, *pcmd, *pseq, *plen, -err);
	}

	return err;
}

static int _DEMOD_L1_WaitResponse(LX_DEMOD_L1_Context * core, UINT8 wait_cmd, UINT8 * prsp, int * plen)
{
	UINT64 start_clock;
	UINT64 spend_clock;
	UINT32 spend_us;
	UINT32 spend_ms;

	UINT8 wait_seq = core->cmd_req_cnt & 0xFF;
	UINT8 cmd;
	UINT8 seq;

	int err = NO_DEMOD_ERROR;

	start_clock = DEMOD_L0_SystemClock();
	
	do {
		err = _DEMOD_L1_CommandResponse(core, &cmd, &seq, prsp, plen);
		spend_clock = DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us);

		if (err == NO_DEMOD_ERROR) {
			if (cmd == wait_cmd && seq == wait_seq) {
				core->cmd_res_val_cnt++;
				break;
			} else {
				core->cmd_res_skp_cnt++;
				DEMOD_NOTI("skip, recv(%d) x%02x(%3u) != wait x%02x(%3u)\n", *plen, cmd, seq, wait_cmd, wait_seq);
			}
		} else {
			DEMOD_WARN("retry, wait x%02x(%3u), err 0x%02x, %s\n", wait_cmd, wait_seq, -err, DEMOD_L1_API_Error_Text(err));
		}
	} while (spend_ms < SPEND_TIME_LIMIT);

	if (NO_DEMOD_ERROR == err && (cmd != wait_cmd || seq != wait_seq)) {
		core->cmd_res_inv_cnt++;
		err = -ERROR_DEMOD_IPC_INVALID;
	}

	if (core->fw_state != DEMOD_FW_STATE_RUN)
		err = -ERROR_DEMOD_FW_NOT_READY;

	if (err != NO_DEMOD_ERROR)
		DEMOD_WARN("Recv Done, tooks %3u.%03ums, recv(%d) x%02x(%3u), wait x%02x(%3u), err 0x%02x, %s\n", spend_ms, spend_us, *plen, cmd, seq, wait_cmd, wait_seq, -err, DEMOD_L1_API_Error_Text(err));
#if defined(DEMOD_SPEND_TIME_CHECK)
	_cmd_res_ms = spend_ms;
	_cmd_res_us = spend_us;
#endif
	return err;
}
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_Process for. (IPC Ver)
 * sending command and waiting response using IPC
 *
 * @param * core 		[IN] LX_DEMOD_L1_Context
 * @param cmdByte 		[IN] send command payload length
 * @param * cmdByteBuffer 	[IN] send command payload
 * @param rspByte 		[IN] recv command payload legnth
 * @param * rspByteBuffer 	[OUT] recv command payload
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
 */

int DEMOD_L1_Process (LX_DEMOD_L1_Context * core, UINT8 req_len, UINT8 * req_buf, UINT8 rsp_len, UINT8 * rsp_buf)
{
	UINT64 start_clock;
	UINT64 spend_clock;
	UINT32 spend_us;
	UINT32 spend_ms;
	
	UINT8	command;

	int err = 0;
	int rcv_len = 0;

	command = req_buf[0];
	
	if (core->fw_state != DEMOD_FW_STATE_RUN) {
		DEMOD_WARN("fw is not ready\n");
		return -ERROR_DEMOD_FW_NOT_READY;
	}

	DEMOD_DEBUG("cmd x%02x, req len %d, rsp len %d\n", command, req_len, rsp_len);
	/* Phase 1 : handle special case
	 * - power_save resume
	 * - have to escape from stall before request command
	 */
	
	start_clock = DEMOD_L0_SystemClock();
	
	if (command == DEMOD_DD_POWER_SAVE_CMD && req_buf[1] == 0) {
		DEMOD_L1_API_StopFirmware(core);
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
		//err = DEMOD_MCU_Suspend(FALSE);
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
		err = DEMOD_L0_WriteCommandBytes(core->chip, 0xF004, sizeof(err), &err);
#else
#endif
		if(err != NO_DEMOD_ERROR) {
			DEMOD_ERROR("failed to WriteCommandBytes(0x%02X) with err 0x%02X\n", command, -err);
			return err;
		}
	}

	/* Phase 2 : Send request command */

	DEMOD_L1_API_Debug(core, check_point[0]);
	DEMOD_L0_CBUF_Status(&core->ipc->tx, check_point[1]);

	//err = DEMOD_L1_Command_Request(command, req_buf + 1, req_len - 1);
	err = _DEMOD_L1_CommandRequest(core, command, req_buf, req_len);	// 1st byte keep... because parsing problems...
	if (err != NO_DEMOD_ERROR) {
		DEMOD_ERROR("failed to CommandRequest(0x%02X) with err 0x%02X\n", command, -err);
		//DEMOD_ERROR("REQ: %s\n", reqLog);

		DEMOD_L1_API_Debug(core, check_point[2]);
		DEMOD_L0_CBUF_Status(&core->ipc->tx, check_point[3]);

		DEMOD_DEBUG("[0] %s\n", check_point[0]);
		DEMOD_DEBUG("[1] %s\n", check_point[1]);
		DEMOD_DEBUG("[2] %s\n", check_point[2]);
		DEMOD_DEBUG("[3] %s\n", check_point[3]);
		return err;
	}

	DEMOD_L1_API_Debug(core, check_point[0]);
	DEMOD_L1_IPC_Status_Fifo(core, check_point[1]);

	/* Phase 3 : Wait response */
	err = _DEMOD_L1_WaitResponse(core, command, rsp_buf, &rcv_len);
	if(err != NO_DEMOD_ERROR) {
		DEMOD_ERROR("failed to WaitResponse(0x%02X) with err 0x%02X\n", command, -err);
		//DEMOD_ERROR("REQ: %s\n", reqLog);
		//DEMOD_ERROR("RES: %s\n", resLog);

		DEMOD_L1_API_Debug(core, check_point[2]);
		DEMOD_L1_IPC_Status_Fifo(core, check_point[3]);

		DEMOD_DEBUG("[0] %s\n", check_point[0]);
		DEMOD_DEBUG("[1] %s\n", check_point[1]);
		DEMOD_DEBUG("[2] %s\n", check_point[2]);
		DEMOD_DEBUG("[3] %s\n", check_point[3]);
		return err;
	}

	if (rsp_len > rcv_len) {
		DEMOD_ERROR("0x%02x: not enough rcv len %d, need %d for command(0x%02X)\n", command, rcv_len, rsp_len, command);
	}

	/* Phase 4 : handle special case
	 * - power_save enter
	 */
	if (command == DEMOD_DD_POWER_SAVE_CMD && req_buf[1] == 1) {
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
		//err = DEMOD_MCU_Suspend(TRUE);
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
		err = DEMOD_L0_WriteCommandBytes(core->chip, 0xF004, sizeof(err), &err);
#else
#endif

		if(err != NO_DEMOD_ERROR) {
			DEMOD_ERROR("failed to WriteCommandBytes with err 0x%02X\n", -err);
			return err;
		}
	}

	spend_clock = DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us);

#if defined(DEMOD_SPEND_TIME_CHECK)
	DEMOD_INFO("0x%02X done, tooks %3u.%03u ms, send %3u.%03u, recv %3u.%03u\n", command, spend_ms, spend_us, _cmd_req_ms, _cmd_req_us, _cmd_res_ms, _cmd_res_us);
#else
	if (spend_ms > SPEND_TIME_WARNING)
		DEMOD_WARN("0x%02X done, tooks %3u.%03u ms\n", command, spend_ms, spend_us);
#endif
	
	return  err;
}

#else
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_Process.
 * sending command and waiting response
 *
 * @param * core 		[IN] LX_DEMOD_L1_Context
 * @param cmdByte 		[IN] send command payload length
 * @param * cmdByteBuffer 	[IN] send command payload
 * @param rspByte 		[IN] recv command payload legnth
 * @param * rspByteBuffer 	[OUT] recv command payload
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_Process (LX_DEMOD_L1_Context * core, UINT8 cmdByte, UINT8 *cmdByteBuffer, UINT8 rspByte, UINT8 *rspByteBuffer)
{
	UINT32 wtemp;
	UINT8 command=0;
	int err = 0;

	err = DEMOD_L0_WriteCommandBytes(core->chip, REG_CMD_ADDR, cmdByte, cmdByteBuffer);
	command = cmdByteBuffer[0];

	switch(command)
	{
	case DEMOD_DD_POWER_SAVE_CMD:
		if(cmdByteBuffer[1])	//powersave
		{
			if(err == NO_DEMOD_ERROR)
				err = DEMOD_L1_SetInt(core);
#ifndef __EVAL_GUI__
			DEMOD_L0_system_wait(1);
#endif
			if(err == NO_DEMOD_ERROR)
				err = DEMOD_L1_GetCts(core, command);

			wtemp = 0x1;
			if(err == NO_DEMOD_ERROR)
				err = DEMOD_L0_WriteCommandBytes(core->chip, 0xF004, 4, &wtemp);
		}
		else
		{
			wtemp = 0x0;
			if(err == NO_DEMOD_ERROR)
				err = DEMOD_L0_WriteCommandBytes(core->chip, 0xF004, 4, &wtemp);

			if(err == NO_DEMOD_ERROR)
				err = DEMOD_L1_SetInt(core);
#ifndef __EVAL_GUI__
			DEMOD_L0_system_wait(1);
#endif
			if(err == NO_DEMOD_ERROR)
				err = DEMOD_L1_GetCts(core, command);
		}

		if (err == NO_DEMOD_ERROR)
			core->cmd_res_cnt++;
		else
			core->cmd_res_err_cnt++;
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
				err = DEMOD_L1_SetInt(core);
#ifndef __EVAL_GUI__
			DEMOD_L0_system_wait(1);
#endif
			//DEMOD_PRINT   ("5 'reset' took %3d ms\n", get_system_time() - core->start_time);
			if(err == NO_DEMOD_ERROR)
				err = DEMOD_L1_GetCts(core, command);

			if (err == NO_DEMOD_ERROR)
				core->cmd_res_cnt++;
			else
				core->cmd_res_err_cnt++;
		}
		break;

	case DEMOD_DD_GET_PROP_CMD:
	case DEMOD_DD_GET_REG_CMD:
	case DEMOD_DD_VSB_STATUS_CMD:
	case DEMOD_DD_QAM_STATUS_CMD:
	case DEMOD_DD_GET_PART_INFO_CMD:
	case DEMOD_DD_STATUS_CMD:
	case DEMOD_DD_TSCLK_STATUS_CMD:
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
		if(err == NO_DEMOD_ERROR)
			err = DEMOD_L1_SetInt(core);
#ifndef __EVAL_GUI__
		DEMOD_L0_system_wait(1);
#endif
		if(err == NO_DEMOD_ERROR)
			err = DEMOD_L1_GetCts(core, command);

		if(err == NO_DEMOD_ERROR)
		{
			err = DEMOD_L1_PollForRsp(core, rspByte, rspByteBuffer);
			//DEMOD_PRINT("\n ########## DEMOD_L1_PollForRsp rspByteBuffer = %x ########## \n\n", *rspByteBuffer);
		}

		if (err == NO_DEMOD_ERROR)
			core->cmd_res_cnt++;
		else
			core->cmd_res_err_cnt++;
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
 * @param *frontend 	[IN] LX_DEMOD_L2_Context
 * @param ptDataBuffer 	[OUT] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_CurrentRspStatus (LX_DEMOD_L1_Context * core, UINT8 ptDataBuffer)
{
	core->status->cts     = ptDataBuffer;
	return  NO_DEMOD_ERROR;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GetCts.
 * gets MCU firmware CTS(Clear To Send) response  after sending commands
 *
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @param cmdCode 		[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GetCts (LX_DEMOD_L1_Context * core, UINT8 cmdCode)
{
	UINT32 start_time=0;
	UINT32 wtemp = 0;

	start_time = get_system_time();
	while ((get_system_time() - start_time) < 1000) { /* wait a maximum of 1000ms */
		if(NO_DEMOD_ERROR == DEMOD_L0_ReadCommandBytes(core->chip, REG_CTS_ADDR, 4, &wtemp)) {
			if((wtemp & 0xFF) == cmdCode) {
				core->chip->i2c_indirect = 0;
				wtemp = 0;
				if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_CTS_ADDR, 4, &wtemp)) {
					return -ERROR_DEMOD_WRITE;
				}
				core->ipc->status.recv_cnt++;
				return NO_DEMOD_ERROR;
			}
		} else {
			core->ipc->status.recv_fail_cnt++;
			return -ERROR_DEMOD_POLLING_RESPONSE;
		}

		DEMOD_L0_system_wait(1);
	}

	core->ipc->status.tout_cnt++;
	return -ERROR_DEMOD_CTS_TIMEOUT;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_PollForRsp.
 * gets required informations from MCU Firmware
 *
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @param nbBytes 		[IN] UINT8
 * @param *pByteBuffer 	[OUT] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_PollForRsp (LX_DEMOD_L1_Context * core, UINT8 nbBytes, UINT8 *pByteBuffer)
{
	int i=0;
	int wlen = (nbBytes + 3) >> 2;

	for (i = 0; i < wlen; i++) {
#ifndef __EVAL_GUI__
		DEMOD_L0_system_wait(1);
#endif
		if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(core->chip, (REG_RSP_ADDR) + 4 * i, 4, pByteBuffer + 4 * i)) {
			return -ERROR_DEMOD_POLLING_RESPONSE;
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_SetInt (LX_DEMOD_L1_Context * core)
{
	UINT32 wtemp = 0;

	wtemp = 0x1;
	if (NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_INT_SRC, 4, &wtemp)) {
		core->ipc->status.send_fail_cnt++;
		return -ERROR_DEMOD_WRITE;
	}

	core->cmd_req_cnt++;
	core->cmd_req_val_cnt++;
	core->ipc->status.send_cnt++;
	return NO_DEMOD_ERROR;
}
#endif

#ifdef    DEMOD_DD_SET_REG_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_SET_DD_Reg.
 * sets demoduator register through MCU
 *
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @param addressMsb 	[IN] UINT8
 * @param addressLsb 	[IN] UINT8
 * @param length 		[IN] UINT8
 * @param data 			[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_SET_DD_Reg (LX_DEMOD_L1_Context * core, UINT8 addressMsb, UINT8 addressLsb, UINT8 length, UINT32 data)
{

	int err = 0;

	UINT8 i=0;
	UINT8 cmdByteBuffer[128]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	cmdByte = 4 + length;
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_SET_REG_CMD;
	cmdByteBuffer[1] = ((addressMsb & DEMOD_DD_SET_REG_CMD_ADDRMSB_MASK) << DEMOD_DD_SET_REG_CMD_ADDRMSB_LSB);
	cmdByteBuffer[2] = ((addressLsb & DEMOD_DD_SET_REG_CMD_ADDRLSB_MASK) << DEMOD_DD_SET_REG_CMD_ADDRLSB_LSB);
	cmdByteBuffer[3] = ((length & DEMOD_DD_SET_REG_CMD_LENGTH_MASK) << DEMOD_DD_SET_REG_CMD_LENGTH_LSB);

	for (i = 0; i < length; i++)
	{
		cmdByteBuffer[4+i] = (UINT8)((data >> (i * 8)) & 0xff) ;
	}

	err = DEMOD_L1_Process (core, cmdByte , cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}

UINT8 DEMOD_L1_SET_DD_Reg_Map (LX_DEMOD_L1_Context * core, UINT8 addressMsb, UINT8 addressLsb, UINT8 length, UINT8 *wrData)
{
	UINT8 err = 0;
	UINT8 i;
	UINT8 cmdByteBuffer[128]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	cmdByte = 4 + length;
	cmdByteBuffer[0] = DEMOD_DD_SET_REG_CMD;
	cmdByteBuffer[1] = ( ( addressMsb & DEMOD_DD_SET_REG_CMD_ADDRMSB_MASK ) << DEMOD_DD_SET_REG_CMD_ADDRMSB_LSB);
	cmdByteBuffer[2] = ( ( addressLsb & DEMOD_DD_SET_REG_CMD_ADDRLSB_MASK ) << DEMOD_DD_SET_REG_CMD_ADDRLSB_LSB);
	cmdByteBuffer[3] = ( ( length & DEMOD_DD_SET_REG_CMD_LENGTH_MASK ) << DEMOD_DD_SET_REG_CMD_LENGTH_LSB);

	for (i = 0; i < length; i++)
	{
		//cmdByteBuffer[4+i] = (UINT8)((data >> (i * 8)) & 0xff) ;
		cmdByteBuffer[4+i] = *(wrData+i);
	}

	err = DEMOD_L1_Process (core, cmdByte , cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @param prop 			[IN] UINT16
 * @param data 			[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_SET_DD_Prop (LX_DEMOD_L1_Context * core, UINT16 prop, UINT32 data)
{

	int err = 0;
	UINT8 cmdByteBuffer[8]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	cmdByte = 8;
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_SET_PROP_CMD;
	cmdByteBuffer[1] = (UINT8)(((prop & DEMOD_DD_SET_PROP_CMD_PROP_MASK) << DEMOD_DD_SET_PROP_CMD_PROP_LSB) >>  8);
	cmdByteBuffer[2] = (UINT8)(((prop & DEMOD_DD_SET_PROP_CMD_PROP_MASK) << DEMOD_DD_SET_PROP_CMD_PROP_LSB) >>  0);
	cmdByteBuffer[3] = (UINT8)0;
	cmdByteBuffer[4] = (UINT8)(((data & DEMOD_DD_SET_PROP_CMD_DATA_MASK) << DEMOD_DD_SET_PROP_CMD_DATA_LSB) >>  0);
	cmdByteBuffer[5] = (UINT8)(((data & DEMOD_DD_SET_PROP_CMD_DATA_MASK) << DEMOD_DD_SET_PROP_CMD_DATA_LSB) >>  8);
	cmdByteBuffer[6] = (UINT8)(((data & DEMOD_DD_SET_PROP_CMD_DATA_MASK) << DEMOD_DD_SET_PROP_CMD_DATA_LSB) >> 16);
	cmdByteBuffer[7] = (UINT8)(((data & DEMOD_DD_SET_PROP_CMD_DATA_MASK) << DEMOD_DD_SET_PROP_CMD_DATA_LSB) >> 24);

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param * chip 			[IN] LX_DEMOD_L0_Context
 * @param rptEn 		[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_SET_DD_Repeat (LX_DEMOD_L0_Context * chip, UINT8 rptEn)
{
	UINT8 wrData[4] = {0, }, rdData[4] = {0, };
	int err;

	LX_DEMOD_L0_Context repeatI2c;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(chip))
		return ERROR_DEMOD_OS_LOCK;


	repeatI2c.i2c_slv_addr	= 0xE0;
	repeatI2c.i2c_idx_size	= 2;
	repeatI2c.i2c_handle	= (chip->i2c_handle & 0xffffff00) + repeatI2c.i2c_slv_addr;

	DEMOD_L0_Lock_CommDevice(chip);
	if(rptEn == 1) {
		err = DEMOD_L0_I2C_Read(&repeatI2c, 0x7000, 1, rdData);
		wrData[0] = rdData[0] & 0xfe;
		err = DEMOD_L0_I2C_Write(&repeatI2c, 0x7000, 1, wrData);
	} else {
		err = DEMOD_L0_I2C_Read(&repeatI2c, 0x7000, 1, rdData);
		wrData[0] = rdData[0] | 0x1;
		err = DEMOD_L0_I2C_Write(&repeatI2c, 0x7000, 1, wrData);
	}
	DEMOD_L0_Unlock_CommDevice(chip);
	DEMOD_L0_UnlockDevice(chip);
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
 * @param * core 		[IN] LX_DEMOD_L1_Context
 * @param softrstb 		[IN] UINT8
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
int DEMOD_L1_SET_DD_SoftRst(LX_DEMOD_L1_Context * core, UINT8 softrstb, UINT8 softrstsyncb, UINT8 softrsteq1b, UINT8 softrsteq2b, UINT8 softrstdiseqcb, UINT8 softrstfecb, UINT8 softrsttpifb)
{

	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	cmdByte=2;
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_SOFT_RESET_CMD;
   	cmdByteBuffer[1] = (UINT8)((softrstb 		& DEMOD_DD_SOFT_RESET_CMD_SOFTRSTB_MASK) 	<< DEMOD_DD_SOFT_RESET_CMD_SOFTRSTB_LSB 	|
			            (softrstsyncb 	& DEMOD_DD_SOFT_RESET_CMD_SOFTRSTSYNCB_MASK)	<< DEMOD_DD_SOFT_RESET_CMD_SOFTRSTSYNCB_LSB 	|
			            (softrsteq1b 	& DEMOD_DD_SOFT_RESET_CMD_SOFTRSTEQ1B_MASK)	<< DEMOD_DD_SOFT_RESET_CMD_SOFTRSTEQ1B_LSB 	|
			            (softrsteq2b 	& DEMOD_DD_SOFT_RESET_CMD_SOFTRSTEQ2B_MASK)	<< DEMOD_DD_SOFT_RESET_CMD_SOFTRSTEQ2B_LSB 	|
			            (softrstdiseqcb 	& DEMOD_DD_SOFT_RESET_CMD_SOFTRSTDISEQCB_MASK)	<< DEMOD_DD_SOFT_RESET_CMD_SOFTRSTDISEQCB_LSB 	|
			            (softrstfecb 	& DEMOD_DD_SOFT_RESET_CMD_SOFTRSTFECB_MASK)	<< DEMOD_DD_SOFT_RESET_CMD_SOFTRSTFECB_LSB 	|
			            (softrsttpifb 	& DEMOD_DD_SOFT_RESET_CMD_SOFTRSTTPIFB_MASK)	<< DEMOD_DD_SOFT_RESET_CMD_SOFTRSTTPIFB_LSB);

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core		[IN] LX_DEMOD_L1_Context
 * @param power_save 	[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_SET_DD_Power_Save(LX_DEMOD_L1_Context * core, UINT8 power_save)
{

	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	cmdByte=2;
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_POWER_SAVE_CMD;
	cmdByteBuffer[1] = (UINT8)power_save;

#ifdef	FPGA_RDK_M17_PRINT
	DEMOD_PRINT("\n ########## DEMOD_L1_SET_DD_Power_Save ########## \n\n");
#endif

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param * core		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_SET_DD_Restart(LX_DEMOD_L1_Context * core)
{

	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	cmdByte = 1;
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_RESTART_CMD;

#ifdef	FPGA_RDK_M17_PRINT
	DEMOD_PRINT("\n ########## DEMOD_L1_SET_DD_Restart ########## \n\n");
#endif

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @param addressMsb 	[IN] UINT8
 * @param addressLsb 	[IN] UINT8
 * @param length 		[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_Reg (LX_DEMOD_L1_Context * core,  UINT8 addressMsb, UINT8 addressLsb, UINT8 length)
{

	int err = 0, i = 0;
	UINT8 cmdByteBuffer[8]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	cmdByte = 4;
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_GET_REG_CMD;
	cmdByteBuffer[1] = ((addressMsb	& DEMOD_DD_GET_REG_CMD_ADDRMSB_MASK) 	<< DEMOD_DD_GET_REG_CMD_ADDRMSB_LSB);
	cmdByteBuffer[2] = ((addressLsb	& DEMOD_DD_GET_REG_CMD_ADDRLSB_MASK) 	<< DEMOD_DD_GET_REG_CMD_ADDRLSB_LSB);
	cmdByteBuffer[3] = ((length	& DEMOD_DD_GET_REG_CMD_LENGTH_MASK) 	<< DEMOD_DD_GET_REG_CMD_LENGTH_LSB);

	rspByte = length;

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	for(i = 0; i <length; i++) {
		core->rsp->dd_get_reg.mData[i] = rspByteBuffer[i];
	}

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}

int DEMOD_L1_GET_DD_Reg_Map (LX_DEMOD_L1_Context * core,  UINT8 addressMsb, UINT8 addressLsb, UINT16 length, UINT8* rspByteBuffer)
{
	int err = 0;
	UINT8 cmdByteBuffer[8]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;
	UINT16 address = (addressMsb << 8) | (addressLsb);

	int cur_length;
	int i;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	cmdByte = 4;
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_GET_REG_CMD;

	for (i = 0; (err == NO_DEMOD_ERROR) && (i < length); i += PAYLOAD_BMAX) {
		addressMsb = (address + i) >> 8;
		addressLsb = (address + i) & 0xFF;

		cur_length = length - i;

		if (cur_length > PAYLOAD_BMAX) {
			cur_length = PAYLOAD_BMAX;
		}

		cmdByteBuffer[1] = ((addressMsb	& DEMOD_DD_GET_REG_CMD_ADDRMSB_MASK) 	<< DEMOD_DD_GET_REG_CMD_ADDRMSB_LSB);
		cmdByteBuffer[2] = ((addressLsb	& DEMOD_DD_GET_REG_CMD_ADDRLSB_MASK) 	<< DEMOD_DD_GET_REG_CMD_ADDRLSB_LSB);
		cmdByteBuffer[3] = ((cur_length	& DEMOD_DD_GET_REG_CMD_LENGTH_MASK) 	<< DEMOD_DD_GET_REG_CMD_LENGTH_LSB);
		rspByte = cur_length;

		err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, &rspByteBuffer[i]);
	}

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_DD_GET_REG_CMD */

#ifdef DEMOD_DD_GET_PROP_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_Prop.
 * sets demoduator register through MCU
 *
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @param prop		 	[IN] UINT16
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_Prop (LX_DEMOD_L1_Context * core, UINT16 prop)
{

	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	rspByte = 4;
	cmdByte = 3;
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_GET_PROP_CMD;
	cmdByteBuffer[1] = (UINT8)(((prop	& DEMOD_DD_GET_PROP_CMD_PROP_MASK) 	<< DEMOD_DD_GET_PROP_CMD_PROP_LSB) >> 8);
	cmdByteBuffer[2] = (UINT8)(((prop	& DEMOD_DD_GET_PROP_CMD_PROP_MASK)	<< DEMOD_DD_GET_PROP_CMD_PROP_LSB) >> 0);

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);
	core->rsp->get_property.data =  (((rspByteBuffer[3] <<24 | rspByteBuffer[2] <<16 | rspByteBuffer[1] <<8 | (rspByteBuffer[0])) >> DEMOD_DD_GET_PROP_CMD_PROP_LSB) & DEMOD_DD_GET_PROP_CMD_PROP_MASK);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_VSB_Status (LX_DEMOD_L1_Context * core)
{

	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	rspByte = 17;
	cmdByte = 1;
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_VSB_STATUS_CMD;

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	core->rsp->vsb_status.if_agc 		= ((((rspByteBuffer[1]) | (rspByteBuffer[0] << 8)) >> DEMOD_DD_VSB_STATUS_RESPONSE_IF_AGC_LSB) & DEMOD_DD_VSB_STATUS_RESPONSE_IF_AGC_MASK);
	core->rsp->vsb_status.mse_info		= ((((rspByteBuffer[3]) | (rspByteBuffer[2] << 8)) >> DEMOD_DD_VSB_STATUS_RESPONSE_MSE_INFO_LSB) & DEMOD_DD_VSB_STATUS_RESPONSE_MSE_INFO_MASK) ;
	core->rsp->vsb_status.ber		= ((((rspByteBuffer[6]) | (rspByteBuffer[5] << 8) | (rspByteBuffer[4] << 16)) >> DEMOD_DD_VSB_STATUS_RESPONSE_BER_LSB) & DEMOD_DD_VSB_STATUS_RESPONSE_BER_MASK);
	core->rsp->vsb_status.cfo		= ((((rspByteBuffer[9]) | (rspByteBuffer[8] << 8) | (rspByteBuffer[7] << 16)) >> DEMOD_DD_VSB_STATUS_RESPONSE_CFO_LSB) & DEMOD_DD_VSB_STATUS_RESPONSE_CFO_MASK);
	core->rsp->vsb_status.op_mode		= ((rspByteBuffer[10] >> DEMOD_DD_VSB_STATUS_RESPONSE_OP_MODE_LSB) & DEMOD_DD_VSB_STATUS_RESPONSE_OP_MODE_MASK);
	core->rsp->vsb_status.pe 		= ((rspByteBuffer[11] >> DEMOD_DD_VSB_STATUS_RESPONSE_PE_LSB) & DEMOD_DD_VSB_STATUS_RESPONSE_PE_MASK);
	core->rsp->vsb_status.spInv		= ((rspByteBuffer[12] >> DEMOD_DD_VSB_STATUS_RESPONSE_SPECINV_LSB) & DEMOD_DD_VSB_STATUS_RESPONSE_SPECINV_MASK);
	core->rsp->vsb_status.sfo		= ((((rspByteBuffer[15]) | (rspByteBuffer[14] << 8) | (rspByteBuffer[13] << 16)) >> DEMOD_DD_VSB_STATUS_RESPONSE_SFO_LSB) & DEMOD_DD_VSB_STATUS_RESPONSE_SFO_MASK);
	core->rsp->vsb_status.lock_carr		= ((rspByteBuffer[16]  >> DEMOD_DD_VSB_STATUS_RESPONSE_LOCK_CARR_LSB) & DEMOD_DD_VSB_STATUS_RESPONSE_LOCK_CARR_MASK);
	core->rsp->vsb_status.lock_fec		= ((rspByteBuffer[16]  >> DEMOD_DD_VSB_STATUS_RESPONSE_LOCK_FEC_LSB) & DEMOD_DD_VSB_STATUS_RESPONSE_LOCK_FEC_MASK);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_QAM_Status (LX_DEMOD_L1_Context * core)
{
	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	rspByte = 19;
	cmdByte = 1;
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_QAM_STATUS_CMD;

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	core->rsp->qam_status.if_agc 		= ((((rspByteBuffer[1]) | (rspByteBuffer[0] << 8)) >> DEMOD_DD_QAM_STATUS_RESPONSE_IF_AGC_LSB) & DEMOD_DD_QAM_STATUS_RESPONSE_IF_AGC_MASK);
	core->rsp->qam_status.mse_info		= ((((rspByteBuffer[3]) | (rspByteBuffer[2] << 8)) >> DEMOD_DD_QAM_STATUS_RESPONSE_MSE_INFO_LSB) & DEMOD_DD_QAM_STATUS_RESPONSE_MSE_INFO_MASK) ;
	core->rsp->qam_status.ber		= ((((rspByteBuffer[6]) | (rspByteBuffer[5] << 8) | (rspByteBuffer[4] << 16)) >> DEMOD_DD_QAM_STATUS_RESPONSE_BER_LSB) & DEMOD_DD_QAM_STATUS_RESPONSE_BER_MASK);
	core->rsp->qam_status.cfo		= ((((rspByteBuffer[9]) | (rspByteBuffer[8] << 8) | (rspByteBuffer[7] << 16)) >> DEMOD_DD_QAM_STATUS_RESPONSE_CFO_LSB) & DEMOD_DD_QAM_STATUS_RESPONSE_CFO_MASK);
	core->rsp->qam_status.op_mode		= ((rspByteBuffer[10] >> DEMOD_DD_QAM_STATUS_RESPONSE_OP_MODE_LSB) & DEMOD_DD_QAM_STATUS_RESPONSE_OP_MODE_MASK);
	core->rsp->qam_status.pe 		= ((rspByteBuffer[11] >> DEMOD_DD_QAM_STATUS_RESPONSE_PE_LSB) & DEMOD_DD_QAM_STATUS_RESPONSE_PE_MASK);
	core->rsp->qam_status.spInv		= ((rspByteBuffer[12] >> DEMOD_DD_QAM_STATUS_RESPONSE_SPECINV_LSB) & DEMOD_DD_QAM_STATUS_RESPONSE_SPECINV_MASK);
	core->rsp->qam_status.constellation	= ((rspByteBuffer[12] >> DEMOD_DD_QAM_STATUS_RESPONSE_CONSTELLATION_LSB) & DEMOD_DD_QAM_STATUS_RESPONSE_CONSTELLATION_MASK);
	core->rsp->qam_status.sym_rate		= ((((rspByteBuffer[14]) | (rspByteBuffer[13] << 8)) >> DEMOD_DD_QAM_STATUS_RESPONSE_SYM_RATE_LSB) & DEMOD_DD_QAM_STATUS_RESPONSE_SYM_RATE_MASK);
	core->rsp->qam_status.sfo		= ((((rspByteBuffer[17]) | (rspByteBuffer[16] << 8) | (rspByteBuffer[15] << 16)) >> DEMOD_DD_QAM_STATUS_RESPONSE_SFO_LSB) & DEMOD_DD_QAM_STATUS_RESPONSE_SFO_MASK);
	core->rsp->qam_status.lock_carr		= ((rspByteBuffer[18]  >> DEMOD_DD_QAM_STATUS_RESPONSE_LOCK_CARR_LSB) & DEMOD_DD_QAM_STATUS_RESPONSE_LOCK_CARR_MASK);
	core->rsp->qam_status.lock_fec		= ((rspByteBuffer[18]  >> DEMOD_DD_QAM_STATUS_RESPONSE_LOCK_FEC_LSB) & DEMOD_DD_QAM_STATUS_RESPONSE_LOCK_FEC_MASK);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_PartInfo (LX_DEMOD_L1_Context * core)
{

	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	rspByte = 7;
	cmdByte = 1;
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_GET_PART_INFO_CMD;

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	core->rsp->part_info.fw_major 	= ((rspByteBuffer[0]  >> DEMOD_DD_GET_PART_INFO_FW_MAJOR_LSB) & DEMOD_DD_GET_PART_INFO_FW_MAJOR_MASK);
	core->rsp->part_info.fw_minor 	= ((rspByteBuffer[1]  >> DEMOD_DD_GET_PART_INFO_FW_MINOR_LSB) & DEMOD_DD_GET_PART_INFO_FW_MINOR_MASK);
	core->rsp->part_info.fw_year	= ((rspByteBuffer[2]  >> DEMOD_DD_GET_PART_INFO_FW_YEAR_LSB) & DEMOD_DD_GET_PART_INFO_FW_YEAR_MASK);
	core->rsp->part_info.fw_month 	= ((rspByteBuffer[3]  >> DEMOD_DD_GET_PART_INFO_FW_MONTH_LSB) & DEMOD_DD_GET_PART_INFO_FW_MONTH_MASK);
	core->rsp->part_info.fw_day   	= ((rspByteBuffer[4]  >> DEMOD_DD_GET_PART_INFO_FW_DAY_LSB) & DEMOD_DD_GET_PART_INFO_FW_DAY_MASK);
	core->rsp->part_info.chip_rev  	= ((rspByteBuffer[5]  >> DEMOD_DD_GET_PART_INFO_FW_CHIP_REV_LSB) & DEMOD_DD_GET_PART_INFO_FW_CHIP_REV_MASK);
	core->rsp->part_info.reserved 	= ((rspByteBuffer[6]  >> DEMOD_DD_GET_PART_INFO_FW_RESERVED_LSB) & DEMOD_DD_GET_PART_INFO_FW_RESERVED_MASK);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_SET_DD_Tune (LX_DEMOD_L1_Context * core)
{

	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	cmdByte=1;
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_SET_TUNE_CMD;

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_Status (LX_DEMOD_L1_Context * core)
{

	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;
//	UINT32 pucWordData = 0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	rspByte=2;
	cmdByte=1;
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_STATUS_CMD;

//	DEMOD_APB_Read(0x90, &pucWordData);
//	DEMOD_PRINT("\n ########## 1 : DEMOD_APB_Read pucWordData = 0x%x	address = 0x%x########## \n\n", pucWordData, rspByteBuffer);

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	core->rsp->dd_status.reply_operMod	= ((rspByteBuffer[0]  >> DEMOD_DD_STATUS_RESPONSE_MODULATION_LSB) & DEMOD_DD_STATUS_RESPONSE_MODULATION_MASK);
	core->rsp->dd_status.lock_fec		= ((rspByteBuffer[1]  >> DEMOD_DD_STATUS_RESPONSE_LOCK_FEC_LSB) & DEMOD_DD_STATUS_RESPONSE_LOCK_FEC_MASK);
	core->rsp->dd_status.neverLock		= ((rspByteBuffer[1]  >> DEMOD_DD_STATUS_RESPONSE_NEVERLOCK_LSB) & DEMOD_DD_STATUS_RESPONSE_NEVERLOCK_MASK);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_DD_STATUS_CMD */



#ifdef DEMOD_DD_TSCLK_STATUS_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_GET_DD_TSCLK_Status.
 * sets demoduator register through MCU
 *
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_TSCLK_Status (LX_DEMOD_L1_Context * core)
{

	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;
//	UINT32 pucWordData = 0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	rspByte=4;
	cmdByte=1;
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_TSCLK_STATUS_CMD;

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	core->rsp->dd_tsclk_status.tsClkRate	= ((((rspByteBuffer[3]) | (rspByteBuffer[2] << 8) | (rspByteBuffer[1] << 16) | (rspByteBuffer[0] << 24)) >> DEMOD_DD_TSCLK_STATUS_RESPONSE_TSCLKRATE_LSB) & DEMOD_DD_TSCLK_STATUS_RESPONSE_TSCLKRATE_MASK);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 			[IN] LX_DEMOD_L1_Context
 * @param plp_id			[IN] UINT8
 * @param plp_id_sel_mode	[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_SET_DD_ATSC3_PLP_Select (LX_DEMOD_L1_Context * core,  UINT8 plp0_id,  UINT8 plp1_id,  UINT8 plp2_id,  UINT8 plp3_id)
{

	int err = 0;
	UINT8 cmdByteBuffer[8]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	cmdByte=5;
	rspByte=1;
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_ATSC3_PLP_SELECT_CMD;
	cmdByteBuffer[1] =(UINT8)( ( plp0_id & DEMOD_DD_ATSC3_PLP_SELECT_CMD_PLP_ID_MASK     ) << DEMOD_DD_ATSC3_PLP_SELECT_CMD_PLP_ID_LSB );
	cmdByteBuffer[2] =(UINT8)( ( plp1_id & DEMOD_DD_ATSC3_PLP_SELECT_CMD_PLP_ID_MASK     ) << DEMOD_DD_ATSC3_PLP_SELECT_CMD_PLP_ID_LSB );
	cmdByteBuffer[3] =(UINT8)( ( plp2_id & DEMOD_DD_ATSC3_PLP_SELECT_CMD_PLP_ID_MASK     ) << DEMOD_DD_ATSC3_PLP_SELECT_CMD_PLP_ID_LSB );
	cmdByteBuffer[4] =(UINT8)( ( plp3_id & DEMOD_DD_ATSC3_PLP_SELECT_CMD_PLP_ID_MASK     ) << DEMOD_DD_ATSC3_PLP_SELECT_CMD_PLP_ID_LSB );

	core->last_plp0 = plp0_id & 0x7f;
	core->last_plp1 = plp1_id & 0x7f;
	core->last_plp2 = plp2_id & 0x7f;
	core->last_plp3 = plp3_id & 0x7f;
	
	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	core->rsp->atsc3_plp_select.plp_select_return_code = ((rspByteBuffer[0]  >> DEMOD_DD_ATSC3_PLP_SELECT_CMD_PLP_ID_LSB ) & DEMOD_DD_ATSC3_PLP_SELECT_CMD_PLP_ID_MASK);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 			[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_ATSC3_Status (LX_DEMOD_L1_Context * core)
{

	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	rspByte=36;
	cmdByte=1;
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_ATSC3_STATUS_CMD;

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

			core->rsp->atsc3_status.ber				= 0x00000000;
			core->rsp->atsc3_status.pe				= 0x0000;	// [packet err] process should determine on L2
			core->rsp->atsc3_status.if_agc			= ((((rspByteBuffer[1]  ) | (rspByteBuffer[0]  << 8 )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_IF_AGC_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_IF_AGC_MASK);

			core->rsp->atsc3_status.ctf_pwr			= (( ((rspByteBuffer[5]  ) | (rspByteBuffer[4]  << 8 ) | (rspByteBuffer[3]  << 16 ) | (rspByteBuffer[2]  << 24 )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_CTF_PWR_LSB     ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_CTF_PWR_MASK     );
			core->rsp->atsc3_status.mse_info_demod	= (( ( (rspByteBuffer[9]  ) | (rspByteBuffer[8]  << 8 ) | (rspByteBuffer[7]  << 16 ) | (rspByteBuffer[6]  << 24)) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_MSE_INFO_DEMOD_LSB     ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_MSE_INFO_DEMOD_MASK     );
			core->rsp->atsc3_status.mse_info			= (( ((rspByteBuffer[13]  ) | (rspByteBuffer[12]  << 8 ) | (rspByteBuffer[11]  << 16 ) | (rspByteBuffer[10] << 24 )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_MSE_INFO_LSB     ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_MSE_INFO_MASK     );
			core->rsp->atsc3_status.sfo				= (( ( (rspByteBuffer[16]  ) | (rspByteBuffer[15]  << 8 ) | (rspByteBuffer[14]  << 16 )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_SFO_LSB     ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_SFO_MASK     );
			core->rsp->atsc3_status.cfo				= (( ( (rspByteBuffer[19]  ) | (rspByteBuffer[18]  << 8 ) | (rspByteBuffer[17]  << 16 )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_CFO_LSB     ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_CFO_MASK     );
			core->rsp->atsc3_status.spInv			= (( (rspByteBuffer[20]) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_SPECINV_LSB) & DEMOD_DD_ATSC3_STATUS_RESPONSE_SPECINV_MASK);
			core->rsp->atsc3_status.lock_carr		= (( (rspByteBuffer[20]) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_LOCK_CARR_LSB) & DEMOD_DD_ATSC3_STATUS_RESPONSE_LOCK_CARR_MASK);
			core->rsp->atsc3_status.bandwidth		= (( (rspByteBuffer[20]) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_BANDWIDTH_LSB) & DEMOD_DD_ATSC3_STATUS_RESPONSE_BANDWIDTH_MASK);
			core->rsp->atsc3_status.plp_exist		= (( (rspByteBuffer[20]) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_PLP_EXIST_LSB) & DEMOD_DD_ATSC3_STATUS_RESPONSE_PLP_EXIST_MASK);

			core->rsp->atsc3_status.ldpc_err			= (( ( (rspByteBuffer[22]  ) | (rspByteBuffer[21]  << 8 )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_LDPC_ERR_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_LDPC_ERR_MASK);
			core->rsp->atsc3_status.plp_ldpc_iter	= (( ( (rspByteBuffer[23]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_PLP_LDPC_ITER_LSB     ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_PLP_LDPC_ITER_MASK     );
			core->rsp->atsc3_status.l1b_ldpc_iter	= (( ( (rspByteBuffer[24]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_L1B_LDPC_ITER_LSB     ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_L1B_LDPC_ITER_MASK     );
			core->rsp->atsc3_status.l1d_ldpc_iter	= (( ( (rspByteBuffer[25]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_L1D_LDPC_ITER_LSB     ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_L1D_LDPC_ITER_MASK     );
			core->rsp->atsc3_status.plp_outer_err	= (( ( (rspByteBuffer[27]  ) | (rspByteBuffer[26]  << 8 )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_PE_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_PE_MASK);
			core->rsp->atsc3_status.op_mode			= (( ( (rspByteBuffer[28] )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_OP_MODE_LSB        ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_OP_MODE_MASK        );
			core->rsp->atsc3_status.done_bs			= (( ( (rspByteBuffer[29]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_DONE_BS_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_DONE_BS_MASK      );
			core->rsp->atsc3_status.done_acq			= (( ( (rspByteBuffer[29]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_DONE_ACQ_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_DONE_ACQ_MASK      );
			core->rsp->atsc3_status.lock_l1b			= (( ( (rspByteBuffer[29]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_LOCK_L1B_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_LOCK_L1B_MASK      );
			core->rsp->atsc3_status.lock_l1d			= (( ( (rspByteBuffer[29]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_LOCK_L1D_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_LOCK_L1D_MASK      );
			core->rsp->atsc3_status.init_sts_done	= (( ( (rspByteBuffer[30]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_INIT_STS_DONE_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_INIT_STS_DONE_MASK      );
			core->rsp->atsc3_status.plp_ldpc_ok		= (( ( (rspByteBuffer[30]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_PLP_LDPC_OK_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_PLP_LDPC_OK_MASK      );
			core->rsp->atsc3_status.l1b_ldpc_ok		= (( ( (rspByteBuffer[30]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_L1B_LDPC_OK_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_L1B_LDPC_OK_MASK      );
			core->rsp->atsc3_status.ti_eq			= (( ( (rspByteBuffer[30]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_TI_EQ_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_TI_EQ_MASK      );
			core->rsp->atsc3_status.l1d_ldpc_ok		= (( ( (rspByteBuffer[30]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_L1D_LDPC_OK_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_L1D_LDPC_OK_MASK      );
			core->rsp->atsc3_status.plp_err_msg		= rspByteBuffer[31]&0xff;

			core->rsp->atsc3_status.plp_pkerr_0		= (( ( (rspByteBuffer[32]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_PLP_PKERR0_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_PLP_PKERR0_MASK      );
			core->rsp->atsc3_status.plp_pkerr_1		= (( ( (rspByteBuffer[33]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_PLP_PKERR1_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_PLP_PKERR1_MASK      );
			core->rsp->atsc3_status.plp_pkerr_2		= (( ( (rspByteBuffer[34]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_PLP_PKERR2_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_PLP_PKERR2_MASK      );
			core->rsp->atsc3_status.plp_pkerr_3		= (( ( (rspByteBuffer[35]  )) >> DEMOD_DD_ATSC3_STATUS_RESPONSE_PLP_PKERR3_LSB      ) & DEMOD_DD_ATSC3_STATUS_RESPONSE_PLP_PKERR3_MASK      );


	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @param index			[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_ATSC3_PLP_ID (LX_DEMOD_L1_Context * core)
{

	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	rspByte=32;
	cmdByte=1;
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_ATSC3_PLP_ID_CMD;

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	core->rsp->atsc3_plp_id.plp_id_flag		=((((UINT64)(rspByteBuffer[7] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_PLP_ID_FLAG_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_PLP_ID_FLAG_MASK        ) << 56)
												| ((((UINT64)(rspByteBuffer[6] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_PLP_ID_FLAG_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_PLP_ID_FLAG_MASK        ) << 48)
												| ((((UINT64)(rspByteBuffer[5] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_PLP_ID_FLAG_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_PLP_ID_FLAG_MASK        ) << 40)
												| ((((UINT64)(rspByteBuffer[4] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_PLP_ID_FLAG_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_PLP_ID_FLAG_MASK        ) << 32)
												| ((((UINT64)(rspByteBuffer[3] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_PLP_ID_FLAG_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_PLP_ID_FLAG_MASK        ) << 24)
												| ((((UINT64)(rspByteBuffer[2] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_PLP_ID_FLAG_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_PLP_ID_FLAG_MASK        ) << 16)
												| ((((UINT64)(rspByteBuffer[1] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_PLP_ID_FLAG_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_PLP_ID_FLAG_MASK        ) << 8)
												| ((((UINT64)(rspByteBuffer[0] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_PLP_ID_FLAG_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_PLP_ID_FLAG_MASK        ) << 0);
	
	core->rsp->atsc3_plp_id.lls_valid			=((((UINT64)(rspByteBuffer[15] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LLS_VALID_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LLS_VALID_MASK        )<<56)
												| ((((UINT64)(rspByteBuffer[14] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LLS_VALID_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LLS_VALID_MASK        )<<48)
												| ((((UINT64)(rspByteBuffer[13] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LLS_VALID_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LLS_VALID_MASK        )<<40)
												| ((((UINT64)(rspByteBuffer[12] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LLS_VALID_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LLS_VALID_MASK        )<<32)
												| ((((UINT64)(rspByteBuffer[11] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LLS_VALID_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LLS_VALID_MASK        )<<24)
												| ((((UINT64)(rspByteBuffer[10] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LLS_VALID_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LLS_VALID_MASK        )<<16)
												| ((((UINT64)(rspByteBuffer[9] ) >>  DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LLS_VALID_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LLS_VALID_MASK        )<<8)
												| ((((UINT64)(rspByteBuffer[8] ) >>  DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LLS_VALID_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LLS_VALID_MASK        )<<0);
	
	core->rsp->atsc3_plp_id.ldm_mode				=((((UINT64)(rspByteBuffer[23] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LDM_MODE_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LDM_MODE_MASK        )<<56)
												| ((((UINT64)(rspByteBuffer[22] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LDM_MODE_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LDM_MODE_MASK        )<<48)
												| ((((UINT64)(rspByteBuffer[21] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LDM_MODE_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LDM_MODE_MASK        )<<40)
												| ((((UINT64)(rspByteBuffer[20] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LDM_MODE_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LDM_MODE_MASK        )<<32)
												| ((((UINT64)(rspByteBuffer[19] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LDM_MODE_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LDM_MODE_MASK        )<<24)
												| ((((UINT64)(rspByteBuffer[18] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LDM_MODE_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LDM_MODE_MASK        )<<16)
												| ((((UINT64)(rspByteBuffer[17] ) >>  DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LDM_MODE_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LDM_MODE_MASK        )<<8)
												| ((((UINT64)(rspByteBuffer[16] ) >>  DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LDM_MODE_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_LDM_MODE_MASK        )<<0);

	core->rsp->atsc3_plp_id.ti_mode				=((((UINT64)(rspByteBuffer[31] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_TI_MODE_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_TI_MODE_MASK        )<<56)
												| ((((UINT64)(rspByteBuffer[30] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_TI_MODE_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_TI_MODE_MASK        )<<48)
												| ((((UINT64)(rspByteBuffer[29] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_TI_MODE_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_TI_MODE_MASK        )<<40)
												| ((((UINT64)(rspByteBuffer[28] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_TI_MODE_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_TI_MODE_MASK        )<<32)
												| ((((UINT64)(rspByteBuffer[27] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_TI_MODE_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_TI_MODE_MASK        )<<24)
												| ((((UINT64)(rspByteBuffer[26] ) >> DEMOD_DD_ATSC3_PLP_ID_RESPONSE_TI_MODE_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_TI_MODE_MASK        )<<16)
												| ((((UINT64)(rspByteBuffer[25] ) >>  DEMOD_DD_ATSC3_PLP_ID_RESPONSE_TI_MODE_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_TI_MODE_MASK        )<<8)
												| ((((UINT64)(rspByteBuffer[24] ) >>  DEMOD_DD_ATSC3_PLP_ID_RESPONSE_TI_MODE_LSB        ) & DEMOD_DD_ATSC3_PLP_ID_RESPONSE_TI_MODE_MASK        )<<0);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @param index			[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/

int DEMOD_L1_GET_DD_ATSC3_PLP_Info (LX_DEMOD_L1_Context * core, UINT8 index)
{

	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	rspByte=25;
	cmdByte=2;
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_ATSC3_PLP_INFO_CMD;
	cmdByteBuffer[1] = (UINT8)index;

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	core->rsp->atsc3_plp_info.bs_pre_str					=(( ( (rspByteBuffer[0]  )) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_BS_PRE_STR_LSB     ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_BS_PRE_STR_MASK     );
	core->rsp->atsc3_plp_info.bs_l1b_mode					=(( ( (rspByteBuffer[0]  )) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_BS_L1B_MODE_LSB     ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_BS_L1B_MODE_MASK     );
	core->rsp->atsc3_plp_info.l1b_num_subframes 			=((( rspByteBuffer[1] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_NUM_SUBFRAMES_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_NUM_SUBFRAMES_MASK        );
	core->rsp->atsc3_plp_info.subframe_sel					=((( rspByteBuffer[2] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_SUBFRAME_SEL_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_SUBFRAME_SEL_MASK        );
	core->rsp->atsc3_plp_info.l1d_mode						=((( rspByteBuffer[3] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_MODE_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_MODE_MASK        );
	core->rsp->atsc3_plp_info.l1b_pre_num_symbols			=(((rspByteBuffer[3] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_PRE_NUM_SYMBOLS_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_PRE_NUM_SYMBOLS_MASK        );
	core->rsp->atsc3_plp_info.l1b_num_ofdm_symbols			=((((rspByteBuffer[5]  ) | (rspByteBuffer[4] << 8 )) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_NUM_OFDM_SYMBOLS_LSB      ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_NUM_OFDM_SYMBOLS_MASK);
	core->rsp->atsc3_plp_info.l1b_sub_fft_size				=(((rspByteBuffer[6] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_FFT_SIZE_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_FFT_SIZE_MASK        );
	core->rsp->atsc3_plp_info.l1b_sub_gi					=(((rspByteBuffer[6] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_GI_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_GI_MASK        );
	core->rsp->atsc3_plp_info.l1b_reduce_carr				=(((rspByteBuffer[7] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_REDUCE_CARR_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_REDUCE_CARR_MASK        );
	core->rsp->atsc3_plp_info.l1b_sub_scatt_pp				=(((rspByteBuffer[8] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SCATT_PP_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SCATT_PP_MASK        );
	core->rsp->atsc3_plp_info.l1b_sub_scatt_pb				=(((rspByteBuffer[8] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SCATT_PB_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SCATT_PB_MASK        );
	core->rsp->atsc3_plp_info.l1b_sub_sbs_first				=(((rspByteBuffer[9] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SBS_FIRST_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SBS_FIRST_MASK        );
	core->rsp->atsc3_plp_info.l1b_sub_sbs_last				=(((rspByteBuffer[9] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SBS_LAST_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SBS_LAST_MASK        );
	core->rsp->atsc3_plp_info.num_plp						=(((rspByteBuffer[10] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_NUM_PLP_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_NUM_PLP_MASK        );
	core->rsp->atsc3_plp_info.plpinfo_sel					=(((rspByteBuffer[10] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLPINFO_SEL_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLPINFO_SEL_MASK        );
	core->rsp->atsc3_plp_info.plp_ti_mode					=(((rspByteBuffer[11] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_TI_MODE_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_TI_MODE_MASK        );
	core->rsp->atsc3_plp_info.plp_fec_type					=(((rspByteBuffer[11] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_FEC_TYPE_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_FEC_TYPE_MASK        );
	core->rsp->atsc3_plp_info.plp_mod						=(((rspByteBuffer[12] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_MASK        );
	core->rsp->atsc3_plp_info.plp_cr						=(((rspByteBuffer[12] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_MASK        );
	core->rsp->atsc3_plp_info.l1d_ap_mode					=(((rspByteBuffer[13] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_AP_MODE_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_AP_MODE_MASK        );
	core->rsp->atsc3_plp_info.plp0_layer					=(((rspByteBuffer[13] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP0_LAYER_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP0_LAYER_MASK        );
	core->rsp->atsc3_plp_info.plp1_layer					=(((rspByteBuffer[13] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP1_LAYER_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP1_LAYER_MASK        );
	core->rsp->atsc3_plp_info.plp2_layer					=(((rspByteBuffer[13] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP2_LAYER_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP2_LAYER_MASK        );
	core->rsp->atsc3_plp_info.plp3_layer					=(((rspByteBuffer[13] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP3_LAYER_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP3_LAYER_MASK        );
	core->rsp->atsc3_plp_info.l1d_segment					=(((rspByteBuffer[14] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_SEGMENT_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_SEGMENT_MASK        );
	core->rsp->atsc3_plp_info.bs_pre_str_mode				=(((rspByteBuffer[15] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_BS_PSTR_MODE_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_BS_PSTR_MODE_MASK        );
	core->rsp->atsc3_plp_info.bs_minor						=(((rspByteBuffer[16] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_BS_MINOR_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_BS_MINOR_MASK        );
	core->rsp->atsc3_plp_info.easinfo						=(((rspByteBuffer[16] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_EASINFO_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_EASINFO_MASK        );
	core->rsp->atsc3_plp_info.l1d_plp_type					=(((rspByteBuffer[17] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_TYPE_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_TYPE_MASK        );	// for Mplp 161209
	core->rsp->atsc3_plp_info.plpn_layer					=(((rspByteBuffer[17] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLPN_LAYER_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLPN_LAYER_MASK        );		// for Mplp 161209
	core->rsp->atsc3_plp_info.m2n							=(((rspByteBuffer[17] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_M2N_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_M2N_MASK        );
	core->rsp->atsc3_plp_info.bsr							=(((rspByteBuffer[18] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_BSR_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_BSR_MASK        );
	core->rsp->atsc3_plp_info.bs_sym						=(((rspByteBuffer[19] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_BS_SYM_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_BS_SYM_MASK        );
	core->rsp->atsc3_plp_info.frame_mode					=(((rspByteBuffer[19] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_FRAME_MODE_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_FRAME_MODE_MASK        );
	core->rsp->atsc3_plp_info.plp_fi_mode					=(((rspByteBuffer[19] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_FI_MODE_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_FI_MODE_MASK        );
	core->rsp->atsc3_plp_info.frame_length_info				=((((rspByteBuffer[23] ) | (rspByteBuffer[22] << 8 ) | (rspByteBuffer[21] << 16 ) | (rspByteBuffer[20] << 24 )) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_FRAME_LENGTH_INFO_LSB      ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_FRAME_LENGTH_INFO_MASK);
	core->rsp->atsc3_plp_info.num_plp_total					=(((rspByteBuffer[24] ) >> DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_NUM_PLP_TOTAL_LSB        ) & DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_NUM_PLP_TOTAL_MASK        );				

	core->rsp->atsc3_plp_info.bs_l1b_mode					+= 1;
	core->rsp->atsc3_plp_info.l1b_num_subframes				+= 1;
	core->rsp->atsc3_plp_info.l1b_pre_num_symbols			+= 1;
	core->rsp->atsc3_plp_info.l1b_num_ofdm_symbols			+= 1;
	core->rsp->atsc3_plp_info.num_plp						+= 1;
	core->rsp->atsc3_plp_info.l1d_mode						+= 1;
	
	DEMOD_L0_UnlockDevice(core->chip);
	return err;

}
#endif /* DEMOD_DD_ATSC3_PLP_INFO_CMD */

#ifdef DEMOD_DD_ATSC3_SUBFRM_INFO_CMD // B17C0, C1 Only
int  DEMOD_L1_GET_DD_ATSC3_SUBFRM_Info(LX_DEMOD_L1_Context * core)
{
	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	rspByte=24;
	cmdByte=1;
	
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_ATSC3_SUBFRM_INFO_CMD;

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);


	core->rsp->atsc3_sbfrm_info.sbfrm_number[0]					= (((rspByteBuffer[0] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_NUMBER_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_NUMBER_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_num_ofdm_symbols[0]		=((((rspByteBuffer[2]  ) | (rspByteBuffer[1] << 8 )) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_NUM_OFDM_SYMBOLS_LSB      ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_NUM_OFDM_SYMBOLS_MASK);
	core->rsp->atsc3_sbfrm_info.sbfrm_fft_size[0]				=(((rspByteBuffer[3] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_FFT_SIZE_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_FFT_SIZE_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_gi[0]						=(((rspByteBuffer[3] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_GI_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_GI_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_reduce_carr[0]			=(((rspByteBuffer[4] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_REDUCE_CARR_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_REDUCE_CARR_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_sbs_first[0]				=(((rspByteBuffer[4] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SBS_FIRST_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SBS_FIRST_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_sbs_last[0]				=(((rspByteBuffer[4] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SBS_LAST_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SBS_LAST_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_scatt_pp[0]				=(((rspByteBuffer[5] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SCATT_PP_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SCATT_PP_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_scatt_pb[0]				=(((rspByteBuffer[5] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SCATT_PB_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SCATT_PB_MASK        );
	
	core->rsp->atsc3_sbfrm_info.sbfrm_number[1]					= (((rspByteBuffer[6] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_NUMBER_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_NUMBER_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_num_ofdm_symbols[1]		=((((rspByteBuffer[8]  ) | (rspByteBuffer[7] << 8 )) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_NUM_OFDM_SYMBOLS_LSB      ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_NUM_OFDM_SYMBOLS_MASK);
	core->rsp->atsc3_sbfrm_info.sbfrm_fft_size[1]				=(((rspByteBuffer[9] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_FFT_SIZE_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_FFT_SIZE_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_gi[1]						=(((rspByteBuffer[9] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_GI_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_GI_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_reduce_carr[1]			=(((rspByteBuffer[10] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_REDUCE_CARR_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_REDUCE_CARR_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_sbs_first[1]				=(((rspByteBuffer[10] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SBS_FIRST_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SBS_FIRST_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_sbs_last[1]				=(((rspByteBuffer[10] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SBS_LAST_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SBS_LAST_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_scatt_pp[1]				=(((rspByteBuffer[11] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SCATT_PP_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SCATT_PP_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_scatt_pb[1]				=(((rspByteBuffer[11] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SCATT_PB_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SCATT_PB_MASK        );
	
	core->rsp->atsc3_sbfrm_info.sbfrm_number[2]					= (((rspByteBuffer[12] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_NUMBER_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_NUMBER_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_num_ofdm_symbols[2]		=((((rspByteBuffer[14]  ) | (rspByteBuffer[13] << 8 )) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_NUM_OFDM_SYMBOLS_LSB      ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_NUM_OFDM_SYMBOLS_MASK);
	core->rsp->atsc3_sbfrm_info.sbfrm_fft_size[2]				=(((rspByteBuffer[15] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_FFT_SIZE_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_FFT_SIZE_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_gi[2]						=(((rspByteBuffer[15] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_GI_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_GI_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_reduce_carr[2]			=(((rspByteBuffer[16] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_REDUCE_CARR_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_REDUCE_CARR_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_sbs_first[2]				=(((rspByteBuffer[16] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SBS_FIRST_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SBS_FIRST_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_sbs_last[2]				=(((rspByteBuffer[16] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SBS_LAST_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SBS_LAST_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_scatt_pp[2]				=(((rspByteBuffer[17] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SCATT_PP_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SCATT_PP_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_scatt_pb[2]				=(((rspByteBuffer[17] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SCATT_PB_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SCATT_PB_MASK        );

	core->rsp->atsc3_sbfrm_info.sbfrm_number[3]					= (((rspByteBuffer[18] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_NUMBER_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_NUMBER_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_num_ofdm_symbols[3]		=((((rspByteBuffer[20]  ) | (rspByteBuffer[19] << 8 )) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_NUM_OFDM_SYMBOLS_LSB      ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_NUM_OFDM_SYMBOLS_MASK);
	core->rsp->atsc3_sbfrm_info.sbfrm_fft_size[3]				=(((rspByteBuffer[21] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_FFT_SIZE_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_FFT_SIZE_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_gi[3]						=(((rspByteBuffer[21] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_GI_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_GI_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_reduce_carr[3]			=(((rspByteBuffer[22] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_REDUCE_CARR_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_REDUCE_CARR_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_sbs_first[3]				=(((rspByteBuffer[22] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SBS_FIRST_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SBS_FIRST_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_sbs_last[3]				=(((rspByteBuffer[22] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SBS_LAST_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SBS_LAST_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_scatt_pp[3]				=(((rspByteBuffer[23] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SCATT_PP_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SCATT_PP_MASK        );
	core->rsp->atsc3_sbfrm_info.sbfrm_scatt_pb[3]				=(((rspByteBuffer[23] ) >> DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SCATT_PB_LSB        ) & DEMOD_DD_ATSC3_SUBFRM_INFO_RESPONSE_SBFRM_SCATT_PB_MASK        );
		
	core->rsp->atsc3_sbfrm_info.sbfrm_num_ofdm_symbols[0]		+= 1;
	core->rsp->atsc3_sbfrm_info.sbfrm_num_ofdm_symbols[1]		+= 1;
	core->rsp->atsc3_sbfrm_info.sbfrm_num_ofdm_symbols[2]		+= 1;
	core->rsp->atsc3_sbfrm_info.sbfrm_num_ofdm_symbols[3]		+= 1;
	

	//DBB_PRINT("core->rsp->atsc3_sbfrm_info.sbfrm_number[0]	\t%d\n",core->rsp->atsc3_sbfrm_info.sbfrm_number[0]	);
	//DBB_PRINT("core->rsp->atsc3_sbfrm_info.sbfrm_number[0]	\t%d\n",core->rsp->atsc3_sbfrm_info.sbfrm_number[1]	);

	return NO_DEMOD_ERROR;

}
#endif /* DEMOD_DD_ATSC3_SUBFRM_INFO_CMD */

/*************************************************************************************/
/*************************************************************************************/
/*********ISDB-T/ DVBC / DVBC2/ DVBT / DVBT2/DVBS / DVBS2 / DEBUG/ functions **********/
/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/


#ifdef DEMOD_DD_ISDBT_BASEADDR_AXI_CMD
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_SET_DD_ISDBT_BASEADDR_AXI.
 * sets demoduator register through MCU
 *
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @param baseAddr		[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_SET_DD_ISDBT_BASEADDR_AXI (LX_DEMOD_L1_Context * core, UINT32 baseAddr)
{

	int err = 0;
	UINT8 cmdByteBuffer[8]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	cmdByte = 8;
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_ISDBT_BASEADDR_AXI_CMD;
	cmdByteBuffer[1] = 0;
	cmdByteBuffer[2] = 0;
	cmdByteBuffer[3] = 0;
	cmdByteBuffer[4] = (UINT8)(((baseAddr & DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_BASEADDR_LSB) >>  0);
	cmdByteBuffer[5] = (UINT8)(((baseAddr & DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_BASEADDR_LSB) >>  8);
	cmdByteBuffer[6] = (UINT8)(((baseAddr & DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_BASEADDR_LSB) >> 16);
	cmdByteBuffer[7] = (UINT8)(((baseAddr & DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_BASEADDR_LSB) >> 24);

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @param baseAddr		[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_SET_DD_DTMB_BASEADDR_AXI (LX_DEMOD_L1_Context * core, UINT32 baseAddr)
{

	int err = 0;
	UINT8 cmdByteBuffer[8]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	cmdByte = 8;

	cmdByteBuffer[0] = (UINT8)DEMOD_DD_DTMB_BASEADDR_AXI_CMD;
	cmdByteBuffer[1] = 0;
	cmdByteBuffer[2] = 0;
	cmdByteBuffer[3] = 0;
	cmdByteBuffer[4] = (UINT8)(((baseAddr & DEMOD_DD_DTMB_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_DTMB_BASEADDR_AXI_CMD_BASEADDR_LSB) >>  0);
	cmdByteBuffer[5] = (UINT8)(((baseAddr & DEMOD_DD_DTMB_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_DTMB_BASEADDR_AXI_CMD_BASEADDR_LSB) >>  8);
	cmdByteBuffer[6] = (UINT8)(((baseAddr & DEMOD_DD_DTMB_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_DTMB_BASEADDR_AXI_CMD_BASEADDR_LSB) >> 16);
	cmdByteBuffer[7] = (UINT8)(((baseAddr & DEMOD_DD_DTMB_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_DTMB_BASEADDR_AXI_CMD_BASEADDR_LSB) >> 24);

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param * core			[IN] LX_DEMOD_L1_Context
 * @param auto_en 		[IN] UINT8
 * @param sym_rate 		[IN] UINT16
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_SET_DD_SymbolRate_Detect (LX_DEMOD_L1_Context * core, UINT8 auto_en, UINT16 sym_rate)
{

	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	cmdByte=4;
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_DVBC_SRD_CMD;
	cmdByteBuffer[1] = (UINT8)((auto_en & DEMOD_DD_DVBC_SRD_CMD_AUTO_EN_MASK) << DEMOD_DD_DVBC_SRD_CMD_AUTO_EN_LSB);
	cmdByteBuffer[2] = (UINT8)((sym_rate & DEMOD_DD_DVBC_SRD_CMD_SYM_RATE1_MASK) >> DEMOD_DD_DVBC_SRD_CMD_SYM_RATE1_SHIFT );
	cmdByteBuffer[3] = (UINT8)((sym_rate & DEMOD_DD_DVBC_SRD_CMD_SYM_RATE2_MASK) >> DEMOD_DD_DVBC_SRD_CMD_SYM_RATE2_LSB);

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 			[IN] LX_DEMOD_L1_Context
 * @param plp_id			[IN] UINT8
 * @param plp_id_sel_mode	[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_SET_DD_DVBT2_PLP_Select (LX_DEMOD_L1_Context * core,  UINT8 plp_id, UINT8   plp_id_sel_mode)
{

	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	cmdByte=3;
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_DVBT2_PLP_SELECT_CMD;
	cmdByteBuffer[1] = (UINT8)((plp_id & DEMOD_DD_DVBT2_PLP_SELECT_CMD_PLP_ID_MASK) << DEMOD_DD_DVBT2_PLP_SELECT_CMD_PLP_ID_LSB);
	cmdByteBuffer[2] = (UINT8)((plp_id_sel_mode & DEMOD_DD_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MASK) << DEMOD_DD_DVBT2_PLP_SELECT_CMD_PLP_ID_SEL_MODE_LSB);

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 			[IN] LX_DEMOD_L1_Context
 * @param freq				[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_SET_DD_DVBC2_StartFrequency (LX_DEMOD_L1_Context * core, UINT32 freq)
{

	int err = 0;
	UINT8 cmdByteBuffer[8]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	cmdByte=5;
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_DVBC2_STARTFREQUENCY_CMD;
	cmdByteBuffer[1] = (UINT8)(((freq & DEMOD_DD_DVBC2_STARTFREQUENCY_CMD_FREQ_MASK) << DEMOD_DD_DVBC2_STARTFREQUENCY_CMD_FREQ_LSB) >> 24);
   	cmdByteBuffer[2] = (UINT8)(((freq & DEMOD_DD_DVBC2_STARTFREQUENCY_CMD_FREQ_MASK) << DEMOD_DD_DVBC2_STARTFREQUENCY_CMD_FREQ_LSB) >> 16);
   	cmdByteBuffer[3] = (UINT8)(((freq & DEMOD_DD_DVBC2_STARTFREQUENCY_CMD_FREQ_MASK) << DEMOD_DD_DVBC2_STARTFREQUENCY_CMD_FREQ_LSB) >>  8);
   	cmdByteBuffer[4] = (UINT8)(((freq & DEMOD_DD_DVBC2_STARTFREQUENCY_CMD_FREQ_MASK) << DEMOD_DD_DVBC2_STARTFREQUENCY_CMD_FREQ_LSB) >>  0);

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 			[IN] LX_DEMOD_L1_Context
 * @param plp_id			[IN] UINT8
 * @param plp_id_mode		[IN] UINT8
 * @param ds_id				[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_SET_DD_DVBC2_PLP_Select (LX_DEMOD_L1_Context * core,  UINT8 plp_id, UINT8 plp_id_mode, UINT8 ds_id)
{

	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	cmdByte=4;
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_DVBC2_PLP_SELECT_CMD;
	cmdByteBuffer[1] = (UINT8)((plp_id_mode & DEMOD_DD_DVBC2_PLP_SELECT_CMD_PLP_ID_MODE_MASK) << DEMOD_DD_DVBC2_PLP_SELECT_CMD_PLP_ID_MODE_LSB);
	cmdByteBuffer[2] = (UINT8)((plp_id & DEMOD_DD_DVBC2_PLP_SELECT_CMD_PLP_ID_MASK) << DEMOD_DD_DVBC2_PLP_SELECT_CMD_PLP_ID_LSB);
	cmdByteBuffer[3] = (UINT8)((ds_id & DEMOD_DD_DVBC2_PLP_SELECT_CMD_DS_ID_MASK) << DEMOD_DD_DVBC2_PLP_SELECT_CMD_DS_ID_LSB);

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 			[IN] LX_DEMOD_L1_Context
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
int DEMOD_L1_SET_DD_DISEQC_Send (LX_DEMOD_L1_Context * core,
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
	int err = 0;
	UINT8 cmdByteBuffer[8]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	cmdByte=8;
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_DISEQC_SEND_CMD;
	cmdByteBuffer[1] = (UINT8)((diseqc_en & DEMOD_DD_DISEQC_SEND_CMD_DISEQC_EN_MASK) << DEMOD_DD_DISEQC_SEND_CMD_DISEQC_EN_LSB |
                                         ( tone_burst & DEMOD_DD_DISEQC_SEND_CMD_TONE_BURST_MASK) << DEMOD_DD_DISEQC_SEND_CMD_TONE_BURST_LSB |
                                         ( cont_tone & DEMOD_DD_DISEQC_SEND_CMD_CONT_TONE_MASK) << DEMOD_DD_DISEQC_SEND_CMD_CONT_TONE_LSB |
                                         ( burst_sel& DEMOD_DD_DISEQC_SEND_CMD_BURST_SEL_MASK) << DEMOD_DD_DISEQC_SEND_CMD_BURST_SEL_LSB |
                                         ( msg_length     & DEMOD_DD_DISEQC_SEND_CMD_MSG_LENGTH_MASK) << DEMOD_DD_DISEQC_SEND_CMD_MSG_LENGTH_LSB);

	cmdByteBuffer[2] = (UINT8)((send_framing & DEMOD_DD_DISEQC_SEND_CMD_SEND_FRAMING_MASK) << DEMOD_DD_DISEQC_SEND_CMD_SEND_FRAMING_LSB);
	cmdByteBuffer[3] = (UINT8)	(( send_address & DEMOD_DD_DISEQC_SEND_CMD_SEND_ADDRESS_MASK) << DEMOD_DD_DISEQC_SEND_CMD_SEND_ADDRESS_LSB);
	cmdByteBuffer[4] = (UINT8)	(( send_command & DEMOD_DD_DISEQC_SEND_CMD_SEND_COMMAND_MASK) << DEMOD_DD_DISEQC_SEND_CMD_SEND_COMMAND_LSB);
	cmdByteBuffer[5] = (UINT8)	(( send_data0 & DEMOD_DD_DISEQC_SEND_CMD_SEND_DATA0_MASK) << DEMOD_DD_DISEQC_SEND_CMD_SEND_DATA0_LSB);
	cmdByteBuffer[6] = (UINT8)	(( send_data1 & DEMOD_DD_DISEQC_SEND_CMD_SEND_DATA1_MASK) << DEMOD_DD_DISEQC_SEND_CMD_SEND_DATA1_LSB);
	cmdByteBuffer[7] = (UINT8)	(( send_data2 & DEMOD_DD_DISEQC_SEND_CMD_SEND_DATA2_MASK) << DEMOD_DD_DISEQC_SEND_CMD_SEND_DATA2_LSB);

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 			[IN] LX_DEMOD_L1_Context
 * @param opmSel			[IN] UINT8
 * @param symbolRate_Khz	[IN] UINT32
 * @param tuneFreq_Khz		[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_SET_DD_DVBS_Blind_Scan_Mode (LX_DEMOD_L1_Context * core, UINT8 opmSel, UINT32 symbolRate_Khz, UINT32 tuneFreq_Khz)
{

	int err = 0;
	UINT8 cmdByteBuffer[12]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	cmdByte=10;
	cmdByteBuffer[0] = (UINT8)DEMOD_DD_DVBS_OPERATING_MODE_CMD;
  	cmdByteBuffer[1] = (UINT8)((opmSel & DEMOD_DD_DVBS_OPERATING_MODE_CMD_OPM_SEL_MASK) << DEMOD_DD_DVBS_OPERATING_MODE_CMD_OPM_SEL_LSB);
	cmdByteBuffer[2] = (UINT8)(((symbolRate_Khz & DEMOD_DD_DVBS_OPERATING_MODE_CMD_SYMBOL_RATE_MASK) << DEMOD_DD_DVBS_OPERATING_MODE_CMD_SYMBOL_RATE_LSB) >> 24);
	cmdByteBuffer[3] = (UINT8)(((symbolRate_Khz & DEMOD_DD_DVBS_OPERATING_MODE_CMD_SYMBOL_RATE_MASK) << DEMOD_DD_DVBS_OPERATING_MODE_CMD_SYMBOL_RATE_LSB) >> 16);
	cmdByteBuffer[4] = (UINT8)(((symbolRate_Khz & DEMOD_DD_DVBS_OPERATING_MODE_CMD_SYMBOL_RATE_MASK) << DEMOD_DD_DVBS_OPERATING_MODE_CMD_SYMBOL_RATE_LSB) >>  8);
	cmdByteBuffer[5] = (UINT8)((symbolRate_Khz & DEMOD_DD_DVBS_OPERATING_MODE_CMD_SYMBOL_RATE_MASK) << DEMOD_DD_DVBS_OPERATING_MODE_CMD_SYMBOL_RATE_LSB);
	cmdByteBuffer[6] = (UINT8)(((tuneFreq_Khz & DEMOD_DD_DVBS_OPERATING_MODE_CMD_TUNE_FREQ3_MASK) << DEMOD_DD_DVBS_OPERATING_MODE_CMD_TUN_FREQ3_LSB) >> 24);
	cmdByteBuffer[7] = (UINT8)(((tuneFreq_Khz & DEMOD_DD_DVBS_OPERATING_MODE_CMD_TUNE_FREQ2_MASK) << DEMOD_DD_DVBS_OPERATING_MODE_CMD_TUN_FREQ2_LSB) >> 16);
	cmdByteBuffer[8] = (UINT8)(((tuneFreq_Khz & DEMOD_DD_DVBS_OPERATING_MODE_CMD_TUNE_FREQ1_MASK) << DEMOD_DD_DVBS_OPERATING_MODE_CMD_TUN_FREQ1_LSB) >>  8);
	cmdByteBuffer[9] = (UINT8)((tuneFreq_Khz & DEMOD_DD_DVBS_OPERATING_MODE_CMD_TUNE_FREQ0_MASK) << DEMOD_DD_DVBS_OPERATING_MODE_CMD_TUN_FREQ0_LSB);

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
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
int DEMOD_L1_SET_DD_SelfRst (LX_DEMOD_L1_Context * core, UINT8  rst_arg, UINT16 rst_time1, UINT16 rst_time2, UINT16 rst_time3, UINT16 rst_time4, UINT8 rst_cnt, UINT16 plp0_thd, UINT16 plp1_thd, UINT16 plp2_thd, UINT16 plp3_thd)
{

	int err = 0;
	UINT8 cmdByteBuffer[20]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	//cmdByte=11;
	cmdByte=20;
	cmdByteBuffer[0]  = (UINT8)DEMOD_DD_SELFRST_CMD;
	cmdByteBuffer[1]  = (UINT8)((rst_arg	& DEMOD_DD_SELFRST_CMD_RST_ARG_MASK) >> DEMOD_DD_SELFRST_CMD_RST_ARG_LSB);
	cmdByteBuffer[2]  = (UINT8)((rst_time1	& DEMOD_DD_SELFRST_CMD_RST_TIME1_MASK) >> DEMOD_DD_SELFRST_CMD_RST_TIME1_LSB);
	cmdByteBuffer[3]  = (UINT8)((rst_time1	& DEMOD_DD_SELFRST_CMD_RST_TIME2_MASK) >> DEMOD_DD_SELFRST_CMD_RST_TIME2_LSB);
	cmdByteBuffer[4]  = (UINT8)((rst_time2	& DEMOD_DD_SELFRST_CMD_RST_TIME1_MASK) >> DEMOD_DD_SELFRST_CMD_RST_TIME1_LSB);
	cmdByteBuffer[5]  = (UINT8)((rst_time2	& DEMOD_DD_SELFRST_CMD_RST_TIME2_MASK) >> DEMOD_DD_SELFRST_CMD_RST_TIME2_LSB);
	cmdByteBuffer[6]  = (UINT8)((rst_time3	& DEMOD_DD_SELFRST_CMD_RST_TIME1_MASK) >> DEMOD_DD_SELFRST_CMD_RST_TIME1_LSB);
	cmdByteBuffer[7]  = (UINT8)((rst_time3	& DEMOD_DD_SELFRST_CMD_RST_TIME2_MASK) >> DEMOD_DD_SELFRST_CMD_RST_TIME2_LSB);
	cmdByteBuffer[8]  = (UINT8)((rst_time4	& DEMOD_DD_SELFRST_CMD_RST_TIME1_MASK) >> DEMOD_DD_SELFRST_CMD_RST_TIME1_LSB);
	cmdByteBuffer[9]  = (UINT8)((rst_time4	& DEMOD_DD_SELFRST_CMD_RST_TIME2_MASK) >> DEMOD_DD_SELFRST_CMD_RST_TIME2_LSB);
	cmdByteBuffer[10] = (UINT8)((rst_cnt	& DEMOD_DD_SELFRST_CMD_RST_ARG_MASK) >> DEMOD_DD_SELFRST_CMD_RST_ARG_LSB);

	//For ATSC 3.0//
	cmdByteBuffer[11] = (UINT8) ( ( plp0_thd  & 0xFF00) >> 8 );
	cmdByteBuffer[12] = (UINT8) (plp0_thd  & 0x00FF);
	cmdByteBuffer[13] = (UINT8) ( ( plp1_thd  & 0xFF00) >> 8 );
	cmdByteBuffer[14] = (UINT8) (plp1_thd  & 0x00FF);
	cmdByteBuffer[15] = (UINT8) ( ( plp2_thd  & 0xFF00) >> 8 );
	cmdByteBuffer[16] = (UINT8) (plp2_thd  & 0x00FF);
	cmdByteBuffer[17] = (UINT8) ( ( plp3_thd  & 0xFF00) >> 8 );
	cmdByteBuffer[18] = (UINT8) (plp3_thd  & 0x00FF);
	
	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_DVBT2_Status (LX_DEMOD_L1_Context * core)
{

	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	rspByte=28;
	cmdByte=1;
	cmdByteBuffer[0] = DEMOD_DD_DVBT2_STATUS_CMD;

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	core->rsp->dvbt2_status.if_agc			= ((((rspByteBuffer[1]) | (rspByteBuffer[0] << 8)) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_IF_AGC_LSB) & DEMOD_DD_DVBT2_STATUS_RESPONSE_IF_AGC_MASK);
	core->rsp->dvbt2_status.mse_info		= ((((rspByteBuffer[3]) | (rspByteBuffer[2] << 8)) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_MSE_INFO_LSB) & DEMOD_DD_DVBT2_STATUS_RESPONSE_MSE_INFO_MASK);
	core->rsp->dvbt2_status.ber			= (((rspByteBuffer[6] << 0 ) | ((rspByteBuffer[5] << 8) | (rspByteBuffer[4] << 16)) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_BER_LSB) & DEMOD_DD_DVBT2_STATUS_RESPONSE_BER_MASK);
	core->rsp->dvbt2_status.cfo			= ((((rspByteBuffer[9]) | (rspByteBuffer[8] << 8) | (rspByteBuffer[7] << 16)) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_CFO_LSB) & DEMOD_DD_DVBT2_STATUS_RESPONSE_CFO_MASK);
	core->rsp->dvbt2_status.op_mode			= ((((rspByteBuffer[10])) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_OP_MODE_LSB) & DEMOD_DD_DVBT2_STATUS_RESPONSE_OP_MODE_MASK);
	core->rsp->dvbt2_status.pe			= ((((rspByteBuffer[11])) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_PE_LSB) & DEMOD_DD_DVBT2_STATUS_RESPONSE_PE_MASK);
	core->rsp->dvbt2_status.spInv			= ((((rspByteBuffer[12])) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_SPECINV_LSB) & DEMOD_DD_DVBT2_STATUS_RESPONSE_SPECINV_MASK);
	core->rsp->dvbt2_status.fft_mode		= ((((rspByteBuffer[12])) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_FFT_MODE_LSB) & DEMOD_DD_DVBT2_STATUS_RESPONSE_FFT_MODE_MASK);
	core->rsp->dvbt2_status.gi			= ((((rspByteBuffer[12])) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_LSB) & DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_MASK);
	core->rsp->dvbt2_status.constellation		= ((((rspByteBuffer[13])) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_CONSTELLATION_LSB) & DEMOD_DD_DVBT2_STATUS_RESPONSE_CONSTELLATION_MASK);
	core->rsp->dvbt2_status.constellation_cm	= ((((rspByteBuffer[13])) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_CONSTELLATION_CM_LSB) & DEMOD_DD_DVBT2_STATUS_RESPONSE_CONSTELLATION_CM_MASK);
	core->rsp->dvbt2_status.cr   			= ((((rspByteBuffer[14])) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_LSB) & DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_MASK);
	core->rsp->dvbt2_status.cr_cm   		= ((((rspByteBuffer[14])) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_CM_LSB) & DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_CM_MASK);
	core->rsp->dvbt2_status.current_plp_id		= ((((rspByteBuffer[15])) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_CURRENT_PLP_ID_LSB) & DEMOD_DD_DVBT2_STATUS_RESPONSE_CURRENT_PLP_ID_MASK);
	core->rsp->dvbt2_status.current_plp_id_cm	= ((((rspByteBuffer[16])) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_CURRENT_PLP_ID_CM_LSB) & DEMOD_DD_DVBT2_STATUS_RESPONSE_CURRENT_PLP_ID_CM_MASK);
	core->rsp->dvbt2_status.num_plp			= ((((rspByteBuffer[17])) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_NUM_PLP_LSB) & DEMOD_DD_DVBT2_STATUS_RESPONSE_NUM_PLP_MASK);
	core->rsp->dvbt2_status.num_dplp		= ((((rspByteBuffer[18])) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_NUM_DPLP_LSB) & DEMOD_DD_DVBT2_STATUS_RESPONSE_NUM_DPLP_MASK);
	core->rsp->dvbt2_status.sfo			= ((((rspByteBuffer[21]) | (rspByteBuffer[20] << 8) | (rspByteBuffer[19] << 16)) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_SFO_LSB) & DEMOD_DD_DVBT2_STATUS_RESPONSE_SFO_MASK);
	core->rsp->dvbt2_status.lock_carr		= ((((rspByteBuffer[22])) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_LOCK_CARR_LSB) & DEMOD_DD_DVBT2_STATUS_RESPONSE_LOCK_CARR_MASK);
	core->rsp->dvbt2_status.lock_fec		= ((((rspByteBuffer[22])) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_LOCK_FEC_LSB) & DEMOD_DD_DVBT2_STATUS_RESPONSE_LOCK_FEC_MASK);
	core->rsp->dvbt2_status.mse_info_demod		= ((((rspByteBuffer[25]) | (rspByteBuffer[24] << 8)) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_MSE_INFO_DEMOD_LSB) & DEMOD_DD_DVBT2_STATUS_RESPONSE_MSE_INFO_DEMOD_MASK);
	core->rsp->dvbt2_status.cell_id			= ((((rspByteBuffer[27]) | (rspByteBuffer[26] << 8)) >> DEMOD_DD_DVBT2_STATUS_RESPONSE_CELL_ID_LSB) & DEMOD_DD_DVBT2_STATUS_RESPONSE_CELL_ID_MASK);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @param index			[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_DVBT2_PLP_ID (LX_DEMOD_L1_Context * core, UINT8 index)
{

	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	rspByte=2;
	cmdByte=2;
	cmdByteBuffer[0] = DEMOD_DD_GET_DVBT2_PLP_ID_CMD;
	cmdByteBuffer[1] = index;

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	core->rsp->dvbt2_plp_id.plp_id			=(((rspByteBuffer[0]) >> DEMOD_DD_GET_DVBT2_PLP_ID_RESPONSE_PLP_ID_LSB) & DEMOD_DD_GET_DVBT2_PLP_ID_RESPONSE_PLP_ID_MASK);
	core->rsp->dvbt2_plp_id.plp_conf		=(((rspByteBuffer[1]) >> DEMOD_DD_GET_DVBT2_PLP_ID_RESPONSE_PLP_CONF_LSB) & DEMOD_DD_GET_DVBT2_PLP_ID_RESPONSE_PLP_CONF_MASK);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_DVBT_Status (LX_DEMOD_L1_Context * core)
{

	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	rspByte=26;
	cmdByte=1;
	cmdByteBuffer[0] = DEMOD_DD_DVBT_STATUS_CMD;

#ifdef	FPGA_RDK_M17_PRINT
	DEMOD_PRINT("\n ########## DEMOD_L1_GET_DD_DVBT_Status ########## \n\n");
#endif

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	core->rsp->dvbt_status.if_agc			= ((((rspByteBuffer[1]) | (rspByteBuffer[0] << 8)) >> DEMOD_DD_DVBT_STATUS_RESPONSE_IF_AGC_LSB) & DEMOD_DD_DVBT_STATUS_RESPONSE_IF_AGC_MASK);
	core->rsp->dvbt_status.mse_info			= ((((rspByteBuffer[3]) | (rspByteBuffer[2] << 8)) >> DEMOD_DD_DVBT_STATUS_RESPONSE_MSE_INFO_LSB) & DEMOD_DD_DVBT_STATUS_RESPONSE_MSE_INFO_MASK) ;
	core->rsp->dvbt_status.ber			= ((((rspByteBuffer[6]) | (rspByteBuffer[5] <<8) | (rspByteBuffer[4] << 16)) >> DEMOD_DD_DVBT_STATUS_RESPONSE_BER_LSB) & DEMOD_DD_DVBT_STATUS_RESPONSE_BER_MASK);
	core->rsp->dvbt_status.cfo			= ((((rspByteBuffer[9]) | (rspByteBuffer[8] << 8) | (rspByteBuffer[7] << 16)) >> DEMOD_DD_DVBT_STATUS_RESPONSE_CFO_LSB) & DEMOD_DD_DVBT_STATUS_RESPONSE_CFO_MASK);
	core->rsp->dvbt_status.op_mode			= ((rspByteBuffer[10] >> DEMOD_DD_DVBT_STATUS_RESPONSE_OP_MODE_LSB) & DEMOD_DD_DVBT_STATUS_RESPONSE_OP_MODE_MASK);
	core->rsp->dvbt_status.pe			= ((rspByteBuffer[11] >> DEMOD_DD_DVBT_STATUS_RESPONSE_PE_LSB) & DEMOD_DD_DVBT_STATUS_RESPONSE_PE_MASK);
	core->rsp->dvbt_status.spInv			= ((rspByteBuffer[12] >> DEMOD_DD_DVBT_STATUS_RESPONSE_SPECINV_LSB) & DEMOD_DD_DVBT_STATUS_RESPONSE_SPECINV_MASK);
	core->rsp->dvbt_status.fft_mode    		= ((rspByteBuffer[12] >> DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_LSB) & DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_MASK);
	core->rsp->dvbt_status.gi			= ((rspByteBuffer[12] >> DEMOD_DD_DVBT_STATUS_RESPONSE_GI_LSB) & DEMOD_DD_DVBT_STATUS_RESPONSE_GI_MASK);
	core->rsp->dvbt_status.tps_length		= ((rspByteBuffer[13] >> DEMOD_DD_DVBT_STATUS_RESPONSE_TPS_LENGTH_LSB) & DEMOD_DD_DVBT_STATUS_RESPONSE_TPS_LENGTH_MASK);
	core->rsp->dvbt_status.cell_id			= ((((rspByteBuffer[15]) |(rspByteBuffer[14] << 8)) >> DEMOD_DD_DVBT_STATUS_RESPONSE_CELL_ID_LSB) & DEMOD_DD_DVBT_STATUS_RESPONSE_CELL_ID_MASK);
	core->rsp->dvbt_status.hierarchy		= ((rspByteBuffer[16] >> DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_LSB) & DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_MASK);
	core->rsp->dvbt_status.constellation		= ((rspByteBuffer[16] >> DEMOD_DD_DVBT_STATUS_RESPONSE_CONSTELLATION_LSB) & DEMOD_DD_DVBT_STATUS_RESPONSE_CONSTELLATION_MASK);
	core->rsp->dvbt_status.hp_cr			= ((rspByteBuffer[17] >> DEMOD_DD_DVBT_STATUS_RESPONSE_HP_CR_LSB) & DEMOD_DD_DVBT_STATUS_RESPONSE_HP_CR_MASK);
	core->rsp->dvbt_status.lp_cr			= ((rspByteBuffer[17] >> DEMOD_DD_DVBT_STATUS_RESPONSE_LP_CR_LSB) & DEMOD_DD_DVBT_STATUS_RESPONSE_LP_CR_MASK);
	core->rsp->dvbt_status.hierarchy_sel		= ((rspByteBuffer[17] >> DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_SEL_LSB) & DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_SEL_MASK);
	core->rsp->dvbt_status.sfo			= ((((rspByteBuffer[20]) | (rspByteBuffer[19] << 8) | (rspByteBuffer[18] << 16)) >> DEMOD_DD_DVBT_STATUS_RESPONSE_SFO_LSB) & DEMOD_DD_DVBT_STATUS_RESPONSE_SFO_MASK);
	core->rsp->dvbt_status.lock_carr		= ((rspByteBuffer[21] >> DEMOD_DD_DVBT_STATUS_RESPONSE_LOCK_CARR_LSB) & DEMOD_DD_DVBT_STATUS_RESPONSE_LOCK_CARR_MASK);
	core->rsp->dvbt_status.lock_fec			= ((rspByteBuffer[21] >> DEMOD_DD_DVBT_STATUS_RESPONSE_LOCK_FEC_LSB) & DEMOD_DD_DVBT_STATUS_RESPONSE_LOCK_FEC_MASK);
	core->rsp->dvbt_status.mse_info_demod		= ((((rspByteBuffer[23]) | (rspByteBuffer[22] << 8)) >> DEMOD_DD_DVBT_STATUS_RESPONSE_MSE_INFO_DEMOD_LSB) & DEMOD_DD_DVBT_STATUS_RESPONSE_MSE_INFO_DEMOD_MASK);
	core->rsp->dvbt_status.pe_1st			= ((rspByteBuffer[24] >> DEMOD_DD_DVBT_STATUS_RESPONSE_PE_1ST_LSB) & DEMOD_DD_DVBT_STATUS_RESPONSE_PE_1ST_MASK);
	core->rsp->dvbt_status.pe_2nd			= ((rspByteBuffer[25] >> DEMOD_DD_DVBT_STATUS_RESPONSE_PE_2ND_LSB) & DEMOD_DD_DVBT_STATUS_RESPONSE_PE_2ND_MASK);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_ISDBT_Status (LX_DEMOD_L1_Context * core)
{
	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	rspByte=19;
	cmdByte=1;
	cmdByteBuffer[0] =	DEMOD_DD_ISDBT_STATUS_CMD;

#ifdef	FPGA_RDK_M17_PRINT
	DEMOD_PRINT("\n ########## DEMOD_L1_GET_DD_ISDBT_Status ########## \n\n");
#endif

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	core->rsp->isdbt_status.if_agc			= ((((rspByteBuffer[1]) | (rspByteBuffer[0] << 8)) >> DEMOD_DD_ISDBT_STATUS_RESPONSE_IF_AGC_LSB	  ) & DEMOD_DD_ISDBT_STATUS_RESPONSE_IF_AGC_MASK);
	core->rsp->isdbt_status.mse_info 		= ((((rspByteBuffer[3]) | (rspByteBuffer[2] << 8)) >> DEMOD_DD_ISDBT_STATUS_RESPONSE_MSE_INFO_LSB) & DEMOD_DD_ISDBT_STATUS_RESPONSE_MSE_INFO_MASK) ;
	core->rsp->isdbt_status.ber			= ((((rspByteBuffer[6]) | (rspByteBuffer[5] << 8) | (rspByteBuffer[4] << 16)) >> DEMOD_DD_ISDBT_STATUS_RESPONSE_BER_LSB) & DEMOD_DD_ISDBT_STATUS_RESPONSE_BER_MASK);
	core->rsp->isdbt_status.cfo			= ((((rspByteBuffer[9]) | (rspByteBuffer[8] << 8) | (rspByteBuffer[7] << 16)) >> DEMOD_DD_ISDBT_STATUS_RESPONSE_CFO_LSB) & DEMOD_DD_ISDBT_STATUS_RESPONSE_CFO_MASK);
	core->rsp->isdbt_status.op_mode			= ((rspByteBuffer[10] >> DEMOD_DD_ISDBT_STATUS_RESPONSE_OP_MODE_LSB) & DEMOD_DD_ISDBT_STATUS_RESPONSE_OP_MODE_MASK);
	core->rsp->isdbt_status.pe			= ((rspByteBuffer[11] >> DEMOD_DD_ISDBT_STATUS_RESPONSE_PE_LSB) & DEMOD_DD_ISDBT_STATUS_RESPONSE_PE_MASK);
	core->rsp->isdbt_status.spInv			= ((rspByteBuffer[12] >> DEMOD_DD_ISDBT_STATUS_RESPONSE_SPECINV_LSB) & DEMOD_DD_ISDBT_STATUS_RESPONSE_SPECINV_MASK);
	core->rsp->isdbt_status.sfo			= ((((rspByteBuffer[15]) | (rspByteBuffer[14] << 8) | (rspByteBuffer[13] << 16 )) >> DEMOD_DD_ISDBT_STATUS_RESPONSE_SFO_LSB) & DEMOD_DD_ISDBT_STATUS_RESPONSE_SFO_MASK);
	core->rsp->isdbt_status.lock_carr		= ((rspByteBuffer[16]  >> DEMOD_DD_ISDBT_STATUS_RESPONSE_LOCK_CARR_LSB) & DEMOD_DD_ISDBT_STATUS_RESPONSE_LOCK_CARR_MASK);
	core->rsp->isdbt_status.lock_fec 		= ((rspByteBuffer[16]  >> DEMOD_DD_ISDBT_STATUS_RESPONSE_LOCK_FEC_LSB) & DEMOD_DD_ISDBT_STATUS_RESPONSE_LOCK_FEC_MASK);
	core->rsp->isdbt_status.mse_info_demod		= ((((rspByteBuffer[18]) | (rspByteBuffer[17] << 8)) >> DEMOD_DD_ISDBT_STATUS_RESPONSE_MSE_INFO_DEMOD_LSB) & DEMOD_DD_ISDBT_STATUS_RESPONSE_MSE_INFO_DEMOD_MASK);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_ISDBT_TMCC_Info (LX_DEMOD_L1_Context * core)
{
	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	rspByte=7;
	cmdByte=1;
	cmdByteBuffer[0] = DEMOD_DD_ISDBT_TMCC_INFO_CMD;

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	core->rsp->isdbt_tmcc_info.fft_mode    		= ((rspByteBuffer[0]  >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_FFT_MODE_LSB) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_FFT_MODE_MASK);
	core->rsp->isdbt_tmcc_info.gi			= ((rspByteBuffer[0]  >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_LSB) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_MASK);
	core->rsp->isdbt_tmcc_info.oqama      		= ((((rspByteBuffer[1])) >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OQAMA_LSB) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OQAMA_MASK);
	core->rsp->isdbt_tmcc_info.ocra    	  	= ((((rspByteBuffer[1])) >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OCRA_LSB) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OCRA_MASK);
	core->rsp->isdbt_tmcc_info.oila    	  	= ((((rspByteBuffer[2])) >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OILA_LSB) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OILA_MASK);
	core->rsp->isdbt_tmcc_info.onsega     		= ((((rspByteBuffer[2])) >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_ONSEGA_LSB) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_ONSEGA_MASK);
	core->rsp->isdbt_tmcc_info.oqamb      		= ((((rspByteBuffer[3])) >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OQAMB_LSB) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OQAMB_MASK);
	core->rsp->isdbt_tmcc_info.ocrb     		= ((((rspByteBuffer[3])) >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OCRB_LSB) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OCRB_MASK);
	core->rsp->isdbt_tmcc_info.oilb      		= ((((rspByteBuffer[4])) >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OILB_LSB) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OILB_MASK);
	core->rsp->isdbt_tmcc_info.onsegb     		= ((((rspByteBuffer[4])) >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_ONSEGA_LSB) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_ONSEGA_MASK);
	core->rsp->isdbt_tmcc_info.oqamc      		= ((((rspByteBuffer[5])) >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OQAMC_LSB) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OQAMC_MASK);
	core->rsp->isdbt_tmcc_info.ocrc      		= ((((rspByteBuffer[5])) >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OCRC_LSB) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OCRC_MASK);
	core->rsp->isdbt_tmcc_info.oilc      		= ((((rspByteBuffer[6])) >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OILC_LSB) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_OILC_MASK);
	core->rsp->isdbt_tmcc_info.onsegc     		= ((((rspByteBuffer[6])) >> DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_ONSEGC_LSB) & DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_ONSEGC_MASK);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_DVBC_Status (LX_DEMOD_L1_Context * core)
{
	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	rspByte=19;
	cmdByte=1;
	cmdByteBuffer[0] = DEMOD_DD_DVBC_STATUS_CMD;

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	core->rsp->dvbc_status.if_agc			= ((((rspByteBuffer[1]) |(rspByteBuffer[0] << 8)) >> DEMOD_DD_DVBC_STATUS_RESPONSE_IF_AGC_LSB) & DEMOD_DD_DVBC_STATUS_RESPONSE_IF_AGC_MASK);
	core->rsp->dvbc_status.mse_info			= ((((rspByteBuffer[3]) | (rspByteBuffer[2] << 8)) >> DEMOD_DD_DVBC_STATUS_RESPONSE_MSE_INFO_LSB) & DEMOD_DD_DVBC_STATUS_RESPONSE_MSE_INFO_MASK) ;
	core->rsp->dvbc_status.ber			= ((((rspByteBuffer[6]) | (rspByteBuffer[5] <<8) | (rspByteBuffer[4] << 16)) >> DEMOD_DD_DVBC_STATUS_RESPONSE_BER_LSB) & DEMOD_DD_DVBC_STATUS_RESPONSE_BER_MASK);
	core->rsp->dvbc_status.cfo			= ((((rspByteBuffer[9]) | (rspByteBuffer[8] << 8) | (rspByteBuffer[7] << 16)) >> DEMOD_DD_DVBC_STATUS_RESPONSE_CFO_LSB) & DEMOD_DD_DVBC_STATUS_RESPONSE_CFO_MASK);
	core->rsp->dvbc_status.op_mode			= ((rspByteBuffer[10] >> DEMOD_DD_DVBC_STATUS_RESPONSE_OP_MODE_LSB) & DEMOD_DD_DVBC_STATUS_RESPONSE_OP_MODE_MASK);
	core->rsp->dvbc_status.pe			= ((rspByteBuffer[11] >> DEMOD_DD_DVBC_STATUS_RESPONSE_PE_LSB) & DEMOD_DD_DVBC_STATUS_RESPONSE_PE_MASK);
	core->rsp->dvbc_status.spInv			= ((rspByteBuffer[12] >> DEMOD_DD_DVBC_STATUS_RESPONSE_SPECINV_LSB) & DEMOD_DD_DVBC_STATUS_RESPONSE_SPECINV_MASK);
	core->rsp->dvbc_status.constellation		= ((rspByteBuffer[12] >> DEMOD_DD_DVBC_STATUS_RESPONSE_CONSTELLATION_LSB) & DEMOD_DD_DVBC_STATUS_RESPONSE_CONSTELLATION_MASK);
	core->rsp->dvbc_status.sym_rate      		= ((((rspByteBuffer[14]) | (rspByteBuffer[13] << 8)) >> DEMOD_DD_DVBC_STATUS_RESPONSE_SYM_RATE_LSB) & DEMOD_DD_DVBC_STATUS_RESPONSE_SYM_RATE_MASK);
	core->rsp->dvbc_status.sfo			= ((((rspByteBuffer[17]) | (rspByteBuffer[16] << 8) | (rspByteBuffer[15] << 16)) >> DEMOD_DD_DVBC_STATUS_RESPONSE_SFO_LSB) & DEMOD_DD_DVBC_STATUS_RESPONSE_SFO_MASK);
	core->rsp->dvbc_status.lock_carr		= ((rspByteBuffer[18]   >> DEMOD_DD_DVBC_STATUS_RESPONSE_LOCK_CARR_LSB) & DEMOD_DD_DVBC_STATUS_RESPONSE_LOCK_CARR_MASK);
	core->rsp->dvbc_status.lock_fec			= ((rspByteBuffer[18]   >> DEMOD_DD_DVBC_STATUS_RESPONSE_LOCK_FEC_LSB) & DEMOD_DD_DVBC_STATUS_RESPONSE_LOCK_FEC_MASK);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_DVBC2_Status (LX_DEMOD_L1_Context * core)
{
	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	rspByte=18;
	cmdByte=1;
	cmdByteBuffer[0] = DEMOD_DD_DVBC2_STATUS_CMD;

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	core->rsp->dvbc2_status.if_agc			= ((((((rspByteBuffer[1]) | (rspByteBuffer[0] << 8)) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_IF_AGC_LSB) & DEMOD_DD_DVBC2_STATUS_RESPONSE_IF_AGC_MASK) <<DEMOD_DD_DVBC2_STATUS_RESPONSE_IF_AGC_SHIFT ) >>DEMOD_DD_DVBC2_STATUS_RESPONSE_IF_AGC_SHIFT  );
	core->rsp->dvbc2_status.mse_info		= ((((((rspByteBuffer[3]) | (rspByteBuffer[2] << 8)) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_MSE_INFO_LSB) & DEMOD_DD_DVBC2_STATUS_RESPONSE_MSE_INFO_MASK) <<DEMOD_DD_DVBC2_STATUS_RESPONSE_MSE_INFO_SHIFT ) >>DEMOD_DD_DVBC2_STATUS_RESPONSE_MSE_INFO_SHIFT  );
	core->rsp->dvbc2_status.ber			= ((((((rspByteBuffer[5]) | (rspByteBuffer[4] << 8)) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_BER_LSB) & DEMOD_DD_DVBC2_STATUS_RESPONSE_BER_MASK) <<DEMOD_DD_DVBC2_STATUS_RESPONSE_BER_SHIFT ) >>DEMOD_DD_DVBC2_STATUS_RESPONSE_BER_SHIFT  );
	core->rsp->dvbc2_status.cfo			= ((((rspByteBuffer[9]) | (rspByteBuffer[8] << 8) | (rspByteBuffer[7] << 16) | (rspByteBuffer[6] << 24)) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_CFO_LSB) & DEMOD_DD_DVBC2_STATUS_RESPONSE_CFO_MASK);
	core->rsp->dvbc2_status.op_mode			= ((((rspByteBuffer[10])) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_OP_MODE_LSB) & DEMOD_DD_DVBC2_STATUS_RESPONSE_OP_MODE_MASK);
	core->rsp->dvbc2_status.pe			= ((((rspByteBuffer[11])) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_PE_LSB) & DEMOD_DD_DVBC2_STATUS_RESPONSE_PE_MASK);
	core->rsp->dvbc2_status.constellation		= ((((rspByteBuffer[12])) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_CONSTELLATION_LSB) & DEMOD_DD_DVBC2_STATUS_RESPONSE_CONSTELLATION_MASK);
	core->rsp->dvbc2_status.spInv			= ((((rspByteBuffer[12])) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_SPECINV_LSB) & DEMOD_DD_DVBC2_STATUS_RESPONSE_SPECINV_MASK);
	core->rsp->dvbc2_status.lock_tr			= ((((rspByteBuffer[13])) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_LOCK_TR_LSB) & DEMOD_DD_DVBC2_STATUS_RESPONSE_LOCK_TR_MASK);
	core->rsp->dvbc2_status.lock_carr		= ((((rspByteBuffer[13])) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_LOCK_CARR_LSB) & DEMOD_DD_DVBC2_STATUS_RESPONSE_LOCK_CARR_MASK);
	core->rsp->dvbc2_status.lock_psync		= ((((rspByteBuffer[13])) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_LOCK_PSYNC_LSB) & DEMOD_DD_DVBC2_STATUS_RESPONSE_LOCK_PSYNC_MASK);
	core->rsp->dvbc2_status.lock_fec		= ((((rspByteBuffer[13])) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_LOCK_FEC_LSB) & DEMOD_DD_DVBC2_STATUS_RESPONSE_LOCK_FEC_MASK);
	core->rsp->dvbc2_status.neverlock		= ((((rspByteBuffer[13])) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_NEVERLOCK_LSB) & DEMOD_DD_DVBC2_STATUS_RESPONSE_NEVERLOCK_MASK);
	core->rsp->dvbc2_status.cr    			= ((((rspByteBuffer[14])) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_CR_LSB) & DEMOD_DD_DVBC2_STATUS_RESPONSE_CR_MASK);
	core->rsp->dvbc2_status.current_plp_id		= ((((rspByteBuffer[15])) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_CURRENT_PLP_ID_LSB) & DEMOD_DD_DVBC2_STATUS_RESPONSE_CURRENT_PLP_ID_MASK);
	core->rsp->dvbc2_status.start_plp_id		= ((((rspByteBuffer[16])) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_START_PLP_ID_LSB) & DEMOD_DD_DVBC2_STATUS_RESPONSE_START_PLP_ID_MASK);
	core->rsp->dvbc2_status.multi_plp_id		= ((((rspByteBuffer[17])) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_MULTI_PLP_ID_LSB) & DEMOD_DD_DVBC2_STATUS_RESPONSE_MULTI_PLP_ID_MASK);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_DTMB_Status (LX_DEMOD_L1_Context * core)
{
	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	rspByte=19;
	cmdByte=1;
	cmdByteBuffer[0] = DEMOD_DD_DTMB_STATUS_CMD;

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	core->rsp->dtmb_status.if_agc			= ((((rspByteBuffer[1]) |(rspByteBuffer[0] << 8)) >> DEMOD_DD_DTMB_STATUS_RESPONSE_IF_AGC_LSB) & DEMOD_DD_DTMB_STATUS_RESPONSE_IF_AGC_MASK);
	core->rsp->dtmb_status.mse_info			= ((((rspByteBuffer[3]) | (rspByteBuffer[2] << 8)) >> DEMOD_DD_DTMB_STATUS_RESPONSE_MSE_INFO_LSB) & DEMOD_DD_DTMB_STATUS_RESPONSE_MSE_INFO_MASK) ;
	core->rsp->dtmb_status.ber			= ((((rspByteBuffer[6]) | (rspByteBuffer[5] <<8) | (rspByteBuffer[4] << 16)) >> DEMOD_DD_DTMB_STATUS_RESPONSE_BER_LSB) & DEMOD_DD_DTMB_STATUS_RESPONSE_BER_MASK);
	core->rsp->dtmb_status.cfo			= ((((rspByteBuffer[9]) | (rspByteBuffer[8] << 8) | (rspByteBuffer[7] << 16)) >> DEMOD_DD_DTMB_STATUS_RESPONSE_CFO_LSB) & DEMOD_DD_DTMB_STATUS_RESPONSE_CFO_MASK);
	core->rsp->dtmb_status.op_mode			= ((rspByteBuffer[10] >> DEMOD_DD_DTMB_STATUS_RESPONSE_OP_MODE_LSB) & DEMOD_DD_DTMB_STATUS_RESPONSE_OP_MODE_MASK);
	core->rsp->dtmb_status.pe			= ((rspByteBuffer[11] >> DEMOD_DD_DTMB_STATUS_RESPONSE_PE_LSB) & DEMOD_DD_DTMB_STATUS_RESPONSE_PE_MASK);
	core->rsp->dtmb_status.spInv			= ((rspByteBuffer[12] >> DEMOD_DD_DTMB_STATUS_RESPONSE_SPECINV_LSB) & DEMOD_DD_DTMB_STATUS_RESPONSE_SPECINV_MASK);
	core->rsp->dtmb_status.sfo			= ((((rspByteBuffer[15]) | (rspByteBuffer[14] << 8) | (rspByteBuffer[13] << 16)) >> DEMOD_DD_DTMB_STATUS_RESPONSE_SFO_LSB) & DEMOD_DD_DTMB_STATUS_RESPONSE_SFO_MASK);
	core->rsp->dtmb_status.il_mode			= ((rspByteBuffer[16]  >> DEMOD_DD_DTMB_STATUS_RESPONSE_IL_MODE_LSB) & DEMOD_DD_DTMB_STATUS_RESPONSE_IL_MODE_MASK);
	core->rsp->dtmb_status.constellation		= ((rspByteBuffer[16] >> DEMOD_DD_DTMB_STATUS_RESPONSE_CONSTELLATION_LSB) & DEMOD_DD_DTMB_STATUS_RESPONSE_CONSTELLATION_MASK);
	core->rsp->dtmb_status.carr_mode		= ((rspByteBuffer[17] >> DEMOD_DD_DTMB_STATUS_RESPONSE_CARR_MODE_LSB) & DEMOD_DD_DTMB_STATUS_RESPONSE_CARR_MODE_MASK);
	core->rsp->dtmb_status.pn_const			= ((rspByteBuffer[17] >> DEMOD_DD_DTMB_STATUS_RESPONSE_PN_CONST_LSB) & DEMOD_DD_DTMB_STATUS_RESPONSE_PN_CONST_MASK);
	core->rsp->dtmb_status.pn_mode			= ((rspByteBuffer[17] >> DEMOD_DD_DTMB_STATUS_RESPONSE_PN_MODE_LSB) & DEMOD_DD_DTMB_STATUS_RESPONSE_PN_MODE_MASK);
	core->rsp->dtmb_status.cr			= ((rspByteBuffer[17]  >> DEMOD_DD_DTMB_STATUS_RESPONSE_CR_LSB) & DEMOD_DD_DTMB_STATUS_RESPONSE_CR_MASK);
	core->rsp->dtmb_status.lock_carr		= ((rspByteBuffer[18]  >> DEMOD_DD_DTMB_STATUS_RESPONSE_LOCK_CARR_LSB) & DEMOD_DD_DTMB_STATUS_RESPONSE_LOCK_CARR_MASK);
	core->rsp->dtmb_status.lock_fec			= ((rspByteBuffer[18]  >> DEMOD_DD_DTMB_STATUS_RESPONSE_LOCK_FEC_LSB) & DEMOD_DD_DTMB_STATUS_RESPONSE_LOCK_FEC_MASK);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_DISEQC_Status (LX_DEMOD_L1_Context * core)
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_DVBS_Status (LX_DEMOD_L1_Context * core)
{
	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	rspByte=20;
	cmdByte=1;
	cmdByteBuffer[0] = DEMOD_DD_DVBS_STATUS_CMD;

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	core->rsp->dvbs_status.if_agc			= ((((rspByteBuffer[1]) |(rspByteBuffer[0] << 8)) >> DEMOD_DD_DVBS_STATUS_RESPONSE_IF_AGC_LSB) & DEMOD_DD_DVBS_STATUS_RESPONSE_IF_AGC_MASK);
	core->rsp->dvbs_status.mse_info			= ((((rspByteBuffer[3]) | (rspByteBuffer[2] << 8)) >> DEMOD_DD_DVBS_STATUS_RESPONSE_MSE_INFO_LSB) & DEMOD_DD_DVBS_STATUS_RESPONSE_MSE_INFO_MASK) ;
	core->rsp->dvbs_status.ber			= ((((rspByteBuffer[6]) | (rspByteBuffer[5] <<8) | (rspByteBuffer[4] << 16)) >> DEMOD_DD_DVBS_STATUS_RESPONSE_BER_LSB) & DEMOD_DD_DVBS_STATUS_RESPONSE_BER_MASK);
	core->rsp->dvbs_status.cfo			= ((((rspByteBuffer[9]) | (rspByteBuffer[8] << 8) | (rspByteBuffer[7] << 16)) >> DEMOD_DD_DVBS_STATUS_RESPONSE_CFO_LSB) & DEMOD_DD_DVBS_STATUS_RESPONSE_CFO_MASK);
	core->rsp->dvbs_status.op_mode			= ((rspByteBuffer[10] >> DEMOD_DD_DVBS_STATUS_RESPONSE_OP_MODE_LSB) & DEMOD_DD_DVBS_STATUS_RESPONSE_OP_MODE_MASK);
	core->rsp->dvbs_status.pe			= ((rspByteBuffer[11] >> DEMOD_DD_DVBS_STATUS_RESPONSE_PE_LSB) & DEMOD_DD_DVBS_STATUS_RESPONSE_PE_MASK);
	core->rsp->dvbs_status.spInv			= ((rspByteBuffer[12] >> DEMOD_DD_DVBS_STATUS_RESPONSE_SPECINV_LSB) & DEMOD_DD_DVBS_STATUS_RESPONSE_SPECINV_MASK);
	core->rsp->dvbs_status.constellation		= ((rspByteBuffer[12] >> DEMOD_DD_DVBS_STATUS_RESPONSE_CONSTELLATION_LSB) & DEMOD_DD_DVBS_STATUS_RESPONSE_CONSTELLATION_MASK);
	core->rsp->dvbs_status.sym_rate     	 	= ((((rspByteBuffer[14]) | (rspByteBuffer[13] << 8)) >> DEMOD_DD_DVBS_STATUS_RESPONSE_SYM_RATE_LSB) & DEMOD_DD_DVBS_STATUS_RESPONSE_SYM_RATE_MASK);
	core->rsp->dvbs_status.sfo			= ((((rspByteBuffer[17]) | (rspByteBuffer[16] << 8) | (rspByteBuffer[15] << 16)) >> DEMOD_DD_DVBS_STATUS_RESPONSE_SFO_LSB) & DEMOD_DD_DVBS_STATUS_RESPONSE_SFO_MASK);
	core->rsp->dvbs_status.cr			= ((rspByteBuffer[18]  >> DEMOD_DD_DVBS_STATUS_RESPONSE_CR_LSB) & DEMOD_DD_DVBS_STATUS_RESPONSE_CR_MASK);
	core->rsp->dvbs_status.lock_carr		= ((rspByteBuffer[19]  >> DEMOD_DD_DVBS_STATUS_RESPONSE_LOCK_CARR_LSB) & DEMOD_DD_DVBS_STATUS_RESPONSE_LOCK_CARR_MASK);
	core->rsp->dvbs_status.lock_fec			= ((rspByteBuffer[19]  >> DEMOD_DD_DVBS_STATUS_RESPONSE_LOCK_FEC_LSB) & DEMOD_DD_DVBS_STATUS_RESPONSE_LOCK_FEC_MASK);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_DVBS2_Status (LX_DEMOD_L1_Context * core)
{
	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	rspByte=20;
	cmdByte=1;
	cmdByteBuffer[0] = DEMOD_DD_DVBS2_STATUS_CMD;

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	core->rsp->dvbs2_status.if_agc			= ((((rspByteBuffer[1]) |(rspByteBuffer[0] << 8)) >> DEMOD_DD_DVBS2_STATUS_RESPONSE_IF_AGC_LSB) & DEMOD_DD_DVBS2_STATUS_RESPONSE_IF_AGC_MASK);
	core->rsp->dvbs2_status.mse_info		= ((((rspByteBuffer[3]) | (rspByteBuffer[2] << 8)) >> DEMOD_DD_DVBS2_STATUS_RESPONSE_MSE_INFO_LSB) & DEMOD_DD_DVBS2_STATUS_RESPONSE_MSE_INFO_MASK) ;
	core->rsp->dvbs2_status.ber			= ((((rspByteBuffer[6]) | (rspByteBuffer[5] <<8) | (rspByteBuffer[4] << 16)) >> DEMOD_DD_DVBS2_STATUS_RESPONSE_BER_LSB) & DEMOD_DD_DVBS2_STATUS_RESPONSE_BER_MASK);
	core->rsp->dvbs2_status.cfo			= ((((rspByteBuffer[9]) | (rspByteBuffer[8] << 8) | (rspByteBuffer[7] << 16)) >> DEMOD_DD_DVBS2_STATUS_RESPONSE_CFO_LSB) & DEMOD_DD_DVBS2_STATUS_RESPONSE_CFO_MASK);
	core->rsp->dvbs2_status.op_mode			= ((rspByteBuffer[10] >> DEMOD_DD_DVBS2_STATUS_RESPONSE_OP_MODE_LSB) & DEMOD_DD_DVBS2_STATUS_RESPONSE_OP_MODE_MASK);
	core->rsp->dvbs2_status.pe			= ((rspByteBuffer[11] >> DEMOD_DD_DVBS2_STATUS_RESPONSE_PE_LSB) & DEMOD_DD_DVBS2_STATUS_RESPONSE_PE_MASK);
	core->rsp->dvbs2_status.spInv			= ((rspByteBuffer[12] >> DEMOD_DD_DVBS2_STATUS_RESPONSE_SPECINV_LSB) & DEMOD_DD_DVBS2_STATUS_RESPONSE_SPECINV_MASK);
	core->rsp->dvbs2_status.constellation		= ((rspByteBuffer[12] >> DEMOD_DD_DVBS2_STATUS_RESPONSE_CONSTELLATION_LSB) & DEMOD_DD_DVBS2_STATUS_RESPONSE_CONSTELLATION_MASK);
	core->rsp->dvbs2_status.sym_rate      		= ((((rspByteBuffer[14]) | (rspByteBuffer[13] << 8)) >> DEMOD_DD_DVBS2_STATUS_RESPONSE_SYM_RATE_LSB) & DEMOD_DD_DVBS2_STATUS_RESPONSE_SYM_RATE_MASK);
	core->rsp->dvbs2_status.sfo			= ((((rspByteBuffer[17]) | (rspByteBuffer[16] << 8) | (rspByteBuffer[15] << 16)) >> DEMOD_DD_DVBS2_STATUS_RESPONSE_SFO_LSB) & DEMOD_DD_DVBS2_STATUS_RESPONSE_SFO_MASK);
	core->rsp->dvbs2_status.pp			= ((rspByteBuffer[18]  >> DEMOD_DD_DVBS2_STATUS_RESPONSE_PP_LSB) & DEMOD_DD_DVBS2_STATUS_RESPONSE_PP_MASK);
	core->rsp->dvbs2_status.cr			= ((rspByteBuffer[18]  >> DEMOD_DD_DVBS2_STATUS_RESPONSE_CR_LSB) & DEMOD_DD_DVBS2_STATUS_RESPONSE_CR_MASK);
	core->rsp->dvbs2_status.lock_carr		= ((rspByteBuffer[19]  >> DEMOD_DD_DVBS2_STATUS_RESPONSE_LOCK_CARR_LSB) & DEMOD_DD_DVBS2_STATUS_RESPONSE_LOCK_CARR_MASK);
	core->rsp->dvbs2_status.lock_fec		= ((rspByteBuffer[19]  >> DEMOD_DD_DVBS2_STATUS_RESPONSE_LOCK_FEC_LSB) & DEMOD_DD_DVBS2_STATUS_RESPONSE_LOCK_FEC_MASK);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_LOCKTIME (LX_DEMOD_L1_Context * core)
{
	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	rspByte=24;
	cmdByte=1;
	cmdByteBuffer[0] = DEMOD_DD_LOCKTIME_CMD;

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_DEBUG("timeStamp1 : %x\n", ((rspByteBuffer[ 3] << 24) | (rspByteBuffer[ 2] << 16) | (rspByteBuffer[ 1] << 8) | rspByteBuffer[ 0]));
	DEMOD_DEBUG("timeStamp2 : %x\n", ((rspByteBuffer[ 7] << 24) | (rspByteBuffer[ 6] << 16) | (rspByteBuffer[ 5] << 8) | rspByteBuffer[ 4]));
	DEMOD_DEBUG("timeStamp3 : %x\n", ((rspByteBuffer[11] << 24) | (rspByteBuffer[10] << 16) | (rspByteBuffer[ 9] << 8) | rspByteBuffer[ 8]));
	DEMOD_DEBUG("timeLock1  : %x\n", ((rspByteBuffer[15] << 24) | (rspByteBuffer[14] << 16) | (rspByteBuffer[13] << 8) | rspByteBuffer[12]));
	DEMOD_DEBUG("timeLock2  : %x\n", ((rspByteBuffer[19] << 24) | (rspByteBuffer[18] << 16) | (rspByteBuffer[17] << 8) | rspByteBuffer[16]));
	DEMOD_DEBUG("timeLock3  : %x\n", ((rspByteBuffer[23] << 24) | (rspByteBuffer[22] << 16) | (rspByteBuffer[21] << 8) | rspByteBuffer[20]));

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_SIGSRCH_NUM (LX_DEMOD_L1_Context * core)
{

	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	rspByte=1;
	cmdByte=1;
	cmdByteBuffer[0] = DEMOD_DD_GET_DD_SIGSRCH_NUM_CMD;

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	core->rsp->dd_sigsrch_num.ch_num			= ((rspByteBuffer[0]  >> DEMOD_DD_GET_DD_SIGSRCH_NUM_RESPONSE_CH_NUM_LSB) & DEMOD_DD_GET_DD_SIGSRCH_NUM_RESPONSE_CH_NUM_MASK);

	DEMOD_INFO("[DEMOD_API] Blind search : %d found\n", core->rsp->dd_sigsrch_num.ch_num);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_SIGSRCH_INFO (LX_DEMOD_L1_Context * core)
{
	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	rspByte=6;
	cmdByte=1;
	cmdByteBuffer[0] = DEMOD_DD_GET_DD_SIGSRCH_INFO_CMD;

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	core->rsp->dd_sigsrch_info.bw_idx		= ((((rspByteBuffer[1]) | (rspByteBuffer[0] << 8)) >> DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_BW_IDX_LSB) & DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_BW_IDX_MASK);
	core->rsp->dd_sigsrch_info.center_idx	= ((((rspByteBuffer[5]) | (rspByteBuffer[4] << 8) | (rspByteBuffer[3] << 16) | (rspByteBuffer[2] << 24)) >> DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_CENTER_IDX_LSB) & DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_CENTER_IDX_MASK);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_BLIND_Status (LX_DEMOD_L1_Context * core)
{
	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	rspByte=1;
	cmdByte=1;
	cmdByteBuffer[0] = DEMOD_DD_BLIND_STATUS_CMD;

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	core->rsp->blind_status.blindStatus		= ((rspByteBuffer[0]  >> DEMOD_DD_BLIND_STATUS_RESPONSE_BLINDSTATUS_LSB) & DEMOD_DD_BLIND_STATUS_RESPONSE_BLINDSTATUS_MASK);
	core->rsp->blind_status.blindDone		= ((rspByteBuffer[0]  >> DEMOD_DD_BLIND_STATUS_RESPONSE_BLINDDONE_LSB) & DEMOD_DD_BLIND_STATUS_RESPONSE_BLINDDONE_MASK);
	core->rsp->blind_status.blindLock		= ((rspByteBuffer[0]  >> DEMOD_DD_BLIND_STATUS_RESPONSE_BLINDLOCK_LSB) & DEMOD_DD_BLIND_STATUS_RESPONSE_BLINDLOCK_MASK);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @param startFreq		[IN] UINT32
 * @param endFreq		[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_BLIND_Init (LX_DEMOD_L1_Context * core, UINT32 startFreq, UINT32 endFreq)
{
	int err = 0;
	UINT8 cmdByteBuffer[12] = {0, };
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	cmdByte=9;

	cmdByteBuffer[0] = (UINT8)DEMOD_DD_BLIND_INIT_CMD;
	cmdByteBuffer[1] = (UINT8)((( startFreq  & DEMOD_DD_BLIND_INIT_CMD_STARTFREQ_MASK) << DEMOD_DD_BLIND_INIT_CMD_STARTFREQ_LSB) >>  0);
	cmdByteBuffer[2] = (UINT8)((( startFreq  & DEMOD_DD_BLIND_INIT_CMD_STARTFREQ_MASK) << DEMOD_DD_BLIND_INIT_CMD_STARTFREQ_LSB) >>  8);
	cmdByteBuffer[3] = (UINT8)((( startFreq  & DEMOD_DD_BLIND_INIT_CMD_STARTFREQ_MASK) << DEMOD_DD_BLIND_INIT_CMD_STARTFREQ_LSB) >> 16);
	cmdByteBuffer[4] = (UINT8)((( startFreq  & DEMOD_DD_BLIND_INIT_CMD_STARTFREQ_MASK) << DEMOD_DD_BLIND_INIT_CMD_STARTFREQ_LSB) >> 24);
	cmdByteBuffer[5] = (UINT8)((( endFreq    & DEMOD_DD_BLIND_INIT_CMD_ENDFREQ_MASK) << DEMOD_DD_BLIND_INIT_CMD_ENDFREQ_LSB) >>  0);
	cmdByteBuffer[6] = (UINT8)((( endFreq    & DEMOD_DD_BLIND_INIT_CMD_ENDFREQ_MASK) << DEMOD_DD_BLIND_INIT_CMD_ENDFREQ_LSB) >>  8);
	cmdByteBuffer[7] = (UINT8)((( endFreq    & DEMOD_DD_BLIND_INIT_CMD_ENDFREQ_MASK) << DEMOD_DD_BLIND_INIT_CMD_ENDFREQ_LSB) >> 16);
	cmdByteBuffer[8] = (UINT8)((( endFreq    & DEMOD_DD_BLIND_INIT_CMD_ENDFREQ_MASK) << DEMOD_DD_BLIND_INIT_CMD_ENDFREQ_LSB) >> 24);

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_BLIND_End (LX_DEMOD_L1_Context * core)
{
	int err = 0;
	UINT8 cmdByteBuffer[4] = {0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	cmdByte=1;
	cmdByteBuffer[0] = DEMOD_DD_BLIND_END_CMD;

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_GET_DD_BLIND_FoundInfo (LX_DEMOD_L1_Context * core)
{

	int err = 0;
	UINT8 cmdByteBuffer[4]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	rspByte=6;
	cmdByte=1;
	cmdByteBuffer[0] = DEMOD_DD_BLIND_FOUNDINFO_CMD;

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	core->rsp->blind_foundinfo.symrate		= ((((rspByteBuffer[1]) | (rspByteBuffer[0] << 8)) >> DEMOD_DD_BLIND_FOUNDINFO_RESPONSE_SYMRATE_LSB) & DEMOD_DD_BLIND_FOUNDINFO_RESPONSE_SYMRATE_MASK);
	core->rsp->blind_foundinfo.center		= ((((rspByteBuffer[5]) | (rspByteBuffer[4] << 8) | (rspByteBuffer[3] << 16) | (rspByteBuffer[2] << 24)) >> DEMOD_DD_BLIND_FOUNDINFO_RESPONSE_CENTER_LSB) & DEMOD_DD_BLIND_FOUNDINFO_RESPONSE_CENTER_MASK);//TO DO

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @param baseAddr1		[IN] UINT32
 * @param baseAddr2		[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_SET_DD_DVBT2_BASEADDR_AXI (LX_DEMOD_L1_Context * core, UINT32 baseAddr1, UINT32 baseAddr2)
{
	int err = 0;
	UINT8 cmdByteBuffer[12]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;


	cmdByte = 12;
	cmdByteBuffer[0]  = (UINT8)DEMOD_DD_DVBT2_BASEADDR_AXI_CMD;
	cmdByteBuffer[1]  = (UINT8)0;
	cmdByteBuffer[2]  = (UINT8)0;
	cmdByteBuffer[3]  = (UINT8)0;
	cmdByteBuffer[4]  = (UINT8)((baseAddr1 & DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_LSB);
	cmdByteBuffer[5]  = (UINT8)(((baseAddr1 & DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_LSB) >>  8);
	cmdByteBuffer[6]  = (UINT8)(((baseAddr1 & DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_LSB) >> 16);
	cmdByteBuffer[7]  = (UINT8)(((baseAddr1 & DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_LSB) >> 24);
	cmdByteBuffer[8]  = (UINT8)((baseAddr2 & DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_LSB);
	cmdByteBuffer[9]  = (UINT8)(((baseAddr2 & DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_LSB) >>  8);
	cmdByteBuffer[10] = (UINT8)(((baseAddr2 & DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_LSB) >> 16);
	cmdByteBuffer[11] = (UINT8)(((baseAddr2 & DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_BASEADDR_LSB) >> 24);

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
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
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @param baseAddr1		[IN] UINT32
 * @param baseAddr2		[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_SET_DD_DVB_BASEADDR_AXI (LX_DEMOD_L1_Context * core, UINT32 baseAddr1, UINT32 baseAddr2, UINT32 baseAddr3)
{
	int err = 0;
	UINT8 cmdByteBuffer[16]={0,};
	UINT8 cmdByte=0;
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	cmdByte = 16;
	cmdByteBuffer[0]  = (UINT8)DEMOD_DD_DVB_BASEADDR_AXI_CMD;
	cmdByteBuffer[1]  = (UINT8)0;
	cmdByteBuffer[2]  = (UINT8)0;
	cmdByteBuffer[3]  = (UINT8)0;
	cmdByteBuffer[4]  = (UINT8)((baseAddr1 & DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_LSB);
	cmdByteBuffer[5]  = (UINT8)(((baseAddr1 & DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_LSB) >>  8);
	cmdByteBuffer[6]  = (UINT8)(((baseAddr1 & DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_LSB) >> 16);
	cmdByteBuffer[7]  = (UINT8)(((baseAddr1 & DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_LSB) >> 24);
	cmdByteBuffer[8]  = (UINT8)((baseAddr2 & DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_LSB);
	cmdByteBuffer[9]  = (UINT8)(((baseAddr2 & DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_LSB) >>  8);
	cmdByteBuffer[10] = (UINT8)(((baseAddr2 & DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_LSB) >> 16);
	cmdByteBuffer[11] = (UINT8)(((baseAddr2 & DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_LSB) >> 24);
	cmdByteBuffer[12] = (UINT8)((baseAddr3 & DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_LSB);
	cmdByteBuffer[13] = (UINT8)(((baseAddr3 & DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_LSB) >>  8);
	cmdByteBuffer[14] = (UINT8)(((baseAddr3 & DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_LSB) >> 16);
	cmdByteBuffer[15] = (UINT8)(((baseAddr3 & DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_MASK) << DEMOD_DD_DVB_BASEADDR_AXI_CMD_BASEADDR_LSB) >> 24);

	err = DEMOD_L1_Process (core, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;

}
#endif /* DEMOD_DD_DVBT2_BASEADDR_AXI_CMD */

  /* --------------------------------------------*/
  /* SEND_COMMAND2 FUNCTION                      */
  /* --------------------------------------------*/
int DEMOD_L1_SendCommand2 (LX_DEMOD_L1_Context * core, UINT32 cmd_code)
{
	switch (cmd_code) {
#ifdef DEMOD_DD_SET_REG_CMD
		case DEMOD_DD_SET_REG_CMD_CODE:
			return DEMOD_L1_SET_DD_Reg (core, core->cmd->dd_set_reg.addressMsb, core->cmd->dd_set_reg.addressLsb, core->cmd->dd_set_reg.length, core->cmd->dd_set_reg.data);
#endif /* DEMOD_DD_SET_REG_CMD */

#ifdef DEMOD_DD_SET_PROP_CMD
		case DEMOD_DD_SET_PROP_CMD_CODE:
			return DEMOD_L1_SET_DD_Prop (core, core->cmd->set_property.prop,  core->cmd->set_property.data);
#endif /* DEMOD_DD_SET_PROP_CMD */

#ifdef DEMOD_DD_SET_REPEAT_CMD
		case DEMOD_DD_SET_REPEAT_CMD_CODE:
			return DEMOD_L1_SET_DD_Repeat (core->chip, core->cmd->dd_set_repeat.repeatEn);
#endif /* DEMOD_DD_SET_REPEAT_CMD */

#ifdef DEMOD_DD_SOFT_RESET_CMD
		case DEMOD_DD_SOFT_RESET_CMD_CODE:
			return DEMOD_L1_SET_DD_SoftRst (core,
					core->cmd->dd_soft_reset.softrstb,
					core->cmd->dd_soft_reset.softrstsyncb,
					core->cmd->dd_soft_reset.softrsteq1b,
					core->cmd->dd_soft_reset.softrsteq2b,
					core->cmd->dd_soft_reset.softrstdiseqcb,
					core->cmd->dd_soft_reset.softrstfecb,
					core->cmd->dd_soft_reset.softrsttpifb);
#endif /* DEMOD_DD_SOFT_RESET_CMD */

#ifdef DEMOD_DD_POWER_SAVE_CMD
		case DEMOD_DD_POWER_SAVE_CMD_CODE:
			return DEMOD_L1_SET_DD_Power_Save (core, core->cmd->power_save.power_save);
#endif /* DEMOD_DD_POWER_SAVE_CMD */

#ifdef DEMOD_DD_RESTART_CMD
		case DEMOD_DD_RESTART_CMD_CODE:
			return DEMOD_L1_SET_DD_Restart (core);
#endif /* DEMOD_DD_RESTART_CMD */

#ifdef DEMOD_DD_ATSC3_PLP_SELECT_CMD
		case DEMOD_DD_ATSC3_PLP_SELECT_CMD_CODE:
			return DEMOD_L1_SET_DD_ATSC3_PLP_Select (core, core->cmd->atsc3_plp_select.plp0_id, core->cmd->atsc3_plp_select.plp1_id, core->cmd->atsc3_plp_select.plp2_id, core->cmd->atsc3_plp_select.plp3_id);
#endif /* DEMOD_DD_ATSC3_PLP_SELECT_CMD */

#ifdef DEMOD_DD_SELFRST_CMD
		case DEMOD_DD_SELFRST_CMD_CODE:
			return DEMOD_L1_SET_DD_SelfRst (core,
					core->cmd->dd_selfrst.rst_arg, 
					core->cmd->dd_selfrst.rst_time1, 
					core->cmd->dd_selfrst.rst_time2, 
					core->cmd->dd_selfrst.rst_time3, 
					core->cmd->dd_selfrst.rst_time4, 
					core->cmd->dd_selfrst.rst_cnt, 
					core->cmd->dd_selfrst.plp0_thd, 
					core->cmd->dd_selfrst.plp1_thd, 
					core->cmd->dd_selfrst.plp2_thd, 
					core->cmd->dd_selfrst.plp3_thd);
		break;
#endif /* DEMOD_DD_SELFRST_CMD */

#ifdef DEMOD_DD_GET_REG_CMD
		case DEMOD_DD_GET_REG_CMD_CODE:
			return DEMOD_L1_GET_DD_Reg (core,  core->cmd->dd_get_reg.addressMsb, core->cmd->dd_get_reg.addressLsb, core->cmd->dd_get_reg.length);
#endif /* DEMOD_DD_GET_REG_CMD */

#ifdef DEMOD_DD_GET_PROP_CMD
		case DEMOD_DD_GET_PROP_CMD_CODE:
			return DEMOD_L1_GET_DD_Prop (core, core->cmd->get_property.prop );
#endif /* DEMOD_DD_GET_PROP_CMD */

#ifdef DEMOD_DD_STATUS_CMD
		case DEMOD_DD_STATUS_CMD_CODE:
			return DEMOD_L1_GET_DD_Status (core);
#endif /* DEMOD_DD_STATUS_CMD */

#ifdef DEMOD_DD_ATSC3_STATUS_CMD
		case DEMOD_DD_ATSC3_STATUS_CMD_CODE:
			return DEMOD_L1_GET_DD_ATSC3_Status (core);
#endif /* DEMOD_DD_ATSC3_STATUS_CMD */

#ifdef DEMOD_DD_ATSC3_PLP_ID_CMD
		case DEMOD_DD_ATSC3_PLP_ID_CMD_CODE:
			return DEMOD_L1_GET_DD_ATSC3_PLP_ID (core);
#endif /* DEMOD_DD_ATSC3_PLP_ID_CMD*/

#ifdef DEMOD_DD_ATSC3_PLP_INFO_CMD
		case DEMOD_DD_ATSC3_PLP_INFO_CMD_CODE:
			return DEMOD_L1_GET_DD_ATSC3_PLP_Info (core, core->cmd->atsc3_plp_info.plp_index);
#endif /* DEMOD_DD_ATSC3_PLP_INFO_CMD*/

#ifdef DEMOD_DD_VSB_STATUS_CMD
		case DEMOD_DD_VSB_STATUS_CMD_CODE:
			return DEMOD_L1_GET_DD_VSB_Status (core );
#endif /* DEMOD_DD_VSB_STATUS_CMD */

#ifdef DEMOD_DD_QAM_STATUS_CMD
		case DEMOD_DD_QAM_STATUS_CMD_CODE:
			return DEMOD_L1_GET_DD_QAM_Status (core);
#endif /* DEMOD_DD_QAM_STATUS_CMD */

#ifdef DEMOD_DD_GET_PART_INFO_CMD
		case DEMOD_DD_GET_PART_INFO_CMD_CODE:
			return DEMOD_L1_GET_DD_PartInfo (core );
#endif /* DEMOD_DD_GET_PART_INFO_CMD */

#ifdef DEMOD_DD_SET_TUNE_CMD
		case DEMOD_DD_SET_TUNE_CMD_CODE:
			return DEMOD_L1_SET_DD_Tune (core );
#endif /* DEMOD_DD_SET_TUNE_CMD */

#ifdef DEMOD_DD_LOCKTIME_CMD
		case DEMOD_DD_LOCKTIME_CMD_CODE:
			return DEMOD_L1_GET_DD_LOCKTIME(core );
#endif

#ifdef DEMOD_DD_ATSC3_SUBFRM_INFO_CMD
		 case DEMOD_DD_ATSC3_SUBFRM_INFO_CMD_CODE:
		   return DEMOD_L1_GET_DD_ATSC3_SUBFRM_Info (core);
#endif /*DEMOD_DD_ATSC3_SUBFRM_INFO_CMD*/
		
#ifdef DEMOD_DD_ISDBT_BASEADDR_AXI_CMD
		case DEMOD_DD_ISDBT_BASEADDR_AXI_CMD_CODE:
			return DEMOD_L1_SET_DD_ISDBT_BASEADDR_AXI (core, core->cmd->isdbt_baseaddr_axi.baseAddr);
#endif /* DEMOD_DD_ISDBT_BASEADDR_AXI_CMD */

#ifdef DEMOD_DD_DVBC_SRD_CMD
		case DEMOD_DD_DVBC_SRD_CMD_CODE:
			return DEMOD_L1_SET_DD_SymbolRate_Detect (core, core->cmd->dvbc_sym_rate.auto_en,  core->cmd->dvbc_sym_rate.sym_rate);
#endif /* DEMOD_DD_DVBC_SRD_CMD */

#ifdef DEMOD_DD_DVBT2_PLP_SELECT_CMD
		case DEMOD_DD_DVBT2_PLP_SELECT_CMD_CODE:
			return DEMOD_L1_SET_DD_DVBT2_PLP_Select (core, core->cmd->dvbt2_plp_select.plp_id, core->cmd->dvbt2_plp_select.plp_id_sel_mode);
#endif /* DEMOD_DD_DVBT2_PLP_SELECT_CMD */

#ifdef DEMOD_DD_GET_DVBT2_PLP_ID_CMD
		case DEMOD_DD_GET_DVBT2_PLP_ID_CMD_CODE:
			return DEMOD_L1_GET_DD_DVBT2_PLP_ID(core, core->cmd->dvbt2_plp_id.plp_index);
#endif /* DEMOD_DD_GET_DVBT2_PLP_ID_CMD */

#ifdef DEMOD_DD_DVBC2_STARTFREQUENCY_CMD
		case DEMOD_DD_DVBC2_STARTFREQUENCY_CMD_CODE:
			return DEMOD_L1_SET_DD_DVBC2_StartFrequency (core, core->cmd->dvbc2_start_frequency.freq);
#endif /* DEMOD_DD_DVBC2_STARTFREQUENCY_CMD */

#ifdef DEMOD_DD_DVBC2_PLP_SELECT_CMD
		case DEMOD_DD_DVBC2_PLP_SELECT_CMD_CODE:
			return DEMOD_L1_SET_DD_DVBC2_PLP_Select (core, core->cmd->dvbc2_plp_info.plp_id, core->cmd->dvbc2_plp_info.plp_id_mode, core->cmd->dvbc2_plp_info.ds_id );
#endif /* DEMOD_DD_DVBC2_PLP_SELECT_CMD */

#ifdef DEMOD_DD_DISEQC_SEND_CMD
		case DEMOD_DD_DISEQC_SEND_CMD_CODE:
			return DEMOD_L1_SET_DD_DISEQC_Send (core,
					core->cmd->dd_diseqc_send.diseqc_en,
					core->cmd->dd_diseqc_send.tone_burst,
					core->cmd->dd_diseqc_send.cont_tone,
					core->cmd->dd_diseqc_send.tone_burst,
					core->cmd->dd_diseqc_send.msg_length,
					core->cmd->dd_diseqc_send.send_framing,
					core->cmd->dd_diseqc_send.send_address,
					core->cmd->dd_diseqc_send.send_command,
					core->cmd->dd_diseqc_send.send_data0,
					core->cmd->dd_diseqc_send.send_data1,
					core->cmd->dd_diseqc_send.send_data2);
#endif /* DEMOD_DD_DISEQC_SEND_CMD */

#ifdef DEMOD_DD_DVBS_OPERATING_MODE_CMD
		case DEMOD_DD_DVBS_OPERATING_MODE_CMD_CODE:
			return DEMOD_L1_SET_DD_DVBS_Blind_Scan_Mode (core, core->cmd->operate_mode.opmSel, core->cmd->operate_mode.symbolRate, core->cmd->operate_mode.tuneFreq_Khz );
#endif /* DEMOD_DD_DVBS_OPERATING_MODE_CMD */

#ifdef DEMOD_DD_DVBT2_STATUS_CMD
		case DEMOD_DD_DVBT2_STATUS_CMD_CODE:
			return DEMOD_L1_GET_DD_DVBT2_Status (core);
#endif /* DEMOD_DD_DVBT2_STATUS_CMD */

#ifdef DEMOD_DD_DVBT_STATUS_CMD
		case DEMOD_DD_DVBT_STATUS_CMD_CODE:
			return DEMOD_L1_GET_DD_DVBT_Status (core);
#endif /* DEMOD_DD_DVBT_STATUS_CMD */

#ifdef DEMOD_DD_ISDBT_STATUS_CMD
		case DEMOD_DD_ISDBT_STATUS_CMD_CODE:
			return DEMOD_L1_GET_DD_ISDBT_Status (core);
#endif /* DEMOD_DD_ISDBT_STATUS_CMD */

#ifdef DEMOD_DD_ISDBT_TMCC_INFO_CMD
		case DEMOD_DD_ISDBT_TMCC_INFO_CMD_CODE:
			return DEMOD_L1_GET_DD_ISDBT_TMCC_Info (core);
#endif /* DEMOD_DD_ISDBT_STATUS_CMD */

#ifdef DEMOD_DD_DVBC_STATUS_CMD
		case DEMOD_DD_DVBC_STATUS_CMD_CODE:
			return DEMOD_L1_GET_DD_DVBC_Status (core);
#endif /* DEMOD_DD_DVBC_STATUS_CMD */

#ifdef DEMOD_DD_DVBC2_STATUS_CMD
		case DEMOD_DD_DVBC2_STATUS_CMD_CODE:
			return DEMOD_L1_GET_DD_DVBC2_Status (core);
#endif /* DEMOD_DD_DVBC2_STATUS_CMD */

#ifdef DEMOD_DD_DISEQC_STATUS_CMD
		case DEMOD_DD_DISEQC_STATUS_CMD_CODE:
			return DEMOD_L1_GET_DD_DISEQC_Status (core);
#endif /* DEMOD_DD_DISEQC_STATUS_CMD */

#ifdef DEMOD_DD_DVBS_STATUS_CMD
		case DEMOD_DD_DVBS_STATUS_CMD_CODE:
			return DEMOD_L1_GET_DD_DVBS_Status (core);
#endif /* DEMOD_DD_DVBS_STATUS_CMD */

#ifdef DEMOD_DD_DVBS2_STATUS_CMD
		case DEMOD_DD_DVBS2_STATUS_CMD_CODE:
			return DEMOD_L1_GET_DD_DVBS2_Status (core);
#endif /* DEMOD_DD_DVBS2_STATUS_CMD */

#ifdef DEMOD_DD_GET_DD_SIGSRCH_INFO_CMD
		case DEMOD_DD_GET_DD_SIGSRCH_INFO_CMD_CODE:
			return DEMOD_L1_GET_DD_SIGSRCH_INFO(core);
#endif /* DEMOD_DD_GET_DD_SIGSRCH_INFO_CMD */

#ifdef DEMOD_DD_BLIND_STATUS_CMD
		case DEMOD_DD_BLIND_STATUS_CMD_CODE:
			return DEMOD_L1_GET_DD_BLIND_Status(core);
#endif /* DEMOD_DD_BLIND_STATUS_CMD */

#ifdef DEMOD_DD_BLIND_INIT_CMD
		case DEMOD_DD_BLIND_INIT_CMD_CODE:
			return DEMOD_L1_GET_DD_BLIND_Init(core, core->cmd->blind_init.startFreq, core->cmd->blind_init.endFreq );
#endif /* DEMOD_DD_BLIND_INIT_CMD */

#ifdef DEMOD_DD_BLIND_FOUNDINFO_CMD
		case DEMOD_DD_BLIND_FOUNDINFO_CMD_CODE:
			return DEMOD_L1_GET_DD_BLIND_FoundInfo(core);
#endif /* DEMOD_DD_BLIND_FOUNDINFO_CMD */

#ifdef DEMOD_DD_DVBT2_BASEADDR_AXI_CMD
		case DEMOD_DD_DVBT2_BASEADDR_AXI_CMD_CODE:
			return DEMOD_L1_SET_DD_DVBT2_BASEADDR_AXI (core, core->cmd->dvbt2_baseaddr_axi.baseAddr1, core->cmd->dvbt2_baseaddr_axi.baseAddr2);
#endif /* DEMOD_DD_ISDBT_BASEADDR_AXI_CMD */

#ifdef DEMOD_DD_DTMB_STATUS_CMD
		case DEMOD_DD_DTMB_STATUS_CMD_CODE:
			return DEMOD_L1_GET_DD_DTMB_Status (core );
#endif /* DEMOD_DD_DTMB_STATUS_CMD */

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
int DEMOD_L1_CommandText (LX_DEMOD_L1_CmdReplyObj   *rsp, UINT32 cmd_code)
{
	switch (cmd_code) {
#ifdef DEMOD_DD_STATUS_CMD
		case DEMOD_DD_STATUS_CMD_CODE:
			switch(rsp->dd_status.reply_operMod) {
				case DEMOD_DD_MODE_PROP_MODULATION_VSB:
					DEMOD_DEBUG("[DEMOD_API][DD_STATUS] OP_MODE : VSB \n");
					break;
				case DEMOD_DD_MODE_PROP_MODULATION_QAM:
					DEMOD_DEBUG("[DEMOD_API][DD_STATUS] OP_MODE : QAM \n");
					break;
				case DEMOD_DD_MODE_PROP_MODULATION_ATSC3:
					DEMOD_DEBUG("[DEMOD_API][DD_STATUS] OP_MODE : ATSC3.0 \n");
					break;
				case DEMOD_DD_MODE_PROP_MODULATION_DVBT:
					DEMOD_DEBUG("[DEMOD_API][DD_STATUS] OP_MODE : DVBT \n");
					break;
				case DEMOD_DD_MODE_PROP_MODULATION_DVBT2:
					DEMOD_DEBUG("[DEMOD_API][DD_STATUS] OP_MODE : DVBT2 \n");
					break;
				case DEMOD_DD_MODE_PROP_MODULATION_DVBC:
					DEMOD_DEBUG("[DEMOD_API][DD_STATUS] OP_MODE : DVBC \n");
					break;
				case DEMOD_DD_MODE_PROP_MODULATION_DVBC2:
					DEMOD_DEBUG("[DEMOD_API][DD_STATUS] OP_MODE : DVBC2 \n");
					break;
				case DEMOD_DD_MODE_PROP_MODULATION_DVBS:
					DEMOD_DEBUG("[DEMOD_API][DD_STATUS] OP_MODE : DVBS \n");
					break;
				case DEMOD_DD_MODE_PROP_MODULATION_DVBS2:
					DEMOD_DEBUG("[DEMOD_API][DD_STATUS] OP_MODE : DVBS2 \n");
					break;
				case DEMOD_DD_MODE_PROP_MODULATION_DTMB:
					DEMOD_DEBUG("[DEMOD_API][DD_STATUS] OP_MODE : DTMB \n");
					break;
				default:
					DEMOD_DEBUG("[DEMOD_API][DD_STATUS] OP_MODE : Unknown \n");
					break;
			}

			if(rsp->dd_status.lock_fec == DEMOD_DD_STATUS_RESPONSE_LOCK_FEC_LOCKED)
				DEMOD_DEBUG("[DEMOD_API][DD_STATUS] FEC_LOCK : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_STATUS] FEC_LOCK : UNLOCKED \n") ;

			if(rsp->dd_status.neverLock == DEMOD_DD_STATUS_RESPONSE_NEVERLOCK_LOCKED)
				DEMOD_DEBUG("[DEMOD_API][DD_STATUS] NEVER_LOCK : LOCKED \n");
			else if(rsp->dd_status.neverLock == DEMOD_DD_STATUS_RESPONSE_NEVERLOCK_PROCESSING)
				DEMOD_DEBUG("[DEMOD_API][DD_STATUS] NEVER_LOCK : PROCESSING \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_STATUS] NEVER_LOCK : UNLOCKED \n") ;
			break;
#endif

#ifdef DEMOD_DD_ATSC3_STATUS_CMD
		case DEMOD_DD_ATSC3_STATUS_CMD_CODE:
			DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] IF_AGC : %d \n", rsp->atsc3_status.if_agc);
			DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] CTF_PWR : %d \n", rsp->atsc3_status.ctf_pwr);
			DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] NUM_PLP : %d \n", rsp->atsc3_plp_info.num_plp_total);
			DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] MSE_INFO : %d \n", rsp->atsc3_status.mse_info);
			DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] BER : %d \n", rsp->atsc3_status.ber);
			DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] CFO_VALUE : 0x%x \n", rsp->atsc3_status.cfo);
			DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] SFO_VALUE : 0x%x \n", rsp->atsc3_status.sfo);
			DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] PACKET_ERROR : %d \n", rsp->atsc3_status.pe);

			if(rsp->atsc3_status.spInv == DEMOD_DD_ATSC3_STATUS_RESPONSE_SPECINV_NORMAL)
				DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] SPECINV : NORMAL  \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] SPECINV : INVERTED \n") ;


			if(rsp->atsc3_status.lock_fec == DEMOD_DD_ATSC3_STATUS_RESPONSE_LOCK_FEC_LOCKED)
				DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] FEC_LOCK : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] FEC_LOCK : UNLOCKED \n") ;

			if(rsp->atsc3_status.lock_carr == DEMOD_DD_ATSC3_STATUS_RESPONSE_LOCK_CARR_LOCKED)
				DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] CARR_LOCK : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] CARR_LOCK : UNLOCKED \n") ;

			if(rsp->atsc3_status.done_bs == DEMOD_DD_ATSC3_STATUS_RESPONSE_DONE_BS_DEC_DONE)
				DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] BS_DONE : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] BS_DONE : UNLOCKED \n") ;

			if(rsp->atsc3_status.done_acq == DEMOD_DD_ATSC3_STATUS_RESPONSE_DONE_ACQ_DONE)
				DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] ACQ_DONE : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] ACQ_DONE : UNLOCKED \n") ;

			if(rsp->atsc3_status.en_fsto_track == DEMOD_DD_ATSC3_STATUS_RESPONSE_EN_FSTO_TRACK_ENABLE)
				DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] FSTO_TRACK_EN : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] FSTO_TRACK_EN : UNLOCKED \n") ;

			if(rsp->atsc3_status.lock_l1b == DEMOD_DD_ATSC3_STATUS_RESPONSE_LOCK_L1B_LOCKED)
				DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] L1B_LOCK : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] L1B_LOCK : UNLOCKED \n") ;

			if(rsp->atsc3_status.lock_l1d == DEMOD_DD_ATSC3_STATUS_RESPONSE_LOCK_L1D_LOCKED)
				DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] L1D_LOCK : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] L1D_LOCK : UNLOCKED \n") ;

			DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] SFO_VALUE : %d \n", rsp->atsc3_status.sfo);
			DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] MSE_INFO_DEMOD : %d \n", rsp->atsc3_status.mse_info_demod);
			DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] LDPC_ERROR : %d \n", rsp->atsc3_status.ldpc_err);

			switch(rsp->atsc3_status.fft_mode) {
				case DEMOD_DD_ATSC3_STATUS_RESPONSE_FFT_MODE_8K:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] FFT_MODE : 8K \n");
					break;

				case DEMOD_DD_ATSC3_STATUS_RESPONSE_FFT_MODE_16K:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] FFT_MODE : 16K \n");
					break;

				case DEMOD_DD_ATSC3_STATUS_RESPONSE_FFT_MODE_32K:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] FFT_MODE : 32K \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] FFT_MODE : Reserved \n");
					break;
			}

			switch(rsp->atsc3_status.gi) {
				case DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_1_192:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] GI : 1 / 192 \n");
					break;

				case DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_2_384:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] GI : 2 / 384 \n");
					break;

				case DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_3_512:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] GI : 3 / 512 \n");
					break;

				case DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_4_768:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] GI : 4 / 768 \n");
					break;

				case DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_5_1024:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] GI : 5 / 1024 \n");
					break;

				case DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_6_1536:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] GI : 6 / 1536 \n");
					break;

				case DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_7_2048:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] GI : 7 / 2048 \n");
					break;

				case DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_8_2432:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] GI : 8 / 2432 \n");
					break;

				case DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_9_3072:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] GI : 9 / 3072 \n");
					break;

				case DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_10_368:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] GI : 10 / 368 \n");
					break;

				case DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_11_4096:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] GI : 11 / 4096 \n");
					break;

				case DEMOD_DD_ATSC3_STATUS_RESPONSE_GI_12_4864:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] GI : 12 / 4864 \n");
					break;

				default:
					break;
			}

			switch(rsp->atsc3_status.bandwidth) {
				case DEMOD_DD_ATSC3_STATUS_RESPONSE_BANDWIDTH_6MHZ:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] BANDWHIDTH : 6MHZ \n");
					break;

				case DEMOD_DD_ATSC3_STATUS_RESPONSE_BANDWIDTH_7MHZ:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] BANDWHIDTH : 7MHZ \n");
					break;

				case DEMOD_DD_ATSC3_STATUS_RESPONSE_BANDWIDTH_8MHZ:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] BANDWHIDTH : 8MHZ \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] BANDWHIDTH : GREATER THAN 8MHZ \n");
					break;
			}

			DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_STATUS] NUM_PLP : %d \n", rsp->atsc3_status.num_plp);
			break;
#endif

#ifdef DEMOD_DD_VSB_STATUS_CMD
		case DEMOD_DD_VSB_STATUS_CMD_CODE:
			DEMOD_DEBUG("[DEMOD_API][DD_VSB_STATUS] IF_AGC : %d \n", rsp->vsb_status.if_agc);
			DEMOD_DEBUG("[DEMOD_API][DD_VSB_STATUS] MSE_INFO : %d \n", rsp->vsb_status.mse_info);
			DEMOD_DEBUG("[DEMOD_API][DD_VSB_STATUS] BER : %d \n", rsp->vsb_status.ber);
			DEMOD_DEBUG("[DEMOD_API][DD_VSB_STATUS] CFO_VALUE : 0x%x \n", rsp->vsb_status.cfo);
			DEMOD_DEBUG("[DEMOD_API][DD_VSB_STATUS] SFO_VALUE : 0x%x \n", rsp->vsb_status.sfo);
			DEMOD_DEBUG("[DEMOD_API][DD_VSB_STATUS] PACKET_ERROR : %d \n", rsp->vsb_status.pe);

			if(rsp->vsb_status.spInv == DEMOD_DD_VSB_STATUS_RESPONSE_SPECINV_NORMAL)
				DEMOD_DEBUG("[DEMOD_API][DD_VSB_STATUS] SPECINV : NORMAL  \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_VSB_STATUS] SPECINV : INVERTED \n") ;

			if(rsp->vsb_status.lock_fec == DEMOD_DD_VSB_STATUS_RESPONSE_LOCK_FEC_LOCKED)
				DEMOD_DEBUG("[DEMOD_API][DD_VSB_STATUS] FEC_LOCK : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_VSB_STATUS] FEC_LOCK : UNLOCKED \n") ;

			if(rsp->vsb_status.lock_carr == DEMOD_DD_VSB_STATUS_RESPONSE_LOCK_CARR_LOCKED)
				DEMOD_DEBUG("[DEMOD_API][DD_VSB_STATUS] CARR_LOCK : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_VSB_STATUS] CARR_LOCK : UNLOCKED \n") ;
			break;
#endif

#ifdef DEMOD_DD_QAM_STATUS_CMD
		case DEMOD_DD_QAM_STATUS_CMD_CODE:
			DEMOD_DEBUG("[DEMOD_API][DD_QAM_STATUS] IF_AGC : %d \n", rsp->qam_status.if_agc);
			DEMOD_DEBUG("[DEMOD_API][DD_QAM_STATUS] MSE_INFO : %d \n", rsp->qam_status.mse_info);
			DEMOD_DEBUG("[DEMOD_API][DD_QAM_STATUS] BER : %d \n", rsp->qam_status.ber);
			DEMOD_DEBUG("[DEMOD_API][DD_QAM_STATUS] CFO_VALUE : 0x%x \n", rsp->qam_status.cfo);
			DEMOD_DEBUG("[DEMOD_API][DD_QAM_STATUS] SFO_VALUE : 0x%x \n", rsp->qam_status.sfo);
			DEMOD_DEBUG("[DEMOD_API][DD_QAM_STATUS] PACKET_ERROR : %d \n", rsp->qam_status.pe);
			DEMOD_DEBUG("[DEMOD_API][DD_QAM_STATUS] SYMBOL_RATE : %d KHz \n", rsp->qam_status.sym_rate);

			if(rsp->qam_status.constellation== DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64)
				DEMOD_DEBUG("[DEMOD_API][DD_QAM_STATUS] CONSTELLATION : 64QAM  \n");
			else if(rsp->qam_status.constellation== DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM256)
				DEMOD_DEBUG("[DEMOD_API][DD_QAM_STATUS] CONSTELLATION : 256QAM  \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_QAM_STATUS] SPECINV : UNKNOWN \n") ;

			if(rsp->qam_status.spInv == DEMOD_DD_QAM_STATUS_RESPONSE_SPECINV_NORMAL)
				DEMOD_DEBUG("[DEMOD_API][DD_QAM_STATUS] SPECINV : NORMAL  \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_QAM_STATUS] SPECINV : INVERTED \n") ;

			if(rsp->qam_status.lock_fec == DEMOD_DD_QAM_STATUS_RESPONSE_LOCK_FEC_LOCKED)
				DEMOD_DEBUG("[DEMOD_API][DD_QAM_STATUS] FEC_LOCK : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_QAM_STATUS] FEC_LOCK : UNLOCKED \n") ;

			if(rsp->qam_status.lock_carr == DEMOD_DD_QAM_STATUS_RESPONSE_LOCK_CARR_LOCKED)
				DEMOD_DEBUG("[DEMOD_API][DD_QAM_STATUS] CARR_LOCK : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_QAM_STATUS] CARR_LOCK : UNLOCKED \n") ;
			break;
#endif

#ifdef DEMOD_DD_DVBC_STATUS_CMD
		case DEMOD_DD_DVBC_STATUS_CMD_CODE:
			DEMOD_DEBUG("[DEMOD_API][DD_DVBC_STATUS] IF_AGC : %d \n", rsp->dvbc_status.if_agc);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBC_STATUS] MSE_INFO : %d \n", 	rsp->dvbc_status.mse_info);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBC_STATUS] BER : %d \n", rsp->dvbc_status.ber);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBC_STATUS] CFO_VALUE : 0x%x \n", rsp->dvbc_status.cfo);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBC_STATUS] SFO_VALUE : 0x%x \n", rsp->dvbc_status.sfo);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBC_STATUS] PACKET_ERROR : %d \n", rsp->dvbc_status.pe);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBC_STATUS] SYMBOL_RATE : %d KHz \n", rsp->dvbc_status.sym_rate);

			switch(rsp->dvbc_status.constellation) {
				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16 :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBC_STATUS] CONSTELLATION : 16QAM  \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM32  :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBC_STATUS] CONSTELLATION : 32QAM  \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64  :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBC_STATUS] CONSTELLATION : 64QAM  \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM128  :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBC_STATUS] CONSTELLATION : 128QAM  \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM256  :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBC_STATUS] CONSTELLATION : 256QAM  \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBC_STATUS] CONSTELLATION : UNKNOWN  \n");
					break;
			}

			if(rsp->dvbc_status.spInv == DEMOD_DD_DVBC_STATUS_RESPONSE_SPECINV_NORMAL)
				DEMOD_DEBUG("[DEMOD_API][DD_DVBC_STATUS] SPECINV : NORMAL  \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_DVBC_STATUS] SPECINV : INVERTED \n") ;

			if(rsp->dvbc_status.lock_fec == DEMOD_DD_DVBC_STATUS_RESPONSE_LOCK_FEC_LOCKED)
				DEMOD_DEBUG("[DEMOD_API][DD_DVBC_STATUS] FEC_LOCK : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_DVBC_STATUS] FEC_LOCK : UNLOCKED \n") ;

			if(rsp->dvbc_status.lock_carr == DEMOD_DD_DVBC_STATUS_RESPONSE_LOCK_CARR_LOCKED)
				DEMOD_DEBUG("[DEMOD_API][DD_DVBC_STATUS] CARR_LOCK : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_DVBC_STATUS] CARR_LOCK : UNLOCKED \n") ;
			break;
#endif

#ifdef DEMOD_DD_GET_PART_INFO_CMD
		case DEMOD_DD_GET_PART_INFO_CMD_CODE:
			DEMOD_DEBUG("[DEMOD_API][DD_PART_INFO] FW_VERSION : %d.%d.0 \n",rsp->part_info.fw_major, rsp->part_info.fw_minor);
			DEMOD_DEBUG("[DEMOD_API][DD_PART_INFO] FW_DATE : %d/%d/%d \n",rsp->part_info.fw_year, rsp->part_info.fw_month, rsp->part_info.fw_day);
			DEMOD_DEBUG("[DEMOD_API][DD_PART_INFO] FW_CHIP_REV : %d\n", rsp->part_info.chip_rev);
			break;
#endif

#ifdef DEMOD_DD_ATSC3_PLP_INFO_CMD
		case DEMOD_DD_ATSC3_PLP_INFO_CMD_CODE:
			DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] BS_PRE_STRUCTURE : %d \n", 				rsp->atsc3_plp_info.bs_pre_str);
			DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] BS_L1B_MOD : %d \n", 					rsp->atsc3_plp_info.bs_l1b_mode);
			DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1B_NUM_SUBFRAMES : %d \n", 			rsp->atsc3_plp_info.l1b_num_subframes);
			DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1B_PRE_NUM_SYMBOLS : %d \n", 			rsp->atsc3_plp_info.l1b_pre_num_symbols);
			DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1B_FIRST_NUM_OFDM_SYMBOLS : %d \n", 	rsp->atsc3_plp_info.l1b_num_ofdm_symbols);
			DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1D_NUM_PLP : %d \n", 					rsp->atsc3_plp_info.um_plp);
			DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1D_PLP_HTI_NUM_TI_BLOCKS : %d \n",	 	rsp->atsc3_plp_info.l1d_plp_hti_num_ti_blocks);
			DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1D_PLP_HTI_NUM_FEC_BLOCKS : %d \n", 	rsp->atsc3_plp_info.l1d_plp_hti_num_fec_blocks);
			DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1D_PLP_HTI_NUM_FEC_BLOCKS_MAX : %d \n", rsp->atsc3_plp_info.l1d_plp_hti_num_fec_blocks_max);
			DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1B_FIRST_REDUCE_CARR : %d \n", 		rsp->atsc3_plp_info.l1b_reduce_carr);
			DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1B_FIRST_SUB_SCATT_PB : %d \n", 		rsp->atsc3_plp_info.l1b_sub_scatt_pb);
			DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1D_PLP_CTI_START_ROW : %d \n", 		rsp->atsc3_plp_info.l1d_plp_cti_start_row);
			DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1D_PLP_HTI_INTER_SUBFRAMES : %d \n", 	rsp->atsc3_plp_info.l1d_plp_hti_inter_subframe);

			switch(rsp->atsc3_plp_info.l1b_sub_fft_size) {
				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_FFT_SIZE_8K:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] FFT_MODE : 8K \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_FFT_SIZE_16K:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] FFT_MODE : 16K \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_FFT_SIZE_32K:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] FFT_MODE : 32K \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] FFT_MODE : Reserved \n");
					break;
			}

			switch(rsp->atsc3_plp_info.l1b_sub_gi) {
				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_GI_1_192:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] GI : 1 / 192 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_GI_2_384:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] GI : 2 / 384 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_GI_3_512:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] GI : 3 / 512 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_GI_4_768:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] GI : 4 / 768 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_GI_5_1024:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] GI : 5 / 1024 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_GI_6_1536:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] GI : 6 / 1536 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_GI_7_2048:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] GI : 7 / 2048 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_GI_8_2432:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] GI : 8 / 2432 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_GI_9_3072:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] GI : 9 / 3072 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_GI_10_3648:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] GI : 10 / 368 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_GI_11_4096:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] GI : 11 / 4096 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_GI_12_4864:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] GI : 12 / 4864 \n");
					break;

				default:
					break;
			}

			switch(rsp->atsc3_plp_info.l1b_sub_scatt_pp) {
				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SCATT_PP_3_2:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PP : 3_2 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SCATT_PP_3_4:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PP : 3_4 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SCATT_PP_4_2:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PP : 4_2 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SCATT_PP_4_4:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PP : 4_4 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SCATT_PP_6_2:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PP : 6_2 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SCATT_PP_6_4:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PP : 6_4 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SCATT_PP_8_2:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PP : 8_2 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SCATT_PP_8_4:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PP : 8_4 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SCATT_PP_12_2:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PP : 12_2 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SCATT_PP_12_4:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PP : 12_4 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SCATT_PP_16_2:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PP : 16_2 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SCATT_PP_16_4:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PP : 16_4 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SCATT_PP_24_2:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PP : 24_2 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SCATT_PP_24_4:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] GI : 24_4 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SCATT_PP_32_2:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] GI : 32_2 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SCATT_PP_32_4:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] GI : 32_4 \n");
					break;

				default:
					break;
			}

			if(rsp->atsc3_plp_info.l1b_sub_sbs_first == DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SBS_FIRST_SBS)
				DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1B_SUB_SBS_FIRST SBS : SBS \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1B_SUB_SBS_FIRST SBS : NO_SBS \n") ;

			if(rsp->atsc3_plp_info.l1b_sub_sbs_last == DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1B_SUB_SBS_LAST_SBS)
				DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1B_SUB_SBS_LAST SBS : SBS \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1B_SUB_SBS_LAST SBS : NO_SBS \n") ;

			switch(rsp->atsc3_plp_info.plp_ti_mode) {
				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_TI_MODE_NO_TI_MODE:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_TI_MODE : NO_TI_MODE \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_TI_MODE_CTI_MODE:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_TI_MODE : CTI_MODE \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_TI_MODE_HTI_MODE:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_TI_MODE : HTI_MODE \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_TI_MODE : Reserved \n");
					break;
			}

			switch(rsp->atsc3_plp_info.plp_fec_type) {
				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_FEC_TYPE_BCH_16K_LDPC:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_FEC_TYPE : BCH_16K_LDPC \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_FEC_TYPE_BCH_64K_LDPC:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_FEC_TYPE : BCH_64K_LDPC \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_FEC_TYPE_CRC_16K_LDPC:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_FEC_TYPE : CRC_16K_LDPC \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_FEC_TYPE_CRC_64K_LDPC:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_FEC_TYPE : CRC_64K_LDPC \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_FEC_TYPE_16K_LDPC:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_FEC_TYPE : 16K_LDPC \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_FEC_TYPE_64K_LDPC:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_FEC_TYPE : 64K_LDPC \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_FEC_TYPE : Reserved \n");
					break;
			}

			switch(rsp->atsc3_plp_info.plp_mod) {
				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_QPSK:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_MOD : QPSK \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_16QAM_NUC:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_MOD : 16QAM_NUC \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_64QAM_NUC:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_MOD : 64QAM_NUC \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_256QAM_NUC:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_MOD : 256QAM_NUC \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_1024QAM_NUC:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_MOD : 1024QAM_NUC \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_MOD_4096QAM_NUC:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_MOD : 4096QAM_NUC \n");
					break;

				default:
					break;
			}

			switch(rsp->atsc3_plp_info.plp_cr) {
				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_2_15:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_CR : 2_15 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_3_15:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_CR : 3_15 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_4_15:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_CR : 4_15 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_5_15:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_CR : 5_15 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_6_15:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_CR : 6_15 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_7_15:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_CR : 7_15 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_8_15:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_CR : 8_15 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_9_15:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_CR : 9_15 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_10_15:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_CR : 10_15 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_11_15:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_CR : 11_15 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_12_15:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_CR : 12_15 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_PLP_CR_13_15:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] PLP_CR : 13_15 \n");
					break;

				default:
					break;
			}

			switch(rsp->atsc3_plp_info.l1d_plp_cti_depth) {
				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CTI_DEPTH_512:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1D_PLP_CTI_DEPTH : 512 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CTI_DEPTH_724:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1D_PLP_CTI_DEPTH : 724 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CTI_DEPTH_887_1254:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1D_PLP_CTI_DEPTH : 887_1254 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_PLP_CTI_DEPTH_1024_1448:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1D_PLP_CTI_DEPTH : 1024_1448 \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1D_PLP_CTI_DEPTH : Reserved \n");
					break;
			}

			if(rsp->atsc3_plp_info.l1d_mimo == DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_MIMO_USED)
				DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1D_MIMO : USED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1D_MIMO : UNUSED \n") ;


			switch(rsp->atsc3_plp_info.l1d_miso) {
				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_MISO_NOMISO:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1D_MISO : NOMISO \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_MISO_MISO64:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1D_MISO : MISO64 \n");
					break;

				case DEMOD_DD_ATSC3_PLP_INFO_RESPONSE_L1D_MISO_MISO256:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1D_MISO : MISO256 \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_ATSC3_PLP_INFO] L1D_MISO : Reserved \n");
					break;
			}
			break;
#endif

#ifdef DEMOD_DD_ISDBT_STATUS_CMD
		case DEMOD_DD_ISDBT_STATUS_CMD_CODE:
			DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_STATUS] IF_AGC : %d \n", rsp->isdbt_status.if_agc);
			DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_STATUS] MSE_INFO : %d \n", rsp->isdbt_status.mse_info);
			DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_STATUS] BER : %d \n", rsp->isdbt_status.ber);
			DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_STATUS] CFO_VALUE : 0x%x \n", rsp->isdbt_status.cfo);
			DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_STATUS] SFO_VALUE : 0x%x \n", rsp->isdbt_status.sfo);
			DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_STATUS] PACKET_ERROR : %d \n", rsp->isdbt_status.pe);

			if(rsp->isdbt_status.spInv == DEMOD_DD_ISDBT_STATUS_RESPONSE_SPECINV_NORMAL)
				DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_STATUS] SPECINV : NORMAL  \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_STATUS] SPECINV : INVERTED \n") ;

			if(rsp->isdbt_status.lock_fec == DEMOD_DD_ISDBT_STATUS_RESPONSE_LOCK_FEC_LOCKED)
				DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_STATUS] FEC_LOCK : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_STATUS] FEC_LOCK : UNLOCKED \n") ;

			if(rsp->isdbt_status.lock_carr == DEMOD_DD_ISDBT_STATUS_RESPONSE_LOCK_CARR_LOCKED)
				DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_STATUS] CARR_LOCK : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_STATUS] CARR_LOCK : UNLOCKED \n") ;
			break;
#endif

#ifdef DEMOD_DD_ISDBT_TMCC_INFO_CMD
		case DEMOD_DD_ISDBT_TMCC_INFO_CMD_CODE:
			switch(rsp->isdbt_tmcc_info.gi) {
				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_1_32:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] GI : 1_32 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_1_16:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] GI : 1_16 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_1_8:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] GI : 1_8 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_1_4:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] GI : 1_4 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_1_128:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] GI : 1_128 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_19_128:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] GI : 19_128 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_19_256:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] GI : 19_256 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_1_64:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] GI : 1_64 \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] GI : Reserved \n");
					break;
			}

			switch(rsp->isdbt_tmcc_info.fft_mode) {
				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_FFT_MODE_2K:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] FFT_MODE : 2K \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_FFT_MODE_8K:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] FFT_MODE : 8K \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_FFT_MODE_4K:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] FFT_MODE : 4K \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_FFT_MODE_1K:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] FFT_MODE : 1K \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_FFT_MODE_16K:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] FFT_MODE : 16K \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_FFT_MODE_32K:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] FFT_MODE : 32K \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_FFT_MODE_512K:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] FFT_MODE : 512K \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_FFT_MODE_256K:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] FFT_MODE : 256K \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] FFT_MODE : Reserved \n");
					break;
			}

			switch(rsp->isdbt_tmcc_info.oqama) {
				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QPSK:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO]  Layer A Constellation : QPSK \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_DQPSK   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Constellation : DQPSK \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Constellation : QAM16 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM32  :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Constellation : QAM32 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Constellation : QAM64 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM128  :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Constellation : QAM128 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM256  :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Constellation : QAM256 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM1024  :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Constellation : QAM1024 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM4096    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Constellation : QAM4096 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_PSK8    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Constellation : PSK8 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_VSB8    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Constellation : VSB8 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM4    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Constellation : QAM4 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_APSK16      :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Constellation : APSK16 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_APSK32      :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Constellation : APSK32 \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Constellation : Reserved \n");
					break;

			}

			switch(rsp->isdbt_tmcc_info.ocra) {
				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_1_2 :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Code rate : 1_2 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_2_3  :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Code rate : 2_3 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_3_4  :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Code rate : 3_4 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_5_6  :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Code rate : 5_6 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_7_8  :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Code rate : 7_8 \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Code rate : Reserved \n");
					break;
			}

			switch(rsp->isdbt_tmcc_info.onsega) {
				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_1   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Segment : 1 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_2    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Segment : 2 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_3    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Segment : 3 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_4    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Segment : 4 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_5   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Segment : 5 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_6    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Segment : 6 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_7    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Segment : 7 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_8    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Segment : 8 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_9    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Segment : 9 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_10   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Segment : 10 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_11   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Segment : 11 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_12   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Segment : 12 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_13   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Segment : 13 \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Segment : Reserved \n");
					break;
			}

			switch(rsp->isdbt_tmcc_info.oila) {

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_0_0_0	:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Interleaving : 0_0_0 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_4_2_1    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Interleaving : 4_2_1 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_8_4_2    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Interleaving : 8_4_2 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_16_8_4    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Interleaving : 16_8_4 \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer A Interleaving : Reserved \n");
					break;
			}

			switch(rsp->isdbt_tmcc_info.oqamb) {
				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QPSK:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO]  Layer B Constellation : QPSK \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_DQPSK   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Constellation : DQPSK \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Constellation : QAM16 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM32  :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Constellation : QAM32 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Constellation : QAM64 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM128  :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Constellation : QAM128 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM256  :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Constellation : QAM256 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM1024  :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Constellation : QAM1024 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM4096    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Constellation : QAM4096 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_PSK8    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Constellation : PSK8 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_VSB8    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Constellation : VSB8 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM4    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Constellation : QAM4 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_APSK16      :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Constellation : APSK16 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_APSK32      :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Constellation : APSK32 \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Constellation : Reserved \n");
					break;
			}

			switch(rsp->isdbt_tmcc_info.ocrb) {
				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_1_2 :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Code rate : 1_2 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_2_3  :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Code rate : 2_3 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_3_4  :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Code rate : 3_4 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_5_6  :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Code rate : 5_6 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_7_8  :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Code rate : 7_8 \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Code rate : Reserved \n");
					break;
			}

			switch(rsp->isdbt_tmcc_info.onsegb) {
				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_1   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Segment : 1 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_2    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Segment : 2 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_3    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Segment : 3 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_4    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Segment : 4 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_5   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Segment : 5 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_6    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Segment : 6 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_7    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Segment : 7 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_8    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Segment : 8 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_9    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Segment : 9 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_10   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Segment : 10 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_11   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Segment : 11 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_12   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Segment : 12 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_13   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Segment : 13 \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Segment : Reserved \n");
					break;
			}

			switch(rsp->isdbt_tmcc_info.oilb) {
				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_0_0_0	:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Interleaving : 0_0_0 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_4_2_1    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Interleaving : 4_2_1 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_8_4_2    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Interleaving : 8_4_2 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_16_8_4    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Interleaving : 16_8_4 \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer B Interleaving : Reserved \n");
					break;
			}

			switch(rsp->isdbt_tmcc_info.oqamc) {
				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QPSK:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO]  Layer C Constellation : QPSK \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_DQPSK   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Constellation : DQPSK \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Constellation : QAM16 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM32  :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Constellation : QAM32 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Constellation : QAM64 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM128  :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Constellation : QAM128 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM256  :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Constellation : QAM256 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM1024  :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Constellation : QAM1024 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM4096    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Constellation : QAM4096 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_PSK8    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Constellation : PSK8 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_VSB8    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Constellation : VSB8 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM4    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Constellation : QAM4 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_APSK16      :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Constellation : APSK16 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_APSK32      :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Constellation : APSK32 \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Constellation : Reserved \n");
					break;
			}

			switch(rsp->isdbt_tmcc_info.ocrc) {
				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_1_2 :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Code rate : 1_2 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_2_3  :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Code rate : 2_3 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_3_4  :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Code rate : 3_4 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_5_6  :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Code rate : 5_6 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_CR_7_8  :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Code rate : 7_8 \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Code rate : Reserved \n");
					break;
			}

			switch(rsp->isdbt_tmcc_info.onsegc) {
				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_1   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Segment : 1 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_2    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Segment : 2 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_3    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Segment : 3 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_4    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Segment : 4 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_5   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Segment : 5 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_6    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Segment : 6 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_7    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Segment : 7 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_8    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Segment : 8 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_9    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Segment : 9 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_10   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Segment : 10 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_11   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Segment : 11 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_12   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Segment : 12 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_SEG_13   :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Segment : 13 \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Segment : Reserved \n");
					break;
			}

			switch(rsp->isdbt_tmcc_info.oilc) {
				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_0_0_0	:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Interleaving : 0_0_0 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_4_2_1    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Interleaving : 4_2_1 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_8_4_2    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Interleaving : 8_4_2 \n");
					break;

				case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_16_8_4    :
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Interleaving : 16_8_4 \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_ISDBT_TMCC_INFO] Layer C Interleaving : Reserved \n");
					break;
			}
			break;
#endif

#ifdef DEMOD_DD_DVBS_STATUS_CMD
		case DEMOD_DD_DVBS_STATUS_CMD_CODE:
			DEMOD_DEBUG("[DEMOD_API][DD_DVBS_STATUS] IF_AGC : %d \n", rsp->dvbs_status.if_agc);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBS_STATUS] MSE_INFO : %d \n", rsp->dvbs_status.mse_info);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBS_STATUS] BER : %d \n", rsp->dvbs_status.ber);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBS_STATUS] CFO_VALUE : 0x%x \n", rsp->dvbs_status.cfo);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBS_STATUS] SFO_VALUE : 0x%x \n", rsp->dvbs_status.sfo);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBS_STATUS] PACKET_ERROR : %d \n", rsp->dvbs_status.pe);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBS_STATUS] SYMBOL_RATE : %d KHz \n", rsp->dvbs_status.sym_rate);

			if(rsp->dvbs_status.constellation== DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QPSK)
				DEMOD_DEBUG("[DEMOD_API][DD_DVBS_STATUS] CONSTELLATION : QPSK  \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_DVBS_STATUS] SPECINV : UNKNOWN \n") ;

			if(rsp->dvbs_status.spInv == DEMOD_DD_DVBS_STATUS_RESPONSE_SPECINV_NORMAL)
				DEMOD_DEBUG("[DEMOD_API][DD_DVBS_STATUS] SPECINV : NORMAL  \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_DVBS_STATUS] SPECINV : INVERTED \n") ;

			switch(rsp->dvbs_status.cr) {
				case DEMOD_DD_STATUS_RESPONSE_CODERATE_1_2 :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBS_STATUS] Code rate : 1_2 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CODERATE_2_3  :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBS_STATUS] Code rate : 2_3 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CODERATE_3_4  :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBS_STATUS] Code rate : 3_4 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CODERATE_5_6  :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBS_STATUS] Code rate : 5_6 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CODERATE_7_8  :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBS_STATUS] Code rate : 7_8 \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBS_STATUS] Code rate : Reserved \n");
					break;
			}

			if(rsp->dvbs_status.lock_fec == DEMOD_DD_DVBS2_STATUS_RESPONSE_LOCK_FEC_LOCKED)
				DEMOD_DEBUG("[DEMOD_API][DD_DVBS_STATUS] FEC_LOCK : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_DVBS_STATUS] FEC_LOCK : UNLOCKED \n") ;

			if(rsp->dvbs_status.lock_carr == DEMOD_DD_DVBS2_STATUS_RESPONSE_LOCK_CARR_LOCKED)
				DEMOD_DEBUG("[DEMOD_API][DD_DVBS_STATUS] CARR_LOCK : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_DVBS_STATUS] CARR_LOCK : UNLOCKED \n") ;
			break;
#endif

#ifdef DEMOD_DD_DVBS2_STATUS_CMD
		case DEMOD_DD_DVBS2_STATUS_CMD_CODE:
			DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] IF_AGC : %d \n", rsp->dvbs2_status.if_agc);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] MSE_INFO : %d \n", rsp->dvbs2_status.mse_info);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] BER : %d \n", rsp->dvbs2_status.ber);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] CFO_VALUE : 0x%x \n", rsp->dvbs2_status.cfo);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] SFO_VALUE : 0x%x \n", rsp->dvbs2_status.sfo);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] PACKET_ERROR : %d \n", rsp->dvbs2_status.pe);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] SYMBOL_RATE : %d KHz \n", rsp->dvbs2_status.sym_rate);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] PILOT_PATTERN : %d \n", rsp->dvbs2_status.pp);

			switch(rsp->dvbs2_status.constellation) {
				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QPSK :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] CONSTELLATION : QPSK  \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_PSK8  :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] CONSTELLATION : PSK  \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_APSK16  :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] CONSTELLATION : 16APSK  \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_APSK32  :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] CONSTELLATION : 32APSK  \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] CONSTELLATION : UNKNOWN  \n");
					break;
			}

			if(rsp->dvbs2_status.spInv == DEMOD_DD_DVBS2_STATUS_RESPONSE_SPECINV_NORMAL)
				DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] SPECINV : NORMAL  \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] SPECINV : INVERTED \n") ;

			switch(rsp->dvbs2_status.cr) {
				case DEMOD_DD_STATUS_RESPONSE_CODERATE_1_4 :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] Code rate : 1_4 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CODERATE_1_3  :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] Code rate : 1_3 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CODERATE_2_5  :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] Code rate : 2_5 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CODERATE_1_2  :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] Code rate : 1_2 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CODERATE_3_5  :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] Code rate : 3_5 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CODERATE_2_3 :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] Code rate : 2_3 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CODERATE_3_4  :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] Code rate : 3_4 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CODERATE_4_5  :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] Code rate : 4_5 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CODERATE_5_6  :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] Code rate : 5_6 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CODERATE_8_9  :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] Code rate : 8_9 \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CODERATE_9_10  :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] Code rate : 9_10 \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] Code rate : Reserved \n");
					break;
			}

			if(rsp->dvbs2_status.lock_fec == DEMOD_DD_DVBS2_STATUS_RESPONSE_LOCK_FEC_LOCKED)
				DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] FEC_LOCK : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] FEC_LOCK : UNLOCKED \n") ;

			if(rsp->dvbs2_status.lock_carr == DEMOD_DD_DVBS2_STATUS_RESPONSE_LOCK_CARR_LOCKED)
				DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] CARR_LOCK : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_DVBS2_STATUS] CARR_LOCK : UNLOCKED \n") ;
			break;
#endif

#ifdef DEMOD_DD_DVBT_STATUS_CMD
		case DEMOD_DD_DVBT_STATUS_CMD_CODE:
			DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] IF_AGC : %d \n", rsp->dvbt_status.if_agc);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] MSE_INFO : %d \n", rsp->dvbt_status.mse_info);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] BER : %d \n", rsp->dvbt_status.ber);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] CFO_VALUE : 0x%x \n", rsp->dvbt_status.cfo);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] SFO_VALUE : 0x%x \n", rsp->dvbt_status.sfo);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] PACKET_ERROR : %d \n", rsp->dvbt_status.pe);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] CELL_ID : %d \n", rsp->dvbt_status.cell_id);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] HIERARCHY : %d \n", rsp->dvbt_status.hierarchy);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] HIERARCHY_SEL : %d \n", rsp->dvbt_status.hierarchy_sel);

			if(rsp->dvbt_status.hierarchy_sel == DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_SEL_HP) {
				switch(rsp->dvbt_status.hp_cr) {
					case DEMOD_DD_DVBT_STATUS_RESPONSE_HP_CR_HP_1_2	:
						DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] HP_CR = 1_2 \n");
						break;

					case DEMOD_DD_DVBT_STATUS_RESPONSE_HP_CR_HP_2_3	:
						DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] HP_CR = 2_3 \n");
						break;

					case DEMOD_DD_DVBT_STATUS_RESPONSE_HP_CR_HP_3_4	:
						DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] HP_CR = 3_4 \n");
						break;

					case DEMOD_DD_DVBT_STATUS_RESPONSE_HP_CR_HP_5_6	:
						DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] HP_CR = 5_6 \n");
						break;

					case DEMOD_DD_DVBT_STATUS_RESPONSE_HP_CR_HP_7_8	:
						DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] HP_CR = 7_8 \n");
						break;

					default:
						DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] HP_CR = = UNKNOWN \n");
						break;
				}
			} else {
				switch(rsp->dvbt_status.lp_cr) {
					case DEMOD_DD_DVBT_STATUS_RESPONSE_LP_CR_1_2	:
						DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] LP_CR = 1_2 \n");
						break;

					case DEMOD_DD_DVBT_STATUS_RESPONSE_LP_CR_2_3	:
						DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] LP_CR = 2_3 \n");
						break;

					case DEMOD_DD_DVBT_STATUS_RESPONSE_LP_CR_3_4	:
						DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] LP_CR = 3_4 \n");
						break;

					case DEMOD_DD_DVBT_STATUS_RESPONSE_LP_CR_5_6	:
						DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] LP_CR = 5_6 \n");
						break;

					case DEMOD_DD_DVBT_STATUS_RESPONSE_LP_CR_7_8	:
						DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] LP_CR = 7_8 \n");
						break;

					default:
						DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] LP_CR = UNKNOWN \n");
						break;
				}
			}

			switch(rsp->dvbt_status.constellation) {
				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QPSK	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] CONSTELLATION = QPSK \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] CONSTELLATION = 16QAM \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] CONSTELLATION = 64QAM \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] CONSTELLATION = UNKNOWN \n");
					break;
			}

			switch(rsp->dvbt_status.gi) {
				case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_32	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] GUARD INTERVAL = 1/32 \n");
					break;

				case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_16	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] GUARD INTERVAL = 1/16 \n");
					break;

				case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_8	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] GUARD INTERVAL = 1/8 \n");
					break;

				case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_4	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] GUARD INTERVAL = 1/4 \n");
					break;

				case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_128	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] GUARD INTERVAL = 1/128 \n");
					break;

				case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_19_128	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] GUARD INTERVAL = 19/128 \n");
					break;

				case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_19_256	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] GUARD INTERVAL = 19/256 \n");
					break;

				case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_64	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] GUARD INTERVAL = 1/64 \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] GUARD INTERVAL = UNKNOWN \n");
					break;
			}

			switch(rsp->dvbt_status.fft_mode) {
				case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_2K	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] FFT_MODE = 2K \n");
					break;

				case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_8K	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] FFT_MODE = 8K \n");
					break;

				case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_4K	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] FFT_MODE = 4K \n");
					break;

				case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_1K	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] FFT_MODE = 1K \n");
					break;

				case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_16K	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] FFT_MODE = 16K \n");
					break;

				case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_32K	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] FFT_MODE = 32K \n");
					break;

				case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_512K	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] FFT_MODE = 512 \n");
					break;

				case DEMOD_DD_DVBT_STATUS_RESPONSE_FFT_MODE_256K	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] FFT_MODE = 256 \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] FFT_MODE = UNKNOWN \n");
					break;
			}

			if(rsp->dvbt_status.spInv == DEMOD_DD_DVBT_STATUS_RESPONSE_SPECINV_NORMAL)
				DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] SPECINV : NORMAL  \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] SPECINV : INVERTED \n") ;

			if(rsp->dvbt_status.lock_fec == DEMOD_DD_DVBT_STATUS_RESPONSE_LOCK_FEC_LOCKED)
				DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] FEC_LOCK : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] FEC_LOCK : UNLOCKED \n") ;

			if(rsp->dvbt_status.lock_carr == DEMOD_DD_DVBT_STATUS_RESPONSE_LOCK_CARR_LOCKED)
				DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] CARR_LOCK : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_DVBT_STATUS] CARR_LOCK : UNLOCKED \n") ;
			break;
#endif

#ifdef 	DEMOD_DD_DVBT2_STATUS_CMD
		case DEMOD_DD_DVBT2_STATUS_CMD_CODE:
			DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] IF_AGC : %d \n", rsp->dvbt2_status.if_agc);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] MSE_INFO : %d \n", rsp->dvbt2_status.mse_info);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] BER : %d \n", rsp->dvbt2_status.ber);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] CFO_VALUE : 0x%x \n", rsp->dvbt2_status.cfo);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] SFO_VALUE : 0x%x \n", rsp->dvbt2_status.sfo);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] PACKET_ERROR : %d \n", rsp->dvbt2_status.pe);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] NUM_PLP : %d \n", rsp->dvbt2_status.num_plp);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] NUM_DPLP : %d \n", rsp->dvbt2_status.num_dplp);
			DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] BW_EXT : %d \n", rsp->dvbt2_status.bw_ext);

			switch(rsp->dvbt2_status.cr) {

				case DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_1_2	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] CR = 1_2 \n");
					break;

				case DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_3_5	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] CR = 3_5 \n");
					break;

				case DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_2_3	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] CR = 2_3 \n");
					break;

				case DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_3_4	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] CR = 3_4 \n");
					break;

				case DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_4_5	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] CR = 4_5 \n");
					break;

				case DEMOD_DD_DVBT2_STATUS_RESPONSE_CR_5_6	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] CR = 5_6 \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] CR = UNKNOWN \n");
					break;
			}

			switch(rsp->dvbt2_status.constellation) {
				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QPSK	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] CONSTELLATION = QPSK \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM16	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] CONSTELLATION = 16QAM \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM64	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] CONSTELLATION = 64QAM \n");
					break;

				case DEMOD_DD_STATUS_RESPONSE_CONSTELLATION_QAM256	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] CONSTELLATION = 256QAM \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] CONSTELLATION = UNKNOWN \n");
					break;
			}

			switch(rsp->dvbt2_status.gi) {
				case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_32	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] GUARD INTERVAL = 1/32 \n");
					break;

				case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_16	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] GUARD INTERVAL = 1/16 \n");
					break;

				case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_8	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] GUARD INTERVAL = 1/8 \n");
					break;

				case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_4	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] GUARD INTERVAL = 1/4 \n");
					break;

				case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_128	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] GUARD INTERVAL = 1/128 \n");
					break;

				case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_19_128	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] GUARD INTERVAL = 19/128 \n");
					break;

				case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_19_256	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] GUARD INTERVAL = 19/256 \n");
					break;

				case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_64	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] GUARD INTERVAL = 1/64 \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] GUARD INTERVAL = UNKNOWN \n");
					break;
			}

			switch(rsp->dvbt2_status.fft_mode) {
				case DEMOD_DD_DVBT2_STATUS_RESPONSE_FFT_MODE_2K	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] FFT_MODE = 2K \n");
					break;

				case DEMOD_DD_DVBT2_STATUS_RESPONSE_FFT_MODE_8K	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] FFT_MODE =  8K \n");
					break;

				case DEMOD_DD_DVBT2_STATUS_RESPONSE_FFT_MODE_4K	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] FFT_MODE =  4K \n");
					break;

				case DEMOD_DD_DVBT2_STATUS_RESPONSE_FFT_MODE_1K	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] FFT_MODE =  1K \n");
					break;

				case DEMOD_DD_DVBT2_STATUS_RESPONSE_FFT_MODE_16K	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] FFT_MODE =  16K \n");
					break;

				case DEMOD_DD_DVBT2_STATUS_RESPONSE_FFT_MODE_32K	:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] FFT_MODE =  32K \n");
					break;

				case DEMOD_DD_DVBT2_STATUS_RESPONSE_FFT_MODE_512 :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] FFT_MODE =  512 \n");
					break;

				case DEMOD_DD_DVBT2_STATUS_RESPONSE_FFT_MODE_256 :
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] FFT_MODE =  256 \n");
					break;

				default:
					DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] FFT_MODE =  UNKNOWN \n");
					break;
			}

			if(rsp->dvbt2_status.spInv == DEMOD_DD_DVBT2_STATUS_RESPONSE_SPECINV_NORMAL)
				DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] SPECINV : NORMAL \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] SPECINV : INVERTED \n") ;

			if(rsp->dvbt2_status.lock_fec == DEMOD_DD_DVBT2_STATUS_RESPONSE_LOCK_FEC_LOCKED)
				DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] FEC_LOCK : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] FEC_LOCK : UNLOCKED \n") ;

			if(rsp->dvbt2_status.lock_carr == DEMOD_DD_DVBT2_STATUS_RESPONSE_LOCK_CARR_LOCKED)
				DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] CARR_LOCK : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_DVBT2_STATUS] CARR_LOCK : UNLOCKED \n") ;
			break;
#endif

#ifdef DEMOD_DD_DTMB_STATUS_CMD
		case DEMOD_DD_DTMB_STATUS_CMD_CODE:
			DEMOD_DEBUG("[DEMOD_API][DD_DTMB_STATUS] IF_AGC : %d \n",	rsp->dtmb_status.if_agc);
			DEMOD_DEBUG("[DEMOD_API][DD_DTMB_STATUS] MSE_INFO : %d \n", rsp->dtmb_status.mse_info);
			DEMOD_DEBUG("[DEMOD_API][DD_DTMB_STATUS] BER : %d \n", rsp->dtmb_status.ber);
			DEMOD_DEBUG("[DEMOD_API][DD_DTMB_STATUS] CFO_VALUE : 0x%x \n", rsp->dtmb_status.cfo);
			DEMOD_DEBUG("[DEMOD_API][DD_DTMB_STATUS] SFO_VALUE : 0x%x \n", rsp->dtmb_status.sfo);
			DEMOD_DEBUG("[DEMOD_API][DD_DTMB_STATUS] PACKET_ERROR : %d \n", rsp->dtmb_status.pe);

			if(rsp->dtmb_status.spInv == DEMOD_DD_DTMB_STATUS_RESPONSE_SPECINV_NORMAL)
				DEMOD_DEBUG("[DEMOD_API][DD_DTMB_STATUS] SPECINV : NORMAL \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_DTMB_STATUS] SPECINV : INVERTED \n") ;

			if(rsp->dtmb_status.lock_fec == DEMOD_DD_DTMB_STATUS_RESPONSE_LOCK_FEC_LOCKED)
				DEMOD_DEBUG("[DEMOD_API][DD_DTMB_STATUS] FEC_LOCK : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_DTMB_STATUS] FEC_LOCK : UNLOCKED \n") ;

			if(rsp->dtmb_status.lock_carr == DEMOD_DD_DTMB_STATUS_RESPONSE_LOCK_CARR_LOCKED)
				DEMOD_DEBUG("[DEMOD_API][DD_DTMB_STATUS] CARR_LOCK : LOCKED \n");
			else
				DEMOD_DEBUG("[DEMOD_API][DD_DTMB_STATUS] CARR_LOCK : UNLOCKED \n") ;
			break;

		default:
			break;
#endif
	}

	return NO_DEMOD_ERROR;
}


