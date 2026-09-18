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

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/interrupt.h>

#include "hdmi20_hal_driver.h"
#include "hdmi20_rx_disland.h"
#include "./synopsys_api/hdmi_rx_ctrl.h"
#include "../hdmi20_drv.h" //For debug prints
#include "hdmi20_kapi.h"
#include "hdmi_kapi.h"

#include "os_util.h"

#include "hdmi20_rx_irq.h"
#include "hdmi20_rx_audio.h"
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
	External Variables
----------------------------------------------------------------------------------------*/
extern volatile HDMI20_HAL_RX_DEVICE_DATA gHDMI20RxHandler[HDMI20_NUM_OF_RX_PORTS];
extern volatile HDMI20_DEV_CONTROL_T	gHDMI20RxDevControler[HDMI20__DEV_CONTROL_LIST_MAXNUM];
extern HDMI20_DEV_CONTROL_T	gHDMI20RxDevAudControler[HDMI20__DEV_AUD_CONTROL_LIST_MAXNUM];

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------------------
	static function	
----------------------------------------------------------------------------------------*/
static int __HDMI20_HAL_Rx_ParseEmPacket(UINT8 port, UINT8 *dataPacket);
static int __HDMI20_HAL_Rx_CheckAllmMode(UINT8 port, UINT8 *dataPacket);

/*----------------------------------------------------------------------------------------
    Implementation
	----------------------------------------------------------------------------------------*/
int HDMI20_HAL_RequestIrq(UINT8 port)
{
	int ret = RET_ERROR;

	ret = request_irq(gHDMI20RxHandler[port].irq, (irq_handler_t)HDMI20_HAL_RX_Link_IRQ_Handler, 0, "HDMI20_LINK", (void *)&gHDMI20RxHandler[port].ctrl.device_id);

	return ret;
}



