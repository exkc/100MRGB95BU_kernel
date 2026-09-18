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
 *  @date		2019-04-15
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

#include "hdmi21_rx_audio_path_spdif.h"
#include "hdmi21_hal_driver.h"
#include "hdmi21_rx_audio.h"
#include "../hdmi20_drv.h"
#include "hdmi_kapi.h"

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
extern HDMI21_HAL_RX_DEVICE_DATA gHDMI21RxHandler[HDMI21_NUM_OF_MAX_PORTS];
extern HDMI20_DEV_CONTROL_T	gHDMI21RxDevAudioControler[HDMI21__DEV_AUDIO_CONTROL_LIST_MAXNUM];
extern HDMI21_HAL_RX_AUDIO_DATA gHDMI21RxAudioHandler[HDMI21_NUM_OF_MAX_PORTS];

/* Number of Max operable ports */
extern int		g_hdmi20_number_of_ports;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int g_HDMI21_AudIrq = 0;
/*----------------------------------------------------------------------------------------
	Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int __HDMI21_Rx_Audio_Path_irq_UpdateClear (void);
/*----------------------------------------------------------------------------------------
	Variables
----------------------------------------------------------------------------------------*/
/* define HDMI AUDIO register */
static volatile HDMI21_RX_AUD_REG_T *g_pRealHDMI21AudioReg = NULL;
static HDMI21_RX_AUD_REG_T *g_pTempHDMI21AudioReg = NULL;
static volatile HDMI21_RX_AUD_REG_O22_T *g_pRealHDMI21AudioRegO22 = NULL;
static HDMI21_RX_AUD_REG_O22_T *g_pTempHDMI21AudioRegO22 = NULL;

BOOLEAN gHDMI21AudioisCSDChange[HDMI21_NUM_OF_MAX_PORTS] ={FALSE, FALSE, FALSE, FALSE};
static HDMI21_AUDIO_REG_DATA _gHDMI21AudioRegData; // NEED initialize

/*========================================================================================
	Implementation Group
========================================================================================*/
int HDMI21_Rx_Audio_RequestIrq(void)
{
	int ret = RET_ERROR;

	if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_IRQ_DISABLE_SPDIF].value == 0x0){

		if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
			ret = request_threaded_irq(HDMI21_RX_O24_IRQ_AUDIO, HDMI21_Rx_Audio_IRQ_Handler, HDMI21_Rx_Audio_IRQ_Thread_Handler, IRQF_TRIGGER_RISING, "HDMI20_AUDIO", &g_HDMI21_AudIrq);
		}else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
			ret = request_threaded_irq(HDMI21_RX_M23_IRQ_AUDIO, HDMI21_Rx_Audio_IRQ_Handler, HDMI21_Rx_Audio_IRQ_Thread_Handler, IRQF_TRIGGER_RISING, "HDMI20_AUDIO", &g_HDMI21_AudIrq);
		}else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
			ret = request_threaded_irq(HDMI21_RX_O22_IRQ_AUDIO, HDMI21_Rx_Audio_IRQ_Handler, HDMI21_Rx_Audio_IRQ_Thread_Handler, IRQF_TRIGGER_RISING, "HDMI20_AUDIO", &g_HDMI21_AudIrq);
		}else if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ){
			ret = request_threaded_irq(HDMI21_RX_E60_IRQ_AUDIO, HDMI21_Rx_Audio_IRQ_Handler, HDMI21_Rx_Audio_IRQ_Thread_Handler, IRQF_TRIGGER_RISING, "HDMI20_AUDIO", &g_HDMI21_AudIrq);
		}else if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
			ret = request_threaded_irq(HDMI21_RX_O20_IRQ_AUDIO, HDMI21_Rx_Audio_IRQ_Handler, HDMI21_Rx_Audio_IRQ_Thread_Handler, IRQF_TRIGGER_RISING, "HDMI20_AUDIO", &g_HDMI21_AudIrq);
		} 

		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0)HDMI20_ADEF("HDMI Audio request interrupt!!(%d)\n", ret);
	}
	return ret;
}

int HDMI21_Rx_Audio_FreeIrq(void)
{
	if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_IRQ_DISABLE_SPDIF].value == (UINT32)0x0){
		if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
			free_irq(HDMI21_RX_M23_IRQ_AUDIO, &g_HDMI21_AudIrq);
		}else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
			free_irq(HDMI21_RX_M23_IRQ_AUDIO, &g_HDMI21_AudIrq);
		}else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
			free_irq(HDMI21_RX_O22_IRQ_AUDIO, &g_HDMI21_AudIrq);
		}else if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ){
			free_irq(HDMI21_RX_E60_IRQ_AUDIO, &g_HDMI21_AudIrq);
		}else if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
			free_irq(HDMI21_RX_O20_IRQ_AUDIO, &g_HDMI21_AudIrq);
		}
	}
	return RET_OK;
}

irqreturn_t HDMI21_Rx_Audio_IRQ_Handler(int irq, void *dev_id)
{
	if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_IRQ_DISABLE_SPDIF].value == 0x0){
		if ( dev_id == NULL){
			HDMI20_INTR("HDMI Audio ISR : NULL parmeter\n" );
			return -1;
		}

		/* Check IRQ */
		HDMI21_Rx_Audio_Path_Irq_Check();

		/* Disable IRQ */
		HDMI21_Rx_Audio_Path_Irq_Disable();

		/* Clear IRQ */
		HDMI21_Rx_Audio_Path_Irq_Clear();

		/* Enable IRQ */
		HDMI21_Rx_Audio_Path_Irq_Enable();
	}
	//return IRQ_HANDLED;
	return IRQ_WAKE_THREAD;
}

