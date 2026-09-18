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
#include <linux/kernel.h>
#include <linux/delay.h>

#include "hdmi20_rx_audio.h"

#include "hdmi20_hal_driver.h"
#include "hdmi20_rx_disland.h" /* Data island control */
#include "./synopsys_api/hdmi_rx_ctrl.h"
#include "../hdmi20_drv.h"

#include "hdmi_kapi.h"

#include "os_util.h"
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define HDMI20_HAL_ACR_N_MARGIN 100
#define HDMI20_HAL_ACR_CTS_MARGIN 500

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#ifndef E_TO_S
#define E_TO_S(x) #x
#endif

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern HDMI20_HAL_RX_DEVICE_DATA gHDMI20RxHandler[HDMI20_NUM_OF_RX_PORTS];
extern HDMI20_DEV_CONTROL_T	gHDMI20RxDevControler[HDMI20__DEV_CONTROL_LIST_MAXNUM];

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
static LX_HDMI_AUDIO_INFO_ACR_T _gHdmiAudioInfoACR[HDMI20_NUM_OF_RX_PORTS] = { \
	{0, 0}, \
	{0, 0}, \
	{0, 0}, \
	{0, 0} };



/* Device controler : This contols the behavior of the Driver */
HDMI20_DEV_CONTROL_T	gHDMI20RxDevAudControler[HDMI20__DEV_AUD_CONTROL_LIST_MAXNUM]=
{
	/* DBG */
	{E_TO_S(HDMI20__AUD_DEBUG), 				0x0,		"====== [Debug] ========="},
	{E_TO_S(HDMI20__AUD_LINE_DBG), 				0x0,		"Activating specific conditions"},
	{E_TO_S(HDMI20__AUD_CNT_DBG), 				0x0,		"Audio count log enable"},
	{E_TO_S(HDMI20__AUD_IRQ_DBG), 				0x0,		"Audio interrupt log enable"},
	{E_TO_S(HDMI20__AUD_CSD_IRQ_DBG), 			0x0,		"Audio CSD interrupt log enable"},

	/* Count */
	{E_TO_S(HDMI20__AUD_COUNT), 				0x0,		"====== [Count] ========="},
	{E_TO_S(HDMI20__AUD_STANDBY_TIME),			0x5,		"Audio stand by time"},
	{E_TO_S(HDMI20__AUD_STABLE_TIME),			HDMI20_AUDIO_STABLE_CNT_INITIAL,		"Audio stable time"},
	{E_TO_S(HDMI20__AUD_STABLE),				(HDMI20_AUDIO_STABLE_CNT_INITIAL-1),	"Audio stable"},
	{E_TO_S(HDMI20__AUD_FIFO_ERR_MUTE_TIME),	0x9,		"Audio FIFO error mute time"},
	{E_TO_S(HDMI20__AUD_CH_MAP_STANDBY_TIME),	0xF,		"Audio channel mapping stand by time"},
	{E_TO_S(HDMI20__AUD_CH_MAP_MAX),			0x5,		"Audio channel mapping max"},
	{E_TO_S(HDMI20__AUD_IRQ_FIFO_ERR_MAX),		0x8,		"Audio interrupt FIFO error max"},
	{E_TO_S(HDMI20__AUD_ACR_ERR_MAX),			0xA,		"Audio ACR error max"},
	{E_TO_S(HDMI20__AUD_FORCE_MUTE_TIME),		0x17,		"Audio force mute time"},
	{E_TO_S(HDMI20__AUD_ACR_RESET_TIME),		0x1,		"Audio ACR reset time"},

	/* Control */
	{E_TO_S(HDMI20__AUD_CONTROL), 				0x0,		"====== [Control] ======="},
	{E_TO_S(HDMI20__AUD_IGNORE_ERR),			0x0,		"Ignore audio errors"},
	{E_TO_S(HDMI20__AUD_IGNORE_IRQ),			0x0,		"Ignore HDMI audio interrupt"},
	{E_TO_S(HDMI20__AUD_FORCE_UNMUTE),			0x0,		"Force audio mute"},
	{E_TO_S(HDMI20__AUD_FORCE_TYPE),			0x0,		"Force audio type"},
	{E_TO_S(HDMI20__AUD_FORCE_FS),				0x0,		"Force audio sampplig frequency"},
	{E_TO_S(HDMI20__AUD_FORCE_CHANNEL),			0x0,		"Force audio channel"},
	{E_TO_S(HDMI20__AUD_FORCE_STREAM),			0x0,		"Force audio stream"},
	{E_TO_S(HDMI20__AUD_FORCE_ACR_RESET),		0x0,		"Audio ACR reset"},
#if 0
	{E_TO_S(HDMI20__AUD_FORCE_UNKNOWN_TYPE),	0x0,		"Force Audio unknown type"},
#endif
	{E_TO_S(HDMI20__AUD_IRQ_DISABLE_PCD),		0x1,		"Audio PCD interrupt disable"},
	{E_TO_S(HDMI20__AUD_IRQ_DISABLE_SPDIF),		0x0,		"Audio SPDIF interrupt disable"},
	{E_TO_S(HDMI20__AUD_FIFO_ADJUST),			0x32,		"Audio FIFO adjustment"},
	{E_TO_S(HDMI20__AUD_REG_PRINT_REPEAT),		0x1,		"Audio register print repeat"},

	/* Info */
	{E_TO_S(HDMI20__AUD_INFORMATION),			0xA,		"====== [Information] ==="},
	{E_TO_S(HDMI20__AUD_DATA),					0x0,		"Input audio data sample"},
	{E_TO_S(HDMI20__AUD_N_CTS),					0x0,		"ACR N/CTS value"},
	{E_TO_S(HDMI20__AUD_INFO),					0x0,		"Input audio information : type, Fs, channel, stream"},
	{E_TO_S(HDMI20__AUD_CNT),					0x0,		"Audio count value(present/stable)"},
	{E_TO_S(HDMI20__AUD_FIFO),					0x0,		"Audio FIFO state"},
	{E_TO_S(HDMI20__AUD_MUTE),					0x0,		"Audio mute state"},
	{E_TO_S(HDMI20__AUD_HBR),					0x0,		"Audio HBR state"},
	{E_TO_S(HDMI20__AUD_PC),					0x0,		"PC connect"},
	{E_TO_S(HDMI20__AUD_REG),					0x0,		"Audio register value"},
	{E_TO_S(HDMI20__AUD_READ_TOP_REG),			0x0,		"Top register read"},
	{E_TO_S(HDMI20__AUD_READ_CTRL_REG),			0x0,		"Ctrl register read"},

	/* DBG Init */
	{E_TO_S(HDMI20__AUD_INITIALIZE), 			0x0,		"====== [Initialize] ===="},
	{E_TO_S(HDMI20__AUD_DEBUG_INIT), 			0x0,		"All debug print initialize"},
	{E_TO_S(HDMI20__AUD_COUNT_INIT), 			0x0,		"All count value initialize"},
	{E_TO_S(HDMI20__AUD_CONTROL_INIT), 			0x0,		"All control value initialize"},
	{E_TO_S(HDMI20__AUD_INFORMATION_INIT), 		0x0,		"All information print initialize"},
	{E_TO_S(HDMI20__AUD_ALL_DEBUG_INIT), 		0x0,		"All audio debug initialize"}
};
/*----------------------------------------------------------------------------------------
	Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Variables
----------------------------------------------------------------------------------------*/
HDMI20_AUDIO_REG_DATA gHDMI20AudioRegData = {0, };
UINT8 gHDMI20_supported_ARC_port = 0;

/*========================================================================================
	Implementation Group
========================================================================================*/

/* IOCTL */
int HDMI20_HAL_Rx_GetAudioInfo(UINT8 port, LX_HDMI_AUDIO_INFO_T *pHdmiAudioInfo, int size)
{
	int ret = RET_ERROR;
	LX_HDMI_AUDIO_INFO_T	data;
	UINT32	reg_hdmi_mode = 0;

	if((UINT16)gHDMI20RxHandler[port].timing_info.dvi){
		reg_hdmi_mode = 0;
	}else{
		reg_hdmi_mode = 1;
	}

	do{
		if(pHdmiAudioInfo == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(LX_HDMI_AUDIO_INFO_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI_AUDIO_INFO_T), size);
			break;
		}

		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Added 2014/08/04 taejun.lee */
		if((reg_hdmi_mode == 1) && ((HDMI20_HAL_Rx_IsLocalMuteOn(port) > 0) || (gHDMI20RxHandler[port].audio_change == TRUE) || (gHDMI20RxHandler[port].ctrl.isMute == 1)\
			|| (gHDMI20RxHandler[port].audioStandByCnt < gHDMI20RxDevAudControler[HDMI20__AUD_STANDBY_TIME].value)\
			|| (gHDMI20RxHandler[port].audioFifoErrMuteCnt < gHDMI20RxDevAudControler[HDMI20__AUD_FIFO_ERR_MUTE_TIME].value)\
			|| (gHDMI20RxHandler[port].audioStableCnt < gHDMI20RxDevAudControler[HDMI20__AUD_STABLE_TIME].value))) {
			data.audioType  = LX_HDMI_AUDIO_NO_AUDIO;
		} else {
			data.audioType  = gHDMI20RxHandler[port].audioInfo.audioType;
		}
		data.samplingFreq =  gHDMI20RxHandler[port].audioInfo.samplingFreq;
		data.countOfChannel = gHDMI20RxHandler[port].audioInfo.countOfChannel;
		data.stream = gHDMI20RxHandler[port].audioInfo.stream;

		ret = copy_to_user((LX_HDMI_AUDIO_INFO_T *)pHdmiAudioInfo, &data, sizeof(LX_HDMI_AUDIO_INFO_T));
		if(ret) {
			HDMI20_ERROR("Error on attempting to copy to USER for Port[%d] Synopsys LINK.\n", port);
			break;
		}

		if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)5) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)6)){
			HDMI20_AUDIO("HDMI[%d] audiotype:%d, samplingFreq:%d, countOfChannel:%d(%d)\n", port, data.audioType, data.samplingFreq, data.countOfChannel, gHDMI20RxHandler[port].audioInfo.countOfChannel);
			if(gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)5) gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value = (UINT32)0;
		}

		ret = RET_OK;

	} while(0);

	return ret;

}

/* IOCTL */
int HDMI20_HAL_Rx_GetAudioCopyInfo(UINT8 port, LX_HDMI_AUDIO_COPY_T *pHdmiCopyInfo, int size)
{
	int ret = RET_OK;

	UINT32	reg_achst_byte0, reg_achst_byte1;
	UINT32	CpBit, LBit;

	LX_HDMI_AUDIO_COPY_T hdmiCopyInfo;

	//Check a HDMI Link Number
	if (port >= HDMI20_NUM_OF_RX_PORTS)
	{
		HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
		return RET_ERROR;
	}

	//Get a hdmi audio copyright information.
	if ((UINT16)gHDMI20RxHandler[port].timing_info.dvi == TRUE)	//HDMI Mode
	{
		//Read  reg_achst_byte0 reg.
		//reg_achst_byte0 = gHDMI20RxHandler[port].top_read(0x70);
		reg_achst_byte0 = gHDMI20AudioRegData.byte0;

		//Set a CpBit
		if (reg_achst_byte0 & (UINT32)HDMI_AUDIO_CP_BIT_MASK)
			CpBit = (UINT32)1;
		else
			CpBit = (UINT32)0;

		//Read  reg_achst_byte1reg.
		//reg_achst_byte1 = gHDMI20RxHandler[port].top_read(0x74);
		reg_achst_byte1 = gHDMI20AudioRegData.byte1;

		//Set a LBit
		if (reg_achst_byte1 & (UINT32)HDMI20_AUDIO_L_BIT_MASK)
			LBit = (UINT32)1;
		else
			LBit = (UINT32)0;

		//Set a Copyright Info. by CpBit and LBit
		if ((CpBit == (UINT32)0) && (LBit == (UINT32)0))
			hdmiCopyInfo = LX_HDMI_AUDIO_COPY_ONCE;
		else if ((CpBit == (UINT32)0) && (LBit == (UINT32)1))
			hdmiCopyInfo = LX_HDMI_AUDIO_COPY_NO_MORE;	//same with LX_HDMI_AUDIO_COPY_NEVER
		else
			hdmiCopyInfo = LX_HDMI_AUDIO_COPY_FREE;

	}
	else	//DVI Mode
	{
		hdmiCopyInfo = LX_HDMI_AUDIO_COPY_FREE;
	}

	ret = copy_to_user((LX_HDMI_AUDIO_COPY_T *)pHdmiCopyInfo, &hdmiCopyInfo, sizeof(LX_HDMI_AUDIO_COPY_T));
	if(ret) {
		HDMI20_ERROR("Error on attempting to copy to USER for Port[%d] Synopsys LINK.\n", port);
		return ret;
	}

	HDMI20_AUDIO("HDMI[%d] HDMI_GetAudioCopyInfo :CopyInfo = %d\n", port, hdmiCopyInfo);
	return ret;
}

