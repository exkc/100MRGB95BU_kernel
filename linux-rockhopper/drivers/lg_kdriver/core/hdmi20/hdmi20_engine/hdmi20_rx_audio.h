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
 *  @date       2016-05-02
 *  @note       Additional information.
 */

#ifndef	_HDMI20_RX_AUDIO_H_
#define	_HDMI20_RX_AUDIO_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "hdmi20_kapi.h"
#include "hdmi_kapi.h"

//#include "./synopsys_api/hdmi_rx_ctrl.h"
//#include "./synopsys_api/hdmi_rx_ctrl_hdcp.h"

#include "hdmi20_rx_audio_path_i2s.h"
#include "hdmi20_rx_audio_path_spdif.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define HDMI20_AUDIO_MUTE		1
#define HDMI20_AUDIO_UNMUTE		0

#define HDMI20_AUDIO_FIFO_FILL_MIN			0x100
#define HDMI20_AUDIO_FIFO_FILL_MAX			0x180

#define HDMI20_AUDIO_L_BIT_MASK	0x80

#define HDMI20_AUDIO_STABLE_CNT_INITIAL		0x14

/* Register */
#define HDMI20_RX_ACR_CLK_N_FS				0x38
#define HDMI20_RX_ACR_CLK_N_FS_128			0x0
#define HDMI20_RX_ACR_CLK_N_FS_256			0x1
#define HDMI20_RX_ACR_CLK_N_FS_512			0x2

#define HDMI20_RX_ACR_CLK_DIVIDER			0x3C
#define HDMI20_RX_ACR_CLK_DIVIDER_DIV1		0x0
#define HDMI20_RX_ACR_CLK_DIVIDER_DIV2		0x1
#define HDMI20_RX_ACR_CLK_DIVIDER_DIV4		0x2

#define HDMI20_RX_AD_MAIN_ARC_SET			0x0C
#define HDMI20_RX_AD_MAIN_ARC_SET_ENABLE	0x01
#define HDMI20_RX_AD_MAIN_PHY_ARC			0xB4
#define HDMI20_RX_AD_MAIN_PHY_ARC_DEFAULT	0x20
#define HDMI20_RX_AD_MAIN_PHY_ARC_ENABLE	0x01

#define HDMI20_RX_AD_MAIN_AUD_INFO_BYTE0	0x70
#define HDMI20_RX_AD_MAIN_AUD_INFO_PC		0x88

#define HDMI20_RX_AD_INFO_CLR_AUDIO				0x11C
#define HDMI20_RX_AD_INFO_CLR_AUDIO_ENABLE	0x00000008
#define HDMI20_RX_AD_INFO_CLR_AUDIO_DISABLE	0x00000000

#define HDMI20_RX_AD_MAIN_AUD_INFO_CLR_SEL	0x06C
#define HDMI20_RX_AD_MAIN_AUD_INFO_CLR_SEL_ENABLE	0x00000001
#define HDMI20_RX_AD_MAIN_AUD_INFO_CLR_SEL_DISABLE	0x00000000

#define HDMI20_RX_AD_INTR_CLR_AUDIO				0x118
#define HDMI20_RX_AD_INTR_CLR_AUDIO_ENABLE	0x00001800
#define HDMI20_RX_AD_INTR_CLR_AUDIO_DISABLE	0x00000000

#define HDMI20_RX_DMI_SW_RST				0xFF0
#define HDMI20_RX_DMI_SW_RST_AUDIO			0x10

#define HDMI20_RX_AUD_PLL_CTRL				0x208

#define HDMI20_RX_AUD_FIFO_STS				0x27C
#define HDMI20_RX_AUD_FIFO_STS_PASS			0x04
#define HDMI20_RX_AUD_FIFO_ISTS				0xFB0
#define HDMI20_RX_AUD_FIFO_ISTS_PASS		0x04
#define HDMI20_RX_AUD_FIFO_ICLR				0xFB8
#define HDMI20_RX_AUD_FIFO_ICLR_ENABLE		0x1F
#define HDMI20_RX_AUD_FIFO_FILLSTS1			0x25C

