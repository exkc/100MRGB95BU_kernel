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
 *  TE crypto device driver
 *
 *  author	Kyungseok Hyun (ks.hyun@lge.com)
 *  version	1.0
 *  date	2020.01.07
 *  note
 *
 */


#include "crypto_impl.h"
#include "hma_alloc.h"

#define dprintf(fmt, args...) seq_printf(m, fmt, ##args)
#define dprintf_str(n, v) dprintf(n ":%s\n", v)
#define dprintf_size(n, v) dprintf(n ":%d(%s)\n", v, te_get_readable_size(v))

#define DEBUG_MSG_INTERVAL msecs_to_jiffies(1000)

enum debug_id {
	DEBUG_ID_CONFIG = 0,
};

enum debug_tsc {
	DEBUG_TSC_EVEN = TE_CRYPTO_TSC_EVEN,
	DEBUG_TSC_ODD = TE_CRYPTO_TSC_ODD,
	DEBUG_TSC_EVEN_ODD,
};

struct debug_params {
	u32 idx;
	struct te_crypto_config cfg;
	enum te_crypto_mode mode;
	enum debug_tsc tsc;
	u8 iv_size;
	int log_level; /* 0:no debug msg, others:display staus */
	unsigned long timeout;
	char buf_name[16]; /* hma pool name but 'system' is kenrel memory */
	u32 buf_size;
	u32 buf_attr;
	u8 key[2][MAX_KEY_SIZE];
	u8 iv[2][MAX_IV_SIZE];
	u8 sys_key[MULTI2_SKEY_SIZE];
};

struct debug_buffer {
	size_t in_size;
	struct te_ringbuf in;

	size_t out_size;
	struct te_ringbuf out;

	bool use_hbuf;
	union {
		void *vbuf;
		struct te_hwbuf hbuf;
	};
	size_t size;
};

enum debug_state {
	DEBUG_STATE_IDLE = 0,
	DEBUG_STATE_GO,
	DEBUG_STATE_DONE,
};

struct debug_device {
	struct te_crypto_ctx *ctx;
	struct debug_buffer buf;
	struct debug_params params;
	int align_size;
	size_t rdsize;
	enum te_crypto_tsc tsc; // for DEBUG_TSC_EVEN_ODD

	unsigned long msg_jiffies;
	size_t processed_size;
	u64 start_tick;

	enum debug_state output_state;
	enum debug_state input_state;
	wait_queue_head_t wq;
	struct task_struct *thread;
};

#define DEBUG_VMALLOC_BUF_NAME "vmalloc"

static struct debug_params __debug_params = {
	.idx = 0,
	.cfg = {
		.type = TE_CRYPTO_BYPASS,
		.blk = TE_CRYPTO_BLK_ECB,
		.res = TE_CRYPTO_RES_CLEAR,
		.fmt = TE_CRYPTO_FMT_TS_192,
		.key_size = 0,
	},
	.mode = TE_CRYPTO_DECRYPTION,
	.tsc = DEBUG_TSC_EVEN,

	.log_level = 1,
#if CONFIG_LX_BOARD_FPGA
	.timeout = 10000,	/* 10000ms */
#else
	.timeout = 500,		/* 500ms */
#endif
	.buf_name = { DEBUG_VMALLOC_BUF_NAME /* TE_MEM_SHARED_NAME */ },
	.buf_size = SZ_2M,
};

static struct debug_device *__debug_device;
static DEFINE_MUTEX(debug_mutex);

static struct debug_device *debug_get_device(void)
{
	return __debug_device;
}

static void debug_set_device(struct debug_device *dev)
{
	__debug_device = dev;
}

static const struct te_val_str debug_tsc_str[] = {
	{ DEBUG_TSC_EVEN, "EVEN" },
	{ DEBUG_TSC_ODD, "ODD" },
	{ DEBUG_TSC_EVEN_ODD, "EVEN_ODD" },
};

