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
 *  main driver implementation for micom device.
 *	micom device will teach you how to make device driver with new platform.
 *
 *  author		jun.kong
 *  version		1.0
 *  date			2016.04.29
 *  note			Additional information.
 *
 *  @addtogroup lg1313_micom
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <linux/cpu.h>
#include <linux/io.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/kernel_stat.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/suspend.h>
#include <linux/io.h>
#include <linux/tick.h>
#include <linux/syscalls.h>
#include <linux/file.h>
#include <linux/fcntl.h>
#include <asm/uaccess.h>
#include <linux/kthread.h>
#include <linux/completion.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <asm/uaccess.h>
#include <linux/poll.h>

#include "os_util.h"
#include "base_device.h"
#include "ucom_drv.h"
#include "ucom_core.h"
#include "ucom_o20_common.h"


#ifdef INCLUDE_L18_CHIP_KDRV
#include "../../chip/o20/os/linux_irqs.h"
#endif

//#define ENABLE_MICOM_EMUL_TASK

#ifdef ENABLE_MICOM_EMUL_TASK
#include "i2c_core.h"

#include "reg_ctrl.h"
#include <linux/completion.h>
static int REG_WRITEI2C(UINT8* data, UINT8 nbyte);
static int REG_READI2C(UINT8 cmd, UINT8* data, UINT8 nbyte);
#endif


/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

#ifdef ENABLE_MICOM_EMUL_TASK
static struct task_struct *micom_emul_task;
static struct completion   ucom_completion;
#endif


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

#define MAKE_SRCDEST( src, dest)    (( src << 4) | dest )

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/


/**
 * ioctl handler for micom device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */




static void __iomem *a2m_ipc_base = NULL;
static void __iomem *m2a_ipc_base = NULL;
static void __iomem *a2m_irq_base = NULL;
static void __iomem *m2a_irq_base = NULL;

static UINT16 ucomkey =0 ;
static UINT32 ucomtask_key  = 0;


static UINT32 ucom_abnormal = 0;

#if 0
static UINT32 swap_32( UINT32 val )
{
    val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF );
    return (val << 16) | (val >> 16);
}

/*
 * Peterson's algorithm (http://en.wikipedia.org/wiki/Peterson%27s_algorithm)
 * to implement the mutual exclusion between the CPU(P0) and the internal UCOM(P1).
 */

static DEFINE_MUTEX(ucom_mutex);

UINT32 flag[2] = {0,0};
UINT32 turn = 1;
UINT8 micomdata[100] = {0,};


static void ucom_mutex_lock(void)
{
	mutex_lock(&ucom_mutex);

	#ifdef ENABLE_UCOM_IPC
	writel(0x01, a2m_ipc_base + MAILBOX(3) + REG(4));
	writel(0x01, a2m_ipc_base + MAILBOX(3) + REG(6));
	while (readl(a2m_ipc_base + MAILBOX(3) + REG(5)) == 0x01 &&
	       readl(a2m_ipc_base + MAILBOX(3) + REG(6)) == 0x01) {
		/* busy wait */
	}
	#else
	flag[0] = 1;
	turn = 1;
	while (flag[1] == 0x01 &&
	       turn == 0x01) {
		/* busy wait */
	}
	#endif
}

static void ucom_mutex_unlock(void)
{
	#ifdef ENABLE_UCOM_IPC
	writel(0x00, a2m_ipc_base + MAILBOX(3) + REG(4));
	#endif

	mutex_unlock(&ucom_mutex);
}

static void ucom_mutex_read_lock(void)
{
	mutex_lock(&ucom_mutex);

	#ifdef ENABLE_UCOM_IPC
	writel(0x01, a2m_ipc_base + MAILBOX(3) + REG(5));
	writel(0x01, a2m_ipc_base + MAILBOX(3) + REG(6));
	while (readl(a2m_ipc_base + MAILBOX(3) + REG(4)) == 0x01 &&
	       readl(a2m_ipc_base + MAILBOX(3) + REG(6)) == 0x00) {
		/* busy wait */
	}
	#endif

}

