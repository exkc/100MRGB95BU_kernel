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
 *  @date		2016-05-02
 *  @note		Additional information. 
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#ifdef INCLUDE_KDRV_DE
#define USE_PQE_CLOCK_SOURCE
#endif

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/interrupt.h>

#include "hdmi20_hal_driver.h"
#include "./synopsys_api/hdmi_rx_ctrl.h"
#include "../hdmi20_drv.h" // For debug prints
#include <linux/delay.h>

#include "hdmi20_rx_audio.h"
#include "hdmi20_kapi.h"
#include "hdmi_kapi.h"

#include "hdmi20_rx_port.h"

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

/*----------------------------------------------------------------------------------------
	Static Function Prototype Declarations
----------------------------------------------------------------------------------------*/
static irqreturn_t __HDMI20_HAL_TOP_IRQ_Handler(UINT8 port, int irq, void *dev_id, struct pt_regs *regs);
static void __HDMI20_HAL_Reset_TOP_SyncInfo(UINT8 port);
static void __HDMI20_HAL_Enable_TOP_IRQ(UINT8 port, int bOnOff);
static UINT32 __HDMI20_HAL_Rx_ALED_Read(UINT8 port, UINT32 addr);
static void   __HDMI20_HAL_Rx_ALED_Write(UINT8 port, UINT32 addr, UINT32 data);
static UINT32 __HDMI20_HAL_Rx_TOP_Read(UINT8 port, UINT32 addr);
static void   __HDMI20_HAL_Rx_TOP_Write(UINT8 port, UINT32 addr, UINT32 data);
static UINT32 __HDMI20_HAL_BSP_Read(UINT8 port, UINT16 addr);
static void __HDMI20_HAL_BSP_Write(UINT8 port, UINT16 addr, UINT32 data);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern volatile HDMI20_HAL_RX_DEVICE_DATA gHDMI20RxHandler[HDMI20_NUM_OF_RX_PORTS];
extern volatile HDMI20_DEV_CONTROL_T	gHDMI20RxDevControler[HDMI20__DEV_CONTROL_LIST_MAXNUM];
extern HDMI20_DEV_CONTROL_T	gHDMI20RxDevAudControler[HDMI20__DEV_AUD_CONTROL_LIST_MAXNUM];

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
void HDMI20_HAL_Log_Error(const char *file, int line, const char *fmt, ...)
{
	va_list args;
    char buf[256];

	va_start(args, fmt);
    vsprintf(buf, fmt, args);

    HDMI20_SNPS_ERR(buf, args);

	va_end(args);
}

void HDMI20_HAL_Log_Info(const char *fmt, ...)
{
	va_list args;
    char buf[256];

	va_start(args, fmt);
    vsprintf(buf, fmt, args);

    HDMI20_SNPS(buf, args);

	va_end(args);
}

irqreturn_t HDMI20_HAL_RX0_TOP_IRQ_Handler(int irq, void *dev_id, struct pt_regs *regs)
{
	return __HDMI20_HAL_TOP_IRQ_Handler(HDMI20_HAL_LINK_DEVICE_ID_PORT0, irq, dev_id, regs);
}

irqreturn_t HDMI20_HAL_RX1_TOP_IRQ_Handler(int irq, void *dev_id, struct pt_regs *regs)
{
	return __HDMI20_HAL_TOP_IRQ_Handler(HDMI20_HAL_LINK_DEVICE_ID_PORT1, irq, dev_id, regs);
}

irqreturn_t HDMI20_HAL_RX2_TOP_IRQ_Handler(int irq, void *dev_id, struct pt_regs *regs)
{
	return __HDMI20_HAL_TOP_IRQ_Handler(HDMI20_HAL_LINK_DEVICE_ID_PORT2, irq, dev_id, regs);
}

irqreturn_t HDMI20_HAL_RX3_TOP_IRQ_Handler(int irq, void *dev_id, struct pt_regs *regs)
{
	return __HDMI20_HAL_TOP_IRQ_Handler(HDMI20_HAL_LINK_DEVICE_ID_PORT3, irq, dev_id, regs);
}

