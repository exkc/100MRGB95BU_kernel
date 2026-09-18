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
 *  @author	Kyungseok Hyun (ks.hyun@lge.com)
 *  @version	1.0
 *  @date	2014-04-08
 *  @note	Additional information.
 */

#ifndef _SDEC_IMPL_H_
#define _SDEC_IMPL_H_

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

#include <lg1k/te/util.h>
#include <lg1k/te/reg.h>
#include <lg1k/te/debug.h>
#include <lg1k/te/buffer.h>
#include <lg1k/te/mem.h>
#include <lg1k/te/sdec.h>
#include <lg1k/te/dump.h>

#include "logm_kapi.h"
#include "te_sdec_kapi.h"

#include "sdec_cfg.h"

#define	SDEC_MODULE		"sdec"
#define SDEC_DEVICE_NAME	"lg1k-sdec"

#define MAX_PID_FILTER		256
#define MAX_SUB_PID_FILTER	2
#define MAX_STREAM_FILTER	256
#define MAX_INPUT_DUMP		2

#define LOG_LEVEL_ERROR		LX_LOGM_LEVEL_ERROR	/* 0 */
#define LOG_LEVEL_WARNING	LX_LOGM_LEVEL_WARNING	/* 1 */
#define LOG_LEVEL_NOTI		LX_LOGM_LEVEL_NOTI	/* 2 */
#define LOG_LEVEL_INFO		LX_LOGM_LEVEL_INFO	/* 3 */
#define LOG_LEVEL_DEBUG		LX_LOGM_LEVEL_DEBUG	/* 4 */
#define LOG_LEVEL_TRACE		LX_LOGM_LEVEL_TRACE	/* 5 */
#define LOG_LEVEL_TRACE_EX	LX_LOGM_LEVEL_TRACE + 1 /* 6 */
#define LOG_LEVEL_NORMAL	LX_LOGM_LEVEL_TRACE + 2 /* 7 */
#define LOG_LEVEL_READ		LX_LOGM_LEVEL_TRACE + 3 /* 8 */
#define LOG_LEVEL_ISR		LX_LOGM_LEVEL_TRACE + 4 /* 9 */
#define LOG_LEVEL_IO		LX_LOGM_LEVEL_TRACE + 5 /* 10 */
#define LOG_LEVEL_FILTER	LX_LOGM_LEVEL_TRACE + 6 /* 11 */
#define LOG_LEVEL_DESC		LX_LOGM_LEVEL_TRACE + 7 /* 12 */
#define LOG_LEVEL_PCR		LX_LOGM_LEVEL_TRACE + 8 /* 13 */
#define LOG_LEVEL_MM		LX_LOGM_LEVEL_TRACE + 9 /* 14 */
#define LOG_LEVEL_CLOCK		LX_LOGM_LEVEL_TRACE + 10
#define LOG_LEVEL_DVB_DEMUX	LX_LOGM_LEVEL_TRACE + 11
#define LOG_LEVEL_DEVICE	LX_LOGM_LEVEL_TRACE + 12
#define LOG_LEVEL_TEMI		LX_LOGM_LEVEL_TRACE + 13

