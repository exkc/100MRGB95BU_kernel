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
 *  @author		taejun.lee
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
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/io.h>

#include "base/os_util.h"

#include "hdmi20_rx_audio_path_spdif.h"
#include "hdmi20_hal_driver.h"
#include "hdmi20_rx_audio.h"
#include "../hdmi20_drv.h"
#include "hdmi_kapi.h"

#include <linux/interrupt.h>

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
//#define SPDIF_IRQ_ENABLE 1
/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern HDMI20_HAL_RX_DEVICE_DATA gHDMI20RxHandler[HDMI20_NUM_OF_RX_PORTS];
extern HDMI20_DEV_CONTROL_T	gHDMI20RxDevAudControler[HDMI20__DEV_CONTROL_LIST_MAXNUM];
/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int g_HDMI20_AudIrq = 0;
/*----------------------------------------------------------------------------------------
	Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int __HDMI20_Rx_Audio_Path_irq_UpdateClear (void);
/*----------------------------------------------------------------------------------------
	Variables
----------------------------------------------------------------------------------------*/
/* define HDMI AUDIO register */
static volatile HDMI20_RX_AUD_REG_T *g_pRealHDMI20AudioReg = NULL;
static HDMI20_RX_AUD_REG_T *g_pTempHDMI20AudioReg = NULL;
/*========================================================================================
	Implementation Group
========================================================================================*/
int HDMI20_Rx_Audio_RequestIrq(void)
{
	int ret = RET_ERROR;

	if(gHDMI20RxDevAudControler[HDMI20__AUD_IRQ_DISABLE_SPDIF].value == (UINT32)0x0){
		if ( lx_chip_rev( ) >= LX_CHIP_REV( M19, A0) ){
			ret = request_irq((UINT32)HDMI20_RX_M19_IRQ_AUDIO, (irq_handler_t)HDMI20_Rx_Audio_IRQ_Handler, (UINT64)0, "HDMI20_AUDIO",&g_HDMI20_AudIrq);
		} else if ( lx_chip_rev( ) >= LX_CHIP_REV( O18, A0) ){
			ret = request_irq((UINT32)HDMI20_RX_O18_IRQ_AUDIO, (irq_handler_t)HDMI20_Rx_Audio_IRQ_Handler, (UINT64)0, "HDMI20_AUDIO",&g_HDMI20_AudIrq);
		} else if ( lx_chip_rev( ) >= LX_CHIP_REV( M17, A0) ){
			ret = request_irq((UINT32)HDMI20_RX_M17_IRQ_AUDIO, (irq_handler_t)HDMI20_Rx_Audio_IRQ_Handler, (UINT64)0, "HDMI20_AUDIO",&g_HDMI20_AudIrq);
		}

		if(gHDMI20RxDevAudControler[HDMI20__AUD_CSD_IRQ_DBG].value != (UINT32)0x0)HDMI20_AUDIO("request Audio interrupt!!(%d)\n", ret);
	}
	return ret;
}

int HDMI20_Rx_Audio_FreeIrq(void)
{
	if(gHDMI20RxDevAudControler[HDMI20__AUD_IRQ_DISABLE_SPDIF].value == (UINT32)0x0){
		if ( lx_chip_rev( ) >= LX_CHIP_REV( M19, A0) ){
			free_irq((UINT32)HDMI20_RX_M19_IRQ_AUDIO, &g_HDMI20_AudIrq);
		} else if ( lx_chip_rev( ) >= LX_CHIP_REV( O18, A0) ){
			free_irq((UINT32)HDMI20_RX_O18_IRQ_AUDIO, &g_HDMI20_AudIrq);
		} else if ( lx_chip_rev( ) >= LX_CHIP_REV( M17, A0) ){
			free_irq((UINT32)HDMI20_RX_M17_IRQ_AUDIO, &g_HDMI20_AudIrq);
		}
	}
	return RET_OK;
}

