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
 *  @author	Kyungseok Hyun ( ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2015-02-09
 *  @note		Additional information.
 */

#include "te_impl.h"
#include "te_reg_ctrl.h"

#define CHECK_CHANNEL(ch)	\
  CHECK_PARAM((ch) >= ciplus_reg_cfg->num_channel, "invalid channel(%d)\n", ch)

#define CHECK_IDX(i)				\
  CHECK_PARAM((i) >= ciplus_reg_cfg->num_idx, "invalid idx(%d)\n", i)

#define TRACE_ENTER(fmt,args...)					\
do { 									\
	if (unlikely(g_te_reg_log_mask & REG_LOG_CIPLUS_MASK)) {	\
		log_noti("@CIPLUS_REG : %s(" fmt ")", __func__, ##args);\
	}								\
} while(0)

#define TRACE_EXIT(fmt,args...)						\
do { 									\
	if (unlikely(g_te_reg_log_mask & REG_LOG_CIPLUS_MASK)) {	\
		log_noti("~CIPLUS_REG : %s(" fmt ")", __func__, ##args);\
	}								\
} while(0)

#define TRACE_VERBOSE_ENTER(fmt,args...)				\
do { 									\
	if (unlikely((g_te_reg_log_mask & REG_LOG_CIPLUS_MASK) &&	\
		     (g_te_reg_log_mask & REG_LOG_VERBOSE_MASK))) {	\
		log_noti("@CIPLUS_REG : %s(" fmt ")", __func__, ##args);\
	}								\
} while(0)

#define TRACE_VERBOSE_EXIT(fmt,args...)					\
do { 									\
	if (unlikely((g_te_reg_log_mask & REG_LOG_CIPLUS_MASK) &&	\
		     (g_te_reg_log_mask & REG_LOG_VERBOSE_MASK))) {	\
		log_noti("~CIPLUS_REG : %s(" fmt ")", __func__, ##args);\
	}								\
} while(0)

typedef struct {
	u8 version;
	u8 num_channel;
	u8 num_idx;

} CIPLUS_REG_CFG_T;

/* M16+ ~ */
static const CIPLUS_REG_CFG_T ciplus_cfg_normal = {
	.version = 0,
	.num_channel = 3,
	.num_idx = 3,
};

static const CIPLUS_REG_CFG_T *ciplus_reg_cfg;

static DEFINE_SPINLOCK(ciplus_reg_lock);

int TE_REG_CIPLUS_Init(void)
{
	ciplus_reg_cfg = &ciplus_cfg_normal;

	return 0;
}

int TE_REG_SetCiplusDemuxDestination(u8 idx, enum te_reg_cip_dmx_dest dest)
{
	unsigned long flag;
	u32 v;

	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d,dest=%d", idx, dest);

	switch (dest) {
	case CIP_DEMUX_DEST_DISABLE:
		v = 0;
		break;
	case CIP_DEMUX_DEST_HW:
		v = 1;
		break;
	case CIP_DEMUX_DEST_MCU:
		v = 2;
		break;
	case CIP_DEMUX_DEST_BOTH:
		v = 3;
		break;
	default:
		log_error("invalid dest(%d)\n", dest);
		return -EINVAL;
	}

	spin_lock_irqsave(&ciplus_reg_lock, flag);

	CIPLUS_RdFL(ciplus_demux_conf[idx]);
	CIPLUS_Wr01(ciplus_demux_conf[idx], demux_dest, v);
	CIPLUS_WrFL(ciplus_demux_conf[idx]);

	spin_unlock_irqrestore(&ciplus_reg_lock, flag);

	return 0;
}

int TE_REG_GetCiplusDemuxDestination(u8 idx, enum te_reg_cip_dmx_dest *dest)
{
	unsigned long flag;
	u32 v;

	CHECK_IDX(idx);

	spin_lock_irqsave(&ciplus_reg_lock, flag);

	CIPLUS_RdFL(ciplus_demux_conf[idx]);
	CIPLUS_Rd01(ciplus_demux_conf[idx], demux_dest, v);

	spin_unlock_irqrestore(&ciplus_reg_lock, flag);

	switch (v) {
	case 1:
		*dest = CIP_DEMUX_DEST_HW;
		break;
	case 2:
		*dest = CIP_DEMUX_DEST_MCU;
		break;
	case 3:
		*dest = CIP_DEMUX_DEST_BOTH;
		break;
	case 0:
	default:
		*dest = CIP_DEMUX_DEST_DISABLE;
		break;
	}

	TRACE_EXIT("idx=%d,*dest=%d", idx, *dest);

	return 0;
}

int TE_REG_SetCiplusDemuxSyncbyte(u8 idx, u8 syncbyte)
{
	unsigned long flag;

	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d,syncbyte=0x%02x", idx, syncbyte);

	spin_lock_irqsave(&ciplus_reg_lock, flag);

	CIPLUS_RdFL(ciplus_demux_conf[idx]);
	CIPLUS_Wr01(ciplus_demux_conf[idx], demux_syncbyte, syncbyte);
	CIPLUS_WrFL(ciplus_demux_conf[idx]);

	spin_unlock_irqrestore(&ciplus_reg_lock, flag);

	return 0;
}

int TE_REG_GetCiplusDemuxSyncbyte(u8 idx, u8 *syncbyte)
{
	unsigned long flag;

	CHECK_IDX(idx);

	spin_lock_irqsave(&ciplus_reg_lock, flag);

	CIPLUS_RdFL(ciplus_demux_conf[idx]);
	CIPLUS_Rd01(ciplus_demux_conf[idx], demux_syncbyte, *syncbyte);

	spin_unlock_irqrestore(&ciplus_reg_lock, flag);

	TRACE_EXIT("idx=%d,*syncbyte=0x%02x", idx, *syncbyte);

	return 0;
}

//FIXME: only ch0 has reset
/* ciplus_demux_conf[0] can reset other ciplus_demux_conf simultaneously
 * Only called when booted */
int TE_REG_ResetCiplusDemux(u8 ch)
{
	unsigned long flag;

	CHECK_IDX(ch);

	TRACE_ENTER("Reset ch=%d", ch);

	spin_lock_irqsave(&ciplus_reg_lock, flag);

	CIPLUS_RdFL(ciplus_demux_conf[ch]);
	CIPLUS_Wr01(ciplus_demux_conf[ch], demux_swreset, 0x1);
	CIPLUS_WrFL(ciplus_demux_conf[ch]);

	spin_unlock_irqrestore(&ciplus_reg_lock, flag);

	return 0;
}

/* Set Ciplus Endian Type (0: normal, 1:byte swap, 2:word swap)
 * Set same value on endian_read and write ( modify it if needed)
 */
int TE_REG_SetCiplusEndian(enum te_reg_cip_endian type)
{
	unsigned long flag;
	u32 v;

	CHECK_PARAM(type >= CIP_ENDIAN_MAX, "invalid type(%d)\n", type);

	TRACE_ENTER("type=%d", type);

	switch (type) {
	case CIP_ENDIAN_BYTESWAP:
		v = 1;
		break;
	case CIP_ENDIAN_WORDSWAP:
		v = 2;
		break;
	case CIP_ENDIAN_NORMAL:
	default:
		v = 0;
		break;
	}

	spin_lock_irqsave(&ciplus_reg_lock, flag);

	CIPLUS_RdFL(ciplus_axi_conf);
	CIPLUS_Wr01(ciplus_axi_conf, endian_read, v);
	CIPLUS_Wr01(ciplus_axi_conf, endian_write, v);
	CIPLUS_WrFL(ciplus_axi_conf);

	spin_unlock_irqrestore(&ciplus_reg_lock, flag);

	return 0;
}

int TE_REG_ResetCiplusInbuf(u8 ch)
{
	unsigned long flag;

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d", ch);

	spin_lock_irqsave(&ciplus_reg_lock, flag);

	CIPLUS_RdFL(ciplus_buf_conf[ch]);
	CIPLUS_Wr01(ciplus_buf_conf[ch], swreset, 0x1);
	CIPLUS_WrFL(ciplus_buf_conf[ch]);

	spin_unlock_irqrestore(&ciplus_reg_lock, flag);

	return 0;
}

int TE_REG_SetCiplusInbufSource(u8 ch, enum te_reg_cip_src src)
{
	unsigned long flag;
	u32 v;

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d src=%d", ch, src);

	switch (src) {
	case CIP_SRC_DEMOD:
		v = 0;
		break;
	case CIP_SRC_MCU:
		v = 1;
		break;
	default:
		log_error("invalid src(%d)\n", src);
		return -EINVAL;
	}

	spin_lock_irqsave(&ciplus_reg_lock, flag);

	CIPLUS_RdFL(ciplus_buf_conf[ch]);
	CIPLUS_Wr01(ciplus_buf_conf[ch], src_sel, v);
	CIPLUS_WrFL(ciplus_buf_conf[ch]);

	spin_unlock_irqrestore(&ciplus_reg_lock, flag);

	return 0;
}

int TE_REG_SetCiplusInbufDestination(u8 ch, enum te_reg_cip_dest dest)
{
	unsigned long flag;
	u32 v;

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d dest=%d", ch, dest);

	switch (dest) {
	case CIP_INPUT_DEST_HW:
		v = 0;
		break;
	case CIP_INPUT_DEST_MCU:
		v = 1;
		break;
	default:
		log_error("invalid dest(%d)\n", dest);
		return -EINVAL;
	}

	spin_lock_irqsave(&ciplus_reg_lock, flag);

	CIPLUS_RdFL(ciplus_buf_conf[ch]);
	CIPLUS_Wr01(ciplus_buf_conf[ch], dest_sel, v);
	CIPLUS_WrFL(ciplus_buf_conf[ch]);

	spin_unlock_irqrestore(&ciplus_reg_lock, flag);

	return 0;
}

int TE_REG_SetCiplusInbufFullLevel(u8 ch, u8 full_level)
{
	unsigned long flag;

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d flevel=%d", ch, full_level);

	spin_lock_irqsave(&ciplus_reg_lock, flag);

	CIPLUS_RdFL(ciplus_buf_conf[ch]);
	CIPLUS_Wr01(ciplus_buf_conf[ch], flevel, full_level);
	CIPLUS_WrFL(ciplus_buf_conf[ch]);

	spin_unlock_irqrestore(&ciplus_reg_lock, flag);

	return 0;
}

int TE_REG_SetCiplusInbufWidx(u8 ch, u8 wdx)
{
	unsigned long flag;

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d widx=%d", ch, wdx);

	spin_lock_irqsave(&ciplus_reg_lock, flag);

	CIPLUS_RdFL(ciplus_buf_conf[ch]);
	CIPLUS_Wr01(ciplus_buf_conf[ch], widx, wdx);
	CIPLUS_WrFL(ciplus_buf_conf[ch]);

	spin_unlock_irqrestore(&ciplus_reg_lock, flag);

	return 0;
}

int TE_REG_ResetCiplusOutbuf(void)
{
	unsigned long flag;

	TRACE_ENTER("reset = 1");

	spin_lock_irqsave(&ciplus_reg_lock, flag);

	CIPLUS_RdFL(ciplus_outbuf_conf);
	CIPLUS_Wr01(ciplus_outbuf_conf, swreset, 0x1);
	CIPLUS_WrFL(ciplus_outbuf_conf);

	spin_unlock_irqrestore(&ciplus_reg_lock, flag);

	return 0;
}

int TE_REG_SetCiplusOutbufSource(enum te_reg_cip_src src)
{
	unsigned long flag;
	u32 v;

	TRACE_ENTER("src=%d", src);

	switch (src) {
	case CIP_SRC_DEMOD:
		v = 0;
		break;
	case CIP_SRC_MCU:
		v = 1;
		break;
	default:
		log_error("invalid src(%d)\n", src);
		return -EINVAL;
	}

	spin_lock_irqsave(&ciplus_reg_lock, flag);

	CIPLUS_RdFL(ciplus_outbuf_conf);
	CIPLUS_Wr01(ciplus_outbuf_conf, src_sel, v);
	CIPLUS_WrFL(ciplus_outbuf_conf);

	spin_unlock_irqrestore(&ciplus_reg_lock, flag);

	return 0;
}

int TE_REG_SetCiplusOutbufDestination(enum te_reg_cip_dest dest)
{
	unsigned long flag;
	u32 v;

	TRACE_ENTER("dest=%d", dest);

	switch (dest) {
	case CIP_INPUT_DEST_HW:
		v = 0;
		break;
	case CIP_INPUT_DEST_MCU:
		v = 1;
		break;
	default:
		log_error("invalid dest(%d)\n", dest);
		return -EINVAL;
	}

	spin_lock_irqsave(&ciplus_reg_lock, flag);

	CIPLUS_RdFL(ciplus_outbuf_conf);
	CIPLUS_Wr01(ciplus_outbuf_conf, dest_sel, v);
	CIPLUS_WrFL(ciplus_outbuf_conf);

	spin_unlock_irqrestore(&ciplus_reg_lock, flag);

	return 0;
}

int TE_REG_SetCiplusOutbufFullLevel(u8 full_level)
{
	unsigned long flag;

	TRACE_ENTER("flevel=%d", full_level);

	spin_lock_irqsave(&ciplus_reg_lock, flag);

	CIPLUS_RdFL(ciplus_outbuf_conf);
	CIPLUS_Wr01(ciplus_outbuf_conf, flevel, full_level);
	CIPLUS_WrFL(ciplus_outbuf_conf);

	spin_unlock_irqrestore(&ciplus_reg_lock, flag);

	return 0;
}

int TE_REG_ResetCiplusInput(u8 ch)
{
	unsigned long flag;

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d", ch);

	spin_lock_irqsave(&ciplus_reg_lock, flag);

	CIPLUS_RdFL(ciplus_pidf_conf[ch]);
	CIPLUS_Wr01(ciplus_pidf_conf[ch], swreset, 0x1);
	CIPLUS_WrFL(ciplus_pidf_conf[ch]);

	spin_unlock_irqrestore(&ciplus_reg_lock, flag);

	return 0;
}

int TE_REG_SetCiplusInputBypass(u8 ch, bool bypass_en)
{
	unsigned long flag;

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d bypass_en=%d", ch, bypass_en);

	spin_lock_irqsave(&ciplus_reg_lock, flag);

	CIPLUS_RdFL(ciplus_pidf_conf[ch]);
	CIPLUS_Wr01(ciplus_pidf_conf[ch], bypass_en, bypass_en ? 1 : 0);
	CIPLUS_WrFL(ciplus_pidf_conf[ch]);

	spin_unlock_irqrestore(&ciplus_reg_lock, flag);

	return 0;
}

int TE_REG_SetCiplusInputTeiDrop(u8 ch, bool en)
{
	unsigned long flag;

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d tei_en=%d", ch, en);

	spin_lock_irqsave(&ciplus_reg_lock, flag);

	CIPLUS_RdFL(ciplus_pidf_conf[ch]);
	CIPLUS_Wr01(ciplus_pidf_conf[ch], tei_en, en ? 1 : 0);
	CIPLUS_WrFL(ciplus_pidf_conf[ch]);

	spin_unlock_irqrestore(&ciplus_reg_lock, flag);

	return 0;
}

int TE_REG_SetCiplusInputSyncbyte(u8 ch, bool en, u8 syncbyte)
{
	unsigned long flag;

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d syncbyte=0x%02x(en:%d)", ch, syncbyte, en);

	spin_lock_irqsave(&ciplus_reg_lock, flag);

	CIPLUS_RdFL(ciplus_pidf_conf[ch]);
	CIPLUS_Wr01(ciplus_pidf_conf[ch], sync_en, en ? 1 : 0);
	CIPLUS_Wr01(ciplus_pidf_conf[ch], syncbyte_r, syncbyte);
	CIPLUS_WrFL(ciplus_pidf_conf[ch]);

	spin_unlock_irqrestore(&ciplus_reg_lock, flag);

	return 0;
}

int TE_REG_SetCiplusQueueEnable(u8 ch, bool en)
{
	unsigned long flag;
	u32 v;

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d queue_en=%d", ch, en);

	v = en ? 1 : 0;

	spin_lock_irqsave(&ciplus_reg_lock, flag);

	CIPLUS_RdFL(ciplus_queue_conf);

	switch (ch) {
	case 0:
		CIPLUS_Wr01(ciplus_queue_conf, chan0_req_en, v);
		break;

	case 1:
		CIPLUS_Wr01(ciplus_queue_conf, chan1_req_en, v);
		break;

	case 2:
		CIPLUS_Wr01(ciplus_queue_conf, chan2_req_en, v);
		break;

	default:
		break;
	}

	CIPLUS_WrFL(ciplus_queue_conf);

	spin_unlock_irqrestore(&ciplus_reg_lock, flag);

	return 0;
}

int TE_REG_SetCiplusPIDF(u8 ch, u8 idx, u16 pid, bool en)
{
	unsigned long flag;

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d idx=%d pid=0x%x(en:%d) ", ch, idx, pid, en);

	spin_lock_irqsave(&ciplus_reg_lock, flag);

	CIPLUS_RdFL(ciplus_pidf[ch][idx]);
	CIPLUS_Wr01(ciplus_pidf[ch][idx], pidf_val, en ? 1 : 0);
	CIPLUS_Wr01(ciplus_pidf[ch][idx], ref_pid, pid);
	CIPLUS_WrFL(ciplus_pidf[ch][idx]);

	spin_unlock_irqrestore(&ciplus_reg_lock, flag);

	return 0;

}

int TE_REG_GetCiplusTPOBitrate(u16 *bitrate)
{
	unsigned long flag;

	spin_lock_irqsave(&ciplus_reg_lock, flag);

	CIPLUS_RdFL(ciplus_tpo_bitrate);
	CIPLUS_Rd01(ciplus_tpo_bitrate, bitrate, *bitrate);

	spin_unlock_irqrestore(&ciplus_reg_lock, flag);

	TRACE_EXIT("*bitrate=0x%08x", *bitrate);

	return 0;
}

int TE_REG_GetCiplusTPOPacketCnt(u32 *pkt_cnt)
{
	unsigned long flag;

	spin_lock_irqsave(&ciplus_reg_lock, flag);

	CIPLUS_RdFL(ciplus_tpo_packet_cnt);
	CIPLUS_Rd01(ciplus_tpo_packet_cnt, tpo_packet_cnt, *pkt_cnt);

	spin_unlock_irqrestore(&ciplus_reg_lock, flag);

	TRACE_EXIT("*count=%d", *pkt_cnt);

	return 0;
}