static void ucom_mutex_read_unlock(void)
{
	#ifdef ENABLE_UCOM_IPC
	writel(0x00, a2m_ipc_base + MAILBOX(3) + REG(5));
	#endif

	mutex_unlock(&ucom_mutex);
}
#endif
static char *get_cmd_string (unsigned char kk)
{
	switch(kk)
	{
		case 0x01:
			return  "CP_WRITE_SET_ONTIMER";
		case 0x02:
			return  "CP_WRITE_SET_OFFTIMER";
		case 0x03:
			return  "CP_WRITE_CANCEL_ONTIMER";
		case 0x04:
			return  "CP_WRITE_CANCEL_OFFTIMER";
		case 0x07:
			return  "CP_WRITE_IIC_KEY_BUZZ";
		case 0x08:
			return  "CP_WRITE_CAM_ONOFF";
		case 0x09:
			return  "CP_WRITE_VR_LANG";
		case 0x0E:
			return  "CP_WRITE_SET_CENTER_LED_CTRL";
		case 0x10:
			return  "CP_WRITE_SET_DISABLE_TIMER";
		case 0x12:
			return  "CP_WRITE_SET_COOL_TIMER";
		case 0x14:
			return  "CP_WRITE_LEDBAR_CTRL";
		case 0x15:
			return  "CP_WRITE_RGB_LED_CTRL";
		case 0x1A:
			return  "CP_WRITE_SET_EMM_TIME";
		case 0x1B:
			return  "CP_WRITE_CANCEL_EMM_TIME";
		case 0x1C:
			return  "CP_WRITE_LED_BLINKING_STATUS";
		case 0x1D:
			return  "CP_WRITE_LED_IIC_WRITE_TEST";
		case 0x1E:
			return  "CP_WRITE_LED_IIC_READ_TEST";
		case 0x20:
			return  "CP_WRITE_LED_CONTROL";
		case 0x21:
			return  "CP_WRITE_POWER_ON_MODE";
		case 0x22:
			return  "CP_WRITE_MAIN_WDT";
		case 0x23:
			return  "CP_WRITE_HOST_READY";
		case 0x24:
			return  "CP_WRITE_RTC_YMDHMS";
		case 0x25:
			return  "CP_WRITE_POWER_CONTROL";
		case 0x26:
			return  "CP_WRITE_INSTANT_CONTROL";
		case 0x27:
			return  "CP_WRITE_POWER_OFF_DELAY";
		case 0x28:
			return  "CP_WRITE_EEPROM_PHIST_READ_READY";
		case 0x29:
			return  "CP_WRITE_EEPROM_WRITE";
		case 0x2A:
			return  "CP_WRITE_APP_STARTED";
		case 0x2B:
			return  "CP_WRITE_EEPROM_DATA_READ_READY";
		case 0x2C:
			return  "CP_WRITE_OLP_ONOFF";
		case 0x2D:
			return  "CP_WRITE_SET_SEARCH_TIME";
		case 0x2E:
			return  "CP_WRITE_CANCEL_SEARCH_TIME";
		case 0x30:
			return  "CP_WRITE_POWER_ERROR_READ_READY";
		case 0x31:
			return  "CP_WRITE_POWER_ERROR_RESET";
		case 0x32:
			return  "CP_WRITE_BAUDRATE";
		case 0x33:
			return  "CP_WRITE_AC_OFF_READY";
		case 0x34:
			return  "CP_WRITE_MODULE5V_ONOFF";
		case 0x35:
			return  "CP_WRITE_INVERT_ERROR_REPORT";
		case 0x36:
			return  "CP_WRITE_INVERT_OR_VAVS_ON";
		case 0x37:
			return  "CP_WRITE_INVERT_OR_VAVS_OFF";
		case 0x38:
			return  "CP_WRITE_HP_ONOFF";
		case 0x39:
			return  "CP_WRITE_SCART_MUTE";
		case 0x3A:
			return  "CP_WRITE_PANEL_ONOFF";
		case 0x3B:
			return  "CP_WRITE_AI_ONOFF";
		case 0x3C:
			return  "CP_WRITE_AMP_MUTE_ON";
		case 0x3D:
			return  "CP_WRITE_AMP_MUTE_OFF";
		case 0x3E:
			return  "CP_WRITE_DISP_ENABLE_ON";
		case 0x3F:
			return  "CP_WRITE_DISP_ENABLE_OFF";
		case 0x40:
			return  "CP_WRITE_RESERVE_TIME";
		case 0x41:
			return  "CP_WRITE_CANCEL_RESERVE_TIME";
		case 0x42:
			return  "CP_WRITE_SET_OTA_ONTIMER";
		case 0x43:
			return  "CP_WRITE_SET_MODULE_TYPE";
		case 0x44:
			return  "CP_WRITE_AUTO_POWER_OFFON";
		case 0x45:
			return  "CP_WRITE_SET_EIT_TIME";
		case 0x46:
			return  "CP_WRITE_CANCEL_EIT_TIME";
		case 0x47  :
			return  "CP_WRITE_CECM_MESSAGE";
		case 0x48  :
			return  "CP_WRITE_CECM_SETMODE";
		case 0x49  :
			return  "CP_WRITE_CECM_READY";
		case 0x4A:
			return  "CP_WRITE_POWER_BORAD_SETTING";
		case 0x4B:
			return  "CP_WRITE_MICOM_LOCALE";
		case 0x4C:
			return  "CP_WRITE_SET_TOT_ONTIMER";
		case 0x4D  :
			return  "CP_WRITE_CHILD_LOCK";
		case 0x4E  :
			return  "CP_WRITE_KEY_LOCK";
		case 0x4F:
			return  "CP_WRITE_CEC_SYNC_POWER";
		case 0x50:
			return  "CP_WRITE_RS232KEYLOCK";
		case 0x52:
			return  "CP_WRITE_POWER_OFF_CANCEL";
		case 0x54:
			return  "CP_WRITE_NAND_WRITE_PROTECT";
		case 0x55:
			return  "CP_WRITE_EDID_WRITE_PROTECT";
		case 0x56:
			return  "CP_WRITE_EQ_INIT";
		case 0x57:
			return  "CP_WRITE_WIRELESS_READY_POWER";
		case 0x58:
			return  "CP_WRITE_WIRELESS_READY_SWITCH";
		case 0x59:
			return  "CP_WRITE_MICOM_AUTOTEST";
		case 0x5A:
			return  "CP_WRITE_RELEASE_POWER_STATUS";
		case 0x5B:
			return  "CP_WRITE_MICOM_RESET";
		case 0x5C:
			return  "CP_WRITE_SET_POWERONLY_FLAG";
		case 0x5F:
			return  "CP_WRITE_RESET_POWEROFF_STATUS";
		case 0x60:
			return  "CP_WRITE_HDMI_PORT_SEL";
		case 0x61:
			return  "CP_WRITE_AUDIO_TV_OUT_MUTE";
		case 0x62:
			return  "CP_WRITE_AUDIO_MNT_OUT_MUTE";
		case 0x64:
			return  "CP_WRITE_POWER_MODE_CTRL";
		case 0x65:
			return  "CP_WRITE_KEYOP_MODE_CTRL";
		case 0x67:
			return  "CP_WRITE_TOUCH_SENSITIVITY_READ_READY";
		case 0x68:
			return  "CP_WRITE_TOUCH_SENSITIVITY";
		case 0x69:
			return  "CP_WRITE_APLUS_LEDBAR_CTRL";
		case 0x6A:
			return  "CP_WRITE_LOGO_LIGHT_LED";
		case 0x6B:
			return  "CP_WRITE_WOL_ONOFF";
		case 0x6C:
			return  "CP_WRITE_COMM_SETID";
		case 0x6D:
			return  "CP_WRITE_MODULE_PORT_OFFON";
		case 0x6E:
			return  "CP_WRITE_POWER_INDICATOR_STANDBYLED";
		case 0x6F:
			return  "CP_WRITE_POWER_INDICATOR_POWERLED";
		case 0x70:
			return  "CP_WRITE_TOOL_TYPE";
		case 0x71:
			return  "CP_WRITE_TOUCH_EEPROM";
		case 0x72:
			return  "CP_WRITE_DCOFFON_KEYLOCKTIME";
		case 0x73:
			return  "CP_WRITE_LOGOLIGHT_COMPLETE";
		case 0x74:
			return  "CP_WRITE_LOGOLIGHT_10MINOFF";
		case 0x75:
			return  "CP_WRITE_EPI_CONTROL_ONOFF";
		case 0x77:
			return  "CP_WRITE_DISPLAY_MODE";
		case 0x78:
			return  "CP_WRITE_EYEQ_SENSOR_ENABLE";
		case 0x79:
			return  "CP_WRITE_LOGO_LIGHT_TEST";
		case 0x7B:
			return  "CP_WRITE_SET_MS_MODE_DUTY";
		case 0x7C:
			return  "CP_WRITE_SET_DELAYED_MS_DUTY";
		case 0x7D:
			return  "CP_WRITE_EDID_WRITE";
		case 0x7E:
			return  "CP_WRITE_EDID_RESET";
		case 0x7F:
			return  "CP_WRITE_CAM_RESET_CONTROL";
		case 0x83:
			return  "CP_WRITE_SET_DIGITAL_EYE_TYPE";
		case 0x8C:
			return  "CP_WRITE_POWERONLY_KEY_LOCK";
		case 0x91:
			return  "CP_WRITE_FRC_RESET_CONTROL";
		case 0x92:
			return  "CP_WRITE_KEY_LOCK_CONTROL";
		case 0x94:
			return  "CP_WRITE_COMBO_RESET_CTRL";
		case 0x96:
			return  "CP_WRITE_CANCEL_TOT_ONTIMER";
		case 0xB9:
			return  "CP_WRITE_MICOM_PMLOG_DUMP";
		case 0xBA:
			return  "CP_WRITE_MICOM_PMLOG_SEND";
		case 0xBB:
			return  "CP_WRITE_MICOM_PMLOG_ENABLE";
		case 0xC9:
			return  "CP_WRITE_SET_ALWAYSON_TIMER";
		case 0xCA:
			return  "CP_WRITE_WOW_ONOFF";
		case 0xCB:
			return  "CP_WRITE_WOBLE_ONOFF";
		case 0xCD:
			return  "CP_WRITE_QSM_TIME";
		case 0xCE:
			return  "CP_WRITE_CANCEL_QSM_TIME";
		case 0xD2:
			return  "CP_WRITE_WIFI_ONOFF";
		case 0xD4:
			return  "CP_WRITE_SET_INSTANT_PERIOD";
		case 0xD5:
			return  "CP_WRITE_SET_INSTANT_KERNELTIMEOUT";
		case 0xD7:
			return  "CP_WRITE_SET_EWBS_ONOFF";
		case 0xE1:
			return  "CP_WRITE_AUTO_MOVING_SPEAKER_ONOFF";
		case 0xE2:
			return  "CP_WRITE_MOVING_SPEAKER_RETRY";
		case 0xE3:
			return  "CP_WRITE_MOVING_TO_SPEAKER_MODE";
		case 0xE4:
			return  "CP_WRITE_CONFIG_JP_MICOM";
		case 0xEA:
			return  "CP_WRITE_MOVING_SPEAKER_OF_INSTOP";
		case 0xEB:
			return  "CP_WRITE_CLOSE_MOVING_SPEAKER";
		case 0xEC:
			return  "CP_WRITE_MELODY_IC_ONOFF";
		case 0xEE:
			return  "CP_WRITE_FORCED_PNWASH";
		case 0xF1:
			return  "CP_WRITE_SET_KEYLOCK_TIMER";
		case 0xFA:
			return  "CP_WRITE_SET_CH_UPDATE_TIME";
		case 0xFB:
			return  "CP_WRITE_CANCEL_CH_UPDATE_TIME";
		case 0x05:
			return  "CP_READ_GET_ONTIMER";
		case 0x11:
			return  "CP_READ_GET_DISABLE_TIMER";
		case 0x13:
			return  "CP_READ_GET_COOL_TIMER";
		case 0x51:
			return  "CP_READ_RS232KEYLOCK";
		case 0x80:
			return  "CP_READ_RTC_YMDHMS";
		case 0x81:
			return  "CP_READ_KEYLOCK_MODE";
		case 0x82:
			return  "CP_READ_GET_DIGITAL_EYE_TYPE";
		case 0x84:
			return  "CP_READ_GET_TOT_ONTIMER";
		case 0x85:
			return  "CP_READ_GET_EIT_TIME";
		case 0x86:
			return  "CP_READ_GET_EMM_TIME";
		case 0x87:
			return  "CP_READ_RESERVE_TIME";
		case 0x88:
			return  "CP_READ_MODULE_TYPE";
		case 0x8A:
			return  "CP_READ_GET_SEARCH_TIME";
		case 0x9A:
			return  "CP_READ_POWERON_MODE";
		case 0x9B:
			return  "CP_READ_LEDBAR_VER";
		case 0x9D:
			return  "CP_READ_WIRELESS_DETECT";
		case 0xA1:
			return  "CP_READ_MICOM_VERSION";
		case 0xA2:
			return  "CP_READ_HDMI_CEC_DATA";
		case 0xA3:
			return  "CP_READ_HDMI_REP_RESULT";
		case 0xA5:
			return  "CP_READ_CEC_FORWARD_DATA";
		case 0xA6:
			return  "CP_READ_MICOM_HWOPTION";
		case 0xA7:
			return  "CP_READ_LED_IIC_READ_VALUE";
		case 0xA8:
			return  "CP_READ_LOGO_LIGHT_LED";
		case 0xA9:
			return  "CP_READ_WOL_ONOFF";
		case 0xAA:
			return  "CP_READ_CAM_ONOFF";
		case 0xAB:
			return  "CP_READ_EPI_ONOFF";
		case 0xAE:
			return  "CP_READ_GET_MS_MODE";
		case 0xB1:
			return  "CP_READ_POWER_STATUS";
		case 0xB2:
			return  "CP_READ_EEPROM_READ";
		case 0xB3:
			return  "CP_READ_PDP_OPTION";
		case 0xB4:
			return  "CP_READ_MICOM_IMAGE_TYPE";
		case 0xB5:
			return  "CP_READ_POWER_ERROR_HISTORY";
		case 0xB6:
			return  "CP_READ_SUB_ASSY_TYPE";
		case 0xB7:
			return  "CP_READ_SLAVE_STATUS";
		case 0xB8:
			return  "CP_READ_LAST_PWROFF_HISTORY";
		case 0xBF:
			return  "CP_READ_CEC_PING_CHK";
		case 0xC0:
			return  "0xc0";
		case 0xC4:
			return  "CP_READ_AUTO_WB";
		case 0xC6:
			return  "CP_READ_TV_LINK_LOADER";
		case 0xC8:
			return  "CP_READ_INTERNALMICOM_STATUS";
		case 0xCC:
			return  "CP_READ_WOW_ONOFF";
		case 0xCF:
			return  "CP_READ_QSM_TIME";
		case 0xD0:
			return  "CP_READ_MICOM_INV_ONOFF";
		case 0xD1:
			return  "CP_READ_MICOM_PANEL_ONOFF";
		case 0xD3:
			return  "CP_READ_WIFI_ONOFF";
		case 0xD6:
			return  "CP_READ_WOBLE_ONOFF";
		case 0xD8:
			return  "CP_READ_MICOM_MODEL_OPTION";
		case 0xD9:
			return  "CP_READ_GET_EWBS_ONOFF";
		case 0xE5:
			return  "CP_READ_CHECK_JP_MICOM";
		case 0xE6:
			return  "CP_READ_SPEAKER_OPEN_CLOSE_COUNT";
		case 0xE7:
			return  "CP_READ_TOUCH_SENSITIVITY";
		case 0xE8:
			return  "CP_READ_TOUCH_SINGLE_THRESHOLD";
		case 0xF5:
			return  "CP_READ_BRETHING_LED_VARIBLE";
		case 0xF8:
			return  "CP_READ_EYEQ_SENSOR_DATA";
		case 0xF9:
			return  "CP_READ_EYEQ_TYPE";
		case 0xFC:
			return  "CP_READ_GET_CH_UPDATE_TIME";
		case 0xFD:
			return  "CP_READ_GET_CURRENT_POWERON_MASK";
		case 0xFE:
			return  "CP_READ_BRETHING_LED_FW_VER";
		default :
			return "UnKnown";
	}
}