irqreturn_t HDMI21_Rx_Audio_IRQ_Thread_Handler(int irq, void *dev_id)
{
	UINT8 i;
	LX_HDMI_AUDIO_INFO_T	data;
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	HDMI21_HAL_RX_AUDIO_DATA *_a;

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value != (UINT32)0x700){
			for(i=(UINT8)0;i<g_hdmi20_number_of_ports;i++){
				if(gHDMI21RxHandler[i].isAudioTypeChangeIrq == TRUE){
					_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[i];
					_a = (HDMI21_HAL_RX_AUDIO_DATA *)&gHDMI21RxAudioHandler[i];
					if(_a->procConfig0_muteControl == HDMI21_RX__EXT__PROC_CONFIG0__MUTE){
						//|| (gHDMI21RxHandler[i].audioFifoErrMuteCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ERR_MUTE_TIME].value)){
						HDMI21_HAL_Rx_Get_AudioType(i, &data.audioType);
						gHDMI21AudioisCSDChange[i] = FALSE;
						if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0)HDMI20_ADEF("HDMI[%d] Audio Ignore interrupt!! AChange:%d, isMute:%d, Mutecnt:%d, I2Scnt:%d, Noaudio:%d \n", i, gHDMI21RxHandler[i].audio_change, gHDMI21RxHandler[i].isMute, gHDMI21RxHandler[i].audioStandByCnt, gHDMI21RxHandler[i].audioFifoErrMuteCnt, gHDMI21RxHandler[i].audioStableCnt);
					}else{
						HDMI21_HAL_Rx_Get_AudioType(i, &data.audioType);
						if(data.audioType != gHDMI21RxHandler[i].audioInfo.audioType \
						&& gHDMI21AudioisCSDChange[i] == TRUE){
							gHDMI21RxHandler[i].audioStableCnt = 0;
							gHDMI21RxHandler[i].audioChMapStandByCnt = 0;
							HDMI21_HAL_Rx_Set_AudioMuteControl(i, HDMI21_AUDIO_MUTE);
							gHDMI21RxHandler[i].isAudioMute = HDMI21_AUDIO_MUTE;
							gHDMI21AudioisCSDChange[i] = FALSE;
							/* [Get]Handler */
							_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[i];
							if(_p->audio_state == (int)HDMI21__AUDIO_STATE__5__ENABLE__CHANGE_IRQ\
							|| _p->audio_state == (int)HDMI21__AUDIO_STATE__0__DEFAULT)
							{
								HDMI21_HAL_Rx_Set_AudioEnable(i, FALSE);
								if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_STATE].value != 0)HDMI20_ADEF("HDMI[%d] Audio state %d->%d(type change)!!!kkkkkk\n", i, HDMI21__AUDIO_STATE__5__ENABLE__CHANGE_IRQ, HDMI21__AUDIO_STATE__1__DISABLE__WAIT_AUDIF_RCV);
							}
							if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0)HDMI20_ADEF("HDMI[%d] Audio interrup - Mute enable!!(audio type : %d -> %d)\n", i, data.audioType, gHDMI21RxHandler[i].audioInfo.audioType);
						}else{
							if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0)HDMI20_ADEF("HDMI[%d] Audio ignore Audio interrup - audio type no change!\n", i);
							gHDMI21AudioisCSDChange[i] = FALSE;
						}
					}
					gHDMI21RxHandler[i].isAudioTypeChangeIrq = FALSE;
				}
			}
		}
	}else{
		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value != 0x700){
			for(i=(UINT8)0;i<g_hdmi20_number_of_ports;i++){
				if(gHDMI21RxHandler[i].isAudioTypeChangeIrq == TRUE){
					if((HDMI21_HAL_Rx_Get_IsLocalMuteOn(i) > 0) ||	(gHDMI21RxHandler[i].audio_change == TRUE) || (gHDMI21RxHandler[i].isMute == TRUE)\
					|| (gHDMI21RxHandler[i].audioStandByCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_STANDBY_TIME].value)\
					|| (gHDMI21RxHandler[i].audioStableCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME].value)){
						//|| (gHDMI21RxHandler[i].audioFifoErrMuteCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ERR_MUTE_TIME].value)){
						HDMI21_HAL_Rx_Get_AudioType(i, &data.audioType);
						if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0)HDMI20_ADEF("HDMI[%d] Audio Ignore interrupt!! AChange:%d, isMute:%d, Mutecnt:%d, I2Scnt:%d, Noaudio:%d \n", i, gHDMI21RxHandler[i].audio_change, gHDMI21RxHandler[i].isMute, gHDMI21RxHandler[i].audioStandByCnt, gHDMI21RxHandler[i].audioFifoErrMuteCnt, gHDMI21RxHandler[i].audioStableCnt);
						gHDMI21AudioisCSDChange[i] = FALSE;
					} else {
						HDMI21_HAL_Rx_Get_AudioType(i, &data.audioType);
						if(data.audioType != gHDMI21RxHandler[i].audioInfo.audioType \
						&& gHDMI21AudioisCSDChange[i] == TRUE){
							gHDMI21RxHandler[i].audioStableCnt = 0;
							gHDMI21RxHandler[i].audioChMapStandByCnt = 0;
							HDMI21_HAL_Rx_Set_AudioMuteControl(i, HDMI21_AUDIO_MUTE);
							gHDMI21RxHandler[i].isAudioMute = HDMI21_AUDIO_MUTE;
							gHDMI21AudioisCSDChange[i] = FALSE;
							/* [Get]Handler */
							_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[i];
							if(_p->audio_state == HDMI21__AUDIO_STATE__5__ENABLE__CHANGE_IRQ\
							|| _p->audio_state == HDMI21__AUDIO_STATE__0__DEFAULT)
							{
								HDMI21_HAL_Rx_Set_AudioEnable(i, FALSE);
								if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_STATE].value != 0)HDMI20_ADEF("HDMI[%d] Audio state %d->%d(type change)!!!kkkkkk\n", i, HDMI21__AUDIO_STATE__5__ENABLE__CHANGE_IRQ, HDMI21__AUDIO_STATE__1__DISABLE__WAIT_AUDIF_RCV);
							}
							if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0)HDMI20_ADEF("HDMI[%d] Audio interrup - Mute enable!!(audio type : %d -> %d)\n", i, data.audioType, gHDMI21RxHandler[i].audioInfo.audioType);
						}else{
							if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0)HDMI20_ADEF("HDMI[%d] Audio ignore Audio interrup - audio type no change!\n", i);
							gHDMI21AudioisCSDChange[i] = FALSE;
						}
					}
					gHDMI21RxHandler[i].isAudioTypeChangeIrq = FALSE;
				}
			}
		}
	}

	return IRQ_HANDLED;
}

int HDMI21_Rx_Audio_Path_Init(void){	
	if (NULL == g_pRealHDMI21AudioReg) {
		if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
			g_pRealHDMI21AudioRegO22 = (volatile HDMI21_RX_AUD_REG_O22_T *)ioremap(HDMI21_RX_O24_AUDIO_REG_ADDRESS, HDMI21_RX_O24_AUDIO_REG_SIZE);
		}else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
			g_pRealHDMI21AudioRegO22 = (volatile HDMI21_RX_AUD_REG_O22_T *)ioremap(HDMI21_RX_M23_AUDIO_REG_ADDRESS, HDMI21_RX_M23_AUDIO_REG_SIZE);
		}else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
			g_pRealHDMI21AudioRegO22 = (volatile HDMI21_RX_AUD_REG_O22_T *)ioremap(HDMI21_RX_O22_AUDIO_REG_ADDRESS, HDMI21_RX_O22_AUDIO_REG_SIZE);
		}else if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ){
			g_pRealHDMI21AudioReg = (volatile HDMI21_RX_AUD_REG_T *)ioremap(HDMI21_RX_E60_AUDIO_REG_ADDRESS, HDMI21_RX_E60_AUDIO_REG_SIZE);
		}else if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
			g_pRealHDMI21AudioReg = (volatile HDMI21_RX_AUD_REG_T *)ioremap(HDMI21_RX_O20_AUDIO_REG_ADDRESS, HDMI21_RX_O20_AUDIO_REG_SIZE);
		}
	}

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
		_gHDMI21AudioRegData.byte0 = 0;
		_gHDMI21AudioRegData.byte1 = 0;
		_gHDMI21AudioRegData.byte2 = 0;
		_gHDMI21AudioRegData.byte3 = 0;
		_gHDMI21AudioRegData.byte4 = 0;
		_gHDMI21AudioRegData.byte5 = 0;
	}

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
		if(g_pRealHDMI21AudioRegO22 == NULL){
			HDMI20_ERROR("ERROR : can't allocate g_pRealHDMI21AudioReg for register\n");
			return -EIO;
		}

		if (NULL == g_pTempHDMI21AudioRegO22) {
		g_pTempHDMI21AudioRegO22 = (HDMI21_RX_AUD_REG_O22_T *)kmalloc(sizeof(HDMI21_RX_AUD_REG_O22_T), GFP_KERNEL);
		}
		if(g_pTempHDMI21AudioRegO22 == NULL)
		{
			HDMI20_ERROR("ERROR : can't allocate g_pTempHDMI21AudioRegO22 for register\n");
			return -EIO;
		}
	}else{
		if(g_pRealHDMI21AudioReg == NULL){
			HDMI20_ERROR("ERROR : can't allocate g_pRealHDMI21AudioReg for register\n");
			return -EIO;
		}

		if (NULL == g_pTempHDMI21AudioReg) {
		g_pTempHDMI21AudioReg = (HDMI21_RX_AUD_REG_T *)kmalloc(sizeof(HDMI21_RX_AUD_REG_T), GFP_KERNEL);
		}
		if(g_pTempHDMI21AudioReg == NULL)
		{
			HDMI20_ERROR("ERROR : can't allocate g_pTempHDMI21AudioReg for register\n");
			return -EIO;
		}
	}

	return RET_OK;
}

