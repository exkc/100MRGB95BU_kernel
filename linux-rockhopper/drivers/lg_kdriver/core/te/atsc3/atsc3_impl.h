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
 *  sdec driver
 *
 *  @author	Yeonju Lee(yeonju.lee@lge.com)
 *  @version	1.0
 *  @date		2016-02-25
 *  @note		Additional information.
 */

#ifndef _ATSC3_IMPL_H_
#define _ATSC3_IMPL_H_

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/kthread.h>
#include <asm/io.h>
#include <linux/vmalloc.h>
#include <linux/poll.h>
#include <linux/freezer.h>
#include <linux/delay.h>

#include <lg1k/te/util.h>
#include <lg1k/te/reg.h>
#include <lg1k/te/debug.h>
#include <lg1k/te/buffer.h>
#include <lg1k/te/mem.h>
#include <lg1k/te/atsc3.h>

#include "logm_kapi.h"

#include "te_atsc3_kapi.h"

#include "atsc3_cfg.h"

#define	ATSC3_MODULE		"atsc3"
#define ATSC3_DEVICE_NAME	"lg1k-atsc3"
#define ATSC3_MEM_NAME		TE_MEM_SHARED_NAME

#define LOG_LEVEL_ERROR		LX_LOGM_LEVEL_ERROR	/* 0 */
#define LOG_LEVEL_WARNING	LX_LOGM_LEVEL_WARNING	/* 1 */
#define LOG_LEVEL_NOTI		LX_LOGM_LEVEL_NOTI	/* 2 */
#define LOG_LEVEL_INFO		LX_LOGM_LEVEL_INFO	/* 3 */
#define LOG_LEVEL_DEBUG		LX_LOGM_LEVEL_DEBUG	/* 4 */
#define LOG_LEVEL_TRACE		LX_LOGM_LEVEL_TRACE	/* 5 */
#define LOG_LEVEL_TRACE_EX	LX_LOGM_LEVEL_TRACE + 1 /* 6 */
#define LOG_LEVEL_FILTER	LX_LOGM_LEVEL_TRACE + 2 /* 7 */
#define LOG_LEVEL_IO		LX_LOGM_LEVEL_TRACE + 3 /* 8 */
#define LOG_LEVEL_CLOCK		LX_LOGM_LEVEL_TRACE + 4 /* 9 */

#define LOG_LEVEL_TIMEINFO	LX_LOGM_LEVEL_TRACE + 8 /* 13 */
#define LOG_LEVEL_DEVICE	LX_LOGM_LEVEL_TRACE + 9

