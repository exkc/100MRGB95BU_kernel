/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2018 by LG Electronics Inc.
 *
 * Parts of this file were based on sources as follows:
 *
 * dmxdev.c - DVB demultiplexer device
 *
 * Copyright (C) 2000 Ralph Metzler & Marcus Metzler
 *		      for convergence integrated media GmbH
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

/** @file
 *
 *  TE(Transport Engine) Driver for linux dvb(DELIVERY)
 *
 *  @author	Yeonju lee (yeonju.lee@lge.com)
 *  @version	1.0
 *  @date	2020-02-17
 *  @note	Additional information.
 */

#include <linux/spinlock.h>
#include <linux/ioctl.h>
#include <linux/poll.h>

#include <lg1k/te/dump.h>
#include <lg1k/te/io.h>
#include <lg1k/te/mem.h>
#include <lg1k/te/atsc3.h>
#include <lg1k/te/arib2.h>
#include <lg1k/te/ci20.h>

#include "lxdvb_impl.h"
#include "lxdvb_delivery.h"

struct dvb_function {
	int (*config_input)(struct lxdvb_delivery_channel *channel,
			    struct delivery_input_cfg *cfg);
	int (*set_time)(struct lxdvb_delivery_channel *channel,
			struct delivery_ext_time *param);
	int (*get_time)(struct lxdvb_delivery_channel *channel,
			struct delivery_ext_time *param);
	int (*set_clock_recovery)(struct lxdvb_delivery_channel *channel,
				  u32 param);
	int (*start_dump)(struct lxdvb_delivery_channel *channel);
	int (*stop_dump)(struct lxdvb_delivery_channel *channel);
	ssize_t (*read_dump)(struct lxdvb_delivery_channel *channel,
			     char __user *buf, size_t count);
	int (*set_system_time)(struct lxdvb_delivery_channel *channel,
			       struct delivery_ext_system_time_info *param);
	int (*set_demod_version)(struct lxdvb_delivery_channel *channel,
				 u32 vers);
	unsigned int (*wait_poll)(enum delivery_ext_event event,
				  struct lxdvb_delivery_channel *channel,
				  struct file *file,
				  struct poll_table_struct *wait);
	int (*set_adjust_clock_table)(struct lxdvb_delivery_channel *channel,
				      int *table, u32 size);
};

struct delivery_control_param {
	u32 id;
	const char *name;
	u32 size;
	u32 dir;
};
#define _IOC_RW			(_IOC_READ | _IOC_WRITE)

#define SIZE_OF_CONFIG_INPUT	sizeof(struct delivery_ext_source)
#define SIZE_OF_SYS_TIME	sizeof(struct delivery_ext_system_time_info)
#define SIZE_OF_CURR_TIME	sizeof(struct delivery_ext_time)

//FIXME
#ifndef DELIVERY_EXT_CID_MANIPULATED_WALL_CLOCK
#define DELIVERY_EXT_CID_MANIPULATED_WALL_CLOCK 9
#endif

static const struct te_val_str port_type_list[] = {
	{DELIVERY_EXT_SRC_TYPE_NULL, "NONE"},
	{DELIVERY_EXT_SRC_TYPE_IN_DEMOD, "IN_DEMOD"},
	{DELIVERY_EXT_SRC_TYPE_EXT_DEMOD, "EXT_DEMOD"},
	{DELIVERY_EXT_SRC_TYPE_MEM, "MEM"},
};

static const struct te_val_str input_type_list[] = {
	{DELIVERY_EXT_PORT_TYPE_SERIAL, "SERIAL"},
	{DELIVERY_EXT_PORT_TYPE_PARALLEL, "PARALLEL"},
	{DELIVERY_EXT_PORT_TYPE_DISABLE, "DISABLE"},
};

static const struct te_val_str dump_state_list[] = {
	{DELIVERY_DUMP_STATE_IDLE, "IDLE"},
	{DELIVERY_DUMP_STATE_RUNNING, "RUNNING"},
};

static const struct te_val_str mode_list[] = {
	{DELIVERY_EXT_MODE_UNSET, "UNSET"},
	{DELIVERY_EXT_MODE_ATSC30, "ATSC3.0"},
	{DELIVERY_EXT_MODE_JAPAN4K, "ARIB2.0"},
	{DELIVERY_EXT_MODE_CI20, "CI2.0"},
};

static const struct te_val_str event_list[] = {
	{DELIVERY_EXT_EVENT_UNSET, "UNSET"},
	{DELIVERY_EXT_EVENT_DATA_DUMP, "DUMP"},
	{DELIVERY_EXT_EVENT_WALL_CLOCK, "CLOCK"},
};

static const char *invalid_str = "INVALID";

static const char *delivery_src_str(enum delivery_ext_src_type type)
{
	return find_match_string(port_type_list, type, invalid_str);
}

static const char *delivery_port_str(enum delivery_ext_port_type type)
{
	return find_match_string(input_type_list, type, invalid_str);
}

static const char *delivery_dump_state_str(enum delivery_dump_state state)
{
	return find_match_string(dump_state_list, state, invalid_str);
}

static const char *delivery_mode_str(enum delivery_ext_mode mode)
{
	return find_match_string(mode_list, mode, invalid_str);
}

static const char *delivery_event_str(enum delivery_ext_event event)
{
	return find_match_string(event_list, event, invalid_str);
}

static const struct delivery_control_param delivery_control_params[] = {
	{DELIVERY_EXT_CID_MODE, "set_mode", 0, _IOC_WRITE},
	{DELIVERY_EXT_CID_INPUT_SOURCE, "input_source", SIZE_OF_CONFIG_INPUT,
	 _IOC_WRITE},
	{DELIVERY_EXT_CID_SYSTEM_TIME_INFO, "system_time", SIZE_OF_SYS_TIME,
	 _IOC_WRITE},
	{DELIVERY_EXT_CID_CURRENT_TIME, "current_time", SIZE_OF_CURR_TIME,
	 _IOC_RW},
	{DELIVERY_EXT_CID_CLOCK_RECOVERY_ONOFF, "recovery", 0, _IOC_WRITE},
	{DELIVERY_EXT_CID_DEMOD_VERSION, "demod_vers", 0, _IOC_WRITE},
	{DELIVERY_EXT_CID_START, "start", 0, _IOC_WRITE},
	{DELIVERY_EXT_CID_STOP, "stop", 0, _IOC_WRITE},
	{DELIVERY_EXT_CID_MANIPULATED_WALL_CLOCK, "manipulated_wall_clock", 0,
	 _IOC_WRITE},
};

static const struct delivery_control_param *get_delivery_control_param(u32 id)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(delivery_control_params); i++) {
		if (delivery_control_params[i].id == id)
			return &delivery_control_params[i];
	}
	return NULL;
}

static int get_cfg_from_ext_source(struct lxdvb_delivery_channel *channel,
				   struct delivery_ext_source *param,
				   struct delivery_input_cfg *cfg)
{
	int num = param->input_port_num;