int HDMI21_Rx_Audio_Path_Irq_Check(void){
	UINT32 port, update_mask, csd_update, pc_update;

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
		if (NULL == g_pRealHDMI21AudioRegO22) {
			return RET_ERROR;
		}
		HDMI21AudO22_RdFL(AUD_INTHW_MASK0);
		HDMI21AudO22_RdFL(AUD_INTHW_ID0);
		HDMI21AudO22_RdFL(AUD_INTHW_MASK1);
		HDMI21AudO22_RdFL(AUD_INTHW_ID1);

		HDMI21AudO22_RdFL(AUD_INTHW_MASK0);
		HDMI21AudO22_Rd01(AUD_INTHW_MASK0, hmr0spdif0csd_update_mask, update_mask);
		if (update_mask == 0) {
			HDMI21AudO22_RdFL(AUD_INTHW_ID0);
			HDMI21AudO22_Rd01(AUD_INTHW_ID0, hmr0spdif0csd_update, csd_update);
			HDMI21AudO22_Rd01(AUD_INTHW_ID0, hmr0spdif0pc_update, pc_update);
			if(csd_update|pc_update){
				port = 0;
				gHDMI21RxHandler[port].isAudioTypeChangeIrq = TRUE;
				if(csd_update) gHDMI21AudioisCSDChange[port] = TRUE;
				if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0)HDMI20_ADEF("HDMI[%d] Audio info change! csd:%d, pc:%d\n", port, csd_update, pc_update);
			}
		}

		HDMI21AudO22_RdFL(AUD_INTHW_MASK0);
		HDMI21AudO22_Rd01(AUD_INTHW_MASK0, hmr1spdif0csd_update_mask, update_mask);
		if (update_mask == 0) {
			HDMI21AudO22_RdFL(AUD_INTHW_ID0);
			HDMI21AudO22_Rd01(AUD_INTHW_ID0, hmr1spdif0csd_update, csd_update);
			HDMI21AudO22_Rd01(AUD_INTHW_ID0, hmr1spdif0pc_update, pc_update);;
			if(csd_update|pc_update){
				port = 1;
				gHDMI21RxHandler[port].isAudioTypeChangeIrq = TRUE;
				if(csd_update) gHDMI21AudioisCSDChange[port] = TRUE;
				if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0)HDMI20_ADEF("HDMI[%d] Audio info change! csd:%d, pc:%d\n", port, csd_update, pc_update);
			}
		}

		HDMI21AudO22_RdFL(AUD_INTHW_MASK0);
		HDMI21AudO22_Rd01(AUD_INTHW_MASK0, hmr2spdif0csd_update_mask, update_mask);
		if (update_mask == 0) {
			HDMI21AudO22_RdFL(AUD_INTHW_ID0);
			HDMI21AudO22_Rd01(AUD_INTHW_ID0, hmr2spdif0csd_update, csd_update);
			HDMI21AudO22_Rd01(AUD_INTHW_ID0, hmr2spdif0pc_update, pc_update);
			if(csd_update|pc_update){
				port = 2;
				gHDMI21RxHandler[port].isAudioTypeChangeIrq = TRUE;
				if(csd_update) gHDMI21AudioisCSDChange[port] = TRUE;
				if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0)HDMI20_ADEF("HDMI[%d] Audio info change! csd:%d, pc:%d\n", port, csd_update, pc_update);
			}
		}

		HDMI21AudO22_RdFL(AUD_INTHW_MASK1);
		HDMI21AudO22_Rd01(AUD_INTHW_MASK1, hmr3spdif0csd_update_mask, update_mask);
		if (update_mask == 0) {
			HDMI21AudO22_RdFL(AUD_INTHW_ID1);
			HDMI21AudO22_Rd01(AUD_INTHW_ID1, hmr3spdif0csd_update, csd_update);
			HDMI21AudO22_Rd01(AUD_INTHW_ID1, hmr3spdif0pc_update, pc_update);
			if(csd_update|pc_update){
				port = 3;
				gHDMI21RxHandler[port].isAudioTypeChangeIrq = TRUE;
				if(csd_update) gHDMI21AudioisCSDChange[port] = TRUE;
				if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0)HDMI20_ADEF("HDMI[%d] Audio info change! csd:%d, pc:%d\n", port, csd_update, pc_update);
			}
		}

		if (( lx_chip_rev( ) < LX_CHIP_REV( E60, A0) ) || ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ))/*(port == 4)*/ {
			HDMI21AudO22_RdFL(AUD_INTHW_MASK1);
			HDMI21AudO22_Rd01(AUD_INTHW_MASK1, hmr4spdif0csd_update_mask, update_mask);
			if (update_mask == 0) {
				HDMI21AudO22_RdFL(AUD_INTHW_ID1);
				HDMI21AudO22_Rd01(AUD_INTHW_ID1, hmr4spdif0csd_update, csd_update);
				HDMI21AudO22_Rd01(AUD_INTHW_ID1, hmr4spdif0pc_update, pc_update);
				if(csd_update|pc_update){
					port = 4;
					gHDMI21RxHandler[port].isAudioTypeChangeIrq = TRUE;
					if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0)HDMI20_ADEF("HDMI[%d] Audio info change! csd:%d, pc:%d\n", port, csd_update, pc_update);
				}
			}
		}
	}else{
		if (NULL == g_pRealHDMI21AudioReg) {
			return RET_ERROR;
		}
		
		HDMI21Aud_RdFL(AUD_INTHW_MASK0);
		HDMI21Aud_RdFL(AUD_INTHW_ID0);
		HDMI21Aud_RdFL(AUD_INTHW_MASK1);
		HDMI21Aud_RdFL(AUD_INTHW_ID1);

		HDMI21Aud_RdFL(AUD_INTHW_MASK0);
		HDMI21Aud_Rd01(AUD_INTHW_MASK0, hmr0spdif0csd_update_mask, update_mask);
		if (update_mask == 0) {
			HDMI21Aud_RdFL(AUD_INTHW_ID0);
			HDMI21Aud_Rd01(AUD_INTHW_ID0, hmr0spdif0csd_update, csd_update);
			HDMI21Aud_Rd01(AUD_INTHW_ID0, hmr0spdif0pc_update, pc_update);
			if(csd_update|pc_update){
				port = 0;
				gHDMI21RxHandler[port].isAudioTypeChangeIrq = TRUE;
				if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0)HDMI20_ADEF("HDMI[%d] Audio info change! csd:%d, pc:%d\n", port, csd_update, pc_update);
			}
		}

		HDMI21Aud_RdFL(AUD_INTHW_MASK0);
		HDMI21Aud_Rd01(AUD_INTHW_MASK0, hmr1spdif0csd_update_mask, update_mask);
		if (update_mask == 0) {
			HDMI21Aud_RdFL(AUD_INTHW_ID0);
			HDMI21Aud_Rd01(AUD_INTHW_ID0, hmr1spdif0csd_update, csd_update);
			HDMI21Aud_Rd01(AUD_INTHW_ID0, hmr1spdif0pc_update, pc_update);;
			if(csd_update|pc_update){
				port = 1;
				gHDMI21RxHandler[port].isAudioTypeChangeIrq = TRUE;
				if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0)HDMI20_ADEF("HDMI[%d] Audio info change! csd:%d, pc:%d\n", port, csd_update, pc_update);
			}
		}

		HDMI21Aud_RdFL(AUD_INTHW_MASK0);
		HDMI21Aud_Rd01(AUD_INTHW_MASK0, hmr2spdif0csd_update_mask, update_mask);
		if (update_mask == 0) {
			HDMI21Aud_RdFL(AUD_INTHW_ID0);
			HDMI21Aud_Rd01(AUD_INTHW_ID0, hmr2spdif0csd_update, csd_update);
			HDMI21Aud_Rd01(AUD_INTHW_ID0, hmr2spdif0pc_update, pc_update);
			if(csd_update|pc_update){
				port = 2;
				gHDMI21RxHandler[port].isAudioTypeChangeIrq = TRUE;
				if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0)HDMI20_ADEF("HDMI[%d] Audio info change! csd:%d, pc:%d\n", port, csd_update, pc_update);
			}
		}

		HDMI21Aud_RdFL(AUD_INTHW_MASK1);
		HDMI21Aud_Rd01(AUD_INTHW_MASK1, hmr3spdif0csd_update_mask, update_mask);
		if (update_mask == 0) {
			HDMI21Aud_RdFL(AUD_INTHW_ID1);
			HDMI21Aud_Rd01(AUD_INTHW_ID1, hmr3spdif0csd_update, csd_update);
			HDMI21Aud_Rd01(AUD_INTHW_ID1, hmr3spdif0pc_update, pc_update);
			if(csd_update|pc_update){
				port = 3;
				gHDMI21RxHandler[port].isAudioTypeChangeIrq = TRUE;
				if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0)HDMI20_ADEF("HDMI[%d] Audio info change! csd:%d, pc:%d\n", port, csd_update, pc_update);
			}
		}

		if (( lx_chip_rev( ) < LX_CHIP_REV( E60, A0) ) || ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ))/*(port == 4)*/ {
			HDMI21Aud_RdFL(AUD_INTHW_MASK1);
			HDMI21Aud_Rd01(AUD_INTHW_MASK1, hmr4spdif0csd_update_mask, update_mask);
			if (update_mask == 0) {
				HDMI21Aud_RdFL(AUD_INTHW_ID1);
				HDMI21Aud_Rd01(AUD_INTHW_ID1, hmr4spdif0csd_update, csd_update);
				HDMI21Aud_Rd01(AUD_INTHW_ID1, hmr4spdif0pc_update, pc_update);
				if(csd_update|pc_update){
					port = 4;
					gHDMI21RxHandler[port].isAudioTypeChangeIrq = TRUE;
					if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0)HDMI20_ADEF("HDMI[%d] Audio info change! csd:%d, pc:%d\n", port, csd_update, pc_update);
				}
			}
		}
	}

	__HDMI21_Rx_Audio_Path_irq_UpdateClear();
	return RET_OK;

}

static int __HDMI21_Rx_Audio_Path_irq_UpdateClear (void){

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
		if (NULL == g_pRealHDMI21AudioRegO22) {
			return RET_ERROR;
		}
		HDMI21AudO22_RdFL(AUD_INTHW_ID0);
		HDMI21AudO22_Wr(AUD_INTHW_ID0, 0x0);
		HDMI21AudO22_WrFL(AUD_INTHW_ID0);

		HDMI21AudO22_RdFL(AUD_INTHW_ID1);
		HDMI21AudO22_Wr(AUD_INTHW_ID1, 0x0);
		HDMI21AudO22_WrFL(AUD_INTHW_ID1);
	}else{
		if (NULL == g_pRealHDMI21AudioReg) {
			return RET_ERROR;
		}
		HDMI21Aud_RdFL(AUD_INTHW_ID0);
		HDMI21Aud_Wr(AUD_INTHW_ID0, 0x0);
		HDMI21Aud_WrFL(AUD_INTHW_ID0);

		HDMI21Aud_RdFL(AUD_INTHW_ID1);
		HDMI21Aud_Wr(AUD_INTHW_ID1, 0x0);
		HDMI21Aud_WrFL(AUD_INTHW_ID1);
	}
	return RET_OK;
}