static enum debug_tsc str_to_debug_tsc(const char *str)
{
	return find_match_value(debug_tsc_str, str, DEBUG_TSC_EVEN);
}

static const char *debug_tsc_to_str(enum debug_tsc tsc)
{
	return find_match_string(debug_tsc_str, tsc, "Invalid");
}

static int debug_alloc_hwbuf(struct te_hwbuf *hbuf, const char *hma_name,
			     u32 size, u32 flags)
{
	int ret;
	phys_addr_t addr;

	addr = hma_alloc_user(hma_name, size, 4096, "te.dsc.debug");
	if (addr == 0)
		return -ENOMEM;

	ret = te_hwbuf_init(hbuf, addr, size, 0, flags);
	if (ret) {
		hma_free(hma_name, addr);
		return ret;
	}

	return 0;
}

static void debug_free_hwbuf(struct te_hwbuf *hbuf, const char *hma_name)
{
	hma_free(hma_name, te_hwbuf_addr(hbuf));
	te_hwbuf_release(hbuf);
}

static int debug_init_buffer(struct debug_device *dev)
{
	int ret, dummy;
	u32 flags;
	void *buf;
	struct debug_buffer *b = &dev->buf;
	struct debug_params *p = &dev->params;

	b->size = p->buf_size;
	/* align buffer size */
	dummy = b->size % dev->align_size;
	if (dummy)
		b->size -= dummy;

	if (!strcmp(DEBUG_VMALLOC_BUF_NAME, p->buf_name)) {
		b->use_hbuf = false;

		b->vbuf = vmalloc(b->size);
		if (!b->vbuf)
			return -ENOMEM;
	} else {
		b->use_hbuf = true;

		flags = TE_BUF_FLAG_NO_EVENT;
		if (p->buf_attr & 0x1)
			flags |= TE_BUF_FLAG_VMAP;
		else
			flags |= TE_BUF_FLAG_VMAP_CACHED;

		ret = debug_alloc_hwbuf(&b->hbuf, p->buf_name, b->size, flags);
		if (ret)
			return ret;
	}

	b->in_size = b->size * 2; // double size of the buffer
	buf = vmalloc(b->in_size);
	if (!buf) {
		ret = -ENOMEM;
		goto err_in_buf;
	}
	te_ringbuf_init(&b->in, buf, b->in_size, TE_BUF_FLAG_UPLOAD_MODULE);

	b->out_size = b->size * 3; // triple size of the buffer
	buf = vmalloc(b->out_size);
	if (!buf) {
		ret = -ENOMEM;
		goto err_out_buf;
	}
	te_ringbuf_init(&b->out, buf, b->out_size, 0);

	return 0;

err_out_buf:
	vfree(te_ringbuf_data(&b->in));
err_in_buf:
	if (b->use_hbuf)
		debug_free_hwbuf(&b->hbuf, p->buf_name);
	else
		vfree(b->vbuf);

	return ret;
}

static void debug_release_buffer(struct debug_device *dev)
{
	struct debug_buffer *b = &dev->buf;
	struct debug_params *p = &dev->params;

	vfree(te_ringbuf_data(&b->in));
	vfree(te_ringbuf_data(&b->out));

	if (b->use_hbuf)
		debug_free_hwbuf(&b->hbuf, p->buf_name);
	else
		vfree(b->vbuf);
}

static void debug_set_crypto_data(struct te_crypto_data *data,
				  struct debug_buffer *b, off_t off,
				  size_t size)
{
	if (b->use_hbuf) {
		data->type = CRYPTO_ADDR_PHYS;
		data->phys.out = te_hwbuf_addr(&b->hbuf) + off;
		data->phys.in = data->phys.out;
	} else {
		data->type = CRYPTO_ADDR_VIRT;
		data->virt.out = b->vbuf + off;
		data->virt.in = data->virt.out;
	}
	data->size = size;
}

