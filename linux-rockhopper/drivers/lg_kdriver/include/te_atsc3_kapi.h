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
 *  atsc3 driver
 *
 *  @author 	Yeonju Lee( yeonju.lee@lge.com)
 *  @version	0.1
 *  @date		2016-03-02
 *  @note		Additional information.
 */

#ifndef	_TE_ATSC3_KAPI_H_
#define	_TE_ATSC3_KAPI_H_

#include <linux/types.h>
#include "te_kapi.h"

/**
 * ATSC3 IOCTL Magic number
 */
#define	ATSC3_IOC_CORE_MAGIC		'c'
#define	ATSC3_IOC_MM_MAGIC		'm'
#define ATSC3_IOC_IO_MAGIC		'i'
#define ATSC3_IOC_FLT_MAGIC		'f'
#define ATSC3_IOC_CLK_MAGIC		'k'

// CORE
#define ATSC3_IOC_GET_CHIPCFG		_IOR (ATSC3_IOC_CORE_MAGIC, 0, LX_ATSC3_CHIP_CFG_T)
#define ATSC3_IOC_GET_NOTIFY		_IOW (ATSC3_IOC_CORE_MAGIC, 1, LX_ATSC3_NOTIFY_MESSAGE_T)

// Memory Management
#define ATSC3_IOC_MM_GETINFO		_IOR (ATSC3_IOC_MM_MAGIC, 0, LX_ATSC3_MEM_INFO_T)
#define ATSC3_IOC_MM_FREE		_IOW (ATSC3_IOC_MM_MAGIC, 1, __u32)
#define ATSC3_IOC_MM_ALLOC		_IOWR(ATSC3_IOC_MM_MAGIC, 2, LX_ATSC3_MEM_T)
#define ATSC3_IOC_MM_CACHE_CTRL		_IOW (ATSC3_IOC_MM_MAGIC, 3, LX_TE_CACHE_CTRL_T)

// I/O
#define ATSC3_IOC_CFG_CHANNEL_INPUT	_IOW (ATSC3_IOC_IO_MAGIC, 0, LX_ATSC3_CHANNEL_INPUT_CFG_T)
#define ATSC3_IOC_CHANNEL_INPUT_STATUS	_IOR (ATSC3_IOC_IO_MAGIC, 1, LX_ATSC3_CHANNEL_INPUT_STATUS_T)
#define ATSC3_IOC_GET_CHANNEL_INPUT_STATUS	ATSC3_IOC_CHANNEL_INPUT_STATUS
#define ATSC3_IOC_SET_DEMOD_TYPE	_IOW (ATSC3_IOC_IO_MAGIC, 2, LX_ATSC3_DEMOD_TYPE_T)

#define ATSC3_IOC_CH_DUMP_START		_IOW (ATSC3_IOC_IO_MAGIC, 3, LX_ATSC3_DUMP_CFG_T)
#define ATSC3_IOC_CH_DUMP_STOP		_IOW (ATSC3_IOC_IO_MAGIC, 4, __u32)
#define ATSC3_IOC_CH_DUMP_GET_INFO	_IOWR(ATSC3_IOC_IO_MAGIC, 5, LX_ATSC3_DUMP_INFO_T)
#define ATSC3_IOC_CH_DUMP_SET_RPTR	_IOW (ATSC3_IOC_IO_MAGIC, 6, LX_ATSC3_DUMP_BUF_PTR_T)

// filter
#define ATSC3_IOC_FLT_REQUEST		_IOW (ATSC3_IOC_FLT_MAGIC, 0, LX_ATSC3_FLT_REQUEST_PARAM_T)
#define ATSC3_IOC_FLT_CANCEL		_IOW (ATSC3_IOC_FLT_MAGIC, 1, LX_ATSC3_FLT_CANCEL_PARAM_T)
#define ATSC3_IOC_FLT_GET_STATUS	_IOW (ATSC3_IOC_FLT_MAGIC, 2, LX_ATSC3_FLT_STATUS_PARAM_T)
#define ATSC3_IOC_FLT_SET_RPTR		_IOW (ATSC3_IOC_FLT_MAGIC, 3, LX_ATSC3_FLT_SET_RPTR_T)