UINT32 HDMI20_HAL_Rx_TOP_Read_Port0(UINT32 addr)
{
	return __HDMI20_HAL_Rx_TOP_Read(HDMI20_HAL_LINK_DEVICE_ID_PORT0, addr);
}

UINT32 HDMI20_HAL_Rx_TOP_Read_Port1(UINT32 addr)
{
	return __HDMI20_HAL_Rx_TOP_Read(HDMI20_HAL_LINK_DEVICE_ID_PORT1, addr);
}

UINT32 HDMI20_HAL_Rx_TOP_Read_Port2(UINT32 addr)
{
	return __HDMI20_HAL_Rx_TOP_Read(HDMI20_HAL_LINK_DEVICE_ID_PORT2, addr);
}

UINT32 HDMI20_HAL_Rx_TOP_Read_Port3(UINT32 addr)
{
	return __HDMI20_HAL_Rx_TOP_Read(HDMI20_HAL_LINK_DEVICE_ID_PORT3, addr);
}

void   HDMI20_HAL_Rx_TOP_Write_Port0(UINT32 addr, UINT32 data)
{
	__HDMI20_HAL_Rx_TOP_Write(HDMI20_HAL_LINK_DEVICE_ID_PORT0, addr, data);
}

void   HDMI20_HAL_Rx_TOP_Write_Port1(UINT32 addr, UINT32 data)
{
	__HDMI20_HAL_Rx_TOP_Write(HDMI20_HAL_LINK_DEVICE_ID_PORT1, addr, data);

}

void   HDMI20_HAL_Rx_TOP_Write_Port2(UINT32 addr, UINT32 data)
{
	__HDMI20_HAL_Rx_TOP_Write(HDMI20_HAL_LINK_DEVICE_ID_PORT2, addr, data);

}

void   HDMI20_HAL_Rx_TOP_Write_Port3(UINT32 addr, UINT32 data)
{
	__HDMI20_HAL_Rx_TOP_Write(HDMI20_HAL_LINK_DEVICE_ID_PORT3, addr, data);
}

UINT32 HDMI20_HAL_Rx_ALED_Read_Port0(UINT32 addr)
{
	return __HDMI20_HAL_Rx_ALED_Read(HDMI20_HAL_LINK_DEVICE_ID_PORT0, addr);
}

UINT32 HDMI20_HAL_Rx_ALED_Read_Port1(UINT32 addr)
{
	return __HDMI20_HAL_Rx_ALED_Read(HDMI20_HAL_LINK_DEVICE_ID_PORT1, addr);
}

UINT32 HDMI20_HAL_Rx_ALED_Read_Port2(UINT32 addr)
{
	return __HDMI20_HAL_Rx_ALED_Read(HDMI20_HAL_LINK_DEVICE_ID_PORT2, addr);
}

UINT32 HDMI20_HAL_Rx_ALED_Read_Port3(UINT32 addr)
{
	return __HDMI20_HAL_Rx_ALED_Read(HDMI20_HAL_LINK_DEVICE_ID_PORT3, addr);
}


void   HDMI20_HAL_Rx_ALED_Write_Port0(UINT32 addr, UINT32 data)
{
	__HDMI20_HAL_Rx_ALED_Write(HDMI20_HAL_LINK_DEVICE_ID_PORT0, addr, data);
}

void   HDMI20_HAL_Rx_ALED_Write_Port1(UINT32 addr, UINT32 data)
{
	__HDMI20_HAL_Rx_ALED_Write(HDMI20_HAL_LINK_DEVICE_ID_PORT1, addr, data);
}

void   HDMI20_HAL_Rx_ALED_Write_Port2(UINT32 addr, UINT32 data)
{
	__HDMI20_HAL_Rx_ALED_Write(HDMI20_HAL_LINK_DEVICE_ID_PORT2, addr, data);
}

