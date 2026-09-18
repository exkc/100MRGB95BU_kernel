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
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/spinlock.h>
#include <linux/spinlock_types.h>
#include <linux/slab.h> 	/**< kmalloc() */
#include <linux/semaphore.h>
#include <linux/platform_device.h>
#include <asm/io.h>

#include "hdmi21_rx_audio.h"
#include "hdmi21_earc_driver.h"

#include "hdmi21_hal_driver.h"
#include "hdmi21_rx_disland.h" /* Data island control */
#include "hdmi21_rx_snps_isrunit.h"
#include "hdmi21_rx_snps_vproc.h"
#include "hdmi21_rx_snps_misc.h"

//#include "./synopsys_api/hdmi_rx_ctrl.h"
#include "../hdmi20_drv.h"

#include "hdmi_kapi.h"

#include "os_util.h"
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
//#define HDMI21_HAL_ACR_N_MARGIN		100
//#define HDMI21_HAL_ACR_CTS_MARGIN	500

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#ifndef E_TO_S
#define E_TO_S(x) #x
#endif

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
#define HDMI21_AUDIO_REG_WR(address,data)   \
	__sMapped_address_audio=(UINT32 *)ioremap(address, sizeof(UINT32));\
do{\
	if(__sMapped_address_audio == NULL) break;\
	*__sMapped_address_audio = data;\
	iounmap((void *)__sMapped_address_audio);\
}while(0);\

#define HDMI21_AUDIO_REG_RD(address,data)   \
	__sMapped_address_audio = (UINT32 *)ioremap(address, sizeof(UINT32));\
do{\
	if(__sMapped_address_audio == NULL) {data = 0; break;}\
	data = (unsigned int)*__sMapped_address_audio;\
	iounmap((void *)__sMapped_address_audio);\
}while(0);\

typedef struct
{
	UINT32 mask;
	UINT32 clear;
	UINT32 force;
	UINT32 status;
	void (*irqFunc)(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
	UINT32 bitfield;
} HDMI21_AUDIO_ISRUNIT_SNPS_CTR_REG_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern HDMI21_HAL_RX_DEVICE_DATA gHDMI21RxHandler[HDMI21_NUM_OF_MAX_PORTS];
extern HDMI20_DEV_CONTROL_T	gHDMI21RxDevVideoControler[HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM];
extern HDMI20_DEV_CONTROL_T		gHDMI21RxDevLinkControler[HDMI21__DEV_LINK_CONTROL_LIST_MAXNUM];

/* Number of Max operable ports */
extern int		g_hdmi20_number_of_ports;
/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
/* Audio Status */
static unsigned int *__sMapped_address_audio;

HDMI21_HAL_RX_AUDIO_DATA gHDMI21RxAudioHandler[HDMI21_NUM_OF_MAX_PORTS];


/* Device controler : This contols the behavior of the Driver */
HDMI20_DEV_CONTROL_T	gHDMI21RxDevAudioControler[HDMI21__DEV_AUDIO_CONTROL_LIST_MAXNUM]=
{
	/* DBG */
	{E_TO_S(HDMI21__AUDIO_DEBUG), 				0x0,		"====== [Debug : 20250613] ========="},
	{E_TO_S(HDMI21__AUDIO_LINE_DBG), 				0x0,		"Activating specific conditions"},
	{E_TO_S(HDMI21__AUDIO_CNT_DBG), 				0x0,		"Audio count log enable"},
	{E_TO_S(HDMI21__AUDIO_IRQ_DBG), 				0x0,		"Audio interrupt log enable"},
	{E_TO_S(HDMI21__AUDIO_CSD_IRQ_DBG), 			0x0,		"Audio CSD interrupt log enable"},

	/* Count */
	{E_TO_S(HDMI21__AUDIO_COUNT), 				0x0,		"====== [Count] ========="},
	{E_TO_S(HDMI21__AUDIO_STANDBY_TIME),			0x5,		"Audio stand by time"},
	{E_TO_S(HDMI21__AUDIO_STABLE_TIME),			HDMI21_AUDIO_STABLE_CNT_INITIAL,		"Audio stable time"},
	{E_TO_S(HDMI21__AUDIO_STABLE_TIME_O22),		HDMI21_AUDIO_STABLE_CNT_INITIAL_O22,	"Audio stable"},
	{E_TO_S(HDMI21__AUDIO_STABLE),				(HDMI21_AUDIO_STABLE_CNT_INITIAL-1),		"Audio stable time"},
	{E_TO_S(HDMI21__AUDIO_STABLE_O22),			(HDMI21_AUDIO_STABLE_CNT_INITIAL_O22-1),	"Audio stable"},
	{E_TO_S(HDMI21_AUDIO_UNKWON_TYPE_MUTE),		HDMI21_AUDIO_UNKWON_TYPE_MUTE_CNT_INITIAL,	"Audio unknown type mute"},
	{E_TO_S(HDMI21__AUDIO_ABNORMAL),		0x10,	"Audio abnormal"},
	{E_TO_S(HDMI21__AUDIO_HBR_ABNORMAL),		0x20,	"Audio HBR abnormal"},
	{E_TO_S(HDMI21__AUDIO_TYPE_ABNORMAL),		0x20,	"Audio Type abnormal"},
	{E_TO_S(HDMI21__AUDIO_FIFO_ABNORMAL),		0x20,	"Audio FIFO abnormal"},
	{E_TO_S(HDMI21__AUDIO_CHANNEL_ABNORMAL),		0x10,	"Audio channel abnormal"},
	{E_TO_S(HDMI21__AUDIO_PRINT_LIMIT),			0x20,	"Audio FIFO error print limit"},
	{E_TO_S(HDMI21__AUDIO_FIFO_ERR_MUTE_TIME),	0x9,		"Audio FIFO error mute time"},
	{E_TO_S(HDMI21__AUDIO_CH_MAP_STANDBY_TIME),	0x9,		"Audio channel mapping stand by time"},
	{E_TO_S(HDMI21__AUDIO_CH_MAP_MAX),			0x4,		"Audio channel mapping max"},
	{E_TO_S(HDMI21__AUDIO_IRQ_FIFO_ERR_MAX),		0x8,		"Audio interrupt FIFO error max"},
	{E_TO_S(HDMI21__AUDIO_ACR_ERR_MAX),			0xA,		"Audio ACR error max"},
	{E_TO_S(HDMI21__AUDIO_FORCE_MUTE_TIME),		0x8,		"Audio force mute time"},
	{E_TO_S(HDMI21__AUDIO_FORCE_MUTE_TIME_O22),		0xF,		"Audio force mute time"},
	{E_TO_S(HDMI21__AUDIO_FORCE_DISABLE),		0x0,		"Audio force mute disable"},
	{E_TO_S(HDMI21__AUDIO_ACR_RESET_TIME),		0x1,		"Audio ACR reset time"},
	{E_TO_S(HDMI21__AUDIO_CHANNEL_INCREASE_TIME),	0x30,		"Audio channel increase time"},

	/* Control */
	{E_TO_S(HDMI21__AUDIO_CONTROL), 				0x0,		"====== [Control] ======="},
	{E_TO_S(HDMI21__AUDIO_IGNORE_ERR),			0x0,		"Ignore audio errors"},
	{E_TO_S(HDMI21__AUDIO_IGNORE_IRQ),			0x0,		"Ignore HDMI audio interrupt"},
	{E_TO_S(HDMI21__AUDIO_IGNORE_CHANNEL),		0x0,		"Ignore HDMI audio channel"},
	{E_TO_S(HDMI21__AUDIO_FORCE_UNMUTE),			0x0,		"Force audio mute"},
	{E_TO_S(HDMI21__AUDIO_FORCE_TYPE),			0x0,		"Force audio type"},
	{E_TO_S(HDMI21__AUDIO_FORCE_FS),				0x0,		"Force audio sampplig frequency"},
	{E_TO_S(HDMI21__AUDIO_FORCE_CHANNEL),			0x0,		"Force audio channel"},
	{E_TO_S(HDMI21__AUDIO_FORCE_STREAM),			0x0,		"Force audio stream"},
	{E_TO_S(HDMI21__AUDIO_FORCE_ACR_RESET),		0x0,		"Audio ACR reset"},
	{E_TO_S(HDMI21__AUDIO_FORCE_UNKNOWN_TYPE),	0x0,		"Force unknown type"},
	{E_TO_S(HDMI21__AUDIO_FORCE_HBR),			0x0,		"Force HBR mode set(0:off, 1:normal, 2:)"},
	{E_TO_S(HDMI21__AUDIO_MANUAL_N_CTS),		0x0,		"Manual ACR N/CTS"},
	{E_TO_S(HDMI21__AUDIO_DISABLE_SPREAD),		0x0,		"Disable HBR Spread"},
	{E_TO_S(HDMI21__AUDIO_STATE_INIT),			0x0,		"State Init"},
	{E_TO_S(HDMI21__AUDIO_TEST),				0x0,		"Test"},

#if 0
	{E_TO_S(HDMI21__AUD_FORCE_UNKNOWN_TYPE),	0x0,		"Force Audio unknown type"},
#endif
	{E_TO_S(HDMI21__AUDIO_IRQ_DISABLE_PCD),		0x1,		"Audio PCD interrupt disable"},
	{E_TO_S(HDMI21__AUDIO_IRQ_DISABLE_SPDIF),		0x0,		"Audio SPDIF interrupt disable"},
	{E_TO_S(HDMI21__AUDIO_FIFO_ADJUST),			0x20,		"Audio FIFO adjustment"},
	{E_TO_S(HDMI21__AUDIO_FIFO_ADJUST_MAX_CNT),			0x20,		"Audio FIFO adjustment max count"},
	{E_TO_S(HDMI21__AUDIO_REG_PRINT_REPEAT),		0x1,		"Audio register print repeat"},
	{E_TO_S(HDMI21__AUDIO_FIFO_ERROR_PRINT_DISABLE),		0x0,		"Audio FIFO error print disable"},

	/* Info */
	{E_TO_S(HDMI21__AUDIO_INFORMATION),			0xA,		"====== [Information] ==="},
	{E_TO_S(HDMI21__AUDIO_DATA),					0x0,		"Input audio data sample"},
	{E_TO_S(HDMI21__AUDIO_N_CTS),					0x0,		"ACR N/CTS value"},
	{E_TO_S(HDMI21__AUDIO_CLOCK),					0x0,		"Clock value"},
	{E_TO_S(HDMI21__AUDIO_INFO),					0x0,		"Input audio information : type, Fs, channel, stream, word length"},
	{E_TO_S(HDMI21__AUDIO_USR_INFO),				0x0,		"User audio information : type, Fs, channel, stream, word length"},
	{E_TO_S(HDMI21__AUDIO_CNT),					0x0,		"Audio count value(present/stable)"},
	{E_TO_S(HDMI21__AUDIO_FUNC_CALL),					0x0,		"Calling Function"},
	{E_TO_S(HDMI21__AUDIO_FIFO),					0x0,		"FIFO state"},
	{E_TO_S(HDMI21__AUDIO_FIFO_DIFF),					0x0,		"FIFO diff"},
	{E_TO_S(HDMI21__AUDIO_MUTE),					0x0,		"Audio mute state"},
	{E_TO_S(HDMI21__AUDIO_HBR),					0x0,		"Audio HBR state"},
	{E_TO_S(HDMI21__AUDIO_PC),					0x0,		"PC connect"},
	{E_TO_S(HDMI21__AUDIO_REG),					0x0,		"Audio register value"},
	{E_TO_S(HDMI21__AUDIO_CHANNEL_STATUS),			0x0,		"Audio Channel Status"},
	{E_TO_S(HDMI21__AUDIO_STATE),				0x0,		"Audio state change"},
	{E_TO_S(HDMI21__AUDIO_PROC_CONFIG0_SETTING),0x0,		"Audio proc_config0 setting value"},
	{E_TO_S(HDMI21__AUDIO_CSD_DATA),			0x0,		"Audio channel status data"},
	{E_TO_S(HDMI21__AUDIO_READ_TOP_REG),			0x0,		"Top register read"},
	{E_TO_S(HDMI21__AUDIO_READ_LINK_REG),			0x0,		"Ctrl register read"},

	/* DBG Init */
	{E_TO_S(HDMI21__AUDIO_INITIALIZE), 			0x0,		"====== [Initialize] ===="},
	{E_TO_S(HDMI21__AUDIO_DEBUG_INIT), 			0x0,		"All debug print initialize"},
	{E_TO_S(HDMI21__AUDIO_COUNT_INIT), 			0x0,		"All count value initialize"},
	{E_TO_S(HDMI21__AUDIO_CONTROL_INIT), 			0x0,		"All control value initialize"},
	{E_TO_S(HDMI21__AUDIO_INFORMATION_INIT), 		0x0,		"All information print initialize"},
	{E_TO_S(HDMI21__AUDIO_ALL_DEBUG_INIT), 		0x0,		"All audio debug initialize"}
};
/*----------------------------------------------------------------------------------------
	Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Variables
----------------------------------------------------------------------------------------*/
HDMI21_AUDIO_REG_DATA gHDMI21AudioRegData = {0, };
UINT64 gHDMI21AcrClockSave[HDMI21_NUM_OF_MAX_PORTS] ={0, 0, 0, 0};
BOOLEAN gHDMI21AudioAdnormal[HDMI21_NUM_OF_MAX_PORTS] ={FALSE, FALSE, FALSE, FALSE};
UINT32 gHDMI21AudioAdnormalCnt[HDMI21_NUM_OF_MAX_PORTS] ={0, 0, 0, 0};
UINT32 gHDMI21AudioFIFOAdnormalCnt[HDMI21_NUM_OF_MAX_PORTS] ={0, 0, 0, 0};
UINT32 gHDMI21AudioChannelAbnormalCnt[HDMI21_NUM_OF_MAX_PORTS] ={0, 0, 0, 0};
BOOLEAN gHDMI21AudioChannelAllocOverride[HDMI21_NUM_OF_MAX_PORTS] ={FALSE, FALSE, FALSE, FALSE};
UINT32 gHDMI21AudioIFChannel[HDMI21_NUM_OF_MAX_PORTS] ={0, 0, 0, 0};
UINT32 gHDMI21AudioChannelIncreaseCnt[HDMI21_NUM_OF_MAX_PORTS] ={0, 0, 0, 0};
BOOLEAN gHDMI21IsAudioChannelIncrease[HDMI21_NUM_OF_MAX_PORTS] ={FALSE, FALSE, FALSE, FALSE};
UINT32 gHDMI21AudioFIFOFill[HDMI21_NUM_OF_MAX_PORTS] ={0, 0, 0, 0};
UINT32 gHDMI21AudioFIFOAdjustPCnt[HDMI21_NUM_OF_MAX_PORTS] ={0, 0, 0, 0};
UINT32 gHDMI21AudioFIFOAdjustMCnt[HDMI21_NUM_OF_MAX_PORTS] ={0, 0, 0, 0};
UINT32 gHDMI21AudioPrintLimitCnt[HDMI21_NUM_OF_MAX_PORTS] ={0, 0, 0, 0};
UINT32 gHDMI21AudioIgnoreChannel[HDMI21_NUM_OF_MAX_PORTS] ={0, 0, 0, 0};


/*========================================================================================
	Implementation Group
========================================================================================*/

/* IOCTL */
int HDMI21_HAL_Rx_GetAudioInfo(UINT8 port, LX_HDMI_AUDIO_INFO_T *pHdmiAudioInfo, int size)
{
	int ret = RET_ERROR;
	UINT32 isForce = 0;
	LX_HDMI_AUDIO_INFO_T	data;
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	do{
		/* [Check]Basic */
		if(pHdmiAudioInfo == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}
		if(size != sizeof(LX_HDMI_AUDIO_INFO_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI_AUDIO_INFO_T), size);
			break;
		}
		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* [Get]Handler */
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];

		/* [Get]Audio Info */
		if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
			if((_p->video.dvi == FALSE) && ((_p->audio_change == TRUE) || (HDMI21_VPROC_Rx_Get_IsMute(_p)) \
				|| (_p->audioStandByCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_STANDBY_TIME].value)\
				|| (_p->audioFifoErrMuteCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ERR_MUTE_TIME].value)\
				|| (_p->audioStableCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME_O22].value))) {
				data.audioType	= LX_HDMI_AUDIO_NO_AUDIO;
			} else {
				data.audioType	= _p->audioInfo.audioType;
			}
		}else{
			if((_p->video.dvi == FALSE) && ((_p->audio_change == TRUE) || (HDMI21_VPROC_Rx_Get_IsMute(_p)) \
				|| (_p->audioStandByCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_STANDBY_TIME].value)\
				|| (_p->audioFifoErrMuteCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ERR_MUTE_TIME].value)\
				|| (_p->audioStableCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME].value))) {
				data.audioType	= LX_HDMI_AUDIO_NO_AUDIO;
			} else {
				data.audioType	= _p->audioInfo.audioType;
			}
		}
		data.samplingFreq =  _p->audioInfo.samplingFreq;
		data.countOfChannel = _p->audioInfo.countOfChannel;
		data.stream = _p->audioInfo.stream;

		/* [W/R] 202206028 spec out condition */
		if((_p->audioInfo.audioType == LX_HDMI_AUDIO_AC3) &&(_p->audioInfo.samplingFreq >= LX_HDMI_SAMPLING_FREQ_192_KHZ) && (_p->isHBRaudio == TRUE)){
			data.audioType	= LX_HDMI_AUDIO_NO_AUDIO;
			HDMI20_ADEF("HDMI[%d] Audio spec out condition ( AC3 + 192kHz )\n", _p->port);
		}

		/* [Debug]Force Info */
		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_TYPE].value != 0x0){
			data.audioType = gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_TYPE].value;
			isForce = 1;
		}
		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_FS].value != 0x0){
			data.samplingFreq = gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_FS].value;
			isForce = 2;
		}
		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_CHANNEL].value != 0x0){
			data.countOfChannel= gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_CHANNEL].value;
			isForce = 3;
		}
		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_STREAM].value != 0x0){
			data.stream= gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_STREAM].value;
			isForce = 4;
		}

		/* [Copy]To User */
		ret = copy_to_user((LX_HDMI_AUDIO_INFO_T *)pHdmiAudioInfo, &data, sizeof(LX_HDMI_AUDIO_INFO_T));
		if(ret) {
			HDMI20_ERROR("Error on attempting to copy to USER for Port[%d] Synopsys LINK.\n", port);
			break;
		}

		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_USR_INFO].value > 0){
			HDMI20_ADEF("HDMI[%d] Audio Type:%d, Fs:%d, Ch:%d, Stream:%d, Word length:%d, isForce:%d \n",\
			port, data.audioType, data.samplingFreq, data.countOfChannel, data.stream, data.wordLength, isForce);
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_USR_INFO].value--;

			if(data.audioType == LX_HDMI_AUDIO_NO_AUDIO){
				if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
					HDMI20_ADEF("HDMI[%d] Audio DVI:%d, AC:%d, V_Mute:%d, Standby:%d(%d), F_Err:%d(%d), stable:%d(%d), chmap:%d(%d) \n",\
					port, _p->video.dvi, _p->audio_change, (HDMI21_VPROC_Rx_Get_IsMute(_p)), _p->audioStandByCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_STANDBY_TIME].value,\
					_p->audioFifoErrMuteCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ERR_MUTE_TIME].value,\
					_p->audioStableCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME_O22].value,\
					_p->audioChMapStandByCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_CH_MAP_STANDBY_TIME].value);
				}else{
					HDMI20_ADEF("HDMI[%d] Audio DVI:%d, AC:%d, V_Mute:%d, Standby:%d(%d), F_Err:%d(%d), stable:%d(%d), chmap:%d(%d) \n",\
					port, _p->video.dvi, _p->audio_change, (HDMI21_VPROC_Rx_Get_IsMute(_p)), _p->audioStandByCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_STANDBY_TIME].value,\
					_p->audioFifoErrMuteCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ERR_MUTE_TIME].value,\
					_p->audioStableCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME].value,\
					_p->audioChMapStandByCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_CH_MAP_STANDBY_TIME].value);
				}
			}
		}

		ret = RET_OK;

	} while(0);

	return ret;

}

/* IOCTL */
int HDMI21_HAL_Rx_GetAudioCopyInfo(UINT8 port, LX_HDMI_AUDIO_COPY_T *pHdmiCopyInfo, int size)
{
	int ret = RET_ERROR;
	UINT32	reg_achst_byte0, reg_achst_byte1;
	UINT32	CpBit, LBit;
	LX_HDMI_AUDIO_COPY_T hdmiCopyInfo;
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	do{
		/* [Check]Basic  */
		if (port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
			break;
		}

		/* [Get]Handler */
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];

		/* [Get]Copy Info */
		if (_p->video.dvi){
			hdmiCopyInfo = LX_HDMI_AUDIO_COPY_FREE;
		}else{
			reg_achst_byte0 = gHDMI21AudioRegData.byte0;

			/* Set a CpBit */
			if (reg_achst_byte0 & HDMI21_AUDIO_CP_BIT_MASK)
				CpBit = 1;
			else
				CpBit = 0;
			reg_achst_byte1 = gHDMI21AudioRegData.byte1;

			/* Set a LBit */
			if (reg_achst_byte1 & HDMI21_AUDIO_L_BIT_MASK)
				LBit = 1;
			else
				LBit = 0;

			/* Set a Copyright Info. by CpBit and LBit */
			if ((CpBit == 0) && (LBit == 0))
				hdmiCopyInfo = LX_HDMI_AUDIO_COPY_ONCE;
			else if ((CpBit == 0) && (LBit == 1))
				hdmiCopyInfo = LX_HDMI_AUDIO_COPY_NO_MORE;	//same with LX_HDMI_AUDIO_COPY_NEVER
			else
				hdmiCopyInfo = LX_HDMI_AUDIO_COPY_FREE;
		}

		/* [Copy]To User */
		ret = copy_to_user((LX_HDMI_AUDIO_COPY_T *)pHdmiCopyInfo, &hdmiCopyInfo, sizeof(LX_HDMI_AUDIO_COPY_T));
		if(ret) {
			HDMI20_ERROR("Error on attempting to copy to USER for Port[%d] Synopsys LINK.\n", _p->port);
			break;
		}

		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 5){
			HDMI20_ADEF("HDMI[%d] Audio HDMI_GetAudioCopyInfo :CopyInfo = %d\n", _p->port, hdmiCopyInfo);
		}
	}while(0);
	return ret;
}

/* IOCTL */
int HDMI21_HAL_Rx_Set_HDMIARC(UINT8 port, BOOLEAN bOnOff)
{
	int ret = RET_OK;
	return ret;
}

/* IOCTL */
int HDMI21_HAL_Rx_Get_DebugAudioInfo(UINT8 port, LX_HDMI_DEBUG_AUDIO_INFO_T *pDebugAudioInfo, int size)
{
	int ret = RET_OK;
	do{

	} while(0);
	return ret;
}

