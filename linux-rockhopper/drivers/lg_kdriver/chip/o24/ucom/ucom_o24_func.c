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
#include <linux/version.h>
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
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 4, 0))
#include <linux/sched/clock.h>
#endif

#include "os_util.h"
#include "base_device.h"
#include "ucom_drv.h"
#include "ucom_core.h"
#include "ucom_o24_common.h"


#ifdef USE_O24_IPC_INTR
ucom_o24_data_t o24_udata;
static struct completion  o24_micom_completion;
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
#include "../../chip/o24/os/linux_irqs.h"
#endif


/*----------------------------------------------------------------------------------------
  Constant Definitions
  ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
  Macro Definitions
  ----------------------------------------------------------------------------------------*/

#define MAKE_SRCDEST( src, dest)    (( src << 4) | dest )
#define O24_UCOM_STATUS_PRINTNUM	3


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




static void __iomem *micom_base = NULL;
static void __iomem *a2m_ipc_base = NULL;
static void __iomem *m2a_ipc_base = NULL;
static void __iomem *a2m_irq_base = NULL;
static void __iomem *m2a_irq_base = NULL;
static void __iomem *o24_ipc_disable = NULL;
static void __iomem *o24_chipreset_base = NULL;
static void __iomem *o24_micom_req_base = NULL;
void __iomem *o24_micom_eeprom_base = NULL;

UINT16 ucomkey =0 ;
UINT32 ucom_abnormal = 0;

void o24_ucom_FuncInit(void);
void o24_ucom_FuncChipReset(void);
int o24_ucom_FuncWrite(LX_UCOM_PARAM_T * param);
int o24_ucom_FuncRead(LX_UCOM_PARAM_T * param);
void o24_set_micom_disable(unsigned int disable);
int __o24_spi_request(int try);
int __o24_ucom_spi_write( UINT8 * addr,  UINT8 * data , UINT8  num );
int __o24_ucom_spi_read( UINT8 * addr,  UINT8 * data , UINT8  num );
int o24_ucom_spi_write32( UINT32 addr, UINT32 val);
UINT32 o24_ucom_spi_read32(UINT32 addr);
int o24_ucom_spi_read( UINT8 * addr,  UINT8 * data , UINT8  num );
int o24_ucom_spi_write( UINT8 * addr,  UINT8 * data , UINT8  num );
int o24_ucom_FuncGetStatus(void );


unsigned int o24_get_micom_disable(void)
{
	unsigned int reg = 0;
	if(o24_ipc_disable == NULL)
		o24_ipc_disable = ioremap(0xF33F417c, 4);

	reg = readl(o24_ipc_disable);

	return reg;
}
EXPORT_SYMBOL(o24_get_micom_disable) ;

void o24_set_micom_disable(unsigned int disable)
{
	if(o24_ipc_disable == NULL)
		o24_ipc_disable = ioremap(0xF33F417c, 4);

	writel(disable, o24_ipc_disable);
}
EXPORT_SYMBOL(o24_set_micom_disable) ;
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


