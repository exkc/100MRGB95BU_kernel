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
 *  @date       2019-03-25
 *  @note       Additional information.
 */

#ifndef	_HDMI21_RX_SNPS_HDCP_H_
#define	_HDMI21_RX_SNPS_HDCP_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/


#ifdef	__cplusplus

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

#define HDMI21_SNPS_REG_HDCP14_CONFIG				(0x290)
#define HDMI21_SNPS_FIELD_HDCP14_DELAY_QST			MSK(2, 30)
#define HDMI21_SNPS_FIELD_REPEATER_QST				BIT(28)
#define HDMI21_SNPS_FIELD_FASTREAUTH_QST			BIT(27)
#define HDMI21_SNPS_FIELD_FEATURES_1DOT1_QST		BIT(26)
#define HDMI21_SNPS_FIELD_FASTI2C_QST				BIT(25)
#define HDMI21_SNPS_FIELD_HDMI_RSVD_QST				BIT(24)
#define HDMI21_SNPS_FIELD_EESS_CTL_THR_QST			MSK(4, 16)
#define HDMI21_SNPS_FIELD_OESS_CTL3_THR_QST			MSK(4, 8)
#define HDMI21_SNPS_FIELD_EESS_OESS_SEL_QST			MSK(2, 4)
#define HDMI21_SNPS_FIELD_KEY_DECRYPT_EN_QST		BIT(0)


#define HDMI21_SNPS_REG_HDCP14_WOO_CONFIG			(0x294)
#define HDMI21_SNPS_FIELD_HDCP_WOO_END_QST			MSK(10, 16)
#define HDMI21_SNPS_FIELD_HDCP_WOO_START_QST		MSK(10, 0)

#define HDMI21_SNPS_REG_HDCP14_KEY_H				(0x2A4)
#define HDMI21_SNPS_FIELD_HDCP_KEY_HIGH				MSK(24, 0)

#define HDMI21_SNPS_REG_HDCP14_KEY_L				(0x2A8)
#define HDMI21_SNPS_FIELD_HDCP_KEY_LOW				(0xFFFFFFFF)	

#define HDMI21_SNPS_REG_HDCP14_KEY_STATUS			(0x2AC)
#define HDMI21_SNPS_FIELD_HDCP_KEY_WR_OK			BIT(8)
#define HDMI21_SNPS_FIELD_HDCP_KEY_INDEX			MSK(6, 0)

#define HDMI21_SNPS_REG_HDCP14_BKSV_H				(0x2B0)
#define HDMI21_SNPS_FIELD_HDCP_BKSV_HIGH_QST		MSK(8, 0)

#define HDMI21_SNPS_REG_HDCP14_BKSV_L				(0x2B4)
#define HDMI21_SNPS_FIELD_HDCP_BKSV_LOW_QST			(0xFFFFFFFF)

#define HDMI21_SNPS_REG_HDCP14_STATUS				(0x2b8)
#define HDMI21_SNPS_FIELD_HDCP14_DECRYPT_ON			BIT(8)
#define HDMI21_SNPS_FIELD_HDCP14_OESS_EESS_CHG_ST	BIT(5)
#define HDMI21_SNPS_FIELD_HDCP14_AUTH_ST			BIT(4)
#define HDMI21_SNPS_FIELD_AUTH_CURSTATE				MSK(2,0)

#define HDMI21_SNPS_REG_HDCP14_BSTATUS				(0x2bc)
#define HDMI21_SNPS_FIELD_HDCP_BSTATUS				MSK(16, 0)

#define HDMI21_SNPS_REG_HDCP14_DDC_STATUS0			(0x2c0)
#define HDMI21_SNPS_FIELD_HDCP_RI					MSK(16, 16)
#define HDMI21_SNPS_FIELD_HDCP_AINFO				BIT(8)
#define HDMI21_SNPS_FIELD_HDCP_PJ					MSK(8, 0)

#define HDMI21_SNPS_REG_HDCP14_DDC_STATUS1			(0x2c4)
#define HDMI21_SNPS_FIELD_HDCP_AN_HIGH				(0xFFFFFFFF)	

#define HDMI21_SNPS_REG_HDCP14_DDC_STATUS2			(0x2c4)
#define HDMI21_SNPS_FIELD_HDCP_AN_LOW				(0xFFFFFFFF)	

