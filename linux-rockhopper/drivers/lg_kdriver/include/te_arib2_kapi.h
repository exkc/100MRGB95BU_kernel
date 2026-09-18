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
 *  @author 	Yeonju Lee( yeonju.lee@lge.com)
 *  @version	0.1
 *  @date		2017-11-21
 *  @note		Additional information.
 */

#ifndef	_TE_ARIB2_KAPI_H_
#define	_TE_ARIB2_KAPI_H_

#include <linux/types.h>
#include "te_kapi.h"

/**
 * ARIB2 IOCTL Magic number
 */
#define ARIB2_IOC_CORE_MAGIC	'c'
#define ARIB2_IOC_MM_MAGIC	'm'
#define ARIB2_IOC_IO_MAGIC	'i'
#define ARIB2_IOC_FLT_MAGIC	'f'
#define ARIB2_IOC_CLK_MAGIC	'k'

// CORE
#define ARIB2_IOC_GET_CHIPCFG		_IOR (ARIB2_IOC_CORE_MAGIC, 0, LX_ARIB2_CHIP_CFG_T)
#define ARIB2_IOC_GET_NOTIFY		_IOWR(ARIB2_IOC_CORE_MAGIC, 1, LX_ARIB2_NOTIFY_MESSAGE_T)

// Memory management
#define ARIB2_IOC_MM_GETINFO		_IOR (ARIB2_IOC_MM_MAGIC, 0, LX_ARIB2_MEM_INFO_T)
#define ARIB2_IOC_MM_FREE		_IOW (ARIB2_IOC_MM_MAGIC, 1, __u32)
#define ARIB2_IOC_MM_ALLOC		_IOWR(ARIB2_IOC_MM_MAGIC, 2, LX_ARIB2_MEM_T)
#define ARIB2_IOC_MM_CACHE_CTRL		_IOW (ARIB2_IOC_MM_MAGIC, 3, LX_TE_CACHE_CTRL_T)

// I/O
#define ARIB2_IOC_CFG_CHANNEL_INPUT	_IOW (ARIB2_IOC_IO_MAGIC, 0, LX_ARIB2_CHANNEL_INPUT_CFG_T)
#define ARIB2_IOC_DUMP_START		_IO  (ARIB2_IOC_IO_MAGIC, 2)
#define ARIB2_IOC_DUMP_STOP		_IO  (ARIB2_IOC_IO_MAGIC, 3)
#define ARIB2_IOC_SET_TIMEOUT		_IOW (ARIB2_IOC_IO_MAGIC, 4, __u32)

// filter
#define	ARIB2_IOC_FLT_REQUEST		_IOW (ARIB2_IOC_FLT_MAGIC, 0, LX_ARIB2_FLT_REQUEST_PARAM_T)
#define ARIB2_IOC_FLT_CANCEL		_IOW (ARIB2_IOC_FLT_MAGIC, 1, LX_ARIB2_FLT_CANCEL_T)

// Clock
#define ARIB2_IOC_CLK_SET_RECOVERY	_IOW (ARIB2_IOC_CLK_MAGIC, 0, LX_ARIB2_CLOCK_CONTROL_T)
#define ARIB2_IOC_CLK_GET_TIME		_IOR (ARIB2_IOC_CLK_MAGIC, 1, LX_ARIB2_TIME_T)
#define ARIB2_IOC_CLK_SET_TIME		_IOW (ARIB2_IOC_CLK_MAGIC, 2, LX_ARIB2_TIME_T)

#define LX_ARIB2_MAX_NOTIFY_DATA		256	/* 64B * 256 = 16KB */

#define LX_ARIB2_NO_WAIT			0
#define LX_ARIB2_INFINITE_WAIT			(__u32)(-1)
#define LX_ARIB2_INPUT_DATA_WAIT		100

typedef struct lx_arib2_chip_cfg {
	__u8 input_ver;		/* 1:M16+ 2:M16++,O18, 3:M16P3 */
} LX_ARIB2_CHIP_CFG_T;
/*_________________________ BEGIN - I/O ______________________________________*/