#ifdef USE_O24_IPC_INTR
static irqreturn_t _ucom_irqhandler(int irq, void *data)
{
	/* clear interrupt */
	writel(0, m2a_irq_base);
	complete(&o24_micom_completion);
	return IRQ_HANDLED;
}
#endif
void o24_ucom_FuncInit(void)
{
	unsigned int reg = 0;
	/* 1: ipc disabled set by micom  0: ipc enabled set by ucom init, and ucom resume */

	if(o24_ipc_disable == NULL)
		o24_ipc_disable = ioremap(0xF33F417c, 4);

	/* enable ipc */
	o24_set_micom_disable(0);

	micom_base = ioremap(0xF0004000, MICOM_BASE_SIZE);
	m2a_ipc_base = ioremap(0xF0004100, M2A_IPC_SIZE);
	m2a_irq_base = ioremap(0xF0004180, M2A_IRQCTRL_SIZE);
	a2m_ipc_base = ioremap(0xF0004200, A2M_IPC_SIZE);
	//	a2m_ipc_base = ioremap(0xFD3004c0, A2M_IPC_SIZE);
	a2m_irq_base = ioremap(0xF0004280, A2M_IRQCTRL_SIZE);

	o24_micom_req_base = ioremap(0xFD3004C8,4);


	o24_micom_eeprom_base = ioremap( 0xc63f5104,4 );

	o24_chipreset_base = ioremap( 0xFD3004C8,4 );
	//
	/* to make mainsoc access eeprom */
	//PAD_WOC_65 (0xc63f5104)
	//reg_pad_micom_06_mux_sel[31:28] : 2 : micom_sclin2  (micom i2c)  / 3: scl7_out (main i2c)
	//reg_pad_micom_08_mux_sel[23:20]:  2 : micom_sdaout2 (micom i2c)  / 3: sda7_out (main i2c)

	if(o24_micom_eeprom_base != NULL){
		reg = readl(o24_micom_eeprom_base);
		reg = reg &(~0xf0f00000) ;
		reg = reg | 0x30300000;
		writel(reg, o24_micom_eeprom_base );
	}


	//KDRV_UCOM_NOTI("m2a_ipc[%p]m2a_irq[%p]a2m_ipc[%p]a2m_irq[%p]\n",
	//	m2a_ipc_base,m2a_irq_base,a2m_ipc_base,a2m_irq_base);

#ifdef USE_O24_IPC_INTR
	o24_udata.irq = 92 ;//32 + 60(O24_CPU_interrupt_list.xlsx)

	init_completion(&o24_micom_completion);

	if(request_irq( o24_udata.irq, _ucom_irqhandler, (unsigned long)0, "ucom0", &o24_udata))
	{
		KDRV_UCOM_ERROR("UCOM IRQ[%d] request error\n", o24_udata.irq);
	}
#endif
#if 0 /* ipc area initalization is removed which is requested by micom fw */
	for(i = 0; i < UCOM_MAX_BASE_WORD_WO_BOOTSTATUS ; i++)
	{
		writel(0, m2a_ipc_base + MAILBOX(0) + REG(i));
		writel(0, a2m_ipc_base + MAILBOX(0) + REG(i));
	}
#endif

	writel(0, m2a_irq_base );
	writel(0, a2m_irq_base );
}

void o24_ucom_FuncChipReset(void)
{
	/* intr set for chip reset */
	if(o24_chipreset_base != NULL)
		writel(0x1 , o24_chipreset_base );
}
static u32 _ucom_key(void)
{
	/* should be called with ucom_mutex locked */
	return 0xface0000 | ucomkey++;
}

static int _ucom_request(u32 key, u32 flag)
{
#ifndef USE_O24_IPC_INTR
	unsigned long timeout = O24_UCOM_TIMEOUT * NSEC_PER_MSEC;
#endif
	unsigned long long start,cur;
	//unsigned int reg;

	int err = 0;

	if(flag != UCOM_FAKE_CMD )
	{
#ifndef USE_O24_IPC_INTR
		preempt_disable();
#endif
#ifdef USE_O24_IPC_INTR
		/* wake M to handle the request */
		writel(0x1, a2m_irq_base);
		start = sched_clock();

		if( wait_for_completion_timeout(&o24_micom_completion, msecs_to_jiffies(O24_UCOM_TIMEOUT)) < 0)
		{
			// if m2a_irq_base == 1 , done
			if(readl(m2a_irq_base) & M2A_IPC_DONE)
			{
				/* clear done: requested by micom fw */
				writel(0,	m2a_irq_base);
			}
			goto quit;
			if(ucom_abnormal > MAX_UCOM_ABNORMAL ) ucom_abnormal = 0;
			else 	ucom_abnormal++;
			/* clear done: requested by micom fw */
			writel(0,	m2a_irq_base);

			cur = sched_clock();
			if(ucom_abnormal < O24_UCOM_STATUS_PRINTNUM){
				KDRV_UCOM_NOTI("ukdrv %s:[%llu]\n", get_cmd_string(readl(a2m_ipc_base + MAILBOX(0) + REG(2)) & 0xff),
						cur - start);
			}
			err = -ETIME;
			goto quit;
		}
#else
		/* wake M to handle the request */
		writel(0x1, a2m_irq_base);
		start = sched_clock();
		/* busy-wait for PMS completion */
		while (!(readl(m2a_irq_base) & M2A_IPC_DONE)) {  // if m2a_irq_base == 0 , waiting
			cur = sched_clock();
			if (cur - start > timeout) {
				if(ucom_abnormal > MAX_UCOM_ABNORMAL ) ucom_abnormal = 0;
				else 	ucom_abnormal++;
				/* clear done: requested by micom fw */
				writel(0,	m2a_irq_base);
				preempt_enable();
				if(ucom_abnormal < O24_UCOM_STATUS_PRINTNUM)
				{
					KDRV_UCOM_NOTI("ukdrv %s:[%llu]\n", get_cmd_string(readl(a2m_ipc_base + MAILBOX(0) + REG(2)) & 0xff),
							cur - start);
				}
				err = -ETIME;
				goto quit;
			}
		}
#endif

		/* clear done: requested by micom fw */
		writel(0,	m2a_irq_base);

#ifndef USE_O24_IPC_INTR
		preempt_enable();
#endif
	}

quit:
	return err;
}

