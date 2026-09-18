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
 *  sdec driver
 *
 *  @author	Jihoon Lee ( gaius.lee@lge.com)
 *  @author	Jinhwan Bae ( jinhwan.bae@lge.com) - modifier
 *  @version	1.0
 *  @date	2010-03-30
 *  @note	Additional information.
 */

#ifndef	_TE_SDEC_KAPI_H_
#define	_TE_SDEC_KAPI_H_

#include <linux/types.h>

#include "te_kapi.h"

/**
 * SDEC IOCTL Magic number
 */

#define	SDEC_IOC_CORE_MAGIC		's'
#define	SDEC_IOC_MM_MAGIC		'm'
#define	SDEC_IOC_DESC_MAGIC		'd'
#define SDEC_IOC_FLT_MAGIC		'f'
#define SDEC_IOC_IO_MAGIC		'i'
#define SDEC_IOC_CLK_MAGIC		'k'

// CORE
#define SDEC_IOC_GET_CHIPCFG		_IOR (SDEC_IOC_CORE_MAGIC, 0, LX_SDEC_CHIP_CFG_T)

// Descrambler
#define SDEC_IOC_DESC_INIT		_IOW (SDEC_IOC_DESC_MAGIC, 0, LX_SDEC_DESC_CONFIG_T)
#define SDEC_IOC_DESC_SET_KEY		_IOW (SDEC_IOC_DESC_MAGIC, 1, LX_SDEC_DESC_KEY_T)
#define SDEC_IOC_DESC_SET_PID		_IOW (SDEC_IOC_DESC_MAGIC, 2, LX_SDEC_DESC_PID_T)
#define SDEC_IOC_DESC_SEND_ECP		_IOWR (SDEC_IOC_DESC_MAGIC, 3, struct lx_sdec_desc_ecp)

// PID filter
#define SDEC_IOC_PFLT_ALLOC		_IOW (SDEC_IOC_FLT_MAGIC, 0, LX_SDEC_PFLT_ALLOC_T)
#define SDEC_IOC_PFLT_FREE		_IOW (SDEC_IOC_FLT_MAGIC, 1, LX_SDEC_PFLT_FREE_T)
#define SDEC_IOC_PFLT_SET		_IOW (SDEC_IOC_FLT_MAGIC, 2, LX_SDEC_PFLT_CONFIG_T)
#define SDEC_IOC_PFLT_GET_STATUS	_IOW (SDEC_IOC_FLT_MAGIC, 3, LX_SDEC_PFLT_STATUS_PARAM_T)
#define SDEC_IOC_PFLT_REQ_TS_HEADER	_IOW (SDEC_IOC_FLT_MAGIC, 4, LX_SDEC_PFLT_TS_HEADER_T)

// Stream(Section,PES,RawTS) filter
#define SDEC_IOC_SFLT_REQUEST		_IOW (SDEC_IOC_FLT_MAGIC, 5, LX_SDEC_SFLT_CONFIG_T)
#define SDEC_IOC_SFLT_CANCEL		_IOW (SDEC_IOC_FLT_MAGIC, 6, LX_SDEC_SFLT_ID_T)
#define SDEC_IOC_SFLT_SET_RPTR		_IOW (SDEC_IOC_FLT_MAGIC, 7, LX_SDEC_SFLT_SET_RPTR_T)
#define SDEC_IOC_SFLT_GET_STATUS	_IOW (SDEC_IOC_FLT_MAGIC, 8, LX_SDEC_SFLT_STATUS_PARAM_T)
#define SDEC_IOC_SFLT_GET_BUF_INFO	_IOW (SDEC_IOC_FLT_MAGIC, 9, LX_SDEC_SFLT_BUFFER_INFO_PARAM_T)
#define SDEC_IOC_TEMI_REQUEST		_IOW (SDEC_IOC_FLT_MAGIC,10, LX_SDEC_TEMI_REQUEST_T)
#define SDEC_IOC_TEMI_CANCEL		_IOW (SDEC_IOC_FLT_MAGIC,11, LX_SDEC_TEMI_CANCEL_T)

// Clock
#define SDEC_IOC_CLK_SET_PCR_PID	_IOW (SDEC_IOC_CLK_MAGIC, 0, LX_SDEC_PCR_PID_T)
#define SDEC_IOC_CLK_SET_PCR_RECOVERY	_IOW (SDEC_IOC_CLK_MAGIC, 1, LX_SDEC_PCR_RECOVERY_CFG_T)
#define SDEC_IOC_CLK_CANCEL_PCR_PID	_IOW (SDEC_IOC_CLK_MAGIC, 2, LX_SDEC_PCR_PID_T)
#define SDEC_IOC_CLK_GET_STC_PCR	_IOR (SDEC_IOC_CLK_MAGIC, 3, LX_SDEC_STC_PCR_T)
#define SDEC_IOC_CLK_GET_LIVE_STC	_IOR (SDEC_IOC_CLK_MAGIC, 4, LX_SDEC_CLK_VALUE_T)

