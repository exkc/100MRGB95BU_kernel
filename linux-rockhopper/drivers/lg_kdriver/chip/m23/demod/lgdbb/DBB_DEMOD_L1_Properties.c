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
**  Name:DBB_DEMOD_L1_Properties.c
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
#define DEMOD_TAG "[L1.PROP] "

#include <DBB_DEMOD_typedefs.h>
#include <demod_util.h>

#include "DBB_DEMOD_L1_IPC.h"

#include "DBB_DEMOD_L1_Properties.h"
#include "DBB_DEMOD_L1_Commands.h"

#include "DBB_DEMOD_L1_API.h"

#include "DBB_DEMOD_L1_IPC_Prototypes.h"
#include "DBB_DEMOD_L1_Commands_Prototypes.h"
#include "DBB_DEMOD_L1_Properties_Functions.h"

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_XTENSA)

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)

#endif


/***********************************************************************************************************************
  DEMOD_storeDefaultProperies function
  Use:        property preparation function
              Used to fill the prop structure with user values.
  Parameter: *prop    a property structure to be filled

  Returns:    void
 ***********************************************************************************************************************/
void DEMOD_L1_Store_User_Properies (LX_DEMOD_L1_PropObj * prop)
{

#ifdef    DEMOD_PROP_BER_RESOL
	prop->dd_ber_resol.exp =  DEMOD_PROP_BER_RESOL_EXP_EXPLO_7; /* (default 7) */
#endif /* DEMOD_PROP_BER_RESOL */

#ifdef    DEMOD_PROP_IF_FREQ
	prop->dd_if_freq.if_freq =  DEMOD_PROP_IF_FREQ_IF_FREQ_DEFAULT; /* (default 6000) */
#endif /* DEMOD_DD_IF_INPUT_FREQ_PROP */

#ifdef    DEMOD_PROP_CLOCK_MODE
	prop->dd_clk_mode.clk_mode = DEMOD_PROP_CLOCK_MODE_24MHZ; /* (default : 24MHz) */
#endif /* DEMOD_PROP_CLOCK_MODE */

#ifdef    DEMOD_PROP_MODE
	prop->dd_mode.tuneMode = DEMOD_PROP_MODE_TUNE_DEFAULT; /* (default : NORMAL) */
	prop->dd_mode.specinvauto = DEMOD_PROP_MODE_SPECINVAUTO_MANUAL;
	prop->dd_mode.specinv = DEMOD_PROP_MODE_SPECINV_NORMAL;
	prop->dd_mode.modulation = DEMOD_MODULATION_UNKNOWN;
	prop->dd_mode.bw = DEMOD_PROP_MODE_BW_6MHZ ;
#endif /* DEMOD_PROP_MODE */

#ifdef    DEMOD_PROP_AUTO_MODE
	prop->dd_auto_mode.auto_detect = DEMOD_PROP_AUTO_MODE_DET_DVBT_ONLY_ENABLE ;
#endif /* DEMOD_PROP_AUTO_MODE */

#ifdef    DEMOD_PROP_TS_MODE
	prop->dd_ts_mode.tpMode = DEMOD_PROP_TS_MODE_TPMODE_DEFAULT; //parallel
	prop->dd_ts_mode.tpClkPol = DEMOD_PROP_TS_MODE_TPCLKPOL_DEFAULT;
	prop->dd_ts_mode.tpSopPol = DEMOD_PROP_TS_MODE_TPSOPPOL_DEFAULT;
	prop->dd_ts_mode.tpValPol = DEMOD_PROP_TS_MODE_TPVALPOL_DEFAULT;
	prop->dd_ts_mode.tpErrPol = DEMOD_PROP_TS_MODE_TPERRPOL_DEFAULT;
	prop->dd_ts_mode.tpClkSup = DEMOD_PROP_TS_MODE_TPCLKSUP_DEFAULT;
	prop->dd_ts_mode.tpMsbFirst = DEMOD_PROP_TS_MODE_TPMSBFST_DEFAULT;
	prop->dd_ts_mode.tpBigEnd = DEMOD_PROP_TS_MODE_TPBIGEND_DEFAULT;
#endif /* DEMOD_PROP_TS_MODE */

#ifdef    DEMOD_PROP_ADC
	prop->dd_adc_sel.adcClkPllSel = DEMOD_PROP_ADC_ADCCLKPLLSEL_DEFAULT;
	prop->dd_adc_sel.adcClk = DEMOD_PROP_ADC_ADCCLK_24MHZ;
#endif /* DEMOD_PROP_ADC */

#ifdef    DEMOD_PROP_CLKPHASE
	prop->dd_clkphase_sel.adSamsel = DEMOD_PROP_CLKPHASE_ADSAMSEL_NORMAL;
	prop->dd_clkphase_sel.adcOutClksel = DEMOD_PROP_CLKPHASE_ADCOUTCLK_NORMAL;
#endif /* DEMOD_PROP_CLKPHASE */

#ifdef    DEMOD_PROP_SDRAM
	prop->dd_sdram_mode.sdRamOn = DEMOD_PROP_SDRAM_SDRAM_UNKNOWN;
#endif /* DEMOD_PROP_SDRAM */

#ifdef    DEMOD_PROP_TWOCTI
	prop->dd_twocti_mode.twoCtiOn = DEMOD_PROP_TWOCTI_TWOCTI_UNKNOWN;
#endif /* DEMOD_PROP_TWOCTI */

#ifdef	  DEMOD_PROP_SDRAM_PWR
	prop->dd_sdram_pwr.sdRamPwrOn = DEMOD_PROP_SDRAM_PWR_PWR_UNKNOWN;
#endif /* DEMOD_PROP_SDRAM_PWR */

#ifdef	  DEMOD_PROP_ATSC3_OUTPUT_TYPE
	prop->dd_atsc3_output_type.type = DEMOD_DD_ATSC3_OUTPUT_TYPE_DEF;
#endif // DEMOD_PROP_ATSC3_OUTPUT_TYPE


#ifdef    DEMOD_PROP_AGC
	prop->dd_agc.agc_src = DEMOD_PROP_AGC_SRC_INSTANT;
	prop->dd_agc.agc_pol = DEMOD_PROP_AGC_POLARITY_NORMAL;
	prop->dd_agc.agc_outEn = DEMOD_PROP_AGC_OUTEN_ENABLE;
	prop->dd_agc.agc_outEn_S = DEMOD_PROP_AGC_OUTEN_S_ENABLE;
	prop->dd_agc.agc_frzEn = DEMOD_PROP_AGC_FRZ_DISABLE;
	prop->dd_agc.agc_bw = DEMOD_PROP_AGC_BW_DEFAULT;
#endif /* DEMOD_PROP_AGC */

#ifdef    DEMOD_PROP_TPOUT_MODE
	prop->dd_tpout_mode.tpSrMsb = DEMOD_PROP_TPOUT_MODE_TPSRMSB_ENABLE;
	prop->dd_tpout_mode.ssopi = DEMOD_PROP_TPOUT_MODE_SSOPI_DEFAULT;
	prop->dd_tpout_mode.tpOutEn = DEMOD_PROP_TPOUT_MODE_TPOUTEN_ENABLE;
#endif /* DEMOD_PROP_TPOUT_MODE */

#ifdef    DEMOD_PROP_CONSTEL
	prop->dd_constel.constellation = DEMOD_CONSTELLATION_QAM256;
	prop->dd_constel.constel_autodet = DEMOD_PROP_CONSTEL_AUTO_DET_ENABLE;
#endif /* DEMOD_PROP_CONSTEL */

#ifdef    DEMOD_PROP_COUNTRY_GRP //190313
	prop->dd_country_grp.grp =  DEMOD_PROP_COUNTRY_GRP_NONE; /* (default) */
#endif /* DEMOD_PROP_COUNTRY_GRP */

#ifdef    DEMOD_PROP_DVBT_HIERARCHY
	prop->dd_dvbt_hp_sel.hierhpsel = DEMOD_PROP_DVBT_HIERARCHY_HIERHPSEL_HIGH;
#endif /* DEMOD_PROP_DVBT_HIERARCHY */

#ifdef    DEMOD_PROP_DISEQC_CONFIG
	prop->dd_diseqc_config.message_sel = DEMOD_PROP_DISEQC_CONFIG_MESSAGE_SEL_DEFAULT; /* (default : envelop) */
	prop->dd_diseqc_config.diseqc_2_x_enable = DEMOD_PROP_DISEQC_CONFIG_EN_2_X_DISABLE; /* (default disable) */
	prop->dd_diseqc_config.message_repeat_en = DEMOD_PROP_DISEQC_CONFIG_MESSAGE_REPEAT_DEFAULT; /* (default 22000) */
#endif /* DEMOD_PROP_DISEQC_CONFIG */

#ifdef    DEMOD_PROP_DVBT2_MODE
	prop->dd_dvbt2_lock_mode.lock_mode = DEMOD_PROP_DVBT2_MODE_LOCK_MODE_BASE_ONLY;
#endif /* DEMOD_PROP_DVBT2_MODE */

#ifdef    DEMOD_PROP_AFC_RANGE
	prop->dd_dvbs_afc_range.range_khz = DEMOD_PROP_AFC_RANGE_RANGE_KHZ_DEFAULT;
#endif /* DEMOD_PROP_AFC_RANGE */

#ifdef    DEMOD_PROP_DVBS_OPMSEL
	prop->dd_dvbs_opm_sel.opmSel = DEMOD_DD_DVBS_OPM_SEL_PROP_NORMAL_MODE;
#endif /* DEMOD_PROP_DVBS_OPMSEL */

}


