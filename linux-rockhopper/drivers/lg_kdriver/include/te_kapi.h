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

/** @file te_kadp.h
 *
 *  Kernel driver for TE.
 *
 *  @author		Kyungseok Hyun ( ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2015-01-05
 *  @note       Additional information.
 */

#ifndef	_TE_KAPI_H_
#define	_TE_KAPI_H_

#include <linux/types.h>

#ifdef	__KERNEL__
#include <linux/kernel.h>
#else
#ifndef unlikely
#define unlikely(x) __builtin_expect((x),0)
#endif
#ifndef __user
#define __user
#endif
#endif

#define TE_MAX_MCU_COUNT	2

#define	TE_IOC_MAGIC		't'

#define TE_IOC_MCU_FWLOAD		_IOW (TE_IOC_MAGIC, 0, LX_TE_MCU_FWLOAD_T)
#define TE_IOC_MCU_FW_CHECK_N_LOAD	_IOW (TE_IOC_MAGIC, 1, LX_TE_MCU_FWLOAD_T)

#define TE_IOC_GET_REG			_IOWR(TE_IOC_MAGIC, 2, LX_TE_REG_T)
#define TE_IOC_SET_REG			_IOW (TE_IOC_MAGIC, 3, LX_TE_REG_T)

#define TE_IOC_SET_ENGINE		_IOW (TE_IOC_MAGIC, 4, LX_TE_STREAM_TYPE_T)

#define TE_IOC_GET_MCU_STATUS		_IOR (TE_IOC_MAGIC, 5, struct lx_te_get_mcu_status)
#define TE_IOC_MCU_DEBUG		_IOW (TE_IOC_MAGIC, 6, LX_TE_MCU_DEBUG_T) // Deprecated

#define TE_IOC_CFG_TPI			_IOW (TE_IOC_MAGIC,10, LX_TE_TPI_CFG_PARAM_T)
#define TE_IOC_GET_TPI_STATUS		_IOW (TE_IOC_MAGIC,11, LX_TE_TPI_STATUS_PARAM_T)
#define TE_IOC_CONNECT_INPUT_PORT	_IOW (TE_IOC_MAGIC,12, LX_TE_INPUT_PORT_CONNECT_T)


/*-----------------------------------------------------------------------------
	Macro Definitions
------------------------------------------------------------------------------*/
#define TE_COMPAT_SIZER(a)		__u64	__compat_sizer_##a

#ifndef __aligned
#define	__aligned(x)			__attribute__((aligned(x)))
#endif

#define	TE_CHECK_IF_ERROR(__checker, __if_output, __if_action, fmt, args...) \
do { \
	if (unlikely(__checker)) { \
		__if_output(fmt,##args); \
		__if_action; \
	} \
} while(0)

static inline __u32 TE_GET32(const void *p)
{
	__u8 *ptr = (__u8 *) p;
	return ptr[0] << 24 | ptr[1] << 16 | ptr[2] << 8 | ptr[3] << 0;
}

static inline __u32 TE_GET24(const void *p)
{
	__u8 *ptr = (__u8 *) p;
	return ptr[0] << 16 | ptr[1] << 8 | ptr[2] << 0;
}

static inline __u32 TE_GET16(const void *p)
{
	__u8 *ptr = (__u8 *) p;
	return ptr[0] << 8 | ptr[1] << 0;
}

static inline __u64 TE_GET64(const void *p)
{
	__u8 *ptr = (__u8 *)p;
	return (__u64)TE_GET32(ptr) << 32 | TE_GET32(&ptr[4]);
}

static inline void TE_PUT32(const void *p, __u32 val)
{
	__u8 *ptr = (__u8 *) p;
	ptr[0] = (val >> 24) & 0xFF;
	ptr[1] = (val >> 16) & 0xFF;
	ptr[2] = (val >> 8) & 0xFF;
	ptr[3] = (val >> 0) & 0xFF;
}

static inline void TE_PUT16(const void *p, __u16 v)
{
	__u8 *ptr = (__u8 *) p;

	ptr[0] = (v >> 8) & 0xFF;
	ptr[1] = (v >> 0) & 0xFF;
}

static inline __u32 TE_SWAP32(__u32 val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0x00FF00FF);
	return (val << 16) | (val >> 16);
}