static int debug_decrypt(struct debug_device *dev, u32 size)
{
	struct debug_params *p = &dev->params;
	struct te_crypto_ctx *ctx = dev->ctx;
	struct debug_buffer *b = &dev->buf;
	struct te_crypto_data cdata;
	int ret;

	if (p->cfg.type == TE_CRYPTO_MULTI2) {
		u8 *data;
		u32 ofs = 0;
		u32 wsize = dev->align_size;

		data = (b->use_hbuf) ? te_hwbuf_data(&b->hbuf) : b->vbuf;

		if (p->cfg.fmt == TE_CRYPTO_FMT_TS_192)
			data += 4;

		while (ofs < size) {
			u8 tsc = data[ofs + 3] & 0xC0;

			if (tsc == 0x80) {
				te_crypto_set_iv_key(ctx, TE_CRYPTO_EVEN_KEY,
						     p->key[EVEN_IDX], 8);
			} else if (tsc == 0xC0) {
				te_crypto_set_iv_key(ctx, TE_CRYPTO_ODD_KEY,
						     p->key[ODD_IDX], 8);
			}

			debug_set_crypto_data(&cdata, b, ofs, wsize);
			ret = te_crypto_decrypt(ctx, &cdata);
			if (ret)
				break;

			ofs += wsize;
		}
	} else {
		debug_set_crypto_data(&cdata, b, 0, size);
		ret = te_crypto_decrypt(ctx, &cdata);
	}

	return ret;
}

static int debug_encrypt(struct debug_device *dev, u32 size)
{
	struct te_crypto_data cdata;
	struct debug_params *p = &dev->params;
	struct debug_buffer *b = &dev->buf;
	struct te_crypto_ctx *ctx = dev->ctx;
	int ret;

	if (p->cfg.fmt == TE_CRYPTO_FMT_TS_188 ||
	    p->cfg.fmt == TE_CRYPTO_FMT_TS_192) {
		enum te_crypto_tsc tsc;

		if (p->tsc == DEBUG_TSC_EVEN_ODD) {
			u32 ofs = 0;
			u32 wsize = dev->align_size;

			while (ofs < size) {
				tsc = dev->tsc;
				if (dev->tsc == TE_CRYPTO_TSC_EVEN) {
					dev->tsc = TE_CRYPTO_TSC_ODD;
				} else {
					dev->tsc = TE_CRYPTO_TSC_EVEN;
				}

				debug_set_crypto_data(&cdata, b, ofs, wsize);
				ret = te_crypto_encrypt(ctx, &cdata, tsc);
				if (ret)
					break;

				ofs += wsize;
			}
		} else {
			tsc = (p->tsc == DEBUG_TSC_ODD) ?
				TE_CRYPTO_TSC_ODD : TE_CRYPTO_TSC_EVEN;
			debug_set_crypto_data(&cdata, b, 0, size);
			ret = te_crypto_encrypt(ctx, &cdata, tsc);
		}
	} else {
		debug_set_crypto_data(&cdata, b, 0, size);
		ret = te_crypto_encrypt(ctx, &cdata, 0);
	}

	return ret;
}

static int debug_process_input(struct debug_device *dev)
{
	int ret, dummy;
	u32 size;
	struct debug_buffer *b = &dev->buf;

	size = te_ringbuf_avail_size(&b->in);
	if (size < dev->align_size) {
		if (dev->input_state == DEBUG_STATE_DONE) {
			size = te_ringbuf_avail_size(&b->out);
			if (!size) {
				te_ringbuf_set_error(&b->out, -ESHUTDOWN);
				return -ENODEV;
			}
		}
		return -EAGAIN;
	}

	if (size > b->size) {
		size = b->size;
	} else {
		dummy = size % dev->align_size;
		if (dummy)
			size -= dummy;
	}

	if (dev->params.log_level > 1) {
		log_noti("processing - offset:0x%08zx size=%u\n",
			 dev->processed_size, size);
	}

	if (b->use_hbuf) {
		te_ringbuf_raw_read(&b->in, te_hwbuf_data(&b->hbuf), size);
		te_hwbuf_cache_sync(&b->hbuf, 0, size, TE_DATA_TO_DEVICE);
	} else {
		te_ringbuf_raw_read(&b->in, b->vbuf, size);
	}

	if (dev->params.mode == TE_CRYPTO_ENCRYPTION) {
		ret = debug_encrypt(dev, size);
	} else {
		ret = debug_decrypt(dev, size);
	}

	if (ret) {
		te_ringbuf_set_error(&b->out, ret);
		return ret;
	}

	if (b->use_hbuf)
		te_hwbuf_cache_sync(&b->hbuf, 0, size, TE_DATA_FROM_DEVICE);

	return size;
}