/***********************************************************************************************************************
  DEMOD_L1_Compare_N_SetProperty function
  Use:        property set function
              Used to call L1_SET_PROPERTY with the property Id and data provided.
  Parameter: *core     LX_DEMOD_L1_Context
  Parameter: prop     the property Id
  Parameter: data     the property bytes
  Behavior:  This function will only download the property if required.
               Conditions to download the property are:
                - The property changes
                - The propertyWriteMode is set to DEMOD_DOWNLOAD_ALWAYS
                - The property is unknown to DEMOD_L1_Unpack_Property (this may be useful for debug purpose)
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/
int DEMOD_L1_Compare_N_SetProperty (LX_DEMOD_L1_Context * core, UINT32 prop_code, UINT32  data)
{
	UINT32  shadowData;
	int retc;

	retc = DEMOD_L1_Unpack_Property(core->propShadow, prop_code, &shadowData);

	/* -- Download property only if required --     */
	if (((data != shadowData)  || (core->propertyWriteMode == DEMOD_DD_DOWNLOAD_ALWAYS)) & (retc != -ERROR_DEMOD_UNKNOWN_PROPERTY))
	{
		DEMOD_INFO("Setting Property 0x%04x to 0x%04x(%d)\n", prop_code,data,data);

		retc = DEMOD_L1_SET_DD_Prop (core, prop_code, data);
		if (retc != NO_DEMOD_ERROR) {
			DEMOD_ERROR("FAIL, DEMOD_L1_SET_DD_Prop() 0x%04x : %s\n", prop_code, DEMOD_L1_API_Error_Text(retc));
			return retc;
		} else {
			/* Update propShadow with latest data if correctly set */
			DEMOD_L1_Pack_Property   (core->propShadow, prop_code, data);

#ifdef DEMOD_GET_PROPERTY_STRING
			DEMOD_L1_PropertyText(core->propShadow, prop_code);
#endif /* DEMOD_GET_PROPERTY_STRING */
		}
	}

	return retc;
}
/***********************************************************************************************************************
  DEMOD_L1_Get_Unpacked_Property function
  Use:        property get function
              Used to call L1_GET_PROPERTY with the property Id provided.
  Parameter: *core     the LGDBB context
  Parameter: prop     the property Id
  Parameter: *data    a buffer to store the property bytes into
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/
int DEMOD_L1_Get_Unpacked_Property (LX_DEMOD_L1_Context * core, UINT32 prop_code, UINT32  *data)
{
	int retc;
	retc = DEMOD_L1_GET_DD_Prop (core,  prop_code);
	*data = core->rsp->get_property.data;
	return retc;
}
/***********************************************************************************************************************
  DEMOD_L1_Set_Property function
  Use:        Sets the property given the property code.
  Parameter: *core     the LGDBB context
  Parameter: prop     the property Id

  Returns:    NO_DEMOD_ERROR if successful.
 ***********************************************************************************************************************/
int DEMOD_L1_Set_Property (LX_DEMOD_L1_Context * core, UINT32 prop_code)
{
	UINT32  data;
	int retc;

	retc = DEMOD_L1_Unpack_Property(core->prop, prop_code, &data);
	if (retc != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, DEMOD_L1_Unpack_Property() 0x%04x : %s\n", prop_code, DEMOD_L1_API_Error_Text(retc));
		return retc;
	}
	return DEMOD_L1_Compare_N_SetProperty (core, prop_code & 0xffff, data);
}
/***********************************************************************************************************************
  DEMOD_L1_Get_Packed_Property function
  Use:        property get function
              Used to call L1_GET_PROPERTY with the property Id provided.
  Parameter: *core     the LGDBB context
  Parameter: prop     the property Id

  Returns:    NO_DEMOD_ERROR if successful.
 ***********************************************************************************************************************/
int DEMOD_L1_Get_Packed_Property (LX_DEMOD_L1_Context * core, UINT32 prop_code)
{
	UINT32  data;
	int retc;

	retc = DEMOD_L1_Get_Unpacked_Property(core, prop_code & 0xffff, &data);
	if (retc != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, DEMOD_L1_Get_Unpacked_Property() 0x%04x : %s\n", prop_code, DEMOD_L1_API_Error_Text(retc));
		return retc;
	}
	return DEMOD_L1_Pack_Property(core->prop, prop_code, data);

}

/*****************************************************************************************
 NAME: DEMOD_L1_Download_COMMON_Properties
  DESCRIPTION: Setup LGDBB DD properties configuration
  This function will download all the DD configuration properties.
  The function DEMOD_storeDefaultProperies should be called before the first call to this function.
  Parameter:  Pointer to LGDBB Context
  Returns:    I2C transaction error code, NO_DEMOD_ERROR if successful
  Programming Guide Reference:    DD setup flowchart
 ******************************************************************************************/
int DEMOD_L1_Download_COMMON_Properties (LX_DEMOD_L1_Context *core)
{
	//DEMOD_PRINT("DEMOD_L1_Download_COMMON_Properties\n");
	DEMOD_PRINT("Start\n");
	
#ifdef DEMOD_PROP_BER_RESOL
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_BER_RESOL_CODE ) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_BER_RESOL_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_BER_RESOL */

#ifdef DEMOD_PROP_IF_FREQ
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_IF_FREQ_CODE ) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_IF_FREQ_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_IF_FREQ */

#ifdef DEMOD_PROP_MODE
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_MODE_CODE) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_MODE_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_MODE */

#ifdef DEMOD_PROP_AUTO_MODE
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_AUTO_MODE_CODE) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_AUTO_MODE_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_AUTO_MODE */

#ifdef DEMOD_PROP_TS_MODE
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_TS_MODE_CODE) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_TS_MODE_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_TS_MODE */

#ifdef DEMOD_PROP_CLKPHASE
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_CLKPHASE_CODE) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_CLKPHASE_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_CLKPHASE */

#ifdef DEMOD_PROP_SDRAM
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_SDRAM_CODE) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_SDRAM_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_SDRAM */

#ifdef DEMOD_PROP_TWOCTI
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_TWOCTI_CODE) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_TWOCTI_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_TWOCTI */

#ifdef DEMOD_PROP_SDRAM_PWR
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_SDRAM_PWR_CODE) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_SDRAM_PWR_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_SDRAM_PWR */
	
#ifdef	  DEMOD_PROP_ATSC3_OUTPUT_TYPE
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_ATSC3_OUTPUT_TYPE_CODE) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_ATSC3_OUTPUT_TYPECODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif // DEMOD_PROP_ATSC3_OUTPUT_TYPE

#ifdef DEMOD_PROP_AGC
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_AGC_CODE) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_AGC_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_AGC */

#ifdef DEMOD_PROP_TPOUT_MODE
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_TPOUT_MODE_CODE) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_TPOUT_MODE_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_TPOUT_MODE */

#ifdef DEMOD_PROP_CONSTEL
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_CONSTEL_CODE) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_CONSTEL_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_CONSTEL */

#ifdef DEMOD_PROP_COUNTRY_GRP //190313
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_COUNTRY_GRP_CODE) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_COUNTRY_GRP_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_COUNTRY_GRP */

	return NO_DEMOD_ERROR;
}


/*****************************************************************************************
 NAME: DEMOD_L1_Download_DVBC_Properties
  DESCRIPTION: Setup LGDBB DVBC properties configuration
  This function will download all the DVBC configuration properties.
  The function DEMOD_storeDefaultProperies should be called before the first call to this function.
  Parameter:  Pointer to LGDBB Context
  Returns:    I2C transaction error code, NO_DEMOD_ERROR if successful
  Programming Guide Reference:    DVBC setup flowchart
 ******************************************************************************************/
int DEMOD_L1_Download_DVBC_Properties (LX_DEMOD_L1_Context *core)
{
	DEMOD_PRINT("Start\n");

#ifdef DEMOD_PROP_MODE
	core->prop->dd_mode.modulation = DEMOD_MODULATION_DVBC;
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_MODE_CODE) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_MODE_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_MODE */

#ifdef DEMOD_PROP_IF_FREQ
	core->prop->dd_if_freq.if_freq =  DEMOD_PROP_IF_FREQ_IF_FREQ_5MHZ; /* (default 6000) */
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_IF_FREQ_CODE ) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_IF_FREQ_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /*	  DEMOD_PROP_IF_FREQ */


	return NO_DEMOD_ERROR;
}
/*****************************************************************************************
 NAME: DEMOD_L1_Download_DTMB_Properties
  DESCRIPTION: Setup LGDBB DVBC properties configuration
  This function will download all the DVBC configuration properties.
  The function DEMOD_storeDefaultProperies should be called before the first call to this function.
  Parameter:  Pointer to LGDBB Context
  Returns:    I2C transaction error code, NO_DEMOD_ERROR if successful
  Programming Guide Reference:    DVBC setup flowchart
 ******************************************************************************************/
int DEMOD_L1_Download_DTMB_Properties (LX_DEMOD_L1_Context *core)
{
	DEMOD_PRINT("Start\n");

#ifdef DEMOD_PROP_MODE
	core->prop->dd_mode.modulation = DEMOD_MODULATION_DTMB;
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_MODE_CODE) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_MODE_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_MODE */

#ifdef DEMOD_PROP_IF_FREQ
	core->prop->dd_if_freq.if_freq =  DEMOD_PROP_IF_FREQ_IF_FREQ_5MHZ; /* (default	6000) */
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_IF_FREQ_CODE ) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_IF_FREQ_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_IF_FREQ */


	return NO_DEMOD_ERROR;
}


/*****************************************************************************************
 NAME: DEMOD_L1_Download_DVBS_Properties
  DESCRIPTION: Setup LGDBB DVBS properties configuration
  This function will download all the DVBS configuration properties.
  The function DEMOD_storeDefaultProperies should be called before the first call to this function.
  Parameter:  Pointer to LGDBB Context
  Returns:    I2C transaction error code, NO_DEMOD_ERROR if successful
  Programming Guide Reference:    DVBS setup flowchart
 *****************************************************************************************/
int DEMOD_L1_Download_DVBS_Properties (LX_DEMOD_L1_Context *core)
{
	DEMOD_PRINT("Start\n");

#ifdef DEMOD_PROP_MODE
	core->prop->dd_mode.modulation = DEMOD_MODULATION_DVBS;
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_MODE_CODE) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_MODE_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_MODE */

#ifdef DEMOD_PROP_IF_FREQ
	core->prop->dd_if_freq.if_freq = DEMOD_PROP_IF_FREQ_IF_FREQ_0MHZ; /* (default	6000) */
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_IF_FREQ_CODE ) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_IF_FREQ_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /*	  DEMOD_PROP_IF_FREQ */

#if 1
#ifdef DEMOD_PROP_AFC_RANGE
	core->prop->dd_dvbs_afc_range.range_khz = DEMOD_PROP_AFC_RANGE_RANGE_KHZ_DEFAULT;
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_AFC_RANGE_CODE) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_AFC_RANGE_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_AFC_RANGE */

#ifdef DEMOD_PROP_DVBS_OPMSEL
	core->prop->dd_dvbs_opm_sel.opmSel = DEMOD_DD_DVBS_OPM_SEL_PROP_NORMAL_MODE;
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_DVBS_OPMSEL_CODE) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_DVBS_OPMSEL_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_DVBS_OPMSEL */

