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

/** @file te_crypto_kapi.h
 *
 *  Kernel driver for TE.
 *
 *  @author	Kyungseok Hyun ( ks.hyun@lge.com)
 *  @version	1.0
 *  @date	2015-01-05
 *  @note       Additional information.
 */

#ifndef	_TE_CRYPTO_KAPI_H_
#define	_TE_CRYPTO_KAPI_H_

#include "te_kapi.h"

#define	TE_CRYPTO_IOC_MAGIC	'c'

#define TE_CRYPTO_IOC_CONFIG	_IOW (TE_CRYPTO_IOC_MAGIC, 0, struct te_crypto_config)
#define TE_CRYPTO_IOC_SET	_IOW (TE_CRYPTO_IOC_MAGIC, 1, struct te_crypto_set)
#define TE_CRYPTO_IOC_MULTI_SET	_IOW (TE_CRYPTO_IOC_MAGIC, 2, struct te_crypto_user_multi_set)
#define TE_CRYPTO_IOC_REQUEST	_IOW (TE_CRYPTO_IOC_MAGIC, 3, struct te_crypto_user_request)

enum te_crypto_type {
	TE_CRYPTO_BYPASS = 0,
	TE_CRYPTO_AES,
	TE_CRYPTO_DES,
	TE_CRYPTO_TDES,
	TE_CRYPTO_MULTI2,
	TE_CRYPTO_MAX
};

enum te_crypto_blk {
	TE_CRYPTO_BLK_ECB = 0,
	TE_CRYPTO_BLK_CBC,
	TE_CRYPTO_BLK_CTR,
	TE_CRYPTO_BLK_MAX
};

enum te_crypto_res {
	TE_CRYPTO_RES_CLEAR = 0,
	TE_CRYPTO_RES_CTS,
	TE_CRYPTO_RES_OFB,
	TE_CRYPTO_RES_SCTE,
	TE_CRYPTO_RES_MAX
};

enum te_crypto_fmt {
	TE_CRYPTO_FMT_DATA = 0,
	TE_CRYPTO_FMT_TS_188,
	TE_CRYPTO_FMT_TS_192,
	TE_CRYPTO_FMT_MAX
};

enum te_crypto_set_type {
	TE_CRYPTO_IV = 0,
	TE_CRYPTO_KEY,
	/* MEPG2 TS */
	TE_CRYPTO_EVEN_IV,
	TE_CRYPTO_ODD_IV,
	TE_CRYPTO_EVEN_KEY,
	TE_CRYPTO_ODD_KEY,
	TE_CRYPTO_MULTI2_SKEY,
	TE_CRYPTO_MULTI2_IV,
};

enum te_crypto_mode {
	TE_CRYPTO_DECRYPTION = 0,
	TE_CRYPTO_ENCRYPTION,
};

/* transport scrambling control bit for MPEG TS */
enum te_crypto_tsc {
	TE_CRYPTO_TSC_EVEN = 0,
	TE_CRYPTO_TSC_ODD,
};

struct te_crypto_config {
	enum te_crypto_type type;
	enum te_crypto_blk blk;
	enum te_crypto_res res;
	enum te_crypto_fmt fmt;
	__u8 key_size; /* byte unit : only for AES */
};

struct te_crypto_set {
	enum te_crypto_set_type type;
	__u32 length;
	__u8 value[32];
};

struct te_crypto_user_multi_set {
	__u32 num;
	union {
		const struct te_crypto_set __user *set;
		TE_COMPAT_SIZER(set);
	};
};

struct te_crypto_user_request {
	enum te_crypto_mode mode;
	enum te_crypto_tsc tsc; /* only used for TS encryption */
	union {
		const void __user *in;
		TE_COMPAT_SIZER(in);
	};
	union {
		void __user *out;
		TE_COMPAT_SIZER(out);
	};
	__u32 nbytes;
};

#endif	/* _TE_CRYPTO_KAPI_H_ */
