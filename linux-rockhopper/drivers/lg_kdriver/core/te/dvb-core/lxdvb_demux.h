/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2018 by LG Electronics Inc.
 *
 * Parts of this file were based on sources as follows:
 *
 * dmxdev.h
 *
 * Copyright (C) 2000 Ralph Metzler & Marcus Metzler
 *                    for convergence integrated media GmbH
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

#ifndef _LXDVB_DEMUX_H_
#define _LXDVB_DEMUX_H_

#include <linux/version.h>
#include <linux/types.h>
#include <linux/spinlock.h>
#include <linux/kernel.h>
#include <linux/time.h>
#include <linux/timer.h>
#include <linux/wait.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/dvb/dmx.h>
#include <linux/dvbv5-ext/dvbv5-ext-demux.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#include <media/dvbdev.h>
#else
#include "dvbdev.h"
#endif

#include <lg1k/te/sdec.h>
#include <lg1k/te/mem.h>

#include "lxdvb_proc.h"

/**
 * DEBUG_DMX_BUFFER:
 *	monitor demux filter buffer usage status
 * USE_DMX_FILTER_DIRECT_BUFFER:
 *	allocate single h/w buffer. it can reduce total memory usage but
 *	needs more h/w memory buffer, and it is not easy to handle errors
 *	likes overflow.
 * USE_DMX_SDEC_ONESHOT_MODE:
 *	enable MCU filter oneshot mode. if message buffer(ipc or callback)
 *	overflow happens, there's no way to receive data.
 */

//#define DEBUG_DMX_BUFFER
//#define USE_DMX_FILTER_DIRECT_BUFFER
//#define USE_DMX_SDEC_ONESHOT_MODE

#define DMX_DRV_VER		0x100
#define DEMUX_MAX_FILTER	(64 + 32)
#define TSHEADER_MAX_FILTER	8
#define DMX_SWFILTER_SIZE	(DMX_FILTER_SIZE + 2)

/**
 * enum lxdvb_dmx_filter_type - type of demux filter type.
 *
 * @DEMUX_FILTER_TYPE_NONE:	no filter set.
 * @DEMUX_FILTER_TYPE_SEC:	section filter.
 * @DEMUX_FILTER_TYPE_PES:	Program Elementary Stream (PES) filter.
 */
enum lxdvb_dmx_filter_type {
	DEMUX_FILTER_TYPE_NONE,
	DEMUX_FILTER_TYPE_SEC,
	DEMUX_FILTER_TYPE_PES,
	DEMUX_FILTER_TYPE_TEMI,
};


/**
 * enum lxdvb_dmx_filter_state - state machine for the dmxdev.
 *
 * @DEMUX_FILTER_STATE_FREE:		indicates that the filter is freed.
 * @DEMUX_FILTER_STATE_ALLOCATED:	indicates that the filter was allocated
 *				to be used.
 * @DEMUX_FILTER_STATE_SET:		indicates that the filter parameters are set.
 * @DEMUX_FILTER_STATE_GO:		indicates that the filter is running.
 * @DEMUX_FILTER_STATE_DONE:		indicates that a packet was already filtered
 *				and the filter is now disabled.
 *				Set only if %DMX_ONESHOT. See
 *				&dmx_sct_filter_params.
 * @DEMUX_FILTER_STATE_TIMEDOUT:	Indicates a timeout condition.
 */
enum lxdvb_dmx_filter_state {
	DEMUX_FILTER_STATE_FREE,
	DEMUX_FILTER_STATE_ALLOCATED,
	DEMUX_FILTER_STATE_SET,
	DEMUX_FILTER_STATE_GO,
	DEMUX_FILTER_STATE_DONE,
	DEMUX_FILTER_STATE_TIMEDOUT,
	DEMUX_FILTER_STATE_ERROR,
};

enum lxdvb_dmx_desc_algo_mode {
	DEMUX_ALGO_LEGACY,
	DEMUX_ALGO_ECP,
	DEMUX_ALGO_XCAS,
	DEMUX_ALGO_NAGRA, //experimental
};

struct lxdvb_demux;
struct lxdvb_dmx_channel;
struct lxdvb_dmx_filter;

struct dmx_pid_filter {
	u8 idx;
	enum lxdvb_dmx_filter_state state;
	enum lx_sdec_payload_type payload_type;
	u16 pid;
	u32 dest_mask;	/* mask of enum lx_sdec_pid_filter_dest */

	struct lxdvb_dmx_channel *channel;
	struct sdec_pid_filter *dev;

	/* List of struct lxdvb_dmx_filter for parameters to set h/w filter */
	struct list_head dvb_filters;
//	struct list_head stream_filters;

	/* List entry for all free filters in
	 * struct lxdvb_demux.free_pid_filters or allocated filters for the
	 * channel in struct lxdvb_dmx_channel.pid_filters */
	struct list_head entry;
};


struct dmx_section_swfilter {
	u8 value[DMX_SWFILTER_SIZE];
	u8 equal_mode[DMX_SWFILTER_SIZE];
	u8 noteq_mode[DMX_SWFILTER_SIZE];
	u8 do_noteq;
};

