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
 *  main driver implementation for pm device.
 *	pm device will teach you how to make device driver with new platform.
 *
 *  author		jun.kong (jun.kong@lge.com)
 *  version		1.0
 *  date			2014.07.18
 *  note			Additional information.
 *
 *  @addtogroup lg1210_pm
 */


#ifndef	_UCOM_KAPI_H_
#define	_UCOM_KAPI_H_

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

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define UCOM_CHIP_H15 		(LX_CHIP_REV(H15, A0) & 0xFFFFFF00)
#define UCOM_CHIP_M16 		(LX_CHIP_REV(M16, A0) & 0xFFFFFF00)
#define UCOM_CHIP_M16P 		(LX_CHIP_REV(M16P, A0) & 0xFFFFFF00)	// 추후 지울것
#define UCOM_CHIP_M17 		(LX_CHIP_REV(M17, A0) & 0xFFFFFF00)
#define UCOM_CHIP_L18 		(LX_CHIP_REV(L18, A0) & 0xFFFFFF00)


#define UCOM_IOC_MAGIC               'u'
#define UCOM_IOC_MAXNR		40

#define UCOM_TX	2
#define UCOM_RX	4

#define	UCOM_TIMEOUT	25		/* msecs */

#define UCOM_SIZE_IDX	0
#define UCOM_CMD_IDX	8
#define UCOM_DATA_IDX	9


#define	UCOM_MAX_MBOX_BYTE	32
#define	UCOM_MAX_MBOX_WORD	(UCOM_MAX_MBOX_BYTE / 4)

#define	UCOM_MAX_CMD_BYTE	24
#define	UCOM_MAX_CMD_WORD	(UCOM_MAX_CMD_BYTE / 4)

#define	UCOM_MAX_BASE_BYTE	0x80
#define	UCOM_MAX_BASE_WORD	(UCOM_MAX_BASE_BYTE / 4)


/* 0xf000427c:  boot_start_satus */
#define	UCOM_MAX_BASE_BYTE_WO_BOOTSTATUS	0x7c
#define	UCOM_MAX_BASE_WORD_WO_BOOTSTATUS	(UCOM_MAX_BASE_BYTE_WO_BOOTSTATUS / 4)


#define	UCOM_FAKE_CMD	0x1

#define A2M_IPC_ISSUE	0x1
#define M2A_IPC_DONE	0x1
#define M2A_IRQ_CTRL	REG(0)		/* PMS to CPU IRQ control & status */
#define M2A_IRQ_MASK	REG(1)		/* PMS to CPU IRQ enable or mask */
#define A2M_IRQ_CTRL	REG(2)		/* CPU to PMS IRQ control & status */
#define A2M_IRQ_MASK	REG(3)		/* CPU to PMS IRQ enable or mask */

#define MAX_CMD_SIZE 16
#define MAX_DATA_SIZE 16

#define TASK_ENUL_MICOM	0x2

#define A2M_IPC_SIZE		0x80
#define A2M_IRQCTRL_SIZE	0x10
#define M2A_IPC_SIZE		0x80
#define M2A_IRQCTRL_SIZE	0x10
#define MICOM_BASE_SIZE		0x90
#define MAX_UCOM_ABNORMAL	0xf0000000

typedef unsigned char			U8;
typedef unsigned int			B16;
typedef unsigned short			U16;
typedef unsigned int			U32;


typedef enum
{
	LX_UCOM_IOCTL_INIT,
	LX_UCOM_IOCTL_TX,
	LX_UCOM_IOCTL_RX,
	LX_UCOM_IOCTL_WAIT_NVRAM_REQ,
	LX_UCOM_IOCTL_DO_NVRAM_REQ,
} LX_UCOM_COMMAND_T;

typedef enum
{
	LX_UCOM_MODE_INPUT				= 0,
	LX_UCOM_MODE_OUTPUT				= 1,
	LX_UCOM_MODE_OUTPUT_OPENDRAIN	= 2,

} LX_UCOM_MODE_T;

typedef enum
{
	LX_UCOM_VALUE_LOW				= 0,
	LX_UCOM_VALUE_HIGH				= 1,
	LX_UCOM_VALUE_INVALID			= 0xFF,
} LX_UCOM_VALUE_T;



