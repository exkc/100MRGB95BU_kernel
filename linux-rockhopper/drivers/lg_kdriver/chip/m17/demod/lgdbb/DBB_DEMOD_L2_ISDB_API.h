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
**  Name:DBB_DEMOD_L2_ATSC_API.h
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

#ifndef   _DBB_DEMOD_L2_ISDB_API_H_
#define   _DBB_DEMOD_L2_ISDB_API_H_

#include "DBB_DEMOD_L1_API.h"
#include "DBB_DEMOD_L1_Properties_Functions.h"
#include "DBB_DEMOD_L1_Commands_Prototypes.h"

#include "DBB_DEMOD_L2_Common_API.h"


typedef struct _LX_DEMOD_L2_TMCC_INFO
{
	UINT8 constellation;
	UINT8 isLock;

	UINT8 fft_mode;
	UINT8 gi;
	UINT8 qamMode_a;
	UINT8 codeRate_a;
	UINT8 segNum_a;
	UINT8 qamMode_b;
	UINT8 codeRate_b;
	UINT8 segNum_b;
	UINT8 qamMode_c;
	UINT8 codeRate_c;
	UINT8 segNum_c;

} LX_DEMOD_L2_TMCC_INFO;


extern UINT8  DEMOD_L2_ISDB_Set_BaseAddr_AXI(LX_DEMOD_L2_Context *frontend, UINT32 baseAddr);
extern UINT8  DEMOD_L2_ISDB_Get_TMCC_Info   (LX_DEMOD_L2_Context *front_end, LX_DEMOD_L2_TMCC_INFO *tmcc);
extern UINT8  DEMOD_L2_ISDB_Get_Emergency_Alarm   (LX_DEMOD_L2_Context *front_end, UINT8 *eAlarm);

#endif /* _DBB_DEMOD_L2_ATSC_API_H_ */
