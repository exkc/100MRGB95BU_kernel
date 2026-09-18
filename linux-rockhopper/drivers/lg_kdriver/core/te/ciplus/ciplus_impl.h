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
 *  TE(Transport Engine) CIPLUS Driver
 *
 *  @author	Ilkyu KIm (ilkyu.kim@lge.com)
 *  @version	0.1
 *  @date		2015-07-06
 *  @note		Additional information.
 */

#ifndef _CIPLUS_IMPL_H_
#define _CIPLUS_IMPL_H_

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/slab.h>		//alloc
#include <linux/poll.h>		//poll function
#include <linux/freezer.h>
#include <linux/delay.h>
#include <linux/cdev.h>

#include <lg1k/te/te.h>
#include <lg1k/te/util.h>
#include <lg1k/te/reg.h>
#include <lg1k/te/debug.h>
#include <lg1k/te/buffer.h>
#include <lg1k/te/mem.h>
#include <lg1k/te/ciplus.h>
#include <lg1k/te/dump.h>

#include "logm_kapi.h"

#include "te_ciplus_kapi.h"

#include "ciplus_cfg.h"

#define	CIPLUS_MODULE		"ciplus"
#define CIPLUS_DEVICE_NAME	"lg1k-ciplus"

#define CIPLUS_MEM_NAME		TE_MEM_SHARED_NAME

#define TP_SYNCBYTE		0x47
#define PACKET_SIZE		188

#define LOG_LEVEL_ERROR		LX_LOGM_LEVEL_ERROR	/* 0 */
#define LOG_LEVEL_WARNING	LX_LOGM_LEVEL_WARNING	/* 1 */
#define LOG_LEVEL_NOTI		LX_LOGM_LEVEL_NOTI	/* 2 */
#define LOG_LEVEL_INFO		LX_LOGM_LEVEL_INFO	/* 3 */
#define LOG_LEVEL_DEBUG		LX_LOGM_LEVEL_DEBUG	/* 4 */
#define LOG_LEVEL_TRACE		LX_LOGM_LEVEL_TRACE	/* 5 */
#define LOG_LEVEL_BITRATE	LX_LOGM_LEVEL_TRACE + 1	/* 6 */
#define LOG_LEVEL_DEVICE	LX_LOGM_LEVEL_TRACE + 2

