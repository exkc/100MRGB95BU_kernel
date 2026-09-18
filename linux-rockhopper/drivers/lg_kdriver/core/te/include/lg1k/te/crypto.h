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
 *  @date	2018-10-12
 *  @note	Additional information.
 */

#ifndef	_LG1K_TE_CRYPTO_H_
#define	_LG1K_TE_CRYPTO_H_

#include <lg1k/te/te.h>
#include "te_crypto_kapi.h"

struct te_crypto_device;
struct te_crypto_channel;
struct te_crypto_ctx;

enum te_crypto_addr_type {
	CRYPTO_ADDR_PHYS = 0,
	CRYPTO_ADDR_VIRT,
	CRYPTO_ADDR_USER,
};

struct te_crypto_data {
	enum te_crypto_addr_type type;
	union {
		struct {
			const void *in;
			void *out;
		} virt;

		struct {
			phys_addr_t in;
			phys_addr_t out;
		} phys;

		struct {
			const void __user *in;
			void __user *out;
		} user;
	};
	size_t size;
};

typedef void (*te_crypto_callback_t)(struct te_crypto_ctx *ctx, int err);

struct te_crypto_device *te_crypto_get_device(struct te_device *dev);
struct te_crypto_channel *te_crypto_get_channel(struct te_crypto_device *dev,
						u8 num);

struct te_crypto_ctx *te_crypto_open(struct te_crypto_channel *channel);
struct te_crypto_ctx *te_crypto_open_from_device(struct te_crypto_device *dev,
						 u8 num);

void te_crypto_close(struct te_crypto_ctx *ctx);
int te_crypto_cancel(struct te_crypto_ctx *ctx);
int te_crypto_set_timeout(struct te_crypto_ctx *ctx, unsigned long timeout);
int te_crypto_set_config(struct te_crypto_ctx *ctx,
			 struct te_crypto_config *cfg);
int te_crypto_set_iv_key(struct te_crypto_ctx *ctx,
			 enum te_crypto_set_type type,
			 const u8 *value, u8 size);

int te_crypto_decrypt(struct te_crypto_ctx *ctx, struct te_crypto_data *data);
int te_crypto_encrypt(struct te_crypto_ctx *ctx, struct te_crypto_data *data,
		      enum te_crypto_tsc tsc);

enum te_crypto_mode te_str_to_crypto_mode(const char *str);
const char *te_crypto_mode_to_str(enum te_crypto_mode mode);
enum te_crypto_fmt te_str_to_crypto_format(const char *str);
const char *te_crypto_format_to_str(enum te_crypto_fmt fmt);
enum te_crypto_type te_str_to_crypto_type(const char *str);
const char *te_crypto_type_to_str(enum te_crypto_type type);
enum te_crypto_blk te_str_to_crypto_blk(const char *str);
const char *te_crypto_blk_to_str(enum te_crypto_blk blk);
enum te_crypto_res te_str_to_crypto_res(const char *str);
const char *te_crypto_res_to_str(enum te_crypto_res res);

#endif /* _LG1K_TE_CRYPTO_H_ */

/** @} */
