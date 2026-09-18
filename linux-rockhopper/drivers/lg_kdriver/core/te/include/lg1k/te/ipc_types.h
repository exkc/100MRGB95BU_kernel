#ifndef __TE_IPC_TYPES_H__
#define __TE_IPC_TYPES_H__

/*
 * Removed tab with vim
 * :set tabstop=4 shiftwidth=4 expandtab
 * :retab
 */

#ifdef __KERNEL__
#include <linux/types.h>
#else
#include "types.h"
#endif

/* IPC Version */
#define IPC_VERSION 0x03

/* IPC Register Offset */
#define IPC_REG_OFFSET_FW_VERSION 0x00
#define IPC_REG_OFFSET_IPC_VERSION 0x04

#define IPC_REG_OFFSET_CHIP_VERSION 0x10
#define IPC_REG_OFFSET_LOGMASK 0x14
#define IPC_REG_OFFSET_CPU_IPC_VERSION 0x18

#define IPC_REG_OFFSET_CPU_SEND_QUEUE 0x20
#define IPC_REG_OFFSET_MCU_SEND_QUEUE0 0x30
#define IPC_REG_OFFSET_MCU_SEND_QUEUE1 0x40
#define IPC_REG_SEND_QUEUE_OFFSET_ADDR 0x00
#define IPC_REG_SEND_QUEUE_OFFSET_SIZE 0x04
#define IPC_REG_SEND_QUEUE_OFFSET_HEAD 0x08
#define IPC_REG_SEND_QUEUE_OFFSET_TAIL 0x0C

#define IPC_REG_OFFSET_STATUS_SDEC_CH 0x50
#define IPC_REG_OFFSET_STATUS_SDEC_FILTER 0x54

#define IPC_REG_OFFSET_STATUS_ATSC3_CH 0x58
#define IPC_REG_OFFSET_STATUS_ATSC3_PLP 0x5C
#define IPC_REG_OFFSET_STATUS_ATSC3_ALP 0x60
#define IPC_REG_OFFSET_STATUS_ATSC3_IP 0x64
#define IPC_REG_OFFSET_STATUS_ATSC3_UDP 0x68

#define IPC_REG_OFFSET_STATUS_ARIB2_CH 0x6C
#define IPC_REG_OFFSET_STATUS_ARIB2_TLV 0x70
#define IPC_REG_OFFSET_STATUS_ARIB2_IP 0x74
#define IPC_REG_OFFSET_STATUS_ARIB2_MMT_PID 0x78
#define IPC_REG_OFFSET_STATUS_ARIB2_MMT_SI 0x7C
#define IPC_REG_OFFSET_STATUS_ARIB2_MMT_AV 0x80

#define IPC_REG_OFFSET_MAIN_PERF 0x84

#define IPC_REG_OFFSET_STCC0 0xA0
#define IPC_REG_OFFSET_STCC1 0xA4
#define IPC_REG_OFFSET_STCC2 0xA8
#define IPC_REG_OFFSET_STCC3 0xAC
#define IPC_REG_OFFSET_GSTCC0 0xB0
#define IPC_REG_OFFSET_GSTCC1 0xB4

#define IPC_REG_OFFSET_MCU_SEND_QUEUE0_OVF 0xC0
#define IPC_REG_OFFSET_MCU_SEND_QUEUE1_OVF 0xC4
#define IPC_REG_OFFSET_MCU_INT_QUEUE_OVF 0xC8

#define IPC_REG_OFFSET_PDEC_IDX_FOR_DUAL_PID_HFR 0xA0
#define IPC_REG_OFFSET_DESC_PROMEM_BASE 0xA4

#define IPC_CHIP_MASK 0xFF00
#define IPC_CHIP_M16P 0x0100
#define IPC_CHIP_L18F 0x0200
#define IPC_CHIP_O18 0x0300
#define IPC_CHIP_M16PP 0x0400
#define IPC_CHIP_M16P3 0x0500
#define IPC_CHIP_O20 0x0600
#define IPC_CHIP_E60 0x0700
#define IPC_CHIP_O22 0x0800
#define IPC_CHIP_M23 0x0900
#define IPC_CHIP_O24 0x0a00
#define IPC_CHIP_O26 0x0b00

#define IPC_CHIP_REV_MASK 0x00FF

/* IPC Command Types */
#define IPC_NO_ACK (0 << 0)
#define IPC_ACK (1 << 0)
#define GET_IPC_ACK_MODE(t) ((t) & (1 << 0))
#define IS_IPC_ACK_MODE(t) ((t)&IPC_ACK)

#define IPC_RUN_ON_ISR (0 << 1)
#define IPC_RUN_ON_MAIN (1 << 1)
#define GET_IPC_RUN_MODE(t) ((t) & (1 << 1))
#define IS_IPC_RUN_ON_MAIN(t) ((t)&IPC_RUN_ON_MAIN)

#define IPC_WRITER_CPU (0 << 2)
#define IPC_WRITER_MCU (1 << 2)

#define IPC_GROUP_SHIFT 8
#define IPC_GROUP_MASK (0xF << IPC_GROUP_SHIFT)
#define IPC_GROUP_ACK (0 << IPC_GROUP_SHIFT)
#define IPC_GROUP_STATUS (1 << IPC_GROUP_SHIFT)
#define IPC_GROUP_DEBUG (2 << IPC_GROUP_SHIFT)
#define IPC_GROUP_FILTER (3 << IPC_GROUP_SHIFT)
#define IPC_GROUP_TS (4 << IPC_GROUP_SHIFT)
#define IPC_GROUP_DSC (5 << IPC_GROUP_SHIFT)
#define IPC_GROUP_CIP (6 << IPC_GROUP_SHIFT)
#define IPC_GROUP_ATSC3 (7 << IPC_GROUP_SHIFT)
#define IPC_GROUP_ARIB2 (8 << IPC_GROUP_SHIFT)
#define GET_IPC_GROUP(t) ((t)&IPC_GROUP_MASK)

#define IPC_NUM_SHIFT 12
#define GET_IPC_NUMBER(t) (((t) >> IPC_NUM_SHIFT) & 0xF)

#define GEN_IPC_CPU_CMD(group, num, ack, run) \
	(((num) << IPC_NUM_SHIFT) | (group) | IPC_WRITER_CPU | (run) | (ack))
#define GEN_IPC_MCU_CMD(group, num, ack) \
	(((num) << IPC_NUM_SHIFT) | (group) | IPC_WRITER_MCU | (ack))

/* ACK */
#define IPC_TYPE_ACK_CPU \
	GEN_IPC_CPU_CMD(IPC_GROUP_ACK, 0, IPC_NO_ACK, IPC_RUN_ON_ISR)
#define IPC_TYPE_ACK_MCU GEN_IPC_MCU_CMD(IPC_GROUP_ACK, 1, IPC_NO_ACK)

/* IPC Message Types */
#define IPC_MAX_MSG_SIZE 256
#define IPC_MAX_PAYLOAD_SIZE (IPC_MAX_MSG_SIZE - sizeof(IPC_MSG_HEADER_T))

/* Data Information */
#define IPC_SEND_DATA_MSG_SIZE 164
#define IPC_SEND_DATA_XCAS_MSG_SIZE 128
#define IPC_NAGRA_NONCE_LEN 16

typedef struct {
	u16 id;
	u16 type;
	u16 reserved;
	u16 payload_len;
} IPC_MSG_HEADER_T;

typedef struct {
	IPC_MSG_HEADER_T header;
	u8 payload[0]; /* variable value */
} IPC_MSG_T;

/* ACK */
typedef struct {
	u16 id;
	u16 type;
	u16 ret_value; /* return value */
	u16 ret_len;
	u8 ret_data[0]; /* variable */
} IPC_MSG_ACK_T;

