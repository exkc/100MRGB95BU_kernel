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
 *  arib2 driver
 *
 *  @author		Yeonju Lee(yeonju.lee@lge.com)
 *  @version		1.0
 *  @date		2017-11-21
 *  @note		Additional information.
 */

#ifndef _ARIB2_IMPL_H_
#define _ARIB2_IMPL_H_

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/vmalloc.h>
#include <linux/poll.h>
#include <linux/freezer.h>
#include <linux/delay.h>

#include <lg1k/te/te.h>
#include <lg1k/te/util.h>
#include <lg1k/te/reg.h>
#include <lg1k/te/debug.h>
#include <lg1k/te/buffer.h>
#include <lg1k/te/dump.h>
#include <lg1k/te/mem.h>
#include <lg1k/te/arib2.h>

#include "logm_kapi.h"
#include "te_arib2_kapi.h"

#include "arib2_cfg.h"

#define	ARIB2_MODULE		"arib2"
#define ARIB2_DEVICE_NAME	"lg1k-arib2"
#define ARIB2_MEM_NAME		TE_MEM_SHARED_NAME

//#define USE_ARIB2_HW_FILTER

#define LOG_LEVEL_ERROR		LX_LOGM_LEVEL_ERROR	/* 0 */
#define LOG_LEVEL_WARNING	LX_LOGM_LEVEL_WARNING	/* 1 */
#define LOG_LEVEL_NOTI		LX_LOGM_LEVEL_NOTI	/* 2 */
#define LOG_LEVEL_INFO		LX_LOGM_LEVEL_INFO	/* 3 */
#define LOG_LEVEL_DEBUG		LX_LOGM_LEVEL_DEBUG	/* 4 */
#define LOG_LEVEL_TRACE		LX_LOGM_LEVEL_TRACE	/* 5 */
#define LOG_LEVEL_TRACE_EX	LX_LOGM_LEVEL_TRACE + 1	/* 6 */
#define LOG_LEVEL_FILTER	LX_LOGM_LEVEL_TRACE + 2 /* 7 */
#define LOG_LEVEL_IO		LX_LOGM_LEVEL_TRACE + 3	/* 8 */
#define LOG_LEVEL_CLOCK		LX_LOGM_LEVEL_TRACE + 4 /* 9 */
#define LOG_LEVEL_DEVICE	LX_LOGM_LEVEL_TRACE + 5 /* 10 */

#define LOG_LEVEL_TIMEINFO	LX_LOGM_LEVEL_TRACE + 8 /* 13 */