#ifdef ENABLE_MICOM_EMUL_TASK
void o20_ucom_do_cmd(void)
{

	KDRV_UCOM_DEBUG("complete key[%x]\n",ucomtask_key);
	complete(&ucom_completion);
}

static int o20_ucom_task(void *pParam)
{
	unsigned int i,ret;
	UINT32	ipccmd[UCOM_MAX_MBOX_WORD]	= {0,}; /*indx 0:size  8:cmd 8:data start */
	UINT32	ipcres[UCOM_MAX_MBOX_WORD]	= {0,};
	UINT8 	i2ccmdbuf[UCOM_MAX_CMD_BYTE];

	UINT8 * pbuf = NULL;
	UINT8 * responsebuf = NULL;

	KDRV_UCOM_NOTI("o20 o20_ucom_task is created\n");

	do {
		/* Check stop condition when device is closed. */
		if (kthread_should_stop()) {
			KDRV_UCOM_NOTI("o20 o20_ucom_task - exit!\n");
			break;
		}

		memset((char *)ipccmd,0x0, UCOM_MAX_CMD_BYTE);
		memset((char *)ipcres,0x0, UCOM_MAX_CMD_BYTE);
		memset((char *)i2ccmdbuf,0x0, UCOM_MAX_CMD_BYTE);


		//reinit_completion(&ucom_completion);
		wait_for_completion(&ucom_completion);

		/*get commad type*/
		/* read ipc cmd */
		for( i = 0; i < UCOM_MAX_MBOX_WORD ; i++)
		{
			ipccmd[i] = readl(a2m_ipc_base + MAILBOX(0) + REG(i));
		}

		if(ucomtask_key == readl(a2m_ipc_base + MAILBOX(0) + REG(1)))
		{
			pbuf = (UINT8 *)ipccmd;

			if(pbuf[1] == UCOM_TX)
			{
				KDRV_UCOM_DEBUG("ukdrv W[%x][%x]key[%x]!!\n",pbuf[0],pbuf[1],ucomtask_key);

				/* make I2C writecmd for external micom */
				if(pbuf[8] == 0x26)
				{
					i2ccmdbuf[0] = (UINT8)0x25; 	    	/* CP_WRITE_POWER_CONTROL in 0x25 in external 0x26 in internal */
				}
				else
					i2ccmdbuf[0] = (UINT8)pbuf[8];

				if( pbuf[0] < (UCOM_MAX_CMD_BYTE - UCOM_CMD_IDX) )
				{
					for(i = 1; i <= pbuf[0]; i++)
					{
						i2ccmdbuf[i] = (UINT8)pbuf[8+i];
					}
				}
				else
					KDRV_UCOM_ERROR("check data size[%x]!!\n",pbuf[0]);

				/* need to plus one for i2c write*/
				ret = REG_WRITEI2C(i2ccmdbuf,pbuf[0]+1)	;


				KDRV_UCOM_DEBUG("ret[%x] task ukdrv wr cmd[%x] size[%x] i2ccmdbuf[%x:%x:%x]!!\n",ret,pbuf[8],pbuf[0],i2ccmdbuf[0],i2ccmdbuf[1],i2ccmdbuf[2]);


				/* copy size, key to m2a ipcres area (not write cmd)*/
				writel(readl(a2m_ipc_base + MAILBOX(0) + REG(0)), m2a_ipc_base + MAILBOX(0) + REG(0));
				writel(readl(a2m_ipc_base + MAILBOX(0) + REG(1)), m2a_ipc_base + MAILBOX(0) + REG(1));

				/* clear possible unhandled m2a pending interrupts */
				writel(0x01,	m2a_irq_base);

				/* clear possible unhandled a2m pending interrupts */
				writel(0x00,	a2m_irq_base);


			}
			else if(pbuf[1] == UCOM_RX)
			{
				responsebuf = (UINT8 *)ipcres;

				KDRV_UCOM_DEBUG("R[%x][%x]key[%x]!!\n",pbuf[0],pbuf[1],ucomtask_key);
				ret = REG_READI2C(pbuf[8],responsebuf,pbuf[0])	;


				if(pbuf[8] == CP_READ_POWERON_MODE ||
					pbuf[8] == CP_READ_POWER_STATUS

				)
				KDRV_UCOM_DEBUG("ret[%x] task rx micom CMD[%x:%x] ipcres[%x][%x]!!\n",ret,pbuf[8],pbuf[0],ipcres[0],ipcres[1]);


				writel(readl(a2m_ipc_base + MAILBOX(0) + REG(0)), m2a_ipc_base + MAILBOX(0) + REG(0));
				writel(readl(a2m_ipc_base + MAILBOX(0) + REG(1)), m2a_ipc_base + MAILBOX(0) + REG(1));

				for(i = 0; i < UCOM_MAX_CMD_WORD ; i++)
					writel(ipcres[i] , m2a_ipc_base + MAILBOX(0) + REG(2+i));


				/* clear possible unhandled m2a pending interrupts */
				writel(0x01,	m2a_irq_base);

				/* clear possible unhandled a2m pending interrupts */
				writel(0x00,	a2m_irq_base);
			}
		}
		else
		{
			pbuf = (UINT8 *)ipccmd;
			KDRV_UCOM_DEBUG("ukdrv kdrv ucomtask_key[%x] reg[%x][%x][%x]!!\n",ucomtask_key,readl(a2m_ipc_base + MAILBOX(0) + REG(0)),readl(a2m_ipc_base + MAILBOX(0) + REG(1)),readl(a2m_ipc_base + MAILBOX(0) + REG(2)));
		}

	} while (1);

	return 0;
}