int HDMI21_Rx_Audio_Path_Irq_Disable(void){
	int ret = RET_OK;

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
		if (NULL == g_pRealHDMI21AudioRegO22) {
			return RET_ERROR;
		}
		HDMI21AudO22_RdFL(AUD_INTHW_EN);
		HDMI21AudO22_Wr01(AUD_INTHW_EN, aud_inthw_en, 0x0);
		HDMI21AudO22_WrFL(AUD_INTHW_EN);
	}else{
		if (NULL == g_pRealHDMI21AudioReg) {
			return RET_ERROR;
		}
		HDMI21Aud_RdFL(AUD_INTHW_EN);
		HDMI21Aud_Wr01(AUD_INTHW_EN, aud_inthw_en, 0x0);
		HDMI21Aud_WrFL(AUD_INTHW_EN);
	}

	return ret;
}

int HDMI21_Rx_Audio_Path_Irq_Enable(void){
	int ret = RET_OK;

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
		if (NULL == g_pRealHDMI21AudioRegO22) {
			return RET_ERROR;
		}
		HDMI21AudO22_RdFL(AUD_INTHW_EN);
		HDMI21AudO22_Wr01(AUD_INTHW_EN, aud_inthw_en, 0x1);
		HDMI21AudO22_WrFL(AUD_INTHW_EN);
	}else{
		if (NULL == g_pRealHDMI21AudioReg) {
			return RET_ERROR;
		}
		HDMI21Aud_RdFL(AUD_INTHW_EN);
		HDMI21Aud_Wr01(AUD_INTHW_EN, aud_inthw_en, 0x1);
		HDMI21Aud_WrFL(AUD_INTHW_EN);
	}

	return ret;
}

int HDMI21_Rx_Audio_Path_Irq_Clear(void){
	int ret = RET_OK;

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
		if (NULL == g_pRealHDMI21AudioReg) {
			return RET_ERROR;
		}
		
		HDMI21AudO22_RdFL(AUD_INTHW_CLR);
		HDMI21AudO22_Wr01(AUD_INTHW_CLR, aud_inthw_clr, 0x1);
		HDMI21AudO22_WrFL(AUD_INTHW_CLR);

		HDMI21AudO22_RdFL(AUD_INTHW_CLR);
		HDMI21AudO22_Wr01(AUD_INTHW_CLR, aud_inthw_clr, 0x0);
		HDMI21AudO22_WrFL(AUD_INTHW_CLR);
	}else{
		if (NULL == g_pRealHDMI21AudioReg) {
			return RET_ERROR;
		}
		
		HDMI21Aud_RdFL(AUD_INTHW_CLR);
		HDMI21Aud_Wr01(AUD_INTHW_CLR, aud_inthw_clr, 0x1);
		HDMI21Aud_WrFL(AUD_INTHW_CLR);

		HDMI21Aud_RdFL(AUD_INTHW_CLR);
		HDMI21Aud_Wr01(AUD_INTHW_CLR, aud_inthw_clr, 0x0);
		HDMI21Aud_WrFL(AUD_INTHW_CLR);
	}

	return ret;
}

int HDMI21_Rx_Audio_Path_SetInthw(UINT8 port){
	int ret = RET_OK;
	UINT32 resetout;

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
		if (NULL == g_pRealHDMI21AudioRegO22) {
			return RET_ERROR;
		}
		HDMI21AudO22_RdFL(AUD_SWRESET);
		HDMI21AudO22_Rd01(AUD_SWRESET, apbresetout, resetout);

		if (resetout == 0){
			HDMI20_ERROR("HDMI Audio register is not ready!\n");
			gHDMI21RxHandler[port].isAudioRegReady = 0;
			return ret;
		}else{
			gHDMI21RxHandler[port].isAudioRegReady = 1;
			HDMI21AudO22_RdFL(AUD_INTHW_EN);
			HDMI21AudO22_Wr01(AUD_INTHW_EN, aud_inthw_en, 0x1);
			HDMI21AudO22_WrFL(AUD_INTHW_EN);

			HDMI21AudO22_RdFL(AUD_INTHW_MASK0);
			//HDMI21Aud_Wr01(AUD_INTHW_MASK0, reserved, 0xFFFFF);
			HDMI21AudO22_WrFL(AUD_INTHW_MASK0);
			HDMI21AudO22_RdFL(AUD_INTHW_MASK1);
			HDMI21AudO22_Wr01(AUD_INTHW_MASK1, reserved, 0x3);
			HDMI21AudO22_WrFL(AUD_INTHW_MASK1);



			if((port >= 0) && (port <= 2)) {
				HDMI21AudO22_RdFL(AUD_INTHW_MASK0);

				if (port == 0) {
					HDMI21AudO22_Wr02(AUD_INTHW_MASK0, hmr0spdif0csd_update_mask, 0, hmr0spdif0pc_update_mask, 0);
				}else if (port == 1) {
					HDMI21AudO22_Wr02(AUD_INTHW_MASK0, hmr1spdif0csd_update_mask, 0, hmr1spdif0pc_update_mask, 0);
				}else /* (port == 2)*/ {
					HDMI21AudO22_Wr02(AUD_INTHW_MASK0, hmr2spdif0csd_update_mask, 0, hmr2spdif0pc_update_mask, 0);
				}
				HDMI21AudO22_WrFL(AUD_INTHW_MASK0);
			}
			else if((port >= 3) && (port <= 4)) {
				HDMI21AudO22_RdFL(AUD_INTHW_MASK1);

				if(port == 3) {
					HDMI21AudO22_Wr02(AUD_INTHW_MASK1, hmr3spdif0csd_update_mask, 0, hmr3spdif0pc_update_mask, 0);
				}else if (( lx_chip_rev( ) < LX_CHIP_REV( E60, A0) ) || ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ))/*(port == 4)*/ {
					HDMI21AudO22_Wr02(AUD_INTHW_MASK1, hmr4spdif0csd_update_mask, 0, hmr4spdif0pc_update_mask, 0);
				}
				HDMI21AudO22_WrFL(AUD_INTHW_MASK1);
			}
			else {
				ret = RET_ERROR;
			}
		}
	}else{
		if (NULL == g_pRealHDMI21AudioReg) {
			return RET_ERROR;
		}
		HDMI21Aud_RdFL(AUD_SWRESET);
		HDMI21Aud_Rd01(AUD_SWRESET, apbresetout, resetout);

		if (resetout == 0){
			HDMI20_ERROR("HDMI Audio register is not ready!\n");
			gHDMI21RxHandler[port].isAudioRegReady = 0;
			return ret;
		}else{
			gHDMI21RxHandler[port].isAudioRegReady = 1;
			HDMI21Aud_RdFL(AUD_INTHW_EN);
			HDMI21Aud_Wr01(AUD_INTHW_EN, aud_inthw_en, 0x1);
			HDMI21Aud_WrFL(AUD_INTHW_EN);

			HDMI21Aud_RdFL(AUD_INTHW_MASK0);
			//HDMI21Aud_Wr01(AUD_INTHW_MASK0, reserved, 0xFFFFF);
			HDMI21Aud_WrFL(AUD_INTHW_MASK0);
			HDMI21Aud_RdFL(AUD_INTHW_MASK1);
			HDMI21Aud_Wr01(AUD_INTHW_MASK1, reserved, 0x3);
			HDMI21Aud_WrFL(AUD_INTHW_MASK1);



			if((port >= 0) && (port <= 2)) {
				HDMI21Aud_RdFL(AUD_INTHW_MASK0);

				if (port == 0) {
					HDMI21Aud_Wr02(AUD_INTHW_MASK0, hmr0spdif0csd_update_mask, 0, hmr0spdif0pc_update_mask, 0);
				}else if (port == 1) {
					HDMI21Aud_Wr02(AUD_INTHW_MASK0, hmr1spdif0csd_update_mask, 0, hmr1spdif0pc_update_mask, 0);
				}else /* (port == 2)*/ {
					HDMI21Aud_Wr02(AUD_INTHW_MASK0, hmr2spdif0csd_update_mask, 0, hmr2spdif0pc_update_mask, 0);
				}
				HDMI21Aud_WrFL(AUD_INTHW_MASK0);
			}
			else if((port >= 3) && (port <= 4)) {
				HDMI21Aud_RdFL(AUD_INTHW_MASK1);

				if(port == 3) {
					HDMI21Aud_Wr02(AUD_INTHW_MASK1, hmr3spdif0csd_update_mask, 0, hmr3spdif0pc_update_mask, 0);
				}else if (( lx_chip_rev( ) < LX_CHIP_REV( E60, A0) ) || ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ))/*(port == 4)*/ {
					HDMI21Aud_Wr02(AUD_INTHW_MASK1, hmr4spdif0csd_update_mask, 0, hmr4spdif0pc_update_mask, 0);
				}
				HDMI21Aud_WrFL(AUD_INTHW_MASK1);
			}
			else {
				ret = RET_ERROR;
			}
		}
	}

	return ret;
}