irqreturn_t HDMI20_HAL_RX_Link_IRQ_Handler(int irq, void *dev_id, struct pt_regs *regs)
{
	int ret = 0;

	if ( dev_id == 0){
		HDMI20_INTR("ISR : RX[0x%p] NULL parmeter\n", (void *)dev_id );
		return -1;
	}

	ret = hdmi_rx_ctrl_irq_handler((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[(int)*((int *)((void *)dev_id))].ctrl);
	if( ret < 0) {
		if (ret != -EPERM)
		{
			HDMI20_INTR("ISR : RX[%d] Link driver ISR error\n", (int)*((int *)((void *)dev_id)));
		}
	}

	return IRQ_HANDLED;
}



/* List up every IRQ handlers in this file to Synopsys API event handler */
int HDMI20_HAL_Register_IRQ_to_handler(UINT8 port)
{
	int ret = RET_ERROR;

	do{
		/* List up to subscribe */
		/* TMDS refresher to IRQ */
		ret = hdmi_rx_ctrl_subscribe((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, hdmi_rx_ctrl_event_clock_change, HDMI20_HAL_Refresh_TMDS);
		if( ret <0 ) { HDMI20_ERROR("Error listing port[%d] TMDS Refresher\n", port);}
		/* VIDEO refresher to IRQ */
		ret = hdmi_rx_ctrl_subscribe((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, hdmi_rx_ctrl_event_video_status, HDMI20_HAL_Refresh_Video);
		if( ret <0 ) { HDMI20_ERROR("Error listing port[%d] VIDEO Refresher\n", port);}
		/* Audio Refresher to IRQ */
		ret = hdmi_rx_ctrl_subscribe((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, hdmi_rx_ctrl_event_audio_status, HDMI20_HAL_Refresh_Audio_CheckSum);
		if( ret <0 ) { HDMI20_ERROR("Error listing port[%d] AUDIO Refresher\n", port);}
		/* Audio Refresher to IRQ */
		ret = hdmi_rx_ctrl_subscribe((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, hdmi_rx_ctrl_event_audio_status2, HDMI20_HAL_Refresh_Audio_Type);
		if( ret <0 ) { HDMI20_ERROR("Error listing port[%d] AUDIO Refresher\n", port);}
		ret = hdmi_rx_ctrl_subscribe((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, hdmi_rx_ctrl_event_audio_status3, HDMI20_HAL_Refresh_Audio_AcrN);
		if( ret <0 ) { HDMI20_ERROR("Error listing port[%d] AUDIO Refresher\n", port);}
		ret = hdmi_rx_ctrl_subscribe((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, hdmi_rx_ctrl_event_audio_status4, HDMI20_HAL_Refresh_Audio_Amute);
		if( ret <0 ) { HDMI20_ERROR("Error listing port[%d] AUDIO Refresher\n", port);}
		/* Data Packet Refresher to IRQ */
		ret = hdmi_rx_ctrl_subscribe((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, hdmi_rx_ctrl_event_packet_reception, HDMI20_HAL_Refresh_DataPacket);
		if( ret <0 ) { HDMI20_ERROR("Error listing port[%d] Data Packet Refresher\n", port);}
		/* AKSV Refresher to IRQ */
		ret = hdmi_rx_ctrl_subscribe((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, hdmi_rx_ctrl_event_aksv_reception, HDMI20_HAL_Refresh_AKSV);
		if( ret <0 ) { HDMI20_ERROR("Error listing port[%d] AKSV Refresher\n",  port);}
		/* PLL Lock Change Refresher to IRQ */
		ret = hdmi_rx_ctrl_subscribe((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, hdmi_rx_ctrl_event_pll_lock_change, HDMI20_HAL_Refresh_PLLLock);
		if( ret <0 ) { HDMI20_ERROR("Error listing port[%d] PLL Lock Change Refresher\n",  port);}
		/* Phy i2c done  Refresher to IRQ */
		ret = hdmi_rx_ctrl_subscribe((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, hdmi_rx_ctrl_event_phy_i2c_done, HDMI20_HAL_Refresh_PhyI2CDone);
		if( ret <0 ) { HDMI20_ERROR("Error listing port[%d] Phy i2c done Refresher\n",  port);}
		/* Phy i2c nack Refresher to IRQ */
		ret = hdmi_rx_ctrl_subscribe((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, hdmi_rx_ctrl_event_phy_i2c_nack, HDMI20_HAL_Refresh_PhyI2CNack);
		if( ret <0 ) { HDMI20_ERROR("Error listing port[%d] Phy i2c nack Refresher\n",  port);}
		ret = hdmi_rx_ctrl_subscribe((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, hdmi_rx_ctrl_event_dcm_change, HDMI20_HAL_Refresh_DCM);
		if( ret <0 ) { HDMI20_ERROR("Error listing port[%d] DCM Refresher\n",  port);}
		ret = hdmi_rx_ctrl_subscribe((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, hdmi_rx_ctrl_event_avmute_change, HDMI20_HAL_Refresh_AVMute);
		if( ret <0 ) { HDMI20_ERROR("Error listing port[%d] AVMute Refresher\n",  port);}
		ret = hdmi_rx_ctrl_subscribe((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, hdmi_rx_ctrl_event_scdc, HDMI20_HAL_Refresh_SCDC);
		if( ret <0 ) { HDMI20_ERROR("Error listing port[%d] SCDC Refresh\n",  port);}
		ret = hdmi_rx_ctrl_subscribe((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, hdmi_rx_ctrl_event_hdcp22_cap, HDMI20_HAL_Refresh_HDCP22_CAP);
		if( ret <0 ) { HDMI20_ERROR("Error listing port[%d] HDCP22 CAP Refresh\n",  port);}
		ret = hdmi_rx_ctrl_subscribe((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, hdmi_rx_ctrl_event_hdcp22_ncap, HDMI20_HAL_Refresh_HDCP22_NCAP);
		if( ret <0 ) { HDMI20_ERROR("Error listing port[%d] HDCP22 NCAP Refresh\n",  port);}
		ret = hdmi_rx_ctrl_subscribe((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, hdmi_rx_ctrl_event_hdcp22_auth_lost, HDMI20_HAL_Refresh_HDCP22_AUTH_LOST);
		if( ret <0 ) { HDMI20_ERROR("Error listing port[%d] HDCP22 AUTH_LOST Refresh\n",  port);}
		ret = hdmi_rx_ctrl_subscribe((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, hdmi_rx_ctrl_event_hdcp22_auth_ists, HDMI20_HAL_Refresh_HDCP22_AUTH_ISTS);
		if( ret <0 ) { HDMI20_ERROR("Error listing port[%d] HDCP22 AUTH_ISTS Refresh\n",  port);}
		ret = hdmi_rx_ctrl_subscribe((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, hdmi_rx_ctrl_event_hdcp22_auth_fail, HDMI20_HAL_Refresh_HDCP22_AUTH_FAIL);
		if( ret <0 ) { HDMI20_ERROR("Error listing port[%d] HDCP22 AUTH_FAIL Refresh\n",  port);}
		ret = hdmi_rx_ctrl_subscribe((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, hdmi_rx_ctrl_event_hdcp22_auth_change, HDMI20_HAL_Refresh_HDCP22_AUTH_CHANGE);
		if( ret <0 ) { HDMI20_ERROR("Error listing port[%d] HDCP22 AUTH_CHANGE Refresh\n",  port);}
		ret = hdmi_rx_ctrl_subscribe((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[port].ctrl, hdmi_rx_ctrl_event_hdcp22_auth_change, HDMI20_HAL_Refresh_HDCP22_AUTH_CHANGE);
		if( ret <0 ) { HDMI20_ERROR("Error listing port[%d] HDCP22 AUTH_CHANGE Refresh\n",  port);}

	}while(0);

	return ret;
}


/* This function is call on IRQ only when Deep Color Mode information has been changed */
int HDMI20_HAL_Refresh_AVMute(struct hdmi_rx_ctrl *ctx)
{
	int ret = RET_OK;

	do{
		/* Step 1. Check pointer */
		if(ctx == 0){
			break;
		}

		if(gHDMI20RxHandler[ctx->device_id].ctrl.isMute == 1){
			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 628) HDMI20_INTR("--NOTICE [%d] : Set AV Mute--\n", ctx->device_id);
			gHDMI20RxHandler[ctx->device_id].avmute_on_time = jiffies_to_msecs(jiffies);
		}
		else{
			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 628)	HDMI20_INTR("--NOTICE [%d] : Clear AV Mute--\n", ctx->device_id);
			//gHDMI20RxHandler[ctx->device_id].avmute_on_time = jiffies_to_msecs(jiffies);
			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value != 734) gHDMI20RxHandler[ctx->device_id].ctrl.isMute = 0;
		}

	} while(0);

	return ret;
}

int HDMI20_HAL_Refresh_HDCP22_CAP(struct hdmi_rx_ctrl *ctx)
{
	int ret = RET_OK;

	do{
		/* Step 1. Check pointer */
		if(ctx == 0){
			break;
		}

		HDMI20_INTR("HDCP2.2 ISR [%d] : HDCP2.2 Capable!!! \n", ctx->device_id);

		if(gHDMI20RxDevControler[HDMI20__VIDEOCON_DETECT_THRES].value > 0){
			if(gHDMI20RxHandler[ctx->device_id].isHDCP22Ncap > 0){

				if(gHDMI20RxHandler[ctx->device_id].ctrl.stable_cnt > gHDMI20RxDevControler[HDMI20__STABLE_CHECK_CNT].value){
					HDMI20_INTR("ISR [%d] : Simultaenous HDCP1.4/HDCP2.2 activity on stable CNT\n", ctx->device_id);

					gHDMI20RxHandler[ctx->device_id].videoConDetectCnt++;
				}

				if(gHDMI20RxHandler[ctx->device_id].videoConDetectCnt > gHDMI20RxDevControler[HDMI20__VIDEOCON_DETECT_THRES].value){
					HDMI20_INTR("ISR [%d] : Detect over 5 of VideoCon Detection. IPC to ESM\n", ctx->device_id);

					HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_HDCP22_VIDEOCON, ctx->device_id);
				}
			}
		}

	} while(0);

	return ret;
}

int HDMI20_HAL_Refresh_HDCP22_NCAP(struct hdmi_rx_ctrl *ctx)
{
	int ret = RET_OK;

	do{
		/* Step 1. Check pointer */
		if(ctx == 0){
			break;
		}

		gHDMI20RxHandler[ctx->device_id].isHDCP22Ncap = 1;

		HDMI20_PRINT("HDCP2.2 ISR [%d] : HDCP2.2 NotCapable(HDCP1.4 rcv) TCS[%d][%d][%d]/[%d][%d][%d]/[%d][%d][%d]/[%d][%d][%d]. SCDC[%d]\n",\
				ctx->device_id, gHDMI20RxHandler[ctx->device_id].phyTCSMin[0], gHDMI20RxHandler[ctx->device_id].phyTCSMin[1],gHDMI20RxHandler[ctx->device_id].phyTCSMin[2],\
					gHDMI20RxHandler[ctx->device_id].phyTCSMax[0],gHDMI20RxHandler[ctx->device_id].phyTCSMax[1],gHDMI20RxHandler[ctx->device_id].phyTCSMax[2],\
					gHDMI20RxHandler[ctx->device_id].phyTCSResult[0],gHDMI20RxHandler[ctx->device_id].phyTCSResult[1],gHDMI20RxHandler[ctx->device_id].phyTCSResult[2],\
					gHDMI20RxHandler[ctx->device_id].phyTCSError[0],gHDMI20RxHandler[ctx->device_id].phyTCSError[1],gHDMI20RxHandler[ctx->device_id].phyTCSError[2],\
					gHDMI20RxHandler[ctx->device_id].isScdcUD);

	} while(0);

	return ret;
}

int HDMI20_HAL_Refresh_HDCP22_AUTH_LOST(struct hdmi_rx_ctrl *ctx)
{
	int ret = RET_OK;

	do{
		/* Step 1. Check pointer */
		if(ctx == 0){
			break;
		}

		HDMI20_PRINT("HDCP2.2 ISR [%d] : HDCP2.2 Authenticate Lost TCS[%d][%d][%d]/[%d][%d][%d]/[%d][%d][%d]/[%d][%d][%d]. SCDC[%d]\n",\
				ctx->device_id, gHDMI20RxHandler[ctx->device_id].phyTCSMin[0], gHDMI20RxHandler[ctx->device_id].phyTCSMin[1],gHDMI20RxHandler[ctx->device_id].phyTCSMin[2],\
					gHDMI20RxHandler[ctx->device_id].phyTCSMax[0],gHDMI20RxHandler[ctx->device_id].phyTCSMax[1],gHDMI20RxHandler[ctx->device_id].phyTCSMax[2],\
					gHDMI20RxHandler[ctx->device_id].phyTCSResult[0],gHDMI20RxHandler[ctx->device_id].phyTCSResult[1],gHDMI20RxHandler[ctx->device_id].phyTCSResult[2],\
					gHDMI20RxHandler[ctx->device_id].phyTCSError[0],gHDMI20RxHandler[ctx->device_id].phyTCSError[1],gHDMI20RxHandler[ctx->device_id].phyTCSError[2],\
					gHDMI20RxHandler[ctx->device_id].isScdcUD);

		gHDMI20RxHandler[ctx->device_id].hdcp22_ists_change = 1;

	} while(0);

	return ret;
}
int HDMI20_HAL_Refresh_HDCP22_AUTH_ISTS(struct hdmi_rx_ctrl *ctx)
{
	int ret = RET_OK;

	do{
		/* Step 1. Check pointer */
		if(ctx == 0){
			break;
		}

		gHDMI20RxHandler[ctx->device_id].isHDCP22 = true;
		gHDMI20RxHandler[ctx->device_id].isHDCP14 = 0;

		HDMI20_PRINT("HDCP2.2 ISR [%d] : HDCP2.2 Auth Success TCS[%d][%d][%d]/[%d][%d][%d]/[%d][%d][%d]/[%d][%d][%d]. SCDC[%d]\n",\
				ctx->device_id, gHDMI20RxHandler[ctx->device_id].phyTCSMin[0], gHDMI20RxHandler[ctx->device_id].phyTCSMin[1],gHDMI20RxHandler[ctx->device_id].phyTCSMin[2],\
					gHDMI20RxHandler[ctx->device_id].phyTCSMax[0],gHDMI20RxHandler[ctx->device_id].phyTCSMax[1],gHDMI20RxHandler[ctx->device_id].phyTCSMax[2],\
					gHDMI20RxHandler[ctx->device_id].phyTCSResult[0],gHDMI20RxHandler[ctx->device_id].phyTCSResult[1],gHDMI20RxHandler[ctx->device_id].phyTCSResult[2],\
					gHDMI20RxHandler[ctx->device_id].phyTCSError[0],gHDMI20RxHandler[ctx->device_id].phyTCSError[1],gHDMI20RxHandler[ctx->device_id].phyTCSError[2],\
					gHDMI20RxHandler[ctx->device_id].isScdcUD);

		HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_AKEMASK, ctx->device_id);

	} while(0);

	return ret;

}

int HDMI20_HAL_Refresh_HDCP22_AUTH_FAIL(struct hdmi_rx_ctrl *ctx)
{
	int ret = RET_OK;

	do{
		/* Step 1. Check pointer */
		if(ctx == 0){
			break;
		}

		HDMI20_INTR("HDCP2.2 ISR [%d] : HDCP2.2 Authenticate Fail\n", ctx->device_id);
	} while(0);

	return ret;
}

int HDMI20_HAL_Refresh_HDCP22_AUTH_CHANGE(struct hdmi_rx_ctrl *ctx)
{
	int ret = RET_OK;

	do{
		/* Step 1. Check pointer */
		if(ctx == 0){
			break;
		}

		if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 913){
			HDMI20_INTR("HDCP2.2 ISR [%d] : HDCP2.2 Authenticate Change\n", ctx->device_id);
		}

		gHDMI20RxHandler[ctx->device_id].hdcp22_auth_change = 1;

	} while(0);

	return ret;
}


int HDMI20_HAL_Refresh_SCDC(struct hdmi_rx_ctrl *ctx)
{
	int ret = RET_OK;
	UINT32 scdc_value;

	do{
		/* Step 1. Check pointer */
		if(ctx == 0){
			break;
		}

		scdc_value = gHDMI20RxHandler[ctx->device_id].ctrl.bsp_read(0x820);
		scdc_value &= 0x00020000;

		if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value > 0) {
			HDMI20_INTR("SCDC ISR [%d] : SCDC[0x820]=[0x%08x]\n", ctx->device_id, scdc_value);
		}

		if(scdc_value) {
			gHDMI20RxHandler[ctx->device_id].isScdcUD = 1;
		}
		else {
			if(gHDMI20RxHandler[ctx->device_id].isManualSyncMode == 1){
				HDMI20_INTR("SCDC ISR [%d] : Interrupt but on link reset[%d]\n", ctx->device_id, gHDMI20RxHandler[ctx->device_id].isManualSyncMode);
				break;
			}
			gHDMI20RxHandler[ctx->device_id].isScdcUD = 0;
		}

	} while(0);

	return ret;


}

/* This function is call on IRQ only when Deep Color Mode information has been changed */
int HDMI20_HAL_Refresh_DCM(struct hdmi_rx_ctrl *ctx)
{
	int ret = RET_ERROR;
	struct hdmi_rx_ctrl_video v;

	do{


		/* Step 1. Check pointer */
		if(ctx == 0){
			break;
		}

		if(gHDMI20RxHandler[ctx->device_id].initiated == 0){
			HDMI20_ERROR("Device handler was not initiated.\n");
			break;
		}

		if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 911) break;

		if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 913){
			if(gHDMI20RxHandler[ctx->device_id].aksv_change !=0){
				HDMI20_INTR("DBG %d : Disable DCM change on AKSV interrupt\n", ctx->device_id);
				break;
			}
		}

		/* Step 2. Wait for stablization */
		if(gHDMI20RxHandler[ctx->device_id].tmds_change != 0){
			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 628) HDMI20_INTR("DCM ISR [%d] : ISR but, on phy reset\n", ctx->device_id);
			ret = RET_OK;
			break;
		}

		if(gHDMI20RxHandler[ctx->device_id].ctrl.isMute != 0){
			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 628) HDMI20_INTR("DCM ISR [%d] : ISR but, on AVMute\n", ctx->device_id);
			ret = RET_OK;
			break;
		}

		/* Step 3. Get Previous TMDS Clock*/
		ret = hdmi_rx_ctrl_get_video(ctx, &v, gHDMI20RxDevControler[HDMI20__VERBOSE_FOR_ABNORMAL_SYNC].value);

		if(ret < 0) {
			if(ret != -ERANGE)HDMI20_INTR("Error when attempting to achieve video data[%d]\n",  ret);
			ret = RET_ERROR;
			break;
		}

		if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 650){
			HDMI20_INTR("DCM ISR [%d] : ISR but disabled by debugger\n", ctx->device_id);
			break;
		}

		if (ctx->previous_video.deep_color_mode != v.deep_color_mode) {
			if(v.deep_color_mode == 24 || v.deep_color_mode == 30 || v.deep_color_mode == 36 || v.deep_color_mode == 48)
			{
				HDMI20_INTR("DCM ISR [%d] : Deep Color Mode Change ISR[%d]->[%d]\n",  ctx->device_id, ctx->previous_video.deep_color_mode, v.deep_color_mode);
				ctx->previous_video.deep_color_mode = v.deep_color_mode;

				gHDMI20RxHandler[ctx->device_id].dcm_change = true;

				HDMI20_HAL_PutHDMIHostError(ctx->device_id, LX_HDMI20_ERROR_GCP_ERROR, 1);

				HDMI20_HAL_UpdateDCMMode(ctx->device_id, 0, v.deep_color_mode);
				gHDMI20RxHandler[ctx->device_id].dcm_change = false;
			}
		}
		else{
			HDMI20_INTR("DCM ISR [%d] : Deep Color Mode ISR but same as previous[%d]->[%d]\n",  ctx->device_id, ctx->previous_video.deep_color_mode, v.deep_color_mode);
		}

	} while(0);

	return ret;


}


/* This function is call on IRQ only when TMDS CLK information has been changed */
int HDMI20_HAL_Refresh_TMDS(struct hdmi_rx_ctrl *ctx)
{
	int ret = RET_ERROR;
	UINT32 tmds_clk = 0;
	struct hdmi_rx_ctrl_video v;

	do{
		/* Step 1. Check pointer */
		if(ctx == 0){
			break;
		}

		if(gHDMI20RxHandler[ctx->device_id].initiated == 0){
			HDMI20_ERROR("Device handler was not initiated.\n");
			break;
		}

		if(HDMI20_HAL_IsTimingInfoEmpty(ctx->device_id)== 0){
			HDMI20_HAL_UpdateTimingInfo(ctx, 1, __L__);
		}

		/* Step 2. Get TMDS Clock */
		tmds_clk = hdmi_rx_ctrl_get_tmds_clk(ctx);

		if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 628){
			HDMI20_INTR("Port[%d] IRQ on TMDS Clk. TCLK is %d\n", ctx->device_id, tmds_clk);
		}

		if(tmds_clk == 0){
			/* Insert code when TMDS Clock is 0 */
			break;
		}

		if(gHDMI20RxHandler[ctx->device_id].ctrl.isMute != 0){
			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 628) HDMI20_INTR("TMDS ISR [%d] : ISR but, on AVMute\n", ctx->device_id);
			ret = RET_OK;
			break;
		}

		/* Step 4. Get Previous TMDS Clock*/
		ret = hdmi_rx_ctrl_get_video(ctx, &v, gHDMI20RxDevControler[HDMI20__VERBOSE_FOR_ABNORMAL_SYNC].value);

		/* Step 5. Change PHY setting for picture-repeatation only when TMDS CLK changed */
		if(tmds_clk != 0){
			if (((ctx->tmds_clock_old + gHDMI20RxDevControler[HDMI20__TOLERENCE_FOR_TMDS_UPDATE].value) > tmds_clk) && \
					((ctx->tmds_clock_old - gHDMI20RxDevControler[HDMI20__TOLERENCE_FOR_TMDS_UPDATE].value) < tmds_clk)) {
				ret = RET_OK;
				break;
			}
			else{
				//HDMI20_CLOCK("Port[%d] TMDS CLK changed from [%3u.%03uMHz] -> [%3u.%03uMHz]\n", ctx->device_id ,(unsigned int)(ctx->tmds_clock_old / 1000), (unsigned int)(ctx->tmds_clock_old %1000), (unsigned int)(tmds_clk/ 1000), (unsigned int)(tmds_clk % 1000));
				if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1213 ){
					HDMI20_INTR("DBG [%d] : TMDS changed over tolerence [%u] -> [%u]\n", ctx->device_id, (unsigned int)ctx->tmds_clock_old, (unsigned int)tmds_clk);	
				}

				gHDMI20RxHandler[ctx->device_id].tmds_change = true;

				gHDMI20RxHandler[ctx->device_id].stablehdcp14time = 0;
				///* Main thread TMDS_Change detect is slow */
				//gHDMI20RxHandler[ctx->device_id].ctrl.stable_cnt = 0;
			}
			/* Update TMDS Clock information for DEVICE Handler */
			//ret = hdmi_rx_ctrl_get_video(ctx, &v, 0);
			ctx->tmds_clock_old = tmds_clk;

		}

	} while(0);

	return ret;
}

/* This function is only called by IRQ when there is a change in video signal */
int HDMI20_HAL_Refresh_Video(struct hdmi_rx_ctrl *ctx)
{
	int ret = 0;
	int vfreq = 0;
	int prev_vfreq=0;
	struct hdmi_rx_ctrl_video v = {0};

	do{
		/* Step 1. Check Pointer */
		if (ctx == 0)
		{
			ret = RET_ERROR;
			break;
		}

		if(gHDMI20RxHandler[ctx->device_id].initiated == 0){
			HDMI20_ERROR("Device handler was not initiated.\n");
			break;
		}

		/* Step 2. Wait for stablization */
		if(gHDMI20RxHandler[ctx->device_id].tmds_change != 0){
			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 628)HDMI20_INTR("VIDEO ISR [%d] : ISR but, on phy reset\n", ctx->device_id);
			ret = RET_OK;
			break;
		}

		if(gHDMI20RxHandler[ctx->device_id].ctrl.isMute != 0){
			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 628)HDMI20_INTR("VIDEO ISR [%d] : ISR but, on AVMute\n", ctx->device_id);
			ret = RET_OK;
			break;
		}


		/* Step 2-1. Do not consider Video ISR on Force VRR/FVA/FreeSync/GSync mode */
		if(gHDMI20RxDevControler[HDMI20__LINK_AMD_FREESYNC_MODE].value == 2){
			ret = RET_OK;
			break;
		}

		/* Step 2-2. Do not consider Video ISR on VRR/FVA/FreeSync/GSync mode */
		if((gHDMI20RxHandler[ctx->device_id].isFreeSyncMode > 0) && (gHDMI20RxDevControler[HDMI20__LINK_AMD_FREESYNC_MODE].value != 0)){
			ret = RET_OK;	
			break;
		}

		/* Step 3. Get Video sync param */
		ret = hdmi_rx_ctrl_get_video(ctx, &v, gHDMI20RxDevControler[HDMI20__VERBOSE_FOR_ABNORMAL_SYNC].value);
		if(ret < 0) {
			if(ret != -ERANGE)HDMI20_INTR("Error when attempting to achieve video data[%d]\n",  ret);
			ret = RET_ERROR;
			break;
		}

		/* Step 4. If video change, save status & set PHY */
		if ((ret == 0) &&
				(((ctx->previous_video.hactive + 10) < (v.hactive)) ||
				 ((ctx->previous_video.hactive != 0) && ((ctx->previous_video.hactive - 10) > (v.hactive))) ||
				 ((ctx->previous_video.vactive + 5) < (v.vactive)) ||
				 ((ctx->previous_video.vactive != 0) && ((ctx->previous_video.vactive - 5) > (v.vactive))) ||
				 (ctx->previous_video.pixel_repetition != v.pixel_repetition) ||
				 //(ctx->previous_video.deep_color_mode != v.deep_color_mode) ||
				 ((ctx->previous_video.refresh_rate + 3) < (v.refresh_rate)) ||
				 ((ctx->previous_video.refresh_rate != 0) && ((ctx->previous_video.refresh_rate - 3) > (v.refresh_rate))) ||
				 (ctx->previous_video.dvi != v.dvi) ||
				 (ctx->previous_video.video_mode != v.video_mode) ||
				 (ctx->previous_video.interlaced != v.interlaced)
				)
		   )
		{
			HDMI20_HAL_Rx_SetLocalVideoMute(ctx->device_id, 1, 0, __L__);

			if((ctx->previous_video.pixel_clk == 0)||(ctx->previous_video.vtotal == 0)||(ctx->previous_video.htotal)) {
				prev_vfreq = 0;
			}
			else{
				prev_vfreq = (ctx->previous_video.pixel_clk *1000) /( ctx->previous_video.vtotal* ctx->previous_video.htotal);
			}

			if((v.pixel_clk == 0)||(v.vtotal == 0)||(v.htotal == 0)){
				vfreq = 0;
			}
			else{
				vfreq = (v.pixel_clk * 1000 )/(v.vtotal * v.htotal);
			}

			/* Debug print */
			HDMI20_INTR("Video Change.. [%ux%u%c@%uHz: %s, DCM %ub, VIC:%u] -> [%ux%u%c@%uHz: %s, DCM %ub, VIC:%u]\n",\
					ctx->previous_video.hactive, ctx->previous_video.vactive, \
					ctx->previous_video.interlaced? 'i' : 'p',prev_vfreq,\
					ctx->previous_video.dvi? "DVI" : "HDMI",\
					ctx->previous_video.deep_color_mode, ctx->previous_video.video_mode,\
					v.hactive, v.vactive, v.interlaced? 'i' : 'p', vfreq ,\
					v.dvi? "DVI" : "HDMI", v.deep_color_mode, v.video_mode);

			/* Important to clear ManualSYnc value */
			HDMI20_HAL_ClearManualSyncSetting(ctx->device_id);

			gHDMI20RxHandler[ctx->device_id].video_change = true;
		
			if (ctx->previous_video.deep_color_mode != v.deep_color_mode) {
				if(v.deep_color_mode == 24 || v.deep_color_mode == 30 || v.deep_color_mode == 36 || v.deep_color_mode == 48)
				{
					HDMI20_INTR("Video ISR [%d] : Deep Color Mode Change ISR[%d]->[%d]\n",  ctx->device_id, ctx->previous_video.deep_color_mode, v.deep_color_mode);
					ctx->previous_video.deep_color_mode = v.deep_color_mode;

					gHDMI20RxHandler[ctx->device_id].dcm_change = true;

					HDMI20_HAL_UpdateDCMMode(ctx->device_id, 0, v.deep_color_mode);
					gHDMI20RxHandler[ctx->device_id].dcm_change = false;
				}
			}


			gHDMI20RxHandler[ctx->device_id].stablehdcp14time = 0;

			/* Update Device Handler video information */
			ctx->previous_video.dvi = v.dvi;
			ctx->previous_video.pixel_clk = v.pixel_clk;
			ctx->previous_video.refresh_rate = v.refresh_rate;
			ctx->previous_video.interlaced = v.interlaced;
			ctx->previous_video.video_mode = v.video_mode;
			ctx->previous_video.htotal = v.htotal;
			ctx->previous_video.vtotal = v.vtotal;
			ctx->previous_video.hactive = v.hactive;
			ctx->previous_video.vactive  = v.vactive;
			ctx->previous_video.pixel_repetition = v.pixel_repetition;
		}
		else{
			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1105)
			{
				HDMI20_INTR("ISR : No video change or change within torrerence\n");
			}
		}
		ret = RET_OK;
	}while(0);

	return ret;
}


/* This function is only called by IRQ when AUDIO information has been changed */
int HDMI20_HAL_Refresh_Audio_CheckSum(struct hdmi_rx_ctrl *ctx)
{
	int ret = 0;
	//struct hdmi_rx_ctrl_audio a;

	do{
		/* Step 1. Check pointer */
		if (ctx == 0){
			ret = RET_ERROR;
			break;
		}

		if(gHDMI20RxHandler[ctx->device_id].initiated == 0){
			HDMI20_ERROR("Device handler was not initiated.\n");
			break;
		}

		if(gHDMI20RxHandler[ctx->device_id].ctrl.isMute != 0){
			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 628)HDMI20_INTR("VIDEO ISR [%d] : ISR but, on AVMute\n", ctx->device_id);
			ret = RET_OK;
			break;
		}

		/* Step 2. Get Audio info */
		ret = hdmi_rx_ctrl_get_audio(ctx, (struct hdmi_rx_ctrl_audio *)&gHDMI20RxHandler[ctx->device_id].audio);

		if( ret < 0) {
			HDMI20_AUDIO("Error when attemting to achieve AUDIO data[%d]\n", ret);
			ret = RET_ERROR;
			break;
		}

		if((gHDMI20RxDevAudControler[HDMI20__AUD_IGNORE_ERR].value == 0x0)\
		&& (gHDMI20RxDevAudControler[HDMI20__AUD_IGNORE_IRQ].value == 0x0)){
			HDMI20_AUDIO("HDMI[%d] Audio HDMI20_HAL_Refresh_Audio_CheckSum (audio pll:0x%x)\n", ctx->device_id, gHDMI20RxHandler[ctx->device_id].ctrl.bsp_read(HDMI20_RX_AUD_PLL_CTRL));
			gHDMI20RxHandler[ctx->device_id].audio_change = 1;
			HDMI20_HAL_Rx_Set_AudioMuteControl(ctx->device_id, HDMI20_AUDIO_MUTE);
			gHDMI20RxHandler[ctx->device_id].isAudioMute = HDMI20_AUDIO_MUTE;
			gHDMI20RxHandler[ctx->device_id].ctrl.bsp_write(HDMI20_RX_DMI_SW_RST, HDMI20_RX_DMI_SW_RST_AUDIO);
			gHDMI20RxHandler[ctx->device_id].audioStableCnt = 0;
		}	

		ret = RET_OK;
	}while(0);

	return ret;
}

int HDMI20_HAL_Refresh_Audio_Type(struct hdmi_rx_ctrl *ctx)
{
	int ret = 0;
	//struct hdmi_rx_ctrl_audio a;

	do{
		/* Step 1. Check pointer */
		if (ctx == 0){
			ret = RET_ERROR;
			break;
		}

		if(gHDMI20RxHandler[ctx->device_id].initiated == 0){
			HDMI20_ERROR("Device handler was not initiated.\n");
			break;
		}

		if(gHDMI20RxHandler[ctx->device_id].ctrl.isMute != 0){
			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 628)HDMI20_INTR("VIDEO ISR [%d] : ISR but, on AVMute\n", ctx->device_id);
			ret = RET_OK;
			break;
		}

		/* Step 2. Get Audio info */
		ret = hdmi_rx_ctrl_get_audio(ctx,(struct hdmi_rx_ctrl_audio *)&gHDMI20RxHandler[ctx->device_id].audio);

		if( ret < 0) {
			HDMI20_AUDIO("Error when attemting to achieve AUDIO data[%d]\n", ret);
			ret = RET_ERROR;
			break;
		}

		if((gHDMI20RxHandler[ctx->device_id].ctrl.bsp_read(HDMI20_RX_AUD_FIFO_ISTS) > HDMI20_RX_AUD_FIFO_ISTS_PASS)\
			&& (gHDMI20RxHandler[ctx->device_id].audioIrqFifoErrCnt < gHDMI20RxDevAudControler[HDMI20__AUD_IRQ_FIFO_ERR_MAX].value)){
			gHDMI20RxHandler[ctx->device_id].audioIrqFifoErrCnt++;
			HDMI20_AUDIO("HDMI[%d] Audio type change interrupt with FIFO err.(cnt:%d)\n", ctx->device_id, gHDMI20RxHandler[ctx->device_id].audioIrqFifoErrCnt);
		}

		if(((gHDMI20RxHandler[ctx->device_id].audioIrqFifoErrCnt < gHDMI20RxDevAudControler[HDMI20__AUD_IRQ_FIFO_ERR_MAX].value)\
			|| (gHDMI20RxHandler[ctx->device_id].ctrl.bsp_read(HDMI20_RX_AUD_FIFO_ISTS) == HDMI20_RX_AUD_FIFO_ISTS_PASS))\
			&& (gHDMI20RxDevAudControler[HDMI20__AUD_IGNORE_ERR].value == 0x0)\
			&& (gHDMI20RxDevAudControler[HDMI20__AUD_IGNORE_IRQ].value == 0x0)){
			if(gHDMI20RxDevAudControler[HDMI20__AUD_IRQ_DBG].value != 0x0)HDMI20_AUDIO("HDMI[%d] Audio HDMI20_HAL_Refresh_Audio_Type (audio pll:0x%x)\n", ctx->device_id,gHDMI20RxHandler[ctx->device_id].ctrl.bsp_read(HDMI20_RX_AUD_PLL_CTRL));
			gHDMI20RxHandler[ctx->device_id].audio_change = 1;
			HDMI20_HAL_Rx_Set_AudioMuteControl(ctx->device_id, HDMI20_AUDIO_MUTE);
			gHDMI20RxHandler[ctx->device_id].isAudioMute = HDMI20_AUDIO_MUTE;
			gHDMI20RxHandler[ctx->device_id].ctrl.bsp_write(HDMI20_RX_DMI_SW_RST, HDMI20_RX_DMI_SW_RST_AUDIO);
			gHDMI20RxHandler[ctx->device_id].audioStableCnt = 0;
			if((gHDMI20RxHandler[ctx->device_id].ctrl.bsp_read(HDMI20_RX_PDEC_AUD_STS) == HDMI20_RX_PDEC_AUD_STS_HBR) && (gHDMI20RxHandler[ctx->device_id].isHBRaudio == 0)) {
				gHDMI20RxHandler[ctx->device_id].isHBRaudio = 1;
				HDMI20_AUDIO("[Type change interrupt]HDMI[%d] Audio High Bit Rate Audio start(pdec_aud_sts=0x%x)!\n",ctx->device_id,gHDMI20RxHandler[ctx->device_id].ctrl.bsp_read(HDMI20_RX_PDEC_AUD_STS));
			}else if ((gHDMI20RxHandler[ctx->device_id].ctrl.bsp_read(HDMI20_RX_PDEC_AUD_STS) != HDMI20_RX_PDEC_AUD_STS_HBR) && (gHDMI20RxHandler[ctx->device_id].isHBRaudio == 1)) {
				gHDMI20RxHandler[ctx->device_id].isHBRaudio = 0;
				HDMI20_AUDIO("[Type change interrupt]HDMI[%d] Audio High Bit Rate Audio stop(pdec_aud_sts=0x%x)!\n",ctx->device_id,gHDMI20RxHandler[ctx->device_id].ctrl.bsp_read(HDMI20_RX_PDEC_AUD_STS));
			}
		}	

		ret = RET_OK;
	}while(0);

	return ret;
}

int HDMI20_HAL_Refresh_Audio_AcrN(struct hdmi_rx_ctrl *ctx)
{
	int ret = 0;
	//struct hdmi_rx_ctrl_audio a;

	do{
		/* Step 1. Check pointer */
		if (ctx == 0){
			ret = RET_ERROR;
			break;
		}

		if(gHDMI20RxHandler[ctx->device_id].initiated == 0){
			HDMI20_ERROR("Device handler was not initiated.\n");
			break;
		}

		if(gHDMI20RxHandler[ctx->device_id].ctrl.isMute != 0){
			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 628)HDMI20_INTR("VIDEO ISR [%d] : ISR but, on AVMute\n", ctx->device_id);
			ret = RET_OK;
			break;
		}

		/* Step 2. Get Audio info */
		ret = hdmi_rx_ctrl_get_audio(ctx, (struct hdmi_rx_ctrl_audio *)&gHDMI20RxHandler[ctx->device_id].audio);

		if( ret < 0) {
			HDMI20_AUDIO("Error when attemting to achieve AUDIO data[%d]\n", ret);
			ret = RET_ERROR;
			break;
		}

		if((gHDMI20RxDevAudControler[HDMI20__AUD_IGNORE_ERR].value == 0x0)\
		&& (gHDMI20RxDevAudControler[HDMI20__AUD_IGNORE_IRQ].value == 0x0)){
			if(gHDMI20RxDevAudControler[HDMI20__AUD_IRQ_DBG].value != 0x0)HDMI20_AUDIO("HDMI[%d] Audio HDMI20_HAL_Refresh_Audio_AcrN (audio pll:0x%x)\n", ctx->device_id,gHDMI20RxHandler[ctx->device_id].ctrl.bsp_read(HDMI20_RX_AUD_PLL_CTRL));

			gHDMI20RxHandler[ctx->device_id].audio_change = 1;
			HDMI20_HAL_Rx_Set_AudioMuteControl(ctx->device_id, HDMI20_AUDIO_MUTE);
			gHDMI20RxHandler[ctx->device_id].isAudioMute = HDMI20_AUDIO_MUTE;
			gHDMI20RxHandler[ctx->device_id].ctrl.bsp_write(HDMI20_RX_DMI_SW_RST, HDMI20_RX_DMI_SW_RST_AUDIO);
			gHDMI20RxHandler[ctx->device_id].audioStableCnt = 0;
		}	

		ret = RET_OK;
	}while(0);

	return ret;
}

int HDMI20_HAL_Refresh_Audio_Amute(struct hdmi_rx_ctrl *ctx)
{
	int ret = 0;
	//struct hdmi_rx_ctrl_audio a;

	do{
		/* Step 1. Check pointer */
		if (ctx == 0){
			ret = RET_ERROR;
			break;
		}

		if(gHDMI20RxHandler[ctx->device_id].initiated == 0){
			HDMI20_ERROR("Device handler was not initiated.\n");
			break;
		}

		if(gHDMI20RxHandler[ctx->device_id].ctrl.isMute != 0){
			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 628)HDMI20_INTR("VIDEO ISR [%d] : ISR but, on AVMute\n", ctx->device_id);
			ret = RET_OK;
			break;
		}

		/* Step 2. Get Audio info */
		ret = hdmi_rx_ctrl_get_audio(ctx, (struct hdmi_rx_ctrl_audio *)&gHDMI20RxHandler[ctx->device_id].audio);

		if( ret < 0) {
			HDMI20_AUDIO("Error when attemting to achieve AUDIO data[%d]\n", ret);
			ret = RET_ERROR;
			break;
		}

		if((gHDMI20RxHandler[ctx->device_id].ctrl.bsp_read(HDMI20_RX_AUD_FIFO_ISTS) > HDMI20_RX_AUD_FIFO_ISTS_PASS)\
			&& (gHDMI20RxHandler[ctx->device_id].audioIrqFifoErrCnt < gHDMI20RxDevAudControler[HDMI20__AUD_IRQ_FIFO_ERR_MAX].value)){
			gHDMI20RxHandler[ctx->device_id].audioIrqFifoErrCnt++;
			if(gHDMI20RxDevAudControler[HDMI20__AUD_IRQ_DBG].value != 0x0)HDMI20_AUDIO("HDMI[%d] Audio interrupt with FIFO err.(cnt:%d)\n", ctx->device_id, gHDMI20RxHandler[ctx->device_id].audioIrqFifoErrCnt);
		}

		if(((gHDMI20RxHandler[ctx->device_id].audioIrqFifoErrCnt < gHDMI20RxDevAudControler[HDMI20__AUD_IRQ_FIFO_ERR_MAX].value)\
			|| (gHDMI20RxHandler[ctx->device_id].ctrl.bsp_read(HDMI20_RX_AUD_FIFO_ISTS) == HDMI20_RX_AUD_FIFO_ISTS_PASS))\
			&& (gHDMI20RxDevAudControler[HDMI20__AUD_IGNORE_ERR].value == 0x0)\
			&& (gHDMI20RxDevAudControler[HDMI20__AUD_IGNORE_IRQ].value == 0x0)\
			&& (gHDMI20RxHandler[ctx->device_id].isPC == FALSE)){
			if(gHDMI20RxDevAudControler[HDMI20__AUD_IRQ_DBG].value != 0x0)HDMI20_AUDIO("HDMI[%d] Audio HDMI20_HAL_Refresh_Audio_Amute (audio pll:0x%x)\n", ctx->device_id,gHDMI20RxHandler[ctx->device_id].ctrl.bsp_read(HDMI20_RX_AUD_PLL_CTRL));
			gHDMI20RxHandler[ctx->device_id].audio_change = 1;
			HDMI20_HAL_Rx_Set_AudioMuteControl(ctx->device_id, HDMI20_AUDIO_MUTE);
			gHDMI20RxHandler[ctx->device_id].isAudioMute = HDMI20_AUDIO_MUTE;
			gHDMI20RxHandler[ctx->device_id].ctrl.bsp_write(HDMI20_RX_DMI_SW_RST, HDMI20_RX_DMI_SW_RST_AUDIO);
			gHDMI20RxHandler[ctx->device_id].audioStableCnt = 0;
		}	

		ret = RET_OK;
	}while(0);

	return ret;
}