typedef struct
{
	UINT32	ioctlcmd;
	UINT32	nvrw;
	UINT32	nvaddr;
	UINT32	nvdata;
	UINT32	bufSize;
	UINT8	Valid;
	UINT8	Opcode;
	UINT8	Cmd;
	UINT8	rsvd;
	union
	{
		UINT8		*buf;			///< register address
		UINT32		buf_compat;
		UINT64		buf_sizer;
	};
	union
	{
		UINT8		*ubuf;			///< register address
		UINT32		ubuf_compat;
		UINT64		ubuf_sizer;
	};
} LX_UCOM_PARAM_T;



/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/


typedef struct
{
    U8  u8Valid;
    U16 u16Addr;
    U8  u8Data;
} Reg_Info_t;

typedef struct
{
    U8  u8Valid;
    U8  u8Opcode;
    U8  u8Cmd;
	U8	u8DataNum;
	U8	*pu8Data;

} UCOM_Data_Info_t;

typedef struct
{
    U8  u8Valid;
    U8  u8Opcode;
    U8  u8Data;
    U16 u16Data;
} Control_Info_t;


typedef struct
{
    U8  u8Valid;
    U32 u32Sec;
} RTC_Time_t;


/* UCOM DDI Layer Command */
typedef enum
{
#if 0
    CP_WRITE_SET_ONTIMER = 0x01,
    CP_WRITE_SET_OFFTIMER = 0x02,
    CP_WRITE_CANCEL_ONTIMER = 0x03,
    CP_WRITE_CANCEL_OFFTIMER = 0x04,
	CP_READ_GET_ONTIMER = 0x05,

    CP_READ_STABLE_CHK = 0x0F,
    CP_WRITE_POWER_ON_MODE = 0x21,
    CP_WRITE_RTC_YMDHMS = 0x24,
	CP_WRITE_HOST_READY = 0x23,

	CP_WRITE_POWER_CONTROL = 0x26, //0x26 internal micom in gp2, 0x26 intstat cmd in pionner
								//0x25 external micom in pionner

	CP_WRITE_APP_STARTED = 0x2a,
	CP_WRITE_SET_SEARCH_TIME = 0x2D ,
	CP_WRITE_CANCEL_SEARCH_TIME = 0x2E,
	CP_WRITE_HP_ONOFF = 0x38,

    CP_WRITE_RESERVE_TIME = 0x40,
    CP_WRITE_CANCEL_RESERVE_TIME = 0x41,
    CP_WRITE_AUTO_POWER_OFFON = 0x44,
    CP_WRITE_SET_OTA_ONTIMER = 0x42,
    CP_WRITE_SET_OTATIMER = 0x43,
    CP_WRITE_CECM_SETMODE = 0x48,

    CP_WRITE_CHILD_LOCK = 0x4D,
    CP_WRITE_KEY_LOCK = 0x4E,

    CP_WRITE_RS232KEYLOCK = 0x50,
    CP_READ_RS232KEYLOCK = 0x51,
    CP_WRITE_POWER_OFF_CANCEL = 0x52,

    CP_WRITE_POWER_MODE_CTRL = 0x64,
    CP_WRITE_KEYOP_MODE_CTRL = 0x65,
    CP_WRITE_COMM_SETID = 0x6C,
    CP_WRITE_POWER_INDICATOR_STANDBYLED = 0x6E,
    CP_WRITE_POWER_INDICATOR_POWERLED = 0x6F,

    CP_WRITE_DISPLAY_MODE = 0x77,	// for demo LED

    CP_READ_RTC_YMDHMS = 0x80,
    CP_READ_RESERVE_TIME = 0x87,
    CP_READ_OTA_TIME = 0x88,
    CP_READ_GET_SEARCH_TIME	= 0x8A,
    CP_READ_POWERON_MODE = 0x9A,
    CP_READ_MICOM_VERSION = 0xA1,

	CP_READ_HDMI_CEC_DATA = 0xA2,
	CP_WRITE_MICOM_COPYEDID = 0xA7,

    CP_READ_POWER_STATUS = 0xB1,
	CP_READ_EEPROM_READ = 0xB2,
	CP_READ_SUB_ASSY_TYPE = 0xB6,

	CP_READ_REMO_INPUT	= 0xc0,

#ifdef ENABLE_NVRAM_RW_BY_MICOM_REQ
	CP_NVRAMDATA_TO_MICOM	= 0xD9,
	CP_NVRAMDATA_TO_ARM		= 0xDA,
#endif

    CP_WRITE_RCU_SETTING = 0xDF,   // RCU(Multi IR, IR BED) ??

	/* common for GP2 ,PIONEER */
	CP_WRITE_BOARD_TYPE = 0xE9,
	CP_READ_MICOM_PIN = 0xEA,
	CP_WRITE_MICOM_PIN = 0xEB,

	CP_READ_CH_UPDATE_TIME = 0xFB,
    CP_NO_CMD = 0
#else
    CP_NO_CMD = 0,
	CP_WRITE_SET_ONTIMER				 =  0x01,
	CP_WRITE_SET_OFFTIMER				 =  0x02,
	CP_WRITE_CANCEL_ONTIMER				 =  0x03,
	CP_WRITE_CANCEL_OFFTIMER			 =  0x04,
	CP_WRITE_IIC_KEY_BUZZ				 =  0x07,
	CP_WRITE_CAM_ONOFF					 =  0x08,
	CP_WRITE_VR_LANG							 =  0x09,
	CP_WRITE_SET_CENTER_LED_CTRL		 =  0x0E,
	CP_WRITE_SET_DISABLE_TIMER			 =  0x10,
	CP_WRITE_SET_COOL_TIMER				 =  0x12,
	CP_WRITE_LEDBAR_CTRL				 =  0x14,
	CP_WRITE_RGB_LED_CTRL				 =  0x15,
	CP_WRITE_SET_EMM_TIME					 =  0x1A,
	CP_WRITE_CANCEL_EMM_TIME			 =  0x1B,
	CP_WRITE_LED_BLINKING_STATUS			 =  0x1C,
	CP_WRITE_LED_IIC_WRITE_TEST			 =  0x1D,
	CP_WRITE_LED_IIC_READ_TEST			 =  0x1E,
	CP_WRITE_LED_CONTROL				 =  0x20,
	CP_WRITE_POWER_ON_MODE			 =  0x21,
	CP_WRITE_MAIN_WDT					 =  0x22,
	CP_WRITE_HOST_READY				 =  0x23,
	CP_WRITE_RTC_YMDHMS				 =  0x24,
	CP_WRITE_POWER_CONTROL				 =  0x25,
	CP_WRITE_INSTANT_CONTROL			 =  0x26,
	CP_WRITE_POWER_OFF_DELAY				 =  0x27,
	CP_WRITE_EEPROM_PHIST_READ_READY		 =  0x28,
	CP_WRITE_EEPROM_WRITE					 =  0x29,
	CP_WRITE_APP_STARTED					 =  0x2A,
	CP_WRITE_EEPROM_DATA_READ_READY		 =  0x2B,
	CP_WRITE_OLP_ONOFF					 =  0x2C,
	CP_WRITE_SET_SEARCH_TIME				 =  0x2D,
	CP_WRITE_CANCEL_SEARCH_TIME			 =  0x2E,
	CP_WRITE_POWER_ERROR_READ_READY		 =  0x30,
	CP_WRITE_POWER_ERROR_RESET			 =  0x31,
	CP_WRITE_BAUDRATE						 =  0x32,
	CP_WRITE_AC_OFF_READY					 =  0x33,
	CP_WRITE_MODULE5V_ONOFF				 =  0x34,
	CP_WRITE_INVERT_ERROR_REPORT			 =  0x35,
	CP_WRITE_INVERT_OR_VAVS_ON				 =  0x36,
	CP_WRITE_INVERT_OR_VAVS_OFF			 =  0x37,
	CP_WRITE_HP_ONOFF						 =  0x38,
	CP_WRITE_SCART_MUTE					 =  0x39,
	CP_WRITE_PANEL_ONOFF					 =  0x3A,
	CP_WRITE_AI_ONOFF						 =  0x3B,
	CP_WRITE_AMP_MUTE_ON					 =  0x3C,
	CP_WRITE_AMP_MUTE_OFF					 =  0x3D,
	CP_WRITE_DISP_ENABLE_ON				 =  0x3E,
	CP_WRITE_DISP_ENABLE_OFF				 =  0x3F,
	CP_WRITE_RESERVE_TIME					 =  0x40,
	CP_WRITE_CANCEL_RESERVE_TIME			 =  0x41,
	CP_WRITE_SET_OTA_ONTIMER				 =  0x42,
	CP_WRITE_SET_MODULE_TYPE				 =  0x43,
	CP_WRITE_AUTO_POWER_OFFON				 =  0x44,
	CP_WRITE_SET_EIT_TIME					 =  0x45,
	CP_WRITE_CANCEL_EIT_TIME				 =  0x46,
	CP_WRITE_CECM_MESSAGE				 =  0x47  ,
	CP_WRITE_CECM_SETMODE				 =  0x48  ,
	CP_WRITE_CECM_READY				 =  0x49  ,
	CP_WRITE_POWER_BORAD_SETTING		 =  0x4A,
	CP_WRITE_MICOM_LOCALE				 =  0x4B,
	CP_WRITE_SET_TOT_ONTIMER			 =  0x4C,
	CP_WRITE_CHILD_LOCK				 =  0x4D  ,
	CP_WRITE_KEY_LOCK					 =  0x4E  ,
	CP_WRITE_CEC_SYNC_POWER			 =  0x4F,
	CP_WRITE_RS232KEYLOCK				 =  0x50,
	CP_WRITE_POWER_OFF_CANCEL			 =  0x52,
	CP_WRITE_NAND_WRITE_PROTECT		 =  0x54,
	CP_WRITE_EDID_WRITE_PROTECT		 =  0x55,
	CP_WRITE_EQ_INIT						 =  0x56,
	CP_WRITE_WIRELESS_READY_POWER		 =  0x57,
	CP_WRITE_WIRELESS_READY_SWITCH	 =  0x58,
	CP_WRITE_MICOM_AUTOTEST			 =  0x59,
	CP_WRITE_RELEASE_POWER_STATUS		 =  0x5A,
	CP_WRITE_MICOM_RESET				 =  0x5B,
	CP_WRITE_SET_POWERONLY_FLAG			 =  0x5C,
	CP_WRITE_RESET_POWEROFF_STATUS	 =  0x5F,
	CP_WRITE_HDMI_PORT_SEL				 =  0x60,
	CP_WRITE_AUDIO_TV_OUT_MUTE			 =  0x61,
	CP_WRITE_AUDIO_MNT_OUT_MUTE 			 =  0x62,
	CP_WRITE_POWER_MODE_CTRL				 =  0x64,
	CP_WRITE_KEYOP_MODE_CTRL				 =  0x65,
	CP_WRITE_TOUCH_SENSITIVITY_READ_READY	 =  0x67,
	CP_WRITE_TOUCH_SENSITIVITY				 =  0x68,
	CP_WRITE_TOUCH_SENSITIVITY_SET_MODE		 =  0x69,
	CP_WRITE_APLUS_LEDBAR_CTRL			 =  0x69,
	CP_WRITE_LOGO_LIGHT_LED				 =  0x6A,
	CP_WRITE_WOL_ONOFF					 =  0x6B,
	CP_WRITE_COMM_SETID					 =  0x6C,
	CP_WRITE_MODULE_PORT_OFFON			 =  0x6D,
	CP_WRITE_POWER_INDICATOR_STANDBYLED	 =  0x6E,
	CP_WRITE_POWER_INDICATOR_POWERLED	 =  0x6F,
	CP_WRITE_TOOL_TYPE						 =  0x70,
	CP_WRITE_TOUCH_EEPROM					 =  0x71,
	CP_WRITE_DCOFFON_KEYLOCKTIME			 =  0x72,
	CP_WRITE_LOGOLIGHT_COMPLETE			 =  0x73,
	CP_WRITE_LOGOLIGHT_10MINOFF			 =  0x74,
	CP_WRITE_EPI_CONTROL_ONOFF				 =  0x75,
	CP_WRITE_DISPLAY_MODE					 =  0x77,
	CP_WRITE_EYEQ_SENSOR_ENABLE			 =  0x78,
	CP_WRITE_LOGO_LIGHT_TEST				 =  0x79,
	CP_WRITE_SET_MS_MODE_DUTY				 =  0x7B,
	CP_WRITE_SET_DELAYED_MS_DUTY			 =  0x7C,
	CP_WRITE_EDID_WRITE						 =  0x7D,
	CP_WRITE_EDID_RESET						 =  0x7E,
	CP_WRITE_CAM_RESET_CONTROL			 =  0x7F,
	CP_WRITE_SET_DIGITAL_EYE_TYPE		 =  0x83,
	CP_WRITE_POWERONLY_KEY_LOCK			 =  0x8C,
	CP_WRITE_FRC_RESET_CONTROL			 =  0x91,
	CP_WRITE_KEY_LOCK_CONTROL			 =  0x92,
	CP_WRITE_COMBO_RESET_CTRL			 =  0x94,
	CP_WRITE_CANCEL_TOT_ONTIMER			 =  0x96,
	CP_WRITE_MICOM_PMLOG_DUMP			 =  0xB9,
	CP_WRITE_MICOM_PMLOG_SEND			 =  0xBA,
	CP_WRITE_MICOM_PMLOG_ENABLE			 =  0xBB,
	CP_WRITE_SET_ALWAYSON_TIMER			 =  0xC9,
	CP_WRITE_WOW_ONOFF				 =  0xCA,
	CP_WRITE_WOBLE_ONOFF				 =  0xCB,
	CP_WRITE_QSM_TIME					 =  0xCD,
	CP_WRITE_CANCEL_QSM_TIME			 =  0xCE,
	CP_WRITE_WIFI_ONOFF					 =  0xD2,
	CP_WRITE_SET_INSTANT_PERIOD			 =  0xD4,
	CP_WRITE_SET_INSTANT_KERNELTIMEOUT	 =  0xD5,
	CP_WRITE_SET_EWBS_ONOFF				 =  0xD7,
	CP_WRITE_AUTO_MOVING_SPEAKER_ONOFF	 =  0xE1,
	CP_WRITE_MOVING_SPEAKER_RETRY		 =  0xE2,
	CP_WRITE_MOVING_TO_SPEAKER_MODE		 =  0xE3,
	CP_WRITE_CONFIG_JP_MICOM			 =  0xE4,
	CP_WRITE_MOVING_SPEAKER_OF_INSTOP	 =  0xEA,
	CP_WRITE_CLOSE_MOVING_SPEAKER		 =  0xEB,
	CP_WRITE_MELODY_IC_ONOFF			 =  0xEC,
	CP_WRITE_FORCED_PNWASH				 =  0xEE,
	CP_WRITE_SET_KEYLOCK_TIMER			 =  0xF1,
	CP_WRITE_SET_CH_UPDATE_TIME		 =  0xFA,
	CP_WRITE_CANCEL_CH_UPDATE_TIME		 =  0xFB,
	CP_READ_GET_ONTIMER					 =  0x05,
	CP_READ_GET_DISABLE_TIMER			 =  0x11,
	CP_READ_GET_COOL_TIMER				 =  0x13,
	CP_READ_RS232KEYLOCK				 =  0x51,
	CP_READ_EYESENSOR_STATUS			 =  0x70,
	CP_READ_RTC_YMDHMS				 =  0x80,
	CP_READ_KEYLOCK_MODE				 =  0x81,
	CP_READ_GET_DIGITAL_EYE_TYPE		 =  0x82,
	CP_READ_GET_TOT_ONTIMER				 =  0x84,
	CP_READ_GET_EIT_TIME				 =  0x85,
	CP_READ_GET_EMM_TIME				 =  0x86,
	CP_READ_RESERVE_TIME				 =  0x87,
	CP_READ_MODULE_TYPE				 =  0x88,
	CP_READ_GET_SEARCH_TIME			 =  0x8A,
	CP_READ_POWERON_MODE				 =  0x9A,
	CP_READ_LEDBAR_VER				 =  0x9B,
	CP_READ_WIRELESS_DETECT			 =  0x9D,
	CP_READ_MICOM_VERSION				 =  0xA1,
	CP_READ_HDMI_CEC_DATA				 =  0xA2,
	CP_READ_HDMI_REP_RESULT			 =  0xA3,
	CP_READ_CEC_FORWARD_DATA			 =  0xA5,
	CP_READ_MICOM_HWOPTION			 =  0xA6,
	CP_READ_LED_IIC_READ_VALUE			 =  0xA7,
	CP_READ_LOGO_LIGHT_LED				 =  0xA8,
	CP_READ_WOL_ONOFF				 =  0xA9,
	CP_READ_CAM_ONOFF				 =  0xAA,
	CP_READ_EPI_ONOFF				 =  0xAB,
	CP_READ_GET_MS_MODE				 =  0xAE,
	CP_READ_POWER_STATUS				 =  0xB1,
	CP_READ_EEPROM_READ					 =  0xB2,
	CP_READ_PDP_OPTION					 =  0xB3,
	CP_READ_MICOM_IMAGE_TYPE			 =  0xB4,
	CP_READ_POWER_ERROR_HISTORY			 =  0xB5,
	CP_READ_SUB_ASSY_TYPE				 =  0xB6,
	CP_READ_SLAVE_STATUS				 =  0xB7,
	CP_READ_LAST_PWROFF_HISTORY			 =  0xB8,
	CP_READ_CEC_PING_CHK				 =  0xBF,
	CP_READ_PERIODIC_CHK				 =  0xC0,
	CP_READ_AUTO_WB						 =  0xC4,
	CP_READ_TV_LINK_LOADER				 =  0xC6,
	CP_READ_INTERNALMICOM_STATUS		 =  0xC8,
	CP_READ_WOW_ONOFF				 =  0xCC,
	CP_READ_QSM_TIME					 =  0xCF,
	CP_READ_MICOM_INV_ONOFF			 =  0xD0,
	CP_READ_MICOM_PANEL_ONOFF			 =  0xD1,
	CP_READ_WIFI_ONOFF					 =  0xD3,
	CP_READ_WOBLE_ONOFF					 =  0xD6,
	CP_READ_MICOM_MODEL_OPTION		 =  0xD8,
	CP_READ_GET_EWBS_ONOFF			 =  0xD9,
#ifdef ENABLE_NVRAM_RW_BY_MICOM_REQ
	CP_NVRAMDATA_TO_MICOM	= 0xDB,
	CP_NVRAMDATA_TO_ARM		= 0xDA,
#endif
	CP_READ_CHECK_JP_MICOM			 =  0xE5,
	CP_READ_SPEAKER_OPEN_CLOSE_COUNT	 =  0xE6,
	CP_READ_TOUCH_SENSITIVITY			 =  0xE7,
	CP_READ_TOUCH_SINGLE_THRESHOLD		 =  0xE8,
	CP_READ_BRETHING_LED_VARIBLE		 =  0xF5,
	CP_READ_EYEQ_SENSOR_DATA			 =  0xF8,
	CP_READ_EYEQ_TYPE					 =  0xF9,
	CP_READ_GET_CH_UPDATE_TIME			 =  0xFC,
	CP_READ_GET_CURRENT_POWERON_MASK	 =  0xFD,
	CP_READ_BRETHING_LED_FW_VER		 =  0xFE
#endif

} DDI_UCOM_CMDTYPE;

#define MICOM_GPIO_PIN_BASE 0
#define MICOM_SAR_PIN_BASE 64

#define UCOM_ENABLE_MONITOR 0 //1  //2012.01.03 , Luke//0 jun.kong 1-> 0->1
#define UCOM_MONITOR_PERIOD_US 2000000 //2sec //2012.01.03 , Luke


#define UCOM_INIT                _IO(UCOM_IOC_MAGIC, 0)
#define UCOM_CHIPRESET                _IO(UCOM_IOC_MAGIC, 1)
#define UCOM_IOW_COMMAND_SET		_IOW(UCOM_IOC_MAGIC,	10, LX_UCOM_PARAM_T)
#define UCOM_IORW_COMMAND_GET		_IOWR(UCOM_IOC_MAGIC,	11, LX_UCOM_PARAM_T)


/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _UCOM_DRV_H_ */

/** @} */