#define UCOM_RETRY_CNT 4
int o24_ucom_FuncWrite(LX_UCOM_PARAM_T * param)
{
	int ret = 0, retrycnt = UCOM_RETRY_CNT;
	UINT8 * pbuf = NULL;
	UINT32 micomcmd[UCOM_MAX_MBOX_WORD]	= {0,};
	UINT32 key,i,index;
	char str[UCOM_MAX_CMD_BYTE*3+1];

	UCOM_CHECK_ERROR( param->bufSize >= UCOM_MAX_CMD_BYTE , goto func_exit, "check buf size");

	/* refer http://collab.lge.com/main/display/DNA/02.+ipc+map */
	pbuf = (UINT8 *)micomcmd;
	pbuf[0] = (param->bufSize + 1) & 0xff;
	pbuf[1] = UCOM_TX;
	pbuf[8] = param->Cmd & 0xff;
	if( param->bufSize > 0)
		memcpy( (UINT8 *)(pbuf + 9 ),(UINT8 *) param->ubuf , param->bufSize );

	writel(micomcmd[0] 			, a2m_ipc_base + MAILBOX(0) + REG(0));
	writel(key =_ucom_key() 	, a2m_ipc_base + MAILBOX(0) + REG(1));
	index = (param->bufSize + 1)  /4; /*  1 consider cmd byte */
	if( index > 0 )
	{
		for(i = 0; i <= index ; i++)
			writel(micomcmd[i+2] , a2m_ipc_base + MAILBOX(0) + REG(i+2));
	}
	else
		writel(micomcmd[2] , a2m_ipc_base + MAILBOX(0) + REG(2));

	while(retrycnt > 0)
	{
		/* clear ipcdone requested by micom fw */
		writel(0, m2a_irq_base);

		if( retrycnt < UCOM_RETRY_CNT)
			usleep_range(8000,10000);
		ret = _ucom_request(key,0);

		if( ret == 0 )
			break;

		if(ret < 0 && retrycnt > 0)
		{
			retrycnt--;
		}

		if(ret < 0 && retrycnt == 0)
		{
			KDRV_UCOM_ERROR("check ukdrv retry[%d] WCMD[%s:%x]size[%x]key[%x] ret[%x]\n",retrycnt ,get_cmd_string(param->Cmd) ,param->Cmd,param->bufSize,key,ret);
			return ret;
		}
	}

	if(param->bufSize > 0)
	{
		pbuf = (UINT8 *)(param->ubuf);
		for (i=0; i <param->bufSize; i++)
		{
			sprintf(str + i*3," %2x", pbuf[i]);
		}
		KDRV_UCOM_DEBUG("[%s] [%s]\n",get_cmd_string(param->Cmd) ,str);
	}
	else
		KDRV_UCOM_DEBUG("[%s] only\n",get_cmd_string(param->Cmd));


func_exit:
	return 0;
}