static int debug_process_output(struct debug_device *dev, size_t size)
{
	u32 free;
	void *data;
	struct debug_buffer *b = &dev->buf;

	free = te_ringbuf_free_size(&b->out);
	if (free < size)
		return -EAGAIN;

	data = b->use_hbuf ? te_hwbuf_data(&b->hbuf) : b->vbuf;
	te_ringbuf_raw_write(&b->out, data, size);

	dev->processed_size += size;
	if (dev->params.log_level) {
		if (time_is_before_jiffies(dev->msg_jiffies)) {
			log_noti("processed size : %s\n",
				 te_get_readable_size(dev->processed_size));
			dev->msg_jiffies = jiffies + DEBUG_MSG_INTERVAL;
		}
	}

	return 0;
}

static void debug_process_done(struct debug_device *dev)
{
	if (dev->params.log_level) {
		log_noti("process done(%s - %llums elapsed)\n",
			 te_get_readable_size(dev->processed_size),
			 te_get_ms_tick() - dev->start_tick);
	}
}

enum debug_thread_state {
	DEBUG_THREAD_STATE_IDLE = 0,
	DEBUG_THREAD_STATE_INPUT,
	DEBUG_THREAD_STATE_OUTPUT,
	DEBUG_THREAD_STATE_DONE,
	DEBUG_THREAD_STATE_STOP,
};

static int debug_thread(void *data)
{
	int ret;
	size_t size;
	int state = DEBUG_THREAD_STATE_IDLE;
	unsigned int delay_msecs = 0;
	struct debug_device *dev = data;

	while (!kthread_should_stop()) {
		switch (state) {
		case DEBUG_THREAD_STATE_IDLE:
			if (READ_ONCE(dev->input_state) != DEBUG_STATE_IDLE) {
				state = DEBUG_THREAD_STATE_INPUT;
				dev->start_tick = te_get_ms_tick();
			} else
				delay_msecs = 50;
			break;

		case DEBUG_THREAD_STATE_INPUT:
			ret = debug_process_input(dev);
			if (ret < 0) {
				if (ret == -EAGAIN)
					delay_msecs = 2;
				else
					state = DEBUG_THREAD_STATE_DONE;
			} else {
				size = ret;
				state = DEBUG_THREAD_STATE_OUTPUT;
			}
			break;

		case DEBUG_THREAD_STATE_OUTPUT:
			ret = debug_process_output(dev, size);
			if (ret == -EAGAIN) {
				delay_msecs = 2;
			} else {
				state = DEBUG_THREAD_STATE_INPUT;
			}
			break;

		case DEBUG_THREAD_STATE_DONE:
			debug_process_done(dev);
			state = DEBUG_THREAD_STATE_STOP;
			break;

		default:
			delay_msecs = 100;
			break;
		}

		if (delay_msecs) {
			unsigned long v;
			if (delay_msecs < (1000 / HZ)) {
				v = delay_msecs * 1000;
				usleep_range(v, v);
			} else {
				v = msecs_to_jiffies(delay_msecs);
				schedule_timeout_interruptible(v);
			}
			delay_msecs = 0;
		}
	}

	return 0;
}

