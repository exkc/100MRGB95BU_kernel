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

#ifndef _DBB_DEMOD_L2_Common_API_H_
#define _DBB_DEMOD_L2_Common_API_H_

#include "DBB_DEMOD_L1_IPC.h"
#include "DBB_DEMOD_L1_Properties.h"
#include "DBB_DEMOD_L1_Commands.h"

#include "DBB_DEMOD_L1_API.h"

#include "DBB_DEMOD_L1_IPC_Prototypes.h"
#include "DBB_DEMOD_L1_Commands_Prototypes.h"
#include "DBB_DEMOD_L1_Properties_Functions.h"

typedef struct _LX_DEMOD_L2_Context {
	LX_DEMOD_L1_Context * demod;

	UINT64	baseAddr;

	UINT8	demod_init_done; //x
	//UINT8	standard;  //x
	UINT32	detected_rf; //o
	UINT32	centerFrq; //x

	UINT8	num_PLP_total;
	UINT8	set_PLP_ID;			// DVB use for plp id
	UINT8 	current_PLP_ID;		// ATSC3 use for plp id 
	UINT8 	current_PLP_ID_0;
	UINT8 	current_PLP_ID_1;
	UINT8 	current_PLP_ID_2;
	UINT8 	current_PLP_ID_3;

	UINT8	last_plp0;
	UINT8	last_plp1;
	UINT8	last_plp2;
	UINT8	last_plp3;
	
	UINT8	auto_detect_DVBT_T2;	//DVBT / DVBT2
	UINT8	cable_blind_scan;	//DVBC
	UINT8	eAlarm;			//ISDB_T

	UINT8	satellite_init_done;
	UINT8	auto_detect_SAT;
	UINT8	satellite_blind_search;
	UINT8	satellite_spectrum_inversion;
#ifndef __KERNEL__
	UINT8	find_chnum;
	UINT32	find_freq[200];
	UINT32	find_symrate[200];
#endif
} LX_DEMOD_L2_Context;

typedef struct _LX_DEMOD_L2_SIG_STATUS
{
	SINT32	snr;
	SINT32	offsetFrq_Hz;
	SINT32	sam_offsetFrq_Hz;
	SINT16	if_agc;
	UINT32	mse_info;
	UINT32	constPwr;
	UINT32	constPwr_eq;
	UINT32	ber;
	UINT32	packetError;
	UINT32	sym_rate;
	UINT8	signalQuality;
	UINT8	operatingMode;
	UINT8	constellation;
	UINT8	spInv;
	UINT8	bandwidth;
	UINT8	demodLock;
	UINT8	lock_l1b;
	UINT8	lock_l1d;

	SINT32	snr_demod;
	SINT32	snr_eq;
	UINT32	mse_info_demod;
	UINT32	mse_info_eq;

	UINT8	guardInterval;	// ATSC3/DVBT/DVBT2/ISDBT
	UINT8	codeRate;	// ATSC3/DVBT/DVBT2/ISDBT
	UINT8	fftMode;	// ATSC3/DVBT/DVBT2/ISDBT

	UINT16	cell_id;	// DVBT
	UINT8	hierarchy;	// DVBT
	UINT8	hierarchy_sel; 	// DVBT
	UINT8	il_mode;	// DTMB
	UINT8	pn_const;	// DTMB
	UINT8	pn_mode;	// DTMB
	UINT8	carr_mode;	// DTMB

	UINT8	num_PLP;	// ATSC3/DVBT2
	SINT32	demod_snr;  // for debugging
	UINT32	plp_pre_bch_ber; // for debugging
	UINT16	ldpc_err; // for debugging
	UINT16	plp_outer_err; // new //
	UINT8	plp_ldpc_iter;//PLP LDPC Iter // htlim 160420 // for debugging
	UINT8	l1b_ldpc_iter;//L1B LDPC Iter // htlim 160420 // for debugging
	UINT8	l1d_ldpc_iter;//L1D LDPC Iter // htlim 160420 // for debugging
	UINT8	plp_pkerr_0;//PLP0_Frame_err // 170918	//B17C0
	UINT8	plp_pkerr_1;//PLP1_Frame_err // 170918	//B17C0
	UINT8	plp_pkerr_2;//PLP2_Frame_err // 170918	//B17C0
	UINT8	plp_pkerr_3;//PLP3_Frame_err // 170918	//B17C0

	UINT8	plp_exist;	//B17C0

	UINT8	frame_length;	//B17C0

	UINT8	plp_Err_msg;	//B17C0

	UINT8	current_plp_id;
	UINT8	bw_Ext;
	UINT8	pp;
	UINT8	time_il;
} LX_DEMOD_L2_SIG_STATUS;

 typedef struct _LX_DEMOD_L2_PART_INFO
{
	UINT8	fw_major;
	UINT8	fw_minor;
	UINT8	fw_year;
	UINT8	fw_month;
	UINT8	fw_day;
	UINT8	chip_type;
	UINT8	chip_rev;
}   LX_DEMOD_L2_PART_INFO;

 typedef struct
{
	UINT8 plpCount_Including_channInfo;
	UINT8 plpID[256]; 					/* array of PLP ID */
	UINT8 plpconf[256]; 					/* array of PLP ID */

	UINT8 plpTotalCount; 					/*number of total PLP */
	UINT8 plpCount;
} LX_DEMOD_L2_MULTI_PLP_ID_T;

