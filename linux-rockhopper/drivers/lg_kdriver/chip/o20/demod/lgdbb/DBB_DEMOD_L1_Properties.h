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

#ifndef   _DBB_DEMOD_L1_PROPERTIES_H_
#define   _DBB_DEMOD_L1_PROPERTIES_H_

/*-------------------------------------------------------------------------*/
#define DEMOD_DD_MODE_PROP							0x100A

#ifdef	  DEMOD_DD_MODE_PROP
#define DEMOD_DD_MODE_PROP_CODE						0x00100A

typedef struct
{ /* SET_MODE_PROP_struct */
	UINT8 tuneMode;
	UINT8 specinvauto;
	UINT8 specinv;
	UINT8 modulation;
	UINT8 bw;
} LX_DEMOD_DD_MODE_PROP_struct;


#define  DEMOD_DD_MODE_PROP_TUNEMODE_LSB			0
#define  DEMOD_DD_MODE_PROP_TUNEMODE_MASK			0x03

#define  DEMOD_DD_MODE_PROP_TUNEMODE_DEFAULT		0
#define  DEMOD_DD_MODE_PROP_TUNEMODE_NORMAL			0
#define  DEMOD_DD_MODE_PROP_TUNEMODE_AUTO			1
#define  DEMOD_DD_MODE_PROP_TUNEMODE_MANUAL			2
#define  DEMOD_DD_MODE_PROP_TUNEMODE_FIXED_DATA 	3
#define  DEMOD_DD_MODE_PROP_TUNEMODE_BLIND		 	4

#define  DEMOD_DD_MODE_PROP_SPECINVAUTO_LSB			2
#define  DEMOD_DD_MODE_PROP_SPECINVAUTO_MASK		0x01

#define  DEMOD_DD_MODE_PROP_SPECINV_AUTO			0
#define  DEMOD_DD_MODE_PROP_SPECINV_MANUAL			1

#define  DEMOD_DD_MODE_PROP_SPECINV_LSB				3
#define  DEMOD_DD_MODE_PROP_SPECINV_MASK			0x01

#define  DEMOD_DD_MODE_PROP_SPECINV_INVERSION		1
#define  DEMOD_DD_MODE_PROP_SPECINV_NORMAL			0

#define  DEMOD_DD_MODE_PROP_BW_LSB					4
#define  DEMOD_DD_MODE_PROP_BW_MASK					0x0f

#define  DEMOD_DD_MODE_PROP_BW_DEFAULT				8
#define  DEMOD_DD_MODE_PROP_BW_BW_4MHZ				4
#define  DEMOD_DD_MODE_PROP_BW_BW_5MHZ				5
#define  DEMOD_DD_MODE_PROP_BW_BW_6MHZ				6
#define  DEMOD_DD_MODE_PROP_BW_BW_7MHZ				7
#define  DEMOD_DD_MODE_PROP_BW_BW_8MHZ				8
#define  DEMOD_DD_MODE_PROP_BW_BW_1D7MHZ			2
#define  DEMOD_DD_MODE_PROP_BW_BW_36MHZ				36
#define  DEMOD_DD_MODE_PROP_BW_BW_40MHZ				40

#define  DEMOD_DD_MODE_PROP_MODULATION_LSB			8
#define  DEMOD_DD_MODE_PROP_MODULATION_MASK			0xff

#define  DEMOD_DD_MODE_PROP_MODULATION_DEFAULT		0x20
#define  DEMOD_DD_MODE_PROP_MODULATION_VSB			0x08
#define  DEMOD_DD_MODE_PROP_MODULATION_QAM			0x48
#define  DEMOD_DD_MODE_PROP_MODULATION_ATSC3		0x09
#define  DEMOD_DD_MODE_PROP_MODULATION_ISDBT		0x10
#define  DEMOD_DD_MODE_PROP_MODULATION_ISDBC		0x11
#define  DEMOD_DD_MODE_PROP_MODULATION_DVBT			0x20
#define  DEMOD_DD_MODE_PROP_MODULATION_DVBT2		0x21
#define  DEMOD_DD_MODE_PROP_MODULATION_DVBC			0x40
#define  DEMOD_DD_MODE_PROP_MODULATION_DVBC2		0x41
#define  DEMOD_DD_MODE_PROP_MODULATION_DVBS			0x60
#define  DEMOD_DD_MODE_PROP_MODULATION_DVBS2		0x61
#define  DEMOD_DD_MODE_PROP_MODULATION_DVBS2X		0x62
#define  DEMOD_DD_MODE_PROP_MODULATION_DTMB			0x18
#define  DEMOD_DD_MODE_PROP_MODULATION_AUTO_DETECT	15
#define  DEMOD_DD_MODE_PROP_MODULATION_ANALOG		100
#define  DEMOD_DD_MODE_PROP_MODULATION_SLEEP		200	//lgit
#define  DEMOD_DD_MODE_PROP_MODULATION_UNKNOWN		250	//lgit

#endif /*DEMOD_DD_MODE */



/*-------------------------------------------------------------------------*/
/* DEMOD_DD_IF_FREQ_PROP property definition */

#define DEMOD_DD_IF_FREQ_PROP						0x100B
#ifdef	  DEMOD_DD_IF_FREQ_PROP
#define DEMOD_DD_IF_FREQ_PROP_CODE					0x00100B

typedef struct
{ /* SET_IF_FREQ_PROP_struct */
	UINT32 if_freq;
} LX_DEMOD_DD_IF_FREQ_PROP_struct;