#define SDEC_IOC_CLK_SET_GSTC		_IOW (SDEC_IOC_CLK_MAGIC, 5, LX_SDEC_GSTC_PARAM_T)
#define SDEC_IOC_CLK_GET_GSTC		_IOW (SDEC_IOC_CLK_MAGIC, 6, LX_SDEC_GSTC_PARAM_T)
#define SDEC_IOC_CLK_SET_DCO_FCW	_IOW (SDEC_IOC_CLK_MAGIC, 7, __u32)
#define SDEC_IOC_CLK_SET_DCO_FREQ	_IOW (SDEC_IOC_CLK_MAGIC, 8, __u32)

// I/O
#define SDEC_IOC_GET_CAPABILITY		_IOR (SDEC_IOC_IO_MAGIC, 0, LX_SDEC_CAP_T )
#define SDEC_IOC_CFG_CHANNEL_INPUT	_IOW (SDEC_IOC_IO_MAGIC, 1, LX_SDEC_CHANNEL_INPUT_CFG_T)
#define SDEC_IOC_CHANNEL_INPUT_STATUS	_IOR (SDEC_IOC_IO_MAGIC, 2, LX_SDEC_CHANNEL_INPUT_STATUS_T)

#define SDEC_IOC_SET_CI_INPUT		_IOW (SDEC_IOC_IO_MAGIC, 3, LX_TE_INPUT_SRC_T)
#define SDEC_IOC_GET_CI_INPUT		_IOR (SDEC_IOC_IO_MAGIC, 4, LX_TE_INPUT_SRC_T)
#define SDEC_IOC_DUMP_START		_IOW (SDEC_IOC_IO_MAGIC, 5, LX_SDEC_INPUT_DUMP_T)
#define SDEC_IOC_DUMP_STOP		_IOW (SDEC_IOC_IO_MAGIC, 6, __u32)
#define SDEC_IOC_GET_DUMP_BUF_INFO	_IOR (SDEC_IOC_IO_MAGIC, 7, LX_SDEC_DUMP_BUF_INFO_T)
#define SDEC_IOC_CFG_IN_OUT		_IOW (SDEC_IOC_IO_MAGIC, 8, LX_SDEC_IO_CFG_T)
#define SDEC_IOC_CFG_OUTPUT_PORT	_IOW (SDEC_IOC_IO_MAGIC, 9, LX_SDEC_OUTPUT_PORT_CFG_T)

// Memory Pool
#define SDEC_IOC_MM_GETINFO		_IOR (SDEC_IOC_MM_MAGIC, 0, LX_SDEC_MEM_INFO_T)
#define SDEC_IOC_MM_FREE		_IOW (SDEC_IOC_MM_MAGIC, 1, __u32)
#define SDEC_IOC_MM_ALLOC		_IOWR(SDEC_IOC_MM_MAGIC, 2, LX_SDEC_MEM_T)
#define SDEC_IOC_MM_CACHE_CTRL		_IOW (SDEC_IOC_MM_MAGIC, 3, LX_TE_CACHE_CTRL_T)

/**
 * Max number of SDEC packet between user layer and kernel layer.
 */
#define LX_SDEC_MAX_NOTIFY_DATA		256
#define LX_SDEC_ALL_PID_FILTER		0xAAAA

typedef enum lx_sdec_ch {
	LX_SDEC_CH_A = 0,
	LX_SDEC_CH_B,
	LX_SDEC_CH_C,
	LX_SDEC_CH_D,
	LX_SDEC_CH_E,
	LX_SDEC_CH_F,
	LX_SDEC_CH_G,
	LX_SDEC_CH_H,
	LX_SDEC_CH_NUM,
	LX_SDEC_CH_INVALID = LX_SDEC_CH_NUM,
} LX_SDEC_CH_T;

typedef enum lx_sdec_io_direction {
	LX_SDEC_IO_INPUT = 0,
	LX_SDEC_IO_OUTPUT,
} LX_SDEC_IO_DIRECTION_T;