#define ATSC3_LOG(type,fmt,args...) \
	LOGM_PRINT( g_atsc3_debug_fd, (LOG_LEVEL_##type), fmt, ##args)

#define log_error(fmt,args...)		ATSC3_LOG(ERROR,fmt,##args)
#define log_warning(fmt,args...)	ATSC3_LOG(WARNING,fmt,##args)
#define log_noti(fmt,args...)		ATSC3_LOG(NOTI,fmt,##args)
#define log_info(fmt,args...)		ATSC3_LOG(INFO,fmt,##args)
#define log_debug(fmt,args...)		ATSC3_LOG(DEBUG,fmt,##args)
#define log_trace(fmt,args...)		ATSC3_LOG(TRACE,fmt,##args)
#define log_trace_ex(fmt,args...)	ATSC3_LOG(TRACE_EX,fmt,##args)
#define log_filter(fmt,args...)		ATSC3_LOG(FILTER,fmt,##args)
#define log_io(fmt,args...)		ATSC3_LOG(IO,fmt,##args)
#define log_clock(fmt,args...)		ATSC3_LOG(CLOCK,fmt,##args)
#define log_timeinfo(fmt,args...)	ATSC3_LOG(TIMEINFO,fmt,##args)
#define log_device(fmt,args...)		ATSC3_LOG(DEVICE,fmt,##args)

#define FUNC_TRACE_ENTER()		log_trace("<--%s", __FUNCTION__)
#define FUNC_TRACE_EXIT()		log_trace("-->%s", __FUNCTION__)

#define FUNC_TRACE_EX_ENTER()		log_trace_ex("<--%s", __FUNCTION__)
#define FUNC_TRACE_EX_EXIT()		log_trace_ex("-->%s", __FUNCTION__)

#define CHECK_ERROR(__checker,__if_action,fmt,args...)   \
  TE_CHECK_IF_ERROR(__checker, log_error, __if_action , fmt, ##args )

#define CHECK_NULL_PARAM(param) \
  CHECK_ERROR((param) == NULL, return -EINVAL, "parameter(" #param ") is null")

#define CHECK_PARAM(__checker,fmt,args...) \
  CHECK_ERROR(__checker, return -EINVAL, "invalid parameter : " fmt, ##args)

struct atsc3_device;
struct atsc3_clock;
struct udp_filter;
struct ip_filter;
struct linksignal_filter;

struct atsc3_dev_message {
	struct mutex mutex;
	struct te_msgbuf buf;

	wait_queue_head_t wq;
	LX_ATSC3_NOTIFY_DATA_T param[LX_ATSC3_MAX_NOTIFY_DATA];
	volatile u32 widx;
	volatile u32 ridx;
};

struct atsc3_filter_buffer {
	u32 metabuf_saddr;
	u32 metabuf_eaddr;
	u32 databuf_saddr;
	u32 databuf_eaddr;
	u32 bbbuf_saddr;
	u32 bbbuf_eaddr;
};

struct atsc3_filter_channel {
	bool enable;
	struct atsc3_filter_buffer buffer;

	struct list_head linksignal_head;	/* linksignal filter list header */
	struct list_head ip_head;	/* ip  filter list header */
	struct list_head udp_head;	/* udp filter list header */

	u8 linksignal_req_num;	/* linksignal requested num */
	u8 udp_req_num;		/* udp requested num */
};

struct atsc3_input_monitor {
	u8 ch;
	struct mutex mutex;
	char name[32];
	bool enable;
	enum lx_te_input_port input;
	bool channel_enable;	/* H/W delivery enabled */
	bool ready;		/* TRUE : after getting 1st status */
	bool no_input;
	u32 message_count;	/* To disable verbose message */
	u32 pkt_count;		/* all packets including err_pkt.*/
	u32 err_pkt_count;	/* bb-frame error */
	u32 overflow_count;	/* full interrupt count from irq handler*/
};

enum atsc3_dump_state {
	INPUT_DUMP_IDLE = 0,
	INPUT_DUMP_RUNNING,
	INPUT_DUMP_SUSPEND,
};

struct atsc3_input_dump {
	volatile enum atsc3_dump_state state;
	u8 ch;
	u32 flags;		/* WAIT_MODE, CHECK_OVERFLOW */
	u32 intr;

	struct timer_list timer;
	unsigned long timer_interval; /* jiffies */
	struct work_struct work;

	spinlock_t spinlock;
	struct mutex mutex;

	enum lx_te_input_port port;

	enum te_reg_atsc3_layer layer;
	enum te_reg_dumper_mode mode;
	struct te_hwbuf *data;
	struct te_hwbuf *meta;
	struct te_ringbuf rbuf; /* use in process_lgc_stream */
	u8 *lgc_buf;
	u32 lgc_buf_size;

	u32 warn_bufsize; /* display warning msg over this size */
	u32 warn_interval;
	u32 warn_time;
};

enum atsc3_debug_status {
	ATSC3_DEBUG_STATUS_FILTER = 0,
	ATSC3_DEBUG_STATUS_MCU_FILTER,
	ATSC3_DEBUG_STATUS_INPUT,
	ATSC3_DEBUG_STATUS_CLOCK,
	ATSC3_DEBUG_STATUS_DUMP,
	ATSC3_DEBUG_STATUS_MAX,
};

typedef int (*atsc3_debug_show_t)(struct atsc3_device *dev, struct seq_file *m);

struct atsc3_dev_debug {
	struct te_debug_dir *dir;
	atsc3_debug_show_t show_status[ATSC3_DEBUG_STATUS_MAX];
};

struct atsc3_dev_filter {
	bool enable;

	u8 num_plpf;
	u8 num_linksignalf;
	u8 num_ipf;
	u8 num_udpf;

	struct te_mem_ctx *mem;

	struct linksignal_filter *linksignalf;
	struct ip_filter *ipf;
	struct udp_filter *udpf;

	struct te_msgbuf callback_buf;
	struct work_struct callback_work;	/* worker for filter */
};

struct atsc3_data {
	bool start;
	u8 found_sync;
	struct mutex mutex;
	struct te_msgbuf msgbuf;
	u64 last_read_time;
};

struct atsc3_stats {
	u32 overflow_count;
	u32 pkt_count;
	u32 err_pkt_count;
	u32 time_pkt_count;
	u64 total_pkt_len;
};

struct atsc3_channel {
	u8 num;
	int users;
	struct atsc3_device *dev;	/* device */

	spinlock_t spinlock;

	struct atsc3_filter_channel filter;
	struct atsc3_data data;

	enum lx_atsc3_demod_type demod_type;
	u8 lgc_hdr_size;
	bool skip_timepkt;

	enum lx_te_input_port input_port;
	struct atsc3_input_monitor monitor;
	struct atsc3_input_dump dump;
	struct atsc3_clock *clock;
	struct atsc3_stats stats;

	char debug_name[8];
	struct te_debug_dir *debug_dir;
};

struct atsc3_device {
	struct mutex mutex;

	struct cdev cdev;
	int users;

	struct atsc3_config *cfg;
	struct atsc3_dev_message msg;

	struct atsc3_dev_filter filter;
	struct te_timer *monitor_timer;

	struct atsc3_dev_debug debug;

	struct te_subdev subdev;

	u8 num_channel;
	struct atsc3_channel channels[0];
};

/* file handle for atsc3 driver */
struct atsc3_dump_fh {
	struct te_hwbuf data;
	struct te_hwbuf meta;
	struct atsc3_input_dump *dump;
};

struct atsc3_fh {
	struct atsc3_device *dev;
	struct atsc3_channel *channel;
	struct atsc3_channel *fixup_channel;
	struct atsc3_dump_fh *dump;
	struct te_mem_ctx *mem;
};

struct atsc3_ioctl_info {
	unsigned int cmd;
	int (*func)(struct atsc3_fh *fh, void *arg);
	const char *name;
	bool dev_node;		/* no need channel instance */
	bool no_lock;
};

struct atsc3_ioctl {
	char magic;
	te_ioctl_func_t func;
	te_ioctl_param_func_t get_user_param;
};

struct atsc3_sub_driver {
	const char *name;

	int (*early_init)(struct atsc3_device *dev);
	int (*init)(struct atsc3_device *dev);
	void (*release)(struct atsc3_device *dev);

	int (*suspend)(struct atsc3_device *dev);
	int (*resume)(struct atsc3_device *dev);

	int (*open)(struct atsc3_fh *fh);
	void (*close)(struct atsc3_fh *fh);
	const struct atsc3_ioctl *ioctl;
};

/*------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *----------------------------------------------------------------------------*/

/* CFG */
void atsc3_cfg_init(void);

/* CORE */
int atsc3_device_init(struct atsc3_device *dev);
void atsc3_device_release(struct atsc3_device *dev);
int atsc3_device_suspend(struct atsc3_device *dev);
int atsc3_device_resume(struct atsc3_device *dev);

extern struct file_operations atsc3_dev_fops;

int atsc3_add_message(struct atsc3_device *dev, LX_ATSC3_MSG_T *msg);
int atsc3_add_msg_status(struct atsc3_device *dev, LX_ATSC3_MSG_TYPE_T type,
			 u16 idx, u32 status);

/* IO */
int atsc3_io_irq_handler(struct atsc3_device *dev, u32 val);

/* FILTER */

/* ISR */

/* CLOCK */
int atsc3_clock_irq_handler(struct atsc3_device *dev, u32 val);

/* MM */

/* DEBUG */
int atsc3_debug_init(struct atsc3_device *dev);
void atsc3_debug_release(struct atsc3_device *dev);
int atsc3_debug_register_status_show(struct atsc3_device *dev,
				     enum atsc3_debug_status status,
				     atsc3_debug_show_t show);

#define te_subdev_to_atsc3_device(sd) \
  container_of(sd, struct atsc3_device, subdev)

#define get_te_device(dev)	(dev->subdev.tdev)

#define atsc3_do_ioctl(priv, cmd, arg, mtx, ioctls) \
  te_do_ioctl(atsc3, priv, cmd, arg, mtx, ioctls)

extern int g_atsc3_debug_fd;

extern const struct atsc3_sub_driver atsc3_debug_driver;
extern const struct atsc3_sub_driver atsc3_mem_driver;
extern const struct atsc3_sub_driver atsc3_isr_driver;
extern const struct atsc3_sub_driver atsc3_io_driver;
extern const struct atsc3_sub_driver atsc3_clock_driver;
extern const struct atsc3_sub_driver atsc3_filter_driver;

#endif				/* _ATSC3_IMPL_H_ */
