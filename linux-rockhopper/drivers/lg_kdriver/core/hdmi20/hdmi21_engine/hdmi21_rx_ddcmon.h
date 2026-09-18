/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2021 by LG Electronics Inc.

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
 *  @date       2021-04-19
 *  @note       Additional information.
 */

#ifndef	_HDMI21_RX_DDCMON_H_
#define	_HDMI21_RX_DDCMON_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "hdmi21_hal_driver.h"

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

#define HDMI21_DDCMON_NUM_OF_DDC_BANK		(4)

#define HDMI21_TOP_REG_DDC_MONITOR_CONFIG	(0xD00)
#define HDMI21_TOP_FIELD_DDC_SEL			MSK(2, 8)
#define HDMI21_TOP_FIELD_MONITOR_CLR		BIT(4)
#define HDMI21_TOP_FIELD_MONITOR_EN			BIT(0)

#define HDMI21_TOP_REG_DDC_INTR_EN			(0xD04)
#define HDMI21_TOP_FIELD_DDC4_INTR_EN		BIT(12)
#define HDMI21_TOP_FIELD_DDC3_INTR_EN		BIT(8)
#define HDMI21_TOP_FIELD_DDC2_INTR_EN		BIT(4)
#define HDMI21_TOP_FIELD_DDC1_INTR_EN		BIT(0)

#define HDMI21_TOP_REG_DDC_INTR_CLR			(0xD08)
#define HDMI21_TOP_FIELD_DDC4_INTR_CLR		BIT(12)
#define HDMI21_TOP_FIELD_DDC3_INTR_CLR		BIT(8)
#define HDMI21_TOP_FIELD_DDC2_INTR_CLR		BIT(4)
#define HDMI21_TOP_FIELD_DDC1_INTR_CLR		BIT(0)

#define HDMI21_TOP_REG_DDC_INTR				(0xD0C)
#define HDMI21_TOP_FIELD_DDC4_INTR			BIT(12)
#define HDMI21_TOP_FIELD_DDC3_INTR			BIT(8)
#define HDMI21_TOP_FIELD_DDC2_INTR			BIT(4)
#define HDMI21_TOP_FIELD_DDC1_INTR			BIT(0)


/* DDC BANK #1 */	
#define HDMI21_TOP_REG_DDC1_STATUS			(0xD10)
#define HDMI21_TOP_FIELD_DDC1_HDCP_SHORT	BIT(24)
#define HDMI21_TOP_FIELD_DDC1_SCDC_SHORT	BIT(20)
#define HDMI21_TOP_FIELD_DDC1_NAK			BIT(16)
#define HDMI21_TOP_FIELD_DDC1_FINISH		BIT(12)
#define HDMI21_TOP_FIELD_DDC1_CAP_LENGTH	MSK(3,8)
#define HDMI21_TOP_FIELD_DDC1_INTR_ERR		BIT(4)
#define HDMI21_TOP_FIELD_DDC1_OP_MODE		BIT(0)

#define HDMI21_TOP_REG_DDC1_ADDR			(0xD14)
#define HDMI21_TOP_FIELD_DDC1_DEV_ADDR		MSK(8, 16)
#define HDMI21_TOP_FIELD_DDC1_SUB_ADDR		MSK(8, 0)

#define HDMI21_TOP_REG_DDC1_DATA			(0xD18)

/* DDC BANK #2 */
#define HDMI21_TOP_REG_DDC2_STATUS			(0xD20)
#define HDMI21_TOP_FIELD_DDC2_HDCP_SHORT	BIT(24)
#define HDMI21_TOP_FIELD_DDC2_SCDC_SHORT	BIT(20)
#define HDMI21_TOP_FIELD_DDC2_NAK			BIT(16)
#define HDMI21_TOP_FIELD_DDC2_FINISH		BIT(12)
#define HDMI21_TOP_FIELD_DDC2_CAP_LENGTH	MSK(3,8)
#define HDMI21_TOP_FIELD_DDC2_INTR_ERR		BIT(4)
#define HDMI21_TOP_FIELD_DDC2_OP_MODE		BIT(0)

#define HDMI21_TOP_REG_DDC2_ADDR			(0xD24)
#define HDMI21_TOP_FIELD_DDC2_DEV_ADDR		MSK(8, 16)
#define HDMI21_TOP_FIELD_DDC2_SUB_ADDR		MSK(8, 0)

#define HDMI21_TOP_REG_DDC2_DATA			(0xD28)

/* DDC BANK #3 */
#define HDMI21_TOP_REG_DDC3_STATUS			(0xD30)
#define HDMI21_TOP_FIELD_DDC3_HDCP_SHORT	BIT(24)
#define HDMI21_TOP_FIELD_DDC3_SCDC_SHORT	BIT(20)
#define HDMI21_TOP_FIELD_DDC3_NAK			BIT(16)
#define HDMI21_TOP_FIELD_DDC3_FINISH		BIT(12)
#define HDMI21_TOP_FIELD_DDC3_CAP_LENGTH	MSK(3,8)
#define HDMI21_TOP_FIELD_DDC3_INTR_ERR		BIT(4)
#define HDMI21_TOP_FIELD_DDC3_OP_MODE		BIT(0)

