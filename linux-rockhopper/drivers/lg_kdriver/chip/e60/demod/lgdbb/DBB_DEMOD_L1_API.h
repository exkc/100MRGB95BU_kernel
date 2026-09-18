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
**  Name:DBB_DEMOD_L1_API.h
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

#ifndef    _DBB_DEMOD_L1_API_H_
#define    _DBB_DEMOD_L1_API_H_

#include "DBB_DEMOD_L0_API.h"
#include "DBB_DEMOD_L0_Regmap.h"
#include "DBB_DEMOD_L0_CBUF.h"
#include "DBB_DEMOD_L0_CBUF_RAM.h"

#include "DBB_DEMOD_L1_IPC.h"

#define  DEMOD_CLOCK_12MHZ	12000
#define  DEMOD_CLOCK_15P5MHZ	15500
#define  DEMOD_CLOCK_24MHZ	24000
#define  DEMOD_CLOCK_96MHZ	96000
#define  DEMOD_CLOCK_124MHZ	124000

typedef enum {
	DEMOD_FW_TYPE_INV	= 0,
	DEMOD_FW_TYPE_TER	= 1,
	DEMOD_FW_TYPE_SAT	= 2,
	DEMOD_FW_TYPE_DDR	= 3,
} demod_fw_type;

typedef enum {
	DEMOD_FW_DEBUG_NONE	= 0,
	DEMOD_FW_DEBUG_IPC	= 1,
	DEMOD_FW_DEBUG_UART	= 2,
	DEMOD_FW_DEBUG_ALL	= 3,
} demod_fw_debug;

typedef enum {
	DEMOD_FW_LOGLV_NONE	= 0,
	DEMOD_FW_LOGLV_ERROR	= 1,
	DEMOD_FW_LOGLV_PRINT	= 2,
	DEMOD_FW_LOGLV_DEFAULT	= 3,
	DEMOD_FW_LOGLV_DEBUG	= 4,
	DEMOD_FW_LOGLV_ALL	= 7,
} demod_fw_loglevel;

typedef enum {
	DEMOD_FW_STATE_INIT	= -1,
	DEMOD_FW_STATE_STOP	= 0,
	DEMOD_FW_STATE_START	= 1,
	DEMOD_FW_STATE_RUN	= 2,
	DEMOD_FW_STATE_TIMEOUT = 3,
	DEMOD_FW_STATE_RESET = 4,
	DEMOD_FW_STATE_FAULT = 5,
} demod_fw_state;

typedef struct
{
	LX_DEMOD_L0_Context *		chip;
	LX_DEMOD_L1_IPC *		ipc;
	LX_DEMOD_L1_CmdObj *		cmd;
	LX_DEMOD_L1_CmdReplyObj *	rsp;
	LX_DEMOD_L1_PropObj *		prop;
	LX_DEMOD_L1_PropObj *		propShadow;
	LX_DEMOD_L1_CommonReplayObj *	status;
	UINT8 				bIsStandby;		//lgit
	UINT8				standard;
	UINT8				media;
	UINT8				propertyWriteMode;	// Selection of DOWNLOAD_ALWAYS/DOWNLOAD_ON_CHANGE

//	LX_DEMOD_FW_STRUCT * 		fwiram;
//	LX_DEMOD_FW_STRUCT * 		fwdram;

	UINT32				cmd_req_cnt;
	UINT32				cmd_req_err_cnt;
	UINT32				cmd_req_out_cnt;
	UINT32				cmd_req_val_cnt;
	UINT32				cmd_req_inv_cnt;
	UINT32				cmd_req_ret_cnt;

	UINT32				cmd_res_cnt;
	UINT32				cmd_res_err_cnt;
	UINT32				cmd_res_out_cnt;
	UINT32				cmd_res_val_cnt;
	UINT32				cmd_res_inv_cnt;
	UINT32				cmd_res_skp_cnt;

	UINT32				fw_load_cnt;
	UINT32				fw_start_cnt;
	demod_fw_state		fw_state;
	volatile UINT8		fw_error;		//emergency reset
	UINT32				fw_ver;
	UINT32				fw_date;

	UINT8				last_plp0;
	UINT8				last_plp1;
	UINT8				last_plp2;
	UINT8				last_plp3;
} LX_DEMOD_L1_Context;