/* This function is only called by IRQ when DATAPACKET has been changed */
int HDMI20_HAL_Refresh_DataPacket(struct hdmi_rx_ctrl *ctx)
{
	int ret = 0;
	UINT8 data[HDMI20_MAX_DATAPACKET_SIZE] = {0};
	int i;
	int enumtype;
	/* 2020/05/25 */
	UINT8	__vsifHead[3];


	do {
		/* Step 1. Check pointer */
		if (ctx == 0){
			ret = RET_ERROR;
			break;
		}

		if(gHDMI20RxHandler[ctx->device_id].initiated == 0){
			HDMI20_ERROR("Device handler was not initiated.\n");
			break;
		}


		/* Step 2. Get Packet Info */
		ret = hdmi_rx_ctrl_get_packet(ctx, data, sizeof(data));
		if ( ret < 0 ) {
			if(ret != -ENODATA) HDMI20_INTR("Error attempting to achieve Data Packet[%d]\n", ret);
			ret = RET_ERROR;
			break;
		}

		if( ret == 0) {
			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value != 3030){
				if(data[0] == 0x01){
					/* Disable duplicate incoming packets */
					ret = HDMI20_HAL_Packet_Store(ctx, data[0], false);
					if(ret <0) HDMI20_INTR("Error attempting Setting Packet Store option[%d]\n", ret);
				}
			}
		}

		/* Added by won.hur : Save data packets to buffer */
		switch (data[0])
		{
			case 0x01:
				enumtype =  hdmi_rx_ctrl_packet_ACR;
				break;
			case 0x03:
				enumtype =  hdmi_rx_ctrl_packet_GCP;
				break;
			case 0x04:
				enumtype =  hdmi_rx_ctrl_packet_ACP;
				break;
			case 0x05:
				enumtype =  hdmi_rx_ctrl_packet_ISRC1;
				break;
			case 0x06:
				enumtype =  hdmi_rx_ctrl_packet_ISRC2;
				break;
			case 0x0A:
				enumtype =  hdmi_rx_ctrl_packet_GAMUT;
				break;
			case 0x0D:
				enumtype =  hdmi_rx_ctrl_packet_AMP;
				break;
			case 0x7F:
				/* Excpetion that EM packet would not be check-sum filtered in below code.. as this is not a Infoframe */
				enumtype = hdmi_rx_ctrl_packet_cnt;
				__HDMI20_HAL_Rx_ParseEmPacket(ctx->device_id, (UINT8 *)&data);
				break;
			case 0x81:
				enumtype =  hdmi_rx_ctrl_packet_VSI;
				break;
			case 0x82:
				enumtype =  hdmi_rx_ctrl_packet_AVI;
				break;
			case 0x83:
				enumtype =  hdmi_rx_ctrl_packet_SPD;
				break;
			case 0x84:
				enumtype =  hdmi_rx_ctrl_packet_AIF;
				break;
			case 0x85:
				enumtype =  hdmi_rx_ctrl_packet_MPEGS;
				break;
			case 0x86:
				enumtype =  hdmi_rx_ctrl_packet_NTSCVBI;
				break;
			case 0x87:
				enumtype =  hdmi_rx_ctrl_packet_HDR;
				break;
			default:
				enumtype = hdmi_rx_ctrl_packet_cnt;
				if((gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1122)||(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 3030)){
					HDMI20_INTR("Detected Unexpected DataPacket[0x%x] for Link[%d]\n", data[0], (UINT32)ctx->device_id);
				}
				hdmi_rx_ctrl_packet_fifo_rst((struct hdmi_rx_ctrl *)&gHDMI20RxHandler[ctx->device_id].ctrl);
				break;
		}

		if((gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1122)||(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 3030)){
			HDMI20_INTR("Recieved DataPacket[0x%x] for Link[%d]\n", data[0], (UINT32)ctx->device_id);
		}

		if(enumtype < hdmi_rx_ctrl_packet_cnt){
			/* Only Update DataPacket when Data is good */
			//if(HDMI20_HAL_Rx_DataPacketFilter(ctx->device_id, &data) == RET_OK){	//warning
			if(HDMI20_HAL_Rx_DataPacketFilter(ctx->device_id, (UINT8*)&data) == RET_OK){

				if((gHDMI20RxDevControler[HDMI20__DBG_PACKET_TYPE].value != 0)&&(gHDMI20RxDevControler[HDMI20__DBG_PACKET_TYPE].value < hdmi_rx_ctrl_packet_cnt)){
					if(gHDMI20RxDevControler[HDMI20__DBG_PACKET_LOCATION].value < MAX_DATA_PACKET_LENGTH){
						if(gHDMI20RxDevControler[HDMI20__DBG_PACKET_TYPE].value == enumtype){
							if(gHDMI20RxHandler[ctx->device_id].dataPacket[gHDMI20RxDevControler[HDMI20__DBG_PACKET_TYPE].value][gHDMI20RxDevControler[HDMI20__DBG_PACKET_LOCATION].value] !=\
									data[gHDMI20RxDevControler[HDMI20__DBG_PACKET_LOCATION].value]){
								HDMI20_DBG("DBG %d : Data Packet Changed for Type[%d], comparing [%d]th Packet Byte\n",\
										ctx->device_id, gHDMI20RxDevControler[HDMI20__DBG_PACKET_TYPE].value, gHDMI20RxDevControler[HDMI20__DBG_PACKET_LOCATION].value);

								for(i=0;i<3;i++){
									HDMI20_DBG("[HB%02d] - Previous[  0x%02x  ] | Current[  0x%02x  ]\n",\
											i,(UINT8)gHDMI20RxHandler[ctx->device_id].dataPacket[gHDMI20RxDevControler[HDMI20__DBG_PACKET_TYPE].value][i], (UINT8)data[i]);
								}

								for(i=4;i<MAX_DATA_PACKET_LENGTH; i++){
									HDMI20_DBG("[ B%02d] - Previous[  0x%02x  ] | Current[  0x%02x  ]\n",\
											(i-4), (UINT8)gHDMI20RxHandler[ctx->device_id].dataPacket[gHDMI20RxDevControler[HDMI20__DBG_PACKET_TYPE].value][i], (UINT8)data[i]);
								}
							}
						}
					}
				}

				/* Put Parsed data packet into SW DataPacket Stack only when TCS is in done status */
				if(gHDMI20RxHandler[ctx->device_id].isPhyLocked == true){
					for(i=0;i<MAX_DATA_PACKET_LENGTH;i++){
						gHDMI20RxHandler[ctx->device_id].dataPacket[enumtype][i] = data[i];
					}	

					/* ALLM Detection */
					if(enumtype == hdmi_rx_ctrl_packet_VSI) { 

						/* 2020/05/25 : Copy VSI to buffers */
						/* Get Header */
						__vsifHead[0] = gHDMI20RxHandler[ctx->device_id].dataPacket[enumtype][5];
						__vsifHead[1] = gHDMI20RxHandler[ctx->device_id].dataPacket[enumtype][6];
						__vsifHead[2] = gHDMI20RxHandler[ctx->device_id].dataPacket[enumtype][7];

						/* H14B VSIF */
						if((__vsifHead[0] == HDMI20_RX_VSI_TYPE_H14B_OUI_0) \
								&& (__vsifHead[1] == HDMI20_RX_VSI_TYPE_H14B_OUI_1) \
								&& (__vsifHead[2] == HDMI20_RX_VSI_TYPE_H14B_OUI_2)) {
							for(i=0;i<MAX_DATA_PACKET_LENGTH;i++){
								gHDMI20RxHandler[ctx->device_id].dataPacket[hdmi_rx_ctrl_packet_H14VSI][i] = data[i];
							}	

						}
						else if((__vsifHead[0] == HDMI20_RX_VSI_TYPE_HF_OUI_0) \
								&& (__vsifHead[1] == HDMI20_RX_VSI_TYPE_HF_OUI_1) \
								&& (__vsifHead[2] == HDMI20_RX_VSI_TYPE_HF_OUI_2)) {
							for(i=0;i<MAX_DATA_PACKET_LENGTH;i++){
								gHDMI20RxHandler[ctx->device_id].dataPacket[hdmi_rx_ctrl_packet_HFVSI][i] = data[i];
							}	

							__HDMI20_HAL_Rx_CheckAllmMode(ctx->device_id, (UINT8 *)&data); 
						}
						else if((__vsifHead[0] == HDMI20_RX_VSI_TYPE_DOLBY_OUI_0) \
								&& (__vsifHead[1] == HDMI20_RX_VSI_TYPE_DOLBY_OUI_1) \
								&& (__vsifHead[2] == HDMI20_RX_VSI_TYPE_DOLBY_OUI_2)) {
							for(i=0;i<MAX_DATA_PACKET_LENGTH;i++){
								gHDMI20RxHandler[ctx->device_id].dataPacket[hdmi_rx_ctrl_packet_DOLBYVSI][i] = data[i];
							}	
						}
					}

					/* Free Sync Detection */
					if(enumtype == hdmi_rx_ctrl_packet_SPD){
						if(HDMI20_HAL_Rx_IsSpdAmdFreeSync((UINT8*)&data) == RET_OK){
							if((data[10] & 0x07) == 0x07){
								if(gHDMI20RxHandler[ctx->device_id].isFreeSyncMode == 0){
									HDMI20_INTR("ISR [%d] : Detected AMD Freesync SPD [On]. Range[%d] ~ Range[%d]\n",ctx->device_id, (int)data[8], (int)data[9]); 
								}

								gHDMI20RxHandler[ctx->device_id].isFreeSyncMode = 1;
								gHDMI20RxHandler[ctx->device_id].vfreq_min = (UINT16)data[8];
								gHDMI20RxHandler[ctx->device_id].vfreq_max = (UINT16)data[9];
							}
							else{
								if(gHDMI20RxHandler[ctx->device_id].isFreeSyncMode){
									HDMI20_INTR("ISR [%d] : Detected AMD Freesync SPD [Off]\n",ctx->device_id); 
								}

								gHDMI20RxHandler[ctx->device_id].isFreeSyncMode = 0;
							}
						}
					}
				}
				else{
					if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1126){
						HDMI20_INTR("Error %d : Discarded DataPacket[0x%x] for non-PhyLock situation\n",ctx->device_id, data[0]);
					}
				}
			}
			else{
				if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1126){
					HDMI20_INTR("Error %d : Discarded DataPacket[0x%x] for filtering condition\n",ctx->device_id, data[0]);
				}
			}

			HDMI20_HAL_SetCscHdrInfoToVSC(ctx->device_id);

		}
		ret = RET_OK;
	} while(0);

	return ret;
}

