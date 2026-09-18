/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2024 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file
 *
 *  CI Driver for linux dvb_ca_dev(DEMUX&CA)
 *
 *  @author	Ilkyu Kim
 *  @version	1.2
 *  @date	2025-07-07
 *  @note	Additional information.
 */

/* Original Copyright */
/*
 * Copyright (C) 2004 Andrew de Quincey
 *
 * Parts of this file were based on sources as follows:
 *
 * Copyright (C) 2003 Ralph Metzler <rjkm@metzlerbros.de>
 *
 * based on code:
 *
 * Copyright (C) 1999-2002 Ralph  Metzler
 *                       & Marcus Metzler for convergence integrated media GmbH
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * Or, point your browser to http://www.gnu.org/copyleft/gpl.html
 */

#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <asm/io.h>
#include <lg1k/te/reg.h>
#include <lg1k/te/io.h>
#include <lg1k/te/ci.h>
#include <lg1k/te/ion.h>

#include "os_util.h"
#include "ci_impl.h"

int ci_module_init(void);
void ci_module_exit(void);

/* Timing parameter for High Speed mode (Current max 0xF = 15)*/
static int _setup_time = 1;
static int _command_time = 4;
static int _recovery_time = 1;

static int force_cd_en = 0;
static int force_cd_val = 0;

module_param_named(te_ci_setup_time, _setup_time, int, 0644);
MODULE_PARM_DESC(te_ci_setup_time, "Setup Time(tick) for high speed mode");

module_param_named(te_ci_command_time, _command_time, int, 0644);
MODULE_PARM_DESC(te_ci_command_time, "Command Time(tick) for high speed mode");

module_param_named(te_ci_recovery_time, _recovery_time, int, 0644);
MODULE_PARM_DESC(te_ci_recovery_time, "Recovery Time(tick) for high speed mode");

module_param_named(te_ci_force_cd_en, force_cd_en, int, 0644);
MODULE_PARM_DESC(te_ci_force_cd_en, "card detection force enabling");

module_param_named(te_ci_force_cd_val, force_cd_val, int, 0644);
MODULE_PARM_DESC(te_ci_force_cd_val, "card detection control (1:insertion)");

/* Hardware Enum Definitions */
enum ci_reg_name {
	CREG_CTRL_STATUS_1 = 0x0000,
	CREG_CTRL_STATUS_2 = 0x0002,
	CREG_CTRL_STATUS_3 = 0x0004,
	/* */
	CREG_PC_CARD_CTRL_1 = 0x0006,
	CREG_PC_CARD_CTRL_2 = 0x0008,
	CREG_PC_CARD_CTRL_3 = 0x000A,
	/* */
	CREG_RSVD_0C = 0x000C,
	CREG_RSVD_0E = 0x000E,
	/* */
	CREG_BUSRT_CTRL = 0x0010,
	CREG_TIMEOUT_CTRL = 0x0012,
	CREG_TIMEOUT = 0x0014,
	/* */
	CREG_RSVD_16 = 0x0016,
	CREG_RSVD_18 = 0x0018,
	CREG_RSVD_1A = 0x001A,
	CREG_RSVD_1C = 0x001C,
	CREG_RSVD_1E = 0x001E,
	CREG_RSVD_20 = 0x0020,
	CREG_RSVD_22 = 0x0022,
	CREG_RSVD_24 = 0x0024,
	/* */
	CREG_INTR_FLAG = 0x0026,
	CREG_INTR_MASK = 0x0028,
	CREG_INTR_CTRL = 0x002A,
	/* */
	CREG_PCMCIA_IDX = 0x002C,
	/* */
	CREG_HS_CTRL_1 = 0x002E,
	CREG_HS_CTRL_2 = 0x0030,
	CREG_HS_CTRL_3 = 0x0032,
	CREG_HS_CTRL_4 = 0x0034,
	CREG_HS_CTRL_5 = 0x0036,
	CREG_HS_CTRL_6 = 0x0038,
	CREG_HS_CTRL_7 = 0x003A,
	CREG_HS_CTRL_8 = 0x003C,
};

#define MAX_CAMCHANGE_CHECK_ITERATION	5

/* Legacy Macro Action */
#define CI_READ16(dev, reg)		\
	ci_reg_read16(dev, reg)
#define CI_WRITE16(dev, val, reg)	\
	ci_reg_write16(dev, val, reg)

#define te_subdev_to_ci_device(sd)			\
	container_of(sd, struct ci_device, subdev)

/* PC Card Control1 */
#define CHIP_MODE_IO			0X001D
#define CHIP_MODE_ATTR			0X001B

/* Control and Status1 */
#define VCC_SW0				0x0004
#define EN_PCCARD			0x0020
#define CARD_RESET			0x0080

/* Control and Status2 */
#define CD1_CD2_HIGH			0x0003

/* interrupt control */
#define CD_CHANGED			0x0001
#define CD_CHANGED_DISABLE_INT		0xFFFF
#define CD_CHANGED_ENABLE_INT		0xFFFE
#define CD_INT_MODE			0x0040
#define CD_POLL				0x0080

/* Control and Status3 */
#define IO_INT_MODE			0x0004
#define POD_MODE			0x0010

/* Delay Time (ms) */
#define DELAY_INIT_INTR			10
#define DELAY_CAM_INIT_VCC_RESET	300
#define DELAY_CAM_INIT_RESET		20
#define DELAY_CAM_INIT_EN_CARD		80
#define DELAY_CAM_INIT_END		20
#define DELAY_CAM_POWER_OFF		50

#define DELAY_TUPLE_EARLY_CHECK		5
#define DELAY_TUPLE_CHECK		12

#define TUPLE_CHECK_CNT			800

#define CI_IRQ_NUM			(32 + 37)