//#ifdef ENABLE_MICOM_EMUL_TASK
//#ifdef INCLUDE_O20_CHIP_KDRV
//static LX_I2C_DEV_HANDLE _i2c_micom_handle;
//#if 1
static int REG_WRITEI2C( UINT8* data, UINT8 nbyte)
{
    UINT32 i;
    int rc = -1;
    UINT32 retry = 1;
	UINT8 slave = 0x52;
	UINT8 ch=1,clock = I2C_CLOCK_400KHZ;
	{
		//UINT8 sub_addr_size;
		//UINT8 data_size;
		UINT8 sbuf[SBUF_SIZE];
		struct i2c_adapter *adap;
		struct i2c_msg msg[1];

		adap = i2c_get_adapter(1  );

		if (!adap)
		return -ENODEV;

		//sub_addr_size = 1;
		//data_size =	1 ;
		//data_size =	1 ;

		switch (clock)
		{
			case I2C_CLOCK_50KHZ:  	msg[0].flags = I2C_M_CLK__50KHZ;
				break;
			case I2C_CLOCK_100KHZ:  msg[0].flags = I2C_M_CLK_100KHZ;
				break;
			case I2C_CLOCK_400KHZ:  msg[0].flags = I2C_M_CLK_400KHZ;
				break;
			case I2C_CLOCK_800KHZ:  msg[0].flags = I2C_M_CLK_800KHZ;
				break;
			default: 				msg[0].flags = I2C_M_CLK_DEAFULT;
				break;
		}

		msg[0].addr = (slave >> 1) & 0x7f;    /* I2C address of chip */
		//msg[0].len = sub_addr_size + data_size;
		msg[0].len = nbyte;
		msg[0].buf = (void __force *)sbuf;
		memcpy(sbuf,data,nbyte);

		//msg[0].buf[0] = reg;
		//msg[0].buf[1] = data;

		for(i=0; i<retry; i++)
		{
			rc = i2c_transfer(adap, msg, 1);
			if(rc >= 0) break;
		}

		i2c_put_adapter(adap);

		rc = (rc >= 0) ? 1 :rc;
	}

	if(rc < 0)
	{
		KDRV_UCOM_ERROR("Internal i2c write failed. ch[%d] slave=0x%02x, reg=0x%02x\n",
			ch ,slave, data[0]);
	}

	return rc;

}

