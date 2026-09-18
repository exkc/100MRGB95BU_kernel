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



/** @file HDMI2020_kapi.h
 *
 *  application interface header for HDMI20 device
 *
 *  @author		won.hur (won.hur@lge.com)
 *  @version	1.0	
 *  @date		2014.04.29
 *
 *  @addtogroup lg115x_HDMI20
 *	@{
 */

#ifndef	_HDMI20_KAPI_H_
#define	_HDMI20_KAPI_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#ifdef CONFIG_COMPAT
#include <linux/compat.h>
#endif
#include "base_types.h"
#include "hdmi_kapi.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define	HDMI20_IOC_MAGIC		'h'

#define HDMI21_NUM_OF_RX_PORTS		5	// Leave this for Legacy support

#define HDMI21_NUM_OF_MAX_PORTS		5
#define HDMI21_NUM_OF_PORTS_O20		5	
#define HDMI21_NUM_OF_PORTS_E60		4
#define HDMI21_NUM_OF_PORTS_O22		4
#define HDMI21_NUM_OF_PORTS_M23		4
#define HDMI21_NUM_OF_PORTS_O24		4
#define HDMI21_NUM_OF_PORTS_O26		4

#define HDMI21_NUM_OF_FRL_CH		4
#define HDMI20_NUM_OF_TMDS_CH_LINK	3

/* SCDC Device Description */
#if 0
#define HDMI20_SCDC_CHIP_DESCRIPTION_0	'S GL' 	/* LG S */
#define HDMI20_SCDC_CHIP_DESCRIPTION_1	'  CI'  /* IC   */
#else
#define HDMI20_SCDC_CHIP_DESCRIPTION_0 ((uint32_t)'S' << 24 | (uint32_t)' ' << 16 | (uint32_t)'G' << 8 | (uint32_t)'L')
#define HDMI20_SCDC_CHIP_DESCRIPTION_1 ((uint32_t)' ' << 24 | (uint32_t)' ' << 16 | (uint32_t)'C' << 8 | (uint32_t)'I')
#endif

#define HDMI20_SCDC_CHIP_CHARACTER_H15_H	'0'
#define HDMI20_SCDC_CHIP_CHARACTER_H15_L	'1'

#define HDMI20_SCDC_CHIP_CHARACTER_M16_H	'0'
#define HDMI20_SCDC_CHIP_CHARACTER_M16_L	'2'

#define HDMI20_SCDC_CHIP_CHARACTER_M16P_H	'0' /* M17 A0 */
#define HDMI20_SCDC_CHIP_CHARACTER_M16P_L	'3' /* M17 A0 */

#define HDMI20_SCDC_CHIP_CHARACTER_M16P2_H	'0' /* M17 C0 */
#define HDMI20_SCDC_CHIP_CHARACTER_M16P2_L	'4' /* M17 C0 */

#define HDMI20_SCDC_CHIP_CHARACTER_O18_H	'0'
#define HDMI20_SCDC_CHIP_CHARACTER_O18_L	'5'

#define HDMI20_SCDC_CHIP_CHARACTER_M16P3_H	'0' /* M19 */
#define HDMI20_SCDC_CHIP_CHARACTER_M16P3_L	'6' /* M19 */

#define HDMI20_SCDC_CHIP_CHARACTER_O20_H	'0'
#define HDMI20_SCDC_CHIP_CHARACTER_O20_L	'7'

#define HDMI20_SCDC_CHIP_CHARACTER_E60_H	'0'
#define HDMI20_SCDC_CHIP_CHARACTER_E60_L	'8'

#define HDMI20_SCDC_CHIP_CHARACTER_O22_H	'0'
#define HDMI20_SCDC_CHIP_CHARACTER_O22_L	'9'

#define HDMI20_SCDC_CHIP_CHARACTER_M23_H	'1'
#define HDMI20_SCDC_CHIP_CHARACTER_M23_L	'0'

