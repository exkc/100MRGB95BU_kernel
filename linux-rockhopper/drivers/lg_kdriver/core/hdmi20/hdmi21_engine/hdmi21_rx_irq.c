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
 *  @author		won.hur
 *  @version	1.0 
 *  @date		2019-04-03
 *  @note		Additional information. 
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/interrupt.h>

#include "os_util.h"
#include "hdmi21_hal_driver.h"
#include "hdmi21_rx_irq.h"
#include "hdmi21_rx_snps_isrunit.h"
#include "hdmi21_rx_ddcmon.h"
#include "../hdmi20_drv.h" //For debug prints



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
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/* Number of Max operable ports */
extern int		g_hdmi20_number_of_ports;
/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern HDMI21_HAL_RX_DEVICE_DATA gHDMI21RxHandler[HDMI21_NUM_OF_MAX_PORTS];
extern HDMI20_DEV_CONTROL_T	gHDMI21RxDevVideoControler[HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM];
extern HDMI20_DEV_CONTROL_T	gHDMI21RxDevLinkControler[HDMI21__DEV_LINK_CONTROL_LIST_MAXNUM];
extern HDMI20_DEV_CONTROL_T	gHDMI21RxDevAudioControler[HDMI21__DEV_AUDIO_CONTROL_LIST_MAXNUM];

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
static UINT32 __gTopIrqMaskValue =  (HDMI21_TOP_FIELD_O_REG_HDMI5V_REDGE | HDMI21_TOP_FIELD_O_REG_HDMI5V_FEDGE | HDMI21_TOP_FIELD_O_REG_INTR_PC_EN);


/*----------------------------------------------------------------------------------------
	static function	
----------------------------------------------------------------------------------------*/
//static int __HDMI20_HAL_Rx_ParseEmPacket(UINT8 port, UINT8 *dataPacket);
//static int __HDMI20_HAL_Rx_CheckAllmMode(UINT8 port, UINT8 *dataPacket);

/*----------------------------------------------------------------------------------------
    Implementation
----------------------------------------------------------------------------------------*/
void HDMI21_IRQ_Rx_SetTopIrqMaskVal(UINT32 val)
{
	__gTopIrqMaskValue = val;
}

UINT32 HDMI21_IRQ_Rx_Get_TopIrqMaskVal(void)
{
	return __gTopIrqMaskValue;
}

int HDMI21_IRQ_Rx_RequestTopIrq(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int ret = RET_ERROR;

	if (request_irq(_p->top_irq, (irq_handler_t)_p->irq_top_handler, 0, "HDMI21_TOP", (void *)_p)) {
		ret = RET_ERROR;
	}
	else {
		ret = RET_OK;
	}

	return ret;
}


int HDMI21_IRQ_Rx_RequestLinkIrq(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int ret = RET_ERROR;

	if( request_irq(_p->irq, (irq_handler_t)_p->irq_link_handler, 0, "HDMI21_LINK", (void *)_p)) {
		ret = RET_ERROR;
	}
	else {
		ret = RET_OK;
	}

	return ret;
}



irqreturn_t HDMI21_IRQ_Rx_Link_IRQ_Handler(UINT8 port, int irq, void *dev_id, struct pt_regs *regs)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	int ret = 0;

	/* Get Handler */
	_p = (HDMI21_HAL_RX_DEVICE_DATA *)dev_id;

	/* Defence Code */
	if(dev_id == NULL) {
		HDMI20_ERROR("Fatal Error! Port[%d] : Top IRQ Argument is NULL\n", port);
		return IRQ_HANDLED;
	}

	if(port != _p->port) {
		HDMI20_ERROR("Fatal Error! Top IRQ port miss-match! API[%d]!=Handler[%d]\n", port, _p->port);
		return IRQ_HANDLED;
	}

	/* IRQ Handle */
	ret = HDMI21_ISRUNIT_Rx_ProcessIRQ(_p);
	if(ret < 0) {
		HDMI20_ERROR("Error[%d] : Link IRQ Error[%d]\n", _p->port, ret);
	}

	return IRQ_HANDLED;
}


irqreturn_t HDMI21_IRQ_Rx_Top_IRQ_Handler(UINT8 port, int irq, void *dev_id, struct pt_regs *regs)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	UINT32 data, data0;
	UINT32 knownISRType = 0;
	int __5VLevel = 0;
