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

#ifndef	_HDMI21_RX_AUDIO_H_
#define	_HDMI21_RX_AUDIO_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "hdmi20_kapi.h"
#include "hdmi_kapi.h"

#include "hdmi21_rx_audio_path_i2s.h"
#include "hdmi21_rx_audio_path_spdif.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* MUTE CONTROL */
#define HDMI21_AUDIO_MUTE		1
#define HDMI21_AUDIO_UNMUTE		0

/* FIFO Adjust */
#define HDMI21_AUDIO_FIFO_FILL_MIN			0x70
#define HDMI21_AUDIO_FIFO_FILL_MAX			0x180

/* Audio Typoe mask */
#define HDMI21_AUDIO_L_BIT_MASK		0x80
#define HDMI21_AUDIO_ACR_8BIT_MASK	0xFF
#define HDMI21_AUDIO_ACR_4BIT_MASK	0xF


#define HDMI21_AUDIO_STABLE_CNT_INITIAL				0x7
#define HDMI21_AUDIO_STABLE_CNT_INITIAL_O22			0x9
#define HDMI21_AUDIO_UNKWON_TYPE_MUTE_CNT_INITIAL	0x3

/* Register */
#define HDMI21_RX_HDMI_SOFT_RESET			0xC9306008
/* TOP*/
#define HDMI21_RX_ACR_PLL_MODE				0x2C//0x28
#define HDMI21_RX_ACR_CTS					0x34//0x30
#define HDMI21_RX_ACR_N						0x30//0x2C

#define HDMI21_RX_ACR_CLK_N_FS				0x38
#define HDMI21_RX_ACR_CLK_N_FS__128			0x0
#define HDMI21_RX_ACR_CLK_N_FS__256			0x1
#define HDMI21_RX_ACR_CLK_N_FS__512			0x2

#define HDMI21_RX_ACR_CLK_DIVIDER			0x3C
#define HDMI21_RX_ACR_CLK_DIVIDER__DIV1		0x0
#define HDMI21_RX_ACR_CLK_DIVIDER__DIV2		0x1
#define HDMI21_RX_ACR_CLK_DIVIDER__DIV4		0x2

#if 0
#define HDMI21_RX_AD_MAIN_ARC_SET			0x0C
#define HDMI21_RX_AD_MAIN_ARC_SET_ENABLE	0x01


#define HDMI21_RX_AD_MAIN_PHY_ARC			0xB4
#define HDMI21_RX_AD_MAIN_PHY_ARC_DEFAULT	0x20
#define HDMI21_RX_AD_MAIN_PHY_ARC_ENABLE	0x01
#endif 

#define HDMI21_RX_AD_MAIN_AUD_INFO_BYTE0			0x70
#define HDMI21_RX_AD_MAIN_AUD_INFO_BYTE1			0x74
#define HDMI21_RX_AD_MAIN_AUD_INFO_BYTE2			0x78
#define HDMI21_RX_AD_MAIN_AUD_INFO_BYTE3			0x7C
#define HDMI21_RX_AD_MAIN_AUD_INFO_PC				0x88

#define HDMI21_RX_AD_INFO_CLR_AUDIO					0x11C
#define HDMI21_RX_AD_INFO_CLR_AUDIO__ENABLE			0x00000008
#define HDMI21_RX_AD_INFO_CLR_AUDIO__DISABLE		0x00000000

#define HDMI21_RX_AD_MAIN_AUD_INFO_CLR_SEL			0x06C
#define HDMI21_RX_AD_MAIN_AUD_INFO_CLR_SEL__ENABLE	0x00000001
#define HDMI21_RX_AD_MAIN_AUD_INFO_CLR_SEL__DISABLE	0x00000000

#define HDMI21_RX_AD_INTR_CLR_AUDIO					0x118
#define HDMI21_RX_AD_INTR_CLR_AUDIO__ENABLE			0x00001800
#define HDMI21_RX_AD_INTR_CLR_AUDIO__DISABLE		0x00000000