#define HDMI20_SCDC_CHIP_CHARACTER_O24_H	'1'
#define HDMI20_SCDC_CHIP_CHARACTER_O24_L	'1'

#define HDMI20_SCDC_CHIP_CHARACTER_O26_H	'1'
#define HDMI20_SCDC_CHIP_CHARACTER_O26_L	'2'



/* Legacy HDMI2.0 : H15/H15P/M16/M16P/M16PP/O18/M16P3 */
#define HDMI20_NUM_OF_RX_PORTS		4	
#define HDMI20_NUM_OF_TX_PORTS		1	
#define HDMI20_NUM_OF_PORTS		(HDMI20_NUM_OF_TX_PORTS + HDMI20_NUM_OF_RX_PORTS)

#define HDMI20_MAX_LENGTH_OF_DBG_MSG 128

/** Receiver key selection size - 40 bits */
#define HDMI20_HDCP_BKSV_SIZE	(2 *  1)
/** Encrypted keys size - 40 bits x 40 keys */
#define HDMI20_HDCP_KEYS_SIZE	(2 * 40)
#define HDMI20_HDCP_CUSTOMER_SIZE	288

/** HDCP1.4 Repeater Handle */
#define HDMI20_HDCP14_RPRX_MAX_DEVICE	(127)


/* For Audio */
#define HDMI20_BURST_INFO_AUDIO_TYPEBIT_MASK		   0x001F	///< Bit 4 - 0

/* For HDMI Dev Contoller */
#define HDMI20_DEV_CONTROL_TITLE_LENGTH			60
#define HDMI20_DEV_CONTROL_DESCRIPTION_LENGTH	120

/* TV Lab Data Packet Max Length */
#define HDMI20_PACKET_DATA_MAX_LENGTH 28
/*----------------------------------------------------------------------------------------
	IO comand naming rule  : MODULE_IO[R][W]_COMMAND
----------------------------------------------------------------------------------------*/
/* HDMI20 Link Control */
#ifndef CONFIG_COMPAT
#define HDMI20_IOC_COMMAND			_IOWR(HDMI20_IOC_MAGIC,  0, LX_HDMI20_CMD_T *)
#define HDMI20_IOC_SET_LOGM			_IOWR(HDMI20_IOC_MAGIC,  1, LX_HDMI20_LOGM_SETTING_T *)
#else
#define HDMI20_IOC_COMMAND			_IOWR(HDMI20_IOC_MAGIC,  0, compat_uptr_t)
#define HDMI20_IOC_SET_LOGM			_IOWR(HDMI20_IOC_MAGIC,  1, compat_uptr_t)
#endif
#define HDMI20_IOC_MAXNR			200	

/* HDCP2.2 Control */
#ifndef CONFIG_COMPAT
#define ESM_HOSTLIB_COMMAND _IOWR('q', 1, esm_hostlib_cmd_t *)
#define ESM_HOSTLIB_STATUS  _IOWR('q', 2, esm_hostlib_status_t *)
#else
#define ESM_HOSTLIB_COMMAND _IOWR('q', 1, compat_uptr_t)
#define ESM_HOSTLIB_STATUS  _IOWR('q', 2, compat_uptr_t)
#endif


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/* IOCTL Commands */
#define HDMI20_CMD_RX_INITIALIZE			1
#define HDMI20_CMD_RX_UNINITIALIZE			2
#define HDMI20_CMD_RX_GET_TIMINGINFO		5
#define HDMI20_CMD_RX_GET_AVIINFO			6
#define HDMI20_CMD_RX_GET_SPDINFO			7
#define HDMI20_CMD_RX_GET_VSIINFO			8
#define HDMI20_CMD_RX_GET_COLORINFO			9
#define HDMI20_CMD_RX_GET_AKSVDATA			10	
#define HDMI20_CMD_RX_GET_PHYSTATUS			11
#define HDMI20_CMD_RX_SET_RESETTIMINGINFO	12
#define HDMI20_CMD_RX_SET_EDID				13
#define HDMI20_CMD_RX_GET_EDID				14
#define HDMI20_CMD_RX_SET_HDCP14			15
#define HDMI20_CMD_RX_GET_HDCP14			16
#define HDMI20_CMD_RX_SET_ENABLEHPD			17
#define HDMI20_CMD_RX_SET_ENABLEEDID		18
#define HDMI20_CMD_RX_GET_AUDIOINFO			19
#define HDMI20_CMD_RX_GET_AUDIOCOPYINFO		20
#define HDMI20_CMD_RX_SET_HDMIARC			21
#define HDMI20_CMD_RX_SET_MUTE				22
#define HDMI20_CMD_RX_GET_AUDIODBGINFO		23	