#define COMMON_CS_BASE			(0xD0000000)
#define COMMON_CS2_BASE			(COMMON_CS_BASE+0x8000000)
#define COMMON_DVBCI_BASE		(COMMON_CS2_BASE+0x0)
#define COMMON_CI_REG_BASE		(COMMON_DVBCI_BASE + 0x10000)
#define COMMON_CI_REG_SIZE		0x40
#define COMMON_CI_CAM_BASE		(COMMON_DVBCI_BASE)
#define COMMON_CI_CAM_SIZE		0x8000

#define CI_SMC_BASE			0xFF400038
#define CI_SMC_SIZE			0x1C

#define IO_DATA_ADDR 0x0

#define get_te_device(dev)		(dev->subdev.tdev)

int g_ci_dvb_debug_fd = -1;

static inline bool check_cd_register(struct ci_device *dev);
static int ci_request_irq(struct ci_device *dev);
static inline void ci_free_irq(struct ci_device *dev);

#ifdef INCLUDE_M23_CHIP_KDRV
static void init_m23_ctop_configurations(void)
{
	//Check PAD_VD0 to get control if CAM is not work properly
	//default; cs0~3, eb_wait, eb_addr15 is shared by gpio
}
#endif

static void init_ctop_configurations(void)
{
	u32 chip = lx_chip();

	switch (chip) {
#ifdef INCLUDE_M23_CHIP_KDRV
	case LX_CHIP_M23:
		return init_m23_ctop_configurations();
#endif
	default:
		return;
	}
}

/* Basic Operations (CICAM READ or Register Read) */
static u16 ci_reg_read16(struct ci_device *dev, u8 addr)
{
	if (dev->cfg.use_ion) {
		u16 val = 0xffff;

		ion_ci_cireg_read16(get_te_device(dev), &val, addr);
		return val;
	}

	return readw(dev->reg_addr + addr);
}

static void ci_reg_write16(struct ci_device *dev, u16 val, u8 addr)
{
	if (dev->cfg.use_ion) {
		ion_ci_cireg_write16(get_te_device(dev), val, addr);
		return;
	}

	writew(val, dev->reg_addr + addr);
}

/* DEBUG related functions / macros */
#define dprintf(fmt, args...)	seq_printf(m, fmt, ##args)
#define CI_PRINT_REG(_cidev, _reg, _name)			\
do {								\
	if (m != NULL) {					\
		dprintf("[0x%02X] %32s [0x%04X]\n",		\
		        _reg, _name, CI_READ16(_cidev, _reg));	\
	} else {						\
		printk("[0x%02X] %32s [0x%04X]\n",		\
		       _reg, _name, CI_READ16(_cidev, _reg));	\
	}							\
} while(0)

static void print_register(struct seq_file *m, struct ci_device *cidev)
{
	CI_PRINT_REG(cidev, CREG_CTRL_STATUS_1, "Control and Status 1");
	CI_PRINT_REG(cidev, CREG_CTRL_STATUS_2, "Control and Status 2");
	CI_PRINT_REG(cidev, CREG_CTRL_STATUS_3, "Control and Status 3");
	CI_PRINT_REG(cidev, CREG_PC_CARD_CTRL_1, "PC Card Control 1");
	CI_PRINT_REG(cidev, CREG_PC_CARD_CTRL_2, "PC Card Control 2");
	CI_PRINT_REG(cidev, CREG_PC_CARD_CTRL_3, "PC Card Control 3");
	CI_PRINT_REG(cidev, CREG_BUSRT_CTRL, "Burst Control");
	CI_PRINT_REG(cidev, CREG_INTR_FLAG, "Interrupt Flag");
	CI_PRINT_REG(cidev, CREG_INTR_MASK, "Interrupt Mask");
	CI_PRINT_REG(cidev, CREG_INTR_CTRL, "Interrupt Control");
	CI_PRINT_REG(cidev, CREG_PCMCIA_IDX, "PCMCIA Address Index");
	CI_PRINT_REG(cidev, CREG_HS_CTRL_1, "Power On Interval 1");
	CI_PRINT_REG(cidev, CREG_HS_CTRL_2, "Power On Interval 2");
	CI_PRINT_REG(cidev, CREG_HS_CTRL_3, "Enable Interval 1");
	CI_PRINT_REG(cidev, CREG_HS_CTRL_4, "Enable Interval 2");
	CI_PRINT_REG(cidev, CREG_HS_CTRL_5, "Card Insert Done Interval 1");
	CI_PRINT_REG(cidev, CREG_HS_CTRL_6, "Card Insert Done Interval 2");
	CI_PRINT_REG(cidev, CREG_HS_CTRL_7, "Card Removal Done Interval 1");
	CI_PRINT_REG(cidev, CREG_HS_CTRL_8, "Card Removal Done Interval 2");
}

static void init_logm(void)
{
	if (g_ci_dvb_debug_fd == -1) {
		g_ci_dvb_debug_fd = LOGM_ObjRegister("dvb_ci");
		LOGM_ObjBitMaskEnable(g_ci_dvb_debug_fd, LOG_LEVEL_ERROR);
		LOGM_ObjBitMaskEnable(g_ci_dvb_debug_fd, LOG_LEVEL_WARNING);
		LOGM_ObjBitMaskEnable(g_ci_dvb_debug_fd, LOG_LEVEL_NOTI);
	}
}

enum {
	DEBUG_ID_REG = 0,
	DEBUG_ID_STATE,
	DEBUG_ID_RESET,
	DEBUG_ID_MAX,
};

static void print_state(struct seq_file *m, struct ci_device *dev)
{
	dprintf("speed: %d error_mode: %d rate_mode: %d\n", dev->speed,
		dev->error_mode, dev->rate_mode);
}

static int debug_show(struct te_debug_item *item, struct seq_file *m)
{
	struct ci_device *dev = item->private;

	switch (item->flags) {
	case DEBUG_ID_REG:
		print_register(m, dev);
		break;
	case DEBUG_ID_STATE:
		print_state(m, dev);
		break;
	default:
		return -EPERM;
	}

	return 0;
}