typedef enum {
	IPC_RET_OK = 0,
	IPC_RET_NOT_OK,
	IPC_RET_INVALID_MSG,
	IPC_RET_NOT_SUPPORTED,
	IPC_RET_BUSY_NOT_OK,

	IPC_RET_MAX,
} IPC_RET_TYPE_T;

typedef struct {
	u32 waddr;
	u32 raddr;
	u32 pkt_cnt; //Packet Count
	u32 ovf_cnt; //Overflow Count
} IPC_BUF_STATUS_T;

/* Group Specific types are inserted Below */
/*----------------------------------------------------------------------------------------
 *   STATUS Group
 *---------------------------------------------------------------------------------------*/
#define IPC_TYPE_STATUS_PING \
	GEN_IPC_CPU_CMD(IPC_GROUP_STATUS, 0, IPC_ACK, IPC_RUN_ON_ISR)
#define IPC_TYPE_STATUS_INIT_DONE \
	GEN_IPC_MCU_CMD(IPC_GROUP_STATUS, 1, IPC_NO_ACK)
#define IPC_TYPE_STATUS_ERROR GEN_IPC_MCU_CMD(IPC_GROUP_STATUS, 2, IPC_NO_ACK)
#define IPC_TYPE_STATUS_ENGINE_SEL \
	GEN_IPC_CPU_CMD(IPC_GROUP_STATUS, 3, IPC_ACK, IPC_RUN_ON_MAIN)

typedef enum {
	IPC_STATUS_PING_ALIVE = 0,
} IPC_STATUS_PING_TYPE_T;

typedef enum {
	IPC_STATUS_ERROR_EXCEPTION = 0,
	IPC_STATUS_ERROR_ISR,
	IPC_STATUS_ERROR_MAIN_LOOP,
} IPC_STATUS_ERROR_TYPE_T;

typedef enum {
	IPC_STATUS_ENGINE_DEFAULT = 0,
	IPC_STATUS_ENGINE_ATSC3,
	IPC_STATUS_ENGINE_ARIB2,
} IPC_STATUS_ENGINE_TYPE_T;

typedef struct {
	u8 type; /* IPC_STATUS_PING_TYPE_T */
} IPC_MSG_STATUS_PING_T;

typedef struct {
	u16 status; /* IPC_RET_TYPE_T */
} IPC_MSG_STATUS_INIT_DONE_T;

typedef struct {
	u8 type; /* IPC_STATUS_ERROR_TYPE_T */
} IPC_MSG_STATUS_ERROR_T;

typedef struct {
	u8 type; /* IPC_STATUS_ENGINE_TYPE_T */
} IPC_MSG_STATUS_ENGINE_SEL_T;

/*----------------------------------------------------------------------------------------
 *   DEBUG Group
 *---------------------------------------------------------------------------------------*/
#define IPC_TYPE_DEBUG_LOG_MASK \
	GEN_IPC_CPU_CMD(IPC_GROUP_DEBUG, 0, IPC_ACK, IPC_RUN_ON_ISR)
#define IPC_TYPE_DEBUG_LOG_MSG GEN_IPC_MCU_CMD(IPC_GROUP_DEBUG, 1, IPC_NO_ACK)
#define IPC_TYPE_DEBUG_UART GEN_IPC_MCU_CMD(IPC_GROUP_DEBUG, 5, IPC_NO_ACK)
#define IPC_TYPE_DEBUG_CONSOLE \
	GEN_IPC_CPU_CMD(IPC_GROUP_DEBUG, 6, IPC_ACK, IPC_RUN_ON_ISR)