#define CIPLUS_LOG(type,fmt,args...) \
	LOGM_PRINT(g_ciplus_debug_fd, (LOG_LEVEL_##type), fmt, ##args)

#define log_error(fmt,args...)			CIPLUS_LOG(ERROR,fmt,##args)
#define log_warning(fmt,args...)		CIPLUS_LOG(WARNING,fmt,##args)
#define log_noti(fmt,args...)			CIPLUS_LOG(NOTI,fmt,##args)
#define log_info(fmt,args...)			CIPLUS_LOG(INFO,fmt,##args)
#define log_debug(fmt,args...)			CIPLUS_LOG(DEBUG,fmt,##args)
#define log_trace(fmt,args...)			CIPLUS_LOG(TRACE,fmt,##args)
#define log_bitrate(fmt,args...)		CIPLUS_LOG(BITRATE,fmt,##args)
#define log_device(fmt,args...)			CIPLUS_LOG(DEVICE,fmt,##args)

#define CHECK_ERROR(__checker,__if_action,fmt,args...)   \
	TE_CHECK_IF_ERROR(__checker, log_error, __if_action , fmt, ##args )

#define CHECK_NULL_PARAM(param,__null_action)		\
	CHECK_ERROR((param) == NULL, __null_action,	\
		   "parameter(" #param ") is null")

#define CHECK_PARAM(__checker,fmt,args...)		\
	CHECK_ERROR(__checker, return -EINVAL,		\
		   "invalid parameter : " fmt, ##args)

struct ciplus_device;
struct ciplus_pidf;

struct ciplus_inbuf_cfg {
	enum te_reg_cip_src src;
	u8 flevel;
	bool pid_bypass;
	enum te_dump_layer layer;

	bool teifilter;
};

struct ciplus_demux_cfg {
	u8 num;
	enum te_reg_cip_dmx_dest dest;
};

struct ciplus_ipd_dev {
	u8 state;
	u8 ch;
	u8 syncbyte;

	spinlock_t spinlock;
	struct mutex mutex;

	struct te_hwbuf *buf;
	struct delayed_work work;
};

struct ciplus_input_monitor {
	struct te_timer *timer;
	u32 last_pkt;
	u32 last_time;
	u32 bitrate;
	bool use_pktcnt;
};

enum ciplus_debug_status {
	CIPLUS_DEBUG_STATUS_BITRATE,
	CIPLUS_DEBUG_STATUS_KDRV,
	CIPLUS_DEBUG_STATUS_MCU,
	CIPLUS_DEBUG_STATUS_MAX,
};

typedef int (*ciplus_debug_show_t)(struct ciplus_device *dev,
				   struct seq_file *m);

struct ciplus_debug {
	struct te_debug_dir *dir;
	ciplus_debug_show_t show_status[CIPLUS_DEBUG_STATUS_MAX];
};

struct ciplus_input_param {
	enum lx_te_input_port port;
	bool ip_play;
	bool en;
};

struct ciplus_channel {
	u8 num;
	bool en;
	u8 syncbyte;
	u8 sync_en;

	u8 tpi;

	int users;

	struct ciplus_inbuf_cfg inbuf;
	bool host_player;

	struct ciplus_device *dev;

	struct list_head callback_head;
	spinlock_t callback_lock;
	struct work_struct callback_work;	/* worker for ipd callback */

	struct ciplus_ipd_dev up_dev;
	struct ciplus_ipd_dev dn_dev;

	u32 num_pidf;
	struct ciplus_pidf *pidf;

	struct ciplus_input_param io_param;
};

struct ciplus_device {
	struct mutex mutex;

	struct cdev cdev;
	int users;

	struct te_mem_ctx *mem;

	struct ciplus_config *cfg;
	struct ciplus_debug debug;
	struct ciplus_input_monitor input_monitor;

	struct te_subdev subdev;

	bool debug_mode;

	u8 num_channel;
	struct ciplus_channel channels[0];
};

/* file handle for ciplus driver */
struct ciplus_dump_fh {
	struct te_hwbuf buf;
	struct ciplus_ipd_dev *dev;
};

struct ciplus_upload_fh {
	struct te_hwbuf buf;
	struct ciplus_ipd_dev *dev;
};

struct ciplus_fh {
	struct ciplus_device *dev;
	struct ciplus_channel *channel;
	struct ciplus_dump_fh *dump;
	struct ciplus_upload_fh *upload;
	struct te_mem_ctx *mem;
};

struct ciplus_ioctl_info {
	unsigned int cmd;
	int (*func)(struct ciplus_fh *fh, void *arg);
	const char *name;
	bool dev_node;		/* no need channel instance */
	bool no_lock;
};


struct ciplus_ioctl {
	char magic;
	te_ioctl_func_t func;
	te_ioctl_param_func_t get_user_param;
};

struct ciplus_sub_driver {
	const char *name;

	int (*early_init)(struct ciplus_device *dev);
	int (*init)(struct ciplus_device *dev);
	void (*release)(struct ciplus_device *dev);

	int (*suspend)(struct ciplus_device *dev);
	int (*resume)(struct ciplus_device *dev);

	int (*open)(struct ciplus_fh *fh);
	void (*close)(struct ciplus_fh *fh);
	const struct ciplus_ioctl *ioctl;
};

/* CFG */
void ciplus_cfg_init(void);

/* CORE */
int ciplus_device_init(struct ciplus_device *dev);
void ciplus_device_release(struct ciplus_device *dev);
int ciplus_device_suspend(struct ciplus_device *dev);
int ciplus_device_resume(struct ciplus_device *dev);

extern struct file_operations ciplus_dev_fops;

/* IO Function */

/* PIDF Function */
int ciplus_pidf_show_status(struct ciplus_channel *channel, struct seq_file *m);
void ciplus_pidf_enable_bypass(struct ciplus_channel *channel, bool en);

/* MM Function */

/* IPD Function */
ssize_t ciplus_ipd_ioc_read(struct file *file, char __user *data, size_t size,
			    loff_t *off);
ssize_t ciplus_ipd_ioc_write(struct file *file, const char __user *data,
			     size_t size, loff_t *off);
unsigned int ciplus_ipd_ioc_poll(struct file *file, poll_table * wait);

/* DEBUG */
int ciplus_debug_register_status_show(struct ciplus_device *dev,
				      enum ciplus_debug_status status,
				      ciplus_debug_show_t show);

#define te_subdev_to_ciplus_device(sd)			\
	container_of(sd, struct ciplus_device, subdev)

#define get_te_device(dev)		(dev->subdev.tdev)

#define ciplus_do_ioctl(priv, cmd, arg, mtx, ioctls)	\
	te_do_ioctl(ciplus, priv, cmd, arg, mtx, ioctls)

extern int g_ciplus_debug_fd;

extern const struct ciplus_sub_driver ciplus_debug_driver;
extern const struct ciplus_sub_driver ciplus_mem_driver;
extern const struct ciplus_sub_driver ciplus_io_driver;
extern const struct ciplus_sub_driver ciplus_pidf_driver;
extern const struct ciplus_sub_driver ciplus_ipd_driver;
extern const struct ciplus_sub_driver ciplus_isr_driver;

#endif				/* _CIPLUS_IMPL_H_ */

/** @} */