int HDMI21_Rx_Audio_Path_InthwUnmask(UINT8 port){
	int ret = RET_OK;

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
		if (NULL == g_pRealHDMI21AudioRegO22) {
			return RET_ERROR;
		}
		HDMI21AudO22_RdFL(AUD_INTHW_MASK0);
		//HDMI21Aud_Wr01(AUD_INTHW_MASK0, reserved, 0xFFFFF);
		HDMI21AudO22_WrFL(AUD_INTHW_MASK0);

		HDMI21AudO22_RdFL(AUD_INTHW_MASK1);
		HDMI21AudO22_Wr01(AUD_INTHW_MASK1, reserved, 0x3);
		HDMI21AudO22_WrFL(AUD_INTHW_MASK1);

		HDMI21AudO22_RdFL(AUD_INTHW_MASK0);
		if (port == 0) {
			HDMI21AudO22_Wr02(AUD_INTHW_MASK0, hmr0spdif0csd_update_mask, 1, hmr0spdif0pc_update_mask, 1);
		}else if (port == 1) {
			HDMI21AudO22_Wr02(AUD_INTHW_MASK0, hmr1spdif0csd_update_mask, 1, hmr1spdif0pc_update_mask, 1);
		}else if(port == 2) {
			HDMI21AudO22_Wr02(AUD_INTHW_MASK0, hmr2spdif0csd_update_mask, 1, hmr2spdif0pc_update_mask, 1);
		}else {
			HDMI20_ERROR("HDMI Audio port number is wrong\n");
			return RET_ERROR;
		}
		HDMI21AudO22_WrFL(AUD_INTHW_MASK0);

		HDMI21AudO22_RdFL(AUD_INTHW_MASK1);
		if(port == 3) {
			HDMI21AudO22_Wr02(AUD_INTHW_MASK1, hmr3spdif0csd_update_mask, 1, hmr3spdif0pc_update_mask, 1);
		}else if((port == 4 && ( lx_chip_rev( ) < LX_CHIP_REV( E60, A0))) || (port == 4 && ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0)))) {
			HDMI21AudO22_Wr02(AUD_INTHW_MASK1, hmr4spdif0csd_update_mask, 1, hmr4spdif0pc_update_mask, 1);
		}else {
			HDMI20_ERROR("HDMI Audio port number is wrong\n");
			return RET_ERROR;
		}
		HDMI21AudO22_WrFL(AUD_INTHW_MASK1);
	}else{
		if (NULL == g_pRealHDMI21AudioReg) {
			return RET_ERROR;
		}
		HDMI21Aud_RdFL(AUD_INTHW_MASK0);
		//HDMI21Aud_Wr01(AUD_INTHW_MASK0, reserved, 0xFFFFF);
		HDMI21Aud_WrFL(AUD_INTHW_MASK0);

		HDMI21Aud_RdFL(AUD_INTHW_MASK1);
		HDMI21Aud_Wr01(AUD_INTHW_MASK1, reserved, 0x3);
		HDMI21Aud_WrFL(AUD_INTHW_MASK1);

		HDMI21Aud_RdFL(AUD_INTHW_MASK0);
		if (port == 0) {
			HDMI21Aud_Wr02(AUD_INTHW_MASK0, hmr0spdif0csd_update_mask, 1, hmr0spdif0pc_update_mask, 1);
		}else if (port == 1) {
			HDMI21Aud_Wr02(AUD_INTHW_MASK0, hmr1spdif0csd_update_mask, 1, hmr1spdif0pc_update_mask, 1);
		}else if(port == 2) {
			HDMI21Aud_Wr02(AUD_INTHW_MASK0, hmr2spdif0csd_update_mask, 1, hmr2spdif0pc_update_mask, 1);
		}else {
			HDMI20_ERROR("HDMI Audio port number is wrong\n");
			return RET_ERROR;
		}
		HDMI21Aud_WrFL(AUD_INTHW_MASK0);

		HDMI21Aud_RdFL(AUD_INTHW_MASK1);
		if(port == 3) {
			HDMI21Aud_Wr02(AUD_INTHW_MASK1, hmr3spdif0csd_update_mask, 1, hmr3spdif0pc_update_mask, 1);
		}else if((port == 4 && ( lx_chip_rev( ) < LX_CHIP_REV( E60, A0))) || (port == 4 && ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0)))) {
			HDMI21Aud_Wr02(AUD_INTHW_MASK1, hmr4spdif0csd_update_mask, 1, hmr4spdif0pc_update_mask, 1);
		}else {
			HDMI20_ERROR("HDMI Audio port number is wrong\n");
			return RET_ERROR;
		}
		HDMI21Aud_WrFL(AUD_INTHW_MASK1);
	}

	return ret;
}