#define  DEMOD_DD_IF_FREQ_PROP_IF_FREQ_LSB			0
#define  DEMOD_DD_IF_FREQ_PROP_IF_FREQ_MASK			0xffff
#define  DEMOD_DD_IF_FREQ_PROP_IF_FREQ_DEFAULT		6000
#define  DEMOD_DD_IF_FREQ_PROP_IF_FREQ_0MHZ			0
#define  DEMOD_DD_IF_FREQ_PROP_IF_FREQ_4_5MHZ		4500
#define  DEMOD_DD_IF_FREQ_PROP_IF_FREQ_5MHZ			5000
#define  DEMOD_DD_IF_FREQ_PROP_IF_FREQ_6MHZ			6000

#endif /*DEMOD_DD_IF_FREQ */



/*-------------------------------------------------------------------------*/
/* depreacated DEMOD_DD_CLOCK_MODE_PROP
 * clk_mode have to set before demod initialize.
 */
#define DEMOD_DD_CLOCK_MODE_PROP					0x100D

#ifdef	  DEMOD_DD_CLOCK_MODE_PROP
  #define DEMOD_DD_CLOCK_MODE_PROP_CODE 			0x00100D

typedef struct
{ /* SET_CLOCK_MODE_PROP_struct */
	UINT32 clk_mode;
}  LX_DEMOD_DD_CLOCK_MODE_PROP_struct;

#define  DEMOD_DD_CLOCK_MODE_PROP_LSB				0
#define  DEMOD_DD_CLOCK_MODE_PROP_MASK				0xffffffff
#define  DEMOD_DD_CLOCK_MODE_PROP_DEFAULT			0x5DC0
#define  DEMOD_DD_CLOCK_MODE_PROP_15P2MHZ			0x3B60
#define  DEMOD_DD_CLOCK_MODE_PROP_20MHZ 			0x4E20
#define  DEMOD_DD_CLOCK_MODE_PROP_21P6MHZ			0x5460
#define  DEMOD_DD_CLOCK_MODE_PROP_22MHZ				0x55F0
#define  DEMOD_DD_CLOCK_MODE_PROP_23MHZ				0x59D8
#define  DEMOD_DD_CLOCK_MODE_PROP_24MHZ				0x5DC0
#define  DEMOD_DD_CLOCK_MODE_PROP_25MHZ				0x61A8
#define  DEMOD_DD_CLOCK_MODE_PROP_26MHZ				0x6590
#define  DEMOD_DD_CLOCK_MODE_PROP_27MHZ				0x6978
#define  DEMOD_DD_CLOCK_MODE_PROP_28MHZ				0x6D60
#define  DEMOD_DD_CLOCK_MODE_PROP_29MHZ				0x7148
#define  DEMOD_DD_CLOCK_MODE_PROP_30MHZ				0x7530
#define  DEMOD_DD_CLOCK_MODE_PROP_40MHZ				0x9C40
#define  DEMOD_DD_CLOCK_MODE_PROP_48MHZ				0xBB80
#define  DEMOD_DD_CLOCK_MODE_PROP_50MHZ				0xC350
#define  DEMOD_DD_CLOCK_MODE_PROP_60P8MHZ			0xED80
#define  DEMOD_DD_CLOCK_MODE_PROP_96MHZ				0x17700
#define  DEMOD_DD_CLOCK_MODE_PROP_124MHZ			0x1E460
#define  DEMOD_DD_CLOCK_MODE_PROP_86P4MHZ			0x15180


#endif /*DEMOD_DD_CLOCK_MODE */


/*-------------------------------------------------------------------------*/
/* LGDBB DD_BER_RESOL property definition */
#define   DEMOD_DD_BER_RESOL_PROP					0x100E	 //jeongpil.yun not implemented 15/9/1

#ifdef	  DEMOD_DD_BER_RESOL_PROP
  #define DEMOD_DD_BER_RESOL_PROP_CODE				0x00100E


typedef struct
{ /* LX_DEMOD_DD_BER_RESOL_PROP_struct */
	 UINT8	 exp;
} LX_DEMOD_DD_BER_RESOL_PROP_struct;

 /* DD_BER_RESOL property, EXP field definition (NO TITLE)*/
#define  DEMOD_DD_BER_RESOL_PROP_EXP_LSB			0
#define  DEMOD_DD_BER_RESOL_PROP_EXP_MASK			0x0f

#define  DEMOD_DD_BER_RESOL_PROP_EXP_DEFAULT		5
#define DEMOD_DD_BER_RESOL_PROP_EXP_EXPLO_5			5
#define DEMOD_DD_BER_RESOL_PROP_EXP_EXPLO_7			7
#endif /* DEMOD_DD_BER_RESOL_PROP */





/*-------------------------------------------------------------------------*/
/* LGDBB DD_TS_MODE property definition */   //JEONGPIL.YUN

#define DEMOD_DD_TS_MODE_PROP						0x1002
#ifdef	  DEMOD_DD_TS_MODE_PROP
#define DEMOD_DD_TS_MODE_PROP_CODE					0x1002

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
}  LX_DEMOD_DD_TS_MODE_PROP_struct;

#define   DEMOD_DD_TS_MODE_PROP_TPMODE_LSB				7
#define   DEMOD_DD_TS_MODE_PROP_TPMODE_MASK				0x01

#define   DEMOD_DD_TS_MODE_PROP_TPMODE_PARALLEL 		1
#define   DEMOD_DD_TS_MODE_PROP_TPMODE_SERIAL			0
#define   DEMOD_DD_TS_MODE_PROP_TPMODE_DEFAULT			1

