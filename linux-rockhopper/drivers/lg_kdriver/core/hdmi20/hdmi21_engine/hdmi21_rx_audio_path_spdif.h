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
 *  @date       2019-04-15
 *  @note       Additional information.
 */

#ifndef	_HDMI21_RX_AUDIO_PATH_SPDIF_H_
#define	_HDMI21_RX_AUDIO_PATH_SPDIF_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "hdmi21_rx_audio_path_common.h"
#include "base_types.h"
#include <linux/interrupt.h>


#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/	
#if 0
#define HDMI20_RX_M17_IRQ_AUDIO				(M17_INTERRUPT_GIC_BASE + 62) 
#define HDMI20_RX_M19_IRQ_AUDIO				(M19A0_INTERRUPT_GIC_BASE + 65) 
#define HDMI20_RX_O18_IRQ_AUDIO				(O18_INTERRUPT_GIC_BASE + 68)

#define HDMI20_RX_M17_AUDIO_REG_ADDRESS		0xC9A00000
#define HDMI20_RX_M17_AUDIO_REG_SIZE		0x300
#define HDMI20_RX_M19_AUDIO_REG_ADDRESS		0xC9A00500
#define HDMI20_RX_M19_AUDIO_REG_SIZE		0x300
#define HDMI20_RX_O18_AUDIO_REG_ADDRESS		0xC9830000
#define HDMI20_RX_O18_AUDIO_REG_SIZE		0x300
#endif
#define O20_IRQ_GIC_BASE	32
#define HDMI21_RX_O20_IRQ_AUDIO				(O20_IRQ_GIC_BASE + 65)
#define E60_IRQ_GIC_BASE	32
#define HDMI21_RX_E60_IRQ_AUDIO				(E60_IRQ_GIC_BASE + 61)
#define O22_IRQ_GIC_BASE	32
#define HDMI21_RX_O22_IRQ_AUDIO				(O22_IRQ_GIC_BASE + 61)
#define M23_IRQ_GIC_BASE	32
#define HDMI21_RX_M23_IRQ_AUDIO				(M23_IRQ_GIC_BASE + 63)
#define O24_IRQ_GIC_BASE	32
#define HDMI21_RX_O24_IRQ_AUDIO				(O24_IRQ_GIC_BASE + 124)	// need confirm




#define HDMI21_RX_O20_AUDIO_REG_ADDRESS		0xC9A00000						// need confirm
#define HDMI21_RX_O20_AUDIO_REG_SIZE		0x1F00							// need confirm
#define HDMI21_RX_E60_AUDIO_REG_ADDRESS		0xF2810000						// need confirm
#define HDMI21_RX_E60_AUDIO_REG_SIZE		0x1F00							// need confirm
#define HDMI21_RX_O22_AUDIO_REG_ADDRESS		0xF2100000						// need confirm
#define HDMI21_RX_O22_AUDIO_REG_SIZE		0x1F00							// need confirm
#define HDMI21_RX_M23_AUDIO_REG_ADDRESS		0xF2810000						// need confirm
#define HDMI21_RX_M23_AUDIO_REG_SIZE		0x1F00							// need confirm
#define HDMI21_RX_O24_AUDIO_REG_ADDRESS		0xF2810000						// need confirm
#define HDMI21_RX_O24_AUDIO_REG_SIZE		0x1F00							// need confirm


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
int HDMI21_Rx_Audio_RequestIrq(void);
int HDMI21_Rx_Audio_FreeIrq(void);
irqreturn_t HDMI21_Rx_Audio_IRQ_Handler(int irq, void *dev_id);
irqreturn_t HDMI21_Rx_Audio_IRQ_Thread_Handler(int irq, void *dev_id);

int HDMI21_Rx_Audio_Path_Irq_Check(void);
int HDMI21_Rx_Audio_Path_Irq_Disable(void);
int HDMI21_Rx_Audio_Path_Irq_Enable(void);
int HDMI21_Rx_Audio_Path_Irq_Clear(void);

int HDMI21_Rx_Audio_Path_Init(void);
int HDMI21_Rx_Audio_Path_SetInthw(UINT8 port);
int HDMI21_Rx_Audio_Path_InthwUnmask(UINT8 port);
int HDMI21_Rx_Audio_Path_GetSPDIFInfo(UINT8 port, HDMI21_AUDIO_REG_DATA *pHdmi21AudioRegData);
int HDMI21_Rx_Audio_Path_SetMute(UINT8 port);
int HDMI21_Rx_Audio_Path_SetUnmute(UINT8 port);
int HDMI21_Rx_Audio_Path_PcPdReset(UINT8 port);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