int HDMI21_Rx_Audio_Path_GetSPDIFInfo(UINT8 port, HDMI21_AUDIO_REG_DATA *pHDMI21AudioRegData){
	int ret = RET_OK;
	UINT32 byte0, byte1, byte2, byte3, byte4, byte5, pc;

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
		if (NULL == g_pRealHDMI21AudioRegO22) {
			return RET_ERROR;
		} else {
			if(port == 0) {
				HDMI21AudO22_RdFL(AUD_HMR0_CSD0_0);
				HDMI21AudO22_Rd01(AUD_HMR0_CSD0_0, HDMI0_CSD0_0, byte0);
				HDMI21AudO22_RdFL(AUD_HMR0_CSD1_0);
				HDMI21AudO22_Rd01(AUD_HMR0_CSD1_0, HDMI0_CSD1_0, byte1);
				HDMI21AudO22_RdFL(AUD_HMR0_CSD2_0);
				HDMI21AudO22_Rd01(AUD_HMR0_CSD2_0, HDMI0_CSD2_0, byte2);
				HDMI21AudO22_RdFL(AUD_HMR0_CSD3_0);
				HDMI21AudO22_Rd01(AUD_HMR0_CSD3_0, HDMI0_CSD3_0, byte3);
				HDMI21AudO22_RdFL(AUD_HMR0_CSD4_0);
				HDMI21AudO22_Rd01(AUD_HMR0_CSD4_0, HDMI0_CSD4_0, byte4);
				HDMI21AudO22_RdFL(AUD_HMR0_CSD5_0);
				HDMI21AudO22_Rd01(AUD_HMR0_CSD5_0, HDMI0_CSD5_0, byte5);
				HDMI21AudO22_RdFL(AUD_HMR0_PCPD_0);
				HDMI21AudO22_Rd01(AUD_HMR0_PCPD_0, HMR0pc_0, pc);
			}else if(port == 1) {
				HDMI21AudO22_RdFL(AUD_HMR1_CSD0_0);
				HDMI21AudO22_Rd01(AUD_HMR1_CSD0_0, HDMI1_CSD0_0, byte0);
				HDMI21AudO22_RdFL(AUD_HMR1_CSD1_0);
				HDMI21AudO22_Rd01(AUD_HMR1_CSD1_0, HDMI1_CSD1_0, byte1);
				HDMI21AudO22_RdFL(AUD_HMR1_CSD2_0);
				HDMI21AudO22_Rd01(AUD_HMR1_CSD2_0, HDMI1_CSD2_0, byte2);
				HDMI21AudO22_RdFL(AUD_HMR1_CSD3_0);
				HDMI21AudO22_Rd01(AUD_HMR1_CSD3_0, HDMI1_CSD3_0, byte3);
				HDMI21AudO22_RdFL(AUD_HMR1_CSD4_0);
				HDMI21AudO22_Rd01(AUD_HMR1_CSD4_0, HDMI1_CSD4_0, byte4);
				HDMI21AudO22_RdFL(AUD_HMR1_CSD5_0);
				HDMI21AudO22_Rd01(AUD_HMR1_CSD5_0, HDMI1_CSD5_0, byte5);
				HDMI21AudO22_RdFL(AUD_HMR1_PCPD_0);
				HDMI21AudO22_Rd01(AUD_HMR1_PCPD_0, HMR1pc_0, pc);
			}else if(port == 2) {
				HDMI21AudO22_RdFL(AUD_HMR2_CSD0_0);
				HDMI21AudO22_Rd01(AUD_HMR2_CSD0_0, HDMI2_CSD0_0, byte0);
				HDMI21AudO22_RdFL(AUD_HMR2_CSD1_0);
				HDMI21AudO22_Rd01(AUD_HMR2_CSD1_0, HDMI2_CSD1_0, byte1);
				HDMI21AudO22_RdFL(AUD_HMR2_CSD2_0);
				HDMI21AudO22_Rd01(AUD_HMR2_CSD2_0, HDMI2_CSD2_0, byte2);
				HDMI21AudO22_RdFL(AUD_HMR2_CSD3_0);
				HDMI21AudO22_Rd01(AUD_HMR2_CSD3_0, HDMI2_CSD3_0, byte3);
				HDMI21AudO22_RdFL(AUD_HMR2_CSD4_0);
				HDMI21AudO22_Rd01(AUD_HMR2_CSD4_0, HDMI2_CSD4_0, byte4);
				HDMI21AudO22_RdFL(AUD_HMR2_CSD5_0);
				HDMI21AudO22_Rd01(AUD_HMR2_CSD5_0, HDMI2_CSD5_0, byte5);
				HDMI21AudO22_RdFL(AUD_HMR2_PCPD_0);
				HDMI21AudO22_Rd01(AUD_HMR2_PCPD_0, HMR2pc_0, pc);
			}else if(port == 3) {
				HDMI21AudO22_RdFL(AUD_HMR3_CSD0_0);
				HDMI21AudO22_Rd01(AUD_HMR3_CSD0_0, HDMI3_CSD0_0, byte0);
				HDMI21AudO22_RdFL(AUD_HMR3_CSD1_0);
				HDMI21AudO22_Rd01(AUD_HMR3_CSD1_0, HDMI3_CSD1_0, byte1);
				HDMI21AudO22_RdFL(AUD_HMR3_CSD2_0);
				HDMI21AudO22_Rd01(AUD_HMR3_CSD2_0, HDMI3_CSD2_0, byte2);
				HDMI21AudO22_RdFL(AUD_HMR3_CSD3_0);
				HDMI21AudO22_Rd01(AUD_HMR3_CSD3_0, HDMI3_CSD3_0, byte3);
				HDMI21AudO22_RdFL(AUD_HMR3_CSD4_0);
				HDMI21AudO22_Rd01(AUD_HMR3_CSD4_0, HDMI3_CSD4_0, byte4);
				HDMI21AudO22_RdFL(AUD_HMR3_CSD5_0);
				HDMI21AudO22_Rd01(AUD_HMR3_CSD5_0, HDMI3_CSD5_0, byte5);
				HDMI21AudO22_RdFL(AUD_HMR3_PCPD_0);
				HDMI21AudO22_Rd01(AUD_HMR3_PCPD_0, HMR3pc_0, pc);
			}else if((port == 4 && ( lx_chip_rev( ) < LX_CHIP_REV( E60, A0))) || (port == 4 && ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0)))) {
				HDMI21AudO22_RdFL(AUD_HMR4_CSD0_0);
				HDMI21AudO22_Rd01(AUD_HMR4_CSD0_0, HDMI4_CSD0_0, byte0);
				HDMI21AudO22_RdFL(AUD_HMR4_CSD1_0);
				HDMI21AudO22_Rd01(AUD_HMR4_CSD1_0, HDMI4_CSD1_0, byte1);
				HDMI21AudO22_RdFL(AUD_HMR4_CSD2_0);
				HDMI21AudO22_Rd01(AUD_HMR4_CSD2_0, HDMI4_CSD2_0, byte2);
				HDMI21AudO22_RdFL(AUD_HMR4_CSD3_0);
				HDMI21AudO22_Rd01(AUD_HMR4_CSD3_0, HDMI4_CSD3_0, byte3);
				HDMI21AudO22_RdFL(AUD_HMR4_CSD4_0);
				HDMI21AudO22_Rd01(AUD_HMR4_CSD4_0, HDMI4_CSD4_0, byte4);
				HDMI21AudO22_RdFL(AUD_HMR4_CSD5_0);
				HDMI21AudO22_Rd01(AUD_HMR4_CSD5_0, HDMI4_CSD5_0, byte5);
				HDMI21AudO22_RdFL(AUD_HMR4_PCPD_0);
				HDMI21AudO22_Rd01(AUD_HMR4_PCPD_0, HMR4pc_0, pc);
			}else {
				HDMI20_ERROR("HDMI Audio port number is wrong\n");
				return RET_ERROR;
			}
			
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_DATA].value != 0x0)HDMI20_ADEF("HDMI[%d] Audio CSD info byte0(0x%x->0x%x) byte1(0x%x->0x%x) byte2(0x%x->0x%x) byte3(0x%x->0x%x) byte4(0x%x->0x%x) byte5(0x%x->0x%x) \n",\
			port, _gHDMI21AudioRegData.byte0, byte0&0xF, _gHDMI21AudioRegData.byte1, byte1&0xF, _gHDMI21AudioRegData.byte2, byte2&0xF, _gHDMI21AudioRegData.byte3, byte3&0xF, _gHDMI21AudioRegData.byte4, byte4&0xF, _gHDMI21AudioRegData.byte5, byte5&0xF);
			
			_gHDMI21AudioRegData.byte0 = byte0 & 0xF;
			_gHDMI21AudioRegData.byte1 = byte1 & 0xF;
			_gHDMI21AudioRegData.byte2 = byte2 & 0xF;
			_gHDMI21AudioRegData.byte3 = byte3 & 0xF;
			_gHDMI21AudioRegData.byte4 = byte4 & 0xF;
			_gHDMI21AudioRegData.byte5 = byte5 & 0xF;
			_gHDMI21AudioRegData.pcpd = pc & 0xFFFF;

			pHDMI21AudioRegData->byte0 = byte0 & 0xF;
			pHDMI21AudioRegData->byte1 = byte1 & 0xF;
			pHDMI21AudioRegData->pcpd = pc & 0xFFFF;

		}
	}else{
		if (NULL == g_pRealHDMI21AudioReg) {
			return RET_ERROR;
		} else {
			if(port == 0) {
				HDMI21Aud_RdFL(AUD_HMR0_CSD0_0);
				HDMI21Aud_Rd01(AUD_HMR0_CSD0_0, HDMI0_CSD0_0, byte0);
				HDMI21Aud_RdFL(AUD_HMR0_CSD1_0);
				HDMI21Aud_Rd01(AUD_HMR0_CSD1_0, HDMI0_CSD1_0, byte1);
				HDMI21Aud_RdFL(AUD_HMR0_PCPD_0);
				HDMI21Aud_Rd01(AUD_HMR0_PCPD_0, HMR0pc_0, pc);
			}else if(port == 1) {
				HDMI21Aud_RdFL(AUD_HMR1_CSD0_0);
				HDMI21Aud_Rd01(AUD_HMR1_CSD0_0, HDMI1_CSD0_0, byte0);
				HDMI21Aud_RdFL(AUD_HMR1_CSD1_0);
				HDMI21Aud_Rd01(AUD_HMR1_CSD1_0, HDMI1_CSD1_0, byte1);
				HDMI21Aud_RdFL(AUD_HMR1_PCPD_0);
				HDMI21Aud_Rd01(AUD_HMR1_PCPD_0, HMR1pc_0, pc);
			}else if(port == 2) {
				HDMI21Aud_RdFL(AUD_HMR2_CSD0_0);
				HDMI21Aud_Rd01(AUD_HMR2_CSD0_0, HDMI2_CSD0_0, byte0);
				HDMI21Aud_RdFL(AUD_HMR2_CSD1_0);
				HDMI21Aud_Rd01(AUD_HMR2_CSD1_0, HDMI2_CSD1_0, byte1);
				HDMI21Aud_RdFL(AUD_HMR2_PCPD_0);
				HDMI21Aud_Rd01(AUD_HMR2_PCPD_0, HMR2pc_0, pc);
			}else if(port == 3) {
				HDMI21Aud_RdFL(AUD_HMR3_CSD0_0);
				HDMI21Aud_Rd01(AUD_HMR3_CSD0_0, HDMI3_CSD0_0, byte0);
				HDMI21Aud_RdFL(AUD_HMR3_CSD1_0);
				HDMI21Aud_Rd01(AUD_HMR3_CSD1_0, HDMI3_CSD1_0, byte1);
				HDMI21Aud_RdFL(AUD_HMR3_PCPD_0);
				HDMI21Aud_Rd01(AUD_HMR3_PCPD_0, HMR3pc_0, pc);
			}else if((port == 4 && ( lx_chip_rev( ) < LX_CHIP_REV( E60, A0))) || (port == 4 && ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0)))) {
				HDMI21Aud_RdFL(AUD_HMR4_CSD0_0);
				HDMI21Aud_Rd01(AUD_HMR4_CSD0_0, HDMI4_CSD0_0, byte0);
				HDMI21Aud_RdFL(AUD_HMR4_CSD1_0);
				HDMI21Aud_Rd01(AUD_HMR4_CSD1_0, HDMI4_CSD1_0, byte1);
				HDMI21Aud_RdFL(AUD_HMR4_PCPD_0);
				HDMI21Aud_Rd01(AUD_HMR4_PCPD_0, HMR4pc_0, pc);
			}else {
				HDMI20_ERROR("HDMI Audio port number is wrong\n");
				return RET_ERROR;
			}

			pHDMI21AudioRegData->byte0 = byte0 & 0xF;
			pHDMI21AudioRegData->byte1 = byte1 & 0xF;
			pHDMI21AudioRegData->pcpd = pc & 0xFFFF;
		}
	}

	return ret;
}

