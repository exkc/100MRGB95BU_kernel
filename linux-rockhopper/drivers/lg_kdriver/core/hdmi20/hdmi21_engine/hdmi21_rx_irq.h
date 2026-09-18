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
 *  @date       2019-04-20
 *  @note       Additional information.
 */

#ifndef	_HDMI21_RX_IRQ_H_
#define	_HDMI21_RX_IRQ_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/

#include "hdmi20_kapi.h"
#include "hdmi_kapi.h"



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


#define HDMI21_TOP_REG_AD_INTR_EN				(0x110)	
#define HDMI21_TOP_FIELD_O_REG_INTR_CHSTS_EN	BIT(12)
#define HDMI21_TOP_FIELD_O_REG_INTR_PC_EN		BIT(11)
#define HDMI21_TOP_FIELD_O_REG_INTR_PD_EN		BIT(10)
#define HDMI21_TOP_FIELD_O_REG_HDMI5V_REDGE		BIT(9)
#define HDMI21_TOP_FIELD_O_REG_HDMI5V_FEDGE		BIT(8)

#define HDMI21_TOP_REG_AD_INTR_CLR				(0x118)

#define HDMI21_TOP_REG_AD_INTR_STATUS			(0x120)


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void HDMI21_IRQ_Rx_SetTopIrqMaskVal(UINT32 val);
UINT32 HDMI21_IRQ_Rx_Get_TopIrqMaskVal(void);
	
int HDMI21_IRQ_Rx_RequestTopIrq(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
int HDMI21_IRQ_Rx_RequestLinkIrq(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
	
/* IRQ handler for LINK : Calls Synopsys API IRQ Handler*/
irqreturn_t HDMI21_IRQ_Rx_Link_IRQ_Handler(UINT8 port, int irq, void *dev_id, struct pt_regs *regs);
irqreturn_t HDMI21_IRQ_Rx_Top_IRQ_Handler(UINT8 port, int irq, void *dev_id, struct pt_regs *regs);

void HDMI21_IRQ_Rx_Enable_Top_IRQ(UINT8 port, int bOnOff);
void HDMI21_IRQ_Rx_Enable_Link_IRQ(UINT8 port, int bOnOff);

/* Integration of DCM GCP packet */
int HDMI20_HAL_UpdateDCMMode(UINT8 port, int clear, int force);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

