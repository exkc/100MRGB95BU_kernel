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
 *  @author    	Taejun Lee 
 *  @version    1.0
 *  @date       2016-05-02
 *  @note       Additional information.
 */

#ifndef	_HDMI20_RX_AUDIO_PATH_SPDIF_H_
#define	_HDMI20_RX_AUDIO_PATH_SPDIF_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "hdmi20_rx_audio_path_common.h"
#include "base_types.h"


#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/	
#define HDMI20_RX_M17_IRQ_AUDIO				(M17_INTERRUPT_GIC_BASE + 62) 
#define HDMI20_RX_M19_IRQ_AUDIO				(M19A0_INTERRUPT_GIC_BASE + 65) 
#define HDMI20_RX_O18_IRQ_AUDIO				(O18_INTERRUPT_GIC_BASE + 68)

#define HDMI20_RX_M17_AUDIO_REG_ADDRESS		0xC9A00000
#define HDMI20_RX_M17_AUDIO_REG_SIZE		0x300
#define HDMI20_RX_M19_AUDIO_REG_ADDRESS		0xC9A00500
#define HDMI20_RX_M19_AUDIO_REG_SIZE		0x300
#define HDMI20_RX_O18_AUDIO_REG_ADDRESS		0xC9830000
#define HDMI20_RX_O18_AUDIO_REG_SIZE		0x300

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
/* IRQ handler for Audio */
int HDMI20_Rx_Audio_RequestIrq(void);
int HDMI20_Rx_Audio_FreeIrq(void);
irqreturn_t HDMI20_Rx_Audio_IRQ_Handler(int irq, void *dev_id, struct pt_regs *regs);
int HDMI20_Rx_Audio_Path_Irq_Check(void);
int HDMI20_Rx_Audio_Path_Irq_Disable(void);
int HDMI20_Rx_Audio_Path_Irq_Enable(void);
int HDMI20_Rx_Audio_Path_Irq_Clear(void);

int HDMI20_Rx_Audio_Path_Init(void);
int HDMI20_Rx_Audio_Path_SetInthw(UINT8 port);
int HDMI20_Rx_Audio_Path_InthwUnmask(UINT8 port);
int HDMI20_Rx_Audio_Path_GetSPDIFInfo(UINT8 port, HDMI20_AUDIO_REG_DATA *pHdmi20AudioRegData);
int HDMI20_Rx_Audio_Path_SetMute(UINT8 port);
int HDMI20_Rx_Audio_Path_SetUnmute(UINT8 port);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