int o24_ucom_FuncRead(LX_UCOM_PARAM_T * param)
{
	int ret = 0, retrycnt = UCOM_RETRY_CNT;
	UINT8 * pbuf = NULL;
	UINT32 micomcmd[UCOM_MAX_MBOX_WORD]	= {0,};
	UINT32 key,i;
	char str[UCOM_MAX_CMD_BYTE*3+1];
	UCOM_CHECK_ERROR( param->bufSize >= UCOM_MAX_CMD_BYTE  , goto func_exit, "check buf size");

	/* refer http://collab.lge.com/main/display/DNA/02.+ipc+map */
	pbuf = (UINT8 *)micomcmd;
	pbuf[0] = param->bufSize & 0xff;
	pbuf[1] = UCOM_RX;
	pbuf[8] = param->Cmd & 0xff;
	memset( (UINT8 *)(pbuf + 9 ), 0x0 , param->bufSize);
	writel(micomcmd[0]			, a2m_ipc_base + MAILBOX(0) + REG(0));
	writel(key =_ucom_key() 	, a2m_ipc_base + MAILBOX(0) + REG(1));

	writel(micomcmd[2] , a2m_ipc_base + MAILBOX(0) + REG(2));

	while(retrycnt > 0)
	{
		/* clear ipcdone requested by micom fw */
		writel(0, m2a_irq_base);

		if( retrycnt < UCOM_RETRY_CNT)
			usleep_range(8000,10000);
		ret = _ucom_request(key,0);

		if( ret == 0 )
			break;

		if(ret < 0 && retrycnt > 0)
		{
			retrycnt--;
		}
		if(ret < 0 && retrycnt == 0)
		{
			KDRV_UCOM_ERROR("check ukdrv retry [%d] RCMD[%s:%x]size[%x]key[%x]ret[%x]\n",retrycnt, get_cmd_string(param->Cmd) ,param->Cmd,param->bufSize,key,ret);
			return ret;
		}
	}

	/* read response from micom */
	for(i = 0; i < UCOM_MAX_CMD_WORD ; i++)
	{
		micomcmd[2+i] = readl(m2a_ipc_base + MAILBOX(0) + REG(2+i));
	}
	memcpy(param->ubuf,(UINT8 *)(micomcmd + 2),param->bufSize);



	if(	param->Cmd == CP_READ_PERIODIC_CHK)
	{
		pbuf = (UINT8 *)(param->ubuf);
		KDRV_UCOM_DEBUG("[%s] [%2x] [%2x]\n",get_cmd_string(param->Cmd) ,pbuf[0],pbuf[1]);
		return 0;
	}

	if(param->bufSize > 0)
	{
		pbuf = (UINT8 *)(param->ubuf);
		for (i=0; i <param->bufSize; i++)
		{
			sprintf(str + i*3," %2x", pbuf[i]);
		}
		KDRV_UCOM_DEBUG("[%s] [%s]\n",get_cmd_string(param->Cmd) ,str);
	}


func_exit:
	return 0;
}

#define UCOM_MAX_SPI_WORD 8
#define UCOM_MAX_SPI_NUM 3
#define UCOM_SPI_RD 1
#define UCOM_SPI_WR 0
int __o24_spi_request(int try)
{
	unsigned long timeout;

	if(readl(m2a_ipc_base + MAILBOX(2) + REG(1)) == 0)
	{
		KDRV_UCOM_ERROR("CHEck ukdrv clear \n");
		return -1;
	}

	writel(0x1, o24_micom_req_base );

	timeout = jiffies + msecs_to_jiffies(O24_UCOM_TIMEOUT) ;

	do
	{
		if (jiffies >= timeout) {
			return -ETIME;
		}

		//KDRV_UCOM_ERROR("jiffies %ld timeout %ld \n",jiffies,timeout);
		if (time_after_eq(jiffies, timeout)){
				//writel(0,	m2a_irq_base);
				return -ETIME;
		}
		usleep_range(50, 500);
	}while ( readl(m2a_ipc_base + MAILBOX(2) +  REG(1)) != 0 );
	return 0;
}

