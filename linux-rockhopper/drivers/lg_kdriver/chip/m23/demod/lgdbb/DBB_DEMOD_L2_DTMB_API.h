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

#ifndef   _DBB_DEMOD_L2_DTMB_API_H_
#define   _DBB_DEMOD_L2_DTMB_API_H_

#include "DBB_DEMOD_L2_Common_API.h"

/*****************************************************************************************/
int DEMOD_L2_DTMB_SW_Init  (LX_DEMOD_L2_Context *frontend, UINT32 demodAdd);

int DEMOD_L2_DTMB_Set_demod   (LX_DEMOD_L2_Context *frontend
											, UINT8  standard
											, UINT32 freq
											, UINT8  tuneMode
											, UINT8  specInv_Auto_Enable
											, UINT8  specInv
											, UINT16  ter_bandwidth_KHz );

int DEMOD_L2_DTMB_Set_BaseAddr_AXI(LX_DEMOD_L2_Context *frontend, UINT32 baseAddr );


#endif /* _DBB_DEMOD_L2_DTMB_API_H_ */