/* IOCTL */
int HDMI20_HAL_Rx_Set_HDMIARC(UINT8 port, BOOLEAN bOnOff)
{
	int ret = RET_OK;

	do{
		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

	 	if(port != 0){
	 		port = gHDMI20_supported_ARC_port;
	 		HDMI20_AUDIO("Set ARC port value error!. fixed 0.\n");
	 	}

		gHDMI20RxHandler[port].isAudioARCMode = bOnOff;

		/* Added 2014/07/02 taejun.lee */
		gHDMI20RxHandler[port].top_write((UINT32)HDMI20_RX_AD_MAIN_ARC_SET, (UINT32)bOnOff);
		gHDMI20RxHandler[port].top_write((UINT32)HDMI20_RX_AD_MAIN_PHY_ARC, ((UINT32)HDMI20_RX_AD_MAIN_PHY_ARC_DEFAULT + (UINT32)bOnOff)); // default : 20

		HDMI20_AUDIO("HDMI[%d] SetHDMIARC : ARCmode(%d)", port, gHDMI20RxHandler[port].isAudioARCMode);
		HDMI20_INFO("Notice %d : ARC Enable called with bOnOff[%d]\n", port,  bOnOff);

	} while(0);

	return ret;

}


/* IOCTL */
int HDMI20_HAL_Rx_Get_DebugAudioInfo(UINT8 port, LX_HDMI_DEBUG_AUDIO_INFO_T *pDebugAudioInfo, int size)
{
	int ret = RET_OK;

	do{

	} while(0);

	return ret;

}


int HDMI20_HAL_Rx_Set_AudioMute(UINT8 port, LX_HDMI_MUTE_CTRL_T *pMuteCtrl, int size)
{
	int ret = RET_OK;

	HDMI20_AUDIO("HDMI[%d] HDMI20_HAL_Rx_Set_AudioMute :mutecnt(%d)\n", port, gHDMI20RxHandler[port].audioStandByCnt);

	do{
		BOOLEAN 	audioMuteState;
		LX_HDMI_MUTE_CTRL_T muteCtrl;

		//Check a HDMI Link Number
		if (port >= HDMI20_NUM_OF_RX_PORTS)
		{
			HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
			return RET_ERROR;
		}

		//Bring audio mute state from register
		audioMuteState = !(gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_OUTPUT_MUTE_CTRL_MUTE) & (UINT32)HDMI20_RX_AUD_OUTPUT_MUTE_CTRL_UNMUTE);

		memset((void *)&muteCtrl, 0, sizeof(LX_HDMI_MUTE_CTRL_T));
		if( copy_from_user(&muteCtrl, (void __user *)pMuteCtrl, sizeof(LX_HDMI_MUTE_CTRL_T))){
			HDMI20_ERROR("Cannot copy HDMI20 audio mute ctrl structure from user\n");
			return RET_ERROR;
		}

		//audio related.
		if ((muteCtrl.eMode == (UINT32)LX_HDMI_AUDIO_MUTE) || (muteCtrl.eMode == (UINT32)LX_HDMI_AV_MUTE))
		{
			//Check a previous state
			if (muteCtrl.bAudioMute != audioMuteState)
			{
				if (muteCtrl.bAudioMute == TRUE)
				{
					//Mute audio data
					HDMI20_HAL_Rx_Set_AudioMuteControl(port, HDMI20_AUDIO_MUTE);
					HDMI20_AUDIO("HDMI[%d] audio Mute enable !\n", port);
					gHDMI20RxHandler[port].isAudioMute = HDMI20_AUDIO_MUTE;
					gHDMI20RxHandler[port].isAudioMuteControl = TRUE;
				}
				else
				{
					//Un-mute audio data
					if(((gHDMI20RxHandler[port].audio_change == FALSE) && (gHDMI20RxHandler[port].ctrl.isMute == FALSE)\
						&& (gHDMI20RxHandler[port].audioStandByCnt == gHDMI20RxDevAudControler[HDMI20__AUD_STANDBY_TIME].value))\
						|| (gHDMI20RxHandler[port].audioStableCnt == gHDMI20RxDevAudControler[HDMI20__AUD_STABLE_TIME].value)) {
						HDMI20_HAL_Rx_Set_AudioMuteControl(port, HDMI20_AUDIO_UNMUTE);
						HDMI20_AUDIO("HDMI[%d] audio Mute disable!\n", port);
						gHDMI20RxHandler[port].isAudioMute = HDMI20_AUDIO_UNMUTE;
					}
					gHDMI20RxHandler[port].isAudioMuteControl = FALSE;
				}

				//For debug print
				HDMI20_AUDIO("[%d] %s : port = %d, bAudioMute = %s \n",	\
							__L__, __F__, port, (muteCtrl.bAudioMute ? "On" : "Off"));
			}

			//For debug print
			if (muteCtrl.bAudioMute == FALSE)
			{
				HDMI20_AUDIO("[%d]SetMute : port = %d, type = %d, freq = %d, mute = %d\n", \
							__L__, port, gHDMI20RxHandler[port].audioInfo.audioType, gHDMI20RxHandler[port].audioInfo.samplingFreq, \
							audioMuteState);
			}
		}
	} while(0);

	return ret;

}

void HDMI20_HAL_Rx_Set_Audio_Configure(UINT8 port, int isUD)
{
	if(gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)0x1000)HDMI20_AUDIO("HDMI(%d) HDMI20_HAL_Rx_Set_Audio_Configure\n", port);

	// HBR audio check
	if((gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_PDEC_AUD_STS) == (UINT32)HDMI20_RX_PDEC_AUD_STS_HBR) && (gHDMI20RxHandler[port].isHBRaudio == FALSE)) {
		gHDMI20RxHandler[port].isHBRaudio = TRUE;
		HDMI20_AUDIO("HDMI[%d] High Bit Rate Audio start(pdec_aud_sts=0x%x)!\n", port, gHDMI20RxHandler[port].ctrl.bsp_read(HDMI20_RX_PDEC_AUD_STS));
	}else if ((gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_PDEC_AUD_STS) != (UINT32)HDMI20_RX_PDEC_AUD_STS_HBR) && (gHDMI20RxHandler[port].isHBRaudio == TRUE)) {
		gHDMI20RxHandler[port].isHBRaudio = FALSE;
		HDMI20_AUDIO("HDMI[%d] High Bit Rate Audio stop(pdec_aud_sts=0x%x)!\n", port, gHDMI20RxHandler[port].ctrl.bsp_read(HDMI20_RX_PDEC_AUD_STS));
	}

	// Register setting
	gHDMI20RxHandler[port].top_write((UINT32)HDMI20_RX_ACR_CLK_DIVIDER, 		(UINT32)HDMI20_RX_ACR_CLK_DIVIDER_DIV1);
	gHDMI20RxHandler[port].top_write((UINT32)HDMI20_RX_ACR_CLK_N_FS,			(UINT32)HDMI20_RX_ACR_CLK_N_FS_128);
	gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_CTRL,			(UINT32)HDMI20_RX_AUD_CTRL_CONF);
	gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_CLK_CTRL,		(UINT32)HDMI20_RX_AUD_CLK_CTRL_CONF);// AUD_CLK_CTRL
	gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_PLL_CTRL,		(UINT32)HDMI20_RX_AUD_PLL_CTRL_CONF);// AUD_PLL_CTRL
	gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_HDMI_CKM_EVLTM,		(UINT32)HDMI20_RX_HDMI_CKM_EVLTM_CONF);// HDMI_CKM_EVLTM
	gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_HDMI_CKM_F,			(UINT32)HDMI20_RX_HDMI_CKM_F_CONF);// HDMI_CKM_F
	gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_FIFO_TH,		(UINT32)HDMI20_RX_AUD_FIFO_TH_CONF);// AUD_FIFO_TH
	gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_PDEC_ASP_CTRL,		(UINT32)HDMI20_RX_PDEC_ASP_CTRL_CONF);// PDEC_ASP_CTRL
	gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_FIFO_CTRL,		(UINT32)HDMI20_RX_AUD_FIFO_CTRL_CONF);// AUD_FIFO_CTRL
	gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_HDMI_RESMPL_CTRL, 	(UINT32)HDMI20_RX_HDMI_RESMPL_CTRL_CONF);// HDMI_RESMPL_CTRL
	gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_MUTE_CTRL,		(UINT32)HDMI20_RX_AUD_MUTE_CTRL_CONF);// AUD_MUTE_CTRL
	gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_PAO_CTRL,		(UINT32)HDMI20_RX_AUD_PAO_CTRL_CONF);// AUD_PAO_CTRL
	gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_PDEC_AIF_CTRL,		(UINT32)HDMI20_RX_PDEC_AIF_CTRL_CONF);// PDEC_AIF_CTRL
	gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL,	(UINT32)HDMI20_RX_AUD_CHEXTR_CTRL_8CH);// AUD_CHEXTR_CTRL
	gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_OUTPUT_MUTE_CTRL, (UINT32)HDMI20_RX_AUD_OUTPUT_MUTE_CTRL_MUTE);// AUD_OUTPUT_MUTE_CTRL mute
	HDMI20_Rx_Audio_Path_SetMute(port);

	if(isUD){
		gHDMI20RxHandler[port].top_write((UINT32)HDMI20_RX_ACR_CLK_N_FS, (UINT32)HDMI20_RX_ACR_CLK_N_FS_256);
		HDMI20_AUDIO("HDMI[%d] signal is UD\n", port);
	}

	if(gHDMI20RxHandler[port].isHBRaudio == 1){
		gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_CTRL, (UINT32)HDMI20_RX_AUD_CTRL_HBR);
		gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_PAO_CTRL, (UINT32)HDMI20_RX_AUD_PAO_CTRL_HBR);// AUD_PAO_CTRL
		gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL, (UINT32)HDMI20_RX_AUD_CHEXTR_CTRL_HBR);// AUD_CHEXTR_CTRL
	}

	// CSD change interrupt masking
	HDMI20_Rx_Audio_Path_SetInthw(port);

	// Count initialize
	gHDMI20RxHandler[port].audioChMapCnt = (UINT32)0;
	gHDMI20RxHandler[port].audioStableCnt = (UINT32)0;
	gHDMI20RxHandler[port].audioChMapStandByCnt = (UINT32)0;
	gHDMI20RxHandler[port].audioAcrResetCnt = (UINT32)0;
	gHDMI20RxHandler[port].audioAcrErrorCnt = (UINT32)0;
	gHDMI20RxHandler[port].isAudioMute = HDMI20_AUDIO_MUTE;

	// Info initialize
	gHDMI20RxHandler[port].audioInfo.audioType = LX_HDMI_AUDIO_DEFAULT;
	gHDMI20RxHandler[port].audioInfo.samplingFreq = LX_HDMI_SAMPLING_FREQ_NONE;
	gHDMI20RxHandler[port].audioInfo.countOfChannel = (UINT32)2;
	gHDMI20RxHandler[port].audioInfo.stream = LX_HDMI_AUDIO_STREAM_NONE;
}

UINT32 HDMI20_HAL_Rx_Get_PLLFreqRange(UINT32 tmds_clk)
{
	/* For DBG purpose */
	if(gHDMI20RxDevControler[HDMI20__FORCE_PLL_RANGE_DETECTED_RESULT].value != (UINT32)0){
		if(gHDMI20RxDevControler[HDMI20__FORCE_PLL_RANGE_DETECTED_RESULT].value == (UINT32)8282){
			return 0;
		}
		else{
			return gHDMI20RxDevControler[HDMI20__FORCE_PLL_RANGE_DETECTED_RESULT].value;
		}
	}

	if(tmds_clk <= (UINT32)25000){
		return 0;
	}
	else if((tmds_clk > (UINT32)25000)&&(tmds_clk <= (UINT32)40000)){
		return 0;
	}
	else if((tmds_clk > (UINT32)40000)&&(tmds_clk <= (UINT32)80000)){
		return 1;
	}
	else if((tmds_clk > (UINT32)80000)&&(tmds_clk <= (UINT32)160000)){
		return 2;
	}
	else if((tmds_clk > (UINT32)160000)&&(tmds_clk <= (UINT32)340000)){
		return 3;
	}else if((tmds_clk > (UINT32)340000)){
		return 3; // 2014/07/08 temperary
	}
	else return 0;

}