static inline __u16 TE_SWAP16(__u16 val)
{
	return (val << 8) | (val >> 8);
}

#ifndef MAX
#define MAX(a, b)		((a) < (b) ? (b) : (a))
#endif

#ifndef MIN
#define MIN(a, b)		((a) < (b) ? (a) : (b))
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a)	(sizeof(a)/sizeof(a[0]))
#endif

/* Macro to convert to string */
#define TE_TO_STR(x)	#x
#define TE_MK_STR(x)	TE_TO_STR(x)

/*-----------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/

/*________________________________ BEGIN - MM ________________________________*/

/**
 * Information of Memory
 * @see TE_IOC_MM_ALLOC
 */
typedef struct lx_te_mem {
	__u32 addr;		/* address */
	__u32 size;		/* total size */
} LX_TE_MEM_T;

/**
 * Information of SDEC Memory
 * @see TE_IOC_MM_GETINFO
 */
typedef struct lx_te_mem_info {
	__u32 addr;		/* address */
	__u32 size;		/* total size */
	__u32 free;		/* free size */
	__u32 avail;		/* max continuous memory size */
} LX_TE_MEM_INFO_T;

typedef enum lx_te_mem_type {
	LX_TE_MEM_UNCACHED = 0,
	LX_TE_MEM_CACHED,
	LX_TE_MEM_TYPE_MAX
} LX_TE_MEM_TYPE_T;

/**
 * cache control for te memory
 *
 */
typedef enum lx_te_cache_op {
	LX_TE_CACHE_OP_INVAL = 0x0,
	LX_TE_CACHE_OP_CLEAN,
} LX_TE_CACHE_OP_T;

typedef struct lx_te_cache_ctrl {
	enum lx_te_cache_op op;

	__u32 paddr;				/**< physical address */
	union {
		void *vaddr;			/**< virtual address returned by mmap */
		 TE_COMPAT_SIZER(vaddr);
	};
	__u32 size;				/**< memory length */
} LX_TE_CACHE_CTRL_T;

/*______________________________ END - MM ____________________________________*/

/*_____________________________ BEGIN - MCU __________________________________*/

typedef enum lx_te_mcu_debug_type {
	LX_TE_MCU_DEBUG_LOGMASK = 0x0,
	LX_TE_MCU_DEBUG_FLTSTATUS,
	LX_TE_MCU_DEBUG_IBUF_FLEVEL,
	LX_TE_MCU_DEBUG_EBUF_FLEVEL,
} LX_TE_MCU_DEBUG_TYPE_T;

/**
 * Load mcu f/w binary
 * @see TE_IOC_MCU_FWLOAD
 */
typedef struct lx_te_mcu_fwload {
	__u8 mcu __aligned(8);		/**< mcu(0 or 1) */
	union {
		const void *data;	/**< data  */
		 TE_COMPAT_SIZER(data);
	};
	__u32 size;			/**< size  */
} LX_TE_MCU_FWLOAD_T;

typedef struct lx_te_mcu_debug { // Deprecated
	enum lx_te_mcu_debug_type type;
	__u8 mcu;			/**< mcu(0 or 1) */
	__u32 value[4];			/**< common value including logmask and loglevel */
} LX_TE_MCU_DEBUG_T;

enum lx_te_mcu_status {
	LX_TE_MCU_STATUS_NOT_READY = 0,
	LX_TE_MCU_STATUS_LOADED,
	LX_TE_MCU_STATUS_READY
};

struct lx_te_mcu_info {
	enum lx_te_mcu_status status;
	__u32 fw_ver;
};