#define HDMI20_CMD_DBG_SET_PRESETS			26
#define HDMI20_CMD_RX_GET_ASPECTRATIO		27
#define HDMI20_CMD_RX_GET_HDMISTATE			28
#define HDMI20_CMD_RX_SET_HDCP22INFO		29
#define HDMI20_CMD_RX_GET_SRCINFO			30
#define HDMI20_CMD_RX_SET_PHY_ACCESS		31
#define HDMI20_CMD_RX_OPEN					32
#define HDMI20_CMD_RX_SET_ENABLE_OPERATION	33
#define HDMI20_CMD_RX_ACCESS_DEV_CTRL		40
#define HDMI20_CMD_RX_PRINT_DEV_CTRL		41
#define HDMI20_CMD_RX_ACCESS_DEV_AUD_CTRL	42
#define HDMI20_CMD_RX_PRINT_DEV_AUD_CTRL	43
#define HDMI20_CMD_RX_SET_REVERSE_HPD 		44
#define HDMI20_CMD_RX_SET_PIONEER_PLAT		45
#define HDMI20_CMD_RX_SET_PHY_AUTO_DEBUGGER 46
#define HDMI20_CMD_RX_GET_DRMINFO			47
#define HDMI20_CMD_RX_SET_RESTARTHPD		48
#define HDMI20_CMD_RX_SET_POWEROFF			49
#define HDMI20_CMD_RX_SET_DISABLE_HDMI		50
#define HDMI20_CMD_RX_SET_COUNTRYINFO		51	
#define HDMI20_CMD_RX_GET_DEV_CTRL_CNT		52
#define HDMI20_CMD_RX_GET_DEV_CTRL			53
#define HDMI20_CMD_RX_GET_HDMI_MISC			54
#define HDMI20_CMD_RX_SET_HDCP14KSVLIST		55	
#define HDMI20_CMD_RX_SET_HDMIFACTOR		56
#define HDMI20_CMD_RX_SET_ERROR_THRES		57
#define HDMI20_CMD_RX_GET_ERROR				58
#define HDMI20_CMD_RX_GET_MULTIPLE_VSI		59
#define HDMI20_CMD_RX_GET_CURRENT_VRR_FREQ	60
#define HDMI20_CMD_RX_GET_EMPACKET			61
#define HDMI20_CMD_RX_ACCESS_DEV_LINK_CTRL	62	
#define HDMI20_CMD_RX_PRINT_DEV_LINK_CTRL	63
#define HDMI20_CMD_RX_ACCESS_DEV_PHY_CTRL	64
#define HDMI20_CMD_RX_PRINT_DEV_PHY_CTRL	65
#define HDMI20_CMD_RX_DBG_TOOL				66
#define HDMI20_CMD_RX_ACCESS_DEV_EARC_CTRL	67
#define HDMI20_CMD_RX_PRINT_DEV_EARC_CTRL	68
#define HDMI20_CMD_RX_SET_DISABLE_OPERATION	69

#define HDMI20_CMD_LAST			HDMI20_CMD_RX_PRINT_DEV_EARC_CTRL
#define HDMI20_CMD_MAXNUM		(HDMI20_CMD_LAST	+ 1)		