typedef enum lx_sdec_output_clk {
	LX_SDEC_OUTPUT_CLK_198MHZ = 0,
	LX_SDEC_OUTPUT_CLK_99MHZ,
	LX_SDEC_OUTPUT_CLK_66MHZ,
	LX_SDEC_OUTPUT_CLK_49MHZ,
	LX_SDEC_OUTPUT_CLK_33MHZ,
	LX_SDEC_OUTPUT_CLK_24MHZ,
	LX_SDEC_OUTPUT_CLK_12MHZ,
	LX_SDEC_OUTPUT_CLK_10MHZ,
	LX_SDEC_OUTPUT_CLK_8MHZ,
	LX_SDEC_OUTPUT_CLK_6MHZ,
	LX_SDEC_OUTPUT_CLK_4MHZ,
	LX_SDEC_OUTPUT_CLK_2MHZ,
} LX_SDEC_OUTPUT_CLK_T;

/**
 * Command of PCR recovery
 * enable/disable and reset the pcr recovery for some reason.
 * @see LX_SDEC_PCR_RECOVERY_CFG_T
 */
typedef enum lx_sdec_pcr_cmd {
	LX_SDEC_PCR_CMD_DISABLE = 0,		/**< Disable PCR Recovery */
	LX_SDEC_PCR_CMD_ENABLE,			/**< Enable PCR Recovery */
	LX_SDEC_PCR_CMD_RESET,			/**< Reset */
	LX_SDEC_PCR_CMD_SET_MAIN,
	LX_SDEC_PCR_CMD_SET_SUB,
} LX_SDEC_PCR_CMD_T;

typedef enum lx_sdec_gstc_time_base {
	LX_SDEC_GSTC_TIME_BASE_90KHZ = 0,
	LX_SDEC_GSTC_TIME_BASE_45KHZ,
	LX_SDEC_GSTC_TIME_BASE_180KHZ,
} LX_SDEC_GSTC_TIME_BASE_T;

/**
 * Stream type in filter
 * @see LX_SDEC_SFLT_CONFIG_T, LX_SDEC_PFLT_CONFIG_T
 */
typedef enum lx_sdec_stream_type {
	LX_SDEC_STREAM_TYPE_SECTION = 0,
	LX_SDEC_STREAM_TYPE_PES,
	LX_SDEC_STREAM_TYPE_RAWTS,
	LX_SDEC_STREAM_TYPE_NONE,
	LX_SDEC_STREAM_TYPE_MAX
} LX_SDEC_STREAM_TYPE_T;

typedef enum lx_sdec_payload_type {
	LX_SDEC_PAYLOAD_PES = 0,
	LX_SDEC_PAYLOAD_SECTION,
	LX_SDEC_PAYLOAD_UNKNOWN,
	LX_SDEC_PAYLOAD_TYPE_MAX
} LX_SDEC_PAYLOAD_TYPE_T;

/**
 * destination of Packet through PID filter.
 * @see LX_SDEC_PFLT_CONFIG_T
 */
typedef enum lx_sdec_pid_filter_dest {
	LX_SDEC_PFLT_DEST_VDEC0 = 0,
	LX_SDEC_PFLT_DEST_VDEC1,
	LX_SDEC_PFLT_DEST_VDEC2,
	LX_SDEC_PFLT_DEST_VDEC3,
	LX_SDEC_PFLT_DEST_ADEC0,
	LX_SDEC_PFLT_DEST_ADEC1,
	LX_SDEC_PFLT_DEST_ADEC2,
	LX_SDEC_PFLT_DEST_ADEC3,
	LX_SDEC_PFLT_DEST_DVR,
	LX_SDEC_PFLT_DEST_DVR0 = LX_SDEC_PFLT_DEST_DVR,
	LX_SDEC_PFLT_DEST_DVR1,
	LX_SDEC_PFLT_DEST_DVR2,
	LX_SDEC_PFLT_DEST_DVR3,
	LX_SDEC_PFLT_DEST_STC,
	LX_SDEC_PFLT_DEST_STC0 = LX_SDEC_PFLT_DEST_STC,
	LX_SDEC_PFLT_DEST_STC1,
	LX_SDEC_PFLT_DEST_BUFFER,
	LX_SDEC_PFLT_DEST_PIE,
	LX_SDEC_PFLT_DEST_TEMI,
	LX_SDEC_PFLT_DEST_TSHEADER,
	LX_SDEC_PFLT_DEST_NONE,	//FIXME: deprecated
	LX_SDEC_PFLT_DEST_MAX
} LX_SDEC_PFLT_DEST_T;

#define LX_SDEC_PFLT_DEST_MASK(d)	(0x1 << LX_SDEC_PFLT_DEST_##d)

/**
 * PID filter status.
 * detailed description.
 * @see LX_SDEC_PFLT_STATUS_T
 */
typedef enum lx_sdec_pflt_state {
	LX_SDEC_PFLT_STATE_SCRMREADY = 0x00000001,	/**< scrambled check ready */
	LX_SDEC_PFLT_STATE_SCRAMBLED = 0x00000002,	/**< Scrambled */
} LX_SDEC_PFLT_STATE_T;