#define SDEC_LOG(type,fmt,args...) \
 LOGM_PRINT( g_sdec_debug_fd, (LOG_LEVEL_##type), fmt, ##args)

#define log_error(fmt,args...)		SDEC_LOG(ERROR,fmt,##args)
#define log_warning(fmt,args...)	SDEC_LOG(WARNING,fmt,##args)
#define log_noti(fmt,args...)		SDEC_LOG(NOTI,fmt,##args)
#define log_info(fmt,args...)		SDEC_LOG(INFO,fmt,##args)
#define log_debug(fmt,args...)		SDEC_LOG(DEBUG,fmt,##args)
#define log_trace(fmt,args...)		SDEC_LOG(TRACE,fmt,##args)
#define log_trace_ex(fmt,args...)	SDEC_LOG(TRACE_EX,fmt,##args)
#define log_normal(fmt,args...)		SDEC_LOG(NORMAL,fmt,##args)
#define log_read(fmt,args...)		SDEC_LOG(READ,fmt,##args)
#define log_isr(fmt,args...)		SDEC_LOG(ISR,fmt,##args)
#define log_io(fmt,args...)		SDEC_LOG(IO,fmt,##args)
#define log_filter(fmt,args...)		SDEC_LOG(FILTER,fmt,##args)
#define log_pcr(fmt,args...)		SDEC_LOG(PCR,fmt,##args)
#define log_desc(fmt,args...)		SDEC_LOG(DESC,fmt,##args)
#define log_mm(fmt,args...)		SDEC_LOG(MM,fmt,##args)
#define log_clock(fmt,args...)		SDEC_LOG(CLOCK,fmt,##args)
#define log_dvb_demux(fmt,args...)	SDEC_LOG(DVB_DEMUX,fmt,##args)
#define log_device(fmt,args...)		SDEC_LOG(DEVICE,fmt,##args)
#define log_temi(fmt,args...)		SDEC_LOG(TEMI,fmt,##args)

#define FUNC_TRACE_ENTER()		log_trace("<--%s", __func__)
#define FUNC_TRACE_EXIT()		log_trace("-->%s", __func__)

#define FUNC_TRACE_EX_ENTER()		log_trace_ex("<--%s", __func__)
#define FUNC_TRACE_EX_EXIT()		log_trace_ex("-->%s", __func__)

#define CHECK_ERROR(__checker,__if_action,fmt,args...)   \
  TE_CHECK_IF_ERROR(__checker, log_error, __if_action , fmt, ##args )

#define CHECK_NULL_PARAM(param) \
  CHECK_ERROR(!(param), return -EINVAL, "parameter(" #param ") is null")

#define CHECK_PARAM(__checker,fmt,args...) \
  CHECK_ERROR(__checker, return -EINVAL, "invalid parameter : " fmt, ##args)

struct sdec_device;
struct sdec_channel;
struct sdec_clock;
struct sdec_pid_filter;
struct sdec_stream_filter;
struct sdec_temi_filter;
struct temi_dev;

struct sdec_key_data {
	u8 used;
	u8 data[32];
	u16 pidf_id;		/* pid filter id */
	u16 pid;		/* pid value */
	enum lx_sdec_desc_key_location loc;
};

struct sdec_desc {
	LX_SDEC_DESC_CONFIG_T cfg;

	struct sdec_key_data skey;
	struct sdec_key_data even_iv;
	struct sdec_key_data odd_iv;
};

enum sdec_filter_owner {
	FILTER_OWNER_USER = 0,
	FILTER_OWNER_KDRV,
	FILTER_OWNER_DEBUG,
};

struct sdec_tsh_filter {
	bool enabled;
	enum sdec_filter_owner owner;
	u16 pid;
	sdec_tsh_filter_callback_t callback;
	void *priv;
};

/* Backup data for InstantBoot */
struct sdec_data {
	struct te_reg_pidf_conf pidf[MAX_PID_FILTER];
	struct te_reg_pidf_conf sub_pidf[MAX_SUB_PID_FILTER];
	u8 sub_bypass[MAX_SUB_PID_FILTER];
};

struct sdec_dev_message {
	struct mutex mutex;
	struct te_msgbuf buf;
	u32 peak_count;
	u32 total_count;
	u32 overflow_count;	/* reset after resume */
	u32 overflow_total_count;
	u32 max_overflow_msg;	/* log off after this count */
};

enum sdec_dump_state {
	INPUT_DUMP_IDLE = 0,
	INPUT_DUMP_READY,
	INPUT_DUMP_RUNNING,
};


#define SDEC_DUMP_FLAG_IGNORE_WARNING	(0x1 << 0)
#define SDEC_DUMP_FLAG_AUTO_PTR_UPDATE	(0x1 << 1)

struct sdec_dump_cfg {
	bool pid_bypass;
	enum te_dump_layer layer;
	struct te_hwbuf *buf;
	enum lx_te_input_port port;
	LX_SDEC_DUMP_TIMESRC_T clk_src;
	LX_SDEC_DUMP_TIMERES_T clk_res;
	u32 flags;
};

struct sdec_input_dump {
	enum sdec_dump_state state;		/* IDLE or RUNNING */

	bool pid_bypass;
	enum te_dump_layer layer;
	u32 flags;		/* WAIT_MODE, CHECK_OVERFLOW */

	struct mutex mutex;
	spinlock_t spinlock;

	struct sdec_channel *channel;
	enum lx_te_input_port port;
	enum lx_te_input_port org_port;

	struct te_hwbuf *buf;
	phys_addr_t wptr;	/* save last wptr to check buffer updated */

	u32 warning_size;	/* display warning msg over this size */
};

struct sdec_dev_io {
	enum lx_te_input_src ci_src;
	enum te_reg_input_mux mux;
	struct sdec_input_dump input_dump[MAX_INPUT_DUMP];
};

struct sdec_dev_filter {
	u8 num_sub_channel;
	u16 num_pidf;
	u16 num_streamf;

	struct sdec_pid_filter *pidf;
	struct sdec_stream_filter *streamf;

	/* callback */
	struct te_msgbuf callback_buf;
	struct work_struct callback_work;	/* worker for filter */
	u32 callback_min_free;
	u32 callback_errors;
};

struct sdec_dev_temi {
	u16 num_dev;	/* num of mcu filters */
	u16 num_filter;	/* s/w filters */

	struct te_mem_ctx *mem;
	struct temi_dev *dev;
	struct sdec_temi_filter *filter;
};

struct sdec_dev_senddata {
	struct completion completion;
	spinlock_t spinlock;
	void *data; // destination for enc/dec area
	u32 size;
};

struct sdec_filter_channel {
	struct list_head pid_list;	/* pid filter list head */
	struct list_head stream_list;	/* stream filter list head */
	struct sdec_tsh_filter ts_header;
};

struct sdec_temi_channel {
	struct list_head dev_list;
	struct list_head filter_list;
	u8 seq_num;
};

struct sdec_channel_monitor {
	struct delayed_work work;
	char name[32];
	struct mutex mutex;	/* protect enable_mask */
	bool enable;
	u32 enable_mask;
	u32 intr;
	u32 interval;		/* msec */
	bool no_input;
	u32 message_count;
	u32 pkt_count;
	u32 err_count;
	u32 ovf_count;
};

enum sdec_debug_status {
	SDEC_DEBUG_STATUS_PID_FILTER = 0,
	SDEC_DEBUG_STATUS_STREAM_FILTER,
	SDEC_DEBUG_STATUS_MCU_FILTER,
	SDEC_DEBUG_STATUS_TEMI,
	SDEC_DEBUG_STATUS_INPUT,
	SDEC_DEBUG_STATUS_PCR_RECOVERY,
	SDEC_DEBUG_STATUS_NOTI,
	SDEC_DEBUG_STATUS_MAX,
};

typedef int (*sdec_debug_show_t)(struct sdec_device *dev, struct seq_file *m);

struct sdec_dev_debug {
	struct te_debug_dir *dir;
	sdec_debug_show_t show_status[SDEC_DEBUG_STATUS_MAX];
};

struct sdec_channel {
	u8 num;
	int users;

	struct sdec_device *dev;
	struct sdec_channel_info *info;

	struct sdec_filter_channel filter;
	struct sdec_temi_channel temi;
	struct sdec_desc desc;

	struct sdec_clock *clk;
	enum lx_te_input_port input_port;

	struct sdec_channel_monitor monitor;
	char debug_name[8];
	struct te_debug_dir *debug_dir;
};

struct sdec_device {
	struct mutex mutex;

	struct cdev cdev;
	int users;

	struct sdec_config *cfg;
	struct sdec_data *data;

	struct sdec_dev_message msg;
	struct sdec_dev_io io;
	struct sdec_dev_filter filter;
	struct sdec_dev_temi temi;

	struct sdec_dev_senddata dsc_senddata;
	void *pmem; // temporal memory area for access CPU area

	struct sdec_dev_debug debug;
	struct te_subdev subdev;

	u8 num_channel;
	struct sdec_channel channels[0];
};

/* file handle for SDEC */
struct sdec_dump_fh {
	struct te_hwbuf buf;
	struct sdec_input_dump *dump;
};

struct sdec_fh {
	struct sdec_device *dev;
	struct sdec_channel *channel;	/* channel node */
	struct te_mem_ctx *mem;
	struct sdec_dump_fh *dump;
};

struct sdec_ioctl_info {
	unsigned int cmd;
	int (*func)(struct sdec_fh *fh, void *arg);
	const char *name;
	bool dev_node;		/* no need channel instance */
	bool no_lock;
};

struct sdec_ioctl {
	char magic;
	te_ioctl_func_t func;
	te_ioctl_param_func_t get_user_param;
};

struct sdec_sub_driver {
	const char *name;

	int (*early_init)(struct sdec_device *dev);
	int (*init)(struct sdec_device *dev);
	void (*release)(struct sdec_device *dev);

	int (*suspend)(struct sdec_device *dev);
	int (*resume)(struct sdec_device *dev);

	int (*open)(struct sdec_fh *fh);
	void (*close)(struct sdec_fh *fh);
	const struct sdec_ioctl *ioctl;
};

/* CFG */
void sdec_cfg_init(void);

/* DRV */

/* CORE */
int sdec_device_init(struct sdec_device *dev);
void sdec_device_release(struct sdec_device *dev);
int sdec_device_suspend(struct sdec_device *dev);
int sdec_device_resume(struct sdec_device *dev);

extern const struct file_operations sdec_dev_fops;

int sdec_add_message(struct sdec_device *dev, LX_SDEC_MSG_T *msg);
int sdec_add_filter_msg_status(struct sdec_device *dev, u16 idx, u32 status);

/* MM */

/* IO */
int sdec_io_irq_handler(struct sdec_channel *channel);
void sdec_io_set_monitor_mask(struct sdec_channel *channel, u32 dest_mask,
			      bool enable);

/* FILTER */

/* CLOCK */
int sdec_clock_irq_handler(struct sdec_channel *channel);

/* DESCRAMBLER */

/* ISR */

/* DEBUG */
int sdec_debug_register_status_show(struct sdec_device *dev,
				    enum sdec_debug_status status,
				    sdec_debug_show_t show);

#define te_subdev_to_sdec_device(sd) \
	container_of(sd, struct sdec_device, subdev)

#define get_te_device(dev)	((dev)->subdev.tdev)

#define sdec_do_ioctl(priv, cmd, arg, mtx, ioctls) \
	te_do_ioctl(sdec, priv, cmd, arg, mtx, ioctls)



extern int g_sdec_debug_fd;

extern const struct sdec_sub_driver sdec_debug_driver;
extern const struct sdec_sub_driver sdec_mem_driver;
extern const struct sdec_sub_driver sdec_clock_driver;
extern const struct sdec_sub_driver sdec_io_driver;
extern const struct sdec_sub_driver sdec_desc_driver;
extern const struct sdec_sub_driver sdec_filter_driver;
extern const struct sdec_sub_driver sdec_temi_driver;
extern const struct sdec_sub_driver sdec_isr_driver;

#endif