/* COMMAND STATUS */
#define HDMI20_CMD_STATUS_PROCESS_ERROR			-7
#define HDMI20_CMD_STATUS_COPY_ERROR			-6
#define HDMI20_CMD_STATUS_IOCTL_ERROR	 		-5
#define HDMI20_CMD_STATUS_SIZE_ERROR	 		-4
#define HDMI20_CMD_STATUS_ATTRI_ERROR	 		-3
#define HDMI20_CMD_STATUS_HANDLE_ERROR 			-2
#define HDMI20_CMD_STATUS_CMD_ERROR				-1
#define HDMI20_CMD_STATUS_OK			 		 0

typedef enum
{
	HDMI21_HAL_PHY_INITIATED_ERROR	= -1,
	HDMI21_HAL_PHY_INITIATED_3G		=  0,
	HDMI21_HAL_PHY_INITIATED_6G		=  1,
	HDMI21_HAL_PHY_INITIATED_FRL_3G_3L,
	HDMI21_HAL_PHY_INITIATED_FRL_6G_3L,
	HDMI21_HAL_PHY_INITIATED_FRL_6G_4L,
	HDMI21_HAL_PHY_INITIATED_FRL_8G_4L,
	HDMI21_HAL_PHY_INITIATED_FRL_10G_4L,
	HDMI21_HAL_PHY_INITIATED_FRL_12G_4L,
	HDMI21_HAL_PHY_INITIATED_MAXNUM
} HDMI21_HAL_PHY_INITIATED_MODE_T;

typedef enum
{
	HDMI_PHY_INITIATED_ERROR = -1,
	HDMI_PHY_INITIATED_3G_M0 = 0,
	HDMI_PHY_INITIATED_3G_M1 = 1,
	HDMI_PHY_INITIATED_3G_M2 = 2,
	HDMI_PHY_INITIATED_3G_M3 = 3,
	HDMI_PHY_INITIATED_6G = 4,
	HDMI_PHY_INITIATED_FRL_3G_3L = 5,
	HDMI_PHY_INITIATED_FRL_6G_3L = 6,
	HDMI_PHY_INITIATED_FRL_6G_4L = 7,
	HDMI_PHY_INITIATED_FRL_8G_4L = 8,
	HDMI_PHY_INITIATED_FRL_10G_4L = 9,
	HDMI_PHY_INITIATED_FRL_12G_4L = 10,
	HDMI_PHY_INITIATED_FRL_10G_CTS = 11,
	HDMI_PHY_INITIATED_FRL_12G_CTS = 12,
	HDMI_PHY_INITIATED_MAXNUM
}HDMI_PHY_INIT_MODE_T;

typedef enum {
	HDMI20_DEV_CONTROL_VIDEO = 0,
	HDMI20_DEV_CONTROL_AUDIO,
	HDMI20_DEV_CONTROL_PHY,
	HDMI20_DEV_CONTROL_LINK,
	HDMI20_DEV_CONTROL_EARC,
	HDMI20_DEV_CONTROL_TABLE,
	HDMI20_DEV_CONTROL_READ_TABLE,
	HDMI20_DEV_CONTROL_WRITE_TABLE,
	HDMI20_DEV_CONTROL_MAXNUM
} HDMI20_DEV_CONTROL_TYPE_T;