#define HDMI21_SNPS_REG_HDCP14_DDC_STATUS3			(0x2cc)
#define HDMI21_SNPS_FIELD_HDCP_AKSV_HIGH			(0x000000FF)	

#define HDMI21_SNPS_REG_HDCP14_DDC_STATUS4			(0x2d0)
#define HDMI21_SNPS_FIELD_HDCP_AKSV_LOW				(0xFFFFFFFF)	

#define HDMI21_SNPS_REG_HDCP14_RPT_KSV_H			(0x2d4)
#define HDMI21_SNPS_FIELD_RPT_KSV_HIGH				MSK(8, 0)	

#define HDMI21_SNPS_REG_HDCP14_RPT_KSV_L			(0x2d8)
#define HDMI21_SNPS_FIELD_RPT_KSV_LOW				(0xFFFFFFFF)	

#define HDMI21_SNPS_REG_HDCP14_RPT_CONTROL			(0x2dc)
#define HDMI21_SNPS_FIELD_RPT_LOSTAUTH				BIT(2)
#define HDMI21_SNPS_FIELD_RPT_TIMEOUT				BIT(1)
#define HDMI21_SNPS_FIELD_RPT_KSVLISTREADY			BIT(0)

#define HDMI21_SNPS_REG_HDCP14_RPT_KSVFIFO			(0x2e0)
#define HDMI21_SNPS_FIELD_RPT_KSV_INDEX				MSK(7, 0)	

#define HDMI21_SNPS_REG_HDCP14_RPT_STATUS			(0x2e4)
#define HDMI21_SNPS_FIELD_RPT_WAITINGKSV			BIT(8)
#define HDMI21_SNPS_FIELD_RPT_KSVHOLD				BIT(4)
#define HDMI21_SNPS_FIELD_RPT_READY					BIT(0)

#define HDMI21_SNPS_REG_HDCP2_STATUS				(0x2f4)
#define HDMI21_SNPS_FIELD_HDCP2_CD_STS				MSK(4, 12)
#define HDMI21_SNPS_FIELD_HDCP2_AVMUTE_STS			BIT(8)
#define HDMI21_SNPS_FIELD_HDCP2_SWITCH_LCK_STS		BIT(7)
#define HDMI21_SNPS_FIELD_HDCP2_OVR_EN_STS			BIT(6)
#define HDMI21_SNPS_FIELD_HDCP2_OVR_VAL_STS			BIT(5)
#define HDMI21_SNPS_FIELD_HDCP2_TYPE_SEL_STS		BIT(4)
#define HDMI21_SNPS_FIELD_HDCP2_IN_AVMUTE			BIT(1)
#define HDMI21_SNPS_FIELD_HDCP2_DECRYPTED			BIT(0)
	
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
	HDMI21_RX_HDCP_HDCP14_UNAUTHENTICATED = 0,
	HDMI21_RX_HDCP_HDCP14_COMPUTATION,
	HDMI21_RX_HDCP_HDCP14_AUTHENTICATED,
	HDMI21_RX_HDCP_HDCP14_UPDATE_RI,
	HDMI21_RX_HDCP_HDCP14_STATE_MAX
} HDMI21_RX_HDCP_HDCP14_STATE_T;


typedef struct 
{
	unsigned char An[8];
	unsigned char Aksv[5];
	unsigned char Bksv[5];
	unsigned char Ri[2];
	unsigned char Bcaps;
	unsigned char Bstatus[2];
} HDMI21_RX_HDCP_HDCP14_INFO_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void HDMI21_HDCP_Rx_Set_Initialize(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
void HDMI21_HDCP_Rx_Set_UpdateHDCP14StableFlag(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isClear);
int  HDMI21_HDCP_Rx_Get_IsCurrentHDCP14(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
int  HDMI21_HDCP_Rx_Get_IsCurrentHDCP23(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);

void HDMI21_HDCP_Rx_Set_HDCP23KeyHistory(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isSet);

int HDMI21_HDCP_Rx_Set_HDCP14Keys(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, LX_HDMI20_HDCP14_DATA_T *pData);
int HDMI21_HDCP_Rx_Set_HDCP14RptKsvList(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 *pData, UINT32 count, UINT32 depth);
int HDMI21_HDCP_Rx_Get_HDCP14Info(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, HDMI21_RX_HDCP_HDCP14_INFO_T *pData);
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

