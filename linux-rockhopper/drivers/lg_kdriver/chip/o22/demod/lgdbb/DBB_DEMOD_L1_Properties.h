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
**  Name:DBB_DEMOD_L1_Properties.h
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

#ifndef _DBB_DEMOD_L1_PROPERTIES_H_
#define _DBB_DEMOD_L1_PROPERTIES_H_

/*-------------------------------------------------------------------------*/
/* DEMOD Properties definitions to enable */
#define DEMOD_PROP_MODE
#define DEMOD_PROP_IF_FREQ
#define DEMOD_PROP_CLOCK_MODE
#define DEMOD_PROP_BER_RESOL
#define DEMOD_PROP_TS_MODE
#define DEMOD_PROP_ADC
#define DEMOD_PROP_CLKPHASE
#define DEMOD_PROP_SDRAM
#define DEMOD_PROP_TWOCTI
#define DEMOD_PROP_SDRAM_PWR
#define DEMOD_PROP_ATSC3_OUTPUT_TYPE
#define DEMOD_PROP_AGC
#define DEMOD_PROP_TPOUT_MODE
#define DEMOD_PROP_CONSTEL
#define DEMOD_PROP_COUNTRY_GRP
#define DEMOD_PROP_AUTO_MODE
#define DEMOD_PROP_DVBT_HIERARCHY
#define DEMOD_PROP_DVBT2_MODE
#define DEMOD_PROP_DISEQC_CONFIG
#define DEMOD_PROP_DVBS_OPMSEL
#define DEMOD_PROP_AFC_RANGE
#define DEMOD_PROP_DVBS2_AFC_RANGE

/*-------------------------------------------------------------------------*/
/* DEMOD_PROP_MODE property definition */
#ifdef DEMOD_PROP_MODE
#define DEMOD_PROP_MODE_CODE							0x100A

typedef struct
{ /* SET_MODE_PROP_struct */
	UINT8 tuneMode;
	UINT8 specinvauto;
	UINT8 specinv;
	UINT8 modulation;
	UINT8 bw;
} LX_DEMOD_PROP_MODE_struct;

#define DEMOD_PROP_MODE_TUNE_LSB						0
#define DEMOD_PROP_MODE_TUNE_MASK						0x03
#define DEMOD_PROP_MODE_TUNE_NORMAL						0
#define DEMOD_PROP_MODE_TUNE_AUTO						1
#define DEMOD_PROP_MODE_TUNE_MANUAL						2
#define DEMOD_PROP_MODE_TUNE_FIXED_DATA					3
#define DEMOD_PROP_MODE_TUNE_BLIND					 	4
#define DEMOD_PROP_MODE_TUNE_DEFAULT					DEMOD_PROP_MODE_TUNE_NORMAL

#define DEMOD_PROP_MODE_SPECINVAUTO_LSB					2
#define DEMOD_PROP_MODE_SPECINVAUTO_MASK				0x01
#define DEMOD_PROP_MODE_SPECINVAUTO_AUTO				0
#define DEMOD_PROP_MODE_SPECINVAUTO_MANUAL				1

#define DEMOD_PROP_MODE_SPECINV_LSB						3
#define DEMOD_PROP_MODE_SPECINV_MASK					0x01
#define DEMOD_PROP_MODE_SPECINV_INVERSION				1
#define DEMOD_PROP_MODE_SPECINV_NORMAL					0

#define DEMOD_PROP_MODE_BW_LSB							4
#define DEMOD_PROP_MODE_BW_MASK							0x0f

#define DEMOD_PROP_MODE_BW_4MHZ							4
#define DEMOD_PROP_MODE_BW_5MHZ							5
#define DEMOD_PROP_MODE_BW_6MHZ							6
#define DEMOD_PROP_MODE_BW_7MHZ							7
#define DEMOD_PROP_MODE_BW_8MHZ							8
#define DEMOD_PROP_MODE_BW_1D7MHZ						2
#define DEMOD_PROP_MODE_BW_36MHZ						36
#define DEMOD_PROP_MODE_BW_40MHZ						40
#define DEMOD_PROP_MODE_BW_DEFAULT						DEMOD_PROP_MODE_BW_8MHZ

#define DEMOD_PROP_MODE_MODULATION_LSB					8
#define DEMOD_PROP_MODE_MODULATION_MASK					0xff

#endif /*DEMOD_DD_MODE */

/*-------------------------------------------------------------------------*/
/* DEMOD_PROP_IF_FREQ property definition */
#ifdef DEMOD_PROP_IF_FREQ
#define DEMOD_PROP_IF_FREQ_CODE							0x100B

typedef struct
{ /* SET_IF_FREQ_PROP_struct */
	UINT32 if_freq;
} LX_DEMOD_PROP_IF_FREQ_struct;

#define DEMOD_PROP_IF_FREQ_IF_FREQ_LSB					0
#define DEMOD_PROP_IF_FREQ_IF_FREQ_MASK					0xffff
#define DEMOD_PROP_IF_FREQ_IF_FREQ_0MHZ					0
#define DEMOD_PROP_IF_FREQ_IF_FREQ_4P5MHZ				4500
#define DEMOD_PROP_IF_FREQ_IF_FREQ_5MHZ					5000
#define DEMOD_PROP_IF_FREQ_IF_FREQ_6MHZ					6000
#define DEMOD_PROP_IF_FREQ_IF_FREQ_DEFAULT				DEMOD_PROP_IF_FREQ_IF_FREQ_6MHZ