irqreturn_t HDMI20_Rx_Audio_IRQ_Handler(int irq, void *dev_id, struct pt_regs *regs)
{
	if(gHDMI20RxDevAudControler[HDMI20__AUD_IRQ_DISABLE_SPDIF].value == (UINT32)0x0){
		UINT8 i;
		LX_HDMI_AUDIO_INFO_T	data;

		if ( dev_id == 0){
			HDMI20_INTR("ISR : RX[%d] NULL parmeter\n", (int)dev_id );
			return -1;
		}

		//HDMI20_AUDIO("Audio interrupt!!\n");

		/* Check IRQ */
		HDMI20_Rx_Audio_Path_Irq_Check();

		/* Disable IRQ */
		HDMI20_Rx_Audio_Path_Irq_Disable();

		/* Clear IRQ */
		HDMI20_Rx_Audio_Path_Irq_Clear();

		if(gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value != (UINT32)0x700){
			for(i=0;i<HDMI20_NUM_OF_RX_PORTS;i++){
				if(gHDMI20RxHandler[i].isAudioTypeChangeIrq == TRUE){
					if((HDMI20_HAL_Rx_IsLocalMuteOn(i) > 0) ||	(gHDMI20RxHandler[i].audio_change == TRUE) || (gHDMI20RxHandler[i].ctrl.isMute == 1)\
						|| (gHDMI20RxHandler[i].audioStandByCnt < gHDMI20RxDevAudControler[HDMI20__AUD_STANDBY_TIME].value)\
						|| (gHDMI20RxHandler[i].audioStableCnt < gHDMI20RxDevAudControler[HDMI20__AUD_STABLE_TIME].value)\
						|| (gHDMI20RxHandler[i].audioFifoErrMuteCnt < gHDMI20RxDevAudControler[HDMI20__AUD_FIFO_ERR_MUTE_TIME].value)){
						if(gHDMI20RxDevAudControler[HDMI20__AUD_CSD_IRQ_DBG].value != (UINT32)0x0)HDMI20_AUDIO("Ignore Audio interrupt!! port:%d, AChange:%d, isMute:%d, Mutecnt:%d, I2Scnt:%d, Noaudio:%d \n", i, gHDMI20RxHandler[i].audio_change, gHDMI20RxHandler[i].ctrl.isMute, gHDMI20RxHandler[i].audioStandByCnt, gHDMI20RxHandler[i].audioFifoErrMuteCnt, gHDMI20RxHandler[i].audioStableCnt);
					} else {
						HDMI20_HAL_Rx_Get_AudioType(i, &data.audioType);
						if(data.audioType != gHDMI20RxHandler[i].audioInfo.audioType){
							gHDMI20RxHandler[i].audioStableCnt = (UINT32)0;
							gHDMI20RxHandler[i].audioChMapStandByCnt = (UINT32)0;
							HDMI20_HAL_Rx_Set_AudioMuteControl(i, HDMI20_AUDIO_MUTE);
							gHDMI20RxHandler[i].isAudioMute = HDMI20_AUDIO_MUTE;
							if(gHDMI20RxDevAudControler[HDMI20__AUD_CSD_IRQ_DBG].value != (UINT32)0x0)HDMI20_AUDIO("Audio interrup - Mute enable!!(audio type : %d -> %d)\n", data.audioType, gHDMI20RxHandler[i].audioInfo.audioType);
						}else{
							if(gHDMI20RxDevAudControler[HDMI20__AUD_CSD_IRQ_DBG].value != (UINT32)0x0)HDMI20_AUDIO("ignore Audio interrup - audio type no change!\n");
						}
					}
					gHDMI20RxHandler[i].isAudioTypeChangeIrq = FALSE;
				}
			}
		}

		/* Enable IRQ */
		HDMI20_Rx_Audio_Path_Irq_Enable();
}
	return IRQ_HANDLED;
}