static void debug_set_data_iv_key(struct debug_device *dev)
{
	struct debug_params *p = &dev->params;
	struct te_crypto_config *cfg = &p->cfg;
	struct te_crypto_ctx *ctx = dev->ctx;

	if (p->log_level > 2) {
		if (cfg->blk != TE_CRYPTO_BLK_ECB) {
			log_noti("IV\n");
			te_hex_dump(p->iv[0], p->iv_size, 1);
		}
		log_noti("KEY\n");
		te_hex_dump(p->key[ODD_IDX], cfg->key_size, 1);
	}

	te_crypto_set_iv_key(ctx, TE_CRYPTO_KEY, p->key[0], cfg->key_size);
	if (cfg->blk == TE_CRYPTO_BLK_ECB)
		return;

	te_crypto_set_iv_key(ctx, TE_CRYPTO_IV, p->iv[0], p->iv_size);
}

static void debug_set_multi2_iv_key(struct debug_device *dev)
{
	struct debug_params *p = &dev->params;
	struct te_crypto_config *cfg = &p->cfg;
	struct te_crypto_ctx *ctx = dev->ctx;

	if (p->log_level > 2) {
		log_noti("IV\n");
		te_hex_dump(p->iv[0], p->iv_size, 1);
		log_noti("SKEY\n");
		te_hex_dump(p->sys_key, MULTI2_SKEY_SIZE, 1);
		log_noti("EVEN KEY\n");
		te_hex_dump(p->key[EVEN_IDX], cfg->key_size, 1);
		log_noti("ODD KEY\n");
		te_hex_dump(p->key[ODD_IDX], cfg->key_size, 1);
	}

	te_crypto_set_iv_key(ctx, TE_CRYPTO_MULTI2_IV, p->iv[0], p->iv_size);
	te_crypto_set_iv_key(ctx, TE_CRYPTO_MULTI2_SKEY, p->sys_key,
			     MULTI2_SKEY_SIZE);
#if 0 // TODO:
	te_crypto_set_iv_key(ctx, TE_CRYPTO_EVEN_KEY, p->key[EVEN_IDX], cfg->key_size);
	te_crypto_set_iv_key(ctx, TE_CRYPTO_ODD_KEY, p->key[ODD_IDX], cfg->key_size);
#endif
}

static void debug_set_ts_iv_key(struct debug_device *dev)
{
	struct debug_params *p = &dev->params;
	struct te_crypto_config *cfg = &p->cfg;
	struct te_crypto_ctx *ctx = dev->ctx;

	if (p->log_level > 2) {
		if (cfg->blk != TE_CRYPTO_BLK_ECB) {
			log_noti("EVEN IV\n");
			te_hex_dump(p->iv[EVEN_IDX], p->iv_size, 1);
			log_noti("ODD IV\n");
			te_hex_dump(p->iv[ODD_IDX], p->iv_size, 1);
		}
		log_noti("EVEN KEY\n");
		te_hex_dump(p->key[EVEN_IDX], cfg->key_size, 1);
		log_noti("ODD KEY\n");
		te_hex_dump(p->key[ODD_IDX], cfg->key_size, 1);
	}

	te_crypto_set_iv_key(ctx, TE_CRYPTO_EVEN_KEY, p->key[EVEN_IDX],
			     cfg->key_size);
	te_crypto_set_iv_key(ctx, TE_CRYPTO_ODD_KEY, p->key[ODD_IDX],
			     cfg->key_size);
	if (cfg->blk != TE_CRYPTO_BLK_ECB) {
		te_crypto_set_iv_key(ctx, TE_CRYPTO_EVEN_IV, p->iv[EVEN_IDX],
				     p->iv_size);
		te_crypto_set_iv_key(ctx, TE_CRYPTO_ODD_IV, p->iv[ODD_IDX],
				     p->iv_size);
	}
}

