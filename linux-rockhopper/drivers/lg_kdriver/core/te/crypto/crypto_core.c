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
 *  TE(Transport Engine) Driver
 *
 *  @author	Kyungseok Hyun (ks.hyun@lge.com)
 *  @version	1.0
 *  @date	2018-07-09
 *  @note	Additional information.
 */

#include <linux/atomic.h>
#include <lg1k/te/dump.h>

#include "crypto_impl.h"

//NOTE: Currently not used since O24
int te_crypto_async_encrypt(struct te_crypto_ctx *ctx,
			    struct te_crypto_data *data, enum te_crypto_tsc tsc,
			    te_crypto_callback_t callback);
int te_crypto_async_decrypt(struct te_crypto_ctx *ctx,
			    struct te_crypto_data *data,
			    te_crypto_callback_t callback);


#define INV_TYPE 0xFFFFFFFF

#if !CONFIG_LX_BOARD_FPGA
#define DEFAULT_CTX_TIMEOUT 1000 /* in ms */
#define DEFAULT_DEV_TIMEOUT 200 /* in ms, depend on h/w buffer size */
#else //FPGA
#define DEFAULT_CTX_TIMEOUT 0 /* in ms */
#define DEFAULT_DEV_TIMEOUT 0 /* in ms, depend on h/w buffer size */
#endif

#define DMA_DONE_MAX_WAIT_TIME 500
#define HW_BUF_SIZE SZ_1M


#define inode_to_device(inode) \
	container_of(inode->i_cdev, struct te_crypto_device, cdev)

#define inode_to_channel(inode) \
({ \
	struct te_crypto_device *__dev = inode_to_device(inode); \
	unsigned __n = iminor(inode); \
	(__n < __dev->num_channel) ? &__dev->channels[__n] : NULL; \
})

#define channel_to_device(channel) \
	container_of(channel, struct te_crypto_device, channels[channel->num])

#define crypto_wait_event(wq, cond, timeout)                                   \
	({                                                                     \
		int __r;                                                       \
		if (timeout == 0) {                                            \
			__r = wait_event_interruptible(wq, cond);              \
		} else {                                                       \
			unsigned long __x = msecs_to_jiffies(timeout);         \
			__r = wait_event_interruptible_timeout(wq, cond, __x); \
			if (__r == 0)                                          \
				__r = -ETIME;                                  \
			else if (__r > 0)                                      \
				__r = 0;                                       \
		}                                                              \
		__r;                                                           \
	})


static const struct te_val_str mode_str[] = {
	{ TE_CRYPTO_DECRYPTION, "DEC" },
	{ TE_CRYPTO_ENCRYPTION, "ENC" },
};

enum te_crypto_mode te_str_to_crypto_mode(const char *str)
{
	return find_match_value(mode_str, str, TE_CRYPTO_DECRYPTION);
}

const char *te_crypto_mode_to_str(enum te_crypto_mode mode)
{
	return find_match_string(mode_str, mode, "Invalid");
}

static const struct te_val_str format_str[] = {
	{ TE_CRYPTO_FMT_DATA, "DATA" },
	{ TE_CRYPTO_FMT_TS_188, "TS_188" },
	{ TE_CRYPTO_FMT_TS_192, "TS_192" },
};

enum te_crypto_fmt te_str_to_crypto_format(const char *str)
{
	return find_match_value(format_str, str, TE_CRYPTO_FMT_TS_192);
}

const char *te_crypto_format_to_str(enum te_crypto_fmt fmt)
{
	return find_match_string(format_str, fmt, "Invalid");
}

static const struct te_val_str type_str[] = {
	{ TE_CRYPTO_BYPASS, "BYPASS" }, { TE_CRYPTO_AES, "AES" },
	{ TE_CRYPTO_DES, "DES" },       { TE_CRYPTO_TDES, "TDES" },
	{ TE_CRYPTO_MULTI2, "MULTI2" },
};

enum te_crypto_type te_str_to_crypto_type(const char *str)
{
	return find_match_value(type_str, str, TE_CRYPTO_BYPASS);
}

const char *te_crypto_type_to_str(enum te_crypto_type type)
{
	return find_match_string(type_str, type, "Invalid");
}

static const struct te_val_str blk_str[] = {
	{ TE_CRYPTO_BLK_ECB, "ECB" },
	{ TE_CRYPTO_BLK_CBC, "CBC" },
	{ TE_CRYPTO_BLK_CTR, "CTR" },
};

enum te_crypto_blk te_str_to_crypto_blk(const char *str)
{
	return find_match_value(blk_str, str, TE_CRYPTO_BLK_ECB);
}

const char *te_crypto_blk_to_str(enum te_crypto_blk blk)
{
	return find_match_string(blk_str, blk, "Invalid");
}

static const struct te_val_str res_str[] = {
	{ TE_CRYPTO_RES_CLEAR, "CLEAR" },
	{ TE_CRYPTO_RES_CTS, "CTS" },
	{ TE_CRYPTO_RES_OFB, "OFB" },
	{ TE_CRYPTO_RES_SCTE, "SCTE" },
};

enum te_crypto_res te_str_to_crypto_res(const char *str)
{
	return find_match_value(res_str, str, TE_CRYPTO_RES_CLEAR);
};

const char *te_crypto_res_to_str(enum te_crypto_res res)
{
	return find_match_string(res_str, res, "Invalid");
}

static int irq_handler(u32 status1, void *dev_id)
{
	u32 status2;
	struct te_crypto_channel *channel = dev_id;

	te_reg_dsc_get_intr_status(channel->dsc_idx, &status2);
	te_reg_dsc_clear_intr(channel->dsc_idx, status2); // clear 2nd level interrupt

	if (status2 & DSC_INTR_DMA_DONE) {
		channel->done = true;
#ifdef USE_CRYPTO_ASYNC_REQUEST
		queue_work(system_highpri_wq, &channel->done_work);
#else
		wake_up_interruptible(&channel->wq);
#endif
	}

	return 0;
}

static void init_hw(struct te_crypto_channel *channel)
{
	te_reg_dsc_reset(channel->dsc_idx);
	te_reg_dsc_set_endian(channel->dsc_idx, true);
}

static void enable_interrupt(struct te_crypto_channel *channel)
{
	TE_REG_SetIntrEnable(channel->intr_mask, true);
	te_reg_dsc_set_intr_enable(channel->dsc_idx, DSC_INTR_DMA_DONE, true);
}

