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
**  Name:DBB_DEMOD_L2_ISDB_API.c
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

/* LGFDEMOD API Specific Includes */
/* Before including the headers, define SiLevel and SiTAG */

#include "DBB_DEMOD_L2_ISDB_API.h"               /* Include file for this code */



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_ISDB_Set_Base Address for AXI_memory write.
 * Set Set_Base Address for ISDB_T AXI_memory
 *
 * @param *front_end 			[IN] LX_DEMOD_L2_Context
 * @param index 				[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L2_ISDB_Set_BaseAddr_AXI(LX_DEMOD_L2_Context *frontend, UINT32 baseAddr)
{
	UINT8 return_code;

	return_code =  DEMOD_L1_API_BaseAddr_AXI(frontend->demod, baseAddr);

	return return_code;

}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_ISDB_Get_TMCC_Info.
 * gets the PLP infomations
 *
 * @param *front_end 			[IN] LX_DEMOD_L2_Context
 * @param index 				[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L2_ISDB_Get_TMCC_Info   (LX_DEMOD_L2_Context *front_end, LX_DEMOD_L2_TMCC_INFO *tmcc)
{

	UINT8 return_code;

	tmcc->isLock = 0;
	tmcc->gi = 0;

	tmcc->qamMode_a = 0;
	tmcc->codeRate_a = 0;
	tmcc->segNum_a = 0;

	tmcc->qamMode_b = 0;
	tmcc->codeRate_b = 0;
	tmcc->segNum_b = 0;

	tmcc->qamMode_c = 0;
	tmcc->codeRate_c = 0;
	tmcc->segNum_c = 0;

	tmcc->fft_mode = 0;

	return_code = DEMOD_L1_GET_DD_ISDBT_TMCC_Info(front_end->demod);

	if(return_code == NO_DEMOD_ERROR)
	{
		tmcc->isLock = front_end->demod->rsp->isdbt_status.lock_fec;
		
		tmcc->gi = front_end->demod->rsp->isdbt_tmcc_info.gi;

		tmcc->fft_mode =  front_end->demod->rsp->isdbt_tmcc_info.fft_mode;
		
		tmcc->qamMode_a = front_end->demod->rsp->isdbt_tmcc_info.oqama;
		
		tmcc->codeRate_a = front_end->demod->rsp->isdbt_tmcc_info.ocra;
		
		tmcc->segNum_a = front_end->demod->rsp->isdbt_tmcc_info.onsega;

		
		tmcc->qamMode_b = front_end->demod->rsp->isdbt_tmcc_info.oqamb;
		
		tmcc->codeRate_b = front_end->demod->rsp->isdbt_tmcc_info.ocrb;
		
		tmcc->segNum_b = front_end->demod->rsp->isdbt_tmcc_info.onsegb;

		
		tmcc->qamMode_c = front_end->demod->rsp->isdbt_tmcc_info.oqamc;
		
		tmcc->codeRate_c = front_end->demod->rsp->isdbt_tmcc_info.ocrc;
		
		tmcc->segNum_c = front_end->demod->rsp->isdbt_tmcc_info.onsegc;

	}

	else
	
	{
		
		return return_code;
	}

	
	return NO_DEMOD_ERROR;


}





/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_ISDB_Get_Emergency_Alarm.
 * gets the emergency alarm infomations
 *
 * @param *front_end 			[IN] LX_DEMOD_L2_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
UINT8  DEMOD_L2_ISDB_Get_Emergency_Alarm   (LX_DEMOD_L2_Context *front_end, UINT8 *eAlarm)
{

	UINT8 return_code;

	return_code =  DEMOD_L1_API_Emergency_Alarm	(front_end->demod, eAlarm);

	front_end->eAlarm = *eAlarm;

	return return_code;

}