static int debug_output_open(struct inode *inode, struct file *file)
{
	int ret;
	struct debug_device *dev;
	struct debug_params *params;
	struct te_debug_item *item = te_debug_get_inode_private(inode);
	struct te_crypto_device *cdev = item->private;

	mutex_lock(&debug_mutex);
	dev = debug_get_device();
	if (dev) {
		ret = -EBUSY;
		goto err_busy;
	}

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev) {
		ret = -ENOMEM;
		goto err_malloc;
	}

	params = &dev->params;
	memcpy(params, &__debug_params, sizeof(*params));

	switch (params->cfg.fmt) {
	case TE_CRYPTO_FMT_TS_188:
		dev->align_size = 188;
		break;
	case TE_CRYPTO_FMT_TS_192:
		dev->align_size = 192;
		break;
	case TE_CRYPTO_FMT_DATA:
	default:
		if (params->cfg.type == TE_CRYPTO_MULTI2) {
			ret = -EINVAL;
			goto err_param;
		} else if (params->cfg.type == TE_CRYPTO_BYPASS) {
			dev->align_size = 4;
		} else {
			if ((params->cfg.key_size == 0) ||
			    (params->cfg.key_size % 4) != 0) {
				ret = -EINVAL;
				goto err_param;
			}

			if (params->cfg.type == TE_CRYPTO_AES)
				dev->align_size = AES_IV_SIZE;
			else
				dev->align_size = DES_IV_SIZE; // DES & TDES
		}
		break;
	}

	ret = debug_init_buffer(dev);
	if (ret) {
		goto err_buffer;
	}

	dev->ctx = te_crypto_open_from_device(cdev, params->idx);
	if (IS_ERR(dev->ctx)) {
		ret = PTR_ERR(dev->ctx);
		goto err_open;
	}

	ret = te_crypto_set_config(dev->ctx, &params->cfg);
	if (ret)
		goto err_cfg;

	te_crypto_set_timeout(dev->ctx, params->timeout);

	if (params->cfg.fmt == TE_CRYPTO_FMT_DATA) {
		debug_set_data_iv_key(dev);
	} else if (params->cfg.type == TE_CRYPTO_MULTI2) {
		debug_set_multi2_iv_key(dev);
	} else {
		debug_set_ts_iv_key(dev);
	}

	dev->output_state = DEBUG_STATE_GO;
	dev->input_state = DEBUG_STATE_IDLE;
	init_waitqueue_head(&dev->wq);

	dev->msg_jiffies = jiffies + DEBUG_MSG_INTERVAL;
	dev->processed_size = 0;

	dev->thread = kthread_run(debug_thread, dev, "dsc_debug");
	if (IS_ERR(dev->thread)) {
		log_error("can't create kthread\n");
		ret = PTR_ERR(dev->thread);
		goto err_thread;
	}

	debug_set_device(dev);

	file->private_data = dev;

	mutex_unlock(&debug_mutex);

	return 0;

err_thread:
err_cfg:
	te_crypto_close(dev->ctx);
err_open:
	debug_release_buffer(dev);
err_buffer:
err_param:
	kfree(dev);
err_malloc:
err_busy:
	mutex_unlock(&debug_mutex);

	return ret;
}

static int debug_output_release(struct inode *inode, struct file *file)
{
	struct debug_device *dev = file->private_data;

	mutex_lock(&debug_mutex);
	dev->output_state = DEBUG_STATE_DONE;
	if (dev->input_state == DEBUG_STATE_GO) {
		te_ringbuf_set_error(&dev->buf.in, -ECANCELED);
	}
	mutex_unlock(&debug_mutex);

	wait_event(dev->wq, READ_ONCE(dev->input_state) != DEBUG_STATE_GO);

	mutex_lock(&debug_mutex);
	kthread_stop(dev->thread);
	te_crypto_close(dev->ctx);
	debug_release_buffer(dev);
	debug_set_device(NULL);
	mutex_unlock(&debug_mutex);

	kfree(dev);

	return 0;
}

static ssize_t debug_output_read(struct file *file, char __user *data,
				 size_t size, loff_t *off)
{
	int ret;
	struct debug_device *dev = file->private_data;
	struct te_ringbuf *rbuf = &dev->buf.out;

	ret = te_ringbuf_io_read(rbuf, data, size, file->f_flags & O_NONBLOCK);
	if (ret > 0)
		dev->rdsize += ret;
	else if (ret == -EIO) {
		int err = te_ringbuf_error(rbuf);
		if (err == -ESHUTDOWN) {
			ret = 0;
		} else {
			ret = err;
		}
	}

	return ret;
}

