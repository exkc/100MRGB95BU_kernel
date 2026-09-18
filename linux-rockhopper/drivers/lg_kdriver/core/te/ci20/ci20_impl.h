/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2020 by LG Electronics Inc.
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
 *  CI2.0 Driver for linux dvb_delivery
 *
 *  @author	Ilkyu Kim (ilkyu.kim@lge.com)
 *  @version	1.0
 *  @date	2020-08-05
 *  @note	Additional information.
 */

#ifndef _CI20_IMPL_H_
#define _CI20_IMPL_H_

//#include <linux/list.h>

#include "debug_util.h"

#include <lg1k/te/te.h>
#include <lg1k/te/debug.h>
#include <lg1k/te/ci20.h>

#define CI20_DEVICE_NAME	"lg1k-ci20"

#define LOG_LEVEL_ERROR		LX_LOGM_LEVEL_ERROR	/* 0 */
#define LOG_LEVEL_WARNING	LX_LOGM_LEVEL_WARNING	/* 1 */
#define LOG_LEVEL_NOTI		LX_LOGM_LEVEL_NOTI	/* 2 */
#define LOG_LEVEL_INFO		LX_LOGM_LEVEL_INFO	/* 3 */
#define LOG_LEVEL_DEBUG		LX_LOGM_LEVEL_DEBUG	/* 4 */
#define LOG_LEVEL_TRACE		LX_LOGM_LEVEL_TRACE	/* 5 */

#define CI20_DVB_LOG(type,fmt,args...)	\
	LOGM_PRINT( g_ci20_dvb_debug_fd, (LOG_LEVEL_##type), fmt, ##args)

#define log_error(fmt,args...)		CI20_DVB_LOG(ERROR,fmt,##args)
#define log_warning(fmt,args...)	CI20_DVB_LOG(WARNING,fmt,##args)
#define log_noti(fmt,args...)		CI20_DVB_LOG(NOTI,fmt,##args)
#define log_info(fmt,args...)		CI20_DVB_LOG(INFO,fmt,##args)
#define log_debug(fmt,args...)		CI20_DVB_LOG(DEBUG,fmt,##args)
#define log_trace(fmt,args...)		CI20_DVB_LOG(TRACE,fmt,##args)

#define FUNC_TRACE_ENTER()		log_trace("<--%s", __FUNCTION__)
#define FUNC_TRACE_EXIT()		log_trace("-->%s", __FUNCTION__)

#define FUNC_TRACE_EX_ENTER()		log_trace_ex("<--%s", __FUNCTION__)
#define FUNC_TRACE_EX_EXIT()		log_trace_ex("-->%s", __FUNCTION__)

#define CHECK_ERROR(__checker,__if_action,fmt,args...)   \
	__CHECK_IF_ERROR(__checker, log_error, __if_action , fmt, ##args )

#define CHECK_NULL_PARAM(param) \
	CHECK_ERROR((param) == NULL, return RET_INVALID_PARAMS, \
		    "parameter(" #param ") is null")

#define CHECK_PARAM(__checker,fmt,args...) \
	CHECK_ERROR(__checker, return RET_INVALID_PARAMS, \
		    "invalid parameter : " fmt, ##args)

enum ci20_dump_state {
	INPUT_DUMP_IDLE = 0,
	INPUT_DUMP_RUNNING,
	INPUT_DUMP_SUSPEND,
};

struct ci20_cfg {
	u8 num_ch;
};

struct ci20_dump_stats {
	u32 pkt;
	u32 sync_drop;
	u32 overflow;
};

struct ci20_input_dump {
	volatile enum ci20_dump_state state;
	u8 ch;
	u32 intr;

	struct te_hwbuf *data;

	struct ci20_dump_stats stats;
	bool sync;
	spinlock_t spinlock;
};

struct ci20_channel {
	u8 num;

	struct ci20_device *dev;	/* for device control */
	enum lx_te_input_port input_port;
	struct ci20_input_dump dump;
	struct mutex mutex;

	char debug_name[8];
	struct te_debug_dir *debug_dir;
};

struct ci20_device {
	struct ci20_cfg *cfg;

	struct te_debug_dir *debug_dir;

	struct te_subdev subdev;

	u8 num_channel;
	struct ci20_channel channels[0];
};

extern int g_ci20_dvb_debug_fd;

#endif				//_CI20_IMPL_H_