typedef enum lx_arib2_mode {
	LX_ARIB2_MODE_TLV = 0,
	LX_ARIB2_MODE_RAW,
	LX_ARIB2_MODE_PVR,
	LX_ARIB2_MODE_DISABLE,
} LX_ARIB2_MODE_T;

typedef struct lx_arib2_channel_input_cfg {
	enum lx_te_input_port port;
	__u8 reset;
	__u8 enable;
} LX_ARIB2_CHANNEL_INPUT_CFG_T;

/*____________________________ END - I/O _____________________________________*/

/**
 * Information of Memory
 * @see ARIB2_IOC_MM_ALLOC
 */
typedef struct lx_arib2_mem {
	__u32 addr;		/* address */
	__u32 size;		/* total size */
} LX_ARIB2_MEM_T;

/**
 * Information of ARIB2 Memory
 * @see ARIB2_IOC_MM_GETINFO
 */
typedef struct lx_arib2_mem_info {
	__u32 addr;		/* address */
	__u32 size;		/* total size */
	__u32 free;		/* free size */
	__u32 avail;		/* max continuous memory size */
} LX_ARIB2_MEM_INFO_T;

/*___________________________ BEGIN - CLK ____________________________________*/

typedef struct lx_arib2_time {
	__u32 sec;
	__u32 fraction;		/* 1/ 2^32 fractions */
	__u32 leap_indicator;
	__u32 latched;
} LX_ARIB2_TIME_T;

typedef enum lx_arib2_clock_recovery {
	LX_ARIB2_CLOCK_RECOVERY_ENABLE = 0,
	LX_ARIB2_CLOCK_RECOVERY_DISABLE,
	LX_ARIB2_CLOCK_RECOVERY_RESET,
} LX_ARIB2_CLOCK_RECOVERY_T;

typedef struct lx_arib2_clock_udp_info {
	__u32 src_ip_v[4];
	__u32 src_ip_m[4];
	__u32 dst_ip_v[4];
	__u32 dst_ip_m[4];

	__u16 src_port_v;
	__u16 src_port_m;
	__u16 dst_port_v;
	__u16 dst_port_m;
} LX_ARIB2_CLOCK_UDP_INFO_T;

typedef struct lx_arib2_clock_control {
	LX_ARIB2_CLOCK_RECOVERY_T cmd;
} LX_ARIB2_CLOCK_CONTROL_T;

/*_____________________________ END - CLK ____________________________________*/

/*____________________________ BEGIN - FILTER ________________________________*/
typedef enum {
	LX_ARIB2_FILTER_TYPE_TLV_SI = 0,
	LX_ARIB2_FILTER_TYPE_MMT_PID,
	LX_ARIB2_FILTER_TYPE_MMT_SI,
	LX_ARIB2_FILTER_TYPE_MMT_AV,
	LX_ARIB2_FILTER_TYPE_MAX
} LX_ARIB2_FLT_TYPE_T;

typedef enum {
	LX_ARIB2_FLT_FLAG_ONESHOT = 0x00000001,
} LX_ARIB2_FLT_FLAG_T;

typedef enum {
	LX_ARIB2_MMT_PID_DATA_SI = 0,
	LX_ARIB2_MMT_PID_DATA_AV,
	LX_ARIB2_MMT_PID_DATA_MAX,
} LX_ARIB2_MMT_PID_DATATYPE_T;

typedef enum {
	LX_ARIB2_NOTIFY_TLV_SI = 0,
	LX_ARIB2_NOTIFY_MMT_SI,
	LX_ARIB2_NOTIFY_MMT_AV,
	LX_ARIB2_NOTIFY_MAX
} LX_ARIB2_NOTIFY_TYPE_T;