/**
 * Stream filter flags
 * @see LX_SDEC_SFLT_CONFIG_T
 */
typedef enum lx_sdec_sflt_flag {
	LX_SDEC_SFLT_FLAG_ONESHOT = 0x00000001,		/**< One packet mode */
	LX_SDEC_SFLT_FLAG_NO_CRC_CHECK = 0x00000002	/**< no CRC checking */
} LX_SDEC_SFLT_FLAG_T;

/**
 * Stream filter state
 * detailed description.
 * @see LX_SDEC_SFLT_STATUS_T
 */
typedef enum lx_sdec_sflt_state {
	LX_SDEC_SFLT_STATE_DATAREADY = 0x00000001,	/**< data is ready - section filter use */
	LX_SDEC_SFLT_STATE_OVERFLOW = 0x00000002,	/**< Overflowed */
	LX_SDEC_SFLT_STATE_DELETED = 0x00000004		/**< deleted */
} LX_SDEC_SFLT_STATE_T;

typedef enum lx_sdec_input_clock_mode {
	LX_SDEC_INPUT_CLOCK_INT = 0x0,
	LX_SDEC_INPUT_CLOCK_EXT
} LX_SDEC_INPUT_CLOCK_MODE_T;

typedef enum lx_sdec_dump_type {
	LX_SDEC_DUMP_TYPE_0 = 0x0,		/** will modify it */
	LX_SDEC_DUMP_TYPE_1
} LX_SDEC_DUMP_TYPE_T;

typedef enum lx_sdec_dump_timeres {
	LX_SDEC_DUMP_TIMESTAMP_NOUSE = 0x0,
	LX_SDEC_DUMP_TIMESTAMP_27MHZ,
	LX_SDEC_DUMP_TIMESTAMP_90KHZ,
} LX_SDEC_DUMP_TIMERES_T;

typedef enum lx_sdec_dump_timesrc {
	LX_SDEC_DUMP_TIMESRC_AUTO = 0x0,	//Set by default value
	LX_SDEC_DUMP_TIMESRC_STCC0,
	LX_SDEC_DUMP_TIMESRC_STCC1,
	LX_SDEC_DUMP_TIMESRC_STCC2,
	LX_SDEC_DUMP_TIMESRC_STCC3,
	LX_SDEC_DUMP_TIMESRC_GSTCC0,
	LX_SDEC_DUMP_TIMESRC_GSTCC1,
	LX_SDEC_DUMP_TIMESRC_GSTCC2,
	LX_SDEC_DUMP_TIMESRC_GSTCC3,
} LX_SDEC_DUMP_TIMESRC_T;

typedef struct lx_sdec_buf {
	__u32 addr;
	__u32 size;
} LX_SDEC_BUF_T;

/**
 * Initialize value.
 * initialize SDEC H/W and get H/W capability from kernel driver.
 * @see SDEC_IO_INIT
 */
typedef struct lx_sdec_cap {
	__u16 num_pidf;		/**< out - number of PID Filter of SDEC */
	__u16 num_secf;		/**< out - number of Section Filter of SDEC */
} LX_SDEC_CAP_T;

#define TPI_LIST_NUM	(LX_TE_INPUT_PORT_TPI_MAX - LX_TE_INPUT_PORT_TPI)

/**
 * SDEC Chip Revision Configuration
 * @see SDEC_IOW_GET_CHIPCFG
 */
typedef struct lx_sdec_chip_cfg {
	__u8 num_channel;	/**< number of channels */
	__u8 num_sub_channel;
	__u8 num_vdec_out;	/**< number of vdec output port. */
	__u8 num_adec_out;	/**< number of adec output port. */
	__u8 num_demod_input;	/**< number of demod input port */
	__u8 num_ci_plus_input;	/**< number of ci+ 1.4 input port */
	__u8 num_ci_input;	/**< number of ci input port */
	__u8 input_ver;		/* 0:M16, 1: >= M16+ */

	__u16 num_pid_filter;
	__u16 num_stream_filter;

	__u8 num_tpi_input;
	enum lx_te_input_port tpi_table[TPI_LIST_NUM];

	__u16 num_temi_filter;
} LX_SDEC_CHIP_CFG_T;

/*_____________________________ BEGIN - I/O __________________________________*/

typedef struct lx_sdec_io_cfg {
	enum lx_te_input_src src;	/* i/o shared port */
	enum lx_te_input_mode mode;	/* serial or parallel */
	enum lx_sdec_io_direction direction;	/* in or out */
	enum lx_sdec_output_clk clk;	/* output clock */
} LX_SDEC_IO_CFG_T;