	switch (param->input_src_type) {
	case DELIVERY_EXT_SRC_TYPE_IN_DEMOD:
		if (num > 0)
			return -EINVAL;
		cfg->port = LX_TE_INPUT_PORT_TPI_IN_DEMOD0;
		break;
	case DELIVERY_EXT_SRC_TYPE_EXT_DEMOD:
		if (num > 1)
			return -EINVAL;
		cfg->port = LX_TE_INPUT_PORT_TPI_EXT_INPUT0 + num;
		break;
	case DELIVERY_EXT_SRC_TYPE_MEM:
		if (num > 1)
			return -EINVAL;
		cfg->port = LX_TE_INPUT_PORT_DVR;
		break;
	case DELIVERY_EXT_SRC_TYPE_NULL:
		cfg->port = LX_TE_INPUT_PORT_NONE;
		break;
	default:
		return -EINVAL;
	}

	if (param->input_port_type == DELIVERY_EXT_PORT_TYPE_SERIAL)
		cfg->mode = LX_TE_INPUT_MODE_SERIAL;
	else
		cfg->mode = LX_TE_INPUT_MODE_PARALLEL;

	return 0;
}

static int set_tpi_config(struct te_device *tdev,
			  struct delivery_input_cfg *cfg,
			  enum lx_te_stream_type type)
{
	struct lx_te_tpi_cfg tpi;
	int ret;

	tpi.stream_type = type;
	tpi.mode = cfg->mode;

	if (type != LX_TE_STREAM_MPEG2TS) { // default (ATSC3, ARIB4K)
		tpi.sync_type = LX_TE_SYNC_SOP;
		tpi.s2p_sync_type = LX_TE_SYNC_SOP;
		tpi.num_of_sync_found = 0;
		tpi.num_of_sync_drop = 0;
	} else { //CI+2.0
		tpi.sync_type = LX_TE_SYNC_SYNC_BYTE;
		tpi.s2p_sync_type = LX_TE_SYNC_SYNC_BYTE;
		tpi.num_of_sync_found = 3;
		tpi.num_of_sync_drop = 3;
	}

	ret = te_config_tpi(tdev, cfg->port, &tpi);
	if (ret < 0) {
		log_error("te_config_tpi failed(%d)", ret);
		return ret;
	}
	return ret;
}

static int init_delivery_hwbuf(enum delivery_ext_mode mode,
			       struct delivery_dump_dev *dump)
{
	u32 data_size, data_unit, meta_size, meta_unit;
	u64 data_flag, meta_flag;
	te_phys_addr_t data, meta;
	int rc;

/* Buffer size should be aligned to 16 Bytes */
#define INPUT_DUMP_ATSC3_DATA_SIZE	(9*1024*1024)
#define INPUT_DUMP_ARIB2_DATA_SIZE	(12*1024*1024)
#define INPUT_DUMP_ATSC3_DATA_UNIT_SIZE	(64*1024)  /* about 25msec in 20Mbps */
#define INPUT_DUMP_ARIB2_DATA_UNIT_SIZE	(384*1024) /* about 30msec in 100Mbps */
#define INPUT_DUMP_TS_DATA_SIZE		INPUT_DUMP_ATSC3_DATA_SIZE
#define INPUT_DUMP_TS_UNIT_SIZE		(8 * 188)

#define DATA_SIZE_PER_META		1024
#define META_SIZE			16

#define INPUT_DUMP_ATSC3_META_SIZE	(16 * 64)
#define INPUT_DUMP_ARIB2_META_SIZE	((INPUT_DUMP_ARIB2_DATA_SIZE / DATA_SIZE_PER_META) * META_SIZE)
#define INPUT_DUMP_META_UNIT_SIZE	0

	if (mode == DELIVERY_EXT_MODE_ATSC30 ||
	    mode == DELIVERY_EXT_MODE_JAPAN4K) {
		if (mode == DELIVERY_EXT_MODE_ATSC30) {
			data_size = INPUT_DUMP_ATSC3_DATA_SIZE;
			meta_size = INPUT_DUMP_ATSC3_META_SIZE;
			data_unit = INPUT_DUMP_ATSC3_DATA_UNIT_SIZE;
		} else {
			data_size = INPUT_DUMP_ARIB2_DATA_SIZE;
			meta_size = INPUT_DUMP_ARIB2_META_SIZE;
			data_unit = INPUT_DUMP_ARIB2_DATA_UNIT_SIZE;
		}
		data_flag = TE_BUF_FLAG_NO_EVENT | TE_BUF_FLAG_VMAP_CACHED;
		meta_flag = TE_BUF_FLAG_NO_EVENT | TE_BUF_FLAG_VMAP;
		meta_unit = INPUT_DUMP_META_UNIT_SIZE;
		dump->use_meta = true;
	} else { // CI20(RAW) dump
		data_size = INPUT_DUMP_TS_DATA_SIZE;
		data_flag = TE_BUF_FLAG_VMAP_CACHED;
		data_unit = INPUT_DUMP_TS_UNIT_SIZE;
		dump->use_meta = false;
	}

	data = te_mem_alloc(dump->mem, data_size, "delivery_data");
	CHECK_ERROR(!data, return -ENOMEM, "te_mem_alloc fail(data)");

	rc = te_hwbuf_init(&dump->data, data, data_size, data_unit, data_flag);
	CHECK_ERROR(rc < 0, goto err_data_init, "error in te_hwbuf_init");

	if (!dump->use_meta)
		return 0;

	meta = te_mem_alloc(dump->mem, meta_size, "delivery_meta");
	if (!meta) {
		rc = -ENOMEM;
		log_error("te_mem_alloc fail(meta)");
		goto err_meta_alloc;
	}

	rc = te_hwbuf_init(&dump->meta, meta, meta_size, meta_unit, meta_flag);
	CHECK_ERROR(rc < 0, goto err_meta_init, "error in te_hwbuf_init");

	return 0;

err_meta_init:
	te_mem_free(dump->mem, meta);
err_meta_alloc:
	te_hwbuf_release(&dump->data);
err_data_init:
	te_mem_free(dump->mem, data);

	return rc;
}

static void release_delivery_hwbuf(struct delivery_dump_dev *dump)
{
	phys_addr_t addr;

	addr = te_hwbuf_addr(&dump->data);
	te_hwbuf_release(&dump->data);
	te_mem_free(dump->mem, addr);

	if (!dump->use_meta)
		return;

	addr = te_hwbuf_addr(&dump->meta);
	te_hwbuf_release(&dump->meta);
	te_mem_free(dump->mem, addr);
}

static int dvb_atsc3_config_input(struct lxdvb_delivery_channel *channel,
				  struct delivery_input_cfg *param)
{
	struct lx_atsc3_channel_input_cfg cfg;
	enum lx_te_stream_type type = LX_TE_STREAM_ATSC3;
	int ret;

	cfg.port = param->port;
	cfg.enable = (param->port == LX_TE_INPUT_PORT_NONE) ? false : true;
	cfg.reset = false;

	if (te_get_input_port_type(param->port) == LX_TE_INPUT_PORT_TPI) {
		ret = set_tpi_config(channel->delivery->tdev, param, type);
		if (ret < 0) {
			log_error("te_config_tpi failed(%d)", ret);
			return ret;
		}
		if (ret == 1)
			cfg.reset = true;
	}