#ifdef DEMOD_PROP_DISEQC_CONFIG
	core->prop->dd_diseqc_config.message_sel = DEMOD_PROP_DISEQC_CONFIG_MESSAGE_SEL_DEFAULT; /* (default : envelop) */
	core->prop->dd_diseqc_config.diseqc_2_x_enable = DEMOD_PROP_DISEQC_CONFIG_EN_2_X_DISABLE; /* (default disable) */
	core->prop->dd_diseqc_config.message_repeat_en = DEMOD_PROP_DISEQC_CONFIG_MESSAGE_REPEAT_DEFAULT; /* (default 22000) */
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_DISEQC_CONFIG_CODE) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_DISEQC_CONFIG_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_DISEQC_CONFIG */
#endif

	return NO_DEMOD_ERROR;
}

/*****************************************************************************************
 NAME: DEMOD_L1_Download_DVBS2_Properties
  DESCRIPTION: Setup LGDBB DVBS2 properties configuration
  This function will download all the DVBS2 configuration properties.
  The function DEMOD_storeDefaultProperies should be called before the first call to this function.
  Parameter:  Pointer to LGDBB Context
  Returns:    I2C transaction error code, NO_DEMOD_ERROR if successful
  Programming Guide Reference:    DVBS2 setup flowchart
 *****************************************************************************************/
int DEMOD_L1_Download_DVBS2_Properties (LX_DEMOD_L1_Context *core)
{
	DEMOD_PRINT("Start\n");

#ifdef DEMOD_PROP_MODE
	core->prop->dd_mode.modulation = DEMOD_MODULATION_DVBS2;
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_MODE_CODE) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_MODE_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_MODE */

#ifdef DEMOD_PROP_IF_FREQ
	core->prop->dd_if_freq.if_freq =  DEMOD_PROP_IF_FREQ_IF_FREQ_0MHZ; /* (default	6000) */
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_IF_FREQ_CODE ) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_IF_FREQ_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_IF_FREQ */


	return NO_DEMOD_ERROR;
}

/*****************************************************************************************
 NAME: DEMOD_L1_Download_DVBT_Properties
  DESCRIPTION: Setup LGDBB DVBT properties configuration
  This function will download all the DVBT configuration properties.
  The function DEMOD_storeDefaultProperies should be called before the first call to this function.
  Parameter:  Pointer to LGDBB Context
  Returns:    I2C transaction error code, NO_DEMOD_ERROR if successful
  Programming Guide Reference:    DVBT setup flowchart
 ******************************************************************************************/
int DEMOD_L1_Download_DVBT_Properties (LX_DEMOD_L1_Context *core)
{
	DEMOD_PRINT("Start\n");

#ifdef DEMOD_PROP_MODE
	core->prop->dd_mode.modulation = DEMOD_MODULATION_DVBT;
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_MODE_CODE) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_MODE_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_MODE */

#ifdef DEMOD_PROP_IF_FREQ
	core->prop->dd_if_freq.if_freq = DEMOD_PROP_IF_FREQ_IF_FREQ_5MHZ; /* (default  6000) */
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_IF_FREQ_CODE ) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_IF_FREQ_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_IF_FREQ */

#if 1
#ifdef DEMOD_PROP_DVBT_HIERARCHY
	core->prop->dd_dvbt_hp_sel.hierhpsel = DEMOD_PROP_DVBT_HIERARCHY_HIERHPSEL_HIGH;
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_DVBT_HIERARCHY_CODE) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_DVBT_HIERARCHY_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_DVBT_HIERARCHY */
#endif
	return NO_DEMOD_ERROR;
}

/*****************************************************************************************
 NAME: DEMOD_L1_Download_DVBT2_Properties
  DESCRIPTION: Setup LGDBB DVBT2 properties configuration
  This function will download all the DVBT2 configuration properties.
  The function DEMOD_storeDefaultProperies should be called before the first call to this function.
  Parameter:  Pointer to LGDBB Context
  Returns:    I2C transaction error code, NO_DEMOD_ERROR if successful
  Programming Guide Reference:    DVBT2 setup flowchart
 ******************************************************************************************/
int DEMOD_L1_Download_DVBT2_Properties (LX_DEMOD_L1_Context *core)
{
	DEMOD_PRINT("Start\n");

#ifdef DEMOD_PROP_MODE
	core->prop->dd_mode.modulation = DEMOD_MODULATION_DVBT2;
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_MODE_CODE) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_MODE_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_MODE */

#ifdef DEMOD_PROP_DVBT2_MODE
	core->prop->dd_dvbt2_lock_mode.lock_mode = DEMOD_PROP_DVBT2_MODE_LOCK_MODE_BASE_ONLY;
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_DVBT2_MODE_CODE) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_DVBT2_MODE_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_PROP_DVBT2_MODE */

#ifdef DEMOD_PROP_IF_FREQ
	core->prop->dd_if_freq.if_freq =  DEMOD_PROP_IF_FREQ_IF_FREQ_5MHZ; /* (default 6000) */
	if (DEMOD_L1_Set_Property(core, DEMOD_PROP_IF_FREQ_CODE ) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("FAIL, Set to DEMOD_PROP_IF_FREQ_CODE\n");
		return -ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /*	  DEMOD_PROP_IF_FREQ */


	return NO_DEMOD_ERROR;
}

int DEMOD_L1_Download_DVBC2_Properties (LX_DEMOD_L1_Context * core)
{
	DEMOD_PRINT("Start\n");
	return NO_DEMOD_ERROR;
}

int DEMOD_L1_Download_ATSC3_Properties (LX_DEMOD_L1_Context * core)
{
	DEMOD_PRINT("Start\n");
	return NO_DEMOD_ERROR;
}

int DEMOD_L1_Download_All_Properties (LX_DEMOD_L1_Context * core)
{
	DEMOD_L1_Download_COMMON_Properties	(core);

	//DEMOD_L1_Download_DVBC_Properties (core);
	//DEMOD_L1_Download_DVBS_Properties (core);
	//DEMOD_L1_Download_DVBS2_Properties (core);
	//DEMOD_L1_Download_DVBT_Properties (core);
	//DEMOD_L1_Download_DVBT2_Properties (core);
	//DEMOD_L1_Download_DVBC2_Properties (core);

	return NO_DEMOD_ERROR;
}
/***********************************************************************************************************************
  DEMOD_L1_Unpack_Property function
  Use:        This function will pack all the members of a property into an integer for the SetProperty function.

  Parameter: *prop          the LGDBB property context
  Parameter:  prop_code     the property Id
  Parameter:  *data         an int to store the property data

  Returns:    NO_DEMOD_ERROR if the property exists.
 ***********************************************************************************************************************/