typedef struct lx_sdec_output_port_cfg {
	enum lx_te_input_src src;	/* i/o shared port (Deprecated) */
	enum lx_te_input_mode mode;	/* serial or parallel */
	enum lx_te_input_port port;	/* input port(0 ~ ...) */

	__u8 clk_inv;		/* clock polarity inverse */
	__u8 enable;

} LX_SDEC_OUTPUT_PORT_CFG_T;

/**
 * SDEC core input port enable/disable
 * @see SDEC_IOW_ENABLE_INPUT_PORT
 */
typedef struct lx_sdec_channel_input_cfg {
	enum lx_te_input_port port;	/**< in  -  input mode of the channel */
	__u8 reset;			/**< in  -  port reset or not */
	__u8 enable;			/**< in  -  Enable/Disable */
} LX_SDEC_CHANNEL_INPUT_CFG_T;

/**
 * SDEC Get Demod_Conf Register value
 * @see SDEC_IOC_GET_CHANNEL_STATUS
 */
typedef struct lx_sdec_channel_input_status {
	enum lx_te_input_port port;
	__u8 enable;		/* Enable/Disable */
	__u32 pkt_count;	/* after pid filter */
	__u32 time;		/* ms unit */
} LX_SDEC_CHANNEL_INPUT_STATUS_T;

typedef struct lx_sdec_input_dump {
	enum lx_sdec_dump_type type;
	__u32 ch;
	enum lx_sdec_dump_timesrc clk_src;
	enum lx_sdec_dump_timeres clk_res;

	enum lx_te_input_port port;
	__u32 buf_start;
	__u32 buf_end;
	__u32 unit_size;
} LX_SDEC_INPUT_DUMP_T;

typedef struct lx_sdec_dump_buf_info {
	__u32 wptr;
} LX_SDEC_DUMP_BUF_INFO_T;

/*____________________________ END - I/O _____________________________________*/

/*_________________________ BEGIN - CRYPTO ___________________________________*/

typedef enum lx_sdec_desc_mode {
	LX_SDEC_DESC_MODE_CHANNEL = 0,
	LX_SDEC_DESC_MODE_PID,
	LX_SDEC_DESC_MODE_CHANNEL_PID,
	LX_SDEC_DESC_MODE_MAX
} LX_SDEC_DESC_MODE_T;

/**
 * Cipherkey setting.
 * detailed description.
 * @see LX_SDEC_CIPHERKEY_T
 */
typedef enum lx_sdec_desc_key_type {
	LX_SDEC_CIPHER_KEY_EVEN = 0,		/**< Even key */
	LX_SDEC_KEY_TYPE_EVEN = LX_SDEC_CIPHER_KEY_EVEN,
	LX_SDEC_CIPHER_KEY_ODD = 1,		/**< Odd key */
	LX_SDEC_KEY_TYPE_ODD = LX_SDEC_CIPHER_KEY_ODD,
	LX_SDEC_CIPHER_KEY_ODD_IV = 2,		/**< Odd Initial Vectore key */
	LX_SDEC_KEY_TYPE_ODD_IV = LX_SDEC_CIPHER_KEY_ODD_IV,
	LX_SDEC_CIPHER_KEY_EVEN_IV = 3,		/**< Even Initial Vectore key */
	LX_SDEC_KEY_TYPE_EVEN_IV = LX_SDEC_CIPHER_KEY_EVEN_IV,
	LX_SDEC_CIPHER_KEY_MULTI2 = 4,		/**< Multi-2 Key */
	LX_SDEC_KEY_TYPE_MULTI2 = LX_SDEC_CIPHER_KEY_MULTI2,
	LX_SDEC_CIPHER_KEY_NUM,
	LX_SDEC_KEY_TYPE_MAX = LX_SDEC_CIPHER_KEY_NUM,
} LX_SDEC_DESC_KEY_TYPE_T, LX_SDEC_CIPHER_KEY_T;

typedef enum lx_sdec_desc_key_location {
	LX_SDEC_KEY_FROM_MSG = 0,
	LX_SDEC_KEY_FROM_MEM,
} LX_SDEC_DESC_KEY_LOCATION_T;

/**
 * Descrambler mode for the reset.
 * @see LX_SDEC_RES_MODE
 */
typedef enum lx_sdec_res_mode {
	LX_SDEC_CLEAR = 0,
	LX_SDEC_CTS = 1,
	LX_SDEC_OFB = 2,
	LX_SDEC_SCTE52_2008 = 3,
	LX_SDEC_CTSOC = 4
} LX_SDEC_RES_MODE_T;

/**
 * Descrambler mode.
 * @see LX_SDEC_RES_MODE
 */
typedef enum lx_sdec_blk_mode {
	LX_SDEC_ECB = 0,
	LX_SDEC_CBC = 1
} LX_SDEC_BLK_MODE_T;

