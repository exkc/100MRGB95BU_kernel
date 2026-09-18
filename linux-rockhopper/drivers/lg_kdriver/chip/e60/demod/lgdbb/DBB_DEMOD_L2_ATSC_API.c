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

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
#include <asm/div64.h> //do_div
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
#include <math.h>
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)

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
//	frontend->standard 			= DEMOD_DD_MODE_PROP_MODULATION_VSB;
	frontend->detected_rf		= 0;
	frontend->centerFrq		= 0;

	frontend->num_PLP_total 	= 0;
	frontend->current_PLP_ID 		= 0;
//	frontend->chipVer				= 0;

	frontend->last_plp0 = 0x00;
	frontend->last_plp1 = 0x40;
	frontend->last_plp2 = 0x40;
	frontend->last_plp3 = 0x40;
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
 * DEMOD_L2_ATSC_Set_demod.
 * sets the demod for locking signals
 *
 * @param *frontend			[IN] LX_DEMOD_L2_Context
 * @param standard			[IN] UINT8
 * @param freq				[IN] UINT32
 * @param tuneMode			[IN] UINT8
 * @param specInv_Auto_Enable	[IN] UINT8
 * @param specInv			[IN] UINT8
 * @param ter_bandwidth_KHz	[IN] UINT16
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
				, UINT16 plp_id) {
	int retc = NO_DEMOD_ERROR;
	UINT32 startTime;	    /* startTime is used to measure internal durations. It is set in various places, whenever required						      */
	UINT32 calcFrq1 = 0;
	UINT32 calcFrq2 = 0;
	UINT32 calcFrq3 = 0;
//	UINT8 auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_VSB_ONLY_ENABLE;

	DEMOD_PRINT("###################VSB,QAM ORG TUNE Sequence##################\n");
		
	//frontend->demod->rsp->atsc3_plp_select.sdram_mode_ch_flg = 0;

	startTime = DEMOD_L0_system_time();

	DEMOD_PRINT ("relock to %s at %d\n", DEMOD_L1_API_StandardName(standard), freq);
	frontend->centerFrq= freq;

	frontend->demod->prop->dd_mode.tuneMode 	= tuneMode;
	frontend->demod->prop->dd_mode.specinvauto	= specInv_Auto_Enable;
	frontend->demod->prop->dd_mode.specinv		= specInv;
	frontend->demod->prop->dd_mode.modulation	= standard;
	frontend->demod->prop->dd_mode.bw		= (UINT8)(ter_bandwidth_KHz/1000);

	DEMOD_NOTI("[DEMOD_API] relock to %s at %d KHz\n", DEMOD_L1_API_StandardName(standard), freq);
	DEMOD_NOTI("[DEMOD_API] Tune Mode = %s\n", (tuneMode == DEMOD_DD_MODE_PROP_TUNEMODE_AUTO) ? "Auto scan" : "Normal");
	DEMOD_NOTI("[DEMOD_API] Spectrum Inversion Auto  = %s\n", (specInv_Auto_Enable == DEMOD_DD_MODE_PROP_SPECINV_AUTO) ? "Auto" : "Manual");

	if(DEMOD_DD_MODE_PROP_SPECINV_AUTO != specInv)
	{
		DEMOD_NOTI("[DEMOD_API] Spectrum = %s\n",(specInv == DEMOD_DD_MODE_PROP_SPECINV_INVERSION) ? "Inversion" : "Not Inversion");
	}
	DEMOD_NOTI("[DEMOD_API] Bandwidth = %d [MHz]\n", frontend->demod->prop->dd_mode.bw);

	/* Setting demod for locking on required standard */
	switch (standard)
	{
		case DEMOD_DD_MODE_PROP_MODULATION_ATSC3:
		{
			DEMOD_NOTI("[DEMOD_API] Modulation  = ATSC3\n");

			frontend->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_ATSC3_ONLY_ENABLE;
			DEMOD_PRINT("DEMOD_DD_AUTO_MODE_PROP_DET_ATSC3_ONLY_ENABLE \n");
			retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_AUTO_MODE_PROP);
			if(retc != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}

/* B17C0 - start */
			if((frontend->centerFrq >=177000) && (frontend->centerFrq <= 213000))
			{
				frontend->demod->prop->dd_clk_mode.clk_mode = DEMOD_DD_CLOCK_MODE_PROP_24MHZ;
			}
			else
			{
				calcFrq1 = ((frontend->centerFrq /100)/12);
				calcFrq2 = (((frontend->centerFrq /1000)/12)*10);
				calcFrq3 = calcFrq1 - calcFrq2;
				DEMOD_PRINT ("calcFrq1 = %d, calcFrq2 = %d, calcFrq3 = %d\n", calcFrq1, calcFrq2, calcFrq3 );

				if((calcFrq3 == 2) || (calcFrq3 == 4))
				{
					frontend->demod->prop->dd_clk_mode.clk_mode = DEMOD_DD_CLOCK_MODE_PROP_24MHZ;
				}
				else
				{
					if((frontend->centerFrq >=515000) && (frontend->centerFrq <= 563000))
					{
						frontend->demod->prop->dd_clk_mode.clk_mode = DEMOD_DD_CLOCK_MODE_PROP_26MHZ;
					}
					else
					{
						switch(frontend->centerFrq)
						{
							case 762000:
								frontend->demod->prop->dd_clk_mode.clk_mode = DEMOD_DD_CLOCK_MODE_PROP_24MHZ;
								break;
							case 575000:
							case 599000:
							case 611000:
								frontend->demod->prop->dd_clk_mode.clk_mode = DEMOD_DD_CLOCK_MODE_PROP_27MHZ;
								break;

							case 479000:
							case 587000:
							case 623000:
							case 635000:
								frontend->demod->prop->dd_clk_mode.clk_mode = DEMOD_DD_CLOCK_MODE_PROP_22MHZ;
								break;

							case 85000:
							case 647000:
								frontend->demod->prop->dd_clk_mode.clk_mode = DEMOD_DD_CLOCK_MODE_PROP_26MHZ;
								break;
							
							default :
								frontend->demod->prop->dd_clk_mode.clk_mode = DEMOD_DD_CLOCK_MODE_PROP_25MHZ;
								break;

						}
					}

				}
			}
/* B17C0 - end */
#ifdef DEMOD_DD_CLOCK_MODE_PROP
			frontend->demod->prop->dd_clk_mode.clk_mode	= DEMOD_DD_CLOCK_MODE_PROP_24MHZ;
#endif
			frontend->demod->prop->dd_adc_sel.adcClk	= DEMOD_DD_ADC_PROP_ADCCLK_24MHZ;
			frontend->demod->prop->dd_if_freq.if_freq	= DEMOD_DD_IF_FREQ_PROP_IF_FREQ_6MHZ;
			frontend->demod->cmd->atsc3_plp_select.plp0_id = (UINT8)plp_id;

			if ((plp_id & 0x40) == 0) // plp0_enable
			{
				frontend->demod->cmd->atsc3_plp_select.plp_id_sel_mode = DEMOD_DD_ATSC3_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MANUAL;
				frontend->demod->cmd->atsc3_plp_select.plp0_id = plp_id;
				frontend->current_PLP_ID = (plp_id & 0x3f);
			}
			else if (plp_id == 0xfe) // 0xfe
			{
				frontend->demod->cmd->atsc3_plp_select.plp_id_sel_mode = DEMOD_DD_ATSC3_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MANUAL;
				frontend->demod->cmd->atsc3_plp_select.plp0_id = frontend->demod->last_plp0;
				frontend->current_PLP_ID = frontend->demod->last_plp0;
			}
			else //plp0_disable
			{
				frontend->demod->cmd->atsc3_plp_select.plp_id_sel_mode = DEMOD_DD_ATSC3_PLP_SELECT_CMD_PLP_ID_SEL_MODE_AUTO;
				frontend->demod->cmd->atsc3_plp_select.plp0_id = 0;
				frontend->current_PLP_ID = 0;
			}

			frontend->demod->last_plp0 = 0x40;
			frontend->demod->last_plp1 = 0x40;
			frontend->demod->last_plp2 = 0x40;
			frontend->demod->last_plp3 = 0x40;

			//retc = DEMOD_L2_ATSC_Set_PLP_Select(frontend, plp_id, 0x40, 0x40, 0x40);
			retc = DEMOD_L2_ATSC_PLP_Change(frontend, frontend->demod->cmd->atsc3_plp_select.plp0_id, 0x40, 0x40, 0x40);
			//retc = DEMOD_L1_SET_DD_ATSC3_PLP_Select (frontend->demod, frontend->demod->cmd->atsc3_plp_select.plp0_id, 0x40, 0x40, 0x40);
			if(retc != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT ("DEMOD_L2_ATSC_PLP_Change error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}
		}
		break;

	case DEMOD_DD_MODE_PROP_MODULATION_VSB:
		{
#ifdef DEMOD_DD_CLOCK_MODE_PROP
			frontend->demod->prop->dd_clk_mode.clk_mode	= DEMOD_DD_CLOCK_MODE_PROP_96MHZ;
#endif
			frontend->demod->prop->dd_adc_sel.adcClk	= DEMOD_DD_ADC_PROP_ADCCLK_24MHZ;
			frontend->demod->prop->dd_if_freq.if_freq	= DEMOD_DD_IF_FREQ_PROP_IF_FREQ_6MHZ;
			frontend->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_VSB_ONLY_ENABLE;
			DEMOD_PRINT("DEMOD_DD_AUTO_MODE_PROP_DET_VSB_ONLY_ENABLE \n");
			retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_AUTO_MODE_PROP);
			if(retc != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}
		}
		break;
	case DEMOD_DD_MODE_PROP_MODULATION_QAM :
		{
#ifdef DEMOD_DD_CLOCK_MODE_PROP
			frontend->demod->prop->dd_clk_mode.clk_mode	= DEMOD_DD_CLOCK_MODE_PROP_96MHZ;
#endif
			frontend->demod->prop->dd_adc_sel.adcClk	= DEMOD_DD_ADC_PROP_ADCCLK_24MHZ;
			frontend->demod->prop->dd_if_freq.if_freq	= DEMOD_DD_IF_FREQ_PROP_IF_FREQ_6MHZ;
		}
		break;
	case DEMOD_DD_MODE_PROP_MODULATION_ISDBT :
		{
#ifdef FPGA_CPBOX
#ifdef DEMOD_DD_CLOCK_MODE_PROP
			frontend->demod->prop->dd_clk_mode.clk_mode	= DEMOD_DD_CLOCK_MODE_PROP_20MHZ;
#endif
			frontend->demod->prop->dd_adc_sel.adcClk	= DEMOD_DD_ADC_PROP_ADCCLK_20MHZ;
#else
#ifdef DEMOD_DD_CLOCK_MODE_PROP
			frontend->demod->prop->dd_clk_mode.clk_mode	= DEMOD_DD_CLOCK_MODE_PROP_96MHZ;
#endif
			frontend->demod->prop->dd_adc_sel.adcClk	= DEMOD_DD_ADC_PROP_ADCCLK_24MHZ;
#endif
			frontend->demod->prop->dd_if_freq.if_freq	= DEMOD_DD_IF_FREQ_PROP_IF_FREQ_5MHZ;
		}
		break;


	default : /* ATV */
		{
			DEMOD_NOTI("[DEMOD_API] '%d' standard (%s) is not supported\n", standard, DEMOD_L1_API_StandardName(standard));
			return 0;
		}
		break;
	}

	retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_MODE_PROP_CODE);
	if(NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("[DEMOD_API] ERROR DEMOD_L1_Set_Property(DEMOD_DD_MODE_PROP_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}
#ifdef DEMOD_DD_CLOCK_MODE_PROP
	retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_CLOCK_MODE_PROP_CODE);
	if(NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("[DEMOD_API] ERROR DEMOD_L1_Set_Property(DEMOD_DD_CLOCK_MODE_PROP_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}
#endif
	retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_ADC_PROP_CODE);
	if(NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("[DEMOD_API] ERROR DEMOD_L1_Set_Property(DEMOD_DD_ADC_PROP_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}
	retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_IF_FREQ_PROP_CODE);
	if(NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("[DEMOD_API] ERROR DEMOD_L1_Set_Property(DEMOD_DD_IF_FREQ_PROP_CODE) 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

#if defined(DEMOD_CONFIG_CROSS_PLATFORM)
	/* cpbox */
	retc = DEMOD_L1_SET_DD_Restart (frontend->demod);
	if(NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("DEMOD_L1_SET_DD_Restart error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}
#endif

	if(DEMOD_DD_MODE_PROP_TUNEMODE_NORMAL != frontend->demod->prop->dd_mode.tuneMode)
	{
		if(870000 >= freq)
			DEMOD_L0_system_wait(20);
		else
			DEMOD_L0_system_wait(40);
	}

	startTime = DEMOD_L0_system_time();

	retc = DEMOD_L1_SET_DD_Tune (frontend->demod);
	if(NO_DEMOD_ERROR != retc)
	{
		DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_SET_DD_Tune() 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

	DEMOD_NOTI("[DEMOD_API] DEMOD 'reset' took %3d ms\n", DEMOD_L0_system_time() - startTime);

	return retc;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_L2_ATSC_Set_demod_Expand.
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
int DEMOD_L2_ATSC_Set_demod_Expand   (LX_DEMOD_L2_Context *frontend
										, UINT8  standard
										, UINT32 freq
										, UINT8  tuneMode
										, UINT8  specInv_Auto_Enable
										, UINT8  specInv
										, UINT16  ter_bandwidth_KHz
										//, UINT8  plp_id
										, UINT8  plp0_id
										, UINT8  plp1_id
										, UINT8  plp2_id
										, UINT8  plp3_id

	)
{
	int retc = NO_DEMOD_ERROR;
	UINT32 startTime;           /* startTime is used to measure internal durations. It is set in various places, whenever required                                                */

	DEMOD_PRINT("###################ATSC3_New TUNE Sequence##################\n");

	startTime = DEMOD_L0_system_time();

	DEMOD_PRINT ("relock to %s at %d\n", DEMOD_L1_API_StandardName(standard), freq);
	frontend->centerFrq= freq;

	frontend->demod->prop->dd_mode.tuneMode            = tuneMode;
	frontend->demod->prop->dd_mode.specinvauto         = specInv_Auto_Enable;
	frontend->demod->prop->dd_mode.specinv               = specInv;
	frontend->demod->prop->dd_mode.modulation          = standard;
	frontend->demod->prop->dd_mode.bw                	= (UINT8)(ter_bandwidth_KHz/1000);

	DEMOD_PRINT("Tune Mode = %s\n", (frontend->demod->prop->dd_mode.tuneMode == DEMOD_DD_MODE_PROP_TUNEMODE_AUTO) ? "Auto scan" : "Normal");
	DEMOD_PRINT("Spectrum Inversion Auto  = %s\n", (frontend->demod->prop->dd_mode.specinvauto == DEMOD_DD_MODE_PROP_SPECINV_AUTO) ? "Auto" : "Manual");

	if(frontend->demod->prop->dd_mode.specinvauto != DEMOD_DD_MODE_PROP_SPECINV_AUTO)
	{
		DEMOD_PRINT("Spectrum = %s\n",( frontend->demod->prop->dd_mode.specinv == DEMOD_DD_MODE_PROP_SPECINV_INVERSION) ? "Inversion" : "Not Inversion");
	}
	DEMOD_PRINT("Bandwidth = %d [MHz]\n", frontend->demod->prop->dd_mode.bw);

	/* Setting demod for locking on required standard */

	frontend->demod->prop->dd_if_freq.if_freq	=  DEMOD_DD_IF_FREQ_PROP_IF_FREQ_6MHZ; /* (default  6000) */
	retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_IF_FREQ_PROP_CODE); // 161121 if freq change for change std
	if(retc != NO_DEMOD_ERROR)
	{
		DEMOD_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

	frontend->demod->prop->dd_clk_mode.clk_mode = DEMOD_DD_CLOCK_MODE_PROP_24MHZ;
	retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_CLOCK_MODE_PROP_CODE);
	if(retc != NO_DEMOD_ERROR)
	{
		DEMOD_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

	switch (standard)
	{
		case DEMOD_DD_MODE_PROP_MODULATION_ATSC3:
		{
			DEMOD_PRINT("Modulation  = ATSC3\n");

			frontend->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_ATSC3_ONLY_ENABLE;
			DEMOD_PRINT("DEMOD_DD_AUTO_MODE_PROP_DET_ATSC3_ONLY_ENABLE \n");
			retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_AUTO_MODE_PROP);
			if(retc != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}

			retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_MODE_PROP_CODE);
			if(retc != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}

			//frontend->demod->cmd->atsc3_plp_select.plp0_id = (UINT8)plp_id;
			frontend->demod->cmd->atsc3_plp_select.plp0_id = plp0_id;
			frontend->demod->cmd->atsc3_plp_select.plp1_id = plp1_id;
			frontend->demod->cmd->atsc3_plp_select.plp2_id = plp2_id;
			frontend->demod->cmd->atsc3_plp_select.plp3_id = plp3_id;
			frontend->current_PLP_ID = plp0_id;
/*
			frontend->demod->prop->dd_sdram_pwr.sdRamPwrOn = DEMOD_DD_SDRAM_PWR_PROP_PWR_ON;
			retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_SDRAM_PWR_PROP_CODE);
			if(retc != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}


			frontend->demod->prop->dd_sdram_mode.sdRamOn = DEMOD_DD_SDRAM_PROP_SDRAM_ON;
			retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_SDRAM_PROP_CODE);
			if(retc != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}
*/
			frontend->demod->prop->dd_twocti_mode.twoCtiOn = DEMOD_DD_TWOCTI_PROP_TWOCTI_OFF; // DEFAULT OFF
			retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_TWOCTI_PROP_CODE);
			if(retc != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}

			frontend->demod->rsp->atsc3_plp_select.two_cti_flag_last = 0;
//			frontend->demod->rsp->atsc3_plp_select.sdram_mode_ch_flg = 0;

			if ((plp0_id & 0xff) == 0xff) // autoscan case
			{
				frontend->demod->cmd->atsc3_plp_select.plp_id_sel_mode = DEMOD_DD_ATSC3_PLP_SELECT_CMD_PLP_ID_SEL_MODE_AUTO;
				frontend->demod->cmd->atsc3_plp_select.plp0_id = 0;
				frontend->demod->cmd->atsc3_plp_select.plp1_id = 0x80;
				frontend->demod->cmd->atsc3_plp_select.plp2_id = 0x80;
				frontend->demod->cmd->atsc3_plp_select.plp3_id = 0x80;
				frontend->current_PLP_ID = 0;
				frontend->current_PLP_ID_0 = 0;
				frontend->current_PLP_ID_1 = 0x80;
				frontend->current_PLP_ID_2 = 0x80;
				frontend->current_PLP_ID_3 = 0x80;
			}
			else
			{
				frontend->demod->cmd->atsc3_plp_select.plp_id_sel_mode = DEMOD_DD_ATSC3_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MANUAL;
				frontend->current_PLP_ID = plp0_id;
				frontend->current_PLP_ID_0 = plp0_id;
				frontend->current_PLP_ID_1 = plp1_id;
				frontend->current_PLP_ID_2 = plp2_id;
				frontend->current_PLP_ID_3 = plp3_id;
			}


			frontend->demod->last_plp0 = 0x80;
			frontend->demod->last_plp1 = 0x80;
			frontend->demod->last_plp2 = 0x80;
			frontend->demod->last_plp3 = 0x80;

			retc = DEMOD_L2_ATSC_Set_PLP_Select(frontend, frontend->demod->cmd->atsc3_plp_select.plp0_id, frontend->demod->cmd->atsc3_plp_select.plp1_id, frontend->demod->cmd->atsc3_plp_select.plp2_id, frontend->demod->cmd->atsc3_plp_select.plp3_id);
			if(retc != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT ("DEMOD_L2_ATSC_PLP_Change error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}

		}
		break;

		case DEMOD_DD_MODE_PROP_MODULATION_VSB:
		{

			retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_MODE_PROP_CODE);
			if(retc != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}


#ifdef DEMOD_ATSC_AUTODETECT

			frontend->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_VSB_ATSC3_ENABLE;
			DEMOD_PRINT("DEMOD_DD_AUTO_MODE_PROP_DET_VSB_ATSC3_ENABLE \n");
			retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_AUTO_MODE_PROP);
			if(retc != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}


			if ((plp_id & 0x40) == 0) // plp0_enable
			{
				frontend->demod->cmd->atsc3_plp_select.plp_id_sel_mode = DEMOD_DD_ATSC3_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MANUAL;
				frontend->demod->cmd->atsc3_plp_select.plp0_id = plp_id;
				frontend->current_PLP_ID = (plp_id & 0x3f);
			}
			else if (plp_id == 0xfe) // 0xfe
			{
				frontend->demod->cmd->atsc3_plp_select.plp_id_sel_mode = DEMOD_DD_ATSC3_PLP_SELECT_CMD_PLP_ID_SEL_MODE_MANUAL;
				frontend->demod->cmd->atsc3_plp_select.plp0_id = frontend->demod->last_plp0;
				frontend->current_PLP_ID = frontend->demod->last_plp0;
			}
			else //plp0_disable
			{
				frontend->demod->cmd->atsc3_plp_select.plp_id_sel_mode = DEMOD_DD_ATSC3_PLP_SELECT_CMD_PLP_ID_SEL_MODE_AUTO;
				frontend->demod->cmd->atsc3_plp_select.plp0_id = 0;
				frontend->current_PLP_ID = 0;
			}

			frontend->demod->last_plp0 = 0x40;
			frontend->demod->last_plp1 = 0x40;
			frontend->demod->last_plp2 = 0x40;
			frontend->demod->last_plp3 = 0x40;

			//retc = DEMOD_L2_ATSC_Set_PLP_Select(frontend, plp_id, 0x40, 0x40, 0x40);
			retc = DEMOD_L2_ATSC_PLP_Change(frontend, frontend->demod->cmd->atsc3_plp_select.plp0_id, 0x40, 0x40, 0x40);
			//retc = DEMOD_L1_SET_DD_ATSC3_PLP_Select (frontend->demod, frontend->demod->cmd->atsc3_plp_select.plp0_id, 0x40, 0x40, 0x40);
			if(retc != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT ("DEMOD_L2_ATSC_PLP_Change error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}

#else

			frontend->demod->prop->dd_auto_mode.auto_detect = DEMOD_DD_AUTO_MODE_PROP_DET_VSB_ONLY_ENABLE;
			DEMOD_PRINT("DEMOD_DD_AUTO_MODE_PROP_DET_VSB_ONLY_ENABLE \n");
			retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_AUTO_MODE_PROP);
			if(retc != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}
#endif


		}
		break;
		case DEMOD_DD_MODE_PROP_MODULATION_QAM :
		{

			retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_MODE_PROP_CODE);
			if(retc != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}



		}
		break;



		default : /* ATV */
		{
			DEMOD_PRINT("'%d' standard (%s) is not supported\n", standard, DEMOD_L1_API_StandardName(standard));
			return 0;
		}
		break;
	}


	if(frontend->demod->prop->dd_mode.tuneMode != DEMOD_DD_MODE_PROP_TUNEMODE_NORMAL)
	{
		if(freq <= 870000)
			DEMOD_L0_system_wait(20);
		else
			DEMOD_L0_system_wait(40);

	}

	retc = DEMOD_L1_SET_DD_Tune (frontend->demod);
	if(retc != NO_DEMOD_ERROR)
	{
		DEMOD_PRINT ("DEMOD_L1_SET_DD_Tune error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
		return retc;
	}

	DEMOD_PRINT   ("DEMOD Set_demod took %3d ms\n", DEMOD_L0_system_time() - startTime);

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

	//frontend->demod->rsp->atsc3_plp_select.sdram_mode_ch_flg = 0;
	frontend->demod->rsp->atsc3_plp_select.two_cti_flag = (plp0_id >> 7) & 0x01;

	if(frontend->demod->rsp->atsc3_plp_select.two_cti_flag != frontend->demod->rsp->atsc3_plp_select.two_cti_flag_last)
	{
		if(frontend->demod->rsp->atsc3_plp_select.two_cti_flag == 1)
		{
/*
			frontend->demod->prop->dd_sdram_mode.sdRamOn = DEMOD_DD_SDRAM_PROP_SDRAM_OFF;
			retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_SDRAM_PROP_CODE);
			if(retc != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}
*/
			frontend->demod->prop->dd_twocti_mode.twoCtiOn = DEMOD_DD_TWOCTI_PROP_TWOCTI_ON;
			retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_TWOCTI_PROP_CODE);
			if(retc != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}
		}
		else
		{
/*
			frontend->demod->prop->dd_sdram_mode.sdRamOn = DEMOD_DD_SDRAM_PROP_SDRAM_ON;
			retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_SDRAM_PROP_CODE);
			if(retc != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}
*/
			frontend->demod->prop->dd_twocti_mode.twoCtiOn = DEMOD_DD_TWOCTI_PROP_TWOCTI_OFF;
			retc = DEMOD_L1_Set_Property(frontend->demod, DEMOD_DD_TWOCTI_PROP_CODE);
			if(retc != NO_DEMOD_ERROR)
			{
				DEMOD_PRINT ("DEMOD_L1_Set_Property error 0x%02x: %s\n", retc, DEMOD_L1_API_Error_Text(retc) );
				return retc;
			}
		}
		frontend->demod->rsp->atsc3_plp_select.two_cti_flag_last = frontend->demod->rsp->atsc3_plp_select.two_cti_flag;
		//frontend->demod->rsp->atsc3_plp_select.sdram_mode_ch_flg = 1;

		//DEMOD_L1_SET_DD_Restart(frontend->demod);
	}

	plp0_id = plp0_id & 0xbf;
	plp1_id = plp1_id & 0xbf;
	plp2_id = plp2_id & 0xbf;
	plp3_id = plp3_id & 0xbf;

	DEMOD_L2_ATSC_PLP_Change(frontend,  plp0_id, plp1_id, plp2_id, plp3_id);
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
int DEMOD_L2_ATSC_Get_PLP_Info   (LX_DEMOD_L2_Context * frontend, UINT8 index, LX_DEMOD_L2_ATSC3_PLP_INFO_T * plpInfo)
{
	int retc = NO_DEMOD_ERROR;

	frontend->demod->cmd->atsc3_plp_info.plp_index = index;
	retc = DEMOD_L1_GET_DD_ATSC3_PLP_Info(frontend->demod, frontend->demod->cmd->atsc3_plp_info.plp_index);
	if(NO_DEMOD_ERROR == retc)
	{
		plpInfo->bs_pre_str							= frontend->demod->rsp->atsc3_plp_info.bs_pre_str;
		plpInfo->bs_l1b_mode						= frontend->demod->rsp->atsc3_plp_info.bs_l1b_mode;
		plpInfo->l1b_num_subframes					= frontend->demod->rsp->atsc3_plp_info.l1b_num_subframes; 				
		plpInfo->l1b_pre_num_symbols				= frontend->demod->rsp->atsc3_plp_info.l1b_pre_num_symbols;
		plpInfo->l1d_mode							= frontend->demod->rsp->atsc3_plp_info.l1d_mode;
		plpInfo->subframe_sel						= frontend->demod->rsp->atsc3_plp_info.subframe_sel;
		plpInfo->l1b_num_ofdm_symbols				= frontend->demod->rsp->atsc3_plp_info.l1b_num_ofdm_symbols;
		plpInfo->l1b_sub_fft_size					= frontend->demod->rsp->atsc3_plp_info.l1b_sub_fft_size;		
		plpInfo->l1b_sub_gi							= frontend->demod->rsp->atsc3_plp_info.l1b_sub_gi;
		plpInfo->l1b_reduce_carr					= frontend->demod->rsp->atsc3_plp_info.l1b_reduce_carr;
		plpInfo->l1b_sub_scatt_pp					= frontend->demod->rsp->atsc3_plp_info.l1b_sub_scatt_pp;			
		plpInfo->l1b_sub_scatt_pb					= frontend->demod->rsp->atsc3_plp_info.l1b_sub_scatt_pb;			
		plpInfo->l1b_sub_sbs_first					= frontend->demod->rsp->atsc3_plp_info.l1b_sub_sbs_first;		
		plpInfo->l1b_sub_sbs_last					= frontend->demod->rsp->atsc3_plp_info.l1b_sub_sbs_last;			
		plpInfo->num_plp							= frontend->demod->rsp->atsc3_plp_info.num_plp;
		plpInfo->plpinfo_sel						= frontend->demod->rsp->atsc3_plp_info.plpinfo_sel;
		plpInfo->plp_ti_mode						= frontend->demod->rsp->atsc3_plp_info.plp_ti_mode;
		plpInfo->plp_fec_type						= frontend->demod->rsp->atsc3_plp_info.plp_fec_type;
		plpInfo->plp_mod							= frontend->demod->rsp->atsc3_plp_info.plp_mod;				
		plpInfo->plp_cr								= frontend->demod->rsp->atsc3_plp_info.plp_cr;						
		plpInfo->l1d_ap_mode						= frontend->demod->rsp->atsc3_plp_info.l1d_ap_mode;						
		plpInfo->l1d_segment						= frontend->demod->rsp->atsc3_plp_info.l1d_segment;		

		plpInfo->bs_pre_str_mode					= frontend->demod->rsp->atsc3_plp_info.bs_pre_str_mode;
		plpInfo->bs_minor							= frontend->demod->rsp->atsc3_plp_info.bs_minor;
		plpInfo->easinfo							= frontend->demod->rsp->atsc3_plp_info.easinfo;
		plpInfo->l1d_plp_type						= frontend->demod->rsp->atsc3_plp_info.l1d_plp_type;	// for Mplp 161209
		plpInfo->plpn_layer							= frontend->demod->rsp->atsc3_plp_info.plpn_layer;		// for Mplp 161209
		plpInfo->m2n								= frontend->demod->rsp->atsc3_plp_info.m2n;
		plpInfo->bsr								= frontend->demod->rsp->atsc3_plp_info.bsr;
		plpInfo->bs_sym								= frontend->demod->rsp->atsc3_plp_info.bs_sym;
		plpInfo->frame_mode							= frontend->demod->rsp->atsc3_plp_info.frame_mode;
		plpInfo->plp_fi_mode						= frontend->demod->rsp->atsc3_plp_info.plp_fi_mode;

		/*
		plpInfo->l1d_plp_cti_depth					= frontend->demod->rsp->atsc3_plp_info.l1d_plp_cti_depth;				
		plpInfo->l1d_plp_hti_inter_subframe			= frontend->demod->rsp->atsc3_plp_info.l1d_plp_hti_inter_subframe;		
		plpInfo->l1d_plp_cti_start_row				= frontend->demod->rsp->atsc3_plp_info.l1d_plp_cti_start_row;			
		plpInfo->l1d_plp_hti_num_ti_blocks			= frontend->demod->rsp->atsc3_plp_info.l1d_plp_hti_num_ti_blocks;		
		plpInfo->l1d_plp_hti_num_fec_blocks_max		= frontend->demod->rsp->atsc3_plp_info.l1d_plp_hti_num_fec_blocks_max;	
		plpInfo->l1d_plp_hti_num_fec_blocks			= frontend->demod->rsp->atsc3_plp_info.l1d_plp_hti_num_fec_blocks;		
		plpInfo->l1d_mimo							= frontend->demod->rsp->atsc3_plp_info.l1d_mimo;
		plpInfo->l1d_miso							= frontend->demod->rsp->atsc3_plp_info.l1d_miso;
		*/
	} else {
		return retc;
	}

	DEMOD_NOTI("[DEMOD_API] Plp index = %d\n", index);

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
	UINT8	PLPOnlyCount =0;
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
		frontend->demod->cmd->atsc3_plp_id.plp_index = index;
		if((frontend->demod->rsp->atsc3_plp_id.plp_id_flag >> index) & 0x0000000000000001)
		{
			PLPOnlyCount++;
			if(plpSel == LLS_ONLY_PLP_ID)
			{
				if((frontend->demod->rsp->atsc3_plp_id.lls_valid >> index) & 0x0000000000000001)
				{
					pPlpParams->plpID[PLPCount] = (index & 0x3f) | (((frontend->demod->rsp->atsc3_plp_id.ti_mode >> index)&0x01) << 6) | (((frontend->demod->rsp->atsc3_plp_id.ldm_mode >> index)&0x01) << 7);
				//	DEMOD_PRINT("LLS_ONLY_PLP_ID : pPlpParams->plpID[PLPCount] = %x \n", pPlpParams->plpID[PLPCount]);
					
					PLPCount++;
				}

				else
					continue;
			}
			else if(plpSel == FULL_PLP_ID)
			{
				pPlpParams->plpID[PLPCount] = (index & 0x3f) | (((frontend->demod->rsp->atsc3_plp_id.ti_mode >> index)&0x01) << 6) | (((frontend->demod->rsp->atsc3_plp_id.ldm_mode >> index)&0x01) << 7);
				//DEMOD_PRINT("FULL_PLP_ID : pPlpParams->plpID[PLPCount] = %x \n", pPlpParams->plpID[PLPCount]);
				
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
	pPlpParams->plpTotalCount = PLPOnlyCount;
	DEMOD_NOTI("[DEMOD_API] Valid num_plp = %d\n",PLPCount);

	return NO_DEMOD_ERROR;

}

int DEMOD_L2_ATSC_PLP_Change(LX_DEMOD_L2_Context *frontend,  UINT8 plp0_id,  UINT8 plp1_id,  UINT8 plp2_id,  UINT8 plp3_id )
{
	int i, j, temp, temp1;
	UINT8 num_enable = 0;
	UINT8 num_enable_last = 0;
	UINT8 pure_plpid[4], pure_plpid_last[4];
	int retc = NO_DEMOD_ERROR;

	frontend->last_plp0 = frontend->demod->last_plp0;
	frontend->last_plp1 = frontend->demod->last_plp1;
	frontend->last_plp2 = frontend->demod->last_plp2;
	frontend->last_plp3 = frontend->demod->last_plp3;

	num_enable = ((plp3_id&0x80)>>3) | ((plp2_id&0x80)>>4) | ((plp1_id&0x80)>>5) | ((plp0_id&0x80)>>6);
	num_enable_last = ((frontend->last_plp3&0x80)>>3) | ((frontend->last_plp2&0x80)>>4) | ((frontend->last_plp1&0x80)>>5) | ((frontend->last_plp0&0x80)>>6);

/*
	if(frontend->demod->rsp->atsc3_plp_select.sdram_mode_ch_flg == 1)
	{
		DEMOD_PRINT("SDRAM Mode Changed!!\n");
		retc =  DEMOD_L1_SET_DD_ATSC3_PLP_Select(frontend->demod, plp0_id, plp1_id, plp2_id, plp3_id);
	}
	else */if(num_enable != num_enable_last)
	{
		DEMOD_PRINT("PLP Changed(Enable changed)!!\n");
		retc =  DEMOD_L1_SET_DD_ATSC3_PLP_Select(frontend->demod, plp0_id, plp1_id, plp2_id, plp3_id);
	}
	else
	{
		pure_plpid[0] = plp0_id&0xbf;
		pure_plpid[1] = plp1_id&0xbf;
		pure_plpid[2] = plp2_id&0xbf;
		pure_plpid[3] = plp3_id&0xbf;


		pure_plpid_last[0] = frontend->last_plp0&0xbf;
		pure_plpid_last[1] = frontend->last_plp1&0xbf;
		pure_plpid_last[2] = frontend->last_plp2&0xbf;
		pure_plpid_last[3] = frontend->last_plp3&0xbf;

		for(i=0; i<3; i++)
		{
			for(j=0; (j+i)<3; j++)
			{
				if(pure_plpid[j] > pure_plpid[j+1])
				{
					temp = pure_plpid[j];
					pure_plpid[j] = pure_plpid[j+1];
					pure_plpid[j+1] = temp;
				}
				if(pure_plpid_last[j] > pure_plpid_last[j+1])
				{
					temp1 = pure_plpid_last[j];
					pure_plpid_last[j] = pure_plpid_last[j+1];
					pure_plpid_last[j+1] = temp1;
				}
			}
		}

		for(i=0;i<4;i++)
		{
			if(pure_plpid[i] != pure_plpid_last[i])
			{
				DEMOD_PRINT("PLP Changed!!(value changed)\n");
				retc =  DEMOD_L1_SET_DD_ATSC3_PLP_Select(frontend->demod, plp0_id, plp1_id, plp2_id, plp3_id);
				break;
			}
			else
			{
				retc = NO_DEMOD_ERROR;
			}
		}

	}	
	
	

	return retc;
}
