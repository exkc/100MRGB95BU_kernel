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
**  Name:DBB_DEMOD_L2_DVB_API.h
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

#ifndef   _DBB_DEMOD_L2_DVB_API_H_
#define   _DBB_DEMOD_L2_DVB_API_H_

#include "DBB_DEMOD_L2_Common_API.h"

/**
 * DVBT Hierachical mode
 */
typedef enum
{
	 LX_DEMOD_L2_TPS_HIERARCHY_DVBT_NONE,			///< DVBT Hierachical mode-> None hierarchical mode
	 LX_DEMOD_L2_TPS_HIERARCHY_DVBT_1,			///< DVBT Hierachical mode-> alpha = 1
	 LX_DEMOD_L2_TPS_HIERARCHY_DVBT_2,			///< DVBT Hierachical mode-> alpha = 2
	 LX_DEMOD_L2_TPS_HIERARCHY_DVBT_4,			///< DVBT Hierachical mode-> alpha = 4
	 LX_DEMOD_L2_TPS_HIERARCHY_DVBT_UNKNOWN			///< DVBT Hierachical mode-> alpha = UNKNOWN
} LX_DEMOD_L2_TPS_HIERARCHY_DVBT_T;

/**
 * RF modulation mode .
 */
typedef enum
{
	LX_DEMOD_L2_CONSTELLATION_16QAM = 0,			///< modulation type -> QAM16
	LX_DEMOD_L2_CONSTELLATION_32QAM,			///< modulation type -> QAM32
	LX_DEMOD_L2_CONSTELLATION_64QAM,			///< modulation type -> QAM64
	LX_DEMOD_L2_CONSTELLATION_128QAM,			///< modulation type -> QAM128
	LX_DEMOD_L2_CONSTELLATION_256QAM,			///< modulation type -> QAM256
	LX_DEMOD_L2_CONSTELLATION_1024QAM,			///< modulation type -> QAM1024
	LX_DEMOD_L2_CONSTELLATION_4096QAM,			///< modulation type -> QAM4096
	LX_DEMOD_L2_CONSTELLATION_BPSK,				///< modulation type -> BPSK
	LX_DEMOD_L2_CONSTELLATION_QPSK,				///< modulation type -> QPSK
	LX_DEMOD_L2_CONSTELLATION_DQPSK,			///< modulation type -> DQPSK
	LX_DEMOD_L2_CONSTELLATION_VSB,				///< modulation type -> VSB
	LX_DEMOD_L2_CONSTELLATION_8PSK,
	LX_DEMOD_L2_CONSTELLATION_16APSK,
	LX_DEMOD_L2_CONSTELLATION_32APSK,
	LX_DEMOD_L2_CONSTELLATION_NTSC,				///< modulation type -> NTSC
	LX_DEMOD_L2_CONSTELLATION_PAL,				///< modulation type -> PAL
	LX_DEMOD_L2_CONSTELLATION_SECAM,			///< modulation type -> SECAM

	LX_DEMOD_L2_CONSTELLATION_MODE_END,
	LX_DEMOD_L2_CONSTELLATION_UNKOWN_MODE			///< modulation type -> UNKNOWN
} LX_DEMOD_L2_CONSTELLATION_MODE_T;

/**
 * Code rate
 */
typedef enum
{
	LX_DEMOD_L2_CODE_1_2,					///< code rate-> 1/2
	LX_DEMOD_L2_CODE_1_3,					///< code rate-> 1/3 only DVBS2
	LX_DEMOD_L2_CODE_1_4,					///< code rate-> 1/4 only DVBS2
	LX_DEMOD_L2_CODE_2_3,					///< code rate-> 2/3
	LX_DEMOD_L2_CODE_3_4,					///< code rate-> 3/4
	LX_DEMOD_L2_CODE_2_5,					///< code rate-> 2/5 only DVBS2
	LX_DEMOD_L2_CODE_3_5,					///< code rate-> 3/5
	LX_DEMOD_L2_CODE_4_5,					///< code rate-> 4/5
	LX_DEMOD_L2_CODE_5_6,					///< code rate-> 5/6
	LX_DEMOD_L2_CODE_6_7,					///< code rate-> 6/7
	LX_DEMOD_L2_CODE_7_8,					///< code rate-> 7/8
	LX_DEMOD_L2_CODE_8_9,					///< code rate-> 8/9, only DVBS2
	LX_DEMOD_L2_CODE_9_10,					///< code rate-> 8/9, only DVBS2
	LX_DEMOD_L2_CODE_UNKNOWN				///< code rate-> UNKNOWN
} LX_DEMOD_L2_CODERATE_T;

/**
 * Nordig C/N reference spec according to both code rate and QAM mode.
 */
typedef struct
{
	LX_DEMOD_L2_TPS_HIERARCHY_DVBT_T	hierarchMode;	///< Hierachical transmission mode
	UINT8 					bSetHp;		///< High/Low priority signal path slection at hierachical transmission mode
	LX_DEMOD_L2_CONSTELLATION_MODE_T	constel;	///< QAM mode
	LX_DEMOD_L2_CODERATE_T			code_rate;	///< code rate
	UINT32					cn_ref;		///< Nordig C/N reference spec.
}LX_DEMOD_L2_SQI_CN_NORDIGP1_T;



int DEMOD_L2_DVB_SW_Init (LX_DEMOD_L2_Context * frontend, UINT32 demodAdd);

int DEMOD_L2_DVB_Set_demod (LX_DEMOD_L2_Context * frontend
							, UINT8 standard
							, UINT32 freq
							, UINT8 tuneMode
							, UINT8 specInv_Auto_Enable
							, UINT8 specInv
							, UINT16 ter_bandwidth_KHz
							, UINT8 dvbt_hpSel
							, UINT16 symbol_rate_Kbps
							, UINT8 dvb_c_constellation
							, UINT8  plp_id
							, UINT8 T2_lock_mode );

int DEMOD_L2_DVB_AutoModeDetectOn (LX_DEMOD_L2_Context * frontend);	//deprecated
int DEMOD_L2_DVB_AutoModeDetectOff (LX_DEMOD_L2_Context * frontend);	//deprecated

int DEMOD_L2_DVB_Set_PLP_Select (LX_DEMOD_L2_Context * frontend,  UINT8 plp_id, UINT8  plp_id_sel_mode);
int DEMOD_L2_DVBC_Set_SymbolRate_Detect (LX_DEMOD_L2_Context * frontend, UINT8 autoEn, UINT8 symbol_rate_Kbps);
int DEMOD_L2_DVB_Get_PLP_ID (LX_DEMOD_L2_Context * frontend, LX_DEMOD_L2_MULTI_PLP_ID_T * pPlpParams);
int DEMOD_L2_DVBT2_Set_BaseAddr_AXI (LX_DEMOD_L2_Context * frontend, UINT32 baseAddr1, UINT32 baseAddr2 );
int DEMOD_L2_DVB_Set_BaseAddr_AXI (LX_DEMOD_L2_Context * frontend, UINT32 baseAddr1, UINT32 baseAddr2, UINT32 baseAddr3 );

#endif /* _DBB_DEMOD_L2_DVB_API_H_ */