struct lx_te_get_mcu_status {
	__u8 count; //mcu count;
	__u8 include_demod;
	struct lx_te_mcu_info mcu[TE_MAX_MCU_COUNT];
};

/*_______________________________ END - MCU __________________________________*/

/*_____________________________ BEGIN - REG __________________________________*/

/**
 * blocks of TE registers
 * used for reading/writing registers for debugging
 * @see LX_TE_REG_T
 */
typedef enum lx_te_block {
	LX_TE_BLOCK_NONE,
	LX_TE_BLOCK_TOP,	/* TOP */
	LX_TE_BLOCK_TPI,	/* External Input Port */
	LX_TE_BLOCK_DEMOD = LX_TE_BLOCK_TPI,
	LX_TE_BLOCK_FE_ENGINE,	/* FE Engine - M16 */
	LX_TE_BLOCK_FE_PIDF,	/* FE PIDF */
	LX_TE_BLOCK_FE_TSBUF,	/* FE TSBUF */
	LX_TE_BLOCK_FE_STCC,	/* FE STCC */
	LX_TE_BLOCK_BE_TOP,	/* BE TOP */
	LX_TE_BLOCK_UPLOAD0,	/* UPLOAD0 */
	LX_TE_BLOCK_UPLOAD1,	/* UPLOAD1 */
	LX_TE_BLOCK_CIPLUS,	/* CIPLUS */
	LX_TE_BLOCK_A3,		/* ATSC3 */
	LX_TE_BLOCK_ARIB2,	/* ARIB2 */
	LX_TE_BLOCK_DUMPER,	/* DUMPER */
	LX_TE_BLOCK_MCU0,	/* MCU0 */
	LX_TE_BLOCK_MCU1,	/* MCU1 */
	LX_TE_BLOCK_DSC0,
	LX_TE_BLOCK_DSC1,
	LX_TE_BLOCK_MAX,
} LX_TE_BLOCK_T;

/**
 * read/write register with direct address
 */
typedef struct {
	enum lx_te_block block;		/**< in  -  TE Block */
	__u32 offset;			/**< in  -  offset of register from block start address */
	__u32 value;			/**< in/out -  value of register written by kernel drvier */
} LX_TE_REG_T;

/*________________________ END - REG _________________________________________*/

typedef enum lx_te_pcap_linktype {
	LX_TE_PCAP_LINKTYPE_ETHERNET = 1,
	/* 147 ~ 162 are reserved for private use */
	LX_TE_PCAP_LINKTYPE_LGC = 150,
	LX_TE_PCAP_LINKTYPE_BB = 151,
	LX_TE_PCAP_LINKTYPE_ALP = 152,

	LX_TE_PCAP_LINKTYPE_LMT = 153,
	LX_TE_PCAP_LINKTYPE_UDP = 154,
	LX_TE_PCAP_LINKTYPE_ROUTE = 155,
	LX_TE_PCAP_LINKTYPE_MMT = 156,

	LX_TE_PCAP_LINKTYPE_IPV4 = 228,
} LX_TE_PCAP_LINKTYPE;

#define LX_TE_PCAP_MAGIC		0xa1b2c3d4
#define LX_TE_PCAP_VER_MAJOR	2
#define LX_TE_PCAP_VER_MINOR	4
typedef struct lx_te_pcap_hdr {
	__u32 magic_number;	/* magic number */
	__u16 version_major;	/* major version number */
	__u16 version_minor;	/* minor version number */
	__s32 thiszone;		/* GMT to local correction */
	__u32 sigfigs;		/* accuracy of timestamps */
	__u32 snaplen;		/* max length of captured packets, in octets */
	__u32 network;		/* data link type */
} LX_TE_PCAP_HDR_T;