#define HDMI21_RX_AD_AUD_MEAS						0x208
#define HDMI21_RX_AD_TMDS_CLK_MEAS					0x20C
#define HDMI21_RX_AD_LINK_CLK_MEAS					0x210
#define HDMI21_RX_AD_FRL_CLK_MEAS					0x214

/* Link */
#define HDMI21_RX_GLOBAL_ENABLE						0x24
#define HDMI21_RX_GLOBAL_ENABLE__AUDIO_ENABLE		0x200
#define HDMI21_RX_GLOBAL_ENABLE__AUDIO_DISABLE		0xFFFFFDFF

#define HDMI21_RX_CMU_STATUS						0x7C
#define HDMI21_RX_CMU_STATUS__AUDCLK_LOCKED_ST		0x1
#define HDMI21_RX_CMU_STATUS__AUDCLK_OFF_ST			0x2

#define HDMI21_RX_CMU_AUDCLK_FREQ					0x80
#define HDMI21_RX_CMU_TMDSQPCLK_FREQ				0x84

/* FIFO */
#define HDMI21_RX_AUD_FIFO_CONFIG					0x460
#define HDMI21_RX_AUD_FIFO_CONFIG__FILL_RESTART		0x1				// always reset in fifo empty situation.
#define HDMI21_RX_AUD_FIFO_CONFIG__FILL_RESTART_ON	0x1				// always reset in fifo empty situation.
#define HDMI21_RX_AUD_FIFO_CONFIG__FILL_RESTART_OFF	0x0				// always reset in fifo empty situation.


#define HDMI21_RX_AUD_FIFO_CONTROL					0x464
#define HDMI21_RX_AUD_FIFO_CONTROL__FIFO_INIT		0x1				// bit0
#define HDMI21_RX_AUD_FIFO_CONTROL__CLR_MIN			0x2				// bit1 0x1
#define HDMI21_RX_AUD_FIFO_CONTROL__CLR_MAX			0x4				// bit2 0x1

#define HDMI21_RX_AUD_FIFO_TH_PASS					0x468
#define HDMI21_RX_AUD_FIFO_TH_PASS__VALUE			0x90

#define HDMI21_RX_AUD_FIFO_TH						0x46C			// AUDIO_FIFO_THR	m16p3: 0x244
#define HDMI21_RX_AUD_FIFO_TH_LOW					0x200000		// bit16~31 0x20
#define HDMI21_RX_AUD_FIFO_TH_LOW_REAL				0x20		// bit16~31 0x20
#define HDMI21_RX_AUD_FIFO_TH_HIGH					0x300

#define HDMI21_RX_AUD_FIFO_ADJUST_LOW				0x70		// bit16~31 0x20
#define HDMI21_RX_AUD_FIFO_ADJUST_HIGH				0x2FF

#define HDMI21_RX_AUD_FIFO_MUTE_TH					0x470
#define HDMI21_RX_AUD_FIFO_MUTE_TH_LOW				0x80000			// bit16~31 0x8
#define HDMI21_RX_AUD_FIFO_MUTE_TH_HIGH				0x320

#define HDMI21_RX_AUD_FIFO_STS1						0x474
#define HDMI21_RX_AUD_FIFO_STS1__FILLSTSMIN			0xFFFF			// bit0~15
#define HDMI21_RX_AUD_FIFO_STS1__FILLSTSMAX			0xFFFF0000		// bit16~31

#define HDMI21_RX_AUD_FIFO_STS2__FILLSTS1			0x478			// bit0~15		m16p3: 0x27C
#define HDMI21_RX_AUD_FIFO_STS2__OVERFLOW			0x1000000		// bit24
#define HDMI21_RX_AUD_FIFO_STS2__UNDERFLOW			0x2000000		// bit25
#define HDMI21_RX_AUD_FIFO_STS2__ERR				0x3000000		// bit24~25
#define HDMI21_RX_AUD_FIFO_STS2__INIT				0x0000000		// bit24~25