#endif /*DEMOD_DD_IF_FREQ */

/*-------------------------------------------------------------------------*/
/* depreacated DEMOD_PROP_CLOCK_MODE
 * clk_mode have to set before demod initialize.
 */
#ifdef DEMOD_PROP_CLOCK_MODE
#define DEMOD_PROP_CLOCK_MODE_CODE 						0x100D

typedef struct
{ /* SET_CLOCK_MODE_PROP_struct */
	UINT32 clk_mode;
}  LX_DEMOD_PROP_CLOCK_MODE_struct;

#define DEMOD_PROP_CLOCK_MODE_LSB						0
#define DEMOD_PROP_CLOCK_MODE_MASK						0xffffffff
#define DEMOD_PROP_CLOCK_MODE_15P2MHZ					0x3B60
#define DEMOD_PROP_CLOCK_MODE_20MHZ 					0x4E20
#define DEMOD_PROP_CLOCK_MODE_21P6MHZ					0x5460
#define DEMOD_PROP_CLOCK_MODE_22MHZ						0x55F0
#define DEMOD_PROP_CLOCK_MODE_23MHZ						0x59D8
#define DEMOD_PROP_CLOCK_MODE_24MHZ						0x5DC0
#define DEMOD_PROP_CLOCK_MODE_25MHZ						0x61A8
#define DEMOD_PROP_CLOCK_MODE_26MHZ						0x6590
#define DEMOD_PROP_CLOCK_MODE_27MHZ						0x6978
#define DEMOD_PROP_CLOCK_MODE_28MHZ						0x6D60
#define DEMOD_PROP_CLOCK_MODE_29MHZ						0x7148
#define DEMOD_PROP_CLOCK_MODE_30MHZ						0x7530
#define DEMOD_PROP_CLOCK_MODE_40MHZ						0x9C40
#define DEMOD_PROP_CLOCK_MODE_48MHZ						0xBB80
#define DEMOD_PROP_CLOCK_MODE_50MHZ						0xC350
#define DEMOD_PROP_CLOCK_MODE_60P8MHZ					0xED80
#define DEMOD_PROP_CLOCK_MODE_86P4MHZ					0x15180
#define DEMOD_PROP_CLOCK_MODE_96MHZ						0x17700
#define DEMOD_PROP_CLOCK_MODE_124MHZ					0x1E460
#define DEMOD_PROP_CLOCK_MODE_400MHZ					0x61A80
#define DEMOD_PROP_CLOCK_MODE_DEFAULT					DEMOD_PROP_CLOCK_MODE_24MHZ

#endif /*DEMOD_DD_CLOCK_MODE */

/*-------------------------------------------------------------------------*/
/* LGDBB DD_BER_RESOL property definition */
#ifdef DEMOD_PROP_BER_RESOL
#define DEMOD_PROP_BER_RESOL_CODE						0x100E

typedef struct
{ /* LX_DEMOD_PROP_BER_RESOL_struct */
	UINT8	 exp;
} LX_DEMOD_PROP_BER_RESOL_struct;

 /* DD_BER_RESOL property, EXP field definition (NO TITLE)*/
#define DEMOD_PROP_BER_RESOL_EXP_LSB					0
#define DEMOD_PROP_BER_RESOL_EXP_MASK					0x0f
#define DEMOD_PROP_BER_RESOL_EXP_EXPLO_5				5
#define DEMOD_PROP_BER_RESOL_EXP_EXPLO_7				7
#define DEMOD_PROP_BER_RESOL_EXP_DEFAULT				DEMOD_PROP_BER_RESOL_EXP_EXPLO_5
#endif /* DEMOD_PROP_BER_RESOL */

/*-------------------------------------------------------------------------*/
/* LGDBB DD_TS_MODE property definition */   //JEONGPIL.YUN
#ifdef DEMOD_PROP_TS_MODE
#define DEMOD_PROP_TS_MODE_CODE							0x1002

typedef struct
{ /* SET_TS_MODE_PROP_struct */
	UINT8 tpMode;
	UINT8 tpClkPol;
	UINT8 tpSopPol;
	UINT8 tpValPol;
	UINT8 tpErrPol;
	UINT8 tpClkSup;
	UINT8 tpMsbFirst;
	UINT8 tpBigEnd;
}  LX_DEMOD_PROP_TS_MODE_struct;

#define DEMOD_PROP_TS_MODE_TPMODE_LSB					7
#define DEMOD_PROP_TS_MODE_TPMODE_MASK					0x01
#define DEMOD_PROP_TS_MODE_TPMODE_PARALLEL				1
#define DEMOD_PROP_TS_MODE_TPMODE_SERIAL				0
#define DEMOD_PROP_TS_MODE_TPMODE_DEFAULT				DEMOD_PROP_TS_MODE_TPMODE_PARALLEL