static int debug_input_open(struct inode *inode, struct file *file)
{
	int ret;
	struct debug_device *dev;

	mutex_lock(&debug_mutex);
	dev = debug_get_device();
	/* To open input device, output device must be opened first  */
	if (!dev || dev->output_state != DEBUG_STATE_GO) {
		ret = -ENODEV;
	} else {
		if (dev->input_state != DEBUG_STATE_IDLE) {
			ret = -EBUSY;
		} else {
			dev->input_state = DEBUG_STATE_GO;
			file->private_data = dev;
			ret = 0;
		}
	}
	mutex_unlock(&debug_mutex);

	return ret;
}

static int debug_input_release(struct inode *inode, struct file *file)
{
	struct debug_device *dev = debug_get_device();

	mutex_lock(&debug_mutex);
	dev->input_state = DEBUG_STATE_DONE;
	if (dev->output_state == DEBUG_STATE_DONE)
		wake_up(&dev->wq);
	mutex_unlock(&debug_mutex);

	return 0;
}

static ssize_t debug_input_write(struct file *file, const char __user *data,
				 size_t size, loff_t *off)
{
	int ret;
	struct debug_device *dev = debug_get_device();
	struct te_ringbuf *buf = &dev->buf.in;

	ret = te_ringbuf_io_write(buf, data, size, file->f_flags & O_NONBLOCK);
	if (ret == -EIO) {
		ret = te_ringbuf_error(buf);
	}

	return ret;
}

static int debug_show(struct te_debug_item *item, struct seq_file *m)
{
	struct debug_params *params = &__debug_params;
	struct te_crypto_config *cfg;

	switch (item->flags) {
	case DEBUG_ID_CONFIG:
		cfg = &params->cfg;
		dprintf_str("mode", te_crypto_mode_to_str(params->mode));
		dprintf_str("format", te_crypto_format_to_str(cfg->fmt));
		dprintf_str("crypto", te_crypto_type_to_str(cfg->type));
		dprintf_str("blk mode", te_crypto_blk_to_str(cfg->blk));
		dprintf_str("res mode", te_crypto_res_to_str(cfg->res));
		dprintf("key_size:%d\n", cfg->key_size);
		dprintf("iv_size:%d\n", params->iv_size);
		dprintf_str("tsc", debug_tsc_to_str(params->tsc));
		break;

	default:
		return -EPERM;
	}

	return 0;
}

static int debug_get_config_iv_key(struct te_debug_param *p, const char *item,
				   u8 *v, int max_size)
{
	int i, rc;
	int arr[64];

	rc = te_debug_param_get_num_array(p, item, arr, max_size, 0);
	for (i = 0; i < rc; i++)
		v[i] = arr[i];

	return rc;
}

static int debug_get_config_iv(struct te_debug_param *p, const char *item,
			       u8 *iv)
{
	return debug_get_config_iv_key(p, item, iv, MAX_IV_SIZE);
}

static int debug_get_config_key(struct te_debug_param *p, const char *item,
				u8 *key)
{
	return debug_get_config_iv_key(p, item, key, MAX_KEY_SIZE);
}

