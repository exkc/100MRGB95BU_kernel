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
 *  CI register details. ( used only within kdriver )
 *
 *  @author		Srinivasan Shanmugam (srinivasan.shanmugam@lge.com)
 *  @author		Hwajeong Lee (hwajeong.lee@lge.com)
 *  @author		Jinhwan Bae (jinhwan.bae@lge.com) - modifier
 *  @author		Hyunho Kim (hyunho747.kim@lge.com) - modifier
 *  @version	1.0
 *  @date		2015.1.1
 *
 *  @addtogroup lg1150_ci
 *	@{
 */

#ifndef __CI_PROC_H__
#define __CI_PROC_H__

#include <linux/types.h>

#include "ci_cfg.h"
#include "ci_regdefs.h"

#if defined(CI_PROC_PCAP_ON)
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
#include <asm/page.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/memory.h>
#endif	//CI_PROC_PCAP_ON

#include "ci_util.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

//CI_PROC_PCAP_ON
enum _ci_pcap_event {
	CI_PCAP_HW_EVT				= 0xFB,
	CI_PCAP_COR_WRITE			= 0xFC,
	CI_PCAP_CIS_READ			= 0xFD,
	CI_PCAP_DATA_HOST_TO_CAM	= 0xFE,
	CI_PCAP_DATA_CAM_TO_HOST	= 0xFF,
};

//for CI_PCAP_HW_EVT
enum _ci_pacp_hw_event {
	CI_PCAP_HW_EVT_CAM_IN		= 0x01,
	CI_PCAP_HW_EVT_CAM_OUT		= 0x02,
	CI_PCAP_HW_EVT_POWER_ON		= 0x03,
	CI_PCAP_HW_EVT_POWER_OFF	= 0x04,
	CI_PCAP_HW_EVT_TS_ROUTE		= 0x05,
	CI_PCAP_HW_EVT_TS_BYPASS	= 0x06,
	CI_PCAP_HW_EVT_RESET_H		= 0x07,
	CI_PCAP_HW_EVT_RESET_L		= 0x08,
	CI_PCAP_HW_EVT_READY_H		= 0x09,
	CI_PCAP_HW_EVT_READY_L		= 0x0A,
	CI_PCAP_HW_EVT_MAX,
};

struct ci_pcap_operations {
	int		(*init)(CI_DEV_T *cidev);
	int		(*uninit)(CI_DEV_T *cidev);
	//
	int		(*init_cis_hdr)(CI_DEV_T *cidev, int off);
	int		(*store_cis_data)(CI_DEV_T *cidevv, char *cis_buf, int len);
	int		(*submit_cis_pkt)(CI_DEV_T *cidev);
	int		(*submit_cor_pkt)(CI_DEV_T *cidev, unsigned int addr, unsigned char val);
	int		(*submit_hw_evt)(CI_DEV_T *cidev, int hw_event);
	int		(*submit_io_pkt)(CI_DEV_T *cidev, char *io_buf, int len, int event);
};
typedef struct ci_pcap_operations ci_pcap_ops_t;

#define CI_PROC_NAME_SZ		32

#if defined(CI_PROC_PCAP_ON)
struct ci_pcap_sf_hdr {
	unsigned int	magic;
	unsigned short	version_major;
	unsigned short	version_minor;
	unsigned int	thiszone;	/* gmt to local correction */
	unsigned int	sigfigs;	/* accuracy of timestamps */
	unsigned int	snaplen;	/* max length saved portion of each pkt */
	unsigned int	linktype;	/* data link type (LINKTYPE_*) */
};
typedef struct ci_pcap_sf_hdr ci_pcap_sf_hdr_t;

struct ci_pcap_timeval {
	unsigned int	tv_sec;		/* seconds */
	unsigned int	tv_usec;	/* microseconds */
};
typedef struct ci_pcap_timeval ci_pcap_timeval_t;

#define CI_PCAP_PSEUDO_VERION	0

struct ci_pseudo_header {
	unsigned char	version;	//always 0
	unsigned char	event;
	unsigned short	len;		//data length
} __attribute__((__packed__));
typedef struct ci_pseudo_header ci_pseudo_header_t;

struct ci_pcap_sf_pkthdr {
	struct ci_pcap_timeval	tval;		/* time stamp */
//	struct timeval			tval;
    unsigned int			caplen;		/* length of portion present */
    unsigned int			len;		/* length this packet (off wire) */
};
typedef struct ci_pcap_sf_pkthdr ci_pcap_sf_pkthdr_t;

#define CI_PCAP_SIZE_FILE_HDR			(sizeof(struct ci_pcap_sf_hdr))
#define CI_PCAP_SIZE_PKT_HDR			(sizeof(struct ci_pcap_sf_pkthdr))
#define CI_PCAP_SIZE_PSEDO_HDR			(sizeof(struct ci_pseudo_header))

#define CI_PCAP_MAGIC					(0xA1B2C3D4)
#define CI_PCAP_VERSION_MAJOR			(0x02)
#define CI_PCAP_VERSION_MINOR			(0x04)
#define CI_PCAP_LINK_TYPE				(0xEB)

#define CI_PCAP_RAW_DATA_MAX_RANGE		4
#define CI_PCAP_RAW_DATA_SIZE_MAX		(4096)
#define CI_PCAP_RAW_DATA_SIZE_MIN		(512)
#define CI_PCAP_RAW_DATA_SIZE			(2048)

#define CI_PCAP_PKT_DATA_SIZE			(CI_PCAP_RAW_DATA_SIZE + CI_PCAP_SIZE_PSEDO_HDR)

struct ci_pcap_event {
	struct list_head		e_link;
	//
	ktime_t					ts;
	unsigned int			len;
	//
	ci_pcap_sf_pkthdr_t		pheader;
	ci_pseudo_header_t		psdhdr;
	//
//	char					ebuf[CI_PCAP_PKT_DATA_SIZE];
	char					*ebuf;
};
typedef struct ci_pcap_event ci_pcap_event_t;

#define CI_PROC_NAME_SZ  32
struct ci_pcap {
	ci_pcap_sf_hdr_t		fheader;
	//
	int						snap_size;
	int						data_max;
	//
	struct kmem_cache		*e_slab;
	struct kmem_cache		*e_buff;
	struct list_head		e_list;
	int						nevents;
	//
	wait_queue_head_t		wait;
	int						print_limit;
	char					*print_buf;
	//
	struct mutex 			print_lock;
	spinlock_t				queue_lock;
	//
	unsigned int			print_first;
	unsigned int			print_count;
	//
	void					*pcap_info;
	//
	void					*priv_data;
};
typedef struct ci_pcap ci_pcap_t;

struct ci_mon_ptr {
	int		cnt;
	char	*pbuf;
};
typedef struct ci_mon_ptr ci_mon_ptr_t;

struct ci_pcap_param {
	char	*name;
//	int		*pvalue;
	int		range;		// 4 for "1234"
	int		max;
	int		min;
};
typedef struct ci_pcap_param ci_pcap_param_t;

struct ci_pcap_info {
	CI_DEV_T				*cidev;
	ci_pcap_t				*pcap;
	int						raw_data_size;
};
typedef struct ci_pcap_info ci_pcap_info_t;

/*
 * This limit exists to prevent OOMs when the user process stops reading.
 * If usbmon were available to unprivileged processes, it might be open
 * to a local DoS. But we have to keep to root in order to prevent
 * password sniffing from HID devices.
 */
#define CI_PCAP_EVENT_MAX  ((8*PAGE_SIZE) / sizeof(ci_pcap_event_t))

#endif	/* CI_PROC_PCAP_ON */

struct ci_proc {
	CI_DEV_T				*cidev;
	OS_PROC_DESC_TABLE_T 	*table;
	struct proc_dir_entry	*root;
#if defined(CI_PROC_PCAP_ON)
	ci_pcap_info_t			pcap_info;
#endif
	struct {
		u32					is_gen_root			:1,
							is_rsvd01			:1,
							is_rsvd02			:1,
							is_rsvd03			:1,
							is_rsvd04			:1,
							is_rsvd05			:1,
							is_rsvd06			:1,
							is_rsvd07			:1,
							//
							is_pcap_dump_on		:1,
							is_rsvd09			:1,
							is_rsvd0A			:1,
							is_rsvd0B			:1,
							is_rsvd0C			:1,
							is_rsvd0D			:1,
							is_rsvd0E			:1,
							is_rsvd0F			:1,
							//
							_rsvd				:(32-16);
	} is_flag;
};
typedef struct ci_proc ci_proc_t;

#define CI_PROC_PARENT		"lg"	/* same as 'BASE_PROC_NAME' in proc_util.c */

extern int ci_pcap_mon_cis_hdr(CI_DEV_T *cidev, int off);
extern int ci_pcap_mon_cis_data(CI_DEV_T *cidev, char *cis_buf, int len);
extern int ci_pcap_mon_cis_pkt(CI_DEV_T *cidev);
extern int ci_pcap_mon_cor_pkt(CI_DEV_T *cidev, unsigned int addr, unsigned char val);
extern int ci_pcap_mon_hw_evt(CI_DEV_T *cidev, int hw_event);
extern int ci_pcap_mon_io_pkt(CI_DEV_T *cidev, char *io_buf, int len, int event);
extern int ci_pcap_mon_nego_pkt(CI_DEV_T *cidev, int size, int event);

extern int ci_init_proc(CI_DEV_T *cidev);
extern void ci_uninit_proc(CI_DEV_T *cidev);


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* __CI_PROC_H__ */