void   HDMI20_HAL_Rx_ALED_Write_Port3(UINT32 addr, UINT32 data)
{
	__HDMI20_HAL_Rx_ALED_Write(HDMI20_HAL_LINK_DEVICE_ID_PORT3, addr, data);
}

UINT32 HDMI20_HAL_BSP_Read_Port0(UINT16 addr)
{
	return __HDMI20_HAL_BSP_Read(HDMI20_HAL_LINK_DEVICE_ID_PORT0, addr);
}

UINT32 HDMI20_HAL_BSP_Read_Port1(UINT16 addr)
{
	return __HDMI20_HAL_BSP_Read(HDMI20_HAL_LINK_DEVICE_ID_PORT1, addr);
}

UINT32 HDMI20_HAL_BSP_Read_Port2(UINT16 addr)
{
	return __HDMI20_HAL_BSP_Read(HDMI20_HAL_LINK_DEVICE_ID_PORT2, addr);
}

UINT32 HDMI20_HAL_BSP_Read_Port3(UINT16 addr)
{
	return __HDMI20_HAL_BSP_Read(HDMI20_HAL_LINK_DEVICE_ID_PORT3, addr);
}


void HDMI20_HAL_BSP_Write_Port0(UINT16 addr, UINT32 data)
{
	__HDMI20_HAL_BSP_Write(HDMI20_HAL_LINK_DEVICE_ID_PORT0, addr, data);
}

void HDMI20_HAL_BSP_Write_Port1(UINT16 addr, UINT32 data)
{
	__HDMI20_HAL_BSP_Write(HDMI20_HAL_LINK_DEVICE_ID_PORT1, addr, data);
}

void HDMI20_HAL_BSP_Write_Port2(UINT16 addr, UINT32 data)
{
	__HDMI20_HAL_BSP_Write(HDMI20_HAL_LINK_DEVICE_ID_PORT2, addr, data);
}

void HDMI20_HAL_BSP_Write_Port3(UINT16 addr, UINT32 data)
{
	__HDMI20_HAL_BSP_Write(HDMI20_HAL_LINK_DEVICE_ID_PORT3, addr, data);
}

void HDMI20_HAL_RX0_Enable_TOP_IRQ(int bOnOff)
{
	__HDMI20_HAL_Enable_TOP_IRQ(HDMI20_HAL_LINK_DEVICE_ID_PORT0, bOnOff);
}

void HDMI20_HAL_RX1_Enable_TOP_IRQ(int bOnOff)
{
	__HDMI20_HAL_Enable_TOP_IRQ(HDMI20_HAL_LINK_DEVICE_ID_PORT1, bOnOff);
}

void HDMI20_HAL_RX2_Enable_TOP_IRQ(int bOnOff)
{
	__HDMI20_HAL_Enable_TOP_IRQ(HDMI20_HAL_LINK_DEVICE_ID_PORT2, bOnOff);
}

void HDMI20_HAL_RX3_Enable_TOP_IRQ(int bOnOff)
{
	__HDMI20_HAL_Enable_TOP_IRQ(HDMI20_HAL_LINK_DEVICE_ID_PORT3, bOnOff);
}


void HDMI20_HAL_RX0_Reset_TOP_SyncInfo(void)
{
	__HDMI20_HAL_Reset_TOP_SyncInfo(HDMI20_HAL_LINK_DEVICE_ID_PORT0);
}

void HDMI20_HAL_RX1_Reset_TOP_SyncInfo(void)
{
	__HDMI20_HAL_Reset_TOP_SyncInfo(HDMI20_HAL_LINK_DEVICE_ID_PORT1);
}

void HDMI20_HAL_RX2_Reset_TOP_SyncInfo(void)
{
	__HDMI20_HAL_Reset_TOP_SyncInfo(HDMI20_HAL_LINK_DEVICE_ID_PORT2);
}

void HDMI20_HAL_RX3_Reset_TOP_SyncInfo(void)
{
	__HDMI20_HAL_Reset_TOP_SyncInfo(HDMI20_HAL_LINK_DEVICE_ID_PORT3);
}



