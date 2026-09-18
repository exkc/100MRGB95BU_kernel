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


/* Before including the headers, define SiLevel and SiTAG */

#include "DBB_DEMOD_typedefs.h"
#include "DBB_DEMOD_L1_API.h"
#include "DBB_DEMOD_L1_Properties_Functions.h"
#include "DBB_DEMOD_L1_Commands_Prototypes.h"

/***********************************************************************************************************************
  DEMOD_storeDefaultProperies function
  Use:        property preparation function
              Used to fill the prop structure with user values.
  Parameter: *prop    a property structure to be filled

  Returns:    void
 ***********************************************************************************************************************/
void	DEMOD_L1_Store_User_Properies    (LX_DEMOD_L1_PropObj   *prop)
{

#ifdef    DEMOD_DD_BER_RESOL_PROP
  	prop->dd_ber_resol.exp							=  DEMOD_DD_BER_RESOL_PROP_EXP_EXPLO_7; /* (default     7) */
#endif /* DEMOD_DD_BER_RESOL_PROP */


#ifdef    DEMOD_DD_IF_FREQ_PROP
  	prop->dd_if_freq.if_freq							=  DEMOD_DD_IF_FREQ_PROP_IF_FREQ_DEFAULT; /* (default  6000) */
#endif /* DEMOD_DD_IF_INPUT_FREQ_PROP */

#ifdef    DEMOD_DD_CLOCK_MODE_PROP
  	prop->dd_clk_mode.clk_mode						= DEMOD_DD_CLOCK_MODE_PROP_24MHZ; /* (default : 24MHz) */
#endif /* DEMOD_DD_CLOCK_MODE_PROP */

#ifdef    DEMOD_DD_MODE_PROP
	prop->dd_mode.tuneMode                                            	= DEMOD_DD_MODE_PROP_TUNEMODE_DEFAULT; /* (default : NORMAL) */
	prop->dd_mode.specinvauto                                         	= DEMOD_DD_MODE_PROP_SPECINV_MANUAL;
	prop->dd_mode.specinv											 	= DEMOD_DD_MODE_PROP_SPECINV_NORMAL;
	prop->dd_mode.modulation                                          	= DEMOD_DD_MODE_PROP_MODULATION_UNKNOWN;
	prop->dd_mode.bw                                              		= DEMOD_DD_MODE_PROP_BW_BW_6MHZ ;
#endif /* DEMOD_DD_MODE_PROP */

#ifdef    DEMOD_DD_AUTO_MODE_PROP
 	prop->dd_auto_mode.auto_detect 					= DEMOD_DD_AUTO_MODE_PROP_DET_DVBT_ONLY_ENABLE ;
#endif /* DEMOD_DD_AUTO_MODE_PROP */

#ifdef    DEMOD_DD_TS_MODE_PROP
	prop->dd_ts_mode.tpMode							= DEMOD_DD_TS_MODE_PROP_TPMODE_DEFAULT; //parallel
	prop->dd_ts_mode.tpClkPol							= DEMOD_DD_TS_MODE_PROP_TPCLKPOL_DEFAULT;
	prop->dd_ts_mode.tpSopPol						= DEMOD_DD_TS_MODE_PROP_TPSOPPOL_DEFAULT;
	prop->dd_ts_mode.tpValPol							= DEMOD_DD_TS_MODE_PROP_TPVALPOL_DEFAULT;
	prop->dd_ts_mode.tpErrPol							= DEMOD_DD_TS_MODE_PROP_TPERRPOL_DEFAULT;
	prop->dd_ts_mode.tpClkSup						= DEMOD_DD_TS_MODE_PROP_TPCLKSUP_DEFAULT;
	prop->dd_ts_mode.tpMsbFirst						= DEMOD_DD_TS_MODE_PROP_TPMSBFST_DEFAULT;
	prop->dd_ts_mode.tpBigEnd						= DEMOD_DD_TS_MODE_PROP_TPBIGEND_DEFAULT;
#endif /* DEMOD_DD_TS_MODE_PROP */

#ifdef    DEMOD_DD_ADC_PROP
       prop->dd_adc_sel.adcClkPllSel 						= DEMOD_DD_ADC_PROP_ADCCLKPLLSEL_DEFAULT;
	   prop->dd_adc_sel.adcClk								= DEMOD_DD_ADC_PROP_ADCCLK_24MHZ;
#endif /* DEMOD_DD_ADC_PROP */

#ifdef    DEMOD_DD_AGC_PROP
	  prop->dd_agc.agc_src  		= DEMOD_DD_AGC_PROP_SRC_INSTANT;
	  prop->dd_agc.agc_pol  		= DEMOD_DD_AGC_PROP_POLARITY_NORMAL;
	  prop->dd_agc.agc_outEn  		= DEMOD_DD_AGC_PROP_OUTEN_ENABLE;
	  prop->dd_agc.agc_outEn_S 		= DEMOD_DD_AGC_PROP_OUTEN_S_ENABLE;
	  prop->dd_agc.agc_frzEn 		= DEMOD_DD_AGC_PROP_FRZ_DISABLE;
	  prop->dd_agc.agc_bw   		= DEMOD_DD_AGC_PROP_BW_DEFAULT;
#endif /* DEMOD_DD_AGC_PROP */

#ifdef    DEMOD_DD_TPOUT_MODE_PROP
	prop->dd_tpout_mode.tpSrMsb						= DEMOD_DD_TPOUT_MODE_PROP_TPSRMSB_ENABLE;
	prop->dd_tpout_mode.tpOutEn 						= DEMOD_DD_TPOUT_MODE_PROP_TPOUTEN_ENABLE;
#endif /* DEMOD_DD_TPOUT_MODE_PROP */

#ifdef    DEMOD_DD_CONSTEL_PROP
       prop->dd_constel.constellation 					= DEMOD_DD_CONSTELATION_PROP_256QAM;
       prop->dd_constel.constel_autodet 				= DEMOD_DD_CONSTELATION_PROP_AUTO_DET_ENABLE;
#endif /* DEMOD_DD_CONSTEL_PROP */

#ifdef    DEMOD_DD_COUNTRY_GRP_PROP //190313
 	prop->dd_country_grp.grp							=  DEMOD_DD_COUNTRY_GRP_PROP_NONE; /* (default) */
#endif /* DEMOD_DD_COUNTRY_GRP_PROP */

#ifndef LG3307_API


#ifdef    DEMOD_DD_DVBT_HIERARCHY_PROP
       prop->dd_dvbt_hp_sel.hierhpsel 					= DEMOD_DD_DVBT_HIERARCHY_PROP_HIERHPSEL_HIGH;
#endif /* DEMOD_DD_DVBT_HIERARCHY_PROP */
	   
#ifdef    DEMOD_DD_DISEQC_CONFIG_PROP
  	prop->dd_diseqc_config.message_sel					= DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_SEL_DEFAULT; /* (default : envelop) */
  	prop->dd_diseqc_config.diseqc_2_x_enable			= DEMOD_DD_DISEQC_CONFIG_PROP_EN_2_X_DISABLE; /* (default disable) */
  	prop->dd_diseqc_config.message_repeat_en			= DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_REPEAT_DEFAULT; /* (default 22000) */
#endif /* DEMOD_DD_DISEQC_CONFIG_PROP */

#ifdef    DEMOD_DD_DVBT2_MODE_PROP
       prop->dd_dvbt2_lock_mode.lock_mode				= DEMOD_DD_DVBT2_MODE_PROP_LOCK_MODE_BASE_ONLY;
#endif /* DEMOD_DD_DVBT2_MODE_PROP */

#ifdef    DEMOD_DD_DVBS_AFC_RANGE_PROP
       prop->dd_dvbs_afc_range.range_khz					= DEMOD_DD_DVBS_AFC_RANGE_PROP_RANGE_KHZ_DEFAULT;
#endif /* DEMOD_DD_DVBS_AFC_RANGE_PROP */

#ifdef    DEMOD_DD_DVBS_OPMSEL_PROP
 	prop->dd_dvbs_opm_sel.opmSel 					= DEMOD_DD_DVBS_OPM_SEL_PROP_NORMAL_MODE;
#endif /* DEMOD_DD_DVBS_OPMSEL_PROP */

#endif

}


/***********************************************************************************************************************
  DEMOD_L1_Compare_N_SetProperty function
  Use:        property set function
              Used to call L1_SET_PROPERTY with the property Id and data provided.
  Parameter: *api     LX_DEMOD_L1_Context
  Parameter: prop     the property Id
  Parameter: data     the property bytes
  Behavior:  This function will only download the property if required.
               Conditions to download the property are:
                - The property changes
                - The propertyWriteMode is set to DEMOD_DOWNLOAD_ALWAYS
                - The property is unknown to DEMOD_L1_Unpack_Property (this may be useful for debug purpose)
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/
UINT8 DEMOD_L1_Compare_N_SetProperty         (LX_DEMOD_L1_Context *api, UINT32 prop_code, UINT32  data)
{
	UINT32  shadowData;
	UINT8  res;

	res = DEMOD_L1_Unpack_Property(api->propShadow, prop_code, &shadowData);
	
   	 /* -- Download property only if required --     */
	if ( ( (data != shadowData)  || (api->propertyWriteMode == DEMOD_DD_DOWNLOAD_ALWAYS) ) & ( res != ERROR_DEMOD_UNKNOWN_PROPERTY ) )
	{
		  DBB_PRINT("DEMOD_L1_Compare_N_SetProperty: Setting Property 0x%04x to 0x%04x(%d)\n", prop_code,data,data);

		  res = DEMOD_L1_SET_DD_Prop (api, prop_code, data);
		  if (res != NO_DEMOD_ERROR)
		  {
			DBB_PRINT("\n Fail, %s:  0x%04x! : %s\n\n", __F__, prop_code, DEMOD_L1_API_Error_Text(res));
			return res;
		  }
		  else
		  {
			/* Update propShadow with latest data if correctly set */
			DEMOD_L1_Pack_Property   (api->propShadow, prop_code, data);

			#ifdef    DEMOD_GET_PROPERTY_STRING
			DEMOD_L1_PropertyText(api->propShadow, prop_code);
			#endif /* DEMOD_GET_PROPERTY_STRING */
		  }
	}

  	return res;

}
/***********************************************************************************************************************
  DEMOD_L1_Get_Unpacked_Property function
  Use:        property get function
              Used to call L1_GET_PROPERTY with the property Id provided.
  Parameter: *api     the LGDBB context
  Parameter: prop     the property Id
  Parameter: *data    a buffer to store the property bytes into
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/
UINT8 DEMOD_L1_Get_Unpacked_Property         (LX_DEMOD_L1_Context *api, UINT32 prop_code, UINT32  *data)
{
    UINT8 res;
    res = DEMOD_L1_GET_DD_Prop (api,  prop_code);
    *data = api->rsp->get_property.data;
    return res;
}
 /***********************************************************************************************************************
  DEMOD_L1_Set_Property function
  Use:        Sets the property given the property code.
  Parameter: *api     the LGDBB context
  Parameter: prop     the property Id

  Returns:    NO_DEMOD_ERROR if successful.
 ***********************************************************************************************************************/