#define HDMI20_RX_PDEC_ACR_CTS					0x390
#define HDMI20_RX_PDEC_ACR_N					0x394

#define HDMI20_RX_PDEC_AIF_PB0					0x3C8
#define HDMI20_RX_PDEC_AIF_PB0_BIT_MASK_CHA_CNT 0x00000007

#define HDMI20_RX_PDEC_STS						0x360
#define HDMI20_RX_PDEC_STS_BIT_MASK_AUD_LAYOUT 	0x800

#define HDMI20_RX_PDEC_AUD_STS					0x364
#define HDMI20_RX_PDEC_AUD_STS_HBR			 	0x8

#define HDMI20_RX_AUD_CTRL						0x200
#define HDMI20_RX_AUD_CTRL_CONF					0x00000060
#define HDMI20_RX_AUD_CTRL_HBR					0x00000000

#define HDMI20_RX_AUD_CLK_CTRL					0x214
#define HDMI20_RX_AUD_CLK_CTRL_CONF				0x00000003

#define HDMI20_RX_AUD_PLL_CTRL					0x208
#define HDMI20_RX_AUD_PLL_CTRL_CONF				0x00000000

#define HDMI20_RX_HDMI_CKM_EVLTM				0x094
#define HDMI20_RX_HDMI_CKM_EVLTM_CONF			0x0016FFF0

#define HDMI20_RX_HDMI_CKM_F					0x098
#define HDMI20_RX_HDMI_CKM_F_CONF				0xF98A0190

#define HDMI20_RX_AUD_FIFO_TH					0x244
#define HDMI20_RX_AUD_FIFO_TH_CONF				0x01401008

#define HDMI20_RX_PDEC_ASP_CTRL					0x340
#define HDMI20_RX_PDEC_ASP_CTRL_CONF			0x0000007C

#define HDMI20_RX_AUD_FIFO_CTRL					0x240
#define HDMI20_RX_AUD_FIFO_CTRL_CONF			0x00010000

#define HDMI20_RX_HDMI_RESMPL_CTRL				0x0A4
#define HDMI20_RX_HDMI_RESMPL_CTRL_CONF			0x00000001

#define HDMI20_RX_AUD_MUTE_CTRL					0x258
#define HDMI20_RX_AUD_MUTE_CTRL_CONF			0x007004A8

#define HDMI20_RX_AUD_PAO_CTRL					0x264
#define HDMI20_RX_AUD_PAO_CTRL_CONF				0x00006000
#define HDMI20_RX_AUD_PAO_CTRL_HBR				0x00006001

#define HDMI20_RX_PDEC_AIF_CTRL					0x3C0
#define HDMI20_RX_PDEC_AIF_CTRL_CONF			0x00000100

#define HDMI20_RX_AUD_OUTPUT_MUTE_CTRL			0x260
#define HDMI20_RX_AUD_OUTPUT_MUTE_CTRL_MUTE		0x000001E0
#define HDMI20_RX_AUD_OUTPUT_MUTE_CTRL_UNMUTE	0x00000001

#define HDMI20_RX_AUD_CHEXTR_CTRL				0x254
#define HDMI20_RX_AUD_CHEXTR_CTRL_8CH			0x000000FC
#define HDMI20_RX_AUD_CHEXTR_CTRL_6CH_1			0x00000094
#define HDMI20_RX_AUD_CHEXTR_CTRL_6CH_2			0x000000B0
#define HDMI20_RX_AUD_CHEXTR_CTRL_6CH_3			0x000000D4
#define HDMI20_RX_AUD_CHEXTR_CTRL_4CH_1			0x00000084
#define HDMI20_RX_AUD_CHEXTR_CTRL_4CH_2			0x00000090
#define HDMI20_RX_AUD_CHEXTR_CTRL_4CH_3			0x000000D0
#define HDMI20_RX_AUD_CHEXTR_CTRL_2CH			0x00000080
#define HDMI20_RX_AUD_CHEXTR_CTRL_HBR			0x000000FF
#define HDMI20_RX_AUD_CHEXTR_CTRL_AUTO			0x0000007C