struct dmx_stream_filter {
	u8 idx;
	enum lxdvb_dmx_filter_state state;
	enum lx_sdec_stream_type stream_type;
	struct dmx_pid_filter *pid_filter;

	struct lxdvb_dmx_channel *channel;
	struct sdec_stream_filter *dev;
	struct te_hwbuf hbuf;
	struct te_pktbuf pbuf;

	struct dmx_section_swfilter *swfilter;
	bool check_crc;
	bool oneshot;

	struct te_timer *timer;

	/* List entry for all free filters in
	 * struct lxdvb_demux.free_stream_filters or allocated filters for
	 * the channel in struct lxdvb_dmx_channel.stream_filters */
	struct list_head entry;

	u32 errors;
	unsigned long received;

#ifdef DEBUG_DMX_BUFFER
	u32 max_used_size;
	u32 max_used_dev_size;
#endif
};

struct dmx_temi_filter {
	u8 idx;
	enum lxdvb_dmx_filter_state state;
	struct dmx_pid_filter *pid_filter;

	struct lxdvb_dmx_channel *channel;
	struct sdec_temi_filter *dev;

	struct te_pktbuf pbuf;

	bool oneshot;
	struct te_timer *timer;

	u32 errors;
	unsigned long received;

	/* List entry for all free filters in
	 * struct lxdvb_demux.free_temi_filters or allocated filters for
	 * the channel in struct lxdvb_dmx_channel.temi_filters */
	struct list_head entry;
};

struct dmx_tsh_filter {
	u8 idx;
	enum lxdvb_dmx_filter_state state;
	struct lxdvb_dmx_filter *dvb_filter;
	u16 pid;
	u8 data[4];
	u8 done;

	/* List entry in struct dmx_tsh_filter_scheduler.wait_list which is
	 * used to schedule ts_header h/w filter */
	struct list_head node;
	struct dmx_tsh_filter_scheduler *sched;
};

struct dmx_tsh_filter_scheduler {
	struct mutex mutex;
	struct task_struct *thread;
	u32 users;

	struct dmx_tsh_filter *runner;
	struct sdec_tsh_filter *dev;
	wait_queue_head_t wq;
	unsigned long flags;
	struct completion woken;

	/* List of all waiting struct dmx_tsh_filter */
	struct list_head wait_list;

	u8 data[4];
};

struct dmx_input_cfg {
	enum lx_te_input_port port;
	enum lx_te_input_mode mode;
};

struct dmx_pcr {
	bool enabled;
	struct lxdvb_dmx_filter *filter;

	bool is_virtual; //virtual pcr filter
	struct lxdvb_dmx_channel *sdt_channel;
};

struct dmx_usb_ci {
	bool enabled;
};

#define DEMUX_FILTER_FLAG_CHILD		(0x1 << 0)
/**
 * struct lxdvb_dmx_filter - digital TV dmxdev filter
 *
 * @params:	dmxdev filter parameters. Depending on the feed type, it
 *		can be:
 *		for section filter: a &struct dmx_sct_filter_params @sec
 *		embedded struct;
 *		for a TS filter: a &struct dmx_pes_filter_params @pes
 *		embedded struct.
 * @type:	type of the dmxdev filter, as defined by &enum dmxdev_type.
 * @state:	state of the dmxdev filter, as defined by &enum dmxdev_state.
 * @demux:	pointer to &struct lxdvb_demux.
 * @buffer:	an embedded &struct dvb_ringbuffer buffer.
 * @mutex:	protects the access to &struct dmxdev_filter.
 * @buf_size:	buffer size requested by user
 * @pbuf:	actual packet buffer
 * @read_size:	accumulated read size by read system call
 */
struct lxdvb_dmx_filter {
	u8 idx;
	bool desc_enable;
	bool xcas_desc_enable;
	bool nagra_desc_enable;
	enum lxdvb_dmx_filter_state state;
	enum lxdvb_dmx_filter_type type;

	struct lxdvb_dmx_channel *channel;

	/* filter parameters depending on the dmx_filter_type */
	union {
		struct dmx_sct_filter_params sec;
		struct dmx_pes_filter_params pes;
	} params;

	u16 pid;
	u16 flags;
	enum lx_sdec_pid_filter_dest dest;
	enum lx_sdec_payload_type payload_type;
	enum lx_sdec_stream_type stream_type;

	struct mutex mutex;

	struct dmx_pid_filter *pid_filter;
	struct dmx_stream_filter *stream_filter;
	struct dmx_temi_filter *temi_filter;

	/* Child filter only used for DMX_EXT_CID_ADD_PID */
	struct lxdvb_dmx_filter *child;

	/* List entry in dmx_pid_filter.dvb_filters which is used to get
	 * the h/w filter destination value */
	struct list_head pid_filter_entry;

	u32 buf_size;
	struct te_pktbuf *pbuf;

	u32 read_size;
};


/**
 * struct lxdvb_dmx_fh - file handle for demux device
 *
 */