	ret = atsc3_config_channel_input(channel->dev, &cfg);
	if (ret) {
		log_error("atsc3_config_channel_input failed(%d)", ret);
		return ret;
	}

	if (cfg.enable) {
		atsc3_io_set_channel_enable(channel->dev, true);
	} else {
		atsc3_io_set_channel_enable(channel->dev, false);
	}

	return ret;
}

static int dvb_atsc3_set_time(struct lxdvb_delivery_channel *channel,
			      struct delivery_ext_time *param)
{
	struct lx_atsc3_time time;

	time.sec = param->sec;
	time.nsec = param->nsec;

	return atsc3_set_time(channel->dev, &time);
}

static int dvb_atsc3_get_time(struct lxdvb_delivery_channel *channel,
			      struct delivery_ext_time *param)
{
	struct lx_atsc3_time time;
	int ret;

	ret = atsc3_get_time(channel->dev, &time);
	if (ret) {
		return ret;
	}

	param->sec = time.sec;
	param->nsec = time.nsec;
	param->wall_clock = time.wall_clock;

	log_trace("sec:%d, nsec:%d, wall_clock:%d",
		  time.sec, time.nsec, time.wall_clock);

	return 0;
}

static int dvb_atsc3_clock_recovery(struct lxdvb_delivery_channel *channel,
				    u32 param)
{
	enum lx_atsc3_clock_recovery value;
	int ret;
	if (param == 1)
		value = LX_ATSC3_CLOCK_RECOVERY_ENABLE;
	else
		value = LX_ATSC3_CLOCK_RECOVERY_DISABLE;

	ret = atsc3_set_clock_recovery(channel->dev, value);

	return ret;
}

/* DEBUG function for clock value change */
static int dvb_atsc3_set_adjust_clock_table(
		struct lxdvb_delivery_channel *channel, int *table, u32 size)
{
	if (!table || !size)
		return -EINVAL;

	return atsc3_set_debug_adjust_clock(channel->dev, table, size);
}

static int dvb_atsc3_input_dump_start(struct lxdvb_delivery_channel *channel)
{
	struct delivery_dump_dev *dump = &channel->dump;
	struct atsc3_dump_cfg cfg;
	struct atsc3_input_dump *dev;
	int ret;

	if (channel->delivery->demod_type == -1) {
		log_error("demod type is not set");
		return -EIO;
	}

	if (dump->state > DELIVERY_DUMP_STATE_IDLE) {
		log_error("invalid state:%s",
			  delivery_dump_state_str(dump->state));
		return -EBUSY;
	}

	ret = init_delivery_hwbuf(channel->delivery->mode, dump);
	if (ret) {
		log_error("hwbuf_init failed(%d)", ret);
		return ret;
	}
	cfg.data = &dump->data;
	cfg.meta = &dump->meta;
	cfg.layer = ATSC3_DECODER_LAYER_BYPASS;
	cfg.mode = DUMPER_MODE_RAW;
	cfg.flags = ATSC3_DUMP_FLAG_WORKQUEUE;

	dev = atsc3_start_input_dump(channel->dev, &cfg);
	if (!dev) {
		log_error("atsc3_start_input_dump failed");
		goto err_start_dump;
	}
	dump->dev = dev;
	dump->state = DELIVERY_DUMP_STATE_RUNNING;

	return 0;

err_start_dump:
	release_delivery_hwbuf(dump);

	return -EIO;
}

static int dvb_atsc3_input_dump_stop(struct lxdvb_delivery_channel *channel)
{
	struct delivery_dump_dev *dump = &channel->dump;
	int rc;

	if (dump->state == DELIVERY_DUMP_STATE_IDLE) {
		log_debug("already_stopped");
		return 0;
	}

	rc = atsc3_stop_input_dump(dump->dev);
	if (rc) {
		log_error("atsc3_stop_input_dump failed");
		return -EIO;
	}
	release_delivery_hwbuf(dump);
	dump->state = DELIVERY_DUMP_STATE_IDLE;

	return 0;
}

static ssize_t dvb_atsc3_read(struct lxdvb_delivery_channel *channel,
			      char __user *buf, size_t count)
{
	if (channel->dump.state != DELIVERY_DUMP_STATE_RUNNING) {
		log_error("dump is not started");
		return -EIO;
	}

	return atsc3_read_data(channel->dev, buf, count);
}

static int dvb_atsc3_set_sys_time(struct lxdvb_delivery_channel *channel,
				  struct delivery_ext_system_time_info *param)
{
	struct lx_atsc3_system_time_info info;

	info.current_utc_offset = param->current_utc_offset;
	info.ptp_prepend = param->ptp_prepend;
	info.leap59 = param->leap59;
	info.leap61 = param->leap61;

	return atsc3_set_system_time_info(channel->dev, &info);
}

static int dvb_atsc3_set_demod_version(struct lxdvb_delivery_channel *channel,
				       u32 version)
{
	enum lx_atsc3_demod_type type;

	if (version == 0)
		type = LX_ATSC3_DEMOD_TYPE_A;
	else if (version == 1)
		type = LX_ATSC3_DEMOD_TYPE_B;
	else if (version == 2)
		type = LX_ATSC3_DEMOD_TYPE_C;
	else if (version == 3)
		type = LX_ATSC3_DEMOD_TYPE_D;
	else if (version == 4) /* after o22, in_demod B17+(OIF type C) */
		type = LX_ATSC3_DEMOD_TYPE_D;
	else
		return -EINVAL;

	return atsc3_set_demod_type(channel->dev, type);
}

static unsigned int dvb_atsc3_poll(enum delivery_ext_event event,
				   struct lxdvb_delivery_channel *channel,
				   struct file *file,
				   struct poll_table_struct *wait)
{
	if (event == DELIVERY_EXT_EVENT_DATA_DUMP) {
		if (channel->dump.state != DELIVERY_DUMP_STATE_RUNNING) {
			log_error("dump is not running");
			return POLLERR;
		}
		return atsc3_wait_data(channel->dev, file, wait);
	} else if (event == DELIVERY_EXT_EVENT_WALL_CLOCK) {
		return atsc3_wait_clock(channel->dev, file, wait);
	} else {
		log_debug("event is not set");
		return POLLERR;
	}
}

static const struct dvb_function atsc3_func = {
	.config_input = dvb_atsc3_config_input,
	.set_time = dvb_atsc3_set_time,
	.get_time = dvb_atsc3_get_time,
	.set_clock_recovery = dvb_atsc3_clock_recovery,
	.start_dump = dvb_atsc3_input_dump_start,
	.stop_dump = dvb_atsc3_input_dump_stop,
	.read_dump = dvb_atsc3_read,
	.set_system_time = dvb_atsc3_set_sys_time,
	.set_demod_version = dvb_atsc3_set_demod_version,
	.wait_poll = dvb_atsc3_poll,
	.set_adjust_clock_table = dvb_atsc3_set_adjust_clock_table
};

static int dvb_arib2_config_input(struct lxdvb_delivery_channel *channel,
				  struct delivery_input_cfg *param)
{
	struct lx_arib2_channel_input_cfg cfg;
	enum lx_te_stream_type type = LX_TE_STREAM_ARIB2;
	int ret;