void HDMI20_HAL_Rx_Update_AudioCtsNparam(int port, int clear)
{
	UINT32 cts_update = 0;
	UINT32 reg_hdmi_mode = 0;

	if((UINT16)gHDMI20RxHandler[port].timing_info.dvi){
		reg_hdmi_mode = (UINT32)0;
	}else{
		reg_hdmi_mode = (UINT32)1;
	}
	/* Block this update to prevent unsteady state of N/CTS value */
	/* SW workaround for AUDIO */
	gHDMI20RxHandler[port].ctrl.n_param = ((UINT32)0x000FFFFF & (gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_PDEC_ACR_N)));
	gHDMI20RxHandler[port].ctrl.cts_param = ((UINT32)0x000FFFFF & (gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_PDEC_ACR_CTS)));

	if((gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == (UINT32)690)||(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == (UINT32)6969)){
		HDMI20_PACKET("HDMI[%d] : N/CTS value => [0x%08x][0x%08x]\n", port, gHDMI20RxHandler[port].ctrl.n_param, gHDMI20RxHandler[port].ctrl.cts_param);
	}

	if(gHDMI20RxDevControler[HDMI20__VIDEO_LINE_DEBUGGER].value == (UINT32)6969){return;}

	if(clear){
		gHDMI20RxHandler[port].ctrl.n_param = (UINT32)0;
		gHDMI20RxHandler[port].ctrl.cts_param = (UINT32)0;
	}

	if(gHDMI20RxHandler[port].audioAcrResetCnt < gHDMI20RxDevAudControler[HDMI20__AUD_ACR_RESET_TIME].value) {
		gHDMI20RxHandler[port].ctrl.n_param = (UINT32)0;
		gHDMI20RxHandler[port].ctrl.cts_param = (UINT32)0;
		gHDMI20RxHandler[port].audioAcrResetCnt++;
		if(gHDMI20RxDevAudControler[HDMI20__AUD_CNT_DBG].value != (UINT32)0)HDMI20_AUDIO("HDMI[%d] Audio ACR reset cnt : %d", port, gHDMI20RxHandler[port].audioAcrResetCnt);
	}
	
	if((gHDMI20RxDevAudControler[HDMI20__AUD_FIFO_ADJUST].value != (UINT32)0) \
		&&  (reg_hdmi_mode == (UINT32)1) \
		&& (gHDMI20RxHandler[port].audioStandByCnt == gHDMI20RxDevAudControler[HDMI20__AUD_STANDBY_TIME].value)\
		&& (gHDMI20RxHandler[port].audioStableCnt == gHDMI20RxDevAudControler[HDMI20__AUD_STABLE_TIME].value)\
		&& (gHDMI20RxHandler[port].audioInfo.audioType > LX_HDMI_AUDIO_NO_AUDIO)){
		if(gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_FIFO_FILLSTS1) > (UINT32)HDMI20_AUDIO_FIFO_FILL_MAX){
			cts_update = gHDMI20RxHandler[port].ctrl.cts_param - gHDMI20RxDevAudControler[HDMI20__AUD_FIFO_ADJUST].value;
			HDMI20_AUDIO("HDMI[%d] FIFO : Recovery overflow(0x%04x), CTS(0x%08x -> 0x%08x) \n", port, gHDMI20RxHandler[port].ctrl.bsp_read(HDMI20_RX_AUD_FIFO_FILLSTS1),\
			gHDMI20RxHandler[port].ctrl.cts_param, cts_update);
			gHDMI20RxHandler[port].ctrl.cts_param = cts_update;
		}else if(gHDMI20RxHandler[port].ctrl.bsp_read(HDMI20_RX_AUD_FIFO_FILLSTS1) < HDMI20_AUDIO_FIFO_FILL_MIN){
			cts_update = gHDMI20RxHandler[port].ctrl.cts_param + gHDMI20RxDevAudControler[HDMI20__AUD_FIFO_ADJUST].value;
			HDMI20_AUDIO("HDMI[%d] FIFO : Recovery underflow(0x%04x), CTS(0x%08x -> 0x%08x) \n", port, gHDMI20RxHandler[port].ctrl.bsp_read(HDMI20_RX_AUD_FIFO_FILLSTS1),\
			gHDMI20RxHandler[port].ctrl.cts_param, cts_update);
			gHDMI20RxHandler[port].ctrl.cts_param = cts_update;
		}
	}

	gHDMI20RxHandler[port].top_write( (UINT32)HDMI20_RX_ACR_CTS, gHDMI20RxHandler[port].ctrl.cts_param);
	gHDMI20RxHandler[port].top_write( (UINT32)HDMI20_RX_ACR_N, gHDMI20RxHandler[port].ctrl.n_param);
	gHDMI20RxHandler[port].top_write( (UINT32)HDMI20_RX_ACR_PLL_V, HDMI20_HAL_Rx_Get_PLLFreqRange( gHDMI20RxHandler[port].real_tmds_clk));
}


int HDMI20_HAL_Rx_Get_AudioType(UINT8 port, LX_HDMI_AUDIO_TYPE_T *audioType)
{
	int ret = RET_OK;

	UINT32	reg_hdmi_mode = 0;
	UINT32	reg_achst_byte0;
	UINT32	reg_burst_pc_0;

	if((UINT16)gHDMI20RxHandler[port].timing_info.dvi){
		reg_hdmi_mode = 0;
	}
	else{
		reg_hdmi_mode = 1;
	}

	HDMI20_Rx_Audio_Path_GetSPDIFInfo(port, &gHDMI20AudioRegData);

	reg_achst_byte0 = gHDMI20AudioRegData.byte0;
	reg_burst_pc_0  = gHDMI20AudioRegData.pcpd;
	if(gHDMI20RxHandler[port].isHBRaudio == TRUE){
		reg_achst_byte0 = gHDMI20RxHandler[port].top_read((UINT32)HDMI20_RX_AD_MAIN_AUD_INFO_BYTE0);
		reg_burst_pc_0  = gHDMI20RxHandler[port].top_read((UINT32)HDMI20_RX_AD_MAIN_AUD_INFO_PC);
	}

	if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)4)){
		HDMI20_AUDIO("HDMI[%d] byte0[aud:%x, link:%x], pc[aud:%x, link:%x], HDMI_mode[%d] \n",\
		port, reg_achst_byte0, gHDMI20RxHandler[port].top_read((UINT32)HDMI20_RX_AD_MAIN_AUD_INFO_BYTE0),\
		reg_burst_pc_0, gHDMI20RxHandler[port].top_read((UINT32)HDMI20_RX_AD_MAIN_AUD_INFO_PC),reg_hdmi_mode);
	}
	/* Audio info Pc error SW workaround */
	if (port == 3){
		reg_achst_byte0 = gHDMI20RxHandler[port].top_read((UINT32)HDMI20_RX_AD_MAIN_AUD_INFO_BYTE0);
		reg_burst_pc_0  = gHDMI20RxHandler[port].top_read((UINT32)HDMI20_RX_AD_MAIN_AUD_INFO_PC);
	}
#if 0
	if(gHDMI20RxDevAudControler[HDMI20__AUD_FORCE_UNKNOWN_TYPE].value != 0x0){
		reg_achst_byte0 = 0;
	}
#endif
	//Check HDMI /DVI Mode, 0 : DVI, 1 : HDMI
	if (reg_hdmi_mode > (UINT32)0)
	{
		//Check if audio sample word used for other purposes than liner PCM.
		if (reg_achst_byte0 & HDMI_AUDIO_SAMPLE_NON_PCM_MASK)	//bit 1, 0 : PCM, 1 : non-PCM
		{
			//Check a vaild Pc data for payload
			if ((reg_burst_pc_0 & BURST_INFO_PAYLOAD_ERROR_BIT_MASK) == (UINT32)0) //bit 7, 0 : No Error, 1 : Error
			{
				//Set Audio Data-Types according to IEC61937-2 Burst Info Preamble C
				switch(reg_burst_pc_0 & HDMI20_BURST_INFO_AUDIO_TYPEBIT_MASK) //bit 4 ~ 0
				{
					case HDMI20_BURST_AUDIO_INFO_TYPE_AC3:
						*audioType = LX_HDMI_AUDIO_AC3;
						if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)4)){
							HDMI20_AUDIO("HDMI[%d] Audio Type = AC3,  ", port);
						}
						break;

					case HDMI20_BURST_AUDIO_INFO_TYPE_AC3_ENHANCED:
						*audioType = LX_HDMI_AUDIO_EAC3;
						if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)4)){
							HDMI20_AUDIO("HDMI[%d] Audio Type = AC3_ENHANCED,  ", port);
						}
						break;

					case HDMI20_BURST_AUDIO_INFO_TYPE_MAT:
						*audioType = LX_HDMI_AUDIO_MAT;
						if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)4)){
							HDMI20_AUDIO("HDMI[%d] Audio Type = MAT,  ", port);
						}
						break;

					case HDMI20_BURST_AUDIO_INFO_TYPE_DTS_I:
					case HDMI20_BURST_AUDIO_INFO_TYPE_DTS_II:
					case HDMI20_BURST_AUDIO_INFO_TYPE_DTS_III:
						*audioType = LX_HDMI_AUDIO_DTS;
						if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)4)){
							HDMI20_AUDIO("HDMI[%d] Audio Type = DTS,  ", port);
						}
						break;

					case HDMI20_BURST_AUDIO_INFO_TYPE_DTS_IV:
						if(reg_burst_pc_0 == 0x0311){
							*audioType = LX_HDMI_AUDIO_DTS_HD_HRA;
							if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)4)){
								HDMI20_AUDIO("HDMI[%d] Audio Type = DTS_HD_HRA,  ", port);
							}
						}else{
							*audioType = LX_HDMI_AUDIO_DTS_HD;
							if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)4)){
							HDMI20_AUDIO("HDMI[%d] Audio Type = DTS_HD,  ", port);
							}
						}
						break;

					case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_AAC:
					case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_AAC_LOW:
					case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG4_AAC:
					case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG4_AAC_LOAS:
						*audioType = LX_HDMI_AUDIO_AAC;
						if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)4)){
							HDMI20_AUDIO("HDMI[%d] Audio Type = AAC,  ", port);
						}
						break;

					case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG1_L1:
					case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG1_L23:
					case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_EXT:
					case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_L1:
					case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_L2:
					case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_L3:
						*audioType = LX_HDMI_AUDIO_MPEG;
						if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)4)){
							HDMI20_AUDIO("HDMI[%d] Audio Type = MPEG,  ", port);
						}
						break;

					case HDMI20_BURST_AUDIO_INFO_TYPE_NULL:
						if(gHDMI20RxHandler[port].audioInfo.audioType == LX_HDMI_AUDIO_PCM) {
							*audioType = LX_HDMI_AUDIO_NO_AUDIO;
						}else {
							*audioType = gHDMI20RxHandler[port].audioInfo.audioType;
						}
						if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)4)){
							HDMI20_AUDIO("HDMI[%d] Audio Type = NON-PCM NULL(%x),  ", port, gHDMI20RxHandler[port].audioInfo.audioType);
						}
						break;

					default:
						*audioType = LX_HDMI_AUDIO_NO_AUDIO;
						if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)4)){
							HDMI20_AUDIO("HDMI[%d] Audio Type = NON-PCM,  ", port);
						}
						break;
				}
			}	//if ((reg_burst_pc_0 & BURST_INFO_PAYLOAD_ERROR_BIT_MASK) == 0)
			else
			{
				*audioType = LX_HDMI_AUDIO_PCM;
				if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)4)){
					HDMI20_AUDIO("HDMI[%d] Audio Type = NON-PCM error,  ", port);
				}

			}
		}	//if (reg_achst_byte0 & HDMI_AUDIO_SAMPLE_NON_PCM_MASK)
		else
		{
#if 1		
			*audioType = LX_HDMI_AUDIO_PCM;
			if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)4)){
				HDMI20_AUDIO("HDMI[%d] Audio Type = PCM,  ", port);
			}	
#else				
			//Check a vaild Pc data for payload
			if ((reg_burst_pc_0 & BURST_INFO_PAYLOAD_ERROR_BIT_MASK) == 0) //bit 7, 0 : No Error, 1 : Error
			{
				//Set Audio Data-Types according to IEC61937-2 Burst Info Preamble C
				switch(reg_burst_pc_0 & HDMI20_BURST_INFO_AUDIO_TYPEBIT_MASK) //bit 4 ~ 0
				{
					case HDMI20_BURST_AUDIO_INFO_TYPE_AC3:
						*audioType = LX_HDMI_AUDIO_UNKNOWN_AC3;
						if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)4)){
							HDMI20_AUDIO("HDMI[%d] Audio Type = Unknown AC3,  ", port);
						}
						break;

					case HDMI20_BURST_AUDIO_INFO_TYPE_AC3_ENHANCED:
						*audioType = LX_HDMI_AUDIO_UNKNOWN_EAC3;
						if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)4)){
							HDMI20_AUDIO("HDMI[%d] Audio Type = Unknown AC3_ENHANCED,  ", port);
						}
						break;

					case HDMI20_BURST_AUDIO_INFO_TYPE_MAT:
						*audioType = LX_HDMI_AUDIO_UNKNOWN_MAT;
						if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)4)){
							HDMI20_AUDIO("HDMI[%d] Audio Type = Unknown MAT,  ", port);
						}
						break;

					case HDMI20_BURST_AUDIO_INFO_TYPE_DTS_I:
					case HDMI20_BURST_AUDIO_INFO_TYPE_DTS_II:
					case HDMI20_BURST_AUDIO_INFO_TYPE_DTS_III:
						*audioType = LX_HDMI_AUDIO_UNKNOWN_DTS;
						if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)4)){
							HDMI20_AUDIO("HDMI[%d] Audio Type = Unknown DTS,  ", port);
						}
						break;

					case HDMI20_BURST_AUDIO_INFO_TYPE_DTS_IV:
						if(reg_burst_pc_0 == 0x0311){
							*audioType = LX_HDMI_AUDIO_UNKNOWN_DTS_HD_HRA;
							if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)4)){
								HDMI20_AUDIO("HDMI[%d] Audio Type = Unknown DTS_HD_HRA,  ", port);
							}
						}else{
							*audioType = LX_HDMI_AUDIO_UNKNOWN_DTS_HD;
							if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)4)){
							HDMI20_AUDIO("HDMI[%d] Audio Type = Unknown DTS_HD,  ", port);
							}
						}
						break;

					case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_AAC:
					case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_AAC_LOW:
					case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG4_AAC:
					case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG4_AAC_LOAS:
						*audioType = LX_HDMI_AUDIO_UNKNOWN_AAC;
						if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)4)){
							HDMI20_AUDIO("HDMI[%d] Audio Type = Unknown AAC,  ", port);
						}
						break;

					case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG1_L1:
					case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG1_L23:
					case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_EXT:
					case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_L1:
					case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_L2:
					case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_L3:
						*audioType = LX_HDMI_AUDIO_UNKNOWN_MPEG;
						if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)4)){
							HDMI20_AUDIO("HDMI[%d] Audio Type = Unknown MPEG,  ", port);
						}
						break;

					case HDMI20_BURST_AUDIO_INFO_TYPE_NULL:
						if(gHDMI20RxHandler[port].audioInfo.audioType == LX_HDMI_AUDIO_PCM) {
							*audioType = LX_HDMI_AUDIO_NO_AUDIO;
						}else {
							*audioType = gHDMI20RxHandler[port].audioInfo.audioType;
						}
						if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)4)){
							HDMI20_AUDIO("HDMI[%d] Audio Type = NON-PCM NULL(%x),  ", port, gHDMI20RxHandler[port].audioInfo.audioType);
						}
						break;

					default:
						*audioType = LX_HDMI_AUDIO_NO_AUDIO;
						if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)4)){
							HDMI20_AUDIO("HDMI[%d] Audio Type = NON-PCM,  ", port);
						}
						break;
				}
			}	//if ((reg_burst_pc_0 & BURST_INFO_PAYLOAD_ERROR_BIT_MASK) == 0)
			else
			{
				*audioType = LX_HDMI_AUDIO_PCM;
				if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)4)){
					HDMI20_AUDIO("HDMI[%d] Audio Type = NON-PCM error,  ", port);

				}
			}