/* HDMI1.4 code defined constant : from deletion of HDMI1.4 codes */
// define audio state
#define HDMI_AUDIO_INIT_STATE						0	///<  Audio ISR Initialize or No SCDT State.
#define HDMI_AUDIO_INTERRUPT_STATE					1	///<  Audio ISR Assert State.
#define HDMI_AUDIO_CLOCK_SET_STATE					2	///<  Audio ACR Clock Set State.
#define HDMI_AUDIO_GET_INFO_STATE				   14	///<  Audio ISR and Get Info. State.(count value)
#define HDMI_AUDIO_STABLE_STATE					   15	///<  Audio ISR and sampling frequency Stable State.(count value)
#define HDMI_AUDIO_RECHECK_TIME			   		   20	///<  1 second, DDI calls a every 20 ms.
#define HDMI_AUDIO_BURST_INFO_RECHECK_80MS 		   80	///<  80 mili-second to check next burst info interrupt.

#define DEBUG_HDMI_AUDIO_MSG_PRINT_TIME			  500	///<  1 second, DDI calls a every 20 ms.

#define HDMI_AUDIO_RECHECK_TIME_500MS 			(500/HDMI_THREAD_TIMEOUT)	///<  0.5 second, Thread calls a every 20 ms.
#define HDMI_AUDIO_FREQ_ERROR_TIME_500MS 		(500/HDMI_THREAD_TIMEOUT)	///<  0.5 second, Thread calls a every 20 ms.
#define HDMI_AUDIO_RECHECK_TIME_1S 				(1000/HDMI_THREAD_TIMEOUT)	///<  1.0 second, Thread calls a every 20 ms.
#define HDMI_AUDIO_PORT_STABLE_TIME_5S 			(5000/HDMI_THREAD_TIMEOUT)	///<  5.0 second, Thread calls a every 20 ms.
#define DEBUG_HDMI_AUDIO_MSG_PRINT_TIME_1S		(1000/HDMI_THREAD_TIMEOUT)	///<  1.0 second, Thread calls a every 20 ms.
#define DEBUG_HDMI_AUDIO_MSG_PRINT_TIME_10S		(10000/HDMI_THREAD_TIMEOUT)	///<  10 seconds, Thread calls a every 20 ms.
#define DEBUG_HDMI_AUDIO_MSG_PRINT_TIME_100S	(100000/HDMI_THREAD_TIMEOUT)///<  100 seconds, Thread calls a every 20 ms.

// define audio interrupt mask
#define HDMI_AUDIO_INTERRUPT_BIT_MASK	   0x0000E000	///<  intr_2npcm_chg, intr_2pcm_chg, intr_fs_chg
//#define HDMI_AUDIO_INTERRUPT_BIT_MASK	   0x1000E000	///<  intr_achst_5b_chg_int, intr_2npcm_chg, intr_2pcm_chg, intr_fs_chg

// define HDMI Audio Sample Word PCM & non-PCM sample
#define HDMI_AUDIO_SAMPLE_NON_PCM_MASK			0x02	///< 0 : linear PCM, 1 : other purpose

// define HDMI Audio Copyright Cp Bit Mask(BYTE0)
#define HDMI_AUDIO_CP_BIT_MASK					 0x04	///< 0 : copyright, 1 : no copyright

// define HDMI Audio Copyright L Bit Mask(BYTE1)
#define HDMI_AUDIO_L_BIT_MASK					 0x80	///< 0 : Home copy, 1 : Pre-recorded

