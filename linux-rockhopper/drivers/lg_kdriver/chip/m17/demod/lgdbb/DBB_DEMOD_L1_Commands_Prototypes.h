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
**  Name:DBB_DEMOD_Commands_Prototypes.h
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

#ifndef    _DBB_DEMOD_COMMANDS_PROTOTYPES_H_
#define    _DBB_DEMOD_COMMANDS_PROTOTYPES_H_

#include "DBB_DEMOD_L1_API.h"

extern UINT8 DEMOD_L1_Process (LX_DEMOD_L1_Context *api, UINT8 cmdByte, UINT8 *cmdByteBuffer, UINT8 rspByte, UINT8 * rspByteBuffer);

extern UINT8 DEMOD_L1_CurrentRspStatus(LX_DEMOD_L1_Context *api,UINT8 ptDataBuffer);

extern UINT8 DEMOD_L1_GetCts(LX_DEMOD_L1_Context *api, UINT8 cmdCode);

extern UINT8 DEMOD_L1_PollForRsp(LX_DEMOD_L1_Context *api, UINT8 nbBytes, UINT8 *pByteBuffer);

extern UINT8 DEMOD_L1_SetInt(LX_DEMOD_L1_Context *api);

#ifdef DEMOD_DD_RESTART_CMD
extern UINT8 DEMOD_L1_SET_DD_Restart(LX_DEMOD_L1_Context *api);
#endif /* DEMOD_DD_RESTART_CMD */

#ifdef DEMOD_DD_SET_REG_CMD
extern UINT8 DEMOD_L1_SET_DD_Reg(LX_DEMOD_L1_Context *api, UINT8 addressMsb, UINT8 addressLsb, UINT8 length, UINT32 data);
#endif /*DEMOD_DD_SET_REG_CMD */

#ifdef DEMOD_DD_SET_PROP_CMD
extern UINT8 DEMOD_L1_SET_DD_Prop(LX_DEMOD_L1_Context *api, UINT16 prop, UINT32 data);
#endif /* DEMOD_DD_SET_PROP_CMD */

#ifdef DEMOD_DD_SET_REPEAT_CMD
extern UINT8 DEMOD_L1_SET_DD_Repeat(LX_DEMOD_L0_Context *i2c, UINT8 rptEn);
#endif /* DEMOD_DD_SET_REPEAT_CMD */

#ifdef DEMOD_DD_SOFT_RESET_CMD
extern UINT8  DEMOD_L1_SET_DD_SoftRst(LX_DEMOD_L1_Context *api, UINT8 softrstb, UINT8 softrstsyncb, UINT8 softrsteq1b, UINT8 softrsteq2b, UINT8 softrstdiseqcb, UINT8 softrstfecb, UINT8 softrsttpifb);
#endif /* DEMOD_DD_SOFT_RESET_CMD */

#ifdef DEMOD_DD_SELFRST_CMD
extern UINT8  DEMOD_L1_SET_DD_SelfRst(LX_DEMOD_L1_Context *api, UINT8  rst_arg, UINT16 rst_time1, UINT16 rst_time2, UINT16 rst_time3, UINT16 rst_time4, UINT8 rst_cnt);
#endif /* DEMOD_DD_SELFRST_CMD */

#ifdef DEMOD_DD_GET_REG_CMD
extern UINT8 DEMOD_L1_GET_DD_Reg(LX_DEMOD_L1_Context *api, UINT8 addressMsb, UINT8 addressLsb, UINT8 length);
extern UINT8 DEMOD_L1_GET_DD_Reg_Map(LX_DEMOD_L1_Context *api,  UINT8 addressMsb, UINT8 addressLsb, UINT8 length, UINT8* rspByteBuffer);
#endif /* DEMOD_DD_GET_REG_CMD */

#ifdef DEMOD_DD_GET_PROP_CMD
extern UINT8 DEMOD_L1_GET_DD_Prop(LX_DEMOD_L1_Context *api, UINT16 prop);
#endif /* DEMOD_DD_GET_PROP_CMD */

