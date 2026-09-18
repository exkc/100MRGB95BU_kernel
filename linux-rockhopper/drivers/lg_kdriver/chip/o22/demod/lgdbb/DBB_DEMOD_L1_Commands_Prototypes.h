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

int DEMOD_L1_Process_Dump(LX_DEMOD_L1_Context * core, char * dbglog);

int DEMOD_L1_CurrentRspStatus (LX_DEMOD_L1_Context * core, UINT8 ptDataBuffer);

int DEMOD_L1_GetCts (LX_DEMOD_L1_Context * core, UINT8 cmdCode);

int DEMOD_L1_PollForRsp (LX_DEMOD_L1_Context * core, UINT8 nbBytes, UINT8 * pByteBuffer);

int DEMOD_L1_SetInt (LX_DEMOD_L1_Context * core);

#ifdef DEMOD_CMD_RESTART
int DEMOD_L1_SET_DD_Restart (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_CMD_RESTART */

#ifdef DEMOD_CMD_SET_REG
int DEMOD_L1_SET_DD_Reg (LX_DEMOD_L1_Context * core, UINT8 addressMsb, UINT8 addressLsb, UINT8 length, UINT32 data);
int DEMOD_L1_SET_DD_Reg_MAP (LX_DEMOD_L1_Context *api, UINT8 addressMsb, UINT8 addressLsb, UINT8 length, UINT8 *wrData);

#endif /*DEMOD_CMD_SET_REG */

#ifdef DEMOD_CMD_SET_PROP
int DEMOD_L1_SET_DD_Prop (LX_DEMOD_L1_Context * core, UINT16 prop, UINT32 data);
#endif /* DEMOD_CMD_SET_PROP */

#ifdef DEMOD_CMD_SET_REPEAT
int DEMOD_L1_SET_DD_Repeat (LX_DEMOD_L0_Context * chip, UINT8 rptEn);
#endif /* DEMOD_CMD_SET_REPEAT */

#ifdef DEMOD_CMD_SOFT_RESET
int DEMOD_L1_SET_DD_SoftRst (LX_DEMOD_L1_Context * core, UINT8 softrstb, UINT8 softrstsyncb, UINT8 softrsteq1b, UINT8 softrsteq2b, UINT8 softrstdiseqcb, UINT8 softrstfecb, UINT8 softrsttpifb);
#endif /* DEMOD_CMD_SOFT_RESET */

#ifdef DEMOD_CMD_SET_SELF_RESET_PARAM
int DEMOD_L1_SET_DD_SelfRst (LX_DEMOD_L1_Context * core, UINT8  rst_arg, UINT16 rst_time1, UINT16 rst_time2, UINT16 rst_time3, UINT16 rst_time4, UINT8 rst_cnt, UINT16 plp0_thd, UINT16 plp1_thd, UINT16 plp2_thd, UINT16 plp3_thd);
#endif /* DEMOD_CMD_SET_SELF_RESET_PARAM */

#ifdef DEMOD_CMD_GET_REG
int DEMOD_L1_GET_DD_Reg (LX_DEMOD_L1_Context * core, UINT8 addressMsb, UINT8 addressLsb, UINT8 length);
int DEMOD_L1_GET_DD_Reg_Map (LX_DEMOD_L1_Context * core,  UINT8 addressMsb, UINT8 addressLsb, UINT16 length, UINT8 * rspByteBuffer);
#endif /* DEMOD_CMD_GET_REG */

#ifdef DEMOD_CMD_GET_PROP
int DEMOD_L1_GET_DD_Prop (LX_DEMOD_L1_Context * core, UINT16 prop);
#endif /* DEMOD_CMD_GET_PROP */

#ifdef DEMOD_CMD_STATUS
int DEMOD_L1_GET_DD_Status (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_CMD_STATUS */

#ifdef DEMOD_CMD_TSCLK_STATUS
int DEMOD_L1_GET_DD_TSCLK_Status (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_CMD_TSCLK_STATUS */

#ifdef DEMOD_CMD_POWER_SAVE
int DEMOD_L1_SET_DD_Power_Save (LX_DEMOD_L1_Context * core, UINT8 power_save);
#endif /* DEMOD_CMD_POWER_SAVE */

#ifdef DEMOD_CMD_RESTART
int DEMOD_L1_SET_DD_Restart (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_CMD_RESTART */

#ifdef DEMOD_CMD_ATSC3_PLP_SELECT
int DEMOD_L1_SET_DD_ATSC3_PLP_Select (LX_DEMOD_L1_Context * core,  UINT8 plp0_id,  UINT8 plp1_id,  UINT8 plp2_id,  UINT8 plp3_id);
#endif /* DEMOD_CMD_ATSC3_PLP_SELECT */

#ifdef DEMOD_CMD_VSB_STATUS
int DEMOD_L1_GET_DD_VSB_Status (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_CMD_VSB_STATUS */

#ifdef DEMOD_CMD_QAM_STATUS
int DEMOD_L1_GET_DD_QAM_Status (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_CMD_QAM_STATUS */

#ifdef DEMOD_CMD_ATSC3_STATUS
int DEMOD_L1_GET_DD_ATSC3_Status (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_CMD_ATSC3_STATUS */

#ifdef DEMOD_CMD_GET_PART_INFO
int DEMOD_L1_GET_DD_PartInfo (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_CMD_GET_PART_INFO */

#ifdef DEMOD_CMD_ATSC3_PLP_ID
int DEMOD_L1_GET_DD_ATSC3_PLP_ID (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_L1_GET_DD_ATSC3_PLP_ID */

#ifdef DEMOD_CMD_ATSC3_PLP_INFO
int DEMOD_L1_GET_DD_ATSC3_PLP_Info (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_L1_GET_DD_ATSC3_PLP_Info */

#ifdef DEMOD_CMD_ATSC3_SET_BASEADDR_AXI
int DEMOD_L1_SET_DD_ATSC3_BASEADDR_AXI (LX_DEMOD_L1_Context * core, UINT32 baseAddr);
#endif /* DEMOD_CMD_ATSC3_SET_BASEADDR_AXI */

#ifdef DEMOD_CMD_SET_TUNE
int DEMOD_L1_SET_DD_Tune (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_CMD_SET_TUNE */

#ifdef DEMOD_CMD_LOCKTIME
int DEMOD_L1_GET_DD_LOCKTIME (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_CMD_LOCKTIME */

//int DEMOD_L1_SendCommand2 (LX_DEMOD_L1_Context * core, UINT32 cmd_code);

int DEMOD_L1_CommandDump (LX_DEMOD_L1_CmdReplyObj *rsp, UINT32 cmd_code, char *logbuf, int *pidx);

int DEMOD_L1_CommandText (LX_DEMOD_L1_CmdReplyObj * rsp, UINT32 cmd_code);



/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/***************ISDBT / DVBT/ DVBT2 / DVBS / DVBS2/DVBC/ DVBC2/  DEBUG*********/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/

#ifdef DEMOD_CMD_DVBT2_PLP_SELECT
int DEMOD_L1_SET_DD_DVBT2_PLP_Select (LX_DEMOD_L1_Context * core,  UINT8 plp_id, UINT8   plp_id_sel_mode);
#endif /* DEMOD_CMD_DVBT2_PLP_SELECT */

#ifdef DEMOD_CMD_GET_DVBT2_PLP_ID
int DEMOD_L1_GET_DD_DVBT2_PLP_ID (LX_DEMOD_L1_Context * core, UINT8 index);
#endif

#ifdef DEMOD_CMD_DVBC_SRD
int DEMOD_L1_SET_DD_SymbolRate_Detect (LX_DEMOD_L1_Context * core, UINT8 auto_en, UINT16 sym_rate);
#endif /* DEMOD_CMD_DVBC_SRD */

#ifdef DEMOD_CMD_DVBC2_STARTFREQUENCY
int DEMOD_L1_SET_DD_DVBC2_StartFrequency (LX_DEMOD_L1_Context * core, UINT32 freq);
#endif /* DEMOD_CMD_DVBC2_STARTFREQUENCY */

#ifdef DEMOD_CMD_DVBC2_PLP_SELECT
int DEMOD_L1_SET_DD_DVBC2_PLP_Select (LX_DEMOD_L1_Context * core,  UINT8 plp_id, UINT8 plp_id_mode, UINT8 ds_id);
#endif /* DEMOD_CMD_DVBC2_PLP_SELECT */

#ifdef DEMOD_CMD_GET_SIGSRCH_NUM
int DEMOD_L1_GET_DD_SIGSRCH_NUM (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_CMD_GET_SIGSRCH_NUM */

#ifdef DEMOD_CMD_GET_SIGSRCH_INFO
int DEMOD_L1_GET_DD_SIGSRCH_INFO (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_CMD_GET_SIGSRCH_INFO */

#ifdef DEMOD_CMD_DISEQC_SEND
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
							UINT8 send_data2 );
#endif /* DEMOD_CMD_DISEQC_SEND */

#ifdef DEMOD_CMD_DVBS_OPERATING_MODE
int DEMOD_L1_SET_DD_DVBS_Blind_Scan_Mode (LX_DEMOD_L1_Context * core, UINT8 opmSel, UINT32 symbolRate_Khz, UINT32 tuneFreq_Khz);
#endif /* DEMOD_CMD_DVBS_OPERATING_MODE */

#ifdef DEMOD_CMD_SET_ISDBT_BASEADDR_AXI
int DEMOD_L1_SET_DD_ISDBT_BASEADDR_AXI (LX_DEMOD_L1_Context * core, UINT32 baseAddr);
#endif /* DEMOD_CMD_SET_ISDBT_BASEADDR_AXI */

#ifdef DEMOD_CMD_SET_DTMB_BASEADDR_AXI
int DEMOD_L1_SET_DD_DTMB_BASEADDR_AXI (LX_DEMOD_L1_Context * core, UINT32 baseAddr);
#endif /* DEMOD_CMD_SET_DTMB_BASEADDR_AXI */

#ifdef DEMOD_CMD_DVBT2_STATUS
int DEMOD_L1_GET_DD_DVBT2_Status (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_CMD_DVBT2_STATUS */

#ifdef DEMOD_CMD_DVBT_STATUS
int DEMOD_L1_GET_DD_DVBT_Status (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_CMD_DVBT_STATUS */

#ifdef DEMOD_CMD_ISDBT_STATUS
int DEMOD_L1_GET_DD_ISDBT_Status (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_CMD_ISDBT_STATUS */

#ifdef DEMOD_CMD_ISDBT_TMCC_INFO
int DEMOD_L1_GET_DD_ISDBT_TMCC_Info (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_CMD_ISDBT_TMCC_INFO */

#ifdef DEMOD_CMD_DVBC_STATUS
int DEMOD_L1_GET_DD_DVBC_Status (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_CMD_DVBC_STATUS */

#ifdef DEMOD_CMD_DVBC2_STATUS
int DEMOD_L1_GET_DD_DVBC2_Status (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_CMD_DVBC2_STATUS */

#ifdef DEMOD_CMD_DISEQC_STATUS
int DEMOD_L1_GET_DD_DISEQC_Status (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_CMD_DISEQC_STATUS */

#ifdef DEMOD_CMD_DVBS_STATUS
int DEMOD_L1_GET_DD_DVBS_Status (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_CMD_DVBS_STATUS */

#ifdef DEMOD_CMD_DVBS2_STATUS
int DEMOD_L1_GET_DD_DVBS2_Status (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_CMD_DVBS2_STATUS */

#ifdef DEMOD_CMD_BLIND_STATUS
int DEMOD_L1_GET_DD_BLIND_Status (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_CMD_BLIND_STATUS */

#ifdef DEMOD_CMD_BLIND_INIT
int DEMOD_L1_GET_DD_BLIND_Init (LX_DEMOD_L1_Context * core, UINT32 startFreq, UINT32 endFreq);
#endif /* DEMOD_CMD_BLIND_INIT */

#ifdef DEMOD_CMD_BLIND_FOUNDINFO
int DEMOD_L1_GET_DD_BLIND_FoundInfo (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_CMD_BLIND_INIT */

#ifdef DEMOD_CMD_BLIND_END
int DEMOD_L1_GET_DD_BLIND_End (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_CMD_BLIND_END */

#ifdef DEMOD_CMD_SET_DVBT2_BASEADDR_AXI
int DEMOD_L1_SET_DD_DVBT2_BASEADDR_AXI (LX_DEMOD_L1_Context * core, UINT32 baseAddr1, UINT32 baseAddr2);
#endif /* DEMOD_CMD_SET_DVBT2_BASEADDR_AXI */

#ifdef DEMOD_CMD_SET_DVB_BASEADDR_AXI
int DEMOD_L1_SET_DD_DVB_BASEADDR_AXI (LX_DEMOD_L1_Context * core, UINT32 baseAddr1, UINT32 baseAddr2, UINT32 baseAddr3);
#endif /* DEMOD_CMD_SET_DVB_BASEADDR_AXI */

#ifdef DEMOD_CMD_DTMB_STATUS
int DEMOD_L1_GET_DD_DTMB_Status (LX_DEMOD_L1_Context * core);
#endif /* DEMOD_CMD_DTMB_STATUS */

#endif /* _DBB_DEMOD_COMMANDS_PROTOTYPES_H_ */














