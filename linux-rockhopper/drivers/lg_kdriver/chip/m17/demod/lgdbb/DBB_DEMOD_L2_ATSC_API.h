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

#include "DBB_DEMOD_L1_API.h"
#include "DBB_DEMOD_L1_Properties_Functions.h"
#include "DBB_DEMOD_L1_Commands_Prototypes.h"

#include "DBB_DEMOD_L2_Common_API.h"


typedef struct
{
	UINT8 plpTotalCount; /*number of total PLP */

	UINT8 plpCount_Including_channInfo;
	UINT8 plpID[64]; /* array of PLP ID */

} LX_DEMOD_L2_ATSC3_MULTI_PLP_ID_T;

typedef struct
{
	UINT16 l1b_num_subframes;
	UINT8 l1b_pre_num_symbols;
	UINT16 l1b_first_num_ofdm_symbols;
	UINT8 l1b_first_sub_fft_size;
	UINT8 l1b_first_sub_gi;
	UINT8 l1b_first_reduce_carr;
	UINT8 l1b_first_sub_scatt_pp;
	UINT8 l1b_first_sub_scatt_pb;
	UINT8 l1b_first_sub_sbs_first;
	UINT8 l1b_first_sub_sbs_last;

	UINT8 l1d_num_plp;
	UINT8 l1d_plp_ti_mode;
	UINT8 l1d_plp_fec_type;
	UINT8 l1d_plp_mod;
	UINT8 l1d_plp_cr;
	UINT8 l1d_plp_cti_depth;
	UINT16 l1d_plp_cti_start_row;
	UINT8 l1d_plp_hti_inter_subframe;
	UINT8 l1d_plp_hti_num_ti_blocks;
	UINT16 l1d_plp_hti_num_fec_blocks;
	UINT8 l1d_miso;
	UINT8 l1d_mimo;
	UINT16 l1d_plp_hti_num_fec_blocks_max;

	UINT16 bs_pre_str;
	UINT8 bs_l1b_mod;

	UINT8 l1d_plp_id;
	UINT8 l1d_slt_flag;
} LX_DEMOD_L2_ATSC3_PLP_INFO_T;



/*****************************************************************************************/
extern UINT8 DEMOD_L2_ATSC_SW_Init  (	LX_DEMOD_L2_Context *front_end  , UINT32 demodAdd);

extern UINT8 DEMOD_L2_ATSC_Set_demod   (LX_DEMOD_L2_Context *front_end
												, UINT8  standard
												, UINT32 freq
												, UINT8  tuneMode
												, UINT8  specInv_Auto_Enable
												, UINT8  specInv
												, UINT16  ter_bandwidth_KHz
												, UINT16  plp_id );

extern UINT8  DEMOD_L2_ATSC_Set_PLP_Select(LX_DEMOD_L2_Context *frontend,  UINT8 plp_id, UINT8   plp_id_sel_mode);
extern UINT8  DEMOD_L2_ATSC_Get_PLP_ID   (LX_DEMOD_L2_Context *front_end, LX_DEMOD_L2_ATSC3_MULTI_PLP_ID_T *pPlpParams);
extern UINT8  DEMOD_L2_ATSC_Get_PLP_Info   (LX_DEMOD_L2_Context *front_end, UINT8 index, LX_DEMOD_L2_ATSC3_PLP_INFO_T *plpInfo);

#endif /* _DBB_DEMOD_L2_ATSC_API_H_ */