static int REG_READI2C(UINT8 cmd, UINT8* data, UINT8 nbyte)
{
	UINT32 i;
    int rc = -1;
	UINT32 retry = 1;
	UINT8 slave =0x52;
	UINT8 ch=1,clock = I2C_CLOCK_400KHZ;
	{
		UINT8 sub_addr_size;
		UINT8 data_size;
		UINT8 msg_num_index;
		UINT8 addrbuf[SUBADDR_MAX_SIZE],databuf[SBUF_SIZE];
		//UINT8*  mbuf = NULL;
		struct i2c_adapter *adap;
		struct i2c_msg msg[2];

		adap = i2c_get_adapter(ch);

		if (!adap)
			return -ENODEV;

		sub_addr_size = 1 ;
		data_size =  nbyte ;


		msg[0].addr = (slave >> 1) & 0x7f;    /* I2C address of chip */
		msg[0].len = sub_addr_size ;
		msg[0].buf = (void __force *)addrbuf;
		msg[0].buf[0] = cmd;


		msg[1].addr = msg[0].addr;   /* I2C address of chip */
		msg[1].len= data_size;

		switch (clock)
		{
			case I2C_CLOCK_50KHZ:	msg[0].flags = I2C_M_CLK__50KHZ;
									msg[1].flags = I2C_M_RD | I2C_M_CLK__50KHZ;
			 break;
			case I2C_CLOCK_100KHZ: 	msg[0].flags = I2C_M_CLK_100KHZ;
									msg[1].flags = I2C_M_RD | I2C_M_CLK_100KHZ;
			 break;
			case I2C_CLOCK_400KHZ: 	msg[0].flags = I2C_M_CLK_400KHZ;
									msg[1].flags = I2C_M_RD | I2C_M_CLK_400KHZ;
			 break;
			case I2C_CLOCK_800KHZ: 	msg[0].flags = I2C_M_CLK_800KHZ;
									msg[1].flags = I2C_M_RD | I2C_M_CLK_800KHZ;
			 break;
			default:
									msg[0].flags = I2C_M_CLK_DEAFULT;
									msg[1].flags = I2C_M_RD | I2C_M_CLK_DEAFULT;
			 break;
		}

		msg_num_index = 1;

		msg[msg_num_index].buf = (void __force *)databuf;

		for(i=0; i<retry; i++)
		{
			rc = i2c_transfer(adap, msg, msg_num_index+1);
			if(rc >= 0) break;
		}

		i2c_put_adapter(adap);

		if (rc >= 0)
		{
			memcpy(data ,(__u8 *)(msg[msg_num_index].buf),data_size);
			rc = data_size;
		}
		else
		{
			KDRV_UCOM_ERROR("Internal i2c read failed. ch[%d] slave=0x%02x, cmd=0x%02x\n",
				ch,slave, cmd);
		}
	}

	return rc;

}
//#endif
//#endif
//#endif