/* This function is only called by IRQ when AKSV data has been changed */
int HDMI20_HAL_Refresh_AKSV(struct hdmi_rx_ctrl *ctx)
{
	int ret = 0;

	if(gHDMI20RxHandler[ctx->device_id].initiated == 0){
		HDMI20_ERROR("Device handler was not initiated.\n");
		return RET_ERROR;
	}

	if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1121){
		HDMI20_INTR("AKSV ISR [%d] : Will ignore AKSV interrupt\n", ctx->device_id);
		return RET_OK;
	}

	if(gHDMI20RxHandler[ctx->device_id].phy_stable_cnt < gHDMI20RxDevControler[HDMI20__PHY_STABLE_THRESHOLD].value){
		HDMI20_VIDEO("AKSV ISR [%d] : Stop phy stable checking process. Stable cnt was [%d]\n", ctx->device_id, gHDMI20RxHandler[ctx->device_id].phy_stable_cnt);

		gHDMI20RxHandler[ctx->device_id].phy_stable_cnt = gHDMI20RxDevControler[HDMI20__PHY_STABLE_THRESHOLD].value;
		gHDMI20RxHandler[ctx->device_id].stopedBetweenStablize = true;
	}

	//HDMI20_HAL_Rx_SetLocalVideoMute(ctx->device_id, 1, 1, __L__);

	HDMI20_PRINT("AKSV ISR [%d] : AKSV arrived from TX device! TCS[%d][%d][%d]/[%d][%d][%d]/[%d][%d][%d]/[%d][%d][%d]. SCDC[%d]\n",\
			ctx->device_id, gHDMI20RxHandler[ctx->device_id].phyTCSMin[0], gHDMI20RxHandler[ctx->device_id].phyTCSMin[1],gHDMI20RxHandler[ctx->device_id].phyTCSMin[2],\
					gHDMI20RxHandler[ctx->device_id].phyTCSMax[0],gHDMI20RxHandler[ctx->device_id].phyTCSMax[1],gHDMI20RxHandler[ctx->device_id].phyTCSMax[2],\
					gHDMI20RxHandler[ctx->device_id].phyTCSResult[0],gHDMI20RxHandler[ctx->device_id].phyTCSResult[1],gHDMI20RxHandler[ctx->device_id].phyTCSResult[2],\
					gHDMI20RxHandler[ctx->device_id].phyTCSError[0],gHDMI20RxHandler[ctx->device_id].phyTCSError[1],gHDMI20RxHandler[ctx->device_id].phyTCSError[2],\
					gHDMI20RxHandler[ctx->device_id].isScdcUD);

	gHDMI20RxHandler[ctx->device_id].isHDCP14 = 1;

	HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_HDCP22_NCAP, ctx->device_id);
	if(gHDMI20RxHandler[ctx->device_id].hdcp.repeat > 0){
		HDMI20_INTR("AKSV ISR [%d] : Currently RPRX Mode. IPC for KSV List\n", ctx->device_id);
		HDMI20_HAL_Send_IPC(HDMI20_HAL_IPC_HDCP14_AKSV, ctx->device_id);
	}

	if((gHDMI20RxDevControler[HDMI20__LOCAL_MUTE_HOLD_TIME].value == gHDMI20RxDevControler[HDMI20__LOCAL_MUTE_HOLD_INIT_TIME].value)){
		HDMI20_INTR("AKSV ISR [%d] : Do not update flag due to cable connect condition\n", ctx->device_id);
	}
	else{
		gHDMI20RxHandler[ctx->device_id].aksv_change = 1;
	}

	ret = HDMI20_HAL_Refresh_Video(ctx);

	return ret;
}

