/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2022 by LG Electronics Inc.
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
 *  mcu verification util
 *
 *  @author	Ilkyu Kim ( ilkyu.kim@lge.com)
 *  @version	1.0
 *  @date	2022-05-20
 *  @note	Additional information.
 */

#include <linux/version.h>
#include <linux/scatterlist.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#include <crypto/internal/akcipher.h>
#include <crypto/hash.h>
#include "te_mcu_verify_key.h"
#include "te_mcu_verify.h"
#include "te_impl.h"

#define SHA256_DIGEST_SIZE 32

/* Referenced from Algorithm testing framework and tests from kernel
 * linux/crypto/testmgr.c
 */
static struct akcipher_request *init_pubkey(struct crypto_akcipher **tfm,
					    const void *data, int len)
{
	struct akcipher_request *req;
	int rc;

	*tfm = crypto_alloc_akcipher("pkcs1pad(rsa,sha256)", 0, 0);
	if (IS_ERR(*tfm)) {
		rc = PTR_ERR(*tfm);
		log_error("fail to alloc akcipher; %d", rc);
		return ERR_PTR(rc);
	}

	req = akcipher_request_alloc(*tfm, GFP_KERNEL);
	if (!req) {
		log_error("fail to alloc akcipher_request");
		crypto_free_akcipher(*tfm);
		return ERR_PTR(-ENOMEM);
	}

	rc = crypto_akcipher_set_pub_key(*tfm, data, len);
	if (rc) {
		log_error("fail to set pub key; %d", rc);
		akcipher_request_free(req);
		crypto_free_akcipher(*tfm);
		return ERR_PTR(rc);
	}

	return req;
}

static void free_pubkey(struct crypto_akcipher *tfm, struct akcipher_request *req)
{
	if (req)
		akcipher_request_free(req);
	if (tfm)
		crypto_free_akcipher(tfm);
}

static void *generate_digest(const void *buf, unsigned int len)
{
	struct scatterlist src;
	struct crypto_ahash *tfm = NULL;
	struct ahash_request *req = NULL;
	u8 *output = NULL;
	int rc, maxlen;

	tfm = crypto_alloc_ahash("sha256", 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(tfm)) {
		rc = PTR_ERR(tfm);
		log_error("fail to alloc ahash; %d", rc);
		return ERR_PTR(rc);
	}

	sg_init_one(&src, buf, len);
	req = ahash_request_alloc(tfm, GFP_ATOMIC);
	if (IS_ERR(req)) {
		rc = PTR_ERR(req);
		log_error("fail to request ahash; %d", rc);
		crypto_free_ahash(tfm);
		return ERR_PTR(rc);
	}

	maxlen = crypto_ahash_digestsize(tfm);
	output = kzalloc(maxlen, GFP_KERNEL);

	if (!output) {
		log_error("fail to alloc hash output");
		ahash_request_free(req);
		crypto_free_ahash(tfm);
		return ERR_PTR(-ENOMEM);
	}

	ahash_request_set_callback(req, 0, NULL, NULL);
	ahash_request_set_crypt(req, &src, output, len);

	rc = crypto_ahash_digest(req);
	if (rc) {
		kfree(output);
		ahash_request_free(req);
		crypto_free_ahash(tfm);
		return ERR_PTR(rc);
	}

	crypto_free_ahash(tfm);
	ahash_request_free(req);

	return output;
}

int te_mcu_verify_mcu_binary(const void *data, u32 size)
{
	struct crypto_akcipher *tfm;
	struct akcipher_request *req;
	void *inbuf = NULL;
	void *hash = NULL;
	struct scatterlist src_tab[3];
	struct crypto_wait wait;
	const u32 siglen = MCU_SIGNATURE_LEN;
	size_t cipher_max_len;
	int rc;

	if (size <= siglen)
		return -EIO;

	hash = generate_digest(data, size - siglen);
	if (IS_ERR(hash))
		return PTR_ERR(hash);

	req = init_pubkey(&tfm, te_pk, sizeof(te_pk));
	if (IS_ERR(req)) {
		kfree(hash);
		return PTR_ERR(req);
	}

	cipher_max_len = crypto_akcipher_maxsize(tfm);

	inbuf = kzalloc(PAGE_SIZE, GFP_KERNEL);
	if (!inbuf) {
		log_error("fail to alloc inbuf");
		rc = -ENOMEM;
		goto fail;
	}

	memcpy(inbuf, data + size - siglen, siglen);
	sg_init_table(src_tab, 3);
	sg_set_buf(&src_tab[0], inbuf, 8);
	sg_set_buf(&src_tab[1], inbuf + 8, siglen - 8);
	sg_set_buf(&src_tab[2], hash, SHA256_DIGEST_SIZE);

	crypto_init_wait(&wait);
	akcipher_request_set_crypt(req, src_tab, NULL, siglen,
				   SHA256_DIGEST_SIZE);


	akcipher_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
			crypto_req_done, &wait);

	rc = crypto_wait_req(crypto_akcipher_verify(req), &wait);
	if (rc) {
		log_error("verification failed");
		goto fail;
	}

	log_noti("Signature verification successful");
	kfree(hash);
	kfree(inbuf);
	free_pubkey(tfm, req);

	return 0;

fail:
	if (hash)
		kfree(hash);
	if (inbuf)
		kfree(inbuf);
	free_pubkey(tfm, req);
	return rc;
}
#else
#include <asm/types.h>
#include <linux/errno.h>

int te_mcu_verify_mcu_binary(const void *data, u32 size)
{
	return -EPERM;
}
#endif