#define HDMI21_TOP_REG_DDC3_ADDR			(0xD34)
#define HDMI21_TOP_FIELD_DDC3_DEV_ADDR		MSK(8, 16)
#define HDMI21_TOP_FIELD_DDC3_SUB_ADDR		MSK(8, 0)

#define HDMI21_TOP_REG_DDC3_DATA			(0xD38)

/* DDC BANK #4 */
#define HDMI21_TOP_REG_DDC4_STATUS			(0xD40)
#define HDMI21_TOP_FIELD_DDC4_HDCP_SHORT	BIT(24)
#define HDMI21_TOP_FIELD_DDC4_SCDC_SHORT	BIT(20)
#define HDMI21_TOP_FIELD_DDC4_NAK			BIT(16)
#define HDMI21_TOP_FIELD_DDC4_FINISH		BIT(12)
#define HDMI21_TOP_FIELD_DDC4_CAP_LENGTH	MSK(3,8)
#define HDMI21_TOP_FIELD_DDC4_INTR_ERR		BIT(4)
#define HDMI21_TOP_FIELD_DDC4_OP_MODE		BIT(0)

#define HDMI21_TOP_REG_DDC4_ADDR			(0xD44)
#define HDMI21_TOP_FIELD_DDC4_DEV_ADDR		MSK(8, 16)
#define HDMI21_TOP_FIELD_DDC4_SUB_ADDR		MSK(8, 0)

#define HDMI21_TOP_REG_DDC4_DATA			(0xD48)

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
	HDMI21_DDCMON_DDC_ENABLE_ALL 	= 0,
	HDMI21_DDCMON_DDC_EDID_ONLY 	= 1,
	HDMI21_DDCMON_DDC_SCDC_ONLY		= 2,
	HDMI21_DDCMON_DDC_HDCP_ONLY		= 3,
	HDMI21_DDCMON_DDC_MAXNUM
} HDMI21_DDCMON_DDC_SEL_TYPE_T;

typedef struct
{
	UINT32
		op_mode:1,			/* 0:0 */
		b_rsvd_0:3,			/* 3:1 */
		intr_err:1,			/* 4:4 */
		b_rsvd_1:3,			/* 7:5 */
		cap_length:3,		/* 10:8 */
		b_rsvd_2:1,			/* 11:11 */
		finish:1,			/* 12:12 */
		b_rsvd_3:3,			/* 15:13 */
		nack:1,				/* 16:16 */
		b_rsvd_4:3,			/* 19:17 */
		scdc_short_rd:1,	/* 20:20 */
		b_rsvd_5:3,			/* 23:21 */
		hdcp_short_rd:1,	/* 24:24 */
		b_rsvd_6:7;			/* 31:25 */
} HDMI21_DDCMON_DDC_STATUS_T;

typedef struct
{
	UINT32	
		sub_addr:8,		/* 7:0 */
		b_rsvd_0:8,		/* 15:8 */
		dev_addr:8,		/* 23:16 */
		b_rsvd_1:8;		/* 31:24 */
} HDMI21_DDCMON_DDC_ADDR_T;

typedef struct
{
	UINT32
		ddc1_intr:1,	/* 0:0 */
		b_rsvd_0:3,		/* 3:1 */
		ddc2_intr:1,	/* 4:4 */
		b_rsvd_1:3,		/* 7:5 */
		ddc3_intr:1,	/* 8:8 */
		b_rsvd_2:3,		/* 11:9 */
		ddc4_intr:1,	/* 12:12 */
		b_rsvd_3:19;	/* 31:13 */
} HDMI21_DDCMON_DDC_INTR_TYPE_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Function Declaration	
----------------------------------------------------------------------------------------*/
void HDMI21_DDCMON_Rx_Set_Initialize(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
void HDMI21_DDCMON_Rx_Set_EnableMonitor(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isEnable);
void HDMI21_DDCMON_Rx_Set_ClearMonitor(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isClear);
void HDMI21_DDCMON_Rx_Set_ModeType(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, HDMI21_DDCMON_DDC_SEL_TYPE_T type);
void HDMI21_DDCMON_Rx_Set_InterruptEnable(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT8 bank, bool isEnable);
void HDMI21_DDCMON_Rx_Set_InterruptClear(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT8 bank);

int HDMI21_DDCMON_Rx_Get_Data(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT8 bank, HDMI21_HAL_DDC_HW_UNITDATA_T *pData);
int HDMI21_DDCMON_Rx_Get_ProcessIsr(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