int HDMI20_HAL_Refresh_PLLLock(struct hdmi_rx_ctrl *ctx)
{
	int ret = 0;


	if(gHDMI20RxHandler[ctx->device_id].is5Vconnected == 1){
		if(gHDMI20RxHandler[ctx->device_id].ctrl.bsp_read(0x30) & 0x00000001){
			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1123) HDMI20_INTR("PLL ISR [%d] => PLL Lock UP\n",ctx->device_id);
		}
		else{
			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1123) HDMI20_INTR("PLL ISR [%d] => PLL Lock Down\n",ctx->device_id);

			HDMI20_HAL_ClearManualSyncSetting(ctx->device_id);

			if(HDMI20_HAL_Rx_IsLocalMuteOn(ctx->device_id) == 0) {
				HDMI20_HAL_Rx_SetLocalVideoMute(ctx->device_id, 1, 0, __L__);
				
				/* 2016/12/08 : Added this part to fix PSPRO Final Fantasy 15 HDR on off issue */
				gHDMI20RxHandler[ctx->device_id].tmds_change = true;
			}
		}
	}
	return ret;
}


int HDMI20_HAL_Refresh_PhyI2CDone(struct hdmi_rx_ctrl *ctx)
{
	int ret = 0;

	gHDMI20RxHandler[ctx->device_id].i2cDoneSignal++;
	HDMI20_INTR("ISR [%d] => Receieved Phy I2C Done[%d]\n", ctx->device_id, gHDMI20RxHandler[ctx->device_id].i2cDoneSignal);

	return ret;
}

