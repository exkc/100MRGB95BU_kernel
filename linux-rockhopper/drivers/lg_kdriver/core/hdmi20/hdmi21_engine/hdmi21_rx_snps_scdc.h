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


/** @file
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author     won.hur
 *  @version    1.0
 *  @date       2019-04-01
 *  @note       Additional information.
 */

#ifndef	_HDMI21_RX_SNPS_SCDC_H_
#define	_HDMI21_RX_SNPS_SCDC_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/


#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/**
 * Bit field mask
 * @param m	width
 * @param n shift
 */
#ifndef MSK
#define MSK(m, n)		(((1 << (m)) - 1) << (n))
#endif

/**
 * Bit mask
 * @param n shift
 */
#ifndef BIT
#define BIT(n)			MSK(1, (n))
#endif

#define HDMI21_SNPS_REG_SCDC_CONFIG				(0x580)
#define HDMI21_SNPS_FIELD_FRL_START_TIMER_THR_SEL MSK(2, 9)
#define HDMI21_SNPS_FIELD_FRL_START_CHK_SB_QST	BIT(8)
#define HDMI21_SNPS_FIELD_RR_IFFLAGS_ALREADYSET	BIT(5)
#define HDMI21_SNPS_FIELD_SCDC_STANDBY			BIT(2)
#define HDMI21_SNPS_FIELD_SCDC_HPDLOW			BIT(1)
#define HDMI21_SNPS_FIELD_SCDC_POWERPROVIDED	BIT(0)

#define HDMI21_SNPS_REG_SCDC_CONTROL			(0x584)
#define HDMI21_SNPS_FIELD_FRL_START_OVR_P		BIT(0)

/* SYNOPSYS LCA03 REG 0x584~0x5DC changed to 0x588~0x5E0 in LCA04 */
#define HDMI21_SNPS_O20A0_REG_SCDC_REGBANK_STATUS2	(0x58C)
#define HDMI21_SNPS_O20B0_REG_SCDC_REGBANK_STATUS2	(0x590)
#define HDMI21_SNPS_FIELD_SCDC_FRL_RATE			MSK(4, 8)

#define HDMI21_SNPS_O20A0_REG_SCDC_REGBANK_STATUS1	(0x588)
#define HDMI21_SNPS_O20B0_REG_SCDC_REGBANK_STATUS1	(0x58C)
#define HDMI21_SNPS_FIELD_SCDC_TMDSBITCLKRATIO	BIT(1)

#define HDMI21_SNPS_O20A0_REG_SCDC_REGBANK_CONFIG0	(0x5BC)
#define HDMI21_SNPS_O20B0_REG_SCDC_REGBANK_CONFIG0	(0x5C0)
#define HDMI21_SNPS_FIELD_SCDC_SINKVERSION_QST	MSK(8, 0)

#define HDMI21_SNPS_O20A0_REG_SCDC_REGBANK_CONFIG2	(0x5C4)
#define HDMI21_SNPS_O20B0_REG_SCDC_REGBANK_CONFIG2	(0x5C8)

#define HDMI21_SNPS_O20A0_REG_SCDC_REGBANK_CONFIG3	(0x5C8)
#define HDMI21_SNPS_O20B0_REG_SCDC_REGBANK_CONFIG3	(0x5CC)


	
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
	HDMI21_SCDC_TMDS_3G = 0,
	HDMI21_SCDC_TMDS_6G,
	HDMI21_SCDC_FRL_3G_3L,
	HDMI21_SCDC_FRL_6G_3L,
	HDMI21_SCDC_FRL_6G_4L,
	HDMI21_SCDC_FRL_8G_4L,
	HDMI21_SCDC_FRL_10G_4L,
	HDMI21_SCDC_FRL_12G_4L,
	HDMI21_SCDC_FRL_MAX_MODE
} HDMI21_SCDC_FRL_MODE_T;