	cfg.port = param->port;
	cfg.enable = (param->port == LX_TE_INPUT_PORT_NONE) ? false : true;
	cfg.reset = false;

	if (te_get_input_port_type(param->port) == LX_TE_INPUT_PORT_TPI) {
		ret = set_tpi_config(channel->delivery->tdev, param, type);
		if (ret < 0) {
			log_error("te_config_tpi failed(%d)", ret);
			return ret;
		}
		if (ret == 1)
			cfg.reset = true;
	}

	ret = arib2_config_channel_input(channel->dev, &cfg);
	if (ret) {
		log_error("arib2_config_channel_input failed(%d)", ret);
		return ret;
	}

	return ret;
}

static int dvb_arib2_set_time(struct lxdvb_delivery_channel *channel,
			      struct delivery_ext_time *param)
{
	struct lx_arib2_time time;

	time.sec = param->sec;
	time.fraction = param->nsec;
	time.latched = param->wall_clock;

	return arib2_set_time(channel->dev, &time);
}

static int dvb_arib2_get_time(struct lxdvb_delivery_channel *channel,
			      struct delivery_ext_time *param)
{
	struct lx_arib2_time time;
	int ret;

	ret = arib2_get_time(channel->dev, &time);
	if (ret) {
		return ret;
	}

	param->sec = time.sec;
	param->nsec = time.fraction;
	param->wall_clock = time.latched;

	log_trace("sec:%d, nsec:%d, wall_clock:%d",
		  time.sec, time.fraction, time.latched);

	return 0;
}

static int dvb_arib2_clock_recovery(struct lxdvb_delivery_channel *channel,
				    u32 param)
{
	enum lx_arib2_clock_recovery value;
	int ret;

	if (param == 1)
		value = LX_ARIB2_CLOCK_RECOVERY_ENABLE;
	else
		value = LX_ARIB2_CLOCK_RECOVERY_DISABLE;

	ret = arib2_set_clock_recovery(channel->dev, value);

	return ret;
}

static int dvb_arib2_input_dump_start(struct lxdvb_delivery_channel *channel)
{
	struct delivery_dump_dev *dump = &channel->dump;
	struct arib2_dump_cfg cfg;
	struct arib2_input_dump *dev;
	int ret;

	if (dump->state > DELIVERY_DUMP_STATE_IDLE) {
		log_error("invalid state:%s",
			  delivery_dump_state_str(dump->state));
		return -EBUSY;
	}

	ret = init_delivery_hwbuf(channel->delivery->mode, dump);
	if (ret) {
		log_error("hwbuf_init failed(%d)", ret);
		return ret;
	}

	cfg.data = &dump->data;
	cfg.meta = &dump->meta;
	cfg.mode = DUMPER_MODE_TLV;
	cfg.flags = ARIB2_DUMP_FLAG_WORKQUEUE;

	dev = arib2_start_input_dump(channel->dev, &cfg);
	if (!dev) {
		log_error("arib2_start_input_dump failed");
		goto err_start_dump;
	}

	dump->dev = dev;
	dump->state = DELIVERY_DUMP_STATE_RUNNING;

	return 0;

err_start_dump:
	release_delivery_hwbuf(dump);

	return -EIO;
}

static int dvb_arib2_input_dump_stop(struct lxdvb_delivery_channel *channel)
{
	struct delivery_dump_dev *dump = &channel->dump;
	int rc;

	if (dump->state == DELIVERY_DUMP_STATE_IDLE) {
		log_debug("already_stopped");
		return 0;
	}

	rc = arib2_stop_input_dump(dump->dev);
	if (rc) {
		log_error("arib2_stop_input_dump failed");
		return -EIO;
	}

	release_delivery_hwbuf(dump);
	dump->state = DELIVERY_DUMP_STATE_IDLE;

	return 0;
}

static ssize_t dvb_arib2_read(struct lxdvb_delivery_channel *channel,
			      char __user *buf, size_t count)
{
	if (channel->dump.state != DELIVERY_DUMP_STATE_RUNNING) {
		log_error("dump is not started");
		return -EIO;
	}

	return arib2_read_data(channel->dev, buf, count);
}

static unsigned int dvb_arib2_poll(enum delivery_ext_event event,
				   struct lxdvb_delivery_channel *channel,
				   struct file *file,
				   struct poll_table_struct *wait)
{
	if (event == DELIVERY_EXT_EVENT_DATA_DUMP) {
		if (channel->dump.state != DELIVERY_DUMP_STATE_RUNNING) {
			log_error("dump is not running");
			return POLLERR;
		}

		return arib2_wait_data(channel->dev, file, wait);
	} else if (event == DELIVERY_EXT_EVENT_WALL_CLOCK) {
		return arib2_wait_clock(channel->dev, file, wait);
	} else {
		log_debug("event is not set");
		return POLLERR;
	}
}

static const struct dvb_function arib2_func = {
	.config_input = dvb_arib2_config_input,
	.set_time = dvb_arib2_set_time,
	.get_time = dvb_arib2_get_time,
	.set_clock_recovery = dvb_arib2_clock_recovery,
	.start_dump = dvb_arib2_input_dump_start,
	.stop_dump = dvb_arib2_input_dump_stop,
	.read_dump = dvb_arib2_read,
	.wait_poll = dvb_arib2_poll,
};

#ifdef INCLUDE_KDRV_CI20
static int dvb_ci20_config_input(struct lxdvb_delivery_channel *channel,
				struct delivery_input_cfg *param)
{
	enum lx_te_stream_type type = LX_TE_STREAM_MPEG2TS;
	enum lx_te_input_port port;
	bool reset, enable;
	int ret;

	port = param->port;
	enable = (param->port == LX_TE_INPUT_PORT_NONE) ? false : true;
	reset = false;

	if (te_get_input_port_type(param->port) == LX_TE_INPUT_PORT_TPI) {
		ret = set_tpi_config(channel->delivery->tdev, param, type);
		if (ret < 0) {
			log_error("te_config_tpi failed(%d)", ret);
			return ret;
		}
		if (ret == 1)
			reset = true;
	}

	ret = ci20_config_channel_input(channel->dev, port, reset, enable);
	if (ret) {
		log_error("atsc3_config_channel_input failed(%d)", ret);
		return ret;
	}

	return 0;
}

static int dvb_ci20_input_dump_start(struct lxdvb_delivery_channel *channel)
{
	struct delivery_dump_dev *dump = &channel->dump;
	struct ci20_dump_cfg cfg;
	struct ci20_input_dump *dev;
	int ret;

	if (dump->state > DELIVERY_DUMP_STATE_IDLE) {
		log_error("invalid state:%s",
			  delivery_dump_state_str(dump->state));
		return -EBUSY;
	}

	ret = init_delivery_hwbuf(channel->delivery->mode, dump);
	if (ret) {
		log_error("hwbuf_init failed(%d)", ret);
		return ret;
	}
	cfg.data = &dump->data;

	dev = ci20_start_input_dump(channel->dev, &cfg);
	if (!dev) {
		log_error("atsc3_start_input_dump failed");
		goto err_start_dump;
	}

	dump->dev = dev;
	dump->state = DELIVERY_DUMP_STATE_RUNNING;

	return 0;

err_start_dump:
	release_delivery_hwbuf(dump);

	return -EIO;
}

