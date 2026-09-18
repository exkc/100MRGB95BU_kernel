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
**  Name:DBB_DEMOD_L2_Properties_Function.h
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

#ifndef   _DBB_PROPERTIES_FUNCTIONS_H_
#define   _DBB_PROPERTIES_FUNCTIONS_H_

void DEMOD_L1_Store_User_Properies (LX_DEMOD_L1_PropObj * prop);
int DEMOD_L1_Compare_N_SetProperty (LX_DEMOD_L1_Context * core, UINT32 prop_code, UINT32  data);
int DEMOD_L1_Get_Unpacked_Property (LX_DEMOD_L1_Context * core, UINT32 prop_code, UINT32  * data);
int DEMOD_L1_Set_Property (LX_DEMOD_L1_Context * core, UINT32 prop_code);
int DEMOD_L1_Get_Packed_Property (LX_DEMOD_L1_Context * core, UINT32 prop_code);

int DEMOD_L1_Download_COMMON_Properties (LX_DEMOD_L1_Context * core);

int DEMOD_L1_Download_DVBC_Properties (LX_DEMOD_L1_Context * core);
int DEMOD_L1_Download_DTMB_Properties (LX_DEMOD_L1_Context * core);
int DEMOD_L1_Download_DVBS_Properties (LX_DEMOD_L1_Context * core);
int DEMOD_L1_Download_DVBS2_Properties (LX_DEMOD_L1_Context * core);
int DEMOD_L1_Download_DVBT_Properties (LX_DEMOD_L1_Context * core);
int DEMOD_L1_Download_DVBT2_Properties (LX_DEMOD_L1_Context * core);
int DEMOD_L1_Download_DVBC2_Properties (LX_DEMOD_L1_Context * core);
int DEMOD_L1_Download_ATSC3_Properties (LX_DEMOD_L1_Context * core);
int DEMOD_L1_Download_All_Properties (LX_DEMOD_L1_Context * core);


int DEMOD_L1_Unpack_Property (LX_DEMOD_L1_PropObj * prop, UINT32 prop_code, UINT32 * data);
int DEMOD_L1_Pack_Property (LX_DEMOD_L1_PropObj * prop, UINT32 prop_code, UINT32  data);
void DEMOD_L1_Store_Properties_Defaults (LX_DEMOD_L1_PropObj * prop) ;
int DEMOD_L1_PropertyText (LX_DEMOD_L1_PropObj * prop, UINT32 prop_code);
#endif /* _LGDBB_PROPERTIES_FUNCTIONS_H_ */