int HDMI20_Rx_Audio_Path_Init(void){	
	if (NULL == g_pRealHDMI20AudioReg) {
		if ( lx_chip_rev( ) >= LX_CHIP_REV( M19, A0) ){
			g_pRealHDMI20AudioReg = (volatile HDMI20_RX_AUD_REG_T *)ioremap(HDMI20_RX_M19_AUDIO_REG_ADDRESS, (UINT64)HDMI20_RX_M19_AUDIO_REG_SIZE);
		} else if ( lx_chip_rev( ) >= LX_CHIP_REV( O18, A0) ){
			g_pRealHDMI20AudioReg = (volatile HDMI20_RX_AUD_REG_T *)ioremap(HDMI20_RX_O18_AUDIO_REG_ADDRESS, (UINT64)HDMI20_RX_O18_AUDIO_REG_SIZE);
		} else if ( lx_chip_rev( ) >= LX_CHIP_REV( M17, A0) ){
			g_pRealHDMI20AudioReg = (volatile HDMI20_RX_AUD_REG_T *)ioremap(HDMI20_RX_M17_AUDIO_REG_ADDRESS, (UINT64)HDMI20_RX_M17_AUDIO_REG_SIZE);
		}
	}
	if(g_pRealHDMI20AudioReg == NULL)
	{
		HDMI20_AUDIO("ERROR : can't allocate g_pRealHDMI20AudioReg for register\n");
		return -EIO;
	}

	if (NULL == g_pTempHDMI20AudioReg) {
		g_pTempHDMI20AudioReg = (HDMI20_RX_AUD_REG_T *)kmalloc(sizeof(HDMI20_RX_AUD_REG_T), GFP_KERNEL);
	}
	if(g_pTempHDMI20AudioReg == NULL)
	{
		HDMI20_AUDIO("ERROR : can't allocate g_pTempHDMI20AudioReg for register\n");
		return -EIO;
	}

	return RET_OK;
}

int HDMI20_Rx_Audio_Path_Irq_Check(void){
	UINT32 port, update_mask, csd_update, pc_update;

	if (NULL == g_pRealHDMI20AudioReg) {
		return RET_ERROR;
	}

	HDMI20Aud_RdFL(aud_inthw_mask);
	HDMI20Aud_RdFL(aud_inthw_id);

	HDMI20Aud_RdFL(aud_inthw_mask);
	HDMI20Aud_Rd01(aud_inthw_mask, hmr0csd_update_mask, update_mask);
	if (update_mask == (UINT32)0) {
		HDMI20Aud_RdFL(aud_inthw_id);
		HDMI20Aud_Rd01(aud_inthw_id, hmr0csd_update, csd_update);
		HDMI20Aud_Rd01(aud_inthw_id, hmr0pc_update, pc_update);
		if(csd_update|pc_update){
			port = (UINT32)0;
			gHDMI20RxHandler[port].isAudioTypeChangeIrq = TRUE;
			if(gHDMI20RxDevAudControler[HDMI20__AUD_CSD_IRQ_DBG].value != (UINT32)0x0)HDMI20_AUDIO("Audio info change! port:%d csd:%d, pc:%d\n", port, csd_update, pc_update);
		}
	}

	HDMI20Aud_RdFL(aud_inthw_mask);
	HDMI20Aud_Rd01(aud_inthw_mask, hmr1csd_update_mask, update_mask);
	if (update_mask == (UINT32)0) {
		HDMI20Aud_RdFL(aud_inthw_id);
		HDMI20Aud_Rd01(aud_inthw_id, hmr1csd_update, csd_update);
		HDMI20Aud_Rd01(aud_inthw_id, hmr1pc_update, pc_update);;
		if(csd_update|pc_update){
			port = (UINT32)1;
			gHDMI20RxHandler[port].isAudioTypeChangeIrq = TRUE;
			if(gHDMI20RxDevAudControler[HDMI20__AUD_CSD_IRQ_DBG].value != (UINT32)0x0)HDMI20_AUDIO("Audio info change! port:%d csd:%d, pc:%d\n", port, csd_update, pc_update);
		}
	}

	HDMI20Aud_RdFL(aud_inthw_mask);
	HDMI20Aud_Rd01(aud_inthw_mask, hmr2csd_update_mask, update_mask);
	if (update_mask == (UINT32)0) {
		HDMI20Aud_RdFL(aud_inthw_id);
		HDMI20Aud_Rd01(aud_inthw_id, hmr2csd_update, csd_update);
		HDMI20Aud_Rd01(aud_inthw_id, hmr2pc_update, pc_update);
		if(csd_update|pc_update){
			port = (UINT32)2;
			gHDMI20RxHandler[port].isAudioTypeChangeIrq = TRUE;
			if(gHDMI20RxDevAudControler[HDMI20__AUD_CSD_IRQ_DBG].value != (UINT32)0x0)HDMI20_AUDIO("Audio info change! port:%d csd:%d, pc:%d\n", port, csd_update, pc_update);
		}
	}

	HDMI20Aud_RdFL(aud_inthw_mask);
	HDMI20Aud_Rd01(aud_inthw_mask, hmr3csd_update_mask, update_mask);
	if (update_mask == (UINT32)0) {
		HDMI20Aud_RdFL(aud_inthw_id);
		HDMI20Aud_Rd01(aud_inthw_id, hmr3csd_update, csd_update);
		HDMI20Aud_Rd01(aud_inthw_id, hmr3pc_update, pc_update);
		if(csd_update|pc_update){
			port = (UINT32)3;
			gHDMI20RxHandler[port].isAudioTypeChangeIrq = TRUE;
			if(gHDMI20RxDevAudControler[HDMI20__AUD_CSD_IRQ_DBG].value != (UINT32)0x0)HDMI20_AUDIO("Audio info change! port:%d csd:%d, pc:%d\n", port, csd_update, pc_update);
		}
	}

	__HDMI20_Rx_Audio_Path_irq_UpdateClear();
	return RET_OK;

}