#endif				
		}	
	}
	else
	{
		//Set DVI mode
		*audioType	  = LX_HDMI_AUDIO_DVI;
		if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)4)){
			HDMI20_AUDIO("HDMI[%d] Audio Type = DVI,  ", port);
		}
	}

	if(gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)3) gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value = (UINT32)0;
	return ret;
}

int HDMI20_HAL_Rx_Get_AudioCountOfChannel(UINT8 port, int *countOfChannel) {
	int ret = RET_OK;
	UINT32 readChannel, realChannel;
	readChannel = gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_PDEC_AIF_PB0) & (UINT32)HDMI20_RX_PDEC_AIF_PB0_BIT_MASK_CHA_CNT;
	/*
	To Do
	if(readChannel == 0) {}
	*/
	realChannel = readChannel + (UINT32)1;

	if((realChannel < (UINT32)2) || (realChannel > (UINT32)8)) {
		*countOfChannel = (int)2;
	}else {
		*countOfChannel = (int)realChannel;
	}

	if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)7) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)8)){
		HDMI20_AUDIO("HDMI[%d] Audio count of channel register vlaue : %d)\n", port, readChannel);
		if(gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)7) gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value = (UINT32)0;
	}

	return ret;
}

int HDMI20_HAL_Rx_Get_AudioStream(UINT8 port, LX_HDMI_AUDIO_STREAM_T *stream){
	int ret = RET_OK;
	*stream = (UINT16)(gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_PDEC_AUD_STS));

	if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)0x9) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)0x10)){
		HDMI20_AUDIO("HDMI[%d] Audio starem : 0x%x\n", port, gHDMI20RxHandler[port].ctrl.bsp_read(HDMI20_RX_PDEC_AUD_STS));
		if(gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)0x9) gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value = (UINT32)0;
	}

	return ret;
}


/* Added 2014/08/05 taejun.lee */
int HDMI20_HAL_Rx_Get_AudioInfo(UINT8 port)
{
	int ret = RET_ERROR;
	bool audioInfoChange = FALSE;
	UINT32 layOut, mute_status, nDiff, ctsDiff;

	LX_HDMI_AUDIO_INFO_T	data;
	UINT32	reg_hdmi_mode = 0;

	if((UINT16)gHDMI20RxHandler[port].timing_info.dvi){
		reg_hdmi_mode = (UINT32)0;
	}else{
		reg_hdmi_mode = (UINT32)1;
	}

	do{
		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		if(gHDMI20RxHandler[port].initiated == 0){
			HDMI20_ERROR("Device handler was not initiated.\n");
			break;
		}

		layOut = gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_PDEC_STS) & (UINT32)HDMI20_RX_PDEC_STS_BIT_MASK_AUD_LAYOUT;

		if(gHDMI20RxHandler[port].ctrl.stable_cnt >= gHDMI20RxDevControler[HDMI20__STABLE_CHECK_CNT].value){
			if (gHDMI20RxHandler[port].audioStandByCnt < gHDMI20RxDevAudControler[HDMI20__AUD_STANDBY_TIME].value) {
				gHDMI20RxHandler[port].audioStandByCnt++;
				if(gHDMI20RxDevAudControler[HDMI20__AUD_CNT_DBG].value != (UINT32)0)HDMI20_AUDIO("Audio stand by cnt : %d",gHDMI20RxHandler[port].audioStandByCnt);
			}
		}
		
		if(gHDMI20RxHandler[port].audioStandByCnt == gHDMI20RxDevAudControler[HDMI20__AUD_STANDBY_TIME].value) {
			if(gHDMI20RxHandler[port].isAudioRegReady == FALSE){
				HDMI20_Rx_Audio_Path_SetInthw(port);
			}

			/* Get Audio Info */
			HDMI20_HAL_Rx_Get_AudioType(port, &data.audioType);
			HDMI20_HAL_Rx_Get_AudioFreqFromTMDSClock(port, &data.samplingFreq);
#ifdef HDMI20_HAL_AUDIO_COUNT_OF_CHANNEL_ENABLE
			/* Get audio channel count */
			if(data.audioType == LX_HDMI_AUDIO_PCM) {
				HDMI20_HAL_Rx_Get_AudioCountOfChannel(port, &data.countOfChannel);
			}
#endif
			HDMI20_HAL_Rx_Get_AudioStream(port, &data.stream);

			/* Audio Mute Count*/
			if(gHDMI20RxHandler[port].audioStableCnt < gHDMI20RxDevAudControler[HDMI20__AUD_STABLE_TIME].value){
				if(gHDMI20RxHandler[port].audioFifoErrMuteCnt  == gHDMI20RxDevAudControler[HDMI20__AUD_FIFO_ERR_MUTE_TIME].value) {
					gHDMI20RxHandler[port].audioStableCnt++;
					if(gHDMI20RxDevAudControler[HDMI20__AUD_CNT_DBG].value != 0)HDMI20_AUDIO("HDMI[%d] Audio stable cnt : %d", port, gHDMI20RxHandler[port].audioStableCnt);

					if(gHDMI20RxHandler[port].audioStableCnt == gHDMI20RxDevAudControler[HDMI20__AUD_STABLE].value){
						/*Audio Info Clear*/
						gHDMI20RxHandler[port].top_write((UINT32)HDMI20_RX_AD_INFO_CLR_AUDIO, (UINT32)HDMI20_RX_AD_INFO_CLR_AUDIO_ENABLE);
						gHDMI20RxHandler[port].top_write((UINT32)HDMI20_RX_AD_MAIN_AUD_INFO_CLR_SEL, (UINT32)HDMI20_RX_AD_MAIN_AUD_INFO_CLR_SEL_ENABLE);
						gHDMI20RxHandler[port].top_write((UINT32)HDMI20_RX_AD_INFO_CLR_AUDIO, (UINT32)HDMI20_RX_AD_INFO_CLR_AUDIO_DISABLE);
						gHDMI20RxHandler[port].top_write((UINT32)HDMI20_RX_AD_MAIN_AUD_INFO_CLR_SEL, (UINT32)HDMI20_RX_AD_MAIN_AUD_INFO_CLR_SEL_DISABLE);
						msleep(4);
						gHDMI20RxHandler[port].top_write((UINT32)HDMI20_RX_AD_INTR_CLR_AUDIO, (UINT32)HDMI20_RX_AD_INTR_CLR_AUDIO_ENABLE);
						gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_DMI_SW_RST, (UINT32)HDMI20_RX_DMI_SW_RST_AUDIO);
						hdmi_rx_ctrl_audio_fifo_rst(&gHDMI20RxHandler[port].ctrl);
						gHDMI20RxHandler[port].audioIrqFifoErrCnt = (UINT32)0;
						HDMI20_Rx_Audio_Path_SetInthw(port);
						HDMI20_AUDIO("HDMI[%d] Audio reset for start!\n", port);
					}
				}
			}else {
				if(gHDMI20RxHandler[port].audioForceMuteCnt < gHDMI20RxDevAudControler[HDMI20__AUD_FORCE_MUTE_TIME].value){
					gHDMI20RxHandler[port].audioForceMuteCnt++;
					if(gHDMI20RxDevAudControler[HDMI20__AUD_CNT_DBG].value != (UINT32)0)HDMI20_AUDIO("HDMI[%d] Audio force mute cnt : %d", port, gHDMI20RxHandler[port].audioForceMuteCnt);
				}
			}

			if(gHDMI20RxHandler[port].audioChMapStandByCnt < gHDMI20RxDevAudControler[HDMI20__AUD_CH_MAP_STANDBY_TIME].value){
				gHDMI20RxHandler[port].audioChMapStandByCnt++;
			}else{
				/* Audio Type error check*/
				if((gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_FIFO_ISTS) > (UINT32)HDMI20_RX_AUD_FIFO_ISTS_PASS)\
					&& (reg_hdmi_mode == 1)\
					&& (gHDMI20RxDevAudControler[HDMI20__AUD_IGNORE_ERR].value == (UINT32)0x0)){
					HDMI20_AUDIO("HDMI[%d] Audio FIFO err	sts(0x%x) itr(0x%x)\n", port, gHDMI20RxHandler[port].ctrl.bsp_read(HDMI20_RX_AUD_FIFO_STS), gHDMI20RxHandler[port].ctrl.bsp_read(HDMI20_RX_AUD_FIFO_ISTS));

					/*HBR audio check*/
					if((gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_PDEC_AUD_STS) == (UINT32)HDMI20_RX_PDEC_AUD_STS_HBR) && (gHDMI20RxHandler[port].isHBRaudio == 0)) {
						gHDMI20RxHandler[port].isHBRaudio = 1;
						gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_CTRL, (UINT32)HDMI20_RX_AUD_CTRL_HBR);
						gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_PAO_CTRL, (UINT32)HDMI20_RX_AUD_PAO_CTRL_HBR);// AUD_PAO_CTRL
						gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL, (UINT32)HDMI20_RX_AUD_CHEXTR_CTRL_HBR);// AUD_CHEXTR_CTRL
						HDMI20_AUDIO("HDMI[%d] Audio High Bit Rate Audio start(pdec_aud_sts=0x%x)!\n", port, gHDMI20RxHandler[port].ctrl.bsp_read(HDMI20_RX_PDEC_AUD_STS));
					}else if ((gHDMI20RxHandler[port].ctrl.bsp_read(HDMI20_RX_PDEC_AUD_STS) != HDMI20_RX_PDEC_AUD_STS_HBR) && (gHDMI20RxHandler[port].isHBRaudio == 1)) {
						gHDMI20RxHandler[port].isHBRaudio = 0;
						gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_CTRL, (UINT32)HDMI20_RX_AUD_CTRL_CONF);
						gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_PAO_CTRL, (UINT32)HDMI20_RX_AUD_PAO_CTRL_CONF);// AUD_PAO_CTRL
						gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL, (UINT32)HDMI20_RX_AUD_CHEXTR_CTRL_8CH);// AUD_CHEXTR_CTRL
						HDMI20_AUDIO("HDMI[%d] Audio High Bit Rate Audio stop(pdec_aud_sts=0x%x)!\n", port, gHDMI20RxHandler[port].ctrl.bsp_read(HDMI20_RX_PDEC_AUD_STS));
					}

					gHDMI20RxHandler[port].audioChMapCnt++;
					if(gHDMI20RxDevAudControler[HDMI20__AUD_CNT_DBG].value != 0)HDMI20_AUDIO("HDMI[%d] Audio ch-map cnt : %d", port, gHDMI20RxHandler[port].audioChMapCnt);
					if(gHDMI20RxHandler[port].audioChMapCnt == gHDMI20RxDevAudControler[HDMI20__AUD_CH_MAP_MAX].value) {
						if((gHDMI20RxHandler[port].isHBRaudio == 0) && (reg_hdmi_mode == 1)){
							if(gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL) == (UINT32)HDMI20_RX_AUD_CHEXTR_CTRL_8CH) {		// 8ch
								gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL, (UINT32)HDMI20_RX_AUD_CHEXTR_CTRL_6CH_1);
							}else if(gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL) == (UINT32)HDMI20_RX_AUD_CHEXTR_CTRL_6CH_1){	// 6ch-1
								gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL, (UINT32)HDMI20_RX_AUD_CHEXTR_CTRL_4CH_1);
							}else if(gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL) == (UINT32)HDMI20_RX_AUD_CHEXTR_CTRL_4CH_1){	// 4ch-1
								gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL, (UINT32)HDMI20_RX_AUD_CHEXTR_CTRL_2CH);
							}else if(gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL) == (UINT32)HDMI20_RX_AUD_CHEXTR_CTRL_2CH){		// 2ch
								gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL, (UINT32)HDMI20_RX_AUD_CHEXTR_CTRL_AUTO);
							}else if(gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL) == (UINT32)HDMI20_RX_AUD_CHEXTR_CTRL_AUTO){	// Auto
								gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL, (UINT32)HDMI20_RX_AUD_CHEXTR_CTRL_6CH_2);
							}else if(gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL) == (UINT32)HDMI20_RX_AUD_CHEXTR_CTRL_6CH_2){	// 6ch-2
								gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL, (UINT32)HDMI20_RX_AUD_CHEXTR_CTRL_4CH_2);
							}else if(gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL) == (UINT32)HDMI20_RX_AUD_CHEXTR_CTRL_4CH_2){	// 4ch-2
								gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL, (UINT32)HDMI20_RX_AUD_CHEXTR_CTRL_6CH_3);
							}else if(gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL) == (UINT32)HDMI20_RX_AUD_CHEXTR_CTRL_6CH_3){	// 6ch-3
								gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL, (UINT32)HDMI20_RX_AUD_CHEXTR_CTRL_4CH_3);
							}else if(gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL) == (UINT32)HDMI20_RX_AUD_CHEXTR_CTRL_4CH_3){	// 4ch-3
								gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL, (UINT32)HDMI20_RX_AUD_CHEXTR_CTRL_8CH);
							}else{
								gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL, (UINT32)HDMI20_RX_AUD_CHEXTR_CTRL_8CH);
							}
							HDMI20_AUDIO("HDMI[%d] Audio ch-map chanege(0x%x)\n", port, gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL));
						}

						gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_FIFO_ICLR, (UINT32)HDMI20_RX_AUD_FIFO_ICLR_ENABLE);
						hdmi_rx_ctrl_audio_fifo_rst(&gHDMI20RxHandler[port].ctrl);
						gHDMI20RxHandler[port].audioChMapCnt = (UINT32)0;
					}
				}else {
					if(gHDMI20RxHandler[port].audioChMapCnt > (UINT32)0){
						gHDMI20RxHandler[port].audioChMapCnt--;
					}
				}
			}

			/* Audio info change check */
			// Audio type change
			if(data.audioType == LX_HDMI_AUDIO_NO_AUDIO || data.audioType != gHDMI20RxHandler[port].audioInfo.audioType){
				audioInfoChange = TRUE;
			}
			if(gHDMI20RxHandler[port].audioInfo.audioType != data.audioType){
				HDMI20_AUDIO("HDMI[%d] Audio type change(%d -> %d) \n", port, gHDMI20RxHandler[port].audioInfo.audioType, data.audioType);
				gHDMI20RxHandler[port].audioInfo.audioType = data.audioType;
			}

			// Audio sampling frequency change
			if(gHDMI20RxHandler[port].audioInfo.samplingFreq != data.samplingFreq){ //Added 2014/07/21 taejun.lee
				audioInfoChange = TRUE;
				HDMI20_AUDIO("HDMI[%d] Audio Fs change(%d -> %d) \n", port, gHDMI20RxHandler[port].audioInfo.samplingFreq, data.samplingFreq);
				gHDMI20RxHandler[port].audioInfo.samplingFreq = data.samplingFreq;
			}

