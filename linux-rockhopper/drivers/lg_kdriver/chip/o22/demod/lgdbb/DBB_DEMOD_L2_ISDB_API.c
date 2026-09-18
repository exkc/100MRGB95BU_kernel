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
#define DEMOD_TAG "[L2.ISDB] "

#include <DBB_DEMOD_typedefs.h>
#include <demod_util.h>

#include <DBB_DEMOD_L2_ISDB_API.h>

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_XTENSA)

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
#include <asm/div64.h> //do_div
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
#include <math.h>
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)

#endif


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_ISDB_Set_Base Address for AXI_memory write.
 * Set Set_Base Address for ISDB_T AXI_memory
 *
 * @param *frontend 			[IN] LX_DEMOD_L2_Context
 * @param index 				[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_ISDB_Set_BaseAddr_AXI(LX_DEMOD_L2_Context *frontend, UINT32 baseAddr)
{
	int retc = NO_DEMOD_ERROR;

	retc =  DEMOD_L1_API_BaseAddr_AXI(frontend->demod, baseAddr);

	return retc;

}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_ISDB_Get_TMCC_Info.
 * gets the PLP infomations
 *
 * @param *frontend 			[IN] LX_DEMOD_L2_Context
 * @param index 				[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_ISDB_Get_TMCC_Info   (LX_DEMOD_L2_Context * frontend, LX_DEMOD_L2_TMCC_INFO *tmcc)
{
	int retc = NO_DEMOD_ERROR;

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

	retc = DEMOD_L1_GET_DD_ISDBT_TMCC_Info(frontend->demod);

	if(NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("FAIL, DEMOD_L2_ISDB_Get_TMCC_Info() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}


	tmcc->isLock = frontend->demod->rsp->isdbt_status.lock_fec;
	tmcc->gi = frontend->demod->rsp->isdbt_tmcc_info.gi;
	tmcc->fft_mode =  frontend->demod->rsp->isdbt_tmcc_info.fft_mode;
	tmcc->qamMode_a = frontend->demod->rsp->isdbt_tmcc_info.oqama;
	tmcc->codeRate_a = frontend->demod->rsp->isdbt_tmcc_info.ocra;
	tmcc->segNum_a = frontend->demod->rsp->isdbt_tmcc_info.onsega;

	tmcc->qamMode_b = frontend->demod->rsp->isdbt_tmcc_info.oqamb;
	tmcc->codeRate_b = frontend->demod->rsp->isdbt_tmcc_info.ocrb;
	tmcc->segNum_b = frontend->demod->rsp->isdbt_tmcc_info.onsegb;

	tmcc->qamMode_c = frontend->demod->rsp->isdbt_tmcc_info.oqamc;
	tmcc->codeRate_c = frontend->demod->rsp->isdbt_tmcc_info.ocrc;
	tmcc->segNum_c = frontend->demod->rsp->isdbt_tmcc_info.onsegc;

	return retc;
}





/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_ISDB_Get_Emergency_Alarm.
 * gets the emergency alarm infomations
 *
 * @param *frontend 			[IN] LX_DEMOD_L2_Context
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_ISDB_Get_Emergency_Alarm (LX_DEMOD_L2_Context * frontend, UINT8 *eAlarm)
{
	int retc = NO_DEMOD_ERROR;

	retc = DEMOD_L1_API_Emergency_Alarm (frontend->demod, eAlarm);

	frontend->eAlarm = *eAlarm;

	return retc;
}