typedef struct
{
	UINT32
		SCDC_SOURCEVERSION:8,		//7:0
		SCDC_STATUSUPDATE:1, 		//8
		SCDC_CEDUPDATE:1,			//9		
		SCDC_RRTEST:1,				//10
		SCDC_SOURCE_TEST_UPDATE:1,	//11
		SCDC_FRL_START:1,			//12
		SCDC_FLT_UPDATE:1,			//13
		SCDC_RSED_UPDATE:1,			//14
		b_rsvd:13,					//27:15
		FRL_START_STS:1,			//28
		b_rsvd1:3;					//31:29
} HDMI21_SNPS_LINK_REG_0X584_T;

typedef struct
{
	UINT32
		SCDC_SCRAMB_EN:1,		//0
		SCDC_TMDSBITCLKRATIO:1,	//1
		b_rsvd:6,				//7:2
		SCDC_SCRAMB_STATUS:1,	//8
		b_rsvd1:23;				//31:9
} HDMI21_SNPS_LINK_REG_0X588_T;

typedef struct
{
	UINT32
		SCDC_RRENABLE:1,		//0
		SCDC_FLT_NO_RETRAIN:1,	//1
		b_rsvd:6,				//7:2
		SCDC_FRL_RATE:4,		//11:8
		SCDC_FFE_LEVELS:4,		//15:12
		b_rsvd1:16;				//31:16
} HDMI21_SNPS_LINK_REG_0X58C_T;

typedef struct
{
	UINT32
		SCDC_CLOCKDETECTED:1,		//0
		SCDC_CH0LOCKED:1,			//1
		SCDC_CH1LOCKED:1,			//2
		SCDC_CH2LOCKED:1,			//3
		b_rsvd:5,					//8:4
		SCDC_LN0LOCKED:1,			//9
		SCDC_LN1LOCKED:1,			//10
		SCDC_LN2LOCKED:1, 			//11
		SCDC_LN3LOCKED:1,			//12
		b_rsvd1:1,					//13
		SCDC_FLT_READY:1, 			//14
		b_rsvd2:1,					//15
		SCDC_FLT_LN0_LTP_REQ:4,		//19:16
		SCDC_FLT_LN1_LTP_REQ:4,		//23:20
		SCDC_FLT_LN2_LTP_REQ:4,		//27:24
		SCDC_FLT_LN3_LTP_REQ:4;		//31:28
} HDMI21_SNPS_LINK_REG_0X590_T;


typedef struct
{
	UINT32
		SCDC_ERR_DET0:15,			//14:0
		SCDC_ERR_DET0_VALID:1,		//15
		SCDC_ERR_DET1:15,			//30:16
		SCDC_ERR_DET1_VALID:1;		//31
} HDMI21_SNPS_LINK_REG_0X594_T;

typedef struct
{
	UINT32
		SCDC_ERR_DET2:15,			//14:0
		SCDC_ERR_DET2_VALID:1,		//15
		SCDC_ERDET_LANE0:15,		//30:16
		SCDC_ERDET_LANE0_VALID:1;	//31
} HDMI21_SNPS_LINK_REG_0X598_T;

typedef struct
{
	UINT32
		SCDC_ERDET_LANE1:15,		//14:0
		SCDC_ERDET_LANE1_VALID:1,	//15
		SCDC_ERDET_LANE2:15,		//30:16
		SCDC_ERDET_LANE2_VALID:1;	//31
} HDMI21_SNPS_LINK_REG_0X59C_T;

typedef struct
{
	UINT32
		SCDC_ERDET_LANE3:15,		//14:0
		SCDC_ERDET_LANE3_VALID:1,	//15
		SCDC_RSFEC_CERDET:15,		//30:16
		SCDC_RSFEC_CERDET_VALID:1;	//31
} HDMI21_SNPS_LINK_REG_0X5A0_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
HDMI21_SCDC_FRL_MODE_T HDMI21_SCDC_Rx_Get_ScdcMode(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
void HDMI21_SCDC_Rx_Set_ScdcConfig(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isSet);
void HDMI21_SCDC_Rx_Set_Initiate(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
void HDMI21_SCDC_Rx_Set_FrlStartManualOn(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
void HDMI21_SCDC_Rx_Set_CedCountRst(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isReset);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