static void disable_interrupt(struct te_crypto_channel *channel)
{
	te_reg_dsc_set_intr_enable(channel->dsc_idx, DSC_INTR_DMA_DONE, false);
	TE_REG_SetIntrEnable(channel->intr_mask, false);
}

static const struct te_type_conv type_dsc_format[] = {
	{ TE_CRYPTO_FMT_DATA, DSC_FORMAT_DATA },
	{ TE_CRYPTO_FMT_TS_188, DSC_FORMAT_TS },
	{ TE_CRYPTO_FMT_TS_192, DSC_FORMAT_TIMESTAMP_TS },
};

static const struct te_type_conv type_dsc_crypto[] = {
	{ TE_CRYPTO_BYPASS, DSC_CRYPTO_TYPE_BYPASS },
	{ TE_CRYPTO_DES, DSC_CRYPTO_TYPE_DES },
	{ TE_CRYPTO_TDES, DSC_CRYPTO_TYPE_TDES },
	{ TE_CRYPTO_AES, DSC_CRYPTO_TYPE_AES },
	{ TE_CRYPTO_MULTI2, DSC_CRYPTO_TYPE_MULTI2 },
};

static const struct te_type_conv type_dsc_blk[] = {
	{ TE_CRYPTO_BLK_ECB, DSC_BLK_MODE_ECB },
	{ TE_CRYPTO_BLK_CBC, DSC_BLK_MODE_CBC },
	{ TE_CRYPTO_BLK_CTR, DSC_BLK_MODE_CTR },
};

static const struct te_type_conv type_dsc_res[] = {
	{ TE_CRYPTO_RES_CLEAR, DSC_RES_MODE_CLEAR },
	{ TE_CRYPTO_RES_CTS, DSC_RES_MODE_CTS },
	{ TE_CRYPTO_RES_OFB, DSC_RES_MODE_OFB },
	{ TE_CRYPTO_RES_SCTE, DSC_RES_MODE_SCTE },
};

static int crypto_set_config(struct te_crypto_ctx *ctx,
			     struct te_crypto_config *cfg)
{
	u32 v;
	struct te_reg_dsc_config *reg_cfg;

	switch (cfg->fmt) {
	case TE_CRYPTO_FMT_TS_188:
		ctx->align_size = 188;
		break;
	case TE_CRYPTO_FMT_TS_192:
		ctx->align_size = 192;
		break;
	case TE_CRYPTO_FMT_DATA:
	default:
#if 0
		switch (cfg->type) {
		case TE_CRYPTO_AES:
			ctx->align_size = AES_IV_SIZE;
			break;
		case TE_CRYPTO_DES:
		case TE_CRYPTO_TDES:
			ctx->align_size = DES_IV_SIZE;
			break;
		case TE_CRYPTO_MULTI2:
			log_error("not support multi2 for data\n");
			return -EINVAL;
		default:
			ctx->align_size = 4;
			break;
		}
#else
		if (cfg->type != TE_CRYPTO_AES) {
			log_error("only support AES for data format\n");
			return -EINVAL;
		}
		ctx->align_size = AES_IV_SIZE;
#endif
	}

	reg_cfg = &ctx->reg_cfg;

	v = convert_to_type1(type_dsc_crypto, cfg->type, INV_TYPE);
	if (v == INV_TYPE) {
		log_error("invalid type(%d)\n", cfg->type);
		return -EINVAL;
	}
	reg_cfg->type = v;

	v = convert_to_type1(type_dsc_blk, cfg->blk, INV_TYPE);
	if (v == INV_TYPE) {
		log_error("invalid block mode(%d)\n", cfg->blk);
		return -EINVAL;
	}
	reg_cfg->blk_mode = v;

	v = convert_to_type1(type_dsc_res, cfg->res, INV_TYPE);
	if (v == INV_TYPE) {
		log_error("invalid residual mode(%d)\n", cfg->res);
		return -EINVAL;
	}
	reg_cfg->res_mode = v;

	v = convert_to_type1(type_dsc_format, cfg->fmt, INV_TYPE);
	if (v == INV_TYPE) {
		log_error("invalid format(%d)\n", cfg->fmt);
		return -EINVAL;
	}
	ctx->reg_fmt = v;

	if (cfg->type == TE_CRYPTO_AES) {
		if (cfg->key_size != 16 && cfg->key_size != 24 &&
		    cfg->key_size != 32) {
			log_error("invalid key size(%d)\n", cfg->key_size);
			return -EINVAL;
		}

		ctx->iv_size = AES_IV_SIZE;
		ctx->key_size = cfg->key_size;
	} else if (cfg->type == TE_CRYPTO_DES) {
		ctx->iv_size = DES_IV_SIZE;
		ctx->key_size = DES_KEY_SIZE;
	} else if (cfg->type == TE_CRYPTO_TDES) {
		ctx->iv_size = TDES_IV_SIZE;
		ctx->key_size = TDES_KEY_SIZE;
	} else if (cfg->type == TE_CRYPTO_MULTI2) {
		ctx->iv_size = MULTI2_IV_SIZE;
		ctx->key_size = MULTI2_DKEY_SIZE;
	}
	reg_cfg->key_size = ctx->key_size;

	ctx->cfg = *cfg;

	return 0;
}

int te_crypto_set_config(struct te_crypto_ctx *ctx,
			 struct te_crypto_config *cfg)
{
	int ret;

	mutex_lock(&ctx->mutex);

	if (ctx->state == CRYPTO_STATE_GO) {
		log_error("busy\n");
		ret = -EBUSY;
		goto exit;
	}

	ret = crypto_set_config(ctx, cfg);
	if (ret) {
		ctx->state = CRYPTO_STATE_IDLE;
	} else {
		ctx->state = CRYPTO_STATE_INIT;
	}

exit:
	mutex_unlock(&ctx->mutex);

	return ret;
}

int te_crypto_set_timeout(struct te_crypto_ctx *ctx, unsigned long timeout)
{
	int ret;

	mutex_lock(&ctx->mutex);
	if (ctx->state == CRYPTO_STATE_GO) {
		log_error("busy\n");
		ret = -EBUSY;
	} else {
		ctx->timeout = timeout;
		ret = 0;
	}
	mutex_unlock(&ctx->mutex);

	return ret;
}

