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

static UINT8	dummyBuffer[COMMAND_BSIZ] = {0,};
static UINT8 	rspByteBuffer[PAYLOAD_BMAX] = {0,};
static char		dbgBuffer[4096] = {0,};

#if defined(DEMOD_USE_DEBUG_CHECK_POINT)
char check_point[4][4096];
#endif

int DEMOD_L1_Process_Dump(LX_DEMOD_L1_Context * core, char * dbglog) {
	int dbgidx = 0;

	return dbgidx;
}

#if defined(PLATFORM_FPGA)
#define SEND_TIME_WARNING	100
#define RECV_TIME_WARNING	100
#define WAIT_TIME_WARNING	100
#define SPEND_TIME_WARNING	2000
#define SPEND_TIME_LIMIT	6000
#else
#if ((DEMOD_COMM == DEMOD_COMM_APB) && !defined(DEMOD_CONFIG_POLL))
#define SEND_TIME_WARNING	30
#define RECV_TIME_WARNING	30
#define WAIT_TIME_WARNING	30
#define SPEND_TIME_WARNING	1000
#define SPEND_TIME_LIMIT	3000
#else
#define SEND_TIME_WARNING	100
#define RECV_TIME_WARNING	100
#define WAIT_TIME_WARNING	100
#define SPEND_TIME_WARNING	1000
#define SPEND_TIME_LIMIT	3000
#endif
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
	UINT32 send_count;

	int state = CBUF_STATE_UNKNOWN;
	int err = NO_DEMOD_ERROR;
	int retry = 5;

	start_clock = DEMOD_L0_SystemClock();

	DEMOD_DEBUG("send req start, cmd x%02X(%u), %d, %s\n", cmd, core->cmd_req_cnt, len, DEMOD_BYTE_TO_HEXSTR((char *)preq, len));
	do {
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
				core->cmd_req_cnt++;
				DEMOD_NOTI("resend, x%02X(%u), retry %d, tx state %d, tooks %3u.%03ums\n", cmd, core->cmd_req_cnt & 0xFF, retry, state, spend_ms, spend_us);
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
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
		do {
			DEMOD_L0_system_wait(1);
			send_count = DEMOD_L1_IPC_Send_Count(core);
			spend_clock = DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us);
		} while ((send_count > 0)  && (spend_ms < SPEND_TIME_LIMIT));
#else
		DEMOD_L0_system_wait(10);
#endif
		break;
#endif
	} while (1);

	spend_clock = DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us);

#if defined(DEMOD_SPEND_TIME_CHECK)
	_cmd_req_ms = spend_ms;
	_cmd_req_us = spend_us;
#endif

	if (err < 0) {
		DEMOD_ERROR("send fail, x%02X(%u), retry %d, tx state %d, tooks %3u.%03ums, len %d, err 0x%02X, %s\n", cmd, core->cmd_req_cnt & 0xFF, retry, state, spend_ms, spend_us, len, -err, DEMOD_L1_API_Error_Text(err));
	} else {
		core->cmd_req_val_cnt++;

		if (spend_ms > SEND_TIME_WARNING) {
			DEMOD_WARN("send req tooks %u.%03u, cmd x%02X(%u), len %u\n", spend_ms, spend_us, cmd, core->cmd_req_cnt, len);
		}
	}

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
		DEMOD_WARN("recv res, err with 0x%02X, %s, tooks %3u.%03u\n", -err, DEMOD_L1_API_Error_Text(err), spend_ms, spend_us);
	} else {
		if (spend_ms > RECV_TIME_WARNING) {
			DEMOD_WARN("recv res tooks %u.%03u\n", spend_ms, spend_us);
		}
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

	if (err != NO_DEMOD_ERROR) {
		DEMOD_WARN("recv res done, tooks %3u.%03ums, recv(%d) x%02X(%u), wait x%02X(%u), err 0x%02x, %s\n", spend_ms, spend_us, *plen, cmd, seq, wait_cmd, wait_seq, -err, DEMOD_L1_API_Error_Text(err));
	} else {
		if (spend_ms > WAIT_TIME_WARNING)
		{
			DEMOD_WARN("wait & recv res tooks %u.%03u\n", spend_ms, spend_us);
		}
	}

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

static int _DEMOD_L1_Process (LX_DEMOD_L1_Context * core, UINT8 command, UINT8 req_len, void * req_buf, UINT8 rsp_len, void * rsp_buf)
{
	UINT64 start_clock;
	UINT64 spend_clock;
	UINT32 spend_us;
	UINT32 spend_ms;
	
	int err = 0;
	int rcv_len = 0;
	
	if (core->fw_state != DEMOD_FW_STATE_RUN) {
		DEMOD_WARN("fw is not ready\n");
		return -ERROR_DEMOD_FW_NOT_READY;
	}

	core->cmd_req_cnt++;

	DEMOD_DEBUG("command start, cmd x%02x(%u), req len %d, rsp len %d\n", command, core->cmd_req_cnt, req_len, rsp_len);

	start_clock = DEMOD_L0_SystemClock();

	/* send request command */
#if defined(DEMOD_USE_DEBUG_CHECK_POINT)
	DEMOD_L1_API_Debug(core, check_point[0]);
	DEMOD_L0_CBUF_Status(&core->ipc->tx, check_point[1]);
#endif

	err = _DEMOD_L1_CommandRequest(core, command, (UINT8 *)req_buf, req_len);
	if (err != NO_DEMOD_ERROR) {
		DEMOD_ERROR("failed to CommandRequest x%02X(%u) with err 0x%02X\n", command, core->cmd_req_cnt, -err);
		DEMOD_L1_API_Debug(core, dbgBuffer);
		DEMOD_ERROR("%s\n", dbgBuffer);
#if defined(DEMOD_USE_DEBUG_CHECK_POINT)
		DEMOD_L1_API_Debug(core, check_point[2]);
		DEMOD_L0_CBUF_Status(&core->ipc->tx, check_point[3]);

		DEMOD_DEBUG("[0] %s\n", check_point[0]);
		DEMOD_DEBUG("[1] %s\n", check_point[1]);
		DEMOD_DEBUG("[2] %s\n", check_point[2]);
		DEMOD_DEBUG("[3] %s\n", check_point[3]);
#endif
		return err;
	}

	spend_clock = DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us);
	if (spend_ms > SPEND_TIME_WARNING)
		DEMOD_WARN("command send tooks %u.%03u, cmd x%02X(%u)\n", spend_ms, spend_us, command, core->cmd_req_cnt);

#if defined(DEMOD_USE_DEBUG_CHECK_POINT)
	DEMOD_L1_API_Debug(core, check_point[0]);
	DEMOD_L1_IPC_Status_Fifo(core, check_point[1]);
#endif

	/* wait & recv response */
	err = _DEMOD_L1_WaitResponse(core, command, (UINT8 *)rsp_buf, &rcv_len);
	if(err != NO_DEMOD_ERROR) {
		DEMOD_ERROR("failed to WaitResponse x%02X(%u) with err 0x%02X\n", command, core->cmd_req_cnt, -err);
		//DEMOD_ERROR("REQ: %s\n", reqLog);
		//DEMOD_ERROR("RES: %s\n", resLog);
		DEMOD_L1_API_Debug(core, dbgBuffer);
		DEMOD_ERROR("%s\n", dbgBuffer);
#if defined(DEMOD_USE_DEBUG_CHECK_POINT)
		DEMOD_L1_API_Debug(core, check_point[2]);
		DEMOD_L1_IPC_Status_Fifo(core, check_point[3]);

		DEMOD_DEBUG("[0] %s\n", check_point[0]);
		DEMOD_DEBUG("[1] %s\n", check_point[1]);
		DEMOD_DEBUG("[2] %s\n", check_point[2]);
		DEMOD_DEBUG("[3] %s\n", check_point[3]);
#endif
		return err;
	}

	if (rsp_len > rcv_len) {
		DEMOD_WARN("x%02x(%u): not enough rcv len %d, need %d for command(0x%02X)\n", command, core->cmd_req_cnt, rcv_len, rsp_len, command);
		//return -ERROR_DEMOD_IPC_INVALID;
	}

	spend_clock = DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us);

#if defined(DEMOD_SPEND_TIME_CHECK)
	DEMOD_INFO("command tooks %u.%03u, cmd x%02X(%u), send %3u.%03u, recv %3u.%03u\n", spend_ms, spend_us, command, core->cmd_req_cnt, _cmd_req_ms, _cmd_req_us, _cmd_res_ms, _cmd_res_us);
#else
	if (spend_ms > SPEND_TIME_WARNING)
		DEMOD_WARN("command tooks %u.%03u, cmd x%02X(%u)\n", spend_ms, spend_us, command, core->cmd_req_cnt);
#endif
	
	return  err;
}