typedef struct lx_te_pcap_rec_hdr {
	__u32 ts_sec;		/* timestamp seconds */
	__u32 ts_usec;		/* timestamp microseconds */
	__u32 incl_len;		/* number of octets of packet saved in file */
	__u32 orig_len;		/* actual length of packet */
} LX_TE_PCAP_REC_HDR_T;

/*____________________________ BEGIN - IO  ___________________________________*/

/**
 * TE core input port setting.
 * detailed description.
 * @see LX_SDEC_SEL_INPUT_T
 */
typedef enum lx_te_input_port {
	LX_TE_INPUT_PORT_NONE = 0x0,

	LX_TE_INPUT_PORT_TPI = 0x10,
	LX_TE_INPUT_PORT_TPI_IN_DEMOD0 = LX_TE_INPUT_PORT_TPI,
	LX_TE_INPUT_PORT_TPI_EXT_INPUT0,
	LX_TE_INPUT_PORT_TPI_EXT_INPUT1,
	LX_TE_INPUT_PORT_TPI_EXT_INPUT2,
	LX_TE_INPUT_PORT_TPI_CI_INPUT,
	LX_TE_INPUT_PORT_TPI_CI_OUTPUT,
	LX_TE_INPUT_PORT_TPI_MAX,

	LX_TE_INPUT_PORT_DVR = 0x30,
	LX_TE_INPUT_PORT_DVR0 = LX_TE_INPUT_PORT_DVR,
	LX_TE_INPUT_PORT_DVR1,

	LX_TE_INPUT_PORT_CI = 0x40,

	LX_TE_INPUT_PORT_CIPLUS_DEMUX = 0x50,
	LX_TE_INPUT_PORT_CIPLUS_DEMUX0 = LX_TE_INPUT_PORT_CIPLUS_DEMUX,
	LX_TE_INPUT_PORT_CIPLUS_DEMUX1,
	LX_TE_INPUT_PORT_CIPLUS_DEMUX2,

	LX_TE_INPUT_PORT_CIPLUS_IN = 0x60,
	LX_TE_INPUT_PORT_CIPLUS_IN0 = LX_TE_INPUT_PORT_CIPLUS_IN,
	LX_TE_INPUT_PORT_CIPLUS_IN1,
	LX_TE_INPUT_PORT_CIPLUS_IN2,

	LX_TE_INPUT_PORT_AUDIO0 = 0x90,
	LX_TE_INPUT_PORT_AUDIO1,
	LX_TE_INPUT_PORT_VIDEO0,
	LX_TE_INPUT_PORT_VIDEO1,

	LX_TE_INPUT_PORT_BYPASS = 0xF0,
	LX_TE_INPUT_PORT_INVALID,
} LX_TE_INPUT_PORT_T;

typedef enum lx_te_input_mode {
	LX_TE_IO_MODE_NONE = 0,
	LX_TE_INPUT_MODE_NONE = LX_TE_IO_MODE_NONE,
	LX_TE_IO_MODE_SERIAL,
	LX_TE_INPUT_MODE_SERIAL = LX_TE_IO_MODE_SERIAL,
	LX_TE_IO_MODE_PARALLEL,
	LX_TE_INPUT_MODE_PARALLEL = LX_TE_IO_MODE_PARALLEL,
	LX_TE_IO_MODE_MAX,
} LX_TE_IO_MODE_T, LX_TE_INPUT_MODE_T;

/**
 * SDEC Input Source setting.
 * detailed description.
 * @see LX_TE_SEL_INPUT_SRC_T
 */
typedef enum lx_te_input_src {
	LX_TE_INPUT_SRC_NONE = 0,
	LX_TE_INPUT_SRC_IN_DEMOD0,
	LX_TE_INPUT_SRC_EXT_INPUT0,
	LX_TE_INPUT_SRC_EXT_INPUT1,
	LX_TE_INPUT_SRC_EXT_INPUT2,
	LX_TE_INPUT_SRC_CI_INPUT,
	LX_TE_INPUT_SRC_CI_OUTPUT,
	LX_TE_INPUT_SRC_TE,
	LX_TE_INPUT_SRC_IP0,
	LX_TE_INPUT_SRC_IP1,
	LX_TE_INPUT_SRC_MAX
} LX_TE_INPUT_SRC_T;