#define   DEMOD_DD_TS_MODE_PROP_TPCLKPOL_LSB			6
#define   DEMOD_DD_TS_MODE_PROP_TPCLKPOL_MASK			0x01

#define   DEMOD_DD_TS_MODE_PROP_TPCLKPOL_POS_EDGE		1
#define   DEMOD_DD_TS_MODE_PROP_TPCLKPOL_NEG_EDGE		0
#define   DEMOD_DD_TS_MODE_PROP_TPCLKPOL_DEFAULT		0

#define   DEMOD_DD_TS_MODE_PROP_TPSOPPOL_LSB			5
#define   DEMOD_DD_TS_MODE_PROP_TPSOPPOL_MASK			0x01

#define   DEMOD_DD_TS_MODE_PROP_TPSOPPOL_HIGH			1
#define   DEMOD_DD_TS_MODE_PROP_TPSOPPOL_LOW			0
#define   DEMOD_DD_TS_MODE_PROP_TPSOPPOL_DEFAULT		1

#define   DEMOD_DD_TS_MODE_PROP_TPVALPOL_LSB			4
#define   DEMOD_DD_TS_MODE_PROP_TPVALPOL_MASK			0x01

#define   DEMOD_DD_TS_MODE_PROP_TPVALPOL_HIGH			1
#define   DEMOD_DD_TS_MODE_PROP_TPVALPOL_LOW			0
#define   DEMOD_DD_TS_MODE_PROP_TPVALPOL_DEFAULT		1

#define   DEMOD_DD_TS_MODE_PROP_TPERRPOL_LSB			3
#define   DEMOD_DD_TS_MODE_PROP_TPERRPOL_MASK			0x01

#define   DEMOD_DD_TS_MODE_PROP_TPERRPOL_HIGH			1
#define   DEMOD_DD_TS_MODE_PROP_TPERRPOL_LOW			0
#define   DEMOD_DD_TS_MODE_PROP_TPERRPOL_DEFAULT		1

#define   DEMOD_DD_TS_MODE_PROP_TPCLKSUP_LSB			2
#define   DEMOD_DD_TS_MODE_PROP_TPCLKSUP_MASK			0x01

#define   DEMOD_DD_TS_MODE_PROP_TPCLKSUP_ENABLE			1
#define   DEMOD_DD_TS_MODE_PROP_TPCLKSUP_DIABLE			0
#define   DEMOD_DD_TS_MODE_PROP_TPCLKSUP_DEFAULT		0

#define   DEMOD_DD_TS_MODE_PROP_TPMSBFST_LSB			1
#define   DEMOD_DD_TS_MODE_PROP_TPMSBFST_MASK			0x01

#define   DEMOD_DD_TS_MODE_PROP_TPMSBFST_ENABLE			1
#define   DEMOD_DD_TS_MODE_PROP_TPMSBFST_DISABLE		0
#define   DEMOD_DD_TS_MODE_PROP_TPMSBFST_DEFAULT		1

#define   DEMOD_DD_TS_MODE_PROP_TPBIGEND_LSB			0
#define   DEMOD_DD_TS_MODE_PROP_TPBIGEND_MASK			0x01

#define   DEMOD_DD_TS_MODE_PROP_TPBIGEND_ENABLE			1
#define   DEMOD_DD_TS_MODE_PROP_TPBIGEND_DISABLE		0
#define   DEMOD_DD_TS_MODE_PROP_TPBIGEND_DEFAULT		1



#endif /*SET_TS_MODE */


/*-------------------------------------------------------------------------*/
/* LGDBB DD_ADC  property definition */   //JEONGPIL.YUN

#define DEMOD_DD_ADC_PROP								0x100C	 //JEONGPIL.YUN
#ifdef DEMOD_DD_ADC_PROP
#define DEMOD_DD_ADC_PROP_CODE							0x100C	 //check number !!

typedef struct
{/*SET_ADC_PROP_CODE_struct */
	UINT8 adcClkPllSel;
	UINT32 adcClk;
}  LX_DEMOD_DD_ADC_PROP_CODE_struct;


#define DEMOD_DD_ADC_PROP_ADCCLKPLLSEL_LSB				28
#define DEMOD_DD_ADC_PROP_ADCCLKPLLSEL_MASK				0x0F

#define DEMOD_DD_ADC_PROP_ADCCLKPLLSEL_EXT_XTAL			0
#define DEMOD_DD_ADC_PROP_ADCCLKPLLSEL_SOC_PLL			1
#define DEMOD_DD_ADC_PROP_ADCCLKPLLSEL_TUNER_PLL		2
#define DEMOD_DD_ADC_PROP_ADCCLKPLLSEL_DEFAULT			1

#define DEMOD_DD_ADC_PROP_ADCCLK_LSB					0
#define DEMOD_DD_ADC_PROP_ADCCLK_MASK					0x0FFFFFFF
#define DEMOD_DD_ADC_PROP_ADCCLK_20MHZ					0x4E20
#define DEMOD_DD_ADC_PROP_ADCCLK_24MHZ					0x5DC0
#define DEMOD_DD_ADC_PROP_ADCCLK_25MHZ					0x61A8
#define DEMOD_DD_ADC_PROP_ADCCLK_60P8MHZ				0xED80
#define DEMOD_DD_ADC_PROP_ADCCLK_80MHZ					0x13880
#define DEMOD_DD_ADC_PROP_ADCCLK_96MHZ					0x17700
#define DEMOD_DD_ADC_PROP_ADCCLK_124MHZ					0x1E460
#define DEMOD_DD_ADC_PROP_ADCCLK_DEFAULT				0x5DC0

