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
 *  TE crypto driver
 *
 *  @author	ks.hyun
 *  @version	1.0
 *  @date	2020.01.07
 *  @note
 */

#ifndef	_CRYPTO_IMPL_H_
#define	_CRYPTO_IMPL_H_

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/vmalloc.h>
#include <linux/delay.h>
#include <linux/kthread.h>

#include <lg1k/te/crypto.h>
#include <lg1k/te/debug.h>
#include <lg1k/te/buffer.h>
#include <lg1k/te/mem.h>

#include "logm_kapi.h"

//#define USE_CRYPTO_ASYNC_REQUEST

#define	CRYPTO_MODULE		"crypto"
#define CRYPTO_DEVICE_NAME	"lg1k-crypto"

#define LOG_LEVEL_ERROR		LX_LOGM_LEVEL_ERROR	/* 0 */
#define LOG_LEVEL_WARNING	LX_LOGM_LEVEL_WARNING	/* 1 */
#define LOG_LEVEL_NOTI		LX_LOGM_LEVEL_NOTI	/* 2 */
#define LOG_LEVEL_INFO		LX_LOGM_LEVEL_INFO	/* 3 */
#define LOG_LEVEL_DEBUG		LX_LOGM_LEVEL_DEBUG	/* 4 */
#define LOG_LEVEL_TRACE		LX_LOGM_LEVEL_TRACE	/* 5 */
#define LOG_LEVEL_TRACE_EX	LX_LOGM_LEVEL_TRACE + 1	/* 6 */

#define CRYPTO_LOG(type,fmt,args...) \
	LOGM_PRINT( g_crypto_logm_fd, (LOG_LEVEL_##type), fmt, ##args)

#define log_error(fmt,args...)		CRYPTO_LOG(ERROR,fmt,##args)
#define log_warning(fmt,args...)	CRYPTO_LOG(WARNING,fmt,##args)
#define log_noti(fmt,args...)		CRYPTO_LOG(NOTI,fmt,##args)
#define log_info(fmt,args...)		CRYPTO_LOG(INFO,fmt,##args)
#define log_debug(fmt,args...)		CRYPTO_LOG(DEBUG,fmt,##args)
#define log_trace(fmt,args...)		CRYPTO_LOG(TRACE,fmt,##args)
#define log_trace_ex(fmt,args...)	CRYPTO_LOG(TRACE_EX,fmt,##args)

#define CHECK_ERROR(__checker,__if_action,fmt,args...)   \
	TE_CHECK_IF_ERROR(__checker, log_error, __if_action , fmt, ##args )

#define CHECK_RET_EINVAL(__checker, fmt, args...) \
	CHECK_ERROR(__checker, return -EINVAL, fmt, ##args)

#define CHECK_NULL_PARAM(param) \
	CHECK_RET_EINVAL(!(param), "parameter(" #param ") is null")

#define CHECK_PARAM(__checker,fmt,args...) \
	CHECK_RET_EINVAL(__checker, "invalid parameter : " fmt, ##args)

#define EVEN_IDX 0
#define ODD_IDX 1

#define MAX_IV_SIZE 16
#define MAX_KEY_SIZE 32

#define AES_IV_SIZE 16

#define DES_IV_SIZE 8
#define DES_KEY_SIZE 8

#define TDES_IV_SIZE 8
#define TDES_KEY_SIZE 24

#define MULTI2_IV_SIZE 8
#define MULTI2_DKEY_SIZE 8
#define MULTI2_SKEY_SIZE 32

enum crypto_flags {
	CRYPTO_FLAGS_BUSY = 0,
	CRYPTO_FLAGS_DONE,
	CRYPTO_FLAGS_CANCEL,
};

struct crypto_dev_request {
	struct te_crypto_ctx *ctx;
	enum te_crypto_mode mode;
	struct te_crypto_data *data;
	enum te_crypto_tsc tsc;

	off_t offset;
	unsigned long flags;

	phys_addr_t in;
	phys_addr_t out;
	size_t size;

#ifdef USE_CRYPTO_ASYNC_REQUEST
	int res;
	te_crypto_callback_t async_callback;
	struct work_struct async_work;
	struct te_crypto_data __data; // save for async request
#endif
	u8 next_iv[MAX_IV_SIZE];

	wait_queue_head_t wq;
	struct list_head list; // list entry in struct crypto_dev_queue::reqs
};

struct crypto_dev_queue {
	/* list of all struct crypto_dev_request */
	struct list_head reqs;
	u32 len;
};

struct crypto_request_param {
	enum te_crypto_mode mode;
	struct te_crypto_data *data;
	enum te_crypto_tsc tsc; // only used for TS encryption
#ifdef USE_CRYPTO_ASYNC_REQUEST
	te_crypto_callback_t async_callback;
#endif
};

struct crypto_buffer {
	void *vaddr;
	phys_addr_t paddr;
	u32 size;
};

struct crypto_debug {
	struct te_debug_dir *dir;
};

struct te_crypto_channel {
	u8 num;
	u8 dsc_idx;
	char name[16];
	struct mutex mutex;
	u32 intr_mask;
	struct te_mem_ctx *mem_ctx;
	struct crypto_buffer buf;

	bool done;
	struct crypto_dev_request *req; // current request
	struct crypto_dev_queue queue;
#ifdef USE_CRYPTO_ASYNC_REQUEST
	struct work_struct done_work;
#else
	wait_queue_head_t wq;
#endif
	atomic_t refcount;
};

struct te_crypto_device {
	struct cdev cdev;
	struct te_subdev subdev;
	struct crypto_debug debug;

	u8 num_channel;
	struct te_crypto_channel channels[0];
};

enum crypto_state {
	CRYPTO_STATE_IDLE = 0,
	CRYPTO_STATE_INIT,
	CRYPTO_STATE_GO,
	CRYPTO_STATE_DONE,
};

union crypto_set {
	struct {
		u8 iv[MAX_IV_SIZE];
		u8 key[MAX_KEY_SIZE];
	} data;

	struct {
		u8 iv[2][MAX_IV_SIZE];
		u8 key[2][MAX_KEY_SIZE];
	} ts;

	struct {
		u8 iv[MULTI2_IV_SIZE];
		u8 skey[MULTI2_SKEY_SIZE];
		u8 dkey[2][MULTI2_DKEY_SIZE];
	} multi2;
};

struct te_crypto_ctx {
	enum crypto_state state;
	struct te_crypto_channel *channel;
	struct mutex mutex;
	struct te_crypto_config cfg;

	struct te_reg_dsc_config reg_cfg;
	enum te_reg_dsc_format reg_fmt;

	union crypto_set set;
	unsigned long timeout;
	u8 key_size;
	u8 iv_size;
	u32 align_size;

	struct crypto_dev_request req;
};

struct te_crypto_fh {
	struct te_crypto_ctx *ctx;
};

int crypto_device_init(struct te_crypto_device *dev);
void crypto_device_release(struct te_crypto_device *dev);
int crypto_device_suspend(struct te_crypto_device *dev);
int crypto_device_resume(struct te_crypto_device *dev);

int crypto_debug_init(struct te_crypto_device *dev);

extern const struct file_operations crypto_dev_fops;


#define te_subdev_to_crypto_device(sd) \
	container_of(sd, struct te_crypto_device, subdev)

#define get_te_device(dev) (dev->subdev.tdev)

extern int g_crypto_logm_fd;

#endif	/* _CRYPTO_IMPL_H_ */

/** @} */