int DEMOD_L1_Unpack_Property (LX_DEMOD_L1_PropObj * prop, UINT32 prop_code, UINT32 * data)
{
	switch (prop_code) {
#ifdef DEMOD_PROP_BER_RESOL
		case DEMOD_PROP_BER_RESOL_CODE:
			*data = (prop->dd_ber_resol.exp  & DEMOD_PROP_BER_RESOL_EXP_MASK ) << DEMOD_PROP_BER_RESOL_EXP_LSB;
			break;
#endif /* DEMOD_PROP_BER_RESOL */

#ifdef DEMOD_PROP_IF_FREQ
		case DEMOD_PROP_IF_FREQ_CODE:
			*data = (prop->dd_if_freq.if_freq  & DEMOD_PROP_IF_FREQ_IF_FREQ_MASK ) << DEMOD_PROP_IF_FREQ_IF_FREQ_LSB;
			break;
#endif /* DEMOD_PROP_IF_FREQ */

#ifdef DEMOD_PROP_CLOCK_MODE
		case DEMOD_PROP_CLOCK_MODE_CODE:
			*data = (prop->dd_clk_mode.clk_mode  & DEMOD_PROP_CLOCK_MODE_MASK ) << DEMOD_PROP_CLOCK_MODE_LSB;
			break;
#endif /* DEMOD_PROP_CLOCK_MODE */

#ifdef DEMOD_PROP_DVBS_OPMSEL
		case DEMOD_PROP_DVBS_OPMSEL_CODE:
			*data = (prop->dd_dvbs_opm_sel.opmSel  & DEMOD_DD_DVBS_OPM_SEL_PROP_MASK ) << DEMOD_DD_DVBS_OPM_SEL_PROP_LSB;
			break;
#endif /* DEMOD_DD_OPMSEL_PROP */

#ifdef DEMOD_PROP_MODE
		case DEMOD_PROP_MODE_CODE:
			*data = (prop->dd_mode.tuneMode  & DEMOD_PROP_MODE_TUNE_MASK ) << DEMOD_PROP_MODE_TUNE_LSB |
				(prop->dd_mode.specinvauto & DEMOD_PROP_MODE_SPECINVAUTO_MASK) << DEMOD_PROP_MODE_SPECINVAUTO_LSB |
				(prop->dd_mode.specinv    & DEMOD_PROP_MODE_SPECINV_MASK) << DEMOD_PROP_MODE_SPECINV_LSB |
				(prop->dd_mode.modulation & DEMOD_PROP_MODE_MODULATION_MASK) << DEMOD_PROP_MODE_MODULATION_LSB |
				(prop->dd_mode.bw & DEMOD_PROP_MODE_BW_MASK) << DEMOD_PROP_MODE_BW_LSB ;
			break;
#endif /* DEMOD_PROP_MODE */

#ifdef DEMOD_PROP_AUTO_MODE
		case DEMOD_PROP_AUTO_MODE_CODE:
			*data = (prop->dd_auto_mode.auto_detect  & DEMOD_PROP_AUTO_MODE_DETEN_MASK ) << DEMOD_PROP_AUTO_MODE_DETEN_LSB;
			break;
#endif /* DEMOD_PROP_AUTO_MODE */

#ifdef DEMOD_PROP_TS_MODE
		case DEMOD_PROP_TS_MODE_CODE:
			*data = (prop->dd_ts_mode.tpMode		& DEMOD_PROP_TS_MODE_TPMODE_MASK ) 	<< DEMOD_PROP_TS_MODE_TPMODE_LSB 		|
				(prop->dd_ts_mode.tpClkPol	& DEMOD_PROP_TS_MODE_TPCLKPOL_MASK) 	<< DEMOD_PROP_TS_MODE_TPCLKPOL_LSB 	|
				(prop->dd_ts_mode.tpSopPol	& DEMOD_PROP_TS_MODE_TPSOPPOL_MASK) 	<< DEMOD_PROP_TS_MODE_TPSOPPOL_LSB 	|
				(prop->dd_ts_mode.tpValPol	& DEMOD_PROP_TS_MODE_TPVALPOL_MASK) 	<< DEMOD_PROP_TS_MODE_TPVALPOL_LSB 	|
				(prop->dd_ts_mode.tpErrPol	& DEMOD_PROP_TS_MODE_TPERRPOL_MASK) 	<< DEMOD_PROP_TS_MODE_TPERRPOL_LSB 	|
				(prop->dd_ts_mode.tpClkSup	& DEMOD_PROP_TS_MODE_TPCLKSUP_MASK) 	<< DEMOD_PROP_TS_MODE_TPCLKSUP_LSB 	|
				(prop->dd_ts_mode.tpMsbFirst	& DEMOD_PROP_TS_MODE_TPMSBFST_MASK) 	<< DEMOD_PROP_TS_MODE_TPMSBFST_LSB 	|
				(prop->dd_ts_mode.tpBigEnd	& DEMOD_PROP_TS_MODE_TPBIGEND_MASK) 	<< DEMOD_PROP_TS_MODE_TPBIGEND_LSB ;
			break;
#endif /* DEMOD_PROP_TS_MODE */

#ifdef DEMOD_PROP_ADC
		case DEMOD_PROP_ADC_CODE:
			*data = (prop->dd_adc_sel.adcClkPllSel  & DEMOD_PROP_ADC_ADCCLKPLLSEL_MASK ) << DEMOD_PROP_ADC_ADCCLKPLLSEL_LSB	|
				(prop->dd_adc_sel.adcClk		& DEMOD_PROP_ADC_ADCCLK_MASK ) << DEMOD_PROP_ADC_ADCCLK_LSB ;
			break;
#endif /* DEMOD_PROP_ADC */

#ifdef DEMOD_PROP_CLKPHASE
		 case DEMOD_PROP_CLKPHASE_CODE:
					*data =(((prop->dd_clkphase_sel.adSamsel  & DEMOD_PROP_CLKPHASE_ADSAMSEL_MASK ) << DEMOD_PROP_CLKPHASE_ADSAMSEL_LSB)	|
						((prop->dd_clkphase_sel.adcOutClksel  & DEMOD_PROP_CLKPHASE_ADCOUTCLK_MASK ) << DEMOD_PROP_CLKPHASE_ADCOUTCLK_LSB));
		 	break;
#endif /* DEMOD_PROP_CLKPHASE */

#ifdef DEMOD_PROP_SDRAM
		 case DEMOD_PROP_SDRAM_CODE:
				*data = ((prop->dd_sdram_mode.sdRamOn  & DEMOD_PROP_SDRAM_MASK ) << DEMOD_PROP_SDRAM_LSB)	;
		 	break;
#endif /* DEMOD_PROP_SDRAM */

#ifdef DEMOD_PROP_TWOCTI
		 case DEMOD_PROP_TWOCTI_CODE:
				*data = ((prop->dd_twocti_mode.twoCtiOn  & DEMOD_PROP_TWOCTI_MASK ) << DEMOD_PROP_TWOCTI_LSB)	;
		 	break;
#endif /* DEMOD_PROP_TWOCTI */

#ifdef DEMOD_PROP_SDRAM_PWR
		 case DEMOD_PROP_SDRAM_PWR_CODE:
				*data = ((prop->dd_sdram_pwr.sdRamPwrOn  & DEMOD_PROP_SDRAM_PWR_MASK ) << DEMOD_PROP_SDRAM_PWR_LSB)	;
		 	break;
#endif /*     DEMOD_PROP_SDRAM_PWR */

#ifdef	  DEMOD_PROP_ATSC3_OUTPUT_TYPE
		 case DEMOD_PROP_ATSC3_OUTPUT_TYPE_CODE:
			 *data = ((prop->dd_atsc3_output_type.type & DEMOD_PROP_ATSC3_OUTPUT_TYPE_MASK) << DEMOD_PROP_ATSC3_OUTPUT_TYPE_LSB);
			 break;
#endif // DEMOD_PROP_ATSC3_OUTPUT_TYPE

#ifdef DEMOD_PROP_AGC
		case DEMOD_PROP_AGC_CODE:
			*data = (prop->dd_agc.agc_src	& DEMOD_PROP_AGC_SRC_MASK) 	<< DEMOD_PROP_AGC_SRC_LSB	|
				(prop->dd_agc.agc_pol	& DEMOD_PROP_AGC_POL_MASK) 	<< DEMOD_PROP_AGC_POL_LSB	|
				(prop->dd_agc.agc_outEn	& DEMOD_PROP_AGC_OUTEN_MASK ) 	<< DEMOD_PROP_AGC_OUTEN_LSB	|
				(prop->dd_agc.agc_outEn_S	& DEMOD_PROP_AGC_OUTEN_S_MASK ) 	<< DEMOD_PROP_AGC_OUTEN_S_LSB	|
				(prop->dd_agc.agc_frzEn	& DEMOD_PROP_AGC_FRZEN_MASK) 	<< DEMOD_PROP_AGC_FRZEN_LSB	|
				(prop->dd_agc.agc_bw		& DEMOD_PROP_AGC_BW_MASK) 	<< DEMOD_PROP_AGC_BW_LSB	;
			break;
#endif /* DEMOD_PROP_AGC */

#ifdef DEMOD_PROP_TPOUT_MODE
		case DEMOD_PROP_TPOUT_MODE_CODE:
			*data =  (prop->dd_tpout_mode.tpSrMsb	 & DEMOD_PROP_TPOUT_MODE_TPSRMSB_MASK) << DEMOD_PROP_TPOUT_MODE_TPSRMSB_LSB 	|
				(prop->dd_tpout_mode.tpOutEn  & DEMOD_PROP_TPOUT_MODE_TPOUTEN_MASK ) << DEMOD_PROP_TPOUT_MODE_TPOUTEN_LSB;
			break;
#endif /* DEMOD_PROP_TPOUT_MODE */

#ifdef DEMOD_PROP_CONSTEL
		case DEMOD_PROP_CONSTEL_CODE:
			*data = (prop->dd_constel.constellation  & DEMOD_PROP_CONSTEL_CONSTELLATION_MASK ) << DEMOD_PROP_CONSTEL_CONSTELLATION_LSB |
				(prop->dd_constel.constel_autodet & DEMOD_PROP_CONSTEL_AUTO_DET_MASK) << DEMOD_PROP_CONSTEL_AUTO_DET_LSB ;
			break;
#endif /* DEMOD_PROP_CONSTEL */

#ifdef DEMOD_PROP_COUNTRY_GRP //190313
		case DEMOD_PROP_COUNTRY_GRP_CODE:
			*data = (prop->dd_country_grp.grp  & DEMOD_PROP_COUNTRY_GRP_MASK ) << DEMOD_PROP_COUNTRY_GRP_LSB;
			break;
#endif /* DEMOD_PROP_COUNTRY_GRP */

#ifdef DEMOD_PROP_DISEQC_CONFIG
		case DEMOD_PROP_DISEQC_CONFIG_CODE:
			*data = (prop->dd_diseqc_config.message_sel  & DEMOD_PROP_DISEQC_CONFIG_MESSAGE_SEL_MASK ) << DEMOD_PROP_DISEQC_CONFIG_MESSAGE_SEL_LSB |
				(prop->dd_diseqc_config.diseqc_2_x_enable & DEMOD_PROP_DISEQC_CONFIG_EN_2_X_MASK) << DEMOD_PROP_DISEQC_CONFIG_EN_2_X_LSB |
				(prop->dd_diseqc_config.message_repeat_en & DEMOD_PROP_DISEQC_CONFIG_MESSAGE_REPEAT_MASK) << DEMOD_PROP_DISEQC_CONFIG_MESSAGE_REPEAT_LSB ;
			break;
#endif /* DEMOD_PROP_DISEQC_CONFIG */

#ifdef DEMOD_PROP_DVBT_HIERARCHY
		case DEMOD_PROP_DVBT_HIERARCHY_CODE:
			*data = (prop->dd_dvbt_hp_sel.hierhpsel  & DEMOD_PROP_DVBT_HIERARCHY_HIERHPSEL_D_MASK ) << DEMOD_PROP_DVBT_HIERARCHY_HIERHPSEL_D_LSB;
			break;
#endif /* DEMOD_PROP_DVBT_HIERARCHY */

#ifdef DEMOD_PROP_DVBT2_MODE
		case DEMOD_PROP_DVBT2_MODE_CODE:
			*data = (prop->dd_dvbt2_lock_mode.lock_mode  & DEMOD_PROP_DVBT2_MODE_LOCK_MODE_MASK ) << DEMOD_PROP_DVBT2_MODE_LOCK_MODE_LSB;
			break;
#endif /* DEMOD_PROP_DVBT2_MODE */

#ifdef DEMOD_PROP_AFC_RANGE
		case DEMOD_PROP_AFC_RANGE_CODE:
			*data = (prop->dd_dvbs_afc_range.range_khz  & DEMOD_PROP_AFC_RANGE_RANGE_KHZ_MASK ) << DEMOD_PROP_AFC_RANGE_RANGE_KHZ_LSB;
			break;
#endif /* DEMOD_PROP_AFC_RANGE */

		default :
			return -ERROR_DEMOD_UNKNOWN_PROPERTY;
	}

	//DEMOD_PRINT("(%s) prop_code = 0x%x, data = 0x%x !!\n", __FUNCTION__, prop_code, *data);

	return NO_DEMOD_ERROR;
}


/***********************************************************************************************************************
  DEMOD_L1_Pack_Property function
  Use:        This function will unpack all the members of a property from an integer from the GetProperty function.

  Parameter: *prop          the LGDBB property context
  Parameter:  prop_code     the property Id
  Parameter:  data          the property data

  Returns:    NO_DEMOD_ERROR if the property exists.
 ***********************************************************************************************************************/