#ifdef	DEMOD_CMD_SET_REG
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
	cmdByteBuffer[0] = (UINT8)DEMOD_CMD_SET_REG_CODE;
	cmdByteBuffer[1] = ((addressMsb & DEMOD_CMD_SET_REG_ADDRMSB_MASK) << DEMOD_CMD_SET_REG_ADDRMSB_LSB);
	cmdByteBuffer[2] = ((addressLsb & DEMOD_CMD_SET_REG_ADDRLSB_MASK) << DEMOD_CMD_SET_REG_ADDRLSB_LSB);
	cmdByteBuffer[3] = ((length & DEMOD_CMD_SET_REG_LENGTH_MASK) << DEMOD_CMD_SET_REG_LENGTH_LSB);

	for (i = 0; i < length; i++)
	{
		cmdByteBuffer[4+i] = (UINT8)((data >> (i * 8)) & 0xff) ;
	}

	err = _DEMOD_L1_Process (core, DEMOD_CMD_SET_REG_CODE, cmdByte , cmdByteBuffer, rspByte, rspByteBuffer);

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
	cmdByteBuffer[0] = DEMOD_CMD_SET_REG_CODE;
	cmdByteBuffer[1] = ( ( addressMsb & DEMOD_CMD_SET_REG_ADDRMSB_MASK ) << DEMOD_CMD_SET_REG_ADDRMSB_LSB);
	cmdByteBuffer[2] = ( ( addressLsb & DEMOD_CMD_SET_REG_ADDRLSB_MASK ) << DEMOD_CMD_SET_REG_ADDRLSB_LSB);
	cmdByteBuffer[3] = ( ( length & DEMOD_CMD_SET_REG_LENGTH_MASK ) << DEMOD_CMD_SET_REG_LENGTH_LSB);

	for (i = 0; i < length; i++)
	{
		//cmdByteBuffer[4+i] = (UINT8)((data >> (i * 8)) & 0xff) ;
		cmdByteBuffer[4+i] = *(wrData+i);
	}

	err = _DEMOD_L1_Process (core, DEMOD_CMD_SET_REG_CODE, cmdByte , cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /*DEMOD_CMD_SET_REG */


#ifdef DEMOD_CMD_SET_PROP
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
	cmdByteBuffer[0] = (UINT8)DEMOD_CMD_SET_PROP_CODE;
	cmdByteBuffer[1] = (UINT8)(((prop & DEMOD_CMD_SET_PROP_PROP_MASK) << DEMOD_CMD_SET_PROP_PROP_LSB) >>  8);
	cmdByteBuffer[2] = (UINT8)(((prop & DEMOD_CMD_SET_PROP_PROP_MASK) << DEMOD_CMD_SET_PROP_PROP_LSB) >>  0);
	cmdByteBuffer[3] = (UINT8)0;
	cmdByteBuffer[4] = (UINT8)(((data & DEMOD_CMD_SET_PROP_DATA_MASK) << DEMOD_CMD_SET_PROP_DATA_LSB) >>  0);
	cmdByteBuffer[5] = (UINT8)(((data & DEMOD_CMD_SET_PROP_DATA_MASK) << DEMOD_CMD_SET_PROP_DATA_LSB) >>  8);
	cmdByteBuffer[6] = (UINT8)(((data & DEMOD_CMD_SET_PROP_DATA_MASK) << DEMOD_CMD_SET_PROP_DATA_LSB) >> 16);
	cmdByteBuffer[7] = (UINT8)(((data & DEMOD_CMD_SET_PROP_DATA_MASK) << DEMOD_CMD_SET_PROP_DATA_LSB) >> 24);

	err = _DEMOD_L1_Process (core, DEMOD_CMD_SET_PROP_CODE, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_CMD_SET_PROP */


#ifdef DEMOD_CMD_SET_REPEAT
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

	memset(&repeatI2c, 0, sizeof(repeatI2c));
	repeatI2c.i2c_slv_addr	= 0xE0;
	repeatI2c.i2c_idx_size	= 2;

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
#endif /* DEMOD_CMD_SET_REPEAT */


#ifdef DEMOD_CMD_SOFT_RESET
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
	cmdByteBuffer[0] = (UINT8)DEMOD_CMD_SOFT_RESET_CODE;
   	cmdByteBuffer[1] = (UINT8)((softrstb 		& DEMOD_CMD_SOFT_RESET_SOFTRSTB_MASK) 	<< DEMOD_CMD_SOFT_RESET_SOFTRSTB_LSB 	|
			            (softrstsyncb 	& DEMOD_CMD_SOFT_RESET_SOFTRSTSYNCB_MASK)	<< DEMOD_CMD_SOFT_RESET_SOFTRSTSYNCB_LSB 	|
			            (softrsteq1b 	& DEMOD_CMD_SOFT_RESET_SOFTRSTEQ1B_MASK)	<< DEMOD_CMD_SOFT_RESET_SOFTRSTEQ1B_LSB 	|
			            (softrsteq2b 	& DEMOD_CMD_SOFT_RESET_SOFTRSTEQ2B_MASK)	<< DEMOD_CMD_SOFT_RESET_SOFTRSTEQ2B_LSB 	|
			            (softrstdiseqcb 	& DEMOD_CMD_SOFT_RESET_SOFTRSTDISEQCB_MASK)	<< DEMOD_CMD_SOFT_RESET_SOFTRSTDISEQCB_LSB 	|
			            (softrstfecb 	& DEMOD_CMD_SOFT_RESET_SOFTRSTFECB_MASK)	<< DEMOD_CMD_SOFT_RESET_SOFTRSTFECB_LSB 	|
			            (softrsttpifb 	& DEMOD_CMD_SOFT_RESET_SOFTRSTTPIFB_MASK)	<< DEMOD_CMD_SOFT_RESET_SOFTRSTTPIFB_LSB);

	err = _DEMOD_L1_Process (core, DEMOD_CMD_SOFT_RESET_CODE, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_CMD_SOFT_RESET */


#ifdef DEMOD_CMD_POWER_SAVE
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
	cmdByteBuffer[0] = (UINT8)DEMOD_CMD_POWER_SAVE_CODE;
	cmdByteBuffer[1] = (UINT8)power_save;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_POWER_SAVE_CODE, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_CMD_POWER_SAVE */


#ifdef DEMOD_CMD_RESTART
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
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_RESTART_CODE, 0, NULL, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_CMD_RESTART */


#ifdef DEMOD_CMD_GET_REG
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
	cmdByteBuffer[0] = (UINT8)DEMOD_CMD_GET_REG_CODE;
	cmdByteBuffer[1] = ((addressMsb	& DEMOD_CMD_GET_REG_ADDRMSB_MASK) 	<< DEMOD_CMD_GET_REG_ADDRMSB_LSB);
	cmdByteBuffer[2] = ((addressLsb	& DEMOD_CMD_GET_REG_ADDRLSB_MASK) 	<< DEMOD_CMD_GET_REG_ADDRLSB_LSB);
	cmdByteBuffer[3] = ((length	& DEMOD_CMD_GET_REG_LENGTH_MASK) 	<< DEMOD_CMD_GET_REG_LENGTH_LSB);

	rspByte = length;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_GET_REG_CODE, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

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
	cmdByteBuffer[0] = (UINT8)DEMOD_CMD_GET_REG_CODE;

	for (i = 0; (err == NO_DEMOD_ERROR) && (i < length); i += PAYLOAD_BMAX) {
		addressMsb = (address + i) >> 8;
		addressLsb = (address + i) & 0xFF;

		cur_length = length - i;

		if (cur_length > PAYLOAD_BMAX) {
			cur_length = PAYLOAD_BMAX;
		}

		cmdByteBuffer[1] = ((addressMsb	& DEMOD_CMD_GET_REG_ADDRMSB_MASK) 	<< DEMOD_CMD_GET_REG_ADDRMSB_LSB);
		cmdByteBuffer[2] = ((addressLsb	& DEMOD_CMD_GET_REG_ADDRLSB_MASK) 	<< DEMOD_CMD_GET_REG_ADDRLSB_LSB);
		cmdByteBuffer[3] = ((cur_length	& DEMOD_CMD_GET_REG_LENGTH_MASK) 	<< DEMOD_CMD_GET_REG_LENGTH_LSB);
		rspByte = cur_length;

		err = _DEMOD_L1_Process (core, DEMOD_CMD_GET_REG_CODE, cmdByte, cmdByteBuffer, rspByte, &rspByteBuffer[i]);
	}

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_CMD_GET_REG */

#ifdef DEMOD_CMD_GET_PROP
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
	cmdByteBuffer[0] = (UINT8)DEMOD_CMD_GET_PROP_CODE;
	cmdByteBuffer[1] = (UINT8)(((prop	& DEMOD_CMD_GET_PROP_PROP_MASK) 	<< DEMOD_CMD_GET_PROP_PROP_LSB) >> 8);
	cmdByteBuffer[2] = (UINT8)(((prop	& DEMOD_CMD_GET_PROP_PROP_MASK)	<< DEMOD_CMD_GET_PROP_PROP_LSB) >> 0);

	err = _DEMOD_L1_Process (core, DEMOD_CMD_GET_PROP_CODE, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);
	core->rsp->get_property.data =  (((rspByteBuffer[3] <<24 | rspByteBuffer[2] <<16 | rspByteBuffer[1] <<8 | (rspByteBuffer[0])) >> DEMOD_CMD_GET_PROP_PROP_LSB) & DEMOD_CMD_GET_PROP_PROP_MASK);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_CMD_GET_PROP */


#ifdef DEMOD_CMD_VSB_STATUS
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
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	rspByte = 17;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_VSB_STATUS_CODE, 0, NULL, rspByte, rspByteBuffer);

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

#endif /* DEMOD_CMD_VSB_STATUS */


#ifdef DEMOD_CMD_QAM_STATUS
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
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	rspByte = 19;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_QAM_STATUS_CODE, 0, NULL, rspByte, rspByteBuffer);

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

#endif /* DEMOD_CMD_QAM_STATUS */


#ifdef DEMOD_CMD_GET_PART_INFO
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
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	rspByte = 7;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_GET_PART_INFO_CODE, 0, NULL, rspByte, rspByteBuffer);

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
#endif /* DEMOD_CMD_GET_PART_INFO */


#ifdef DEMOD_CMD_SET_TUNE
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
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_SET_TUNE_CODE, 0, NULL, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_CMD_SET_TUNE */


#ifdef DEMOD_CMD_STATUS
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
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	rspByte=2;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_STATUS_CODE, 0, NULL, rspByte, rspByteBuffer);

	core->rsp->dd_status.reply_operMod	= ((rspByteBuffer[0]  >> DEMOD_DD_STATUS_RESPONSE_MODULATION_LSB) & DEMOD_DD_STATUS_RESPONSE_MODULATION_MASK);
	core->rsp->dd_status.lock_fec		= ((rspByteBuffer[1]  >> DEMOD_DD_STATUS_RESPONSE_LOCK_FEC_LSB) & DEMOD_DD_STATUS_RESPONSE_LOCK_FEC_MASK);
	core->rsp->dd_status.neverLock		= ((rspByteBuffer[1]  >> DEMOD_DD_STATUS_RESPONSE_NEVERLOCK_LSB) & DEMOD_DD_STATUS_RESPONSE_NEVERLOCK_MASK);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_CMD_STATUS */



#ifdef DEMOD_CMD_TSCLK_STATUS
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
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	rspByte=4;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_TSCLK_STATUS_CODE, 0, NULL, rspByte, rspByteBuffer);

	core->rsp->dd_tsclk_status.tsClkRate	= ((((rspByteBuffer[3]) | (rspByteBuffer[2] << 8) | (rspByteBuffer[1] << 16) | (rspByteBuffer[0] << 24)) >> DEMOD_DD_TSCLK_STATUS_RESPONSE_TSCLKRATE_LSB) & DEMOD_DD_TSCLK_STATUS_RESPONSE_TSCLKRATE_MASK);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_CMD_STATUS */



#ifdef DEMOD_CMD_ATSC3_PLP_SELECT
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
	int err = NO_DEMOD_ERROR;
	int i;

	UINT8 plp_ids[4] = {plp0_id, plp1_id, plp2_id, plp3_id};

	DEMOD_REQ_ATSC3_PLP_SELECT_struct plpselect_req;
	DEMOD_RES_ATSC3_PLP_SELECT_struct plpselect_res;

	memset(&plpselect_req, 0, sizeof(plpselect_req));
	memset(&plpselect_res, 0, sizeof(plpselect_res));

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	for (i = 0; i < 4; i++) {
		plpselect_req.plp_dec_idx[i].dec_active_low = (plp_ids[i] & 0x80) ? 1 : 0;
		plpselect_req.plp_dec_idx[i].id = plp_ids[i] & 0x3F;
	}

	err = _DEMOD_L1_Process (core, DEMOD_CMD_ATSC3_PLP_SELECT_CODE, sizeof(plpselect_req), &plpselect_req, sizeof(plpselect_res), rspByteBuffer);
	if (NO_DEMOD_ERROR == err) {
		memcpy(&plpselect_res, rspByteBuffer, sizeof(plpselect_res));

		if (plpselect_res.retc == NO_DEMOD_ERROR) {
			core->rsp->atsc3_plp_select = plpselect_res;
			core->cmd->atsc3_plp_select = plpselect_req;
		} else
			DEMOD_ERROR("plp select failed from fw, %d\n", plpselect_res.retc);
	} else {
		DEMOD_WARN("_DEMOD_L1_Process failed with %d\n", err);
	}
	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_CMD_ATSC3_PLP_SELECT */


#ifdef DEMOD_CMD_ATSC3_STATUS
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
	int err = NO_DEMOD_ERROR;

	DEMOD_RES_ATSC3_STATUS_struct status_res;
	memset(&status_res, 0, sizeof(status_res));

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_ATSC3_STATUS_CODE, 0, NULL, sizeof(status_res), &status_res);
	if (NO_DEMOD_ERROR == err) {
		core->rsp->atsc3_status = status_res;
	} else {
		DEMOD_WARN("_DEMOD_L1_Process failed with %d\n", err);
	}

	DEMOD_L0_UnlockDevice(core->chip);

	DEMOD_DEBUG("A3S %u,%u,%u,%u,%u,x%02X\n",
		core->rsp->atsc3_status.if_agc, core->rsp->atsc3_status.eq_mse, core->rsp->atsc3_status.demod_mse, core->rsp->atsc3_status.sfo, core->rsp->atsc3_status.cfo, core->rsp->atsc3_status.reply_operMod);
	DEMOD_DEBUG("A3S %u,%u,%u %u,%u %u,%u %u\n",
		core->rsp->atsc3_status.done_bs, core->rsp->atsc3_status.done_acq, core->rsp->atsc3_status.init_sts_done,
		core->rsp->atsc3_status.l1b_scs, core->rsp->atsc3_status.l1b_ldpc_correct, core->rsp->atsc3_status.l1d_scs, core->rsp->atsc3_status.l1d_ldpc_correct,
		core->rsp->atsc3_status.plp_ldpc_correct);

	return err;
}
#endif /* DEMOD_CMD_ATSC3_STATUS */

#ifdef DEMOD_CMD_ATSC3_PLP_ID
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
	int err = NO_DEMOD_ERROR;

	DEMOD_RES_ATSC3_PLP_ID_struct plpid_res;
	memset(&plpid_res, 0, sizeof(plpid_res));

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_ATSC3_PLP_ID_CODE, 0, NULL, sizeof(plpid_res), &plpid_res);
	if (NO_DEMOD_ERROR == err) {
		core->rsp->atsc3_plp_id = plpid_res;
	} else {
		DEMOD_WARN("_DEMOD_L1_Process failed with %d\n", err);
	}

	DEMOD_L0_UnlockDevice(core->chip);

	return err;
}
#endif /* DEMOD_CMD_ATSC3_PLP_ID */

#ifdef DEMOD_CMD_ATSC3_PLP_INFO
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

int DEMOD_L1_GET_DD_ATSC3_PLP_Info (LX_DEMOD_L1_Context * core)
{
	int err = NO_DEMOD_ERROR;
	int i;

	DEMOD_RES_ATSC3_PLP_INFO_struct plpinfo_res;
	memset(&plpinfo_res, 0, sizeof(plpinfo_res));

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_ATSC3_PLP_INFO_CODE, 0, NULL, sizeof(plpinfo_res), &plpinfo_res);

	if (NO_DEMOD_ERROR == err) {
		plpinfo_res.bs_l1b_mode								+= 1;
		plpinfo_res.l1b_num_subframes						+= 1;
		plpinfo_res.l1b_pre_num_symbols						+= 1;
		plpinfo_res.l1b_num_ofdm_symbols					+= 1;
		plpinfo_res.l1d_mode								+= 1;

		for (i = 0; i < DEMOD_ATSC3_PLP_DEC_MAX; i++) {
			if (plpinfo_res.plp[i].dec_en) {
				plpinfo_res.sbf[i].num_ofdm_symbols	+= 1;
				plpinfo_res.sbf[i].num_plp	+= 1;
			}
		}

		core->rsp->atsc3_plp_info = plpinfo_res;
	} else {
		DEMOD_WARN("_DEMOD_L1_Process failed with %d\n", err);
	}

	DEMOD_L0_UnlockDevice(core->chip);

	DEMOD_DEBUG("A3I: %u,%u,%u,%u,%u,%u, retc %d\n",
		plpinfo_res.bs_l1b_mode, plpinfo_res.bs_sym, plpinfo_res.l1b_num_subframes,
		plpinfo_res.l1d_ap_mode, plpinfo_res.l1d_mode, plpinfo_res.plp[0].fec_type, err);
	return err;

}
#endif /* DEMOD_CMD_ATSC3_PLP_INFO */

#ifdef DEMOD_CMD_ATSC3_SET_BASEADDR_AXI
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L1_SET_DD_ATSC3_BASEADDR_AXI.
 * sets demoduator register through MCU
 *
 * @param *core 		[IN] LX_DEMOD_L1_Context
 * @param baseAddr		[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L1_SET_DD_ATSC3_BASEADDR_AXI (LX_DEMOD_L1_Context * core, UINT32 baseAddr)
{
	int err = NO_DEMOD_ERROR;

	DEMOD_CMD_ATSC3_SET_BASEADDR_AXI_struct baseaddr_req;
	DEMOD_RES_ATSC3_SET_BASEADDR_AXI_struct baseaddr_res;

	memset(&baseaddr_req, 0, sizeof(baseaddr_req));
	memset(&baseaddr_res, 0, sizeof(baseaddr_res));

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	baseaddr_req.baseAddr = baseAddr;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_ATSC3_SET_BASEADDR_AXI_CODE, sizeof(baseaddr_req), &baseaddr_req, sizeof(baseaddr_res), &baseaddr_res);
	if (NO_DEMOD_ERROR == err) {
		if (NO_DEMOD_ERROR == baseaddr_res.retc) {
			core->cmd->atsc3_baseaddr_axi = baseaddr_req;
		} else {
			DEMOD_WARN("DEMOD_CMD_ATSC3_SET_BASEADDR_AXI_CODE failed with %d\n", baseaddr_res.retc);
		}
	} else {
		DEMOD_WARN("_DEMOD_L1_Process failed with %d\n", err);
	}

	DEMOD_L0_UnlockDevice(core->chip);
	return err;

}
#endif /* DEMOD_CMD_SET_ISDBT_BASEADDR_AXI */

