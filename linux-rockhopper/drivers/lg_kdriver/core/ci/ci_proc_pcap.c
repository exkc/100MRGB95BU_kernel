/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
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
 *  Linux proc interface for ci device.
 *	ci device will teach you how to make device driver with new platform.
 *
 *  author		Srinivasan Shanmugam (srinivasan.shanmugam@lge.com) /  Hwajeong Lee (hwajeong.lee@lge.com)
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_ci
 *	@{
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
#include <linux/compiler.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/irqreturn.h>
#include <linux/mm.h>
#include <linux/rmap.h>
#include <linux/poll.h>
#include <linux/version.h>
#include <linux/smp.h>
#include <linux/vmalloc.h>
#include <linux/file.h>
#include <linux/clk.h>
#include <linux/input.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/pm_runtime.h>
#include <linux/suspend.h>
#include <linux/namei.h>
#include <linux/path.h>
#include <asm/div64.h>
#include <asm/page.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/memory.h>

#include "ci_dev.h"
#include "ci_hw_cis.h"
#include "ci_proc.h"
#include "ci_util.h"

/* PCAP DUMP
Wireshark : www.wireshark.org

[Usage - webOS]
(1) Remove CI Module from target board

(2) Go to /proc/lg/c0i/pcap
	/proc/lg/ci0/pcap # ls -al
	total 0
	dr-xr-xr-x    2 root     root             0 Oct 28 15:48 .
	dr-xr-xr-x    3 root     root             0 Oct 28 15:48 ..
	-r--r-----    1 root     root             0 Oct 28 15:50 pcap_dump
	-rw-r-----    1 root     root             0 Oct 28 15:50 pcap_size

(3) Set buffer size : 512 <= x <= 4096
	/proc/lg/ci0/pcap # echo 4096 > pcap_size
	* Initial value is 0, which means 'off'

(4) Set Capture file, now ci monitor is operational
	/proc/lg/ci0/pcap # cat pcap_dump > /tmp/ci.pcap

(5) Insert CI Module into target board
    then all ci operational data will be captured into pcap file

(6) Press Ctrl+C to finish capture

(7) Copy the '/tmp/ci.pcap' file from the board and open it with Wireshark

[Usage - Pioneer]
(1) Remove CI Module from target board

(2) Go to /proc/lg/ci0/pcap

(3) Set buffer size : 512 <= x <= 4096

(4) Set Capture file, now ci monitor is operational
	/proc/lg/ci0/pcap # cat pcap_dump > /tmp/ci.pcap &
	* '&' is very important because you should use kadp menu

(5) Insert CI Module into target board

(6) go to 'kadp > 0x50', then test CI operation

(7) go to shell again after test completion

(8) Kill 'cat pcap_dump' process
	# ps -a | grep pcap
	11984 root       0:00 cat pcap_dump	<--- kill this
	13941 root       0:00 grep pcap
	# kill -9 11984
	[ 1817.005127] ci       NOT (11984) ci_pcap_dump_release: 847 ] PCAP dump closed

(9) Copy the '/tmp/ci.pcap' file from the board and open it with Wireshark

*/

/*
[Wireshark pcap file format]

Global Header + [Packet Header + Packet Data] + [Packet Header + Packet Data] + ...

D4 C3 B2 A1 02 00 04 00 00 00 00 00 00 00 00 00
~~~~~~~~~~~ ~~~~~ ~~~~~ ~~~~~~~~~~~ ~~~~~~~~~~~
magic       major minor thiszone    sigfigs

00 02 00 00 EB 00 00 00 E8 42 6E 4D 38 7F 0C 00
~~~~~~~~~~~ ~~~~~~~~~~~ ~~~~~~~~~~~ ~~~~~~~~~~~
snaplen     linktype    ts.tv_sec   ts.tv_usec : from gettimeofday

00 02 00 00 05 00 00 00 00 FB 00 01 01 xx xx xx
~~~~~~~~~~~ ~~~~~~~~~~~ ~~~~~~~~~~~~~~
caplen      len         packet data

#define TCPDUMP_MAGIC 0xa1b2c3d4

#define LINKTYPE_DVB_CI	235	//0xEB

//Global Header
struct pcap_file_header {
	bpf_u_int32 magic;
	u_short version_major;
	u_short version_minor;
	bpf_int32 thiszone;		// gmt to local correction
	bpf_u_int32 sigfigs;	// accuracy of timestamps
	bpf_u_int32 snaplen;	// max length saved portion of each pkt
	bpf_u_int32 linktype;	// data link type (LINKTYPE_*)
};

//Packet Header
struct pcap_pkthdr {
	struct timeval ts;	// time stamp
	bpf_u_int32 caplen;	// length of portion present
	bpf_u_int32 len;	// length this packet (off wire)
};

packet data size는 caplen 기준 (caplen = snaplen)
valid data size는 len 기준

[www.kaiser.cx/pcap-dvbci.html]
//Pseudo Header in DVB-CI Packet Data
struct dvbci_header {
	u_int8_t version;	//always 0
	u_int8_t event;
	u_int16_t len;		//data length	//Big-Endian
} __attribute__((__packed__));

//event
DATA_CAM_TO_HOST	0xFF
DATA_HOST_TO_CAM	0xFE
CIS_READ		0xFD
COR_WRITE		0xFC
HW_EVT			0xFB

//HW_EVT
CAM_IN			0x01
CAM_OUT			0x02
POWER_ON		0x03
POWER_OFF		0x04
TS_ROUTE		0x05
TS_BYPASS		0x06
RESET_H			0x07
RESET_L			0x08
READY_H			0x09
READY_L			0x0A

*/

/* pcap_show : print log format to show partial(< CI_PCAP_SHOW_DATA_LIMIT) data

/proc/lg/ci0/pcap # cat pcap_show
>    76.159674: HWE - CAM IN
>    76.393955: HWE - POWER OFF
>    76.693978: HWE - POWER ON
>    76.993997: HWE - RESET L
>    76.999012: HWE - RESET H
>    76.999109: CIS( 129) 1D 04 00 DB 08 FF 1C 03 00 08 FF 15 19 05 00 53 6D 61 72 44 54 56 00 44 56 00 44 56 42 20 43 41 20 4D 6F ...
>    79.177264: COR(   3) 03 FE 0F
>    81.130955: <-C(NEGO) 07 FE
>    81.146006: H->(NEGO) 07 FE
>    81.247367: H->(   5) 01 00 82 01 01
>    81.267594: <-C(   9) 01 00 83 01 01 80 02 01 00
>    81.287795: H->(   5) 01 00 A0 01 01
>    81.307957: <-C(   6) 01 00 80 02 01 80
>    81.328143: H->(   5) 01 00 81 01 01
>    81.346838: <-C(  15) 01 00 A0 07 01 91 04 00 01 00 41 80 02 01 00
>    81.367263: H->(  14) 01 00 A0 0A 01 92 07 00 00 01 00 41 00 01
>    81.387547: <-C(   6) 01 00 80 02 01 00
...
*/

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

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
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
DEFINE_MUTEX(_ci_proc_mutex);
#define ci_proc_mutex_lock()		mutex_lock(&_ci_proc_mutex);
#define ci_proc_mutex_unlock()		mutex_unlock(&_ci_proc_mutex);

#define CI_PCAP_TIME_FORMAT		"%5ld.%06ld"

#if defined(CI_PROC_PCAP_ON)

#define CI_PCAP_STR_LEN				128

static int ci_pcap_chk_io_evt(int event)
{
	switch (event) {
	case CI_PCAP_DATA_CAM_TO_HOST:
	case CI_PCAP_DATA_HOST_TO_CAM:
		break;
	default:
		LOG_ERROR("Invalid event : %d\n", event);
		event = -1;
		break;
	}
	return event;
}

static int ci_pcap_chk_hw_evt(int hw_event)
{
	if (hw_event >= CI_PCAP_HW_EVT_MAX) {
		LOG_ERROR("Invalid hw_event : %d\n", hw_event);
		return -1;
	}

	return 0;
}

static void ci_pcap_free_evt(ci_pcap_t *pcap, ci_pcap_event_t *pevt)
{
	kmem_cache_free(pcap->e_buff, pevt->ebuf);
	kmem_cache_free(pcap->e_slab, pevt);
}

static ci_pcap_event_t *ci_pcap_gen_evt(ci_pcap_t *pcap)
{
	ci_pcap_event_t *pevt = NULL;
	int event_max;

	event_max = (8*PAGE_SIZE) / (sizeof(ci_pcap_event_t) + pcap->data_max);
//	if (pcap->nevents >= CI_PCAP_EVENT_MAX) {
	if (pcap->nevents >= event_max) {
		LOG_WARNING("MAX events : max[%d]\n", event_max);
		goto out;
	}

	pevt = kmem_cache_alloc(pcap->e_slab, GFP_ATOMIC);
	if (pevt == NULL) {
		LOG_ERROR("NULL pevt\n");
		goto out;
	}

	pevt->ebuf = kmem_cache_alloc(pcap->e_buff, GFP_ATOMIC);
	if (pevt->ebuf == NULL) {
		kmem_cache_free(pcap->e_slab, pevt);
		LOG_ERROR("NULL pevt->ebuf\n");
		goto out;
	}

out:
	return pevt;
}

static void ci_pcap_init_file_hdr(ci_pcap_t *pcap)
{
	struct ci_pcap_sf_hdr *fheader = &pcap->fheader;

	fheader->magic = CI_PCAP_MAGIC;
	fheader->version_major = CI_PCAP_VERSION_MAJOR;
	fheader->version_minor = CI_PCAP_VERSION_MINOR;

	fheader->thiszone = 0;
	fheader->sigfigs = 0;
	fheader->snaplen = pcap->snap_size;
	fheader->linktype = CI_PCAP_LINK_TYPE;
}

static int ci_pcap_init_evt(ci_pcap_event_t *pevt, int len, int event)
{
	pevt->ts = ktime_get();
	pevt->len = CI_PCAP_SIZE_PSEDO_HDR + len;

	pevt->psdhdr.version = CI_PCAP_PSEUDO_VERION;
	pevt->psdhdr.event = event;
	pevt->psdhdr.len = len;

	return 0;
}

static int ci_pcap_submit_evt(ci_pcap_t *pcap, ci_pcap_event_t *pevt)
{
	unsigned long flags;

	if (pcap == NULL) {
		return -ENODEV;
	}

	spin_lock_irqsave(&pcap->queue_lock, flags);

	pcap->nevents++;
	list_add_tail(&pevt->e_link, &pcap->e_list);
	wake_up(&pcap->wait);

	spin_unlock_irqrestore(&pcap->queue_lock, flags);
	return 0;
}

static int ci_pcap_init_cis_hdr(CI_DEV_T *cidev, int off)
{
	ci_pcap_info_t *pcap_info;
	ci_pcap_t *pcap;
	ci_pcap_event_t *pevt;
	int ret = 0;

	BUG_ON(cidev->proc == NULL);

	if (!cidev->proc->is_flag.is_pcap_dump_on) {
		//Not opened : skip
		return 0;
	}

	pcap_info = &cidev->proc->pcap_info;
	pcap = pcap_info->pcap;
	if (pcap == NULL) {
		//Not opened : skip
		return 0;
	}

	if (off) {	//cancel
		pevt = pcap->priv_data;
		if (pevt != NULL) {
			ci_pcap_free_evt(pcap, pevt);
			pcap->priv_data = NULL;
		}
		return 0;
	}

	pevt = ci_pcap_gen_evt(pcap);
	if (pevt == NULL) {
		return -1;
	}

	ci_pcap_init_evt(pevt, 0, CI_PCAP_CIS_READ);

	pcap->priv_data = pevt;
	return ret;
}

int ci_pcap_store_cis_data(CI_DEV_T *cidev, char *cis_buf, int len)
{
	ci_pcap_info_t *pcap_info;
	ci_pcap_t *pcap;
	ci_pcap_event_t *pevt;
	char *buf;
	int last_len;

	BUG_ON(cidev->proc == NULL);

	if (!cidev->proc->is_flag.is_pcap_dump_on) {
		//Not opened : skip
		return 0;
	}

	pcap_info = &cidev->proc->pcap_info;
	pcap = pcap_info->pcap;
	if (pcap == NULL) {
		//Not opened : skip
		return 0;
	}

	pevt = pcap->priv_data;
	if (pevt == NULL) {
	//	LOG_ERROR("NULL pevt\n");
		return -1;
	}

	last_len = pevt->psdhdr.len;
	if ((last_len + len) > pcap->data_max) {
		len = pcap->data_max - last_len;
		if (len < 0) {
			LOG_ERROR("Dump buffer full in CIS\n");
			return 0;
		}
	}

	buf = &pevt->ebuf[last_len];
	memcpy((void *)buf, (void *)cis_buf, len);
	pevt->psdhdr.len += len;
	pevt->len += len;

	LOG_PROC_LVL1("> PCAP - Store CIS data : 0x%04X, 0x%04X\n", last_len, len);

	return 0;
}

int ci_pcap_submit_cis_pkt(CI_DEV_T *cidev)
{
	ci_pcap_info_t *pcap_info;
	ci_pcap_t *pcap;
	ci_pcap_event_t *pevt;
	int ret;

	BUG_ON(cidev->proc == NULL);

	if (!cidev->proc->is_flag.is_pcap_dump_on) {
		//Not opened : skip
		return 0;
	}

	pcap_info = &cidev->proc->pcap_info;
	pcap = pcap_info->pcap;
	if (pcap == NULL) {
		//Not opened : skip
		return 0;
	}

	pevt = pcap->priv_data;
	if (pevt == NULL) {
		LOG_ERROR("NULL pevt\n");
		return -1;
	}
	pcap->priv_data = NULL;

	ret = ci_pcap_submit_evt(pcap, pevt);
	LOG_PROC_LVL1("> PCAP - Catch CIS data\n");
	return ret;
}

int ci_pcap_submit_cor_pkt(CI_DEV_T *cidev, unsigned int addr, unsigned char val)
{
	ci_pcap_info_t *pcap_info;
	ci_pcap_t *pcap;
	ci_pcap_event_t *pevt;
	char *buf;
	int ret;

	BUG_ON(cidev->proc == NULL);

	if (!cidev->proc->is_flag.is_pcap_dump_on) {
		//Not opened : skip
		return 0;
	}

	pcap_info = &cidev->proc->pcap_info;
	pcap = pcap_info->pcap;
	if (pcap == NULL) {
		//Not opened : skip
		return 0;
	}

	pevt = ci_pcap_gen_evt(pcap);
	if (pevt == NULL) {
		return -1;
	}

	ci_pcap_init_evt(pevt, 0, CI_PCAP_COR_WRITE);

	buf = pevt->ebuf;
	buf[0] = addr>>8;
	buf[1] = addr&0xFF;
	buf[2] = val;
	pevt->psdhdr.len += 3;
	pevt->len += 3;

	ret = ci_pcap_submit_evt(pcap, pevt);
	LOG_PROC_LVL1("> PCAP - Catch COR data\n");
	return ret;
}

int ci_pcap_submit_hw_pkt(CI_DEV_T *cidev, int hw_event)
{
	ci_pcap_info_t *pcap_info;
	ci_pcap_t *pcap;
	ci_pcap_event_t *pevt;
	char *buf;
	int ret;

	BUG_ON(cidev->proc == NULL);

	if (!cidev->proc->is_flag.is_pcap_dump_on) {
		//Not opened : skip
		return 0;
	}

	pcap_info = &cidev->proc->pcap_info;
	pcap = pcap_info->pcap;
	if (pcap == NULL) {
		//Not opened : skip
		return 0;
	}

	ret = ci_pcap_chk_hw_evt(hw_event);
	if (ret < 0) {
		return ret;
	}

	pevt = ci_pcap_gen_evt(pcap);
	if (pevt == NULL) {
		return -1;
	}

	ci_pcap_init_evt(pevt, 0, CI_PCAP_HW_EVT);

	buf = pevt->ebuf;
	buf[0] = hw_event;
	pevt->psdhdr.len += 1;
	pevt->len += 1;

	ret = ci_pcap_submit_evt(pcap, pevt);
	LOG_PROC_LVL1("> PCAP - Catch HW Event\n");
	return ret;
}

int ci_pcap_submit_io_pkt(CI_DEV_T *cidev, char *io_buf, int len, int event)
{
	ci_pcap_info_t *pcap_info;
	ci_pcap_t *pcap;
	ci_pcap_event_t *pevt;
	char *buf;
	int ret;

	BUG_ON(cidev->proc == NULL);

	if (!cidev->proc->is_flag.is_pcap_dump_on) {
		//Not opened : skip
		return 0;
	}

	pcap_info = &cidev->proc->pcap_info;
	pcap = pcap_info->pcap;
	if (pcap == NULL) {
		//Not opened : skip
		return 0;
	}

	ret = ci_pcap_chk_io_evt(event);
	if (ret < 0) {
		return ret;
	}

	pevt = ci_pcap_gen_evt(pcap);
	if (pevt == NULL) {
		return -1;
	}

	if (len > pcap->data_max) {
		LOG_WARNING("Dump buffer limit : %d > %d\n", len, pcap->data_max);
		len = pcap->data_max;
	}

	ci_pcap_init_evt(pevt, len, event);

	buf = pevt->ebuf;
	memcpy(buf, io_buf, len);

	ret = ci_pcap_submit_evt(pcap, pevt);
	LOG_PROC_LVL1("> PCAP - Catch I/O\n");
	return ret;
}

static ci_pcap_event_t *ci_pcap_event_fetch(ci_pcap_t *pcap)
{
	struct list_head *p;
	unsigned long flags;

	spin_lock_irqsave(&pcap->queue_lock, flags);
	if (list_empty(&pcap->e_list)) {
		spin_unlock_irqrestore(&pcap->queue_lock, flags);
		return NULL;
	}
	p = pcap->e_list.next;
	list_del(p);
	--pcap->nevents;
	spin_unlock_irqrestore(&pcap->queue_lock, flags);
	return list_entry(p, ci_pcap_event_t, e_link);
}

static ci_pcap_event_t *ci_pcap_read_wait(ci_pcap_t *pcap, struct file *file)
{
	DECLARE_WAITQUEUE(waita, current);
	ci_pcap_event_t *pevt = NULL;

	add_wait_queue(&pcap->wait, &waita);
	set_current_state(TASK_INTERRUPTIBLE);
	while ((pevt = ci_pcap_event_fetch(pcap)) == NULL) {
		if (file->f_flags & O_NONBLOCK) {
			set_current_state(TASK_RUNNING);
			remove_wait_queue(&pcap->wait, &waita);
			return ERR_PTR(-EWOULDBLOCK);
		}
		/*
		 * We do not count nwaiters, because ->release is supposed
		 * to be called when all openers are gone only.
		 */
		schedule();
		if (signal_pending(current)) {
			remove_wait_queue(&pcap->wait, &waita);
			return ERR_PTR(-EINTR);
		}
		set_current_state(TASK_INTERRUPTIBLE);
	}
	set_current_state(TASK_RUNNING);
	remove_wait_queue(&pcap->wait, &waita);
	return pevt;
}

const char *pcap_hw_event_name[] = {
	[CI_PCAP_HW_EVT_CAM_IN]		= "CAM IN",
	[CI_PCAP_HW_EVT_CAM_OUT]	= "CAM OUT",
	[CI_PCAP_HW_EVT_POWER_ON]	= "POWER ON",
	[CI_PCAP_HW_EVT_POWER_OFF]	= "POWER OFF",
	[CI_PCAP_HW_EVT_TS_ROUTE]	= "TS ROUTE",
	[CI_PCAP_HW_EVT_TS_BYPASS]	= "TS BYPASS",
	[CI_PCAP_HW_EVT_RESET_H]	= "RESET H",
	[CI_PCAP_HW_EVT_RESET_L]	= "RESET L",
	[CI_PCAP_HW_EVT_READY_H]	= "READY H",
	[CI_PCAP_HW_EVT_READY_L]	= "READY L",
};

static int ci_pcap_event_print(char *pbuf, ci_pcap_event_t *pevt)
{
	int ptr_cnt = 0;
	u16 pseudo_len = pevt->psdhdr.len;
	u8 event = pevt->psdhdr.event;

	switch (event) {
	case CI_PCAP_HW_EVT:
		{
			unsigned char idx = pevt->ebuf[0];
			char *s_name;
//	idx value is unsigned, so doesn't need to check negative value.
//			if ((idx < 0) || (idx > CI_PCAP_HW_EVT_READY_L)) {
			if (idx > CI_PCAP_HW_EVT_READY_L) {
				s_name = "unknown";
			} else {
				s_name = (char *)pcap_hw_event_name[idx];
			}
			ptr_cnt += snprintf(pbuf, CI_PCAP_STR_LEN, "HWE - %s", s_name);
		}
		break;
	case CI_PCAP_COR_WRITE:
		{
			ptr_cnt += snprintf(pbuf, CI_PCAP_STR_LEN, "COR(%4d) ", pseudo_len);
		}
		break;
	case CI_PCAP_CIS_READ:
		{
			ptr_cnt += snprintf(pbuf, CI_PCAP_STR_LEN, "CIS(%4d) ", pseudo_len);
		}
		break;
	case CI_PCAP_DATA_HOST_TO_CAM:
	case CI_PCAP_DATA_CAM_TO_HOST:
		{
			char *e_name;
			e_name = (event == CI_PCAP_DATA_HOST_TO_CAM)? "H->" : "<-C";
			if (pseudo_len == 2) {
				ptr_cnt += snprintf(pbuf, CI_PCAP_STR_LEN, "%s(NEGO) ", e_name);
			} else {
				ptr_cnt += snprintf(pbuf, CI_PCAP_STR_LEN, "%s(%4d) ", e_name, pseudo_len);
			}
		}
		break;
	default:
		{
			ptr_cnt += snprintf(pbuf, CI_PCAP_STR_LEN, "(Unknown)(%4d) ",pseudo_len);
		}
		break;
	};
	return ptr_cnt;
}

static void __ci_pcap_event_ctor(void *mem)
{
	ci_pcap_event_t *pevt = mem;

#if 1
	memset((void *)pevt, 0x00, sizeof(ci_pcap_event_t));
#else
	memset((void *)pevt, 0x00, sizeof(ci_pcap_event_t) - CI_PCAP_PKT_DATA_SIZE);
#endif
	INIT_LIST_HEAD(&pevt->e_link);
}

static int __ci_pcap_dump_open_gen(CI_DEV_T *cidev, ci_pcap_info_t *pcap_info)
{
	ci_pcap_t *pcap = NULL;
	char name[CI_PROC_NAME_SZ+1];
	int ret = 0;

	pcap = (ci_pcap_t *)ci_zalloc(sizeof(ci_pcap_t));
	if (pcap == NULL) {
		LOG_ERROR("unabled to allocate pcap\n");
		ret = -ENOMEM;
		goto out;
	}

	pcap->data_max = pcap_info->raw_data_size;
	pcap->snap_size = pcap->data_max + CI_PCAP_SIZE_PSEDO_HDR;

	pcap->print_limit = pcap->snap_size + CI_PCAP_SIZE_PKT_HDR;
	pcap->print_buf = ci_malloc(pcap->print_limit);
	if (pcap->print_buf == NULL) {
		ret = -ENOMEM;
		goto out_alloc;
	}

	snprintf(name, CI_PROC_NAME_SZ, "%s_pcap_s", ci_dev_name(cidev));
	pcap->e_slab = kmem_cache_create(name,
	    						sizeof(ci_pcap_event_t),
	    						sizeof(long),
	    						0,
							    __ci_pcap_event_ctor);
	if (pcap->e_slab == NULL) {
		ret = -ENOMEM;
		goto out_print_buf;
	}

	snprintf(name, CI_PROC_NAME_SZ, "%s_pcap_b", ci_dev_name(cidev));
	pcap->e_buff = kmem_cache_create(name,
					    		pcap->data_max,
					    		sizeof(long),
					    		0,
					    		NULL);
	if (pcap->e_buff == NULL) {
		ret = -ENOMEM;
		goto out_e_slab;
	}

	pcap->pcap_info = pcap_info;

	pcap_info->pcap = pcap;

	return 0;

out_e_slab:
	kmem_cache_destroy(pcap->e_slab);

out_print_buf:
	ci_free(pcap->print_buf);

out_alloc:
	ci_free(pcap);

out:
	return ret;
}

static int __ci_pcap_dump_open_pre(struct inode *inode,
								CI_DEV_T **_cidev,
								ci_pcap_info_t **_pcap_info)
{
	CI_DEV_T *cidev;
	ci_pcap_info_t *pcap_info;

	if (!capable(CAP_SYS_ADMIN)) {
		LOG_ERROR("capable(CAP_SYS_ADMIN) error\n");
		return -EPERM;
	}

#if 1	/* PDE - cidev */
	cidev = (CI_DEV_T *)PDE_DATA(inode);
	if (cidev == NULL) {
		LOG_ERROR("NULL cidev\n");
		return -ENODEV;
	}
	pcap_info = &cidev->proc->pcap_info;
	if (pcap_info == NULL) {
		LOG_ERROR("NULL pcap_info\n");
		return -ENODEV;
	}
	if (pcap_info->cidev != cidev) {
		LOG_ERROR("wrong cidev : cidev[%p] vs. pcap_info->cidev[%p]\n",
				cidev, pcap_info->cidev);
		return -EINVAL;
	}
#else
	pcap_info = (ci_pcap_info_t *)PDE_DATA(inode);
	if (pcap_info == NULL) {
		LOG_ERROR("NULL pcap_info\n");
		return -ENODEV;
	}
	cidev = (CI_DEV_T *)pcap_info->cidev;
	if (cidev == NULL) {
		LOG_ERROR("NULL cidev\n");
		return -ENODEV;
	}
#endif
	if (pcap_info->pcap != NULL) {
		LOG_WARNING("already opened\n");
		return -EFAULT;
	}

	(*_cidev) = cidev;
	(*_pcap_info) = pcap_info;

	return 0;
}

static int __ci_pcap_dump_open(struct inode *inode, struct file *file, int dump)
{
	CI_DEV_T *cidev;
	ci_pcap_info_t *pcap_info;
	ci_pcap_t *pcap;
	int ret = 0;

	ret = __ci_pcap_dump_open_pre(inode, &cidev, &pcap_info);
	if (ret != 0) {
		return ret;
	}

	ci_proc_mutex_lock();

	if ((pcap_info->raw_data_size < CI_PCAP_RAW_DATA_SIZE_MIN) ||
		(pcap_info->raw_data_size > CI_PCAP_RAW_DATA_SIZE_MAX))
	{
		LOG_ERROR("invalid snap size : %d -> set pcap_size first\n", pcap_info->raw_data_size);
		ret = -EINVAL;
		goto out;
	}

	ret = __ci_pcap_dump_open_gen(cidev, pcap_info);
	if (ret != 0) {
		goto out;
	}
	pcap = pcap_info->pcap;

	INIT_LIST_HEAD(&pcap->e_list);
	init_waitqueue_head(&pcap->wait);
	mutex_init(&pcap->print_lock);
	spin_lock_init(&pcap->queue_lock);

	ci_pcap_init_file_hdr(pcap);

	pcap->print_first = !!(dump);
	pcap->print_count = 0;

	file->private_data = pcap_info;

	cidev->proc->is_flag.is_pcap_dump_on = 1;
	ci_is_pcap_dump_on(cidev) = 1;

	ci_proc_mutex_unlock();

	LOG_NOTI("PCAP %s opened\n", (dump)?"dump":"show");

	return 0;

out:
	ci_proc_mutex_unlock();
	return ret;
}

#define CI_PCAP_SHOW_DATA_LIMIT		32

static int __ci_pcap_set_dump_data(ci_pcap_t *pcap, ci_pcap_event_t *pevt, int dump)
{
	struct timeval tval;
	struct ci_pcap_sf_pkthdr *pheader;
	char *buf;
	int ptr_cnt = 0;
	int i;
	u16 data_len, pseudo_len;
	u8 pseudo_evt;

	pheader = &pevt->pheader;
	tval = ktime_to_timeval(pevt->ts);
	pheader->tval.tv_sec = (unsigned int)tval.tv_sec;
	pheader->tval.tv_usec = (unsigned int)tval.tv_usec;
	pheader->caplen = pcap->fheader.snaplen;
	pheader->len = pevt->len;
	LOG_PROC_LVL4("# pakcet_hdr->tval.sec  : 0x%08X\n", pheader->tval.tv_sec);
	LOG_PROC_LVL4("#           ->tval.usec : 0x%08X\n", pheader->tval.tv_usec);
	LOG_PROC_LVL4("#           ->caplen    : 0x%08X\n", pheader->caplen);
	LOG_PROC_LVL4("#           ->len       : 0x%08X\n", pheader->len);

	pseudo_evt = pevt->psdhdr.event;
	pseudo_len = pevt->psdhdr.len;
	LOG_PROC_LVL4("# pseudo_hdr->version   : 0x%02X\n", pevt->psdhdr.version);
	LOG_PROC_LVL4("#           ->event     : 0x%02X\n", pseudo_evt);
	LOG_PROC_LVL4("#           ->len       : 0x%04X\n", pseudo_len);

	buf = pcap->print_buf;
	if (dump) {
		// 1. write packet header
		memcpy((void *)buf, (void *)pheader, CI_PCAP_SIZE_PKT_HDR);
		buf += CI_PCAP_SIZE_PKT_HDR;

		//Big-Endian reuiqred in wireshark format
		pevt->psdhdr.len = cpu_to_be16(pseudo_len);

		// 2. write packet data
		// 2-1. write pseudo header
		memcpy((void *)buf, (void *)&pevt->psdhdr, CI_PCAP_SIZE_PSEDO_HDR);
		buf += CI_PCAP_SIZE_PSEDO_HDR;

		// 2-2. write real I/O data
		memcpy((void *)buf, (void *)pevt->ebuf, pseudo_len);
		return pcap->print_limit;
	}

	//for pcap_show
//	ptr_cnt += sprintf(buf, "[%8d] ", pcap->print_count);
	ptr_cnt += snprintf(buf + ptr_cnt, CI_PCAP_STR_LEN, "> " CI_PCAP_TIME_FORMAT ": ",
					tval.tv_sec, tval.tv_usec);

	ptr_cnt += ci_pcap_event_print(buf + ptr_cnt, pevt);
	if (pseudo_evt != CI_PCAP_HW_EVT) {
		data_len = pseudo_len;
		if (data_len > CI_PCAP_SHOW_DATA_LIMIT) {
			data_len = CI_PCAP_SHOW_DATA_LIMIT;
		}
		for (i = 0 ; i < data_len ; i++) {
			ptr_cnt += snprintf(buf + ptr_cnt, pcap->print_limit - ptr_cnt,
					  		 	"%02X ", pevt->ebuf[i]);
		}
		if (pseudo_len > CI_PCAP_SHOW_DATA_LIMIT) {
			ptr_cnt += snprintf(buf + ptr_cnt, pcap->print_limit - ptr_cnt, "...");
		}
	}
	ptr_cnt += snprintf(buf + ptr_cnt, pcap->print_limit - ptr_cnt, "\n");
	return ptr_cnt;
}

static ssize_t __ci_pcap_dump_read(struct file *file, char __user *buf,
						size_t nbytes, loff_t *ppos, int dump)
{
	ci_pcap_info_t *pcap_info = file->private_data;
	ci_pcap_t *pcap = pcap_info->pcap;
	ci_pcap_event_t *pevt;
	ci_mon_ptr_t ptr;

	if (pcap == NULL) {
		LOG_ERROR("NULL pcap\n");
		return -EFAULT;
	}

	if (pcap->print_first) {
		mutex_lock(&pcap->print_lock);

		ptr.cnt = CI_PCAP_SIZE_FILE_HDR;
		ptr.pbuf = (char *)&pcap->fheader;

		if (copy_to_user((void *)buf, (void *)ptr.pbuf, ptr.cnt)) {
			ptr.cnt = -EFAULT;
		}

		pcap->print_first = 0;
		pcap->print_count++;

		mutex_unlock(&pcap->print_lock);

		LOG_PROC_LVL1("> PCAP - read 1st\n");

		return ptr.cnt;
	}

	if (IS_ERR(pevt = ci_pcap_read_wait(pcap, file))) {
		return PTR_ERR(pevt);
	}

	mutex_lock(&pcap->print_lock);

	{
		struct ci_pseudo_header *psdhdr;
		psdhdr = (struct ci_pseudo_header *)&pevt->psdhdr;
		LOG_PROC_LVL4("PCAP - read data : evt[0x%02X] len[0x%04X]\n",
					psdhdr->event, be16_to_cpu(psdhdr->len));
	}

	ptr.cnt = __ci_pcap_set_dump_data(pcap, pevt, dump);
	ptr.pbuf = pcap->print_buf;

	if (copy_to_user((void *)buf, (void *)ptr.pbuf, ptr.cnt)) {
		ptr.cnt = -EFAULT;
	}

	pcap->print_count++;

	mutex_unlock(&pcap->print_lock);
	ci_pcap_free_evt(pcap, pevt);

	return ptr.cnt;
}

static int __ci_pcap_dump_stop(ci_pcap_info_t *pcap_info)
{
	CI_DEV_T *cidev = pcap_info->cidev;
	ci_pcap_t *pcap = pcap_info->pcap;
	struct list_head *p;
	ci_pcap_event_t *pevt;
	unsigned long flags;

	if ((cidev == NULL) || (pcap == NULL)) {
		return 0;
	}

	cidev->proc->is_flag.is_pcap_dump_on = 0;

	spin_lock_irqsave(&pcap->queue_lock, flags);
	while (!list_empty(&pcap->e_list)) {
		p = pcap->e_list.next;
		pevt = list_entry(p, ci_pcap_event_t, e_link);
		list_del(p);
		--pcap->nevents;
		ci_pcap_free_evt(pcap, pevt);
	}
	spin_unlock_irqrestore(&pcap->queue_lock, flags);

	kmem_cache_destroy(pcap->e_buff);
	kmem_cache_destroy(pcap->e_slab);
	ci_free(pcap->print_buf);
	ci_free(pcap);
	pcap_info->pcap = NULL;

	ci_is_pcap_dump_on(cidev) = 0;

	return 0;
}

static int __ci_pcap_dump_release(struct inode *inode, struct file *file, int dump)
{
	CI_DEV_T *cidev;
	ci_pcap_info_t *pcap_info;
	ci_pcap_t *pcap;

	ci_proc_mutex_lock();

	pcap_info = (ci_pcap_info_t *)file->private_data;
	if (pcap_info == NULL) {
		LOG_ERROR("NULL pcap_info\n");
		goto out;
	}
	cidev = (CI_DEV_T *)pcap_info->cidev;
	if (cidev == NULL) {
		LOG_ERROR("NULL cidev\n");
		goto out;
	}
	pcap = pcap_info->pcap;
	if (pcap == NULL) {
		LOG_ERROR("NULL pcap\n");
		goto out;
	}

	__ci_pcap_dump_stop(pcap_info);

	file->private_data = NULL;

out:
	ci_proc_mutex_unlock();

	LOG_NOTI("PCAP %s closed\n", (dump)?"dump":"show");

	return 0;
}

static ssize_t ci_pcap_dump_read(struct file *file, char __user *buf,
						size_t nbytes, loff_t *ppos)
{
	return __ci_pcap_dump_read(file, buf, nbytes, ppos, 1);
}

static int ci_pcap_dump_open(struct inode *inode, struct file *file)
{
	return __ci_pcap_dump_open(inode, file, 1);
}

static int ci_pcap_dump_release(struct inode *inode, struct file *file)
{
	return __ci_pcap_dump_release(inode, file, 1);
}

const struct file_operations ci_pcap_dump_fops =
{
	.open		= ci_pcap_dump_open,
	.read		= ci_pcap_dump_read,
	.release	= ci_pcap_dump_release,
};

static ssize_t ci_pcap_show_read(struct file *file, char __user *buf,
						size_t nbytes, loff_t *ppos)
{
	return __ci_pcap_dump_read(file, buf, nbytes, ppos, 0);
}

static int ci_pcap_show_open(struct inode *inode, struct file *file)
{
	return __ci_pcap_dump_open(inode, file, 0);
}

static int ci_pcap_show_release(struct inode *inode, struct file *file)
{
	return __ci_pcap_dump_release(inode, file, 0);
}

const struct file_operations ci_pcap_show_fops =
{
	.open		= ci_pcap_show_open,
	.read		= ci_pcap_show_read,
	.release	= ci_pcap_show_release,
};

static int __ci_pcap_size_write_chk_value(int value, ci_pcap_param_t *param)
{
	if (value) {
		int value_min, value_max;

		value_min = param->min;
		value_max = param->max;
		if ((!value_min && !value_max) ||
			(value_min >= value_max)) {
			LOG_ERROR("Wrong range: min:%d, max:%d\n",
						value_min,
						value_max);
			return -EINVAL;
		}

		if ((value < value_min) ||
			(value > value_max))
		{
			LOG_ERROR("Out of range: %d [ON(min:%d, max:%d) / OFF(0)]\n",
						value,
						value_min,
						value_max);
			return -EINVAL;
		}
	}
	return 0;
}

static int __ci_pcap_size_write_pre(struct file *file,
									CI_DEV_T **_cidev,
									ci_pcap_info_t **_pcap_info)
{
	struct seq_file *m = (struct seq_file *)file->private_data;
	CI_DEV_T *cidev;
	ci_pcap_info_t *pcap_info;

#if 0
	if (m == NULL) {
		LOG_ERROR("NULL file->private_data\n");
		return -ENODEV;
	}
#endif

#if 1	/* PDE - cidev */
	cidev = (CI_DEV_T *)m->private;
	if (cidev == NULL) {
		LOG_ERROR("NULL cidev\n");
		return -ENODEV;
	}
	pcap_info = &cidev->proc->pcap_info;
	if (pcap_info == NULL) {
		LOG_ERROR("NULL pcap_info\n");
		return -ENODEV;
	}
	if (pcap_info->cidev != cidev) {
		LOG_ERROR("wrong cidev : cidev[%p] vs. pcap_info->cidev[%p]\n",
				cidev, pcap_info->cidev);
		return -EINVAL;
	}
#else
	pcap_info = (ci_pcap_info_t *)m->private;
	if (pcap_info == NULL) {
		LOG_ERROR("NULL pcap_info\n");
		return -ENODEV;
	}
	cidev = pcap_info->cidev;
	if (cidev == NULL) {
		LOG_ERROR("NULL cidev\n");
		return -ENODEV;
	}
#endif
	if (pcap_info->pcap != NULL) {
		LOG_WARNING("Not permitted while dump operating\n");
		return -EPERM;
	}

	(*_cidev) = cidev;
	(*_pcap_info) = pcap_info;

	return 0;
}

static ssize_t __ci_pcap_size_write(struct file *file,
								const char __user *buf,
								size_t size, loff_t *off,
								ci_pcap_param_t *param)
{
	CI_DEV_T *cidev;
	ci_pcap_info_t *pcap_info;
	int value_old;
	int value = 0;
	int	range_limit;
	char tmp[10], *t;
	char *endptr;
	int ret;

	if (size == 0) {
		return 0;
	}

	ret = __ci_pcap_size_write_pre(file, &cidev, &pcap_info);
	if (ret != 0) {
		return ret;
	}

	/* we only allow single write */
	if (*off != 0) {
		LOG_ERROR("Invalid offset : %lld\n", (*off));
		return -EINVAL;
	}

	range_limit = min((int)sizeof(tmp), param->range+1);
	if (size > (range_limit-1)) {
		LOG_ERROR("sizeof(tmp)      = %d\n", (int)sizeof(tmp));
		LOG_ERROR("param->range + 1 = %d\n", param->range+1);
		LOG_ERROR("range_limit      = %d\n", range_limit);
		LOG_ERROR("too long         : size(%zu) > (range_limit - 1)\n",
					size);
		return -EINVAL;
	}

	if (copy_from_user (tmp, buf, size)) {
		LOG_ERROR("copy_from_user failed\n");
		return -EFAULT;
	}

	tmp[size-1] = 0;
	t = tmp;

	value = simple_strtoul(t, &endptr, 0);
	if (endptr == t) {
		LOG_ERROR("Invalid\n");
		return -EINVAL;
	}

	ret = __ci_pcap_size_write_chk_value(value, param);
	if (ret != 0) {
		return ret;
	}

	ci_proc_mutex_lock();

	value_old = pcap_info->raw_data_size;
	pcap_info->raw_data_size = value;
	LOG_NOTI("\n%s changed : %d -> %d %s\n",
				param->name,
				value_old, value,
				(value == 0)? "(off)" : "(on)");

	ci_proc_mutex_unlock();
	return size;
}

static ssize_t ci_pcap_size_write(struct file *file,
								const char __user *buf,
								size_t size, loff_t *off)
{
	ci_pcap_param_t param;

	if (!capable(CAP_SYS_ADMIN)) {
		LOG_ERROR("capable(CAP_SYS_ADMIN) error\n");
		return -EPERM;
	}

	param.name = "Snap-Size";
	param.range = CI_PCAP_RAW_DATA_MAX_RANGE + 1;
	param.max = CI_PCAP_RAW_DATA_SIZE_MAX;
	param.min = CI_PCAP_RAW_DATA_SIZE_MIN;

	size = __ci_pcap_size_write(file, buf, size, off, &param);

	return size;
}

static int ci_pcap_size_show_pre(struct seq_file *m,
								CI_DEV_T **_cidev,
								ci_pcap_info_t **_pcap_info)
{
	CI_DEV_T *cidev;
	ci_pcap_info_t *pcap_info;

	if (!capable(CAP_SYS_ADMIN)) {
		LOG_ERROR("capable(CAP_SYS_ADMIN) error\n");
		return -EPERM;
	}

#if 0
	if (m == NULL) {
		LOG_ERROR("NULL m\n");
		return -ENODEV;
	}
#endif

#if 1	/* PDE - cidev */
	cidev = (CI_DEV_T *)m->private;
	if (cidev == NULL) {
		LOG_ERROR("NULL cidev\n");
		return -ENODEV;
	}
	pcap_info = &cidev->proc->pcap_info;
	if (pcap_info == NULL) {
		LOG_ERROR("NULL pcap_info\n");
		return -ENODEV;
	}
	if (pcap_info->cidev != cidev) {
		LOG_ERROR("wrong cidev : cidev[%p] vs. pcap_info->cidev[%p]\n",
				cidev, pcap_info->cidev);
		return -EINVAL;
	}
#else
	pcap_info = (ci_pcap_info_t *)m->private;
	if (pcap_info == NULL) {
		LOG_ERROR("NULL pcap_info\n");
		return -ENODEV;
	}
	CI_DEV_T *cidev = pcap_info->cidev;
	if (cidev == NULL) {
		LOG_ERROR("NULL cidev\n");
		return -ENODEV;
	}
#endif

	(*_cidev) = cidev;
	(*_pcap_info) = pcap_info;

	return 0;
}

static int ci_pcap_size_show(struct seq_file *m, void *data)
{
	CI_DEV_T *cidev;
	ci_pcap_info_t *pcap_info;
	int ret;

	ret = ci_pcap_size_show_pre(m, &cidev, &pcap_info);
	if (ret != 0) {
		return ret;
	}

	ci_proc_mutex_lock();
	seq_printf(m, "%d\n", pcap_info->raw_data_size);
	ci_proc_mutex_unlock();
	return 0;
}

static int ci_pcap_size_open(struct inode *inode, struct file *file)
{
	return single_open(file, ci_pcap_size_show, PDE_DATA(inode));
}

static int ci_pcap_size_release(struct inode *inode, struct file *file)
{
	return single_release(inode, file);
}

const struct file_operations ci_pcap_size_fops =
{
	.open		= ci_pcap_size_open,
	.read		= seq_read,
	.write		= ci_pcap_size_write,
	.llseek		= seq_lseek,
	.release	= ci_pcap_size_release,
};

static int ci_pcap_uninit(CI_DEV_T *cidev)
{
	ci_pcap_info_t *pcap_info = &cidev->proc->pcap_info;

	ci_proc_mutex_lock();

	__ci_pcap_dump_stop(pcap_info);
	pcap_info->cidev = NULL;

	ci_proc_mutex_unlock();

	LOG_DRV("* CI PROC PCAP uninit\n");

	return 0;
}

/*
 * /proc/lg/ci0/pcap_dump
 *              pcap_show
 *              pcap_size
 */
static int ci_pcap_init(CI_DEV_T *cidev)
{
	ci_pcap_info_t *pcap_info = &cidev->proc->pcap_info;

	ci_proc_mutex_lock();

	pcap_info->cidev = cidev;
//	pcap_info->raw_data_size = CI_PCAP_RAW_DATA_SIZE;

	ci_proc_mutex_unlock();

	LOG_DRV("* CI PROC PCAP init\n");

	return 0;
}

static const ci_pcap_ops_t ci_pcap_ops =
{
	.init			= ci_pcap_init,
	.uninit			= ci_pcap_uninit,
	//
	.init_cis_hdr	= ci_pcap_init_cis_hdr,
	.store_cis_data	= ci_pcap_store_cis_data,
	.submit_cis_pkt	= ci_pcap_submit_cis_pkt,
	.submit_cor_pkt	= ci_pcap_submit_cor_pkt,
	.submit_hw_evt	= ci_pcap_submit_hw_pkt,
	.submit_io_pkt	= ci_pcap_submit_io_pkt,
};

#else	//CI_PROC_PCAP_ON
static const ci_pcap_ops_t ci_pcap_ops =
{
	.init			= NULL,
	.uninit			= NULL,
	//
	.init_cis_hdr	= NULL,
	.store_cis_data	= NULL,
	.submit_cis_pkt	= NULL,
	.submit_cor_pkt	= NULL,
	.submit_hw_evt	= NULL,
	.submit_io_pkt	= NULL,
};

#endif	//CI_PROC_PCAP_ON

int ci_pcap_mon_cis_hdr(CI_DEV_T *cidev, int off)	// 0 : Init, 1 : Cancel
{
	if (ci_pcap_ops.init_cis_hdr != NULL)
		return (ci_pcap_ops.init_cis_hdr)((void *)cidev, off);
	return 0;
}

int ci_pcap_mon_cis_data(CI_DEV_T *cidev, char *cis_buf, int len)
{
	if (ci_pcap_ops.store_cis_data != NULL)
		return (ci_pcap_ops.store_cis_data)((void *)cidev, cis_buf, len);
	return 0;
}

int ci_pcap_mon_cis_pkt(CI_DEV_T *cidev)
{
	if (ci_pcap_ops.submit_cis_pkt != NULL)
		return (ci_pcap_ops.submit_cis_pkt)((void *)cidev);
	return 0;
}

int ci_pcap_mon_cor_pkt(CI_DEV_T *cidev, unsigned int addr, unsigned char val)
{
	if (ci_pcap_ops.submit_cor_pkt != NULL)
		return (ci_pcap_ops.submit_cor_pkt)((void *)cidev, addr, val);
	return 0;
}

int ci_pcap_mon_hw_evt(CI_DEV_T *cidev, int hw_event)
{
	if (ci_pcap_ops.submit_hw_evt != NULL)
		return (ci_pcap_ops.submit_hw_evt)((void *)cidev, hw_event);
	return 0;
}

int ci_pcap_mon_io_pkt(CI_DEV_T *cidev, char *io_buf, int len, int event)
{
	if (ci_pcap_ops.submit_io_pkt != NULL)
		return (ci_pcap_ops.submit_io_pkt)((void *)cidev, io_buf, len, event);
	return 0;
}

int ci_pcap_mon_nego_pkt(CI_DEV_T *cidev, int size, int event)
{
	u8 buf[2];

	buf[0] = size>>8;
	buf[1] = size&0xFF;
	return ci_pcap_mon_io_pkt(cidev, buf, 2, event);
}

int ci_pcap_mon_init(CI_DEV_T *cidev)
{
	if (ci_pcap_ops.init != NULL)
		return (ci_pcap_ops.init)(cidev);
	return 0;
}

int ci_pcap_mon_uninit(CI_DEV_T *cidev)
{
	if (ci_pcap_ops.uninit != NULL)
		return (ci_pcap_ops.uninit)(cidev);
	return 0;
}