// Clock
#define ATSC3_IOC_CLK_SET_RECOVERY	_IOW (ATSC3_IOC_CLK_MAGIC, 0, LX_ATSC3_CLOCK_RECOVERY_T)
#define ATSC3_IOC_CLK_GET_TIME		_IOR (ATSC3_IOC_CLK_MAGIC, 1, LX_ATSC3_TIME_T)
#define ATSC3_IOC_CLK_SET_TIME_INFO	_IOW (ATSC3_IOC_CLK_MAGIC, 2, LX_ATSC3_SYSTEM_TIME_INFO_T)
#define ATSC3_IOC_CLK_SET_TIME		_IOW (ATSC3_IOC_CLK_MAGIC, 3, LX_ATSC3_TIME_T)
#define ATSC3_IOC_CLK_SET_TAI		ATSC3_IOC_CLK_SET_TIME	/* deprecated - will be removed */
#define ATSC3_IOC_CLK_WAIT_WALLCLOCK	_IOW (ATSC3_IOC_CLK_MAGIC, 4, __u32)

#define LX_ATSC3_MAX_NOTIFY_DATA		256

#define LX_ATSC3_NO_WAIT			0
#define LX_ATSC3_INFINITE_WAIT			(__u32)(-1)

/*________________________ BEGIN - I/O _______________________________________*/

typedef struct lx_atsc3_channel_input_cfg {
	enum lx_te_input_port port;	/**< in  -  input mode of the channel */
	__u8 reset;			/**< in  -  port reset or not */
	__u8 enable;			/**< in  -  Enable/Disable */
} LX_ATSC3_CHANNEL_INPUT_CFG_T;

/**
 * SDEC Get Demod_Conf Register value
 * @see SDEC_IOC_GET_CHANNEL_STATUS
 */
typedef struct lx_atsc3_channel_status {
	enum lx_te_input_port port;
	__u8 enable;		/* Enable/Disable */
	__u32 packet_cnt;
	__u32 err_packet_cnt;
	__u32 packet_len;
	__u32 time;		/* TODO: checkms unit */
} LX_ATSC3_CHANNEL_INPUT_STATUS_T, LX_ATSC3_CHANNEL_STATUS_T;

typedef enum lx_atsc3_demod_type {
	LX_ATSC3_DEMOD_TYPE_A = 0,	/* B17 A0 */
	LX_ATSC3_DEMOD_TYPE_B,	/* B17 B0 */
	LX_ATSC3_DEMOD_TYPE_C,	/* B17 B1 */
	LX_ATSC3_DEMOD_TYPE_D,	/* B17+ */
} LX_ATSC3_DEMOD_TYPE_T;

typedef enum lx_atsc3_decoder_layer {
	LX_ATSC3_DECODER_LAYER_LGC = 0,
	LX_ATSC3_DECODER_LAYER_BB,
	LX_ATSC3_DECODER_LAYER_BB_PLP,
	LX_ATSC3_DECODER_LAYER_ALP,
	LX_ATSC3_DECODER_LAYER_LINKSIGNAL = LX_ATSC3_DECODER_LAYER_ALP,
	LX_ATSC3_DECODER_LAYER_TIME_LGC,
	LX_ATSC3_DECODER_LAYER_NONE
} LX_ATSC3_DECODER_LAYER_T;

typedef struct lx_atsc3_dump_buf {
	__u32 addr;
	__u32 size;
	__u32 unit_size;
} LX_ATSC3_DUMP_BUF_T;

typedef struct lx_atsc3_dump_cfg {
	enum lx_atsc3_decoder_layer layer;
	enum lx_te_input_port port;

	struct lx_atsc3_dump_buf data;
	struct lx_atsc3_dump_buf meta;
} LX_ATSC3_DUMP_CFG_T;

typedef struct lx_atsc3_dump_buf_ptr {
	__u32 data;
	__u32 meta;
} LX_ATSC3_DUMP_BUF_PTR_T;

typedef struct lx_atsc3_dump_info {
	__u8 idx;		//FIXME: deprecated
	__u32 timeout;
	union {
		struct lx_atsc3_dump_buf_ptr *wptr;
		TE_COMPAT_SIZER(wptr);
	};
} LX_ATSC3_DUMP_INFO_T;

/*_______________________ END - I/O __________________________________________*/

typedef struct lx_atsc3_chip_cfg {
	__u8 input_ver;		/* input version 1:M16+ 2:O18,M16++ 3:M16P3 */
	__u8 num_channel;
} LX_ATSC3_CHIP_CFG_T;

typedef struct lx_atsc3_mem {
	__u32 addr;		/* address */
	__u32 size;		/* total size */
} LX_ATSC3_MEM_T;