#endif /*SET_ADC_PROP*/

/*-------------------------------------------------------------------------*/
/* LGDBB DD_CLK PHASE  property definition */   
#define DEMOD_DD_CLKPHASE_PROP							0x1010
#ifdef DEMOD_DD_CLKPHASE_PROP
#define DEMOD_DD_CLKPHASE_PROP_CODE						0x001010


typedef struct
{/*SET_CLKPHASE_PROP_CODE_struct */
	UINT8 adSamsel;
	UINT8 adcOutClksel;
}  LX_DEMOD_DD_CLKPHASE_PROP_CODE_struct;

#define DEMOD_DD_CLKPHASE_PROP_LSB						0
#define DEMOD_DD_CLKPHASE_PROP_MASK						0xff

#define DEMOD_DD_CLKPHASE_PROP_ADSAMSEL_LSB        		7
#define DEMOD_DD_CLKPHASE_PROP_ADSAMSEL_MASK      		0x01

#define DEMOD_DD_CLKPHASE_PROP_ADSAMSEL_NORMAL			0
#define DEMOD_DD_CLKPHASE_PROP_ADSAMSEL_INV				1

#define DEMOD_DD_CLKPHASE_PROP_ADCOUTCLK_LSB         	0
#define DEMOD_DD_CLKPHASE_PROP_ADCOUTCLK_MASK			0x01

#define DEMOD_DD_CLKPHASE_PROP_ADCOUTCLK_NORMAL			0
#define DEMOD_DD_CLKPHASE_PROP_ADCOUTCLK_INV			1

#endif
/*-------------------------------------------------------------------------*/
/* LGDBB DD_SDRAM  property definition */   
#define DEMOD_DD_SDRAM_PROP								0x1021
#ifdef DEMOD_DD_SDRAM_PROP
#define DEMOD_DD_SDRAM_PROP_CODE						0x001021


typedef struct
{/*SET_SDRAM_PROP_CODE_struct */
	UINT8 sdRamOn;
}  LX_DEMOD_DD_SDRAM_PROP_CODE_struct;

#define DEMOD_DD_SDRAM_PROP_LSB							0
#define DEMOD_DD_SDRAM_PROP_MASK						0x03
#define DEMOD_DD_SDRAM_PROP_SDRAM_ON					1
#define DEMOD_DD_SDRAM_PROP_SDRAM_OFF					0
#define DEMOD_DD_SDRAM_PROP_SDRAM_UNKNOWN				2

#endif
/*-------------------------------------------------------------------------*/
/* LGDBB DD_TWOCTI  property definition */   
#define DEMOD_DD_TWOCTI_PROP							0x1022
#ifdef DEMOD_DD_TWOCTI_PROP
#define DEMOD_DD_TWOCTI_PROP_CODE						0x001022


typedef struct
{/*SET_TWOCTI_PROP_CODE_struct */
	UINT8 twoCtiOn;
}  LX_DEMOD_DD_TWOCTI_PROP_CODE_struct;

#define DEMOD_DD_TWOCTI_PROP_LSB						0
#define DEMOD_DD_TWOCTI_PROP_MASK						0x03
#define DEMOD_DD_TWOCTI_PROP_TWOCTI_ON					1
#define DEMOD_DD_TWOCTI_PROP_TWOCTI_OFF					0
#define DEMOD_DD_TWOCTI_PROP_TWOCTI_UNKNOWN				2

#endif

/*-------------------------------------------------------------------------*/
/* LGDBB DD_SDRAM_POWER property definition */   
#define DEMOD_DD_SDRAM_PWR_PROP							0x1023
#ifdef DEMOD_DD_SDRAM_PWR_PROP
#define DEMOD_DD_SDRAM_PWR_PROP_CODE					0x001023


typedef struct
{/*SET_SDRAM_PWR_PROP_CODE_struct */
	UINT8 sdRamPwrOn;
}  LX_DEMOD_DD_SDRAM_PWR_PROP_CODE_struct;

#define DEMOD_DD_SDRAM_PWR_PROP_LSB						0
#define DEMOD_DD_SDRAM_PWR_PROP_MASK					0x03
#define DEMOD_DD_SDRAM_PWR_PROP_PWR_ON					1
#define DEMOD_DD_SDRAM_PWR_PROP_PWR_OFF					0
#define DEMOD_DD_SDRAM_PWR_PROP_PWR_UNKNOWN				2

#endif



/*-------------------------------------------------------------------------*/
#define DEMOD_DD_AGC_PROP							0x101F
#ifdef DEMOD_DD_AGC_PROP
#define DEMOD_DD_AGC_PROP_CODE						0x101F

typedef struct
{/*DEMOD_DD_AGC_PROP_struct */
	UINT8	agc_src;
	UINT8	agc_pol;
	UINT8	agc_frzEn;
	UINT8	agc_outEn;
	UINT8	agc_outEn_S;
	UINT8	agc_bw;

}  LX_DEMOD_DD_AGC_PROP_struct;

#define DEMOD_DD_AGC_PROP_SRC_LSB					7
#define DEMOD_DD_AGC_PROP_SRC_AVERAGE				0
#define DEMOD_DD_AGC_PROP_SRC_INSTANT				1
#define DEMOD_DD_AGC_PROP_SRC_MASK					0x01

#define DEMOD_DD_AGC_PROP_POL_LSB					6
#define DEMOD_DD_AGC_PROP_POLARITY_INVERSION		0
#define DEMOD_DD_AGC_PROP_POLARITY_NORMAL			1
#define DEMOD_DD_AGC_PROP_POL_MASK					0x01