int HDMI20_HAL_Refresh_PhyI2CNack(struct hdmi_rx_ctrl *ctx)
{
	int ret = 0;

	gHDMI20RxHandler[ctx->device_id].i2cNackSignal++;
	HDMI20_INTR("ISR [%d] => Receieved Phy I2C Nack[%d]\n", ctx->device_id,gHDMI20RxHandler[ctx->device_id].i2cNackSignal);

	return ret;
}


int HDMI20_HAL_UpdateDCMMode(UINT8 port, int clear, int force)
{
	int ret = 0;
	int currentDCM = 0;

	if(gHDMI20RxHandler[port].initiated == 0){
		HDMI20_ERROR("Device handler was not initiated.\n");
		return RET_ERROR;
	}


	if(clear){
		HDMI20_PACKET("Notice [%d] : Clear DCM History \n", port);
		gHDMI20RxHandler[port].currentDCMMode = 0x0;

		//if(force >0 )hdmi_rx_ctrl_phy_write(&gHDMI20RxHandler[port].ctrl, 0x69, 0x3, 0x200);
	}
	else if(force > 0){

		if(gHDMI20RxDevControler[HDMI20__DISABLE_DCM_UPDATE_FOR_LINK].value > 0) return 0;

		switch(force)
		{
			case 24:
				currentDCM = 0x0;
				break;
			case 30:
				currentDCM = 0x5;
				break;
			case 36:
				currentDCM = 0x6;
				break;
			case 48:
				currentDCM = 0x7;
				break;
			default:
				currentDCM = force;
				break;
		}


		if(gHDMI20RxHandler[port].currentDCMMode == currentDCM){
			HDMI20_PACKET("Notice [%d] : Force DCM update but, same as previous[0x%x]\n", port, currentDCM);
			return 0;	
		}

		if(currentDCM == 0x5){
			HDMI20_PACKET("Notice [%d] : DCM Mode Changed from [0x%x] to 10 bit mode\n", port, gHDMI20RxHandler[port].currentDCMMode);
			ret = RET_OK;
		}
		else if(currentDCM == 0x6){
			HDMI20_PACKET("Notice [%d] : DCM Mode Changed from [0x%x] to 12 bit mode\n", port, gHDMI20RxHandler[port].currentDCMMode);
			ret = RET_OK;
		}
		else if(currentDCM == 0x7){
			HDMI20_PACKET("Notice [%d] : DCM Mode Changed  from [0x%x] to 16 bit mode\n", port, gHDMI20RxHandler[port].currentDCMMode);
			ret = RET_OK;
		}
		else if((currentDCM == 0x4)||(currentDCM == 0x0)){
			currentDCM = 0;
			HDMI20_PACKET("Notice [%d] : DCM Mode Changed from [0x%x] to 8 Bit mode\n", port, gHDMI20RxHandler[port].currentDCMMode);

			ret = RET_OK;
		}
		else{
			HDMI20_PACKET("Error [%d] : Unknown DCM value[0x%08x]\n", port, currentDCM);
			ret = RET_ERROR;
		}


		if(ret == RET_OK){
			gHDMI20RxHandler[port].currentDCMMode = currentDCM;
		}
	}

	return ret;
}