/*========================================================================================
 Static Function Implementation 
======================================================================================== */

static irqreturn_t __HDMI20_HAL_TOP_IRQ_Handler(UINT8 port, int irq, void *dev_id, struct pt_regs *regs)
{
	int __5vLevel = 0;
	UINT8 knownISRType;

	UINT32 data;
	UINT32 mask = HDMI20_RX_AD_INTR_FLAG_5V_REDGE | HDMI20_RX_AD_INTR_FLAG_5V_FEDGE | HDMI20_RX_AD_INTR_PHY_INFO;
	UINT32 rise_mask = HDMI20_RX_AD_INTR_FLAG_5V_REDGE;
	UINT32 fall_mask = HDMI20_RX_AD_INTR_FLAG_5V_FEDGE;
	UINT32 tcsDoneMask = HDMI20_RX_AD_INTR_PHY_INFO;
	//UINT32 pcdMask = HDMI20_RX_AD_INTR_FLAG_PCD;
	//LX_HDMI_AUDIO_INFO_T	audioData;

	knownISRType = 0;

	#if 0
	if(gHDMI20RxDevAudControler[HDMI20__AUD_IRQ_DISABLE_PCD].value == 0x0){
		mask = mask | HDMI20_RX_AD_INTR_FLAG_PCD;
	}
	#endif

	/* Check IRQ */
	data = __HDMI20_HAL_Rx_TOP_Read(port, HDMI20_RX_AD_INTR_DATA);

	//HDMI20_INTR("TOP ISR[%d] : Status[0x%08x]! \n", port, data);

	/* Disable IRQ */
	__HDMI20_HAL_Enable_TOP_IRQ(port, 0);

	if((data & mask) != 0){

		/* Clear IRQ */
		__HDMI20_HAL_Rx_TOP_Write(port, HDMI20_RX_AD_INTR_CLR, mask);

		if((data & tcsDoneMask) != 0){
			HDMI20_INTR("TOP ISR[%d] : <><><><><><> [TCS Done] <><><><><><> \n", port);
			gHDMI20RxHandler[port].phyTCSDone = 1;
		
			gHDMI20RxHandler[port].tmds_change = 0;
			gHDMI20RxHandler[port].ctrl.stable_cnt = 0;
			
			knownISRType = 1;
			gHDMI20RxHandler[port].ctrl.isr_count[HDMI20_ISR_LINK_TOP_TCSDONE]++;

			if(gHDMI20RxDevControler[HDMI20__LINK_USE_TCS_DONE_APB].value > 0){
				/* Inform HDCP2.2 that video is stable */
				if(gHDMI20RxHandler[port].gWasHDCP22Written > 0){
					HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_RESET_VIDEO, port);
					HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_GOOD_VIDEO, port);
				}
			}
		
		}

		if(((data & rise_mask) != 0)||((data & fall_mask) != 0)){
			HDMI20_HAL_Check5VLevelInfo(port, &__5vLevel, 1);
			gHDMI20RxHandler[port].locking_time = 0;

			knownISRType = 1;
			gHDMI20RxHandler[port].ctrl.isr_count[HDMI20_ISR_LINK_TOP_5V]++;

			if(__5vLevel) {
				HDMI20_INTR("TOP ISR[%d] : <><><><><><> [5V UP] <><><><><><>\n", port);
				//HDMI20_HAL_ConnectCable(port, 1); /* This will be better if Main thread detectes this on its own */
			}
			else{
				HDMI20_INTR("TOP ISR[%d] <><><><><><> [5V DOWN] <><><><><><>\n", port);
				HDMI20_HAL_ConnectCable(port, 0);
			}
		}

		#if 0
		if((data & pcdMask) != 0){
			knownISRType = 1;
			gHDMI20RxHandler[port].ctrl.isr_count[HDMI20_ISR_LINK_TOP_PCPD]++;

			HDMI20_INTR("TOP ISR[%d] : <><><><><><> [Pcd Change] <><><><><><> \n", port);
			gHDMI20RxHandler[port].isAudioTypeChangeIrq = 1;
			if(gHDMI20RxHandler[port].isAudioTypeChangeIrq == 1){
				if((HDMI20_HAL_Rx_IsLocalMuteOn(port) > 0) ||	(gHDMI20RxHandler[port].audio_change == 1) || (gHDMI20RxHandler[port].ctrl.isMute == 1)\
					|| (gHDMI20RxHandler[port].audioStandByCnt < gHDMI20RxDevAudControler[HDMI20__AUD_STANDBY_TIME].value)\
					|| (gHDMI20RxHandler[port].audioStableCnt < gHDMI20RxDevAudControler[HDMI20__AUD_STABLE_TIME].value)\
					|| (gHDMI20RxHandler[port].audioFifoErrMuteCnt < gHDMI20RxDevAudControler[HDMI20__AUD_FIFO_ERR_MUTE_TIME].value)){
					if(gHDMI20RxDevAudControler[HDMI20__AUD_CSD_IRQ_DBG].value != 0x0)HDMI20_AUDIO("Ignore Audio interrupt!! port:%d, AChange:%d, isMute:%d, Mutecnt:%d, I2Scnt:%d, Noaudio:%d \n", port, gHDMI20RxHandler[port].audio_change, gHDMI20RxHandler[port].ctrl.isMute, gHDMI20RxHandler[port].audioStandByCnt, gHDMI20RxHandler[port].audioFifoErrMuteCnt, gHDMI20RxHandler[port].audioStableCnt);
				} else {
					HDMI20_HAL_Rx_Get_AudioType(port, &audioData.audioType);
					if(audioData.audioType != gHDMI20RxHandler[port].audioInfo.audioType){
						gHDMI20RxHandler[port].audioStableCnt = 0;
						gHDMI20RxHandler[port].audioChMapStandByCnt = 0;
						HDMI20_HAL_Rx_Set_AudioMuteControl(port, HDMI20_AUDIO_MUTE);
						gHDMI20RxHandler[port].isAudioMute = HDMI20_AUDIO_MUTE;
						if(gHDMI20RxDevAudControler[HDMI20__AUD_CSD_IRQ_DBG].value != 0x0)HDMI20_AUDIO("Audio interrup - Mute enable!!(audio type : %d -> %d)\n", audioData.audioType, gHDMI20RxHandler[port].audioInfo.audioType);
					}else{
						if(gHDMI20RxDevAudControler[HDMI20__AUD_CSD_IRQ_DBG].value != 0x0)HDMI20_AUDIO("ignore Audio interrup - audio type no change!\n");
					}
				}
				gHDMI20RxHandler[port].isAudioTypeChangeIrq = 0;
			}		
		}
		#endif
	}

	if(knownISRType == 0){
		gHDMI20RxHandler[port].ctrl.isr_count[HDMI20_ISR_LINK_TOP_UNKNOWN]++;
	}

	/* Enable IRQ */
	__HDMI20_HAL_Enable_TOP_IRQ(port, 1);

	return IRQ_HANDLED;
}