int DEMOD_L1_Pack_Property (LX_DEMOD_L1_PropObj * prop, UINT32 prop_code, UINT32  data)
{
	switch (prop_code) {
#ifdef DEMOD_PROP_BER_RESOL
		case DEMOD_PROP_BER_RESOL_CODE:
			prop->dd_ber_resol.exp  = (data >> DEMOD_PROP_BER_RESOL_EXP_LSB ) & DEMOD_PROP_BER_RESOL_EXP_MASK;
			break;
#endif /* DEMOD_PROP_BER_RESOL */

#ifdef DEMOD_PROP_IF_FREQ
		case DEMOD_PROP_IF_FREQ_CODE:
			prop->dd_if_freq.if_freq = (data >> DEMOD_PROP_IF_FREQ_IF_FREQ_LSB) & DEMOD_PROP_IF_FREQ_IF_FREQ_MASK;
			break;
#endif /* DEMOD_PROP_IF_FREQ */

#ifdef DEMOD_PROP_CLOCK_MODE
		case DEMOD_PROP_CLOCK_MODE_CODE:
			prop->dd_clk_mode.clk_mode  = (data >> DEMOD_PROP_CLOCK_MODE_LSB ) & DEMOD_PROP_CLOCK_MODE_MASK;
			break;
#endif /* DEMOD_PROP_CLOCK_MODE */

#ifdef DEMOD_PROP_DVBS_OPMSEL
		case DEMOD_PROP_DVBS_OPMSEL_CODE:
			prop->dd_dvbs_opm_sel.opmSel = (data >> DEMOD_DD_DVBS_OPM_SEL_PROP_LSB) & DEMOD_DD_DVBS_OPM_SEL_PROP_MASK;
			break;
#endif /* DEMOD_DD_OPMSEL_PROP */

#ifdef DEMOD_PROP_MODE
		case DEMOD_PROP_MODE_CODE:
			prop->dd_mode.tuneMode = (data >> DEMOD_PROP_MODE_TUNE_LSB) & DEMOD_PROP_MODE_TUNE_MASK;
			prop->dd_mode.specinvauto = (data >> DEMOD_PROP_MODE_SPECINVAUTO_LSB) & DEMOD_PROP_MODE_SPECINVAUTO_MASK;
			prop->dd_mode.specinv = (data >> DEMOD_PROP_MODE_SPECINV_LSB) & DEMOD_PROP_MODE_SPECINV_MASK;
			prop->dd_mode.modulation = (data >> DEMOD_PROP_MODE_MODULATION_LSB) & DEMOD_PROP_MODE_MODULATION_MASK;
			prop->dd_mode.bw = (data >> DEMOD_PROP_MODE_BW_LSB) & DEMOD_PROP_MODE_BW_MASK;
			break;
#endif /* DEMOD_PROP_MODE */

#ifdef DEMOD_PROP_AUTO_MODE
		case DEMOD_PROP_AUTO_MODE_CODE:
			prop->dd_auto_mode.auto_detect = (data >> DEMOD_PROP_AUTO_MODE_DETEN_LSB    ) & DEMOD_PROP_AUTO_MODE_DETEN_MASK ;
			break;
#endif /* DEMOD_PROP_AUTO_MODE */

#ifdef DEMOD_PROP_TS_MODE
		case DEMOD_PROP_TS_MODE_CODE:
			prop->dd_ts_mode.tpMode = (data >> DEMOD_PROP_TS_MODE_TPMODE_LSB) & DEMOD_PROP_TS_MODE_TPMODE_MASK;
			prop->dd_ts_mode.tpClkPol = (data >> DEMOD_PROP_TS_MODE_TPCLKPOL_LSB) & DEMOD_PROP_TS_MODE_TPCLKPOL_MASK;
			prop->dd_ts_mode.tpSopPol = (data >> DEMOD_PROP_TS_MODE_TPSOPPOL_LSB) & DEMOD_PROP_TS_MODE_TPSOPPOL_MASK;
			prop->dd_ts_mode.tpValPol = (data >> DEMOD_PROP_TS_MODE_TPVALPOL_LSB) & DEMOD_PROP_TS_MODE_TPVALPOL_MASK;
			prop->dd_ts_mode.tpErrPol = (data >> DEMOD_PROP_TS_MODE_TPERRPOL_LSB) & DEMOD_PROP_TS_MODE_TPERRPOL_MASK;
			prop->dd_ts_mode.tpClkSup = (data >> DEMOD_PROP_TS_MODE_TPCLKSUP_LSB) & DEMOD_PROP_TS_MODE_TPCLKSUP_MASK;
			prop->dd_ts_mode.tpMsbFirst = (data >> DEMOD_PROP_TS_MODE_TPMSBFST_LSB) & DEMOD_PROP_TS_MODE_TPMSBFST_MASK;
			prop->dd_ts_mode.tpBigEnd = (data >> DEMOD_PROP_TS_MODE_TPBIGEND_LSB) & DEMOD_PROP_TS_MODE_TPBIGEND_MASK ;
			break;
#endif /* DEMOD_PROP_TS_MODE */

#ifdef DEMOD_PROP_ADC
		case DEMOD_PROP_ADC_CODE:
			prop->dd_adc_sel.adcClkPllSel = (data >> DEMOD_PROP_ADC_ADCCLKPLLSEL_LSB) & DEMOD_PROP_ADC_ADCCLKPLLSEL_MASK;
			prop->dd_adc_sel.adcClk = (data >> DEMOD_PROP_ADC_ADCCLK_LSB) & DEMOD_PROP_ADC_ADCCLK_MASK;
			break;
#endif /* DEMOD_PROP_ADC */

#ifdef DEMOD_PROP_CLKPHASE
		case DEMOD_PROP_CLKPHASE_CODE:
			prop->dd_clkphase_sel.adSamsel = (data >> DEMOD_PROP_CLKPHASE_ADSAMSEL_LSB) & DEMOD_PROP_CLKPHASE_ADSAMSEL_MASK;
			prop->dd_clkphase_sel.adcOutClksel = (data >> DEMOD_PROP_CLKPHASE_ADCOUTCLK_LSB) & DEMOD_PROP_CLKPHASE_ADCOUTCLK_MASK;
		 	break;
#endif /* DEMOD_PROP_CLKPHASE */

#ifdef DEMOD_PROP_SDRAM
		case DEMOD_PROP_SDRAM_CODE:
			prop->dd_sdram_mode.sdRamOn = (data >> DEMOD_PROP_SDRAM_LSB) & DEMOD_PROP_SDRAM_MASK;
			break;
#endif /* DEMOD_PROP_SDRAM */

#ifdef DEMOD_PROP_TWOCTI
		case DEMOD_PROP_TWOCTI_CODE:
			prop->dd_twocti_mode.twoCtiOn = (data >> DEMOD_PROP_TWOCTI_LSB) & DEMOD_PROP_TWOCTI_MASK;
		 	break;
#endif /* DEMOD_PROP_TWOCTI */

#ifdef DEMOD_PROP_SDRAM_PWR
		case DEMOD_PROP_SDRAM_PWR_CODE:
			prop->dd_sdram_pwr.sdRamPwrOn = (data >> DEMOD_PROP_SDRAM_PWR_LSB) & DEMOD_PROP_SDRAM_PWR_MASK;
			break;
#endif /* DEMOD_PROP_SDRAM_PWR */

#ifdef	  DEMOD_PROP_ATSC3_OUTPUT_TYPE
		case DEMOD_PROP_ATSC3_OUTPUT_TYPE_CODE:
			 prop->dd_atsc3_output_type.type = (data >> DEMOD_PROP_ATSC3_OUTPUT_TYPE_LSB) & DEMOD_PROP_ATSC3_OUTPUT_TYPE_MASK;
			 break;
#endif // DEMOD_PROP_ATSC3_OUTPUT_TYPE

#ifdef DEMOD_PROP_AGC
		case DEMOD_PROP_AGC_CODE:
			prop->dd_agc.agc_src 	= (data >> DEMOD_PROP_AGC_SRC_LSB) & DEMOD_PROP_AGC_SRC_MASK;
			prop->dd_agc.agc_pol 	= (data >> DEMOD_PROP_AGC_POL_LSB) & DEMOD_PROP_AGC_POL_MASK;
			prop->dd_agc.agc_outEn 	= (data >> DEMOD_PROP_AGC_OUTEN_LSB) & DEMOD_PROP_AGC_OUTEN_MASK;
			prop->dd_agc.agc_outEn_S= (data >> DEMOD_PROP_AGC_OUTEN_S_LSB) & DEMOD_PROP_AGC_OUTEN_S_MASK;
			prop->dd_agc.agc_frzEn 	= (data >> DEMOD_PROP_AGC_FRZEN_LSB) & DEMOD_PROP_AGC_FRZEN_MASK;
			prop->dd_agc.agc_bw 	= (data >> DEMOD_PROP_AGC_BW_LSB) & DEMOD_PROP_AGC_BW_MASK;
			break;
#endif /* DEMOD_PROP_AGC */

#ifdef DEMOD_PROP_TPOUT_MODE
		case DEMOD_PROP_TPOUT_MODE_CODE:
			prop->dd_tpout_mode.tpSrMsb = (data >> DEMOD_PROP_TPOUT_MODE_TPSRMSB_LSB	) &DEMOD_PROP_TPOUT_MODE_TPSRMSB_MASK;
			prop->dd_tpout_mode.tpOutEn = (data >> DEMOD_PROP_TPOUT_MODE_TPOUTEN_LSB    ) & DEMOD_PROP_TPOUT_MODE_TPOUTEN_MASK;
			break;
#endif /* DEMOD_PROP_TPOUT_MODE */

#ifdef DEMOD_PROP_CONSTEL
		case DEMOD_PROP_CONSTEL_CODE:
			prop->dd_constel.constellation = (data >> DEMOD_PROP_CONSTEL_CONSTELLATION_LSB  ) & DEMOD_PROP_CONSTEL_CONSTELLATION_MASK;
			prop->dd_constel.constel_autodet = (data >> DEMOD_PROP_CONSTEL_AUTO_DET_LSB  ) & DEMOD_PROP_CONSTEL_AUTO_DET_MASK;
			break;
#endif /* DEMOD_PROP_CONSTEL */

#ifdef DEMOD_PROP_COUNTRY_GRP //190313
		case DEMOD_PROP_COUNTRY_GRP_CODE:
			prop->dd_country_grp.grp = (data >> DEMOD_PROP_COUNTRY_GRP_LSB  ) & DEMOD_PROP_COUNTRY_GRP_MASK;
			break;
#endif /* DEMOD_PROP_COUNTRY_GRP */

#ifdef DEMOD_PROP_DISEQC_CONFIG
		case DEMOD_PROP_DISEQC_CONFIG_CODE:
			prop->dd_diseqc_config.message_sel = (data >> DEMOD_PROP_DISEQC_CONFIG_MESSAGE_SEL_LSB) & DEMOD_PROP_DISEQC_CONFIG_MESSAGE_SEL_MASK;
			prop->dd_diseqc_config.diseqc_2_x_enable = (data >> DEMOD_PROP_DISEQC_CONFIG_EN_2_X_LSB) & DEMOD_PROP_DISEQC_CONFIG_EN_2_X_MASK;
			prop->dd_diseqc_config.message_repeat_en = (data >> DEMOD_PROP_DISEQC_CONFIG_MESSAGE_REPEAT_LSB) & DEMOD_PROP_DISEQC_CONFIG_MESSAGE_REPEAT_MASK;
			break;
#endif /* DEMOD_PROP_DISEQC_CONFIG */

#ifdef DEMOD_PROP_DVBT_HIERARCHY
		case DEMOD_PROP_DVBT_HIERARCHY_CODE:
			prop->dd_dvbt_hp_sel.hierhpsel = (data >> DEMOD_PROP_DVBT_HIERARCHY_HIERHPSEL_D_LSB    ) & DEMOD_PROP_DVBT_HIERARCHY_HIERHPSEL_D_MASK;
			break;
#endif /* DEMOD_PROP_DVBT_HIERARCHY */

#ifdef DEMOD_PROP_DVBT2_MODE
		case DEMOD_PROP_DVBT2_MODE_CODE:
			prop->dd_dvbt2_lock_mode.lock_mode = (data >> DEMOD_PROP_DVBT2_MODE_LOCK_MODE_LSB) & DEMOD_PROP_DVBT2_MODE_LOCK_MODE_MASK;
			break;
#endif /* DEMOD_PROP_DVBT2_MODE */

#ifdef DEMOD_PROP_AFC_RANGE
		case DEMOD_PROP_AFC_RANGE_CODE:
			prop->dd_dvbs_afc_range.range_khz = (data >> DEMOD_PROP_AFC_RANGE_RANGE_KHZ_LSB) & DEMOD_PROP_AFC_RANGE_RANGE_KHZ_MASK;
			break;
#endif /* DEMOD_PROP_AFC_RANGE */


		default :
			return -ERROR_DEMOD_UNKNOWN_PROPERTY;
	}
	//DEMOD_PRINT("(%s) prop_code = 0x%x, data = 0x%x !!\n", __FUNCTION__, prop_code, data);

	return NO_DEMOD_ERROR;
}
/***********************************************************************************************************************
  DEMOD_L1_Store_Properties_Defaults function
  Use:        property defaults function
              Used to fill the propShadow structure with startup values.
  Parameter: *prop     the DEMOD_PropObject structure

 |---------------------------------------------------------------------------------------------------------------------|
 | Do NOT change this code unless you really know what you're doing!                                                   |
 | It should reflect the part internal property settings after firmware download                                       |
 |---------------------------------------------------------------------------------------------------------------------|

 Returns:    void
 ***********************************************************************************************************************/