#define DEMOD_PROP_TS_MODE_TPCLKPOL_LSB					6
#define DEMOD_PROP_TS_MODE_TPCLKPOL_MASK				0x01
#define DEMOD_PROP_TS_MODE_TPCLKPOL_POS_EDGE			1
#define DEMOD_PROP_TS_MODE_TPCLKPOL_NEG_EDGE			0
#define DEMOD_PROP_TS_MODE_TPCLKPOL_DEFAULT				DEMOD_PROP_TS_MODE_TPCLKPOL_NEG_EDGE

#define DEMOD_PROP_TS_MODE_TPSOPPOL_LSB					5
#define DEMOD_PROP_TS_MODE_TPSOPPOL_MASK				0x01
#define DEMOD_PROP_TS_MODE_TPSOPPOL_HIGH				1
#define DEMOD_PROP_TS_MODE_TPSOPPOL_LOW					0
#define DEMOD_PROP_TS_MODE_TPSOPPOL_DEFAULT				DEMOD_PROP_TS_MODE_TPSOPPOL_HIGH

#define DEMOD_PROP_TS_MODE_TPVALPOL_LSB					4
#define DEMOD_PROP_TS_MODE_TPVALPOL_MASK				0x01
#define DEMOD_PROP_TS_MODE_TPVALPOL_HIGH				1
#define DEMOD_PROP_TS_MODE_TPVALPOL_LOW					0
#define DEMOD_PROP_TS_MODE_TPVALPOL_DEFAULT				DEMOD_PROP_TS_MODE_TPVALPOL_HIGH

#define DEMOD_PROP_TS_MODE_TPERRPOL_LSB					3
#define DEMOD_PROP_TS_MODE_TPERRPOL_MASK				0x01
#define DEMOD_PROP_TS_MODE_TPERRPOL_HIGH				1
#define DEMOD_PROP_TS_MODE_TPERRPOL_LOW					0
#define DEMOD_PROP_TS_MODE_TPERRPOL_DEFAULT				DEMOD_PROP_TS_MODE_TPERRPOL_HIGH

#define DEMOD_PROP_TS_MODE_TPCLKSUP_LSB					2
#define DEMOD_PROP_TS_MODE_TPCLKSUP_MASK				0x01
#define DEMOD_PROP_TS_MODE_TPCLKSUP_ENABLE				1
#define DEMOD_PROP_TS_MODE_TPCLKSUP_DIABLE				0
#define DEMOD_PROP_TS_MODE_TPCLKSUP_DEFAULT				DEMOD_PROP_TS_MODE_TPCLKSUP_DIABLE

#define DEMOD_PROP_TS_MODE_TPMSBFST_LSB					1
#define DEMOD_PROP_TS_MODE_TPMSBFST_MASK				0x01
#define DEMOD_PROP_TS_MODE_TPMSBFST_ENABLE				1
#define DEMOD_PROP_TS_MODE_TPMSBFST_DISABLE				0
#define DEMOD_PROP_TS_MODE_TPMSBFST_DEFAULT				DEMOD_PROP_TS_MODE_TPMSBFST_ENABLE

#define DEMOD_PROP_TS_MODE_TPBIGEND_LSB					0
#define DEMOD_PROP_TS_MODE_TPBIGEND_MASK				0x01
#define DEMOD_PROP_TS_MODE_TPBIGEND_ENABLE				1
#define DEMOD_PROP_TS_MODE_TPBIGEND_DISABLE				0
#define DEMOD_PROP_TS_MODE_TPBIGEND_DEFAULT				DEMOD_PROP_TS_MODE_TPBIGEND_ENABLE

#endif /*SET_TS_MODE */

/*-------------------------------------------------------------------------*/
/* LGDBB DD_ADC  property definition */   //JEONGPIL.YUN
#ifdef DEMOD_PROP_ADC
#define DEMOD_PROP_ADC_CODE								0x100C	 //check number !!

typedef struct
{/*SET_ADC_PROP_CODE_struct */
	UINT8 adcClkPllSel;
	UINT32 adcClk;
}  LX_DEMOD_PROP_ADC_CODE_struct;

#define DEMOD_PROP_ADC_ADCCLKPLLSEL_LSB					28
#define DEMOD_PROP_ADC_ADCCLKPLLSEL_MASK				0x0F
#define DEMOD_PROP_ADC_ADCCLKPLLSEL_EXT_XTAL			0
#define DEMOD_PROP_ADC_ADCCLKPLLSEL_SOC_PLL				1
#define DEMOD_PROP_ADC_ADCCLKPLLSEL_TUNER_PLL			2
#define DEMOD_PROP_ADC_ADCCLKPLLSEL_DEFAULT				1

#define DEMOD_PROP_ADC_ADCCLK_LSB						0
#define DEMOD_PROP_ADC_ADCCLK_MASK						0x0FFFFFFF
#define DEMOD_PROP_ADC_ADCCLK_20MHZ						0x4E20
#define DEMOD_PROP_ADC_ADCCLK_24MHZ						0x5DC0
#define DEMOD_PROP_ADC_ADCCLK_25MHZ						0x61A8
#define DEMOD_PROP_ADC_ADCCLK_60P8MHZ					0xED80
#define DEMOD_PROP_ADC_ADCCLK_80MHZ						0x13880
#define DEMOD_PROP_ADC_ADCCLK_96MHZ						0x17700
#define DEMOD_PROP_ADC_ADCCLK_124MHZ					0x1E460
#define DEMOD_PROP_ADC_ADCCLK_DEFAULT					DEMOD_PROP_ADC_ADCCLK_24MHZ

