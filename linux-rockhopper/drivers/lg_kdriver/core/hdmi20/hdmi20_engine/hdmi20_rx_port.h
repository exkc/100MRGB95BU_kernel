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
 *  @date       2016-05-02
 *  @note       Additional information.
 */

#ifndef	_HDMI20_RX_PORT0_H_
#define	_HDMI20_RX_PORT0_H_

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

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void HDMI20_HAL_Log_Error(const char *file, int line, const char *fmt, ...);
void HDMI20_HAL_Log_Info(const char *fmt, ...);
	
/* IRQ handler for 5V detector */
irqreturn_t HDMI20_HAL_RX0_TOP_IRQ_Handler(int irq, void *dev_id, struct pt_regs *regs);
irqreturn_t HDMI20_HAL_RX1_TOP_IRQ_Handler(int irq, void *dev_id, struct pt_regs *regs);
irqreturn_t HDMI20_HAL_RX2_TOP_IRQ_Handler(int irq, void *dev_id, struct pt_regs *regs);
irqreturn_t HDMI20_HAL_RX3_TOP_IRQ_Handler(int irq, void *dev_id, struct pt_regs *regs);


/* TOP ctrl read/write reg */
UINT32 HDMI20_HAL_Rx_TOP_Read_Port0(UINT32 addr);
UINT32 HDMI20_HAL_Rx_TOP_Read_Port1(UINT32 addr);
UINT32 HDMI20_HAL_Rx_TOP_Read_Port2(UINT32 addr);
UINT32 HDMI20_HAL_Rx_TOP_Read_Port3(UINT32 addr);

void   HDMI20_HAL_Rx_TOP_Write_Port0(UINT32 addr, UINT32 data);
void   HDMI20_HAL_Rx_TOP_Write_Port1(UINT32 addr, UINT32 data);
void   HDMI20_HAL_Rx_TOP_Write_Port2(UINT32 addr, UINT32 data);
void   HDMI20_HAL_Rx_TOP_Write_Port3(UINT32 addr, UINT32 data);

/* Always On EDID read/write/reg */
UINT32 HDMI20_HAL_Rx_ALED_Read_Port0(UINT32 addr);
UINT32 HDMI20_HAL_Rx_ALED_Read_Port1(UINT32 addr);
UINT32 HDMI20_HAL_Rx_ALED_Read_Port2(UINT32 addr);
UINT32 HDMI20_HAL_Rx_ALED_Read_Port3(UINT32 addr);

void   HDMI20_HAL_Rx_ALED_Write_Port0(UINT32 addr, UINT32 data);
void   HDMI20_HAL_Rx_ALED_Write_Port1(UINT32 addr, UINT32 data);
void   HDMI20_HAL_Rx_ALED_Write_Port2(UINT32 addr, UINT32 data);
void   HDMI20_HAL_Rx_ALED_Write_Port3(UINT32 addr, UINT32 data);


/* Link CTRL read/write reg */
UINT32 HDMI20_HAL_BSP_Read_Port0(UINT16 addr);
UINT32 HDMI20_HAL_BSP_Read_Port1(UINT16 addr);
UINT32 HDMI20_HAL_BSP_Read_Port2(UINT16 addr);
UINT32 HDMI20_HAL_BSP_Read_Port3(UINT16 addr);

void HDMI20_HAL_BSP_Write_Port0(UINT16 addr, UINT32 data);
void HDMI20_HAL_BSP_Write_Port1(UINT16 addr, UINT32 data);
void HDMI20_HAL_BSP_Write_Port2(UINT16 addr, UINT32 data);
void HDMI20_HAL_BSP_Write_Port3(UINT16 addr, UINT32 data);


void HDMI20_HAL_RX0_Enable_TOP_IRQ(int bOnOff);
void HDMI20_HAL_RX1_Enable_TOP_IRQ(int bOnOff);
void HDMI20_HAL_RX2_Enable_TOP_IRQ(int bOnOff);
void HDMI20_HAL_RX3_Enable_TOP_IRQ(int bOnOff);

void HDMI20_HAL_RX0_Reset_TOP_SyncInfo(void);
void HDMI20_HAL_RX1_Reset_TOP_SyncInfo(void);
void HDMI20_HAL_RX2_Reset_TOP_SyncInfo(void);
void HDMI20_HAL_RX3_Reset_TOP_SyncInfo(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

