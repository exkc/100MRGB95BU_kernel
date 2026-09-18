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
 *  application interface header for pvr device
 *
 *  author		Jihoon Lee (gaius.lee@lge.com)
 *  version		1.1
 *  date		2010.03.20
 *
 *  @addtogroup lg1150_pvr
 *	@{
 */

#ifndef	_TE_PVR_KAPI_H_
#define	_TE_PVR_KAPI_H_

#include <linux/types.h>

#include "te_kapi.h"

#define	PVR_IOC_MAGIC		'a'
#define PVR_IOC_DN_MAGIC	'd'
#define PVR_IOC_UP_MAGIC	'u'
#define	PVR_IOC_MM_MAGIC	'm'

/**
@name PVR IOCTL List
ioctl list for pvr device.

@{
@def PVR_IOC_INIT
Initialize pvr module.
Set PVR to default status.

@def PVR_IOW_DN_CONTROL
Let PVR Module start/stop processing packet from SDEC

@def PVR_IOW_DN_BUF_SET
Setting Ring buffer address to kernel driver.
Kernel driver management ringbuffer write address.

@def PVR_IOR_DN_GET_WRITE_ADD
Give read address to and
get write address from kernel driver.
Kernel driver return buffer status.
Handling both of Stream buffer and index buffer.
Normally, m/w take buffer 96KB by 2n. n is singed number.
Saturn 7 have download size range from 24K to 768K.

@def PVR_IOW_DN_SET_CONFIG
Reserved

@def PVR_IOW_PIE_BUF_SET
Setting PIE buffer address to kernel driver.
Kernel driver management ringbuffer write address.

@def PVR_IOW_PIE_SET_PID
Setting PID and PID Type to PIE Module.
PID Type is MPEG2 TS and Others.
The uiDownChunkPktCount field specify the number of packets in each download chunk. The PIE numbering will restart with this number

@def PVR_IOC_UP_INIT
Initialize PVR module and set buffer address and size.
This function is called when PVR up module is initialize.

@def PVR_IOC_UP_SET_WRITE_PTR
Provide kernel driver upload buffer.
User layer write buffer and let kernel driver knows address and size.
This buffer will be written continuosly. So kernel driver just increase write address.

@def PVR_IOC_UP_CONTROL
PVR Upload module start to processing buffer.
This IOCTL is called after first packet is loaded.
Reset the PVR Up module. Called before being used.

@def PVR_IOR_UP_GET_STATE
Getting current PVR Upload module.
Upper layer ask to kernel driver about current status of upload module.
If kernel driver is ready to receive next buffer, it said ready to upper layer.
If not, it said busy. If upload processing is paused, it said pause."

*/
/*----------------------------------------------------------------------------------------
	IO comand naming rule  : MODULE_IO[R][W]_COMMAND
----------------------------------------------------------------------------------------*/
// General commands
#define	PVR_IOC_INIT			_IO  (PVR_IOC_MAGIC, 0)
#define PVR_IOC_GET_HW_INFO		_IOR (PVR_IOC_MAGIC, 1, LX_PVR_HW_INFO_T)

// Memory Pool
#define PVR_IOC_MM_CACHE_CTRL		_IOW (PVR_IOC_MM_MAGIC, 0, LX_TE_CACHE_CTRL_T)
#define PVR_IOC_MM_ALLOC		_IOWR(PVR_IOC_MM_MAGIC, 1, LX_PVR_MM_ALLOC_T)
#define PVR_IOC_MM_FREE			_IOW (PVR_IOC_MM_MAGIC, 2, LX_PVR_MM_FREE_T)

// Download
#define PVR_IOC_DN_INIT			_IOW (PVR_IOC_DN_MAGIC, 0, LX_PVR_DN_CFG_T)
#define PVR_IOC_DN_CONTROL		_IOW (PVR_IOC_DN_MAGIC, 1, LX_PVR_DN_CONTROL_T)
#define PVR_IOC_DN_GET_BUF_INFO		_IOR (PVR_IOC_DN_MAGIC, 2, LX_PVR_DN_BUF_INFO_T)
#define PVR_IOC_DN_SET_READ_PTR		_IOW (PVR_IOC_DN_MAGIC, 3, LX_PVR_BUF_PTR_T)

#define PVR_IOC_DN_SET_PIE_CFG		_IOW (PVR_IOC_DN_MAGIC, 4, LX_PVR_PIE_CFG_T)
#define PVR_IOC_DN_GET_PIE_BUF_INFO	_IOR (PVR_IOC_DN_MAGIC, 5, LX_PVR_PIE_BUF_INFO_T)
#define PVR_IOC_DN_SET_PIE_READ_PTR	_IOW (PVR_IOC_DN_MAGIC, 6, LX_PVR_BUF_PTR_T)

// Upload
#define PVR_IOC_UP_INIT			_IOW (PVR_IOC_UP_MAGIC, 0, LX_PVR_UP_CFG_T)
#define PVR_IOC_UP_CONTROL		_IOW (PVR_IOC_UP_MAGIC, 1, LX_PVR_UP_CONTROL_T)
#define PVR_IOC_UP_GET_BUF_INFO		_IOR (PVR_IOC_UP_MAGIC, 2, LX_PVR_UP_BUF_INFO_T)
#define PVR_IOC_UP_SET_WRITE_PTR	_IOW (PVR_IOC_UP_MAGIC, 3, LX_PVR_BUF_PTR_T)

/** @} */


#define PVR_DN_PKT_SIZE			192

/* aligned to packet size */
#define PVR_DN_DEFAULT_UNIT_SIZE	(512*PVR_DN_PKT_SIZE)	/* 96KB */

#define PVR_PIE_DETECT_BYTE		3
#define PVR_PIE_DETECT_COUNT		4


/**
 * PVR Module selection
 */
typedef enum {
	LX_PVR_CH_A = 0,
	LX_PVR_CH_B,
	LX_PVR_CH_MAX
} LX_PVR_CH_T;

typedef enum lx_pvr_dn_control_type {
	LX_PVR_DN_START = 0,
	LX_PVR_DN_STOP,

} LX_PVR_DN_CONTROL_TYPE_T;

/**
 * Status of buffer
 * Kernel driver return this buffer status with data.
 * Empty/Full/Ready
 * @see LX_PVR_DN_GET_WRITE_ADD_T
 */
typedef enum lx_pvr_buf_stat {
	LX_PVR_BUF_STAT_READY = 0,	/**< Data is ready */
	LX_PVR_BUF_STAT_EMPTY = 1,	/**< Buffer is empty */
	LX_PVR_BUF_STAT_FULL = 2	/**< Buffer is full!!*/
} LX_PVR_BUF_STAT_T;

/**
 * PID Type
 * PIE module want to know this PID type is MPEG2 TS or not.
 * @see LX_PVR_PIE_PID_T
 */
typedef enum lx_pvr_pie_type {
	LX_PVR_PIE_TYPE_NONE = 0,
	LX_PVR_PIE_TYPE_MPEG2TS,	/**< PID Type is MPEG2 TS */
	LX_PVR_PIE_TYPE_H264TS,		/**< PID Type is MPEG4 H264 TS */
	LX_PVR_PIE_TYPE_HEVCTS,		/**< PID Type is MPEG4 HEVC TS */
	LX_PVR_PIE_TYPE_USER,		/**< User defined pattern */
	LX_PVR_PIE_TYPE_MAX
} LX_PVR_PIE_TYPE_T;

typedef enum lx_pvr_up_control_type {
	LX_PVR_UP_START = 0,
	LX_PVR_UP_STOP,
	LX_PVR_UP_RESET,
	LX_PVR_UP_PAUSE,
	LX_PVR_UP_RESUME,
	LX_PVR_UP_SET_MODE,
	LV_PVR_UP_SET_SPEED,		/**< Set upload speed(bytes/sec) if not using timestamp */
	LX_PVR_UP_SET_TLV,
} LX_PVR_UP_CONTROL_TYPE_T;

typedef enum lx_pvr_up_mode {
	LX_PVR_UPMODE_NORMAL = 0,	/**< Normal Play mode */
	LX_PVR_UPMODE_TRICK_MODE,	/**< Trick Play mode */
	LX_PVR_UPMODE_SLOW,		/**< 0.5x Play mode */
	LX_PVR_UPMODE_FAST2X,		/**< 2x Play mode */
	LX_PVR_UPMODE_MAX
} LX_PVR_UP_MODE_T;

typedef enum lx_pvr_up_dest {
	LX_PVR_UP_DEST_ANY = 0,	/* depends on input channel. do not check ready status 8 */
	LX_PVR_UP_DEST_SDEC_CH0,
	LX_PVR_UP_DEST_SDEC_CH1,
	LX_PVR_UP_DEST_SDEC_CH2,
	LX_PVR_UP_DEST_SDEC_CH3,
	LX_PVR_UP_DEST_SDEC_CH4,
	LX_PVR_UP_DEST_SDEC_CH5,
	LX_PVR_UP_DEST_SDEC_CH6,
	LX_PVR_UP_DEST_SDEC_CH7,
	LX_PVR_UP_DEST_TS_OUT0,
	LX_PVR_UP_DEST_TS_OUT1,
	LX_PVR_UP_DEST_A3_CH0,
	LX_PVR_UP_DEST_ARIB_CH0 = LX_PVR_UP_DEST_A3_CH0,
	LX_PVR_UP_DEST_A3_CH1,
	LX_PVR_UP_DEST_ARIB_CH1 = LX_PVR_UP_DEST_A3_CH1,
	LX_PVR_UP_DEST_A3_CH2,
	LX_PVR_UP_DEST_ARIB_CH2 = LX_PVR_UP_DEST_A3_CH2,
	LX_PVR_UP_DEST_A3_CH3,
	LX_PVR_UP_DEST_MAX,
} LX_PVR_UP_DEST_T;


typedef enum lx_pvr_mem_id {
	LX_PVR_MM_ID_0 = 0,	/* pvr dedicated memory */
	LX_PVR_MM_ID_1,		/* shared memory */
	LX_PVR_MM_ID_MAX,
} LX_PVR_MM_ID_T;

/**
 * Information of Memory
 * @see PVR_IOC_MM_ALLOC
 */
typedef struct {
	LX_PVR_MM_ID_T id;
	__u32 addr;		/* address */
	__u32 size;		/* total size */
} LX_PVR_MM_ALLOC_T;

typedef struct {
	LX_PVR_MM_ID_T id;
	__u32 addr;		/* address */
} LX_PVR_MM_FREE_T;

/**
 * Get H/W information from kernel driver.
 * @see PVR_IOC_GET_HW_INFO
 */
typedef struct lx_pvr_hw_info {
	__u8 num_dndev;		/* number of upload device */
	__u8 num_updev;		/* number of download device */

	__u32 mem_size;		/* pvr ddr memory size in byte */
	__u32 buf_type;		/* will remove. avoid to jeckins build fail */
	__u8 no_pie;		/* not use pie hw module */

	__u8 swap_dn_timestamp;	/* little endian timestamp */
	__u8 fixup_index_error;
	__u8 fix_up_timestamp;	/* fix upload timestamp (M16, M16P Ax) */
} LX_PVR_HW_INFO_T;

/**
 * Data structure for download stream data and index data
 * @see LX_PVR_DN_GET_WRITE_ADD_T
 */
typedef struct lx_pvr_buf_ptr {
	__u32 rptr;		/**< give read address to kernel driver */
	__u32 wptr;		/**< get write address from kernel driver */
} LX_PVR_BUF_PTR_T;

/**
 * Init pvr download module
 * Kernel driver management ringbuffer write address and unit size.
 * @see PVR_IOC_DN_INIT
 */
typedef struct lx_pvr_dn_cfg {
	__u32 src;		/**< Source(sdec channel) */
	__u32 addr;		/**< Start address of buffer */
	__u32 size;		/**< Size of buffer */
	__u32 unit_size;	/**< Size of download chunk */
} LX_PVR_DN_CFG_T;

/**
 * Control pvr download module
 * Let PVR Module start/stop processing packet from SDEC
 * @see PVR_IOC_DN_START, PVR_IOC_DN_STOP
 */
typedef struct {
	enum lx_pvr_dn_control_type type;			/**< START / STOP */

} LX_PVR_DN_CONTROL_T;

/**
 * getting write address from kernel driver.
 * give read address and let kernel driver decide current status.
 * pvr module return stream data and index data concurrently.
 * @see PVR_IOR_DN_GET_WRITE_ADD
 */
typedef struct lx_pvr_buf_info {
	LX_PVR_BUF_PTR_T ptr;
	LX_PVR_BUF_STAT_T status;	/**< buffer status from kernel driver */

} LX_PVR_DN_BUF_INFO_T, LX_PVR_UP_BUF_INFO_T, LX_PVR_PIE_BUF_INFO_T;

typedef struct lx_pvr_pie_pattern {
	__u8 enable;
	__u8 mask[PVR_PIE_DETECT_BYTE];
	__u8 value[PVR_PIE_DETECT_BYTE];
} LX_PVR_PIE_PATTERN_T;

/**
 * Setting PIE to make index file.
 * @see PVR_IOW_PIE_SET_CFG
 */
typedef struct lx_pvr_pie_cfg {
	__u16 pid;			/**< PID which is source of making index file */
	enum lx_pvr_pie_type type;	/**< PID Type */
	__u32 addr;
	__u32 size;
	struct lx_pvr_pie_pattern pattern[PVR_PIE_DETECT_COUNT];
} LX_PVR_PIE_CFG_T;

/**
 * PIE database
 */
typedef enum {
	LX_PVR_IDX_SEQ = 0x01,	/* sequence header */
	LX_PVR_IDX_I_PIC = 0x02,	/* I picture */
	LX_PVR_IDX_SEQ_I_PIC = 0x03,	/* sequence header and  I picture */
	LX_PVR_IDX_P_PIC = 0x04,	/* P picture */
	LX_PVR_IDX_B_PIC = 0x08,	/* B picture */
	LX_PVR_IDX_NONE = 0xFF	/* nothing */
} LX_PVR_INDEX_TYPE_T;

/**
 * PVR Picture index data
 */
typedef struct lx_pvr_pie_data {
	__u32	type	: 2,
		src	: 2,
		offset	:28;
} LX_PVR_PIE_DATA_T;

/**
 * Init pvr upload module
 * Kernel driver management ringbuffer write address and unit size.
 * @see PVR_IOC_DN_INIT
 */
typedef struct lx_pvr_up_cfg {
	__u32 addr;			/**< Start address of buffer */
	__u32 size;			/**< Size of buffer */
	enum lx_pvr_up_dest dest;
	__u8 pkt_len;			/** < Packet length of stream */
	__u8 up_cert[32];
} LX_PVR_UP_CFG_T;

/**
 * Control pvr upload module
 * Let PVR Module start/stop processing packet to SDEC
 * @see PVR_IOC_UP_CONTROL
 */
typedef struct lx_pvr_up_control {
	enum lx_pvr_up_control_type type;	/**< START / STOP */
	__u32 value;
} LX_PVR_UP_CONTROL_T;

#endif				/* _TE_PVR_KAPI_H_ */

/** @} */
