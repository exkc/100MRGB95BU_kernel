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
 *  @author	Ilkyu Kim (ilkyu.kim@lge.com)
 *  @version	1.0
 *  @date		2018-02-09
 *  @note		Additional information.
 */

/* Original Copyright */
/*
 * Copyright (C) 2004 Andrew de Quincey
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 */

#ifndef _CI_IMPL_H_
#define _CI_IMPL_H_

#include <linux/delay.h>
#include <linux/list.h>

#include "debug_util.h"

#include <lg1k/te/te.h>
#include <lg1k/te/debug.h>
#include <lg1k/te/ci.h>

#define CI_DEVICE_NAME	"lg1k-ci"

#define LOG_LEVEL_ERROR		LX_LOGM_LEVEL_ERROR	/* 0 */
#define LOG_LEVEL_WARNING	LX_LOGM_LEVEL_WARNING	/* 1 */
#define LOG_LEVEL_NOTI		LX_LOGM_LEVEL_NOTI	/* 2 */
#define LOG_LEVEL_INFO		LX_LOGM_LEVEL_INFO	/* 3 */
#define LOG_LEVEL_DEBUG		LX_LOGM_LEVEL_DEBUG	/* 4 */
#define LOG_LEVEL_TRACE		LX_LOGM_LEVEL_TRACE	/* 5 */
#define LOG_LEVEL_TRACE_EX	LX_LOGM_LEVEL_TRACE + 1 /* 6 */
#define LOG_LEVEL_TUPLE		LX_LOGM_LEVEL_TRACE + 2 /* 7 */

#define CI_DVB_LOG(type,fmt,args...)	\
	LOGM_PRINT( g_ci_dvb_debug_fd, (LOG_LEVEL_##type), fmt, ##args)

#define log_error(fmt,args...)		CI_DVB_LOG(ERROR,fmt,##args)
#define log_warning(fmt,args...)	CI_DVB_LOG(WARNING,fmt,##args)
#define log_noti(fmt,args...)		CI_DVB_LOG(NOTI,fmt,##args)
#define log_info(fmt,args...)		CI_DVB_LOG(INFO,fmt,##args)
#define log_debug(fmt,args...)		CI_DVB_LOG(DEBUG,fmt,##args)
#define log_trace(fmt,args...)		CI_DVB_LOG(TRACE,fmt,##args)
#define log_trace_ex(fmt,args...)	CI_DVB_LOG(TRACE_EX,fmt,##args)
#define log_tuple(fmt,args...)		CI_DVB_LOG(TUPLE,fmt,##args)

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

struct ci_cfg {
	int irq_num;
	u32 smc_phys_addr;
	u32 smc_phys_size;

	u32 reg_base;
	u32 reg_size;
	u32 mod_base;
	u32 mod_size;

	u32 cis_addr_limit;

	u8 smc_need_vcc;
	bool support_irq;
	bool use_ion; // for ION configuration
};

enum cam_access_mode {
	CAM_ACCESS_MODE_NONE = 0,
	CAM_ACCESS_MODE_ATTRMEM,
	CAM_ACCESS_MODE_IO,
};

struct ci_device {
	struct ci_cfg cfg;

	void __iomem *reg_addr;
	void __iomem *mod_addr;
	void __iomem *smc_addr;

	//spinlock_t carddetect_lock;	//card detect lock
	int irq;

	bool inited;
	bool suspended;
	bool use_irq;
	bool card_detect;
	volatile bool reset_abort;
	enum cam_ready_status cam_ready;
	struct mutex reset_lock;

	enum cam_access_mode access_mode;
	enum ci_mode_speed speed;	//0: LOW 1: HIGH
	enum ci_mode_error error_mode;
	enum ci_mode_datarate rate_mode;

	enum lx_te_input_src input_src;
	struct te_debug_dir *debug_dir;

	struct work_struct reset_work;	/* worker for reset request */
	struct ci_callback lxdvb_cb;

	struct te_subdev subdev;
};

extern int g_ci_dvb_debug_fd;

static inline void ci_sleep(int delay)
{
	usleep_range(delay * 1000, delay * 1000);
}

#endif				//_CI_IMPL_H_