static int __HDMI20_HAL_Rx_ParseEmPacket(UINT8 port, UINT8 *dataPacket)
{
	int ret = RET_ERROR;
	int i;
	UINT8 data[HDMI20_MAX_DATAPACKET_SIZE] = {0};

	do{
		/* Check Port */
		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Check Pointer */
		if(dataPacket == NULL){
			HDMI20_ERROR("Error! Parse EM Packet Null Pointer. Port[%d]\n",port);
			break;
		}

		/* For Debug Purpose. Print EM Packet */
		if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1127){
			for(i=0;i<3;i++){
				HDMI20_DBG("[HB%02d] - [  0x%02x  ]\n",i, (UINT8)dataPacket[i]);
			}

			for(i=4;i<HDMI20_MAX_DATAPACKET_SIZE; i++){
				HDMI20_DBG("[ B%02d] - [  0x%02x  ]\n",(i-4), (UINT8)dataPacket[i]);
			}
		}

		if(gHDMI20RxHandler[port].isPhyLocked != true){
			/* Put Parsed data packet into SW DataPacket Stack only when TCS is in done status */
			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1130){
				HDMI20_DBG("Error! Would not parse EM Packet when Phy lock is down. Port[%d]\n",port);
			}
			break;
		}

		memcpy((void *)&data, (void *)dataPacket, sizeof(UINT8) * HDMI20_MAX_DATAPACKET_SIZE);

		if(data[1] == 0xC0){
			/* Single EM Packet : VTEM */
			if(data[2] == 0x00){
				/* Check VTEM */
				if(((data[4] & 0x3F) == 0x04) && (data[6] == 0x01) && (data[7] == 0x00) && (data[8] == 0x01) && (data[9] == 0x00) && (data[10] == 0x04)){

					for(i=0;i<MAX_DATA_PACKET_LENGTH;i++){
						gHDMI20RxHandler[port].emp_vtemPacket[i] = data[i];
					}	
					/* VRR Detection */
					if((data[11] & 0x01) == 0x01){
						if(gHDMI20RxHandler[port].isFreeSyncMode == 0){
							HDMI20_INTR("ISR [%d] : Detected VRR Mode[On]. BaseVfront[0x%02x], BaseRate[0x%02x]\n",port, (int)data[12], (int)data[14]); 
						}
						gHDMI20RxHandler[port].isFreeSyncMode = 1;
					}
					else{
						if(gHDMI20RxHandler[port].isFreeSyncMode){
							HDMI20_INTR("ISR [%d] : Detected VRR Mode[Off]\n",port); 
						}
						gHDMI20RxHandler[port].isFreeSyncMode = 0;
					}
				}
				else{
					if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1129){
						HDMI20_DBG("DBG [%d] : Unknown EMP data type. [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x] [0x%02x] \n", port,\
								(data[4] & 0x3F), data[6], data[7], data[8], data[9], data[10]);
					}
				}
			}
			else{
				/* Would be weird to have this as non zero, as these are single packets */
				if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1129){
					HDMI20_DBG("DBG [%d] : Abnormal EMP Header\n", port);
				}
			}
		}
		else{
			/* Multiple EM Packet :  Not Supported Yet */
	
			/* For Debug Purpose. Print EM Packet */
			if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1128){
				for(i=0;i<3;i++){
					HDMI20_DBG("[HB%02d] - [  0x%02x  ]\n",i, (UINT8)data[i]);
				}

				for(i=4;i<HDMI20_MAX_DATAPACKET_SIZE; i++){
					HDMI20_DBG("[ B%02d] - [  0x%02x  ]\n",(i-4), (UINT8)data[i]);
				}
			}
		}

		ret = RET_OK;
	} while(0);

	return ret;
}