int HDMI21_HAL_Rx_Set_AudioMute(UINT8 port, LX_HDMI_MUTE_CTRL_T *pMuteCtrl, int size)
{
	int ret = RET_OK;
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	BOOLEAN 	audioMuteState;
	LX_HDMI_MUTE_CTRL_T muteCtrl;

	do{
		/* [Check]Basic */
		if (port >= g_hdmi20_number_of_ports)		{
			HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
			return RET_ERROR;
		}

		/* [Get]Handler */
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];

		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG].value != 0) HDMI20_ADEF("HDMI[%d] Audio HDMI21_HAL_Rx_Set_AudioMute :mutecnt(%d)\n", _p->port, _p->audioStandByCnt);

		/* [Get]Current Mute State */
		//audioMuteState = !((_p->link_read(HDMI21_RX_PROC_CONFIG0) & HDMI21_RX_PROC_CONFIG0__I2S_ENABLE) >> 1);
		if((_p->link_read((UINT32)HDMI21_RX_PROC_CONFIG0) & (UINT32)HDMI21_RX_PROC_CONFIG0__I2S_ENABLE) == (UINT32)0){
			audioMuteState = TRUE;
		}else{
			audioMuteState = FALSE;
		}

		/* [Copy]From User */
		memset((void *)&muteCtrl, 0, sizeof(LX_HDMI_MUTE_CTRL_T));
		if( copy_from_user(&muteCtrl, (void __user *)pMuteCtrl, sizeof(LX_HDMI_MUTE_CTRL_T))){
			HDMI20_ERROR("Cannot copy HDMI21 audio mute ctrl structure from user\n");
			return RET_ERROR;
		}

		/* Mute Control */
		if ((muteCtrl.eMode == LX_HDMI_AUDIO_MUTE) || (muteCtrl.eMode == LX_HDMI_AV_MUTE)){
			// Check a current state
			if (muteCtrl.bAudioMute != audioMuteState){
				if (muteCtrl.bAudioMute == TRUE){
					// Mute audio data
					HDMI21_HAL_Rx_Set_AudioMuteControl(_p->port, HDMI21_AUDIO_MUTE);
					HDMI20_ADEF("HDMI[%d] Audio Mute enable !\n", _p->port);
					_p->isAudioMute = HDMI21_AUDIO_MUTE;
					_p->isAudioMuteControl = TRUE;
				}else{
					// Un-mute audio data
					if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
						if(((_p->audio_change == FALSE) && (_p->isMute == FALSE)\
							&& (_p->audioStandByCnt == gHDMI21RxDevAudioControler[HDMI21__AUDIO_STANDBY_TIME].value))\
							|| (_p->audioStableCnt == gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME_O22].value)) {
							HDMI21_HAL_Rx_Set_AudioMuteControl(port, HDMI21_AUDIO_UNMUTE);
							HDMI20_ADEF("HDMI[%d] Audio Mute disable!\n", port);
							_p->isAudioMute = HDMI21_AUDIO_UNMUTE;
						}
					}else{
						if(((_p->audio_change == FALSE) && (_p->isMute == FALSE)\
							&& (_p->audioStandByCnt == gHDMI21RxDevAudioControler[HDMI21__AUDIO_STANDBY_TIME].value))\
							|| (_p->audioStableCnt == gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME].value)) {
							HDMI21_HAL_Rx_Set_AudioMuteControl(port, HDMI21_AUDIO_UNMUTE);
							HDMI20_ADEF("HDMI[%d] Audio Mute disable!\n", port);
							_p->isAudioMute = HDMI21_AUDIO_UNMUTE;
						}
					}
					_p->isAudioMuteControl = FALSE;
				}

				//For debug print
				HDMI20_ADEF("HDMI[%d] Audio %s : port = %d, bAudioMute = %s b20250613 \n",	__L__, __F__, _p->port, (muteCtrl.bAudioMute ? "On" : "Off"));
			}

			//For debug print
			if (muteCtrl.bAudioMute == FALSE){
				HDMI20_ADEF("HDMI[%d] Audio SetMute[%d], type:%d, freq:%d, mute:%d\n", \
							__L__, _p->port, _p->audioInfo.audioType, _p->audioInfo.samplingFreq, audioMuteState);
			}
		}
	} while(0);

	return ret;

}

void HDMI21_HAL_Rx_Set_Audio_Configure(UINT8 port, HDMI21_HAL_PHY_INITIATED_MODE_T mode)
{
	UINT32 hbr_status = 0;
	//UINT32 proc_config0 = 0;
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	HDMI21_HAL_RX_AUDIO_DATA *_a;

	do{
		/* [Check]Basic */
		if (port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
			break;
		}

		/* [Get]Handler */
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];
		_a = (HDMI21_HAL_RX_AUDIO_DATA *)&gHDMI21RxAudioHandler[port];

		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_FUNC_CALL].value != 0)HDMI20_ADEF("HDMI(%d) Audio HDMI21_HAL_Rx_Set_Audio_Configure\n", _p->port);

		/* [Set]Register */
		_p->top_write(HDMI21_RX_ACR_CLK_DIVIDER, 	HDMI21_RX_ACR_CLK_DIVIDER__DIV1);
		_p->top_write(HDMI21_RX_ACR_CLK_N_FS,		HDMI21_RX_ACR_CLK_N_FS__128);
		_p->link_write(HDMI21_RX_PROC_CONFIG0,		(HDMI21_RX_PROC_CONFIG0__PAO_ENABLE |HDMI21_RX_PROC_CONFIG0__SPDIF_ENABLE ));
		//_p->link_write(HDMI21_RX_PDEC_ACR_CONFIG,	(HDMI21_RX_PDEC_ACR_OVERRIDE_DISABLE | HDMI21_RX_PDEC_ACR_DELTA_CTA_32));
		_p->link_write(HDMI21_RX_PDEC_ACR_CONFIG,	(HDMI21_RX_PDEC_ACR_OVERRIDE_DISABLE | HDMI21_RX_PDEC_ACR_DELTA_CTA_32));
		HDMI21_Rx_Audio_Path_SetMute(_p->port);

		/* [Check]6G */
		if(mode == HDMI21_HAL_PHY_INITIATED_6G){
			_p->top_write(HDMI21_RX_ACR_CLK_N_FS, HDMI21_RX_ACR_CLK_N_FS__256);
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG].value != 0) HDMI20_ADEF("HDMI[%d] signal is TMDS 6G\n", _p->port);
		}

		/* [Check]HBR */
		hbr_status = _p->link_read(HDMI21_RX_PROC_STATUS1) & HDMI21_RX_PROC_STATUS1__AUD_FMT_ST__MASK;
		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_HBR].value == 1) {
			_p->isHBRaudio = FALSE;
		}else if (gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_HBR].value == 2) {
			_p->isHBRaudio = TRUE;
		}else {
			if((hbr_status == HDMI21_RX_PROC_STATUS1__AUD_FMT_ST__HBR) && (_p->isHBRaudio == FALSE)) {
				_p->isHBRaudio = TRUE;
				if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG].value != 0) HDMI20_ADEF("HDMI[%d] Audio High Bit Rate Audio start(pdec_aud_sts=0x%x)!\n", _p->port, hbr_status);
			}else if ((hbr_status != HDMI21_RX_PROC_STATUS1__AUD_FMT_ST__HBR) && (_p->isHBRaudio == TRUE)) {
				_p->isHBRaudio = FALSE;
				if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG].value != 0) HDMI20_ADEF("HDMI[%d] Audio High Bit Rate Audio stop(pdec_aud_sts=0x%x)!\n", _p->port, hbr_status);
			}
		}

		_a->procConfig0_chSpread = HDMI21_RX__EXT__PROC_CONFIG0__AUD_CHAN_SPREAD_DISEN;
		_a->procConfig0_muteControl= HDMI21_RX__EXT__PROC_CONFIG0__MUTE;
		_a->procConfig0_chAlloc = HDMI21_RX__EXT__PROC_CONFIG0__SPK_ALLOC_OVR_DISEN;

		/* [Set]HBR */
		if(_p->isHBRaudio == TRUE){
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_DISABLE_SPREAD].value != 0){
				_p->link_write(HDMI21_RX_PROC_CONFIG2,		HDMI21_RX_PROC_CONFIG2__FMT_OFF);
				_p->top_write(HDMI21_RX_ACR_CLK_N_FS,			HDMI21_RX_ACR_CLK_N_FS__512);
				_a->procConfig0_chSpread = HDMI21_RX__EXT__PROC_CONFIG0__AUD_CHAN_SPREAD_DISEN;
				_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
			}else{
				_p->link_write(HDMI21_RX_PROC_CONFIG2,		HDMI21_RX_PROC_CONFIG2__FMT_OFF);
				_a->procConfig0_chSpread = HDMI21_RX__EXT__PROC_CONFIG0__AUD_CHAN_SPREAD_EN;
				_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
			}
		}

		/* [Set]Irq Enable */
		HDMI21_Rx_Audio_Path_SetInthw(_p->port);

		_p->top_write(HDMI21_RX_ACR_PLL_MODE, 0x10001 );
		HDMI21_HAL_Rx_Get_AudioACRParam(_p->port, TRUE);
		HDMI21_HAL_Rx_Get_AudioACRParam(_p->port, FALSE);
		_p->top_write(HDMI21_RX_ACR_PLL_MODE, 0x1 );
		if(((lx_chip_rev( ) >= LX_CHIP_REV( E60, B0)) && (lx_chip_rev( ) < LX_CHIP_REV( O22, A0)))\
		&& (((_p->scdcTmdsMode >= HDMI21_HAL_PHY_INITIATED_FRL_8G_4L) && ((_p->port == 3) || (_p->port == 4)))\
		|| ((_p->scdcTmdsMode >= HDMI21_HAL_PHY_INITIATED_FRL_10G_4L) && (_p->port == 2) ))) {
			_p->top_write(HDMI21_RX_ACR_PLL_MODE, 0x10001 );
		}

		/* [Set] FIFO Rgister */
		//_p->link_write(HDMI21_RX_AUD_FIFO_TH_PASS,	HDMI21_RX_AUD_FIFO_TH_PASS__VALUE);
		_p->link_write(HDMI21_RX_AUD_FIFO_TH,		(HDMI21_RX_AUD_FIFO_TH_LOW | HDMI21_RX_AUD_FIFO_TH_HIGH));
		_p->link_write(HDMI21_RX_AUD_FIFO_MUTE_TH,	(HDMI21_RX_AUD_FIFO_MUTE_TH_LOW | HDMI21_RX_AUD_FIFO_MUTE_TH_HIGH));
		_p->link_write(HDMI21_RX_AUD_FIFO_CONFIG,	HDMI21_RX_AUD_FIFO_CONFIG__FILL_RESTART_OFF);
		_p->link_write(HDMI21_RX_AUD_FIFO_CONTROL,	(HDMI21_RX_AUD_FIFO_CONTROL__FIFO_INIT | HDMI21_RX_AUD_FIFO_CONTROL__CLR_MIN | HDMI21_RX_AUD_FIFO_CONTROL__CLR_MAX));

		/* [Init]Count */
		_p->audioChMapCnt = 0;
		_p->audioStableCnt = 0;
		_p->audioChMapStandByCnt = 0;
		_p->audioHBRAdnormalCnt = 0;
		_p->audioTypeAdnormalCnt = 0;
		_p->audioAcrResetCnt = 0;
		_p->audioAcrErrorCnt = 0;
		_p->audioUnknowTypeMuteCnt = 0;
		_p->audioHBRAdnormalCnt = 0;
		_p->isAudioMute = HDMI21_AUDIO_MUTE;

		/* [Init]Info */
		_p->audioInfo.audioType = LX_HDMI_AUDIO_DEFAULT;
		_p->audioInfo.pao_byte0 = 0;
		_p->audioInfo.pao_pc = 0;
		_p->audioInfo.samplingFreq = LX_HDMI_SAMPLING_FREQ_NONE;
		_p->audioInfo.countOfChannel = 9;
		_p->audioInfo.stream = LX_HDMI_AUDIO_STREAM_NONE;

		gHDMI21AcrClockSave[_p->port] = 0;
		gHDMI21AudioAdnormal[_p->port] = FALSE;
		gHDMI21AudioAdnormalCnt[_p->port] = 0;
		gHDMI21AudioFIFOAdnormalCnt[_p->port] = 0;
		gHDMI21AudioChannelAbnormalCnt[_p->port] = 0;
		gHDMI21AudioChannelAllocOverride[_p->port] = FALSE;
		gHDMI21AudioIFChannel[_p->port] = 0;
		gHDMI21IsAudioChannelIncrease[_p->port] = FALSE;
		gHDMI21AudioChannelIncreaseCnt[_p->port] = 0;
		gHDMI21AudioFIFOFill[_p->port] = 0;
		gHDMI21AudioFIFOAdjustPCnt[_p->port] = 0;
		gHDMI21AudioFIFOAdjustMCnt[_p->port] = 0;
		gHDMI21AudioIgnoreChannel[_p->port] = 0;
		//gHDMI21AudioPrintLimitCnt[_p->port] = 0;

		//gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_CHANNEL].value = 0;

		/* [Get]Info */
		if(_p->isAudioRegReady == 0){
			HDMI21_Rx_Audio_Path_SetInthw(_p->port);
		}

#if 0
		/* [Get]Audio Info */
		HDMI21_HAL_Rx_Get_AudioType(_p->port, &data.audioType);
		HDMI21_HAL_Rx_Get_AudioFreqFromTMDSClock(_p->port, &data.samplingFreq);
		HDMI21_HAL_Rx_Get_AudioStream(_p->port, &data.stream);
		if(data.audioType == LX_HDMI_AUDIO_PCM && (_p->video.dvi == 0)) {
			HDMI21_HAL_Rx_Get_AudioCountOfChannel(_p->port, &data.countOfChannel);
			_p->audioInfo.countOfChannel = data.countOfChannel;
		}else{
			proc_config0 = _p->link_read(HDMI21_RX_PROC_CONFIG0);
			_p->link_write(HDMI21_RX_PROC_CONFIG0, proc_config0 & HDMI21_RX_PROC_CONFIG0__SPK_ALLOC_OVR_DISEN);
			_p->audioInfo.countOfChannel = 9;
		}

		_p->audioInfo.audioType = data.audioType;
		_p->audioInfo.samplingFreq = data.samplingFreq;
		_p->audioInfo.stream = data.stream;
#endif
	}while(0);
}

UINT32 HDMI21_HAL_Rx_Get_PLLFreqRange(UINT32 tmds_clk)
{
	if((tmds_clk >= 0)&&(tmds_clk <= 25000)){
		return 0;
	}
	else if((tmds_clk > 25000)&&(tmds_clk <= 40000)){
		return 0;
	}
	else if((tmds_clk > 40000)&&(tmds_clk <= 80000)){
		return 1;
	}
	else if((tmds_clk > 80000)&&(tmds_clk <= 160000)){
		return 2;
	}
	else if((tmds_clk > 160000)&&(tmds_clk <= 340000)){
		return 3;
	}else if((tmds_clk > 340000)){
		return 3; // 2014/07/08 temperary
	}
	else return 0;

}


void HDMI21_HAL_Rx_Get_AudioACRParam(UINT8 port, BOOLEAN clear)
{
	UINT32 n, n0, n1, n2, nn;
	UINT32 cts, cts0, cts1, cts2;
	UINT32 mn, mn0, mn1, mn2;
	UINT32 mcts, mcts0, mcts1, mcts2;
	UINT32 fill_status, cts_update;
	UINT32 acr_mode;
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	HDMI21_HAL_PHY_INITIATED_MODE_T scdcmode;

	do{
		/* [Check]Basic */
		if (port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
			break;
		}

		/* [Get]Handler */
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];

		/* [Get]ACR N/CTS */ // Spec : N[20]=SB6~SB4, CTS[20]=SB3~SB1(HDMI1.4 spec p.101)
		n0 = ((UINT32)(_p->dataPacket[HDMI21_DISLAND_DATA__ACR][9])) & HDMI21_AUDIO_ACR_8BIT_MASK; // SB6
		n1 = ((UINT32)(_p->dataPacket[HDMI21_DISLAND_DATA__ACR][8])) & HDMI21_AUDIO_ACR_8BIT_MASK; // SB5
		n2 = ((UINT32)(_p->dataPacket[HDMI21_DISLAND_DATA__ACR][7])) & HDMI21_AUDIO_ACR_8BIT_MASK; // SB4
		n = (n0 | (n1<<8) | ((n2 & HDMI21_AUDIO_ACR_4BIT_MASK)<<16));

		cts0 = ((UINT32)(_p->dataPacket[HDMI21_DISLAND_DATA__ACR][6])) & HDMI21_AUDIO_ACR_8BIT_MASK; // SB3
		cts1 = ((UINT32)(_p->dataPacket[HDMI21_DISLAND_DATA__ACR][5])) & HDMI21_AUDIO_ACR_8BIT_MASK; // SB2
		cts2 = ((UINT32)(_p->dataPacket[HDMI21_DISLAND_DATA__ACR][4])) & HDMI21_AUDIO_ACR_8BIT_MASK; // SB1
		cts = (cts0 | (cts1<<8) | ((cts2 & HDMI21_AUDIO_ACR_4BIT_MASK)<<16));

		/* [Check] N/CTS Adnormal */
		mn0 = (_p->link_read(HDMI21_RX_PDEC_ACR_PB_N)) & 0x000000FF; // SB6
		mn1 = (_p->link_read(HDMI21_RX_PDEC_ACR_PB_N)) & 0x0000FF00; // SB5
		mn2 = (_p->link_read(HDMI21_RX_PDEC_ACR_PB_N)) & 0x00FF0000; // SB4
		//mn = ((mn0)<<16) | (mn1) | ((mn2)>>16);
		mn = ((mn0)<<8) | ((mn1)>>8);

		mcts0 = (_p->link_read(HDMI21_RX_PDEC_ACR_PB_CTS)) & 0x000000FF; // SB3
		mcts1 = (_p->link_read(HDMI21_RX_PDEC_ACR_PB_CTS)) & 0x0000FF00; // SB2
		mcts2 = (_p->link_read(HDMI21_RX_PDEC_ACR_PB_CTS)) & 0x00FF0000; // SB1
		mcts = ((mcts0)<<16) | (mcts1) | ((mcts2)>>16);

		if((n == 0) && (n != mn)){
			HDMI20_AUDIO("HDMI[%d] Audio FIFO : ACR N value is Adnormal(n=0x%x, mn=0x%x) \n", port, n, mn);
			n = mn;
		}
		if((cts == 0) && (cts != mcts)){
			HDMI20_AUDIO("HDMI[%d] Audio FIFO : ACR CTS value is Adnormal(cts=0x%x, mcts=0x%x) \n", port, cts, mcts);
			cts = mcts;
		}

		//HDMI20_AUDIO("HDMI[%d] Audio FIFO : ACR CTS value is Adnormal(n=0x%x, mn=0x%x)(cts=0x%x, mcts=0x%x) \n", port, n, mn, cts, mcts);

		_p->audioInfo.acr_n= n;
		_p->audioInfo.acr_cts= cts;
#if 0
		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_N_CTS].value > 0){
			if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG].value != 0) HDMI20_ADEF("HDMI[%d] Audio ACR : N[0x%08x]0x%08x]0x%08x], CTS:[0x%08x]0x%08x]0x%08x]\n", _p->port, n0, n1, n2, cts0, cts1, cts2);
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_N_CTS].value--;

			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG].value != 0) HDMI20_ADEF("ACR3 [0x%08x]\n", (UINT32)(_p->dataPacket[HDMI21_DISLAND_DATA__ACR][3]));
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG].value != 0) HDMI20_ADEF("ACR4 [0x%08x]\n", (UINT32)(_p->dataPacket[HDMI21_DISLAND_DATA__ACR][4]));
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG].value != 0) HDMI20_ADEF("ACR5 [0x%08x]\n", (UINT32)(_p->dataPacket[HDMI21_DISLAND_DATA__ACR][5]));
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG].value != 0) HDMI20_ADEF("ACR6 [0x%08x]\n", (UINT32)(_p->dataPacket[HDMI21_DISLAND_DATA__ACR][6]));
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG].value != 0) HDMI20_ADEF("ACR7 [0x%08x]\n", (UINT32)(_p->dataPacket[HDMI21_DISLAND_DATA__ACR][7]));
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG].value != 0) HDMI20_ADEF("ACR8 [0x%08x]\n", (UINT32)(_p->dataPacket[HDMI21_DISLAND_DATA__ACR][8]));
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG].value != 0) HDMI20_ADEF("ACR9 [0x%08x]\n", (UINT32)(_p->dataPacket[HDMI21_DISLAND_DATA__ACR][9]));
		}