static int reg_write_command(struct ci_device *dev, const char *cmd)
{
	int rc;
	u32 offset, value;

	rc = sscanf(cmd, "%8x %8x", &offset, &value);
	if (rc != 2)
		return -EINVAL;

	CI_WRITE16(dev, (u16)value, (u16)offset);

	return 0;
}

static int debug_reset_command(struct ci_device *dev, const char *cmd)
{
	//TODO: consider other way
//	ci_slot_do_initial_detection(dev);

	return 0;
}

static int debug_write(struct te_debug_item *item, char *str)
{
	struct ci_device *dev = item->private;
	int rc;

	switch (item->flags) {
	case DEBUG_ID_REG:
		rc = reg_write_command(dev, str);
		break;
	case DEBUG_ID_RESET:
		rc = debug_reset_command(dev, str);
		break;

	default:
		rc = -EPERM;
	}

	return rc;
}

static const struct te_debug_simple_ops debug_ops = {
	.show = debug_show,
	.write = debug_write,
};

static const struct te_debug_item_info debug_list[] = {
	DBGITM_SIM("reg", &debug_ops, DEBUG_ID_REG),
	DBGITM_SIM_R("state", &debug_ops, DEBUG_ID_STATE),
	DBGITM_SIM_W("reset", &debug_ops, DEBUG_ID_RESET)
};

static int pcmcia_speed_ctrl(struct ci_device *dev, enum ci_mode_speed speed)
{
	if (speed == CI_PCMCIA_SPEED_LOW) {
		CI_WRITE16(dev, 0x0F03, CREG_PC_CARD_CTRL_2);
		CI_WRITE16(dev, 0x0003, CREG_PC_CARD_CTRL_3);
	} else if (speed == CI_PCMCIA_SPEED_HIGH) {
		u16 val;

		val = ((_command_time & 0xF) << 8) | (_setup_time & 0xF);
		CI_WRITE16(dev, val, CREG_PC_CARD_CTRL_2);

		val = (_recovery_time & 0xF);
		CI_WRITE16(dev, val, CREG_PC_CARD_CTRL_3);
	} else {
		log_error("invalid speed[%d]", speed);
		return -EINVAL;
	}

	dev->speed = speed;
	return 0;
}

static u8 read_attribute_mem(struct ci_device *dev, uint16_t address)
{
	u8 val = 0xff;

	if (dev->access_mode != CAM_ACCESS_MODE_ATTRMEM) {
		log_debug("(DEBUG) change access_mode: ATTR");
		CI_WRITE16(dev, POD_MODE, CREG_CTRL_STATUS_3);
		CI_WRITE16(dev, CHIP_MODE_ATTR, CREG_PC_CARD_CTRL_1);
		dev->access_mode = CAM_ACCESS_MODE_ATTRMEM;
	}

	if (dev->cfg.use_ion)
		ion_ci_read_attribute_mem(get_te_device(dev), &val, address);
	else
		val = readb(dev->mod_addr + address);

	return val;
}

/* Hardware Functions for dvb_ca */
int ci_read_attribute_mem(struct ci_device *dev, int address)
{
	u8 val;

	mutex_lock(&dev->reset_lock);

	if (dev->cam_ready != CAM_READY_SUCCESS) {
		mutex_unlock(&dev->reset_lock);
		return -EIO;
	}

	val = read_attribute_mem(dev, address << 1); //addr is goint to half in HW

	mutex_unlock(&dev->reset_lock);

	log_trace("[0x%04x]: 0x%02x", address << 1, val);

	return (int)val;
}

static void write_attribute_mem(struct ci_device *dev, uint16_t address,
				 u8 value)
{
	if (dev->access_mode != CAM_ACCESS_MODE_ATTRMEM) {
		log_debug("(DEBUG) change access_mode: ATTR");
		CI_WRITE16(dev, POD_MODE, CREG_CTRL_STATUS_3);
		CI_WRITE16(dev, CHIP_MODE_ATTR, CREG_PC_CARD_CTRL_1);
		dev->access_mode = CAM_ACCESS_MODE_ATTRMEM;
	}

	if (dev->cfg.use_ion)
		ion_ci_write_attribute_mem(get_te_device(dev), value, address);
	else
		writeb(value, dev->mod_addr + address);
}

int ci_write_attribute_mem(struct ci_device *dev, int address, u8 value)
{
	log_trace("[0x%04x]: 0x%02x", address << 1, value);

	mutex_lock(&dev->reset_lock);

	if (dev->cam_ready != CAM_READY_SUCCESS) {
		mutex_unlock(&dev->reset_lock);
		return -EIO;
	}

	write_attribute_mem(dev, (address << 1), value); //addr is goint go half in HW

	mutex_unlock(&dev->reset_lock);

	return 0;
}

static u8 read_cam_control(struct ci_device *dev, u8 address)
{
	u8 val = 0xff;

	if (dev->access_mode != CAM_ACCESS_MODE_IO) {
		log_debug("(DEBUG) change access_mode: IO");
		CI_WRITE16(dev, (POD_MODE | IO_INT_MODE), CREG_CTRL_STATUS_3);
		CI_WRITE16(dev, CHIP_MODE_IO, CREG_PC_CARD_CTRL_1);
		dev->access_mode = CAM_ACCESS_MODE_IO;
	}

	if (dev->cfg.use_ion)
		ion_ci_read_cam_control(get_te_device(dev), &val, address);
	else
		val = readb(dev->mod_addr + address);

	return val;
}

int ci_read_cam_control(struct ci_device *dev, u8 address)
{
	u8 val;

	mutex_lock(&dev->reset_lock);

	if (dev->cam_ready != CAM_READY_SUCCESS) {
		mutex_unlock(&dev->reset_lock);
		return -EIO;
	}

	val = read_cam_control(dev, (address << 1)); // addr is going to half in HW

	mutex_unlock(&dev->reset_lock);

	log_trace("[0x%02x]: 0x%02x", address << 1, val);

	return (int)val;
}

