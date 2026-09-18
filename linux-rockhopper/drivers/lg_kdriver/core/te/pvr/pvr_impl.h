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
 *  pvr driver
 *
 *  @author	Kyungseok Hyun (ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2014-04-08
 *  @note		Additional information.
 */

#ifndef _PVR_IMPL_H_
#define _PVR_IMPL_H_

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/kthread.h>
#include <asm/io.h>
#include <asm/uaccess.h>

#include <lg1k/te/util.h>
#include <lg1k/te/reg.h>
#include <lg1k/te/debug.h>
#include <lg1k/te/buffer.h>
#include <lg1k/te/pvr.h>

#include "logm_kapi.h"

#include "pvr_cfg.h"
#include "pvr_kapi.h"

#define	PVR_MODULE		"pvr"
#define PVR_DEVICE_NAME		"lg1k-pvr"
#define	PVR_MEM_NAME		PVR_MODULE

#define PVR_UP_MAX		2
#define PVR_DN_MAX		2

#define LOG_LEVEL_ERROR		LX_LOGM_LEVEL_ERROR	/* 0 */
#define LOG_LEVEL_WARNING	LX_LOGM_LEVEL_WARNING	/* 1 */
#define LOG_LEVEL_NOTI		LX_LOGM_LEVEL_NOTI	/* 2 */
#define LOG_LEVEL_INFO		LX_LOGM_LEVEL_INFO	/* 3 */
#define LOG_LEVEL_DEBUG		LX_LOGM_LEVEL_DEBUG	/* 4 */
#define LOG_LEVEL_TRACE		LX_LOGM_LEVEL_TRACE	/* 5 */
#define LOG_LEVEL_TRACE_EX	LX_LOGM_LEVEL_TRACE + 1 /* 6 */
#define LOG_LEVEL_DRV		LX_LOGM_LEVEL_TRACE + 2 /* 7 */
#define LOG_LEVEL_NORMAL	LX_LOGM_LEVEL_TRACE + 3 /* 8 */
#define LOG_LEVEL_ISR		LX_LOGM_LEVEL_TRACE + 4 /* 9 */
#define LOG_LEVEL_UPLOAD	LX_LOGM_LEVEL_TRACE + 5 /* 10 */
#define LOG_LEVEL_PIE		LX_LOGM_LEVEL_TRACE + 6 /* 11 */
#define LOG_LEVEL_REG		LX_LOGM_LEVEL_TRACE + 7 /* 12 */
#define LOG_LEVEL_REG_EX	LX_LOGM_LEVEL_TRACE + 8 /* 13 */
#define LOG_LEVEL_DEVICE	LX_LOGM_LEVEL_TRACE + 9 /* 14 */

#define PVR_LOG(type,fmt,args...) \
  LOGM_PRINT(g_pvr_debug_fd, (LOG_LEVEL_##type), fmt, ##args)
#define PVR_R_LOG(type,fmt,args...) \
  PVR_LOG(type, TE_COLOR_RED fmt TE_COLOR_NONE, ##args)
#define PVR_Y_LOG(type,fmt,args...) \
  PVR_LOG(type, TE_COLOR_RED fmt TE_COLOR_NONE, ##args)

#define log_error(fmt,args...)		PVR_R_LOG(ERROR,fmt,##args)
#define log_warning(fmt,args...)	PVR_Y_LOG(WARNING,fmt,##args)
#define log_noti(fmt,args...)		PVR_LOG(NOTI,fmt,##args)
#define log_info(fmt,args...)		PVR_LOG(INFO,fmt,##args)
#define log_debug(fmt,args...)		PVR_LOG(DEBUG,fmt,##args)
#define log_trace(fmt,args...)		PVR_LOG(TRACE,fmt,##args)
#define log_trace_ex(fmt,args...)	PVR_LOG(TRACE_EX,fmt,##args)
#define log_drv(fmt,args...)		PVR_LOG(DRV,fmt,##args)
#define log_normal(fmt,args...)		PVR_LOG(NORMAL,fmt,##args)
#define log_isr(fmt,args...)		PVR_LOG(ISR,fmt,##args)
#define log_upload(fmt,args...)		PVR_LOG(UPLOAD,fmt,##args)
#define log_pie(fmt,args...)		PVR_LOG(PIE,fmt,##args)
#define log_reg(fmt,args...)		PVR_LOG(REG,fmt,##args)
#define log_reg_ex(fmt,args...)		PVR_LOG(REG_EX,fmt,##args)
#define log_device(fmt,args...)		PVR_LOG(DEVICE,fmt,##args)

#define CHECK_ERROR(__checker,__if_action,fmt,args...)   \
  TE_CHECK_IF_ERROR(__checker, log_error, __if_action , fmt, ##args )

#define CHECK_PARAM(__checker,fmt,args...) \
  CHECK_ERROR(__checker, return -EINVAL, "invalid parameter : " fmt, ##args)

#define CHECK_NULL_PARAM(param) \
  CHECK_ERROR(!(param), return -EINVAL, "parameter(" #param ") is null")

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
struct pvr_device;
struct pvr_fh;

enum pvr_dev_type {
	PVR_DEV_TYPE_CORE = 0,
	PVR_DEV_TYPE_UP,
	PVR_DEV_TYPE_DN,
	PVR_DEV_TYPE_MAX,
};

struct pvr_buf_info {
	u32 base;
	u32 end;
	u32 size;
	u32 rptr;
	u32 wptr;
	LX_PVR_BUF_STAT_T status;
};

enum pvr_up_state {
	PVR_UP_STATE_FREE = 0,
	PVR_UP_STATE_IDLE,
	PVR_UP_STATE_READY,
	PVR_UP_STATE_PLAY,
	PVR_UP_STATE_PAUSE,
};

struct pvr_up_stats {
	u32 empty;
	u32 almost_empty;
	u32 sync_err;
};

struct pvr_up {
	u8 idx;
	enum pvr_up_state state;
	enum lx_pvr_up_mode mode;
	struct te_hwbuf *hbuf;

	struct delayed_work work;

	enum lx_pvr_up_dest dest;
	struct pvr_up_stats stats;

	struct mutex mutex;
	spinlock_t spinlock;

	bool use_timestamp;
	bool first_time;	/* is the first packet ? */
	u8 pkt_len;		/* 188 or 192 */

	bool empty;		/* upload buffer underrun occured */
	bool up_cert_passed;	/* legacy upload permissions */
};

enum pvr_dn_state {
	PVR_DN_STATE_FREE = 0,
	PVR_DN_STATE_IDLE,
	PVR_DN_STATE_READY,
	PVR_DN_STATE_RECORD,
};

struct pvr_dn_stats {
	u32 unitbuf;
	u32 overflow;
};

struct pvr_pie {
	LX_PVR_PIE_TYPE_T type;
	struct pvr_buf_info buf;

	bool first_time;	/* TRUE : any index is not matched */
	u32 last_wptr;		/* wptr updated after first index matching */
	bool errmsg_enable;
	u32 buf_ovf_level;
};

struct pvr_dn {
	u8 idx;

	u32 src;		/* sdec channel to download */
	u8 pkt_len;
	enum pvr_dn_state state;
	struct te_hwbuf *hbuf;
	u32 last_wptr;
	u32 segment_size;

	struct delayed_work work;

	struct pvr_pie pie;
	struct pvr_dn_stats stats;

	struct mutex mutex;
	spinlock_t spinlock;

	bool first_time;	/* TRUE : the packet is not received */
	bool no_pie;		/* TRUE : not use or exist PIE */

	/* Show warning message if availabe buffer is under this size */
	u32 overflow_bufsize;
	u32 warn_bufsize;

	/* ms unit - do not display message again under this time after showing message */
	u32 warn_interval;
	u32 warn_time;		/* last displayed time */
	bool errmsg_enable;
};

struct pvr_node {
	int users;

	int (*open)(struct pvr_fh *fh);
	void (*close)(struct pvr_fh *fh);

	te_ioctl_func_t ioctl;
	te_ioctl_param_func_t ioctl_param;
};

enum pvr_debug_status {
	PVR_DEBUG_STATUS_UP_DEV = 0,
	PVR_DEBUG_STATUS_DN_DEV,
	PVR_DEBUG_STATUS_MAX,
};

typedef void (*pvr_debug_show_t)(struct pvr_device *dev, struct seq_file *m);

struct pvr_debug {
	struct te_debug_dir *dir;
	pvr_debug_show_t show_status[PVR_DEBUG_STATUS_MAX];
};

struct pvr_device {
	struct pvr_config *cfg;

	struct mutex mutex;

	struct cdev cdev;
	struct pvr_node *node[PVR_DEV_TYPE_MAX];

	struct pvr_debug debug;
	struct te_subdev subdev;

	u8 num_up;
	struct pvr_up up[PVR_UP_MAX];

	u8 num_dn;
	struct pvr_dn dn[PVR_DN_MAX];
};

struct pvr_up_fh {
	struct pvr_up *dev;
	struct te_hwbuf hbuf;
};

struct pvr_dn_fh {
	struct pvr_dn *dev;
	struct te_hwbuf hbuf;
};

struct pvr_fh {
	struct pvr_device *dev;
	union {
		struct pvr_up_fh up;
		struct pvr_dn_fh dn;
	};
	struct te_mem_ctx *mem[LX_PVR_MM_ID_MAX];
	struct pvr_node *node;
	u8 idx;
};

struct pvr_sub_driver {
	const char *name;

	int (*init)(struct pvr_device *dev);
	void (*release)(struct pvr_device *dev);

	int (*suspend)(struct pvr_device *dev);
	int (*resume)(struct pvr_device *dev);
};

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/* CFG */
void pvr_cfg_init(void);

/* CORE */
int pvr_device_init(struct pvr_device *dev);
void pvr_device_release(struct pvr_device *dev);
int pvr_device_suspend(struct pvr_device *dev);
int pvr_device_resume(struct pvr_device *dev);
bool pvr_device_check_paddr_range(struct pvr_fh *fh, u32 paddr, u32 size);

/* DEBUG */
int pvr_debug_register_status_show(struct pvr_device *dev,
				   enum pvr_debug_status status,
				   pvr_debug_show_t show);

/* DN */
void pvr_dn_check_overflow(struct pvr_dn *dn, u32 wptr);
void pvr_pie_check_overflow(struct pvr_dn *dn);

/* UP */

#define te_subdev_to_pvr_device(sd) \
	container_of(sd, struct pvr_device, subdev)

#define get_te_device(dev)		(dev->subdev.tdev)

static inline bool is_valid_addr(struct pvr_buf_info *buf, u32 addr)
{
	return (addr >= buf->base && addr < buf->end);
}

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/
extern int g_pvr_debug_fd;

extern const struct pvr_sub_driver pvr_debug_driver;
extern const struct pvr_sub_driver pvr_up_driver;
extern const struct pvr_sub_driver pvr_dn_driver;
extern const struct pvr_sub_driver pvr_isr_driver;

#endif