void o20_ucom_task_init(void)
{
	int cpu;
	unsigned long targetcpu = 0;
	cpu = 0;

	if (micom_emul_task == NULL) {
		init_completion(&ucom_completion);
		micom_emul_task = kthread_create_on_node(o20_ucom_task,
					NULL,
					cpu,
					"UCOMFAKE-TASK/%lu", targetcpu);

		if (likely(!IS_ERR(micom_emul_task))) {
			kthread_bind(micom_emul_task, targetcpu);
			wake_up_process(micom_emul_task);
			KDRV_UCOM_NOTI("UCOMFAKE-TASK create successed\n");
		} else
			KDRV_UCOM_ERROR("UCOMFAKE-TASK create failed\n");
	}
}
#endif

void o20_ucom_FuncInit(void)
{
	int i = 0;

	#ifdef ENABLE_IOREMAP_IPC
	m2a_ipc_base = ioremap(0xF0004100, M2A_IPC_SIZE);
	m2a_irq_base = ioremap(0xF0004180, M2A_IRQCTRL_SIZE);
	a2m_ipc_base = ioremap(0xF0004200, A2M_IPC_SIZE);
	a2m_irq_base = ioremap(0xF0004280, A2M_IRQCTRL_SIZE);
    KDRV_UCOM_NOTI("m2a_ipc[%8x]m2a_irq[%8x]a2m_ipc[%8x]a2m_irq[%8x]\n",m2a_ipc_base,m2a_irq_base,a2m_ipc_base,a2m_irq_base);
	#else
	m2a_ipc_base = kmalloc(M2A_IPC_SIZE , GFP_KERNEL);
	m2a_irq_base = kmalloc(M2A_IRQCTRL_SIZE , GFP_KERNEL);
	a2m_ipc_base = kmalloc(A2M_IPC_SIZE , GFP_KERNEL);
	a2m_irq_base = kmalloc(A2M_IRQCTRL_SIZE , GFP_KERNEL);
    KDRV_UCOM_NOTI("malloc m2a_ipc[%p]m2a_irq[%p]a2m_ipc[%p]a2m_irq[%p]\n",m2a_ipc_base,m2a_irq_base,a2m_ipc_base,a2m_irq_base);
	#endif

	for(i = 0; i < UCOM_MAX_BASE_WORD_WO_BOOTSTATUS ; i++)
	{
		writel(0, m2a_ipc_base + MAILBOX(0) + REG(i));
		writel(0, a2m_ipc_base + MAILBOX(0) + REG(i));
	}

	writel(0, m2a_irq_base );
	writel(0, a2m_irq_base );

#ifdef ENABLE_MICOM_EMUL_TASK
	o20_ucom_task_init();

	#ifdef INCLUDE_O20_CHIP_KDRV
	//_i2c_micom_handle= I2C_DevOpenPriv(1, 0);
	//I2C_DevSetClock(_i2c_micom_handle,I2C_CLOCK_400KHZ);
	#endif

#endif


}

static u32 _ucom_key(void)
{
	/* should be called with ucom_mutex locked */
	return 0xface0000 | ucomkey++;
}