/**
 * Cipherkey setting.
 * @see LX_SDEC_CAS_TYPE
 */
typedef enum lx_sdec_cas_type {
	LX_SDEC_BYPASS = 0,
	LX_SDEC_DES = 1,
	LX_SDEC_TDES = 2,
	LX_SDEC_AES = 3,
	LX_SDEC_CSA = 4,
	LX_SDEC_MULTI2 = 5,
} LX_SDEC_CAS_TYPE_T;

/**
 * Cipherkey setting.
 * @see LX_SDEC_KEY_SIZE
 */
typedef enum lx_sdec_key_size {
	LX_SDEC_KEY_64BIT = 0,
	LX_SDEC_KEY_128BIT = 1,
	LX_SDEC_KEY_192BIT = 2,
	LX_SDEC_KEY_256BIT = 3
} LX_SDEC_KEY_SIZE_T;

typedef enum lx_sdec_desc_pid_mode {
	LX_SDEC_DESC_PID_CLEAR = 0,
	LX_SDEC_DESC_PID_ENABLE,
	LX_SDEC_DESC_PID_DISABLE,
} LX_SDEC_DESC_PID_MODE_T;

enum lx_sdec_desc_cas_mode {
	LX_SDEC_DESC_CAS_NORMAL = 0,
	LX_SDEC_DESC_CAS_ECP,
	LX_SDEC_DESC_CAS_XCAS,
	LX_SDEC_DESC_CAS_NAGRA,
	LX_SDEC_DESC_CAS_MAX
};

/**
 * Descrambler key setting.
 * @see SDEC_IOC_DESC_SET_KEY
 */
typedef struct lx_sdec_desc_key {
	enum lx_sdec_desc_key_type type;	/* key type */
	enum lx_sdec_desc_key_location location;	/* msg or mem */
	union {
		__u8 key[32];	/* Keys */
		__u32 addr;	/* Indirect (DEPRECATED) */
	};
	__u8 size;		/* Key Size in 4bytes aligen */
	__u16 pidf_id;		/* pid filter id */
	__u16 pid;		/* pid value */
} LX_SDEC_DESC_KEY_T;

typedef struct lx_sdec_desc_pid {
	__u16 pidf_id;		/* pid filter id */
	__u16 pid;		/* pid value */
	enum lx_sdec_desc_pid_mode mode;	/* 0:clear, 1:enable, 2:diable */
} LX_SDEC_DESC_PID_T;

/**
 * Descrambler configuration
 * @see SDEC_IOC_DESC_INIT
 */
typedef struct lx_sdec_desc_config {
	enum lx_sdec_desc_mode desc_mode;	/* Channel or PID */
	enum lx_sdec_cas_type cas_type;	/* Cas Type (Bypass/DES/TDES/AES/CSA/MULTI2) */
	enum lx_sdec_blk_mode blk_mode;	/* Blk Mode (ECB/CBC) */
	enum lx_sdec_res_mode res_mode;	/* Residual Mode (Clear/CTS/OFB/...) */
	enum lx_sdec_key_size key_size;	/* Key Size if variable type like AES */
	enum lx_sdec_desc_cas_mode cas_mode; /* new for enhanced control */
} LX_SDEC_DESC_CONFIG_T;

/**
 * descrambler ecp ioctl test call
 * Will be removed soon
 */
struct lx_sdec_desc_ecp {
	enum lx_sdec_cas_type cas_type;
	enum lx_sdec_desc_key_type key_type;
	__u32 len;
	__u8 data[256];
};

/*_____________________________ END - CRYPTO _________________________________*/

/*__________________________ BEGIN - MM ______________________________________*/

/**
 * Information of Memory
 * @see SDEC_IOC_MM_ALLOC
 */
typedef struct lx_sdec_mem {
	__u32 addr;		/* address */
	__u32 size;		/* total size */
} LX_SDEC_MEM_T;

/**
 * Information of SDEC Memory
 * @see SDEC_IOC_MM_GETINFO
 */
typedef struct lx_sdec_mem_info {
	__u32 addr;		/* address */
	__u32 size;		/* total size */
	__u32 free;		/* free size */
	__u32 avail;		/* max continuous memory size */
} LX_SDEC_MEM_INFO_T;

/*_____________________________ END - MM _____________________________________*/

/*__________________________ BEGIN - CLOCK ___________________________________*/

/**
 * Set PCR pid value.
 * @see SDEC_IOW_SET_PCR_PID
 */
typedef struct lx_sdec_pcr_pid {
	__u16 pid;		/**< PID value(0x1fff = disable) */
	__u8 main;		/**< is this pcr is used for main or sub */
} LX_SDEC_PCR_PID_T;

