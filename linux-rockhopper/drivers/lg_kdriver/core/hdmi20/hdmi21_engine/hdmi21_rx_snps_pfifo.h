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

#ifndef	_HDMI21_RX_SNPS_PFIFO_H_
#define	_HDMI21_RX_SNPS_PFIFO_H_

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

#define HDMI21_PFIFO_READ_COUNT_PER_OP	8

#define HDMI21_SNPS_REG_PKTFIFO_CONFIG 				(0x1500) 	
#define HDMI21_SNPS_FIELD_PKTFIFO_WRITE_EN			BIT(0)

#define HDMI21_SNPS_REG_PKTFIFO_STORE_FILT_CONFIG	(0x1504)
#define HDMI21_SNPS_FIELD_PKTFIFO_STORE_GENPKT1		BIT(29)
#define HDMI21_SNPS_FIELD_PKTFIFO_STORE_GENPKT0		BIT(28)
#define HDMI21_SNPS_FIELD_PKTFIFO_STORE_EMD			BIT(14)
#define HDMI21_SNPS_FIELD_PKTFIFO_STORE_DRMIF		BIT(13)
#define HDMI21_SNPS_FIELD_PKTFIFO_STORE_NTSCVBIIF	BIT(12)
#define HDMI21_SNPS_FIELD_PKTFIFO_STORE_AUDIF		BIT(10)
#define HDMI21_SNPS_FIELD_PKTFIFO_STORE_SRCPDIF		BIT(9)
#define HDMI21_SNPS_FIELD_PKTFIFO_STORE_AVIIF		BIT(8)
#define HDMI21_SNPS_FIELD_PKTFIFO_STORE_VSIF		BIT(7)
#define HDMI21_SNPS_FIELD_PKTFIFO_STORE_AMD			BIT(6)
#define HDMI21_SNPS_FIELD_PKTFIFO_STORE_GMD			BIT(5)
#define HDMI21_SNPS_FIELD_PKTFIFO_STORE_ISRC		BIT(4)
#define HDMI21_SNPS_FIELD_PKTFIFO_STORE_ACP			BIT(3)
#define HDMI21_SNPS_FIELD_PKTFIFO_STORE_GCP			BIT(2)
#define HDMI21_SNPS_FIELD_PKTFIFO_STORE_ACR			BIT(1)
#define HDMI21_SNPS_FIELD_PKTFIFO_STORE_FILT_EN		BIT(0)

#define HDMI21_SNPS_REG_PKTFIFO_THR_CONFIG0			(0x1508)
#define HDMI21_SNPS_FIELD_PKTFIFO_THR_PASS_QST		MSK(10, 0)

#define HDMI21_SNPS_REG_PKTFIFO_THR_CONFIG1			(0x150C)
#define HDMI21_SNPS_FIELD_PKTFIFO_THR_HIGH_QST		MSK(10, 16)
#define HDMI21_SNPS_FIELD_PKTFIFO_THR_LOW_QST		MSK(10, 0)

#define HDMI21_SNPS_REG_PKTFIFO_CONTROL				(0x1510)
#define HDMI21_SNPS_FIELD_PKTFIFO_LTFILL_CLR_P		BIT(8)
#define HDMI21_SNPS_FIELD_PKTFIFO_INIT_P			BIT(0)

#define HDMI21_SNPS_REG_PKTFIFO_FILL_STATUS			(0x1514)
#define HDMI21_SNPS_FIELD_PKTFIFO_THR_HIGH_ST		BIT(28)
#define HDMI21_SNPS_FIELD_PKTFIFO_THR_PASS_ST		BIT(24)
#define HDMI21_SNPS_FIELD_PKTFIFO_THR_LOW_ST		BIT(20)
#define HDMI21_SNPS_FIELD_PKTFIFO_NEW_ENTRY_ST		BIT(16)
#define HDMI21_SNPS_FIELD_PKTFIFO_FILL_STS			MSK(16, 0)

#define HDMI21_SNPS_REG_PKTFIFO_LTERM_FILL_STATUS	(0x1518)
#define HDMI21_SNPS_FIELD_PKTFIFO_LTFILL_MAX_STS	MSK(16, 16)
#define HDMI21_SNPS_FIELD_PKTFIFO_LTFILL_MIN_STS	MSK(16, 0)

#define HDMI21_SNPS_REG_PKTFIFO_SKIP_PKT_CONTROL	(0x151C)
#define HDMI21_SNPS_FIELD_PKTFIFO_SKIP_PKT_P		BIT(0)

#define HDMI21_SNPS_REG_PKTFIFO_DATA				(0x1520)
#define HDMI21_SNPS_FIELD_PKTFIFO_DATA				MSK(31, 0)

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void HDMI21_PFIFO_Rx_Set_Initialize(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isEnable);
void HDMI21_PFIFO_Rx_Set_ResetPktFifo(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
int  HDMI21_PFIFO_Rx_Get_FifoData(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