static void __HDMI20_HAL_Reset_TOP_SyncInfo(UINT8 port)
{
	__HDMI20_HAL_Rx_TOP_Write(port, HDMI20_RX_AD_INFO_CLR, HDMI20_RX_INFO_CLR_DATA);
}


static void __HDMI20_HAL_Enable_TOP_IRQ(UINT8 port, int bOnOff)
{
	UINT32 data;
	UINT32 mask = HDMI20_RX_AD_INTR_FLAG_5V_REDGE | HDMI20_RX_AD_INTR_FLAG_5V_FEDGE | HDMI20_RX_AD_INTR_PHY_INFO;
	
	#if 0
	if(gHDMI20RxDevAudControler[HDMI20__AUD_IRQ_DISABLE_PCD].value == 0x0){
		mask = mask | HDMI20_RX_AD_INTR_FLAG_PCD;
	}
	#endif

	data = __HDMI20_HAL_Rx_TOP_Read(port, HDMI20_RX_AD_INTR_EN);

	if(bOnOff){
		data |= mask;
		//HDMI20_LINK("HDMI2.0 Port[%d] 5V IRQ Enabled for Mask[0x%08x] \n", port,data);
	}
	else{
		data &= (~mask);
		//HDMI20_LINK("HDMI2.0 Port[%d] 5V IRQ Disabled for Mask[0x%08x] \n", port,data);
	}

	__HDMI20_HAL_Rx_TOP_Write(port, HDMI20_RX_AD_INTR_EN, data);
}