typedef struct lx_atsc3_mem_info {
	__u32 addr;		/* address */
	__u32 size;		/* total size */
	__u32 free;		/* free size */
	__u32 avail;		/* max continuous memory size */
} LX_ATSC3_MEM_INFO_T;


/*__________________________ BEGIN - FILTER REQUEST __________________________*/

typedef enum {
	LX_ATSC3_UDPF_TYPE_LLS = 0,
	LX_ATSC3_UDPF_TYPE_ROUTE_OBJECT,
	LX_ATSC3_UDPF_TYPE_ROUTE_AV,
	LX_ATSC3_UDPF_TYPE_ROUTE_SLS,
	LX_ATSC3_UDPF_TYPE_MMT_SIGNAL,
	LX_ATSC3_UDPF_TYPE_MMT_AV,
	LX_ATSC3_UDPF_TYPE_MAX,
} LX_ATSC3_UDPF_TYPE_T;

typedef enum {
	LX_ATSC3_FLT_STATE_DATAREADY = 0x00000001,	/**< data is ready - filter is in used */
	LX_ATSC3_FLT_STATE_OVERFLOW = 0x00000002,	/**< Overflowed */
	LX_ATSC3_FLT_STATE_DELETED = 0x00000004		/**< deleted */
} LX_ATSC3_FLT_STATE_T;

typedef enum {
	LX_ATSC3_ROUTE_MODE_GENERAL = 0,
	LX_ATSC3_ROUTE_MODE_MDE = 1,
} LX_ATSC3_ROUTE_MODE_T;

typedef struct {
	__u32 addr;		/* address              */
	__u32 size;		/* total size   */
	__u8 *data;		/* data                 */
} LX_ATSC3_DATA_T;

typedef struct {
	__u32 hi;
	__u32 lo;
} LX_ATSC3_TIMESTAMP_T;

typedef struct {
	__u8
	pt_l		:1,
	pt_h		:1,
	sct_l		:1,
	sct_h		:1,
	reserved	:4;
} LX_ATSC3_TIME_FLAG_T;

typedef struct {
	__u8 version;
	__u8 type;
	__u16 type_extension;
	__u8 format;
	__u8 encoding;
} LX_ATSC3_LINKSIGNAL_INFO_T;

typedef struct {
	__u32 toi;

	LX_ATSC3_ROUTE_MODE_T mode;
	__u8 time_info;

	LX_ATSC3_TIME_FLAG_T flag;

	__u32 object_len;
	__u32 offset;

	LX_ATSC3_TIMESTAMP_T sct;
	LX_ATSC3_TIMESTAMP_T pt;

} LX_ATSC3_ROUTEINFO_T, LX_ATSC3_ROUTE_INFO_T;

typedef struct {
	__u32 movie_fragment_sequence_number;	// movie_fragment_sequence_number
	__u32 sample_number;	// the number of total samples
	__u32 offset;		// offset of the media data of this MFU inside the referenced sample
	__u8 priority;
	__u8 dep_counter;
} LX_MFU_DU_HEADER_T;

typedef struct {
	__u32 message_id;
	__u32 timestamp;
	__u8 rap_flag;
	__u8 mpu_fragment_type;
	__u32 mpu_sequence_number;
	LX_MFU_DU_HEADER_T du_header;
} LX_ATSC3_MMTINFO_T, LX_ATSC3_MMT_INFO_T;

typedef enum {
	LX_ATSC3_NOTIFY_ALP_FILTER = 0,
	LX_ATSC3_NOTIFY_LINKSIGNAL_FILTER = LX_ATSC3_NOTIFY_ALP_FILTER,
	LX_ATSC3_NOTIFY_UDP_FILTER,
	LX_ATSC3_NOTIFY_TYPE_MAX
} LX_ATSC3_MSG_TYPE_T, LX_ATSC3_NOTIFY_TYPE_T;

typedef struct {
	__u8 ch;
	__u8 index;		/* driver filter index */
	__u8 status;		/* status of section filter buffer(Ready/Overflow) @LX_ATSC3_FLT_STATE_T */

	__u32 rptr;
	__u32 wptr;
	__u64 msec;

	union {
		void *priv;	/* private data for application */
		TE_COMPAT_SIZER(priv);
	};
	union {
		LX_ATSC3_LINKSIGNAL_INFO_T linksignal;
		LX_ATSC3_ROUTE_INFO_T route;
		__u32 lls_filter;
		LX_ATSC3_MMT_INFO_T mmt;
	};

} LX_ATSC3_NOTIFY_FILTER_T;