#ifdef DEMOD_DD_STATUS_CMD
extern UINT8  DEMOD_L1_GET_DD_Status(LX_DEMOD_L1_Context *api);
#endif /* DEMOD_DD_STATUS_CMD */

#ifdef DEMOD_DD_POWER_SAVE_CMD
extern UINT8  DEMOD_L1_SET_DD_Power_Save(LX_DEMOD_L1_Context *api, UINT8 power_save);
#endif /* DEMOD_DD_POWER_SAVE_CMD */

#ifdef DEMOD_DD_RESTART_CMD
extern UINT8  DEMOD_L1_SET_DD_Restart(LX_DEMOD_L1_Context *api);
#endif /* DEMOD_DD_RESTART_CMD */

#ifdef DEMOD_DD_ATSC3_PLP_SELECT_CMD
extern UINT8  DEMOD_L1_SET_DD_ATSC3_PLP_Select(LX_DEMOD_L1_Context *api,  UINT8 plp_id, UINT8   plp_id_sel_mode);
#endif /* DEMOD_DD_ATSC3_PLP_SELECT_CMD */

#ifdef DEMOD_DD_VSB_STATUS_CMD
extern UINT8  DEMOD_L1_GET_DD_VSB_Status(LX_DEMOD_L1_Context *api);
#endif /* DEMOD_DD_VSB_STATUS_CMD */

#ifdef DEMOD_DD_QAM_STATUS_CMD
extern UINT8  DEMOD_L1_GET_DD_QAM_Status(LX_DEMOD_L1_Context *api);
#endif /* DEMOD_DD_QAM_STATUS_CMD */

#ifdef DEMOD_DD_ATSC3_STATUS_CMD
extern UINT8  DEMOD_L1_GET_DD_ATSC3_Status(LX_DEMOD_L1_Context *api);
#endif /* DEMOD_DD_ATSC3_STATUS_CMD */

#ifdef DEMOD_DD_GET_PART_INFO_CMD
extern UINT8  DEMOD_L1_GET_DD_PartInfo(LX_DEMOD_L1_Context *api);
#endif /* DEMOD_DD_GET_PART_INFO_CMD */

#ifdef DEMOD_DD_ATSC3_PLP_ID_CMD
extern UINT8  DEMOD_L1_GET_DD_ATSC3_PLP_ID(LX_DEMOD_L1_Context *api, UINT8 index);
#endif /* DEMOD_L1_GET_DD_ATSC3_PLP_ID */

#ifdef DEMOD_DD_ATSC3_PLP_INFO_CMD
extern UINT8  DEMOD_L1_GET_DD_ATSC3_PLP_Info(LX_DEMOD_L1_Context *api, UINT8 index);
#endif /* DEMOD_L1_GET_DD_ATSC3_PLP_Info */

#ifdef DEMOD_DD_SET_TUNE_CMD
extern UINT8  DEMOD_L1_SET_DD_Tune(LX_DEMOD_L1_Context *api);
#endif /* DEMOD_DD_SET_TUNE_CMD */

#ifdef DEMOD_DD_LOCKTIME_CMD
extern UINT8 DEMOD_L1_GET_DD_LOCKTIME(LX_DEMOD_L1_Context *api);
#endif /* DEMOD_DD_LOCKTIME_CMD */

extern UINT8   DEMOD_L1_SendCommand2(LX_DEMOD_L1_Context *api, unsigned int cmd_code);

extern UINT8  DEMOD_L1_CommandText          (LX_DEMOD_L1_CmdReplyObj   *rsp, UINT32 cmd_code);


#ifndef LG3307_API


/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/***************ISDBT / DVBT/ DVBT2 / DVBS / DVBS2/DVBC/ DVBC2/  DEBUG*********/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/


#ifdef DEMOD_DD_DVBT2_PLP_SELECT_CMD
extern UINT8  DEMOD_L1_SET_DD_DVBT2_PLP_Select(LX_DEMOD_L1_Context *api,  UINT8 plp_id, UINT8   plp_id_sel_mode);
#endif /* DEMOD_DD_DVBT2_PLP_SELECT_CMD */