// define HDMI Audio Sample Frequency according to IEC60958 channel status BYTE3(IEC60958-3 Third edition, 2006-05 spec.)
#define HDMI_AUDIO_SAMPLE_BIT_MASK				 0x0F	///< Bit 0 ~ 3
#define HDMI_AUDIO_SAMPLE_22_05KHZ				    4	///< 22.05 Kbps
#define HDMI_AUDIO_SAMPLE_24_KHZ					6	///< 24 Kbps
#define HDMI_AUDIO_SAMPLE_32_KHZ					3	///< 32 Kbps
#define HDMI_AUDIO_SAMPLE_44_1KHZ					0	///< 44.1 Kbps
#define HDMI_AUDIO_SAMPLE_48_KHZ					2	///< 48 Kbps
#define HDMI_AUDIO_SAMPLE_88_2KHZ					8	///< 88.2 Kbps
#define HDMI_AUDIO_SAMPLE_96_KHZ				   10	///< 96 Kbps
#define HDMI_AUDIO_SAMPLE_176_4KHZ				   12	///< 176.4 Kbps
#define HDMI_AUDIO_SAMPLE_192_KHZ				   14	///< 192 Kbps
#define HDMI_AUDIO_SAMPLE_768_KHZ					9	///< 768 Kbps

// Used for high bite rate transmission using IEC60958 protocol defined in 61883-6.
#define HDMI_AUDIO_EXT_SAMPLE_BIT_MASK			 0x3F	///< Bit 0 ~ 3, Bit 6~7
#define HDMI_AUDIO_EXT_SAMPLE_384_KHZ				5	///< 384 Kbps
#define HDMI_AUDIO_EXT_SAMPLE_1536_KHZ			   21	///< 1536 Kbps
#define HDMI_AUDIO_EXT_SAMPLE_1024_KHZ			   53	///< 1024 Kbps
#define HDMI_AUDIO_EXT_SAMPLE_3528_KHZ			   13	///< 3528 Kbps
#define HDMI_AUDIO_EXT_SAMPLE_7056_KHZ			   45	///< 7056 Kbps
#define HDMI_AUDIO_EXT_SAMPLE_14112_KHZ			   29	///< 14112 Kbps
#define HDMI_AUDIO_EXT_SAMPLE_64_KHZ			   11	///< 64 Kbps
#define HDMI_AUDIO_EXT_SAMPLE_128_KHZ			   43	///< 128 Kbps
#define HDMI_AUDIO_EXT_SAMPLE_256_KHZ			   27	///< 256 Kbps
#define HDMI_AUDIO_EXT_SAMPLE_512_KHZ			   59	///< 512 Kbps

// define HDMI Audio Data-Types according to IEC61937-2 Burst Info Preamble C(Pc)(IEC61937-2 First edition, 2004-03 spec.)
#define BURST_INFO_AUDIO_TYPE_BIT_MASK		   0x001F	///< Bit 4 - 0
#define BURST_INFO_AUDIO_TYPE_NULL					0	///<Null Data
#define BURST_INFO_AUDIO_TYPE_AC3					1	///<AC-3 data
#define BURST_INFO_AUDIO_TYPE_SMPTE_338M			2	///<Refer to SMPTE 338M
#define BURST_INFO_AUDIO_TYPE_PAUSE					3	///<Pause
#define BURST_INFO_AUDIO_TYPE_MPEG1_L1				4	///<MPEG-1 layer-1 data
#define BURST_INFO_AUDIO_TYPE_MPEG1_L23				5	///<MPEG-1 layer-2 or -3 data or MPEG-2 without extension
#define BURST_INFO_AUDIO_TYPE_MPEG2_EXT				6	///<MPEG-2 data with extension
#define BURST_INFO_AUDIO_TYPE_MPEG2_AAC				7	///<MPEG-2 AAC
#define BURST_INFO_AUDIO_TYPE_MPEG2_L1				8	///<MPEG-2, layer-1 low sampling frequency
#define BURST_INFO_AUDIO_TYPE_MPEG2_L2				9	///<MPEG-2, layer-2 low sampling frequency
#define BURST_INFO_AUDIO_TYPE_MPEG2_L3			   10	///<MPEG-2, layer-3 low sampling frequency
#define BURST_INFO_AUDIO_TYPE_DTS_I			   	   11	///<DTS type I
#define BURST_INFO_AUDIO_TYPE_DTS_II			   12	///<DTS type II
#define BURST_INFO_AUDIO_TYPE_DTS_III			   13	///<DTS type III
#define BURST_INFO_AUDIO_TYPE_ATRAC			   	   14	///<ATRAC
#define BURST_INFO_AUDIO_TYPE_ATRAC_23			   15	///<ATRAC 2/3
#define BURST_INFO_AUDIO_TYPE_ATRAC_X			   16	///<ATRAC-X
#define BURST_INFO_AUDIO_TYPE_DTS_IV			   17	///<DTS type IV
#define BURST_INFO_AUDIO_TYPE_WMA_I_IV			   18	///<WMA type I ~ IV
#define BURST_INFO_AUDIO_TYPE_MPEG2_AAC_LOW	       19	///<MPEG-2 AAC low sampling frequency
#define BURST_INFO_AUDIO_TYPE_MPEG4_AAC	       	   20	///<MPEG-4 AAC
#define BURST_INFO_AUDIO_TYPE_AC3_ENHANCED		   21	///<AC-3 Enhanced
#define BURST_INFO_AUDIO_TYPE_MAT				   22	///<MAT
														///<23-26 Reserved
														///<27-30 Refer to SMPTE 338M
														///<31 Extended data-type