#define DEMOD_DD_AGC_PROP_OUTEN_LSB					5
#define DEMOD_DD_AGC_PROP_OUTEN_ENABLE				0
#define DEMOD_DD_AGC_PROP_OUTEN_DISABLE 			1
#define DEMOD_DD_AGC_PROP_OUTEN_MASK				0x01

#define DEMOD_DD_AGC_PROP_OUTEN_S_LSB				4
#define DEMOD_DD_AGC_PROP_OUTEN_S_ENABLE			0
#define DEMOD_DD_AGC_PROP_OUTEN_S_DISABLE			1
#define DEMOD_DD_AGC_PROP_OUTEN_S_MASK				0x01

#define DEMOD_DD_AGC_PROP_FRZEN_LSB					3
#define DEMOD_DD_AGC_PROP_FRZ_ENABLE				1
#define DEMOD_DD_AGC_PROP_FRZ_DISABLE				0
#define DEMOD_DD_AGC_PROP_FRZEN_MASK				0x01

#define DEMOD_DD_AGC_PROP_BW_LSB					0
#define DEMOD_DD_AGC_PROP_BW_DEFAULT				3
#define DEMOD_DD_AGC_PROP_BW_MASK					0x07

#endif /*DEMOD_DD_AGC*/



/*-------------------------------------------------------------------------*/
#define DEMOD_DD_TPOUT_MODE_PROP				0x1003
#ifdef	  DEMOD_DD_TPOUT_MODE_PROP
  #define DEMOD_DD_TPOUT_MODE_PROP_CODE 			0x1003

typedef struct
{ /* SET_TS_MODE_PROP_struct */
	UINT8 tpSrMsb;
	UINT8 ssopi;
	UINT8 tpOutEn;
}  LX_DEMOD_DD_TPOUT_MODE_PROP_struct;

#define   DEMOD_DD_TPOUT_MODE_PROP_TPOUTEN_LSB			0
#define   DEMOD_DD_TPOUT_MODE_PROP_TPOUTEN_MASK 		0x01
#define   DEMOD_DD_TPOUT_MODE_PROP_TPOUTEN_ENABLE		1
#define   DEMOD_DD_TPOUT_MODE_PROP_TPOUTEN_DISABLE		0
#define   DEMOD_DD_TPOUT_MODE_PROP_SSOPI_LSB         		4	
#define   DEMOD_DD_TPOUT_MODE_PROP_SSOPI_MASK      			0x01
#define   DEMOD_DD_TPOUT_MODE_PROP_SSOPI_8BIT     			0
#define   DEMOD_DD_TPOUT_MODE_PROP_SSOPI_1BIT				1
#define   DEMOD_DD_TPOUT_MODE_PROP_SSOPI_DEFAULT			0

#define   DEMOD_DD_TPOUT_MODE_PROP_TPSRMSB_LSB			7
#define   DEMOD_DD_TPOUT_MODE_PROP_TPSRMSB_MASK 		0x01
#define   DEMOD_DD_TPOUT_MODE_PROP_TPSRMSB_ENABLE		1
#define   DEMOD_DD_TPOUT_MODE_PROP_TPSRMSB_DISABLE		0


#endif /*DEMOD_DD_TS_MODE */

/*-------------------------------------------------------------------------*/
#define DEMOD_DD_CONSTEL_PROP					0x1005
#ifdef DEMOD_DD_CONSTEL_PROP
#define DEMOD_DD_CONSTEL_PROP_CODE				0x1005

	typedef struct { /* SET_DVBC_CONSTEL_PROP_struct */
		UINT8 constellation;
		UINT8 constel_autodet;
}  LX_DEMOD_DD_CONSTEL_PROP_struct;

#define DEMOD_DD_CONSTELATION_PROP_LSB					4
#define DEMOD_DD_CONSTELATION_PROP_MASK					0x0f

#define DEMOD_DD_CONSTELATION_PROP_QPSK					0
#define DEMOD_DD_CONSTELATION_PROP_DQPSK				0x1
#define DEMOD_DD_CONSTELATION_PROP_16QAM				0x2
#define DEMOD_DD_CONSTELATION_PROP_32QAM				0x3
#define DEMOD_DD_CONSTELATION_PROP_64QAM				0x4
#define DEMOD_DD_CONSTELATION_PROP_128QAM				0x5
#define DEMOD_DD_CONSTELATION_PROP_256QAM				0x6
#define DEMOD_DD_CONSTELATION_PROP_1024QAM				0x7
#define DEMOD_DD_CONSTELATION_PROP_4096QAM				0x8
#define DEMOD_DD_CONSTELATION_PROP_PSK					0x9
#define DEMOD_DD_CONSTELATION_PROP_VSB					0xa
#define DEMOD_DD_CONSTELATION_PROP_QAM					0xb
#define DEMOD_DD_CONSTELATION_PROP_16APSK				0xc
#define DEMOD_DD_CONSTELATION_PROP_32APSK				0xd
#define	DEMOD_DD_CONSTELATION_PROP_BPSK					0xe
#define DEMOD_DD_CONSTELATION_PROP_AUTO					0xf


#define DEMOD_DD_CONSTELATION_PROP_AUTO_DET_LSB			0
#define DEMOD_DD_CONSTELATION_PROP_AUTO_DET_MASK		0x1

#define DEMOD_DD_CONSTELATION_PROP_AUTO_DET_ENABLE		0
#define DEMOD_DD_CONSTELATION_PROP_AUTO_DET_DISABLE		1