#ifdef HDMI20_HAL_AUDIO_COUNT_OF_CHANNEL_ENABLE
			// Audio channel count change
			if(gHDMI20RxHandler[port].audioInfo.countOfChannel != data.countOfChannel){
				audioInfoChange = TRUE;
				HDMI20_AUDIO("HDMI[%d] Audio channel count change(%d -> %d) \n", port, gHDMI20RxHandler[port].audioInfo.countOfChannel, data.countOfChannel);
				gHDMI20RxHandler[port].audioInfo.countOfChannel = data.countOfChannel;
			}
#endif

			// Audio ACR N/CTS value change
			if(_gHdmiAudioInfoACR[port].n_param > gHDMI20RxHandler[port].ctrl.n_param) {
				nDiff = _gHdmiAudioInfoACR[port].n_param - gHDMI20RxHandler[port].ctrl.n_param;
			} else {
				nDiff = gHDMI20RxHandler[port].ctrl.n_param - _gHdmiAudioInfoACR[port].n_param;
			}
			if(_gHdmiAudioInfoACR[port].cts_param > gHDMI20RxHandler[port].ctrl.cts_param) {
				ctsDiff = _gHdmiAudioInfoACR[port].cts_param - gHDMI20RxHandler[port].ctrl.cts_param;
			} else {
				ctsDiff = gHDMI20RxHandler[port].ctrl.cts_param - _gHdmiAudioInfoACR[port].cts_param;
			}

			if((nDiff > HDMI20_HAL_ACR_N_MARGIN) || (ctsDiff > HDMI20_HAL_ACR_CTS_MARGIN)){
				audioInfoChange = TRUE;
				HDMI20_AUDIO("HDMI[%d] Audio ACR N/CTS change(n:%d -> %d, cts:%d -> %d) \n", port, _gHdmiAudioInfoACR[port].n_param, gHDMI20RxHandler[port].ctrl.n_param, _gHdmiAudioInfoACR[port].cts_param, gHDMI20RxHandler[port].ctrl.cts_param);
				_gHdmiAudioInfoACR[port].n_param = gHDMI20RxHandler[port].ctrl.n_param;
				_gHdmiAudioInfoACR[port].cts_param = gHDMI20RxHandler[port].ctrl.cts_param;
			}

			// Audio stream change
			if(gHDMI20RxHandler[port].audioInfo.stream!= data.stream){
				audioInfoChange = TRUE;
				HDMI20_AUDIO("HDMI[%d] Audio Stream change(%d -> %d) \n", port, gHDMI20RxHandler[port].audioInfo.stream, data.stream);
				gHDMI20RxHandler[port].audioInfo.stream = data.stream;
			}

			if(audioInfoChange == TRUE){
				gHDMI20RxHandler[port].audioStableCnt = (UINT32)0;
				gHDMI20RxHandler[port].audioChMapStandByCnt = (UINT32)0;
				gHDMI20RxHandler[port].audioForceMuteCnt = (UINT32)0;
				HDMI20_HAL_Rx_Set_AudioMuteControl(port, HDMI20_AUDIO_MUTE);
				gHDMI20RxHandler[port].isAudioMute = HDMI20_AUDIO_MUTE;
			}

			/* Audio Mute Control*/
			mute_status = gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_OUTPUT_MUTE_CTRL) & (UINT32)HDMI20_RX_AUD_OUTPUT_MUTE_CTRL_UNMUTE;
			if((gHDMI20RxHandler[port].audioStableCnt < gHDMI20RxDevAudControler[HDMI20__AUD_STABLE_TIME].value) && (mute_status == 1)){
				HDMI20_HAL_Rx_Set_AudioMuteControl(port, HDMI20_AUDIO_MUTE);
				gHDMI20RxHandler[port].isAudioMute = HDMI20_AUDIO_MUTE;
				HDMI20_AUDIO("HDMI[%d] Audio Cnt(%d) : Force Mute enalbe!\n", port, gHDMI20RxHandler[port].audioStableCnt);
			} else if((gHDMI20RxHandler[port].audio_change != TRUE) && (mute_status == (UINT32)0)\
				&& (gHDMI20RxHandler[port].audioStandByCnt == gHDMI20RxDevAudControler[HDMI20__AUD_STANDBY_TIME].value)\
				&& (gHDMI20RxHandler[port].audioStableCnt == gHDMI20RxDevAudControler[HDMI20__AUD_STABLE_TIME].value)\
				&& (gHDMI20RxHandler[port].audioFifoErrMuteCnt == gHDMI20RxDevAudControler[HDMI20__AUD_FIFO_ERR_MUTE_TIME].value)\
				&& (gHDMI20RxHandler[port].audioForceMuteCnt == gHDMI20RxDevAudControler[HDMI20__AUD_FORCE_MUTE_TIME].value)\
				&& (gHDMI20RxHandler[port].isAudioMuteControl == FALSE)){
				HDMI20_HAL_Rx_Set_AudioMuteControl(port, HDMI20_AUDIO_UNMUTE);
				gHDMI20RxHandler[port].isAudioMute = HDMI20_AUDIO_UNMUTE;
				HDMI20_AUDIO("HDMI[%d] Audio Cnt(%d) : Force Mute disable!\n", port, gHDMI20RxHandler[port].audioStableCnt);
			}
		}

		/* FIFO error check */
		if(((gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_FIFO_STS) != (UINT32)HDMI20_RX_AUD_FIFO_STS_PASS)\
			|| (gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_FIFO_ISTS) != (UINT32)HDMI20_RX_AUD_FIFO_ISTS_PASS))\
			&& (gHDMI20RxHandler[port].audioStableCnt != gHDMI20RxDevAudControler[HDMI20__AUD_STABLE].value)\
			&& (reg_hdmi_mode == (UINT32)1)\
			&& (gHDMI20RxDevAudControler[HDMI20__AUD_IGNORE_ERR].value == (UINT32)0x0)){
			HDMI20_HAL_Rx_Set_AudioMuteControl(port, HDMI20_AUDIO_MUTE);
			gHDMI20RxHandler[port].isAudioMute = HDMI20_AUDIO_MUTE;
			if(gHDMI20RxHandler[port].isPC == FALSE){
				gHDMI20RxHandler[port].audioFifoErrMuteCnt = (UINT32)0;
			}
			gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_FIFO_ICLR, (UINT32)HDMI20_RX_AUD_FIFO_ICLR_ENABLE);
			gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_DMI_SW_RST, (UINT32)HDMI20_RX_DMI_SW_RST_AUDIO);
			hdmi_rx_ctrl_audio_fifo_rst(&gHDMI20RxHandler[port].ctrl);
		}else if(gHDMI20RxHandler[port].audioFifoErrMuteCnt < gHDMI20RxDevAudControler[HDMI20__AUD_FIFO_ERR_MUTE_TIME].value){
			gHDMI20RxHandler[port].audioFifoErrMuteCnt++;
			if(gHDMI20RxDevAudControler[HDMI20__AUD_CNT_DBG].value != (UINT32)0)HDMI20_AUDIO("HDMI[%d] Audio FIFO err mute cnt : %d", port, gHDMI20RxHandler[port].audioFifoErrMuteCnt);
		}

		/* ACR error check */
		if(((gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_FIFO_STS) == (UINT32)0)\
			|| (gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_FIFO_ISTS) == (UINT32)0))\
			&& (gHDMI20RxDevAudControler[HDMI20__AUD_IGNORE_ERR].value == (UINT32)0x0)){
			if (gHDMI20RxHandler[port].audioAcrErrorCnt == gHDMI20RxDevAudControler[HDMI20__AUD_ACR_ERR_MAX].value) {
				gHDMI20RxHandler[port].top_write((UINT32)HDMI20_RX_ACR_PLL_MODE, (UINT32)0x110001 );
				gHDMI20RxHandler[port].top_write((UINT32)HDMI20_RX_ACR_PLL_MODE, (UINT32)0x110101 );
				gHDMI20RxHandler[port].top_write((UINT32)HDMI20_RX_ACR_PLL_MODE, (UINT32)0x110001 );
				gHDMI20RxHandler[port].top_write((UINT32)HDMI20_RX_ACR_PLL_MODE, (UINT32)0x10001 );
				gHDMI20RxHandler[port].audioAcrErrorCnt = (UINT32)0;
				HDMI20_AUDIO("HDMI[%d] Audio ACR reset!! \n", port);
			}else {
				gHDMI20RxHandler[port].audioAcrErrorCnt++;
				if(gHDMI20RxDevAudControler[HDMI20__AUD_CNT_DBG].value != (UINT32)0)HDMI20_AUDIO("HDMI[%d] Audio ARC err cnt : %d", port, gHDMI20RxHandler[port].audioAcrErrorCnt);
			}
		}
		

		/* Audio debug */
		if((gHDMI20RxDevAudControler[HDMI20__AUD_FORCE_ACR_RESET].value > (UINT32)0)\
			&& (reg_hdmi_mode == 1)){
			gHDMI20RxHandler[port].top_write((UINT32)HDMI20_RX_ACR_PLL_MODE, (UINT32)0x110001 );
			gHDMI20RxHandler[port].top_write((UINT32)HDMI20_RX_ACR_PLL_MODE, (UINT32)0x110101 );
			gHDMI20RxHandler[port].top_write((UINT32)HDMI20_RX_ACR_PLL_MODE, (UINT32)0x110001 );
			gHDMI20RxHandler[port].top_write((UINT32)HDMI20_RX_ACR_PLL_MODE, (UINT32)0x10001 );
			HDMI20_AUDIO("HDMI[%d] Audio Force ACR reset!! \n", port);
			gHDMI20RxDevAudControler[HDMI20__AUD_FORCE_ACR_RESET].value = (UINT32)0;
		}


		HDMI20_HAL_Rx_AudioForceInfoControl(port);
		HDMI20_HAL_Rx_AudioInfoPrint(port);
		HDMI20_HAL_Rx_AudioDebugIntialize(port);

		// Commit history
		if(gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)0x9999) {
			HDMI20_AUDIO("170703 : [Add] Register address and value define.\n");
			HDMI20_AUDIO("170703 : [Add] CSD update mask enable before audio start.\n");
			HDMI20_AUDIO("170707 : [Add] Dolby True-HD HBR audio type.\n");
			HDMI20_AUDIO("170710 : [Mod] Follow coding rules.\n");
			HDMI20_AUDIO("170712 : [Mod] Audio Count Define.\n");
			HDMI20_AUDIO("170714 : [Add] Audio CSD change interrupt.\n");
			HDMI20_AUDIO("170728 : [Mod] Audio Count.\n");
			HDMI20_AUDIO("170821 : [Mod] Audio debug menu.\n");
			HDMI20_AUDIO("170912 : [Mod] Audio debug menu2.\n");
			HDMI20_AUDIO("170926 : [Mod] AudioStableCnt reduction for audio mute delay reduction.(10 -> 5)\n");
			HDMI20_AUDIO("171010 : [Add] DTS High Resolution Audio type.\n");
			HDMI20_AUDIO("171012 : [Mod] return value.\n");
			HDMI20_AUDIO("171024 : [Rev] AudioStableCnt restoration for audio noise remove.(5 -> 10)\n");
			HDMI20_AUDIO("171024 : [Add] Ignore HDMI audio interrupt debug\n");
			HDMI20_AUDIO("171031 : [Mod] HDMI20__AUD_FIFO_ADJUST disable.\n");
			HDMI20_AUDIO("171108 : [Mod] HDMI20__AUD_FIFO_ADJUST modifiing and enable.\n");
			HDMI20_AUDIO("171115 : [Mod] HDMI audio interrupt ignore on PC connect.\n");
			HDMI20_AUDIO("171115 : [Mod] Ignore audioFifoErrMuteCnt initialize for PC mute issue.\n");
			HDMI20_AUDIO("171122 : [Add] Port info for debuging.\n");
			HDMI20_AUDIO("180423 : [Mod] M16P3 AUDIO_REG_ADDRESS setting.\n");
			HDMI20_AUDIO("180510 : [Mod] Increase HDMI20__AUD_STABLE_TIME(0xf -> 0x14).\n");
			HDMI20_AUDIO("180607 : [Mod] Audio info Pc error SW workaround.\n");
			HDMI20_AUDIO("180618 : [Mod] Audio info Pc change interrupt.\n");
			HDMI20_AUDIO("180802 : [Mod] Audio SPDIF change IRQ.\n");
			HDMI20_AUDIO("180802 : [Add] Audio ACR reset for FIFO recovery.\n");
			HDMI20_AUDIO("180807 : [Add] Pd change interrup disable.\n");
			HDMI20_AUDIO("180810 : [Add] FIFO adjust enable.\n");
			HDMI20_AUDIO("180816 : [Add] Audio configuration for HDMI Link reset.\n");
			HDMI20_AUDIO("180918 : [Mod] Delete layout conditional statement in channel mapping.\n");
			HDMI20_AUDIO("180918 : [Mod] ACR reset cnt init.\n");
			HDMI20_AUDIO("180918 : [Add] Default 8ch setting in channel mapping.\n");
			HDMI20_AUDIO("190226 : [Mod] DVI mode.\n");
			HDMI20_AUDIO("190227 : [Add] Unknown Audio type.\n");
			HDMI20_AUDIO("190409 : [Rev] Unknown Audio type.\n");
			HDMI20_AUDIO("190415 : [Mod] Video stable check change.\n");
			gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value = (UINT32)0;
		}

		ret = RET_OK;

	} while(0);

	return ret;

}