int __o24_ucom_spi_write( UINT8 * addr,  UINT8 * data , UINT8  num )
{
	int ret = 0, retrycnt = UCOM_RETRY_CNT;
	UINT8 * pbuf = NULL;
	UINT32 cmd[UCOM_MAX_SPI_WORD]	= {0,};
	UINT32 i;

	UCOM_CHECK_ERROR( num > UCOM_MAX_SPI_NUM  , goto func_exit, "check buf size");

	pbuf = (UINT8 *)cmd;
	memset( (UINT8 *)(pbuf), 0x0 , UCOM_MAX_SPI_WORD * 4);

	pbuf[0] = num & 0x3;
	pbuf[2] = 0xE0; //command
	pbuf[3] = UCOM_SPI_WR << 7|0xF;


	for(i = 0; i < num; i++)
	{
		memcpy( (UINT8 *)(pbuf + 4 + 8*i ),(UINT8 *) (addr+ 4*i) , 4);
		memcpy( (UINT8 *)(pbuf + 8 + 8*i ),(UINT8 *) (data+ 4*i) , 4);
	}

	writel(cmd[0], m2a_ipc_base + MAILBOX(2) + REG(1));

	if(num > 1)
		KDRV_UCOM_DEBUG("sumaddr[%8x] cmd[%8x][%8x][%8x][%8x][%8x]\n", MAILBOX(2) + REG(1),cmd[0],cmd[1],cmd[2],cmd[3],cmd[4] );
	else
		KDRV_UCOM_DEBUG("sumaddr[%8x] cmd[%8x][%8x][%8x]\n", MAILBOX(2) + REG(1),cmd[0],cmd[1],cmd[2] );

	for(i = 0; i < num; i++)
	{
		writel(cmd[1+i*2], m2a_ipc_base + MAILBOX(2) + REG(2 + i*2));
		writel(cmd[2+i*2], m2a_ipc_base + MAILBOX(2) + REG(3 + i*2));
	}

	while(retrycnt > 0)
	{
		ret = __o24_spi_request(retrycnt);

		if( retrycnt < UCOM_RETRY_CNT)
			usleep_range(5000,10000);

		if( ret == 0 )
			break;

		if(ret < 0 && retrycnt > 0)
		{
			retrycnt--;
		}

		if(ret < 0 && retrycnt == 0)
		{
			KDRV_UCOM_ERROR("CHeck ukdrv retry [%d] addr[%x]size[%x] ret[%d]\n",retrycnt,cmd[1],num ,ret);
			return ret;
		}
	}

	return 0;
func_exit:
	return -1;
}


int __o24_ucom_spi_read( UINT8 * addr,  UINT8 * data , UINT8  num )

{
	int ret = 0, retrycnt = UCOM_RETRY_CNT;
	UINT8 * pbuf = NULL;
	UINT32 cmd[UCOM_MAX_SPI_WORD]	= {0,};
	UINT32 i;

	UCOM_CHECK_ERROR( num > UCOM_MAX_SPI_NUM  , goto func_exit, "check buf size");

	pbuf = (UINT8 *)cmd;
	memset( (UINT8 *)(pbuf), 0x0 , UCOM_MAX_SPI_WORD * 4);

	pbuf[0] = num & 0x3;
	pbuf[2] = 0xE0; //command
	pbuf[3] = UCOM_SPI_RD << 7 | 0xF;

	for(i = 0; i < num; i++)
	{
		memcpy( (UINT8 *)(pbuf + 4 + 8*i ),(UINT8 *) (addr+ 4*i) , 4);
	}

	writel(cmd[0], m2a_ipc_base + MAILBOX(2) + REG(1));

	if(num > 1)
		KDRV_UCOM_DEBUG("sumaddr[%8x] cmd[%8x][%8x][%8x][%8x][%8x]\n", MAILBOX(2) + REG(1),cmd[0],cmd[1],cmd[2],cmd[3],cmd[4] );
	else
		KDRV_UCOM_DEBUG("sumaddr[%8x] cmd[%8x][%8x][%8x]\n", MAILBOX(2) + REG(1),cmd[0],cmd[1],cmd[2] );

	for(i = 0; i < num; i++)
	{
		writel(cmd[1+i*2], m2a_ipc_base + MAILBOX(2) + REG(2 + i*2));
		writel(cmd[2+i*2], m2a_ipc_base + MAILBOX(2) + REG(3 + i*2));
	}


	while(retrycnt > 0)
	{
		ret = __o24_spi_request(retrycnt);

		if( retrycnt < UCOM_RETRY_CNT)
			usleep_range(5000,10000);

		if( ret == 0 )
			break;

		if(ret < 0 && retrycnt > 0)
		{
			retrycnt--;
		}
		if(ret < 0 && retrycnt == 0)
		{
			KDRV_UCOM_ERROR("Check ukdrv retry [%d] addr[%x]size[%x] ret[%d]\n",retrycnt,cmd[1],num ,ret);
			return ret;
		}
	}

	/* read response from micom */
	for(i = 0; i < num ; i++)
	{
		cmd[2+i*2] = readl(m2a_ipc_base + MAILBOX(2) + REG(3+i*2));
		memcpy( (UINT8 *)(data + 4*i ), (UINT8 *)(pbuf + 8 + 8*i ), 4);
	}
	return 0;

func_exit:
	return -1;
}