#endif /* DEMOD_DD_CONSTEL*/

/*-------------------------------------------------------------------------*/

#define DEMOD_DD_COUNTRY_GRP_PROP					0x1011
#ifdef DEMOD_DD_COUNTRY_GRP_PROP
#define DEMOD_DD_COUNTRY_GRP_PROP_CODE				0x1011

	typedef struct {
		UINT8 grp;
}  LX_DEMOD_DD_COUNTRY_GRP_PROP_struct;

#define DEMOD_DD_COUNTRY_GRP_PROP_LSB				0
#define DEMOD_DD_COUNTRY_GRP_PROP_MASK				0x0f
#define DEMOD_DD_COUNTRY_GRP_PROP_NONE				0x0
#define DEMOD_DD_COUNTRY_GRP_PROP_EU				0x1
#define DEMOD_DD_COUNTRY_GRP_PROP_END				0x2
#define DEMOD_DD_COUNTRY_GRP_PROP_UNKNOWN			0xf

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
#define   DEMOD_DD_AUTO_MODE_PROP					0x1001	//jeongpil.yun not implemented 15/9/1

#ifdef	  DEMOD_DD_AUTO_MODE_PROP
  #define DEMOD_DD_AUTO_MODE_PROP_CODE				0x1001


    typedef struct
    { /* LX_DEMOD_DD_TUNE_MODE_PROP_struct */
	UINT8	auto_detect;
    } LX_DEMOD_DD_AUTO_MODE_PROP_struct;

   /* DD_TUNE_MODE property*/
	#define  DEMOD_DD_AUTO_MODE_PROP_DETEN_LSB		0
	#define  DEMOD_DD_AUTO_MODE_PROP_DETEN_MASK		0x0f
	#define  DEMOD_DD_AUTO_MODE_PROP_DET_DVBT_DVBT2_ENABLE	1
	#define  DEMOD_DD_AUTO_MODE_PROP_DET_DVBT_ONLY_ENABLE	2
	#define  DEMOD_DD_AUTO_MODE_PROP_DET_DVBT2_ONLY_ENABLE	3
	#define  DEMOD_DD_AUTO_MODE_PROP_DET_DVBC_DVBC2_ENABLE	4
	#define  DEMOD_DD_AUTO_MODE_PROP_DET_DVBC_ONLY_ENABLE	5
	#define  DEMOD_DD_AUTO_MODE_PROP_DET_DVBC2_ONLY_ENABLE	6
	#define  DEMOD_DD_AUTO_MODE_PROP_DET_DVBS_DVBS2_ENABLE	7
	#define  DEMOD_DD_AUTO_MODE_PROP_DET_DVBS_ONLY_ENABLE	8
	#define  DEMOD_DD_AUTO_MODE_PROP_DET_DVBS2_ONLY_ENABLE	9
	#define  DEMOD_DD_AUTO_MODE_PROP_DET_VSB_ATSC3_ENABLE	10
	#define  DEMOD_DD_AUTO_MODE_PROP_DET_VSB_ONLY_ENABLE	11
	#define  DEMOD_DD_AUTO_MODE_PROP_DET_ATSC3_ONLY_ENABLE	12

#endif /* DEMOD_DD_AUTO_MODE_PROP */

/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/***************ISDBT / DVBT/ DVBT2 / DVBS / DVBS2/DVBC/ DVBC2/  DEBUG*********/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/


/*-------------------------------------------------------------------------*/
#define DEMOD_DD_DVBT_HIERARCHY_PROP				0x1004
#ifdef DEMOD_DD_DVBT_HIERARCHY_PROP
#define DEMOD_DD_DVBT_HIERARCHY_PROP_CODE			0x1004

	typedef struct { /* SET_DVBT_HIERARCHY_PROP_struct */
		UINT8 hierhpsel;
}  LX_DEMOD_DD_DVBT_HIERARCHY_PROP_struct;

#define DEMOD_DD_DVBT_HIERARCHY_PROP_HIERHPSEL_D_LSB		0
#define DEMOD_DD_DVBT_HIERARCHY_PROP_HIERHPSEL_D_MASK		0x01
#define DEMOD_DD_DVBT_HIERARCHY_PROP_HIERHPSEL_HIGH		1
#define DEMOD_DD_DVBT_HIERARCHY_PROP_HIERHPSEL_LOW		0

#endif /* DEMOD_DD_DVBT_HIERARCHY*/


/*-------------------------------------------------------------------------*/
#define   DEMOD_DD_DVBT2_MODE_PROP				0x1006
#ifdef	  DEMOD_DD_DVBT2_MODE_PROP
  #define DEMOD_DD_DVBT2_MODE_PROP_CODE 			0x001006


    typedef struct { /* LX_DEMOD_DD_DVBT2_MODE_PROP_struct */
      UINT8   lock_mode;
   } LX_DEMOD_DD_DVBT2_MODE_PROP_struct;

   /* DVBT2_MODE property, LOCK_MODE field definition (NO TITLE)*/
   #define  DEMOD_DD_DVBT2_MODE_PROP_LOCK_MODE_LSB		0
   #define  DEMOD_DD_DVBT2_MODE_PROP_LOCK_MODE_MASK		0x01
   #define  DEMOD_DD_DVBT2_MODE_PROP_LOCK_MODE_DEFAULT		0
   //#define DEMOD_DD_DVBT2_MODE_PROP_LOCK_MODE_ANY		0
   #define DEMOD_DD_DVBT2_MODE_PROP_LOCK_MODE_BASE_ONLY		0
   #define DEMOD_DD_DVBT2_MODE_PROP_LOCK_MODE_LITE_ONLY		1