static void write_cam_control(struct ci_device *dev, u8 address, u8 value)
{
	if (dev->access_mode != CAM_ACCESS_MODE_IO) {
		log_debug("(DEBUG) change access_mode: IO");
		CI_WRITE16(dev, (POD_MODE | IO_INT_MODE), CREG_CTRL_STATUS_3);
		CI_WRITE16(dev, CHIP_MODE_IO, CREG_PC_CARD_CTRL_1);
		dev->access_mode = CAM_ACCESS_MODE_IO;
	}

	if (dev->cfg.use_ion)
		ion_ci_write_cam_control(get_te_device(dev), value, address);
	else
		writeb(value, dev->mod_addr + address);
}

int ci_write_cam_control(struct ci_device *dev, u8 address, u8 value)
{
	log_trace("[0x%02x]: 0x%02x", address << 1, value);

	mutex_lock(&dev->reset_lock);

	if (dev->cam_ready != CAM_READY_SUCCESS) {
		mutex_unlock(&dev->reset_lock);
		return -EIO;
	}

	write_cam_control(dev, (address << 1), value); // addr is going to half in HW

	mutex_unlock(&dev->reset_lock);

	return 0;
}

static int read_io_data(struct ci_device *dev, u8 *buf, u32 len)
{
	int i, ret;

	if (unlikely(dev->access_mode != CAM_ACCESS_MODE_IO)) {
		log_debug("(DEBUG) change access_mode: IO");
		CI_WRITE16(dev, (POD_MODE | IO_INT_MODE), CREG_CTRL_STATUS_3);
		CI_WRITE16(dev, CHIP_MODE_IO, CREG_PC_CARD_CTRL_1);
		dev->access_mode = CAM_ACCESS_MODE_IO;
	}

	if (dev->cfg.use_ion) {
		ret = ion_ci_read_io_data(get_te_device(dev), buf, len);
	} else {
		for (i = 0; i < len; i ++) {
			// from read_cam_control(dev, IO_DATA_ADDR);
			buf[i] = readb(dev->mod_addr + IO_DATA_ADDR);
		}
		ret = 0;
	}

	return ret;
}

int ci_read_io_data(struct ci_device *dev, u8 *buf, u32 len)
{
	int ret;

	if (!buf || !len)
		return -EFAULT;

	log_trace("len:%u", len);

	mutex_lock(&dev->reset_lock);
	if (dev->cam_ready != CAM_READY_SUCCESS) {
		mutex_unlock(&dev->reset_lock);
		return -EIO;
	}

	ret = read_io_data(dev, buf, len);

	mutex_unlock(&dev->reset_lock);

	return ret;
}

static int write_io_data(struct ci_device *dev, u8 *buf, u32 len)
{
	int i, ret;

	if (unlikely(dev->access_mode != CAM_ACCESS_MODE_IO)) {
		log_debug("(DEBUG) change access_mode: IO");
		CI_WRITE16(dev, (POD_MODE | IO_INT_MODE), CREG_CTRL_STATUS_3);
		CI_WRITE16(dev, CHIP_MODE_IO, CREG_PC_CARD_CTRL_1);
		dev->access_mode = CAM_ACCESS_MODE_IO;
	}

	if (dev->cfg.use_ion) {
		ret = ion_ci_write_io_data(get_te_device(dev), buf, len);
	} else {
		for (i = 0; i < len; i++) {
			//from write_cam_control(dev, IO_DATA_ADDR, buf[i]);
			writeb(buf[i], dev->mod_addr + IO_DATA_ADDR);
		}
		ret = 0;
	}

	return ret;
}

int ci_write_io_data(struct ci_device *dev, u8 *buf, u32 len)
{
	int ret;

	if (!buf || !len)
		return -EFAULT;

	log_trace("len:%u", len);

	mutex_lock(&dev->reset_lock);
	if (dev->cam_ready != CAM_READY_SUCCESS) {
		mutex_unlock(&dev->reset_lock);
		return -EIO;
	}

	ret = write_io_data(dev, buf, len);

	mutex_unlock(&dev->reset_lock);

	return ret;
}

void ci_poll_slot_status(struct ci_device *dev, bool *changed, bool *present,
			 enum cam_ready_status *cam_ready)
{
	bool status = check_cd_register(dev);

	*present = status;

	if (status != dev->card_detect) {
		dev->card_detect = status;
		*changed = true;
		*cam_ready = CAM_READY_WAIT;
	} else {
		*changed = false;
		*cam_ready = dev->cam_ready;
	}
}

bool ci_check_card_detect(struct ci_device *dev)
{
	return check_cd_register(dev);
}

/* Similar with ci_poll_slot_status but does not change its status */
int ci_get_slot_status(struct ci_device *dev, enum cam_ready_status *cam_ready)
{
	bool status;

	if (!dev)
		return -ENODEV;
	if (!cam_ready)
		return -EFAULT;

	status = check_cd_register(dev);
	if (status)
		*cam_ready = dev->cam_ready;
	else
		*cam_ready = CAM_READY_WAIT;

	return 0;
}

// Not check card detect & ready
// inside mutex
static u8 read_camready(struct ci_device *dev)
{
	return read_attribute_mem(dev, (0 << 1));
}

enum slot_reset_state {
	SLOT_STATE_POWER_OFF = 0,
	SLOT_STATE_POWER_ON,
	SLOT_STATE_CARD_RESET,
	SLOT_STATE_CARD_RESET_N,
	SLOT_STATE_ENABLE_CARD,
	SLOT_STATE_SUCCESS,
};

static bool check_abort(struct ci_device *dev, const char *str)
{
	if (!check_cd_register(dev)) {
		log_warning("cd register off -%s", str);
		return true;
	}

	if (dev->reset_abort) {
		log_warning("reset abort -%s", str);
		return true;
	}

	return false;
}