static int dvb_ci20_input_dump_stop(struct lxdvb_delivery_channel *channel)
{
	struct delivery_dump_dev *dump = &channel->dump;
	int rc;

	if (dump->state == DELIVERY_DUMP_STATE_IDLE) {
		log_debug("already_stopped");
		return 0;
	}

	rc = ci20_stop_input_dump(dump->dev);
	if (rc) {
		log_error("atsc3_stop_input_dump failed");
		return -EIO;
	}
	release_delivery_hwbuf(dump);
	dump->state = DELIVERY_DUMP_STATE_IDLE;

	return 0;
}

static ssize_t dvb_ci20_read(struct lxdvb_delivery_channel *channel,
			    char __user *buf, size_t count)
{
	if (channel->dump.state != DELIVERY_DUMP_STATE_RUNNING) {
		log_error("dump is not started");
		return -EIO;
	}

	return ci20_read_data(channel->dev, buf, count);
}

static unsigned int dvb_ci20_poll(enum delivery_ext_event event,
				  struct lxdvb_delivery_channel *channel,
				  struct file *file,
				  struct poll_table_struct *wait)
{
	if (event == DELIVERY_EXT_EVENT_DATA_DUMP) {
		if (channel->dump.state != DELIVERY_DUMP_STATE_RUNNING) {
			log_error("dump is not running");
			return POLLERR;
		}
		return ci20_wait_data(channel->dev, file, wait);
	} else {
		log_debug("event is not set (need DUMP)");
		return POLLERR;
	}
}

static const struct dvb_function ci20_func = {
	.config_input = dvb_ci20_config_input,
	.set_time = NULL,
	.get_time = NULL,
	.set_clock_recovery = NULL,
	.start_dump = dvb_ci20_input_dump_start,
	.stop_dump = dvb_ci20_input_dump_stop,
	.read_dump = dvb_ci20_read,
	.set_system_time = NULL,
	.set_demod_version = NULL,
	.wait_poll = dvb_ci20_poll,
};
#endif

static int ioc_set_mode(struct lxdvb_delivery_fh *fh,
			enum delivery_ext_mode mode)
{
	struct lxdvb_delivery_channel *channel = fh->channel;
	struct lxdvb_delivery *delivery = channel->delivery;

	log_noti("%s(ch:%d,delivery:%s,curr:%s,new:%s)", __func__, channel->idx,
		 delivery_mode_str(delivery->mode),
		 delivery_mode_str(fh->mode), delivery_mode_str(mode));
	if (mode > DELIVERY_EXT_MODE_CI20) {
		log_error("invalid mode(%d)", mode);
		return -EPERM;
	}

	if (delivery->mode != DELIVERY_EXT_MODE_UNSET) {
		if (mode != delivery->mode) {
			log_error("cannot change delivery mode");
			return -EPERM;
		}
	}

	if (mode == DELIVERY_EXT_MODE_ATSC30) {
		delivery->dev = atsc3_get_device(delivery->tdev);
		if (!delivery->dev) {
			log_error("atsc3 not supported");
			return -ENODEV;
		}
		te_set_engine_mode(delivery->tdev, LX_TE_STREAM_ATSC3);

		channel->func = &atsc3_func;
		channel->dev = atsc3_get_channel(delivery->dev, channel->idx);
		if (!channel->dev) {
			log_error("atsc3 ch[%d] not supported", channel->idx);
			return -ENODEV;
		}
#ifdef INCLUDE_KDRV_CI20
	} else if (mode == DELIVERY_EXT_MODE_CI20) {
		delivery->dev = ci20_get_device(delivery->tdev);
		if (!delivery->dev) {
			log_error("ci20 not supported");
			return -ENODEV;
		}
		te_set_engine_mode(delivery->tdev, LX_TE_STREAM_MPEG2TS);

		channel->func = &ci20_func;
		channel->dev = ci20_get_channel(delivery->dev, channel->idx);
		if (!channel->dev) {
			log_error("ci20 ch[%d] not supported", channel->idx);
			return -ENODEV;
		}
#endif
	} else  {
		delivery->dev = arib2_get_device(delivery->tdev);
		if (!delivery->dev) {
			log_error("arib2 not supported");
			return -ENODEV;
		}
		te_set_engine_mode(delivery->tdev, LX_TE_STREAM_ARIB2);

		channel->func = &arib2_func;
		channel->dev = arib2_get_channel(delivery->dev, channel->idx);
		if (!channel->dev) {
			log_error("arib2 ch[%d] not supported", channel->idx);
			return -ENODEV;
		}
	}

	fh->mode = mode;
	delivery->mode = mode;

	return 0;
}

static int ioc_set_input_source(struct lxdvb_delivery_channel *channel,
				struct delivery_ext_source *param)
{
	struct delivery_input_cfg cfg;
	int ret;

	log_noti("%s(ch:%d,%s+%d,%s)", __func__, channel->idx,
		 delivery_src_str(param->input_src_type),
		 param->input_port_num,
		 delivery_port_str(param->input_port_type));

	ret = get_cfg_from_ext_source(channel, param, &cfg);
	CHECK_ERROR(ret, return ret, "get_cfg_from_source failed");

	ret = channel->func->config_input(channel, &cfg);
	CHECK_ERROR(ret, return ret, "config_input failed");

	channel->input_cfg = cfg;
	channel->input_params = *param;

	return ret;
}

static int ioc_set_sys_time(struct lxdvb_delivery_channel *channel,
			    struct delivery_ext_system_time_info *param)
{
	log_trace("%s(ch:%d,current_utc_ofs:%d,ptp:%d,leap59:%d,leap61:%d)",
		  __func__, channel->idx, param->current_utc_offset,
		  param->ptp_prepend, param->leap59, param->leap61);

	if (!channel->func->set_system_time)
		return -EIO;

	return channel->func->set_system_time(channel, param);
}

static int ioc_set_time(struct lxdvb_delivery_channel *channel,
			struct delivery_ext_time *param)
{
	log_trace("%s(ch:%d)", __func__, channel->idx);

	if (!channel->func->set_time)
		return -EIO;

	return channel->func->set_time(channel, param);
}

static int ioc_get_time(struct lxdvb_delivery_channel *channel,
			struct delivery_ext_time *param)
{
	if (!channel->func->get_time)
		return -EIO;

	return channel->func->get_time(channel, param);
}

static int ioc_set_clock_recovery(struct lxdvb_delivery_channel *channel,
				  u32 param)
{
	int rc;

	log_noti("%s(ch:%d - %u)", __func__, channel->idx, param);

	if (!channel->func->set_clock_recovery)
		return -EIO;

	rc = channel->func->set_clock_recovery(channel, param);
	if (rc)
		return rc;

	if (param == 1) {
		channel->clock_recovery = true;
	} else {
		channel->clock_recovery = false;
	}

	return 0;
}

static int ioc_set_demod_vers(struct lxdvb_delivery_channel *channel,
			      u32 version)
{
	int ret;

	log_noti("%s(ch:%d,vers:%d)", __func__, channel->idx, version);

	if (!channel->func->set_demod_version)
		return -EIO;

	ret = channel->func->set_demod_version(channel, version);
	if (ret == 0)
		channel->delivery->demod_type = version;

	return ret;
}