typedef struct {
	LX_ATSC3_NOTIFY_TYPE_T type;	/* type @LX_ATSC3_NOTIFY_TYPE_T */
	LX_ATSC3_NOTIFY_FILTER_T filter;
} LX_ATSC3_MSG_T, LX_ATSC3_NOTIFY_DATA_T;

typedef struct {
	__u32 timeout;
	__u32 max_count;
	union {
		LX_ATSC3_MSG_T *data;	/* out - */
		TE_COMPAT_SIZER(data);
	};
} LX_ATSC3_MSG_PARAM_T, LX_ATSC3_NOTIFY_MESSAGE_T;

typedef struct {
	__u32 value;
	__u32 mask;
	__u32 noteq;
} LX_ATSC3_PATTERN_T;

typedef struct {
	__u32 start;
	__u32 end;
	__u32 rptr;
	__u32 wptr;
} LX_ATSC3_BUFFER_T;

typedef enum {
	LX_ATSC3_FLT_FLAG_ONESHOT = 0x00000001,			/**< One packet mode */
} LX_ATSC3_FLT_FLAG_T;


typedef struct {
	__u8 id;
} LX_ATSC3_FLT_PLP_REQ_T;

typedef struct {
	__u8 up_idx;
	__u16 flags;
	LX_ATSC3_MEM_T buf;
	LX_ATSC3_PATTERN_T pattern;

	__u8 plpid_val;
	__u8 plpid_mask;
	__u8 plpid_noteq;

	union {
		void *priv;
		TE_COMPAT_SIZER(priv);
	};
} LX_ATSC3_FLT_ALP_REQ_T, LX_ATSC3_FLT_LINKSIGNAL_REQ_T;

typedef struct {
	__u8 up_idx;
	__u8 src_ip[4];
	__u8 dst_ip[4];
} LX_ATSC3_FLT_IP_REQ_T;

typedef struct {
	__u8 code_point;
	__u8 fec_payload_id;
	__u16 reserved;
} LX_ATSC3_PAYLOAD_INFO_T;

typedef struct {
	__u32 init_toi;
	__u32 num_start;
} LX_ATSC3_AV_INFO_T;

typedef struct {
	__u32 tsi;
	__u8 ignore_dup;

	/* Optional information for AV gathering */
	LX_ATSC3_AV_INFO_T av;

	__u8 payload_num;
	union {
		LX_ATSC3_PAYLOAD_INFO_T *payload;
		TE_COMPAT_SIZER(payload);
	};
} LX_ATSC3_ROUTE_REQ_T;

typedef struct {
	__u16 packet_id;
	LX_ATSC3_PATTERN_T table;
	LX_ATSC3_PATTERN_T content;
} LX_ATSC3_MMT_REQ_T;

typedef struct {
	__u8 plpid_val;
	__u8 plpid_mask;
	__u8 plpid_noteq;
} LX_ATSC3_LLS_REQ_T;

typedef struct {
	__u8 up_idx;
	__u16 dst_port;
	LX_ATSC3_MEM_T buf;

	LX_ATSC3_PATTERN_T pattern;

	__u16 flags;		//oneshot
	union {
		void *priv;
		TE_COMPAT_SIZER(priv);
	};
	LX_ATSC3_UDPF_TYPE_T type;
	union {
		LX_ATSC3_ROUTE_REQ_T route;
		LX_ATSC3_MMT_REQ_T mmt;
		LX_ATSC3_LLS_REQ_T lls;
	};
} LX_ATSC3_FLT_UDP_REQ_T;

typedef enum {
	LX_ATSC3_FILTER_TYPE_PLP = 0,	//will be removed
	LX_ATSC3_FILTER_TYPE_ALP,
	LX_ATSC3_FILTER_TYPE_LINKSIGNAL = LX_ATSC3_FILTER_TYPE_ALP,
	LX_ATSC3_FILTER_TYPE_IP,
	LX_ATSC3_FILTER_TYPE_UDP,
} LX_ATSC3_FLT_TYPE_T;

typedef struct {
	LX_ATSC3_FLT_TYPE_T type __aligned(8);
	union {
		LX_ATSC3_FLT_PLP_REQ_T *plp;	//will be removed
		LX_ATSC3_FLT_ALP_REQ_T *alp;	//will be removed
		LX_ATSC3_FLT_LINKSIGNAL_REQ_T *linksignal;
		LX_ATSC3_FLT_IP_REQ_T *ip;
		LX_ATSC3_FLT_UDP_REQ_T *udp;
		void *filter;
		TE_COMPAT_SIZER(filter);
	};
} LX_ATSC3_FLT_REQUEST_PARAM_T;

