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
 *  ciplus driver
 *
 *  @author Ilkyu Kim ( ilkyu.kim@lge.com)
 *  @version	0.1
 *  @date		2015-07-07
 *  @note		Additional information.
 */

#ifndef	_TE_CIPLUS_KAPI_H_
#define	_TE_CIPLUS_KAPI_H_

#include "te_kapi.h"

/**
 * SDEC IOCTL Magic number
 */
#define	CIPLUS_IOC_CORE_MAGIC		'c'
#define	CIPLUS_IOC_MM_MAGIC		'm'

#define CIPLUS_IOC_IO_MAGIC		'i'
#define CIPLUS_IOC_IPD_MAGIC		'd'
#define CIPLUS_IOC_PIDF_MAGIC		'p'

#define CIPLUS_CORE_INIT		_IO(CIPLUS_IOC_CORE_MAGIC, 0)
#define CIPLUS_CORE_GET_CHIPCFG		_IOR(CIPLUS_IOC_CORE_MAGIC, 1, LX_CIPLUS_CHIP_CFG_T)
#define CIPLUS_CORE_GET_BASEADDRESS	_IOR(CIPLUS_IOC_CORE_MAGIC, 3,LX_CIPLUS_MEM_T)

#define CIPLUS_IO_CONFIG_CHANNEL	_IOW(CIPLUS_IOC_IO_MAGIC, 0, LX_CIPLUS_CHANNEL_CFG_T)
#define CIPLUS_IO_ENABLE_CHANNEL	_IOW(CIPLUS_IOC_IO_MAGIC, 1, __u8)
#define CIPLUS_IO_GET_BITRATE		_IOR(CIPLUS_IOC_IO_MAGIC, 3, __u32)
#define CIPLUS_IO_SET_DEMUXDEST		_IOW(CIPLUS_IOC_IO_MAGIC, 4, LX_CIPLUS_DEMUX_DEST_T)

#define CIPLUS_CORE_GET_BITRATE	CIPLUS_IO_GET_BITRATE	//Deprecated

#define CIPLUS_PIDF_SET			_IOWR(CIPLUS_IOC_PIDF_MAGIC, 0, LX_CIPLUS_PIDF_CFG_T)
#define CIPLUS_PIDF_FREE		_IOW(CIPLUS_IOC_PIDF_MAGIC, 1, LX_CIPLUS_PIDF_CFG_T)
#define CIPLUS_PIDF_CLEANALL		_IO(CIPLUS_IOC_PIDF_MAGIC, 2)
#define CIPLUS_PIDF_BYPASS		_IOW(CIPLUS_IOC_PIDF_MAGIC, 3, __u8)

/* new ioctls for buffer test */
#define CIPLUS_IPD_START_DOWNLOAD	_IO(CIPLUS_IOC_IPD_MAGIC, 0)
#define CIPLUS_IPD_RESET_DOWNLOAD	_IO(CIPLUS_IOC_IPD_MAGIC, 1)
#define CIPLUS_IPD_START_UPLOAD		_IO(CIPLUS_IOC_IPD_MAGIC, 2)
#define CIPLUS_IPD_RESET_UPLOAD		_IO(CIPLUS_IOC_IPD_MAGIC, 3)

#define CIPLUS_MM_OPEN			_IO (CIPLUS_IOC_MM_MAGIC, 0)
#define CIPLUS_MM_CLOSE			_IO (CIPLUS_IOC_MM_MAGIC, 1)
#define CIPLUS_MM_ALLOC			_IOWR(CIPLUS_IOC_MM_MAGIC, 2, LX_CIPLUS_MEM_T)
#define CIPLUS_MM_FREE			_IOW (CIPLUS_IOC_MM_MAGIC, 3, __u32)
#define CIPLUS_MM_GETINFO		_IOR (CIPLUS_IOC_MM_MAGIC, 4, LX_CIPLUS_MEM_INFO_T)
#define CIPLUS_MM_CACHE_CTRL		_IOW (CIPLUS_IOC_MM_MAGIC, 5, LX_TE_CACHE_CTRL_T)

#define CIPLUS_IOC_MAXNR			30

typedef enum lx_ciplus_input_dest {
	LX_CIPLUS_DEST_HW = 0,
	LX_CIPLUS_DEST_MCU = 1,
} LX_CIPLUS_INPUT_DEST_T;

typedef enum lx_ciplus_demux_dest {
	LX_CIPLUS_DEMUX_DEST_NONE = 0,
	LX_CIPLUS_DEMUX_DEST_HWONLY = 1,
	LX_CIPLUS_DEMUX_DEST_MCUONLY = 2,
	LX_CIPLUS_DEMUX_DEST_BOTH = 3,
	LX_CIPLUS_DEMUX_DEST_MAX,
} LX_CIPLUS_DEMUX_DEST_T;

typedef enum lx_ciplus_demux_num {
	LX_CIPLUS_DEMUX0 = 0,
	LX_CIPLUS_DEMUX1 = 1,
	LX_CIPLUS_DEMUX2 = 2,
	LX_CIPLUS_DEMUX_NONE = 3,
} LX_CIPLUS_DEMUX_NUM_T;

/*----------------------------------------------------------------------------------------
	Stucture Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct lx_ciplus_input_buf_cfg {
	enum lx_te_input_src src;		/**< input src(HW demod or MCU AXI) */
	enum lx_ciplus_input_dest dest;		/**< input dest(HW Queue or MCU AXI) */

	__u8 full_level;
} LX_CIPLUS_INPUT_BUF_CFG_T;

typedef struct lx_ciplus_channel_cfg {
	enum lx_te_input_src src;
	enum lx_ciplus_demux_dest demux_dest;
} LX_CIPLUS_CHANNEL_CFG_T;

typedef struct lx_ciplus_input_src_cfg {
	enum lx_te_input_port demod;		/**< input dest(HW Queue or MCU AXI) */

	__u8 bypass_en;
	__u8 tei_en;

} LX_CIPLUS_INPUT_SRC_CFG_T;

typedef struct lx_ciplus_demux_cfg {
	enum lx_ciplus_demux_dest demux_dest;
	__u8 syncbyte;
} LX_CIPLUS_DEMUX_CFG_T;

typedef struct lx_ciplus_pidf_cfg {
	__u8 idx;
	__u16 pid;
} LX_CIPLUS_PIDF_CFG_T;

/* CIPLUS MM Structure */
typedef struct lx_ciplus_mem {
	__u32 addr;		/* address */
	__u32 size;		/* requested size */
} LX_CIPLUS_MEM_T;

/**
 * Information of CIPLUS Memory
 * @see SDEC_IOC_MM_GETINFO
 */
typedef struct lx_ciplus_mem_info {
	__u32 addr;		/* address */
	__u32 size;		/* total size */
	__u32 free;		/* free size */
	__u32 avail;		/* max continuous memory size */
} LX_CIPLUS_MEM_INFO_T;

typedef struct lx_ciplus_chip_cfg {
	__u8 num_ch;
	__u8 num_pidf;
	__u8 use_cinport;
} LX_CIPLUS_CHIP_CFG_T;

#define CIPLUS_NUM_PIDF		32

#endif				/* _TE_CIPLUS_KAPI_H_ */

/** @} */