static void slot_reset_work(struct work_struct *work)
{
	struct ci_device *dev;
	struct ci_callback *cb;
	int i, delay;
	u16 val;
	bool ready = false;
	enum slot_reset_state state = SLOT_STATE_POWER_OFF;
	u8 type;

	dev = container_of(work, struct ci_device, reset_work);
	cb = &dev->lxdvb_cb;

	mutex_lock(&dev->reset_lock);
	dev->cam_ready = CAM_READY_WAIT;

	if (check_abort(dev, "init"))
		goto error;

	while (state != SLOT_STATE_SUCCESS)
	{
		val = CI_READ16(dev, CREG_CTRL_STATUS_1);

		switch (state) {
		case SLOT_STATE_POWER_OFF:
			val = 0x0000;
			delay = DELAY_CAM_INIT_VCC_RESET;
			state = SLOT_STATE_POWER_ON;
			break;
		case SLOT_STATE_POWER_ON:
			val |= VCC_SW0;		//POWER ON
			delay = DELAY_CAM_INIT_VCC_RESET;
			state = SLOT_STATE_CARD_RESET;
			break;
		case SLOT_STATE_CARD_RESET:
			val |= CARD_RESET;
			delay = DELAY_CAM_INIT_RESET;
			state = SLOT_STATE_CARD_RESET_N;
			break;
		case SLOT_STATE_CARD_RESET_N:
			val &= ~CARD_RESET;
			delay = DELAY_CAM_INIT_EN_CARD;
			state = SLOT_STATE_ENABLE_CARD;
			break;
		case SLOT_STATE_ENABLE_CARD:
			val |= EN_PCCARD;
			delay = DELAY_CAM_INIT_END;
			state = SLOT_STATE_SUCCESS;
			break;
		default:
			break;
		}

		CI_WRITE16(dev, val, CREG_CTRL_STATUS_1);

		ci_sleep(delay);
		if (check_abort(dev, "state machine"))
			goto error;
	}

	/* Ready for CAM ready */
	for (i = 0; i < TUPLE_CHECK_CNT; i++) {
		type = read_camready(dev);
		log_tuple("(DEBUG): 0x%02x", type);

		if (type == 0x1D) {
			if (i == 0)
				ci_sleep(DELAY_TUPLE_EARLY_CHECK);
			break;
		} else {
			ci_sleep(DELAY_TUPLE_CHECK);
		}

		if (check_abort(dev, "tuple checker"))
			goto error;
	}

	if (i < TUPLE_CHECK_CNT)
		ready = true;

	if (cb->camready_callback) //interrupt callback
		cb->camready_callback(cb->arg, 0, ready);

	if (ready)
		dev->cam_ready = CAM_READY_SUCCESS;
	else
		dev->cam_ready = CAM_READY_FAIL;

	mutex_unlock(&dev->reset_lock);

	log_debug("(DEBUG) done: ready[%d]", ready);
	return;

error:
	if (cb->camready_callback)
		cb->camready_callback(cb->arg, 0, false);
	dev->cam_ready = CAM_READY_FAIL;

	/* Power Off */
	ci_sleep(DELAY_CAM_POWER_OFF);
	CI_WRITE16(dev, 0x0000, CREG_CTRL_STATUS_1);

	log_debug("(DEBUG) fail: state[%d]", state);

	mutex_unlock(&dev->reset_lock);
}


int ci_slot_reset(struct ci_device *dev)
{
	//TODO: Consider pin mux with sci (SCDCR-3995)
	queue_work(system_wq, &dev->reset_work);
	return 0;
}

static void cancel_reset_work(struct ci_device *dev)
{
	dev->reset_abort = true;
	cancel_work_sync(&dev->reset_work);
	dev->reset_abort = false;
}

int ci_slot_shutdown(struct ci_device *dev)
{
	cancel_reset_work(dev);

	mutex_lock(&dev->reset_lock);

	dev->cam_ready = CAM_READY_WAIT;
	ci_sleep(DELAY_CAM_POWER_OFF);
	CI_WRITE16(dev, 0x0000, CREG_CTRL_STATUS_1);

	mutex_unlock(&dev->reset_lock);

	return 0;
}

static bool check_cd_register(struct ci_device *dev)
{
	if (!force_cd_en) {
		u16 state = CI_READ16(dev, CREG_CTRL_STATUS_2);

		if ((state & CD1_CD2_HIGH) == 0x0000)
			return true;
		else
			return false;
	} else {
		return (!force_cd_val) ? false : true;
	}
}

static void write_poll_register(struct ci_device *dev, bool status)
{
	u16 reg = CI_READ16(dev, CREG_INTR_CTRL);

	if (status)
		reg |= CD_POLL;
	else
		reg &= ~CD_POLL;

	CI_WRITE16(dev, reg, CREG_INTR_CTRL);
}

#define CI_IIR				0x10	/* for CI plus */
#define	STAT_REG			0x00000002
int ci_read_iir_register(struct ci_device *dev)
{
	u8 val;

	mutex_lock(&dev->reset_lock);

	if (dev->cam_ready != CAM_READY_SUCCESS) {
		mutex_unlock(&dev->reset_lock);
		return -EIO;
	}

	val = read_cam_control(dev, STAT_REG);

	mutex_unlock(&dev->reset_lock);

	return (val & CI_IIR) ? 1 : 0;
}

int ci_slot_initialize(struct ci_device *dev, bool use_intr)
{
	int i, cnt = 0;
	bool status, old_status = false; //default: false
	struct ci_callback *cb = &dev->lxdvb_cb;

	if (!use_intr || !dev->cfg.support_irq)
		return 0;

	if (ci_request_irq(dev)) {
		log_error("request irq failed");
		return -EPERM;
	}

	/* send remove first */
	if (cb->camchange_irq)
		cb->camchange_irq(cb->arg, 0, false);
	write_poll_register(dev, false);

	for (i = 0; i <MAX_CAMCHANGE_CHECK_ITERATION; i++) {
		status = check_cd_register(dev);

		if (status == old_status)
			break;

		old_status = status;
		cnt++;

		/* Poll register replace */
		write_poll_register(dev, status);
		if (cb->camchange_irq)
			cb->camchange_irq(cb->arg, 0, status);
	}

	dev->card_detect = status;
	dev->use_irq = true;
	dev->reset_abort = false;
	log_noti("status[%d] - %d status changes", status, cnt);

	/* Enable interrupt */
	CI_WRITE16(dev, CD_CHANGED_ENABLE_INT, CREG_INTR_MASK);
	return 0;
}