UINT8  DEMOD_L1_Set_Property        (LX_DEMOD_L1_Context *api, UINT32 prop_code)
{
	UINT32  data;
	UINT8 res;

	res = DEMOD_L1_Unpack_Property(api->prop, prop_code, &data);
	if (res != NO_DEMOD_ERROR)
	{
		DBB_PRINT("\n Fail, %s:  0x%04x! : %s\n\n", __F__, prop_code, DEMOD_L1_API_Error_Text(res));
		return res;
	}
	return DEMOD_L1_Compare_N_SetProperty (api, prop_code & 0xffff, data);
  }
 /***********************************************************************************************************************
  DEMOD_L1_Get_Packed_Property function
  Use:        property get function
              Used to call L1_GET_PROPERTY with the property Id provided.
  Parameter: *api     the LGDBB context
  Parameter: prop     the property Id

  Returns:    NO_DEMOD_ERROR if successful.
 ***********************************************************************************************************************/
UINT8 DEMOD_L1_Get_Packed_Property        (LX_DEMOD_L1_Context *api, UINT32 prop_code)
{
	UINT32  data;
	UINT8 res;

	res = DEMOD_L1_Get_Unpacked_Property(api, prop_code & 0xffff, &data);
	if (res != NO_DEMOD_ERROR)
	{
		DBB_PRINT("\n Fail, %s:  0x%04x:  %s\n\n", __F__, prop_code, DEMOD_L1_API_Error_Text(res));
		return res;
	}
	return DEMOD_L1_Pack_Property(api->prop, prop_code, data);

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
UINT8  DEMOD_L1_Download_COMMON_Properties      (LX_DEMOD_L1_Context *api)
{
  	//DBB_PRINT("DEMOD_L1_Download_COMMON_Properties\n");
	#ifdef        DEMOD_DD_BER_RESOL_PROP
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_BER_RESOL_PROP_CODE ) != NO_DEMOD_ERROR)
	{
		DBB_PRINT("NOT Implemented yet\n");
		return ERROR_DEMOD_SENDING_COMMAND;
	}
	#endif /*  DEMOD_DD_BER_RESOL_PROP */

	#ifdef        DEMOD_DD_IF_FREQ_PROP
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_IF_FREQ_PROP_CODE ) != NO_DEMOD_ERROR)
	{
		return ERROR_DEMOD_SENDING_COMMAND;
	}
	#endif /*     DEMOD_DD_IF_FREQ_PROP */

	#ifdef        DEMOD_DD_CLOCK_MODE_PROP
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_CLOCK_MODE_PROP_CODE ) != NO_DEMOD_ERROR)
	{
		return ERROR_DEMOD_SENDING_COMMAND;
	}
	#endif /*     DEMOD_DD_CLOCK_MODE_PROP */

	#ifdef        DEMOD_DD_MODE_PROP
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_MODE_PROP_CODE) != NO_DEMOD_ERROR)
	{
		return ERROR_DEMOD_SENDING_COMMAND;
	}
	#endif /*     DEMOD_DD_MODE_PROP */

	#ifdef        DEMOD_DD_AUTO_MODE_PROP
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_AUTO_MODE_PROP_CODE) != NO_DEMOD_ERROR)
	{
		DBB_PRINT("NOT Implemented yet\n");
		return ERROR_DEMOD_SENDING_COMMAND;
	}
	#endif /*     DEMOD_DD_AUTO_MODE_PROP */

	#ifdef        DEMOD_DD_TS_MODE_PROP
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_TS_MODE_PROP_CODE) != NO_DEMOD_ERROR)
	{
		DBB_PRINT("NOT Implemented yet\n");
		return ERROR_DEMOD_SENDING_COMMAND;
	}
	#endif /*     DEMOD_DD_TS_MODE_PROP */

	#ifdef        DEMOD_DD_ADC_PROP
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_ADC_PROP_CODE) != NO_DEMOD_ERROR)
	{
		DBB_PRINT("NOT Implemented yet\n");
		return ERROR_DEMOD_SENDING_COMMAND;
	}
	#endif /*     DEMOD_DD_ADC_PROP */

	#ifdef    DEMOD_DD_AGC_PROP
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_AGC_PROP_CODE) != NO_DEMOD_ERROR)
	{
		DBB_PRINT("NOT Implemented yet\n");
		return ERROR_DEMOD_SENDING_COMMAND;
	}
	#endif /*     DEMOD_DD_AGC_PROP */

	#ifdef        DEMOD_DD_TPOUT_MODE_PROP
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_TPOUT_MODE_PROP_CODE) != NO_DEMOD_ERROR)
	{
		DBB_PRINT("NOT Implemented yet\n");
		return ERROR_DEMOD_SENDING_COMMAND;
	}
	#endif /*     DEMOD_DD_TPOUT_MODE_PROP */

	#ifdef        DEMOD_DD_CONSTEL_PROP
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_CONSTEL_PROP_CODE) != NO_DEMOD_ERROR)
	{
		DBB_PRINT("NOT Implemented yet\n");
		return ERROR_DEMOD_SENDING_COMMAND;
	}
	#endif /*     DEMOD_DD_CONSTEL_PROP */
	
	#ifdef    DEMOD_DD_COUNTRY_GRP_PROP //190313
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_COUNTRY_GRP_PROP_CODE) != NO_DEMOD_ERROR)
	{
		DBB_PRINT("NOT Implemented yet\n");
		return ERROR_DEMOD_SENDING_COMMAND;
	}
	#endif /* DEMOD_DD_COUNTRY_GRP_PROP */



	return NO_DEMOD_ERROR;

}


#ifndef LG3307_API