#endif /* DEMOD_DD_DVBT2_MODE_PROP */

/*-------------------------------------------------------------------------*/
/* DVBS_AFC_RANGE property definition */
#define   DEMOD_DD_DVBS_AFC_RANGE_PROP				0x1007

#ifdef	  DEMOD_DD_DVBS_AFC_RANGE_PROP
  #define DEMOD_DD_DVBS_AFC_RANGE_PROP_CODE			0x001007


    typedef struct { /* DEMOD_DD_DVBS_AFC_RANGE_PROP_struct */
      UINT32	range_khz;
   } LX_DEMOD_DD_DVBS_AFC_RANGE_PROP_struct;

   /* DVBS_AFC_RANGE property, RANGE_KHZ field definition (NO TITLE)*/
   #define  DEMOD_DD_DVBS_AFC_RANGE_PROP_RANGE_KHZ_LSB		0
   #define  DEMOD_DD_DVBS_AFC_RANGE_PROP_RANGE_KHZ_MASK 	0xffff
   #define  DEMOD_DD_DVBS_AFC_RANGE_PROP_RANGE_KHZ_DEFAULT	4000
#endif /* DEMOD_DD_DVBS_AFC_RANGE_PROP */


/*-------------------------------------------------------------------------*/
/* DVBS2_AFC_RANGE property definition */
#define   DEMOD_DD_DVBS2_AFC_RANGE_PROP				0x1008

#ifdef	  DEMOD_DD_DVBS2_AFC_RANGE_PROP
  #define DEMOD_DD_DVBS2_AFC_RANGE_PROP_CODE			0x001008


    typedef struct { /* LX_DEMOD_DD_DVBS_AFC_RANGE_PROP_struct */
      UINT32	range_khz;
   } LX_DEMOD_DD_DVBS2_AFC_RANGE_PROP_struct;

   /* DVBS_AFC_RANGE property, RANGE_KHZ field definition (NO TITLE)*/
   #define  DEMOD_DD_DVBS2_AFC_RANGE_PROP_RANGE_KHZ_LSB		0
   #define  DEMOD_DD_DVBS2_AFC_RANGE_PROP_RANGE_KHZ_MASK	0xffff
   #define  DEMOD_DD_DVBS2_AFC_RANGE_PROP_RANGE_KHZ_DEFAULT	4000
#endif /* LX_DEMOD_DD_DVBS2_AFC_RANGE_PROP */


/*------------------------- -------------------------------------------------*/
#define DEMOD_DD_DVBS_OPMSEL_PROP				0x1009
#ifdef DEMOD_DD_DVBS_OPMSEL_PROP
#define DEMOD_DD_DVBS_OPMSEL_PROP_CODE				0x1009

typedef struct
{/*SET_DVBS_BLIND_SCAN_PROP_struct */
	UINT8 opmSel;
} LX_DEMOD_DD_DVBS_OPMSEL_PROP_struct;

#define DEMOD_DD_DVBS_OPM_SEL_PROP_LSB				0
#define DEMOD_DD_DVBS_OPM_SEL_PROP_MASK				0xff
#define DEMOD_DD_DVBS_OPM_SEL_PROP_BLIND_SCAN_MODE		0x30
#define DEMOD_DD_DVBS_OPM_SEL_PROP_BLIND_LOCK_MODE		0x20
#define DEMOD_DD_DVBS_OPM_SEL_PROP_NORMAL_MODE			0x10

#endif /*DEMOD_DD_DVBS_OPMSEL*/


/*-------------------------------------------------------------------------*/
/* LGDBB DEMOD_DD_DISEQC_CONFIG_PROP property definition */
#define   DEMOD_DD_DISEQC_CONFIG_PROP				0x100F

#ifdef	  DEMOD_DD_DISEQC_CONFIG_PROP
  #define DEMOD_DD_DISEQC_CONFIG_PROP_CODE			0x00100F


typedef struct
{ /* LX_DEMOD_DD_DISEQC_PARAM_PROP_struct */
	UINT8 message_sel;   //envelope or 22khz
	UINT8 diseqc_2_x_enable;
	UINT8 message_repeat_en;

} LX_DEMOD_DD_DISEQC_CONFIG_PROP_struct;

   /* DD_DISEQC_PARAM property, SEQUENCE_MODE field definition (NO TITLE)*/
#define  DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_SEL_LSB		0
#define  DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_SEL_MASK		0x01

#define  DEMOD_DD_DISEQC_CONFIG_PROP_EN_2_X_LSB			1
#define  DEMOD_DD_DISEQC_CONFIG_PROP_EN_2_X_MASK		0x01

#define  DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_REPEAT_LSB 	2
#define  DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_REPEAT_MASK	0x01

#define DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_SEL_ENVELOPE	0
#define DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_SEL_TONE_22KHZ	1
#define DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_SEL_DEFAULT 	0

#define  DEMOD_DD_DISEQC_CONFIG_PROP_EN_2_X_ENABLE		1
#define  DEMOD_DD_DISEQC_CONFIG_PROP_EN_2_X_DISABLE		0
#define  DEMOD_DD_DISEQC_CONFIG_PROP_EN_2_X_DEFAULT		0

#define  DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_REPEAT_ENABLE	1
#define  DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_REPEAT_DISABLE	0
#define  DEMOD_DD_DISEQC_CONFIG_PROP_MESSAGE_REPEAT_DEFAULT	0