int o24_ucom_spi_write32( UINT32 addr, UINT32 val)
{
	UINT8 addrbuf[4];
	UINT8 buf[4];
	int ret = 0;

	addrbuf[0] = addr >>0 & 0xff;
	addrbuf[1] = addr >>8 & 0xff;
	addrbuf[2] = addr >>16 & 0xff;
	addrbuf[3] = addr >>24 & 0xff;

	buf[0] = val >>0 & 0xff;
	buf[1] = val >>8 & 0xff;
	buf[2] = val >>16 & 0xff;
	buf[3] = val >>24 & 0xff;

	ret = o24_ucom_spi_write(addrbuf,buf,1);
	return ret;
}

UINT32 o24_ucom_spi_read32(UINT32 addr)
{
	UINT8 addrbuf[4];
	UINT8 buf[4];
	UINT32 val = 0;

	addrbuf[0] = addr >>0 & 0xff;
	addrbuf[1] = addr >>8 & 0xff;
	addrbuf[2] = addr >>16 & 0xff;
	addrbuf[3] = addr >>24 & 0xff;

	o24_ucom_spi_read(addrbuf,buf,1);

	val = buf[3] << 24 | buf[2] << 16 | buf[1] << 8 | buf[0] << 0;
	return val;
}

int o24_ucom_spi_read( UINT8 * addr,  UINT8 * data , UINT8  num )
{
	int ret = 0;
	if(o24_get_micom_disable() == 0)
	{
		O24_KDRV_UCOM_LOCK();
		ret = __o24_ucom_spi_read(addr, data, num);
		O24_KDRV_UCOM_UNLOCK();
	}
	return ret;
}
int o24_ucom_spi_write( UINT8 * addr,  UINT8 * data , UINT8  num )
{
	int ret = 0;
	if(o24_get_micom_disable() == 0)
	{
		O24_KDRV_UCOM_LOCK();
		ret = __o24_ucom_spi_write(addr,data, num);
		O24_KDRV_UCOM_UNLOCK();
	}
	return ret;
}

int o24_ucom_FuncGetStatus(void )
{

	UINT8 buf[UCOM_MAX_CMD_BYTE];
	LX_UCOM_PARAM_T  param	;
	int ret;

	param.bufSize = 1;
	param.Cmd = CP_READ_POWER_STATUS	;
	param.ubuf = buf;
	ret = o24_ucom_FuncRead(&param);
	if(ret == 0)
	{
		ret = param.ubuf[0] ;
	}
	else
		ret = -1;

	return ret;
}



static ucom_o24_func_t o24_ucom_func =
{
	.init = o24_ucom_FuncInit,
	.chipreset = o24_ucom_FuncChipReset,
	.write = o24_ucom_FuncWrite,
	.read = o24_ucom_FuncRead,
	.getstatus= o24_ucom_FuncGetStatus,
};

ucom_o24_func_t* get_o24_ucom_func(void)
{
	return &o24_ucom_func;
}