typedef struct
{
	UINT8	constel;			// QAM mode
	UINT8	code_rate;			// code rate
	UINT32	sn_ref;				// Nordig C/N reference spec.
}LX_DEMOD_SQI_CN_ATSC3P1_T;

int DEMOD_L2_Configure (LX_DEMOD_L2_Context *frontend);
int DEMOD_L2_Opermode_Configure (LX_DEMOD_L2_Context *frontend , LX_DEMOD_OPER_MODE_T operMode);

int DEMOD_L2_Standby (LX_DEMOD_L2_Context *frontend);
int DEMOD_L2_WakeUp (LX_DEMOD_L2_Context *frontend);
int DEMOD_L2_PowerUpWithPatch (LX_DEMOD_L2_Context *frontend);
int DEMOD_L2_LoadFirmware_IRAM (LX_DEMOD_L2_Context *frontend, LX_DEMOD_FW_STRUCT fw_table[], UINT8 nbLines);
int DEMOD_L2_LoadFirmware_DRAM (LX_DEMOD_L2_Context *frontend, LX_DEMOD_FW_STRUCT fw_table[], UINT8 nbLines);

int DEMOD_L2_Init (LX_DEMOD_L2_Context *frontend);
int DEMOD_L2_Media (LX_DEMOD_L2_Context *frontend, UINT8 modulation);
int DEMOD_L2_StartFirmware (LX_DEMOD_L2_Context *frontend);

/*****************************************************************************************/
int DEMOD_L2_Switch_to_standard (LX_DEMOD_L2_Context *frontend, UINT8 new_standard);
int DEMOD_L2_Check_NeverLock_state (LX_DEMOD_L2_Context *frontend);
int DEMOD_L2_Check_NeverLock_loop (LX_DEMOD_L2_Context *frontend, UINT8 standard);
int DEMOD_L2_Check_lock_loop (LX_DEMOD_L2_Context *frontend, UINT8 standard);
int DEMOD_L2_Check_BlindLock_state (LX_DEMOD_L2_Context *frontend);
int DEMOD_L2_Check_BlindLock_loop (LX_DEMOD_L2_Context *frontend, UINT8 standard);


int DEMOD_L2_Set_Invert_Spectrum (LX_DEMOD_L2_Context *frontend);

int DEMOD_L2_Get_LockStatus (LX_DEMOD_L2_Context *frontend, UINT8 *pOperMode,  UINT8 *pFecLock);
int DEMOD_L2_Get_OperMode (LX_DEMOD_L2_Context *frontend, LX_DEMOD_OPER_MODE_T *reply_opmode);
int DEMOD_L2_SignalStatus (LX_DEMOD_L2_Context *frontend, LX_DEMOD_L2_SIG_STATUS *pSignalStatus);
int DEMOD_L2_SendCommand (LX_DEMOD_L2_Context *frontend, UINT32 cmd_code);
int DEMOD_L2_Set_Property (LX_DEMOD_L2_Context *frontend, UINT32 prop_code);

int DEMOD_L2_GET_REG (LX_DEMOD_L2_Context *frontend, UINT16  addr, UINT8 length, UINT8   *readData);
int DEMOD_L2_GET_REG_MAP (LX_DEMOD_L2_Context *frontend, UINT16  addr, UINT16 length, UINT8 *readData);
int DEMOD_L2_SET_REG (LX_DEMOD_L2_Context *frontend,  UINT16  addr, UINT8 length, UINT32   wrData);

int DEMOD_L2_Tuner_I2C_Enable (LX_DEMOD_L2_Context *frontend);
int DEMOD_L2_Tuner_I2C_Disable (LX_DEMOD_L2_Context *frontend);
int DEMOD_L2_Get_PartInfo (LX_DEMOD_L2_Context *frontend, LX_DEMOD_L2_PART_INFO *fwInfo);
int DEMOD_L2_GetDump (LX_DEMOD_L2_Context *frontend);
int DEMOD_L2_Get_Property (LX_DEMOD_L2_Context *frontend, UINT32 prop_code);

int DEMOD_L2_Set_ChipInfo (LX_DEMOD_L2_Context *frontend, UINT16 chip_ver, UINT8 chip_if);
int DEMOD_L2_Set_SoftRst (LX_DEMOD_L2_Context *frontend, UINT8 softrstb, UINT8 softrstsyncb, UINT8 softrsteq1b, UINT8 softrsteq2b, UINT8 softrstdiseqcb, UINT8 softrstfecb, UINT8 softrsttpifb);

int DEMOD_L2_InitMem (LX_DEMOD_L2_Context *frontend);
int DEMOD_L2_Set_MemAddr (LX_DEMOD_L2_Context *frontend, UINT64 baseAddr);
int DEMOD_L2_PowerUpWithMem (LX_DEMOD_L2_Context *frontend);

int DEMOD_L2_Get_TsClkStatus (LX_DEMOD_L2_Context *frontend, UINT32 *pTsClkRate);

#endif /* _DBB_DEMOD_L2_Common_API_H_ */

