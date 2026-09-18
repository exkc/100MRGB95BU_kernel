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
 *  @author	Kyungseok Hyun (ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2015-02-04
 *  @note		Additional information.
 */

#ifndef _LG1K_TE_IPC_H_
#define _LG1K_TE_IPC_H_

#include <linux/types.h>

#include "ipc_types.h"

typedef int (*ipc_msg_callback_t)(void *msg, void *arg);

enum ipc_dump_type {
	IPC_DUMP_TYPE_FE_ISR = 0,	/* dump in isr */
	IPC_DUMP_TYPE_FE_MAIN,		/* dump in main loop */
	IPC_DUMP_TYPE_BE,		/* dump in isr */
};

/* Internal Structure for send information to TE_IPC_funcs.. */

typedef struct {
	u8 type;		//IPC_FILTER_REQUEST_TYPE_T
	u8 flt_idx;
	u8 req_num;
	u16 pid;
	u16 unit_size;
	u32 gpb_saddr;
	u32 gpb_eaddr;
	u8 crc;
	u8 one_shot;
	u32 value[2];
	u32 mask[2];
	u32 noteq[2];
} IPC_ADAP_FILTER_REQUEST_T;	//check IPC_MSG_FILTER_REQUEST_T

typedef struct {
	enum ipc_dump_type type;
	u8 use_timestamp;
	u8 clock_src;
	u32 unit_size;
	u32 saddr;
	u32 eaddr;
} IPC_ADAP_DEBUG_DUMP_INFO_T;

typedef struct {
	u32 metabuf_saddr;
	u32 metabuf_eaddr;
	u32 databuf_saddr;
	u32 databuf_eaddr;
	u32 bbbuf_saddr;
	u32 bbbuf_eaddr;
} IPC_ADAP_ATSC3_CHBUF_INFO_T;

typedef struct {
	u32 meta_saddr;
	u32 meta_eaddr;
	u32 data_saddr;
	u32 data_eaddr;
	u32 temp_saddr;
	u32 temp_eaddr;
} IPC_ADAP_ARIB2_CHBUF_INFO_T;

enum pes_dest_type {
	IPC_CLK_PES_DEST_VD0 = 0,
	IPC_CLK_PES_DEST_VD1,
	IPC_CLK_PES_DEST_AD0,
	IPC_CLK_PES_DEST_AD1
};

/*------------------------------------------------------------------------------
 *   DEBUG Group
 *----------------------------------------------------------------------------*/
int te_ipc_write_data(const void *data, u32 size);
int te_ipc_get_authority(enum ipc_authority_module m);

int TE_IPC_StartInputDump(u8 ch, IPC_ADAP_DEBUG_DUMP_INFO_T *info);
int TE_IPC_StopInputDump(u8 ch);
int TE_IPC_RegisterDumpUpdateCallback(u8 ch, ipc_msg_callback_t callback,
				      void *arg);
int TE_IPC_SetInputDumpRptr(u8 ch, u32 rptr);
int TE_IPC_GetInputDumpWptr(u8 ch, u32 *wptr);
int TE_IPC_GetInputDumpBufStatus(u8 ch, IPC_BUF_STATUS_T *status);
int te_ipc_get_stcc(u8 idx, u32 *stcc_32, u32 *stcc_31_0);
int te_ipc_get_gstcc(u8 idx, u32 *gstcc_32, u32 *gstcc_31_0);
int te_ipc_set_stcc(u8 idx, u32 stcc_32, u32 stcc_31_0);
int te_ipc_set_gstcc(u8 idx, u32 gstcc_32, u32 gstcc_31_0);
int te_ipc_reset_stcc(u8 idx);
int te_ipc_reset_gstcc(u8 idx);
int te_ipc_enable_stcc(u8 idx, u8 en);
int te_ipc_enable_gstcc(u8 idx, u8 en);
int te_ipc_set_stcc_freq(u8 idx, u32 freq);
int te_ipc_set_gstcc_freq(u8 idx, u32 freq);
int te_ipc_set_stcc_copy_enable(u8 idx);
int te_ipc_set_stcc_source(u8 idx, enum pes_dest_type type);

//DEMOD unified only
int te_ipc_enable_demod(u8 en);
/*------------------------------------------------------------------------------
 *   FILTER Group
 *----------------------------------------------------------------------------*/
int TE_IPC_RequestStreamFilter(u8 ch, const IPC_ADAP_FILTER_REQUEST_T *m);
int TE_IPC_CancelStreamFilter(u8 ch, u8 idx);
int TE_IPC_GetStreamFilterStatus(u16 idx, IPC_FILTER_STATUS_T *status);
int TE_IPC_SetStreamFilterRptr(u16 idx, u32 ptr);
int TE_IPC_GetStreamFilterWptr(u16 idx, u32 *ptr);
int TE_IPC_RegisterStreamFilterCallback(ipc_msg_callback_t callback, void *arg);

int te_ipc_request_temi_filter(u8 ch, IPC_ADAP_FILTER_REQUEST_T *f);
int te_ipc_cancel_temi_filter(u8 ch, u8 idx);
int te_ipc_register_temi_callback(ipc_msg_callback_t callback, void *arg);
int te_ipc_send_filter_data(IPC_MSG_FILTER_SEND_DATA_T *msg);
int te_ipc_send_filter_xcas_data(IPC_MSG_FILTER_SEND_DATA_T *msg);

/*------------------------------------------------------------------------------
 *   TS Group
 *----------------------------------------------------------------------------*/
int TE_IPC_RequestTsHeader(IPC_MSG_TS_HEADER_REQUEST_T *msg);
int TE_IPC_CancelTsHeader(IPC_MSG_TS_HEADER_CANCEL_T *msg);
int TE_IPC_RegisterTsHeaderCallback(ipc_msg_callback_t callback, void *arg);
int TE_IPC_ChannelReset(u8 ch);
int TE_IPC_GetChannelStatus(u8 ch, IPC_TS_CH_STATUS_T *status);
const char *TE_IPC_GetOverflowBufTypeStr(IPC_OVERFLOW_BUF_TYPE_T type);

int te_ipc_request_pcr_pid(u8 ch, u16 pid);
int te_ipc_cancel_pcr_pid(u8 ch);
int te_ipc_register_pcr_callback(ipc_msg_callback_t callback, void *arg);

/*------------------------------------------------------------------------------
 *   DSC Group
 *----------------------------------------------------------------------------*/
int TE_IPC_SetCipherMode(IPC_MSG_DSC_ALGO_T *msg);
int TE_IPC_SetCipherKey(IPC_MSG_DSC_KEY_T *msg);
int te_ipc_send_dsc_data(IPC_MSG_DSC_SEND_DATA_T *msg);
int te_ipc_send_xcas_data(IPC_MSG_DSC_XCAS_DATA_T *msg);
int te_ipc_cancel_xcas_pid(IPC_MSG_DSC_XCAS_CANCEL_T *msg);
int te_ipc_register_dsc_callback(ipc_msg_callback_t cb, void *arg);
int te_ipc_set_nagra_key(IPC_MSG_DSC_NAGRA_KMSG_T *msg);
int te_ipc_cancel_nagra_pid(struct pid_cancel *msg);
int te_ipc_get_nagra_nonce(IPC_MSG_DSC_NAGRA_REQUEST_NONCE_T *msg);
int te_ipc_set_nagra_state(IPC_MSG_DSC_NAGRA_SET_STATE_T *msg);

/*------------------------------------------------------------------------------
 *   CIP Group
 *----------------------------------------------------------------------------*/
int TE_IPC_StartCIPLUSUpload(u8 ch, u32 saddr, u32 eaddr, u32 unit_size,
			     u8 lts_id);
int TE_IPC_StopCIPLUSUpload(u8 ch);
int TE_IPC_GetCIPLUSUploadRptr(u8 ch, u32 *ptr);
int TE_IPC_UpdateCIPLUSUploadWptr(u8 ch, u32 ptr);
int TE_IPC_GetCIPLUSUploadStatus(u8 ch,
				 u32 *rptr, u32 *wptr, u32 *pkt_cnt,
				 u32 *ovf_cnt);

int TE_IPC_StartCIPLUSDownload(u8 ch, u32 saddr, u32 eaddr, u32 unit_size,
			       u8 lts_id);
int TE_IPC_StopCIPLUSDownload(u8 ch);
int TE_IPC_GetCIPLUSDownloadWptr(u8 ch, u32 *ptr);
int TE_IPC_UpdateCIPLUSDownloadRptr(u8 ch, u32 ptr);
int TE_IPC_GetCIPLUSDownloadStatus(u8 ch,
				   u32 *rptr, u32 *wptr, u32 *pkt_cnt,
				   u32 *ovf_cnt);

int TE_IPC_RegisterCIPLUSDataCallback(ipc_msg_callback_t callback, void *arg);

/*------------------------------------------------------------------------------
 *   ATSC3.0 Group
 *----------------------------------------------------------------------------*/
int TE_IPC_RegisterATSC3FilterCallback(ipc_msg_callback_t callback, void *arg);
int TE_IPC_RequestATSC3Filter(u8 ch, IPC_ATSC3_FILTER_TYPE_T type, u8 idx,
			      u8 payload_len, void *payload);
int TE_IPC_CancelATSC3Filter(IPC_MSG_ATSC3_FLT_CANCEL_T *msg);
int TE_IPC_OpenATSC3Channel(u8 ch, IPC_ADAP_ATSC3_CHBUF_INFO_T *m);
int TE_IPC_CloseATSC3Channel(u8 ch);
int TE_IPC_GetATSC3FilterStatus(u16 idx, u8 type, void *status);
int TE_IPC_GetATSC3ChannelStatus(u8 ch, IPC_ATSC3_CH_STATUS_T *status);
int TE_IPC_ControlATSC3(IPC_MSG_ATSC3_CONTROL_T *msg);
int TE_IPC_SetATSC3FilterRptr(u16 idx, u8 type, u32 ptr);

/*------------------------------------------------------------------------------
 *   ARIB2 Group
 *----------------------------------------------------------------------------*/
int TE_IPC_RegisterARIB2FilterCallback(ipc_msg_callback_t callback, void *arg);
int TE_IPC_OpenARIB2Channel(u8 ch, IPC_ADAP_ARIB2_CHBUF_INFO_T *info);
int TE_IPC_CloseARIB2Channel(u8 ch);
int TE_IPC_RequestARIB2Filter(u8 ch, u8 type, u8 idx, void *payload);
int TE_IPC_CancelARIB2Filter(u8 ch, u8 type, u8 idx);
int TE_IPC_SetARIB2FilterRptr(u8 idx, u8 type, u32 rptr);
int TE_IPC_GetARIB2ChannelStatus(u8 ch, IPC_ARIB2_CH_STATUS_T *status);
int TE_IPC_GetARIB2FilterStatus(u8 idx, u8 type, void *status);

int TE_IPC_SetEngineType(IPC_STATUS_ENGINE_TYPE_T type);
int te_ipc_enable_atsc3_filter(void);
/*------------------------------------------------------------------------------
 *   Removed
 *----------------------------------------------------------------------------*/
int TE_IPC_StartDownload(u8 ch, u32 buf_start, u32 buf_end, u32 unit_size);
int TE_IPC_StopDownload(u8 ch);
int TE_IPC_RegisterDownloadCallback(u8 ch, ipc_msg_callback_t callback,
				    void *arg);
int TE_IPC_GetDownloadWptr(u8 ch, u32 *ptr);

#endif				/* _LG1K_TE_IPC_H_ */