/* PROC */
#define HDMI21_RX_PROC_CONFIG0						0x480
#define HDMI21_RX_PROC_CONFIG0__OUT_DISABLE			0xFFFFFFF8		// bit0~2
#define HDMI21_RX_PROC_CONFIG0__OUT_ENABLE			0x5		// bit0~2
#define HDMI21_RX_PROC_CONFIG0__MUTE				0xFFFFFFFD		// bit0~2
#define HDMI21_RX_PROC_CONFIG0__UNMUTE				0x7				// bit0~2 0b111
#define HDMI21_RX_PROC_CONFIG0__PAO_ENABLE			0x1				// bit0
#define HDMI21_RX_PROC_CONFIG0__I2S_ENABLE			0x2				// bit1
#define HDMI21_RX_PROC_CONFIG0__SPDIF_ENABLE		0x4				// bit2
#define HDMI21_RX_PROC_CONFIG0__AUD_CHAN_SPREAD_EN	0x20			// bit5
#define HDMI21_RX_PROC_CONFIG0__AUD_CHAN_SPREAD_DISEN 0xFFFFFFDF	// bit5
#define HDMI21_RX_PROC_CONFIG0__AUD_MUTE_OVR_EN		0x1000			// bit12
#define HDMI21_RX_PROC_CONFIG0__AUD_MUTE_OVR_VALUE	0x2000			// bit13
#define HDMI21_RX_PROC_CONFIG0__SPK_ALLOC_OVR_EN	0x10000			// bit16
#define HDMI21_RX_PROC_CONFIG0__SPK_ALLOC_OVR_DISEN	0xFFFEFFFF		// bit16

#define HDMI21_RX__EXT__PROC_CONFIG0__MUTE					0x00000005	// bit0~2
#define HDMI21_RX__EXT__PROC_CONFIG0__UNMUTE				0x00000007				// bit0~2 0b111
#define HDMI21_RX__EXT__PROC_CONFIG0__AUD_CHAN_SPREAD_EN	0x00000020			// bit5
#define HDMI21_RX__EXT__PROC_CONFIG0__AUD_CHAN_SPREAD_DISEN 0x00000000	// bit5
#define HDMI21_RX__EXT__PROC_CONFIG0__SPK_ALLOC_OVR_EN		0x00010000			// bit16
#define HDMI21_RX__EXT__PROC_CONFIG0__SPK_ALLOC_OVR_DISEN	0x00000000		// bit16


#define HDMI21_RX_PROC_CONFIG1						0x484
#define HDMI21_RX_PROC_CONFIG1__LAYOUT_OVR_EN		0x1				// bit0
#define HDMI21_RX_PROC_CONFIG1__LAYOUT_OVR_VALUE__1	0x2				// bit1

#define HDMI21_RX_PROC_CONFIG2						0x488
#define HDMI21_RX_PROC_CONFIG2__MASK_ON				0x01F103F1//0x01F103F3
#define HDMI21_RX_PROC_CONFIG2__FMT_OFF				0x01F103F1
#define HDMI21_RX_PROC_CONFIG2__MASK_OFF			0x01F10000


#define HDMI21_RX_PROC_CONFIG3						0x48C
#define HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH8	0xFF			// bit0~31
#define HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH6	0x3F			// bit0~31
#define HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH4	0xF				// bit0~31
#define HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_CH2	0x3				// bit0~31
#define HDMI21_RX_PROC_CONFIG3__SPK_ALLOC_OVR_INIT	0x0				// bit0~31