static int __HDMI20_HAL_Rx_CheckAllmMode(UINT8 port, UINT8 *dataPacket)
{
	int ret = RET_ERROR;
	int i;
	UINT8 data[HDMI20_MAX_DATAPACKET_SIZE] = {0};

	do{
		/* Check Port */
		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Check Pointer */
		if(dataPacket == NULL){
			HDMI20_ERROR("Error! Parse EM Packet Null Pointer. Port[%d]\n",port);
			break;
		}

		/* For Debug Purpose. Print Packet */
		if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == 1127){
			for(i=0;i<3;i++){
				HDMI20_DBG("[HB%02d] - [  0x%02x  ]\n",i, (UINT8)dataPacket[i]);
			}

			for(i=4;i<HDMI20_MAX_DATAPACKET_SIZE; i++){
				HDMI20_DBG("[ B%02d] - [  0x%02x  ]\n",(i-4), (UINT8)dataPacket[i]);
			}
		}

		if(gHDMI20RxHandler[port].isPhyLocked != true){
			/* Put Parsed data packet into SW DataPacket Stack only when TCS is in done status */
			HDMI20_ERROR("Error! Would not parse VSI Packet when Phy lock is down. Port[%d]\n",port);
			break;
		}

		memcpy((void *)&data, (void *)dataPacket, sizeof(UINT8) * HDMI20_MAX_DATAPACKET_SIZE);

		if((data[5] == 0xD8) && (data[6] == 0x5D) && (data[7] == 0xC4)){

			if(data[8] == 0x01){
				if((data[9] & 0x02) == 0x02) {
					if(gHDMI20RxHandler[port].isAllmMode == 0){
						HDMI20_INTR("ISR [%d] : Detected ALLM Mode[On].\n",port); 
					}
					gHDMI20RxHandler[port].isAllmMode = 1;
					gHDMI20RxHandler[port].allm_recieve_time = jiffies_to_msecs(jiffies);
				}
				else{
					if(gHDMI20RxHandler[port].isAllmMode == 1){
						HDMI20_INTR("ISR [%d] : Detected ALLM Mode[Off]\n",port); 
					}
					gHDMI20RxHandler[port].isAllmMode = 0;
					gHDMI20RxHandler[port].allm_recieve_time = 0;
				}
			}
		}
		else{
			/* Not a HF-VSIF */
		}

		ret = RET_OK;
	} while(0);

	return ret;
}
