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
 *  TE(Transport Engine) Driver for linux dvb(DEMUX&CA)
 *
 *  @author	Kyungseok Hyun (ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2018-01-26
 *  @note		Additional information.
 */

#ifndef _LXDVB_IMPL_H_
#define _LXDVB_IMPL_H_

#include <linux/version.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/vmalloc.h>
#include <linux/platform_device.h>
#include <linux/delay.h>

#include "logm_kapi.h"
#include "te_kapi.h"
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#include <media/dvbdev.h>
#else
#include "dvbdev.h"
#endif

#include <lg1k/te/te.h>
#include <lg1k/te/debug.h>

#define	LXDVB_MODULE		"lxdvb"
#define LXDVB_DEVICE_NAME	"lg1k-dvb"

#define LOG_LEVEL_ERROR		LX_LOGM_LEVEL_ERROR	/* 0 */
#define LOG_LEVEL_WARNING	LX_LOGM_LEVEL_WARNING	/* 1 */
#define LOG_LEVEL_NOTI		LX_LOGM_LEVEL_NOTI	/* 2 */
#define LOG_LEVEL_INFO		LX_LOGM_LEVEL_INFO	/* 3 */
#define LOG_LEVEL_DEBUG		LX_LOGM_LEVEL_DEBUG	/* 4 */
#define LOG_LEVEL_TRACE		LX_LOGM_LEVEL_TRACE	/* 5 */
#define LOG_LEVEL_FILTER	LX_LOGM_LEVEL_TRACE + 1
#define LOG_LEVEL_PES_FILTER	LX_LOGM_LEVEL_TRACE + 2
#define LOG_LEVEL_TUPLE		LX_LOGM_LEVEL_TRACE + 3
#define LOG_LEVEL_DEVICE	LX_LOGM_LEVEL_TRACE + 4
#define LOG_LEVEL_DESC		LX_LOGM_LEVEL_TRACE + 5
#define LOG_LEVEL_TS_HEADER	LX_LOGM_LEVEL_TRACE + 6

#define lxdvb_log(type,fmt,args...)	\
	LOGM_PRINT( g_lxdvb_debug_fd, (LOG_LEVEL_##type), fmt, ##args)

#define log_error(fmt,args...)		lxdvb_log(ERROR,fmt,##args)
#define log_warning(fmt,args...)	lxdvb_log(WARNING,fmt,##args)
#define log_noti(fmt,args...)		lxdvb_log(NOTI,fmt,##args)
#define log_info(fmt,args...)		lxdvb_log(INFO,fmt,##args)
#define log_debug(fmt,args...)		lxdvb_log(DEBUG,fmt,##args)
#define log_trace(fmt,args...)		lxdvb_log(TRACE,fmt,##args)
#define log_filter(fmt,args...)		lxdvb_log(FILTER,fmt,##args)
#define log_pes_filter(fmt,args...)	lxdvb_log(PES_FILTER,fmt,##args)
#define log_tuple(fmt,args...)		lxdvb_log(TUPLE,fmt,##args)
#define log_device(fmt,args...)		lxdvb_log(DEVICE,fmt,##args)
#define log_desc(fmt,args...)		lxdvb_log(DESC,fmt,##args)
#define log_tsh(fmt,args...)		lxdvb_log(TS_HEADER,fmt,##args)

#define CHECK_ERROR(__checker,__if_action,fmt,args...)   \
  TE_CHECK_IF_ERROR(__checker, log_error, __if_action , fmt, ##args )

#define CHECK_PARAM(__checker,fmt,args...) \
  CHECK_ERROR(__checker, return -EINVAL, "invalid parameter : " fmt, ##args)

#define CHECK_NULL_PARAM(param) \
  CHECK_ERROR((param) == NULL, return -EINVAL, "parameter(" #param ") is null")


struct lxdvb_demux;
struct lxdvb_dvr;
struct lxdvb_ca;

struct lxdvb_device {
	struct platform_device *pdev;
	struct te_subdev subdev;
	struct dvb_adapter adapter;
	struct te_debug_dir *debug_dir;

	struct lxdvb_demux *dmx;
	struct lxdvb_dvr *dvr;
	struct lxdvb_ca *ca;
	struct lxdvb_ci14 *ci14;
	struct lxdvb_sci *sci;
	struct lxdvb_delivery *delivery;
};

struct lxdvb_sub_driver {
	const char *name;

	int (*init)(struct lxdvb_device *dev);
	void (*release)(struct lxdvb_device *dev);

	int (*suspend)(struct lxdvb_device *dev);
	int (*resume)(struct lxdvb_device *dev);
};

int lxdvb_device_init(struct lxdvb_device *dev);
void lxdvb_device_release(struct lxdvb_device *dev);
int lxdvb_device_suspend(struct lxdvb_device *dev);
int lxdvb_device_resume(struct lxdvb_device *dev);

int lxdvb_proc_init(struct lxdvb_device *dev);

#define get_te_device(dev)	((dev)->subdev.tdev)


extern int g_lxdvb_debug_fd;

extern const struct lxdvb_sub_driver lxdvb_demux_driver;
extern const struct lxdvb_sub_driver lxdvb_dvr_driver;
extern const struct lxdvb_sub_driver lxdvb_ca_driver;
extern const struct lxdvb_sub_driver lxdvb_ci14_driver;
extern const struct lxdvb_sub_driver lxdvb_sci_driver;
extern const struct lxdvb_sub_driver lxdvb_delivery_driver;


#endif