static int crypto_set_iv_key(struct te_crypto_ctx *ctx,
			     enum te_crypto_set_type type, const u8 *value,
			     u8 size)
{
	u8 *dst;
	u8 esize;

	if (ctx->cfg.fmt == TE_CRYPTO_FMT_DATA) {
		switch (type) {
		case TE_CRYPTO_IV:
			dst = ctx->set.data.iv;
			break;
		case TE_CRYPTO_KEY:
			dst = ctx->set.data.key;
			break;
		default:
			return -EINVAL;
		}
	} else {
		if (ctx->cfg.type == TE_CRYPTO_MULTI2) {
			switch (type) {
			case TE_CRYPTO_MULTI2_SKEY:
				dst = ctx->set.multi2.skey;
				break;
			case TE_CRYPTO_MULTI2_IV:
				dst = ctx->set.multi2.iv;
				break;
			case TE_CRYPTO_EVEN_KEY:
				dst = ctx->set.multi2.dkey[EVEN_IDX];
				break;
			case TE_CRYPTO_ODD_KEY:
				dst = ctx->set.multi2.dkey[ODD_IDX];
				break;
			default:
				return -EINVAL;
			}
		} else {
			switch (type) {
			case TE_CRYPTO_EVEN_IV:
				dst = ctx->set.ts.iv[EVEN_IDX];
				break;
			case TE_CRYPTO_ODD_IV:
				dst = ctx->set.ts.iv[ODD_IDX];
				break;
			case TE_CRYPTO_EVEN_KEY:
				dst = ctx->set.ts.key[EVEN_IDX];
				break;
			case TE_CRYPTO_ODD_KEY:
				dst = ctx->set.ts.key[ODD_IDX];
				break;
			default:
				return -EINVAL;
			}
		}
	}

	// get expected size
	switch (type) {
	case TE_CRYPTO_KEY:
	case TE_CRYPTO_EVEN_KEY:
	case TE_CRYPTO_ODD_KEY:
		esize = ctx->key_size;
		break;
	case TE_CRYPTO_MULTI2_SKEY:
		esize = MULTI2_SKEY_SIZE;
		break;
	case TE_CRYPTO_IV:
	case TE_CRYPTO_EVEN_IV:
	case TE_CRYPTO_ODD_IV:
	default:
		esize = ctx->iv_size;
		break;
	}

	if (esize != size) {
		return -EINVAL;
	}

	memcpy(dst, value, size);

	return 0;
}

int te_crypto_set_iv_key(struct te_crypto_ctx *ctx,
			 enum te_crypto_set_type type, const u8 *value, u8 size)
{
	int ret;

	mutex_lock(&ctx->mutex);

	if (ctx->state == CRYPTO_STATE_IDLE) {
		log_error("idle\n");
		ret = -EINVAL;
		goto exit;
	}

	if (ctx->state == CRYPTO_STATE_GO) {
		log_error("busy\n");
		ret = -EBUSY;
		goto exit;
	}

	ret = crypto_set_iv_key(ctx, type, value, size);

exit:
	mutex_unlock(&ctx->mutex);

	return ret;
}

static int __config_dev_request(struct te_crypto_channel *channel)
{
	struct crypto_dev_request *req = channel->req;
	struct te_crypto_ctx *ctx = req->ctx;
	int idx = channel->dsc_idx;

	te_reg_dsc_reset(idx);

	if (req->mode == TE_CRYPTO_ENCRYPTION)
		ctx->reg_cfg.scramble = true;
	else
		ctx->reg_cfg.scramble = false;

	te_reg_dsc_set_config(idx, &ctx->reg_cfg);

	// set iv & key
	if (ctx->cfg.type == TE_CRYPTO_MULTI2) {
		te_reg_dsc_set_multi2(idx, DSC_MULTI2_IV, ctx->set.multi2.iv,
				      MULTI2_IV_SIZE);
		te_reg_dsc_set_multi2(idx, DSC_MULTI2_SKEY,
				      ctx->set.multi2.skey, MULTI2_SKEY_SIZE);
		te_reg_dsc_set_multi2(idx, DSC_EVEN_KEY,
				      ctx->set.multi2.dkey[EVEN_IDX],
				      MULTI2_DKEY_SIZE);
		te_reg_dsc_set_multi2(idx, DSC_ODD_KEY,
				      ctx->set.multi2.dkey[ODD_IDX],
				      MULTI2_DKEY_SIZE);
	} else if (ctx->cfg.fmt == TE_CRYPTO_FMT_DATA) {
		if (ctx->cfg.blk != TE_CRYPTO_BLK_ECB) {
			te_reg_dsc_set_iv_key(idx, DSC_IV, ctx->set.data.iv,
					      ctx->iv_size);
		}
		te_reg_dsc_set_iv_key(idx, DSC_KEY, ctx->set.data.key,
				      ctx->key_size);
	} else {
		// TE_CRYPTO_FMT_TS_188 || TE_CRYPTO_FMT_TS_192
		if (req->mode == TE_CRYPTO_ENCRYPTION) {
			int sidx;
			if (req->tsc == TE_CRYPTO_TSC_ODD) {
				te_reg_dsc_set_odd_mode(idx, true);
				sidx = ODD_IDX;
			} else {
				te_reg_dsc_set_odd_mode(idx, false);
				sidx = EVEN_IDX;
			}

			// in odd mode, set odd key into even key register.
			if (ctx->cfg.blk != TE_CRYPTO_BLK_ECB) {
				te_reg_dsc_set_iv_key(idx, DSC_IV,
						      ctx->set.ts.iv[sidx],
						      ctx->iv_size);
			}

			te_reg_dsc_set_iv_key(idx, DSC_KEY,
					      ctx->set.ts.key[sidx],
					      ctx->key_size);
		} else {
			if (ctx->cfg.blk != TE_CRYPTO_BLK_ECB) {
				te_reg_dsc_set_iv_key(idx, DSC_EVEN_IV,
						      ctx->set.ts.iv[EVEN_IDX],
						      ctx->iv_size);
				te_reg_dsc_set_iv_key(idx, DSC_ODD_IV,
						      ctx->set.ts.iv[ODD_IDX],
						      ctx->iv_size);
			}
			te_reg_dsc_set_iv_key(idx, DSC_EVEN_KEY,
					      ctx->set.ts.key[EVEN_IDX],
					      ctx->key_size);
			te_reg_dsc_set_iv_key(idx, DSC_ODD_KEY,
					      ctx->set.ts.key[ODD_IDX],
					      ctx->key_size);
		}
	}

	return 0;
}