void ci_slot_finalize(struct ci_device *dev)
{
	cancel_reset_work(dev);

	if (!dev->use_irq)
		return;

	/* Disable interrupt */
	CI_WRITE16(dev, CD_CHANGED_DISABLE_INT, CREG_INTR_MASK);

	ci_free_irq(dev);
	dev->use_irq = false;
}

int ci_set_input(struct ci_device *dev, enum lx_te_input_src src)
{
	struct te_device *tdev = get_te_device(dev);
	enum te_reg_ci_input ci_src;
	int rc;

	log_noti("%s(%s)", __func__, te_input_source_to_str(src));

	ci_src = te_input_src_to_reg_ci_input(src);
	if (ci_src == CI_INPUT_SRC_INVALID) {
		log_error("invalid setting - [%d]", src);
		return -EINVAL;
	}

	log_noti("ci_src: %s", te_ci_src_type_to_str(ci_src));

	te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_CI);

	rc = TE_REG_SetCiInput(ci_src);
	if (rc == 0)
		dev->input_src = src;

	rc = te_notify_ci_src_port(tdev, dev->input_src);
	if (rc)
		log_error("error in te_notify_ci_src_port %d", rc);

	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_CI);

	return rc;
}

int ci_get_input(struct ci_device *dev, enum lx_te_input_src *src)
{
	*src = dev->input_src;
	return 0;
}

int ci_set_speed_mode(struct ci_device *dev, enum ci_mode_speed speed)
{
	log_noti("%s(%d)", __func__, speed);

	return pcmcia_speed_ctrl(dev, speed);
}

int ci_set_rate_mode(struct ci_device *dev, enum ci_mode_datarate rate)
{
	log_noti("%s(%d)", __func__, rate);
	dev->rate_mode = rate;

	return 0;
}

int ci_set_error_mode(struct ci_device *dev, enum ci_mode_error err)
{
	log_noti("%s(%d)", __func__, err);
	dev->error_mode = err;

	return 0;
}

int ci_get_speed_mode(struct ci_device *dev, enum ci_mode_speed *speed)
{
	*speed = dev->speed;
	log_debug("(DEBUG) %s(%d)", __func__, *speed);

	return 0;
}

int ci_get_rate_mode(struct ci_device *dev, enum ci_mode_datarate *rate)
{
	*rate = dev->rate_mode;
	log_debug("(DEBUG) %s(%d)", __func__, *rate);

	return 0;
}

int ci_get_error_mode(struct ci_device *dev, enum ci_mode_error *err)
{
	*err = dev->error_mode;
	log_debug("(DEBUG) %s(%d)", __func__, *err);

	return 0;
}

static irqreturn_t irq_handler(int irq, void *dev_id)
{
	struct ci_device *dev = dev_id;
	struct ci_callback *cb;
	u16 intr_flag = 0xFFFF;
	bool status, old_status;

	/* Read and Clear Interrupt Flag */
	intr_flag = CI_READ16(dev, CREG_INTR_FLAG);
	CI_WRITE16(dev, intr_flag & 0xFE, CREG_INTR_FLAG);

	if (intr_flag & CD_CHANGED) {
		/* Read CD Register */
		status = check_cd_register(dev);
		old_status = status;

		/* POLL Register Write */
		write_poll_register(dev, status);

		/* Retry for stable detecting */
		status = check_cd_register(dev);
		if (status != old_status) {
			write_poll_register(dev, status);
		}

		dev->card_detect = status;

		cb = &dev->lxdvb_cb;
		if (cb->camchange_irq)
			cb->camchange_irq(cb->arg, 0, status);
	}

	return IRQ_HANDLED;
}

#define SMBIDCYR		(0x00)
#define SMBCR			(0x14)
#define IDCY_MASK		(0xf)
#define IDLE_CYCLE		0x00
#define SMBCR_MW16BIT	(1 << 6)
#define SMBCR_WAITEN	(1 << 2)
#define SMBCR_RBLE		(1 << 0)
static void smc_hw_init(struct ci_device *dev)
{
	if (dev->cfg.use_ion) {
		u32 val;

		ion_ci_smc_write32(get_te_device(dev), IDLE_CYCLE & IDCY_MASK,
				   SMBIDCYR);
		ion_ci_smc_write32(get_te_device(dev),
				   SMBCR_MW16BIT | SMBCR_WAITEN | SMBCR_RBLE,
				   SMBCR);

		ion_ci_smc_read32(get_te_device(dev), &val, SMBIDCYR);
		log_debug("smc_addr[0x%02x] = 0x%08X", SMBIDCYR, val);
		ion_ci_smc_read32(get_te_device(dev), &val, SMBCR);
		log_debug("smc_addr[0x%02x] = 0x%08X", SMBCR, val);
		return;
	}

	writel(IDLE_CYCLE & IDCY_MASK, dev->smc_addr + SMBIDCYR);
	writel(SMBCR_MW16BIT | SMBCR_WAITEN | SMBCR_RBLE,
	       dev->smc_addr + SMBCR);

	log_debug("smc_addr[0x%02x] = 0x%08X", SMBIDCYR,
		  readl(dev->smc_addr + SMBIDCYR));
	log_debug("smc_addr[0x%02x] = 0x%08X", SMBCR,
		  readl(dev->smc_addr + SMBCR));
}

