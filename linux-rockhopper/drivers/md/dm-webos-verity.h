/*
 * Copyright (C) 2021 LG Electronics, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef DM_WEBOS_VERITY_H
#define DM_WEBOS_VERITY_H

#include <crypto/sha1.h>
#include <crypto/sha2.h>

#define VERITY_METADATA_MAGIC_NUMBER 0xb001b001
#define VERITY_METADATA_VERSION 0
#define DATA_BLOCK_SIZE (4 * 1024)
#define VERITY_METADATA_SIZE (8 * DATA_BLOCK_SIZE)
#define VERITY_TABLE_ARGS 10

#define FEC_MAGIC 0xFECFECFE
#define FEC_BLOCK_SIZE (4 * 1024)
#define FEC_VERSION 0
#define FEC_RSM 255
#define FEC_ARG_LENGTH 300

#define VERITY_HASH_ALG "sha256-ce"

#define VERITY_TABLE_OPT_RESTART "restart_on_corruption"
#define VERITY_TABLE_OPT_LOGGING "ignore_corruption"
#define VERITY_TABLE_OPT_IGNZERO "ignore_zero_blocks"
#define VERITY_TABLE_OPT_AT_MOST_ONCE "check_at_most_once"

#define VERITY_TABLE_OPT_FEC_FORMAT \
	"use_fec_from_device %s fec_start %llu fec_blocks %llu fec_roots %u ignore_zero_blocks"
#define VERITY_TABLE_OPT_FEC_ARGS 9

#define VERITY_DEBUG 0

#define DM_MSG_PREFIX                   "webos-verity"

enum dm_webos_verity_type {
	DM_VERITY_DEFAULT,
	DM_VERITY_RO,
	DM_VERITY_RW,
};

/*
 * There can be two formats.
 * if fec is present
 * <data_blocks> <verity_tree> <verity_metdata_32K><fec_data><fec_data_4K>
 * if fec is not present
 * <data_blocks> <verity_tree> <verity_metdata_32K>
 */
struct fec_header {
	__le32 magic;
	__le32 version;
	__le32 size;
	__le32 roots;
	__le32 fec_size;
	__le64 inp_size;
	u8 hash[SHA256_DIGEST_SIZE];
} __attribute__((packed));

struct webos_metadata_header {
	__le32 magic_number;
	__le32 protocol_version;
	__le32 table_length;
	__le32 signature_length;
};

struct webos_metadata {
	struct webos_metadata_header *header;
	char *verity_table;
	char *signature;
};

struct fec_ecc_metadata {
	bool valid;
	u32 roots;
	u64 blocks;
	u64 rounds;
	u64 start;
};

struct bio_read {
	struct page **page_io;
	int number_of_pages;
};

#endif /* DM_WEBOS_VERITY_H */
