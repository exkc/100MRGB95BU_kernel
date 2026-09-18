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

#ifndef   _DBB_DEMOD_L2_ATSC_API_H_
#define   _DBB_DEMOD_L2_ATSC_API_H_

#include "DBB_DEMOD_L2_Common_API.h"

typedef struct {
	DEMOD_RES_ATSC3_PLP_INFO_struct plp_info;
} DEMOD_ATSC3_PLP_INFO_T;

typedef enum
{
	NONE_PLP_ID		= 0x00,
	FULL_PLP_ID, 	
	LLS_ONLY_PLP_ID

} LX_DEMOD_L2_MULTI_PLP_ID_SEL_T;

/*****************************************************************************************/
int DEMOD_L2_ATSC_SW_Init (LX_DEMOD_L2_Context * frontend, UINT32 demodAddr);

int DEMOD_L2_ATSC_Set_demod (LX_DEMOD_L2_Context *frontend,
							UINT8  standard,
							UINT32 freq,
							UINT8  tuneMode,
							UINT8  specInv_Auto_Enable,
							UINT8  specInv,
							UINT16  ter_bandwidth_KHz,
							UINT8  plp0_id,
							UINT8  plp1_id,
							UINT8  plp2_id,
							UINT8  plp3_id);

int DEMOD_L2_ATSC_Set_PLP_Select (LX_DEMOD_L2_Context * frontend, UINT8 plp0_id,  UINT8 plp1_id,  UINT8 plp2_id,  UINT8 plp3_id);
int DEMOD_L2_ATSC_Get_PLP_ID (LX_DEMOD_L2_Context * frontend, LX_DEMOD_L2_MULTI_PLP_ID_T * pPlpParams, LX_DEMOD_L2_MULTI_PLP_ID_SEL_T plpSel);
int DEMOD_L2_ATSC_Get_PLP_Info (LX_DEMOD_L2_Context * frontend, DEMOD_ATSC3_PLP_INFO_T * plpInfo);
int DEMOD_L2_ATSC_PLP_Change (LX_DEMOD_L2_Context *frontend,  UINT8 plp0_id,  UINT8 plp1_id,  UINT8 plp2_id,  UINT8 plp3_id );
int DEMOD_L2_ATSC3_Set_BaseAddr_AXI (LX_DEMOD_L2_Context *frontend, UINT32 baseAddr);

#endif /* _DBB_DEMOD_L2_ATSC_API_H_ */