typedef enum
{
	LX_HDMI20_SETTING_HPD_LOW_DURATION,
	LX_HDMI20_SETTING_TMDS_MANUAL_EQ_MODE,
	LX_HDMI20_SETTING_TMDS_MANUAL_EQ_CH0,
	LX_HDMI20_SETTING_TMDS_MANUAL_EQ_CH1,
	LX_HDMI20_SETTING_TMDS_MANUAL_EQ_CH2,
	LX_HDMI20_SETTING_TMDS_EQ_PERIOD,
	LX_HDMI20_SETTING_VIDEO_STABLE_COUNT,
	LX_HDMI20_SETTING_AUDIO_STABLE_COUNT,
	LX_HDMI20_SETTING_DISABLE_HDCP22_PORT0,
	LX_HDMI20_SETTING_DISABLE_HDCP22_PORT1,
	LX_HDMI20_SETTING_DISABLE_HDCP22_PORT2,
	LX_HDMI20_SETTING_DISABLE_HDCP22_PORT3,
	LX_HDMI20_SETTING_REAUTH_HDCP22_PORT0,
	LX_HDMI20_SETTING_REAUTH_HDCP22_PORT1,
	LX_HDMI20_SETTING_REAUTH_HDCP22_PORT2,
	LX_HDMI20_SETTING_REAUTH_HDCP22_PORT3,
	LX_HDMI20_SETTING_ON_TO_RXSENSE_TIME,
	LX_HDMI20_SETTING_RXSENSE_TO_HPD_TIME,
	LX_HDMI20_SETTING_PORT0_MANUAL_EQ_MODE,
	LX_HDMI20_SETTING_PORT0_MANUAL_EQ_CH0,
	LX_HDMI20_SETTING_PORT0_MANUAL_EQ_CH1,
	LX_HDMI20_SETTING_PORT0_MANUAL_EQ_CH2,
	LX_HDMI20_SETTING_PORT1_MANUAL_EQ_MODE,
	LX_HDMI20_SETTING_PORT1_MANUAL_EQ_CH0,
	LX_HDMI20_SETTING_PORT1_MANUAL_EQ_CH1,
	LX_HDMI20_SETTING_PORT1_MANUAL_EQ_CH2,
	LX_HDMI20_SETTING_PORT2_MANUAL_EQ_MODE,
	LX_HDMI20_SETTING_PORT2_MANUAL_EQ_CH0,
	LX_HDMI20_SETTING_PORT2_MANUAL_EQ_CH1,
	LX_HDMI20_SETTING_PORT2_MANUAL_EQ_CH2,
	LX_HDMI20_SETTING_PORT3_MANUAL_EQ_MODE,
	LX_HDMI20_SETTING_PORT3_MANUAL_EQ_CH0,
	LX_HDMI20_SETTING_PORT3_MANUAL_EQ_CH1,
	LX_HDMI20_SETTING_PORT3_MANUAL_EQ_CH2,
	LX_HDMI20_SETTING_PORT0_MANUAL_EQ_CH3,
	LX_HDMI20_SETTING_PORT1_MANUAL_EQ_CH3,
	LX_HDMI20_SETTING_PORT2_MANUAL_EQ_CH3,
	LX_HDMI20_SETTING_PORT3_MANUAL_EQ_CH3,
	LX_HDMI20_SETTING_MAXNUM,
} LX_HDMI20_SETTING_TYPE_T;

typedef enum
{
	LX_HDMI20_ERROR_GCP_ERROR,
	LX_HDMI20_ERROR_HDCP22_REAUTH,
	LX_HDMI20_ERROR_TMDS_ERROR,
	LX_HDMI20_ERROR_PHY_LOW_RANGE,
	LX_HDMI20_ERROR_PHY_ABNORMAL,
	LX_HDMI20_ERROR_CED_ERROR,
	LX_HDMI20_ERROR_AUDIO_BUFFER,
	LX_HDMI20_ERROR_UNSTABLE_SYNC,
	LX_HDMI20_ERROR_MAXNUM,
	LX_HDMI20_ERROR_FAILED = 0xFF,
} LX_HDMI20_ERROR_TYPE_T;


typedef struct
{
	UINT32 errorVal;
	UINT32 param_A;
	UINT32 param_B;
} LX_HDMI20_ERROR_SETTING_T;

typedef struct {
	char index[HDMI20_DEV_CONTROL_TITLE_LENGTH];
	UINT32 value;
	char description[HDMI20_DEV_CONTROL_DESCRIPTION_LENGTH];
} HDMI20_DEV_CONTROL_T;

typedef struct 
{
	int 	command;
	union
	{
		void*	handle;
		UINT32	compat_handle;
		UINT64	sizer;
	};
	int		size;
	int		attributes;
	int		status;
} LX_HDMI20_CMD_T;