#endif

		fill_status = _p->link_read(HDMI21_RX_AUD_FIFO_STS2__FILLSTS1) & 0xFFFF;
		acr_mode = _p->top_read(HDMI21_RX_ACR_PLL_MODE);
		if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ADJUST].value != 0 \
				&& (_p->audioStandByCnt == gHDMI21RxDevAudioControler[HDMI21__AUDIO_STANDBY_TIME].value)\
				&& (_p->audioStableCnt == gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME_O22].value)\
				&& (_p->audioInfo.audioType > LX_HDMI_AUDIO_NO_AUDIO) && (_p->isPC == FALSE)\
				&& (acr_mode == 0x10001)){
				if(fill_status > HDMI21_RX_AUD_FIFO_ADJUST_HIGH){
					if(gHDMI21AudioFIFOAdjustMCnt[_p->port] < gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ADJUST_MAX_CNT].value){
						gHDMI21AudioFIFOAdjustMCnt[_p->port]++;
					}
					if(_p->audioInfo.acr_cts >= (gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ADJUST].value * gHDMI21AudioFIFOAdjustMCnt[_p->port])){
						cts_update = _p->audioInfo.acr_cts - (gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ADJUST].value * gHDMI21AudioFIFOAdjustMCnt[_p->port]);
					}
					if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG].value != 0) HDMI20_ADEF("HDMI[%d] Audio FIFO : Recovery overflow(0x%04x), CTS(0x%08x -> 0x%08x) \n", port, fill_status, _p->audioInfo.acr_cts, cts_update);
					_p->audioInfo.acr_cts = cts_update;
				}else if(fill_status < HDMI21_RX_AUD_FIFO_ADJUST_LOW){
					if(gHDMI21AudioFIFOAdjustPCnt[_p->port] < gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ADJUST_MAX_CNT].value){
						gHDMI21AudioFIFOAdjustPCnt[_p->port]++;
					}
					if(_p->audioInfo.acr_cts <= 0xFF0000){
						cts_update = _p->audioInfo.acr_cts + (gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ADJUST].value * gHDMI21AudioFIFOAdjustPCnt[_p->port]);
					}
					if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG].value != 0) HDMI20_ADEF("HDMI[%d] Audio FIFO : Recovery underflow(0x%04x), CTS(0x%08x -> 0x%08x) \n", port, fill_status, _p->audioInfo.acr_cts, cts_update);
					_p->audioInfo.acr_cts = cts_update;
				}else{
					if(gHDMI21AudioFIFOAdjustMCnt[_p->port] > 0){
						gHDMI21AudioFIFOAdjustMCnt[_p->port]--;
						if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value != 0)HDMI20_ADEF("HDMI[%d] Audio FIFO adjust Cnt : %d", port, gHDMI21AudioFIFOAdjustMCnt[_p->port]);
						if(_p->audioInfo.acr_cts >= (gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ADJUST].value * gHDMI21AudioFIFOAdjustMCnt[_p->port])) {
							cts_update = _p->audioInfo.acr_cts - (gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ADJUST].value * gHDMI21AudioFIFOAdjustMCnt[_p->port]);
						}
						_p->audioInfo.acr_cts = cts_update;
					}
					if(gHDMI21AudioFIFOAdjustPCnt[_p->port] > 0){
						gHDMI21AudioFIFOAdjustPCnt[_p->port]--;
						if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value != 0)HDMI20_ADEF("HDMI[%d] Audio FIFO adjust Cnt : %d", port, gHDMI21AudioFIFOAdjustPCnt[_p->port]);
						if(_p->audioInfo.acr_cts <= 0xFF0000){
							cts_update = _p->audioInfo.acr_cts + (gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ADJUST].value * gHDMI21AudioFIFOAdjustPCnt[_p->port]);
						}
						_p->audioInfo.acr_cts = cts_update;
					}
				}
			}
		}else{
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ADJUST].value != 0 \
				&& (_p->audioStandByCnt == gHDMI21RxDevAudioControler[HDMI21__AUDIO_STANDBY_TIME].value)\
				&& (_p->audioStableCnt == gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME].value)\
				&& (_p->audioInfo.audioType > LX_HDMI_AUDIO_NO_AUDIO) && (_p->isPC == FALSE)\
				&& (acr_mode == 0x10001)){
				if(fill_status > HDMI21_RX_AUD_FIFO_ADJUST_HIGH){
					if(gHDMI21AudioFIFOAdjustMCnt[_p->port] < gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ADJUST_MAX_CNT].value){
						gHDMI21AudioFIFOAdjustMCnt[_p->port]++;
					}
					if(_p->audioInfo.acr_cts >= (gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ADJUST].value * gHDMI21AudioFIFOAdjustMCnt[_p->port])){
						cts_update = _p->audioInfo.acr_cts - (gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ADJUST].value * gHDMI21AudioFIFOAdjustMCnt[_p->port]);
					}
					if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG].value != 0) HDMI20_ADEF("HDMI[%d] Audio FIFO : Recovery overflow(0x%04x), CTS(0x%08x -> 0x%08x) \n", port, fill_status, _p->audioInfo.acr_cts, cts_update);
					_p->audioInfo.acr_cts = cts_update;
				}else if(fill_status < HDMI21_RX_AUD_FIFO_ADJUST_LOW){
					if(gHDMI21AudioFIFOAdjustPCnt[_p->port] < gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ADJUST_MAX_CNT].value){
						gHDMI21AudioFIFOAdjustPCnt[_p->port]++;
					}
					if(_p->audioInfo.acr_cts <= 0xFF0000){
						cts_update = _p->audioInfo.acr_cts + (gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ADJUST].value * gHDMI21AudioFIFOAdjustPCnt[_p->port]);
					}
					if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG].value != 0) HDMI20_ADEF("HDMI[%d] Audio FIFO : Recovery underflow(0x%04x), CTS(0x%08x -> 0x%08x) \n", port, fill_status, _p->audioInfo.acr_cts, cts_update);
					_p->audioInfo.acr_cts = cts_update;
				}else{
					if(gHDMI21AudioFIFOAdjustMCnt[_p->port] > 0){
						gHDMI21AudioFIFOAdjustMCnt[_p->port]--;
						if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value != 0)HDMI20_ADEF("HDMI[%d] Audio FIFO adjust Cnt : %d", port, gHDMI21AudioFIFOAdjustMCnt[_p->port]);
						if(_p->audioInfo.acr_cts >= (gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ADJUST].value * gHDMI21AudioFIFOAdjustMCnt[_p->port])) {
							cts_update = _p->audioInfo.acr_cts - (gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ADJUST].value * gHDMI21AudioFIFOAdjustMCnt[_p->port]);
						}
						_p->audioInfo.acr_cts = cts_update;
					}
					if(gHDMI21AudioFIFOAdjustPCnt[_p->port] > 0){
						gHDMI21AudioFIFOAdjustPCnt[_p->port]--;
						if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value != 0)HDMI20_ADEF("HDMI[%d] Audio FIFO adjust Cnt : %d", port, gHDMI21AudioFIFOAdjustPCnt[_p->port]);
						if(_p->audioInfo.acr_cts <= 0xFF0000){
							cts_update = _p->audioInfo.acr_cts + (gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ADJUST].value * gHDMI21AudioFIFOAdjustPCnt[_p->port]);
						}
						_p->audioInfo.acr_cts = cts_update;
					}
				}
			}
		}

		/* [Set]Force N/CTS */
		if(clear){
			_p->audioInfo.acr_n= 0;
			_p->audioInfo.acr_cts= 0;
		}

		/* [Get]SCDC Mode */
		scdcmode = _p->scdcTmdsMode;
		nn = _p->audioInfo.acr_n * 2;

		/* [Get]ACR N/CTS */
		_p->link_write(HDMI21_RX_PDEC_ACR_CTS_CONFIG, cts);
		_p->link_write(HDMI21_RX_PDEC_ACR_N_CONFIG, n);
		_p->top_write( HDMI21_RX_ACR_CTS, _p->audioInfo.acr_cts);

		if(((lx_chip_rev( ) >= LX_CHIP_REV( E60, B0)) && (lx_chip_rev( ) < LX_CHIP_REV( O22, A0))) \
		&& (((_p->scdcTmdsMode >= HDMI21_HAL_PHY_INITIATED_FRL_8G_4L) && ((_p->port == 3) || (_p->port == 4)))\
		|| ((_p->scdcTmdsMode >= HDMI21_HAL_PHY_INITIATED_FRL_10G_4L) && (_p->port == 2) ))) {
			_p->top_write( HDMI21_RX_ACR_N, nn );
			//_p->top_write( 0x44, 0x61 );
			_p->top_write( 0x2c, 0x110011 );
			_p->top_write( 0x2c, 0x110111 );
			_p->top_write( 0x2c, 0x110011 );
		}else{
			//_p->phyPDC_write(0x12C, 0x0);
			_p->top_write( HDMI21_RX_ACR_N, _p->audioInfo.acr_n );
		}


	}while(0);
}

int HDMI21_HAL_Rx_Get_AudioWordLength(UINT8 port, LX_HDMI_AUDIO_WORD_LENGTH_T *wordLength){
	int ret = RET_ERROR;
	UINT32	reg_achst_byte4;
	UINT32	reg_achst_byte4_bit32 = 0;
	UINT32	reg_achst_byte4_bit353433 = 0;
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	do{
		/* [Check]Basic */
		if (port >= g_hdmi20_number_of_ports)	{
			HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
			break;
		}

		/* [Get]Handler */
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];
		
		/* [Get]Word Length Info From Audio */
		HDMI21_Rx_Audio_Path_GetSPDIFInfo(_p->port, &gHDMI21AudioRegData);
		reg_achst_byte4 = gHDMI21AudioRegData.byte1;
		reg_achst_byte4_bit32 = reg_achst_byte4 & (0x1);
		reg_achst_byte4_bit353433 = reg_achst_byte4 & (0xE);
		reg_achst_byte4_bit353433 = reg_achst_byte4_bit353433 >> 1;

		if(reg_achst_byte4_bit32 == 0x1){
			if(reg_achst_byte4_bit353433 == 0x1){
				*wordLength = 20;
			}else if(reg_achst_byte4_bit353433 == 0x2){
				*wordLength = 22;
			}else if(reg_achst_byte4_bit353433 == 0x4){
				*wordLength = 23;
			}else if(reg_achst_byte4_bit353433 == 0x5){
				*wordLength = 24;
			}else if(reg_achst_byte4_bit353433 == 0x6){
				*wordLength = 21;
			}else{
				*wordLength = 0;
			}
		}else{ // reg_achst_byte4_bit32 == 0x0
			if(reg_achst_byte4_bit353433 == 0x1){
				*wordLength = 16;
			}else if(reg_achst_byte4_bit353433 == 0x2){
				*wordLength = 18;
			}else if(reg_achst_byte4_bit353433 == 0x4){
				*wordLength = 19;
			}else if(reg_achst_byte4_bit353433 == 0x5){
				*wordLength = 20;
			}else if(reg_achst_byte4_bit353433 == 0x6){
				*wordLength = 17;
			}else{
				*wordLength = 0;
			}
		}		

		if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 0x21) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 0x22)){
			HDMI20_ADEF("HDMI[%d] Audio Word length : 0x%x\n", _p->port, reg_achst_byte4);
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 0x21) gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value = 0;
		}

		ret = RET_OK;
	}while(0);

	return ret;
}



int HDMI21_HAL_Rx_Get_AudioType(UINT8 port, LX_HDMI_AUDIO_TYPE_T *audioType)
{
	int ret = RET_OK;
	UINT32	reg_achst_byte0;
	UINT32	reg_burst_pc_0;
	UINT32	reg_pao_byte0;
	UINT32	reg_pao_pc_0;
	UINT32	proc_status1;
	BOOLEAN isSamplePresent = false;
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	do{
		/* [Check]Basic */
		if (port >= g_hdmi20_number_of_ports)	{
			HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
			return RET_ERROR;
		}

		/* [Get]Handler */
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];

		/* [Get] Sample present exist */
		proc_status1 = _p->link_read(HDMI21_RX_PROC_STATUS1);
		if(proc_status1 & HDMI21_RX_PROC_STATUS1__SAMPLE_PRESENT_MASK)isSamplePresent=TRUE;

		/* [Get]Type Info From Audio */
		HDMI21_Rx_Audio_Path_GetSPDIFInfo(_p->port, &gHDMI21AudioRegData);
		reg_achst_byte0 = gHDMI21AudioRegData.byte0;
		reg_burst_pc_0  = gHDMI21AudioRegData.pcpd;

		reg_pao_byte0 = _p->top_read(HDMI21_RX_AD_MAIN_AUD_INFO_BYTE0);
		reg_pao_pc_0  = _p->top_read(HDMI21_RX_AD_MAIN_AUD_INFO_PC);

		/* [Check]HBR */
		if(_p->isHBRaudio == TRUE){
			reg_achst_byte0 = reg_pao_byte0;
			reg_burst_pc_0  = reg_pao_pc_0;
		}
#if 0
		/* [SW W/R]O22 audio bus error */
		if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
			reg_achst_byte0 = reg_pao_byte0;
			reg_burst_pc_0  = reg_pao_pc_0;
		}
#endif
		/* Update PAO Var */
		gHDMI21RxHandler[_p->port].audioInfo.pao_byte0= reg_pao_byte0;
		gHDMI21RxHandler[_p->port].audioInfo.pao_pc = reg_pao_pc_0;

		if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
			HDMI20_ADEF("HDMI[%d] Audio byte0[aud:%x, link:%x], pc[aud:%x, link:%x], dvi[%d] HBR[%d] \n",\
			port, reg_achst_byte0, _p->top_read(HDMI21_RX_AD_MAIN_AUD_INFO_BYTE0),\
			reg_burst_pc_0, _p->top_read(HDMI21_RX_AD_MAIN_AUD_INFO_PC),_p->video.dvi, _p->isHBRaudio);
		}

		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_UNKNOWN_TYPE].value != 0){
			reg_achst_byte0 = 0;
		}

		/* [Set]Type Info */
		//Check HDMI /DVI Mode, 1 : DVI, 0 : HDMI
		if (_p->video.dvi == FALSE)	{
			//Check if audio sample word used for other purposes than liner PCM.
			if (reg_achst_byte0 & HDMI21_AUDIO_SAMPLE_NON_PCM_MASK){ //bit 1, 0 : PCM, 1 : non-PCM
				//Check a vaild Pc data for payload
				if ((reg_burst_pc_0 & HDMI21_BURST_INFO_PAYLOAD_ERROR_BIT_MASK) == 0){ //bit 7, 0 : No Error, 1 : Error
					//Set Audio Data-Types according to IEC61937-2 Burst Info Preamble C
					switch(reg_burst_pc_0 & HDMI21_BURST_INFO_AUDIO_TYPEBIT_MASK){ //bit 4 ~ 0
						case HDMI20_BURST_AUDIO_INFO_TYPE_AC3:
						case HDMI20_BURST_AUDIO_INFO_TYPE_PAUSE:
							*audioType = LX_HDMI_AUDIO_AC3;
							if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
								HDMI20_ADEF("HDMI[%d] Audio Type = AC3,  ", _p->port);
							}
							break;

						case HDMI20_BURST_AUDIO_INFO_TYPE_AC3_ENHANCED:
							*audioType = LX_HDMI_AUDIO_EAC3;
							if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
								HDMI20_ADEF("HDMI[%d] Audio Type = AC3_ENHANCED,  ", _p->port);
							}
							break;

						case HDMI20_BURST_AUDIO_INFO_TYPE_MAT:
							*audioType = LX_HDMI_AUDIO_MAT;
							if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
								HDMI20_ADEF("HDMI[%d] Audio Type = MAT,  ", _p->port);
							}
							break;

						case HDMI20_BURST_AUDIO_INFO_TYPE_DTS_I:
						case HDMI20_BURST_AUDIO_INFO_TYPE_DTS_II:
						case HDMI20_BURST_AUDIO_INFO_TYPE_DTS_III:
							*audioType = LX_HDMI_AUDIO_DTS;
							if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
								HDMI20_ADEF("HDMI[%d] Audio Type = DTS,  ", _p->port);
							}
							break;

						case HDMI20_BURST_AUDIO_INFO_TYPE_DTS_IV:
							if((_p->isHBRaudio == false) && (reg_burst_pc_0 == 0x0411 || reg_burst_pc_0 == 0x0a11)){
								*audioType = LX_HDMI_AUDIO_DTS;
								if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
									HDMI20_ADEF("HDMI[%d] Audio Type = DTS,  ", _p->port);
								}
							}else if((reg_burst_pc_0 == 0x0311) || (reg_burst_pc_0 == 0x0211)){
								*audioType = LX_HDMI_AUDIO_DTS_HD_HRA;
								if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
									HDMI20_ADEF("HDMI[%d] Audio Type = DTS_HD_HRA,  ", _p->port);
								}
							}else{
								*audioType = LX_HDMI_AUDIO_DTS_HD;
								if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
								HDMI20_ADEF("HDMI[%d] Audio Type = DTS_HD,  ", _p->port);
								}
							}
							break;

						case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_AAC:
						case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_AAC_LOW:
						case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG4_AAC:
						case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG4_AAC_LOAS:
							*audioType = LX_HDMI_AUDIO_AAC;
							if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
								HDMI20_ADEF("HDMI[%d] Audio Type = AAC,  ", _p->port);
							}
							break;

						case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG1_L1:
						case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG1_L23:
						case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_EXT:
						case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_L1:
						case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_L2:
						case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_L3:
							*audioType = LX_HDMI_AUDIO_MPEG;
							if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
								HDMI20_ADEF("HDMI[%d] Audio Type = MPEG,  ", _p->port);
							}
							break;

						case HDMI20_BURST_AUDIO_INFO_TYPE_NULL:
							if(_p->audioInfo.audioType == LX_HDMI_AUDIO_PCM) {
								*audioType = LX_HDMI_AUDIO_NO_AUDIO;
							}else {
								*audioType = _p->audioInfo.audioType;
							}
							if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
								HDMI20_ADEF("HDMI[%d] Audio Type = NON-PCM NULL(%x),  ", _p->port, _p->audioInfo.audioType);
							}
							break;

						default:
							*audioType = LX_HDMI_AUDIO_NO_AUDIO;
							if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
								HDMI20_ADEF("HDMI[%d] Audio Type = NON-PCM,  ", _p->port);
							}
							break;
					}
					_p->audioTypeAdnormalCnt = 0;
				}	//if ((reg_burst_pc_0 & HDMI21_BURST_INFO_PAYLOAD_ERROR_BIT_MASK) == 0)
				else{
					*audioType = LX_HDMI_AUDIO_PCM;
					if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
						HDMI20_ADEF("HDMI[%d] Audio Type = NON-PCM error,  ", _p->port);
					}
				}
			}	//if (reg_achst_byte0 & HDMI21_AUDIO_SAMPLE_NON_PCM_MASK)
			else{
				//Check a vaild Pc data for payload
				if (((reg_burst_pc_0 & HDMI21_BURST_INFO_PAYLOAD_ERROR_BIT_MASK) == 0) || ((reg_pao_pc_0 & HDMI21_BURST_INFO_PAYLOAD_ERROR_BIT_MASK) == 0)){ //bit 7, 0 : No Error, 1 : Error
					//Set Audio Data-Types according to IEC61937-2 Burst Info Preamble C
					switch(reg_burst_pc_0 & HDMI21_BURST_INFO_AUDIO_TYPEBIT_MASK){ //bit 4 ~ 0
						case HDMI20_BURST_AUDIO_INFO_TYPE_AC3:
						case HDMI20_BURST_AUDIO_INFO_TYPE_PAUSE:
							if(reg_pao_pc_0){
								*audioType = LX_HDMI_AUDIO_UNKNOWN_AC3;
							}else{
								*audioType = LX_HDMI_AUDIO_PCM;
							}
							if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
								HDMI20_ADEF("HDMI[%d] Audio Type = Unknown AC3,  ", port);
							}
							break;

						case HDMI20_BURST_AUDIO_INFO_TYPE_AC3_ENHANCED:
							if(reg_pao_pc_0){
								*audioType = LX_HDMI_AUDIO_UNKNOWN_EAC3;
							}else{
								*audioType = LX_HDMI_AUDIO_PCM;
							}
							if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
								HDMI20_ADEF("HDMI[%d] Audio Type = Unknown AC3_ENHANCED,  ", port);
							}
							break;

						case HDMI20_BURST_AUDIO_INFO_TYPE_MAT:
							if(reg_pao_pc_0){
								*audioType = LX_HDMI_AUDIO_UNKNOWN_MAT;
							}else{
								*audioType = LX_HDMI_AUDIO_PCM;
							}
							if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
								HDMI20_ADEF("HDMI[%d] Audio Type = Unknown MAT,  ", port);
							}
							break;

						case HDMI20_BURST_AUDIO_INFO_TYPE_DTS_I:
						case HDMI20_BURST_AUDIO_INFO_TYPE_DTS_II:
						case HDMI20_BURST_AUDIO_INFO_TYPE_DTS_III:
							if(reg_pao_pc_0){
								*audioType = LX_HDMI_AUDIO_UNKNOWN_DTS;
							}else{
								*audioType = LX_HDMI_AUDIO_PCM;
							}
							if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
								HDMI20_ADEF("HDMI[%d] Audio Type = Unknown DTS,  ", port);
							}
							break;

						case HDMI20_BURST_AUDIO_INFO_TYPE_DTS_IV:
							if((_p->isHBRaudio == false) && (reg_burst_pc_0 == 0x0411 || reg_burst_pc_0 == 0x0a11)){
								if(reg_pao_pc_0){
									*audioType = LX_HDMI_AUDIO_UNKNOWN_DTS;
								}else{
									*audioType = LX_HDMI_AUDIO_PCM;
								}
								if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
									HDMI20_ADEF("HDMI[%d] Audio Type = Unknown DTS,  ", port);
								}
							}else if((reg_burst_pc_0 == 0x0311) || (reg_burst_pc_0 == 0x0211)){
								if(reg_pao_pc_0){
									*audioType = LX_HDMI_AUDIO_UNKNOWN_DTS_HD_HRA;
								}else{
									*audioType = LX_HDMI_AUDIO_PCM;
								}
								if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
									HDMI20_ADEF("HDMI[%d] Audio Type = Unknown DTS_HD_HRA,  ", port);
								}
							}else{
								if(reg_pao_pc_0){
									*audioType = LX_HDMI_AUDIO_UNKNOWN_DTS_HD;
								}else{
									*audioType = LX_HDMI_AUDIO_PCM;
								}
								if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
								HDMI20_ADEF("HDMI[%d] Audio Type = Unknown DTS_HD,  ", port);
								}
							}
							break;

						case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_AAC:
						case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_AAC_LOW:
						case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG4_AAC:
						case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG4_AAC_LOAS:
							if(reg_pao_pc_0){
								*audioType = LX_HDMI_AUDIO_UNKNOWN_AAC;
							}else{
								*audioType = LX_HDMI_AUDIO_PCM;
							}
							if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
								HDMI20_ADEF("HDMI[%d] Audio Type = Unknown AAC,  ", port);
							}
							break;

						case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG1_L1:
						case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG1_L23:
						case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_EXT:
						case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_L1:
						case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_L2:
						case HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_L3:
							if(reg_pao_pc_0){
								*audioType = LX_HDMI_AUDIO_UNKNOWN_MPEG;
							}else{
								*audioType = LX_HDMI_AUDIO_PCM;
							}
							if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
								HDMI20_ADEF("HDMI[%d] Audio Type = Unknown MPEG,  ", port);
							}
							break;

						case HDMI20_BURST_AUDIO_INFO_TYPE_NULL:
							*audioType = LX_HDMI_AUDIO_PCM;
							if(_p->audioTypeAdnormalCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_TYPE_ABNORMAL].value){
								if(_p->isHBRaudio){
									_p->audioTypeAdnormalCnt++;
									if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value != 0)HDMI20_ADEF("HDMI[%d] Audio type adnormal cnt : %d", port, _p->audioTypeAdnormalCnt);
								}else{
									_p->audioTypeAdnormalCnt = 0;
								}
							}else{
								_p->audioTypeAdnormalCnt = 0;
								if(_p->audio_state == HDMI21__AUDIO_STATE__5__ENABLE__CHANGE_IRQ\
								|| _p->audio_state == HDMI21__AUDIO_STATE__0__DEFAULT)
								{
									HDMI21_HAL_Rx_Set_AudioEnable(_p->port, FALSE);
									if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_STATE].value != 0)HDMI20_ADEF("Audio[%d] state %d->%d(PAO type adrnormal change)!!!kkkkkk\n", _p->port, HDMI21__AUDIO_STATE__5__ENABLE__CHANGE_IRQ, HDMI21__AUDIO_STATE__1__DISABLE__WAIT_AUDIF_RCV);
								}
							}
							if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
								HDMI20_ADEF("HDMI[%d] Audio Type = PCM NULL(%x),  ", port, _p->audioInfo.audioType);
							}
							break;

						default:
							if(reg_pao_pc_0){
								*audioType = LX_HDMI_AUDIO_NO_AUDIO;
							}else{
								*audioType = LX_HDMI_AUDIO_PCM;
							}
							if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
								HDMI20_ADEF("HDMI[%d] Audio Type = NON-PCM,  ", port);
							}
							break;
					}
				}	//if ((reg_burst_pc_0 & HDMI21_BURST_INFO_PAYLOAD_ERROR_BIT_MASK) == 0)
				else
				{
					*audioType = LX_HDMI_AUDIO_PCM;
					if(reg_pao_pc_0 & HDMI21_BURST_INFO_PAYLOAD_ERROR_BIT_MASK){
						if(_p->audioTypeAdnormalCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_TYPE_ABNORMAL].value){
							_p->audioTypeAdnormalCnt++;
							if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value != 0)HDMI20_ADEF("HDMI[%d] Audio type adnormal cnt : %d", port, _p->audioTypeAdnormalCnt);
						}else{
							_p->audioTypeAdnormalCnt = 0;
							if(_p->audio_state == HDMI21__AUDIO_STATE__5__ENABLE__CHANGE_IRQ\
							|| _p->audio_state == HDMI21__AUDIO_STATE__0__DEFAULT)
							{
								HDMI21_HAL_Rx_Set_AudioEnable(_p->port, FALSE);
								if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_STATE].value != 0)HDMI20_ADEF("Audio[%d] state %d->%d(PAO type adrnormal change)!!!kkkkkk\n", _p->port, HDMI21__AUDIO_STATE__5__ENABLE__CHANGE_IRQ, HDMI21__AUDIO_STATE__1__DISABLE__WAIT_AUDIF_RCV);
							}
						}
					}
					if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
						HDMI20_ADEF("HDMI[%d] Audio Type = NON-PCM error,  ", port);

					}
				}
			}
		}
		else{
			//Set DVI mode
			*audioType	  = LX_HDMI_AUDIO_DVI;
			if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 4)){
				HDMI20_ADEF("HDMI[%d] Audio Type = DVI,  ", _p->port);
			}
		}