/**
 * Enable/Disable PCR Recovery
 * @see SDEC_IOW_SET_PCR_RECOVERY
 */
typedef struct lx_sdec_pcr_recovery_cfg {
	enum lx_sdec_pcr_cmd cmd;	/**<  Enable/disable/reset */
} LX_SDEC_PCR_RECOVERY_CFG_T;

typedef struct lx_sdec_clk_value {
	__u32 base_32;		/* [32] in base 33bits */
	__u32 base_31_0;	/* [31:0] in  base 33bits */
	__u32 ext;		/* extenstion 9bits */
} LX_SDEC_CLK_VALUE_T;

/**
 * STC value.
 * @see SDEC_IOC_CLK_GET_STC_PCR
 */
typedef struct lx_sdec_stc_pcr {
	struct lx_sdec_clk_value stc;
	struct lx_sdec_clk_value pcr;
} LX_SDEC_STC_PCR_T;

/**
 * GSTC value.
 * @see SDEC_IOR_GET_STC_PCR
 */
typedef struct {
	__u8 index;				/**< in - gstc index */
	enum lx_sdec_gstc_time_base time_base;	/**< in - gstc timebase */
	union {
		struct lx_sdec_clk_value *value;
		TE_COMPAT_SIZER(value);
	};
} LX_SDEC_GSTC_PARAM_T;

/*_____________________________ END - CLOCK __________________________________*/

/*_________________________ BEGIN - PID FILTER _______________________________*/

/**
 * Allocation information
 * @see SDEC_IOC_PFLT_ALLOC
 */
typedef struct lx_sdec_pflt_alloc {
	__u16 pid;		/**< in  -  PID value */
} LX_SDEC_PFLT_ALLOC_T;

/**
 * Remove PID filter.
 * @see SDEC_IOC_PFLT_FREE
 */
typedef struct lx_sdec_pflt_free {
	__u16 flt_id;		/**< in  -  PID filter ID */
} LX_SDEC_PFLT_FREE_T;

/**
 * Set PID filter.
 * @see SDEC_IOC_PFLT_SET
 */
typedef struct lx_sdec_pflt_config {
	__u16 flt_id;		/**< PID filter ID */
	enum lx_sdec_payload_type payload_type;
	__u32 dest_mask;	/**< Destination mask @see LX_SDEC_PFLT_DEST_T */
	__u8 enable;		/**< PID Filter Enable or Not */
} LX_SDEC_PFLT_CONFIG_T;

/**
 * Get PID filter status.
 * @see SDEC_IOC_PFLT_GET_STATUS
 */
typedef struct lx_sdec_pflt_status {
	__u16 pid;		/**< PID Value of PID Filter */
	__u8 enabled;		/**< PID filter enable/disable */
	enum lx_sdec_payload_type payload;
	__u32 subfilter[8];	/**< connected section filter id if exist */
	__u32 dest_mask;	/**< Destination mask @see LX_SDEC_PFLT_DEST_T */
	__u32 state;		/**< Status of PID filter.  @see LX_SDEC_PFLT_STATE_T */
	__u32 reg_value;	/**< Value of the PID filter */
} LX_SDEC_PFLT_STATUS_T;

typedef struct {
	__u16 flt_id __aligned(8);	/**< PID filter ID */
	union {
		struct lx_sdec_pflt_status *status;
		TE_COMPAT_SIZER(status);
	};
} LX_SDEC_PFLT_STATUS_PARAM_T;

/**
 * Request TS Header
 * @see SDEC_IOW_PFLT_REQ_TS_HEADER
 */
typedef struct lx_sdec_pflt_ts_header {
	__u16 pid;		/**< in  -  PID */
	__u8 enable;		/**< in  -  PID filter enable/disable */
} LX_SDEC_PFLT_TS_HEADER_T;

/*________________________ END - PID FILTER __________________________________*/

/*_______________ BEGIN - STREAM FILTER (Section,PES,RawTS)___________________*/

/**
 * Set read pointer to gpb.
 * @see SDEC_IOC_SFLT_SET_RPTR
 */
typedef struct lx_sdec_sflt_set_rptr {
	enum lx_sdec_stream_type stream_type;
	__u32 flt_id;		/**< in  -  Filter ID */
	__u32 rptr;		/**< in  -  Read pointer address */
} LX_SDEC_SFLT_SET_RPTR_T;

#define LX_SDEC_FILTER_SIZE	8
/**
 * Set section filtering pattern.
 * @see SDEC_IOW_SECFLT_PATTERN, LX_SDEC_FLTMODE_T
 */
