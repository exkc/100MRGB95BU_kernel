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
**  Name:DBB_DEMOD_L2_SAT_API.h
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
#ifndef   _DBB_DEMOD_L2_SAT_API_H_
#define   _DBB_DEMOD_L2_SAT_API_H_

#include "DBB_DEMOD_L2_Common_API.h"

typedef struct
{
	UINT8  standard;
	UINT32 freq;
	UINT32 symbol_rate_bps;
	UINT32 codeRate;
	UINT8 constellation;

	int result;

} LX_DEMOD_L2_BLINDSCAN_DVBS_MSG_T;

typedef struct
{
	UINT32 totalCount;
	UINT8  bFinished;
	LX_DEMOD_L2_BLINDSCAN_DVBS_MSG_T seekinfo[20];

} LX_DEMOD_L2_BLIND_DVBS_INFO_T;

typedef struct
{
	UINT8 standard;
	UINT32 freq;
	UINT32 symbolRate;  //Kbps
	UINT8  constellation;

}LX_DEMOD_L2_BLIND_DVBS_INFO_PARAM_T;

typedef struct
{
	UINT32 totalCount;
	UINT8 detectDone;
	LX_DEMOD_L2_BLIND_DVBS_INFO_PARAM_T paramInfo[16];

}LX_DEMOD_L2_BLIND_DVBS_PARAM_T;

int DEMOD_L2_SAT_SW_Init (LX_DEMOD_L2_Context * frontend, UINT32 demodAddr);
int DEMOD_L2_SAT_set_demod (LX_DEMOD_L2_Context * frontend
						, UINT8 standard
						, UINT32 freq
						, UINT8 tuneMode
						, UINT8 specInv_Auto_Enable
						, UINT8 specInv
						, UINT16 symbol_rate_Kbps
						, UINT8 operatingMode );
int DEMOD_L2_SAT_Spectrum (LX_DEMOD_L2_Context * frontend, UINT8 spectrum_inversion);
int DEMOD_L2_SAT_send_diseqc_sequence (LX_DEMOD_L2_Context * frontend, UINT8 sequence_length, UINT8 * sequenceBuffer, UINT8 cont_tone, UINT8 tone_burst, UINT8 burst_sel, UINT8 repeatEn);
int DEMOD_L2_SAT_Blind_Info (LX_DEMOD_L2_Context * frontend);
int DEMOD_L2_SAT_Blind_Init (LX_DEMOD_L2_Context * frontend, UINT32 startFreq, UINT32 endFreq);
int DEMOD_L2_SAT_Blind_End (LX_DEMOD_L2_Context * frontend);
int DEMOD_L2_SAT_Blind_FoundInfo (LX_DEMOD_L2_Context * frontend);
int DEMOD_L2_SAT_Blind_Status (LX_DEMOD_L2_Context * frontend);
int DEMOD_L2_SAT_Blind_SymbolRate_Detect (LX_DEMOD_L2_Context * frontend);

#endif /* _DBB_DEMOD_L2_SAT_API_H_ */
