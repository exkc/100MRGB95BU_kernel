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

#ifndef	_HDMI20_RX_IRQ_H_
#define	_HDMI20_RX_IRQ_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "./synopsys_api/hdmi_rx_ctrl.h"
#include "./synopsys_api/hdmi_rx_ctrl_hdcp.h"


#include "hdmi20_kapi.h"
#include "hdmi_kapi.h"



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
/* list up IRQ functions to Synopsys Event Handlers */
int HDMI20_HAL_Register_IRQ_to_handler(UINT8 port);
	
/* IRQ handler for LINK : Calls Synopsys API IRQ Handler*/
int HDMI20_HAL_RequestIrq(UINT8 port);
irqreturn_t HDMI20_HAL_RX_Link_IRQ_Handler(int irq, void *dev_id, struct pt_regs *regs);

/* Integration of DCM GCP packet */
int HDMI20_HAL_UpdateDCMMode(UINT8 port, int clear, int force);

/* Interrupt Service Routine : Called by Synopsys API IRQ handler */
int HDMI20_HAL_Refresh_TMDS(struct hdmi_rx_ctrl *ctx);
int HDMI20_HAL_Refresh_AVMute(struct hdmi_rx_ctrl *ctx);
int HDMI20_HAL_Refresh_Video(struct hdmi_rx_ctrl *ctx);
int HDMI20_HAL_Refresh_Audio_CheckSum(struct hdmi_rx_ctrl *ctx);
int HDMI20_HAL_Refresh_Audio_Type(struct hdmi_rx_ctrl *ctx);
int HDMI20_HAL_Refresh_Audio_AcrN(struct hdmi_rx_ctrl *ctx);
int HDMI20_HAL_Refresh_Audio_Amute(struct hdmi_rx_ctrl *ctx);
int HDMI20_HAL_Refresh_DataPacket(struct hdmi_rx_ctrl *ctx);
int HDMI20_HAL_Refresh_AKSV(struct hdmi_rx_ctrl *ctx);
int HDMI20_HAL_Refresh_PLLLock(struct hdmi_rx_ctrl *ctx);
int HDMI20_HAL_Refresh_PhyI2CDone(struct hdmi_rx_ctrl *ctx);
int HDMI20_HAL_Refresh_PhyI2CNack(struct hdmi_rx_ctrl *ctx);
int HDMI20_HAL_Refresh_DCM(struct hdmi_rx_ctrl *ctx);
int HDMI20_HAL_Refresh_SCDC(struct hdmi_rx_ctrl *ctx);
int HDMI20_HAL_Refresh_HDCP22_CAP(struct hdmi_rx_ctrl *ctx);
int HDMI20_HAL_Refresh_HDCP22_NCAP(struct hdmi_rx_ctrl *ctx);
int HDMI20_HAL_Refresh_HDCP22_AUTH_LOST(struct hdmi_rx_ctrl *ctx);
int HDMI20_HAL_Refresh_HDCP22_AUTH_ISTS(struct hdmi_rx_ctrl *ctx);
int HDMI20_HAL_Refresh_HDCP22_AUTH_FAIL(struct hdmi_rx_ctrl *ctx);
int HDMI20_HAL_Refresh_HDCP22_AUTH_CHANGE(struct hdmi_rx_ctrl *ctx);


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