void DEMOD_L1_Store_Properties_Defaults (LX_DEMOD_L1_PropObj * prop)
{

#ifdef DEMOD_PROP_BER_RESOL
	prop->dd_ber_resol.exp = DEMOD_PROP_BER_RESOL_EXP_DEFAULT; /* (default 7) */
#endif /* DEMOD_PROP_BER_RESOL */

#ifdef DEMOD_PROP_IF_FREQ
	prop->dd_if_freq.if_freq = DEMOD_PROP_IF_FREQ_IF_FREQ_DEFAULT; /* (default 6000) */
#endif /* DEMOD_DD_IF_INPUT_FREQ_PROP */

#ifdef DEMOD_PROP_CLOCK_MODE
	prop->dd_clk_mode.clk_mode = DEMOD_PROP_CLOCK_MODE_24MHZ; /* (default : 24MHz) */
#endif /* DEMOD_PROP_CLOCK_MODE */

#ifdef DEMOD_PROP_MODE
	prop->dd_mode.tuneMode = DEMOD_PROP_MODE_TUNE_DEFAULT; /* (default : NORMAL) */
	prop->dd_mode.specinvauto = DEMOD_PROP_MODE_SPECINVAUTO_MANUAL;
	prop->dd_mode.specinv = DEMOD_PROP_MODE_SPECINV_NORMAL;
	prop->dd_mode.modulation = DEMOD_MODULATION_UNKNOWN;
	prop->dd_mode.bw = DEMOD_PROP_MODE_BW_6MHZ ;
#endif /* DEMOD_PROP_MODE */

#ifdef DEMOD_PROP_AUTO_MODE
	prop->dd_auto_mode.auto_detect = DEMOD_PROP_AUTO_MODE_DET_DVBT_ONLY_ENABLE ;
#endif /* DEMOD_PROP_AUTO_MODE */

#ifdef DEMOD_PROP_TS_MODE
	prop->dd_ts_mode.tpMode = DEMOD_PROP_TS_MODE_TPMODE_DEFAULT; //parallel
	prop->dd_ts_mode.tpClkPol = DEMOD_PROP_TS_MODE_TPCLKPOL_DEFAULT;
	prop->dd_ts_mode.tpSopPol = DEMOD_PROP_TS_MODE_TPSOPPOL_DEFAULT;
	prop->dd_ts_mode.tpValPol = DEMOD_PROP_TS_MODE_TPVALPOL_DEFAULT;
	prop->dd_ts_mode.tpErrPol = DEMOD_PROP_TS_MODE_TPERRPOL_DEFAULT;
	prop->dd_ts_mode.tpClkSup = DEMOD_PROP_TS_MODE_TPCLKSUP_DEFAULT;
	prop->dd_ts_mode.tpMsbFirst = DEMOD_PROP_TS_MODE_TPMSBFST_DEFAULT;
	prop->dd_ts_mode.tpBigEnd = DEMOD_PROP_TS_MODE_TPBIGEND_DEFAULT;
#endif /* DEMOD_PROP_TS_MODE */

#ifdef DEMOD_PROP_ADC
	prop->dd_adc_sel.adcClkPllSel = DEMOD_PROP_ADC_ADCCLKPLLSEL_DEFAULT;
	prop->dd_adc_sel.adcClk = DEMOD_PROP_ADC_ADCCLK_DEFAULT;
#endif /* DEMOD_PROP_ADC */

#ifdef DEMOD_PROP_CLKPHASE
	prop->dd_clkphase_sel.adSamsel = DEMOD_PROP_CLKPHASE_ADSAMSEL_NORMAL;
	prop->dd_clkphase_sel.adcOutClksel = DEMOD_PROP_CLKPHASE_ADCOUTCLK_NORMAL;
#endif /* DEMOD_PROP_CLKPHASE */

#ifdef DEMOD_PROP_SDRAM
	prop->dd_sdram_mode.sdRamOn = DEMOD_PROP_SDRAM_SDRAM_UNKNOWN;
#endif /* DEMOD_PROP_SDRAM */

#ifdef DEMOD_PROP_TWOCTI
	prop->dd_twocti_mode.twoCtiOn = DEMOD_PROP_TWOCTI_TWOCTI_UNKNOWN;
#endif /* DEMOD_PROP_TWOCTI */

#ifdef DEMOD_PROP_SDRAM_PWR
	prop->dd_sdram_pwr.sdRamPwrOn = DEMOD_PROP_SDRAM_PWR_PWR_UNKNOWN;
#endif /* DEMOD_PROP_SDRAM_PWR */

#ifdef	  DEMOD_PROP_ATSC3_OUTPUT_TYPE
	prop->dd_atsc3_output_type.type = DEMOD_DD_ATSC3_OUTPUT_TYPE_DEF;
#endif // DEMOD_PROP_ATSC3_OUTPUT_TYPE

#ifdef DEMOD_PROP_AGC
	prop->dd_agc.agc_src = DEMOD_PROP_AGC_SRC_INSTANT;
	prop->dd_agc.agc_pol = DEMOD_PROP_AGC_POLARITY_NORMAL;
	prop->dd_agc.agc_outEn = DEMOD_PROP_AGC_OUTEN_ENABLE;
	prop->dd_agc.agc_outEn_S = DEMOD_PROP_AGC_OUTEN_S_ENABLE;
	prop->dd_agc.agc_frzEn = DEMOD_PROP_AGC_FRZ_DISABLE;
	prop->dd_agc.agc_bw = DEMOD_PROP_AGC_BW_DEFAULT;
#endif /* DEMOD_PROP_AGC */

#ifdef DEMOD_PROP_TPOUT_MODE
	prop->dd_tpout_mode.ssopi = DEMOD_PROP_TPOUT_MODE_SSOPI_DEFAULT;
	prop->dd_tpout_mode.tpSrMsb = DEMOD_PROP_TPOUT_MODE_TPSRMSB_ENABLE;
	prop->dd_tpout_mode.tpOutEn = DEMOD_PROP_TPOUT_MODE_TPOUTEN_ENABLE;
#endif /* DEMOD_PROP_TPOUT_MODE */

#ifdef DEMOD_PROP_CONSTEL
	prop->dd_constel.constellation = DEMOD_CONSTELLATION_QAM256;
	prop->dd_constel.constel_autodet = DEMOD_PROP_CONSTEL_AUTO_DET_ENABLE;
#endif /* DEMOD_PROP_CONSTEL */

#ifdef DEMOD_PROP_COUNTRY_GRP //190313
	prop->dd_country_grp.grp =  DEMOD_PROP_COUNTRY_GRP_NONE; /* (default) */
#endif /* DEMOD_PROP_COUNTRY_GRP */

#ifdef DEMOD_PROP_DISEQC_CONFIG
	prop->dd_diseqc_config.message_sel = DEMOD_PROP_DISEQC_CONFIG_MESSAGE_SEL_DEFAULT; /* (default : envelop) */
	prop->dd_diseqc_config.diseqc_2_x_enable = DEMOD_PROP_DISEQC_CONFIG_EN_2_X_DISABLE; /* (default disable) */
	prop->dd_diseqc_config.message_repeat_en = DEMOD_PROP_DISEQC_CONFIG_MESSAGE_REPEAT_DEFAULT; /* (default 22000) */
#endif /* DEMOD_PROP_DISEQC_CONFIG */

#ifdef DEMOD_PROP_DVBT_HIERARCHY
	prop->dd_dvbt_hp_sel.hierhpsel = DEMOD_PROP_DVBT_HIERARCHY_HIERHPSEL_HIGH;
#endif /* DEMOD_PROP_DVBT_HIERARCHY */

#ifdef DEMOD_PROP_DVBT2_MODE
	prop->dd_dvbt2_lock_mode.lock_mode = DEMOD_PROP_DVBT2_MODE_LOCK_MODE_BASE_ONLY;
#endif /* DEMOD_PROP_DVBT2_MODE */

#ifdef DEMOD_PROP_AFC_RANGE
	prop->dd_dvbs_afc_range.range_khz = DEMOD_PROP_AFC_RANGE_RANGE_KHZ_DEFAULT;
#endif /* DEMOD_PROP_AFC_RANGE */

#ifdef DEMOD_PROP_DVBS_OPMSEL
	prop->dd_dvbs_opm_sel.opmSel = DEMOD_DD_DVBS_OPM_SEL_PROP_NORMAL_MODE;
#endif /* DEMOD_PROP_DVBS_OPMSEL */

}