#endif /*SET_ADC_PROP*/

/*-------------------------------------------------------------------------*/
/* LGDBB DD_CLK PHASE  property definition */   
#ifdef DEMOD_PROP_CLKPHASE
#define DEMOD_PROP_CLKPHASE_CODE						0x1010

typedef struct
{/*SET_CLKPHASE_PROP_CODE_struct */
	UINT8 adSamsel;
	UINT8 adcOutClksel;
}  LX_DEMOD_PROP_CLKPHASE_CODE_struct;

#define DEMOD_PROP_CLKPHASE_LSB							0
#define DEMOD_PROP_CLKPHASE_MASK						0xff

#define DEMOD_PROP_CLKPHASE_ADSAMSEL_LSB				7
#define DEMOD_PROP_CLKPHASE_ADSAMSEL_MASK				0x01
#define DEMOD_PROP_CLKPHASE_ADSAMSEL_NORMAL				0
#define DEMOD_PROP_CLKPHASE_ADSAMSEL_INV				1

#define DEMOD_PROP_CLKPHASE_ADCOUTCLK_LSB			 	0
#define DEMOD_PROP_CLKPHASE_ADCOUTCLK_MASK				0x01
#define DEMOD_PROP_CLKPHASE_ADCOUTCLK_NORMAL			0
#define DEMOD_PROP_CLKPHASE_ADCOUTCLK_INV				1

#endif
/*-------------------------------------------------------------------------*/
/* LGDBB DD_SDRAM  property definition */   
#ifdef DEMOD_PROP_SDRAM
#define DEMOD_PROP_SDRAM_CODE							0x1021

typedef struct
{/*SET_SDRAM_PROP_CODE_struct */
	UINT8 sdRamOn;
}  LX_DEMOD_PROP_SDRAM_CODE_struct;

#define DEMOD_PROP_SDRAM_LSB							0
#define DEMOD_PROP_SDRAM_MASK							0x03
#define DEMOD_PROP_SDRAM_SDRAM_ON						1
#define DEMOD_PROP_SDRAM_SDRAM_OFF						0
#define DEMOD_PROP_SDRAM_SDRAM_UNKNOWN					2

#endif
/*-------------------------------------------------------------------------*/
/* LGDBB DD_TWOCTI  property definition */   
#ifdef DEMOD_PROP_TWOCTI
#define DEMOD_PROP_TWOCTI_CODE							0x1022

typedef struct
{/*SET_TWOCTI_PROP_CODE_struct */
	UINT8 twoCtiOn;
}  LX_DEMOD_PROP_TWOCTI_CODE_struct;

#define DEMOD_PROP_TWOCTI_LSB							0
#define DEMOD_PROP_TWOCTI_MASK							0x03
#define DEMOD_PROP_TWOCTI_TWOCTI_ON						1
#define DEMOD_PROP_TWOCTI_TWOCTI_OFF					0
#define DEMOD_PROP_TWOCTI_TWOCTI_UNKNOWN				2

#endif

/*-------------------------------------------------------------------------*/
/* LGDBB DD_SDRAM_POWER property definition */   
#ifdef DEMOD_PROP_SDRAM_PWR
#define DEMOD_PROP_SDRAM_PWR_CODE						0x001023

typedef struct
{/*SET_SDRAM_PWR_PROP_CODE_struct */
	UINT8 sdRamPwrOn;
}  LX_DEMOD_PROP_SDRAM_PWR_CODE_struct;

#define DEMOD_PROP_SDRAM_PWR_LSB						0
#define DEMOD_PROP_SDRAM_PWR_MASK						0x03
#define DEMOD_PROP_SDRAM_PWR_PWR_ON						1
#define DEMOD_PROP_SDRAM_PWR_PWR_OFF					0
#define DEMOD_PROP_SDRAM_PWR_PWR_UNKNOWN				2

#endif

/*-------------------------------------------------------------------------*/
/* LGDBB DD_ATSC3_OUTPUT_TYPE property definition */   
#ifdef DEMOD_PROP_ATSC3_OUTPUT_TYPE
#define DEMOD_PROP_ATSC3_OUTPUT_TYPE_CODE				0x001024

typedef struct
{/*DD_ATSC3_OUTPUT_TYPE_struct */
	UINT8 type;
}  LX_DEMOD_DD_ATSC3_OUTPUT_TYPE_struct;

#define DEMOD_PROP_ATSC3_OUTPUT_TYPE_LSB				0
#define DEMOD_PROP_ATSC3_OUTPUT_TYPE_MASK				0x03
#define DEMOD_DD_ATSC3_OUTPUT_TYPE_DEF					0
#define DEMOD_DD_ATSC3_OUTPUT_TYPE_B					1
#define DEMOD_DD_ATSC3_OUTPUT_TYPE_C					2

#endif