#if 0
		if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
			if((_p->video.dvi == FALSE) \
			&& ((reg_burst_pc_0 & HDMI21_BURST_INFO_PAYLOAD_ERROR_BIT_MASK) != 0) \
			&& (_p->audioInfo.audioType != LX_HDMI_AUDIO_PCM)){
				*audioType = _p->audioInfo.audioType;
				HDMI20_ADEF("HDMI[%d] Audio Error Flag & ES!! keep previous Type.byte0[aud:%x, link:%x], pc[aud:%x, link:%x], dvi[%d] HBR[%d] \n",\
				port, reg_achst_byte0, _p->top_read(HDMI21_RX_AD_MAIN_AUD_INFO_BYTE0),\
				reg_burst_pc_0, _p->top_read(HDMI21_RX_AD_MAIN_AUD_INFO_PC),_p->video.dvi, _p->isHBRaudio);
			}
		}
#endif
		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 3) gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value = 0;
	}while(0);
	return ret;
}

int HDMI21_HAL_Rx_Get_AudioCountOfChannel(UINT8 port, int *countOfChannel) {
	int ret = RET_ERROR;
	UINT32 readChannel, realChannel, proc_status1, sp_channel, hbr_status;
	//UINT32 proc_config0;
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	HDMI21_HAL_RX_AUDIO_DATA *_a;

	do{
		/* [Check]Basic */
		if (port >= g_hdmi20_number_of_ports)	{
			HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
			break;
		}

		/* [Get]Handler */
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];
		_a = (HDMI21_HAL_RX_AUDIO_DATA *)&gHDMI21RxAudioHandler[port];

		/* [Get]Channel Info */
		readChannel = _p->link_read(HDMI21_RX_PDEC_AUDIF_PB3_0) & HDMI21_RX_PDEC_AUDIF_PB3_0__BIT_MASK_CHA_CNT;
		readChannel = readChannel >> 8;
		gHDMI21AudioIFChannel[_p->port] = readChannel;

		/* [Check]HBR */
		hbr_status = _p->link_read(HDMI21_RX_PROC_STATUS1) & HDMI21_RX_PROC_STATUS1__AUD_FMT_ST__MASK;
		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_HBR].value == 1) {
			_p->isHBRaudio = FALSE;
		}else if (gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_HBR].value == 2) {
			_p->isHBRaudio = TRUE;
		}else {
			if((hbr_status == HDMI21_RX_PROC_STATUS1__AUD_FMT_ST__HBR) && (_p->isHBRaudio == FALSE)) {
				_p->isHBRaudio = TRUE;
				HDMI20_ADEF("HDMI[%d] Audio High Bit Rate Audio start(pdec_aud_sts=0x%x)!\n", _p->port, hbr_status);
			}else if ((hbr_status != HDMI21_RX_PROC_STATUS1__AUD_FMT_ST__HBR) && (_p->isHBRaudio == TRUE)) {
				_p->isHBRaudio = FALSE;
				HDMI20_ADEF("HDMI[%d] Audio High Bit Rate Audio stop(pdec_aud_sts=0x%x)!\n", _p->port, hbr_status);
			}
		}

		/* Channel Count by Sample present */
		proc_status1 = _p->link_read(HDMI21_RX_PROC_STATUS1);
		sp_channel = 0;
		if(proc_status1 & HDMI21_RX_PROC_STATUS1__SAMPLE_PRESENT_MASK1) sp_channel++;
		if(proc_status1 & HDMI21_RX_PROC_STATUS1__SAMPLE_PRESENT_MASK2) sp_channel++;
		if(proc_status1 & HDMI21_RX_PROC_STATUS1__SAMPLE_PRESENT_MASK3) sp_channel++;
		if(proc_status1 & HDMI21_RX_PROC_STATUS1__SAMPLE_PRESENT_MASK4) sp_channel++;

		/* [Set] check channel info */
		if((gHDMI21AudioIgnoreChannel[_p->port] != 0) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_CHANNEL].value != 0)){
			_a->procConfig0_chAlloc = HDMI21_RX__EXT__PROC_CONFIG0__SPK_ALLOC_OVR_EN ;
			_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
		}

		if((gHDMI21AudioIgnoreChannel[_p->port] == 0) && (gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_CHANNEL].value == 0)){
			if(sp_channel > 0){
				realChannel = sp_channel * 2;

				/* [Check] Currunt Setting */
				if((_p->audioInfo.countOfChannel == 2) && (_p->link_read(HDMI21_RX_PROC_CONFIG3) != HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH2)){
					HDMI20_ADEF("HDMI[%d] Audio Channel Allocation Error!!! : 0x%x -> 0x%x \n", _p->port, _p->link_read(HDMI21_RX_PROC_CONFIG3), HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH2);
					_a->procConfig0_chAlloc = HDMI21_RX__EXT__PROC_CONFIG0__SPK_ALLOC_OVR_DISEN ;
					_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
					_p->link_write(HDMI21_RX_PROC_CONFIG3, HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH2);
					_a->procConfig0_chAlloc = HDMI21_RX__EXT__PROC_CONFIG0__SPK_ALLOC_OVR_EN;
					_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
				}else if((_p->audioInfo.countOfChannel == 4) && (_p->link_read(HDMI21_RX_PROC_CONFIG3) != HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH2)){
					HDMI20_ADEF("HDMI Audio Channel Allocation Error!!! : 0x%x -> 0x%x \n",_p->link_read(HDMI21_RX_PROC_CONFIG3), HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH4);
					_a->procConfig0_chAlloc = HDMI21_RX__EXT__PROC_CONFIG0__SPK_ALLOC_OVR_DISEN ;
					_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
					_p->link_write(HDMI21_RX_PROC_CONFIG3, HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH2);
					_a->procConfig0_chAlloc = HDMI21_RX__EXT__PROC_CONFIG0__SPK_ALLOC_OVR_EN;
					_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
				}else if((_p->audioInfo.countOfChannel == 6) && (_p->link_read(HDMI21_RX_PROC_CONFIG3) != HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH2)){
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																														HDMI20_ADEF("HDMI[%d] Audio Channel Allocation Error!!! : 0x%x -> 0x%x \n", _p->port, _p->link_read(HDMI21_RX_PROC_CONFIG3), HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH6);
					_a->procConfig0_chAlloc = HDMI21_RX__EXT__PROC_CONFIG0__SPK_ALLOC_OVR_DISEN ;
					_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
					_p->link_write(HDMI21_RX_PROC_CONFIG3, HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH2);
					_a->procConfig0_chAlloc = HDMI21_RX__EXT__PROC_CONFIG0__SPK_ALLOC_OVR_EN;
					_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
				}else if((_p->audioInfo.countOfChannel == 8) && (_p->link_read(HDMI21_RX_PROC_CONFIG3) != HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH8)){
					HDMI20_ADEF("HDMI[%d] Audio Channel Allocation Error!!! : 0x%x -> 0x%x \n", _p->port, _p->link_read(HDMI21_RX_PROC_CONFIG3), HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH8);
					_a->procConfig0_chAlloc = HDMI21_RX__EXT__PROC_CONFIG0__SPK_ALLOC_OVR_DISEN ;
					_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
					_p->link_write(HDMI21_RX_PROC_CONFIG3, HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH8);
					_a->procConfig0_chAlloc = HDMI21_RX__EXT__PROC_CONFIG0__SPK_ALLOC_OVR_EN;
					_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
				}


				/* [Set] Update Setting */
				if((_p->audioInfo.countOfChannel > realChannel) \
				|| (gHDMI21AudioChannelIncreaseCnt[_p->port] >= gHDMI21RxDevAudioControler[HDMI21__AUDIO_CHANNEL_INCREASE_TIME].value)){
					_a->procConfig0_chAlloc = HDMI21_RX__EXT__PROC_CONFIG0__SPK_ALLOC_OVR_DISEN;
					_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));

					if(realChannel == 2){
						_p->link_write(HDMI21_RX_PROC_CONFIG3, HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH2);
						//gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_CHANNEL].value = 1;
						gHDMI21AudioIgnoreChannel[_p->port] = 1;
					}else if(realChannel == 4){
						_p->link_write(HDMI21_RX_PROC_CONFIG3, HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH2);
						//gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_CHANNEL].value = 1;
						gHDMI21AudioIgnoreChannel[_p->port] = 1;
					}else if(realChannel == 6){
						_p->link_write(HDMI21_RX_PROC_CONFIG3, HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH2);
						//gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_CHANNEL].value = 1;
						gHDMI21AudioIgnoreChannel[_p->port] = 1;
					}else if(realChannel == 8){
						_p->link_write(HDMI21_RX_PROC_CONFIG3, HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH8);
						//gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_CHANNEL].value = 1;
						gHDMI21AudioIgnoreChannel[_p->port] = 1;
					}
					HDMI20_ADEF("HDMI[%d] Audio Channel Allocation Override Set!!! : %d \n", _p->port,  realChannel);
					_p->audioChMapCnt = 0;

					_a->procConfig0_chAlloc = HDMI21_RX__EXT__PROC_CONFIG0__SPK_ALLOC_OVR_EN;
					_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
					gHDMI21AudioChannelAllocOverride[_p->port] = TRUE;
					if(gHDMI21AudioChannelIncreaseCnt[_p->port] >= gHDMI21RxDevAudioControler[HDMI21__AUDIO_CHANNEL_INCREASE_TIME].value){
						gHDMI21IsAudioChannelIncrease[_p->port] = TRUE;
						HDMI20_ADEF("HDMI[%d] Audio channel increase[cnt:%d, ch:%d]!!!\n", port, gHDMI21AudioChannelIncreaseCnt[_p->port], realChannel);
					}
					gHDMI21AudioChannelIncreaseCnt[_p->port] = 0;
				}else if(_p->audioInfo.countOfChannel < realChannel){
					//gHDMI21AudioChannelIncreaseCnt[_p->port]++;
					//if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value != 0)HDMI20_ADEF("HDMI[%d] Audio channel increase cnt : %d", port, gHDMI21AudioChannelIncreaseCnt[_p->port]);
				}else if(_p->audioInfo.countOfChannel == realChannel){
					gHDMI21AudioChannelIncreaseCnt[_p->port] = 0;
				}
			}else{
#if 0
				_a->procConfig0_chAlloc = HDMI21_RX__EXT__PROC_CONFIG0__SPK_ALLOC_OVR_DISEN;
				_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
				_p->link_write(HDMI21_RX_PROC_CONFIG3, HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_INIT);
				//gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_CHANNEL].value = 0;
#endif

				realChannel = _p->audioInfo.countOfChannel;
			}
		}

		/* [Set] Channel mapping force channel */
		if((gHDMI21AudioIgnoreChannel[_p->port] != 0) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_CHANNEL].value != 0)){
			if(_p->link_read(HDMI21_RX_PROC_CONFIG3) == HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH2){
				realChannel = 2;
			}else if(_p->link_read(HDMI21_RX_PROC_CONFIG3) == HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH4){
				realChannel = 4;
			}else if(_p->link_read(HDMI21_RX_PROC_CONFIG3) == HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH6){
				realChannel = 6;
			}else if(_p->link_read(HDMI21_RX_PROC_CONFIG3) == HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH8){
				realChannel = 8;
			}
		}

		if((realChannel < 2) || (realChannel > 8)) {
			*countOfChannel = 2;
		}else {
			*countOfChannel = realChannel;
		}

		if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 7) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 8)){
			HDMI20_ADEF("HDMI[%d] Audio count of channel register vlaue : %d, proc_status1 : 0x%x, => %d ch\n", _p->port, readChannel, proc_status1, realChannel);
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 7) gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value = 0;
		}

		ret = RET_OK;
	}while(0);

	return ret;
}

int HDMI21_HAL_Rx_Get_AudioStream(UINT8 port, LX_HDMI_AUDIO_STREAM_T *stream){
	int ret = RET_ERROR;
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	do{
		/* [Check]Basic */
		if (port >= g_hdmi20_number_of_ports)	{
			HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
			break;
		}

		/* [Get]Handler */
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];
		/* [Get] Stream Info */
		*stream = (_p->link_read(HDMI21_RX_PROC_STATUS1) & HDMI21_RX_PROC_STATUS1__AUD_FMT_ST__MASK);

		if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 0x9) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 0x10)){
			HDMI20_ADEF("HDMI[%d] Audio starem : %d\n", _p->port, (_p->link_read(HDMI21_RX_PROC_STATUS1)| HDMI21_RX_PROC_STATUS1__AUD_FMT_ST__MASK));
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 0x9) gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value = 0;
		}

		ret = RET_OK;
	}while(0);

	return ret;
}