static void hw_init(struct ci_device *dev)
{
	u16 reg_val;
	int rc;

	log_noti("perform hw_init");

	init_ctop_configurations();

	/* spi initialization (if needed for ion) */
	if (dev->cfg.use_ion) {
		log_noti("start ion_ci_init");
		rc = ion_ci_init(get_te_device(dev));
		if (rc < 0)
			panic("fail in ion_ci_init; %d", rc);
	}

	/* smc initialization */
	if (dev->cfg.smc_need_vcc) {
		/* VCC Enable before access smc (M16P3 issue) */
		reg_val = CI_READ16(dev, CREG_CTRL_STATUS_1);
		CI_WRITE16(dev, (reg_val | VCC_SW0), CREG_CTRL_STATUS_1);

		/* VCC up time: typical 0.5 ms, max 1.5 ms */
		log_noti("VCC on before Access SMC (5 ms)");

		ci_sleep(5);

		smc_hw_init(dev);

		/* Recover Vcc status */
		CI_WRITE16(dev, reg_val, CREG_CTRL_STATUS_1);
	} else {
		smc_hw_init(dev);
	}

	/* Register Initialization */
	CI_WRITE16(dev, 0x0000, CREG_CTRL_STATUS_1);

	CI_WRITE16(dev, POD_MODE, CREG_CTRL_STATUS_3);
	CI_WRITE16(dev, 0x0000, CREG_INTR_CTRL);
	CI_WRITE16(dev, CD_CHANGED_DISABLE_INT, CREG_INTR_MASK);

	ci_sleep(DELAY_INIT_INTR);

	/* Set PCMCIA BUS Speed as Low */
	pcmcia_speed_ctrl(dev, CI_PCMCIA_SPEED_LOW);

	dev->error_mode = CI_ERROR_CHECK_FULL;
	dev->rate_mode = CI_DATARATE_72;

	/* Init Interrupt Flag */
	CI_WRITE16(dev, 0x0000, CREG_INTR_FLAG);

	dev->inited = true;
}

void ci_hw_init(struct ci_device *dev)
{
	// need perform once at first open & resume

	if (dev->inited && !dev->suspended) { // already inited
		log_noti("device already inited - skip");
		return;
	}
	if (!dev->inited && dev->suspended) { // device not opened when resume
		log_noti("not opened when resume - skip");
		return;
	}

	hw_init(dev);
}

// Abnormal Detection or Forced reset for SLT
int ci_hw_ion_reset(struct ci_device *dev)
{
	int rc = 0;

	log_warning("ion reset");

	mutex_lock(&dev->reset_lock);

	if (!dev->cfg.use_ion) {
		log_error("No Device (ION)");
		rc = - ENODEV;
		goto error;
	}

	rc = ion_ci_reset(get_te_device(dev));
	if (rc) {
		log_error("error %d in ion_ci_reg_hw_reset", rc);
		goto error;
	}

	hw_init(dev);
	dev->cam_ready = CAM_READY_WAIT; // status reset
error:
	mutex_unlock(&dev->reset_lock);
	return rc;
}

int ci_hw_ion_init_tp_checker(struct ci_device *dev, u16 pkt_cnt)
{
	int rc;

	// maybe need mutex lock;
	// this API is only for SLT Test, not for real CAM control
	force_cd_en = 1;
	force_cd_val = 0;
	log_warning("Stop CAM Detection");
	log_warning("Init ion TP Checker");

	rc = ion_ci_init_tp_checker(get_te_device(dev), pkt_cnt);
	if (rc)
		log_error("error %d in ion_ci_init_tp_checker", rc);

	return rc;
}

int ci_hw_ion_start_tp_checker(struct ci_device *dev, u16 pkt_cnt)
{
	return ion_ci_start_tp_checker(get_te_device(dev), pkt_cnt);
}

static int ci_io_init(struct ci_device *dev)
{
	int rc = 0;
	struct te_device *tdev = get_te_device(dev);
	// Requested by Demod, internal demod is initially selected to ci output
	enum te_reg_ci_input ci_src = CI_INPUT_SRC_IN_DEMOD;

	rc = TE_REG_SetCiInput(ci_src);
	if (rc) {
		log_error("Error in SetCiInput %d", rc);
		return rc;
	}

	dev->input_src = LX_TE_INPUT_SRC_IN_DEMOD0;
	rc = te_notify_ci_src_port(tdev, dev->input_src);
	if (rc) {
		log_error("error in te_notify_ci_src_port %d", rc);
		return rc;
	}

	return 0;
}

static int ci_io_resume(struct ci_device *dev)
{
	int rc;

	rc = ci_set_input(dev, dev->input_src);
	CHECK_ERROR(rc != 0, return rc, "error in io resume");

	return 0;
}

static int ci_proc_init(struct ci_device *dev)
{
	int ret;

	dev->debug_dir = te_debug_create_dir("ci", NULL);
	if (!dev->debug_dir) {
		log_error("Err in te_debug_create_dir\n");
		return -EIO;
	}

	ret = debug_create_item_files(debug_list, dev, dev->debug_dir);
	if (ret) {
		log_error("error in create item files %d", ret);
		return ret;
	}

	return ret;
}

static int ci_request_irq(struct ci_device *dev)
{
	int ret;

	dev->irq = dev->cfg.irq_num;
	ret = request_irq(dev->irq, irq_handler, 0,
			  // IRQF_SHARED | IRQF_TRIGGER_HIGH,
			  // IRQF_SHARED | IRQF_TRIGGER_RISING,
			  "dvb_ci0", dev);

	return ret;
}

static inline void ci_free_irq(struct ci_device *dev)
{
	free_irq(dev->irq, dev);
}