typedef struct 
{
	UINT32 logLevel;
	BOOLEAN onOff;	 
} LX_HDMI20_LOGM_SETTING_T;

typedef struct
{
	unsigned int addr;
	unsigned int value;
} LX_HDMI20_REG_T;

typedef struct
{
	char index[100];
	LX_HDMI20_REG_T* regs;
	UINT32 count;
} LX_HDMI20_REG_SETTING_T;

typedef struct
{
	LX_HDMI20_SETTING_TYPE_T type;
	UINT32 value1;
	UINT32 value2;
	UINT32 value3;
} LX_HDMI20_SETTING_FACTOR_T;

typedef struct
{
	LX_HDMI20_REG_SETTING_T	*pRegSettings;
	UINT32 number_of_modes;
} LX_HDMI20_REG_SETS_T;

typedef struct 
{
	BOOLEAN repeat;
	UINT32 seed;
	/**
	 * Receiver key selection
	 * @note 0: high order, 1: low order
	 */
	UINT32 bksv[HDMI20_HDCP_BKSV_SIZE];
	/**
	 * Encrypted keys
	 * @note 0: high order, 1: low order
	 */
	UINT32 keys[HDMI20_HDCP_KEYS_SIZE];
} LX_HDMI20_HDCP14_DATA_T;

typedef struct
{
	UINT32 depth;
	UINT32 count;
	UINT32 ksvList[HDMI20_HDCP14_RPRX_MAX_DEVICE * 2];	
} LX_HDMI20_HDCP14_RP_T;

typedef enum
{
	HDMI20_HAL_IPC_REQUEST_HPD = 0x00000001,
	HDMI20_HAL_IPC_GOOD_VIDEO  = 0x00000002,
	HDMI20_HAL_IPC_BAD_VIDEO   = 0x00000004,
	HDMI20_HAL_IPC_RESET_VIDEO = 0x00000008,
	HDMI20_HAL_IPC_HDCP22_NCAP = 0x00000010,
	HDMI20_HAL_IPC_HDCP22_VIDEOCON = 0x00000020,
	HDMI20_HAL_IPC_HDCP14_AKSV = 0x00000040,
	HDMI20_HAL_IPC_AKEMASK = 0x00000080,
	HDMI20_HAL_IPC_MAXNUM
} HDMI20_HAL_IPC_T;
	
typedef struct
{
	int number_of_ports;
	unsigned int ipc_address[HDMI20_NUM_OF_PORTS];
} LX_HDMI20_INIT_T;

typedef struct
{
	BOOLEAN isHDMI20Device;
} LX_HDMI20_SRCINFO_T;

typedef struct
{
	BOOLEAN isWrite;
	UINT8 slaveAddr;
	UINT32 regAddr;
	UINT32 data;
	UINT8 regBank;
} LX_HDMI20_PHY_ACCESS_T;

typedef struct
{
	BOOLEAN isSteady;
	BOOLEAN isDVI;
	BOOLEAN isRestartState;
	UINT32	numOfActivePort;
} LX_HDMI20_OP_STATUS_T;

typedef struct
{
	BOOLEAN isReset;
	BOOLEAN isConfigure;

	/* Configure value */
	UINT32 set_cedLimit;

	/* Read Values */
	UINT32 read_IsPhyLocked;
	UINT32 read_reg214Diff;
	UINT32 read_cedCh0Diff;
	UINT32 read_cedCh1Diff;
	UINT32 read_cedCh2Diff;
} LX_HDMI20_RX_DBG_AUTO_PHY_TUNE_T;