#define HDMI21_RX_PROC_STATUS1						0x490
#define HDMI21_RX_PROC_STATUS1__AUD_FMT_ST__MASK	0x7 			// bit0~2
#define HDMI21_RX_PROC_STATUS1__AUD_FMT_ST__ASP		0xFFFFFFF8 		// bit0~2
#define HDMI21_RX_PROC_STATUS1__AUD_FMT_ST__HBR		0x3 			// bit0~2 0b11(3)
#define HDMI21_RX_PROC_STATUS1__LAYOUT_MASK			0x8 			// bit3
#define HDMI21_RX_PROC_STATUS1__AUD_MUTE_ST			0x100 			// bit8
#define HDMI21_RX_PROC_STATUS1__SAMPLE_PRESENT_MASK	0x1E0000 		// bit17~20
#define HDMI21_RX_PROC_STATUS1__SAMPLE_PRESENT_MASK1	0x020000 		// bit17
#define HDMI21_RX_PROC_STATUS1__SAMPLE_PRESENT_MASK2	0x040000 		// bit18
#define HDMI21_RX_PROC_STATUS1__SAMPLE_PRESENT_MASK3	0x080000 		// bit19
#define HDMI21_RX_PROC_STATUS1__SAMPLE_PRESENT_MASK4	0x100000 		// bit20
#define HDMI21_RX_PROC_STATUS1__SPEAKER_ALLOC_MASK	0xFF000000 		// bit17~20


#define HDMI21_RX_PROC_CHSTAT_SP0_L1				0x4A0
#define HDMI21_RX_PROC_CHSTAT_SP0_L2				0x4A4
#define HDMI21_RX_PROC_CHSTAT_SP0_L3				0x4A8
#define HDMI21_RX_PROC_CHSTAT_SP0_L4				0x4AC
#define HDMI21_RX_PROC_CHSTAT_SP0_L5				0x4B0
#define HDMI21_RX_PROC_CHSTAT_SP0_L6				0x4B4

/* AUDIO */
#define HDMI21_RX_AUD_GEN_CONFIG0					0x740
#define HDMI21_RX_AUD_GEN_CONFIG0__AGEN_EN			0x1			// bit0 0b1
#define HDMI21_RX_AUD_GEN_CONFIG0__AGEN_DISEN		0x0			// bit0 0b0
#define HDMI21_RX_AUD_GEN_CONFIG0__LAYOUT__0		0x00		// bit4 0b0
#define HDMI21_RX_AUD_GEN_CONFIG0__LAYOUT__1		0x10		// bit4 0b1
#define HDMI21_RX_AUD_GEN_CONFIG0__CH__MASK			0xFF00
#define HDMI21_RX_AUD_GEN_CONFIG0__CH__8			0x1F01		// bit8~15 0b11111100(0xFC)
#define HDMI21_RX_AUD_GEN_CONFIG0__CH__6			0x0501		// bit8~15 0b00010100(0x94)
#define HDMI21_RX_AUD_GEN_CONFIG0__CH__4			0x0101		// bit8~15 0b00000100(0x84)
#define HDMI21_RX_AUD_GEN_CONFIG0__CH__2			0x0001		// bit8~15 0b00000000(0x80)
#define HDMI21_RX_AUD_GEN_CONFIG0__CH__HBR			0x1F01		// bit8~15 0b01110000(0xFF)
#define HDMI21_RX_AUD_GEN_CONFIG0__CH__AUTO			0x0000		// bit8~15 0b01110000(0x7C)

/* ACR */
#define HDMI21_RX_PDEC_ACR_CONFIG					0x1000
#define HDMI21_RX_PDEC_ACR_OVERRIDE_ENABLE 			0x1
#define HDMI21_RX_PDEC_ACR_OVERRIDE_DISABLE			0x0
#define HDMI21_RX_PDEC_ACR_DELTA_CTA_1				0x0
#define HDMI21_RX_PDEC_ACR_DELTA_CTA_2				0x10
#define HDMI21_RX_PDEC_ACR_DELTA_CTA_4				0x20
#define HDMI21_RX_PDEC_ACR_DELTA_CTA_8				0x30
#define HDMI21_RX_PDEC_ACR_DELTA_CTA_16				0x40
#define HDMI21_RX_PDEC_ACR_DELTA_CTA_32				0x50