static UINT32 __HDMI20_HAL_Rx_ALED_Read(UINT8 port, UINT32 addr)
{
	UINT32 ret;
	
	if(gHDMI20RxHandler[port].aledmem.pSwAddr != NULL){
		ret = (UINT32)(*((UINT32 *)((uintptr_t)gHDMI20RxHandler[port].aledmem.pSwAddr + (uintptr_t)addr)));
	}
	else{
		HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.\n", __F__, __L__);
		ret = 0;
	}

	return ret;
}

static void   __HDMI20_HAL_Rx_ALED_Write(UINT8 port, UINT32 addr, UINT32 data)
{
	UINT32* dest;

	if(gHDMI20RxHandler[port].aledmem.pSwAddr != NULL){
		dest = 	((UINT32 *)((uintptr_t)gHDMI20RxHandler[port].aledmem.pSwAddr + (uintptr_t)addr));
		//HDMI20_LINK("Writing for Port[%d] : [0x%08x] <= [0x%08x] \n", port, (unsigned int)dest, (unsigned int)data);
		*dest = data;	
	}
	else{
		HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.\n",__F__ , __L__);
	}
}


static UINT32 __HDMI20_HAL_Rx_TOP_Read(UINT8 port, UINT32 addr)
{
	UINT32 ret;
	
	if(gHDMI20RxHandler[port].topmem.pSwAddr != NULL){
		ret = (UINT32)(*((UINT32 *)((uintptr_t)gHDMI20RxHandler[port].topmem.pSwAddr + (uintptr_t)addr)));
	}
	else{
		HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.\n", __F__, __L__);
		ret = 0;
	}

	return ret;
}

static void   __HDMI20_HAL_Rx_TOP_Write(UINT8 port, UINT32 addr, UINT32 data)
{
	UINT32* dest;

	if(gHDMI20RxHandler[port].topmem.pSwAddr != NULL){
		dest = 	((UINT32 *)((uintptr_t)gHDMI20RxHandler[port].topmem.pSwAddr + (uintptr_t)addr));
		//HDMI20_LINK("Writing for Port[%d] : [0x%08x] <= [0x%08x] \n", port, (unsigned int)dest, (unsigned int)data);
		*dest = data;	
	}
	else{
		HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.\n",__F__ , __L__);
	}
}

static UINT32 __HDMI20_HAL_BSP_Read(UINT8 port, UINT16 addr)
{
	UINT32 ret;
	
	if(gHDMI20RxHandler[port].linkmem.pSwAddr != NULL){
		ret = (UINT32)(*((UINT32 *)((uintptr_t)gHDMI20RxHandler[port].linkmem.pSwAddr + (uintptr_t)addr)));
	}
	else{
		HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.\n", __F__, __L__);
		ret = 0;
	}

	return ret;
}

static void __HDMI20_HAL_BSP_Write(UINT8 port, UINT16 addr, UINT32 data)
{
	UINT32* dest;

	if( gHDMI20RxDevControler[HDMI20__DISABLE_SYNOPSYS_BSP_ACCESS].value >0){
		return;
	}

	if(gHDMI20RxHandler[port].linkmem.pSwAddr != NULL){
		dest = 	((UINT32 *)((uintptr_t)gHDMI20RxHandler[port].linkmem.pSwAddr + (uintptr_t)addr));
		*dest = data;	
	}
	else{
		HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.\n",__F__, __L__);
	}
}

