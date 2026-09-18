/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2018 by LG Electronics Inc.
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
 *  CI Driver for linux dvb_ca(DEMUX&CA)
 *
 *  @author	Ilkyu Kim
 *  @version	1.1
 *  @date	2025-07-07
 *  @note	Additional information.
 */

/*
 * dvb_ca.c: generic DVB functions for EN50221 CAM interfaces
 *
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

#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/vmalloc.h>
#include <linux/delay.h>
#include <linux/spinlock.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/freezer.h>

#include "lxdvb_ca.h"

#include "lxdvb_impl.h"
#include <lg1k/te/debug.h>
#include <lg1k/te/ci.h>
#include <lg1k/te/buffer.h>
#include <lg1k/te/dump.h>
#include <lg1k/te/util.h>
#include <lg1k/te/io.h>

#include "lxdvb_proc.h"
#include "te_dvb_ca_kapi.h"

//Remains for future use
static int dvb_ca_debug;
static int _polling_delay = 2;

module_param_named(lxdvb_ca_debug, dvb_ca_debug, int, 0644);
MODULE_PARM_DESC(lxdvb_ca_debug, "enable verbose debug messages");

module_param_named(lxdvb_ca_polling, _polling_delay, int, 0644);
MODULE_PARM_DESC(lxdvb_ca_polling, "polling delay");

#define INIT_TIMEOUT_SECS 10

//#define HOST_LINK_BUF_SIZE	0x2000

#define RX_BUFFER_SIZE (256 * 1024)

#define MAX_RX_PACKETS_PER_ITERATION	10
#define MAX_PARSE_ATTR_ITERATION		4	// 3 retries

#define CTRLIF_DATA      0
#define CTRLIF_COMMAND   1
#define CTRLIF_STATUS    1
#define CTRLIF_SIZE_LOW  2
#define CTRLIF_SIZE_HIGH 3

#define CMDREG_HC        1	/* Host control */
#define CMDREG_SW        2	/* Size write */
#define CMDREG_SR        4	/* Size read */
#define CMDREG_RS        8	/* Reset interface */
#define CMDREG_FRIE   0x40	/* Enable FR interrupt */
#define CMDREG_DAIE   0x80	/* Enable DA interrupt */
#define IRQEN (CMDREG_DAIE)

#define STATUSREG_RE     1	/* read error */
#define STATUSREG_WE     2	/* write error */
#define STATUSREG_FR  0x40	/* module free */
#define STATUSREG_DA  0x80	/* data available */
#define STATUSREG_TXERR (STATUSREG_RE|STATUSREG_WE) /* general transfer error */

#define _IOC_RW		(_IOC_READ | _IOC_WRITE)

#define DVB_CA_SLOTSTATE_NONE			0
#define DVB_CA_SLOTSTATE_UNINITIALISED		1
#define DVB_CA_SLOTSTATE_RUNNING		2
#define DVB_CA_SLOTSTATE_INVALID		3
#define DVB_CA_SLOTSTATE_WAITREADY		4
#define DVB_CA_SLOTSTATE_VALIDATE_CHECK_CIS	5
#define DVB_CA_SLOTSTATE_VALIDATE_WRITE_COR	6
#define DVB_CA_SLOTSTATE_VALIDATE_SET_RS	7
#define DVB_CA_SLOTSTATE_WAITFR			8
#define DVB_CA_SLOTSTATE_LINKINIT		9