/***********************************************************************************************************************
  DEMOD_L1_PropertyText function
  Use:        property text function
              Used to turn the property data into clear text.
  Parameter: *prop     the DEMOD_PropObject property structure (containing all properties)
  Parameter: prop_code the property Id (used to know which property to use)
  Returns:    NO_DEMOD_ERROR if successful.
 ***********************************************************************************************************************/
int DEMOD_L1_PropertyText (LX_DEMOD_L1_PropObj * prop, UINT32 prop_code)
{
	switch (prop_code)
	{
#ifdef DEMOD_PROP_BER_RESOL
		case DEMOD_PROP_BER_RESOL_CODE:
			DEMOD_NOTI("[PROP] BER Resolution = EXP %d \n", prop->dd_ber_resol.exp);
			break;
#endif /* DEMOD_PROP_BER_RESOL */

#ifdef DEMOD_PROP_IF_FREQ
		case DEMOD_PROP_IF_FREQ_CODE:
			DEMOD_NOTI("[PROP] IF Frequency = %d [KHz] \n", prop->dd_if_freq.if_freq);
			break;
#endif /* DEMOD_PROP_IF_FREQ */

#ifdef DEMOD_PROP_CLOCK_MODE
		case DEMOD_PROP_CLOCK_MODE_CODE:
			//DEMOD_DEBUG("[PROP]  Clock Source   = %s \n", (prop->dd_clk_mode.clk_mode == DEMOD_PROP_CLOCK_MODE_24MHZ) ? "24 MHz" : "20 MHz");
			DEMOD_NOTI("[PROP] Clock  = %s \n",	
					(prop->dd_clk_mode.clk_mode   == DEMOD_PROP_CLOCK_MODE_20MHZ )  ? "20MHz" :
					(prop->dd_clk_mode.clk_mode   == DEMOD_PROP_CLOCK_MODE_22MHZ)   ? "22MHz" :
					(prop->dd_clk_mode.clk_mode   == DEMOD_PROP_CLOCK_MODE_23MHZ)   ? "23MHz" :
					(prop->dd_clk_mode.clk_mode   == DEMOD_PROP_CLOCK_MODE_24MHZ)   ? "24MHz" :
					(prop->dd_clk_mode.clk_mode   == DEMOD_PROP_CLOCK_MODE_25MHZ)   ? "25MHz" :
					(prop->dd_clk_mode.clk_mode   == DEMOD_PROP_CLOCK_MODE_26MHZ)   ? "26MHz" :
					(prop->dd_clk_mode.clk_mode   == DEMOD_PROP_CLOCK_MODE_27MHZ)   ? "27MHz" :
					(prop->dd_clk_mode.clk_mode   == DEMOD_PROP_CLOCK_MODE_28MHZ)   ? "28MHz" :
					(prop->dd_clk_mode.clk_mode   == DEMOD_PROP_CLOCK_MODE_29MHZ)   ? "29MHz" :
					(prop->dd_clk_mode.clk_mode   == DEMOD_PROP_CLOCK_MODE_30MHZ)   ? "30MHz" :
					(prop->dd_clk_mode.clk_mode   == DEMOD_PROP_CLOCK_MODE_40MHZ	)  ? "40MHz" :
					(prop->dd_clk_mode.clk_mode   == DEMOD_PROP_CLOCK_MODE_48MHZ	)  ? "48MHz" :
					(prop->dd_clk_mode.clk_mode   == DEMOD_PROP_CLOCK_MODE_50MHZ	)  ? "50MHz" :
					(prop->dd_clk_mode.clk_mode   == DEMOD_PROP_CLOCK_MODE_60P8MHZ) ? "60.8MHz" :  "UNKNOWN");
			break;
#endif /* DEMOD_PROP_CLOCK_MODE */


#ifdef DEMOD_PROP_MODE
		case DEMOD_PROP_MODE_CODE:
			DEMOD_NOTI("[PROP] Tune mode  = %s \n",(prop->dd_mode.tuneMode   == DEMOD_PROP_MODE_TUNE_AUTO) ?  "AUTO" :
					(prop->dd_mode.tuneMode   == DEMOD_PROP_MODE_TUNE_MANUAL)  ? "MANUAL" :
					(prop->dd_mode.tuneMode   == DEMOD_PROP_MODE_TUNE_FIXED_DATA)  ?  "FIXED_DATA" : "NOMAL");

			DEMOD_NOTI("[PROP] Spectrum Inversion Mode   = %s \n",(prop->dd_mode.specinvauto   == DEMOD_PROP_MODE_SPECINVAUTO_AUTO) ?  "AUTO" :  "NOMAL");
			DEMOD_NOTI("[PROP] Spectrum  = %s \n",(prop->dd_mode.specinv   == DEMOD_PROP_MODE_SPECINV_INVERSION)  ? "Inverted" :  "Normal");

			DEMOD_NOTI("[PROP] Modulation = %s (0x%0x) \n", DEMOD_L1_API_Modulation_Text(prop->dd_mode.modulation), prop->dd_mode.modulation);

			DEMOD_NOTI("[PROP] Band Width  = %s \n",	(prop->dd_mode.bw   == DEMOD_PROP_MODE_BW_5MHZ)  ? "5MHz" :
					(prop->dd_mode.bw   == DEMOD_PROP_MODE_BW_6MHZ)  ? "6MHz" :
					(prop->dd_mode.bw   == DEMOD_PROP_MODE_BW_7MHZ)  ? "7MHz" :
					(prop->dd_mode.bw   == DEMOD_PROP_MODE_BW_8MHZ)  ? "8MHz" :
					(prop->dd_mode.bw   == DEMOD_PROP_MODE_BW_1D7MHZ) ?  "1.7MHz" :  "UNKNOWN");
			break;
#endif /* DEMOD_PROP_MODE */

#ifdef DEMOD_PROP_AUTO_MODE
		case DEMOD_PROP_AUTO_MODE_CODE:
			DEMOD_NOTI("[PROP] Auto mode   = %s \n", (prop->dd_auto_mode.auto_detect   == DEMOD_PROP_AUTO_MODE_DET_DVBT_DVBT2_ENABLE)  ? "DVBT_DVBT2" :
					(prop->dd_auto_mode.auto_detect   == DEMOD_PROP_AUTO_MODE_DET_DVBT_ONLY_ENABLE)  ? "DVBT Only" :
					(prop->dd_auto_mode.auto_detect   == DEMOD_PROP_AUTO_MODE_DET_DVBT2_ONLY_ENABLE)  ? "DVBT2 Only" :
					(prop->dd_auto_mode.auto_detect   == DEMOD_PROP_AUTO_MODE_DET_DVBC_DVBC2_ENABLE)  ? "DVBC_DVBC2" :
					(prop->dd_auto_mode.auto_detect   == DEMOD_PROP_AUTO_MODE_DET_DVBC_ONLY_ENABLE)  ? "DVBC Only" :
					(prop->dd_auto_mode.auto_detect   == DEMOD_PROP_AUTO_MODE_DET_DVBC2_ONLY_ENABLE)  ? "DVBC2 Only" :
					(prop->dd_auto_mode.auto_detect   == DEMOD_PROP_AUTO_MODE_DET_DVBS_DVBS2_ENABLE) ?  "DVBS_DVBS2" :
					(prop->dd_auto_mode.auto_detect   == DEMOD_PROP_AUTO_MODE_DET_DVBS_ONLY_ENABLE)  ? "DVBS Only" :
					(prop->dd_auto_mode.auto_detect   == DEMOD_PROP_AUTO_MODE_DET_DVBS2_ONLY_ENABLE)  ? "DVBS2 Only" :  "UNKNOWN");
			break;
#endif /* DEMOD_PROP_AUTO_MODE */

#ifdef DEMOD_PROP_TS_MODE
		case DEMOD_PROP_TS_MODE_CODE:
			DEMOD_NOTI("[PROP] TP Mode   = %s \n", (prop->dd_ts_mode.tpMode == DEMOD_PROP_TS_MODE_TPMODE_PARALLEL)  ? "Parallel" : "Serial");
			DEMOD_NOTI("[PROP] TP CLK Polarization   = %s \n", (prop->dd_ts_mode.tpClkPol == DEMOD_PROP_TS_MODE_TPCLKPOL_POS_EDGE)  ? "Positive Edge" : "Negative Edge");
			DEMOD_NOTI("[PROP] TP SOP Polarization   = %s \n", (prop->dd_ts_mode.tpSopPol == DEMOD_PROP_TS_MODE_TPSOPPOL_HIGH) ?  "High Active" : "Low Active");
			DEMOD_NOTI("[PROP] TP VAL Polarization  = %s \n", (prop->dd_ts_mode.tpValPol == DEMOD_PROP_TS_MODE_TPVALPOL_HIGH)  ? "High Active" : "Low Active");
			DEMOD_NOTI("[PROP] TP ERR Polarization   = %s \n", (prop->dd_ts_mode.tpErrPol == DEMOD_PROP_TS_MODE_TPERRPOL_HIGH)  ? "High Active" : "Low Active");
			DEMOD_NOTI("[PROP] TP CLK Suppression   = %s \n", (prop->dd_ts_mode.tpClkSup == DEMOD_PROP_TS_MODE_TPCLKSUP_ENABLE)  ? "Enable" : "Disable");
			DEMOD_NOTI("[PROP] TP MSB First   = %s \n", (prop->dd_ts_mode.tpMsbFirst == DEMOD_PROP_TS_MODE_TPMSBFST_ENABLE)  ? "Enable" : "Disable");
			DEMOD_NOTI("[PROP] TP BIG/LITTLE   = %s \n", (prop->dd_ts_mode.tpMsbFirst == DEMOD_PROP_TS_MODE_TPMSBFST_ENABLE)  ? "Big" : "Little");
			break;
#endif /* DEMOD_PROP_TS_MODE */

#ifdef DEMOD_PROP_ADC
		case DEMOD_PROP_ADC_CODE:
			DEMOD_NOTI("[PROP] ADC CLK   = %s \n", (prop->dd_adc_sel.adcClkPllSel == DEMOD_PROP_ADC_ADCCLKPLLSEL_SOC_PLL) ? "SOC PLL" :
					(prop->dd_adc_sel.adcClkPllSel == DEMOD_PROP_ADC_ADCCLKPLLSEL_TUNER_PLL) ?"TUENR PLL" : "XTAL CLOCK");
			DEMOD_NOTI("[PROP] ADC CLK   = %d \n", prop->dd_adc_sel.adcClk);
			break;
#endif /* DEMOD_PROP_ADC */

#ifdef DEMOD_PROP_CLKPHASE
		case DEMOD_PROP_CLKPHASE_CODE:
			DEMOD_NOTI("[PROP] ADSAMSEL   = %s \n", (prop->dd_clkphase_sel.adSamsel == DEMOD_PROP_CLKPHASE_ADSAMSEL_NORMAL) ? "PHASE NORMAL" : "PHASE INVERSION");
			DEMOD_NOTI("[PROP] ADCOUTCLKSEL   = %s \n", (prop->dd_clkphase_sel.adcOutClksel == DEMOD_PROP_CLKPHASE_ADCOUTCLK_NORMAL) ? "PHASE NORMAL" : "PHASE INVERSION");
			break;
#endif /*     DEMOD_PROP_CLKPHASE */

#ifdef DEMOD_PROP_SDRAM
		 case DEMOD_PROP_SDRAM_CODE:
			DEMOD_NOTI("[PROP] SDRAM MODE   = %s \n", (prop->dd_sdram_mode.sdRamOn == DEMOD_PROP_SDRAM_SDRAM_ON) ? "SDRAM ON" : "SDRAM OFF");
	 		break;
#endif /* DEMOD_PROP_SDRAM */

#ifdef DEMOD_PROP_TWOCTI
		case DEMOD_PROP_TWOCTI_CODE:
			DEMOD_NOTI("[PROP] TWO CTI MODE   = %s \n", (prop->dd_twocti_mode.twoCtiOn == DEMOD_PROP_TWOCTI_TWOCTI_ON) ? "TWOCTI ON" : "TWOCTI OFF");
			break;
#endif /* DEMOD_PROP_TWOCTI */

#ifdef DEMOD_PROP_SDRAM_PWR
		case DEMOD_PROP_SDRAM_PWR_CODE:
			DEMOD_NOTI("[PROP] SDRAM PWR MODE   = %s \n", (prop->dd_sdram_pwr.sdRamPwrOn == DEMOD_PROP_SDRAM_PWR_PWR_ON) ? "SDRAM PWR ON" : "SDRAM PWR OFF");
			break;
#endif /*     DEMOD_PROP_SDRAM_PWR */

#ifdef DEMOD_PROP_ATSC3_OUTPUT_TYPE
		case DEMOD_PROP_ATSC3_OUTPUT_TYPE_CODE:
			DEMOD_NOTI("[PROP] ATSC3 OUTPUT TYPE = %s \n", (prop->dd_atsc3_output_type.type == DEMOD_DD_ATSC3_OUTPUT_TYPE_B) ? "B" : "C");
			 break;
#endif // DEMOD_PROP_ATSC3_OUTPUT_TYPE

#ifdef DEMOD_PROP_AGC
		case DEMOD_PROP_AGC_CODE:
			DEMOD_NOTI("[PROP] AGC Source   	= %s \n", (prop->dd_agc.agc_src == DEMOD_PROP_AGC_SRC_INSTANT)  ? "Instant" : "Average");
			DEMOD_NOTI("[PROP] AGC Polarization = %s \n", (prop->dd_agc.agc_pol  == DEMOD_PROP_AGC_POLARITY_NORMAL)  ? "Normal" : "Inverted");
			DEMOD_NOTI("[PROP] AGC Output   	= %s \n", (prop->dd_agc.agc_outEn == DEMOD_PROP_AGC_OUTEN_ENABLE)  ? "Enable" : "Disable");
			DEMOD_NOTI("[PROP] AGC Output_S   	= %s \n", (prop->dd_agc.agc_outEn_S == DEMOD_PROP_AGC_OUTEN_S_ENABLE)  ? "Enable" : "Disable");
			DEMOD_NOTI("[PROP] AGC Freeze  	    = %s \n", (prop->dd_agc.agc_frzEn == DEMOD_PROP_AGC_FRZ_DISABLE)  ? "Disable" : "Enable");
			DEMOD_NOTI("[PROP] AGC Bandwidth    = %d \n", prop->dd_agc.agc_bw );
			break;
#endif /* DEMOD_PROP_AGC */

#ifdef DEMOD_PROP_TPOUT_MODE
		case DEMOD_PROP_TPOUT_MODE_CODE:
			if(prop->dd_mode.modulation == DEMOD_MODULATION_ATSC3)
			{
				DEMOD_NOTI("[PROP] TP SSOPI   = %s \n", (prop->dd_tpout_mode.ssopi == DEMOD_PROP_TPOUT_MODE_SSOPI_1BIT)  ? "1 Bit Mode" : "8 Bit Mode");
				DEMOD_NOTI("[PROP] TP SR MSB   = %s \n", (prop->dd_tpout_mode.tpSrMsb == DEMOD_PROP_TPOUT_MODE_TPSRMSB_DISABLE)  ? "LSB OUT" : "MSB OUT");
			}
			DEMOD_NOTI("[PROP] TP OUT    = %s \n", (prop->dd_tpout_mode.tpOutEn  == DEMOD_PROP_TPOUT_MODE_TPOUTEN_ENABLE)  ? "Enable" : "Disable");
			break;
#endif /* DEMOD_PROP_TPOUT_MODE */

#ifdef DEMOD_PROP_CONSTEL
		case DEMOD_PROP_CONSTEL_CODE:
			DEMOD_NOTI("[PROP] Constellation mode    = %s \n", DEMOD_L1_API_Constellation_Text(prop->dd_constel.constellation));
			DEMOD_NOTI("[PROP] QAM mode Setting type    = %s \n", (prop->dd_constel.constel_autodet  == DEMOD_PROP_CONSTEL_AUTO_DET_ENABLE) ?  "AUTO" : "MANUAL");
			break;
#endif /* DEMOD_PROP_CONSTEL */

#ifdef DEMOD_PROP_COUNTRY_GRP //190313
		case DEMOD_PROP_COUNTRY_GRP_CODE:
			DEMOD_NOTI("[PROP] Country Group    = %s \n", (prop->dd_country_grp.grp   == DEMOD_PROP_COUNTRY_GRP_NONE) ?  "NONE" :
					(prop->dd_country_grp.grp  == DEMOD_PROP_COUNTRY_GRP_EU) ?  "EU" :
					(prop->dd_country_grp.grp  == DEMOD_PROP_COUNTRY_GRP_END) ?  "END" : "UNKNOWN");
			break;
#endif /* DEMOD_PROP_COUNTRY_GRP */

#ifdef DEMOD_PROP_DISEQC_CONFIG
		case DEMOD_PROP_DISEQC_CONFIG_CODE:
			DEMOD_NOTI("[PROP] DISEqC message type = %s \n", (prop->dd_diseqc_config.message_sel == DEMOD_PROP_DISEQC_CONFIG_MESSAGE_SEL_ENVELOPE) ? "Envelope" : "22KHz Tone");
			DEMOD_NOTI("[PROP] DISEqC 2.0 =  %s \n",(prop->dd_diseqc_config.diseqc_2_x_enable  == DEMOD_PROP_DISEQC_CONFIG_EN_2_X_ENABLE) ? " Supported" : "NOT Supported");
			DEMOD_NOTI("[PROP] Message repeat enable = %s\n",(prop->dd_diseqc_config.message_repeat_en  == DEMOD_PROP_DISEQC_CONFIG_MESSAGE_REPEAT_ENABLE) ?  " ON" : "OFF");
			break;
#endif /* DEMOD_PROP_DISEQC_CONFIG */

#ifdef DEMOD_PROP_DVBT_HIERARCHY
		case DEMOD_PROP_DVBT_HIERARCHY_CODE:
			DEMOD_NOTI("[PROP] DVBT HP sel    = %s \n", (prop->dd_dvbt_hp_sel.hierhpsel   == DEMOD_PROP_DVBT_HIERARCHY_HIERHPSEL_HIGH) ?  "Enable" : "Disable");
			break;
#endif /* DEMOD_PROP_DVBT_HIERARCHY */

#ifdef DEMOD_PROP_DVBT2_MODE
		case DEMOD_PROP_DVBT2_MODE_CODE:
			DEMOD_NOTI("[PROP] DVBT2 lock mode    = %s \n", (prop->dd_dvbt2_lock_mode.lock_mode   == DEMOD_PROP_DVBT2_MODE_LOCK_MODE_BASE_ONLY) ?  "ANY" :
					(prop->dd_dvbt2_lock_mode.lock_mode   == DEMOD_PROP_DVBT2_MODE_LOCK_MODE_BASE_ONLY)  ? "BASE Only" :
					(prop->dd_dvbt2_lock_mode.lock_mode   == DEMOD_PROP_DVBT2_MODE_LOCK_MODE_LITE_ONLY)  ? "LITE Only" : "RESERVED");
			break;
#endif /* DEMOD_PROP_DVBT2_MODE */

#ifdef DEMOD_PROP_DVBS_OPMSEL
		case DEMOD_PROP_DVBS_OPMSEL_CODE:
			DEMOD_NOTI("[PROP] DVBS Blind mode type   = %s \n", (prop->dd_dvbs_opm_sel.opmSel  == DEMOD_DD_DVBS_OPM_SEL_PROP_BLIND_SCAN_MODE)  ? "Blind Scan" :
					(prop->dd_dvbs_opm_sel.opmSel  == DEMOD_DD_DVBS_OPM_SEL_PROP_BLIND_LOCK_MODE) ?  "Blind LOCK" : "NORMAL");
			break;
#endif /* DEMOD_PROP_DVBS_OPMSEL */

#ifdef DEMOD_PROP_AFC_RANGE
		case DEMOD_PROP_AFC_RANGE_CODE:
			DEMOD_NOTI("[PROP] DVBS AFC Range  = %d \n", prop->dd_dvbs_afc_range.range_khz );
			break;
#endif /* DEMOD_PROP_AFC_RANGE */

		default :
			return -ERROR_DEMOD_UNKNOWN_PROPERTY;
	}

	return NO_DEMOD_ERROR;


}