#ifdef DEMOD_DD_GET_DVBT2_PLP_ID_CMD
extern UINT8  DEMOD_L1_GET_DD_DVBT2_PLP_ID(LX_DEMOD_L1_Context *api, UINT8 index);
#endif

#ifdef DEMOD_DD_DVBC_SRD_CMD
extern UINT8  DEMOD_L1_SET_DD_SymbolRate_Detect(LX_DEMOD_L1_Context *api, UINT8 auto_en, UINT16 sym_rate);
#endif /* DEMOD_DD_DVBC_SRD_CMD */

#ifdef DEMOD_DD_DVBC2_STARTFREQUENCY_CMD
extern UINT8  DEMOD_L1_SET_DD_DVBC2_StartFrequency(LX_DEMOD_L1_Context *api, UINT32 freq);
#endif /* DEMOD_DD_DVBC2_STARTFREQUENCY_CMD */

#ifdef DEMOD_DD_DVBC2_PLP_SELECT_CMD
extern UINT8  DEMOD_L1_SET_DD_DVBC2_PLP_Select(LX_DEMOD_L1_Context *api,  UINT8 plp_id, UINT8 plp_id_mode, UINT8 ds_id);
#endif /* DEMOD_DD_DVBC2_PLP_SELECT_CMD */

#ifdef DEMOD_DD_GET_DD_SIGSRCH_NUM_CMD
extern UINT8  DEMOD_L1_GET_DD_SIGSRCH_NUM(LX_DEMOD_L1_Context *api);
#endif /* DEMOD_DD_GET_DD_SIGSRCH_NUM_CMD */

#ifdef DEMOD_DD_GET_DD_SIGSRCH_INFO_CMD
extern UINT8  DEMOD_L1_GET_DD_SIGSRCH_INFO(LX_DEMOD_L1_Context *api);
#endif /* DEMOD_DD_GET_DD_SIGSRCH_INFO_CMD */

#ifdef DEMOD_DD_DISEQC_SEND_CMD
extern UINT8  DEMOD_L1_SET_DD_DISEQC_Send(LX_DEMOD_L1_Context *api,
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
												UINT8 send_data2 );
#endif /* DEMOD_DD_DISEQC_SEND_CMD */

#ifdef DEMOD_DD_DVBS_OPERATING_MODE_CMD
extern UINT8  DEMOD_L1_SET_DD_DVBS_Blind_Scan_Mode(	LX_DEMOD_L1_Context *api, UINT8 opmSel, UINT32 symbolRate_Khz, UINT32 tuneFreq_Khz);
#endif /* DEMOD_DD_DVBS_OPERATING_MODE_CMD */

#ifdef DEMOD_DD_ISDBT_BASEADDR_AXI_CMD
UINT8  DEMOD_L1_SET_DD_ISDBT_BASEADDR_AXI(LX_DEMOD_L1_Context *api, UINT32 baseAddr);
#endif /* DEMOD_DD_ISDBT_BASEADDR_AXI_CMD */

#ifdef DEMOD_DD_DTMB_BASEADDR_AXI_CMD
UINT8  DEMOD_L1_SET_DD_DTMB_BASEADDR_AXI(LX_DEMOD_L1_Context *api, UINT32 baseAddr);
#endif /* DEMOD_DD_DTMB_BASEADDR_AXI_CMD */

#ifdef DEMOD_DD_DVBT2_STATUS_CMD
extern UINT8  DEMOD_L1_GET_DD_DVBT2_Status(LX_DEMOD_L1_Context *api);
#endif /* DEMOD_DD_DVBT2_STATUS_CMD */

#ifdef DEMOD_DD_DVBT_STATUS_CMD
extern UINT8  DEMOD_L1_GET_DD_DVBT_Status(LX_DEMOD_L1_Context *api);
#endif /* DEMOD_DD_DVBT_STATUS_CMD */