static int __wait_for_dma_done(struct te_crypto_channel *channel)
{
	int ret = 0;
	struct te_reg_dsc_status s;
	u64 start, elapsed;

	/* No way to stop the dma, just wait for the end of the xfer.
	 * DO NOT reset during busy state,
	 * it causes h/w fault and never recovered. */

	te_reg_dsc_get_status(channel->dsc_idx, &s);
	if (s.busy) {
		start = te_get_ms_tick();
		while (1) {
			te_reg_dsc_get_status(channel->dsc_idx, &s);
			elapsed = te_get_ms_tick() - start;
			if (!s.busy) {
				log_debug("busy for %lldms\n", elapsed);
				break;
			}

			if (elapsed > DMA_DONE_MAX_WAIT_TIME) {
				log_error("dma not done !!!\n");

				// TODO: recover h/w

				ret = -EIO;
				break;
			}

			msleep(1);
		}
	}

	return ret;
}

/**
 * set_next_iv - set the next IV if needed
 *
 * @data: last ecnrypted or decrypted data
 * @size: size of data
 */
static void set_next_iv(struct crypto_dev_request *req, const void *data,
			size_t size)
{
	u8 *iv;
	struct te_crypto_ctx *ctx = req->ctx;

	if (ctx->cfg.fmt != TE_CRYPTO_FMT_DATA ||
	    ctx->cfg.blk == TE_CRYPTO_BLK_ECB)
		return;

	iv = ctx->set.data.iv;
	if (ctx->cfg.blk == TE_CRYPTO_BLK_CBC) {
		const void *ciphertext;
		/* The next IV is the ciphertext of the previous block */
		if (req->mode == TE_CRYPTO_ENCRYPTION) {
			ciphertext = data + size - ctx->iv_size;
		} else {
			ciphertext = req->next_iv;
		}
		memcpy(iv, ciphertext, ctx->iv_size);
	} else if (ctx->cfg.blk == TE_CRYPTO_BLK_CTR) {
		u32 i, v;
		bool carry;
		u32 block_count = size / ctx->iv_size;

		// add block count to counter
		v = te_get32(iv + ctx->iv_size - 4); // get LSB 4byte
		if (block_count > (u32)(0xFFFFFFFF - v)) // overflow
			carry = true;
		else
			carry = false;

		v += block_count;
		te_put32(iv + ctx->iv_size - 4, v);
		if (carry) {
			// add carry to MSB
			for (i = 8; i <= ctx->iv_size; i += 4) {
				v = te_get32(iv + ctx->iv_size - i);
				v += 1;
				te_put32(iv + ctx->iv_size - i, v);
				if (v != 0)
					break;
			}
		}
	}
}

static void save_data_for_next_iv(struct crypto_dev_request *req,
				  const void *data, size_t size)
{
	struct te_crypto_ctx *ctx = req->ctx;

	if (ctx->cfg.fmt == TE_CRYPTO_FMT_DATA &&
	    ctx->cfg.blk == TE_CRYPTO_BLK_CBC &&
	    req->mode == TE_CRYPTO_DECRYPTION) {
		/* save the ciphertext for the next IV */
		memcpy(req->next_iv, data + size - ctx->iv_size, ctx->iv_size);
	}
}

static inline int __enqueue_dev_request(struct te_crypto_channel *channel,
					struct crypto_dev_request *req)
{
	// TODO: MAX QUEUE ??

	list_add_tail(&req->list, &channel->queue.reqs);
	channel->queue.len++;

	log_debug("enqueue(%d) req(%p)\n", channel->queue.len, req);

	return 0;
}

static inline struct crypto_dev_request *
__dequeue_dev_reqeust(struct te_crypto_channel *channel)
{
	struct crypto_dev_request *req;

	req = list_first_entry_or_null(&channel->queue.reqs,
				       struct crypto_dev_request, list);
	if (!req)
		return NULL;

	list_del(&req->list);
	channel->queue.len--;

	log_debug("dequeue(%d) req(%p)\n", channel->queue.len, req);

	return req;
}

static inline void __remove_dev_request(struct te_crypto_channel *channel,
					struct crypto_dev_request *req)
{
	list_del(&req->list);
	channel->queue.len--;

	log_debug("remove(%d) req(%p)\n", channel->queue.len, req);
}

#ifdef USE_CRYPTO_ASYNC_REQUEST
static int __start_dev_request(struct te_crypto_channel *channel)
{
	int ret;
	struct crypto_dev_request *req = channel->req;
	struct te_crypto_ctx *ctx = req->ctx;
	struct te_crypto_data *data = req->data;

	if (data->type == CRYPTO_ADDR_PHYS) {
		req->in = data->phys.in;
		req->out = data->phys.out;
		req->size = data->size;
	} else {
		size_t size, remained;
		struct crypto_buffer *b = &channel->buf;

		if (req->offset >= data->size) {
			return -EINVAL;
		}

		remained = data->size - req->offset;
		if (remained > b->size) {
			size = (b->size / ctx->align_size) * ctx->align_size;
		} else {
			size = remained;
		}
		memcpy(b->vaddr, data->virt.in + req->offset, size);

		// save data to get the next iv if needed
		save_data_for_next_iv(req, b->vaddr, size);

		te_cache_sync(b->paddr, b->vaddr, size, TE_DATA_TO_DEVICE);

		req->in = b->paddr;
		req->out = b->paddr;
		req->size = size;
	}
	__config_dev_request(channel);

	channel->done = false;
	ret = te_reg_dsc_start(channel->dsc_idx, ctx->reg_fmt, (u32)req->in,
			       (u32)req->out, req->size);

	return ret;
}

static int __finish_dev_request(struct te_crypto_channel *channel)
{
	int ret = 0;
	struct crypto_dev_request *req = channel->req;
	struct te_crypto_data *data = req->data;

	if (data->type == CRYPTO_ADDR_VIRT) {
		struct crypto_buffer *b = &channel->buf;
		void *out = data->virt.out + req->offset;
		size_t size = req->size;

		te_cache_sync(b->paddr, b->vaddr, size, TE_DATA_FROM_DEVICE);

		// set the next iv if needed
		set_next_iv(req, b->vaddr, size);

		memcpy(out, b->vaddr, size);

		req->offset += size;
		if (req->offset < data->size) {
			ret = data->size - req->offset;
		}
	}

	return ret;
}