/*-------------------------------------------------------------------------*/
/* DEMOD_PROP_AGC property definition */
#ifdef DEMOD_PROP_AGC
#define DEMOD_PROP_AGC_CODE								0x101F

typedef struct
{/*DEMOD_PROP_AGC_struct */
	UINT8	agc_src;
	UINT8	agc_pol;
	UINT8	agc_frzEn;
	UINT8	agc_outEn;
	UINT8	agc_outEn_S;
	UINT8	agc_bw;

}  LX_DEMOD_PROP_AGC_struct;

#define DEMOD_PROP_AGC_SRC_LSB							7
#define DEMOD_PROP_AGC_SRC_MASK							0x01
#define DEMOD_PROP_AGC_SRC_AVERAGE						0
#define DEMOD_PROP_AGC_SRC_INSTANT						1

#define DEMOD_PROP_AGC_POL_LSB							6
#define DEMOD_PROP_AGC_POL_MASK							0x01
#define DEMOD_PROP_AGC_POLARITY_INVERSION				0
#define DEMOD_PROP_AGC_POLARITY_NORMAL					1

#define DEMOD_PROP_AGC_OUTEN_LSB						5
#define DEMOD_PROP_AGC_OUTEN_MASK						0x01
#define DEMOD_PROP_AGC_OUTEN_ENABLE						0
#define DEMOD_PROP_AGC_OUTEN_DISABLE 					1

#define DEMOD_PROP_AGC_OUTEN_S_LSB						4
#define DEMOD_PROP_AGC_OUTEN_S_MASK						0x01
#define DEMOD_PROP_AGC_OUTEN_S_ENABLE					0
#define DEMOD_PROP_AGC_OUTEN_S_DISABLE					1

#define DEMOD_PROP_AGC_FRZEN_LSB						3
#define DEMOD_PROP_AGC_FRZEN_MASK						0x01
#define DEMOD_PROP_AGC_FRZ_ENABLE						1
#define DEMOD_PROP_AGC_FRZ_DISABLE						0

#define DEMOD_PROP_AGC_BW_LSB							0
#define DEMOD_PROP_AGC_BW_MASK							0x07
#define DEMOD_PROP_AGC_BW_DEFAULT						3

#endif /*DEMOD_DD_AGC*/

/*-------------------------------------------------------------------------*/
/* DEMOD_PROP_TPOUT_MODE property definition */
#ifdef DEMOD_PROP_TPOUT_MODE
#define DEMOD_PROP_TPOUT_MODE_CODE 						0x1003

typedef struct
{ /* SET_TS_MODE_PROP_struct */
	UINT8 tpSrMsb;
	UINT8 ssopi;
	UINT8 tpOutEn;
}  LX_DEMOD_PROP_TPOUT_MODE_struct;

#define DEMOD_PROP_TPOUT_MODE_TPOUTEN_LSB				0
#define DEMOD_PROP_TPOUT_MODE_TPOUTEN_MASK 				0x01
#define DEMOD_PROP_TPOUT_MODE_TPOUTEN_ENABLE			1
#define DEMOD_PROP_TPOUT_MODE_TPOUTEN_DISABLE			0
#define DEMOD_PROP_TPOUT_MODE_SSOPI_LSB         		4
#define DEMOD_PROP_TPOUT_MODE_SSOPI_MASK      			0x01
#define DEMOD_PROP_TPOUT_MODE_SSOPI_8BIT     			0
#define DEMOD_PROP_TPOUT_MODE_SSOPI_1BIT				1
#define DEMOD_PROP_TPOUT_MODE_SSOPI_DEFAULT				0

#define DEMOD_PROP_TPOUT_MODE_TPSRMSB_LSB				7
#define DEMOD_PROP_TPOUT_MODE_TPSRMSB_MASK 				0x01
#define DEMOD_PROP_TPOUT_MODE_TPSRMSB_ENABLE			1
#define DEMOD_PROP_TPOUT_MODE_TPSRMSB_DISABLE			0

#endif /*DEMOD_DD_TS_MODE */

/*-------------------------------------------------------------------------*/
/* DEMOD_PROP_CONSTEL property definition */
#ifdef DEMOD_PROP_CONSTEL
#define DEMOD_PROP_CONSTEL_CODE							0x1005

typedef struct { /* SET_DVBC_CONSTEL_PROP_struct */
	UINT8 constellation;
	UINT8 constel_autodet;
}  LX_DEMOD_PROP_CONSTEL_struct;

#define DEMOD_PROP_CONSTEL_CONSTELLATION_LSB			4
#define DEMOD_PROP_CONSTEL_CONSTELLATION_MASK			0x0f

#define DEMOD_PROP_CONSTEL_AUTO_DET_LSB					0
#define DEMOD_PROP_CONSTEL_AUTO_DET_MASK				0x1

#define DEMOD_PROP_CONSTEL_AUTO_DET_ENABLE				0
#define DEMOD_PROP_CONSTEL_AUTO_DET_DISABLE				1

#endif /* DEMOD_DD_CONSTEL*/

/*-------------------------------------------------------------------------*/
/* DEMOD_PROP_COUNTRY_GRP property definition */
#ifdef DEMOD_PROP_COUNTRY_GRP
#define DEMOD_PROP_COUNTRY_GRP_CODE						0x1011

