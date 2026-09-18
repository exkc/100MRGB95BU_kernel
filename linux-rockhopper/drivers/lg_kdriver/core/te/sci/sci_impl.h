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
 *	sci driver
 *
 *  @author		yeonju.lee
 *  @version	1.0
 *  @date		2016.05.23
 *  @note		Additional information.
 */

#ifndef	_SCI_IMPL_H_
#define	_SCI_IMPL_H_

#include "logm_kapi.h"
#include <linux/kernel.h>
#include <lg1k/te/debug.h>
#include <lg1k/te/sci.h>
#include <lg1k/te/util.h>

#define USE_ATR_POLLING_MODE

#define MAX_RF_DEPTH		0x3F
#define MAX_TF_DEPTH		0x1F
#define MAX_ATR_LEN		33

#define SCI_LOG(type,fmt,args...)	\
	LOGM_PRINT( g_sci_debug_fd, (LOG_LEVEL_##type), fmt, ##args)

#define log_noti(fmt, args...)		SCI_LOG( NOTI, fmt, ##args)
#define log_warning(fmt, args...)	SCI_LOG( WARNING, fmt, ##args)
#define log_error(fmt, args...)		SCI_LOG( ERROR, fmt, ##args)
#define log_trace(fmt, args...)		SCI_LOG( TRACE, fmt, ##args)
#define log_atr(fmt, args...)		SCI_LOG( ATR, fmt, ##args)
#define log_debug(fmt, args...)		SCI_LOG( DEBUG, fmt, ##args)

#define r_log(fmt, args...)	log_debug(TE_COLOR_RED fmt TE_COLOR_NONE, ##args)
#define g_log(fmt, args...)	log_debug(TE_COLOR_GREEN fmt TE_COLOR_NONE, ##args)
#define b_log(fmt, args...)	log_debug(TE_COLOR_BLUE fmt TE_COLOR_NONE, ##args)
#define y_log(fmt, args...)	log_debug(TE_COLOR_YELLOW fmt TE_COLOR_NONE, ##args)

#define CHECK_ERROR(__checker,__if_action,fmt,args...)   \
  TE_CHECK_IF_ERROR(__checker, log_error, __if_action , fmt, ##args )

#define CHECK_NULL_PARAM(param) \
  CHECK_ERROR(!(param), return -EINVAL, "parameter(" #param ") is null")

#define CHECK_PARAM(__checker,fmt,args...) \
  CHECK_ERROR(__checker, return -EINVAL, "invalid parameter : " fmt, ##args)


#define LOG_LEVEL_ERROR		LX_LOGM_LEVEL_ERROR	/* 0 */
#define LOG_LEVEL_WARNING	LX_LOGM_LEVEL_WARNING	/* 1 */
#define LOG_LEVEL_NOTI		LX_LOGM_LEVEL_NOTI	/* 2 */
#define LOG_LEVEL_INFO		LX_LOGM_LEVEL_INFO	/* 3 */
#define LOG_LEVEL_DEBUG		LX_LOGM_LEVEL_DEBUG	/* 4 */
#define LOG_LEVEL_TRACE		LX_LOGM_LEVEL_TRACE	/* 5 */
#define LOG_LEVEL_TRACE_EX	LX_LOGM_LEVEL_TRACE + 1 /* 6 */
#define LOG_LEVEL_ISR		LX_LOGM_LEVEL_TRACE + 2 /* 7 */
#define LOG_LEVEL_REG		LX_LOGM_LEVEL_TRACE + 3 /* 8 */
#define LOG_LEVEL_ATR		LX_LOGM_LEVEL_TRACE + 4 /* 10 */

enum {
	SCI_OK = 0,
	SCI_ESTATE,
	SCI_EATR,
	SCI_EACK,
	SCI_ECARD,
	SCI_ETIMEOUT,
	SCI_ETX,
	SCI_ERX,
};

//////////DVB SCI
#define	SCI_MODULE		"sci"
#define SCI_DEVICE_NAME		"lg1k-sci"

#define te_subdev_to_sci_device(sd) \
	container_of(sd, struct sci_dev, subdev)

#define get_te_device(dev)		(dev->subdev.tdev)

struct sci_info {
	u8 activated;

	u32 rx_fifo_depth;
	u32 tx_fifo_depth;

	u8 wtx;
	u8 deviceNS;
	u8 cardNS;

	u32 num_tx;
	u32 num_rx;
};

struct atr_T1 {
	u8 count;
	unsigned long data_bits;
	u8 TA;			/* first TA */
	u8 TB;			/* first TB */
	u8 TC;			/* first TC */

	/* IFSC is the maximum size of information field of blocks that
	 * can be received by the card.
	 * In first TA for T=1 and default value is 32
	 */
	u8 ifsc;

	/* In first TB for T=1 */
	u8 cwi;			/* Character Waiting time Integer. default = 13 */
	u8 bwi;			/* Block Waiting time Integer. default = 4 */

	/* In first TC for T=1 */
	u8 edc;			/* Error Detection Code - 0=LRC(default) or 1=CRC */
};

struct atr_T15 {
	u8 count;
	unsigned long data_bits;
	u8 TA;			/* first TA */
	u8 TB;			/* first TB */

	/* In first TA for T=15 */
	u8 clock_stop;		/* 0: not supported(default), 1:L, 2:H, 3:No preference */
	u8 class_supported;	/* bit(0=A,1=B,2=C), default=0x1(only class A) */

	/* In first TB for T=15 */
	u8 spu;			/* Standard or Proprietary Use contact. default=0(Not use) */
};
enum xfer_state {
	XFER_STATE_IDLE,
	XFER_STATE_READY,
	XFER_STATE_TX_WRITE,
	XFER_STATE_TX_WRITE_DONE,
	XFER_STATE_TX_DONE,
	XFER_STATE_RX_WAIT,
	XFER_STATE_RX_DONE,
	XFER_STATE_OVERFLOW,
	XFER_STATE_TIMEOUT,
};

enum xfer_error {
	XFER_ERR_NONE,
	XFER_ERR_CDPOWER,
	XFER_ERR_TX,
	XFER_ERR_RX,
};

struct block_frame {
	u8 nad;
	u8 pcb;
	u8 len;
	u8 inf[MAX_APDU_DATA_LEN];
	u8 idx;
};

struct tx_data {
	u8 data[MAX_CMD_APDU_LEN];
	u8 idx;
	u32 len;
};

struct rx_data {
	u8 data[MAX_APDU_DATA_LEN];
	u32 len;
	u32 max_len;
};

struct rx_buffer {
	u8 idx;
	u8 ridx;
	u8 data[MAX_APDU_DATA_LEN];
};

struct atr {
	u8 data[MAX_ATR_LEN];
	u8 len;

	u8 TS;
	u8 T0;

	unsigned long data_bits;
	u8 TA[2];
	u8 TB[2];
	u8 TC[2];
	u8 TD[2];

	u8 historical_bytes;
	u8 historical[16];

	u8 TCK;
	u8 conversion;		//0:inverse, 1:direct

	/* global interface bytes TA1, TB1, TC1, TA2, TB2, the first TA for T=15
	 * and the first TB for T=15 */

	/* TA1 */
	u16 Fi;
	u8 fmax;
	u8 Di;

	/* TB1, TB2 deprecated */

	/* TC1 */
	u8 guard_time;

	/* TD1 */
	u8 TD1_transmission_protocol;

	/* TA2 */
	u8 negotiable;		//1: negotiable, 0:specific
	u8 implicit_parameter;
	u8 TA2_transmission_protocol;

	u8 transmission_protocol;

	struct atr_T1 T1_params;
	struct atr_T15 T15_params;

};

/* Refer AT7816L4 User's Manual */
enum sci_phase {
	SCI_PHASE_IDLE = 0,
	SCI_PHASE_COLD_RESET,
	SCI_PHASE_ATR,
	SCI_PHASE_BYTE_MESSAGE,
	SCI_PHASE_BLOCK_MESSAGE,
	SCI_PHASE_DEACTIVATION,
	SCI_PHASE_WARM_RESET,
};

enum sci_debug_print {
	SCI_DEBUG_PRINT_ATR = 0,
	SCI_DEBUG_PRINT_TX_APDU,
	SCI_DEBUG_PRINT_RX_APDU,
};

struct sci_debug {
	struct te_debug_dir *dir;
	bool print_data;
};

struct sci_dev {
	int open_count;
	struct te_subdev subdev;
	struct atr atr;

	enum xfer_state xfer_state;
	bool xfer_done;		//i block received: true. otherwise: false
	enum xfer_error xfer_error;

	struct block_frame tx_block;
	struct block_frame rx_block;

	int num_tx;
	int num_rx;

	struct tx_data tx_data;	/* user requeseted block frame */
	struct rx_data rx_data;	/* data to return */

	struct rx_buffer rx_buffer;

	spinlock_t lock;
	struct mutex mutex;

	u8 deviceNS;
	u8 cardNS;

	u8 cwi;
	u8 bwi;
	u16 Fi;
	u8 Di;

	u32 wtx_bwt; /* msec */
	u8 ifs;
	u32 clock_supplied_khz;

	wait_queue_head_t wq;
	u32 event_mask;
	int event_status;	//event occured check
	enum sci_phase phase;
	struct sci_debug debug;
};

/* CTOP */
u32 sci_ctop_get_clock(void);
void sci_ctop_select_smartcard(void);
void sci_ctop_external_inputmode(void);
void sci_ctop_set_clock(void);

/* DEBUG */
int sci_debug_init(struct sci_dev *dev);
void sci_debug_release(struct sci_dev *dev);

/* ISR */
#define SCI_EVENT_CARD_POWER	(0x1 << 0)
#define SCI_EVENT_RX_DONE	(0x1 << 1)
#define SCI_EVENT_RXFIFO_FULL	(0x1 << 2)
#define SCI_EVENT_TX_ERROR	(0x1 << 3)
#define SCI_EVENT_RX_ERROR	(0x1 << 4)

int sci_isr_init(struct sci_dev *dev);
void sci_isr_cleanup(struct sci_dev *dev);

/*
	FTE: transmitter FIFO-is-Empty interrupt
	FTF: transmitter FIFO-is-FULL interrupt
	FRNE: Receiver FIFO-is-Not_Empty interrupt
*/
typedef enum {
	SCI_IRQ_FRF = 0x01,
	SCI_IRQ_FRNE = 0x02,
	SCI_IRQ_FTF = 0x04,
	SCI_IRQ_FTE = 0x08,
	SCI_IRQ_EOR = 0x10,
	SCI_IRQ_EOT = 0x20,
	SCI_IRQ_ERR = 0x40,
	SCI_IRQ_CDPWR = 0x80,
	SCI_IRQ_ALL = 0xFF
} SCI_IRQ_T;

/* CORE */
struct atr_decoder {
	u8 idx;			/* 0:TA1~TD1, 1:TA2~TD2, ... */
	u8 T;			/* Transmission procotol in TDi-1 */
	u8 Yi;
};

void sci_set_debug_print(struct sci_dev *dev, bool enable);
bool sci_get_debug_print(struct sci_dev *dev);

/* CFG */
struct sci_cfg {
	u32 reg_base_addr;
	int hw_irq_num;
};

void sci_cfg_init(void);
struct sci_cfg *sci_get_config(void);
void sci_isr_set_log_mask(int en);
u32 sci_isr_get_log_mask(void);

extern int g_sci_debug_fd;

#endif				/* _SCI_IMPL_H_ */

/** @} */