static int __HDMI20_Rx_Audio_Path_irq_UpdateClear (void){
	if (NULL == g_pRealHDMI20AudioReg) {
		return RET_ERROR;
	}

	HDMI20Aud_RdFL(aud_inthw_id);
	HDMI20Aud_Wr(aud_inthw_id, (UINT32)0x0);
	HDMI20Aud_WrFL(aud_inthw_id);
	return RET_OK;
}

int HDMI20_Rx_Audio_Path_Irq_Disable(void){
	int ret = RET_OK;

	if (NULL == g_pRealHDMI20AudioReg) {
		return RET_ERROR;
	}

	HDMI20Aud_RdFL(aud_inthw_en);
	HDMI20Aud_Wr01(aud_inthw_en, aud_inthw_en, (UINT32)0x0);
	HDMI20Aud_WrFL(aud_inthw_en);

	return ret;
}

int HDMI20_Rx_Audio_Path_Irq_Enable(void){
	int ret = RET_OK;

	if (NULL == g_pRealHDMI20AudioReg) {
		return RET_ERROR;
	}

	HDMI20Aud_RdFL(aud_inthw_en);
	HDMI20Aud_Wr01(aud_inthw_en, aud_inthw_en, (UINT32)0x1);
	HDMI20Aud_WrFL(aud_inthw_en);

	return ret;
}

int HDMI20_Rx_Audio_Path_Irq_Clear(void){
	int ret = RET_OK;

	if (NULL == g_pRealHDMI20AudioReg) {
		return RET_ERROR;
	}

	HDMI20Aud_RdFL(aud_inthw_clr);
	HDMI20Aud_Wr01(aud_inthw_clr, aud_inthw_clr, (UINT32)0x1);
	HDMI20Aud_WrFL(aud_inthw_clr);

	HDMI20Aud_RdFL(aud_inthw_clr);
	HDMI20Aud_Wr01(aud_inthw_clr, aud_inthw_clr, (UINT32)0x0);
	HDMI20Aud_WrFL(aud_inthw_clr);

	return ret;
}