static int ioc_start(struct lxdvb_delivery_fh *fh,
		     enum delivery_ext_event event)
{
	struct lxdvb_delivery_channel *channel = fh->channel;
	int ret;

	log_noti("%s(ch:%d,event:%s)", __func__, channel->idx,
		 delivery_event_str(event));

	if (fh->event != DELIVERY_EXT_EVENT_UNSET && (fh->event != event)) {
		log_error("can't change event(%s->%s)",
			  delivery_event_str(fh->event),
			  delivery_event_str(event));
		return -EIO;
	}

	if (event == DELIVERY_EXT_EVENT_DATA_DUMP) {
		ret = channel->func->start_dump(channel);
	} else if (event == DELIVERY_EXT_EVENT_WALL_CLOCK) {
		ret = 0;
	} else {
		log_error("invalid event(%d)", event);
		ret = -EIO;
	}

	if (ret == 0) {
		fh->event = event;
		channel->user_read_size = 0;
	}

	return ret;
}

static int ioc_stop(struct lxdvb_delivery_fh *fh)
{
	struct lxdvb_delivery_channel *channel = fh->channel;
	int ret;

	log_noti("%s(ch:%d,event:%s)", __func__, channel->idx,
		 delivery_event_str(fh->event));

	if (fh->event == DELIVERY_EXT_EVENT_DATA_DUMP) {
		ret = channel->func->stop_dump(channel);
	} else if (fh->event == DELIVERY_EXT_EVENT_WALL_CLOCK) {
		ret = 0;
	} else {
		ret = -EIO;
	}

	if (ret == 0)
		fh->event = DELIVERY_EXT_EVENT_UNSET;

	log_noti("%s done(ret:%d)", __func__, ret);

	return ret;
}

static int ioc_set_adjust_clock_table(struct lxdvb_delivery_channel *channel,
				      int *table, u32 size)
{
	log_noti("%s(ch:%d, table_size:%u)", __func__, channel->idx, size);
	log_warning("set clock adjust table; wall clock will be invalid!!");

	if (!channel->func->set_adjust_clock_table)
		return -EIO;

	return channel->func->set_adjust_clock_table(channel, table, size);
}

static int ioc_set_control(struct lxdvb_delivery_fh *fh,
			   struct delivery_ext_control *control)
{
	struct lxdvb_delivery_channel *channel = fh->channel;
	u32 id = control->id;
	enum delivery_ext_mode mode = fh->mode;
	void *ptr = (void __force *)control->ptr;
	int ret;

	if (id != DELIVERY_EXT_CID_MODE && mode == DELIVERY_EXT_MODE_UNSET) {
		log_error("mode is not set");
		return -EIO;
	}

	switch (id) {
	case DELIVERY_EXT_CID_MODE:
		ret = ioc_set_mode(fh, control->value64);
		break;
	case DELIVERY_EXT_CID_INPUT_SOURCE:
		ret = ioc_set_input_source(channel, ptr);
		break;
	case DELIVERY_EXT_CID_SYSTEM_TIME_INFO:
		ret = ioc_set_sys_time(channel, ptr);
		break;
	case DELIVERY_EXT_CID_CURRENT_TIME:
		ret = ioc_set_time(channel, ptr);
		break;
	case DELIVERY_EXT_CID_CLOCK_RECOVERY_ONOFF:
		ret = ioc_set_clock_recovery(channel, control->value64);
		break;
	case DELIVERY_EXT_CID_DEMOD_VERSION:
		ret = ioc_set_demod_vers(channel, control->value64);
		break;
	case DELIVERY_EXT_CID_START:
		ret = ioc_start(fh, control->value64);
		break;
	case DELIVERY_EXT_CID_STOP:
		ret = ioc_stop(fh);
		break;
	case DELIVERY_EXT_CID_MANIPULATED_WALL_CLOCK:
		ret = ioc_set_adjust_clock_table(channel, ptr, control->size);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}

static int ioc_get_control(struct lxdvb_delivery_fh *fh,
			   struct delivery_ext_control *control)
{
	int ret;

	if (fh->mode == DELIVERY_EXT_MODE_UNSET) {
		log_error("mode is not set");
		return -EIO;
	}

	switch (control->id) {
	case DELIVERY_EXT_CID_CURRENT_TIME:
		ret = ioc_get_time(fh->channel, (void __force *)control->ptr);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}

static int delivery_do_ioctl(void *priv, unsigned int cmd, void *parg)
{
	struct lxdvb_delivery_fh *fh = priv;
	struct lxdvb_delivery_channel *channel = fh->channel;
	int ret;

	if (mutex_lock_interruptible(&channel->mutex))
		return -ERESTARTSYS;

	switch (cmd) {
	case DELIVERY_EXT_S_CTRL:
		ret = ioc_set_control(fh, parg);
		break;
	case DELIVERY_EXT_G_CTRL:
		ret = ioc_get_control(fh, parg);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	mutex_unlock(&channel->mutex);

	if (ret < 0) {
		log_error("command[0x%08x]. magic=0x%02X, num=%d - error %d",
			  cmd, _IOC_TYPE(cmd), _IOC_NR(cmd), ret);
	}
	return ret;
}

static int delivery_get_user_ptr(void *priv, unsigned int cmd, void *arg,
				 struct te_ioctl_ptr_param *param)
{
	int dir;
	struct delivery_ext_control *p;
	const struct delivery_control_param *c;

	switch (cmd) {
	case DELIVERY_EXT_S_CTRL:
	case DELIVERY_EXT_G_CTRL:
		p = arg;
		c = get_delivery_control_param(p->id);
		dir = (cmd == DELIVERY_EXT_S_CTRL) ? _IOC_WRITE : _IOC_READ;

		if (!c) {
			log_error("invalid delivery_ext_control id(%u)", p->id);
			return -EINVAL;
		}

		/* DELIVERY_EXT_CID_MANIPULATED_WALL_CLOCK
		 * debug func and has variable size */
		if (c->size != p->size &&
		    p->id != DELIVERY_EXT_CID_MANIPULATED_WALL_CLOCK) {
			log_error("size %u != %u of delivery_ext_control(%s)",
				  p->size, c->size, c->name);
			return -EINVAL;
		}

		if (!(c->dir & dir)) {
			log_error("invalid command of delivery_ext_control(%s)",
				  c->name);
			return -EINVAL;
		}
		if (p->size > 0) {
			param->user_ptr = te_ioctl_get_user_ptr(p->ptr);
			param->kernel_ptr = (void **)&p->ptr;
			param->size = p->size;
			param->dir = dir;
		}
		break;
	default:
		break;

	}

	return 0;
}

static long delivery_ioctl(struct file *file, unsigned int cmd,
			   unsigned long arg)
{
	return te_ioctl_usercopy(cmd, arg, delivery_do_ioctl,
				 delivery_get_user_ptr, file->private_data);
}

static int delivery_release(struct inode *inode, struct file *file)
{

	struct lxdvb_delivery_fh *fh = file->private_data;
	struct lxdvb_delivery_channel *channel = fh->channel;
	struct te_device *tdev = channel->delivery->tdev;

	log_noti("%s(ch:%d,users:%d)", __func__, channel->idx,
		 channel->dvbdev->users);

	mutex_lock(&channel->mutex);
	if (fh->event == DELIVERY_EXT_EVENT_DATA_DUMP)
		channel->func->stop_dump(channel);
	channel->dvbdev->users--;

	// disable clock recovery if enabled
	if (!channel->dvbdev->users && channel->clock_recovery) {
		log_noti("disable clock recovery(ch:%u)", channel->idx);
		channel->func->set_clock_recovery(channel, 0);
		channel->clock_recovery = false;
	}

	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_DVB_DELIVERY);
	kfree(fh);

	mutex_unlock(&channel->mutex);

	return 0;
}

static int delivery_open(struct inode *inode, struct file *file)
{
	struct dvb_device *dvbdev = file->private_data;
	struct lxdvb_delivery_channel *channel = dvbdev->priv;
	struct lxdvb_delivery_fh *fh;
	struct te_device *tdev = channel->delivery->tdev;

	log_noti("%s(ch:%d,users:%d)", __func__, channel->idx, dvbdev->users);

	fh = kzalloc(sizeof(*fh), GFP_KERNEL);
	if (!fh)
		return -ENOMEM;

	if (mutex_lock_interruptible(&channel->mutex)) {
		kfree(fh);
		return -ERESTARTSYS;
	}
	fh->delivery = channel->delivery;
	fh->channel = channel;
	fh->event = DELIVERY_EXT_EVENT_UNSET;
	file->private_data = fh;

	te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_DVB_DELIVERY);
	dvbdev->users++;