typedef struct {
	UINT8 grp;
}  LX_DEMOD_PROP_COUNTRY_GRP_struct;

#define DEMOD_PROP_COUNTRY_GRP_LSB						0
#define DEMOD_PROP_COUNTRY_GRP_MASK						0x0f
#define DEMOD_PROP_COUNTRY_GRP_NONE						0x0
#define DEMOD_PROP_COUNTRY_GRP_EU						0x1
#define DEMOD_PROP_COUNTRY_GRP_END						0x2
#define DEMOD_PROP_COUNTRY_GRP_UNKNOWN					0xf

#endif

/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/***************ISDBT / DVBT/ DVBT2 / DVBS / DVBS2/DVBC/ DVBC2/  DEBUG*********/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/

/*-------------------------------------------------------------------------*/
/* LGDBB DD AUTO MODE property definition */  //JEONGPIL.YUN
#ifdef DEMOD_PROP_AUTO_MODE
#define DEMOD_PROP_AUTO_MODE_CODE						0x1001

typedef struct
{ /* LX_DEMOD_DD_TUNE_MODE_PROP_struct */
	UINT8	auto_detect;
} LX_DEMOD_PROP_AUTO_MODE_struct;

/* DD_TUNE_MODE property*/
#define DEMOD_PROP_AUTO_MODE_DETEN_LSB					0
#define DEMOD_PROP_AUTO_MODE_DETEN_MASK					0x0f
#define DEMOD_PROP_AUTO_MODE_DET_DVBT_DVBT2_ENABLE		1
#define DEMOD_PROP_AUTO_MODE_DET_DVBT_ONLY_ENABLE		2
#define DEMOD_PROP_AUTO_MODE_DET_DVBT2_ONLY_ENABLE		3
#define DEMOD_PROP_AUTO_MODE_DET_DVBC_DVBC2_ENABLE		4
#define DEMOD_PROP_AUTO_MODE_DET_DVBC_ONLY_ENABLE		5
#define DEMOD_PROP_AUTO_MODE_DET_DVBC2_ONLY_ENABLE		6
#define DEMOD_PROP_AUTO_MODE_DET_DVBS_DVBS2_ENABLE		7
#define DEMOD_PROP_AUTO_MODE_DET_DVBS_ONLY_ENABLE		8
#define DEMOD_PROP_AUTO_MODE_DET_DVBS2_ONLY_ENABLE		9
#define DEMOD_PROP_AUTO_MODE_DET_VSB_ATSC3_ENABLE		10
#define DEMOD_PROP_AUTO_MODE_DET_VSB_ONLY_ENABLE		11
#define DEMOD_PROP_AUTO_MODE_DET_ATSC3_ONLY_ENABLE		12

#endif /* DEMOD_PROP_AUTO_MODE */

/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/***************ISDBT / DVBT/ DVBT2 / DVBS / DVBS2/DVBC/ DVBC2/  DEBUG*********/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/

/*-------------------------------------------------------------------------*/
/* DEMOD_PROP_DVBT_HIERARCHY property definition */
#ifdef DEMOD_PROP_DVBT_HIERARCHY
#define DEMOD_PROP_DVBT_HIERARCHY_CODE					0x1004

typedef struct { /* SET_DVBT_HIERARCHY_PROP_struct */
	UINT8 hierhpsel;
}  LX_DEMOD_PROP_DVBT_HIERARCHY_struct;

#define DEMOD_PROP_DVBT_HIERARCHY_HIERHPSEL_D_LSB		0
#define DEMOD_PROP_DVBT_HIERARCHY_HIERHPSEL_D_MASK		0x01
#define DEMOD_PROP_DVBT_HIERARCHY_HIERHPSEL_HIGH		1
#define DEMOD_PROP_DVBT_HIERARCHY_HIERHPSEL_LOW			0

#endif /* DEMOD_DD_DVBT_HIERARCHY*/


/*-------------------------------------------------------------------------*/
/* DEMOD_PROP_DVBT2_MODE property definition */
#ifdef DEMOD_PROP_DVBT2_MODE
#define DEMOD_PROP_DVBT2_MODE_CODE 						0x1006

typedef struct { /* LX_DEMOD_PROP_DVBT2_MODE_struct */
    UINT8   lock_mode;
} LX_DEMOD_PROP_DVBT2_MODE_struct;

/* DVBT2_MODE property, LOCK_MODE field definition (NO TITLE)*/
#define DEMOD_PROP_DVBT2_MODE_LOCK_MODE_LSB				0
#define DEMOD_PROP_DVBT2_MODE_LOCK_MODE_MASK			0x01
#define DEMOD_PROP_DVBT2_MODE_LOCK_MODE_DEFAULT			0
//#define DEMOD_PROP_DVBT2_MODE_LOCK_MODE_ANY			0
#define DEMOD_PROP_DVBT2_MODE_LOCK_MODE_BASE_ONLY		0
#define DEMOD_PROP_DVBT2_MODE_LOCK_MODE_LITE_ONLY		1

#endif /* DEMOD_PROP_DVBT2_MODE */