int HDMI20_HAL_Rx_Set_AudioMuteControl(UINT8 port, BOOLEAN mute)
{
	UINT32 ret = 0;
	if(mute == HDMI20_AUDIO_UNMUTE){
		gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_OUTPUT_MUTE_CTRL, (UINT32)HDMI20_RX_AUD_OUTPUT_MUTE_CTRL_UNMUTE);
		HDMI20_Rx_Audio_Path_SetUnmute(port);
	}else if((mute == HDMI20_AUDIO_MUTE) && (gHDMI20RxDevAudControler[HDMI20__AUD_FORCE_UNMUTE].value == (UINT32)0x0)){
		gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_OUTPUT_MUTE_CTRL, (UINT32)HDMI20_RX_AUD_OUTPUT_MUTE_CTRL_MUTE);
		HDMI20_Rx_Audio_Path_SetMute(port);
	}

	return ret;
}

int HDMI20_HAL_Rx_Set_AudioReset(UINT8 port)
{
	UINT32 ret = 0;
	// Mute
	HDMI20_HAL_Rx_Set_AudioMuteControl(port, HDMI20_AUDIO_MUTE);
	gHDMI20RxHandler[port].isAudioMute = HDMI20_AUDIO_MUTE;

	// Count initialize
	gHDMI20RxHandler[port].audioStandByCnt = (UINT32)0;
	gHDMI20RxHandler[port].audioStableCnt = (UINT32)0;
	gHDMI20RxHandler[port].audioChMapStandByCnt = (UINT32)0;
	gHDMI20RxHandler[port].audioForceMuteCnt = (UINT32)0;

	// FIFO clear
	gHDMI20RxHandler[port].ctrl.bsp_write((UINT16)HDMI20_RX_AUD_FIFO_ICLR, (UINT32)HDMI20_RX_AUD_FIFO_ICLR_ENABLE);
	hdmi_rx_ctrl_audio_fifo_rst(&gHDMI20RxHandler[port].ctrl);

	return ret;
}

int HDMI20_HAL_Rx_Get_AudioFreqFromTMDSClock(UINT8 port, unsigned int *samplingFreq)
{
	int ret = RET_OK;

	UINT64		ui64TmdsClock = 0;			//< HDMI measured clock value of TMDS clock
	UINT64		ui64AcrN = 0;				//< HDMI ACR N value
	UINT64		ui64AcrCts = 0;				//< HDMI ACR CTS value
	UINT64		ui64TmdsSamplingFreq = 0;	//< HDMI sampling frequency in source device from TMDS clock

	//Get measured frequency value of TMDS clock.
	ui64TmdsClock = (UINT64)(gHDMI20RxHandler[port].real_tmds_clk) * (UINT64)1000;

	//Get ACR N H/W value.
	ui64AcrN = gHDMI20RxHandler[port].ctrl.n_param;		//20 bits

	//Get ACR CTS H/W value.
	ui64AcrCts = gHDMI20RxHandler[port].ctrl.cts_param;	//20 bits

	//Compute a sampling frequency from TMDS clock
	ui64TmdsSamplingFreq = ui64AcrN * ui64TmdsClock;

	//Check divide by zero value.
	if ( (ui64TmdsSamplingFreq > (UINT64)0) && (ui64AcrCts > (UINT64)0) )
	{
		do_div(ui64TmdsSamplingFreq, ui64AcrCts * (UINT64)128);
	}

	//Mapping a sampling frequency from measuring from TMDS clock and ACR N & CTS H/W value
	if (ui64TmdsSamplingFreq == (UINT64)0){
		*samplingFreq = LX_HDMI_SAMPLING_FREQ_NONE;
	}else if (ui64TmdsSamplingFreq < (UINT64)22983){
		*samplingFreq = LX_HDMI_SAMPLING_FREQ_22_05KHZ;	//  22.05 kHz(not supported)
	}else if (ui64TmdsSamplingFreq < (UINT64)30000){
		*samplingFreq = LX_HDMI_SAMPLING_FREQ_24_KHZ;	//  24 kHz(not supported)
	}else if (ui64TmdsSamplingFreq < (UINT64)33800){
		*samplingFreq = LX_HDMI_SAMPLING_FREQ_32_KHZ;	//  32 kHz
	}else if (ui64TmdsSamplingFreq < (UINT64)45965){
		*samplingFreq = LX_HDMI_SAMPLING_FREQ_44_1KHZ;	//  44.1 kHz
	}else if (ui64TmdsSamplingFreq < (UINT64)67000){
		*samplingFreq = LX_HDMI_SAMPLING_FREQ_48_KHZ;	//  48 kHz
	}else if (ui64TmdsSamplingFreq < (UINT64)91935){
		*samplingFreq = LX_HDMI_SAMPLING_FREQ_88_2KHZ;	//  88.2 kHz
	}else if (ui64TmdsSamplingFreq < (UINT64)135000){
		*samplingFreq = LX_HDMI_SAMPLING_FREQ_96_KHZ;	//  96 kHz
	}else if (ui64TmdsSamplingFreq < (UINT64)183870){
		*samplingFreq = LX_HDMI_SAMPLING_FREQ_176_4KHZ;	//  176.4 kHz
	}else if (ui64TmdsSamplingFreq < (UINT64)210000){
		*samplingFreq = LX_HDMI_SAMPLING_FREQ_192_KHZ;	//  192 kHz
	}else{
		*samplingFreq = LX_HDMI_SAMPLING_FREQ_768_KHZ;	//  768 kHz(not supported)
	}

	return ret;
}

int HDMI20_HAL_Rx_AudioForceInfoControl(UINT8 port)
{
	UINT32 ret = 0;
	if(gHDMI20RxDevAudControler[HDMI20__AUD_FORCE_TYPE].value != (UINT32)0x0){
		gHDMI20RxHandler[port].audioInfo.audioType = gHDMI20RxDevAudControler[HDMI20__AUD_FORCE_TYPE].value;
	}

	if(gHDMI20RxDevAudControler[HDMI20__AUD_FORCE_FS].value != (UINT32)0x0){
		gHDMI20RxHandler[port].audioInfo.samplingFreq= gHDMI20RxDevAudControler[HDMI20__AUD_FORCE_FS].value;
	}

	if(gHDMI20RxDevAudControler[HDMI20__AUD_FORCE_CHANNEL].value != (UINT32)0x0){
		gHDMI20RxHandler[port].audioInfo.countOfChannel= gHDMI20RxDevAudControler[HDMI20__AUD_FORCE_CHANNEL].value;
	}

	if(gHDMI20RxDevAudControler[HDMI20__AUD_FORCE_STREAM].value != (UINT32)0x0){
		gHDMI20RxHandler[port].audioInfo.stream= gHDMI20RxDevAudControler[HDMI20__AUD_FORCE_STREAM].value;
	}

	return ret;
}