#define CA_NOTI(ca_state, fmt, args...)				\
	do {							\
		pr_info("(0)-%04u [CI][EN50221][%-18s]"fmt"\n",	\
			current->pid,				\
			get_slot_state_str(ca_state), ##args);	\
		log_noti(fmt, ##args);				\
	} while(0)

#define CA_WARN(ca_state, fmt, args...)				\
	do {							\
		pr_warn("(0)-%04u [CI][EN50221][%-18s]"fmt"\n",	\
			current->pid,				\
			get_slot_state_str(ca_state), ##args);	\
		log_warning(fmt, ##args);			\
	} while(0)

#define CA_ERR(ca_state, fmt, args...)				\
	do {							\
		pr_err("(0)-%04u [CI][EN50221][%-18s]"fmt"\n",	\
		       current->pid,				\
		       get_slot_state_str(ca_state), ##args);	\
		log_error(fmt, ##args);				\
	} while(0)

enum {
	CA_DEBUG_TRACE = (0x1) << 0,
	CA_DEBUG_RW = (0x1) << 1,
	CA_DEBUG_STATE = (0x1) << 2,
	CA_DEBUG_WRITE = (0x1) << 3,
};

enum ca_slot_bits {
	CA_SLOT_CAMREADY = 0,
	CA_SLOT_CAMFAIL,
};

static struct ci_lge_control_param {
	u32 id;
	const char *name;
	u32 size;
	u32 dir;
} ci_lge_control_params[] = {
	{CA_EXT_CID_INPUTSOURCE, "inputsource", sizeof(struct ca_ext_source),
	 _IOC_RW},
	{CA_EXT_CID_DA_STATUS, "readda", 0, _IOC_READ},
	{CA_EXT_CID_ERROR_MODE, "errormode", 0, _IOC_RW},
	{CA_EXT_CID_PLUS_CAPA, "cipcapa", 0, _IOC_READ},
	{CA_EXT_CID_DATA_RATE, "datarate", 0, _IOC_READ},
	{CA_EXT_CID_PCMCIA_SPEED, "pcmcia_speed", 0, _IOC_WRITE},
	{CA_EXT_CID_FAST_POOL_TIME, "fastpool", 0, _IOC_READ},
	{CA_EXT_CID_PLUS_VERSION, "cipver", 0, _IOC_READ},
	{CA_EXT_CID_PLUS_IIR_STATUS, "iirstat", 0, _IOC_READ},
	{CA_EXT_CID_SET_RS_BIT, "setrs", 0, _IOC_WRITE},
	{CA_EXT_CID_GET_NEGO_BUFF, "negobuff", 0, _IOC_READ},
};

struct debug_dump {
	bool running;
	struct mutex mutex;
	struct te_hwbuf *buf;
};

/* Information on a CA slot */
struct dvb_ca_slot {

	/* current state of the CAM */
	int slot_state;

	/* mutex used for serializing access to one CI slot */
	struct mutex slot_lock;
	spinlock_t spinlock;

	/* Number of CAMCHANGES that have occurred since last processing */
	atomic_t camchange_count;	//not used this time

	/* Type of last CAMCHANGE */
	int camchange_type;
	int camchanged;

	/* base address of CAM config */
	u32 config_base;

	/* Check if ciplus or not */
	u32 version;
	u8 is_ciplus;

	/* CIS parse retry count */
	u8 retry_parse;

	/* value to write into Config Control register */
	u8 config_option;

	/* if 1, the CAM supports DA IRQs */
	u8 da_irq_supported:1;

	/* size of the buffer to use when talking to the CAM */
	int link_buf_size;

	/*  temporal buffer for hw read/write sequence */
	u8 *link_read_buf;
	u8 *link_write_buf;

	/* buffer for incoming packets */
	u8 *rx_buf;
	struct te_pktbuf p_rx_buf;

	/* timer used during various states of the slot */
	unsigned long timeout;

	/* Check for elapsed initilization time */
	u64 start_time;

	/* timer used for check cis (for error case) */
	unsigned long check_interval;
	/* cam ready irq without check the states */
	unsigned long flags;
};

/* Private CA-interface information */
struct lxdvb_ca {

	/* the DVB device */
	struct dvb_device *dvbdev;

	/* Flags describing the interface (DVB_CA_FLAG_*) */
	u32 flags;

	/* number of slots supported by this CA interface */
	unsigned int slot_count;

	/* information on each slot */
	struct dvb_ca_slot *slot_info;

	/* wait queues for read() and write() operations */
	wait_queue_head_t wait_queue;

	/* wait queues for thread sleep opeartions */
	wait_queue_head_t thread_wait_queue;

	/* PID of the monitoring thread */
	struct task_struct *thread;

	/* Flag indicating if the CA device is open */
	unsigned int open;

	/* Flag indicating the thread should wake up now */
	unsigned int wakeup:1;

	/* Delay the main thread should use */
	unsigned long delay;

	/* Prevent verbose messages */
	unsigned long running_time;
	int wakecount;

	/* Slot to start looking for data to read from in the next user-space read operation */
	int next_read_slot;

	/* mutex serializing ioctls */
	struct mutex ioctl_mutex;

	/* Prepare for error_mode compatiblity (can be ignored) */
	u8 ignore_error;

	struct te_debug_dir *debug_dir;
	struct lxdvb_proc_dir *proc_dir;

	struct ci_device *dev;
	struct te_device *tdev;
	struct debug_dump dump;
};

static int check_camchange_by_intr(struct lxdvb_ca *ca, int slot);
static int lxdvb_ca_slot_shutdown(struct lxdvb_ca *ca, int slot);
static void lxdvb_ca_thread_wakeup(struct lxdvb_ca *ca);
static void lxdvb_ca_thread_update_slot_delay(struct lxdvb_ca *ca,
					      int slot_num);
//static void dvb_ca_thread_update_delay(struct lxdvb_ca *ca);
static int lxdvb_ca_read_data(struct lxdvb_ca *ca, int slot, u8 *ebuf,
			      int ecount);
static int lxdvb_ca_write_data(struct lxdvb_ca *ca, int slot, u8 *ebuf,
			       int ecount);

static struct ci_lge_control_param *get_ci_lge_control_param(u32 id);

static void ca_dump_write(struct debug_dump *d,
			  const char __user *data, u32 size, bool is_read);
/* DEBUG related functions / macros */

/**
 * Safely find needle in haystack.
 *
 * @haystack: Buffer to look in.
 * @hlen: Number of bytes in haystack.
 * @needle: Buffer to find.
 * @nlen: Number of bytes in needle.
 * @return Pointer into haystack needle was found at, or NULL if not found.
 */
static char *findstr(char *haystack, int hlen, char *needle, int nlen)
{
	int i;

	if (hlen < nlen)
		return NULL;

	for (i = 0; i <= hlen - nlen; i++) {
		if (!strncmp(haystack + i, needle, nlen))
			return haystack + i;
	}

	return NULL;
}

static char *findstr_case(char *haystack, int hlen, char *needle, int nlen)
{
	int i;

	if (hlen < nlen)
		return NULL;

	for (i = 0; i <= hlen - nlen; i++) {
		if (!strncasecmp(haystack + i, needle, nlen))
			return haystack + i;
	}

	return NULL;
}

/* DEBUG Function */
static const char *get_slot_state_str(int slot_state)
{
	switch (slot_state) {
	case DVB_CA_SLOTSTATE_NONE:
		return "NONE";
	case DVB_CA_SLOTSTATE_UNINITIALISED:
		return "UNINITIALISED";
	case DVB_CA_SLOTSTATE_RUNNING:
		return "RUNNING";
	case DVB_CA_SLOTSTATE_INVALID:
		return "INVALID";
	case DVB_CA_SLOTSTATE_WAITREADY:
		return "WAITREADY";
	case DVB_CA_SLOTSTATE_VALIDATE_CHECK_CIS:
		return "VALIDATE_CHECK_CIS";
	case DVB_CA_SLOTSTATE_VALIDATE_WRITE_COR:
		return "VALIDATE_WRITE_COR";
	case DVB_CA_SLOTSTATE_VALIDATE_SET_RS:
		return "VALIDATE_SET_RS";
	case DVB_CA_SLOTSTATE_WAITFR:
		return "WAITFR";
	case DVB_CA_SLOTSTATE_LINKINIT:
		return "LINKINIT";
	default:
		return "UNKNOWN(ERROR)";
	}
}

static void update_slot_state(struct lxdvb_ca *ca, int slot, int state)
{
	ca->slot_info[slot].slot_state = state;
	lxdvb_ca_thread_update_slot_delay(ca, slot);
}

static void invalid_slot_state(struct lxdvb_ca *ca, int slot)
{
	ca->slot_info[slot].slot_state = DVB_CA_SLOTSTATE_INVALID;
	lxdvb_ca_thread_update_slot_delay(ca, slot);
	ca->running_time = 0;
	ca->wakecount = 0;
}

/* EN50221 physical interface functions */

/**
 * lxdvb_ca_check_camstatus - Check CAM status.
 */
static int lxdvb_ca_check_camstatus(struct lxdvb_ca *ca, int slot)
{
	struct dvb_ca_slot *s = &ca->slot_info[slot];
	bool cam_present_now, cam_changed;
	enum cam_ready_status cam_ready;

	/* IRQ mode */
	if (ca->flags & DVB_CA_FLAG_IRQ_CAMCHANGE) {
		return check_camchange_by_intr(ca, slot);
	}

	/* Poll mode */
	ci_poll_slot_status(ca->dev, &cam_changed, &cam_present_now,
			    &cam_ready);

	if (!cam_changed) {
		bool cam_present_old = (s->slot_state != DVB_CA_SLOTSTATE_NONE);
		cam_changed = (cam_present_now != cam_present_old);
	}

	if (cam_changed) {
		if (s->slot_state != DVB_CA_SLOTSTATE_NONE) {
			CA_NOTI(s->slot_state, "shutdown by poll");
			lxdvb_ca_slot_shutdown(ca, slot);
		}
		/* if a CAM is NOW present, initialise it */
		if (cam_present_now) {
			CA_NOTI(s->slot_state, "cam insertion detected");
			update_slot_state(ca, slot,
					  DVB_CA_SLOTSTATE_UNINITIALISED);
		}
	} else {
		if (s->slot_state == DVB_CA_SLOTSTATE_WAITREADY) {
			if (cam_ready == CAM_READY_SUCCESS)
				set_bit(CA_SLOT_CAMREADY, &s->flags);
			else if (cam_ready == CAM_READY_FAIL)
				set_bit(CA_SLOT_CAMFAIL, &s->flags);
		}
	}

	return cam_changed;
}

/**
 * lxdvb_ca_wait_if_status - Wait for flags to become set on the STATUS
 *	 register on a CAM interface, checking for errors and timeout.
 *
 * @ca: CA instance.
 * @slot: Slot on interface.
 * @waitfor: Flags to wait for.
 * @timeout_ms: Timeout in milliseconds.
 *
 * @return 0 on success, nonzero on error.
 */
static int lxdvb_ca_wait_if_status(struct lxdvb_ca *ca, int slot,
				 u8 waitfor, int timeout_hz)
{
	unsigned long timeout;
	unsigned long start;

	log_debug("%s", __func__);

	/* loop until timeout elapsed */
	start = jiffies;
	timeout = start + timeout_hz;
	while (1) {
		/* read the status and check for error */
		int res = ci_read_cam_control(ca->dev, CTRLIF_STATUS);
		if (res < 0)
			return -EIO;

		//log_error("wait_if:0x%02x", res);
		/* if we got the flags, it was successful! */
		if (res & waitfor) {
			log_debug("%s succeeded timeout:%lu", __func__,
				  jiffies - start);
			return 0;
		}

		/* check for timeout */
		if (time_after(jiffies, timeout)) {
			break;
		}

		/* check CAM status and exit immediately if cam changed */
		if (lxdvb_ca_check_camstatus(ca, slot)) {
			ca->wakeup = 1;
			return -EIO;
		}

		/* wait for a bit */
		/* wait 10ms by legacy driver (NEGO_BUFF_CHECK_FR/DA) */
		usleep_range(10 * 1000, 10 * 1000);
	}

	CA_ERR(ca->slot_info[slot].slot_state, "%s failed timeout:%lu",
	       __func__, jiffies - start);

	/* if we get here, we've timed out */
	return -ETIMEDOUT;
}

/**
 * lxdvb_ca_write_buf_size - This function is same as lxdvb_ca_write_data
 *		             but ignores unnecessary DA, FR, WE check,
 *		             and remains SW (Size Write)
 *
 * @ca: CA instance.
 * @slot: Slot to write to.
 * @ebuf: The data in this buffer only treats as buffer size
 * @count: Size of ebuf. (2 bytes)
 *
 * @return Number of bytes written, or < 0 on error.
 */
static int lxdvb_ca_write_buf_size(struct lxdvb_ca *ca, int slot, u8 *buf,
				   int bytes_write)
{
	int status;
	struct ci_device *dev = ca->dev;

	log_debug("%s", __func__);

	/* sanity check */
	if (bytes_write > ca->slot_info[slot].link_buf_size)
		return -EINVAL;

	/* send the amount of data */
	if ((status = ci_write_cam_control(dev, CTRLIF_SIZE_HIGH,
						bytes_write >> 8)) != 0)
		goto exit;
	if ((status = ci_write_cam_control(dev, CTRLIF_SIZE_LOW,
						bytes_write & 0xff)) != 0)
		goto exit;

	/* send the buffer */
	status = ci_write_io_data(dev, buf, bytes_write);
	if (status != 0) {
		log_error("ci_write_io_data failed %d", status);
		goto exit;
	}

	status = bytes_write;
	log_debug("Wrote CA packet for slot %i size:0x%x", slot, bytes_write);

exit:
	ci_write_cam_control(dev, CTRLIF_COMMAND, 0);
	return status;
}
/**
 * lxdvb_ca_link_init - Initialise the link layer connection to a CAM.
 *
 * @ca: CA instance.
 * @slot: Slot id.
 *
 * @return 0 on success, nonzero on failure.
 */
static int lxdvb_ca_link_init(struct lxdvb_ca *ca, int slot)
{
	int ret;
	int buf_size;
	u8 buf[2];
	struct ci_device *dev = ca->dev;

	log_debug("%s", __func__);

	if (ca->slot_info[slot].link_read_buf) {
		vfree(ca->slot_info[slot].link_read_buf);
		ca->slot_info[slot].link_read_buf = NULL;
	}
	if (ca->slot_info[slot].link_write_buf) {
		vfree(ca->slot_info[slot].link_write_buf);
		ca->slot_info[slot].link_write_buf = NULL;
	}

	/* we'll be determining these during this function */
	ca->slot_info[slot].da_irq_supported = 0;

	/* set the host link buffer size temporarily. it will be overwritten with the
	 * real negotiated size later. */
	ca->slot_info[slot].link_buf_size = 2;

	/* read the buffer size from the CAM */
	if ((ret = ci_write_cam_control(dev, CTRLIF_COMMAND, CMDREG_SR)) != 0)
		return ret;
	/* follow by legacy codes 10 ms * 600 retry = 6 sec */
	if ((ret = lxdvb_ca_wait_if_status(ca, slot, STATUSREG_DA, HZ*6)) != 0)
		return ret;
	if ((ret = lxdvb_ca_read_data(ca, slot, buf, 2)) != 2)
		return -EIO;
	if ((ret = ci_write_cam_control(dev, CTRLIF_COMMAND, 0)) != 0)
		return ret;

	/* store it, and choose the minimum of our buffer and the CAM's buffer size */
	buf_size = (buf[0] << 8) | buf[1];
	ca->slot_info[slot].link_buf_size = buf_size;

	ca->slot_info[slot].link_read_buf = vmalloc(buf_size);
	if (ca->slot_info[slot].link_read_buf == NULL) {
		CA_ERR(ca->slot_info[slot].slot_state, "fail to alloc "
		       "read buf");
		return -ENOMEM;
	}
	ca->slot_info[slot].link_write_buf = vmalloc(buf_size);
	if (ca->slot_info[slot].link_write_buf == NULL) {
		CA_ERR(ca->slot_info[slot].slot_state, "fail to alloc "
		       "write buf");
		vfree(ca->slot_info[slot].link_read_buf);
		ca->slot_info[slot].link_read_buf = NULL;
		return -ENOMEM;
	}

	buf[0] = buf_size >> 8;
	buf[1] = buf_size & 0xff;
	log_debug("Chosen link buffer size of %i", buf_size);

	/* write the buffer size to the CAM */
	if ((ret = ci_write_cam_control(dev, CTRLIF_COMMAND,
					     CMDREG_HC | CMDREG_SW)) != 0)
		return ret;
	/* follow by legacy codes 10 ms * 600 retry = 6 sec */
	if ((ret = lxdvb_ca_wait_if_status(ca, slot, STATUSREG_FR, HZ*6)) != 0)
		return ret;
	if ((ret = lxdvb_ca_write_buf_size(ca, slot, buf, 2)) != 2)
		return -EIO;

	/* from legacy driver 5 ms wait (AFTER_WRITE_DATA) */
	usleep_range(5 * 1000, 5 * 1000);
	if ((ret = ci_write_cam_control(dev, CTRLIF_COMMAND, 0)) != 0)
		return ret;

	/* success */
	return 0;
}

#define TUPLE_ADDR(addr) (0xd8000000 + ((addr) << 1))

/**
 * lxdvb_ca_read_tuple - Read a tuple from attribute memory.
 *
 * @ca: CA instance.
 * @slot: Slot id.
 * @address: Address to read from. Updated.
 * @tupleType: Tuple id byte. Updated.
 * @tupleLength: Tuple length. Updated.
 * @tuple: Dest buffer for tuple (must be 256 bytes). Updated.
 *
 * @return 0 on success, nonzero on error.
 */
static int lxdvb_ca_read_tuple(struct lxdvb_ca *ca, int slot,
			     int *address, int *tupleType, int *tupleLength,
			     u8 *tuple)
{
	int i;
	int _tupleType;
	int _tupleLength;
	int _address = *address;
	struct ci_device *dev = ca->dev;

	/* check CAM status */
	if (lxdvb_ca_check_camstatus(ca, slot)) {
		ca->wakeup = 1;
		return -EIO;
	}

	/* grab the next tuple length and type */
	_tupleType = ci_read_attribute_mem(dev, _address);
	if (_tupleType  < 0)
		return _tupleType;
	if (_tupleType == 0xff) {
		log_tuple("END OF CHAIN TUPLE type:0x%x", _tupleType);
		*address += 2;
		*tupleType = _tupleType;
		*tupleLength = 0;
		return 0;
	}
	_tupleLength = ci_read_attribute_mem(dev, _address + 2);
	if (_tupleLength < 0)
		return _tupleLength;
	_address += 4;

	log_tuple("TUPLE type:0x%x length:%i", _tupleType, _tupleLength);

	/* read in the whole tuple */
	for (i = 0; i < _tupleLength; i++) {
		tuple[i] = ci_read_attribute_mem(dev, _address + (i * 2));
		log_tuple("  0x%02x: 0x%02x %c (0x%08x)", i, tuple[i] & 0xff,
			  ((tuple[i] > 31) && (tuple[i] < 127)) ?
			  tuple[i] : '.', TUPLE_ADDR(_address + (i * 2)));

		// By Legacy driver 5 ms wait between tuple reads (DURING_READ_TUPLE)
		// Is it needed?
		usleep_range(5 * 1000, 5 * 1000);
	}
	_address += (_tupleLength * 2);

	// success
	*tupleType = _tupleType;
	*tupleLength = _tupleLength;
	*address = _address;
	return 0;
}

#define STR_COMPAT_LEN	11	/* compatible=[ */
#define STR_CIPLUS_LEN	7	/* ciplus= */
static void tuple_check_ci_plus(struct lxdvb_ca *ca, int slot, char *buf,
				int len)
{
	char *pbuf, mode = 0;
	struct dvb_ca_slot *slot_info = &ca->slot_info[slot];
	u32 version = 0;
	int i, num;

	slot_info->version = 0;
	slot_info->is_ciplus = 0;

	pbuf = findstr_case(buf, len, "compatible[", STR_COMPAT_LEN);
	if (pbuf == NULL)
		return;

	pbuf += STR_COMPAT_LEN;
	len -= (pbuf - buf);

	pbuf = findstr_case(pbuf, len, "ciplus=", STR_CIPLUS_LEN);
	if (pbuf == NULL)
		return;
	pbuf += STR_CIPLUS_LEN;

	if (pbuf[0] == '-')
		return;

	if (pbuf[0] == '+' || pbuf[0] == '*') {
		mode = pbuf[0];
		pbuf++;
	}

	num = simple_strtoul(pbuf, NULL, 10);

	if (num > 0) {
		if (mode == 0 || mode == '+') {
			version = (0x1 << (num - 1));
		} else if (mode == '*') {
			for (i = 0; i < num; i++)
				version |= (0x1 << i);
		}
	}

	log_debug("(DEBUG) version = 0x%08x", version);

	slot_info->version = version;
	slot_info->is_ciplus = (version) ? 1 : 0;
}

static bool has_no_cftable_strings(char* tuple, int len)
{
	if (findstr(tuple, len, "DVB_HOST", 8) == NULL)
		return true;
	if (findstr(tuple, len, "DVB_CI_MODULE", 13) == NULL)
		return true;

	return false;
}

/**
 * lxdvb_ca_parse_attributes - Parse attribute memory of a CAM module,
 *	extracting Config register, and checking it is a DVB CAM module.
 *
 * @ca: CA instance.
 * @slot: Slot id.
 *
 * @return 0 on success, <0 on failure.
 */
static int lxdvb_ca_parse_attributes(struct lxdvb_ca *ca, int slot)
{
	int address = 0;
	int tupleLength;
	int tupleType;
	u8 tuple[257];
	char *dvb_str;
	int rasz;
	int status;
	int got_cftableentry = 0;
	int end_chain = 0;
	int i;
	u16 manfid = 0;
	u16 devid = 0;

	// CISTPL_DEVICE_0A
	if ((status = lxdvb_ca_read_tuple(ca, slot, &address, &tupleType,
					  &tupleLength, tuple)) < 0)
		return status;
	if (tupleType != 0x1D)
		return -EINVAL;

	// CISTPL_DEVICE_0C
	if ((status = lxdvb_ca_read_tuple(ca, slot, &address, &tupleType,
					  &tupleLength, tuple)) < 0)
		return status;
	if (tupleType != 0x1C)
		return -EINVAL;

	// CISTPL_VERS_1
	if ((status = lxdvb_ca_read_tuple(ca, slot, &address, &tupleType,
					  &tupleLength, tuple)) < 0)
		return status;
	if (tupleType != 0x15)
		return -EINVAL;

	tuple_check_ci_plus(ca, slot, tuple, tupleLength);

	// CISTPL_MANFID
	if ((status = lxdvb_ca_read_tuple(ca, slot, &address, &tupleType,
					  &tupleLength, tuple)) < 0)
		return status;
	if (tupleType != 0x20)
		return -EINVAL;
	if (tupleLength != 4)
		return -EINVAL;
	manfid = (tuple[1] << 8) | tuple[0];
	devid = (tuple[3] << 8) | tuple[2];

	// CISTPL_CONFIG
	if ((status = lxdvb_ca_read_tuple(ca, slot, &address, &tupleType,
					  &tupleLength, tuple)) < 0)
		return status;
	if (tupleType != 0x1A)
		return -EINVAL;
	if (tupleLength < 3)
		return -EINVAL;

	/* extract the configbase */
	rasz = tuple[0] & 3;
	if (tupleLength < (3 + rasz + 14))
		return -EINVAL;
	ca->slot_info[slot].config_base = 0;
	for (i = 0; i < rasz + 1; i++) {
		ca->slot_info[slot].config_base |= (tuple[2 + i] << (8 * i));
	}

	/* check it contains the correct DVB string */
	dvb_str = findstr((char *)tuple, tupleLength, "DVB_CI_V", 8);
	if (dvb_str == NULL)
		return -EINVAL;
	if (tupleLength < ((dvb_str - (char *)tuple) + 12))
		return -EINVAL;

	/* is it a version we support? */
	if (strncmp(dvb_str + 8, "1.00", 4)) {
		CA_ERR(ca->slot_info[slot].slot_state, "dvb_ca adapter %d: "
		       "Unsupported DVB CAM module version %c%c%c%c",
		       ca->dvbdev->adapter->num, dvb_str[8], dvb_str[9],
		       dvb_str[10], dvb_str[11]);
		return -EINVAL;
	}

	/* process the CFTABLE_ENTRY tuples, and any after those */
	while ((!end_chain) && (address < 0x1000)) {
		if ((status = lxdvb_ca_read_tuple(ca, slot, &address,
						  &tupleType,
						  &tupleLength, tuple)) < 0)
			return status;
		switch (tupleType) {
		case 0x1B:	// CISTPL_CFTABLE_ENTRY
			if (tupleLength < (2 + 11 + 17))
				break;

			/* if we've already parsed one, just use it */
			if (got_cftableentry)
				break;

			/* get the config option */
			ca->slot_info[slot].config_option = tuple[0] & 0x3f;

			/* OK, check it contains the correct strings */
			if (has_no_cftable_strings(tuple, tupleLength))
				break;

			got_cftableentry = 1;
			break;

		case 0x14:	// CISTPL_NO_LINK
			break;

		case 0xFF:	// CISTPL_END
			end_chain = 1;
			break;

		default:	/* Unknown tuple type - just skip this tuple and move to the next one */
			log_debug("dvb_ca: "
				  "Skipping unknown tupletype:0x%x length:0x%x",
				  tupleType, tupleLength);
			break;
		}
	}

	if ((address > 0x1000) || (!got_cftableentry))
		return -EINVAL;

	log_debug("Valid DVB CAM detected "
		  "MANID:%x DEVID:%x CONFIGBASE:0x%x CONFIGOPTION:0x%x",
		  manfid, devid, ca->slot_info[slot].config_base,
		  ca->slot_info[slot].config_option);

	// success!
	return 0;
}

/**
 * lxdvb_ca_set_configoption - Set CAM's configoption correctly.
 *
 * @ca: CA instance.
 * @slot: Slot containing the CAM.
 */
static int lxdvb_ca_set_configoption(struct lxdvb_ca *ca, int slot)
{
	int configoption;
	struct ci_device *dev = ca->dev;
	struct dvb_ca_slot *s;

	log_debug("%s", __func__);

	s = &ca->slot_info[slot];
	/* set the config option */
	ci_write_attribute_mem(dev, s->config_base, s->config_option);

	/* check it */
	configoption = ci_read_attribute_mem(dev, s->config_base);
	log_debug("Set configoption 0x%x, read configoption 0x%x",
		  s->config_option, configoption & 0x3f);

	/* fine! */
	return 0;

}


/**
 * lxdvb_ca_read_data - This function talks to an EN50221 CAM control
 *	interface. It reads a buffer of data from the CAM. The data can either
 *	be stored in a supplied buffer, or automatically be added to the slot's
 *	rx_buffer.
 *
 * @ca: CA instance.
 * @slot: Slot to read from.
 * @ebuf: If non-NULL, the data will be written to this buffer. If NULL,
 * the data will be added into the buffering system as a normal fragment.
 * @ecount: Size of ebuf. Ignored if ebuf is NULL.
 *
 * @return Number of bytes read, or < 0 on error
 */
static int lxdvb_ca_read_data(struct lxdvb_ca *ca, int slot, u8 *ebuf,
			      int ecount)
{
	struct ci_device *dev = ca->dev;
	int bytes_read;
	int status;
	u8 *buf = NULL;
	struct dvb_ca_slot *slot_info;
	bool wakeup = false;

	log_debug("%s", __func__);
	slot_info = &ca->slot_info[slot];

	/* check if we have space for a link buf in the rx_buffer */
	if (!ebuf) {
		u32 buf_free;

		if (!slot_info->rx_buf) {
			status = -EIO;
			goto exit;
		}

		buf_free = te_pktbuf_free_size(&slot_info->p_rx_buf);
		if (buf_free < slot_info->link_buf_size) {
			status = -EAGAIN;
			goto exit;
		}
	}

	/* check if there is data available */
	if ((status = ci_read_cam_control(dev, CTRLIF_STATUS)) < 0)
		goto exit;
	if (!(status & STATUSREG_DA)) {
		/* no data */
		status = 0;
		goto exit;
	}

	/* read the amount of data */
	if ((status = ci_read_cam_control(dev, CTRLIF_SIZE_HIGH)) < 0)
		goto exit;
	bytes_read = status << 8;
	if ((status = ci_read_cam_control(dev, CTRLIF_SIZE_LOW)) < 0)
		goto exit;
	bytes_read |= status;

	/* check it will fit */
	if (ebuf == NULL) {
		if (bytes_read > slot_info->link_buf_size) {
			CA_ERR(slot_info->slot_state,
			       "dvb_ca adapter %d: CAM tried to send "
			       "a buffer larger than the link buffer size "
			       "(%i > %i)!",
			       ca->dvbdev->adapter->num, bytes_read,
			       slot_info->link_buf_size);
			update_slot_state(ca, slot, DVB_CA_SLOTSTATE_LINKINIT);
			status = -EIO;
			goto exit;
		}
		if (bytes_read < 2) {
			CA_ERR(slot_info->slot_state,
			       "dvb_ca adapter %d: CAM sent a buffer that "
			       "was less than 2 bytes! (%d)",
			       ca->dvbdev->adapter->num, bytes_read);
			update_slot_state(ca, slot, DVB_CA_SLOTSTATE_LINKINIT);
			status = -EIO;
			goto exit;
		}
		/* alloc temporal link buffer to read */
		buf = slot_info->link_read_buf;
		if (!buf) {
			CA_ERR(slot_info->slot_state,
			       "link read buffer is not allocated");
			update_slot_state(ca, slot, DVB_CA_SLOTSTATE_LINKINIT);
			status = -EIO;
			goto exit;
		}
	} else {
		if (bytes_read > ecount) {
			CA_ERR(slot_info->slot_state, "dvb_ca adapter %d: "
			       "CAM tried to send a buffer larger than "
			       "the ecount size! (0x%04x > 0x%04x)",
			       ca->dvbdev->adapter->num, bytes_read, ecount);
			status = -EIO;
			goto exit;
		}
		/* use actual buffer */
		buf = ebuf;
	}

	/* fill the buffer */
	/* read byte and check */
	status = ci_read_io_data(dev, buf, bytes_read);
	if (status < 0) {
		log_error("ci_read_io_data failed %d", status);
		goto exit;
	}

	/* check for read error (RE should now be 0) */
	if ((status = ci_read_cam_control(dev, CTRLIF_STATUS)) < 0)
		goto exit;
	if (status & STATUSREG_RE) {
		CA_ERR(slot_info->slot_state, "Detect RE Signal");
		update_slot_state(ca, slot, DVB_CA_SLOTSTATE_LINKINIT);
		status = -EIO;
		goto exit;
	}

	/* OK, add it to the receive buffer, or copy into external buffer if supplied */
	if (ebuf == NULL) {
		status = te_pktbuf_packet_write(&slot_info->p_rx_buf,
						buf, bytes_read);
		if (status < 0)
			goto exit;
		wakeup = true;
	}

	if (dvb_ca_debug & CA_DEBUG_TRACE) {
		log_noti("Received CA packet for slot %i size:0x%x",
			 slot, bytes_read);
	}

	/* wake up readers when a last_fragment is received */
	if (wakeup) {
		wake_up_interruptible(&ca->wait_queue);
	}
	status = bytes_read;

exit:
	return status;
}

/**
 * lxdvb_ca_write_data - This function talks to an EN50221 CAM control
 *		       interface. It writes a buffer of data to a CAM.
 *
 * @ca: CA instance.
 * @slot: Slot to write to.
 * @ebuf: The data in this buffer is treated as a complete link-level packet to
 * be written.
 * @count: Size of ebuf.
 *
 * @return Number of bytes written, or < 0 on error.
 */
static int lxdvb_ca_write_data(struct lxdvb_ca *ca, int slot, u8 *buf,
			     int bytes_write)
{
	int status;
	struct ci_device *dev = ca->dev;

	log_debug("%s", __func__);

	/* sanity check */
	if (bytes_write > ca->slot_info[slot].link_buf_size)
		return -EINVAL;

	/* it is possible we are dealing with a single buffer implementation,
	   thus if there is data available for read or if there is even a read
	   already in progress, we do nothing but awake the kernel thread to
	   process the data if necessary. */
	if ((status = ci_read_cam_control(dev, CTRLIF_STATUS)) < 0)
		goto exitnowrite;
	if (status & (STATUSREG_DA | STATUSREG_RE)) {
		if (status & STATUSREG_DA)
			lxdvb_ca_thread_wakeup(ca);

		status = -EAGAIN;
		goto exitnowrite;
	}

	/* OK, set HC bit */
	if ((status = ci_write_cam_control(dev, CTRLIF_COMMAND,
					   CMDREG_HC)) != 0)
		goto exit;

	/* check if interface is still free */
	if ((status = ci_read_cam_control(dev, CTRLIF_STATUS)) < 0)
		goto exit;
	if (!(status & STATUSREG_FR)) {
		/* it wasn't free => try again later */
		status = -EAGAIN;
		goto exit;
	}

	/* send the amount of data */
	if ((status = ci_write_cam_control(dev, CTRLIF_SIZE_HIGH,
						bytes_write >> 8)) != 0)
		goto exit;
	if ((status = ci_write_cam_control(dev, CTRLIF_SIZE_LOW,
						bytes_write & 0xff)) != 0)
		goto exit;

	/* send the buffer */
	status = ci_write_io_data(dev, buf, bytes_write);
	if (status != 0) {
		log_error("ci_write_io_data failed %d", status);
		goto exit;
	}

	/* check for write error (WE should now be 0) */
	if ((status = ci_read_cam_control(dev, CTRLIF_STATUS)) < 0)
		goto exit;
	if (status & STATUSREG_WE) {
		CA_ERR(ca->slot_info[slot].slot_state, "Detect WE Signal");
		update_slot_state(ca, slot, DVB_CA_SLOTSTATE_LINKINIT);
		status = -EIO;
		goto exit;
	}
	status = bytes_write;

	log_debug("Wrote CA packet for slot %i size:0x%x", slot, bytes_write);

exit:
	ci_write_cam_control(dev, CTRLIF_COMMAND, 0);

exitnowrite:
	return status;
}

static void shutdown_slot_hw(struct lxdvb_ca *ca)
{
	struct ci_device *dev = ca->dev;

	/* reset ca information to zero */
	ca->running_time = 0;
	ca->wakecount = 0;

	/* actual hardware shutdown */
	ci_slot_shutdown(dev);

	/* need to wake up all processes to check if they're now
	   trying to write to a defunct CAM */
	wake_up_interruptible(&ca->wait_queue);
}

/* EN50221 higher level functions */

/**
 * dvb_ca_camready_irq - A CAM has been removed => shut it down.
 *
 * @ca: CA instance.
 * @slot: Slot to shut down.
 */
static int lxdvb_ca_slot_shutdown(struct lxdvb_ca *ca, int slot)
{
	log_debug("%s", __func__);

	update_slot_state(ca, slot, DVB_CA_SLOTSTATE_NONE);
	shutdown_slot_hw(ca);

	log_debug("Slot %i shutdown", slot);

	/* success */
	return 0;
}

/**
 * check the cam status + deal with CAMCHANGEs
 */
static int check_camchange_by_intr(struct lxdvb_ca *ca, int slot)
{
	struct dvb_ca_slot *s = &ca->slot_info[slot];
	unsigned long flags;
	int changed, type;

	spin_lock_irqsave(&s->spinlock, flags);

	type = s->camchange_type;
	changed = s->camchanged;
	s->camchanged = 0;

	spin_unlock_irqrestore(&s->spinlock, flags);

	// check the cam status + deal with CAMCHANGEs
	if (changed) {
		if (s->slot_state != DVB_CA_SLOTSTATE_NONE) {
			CA_NOTI(s->slot_state, "shutdown by intr");
			lxdvb_ca_slot_shutdown(ca, slot);
		}

		/* if a CAM is NOW present, initialise it */
		if (type == DVB_CA_CAMCHANGE_INSERTED) {
			CA_NOTI(s->slot_state, "cam insertion detected");
			update_slot_state(ca, slot,
					  DVB_CA_SLOTSTATE_UNINITIALISED);
		}
	}

	return changed;
}

/**
 * dvb_ca_camready_irq - A CAMCHANGE IRQ has occurred.
 *
 * @ca: CA instance.
 * @slot: Slot concerned.
 * @change_type: One of the DVB_CA_CAMCHANGE_* values.
 */
// Inside carddetect_lock
static void camchange_irq(void *arg, int slot, bool detect)
{
	struct lxdvb_ca *ca = arg;
	unsigned long flags;

	log_noti("CAMCHANGE IRQ slot:%i change_type:%i", slot, detect);

	spin_lock_irqsave(&ca->slot_info[slot].spinlock, flags);
	ca->slot_info[slot].camchange_type = (detect) ?
		DVB_CA_CAMCHANGE_INSERTED : DVB_CA_CAMCHANGE_REMOVED;
	ca->slot_info[slot].camchanged = 1;
	spin_unlock_irqrestore(&ca->slot_info[slot].spinlock, flags);

	//atomic_inc(&ca->slot_info[slot].camchange_count);
	lxdvb_ca_thread_wakeup(ca);
}

/**
 * dvb_ca_camready_irq - followed by ci_slot_rest (not interrupt)
 *
 * @ca: CA instance.
 * @slot: Slot concerned.
 */
static void camready_callback(void *arg, int slot, bool ready)
{
	struct lxdvb_ca *ca = arg;

	log_debug("CAMREADY callback slot:%i", slot);

	if (ready)
		set_bit(CA_SLOT_CAMREADY, &ca->slot_info[slot].flags);
	else
		set_bit(CA_SLOT_CAMFAIL, &ca->slot_info[slot].flags);

	lxdvb_ca_thread_wakeup(ca);
}

/* EN50221 thread functions */

/**
 * Wake up the DVB CA thread
 *
 * @ca: CA instance.
 */
static void lxdvb_ca_thread_wakeup(struct lxdvb_ca *ca)
{

	log_debug("%s", __func__);

	ca->wakeup = 1;
	wake_up_interruptible(&ca->thread_wait_queue);
}

static int get_running_delay(struct lxdvb_ca *ca)
{
	int rc;
	enum ci_mode_speed s;

	rc = ci_get_speed_mode(ca->dev, &s);
	if (rc == 0 && s == CI_PCMCIA_SPEED_HIGH) {
		return _polling_delay; /* 5ms->2ms (tvservice high poll time) */
	} else {
		return 20; /* 20ms (tvservice default poll time) */
	}
}

/* Update the delay by the thread (slot indicated) */
static void lxdvb_ca_thread_update_slot_delay(struct lxdvb_ca *ca,
					      int slot_num)
{
	int delay;

	/* Beware of too high polling frequency, because one polling
	 * call might take several hundred milliseconds until timeout!
	 */
	if (!(ca->flags & DVB_CA_FLAG_IRQ_CAMCHANGE)) {
		switch (ca->slot_info[slot_num].slot_state) {
		case DVB_CA_SLOTSTATE_WAITFR:
			delay = 10;	/* 10 ms */
			break;
		case DVB_CA_SLOTSTATE_RUNNING:
			delay = 100;	/* 100 ms */
			if (ca->open) //Not Support DA IRQ
				delay = get_running_delay(ca);
			break;
		case DVB_CA_SLOTSTATE_NONE:
		case DVB_CA_SLOTSTATE_UNINITIALISED:
		case DVB_CA_SLOTSTATE_INVALID:
		case DVB_CA_SLOTSTATE_WAITREADY:
		case DVB_CA_SLOTSTATE_VALIDATE_CHECK_CIS:
		case DVB_CA_SLOTSTATE_VALIDATE_WRITE_COR:
		case DVB_CA_SLOTSTATE_VALIDATE_SET_RS:
		case DVB_CA_SLOTSTATE_LINKINIT:
		default:
			delay = 100;	/* 100ms */
			break;
		}

		ca->delay = delay;
		return;
	}

	switch (ca->slot_info[slot_num].slot_state) {
	default:
	case DVB_CA_SLOTSTATE_NONE:
	case DVB_CA_SLOTSTATE_INVALID:
		delay = (60 * 1000);	/* 60s */
		break;
	case DVB_CA_SLOTSTATE_VALIDATE_CHECK_CIS:
	case DVB_CA_SLOTSTATE_VALIDATE_WRITE_COR:
	case DVB_CA_SLOTSTATE_UNINITIALISED:
	case DVB_CA_SLOTSTATE_WAITREADY:
	case DVB_CA_SLOTSTATE_LINKINIT:
	case DVB_CA_SLOTSTATE_VALIDATE_SET_RS: /* from legacy sleep */
		delay = 100;	/* 100ms */
		break;
	case DVB_CA_SLOTSTATE_WAITFR:
		delay = 10;	/* 10 ms */
		break;
	case DVB_CA_SLOTSTATE_RUNNING:
		delay = (60 * 1000);	/* 60s */
		if (ca->open) //Not Support DA IRQ
			delay = get_running_delay(ca);
		break;
	}

	ca->delay = delay;
}

static void do_cam_state_machine(struct lxdvb_ca *ca,
				 struct ci_device *dev, int slot)
{
	struct dvb_ca_slot *s =&ca->slot_info[slot];
	int flags;
	int pktcount;
	void *rxbuf;
	int status;
	int rc;

	mutex_lock(&s->slot_lock);

	lxdvb_ca_check_camstatus(ca, slot);	//Check the cam status and DEAL with it

	if (dvb_ca_debug & CA_DEBUG_STATE) {
		if (s->slot_state == DVB_CA_SLOTSTATE_RUNNING ||
		    s->slot_state == DVB_CA_SLOTSTATE_NONE ||
		    s->slot_state == DVB_CA_SLOTSTATE_INVALID) {
			if (!ca->running_time ||
			    time_after(jiffies, ca->running_time + HZ)) {
				log_noti("(DEBUG:%d) %s wake count(%d)",
					 slot,
					 get_slot_state_str(s->slot_state),
					 ca->wakecount);
				ca->running_time = jiffies;
				ca->wakecount = 0;
			} else {
				ca->wakecount++;
			}
		} else {
			log_noti("(DEBUG:%d) %s",
				 slot, get_slot_state_str(s->slot_state));
		}
	}

	// CAM state machine
	switch (s->slot_state) {
	case DVB_CA_SLOTSTATE_NONE:
	case DVB_CA_SLOTSTATE_INVALID:
		// no action needed
		break;

	case DVB_CA_SLOTSTATE_UNINITIALISED:
		s->start_time = te_get_ms_tick();
		clear_bit(CA_SLOT_CAMREADY, &s->flags);
		clear_bit(CA_SLOT_CAMFAIL, &s->flags);
		ci_slot_reset(dev);
		update_slot_state(ca, slot, DVB_CA_SLOTSTATE_WAITREADY);
		s->timeout = jiffies + (INIT_TIMEOUT_SECS * HZ);
		break;

	case DVB_CA_SLOTSTATE_WAITREADY:
		if (test_bit(CA_SLOT_CAMREADY, &s->flags)) {
			clear_bit(CA_SLOT_CAMREADY, &s->flags);
			s->retry_parse = 0;
			update_slot_state(ca, slot,
					  DVB_CA_SLOTSTATE_VALIDATE_CHECK_CIS);
			s->check_interval = 0;
			ca->wakeup = 1;
		} else if (test_bit(CA_SLOT_CAMFAIL, &s->flags)) {
			CA_ERR(s->slot_state, "dvb_ca adaptor %d: "
			       "PC card did not respond :( (FAIL bit)",
			       ca->dvbdev->adapter->num);
			clear_bit(CA_SLOT_CAMFAIL, &s->flags);
			invalid_slot_state(ca, slot);
			break;
		} else if (time_after(jiffies, s->timeout)) {
			CA_ERR(s->slot_state, "dvb_ca adaptor %d: "
			       "PC card did not respond :( (timeout)",
			       ca->dvbdev->adapter->num);
			clear_bit(CA_SLOT_CAMFAIL, &s->flags);
			invalid_slot_state(ca, slot);
			break;
		}
		break;

	case DVB_CA_SLOTSTATE_VALIDATE_CHECK_CIS: // 1 2 3 steps
		if (s->retry_parse &&
		    time_before_eq(jiffies, s->check_interval))
			break;

		if (lxdvb_ca_parse_attributes(ca, slot) != 0) {
			/* Retry from legacy driver (4 times) */
			s->retry_parse++;
			if (s->retry_parse == MAX_PARSE_ATTR_ITERATION) {
				CA_ERR(s->slot_state, "dvb_ca adapter %d: "
				       "Invalid PC card inserted :(",
				       ca->dvbdev->adapter->num);
				/* Fail Case */
				invalid_slot_state(ca, slot);
			} else {
				CA_WARN(s->slot_state, "parse attribute failed,"
					"retry [%d/%d]",
					s->retry_parse,
					MAX_PARSE_ATTR_ITERATION);
				/* Retry with more interval */
				s->check_interval = jiffies +
					(s->retry_parse * 2 * HZ / 10);
			}

			break;
		}
		update_slot_state(ca, slot,
				  DVB_CA_SLOTSTATE_VALIDATE_WRITE_COR);
		break;

	case DVB_CA_SLOTSTATE_VALIDATE_WRITE_COR:
		if (lxdvb_ca_set_configoption(ca, slot) != 0) {
			CA_ERR(s->slot_state, "dvb_ca adapter %d: "
			       "Unable to initialise CAM :(",
			       ca->dvbdev->adapter->num);
			invalid_slot_state(ca, slot);
			break;
		}
		update_slot_state(ca, slot, DVB_CA_SLOTSTATE_VALIDATE_SET_RS);
		break;

	case DVB_CA_SLOTSTATE_VALIDATE_SET_RS:
		if (ci_write_cam_control(dev, CTRLIF_COMMAND, CMDREG_RS) != 0) {
			CA_ERR(s->slot_state,
			       "dvb_ca adapter %d: Unable to reset CAM IF",
			       ca->dvbdev->adapter->num);
			invalid_slot_state(ca, slot);
			break;
		}
		log_debug("DVB CAM validated successfully");

		s->timeout = jiffies + (INIT_TIMEOUT_SECS * HZ);
		update_slot_state(ca, slot, DVB_CA_SLOTSTATE_WAITFR);
		ca->wakeup = 1;
		break;

	case DVB_CA_SLOTSTATE_WAITFR:
		if (time_after(jiffies, s->timeout)) {
			CA_ERR(s->slot_state, "dvb_ca adapter %d: "
			       "DVB CAM did not respond :(",
			       ca->dvbdev->adapter->num);
			invalid_slot_state(ca, slot);
			break;
		}

		flags = ci_read_cam_control(dev, CTRLIF_STATUS);
		log_tuple("flags: 0x%02x", flags);
		if (flags & STATUSREG_FR) {
			update_slot_state(ca, slot, DVB_CA_SLOTSTATE_LINKINIT);
			ca->wakeup = 1;
		}
		break;

	case DVB_CA_SLOTSTATE_LINKINIT:
		if (ci_write_cam_control(dev, CTRLIF_COMMAND, 0) != 0) {
			CA_ERR(s->slot_state,
			       "dvb_ca adapter %d: Unable to unreset CAM IF",
			       ca->dvbdev->adapter->num);
			invalid_slot_state(ca, slot);
			break;
		}
		if (lxdvb_ca_link_init(ca, slot) != 0) {

			CA_ERR(s->slot_state, "dvb_ca adapter %d: "
			       "DVB CAM link initialisation failed :(",
			       ca->dvbdev->adapter->num);
			invalid_slot_state(ca, slot);
			break;
		}

		if (s->rx_buf == NULL) {
			rxbuf = vmalloc(RX_BUFFER_SIZE);
			if (!rxbuf) {
				CA_ERR(s->slot_state, "dvb_ca adapter %d: "
				       "Unable to allocate CAM rx buffer :(",
				       ca->dvbdev->adapter->num);
				invalid_slot_state(ca, slot);
				break;
			}
			s->rx_buf = rxbuf;
			rc = te_pktbuf_init(&s->p_rx_buf,
					    rxbuf, RX_BUFFER_SIZE, 32,
					    TE_BUF_FLAG_NO_EVENT);
			if (rc) {
				CA_ERR(s->slot_state, "dvb_ca adapter %d: "
				       "unable to init pktbuffer :(",
				       ca->dvbdev->adapter->num);
				vfree(s->rx_buf);
				s->rx_buf = NULL;
				invalid_slot_state(ca, slot);
				break;
			}
		}

		//slot_ts_enable(ca->pub, slot);
		update_slot_state(ca, slot, DVB_CA_SLOTSTATE_RUNNING);
		ca->running_time = 0;	//prevent verbose message
		ca->wakecount = 0;
		CA_NOTI(s->slot_state, "dvb_ca adapter %d: "
			"DVB CAM detected and initialised successfully "
			"(%lld ms)",
			ca->dvbdev->adapter->num,
			te_get_ms_tick() - s->start_time);
		break;

	case DVB_CA_SLOTSTATE_RUNNING:
		if (!ca->open)
			break;

		// poll slots for data
		pktcount = 0;
		while ((status = lxdvb_ca_read_data(ca, slot, NULL, 0)) > 0) {
			if (!ca->open)
				break;

			/* if a CAMCHANGE occurred at some point, do not do any more processing of this slot */
			if (lxdvb_ca_check_camstatus(ca, slot)) {
				// we dont want to sleep on the next iteration so we can handle the cam change
				ca->wakeup = 1;
				break;
			}

			/* check if we've hit our limit this time */
			if (++pktcount >= MAX_RX_PACKETS_PER_ITERATION) {
				// dont sleep; there is likely to be more data to read
				ca->wakeup = 1;
				break;
			}
		}

		if (dvb_ca_debug & CA_DEBUG_TRACE)
			log_noti("(DEBUG)Read %d packets", pktcount);
		break;
	}

	mutex_unlock(&s->slot_lock);
}

/**
 * Kernel thread which monitors CA slots for CAM changes, and performs data transfers.
 */
static int lxdvb_ca_thread(void *data)
{
	struct lxdvb_ca *ca = data;
	int slot;
	bool frozen;

	CA_NOTI(ca->slot_info[0].slot_state, "%s started", __func__);

	for (slot = 0; slot < ca->slot_count; slot++) {
		mutex_lock(&ca->slot_info[slot].slot_lock);

		/* choose the correct initial delay */
		lxdvb_ca_thread_update_slot_delay(ca, slot);

		mutex_unlock(&ca->slot_info[slot].slot_lock);
	}

	set_freezable();

	/* main loop */
	while (1) {
		/* sleep for a bit */
		wait_event_interruptible_hrtimeout(ca->thread_wait_queue,
						   (ca->wakeup ||
						   kthread_should_stop()),
						   ms_to_ktime(ca->delay));
		if (kthread_freezable_should_stop(&frozen))
			break;

		ca->wakeup = 0;

		/* go through all the slots processing them */
		for (slot = 0; slot < ca->slot_count; slot++) {
			do_cam_state_machine(ca, ca->dev, slot);
		}
	}

	CA_NOTI(ca->slot_info[0].slot_state, "%s exited", __func__);

	return 0;
}

static int get_te_input_src(struct ca_ext_source *s, enum lx_te_input_src *src)
{
	switch (s->input_src_type) {
	case CA_EXT_SRC_TYPE_IN_DEMOD:
		if (s->input_port_num > 0)
			return -EINVAL;
		*src = LX_TE_INPUT_SRC_IN_DEMOD0;
		break;
	case CA_EXT_SRC_TYPE_EXT_DEMOD:
		if (s->input_port_num > 1)
			return -EINVAL;
		*src = LX_TE_INPUT_SRC_EXT_INPUT0 + s->input_port_num;
		break;
	case CA_EXT_SRC_TYPE_CIP:
		if (s->input_port_num > 0)
			return -EINVAL;
		*src = LX_TE_INPUT_SRC_TE;
		break;

	default:
		return -EINVAL;
	}

	return 0;
}

static int set_input_source(struct ci_device *dev, struct ca_ext_source *s)
{
	enum lx_te_input_src src;

	if (get_te_input_src(s, &src) < 0) {
		log_error("invalid setting(type:%d num:%u)", s->input_src_type,
			  s->input_port_num);
		return -EINVAL;
	}

	return ci_set_input(dev, src);
}

static int set_error_mode(struct lxdvb_ca *ca, struct ci_device *dev,
			  enum ca_ext_error_mode e)
{
	int rc;
	enum ci_mode_error err;

	switch (e) {
	case CA_EXT_CI_ERROR_CHECK_MODE_FULL:
		err = CI_ERROR_CHECK_FULL;
		break;
	case CA_EXT_CI_ERROR_CHECK_MODE_SIMPLE:
		err = CI_ERROR_CHECK_SIMPLE;
		break;
	default:
		log_error("invalid setting %d", e);
		return -EINVAL;
	}

	rc = ci_set_error_mode(dev, err);
	if (rc == 0) {
		if (err == CI_ERROR_CHECK_FULL)
			ca->ignore_error = 1;
		else
			ca->ignore_error = 0;
	}

	return rc;
}

static int set_speed_mode(struct lxdvb_ca *ca, struct ci_device *dev,
			  enum ca_ext_pcmcia_speed s)
{
	int rc;
	int slot;
	enum ci_mode_speed speed;

	switch (s) {
	case CA_EXT_PMCICA_SPEED_LOW:
		speed = CI_PCMCIA_SPEED_LOW;
		break;
	case CA_EXT_PMCICA_SPEED_HIGH:
		speed = CI_PCMCIA_SPEED_HIGH;
		break;
	default:
		log_error("invalid setting %d", s);
		return -EINVAL;
	}

	rc = ci_set_speed_mode(dev, speed);
	if (rc == 0) {
		for (slot = 0; slot < ca->slot_count; slot++) {
			mutex_lock(&ca->slot_info[slot].slot_lock);

			/* update slot delay as requrested */
			lxdvb_ca_thread_update_slot_delay(ca, slot);

			mutex_unlock(&ca->slot_info[slot].slot_lock);
		}
	}

	return rc;
}

static int set_rs_bit(struct lxdvb_ca *ca, struct ci_device *dev)
{
	int rc = 0;
	int slot = 0;
	int state;
	struct te_pktbuf *pktbuf;

	mutex_lock(&ca->slot_info[slot].slot_lock);
	// protect from not expected user call
	state = ca->slot_info[slot].slot_state;
	if (state != DVB_CA_SLOTSTATE_RUNNING) {
		CA_ERR(state, "fail, not ready state[%s]",
		       get_slot_state_str(state));
		rc = -EIO;
		goto exit;
	}

	if (ci_write_cam_control(dev, CTRLIF_COMMAND, CMDREG_RS) != 0) {
		CA_ERR(state, "dvb_ca adapter %d: Unable to reset CAM IF",
		       ca->dvbdev->adapter->num);
		rc = -EPERM;
	}

	if (ca->slot_info[slot].rx_buf) {
		pktbuf = &ca->slot_info[slot].p_rx_buf;
		te_pktbuf_flush(pktbuf);
	}

exit:
	mutex_unlock(&ca->slot_info[slot].slot_lock);

	return rc;
}

static int ci_set_control(struct lxdvb_ca *ca,
			  struct ca_ext_control *control)
{
	int ret = 0;

	if (dvb_ca_debug & CA_DEBUG_TRACE) {
		struct ci_lge_control_param *c;
		c = get_ci_lge_control_param(control->id);
		if (c)
			log_noti("ioctl - set %s", c->name);
	}

	switch (control->id) {
	case CA_EXT_CID_INPUTSOURCE:
		ret = set_input_source(ca->dev, (void __force *)control->ptr);
		break;
	case CA_EXT_CID_ERROR_MODE:
		ret = set_error_mode(ca, ca->dev, control->value64);
		break;
	case CA_EXT_CID_PCMCIA_SPEED:
		ret = set_speed_mode(ca, ca->dev, control->value64);
		break;
	case CA_EXT_CID_SET_RS_BIT:
		ret = set_rs_bit(ca, ca->dev);
		break;
	case CA_EXT_CID_DATA_RATE:
		//ret = dvb_ca_set_option(pub, CI_OPTION_RATE_MODE,
		//			(int)control->value64);
		//break;
	case CA_EXT_CID_PLUS_CAPA:
	case CA_EXT_CID_PLUS_VERSION:
	case CA_EXT_CID_PLUS_IIR_STATUS:
	default:
		log_error("not supported id[%d]", control->id);
		ret = -EINVAL;
		break;
	}

	return ret;
}

static int get_is_ciplus(struct lxdvb_ca *ca, int slot_num, int *val)
{
	int state, ret;

	mutex_lock(&ca->slot_info[slot_num].slot_lock);

	state = ca->slot_info[slot_num].slot_state;
	if (state == DVB_CA_SLOTSTATE_LINKINIT
	    || state == DVB_CA_SLOTSTATE_RUNNING) {
		*val = ca->slot_info[slot_num].is_ciplus;
		ret = 0;
	} else {
		*val = 0;
		ret = -EAGAIN;
	}

	mutex_unlock(&ca->slot_info[slot_num].slot_lock);

	return ret;
}

static int get_ciplus_ver(struct lxdvb_ca *ca, int slot_num, int *val)
{
	int state, ret;

	mutex_lock(&ca->slot_info[slot_num].slot_lock);

	state = ca->slot_info[slot_num].slot_state;
	if (state == DVB_CA_SLOTSTATE_LINKINIT ||
	    state == DVB_CA_SLOTSTATE_RUNNING) {
		*val = ca->slot_info[slot_num].version;
		ret = 0;
	} else {
		*val = 0;
		ret = -EAGAIN;
	}

	mutex_unlock(&ca->slot_info[slot_num].slot_lock);

	return ret;
}

static int ci_get_iir(struct lxdvb_ca *ca, int slot)
{
	int rc = -EFAULT;
	int state;
	struct ci_device *dev = ca->dev;

	mutex_lock(&ca->slot_info[slot].slot_lock);

	state = ca->slot_info[slot].slot_state;
	if (state == DVB_CA_SLOTSTATE_RUNNING) {
		rc = ci_read_iir_register(dev);
		if (rc)
			log_error("(DEBUG)iir bit detected");
	} else {
		CA_ERR(state, "CAM is not running state: %s",
		       get_slot_state_str(state));
	}

	mutex_unlock(&ca->slot_info[slot].slot_lock);

	return rc;
}

static int get_ci_negobuf_size(struct lxdvb_ca *ca, int slot, int *val)
{
	int rc = -EAGAIN;
	int state;

	mutex_lock(&ca->slot_info[slot].slot_lock);

	state = ca->slot_info[slot].slot_state;
	if (state == DVB_CA_SLOTSTATE_RUNNING) {
		*val = ca->slot_info[slot].link_buf_size;
		rc = 0;
	} else {
		CA_ERR(state, "CAM is not running state: %s",
		       get_slot_state_str(state));
		*val = 0;
	}

	mutex_unlock(&ca->slot_info[slot].slot_lock);

	return rc;
}

static void get_ca_ext_source(struct ca_ext_source *s, enum lx_te_input_src src)
{
	s->input_port_num = 0; //default

	switch (src) {
	case LX_TE_INPUT_SRC_IN_DEMOD0:
		s->input_src_type = CA_EXT_SRC_TYPE_IN_DEMOD;
		break;
	case LX_TE_INPUT_SRC_EXT_INPUT0:
		s->input_src_type = CA_EXT_SRC_TYPE_EXT_DEMOD;
		break;
	case LX_TE_INPUT_SRC_EXT_INPUT1:
		s->input_src_type = CA_EXT_SRC_TYPE_EXT_DEMOD;
		s->input_port_num = 1;
		break;
	case LX_TE_INPUT_SRC_TE:
		s->input_src_type = CA_EXT_SRC_TYPE_CIP;
		break;
	default:
		s->input_src_type = CA_EXT_SRC_TYPE_NULL;
	}
}

static int get_input_source(struct ci_device *dev, struct ca_ext_source *s)
{
	int rc;
	enum lx_te_input_src src;

	rc = ci_get_input(dev, &src);
	if (rc == 0)
		get_ca_ext_source(s, src);

	return rc;
}

static int get_error_mode(struct ci_device *dev, int *val)
{
	int rc;
	enum ci_mode_error err;

	rc = ci_get_error_mode(dev, &err);
	if (rc == 0) {
		if (err == CI_ERROR_CHECK_FULL)
			*val = CA_EXT_CI_ERROR_CHECK_MODE_FULL;
		else
			*val = CA_EXT_CI_ERROR_CHECK_MODE_SIMPLE;
	}

	return rc;
}

static int get_rate_mode(struct ci_device *dev, int *val)
{
	int rc;
	enum ci_mode_datarate rate;

	rc = ci_get_rate_mode(dev, &rate);
	if (rc == 0) {
		if (rate == CI_DATARATE_72)
			*val = CA_EXT_CIPLUS_DATARATE_72;
		else
			*val = CA_EXT_CIPLUS_DATARATE_96;
	}

	return rc;
}

static int get_speed_mode(struct ci_device *dev, int *val)
{
	int rc;
	enum ci_mode_speed speed;

	rc = ci_get_speed_mode(dev, &speed);
	if (rc == 0) {
		if (speed == CI_PCMCIA_SPEED_LOW)
			*val = CA_EXT_PMCICA_SPEED_LOW;
		else
			*val = CA_EXT_PMCICA_SPEED_HIGH;
	}

	return rc;
}

static int ci_get_control(struct lxdvb_ca *ca,
			  struct ca_ext_control *control)
{
	int ret = 0, val = 0;

	if (dvb_ca_debug & CA_DEBUG_TRACE) {
		struct ci_lge_control_param *c;
		c = get_ci_lge_control_param(control->id);
		if (c)
			log_noti("ioctl - get %s", c->name);
	}

	switch (control->id) {
	case CA_EXT_CID_INPUTSOURCE:
		ret = get_input_source(ca->dev, (void __force *)control->ptr);
		break;
	case CA_EXT_CID_ERROR_MODE:
		ret = get_error_mode(ca->dev, &val);
		control->value64 = val;
		break;
	case CA_EXT_CID_PLUS_CAPA:
		ret = get_is_ciplus(ca, 0, &val);
		control->value64 = val;
		break;
	case CA_EXT_CID_DATA_RATE:
		ret = get_rate_mode(ca->dev, &val);
		control->value64 = val;
		break;
	case CA_EXT_CID_PCMCIA_SPEED:
		ret = get_speed_mode(ca->dev, &val);
		control->value64 = val;
		break;
	case CA_EXT_CID_PLUS_VERSION:
		ret = get_ciplus_ver(ca, 0, &val);
		control->value64 = val;
		break;
	case CA_EXT_CID_PLUS_IIR_STATUS:
		ret = ci_get_iir(ca, 0);
		control->value64 = (ret >= 0) ? ret : 0;
		break;
	case CA_EXT_CID_GET_NEGO_BUFF:
		ret = get_ci_negobuf_size(ca, 0, &val);
		control->value64 = val;
		break;
	default:
		log_error("not supported id[%d]", control->id);
		ret = -EINVAL;
		break;
	}

	return ret;
}

static struct ci_lge_control_param *get_ci_lge_control_param(u32 id)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(ci_lge_control_params); i++) {
		if (ci_lge_control_params[i].id == id)
			return &ci_lge_control_params[i];
	}

	return NULL;
}

static int ci_get_user_ptr(void *priv, unsigned int cmd, void *arg,
			   struct te_ioctl_ptr_param *param)
{
	struct ca_ext_control *p;
	int dir;
	struct ci_lge_control_param *c;

	switch (cmd) {
	case CA_EXT_S_CTL:
	case CA_EXT_G_CTL:{
		p = arg;
		c = get_ci_lge_control_param(p->id);
		dir = (cmd == CA_EXT_S_CTL) ? _IOC_WRITE : _IOC_READ;

		CHECK_ERROR(!c, return -EINVAL,
			    "invalid ca_ext_control id(%u)", p->id);
		CHECK_ERROR(c->size != p->size, return -EINVAL,
			    "invalid size(%u) of ca_ext_control(%s) "
			    "- expected(%u)",
			    p->size, c->name, c->size);
		CHECK_ERROR(!(c->dir & dir), return -EINVAL,
			    "invalid command of ca_ext_control(%s)",
			    c->name);

		if (p->size > 0) {
			param->user_ptr = te_ioctl_get_user_ptr(p->ptr);
			param->kernel_ptr = (void **)&p->ptr;
			param->size = p->size;
			param->dir = dir;
		}
		break;
	}
	default:
		break;
	}

	return 0;
}

static int ca_reset(struct lxdvb_ca *ca)
{
	int state, rc = 0;
	int slot = 0;

	mutex_lock(&ca->slot_info[slot].slot_lock);
	state = ca->slot_info[slot].slot_state;
	if (state == DVB_CA_SLOTSTATE_UNINITIALISED ||
	    state == DVB_CA_SLOTSTATE_WAITREADY) {
		CA_WARN(state, "Reset is ongoing(%s) - ignore request",
			get_slot_state_str(state));
		rc = -EBUSY;
	} else if (state != DVB_CA_SLOTSTATE_NONE) {
		shutdown_slot_hw(ca);
		update_slot_state(ca, slot, DVB_CA_SLOTSTATE_UNINITIALISED);
	}
	mutex_unlock(&ca->slot_info[slot].slot_lock);

	return rc;
}

static int test_ion_tp_checker(struct lxdvb_ca *ca,
			       struct te_dvb_ca_test_pkt_cnt *param)
{
	enum lx_te_input_src src;
	int rc;

	if (!param->cnt) {
		log_error("invalid param cnt:%u", param->cnt);
		return -EINVAL;
	}

	log_warning("test ion tp checker cnt:%u", param->cnt);

	ci_get_input(ca->dev, &src);
	if (src != LX_TE_INPUT_SRC_TE) {
		log_error("CI_IN:%s; disconnect it before conducting test",
			  te_input_source_to_str(src));
		return -EPERM;
	}

	rc = ci_hw_ion_reset(ca->dev);
	if (rc) {
		log_error("error %d in ci_hw_ion_reset", rc);
		return rc;
	}

	ca_reset(ca);

	rc = ci_hw_ion_init_tp_checker(ca->dev, param->cnt);
	if (rc) {
		log_error("error %d in ci_hw_ion_init_tp_checker", rc);
		return rc;
	}

	rc = ci_hw_ion_start_tp_checker(ca->dev, param->cnt);
	if (!rc) {
		log_noti("tp checker[%u] OK", param->cnt);
	} else {
		log_error("tp checker[%u] failed %d", param->cnt, rc);
		return rc;
	}

	return 0;
}

static int do_kapi_ioctl(struct lxdvb_ca *ca, unsigned int cmd, void *parg)
{
	int ret;

	switch (cmd) {
	case TE_DVB_CA_TEST_PKT_CNT:
		ret = test_ion_tp_checker(ca, parg);
		break;
	default:
		log_error("invalid command[0x%08x]. magic=0x%02X, num=%d",
			   cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));
		ret = -ENOTTY;
		break;
	}

	return ret;
}

static int do_ext_ioctl(struct lxdvb_ca *ca, unsigned int cmd, void *arg)
{
	int ret;

	if (_IOC_TYPE(cmd) == TE_DVB_CA_MAGIC)
		return do_kapi_ioctl(ca, cmd, arg);

	switch (cmd) {
	case CA_EXT_S_CTL:
		ret = ci_set_control(ca, arg);
		break;
	case CA_EXT_G_CTL:
		ret = ci_get_control(ca, arg);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}

/* EN50221 IO interface functions */
static int do_ioc_ca_reset(struct lxdvb_ca *ca, int slot)
{
	return ca_reset(ca);
}

static void get_ioc_ca_slot_info(struct lxdvb_ca *ca, struct ca_slot_info *info)
{
	bool cam_present_now;
	int state;

	info->num = 0;
	info->type = CA_CI_PHYS;
	info->flags = 0;

	state = ca->slot_info[info->num].slot_state;
	if (!(ca->flags & DVB_CA_FLAG_IRQ_CAMCHANGE)) {
		/* Poll mode needs to check card detect at this time */
		cam_present_now = ci_check_card_detect(ca->dev);

		if (cam_present_now) {
			info->flags = CA_CI_MODULE_PRESENT;

			if (state == DVB_CA_SLOTSTATE_NONE) {
				CA_WARN(state, "card detect on (NONE) state");
			}
		}
	} else {
		/* IRQ (legacy) Mode */
		if ((state != DVB_CA_SLOTSTATE_NONE) &&
		    (state != DVB_CA_SLOTSTATE_INVALID)) {
			info->flags = CA_CI_MODULE_PRESENT;
		}
	}

	if (state == DVB_CA_SLOTSTATE_RUNNING) {
		info->flags |= CA_CI_MODULE_READY;
	} else if (state == DVB_CA_SLOTSTATE_INVALID) {
		info->flags |= CA_EXT_CI_MODULE_INVALID;
	}
}


/**
 * Real ioctl implementation.
 * NOTE: CA_SEND_MSG/CA_GET_MSG ioctls have userspace buffers passed to them.
 *
 * @inode: Inode concerned.
 * @file: File concerned.
 * @cmd: IOCTL command.
 * @arg: Associated argument.
 *
 * @return 0 on success, <0 on error.
 */
static int lxdvb_ca_io_do_ioctl(void *priv, unsigned int cmd, void *parg)
{
	struct lxdvb_ca *ca = priv;
	int ret = 0;
	int slot;

	if (mutex_lock_interruptible(&ca->ioctl_mutex))
		return -ERESTARTSYS;

	switch (cmd) {
	case CA_RESET:
		CA_NOTI(ca->slot_info[0].slot_state, "ioctl - CA_RESET");

		for (slot = 0; slot < ca->slot_count; slot++)
			ret = do_ioc_ca_reset(ca, slot);

		ca->next_read_slot = 0;
		lxdvb_ca_thread_wakeup(ca);
		break;

	case CA_GET_CAP:{
		struct ca_caps *caps = parg;

		if (dvb_ca_debug & CA_DEBUG_TRACE)
			log_noti("ioctl - CA_GET_CAP");

		caps->slot_num = ca->slot_count;
		caps->slot_type = CA_CI_PHYS;
		caps->descr_num = 0;
		caps->descr_type = 0;
		break;
	}

	case CA_GET_SLOT_INFO:{
		struct ca_slot_info *info = parg;

		get_ioc_ca_slot_info(ca, info);

		if (dvb_ca_debug & CA_DEBUG_TRACE)
			log_noti("ioctl - CA_GET_SLOT_INFO - %u", info->flags);
		break;
	}

	default:
		ret = do_ext_ioctl(ca, cmd, parg);
		break;
	}

//out_unlock:
	mutex_unlock(&ca->ioctl_mutex);

	if (ret < 0) {
		log_error("command[0x%08x]. magic=0x%02X, num=%d - error %d",
			   cmd, _IOC_TYPE(cmd), _IOC_NR(cmd), ret);
	}
	return ret;
}

/**
 * Wrapper for ioctl implementation.
 *
 * @inode: Inode concerned.
 * @file: File concerned.
 * @cmd: IOCTL command.
 * @arg: Associated argument.
 *
 * @return 0 on success, <0 on error.
 */
static long lxdvb_ca_io_ioctl(struct file *file,
			    unsigned int cmd, unsigned long arg)
{
	struct lxdvb_ca *ca = file->private_data;

	return te_ioctl_usercopy(cmd, arg, lxdvb_ca_io_do_ioctl,
				 ci_get_user_ptr, ca);
}

// TEST CODE
static void debug_io_rw_str(const char __user *buf, size_t count, bool is_read)
{
	u8 *b;
	u8 byte;
	int i, size = count * 6 + 1;

	b = vmalloc(size);
	CHECK_ERROR(!b, return, "malloc error");

	for (i = 0; i < count; i++) {
		if (copy_from_user(&byte, buf + i, 1)) {
			log_error("copy_from_user failed");
			vfree(b);
			return;
		}
		snprintf(b + (i * 6), 7, "[0x%02x]", byte);
	}

	b[size - 1] = '\0';
	log_noti("%s str:%s", (is_read == 1) ? "read" : "write", b);

	vfree(b);
}

/**
 * Implementation of write() syscall.
 *
 * @file: File structure.
 * @buf: Source buffer.
 * @count: Size of source buffer.
 * @ppos: Position in file (ignored).
 *
 * @return Number of bytes read, or <0 on error.
 */
static ssize_t lxdvb_ca_io_write(struct file *file,
			       const char __user *buf, size_t count,
			       loff_t *ppos)
{
	struct lxdvb_ca *ca = file->private_data;
	u8 slot;
	int status;
	u8 *writebuf;
	unsigned long timeout;
	bool written;
	u64 a = 0, b = 0;
	int *slot_state;

	if (dvb_ca_debug & CA_DEBUG_RW)
		debug_io_rw_str(buf, count, 0);
	if (dvb_ca_debug & CA_DEBUG_TRACE)
		log_noti("%s", __func__);
	if (dvb_ca_debug & CA_DEBUG_WRITE)
		a = te_get_us_tick();

	slot = 0; // FIXED
	if (count < 2)
		return -EINVAL;
	if (count > ca->slot_info[slot].link_buf_size) {
		CA_ERR(ca->slot_info[slot].slot_state,
		       "exceeds link buf size(%u) < %zu",
		       ca->slot_info[slot].link_buf_size, count);
		return -EINVAL;
	}

	slot_state = &ca->slot_info[slot].slot_state;

	///* check if the slot is actually running */
	//if (*slot_state != DVB_CA_SLOTSTATE_RUNNING)
	//      return -EINVAL;
	ca_dump_write(&ca->dump, buf, count, false);

	/* alloc temporal link buffer to write */
	writebuf = ca->slot_info[slot].link_write_buf;
	CHECK_ERROR(!writebuf, return -ENOMEM, "write buffer not allocated");

	/* store in the buffer */
	status = copy_from_user(writebuf, buf, count);
	if (status) {
		status = -EFAULT;
		goto exit;
	}

	/* legacy driver 5 ms * 500 = 2.5 sec timeout */
	timeout = jiffies + (HZ * 25 / 10);
	written = false;
	while (!time_after(jiffies, timeout)) {
		mutex_lock(&ca->slot_info[slot].slot_lock);
		/* check the CAM hasn't been removed/reset in the meantime */
		if (*slot_state != DVB_CA_SLOTSTATE_RUNNING) {
			status = -EIO;
			mutex_unlock(&ca->slot_info[slot].slot_lock);
			goto exit;
		}

		status = lxdvb_ca_write_data(ca, slot, writebuf, count);
		mutex_unlock(&ca->slot_info[slot].slot_lock);
		if (status == count) {
			written = true;
			break;
		}

		if (status != -EAGAIN)
			goto exit;

		/* legacy wait 5 ms but its meaningless, only need check DA, FR
		 * bit in time */
		usleep_range(100, 100);	/* 100 us */
	}

	if (!written) {
		status = -EIO;
		goto exit;
	}
	status = count;
exit:
	if (dvb_ca_debug & CA_DEBUG_WRITE) {
		b = te_get_us_tick();
		log_noti("Write elapsed %lld us / %d", (b - a), status);
	}
	return status;
}

/**
 * Condition for waking up in lxdvb_ca_io_read_condition
 */
static int lxdvb_ca_io_read_condition(struct lxdvb_ca *ca, int *result,
				      int *_slot)
{
	int slot;
	int slot_count = 0;
	int found = 0;
	struct te_pktbuf *pktbuf;

	slot = ca->next_read_slot;
	while ((slot_count < ca->slot_count) && (!found)) {
		mutex_lock(&ca->slot_info[slot].slot_lock);
		pktbuf = &ca->slot_info[slot].p_rx_buf;
		if (ca->slot_info[slot].slot_state != DVB_CA_SLOTSTATE_RUNNING)
			goto nextslot;

		if (ca->slot_info[slot].rx_buf == NULL) {
			mutex_unlock(&ca->slot_info[slot].slot_lock);
			return 0;
		}

		if (te_pktbuf_avail_packet(pktbuf) > 0) {
			*_slot = slot;
			found = 1;
		}
nextslot:
		mutex_unlock(&ca->slot_info[slot].slot_lock);
		slot = (slot + 1) % ca->slot_count;
		slot_count++;
	}
	if (dvb_ca_debug & CA_DEBUG_TRACE)
		log_noti("(DEBUG) found:%d", found);

	ca->next_read_slot = slot;
	return found;
}

/**
 * Implementation of read() syscall.
 *
 * @file: File structure.
 * @buf: Destination buffer.
 * @count: Size of destination buffer.
 * @ppos: Position in file (ignored).
 *
 * @return Number of bytes read, or <0 on error.
 */
static ssize_t lxdvb_ca_io_read(struct file *file, char __user *buf,
			      size_t count, loff_t *ppos)
{
	struct lxdvb_ca *ca = file->private_data;
	int status;
	int result = 0;
	int slot;
	struct te_pktbuf *pktbuf;

	if (dvb_ca_debug & CA_DEBUG_TRACE)
		log_noti("%s len = %zu", __func__, count);

	if (count < 2)
		return -EINVAL;

	/* wait for some data */
	if ((status = lxdvb_ca_io_read_condition(ca, &result, &slot)) == 0) {

		/* if we're in nonblocking mode, exit immediately */
		if (file->f_flags & O_NONBLOCK)
			return -EWOULDBLOCK;

		/* wait for some data */
		status = wait_event_interruptible(ca->wait_queue,
						  lxdvb_ca_io_read_condition
						  (ca, &result, &slot));
	}
	if ((status < 0) || (result < 0)) {
		if (result)
			return result;
		return status;
	}

	pktbuf = &ca->slot_info[slot].p_rx_buf;
	status = te_pktbuf_packet_read_user(pktbuf, buf, count);
	if (status <= 0) {
		CA_ERR(ca->slot_info[slot].slot_state,
		       "dvb_ca adapter %d: error when read pktbuffer - %d",
		       ca->dvbdev->adapter->num, status);
	} else {
		if (dvb_ca_debug & CA_DEBUG_TRACE)
			log_noti("done with len = %d", status);
		if (dvb_ca_debug & CA_DEBUG_RW)
			debug_io_rw_str(buf, status, 1);

		ca_dump_write(&ca->dump, buf, status, true);
	}

	return status;
}

/**
 * Implementation of file open syscall.
 *
 * @inode: Inode concerned.
 * @file: File concerned.
 *
 * @return 0 on success, <0 on failure.
 */
static int lxdvb_ca_io_open(struct inode *inode, struct file *file)
{
	struct dvb_device *dvbdev = file->private_data;
	struct lxdvb_ca *ca = dvbdev->priv;
	struct dvb_ca_slot *s;
	int i, ret;

	if (dvb_ca_debug & CA_DEBUG_TRACE)
		log_noti("%s", __func__);

	mutex_lock(&ca->ioctl_mutex);

	if (!ca->open) {
		ci_hw_init(ca->dev);

		/* now initialise each slot */
		for (i = 0; i < ca->slot_count; i++) {
			s = &ca->slot_info[i];
			s->slot_state = DVB_CA_SLOTSTATE_NONE;

			s->rx_buf = NULL;
			s->link_read_buf = NULL;
			s->link_write_buf = NULL;

			s->camchanged = 0;
			s->camchange_type = DVB_CA_CAMCHANGE_REMOVED;
		}

		/* Initial card detection */
		ret = ci_slot_initialize(ca->dev,
					 ca->flags & DVB_CA_FLAG_IRQ_CAMCHANGE);
		if (ret) {
			CA_ERR(s->slot_state, "failed to initialize slot (%d)",
			       ret);
			mutex_unlock(&ca->ioctl_mutex);
			return -ENODEV;
		}

		/* create a kthread for monitoring this CA device */
		ca->thread = kthread_run(lxdvb_ca_thread, ca, "kdvb-ca-%i:%i",
					 ca->dvbdev->adapter->num,
					 ca->dvbdev->id);
		if (IS_ERR(ca->thread)) {
			ret = PTR_ERR(ca->thread);
			CA_ERR(s->slot_state,
			       "failed to start kernel_thread (%d)", ret);
			mutex_unlock(&ca->ioctl_mutex);
			return -ENODEV;
		}

		ca->open = 1;
		lxdvb_ca_thread_wakeup(ca);
	} else {
		ca->open++;
	}

	/* It is safe since actually ca is not te device */
	te_clockgate_acquire_clock(ca->tdev, TE_DEVICE_TYPE_CI);

	file->private_data = ca;

	mutex_unlock(&ca->ioctl_mutex);

	return 0;
}

/**
 * Implementation of file close syscall.
 *
 * @inode: Inode concerned.
 * @file: File concerned.
 *
 * @return 0 on success, <0 on failure.
 */
static int lxdvb_ca_io_release(struct inode *inode, struct file *file)
{
	struct lxdvb_ca *ca = file->private_data;
	int i;

	if (dvb_ca_debug & CA_DEBUG_TRACE)
		log_noti("%s", __func__);

	mutex_lock(&ca->ioctl_mutex);

	if (ca->open)
		ca->open--;

	/* mark the CA device as closed */
	if (!ca->open) {
		/* shutdown the thread if there was one */
		kthread_stop(ca->thread);
		ca->thread = NULL;

		/* turn off the interrupt */
		ci_slot_finalize(ca->dev);

		for (i = 0; i < ca->slot_count; i++) {
			mutex_lock(&ca->slot_info[i].slot_lock);

			CA_NOTI(ca->slot_info[i].slot_state,
				"shutdown by close");
			lxdvb_ca_slot_shutdown(ca, i);
			if (ca->slot_info[i].rx_buf) {
				te_pktbuf_release(&ca->slot_info[i].p_rx_buf);
				vfree(ca->slot_info[i].rx_buf);
			}
			if (ca->slot_info[i].link_read_buf)
				vfree(ca->slot_info[i].link_read_buf);
			if (ca->slot_info[i].link_write_buf)
				vfree(ca->slot_info[i].link_write_buf);

			ca->slot_info[i].rx_buf = NULL;
			ca->slot_info[i].link_read_buf = NULL;
			ca->slot_info[i].link_write_buf = NULL;
			mutex_unlock(&ca->slot_info[i].slot_lock);
		}
	}

	te_clockgate_release_clock(ca->tdev, TE_DEVICE_TYPE_CI);
	mutex_unlock(&ca->ioctl_mutex);

	return 0;
}

/**
 * Implementation of poll() syscall.
 *
 * @file: File concerned.
 * @wait: poll wait table.
 *
 * @return Standard poll mask.
 */
static unsigned int lxdvb_ca_io_poll(struct file *file, poll_table * wait)
{
	struct lxdvb_ca *ca = file->private_data;
	unsigned int mask = 0;
	int slot;
	int result = 0;

	/* wait for something to happen */
	poll_wait(file, &ca->wait_queue, wait);

	if (lxdvb_ca_io_read_condition(ca, &result, &slot) == 1)
		mask |= POLLIN;

	if (dvb_ca_debug & CA_DEBUG_TRACE)
		log_noti("%s: %d", __func__, mask);

	return mask;
}

static const struct file_operations dvb_ca_fops = {
	.owner = THIS_MODULE,
	.read = lxdvb_ca_io_read,
	.write = lxdvb_ca_io_write,
	.unlocked_ioctl = lxdvb_ca_io_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = lxdvb_ca_io_ioctl,
#endif
	.open = lxdvb_ca_io_open,
	.release = lxdvb_ca_io_release,
	.poll = lxdvb_ca_io_poll,
	.llseek = noop_llseek,
};

static const struct dvb_device dvbdev_ca = {
	.priv = NULL,
	.users = 1,
	.readers = 1,
	.writers = 1,
#if defined(CONFIG_MEDIA_CONTROLLER_DVB)
	.name = "dvb-ca-en50221",
#endif
	.fops = &dvb_ca_fops,
};

/* Proc debug functions */
enum {
	DEBUG_ID_POLL = 0,
	DEBUG_ID_STATE,
	DEBUG_ID_SLOT_INFO,
	DEBUG_ID_RESET,
	DEBUG_ID_MAX,
};

static int debug_write(struct te_debug_item *item, char *str)
{
	struct lxdvb_ca *ca = item->private;
	int rc = 0;

	switch (item->flags) {
	case DEBUG_ID_RESET:
		rc = do_ioc_ca_reset(ca, 0);
		break;
	default:
		rc = -EPERM;
	}

	return rc;
}

#define dprintf(fmt, args...)	seq_printf(m, fmt, ##args)
static void proc_print_poll(struct seq_file *m, struct lxdvb_ca *ca)
{
	int status;
	int slot = -1;
	int result = 0;

	status = lxdvb_ca_io_read_condition(ca, &result, &slot);
	dprintf("status:%d result:%d, slot:%d\n", status, result, slot);
}

static void proc_print_slot_state(struct seq_file *m, struct lxdvb_ca *ca)
{
	struct dvb_ca_slot *s;

	s = &ca->slot_info[0];
	mutex_lock(&s->slot_lock);

	dprintf("state: [%s] is_ciplus: %d version: %d\n",
		get_slot_state_str(s->slot_state), s->is_ciplus,
		s->version);
//	dprintf("fragbuf count [%d]\n\n", count_fragbuf(s));

	mutex_unlock(&s->slot_lock);
}

static void proc_print_slot_info(struct seq_file *m, struct lxdvb_ca *ca)
{
	struct ca_slot_info info;

	get_ioc_ca_slot_info(ca, &info);

	dprintf("num:%d type: %d flags: %u\n",
		info.num, info.type, info.flags);
}

static int debug_show(struct te_debug_item *item, struct seq_file *m)
{
	struct lxdvb_ca *ca = item->private;

	switch (item->flags) {
	case DEBUG_ID_POLL:
		proc_print_poll(m, ca);
		break;
	case DEBUG_ID_STATE:
		proc_print_slot_state(m, ca);
		break;
	case DEBUG_ID_SLOT_INFO:
		proc_print_slot_info(m, ca);
		break;
	default:
		return -EPERM;
	}

	return 0;
}

static const struct te_debug_simple_ops debug_ops = {
	.show = debug_show,
	.write = debug_write,
};

static const struct te_debug_item_info debug_list[] = {
	DBGITM_SIM_R("poll", &debug_ops, DEBUG_ID_POLL),
	DBGITM_SIM_R("state", &debug_ops, DEBUG_ID_STATE),
	DBGITM_SIM_R("slot_info", &debug_ops, DEBUG_ID_SLOT_INFO),
	DBGITM_SIM_W("ca_reset", &debug_ops, DEBUG_ID_RESET),
};

/* webos linuxtv proc */
static int proc_show_status(struct lxdvb_proc_item *item, struct seq_file *m)
{
	struct lxdvb_ca *ca = item->private;
	struct dvb_ca_slot *s = &ca->slot_info[0];

	mutex_lock(&s->slot_lock);

	dprintf("slot_state: [%s]\n", get_slot_state_str(s->slot_state));

	mutex_unlock(&s->slot_lock);

	return 0;
}

static struct lxdvb_proc_item_info proc_list[] = {
	LXDVB_PROC_ITEM_SHOW("status", proc_show_status, 0),
};

static int ca_dump_start(struct te_dump_device *dev,
			 struct te_dump_handle *h, struct te_dump_cfg *cfg)
{
	struct lxdvb_ca *ca = dev->private;
	struct debug_dump *d = &ca->dump;
	int rc;
	struct te_pcap_hdr hdr;

	if (d->running) {
		log_error("already started");
		return -EBUSY;
	}

	d->buf = cfg->data;

	memset(&hdr, 0, sizeof(hdr));
	hdr.magic_number = TE_PCAP_MAGIC;
	hdr.version_major = TE_PCAP_VER_MAJOR;
	hdr.version_minor = TE_PCAP_VER_MINOR;
	hdr.network = TE_PCAP_LINKTYPE_CA;

	rc = te_hwbuf_cwrite(d->buf, &hdr, sizeof(hdr));
	if (rc) {
		return rc;
	}

	d->running = true;
	h->dev_handle = d;

	return 0;
}

static void ca_dump_stop(struct te_dump_device *dev,
			 struct te_dump_handle *h)
{
	struct debug_dump *d = h->dev_handle;

	mutex_lock(&d->mutex);
	d->running = false;
	mutex_unlock(&d->mutex);

	h->dev_handle = NULL;

	return;
}

struct ca_pseudo_hdr {
	u8 ver;
	u8 event;
	u16 size;
};

#define PSEUDO_HDR_TYPE_HOST_TO_CAM	0xfe
#define PSEUDO_HDR_TYPE_CAM_TO_HOST	0xff

static void ca_dump_write(struct debug_dump *d,
			  const char __user *data, u32 size, bool is_read)
{
	int rc;
	struct te_pcap_rec_hdr rhdr;
	struct ca_pseudo_hdr phdr;
	s64 usec;
	s64 sec;

	mutex_lock(&d->mutex);

	if (!d->running || te_hwbuf_error(d->buf)) {
		mutex_unlock(&d->mutex);
		return;
	}

	sec = te_get_us_tick();
	usec = do_div(sec, USEC_PER_SEC);

	rhdr.ts_sec = sec;
	rhdr.ts_usec = usec;
	rhdr.incl_len = size + sizeof(phdr);
	rhdr.orig_len = rhdr.incl_len;

	rc = te_hwbuf_cwrite(d->buf, &rhdr, sizeof(rhdr));
	if (rc < 0) {
		te_hwbuf_set_error(d->buf, rc);
		goto exit;
	}

	phdr.ver = 0;
	phdr.event = (is_read) ?
		     PSEUDO_HDR_TYPE_CAM_TO_HOST : PSEUDO_HDR_TYPE_HOST_TO_CAM;
	phdr.size = te_swap16((u16)size);

	rc = te_hwbuf_cwrite(d->buf, &phdr, sizeof(phdr));
	if (rc < 0) {
		te_hwbuf_set_error(d->buf, rc);
		goto exit;
	}

	rc = te_hwbuf_cwrite_user(d->buf, data, size);
	if (rc < 0)
		te_hwbuf_set_error(d->buf, rc);

exit:
	mutex_unlock(&d->mutex);
}

static struct te_dump_device dump_device = {
	.module = TE_DUMP_MODULE_CA,
	.start = ca_dump_start,
	.stop = ca_dump_stop,
};


/* Initialisation/shutdown functions */
static int debug_init(struct lxdvb_ca *ca, struct lxdvb_device *dev)
{
	int rc;

	ca->dump.running = false;
	mutex_init(&ca->dump.mutex);

	dump_device.private = ca;
	rc = te_dump_register_device(&dump_device);
	CHECK_ERROR(rc < 0, return rc, "fail to register dump_device:%d", rc);

	ca->debug_dir = te_debug_create_dir("ca", dev->debug_dir);
	if (!ca->debug_dir) {
		log_error("error in te_debug_create_dir");
		return -EIO;
	}
	debug_create_item_files(debug_list, ca, ca->debug_dir);

	ca->proc_dir = lxdvb_proc_create_dir("dvb_ca", NULL);
	if (!ca->proc_dir) {
		log_error("error in lxdvb_proc_create_dir");
		return -EIO;
	}
	lxdvb_proc_create_files(proc_list, ca, ca->proc_dir);

	return 0;
}

static void debug_release(struct lxdvb_ca *ca)
{
	te_debug_remove_dir(ca->debug_dir);
}

/**
 * Initialise a new DVB CA EN50221 interface device.
 *
 * @dvb_adapter: DVB adapter to attach the new CA device to.
 * @ca: The dvb_ca instance.
 * @flags: Flags describing the CA device (DVB_CA_FLAG_*).
 * @slot_count: Number of slots supported.
 *
 * @return 0 on success, nonzero on failure
 */

static void register_cb_funcs(struct lxdvb_ca *ca)
{
	struct ci_callback cb;

	cb.camchange_irq = camchange_irq;
	cb.camready_callback = camready_callback; //FIXME: slot_state protection
	cb.arg = ca;

	ci_register_callback_funcs(ca->dev, &cb);
}

static void unregister_cb_funcs(struct lxdvb_ca *ca)
{
	struct ci_callback cb;

	cb.camchange_irq = NULL;
	cb.camready_callback = NULL;
	cb.arg = NULL;

	ci_register_callback_funcs(ca->dev, &cb);
}

static int dev_init(struct lxdvb_device *dev)
{
	int ret;
	int slot_count = 1;
	int i;
	struct lxdvb_ca *ca;
	struct te_device *tdev = get_te_device(dev);

	/* initialise the system data */
	if ((ca = kzalloc(sizeof(struct lxdvb_ca), GFP_KERNEL)) == NULL) {
		ret = -ENOMEM;
		goto exit;
	}
	ca->dev = ci_get_device(tdev);
	if (ca->dev == NULL) {
		ret = -EFAULT;
		goto free_ca;
	}
	ca->tdev = tdev;

	ca->flags = 0; //DVB_CA_FLAG_IRQ_CAMCHANGE
	ca->slot_count = slot_count;
	if ((ca->slot_info = kcalloc(slot_count, sizeof(struct dvb_ca_slot),
				     GFP_KERNEL)) == NULL) {
		ret = -ENOMEM;
		goto free_ca;
	}
	init_waitqueue_head(&ca->wait_queue);
	init_waitqueue_head(&ca->thread_wait_queue);
	ca->open = 0;
	ca->wakeup = 0;
	ca->next_read_slot = 0;

	/* register the DVB device */
	ret = dvb_register_device(&dev->adapter, &ca->dvbdev, &dvbdev_ca, ca,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
				  DVB_DEVICE_CA, 0);
#else
				  DVB_DEVICE_CA);
#endif
	if (ret)
		goto free_slot_info;

	/* now initialise each slot mutex */
	for (i = 0; i < slot_count; i++) {
		spin_lock_init(&ca->slot_info[i].spinlock);

		//atomic_set(&ca->slot_info[i].camchange_count, 0);
		mutex_init(&ca->slot_info[i].slot_lock);
	}

	register_cb_funcs(ca);

	mutex_init(&ca->ioctl_mutex);
	debug_init(ca, dev);

	dev->ca = ca;

	return 0;

free_slot_info:
	kfree(ca->slot_info);
free_ca:
	kfree(ca);
exit:
	dev->ca = NULL;
	return ret;
}

static void dev_release(struct lxdvb_device *dev)
{
	struct lxdvb_ca *ca = dev->ca;

	log_debug("%s", __func__);

	dvb_unregister_device(ca->dvbdev);
	debug_release(ca);
	unregister_cb_funcs(ca);
	kfree(ca->slot_info);
	kfree(ca);
	dev->ca = NULL;
}

static int dev_suspend(struct lxdvb_device *dev)
{
	struct lxdvb_ca *ca = dev->ca;
	unsigned long flags;
	int i = 0;

	printk("lxdvb_ca - suspend BEGIN\n");

	/* turn off the interrupt */
	ci_slot_finalize(ca->dev);

	if (ca->open) {
		int state;

		mutex_lock(&ca->slot_info[i].slot_lock);

		state = ca->slot_info[i].slot_state;
		CA_NOTI(state, "shutdown by suspend - open cnt:%u", ca->open);
		lxdvb_ca_slot_shutdown(ca, i);
		if (ca->slot_info[i].rx_buf) {
			te_pktbuf_reset(&ca->slot_info[i].p_rx_buf);
		}
		spin_lock_irqsave(&ca->slot_info[i].spinlock, flags);
		ca->slot_info[i].camchanged = 0;
		ca->slot_info[i].camchange_type = DVB_CA_CAMCHANGE_REMOVED;
		spin_unlock_irqrestore(&ca->slot_info[i].spinlock, flags);

		mutex_unlock(&ca->slot_info[i].slot_lock);
	}

	printk("lxdvb_ca - suspend END\n");

	return 0;
}

static int dev_resume(struct lxdvb_device *dev)
{
	struct lxdvb_ca *ca = dev->ca;
	int rc;
	bool use_intr;

	printk("lxdvb_ca - resume BEGIN\n");

	use_intr = ca->flags & DVB_CA_FLAG_IRQ_CAMCHANGE;

	mutex_lock(&ca->slot_info[0].slot_lock);

	/* request interrupt */
	rc = ci_slot_initialize(ca->dev, use_intr);
	if (rc) {
		mutex_lock(&ca->slot_info[0].slot_lock);
		return rc;
	}

	mutex_unlock(&ca->slot_info[0].slot_lock);

	lxdvb_ca_thread_wakeup(ca); //wake up and check card detect

	printk("lxdvb_ca - resume END\n");

	return 0;
}

const struct lxdvb_sub_driver lxdvb_ca_driver = {
	.name = "lxdvb_ca",
	.init = dev_init,
	.release = dev_release,
	.suspend = dev_suspend,
	.resume = dev_resume,
};