static int _ucom_request(u32 key, u32 flag)
{
	unsigned long timeout = UCOM_TIMEOUT * NSEC_PER_MSEC;
	unsigned long long start,cur;
	#ifdef ENABLE_MICOM_EMUL_TASK
	#else
	unsigned int reg;
	#endif

	int err = 0;

	if(flag != UCOM_FAKE_CMD )
	{
		/* clear possible unhandled pending interrupts */
		writel(0,	m2a_irq_base);
		/* wake M to handle the request */
		writel(0x1, a2m_irq_base);

		#ifdef ENABLE_MICOM_EMUL_TASK
		if(flag == TASK_ENUL_MICOM)
		{
			ucomtask_key = readl(a2m_ipc_base + MAILBOX(0) + REG(1));
			o20_ucom_do_cmd();
		}
		#endif

		start = sched_clock();
		/* busy-wait for PMS completion */
		while (!(readl(m2a_irq_base) & M2A_IPC_DONE)) {  // if m2a_irq_base == 0 , waiting
			cur = sched_clock();
			if (cur - start > timeout) {
				if(ucom_abnormal > MAX_UCOM_ABNORMAL ) ucom_abnormal = 0;
				else 	ucom_abnormal++;

				KDRV_UCOM_ERROR("ukdrv %s:[%llu] [%d][%x][%x][%x][%x]\n", get_cmd_string(readl(a2m_ipc_base + MAILBOX(0) + REG(2)) & 0xff)
				, cur - start, ucom_abnormal,readl(m2a_ipc_base + MAILBOX(0) + REG(1)),readl(a2m_ipc_base + MAILBOX(0) + REG(1)),key,ucomkey);
				err = -ETIME;
				goto quit;
			}
		}

		#ifdef ENABLE_MICOM_EMUL_TASK
		#else
		/* check transaction key */
		reg = readl(m2a_ipc_base + MAILBOX(0) + REG(1));

		if (reg != key) {
			KDRV_UCOM_TRACE("mkey:%x akey%x  (expected: %x) uk%x\n", reg,readl(a2m_ipc_base + MAILBOX(0) + REG(1)) , key,ucomkey);
			err = -EINVAL;
			goto quit;
		}
		#endif
	}

quit:
	return err;
}


int o20_ucom_FuncWrite(LX_UCOM_PARAM_T * param)
{
	int ret;

	UINT32	micomcmd[UCOM_MAX_MBOX_WORD]	= {0,};
	UINT8 * pbuf = NULL;
	UINT32 key,i,index;

	UCOM_CHECK_ERROR( param->bufSize > UCOM_MAX_CMD_BYTE , goto func_exit, "check buf size");

	/* refer http://collab.lge.com/main/display/DNA/02.+ipc+map */
	pbuf = (UINT8 *)micomcmd;
	pbuf[0] = param->bufSize & 0xff;
	pbuf[1] = UCOM_TX;
	pbuf[8] = param->Cmd & 0xff;
	if( param->bufSize > 1)
		memcpy( (UINT8 *)(pbuf + 9 ),(UINT8 *) param->ubuf , param->bufSize - 1 );

	writel(micomcmd[0] 			, a2m_ipc_base + MAILBOX(0) + REG(0));
	writel(key =_ucom_key() 	, a2m_ipc_base + MAILBOX(0) + REG(1));
	index = (param->bufSize)/4;
	if( index > 0 )
	{
		for(i = 0; i <= index ; i++)
			writel(micomcmd[i+2] , a2m_ipc_base + MAILBOX(0) + REG(i+2));
	}
	else
		writel(micomcmd[2] , a2m_ipc_base + MAILBOX(0) + REG(2));


	#ifdef ENABLE_MICOM_EMUL_TASK
	ret = _ucom_request(key,TASK_ENUL_MICOM);
	#else
	ret = _ucom_request(key,0);
	#endif

	if(ret < 0)
	{
		KDRV_UCOM_DEBUG("ukdrv WCMD[%s:%x]size[%x]key[%x]\n",get_cmd_string(param->Cmd) ,param->Cmd,param->bufSize,key);
		return ret;
	}

	pbuf = (UINT8 *)(param->ubuf);

	if(param->bufSize > 1)
	{
		switch(param->bufSize - 1)
		{
			case 1:
				KDRV_UCOM_DEBUG("[%s] [%2x]\n",get_cmd_string(param->Cmd) ,pbuf[0]);
				break;
			case 2:
				KDRV_UCOM_DEBUG("[%s] [%2x][%2x]\n",get_cmd_string(param->Cmd) ,pbuf[0],pbuf[1]);
				break;
			case 3:
				KDRV_UCOM_DEBUG("[%s] [%2x][%2x][%2x]\n",get_cmd_string(param->Cmd) ,pbuf[0],pbuf[1],pbuf[2]);
				break;
			case 4:
				KDRV_UCOM_DEBUG("[%s] [%2x][%2x][%2x][%2x]\n",get_cmd_string(param->Cmd) ,pbuf[0],pbuf[1],pbuf[2],pbuf[3]);
				break;
			case 5:
				KDRV_UCOM_DEBUG("[%s] [%2x][%2x][%2x][%2x][%2x]\n",get_cmd_string(param->Cmd) ,pbuf[0],pbuf[1],pbuf[2],pbuf[3],pbuf[4]);
				break;
			case 6:
				KDRV_UCOM_DEBUG("[%s] [%2x][%2x][%2x][%2x][%2x][%2x]\n",get_cmd_string(param->Cmd) ,pbuf[0],pbuf[1],pbuf[2],pbuf[3],pbuf[4],pbuf[5]);
				break;
			case 7:
				KDRV_UCOM_DEBUG("[%s] [%2x][%2x][%2x][%2x][%2x][%2x][%2x]\n",get_cmd_string(param->Cmd) ,pbuf[0],pbuf[1],pbuf[2],pbuf[3],pbuf[4],pbuf[5],pbuf[6]);
				break;
			case 8:
				KDRV_UCOM_DEBUG("[%s] [%2x][%2x][%2x][%2x][%2x][%2x][%2x][%2x]\n",get_cmd_string(param->Cmd) ,pbuf[0],pbuf[1],pbuf[2],pbuf[3],pbuf[4],pbuf[5],pbuf[6],pbuf[7]);
				break;
			case 9:
				KDRV_UCOM_DEBUG("[%s] [%2x][%2x][%2x][%2x][%2x][%2x][%2x][%2x][%2x]\n",get_cmd_string(param->Cmd) ,pbuf[0],pbuf[1],pbuf[2],pbuf[3],pbuf[4],pbuf[5],pbuf[6],pbuf[7],pbuf[8]);
				break;

			default:
				break;
		}
	}
	else
		KDRV_UCOM_DEBUG("[%s] only\n",get_cmd_string(param->Cmd));


func_exit:
	return 0;
}