#define HDMI21_RX_PDEC_ACR_CTS_CONFIG				0x1004
#define HDMI21_RX_PDEC_ACR_N_CONFIG					0x1008

#define HDMI21_RX_PDEC_ACR_MAXMIN_CLEAR				0x100C
#define HDMI21_RX_PDEC_ACR_MAXMIN_CLEAR_ENABLE		0x1
#define HDMI21_RX_PDEC_ACR_CTS_MAX_STATUS			0x1010
#define HDMI21_RX_PDEC_ACR_CTS_MIN_STATUS			0x1014
#define HDMI21_RX_PDEC_ACR_N_MAX_STATUS				0x1018
#define HDMI21_RX_PDEC_ACR_N_MIN_STATUS				0x101C

#define HDMI21_RX_PDEC_ACR_PB_CTS				0x110C
#define HDMI21_RX_PDEC_ACR_PB_N					0x1110


// channel count
#define HDMI21_RX_PDEC_AUDIF_PB3_0					0x1244		// disland.c infoframe-color, channel count= PB1-0~3bit
#define HDMI21_RX_PDEC_AUDIF_PB3_0__BIT_MASK_CHA_CNT 0x00000700	//wonsik.do 

#define HDMI21_BURST_INFO_PAYLOAD_ERROR_BIT_MASK	0x0080	///<Error-flag indicationg that the burst-payload may contain errors
#define HDMI21_AUDIO_CP_BIT_MASK					0x04	///< 0 : copyright, 1 : no copyright
#define HDMI21_AUDIO_SAMPLE_NON_PCM_MASK			0x02	///< 0 : linear PCM, 1 : other purpose
#define HDMI21_BURST_INFO_AUDIO_TYPEBIT_MASK		   0x001F	///< Bit 4 - 0

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
	/* DBG */
	HDMI21__AUDIO_STATE__0__DEFAULT = 0,
	HDMI21__AUDIO_STATE__1__DISABLE__WAIT_AUDIF_RCV,
	HDMI21__AUDIO_STATE__2__ENABLE__WAIT_CLK_OFF_CHG,
	HDMI21__AUDIO_STATE__3__ENABLE__WAIT_FIFO_PASS_IRQ1,
	HDMI21__AUDIO_STATE__4__ENABLE__WAIT_FIFO_PASS_IRQ2,
	HDMI21__AUDIO_STATE__5__ENABLE__CHANGE_IRQ,
	
	HDMI21__AUDIO_STATE__MAXNUM
} HDMI21__AUDIO_STATE__LIST_T;