	mutex_unlock(&channel->mutex);

	return 0;
}

static void debug_dump_write(struct delivery_debug_dump *dump,
			     const char __user *data, u32 size)
{
	int rc;

	mutex_lock(&dump->mutex);
	if (dump->running == false || te_hwbuf_error(dump->buf)) {
		mutex_unlock(&dump->mutex);
		return;
	}
	rc = te_hwbuf_cwrite_user(dump->buf, data, size);
	if (rc < 0)
		te_hwbuf_set_error(dump->buf, rc);

	mutex_unlock(&dump->mutex);
}

static ssize_t delivery_read(struct file *file, char __user *buf,
			     size_t count, loff_t *ppos)
{
	struct lxdvb_delivery_fh *fh = file->private_data;
	struct lxdvb_delivery_channel *channel = fh->channel;
	int ret;

	if (fh->event != DELIVERY_EXT_EVENT_DATA_DUMP) {
		log_debug("invalid event(%s)", delivery_event_str(fh->event));
		return -EINVAL;
	}

	ret = channel->func->read_dump(channel, buf, count);
	if (ret > 0) {
		debug_dump_write(&channel->debug_dump, buf, ret);
		channel->user_read_size += ret;
	}

	return ret;
}

static unsigned int delivery_poll(struct file *file,
				  struct poll_table_struct *wait)
{
	struct lxdvb_delivery_fh *fh = file->private_data;
	struct lxdvb_delivery_channel *channel = fh->channel;

	log_debug("%s(ch:%d,%s)", __func__, channel->idx,
		  delivery_event_str(fh->event));

	if (channel->func)
		return channel->func->wait_poll(fh->event, channel, file, wait);

	log_error("(ch:%d) mode was not set", channel->idx);
	return POLLERR;
}

/*--------------------------- DEBUG START ------------------------------------*/
enum debug_status {
	DEBUG_STATUS_PARAM = 0,
	DEBUG_STATUS_CHANNEL,
	DEBUG_STATUS_BUFFER,
	DEBUG_STATUS_MAX
};

#define SHOW_MASK_PARAM		(0x1 << DEBUG_STATUS_PARAM)
#define SHOW_MASK_CHANNEL	(0x1 << DEBUG_STATUS_CHANNEL)
#define SHOW_MASK_BUFFER	(0x1 << DEBUG_STATUS_BUFFER)

#define SHOW_MASK_ALL		0xFFFF
/* DEBUG Functions */
#define dprintf(fmt, args...)	seq_printf(m, fmt, ##args)
#define dprintf1(fmt, args...)	dprintf("     " fmt, ##args)

static void debug_show_params(struct lxdvb_delivery *delivery,
			      struct seq_file *m)
{
	dprintf("PARAMETERS\n");
	dprintf("DELIVERY MODE:");
	dprintf("%-9s \n", delivery_mode_str(delivery->mode));
	if (delivery->mode == DELIVERY_EXT_MODE_ATSC30) {
		dprintf("DEMOD TYPE:");
		dprintf("%-9d \n", delivery->demod_type);
	}
}

static void debug_show_channel(struct lxdvb_delivery *delivery,
			       struct seq_file *m)
{
	struct delivery_ext_source *param;
	int i;
	struct lxdvb_delivery_channel *channel;
	enum te_reg_tpi_port tpi;

	dprintf("CHANNEL INFO\n");
	dprintf("%3s %11s %10s %11s %13s %10s\n", "NUM", "SRC_TYPE", "PORT_NUM",
		"PORT_TYPE", "TE_INPUT_PORT", "TPI");
	for (i = 0; i < delivery->num_channel; i++) {
		channel = &delivery->channels[i];
		param = &channel->input_params;
		tpi = te_input_port_to_reg_tpi_port(channel->input_cfg.port);

		dprintf("%3d %11s %10d %11s %13s %10s\n", i,
			delivery_src_str(param->input_src_type),
			param->input_port_num,
			delivery_port_str(param->input_port_type),
			te_input_port_to_str(channel->input_cfg.port),
			te_reg_tpi_port_to_str(tpi));
	}
}

static void debug_show_buffer(struct lxdvb_delivery *delivery,
			      struct seq_file *m)
{
	struct delivery_dump_dev *d;
	u32 data, size, avail;
	u64 read;
	int i;

	dprintf("BUFFER INFO\n");
	dprintf("%3s %10s %20s %6s %12s %10s\n",
		"NUM", "STATUS", "RANGE", "SIZE", "USAGE", "READ");

