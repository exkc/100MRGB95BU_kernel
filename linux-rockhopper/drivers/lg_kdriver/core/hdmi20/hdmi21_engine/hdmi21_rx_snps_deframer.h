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
 *  @date       2019-04-17
 *  @note       Additional information.
 */

#ifndef	_HDMI21_RX_SNPS_DEFRAMER_H_
#define	_HDMI21_RX_SNPS_DEFRAMER_H_

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

#define HDMI21_SNPS_REG_DEFRAMER_CONFIG0			(0x270)
#define HDMI21_SNPS_FIELD_VS_CNT_THR_QST			MSK(8, 20)
#define HDMI21_SNPS_FIELD_HS_POL_QST				MSK(2, 18)
#define HDMI21_SNPS_FIELD_VS_POL_QST				MSK(2, 16)
#define HDMI21_SNPS_FIELD_CTL_SPIKEFILTER_EN_QST	BIT(12)
#define HDMI21_SNPS_FIELD_VS_REMAPFILTER_EN_QST		BIT(8)
#define HDMI21_SNPS_FIELD_HS_FILTER_ORDER_QST		MSK(2, 2)
#define HDMI21_SNPS_FIELD_VS_FILTER_ORDER_QST		MSK(2, 0)


#define HDMI21_SNPS_REG_DEFRAMER_CONFIG1			(0x274)
#define HDMI21_SNPS_FIELD_OPMODE_HDMI_TYPE_QST		MSK(2, 28)
#define HDMI21_SNPS_FIELD_HDMI2DVI_THR_QST			MSK(2, 24)
#define HDMI21_SNPS_FIELD_DVI2HDMI_THR_QST			MSK(3, 20)
#define HDMI21_SNPS_FIELD_OPMODE_HDMI_QST			MSK(2, 16)
#define HDMI21_SNPS_FIELD_GB_ERR_THR_QST			MSK(8, 8)
#define HDMI21_SNPS_FIELD_LAST_FRAME_GB_CHECK_QST	MSK(4, 4)
#define HDMI21_SNPS_FIELD_NUM_PREAMBLE_LOCK_QST		MSK(4, 0)


#define HDMI21_SNPS_REG_DEFRAMER_VSYNC_CNT_CLEAR	(0x278)
#define HDMI21_SNPS_FIELD_VSYNC_CNT_CLR_P			BIT(0)

#define HDMI21_SNPS_REG_DEFRAMER_STATUS				(0x27C)
#define HDMI21_SNPS_FIELD_OPMODE_STS				MSK(3,4)
#define HDMI21_SNPS_FIELD_AUTOHDMIDVI_STS			BIT(0)
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void	HDMI21_DEFRAMER_Rx_Set_Initialize(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
bool 	HDMI21_DEFRAMER_Rx_Get_IsDVIMode(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
UINT32	HDMI21_DEFRAMER_Rx_Get_CurrentOpMode(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
void 	HDMI21_DEFRAMER_Rx_Set_NumOfPreambleLock(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 num);
void HDMI21_DEFRAMER_Rx_Set_HVSyncPolarity(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isAuto, bool hInversion, bool vInversion);
void HDMI21_DEFRAMER_Rx_Set_DviHdmiThresHold(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int dviToHdmi, int hdmiToDvi);
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