/**
 * __complete_dev_request - complete request if finished
 * @res: remained data size, if res > 0 then add request again
 *
 */
static void __complete_dev_request(struct te_crypto_channel *channel, int res)
{
	struct crypto_dev_request *req = channel->req;

	if (res > 0) {
		__enqueue_dev_request(channel, req);
	} else {
		req->res = res;
		if (req->async_callback) {
			queue_work(system_wq, &req->async_work);
		} else {
			set_bit(CRYPTO_FLAGS_DONE, &req->flags);
			wake_up_interruptible(&req->wq);
		}
	}

	channel->req = NULL;
	channel->done = false;
}

static void __handle_request_queue(struct te_crypto_channel *channel)
{
	int ret;
	struct crypto_dev_request *req;

	if (channel->req)
		return;

retry:
	req = __dequeue_dev_reqeust(channel);
	if (!req)
		return;

	// set current request
	channel->req = req;
	ret = __start_dev_request(channel);
	if (ret) {
		log_error("__start_request(%p) failed(%d)\n", req, ret);

		__complete_dev_request(channel, ret);

		goto retry;
	}
}

static void __cancel_dev_request(struct te_crypto_channel *channel)
{
	struct crypto_dev_request *req = channel->req;

	log_debug("%s(%p)\n", __func__, req);

	__wait_for_dma_done(channel);
	__complete_dev_request(channel, -ECANCELED);

#if 0
	// ret = __wait_for_dma_done(dev)
	// if __wait_for_dma_done has an error, it means h/w broken
	if (ret) {
		te_reg_dsc_reset(dev->idx);
		__handle_request_queue(dev);
	}
#endif
}

static int add_request(struct crypto_dev_request *req)
{
	struct te_crypto_ctx *ctx = req->ctx;
	struct te_crypto_channel *channel = ctx->channel;

	mutex_lock(&channel->mutex);

	__enqueue_dev_request(channel, req);
	__handle_request_queue(channel);

	mutex_unlock(&channel->mutex);

	return 0;
}

static void cancel_request_done(struct crypto_dev_request *req, bool wakeup)
{
	struct te_crypto_ctx *ctx = req->ctx;
	struct te_crypto_channel *channel = ctx->channel;
	struct crypto_dev_request *a;
	bool found = false;

	mutex_lock(&channel->mutex);

	list_for_each_entry (a, &channel->queue.reqs, list) {
		if (a == req) {
			found = true;
			break;
		}
	}

	log_debug("%s - found=%d\n", __func__, found);

	if (found) {
		list_del(&req->list);
		if (wakeup) {
			set_bit(CRYPTO_FLAGS_CANCEL, &req->flags);
			wake_up_interruptible(&req->wq);
		}
	} else {
		// request is running
		if (channel->req == req) {
			__cancel_dev_request(channel);
		}
	}
	mutex_unlock(&channel->mutex);
}

static void cancel_request(struct crypto_dev_request *req)
{
	cancel_request_done(req, true);
}

static void async_callback_work(struct work_struct *work)
{
	struct crypto_dev_request *req;

	req = container_of(work, struct crypto_dev_request, async_work);

	req->ctx->state = CRYPTO_STATE_DONE;
	req->async_callback(req->ctx, req->res);
}

static void request_done_work(struct work_struct *work)
{
	int ret;
	struct te_crypto_channel *channel;

	channel = container_of(work, struct te_crypto_channel, done_work);

	mutex_lock(&channel->mutex);

	log_debug("%s - done=%d\n", __func__, channel->done);

	if (channel->done && channel->req) {
		ret = __finish_dev_request(channel);
		__complete_dev_request(channel, ret);
	}
	__handle_request_queue(channel);

	mutex_unlock(&channel->mutex);
}

static bool req_done_cond(struct crypto_dev_request *req)
{
	if (test_bit(CRYPTO_FLAGS_DONE, &req->flags) ||
	    test_bit(CRYPTO_FLAGS_CANCEL, &req->flags))
		return true;

	return false;
}

static int wait_for_req_done(struct crypto_dev_request *req)
{
	int ret;
	struct te_crypto_ctx *ctx = req->ctx;

	log_debug("%s(timeout=%lu)\n", __func__, ctx->timeout);

	ret = crypto_wait_event(req->wq, req_done_cond(req), ctx->timeout);
	if (ret) {
		// -ERESTARTSYS or -ETIME
		cancel_request_done(req, false);
	} else {
		if (test_bit(CRYPTO_FLAGS_DONE, &req->flags))
			ret = req->res;
		else
			ret = -ECANCELED;
	}

	return ret;
}

static int do_request(struct crypto_dev_request *req)
{
	int ret = 0;
	struct te_crypto_ctx *ctx = req->ctx;

	if (req->data->type == CRYPTO_ADDR_USER) {
		ctx->state = CRYPTO_STATE_DONE;
		return -EINVAL;
	}

	ret = add_request(req);
	if (ret)
		return ret;

	if (!req->async_callback) {
		ret = wait_for_req_done(req);
		ctx->state = CRYPTO_STATE_DONE;
	}

	return ret;
}
#else
static bool dsc_condition(struct te_crypto_channel *channel)
{
	if (channel->done)
		return true;

	return false;
}

static int wait_for_dsc_done(struct te_crypto_channel *channel,
			     unsigned long timeout)
{
	int ret;

	ret = crypto_wait_event(channel->wq, dsc_condition(channel), timeout);
	if (ret) {
		__wait_for_dma_done(channel);
	}

	return ret;
}

static int __do_phys_request(struct crypto_dev_request *req)
{
	int ret;
	struct te_crypto_ctx *ctx = req->ctx;
	struct te_crypto_channel *channel = ctx->channel;

	__config_dev_request(channel);

	channel->done = false;
	ret = te_reg_dsc_start(channel->dsc_idx, ctx->reg_fmt, (u32)req->in,
			       (u32)req->out, req->size);
	if (!ret) {
		ret = wait_for_dsc_done(channel, DEFAULT_DEV_TIMEOUT);
	}

	return ret;
}