int o20_ucom_FuncRead(LX_UCOM_PARAM_T * param)
{

	int ret;

	UINT32	micomcmd[UCOM_MAX_MBOX_WORD]	= {0,};
	UINT8 * pbuf = NULL;
	UINT32 key,i;

	UCOM_CHECK_ERROR( param->bufSize > UCOM_MAX_CMD_BYTE  , goto func_exit, "check buf size");

	/* refer http://collab.lge.com/main/display/DNA/02.+ipc+map */
	pbuf = (UINT8 *)micomcmd;
	pbuf[0] = param->bufSize & 0xff;
	pbuf[1] = UCOM_RX;
	pbuf[8] = param->Cmd & 0xff;
	memcpy( (UINT8 *)(pbuf + 9 ),(UINT8 *) param->ubuf , param->bufSize );

	writel(micomcmd[0]			, a2m_ipc_base + MAILBOX(0) + REG(0));
	writel(key =_ucom_key() 	, a2m_ipc_base + MAILBOX(0) + REG(1));

	writel(micomcmd[2] , a2m_ipc_base + MAILBOX(0) + REG(2));

#ifdef ENABLE_MICOM_EMUL_TASK
	ret =_ucom_request(key,TASK_ENUL_MICOM); //jun.kong
#else
	ret = _ucom_request(key,0);
#endif

	if(ret < 0)
	{
		KDRV_UCOM_DEBUG("ukdrv RCMD[%s:%x]size[%x]key[%x]\n",get_cmd_string(param->Cmd) ,param->Cmd,param->bufSize,key);
		return ret;
	}

	/* read response from micom */
	for(i = 0; i < UCOM_MAX_CMD_WORD ; i++)
	{
		micomcmd[2+i] = readl(m2a_ipc_base + MAILBOX(0) + REG(2+i));
	}
	memcpy(param->ubuf,(UINT8 *)(micomcmd + 2),param->bufSize);


	pbuf = (UINT8 *)(param->ubuf);

	if(	param->Cmd == CP_READ_PERIODIC_CHK)
	{
		KDRV_UCOM_DEBUG("[%s] [%2x] [%2x]\n",get_cmd_string(param->Cmd) ,pbuf[0],pbuf[1]);
		return 0;
	}

	switch(param->bufSize)
	{
		case 1:
			KDRV_UCOM_DEBUG("[%s] [%2x]\n",get_cmd_string(param->Cmd) ,pbuf[0]);
			break;
		case 2:
			KDRV_UCOM_DEBUG("[%s] [%2x][%2x]\n",get_cmd_string(param->Cmd) ,pbuf[0],pbuf[1]);
			break;
		case 3:
			KDRV_UCOM_DEBUG("[%s] [%2x][%2x][%2x]\n",get_cmd_string(param->Cmd) ,pbuf[0],pbuf[1],pbuf[2]);
			break;
		case 4:
			KDRV_UCOM_DEBUG("[%s] [%2x][%2x][%2x][%2x]\n",get_cmd_string(param->Cmd) ,pbuf[0],pbuf[1],pbuf[2],pbuf[3]);
			break;
		case 5:
			KDRV_UCOM_DEBUG("[%s] [%2x][%2x][%2x][%2x][%2x]\n",get_cmd_string(param->Cmd) ,pbuf[0],pbuf[1],pbuf[2],pbuf[3],pbuf[4]);
			break;
		case 6:
			KDRV_UCOM_DEBUG("[%s] [%2x][%2x][%2x][%2x][%2x][%2x]\n",get_cmd_string(param->Cmd) ,pbuf[0],pbuf[1],pbuf[2],pbuf[3],pbuf[4],pbuf[5]);
			break;
		case 7:
			KDRV_UCOM_DEBUG("[%s] [%2x][%2x][%2x][%2x][%2x][%2x][%2x]\n",get_cmd_string(param->Cmd) ,pbuf[0],pbuf[1],pbuf[2],pbuf[3],pbuf[4],pbuf[5],pbuf[6]);
			break;
		case 8:
			KDRV_UCOM_DEBUG("[%s] [%2x][%2x][%2x][%2x][%2x][%2x][%2x][%2x]\n",get_cmd_string(param->Cmd) ,pbuf[0],pbuf[1],pbuf[2],pbuf[3],pbuf[4],pbuf[5],pbuf[6],pbuf[7]);
			break;
		case 9:
			KDRV_UCOM_DEBUG("[%s] [%2x][%2x][%2x][%2x][%2x][%2x][%2x][%2x][%2x]\n",get_cmd_string(param->Cmd) ,pbuf[0],pbuf[1],pbuf[2],pbuf[3],pbuf[4],pbuf[5],pbuf[6],pbuf[7],pbuf[8]);
			break;

		default:
			break;
	}


func_exit:
	return 0;
}

int o20_ucom_FuncGetStatus(void )
{

	UINT8 buf[UCOM_MAX_CMD_BYTE];
	LX_UCOM_PARAM_T  param	;
	int ret;

	param.bufSize = 1;
	param.Cmd = CP_READ_POWER_STATUS	;
	param.ubuf = buf;
	ret = o20_ucom_FuncRead(&param);
	if(ret == 0)
	{
		ret = param.ubuf[0] ;
	}
	else
		ret = -1;

	return ret;
}



static ucom_o20_func_t o20_ucom_func =
{
	.init = o20_ucom_FuncInit,
	.write = o20_ucom_FuncWrite,
	.read = o20_ucom_FuncRead,
	.getstatus= o20_ucom_FuncGetStatus,

};

ucom_o20_func_t* get_o20_ucom_func(void)
{
	return &o20_ucom_func;
}