/*************************************************************************************/
/*************************************************************************************/
/*********ISDB-T/ DVBC / DVBC2/ DVBT / DVBT2/DVBS / DVBS2 / DEBUG/ functions **********/
/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/


#ifdef DEMOD_CMD_SET_ISDBT_BASEADDR_AXI
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
	cmdByteBuffer[0] = (UINT8)DEMOD_CMD_SET_ISDBT_BASEADDR_AXI_CODE;
	cmdByteBuffer[1] = 0;
	cmdByteBuffer[2] = 0;
	cmdByteBuffer[3] = 0;
	cmdByteBuffer[4] = (UINT8)(((baseAddr & DEMOD_CMD_SET_ISDBT_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_ISDBT_BASEADDR_AXI_BASEADDR_LSB) >>  0);
	cmdByteBuffer[5] = (UINT8)(((baseAddr & DEMOD_CMD_SET_ISDBT_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_ISDBT_BASEADDR_AXI_BASEADDR_LSB) >>  8);
	cmdByteBuffer[6] = (UINT8)(((baseAddr & DEMOD_CMD_SET_ISDBT_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_ISDBT_BASEADDR_AXI_BASEADDR_LSB) >> 16);
	cmdByteBuffer[7] = (UINT8)(((baseAddr & DEMOD_CMD_SET_ISDBT_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_ISDBT_BASEADDR_AXI_BASEADDR_LSB) >> 24);

	err = _DEMOD_L1_Process (core, DEMOD_CMD_SET_ISDBT_BASEADDR_AXI_CODE, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;

}
#endif /* DEMOD_CMD_SET_ISDBT_BASEADDR_AXI */

#ifdef DEMOD_CMD_SET_DTMB_BASEADDR_AXI
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

	cmdByteBuffer[0] = (UINT8)DEMOD_CMD_SET_DTMB_BASEADDR_AXI_CODE;
	cmdByteBuffer[1] = 0;
	cmdByteBuffer[2] = 0;
	cmdByteBuffer[3] = 0;
	cmdByteBuffer[4] = (UINT8)(((baseAddr & DEMOD_CMD_SET_DTMB_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_DTMB_BASEADDR_AXI_BASEADDR_LSB) >>  0);
	cmdByteBuffer[5] = (UINT8)(((baseAddr & DEMOD_CMD_SET_DTMB_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_DTMB_BASEADDR_AXI_BASEADDR_LSB) >>  8);
	cmdByteBuffer[6] = (UINT8)(((baseAddr & DEMOD_CMD_SET_DTMB_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_DTMB_BASEADDR_AXI_BASEADDR_LSB) >> 16);
	cmdByteBuffer[7] = (UINT8)(((baseAddr & DEMOD_CMD_SET_DTMB_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_DTMB_BASEADDR_AXI_BASEADDR_LSB) >> 24);

	err = _DEMOD_L1_Process (core, DEMOD_CMD_SET_DTMB_BASEADDR_AXI_CODE, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;

}
#endif /* DEMOD_CMD_SET_DTMB_BASEADDR_AXI */

#ifdef DEMOD_CMD_DVBC_SRD
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
	cmdByteBuffer[0] = (UINT8)DEMOD_CMD_DVBC_SRD_CODE;
	cmdByteBuffer[1] = (UINT8)((auto_en & DEMOD_CMD_DVBC_SRD_AUTO_EN_MASK) << DEMOD_CMD_DVBC_SRD_AUTO_EN_LSB);
	cmdByteBuffer[2] = (UINT8)((sym_rate & DEMOD_CMD_DVBC_SRD_SYM_RATE1_MASK) >> DEMOD_CMD_DVBC_SRD_SYM_RATE1_SHIFT );
	cmdByteBuffer[3] = (UINT8)((sym_rate & DEMOD_CMD_DVBC_SRD_SYM_RATE2_MASK) >> DEMOD_CMD_DVBC_SRD_SYM_RATE2_LSB);

	err = _DEMOD_L1_Process (core, DEMOD_CMD_DVBC_SRD_CODE, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_CMD_DVBC_SRD */


#ifdef DEMOD_CMD_DVBT2_PLP_SELECT
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
	cmdByteBuffer[0] = (UINT8)DEMOD_CMD_DVBT2_PLP_SELECT_CODE;
	cmdByteBuffer[1] = (UINT8)((plp_id & DEMOD_CMD_DVBT2_PLP_SELECT_PLP_ID_MASK) << DEMOD_CMD_DVBT2_PLP_SELECT_PLP_ID_LSB);
	cmdByteBuffer[2] = (UINT8)((plp_id_sel_mode & DEMOD_CMD_DVBT2_PLP_SELECT_PLP_ID_SEL_MODE_MASK) << DEMOD_CMD_DVBT2_PLP_SELECT_PLP_ID_SEL_MODE_LSB);

	err = _DEMOD_L1_Process (core, DEMOD_CMD_DVBT2_PLP_SELECT_CODE, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_CMD_DVBT2_PLP_SELECT */


#ifdef DEMOD_CMD_DVBC2_STARTFREQUENCY
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
	cmdByteBuffer[0] = (UINT8)DEMOD_CMD_DVBC2_STARTFREQUENCY_CODE;
	cmdByteBuffer[1] = (UINT8)(((freq & DEMOD_CMD_DVBC2_STARTFREQUENCY_FREQ_MASK) << DEMOD_CMD_DVBC2_STARTFREQUENCY_FREQ_LSB) >> 24);
   	cmdByteBuffer[2] = (UINT8)(((freq & DEMOD_CMD_DVBC2_STARTFREQUENCY_FREQ_MASK) << DEMOD_CMD_DVBC2_STARTFREQUENCY_FREQ_LSB) >> 16);
   	cmdByteBuffer[3] = (UINT8)(((freq & DEMOD_CMD_DVBC2_STARTFREQUENCY_FREQ_MASK) << DEMOD_CMD_DVBC2_STARTFREQUENCY_FREQ_LSB) >>  8);
   	cmdByteBuffer[4] = (UINT8)(((freq & DEMOD_CMD_DVBC2_STARTFREQUENCY_FREQ_MASK) << DEMOD_CMD_DVBC2_STARTFREQUENCY_FREQ_LSB) >>  0);

	err = _DEMOD_L1_Process (core, DEMOD_CMD_DVBC2_STARTFREQUENCY_CODE, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_CMD_DVBC2_STARTFREQUENCY */


#ifdef DEMOD_CMD_DVBC2_PLP_SELECT
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
	cmdByteBuffer[0] = (UINT8)DEMOD_CMD_DVBC2_PLP_SELECT_CODE;
	cmdByteBuffer[1] = (UINT8)((plp_id_mode & DEMOD_CMD_DVBC2_PLP_SELECT_PLP_ID_MODE_MASK) << DEMOD_CMD_DVBC2_PLP_SELECT_PLP_ID_MODE_LSB);
	cmdByteBuffer[2] = (UINT8)((plp_id & DEMOD_CMD_DVBC2_PLP_SELECT_PLP_ID_MASK) << DEMOD_CMD_DVBC2_PLP_SELECT_PLP_ID_LSB);
	cmdByteBuffer[3] = (UINT8)((ds_id & DEMOD_CMD_DVBC2_PLP_SELECT_DS_ID_MASK) << DEMOD_CMD_DVBC2_PLP_SELECT_DS_ID_LSB);

	err = _DEMOD_L1_Process (core, DEMOD_CMD_DVBC2_PLP_SELECT_CODE, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_CMD_DVBC2_PLP_SELECT */


#ifdef DEMOD_CMD_DISEQC_SEND
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
	cmdByteBuffer[0] = (UINT8)DEMOD_CMD_DISEQC_SEND_CODE;
	cmdByteBuffer[1] = (UINT8)((diseqc_en & DEMOD_CMD_DISEQC_SEND_DISEQC_EN_MASK) << DEMOD_CMD_DISEQC_SEND_DISEQC_EN_LSB |
                                         ( tone_burst & DEMOD_CMD_DISEQC_SEND_TONE_BURST_MASK) << DEMOD_CMD_DISEQC_SEND_TONE_BURST_LSB |
                                         ( cont_tone & DEMOD_CMD_DISEQC_SEND_CONT_TONE_MASK) << DEMOD_CMD_DISEQC_SEND_CONT_TONE_LSB |
                                         ( burst_sel& DEMOD_CMD_DISEQC_SEND_BURST_SEL_MASK) << DEMOD_CMD_DISEQC_SEND_BURST_SEL_LSB |
                                         ( msg_length     & DEMOD_CMD_DISEQC_SEND_MSG_LENGTH_MASK) << DEMOD_CMD_DISEQC_SEND_MSG_LENGTH_LSB);

	cmdByteBuffer[2] = (UINT8)((send_framing & DEMOD_CMD_DISEQC_SEND_SEND_FRAMING_MASK) << DEMOD_CMD_DISEQC_SEND_SEND_FRAMING_LSB);
	cmdByteBuffer[3] = (UINT8)	(( send_address & DEMOD_CMD_DISEQC_SEND_SEND_ADDRESS_MASK) << DEMOD_CMD_DISEQC_SEND_SEND_ADDRESS_LSB);
	cmdByteBuffer[4] = (UINT8)	(( send_command & DEMOD_CMD_DISEQC_SEND_SEND_COMMAND_MASK) << DEMOD_CMD_DISEQC_SEND_SEND_COMMAND_LSB);
	cmdByteBuffer[5] = (UINT8)	(( send_data0 & DEMOD_CMD_DISEQC_SEND_SEND_DATA0_MASK) << DEMOD_CMD_DISEQC_SEND_SEND_DATA0_LSB);
	cmdByteBuffer[6] = (UINT8)	(( send_data1 & DEMOD_CMD_DISEQC_SEND_SEND_DATA1_MASK) << DEMOD_CMD_DISEQC_SEND_SEND_DATA1_LSB);
	cmdByteBuffer[7] = (UINT8)	(( send_data2 & DEMOD_CMD_DISEQC_SEND_SEND_DATA2_MASK) << DEMOD_CMD_DISEQC_SEND_SEND_DATA2_LSB);

	err = _DEMOD_L1_Process (core, DEMOD_CMD_DISEQC_SEND_CODE, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_CMD_DISEQC_SEND */


#ifdef DEMOD_CMD_DVBS_OPERATING_MODE
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
	cmdByteBuffer[0] = (UINT8)DEMOD_CMD_DVBS_OPERATING_MODE_CODE;
  	cmdByteBuffer[1] = (UINT8)((opmSel & DEMOD_CMD_DVBS_OPERATING_MODE_OPM_SEL_MASK) << DEMOD_CMD_DVBS_OPERATING_MODE_OPM_SEL_LSB);
	cmdByteBuffer[2] = (UINT8)(((symbolRate_Khz & DEMOD_CMD_DVBS_OPERATING_MODE_SYMBOL_RATE_MASK) << DEMOD_CMD_DVBS_OPERATING_MODE_SYMBOL_RATE_LSB) >> 24);
	cmdByteBuffer[3] = (UINT8)(((symbolRate_Khz & DEMOD_CMD_DVBS_OPERATING_MODE_SYMBOL_RATE_MASK) << DEMOD_CMD_DVBS_OPERATING_MODE_SYMBOL_RATE_LSB) >> 16);
	cmdByteBuffer[4] = (UINT8)(((symbolRate_Khz & DEMOD_CMD_DVBS_OPERATING_MODE_SYMBOL_RATE_MASK) << DEMOD_CMD_DVBS_OPERATING_MODE_SYMBOL_RATE_LSB) >>  8);
	cmdByteBuffer[5] = (UINT8)((symbolRate_Khz & DEMOD_CMD_DVBS_OPERATING_MODE_SYMBOL_RATE_MASK) << DEMOD_CMD_DVBS_OPERATING_MODE_SYMBOL_RATE_LSB);
	cmdByteBuffer[6] = (UINT8)(((tuneFreq_Khz & DEMOD_CMD_DVBS_OPERATING_MODE_TUNE_FREQ3_MASK) << DEMOD_CMD_DVBS_OPERATING_MODE_TUN_FREQ3_LSB) >> 24);
	cmdByteBuffer[7] = (UINT8)(((tuneFreq_Khz & DEMOD_CMD_DVBS_OPERATING_MODE_TUNE_FREQ2_MASK) << DEMOD_CMD_DVBS_OPERATING_MODE_TUN_FREQ2_LSB) >> 16);
	cmdByteBuffer[8] = (UINT8)(((tuneFreq_Khz & DEMOD_CMD_DVBS_OPERATING_MODE_TUNE_FREQ1_MASK) << DEMOD_CMD_DVBS_OPERATING_MODE_TUN_FREQ1_LSB) >>  8);
	cmdByteBuffer[9] = (UINT8)((tuneFreq_Khz & DEMOD_CMD_DVBS_OPERATING_MODE_TUNE_FREQ0_MASK) << DEMOD_CMD_DVBS_OPERATING_MODE_TUN_FREQ0_LSB);

	err = _DEMOD_L1_Process (core, DEMOD_CMD_DVBS_OPERATING_MODE_CODE, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_CMD_DVBS_OPERATING_MODE */


#ifdef DEMOD_CMD_SET_SELF_RESET_PARAM
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
	cmdByteBuffer[0]  = (UINT8)DEMOD_CMD_SET_SELF_RESET_PARAM_CODE;
	cmdByteBuffer[1]  = (UINT8)((rst_arg	& DEMOD_CMD_SELF_RESET_RST_ARG_MASK) >> DEMOD_CMD_SELF_RESET_RST_ARG_LSB);
	cmdByteBuffer[2]  = (UINT8)((rst_time1	& DEMOD_CMD_SELF_RESET_RST_TIME1_MASK) >> DEMOD_CMD_SELF_RESET_RST_TIME1_LSB);
	cmdByteBuffer[3]  = (UINT8)((rst_time1	& DEMOD_CMD_SELF_RESET_RST_TIME2_MASK) >> DEMOD_CMD_SELF_RESET_RST_TIME2_LSB);
	cmdByteBuffer[4]  = (UINT8)((rst_time2	& DEMOD_CMD_SELF_RESET_RST_TIME1_MASK) >> DEMOD_CMD_SELF_RESET_RST_TIME1_LSB);
	cmdByteBuffer[5]  = (UINT8)((rst_time2	& DEMOD_CMD_SELF_RESET_RST_TIME2_MASK) >> DEMOD_CMD_SELF_RESET_RST_TIME2_LSB);
	cmdByteBuffer[6]  = (UINT8)((rst_time3	& DEMOD_CMD_SELF_RESET_RST_TIME1_MASK) >> DEMOD_CMD_SELF_RESET_RST_TIME1_LSB);
	cmdByteBuffer[7]  = (UINT8)((rst_time3	& DEMOD_CMD_SELF_RESET_RST_TIME2_MASK) >> DEMOD_CMD_SELF_RESET_RST_TIME2_LSB);
	cmdByteBuffer[8]  = (UINT8)((rst_time4	& DEMOD_CMD_SELF_RESET_RST_TIME1_MASK) >> DEMOD_CMD_SELF_RESET_RST_TIME1_LSB);
	cmdByteBuffer[9]  = (UINT8)((rst_time4	& DEMOD_CMD_SELF_RESET_RST_TIME2_MASK) >> DEMOD_CMD_SELF_RESET_RST_TIME2_LSB);
	cmdByteBuffer[10] = (UINT8)((rst_cnt	& DEMOD_CMD_SELF_RESET_RST_ARG_MASK) >> DEMOD_CMD_SELF_RESET_RST_ARG_LSB);

	//For ATSC 3.0//
	cmdByteBuffer[11] = (UINT8) ( ( plp0_thd  & 0xFF00) >> 8 );
	cmdByteBuffer[12] = (UINT8) (plp0_thd  & 0x00FF);
	cmdByteBuffer[13] = (UINT8) ( ( plp1_thd  & 0xFF00) >> 8 );
	cmdByteBuffer[14] = (UINT8) (plp1_thd  & 0x00FF);
	cmdByteBuffer[15] = (UINT8) ( ( plp2_thd  & 0xFF00) >> 8 );
	cmdByteBuffer[16] = (UINT8) (plp2_thd  & 0x00FF);
	cmdByteBuffer[17] = (UINT8) ( ( plp3_thd  & 0xFF00) >> 8 );
	cmdByteBuffer[18] = (UINT8) (plp3_thd  & 0x00FF);
	
	err = _DEMOD_L1_Process (core, DEMOD_CMD_SET_SELF_RESET_PARAM_CODE, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_CMD_SELF_RESET */


#ifdef DEMOD_CMD_DVBT2_STATUS
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
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	rspByte=28;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_DVBT2_STATUS_CODE, 0, NULL, rspByte, rspByteBuffer);

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
#endif /* DEMOD_CMD_DVBT2_STATUS */


#ifdef DEMOD_CMD_GET_DVBT2_PLP_ID
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
	cmdByteBuffer[0] = DEMOD_CMD_GET_DVBT2_PLP_ID_CODE;
	cmdByteBuffer[1] = index;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_GET_DVBT2_PLP_ID_CODE, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	core->rsp->dvbt2_plp_id.plp_id			=(((rspByteBuffer[0]) >> DEMOD_DD_GET_DVBT2_PLP_ID_RESPONSE_PLP_ID_LSB) & DEMOD_DD_GET_DVBT2_PLP_ID_RESPONSE_PLP_ID_MASK);
	core->rsp->dvbt2_plp_id.plp_conf		=(((rspByteBuffer[1]) >> DEMOD_DD_GET_DVBT2_PLP_ID_RESPONSE_PLP_CONF_LSB) & DEMOD_DD_GET_DVBT2_PLP_ID_RESPONSE_PLP_CONF_MASK);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;

}
#endif /* DEMOD_CMD_GET_DVBT2_PLP_ID */


#ifdef DEMOD_CMD_DVBT_STATUS
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
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	rspByte=26;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_DVBT_STATUS_CODE, 0, NULL, rspByte, rspByteBuffer);

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
#endif /* DEMOD_CMD_DVBT_STATUS */


#ifdef DEMOD_CMD_ISDBT_STATUS
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
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	rspByte=19;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_ISDBT_STATUS_CODE, 0, NULL, rspByte, rspByteBuffer);

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

#endif /* DEMOD_CMD_ISDBT_STATUS */


#ifdef DEMOD_CMD_ISDBT_TMCC_INFO
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
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	rspByte=7;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_ISDBT_TMCC_INFO_CODE, 0, NULL, rspByte, rspByteBuffer);

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
#endif /* DEMOD_CMD_ISDBT_STATUS */


#ifdef DEMOD_CMD_DVBC_STATUS
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
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	rspByte=19;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_DVBC_STATUS_CODE, 0, NULL, rspByte, rspByteBuffer);

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
#endif /* DEMOD_CMD_DVBC_STATUS */


#ifdef DEMOD_CMD_DVBC2_STATUS
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
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	rspByte=18;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_DVBC2_STATUS_CODE, 0, NULL, rspByte, rspByteBuffer);

	core->rsp->dvbc2_status.if_agc			= ((((rspByteBuffer[1]) | (rspByteBuffer[0] << 8)) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_IF_AGC_LSB) & DEMOD_DD_DVBC2_STATUS_RESPONSE_IF_AGC_MASK);
	core->rsp->dvbc2_status.mse_info		= ((((rspByteBuffer[3]) | (rspByteBuffer[2] << 8)) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_MSE_INFO_LSB) & DEMOD_DD_DVBC2_STATUS_RESPONSE_MSE_INFO_MASK);
	core->rsp->dvbc2_status.ber			= ((((rspByteBuffer[5]) | (rspByteBuffer[4] << 8)) >> DEMOD_DD_DVBC2_STATUS_RESPONSE_BER_LSB) & DEMOD_DD_DVBC2_STATUS_RESPONSE_BER_MASK);
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
#endif /* DEMOD_CMD_DVBC2_STATUS */

#ifdef DEMOD_CMD_DTMB_STATUS
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
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	rspByte=19;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_DTMB_STATUS_CODE, 0, NULL, rspByte, rspByteBuffer);

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
#endif /* DEMOD_CMD_DTMB_STATUS */


#ifdef DEMOD_CMD_DISEQC_STATUS
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
#endif /*DEMOD_CMD_DISEQC_STATUS*/


#ifdef DEMOD_CMD_DVBS_STATUS
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
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	rspByte=20;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_DVBS_STATUS_CODE, 0, NULL, rspByte, rspByteBuffer);

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
#endif /* DEMOD_CMD_DVBS_STATUS */


#ifdef DEMOD_CMD_DVBS2_STATUS
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
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	rspByte=20;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_DVBS2_STATUS_CODE, 0, NULL, rspByte, rspByteBuffer);

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
#endif /* DEMOD_CMD_DVBS2_STATUS */


#ifdef DEMOD_CMD_LOCKTIME
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
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	rspByte=24;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_LOCKTIME_CODE, 0, NULL, rspByte, rspByteBuffer);

	DEMOD_DEBUG("timeStamp1 : %x\n", ((rspByteBuffer[ 3] << 24) | (rspByteBuffer[ 2] << 16) | (rspByteBuffer[ 1] << 8) | rspByteBuffer[ 0]));
	DEMOD_DEBUG("timeStamp2 : %x\n", ((rspByteBuffer[ 7] << 24) | (rspByteBuffer[ 6] << 16) | (rspByteBuffer[ 5] << 8) | rspByteBuffer[ 4]));
	DEMOD_DEBUG("timeStamp3 : %x\n", ((rspByteBuffer[11] << 24) | (rspByteBuffer[10] << 16) | (rspByteBuffer[ 9] << 8) | rspByteBuffer[ 8]));
	DEMOD_DEBUG("timeLock1  : %x\n", ((rspByteBuffer[15] << 24) | (rspByteBuffer[14] << 16) | (rspByteBuffer[13] << 8) | rspByteBuffer[12]));
	DEMOD_DEBUG("timeLock2  : %x\n", ((rspByteBuffer[19] << 24) | (rspByteBuffer[18] << 16) | (rspByteBuffer[17] << 8) | rspByteBuffer[16]));
	DEMOD_DEBUG("timeLock3  : %x\n", ((rspByteBuffer[23] << 24) | (rspByteBuffer[22] << 16) | (rspByteBuffer[21] << 8) | rspByteBuffer[20]));

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_CMD_LOCKTIME */


#ifdef DEMOD_CMD_GET_SIGSRCH_NUM
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
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	rspByte=1;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_GET_SIGSRCH_NUM_CODE, 0, NULL, rspByte, rspByteBuffer);

	core->rsp->dd_sigsrch_num.ch_num			= ((rspByteBuffer[0]  >> DEMOD_DD_GET_DD_SIGSRCH_NUM_RESPONSE_CH_NUM_LSB) & DEMOD_DD_GET_DD_SIGSRCH_NUM_RESPONSE_CH_NUM_MASK);

	DEMOD_INFO("Blind search : %d found\n", core->rsp->dd_sigsrch_num.ch_num);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_CMD_GET_SIGSRCH_NUM */


#ifdef DEMOD_CMD_GET_SIGSRCH_INFO
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
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	rspByte=6;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_GET_SIGSRCH_INFO_CODE, 0, NULL, rspByte, rspByteBuffer);

	core->rsp->dd_sigsrch_info.bw_idx		= ((((rspByteBuffer[1]) | (rspByteBuffer[0] << 8)) >> DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_BW_IDX_LSB) & DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_BW_IDX_MASK);
	core->rsp->dd_sigsrch_info.center_idx	= ((((rspByteBuffer[5]) | (rspByteBuffer[4] << 8) | (rspByteBuffer[3] << 16) | (rspByteBuffer[2] << 24)) >> DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_CENTER_IDX_LSB) & DEMOD_DD_GET_DD_SIGSRCH_INFO_RESPONSE_CENTER_IDX_MASK);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_CMD_GET_SIGSRCH_INFO */


#ifdef DEMOD_CMD_BLIND_STATUS
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
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	rspByte=1;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_BLIND_STATUS_CODE, 0, NULL, rspByte, rspByteBuffer);

	core->rsp->blind_status.blindStatus		= ((rspByteBuffer[0]  >> DEMOD_DD_BLIND_STATUS_RESPONSE_BLINDSTATUS_LSB) & DEMOD_DD_BLIND_STATUS_RESPONSE_BLINDSTATUS_MASK);
	core->rsp->blind_status.blindDone		= ((rspByteBuffer[0]  >> DEMOD_DD_BLIND_STATUS_RESPONSE_BLINDDONE_LSB) & DEMOD_DD_BLIND_STATUS_RESPONSE_BLINDDONE_MASK);
	core->rsp->blind_status.blindLock		= ((rspByteBuffer[0]  >> DEMOD_DD_BLIND_STATUS_RESPONSE_BLINDLOCK_LSB) & DEMOD_DD_BLIND_STATUS_RESPONSE_BLINDLOCK_MASK);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_CMD_BLIND_STATUS */


#ifdef DEMOD_CMD_BLIND_INIT
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

	cmdByteBuffer[0] = (UINT8)DEMOD_CMD_BLIND_INIT_CODE;
	cmdByteBuffer[1] = (UINT8)((( startFreq  & DEMOD_CMD_BLIND_INIT_STARTFREQ_MASK) << DEMOD_CMD_BLIND_INIT_STARTFREQ_LSB) >>  0);
	cmdByteBuffer[2] = (UINT8)((( startFreq  & DEMOD_CMD_BLIND_INIT_STARTFREQ_MASK) << DEMOD_CMD_BLIND_INIT_STARTFREQ_LSB) >>  8);
	cmdByteBuffer[3] = (UINT8)((( startFreq  & DEMOD_CMD_BLIND_INIT_STARTFREQ_MASK) << DEMOD_CMD_BLIND_INIT_STARTFREQ_LSB) >> 16);
	cmdByteBuffer[4] = (UINT8)((( startFreq  & DEMOD_CMD_BLIND_INIT_STARTFREQ_MASK) << DEMOD_CMD_BLIND_INIT_STARTFREQ_LSB) >> 24);
	cmdByteBuffer[5] = (UINT8)((( endFreq    & DEMOD_CMD_BLIND_INIT_ENDFREQ_MASK) << DEMOD_CMD_BLIND_INIT_ENDFREQ_LSB) >>  0);
	cmdByteBuffer[6] = (UINT8)((( endFreq    & DEMOD_CMD_BLIND_INIT_ENDFREQ_MASK) << DEMOD_CMD_BLIND_INIT_ENDFREQ_LSB) >>  8);
	cmdByteBuffer[7] = (UINT8)((( endFreq    & DEMOD_CMD_BLIND_INIT_ENDFREQ_MASK) << DEMOD_CMD_BLIND_INIT_ENDFREQ_LSB) >> 16);
	cmdByteBuffer[8] = (UINT8)((( endFreq    & DEMOD_CMD_BLIND_INIT_ENDFREQ_MASK) << DEMOD_CMD_BLIND_INIT_ENDFREQ_LSB) >> 24);

	err = _DEMOD_L1_Process (core, DEMOD_CMD_BLIND_INIT_CODE, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_CMD_BLIND_INIT */


#ifdef DEMOD_CMD_BLIND_END
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
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_BLIND_END_CODE, 0, NULL, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_CMD_BLIND_INIT */

#ifdef DEMOD_CMD_BLIND_FOUNDINFO
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
	UINT8 rspByte=0;

	if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(core->chip))
		return ERROR_DEMOD_OS_LOCK;

	rspByte=6;

	err = _DEMOD_L1_Process (core, DEMOD_CMD_BLIND_FOUNDINFO_CODE, 0, NULL, rspByte, rspByteBuffer);

	core->rsp->blind_foundinfo.symrate		= ((((rspByteBuffer[1]) | (rspByteBuffer[0] << 8)) >> DEMOD_DD_BLIND_FOUNDINFO_RESPONSE_SYMRATE_LSB) & DEMOD_DD_BLIND_FOUNDINFO_RESPONSE_SYMRATE_MASK);
	core->rsp->blind_foundinfo.center		= ((((rspByteBuffer[5]) | (rspByteBuffer[4] << 8) | (rspByteBuffer[3] << 16) | (rspByteBuffer[2] << 24)) >> DEMOD_DD_BLIND_FOUNDINFO_RESPONSE_CENTER_LSB) & DEMOD_DD_BLIND_FOUNDINFO_RESPONSE_CENTER_MASK);//TO DO

	DEMOD_L0_UnlockDevice(core->chip);
	return err;
}
#endif /* DEMOD_CMD_BLIND_FOUNDINFO */