#define IPC_TYPE_DEBUG_WRITE_DATA \
	GEN_IPC_CPU_CMD(IPC_GROUP_DEBUG, 7, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_DEBUG_GET_AUTH \
	GEN_IPC_CPU_CMD(IPC_GROUP_DEBUG, 8, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_DEBUG_SET_CLOCK \
	GEN_IPC_CPU_CMD(IPC_GROUP_DEBUG, 9, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_DEBUG_ENABLE_DEMOD \
	GEN_IPC_CPU_CMD(IPC_GROUP_DEBUG, 10, IPC_ACK, IPC_RUN_ON_MAIN)

typedef struct {
	u16 module; /* refer below enum for module list */
	u16 value;
} IPC_MSG_DEBUG_LOG_MASK_T;

typedef struct {
	u8 len; /* MAX_PAYLOAD_LEN - 1 Byte */
	u8 str[0]; /* Should terminate with NULL */
} IPC_MSG_DEBUG_LOG_MSG_T;

typedef enum {
	IPC_TIMESTAMP_NO_USE = 0,
	IPC_TIMESTAMP_27MHZ_PRECISION,
	IPC_TIMESTAMP_90KHZ_PRECISION,
} IPC_DUMP_TIMESTAMP_TYPE_T;

typedef enum {
	IPC_DUMP_CLK_STCC0 = 0,
	IPC_DUMP_CLK_STCC1,
	IPC_DUMP_CLK_STCC2,
	IPC_DUMP_CLK_STCC3,
	IPC_DUMP_CLK_GSTCC0,
	IPC_DUMP_CLK_GSTCC1,
	IPC_DUMP_CLK_GSTCC2,
	IPC_DUMP_CLK_GSTCC3,
} IPC_DUMP_CLK_SRC_T;

typedef struct {
	u8 ch;
	u8 reserved;
	u8 use_timestamp;
	u8 clock_src; /* IPC_DUMP_CLK_SRC_T */
	u32 unit_size;
	u32 buf_saddr;
	u32 buf_eaddr;
	u32 status_addr; /* IPC_BUF_STATUS_T */
} IPC_MSG_DEBUG_DUMP_START_T, IPC_MSG_DUMP_START_T;

typedef struct {
	u8 ch;
} IPC_MSG_DEBUG_DUMP_STOP_T, IPC_MSG_DUMP_STOP_T;

typedef struct {
	u8 ch;
	u8 reserved1;
	u8 status; /* IPC_DATA_STATUS_TYPE_T */
	u8 reserved2;
	u32 buf_wptr;
} IPC_MSG_DEBUG_DUMP_DATA_T, IPC_MSG_DUMP_DATA_T;

typedef struct {
	u8 use; /* 0:not use(uart mux to cpu), 1:uart mux to mcu */
} IPC_MSG_DEBUG_UART_T;

typedef struct {
	u8 enable; /* 0:disable, 1:enable */
} IPC_MSG_DEBUG_CONSOLE_T;

typedef enum {
	IPC_LOG_MODULE_BASE = 0,
	IPC_LOG_MODULE_FE,
	IPC_LOG_MODULE_DSC,
	IPC_LOG_MODULE_CIPLUS,
	IPC_LOG_MODULE_SECTION,
	IPC_LOG_MODULE_DVR,
	IPC_LOG_MODULE_A3_PLP,
	IPC_LOG_MODULE_A3_BB,
	IPC_LOG_MODULE_A3_ALP,
	IPC_LOG_MODULE_A3_ROHC,
	IPC_LOG_MODULE_A3_IPUDP,
	IPC_LOG_MODULE_A3_LLS,
	IPC_LOG_MODULE_A3_ROUTE,
	IPC_LOG_MODULE_A3_MMT,
	IPC_LOG_MODULE_DEMOD,
	IPC_LOG_MODULE_ARIB_TLV,
	IPC_LOG_MODULE_ARIB_CIP,
	IPC_LOG_MODULE_ARIB_MMT,
	IPC_LOG_MODULE_MAX,
} IPC_LOG_MODULE_T;

typedef enum {
	IPC_LOG_LEVEL_ERROR = 0,
	IPC_LOG_LEVEL_WARN,
	IPC_LOG_LEVEL_NOTI,
	IPC_LOG_LEVEL_INFO,
	IPC_LOG_LEVEL_DEBUG,
} IPC_LOG_LEVEL_T;

typedef enum {
	IPC_DUMP_TS_BUF = 0,
	IPC_DUMP_CLR_BUF,
	IPC_DUMP_CIPLUS_BUF,
} IPC_DUMP_BUFFER_T;

typedef enum {
	IPC_CLK_TYPE_STC = 0,
	IPC_CLK_TYPE_GSTC,
} IPC_CLK_TYPE_T;

typedef enum {
	IPC_CLK_SET_MODE_ENABLE = 0,
	IPC_CLK_SET_MODE_RESET,
	IPC_CLK_SET_MODE_FREQ,
	IPC_CLK_SET_MODE_COUNTER, // in 45khz
	IPC_CLK_SET_MODE_COPY,
	IPC_CLK_SET_MODE_VDEC,
	IPC_CLK_SET_MODE_ADEC,
} IPC_CLK_SET_MODE_T;

typedef struct {
	u8 type; /* IPC_CLK_TYPE_T */
	u8 idx;
	u8 mode; /* IPC_CLK_SET_MODE_T */
	u8 reserved;
	u32 value;
} IPC_MSG_CLK_SET_T;

typedef enum {
	IPC_MAIN_PERF_TYPE_SYS = 0,
	IPC_MAIN_PERF_TYPE_IPC,
	IPC_MAIN_PERF_TYPE_FILTER,
	IPC_MAIN_PERF_TYPE_CIPLUS,
	IPC_MAIN_PERF_TYPE_ATSC3,
	IPC_MAIN_PERF_TYPE_FE,
	IPC_MAIN_PERF_TYPE_DSC,
	IPC_MAIN_PERF_TYPE_DEBUG,
	IPC_MAIN_PERF_TYPE_DEMOD,
	IPC_MAIN_PERF_TYPE_MAX
} IPC_MAIN_PERF_TYPE_T;

typedef struct {
	bool en; // notice enable status to driver
	u32 count;
	u32 curr;
	u32 max;
	u32 total;
} IPC_DEBUG_MAIN_PERF_T;

typedef struct {
	u8 en;
} IPC_MSG_DEBUG_ENABLE_DEMOD_T;

/*----------------------------------------------------------------------------------------
 *   FILTER Group
 *---------------------------------------------------------------------------------------*/
// command magic
#define IPC_TYPE_FILTER_REQUEST \
	GEN_IPC_CPU_CMD(IPC_GROUP_FILTER, 0, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_FILTER_CANCEL \
	GEN_IPC_CPU_CMD(IPC_GROUP_FILTER, 1, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_FILTER_DATA GEN_IPC_MCU_CMD(IPC_GROUP_FILTER, 2, IPC_NO_ACK)
#define IPC_TYPE_TEMI_REQUEST \
	GEN_IPC_CPU_CMD(IPC_GROUP_FILTER, 3, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_TEMI_CANCEL \
	GEN_IPC_CPU_CMD(IPC_GROUP_FILTER, 4, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_TEMI_DATA GEN_IPC_MCU_CMD(IPC_GROUP_FILTER, 5, IPC_NO_ACK)
#define IPC_TYPE_FILTER_SEND_DATA \
	GEN_IPC_CPU_CMD(IPC_GROUP_FILTER, 6, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_FILTER_DUMP_START \
	GEN_IPC_CPU_CMD(IPC_GROUP_FILTER, 7, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_FILTER_DUMP_STOP \
	GEN_IPC_CPU_CMD(IPC_GROUP_FILTER, 8, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_FILTER_DUMP_DATA \
	GEN_IPC_MCU_CMD(IPC_GROUP_FILTER, 9, IPC_NO_ACK)
#define IPC_TYPE_FILTER_XCAS_SEND_DATA \
	GEN_IPC_CPU_CMD(IPC_GROUP_FILTER, 10, IPC_ACK, IPC_RUN_ON_MAIN)

typedef enum {
	IPC_FILTER_REQUEST_SECTION = 0,
	IPC_FILTER_REQUEST_PES,
	IPC_FILTER_REQUEST_RAWTS,
} IPC_FILTER_REQUEST_TYPE_T;

typedef enum {
	IPC_FILTER_STATE_IDLE = 0,
	IPC_FILTER_STATE_RUNNING,
	IPC_FILTER_STATE_WAITING,
} IPC_FILTER_STATE_T;

typedef enum {
	IPC_FILTER_SENDTYPE_PES = 0,
	IPC_FILTER_SENDTYPE_NOTI,
} IPC_FILTER_SENDTYPE_T;

typedef struct {
	u8 ch;
	u8 type; //IPC_FILTER_REQUEST_TYPE_T
	u8 flt_idx;
	u8 req_num;
	u16 pid;
	u16 reserved_0;
	u32 gpb_saddr;
	u32 gpb_eaddr;
	u8 crc;
	u8 one_shot;
	u16 reserved_1;
	u32 value[2];
	u32 mask[2];
	u32 noteq[2];
} IPC_MSG_FILTER_REQUEST_T;

typedef struct {
	u8 ch;
	u8 flt_idx;
} IPC_MSG_FILTER_CANCEL_T;

typedef struct {
	u8 ch;
	u8 status; //IPC_FILTER_DATA_STATUS_TYPE_T
	u8 flt_idx;
	u8 req_num;
	u32 data_saddr;
	u32 data_eaddr;
} IPC_MSG_FILTER_DATA_T;

typedef struct {
	u8 req_num;
	u8 reserved_0;
	u8 reserved_1;
	u8 state; //IPC_FILTER_STATE_T
	u32 gpb_wptr;
	u32 gpb_rptr;
	u8 overflow;
	u8 reserved_2;
	u16 reserved_3;
} IPC_FILTER_STATUS_T;

typedef struct {
	u8 ch;
	u8 reserved_0;
	u8 idx;
	u8 req_num;
	u16 pid;
	u16 unit_size;
	u32 gpb_saddr;
	u32 gpb_eaddr;
} IPC_MSG_TEMI_REQUEST_T;

typedef struct {
	u8 ch;
	u8 idx;
} IPC_MSG_TEMI_CANCEL_T;

typedef struct {
	u8 ch;
	u8 status; //IPC_DATA_STATUS_TYPE_T : Common use
	u8 idx;
	u8 req_num;
	u32 data_saddr;
	u32 data_eaddr;
} IPC_MSG_TEMI_DATA_T;

typedef struct {
	u8 ch;
	u8 data_type; //IPC_FILTER_SENDTYPE_T
	u8 data[IPC_SEND_DATA_MSG_SIZE];
} IPC_MSG_FILTER_SEND_DATA_T;

/*----------------------------------------------------------------------------------------
 *   TS Group
 *---------------------------------------------------------------------------------------*/
#define IPC_TYPE_TS_HEADER_REQUEST \
	GEN_IPC_CPU_CMD(IPC_GROUP_TS, 0, IPC_ACK, IPC_RUN_ON_ISR)
#define IPC_TYPE_TS_HEADER_CANCEL \
	GEN_IPC_CPU_CMD(IPC_GROUP_TS, 1, IPC_ACK, IPC_RUN_ON_ISR)
#define IPC_TYPE_TS_HEADER_DATA GEN_IPC_MCU_CMD(IPC_GROUP_TS, 2, IPC_NO_ACK)
#define IPC_TYPE_TS_CH_RESET \
	GEN_IPC_CPU_CMD(IPC_GROUP_TS, 3, IPC_ACK, IPC_RUN_ON_ISR)
#define IPC_TYPE_TS_OVERFLOW GEN_IPC_MCU_CMD(IPC_GROUP_TS, 4, IPC_NO_ACK)
#define IPC_TYPE_TS_MAIN_DUMP_START \
	GEN_IPC_CPU_CMD(IPC_GROUP_TS, 5, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_TS_MAIN_DUMP_STOP \
	GEN_IPC_CPU_CMD(IPC_GROUP_TS, 6, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_TS_DUMP_DATA GEN_IPC_MCU_CMD(IPC_GROUP_TS, 7, IPC_NO_ACK)
#define IPC_TYPE_VPS_PACKET_PUMP \
	GEN_IPC_CPU_CMD(IPC_GROUP_TS, 8, IPC_ACK, IPC_RUN_ON_ISR)
#define IPC_TYPE_TS_PCR_REQUEST \
	GEN_IPC_CPU_CMD(IPC_GROUP_TS, 9, IPC_ACK, IPC_RUN_ON_ISR)
#define IPC_TYPE_TS_PCR_CANCEL \
	GEN_IPC_CPU_CMD(IPC_GROUP_TS, 10, IPC_ACK, IPC_RUN_ON_ISR)
#define IPC_TYPE_TS_PCR_DATA GEN_IPC_MCU_CMD(IPC_GROUP_TS, 11, IPC_NO_ACK)
#define IPC_TYPE_TS_ISR_DUMP_START \
	GEN_IPC_CPU_CMD(IPC_GROUP_TS, 12, IPC_ACK, IPC_RUN_ON_ISR)
#define IPC_TYPE_TS_ISR_DUMP_STOP \
	GEN_IPC_CPU_CMD(IPC_GROUP_TS, 13, IPC_ACK, IPC_RUN_ON_ISR)

#define IPC_TS_CH_STATUS_SIZE 0x20

#define IPC_TS_HEADER_FLAG_PUSI (1 << 0)

typedef struct {
	u8 ch;
	u8 cnt;
	u16 pid;
	u32 flag; // IPC_TS_HEADER_FLAG_PUSI,...
} IPC_MSG_TS_HEADER_REQUEST_T;

typedef struct {
	u8 ch;
	u8 reserved;
	u16 pid;
} IPC_MSG_TS_HEADER_CANCEL_T;

typedef struct {
	u8 ch;
	u8 reserved;
	u16 pid;
	u32 data; // TS Header Data
} IPC_MSG_TS_HEADER_DATA_T;

typedef struct {
	u8 ch;
} IPC_MSG_TS_CH_RESET_T;

typedef struct {
	u8 ch;
	u8 pdec_idx;
} IPC_MSG_TS_VPS_REQUEST_T;

typedef struct {
	u8 ch;
	u8 reserved;
	u16 pid;
} IPC_MSG_TS_PCR_REQUEST_T;

typedef struct {
	u8 ch;
} IPC_MSG_TS_PCR_CANCEL_T;

typedef struct {
	u8 ch;
	u32 pcr;
	u32 stcc;
} IPC_MSG_TS_PCR_DATA_T;

typedef enum {
	IPC_OVERFLOW_TS_BUF = 0,
	IPC_OVERFLOW_CLEAR_TS_BUF,
	IPC_OVERFLOW_INTERNAL_TS_BUF,
	IPC_OVERFLOW_MAX,
} IPC_OVERFLOW_BUF_TYPE_T;

typedef struct {
	u8 ch;
	u8 type; // IPC_OVERFLOW_BUF_TYPE_T
	u16 reserved;
	u32 cnt;
} IPC_MSG_TS_OVERFLOW_T;

typedef struct {
	u32 full_cnt;
	u32 overflow_cnt;
	u32 syncbyte_errors;
} IPC_TS_CH_STATUS_T;

enum ipc_authority_module {
	IPC_AUTH_NONE = 0,
	IPC_AUTH_DUMP_SDEC,
	IPC_AUTH_DUMP_ATSC3,
	IPC_AUTH_DUMP_ARIB2,
	IPC_AUTH_DUMP_CIPLUS,
	IPC_AUTH_DUMP_DMX,
	IPC_AUTH_DUMP_DVR,
	IPC_AUTH_DUMP_CA,
	IPC_AUTH_DUMP_DELIVERY,
	IPC_AUTH_MAX,
};

enum ipc_writedata_type {
	IPC_WRITE_DEBUG = 0,
	IPC_WRITE_DVR_DN,
	IPC_WRITE_DVR_UP,
};

/*----------------------------------------------------------------------------------------
 *   DSC Group
 *---------------------------------------------------------------------------------------*/
#define IPC_TYPE_DSC_ALGO \
	GEN_IPC_CPU_CMD(IPC_GROUP_DSC, 0, IPC_ACK, IPC_RUN_ON_ISR)
#define IPC_TYPE_DSC_KEY \
	GEN_IPC_CPU_CMD(IPC_GROUP_DSC, 1, IPC_ACK, IPC_RUN_ON_ISR)
#define IPC_TYPE_DSC_SEND_DATA \
	GEN_IPC_CPU_CMD(IPC_GROUP_DSC, 2, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_DSC_RETURN_DATA \
	GEN_IPC_MCU_CMD(IPC_GROUP_DSC, 3, IPC_NO_ACK)
#define IPC_TYPE_DSC_XCAS_SEND_DATA \
	GEN_IPC_CPU_CMD(IPC_GROUP_DSC, 4, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_DSC_XCAS_CANCEL_PID \
	GEN_IPC_CPU_CMD(IPC_GROUP_DSC, 5, IPC_ACK, IPC_RUN_ON_MAIN)

#define IPC_TYPE_DSC_NAGRA_KMSG \
	GEN_IPC_CPU_CMD(IPC_GROUP_DSC, 6, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_DSC_NAGRA_PID_CANCEL \
	GEN_IPC_CPU_CMD(IPC_GROUP_DSC, 7, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_DSC_NAGRA_REQUEST_NONCE \
	GEN_IPC_CPU_CMD(IPC_GROUP_DSC, 8, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_DSC_NAGRA_SET_STATE \
	GEN_IPC_CPU_CMD(IPC_GROUP_DSC, 9, IPC_ACK, IPC_RUN_ON_MAIN)

typedef enum {
	IPC_DSC_ALGO_MODE_CH = 0,
	IPC_DSC_ALGO_MODE_PID,
	IPC_DSC_ALGO_MODE_CH_PID,
	IPC_DSC_ALGO_MODE_MAX,
} IPC_DSC_ALGO_MODE_TYPE_T;

typedef enum {
	IPC_DSC_KEY_MODE_CH = 0,
	IPC_DSC_KEY_MODE_PID_SET,
	IPC_DSC_KEY_MODE_PID_CANCEL,
	IPC_DSC_KEY_MODE_MAX,
} IPC_DSC_KEY_MODE_TYPE_T;

typedef enum {
	IPC_DSC_CAS_BYPASS = 0,
	IPC_DSC_CAS_DES,
	IPC_DSC_CAS_TDES,
	IPC_DSC_CAS_AES,
	IPC_DSC_CAS_DVB_CSA,
	IPC_DSC_CAS_MULTI2,
} IPC_DSC_CAS_TYPE_T;

typedef enum {
	IPC_DSC_BLOCK_ECB = 0,
	IPC_DSC_BLOCK_CBC,
} IPC_DSC_BLOCK_TYPE_T;

typedef enum {
	IPC_DSC_RES_CLEAR = 0,
	IPC_DSC_RES_CTS,
	IPC_DSC_RES_OFB,
} IPC_DSC_RES_TYPE_T;

typedef enum {
	IPC_DSC_KEY_SIZE_64BIT = 0,
	IPC_DSC_KEY_SIZE_128BIT,
	IPC_DSC_KEY_SIZE_192BIT,
	IPC_DSC_KEY_SIZE_256BIT,
} IPC_DSC_KEY_SIZE_T;

typedef enum {
	IPC_DSC_KEY_ATTR_EVEN = 0,
	IPC_DSC_KEY_ATTR_ODD,
	IPC_DSC_KEY_ATTR_MULTI2_SKEY,
	IPC_DSC_KEY_ATTR_MULTI2_IV,
} IPC_DSC_KEY_ATTR_T;

typedef enum {
	IPC_DSC_KEY_TYPE_KEY = 0, /* AES, DES, DVB_CSA, MULTI2 SKEY */
	IPC_DSC_KEY_TYPE_IV,
	IPC_DSC_KEY_TYPE_MULTI2_DKEY,
} IPC_DSC_KEY_TYPE_T;

typedef enum {
	IPC_DSC_KEY_OP_MODE_NORMAL = 0,
	IPC_DSC_KEY_OP_MODE_CIPLUS,
} IPC_DSC_KEY_OPERATION_MODE_T;

typedef enum {
	IPC_DSC_SENDTYPE_KEY = 0,
	IPC_DSC_SENDTYPE_PVR,
} IPC_DSC_SENDTYPE_T;

typedef enum {
	IPC_DSC_CAS_MODE_NORMAL = 0,
	IPC_DSC_CAS_MODE_ECP,
	IPC_DSC_CAS_MODE_XCAS,
	IPC_DSC_CAS_MODE_NAGRA,
	IPC_DSC_CAS_MODE_MAX
} IPC_DSC_CAS_MODE_T;

typedef struct {
	u8 ch;
	u8 mode; // IPC_DSC_ALGO_MODE_TYPE_T
	u8 cas_type; // IPC_DSC_CAS_TYPE_T
	u8 block_type;
	u8 res_type;
	u8 key_size;
	u8 cas_mode; // IPC_DSC_CAS_MODE_T
	u8 reserved;
} IPC_MSG_DSC_ALGO_T;

typedef struct {
	u8 ch;
	u8 mode; //IPC_DSC_KEY_MODE_TYPE_T
	u8 attribute; //IPC_DSC_KEY_ATTR_T
	u8 key_type; //IPC_DSC_KEY_TYPE_T
	u16 pid;
	u8 op_mode; // IPC_DSC_KEY_OPERATION_MODE_T - Deprecated
	u8 reserved;
	u32 data[8];
} IPC_MSG_DSC_KEY_T;

typedef struct {
	u8 ch;
	u8 attribute;
	u8 cas_type; // IPC_DSC_CAS_TYPE_T
	u8 data_type; // IPC_DSC_SENDTYPE_T
	u8 data[IPC_SEND_DATA_MSG_SIZE];
} IPC_MSG_DSC_SEND_DATA_T;

typedef struct {
	u8 ch;
	u8 size;
	u16 reserved;
	u8 data[IPC_SEND_DATA_MSG_SIZE];
} IPC_MSG_DSC_RETURN_DATA_T;

typedef struct {
	u8 ch;
	u8 attribute;
	u8 cas_type;
	u8 data_type;
	u16 pid;
	u16 reserved_0;
	u8 data[IPC_SEND_DATA_XCAS_MSG_SIZE];
} IPC_MSG_DSC_XCAS_DATA_T;

typedef struct pid_cancel {
	u8 ch;
	u8 reserved_0;
	u16 pid;
} IPC_MSG_DSC_XCAS_CANCEL_T, IPC_MSG_DSC_NAGRA_PID_CANCEL_T;

typedef struct {
	u8 ch;
	u8 algo_mode;
	u16 pid;
	u8 attribute; //even/odd
	u8 key_len;
	u8 key_encrypted;
	u8 iv_len;
	u8 iv_encrypted;
	u8 data[32];
	u8 iv[32];
	u8 comm_iv[16];
} IPC_MSG_DSC_NAGRA_KMSG_T;

typedef struct {
	u8 ch;
} IPC_MSG_DSC_NAGRA_REQUEST_NONCE_T;

typedef struct {
	u8 ch;
	u8 data[32];
	u8 comm_iv[16];
} IPC_MSG_DSC_NAGRA_SET_STATE_T;

/*----------------------------------------------------------------------------------------
 *   CIP Group
 *---------------------------------------------------------------------------------------*/
#define IPC_TYPE_CIP_IP_START \
	GEN_IPC_CPU_CMD(IPC_GROUP_CIP, 0, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_CIP_IP_STOP \
	GEN_IPC_CPU_CMD(IPC_GROUP_CIP, 1, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_CIP_IP_DATA GEN_IPC_MCU_CMD(IPC_GROUP_CIP, 2, IPC_NO_ACK)
#define IPC_TYPE_CIP_RF_START \
	GEN_IPC_CPU_CMD(IPC_GROUP_CIP, 3, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_CIP_RF_STOP \
	GEN_IPC_CPU_CMD(IPC_GROUP_CIP, 4, IPC_ACK, IPC_RUN_ON_MAIN)

#define IPC_CIP_CH_BUF_SIZE 0x20

typedef struct {
	u8 ch;
	u8 dir; /* refer below enum */
	u8 lts_id;
	u8 reserved;
	u32 unit_size;
	u32 buf_saddr;
	u32 buf_eaddr;
	u32 status_addr;
} IPC_MSG_CIP_IP_START_T;

typedef struct {
	u8 ch;
	u8 dir; /* use same enum to one of IPC_MSG_CIP_START_T */
} IPC_MSG_CIP_IP_STOP_T;

typedef struct {
	u8 ch;
	u8 dir;
	u8 status;
	u8 reserved;
	u32 buf_addr; /* Structure Point for IPC_BUF_STATUS_T */
} IPC_MSG_CIP_IP_DATA_T;

typedef struct {
	u8 ch;
	u8 reserved[3];
	u32 buf_saddr;
	u32 buf_eaddr;
	u32 status_addr;
} IPC_MSG_CIP_RF_START_T;

typedef struct {
	u8 ch;
} IPC_MSG_CIP_RF_STOP_T;

typedef enum {
	IPC_CIP_DIR_UPSTREAM = 0, /* CPU(DDR) --> MCU(CAM) */
	IPC_CIP_DIR_DNSTREAM, /* MCU(CAM) --> CPU(DDR) */
} IPC_CIP_DIR_T; /* Name of ENUM */

/*----------------------------------------------------------------------------------------
 *   ATSC3.0 Group
 *---------------------------------------------------------------------------------------*/
#define IPC_TYPE_ATSC3_CH_OPEN \
	GEN_IPC_CPU_CMD(IPC_GROUP_ATSC3, 0, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_ATSC3_CH_CLOSE \
	GEN_IPC_CPU_CMD(IPC_GROUP_ATSC3, 1, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_ATSC3_FILTER_REQUEST \
	GEN_IPC_CPU_CMD(IPC_GROUP_ATSC3, 2, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_ATSC3_FILTER_CANCEL \
	GEN_IPC_CPU_CMD(IPC_GROUP_ATSC3, 3, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_ATSC3_DATA GEN_IPC_MCU_CMD(IPC_GROUP_ATSC3, 4, IPC_NO_ACK)
#define IPC_TYPE_ATSC3_CONTROL \
	GEN_IPC_CPU_CMD(IPC_GROUP_ATSC3, 5, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_ATSC3_ENABLE \
	GEN_IPC_CPU_CMD(IPC_GROUP_ATSC3, 6, IPC_ACK, IPC_RUN_ON_MAIN)

#define IPC_ATSC3_PLP_STATUS_SIZE 0x20
#define IPC_ATSC3_IP_STATUS_SIZE 0x20
#define IPC_ATSC3_LKS_STATUS_SIZE 0x20
#define IPC_ATSC3_UDP_STATUS_SIZE 0x30
#define IPC_ATSC3_CH_STATUS_SIZE 0x20

#define IPC_MAX_IP_LEN 4

#define IPC_ROUTE_FLAG_PT_L (1 << 0)
#define IPC_ROUTE_FLAG_PT_H (1 << 1)
#define IPC_ROUTE_FLAG_SCT_L (1 << 2)
#define IPC_ROUTE_FLAG_SCT_H (1 << 3)

typedef enum {
	IPC_ATSC3_FILTER_TYPE_PLP = 0x00,
	IPC_ATSC3_FILTER_TYPE_LKS = 0x10,
	IPC_ATSC3_FILTER_TYPE_IP = 0x20,

	IPC_ATSC3_FILTER_TYPE_UDP = 0x30,
	IPC_ATSC3_FILTER_TYPE_UDP_LLS = IPC_ATSC3_FILTER_TYPE_UDP,
	IPC_ATSC3_FILTER_TYPE_UDP_ROUTE_OBJ,
	IPC_ATSC3_FILTER_TYPE_UDP_ROUTE_AV,
	IPC_ATSC3_FILTER_TYPE_UDP_ROUTE_SLS,
	IPC_ATSC3_FILTER_TYPE_UDP_MMT_SIGNAL,
	IPC_ATSC3_FILTER_TYPE_UDP_MMT_AV,
	IPC_ATSC3_FILTER_TYPE_UDP_MAX,

	IPC_ATSC3_FILTER_TYPE_MAX,
} IPC_ATSC3_FILTER_TYPE_T;

typedef enum {
	IPC_DATA_STATUS_OK = 0x0,
	IPC_DATA_STATUS_OVERFLOW_OVERLAPS_PTR,
	IPC_DATA_STATUS_OVERFLOW_NOT_ENOUGH_BUF,
	IPC_DATA_STATUS_MAX,
} IPC_DATA_STATUS_TYPE_T; //Common use

typedef enum {
	IPC_ATSC3_CONTROL_MAX,
} IPC_ATSC3_CONTROL_TYPE_T;

enum ipc_data_route_mode {
	IPC_DATA_ROUTE_OBJ_MODE = 0x0,
	IPC_DATA_ROUTE_MDE_MODE = 0x1,
};

enum ipc_atsc3_filter_control {
	IPC_ATSC3_FILTER_DISABLE = 0,
	IPC_ATSC3_FILTER_ENABLE = 1,
};

typedef struct {
	u8 ch;
	u8 reserved_0;
	u16 reserved_1;
	u32 metabuf_saddr;
	u32 metabuf_eaddr;
	u32 databuf_saddr;
	u32 databuf_eaddr;
	u32 bbbuf_saddr;
	u32 bbbuf_eaddr;
} IPC_MSG_ATSC3_CH_OPEN_T;

typedef struct {
	u8 ch;
} IPC_MSG_ATSC3_CH_CLOSE_T;

typedef struct {
	u8 req_num;
	u8 oneshot;
	u16 reserved_0;
	u32 gpb_saddr;
	u32 gpb_eaddr;
	u32 filter_value;
	u32 filter_mask;
	u32 filter_noteq;
	u8 plpid_value;
	u8 plpid_mask;
	u8 plpid_noteq;
	u8 reserved_1;
} IPC_ATSC3_LKS_REQ_PAYLOAD_T;

typedef struct {
	u32 ipbuf_saddr;
	u32 ipbuf_eaddr;
	u8 src_ip[IPC_MAX_IP_LEN];
	u8 dst_ip[IPC_MAX_IP_LEN];
} IPC_ATSC3_IP_REQ_PAYLOAD_T;

typedef struct {
	u8 req_num;
	u8 oneshot;
	u8 ip_idx;
	u8 reserved_0;
	u16 dst_port;
	u16 reserved_1;
	u32 gpb_saddr;
	u32 gpb_eaddr;
} IPC_ATSC3_UDP_REQ_INFO_T;

typedef struct {
	IPC_ATSC3_UDP_REQ_INFO_T info;
	u32 filter_value;
	u32 filter_mask;
	u32 filter_noteq;
	u8 plpid_value;
	u8 plpid_mask;
	u8 plpid_noteq;
	u8 reserved_0;
} IPC_ATSC3_UDP_LLS_REQ_PAYLOAD_T;

// For CodePoint Information
typedef struct {
	u8 cp;
	u8 fec_payload_id;
	u16 reserved_0;
} IPC_ATSC3_UDP_CP_INFO_T;

typedef struct {
	u32 tsi;
	u32 cp_addr;
	u8 cp_num;
	u8 ignore_dup;
	u16 reserved_0;
} IPC_ATSC3_UDP_ROUTE_REQ_INFO_T;

typedef struct {
	IPC_ATSC3_UDP_REQ_INFO_T info;
	IPC_ATSC3_UDP_ROUTE_REQ_INFO_T route_info;
	u32 toi_value;
	u32 toi_mask;
	u32 toi_noteq;
} IPC_ATSC3_UDP_ROUTE_OBJ_REQ_PAYLOAD_T;

typedef struct {
	IPC_ATSC3_UDP_REQ_INFO_T info;
	IPC_ATSC3_UDP_ROUTE_REQ_INFO_T route_info;
	u32 init_toi;
	u32 num_start;
} IPC_ATSC3_UDP_ROUTE_AV_REQ_PAYLOAD_T;

typedef struct {
	IPC_ATSC3_UDP_REQ_INFO_T info;
	u16 packet_id;
	u16 reserved_0;
	u32 msg_value;
	u32 msg_mask;
	u32 msg_noteq;
	u32 table_value;
	u32 table_mask;
	u32 table_noteq;
	u32 content_value;
	u32 content_mask;
	u32 content_noteq;
} IPC_ATSC3_UDP_MMT_SIGNAL_REQ_PAYLOAD_T;

typedef struct {
	IPC_ATSC3_UDP_REQ_INFO_T info;
	u16 packet_id;
	u16 reserved_0;
} IPC_ATSC3_UDP_MMT_AV_REQ_PAYLOAD_T;

typedef struct {
	u8 ch;
	u8 type;
	u8 reserved;
	u8 flt_idx;
} IPC_ATSC3_FLT_REQ_INFO_T;

typedef struct {
	IPC_ATSC3_FLT_REQ_INFO_T info;
	union {
		u8 req_payload[0];
		IPC_ATSC3_LKS_REQ_PAYLOAD_T lks;
		IPC_ATSC3_IP_REQ_PAYLOAD_T ip;
		IPC_ATSC3_UDP_LLS_REQ_PAYLOAD_T lls;
		IPC_ATSC3_UDP_ROUTE_OBJ_REQ_PAYLOAD_T route_obj;
		IPC_ATSC3_UDP_ROUTE_AV_REQ_PAYLOAD_T route_av;
		IPC_ATSC3_UDP_MMT_SIGNAL_REQ_PAYLOAD_T mmt_sig;
		IPC_ATSC3_UDP_MMT_AV_REQ_PAYLOAD_T mmt_av;
	};
} IPC_MSG_ATSC3_FLT_REQ_T;

typedef struct {
	u8 ch;
	u8 type;
	u8 reserved_0;
	u8 flt_idx;
} IPC_MSG_ATSC3_FLT_CANCEL_T;

typedef struct {
	u8 ch;
	u8 type;
	u8 req_num;
	u8 flt_idx;
	u8 status;
	u8 reserved_0;
	u16 reserved_1;
} IPC_MSG_ATSC3_DATA_INFO_T;

typedef struct {
	u32 data_saddr;
	u32 data_eaddr;
	u8 ver;
	u8 type;
	u16 type_ext;
	u8 fmt; // format
	u8 enc; // encoding
	u16 reserved_0;
} IPC_ATSC3_LKS_DATA_PAYLOAD_T;

typedef struct {
	u32 data_saddr;
	u32 data_eaddr;
} IPC_ATSC3_UDP_DATA_INFO_T;

typedef struct {
	IPC_ATSC3_UDP_DATA_INFO_T info;
} IPC_ATSC3_UDP_LLS_DATA_PAYLOAD_T;

typedef struct {
	IPC_ATSC3_UDP_DATA_INFO_T info;
	u8 err_indicator;
	u8 reserved_0;
	u16 reserved_1;
	u32 toi;
} IPC_ATSC3_UDP_ROUTE_OBJ_DATA_PAYLOAD_T;

typedef struct {
	IPC_ATSC3_UDP_DATA_INFO_T info;
	u8 err_indicator;
	u8 reserved_0;
	u16 reserved_1;
	u32 toi;
	u8 mode;
	u8 reserved_2;
	u16 reserved_3;
	// under entries are valid only if mode == IPC_DATA_ROUTE_MDE_MODE
	u8 flags; // 0:7 -> [0]pt_l:[1]pt_h:[2]sct_l:[3]sct_h:[4-]reserved
	u8 reserved_4;
	u16 reserved_5;
	u32 object_len;
	u32 sct_high; // valid only if sct_h is set
	u32 sct_low; // valid only if sct_l is set
	u32 pt_high; // valid only if pt_h is set
	u32 pt_low; // valid only if pt_l is set
} IPC_ATSC3_UDP_ROUTE_AV_DATA_PAYLOAD_T;

typedef struct {
	IPC_ATSC3_UDP_DATA_INFO_T info;
} IPC_ATSC3_UDP_MMT_SIGNAL_DATA_PAYLOAD_T;

typedef struct {
	IPC_ATSC3_UDP_DATA_INFO_T info;
	u32 timestamp;
	u8 rap; // Random Access Pointer flag
	u8 mpu_type; // MPU fragment type
	u8 priority;
	u8 dep_counter; // Dependency Counter
	u32 mpu_seq_num;
	u32 mov_frag_seq_num;
	u32 sample_number;
	u32 offset;
} IPC_ATSC3_UDP_MMT_AV_DATA_PAYLOAD_T;

typedef struct {
	IPC_MSG_ATSC3_DATA_INFO_T info;
	union {
		u8 data_payload[0]; // valid if status == IPC_DATA_STATUS_OK
		IPC_ATSC3_LKS_DATA_PAYLOAD_T lks;
		IPC_ATSC3_UDP_LLS_DATA_PAYLOAD_T lls;
		IPC_ATSC3_UDP_ROUTE_OBJ_DATA_PAYLOAD_T route_obj;
		IPC_ATSC3_UDP_ROUTE_AV_DATA_PAYLOAD_T route_av;
		IPC_ATSC3_UDP_MMT_SIGNAL_DATA_PAYLOAD_T mmt_sig;
		IPC_ATSC3_UDP_MMT_AV_DATA_PAYLOAD_T mmt_av;
	};
} IPC_MSG_ATSC3_DATA_T;

typedef struct {
	u8 ch;
	u8 type;
	u8 reserved_0;
	u8 flt_idx;
	u8 control;
	u8 reserved_1;
	u16 reserved_2;
} IPC_MSG_ATSC3_CONTROL_T;

typedef struct {
	u32 packet_cnt;
	u32 err_packet_cnt;
	u32 packet_len;
} IPC_ATSC3_CH_STATUS_T;

typedef struct {
	u8 reserved_0;
	u8 plp_id;
	u8 reserved_1;
	u8 status;
	u32 packet_cnt;
	u32 cc_err_cnt;
	u32 extmode_err_cnt;
	u32 pointer_err_cnt;
	u32 alp_header_err_cnt;
} IPC_ATSC3_PLP_STATUS_T;

typedef struct {
	u8 request_num;
	u8 reserved_0;
	u8 reserved_1;
	u8 status;
	u32 gpb_wptr;
	u32 gpb_rptr;
	u32 overflow;
} IPC_ATSC3_LKS_STATUS_T;

typedef struct {
	u16 reserved_0;
	u8 reserved_1;
	u8 status;
	u32 gpb_wptr;
	u32 gpb_rptr;
	u16 vers4_err;
	u16 not_udp;
	u16 hdr_len_err;
	u16 hdr_len_mismatch;
	u16 frag_offset_err;
	u16 frag_buf_ovf;
	u16 chksum_err;
	u16 reserved_2;
	u32 packet_cnt;
} IPC_ATSC3_IP_STATUS_T;

typedef struct {
	u16 vers1_err;
	u16 protocol_err;
	u16 flag_err; // (TSI, TOI, Half...)
	u16 multi_objlen; // Multiple object length field exist
	u16 multi_sct; // Multi-SCT field exist
	u16 multi_prestime; // Multi-pres time exist
	u16 no_ofs_len; // No Offset Length Error
	u16 unknown_obj; // Unknown Object (GATHERING)
	u16 no_ofs_gathering; // No Offset while gathering is in progress
	u16 jump_next_toi; // Jump to next TOI
	u16 ofs_rewind; // Offset rewind
	u16 skip_byte; // Skip Bytes
	u16 object_rollback; // Object Rollback
	u16 reserved_0;
} IPC_ATSC3_UDP_ROUTE_ERR_CNT_T;

typedef struct {
	u16 vers1_err;
	u16 fec_protect_err; // Fec protection err
	u16 seqnum_discnt; // Sequence number discontinuity
	u16 non_timed; // Non timed cnt
	u16 file_type_err;
	u16 frag_discnt; // Fragment count discontinuity
} IPC_ATSC3_UDP_MMT_ERR_CNT_T;

typedef struct {
	u32 old_lls_cnt;
} IPC_ATSC3_UDP_LLS_ERR_CNT_T;

typedef struct {
	u8 request_num;
	u8 filter_type;
	u8 is_mde;
	u8 status;
	u32 gpb_wptr;
	u32 gpb_rptr;
	u32 overflow;
	union {
		IPC_ATSC3_UDP_ROUTE_ERR_CNT_T route;
		IPC_ATSC3_UDP_MMT_ERR_CNT_T mmt;
		IPC_ATSC3_UDP_LLS_ERR_CNT_T lls;
	};
} IPC_ATSC3_UDP_STATUS_T;

/*----------------------------------------------------------------------------------------
 *   ARIB2.0 Group
 *---------------------------------------------------------------------------------------*/
#define IPC_TYPE_ARIB2_CH_OPEN \
	GEN_IPC_CPU_CMD(IPC_GROUP_ARIB2, 0, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_ARIB2_CH_CLOSE \
	GEN_IPC_CPU_CMD(IPC_GROUP_ARIB2, 1, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_ARIB2_FILTER_REQUEST \
	GEN_IPC_CPU_CMD(IPC_GROUP_ARIB2, 2, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_ARIB2_FILTER_CANCEL \
	GEN_IPC_CPU_CMD(IPC_GROUP_ARIB2, 3, IPC_ACK, IPC_RUN_ON_MAIN)
#define IPC_TYPE_ARIB2_DATA GEN_IPC_MCU_CMD(IPC_GROUP_ARIB2, 4, IPC_NO_ACK)
#define IPC_TYPE_ARIB2_CONTROL \
	GEN_IPC_CPU_CMD(IPC_GROUP_ARIB2, 5, IPC_ACK, IPC_RUN_ON_MAIN)

#define IPC_ARIB2_CH_STATUS_SIZE 0x20
#define IPC_ARIB2_TLV_SI_FILTER_STATUS_SIZE 0x20
#define IPC_ARIB2_IP_STATUS_SIZE 0x40
#define IPC_ARIB2_MMT_PID_STATUS_SIZE 0x20
#define IPC_ARIB2_MMT_SI_FILTER_STATUS_SIZE 0x20
#define IPC_ARIB2_MMT_AV_FILTER_STATUS_SIZE 0x20

#define IPC_MAX_IP6_LEN 16

typedef struct {
	u8 ch;
	u8 reserved_0;
	u16 reserved_1;
	u32 meta_buf_saddr;
	u32 meta_buf_eaddr;
	u32 data_buf_saddr;
	u32 data_buf_eaddr;
	u32 temp_buf_saddr;
	u32 temp_buf_eaddr;
} IPC_MSG_ARIB2_CH_OPEN_T;

typedef struct {
	u8 ch;
} IPC_MSG_ARIB2_CH_CLOSE_T;

typedef enum {
	IPC_ARIB2_FILTER_TYPE_TLV_SI = 0x00,

	IPC_ARIB2_FILTER_TYPE_MMT_PID = 0x10,
	IPC_ARIB2_FILTER_TYPE_MMT_SI,
	IPC_ARIB2_FILTER_TYPE_MMT_AV,

	IPC_ARIB2_FILTER_TYPE_IP = 0x20,

	IPC_ARIB2_FILTER_TYPE_MAX,
} IPC_ARIB2_FILTER_TYPE_T;

typedef struct {
	u8 ch;
	u8 type;
	u8 reserved;
	u8 flt_idx;
} IPC_ARIB2_FLT_REQ_INFO_T;

typedef struct {
	u8 req_num;
	u8 one_shot;
	u16 reserved;
	// Filter Parameters
	u32 value[2];
	u32 mask[2];
	u32 noteq[2];
	// GPB
	u32 gpb_saddr;
	u32 gpb_eaddr;
} IPC_ARIB2_TLV_SIGNAL_REQ_PAYLOAD_T;

typedef enum {
	IPC_ARIB2_DATA_TYPE_SIGNAL = 0,
	IPC_ARIB2_DATA_TYPE_AUDIO,
	IPC_ARIB2_DATA_TYPE_VIDEO,
	IPC_ARIB2_DATA_TYPE_MAX,
} IPC_ARIB2_DATA_TYPE_T;

typedef struct {
	u8 data_type; // A/V or SI
	u8 direct_play; // phase2. deliver MFU to A/V DEC via MCU1
	u16 packet_id;
	u32 seg_buf_saddr; // TODO: if data_type is A/V, MCU1 use segment buffer as output buffer(MCU0 should deliver the buffer to MCU1)
	u32 seg_buf_eaddr;
} IPC_ARIB2_MMT_PID_REQ_PAYLOAD_T;

typedef struct {
	u8 req_num;
	u8 one_shot;
	u16 pidf_idx;

	u16 message_id;
	u16 reserved;

	u32 value[2];
	u32 mask[2];
	u32 noteq[2];

	u32 gpb_saddr;
	u32 gpb_eaddr;
} IPC_ARIB2_MMT_SIGNAL_REQ_PAYLOAD_T;

typedef struct {
	u8 req_num;
	u8 reserved;
	u16 pidf_idx;

	u32 gpb_saddr;
	u32 gpb_eaddr;
} IPC_ARIB2_MMT_AV_REQ_PAYLOAD_T;

typedef struct {
	IPC_ARIB2_FLT_REQ_INFO_T info;
	union {
		u8 req_payload[0];
		IPC_ARIB2_TLV_SIGNAL_REQ_PAYLOAD_T tlv_si;
		IPC_ARIB2_MMT_PID_REQ_PAYLOAD_T mmt_pid;
		IPC_ARIB2_MMT_SIGNAL_REQ_PAYLOAD_T mmt_si;
		IPC_ARIB2_MMT_AV_REQ_PAYLOAD_T mmt_av;
	};
} IPC_MSG_ARIB2_FLT_REQ_T;

typedef struct {
	u8 ch;
	u8 type;
	u8 reserved_0;
	u8 flt_idx;
} IPC_MSG_ARIB2_FLT_CANCEL_T;

typedef struct {
	u8 ch;
	u8 type;
	u8 req_num;
	u8 flt_idx;
	u8 status;
	u8 reserved_0;
	u16 reserved_1;
	u32 data_saddr;
	u32 data_eaddr;
} IPC_MSG_ARIB2_DATA_INFO_T;

typedef struct {
	u8 table_id;
} IPC_ARIB2_TLV_SIGNAL_DATA_PAYLOAD_T;

typedef struct {
	u16 msg_id;
} IPC_ARIB2_MMT_SIGNAL_DATA_PAYLOAD_T;

typedef struct {
	u8 rap_f;
	u8 timed; // IPC_ARIB2_MMT_AV_DATA_TIMED_T
	u16 reserved;
	u32 mpu_seq_number;
	u32 item_id; // valid only if non-timed data
	u8 scr_ctrl;
	u8 scr_init_counter[16];
} IPC_ARIB2_MMT_AV_DATA_PAYLOAD_T;

typedef struct {
	IPC_MSG_ARIB2_DATA_INFO_T info;
	union {
		u8 data_payload[0];
		//IPC_ARIB2_TLV_SIGNAL_DATA_PAYLOAD_T tlv_si;
		//IPC_ARIB2_MMT_SIGNAL_DATA_PAYLOAD_T mmt_si;
		IPC_ARIB2_MMT_AV_DATA_PAYLOAD_T mmt_av;
	};
} IPC_MSG_ARIB2_DATA_T;

typedef struct {
	u8 status;
	u8 reserved;
	u16 reserved_1;

	u32 packet_cnt;
	u32 err_packet_cnt;
} IPC_ARIB2_CH_STATUS_T;

typedef struct {
	u8 request_num;
	u8 status;
	u16 reserved;

	u32 gpb_wptr;
	u32 gpb_rptr;
	u32 overflow_cnt;
} IPC_ARIB2_TLV_SI_FILTER_STATUS_T;

typedef struct {
	u8 status;
	u8 reserved_0;
	u16 cid; // context id
	u32 packet_cnt;
	u32 err_packet_cnt;
	u32 cid_chg_cnt; // CID changed
	u32 ip_chg_cnt; // CID same, IP changed
	u32 sn_err_cnt; // sequence number discontinuity count
	u16 src_port;
	u16 dst_port;
	u8 src_addr[16];
	u8 dst_addr[16];
} IPC_ARIB2_IP_STATUS_T;

typedef struct {
	u8 status;
	u8 reserved_0;
	u16 reserved_1;

	u32 packet_cnt;
	u32 err_packet_cnt;
} IPC_ARIB2_MMT_PID_STATUS_T;

typedef struct {
	u8 request_num;
	u8 status;
	u16 reserved;

	u32 gpb_wptr;
	u32 gpb_rptr;
	u32 overflow;
} IPC_ARIB2_MMT_SI_FILTER_STATUS_T;

typedef struct {
	u8 request_num;
	u8 status;
	u16 reserved;

	u32 gpb_wptr;
	u32 gpb_rptr;
	u32 overflow;
} IPC_ARIB2_MMT_AV_FILTER_STATUS_T;

#endif /* __TE_IPC_TYPES_H__ */