typedef struct {
	__u8 type;
	__u8 idx;				/**< in  -  filter index */
} LX_ATSC3_FLT_CANCEL_PARAM_T;
/*_____________________ END - FILTER REQUEST _________________________________*/

/*____________________ BEGIN - FILTER STATUS _________________________________*/

typedef struct {
	__u8 id;

	__u8 req_num;
	__u32 packet_cnt;
	__u32 cc_err_cnt;
	__u32 extmode_err_cnt;
	__u32 pointer_err_cnt;
	__u32 alp_header_err_cnt;

	LX_ATSC3_MEM_T meta_buf;
	LX_ATSC3_MEM_T data_buf;
} LX_ATSC3_FLT_PLP_STATUS_T;

typedef struct {
	__u8 up_idx;		// will be removed
	__u8 req_num;
	LX_ATSC3_PATTERN_T filter;
	LX_ATSC3_BUFFER_T buffer;
	__u16 flags;
	__u32 ovf_cnt;
} LX_ATSC3_FLT_ALP_STATUS_T, LX_ATSC3_FLT_LINKSIGNAL_STATUS_T;

typedef struct {
	__u8 up_idx;		// will be removed
	__u8 req_num;
	LX_ATSC3_BUFFER_T buffer;
	__u32 ovf_cnt;
	__u8 src_ip[4];
	__u8 dst_ip[4];
} LX_ATSC3_FLT_IP_STATUS_T;

typedef struct {
	__u32 tsi;
	__u8 ignore_dup;
	__u32 init_toi;
	__u32 num_start;
	//payload, payload_num?
} LX_ATSC3_ROUTE_STATUS_T;

typedef struct {
	__u16 packet_id;
	LX_ATSC3_PATTERN_T table;
	LX_ATSC3_PATTERN_T content;
} LX_ATSC3_MMT_STATUS_T;

typedef struct {
	__u8 up_idx;
	__u16 flags;
	__u16 dst_port;
	LX_ATSC3_BUFFER_T buffer;
	LX_ATSC3_PATTERN_T pattern;

	/* ipc start */
	__u8 req_num;
	__u8 is_mde;
	__u32 ovf_cnt;
	/* ipc enc */

	LX_ATSC3_UDPF_TYPE_T type;
	union {
		LX_ATSC3_ROUTE_STATUS_T route;
		LX_ATSC3_MMT_STATUS_T mmt;
	};
} LX_ATSC3_FLT_UDP_STATUS_T;

typedef struct {
	LX_ATSC3_FLT_TYPE_T type;
	__u8 idx;		/**< in  -  filter index */
	union {
		LX_ATSC3_FLT_PLP_STATUS_T *plp;
		LX_ATSC3_FLT_LINKSIGNAL_STATUS_T *linksignal;
		LX_ATSC3_FLT_IP_STATUS_T *ip;
		LX_ATSC3_FLT_UDP_STATUS_T *udp;
		void *status;
		TE_COMPAT_SIZER(status);
	};
} LX_ATSC3_FLT_STATUS_PARAM_T;

/*_________________________ END - FILTER STATUS ______________________________*/

typedef struct {
	LX_ATSC3_FLT_TYPE_T type;
	__u8 idx;
	__u32 rptr;
} LX_ATSC3_FLT_SET_RPTR_T;

/*___________________________ BEGIN - CLOCK __________________________________*/

typedef enum lx_atsc3_clock_recovery {
	LX_ATSC3_CLOCK_RECOVERY_ENABLE = 0,
	LX_ATSC3_CLOCK_RECOVERY_DISABLE,
	LX_ATSC3_CLOCK_RECOVERY_RESET,
} LX_ATSC3_CLOCK_RECOVERY_T;

typedef struct lx_atsc3_time {
	__u32 sec;		/* seconds */
	__u32 nsec;		/* nanoseconds */
	__u8 wall_clock;	/* whether wallclock is latched or not */
} LX_ATSC3_TIME_T;

typedef struct lx_atsc3_system_time_info {
	__u8 current_utc_offset;
	__u16 ptp_prepend;
	__u8 leap59;
	__u8 leap61;
} LX_ATSC3_SYSTEM_TIME_INFO_T;

/*_________________________ END - CLOCK ______________________________________*/

#endif				/* _TE_ATSC3_KAPI_H_ */

/** @} */