//	LX_HDMI_AUDIO_INFO_T	adata;
	int _ddcMonRetVal = 0;

	/* Get Handler */
	_p = (HDMI21_HAL_RX_DEVICE_DATA *)dev_id;

	/* Defence Code */
	if(dev_id == NULL) {
		HDMI20_ERROR("Fatal Error! Port[%d] : Top IRQ Argument is NULL\n", port);
		return IRQ_HANDLED;
	}

	if(port != _p->port) {
		HDMI20_ERROR("Fatal Error! Top IRQ port miss-match! API[%d]!=Handler[%d]\n", port, _p->port);
		return IRQ_HANDLED;
	}

	/* Get IRQ Status */
	data = _p->top_read(HDMI21_TOP_REG_AD_INTR_STATUS);
	data0 = data;
	/* Disable IRQ */
	_p->control_top_irq(0);

	HDMI21_LINE_DBG(130, "Top IRQ[%d] : Status[0x%08x]! \n",_p->port, data);
	if(((data & HDMI21_TOP_FIELD_O_REG_HDMI5V_REDGE) != 0)|| ((data & HDMI21_TOP_FIELD_O_REG_HDMI5V_FEDGE) != 0))
	{
		/* Note that rise/fall may both be toggled on a single event */
		if((data & HDMI21_TOP_FIELD_O_REG_HDMI5V_REDGE) != 0){
			HDMI20_INFO("DBG[%d] : TOP IRQ RiseEdge\n", _p->port);
			data &= (~HDMI21_TOP_FIELD_O_REG_HDMI5V_REDGE);
			_p->isr_count0[HDMI21_ISR_TOP_5V_UP]++;
		}
	
		if((data & HDMI21_TOP_FIELD_O_REG_HDMI5V_FEDGE) != 0){
			HDMI20_INFO("DBG[%d] : TOP IRQ FallEdge\n", _p->port);
			data &= (~HDMI21_TOP_FIELD_O_REG_HDMI5V_FEDGE);
			_p->isr_count0[HDMI21_ISR_TOP_5V_DOWN]++;
		}

		/* Function call should be based on actuall 5V level */	
		HDMI21_HAL_Rx_Get_Check5VLevelInfo(_p->port, &__5VLevel, 1);
		
		if(__5VLevel){
			HDMI21_HAL_ConnectCable(_p->port, 1);

		}
		else {
			HDMI21_HAL_ConnectCable(_p->port, 0);
		}
		
		knownISRType = 1;
	}else if((data & HDMI21_TOP_FIELD_O_REG_INTR_PC_EN) != 0)
	{
		/* Note that rise/fall may both be toggled on a single event */
		if((data & HDMI21_TOP_FIELD_O_REG_INTR_PC_EN) != 0){
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0) HDMI20_INFO("DBG[%d] : Pc EN kkkkkkk\n", _p->port);
			data &= (~HDMI21_TOP_FIELD_O_REG_INTR_PC_EN);
			_p->isr_count0[HDMI21_ISR_TOP_PC]++;
		}

		HDMI21_HAL_Rx_Check_CSDIrq(_p->port);
	}
	/* EARC */
	if(HDMI21_ISRUNIT_Rx_ProcessEarcIRQ(_p) > 0) {
		knownISRType = 1;

	}
	/* DDC Mon */
	if(_p->isDdcMonEnabled > 0) {
		_ddcMonRetVal = HDMI21_DDCMON_Rx_Get_ProcessIsr(_p);
		if(_ddcMonRetVal > 0) {
			knownISRType = 1;
		}
	}
	if(knownISRType == 0){
		_p->isr_count0[HDMI21_ISR_TOP_UNKNOWN]++;
		HDMI21_LINE_DBG(207, "TOP ISR[%d] : Warning! Not processed IRQ[0x%08x]\n", _p->port, data);
	}
	
	/* Clear ISR */
	_p->top_write(HDMI21_TOP_REG_AD_INTR_CLR, data0);
	
	/* Enable IRQ */
	_p->control_top_irq(1);
	
	return IRQ_HANDLED;
}



void HDMI21_IRQ_Rx_Enable_Link_IRQ(UINT8 port, int bOnOff)
{

	/* Port Defence Code */
	if(port >= g_hdmi20_number_of_ports){
		return;
	}

	return;
}

void HDMI21_IRQ_Rx_Enable_Top_IRQ(UINT8 port, int bOnOff)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	UINT32 data;

	/* Port Defence Code */
	if(port >= g_hdmi20_number_of_ports){
		return;
	}

	_p = &gHDMI21RxHandler[port];

	//data = _p->top_read(HDMI21_TOP_REG_AD_INTR_EN);

	if(bOnOff){
		data = __gTopIrqMaskValue;

		if(_p->isDdcMonEnabled == 0) {
			HDMI21_LINE_DBG(273, "DBG[%d] : Top IRQ Enabled with Mask[0x%08x].\n", _p->port, data);
		}
	}
	else{
		data = 0;
		if(_p->isDdcMonEnabled == 0) {
			HDMI21_LINE_DBG(273, "DBG[%d] : Top IRQ Disabled.\n",_p->port);
		}

	}

	_p->top_write(HDMI21_TOP_REG_AD_INTR_EN, data);
}