#define ARIB2_LOG(type,fmt,args...) \
	LOGM_PRINT( g_arib2_debug_fd, LOG_LEVEL_##type, fmt, ##args)

#define log_error(fmt,args...)			ARIB2_LOG(ERROR,fmt,##args)
#define log_warning(fmt,args...)		ARIB2_LOG(WARNING,fmt,##args)
#define log_noti(fmt,args...)			ARIB2_LOG(NOTI,fmt,##args)
#define log_info(fmt,args...)			ARIB2_LOG(INFO,fmt,##args)
#define log_debug(fmt,args...)			ARIB2_LOG(DEBUG,fmt,##args)
#define log_trace(fmt,args...)			ARIB2_LOG(TRACE,fmt,##args)
#define log_trace_ex(fmt,args...)		ARIB2_LOG(TRACE_EX,fmt,##args)
#define log_filter(fmt,args...)			ARIB2_LOG(FILTER,fmt,##args)
#define log_io(fmt,args...)			ARIB2_LOG(IO,fmt,##args)
#define log_clock(fmt,args...)			ARIB2_LOG(CLOCK,fmt,##args)
#define log_timeinfo(fmt,args...)		ARIB2_LOG(TIMEINFO,fmt,##args)
#define log_device(fmt,args...)			ARIB2_LOG(DEVICE,fmt,##args)

#define FUNC_TRACE_ENTER()			log_trace("<--%s", __func__)
#define FUNC_TRACE_EXIT()			log_trace("-->%s", __func__)

#define FUNC_TRACE_EX_ENTER()			log_trace_ex("<--%s", __func__)
#define FUNC_TRACE_EX_EXIT()			log_trace_ex("-->%s", __func__)

#define CHECK_ERROR(__checker,__if_action,fmt,args...)   \
  TE_CHECK_IF_ERROR(__checker, log_error, __if_action , fmt, ##args )

#define CHECK_NULL_PARAM(param) \
  CHECK_ERROR((param) == NULL, return -EINVAL, "parameter(" #param ") is null")

#define CHECK_PARAM(__checker,fmt,args...) \
  CHECK_ERROR(__checker, return -EINVAL, "invalid parameter : " fmt, ##args)

/*------------------------------------------------------------------------------
 *   Type Definitions
 *----------------------------------------------------------------------------*/

struct arib2_device;
struct arib2_clock;

struct arib2_notifier {
	struct mutex lock;
	wait_queue_head_t wq;

	LX_ARIB2_NOTIFY_DATA_T param[LX_ARIB2_MAX_NOTIFY_DATA];
	volatile u32 widx;
	volatile u32 ridx;

	/* for summary */
	u32 peak_count;
	u32 total_count;
};

struct arib2_data_stat {
	u64 total_length;
	u32 packet_count;
	u32 err_packet_count;
	u32 overflow_count;
};

struct arib2_data {
	struct te_pktbuf pbuf;
	u8 *buf;		/* packet data */
	bool start;
	struct mutex mutex;	/* start lock, protect buf */

	u32 warn_bufsize;
	u32 warn_interval;	/* ms unit interval of showing message */
	u32 warn_time;		/* last displayed time */

	u64 last_read_time;
	struct arib2_data_stat stat;

	u32 timeout;
};

struct arib2_channel_filter {
	struct list_head tlv_si_head;	/* TLV SI filter list header */
	struct list_head mmt_pid_head;	/* MMT_PID filter list header */
	struct list_head mmt_si_head;	/* MMT_SI filter list header */
	struct list_head mmt_av_head;	/* MMT_AV filter list header */

	struct list_head callback_head;
	spinlock_t callback_lock;
	struct work_struct callback_work;	/* worker for filter */

	u8 tlv_si_req_num;
	//u8 mmt_pid_req_num;
	u8 mmt_si_req_num;
	u8 mmt_av_req_num;
};

struct arib2_input_monitor {
	char name[32];
	bool enable;
	bool ready;		/* TRUE : after getting 1st status */
	bool no_input;
	u32 message_count;	/* To disable verbose message */
	u32 pkt_count;		/* all tlv packets including err_pkt */
	u32 err_pkt_count;	/* tlv sync lost or length error */
	u32 overflow_count;	/* packet buffer overflow count */
};

enum arib2_dump_state {
	INPUT_DUMP_STATE_IDLE = 0,
	INPUT_DUMP_STATE_RUNNING,
	INPUT_DUMP_STATE_SUSPEND,
};

struct arib2_input_dump {
	volatile enum arib2_dump_state state;
	u8 ch;
	u32 flags;		/* WAIT_MODE, CHECK_OVERFLOW */
	u32 intr;
	enum te_reg_dumper_mode mode;

	struct timer_list timer;
	unsigned long timer_interval; /* jiffies */
	struct work_struct work;

	spinlock_t spinlock;

	char hma_name[16];

	struct te_hwbuf *data;
	struct te_hwbuf *meta;

	u32 warning_size;	/* display warning msg under this size */
	u32 warn_interval;
	u32 warn_time;		/* last displayed time */
};

/* swtlv */
struct swtlv_input_dump {
	u8 ch;			/* sdec dump ch */

	u8 mcu;
	u8 pid_bypass;

	struct te_hwbuf hbuf;	/* ts dump buffer */

	u32 warning_size;	/* display warning msg under this size */
	u32 warn_interval;
	u32 warn_time;		/* last displayed time */
};

enum swtlv_status {
	SWTLV_STATUS_IDLE,
	SWTLV_STATUS_RUNNING,
	SWTLV_STATUS_SUSPEND,
};

typedef int (*swtlv_cb_func_t)(void *arg, u32 timestamp, void *data, u32 len);

struct swtlv_callback {
	swtlv_cb_func_t func;
	void *arg;
	struct mutex mutex;
};

struct arib2_swtlv {
	enum swtlv_status status;
	u8 find_cnt;		/* 0 ~ NUM_OF_SYNC_CHECK */
	u8 sync;
	struct work_struct work;	/* swtlv_data_callback_work */
	spinlock_t spinlock;	/* workqueue lock */
	/* sdec buffer position */
	u8 sync_offset;		/* sync offset in a packet(192) */
	u16 tlv_size;		/* packet payload size */
	u8 next_sync_offset;
	struct swtlv_input_dump dump;
	u8 *pkt_buf;

	struct arib2_data *data;	/* tlv packet data */
	struct swtlv_callback callback;
};

struct arib2_debug_dump {
	enum te_dump_mode mode;
	bool running;
	struct arib2_input_dump *dev;	/* for stop input dump */
	struct te_hwbuf *buf;
};

enum arib2_debug_status {
	ARIB2_DEBUG_STATUS_INPUT = 0,
	ARIB2_DEBUG_STATUS_CLOCK,
	ARIB2_DEBUG_STATUS_DUMP,
	ARIB2_DEBUG_STATUS_MAX,
};

typedef int (*arib2_debug_show_t)(struct arib2_device *dev, struct seq_file *m);

struct arib2_dev_debug {
	struct te_debug_dir *dir;
	arib2_debug_show_t show_status[ARIB2_DEBUG_STATUS_MAX];
};

struct arib2_channel {
	u8 num;

	int users;
	struct arib2_device *dev;

	spinlock_t spinlock;

	LX_TE_INPUT_PORT_T input_port;

	struct arib2_channel_filter filter;
	struct arib2_data data;

	struct arib2_clock *clock;

	union {
		struct arib2_swtlv swtlv;
		struct arib2_input_dump dump;
	};

	struct arib2_input_monitor monitor;
	struct arib2_debug_dump debug_dump[TE_DUMP_MODE_MAX];

	char debug_name[8];
	struct te_debug_dir *debug_dir;
};

struct arib2_device {
	struct mutex mutex;

	struct cdev cdev;
	int users;

	struct arib2_config *cfg;
	struct arib2_notifier *noti;	//noti structure for callback send

	struct arib2_dev_debug debug;

	struct te_timer *monitor_timer;

	struct te_subdev subdev;

	bool use_swtlv;
	u8 num_channel;
	struct arib2_channel channels[0];
};

/* file handle for arib2 driver */
struct arib2_dump_fh {
	struct te_hwbuf data;
	struct te_hwbuf meta;
	union {
		struct arib2_swtlv *swtlv;
		struct arib2_input_dump *input_dump;
	};
};

struct arib2_fh {
	struct arib2_device *dev;
	struct arib2_channel *channel;
	struct arib2_dump_fh *dump;
	struct te_mem_ctx *mem;
};

struct arib2_ioctl_info {
	unsigned int cmd;
	int (*func)(struct arib2_fh *fh, void *arg);
	const char *name;
	bool dev_node;		/* no need channel instance */
	bool no_lock;
};

struct arib2_ioctl {
	char magic;
	te_ioctl_func_t func;
	te_ioctl_param_func_t get_user_param;
};

struct arib2_sub_driver {
	const char *name;

	int (*early_init)(struct arib2_device *dev);
	int (*init)(struct arib2_device *dev);
	void (*release)(struct arib2_device *dev);

	int (*suspend)(struct arib2_device *dev);
	int (*resume)(struct arib2_device *dev);

	/* file operations */
	int (*open)(struct arib2_fh *fh);
	void (*close)(struct arib2_fh *fh);
	const struct arib2_ioctl *ioctl;
};

/* CFG */
void arib2_cfg_init(void);

/* CORE */
int arib2_dev_init(struct arib2_device *dev);
void arib2_dev_release(struct arib2_device *dev);
int arib2_dev_suspend(struct arib2_device *dev);
int arib2_dev_resume(struct arib2_device *dev);

extern struct file_operations arib2_dev_fops;

#ifdef USE_ARIB2_HW_FILTER
int arib2_add_noti(struct arib2_device *dev, LX_ARIB2_NOTIFY_DATA_T *data);
int arib2_add_noti_status(struct arib2_device *dev, LX_ARIB2_NOTIFY_TYPE_T type,
			  u8 idx, u32 status);
#else
static inline int arib2_add_noti(struct arib2_device *dev,
				 LX_ARIB2_NOTIFY_DATA_T *data)
{
	return 0;
}

static inline int arib2_add_noti_status(struct arib2_device *dev,
					LX_ARIB2_NOTIFY_TYPE_T type,
					u8 idx, u32 status)
{
	return 0;
}
#endif

/* CLOCK */
int arib2_clock_irq_handler(struct arib2_device *dev, u32 val);

/* FILTER */

/* IO */
void arib2_io_irq_handler(struct arib2_device *dev, u32 val);

void arib2_swtlv_register_data_callback(struct arib2_channel *channel,
					swtlv_cb_func_t func, void *arg);

void arib2_debug_user_read_callback(struct arib2_channel *channel,
				    void __user *data, u32 size);

/* ISR */

/* DEBUG */
int arib2_debug_register_status_show(struct arib2_device *dev,
				     enum arib2_debug_status status,
				     arib2_debug_show_t show);

#define te_subdev_to_arib2_device(sd) \
	container_of(sd, struct arib2_device, subdev)

#define get_te_device(dev)		(dev->subdev.tdev)

#define arib2_do_ioctl(priv,cmd,arg,mtx,ioctls) \
	te_do_ioctl(arib2, priv, cmd, arg, mtx, ioctls)

extern int g_arib2_debug_fd;

extern const struct arib2_sub_driver arib2_debug_driver;
extern const struct arib2_sub_driver arib2_mem_driver;
extern const struct arib2_sub_driver arib2_io_driver;
extern const struct arib2_sub_driver arib2_clock_driver;
extern const struct arib2_sub_driver arib2_filter_driver;
extern const struct arib2_sub_driver arib2_isr_driver;

#endif				/* _ARIB2_IMPL_H_ */