static int debug_set_config(const char *path, struct debug_params *params)
{
	struct te_debug_param *p;
	int rc, v;
	const char *s;
	struct te_crypto_config *cfg = &params->cfg;

	p = te_debug_param_create(path);
	if (IS_ERR(p)) {
		log_error("can't create param '%s'", path);
		return PTR_ERR(p);
	}

	//te_debug_param_display(p);

	rc = te_debug_param_get_num(p, "scramble", &v, 0);
	if (!rc) {
		params->mode = v ? TE_CRYPTO_ENCRYPTION : TE_CRYPTO_DECRYPTION;
	}

	s = te_debug_param_get_str(p, "tsc");
	if (s) {
		params->tsc = str_to_debug_tsc(s);
	}

	s = te_debug_param_get_str(p, "format");
	if (s) {
		cfg->fmt = te_str_to_crypto_format(s);
	}

	s = te_debug_param_get_str(p, "cas");
	if (s) {
		cfg->type = te_str_to_crypto_type(s);
	}

	s = te_debug_param_get_str(p, "blk");
	if (s) {
		cfg->blk = te_str_to_crypto_blk(s);
	}

	s = te_debug_param_get_str(p, "res");
	if (s) {
		cfg->res = te_str_to_crypto_res(s);
	}

	rc = te_debug_param_get_num(p, "key_size", &v, 0);
	if (!rc)
		cfg->key_size = v;

	rc = te_debug_param_get_num(p, "iv_size", &v, 0);
	if (!rc)
		params->iv_size = v;

	if (cfg->fmt == TE_CRYPTO_FMT_DATA) {
		debug_get_config_iv(p, "iv", params->iv[0]);
		debug_get_config_key(p, "key", params->key[0]);
	} else {
		debug_get_config_key(p, "odd_key", params->key[ODD_IDX]);
		debug_get_config_key(p, "even_key", params->key[EVEN_IDX]);

		debug_get_config_iv(p, "odd_iv", params->iv[ODD_IDX]);
		debug_get_config_iv(p, "even_iv", params->iv[EVEN_IDX]);

		debug_get_config_key(p, "sys_key", params->sys_key);
	}

	te_debug_param_destory(p);

	return 0;
}

static int debug_write(struct te_debug_item *item, char *str)
{
	struct debug_params *params = &__debug_params;
	int ret = 0;

	mutex_lock(&debug_mutex);

	switch (item->flags) {
	case DEBUG_ID_CONFIG:
		ret = debug_set_config(str, params);
		break;

	default:
		ret = -EPERM;
		break;
	}

	mutex_unlock(&debug_mutex);

	return ret;
}

static const struct te_debug_simple_ops debug_ops = {
	.show = debug_show,
	.write = debug_write,
};

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,11,0)
static const struct proc_ops input_fops = {
	.proc_open = debug_input_open,
	.proc_write = debug_input_write,
	.proc_release = debug_input_release,
};

static const struct proc_ops output_fops = {
	.proc_open = debug_output_open,
	.proc_read = debug_output_read,
	.proc_release = debug_output_release,
};
#else
static const struct file_operations input_fops = {
	.open = debug_input_open,
	.write = debug_input_write,
	.release = debug_input_release,
};

static const struct file_operations output_fops = {
	.open = debug_output_open,
	.read = debug_output_read,
	.release = debug_output_release,
};
#endif

static const struct te_debug_item_info debug_list[] = {
	DBGITM_SIM("config", &debug_ops, DEBUG_ID_CONFIG),
	DBGITM_FOPS("input", &input_fops, 0),
	DBGITM_FOPS("output", &output_fops, 0),
	DBGITM_NUM("log_level", &__debug_params.log_level),
	DBGITM_STR("buf_name", __debug_params.buf_name),
	DBGITM_NUM("buf_size", &__debug_params.buf_size),
	DBGITM_NUM("buf_attr", &__debug_params.buf_attr),
	DBGITM_NUM("timeout", &__debug_params.timeout),
};

int crypto_debug_init(struct te_crypto_device *dev)
{
	int ret;
	struct te_device *tdev = get_te_device(dev);
	struct te_debug_dir *parent = te_get_debug_dir(tdev);

	dev->debug.dir = te_debug_create_dir("crypto", parent);
	CHECK_ERROR(!dev->debug.dir, return -EIO, "te_debug_create_dir failed");

	ret = debug_create_item_files(debug_list, dev, dev->debug.dir);
	CHECK_ERROR(ret, return ret, "debug_create_item_files failed");

	return 0;
}
/** @} */
