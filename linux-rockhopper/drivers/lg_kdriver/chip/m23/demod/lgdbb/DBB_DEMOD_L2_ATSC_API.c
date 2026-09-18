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
**  Name:DBB_DEMOD_L2_ATSC_API.c
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
**     Date	   Author	   Description
**  -------------------------------------------------------------------------
**   20-01-2016  Jeongpil Yun	 Initial draft.
**
*****************************************************************************/
#define DEMOD_TAG "[L2.ATSC] "

#include <DBB_DEMOD_typedefs.h>
#include <demod_util.h>

#include <DBB_DEMOD_L2_ATSC_API.h>

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_XTENSA)
static int DEMOD_L0_BitCountSet(UINT32 word) {
	return __builtin_popcount(word);
}
static int DEMOD_L0_BitFindFirstSet(UINT32 word) {
	return __builtin_ctz(word);
}

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
#include <asm/div64.h> //do_div

#include <linux/bitops.h>
static int DEMOD_L0_BitCountSet(UINT32 word) {
	return __arch_hweight32(word);
}
static int DEMOD_L0_BitFindFirstSet(UINT32 word) {
	return __ffs(word);
}

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
#include <math.h>

#include <intrin.h>
static int DEMOD_L0_BitCountSet(UINT32 word) {
	return __popcnt(word);
}
static int DEMOD_L0_BitFindFirstSet(UINT32 word) {
	DWORD idx;
	BOOLEAN ret;
	ret = _BitScanForward(&idx, (DWORD)word);
	return idx;
}
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)
static int DEMOD_L0_BitCountSet(UINT32 word) {
	//return __builtin_popcount(word);
	return 0;
}
static int DEMOD_L0_BitFindFirstSet(UINT32 word) {
	//return __builtin_ctz(word);
	return 0;
}
#endif

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_ATSC_SW_Init.
 * software initialization function for VSB/QAM/ISDBT/ATSC3.0
 *  Used to initialize the demodulator
 *
 * @param *frontend		[IN] LX_DEMOD_L2_Context, a pointer to LX_DEMOD_L2_Context context to be initialized
 * @param demodAdd		[IN] int, the I2C address of the demod
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_ATSC_SW_Init (LX_DEMOD_L2_Context * frontend, UINT32 demodAddr)
{
	int retc = NO_DEMOD_ERROR;

	frontend->demod->bIsStandby	= 0;
//	frontend->standard 			= DEMOD_MODULATION_VSB;
	frontend->detected_rf		= 0;
	frontend->centerFrq		= 0;

	frontend->num_PLP_total 	= 0;
	frontend->current_PLP_ID 		= 0;
//	frontend->chipVer				= 0;

	/* Calling underlying SW initialization functions */
	retc =  DEMOD_L1_API_Init (frontend->demod,  demodAddr);
	if (NO_DEMOD_ERROR != retc) {
		DEMOD_ERROR("DEMOD_L1_API_Init() error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc));
	}
	return retc;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_ATSC3_Set_BaseAddr_AXI Address for AXI_memory write.
 * Set Set_Base Address for ATSC3 AXI_memory
 *
 * @param *frontend 			[IN] LX_DEMOD_L2_Context
 * @param baseAddr				[IN] UINT32
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_ATSC3_Set_BaseAddr_AXI (LX_DEMOD_L2_Context *frontend, UINT32 baseAddr)
{
	int retc = NO_DEMOD_ERROR;

	retc = DEMOD_L1_SET_DD_ATSC3_BASEADDR_AXI(frontend->demod, baseAddr);

	if (retc != NO_DEMOD_ERROR) {
		DEMOD_ERROR("FAIL, DEMOD_L1_SET_DD_ATSC3_BASEADDR_AXI() BecauseOf %s\n", DEMOD_L1_API_Error_Text(retc));
		return -ERROR_DEMOD_WRITE;
	}

	return retc;
}
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_ATSC_Set_demod
 * sets the demod for locking signals
 *
 * @param *frontend 			[IN] LX_DEMOD_L2_Context
 * @param standard 			[IN] UINT8
 * @param freq 				[IN] UINT32
 * @param tuneMode 			[IN] UINT8
 * @param specInv_Auto_Enable 	[IN] UINT8
 * @param specInv 			[IN] UINT8
 * @param ter_bandwidth_KHz 	[IN] UINT16
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/

int DEMOD_L2_ATSC_Set_demod (LX_DEMOD_L2_Context * frontend
				, UINT8  standard
				, UINT32 freq
				, UINT8  tuneMode
				, UINT8  specInv_Auto_Enable
				, UINT8  specInv
				, UINT16 ter_bandwidth_KHz
				, UINT8  plp0_id
				, UINT8  plp1_id
				, UINT8  plp2_id
				, UINT8  plp3_id)
{
	int retc = NO_DEMOD_ERROR;
	/* startTime is used to measure internal durations. It is set in various places, whenever required */
	UINT32  startTime = DEMOD_L0_system_time();
	UINT32	checkTime = startTime;

	UINT32 calcFrq1 = 0;
	UINT32 calcFrq2 = 0;
	UINT32 calcFrq3 = 0;

	DEMOD_PRINT("###################ATSC(VSB,QAM,ATSC3) TUNE Sequence##################\n");
		
	//frontend->demod->rsp->atsc3_plp_select.sdram_mode_ch_flg = 0;

	frontend->centerFrq= freq;

	frontend->demod->prop->dd_mode.tuneMode 	= tuneMode;
	frontend->demod->prop->dd_mode.specinvauto	= specInv_Auto_Enable;
	frontend->demod->prop->dd_mode.specinv		= specInv;
	frontend->demod->prop->dd_mode.modulation	= standard;
	frontend->demod->prop->dd_mode.bw		= (UINT8)(ter_bandwidth_KHz/1000);

	DEMOD_NOTI("tune %s, mode %s, specInv %s, bw %d MHz\n",
		DEMOD_L1_API_Modulation_Text(standard),
		(tuneMode == DEMOD_PROP_MODE_TUNE_AUTO) ? "Auto scan" : "Normal",
		(specInv_Auto_Enable == DEMOD_PROP_MODE_SPECINVAUTO_AUTO) ? "Auto" : ((specInv == DEMOD_PROP_MODE_SPECINV_INVERSION) ? "Inversion" : "Not Inversion"),
		frontend->demod->prop->dd_mode.bw);
/*
	DEMOD_INFO("relock to %s at %d KHz\n", DEMOD_L1_API_Modulation_Text(standard), freq);
	DEMOD_INFO("Tune Mode = %s\n", (tuneMode == DEMOD_PROP_MODE_TUNE_AUTO) ? "Auto scan" : "Normal");
	DEMOD_INFO("Spectrum Inversion Auto  = %s\n", (specInv_Auto_Enable == DEMOD_PROP_MODE_SPECINVAUTO_AUTO) ? "Auto" : "Manual");

	if(DEMOD_PROP_MODE_SPECINVAUTO_AUTO != specInv_Auto_Enable)
	{
		DEMOD_INFO("Spectrum = %s\n",(specInv == DEMOD_PROP_MODE_SPECINV_INVERSION) ? "Inversion" : "Not Inversion");
	}
	DEMOD_INFO("Bandwidth = %d [MHz]\n", frontend->demod->prop->dd_mode.bw);
*/
	frontend->demod->prop->dd_if_freq.if_freq	=  DEMOD_PROP_IF_FREQ_IF_FREQ_6MHZ; /* (default  6000) */

	/* Setting demod for locking on required standard */
	switch (standard)
	{
		case DEMOD_MODULATION_ATSC3:
		{
			DEMOD_PRINT("Modulation  = ATSC3\n");

			frontend->demod->prop->dd_auto_mode.auto_detect = DEMOD_PROP_AUTO_MODE_DET_ATSC3_ONLY_ENABLE;
			DEMOD_PRINT("DEMOD_PROP_AUTO_MODE_DET_ATSC3_ONLY_ENABLE \n");
			retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_PROP_AUTO_MODE_CODE);
			if(retc != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}

			retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_PROP_MODE_CODE);
			if(retc != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}

			frontend->current_PLP_ID = plp0_id;
			frontend->demod->prop->dd_twocti_mode.twoCtiOn = DEMOD_PROP_TWOCTI_TWOCTI_OFF; // DEFAULT OFF
			retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_PROP_TWOCTI_CODE);
			if(retc != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}
/*
			frontend->demod->prop->dd_atsc3_output_type.type = DEMOD_DD_ATSC3_OUTPUT_TYPE_B;
			//frontend->demod->prop->dd_atsc3_output_type.type = DEMOD_DD_ATSC3_OUTPUT_TYPE_DEF;	// TYPE_C

			retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_PROP_ATSC3_OUTPUT_TYPE_CODE);
			if(retc != NO_DEMOD_ERROR)
			{
				DEMOD_ERROR ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}
//*/
			if ((plp0_id & 0xff) == 0xff) // autoscan case
			{
				plp0_id = 0x00;		// plp0 on, id 0
				plp1_id = 0x40;		// plp1 off
				plp2_id = 0x40;		// plp2 off
				plp3_id = 0x40;		// plp3 off

				frontend->current_PLP_ID = 0;
			}
			else
			{
				frontend->current_PLP_ID = plp0_id;
			}

//			memset(&frontend->demod->cmd->atsc3_plp_select, -1, sizeof(DEMOD_REQ_ATSC3_PLP_SELECT_struct));

			retc = DEMOD_L2_ATSC_Set_PLP_Select(frontend, plp0_id, plp1_id, plp2_id, plp3_id);
			if(retc != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT ("DEMOD_L2_ATSC_PLP_Change error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}

		}
		break;

	case DEMOD_MODULATION_VSB:
		{
			frontend->demod->prop->dd_if_freq.if_freq	= DEMOD_PROP_IF_FREQ_IF_FREQ_6MHZ;
			frontend->demod->prop->dd_auto_mode.auto_detect = DEMOD_PROP_AUTO_MODE_DET_VSB_ONLY_ENABLE;
			DEMOD_PRINT("DEMOD_PROP_AUTO_MODE_DET_VSB_ONLY_ENABLE \n");
			retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_PROP_AUTO_MODE_CODE);
			if(retc != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}
		}
		break;
	case DEMOD_MODULATION_QAM :
		{
			frontend->demod->prop->dd_if_freq.if_freq	= DEMOD_PROP_IF_FREQ_IF_FREQ_6MHZ;
		}
		break;
	case DEMOD_MODULATION_ISDBT :
		{

			frontend->demod->prop->dd_if_freq.if_freq	= DEMOD_PROP_IF_FREQ_IF_FREQ_5MHZ;
		}
		break;


	default : /* ATV */
		{
			DEMOD_NOTI("'%d' standard (%s) is not supported\n", standard, DEMOD_L1_API_Modulation_Text(standard));
			return 0;
		}
		break;
	}

	retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_PROP_MODE_CODE);
	if(NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("ERROR DEMOD_L1_Set_Property(DEMOD_PROP_MODE_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}
	retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_PROP_IF_FREQ_CODE);
	if(NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("ERROR DEMOD_L1_Set_Property(DEMOD_PROP_IF_FREQ_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}
	retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_PROP_IF_FREQ_CODE); // 161121 if freq change for change std
	if(retc != NO_DEMOD_ERROR)
	{
		DEMOD_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

	frontend->demod->prop->dd_clk_mode.clk_mode = DEMOD_PROP_CLOCK_MODE_24MHZ;
	retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_PROP_CLOCK_MODE_CODE);
	if(retc != NO_DEMOD_ERROR)
	{
		DEMOD_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

	if(DEMOD_PROP_MODE_TUNE_NORMAL != frontend->demod->prop->dd_mode.tuneMode)
	{
		if(870000 >= freq)
			DEMOD_L0_system_wait(20);
		else
			DEMOD_L0_system_wait(40);
	}

	DEMOD_INFO("tune prepare took %3d ms\n", DEMOD_L0_system_time() - checkTime);
	checkTime = DEMOD_L0_system_time();

	retc = DEMOD_L1_SET_DD_Tune (frontend->demod);
	if(NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("FAIL, DEMOD_L1_SET_DD_Tune() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

	DEMOD_INFO("tune took %3d ms\n", DEMOD_L0_system_time() - checkTime);
	DEMOD_NOTI("total tune took %3d ms\n", DEMOD_L0_system_time() - startTime);

	return retc;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_ATSC_Set_PLP_Select.
 * Selects the PLP ID for ATSC3.0
 *
 * @param *frontend			[IN] LX_DEMOD_L2_Context
 * @param index 				[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_ATSC_Set_PLP_Select(LX_DEMOD_L2_Context *frontend,  UINT8 plp0_id,  UINT8 plp1_id,  UINT8 plp2_id,  UINT8 plp3_id )
{
	int retc = NO_DEMOD_ERROR;

	LX_DEMOD_DD_ATSC3_PLP_INDEX_struct plp_select[4];
	UINT8 two_cti_flag = ((plp0_id >> 7) & 0x01) ? DEMOD_PROP_TWOCTI_TWOCTI_ON : DEMOD_PROP_TWOCTI_TWOCTI_OFF;

	DEMOD_INFO("PLP_Select %02x %02x %02x %02x\n", plp0_id, plp1_id, plp2_id, plp3_id);

	if(two_cti_flag != frontend->demod->prop->dd_twocti_mode.twoCtiOn)
	{
		if(two_cti_flag == 1) {
			frontend->demod->prop->dd_twocti_mode.twoCtiOn = DEMOD_PROP_TWOCTI_TWOCTI_ON;
		} else {
			frontend->demod->prop->dd_twocti_mode.twoCtiOn = DEMOD_PROP_TWOCTI_TWOCTI_OFF;
		}

		retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_PROP_TWOCTI_CODE);
		if(retc != NO_DEMOD_ERROR)
		{
			DEMOD_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
			return retc;
		}

		DEMOD_DEBUG("twocti %u\n", frontend->demod->prop->dd_twocti_mode.twoCtiOn);
	}

	plp_select[0].dec_active_low 	= ((plp0_id & 0x40) > 0) ? 1 : 0;
	plp_select[0].id 				= (plp0_id & 0x3F);
	plp_select[1].dec_active_low 	= ((plp1_id & 0x40) > 0) ? 1 : 0;
	plp_select[1].id 				= (plp1_id & 0x3F);
	plp_select[2].dec_active_low 	= ((plp2_id & 0x40) > 0) ? 1 : 0;
	plp_select[2].id 				= (plp2_id & 0x3F);
	plp_select[3].dec_active_low 	= ((plp3_id & 0x40) > 0) ? 1 : 0;
	plp_select[3].id 				= (plp3_id & 0x3F);

	DEMOD_L2_ATSC_PLP_Change(frontend,  plp_select[0].idval, plp_select[1].idval, plp_select[2].idval, plp_select[3].idval);
	return NO_DEMOD_ERROR;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_ATSC_Get_PLP_Info.
 * gets the PLP infomations
 *
 * @param *frontend			[IN] LX_DEMOD_L2_Context
 * @param index 				[IN] UINT8
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_ATSC_Get_PLP_Info   (LX_DEMOD_L2_Context * frontend, DEMOD_ATSC3_PLP_INFO_T * plpInfo)
{
	int retc = NO_DEMOD_ERROR;

	retc = DEMOD_L1_GET_DD_ATSC3_PLP_Info(frontend->demod);
	if (NO_DEMOD_ERROR != retc) {
		DEMOD_ERROR("DEMOD_L1_GET_DD_ATSC3_PLP_Info error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

	plpInfo->plp_info = frontend->demod->rsp->atsc3_plp_info;

	return NO_DEMOD_ERROR;
}



/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_ATSC_Get_PLP_ID.
 * gets the PLP infomations
 *
 * @param *frontend			[IN] LX_DEMOD_L2_Context
 * @param *pPlpParams		[OUT] LX_DEMOD_L2_MULTI_PLP_ID_T
 * @return if Succeeded - NO_DEMOD_ERROR else-error code
 * @see
 * @author
*/
int DEMOD_L2_ATSC_Get_PLP_ID   (LX_DEMOD_L2_Context *frontend, LX_DEMOD_L2_MULTI_PLP_ID_T *pPlpParams, LX_DEMOD_L2_MULTI_PLP_ID_SEL_T plpSel)
{
	UINT8	index;
	UINT8	PLPCount =0;
	UINT8	plpTotalCount =0;
	int retc = NO_DEMOD_ERROR;
	if(plpSel == NONE_PLP_ID)
	{
		return NO_DEMOD_ERROR;
	}
	retc = DEMOD_L1_GET_DD_ATSC3_PLP_ID(frontend->demod);
	if(retc != NO_DEMOD_ERROR)
    {
        DEMOD_PRINT( "FAIL, DEMOD_L2_ATSC_Get_PLP_ID(return (%d))\n",retc);
        return retc;
    }
	for (index = 0; index <64; index++)
	{
		pPlpParams->plpID[index] = 0;		
	}

	for (index = 0; index <64; index++)
	{
		if((frontend->demod->rsp->atsc3_plp_id.plp_id_flag >> index) & 0x0000000000000001)
		{
			plpTotalCount++;

			if(plpSel == LLS_ONLY_PLP_ID)
			{
				if((frontend->demod->rsp->atsc3_plp_id.lls_valid >> index) & 0x0000000000000001)
				{
					pPlpParams->plpID[PLPCount] =
						(index & 0x3f) |
						(((frontend->demod->rsp->atsc3_plp_id.ti_mode >> index) & 0x01) << 6) |
						(((frontend->demod->rsp->atsc3_plp_id.ldm_mode >> index) &  0x01) << 7);
					DEMOD_PRINT("LLS_ONLY_PLP_ID: PLP #%u, ID %u, LDM %u, TI %u => 0x%02X\n", PLPCount,
					((index & 0x3f)),
					((frontend->demod->rsp->atsc3_plp_id.ldm_mode >> index) & 0x01),
					((frontend->demod->rsp->atsc3_plp_id.ti_mode  >> index) & 0x01),
					pPlpParams->plpID[PLPCount]);
					PLPCount++;
				}
			}
			else if(plpSel == FULL_PLP_ID)
			{
				pPlpParams->plpID[PLPCount] =
					(index & 0x3f) |
					(((frontend->demod->rsp->atsc3_plp_id.ti_mode >> index) & 0x01) << 6) |
					(((frontend->demod->rsp->atsc3_plp_id.ldm_mode >> index) & 0x01) << 7);
				DEMOD_PRINT("FULL_PLP_ID: PLP #%u, ID %u, LDM %u, TI %u => 0x%02X\n", PLPCount,
					((index & 0x3f)),
					((frontend->demod->rsp->atsc3_plp_id.ldm_mode >> index) & 0x01),
					((frontend->demod->rsp->atsc3_plp_id.ti_mode  >> index) & 0x01),
					pPlpParams->plpID[PLPCount]);
				PLPCount++;
			}
			else
			{
				// nothing
			}
		}
	}
	
	if(PLPCount == 0)
	{
		pPlpParams->plpID[0] = frontend->current_PLP_ID;
	}

	pPlpParams->plpCount = PLPCount;
	pPlpParams->plpTotalCount = plpTotalCount;
	DEMOD_PRINT("plp valid %d, total %d\n", PLPCount, plpTotalCount);

	return NO_DEMOD_ERROR;
}

int DEMOD_L2_ATSC_PLP_Change(LX_DEMOD_L2_Context *frontend,  UINT8 plp0_id,  UINT8 plp1_id,  UINT8 plp2_id,  UINT8 plp3_id )
{
	int retc = NO_DEMOD_ERROR;
	int i, j;

	LX_DEMOD_DD_ATSC3_PLP_INDEX_struct next_plp_select[4];
	LX_DEMOD_DD_ATSC3_PLP_INDEX_struct prev_plp_select[4];
	LX_DEMOD_DD_ATSC3_PLP_INDEX_struct temp;
	UINT8 next_plp_en_cnt = 0;
	UINT8 prev_plp_en_cnt = 0;

	next_plp_select[0].idval = plp0_id;
	next_plp_select[1].idval = plp1_id;
	next_plp_select[2].idval = plp2_id;
	next_plp_select[3].idval = plp3_id;

	memcpy(prev_plp_select, frontend->demod->cmd->atsc3_plp_select.plp_dec_idx, sizeof(LX_DEMOD_DD_ATSC3_PLP_INDEX_struct) * DEMOD_ATSC3_PLP_DEC_MAX);

	// count en bit
	for(i = 0; i < DEMOD_ATSC3_PLP_DEC_MAX; i++) {
		next_plp_en_cnt += !next_plp_select[i].dec_active_low;
		prev_plp_en_cnt += !prev_plp_select[i].dec_active_low;
	}

	// sort by plp id
	for(i = 0; i < DEMOD_ATSC3_PLP_DEC_MAX - 1; i++)
	{
		for(j = 0; (j + i) < DEMOD_ATSC3_PLP_DEC_MAX - 1; j++)
		{
			if(next_plp_select[j].id > next_plp_select[j + 1].id)
			{
				temp = next_plp_select[j];
				next_plp_select[j] = next_plp_select[j + 1];
				next_plp_select[j + 1] = temp;
			}
			if(prev_plp_select[j].id > prev_plp_select[j+1].id)
			{
				temp = prev_plp_select[j];
				prev_plp_select[j] = prev_plp_select[j+1];
				prev_plp_select[j+1] = temp;
			}
		}
	}

	if (memcmp(next_plp_select, prev_plp_select, sizeof(LX_DEMOD_DD_ATSC3_PLP_INDEX_struct) * DEMOD_ATSC3_PLP_DEC_MAX) != 0) {
		DEMOD_DEBUG("PLP Changed (memcmp) n %08X, p %08X\n", *((UINT32 *)next_plp_select), *((UINT32 *)prev_plp_select));
		retc =  DEMOD_L1_SET_DD_ATSC3_PLP_Select(frontend->demod, plp0_id, plp1_id, plp2_id, plp3_id);
	} else {
		if (next_plp_en_cnt != prev_plp_en_cnt) {
			DEMOD_DEBUG("PLP Changed (en cnt) n %u, p %u\n", next_plp_en_cnt, prev_plp_en_cnt);
			retc =  DEMOD_L1_SET_DD_ATSC3_PLP_Select(frontend->demod, plp0_id, plp1_id, plp2_id, plp3_id);
		} else {
			for(i = 0; i < DEMOD_ATSC3_PLP_DEC_MAX; i++) {
				if (next_plp_select[i].id != prev_plp_select[i].id) {
					DEMOD_DEBUG("PLP Changed (value changed) n[%d] %u, p[%d] %u\n", i, next_plp_select[i].id, i, prev_plp_select[i].id);
					retc =  DEMOD_L1_SET_DD_ATSC3_PLP_Select(frontend->demod, plp0_id, plp1_id, plp2_id, plp3_id);
					break;
				}
			}
		}
	}

	return retc;
}