typedef enum
{
	/* DBG */
	HDMI21__AUDIO_DEBUG = 0,
	HDMI21__AUDIO_LINE_DBG,
	HDMI21__AUDIO_CNT_DBG,
	HDMI21__AUDIO_IRQ_DBG,
	HDMI21__AUDIO_CSD_IRQ_DBG,

	/* Count */
	HDMI21__AUDIO_COUNT,
	HDMI21__AUDIO_STANDBY_TIME,
	HDMI21__AUDIO_STABLE_TIME,
	HDMI21__AUDIO_STABLE_TIME_O22,
	HDMI21__AUDIO_STABLE,
	HDMI21__AUDIO_STABLE_O22,
	HDMI21_AUDIO_UNKWON_TYPE_MUTE,
	HDMI21__AUDIO_ABNORMAL,
	HDMI21__AUDIO_HBR_ABNORMAL,
	HDMI21__AUDIO_TYPE_ABNORMAL,
	HDMI21__AUDIO_FIFO_ABNORMAL,
	HDMI21__AUDIO_CHANNEL_ABNORMAL,
	HDMI21__AUDIO_PRINT_LIMIT,
	HDMI21__AUDIO_FIFO_ERR_MUTE_TIME,
	HDMI21__AUDIO_CH_MAP_STANDBY_TIME,
	HDMI21__AUDIO_CH_MAP_MAX,
	HDMI21__AUDIO_IRQ_FIFO_ERR_MAX,
	HDMI21__AUDIO_ACR_ERR_MAX,
	HDMI21__AUDIO_FORCE_MUTE_TIME,
	HDMI21__AUDIO_FORCE_MUTE_TIME_O22,
	HDMI21__AUDIO_FORCE_DISABLE,
	HDMI21__AUDIO_ACR_RESET_TIME,
	HDMI21__AUDIO_CHANNEL_INCREASE_TIME,

	/* Control */
	HDMI21__AUDIO_CONTROL,
	HDMI21__AUDIO_IGNORE_ERR,
	HDMI21__AUDIO_IGNORE_IRQ,
	HDMI21__AUDIO_IGNORE_CHANNEL,
	HDMI21__AUDIO_FORCE_UNMUTE,
	HDMI21__AUDIO_FORCE_TYPE,
	HDMI21__AUDIO_FORCE_FS,
	HDMI21__AUDIO_FORCE_CHANNEL,
	HDMI21__AUDIO_FORCE_STREAM,
	HDMI21__AUDIO_FORCE_ACR_RESET,
	HDMI21__AUDIO_FORCE_UNKNOWN_TYPE,
	HDMI21__AUDIO_FORCE_HBR,
	HDMI21__AUDIO_MANUAL_N_CTS,
	HDMI21__AUDIO_DISABLE_SPREAD,
	HDMI21__AUDIO_STATE_INIT,
	HDMI21__AUDIO_TEST,
	HDMI21__AUDIO_IRQ_DISABLE_PCD,
	HDMI21__AUDIO_IRQ_DISABLE_SPDIF,
	HDMI21__AUDIO_FIFO_ADJUST,
	HDMI21__AUDIO_FIFO_ADJUST_MAX_CNT,
	HDMI21__AUDIO_REG_PRINT_REPEAT,
	HDMI21__AUDIO_FIFO_ERROR_PRINT_DISABLE,

	/* Info */
	HDMI21__AUDIO_INFORMATION,
	HDMI21__AUDIO_DATA,
	HDMI21__AUDIO_N_CTS,
	HDMI21__AUDIO_CLOCK,
	HDMI21__AUDIO_INFO,
	HDMI21__AUDIO_USR_INFO,
	HDMI21__AUDIO_CNT,
	HDMI21__AUDIO_FUNC_CALL,
	HDMI21__AUDIO_FIFO,
	HDMI21__AUDIO_FIFO_DIFF,
	HDMI21__AUDIO_MUTE,
	HDMI21__AUDIO_HBR,
	HDMI21__AUDIO_PC,
	HDMI21__AUDIO_REG,
	HDMI21__AUDIO_CHANNEL_STATUS,
	HDMI21__AUDIO_STATE,
	HDMI21__AUDIO_PROC_CONFIG0_SETTING,
	HDMI21__AUDIO_CSD_DATA,
	HDMI21__AUDIO_READ_TOP_REG,
	HDMI21__AUDIO_READ_LINK_REG,

	/* DBG Init */
	HDMI21__AUDIO_INITIALIZE,
	HDMI21__AUDIO_DEBUG_INIT,
	HDMI21__AUDIO_COUNT_INIT,
	HDMI21__AUDIO_CONTROL_INIT,
	HDMI21__AUDIO_INFORMATION_INIT,
	HDMI21__AUDIO_ALL_DEBUG_INIT,
	
	HDMI21__DEV_AUDIO_CONTROL_LIST_MAXNUM
} HDMI21_DEV_AUDIO_CONTROL_LIST_T;

typedef struct{
	UINT32 procConfig0_chAlloc;
	UINT32 procConfig0_chSpread;
	UINT32 procConfig0_muteControl;
}HDMI21_HAL_RX_AUDIO_DATA;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
/* IOCTL */
int HDMI21_HAL_Rx_GetAudioInfo(UINT8 port, LX_HDMI_AUDIO_INFO_T *pHdmiAudioInfo, int size);
int HDMI21_HAL_Rx_GetAudioCopyInfo(UINT8 port, LX_HDMI_AUDIO_COPY_T *pHdmiCopyInfo, int size);
int HDMI21_HAL_Rx_Set_HDMIARC(UINT8 port, BOOLEAN bOnOff);