typedef enum
{
	HDMI20_BURST_AUDIO_INFO_TYPE_NULL		=	0,	//<Null Data
	HDMI20_BURST_AUDIO_INFO_TYPE_AC3		=	1,	//<AC-3 data
	HDMI20_BURST_AUDIO_INFO_TYPE_SMPTE_338M	=	2,	//<Refer to SMPTE 338M
	HDMI20_BURST_AUDIO_INFO_TYPE_PAUSE		=	3,	//<Pause
	HDMI20_BURST_AUDIO_INFO_TYPE_MPEG1_L1	=	4,	//<MPEG-1 layer-1 data
	HDMI20_BURST_AUDIO_INFO_TYPE_MPEG1_L23	=	5,	//<MPEG-1 layer-2 or -3 data or MPEG-2 without extension
	HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_EXT	=	6,	//<MPEG-2 data with extension
	HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_AAC	=	7,	//<MPEG-2 AAC
	HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_L1	=	8,	//<MPEG-2, layer-1 low sampling frequency
	HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_L2	=	9,	//<MPEG-2, layer-2 low sampling frequency
	HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_L3	=   10,	//<MPEG-2, layer-3 low sampling frequency
	HDMI20_BURST_AUDIO_INFO_TYPE_DTS_I		=	11,	//<DTS type I
	HDMI20_BURST_AUDIO_INFO_TYPE_DTS_II		=	12,	//<DTS type II
	HDMI20_BURST_AUDIO_INFO_TYPE_DTS_III	=	13,	//<DTS type III
	HDMI20_BURST_AUDIO_INFO_TYPE_ATRAC		=	14,	//<ATRAC
	HDMI20_BURST_AUDIO_INFO_TYPE_ATRAC_23	=	15,	//<ATRAC 2/3
	HDMI20_BURST_AUDIO_INFO_TYPE_ATRAC_X	=	16,	//<ATRAC-X
	HDMI20_BURST_AUDIO_INFO_TYPE_DTS_IV		=	17,	//<DTS type IV
	HDMI20_BURST_AUDIO_INFO_TYPE_WMA_I_IV	=	18,	//<WMA type I ~ IV
	HDMI20_BURST_AUDIO_INFO_TYPE_MPEG2_AAC_LOW	=	19,	//<MPEG-2 AAC low sampling frequency
	HDMI20_BURST_AUDIO_INFO_TYPE_MPEG4_AAC	=	20,	//<MPEG-4 AAC
	HDMI20_BURST_AUDIO_INFO_TYPE_AC3_ENHANCED	=	21,	//<AC-3 Enhanced
	HDMI20_BURST_AUDIO_INFO_TYPE_MAT		=	22,	//<MAT
	HDMI20_BURST_AUDIO_INFO_TYPE_MPEG4_AAC_LOAS	=	23,	//<MPEG-4 AAC LOAS
													//<24-26 Reserved
													//<27-30 Refer to SMPTE 338M
													//<31 Extended data-type
	HDMI20_BURST_AUDIO_INFO_TYPE_MAXNUM
} HDMI20_BURST_AUDIO_INFO_TYPE;

typedef enum {
    HDMI21_EARC_OUTPUT_PORT_NONE = 0,
    HDMI21_EARC_OUTPUT_PORT_1,
    HDMI21_EARC_OUTPUT_PORT_2,
    HDMI21_EARC_OUTPUT_PORT_3,
    HDMI21_EARC_OUTPUT_PORT_4,
    HDMI21_EARC_OUTPUT_PORT_ALL,
} HDMI21_EARC_OUTPUT_PORT_T;

typedef enum {
	HDMI21_EARC_STATUS__OFF			=	0,			///< OFF
	HDMI21_EARC_STATUS__IDLE1		=	1,			///< IDLE1
	HDMI21_EARC_STATUS__IDLE2		=	2,			///< IDLE2
	HDMI21_EARC_STATUS__DISC1		=	3,			///< DISC1
	HDMI21_EARC_STATUS__DISC2		=	4,			///< DISC2
	HDMI21_EARC_STATUS__EARC 		=	5,			///< EARC
	HDMI21_EARC_STATUS__ARC			=	6,			///< ARC
	HDMI21_EARC_STATUS__MAXIMUM		=	7
} HDMI21_EARC_STATUS_T;