int HDMI21_Rx_Audio_Path_SetMute(UINT8 port){

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
		if (NULL == g_pRealHDMI21AudioRegO22) {
			return RET_ERROR;
		}
		if (port == 0) {
			HDMI21AudO22_RdFL(AUD_HMR0_MUTE);
			HDMI21AudO22_Wr01(AUD_HMR0_MUTE, HMR0mute, 0x1);
			HDMI21AudO22_WrFL(AUD_HMR0_MUTE);
		}else if (port == 1) {
			HDMI21AudO22_RdFL(AUD_HMR1_MUTE);
			HDMI21AudO22_Wr01(AUD_HMR1_MUTE, HMR1mute, 0x1);
			HDMI21AudO22_WrFL(AUD_HMR1_MUTE);
		}else if(port == 2) {
			HDMI21AudO22_RdFL(AUD_HMR2_MUTE);
			HDMI21AudO22_Wr01(AUD_HMR2_MUTE, HMR2mute, 0x1);
			HDMI21AudO22_WrFL(AUD_HMR2_MUTE);
		}else if(port == 3) {
			HDMI21AudO22_RdFL(AUD_HMR3_MUTE);
			HDMI21AudO22_Wr01(AUD_HMR3_MUTE, HMR3mute, 0x1);
			HDMI21AudO22_WrFL(AUD_HMR3_MUTE);
		}else if((port == 4 && ( lx_chip_rev( ) < LX_CHIP_REV( E60, A0))) || (port == 4 && ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0)))) {
			HDMI21AudO22_RdFL(AUD_HMR4_MUTE);
			HDMI21AudO22_Wr01(AUD_HMR4_MUTE, HMR4mute, 0x1);
			HDMI21AudO22_WrFL(AUD_HMR4_MUTE);
		}else {
			HDMI20_ERROR("HDMI Audio port number is wrong\n");
			return RET_ERROR;
		}
	}else{
		if (NULL == g_pRealHDMI21AudioReg) {
			return RET_ERROR;
		}
		if (port == 0) {
			HDMI21Aud_RdFL(AUD_HMR0_MUTE);
			HDMI21Aud_Wr01(AUD_HMR0_MUTE, HMR0mute, 0x1);
			HDMI21Aud_WrFL(AUD_HMR0_MUTE);
		}else if (port == 1) {
			HDMI21Aud_RdFL(AUD_HMR1_MUTE);
			HDMI21Aud_Wr01(AUD_HMR1_MUTE, HMR1mute, 0x1);
			HDMI21Aud_WrFL(AUD_HMR1_MUTE);
		}else if(port == 2) {
			HDMI21Aud_RdFL(AUD_HMR2_MUTE);
			HDMI21Aud_Wr01(AUD_HMR2_MUTE, HMR2mute, 0x1);
			HDMI21Aud_WrFL(AUD_HMR2_MUTE);
		}else if(port == 3) {
			HDMI21Aud_RdFL(AUD_HMR3_MUTE);
			HDMI21Aud_Wr01(AUD_HMR3_MUTE, HMR3mute, 0x1);
			HDMI21Aud_WrFL(AUD_HMR3_MUTE);
		}else if((port == 4 && ( lx_chip_rev( ) < LX_CHIP_REV( E60, A0))) || (port == 4 && ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0)))) {
			HDMI21Aud_RdFL(AUD_HMR4_MUTE);
			HDMI21Aud_Wr01(AUD_HMR4_MUTE, HMR4mute, 0x1);
			HDMI21Aud_WrFL(AUD_HMR4_MUTE);
		}else {
			HDMI20_ERROR("HDMI Audio port number is wrong\n");
			return RET_ERROR;
		}
	}

	return RET_OK;
}
int HDMI21_Rx_Audio_Path_SetUnmute(UINT8 port){
	if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
		if (NULL == g_pRealHDMI21AudioRegO22) {
			return RET_ERROR;
		}
		if (port == 0) {
			HDMI21AudO22_RdFL(AUD_HMR0_MUTE);
			HDMI21AudO22_Wr01(AUD_HMR0_MUTE, HMR0mute, 0x0);
			HDMI21AudO22_WrFL(AUD_HMR0_MUTE);
		}else if (port == 1) {
			HDMI21AudO22_RdFL(AUD_HMR1_MUTE);
			HDMI21AudO22_Wr01(AUD_HMR1_MUTE, HMR1mute, 0x0);
			HDMI21AudO22_WrFL(AUD_HMR1_MUTE);
		}else if(port == 2) {
			HDMI21AudO22_RdFL(AUD_HMR2_MUTE);
			HDMI21AudO22_Wr01(AUD_HMR2_MUTE, HMR2mute, 0x0);
			HDMI21AudO22_WrFL(AUD_HMR2_MUTE);
		}else if(port == 3) {
			HDMI21AudO22_RdFL(AUD_HMR3_MUTE);
			HDMI21AudO22_Wr01(AUD_HMR3_MUTE, HMR3mute, 0x0);
			HDMI21AudO22_WrFL(AUD_HMR3_MUTE);
		}else if((port == 4 && ( lx_chip_rev( ) < LX_CHIP_REV( E60, A0))) || (port == 4 && ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0)))) {
			HDMI21AudO22_RdFL(AUD_HMR4_MUTE);
			HDMI21AudO22_Wr01(AUD_HMR4_MUTE, HMR4mute, 0x0);
			HDMI21AudO22_WrFL(AUD_HMR4_MUTE);
		}else {
			HDMI20_ERROR("HDMI Audio port number is wrong\n");
			return RET_ERROR;
		}
	}else{
		if (NULL == g_pRealHDMI21AudioReg) {
			return RET_ERROR;
		}
		if (port == 0) {
			HDMI21Aud_RdFL(AUD_HMR0_MUTE);
			HDMI21Aud_Wr01(AUD_HMR0_MUTE, HMR0mute, 0x0);
			HDMI21Aud_WrFL(AUD_HMR0_MUTE);
		}else if (port == 1) {
			HDMI21Aud_RdFL(AUD_HMR1_MUTE);
			HDMI21Aud_Wr01(AUD_HMR1_MUTE, HMR1mute, 0x0);
			HDMI21Aud_WrFL(AUD_HMR1_MUTE);
		}else if(port == 2) {
			HDMI21Aud_RdFL(AUD_HMR2_MUTE);
			HDMI21Aud_Wr01(AUD_HMR2_MUTE, HMR2mute, 0x0);
			HDMI21Aud_WrFL(AUD_HMR2_MUTE);
		}else if(port == 3) {
			HDMI21Aud_RdFL(AUD_HMR3_MUTE);
			HDMI21Aud_Wr01(AUD_HMR3_MUTE, HMR3mute, 0x0);
			HDMI21Aud_WrFL(AUD_HMR3_MUTE);
		}else if((port == 4 && ( lx_chip_rev( ) < LX_CHIP_REV( E60, A0))) || (port == 4 && ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0)))) {
			HDMI21Aud_RdFL(AUD_HMR4_MUTE);
			HDMI21Aud_Wr01(AUD_HMR4_MUTE, HMR4mute, 0x0);
			HDMI21Aud_WrFL(AUD_HMR4_MUTE);
		}else {
			HDMI20_ERROR("HDMI Audio port number is wrong\n");
			return RET_ERROR;
		}
	}

	return RET_OK;
}
#if 1
int HDMI21_Rx_Audio_Path_PcPdReset(UINT8 port){
	if (NULL == g_pRealHDMI21AudioRegO22) {
		return RET_ERROR;
	}

	if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){ 
		if (port == 0) {
			HDMI21AudO22_RdFL(AUD_HMR0_PCPD_0_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR0_PCPD_0_CLEAR, CLEAR_HMR0pc_0, 0x1);
			HDMI21AudO22_WrFL(AUD_HMR0_PCPD_0_CLEAR);
			HDMI21AudO22_RdFL(AUD_HMR0_PCPD_1_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR0_PCPD_1_CLEAR, CLEAR_HMR0pc_1, 0x1);
			HDMI21AudO22_WrFL(AUD_HMR0_PCPD_1_CLEAR);
			HDMI21AudO22_RdFL(AUD_HMR0_PCPD_2_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR0_PCPD_2_CLEAR, CLEAR_HMR0pc_2, 0x1);
			HDMI21AudO22_WrFL(AUD_HMR0_PCPD_2_CLEAR);
			HDMI21AudO22_RdFL(AUD_HMR0_PCPD_3_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR0_PCPD_3_CLEAR, CLEAR_HMR0pc_3, 0x1);
			HDMI21AudO22_WrFL(AUD_HMR0_PCPD_3_CLEAR);

			HDMI21AudO22_RdFL(AUD_HMR0_PCPD_0_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR0_PCPD_0_CLEAR, CLEAR_HMR0pc_0, 0x0);
			HDMI21AudO22_WrFL(AUD_HMR0_PCPD_0_CLEAR);
			HDMI21AudO22_RdFL(AUD_HMR0_PCPD_1_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR0_PCPD_1_CLEAR, CLEAR_HMR0pc_1, 0x0);
			HDMI21AudO22_WrFL(AUD_HMR0_PCPD_1_CLEAR);
			HDMI21AudO22_RdFL(AUD_HMR0_PCPD_2_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR0_PCPD_2_CLEAR, CLEAR_HMR0pc_2, 0x0);
			HDMI21AudO22_WrFL(AUD_HMR0_PCPD_2_CLEAR);
			HDMI21AudO22_RdFL(AUD_HMR0_PCPD_3_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR0_PCPD_3_CLEAR, CLEAR_HMR0pc_3, 0x0);
			HDMI21AudO22_WrFL(AUD_HMR0_PCPD_3_CLEAR);
		}else if (port == 1) {
			HDMI21AudO22_RdFL(AUD_HMR1_PCPD_0_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR1_PCPD_0_CLEAR, CLEAR_HMR1pc_0, 0x1);
			HDMI21AudO22_WrFL(AUD_HMR1_PCPD_0_CLEAR);
			HDMI21AudO22_RdFL(AUD_HMR1_PCPD_1_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR1_PCPD_1_CLEAR, CLEAR_HMR1pc_1, 0x1);
			HDMI21AudO22_WrFL(AUD_HMR1_PCPD_1_CLEAR);
			HDMI21AudO22_RdFL(AUD_HMR1_PCPD_2_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR1_PCPD_2_CLEAR, CLEAR_HMR1pc_2, 0x1);
			HDMI21AudO22_WrFL(AUD_HMR1_PCPD_2_CLEAR);
			HDMI21AudO22_RdFL(AUD_HMR1_PCPD_3_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR1_PCPD_3_CLEAR, CLEAR_HMR1pc_3, 0x1);
			HDMI21AudO22_WrFL(AUD_HMR1_PCPD_3_CLEAR);

			HDMI21AudO22_RdFL(AUD_HMR1_PCPD_0_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR1_PCPD_0_CLEAR, CLEAR_HMR1pc_0, 0x0);
			HDMI21AudO22_WrFL(AUD_HMR1_PCPD_0_CLEAR);
			HDMI21AudO22_RdFL(AUD_HMR1_PCPD_1_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR1_PCPD_1_CLEAR, CLEAR_HMR1pc_1, 0x0);
			HDMI21AudO22_WrFL(AUD_HMR1_PCPD_1_CLEAR);
			HDMI21AudO22_RdFL(AUD_HMR1_PCPD_2_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR1_PCPD_2_CLEAR, CLEAR_HMR1pc_2, 0x0);
			HDMI21AudO22_WrFL(AUD_HMR1_PCPD_2_CLEAR);
			HDMI21AudO22_RdFL(AUD_HMR1_PCPD_3_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR1_PCPD_3_CLEAR, CLEAR_HMR1pc_3, 0x0);
			HDMI21AudO22_WrFL(AUD_HMR1_PCPD_3_CLEAR);
		}else if(port == 2) {
			HDMI21AudO22_RdFL(AUD_HMR2_PCPD_0_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR2_PCPD_0_CLEAR, CLEAR_HMR2pc_0, 0x1);
			HDMI21AudO22_WrFL(AUD_HMR2_PCPD_0_CLEAR);
			HDMI21AudO22_RdFL(AUD_HMR2_PCPD_1_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR2_PCPD_1_CLEAR, CLEAR_HMR2pc_1, 0x1);
			HDMI21AudO22_WrFL(AUD_HMR2_PCPD_1_CLEAR);
			HDMI21AudO22_RdFL(AUD_HMR2_PCPD_2_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR2_PCPD_2_CLEAR, CLEAR_HMR2pc_2, 0x1);
			HDMI21AudO22_WrFL(AUD_HMR2_PCPD_2_CLEAR);
			HDMI21AudO22_RdFL(AUD_HMR2_PCPD_3_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR2_PCPD_3_CLEAR, CLEAR_HMR2pc_3, 0x1);
			HDMI21AudO22_WrFL(AUD_HMR2_PCPD_3_CLEAR);

			HDMI21AudO22_RdFL(AUD_HMR2_PCPD_0_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR2_PCPD_0_CLEAR, CLEAR_HMR2pc_0, 0x0);
			HDMI21AudO22_WrFL(AUD_HMR2_PCPD_0_CLEAR);
			HDMI21AudO22_RdFL(AUD_HMR2_PCPD_1_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR2_PCPD_1_CLEAR, CLEAR_HMR2pc_1, 0x0);
			HDMI21AudO22_WrFL(AUD_HMR2_PCPD_1_CLEAR);
			HDMI21AudO22_RdFL(AUD_HMR2_PCPD_2_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR2_PCPD_2_CLEAR, CLEAR_HMR2pc_2, 0x0);
			HDMI21AudO22_WrFL(AUD_HMR2_PCPD_2_CLEAR);
			HDMI21AudO22_RdFL(AUD_HMR2_PCPD_3_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR2_PCPD_3_CLEAR, CLEAR_HMR2pc_3, 0x0);
			HDMI21AudO22_WrFL(AUD_HMR2_PCPD_3_CLEAR);
		}else if(port == 3) {
			HDMI21AudO22_RdFL(AUD_HMR3_PCPD_0_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR3_PCPD_0_CLEAR, CLEAR_HMR3pc_0, 0x1);
			HDMI21AudO22_WrFL(AUD_HMR3_PCPD_0_CLEAR);
			HDMI21AudO22_RdFL(AUD_HMR3_PCPD_1_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR3_PCPD_1_CLEAR, CLEAR_HMR3pc_1, 0x1);
			HDMI21AudO22_WrFL(AUD_HMR3_PCPD_1_CLEAR);
			HDMI21AudO22_RdFL(AUD_HMR3_PCPD_2_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR3_PCPD_2_CLEAR, CLEAR_HMR3pc_2, 0x1);
			HDMI21AudO22_WrFL(AUD_HMR3_PCPD_2_CLEAR);
			HDMI21AudO22_RdFL(AUD_HMR3_PCPD_3_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR3_PCPD_3_CLEAR, CLEAR_HMR3pc_3, 0x1);
			HDMI21AudO22_WrFL(AUD_HMR3_PCPD_3_CLEAR);

			HDMI21AudO22_RdFL(AUD_HMR3_PCPD_0_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR3_PCPD_0_CLEAR, CLEAR_HMR3pc_0, 0x0);
			HDMI21AudO22_WrFL(AUD_HMR3_PCPD_0_CLEAR);
			HDMI21AudO22_RdFL(AUD_HMR3_PCPD_1_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR3_PCPD_1_CLEAR, CLEAR_HMR3pc_1, 0x0);
			HDMI21AudO22_WrFL(AUD_HMR3_PCPD_1_CLEAR);
			HDMI21AudO22_RdFL(AUD_HMR3_PCPD_2_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR3_PCPD_2_CLEAR, CLEAR_HMR3pc_2, 0x0);
			HDMI21AudO22_WrFL(AUD_HMR3_PCPD_2_CLEAR);
			HDMI21AudO22_RdFL(AUD_HMR3_PCPD_3_CLEAR);
			HDMI21AudO22_Wr01(AUD_HMR3_PCPD_3_CLEAR, CLEAR_HMR3pc_3, 0x0);
			HDMI21AudO22_WrFL(AUD_HMR3_PCPD_3_CLEAR);
		}else {
			HDMI20_ERROR("HDMI Audio port number is wrong\n");
			return RET_ERROR;
		}
	}

	return RET_OK;
}
#endif