static void __wakeup_next_request(struct te_crypto_channel *channel)
{
	struct crypto_dev_request *req;

	req = list_first_entry_or_null(&channel->queue.reqs,
				       struct crypto_dev_request, list);
	if (req) {
		channel->req = req;
		set_bit(CRYPTO_FLAGS_DONE, &req->flags);
		wake_up_interruptible(&req->wq);
	} else {
		channel->req = NULL; // no runnable request
	}
}

static bool req_wait_cond(struct crypto_dev_request *req)
{
	if (test_bit(CRYPTO_FLAGS_DONE, &req->flags) ||
	    test_bit(CRYPTO_FLAGS_CANCEL, &req->flags))
		return true;

	return false;
}

static int get_dev_request(struct crypto_dev_request *req)
{
	int ret = 0;
	struct te_crypto_ctx *ctx = req->ctx;
	struct te_crypto_channel *channel = ctx->channel;
	bool wait;

	mutex_lock(&channel->mutex);

	if (channel->req) {
		__enqueue_dev_request(channel, req);
		wait = true;
	} else {
		channel->req = req;
		wait = false;
	}

	mutex_unlock(&channel->mutex);

	if (wait) {
		ret = crypto_wait_event(req->wq, req_wait_cond(req),
					ctx->timeout);

		mutex_lock(&channel->mutex);

		__remove_dev_request(channel, req);

		log_debug("run waited req(%p) - ret=%d\n", req, ret);

		if (!ret) {
			if (test_bit(CRYPTO_FLAGS_CANCEL, &req->flags)) {
				log_debug("req(%p) canceled\n", req);
				ret = -ECANCELED;
			}
		}

		// wakeup other request if it is an owner but has an error
		if (ret && channel->req == req) {
			__wakeup_next_request(channel);
		}

		mutex_unlock(&channel->mutex);
	}

	return ret;
}

static void put_dev_request(struct crypto_dev_request *req)
{
	struct te_crypto_ctx *ctx = req->ctx;
	struct te_crypto_channel *channel = ctx->channel;

	mutex_lock(&channel->mutex);
	__wakeup_next_request(channel);
	mutex_unlock(&channel->mutex);
}

/* reqeust for virtual & user address */
static int __do_request(struct crypto_dev_request *req)
{
	int ret = 0;
	size_t size;
	size_t remained;
	struct te_crypto_ctx *ctx = req->ctx;
	struct te_crypto_channel *channel = ctx->channel;
	struct crypto_buffer *b = &channel->buf;
	struct te_crypto_data *d = req->data;

	req->in = b->paddr;
	req->out = b->paddr;

	while (req->offset < d->size) {
		remained = d->size - req->offset;
		if (remained > b->size) {
			size = (b->size / ctx->align_size) * ctx->align_size;
		} else {
			size = remained;
		}

		if (d->type == CRYPTO_ADDR_USER) {
			const void __user *in = d->user.in + req->offset;
			if (copy_from_user(b->vaddr, in, size)) {
				ret = -EFAULT;
				break;
			}
		} else {
			const void *in = d->virt.in + req->offset;
			memcpy(b->vaddr, in, size);
		}
		req->size = size;

		// save data to get the next iv if needed
		save_data_for_next_iv(req, b->vaddr, size);

		te_cache_sync(b->paddr, b->vaddr, size, TE_DATA_TO_DEVICE);

		ret = __do_phys_request(req);
		if (ret)
			break;

		te_cache_sync(b->paddr, b->vaddr, size, TE_DATA_FROM_DEVICE);

		// set the next iv if needed
		set_next_iv(req, b->vaddr, size);

		if (d->type == CRYPTO_ADDR_USER) {
			void __user *out = d->user.out + req->offset;
			if (copy_to_user(out, b->vaddr, size)) {
				ret = -EFAULT;
				break;
			}
		} else {
			void *out = d->virt.out + req->offset;
			memcpy(out, b->vaddr, size);
		}

		req->offset += size;
	}

	return ret;
}

static int do_request(struct crypto_dev_request *req)
{
	int ret;
	struct te_crypto_ctx *ctx = req->ctx;
	struct te_crypto_data *data = req->data;

	/* get device for this request */
	ret = get_dev_request(req);
	if (ret)
		goto exit;

	if (data->type == CRYPTO_ADDR_PHYS) {
		// process whole data at once
		req->in = data->phys.in;
		req->out = data->phys.out;
		req->size = data->size;

		ret = __do_phys_request(req);
	} else {
		ret = __do_request(req);
	}

	put_dev_request(req);

exit:
	ctx->state = CRYPTO_STATE_DONE;

	return ret;
}

static void cancel_request(struct crypto_dev_request *req)
{
	set_bit(CRYPTO_FLAGS_CANCEL, &req->flags);
	wake_up_interruptible(&req->wq);
}
#endif

static void init_dev_request(struct te_crypto_ctx *ctx,
			     struct crypto_dev_request *req)
{
	req->ctx = ctx;
	init_waitqueue_head(&req->wq);

#ifdef USE_CRYPTO_ASYNC_REQUEST
	INIT_WORK(&req->async_work, async_callback_work);
#endif
}

static int crypto_request(struct te_crypto_ctx *ctx,
			  struct crypto_request_param *param)
{
	int ret;
	struct crypto_dev_request *req;

	mutex_lock(&ctx->mutex);

	if (ctx->state != CRYPTO_STATE_INIT &&
	    ctx->state != CRYPTO_STATE_DONE) {
		log_error("invalid state(%d)\n", ctx->state);
		mutex_unlock(&ctx->mutex);
		return -EINVAL;
	}

	if (param->data->size % ctx->align_size) {
		log_error("unaligned size(%zu)\n", param->data->size);
		mutex_unlock(&ctx->mutex);
		return -EINVAL;
	}

	req = &ctx->req;

	req->mode = param->mode;
	req->tsc = param->tsc;
#ifdef USE_CRYPTO_ASYNC_REQUEST
	req->async_callback = param->async_callback;
	if (req->async_callback) {
		req->__data = *param->data;
		req->data = &req->__data;
	} else {
		req->data = param->data;
	}
#else
	req->data = param->data;
#endif
	req->offset = 0;
	req->flags = 0;