	for (i = 0; i < delivery->num_channel; i++) {
		dprintf("%3d", i);
		d = &delivery->channels[i].dump;
		dprintf("%11s", delivery_dump_state_str(d->state));
		if (d->state == DELIVERY_DUMP_STATE_RUNNING) {
			data = (u32)te_hwbuf_addr(&d->data);
			size = te_hwbuf_size(&d->data);
			avail = te_hwbuf_avail_size(&d->data);
			read = delivery->channels[i].user_read_size;
			dprintf("   %08x--%08x", data, data + size);
			dprintf("%7s", te_get_readable_size(size));
			dprintf("%9s(%d%%)", te_get_readable_size(avail),
				(avail * 100) / size);
			dprintf("%11llu", read);
		} else {
			dprintf("%21s %6s %12s %10s", "N/A", "N/A", "N/A",
				"N/A");
		}
		dprintf("\n");
	}
}

static int show_status(struct lxdvb_delivery *delivery, struct seq_file *m,
		       enum debug_status s)
{
	switch (s) {
	case DEBUG_STATUS_PARAM:
		debug_show_params(delivery, m);
		break;
	case DEBUG_STATUS_CHANNEL:
		debug_show_channel(delivery, m);
		break;
	case DEBUG_STATUS_BUFFER:
		debug_show_buffer(delivery, m);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}

static int debug_show_status(struct te_debug_item *item, struct seq_file *m)
{
	unsigned long mask = item->flags;
	struct lxdvb_delivery *delivery = item->private;
	int i, rc;

	for (i = 0; i < DEBUG_STATUS_MAX; i++) {
		if (mask & (0x1 << i)) {
			rc = show_status(delivery, m, i);
			if (!rc) {

			}
		}
	}
	return 0;
}

static const struct te_debug_item_info debug_list[] = {
	DBGITM_SHOW("param", debug_show_status, SHOW_MASK_PARAM),
	DBGITM_SHOW("channel", debug_show_status, SHOW_MASK_CHANNEL),
	DBGITM_SHOW("buffer", debug_show_status, SHOW_MASK_BUFFER),
};

static int debug_dump_start(struct te_dump_device *dev,
			    struct te_dump_handle *h, struct te_dump_cfg *cfg)
{
	struct lxdvb_delivery *delivery = dev->private;
	struct delivery_debug_dump *dump;
	u8 ch = cfg->ch;

	log_noti("%s(ch:%d)", __func__, ch);

	if (ch >= delivery->num_channel) {
		log_error("invalid channel(%d)", ch);
		return -EPERM;
	}

	dump = &delivery->channels[ch].debug_dump;
	if (dump->running == true) {
		log_error("already started");
		return -EBUSY;
	}
	dump->buf = cfg->data;
	dump->running = true;

	h->dev_handle = dump;
	return 0;
}

static void debug_dump_stop(struct te_dump_device *dev,
			    struct te_dump_handle *h)
{
	struct delivery_debug_dump *dump = h->dev_handle;

	log_noti("%s", __func__);

	mutex_lock(&dump->mutex);
	dump->running = false;
	mutex_unlock(&dump->mutex);

	h->dev_handle = NULL;
}

static struct te_dump_device dump_device = {
	.module = TE_DUMP_MODULE_DELIVERY,
	.start = debug_dump_start,
	.stop = debug_dump_stop,
};

static void init_debug(struct lxdvb_device *dev,
		       struct lxdvb_delivery *delivery)
{
	int rc;

	dump_device.private = delivery;
	rc = te_dump_register_device(&dump_device);
	CHECK_ERROR(rc < 0, return, "Error in te_dump_register_device");

	delivery->debug_dir = te_debug_create_dir("delivery", dev->debug_dir);
	if (!delivery->debug_dir) {
		log_error("Error in te_debug_create_dir");
		return;
	}
	debug_create_item_files(debug_list, delivery, delivery->debug_dir);
	return;
}

/*--------------------------- DEBUG END --------------------------------------*/

static const struct file_operations lxdvb_delivery_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = delivery_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = delivery_ioctl,
#endif
	.open = delivery_open,
	.read = delivery_read,
	.poll = delivery_poll,
#if (LINUX_VERSION_CODE < KERNEL_VERSION(5, 19, 0))
	.llseek = no_llseek,
#endif
	.release = delivery_release,
};

static const struct dvb_device delivery_dvbdev = {
	.priv = NULL,
#if defined(CONFIG_MEDIA_CONTROLLER_DVB)
	.name = "dvb-delivery",
#endif
	.fops = &lxdvb_delivery_fops,
};

static void release_delivery_channel(struct lxdvb_delivery_channel *channel)
{
	if (channel->func)
		channel->func->stop_dump(channel);

	dvb_unregister_device(channel->dvbdev);
}

static int init_delivery_channel(struct lxdvb_device *dev,
				 struct lxdvb_delivery_channel *channel)
{
	int ret;

	ret = dvb_register_device(&dev->adapter, &channel->dvbdev,
				  &delivery_dvbdev, channel,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
				  DVB_DEVICE_DELIVERY, 0);
#else
				  DVB_DEVICE_DELIVERY);
#endif
	if (ret) {
		log_error("dvb_register_device failed\n");
	}

	mutex_init(&channel->mutex);
	mutex_init(&channel->debug_dump.mutex);

	return 0;
}

static void init_delivery_dump(struct lxdvb_delivery_channel *channel)
{
	struct delivery_dump_dev *d = &channel->dump;

	d->ch = channel->idx;
	d->state = DELIVERY_DUMP_STATE_IDLE;
	d->mem = channel->delivery->mem;
}

static int dev_init(struct lxdvb_device *dev)
{
	struct lxdvb_delivery *delivery;
	struct lxdvb_delivery_channel *channel;
	struct te_device *tdev = get_te_device(dev);
	struct atsc3_device *atsc3_dev;
	struct lx_atsc3_chip_cfg atsc3_cfg;
	int i, ret, num_channel, size;

	log_noti("%s", __func__);

	atsc3_dev = atsc3_get_device(tdev);
	if (!atsc3_dev) {
		log_error("Not support atsc3 device!");
		return -ENODEV;
	}

	atsc3_get_chip_config(atsc3_dev, &atsc3_cfg);
	num_channel = atsc3_cfg.num_channel;

	size = sizeof(*delivery) + num_channel * sizeof(*channel);
	delivery = devm_kzalloc(&dev->pdev->dev, size, GFP_KERNEL);
	CHECK_ERROR(!delivery, return -ENOMEM, "no memory");

	delivery->demod_type = -1;
	delivery->tdev = tdev;
	delivery->mode = DELIVERY_EXT_MODE_UNSET;
	delivery->num_channel = num_channel;
	delivery->mem = te_mem_open(TE_MEM_SHARED_NAME);
	if (!delivery->mem) {
		log_error("te_mem_open failed\n");
		return -EIO;
	}

	/* channel init */
	for (i = 0; i < num_channel; i++) {
		channel = &delivery->channels[i];
		channel->idx = i;
		channel->delivery = delivery;
		ret = init_delivery_channel(dev, channel);
		if (ret) {
			log_error("init_delivery_channel failed(ch:%d)", i);
			//do something?
		}
		init_delivery_dump(channel);
	}

	init_debug(dev, delivery);

	dev->delivery = delivery;

	return 0;
}

static void dev_release(struct lxdvb_device *dev)
{
	struct lxdvb_delivery *delivery = dev->delivery;
	int i;

	log_noti("%s", __func__);

	for (i = 0; i < delivery->num_channel; i++) {
		release_delivery_channel(&delivery->channels[i]);
	}

	te_mem_close(delivery->mem);

	dev->delivery = NULL;
}

static int dev_suspend(struct lxdvb_device *dev)
{
	struct te_device *tdev = get_te_device(dev);

	te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_DVB_DELIVERY);

	return 0;
}

static int dev_resume(struct lxdvb_device *dev)
{
	struct te_device *tdev = get_te_device(dev);

	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_DVB_DELIVERY);

	return 0;
}

const struct lxdvb_sub_driver lxdvb_delivery_driver = {
	.name = "lxdvb_delivery",
	.init = dev_init,
	.release = dev_release,
	.suspend = dev_suspend,
	.resume = dev_resume,
};