/* Added 2014/08/05 taejun.lee */
int HDMI21_HAL_Rx_Get_AudioInfo(UINT8 port)
{
	int ret = RET_ERROR;
	int __vidStable = 0;
	BOOLEAN audioInfoChange = FALSE;
	//UINT32 mute_status, nDiff, ctsDiff;;
	UINT32 fifo_fill = 0x0;
	UINT32 fifo_status = 0x0;
	UINT32 fifo_diff = 0x0;
	UINT32 hbr_status = 0;
	UINT32 proc_config0 = 0;
	UINT32 proc_config2 = 0;
	UINT32 proc_config3 = 0;
	UINT32 proc_status1 = 0;
	UINT32 mute_status = 0;
	UINT32 sp_channel = 0;
	LX_HDMI_AUDIO_INFO_T	data;
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	HDMI21_HAL_RX_AUDIO_DATA *_a;

	do{
		/* [Check]Basic */
		if (port >= g_hdmi20_number_of_ports)	{
			HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
			break;
		}

		/* [Get]Handler */
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];
		_a = (HDMI21_HAL_RX_AUDIO_DATA *)&gHDMI21RxAudioHandler[port];


		/* [Wait]Video Stable */
		if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_TICK_THRESHOLD_LOWPOWER].value > 0) {
			if((_p->lowPowerMode <= HDMI21_HAL_POWER_NORMAL) &&(_p->stable_cnt >= gHDMI21RxDevVideoControler[HDMI21__STABLE_CHECK_CNT].value)) {
				__vidStable = 1;
			}
		}
		else {
			if(_p->stable_cnt >= gHDMI21RxDevVideoControler[HDMI21__STABLE_CHECK_CNT].value) {
				__vidStable = 1;
			}
		}


		if(__vidStable){
			if (_p->audioStandByCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_STANDBY_TIME].value) {
				_p->audioStandByCnt++;
				if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value != 0)HDMI20_ADEF("HDMI[%d] Audio stand by cnt : %d", _p->port, _p->audioStandByCnt);
				if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
					if(_p->audioStandByCnt == (gHDMI21RxDevAudioControler[HDMI21__AUDIO_STANDBY_TIME].value-2)){
						HDMI21_HAL_Rx_Set_Audio_Configure(_p->port, _p->phyInitiatedMode);
						if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG].value != 0) HDMI20_ADEF("HDMI[%d] Audio configuration for start!\n", _p->port);
					}
				}
			}
		}else{
			gHDMI21AudioPrintLimitCnt[_p->port] = 0;
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value != 0) HDMI20_ADEF("HDMI[%d] Audio print limit cnt init!", port);
		}

		if(_p->audioStandByCnt == gHDMI21RxDevAudioControler[HDMI21__AUDIO_STANDBY_TIME].value) {
			if(_p->audio_state != HDMI21__AUDIO_STATE__5__ENABLE__CHANGE_IRQ){
				HDMI21_HAL_Rx_Audio_Set_SwWaAudioDolbyWakeUpCall(_p->port);
			}

			if(_p->isAudioRegReady == FALSE){
				HDMI21_Rx_Audio_Path_SetInthw(_p->port);
			}

			/* [Check]Audio Format Change Mask */
			if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
				proc_config2 = _p->link_read(HDMI21_RX_PROC_CONFIG2);
				if(proc_config2 != HDMI21_RX_PROC_CONFIG2__FMT_OFF){
					_p->link_write(HDMI21_RX_PROC_CONFIG2,	HDMI21_RX_PROC_CONFIG2__FMT_OFF);
					HDMI20_ADEF("HDMI[%d] Audio Format Change Mask Disable!\n", _p->port);
				}

				proc_status1 = _p->link_read(HDMI21_RX_PROC_STATUS1);
				if(((proc_status1 & HDMI21_RX_PROC_STATUS1__AUD_MUTE_ST) == HDMI21_RX_PROC_STATUS1__AUD_MUTE_ST)\
				&& (_p->audioChMapStandByCnt >= gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME].value)){
					HDMI21_HAL_Rx_Set_AudioFIFOReset(_p->port);
				}
			}

			/* [Get]Audio Info */
			HDMI21_HAL_Rx_Get_AudioType(_p->port, &data.audioType);
			HDMI21_HAL_Rx_Get_AudioACRParam(_p->port, FALSE);
			HDMI21_HAL_Rx_Get_AudioFreqFromTMDSClock(_p->port, &data.samplingFreq);
			HDMI21_HAL_Rx_Get_AudioStream(_p->port, &data.stream);
			HDMI21_HAL_Rx_Get_AudioWordLength(_p->port, &data.wordLength);
			
			if(data.audioType == LX_HDMI_AUDIO_PCM && (_p->video.dvi == FALSE)) {
				HDMI21_HAL_Rx_Get_AudioCountOfChannel(_p->port, &data.countOfChannel);
			}else{
				_a->procConfig0_chAlloc = HDMI21_RX__EXT__PROC_CONFIG0__SPK_ALLOC_OVR_DISEN;
				_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
				_p->link_write(HDMI21_RX_PROC_CONFIG3, HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_INIT);
				//gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_CHANNEL].value = 0;
				gHDMI21AudioIgnoreChannel[_p->port] = 0;
			}

			/* [Wait]Audio stable*/
			if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
				if(_p->audioStableCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME_O22].value){
					if(_p->audioFifoErrMuteCnt  == gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ERR_MUTE_TIME].value) {
						_p->audioStableCnt++;
						if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value != 0)HDMI20_ADEF("HDMI[%d] Audio stable cnt : %d", port, _p->audioStableCnt);

						if(_p->audioStableCnt == gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_O22].value){
							_p->audioIrqFifoErrCnt = 0;
							HDMI21_Rx_Audio_Path_SetInthw(_p->port);
							if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG].value != 0) HDMI20_ADEF("HDMI[%d] Audio reset for start!\n", _p->port);
						}
					}
				}else {
					if(_p->audioForceMuteCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_MUTE_TIME_O22].value){
						_p->audioForceMuteCnt++;
						if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value != 0)HDMI20_ADEF("HDMI[%d] Audio Force Mute Cnt : %d", port, _p->audioForceMuteCnt);
					}
				}
			}else{
				if(_p->audioStableCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME].value){
					if(_p->audioFifoErrMuteCnt  == gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ERR_MUTE_TIME].value) {
						_p->audioStableCnt++;
						if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value != 0)HDMI20_ADEF("HDMI[%d] Audio stable cnt : %d", port, _p->audioStableCnt);

						if(_p->audioStableCnt == gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE].value){
							_p->audioIrqFifoErrCnt = 0;
							HDMI21_Rx_Audio_Path_SetInthw(_p->port);
							if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG].value != 0) HDMI20_ADEF("HDMI[%d] Audio reset for start!\n", _p->port);
						}
					}
				}else {
					if(_p->audioForceMuteCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_MUTE_TIME].value){
						_p->audioForceMuteCnt++;
						if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value != 0)HDMI20_ADEF("HDMI[%d] Audio Force Mute Cnt : %d", port, _p->audioForceMuteCnt);
					}
				}
			}

			/* [Check]HBR */
			hbr_status = _p->link_read(HDMI21_RX_PROC_STATUS1) & HDMI21_RX_PROC_STATUS1__AUD_FMT_ST__MASK;
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_HBR].value == 1) {
				_p->isHBRaudio = FALSE;
			}else if (gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_HBR].value == 2) {
				_p->isHBRaudio = TRUE;
			}else {
				if((hbr_status == HDMI21_RX_PROC_STATUS1__AUD_FMT_ST__HBR) && (_p->isHBRaudio == FALSE)) {
					_p->isHBRaudio = TRUE;
					if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_DISABLE_SPREAD].value != 0)){
						_p->top_write(HDMI21_RX_ACR_CLK_N_FS,			HDMI21_RX_ACR_CLK_N_FS__512);
						_a->procConfig0_chSpread = HDMI21_RX__EXT__PROC_CONFIG0__AUD_CHAN_SPREAD_DISEN;
						_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
					}else{
						_a->procConfig0_chSpread = HDMI21_RX__EXT__PROC_CONFIG0__AUD_CHAN_SPREAD_EN;
						_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
					}

					HDMI20_ADEF("HDMI[%d] Audio High Bit Rate Audio start(pdec_aud_sts=0x%x)!\n", _p->port, hbr_status);
				}else if ((hbr_status != HDMI21_RX_PROC_STATUS1__AUD_FMT_ST__HBR) && (_p->isHBRaudio == TRUE)) {
					_p->isHBRaudio = FALSE;
					_p->top_write(HDMI21_RX_ACR_CLK_N_FS,			HDMI21_RX_ACR_CLK_N_FS__128);
					_a->procConfig0_chSpread = HDMI21_RX__EXT__PROC_CONFIG0__AUD_CHAN_SPREAD_DISEN;
					_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
					HDMI20_ADEF("HDMI[%d] Audio High Bit Rate Audio stop(pdec_aud_sts=0x%x)!\n", _p->port, hbr_status);
				}
			}

			/* [Check]HBR seetting */
			proc_config0 = _p->link_read(HDMI21_RX_PROC_CONFIG0);
			if((hbr_status == HDMI21_RX_PROC_STATUS1__AUD_FMT_ST__HBR) && (_p->isHBRaudio == TRUE)){
				if((proc_config0 & HDMI21_RX_PROC_CONFIG0__AUD_CHAN_SPREAD_EN) == 0x0){
					_a->procConfig0_chSpread = HDMI21_RX__EXT__PROC_CONFIG0__AUD_CHAN_SPREAD_EN;
					_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
					proc_config0 = _p->link_read(HDMI21_RX_PROC_CONFIG0);
					HDMI20_ADEF("HDMI[%d] Audio High Bit Rate Audio re-setting for enable(pdec_aud_sts=0x%x,proc_cfg=0x%x)!\n", _p->port, hbr_status, proc_config0);
				}
			}else if((hbr_status != HDMI21_RX_PROC_STATUS1__AUD_FMT_ST__HBR) && (_p->isHBRaudio == FALSE)){
				if((proc_config0 & HDMI21_RX_PROC_CONFIG0__AUD_CHAN_SPREAD_EN) == HDMI21_RX_PROC_CONFIG0__AUD_CHAN_SPREAD_EN){
					_a->procConfig0_chSpread = HDMI21_RX__EXT__PROC_CONFIG0__AUD_CHAN_SPREAD_DISEN;
					_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
					proc_config0 = _p->link_read(HDMI21_RX_PROC_CONFIG0);
					HDMI20_ADEF("HDMI[%d] Audio High Bit Rate Audio re-setting for disable(pdec_aud_sts=0x%x,proc_cfg=0x%x)!\n", _p->port, hbr_status, proc_config0);
				}
			}


			/* Channel Count by Sample present */
			proc_status1 = _p->link_read(HDMI21_RX_PROC_STATUS1);
			sp_channel = 0;
			if(proc_status1 & HDMI21_RX_PROC_STATUS1__SAMPLE_PRESENT_MASK1) sp_channel++;
			if(proc_status1 & HDMI21_RX_PROC_STATUS1__SAMPLE_PRESENT_MASK2) sp_channel++;
			if(proc_status1 & HDMI21_RX_PROC_STATUS1__SAMPLE_PRESENT_MASK3) sp_channel++;
			if(proc_status1 & HDMI21_RX_PROC_STATUS1__SAMPLE_PRESENT_MASK4) sp_channel++;
			if(_p->audio_state == HDMI21__AUDIO_STATE__5__ENABLE__CHANGE_IRQ && (sp_channel != 0) && (sp_channel<4) && _p->isHBRaudio){
				if(_p->audioHBRAdnormalCnt <  gHDMI21RxDevAudioControler[HDMI21__AUDIO_HBR_ABNORMAL].value){
					_p->audioHBRAdnormalCnt++;
				}else{
					HDMI21_HAL_Rx_Set_AudioEnable(_p->port, FALSE);
					HDMI20_ADEF("HDMI[%d] Audio state %d->%d(Format!=Sp change)!!!kkkkkk\n", _p->port, HDMI21__AUDIO_STATE__5__ENABLE__CHANGE_IRQ, HDMI21__AUDIO_STATE__1__DISABLE__WAIT_AUDIF_RCV);
					_p->audioHBRAdnormalCnt = 0;
				}
			}

			/* [Set]Channel Mapping */
			if(_p->audio_state == HDMI21__AUDIO_STATE__5__ENABLE__CHANGE_IRQ){
				if(_p->audioChMapStandByCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_CH_MAP_STANDBY_TIME].value){
					_p->audioChMapStandByCnt++;
					if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value != 0)HDMI20_ADEF("HDMI[%d] Audio Channel Mapping Cnt : %d", port, _p->audioChMapStandByCnt);
				}

				fifo_status = _p->link_read(HDMI21_RX_AUD_FIFO_STS2__FILLSTS1);
				fifo_fill = fifo_status & 0xFFFF;
				if(fifo_fill > gHDMI21AudioFIFOFill[_p->port]){
					fifo_diff = fifo_fill - gHDMI21AudioFIFOFill[_p->port];
				}else{
					fifo_diff = gHDMI21AudioFIFOFill[_p->port]- fifo_fill;
				}

				if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_DIFF].value > 0){
					HDMI20_ADEF("HDMI[%d] Audio fifo_diff(%d), fifo_fill(%d), fifo_status(0x%x)\n", _p->port, fifo_diff, fifo_fill, fifo_status);
					gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_DIFF].value--;
				}

				/* if(((fifo_diff > 20) || (fifo_fill > 0 && fifo_fill < 20)) && (_p->video.dvi == 0)\ */
				if(((fifo_status & HDMI21_RX_AUD_FIFO_STS2__OVERFLOW) || (fifo_status & HDMI21_RX_AUD_FIFO_STS2__UNDERFLOW) || (fifo_fill < 20))\
					&& (_p->video.dvi == FALSE)\
					&& (fifo_status)\
					&& (gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ERROR_PRINT_DISABLE].value == 0x0)
					&& (gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_ERR].value == 0x0)){
					if(fifo_status & HDMI21_RX_AUD_FIFO_STS2__ERR){
						if(gHDMI21AudioPrintLimitCnt[_p->port] < gHDMI21RxDevAudioControler[HDMI21__AUDIO_PRINT_LIMIT].value){
							HDMI20_ADEF("HDMI[%d] Audio fifo abnormal(cnt:%d, fifo:%d->%d(%d), ch:%d, fifo_status:0x%x)\n", _p->port, _p->audioChMapCnt, gHDMI21AudioFIFOFill[_p->port], fifo_fill, fifo_diff, data.countOfChannel, fifo_status);
							gHDMI21AudioPrintLimitCnt[_p->port]++;
						}

						
						if(gHDMI21AudioChannelAbnormalCnt[_p->port] < gHDMI21RxDevAudioControler[HDMI21__AUDIO_CHANNEL_ABNORMAL].value){
							gHDMI21AudioChannelAbnormalCnt[_p->port]++;
							if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value != 0)HDMI20_ADEF("HDMI[%d] Audio Channel abnormal Cnt : %d, print limit cnt : %d", port, gHDMI21AudioChannelAbnormalCnt[_p->port], gHDMI21AudioPrintLimitCnt[_p->port]);
						}else{
							if(gHDMI21AudioPrintLimitCnt[_p->port] < gHDMI21RxDevAudioControler[HDMI21__AUDIO_PRINT_LIMIT].value){
								if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
									HDMI20_ADEF("HDMI[%d] Audio Restart due to channel abnormal(cnt:%d)\n", _p->port, gHDMI21AudioChannelAbnormalCnt[_p->port]);
									HDMI21_HAL_Rx_Set_AudioEnable(_p->port, FALSE);
								}
								gHDMI21AudioChannelAbnormalCnt[_p->port] = 0;
							}
						}
					}else if(fifo_status & HDMI21_RX_AUD_FIFO_STS2__OVERFLOW){
						if(gHDMI21AudioPrintLimitCnt[_p->port] < gHDMI21RxDevAudioControler[HDMI21__AUDIO_PRINT_LIMIT].value){
							HDMI20_ADEF("HDMI[%d] Audio fifo overflow(cnt:%d, fifo:%d->%d(%d), ch:%d, fifo_status:0x%x)\n", _p->port, _p->audioChMapCnt, gHDMI21AudioFIFOFill[_p->port], fifo_fill, fifo_diff, data.countOfChannel, fifo_status);
							gHDMI21AudioPrintLimitCnt[_p->port]++;
						}
						gHDMI21AudioFIFOAdnormalCnt[_p->port] = 0;
					}else if(fifo_status & HDMI21_RX_AUD_FIFO_STS2__UNDERFLOW){
						if(gHDMI21AudioPrintLimitCnt[_p->port] < gHDMI21RxDevAudioControler[HDMI21__AUDIO_PRINT_LIMIT].value){
							HDMI20_ADEF("HDMI[%d] Audio fifo underflow(cnt:%d, fifo:%d->%d(%d), ch:%d, fifo_status:0x%x)\n", _p->port, _p->audioChMapCnt, gHDMI21AudioFIFOFill[_p->port], fifo_fill, fifo_diff, data.countOfChannel, fifo_status);
							gHDMI21AudioPrintLimitCnt[_p->port]++;
						}
						gHDMI21AudioFIFOAdnormalCnt[_p->port] = 0;
					}

					gHDMI21AudioFIFOAdjustPCnt[_p->port] = 0;
					gHDMI21AudioFIFOAdjustMCnt[_p->port] = 0;
					_p->audioChMapStandByCnt = 0;
					_p->audioChMapCnt++;
					if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value != 0) HDMI20_ADEF("HDMI[%d] Audio ch-map cnt : %d", _p->port, _p->audioChMapCnt);
					if(_p->audioChMapCnt >= gHDMI21RxDevAudioControler[HDMI21__AUDIO_CH_MAP_MAX].value) {
						if(_p->isHBRaudio == FALSE){
							HDMI21_HAL_Rx_Set_AudioChange(_p->port);
							proc_config3 = _p->link_read(HDMI21_RX_PROC_CONFIG3);
							if(proc_config3 == HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH8) {	// Manual 2ch
								_p->link_write(HDMI21_RX_PROC_CONFIG3, HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH2);
								_a->procConfig0_chAlloc = HDMI21_RX__EXT__PROC_CONFIG0__SPK_ALLOC_OVR_EN;
								_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
								//gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_CHANNEL].value = 1;
								gHDMI21AudioIgnoreChannel[_p->port] = 1;
								data.countOfChannel = 2;
							}else if(proc_config3 == HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH2){	// Manual 4ch
								_p->link_write(HDMI21_RX_PROC_CONFIG3, HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH4);
								_a->procConfig0_chAlloc = HDMI21_RX__EXT__PROC_CONFIG0__SPK_ALLOC_OVR_EN;
								_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
								//gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_CHANNEL].value = 1;
								gHDMI21AudioIgnoreChannel[_p->port] = 1;
								data.countOfChannel = 4;
							}else if(proc_config3 == HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH4){	// Manual 6ch
								_p->link_write(HDMI21_RX_PROC_CONFIG3, HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH6);
								_a->procConfig0_chAlloc = HDMI21_RX__EXT__PROC_CONFIG0__SPK_ALLOC_OVR_EN;
								_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
								//gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_CHANNEL].value = 1;
								gHDMI21AudioIgnoreChannel[_p->port] = 1;
								data.countOfChannel = 6;
							}else if(proc_config3 == HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH6){	// Manual 8ch
								_p->link_write(HDMI21_RX_PROC_CONFIG3, HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH8);
								_a->procConfig0_chSpread = HDMI21_RX__EXT__PROC_CONFIG0__SPK_ALLOC_OVR_EN;
								_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
								//gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_CHANNEL].value = 1;
								gHDMI21AudioIgnoreChannel[_p->port] = 1;
								data.countOfChannel = 8;
							}else if(proc_config3 == HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_INIT){	// Manual 8ch
								_p->link_write(HDMI21_RX_PROC_CONFIG3, HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH2);
								_a->procConfig0_chAlloc = HDMI21_RX__EXT__PROC_CONFIG0__SPK_ALLOC_OVR_EN;
								_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
								//gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_CHANNEL].value = 1;
								gHDMI21AudioIgnoreChannel[_p->port] = 1;
								data.countOfChannel = 8;
							}else{
								_p->link_write(HDMI21_RX_PROC_CONFIG3, HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_INIT);
								//gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_CHANNEL].value = 0;
								gHDMI21AudioIgnoreChannel[_p->port] = 0;
							}
							if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ERROR_PRINT_DISABLE].value == 0x0) && (gHDMI21AudioPrintLimitCnt[_p->port] < gHDMI21RxDevAudioControler[HDMI21__AUDIO_PRINT_LIMIT].value))HDMI20_ADEF("HDMI[%d] Audio ch-map change(ch-map:0x%x->0x%x, fifo:%d->%d(%d))\n", _p->port, proc_config3, _p->link_read(HDMI21_RX_PROC_CONFIG3), gHDMI21AudioFIFOFill[_p->port], fifo_fill, fifo_diff);
							_p->audioChMapStandByCnt = 0;
							gHDMI21AudioChannelAbnormalCnt[_p->port]++;
						}
						HDMI21_HAL_Rx_Set_AudioFIFOReset(_p->port);

						_p->audioChMapCnt = 0;
					}
				}else {
					if(_p->audioChMapCnt > 0){
						_p->audioChMapCnt--;

						if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value != 0)HDMI20_ADEF("HDMI[%d] Audio Channel Mapping Cnt : %d", port, _p->audioChMapCnt);
					}

					if(gHDMI21AudioChannelAbnormalCnt[_p->port] > 0){
						gHDMI21AudioChannelAbnormalCnt[_p->port]--;

						if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value != 0)HDMI20_ADEF("HDMI[%d] Audio Channel abnormal Cnt : %d", port, gHDMI21AudioChannelAbnormalCnt[_p->port]);
					}

					if(gHDMI21AudioPrintLimitCnt[_p->port] > 0){
						gHDMI21AudioPrintLimitCnt[_p->port]--;

						if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value != 0)HDMI20_ADEF("HDMI[%d] Audio Channel Print Limit Cnt : %d", port, gHDMI21AudioPrintLimitCnt[_p->port]);
					}
				}
			}

			//if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_CHANNEL].value != 0)HDMI20_ADEF("ignore channel \n");

			/* [Check]Info Change */
			// Type change
			if(data.audioType == LX_HDMI_AUDIO_NO_AUDIO || data.audioType != _p->audioInfo.audioType){
				audioInfoChange = TRUE;
			}
			if((_p->audioInfo.audioType != data.audioType)\
			&&(gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_ERR].value == 0x0)){
				HDMI20_ADEF("HDMI[%d] Audio type change(%d -> %d) \n", _p->port, _p->audioInfo.audioType, data.audioType);
				_p->audioInfo.audioType = data.audioType;
				if(data.audioType >= LX_HDMI_AUDIO_UNKNOWN_AC3){
					_p->audioUnknowTypeMuteCnt = 0;
					if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value != 0)HDMI20_ADEF("HDMI[%d] Audio Force Mute Cnt start: %d!!!", port, _p->audioForceMuteCnt);

				}
			}
			// Fs change
			if((_p->audioInfo.samplingFreq != data.samplingFreq)\
			&&(gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_ERR].value == 0x0)){ //Added 2014/07/21 taejun.lee
				audioInfoChange = TRUE;
				HDMI20_ADEF("HDMI[%d] Audio Fs change(%d -> %d) \n", _p->port, _p->audioInfo.samplingFreq, data.samplingFreq);
				_p->audioInfo.samplingFreq = data.samplingFreq;
			}

			// Channel count change
			if(data.audioType == LX_HDMI_AUDIO_PCM && (_p->video.dvi == FALSE)) {
				if(((_p->audioInfo.countOfChannel > data.countOfChannel) \
				|| (((gHDMI21IsAudioChannelIncrease[_p->port] == TRUE) || ((gHDMI21AudioIgnoreChannel[_p->port] == 1) ||(gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_CHANNEL].value == 1))) && (_p->audioInfo.countOfChannel != data.countOfChannel)))\
				&& (gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_ERR].value == 0x0)){
					audioInfoChange = TRUE;
					gHDMI21IsAudioChannelIncrease[_p->port] = FALSE;
					if(gHDMI21AudioPrintLimitCnt[_p->port] < gHDMI21RxDevAudioControler[HDMI21__AUDIO_PRINT_LIMIT].value) HDMI20_ADEF("HDMI[%d] Audio channel count change(%d -> %d), increase(%d), ignore(%d) \n", _p->port, _p->audioInfo.countOfChannel, data.countOfChannel, gHDMI21IsAudioChannelIncrease[_p->port], gHDMI21AudioIgnoreChannel[_p->port]);
					_p->audioInfo.countOfChannel = data.countOfChannel;
				}
			}

			// Stream change
			if((_p->audioInfo.stream!= data.stream)\
			&&(gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_ERR].value == 0x0)){
				audioInfoChange = TRUE;
				HDMI20_ADEF("HDMI[%d] Audio Stream change(%d -> %d) \n", _p->port, _p->audioInfo.stream, data.stream);
				_p->audioInfo.stream = data.stream;
			}

			// Stream change
			if((_p->audioInfo.wordLength!= data.wordLength)\
			&&(gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_ERR].value == 0x0)){
				audioInfoChange = TRUE;
				HDMI20_ADEF("HDMI[%d] Audio Word Length change(%d -> %d) \n", _p->port, _p->audioInfo.wordLength, data.wordLength);
				_p->audioInfo.wordLength = data.wordLength;
			}

			// layout update
			_p->audioInfo.layout = (_p->link_read(HDMI21_RX_PROC_STATUS1) & HDMI21_RX_PROC_STATUS1__LAYOUT_MASK) >> 3;

			// FIFO fill update
			gHDMI21AudioFIFOFill[_p->port] = fifo_fill;

			// Init count
			if(audioInfoChange == TRUE){
				HDMI21_HAL_Rx_Set_AudioChange(_p->port);
			}

			/* [Force]Mute Control */
			mute_status = ((_p->link_read(HDMI21_RX_PROC_CONFIG0) & HDMI21_RX_PROC_CONFIG0__I2S_ENABLE) >> 1);
			proc_status1 = _p->link_read(HDMI21_RX_PROC_STATUS1);
			if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
				if(((_p->audioStableCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME_O22].value) && (mute_status != 0)) \
					|| ((proc_status1 & HDMI21_RX_PROC_STATUS1__AUD_MUTE_ST) == HDMI21_RX_PROC_STATUS1__AUD_MUTE_ST)){
					HDMI21_HAL_Rx_Set_AudioMuteControl(_p->port, HDMI21_AUDIO_MUTE);
					_p->isAudioMute = HDMI21_AUDIO_MUTE;
					if(_p->isPC == FALSE) _p->audioForceMuteCnt = 0;
					//HDMI20_AUDIO("HDMI[%d] : Force Mute enalbe[status:0x%x, mute:%d, stable:%d(%d)]\n", _p->port, proc_status1, mute_status, _p->audioStableCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME_O22].value);
				} else if((_p->audio_change != TRUE) && (mute_status == 0)\
					&& (_p->audioStandByCnt == gHDMI21RxDevAudioControler[HDMI21__AUDIO_STANDBY_TIME].value)\
					&& (_p->audioStableCnt == gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME_O22].value)\
					&& (_p->audioFifoErrMuteCnt == gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ERR_MUTE_TIME].value)\
					&& (_p->audioForceMuteCnt == gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_MUTE_TIME_O22].value)\
					&& (_p->isAudioMuteControl == FALSE)){
						HDMI21_HAL_Rx_Set_AudioMuteControl(_p->port, HDMI21_AUDIO_UNMUTE);
						_p->isAudioMute = HDMI21_AUDIO_UNMUTE;
						HDMI20_ADEF("HDMI[%d] Audio Force Mute disable![stable:%d(%d)]\n", _p->port, _p->audioStableCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME_O22].value);
				}
			}else{
				if(((_p->audioStableCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME].value) && (mute_status != 0)) \
					|| ((proc_status1 & HDMI21_RX_PROC_STATUS1__AUD_MUTE_ST) == HDMI21_RX_PROC_STATUS1__AUD_MUTE_ST)){
					HDMI21_HAL_Rx_Set_AudioMuteControl(_p->port, HDMI21_AUDIO_MUTE);
					_p->isAudioMute = HDMI21_AUDIO_MUTE;
					if(_p->isPC == FALSE) _p->audioForceMuteCnt = 0;
					//HDMI20_AUDIO("HDMI[%d] : Force Mute enalbe[status:0x%x, mute:%d, stable:%d(%d)]\n", _p->port, proc_status1, mute_status, _p->audioStableCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME].value);
				} else if((_p->audio_change != TRUE) && (mute_status == 0)\
					&& (_p->audioStandByCnt == gHDMI21RxDevAudioControler[HDMI21__AUDIO_STANDBY_TIME].value)\
					&& (_p->audioStableCnt == gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME].value)\
					&& (_p->audioFifoErrMuteCnt == gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ERR_MUTE_TIME].value)\
					&& (_p->audioForceMuteCnt == gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_MUTE_TIME].value)\
					&& (_p->isAudioMuteControl == FALSE)){
						HDMI21_HAL_Rx_Set_AudioMuteControl(_p->port, HDMI21_AUDIO_UNMUTE);
						_p->isAudioMute = HDMI21_AUDIO_UNMUTE;
						HDMI20_ADEF("HDMI[%d] Audio Force Mute disable![stable:%d(%d)]\n", _p->port, _p->audioStableCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME].value);
				}
			}

			/* [Check] FIFO Adnormal Case */
			proc_status1 = _p->link_read(HDMI21_RX_PROC_STATUS1);
			fifo_status = _p->link_read(HDMI21_RX_AUD_FIFO_STS2__FILLSTS1);
			fifo_fill = fifo_status & 0xFFFF;
			if((((proc_status1 & HDMI21_RX_PROC_STATUS1__AUD_MUTE_ST) == HDMI21_RX_PROC_STATUS1__AUD_MUTE_ST)\
				&& ((fifo_fill <= HDMI21_RX_AUD_FIFO_TH_LOW_REAL) || (fifo_fill >= HDMI21_RX_AUD_FIFO_TH_HIGH))) \
				|| (fifo_status == HDMI21_RX_AUD_FIFO_STS2__ERR)){
				if(gHDMI21AudioFIFOAdnormalCnt[_p->port] < gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ABNORMAL].value){
					if((_p->isPC == FALSE) || (fifo_status == HDMI21_RX_AUD_FIFO_STS2__ERR)){
						gHDMI21AudioFIFOAdnormalCnt[_p->port]++;
						if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value != 0)HDMI20_ADEF("HDMI[%d] Audio FIFO adnormal Cnt start: %d!!!(proc_status1(0x%x), fifo(0x%x)", port, gHDMI21AudioFIFOAdnormalCnt[_p->port], proc_status1, fifo_status);
					}else{
						if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value != 0)HDMI20_ADEF("HDMI[%d] Audio FIFO adnormal on PC connection : %d -> 0!!!(proc_status1(0x%x), fifo(0x%x)", port, gHDMI21AudioFIFOAdnormalCnt[_p->port], proc_status1, fifo_status);
						gHDMI21AudioFIFOAdnormalCnt[_p->port] = 0;
						/* [Set] Force Audio start on PC connection */
						if(_p->audio_state == HDMI21__AUDIO_STATE__0__DEFAULT){
							HDMI21_HAL_Rx_Set_AudioEnable(_p->port, TRUE);
							HDMI21_HAL_Rx_Set_Audio_Configure(_p->port, _p->phyInitiatedMode);
							_p->audio_state = HDMI21__AUDIO_STATE__4__ENABLE__WAIT_FIFO_PASS_IRQ2;

							HDMI20_ADEF("HDMI[%d] Audio Force start on PC connection condition \n", port);
						}
					}
				}else{
					if(_p->audio_state == HDMI21__AUDIO_STATE__5__ENABLE__CHANGE_IRQ\
						|| _p->audio_state == HDMI21__AUDIO_STATE__0__DEFAULT){
						gHDMI21AudioFIFOAdnormalCnt[_p->port] = 0;
						HDMI21_HAL_Rx_Set_AudioEnable(_p->port, FALSE);
						if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_STATE].value != 0)HDMI20_ADEF("HDMI[%d] Audio state %d->%d(FIFO adrnormal change)!!!kkkkkk\n", _p->port, HDMI21__AUDIO_STATE__5__ENABLE__CHANGE_IRQ, HDMI21__AUDIO_STATE__1__DISABLE__WAIT_AUDIF_RCV);
					}
				}
			}else{
				gHDMI21AudioFIFOAdnormalCnt[_p->port] = 0;
			}


			/* [Check]Internal Mute Disable */
			if(((proc_status1 & HDMI21_RX_PROC_STATUS1__AUD_MUTE_ST) != HDMI21_RX_PROC_STATUS1__AUD_MUTE_ST) && (_p->isAudioMute == HDMI21_AUDIO_UNMUTE)){
				HDMI21_HAL_Rx_Set_AudioMuteControl(port, HDMI21_AUDIO_UNMUTE);
				_p->isAudioMute = HDMI21_AUDIO_UNMUTE;
			}
		}

		/* [Check]FIFO Error */
		fifo_fill = _p->link_read(HDMI21_RX_AUD_FIFO_STS2__FILLSTS1);
		if((fifo_fill & HDMI21_RX_AUD_FIFO_STS2__ERR) && (_p->video.dvi == FALSE)\
			&& (gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_ERR].value == 0x0)){
			HDMI21_HAL_Rx_Set_AudioMuteControl(_p->port, HDMI21_AUDIO_MUTE);
			_p->isAudioMute = HDMI21_AUDIO_MUTE;
			if(_p->isPC == FALSE)_p->audioFifoErrMuteCnt = 0;

			if(_p->stable_cnt >= gHDMI21RxDevVideoControler[HDMI21__STABLE_CHECK_CNT].value){
				HDMI21_HAL_Rx_Get_AudioType(_p->port, &data.audioType);
				if(data.audioType == LX_HDMI_AUDIO_PCM && (_p->video.dvi == FALSE))	{
					HDMI21_HAL_Rx_Get_AudioCountOfChannel(_p->port, &data.countOfChannel);
				}else{
					_a->procConfig0_chAlloc = HDMI21_RX__EXT__PROC_CONFIG0__SPK_ALLOC_OVR_DISEN;
					_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
					_p->link_write(HDMI21_RX_PROC_CONFIG3, HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_INIT);
					//gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_CHANNEL].value = 0;
					gHDMI21AudioIgnoreChannel[_p->port] = 0;
				}
			}
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG].value != 0) HDMI20_ADEF("HDMI[%d] Audio FIFO Reset![fill:0x%x, dvi:%d, ignore:%d]\n", _p->port, fifo_fill, _p->video.dvi, gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_ERR].value);

			HDMI21_HAL_Rx_Set_AudioFIFOReset(_p->port);
		}else if(_p->audioFifoErrMuteCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ERR_MUTE_TIME].value){
			_p->audioFifoErrMuteCnt++;
			if(_p->audioFifoErrMuteCnt == (gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ERR_MUTE_TIME].value - 1)){
				if(gHDMI21AudioPrintLimitCnt[_p->port] < gHDMI21RxDevAudioControler[HDMI21__AUDIO_PRINT_LIMIT].value)_p->link_write(HDMI21_RX_PROC_CONFIG2,	HDMI21_RX_PROC_CONFIG2__MASK_ON);
			}
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value != 0)HDMI20_ADEF("HDMI[%d] Audio FIFO err mute cnt : %d", _p->port, _p->audioFifoErrMuteCnt);
		}

		/* [Check]Internal Mute */
		proc_status1 = _p->link_read((UINT32)HDMI21_RX_PROC_STATUS1);
		if(((proc_status1 & (UINT32)HDMI21_RX_PROC_STATUS1__AUD_MUTE_ST) == (UINT32)HDMI21_RX_PROC_STATUS1__AUD_MUTE_ST)\
			&& (_p->audioFifoErrMuteCnt == gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ERR_MUTE_TIME].value)\
			&& (_p->video.dvi == FALSE) && (_p->isHBRaudio == TRUE)\
			&& (_p->lowPowerMode != HDMI21_HAL_POWER_LOWPOWER)\
			&& (gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_ERR].value == (UINT32)0x0)){
			if(_p->isPC == FALSE) _p->audioFifoErrMuteCnt = (UINT32)0;
			if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
				if((_p->link_read(HDMI21_RX_CMU_STATUS) & HDMI21_RX_CMU_STATUS__AUDCLK_OFF_ST) == 0x0){
					_p->link_write((UINT32)HDMI21_RX_PROC_CONFIG2,	(UINT32)HDMI21_RX_PROC_CONFIG2__FMT_OFF);
					_p->top_write((UINT32)HDMI21_RX_ACR_PLL_MODE, (UINT32)0x10001 );
					HDMI21_HAL_Rx_Get_AudioACRParam(_p->port, TRUE);
					HDMI21_HAL_Rx_Get_AudioACRParam(_p->port, FALSE);
					_p->top_write((UINT32)HDMI21_RX_ACR_PLL_MODE, (UINT32)0x1 );
					if(((lx_chip_rev( ) >= LX_CHIP_REV( E60, B0)) && (lx_chip_rev( ) < LX_CHIP_REV( O22, A0))) \
					&& (((_p->scdcTmdsMode >= HDMI21_HAL_PHY_INITIATED_FRL_8G_4L) && ((_p->port == (UINT32)3) || (_p->port == (UINT32)4)))\
					|| ((_p->scdcTmdsMode >= HDMI21_HAL_PHY_INITIATED_FRL_10G_4L) && (_p->port == (UINT32)2) ))) {
						_p->top_write((UINT32)HDMI21_RX_ACR_PLL_MODE, (UINT32)0x10001 );
					}
					_p->link_write((UINT32)HDMI21_RX_AUD_FIFO_CONTROL,	((UINT32)HDMI21_RX_AUD_FIFO_CONTROL__FIFO_INIT | (UINT32)HDMI21_RX_AUD_FIFO_CONTROL__CLR_MIN | (UINT32)HDMI21_RX_AUD_FIFO_CONTROL__CLR_MAX));
					HDMI20_ADEF("HDMI[%d] Audio ACR Reset![proc_sts:0x%x, F_err:%d[%d], dvi:%d, HBR:%d, ignore:%d]\n", \
					_p->port, proc_status1, _p->audioFifoErrMuteCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ERR_MUTE_TIME].value,_p->isHBRaudio ,_p->video.dvi, gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_ERR].value);

				}else{
					HDMI20_ADEF("HDMI[%d] Audio FIFO reset Fail. \n", _p->port);
				}
			}else{
				if(_p->link_read((UINT32)HDMI21_RX_CMU_STATUS) & (UINT32)HDMI21_RX_CMU_STATUS__AUDCLK_LOCKED_ST){
					_p->link_write((UINT32)HDMI21_RX_PROC_CONFIG2,	(UINT32)HDMI21_RX_PROC_CONFIG2__FMT_OFF);
					_p->top_write((UINT32)HDMI21_RX_ACR_PLL_MODE, (UINT32)0x10001 );
					HDMI21_HAL_Rx_Get_AudioACRParam(_p->port, TRUE);
					HDMI21_HAL_Rx_Get_AudioACRParam(_p->port, FALSE);
					_p->top_write((UINT32)HDMI21_RX_ACR_PLL_MODE, (UINT32)0x1 );
					if(((lx_chip_rev( ) >= LX_CHIP_REV( E60, B0)) && (lx_chip_rev( ) < LX_CHIP_REV( O22, A0))) \
					&& (((_p->scdcTmdsMode >= HDMI21_HAL_PHY_INITIATED_FRL_8G_4L) && ((_p->port == (UINT32)3) || (_p->port == (UINT32)4)))\
					|| ((_p->scdcTmdsMode >= HDMI21_HAL_PHY_INITIATED_FRL_10G_4L) && (_p->port == (UINT32)2) ))) {
						_p->top_write((UINT32)HDMI21_RX_ACR_PLL_MODE, (UINT32)0x10001 );
					}
					_p->link_write((UINT32)HDMI21_RX_AUD_FIFO_CONTROL,	((UINT32)HDMI21_RX_AUD_FIFO_CONTROL__FIFO_INIT | (UINT32)HDMI21_RX_AUD_FIFO_CONTROL__CLR_MIN | (UINT32)HDMI21_RX_AUD_FIFO_CONTROL__CLR_MAX));
					HDMI20_ADEF("HDMI[%d] Audio ACR Reset![proc_sts:0x%x, F_err:%d[%d], dvi:%d, HBR:%d, ignore:%d]\n", \
					_p->port, proc_status1, _p->audioFifoErrMuteCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ERR_MUTE_TIME].value,_p->isHBRaudio ,_p->video.dvi, gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_ERR].value);

				}else{
					HDMI20_ADEF("HDMI[%d] Audio FIFO reset Fail. \n", _p->port);
				}
			}
		}

		/* [Force]ACR Reset */
		if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_ACR_RESET].value > 0)\
			&& (_p->video.dvi == 0)){
			_p->top_write(HDMI21_RX_ACR_PLL_MODE, 0x10001 );
			HDMI21_HAL_Rx_Get_AudioACRParam(_p->port, TRUE);
			HDMI21_HAL_Rx_Get_AudioACRParam(_p->port, FALSE);
			_p->top_write(HDMI21_RX_ACR_PLL_MODE, 0x1 );
			if(((lx_chip_rev( ) >= LX_CHIP_REV( E60, B0)) && (lx_chip_rev( ) < LX_CHIP_REV( O22, A0))) \
			&& (((_p->scdcTmdsMode >= HDMI21_HAL_PHY_INITIATED_FRL_8G_4L) && ((_p->port == 3) || (_p->port == 4)))\
			|| ((_p->scdcTmdsMode >= HDMI21_HAL_PHY_INITIATED_FRL_10G_4L) && (_p->port == 2) ))) {
				_p->top_write(HDMI21_RX_ACR_PLL_MODE, 0x10001 );
			}
			HDMI20_ADEF("HDMI[%d] Audio Force ACR reset!! \n", _p->port);
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_ACR_RESET].value = 0;
		}

		HDMI21_HAL_Rx_AudioInfoPrint(_p->port);
		HDMI21_HAL_Rx_AudioDebugIntialize(_p->port);

		ret = RET_OK;
	} while(0);

	return ret;

}