#define  BURST_INFO_PAYLOAD_ERROR_BIT_MASK	   0x0080	///<Error-flag indicationg that the burst-payload may contain errors
#define  BURST_INFO_DEPENDENT_INFO_BIT_MASK	   0x1F00	///<Data-type-dependent info.
#define  BURST_INFO_STREAM_NUMBER_BIT_MASK	   0xD000	///<Bitstream number

#define HDMI_DEEP_COLOR_8BIT						0	///<  Deep Color 8bit
#define HDMI_DEEP_COLOR_10BIT						1	///<  Deep Color 8bit
#define HDMI_DEEP_COLOR_12BIT						2	///<  Deep Color 8bit

// define CEA-861-E Audio Infoframe.
#define HDMI_INFO_AUDIO_TYPE_CODE				 0x04	///< InfoFrame Type = 0x04
#define HDMI_INFO_AUDIO_VERSION_NUM				 0x01	///< Version = 0x01
#define HDMI_INFO_AUDIO_LENGTH					 0x0A	///< Length  = 0x0A

// define HDMI Audio Coding-Types according to CEA-861-E Audio Infoframe.
#define HDMI_INFO_AUDIO_TYPE_BIT_SHIFT		   	    4	///< Bit 4 ~ 7, CT3 ~ CT0, Data Byte 1
#define HDMI_INFO_AUDIO_TYPE_BIT_MASK		   	 0x0F	///< Bit 4 ~ 7, CT3 ~ CT0, Data Byte 1
#define HDMI_INFO_AUDIO_TYPE_REFER_HEADER	 		0	///< Refer to Stream Header
#define HDMI_INFO_AUDIO_TYPE_PCM					1	///< PCM
#define HDMI_INFO_AUDIO_TYPE_AC3					2	///< AC3
#define HDMI_INFO_AUDIO_TYPE_MPEG_1					3	///< MPEG-1
#define HDMI_INFO_AUDIO_TYPE_MP3					4	///< MP3
#define HDMI_INFO_AUDIO_TYPE_MPEG2					5	///< MPEG2
#define HDMI_INFO_AUDIO_TYPE_AAC_LC					6	///< AAC LC
#define HDMI_INFO_AUDIO_TYPE_DTS					7	///< DTS
#define HDMI_INFO_AUDIO_TYPE_ATRAC					8	///< ATRAC
#define HDMI_INFO_AUDIO_TYPE_DSD					9	///< DSD
#define HDMI_INFO_AUDIO_TYPE_E_AC_3			   	   10	///< E-AC-3
#define HDMI_INFO_AUDIO_TYPE_DTS_HD			   	   11	///< DTS-HD
#define HDMI_INFO_AUDIO_TYPE_MLP			   	   12	///< MLP
#define HDMI_INFO_AUDIO_TYPE_DST			       13	///< DST
#define HDMI_INFO_AUDIO_TYPE_WMA_PRO			   14	///< WMA_PRO
#define HDMI_INFO_AUDIO_TYPE_REFER_EXT			   15	///< Refer to Audio Coding Extension Type