int DEMOD_L1_API_Init (LX_DEMOD_L1_Context * core, UINT32 addr);

//int DEMOD_L1_API_SelectFirmware (LX_DEMOD_L1_Context * core, LX_DEMOD_FW_STRUCT * iram, LX_DEMOD_FW_STRUCT * dram);

int DEMOD_L1_API_Patch_I (LX_DEMOD_L1_Context * core, UINT16 addr, UINT32 iNbBytes, UINT8 * pucDataBuffer);
int DEMOD_L1_API_Patch_D (LX_DEMOD_L1_Context * core, UINT16 addr, UINT32 iNbBytes, UINT8 * pucDataBuffer);
int DEMOD_L1_API_LoadFirmware_IRAM (LX_DEMOD_L1_Context * core, LX_DEMOD_FW_STRUCT fw_table[], UINT8 nbLines);
int DEMOD_L1_API_LoadFirmware_DRAM (LX_DEMOD_L1_Context * core, LX_DEMOD_FW_STRUCT fw_table[], UINT8 nbLines);
int DEMOD_L1_API_LoadFirmware_EXT (LX_DEMOD_L1_Context * core, LX_DEMOD_FW_STRUCT * fw_table);

int DEMOD_L1_API_LoadFirmware_MEM (LX_DEMOD_L1_Context * core, UINT32 baseAddr);

int DEMOD_L1_API_Debug (LX_DEMOD_L1_Context * core, char * dbglog);
int DEMOD_L1_API_Status (LX_DEMOD_L1_Context * core, char * dbglog);
int DEMOD_L1_API_Dump (LX_DEMOD_L1_Context * core, char * dbglog);

int DEMOD_L1_API_IsReady (LX_DEMOD_L1_Context * core);
int DEMOD_L1_API_SetFrequency (LX_DEMOD_L1_Context * core, UINT32 fw_clk, UINT32 adc_clk);
int DEMOD_L1_API_SetDebug (LX_DEMOD_L1_Context * core, demod_fw_debug mode, demod_fw_loglevel loglevel);

int DEMOD_L1_API_FinishFirmware (LX_DEMOD_L1_Context * core);
int DEMOD_L1_API_StopFirmware (LX_DEMOD_L1_Context * core);
int DEMOD_L1_API_InitFirmware (LX_DEMOD_L1_Context * core, UINT32 fw_clk, UINT32 adc_clk);
int DEMOD_L1_API_InitFirmware_DDR (LX_DEMOD_L1_Context * core, UINT32 fw_clk, UINT32 adc_clk);
int DEMOD_L1_API_StartFirmware (LX_DEMOD_L1_Context * core);

int DEMOD_L1_API_SetTrace (LX_DEMOD_L1_Context * core, UINT32 enable);
int DEMOD_L1_API_GetTrace (LX_DEMOD_L1_Context * core, UINT32 * ptrace, UINT32 *pdata, UINT32 *pstate);

char * DEMOD_L1_API_Error_Text (int error_code);
char * DEMOD_L1_API_StandardName (UINT8  standard);

int DEMOD_L1_API_BaseAddr_AXI (LX_DEMOD_L1_Context * core, UINT32 baseAddr);
int DEMOD_L1_API_Emergency_Alarm (LX_DEMOD_L1_Context * core, UINT8 *eAlarm);
int DEMOD_L1_API_DVBT2_BaseAddr_AXI (LX_DEMOD_L1_Context * core, UINT32 baseAddr1, UINT32 baseAddr2);
int DEMOD_L1_API_DVB_BaseAddr_AXI (LX_DEMOD_L1_Context * core, UINT32 baseAddr1, UINT32 baseAddr2, UINT32 baseAddr3);
int DEMOD_L1_API_DTMB_BaseAddr_AXI (LX_DEMOD_L1_Context * core, UINT32 baseAddr);

#endif //_DBB_DEMOD_L1_API_H_ //