int HDMI21_HAL_Rx_Set_AudioMuteControl(UINT8 port, BOOLEAN mute)
{
	int ret = RET_ERROR;
	UINT32 proc_config0 = 0;
	int proc_status1 = 0;
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	HDMI21_HAL_RX_AUDIO_DATA *_a;

	do{
		/* [Check]Basic */
		if (port >= g_hdmi20_number_of_ports)	{
			HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
			break;
		}

		/* [Get]Handler */
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];
		_a = (HDMI21_HAL_RX_AUDIO_DATA *)&gHDMI21RxAudioHandler[port];

		//HDMI20_ADEF("DBG[%d] : Audio Mute Control[%s]. Caller[%pS]\n", _p->port, mute?"Set":"Clear", __builtin_return_address(0));

		/* [Set]Mute */
		proc_config0 = _p->link_read(HDMI21_RX_PROC_CONFIG0);
		if(mute == HDMI21_AUDIO_UNMUTE){
			proc_status1 = _p->link_read(HDMI21_RX_PROC_STATUS1);
			if((proc_status1 & HDMI21_RX_PROC_STATUS1__AUD_MUTE_ST) != HDMI21_RX_PROC_STATUS1__AUD_MUTE_ST){
				_a->procConfig0_muteControl = HDMI21_RX__EXT__PROC_CONFIG0__UNMUTE;
				_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
				HDMI21_Rx_Audio_Path_SetUnmute(_p->port);
			}
		}else if((mute == HDMI21_AUDIO_MUTE) && (gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_UNMUTE].value == 0x0)){
			_a->procConfig0_muteControl = HDMI21_RX__EXT__PROC_CONFIG0__MUTE;
			_p->link_write(HDMI21_RX_PROC_CONFIG0, (_a->procConfig0_chSpread |_a->procConfig0_chAlloc | _a->procConfig0_muteControl));
			HDMI21_Rx_Audio_Path_SetMute(_p->port);
		}

		ret = RET_OK;
	}while(0);
	return ret;
}

int HDMI21_HAL_Rx_Set_AudioReset(UINT8 port)
{
	UINT32 ret = RET_ERROR;
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	do{
		/* [Check]Basic */
		if (port >= g_hdmi20_number_of_ports)	{
			HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
			break;
		}

		/* [Get]Handler */
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];

		/* [Set]Mute */
		HDMI21_HAL_Rx_Set_AudioMuteControl(port, HDMI21_AUDIO_MUTE);
		_p->isAudioMute = HDMI21_AUDIO_MUTE;

		/* [Init]Count */
		_p->audioStandByCnt = 0;
		_p->audioStableCnt = 0;
		_p->audioChMapStandByCnt = 0;
		_p->audioForceMuteCnt = 0;
		gHDMI21AudioFIFOAdnormalCnt[_p->port] = 0;
		gHDMI21AudioChannelAbnormalCnt[_p->port] = 0;

		/* [Set]FIFO Reset */
		ret = HDMI21_HAL_Rx_Set_AudioFIFOReset(_p->port);

		return RET_OK;
	}while(0);
	return ret;
}

int HDMI21_HAL_Rx_Set_AudioChange(UINT8 port)
{
	int ret = RET_ERROR;
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	do{
		/* [Check]Basic */
		if (port >= g_hdmi20_number_of_ports) {
			HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
			break;
		}

		/* [Get]Handler */
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];

		_p->audioStableCnt = 0;
		_p->audioChMapStandByCnt = 0;
		_p->audioForceMuteCnt = 0;
		_p->audioChMapCnt = 0;
		HDMI21_HAL_Rx_Set_AudioMuteControl(_p->port, HDMI21_AUDIO_MUTE);
		_p->isAudioMute = HDMI21_AUDIO_MUTE;

		return RET_OK;
	}while(0);
	return ret;
}


int HDMI21_HAL_Rx_Set_AudioFIFOReset(UINT8 port){
	int ret = RET_ERROR;
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	do{
		/* [Check]Basic */
		if (port >= g_hdmi20_number_of_ports)	{
			HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
			break;
		}

		/* [Get]Handler */
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];
#if 0
		if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
			if((_p->link_read(HDMI21_RX_CMU_STATUS) & HDMI21_RX_CMU_STATUS__AUDCLK_OFF_ST) == 0x0){
				/* [Set]FIFO Register */
				//_p->link_write(HDMI21_RX_AUD_FIFO_TH_PASS,	HDMI21_RX_AUD_FIFO_TH_PASS__VALUE);
				_p->link_write(HDMI21_RX_AUD_FIFO_TH,		(HDMI21_RX_AUD_FIFO_TH_LOW | HDMI21_RX_AUD_FIFO_TH_HIGH));
				_p->link_write(HDMI21_RX_AUD_FIFO_MUTE_TH,	(HDMI21_RX_AUD_FIFO_MUTE_TH_LOW | HDMI21_RX_AUD_FIFO_MUTE_TH_HIGH));
				_p->link_write(HDMI21_RX_AUD_FIFO_CONFIG,	HDMI21_RX_AUD_FIFO_CONFIG__FILL_RESTART_OFF);
				_p->link_write(HDMI21_RX_AUD_FIFO_CONTROL,	(HDMI21_RX_AUD_FIFO_CONTROL__FIFO_INIT | HDMI21_RX_AUD_FIFO_CONTROL__CLR_MIN | HDMI21_RX_AUD_FIFO_CONTROL__CLR_MAX));
			}else{
				if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG].value != 0) HDMI20_ADEF("HDMI[%d] Audio FIFO reset Fail. \n", _p->port);
			}
		}else{
			if(_p->link_read(HDMI21_RX_CMU_STATUS) & (UINT32)HDMI21_RX_CMU_STATUS__AUDCLK_LOCKED_ST){
				/* [Set]FIFO Register */
				//_p->link_write(HDMI21_RX_AUD_FIFO_TH_PASS,	HDMI21_RX_AUD_FIFO_TH_PASS__VALUE);
				_p->link_write(HDMI21_RX_AUD_FIFO_TH,		(HDMI21_RX_AUD_FIFO_TH_LOW | HDMI21_RX_AUD_FIFO_TH_HIGH));
				_p->link_write(HDMI21_RX_AUD_FIFO_MUTE_TH,	(HDMI21_RX_AUD_FIFO_MUTE_TH_LOW | HDMI21_RX_AUD_FIFO_MUTE_TH_HIGH));
				_p->link_write(HDMI21_RX_AUD_FIFO_CONFIG,	HDMI21_RX_AUD_FIFO_CONFIG__FILL_RESTART_OFF);
				_p->link_write(HDMI21_RX_AUD_FIFO_CONTROL,	(HDMI21_RX_AUD_FIFO_CONTROL__FIFO_INIT | HDMI21_RX_AUD_FIFO_CONTROL__CLR_MIN | HDMI21_RX_AUD_FIFO_CONTROL__CLR_MAX));
			}else{
				if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG].value != 0) HDMI20_ADEF("HDMI[%d] Audio FIFO reset Fail. \n", _p->port);
			}
		}
#endif
#if 1
		if(_p->link_read(HDMI21_RX_CMU_STATUS) & (UINT32)HDMI21_RX_CMU_STATUS__AUDCLK_LOCKED_ST){
			/* [Set]FIFO Register */
			//_p->link_write(HDMI21_RX_AUD_FIFO_TH_PASS,	HDMI21_RX_AUD_FIFO_TH_PASS__VALUE);
			_p->link_write(HDMI21_RX_AUD_FIFO_TH,		((UINT32)HDMI21_RX_AUD_FIFO_TH_LOW | (UINT32)HDMI21_RX_AUD_FIFO_TH_HIGH));
			_p->link_write(HDMI21_RX_AUD_FIFO_MUTE_TH,	((UINT32)HDMI21_RX_AUD_FIFO_MUTE_TH_LOW | (UINT32)HDMI21_RX_AUD_FIFO_MUTE_TH_HIGH));
			_p->link_write(HDMI21_RX_AUD_FIFO_CONFIG,	(UINT32)HDMI21_RX_AUD_FIFO_CONFIG__FILL_RESTART_OFF);
			_p->link_write(HDMI21_RX_AUD_FIFO_CONTROL,	((UINT32)HDMI21_RX_AUD_FIFO_CONTROL__FIFO_INIT | (UINT32)HDMI21_RX_AUD_FIFO_CONTROL__CLR_MIN | (UINT32)HDMI21_RX_AUD_FIFO_CONTROL__CLR_MAX));
		}
		else{
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG].value != 0) HDMI20_ADEF("HDMI[%d] Audio FIFO reset Fail. \n", _p->port);
		}
#endif
		return RET_OK;
	}while(0);
	return ret;
}

int HDMI21_HAL_Rx_Get_AudioFreqFromTMDSClock(UINT8 port, unsigned int *samplingFreq)
{
	int ret = RET_ERROR;
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	HDMI21_HAL_PHY_INITIATED_MODE_T scdcmode;
	UINT64		ui64TmdsClock = 0;			//< HDMI measured clock value of TMDS clock
	UINT64		ui64AcrN = 0;				//< HDMI ACR N value
	UINT64		ui64AcrCts = 0; 			//< HDMI ACR CTS value
	UINT64		ui64TmdsSamplingFreq = 0;	//< HDMI sampling frequency in source device from TMDS clock

	do{
		/* [Check]Basic */
		if (port >= g_hdmi20_number_of_ports) {
			HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
			break;
		}

		/* [Get]Handler */
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];

		/* [Get]SCDC Mode */
		scdcmode = _p->scdcTmdsMode;

		/* [Get]Clock */
		if(scdcmode == HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) {
			ui64TmdsClock = 166666 * 1000;
		}else if((scdcmode == HDMI21_HAL_PHY_INITIATED_FRL_6G_3L) || (scdcmode == HDMI21_HAL_PHY_INITIATED_FRL_6G_4L)) {
			ui64TmdsClock = 333333 * 1000;
		}else if(scdcmode == HDMI21_HAL_PHY_INITIATED_FRL_8G_4L) {
			ui64TmdsClock = 444444 * 1000;
		}else if(scdcmode == HDMI21_HAL_PHY_INITIATED_FRL_10G_4L) {
			ui64TmdsClock = 555556 * 1000;
		}else if(scdcmode == HDMI21_HAL_PHY_INITIATED_FRL_12G_4L) {
			ui64TmdsClock = 666667 * 1000;
		}else if((scdcmode == HDMI21_HAL_PHY_INITIATED_3G) || (scdcmode == HDMI21_HAL_PHY_INITIATED_6G)){
			//Get measured frequency value of TMDS clock.
			ui64TmdsClock = (UINT64)(_p->real_tmds_clk) * 1000;
		}

		//Get ACR N H/W value.
		ui64AcrN = _p->audioInfo.acr_n;		//20 bits

		//Get ACR CTS H/W value.
		ui64AcrCts = _p->audioInfo.acr_cts;	//20 bits

		//Compute a sampling frequency from TMDS clock
		ui64TmdsSamplingFreq = ui64AcrN * ui64TmdsClock;

		//Check divide by zero value.
		if((ui64TmdsSamplingFreq > 0)&&(ui64AcrCts > 0)){
			do_div(ui64TmdsSamplingFreq, ui64AcrCts * 128);
		}

		if (ui64TmdsSamplingFreq == 0){
			*samplingFreq = LX_HDMI_SAMPLING_FREQ_NONE;
		}else if (ui64TmdsSamplingFreq < 22983){
			*samplingFreq = LX_HDMI_SAMPLING_FREQ_22_05KHZ;	//  22.05 kHz(not supported)
		}else if (ui64TmdsSamplingFreq < 30000){
			*samplingFreq = LX_HDMI_SAMPLING_FREQ_24_KHZ;	//  24 kHz(not supported)
		}else if (ui64TmdsSamplingFreq < 33800){
			*samplingFreq = LX_HDMI_SAMPLING_FREQ_32_KHZ;	//  32 kHz
		}else if (ui64TmdsSamplingFreq < 45965){
			*samplingFreq = LX_HDMI_SAMPLING_FREQ_44_1KHZ;	//  44.1 kHz
		}else if (ui64TmdsSamplingFreq < 67000){
			*samplingFreq = LX_HDMI_SAMPLING_FREQ_48_KHZ;	//  48 kHz
		}else if (ui64TmdsSamplingFreq < 91935){
			*samplingFreq = LX_HDMI_SAMPLING_FREQ_88_2KHZ;	//  88.2 kHz
		}else if (ui64TmdsSamplingFreq < 135000){
			*samplingFreq = LX_HDMI_SAMPLING_FREQ_96_KHZ;	//  96 kHz
		}else if (ui64TmdsSamplingFreq < 183870){
			*samplingFreq = LX_HDMI_SAMPLING_FREQ_176_4KHZ;	//  176.4 kHz
		}else if (ui64TmdsSamplingFreq < 210000){
			*samplingFreq = LX_HDMI_SAMPLING_FREQ_192_KHZ;	//  192 kHz
		}else{
			*samplingFreq = LX_HDMI_SAMPLING_FREQ_768_KHZ;	//  768 kHz(not supported)
		}

		ret = RET_OK;
	}while(0);
	return ret;
}

int HDMI21_HAL_Rx_Set_AudioEnable(UINT8 port, BOOLEAN enable){
	int ret = RET_ERROR;
	UINT32 global_Swenable;
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	do{
		/* [Check]Basic */
		if (port >= g_hdmi20_number_of_ports) {
			HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
			break;
		}

		/* [Get]Handler */
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];

		global_Swenable = _p->link_read(HDMI21_RX_GLOBAL_ENABLE);
		if(enable){
#if 1
			/* [Init]Count */
			_p->audioChMapCnt = 0;
			_p->audioStableCnt = 0;
			_p->audioChMapStandByCnt = 0;
			_p->audioAcrResetCnt = 0;
			_p->audioAcrErrorCnt = 0;
			_p->isAudioMute = HDMI21_AUDIO_MUTE;

			/* [Init]Info */
			_p->audioInfo.audioType = LX_HDMI_AUDIO_DEFAULT;
			_p->audioInfo.samplingFreq = LX_HDMI_SAMPLING_FREQ_NONE;
			_p->audioInfo.countOfChannel = 2;
			_p->audioInfo.stream = LX_HDMI_AUDIO_STREAM_NONE;
			gHDMI21AcrClockSave[_p->port] = 0;

			_p->top_write(HDMI21_RX_ACR_PLL_MODE, 0x10001 );
			HDMI21_HAL_Rx_Get_AudioACRParam(_p->port, 1);
			HDMI21_HAL_Rx_Get_AudioACRParam(_p->port, 0);
			_p->top_write(HDMI21_RX_ACR_PLL_MODE, 0x1 );
			if(((lx_chip_rev( ) >= LX_CHIP_REV( E60, B0)) && (lx_chip_rev( ) < LX_CHIP_REV( O22, A0))) \
			&& (((_p->scdcTmdsMode >= HDMI21_HAL_PHY_INITIATED_FRL_8G_4L) && ((_p->port == 3) || (_p->port == 4)))\
			|| ((_p->scdcTmdsMode >= HDMI21_HAL_PHY_INITIATED_FRL_10G_4L) && (_p->port == 2) ))) {
				_p->top_write(HDMI21_RX_ACR_PLL_MODE, 0x10001 );
			}
#endif
			_p->link_write(HDMI21_RX_GLOBAL_ENABLE, global_Swenable | HDMI21_RX_GLOBAL_ENABLE__AUDIO_ENABLE);
			_p->audio_state = HDMI21__AUDIO_STATE__2__ENABLE__WAIT_CLK_OFF_CHG;
		}else{
			_p->link_write(HDMI21_RX_GLOBAL_ENABLE, global_Swenable & HDMI21_RX_GLOBAL_ENABLE__AUDIO_DISABLE);
			_p->top_write(HDMI21_RX_ACR_PLL_MODE, 0x10001 );
			HDMI21_HAL_Rx_Get_AudioACRParam(_p->port, 1);
			HDMI21_HAL_Rx_Get_AudioACRParam(_p->port, 0);
			_p->top_write(HDMI21_RX_ACR_PLL_MODE, 0x1 );
			if(((lx_chip_rev( ) >= LX_CHIP_REV( E60, B0)) && (lx_chip_rev( ) < LX_CHIP_REV( O22, A0))) \
			&& (((_p->scdcTmdsMode >= HDMI21_HAL_PHY_INITIATED_FRL_8G_4L) && ((_p->port == 3) || (_p->port == 4)))\
			|| ((_p->scdcTmdsMode >= HDMI21_HAL_PHY_INITIATED_FRL_10G_4L) && (_p->port == 2) ))) {
				_p->top_write(HDMI21_RX_ACR_PLL_MODE, 0x10001 );
			}

			_p->audio_state = HDMI21__AUDIO_STATE__1__DISABLE__WAIT_AUDIF_RCV;
			gHDMI21AudioAdnormalCnt[_p->port] = 0;
			gHDMI21AudioFIFOAdnormalCnt[_p->port] = 0;
			gHDMI21AudioChannelAbnormalCnt[_p->port] = 0;
		}

		return RET_OK;
	}while(0);
	return ret;
}