struct lxdvb_dmx_fh {
	struct lxdvb_dmx_channel *channel;
	struct lxdvb_dmx_filter *filter;
	struct dmx_tsh_filter *tsh_filter;
};

/**
 * struct lxdvb_dmx_channel - Describes a demux channel device.
 *
 * @dvbdev:		pointer to &struct dvb_device associated with
 *			the demux device node.
 * @filter:		pointer to &struct dmxdev_filter.
 * @demux:		pointer to &struct dmx_demux.
 * @num_filter:		number of filters.
 * @exit:		flag to indicate that the demux is being released.
 * @dvr_buffer:		embedded &struct dvb_ringbuffer for DVB output.
 * @mutex:		protects the usage of this structure.
 * @lock:		protects access to &dmxdev->filter->data.
 */
struct lxdvb_dmx_channel {
	u8 idx;
	struct lxdvb_demux *dmx;
	struct sdec_channel *dev;
	struct dvb_device *dvbdev;
	bool exit;

	struct te_debug_dir *debug_dir;
	u16 num_filter;
	struct lxdvb_dmx_filter *filter;

	/* list of all allocated struct dmx_pid_filter for this channel */
	struct list_head pid_filters;

	/* list of all allocated struct dmx_stream_filter for this channel */
	struct list_head stream_filters;
	struct list_head temi_filters;

	u16 num_tsh_filter;
	struct dmx_tsh_filter *tsh_filter;
	struct dmx_tsh_filter_scheduler tsh_filter_sched;
	struct dmx_pcr pcr;
	struct dmx_usb_ci usb_ci;

	struct dmx_input_cfg input_cfg;
	struct dmx_ext_source input_params;

	enum dmx_ext_dscrmb_type desc_type;
	enum lx_sdec_desc_mode desc_mode;
	enum lxdvb_dmx_desc_algo_mode algo_mode;

	int dvr_idx;
	struct lxdvb_dmx_channel *sdt; // for register SDT_PORT_INFO
};

struct lxdvb_dmx_param {
	enum dmx_platform platform;
	enum dmx_country country;
	u32 model_no;
	u8 num_of_tuner;
};

/**
 * struct lxdvb_demux - Describes a digital TV demux device.
 *
 * @dvbdev:		pointer to &struct dvb_device associated with
 *			the demux device node.
 * @dvr_dvbdev:		pointer to &struct dvb_device associated with
 *			the dvr device node.
 * @filter:		pointer to &struct dmxdev_filter.
 * @demux:		pointer to &struct dmx_demux.
 * @filternum:		number of filters.
 * @capabilities:	demux capabilities as defined by &enum dmx_demux_caps.
 * @exit:		flag to indicate that the demux is being released.
 * @dvr_orig_fe:	pointer to &struct dmx_frontend.
 * @dvr_buffer:		embedded &struct dvb_ringbuffer for DVB output.
 * @mutex:		protects the usage of this structure.
 * @lock:		protects access to &dmxdev->filter->data.
 *
 */
struct lxdvb_demux {
	spinlock_t lock;
	struct te_debug_dir *debug_dir;
	struct lxdvb_proc_dir *proc_dir;
	struct te_device *tdev;
	struct sdec_device *sdev;

	struct te_mem_ctx *mem;

	struct lxdvb_dmx_param param;

	u16 num_channel;
	u16 num_pid_filter;
	u16 num_stream_filter;
	u16 num_temi_filter;

	struct mutex mutex; //for sys call
	struct dmx_pid_filter *pid_filters;
	struct dmx_stream_filter *stream_filters;
	struct dmx_temi_filter *temi_filters;

	/* list of all free struct dmx_pid_filter */
	struct list_head free_pid_filters;

	/* list of all free struct dmx_stream_filter */
	struct list_head free_stream_filters;
	struct list_head free_temi_filters;

	struct lxdvb_dmx_channel channels[0];
};

const char *lxdvb_demux_platform_str(enum dmx_platform platform);
const char *lxdvb_demux_country_str(enum dmx_country country);
const char *lxdvb_demux_output_str(enum dmx_output output);
const char *lxdvb_demux_pes_type_str(enum dmx_ts_pes type);
const char *lxdvb_demux_src_type_str(enum dmx_src_type type);
const char *lxdvb_demux_port_type_str(enum dmx_ext_port_type type);
const char *lxdvb_demux_filter_state_str(enum lxdvb_dmx_filter_state state);
const char *lxdvb_demux_filter_type_str(enum lxdvb_dmx_filter_type type);

/* DVR related function */
int lxdvb_demux_set_dvr_idx(struct lxdvb_dmx_channel *channel, int idx);
int lxdvb_demux_check_usb_ci_recording(struct lxdvb_dmx_channel *channel,
				       bool *detect_usb);
int lxdvb_demux_set_usb_ci_mode(struct lxdvb_dmx_channel *channel, bool en);

/* DESC related function */
int lxdvb_demux_desc_disable_all_pid(struct lxdvb_dmx_channel *channel);

#endif				/* _TE_DVB_DEMUX_H_ */