/* DBG */
int HDMI21_HAL_Rx_Get_DebugAudioInfo(UINT8 port, LX_HDMI_DEBUG_AUDIO_INFO_T *pDebugAudioInfo, int size);
int HDMI21_HAL_Rx_AudioInfoPrint(UINT8 port);
int HDMI21_HAL_Rx_AudioDebugIntialize(UINT8 port);

/* Function */
int HDMI21_HAL_Rx_Set_AudioMute(UINT8 port, LX_HDMI_MUTE_CTRL_T *pMuteCtrl, int size);
void HDMI21_HAL_Rx_Set_Audio_Configure(UINT8 port, HDMI21_HAL_PHY_INITIATED_MODE_T mode);
UINT32 HDMI21_HAL_Rx_Get_PLLFreqRange(UINT32 tmds_clk);
void HDMI21_HAL_Rx_Get_AudioACRParam(UINT8 port, BOOLEAN clear);
int HDMI21_HAL_Rx_Get_AudioWordLength(UINT8 port, LX_HDMI_AUDIO_WORD_LENGTH_T *wordLength);
int HDMI21_HAL_Rx_Get_AudioType(UINT8 port, LX_HDMI_AUDIO_TYPE_T *audioType);
int HDMI21_HAL_Rx_Get_AudioInfo(UINT8 port);
int HDMI21_HAL_Rx_Set_AudioReset(UINT8 port);
int HDMI21_HAL_Rx_Set_AudioChange(UINT8 port);
int HDMI21_HAL_Rx_Set_AudioFIFOReset(UINT8 port);
int HDMI21_HAL_Rx_Set_AudioMuteControl(UINT8 port, BOOLEAN mute);
int HDMI21_HAL_Rx_Get_AudioFreqFromTMDSClock(UINT8 port, unsigned int *samplingFreq);
int HDMI21_HAL_Rx_Get_AudioCountOfChannel(UINT8 port, int *countOfChannel);
int HDMI21_HAL_Rx_Get_AudioStream(UINT8 port, LX_HDMI_AUDIO_STREAM_T *stream);
int HDMI21_HAL_Rx_Set_AudioEnable(UINT8 port, BOOLEAN enable);
int HDMI21_HAL_Rx_Set_AudioState(UINT8 port);
void HDMI21_HAL_Rx_Audio_Set_SwWaAudioDolbyWakeUpCall(UINT8 port);
void HDMI21_HAL_Rx_Check_CSDIrq(UINT8 port);


/* KDRV */
int KDRV_HDMI21_HAL_Rx_GetAudioInfo(UINT8 port, LX_HDMI_AUDIO_INFO_T *pHdmiAudioInfo, int size);
int KDRV_HDMI21_HAL_Rx_GetAudioACRInfo(UINT8 port, LX_HDMI_AUDIO_INFO_ACR_T *pHdmiAudioInfoAcr, int size);
int KDRV_HDMI21_HAL_Rx_GetAudioChannelStatusInfo(UINT8 port, LX_HDMI_AUDIO_INFO_CHANNEL_STATUS_T *pHdmiAudioInfoChannelStatus, int size);
int KDRV_HDMI21_HAL_Rx_GetAudioCopyInfo(UINT8 port, LX_HDMI_AUDIO_COPY_T *pHdmiCopyInfo, int size);
int KDRV_HDMI21_HAL_Rx_Set_HDMIARC(UINT8 port, BOOLEAN bOnOff);
int KDRV_HDMI21_HAL_Rx_Set_AudioMute(UINT8 port, LX_HDMI_MUTE_CTRL_T *pMuteCtrl, int size);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