int HDMI21_HAL_Rx_Set_AudioState(UINT8 port){
	int ret = RET_ERROR;
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	do{
		/* [Check]Basic */
		if (port >= g_hdmi20_number_of_ports) {
			HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
			break;
		}

		/* [Get]Handler */
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];

		if((_p->audio_state == HDMI21__AUDIO_STATE__1__DISABLE__WAIT_AUDIF_RCV) && (lx_chip_rev( ) >= LX_CHIP_REV( O20, A0))){
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_STATE].value != 0)HDMI20_ADEF("HDMI[%d] Audio state %d->%d(o20 A0)!!!kkkkkk\n", _p->port, HDMI21__AUDIO_STATE__1__DISABLE__WAIT_AUDIF_RCV, HDMI21__AUDIO_STATE__2__ENABLE__WAIT_CLK_OFF_CHG);
			HDMI21_HAL_Rx_Set_AudioEnable(_p->port, 1);
		}
		return RET_OK;
	}while(0);
	return ret;
}

int HDMI21_HAL_Rx_AudioInfoPrint(UINT8 port)
{
	int ret = RET_ERROR;
	UINT32 i,j;
	UINT32 addr;
	UINT32 fifo_status;
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	HDMI21_HAL_RX_AUDIO_DATA *_a;

	do{
		/* [Check]Basic */
		if (port >= g_hdmi20_number_of_ports) {
			HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
			break;
		}

		/* [Get]Handler */
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];
		_a = (HDMI21_HAL_RX_AUDIO_DATA *)&gHDMI21RxAudioHandler[port];

		if(_p->audioDbgPrintCnt == 0){

			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_UNMUTE].value != 0x0){
				HDMI21_HAL_Rx_Set_AudioMuteControl(port, HDMI21_AUDIO_UNMUTE);
				HDMI20_AUDIO("HDMI[%d] Audio Force Unmute !\n", _p->port);
				_p->isAudioMute = HDMI21_AUDIO_UNMUTE;
				_p->isAudioMuteControl = FALSE;
			}
			
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_DISABLE].value > 0){
				HDMI20_ADEF("HDMI[%d] Audio Force Disable!\n",port);
				gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_DISABLE].value--;
			}

			//Input data sample
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_DATA].value > 0){
				HDMI20_ADEF("HDMI[%d] Audio Data : [0x%08x] [0x%08x] [0x%08x] [0x%08x]!\n",\
				port, _p->top_read(0xFA0) , _p->top_read(0xFA4), _p->top_read(0xFA8), _p->top_read(0xFAC));
				gHDMI21RxDevAudioControler[HDMI21__AUDIO_DATA].value--;
			}
			//ACR N/CTS
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_N_CTS].value > 0){
				HDMI20_ADEF("HDMI[%d] Audio ACR : N[0x%08x], CTS:[0x%08x], TMDS[0x%08llx]\n", _p->port, _p->audioInfo.acr_n, _p->audioInfo.acr_cts, _p->real_tmds_clk);
				gHDMI21RxDevAudioControler[HDMI21__AUDIO_N_CTS].value--;
			}

			//Info
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_INFO].value > 0){
				HDMI20_ADEF("HDMI[%d] Audio INFO : Type[%d], Fs[%d], Channel[%d], Stream[%d], Word Length[%d]\n",\
				port, _p->audioInfo.audioType, _p->audioInfo.samplingFreq, _p->audioInfo.countOfChannel, _p->audioInfo.stream, _p->audioInfo.wordLength);
				gHDMI21RxDevAudioControler[HDMI21__AUDIO_INFO].value--;
			}

			//Count
			if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
				if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT].value > (UINT32)0){
					HDMI20_ADEF("HDMI[%d] Audio CNT : StandBy[%d/%d], Stable[%d/%d], FifoErr[%d/%d], ChMapStandBy[%d/%d], ChMap[%d/%d], IrqFifoErr[%d/%d], ForceMute[%d/%d], AcrReset[%d/%d]\n",\
					port, _p->audioStandByCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_STANDBY_TIME].value,\
					_p->audioStableCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME_O22].value,\
					_p->audioFifoErrMuteCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ERR_MUTE_TIME].value,\
					_p->audioChMapStandByCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_CH_MAP_STANDBY_TIME].value,\
					_p->audioChMapCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_CH_MAP_MAX].value,\
					_p->audioIrqFifoErrCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_IRQ_FIFO_ERR_MAX].value,\
					_p->audioForceMuteCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_MUTE_TIME_O22].value,\
					_p->audioAcrResetCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_ACR_RESET_TIME].value);
					gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT].value--;
				}
			}else{
				if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT].value > (UINT32)0){
					HDMI20_ADEF("HDMI[%d] Audio CNT : StandBy[%d/%d], Stable[%d/%d], FifoErr[%d/%d], ChMapStandBy[%d/%d], ChMap[%d/%d], IrqFifoErr[%d/%d], ForceMute[%d/%d], AcrReset[%d/%d]\n",\
					port, _p->audioStandByCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_STANDBY_TIME].value,\
					_p->audioStableCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME].value,\
					_p->audioFifoErrMuteCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ERR_MUTE_TIME].value,\
					_p->audioChMapStandByCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_CH_MAP_STANDBY_TIME].value,\
					_p->audioChMapCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_CH_MAP_MAX].value,\
					_p->audioIrqFifoErrCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_IRQ_FIFO_ERR_MAX].value,\
					_p->audioForceMuteCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_MUTE_TIME].value,\
					_p->audioAcrResetCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_ACR_RESET_TIME].value);
					gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT].value--;
				}
			}

			//FIFO fill status
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO].value > 0){
				fifo_status = _p->link_read(HDMI21_RX_AUD_FIFO_STS2__FILLSTS1);
				HDMI20_ADEF("HDMI[%d] Audio FIFO : Fill[0x%04x], Status[0x%x]\n",\
				port, (fifo_status & 0xFFFF), fifo_status);
				gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO].value--;
			}

			//Mute status
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_MUTE].value > 0){
				HDMI20_ADEF("HDMI[%d] Audio MUTE : Sts[%d], Reg[0x%08x]\n",\
				port, _p->isAudioMute, _p->link_read(HDMI21_RX_PROC_CONFIG0));
				gHDMI21RxDevAudioControler[HDMI21__AUDIO_MUTE].value--;
			}

			//HBR status
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_HBR].value > 0){
				HDMI20_ADEF("HDMI[%d] Audio HBR : Sts[%d]", _p->port, _p->isHBRaudio);
				gHDMI21RxDevAudioControler[HDMI21__AUDIO_HBR].value--;
			}

			//PC connect status
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_PC].value > 0){
				HDMI20_ADEF("HDMI[%d] Audio PC:Sts[%d], SPD29:0x%02x \n", _p->port, _p->isPC, _p->dataPacket[HDMI21_DISLAND_DATA__SPD][28]);
				gHDMI21RxDevAudioControler[HDMI21__AUDIO_PC].value--;
			}

			//Clock
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CLOCK].value > 0){
				HDMI20_ADEF("HDMI[%d] Audio Clock : \n", _p->port);
				HDMI20_ADEF("Audio ACR : N[%08d], CTS:[%08d], TMDS[%08llu]\n", _p->audioInfo.acr_n, _p->audioInfo.acr_cts, _p->real_tmds_clk);
				HDMI20_ADEF("====== Top ==========");
				HDMI20_ADEF("[0x%04x]	AUD_MEAS		: [%08d]", HDMI21_RX_AD_AUD_MEAS		, _p->top_read(HDMI21_RX_AD_AUD_MEAS) &0xFFFF);
				HDMI20_ADEF("[0x%04x]	TMDS_CLK_MEAS		: [%08d]", HDMI21_RX_AD_TMDS_CLK_MEAS	, _p->top_read(HDMI21_RX_AD_TMDS_CLK_MEAS) &0xFFFF);
				HDMI20_ADEF("[0x%04x]	LINK_CLK_MEAS		: [%08d]", HDMI21_RX_AD_LINK_CLK_MEAS	, _p->top_read(HDMI21_RX_AD_LINK_CLK_MEAS) &0xFFFF);
				HDMI20_ADEF("[0x%04x]	FRL_CLK_MEAS		: [%08d]", HDMI21_RX_AD_FRL_CLK_MEAS	, _p->top_read(HDMI21_RX_AD_FRL_CLK_MEAS) &0xFFFF);
				HDMI20_ADEF("====== Link ==========");
				HDMI20_ADEF("[0x%04x]	AUDCLK_FREQ		: [%08d]", HDMI21_RX_CMU_AUDCLK_FREQ		, _p->link_read(HDMI21_RX_CMU_AUDCLK_FREQ) &0xFFFFF);
				HDMI20_ADEF("[0x%04x]	TMDSQPCLK_FREQ		: [%08d]", HDMI21_RX_CMU_TMDSQPCLK_FREQ	, _p->link_read(HDMI21_RX_CMU_TMDSQPCLK_FREQ) &0xFFFFF);
				gHDMI21RxDevAudioControler[HDMI21__AUDIO_CLOCK].value--;
			}

			//Channel status data
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CHANNEL_STATUS].value > 0){
				HDMI20_ADEF("HDMI[%d] Top Reg, \n", _p->port);
				HDMI20_ADEF("HDMI[%d] Byte[0] -> 0x%x : 0x%x \n", _p->port,HDMI21_RX_AD_MAIN_AUD_INFO_BYTE0,_p->top_read(HDMI21_RX_AD_MAIN_AUD_INFO_BYTE0));
				HDMI20_ADEF("HDMI[%d] Byte[1] -> 0x%x : 0x%x \n", _p->port,HDMI21_RX_AD_MAIN_AUD_INFO_BYTE1,_p->top_read(HDMI21_RX_AD_MAIN_AUD_INFO_BYTE1));
				HDMI20_ADEF("HDMI[%d] Byte[2] -> 0x%x : 0x%x \n", _p->port,HDMI21_RX_AD_MAIN_AUD_INFO_BYTE2,_p->top_read(HDMI21_RX_AD_MAIN_AUD_INFO_BYTE2));
				HDMI20_ADEF("HDMI[%d] Byte[3] -> 0x%x : 0x%x \n", _p->port,HDMI21_RX_AD_MAIN_AUD_INFO_BYTE3,_p->top_read(HDMI21_RX_AD_MAIN_AUD_INFO_BYTE3));
				addr = (UINT32)HDMI21_RX_PROC_CHSTAT_SP0_L1;
				HDMI20_ADEF("HDMI[%d] Link Reg, \n", _p->port);
				for(i=0; i<8; i++){
					for(j=0; j<6; j++){
						HDMI20_ADEF("HDMI[%d] Audio Channel[%d] Byte[%02d] -> 0x%04x : 0x%08x \n", _p->port, i, j*4, addr, _p->link_read(addr));
						addr += 4;
					}
				}
				gHDMI21RxDevAudioControler[HDMI21__AUDIO_CHANNEL_STATUS].value = 0;
			}

			//Read Register
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_READ_TOP_REG].value > 0){
				HDMI20_ADEF("HDMI[%d] Audio TOP REG : address[0x%04x], value[0x%08x]", _p->port, gHDMI21RxDevAudioControler[HDMI21__AUDIO_READ_TOP_REG].value, _p->top_read(gHDMI21RxDevAudioControler[HDMI21__AUDIO_READ_TOP_REG].value));
				if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_REG_PRINT_REPEAT].value > 0) gHDMI21RxDevAudioControler[HDMI21__AUDIO_READ_TOP_REG].value = 0;
			}
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_READ_LINK_REG].value > 0){
				HDMI20_ADEF("HDMI[%d] Audio CTRL REG : address[0x%04x], value[0x%08x]", _p->port, gHDMI21RxDevAudioControler[HDMI21__AUDIO_READ_LINK_REG].value, _p->link_read(gHDMI21RxDevAudioControler[HDMI21__AUDIO_READ_LINK_REG].value));
				if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_REG_PRINT_REPEAT].value > 0) gHDMI21RxDevAudioControler[HDMI21__AUDIO_READ_LINK_REG].value = 0;
			}

			_p->audioDbgPrintCnt = gHDMI21RxDevAudioControler[HDMI21__AUDIO_INFORMATION].value;
		}else if(_p->audioDbgPrintCnt > 0){
			_p->audioDbgPrintCnt--;
		}

		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_STATE].value == 7){
			HDMI20_ADEF("HDMI[%d] Audio State : %d\n", _p->port, _p->audio_state);
		}

		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_PROC_CONFIG0_SETTING].value != 0){
			HDMI20_ADEF("HDMI[%d] Audio Proc config0 setting value(0x%x) : \n", _p->port, (_p->link_read(HDMI21_RX_PROC_CONFIG0)));
			HDMI20_ADEF("HDMI[%d] ch alloc(0x%x), ch spread(0x%x), mute(0x%x), \n", _p->port, _a->procConfig0_chAlloc, _a->procConfig0_chSpread, _a->procConfig0_muteControl);
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_PROC_CONFIG0_SETTING].value--;
		}

		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_STATE_INIT].value != 0){
			HDMI20_ADEF("HDMI[%d] Audio StateInit : %d\n", _p->port, _p->audio_state);
			HDMI21_HAL_Rx_Set_AudioEnable(_p->port, 0);
			_p->audio_state = HDMI21__AUDIO_STATE__1__DISABLE__WAIT_AUDIF_RCV;
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_STATE_INIT].value = 0;
		}

		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_TEST].value != 0){
			HDMI20_ADEF("HDMI[%d] Audio Test\n", _p->port);
			HDMI21_AUDIO_REG_WR(0xC331A078, 0x2);
			HDMI21_AUDIO_REG_WR(0xC331A078, 0x3);
			HDMI21_AUDIO_REG_WR(0xC331A078, 0x2);
			HDMI21_AUDIO_REG_WR(0xC331A078, 0x3);
			HDMI21_AUDIO_REG_WR(0xC331A078, 0x2);
			HDMI21_AUDIO_REG_WR(0xC331A078, 0x3);
			HDMI21_AUDIO_REG_WR(0xC331A078, 0x2);
			HDMI21_AUDIO_REG_WR(0xC331A078, 0x3);
			HDMI21_AUDIO_REG_WR(0xC331A078, 0x2);
			HDMI21_AUDIO_REG_WR(0xC331A078, 0x3);
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_TEST].value = 0;
		}

		//Reg
		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_REG].value != 0){
			HDMI20_ADEF("HDMI[%d] Audio REG : \n", _p->port);
			HDMI20_ADEF("[0x%04x]	ACR_CLK_DIVIDER 	: [0x%08x]", HDMI21_RX_ACR_CLK_DIVIDER, _p->top_read(HDMI21_RX_ACR_CLK_DIVIDER));
			HDMI20_ADEF("[0x%04x]	ACR_CLK_N_FS		: [0x%08x]", HDMI21_RX_ACR_CLK_N_FS, _p->top_read(HDMI21_RX_ACR_CLK_N_FS));
			HDMI20_ADEF("[0x%04x]	AUD_FIFO_TH		: [0x%08x]", HDMI21_RX_AUD_FIFO_TH, _p->link_read(HDMI21_RX_AUD_FIFO_TH));
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_REG].value = 0;
		}

		//Commit history
		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 0x9999) {
			HDMI20_ADEF("180423 : [Mod] M16P3 AUDIO_REG_ADDRESS setting.\n");
			HDMI20_ADEF("180510 : [Mod] Increase HDMI21__AUD_STABLE_TIME(0xf -> 0x14).\n");
			HDMI20_ADEF("180607 : [Mod] Audio info Pc error SW workaround.\n");
			HDMI20_ADEF("180618 : [Mod] Audio info Pc change interrupt.\n");
			HDMI20_ADEF("180802 : [Mod] Audio SPDIF change IRQ.\n");
			HDMI20_ADEF("180802 : [Add] Audio ACR reset for FIFO recovery.\n");
			HDMI20_ADEF("180807 : [Add] Pd change interrup disable.\n");
			HDMI20_ADEF("180810 : [Add] FIFO adjust enable.\n");
			HDMI20_ADEF("180816 : [Add] Audio configuration for HDMI Link reset.\n");
			HDMI20_ADEF("180918 : [Mod] Delete layout conditional statement in channel mapping.\n");
			HDMI20_ADEF("180918 : [Mod] ACR reset cnt init.\n");
			HDMI20_ADEF("180918 : [Add] Default 8ch setting in channel mapping.\n");
			HDMI20_ADEF("190226 : [Mod] DVI mode.\n");
			HDMI20_ADEF("190227 : [Add] Unknown Audio type.\n");
			HDMI20_ADEF("190409 : [Rev] Unknown Audio type.\n");
			HDMI20_ADEF("190415 : [Mod] Video stable check change.\n");
			HDMI20_ADEF("190424 : [Add] HDMI2.1 audio release 1st.\n");
			HDMI20_ADEF("190510 : [Add] HDMI2.1 audio release 7th.\n");
			HDMI20_ADEF("190621 : [Add] FIFO restart for HBR Mute.\n");
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value = 0;
		}
	}while(0);
	return ret;
}

int HDMI21_HAL_Rx_AudioDebugIntialize(UINT8 port)
{
	UINT32 ret = RET_ERROR;

	do{
		/* [Check]Basic */
		if (port >= g_hdmi20_number_of_ports) {
			HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
			break;
		}

		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_ALL_DEBUG_INIT].value != 0x0){
			HDMI20_ADEF("All Audio Debug Initialize!!!\n");
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG_INIT].value = 0x1;
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_COUNT_INIT].value = 0x1;
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_CONTROL_INIT].value = 0x1;
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_INFORMATION_INIT].value = 0x1;

			gHDMI21RxDevAudioControler[HDMI21__AUDIO_ALL_DEBUG_INIT].value = 0x0;
		}

		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG_INIT].value != 0x0){
			HDMI20_ADEF("All debug print initialize!\n");
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value = 0x0;
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value = 0x0;
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_IRQ_DBG].value = 0x0;
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value = 0x0;

			gHDMI21RxDevAudioControler[HDMI21__AUDIO_DEBUG_INIT].value = 0x0;
		}

		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_COUNT_INIT].value != 0x0){
			HDMI20_ADEF("All count value initialize!\n");
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_STANDBY_TIME].value = 0x3;
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME].value = 0xA;
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE].value = 0x9;
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ERR_MUTE_TIME].value = 0x6;
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_CH_MAP_STANDBY_TIME].value = 0xA;
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_CH_MAP_MAX].value = 0x3;
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_IRQ_FIFO_ERR_MAX].value = 0x5;
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_MUTE_TIME].value = 0xF;
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_ACR_RESET_TIME].value = 0x1;

			gHDMI21RxDevAudioControler[HDMI21__AUDIO_COUNT_INIT].value = 0x0;
		}

		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CONTROL_INIT].value != 0x0){
			HDMI20_ADEF("All control value initialize!\n");
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_IGNORE_ERR].value = 0x0;
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_UNMUTE].value = 0x0;
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_REG_PRINT_REPEAT].value = 0x1;

			gHDMI21RxDevAudioControler[HDMI21__AUDIO_CONTROL_INIT].value = 0x0;
		}

		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_INFORMATION_INIT].value != 0x0){
			HDMI20_ADEF("All information print initialize!\n");
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_DATA].value = 0x0;
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_N_CTS].value = 0x0;
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_INFO].value = 0x0;
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT].value = 0x0;
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO].value = 0x0;
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_MUTE].value = 0x0;
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_REG].value = 0x0;

			gHDMI21RxDevAudioControler[HDMI21__AUDIO_INFORMATION_INIT].value = 0x0;
		}

		ret = RET_OK;
	}while(0);
	return ret;
}

/* SEETV */
int KDRV_HDMI21_HAL_Rx_GetAudioInfo(UINT8 port, LX_HDMI_AUDIO_INFO_T *pHdmiAudioInfo, int size)
{
	int ret = RET_ERROR;
	LX_HDMI_AUDIO_INFO_T	data;
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	do{
		/* [Check]Basic */
		if (port >= g_hdmi20_number_of_ports) {
			HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
			return RET_ERROR;
		}
		if(pHdmiAudioInfo == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}
		if(size != sizeof(LX_HDMI_AUDIO_INFO_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI_AUDIO_INFO_T), size);
			break;
		}

		/* [Get]Handler */
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];

		/* [Get]Info */
		if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
			if((_p->video.dvi == FALSE) && ((_p->audio_change == TRUE) || (HDMI21_VPROC_Rx_Get_IsMute(_p)) || (_p->audio_change == TRUE) \
				|| (_p->audioStandByCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_STANDBY_TIME].value)\
				|| (_p->audioFifoErrMuteCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ERR_MUTE_TIME].value)\
				|| (_p->audioStableCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME_O22].value))) {
				data.audioType	= LX_HDMI_AUDIO_NO_AUDIO;
			} else {
				data.audioType	= _p->audioInfo.audioType;
			}
		}else{
			if((_p->video.dvi == FALSE) && ((_p->audio_change == TRUE) || (HDMI21_VPROC_Rx_Get_IsMute(_p)) || (_p->audio_change == TRUE) \
				|| (_p->audioStandByCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_STANDBY_TIME].value)\
				|| (_p->audioFifoErrMuteCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ERR_MUTE_TIME].value)\
				|| (_p->audioStableCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME].value))) {
				data.audioType	= LX_HDMI_AUDIO_NO_AUDIO;
			} else {
				data.audioType	= _p->audioInfo.audioType;
			}
		}
		data.samplingFreq =  _p->audioInfo.samplingFreq;
		data.countOfChannel = _p->audioInfo.countOfChannel;
		data.stream = _p->audioInfo.stream;


		/* [Debug]Force Info */
		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_TYPE].value != 0x0){
			data.audioType = gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_TYPE].value;
		}
		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_FS].value != 0x0){
			data.samplingFreq = gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_FS].value;
		}
		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_CHANNEL].value != 0x0){
			data.countOfChannel= gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_CHANNEL].value;
		}
		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_STREAM].value != 0x0){
			data.stream= gHDMI21RxDevAudioControler[HDMI21__AUDIO_FORCE_STREAM].value;
		}

		memcpy((LX_HDMI_AUDIO_INFO_T *)pHdmiAudioInfo, &data, sizeof(LX_HDMI_AUDIO_INFO_T));

		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_USR_INFO].value > 0){
			HDMI20_ADEF("HDMI[%d] Audio audiotype:%d, samplingFreq:%d, countOfChannel:%d(%d), word length(%d)\n", _p->port, data.audioType, data.samplingFreq, data.countOfChannel, _p->audioInfo.countOfChannel, data.wordLength);
			gHDMI21RxDevAudioControler[HDMI21__AUDIO_USR_INFO].value--;

			if(data.audioType == LX_HDMI_AUDIO_NO_AUDIO){
				HDMI20_ADEF("HDMI[%d] Audio DVI:%d, AC:%d, V_Mute:%d, Standby:%d(%d), F_Err:%d(%d), stable:%d(%d) \n",\
				port, _p->video.dvi, _p->audio_change, (HDMI21_VPROC_Rx_Get_IsMute(_p)), _p->audioStandByCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_STANDBY_TIME].value,\
				_p->audioFifoErrMuteCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ERR_MUTE_TIME].value,\
				_p->audioStableCnt, gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME].value);
			}
		}
		ret = RET_OK;
	} while(0);
	return ret;
}