/*****************************************************************************************
 NAME: DEMOD_L1_Download_DVBC_Properties
  DESCRIPTION: Setup LGDBB DVBC properties configuration
  This function will download all the DVBC configuration properties.
  The function DEMOD_storeDefaultProperies should be called before the first call to this function.
  Parameter:  Pointer to LGDBB Context
  Returns:    I2C transaction error code, NO_DEMOD_ERROR if successful
  Programming Guide Reference:    DVBC setup flowchart
******************************************************************************************/
UINT8  DEMOD_L1_Download_DVBC_Properties        (LX_DEMOD_L1_Context *api)
{
  	DBB_PRINT("DEMOD_L1_Download_DVBC_Properties\n");
#ifdef    DEMOD_DD_CLOCK_MODE_PROP
	api->prop->dd_clk_mode.clk_mode		= DEMOD_DD_CLOCK_MODE_PROP_24MHZ; /* (default : 24MHz) */
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_CLOCK_MODE_PROP_CODE) != NO_DEMOD_ERROR)
	{
		return ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_DD_CLOCK_MODE_PROP */
#ifdef    DEMOD_DD_ADC_PROP
       api->prop->dd_adc_sel.adcClkPllSel 							= DEMOD_DD_ADC_PROP_ADCCLKPLLSEL_DEFAULT;
	api->prop->dd_adc_sel.adcClk								= DEMOD_DD_ADC_PROP_ADCCLK_24MHZ;

	if (DEMOD_L1_Set_Property(api, DEMOD_DD_ADC_PROP_CODE) != NO_DEMOD_ERROR)
	{
		DBB_PRINT("NOT Implemented yet\n");
		return ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_DD_ADC_PROP */

		
#ifdef    DEMOD_DD_MODE_PROP
	api->prop->dd_mode.modulation		= DEMOD_DD_MODE_PROP_MODULATION_DVBC;	
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_MODE_PROP_CODE) != NO_DEMOD_ERROR)
	{
		return ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_DD_MODE_PROP */
#ifdef		  DEMOD_DD_IF_FREQ_PROP
		
	api->prop->dd_if_freq.if_freq							=  DEMOD_DD_IF_FREQ_PROP_IF_FREQ_5MHZ; /* (default	6000) */
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_IF_FREQ_PROP_CODE ) != NO_DEMOD_ERROR)
	{
		return ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /*	  DEMOD_DD_IF_FREQ_PROP */


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
UINT8  DEMOD_L1_Download_DTMB_Properties        (LX_DEMOD_L1_Context *api)
{
  	DBB_PRINT("DEMOD_L1_Download_DTMB_Properties \n");
#ifdef    DEMOD_DD_CLOCK_MODE_PROP
	api->prop->dd_clk_mode.clk_mode		= DEMOD_DD_CLOCK_MODE_PROP_24MHZ; /* (default : 24MHz) */
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_CLOCK_MODE_PROP_CODE) != NO_DEMOD_ERROR)
	{
		return ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_DD_CLOCK_MODE_PROP */
#ifdef    DEMOD_DD_ADC_PROP
       api->prop->dd_adc_sel.adcClkPllSel 							= DEMOD_DD_ADC_PROP_ADCCLKPLLSEL_DEFAULT;
	api->prop->dd_adc_sel.adcClk								= DEMOD_DD_ADC_PROP_ADCCLK_24MHZ;

	if (DEMOD_L1_Set_Property(api, DEMOD_DD_ADC_PROP_CODE) != NO_DEMOD_ERROR)
	{
		DBB_PRINT("NOT Implemented yet\n");
		return ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_DD_ADC_PROP */

		
#ifdef    DEMOD_DD_MODE_PROP
	api->prop->dd_mode.modulation		= DEMOD_DD_MODE_PROP_MODULATION_DTMB;	
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_MODE_PROP_CODE) != NO_DEMOD_ERROR)
	{
		return ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_DD_MODE_PROP */
#ifdef		  DEMOD_DD_IF_FREQ_PROP
		
	api->prop->dd_if_freq.if_freq							=  DEMOD_DD_IF_FREQ_PROP_IF_FREQ_5MHZ; /* (default	6000) */
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_IF_FREQ_PROP_CODE ) != NO_DEMOD_ERROR)
	{
		return ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /*	  DEMOD_DD_IF_FREQ_PROP */


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
******************************************************************************************/
UINT8  DEMOD_L1_Download_DVBS_Properties        (LX_DEMOD_L1_Context *api)
{
  	DBB_PRINT("DEMOD_L1_Download_DVBS_Properties\n");
  	
#ifdef    DEMOD_DD_CLOCK_MODE_PROP
	api->prop->dd_clk_mode.clk_mode		= DEMOD_DD_CLOCK_MODE_PROP_24MHZ; /* (default : 24MHz) */
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_CLOCK_MODE_PROP_CODE) != NO_DEMOD_ERROR)
	{
		return ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_DD_CLOCK_MODE_PROP */
#ifdef    DEMOD_DD_ADC_PROP
       api->prop->dd_adc_sel.adcClkPllSel 							= DEMOD_DD_ADC_PROP_ADCCLKPLLSEL_DEFAULT;
	api->prop->dd_adc_sel.adcClk								= DEMOD_DD_ADC_PROP_ADCCLK_124MHZ;

	if (DEMOD_L1_Set_Property(api, DEMOD_DD_ADC_PROP_CODE) != NO_DEMOD_ERROR)
	{
		DBB_PRINT("NOT Implemented yet\n");
		return ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_DD_ADC_PROP */

		
#ifdef    DEMOD_DD_MODE_PROP
	api->prop->dd_mode.modulation		= DEMOD_DD_MODE_PROP_MODULATION_DVBS;	
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_MODE_PROP_CODE) != NO_DEMOD_ERROR)
	{
		return ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_DD_MODE_PROP */

#ifdef		  DEMOD_DD_IF_FREQ_PROP
	
			api->prop->dd_if_freq.if_freq							=  DEMOD_DD_IF_FREQ_PROP_IF_FREQ_0MHZ; /* (default	6000) */
			if (DEMOD_L1_Set_Property(api, DEMOD_DD_IF_FREQ_PROP_CODE ) != NO_DEMOD_ERROR)
			{
				return ERROR_DEMOD_SENDING_COMMAND;
			}
#endif /*	  DEMOD_DD_IF_FREQ_PROP */

#if 1
	#ifdef        DEMOD_DD_DVBS_AFC_RANGE_PROP
	
	api->prop->dd_dvbs_afc_range.range_khz					 = DEMOD_DD_DVBS_AFC_RANGE_PROP_RANGE_KHZ_DEFAULT;
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_DVBS_AFC_RANGE_PROP_CODE) != NO_DEMOD_ERROR)
	{
		return ERROR_DEMOD_SENDING_COMMAND;
	}
	#endif /*     DEMOD_DD_DVBS_AFC_RANGE_PROP */

	#ifdef    DEMOD_DD_DVBS_OPMSEL_PROP	
 	api->prop->dd_dvbs_opm_sel.opmSel 					= DEMOD_DD_DVBS_OPM_SEL_PROP_NORMAL_MODE;
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_DVBS_OPMSEL_PROP_CODE) != NO_DEMOD_ERROR)
	{
		return ERROR_DEMOD_SENDING_COMMAND;
	}
	#endif /* DEMOD_DD_DVBS_OPMSEL_PROP */

	#ifdef        DEMOD_DD_DISEQC_CONFIG_PROP
	api->prop->dd_diseqc_config.message_sel					= DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_SEL_DEFAULT; /* (default : envelop) */
  	api->prop->dd_diseqc_config.diseqc_2_x_enable			= DEMOD_DD_DISEQC_CONFIG_PROP_EN_2_X_DISABLE; /* (default disable) */
  	api->prop->dd_diseqc_config.message_repeat_en			= DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_REPEAT_DEFAULT; /* (default 22000) */
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_DISEQC_CONFIG_PROP_CODE) != NO_DEMOD_ERROR)
	{
		return ERROR_DEMOD_SENDING_COMMAND;
	}
	#endif /*  DEMOD_DD_DISEQC_CONFIG_PROP */
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
******************************************************************************************/
UINT8  DEMOD_L1_Download_DVBS2_Properties       (LX_DEMOD_L1_Context *api)
{
  	DBB_PRINT("DEMOD_L1_Download_DVBS2_Properties\n");

#ifdef    DEMOD_DD_CLOCK_MODE_PROP
		api->prop->dd_clk_mode.clk_mode		= DEMOD_DD_CLOCK_MODE_PROP_24MHZ; /* (default : 24MHz) */
		if (DEMOD_L1_Set_Property(api, DEMOD_DD_CLOCK_MODE_PROP_CODE) != NO_DEMOD_ERROR)
		{
			return ERROR_DEMOD_SENDING_COMMAND;
		}
#endif /* DEMOD_DD_CLOCK_MODE_PROP */
#ifdef    DEMOD_DD_ADC_PROP
       api->prop->dd_adc_sel.adcClkPllSel 						= DEMOD_DD_ADC_PROP_ADCCLKPLLSEL_DEFAULT;
	api->prop->dd_adc_sel.adcClk								= DEMOD_DD_ADC_PROP_ADCCLK_124MHZ;

	if (DEMOD_L1_Set_Property(api, DEMOD_DD_ADC_PROP_CODE) != NO_DEMOD_ERROR)
	{
		DBB_PRINT("NOT Implemented yet\n");
		return ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_DD_ADC_PROP */		
#ifdef    DEMOD_DD_MODE_PROP
		api->prop->dd_mode.modulation		= DEMOD_DD_MODE_PROP_MODULATION_DVBS2;
		if (DEMOD_L1_Set_Property(api, DEMOD_DD_MODE_PROP_CODE) != NO_DEMOD_ERROR)
		{
			return ERROR_DEMOD_SENDING_COMMAND;
		}
#endif /* DEMOD_DD_MODE_PROP */

#ifdef		  DEMOD_DD_IF_FREQ_PROP
	
			api->prop->dd_if_freq.if_freq							=  DEMOD_DD_IF_FREQ_PROP_IF_FREQ_0MHZ; /* (default	6000) */
			if (DEMOD_L1_Set_Property(api, DEMOD_DD_IF_FREQ_PROP_CODE ) != NO_DEMOD_ERROR)
			{
				return ERROR_DEMOD_SENDING_COMMAND;
			}
#endif /*	  DEMOD_DD_IF_FREQ_PROP */


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
UINT8  DEMOD_L1_Download_DVBT_Properties        (LX_DEMOD_L1_Context *api)
{
  	DBB_PRINT("DEMOD_L1_Download_DVBT_Properties\n");

#ifdef    DEMOD_DD_CLOCK_MODE_PROP
		api->prop->dd_clk_mode.clk_mode						= DEMOD_DD_CLOCK_MODE_PROP_24MHZ; /* (default : 24MHz) */
		if (DEMOD_L1_Set_Property(api, DEMOD_DD_CLOCK_MODE_PROP_CODE) != NO_DEMOD_ERROR)
		{
			return ERROR_DEMOD_SENDING_COMMAND;
		}
#endif /* DEMOD_DD_CLOCK_MODE_PROP */

#ifdef    DEMOD_DD_ADC_PROP
       api->prop->dd_adc_sel.adcClkPllSel 						= DEMOD_DD_ADC_PROP_ADCCLKPLLSEL_DEFAULT;
	api->prop->dd_adc_sel.adcClk								= DEMOD_DD_ADC_PROP_ADCCLK_24MHZ;

	if (DEMOD_L1_Set_Property(api, DEMOD_DD_ADC_PROP_CODE) != NO_DEMOD_ERROR)
	{
		DBB_PRINT("NOT Implemented yet\n");
		return ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_DD_ADC_PROP */

#ifdef    DEMOD_DD_MODE_PROP
		api->prop->dd_mode.modulation							= DEMOD_DD_MODE_PROP_MODULATION_DVBT;
		if (DEMOD_L1_Set_Property(api, DEMOD_DD_MODE_PROP_CODE) != NO_DEMOD_ERROR)
		{
			return ERROR_DEMOD_SENDING_COMMAND;
		}
#endif /* DEMOD_DD_MODE_PROP */

#ifdef		  DEMOD_DD_IF_FREQ_PROP

		api->prop->dd_if_freq.if_freq							=  DEMOD_DD_IF_FREQ_PROP_IF_FREQ_5MHZ; /* (default  6000) */
		if (DEMOD_L1_Set_Property(api, DEMOD_DD_IF_FREQ_PROP_CODE ) != NO_DEMOD_ERROR)
		{
			return ERROR_DEMOD_SENDING_COMMAND;
		}
#endif /*	  DEMOD_DD_IF_FREQ_PROP */


#if 1

	#ifdef        DEMOD_DD_DVBT_HIERARCHY_PROP
	api->prop->dd_dvbt_hp_sel.hierhpsel					 = DEMOD_DD_DVBT_HIERARCHY_PROP_HIERHPSEL_HIGH;
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_DVBT_HIERARCHY_PROP_CODE) != NO_DEMOD_ERROR)
	{
		return ERROR_DEMOD_SENDING_COMMAND;
	}
	#endif /*     DEMOD_DD_DVBT_HIERARCHY_PROP */
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
UINT8  DEMOD_L1_Download_DVBT2_Properties       (LX_DEMOD_L1_Context *api)
{
  	DBB_PRINT("DEMOD_L1_Download_DVBT2_Properties\n");
  	
#ifdef    DEMOD_DD_CLOCK_MODE_PROP
	api->prop->dd_clk_mode.clk_mode						= DEMOD_DD_CLOCK_MODE_PROP_24MHZ; /* (default : 24MHz) */
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_CLOCK_MODE_PROP_CODE) != NO_DEMOD_ERROR)
	{
		return ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_DD_CLOCK_MODE_PROP */
#ifdef    DEMOD_DD_ADC_PROP
	api->prop->dd_adc_sel.adcClkPllSel 						= DEMOD_DD_ADC_PROP_ADCCLKPLLSEL_DEFAULT;
	api->prop->dd_adc_sel.adcClk								= DEMOD_DD_ADC_PROP_ADCCLK_24MHZ;

	if (DEMOD_L1_Set_Property(api, DEMOD_DD_ADC_PROP_CODE) != NO_DEMOD_ERROR)
	{
		DBB_PRINT("NOT Implemented yet\n");
		return ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_DD_ADC_PROP */	
#ifdef    DEMOD_DD_MODE_PROP
	api->prop->dd_mode.modulation							= DEMOD_DD_MODE_PROP_MODULATION_DVBT2;
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_MODE_PROP_CODE) != NO_DEMOD_ERROR)
	{
		return ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /* DEMOD_DD_MODE_PROP */

#ifdef        DEMOD_DD_DVBT2_MODE_PROP
	api->prop->dd_dvbt2_lock_mode.lock_mode				 = DEMOD_DD_DVBT2_MODE_PROP_LOCK_MODE_BASE_ONLY;
	if (DEMOD_L1_Set_Property(api, DEMOD_DD_DVBT2_MODE_PROP_CODE) != NO_DEMOD_ERROR)
	{
		return ERROR_DEMOD_SENDING_COMMAND;
	}
#endif /*     DEMOD_DD_DVBT2_MODE_PROP */

#ifdef		  DEMOD_DD_IF_FREQ_PROP
	
			api->prop->dd_if_freq.if_freq							=  DEMOD_DD_IF_FREQ_PROP_IF_FREQ_5MHZ; /* (default	6000) */
			if (DEMOD_L1_Set_Property(api, DEMOD_DD_IF_FREQ_PROP_CODE ) != NO_DEMOD_ERROR)
			{
				return ERROR_DEMOD_SENDING_COMMAND;
			}
#endif /*	  DEMOD_DD_IF_FREQ_PROP */


	return NO_DEMOD_ERROR;
}


/*****************************************************************************************
 NAME: DEMOD_downloadMCNSProperties
  DESCRIPTION: Setup LGDBB MCNS properties configuration
  This function will download all the MCNS configuration properties.
  The function DEMOD_storeDefaultProperies should be called before the first call to this function.
  Parameter:  Pointer to LGDBB Context
  Returns:    I2C transaction error code, NO_DEMOD_ERROR if successful
  Programming Guide Reference:    MCNS setup flowchart
******************************************************************************************/
UINT8  DEMOD_L1_Download_DVBC2_Properties	(LX_DEMOD_L1_Context *api)
{
  	DBB_PRINT("DEMOD_L1_Download_DVBC2_Properties\n");
	return NO_DEMOD_ERROR;
}

#endif

UINT8  DEMOD_L1_Download_All_Properties	(LX_DEMOD_L1_Context *api)
{
	DEMOD_L1_Download_COMMON_Properties	(api);

#ifndef LG3307_API

//	DEMOD_L1_Download_DVBC_Properties	(api);
//	DEMOD_L1_Download_DVBS_Properties	(api);
//	DEMOD_L1_Download_DVBS2_Properties	(api);
//	DEMOD_L1_Download_DVBT_Properties	(api);
//	DEMOD_L1_Download_DVBT2_Properties	(api);
//	DEMOD_L1_Download_DVBC2_Properties	(api);
#endif

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
UINT8  DEMOD_L1_Unpack_Property            (LX_DEMOD_L1_PropObj   *prop, UINT32 prop_code, UINT32 *data)
{

	switch (prop_code)
	{
		#ifdef        DEMOD_DD_BER_RESOL_PROP
		 case         DEMOD_DD_BER_RESOL_PROP_CODE:
		 	{
     				 *data = (prop->dd_ber_resol.exp  & DEMOD_DD_BER_RESOL_PROP_EXP_MASK ) << DEMOD_DD_BER_RESOL_PROP_EXP_LSB;
		 	}
	  		break;
		#endif /*     DEMOD_DD_BER_RESOL_PROP */

		#ifdef        DEMOD_DD_IF_FREQ_PROP
		 case         DEMOD_DD_IF_FREQ_PROP_CODE:
		 	{
	     			 *data = (prop->dd_if_freq.if_freq  & DEMOD_DD_IF_FREQ_PROP_IF_FREQ_MASK ) << DEMOD_DD_IF_FREQ_PROP_IF_FREQ_LSB;
		 	}
		 	break;
		#endif /*     DEMOD_DD_IF_FREQ_PROP */

		#ifdef        DEMOD_DD_CLOCK_MODE_PROP
		 case         DEMOD_DD_CLOCK_MODE_PROP_CODE:
		 	{
	     			 *data = (prop->dd_clk_mode.clk_mode  & DEMOD_DD_CLOCK_MODE_PROP_MASK ) << DEMOD_DD_CLOCK_MODE_PROP_LSB;
		 	}
		 	break;
		#endif /*     DEMOD_DD_CLOCK_MODE_PROP */

		#ifdef        DEMOD_DD_DVBS_OPMSEL_PROP
		 case         DEMOD_DD_DVBS_OPMSEL_PROP_CODE:
		 	{
	     			 *data = (prop->dd_dvbs_opm_sel.opmSel  & DEMOD_DD_DVBS_OPM_SEL_PROP_MASK ) << DEMOD_DD_DVBS_OPM_SEL_PROP_LSB;
		 	}
		 	break;
		#endif /*     DEMOD_DD_OPMSEL_PROP */

		#ifdef        DEMOD_DD_MODE_PROP
		 case         DEMOD_DD_MODE_PROP_CODE:
		 	{
     				 *data = (prop->dd_mode.tuneMode  & DEMOD_DD_MODE_PROP_TUNEMODE_MASK ) << DEMOD_DD_MODE_PROP_TUNEMODE_LSB |
				              (prop->dd_mode.specinvauto & DEMOD_DD_MODE_PROP_SPECINVAUTO_MASK) << DEMOD_DD_MODE_PROP_SPECINVAUTO_LSB |
				              (prop->dd_mode.specinv    & DEMOD_DD_MODE_PROP_SPECINV_MASK) << DEMOD_DD_MODE_PROP_SPECINV_LSB |
				              (prop->dd_mode.modulation & DEMOD_DD_MODE_PROP_MODULATION_MASK) << DEMOD_DD_MODE_PROP_MODULATION_LSB |
				              (prop->dd_mode.bw & DEMOD_DD_MODE_PROP_BW_MASK) << DEMOD_DD_MODE_PROP_BW_LSB ;
		 	}
		 	break;
		#endif /*     DEMOD_DD_MODE_PROP */


		#ifdef        DEMOD_DD_AUTO_MODE_PROP
		 case         DEMOD_DD_AUTO_MODE_PROP_CODE:
		 	{
	     			 *data = (prop->dd_auto_mode.auto_detect  & DEMOD_DD_AUTO_MODE_PROP_DETEN_MASK ) << DEMOD_DD_AUTO_MODE_PROP_DETEN_LSB;
		 	}
		 	break;
		#endif /*     DEMOD_DD_AUTO_MODE_PROP */

		#ifdef        DEMOD_DD_TS_MODE_PROP
		 case         DEMOD_DD_TS_MODE_PROP_CODE:
		 	{
     				 *data = (prop->dd_ts_mode.tpMode		& DEMOD_DD_TS_MODE_PROP_TPMODE_MASK ) 	<< DEMOD_DD_TS_MODE_PROP_TPMODE_LSB 		|
				              (prop->dd_ts_mode.tpClkPol	& DEMOD_DD_TS_MODE_PROP_TPCLKPOL_MASK) 	<< DEMOD_DD_TS_MODE_PROP_TPCLKPOL_LSB 	|
				              (prop->dd_ts_mode.tpSopPol	& DEMOD_DD_TS_MODE_PROP_TPSOPPOL_MASK) 	<< DEMOD_DD_TS_MODE_PROP_TPSOPPOL_LSB 	|
				              (prop->dd_ts_mode.tpValPol	& DEMOD_DD_TS_MODE_PROP_TPVALPOL_MASK) 	<< DEMOD_DD_TS_MODE_PROP_TPVALPOL_LSB 	|
				              (prop->dd_ts_mode.tpErrPol	& DEMOD_DD_TS_MODE_PROP_TPERRPOL_MASK) 	<< DEMOD_DD_TS_MODE_PROP_TPERRPOL_LSB 	|
				              (prop->dd_ts_mode.tpClkSup	& DEMOD_DD_TS_MODE_PROP_TPCLKSUP_MASK) 	<< DEMOD_DD_TS_MODE_PROP_TPCLKSUP_LSB 	|
				              (prop->dd_ts_mode.tpMsbFirst	& DEMOD_DD_TS_MODE_PROP_TPMSBFST_MASK) 	<< DEMOD_DD_TS_MODE_PROP_TPMSBFST_LSB 	|
				              (prop->dd_ts_mode.tpBigEnd	& DEMOD_DD_TS_MODE_PROP_TPBIGEND_MASK) 	<< DEMOD_DD_TS_MODE_PROP_TPBIGEND_LSB ;
		 	}
		 	break;
		#endif /*     DEMOD_DD_TS_MODE_PROP */

		#ifdef        DEMOD_DD_ADC_PROP
		 case         DEMOD_DD_ADC_PROP_CODE:
		 	{
	     			 //*data = (prop->dd_adc_sel.adcClkPllSel  & DEMOD_DD_ADC_PROP_ADCCLKPLLSEL_MASK ) << DEMOD_DD_ADC_PROP_ADCCLKPLLSEL_LSB;
					*data = (prop->dd_adc_sel.adcClkPllSel  & DEMOD_DD_ADC_PROP_ADCCLKPLLSEL_MASK ) << DEMOD_DD_ADC_PROP_ADCCLKPLLSEL_LSB	|
		 					(prop->dd_adc_sel.adcClk		& DEMOD_DD_ADC_PROP_ADCCLK_MASK ) << DEMOD_DD_ADC_PROP_ADCCLK_LSB ;
			}
		 	break;
		#endif /*     DEMOD_DD_ADC_PROP */

		#ifdef        DEMOD_DD_AGC_PROP
		 case         DEMOD_DD_AGC_PROP_CODE:
		 	{

     				 *data = (prop->dd_agc.agc_src	& DEMOD_DD_AGC_PROP_SRC_MASK) 	<< DEMOD_DD_AGC_PROP_SRC_LSB	|
				             (prop->dd_agc.agc_pol	& DEMOD_DD_AGC_PROP_POL_MASK) 	<< DEMOD_DD_AGC_PROP_POL_LSB	|
							 (prop->dd_agc.agc_outEn	& DEMOD_DD_AGC_PROP_OUTEN_MASK ) 	<< DEMOD_DD_AGC_PROP_OUTEN_LSB	|
							 (prop->dd_agc.agc_outEn_S	& DEMOD_DD_AGC_PROP_OUTEN_S_MASK ) 	<< DEMOD_DD_AGC_PROP_OUTEN_S_LSB	|
				             (prop->dd_agc.agc_frzEn	& DEMOD_DD_AGC_PROP_FRZEN_MASK) 	<< DEMOD_DD_AGC_PROP_FRZEN_LSB	|
				             (prop->dd_agc.agc_bw		& DEMOD_DD_AGC_PROP_BW_MASK) 	<< DEMOD_DD_AGC_PROP_BW_LSB	;

		 	}
		 	break;
		#endif /*     DEMOD_DD_AGC_PROP */


		#ifdef        DEMOD_DD_TPOUT_MODE_PROP
		 case         DEMOD_DD_TPOUT_MODE_PROP_CODE:
		 	{
	     			 *data =  (prop->dd_tpout_mode.tpSrMsb	 & DEMOD_DD_TPOUT_MODE_PROP_TPSRMSB_MASK) << DEMOD_DD_TPOUT_MODE_PROP_TPSRMSB_LSB 	|
					 	 (prop->dd_tpout_mode.tpOutEn  & DEMOD_DD_TPOUT_MODE_PROP_TPOUTEN_MASK ) << DEMOD_DD_TPOUT_MODE_PROP_TPOUTEN_LSB;
		 	}
		 	break;
		#endif /*     DEMOD_DD_TPOUT_MODE_PROP */


		#ifdef        DEMOD_DD_CONSTEL_PROP
		 case         DEMOD_DD_CONSTEL_PROP_CODE:
		 	{
     				 *data = (prop->dd_constel.constellation  & DEMOD_DD_CONSTELATION_PROP_MASK ) << DEMOD_DD_CONSTELATION_PROP_LSB |
				              (prop->dd_constel.constel_autodet & DEMOD_DD_CONSTELATION_PROP_AUTO_DET_MASK) << DEMOD_DD_CONSTELATION_PROP_AUTO_DET_LSB ;
	 	}
	 	 	break;
		#endif /*     DEMOD_DD_CONSTEL_PROP */


		#ifdef    DEMOD_DD_COUNTRY_GRP_PROP //190313		
		 case         DEMOD_DD_COUNTRY_GRP_PROP_CODE:
		 	{
   				 *data = (prop->dd_country_grp.grp  & DEMOD_DD_COUNTRY_GRP_PROP_MASK ) << DEMOD_DD_COUNTRY_GRP_PROP_LSB;
	 		}
	 	 	break;
		#endif /* DEMOD_DD_COUNTRY_GRP_PROP */		
		
#ifndef LG3307_API


		#ifdef        DEMOD_DD_DISEQC_CONFIG_PROP
		 case         DEMOD_DD_DISEQC_CONFIG_PROP_CODE:
		 	{
     				 *data = (prop->dd_diseqc_config.message_sel  & DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_SEL_MASK ) << DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_SEL_LSB |
				              (prop->dd_diseqc_config.diseqc_2_x_enable & DEMOD_DD_DISEQC_CONFIG_PROP_EN_2_X_MASK) << DEMOD_DD_DISEQC_CONFIG_PROP_EN_2_X_LSB |
				              (prop->dd_diseqc_config.message_repeat_en & DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_REPEAT_MASK) << DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_REPEAT_LSB ;
		 	}
		 	break;
		#endif /*     DEMOD_DD_DISEQC_CONFIG_PROP */

		#ifdef        DEMOD_DD_DVBT_HIERARCHY_PROP
		 case         DEMOD_DD_DVBT_HIERARCHY_PROP_CODE:
		 	{
	     			 *data = (prop->dd_dvbt_hp_sel.hierhpsel  & DEMOD_DD_DVBT_HIERARCHY_PROP_HIERHPSEL_D_MASK ) << DEMOD_DD_DVBT_HIERARCHY_PROP_HIERHPSEL_D_LSB;
		 	}
		 	break;
		#endif /*     DEMOD_DD_DVBT_HIERARCHY_PROP */

		#ifdef        DEMOD_DD_DVBT2_MODE_PROP
		 case         DEMOD_DD_DVBT2_MODE_PROP_CODE:
		 	{
	     			 *data = (prop->dd_dvbt2_lock_mode.lock_mode  & DEMOD_DD_DVBT2_MODE_PROP_LOCK_MODE_MASK ) << DEMOD_DD_DVBT2_MODE_PROP_LOCK_MODE_LSB;
		 	}
		 	break;
		#endif /*     DEMOD_DD_DVBT2_MODE_PROP */

		#ifdef        DEMOD_DD_DVBS_AFC_RANGE_PROP
		 case         DEMOD_DD_DVBS_AFC_RANGE_PROP_CODE:
		 	{
	     			 *data = (prop->dd_dvbs_afc_range.range_khz  & DEMOD_DD_DVBS_AFC_RANGE_PROP_RANGE_KHZ_MASK ) << DEMOD_DD_DVBS_AFC_RANGE_PROP_RANGE_KHZ_LSB;
		 	}
		 	break;
		#endif /*     DEMOD_DD_DVBS_AFC_RANGE_PROP */
#endif

		 default : return ERROR_DEMOD_UNKNOWN_PROPERTY; break;
	}

	//DBB_PRINT("(%s) prop_code = 0x%x, data = 0x%x !!\n", __F__,prop_code, *data);

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
UINT8 DEMOD_L1_Pack_Property          (LX_DEMOD_L1_PropObj   *prop, UINT32 prop_code, UINT32  data)
{
	switch (prop_code)
	{
		#ifdef        DEMOD_DD_BER_RESOL_PROP
		 case         DEMOD_DD_BER_RESOL_PROP_CODE:
		 	{
		           	prop->dd_ber_resol.exp  = (data >> DEMOD_DD_BER_RESOL_PROP_EXP_LSB ) & DEMOD_DD_BER_RESOL_PROP_EXP_MASK;
		 	}
		 	break;
		#endif /*     DEMOD_DD_BER_RESOL_PROP */

		#ifdef        DEMOD_DD_IF_FREQ_PROP
		 case         DEMOD_DD_IF_FREQ_PROP_CODE:
		 	{
		           	prop->dd_if_freq.if_freq = (data >> DEMOD_DD_IF_FREQ_PROP_IF_FREQ_LSB) & DEMOD_DD_IF_FREQ_PROP_IF_FREQ_MASK;
		 	}
		 	break;
		#endif /*     DEMOD_DD_IF_FREQ_PROP */

		#ifdef        DEMOD_DD_CLOCK_MODE_PROP
		 case         DEMOD_DD_CLOCK_MODE_PROP_CODE:
		 	{
		           	prop->dd_clk_mode.clk_mode  = (data >> DEMOD_DD_CLOCK_MODE_PROP_LSB ) & DEMOD_DD_CLOCK_MODE_PROP_MASK;
		 	}
		 	break;
		#endif /*     DEMOD_DD_CLOCK_MODE_PROP */

		#ifdef        DEMOD_DD_DVBS_OPMSEL_PROP
		 case         DEMOD_DD_DVBS_OPMSEL_PROP_CODE:
		 	{
		           	prop->dd_dvbs_opm_sel.opmSel = (data >> DEMOD_DD_DVBS_OPM_SEL_PROP_LSB) & DEMOD_DD_DVBS_OPM_SEL_PROP_MASK;
		 	}
		 	break;
		#endif /*     DEMOD_DD_OPMSEL_PROP */

		#ifdef        DEMOD_DD_MODE_PROP
		 case         DEMOD_DD_MODE_PROP_CODE:
		 	{
				prop->dd_mode.tuneMode  		= (data >> DEMOD_DD_MODE_PROP_TUNEMODE_LSB) & DEMOD_DD_MODE_PROP_TUNEMODE_MASK;
				prop->dd_mode.specinvauto     	= (data >> DEMOD_DD_MODE_PROP_SPECINVAUTO_LSB) & DEMOD_DD_MODE_PROP_SPECINVAUTO_MASK;
				prop->dd_mode.specinv            	= (data >> DEMOD_DD_MODE_PROP_SPECINV_LSB) & DEMOD_DD_MODE_PROP_SPECINV_MASK;
				prop->dd_mode.modulation       	= (data >> DEMOD_DD_MODE_PROP_MODULATION_LSB) & DEMOD_DD_MODE_PROP_MODULATION_MASK;
				prop->dd_mode.bw                   	= (data >> DEMOD_DD_MODE_PROP_BW_LSB) & DEMOD_DD_MODE_PROP_BW_MASK;
		 	}
		 	break;
		#endif /*     DEMOD_DD_MODE_PROP */


		#ifdef        DEMOD_DD_AUTO_MODE_PROP
		 case         DEMOD_DD_AUTO_MODE_PROP_CODE:
		 	{
	 			prop->dd_auto_mode.auto_detect		= (data >> DEMOD_DD_AUTO_MODE_PROP_DETEN_LSB    ) & DEMOD_DD_AUTO_MODE_PROP_DETEN_MASK ;
		 	}
		 	break;
		#endif /*     DEMOD_DD_AUTO_MODE_PROP */

		#ifdef        DEMOD_DD_TS_MODE_PROP
		 case         DEMOD_DD_TS_MODE_PROP_CODE:
		 	{
				prop->dd_ts_mode.tpMode				= (data >> DEMOD_DD_TS_MODE_PROP_TPMODE_LSB) & DEMOD_DD_TS_MODE_PROP_TPMODE_MASK;
				prop->dd_ts_mode.tpClkPol				= (data >> DEMOD_DD_TS_MODE_PROP_TPCLKPOL_LSB) & DEMOD_DD_TS_MODE_PROP_TPCLKPOL_MASK;
				prop->dd_ts_mode.tpSopPol			= (data >> DEMOD_DD_TS_MODE_PROP_TPSOPPOL_LSB) & DEMOD_DD_TS_MODE_PROP_TPSOPPOL_MASK;
				prop->dd_ts_mode.tpValPol				= (data >> DEMOD_DD_TS_MODE_PROP_TPVALPOL_LSB) & DEMOD_DD_TS_MODE_PROP_TPVALPOL_MASK;
				prop->dd_ts_mode.tpErrPol				= (data >> DEMOD_DD_TS_MODE_PROP_TPERRPOL_LSB) & DEMOD_DD_TS_MODE_PROP_TPERRPOL_MASK;
				prop->dd_ts_mode.tpClkSup			= (data >> DEMOD_DD_TS_MODE_PROP_TPCLKSUP_LSB) & DEMOD_DD_TS_MODE_PROP_TPCLKSUP_MASK;
				prop->dd_ts_mode.tpMsbFirst			= (data >> DEMOD_DD_TS_MODE_PROP_TPMSBFST_LSB) & DEMOD_DD_TS_MODE_PROP_TPMSBFST_MASK;
				prop->dd_ts_mode.tpBigEnd			= (data >> DEMOD_DD_TS_MODE_PROP_TPBIGEND_LSB) & DEMOD_DD_TS_MODE_PROP_TPBIGEND_MASK ;
		 	}
		 	break;
		#endif /*     DEMOD_DD_TS_MODE_PROP */

		#ifdef        DEMOD_DD_ADC_PROP
		 case         DEMOD_DD_ADC_PROP_CODE:
		 	{
	       		//prop->dd_adc_sel.adcClkPllSel 	= (data >> DEMOD_DD_ADC_PROP_ADCCLKPLLSEL_LSB) & DEMOD_DD_ADC_PROP_ADCCLKPLLSEL_MASK;
				prop->dd_adc_sel.adcClkPllSel 	= (data >> DEMOD_DD_ADC_PROP_ADCCLKPLLSEL_LSB) & DEMOD_DD_ADC_PROP_ADCCLKPLLSEL_MASK;
				prop->dd_adc_sel.adcClk			= (data >> DEMOD_DD_ADC_PROP_ADCCLK_LSB) & DEMOD_DD_ADC_PROP_ADCCLK_MASK;
		 	}
		 	break;
		#endif /*     DEMOD_DD_ADC_PROP */

		#ifdef        DEMOD_DD_AGC_PROP
		 case         DEMOD_DD_AGC_PROP_CODE:
		 	{
	       		prop->dd_agc.agc_src 	= (data >> DEMOD_DD_AGC_PROP_SRC_LSB) & DEMOD_DD_AGC_PROP_SRC_MASK;
	       		prop->dd_agc.agc_pol 	= (data >> DEMOD_DD_AGC_PROP_POL_LSB) & DEMOD_DD_AGC_PROP_POL_MASK;
				prop->dd_agc.agc_outEn 	= (data >> DEMOD_DD_AGC_PROP_OUTEN_LSB) & DEMOD_DD_AGC_PROP_OUTEN_MASK;
				prop->dd_agc.agc_outEn_S= (data >> DEMOD_DD_AGC_PROP_OUTEN_S_LSB) & DEMOD_DD_AGC_PROP_OUTEN_S_MASK;
	       		prop->dd_agc.agc_frzEn 	= (data >> DEMOD_DD_AGC_PROP_FRZEN_LSB) & DEMOD_DD_AGC_PROP_FRZEN_MASK;
	       		prop->dd_agc.agc_bw 	= (data >> DEMOD_DD_AGC_PROP_BW_LSB) & DEMOD_DD_AGC_PROP_BW_MASK;

		 	}
		 	break;
		#endif /*     DEMOD_DD_AGC_PROP */



		#ifdef        DEMOD_DD_TPOUT_MODE_PROP
		 case         DEMOD_DD_TPOUT_MODE_PROP_CODE:
		 	{
				prop->dd_tpout_mode.tpSrMsb		= (data >> DEMOD_DD_TPOUT_MODE_PROP_TPSRMSB_LSB	) &DEMOD_DD_TPOUT_MODE_PROP_TPSRMSB_MASK;
				prop->dd_tpout_mode.tpOutEn 		= (data >> DEMOD_DD_TPOUT_MODE_PROP_TPOUTEN_LSB    ) & DEMOD_DD_TPOUT_MODE_PROP_TPOUTEN_MASK;
		 	}
		 	break;
		#endif /*     DEMOD_DD_TPOUT_MODE_PROP */


		#ifdef        DEMOD_DD_CONSTEL_PROP
		 case         DEMOD_DD_CONSTEL_PROP_CODE:
		 	{
			       prop->dd_constel.constellation 			= (data >> DEMOD_DD_CONSTELATION_PROP_LSB  ) & DEMOD_DD_CONSTELATION_PROP_MASK;
			       prop->dd_constel.constel_autodet 	= (data >> DEMOD_DD_CONSTELATION_PROP_AUTO_DET_LSB  ) & DEMOD_DD_CONSTELATION_PROP_AUTO_DET_MASK;
	 	}
		 	break;
		#endif /*     DEMOD_DD_CONSTEL_PROP */
		
		
		#ifdef    DEMOD_DD_COUNTRY_GRP_PROP //190313
			case    DEMOD_DD_COUNTRY_GRP_PROP_CODE:
			{
				      prop->dd_country_grp.grp 			= (data >> DEMOD_DD_COUNTRY_GRP_PROP_LSB  ) & DEMOD_DD_COUNTRY_GRP_PROP_MASK;				       
		 	}
		 	break;
		#endif /* DEMOD_DD_COUNTRY_GRP_PROP */

#ifndef LG3307_API

		#ifdef        DEMOD_DD_DISEQC_CONFIG_PROP
		 case         DEMOD_DD_DISEQC_CONFIG_PROP_CODE:
		 	{
		           	prop->dd_diseqc_config.message_sel = (data >> DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_SEL_LSB) & DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_SEL_MASK;
		          	prop->dd_diseqc_config.diseqc_2_x_enable = (data >> DEMOD_DD_DISEQC_CONFIG_PROP_EN_2_X_LSB) & DEMOD_DD_DISEQC_CONFIG_PROP_EN_2_X_MASK;
		          	prop->dd_diseqc_config.message_repeat_en = (data >> DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_REPEAT_LSB) & DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_REPEAT_MASK;
		 	}
		 	break;
		#endif /*     DEMOD_DD_DISEQC_CONFIG_PROP */

		#ifdef        DEMOD_DD_DVBT_HIERARCHY_PROP
		 case         DEMOD_DD_DVBT_HIERARCHY_PROP_CODE:
		 	{
	      			 prop->dd_dvbt_hp_sel.hierhpsel 	= (data >> DEMOD_DD_DVBT_HIERARCHY_PROP_HIERHPSEL_D_LSB    ) & DEMOD_DD_DVBT_HIERARCHY_PROP_HIERHPSEL_D_MASK;
		 	}
		 	break;
		#endif /*     DEMOD_DD_DVBT_HIERARCHY_PROP */


		#ifdef        DEMOD_DD_DVBT2_MODE_PROP
		 case         DEMOD_DD_DVBT2_MODE_PROP_CODE:
		 	{
				prop->dd_dvbt2_lock_mode.lock_mode	= (data >> DEMOD_DD_DVBT2_MODE_PROP_LOCK_MODE_LSB) & DEMOD_DD_DVBT2_MODE_PROP_LOCK_MODE_MASK;
		 	}
		 	break;
		#endif /*     DEMOD_DD_DVBT2_MODE_PROP */

		#ifdef        DEMOD_DD_DVBS_AFC_RANGE_PROP
		 case         DEMOD_DD_DVBS_AFC_RANGE_PROP_CODE:
		 	{
	       		prop->dd_dvbs_afc_range.range_khz		= (data >> DEMOD_DD_DVBS_AFC_RANGE_PROP_RANGE_KHZ_LSB) & DEMOD_DD_DVBS_AFC_RANGE_PROP_RANGE_KHZ_MASK;
		 	}
		 	break;
		#endif /*     DEMOD_DD_DVBS_AFC_RANGE_PROP */
#endif

		 default : return ERROR_DEMOD_UNKNOWN_PROPERTY; break;
	}
	//DBB_PRINT("(%s) prop_code = 0x%x, data = 0x%x !!\n", __F__,prop_code, data);

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
void  DEMOD_L1_Store_Properties_Defaults (LX_DEMOD_L1_PropObj   *prop)
{

#ifdef    DEMOD_DD_BER_RESOL_PROP
  	prop->dd_ber_resol.exp							=  DEMOD_DD_BER_RESOL_PROP_EXP_DEFAULT; /* (default     7) */
#endif /* DEMOD_DD_BER_RESOL_PROP */

#ifdef    DEMOD_DD_IF_FREQ_PROP
  	prop->dd_if_freq.if_freq							=  DEMOD_DD_IF_FREQ_PROP_IF_FREQ_DEFAULT; /* (default  6000) */
#endif /* DEMOD_DD_IF_INPUT_FREQ_PROP */

#ifdef    DEMOD_DD_CLOCK_MODE_PROP
  	prop->dd_clk_mode.clk_mode						= DEMOD_DD_CLOCK_MODE_PROP_24MHZ; /* (default : 24MHz) */
#endif /* DEMOD_DD_CLOCK_MODE_PROP */

#ifdef    DEMOD_DD_MODE_PROP
	prop->dd_mode.tuneMode                                            	= DEMOD_DD_MODE_PROP_TUNEMODE_DEFAULT; /* (default : NORMAL) */
	prop->dd_mode.specinvauto                                         	= DEMOD_DD_MODE_PROP_SPECINV_MANUAL;
	prop->dd_mode.specinv                                          	= DEMOD_DD_MODE_PROP_SPECINV_NORMAL;
	prop->dd_mode.modulation                                          	= DEMOD_DD_MODE_PROP_MODULATION_UNKNOWN;
	prop->dd_mode.bw                                              		= DEMOD_DD_MODE_PROP_BW_BW_6MHZ ;
#endif /* DEMOD_DD_MODE_PROP */

#ifdef    DEMOD_DD_AUTO_MODE_PROP
 	prop->dd_auto_mode.auto_detect					= DEMOD_DD_AUTO_MODE_PROP_DET_DVBT_ONLY_ENABLE ;
#endif /* DEMOD_DD_AUTO_MODE_PROP */

#ifdef    DEMOD_DD_TS_MODE_PROP
	prop->dd_ts_mode.tpMode							= DEMOD_DD_TS_MODE_PROP_TPMODE_DEFAULT; //parallel
	prop->dd_ts_mode.tpClkPol							= DEMOD_DD_TS_MODE_PROP_TPCLKPOL_DEFAULT;
	prop->dd_ts_mode.tpSopPol						= DEMOD_DD_TS_MODE_PROP_TPSOPPOL_DEFAULT;
	prop->dd_ts_mode.tpValPol							= DEMOD_DD_TS_MODE_PROP_TPVALPOL_DEFAULT;
	prop->dd_ts_mode.tpErrPol							= DEMOD_DD_TS_MODE_PROP_TPERRPOL_DEFAULT;
	prop->dd_ts_mode.tpClkSup						= DEMOD_DD_TS_MODE_PROP_TPCLKSUP_DEFAULT;
	prop->dd_ts_mode.tpMsbFirst						= DEMOD_DD_TS_MODE_PROP_TPMSBFST_DEFAULT;
	prop->dd_ts_mode.tpBigEnd							= DEMOD_DD_TS_MODE_PROP_TPBIGEND_DEFAULT;
#endif /* DEMOD_DD_TS_MODE_PROP */

#ifdef    DEMOD_DD_ADC_PROP
       prop->dd_adc_sel.adcClkPllSel 						= DEMOD_DD_ADC_PROP_ADCCLKPLLSEL_DEFAULT;
	   prop->dd_adc_sel.adcClk		 						= DEMOD_DD_ADC_PROP_ADCCLK_DEFAULT;

#endif /* DEMOD_DD_ADC_PROP */

#ifdef    DEMOD_DD_AGC_PROP
	  prop->dd_agc.agc_src  		= DEMOD_DD_AGC_PROP_SRC_INSTANT;
	  prop->dd_agc.agc_pol  		= DEMOD_DD_AGC_PROP_POLARITY_NORMAL;
	  prop->dd_agc.agc_outEn  		= DEMOD_DD_AGC_PROP_OUTEN_ENABLE;
	  prop->dd_agc.agc_outEn_S 		= DEMOD_DD_AGC_PROP_OUTEN_S_ENABLE;
	  prop->dd_agc.agc_frzEn 		= DEMOD_DD_AGC_PROP_FRZ_DISABLE;
	  prop->dd_agc.agc_bw   		= DEMOD_DD_AGC_PROP_BW_DEFAULT;
#endif /* DEMOD_DD_AGC_PROP */


#ifdef    DEMOD_DD_TPOUT_MODE_PROP
	prop->dd_tpout_mode.tpSrMsb						= DEMOD_DD_TPOUT_MODE_PROP_TPSRMSB_ENABLE;
	prop->dd_tpout_mode.tpOutEn 						= DEMOD_DD_TPOUT_MODE_PROP_TPOUTEN_ENABLE;
#endif /* DEMOD_DD_TPOUT_MODE_PROP */

#ifdef    DEMOD_DD_CONSTEL_PROP
       prop->dd_constel.constellation 						= DEMOD_DD_CONSTELATION_PROP_256QAM;
       prop->dd_constel.constel_autodet 					= DEMOD_DD_CONSTELATION_PROP_AUTO_DET_ENABLE;
#endif /* DEMOD_DD_CONSTEL_PROP */


#ifdef    DEMOD_DD_COUNTRY_GRP_PROP //190313
 	prop->dd_country_grp.grp							=  DEMOD_DD_COUNTRY_GRP_PROP_NONE; /* (default) */
#endif /* DEMOD_DD_COUNTRY_GRP_PROP */
	

#ifndef LG3307_API


#ifdef    DEMOD_DD_DISEQC_CONFIG_PROP
  	prop->dd_diseqc_config.message_sel					= DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_SEL_DEFAULT; /* (default : envelop) */
  	prop->dd_diseqc_config.diseqc_2_x_enable			= DEMOD_DD_DISEQC_CONFIG_PROP_EN_2_X_DISABLE; /* (default disable) */
  	prop->dd_diseqc_config.message_repeat_en			= DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_REPEAT_DEFAULT; /* (default 22000) */
#endif /* DEMOD_DD_DISEQC_CONFIG_PROP */

#ifdef    DEMOD_DD_DVBT_HIERARCHY_PROP
       prop->dd_dvbt_hp_sel.hierhpsel 					= DEMOD_DD_DVBT_HIERARCHY_PROP_HIERHPSEL_HIGH;
#endif /* DEMOD_DD_DVBT_HIERARCHY_PROP */

#ifdef    DEMOD_DD_DVBT2_MODE_PROP
       prop->dd_dvbt2_lock_mode.lock_mode				= DEMOD_DD_DVBT2_MODE_PROP_LOCK_MODE_BASE_ONLY;
#endif /* DEMOD_DD_DVBT2_MODE_PROP */

#ifdef    DEMOD_DD_DVBS_AFC_RANGE_PROP
       prop->dd_dvbs_afc_range.range_khz					= DEMOD_DD_DVBS_AFC_RANGE_PROP_RANGE_KHZ_DEFAULT;
#endif /* DEMOD_DD_DVBS_AFC_RANGE_PROP */

#ifdef    DEMOD_DD_DVBS_OPMSEL_PROP
 	prop->dd_dvbs_opm_sel.opmSel 					= DEMOD_DD_DVBS_OPM_SEL_PROP_NORMAL_MODE;
#endif /* DEMOD_DD_DVBS_OPMSEL_PROP */
#endif




}

/***********************************************************************************************************************
  DEMOD_L1_PropertyText function
  Use:        property text function
              Used to turn the property data into clear text.
  Parameter: *prop     the DEMOD_PropObject property structure (containing all properties)
  Parameter: prop_code the property Id (used to know which property to use)
  Returns:    NO_DEMOD_ERROR if successful.
 ***********************************************************************************************************************/
UINT8  DEMOD_L1_PropertyText          (LX_DEMOD_L1_PropObj   *prop, UINT32 prop_code)
{
	switch (prop_code)
	{
		#ifdef        DEMOD_DD_BER_RESOL_PROP
		 case         DEMOD_DD_BER_RESOL_PROP_CODE:
		 	{
				DBB_DUMP_PRINT(" [PROP] BER Resolution = EXP %d \n", prop->dd_ber_resol.exp);
		 	}
		 	break;
		#endif /*     DEMOD_DD_BER_RESOL_PROP */

		#ifdef        DEMOD_DD_IF_FREQ_PROP
		 case         DEMOD_DD_IF_FREQ_PROP_CODE:
		 	{
				DBB_DUMP_PRINT("[PROP] IF Frequency = %d [KHz] \n", prop->dd_if_freq.if_freq);
		 	}
		 	break;
		#endif /*     DEMOD_DD_IF_FREQ_PROP */

		#ifdef        DEMOD_DD_CLOCK_MODE_PROP
		 case         DEMOD_DD_CLOCK_MODE_PROP_CODE:
		 	{
				//DBB_DUMP_PRINT("[PROP]  Clock Source   = %s \n", (prop->dd_clk_mode.clk_mode == DEMOD_DD_CLOCK_MODE_PROP_24MHZ) ? "24 MHz" : "20 MHz");
				DBB_DUMP_PRINT("[PROP]  Clock  = %s \n",	(prop->dd_clk_mode.clk_mode   == DEMOD_DD_CLOCK_MODE_PROP_20MHZ )  ? "20MHz" :
															(prop->dd_clk_mode.clk_mode   == DEMOD_DD_CLOCK_MODE_PROP_24MHZ	)  ? "24MHz" :
															(prop->dd_clk_mode.clk_mode   == DEMOD_DD_CLOCK_MODE_PROP_25MHZ	)  ? "25MHz" :
															(prop->dd_clk_mode.clk_mode   == DEMOD_DD_CLOCK_MODE_PROP_40MHZ	)  ? "40MHz" :
															(prop->dd_clk_mode.clk_mode   == DEMOD_DD_CLOCK_MODE_PROP_48MHZ	)  ? "48MHz" :
															(prop->dd_clk_mode.clk_mode   == DEMOD_DD_CLOCK_MODE_PROP_50MHZ	)  ? "50MHz" :
															(prop->dd_clk_mode.clk_mode   == DEMOD_DD_CLOCK_MODE_PROP_60P8MHZ	) ?  "60.8MHz" :  "UNKNOWN");
		 	}
		 	break;
		#endif /*     DEMOD_DD_CLOCK_MODE_PROP */


		#ifdef        DEMOD_DD_MODE_PROP
		 case         DEMOD_DD_MODE_PROP_CODE:
		 	{
				DBB_DUMP_PRINT("[PROP]  Tune mode  = %s \n",(prop->dd_mode.tuneMode   == DEMOD_DD_MODE_PROP_TUNEMODE_AUTO) ?  "AUTO" :
														(prop->dd_mode.tuneMode   == DEMOD_DD_MODE_PROP_TUNEMODE_MANUAL)  ? "MANUAL" :
														(prop->dd_mode.tuneMode   == DEMOD_DD_MODE_PROP_TUNEMODE_FIXED_DATA)  ?  "FIXED_DATA" : "NOMAL");

				DBB_DUMP_PRINT("[PROP]  Spectrum Inversion Mode   = %s \n",(prop->dd_mode.specinvauto   == DEMOD_DD_MODE_PROP_SPECINV_AUTO) ?  "AUTO" :  "NOMAL");
				DBB_DUMP_PRINT("[PROP]  Spectrum  = %s \n",(prop->dd_mode.specinv   == DEMOD_DD_MODE_PROP_SPECINV_INVERSION)  ? "Inverted" :  "Normal");

				DBB_DUMP_PRINT("[PROP]  Modulation = %s \n", DEMOD_L1_API_StandardName(prop->dd_mode.modulation));
				DBB_DUMP_PRINT("[PROP]  Modulation = 0x%x \n", (prop->dd_mode.modulation));


				DBB_DUMP_PRINT("[PROP]  Band Width  = %s \n",	(prop->dd_mode.bw   == DEMOD_DD_MODE_PROP_BW_BW_5MHZ)  ? "5MHz" :
														(prop->dd_mode.bw   == DEMOD_DD_MODE_PROP_BW_BW_6MHZ)  ? "6MHz" :
														(prop->dd_mode.bw   == DEMOD_DD_MODE_PROP_BW_BW_7MHZ)  ? "7MHz" :
														(prop->dd_mode.bw   == DEMOD_DD_MODE_PROP_BW_BW_8MHZ)  ? "8MHz" :
														(prop->dd_mode.bw   == DEMOD_DD_MODE_PROP_BW_BW_1D7MHZ) ?  "1.7MHz" :  "UNKNOWN");

		 	}
		 	break;
		#endif /*     DEMOD_DD_MODE_PROP */

		#ifdef        DEMOD_DD_AUTO_MODE_PROP
		 case         DEMOD_DD_AUTO_MODE_PROP_CODE:
		 	{
				DBB_DUMP_PRINT("[PROP]  Auto mode   = %s \n", (prop->dd_auto_mode.auto_detect   == DEMOD_DD_AUTO_MODE_PROP_DET_DVBT_DVBT2_ENABLE)  ? "DVBT_DVBT2" :
														(prop->dd_auto_mode.auto_detect   == DEMOD_DD_AUTO_MODE_PROP_DET_DVBT_ONLY_ENABLE)  ? "DVBT Only" :
														(prop->dd_auto_mode.auto_detect   == DEMOD_DD_AUTO_MODE_PROP_DET_DVBT2_ONLY_ENABLE)  ? "DVBT2 Only" :
														(prop->dd_auto_mode.auto_detect   == DEMOD_DD_AUTO_MODE_PROP_DET_DVBC_DVBC2_ENABLE)  ? "DVBC_DVBC2" :
														(prop->dd_auto_mode.auto_detect   == DEMOD_DD_AUTO_MODE_PROP_DET_DVBC_ONLY_ENABLE)  ? "DVBC Only" :
														(prop->dd_auto_mode.auto_detect   == DEMOD_DD_AUTO_MODE_PROP_DET_DVBC2_ONLY_ENABLE)  ? "DVBC2 Only" :
														(prop->dd_auto_mode.auto_detect   == DEMOD_DD_AUTO_MODE_PROP_DET_DVBS_DVBS2_ENABLE) ?  "DVBS_DVBS2" :
														(prop->dd_auto_mode.auto_detect   == DEMOD_DD_AUTO_MODE_PROP_DET_DVBS_ONLY_ENABLE)  ? "DVBS Only" :
														(prop->dd_auto_mode.auto_detect   == DEMOD_DD_AUTO_MODE_PROP_DET_DVBS2_ONLY_ENABLE)  ? "DVBS2 Only" :  "UNKNOWN");

		 	}
		 	break;
		#endif /*     DEMOD_DD_AUTO_MODE_PROP */

		#ifdef        DEMOD_DD_TS_MODE_PROP
		 case         DEMOD_DD_TS_MODE_PROP_CODE:
		 	{
				DBB_DUMP_PRINT("[PROP] TP Mode   = %s \n", (prop->dd_ts_mode.tpMode == DEMOD_DD_TS_MODE_PROP_TPMODE_PARALLEL)  ? "Parallel" : "Serial");
				DBB_DUMP_PRINT("[PROP] TP CLK Polarization   = %s \n", (prop->dd_ts_mode.tpClkPol == DEMOD_DD_TS_MODE_PROP_TPCLKPOL_POS_EDGE)  ? "Positive Edge" : "Negative Edge");
				DBB_DUMP_PRINT("[PROP] TP SOP Polarization   = %s \n", (prop->dd_ts_mode.tpSopPol == DEMOD_DD_TS_MODE_PROP_TPSOPPOL_HIGH) ?  "High Active" : "Low Active");
				DBB_DUMP_PRINT("[PROP] TP VAL Polarization  = %s \n", (prop->dd_ts_mode.tpValPol == DEMOD_DD_TS_MODE_PROP_TPVALPOL_HIGH)  ? "High Active" : "Low Active");
				DBB_DUMP_PRINT("[PROP] TP ERR Polarization   = %s \n", (prop->dd_ts_mode.tpErrPol == DEMOD_DD_TS_MODE_PROP_TPERRPOL_HIGH)  ? "High Active" : "Low Active");
				DBB_DUMP_PRINT("[PROP] TP CLK Suppression   = %s \n", (prop->dd_ts_mode.tpClkSup == DEMOD_DD_TS_MODE_PROP_TPCLKSUP_ENABLE)  ? "Enable" : "Disable");
				DBB_DUMP_PRINT("[PROP] TP MSB First   = %s \n", (prop->dd_ts_mode.tpMsbFirst == DEMOD_DD_TS_MODE_PROP_TPMSBFST_ENABLE)  ? "Enable" : "Disable");
		 	}
		 	break;
		#endif /*     DEMOD_DD_TS_MODE_PROP */

		#ifdef        DEMOD_DD_ADC_PROP
		 case         DEMOD_DD_ADC_PROP_CODE:
		 	{
				    DBB_DUMP_PRINT("[PROP] ADC CLK   = %s \n", (prop->dd_adc_sel.adcClkPllSel == DEMOD_DD_ADC_PROP_ADCCLKPLLSEL_SOC_PLL) ? "SOC PLL" :
					 								(prop->dd_adc_sel.adcClkPllSel == DEMOD_DD_ADC_PROP_ADCCLKPLLSEL_TUNER_PLL) ?"TUENR PLL" : "XTAL CLOCK");
					DBB_DUMP_PRINT("[PROP] ADC CLK   = %d \n", prop->dd_adc_sel.adcClk);
					 								
		 	}
		 	break;
		#endif /*     DEMOD_DD_ADC_PROP */

		#ifdef        DEMOD_DD_AGC_PROP
		 case         DEMOD_DD_AGC_PROP_CODE:
		 	{
				DBB_DUMP_PRINT("[PROP] AGC Source   	= %s \n", (prop->dd_agc.agc_src == DEMOD_DD_AGC_PROP_SRC_INSTANT)  ? "Instant" : "Average");
				DBB_DUMP_PRINT("[PROP] AGC Polarization = %s \n", (prop->dd_agc.agc_pol  == DEMOD_DD_AGC_PROP_POLARITY_NORMAL)  ? "Normal" : "Inverted");
				DBB_DUMP_PRINT("[PROP] AGC Output   	= %s \n", (prop->dd_agc.agc_outEn == DEMOD_DD_AGC_PROP_OUTEN_ENABLE)  ? "Enable" : "Disable");
				DBB_DUMP_PRINT("[PROP] AGC Output_S   	= %s \n", (prop->dd_agc.agc_outEn_S == DEMOD_DD_AGC_PROP_OUTEN_S_ENABLE)  ? "Enable" : "Disable");
				DBB_DUMP_PRINT("[PROP] AGC Freeze  	    = %s \n", (prop->dd_agc.agc_frzEn == DEMOD_DD_AGC_PROP_FRZ_DISABLE)  ? "Disable" : "Enable");
				DBB_DUMP_PRINT("[PROP] AGC Bandwidth    = %d \n", prop->dd_agc.agc_bw );
				
		 	}
		 	break;
		#endif /*     DEMOD_DD_AGC_PROP */

		#ifdef        DEMOD_DD_TPOUT_MODE_PROP
		 case         DEMOD_DD_TPOUT_MODE_PROP_CODE:
		 	{
				DBB_DUMP_PRINT("[PROP] TP OUT    = %s \n", (prop->dd_tpout_mode.tpOutEn  == DEMOD_DD_TPOUT_MODE_PROP_TPOUTEN_ENABLE)  ? "Enable" : "Disable");
		 	}
		 	break;
		#endif /*     DEMOD_DD_TPOUT_MODE_PROP */

		#ifdef        DEMOD_DD_CONSTEL_PROP
		 case         DEMOD_DD_CONSTEL_PROP_CODE:
		 	{
				DBB_DUMP_PRINT("[PROP] Constellation mode    = %s \n", (prop->dd_constel.constellation   == DEMOD_DD_CONSTELATION_PROP_16QAM) ?  "16QAM" :
																	(prop->dd_constel.constellation   == DEMOD_DD_CONSTELATION_PROP_32QAM) ?  "32QAM" :
																	(prop->dd_constel.constellation   == DEMOD_DD_CONSTELATION_PROP_64QAM)  ? "64QAM" :
																	(prop->dd_constel.constellation   == DEMOD_DD_CONSTELATION_PROP_128QAM) ?  "128QAM" :
																	(prop->dd_constel.constellation  == DEMOD_DD_CONSTELATION_PROP_256QAM) ?  "256QAM" :
																	(prop->dd_constel.constellation  == DEMOD_DD_CONSTELATION_PROP_VSB) ?  "VSB" :
																	(prop->dd_constel.constellation  == DEMOD_DD_CONSTELATION_PROP_DQPSK) ?  "DQSK" :
																	(prop->dd_constel.constellation  == DEMOD_DD_CONSTELATION_PROP_QPSK) ?  "QPSK" :"UNKNOWN");

				DBB_DUMP_PRINT("[PROP] QAM mode Setting type    = %s \n", (prop->dd_constel.constel_autodet  == DEMOD_DD_CONSTELATION_PROP_AUTO_DET_ENABLE) ?  "AUTO" : "MANUAL");
		 	}
		 	break;
		#endif /*     DEMOD_DD_CONSTEL_PROP */
		
		
		#ifdef    DEMOD_DD_COUNTRY_GRP_PROP //190313
		 case        DEMOD_DD_COUNTRY_GRP_PROP_CODE:
		 	{
				DBB_DUMP_PRINT("[PROP] Country Group    = %s \n", (prop->dd_country_grp.grp   == DEMOD_DD_COUNTRY_GRP_PROP_NONE) ?  "NONE" :
																	(prop->dd_country_grp.grp  == DEMOD_DD_COUNTRY_GRP_PROP_EU) ?  "EU" :
																	(prop->dd_country_grp.grp  == DEMOD_DD_COUNTRY_GRP_PROP_END) ?  "END" : "UNKNOWN");
		 	}
		 	break;		  	
		#endif /* DEMOD_DD_COUNTRY_GRP_PROP */



#ifndef LG3307_API

		#ifdef        DEMOD_DD_DISEQC_CONFIG_PROP
		 case         DEMOD_DD_DISEQC_CONFIG_PROP_CODE:
		 	{
				DBB_DUMP_PRINT("[PROP] DISEqC message type = %s \n", (prop->dd_diseqc_config.message_sel == DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_SEL_ENVELOPE) ? "Envelope" : "22KHz Tone");
				DBB_DUMP_PRINT("[PROP] DISEqC 2.0 =  %s \n",(prop->dd_diseqc_config.diseqc_2_x_enable  == DEMOD_DD_DISEQC_CONFIG_PROP_EN_2_X_ENABLE) ? " Supported" : "NOT Supported");
				DBB_DUMP_PRINT("[PROP] Message repeat enable = %s\n",(prop->dd_diseqc_config.message_repeat_en  == DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_REPEAT_ENABLE) ?  " ON" : "OFF");
		 	}
		 	break;
		#endif /*     DEMOD_DD_DISEQC_CONFIG_PROP */

		#ifdef        DEMOD_DD_DVBT_HIERARCHY_PROP
		 case         DEMOD_DD_DVBT_HIERARCHY_PROP_CODE:
		 	{
				DBB_DUMP_PRINT("[PROP] DVBT HP sel    = %s \n", (prop->dd_dvbt_hp_sel.hierhpsel   == DEMOD_DD_DVBT_HIERARCHY_PROP_HIERHPSEL_HIGH) ?  "Enable" : "Disable");
		 	}
		 	break;
		#endif /*     DEMOD_DD_DVBT_HIERARCHY_PROP */

		#ifdef        DEMOD_DD_DVBT2_MODE_PROP
		 case         DEMOD_DD_DVBT2_MODE_PROP_CODE:
		 	{
				DBB_DUMP_PRINT("[PROP] DVBT2 lock mode    = %s \n", (prop->dd_dvbt2_lock_mode.lock_mode   == DEMOD_DD_DVBT2_MODE_PROP_LOCK_MODE_BASE_ONLY) ?  "ANY" :
															(prop->dd_dvbt2_lock_mode.lock_mode   == DEMOD_DD_DVBT2_MODE_PROP_LOCK_MODE_BASE_ONLY)  ? "BASE Only" :
															(prop->dd_dvbt2_lock_mode.lock_mode   == DEMOD_DD_DVBT2_MODE_PROP_LOCK_MODE_LITE_ONLY)  ? "LITE Only" : "RESERVED");
		 	}
		 	break;
		#endif /*     DEMOD_DD_DVBT2_MODE_PROP */

		#ifdef        DEMOD_DD_DVBS_OPMSEL_PROP
		 case         DEMOD_DD_DVBS_OPMSEL_PROP_CODE:
		 	{
				DBB_DUMP_PRINT("[PROP]  DVBS Blind mode type   = %s \n", (prop->dd_dvbs_opm_sel.opmSel  == DEMOD_DD_DVBS_OPM_SEL_PROP_BLIND_SCAN_MODE)  ? "Blind Scan" :
														(prop->dd_dvbs_opm_sel.opmSel  == DEMOD_DD_DVBS_OPM_SEL_PROP_BLIND_LOCK_MODE) ?  "Blind LOCK" : "NORMAL");
		 	}
		 	break;
		#endif /*     DEMOD_DD_DVBS_OPMSEL_PROP */
		
		#ifdef        DEMOD_DD_DVBS_AFC_RANGE_PROP
		 case         DEMOD_DD_DVBS_AFC_RANGE_PROP_CODE:
		 	{
				DBB_DUMP_PRINT("[PROP]DVBS AFC Range  = %d \n", prop->dd_dvbs_afc_range.range_khz );
		 	}
		 	break;
		#endif /*     DEMOD_DD_DVBS_AFC_RANGE_PROP */
#endif

		 default : return ERROR_DEMOD_UNKNOWN_PROPERTY; break;
	}

    	return NO_DEMOD_ERROR;


}