typedef struct lx_sdec_filter_pattern {
	__u8 value[LX_SDEC_FILTER_SIZE];	/**< section filtering pattern */
	__u8 mask[LX_SDEC_FILTER_SIZE];		/**< section filtering mask */
	__u8 noteq[LX_SDEC_FILTER_SIZE];	/**< NotEqual mask. If setted as 1, SDEC exclude pattern value */
} LX_SDEC_SFLT_PATTERN_T;

/**
 * Configuration value to request section filter
 * @see SDEC_IOC_SECF_REQUEST
 */
typedef struct lx_sdec_sflt_config {
	enum lx_sdec_stream_type stream_type;
	__u16 pidf_id;		/**< in  - PID Filter Id */
	__u16 flags;		/**< in  - Filter Falgs with LX_SDEC_SFLT_FLAG_T */
	struct lx_sdec_buf buf;

	LX_SDEC_SFLT_PATTERN_T pattern;	/**< in  - Filter Pattern only used in section */
	union {
		void *priv;
		TE_COMPAT_SIZER(priv);
	};
} LX_SDEC_SFLT_CONFIG_T;

typedef struct lx_sdec_sflt_id {
	enum lx_sdec_stream_type stream_type;
	__u32 id;		/**< in  - Filter Id */
} LX_SDEC_SFLT_ID_T;

/**
 * Get status of section filter.
 * @see SDEC_IOC_SFLT_GET_STATE
 */
typedef struct lx_sdec_sflt_status {
	__u16 pidf_id;		/**< out  - PID Filter Id */
	__u16 flags;		/**< out  - Filter Falgs with LX_SDEC_SFLT_FLAG_T */
	__u32 state;		/**< filter state with LX_SDEC_SFLT_STATE_T */
	struct lx_sdec_buf buf;

	LX_SDEC_SFLT_PATTERN_T pattern;	/**< out  - Filter Pattern only used in section */
	union {
		void *priv;
		TE_COMPAT_SIZER(priv);
	};
} LX_SDEC_SFLT_STATUS_T;

typedef struct lx_sdec_sflt_status_param {
	enum lx_sdec_stream_type stream_type;
	__u32 flt_id;

	union {
		LX_SDEC_SFLT_STATUS_T *status;
		TE_COMPAT_SIZER(status);
	};
} LX_SDEC_SFLT_STATUS_PARAM_T;


typedef struct lx_sdec_sflt_buffer_info {
	__u32 rptr;			/**< out - Read Pointer  */
	__u32 wptr;			/**< out - Write Pointer */
} LX_SDEC_SFLT_BUFFER_INFO_T;

typedef struct lx_sdec_sflt_buffer_info_param {
	enum lx_sdec_stream_type stream_type;
	__u32 flt_id;			/**< in  - Filter Id */

	union {
		LX_SDEC_SFLT_BUFFER_INFO_T *info;
		TE_COMPAT_SIZER(info);
	};
} LX_SDEC_SFLT_BUFFER_INFO_PARAM_T;

/*________________ END - STREAM FILTER (Section,PES,RawTS)____________________*/

typedef enum lx_sdec_msg_type {
	LX_SDEC_MSG_TYPE_FILTER = 0,
	LX_SDEC_MSG_TYPE_TS_HEADER,
	LX_SDEC_MSG_TYPE_MAX
} LX_SDEC_NOTIFY_TYPE_T, LX_SDEC_MSG_TYPE_T;

typedef struct lx_sdec_filter_msg {
	__u8 ch;
	__u8 status;		/* status of section filter buffer(Ready/Overflow) @LX_SDEC_SFLT_STATE_T */
	__u16 index;		/* driver filter index */

	__u32 rptr;
	__u32 wptr;
	__u32 reserved_0;
	__u64 msec;

	union {
		void *priv;	/* private data for application */
		TE_COMPAT_SIZER(priv);
	};
} LX_SDEC_FILTER_MSG_T;

typedef struct lx_sdec_ts_header_msg {
	__u8 ch;
	__u8 reserved_0;
	__u16 pid;
	__u8 data[4];

	union {
		void *priv;	/* private data for application */
		TE_COMPAT_SIZER(priv);
	};
} LX_SDEC_TS_HEADER_MSG_T;

typedef struct lx_sdec_msg {
	enum lx_sdec_msg_type type;
	union {
		struct lx_sdec_filter_msg filter;
		struct lx_sdec_ts_header_msg ts_header;
	};
} LX_SDEC_MSG_T;

typedef struct lx_sdec_temi_request {
	__u16 pid;
	struct lx_sdec_buf buf;
} LX_SDEC_TEMI_REQUEST_T;

typedef struct lx_sdec_temi_cancel {
	__u8 idx;
} LX_SDEC_TEMI_CANCEL_T;

#endif				/* _TE_SDEC_KAPI_H_ */

/** @} */