// define HDMI Audio Coding-Types according to CEA-861-E Audio Infoframe.
#define HDMI_INFO_AUDIO_EXT_TYPE_BIT_SHIFT		   	0	///< Bit 0 ~ 4, CXT4 ~ CXT0, Data Byte 3
#define HDMI_INFO_AUDIO_EXT_TYPE_BIT_MASK		 0x1F	///< Bit 0 ~ 4, CXT4 ~ CXT0, Data Byte 3
#define HDMI_INFO_AUDIO_EXT_TYPE_REFER_CT			0	///< Refer to Audio Coding Type
#define HDMI_INFO_AUDIO_EXT_TYPE_HE_AAC				1	///< HE-AAC
#define HDMI_INFO_AUDIO_EXT_TYPE_HE_AACV2			2	///< HE-AAC V2
#define HDMI_INFO_AUDIO_EXT_TYPE_MPEG_SUR			3	///< MPEG Surround

// define HDMI Audio Sample Frequency according to CEA-861-E Audio Infoframe.
#define HDMI_INFO_AUDIO_SAMPLE_BIT_SHIFT		    2	///< Bit 4 ~ 2, SF2 ~ SF0, Data Byte 2
#define HDMI_INFO_AUDIO_SAMPLE_BIT_MASK			 0x07	///< Bit 4 ~ 2, SF2 ~ SF0, Data Byte 2
#define HDMI_INFO_AUDIO_SAMPLE_REFER_HEADER		    0	///< Refer to Stream Header
#define HDMI_INFO_AUDIO_SAMPLE_32_KHZ			    1	///< 32 Kbps
#define HDMI_INFO_AUDIO_SAMPLE_44_1KHZ				2	///< 44.1 Kbps
#define HDMI_INFO_AUDIO_SAMPLE_48_KHZ				3	///< 48 Kbps
#define HDMI_INFO_AUDIO_SAMPLE_88_2KHZ				4	///< 88.2 Kbps
#define HDMI_INFO_AUDIO_SAMPLE_96_KHZ				5	///< 96 Kbps
#define HDMI_INFO_AUDIO_SAMPLE_176_4KHZ				6	///< 176.4 Kbps
#define HDMI_INFO_AUDIO_SAMPLE_192_KHZ				7	///< 192 Kbps




/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
	/* DBG */
	HDMI20__AUD_DEBUG = 0,
	HDMI20__AUD_LINE_DBG,
	HDMI20__AUD_CNT_DBG,
	HDMI20__AUD_IRQ_DBG,
	HDMI20__AUD_CSD_IRQ_DBG,

	/* Count */
	HDMI20__AUD_COUNT,
	HDMI20__AUD_STANDBY_TIME,
	HDMI20__AUD_STABLE_TIME,
	HDMI20__AUD_STABLE,
	HDMI20__AUD_FIFO_ERR_MUTE_TIME,
	HDMI20__AUD_CH_MAP_STANDBY_TIME,
	HDMI20__AUD_CH_MAP_MAX,
	HDMI20__AUD_IRQ_FIFO_ERR_MAX,
	HDMI20__AUD_ACR_ERR_MAX,
	HDMI20__AUD_FORCE_MUTE_TIME,
	HDMI20__AUD_ACR_RESET_TIME,

	/* Control */
	HDMI20__AUD_CONTROL,
	HDMI20__AUD_IGNORE_ERR,
	HDMI20__AUD_IGNORE_IRQ,
	HDMI20__AUD_FORCE_UNMUTE,
	HDMI20__AUD_FORCE_TYPE,
	HDMI20__AUD_FORCE_FS,
	HDMI20__AUD_FORCE_CHANNEL,
	HDMI20__AUD_FORCE_STREAM,
	HDMI20__AUD_FORCE_ACR_RESET,