#endif /* DEMOD_DD_DISEQC_PARAM_PROP */


/* --------------------------------------------*/
/* PROPERTIES STRUCT			       */
/* This stores all property fields	       */
/* --------------------------------------------*/
typedef struct {
#ifdef	  DEMOD_DD_BER_RESOL_PROP
	LX_DEMOD_DD_BER_RESOL_PROP_struct			dd_ber_resol;
#endif /* DEMOD_DD_BER_RESOL_PROP */

#ifdef	  DEMOD_DD_IF_FREQ_PROP
	LX_DEMOD_DD_IF_FREQ_PROP_struct				dd_if_freq;
#endif /* DEMOD_DD_IF_INPUT_FREQ_PROP */

#ifdef	  DEMOD_DD_CLOCK_MODE_PROP
	LX_DEMOD_DD_CLOCK_MODE_PROP_struct			dd_clk_mode;
#endif /* DEMOD_DD_CLOCK_MODE_PROP */

#ifdef	  DEMOD_DD_MODE_PROP
	LX_DEMOD_DD_MODE_PROP_struct				dd_mode;
#endif /*DEMOD_DD_MODE */

#ifdef	  DEMOD_DD_TS_MODE_PROP
	LX_DEMOD_DD_TS_MODE_PROP_struct 			dd_ts_mode;
#endif /* DEMOD_DD_TS_MODE_PROP */

#ifdef	  DEMOD_DD_ADC_PROP
	LX_DEMOD_DD_ADC_PROP_CODE_struct			dd_adc_sel;
#endif /* DEMOD_DD_ADC_PROP */

#ifdef    DEMOD_DD_CLKPHASE_PROP
	 LX_DEMOD_DD_CLKPHASE_PROP_CODE_struct		dd_clkphase_sel;
#endif/* DEMOD_DD_CLKPHASE_PROP */
				 
#ifdef    DEMOD_DD_SDRAM_PROP
	 LX_DEMOD_DD_SDRAM_PROP_CODE_struct			dd_sdram_mode;
#endif/* DEMOD_DD_SDRAM_PROP */

#ifdef    DEMOD_DD_TWOCTI_PROP
	 LX_DEMOD_DD_TWOCTI_PROP_CODE_struct		dd_twocti_mode;
#endif/* DEMOD_DD_TWOCTI_PROP */

#ifdef    DEMOD_DD_SDRAM_PWR_PROP
	 LX_DEMOD_DD_SDRAM_PWR_PROP_CODE_struct		dd_sdram_pwr;
#endif/* DEMOD_DD_SDRAM_PWR_PROP */
#ifdef	  DEMOD_DD_AGC_PROP
	LX_DEMOD_DD_AGC_PROP_struct					dd_agc;
#endif /* DEMOD_DD_AGC_PROP */

#ifdef	  DEMOD_DD_TPOUT_MODE_PROP
	LX_DEMOD_DD_TPOUT_MODE_PROP_struct			dd_tpout_mode;
#endif /* DEMOD_DD_TPOUT_MODE_PROP */

#ifdef	  DEMOD_DD_CONSTEL_PROP
	LX_DEMOD_DD_CONSTEL_PROP_struct				dd_constel;
#endif /* DEMOD_DD_CONSTEL_PROP */

#ifdef	  DEMOD_DD_AUTO_MODE_PROP
	LX_DEMOD_DD_AUTO_MODE_PROP_struct			dd_auto_mode;
#endif /* DEMOD_DD_AUTO_MODE_PROP */

#ifdef	  DEMOD_DD_COUNTRY_GRP_PROP
	LX_DEMOD_DD_COUNTRY_GRP_PROP_struct			dd_country_grp;
#endif /* DEMOD_DD_COUNTRY_GRP_PROP */


/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/***************ISDBT / DVBT/ DVBT2 / DVBS / DVBS2/DVBC/ DVBC2/  DEBUG*********/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/

#ifdef	  DEMOD_DD_DISEQC_CONFIG_PROP
	LX_DEMOD_DD_DISEQC_CONFIG_PROP_struct		dd_diseqc_config;
#endif /* DEMOD_DD_DISEQC_CONFIG_PROP */

#ifdef	  DEMOD_DD_DVBT_HIERARCHY_PROP
	LX_DEMOD_DD_DVBT_HIERARCHY_PROP_struct 		dd_dvbt_hp_sel;
#endif /* DEMOD_DD_DVBT_HIERARCHY_PROP */

#ifdef	  DEMOD_DD_DVBT2_MODE_PROP
	LX_DEMOD_DD_DVBT2_MODE_PROP_struct			dd_dvbt2_lock_mode;
#endif

#ifdef	  DEMOD_DD_DVBS_AFC_RANGE_PROP
	LX_DEMOD_DD_DVBS_AFC_RANGE_PROP_struct		dd_dvbs_afc_range;
#endif

#ifdef	  DEMOD_DD_DVBS2_AFC_RANGE_PROP
	LX_DEMOD_DD_DVBS2_AFC_RANGE_PROP_struct		dd_dvbs2_afc_range;
#endif

#ifdef	  DEMOD_DD_DVBS_OPMSEL_PROP
	LX_DEMOD_DD_DVBS_OPMSEL_PROP_struct			dd_dvbs_opm_sel;
#endif /* DEMOD_DD_DVBS_OPMSEL_PROP */

} LX_DEMOD_L1_PropObj;

//#define   DEMOD_GET_PROPERTY_STRING
#endif /* _DBB_DEMOD_L1_PROPERTIES_H_ */