/*-------------------------------------------------------------------------*/
/* DVBS_AFC_RANGE property definition */
#ifdef DEMOD_PROP_AFC_RANGE
#define DEMOD_PROP_AFC_RANGE_CODE						0x1007

typedef struct { /* DEMOD_PROP_AFC_RANGE_struct */
	UINT32	range_khz;
} LX_DEMOD_PROP_AFC_RANGE_struct;

/* DVBS_AFC_RANGE property, RANGE_KHZ field definition (NO TITLE)*/
#define DEMOD_PROP_AFC_RANGE_RANGE_KHZ_LSB				0
#define DEMOD_PROP_AFC_RANGE_RANGE_KHZ_MASK 			0xffff
#define DEMOD_PROP_AFC_RANGE_RANGE_KHZ_DEFAULT			4000
#endif /* DEMOD_PROP_AFC_RANGE */


/*-------------------------------------------------------------------------*/
/* DVBS2_AFC_RANGE property definition */
#ifdef DEMOD_PROP_DVBS2_AFC_RANGE
#define DEMOD_PROP_DVBS2_AFC_RANGE_CODE					0x1008

typedef struct { /* LX_DEMOD_PROP_AFC_RANGE_struct */
	UINT32	range_khz;
} LX_DEMOD_PROP_DVBS2_AFC_RANGE_struct;

/* DVBS_AFC_RANGE property, RANGE_KHZ field definition (NO TITLE)*/
#define DEMOD_PROP_DVBS2_AFC_RANGE_RANGE_KHZ_LSB		0
#define DEMOD_PROP_DVBS2_AFC_RANGE_RANGE_KHZ_MASK		0xffff
#define DEMOD_PROP_DVBS2_AFC_RANGE_RANGE_KHZ_DEFAULT	4000
#endif /* LX_DEMOD_PROP_DVBS2_AFC_RANGE */

/*--------------------------------------------------------------------------*/
/* DVBS2_AFC_RANGE property definition */
#ifdef DEMOD_PROP_DVBS_OPMSEL
#define DEMOD_PROP_DVBS_OPMSEL_CODE						0x1009

typedef struct
{/*SET_DVBS_BLIND_SCAN_PROP_struct */
	UINT8 opmSel;
} LX_DEMOD_PROP_DVBS_OPMSEL_struct;

#define DEMOD_DD_DVBS_OPM_SEL_PROP_LSB					0
#define DEMOD_DD_DVBS_OPM_SEL_PROP_MASK					0xff
#define DEMOD_DD_DVBS_OPM_SEL_PROP_BLIND_SCAN_MODE		0x30
#define DEMOD_DD_DVBS_OPM_SEL_PROP_BLIND_LOCK_MODE		0x20
#define DEMOD_DD_DVBS_OPM_SEL_PROP_NORMAL_MODE			0x10

#endif /*DEMOD_DD_DVBS_OPMSEL*/

/*-------------------------------------------------------------------------*/
/* LGDBB DEMOD_PROP_DISEQC_CONFIG property definition */
#ifdef DEMOD_PROP_DISEQC_CONFIG
#define DEMOD_PROP_DISEQC_CONFIG_CODE					0x100F

typedef struct
{ /* LX_DEMOD_DD_DISEQC_PARAM_PROP_struct */
	UINT8 message_sel;   //envelope or 22khz
	UINT8 diseqc_2_x_enable;
	UINT8 message_repeat_en;
} LX_DEMOD_PROP_DISEQC_CONFIG_struct;

   /* DD_DISEQC_PARAM property, SEQUENCE_MODE field definition (NO TITLE)*/
#define DEMOD_PROP_DISEQC_CONFIG_MESSAGE_SEL_LSB		0
#define DEMOD_PROP_DISEQC_CONFIG_MESSAGE_SEL_MASK		0x01

#define DEMOD_PROP_DISEQC_CONFIG_EN_2_X_LSB				1
#define DEMOD_PROP_DISEQC_CONFIG_EN_2_X_MASK			0x01

#define DEMOD_PROP_DISEQC_CONFIG_MESSAGE_REPEAT_LSB 	2
#define DEMOD_PROP_DISEQC_CONFIG_MESSAGE_REPEAT_MASK	0x01

#define	DEMOD_PROP_DISEQC_CONFIG_MESSAGE_SEL_ENVELOPE	0
#define DEMOD_PROP_DISEQC_CONFIG_MESSAGE_SEL_TONE_22KHZ	1
#define DEMOD_PROP_DISEQC_CONFIG_MESSAGE_SEL_DEFAULT 	0

#define DEMOD_PROP_DISEQC_CONFIG_EN_2_X_ENABLE			1
#define DEMOD_PROP_DISEQC_CONFIG_EN_2_X_DISABLE			0
#define DEMOD_PROP_DISEQC_CONFIG_EN_2_X_DEFAULT			0

#define DEMOD_PROP_DISEQC_CONFIG_MESSAGE_REPEAT_ENABLE	1
#define DEMOD_PROP_DISEQC_CONFIG_MESSAGE_REPEAT_DISABLE	0
#define DEMOD_PROP_DISEQC_CONFIG_MESSAGE_REPEAT_DEFAULT	0

#endif /* DEMOD_DD_DISEQC_PARAM_PROP */