typedef enum {
	LX_ARIB2_FLT_STATE_DATAREADY = 0x00000001,	/** data is ready - filter is activated */
	LX_ARIB2_FLT_STATE_OVERFLOW = 0x00000002,	/** Overflow */
	LX_ARIB2_FLT_STATE_DELETED = 0x00000004,	/** deleted due to cancel */
} LX_ARIB2_FLT_STATE_T;

typedef struct {
	__u8 value[8];
	__u8 mask[8];
	__u8 noteq[8];
} LX_ARIB2_FLT_PATTERN_T;

typedef struct {
	__u32 addr;
	__u32 size;
} LX_ARIB2_BUFFER_T;

typedef struct {

	__u16 flags __aligned(8);

	LX_ARIB2_BUFFER_T buf;
	LX_ARIB2_FLT_PATTERN_T pattern;

	union {
		void *priv;
		 TE_COMPAT_SIZER(priv);
	};
} LX_ARIB2_FLT_TLVSI_REQ_T;

typedef struct {
	__u16 packet_id;
	__u16 direct_play;
	LX_ARIB2_MMT_PID_DATATYPE_T data_type;
} LX_ARIB2_FLT_MMTPID_REQ_T;

typedef struct {
	__u16 flags;
	__u16 pidf_idx;		//same as upper index in ATSC3
	__u16 message_id;

	LX_ARIB2_BUFFER_T buf;
	LX_ARIB2_FLT_PATTERN_T pattern;

	union {
		void *priv;
		 TE_COMPAT_SIZER(priv);
	};
} LX_ARIB2_FLT_MMTSI_REQ_T;

typedef struct {
	__u16 pidf_idx;
	__u16 flags;		//TODO:Check necessity
	__u32 reserved_1;

	LX_ARIB2_BUFFER_T buf;
	union {
		void *priv;
		 TE_COMPAT_SIZER(priv);
	};
} LX_ARIB2_FLT_MMTAV_REQ_T;

typedef struct {
	LX_ARIB2_FLT_TYPE_T type __aligned(8);
	union {
		LX_ARIB2_FLT_TLVSI_REQ_T *tlv_si;
		LX_ARIB2_FLT_MMTPID_REQ_T *mmt_pid;
		LX_ARIB2_FLT_MMTSI_REQ_T *mmt_si;
		LX_ARIB2_FLT_MMTAV_REQ_T *mmt_av;

		void *filter;
		 TE_COMPAT_SIZER(filter);
	};
} LX_ARIB2_FLT_REQUEST_PARAM_T;

typedef struct {
	LX_ARIB2_FLT_TYPE_T type;
	__u8 idx;
} LX_ARIB2_FLT_CANCEL_T;

typedef struct {
	__u8 rap_f;
	__u8 timed;
	__u32 mpu_seq_num;

	__u32 item_id;
	__u8 scr_ctrl;

	__u8 scr_init_counter[16];
} LX_ARIB2_MMT_AV_INFO_T;

typedef struct {
	__u8 ch;
	__u8 idx;		/* driver filter index */
	__u8 status;		/* See LX_ARIB2_FLT_STATE_T */
	__u32 rptr;

	__u32 wptr;
	__u32 reserved_0;

	__u64 msec;

	union {
		void *priv;
		 TE_COMPAT_SIZER(priv);
	};

	LX_ARIB2_MMT_AV_INFO_T mmt_av;	// consider union if other filters are needed

} LX_ARIB2_NOTIFY_FILTER_T;

typedef struct {
	LX_ARIB2_NOTIFY_TYPE_T type __aligned(8);
	LX_ARIB2_NOTIFY_FILTER_T filter;
} LX_ARIB2_NOTIFY_DATA_T;

typedef struct {
	__u32 timeout;
	__u32 max_count;

	union {
		LX_ARIB2_NOTIFY_DATA_T *data;
		 TE_COMPAT_SIZER(data);
	};
} LX_ARIB2_NOTIFY_MESSAGE_T;

/*___________________________ END - FILTER ___________________________________*/

#endif				/* _TE_ARIB2_KAPI_H_ */

/** @} */