typedef enum lx_te_sync_type {
	LX_TE_SYNC_SYNC_BYTE = 0x0,
	LX_TE_SYNC_SYNCBYTE = LX_TE_SYNC_SYNC_BYTE,
	LX_TE_SYNC_SOP,
	LX_TE_SYNC_SOP_ALL_BIT = LX_TE_SYNC_SOP,
	LX_TE_SYNC_SOP_FIRSTBIT,
	LX_TE_SYNC_VALIDONLY,
	LX_TE_SYNC_SOP_SYNCBYTE,	/* SYNC BYTE & SOP */
	LX_TE_SYNC_MAGIC,	/* Magic Number */
	LX_TE_SYNC_SOP_MAGIC,	/* Magic Number & SOP */
	LX_TE_SYNC_BYPASS,
	LX_TE_SYNC_MAX,
} LX_TE_SYNC_TYPE_T;

typedef enum lx_te_stream_type {
	LX_TE_STREAM_UNKNOWN = 0,
	LX_TE_STREAM_MPEG2TS,
	LX_TE_STREAM_ATSC3,
	LX_TE_STREAM_ARIB2,
	LX_TE_STREAM_BYPASS,
	LX_TE_STREAM_MAX,
} LX_TE_STREAM_TYPE_T;

/**
 * TE input port configuration. (SDEC / ATSC3 / CIPLUS)
 */
typedef struct lx_te_tpi_cfg {
	enum lx_te_stream_type stream_type;
	enum lx_te_input_mode mode;		/* input mode(Serial/Parallel/Disable) */

	enum lx_te_sync_type sync_type;		/* Synchronization type */
	enum lx_te_sync_type s2p_sync_type;	/* Serial to parallel mode */

	__u8 num_of_sync_found;			/* Number of sync should be found for sync */
	__u8 num_of_sync_drop;			/* Number of sync should be dropped for sync */
} LX_TE_TPI_CFG_T;

typedef struct lx_te_tpi_cfg_param {
	enum lx_te_input_port port __aligned(8);	/**< in - input port(0 ~ ...) */
	union {
		struct lx_te_tpi_cfg *value;
		TE_COMPAT_SIZER(value);
	};
} LX_TE_TPI_CFG_PARAM_T;

typedef struct lx_te_tpi_status {
	enum lx_te_stream_type stream_type;
	enum lx_te_input_mode mode;		/* input mode(Serial/Parallel) */
	enum lx_te_sync_type sync_type;		/* Synchronization type */
	enum lx_te_sync_type s2p_sync_type;	/* Synchronization type(Serial) */

	__u8 enable;
	__u8 sync_drop;
	__u8 num_of_sync_found;	/* Numbfer of sync should be found for sync */
	__u8 num_of_sync_drop;	/* Numbfer of sync should be dropped for sync */

	__u32 pkt_count;	/* packet count from input */
	__u32 tei_count;	/* transport error indicator count */
	__u32 time;		/* capture time - ms unit */

	__u32 reg_value[3];
} LX_TE_TPI_STATUS_T;

typedef struct lx_te_tpi_status_param {
	enum lx_te_input_port port __aligned(8);	/**< in - input port(0 ~ ...) */
	union {
		struct lx_te_tpi_status *value;
		TE_COMPAT_SIZER(value);
	};
} LX_TE_TPI_STATUS_PARAM_T;

typedef struct lx_te_input_port_connect {
	enum lx_te_input_port port;
	enum lx_te_input_port src;
} LX_TE_INPUT_PORT_CONNECT_T;

/*________________________________ END - IO  _________________________________*/


#endif				/* _TE_KAPI_H_ */
