/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2018 by LG Electronics Inc.
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
 *  descrambler register access API
 *
 *  @author	Yeonju Lee (yeonju.lee@lge.com)
 *  @version	1.0
 *  @date		2018-08-23
 *  @note		Additional information.
 */

#include "te_impl.h"
#include "te_reg_ctrl.h"

#define INV_TYPE	0xFFFFFFFF

#define CHECK_IDX(idx)	\
  CHECK_PARAM(idx >= num_dsc, "invalid idx(%d)\n", idx)

#define TRACE_ENTER(fmt,args...)					\
do { 									\
	if (unlikely(g_te_reg_log_mask & REG_LOG_DSC_MASK)) {		\
		log_noti("@DSC_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

#define TRACE_EXIT(fmt,args...)						\
do { 									\
	if (unlikely(g_te_reg_log_mask & REG_LOG_DSC_MASK)) {		\
		log_noti("~DSC_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

#define TRACE_VERBOSE_ENTER(fmt,args...)				\
do { 									\
	if (unlikely((g_te_reg_log_mask & REG_LOG_DSC_MASK) &&		\
		     (g_te_reg_log_mask & REG_LOG_VERBOSE_MASK))) {	\
		log_noti("@DSC_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

#define TRACE_VERBOSE_EXIT(fmt,args...)					\
do { 									\
	if (unlikely((g_te_reg_log_mask & REG_LOG_DSC_MASK) &&		\
		     (g_te_reg_log_mask & REG_LOG_VERBOSE_MASK))) {	\
		log_noti("~DSC_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)


static u8 num_dsc;

int te_reg_dsc_init(void)
{
	struct te_config *cfg = te_get_config();

	num_dsc = cfg->num_dsc;

	return 0;
}

int te_reg_dsc_reset(u8 idx)
{
	u32 v;

	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d", idx);

	DSC_RdFL(idx, dma_start);
	DSC_Rd01(idx, dma_start, busy, v);
	if (v) {
		log_warning("dsc(%d) busy\n", idx);
	}

	DSC_Wr(idx, sw_reset, 1);
	DSC_WrFL(idx, sw_reset);

	return 0;
}

int te_reg_dsc_set_endian(u8 idx, bool big_endian)
{
	CHECK_IDX(idx);

	DSC_Wr(idx, endian, big_endian ? 1 : 0);
	DSC_WrFL(idx, endian);

	return 0;
}

static const struct te_type_conv crypto_type_list[] = {
	{DSC_CRYPTO_TYPE_BYPASS, 0},
	{DSC_CRYPTO_TYPE_DES, 1},
	{DSC_CRYPTO_TYPE_TDES, 2},
	{DSC_CRYPTO_TYPE_AES, 3},
	{DSC_CRYPTO_TYPE_DVBCSA, 4},
	{DSC_CRYPTO_TYPE_MULTI2, 5},
};

static const struct te_type_conv blk_mode_list[] = {
	{DSC_BLK_MODE_ECB, 0},
	{DSC_BLK_MODE_CBC, 1},
	{DSC_BLK_MODE_CTR, 2},
	{DSC_BLK_MODE_OMAC1, 3},
};

static const struct te_type_conv res_mode_list[] = {
	{DSC_RES_MODE_CLEAR, 0},
	{DSC_RES_MODE_CTS, 1},
	{DSC_RES_MODE_OFB, 2},
	{DSC_RES_MODE_SCTE, 3},
};

int te_reg_dsc_set_config(u8 idx, struct te_reg_dsc_config *cfg)
{
	u32 type, blk_mode, res_mode, scramble;

	CHECK_IDX(idx);

	type = convert_to_type1(crypto_type_list, cfg->type, INV_TYPE);
	if (type == INV_TYPE) {
		log_error("invalid crypto type(%d)\n", cfg->type);
		return -EINVAL;
	}

	blk_mode = convert_to_type1(blk_mode_list, cfg->blk_mode, INV_TYPE);
	if (blk_mode == INV_TYPE) {
		log_error("invalid blk_mode(%d)\n", cfg->blk_mode);
		return -EINVAL;
	}

	res_mode = convert_to_type1(res_mode_list, cfg->res_mode, INV_TYPE);
	if (res_mode == INV_TYPE) {
		log_error("invalid res_mode(%d)\n", cfg->res_mode);
		return -EINVAL;
	}

	if (cfg->key_size != 8 && cfg->key_size != 16 &&
	    cfg->key_size != 24 && cfg->key_size != 32) {
		log_error("invalid key_size(%d)\n", cfg->key_size);
		return -EINVAL;
	}

	scramble = cfg->scramble ? 1 : 0;

	TRACE_ENTER("idx=%d,scramble:%d,type=%d,blk=%d,res=%d,size=%d",
		    idx, cfg->scramble, cfg->type, cfg->blk_mode,
		    cfg->res_mode, cfg->key_size);

	DSC_Wr01(idx, crypto_ctrl, scramble, scramble);
	DSC_Wr01(idx, crypto_ctrl, crypto_type, type);
	DSC_Wr01(idx, crypto_ctrl, blk_mode, blk_mode);
	DSC_Wr01(idx, crypto_ctrl, res_mode, res_mode);
	DSC_Wr01(idx, crypto_ctrl, key_size, cfg->key_size);
	DSC_WrFL(idx, crypto_ctrl);

	return 0;
}

static int set_even_key(u8 idx, const u8 *key, u8 size)
{
	int i;

	if (size > 32 || size % 4 != 0) {
		log_error("invalid key size(%d)\n", size);
		return -EINVAL;
	}

	for (i = 0; i < size / 4; i++, key += 4) {
		DSC_REG_WRITE32(idx, even_key[i], TE_GET32(key));
	}

	return 0;
}

static int set_odd_key(u8 idx, const u8 *key, u8 size)
{
	int i;

	if (size > 32 || size % 4 != 0) {
		log_error("invalid key size(%d)\n", size);
		return -EINVAL;
	}

	for (i = 0; i < size / 4; i++, key += 4) {
		DSC_REG_WRITE32(idx, odd_key[i], TE_GET32(key));
	}

	return 0;
}

static int set_even_iv(u8 idx, const u8 *key, u8 size)
{
	int i;

	if (size > 16 || size % 4 != 0) {
		log_error("invalid key size(%d)\n", size);
		return -EINVAL;
	}

	for (i = 0; i < size / 4; i++, key += 4) {
		DSC_REG_WRITE32(idx, even_iv[i], TE_GET32(key));
	}

	return 0;
}

static int set_odd_iv(u8 idx, const u8 *key, u8 size)
{
	int i;

	if (size > 16 || size % 4 != 0) {
		log_error("invalid key size(%d)\n", size);
		return -EINVAL;
	}

	for (i = 0; i < size / 4; i++, key += 4) {
		DSC_REG_WRITE32(idx, odd_iv[i], TE_GET32(key));
	}

	return 0;
}

static int set_multi2_iv(u8 idx, const u8 *key, u8 size)
{
	int i;

	if (size != 8) {
		log_error("invalid key size(%d)\n", size);
		return -EINVAL;
	}

	for (i = 0; i < size / 4; i++, key += 4) {
		DSC_REG_WRITE32(idx, even_iv[2 + i], TE_GET32(key));
		DSC_REG_WRITE32(idx, odd_iv[2 + i], TE_GET32(key));
	}

	return 0;
}

static int set_multi2_skey(u8 idx, const u8 *key, u8 size)
{
	int i;

	if (size != 32) {
		log_error("invalid key size(%d)\n", size);
		return -EINVAL;
	}

	for (i = 0; i < size / 4; i++, key += 4) {
		DSC_REG_WRITE32(idx, even_key[i], TE_GET32(key));

		/* After s/w reset, descrambler uses even key register value
		 * for first packet and odd key register value for last packets
		 */
		//DSC_REG_WRITE32(idx, odd_key[i], TE_GET32(key));
	}

	return 0;
}

static int set_multi2_even_key(u8 idx, const u8 *key, u8 size)
{
	int i;

	if (size != 8) {
		log_error("invalid key size(%d)\n", size);
		return -EINVAL;
	}

	for (i = 0; i < size / 4; i++, key += 4) {
		DSC_REG_WRITE32(idx, even_key[8 + i], TE_GET32(key));
	}

	return 0;
}

static int set_multi2_odd_key(u8 idx, const u8 *key, u8 size)
{
	int i;

	if (size != 8) {
		log_error("invalid key size(%d)\n", size);
		return -EINVAL;
	}

	for (i = 0; i < size / 4; i++, key += 4) {
		DSC_REG_WRITE32(idx, even_key[8 + i], TE_GET32(key));

		/* After s/w reset, descrambler uses even key register value
		 * for first packet and odd key register value for last packets.
		 */
		//DSC_REG_WRITE32(idx, odd_key[8 + i], TE_GET32(key));
	}

	return 0;
}

int te_reg_dsc_set_odd_mode(u8 idx, bool odd)
{
	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d,odd=%d", idx, odd);

	DSC_RdFL(idx, dma_start);
	DSC_Wr01(idx, dma_start, ts_odd_mode, odd ? 1 : 0);
	DSC_WrFL(idx, dma_start);

	return 0;
}

int te_reg_dsc_set_iv_key(u8 idx, enum te_reg_dsc_iv_key type,
			  const u8 *val, u8 size)
{
	int ret;

	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d,type:%d,size=%d", idx, type, size);

	switch (type) {
	case DSC_KEY:
	case DSC_EVEN_KEY:
		ret = set_even_key(idx, val, size);
		break;
	case DSC_ODD_KEY:
		ret = set_odd_key(idx, val, size);
		break;
	case DSC_IV:
	case DSC_EVEN_IV:
		ret = set_even_iv(idx, val, size);
		break;
	case DSC_ODD_IV:
		ret = set_odd_iv(idx, val, size);
		break;
	default:
		log_error("invalid type(%d)\n", type);
		ret = -EINVAL;
		break;
	}

	return ret;
}

int te_reg_dsc_set_multi2(u8 idx, enum te_reg_dsc_iv_key type,
			  const u8 *val, u8 size)
{
	int ret;

	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d,type:%d,size=%d", idx, type, size);

	switch (type) {
	case DSC_MULTI2_SKEY:
		ret = set_multi2_skey(idx, val, size);
		break;
	case DSC_MULTI2_IV:
		ret = set_multi2_iv(idx, val, size);
		break;
	case DSC_EVEN_KEY:
		ret = set_multi2_even_key(idx, val, size);
		break;
	case DSC_ODD_KEY:
		ret = set_multi2_odd_key(idx, val, size);
		break;
	default:
		log_error("invalid type(%d)\n", type);
		ret = -EINVAL;
		break;
	}

	return ret;
}

int te_reg_dsc_start(u8 idx, enum te_reg_dsc_format fmt, u32 src, u32 dst,
		     u32 size)
{
	int align_size;
	u32 fmt_val;
	u32 v, skip_len, load_len;

	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d,fmt=%d,size=%u", idx, fmt, size);

	switch (fmt) {
	case DSC_FORMAT_TS:
		align_size = 188;
		skip_len = 4;
		load_len = 184;
		fmt_val = 1;
		break;
	case DSC_FORMAT_TIMESTAMP_TS:
		align_size = 192;
		skip_len = 8;
		load_len = 184;
		fmt_val = 2;
		break;
	case DSC_FORMAT_DATA:
	default:
		align_size = 4;
		skip_len = 0;
		load_len = size;
		fmt_val = 0;
		break;
	}

	if (size % align_size) {
		log_error("not aligned to %dbytes\n", align_size);
		return -EINVAL;
	}

	DSC_RdFL(idx, dma_start);
	DSC_Rd01(idx, dma_start, busy, v);
	if (v) {
		log_error("dsc(%d) busy\n", idx);
		return -EBUSY;
	}
	DSC_Wr01(idx, dma_start, ts_format, fmt_val);
	DSC_WrFL(idx, dma_start);

	DSC_REG_WRITE32(idx, proc_skip_len, skip_len);
	DSC_REG_WRITE32(idx, proc_load_len, load_len);

	DSC_REG_WRITE32(idx, dma_src_addr, src);
	DSC_REG_WRITE32(idx, dma_src_len, size);
	DSC_REG_WRITE32(idx, dma_dst_addr, dst);
	DSC_REG_WRITE32(idx, dma_dst_len, size);

	DSC_Wr01(idx, dma_start, start, 1);
	DSC_WrFL(idx, dma_start);

	return 0;
}

int te_reg_dsc_get_status(u8 idx, struct te_reg_dsc_status *s)
{
	u32 v;

	CHECK_IDX(idx);

	DSC_RdFL(idx, dma_start);
	DSC_Rd01(idx, dma_start, busy, v);
	s->busy = v ? true : false;

	// TODO: add others...

	return 0;
}

static u32 get_intr_reg_bits(u32 val)
{
	u32 bits;

	bits = 0;
	if (val & DSC_INTR_DMA_DONE)
		bits |= (0x1 << 0);

	return bits;
}

static u32 get_intr_value(u32 bits)
{
	u32 val;

	val = 0;
	if (bits & (0x1 << 0))
		val |= DSC_INTR_DMA_DONE;

	return val;
}

int te_reg_dsc_set_intr_enable(u8 idx, u32 val, bool en)
{
	u32 v;
	u32 bits;

	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d,val=0x%x,en=%d", idx, val, en);

	bits = get_intr_reg_bits(val);

	DSC_RdFL(idx, addr_cpu_intr_en);
	DSC_Rd(idx, addr_cpu_intr_en, v);
	if (en)
		v |= bits;
	else
		v &= ~bits;
	DSC_Wr(idx, addr_cpu_intr_en, v);
	DSC_WrFL(idx, addr_cpu_intr_en);

	return 0;
}

int te_reg_dsc_get_intr_status(u8 idx, u32 *val)
{
	u32 bits;

	CHECK_IDX(idx);

	DSC_RdFL(idx, addr_cpu_intr_stat);
	DSC_Rd(idx, addr_cpu_intr_stat, bits);

	*val = get_intr_value(bits);

	TRACE_VERBOSE_EXIT("idx=%d,*val=0x%x", idx, *val);

	return 0;
}

int te_reg_dsc_clear_intr(u8 idx, u32 val)
{
	u32 bits;

	CHECK_IDX(idx);

	TRACE_VERBOSE_ENTER("idx=%d,val=0x%x", idx, val);

	bits = get_intr_reg_bits(val);

	DSC_Wr(idx, addr_cpu_intr_clr, bits);
	DSC_WrFL(idx, addr_cpu_intr_clr);

	return 0;
}