	ctx->state = CRYPTO_STATE_GO;
	mutex_unlock(&ctx->mutex);

	ret = do_request(req);

	return ret;
}

int te_crypto_decrypt(struct te_crypto_ctx *ctx, struct te_crypto_data *data)
{
	struct crypto_request_param param;

	param.mode = TE_CRYPTO_DECRYPTION;
	param.data = data;
#ifdef USE_CRYPTO_ASYNC_REQUEST
	param.async_callback = NULL;
#endif

	return crypto_request(ctx, &param);
}

int te_crypto_encrypt(struct te_crypto_ctx *ctx, struct te_crypto_data *data,
		      enum te_crypto_tsc tsc)
{
	struct crypto_request_param param;

	param.mode = TE_CRYPTO_ENCRYPTION;
	param.data = data;
	param.tsc = tsc;
#ifdef USE_CRYPTO_ASYNC_REQUEST
	param.async_callback = NULL;
#endif

	return crypto_request(ctx, &param);
}

int te_crypto_async_decrypt(struct te_crypto_ctx *ctx,
			    struct te_crypto_data *data,
			    te_crypto_callback_t callback)
{
#ifdef USE_CRYPTO_ASYNC_REQUEST
	struct crypto_request_param param;

	param.mode = TE_CRYPTO_DECRYPTION;
	param.data = data;
	param.async_callback = callback;

	return crypto_request(ctx, &param);
#else
	return -EPERM;
#endif
}

int te_crypto_async_encrypt(struct te_crypto_ctx *ctx,
			    struct te_crypto_data *data, enum te_crypto_tsc tsc,
			    te_crypto_callback_t callback)
{
#ifdef USE_CRYPTO_ASYNC_REQUEST
	struct crypto_request_param param;

	param.mode = TE_CRYPTO_ENCRYPTION;
	param.data = data;
	param.async_callback = callback;

	return crypto_request(ctx, &param);
#else
	return -EPERM;
#endif
}

int te_crypto_cancel(struct te_crypto_ctx *ctx)
{
	log_debug("%s(%p)\n", __func__, ctx);

	mutex_lock(&ctx->mutex);
	if (ctx->state == CRYPTO_STATE_GO) {
		cancel_request(&ctx->req);
	}
	mutex_unlock(&ctx->mutex);

	return 0;
}

/**
 * te_crypto_open - allocate crypto context
 *
 * Returns struct te_crypto_ctx or ERR_PTR
 */
struct te_crypto_ctx *te_crypto_open(struct te_crypto_channel *channel)
{
	struct te_crypto_ctx *ctx;

	ctx = kmalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx) {
		return ERR_PTR(-ENOMEM);
	}

	ctx->state = CRYPTO_STATE_IDLE;
	ctx->timeout = DEFAULT_CTX_TIMEOUT;
	ctx->channel = channel;
	mutex_init(&ctx->mutex);

	init_dev_request(ctx, &ctx->req);

	atomic_inc(&channel->refcount);

	return ctx;
}

struct te_crypto_ctx *te_crypto_open_from_device(struct te_crypto_device *dev,
						 u8 num)
{
	struct te_crypto_channel *channel = te_crypto_get_channel(dev, num);

	if (!channel)
		return ERR_PTR(-EINVAL);

	return te_crypto_open(channel);
}

void te_crypto_close(struct te_crypto_ctx *ctx)
{
	struct te_crypto_channel *channel = ctx->channel;

	if (ctx->state == CRYPTO_STATE_GO) {
		log_warning("%s(%p) - running state\n", __func__, ctx);
	}
	kfree(ctx);

	atomic_dec(&channel->refcount);
}

struct te_crypto_device *te_crypto_get_device(struct te_device *dev)
{
	struct te_subdev *sd;

	sd = te_get_subdev(dev, CRYPTO_DEVICE_NAME);
	if (!sd)
		return NULL;

	return te_subdev_to_crypto_device(sd);
}

struct te_crypto_channel *te_crypto_get_channel(struct te_crypto_device *dev,
						u8 num)
{
	if (num < dev->num_channel)
		return &dev->channels[num];

	return NULL;
}


/* file operation functions */
static int ioc_crypto_config(struct te_crypto_fh *fh,
			     struct te_crypto_config *arg)
{
	int ret;
	struct te_crypto_ctx *ctx = fh->ctx;

	ret = te_crypto_set_config(ctx, arg);

	return ret;
}

static int ioc_crypto_set(struct te_crypto_fh *fh, struct te_crypto_set *arg)
{
	int ret;
	struct te_crypto_ctx *ctx = fh->ctx;

	ret = te_crypto_set_iv_key(ctx, arg->type, arg->value, arg->length);

	return ret;
}

static int ioc_crypto_multi_set(struct te_crypto_fh *fh,
				struct te_crypto_user_multi_set *arg)
{
	int ret, i;
	struct te_crypto_set s;
	const struct te_crypto_set __user *uset;
	struct te_crypto_ctx *ctx = fh->ctx;

	uset = te_ioctl_get_user_ptr(arg->set);
	for (i = 0; i < arg->num; i++) {
		if (copy_from_user(&s, &uset[i], sizeof(s))) {
			ret = -EFAULT;
			break;
		}
		if (s.length > 32) {
			ret = -EINVAL;
			break;
		}
		ret = te_crypto_set_iv_key(ctx, s.type, s.value, s.length);
		if (ret)
			break;
	}

	return ret;
}

static int ioc_crypto_request(struct te_crypto_fh *fh,
			      struct te_crypto_user_request *arg)
{
	int ret;
	struct te_crypto_ctx *ctx = fh->ctx;
	struct te_crypto_data data;
	const void __user *in;
	void __user *out;
#ifdef USE_CRYPTO_ASYNC_REQUEST
	void *vaddr;
#endif

	in = te_ioctl_get_user_ptr(arg->in);
	out = te_ioctl_get_user_ptr(arg->out);

#ifdef USE_CRYPTO_ASYNC_REQUEST
	vaddr = vmalloc(arg->nbytes);
	if (!vaddr) {
		ret = -ENOMEM;
		goto exit;
	}

	if (copy_from_user(vaddr, in, arg->nbytes)) {
		ret = -EFAULT;
		goto err_copy;
	}

	data.type = CRYPTO_ADDR_VIRT;
	data.virt.in = vaddr;
	data.virt.out = vaddr;
	data.size = arg->nbytes;