int HDMI20_HAL_Rx_AudioInfoPrint(UINT8 port)
{
	UINT32 ret = 0;

	if(gHDMI20RxHandler[port].audioDbgPrintCnt == (UINT32)0){
		if(gHDMI20RxDevAudControler[HDMI20__AUD_DATA].value > (UINT32)0){
			HDMI20_AUDIO("HDMI[%d] Audio Data : [0x%08x] [0x%08x] [0x%08x] [0x%08x]!\n",\
			port, gHDMI20RxHandler[port].top_read((UINT32)0xFA0) , gHDMI20RxHandler[port].top_read((UINT32)0xFA4), gHDMI20RxHandler[port].top_read((UINT32)0xFA8), gHDMI20RxHandler[port].top_read((UINT32)0xFAC));
			gHDMI20RxDevAudControler[HDMI20__AUD_DATA].value--;
		}

		if(gHDMI20RxDevAudControler[HDMI20__AUD_N_CTS].value > (UINT32)0){
			HDMI20_AUDIO("HDMI[%d] Audio ACR : N[0x%08x], CTS:[0x%08x]\n", port, gHDMI20RxHandler[port].ctrl.n_param, gHDMI20RxHandler[port].ctrl.cts_param);
			gHDMI20RxDevAudControler[HDMI20__AUD_N_CTS].value--;
		}

		if(gHDMI20RxDevAudControler[HDMI20__AUD_INFO].value > (UINT32)0){
			HDMI20_AUDIO("HDMI[%d] Audio INFO : Type[%d], Fs[%d], Channel[%d], Stream[%d]\n",\
			port, gHDMI20RxHandler[port].audioInfo.audioType, gHDMI20RxHandler[port].audioInfo.samplingFreq, gHDMI20RxHandler[port].audioInfo.countOfChannel, gHDMI20RxHandler[port].audioInfo.stream);
			gHDMI20RxDevAudControler[HDMI20__AUD_INFO].value--;
		}

		if(gHDMI20RxDevAudControler[HDMI20__AUD_CNT].value > (UINT32)0){
			HDMI20_AUDIO("HDMI[%d] Audio CNT : StandBy[%d/%d], Stable[%d/%d], FifoErr[%d/%d], ChMapStandBy[%d/%d], ChMap[%d/%d], IrqFifoErr[%d/%d], ForceMute[%d/%d], AcrReset[%d/%d]\n",\
			port, gHDMI20RxHandler[port].audioStandByCnt, gHDMI20RxDevAudControler[HDMI20__AUD_STANDBY_TIME].value,\
			gHDMI20RxHandler[port].audioStableCnt, gHDMI20RxDevAudControler[HDMI20__AUD_STABLE_TIME].value,\
			gHDMI20RxHandler[port].audioFifoErrMuteCnt, gHDMI20RxDevAudControler[HDMI20__AUD_FIFO_ERR_MUTE_TIME].value,\
			gHDMI20RxHandler[port].audioChMapStandByCnt, gHDMI20RxDevAudControler[HDMI20__AUD_CH_MAP_STANDBY_TIME].value,\
			gHDMI20RxHandler[port].audioChMapCnt, gHDMI20RxDevAudControler[HDMI20__AUD_CH_MAP_MAX].value,\
			gHDMI20RxHandler[port].audioIrqFifoErrCnt, gHDMI20RxDevAudControler[HDMI20__AUD_IRQ_FIFO_ERR_MAX].value,\
			gHDMI20RxHandler[port].audioForceMuteCnt, gHDMI20RxDevAudControler[HDMI20__AUD_FORCE_MUTE_TIME].value,\
			gHDMI20RxHandler[port].audioAcrResetCnt, gHDMI20RxDevAudControler[HDMI20__AUD_ACR_RESET_TIME].value);
			gHDMI20RxDevAudControler[HDMI20__AUD_CNT].value--;
		}

		if(gHDMI20RxDevAudControler[HDMI20__AUD_FIFO].value > (UINT32)0){
			HDMI20_AUDIO("HDMI[%d] Audio FIFO : Fill[0x%04x], Sts[%d], ItrSts[%d]\n",\
			port, gHDMI20RxHandler[port].ctrl.bsp_read(HDMI20_RX_AUD_FIFO_FILLSTS1), gHDMI20RxHandler[port].ctrl.bsp_read(HDMI20_RX_AUD_FIFO_STS), gHDMI20RxHandler[port].ctrl.bsp_read(HDMI20_RX_AUD_FIFO_ISTS));
			gHDMI20RxDevAudControler[HDMI20__AUD_FIFO].value--;
		}

		if(gHDMI20RxDevAudControler[HDMI20__AUD_MUTE].value > (UINT32)0){
			HDMI20_AUDIO("HDMI[%d] Audio MUTE : Sts[%d], Reg[0x%08x]\n",\
			port, gHDMI20RxHandler[port].isAudioMute, gHDMI20RxHandler[port].ctrl.bsp_read(HDMI20_RX_AUD_OUTPUT_MUTE_CTRL));
			gHDMI20RxDevAudControler[HDMI20__AUD_MUTE].value--;
		}

		if(gHDMI20RxDevAudControler[HDMI20__AUD_HBR].value > (UINT32)0){
			HDMI20_AUDIO("HDMI[%d] Audio HBR : Sts[%d]", port, gHDMI20RxHandler[port].isHBRaudio);
			HDMI20_AUDIO("[0x%04x]	AUD_CTRL		: [0x%08x]", HDMI20_RX_AUD_CTRL, gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_CTRL));
			HDMI20_AUDIO("[0x%04x]	AUD_PAO_CTRL		: [0x%08x]", HDMI20_RX_AUD_PAO_CTRL, gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_PAO_CTRL));
			HDMI20_AUDIO("[0x%08x]	AUD_CHEXTR_CTRL		: [0x%08x]", HDMI20_RX_AUD_CHEXTR_CTRL, gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL));
			gHDMI20RxDevAudControler[HDMI20__AUD_HBR].value--;
		}

		if(gHDMI20RxDevAudControler[HDMI20__AUD_PC].value > (UINT32)0){
			HDMI20_AUDIO("HDMI[%d] Audio PC:Sts[%d], SPD29:0x%02x \n", port, gHDMI20RxHandler[port].isPC, gHDMI20RxHandler[port].dataPacket[SPD][29]);
			gHDMI20RxDevAudControler[HDMI20__AUD_PC].value--;
		}

		if(gHDMI20RxDevAudControler[HDMI20__AUD_READ_TOP_REG].value > (UINT32)0){
			HDMI20_AUDIO("HDMI[%d] Audio TOP REG : address[0x%x], value[0x%x]", port, gHDMI20RxDevAudControler[HDMI20__AUD_READ_TOP_REG].value, gHDMI20RxHandler[port].top_read(gHDMI20RxDevAudControler[HDMI20__AUD_READ_TOP_REG].value));
			if(gHDMI20RxDevAudControler[HDMI20__AUD_REG_PRINT_REPEAT].value > (UINT32)0) gHDMI20RxDevAudControler[HDMI20__AUD_READ_TOP_REG].value = 0;
		}
		if(gHDMI20RxDevAudControler[HDMI20__AUD_READ_CTRL_REG].value > 0){
			HDMI20_AUDIO("HDMI[%d] Audio CTRL REG : address[0x%x], value[0x%x]", port, gHDMI20RxDevAudControler[HDMI20__AUD_READ_CTRL_REG].value, gHDMI20RxHandler[port].ctrl.bsp_read(gHDMI20RxDevAudControler[HDMI20__AUD_READ_CTRL_REG].value));
			if(gHDMI20RxDevAudControler[HDMI20__AUD_REG_PRINT_REPEAT].value > 0) gHDMI20RxDevAudControler[HDMI20__AUD_READ_CTRL_REG].value = 0;
		}

		gHDMI20RxHandler[port].audioDbgPrintCnt = gHDMI20RxDevAudControler[HDMI20__AUD_INFORMATION].value;
	}else if(gHDMI20RxHandler[port].audioDbgPrintCnt > 0){
		gHDMI20RxHandler[port].audioDbgPrintCnt--;
	}

	if(gHDMI20RxDevAudControler[HDMI20__AUD_REG].value != 0){
		HDMI20_AUDIO("HDMI[%d] Audio REG : \n", port);
		HDMI20_AUDIO("[0x%04x]	ACR_CLK_DIVIDER 	: [0x%08x]", HDMI20_RX_ACR_CLK_DIVIDER, gHDMI20RxHandler[port].top_read((UINT32)HDMI20_RX_ACR_CLK_DIVIDER));
		HDMI20_AUDIO("[0x%04x]	ACR_CLK_N_FS		: [0x%08x]", HDMI20_RX_ACR_CLK_N_FS, gHDMI20RxHandler[port].top_read((UINT32)HDMI20_RX_ACR_CLK_N_FS));
		HDMI20_AUDIO("[0x%04x]	AUD_CTRL		: [0x%08x]", HDMI20_RX_AUD_CTRL, gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_CTRL));
		HDMI20_AUDIO("[0x%04x]	AUD_CLK_CTRL		: [0x%08x]", HDMI20_RX_AUD_CLK_CTRL, gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_CLK_CTRL));
		HDMI20_AUDIO("[0x%04x]	AUD_PLL_CTRL		: [0x%08x]", HDMI20_RX_AUD_PLL_CTRL, gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_PLL_CTRL));
		HDMI20_AUDIO("[0x%04x]	HDMI_CKM_EVLTM		: [0x%08x]", HDMI20_RX_HDMI_CKM_EVLTM, gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_HDMI_CKM_EVLTM));
		HDMI20_AUDIO("[0x%04x]	HDMI_CKM_F		: [0x%08x]", HDMI20_RX_HDMI_CKM_F, gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_HDMI_CKM_F));
		HDMI20_AUDIO("[0x%04x]	AUD_FIFO_TH		: [0x%08x]", HDMI20_RX_AUD_FIFO_TH, gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_FIFO_TH));
		HDMI20_AUDIO("[0x%04x]	PDEC_ASP_CTRL		: [0x%08x]", HDMI20_RX_PDEC_ASP_CTRL, gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_PDEC_ASP_CTRL));
		HDMI20_AUDIO("[0x%04x]	AUD_FIFO_CTRL		: [0x%08x]", HDMI20_RX_AUD_FIFO_CTRL, gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_FIFO_CTRL));
		HDMI20_AUDIO("[0x%04x]	HDMI_RESMPL_CTRL	: [0x%08x]", HDMI20_RX_HDMI_RESMPL_CTRL, gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_HDMI_RESMPL_CTRL));
		HDMI20_AUDIO("[0x%04x]	AUD_MUTE_CTRL		: [0x%08x]", HDMI20_RX_AUD_MUTE_CTRL, gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_MUTE_CTRL));
		HDMI20_AUDIO("[0x%04x]	AUD_PAO_CTRL		: [0x%08x]", HDMI20_RX_AUD_PAO_CTRL, gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_PAO_CTRL));
		HDMI20_AUDIO("[0x%08x]	PDEC_AIF_CTRL		: [0x%08x]", HDMI20_RX_PDEC_AIF_CTRL, gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_PDEC_AIF_CTRL));
		HDMI20_AUDIO("[0x%08x]	AUD_CHEXTR_CTRL		: [0x%08x]", HDMI20_RX_AUD_CHEXTR_CTRL, gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_CHEXTR_CTRL));
		HDMI20_AUDIO("[0x%08x]	AUD_OUTPUT_MUTE_CTRL	: [0x%08x]", HDMI20_RX_AUD_OUTPUT_MUTE_CTRL, gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_OUTPUT_MUTE_CTRL));
		gHDMI20RxDevAudControler[HDMI20__AUD_REG].value = (UINT32)0;
	}

	return ret;
}

int HDMI20_HAL_Rx_AudioDebugIntialize(UINT8 port)
{
	int ret = 0;

	if(gHDMI20RxDevAudControler[HDMI20__AUD_ALL_DEBUG_INIT].value != (UINT32)0x0){
		HDMI20_AUDIO("All Audio Debug Initialize!!!\n");
		gHDMI20RxDevAudControler[HDMI20__AUD_DEBUG_INIT].value = (UINT32)0x1;
		gHDMI20RxDevAudControler[HDMI20__AUD_COUNT_INIT].value = (UINT32)0x1;
		gHDMI20RxDevAudControler[HDMI20__AUD_CONTROL_INIT].value = (UINT32)0x1;
		gHDMI20RxDevAudControler[HDMI20__AUD_INFORMATION_INIT].value = (UINT32)0x1;

		gHDMI20RxDevAudControler[HDMI20__AUD_ALL_DEBUG_INIT].value = (UINT32)0x0;
	}

	if(gHDMI20RxDevAudControler[HDMI20__AUD_DEBUG_INIT].value != (UINT32)0x0){
		HDMI20_AUDIO("All debug print initialize!\n");
		gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value = (UINT32)0x0;
		gHDMI20RxDevAudControler[HDMI20__AUD_CNT_DBG].value = (UINT32)0x0;
		gHDMI20RxDevAudControler[HDMI20__AUD_IRQ_DBG].value = (UINT32)0x0;
		gHDMI20RxDevAudControler[HDMI20__AUD_CSD_IRQ_DBG].value = (UINT32)0x0;

		gHDMI20RxDevAudControler[HDMI20__AUD_DEBUG_INIT].value = (UINT32)0x0;
	}

	if(gHDMI20RxDevAudControler[HDMI20__AUD_COUNT_INIT].value != (UINT32)0x0){
		HDMI20_AUDIO("All count value initialize!\n");
		gHDMI20RxDevAudControler[HDMI20__AUD_STANDBY_TIME].value = (UINT32)0x3;
		gHDMI20RxDevAudControler[HDMI20__AUD_STABLE_TIME].value = (UINT32)0xA;
		gHDMI20RxDevAudControler[HDMI20__AUD_STABLE].value = (UINT32)0x9;
		gHDMI20RxDevAudControler[HDMI20__AUD_FIFO_ERR_MUTE_TIME].value = (UINT32)0x6;
		gHDMI20RxDevAudControler[HDMI20__AUD_CH_MAP_STANDBY_TIME].value = (UINT32)0xA;
		gHDMI20RxDevAudControler[HDMI20__AUD_CH_MAP_MAX].value = (UINT32)0x3;
		gHDMI20RxDevAudControler[HDMI20__AUD_IRQ_FIFO_ERR_MAX].value = (UINT32)0x5;
		gHDMI20RxDevAudControler[HDMI20__AUD_FORCE_MUTE_TIME].value = (UINT32)0xF;
		gHDMI20RxDevAudControler[HDMI20__AUD_ACR_RESET_TIME].value = (UINT32)0x1;

		gHDMI20RxDevAudControler[HDMI20__AUD_COUNT_INIT].value = (UINT32)0x0;
	}

	if(gHDMI20RxDevAudControler[HDMI20__AUD_CONTROL_INIT].value != (UINT32)0x0){
		HDMI20_AUDIO("All control value initialize!\n");
		gHDMI20RxDevAudControler[HDMI20__AUD_IGNORE_ERR].value = (UINT32)0x0;
		gHDMI20RxDevAudControler[HDMI20__AUD_FORCE_UNMUTE].value = (UINT32)0x0;
		gHDMI20RxDevAudControler[HDMI20__AUD_REG_PRINT_REPEAT].value = (UINT32)0x1;

		gHDMI20RxDevAudControler[HDMI20__AUD_CONTROL_INIT].value = (UINT32)0x0;
	}

	if(gHDMI20RxDevAudControler[HDMI20__AUD_INFORMATION_INIT].value != (UINT32)0x0){
		HDMI20_AUDIO("All information print initialize!\n");
		gHDMI20RxDevAudControler[HDMI20__AUD_DATA].value = (UINT32)0x0;
		gHDMI20RxDevAudControler[HDMI20__AUD_N_CTS].value = (UINT32)0x0;
		gHDMI20RxDevAudControler[HDMI20__AUD_INFO].value = (UINT32)0x0;
		gHDMI20RxDevAudControler[HDMI20__AUD_CNT].value = (UINT32)0x0;
		gHDMI20RxDevAudControler[HDMI20__AUD_FIFO].value = (UINT32)0x0;
		gHDMI20RxDevAudControler[HDMI20__AUD_MUTE].value = (UINT32)0x0;
		gHDMI20RxDevAudControler[HDMI20__AUD_REG].value = (UINT32)0x0;

		gHDMI20RxDevAudControler[HDMI20__AUD_INFORMATION_INIT].value = (UINT32)0x0;
	}

	return ret;
}