int KDRV_HDMI21_HAL_Rx_GetAudioACRInfo(UINT8 port, LX_HDMI_AUDIO_INFO_ACR_T *pHdmiAudioInfoAcr, int size)
{
	int ret = RET_ERROR;
	LX_HDMI_AUDIO_INFO_ACR_T	data;
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	do{
		/* [Check]Basic */
		if (port >= g_hdmi20_number_of_ports)	{
			HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
			break;
		}
		if(pHdmiAudioInfoAcr == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}
		if(size != sizeof(LX_HDMI_AUDIO_INFO_ACR_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI_AUDIO_INFO_ACR_T), size);
			break;
		}

		/* [Get]Handler */
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];

		/* [Get]ACR N/CTS*/
		data.n_param =  _p->audioInfo.acr_n;
		data.cts_param = _p->audioInfo.acr_cts;
		memcpy((LX_HDMI_AUDIO_INFO_ACR_T *)pHdmiAudioInfoAcr, &data, sizeof(LX_HDMI_AUDIO_INFO_ACR_T));

		if((gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 9) || (gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 10)){
			HDMI20_ADEF("HDMI[%d] Audio ACR n:%d, cts:%d\n", _p->port, _p->audioInfo.acr_n, _p->audioInfo.acr_cts);
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 9) gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value = 0;
		}

		ret = RET_OK;
	} while(0);
	return ret;
}

int KDRV_HDMI21_HAL_Rx_GetAudioChannelStatusInfo(UINT8 port, LX_HDMI_AUDIO_INFO_CHANNEL_STATUS_T *pHdmiAudioInfoChannelStatus, int size)
{
	int ret = RET_ERROR;
	LX_HDMI_AUDIO_INFO_CHANNEL_STATUS_T	data;
	UINT32 i,j;
	UINT32 addr;
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	do{
		/* [Check]Basic */
		if (port >= g_hdmi20_number_of_ports)	{
			HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
			break;
		}
		if(pHdmiAudioInfoChannelStatus== NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}
		if(size != sizeof(LX_HDMI_AUDIO_INFO_CHANNEL_STATUS_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI_AUDIO_INFO_CHANNEL_STATUS_T), size);
			break;
		}

		/* [Get]Handler */
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];

		/* [Init]data*/
		memset((void *)&data, 0, sizeof(LX_HDMI_AUDIO_INFO_CHANNEL_STATUS_T));
		addr = (UINT32)HDMI21_RX_PROC_CHSTAT_SP0_L1;

		/* [Get]Channel Status Data */
		for(i=0; i<8; i++){
			for(j=0; j<6; j++){
				//HDMI20_AUDIO("HDMI[%d] Channel[%d] Byte[%02d] -> 0x%04x : 0x%08x \n", _p->port, i, j*4, addr, _p->link_read(addr));
				data.subpacket[i][j]= _p->link_read(addr);
				addr += 4;
			}
		}

		memcpy((LX_HDMI_AUDIO_INFO_CHANNEL_STATUS_T *)pHdmiAudioInfoChannelStatus, &data, sizeof(LX_HDMI_AUDIO_INFO_CHANNEL_STATUS_T));

		ret = RET_OK;
	} while(0);
	return ret;

}

void HDMI21_HAL_Rx_Audio_Set_SwWaAudioDolbyWakeUpCall(UINT8 port)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	/* [Get]Handler */
	_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];

	do {
		/* Device Handler NULL defence */
		if(_p == NULL) {
			HDMI20_ERROR("Error : NULL Handler\n");
			break;
		}

		if(_p->video.dvi){
			/* Lets not do this in DVI mode */
			break;
		}

		if(gHDMI21AudioAdnormalCnt[_p->port] < gHDMI21RxDevAudioControler[HDMI21__AUDIO_ABNORMAL].value){
			gHDMI21AudioAdnormalCnt[_p->port]++;
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CNT_DBG].value != 0)HDMI20_ADEF("HDMI[%d] Audio adnormal cnt : %d < %d \n", _p->port, gHDMI21AudioAdnormalCnt[_p->port] ,gHDMI21RxDevAudioControler[HDMI21__AUDIO_ABNORMAL].value);
		}else{
			if((_p->audio_state == HDMI21__AUDIO_STATE__1__DISABLE__WAIT_AUDIF_RCV)
			&& (_p->audioInfo.acr_n != 0) && (_p->audioInfo.acr_cts != 0)){
				HDMI20_ADEF("HDMI[%d] SWWA : Audio State[%d] detected for SWWA to give kick to Audio AMD ISR!(n:%d, cts:%d)\n", _p->port, _p->audio_state, _p->audioInfo.acr_n,_p->audioInfo.acr_cts);
				HDMI21_ISRUNIT_Rx_Set_ForceIsrSet(_p, HDMI21_IRQ_SNPS_PKT_2_INTVEC, HDMI21_SNPS_FIELD_PKTDEC_AUDIF_RCV_IRQ);
				gHDMI21AudioAdnormal[_p->port] = TRUE;
			}
			else {
				HDMI21_LINE_DBG(11115, "HDMI[%d] SWWA : Audio State[%d] is not DISABLE_WAIT_AUDIF_RCV state[%d]\n", _p->port, _p->audio_state, HDMI21__AUDIO_STATE__1__DISABLE__WAIT_AUDIF_RCV);
			}
		}

	} while(0);

	return;
}

void HDMI21_HAL_Rx_Check_CSDIrq(UINT8 port)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	UINT32	reg_pao_byte0, reg_pao_pc_0;

	/* [Get]Handler */
	_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];

	do {
		/* Device Handler NULL defence */
		if(_p == NULL) {
			HDMI20_ERROR("Error : NULL Handler\n");
			break;
		}

#if 0
		/* Reset Audio type info */
		if( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ) {
			HDMI21_Rx_Audio_Path_PcPdReset(_p->port);
		}
#endif
		if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
			if((HDMI21_HAL_Rx_Get_IsLocalMuteOn((_p->port)) > 0) ||	(gHDMI21RxHandler[_p->port].audio_change == TRUE) || (gHDMI21RxHandler[_p->port].isMute == TRUE)\
				|| (gHDMI21RxHandler[_p->port].audioStandByCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_STANDBY_TIME].value)\
				|| (gHDMI21RxHandler[_p->port].audioStableCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME].value)\
				|| (gHDMI21RxHandler[_p->port].audioFifoErrMuteCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ERR_MUTE_TIME].value)){
				if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0)HDMI20_ADEF("HDMI[%d] Audio Ignore interrupt!! AChange:%d, isMute:%d, Mutecnt:%d, I2Scnt:%d, Noaudio:%d \n", _p->port, gHDMI21RxHandler[_p->port].audio_change, gHDMI21RxHandler[_p->port].isMute, gHDMI21RxHandler[_p->port].audioStandByCnt, gHDMI21RxHandler[_p->port].audioFifoErrMuteCnt, gHDMI21RxHandler[_p->port].audioStableCnt);
			} else {
				reg_pao_byte0 = _p->top_read(HDMI21_RX_AD_MAIN_AUD_INFO_BYTE0);
				reg_pao_pc_0  = _p->top_read(HDMI21_RX_AD_MAIN_AUD_INFO_PC);
				if((reg_pao_pc_0 & HDMI21_BURST_INFO_PAYLOAD_ERROR_BIT_MASK)){
					HDMI20_ADEF("HDMI[%d] Audio Pc adnormal!!(pc:%d->%d)\n", _p->port, gHDMI21RxHandler[_p->port].audioInfo.pao_pc,reg_pao_pc_0);
				}
				if(((reg_pao_byte0&(0x2)) != (gHDMI21RxHandler[_p->port].audioInfo.pao_byte0&(0x2))) \
				|| (((reg_pao_pc_0& HDMI21_BURST_INFO_AUDIO_TYPEBIT_MASK) != (gHDMI21RxHandler[_p->port].audioInfo.pao_pc& (UINT32)HDMI21_BURST_INFO_AUDIO_TYPEBIT_MASK)) \
				&& ((reg_pao_pc_0 & HDMI21_BURST_INFO_PAYLOAD_ERROR_BIT_MASK) && ((reg_pao_byte0&(0x2)) == 0)))){
					gHDMI21RxHandler[_p->port].audioStableCnt = 0;
					gHDMI21RxHandler[_p->port].audioChMapStandByCnt = 0;
					HDMI21_HAL_Rx_Set_AudioMuteControl(_p->port, HDMI21_AUDIO_MUTE);
					gHDMI21RxHandler[_p->port].isAudioMute = HDMI21_AUDIO_MUTE;
					if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0)HDMI20_ADEF("HDMI[%d] Audio interrup - Mute enable!!(byte0:%d->%d, pc:%d->%d)\n", _p->port, reg_pao_byte0, gHDMI21RxHandler[_p->port].audioInfo.pao_byte0, reg_pao_pc_0, gHDMI21RxHandler[_p->port].audioInfo.pao_pc);
					/* Update PAO Var */
					gHDMI21RxHandler[_p->port].audioInfo.pao_byte0= reg_pao_byte0;
					gHDMI21RxHandler[_p->port].audioInfo.pao_pc = reg_pao_pc_0;
					/* [Get]Handler */
					_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[_p->port];
					if(_p->audio_state == HDMI21__AUDIO_STATE__5__ENABLE__CHANGE_IRQ\
					|| _p->audio_state == HDMI21__AUDIO_STATE__0__DEFAULT)
					{
						HDMI21_HAL_Rx_Set_AudioEnable(_p->port, FALSE);
						if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_STATE].value != 0)HDMI20_ADEF("HDMI[%d] Audio state %d->%d(PAO type change)!!!kkkkkk\n", _p->port, HDMI21__AUDIO_STATE__5__ENABLE__CHANGE_IRQ, HDMI21__AUDIO_STATE__1__DISABLE__WAIT_AUDIF_RCV);
					}
					//if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0)HDMI20_ADEF("Audio interrup - Mute enable!!(byte0:%d->%d, pc:%d->%d)\n", reg_pao_byte0, gHDMI21RxHandler[_p->port].audioInfo.pao_byte0, reg_pao_pc_0, gHDMI21RxHandler[_p->port].audioInfo.pao_pc);
				}else{
					if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0)HDMI20_ADEF("HDMI[%d] Audio interrup[ ignore - audio type no change!\n", _p->port);
				}
			}
		}else{

			if((HDMI21_HAL_Rx_Get_IsLocalMuteOn((_p->port)) > 0) ||	(gHDMI21RxHandler[_p->port].audio_change == TRUE) || (gHDMI21RxHandler[_p->port].isMute == TRUE)\
				|| (gHDMI21RxHandler[_p->port].audioStandByCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_STANDBY_TIME].value)\
				|| (gHDMI21RxHandler[_p->port].audioStableCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME].value)\
				|| (gHDMI21RxHandler[_p->port].audioFifoErrMuteCnt < gHDMI21RxDevAudioControler[HDMI21__AUDIO_FIFO_ERR_MUTE_TIME].value)){
				if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0)HDMI20_ADEF("HDMI[%d] Audio Ignore interrupt!! AChange:%d, isMute:%d, Mutecnt:%d, I2Scnt:%d, Noaudio:%d \n", _p->port, gHDMI21RxHandler[_p->port].audio_change, gHDMI21RxHandler[_p->port].isMute, gHDMI21RxHandler[_p->port].audioStandByCnt, gHDMI21RxHandler[_p->port].audioFifoErrMuteCnt, gHDMI21RxHandler[_p->port].audioStableCnt);
			} else {
				reg_pao_byte0 = _p->top_read(HDMI21_RX_AD_MAIN_AUD_INFO_BYTE0);
				reg_pao_pc_0  = _p->top_read(HDMI21_RX_AD_MAIN_AUD_INFO_PC);
				if((reg_pao_pc_0 & HDMI21_BURST_INFO_PAYLOAD_ERROR_BIT_MASK)){
					HDMI20_ADEF("HDMI[%d] Audio Pc adnormal!!(pc:%d->%d)\n", _p->port, gHDMI21RxHandler[_p->port].audioInfo.pao_pc,reg_pao_pc_0);
				}

				if(((reg_pao_byte0&(0x2)) != (gHDMI21RxHandler[_p->port].audioInfo.pao_byte0&(0x2))) \
				|| (((reg_pao_pc_0& HDMI21_BURST_INFO_AUDIO_TYPEBIT_MASK) != (gHDMI21RxHandler[_p->port].audioInfo.pao_pc & (UINT32)HDMI21_BURST_INFO_AUDIO_TYPEBIT_MASK)) \
				&& (reg_pao_pc_0 & HDMI21_BURST_INFO_PAYLOAD_ERROR_BIT_MASK))){
					gHDMI21RxHandler[_p->port].audioStableCnt = 0;
					gHDMI21RxHandler[_p->port].audioChMapStandByCnt = 0;
					HDMI21_HAL_Rx_Set_AudioMuteControl(_p->port, HDMI21_AUDIO_MUTE);
					gHDMI21RxHandler[_p->port].isAudioMute = HDMI21_AUDIO_MUTE;
					if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0)HDMI20_ADEF("HDMI[%d] Audio interrup - Mute enable!!(byte0:%d->%d, pc:%d->%d)\n", _p->port, reg_pao_byte0, gHDMI21RxHandler[_p->port].audioInfo.pao_byte0, reg_pao_pc_0, gHDMI21RxHandler[_p->port].audioInfo.pao_pc);
					/* Update PAO Var */
					gHDMI21RxHandler[_p->port].audioInfo.pao_byte0= reg_pao_byte0;
					gHDMI21RxHandler[_p->port].audioInfo.pao_pc = reg_pao_pc_0;
					/* [Get]Handler */
					_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[_p->port];
					if(_p->audio_state == HDMI21__AUDIO_STATE__5__ENABLE__CHANGE_IRQ\
					|| _p->audio_state == HDMI21__AUDIO_STATE__0__DEFAULT)
					{
						HDMI21_HAL_Rx_Set_AudioEnable(_p->port, FALSE);
						if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_STATE].value != 0)HDMI20_ADEF("HDMI[%d] Audio state %d->%d(PAO type change)!!!kkkkkk\n", _p->port, HDMI21__AUDIO_STATE__5__ENABLE__CHANGE_IRQ, HDMI21__AUDIO_STATE__1__DISABLE__WAIT_AUDIF_RCV);
					}
					//if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0)HDMI20_ADEF("Audio interrup - Mute enable!!(byte0:%d->%d, pc:%d->%d)\n", reg_pao_byte0, gHDMI21RxHandler[_p->port].audioInfo.pao_byte0, reg_pao_pc_0, gHDMI21RxHandler[_p->port].audioInfo.pao_pc);
				}else{
					if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_CSD_IRQ_DBG].value != 0x0)HDMI20_ADEF("HDMI[%d] Audio interrup[ ignore - audio type no change!\n", _p->port);
				}
			}
		}
	} while(0);

	return;
}


int KDRV_HDMI21_HAL_Rx_GetAudioCopyInfo(UINT8 port, LX_HDMI_AUDIO_COPY_T *pHdmiCopyInfo, int size)
{
	int ret = RET_ERROR;
	UINT32	reg_achst_byte0, reg_achst_byte1;
	UINT32	CpBit, LBit;
	LX_HDMI_AUDIO_COPY_T hdmiCopyInfo;
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	do{
		/* [Check]Basic */
		if (port >= g_hdmi20_number_of_ports) {
			HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
			break;
		}

		/* [Get]Handler */
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];

		/* [Get]Copyright Info */
		if (_p->video.dvi == 1){//DVI Mode
			reg_achst_byte0 = gHDMI21AudioRegData.byte0;

			//Set a CpBit
			if (reg_achst_byte0 & HDMI21_AUDIO_CP_BIT_MASK)
				CpBit = 1;
			else
				CpBit = 0;

			reg_achst_byte1 = gHDMI21AudioRegData.byte1;

			//Set a LBit
			if (reg_achst_byte1 & HDMI21_AUDIO_L_BIT_MASK)
				LBit = 1;
			else
				LBit = 0;

			//Set a Copyright Info. by CpBit and LBit
			if ((CpBit == 0) && (LBit == 0))
				hdmiCopyInfo = LX_HDMI_AUDIO_COPY_ONCE;
			else if ((CpBit == 0) && (LBit == 1))
				hdmiCopyInfo = LX_HDMI_AUDIO_COPY_NO_MORE;	//same with LX_HDMI_AUDIO_COPY_NEVER
			else
				hdmiCopyInfo = LX_HDMI_AUDIO_COPY_FREE;

		}
		else{ //HDMI Mode
			hdmiCopyInfo = LX_HDMI_AUDIO_COPY_FREE;
		}

		memcpy((LX_HDMI_AUDIO_COPY_T *)pHdmiCopyInfo, &hdmiCopyInfo, sizeof(LX_HDMI_AUDIO_COPY_T));

		if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_LINE_DBG].value == 5){
			HDMI20_ADEF("HDMI[%d] Audio HDMI_GetAudioCopyInfo :CopyInfo = %d\n", _p->port, hdmiCopyInfo);
		}

		ret = RET_OK;
	}while(0);
	return ret;
}

int KDRV_HDMI21_HAL_Rx_Set_HDMIARC(UINT8 port, BOOLEAN bOnOff)
{
	int ret = RET_OK;
	return ret;
}

int KDRV_HDMI21_HAL_Rx_Set_AudioMute(UINT8 port, LX_HDMI_MUTE_CTRL_T *pMuteCtrl, int size)
{
	int ret = RET_OK;
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	BOOLEAN 	audioMuteState;
	LX_HDMI_MUTE_CTRL_T muteCtrl;

	do{
		/* [Check]Basic */
		if (port >= g_hdmi20_number_of_ports)	{
			HDMI20_ERROR("[%d] %s : port = %d is error!!!\n", __L__, __F__, port);
			break;
		}

		/* [Get]Handler */
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[port];

		HDMI20_AUDIO("HDMI[%d] Audio HDMI21_HAL_Rx_Set_AudioMute :mutecnt(%d)\n", port, _p->audioStandByCnt);

		/* [Get]Mute status */
		audioMuteState = !((_p->link_read(HDMI21_RX_PROC_CONFIG0) & HDMI21_RX_PROC_CONFIG0__I2S_ENABLE) >> 1);
		memset((void *)&muteCtrl, 0, sizeof(LX_HDMI_MUTE_CTRL_T));
		memcpy(&muteCtrl, (void __user *)pMuteCtrl, sizeof(LX_HDMI_MUTE_CTRL_T));

		/* [Set]Mute Control */
		if ((muteCtrl.eMode == LX_HDMI_AUDIO_MUTE) || (muteCtrl.eMode == LX_HDMI_AV_MUTE)) {
			//Check a previous state
			if (muteCtrl.bAudioMute != audioMuteState) {
				if (muteCtrl.bAudioMute == TRUE) {
					//Mute audio data
					HDMI21_HAL_Rx_Set_AudioMuteControl(port, HDMI21_AUDIO_MUTE);
					HDMI20_AUDIO("HDMI[%d] Audio Mute enable !\n", _p->port);
					_p->isAudioMute = HDMI21_AUDIO_MUTE;
					_p->isAudioMuteControl = TRUE;
				}else {
					//Un-mute audio data
					if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
						if(((_p->audio_change == FALSE) && (_p->isMute == FALSE)\
							&& (_p->audioStandByCnt == gHDMI21RxDevAudioControler[HDMI21__AUDIO_STANDBY_TIME].value))\
							|| (_p->audioStableCnt == gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME_O22].value)) {
							HDMI21_HAL_Rx_Set_AudioMuteControl(port, HDMI21_AUDIO_UNMUTE);
							HDMI20_ADEF("HDMI[%d] Audio Mute disable!\n", _p->port);
							_p->isAudioMute = HDMI21_AUDIO_UNMUTE;
						}
						_p->isAudioMuteControl = 0;
					}else{
						if(((_p->audio_change == FALSE) && (_p->isMute == FALSE)\
							&& (_p->audioStandByCnt == gHDMI21RxDevAudioControler[HDMI21__AUDIO_STANDBY_TIME].value))\
							|| (_p->audioStableCnt == gHDMI21RxDevAudioControler[HDMI21__AUDIO_STABLE_TIME].value)) {
							HDMI21_HAL_Rx_Set_AudioMuteControl(port, HDMI21_AUDIO_UNMUTE);
							HDMI20_ADEF("HDMI[%d] Audio Mute disable!\n", _p->port);
							_p->isAudioMute = HDMI21_AUDIO_UNMUTE;
						}
						_p->isAudioMuteControl = 0;
					}
				}

				//For debug print
				HDMI20_ADEF("[%d] %s : HDMI[%d] Audio bAudioMute = %s \n",	\
							__L__, __F__, _p->port, (muteCtrl.bAudioMute ? "On" : "Off"));
			}

			//For debug print
			if (muteCtrl.bAudioMute == FALSE) {
				HDMI20_ADEF("HDMI[%d] Audio SetMute : port = %d, type = %d, freq = %d, mute = %d->%d\n", \
							__L__, _p->port, _p->audioInfo.audioType, _p->audioInfo.samplingFreq, \
							audioMuteState, muteCtrl.bAudioMute);
			}
		}

		ret = RET_OK;
	} while(0);
	return ret;
}

EXPORT_SYMBOL (KDRV_HDMI21_HAL_Rx_GetAudioInfo);
EXPORT_SYMBOL (KDRV_HDMI21_HAL_Rx_GetAudioACRInfo);
EXPORT_SYMBOL (KDRV_HDMI21_HAL_Rx_GetAudioChannelStatusInfo);
EXPORT_SYMBOL (KDRV_HDMI21_HAL_Rx_Set_AudioMute);
EXPORT_SYMBOL (KDRV_HDMI21_HAL_Rx_GetAudioCopyInfo);
EXPORT_SYMBOL (KDRV_HDMI21_HAL_Rx_Set_HDMIARC);