int HDMI20_Rx_Audio_Path_SetInthw(UINT8 port){
	int ret = RET_OK;
	UINT32 resetout;

	if (NULL == g_pRealHDMI20AudioReg) {
		return RET_ERROR;
	}

	HDMI20Aud_RdFL(aud_swreset);
	HDMI20Aud_Rd01(aud_swreset, apbresetout, resetout);

	if (resetout == 0){
		HDMI20_AUDIO("HDMI Audio register is not ready!\n");
		gHDMI20RxHandler[port].isAudioRegReady = FALSE;
		return ret;
	}else{
		gHDMI20RxHandler[port].isAudioRegReady = TRUE;
		HDMI20Aud_RdFL(aud_inthw_en);
		HDMI20Aud_Wr01(aud_inthw_en, aud_inthw_en, (UINT32)0x1);
		HDMI20Aud_WrFL(aud_inthw_en);

		HDMI20Aud_RdFL(aud_inthw_mask);
		HDMI20Aud_Wr01(aud_inthw_mask, reserved, (UINT32)0xFFFFF);
		HDMI20Aud_WrFL(aud_inthw_mask);

		HDMI20Aud_RdFL(aud_inthw_mask);
		if (port == 0) {
			HDMI20Aud_Wr02(aud_inthw_mask, hmr0csd_update_mask, (UINT32)0, hmr0pc_update_mask, (UINT32)0);
		}else if (port == 1) {
			HDMI20Aud_Wr02(aud_inthw_mask, hmr1csd_update_mask, (UINT32)0, hmr1pc_update_mask, (UINT32)0);
		}else if(port == 2) {
			HDMI20Aud_Wr02(aud_inthw_mask, hmr2csd_update_mask, (UINT32)0, hmr2pc_update_mask, (UINT32)0);
		}else if(port == 3) {
			HDMI20Aud_Wr02(aud_inthw_mask, hmr3csd_update_mask, (UINT32)0, hmr3pc_update_mask, (UINT32)0);
		}else {
			HDMI20_AUDIO("port number is wrong\n");
			return RET_ERROR;
		}
		HDMI20Aud_WrFL(aud_inthw_mask);
	}

	return ret;
}

int HDMI20_Rx_Audio_Path_InthwUnmask(UINT8 port){
	int ret = RET_OK;

	if (NULL == g_pRealHDMI20AudioReg) {
		return RET_ERROR;
	}

	HDMI20Aud_RdFL(aud_inthw_mask);
	HDMI20Aud_Wr01(aud_inthw_mask, reserved, (UINT32)0xFFFFF);
	HDMI20Aud_WrFL(aud_inthw_mask);

	HDMI20Aud_RdFL(aud_inthw_mask);
	if (port == 0) {
		HDMI20Aud_Wr02(aud_inthw_mask, hmr0csd_update_mask, (UINT32)1, hmr0pc_update_mask, (UINT32)1);
	}else if (port == 1) {
		HDMI20Aud_Wr02(aud_inthw_mask, hmr1csd_update_mask, (UINT32)1, hmr1pc_update_mask, (UINT32)1);
	}else if(port == 2) {
		HDMI20Aud_Wr02(aud_inthw_mask, hmr2csd_update_mask, (UINT32)1, hmr2pc_update_mask, (UINT32)1);
	}else if(port == 3) {
		HDMI20Aud_Wr02(aud_inthw_mask, hmr3csd_update_mask, (UINT32)1, hmr3pc_update_mask, (UINT32)1);
	}else {
		HDMI20_AUDIO("port number is wrong\n");
		return RET_ERROR;
	}
	HDMI20Aud_WrFL(aud_inthw_mask);

	return ret;
}