/* SEETV */
int KDRV_HDMI20_HAL_Rx_GetAudioInfo(UINT8 port, LX_HDMI_AUDIO_INFO_T *pHdmiAudioInfo, int size)
{
	int ret = RET_ERROR;
	LX_HDMI_AUDIO_INFO_T	data;
	UINT32	reg_hdmi_mode = 0;
	
	if((UINT16)gHDMI20RxHandler[port].timing_info.dvi){
		reg_hdmi_mode = 0;
	}else{
		reg_hdmi_mode = 1;
	}

	do{
		if(pHdmiAudioInfo == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(LX_HDMI_AUDIO_INFO_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI_AUDIO_INFO_T), size);
			break;
		}

		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Added 2014/08/04 taejun.lee */
		if((reg_hdmi_mode == 1) && ((HDMI20_HAL_Rx_IsLocalMuteOn(port) > 0) || (gHDMI20RxHandler[port].audio_change == TRUE) || (gHDMI20RxHandler[port].ctrl.isMute == TRUE)\
			|| (gHDMI20RxHandler[port].audioStandByCnt < gHDMI20RxDevAudControler[HDMI20__AUD_STANDBY_TIME].value)\
			|| (gHDMI20RxHandler[port].audioFifoErrMuteCnt < gHDMI20RxDevAudControler[HDMI20__AUD_FIFO_ERR_MUTE_TIME].value)\
			|| (gHDMI20RxHandler[port].audioStableCnt < gHDMI20RxDevAudControler[HDMI20__AUD_STABLE_TIME].value))) {
			data.audioType	= LX_HDMI_AUDIO_NO_AUDIO;
		} else {
			data.audioType	= gHDMI20RxHandler[port].audioInfo.audioType;
		}

		data.samplingFreq =  gHDMI20RxHandler[port].audioInfo.samplingFreq;
		data.countOfChannel = gHDMI20RxHandler[port].audioInfo.countOfChannel;
		data.stream = gHDMI20RxHandler[port].audioInfo.stream;

		memcpy((LX_HDMI_AUDIO_INFO_T *)pHdmiAudioInfo, &data, sizeof(LX_HDMI_AUDIO_INFO_T));

		if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)5) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)6)){
			HDMI20_AUDIO("HDMI[%d] audiotype:%d, samplingFreq:%d, countOfChannel:%d(%d)\n", port, data.audioType, data.samplingFreq, data.countOfChannel, gHDMI20RxHandler[port].audioInfo.countOfChannel);
			if(gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)5) gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value = (UINT32)0;
		}

		ret = RET_OK;

	} while(0);

	return ret;

}

int KDRV_HDMI20_HAL_Rx_GetAudioAcrInfo(UINT8 port, LX_HDMI_AUDIO_INFO_ACR_T *pHdmiAudioInfoAcr, int size)
{
	int ret = RET_ERROR;
	LX_HDMI_AUDIO_INFO_ACR_T	data;
	UINT32	reg_hdmi_mode = 0;

	do{
		if(pHdmiAudioInfoAcr == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(LX_HDMI_AUDIO_INFO_ACR_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI_AUDIO_INFO_ACR_T), size);
			break;
		}

		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		data.n_param =  gHDMI20RxHandler[port].ctrl.n_param;
		data.cts_param = gHDMI20RxHandler[port].ctrl.cts_param;

		memcpy((LX_HDMI_AUDIO_INFO_ACR_T *)pHdmiAudioInfoAcr, &data, sizeof(LX_HDMI_AUDIO_INFO_ACR_T));

		if((gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)9) || (gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)10)){
			HDMI20_AUDIO("HDMI[%d] n:%d, cts:%d\n", port, gHDMI20RxHandler[port].ctrl.n_param, gHDMI20RxHandler[port].ctrl.cts_param);
			if(gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value == (UINT32)9) gHDMI20RxDevAudControler[HDMI20__AUD_LINE_DBG].value = (UINT32)0;
		}

		ret = RET_OK;

	} while(0);

	return ret;

}


int KDRV_HDMI20_HAL_Rx_GetAudioCopyInfo(UINT8 port, LX_HDMI_AUDIO_COPY_T *pHdmiCopyInfo, int size)
{
	int ret = RET_OK;

	UINT32	reg_achst_byte0, reg_achst_byte1;
	UINT32	CpBit, LBit;

	LX_HDMI_AUDIO_COPY_T hdmiCopyInfo;

	//Check a HDMI Link Number
	if (port >= HDMI20_NUM_OF_RX_PORTS)
	{
		HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
		return RET_ERROR;
	}

	//Get a hdmi audio copyright information.
	if ((UINT16)gHDMI20RxHandler[port].timing_info.dvi == TRUE)	//HDMI Mode
	{
		//Read  reg_achst_byte0 reg.
		//reg_achst_byte0 = gHDMI20RxHandler[port].top_read(0x70);
		reg_achst_byte0 = gHDMI20AudioRegData.byte0;

		//Set a CpBit
		if (reg_achst_byte0 & (UINT32)HDMI_AUDIO_CP_BIT_MASK)
			CpBit = (UINT32)1;
		else
			CpBit = (UINT32)0;

		//Read  reg_achst_byte1reg.
		//reg_achst_byte1 = gHDMI20RxHandler[port].top_read(0x74);
		reg_achst_byte1 = gHDMI20AudioRegData.byte1;

		//Set a LBit
		if (reg_achst_byte1 & (UINT32)HDMI20_AUDIO_L_BIT_MASK)
			LBit = (UINT32)1;
		else
			LBit = (UINT32)0;

		//Set a Copyright Info. by CpBit and LBit
		if ((CpBit == (UINT32)0) && (LBit == (UINT32)0))
			hdmiCopyInfo = LX_HDMI_AUDIO_COPY_ONCE;
		else if ((CpBit == (UINT32)0) && (LBit == (UINT32)1))
			hdmiCopyInfo = LX_HDMI_AUDIO_COPY_NO_MORE;	//same with LX_HDMI_AUDIO_COPY_NEVER
		else
			hdmiCopyInfo = LX_HDMI_AUDIO_COPY_FREE;

	}
	else	//DVI Mode
	{
		hdmiCopyInfo = LX_HDMI_AUDIO_COPY_FREE;
	}

	memcpy((LX_HDMI_AUDIO_COPY_T *)pHdmiCopyInfo, &hdmiCopyInfo, sizeof(LX_HDMI_AUDIO_COPY_T));

	HDMI20_AUDIO("HDMI[%d] HDMI_GetAudioCopyInfo :CopyInfo = %d\n", port, hdmiCopyInfo);
	return ret;
}

int KDRV_HDMI20_HAL_Rx_Set_HDMIARC(UINT8 port, BOOLEAN bOnOff)
{
	int ret = RET_OK;

	do{
		if(port >= HDMI20_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

        if(port != 0){
            port = gHDMI20_supported_ARC_port;
            HDMI20_AUDIO("Set ARC port value error!. fixed 0.\n");
        }

		gHDMI20RxHandler[port].isAudioARCMode = bOnOff;

		/* Added 2014/07/02 taejun.lee */
		gHDMI20RxHandler[port].top_write((UINT32)HDMI20_RX_AD_MAIN_ARC_SET, (UINT32)bOnOff);
		gHDMI20RxHandler[port].top_write((UINT32)HDMI20_RX_AD_MAIN_PHY_ARC, ((UINT32)HDMI20_RX_AD_MAIN_PHY_ARC_DEFAULT + (UINT32)bOnOff)); // default : 20

		HDMI20_AUDIO("HDMI[%d] SetHDMIARC : ARCmode(%d)", port, gHDMI20RxHandler[port].isAudioARCMode);
		HDMI20_INFO("Notice %d : ARC Enable called with bOnOff[%d]\n", port,  bOnOff);

	} while(0);

	return ret;
}

int KDRV_HDMI20_HAL_Rx_Set_AudioMute(UINT8 port, LX_HDMI_MUTE_CTRL_T *pMuteCtrl, int size)
{
	int ret = RET_OK;

	HDMI20_AUDIO("HDMI[%d] HDMI20_HAL_Rx_Set_AudioMute :mutecnt(%d)\n", port, gHDMI20RxHandler[port].audioStandByCnt);

	do{
		BOOLEAN 	audioMuteState;
		LX_HDMI_MUTE_CTRL_T muteCtrl;

		//Check a HDMI Link Number
		if (port >= HDMI20_NUM_OF_RX_PORTS)
		{
			HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
			return RET_ERROR;
		}

		//Bring audio mute state from register
		//audioMuteState = !(gHDMI20RxHandler[port].ctrl.bsp_read((UINT32)HDMI20_RX_AUD_OUTPUT_MUTE_CTRL_MUTE) & (UINT32)HDMI20_RX_AUD_OUTPUT_MUTE_CTRL_UNMUTE);
		if((gHDMI20RxHandler[port].ctrl.bsp_read((UINT16)HDMI20_RX_AUD_OUTPUT_MUTE_CTRL) & (UINT32)HDMI20_RX_AUD_OUTPUT_MUTE_CTRL_UNMUTE) == (UINT32)0){
			audioMuteState = TRUE;
		}else{
			audioMuteState = FALSE;
		}

		memset((void *)&muteCtrl, 0, sizeof(LX_HDMI_MUTE_CTRL_T));
		memcpy(&muteCtrl, (void __user *)pMuteCtrl, sizeof(LX_HDMI_MUTE_CTRL_T));

		//audio related.
		if ((muteCtrl.eMode == LX_HDMI_AUDIO_MUTE) || (muteCtrl.eMode == LX_HDMI_AV_MUTE))
		{
			//Check a previous state
			if (muteCtrl.bAudioMute != audioMuteState)
			{
				if (muteCtrl.bAudioMute == TRUE)
				{
					//Mute audio data
					HDMI20_HAL_Rx_Set_AudioMuteControl(port, HDMI20_AUDIO_MUTE);
					HDMI20_AUDIO("HDMI[%d] audio Mute enable !\n", port);
					gHDMI20RxHandler[port].isAudioMute = HDMI20_AUDIO_MUTE;
					gHDMI20RxHandler[port].isAudioMuteControl = TRUE;
				}
				else
				{
					//Un-mute audio data
					if(((gHDMI20RxHandler[port].audio_change == FALSE) && (gHDMI20RxHandler[port].ctrl.isMute == FALSE)\
						&& (gHDMI20RxHandler[port].audioStandByCnt == gHDMI20RxDevAudControler[HDMI20__AUD_STANDBY_TIME].value))\
						|| (gHDMI20RxHandler[port].audioStableCnt == gHDMI20RxDevAudControler[HDMI20__AUD_STABLE_TIME].value)) {
						HDMI20_HAL_Rx_Set_AudioMuteControl(port, HDMI20_AUDIO_UNMUTE);
						HDMI20_AUDIO("HDMI[%d] audio Mute disable!\n", port);
						gHDMI20RxHandler[port].isAudioMute = HDMI20_AUDIO_UNMUTE;
					}
					gHDMI20RxHandler[port].isAudioMuteControl = FALSE;
				}

				//For debug print
				HDMI20_AUDIO("[%d] %s : port = %d, bAudioMute = %s \n",	\
							__L__, __F__, port, (muteCtrl.bAudioMute ? "On" : "Off"));
			}

			//For debug print
			if (muteCtrl.bAudioMute == FALSE)
			{
				HDMI20_AUDIO("[%d]SetMute : port = %d, type = %d, freq = %d, mute = %d\n", \
							__L__, port, gHDMI20RxHandler[port].audioInfo.audioType, gHDMI20RxHandler[port].audioInfo.samplingFreq, \
							audioMuteState);
			}
		}
	} while(0);

	return ret;
}

EXPORT_SYMBOL (KDRV_HDMI20_HAL_Rx_GetAudioInfo);
EXPORT_SYMBOL (KDRV_HDMI20_HAL_Rx_GetAudioAcrInfo);
EXPORT_SYMBOL (KDRV_HDMI20_HAL_Rx_Set_AudioMute);
EXPORT_SYMBOL (KDRV_HDMI20_HAL_Rx_GetAudioCopyInfo);
EXPORT_SYMBOL (KDRV_HDMI20_HAL_Rx_Set_HDMIARC);