#if 0
	HDMI20__AUD_FORCE_UNKNOWN_TYPE,
#endif
	HDMI20__AUD_IRQ_DISABLE_PCD,
	HDMI20__AUD_IRQ_DISABLE_SPDIF,
	HDMI20__AUD_FIFO_ADJUST,
	HDMI20__AUD_REG_PRINT_REPEAT,

	/* Info */
	HDMI20__AUD_INFORMATION,
	HDMI20__AUD_DATA,
	HDMI20__AUD_N_CTS,
	HDMI20__AUD_INFO,
	HDMI20__AUD_CNT,
	HDMI20__AUD_FIFO,
	HDMI20__AUD_MUTE,
	HDMI20__AUD_HBR,
	HDMI20__AUD_PC,
	HDMI20__AUD_REG,
	HDMI20__AUD_READ_TOP_REG,
	HDMI20__AUD_READ_CTRL_REG,

	/* DBG Init */
	HDMI20__AUD_INITIALIZE,
	HDMI20__AUD_DEBUG_INIT,
	HDMI20__AUD_COUNT_INIT,
	HDMI20__AUD_CONTROL_INIT,
	HDMI20__AUD_INFORMATION_INIT,
	HDMI20__AUD_ALL_DEBUG_INIT,
	
	HDMI20__DEV_AUD_CONTROL_LIST_MAXNUM
} HDMI20_DEV_AUD_CONTROL_LIST_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
/* IOCTL */
int HDMI20_HAL_Rx_GetAudioInfo(UINT8 port, LX_HDMI_AUDIO_INFO_T *pHdmiAudioInfo, int size);
int HDMI20_HAL_Rx_GetAudioCopyInfo(UINT8 port, LX_HDMI_AUDIO_COPY_T *pHdmiCopyInfo, int size);
int HDMI20_HAL_Rx_Set_HDMIARC(UINT8 port, BOOLEAN bOnOff);

/* DBG */
int HDMI20_HAL_Rx_Get_DebugAudioInfo(UINT8 port, LX_HDMI_DEBUG_AUDIO_INFO_T *pDebugAudioInfo, int size);
int HDMI20_HAL_Rx_AudioForceInfoControl(UINT8 port);
int HDMI20_HAL_Rx_AudioInfoPrint(UINT8 port);
int HDMI20_HAL_Rx_AudioDebugIntialize(UINT8 port);

/* Function */
int HDMI20_HAL_Rx_Set_AudioMute(UINT8 port, LX_HDMI_MUTE_CTRL_T *pMuteCtrl, int size);
void HDMI20_HAL_Rx_Set_Audio_Configure(UINT8 port, int isUD);
UINT32 HDMI20_HAL_Rx_Get_PLLFreqRange(UINT32 tmds_clk);
void HDMI20_HAL_Rx_Update_AudioCtsNparam(int port, int clear);
int HDMI20_HAL_Rx_Get_AudioType(UINT8 port, LX_HDMI_AUDIO_TYPE_T *audioType);
int HDMI20_HAL_Rx_Get_AudioInfo(UINT8 port);
int HDMI20_HAL_Rx_Set_AudioReset(UINT8 port);
int HDMI20_HAL_Rx_Set_AudioMuteControl(UINT8 port, BOOLEAN mute);
int HDMI20_HAL_Rx_Get_AudioFreqFromTMDSClock(UINT8 port, unsigned int *samplingFreq);
int HDMI20_HAL_Rx_Get_AudioCountOfChannel(UINT8 port, int *countOfChannel);
int HDMI20_HAL_Rx_Get_AudioStream(UINT8 port, LX_HDMI_AUDIO_STREAM_T *stream);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