	if (arg->mode == TE_CRYPTO_ENCRYPTION)
		ret = te_crypto_encrypt(ctx, &data, arg->tsc);
	else
		ret = te_crypto_decrypt(ctx, &data);

	if (!ret) {
		if (copy_to_user(out, vaddr, arg->nbytes)) {
			ret = -EFAULT;
		}
	}

err_copy:
	vfree(vaddr);

exit:

#else
	data.type = CRYPTO_ADDR_USER;
	data.user.in = in;
	data.user.out = out;
	data.size = arg->nbytes;

	if (arg->mode == TE_CRYPTO_ENCRYPTION)
		ret = te_crypto_encrypt(ctx, &data, arg->tsc);
	else
		ret = te_crypto_decrypt(ctx, &data);
#endif


	return ret;
}

static int do_ioctl(void *priv, unsigned int cmd, void *arg)
{
	int ret;
	struct te_crypto_fh *fh = priv;

	switch (cmd) {
	case TE_CRYPTO_IOC_CONFIG:
		ret = ioc_crypto_config(fh, arg);
		break;
	case TE_CRYPTO_IOC_SET:
		ret = ioc_crypto_set(fh, arg);
		break;
	case TE_CRYPTO_IOC_MULTI_SET:
		ret = ioc_crypto_multi_set(fh, arg);
		break;
	case TE_CRYPTO_IOC_REQUEST:
		ret = ioc_crypto_request(fh, arg);
		break;
	default:
		log_error("invalid command[0x%08x]. magic=0x%02X, num=%d", cmd,
			  _IOC_TYPE(cmd), _IOC_NR(cmd));
		ret = -ENOTTY;
		break;
	}

	return ret;
}

static long dev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	return te_ioctl_usercopy(cmd, arg, do_ioctl, NULL, file->private_data);
}

static int dev_open(struct inode *inode, struct file *file)
{
	struct te_crypto_ctx *ctx;
	struct te_crypto_fh *fh;
	struct te_crypto_channel *channel = inode_to_channel(inode);
	struct te_device *tdev = get_te_device(inode_to_device(inode));

	fh = kzalloc(sizeof(*fh), GFP_KERNEL);
	if (!fh)
		return -ENOMEM;

	te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_CRYPTO);

	ctx = te_crypto_open(channel);
	if (IS_ERR(ctx)) {
		kfree(fh);
		return PTR_ERR(ctx);
	}

	fh->ctx = ctx;

	log_trace("device opened (%d:%d)\n", imajor(inode), iminor(inode));

	file->private_data = fh;

	return 0;
}

static int dev_close(struct inode *inode, struct file *file)
{
	struct te_crypto_fh *fh = file->private_data;
	struct te_device *tdev;

	tdev = get_te_device(channel_to_device(fh->ctx->channel));

	te_crypto_close(fh->ctx);

	log_trace("device closed (%d:%d)", imajor(inode), iminor(inode));

	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_CRYPTO);
	kfree(fh);

	return 0;
}

const struct file_operations crypto_dev_fops = {
	.open = dev_open,
	.release = dev_close,
	.unlocked_ioctl = dev_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = dev_ioctl,
#endif
};


static int alloc_crypto_buffer(struct te_crypto_channel *channel,
			       struct crypto_buffer *buf, u32 size)
{
	buf->paddr = te_mem_alloc(channel->mem_ctx, size, "te.crypto");
	if (buf->paddr == 0)
		return -ENOMEM;

	buf->vaddr = te_vmap(buf->paddr, size, true);
	if (!buf->vaddr) {
		te_mem_free(channel->mem_ctx, buf->paddr);
		return -ENOMEM;
	}
	buf->size = size;

	return 0;
}

static void free_crypto_buffer(struct te_crypto_channel *channel,
			       struct crypto_buffer *buf)
{
	te_vunmap(buf->vaddr);
	te_mem_free(channel->mem_ctx, buf->paddr);
}

static int init_channel(struct te_crypto_channel *channel)
{
	int ret;
	struct te_crypto_device *dev = channel_to_device(channel);
	struct te_device *tdev = get_te_device(dev);

	channel->mem_ctx = te_mem_open(TE_MEM_SHARED_NAME);
	if (!channel->mem_ctx)
		return -EIO;

	ret = alloc_crypto_buffer(channel, &channel->buf, HW_BUF_SIZE);
	if (ret) {
		te_mem_close(channel->mem_ctx);
		return ret;
	}

	INIT_LIST_HEAD(&channel->queue.reqs);
	channel->queue.len = 0;
	channel->req = NULL;
	atomic_set(&channel->refcount, 0);

#ifdef USE_CRYPTO_ASYNC_REQUEST
	INIT_WORK(&channel->done_work, request_done_work);
#else
	init_waitqueue_head(&channel->wq);
#endif

	init_hw(channel);
	enable_interrupt(channel);

	ret = te_request_irq(tdev, channel->name, channel->intr_mask,
			     irq_handler, channel);

	return ret;
}

static void release_channel(struct te_crypto_channel *channel)
{
	struct te_crypto_device *dev = channel_to_device(channel);
	struct te_device *tdev = get_te_device(dev);

	te_free_irq(tdev, channel->name);
	free_crypto_buffer(channel, &channel->buf);
	te_mem_close(channel->mem_ctx);
	disable_interrupt(channel);
}

int crypto_device_suspend(struct te_crypto_device *dev)
{
	return 0;
}

int crypto_device_resume(struct te_crypto_device *dev)
{
	int i;
	struct te_crypto_channel *channel;

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];
		init_hw(channel);
		enable_interrupt(channel);
	}

	return 0;
}

int crypto_device_init(struct te_crypto_device *dev)
{
	int i;
	struct te_crypto_channel *channel;

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];
		channel->num = i;
		channel->dsc_idx = 1 + i;
		snprintf(channel->name, sizeof(channel->name), "crypto[%d]", i);
		mutex_init(&channel->mutex);
		channel->intr_mask = TOP_INTR_DSC1; // TODO: FIX ME if it has multi channels

		init_channel(channel);
	}

	crypto_debug_init(dev);

	return 0;
}

void crypto_device_release(struct te_crypto_device *dev)
{
	int i;
	struct te_crypto_channel *channel;

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];
		release_channel(channel);
	}
}