int HDMI20_Rx_Audio_Path_GetSPDIFInfo(UINT8 port, HDMI20_AUDIO_REG_DATA *pHdmi20AudioRegData){
	int ret = RET_OK;
	UINT32 byte0, byte1, pc;

	if (NULL == g_pRealHDMI20AudioReg) {
		return RET_ERROR;
	} else {
		if(port == 0) {
			HDMI20Aud_RdFL(hmr0_csd0);
			HDMI20Aud_Rd01(hmr0_csd0, hmr0csd0, byte0);
			HDMI20Aud_RdFL(hmr0_csd1);
			HDMI20Aud_Rd01(hmr0_csd1, hmr0csd1, byte1);
			HDMI20Aud_RdFL(hmr0_pcpd);
			HDMI20Aud_Rd01(hmr0_pcpd, hmr0pc, pc);
		}else if(port == 1) {
			HDMI20Aud_RdFL(hmr1_csd0);
			HDMI20Aud_Rd01(hmr1_csd0, hmr1csd0, byte0);
			HDMI20Aud_RdFL(hmr1_csd1);
			HDMI20Aud_Rd01(hmr1_csd1, hmr1csd1, byte1);
			HDMI20Aud_RdFL(hmr1_pcpd);
			HDMI20Aud_Rd01(hmr1_pcpd, hmr1pc, pc);
		}else if(port == 2) {
			HDMI20Aud_RdFL(hmr2_csd0);
			HDMI20Aud_Rd01(hmr2_csd0, hmr2csd0, byte0);
			HDMI20Aud_RdFL(hmr2_csd1);
			HDMI20Aud_Rd01(hmr2_csd1, hmr2csd1, byte1);
			HDMI20Aud_RdFL(hmr2_pcpd);
			HDMI20Aud_Rd01(hmr2_pcpd, hmr2pc, pc);
		}else if(port == 3) {
			HDMI20Aud_RdFL(hmr3_csd0);
			HDMI20Aud_Rd01(hmr3_csd0, hmr3csd0, byte0);
			HDMI20Aud_RdFL(hmr3_csd1);
			HDMI20Aud_Rd01(hmr3_csd1, hmr3csd1, byte1);
			HDMI20Aud_RdFL(hmr3_pcpd);
			HDMI20Aud_Rd01(hmr3_pcpd, hmr3pc, pc);
		}else {
			HDMI20_AUDIO("port number is wrong\n");
			return RET_ERROR;
		}

		pHdmi20AudioRegData->byte0 = byte0 & (UINT32)0xF;
		pHdmi20AudioRegData->byte1 = byte1 & (UINT32)0xF;
		pHdmi20AudioRegData->pcpd = pc & (UINT32)0xFFFF;
	}

	return ret;
}

int HDMI20_Rx_Audio_Path_SetMute(UINT8 port){

	if (NULL == g_pRealHDMI20AudioReg) {
		return RET_ERROR;
	}

	if (port == 0) {
		HDMI20Aud_RdFL(hmr0_mute);
		HDMI20Aud_Wr01(hmr0_mute, hmr0mute, (UINT32)0x1);
		HDMI20Aud_WrFL(hmr0_mute);
	}else if (port == 1) {
		HDMI20Aud_RdFL(hmr1_mute);
		HDMI20Aud_Wr01(hmr1_mute, hmr1mute, (UINT32)0x1);
		HDMI20Aud_WrFL(hmr1_mute);
	}else if(port == 2) {
		HDMI20Aud_RdFL(hmr2_mute);
		HDMI20Aud_Wr01(hmr2_mute, hmr2mute, (UINT32)0x1);
		HDMI20Aud_WrFL(hmr2_mute);
	}else if(port == 3) {
		HDMI20Aud_RdFL(hmr3_mute);
		HDMI20Aud_Wr01(hmr3_mute, hmr3mute, (UINT32)0x1);
		HDMI20Aud_WrFL(hmr3_mute);
	}else {
		HDMI20_AUDIO("port number is wrong\n");
		return RET_ERROR;
	}

	return RET_OK;
}
int HDMI20_Rx_Audio_Path_SetUnmute(UINT8 port){
	if (NULL == g_pRealHDMI20AudioReg) {
		return RET_ERROR;
	}

	if (port == 0) {
		HDMI20Aud_RdFL(hmr0_mute);
		HDMI20Aud_Wr01(hmr0_mute, hmr0mute, (UINT32)0x0);
		HDMI20Aud_WrFL(hmr0_mute);
	}else if (port == 1) {
		HDMI20Aud_RdFL(hmr1_mute);
		HDMI20Aud_Wr01(hmr1_mute, hmr1mute, (UINT32)0x0);
		HDMI20Aud_WrFL(hmr1_mute);
	}else if(port == 2) {
		HDMI20Aud_RdFL(hmr2_mute);
		HDMI20Aud_Wr01(hmr2_mute, hmr2mute, (UINT32)0x0);
		HDMI20Aud_WrFL(hmr2_mute);
	}else if(port == 3) {
		HDMI20Aud_RdFL(hmr3_mute);
		HDMI20Aud_Wr01(hmr3_mute, hmr3mute, (UINT32)0x0);
		HDMI20Aud_WrFL(hmr3_mute);
	}else {
		HDMI20_AUDIO("port number is wrong\n");
		return RET_ERROR;
	}

	return RET_OK;
}