/* --------------------------------------------*/
/* PROPERTIES STRUCT			       */
/* This stores all property fields	       */
/* --------------------------------------------*/
typedef struct {
#ifdef DEMOD_PROP_BER_RESOL
	LX_DEMOD_PROP_BER_RESOL_struct			dd_ber_resol;
#endif /* DEMOD_PROP_BER_RESOL */

#ifdef DEMOD_PROP_IF_FREQ
	LX_DEMOD_PROP_IF_FREQ_struct			dd_if_freq;
#endif /* DEMOD_DD_IF_INPUT_FREQ_PROP */

#ifdef DEMOD_PROP_CLOCK_MODE
	LX_DEMOD_PROP_CLOCK_MODE_struct			dd_clk_mode;
#endif /* DEMOD_PROP_CLOCK_MODE */

#ifdef DEMOD_PROP_MODE
	LX_DEMOD_PROP_MODE_struct				dd_mode;
#endif /*DEMOD_DD_MODE */

#ifdef DEMOD_PROP_TS_MODE
	LX_DEMOD_PROP_TS_MODE_struct 			dd_ts_mode;
#endif /* DEMOD_PROP_TS_MODE */

#ifdef DEMOD_PROP_ADC
	LX_DEMOD_PROP_ADC_CODE_struct			dd_adc_sel;
#endif /* DEMOD_PROP_ADC */

#ifdef DEMOD_PROP_CLKPHASE
	LX_DEMOD_PROP_CLKPHASE_CODE_struct		dd_clkphase_sel;
#endif/* DEMOD_PROP_CLKPHASE */
				 
#ifdef DEMOD_PROP_SDRAM
	LX_DEMOD_PROP_SDRAM_CODE_struct			dd_sdram_mode;
#endif/* DEMOD_PROP_SDRAM */

#ifdef DEMOD_PROP_TWOCTI
	 LX_DEMOD_PROP_TWOCTI_CODE_struct		dd_twocti_mode;
#endif/* DEMOD_PROP_TWOCTI */

#ifdef DEMOD_PROP_SDRAM_PWR
	 LX_DEMOD_PROP_SDRAM_PWR_CODE_struct	dd_sdram_pwr;
#endif/* DEMOD_PROP_SDRAM_PWR */

#ifdef DEMOD_PROP_ATSC3_OUTPUT_TYPE
	 LX_DEMOD_DD_ATSC3_OUTPUT_TYPE_struct	dd_atsc3_output_type;
#endif/* DEMOD_PROP_ATSC3_OUTPUT_TYPE */

#ifdef DEMOD_PROP_AGC
	LX_DEMOD_PROP_AGC_struct				dd_agc;
#endif /* DEMOD_PROP_AGC */

#ifdef DEMOD_PROP_TPOUT_MODE
	LX_DEMOD_PROP_TPOUT_MODE_struct			dd_tpout_mode;
#endif /* DEMOD_PROP_TPOUT_MODE */

#ifdef DEMOD_PROP_CONSTEL
	LX_DEMOD_PROP_CONSTEL_struct			dd_constel;
#endif /* DEMOD_PROP_CONSTEL */

#ifdef DEMOD_PROP_AUTO_MODE
	LX_DEMOD_PROP_AUTO_MODE_struct			dd_auto_mode;
#endif /* DEMOD_PROP_AUTO_MODE */

#ifdef DEMOD_PROP_COUNTRY_GRP
	LX_DEMOD_PROP_COUNTRY_GRP_struct		dd_country_grp;
#endif /* DEMOD_PROP_COUNTRY_GRP */


/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/***************ISDBT / DVBT/ DVBT2 / DVBS / DVBS2/DVBC/ DVBC2/  DEBUG*********/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/

#ifdef DEMOD_PROP_DISEQC_CONFIG
	LX_DEMOD_PROP_DISEQC_CONFIG_struct		dd_diseqc_config;
#endif /* DEMOD_PROP_DISEQC_CONFIG */

#ifdef DEMOD_PROP_DVBT_HIERARCHY
	LX_DEMOD_PROP_DVBT_HIERARCHY_struct 	dd_dvbt_hp_sel;
#endif /* DEMOD_PROP_DVBT_HIERARCHY */

#ifdef DEMOD_PROP_DVBT2_MODE
	LX_DEMOD_PROP_DVBT2_MODE_struct			dd_dvbt2_lock_mode;
#endif

#ifdef DEMOD_PROP_AFC_RANGE
	LX_DEMOD_PROP_AFC_RANGE_struct			dd_dvbs_afc_range;
#endif

#ifdef DEMOD_PROP_DVBS2_AFC_RANGE
	LX_DEMOD_PROP_DVBS2_AFC_RANGE_struct	dd_dvbs2_afc_range;
#endif

#ifdef DEMOD_PROP_DVBS_OPMSEL
	LX_DEMOD_PROP_DVBS_OPMSEL_struct		dd_dvbs_opm_sel;
#endif /* DEMOD_PROP_DVBS_OPMSEL */

} LX_DEMOD_L1_PropObj;

//#define DEMOD_GET_PROPERTY_STRING
#endif /* _DBB_DEMOD_L1_PROPERTIES_H_ */