typedef struct
{
	UINT8	nVersion;
	UINT8	nLength;

	UINT8	metaData[32];
} LX_HDMI20_RX_DRM_PACKET_T;

typedef enum {
	HDMI_DOLBY_STATE_OFF,
	HDMI_DOLBY_STD_OLDVSI,
	HDMI_DOLBY_STD_NEWVSI,
	HDMI_DOLBY_LL_422_12B,
	HDMI_DOLBY_LL_PC
}LX_HDMI_DOLBY_STATE_T;


typedef struct
{
	UINT8 sink_version;
	UINT8 source_version;
	UINT8 bit_ratio;
	BOOLEAN scramble_enable;
	BOOLEAN scramble_status;
	BOOLEAN clock_detect;
	BOOLEAN ch_locked[HDMI20_NUM_OF_TMDS_CH_LINK];
	UINT16 ch_error_count[HDMI20_NUM_OF_TMDS_CH_LINK];
} LX_HDMI20_RX_SCDC_INFO_T;

typedef struct
{
	UINT8 status;
	UINT8 An[8];
	UINT8 Aksv[5];
	UINT8 Bksv[5];
	UINT8 Ri[2];
	UINT8 Bcaps;
	UINT8 Bstatus[2];
} LX_HDMI20_HDCP14_INFO_T;

typedef struct
{
	UINT8 kdrvVer;
	BOOLEAN avMute;
	BOOLEAN avMuteClear;
	UINT32 phyLockTime;
	UINT32 n_param;
	UINT32 cts_param;

	LX_HDMI20_RX_SCDC_INFO_T scdcInfo;
	LX_HDMI20_HDCP14_INFO_T hdcpInfo;
} LX_HDMI20_RX_HDMI_MISC_T;

typedef enum
{
    LX_HDMI20_EMP_VSEMDS, /*vendor specific EM data set*/
    LX_HDMI20_EMP_HDRDM, /*HDR Dynamic Metadata*/
    LX_HDMI20_EMP_VTEM, /*Video Timing Extended Metadata*/
    LX_HDMI20_EMP_CVTEM, /*Compressed Video Transport Extended Metadata*/
	LX_HDMI20_EMP_MAXNUM
}LX_HDMI20_EMP_TYPE_T;

typedef enum
{
	LX_HDMI20_VSI_H14B_VSIF,
	LX_HDMI20_VSI_HF_VSIF,
	LX_HDMI20_VSI_DOLBY,
	LX_HDMI20_VSI_UNKNOWN,
	LX_HDMI20_VSI_MAXNUM
} LX_HDMI20_VSI_TYPE_T;

typedef struct
{
	UINT8 type;            /**< packet type */
	UINT8 version;         /**< packet version */
	UINT8 length;          /**< packet length */
	UINT8 dataBytes[HDMI20_PACKET_DATA_MAX_LENGTH]; /**< packet data */
} LX_HDMI20_IN_PACKET_T;

typedef struct
{
    UINT8 numberOfVSI;
    LX_HDMI20_IN_PACKET_T packet[LX_HDMI20_VSI_MAXNUM];		/**< HDMI VSI info */
} LX_HDMI20_MULTIPLE_VSI_T;

typedef enum
{
	LX_HDMI20_PLATFORM_WEBOS = 0,
	LX_HDMI20_PLATFORM_PIONEER,
	LX_HDMI20_PLATFORM_MAXNUM
} LX_HDMI20_PLATFORM_TYPE_T;

typedef enum
{
       LX_HDMI_HDR_MODE_SDR = 0,
       LX_HDMI_HDR_MODE_DOLBY,
       LX_HDMI_HDR_MODE_HDR10,
       LX_HDMI_HDR_MODE_HLG,
       LX_HDMI_HDR_MODE_TECHNICOLOR,
       LX_HDMI_HDR_MODE_HDREFFECT,
       LX_HDMI_HDR_MODE_MAX
} LX_HDMI_HDR_MODE_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _HDMI20_DRV_H_ */

/** @} */