#ifdef DEMOD_CMD_SET_DVBT2_BASEADDR_AXI
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
	cmdByteBuffer[0]  = (UINT8)DEMOD_CMD_SET_DVBT2_BASEADDR_AXI_CODE;
	cmdByteBuffer[1]  = (UINT8)0;
	cmdByteBuffer[2]  = (UINT8)0;
	cmdByteBuffer[3]  = (UINT8)0;
	cmdByteBuffer[4]  = (UINT8)((baseAddr1 & DEMOD_CMD_SET_DVBT2_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_DVBT2_BASEADDR_AXI_BASEADDR_LSB);
	cmdByteBuffer[5]  = (UINT8)(((baseAddr1 & DEMOD_CMD_SET_DVBT2_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_DVBT2_BASEADDR_AXI_BASEADDR_LSB) >>  8);
	cmdByteBuffer[6]  = (UINT8)(((baseAddr1 & DEMOD_CMD_SET_DVBT2_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_DVBT2_BASEADDR_AXI_BASEADDR_LSB) >> 16);
	cmdByteBuffer[7]  = (UINT8)(((baseAddr1 & DEMOD_CMD_SET_DVBT2_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_DVBT2_BASEADDR_AXI_BASEADDR_LSB) >> 24);
	cmdByteBuffer[8]  = (UINT8)((baseAddr2 & DEMOD_CMD_SET_DVBT2_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_DVBT2_BASEADDR_AXI_BASEADDR_LSB);
	cmdByteBuffer[9]  = (UINT8)(((baseAddr2 & DEMOD_CMD_SET_DVBT2_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_DVBT2_BASEADDR_AXI_BASEADDR_LSB) >>  8);
	cmdByteBuffer[10] = (UINT8)(((baseAddr2 & DEMOD_CMD_SET_DVBT2_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_DVBT2_BASEADDR_AXI_BASEADDR_LSB) >> 16);
	cmdByteBuffer[11] = (UINT8)(((baseAddr2 & DEMOD_CMD_SET_DVBT2_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_DVBT2_BASEADDR_AXI_BASEADDR_LSB) >> 24);

	err = _DEMOD_L1_Process (core, DEMOD_CMD_SET_DVBT2_BASEADDR_AXI_CODE, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;

}
#endif /* DEMOD_CMD_SET_DVBT2_BASEADDR_AXI */


#ifdef DEMOD_CMD_SET_DVB_BASEADDR_AXI
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
	cmdByteBuffer[0]  = (UINT8)DEMOD_CMD_SET_DVB_BASEADDR_AXI_CODE;
	cmdByteBuffer[1]  = (UINT8)0;
	cmdByteBuffer[2]  = (UINT8)0;
	cmdByteBuffer[3]  = (UINT8)0;
	cmdByteBuffer[4]  = (UINT8)((baseAddr1 & DEMOD_CMD_SET_DVB_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_DVB_BASEADDR_AXI_BASEADDR_LSB);
	cmdByteBuffer[5]  = (UINT8)(((baseAddr1 & DEMOD_CMD_SET_DVB_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_DVB_BASEADDR_AXI_BASEADDR_LSB) >>  8);
	cmdByteBuffer[6]  = (UINT8)(((baseAddr1 & DEMOD_CMD_SET_DVB_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_DVB_BASEADDR_AXI_BASEADDR_LSB) >> 16);
	cmdByteBuffer[7]  = (UINT8)(((baseAddr1 & DEMOD_CMD_SET_DVB_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_DVB_BASEADDR_AXI_BASEADDR_LSB) >> 24);
	cmdByteBuffer[8]  = (UINT8)((baseAddr2 & DEMOD_CMD_SET_DVB_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_DVB_BASEADDR_AXI_BASEADDR_LSB);
	cmdByteBuffer[9]  = (UINT8)(((baseAddr2 & DEMOD_CMD_SET_DVB_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_DVB_BASEADDR_AXI_BASEADDR_LSB) >>  8);
	cmdByteBuffer[10] = (UINT8)(((baseAddr2 & DEMOD_CMD_SET_DVB_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_DVB_BASEADDR_AXI_BASEADDR_LSB) >> 16);
	cmdByteBuffer[11] = (UINT8)(((baseAddr2 & DEMOD_CMD_SET_DVB_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_DVB_BASEADDR_AXI_BASEADDR_LSB) >> 24);
	cmdByteBuffer[12] = (UINT8)((baseAddr3 & DEMOD_CMD_SET_DVB_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_DVB_BASEADDR_AXI_BASEADDR_LSB);
	cmdByteBuffer[13] = (UINT8)(((baseAddr3 & DEMOD_CMD_SET_DVB_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_DVB_BASEADDR_AXI_BASEADDR_LSB) >>  8);
	cmdByteBuffer[14] = (UINT8)(((baseAddr3 & DEMOD_CMD_SET_DVB_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_DVB_BASEADDR_AXI_BASEADDR_LSB) >> 16);
	cmdByteBuffer[15] = (UINT8)(((baseAddr3 & DEMOD_CMD_SET_DVB_BASEADDR_AXI_BASEADDR_MASK) << DEMOD_CMD_SET_DVB_BASEADDR_AXI_BASEADDR_LSB) >> 24);

	err = _DEMOD_L1_Process (core, DEMOD_CMD_SET_DVB_BASEADDR_AXI_CODE, cmdByte, cmdByteBuffer, rspByte, rspByteBuffer);

	DEMOD_L0_UnlockDevice(core->chip);
	return err;

}
#endif /* DEMOD_CMD_SET_DVBT2_BASEADDR_AXI */

/***********************************************************************************************************************
  DEMOD_L1_CommandDump function
  Use:        command text function
              Used to turn the command data into clear text.
  Parameter: *rsp     the DEMOD_CmdReplyObj structure (containing all commands)
  Parameter: rsp_code the command Id (used to know which command to use)
  Returns:    NO_DEMOD_ERROR if successful.
 ***********************************************************************************************************************/
int DEMOD_L1_CommandDump (LX_DEMOD_L1_CmdReplyObj *rsp, UINT32 cmd_code, char *logbuf, int *pidx)
{
	int i;
	int idx = *pidx;

	const char * str1 = NULL, * str2 = NULL, * str3 = NULL, * str4 = NULL;

	switch (cmd_code) {
		case DEMOD_CMD_STATUS_CODE:
			idx += SPRINTF(logbuf + idx, "DD_STATUS\n");
			idx += SPRINTF(logbuf + idx, "\t""OP_MODE   : %s\n",				DEMOD_L1_API_Modulation_Text((DEMOD_MODULATION)rsp->dd_status.reply_operMod));

			str1 = (rsp->dd_status.lock_fec == DEMOD_LOCK_LOCKED) ? "Locked" : "UnLocked";
			idx += SPRINTF(logbuf + idx, "\t""FEC_LOCK  : %s\n",				str1);

			switch(rsp->dd_status.neverLock) {
			case DEMOD_STATUS_NEVERLOCK_LOCKED:						str1 = "Locked";		break;
			case DEMOD_STATUS_NEVERLOCK_PROCESSING:					str1 = "Processing";	break;
			case DEMOD_STATUS_NEVERLOCK_NO_LOCK:					str1 = "UnLocked";		break;
			default:															str1 = "INV";			break;
			}
			idx += SPRINTF(logbuf + idx, "\t""NEVER_LOCK: %s\n",				str1);
			break;

#ifdef DEMOD_CMD_ATSC3_STATUS
		case DEMOD_CMD_ATSC3_STATUS_CODE:
			idx += SPRINTF(logbuf + idx, "ATSC3_STATUS\n");

			idx += SPRINTF(logbuf + idx, "\t""IF_AGC    : %u\n",				(rsp->atsc3_status.if_agc));
			idx += SPRINTF(logbuf + idx, "\t""SPECINV   : %s\n",				(rsp->atsc3_status.spInv == DEMOD_ATSC3_STATUS_SPECINV_NORMAL) ? "Normal" : "Inverted");
			switch(rsp->atsc3_status.bs_system_bw) {
			case DEMOD_ATSC3_STATUS_BANDWIDTH_6MHZ:					str1 = "6MHZ";			break;
			case DEMOD_ATSC3_STATUS_BANDWIDTH_7MHZ:					str1 = "7MHZ";			break;
			case DEMOD_ATSC3_STATUS_BANDWIDTH_8MHZ:					str1 = "8MHZ";			break;
			default:															str1 = "G/T 8MHZ";		break;
			}
			idx += SPRINTF(logbuf + idx, "\t""B/W       : %s\n",				(str1));
			idx += SPRINTF(logbuf + idx, "\t""TI_EQ     : %u\n",				(rsp->atsc3_status.ti_eq));
			idx += SPRINTF(logbuf + idx, "\t""EQ_MSE    : %u\n",				(rsp->atsc3_status.eq_mse));
			idx += SPRINTF(logbuf + idx, "\t""DEMOD_MSE : %u\n",				(rsp->atsc3_status.demod_mse));
			idx += SPRINTF(logbuf + idx, "\t""CFO_VALUE : 0x%x\n",				(rsp->atsc3_status.cfo));
			idx += SPRINTF(logbuf + idx, "\t""SFO_VALUE : 0x%x\n",				(rsp->atsc3_status.sfo));
			idx += SPRINTF(logbuf + idx, "\t""BS_DONE   : %s\n",				(rsp->atsc3_status.done_bs == DEMOD_ATSC3_STATUS_DONE_BS_DEC_DONE) ? "Locked" : "UnLocked");
			idx += SPRINTF(logbuf + idx, "\t""ACQ_DONE  : %s\n",				(rsp->atsc3_status.done_acq == DEMOD_ATSC3_STATUS_DONE_BS_DEC_DONE) ? "Locked" : "UnLocked");
			idx += SPRINTF(logbuf + idx, "\t""L1B_SCS   : %s\n",				(rsp->atsc3_status.l1b_scs == DEMOD_ATSC3_STATUS_LOCK_L1B_LOCKED) ? "Locked" : "UnLocked");
			idx += SPRINTF(logbuf + idx, "\t""L1B_LDPC  : correct %u, iter %u\n",
																				(rsp->atsc3_status.l1b_ldpc_correct),
																				(rsp->atsc3_status.l1b_ldpc_iter));
			idx += SPRINTF(logbuf + idx, "\t""L1D_SCS   : %s\n",				(rsp->atsc3_status.l1d_scs == DEMOD_ATSC3_STATUS_LOCK_L1D_LOCKED) ? "Locked" : "UnLocked");
			idx += SPRINTF(logbuf + idx, "\t""L1D_LDPC  : correct %u, iter %u\n",
																				(rsp->atsc3_status.l1d_ldpc_correct),
																				(rsp->atsc3_status.l1d_ldpc_iter));
			str1 = DEMOD_L1_API_FFT_Mode_Text(rsp->atsc3_status.fft_mode);
			idx += SPRINTF(logbuf + idx, "\t""FFT_MODE  : %s\n",				(str1));
			idx += SPRINTF(logbuf + idx, "\t""PLP_EXIST : %u%u%u%u\n",			(rsp->atsc3_status.plp_exist >> 3 & 0x1),
																				(rsp->atsc3_status.plp_exist >> 2 & 0x1),
																				(rsp->atsc3_status.plp_exist >> 1 & 0x1),
																				(rsp->atsc3_status.plp_exist >> 0 & 0x1));
			idx += SPRINTF(logbuf + idx, "\t""PLP_TOTAL : %u\n",				(rsp->atsc3_status.num_plp_total));
			idx += SPRINTF(logbuf + idx, "\t""PLP_LDPC  : correct %u, iter %u, err %u\n",
																				(rsp->atsc3_status.plp_ldpc_correct),
																				(rsp->atsc3_status.plp_ldpc_iter),
																				(rsp->atsc3_status.plp_ldpc_err));
			idx += SPRINTF(logbuf + idx, "\t""PLP_PKERR : %u, %u, %u, %u\n",	(rsp->atsc3_status.plp_pkerr[0]),
																				(rsp->atsc3_status.plp_pkerr[1]),
																				(rsp->atsc3_status.plp_pkerr[2]),
																				(rsp->atsc3_status.plp_pkerr[3]));
			break;
#endif

#ifdef DEMOD_CMD_VSB_STATUS
		case DEMOD_CMD_VSB_STATUS_CODE:
			idx += SPRINTF(logbuf + idx, "VSB_STATUS\n");

			idx += SPRINTF(logbuf + idx, "\t""IF_AGC    : %u\n",				(rsp->vsb_status.if_agc));
			idx += SPRINTF(logbuf + idx, "\t""SPECINV   : %s\n",				(rsp->vsb_status.spInv == DEMOD_PROP_MODE_SPECINV_INVERSION) ? "Inverted" : "Normal");
			idx += SPRINTF(logbuf + idx, "\t""MSE_INFO  : %u\n",				(rsp->vsb_status.mse_info));
			idx += SPRINTF(logbuf + idx, "\t""BER       : %u\n",				(rsp->vsb_status.ber));
			idx += SPRINTF(logbuf + idx, "\t""CFO_VALUE : 0x%x\n",				(rsp->vsb_status.cfo));
			idx += SPRINTF(logbuf + idx, "\t""SFO_VALUE : 0x%x\n",				(rsp->vsb_status.sfo));
			idx += SPRINTF(logbuf + idx, "\t""FEC_LOCK  : %s\n",				(rsp->vsb_status.lock_fec == DEMOD_LOCK_LOCKED) ? "Locked" : "UnLocked");
			idx += SPRINTF(logbuf + idx, "\t""CARR_LOCK : %s\n",				(rsp->vsb_status.lock_carr == DEMOD_LOCK_LOCKED) ? "Locked" : "UnLocked");
			idx += SPRINTF(logbuf + idx, "\t""PKT ERROR : %u",					(rsp->vsb_status.pe));
			break;
#endif

#ifdef DEMOD_CMD_QAM_STATUS
		case DEMOD_CMD_QAM_STATUS_CODE:
			idx += SPRINTF(logbuf + idx, "QAM_STATUS\n");

			idx += SPRINTF(logbuf + idx, "\t""IF_AGC    : %u\n",				(rsp->qam_status.if_agc));
			idx += SPRINTF(logbuf + idx, "\t""SPECINV   : %s\n",				(rsp->qam_status.spInv == DEMOD_PROP_MODE_SPECINV_INVERSION) ? "Inverted" : "Normal");
			idx += SPRINTF(logbuf + idx, "\t""MSE_INFO  : %u\n",				(rsp->qam_status.mse_info));
			idx += SPRINTF(logbuf + idx, "\t""BER       : %u\n",				(rsp->qam_status.ber));
			idx += SPRINTF(logbuf + idx, "\t""CFO_VALUE : 0x%x\n",				(rsp->qam_status.cfo));
			idx += SPRINTF(logbuf + idx, "\t""SFO_VALUE : 0x%x\n",				(rsp->qam_status.sfo));
			idx += SPRINTF(logbuf + idx, "\t""SYM_RATE  : %u KHz\n",			(rsp->qam_status.sym_rate));
			switch(rsp->qam_status.constellation) {
			case DEMOD_CONSTELLATION_QAM64:					str1 = "64QAM";			break;
			case DEMOD_CONSTELLATION_QAM256:					str1 = "256QAM";		break;
			default:															str1 = "INV";			break;
			}
			idx += SPRINTF(logbuf + idx, "\t""CONSTEL.. : %s\n",				str1);

			idx += SPRINTF(logbuf + idx, "\t""FEC_LOCK  : %s\n",				(rsp->qam_status.lock_fec == DEMOD_LOCK_LOCKED) ? "Locked" : "UnLocked");
			idx += SPRINTF(logbuf + idx, "\t""CARR_LOCK : %s\n",				(rsp->qam_status.lock_carr == DEMOD_LOCK_LOCKED) ? "Locked" : "UnLocked");
			idx += SPRINTF(logbuf + idx, "\t""PKT ERROR : %u",					(rsp->qam_status.pe));

			break;
#endif

#ifdef DEMOD_CMD_DVBC_STATUS
		case DEMOD_CMD_DVBC_STATUS_CODE:
			idx += SPRINTF(logbuf + idx, "DVBC_STATUS\n");

			idx += SPRINTF(logbuf + idx, "\t""IF_AGC    : %u\n",				(rsp->dvbc_status.if_agc));
			idx += SPRINTF(logbuf + idx, "\t""SPECINV   : %s\n",				(rsp->dvbc_status.spInv == DEMOD_PROP_MODE_SPECINV_INVERSION) ? "Inverted" : "Normal");
			idx += SPRINTF(logbuf + idx, "\t""MSE_INFO  : %u\n",				(rsp->dvbc_status.mse_info));
			idx += SPRINTF(logbuf + idx, "\t""BER       : %u\n",				(rsp->dvbc_status.ber));
			idx += SPRINTF(logbuf + idx, "\t""CFO_VALUE : 0x%x\n",				(rsp->dvbc_status.cfo));
			idx += SPRINTF(logbuf + idx, "\t""SFO_VALUE : 0x%x\n",				(rsp->dvbc_status.sfo));
			idx += SPRINTF(logbuf + idx, "\t""SYM_RATE  : %u KHz\n",			(rsp->dvbc_status.sym_rate));
			
			switch(rsp->dvbc_status.constellation) {
			case DEMOD_CONSTELLATION_QAM16:
			case DEMOD_CONSTELLATION_QAM32:
			case DEMOD_CONSTELLATION_QAM64:
			case DEMOD_CONSTELLATION_QAM128:
			case DEMOD_CONSTELLATION_QAM256:
				str1 = DEMOD_L1_API_Constellation_Text(rsp->dvbc_status.constellation);
				break;
			default:
				str1 = "INV";
				break;
			}
			idx += SPRINTF(logbuf + idx, "\t""CONSTEL.. : %s\n",				str1);

			idx += SPRINTF(logbuf + idx, "\t""FEC_LOCK  : %s\n",				(rsp->dvbc_status.lock_fec == DEMOD_LOCK_LOCKED) ? "Locked" : "UnLocked");
			idx += SPRINTF(logbuf + idx, "\t""CARR_LOCK : %s\n",				(rsp->dvbc_status.lock_carr == DEMOD_LOCK_LOCKED) ? "Locked" : "UnLocked");
			idx += SPRINTF(logbuf + idx, "\t""PKT ERROR : %u",					(rsp->dvbc_status.pe));

			break;
#endif

#ifdef DEMOD_CMD_GET_PART_INFO
		case DEMOD_CMD_GET_PART_INFO_CODE:
			idx += SPRINTF(logbuf + idx, "FW INFO\n");

			idx += SPRINTF(logbuf + idx, "\t""FW_VERSION : %d.%d.0\n",			(rsp->part_info.fw_major), (rsp->part_info.fw_minor));
			idx += SPRINTF(logbuf + idx, "\t""FW_DATE    : %4d/%2d/%2d\n",		(rsp->part_info.fw_year), (rsp->part_info.fw_month), (rsp->part_info.fw_day));
			idx += SPRINTF(logbuf + idx, "\t""FW_CHIP_REV: %d\n",				(rsp->part_info.chip_rev));
			break;
#endif

#ifdef DEMOD_CMD_ATSC3_PLP_INFO
		case DEMOD_CMD_ATSC3_PLP_INFO_CODE:
			idx += SPRINTF(logbuf + idx, "ATSC3_PLP_INFO\n");
			idx += SPRINTF(logbuf + idx, "\t""BS        : pre_str %d\n", 		rsp->atsc3_plp_info.bs_pre_str);
			idx += SPRINTF(logbuf + idx, "\t""BS        : l1b_mode %d\n", 		rsp->atsc3_plp_info.bs_l1b_mode);
			idx += SPRINTF(logbuf + idx, "\t""BS        : symbol %d\n", 		rsp->atsc3_plp_info.bs_sym);
			idx += SPRINTF(logbuf + idx, "\t""BS        : minor %d\n", 			rsp->atsc3_plp_info.bs_minor);
			idx += SPRINTF(logbuf + idx, "\t""L1B       : #of subf %d, #of sym %d, #of ofdm %d\n",
																				rsp->atsc3_plp_info.l1b_num_subframes,
																				rsp->atsc3_plp_info.l1b_pre_num_symbols,
																				rsp->atsc3_plp_info.l1b_num_ofdm_symbols);
			idx += SPRINTF(logbuf + idx, "\t""L1B       : reduce_carr %d\n",	rsp->atsc3_plp_info.l1b_reduce_carr);
			switch(rsp->atsc3_plp_info.l1b_sub_fft_size) {
			case DEMOD_ATSC3_PLP_INFO_SUBFRAME_FFT_SIZE_8K:					str1 = "8K";				break;
			case DEMOD_ATSC3_PLP_INFO_SUBFRAME_FFT_SIZE_16K:					str1 = "16K";				break;
			case DEMOD_ATSC3_PLP_INFO_SUBFRAME_FFT_SIZE_32K:					str1 = "32K";				break;
			default:															str1 = "RSVD";				break;
			}
			switch(rsp->atsc3_plp_info.l1b_sub_gi) {
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_GI_1_192:				str2 = "1 / 192";			break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_GI_2_384:				str2 = "2 / 384";			break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_GI_3_512:				str2 = "3 / 512";			break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_GI_4_768:				str2 = "4 / 768";			break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_GI_5_1024:			str2 = "5 / 1024";			break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_GI_6_1536:			str2 = "6 / 1536";			break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_GI_7_2048:			str2 = "7 / 2048";			break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_GI_8_2432:			str2 = "8 / 2432";			break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_GI_9_3072:			str2 = "9 / 3072";			break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_GI_10_3648:			str2 = "10 / 3648";			break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_GI_11_4096:			str2 = "11 / 4096";			break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_GI_12_4864:			str2 = "12 / 4864";			break;
			default:															str2 = "INV";				break;
			}
			idx += SPRINTF(logbuf + idx, "\t""L1B_SUB   : fft %s, gi %s\n",		str1, str2);

			switch(rsp->atsc3_plp_info.l1b_sub_scatt_pp) {
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_SCATT_PP_3_2:			str1 = "3_2";				break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_SCATT_PP_3_4:			str1 = "3_4";				break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_SCATT_PP_4_2:			str1 = "4_2";				break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_SCATT_PP_4_4:			str1 = "4_4";				break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_SCATT_PP_6_2:			str1 = "6_2";				break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_SCATT_PP_6_4:			str1 = "6_4";				break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_SCATT_PP_8_2:			str1 = "8_2";				break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_SCATT_PP_8_4:			str1 = "8_4";				break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_SCATT_PP_12_2:		str1 = "12_2";				break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_SCATT_PP_12_4:		str1 = "12_4";				break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_SCATT_PP_16_2:		str1 = "16_2";				break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_SCATT_PP_16_4:		str1 = "16_4";				break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_SCATT_PP_24_2:		str1 = "24_2";				break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_SCATT_PP_24_4:		str1 = "24_4";				break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_SCATT_PP_32_2:		str1 = "32_2";				break;
			case DEMOD_ATSC3_PLP_INFO_L1B_SUB_SCATT_PP_32_4:		str1 = "32_4";				break;
			default:															str1 = "INV";				break;
			break;
			}
			idx += SPRINTF(logbuf + idx, "\t""L1B_SUB   : spb %d, spp %s\n",	rsp->atsc3_plp_info.l1b_sub_scatt_pb,
																				str1);
			idx += SPRINTF(logbuf + idx, "\t""L1B_SUB   : first %s, last %s\n",	(rsp->atsc3_plp_info.l1b_sub_sbs_first == DEMOD_ATSC3_PLP_INFO_L1B_SUB_SBS_FIRST_SBS) ? "SBS" : "NO_SBS",
																				(rsp->atsc3_plp_info.l1b_sub_sbs_last == DEMOD_ATSC3_PLP_INFO_L1B_SUB_SBS_LAST_SBS) ? "SBS" : "NO_SBS");
			idx += SPRINTF(logbuf + idx, "\t""L1D       : mode %d, ap_mode %d, segment %d\n",
																				rsp->atsc3_plp_info.l1b_num_subframes,
																				rsp->atsc3_plp_info.l1b_pre_num_symbols,
																				rsp->atsc3_plp_info.l1b_num_ofdm_symbols);
			idx += SPRINTF(logbuf + idx, "\t""pre_str_m : %d\n",				rsp->atsc3_plp_info.pre_str_mode);
			idx += SPRINTF(logbuf + idx, "\t""frm_mod   : %d\n",				rsp->atsc3_plp_info.frm_mod);
			idx += SPRINTF(logbuf + idx, "\t""frm_len_i : %d\n",				rsp->atsc3_plp_info.frame_length_info);
			idx += SPRINTF(logbuf + idx, "\t""bsr       : %d\n",				rsp->atsc3_plp_info.bsr);
			idx += SPRINTF(logbuf + idx, "\t""easinfo   : %d\n",				rsp->atsc3_plp_info.easinfo);
			idx += SPRINTF(logbuf + idx, "\t""m2n       : %d\n",				rsp->atsc3_plp_info.m2n);

			{
				UINT32 frame_length_ms = 0;
				switch (rsp->atsc3_plp_info.bsr) {
				case 2:
					frame_length_ms = ((UINT64)144675926 * rsp->atsc3_plp_info.frame_length_info) / 1000000000000ULL;
					break;
				case 5:
					frame_length_ms = ((UINT64)124007937 * rsp->atsc3_plp_info.frame_length_info) / 1000000000000ULL;
					break;
				case 8:
					frame_length_ms = ((UINT64)108506944 * rsp->atsc3_plp_info.frame_length_info) / 1000000000000ULL;
					break;
				default:
					break;
				}
				idx += SPRINTF(logbuf + idx, "\t""frm_len   : %d ms\n",				frame_length_ms);
			}

			for (i = 0; i < DEMOD_ATSC3_PLP_DEC_MAX; i++) {
				if (rsp->atsc3_plp_info.plp[i].dec_en) {
					switch(rsp->atsc3_plp_info.plp[i].fec_type) {
					case DEMOD_ATSC3_PLP_INFO_PLP_FEC_TYPE_BCH_16K_LDPC:	str1 = "BCH_16K";		break;
					case DEMOD_ATSC3_PLP_INFO_PLP_FEC_TYPE_BCH_64K_LDPC:	str1 = "BCH_64K";		break;
					case DEMOD_ATSC3_PLP_INFO_PLP_FEC_TYPE_CRC_16K_LDPC:	str1 = "CRC_16K";		break;
					case DEMOD_ATSC3_PLP_INFO_PLP_FEC_TYPE_CRC_64K_LDPC:	str1 = "CRC_64K";		break;
					case DEMOD_ATSC3_PLP_INFO_PLP_FEC_TYPE_16K_LDPC:		str1 = "16K";			break;
					case DEMOD_ATSC3_PLP_INFO_PLP_FEC_TYPE_64K_LDPC:		str1 = "64K";			break;
					default:															str1 = "RSVD";			break;
					}

					str2 = DEMOD_L1_API_Coderate_Text(DEMOD_MODULATION_ATSC3, rsp->atsc3_plp_info.plp[i].cr);

					switch(rsp->atsc3_plp_info.plp[i].mod) {
					case DEMOD_ATSC3_PLP_INFO_PLP_MOD_QPSK:					str3 = "QPSK";			break;
					case DEMOD_ATSC3_PLP_INFO_PLP_MOD_16QAM_NUC:			str3 = "16QAM_NUC";		break;
					case DEMOD_ATSC3_PLP_INFO_PLP_MOD_64QAM_NUC:			str3 = "64QAM_NUC";		break;
					case DEMOD_ATSC3_PLP_INFO_PLP_MOD_256QAM_NUC:			str3 = "256QAM_NUC";	break;
					case DEMOD_ATSC3_PLP_INFO_PLP_MOD_1024QAM_NUC:			str3 = "1024QAM_NUC";	break;
					case DEMOD_ATSC3_PLP_INFO_PLP_MOD_4096QAM_NUC:			str3 = "4096QAM_NUC";	break;
					default:															str3 = "INV";			break;
					}

					idx += SPRINTF(logbuf + idx, "\t""#%d plp%-3d : dec_en %u, type %d, %s layer, ti %u\n", i,
																					rsp->atsc3_plp_info.plp[i].id,
																					rsp->atsc3_plp_info.plp[i].dec_en,
																					rsp->atsc3_plp_info.plp[i].type,
																					(rsp->atsc3_plp_info.plp[i].layer == 0) ? "core" : "enhanced",
																					rsp->atsc3_plp_info.plp[i].ti_mode);
					idx += SPRINTF(logbuf + idx, "\t""            fec %8s, cr %6s, mod %s\n", str1, str2, str3);

					// plp_info.Layer is L1D_plp_layer, 0: Core, 1: Enhanced
					if (rsp->atsc3_plp_info.plp[i].layer == 0) {
						switch(rsp->atsc3_plp_info.plp[i].ti_mode) {
						case DEMOD_ATSC3_PLP_INFO_PLP_TI_MODE_NO_TI_MODE:
							idx += SPRINTF(logbuf + idx, "\t""            NO_TI\n");
							break;
						case DEMOD_ATSC3_PLP_INFO_PLP_TI_MODE_CTI_MODE:
							switch(rsp->atsc3_plp_info.plp[i].cti.depth) {
							case DEMOD_ATSC3_PLP_INFO_L1D_PLP_CTI_DEPTH_512:		str1 = "512";				break;
							case DEMOD_ATSC3_PLP_INFO_L1D_PLP_CTI_DEPTH_724:		str1 = "724";				break;
							case DEMOD_ATSC3_PLP_INFO_L1D_PLP_CTI_DEPTH_887_1254:
								if (rsp->atsc3_plp_info.plp[i].mod == DEMOD_ATSC3_PLP_INFO_PLP_MOD_QPSK)
																								str1 = "1254";
								else
																								str1 = "887";
								break;
							case DEMOD_ATSC3_PLP_INFO_L1D_PLP_CTI_DEPTH_1024_1448:
								if (rsp->atsc3_plp_info.plp[i].mod == DEMOD_ATSC3_PLP_INFO_PLP_MOD_QPSK)
																								str1 = "1448";
								else
																								str1 = "1024";
								break;
							default:															str1 = "RSVD";				break;
							}
							idx += SPRINTF(logbuf + idx, "\t""            CTI, depth %s, start_row %u\n", str1, rsp->atsc3_plp_info.plp[i].cti.start_row);
						break;
						case DEMOD_ATSC3_PLP_INFO_PLP_TI_MODE_HTI_MODE:
							idx += SPRINTF(logbuf + idx, "\t""            HTI, inter_subf %u, #of ti_blocks %u, #of fec_blocks_max %u, cell_il %u\n",
																						rsp->atsc3_plp_info.plp[i].hti.inter_subframe,
																						rsp->atsc3_plp_info.plp[i].hti.num_ti_blocks,
																						rsp->atsc3_plp_info.plp[i].hti.num_fec_blocks_max,
																						rsp->atsc3_plp_info.plp[i].hti.cell_interleaver);
							break;
						default:
							idx += SPRINTF(logbuf + idx, "\t""            INV TI_MODE, %u\n", rsp->atsc3_plp_info.plp[i].ti_mode);
							break;
						}
					} else {
						idx += SPRINTF(logbuf + idx, "\t""            ldm inj_lv : %u\n", rsp->atsc3_plp_info.plp[i].ldm.injection_level);
					}

					idx += SPRINTF(logbuf + idx, "\t""   sbf%-3u : num plp %u, num ofdm %u, freq_ilv %u\n",
					//idx += SPRINTF(logbuf + idx, "\t""#SBF #%2d   : idx %u, #o plp %u, #o ofdm %u, f_ilv %u\n", i, 
																					rsp->atsc3_plp_info.sbf[i].number,
																					rsp->atsc3_plp_info.sbf[i].num_plp,
																					rsp->atsc3_plp_info.sbf[i].num_ofdm_symbols,
																					rsp->atsc3_plp_info.sbf[i].freq_ilv);
					idx += SPRINTF(logbuf + idx, "\t""            sbs %u,%u, spb %u, spp %u, gi %u, rc %u, fft %u\n", 
																					rsp->atsc3_plp_info.sbf[i].sbs_first,
																					rsp->atsc3_plp_info.sbf[i].sbs_last,
																					rsp->atsc3_plp_info.sbf[i].sp_boost,
																					rsp->atsc3_plp_info.sbf[i].sp_pattern,
																					rsp->atsc3_plp_info.sbf[i].gi,
																					rsp->atsc3_plp_info.sbf[i].reduce_carr,
																					rsp->atsc3_plp_info.sbf[i].fft_size);
				}
			}
			break;
#endif
#ifdef DEMOD_CMD_ATSC3_PLP_ID
		case DEMOD_CMD_ATSC3_PLP_ID_CODE: {
			UINT8 index = 0;
			UINT8 count = 0;

			idx += SPRINTF(logbuf + idx, "ATSC3_PLP_ID\n");
			for (index = 0; index <64; index++)
			{
				if((rsp->atsc3_plp_id.plp_id_flag >> index) & 0x0000000000000001)
				{
					count++;
					idx += SPRINTF(logbuf + idx, "\t""PLP #%2u, cti_mode %u, ldm_mode %u, lls_valid %u\n", index & 0x3f,
						(rsp->atsc3_plp_id.ti_mode >> index) & 0x01,
						(rsp->atsc3_plp_id.ldm_mode >> index) & 0x01,
						(rsp->atsc3_plp_id.lls_valid >> index) & 0x1);
				}
			}
			idx += SPRINTF(logbuf + idx, "\t""PLP count %d\n", count);
			break;
			}
#endif

#ifdef DEMOD_CMD_ISDBT_STATUS
		case DEMOD_CMD_ISDBT_STATUS_CODE:
			idx += SPRINTF(logbuf + idx, "ISDBT_STATUS\n");

			idx += SPRINTF(logbuf + idx, "\t""IF_AGC    : %u\n",				(rsp->isdbt_status.if_agc));
			idx += SPRINTF(logbuf + idx, "\t""SPECINV   : %s\n",				(rsp->isdbt_status.spInv == DEMOD_PROP_MODE_SPECINV_INVERSION) ? "Inverted" : "Normal");
			idx += SPRINTF(logbuf + idx, "\t""MSE_INFO  : %u\n",				(rsp->isdbt_status.mse_info));
			idx += SPRINTF(logbuf + idx, "\t""BER       : %u\n",				(rsp->isdbt_status.ber));
			idx += SPRINTF(logbuf + idx, "\t""CFO_VALUE : 0x%x\n",				(rsp->isdbt_status.cfo));
			idx += SPRINTF(logbuf + idx, "\t""SFO_VALUE : 0x%x\n",				(rsp->isdbt_status.sfo));

			idx += SPRINTF(logbuf + idx, "\t""FEC_LOCK  : %s\n",				(rsp->isdbt_status.lock_fec == DEMOD_LOCK_LOCKED) ? "Locked" : "UnLocked");
			idx += SPRINTF(logbuf + idx, "\t""CARR_LOCK : %s\n",				(rsp->isdbt_status.lock_carr == DEMOD_LOCK_LOCKED) ? "Locked" : "UnLocked");
			idx += SPRINTF(logbuf + idx, "\t""PKT ERROR : %u",					(rsp->isdbt_status.pe));
			break;
#endif

#ifdef DEMOD_CMD_ISDBT_TMCC_INFO
		case DEMOD_CMD_ISDBT_TMCC_INFO_CODE:
			idx += SPRINTF(logbuf + idx, "ISDBT_TMCC_INFO\n");

			switch(rsp->isdbt_tmcc_info.gi) {
			case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_1_32:						str1 =  "1 / 32";			break;
			case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_1_16:						str1 =  "1 / 16";			break;
			case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_1_8:						str1 =  "1 / 8";			break;
			case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_1_4:						str1 =  "1 / 4";			break;
			case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_1_128:					str1 =  "1 / 128";			break;
			case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_19_128:					str1 = "19 / 128";			break;
			case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_19_256:					str1 = "19 / 256";			break;
			case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_GI_1_64:						str1 =  "1 / 64";			break;
			default:															str1 = "RSVD";				break;
			}
			str2 = DEMOD_L1_API_FFT_Mode_Text(rsp->isdbt_tmcc_info.fft_mode);

			idx += SPRINTF(logbuf + idx, "\t""GI        : %s\n",				(str1));
			idx += SPRINTF(logbuf + idx, "\t""FFT       : %s\n",				(str2));

			str1 = DEMOD_L1_API_Constellation_Text(rsp->isdbt_tmcc_info.oqama);
			str2 = DEMOD_L1_API_Coderate_Text(DEMOD_MODULATION_ISDBT, rsp->isdbt_tmcc_info.ocra);

			switch(rsp->isdbt_tmcc_info.oila) {
			case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_0_0_0:					str4 = "0_0_0";				break;
			case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_4_2_1:					str4 = "4_2_1";				break;
			case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_8_4_2:					str4 = "8_4_2";				break;
			case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_16_8_4:					str4 = "16_8_4";			break;
			default:															str4 = "RSVD";				break;
			}

			idx += SPRINTF(logbuf + idx, "\t""LayerA QAM: CONSTEL %s, CR %3s, SEG %u, ilv %s\n",
																				str1, str2, rsp->isdbt_tmcc_info.onsega, str4);

			str1 = DEMOD_L1_API_Constellation_Text(rsp->isdbt_tmcc_info.oqamb);
			str2 = DEMOD_L1_API_Coderate_Text(DEMOD_MODULATION_ISDBT, rsp->isdbt_tmcc_info.ocrb);

			switch(rsp->isdbt_tmcc_info.oilb) {
			case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_0_0_0:					str4 = "0_0_0";				break;
			case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_4_2_1:					str4 = "4_2_1";				break;
			case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_8_4_2:					str4 = "8_4_2";				break;
			case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_16_8_4:					str4 = "16_8_4";			break;
			default:															str4 = "RSVD";				break;
			}

			idx += SPRINTF(logbuf + idx, "\t""LayerB QAM: CONSTEL %s, CR %3s, SEG %u, ilv %s\n",
																				(str1), (str2), (rsp->isdbt_tmcc_info.onsegb), (str4));

			str1 = DEMOD_L1_API_Constellation_Text(rsp->isdbt_tmcc_info.oqamc);
			str2 = DEMOD_L1_API_Coderate_Text(DEMOD_MODULATION_ISDBT, rsp->isdbt_tmcc_info.ocrc);

			switch(rsp->isdbt_tmcc_info.oilc) {
			case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_0_0_0:					str4 = "0_0_0";				break;
			case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_4_2_1:					str4 = "4_2_1";				break;
			case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_8_4_2:					str4 = "8_4_2";				break;
			case DEMOD_DD_ISDBT_TMCC_INFO_RESPONSE_IT_16_8_4:					str4 = "16_8_4";			break;
			default:															str4 = "RSVD";				break;
			}

			idx += SPRINTF(logbuf + idx, "\t""LayerC QAM: CONSTEL %s, CR %3s, SEG %u, ilv %s\n",
																				(str1), (str2), (rsp->isdbt_tmcc_info.onsegc), (str4));
			break;
#endif

#ifdef DEMOD_CMD_DVBS_STATUS
		case DEMOD_CMD_DVBS_STATUS_CODE:
			idx += SPRINTF(logbuf + idx, "DVBS_STATUS\n");

			idx += SPRINTF(logbuf + idx, "\t""IF_AGC    : %u\n",				(rsp->dvbs_status.if_agc));
			idx += SPRINTF(logbuf + idx, "\t""SPECINV   : %s\n",				(rsp->dvbs_status.spInv == DEMOD_PROP_MODE_SPECINV_INVERSION) ? "Inverted" : "Normal");
			idx += SPRINTF(logbuf + idx, "\t""MSE_INFO  : %u\n",				(rsp->dvbs_status.mse_info));
			idx += SPRINTF(logbuf + idx, "\t""BER       : %u\n",				(rsp->dvbs_status.ber));
			idx += SPRINTF(logbuf + idx, "\t""CFO_VALUE : 0x%x\n",				(rsp->dvbs_status.cfo));
			idx += SPRINTF(logbuf + idx, "\t""SFO_VALUE : 0x%x\n",				(rsp->dvbs_status.sfo));
			idx += SPRINTF(logbuf + idx, "\t""SYM_RATE  : %u KHz\n",			(rsp->dvbs_status.sym_rate));

			str1 = DEMOD_L1_API_Constellation_Text(rsp->dvbs_status.constellation);
			str2 = DEMOD_L1_API_Coderate_Text(DEMOD_MODULATION_DVBS, rsp->dvbs_status.cr);
			idx += SPRINTF(logbuf + idx, "\t""CONSTEL.. : %s\n",				str1);
			idx += SPRINTF(logbuf + idx, "\t""CODE RATE : %s\n",				str2);

			idx += SPRINTF(logbuf + idx, "\t""FEC_LOCK  : %s\n",				(rsp->dvbs_status.lock_fec == DEMOD_LOCK_LOCKED) ? "Locked" : "UnLocked");
			idx += SPRINTF(logbuf + idx, "\t""CARR_LOCK : %s\n",				(rsp->dvbs_status.lock_carr == DEMOD_LOCK_LOCKED) ? "Locked" : "UnLocked");
			idx += SPRINTF(logbuf + idx, "\t""PKT ERROR : %u",					(rsp->dvbs_status.pe));

			break;
#endif

#ifdef DEMOD_CMD_DVBS2_STATUS
		case DEMOD_CMD_DVBS2_STATUS_CODE:
			idx += SPRINTF(logbuf + idx, "DVBS2_STATUS\n");

			idx += SPRINTF(logbuf + idx, "\t""IF_AGC    : %u\n",				(rsp->dvbs2_status.if_agc));
			idx += SPRINTF(logbuf + idx, "\t""SPECINV   : %s\n",				(rsp->dvbs2_status.spInv == DEMOD_PROP_MODE_SPECINV_INVERSION) ? "Inverted" : "Normal");
			idx += SPRINTF(logbuf + idx, "\t""MSE_INFO  : %u\n",				(rsp->dvbs2_status.mse_info));
			idx += SPRINTF(logbuf + idx, "\t""BER       : %u\n",				(rsp->dvbs2_status.ber));
			idx += SPRINTF(logbuf + idx, "\t""CFO_VALUE : 0x%x\n",				(rsp->dvbs2_status.cfo));
			idx += SPRINTF(logbuf + idx, "\t""SFO_VALUE : 0x%x\n",				(rsp->dvbs2_status.sfo));
			idx += SPRINTF(logbuf + idx, "\t""SYM_RATE  : %u KHz\n",			(rsp->dvbs2_status.sym_rate));
			idx += SPRINTF(logbuf + idx, "\t""PP        : %u\n",				(rsp->dvbs2_status.pp));

			str1 = DEMOD_L1_API_Constellation_Text(rsp->dvbs_status.constellation);
			str2 = DEMOD_L1_API_Coderate_Text(DEMOD_MODULATION_DVBS2, rsp->dvbs_status.cr);
			idx += SPRINTF(logbuf + idx, "\t""CONSTEL.. : %s\n",				str1);
			idx += SPRINTF(logbuf + idx, "\t""CODE RATE : %s\n",				str2);

			idx += SPRINTF(logbuf + idx, "\t""FEC_LOCK  : %s\n",				(rsp->dvbs2_status.lock_fec == DEMOD_LOCK_LOCKED) ? "Locked" : "UnLocked");
			idx += SPRINTF(logbuf + idx, "\t""CARR_LOCK : %s\n",				(rsp->dvbs2_status.lock_carr == DEMOD_LOCK_LOCKED) ? "Locked" : "UnLocked");
			idx += SPRINTF(logbuf + idx, "\t""PKT ERROR : %u",					(rsp->dvbs2_status.pe));
			break;
#endif

#ifdef DEMOD_CMD_DVBT_STATUS
		case DEMOD_CMD_DVBT_STATUS_CODE:
			idx += SPRINTF(logbuf + idx, "DVBT_STATUS\n");

			idx += SPRINTF(logbuf + idx, "\t""IF_AGC    : %u\n",				(rsp->dvbt_status.if_agc));
			idx += SPRINTF(logbuf + idx, "\t""SPECINV   : %s\n",				(rsp->dvbt_status.spInv == DEMOD_PROP_MODE_SPECINV_INVERSION) ? "Inverted" : "Normal");
			idx += SPRINTF(logbuf + idx, "\t""MSE_INFO  : %u\n",				(rsp->dvbt_status.mse_info));
			idx += SPRINTF(logbuf + idx, "\t""BER       : %u\n",				(rsp->dvbt_status.ber));
			idx += SPRINTF(logbuf + idx, "\t""CFO_VALUE : 0x%x\n",				(rsp->dvbt_status.cfo));
			idx += SPRINTF(logbuf + idx, "\t""SFO_VALUE : 0x%x\n",				(rsp->dvbt_status.sfo));
			idx += SPRINTF(logbuf + idx, "\t""CELL_ID   : %u\n",				(rsp->dvbt_status.cell_id));

			if(rsp->dvbt_status.hierarchy_sel == DEMOD_DD_DVBT_STATUS_RESPONSE_HIERARCHY_SEL_HP) {
				str1 = "HP_CR";
				str2 = DEMOD_L1_API_Coderate_Text(DEMOD_MODULATION_DVBT, rsp->dvbt_status.hp_cr);
			} else {
				str1 = "LP_CR";
				str2 = DEMOD_L1_API_Coderate_Text(DEMOD_MODULATION_DVBT, rsp->dvbt_status.lp_cr);
			}
			idx += SPRINTF(logbuf + idx, "\t""HIERARCHY : %s %s\n",			str1, str2);

			str1 = DEMOD_L1_API_Constellation_Text(rsp->dvbt_status.constellation);
			str2 = DEMOD_L1_API_FFT_Mode_Text(rsp->dvbt_status.fft_mode);

			switch(rsp->dvbt_status.gi) {
			case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_32:							str3 =  "1 / 32";		break;
			case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_16:							str3 =  "1 / 16";		break;
			case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_8:							str3 =  "1 / 8";		break;
			case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_4:							str3 =  "1 / 4";		break;
			case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_128:						str3 =  "1 / 128";		break;
			case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_19_128:						str3 = "19 / 128";		break;
			case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_19_256:						str3 = "19 / 256";		break;
			case DEMOD_DD_DVBT_STATUS_RESPONSE_GI_1_64:							str3 =  "1 / 64";		break;
			default:															str3 = "RSVD";			break;
			}

			idx += SPRINTF(logbuf + idx, "\t""CONSTEL.. : %s\n",				str1);
			idx += SPRINTF(logbuf + idx, "\t""FFT       : %s\n",				str2);
			idx += SPRINTF(logbuf + idx, "\t""GI        : %s\n",				str3);

			idx += SPRINTF(logbuf + idx, "\t""FEC_LOCK  : %s\n",				(rsp->dvbt_status.lock_fec == DEMOD_LOCK_LOCKED) ? "Locked" : "UnLocked");
			idx += SPRINTF(logbuf + idx, "\t""CARR_LOCK : %s\n",				(rsp->dvbt_status.lock_carr == DEMOD_LOCK_LOCKED) ? "Locked" : "UnLocked");
			idx += SPRINTF(logbuf + idx, "\t""PKT ERROR : %u",					(rsp->dvbt_status.pe));
			break;
#endif

#ifdef DEMOD_CMD_DVBT2_STATUS
		case DEMOD_CMD_DVBT2_STATUS_CODE:
			idx += SPRINTF(logbuf + idx, "DVBT2_STATUS\n");

			idx += SPRINTF(logbuf + idx, "\t""IF_AGC    : %u\n",				(rsp->dvbt2_status.if_agc));
			idx += SPRINTF(logbuf + idx, "\t""SPECINV   : %s\n",				(rsp->dvbt2_status.spInv == DEMOD_PROP_MODE_SPECINV_INVERSION) ? "Inverted" : "Normal");
			idx += SPRINTF(logbuf + idx, "\t""MSE_INFO  : %u\n",				(rsp->dvbt2_status.mse_info));
			idx += SPRINTF(logbuf + idx, "\t""BER       : %u\n",				(rsp->dvbt2_status.ber));
			idx += SPRINTF(logbuf + idx, "\t""CFO_VALUE : 0x%x\n",				(rsp->dvbt2_status.cfo));
			idx += SPRINTF(logbuf + idx, "\t""SFO_VALUE : 0x%x\n",				(rsp->dvbt2_status.sfo));

			idx += SPRINTF(logbuf + idx, "\t""NUM_PLP   : 0x%x\n",				(rsp->dvbt2_status.num_plp));
			idx += SPRINTF(logbuf + idx, "\t""NUM_DPLP  : 0x%x\n",				(rsp->dvbt2_status.num_dplp));
			idx += SPRINTF(logbuf + idx, "\t""BW_EXT    : 0x%x\n",				(rsp->dvbt2_status.bw_ext));

			str1 = DEMOD_L1_API_Constellation_Text(rsp->dvbt2_status.constellation);
			str2 = DEMOD_L1_API_FFT_Mode_Text(rsp->dvbt2_status.fft_mode);
			str3 = DEMOD_L1_API_Coderate_Text(DEMOD_MODULATION_DVBT2, rsp->dvbt2_status.cr);
			idx += SPRINTF(logbuf + idx, "\t""CONSTEL.. : %s\n",				str1);
			idx += SPRINTF(logbuf + idx, "\t""FFT       : %s\n",				str2);
			idx += SPRINTF(logbuf + idx, "\t""CODE RATE : %s\n",				str3);

			switch(rsp->dvbt2_status.gi) {
			case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_32:						str2 =  "1 / 32";		break;
			case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_16:						str2 =  "1 / 16";		break;
			case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_8:							str2 =  "1 / 8";		break;
			case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_4:							str2 =  "1 / 4";		break;
			case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_128:						str2 =  "1 / 128";		break;
			case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_19_128:						str2 = "19 / 128";		break;
			case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_19_256:						str2 = "19 / 256";		break;
			case DEMOD_DD_DVBT2_STATUS_RESPONSE_GI_1_64:						str2 =  "1 / 64";		break;
			default:															str2 = "RSVD";			break;
			}

			idx += SPRINTF(logbuf + idx, "\t""GI        : %s\n",				str2);

			idx += SPRINTF(logbuf + idx, "\t""FEC_LOCK  : %s\n",				(rsp->dvbt2_status.lock_fec == DEMOD_LOCK_LOCKED) ? "Locked" : "UnLocked");
			idx += SPRINTF(logbuf + idx, "\t""CARR_LOCK : %s\n",				(rsp->dvbt2_status.lock_carr == DEMOD_LOCK_LOCKED) ? "Locked" : "UnLocked");
			idx += SPRINTF(logbuf + idx, "\t""PKT ERROR : %u",					(rsp->dvbt2_status.pe));
			break;
#endif

#ifdef DEMOD_CMD_DTMB_STATUS
		case DEMOD_CMD_DTMB_STATUS_CODE:
			idx += SPRINTF(logbuf + idx, "DTMB_STATUS\n");

			idx += SPRINTF(logbuf + idx, "\t""IF_AGC    : %u\n",				(rsp->dtmb_status.if_agc));
			idx += SPRINTF(logbuf + idx, "\t""SPECINV   : %s\n",				(rsp->dtmb_status.spInv == DEMOD_PROP_MODE_SPECINV_INVERSION) ? "Inverted" : "Normal");
			idx += SPRINTF(logbuf + idx, "\t""MSE_INFO  : %u\n",				(rsp->dtmb_status.mse_info));
			idx += SPRINTF(logbuf + idx, "\t""BER       : %u\n",				(rsp->dtmb_status.ber));
			idx += SPRINTF(logbuf + idx, "\t""CFO_VALUE : 0x%x\n",				(rsp->dtmb_status.cfo));
			idx += SPRINTF(logbuf + idx, "\t""SFO_VALUE : 0x%x\n",				(rsp->dtmb_status.sfo));

			idx += SPRINTF(logbuf + idx, "\t""FEC_LOCK  : %s\n",				(rsp->dtmb_status.lock_fec == DEMOD_LOCK_LOCKED) ? "Locked" : "UnLocked");
			idx += SPRINTF(logbuf + idx, "\t""CARR_LOCK : %s\n",				(rsp->dtmb_status.lock_carr == DEMOD_LOCK_LOCKED) ? "Locked" : "UnLocked");
			idx += SPRINTF(logbuf + idx, "\t""PKT ERROR : %u",					(rsp->dtmb_status.pe));
		default:
			break;
#endif
	}

	*pidx = idx;
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
	int i;
	i = 0;
	DEMOD_L1_CommandDump(rsp, cmd_code, sdbglog, &i);
	DEMOD_INFO("%s\n", sdbglog);

	return NO_DEMOD_ERROR;
}