static int ci_preinit(struct ci_device *dev)
{
	u32 chip = lx_chip();
	struct ci_cfg *cfg = &dev->cfg;
	struct te_config *te_cfg = te_get_config();

	/* get chip config */
	switch (chip) {
	case LX_CHIP_M19:
	case LX_CHIP_O18:
		cfg->smc_need_vcc = 1;
		break;
	default: // O20 ~
		cfg->smc_need_vcc = 0;
		break;
	}

	//Check when using interrupt mode
	cfg->irq_num = CI_IRQ_NUM;

	cfg->support_irq = false;

	cfg->use_ion = te_cfg->use_ion;
	cfg->smc_phys_addr = CI_SMC_BASE;
	cfg->smc_phys_size = CI_SMC_SIZE;
	cfg->reg_base = COMMON_CI_REG_BASE;
	cfg->reg_size = COMMON_CI_REG_SIZE;
	cfg->mod_base = COMMON_CI_CAM_BASE;
	cfg->mod_size = COMMON_CI_CAM_SIZE;
	cfg->cis_addr_limit = COMMON_CI_CAM_SIZE;	//not used

	return 0;

}

static int ci_init(struct ci_device *dev)
{
	struct ci_cfg *cfg = &dev->cfg;

	ci_preinit(dev);

	dev->card_detect = false;
	dev->cam_ready = CAM_READY_WAIT;
	dev->access_mode = CAM_ACCESS_MODE_NONE;
	mutex_init(&dev->reset_lock);
	dev->use_irq = false;

	if (!dev->cfg.use_ion) { // non-ion operation (legacy)
		/* ioremap for reg_addr, mod_addr */
		dev->reg_addr = ioremap(cfg->reg_base, cfg->reg_size);
		dev->mod_addr = ioremap(cfg->mod_base, cfg->mod_size);

		/* ioremap for smc_addr */
		dev->smc_addr = ioremap(cfg->smc_phys_addr, cfg->smc_phys_size);

		CHECK_ERROR((!dev->reg_addr || !dev->mod_addr),
			     goto error_ioremap, "ioremap failed");
		CHECK_ERROR(!dev->smc_addr, goto error_ioremap,
			    "ioremap failed");

		log_debug("dev->reg_addr = 0x%p", dev->reg_addr);
		log_debug("dev->mod_addr = 0x%p", dev->mod_addr);
	}

	INIT_WORK(&dev->reset_work, slot_reset_work);

	// device init should be delayed due to spi control
	//ci_hw_init(dev);

	ci_io_init(dev);
	ci_proc_init(dev);

	return 0;

error_ioremap:
	if (dev->mod_addr)
		iounmap(dev->mod_addr);
	dev->mod_addr = NULL;

	if (dev->reg_addr)
		iounmap(dev->reg_addr);
	dev->reg_addr = NULL;

	if (dev->smc_addr)
		iounmap(dev->smc_addr);
	dev->smc_addr = NULL;

	return -EFAULT;
}

static void ci_remove(struct ci_device *dev)
{
	cancel_reset_work(dev);

	if (dev->mod_addr)
		iounmap(dev->mod_addr);
	dev->mod_addr = NULL;

	if (dev->reg_addr)
		iounmap(dev->reg_addr);
	dev->reg_addr = NULL;

	if (dev->smc_addr)
		iounmap(dev->smc_addr);
	dev->smc_addr = NULL;
}

/* ************************************************************************** */
/* Initialisation/shutdown functions */
static int probe(struct platform_device *pdev)
{
	struct ci_device *dev;
	int rc;

	dev = devm_kzalloc(&pdev->dev, sizeof(*dev), GFP_KERNEL);
	CHECK_ERROR(!dev, goto error, "no memory");

	platform_set_drvdata(pdev, dev);
	te_register_subdev(&pdev->dev, &dev->subdev);

	rc = ci_init(dev);
	CHECK_ERROR(rc, goto error, "Error in ci_init(%d)", rc);

	log_noti("ci_device probe done");

	return 0;
error:
	panic("ci_device probe failed\n");
}

static void remove(struct platform_device *pdev)
{
	struct ci_device *dev = platform_get_drvdata(pdev);

	ci_remove(dev);
	log_noti("ci_device remove done");
}

#if (LINUX_VERSION_CODE < KERNEL_VERSION(6, 5, 0))
static int legacy_remove(struct platform_device *pdev)
{
	remove(pdev);
	return 0;
}
#endif

static int suspend(struct platform_device *pdev, pm_message_t state)
{
	struct ci_device *dev = platform_get_drvdata(pdev);
	struct te_device *tdev = get_te_device(dev);

	te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_CI);

	printk("ci_device - suspend BEGIN\n");

	dev->access_mode = CAM_ACCESS_MODE_NONE;
	dev->suspended = true;

	printk("ci_device - suspend END\n");
	return 0;
}

static int resume(struct platform_device *pdev)
{
	struct ci_device *dev = platform_get_drvdata(pdev);
	struct te_device *tdev = get_te_device(dev);

	printk("ci_device - resume BEGIN\n");

	ci_hw_init(dev);
	ci_io_resume(dev);

	dev->suspended = false;

	printk("ci_device - resume END\n");

	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_CI);

	return 0;
}

static struct platform_driver platform_driver = {
	.probe = probe,
	.suspend = suspend,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 5, 0))
	.remove = remove,
#else
	.remove = legacy_remove,
#endif
	.resume = resume,
	.driver = {
		.name = CI_DEVICE_NAME,
	},
};

int ci_module_init(void)
{
	int ret;

	init_logm();

	ret = platform_driver_register(&platform_driver);
	if (ret) {
		log_error("%s platform driver register failed:%d",
			  CI_DEVICE_NAME, ret);
		return ret;
	}

	return 0;
}

void ci_module_exit(void)
{
	platform_driver_unregister(&platform_driver);
}

struct ci_device *ci_get_device(struct te_device *dev)
{
	struct te_subdev *sd;

	sd = te_get_subdev(dev, CI_DEVICE_NAME);
	if (!sd)
		return NULL;

	return te_subdev_to_ci_device(sd);
}

int ci_register_callback_funcs(struct ci_device *dev,
			       struct ci_callback *cb)
{
	dev->lxdvb_cb = *cb;
	return 0;
}