#ifdef DEMOD_DD_ISDBT_STATUS_CMD
extern UINT8  DEMOD_L1_GET_DD_ISDBT_Status(LX_DEMOD_L1_Context *api);
#endif /* DEMOD_DD_ISDBT_STATUS_CMD */

#ifdef DEMOD_DD_ISDBT_TMCC_INFO_CMD
extern UINT8  DEMOD_L1_GET_DD_ISDBT_TMCC_Info(LX_DEMOD_L1_Context *api);
#endif /* DEMOD_DD_ISDBT_TMCC_INFO_CMD */

#ifdef DEMOD_DD_DVBC_STATUS_CMD
extern UINT8  DEMOD_L1_GET_DD_DVBC_Status(LX_DEMOD_L1_Context *api);
#endif /* DEMOD_DD_DVBC_STATUS_CMD */

#ifdef DEMOD_DD_DVBC2_STATUS_CMD
extern UINT8  DEMOD_L1_GET_DD_DVBC2_Status(LX_DEMOD_L1_Context *api);
#endif /* DEMOD_DD_DVBC2_STATUS_CMD */

#ifdef DEMOD_DD_DISEQC_STATUS_CMD
extern UINT8  DEMOD_L1_GET_DD_DISEQC_Status(LX_DEMOD_L1_Context *api);
#endif /* DEMOD_DD_DISEQC_STATUS_CMD */

#ifdef DEMOD_DD_DVBS_STATUS_CMD
extern UINT8  DEMOD_L1_GET_DD_DVBS_Status(LX_DEMOD_L1_Context *api);
#endif /* DEMOD_DD_DVBS_STATUS_CMD */

#ifdef DEMOD_DD_DVBS2_STATUS_CMD
extern UINT8  DEMOD_L1_GET_DD_DVBS2_Status(LX_DEMOD_L1_Context *api);
#endif /* DEMOD_DD_DVBS2_STATUS_CMD */

#ifdef DEMOD_DD_BLIND_STATUS_CMD
extern UINT8  DEMOD_L1_GET_DD_BLIND_Status(LX_DEMOD_L1_Context *api);
#endif /* DEMOD_DD_BLIND_STATUS_CMD */

#ifdef DEMOD_DD_BLIND_INIT_CMD
extern UINT8  DEMOD_L1_GET_DD_BLIND_Init(LX_DEMOD_L1_Context *api, UINT32 startFreq, UINT32 endFreq);
#endif /* DEMOD_DD_BLIND_INIT_CMD */

#ifdef DEMOD_DD_BLIND_FOUNDINFO_CMD
extern UINT8  DEMOD_L1_GET_DD_BLIND_FoundInfo(LX_DEMOD_L1_Context *api);
#endif /* DEMOD_DD_BLIND_INIT_CMD */

#ifdef DEMOD_DD_BLIND_END_CMD
extern UINT8  DEMOD_L1_GET_DD_BLIND_End(LX_DEMOD_L1_Context *api);
#endif /* DEMOD_DD_BLIND_END_CMD */

#ifdef DEMOD_DD_DVBT2_BASEADDR_AXI_CMD
UINT8  DEMOD_L1_SET_DD_DVBT2_BASEADDR_AXI(LX_DEMOD_L1_Context *api, UINT32 baseAddr1, UINT32 baseAddr2);
#endif /* DEMOD_DD_DVBT2_BASEADDR_AXI_CMD */

#ifdef DEMOD_DD_DVB_BASEADDR_AXI_CMD
UINT8  DEMOD_L1_SET_DD_DVB_BASEADDR_AXI(LX_DEMOD_L1_Context *api, UINT32 baseAddr1, UINT32 baseAddr2, UINT32 baseAddr3);
#endif /* DEMOD_DD_DVB_BASEADDR_AXI_CMD */

#ifdef DEMOD_DD_DTMB_STATUS_CMD
extern UINT8  DEMOD_L1_GET_DD_DTMB_Status(LX_DEMOD_L1_Context *api);
#endif /* DEMOD_DD_DTMB_STATUS_CMD */

#endif
#endif /* _DBB_DEMOD_COMMANDS_PROTOTYPES_H_ */














