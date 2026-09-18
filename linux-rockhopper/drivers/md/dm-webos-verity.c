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

#include <linux/buffer_head.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/device-mapper.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/fcntl.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mount.h>
#include <linux/of.h>
#include <linux/reboot.h>
#include <linux/string.h>
#include <linux/vmalloc.h>
#include <linux/syscore_ops.h>
#include <linux/kmsg_dump.h>

#include "dm.h"
#include "dm-verity.h"
#include "dm-webos-verity.h"
#ifdef CONFIG_DM_VERITY_VERIFY_ROOTHASH_SIG
#include "dm-verity-verify-sig.h"
#endif

static void kernel_restart_dmverity(char *cmd)
{
	kernel_restart_prepare(cmd);
	migrate_to_reboot_cpu();
	syscore_shutdown();
	if (!cmd)
		pr_emerg("Restarting system(dmverity)\n");
	else
		pr_emerg("Restarting system with command '%s'\n", cmd);
	kmsg_dump(KMSG_DUMP_DMVERITY);
	machine_restart(cmd);
}

void dm_webos_verity_error_handle(enum dm_webos_error_type error_type,
				struct mapped_device *md)
{
	if (error_type == DM_VERITY_SIGNATURE_FAILURE) {
		DMERR("triggering restart");
		kernel_restart_dmverity("dm-verity device corrupted");
	}
}

static int webos_verity_ctr(struct dm_target *ti, unsigned argc, char **argv);
static int verity_clear_validated_blocks(struct dm_target *ti);

static struct target_type webos_verity_target = {
	.name                   = "webos-verity",
	.version                = {1, 0, 0},
	.module                 = THIS_MODULE,
	.ctr                    = webos_verity_ctr,
	.dtr                    = verity_dtr,
	.map                    = verity_map,
	.status                 = verity_status,
	.prepare_ioctl          = verity_prepare_ioctl,
	.iterate_devices        = verity_iterate_devices,
	.io_hints               = verity_io_hints,
	.clear_validated_blocks = verity_clear_validated_blocks,
};

static int verity_clear_validated_blocks(struct dm_target *ti)
{
	struct dm_verity *v = ti->private;

	/* the bitset can only handle INT_MAX blocks */
	if (v->data_blocks > INT_MAX) {
		ti->error = "device too large to use check_at_most_once";
		return -E2BIG;
	}

	if (!v->validated_blocks) {
		ti->error = "failed to free bitset for check_at_most_once";
		return -ENOMEM;
	}

	kvfree(v->validated_blocks);
	v->validated_blocks = 0;
	v->validated_blocks = kvcalloc(BITS_TO_LONGS(v->data_blocks),
			sizeof(unsigned long),
			GFP_KERNEL);
	if (!v->validated_blocks) {
		ti->error = "failed to allocate bitset for check_at_most_once";
		return -ENOMEM;
	}

	DMINFO("cleared validated_blocks");
	return 0;
}

static int read_block_dev(struct bio_read *payload, struct block_device *bdev,
		sector_t offset, int length)
{
	struct bio *bio;
	int err = 0, i;

	payload->number_of_pages = DIV_ROUND_UP(length, PAGE_SIZE);
	bio = bio_alloc(bdev, payload->number_of_pages, REQ_OP_READ | REQ_META | REQ_PRIO, GFP_KERNEL);
	if (!bio) {
		DMERR("Error while allocating bio");
		return -ENOMEM;
	}

	bio_set_dev(bio, bdev);
	bio->bi_iter.bi_sector = offset;
	bio->bi_opf = REQ_OP_READ;

	payload->page_io = kcalloc(payload->number_of_pages,
		sizeof(struct page *), GFP_KERNEL);
	if (!payload->page_io) {
		DMERR("page_io array alloc failed");
		err = -ENOMEM;
		goto free_bio;
	}

	for (i = 0; i < payload->number_of_pages; i++) {
		payload->page_io[i] = alloc_page(GFP_KERNEL);
		if (!payload->page_io[i]) {
			DMERR("alloc_page failed");
			err = -ENOMEM;
			goto free_pages;
		}
		if (!bio_add_page(bio, payload->page_io[i], PAGE_SIZE, 0)) {
			DMERR("bio_add_page error");
			err = -EIO;
			goto free_pages;
		}
	}

	if (!submit_bio_wait(bio))
		/* success */
		goto free_bio;
	DMERR("bio read failed");
	err = -EIO;

free_pages:
	for (i = 0; i < payload->number_of_pages; i++)
		if (payload->page_io[i])
			__free_page(payload->page_io[i]);
	kfree(payload->page_io);
free_bio:
	bio_put(bio);
	return err;
}

static inline u64 fec_div_round_up(u64 x, u64 y)
{
	u64 remainder;

	return div64_u64_rem(x, y, &remainder) +
		(remainder > 0 ? 1 : 0);
}

static inline void populate_fec_metadata(struct fec_header *header,
				struct fec_ecc_metadata *ecc)
{
	ecc->blocks = fec_div_round_up(le64_to_cpu(header->inp_size),
			FEC_BLOCK_SIZE);
	ecc->roots = le32_to_cpu(header->roots);
	ecc->start = le64_to_cpu(header->inp_size) + VERITY_METADATA_SIZE;
}

static inline int validate_fec_header(struct fec_header *header, u64 offset)
{
	/* move offset to make the sanity check work for backup header
	 * as well.
	 */
	offset -= offset % FEC_BLOCK_SIZE;
	if (le32_to_cpu(header->magic) != FEC_MAGIC ||
		le32_to_cpu(header->version) != FEC_VERSION ||
		le32_to_cpu(header->size) != sizeof(struct fec_header) ||
		le32_to_cpu(header->roots) == 0 ||
		le32_to_cpu(header->roots) >= FEC_RSM)
		return -EINVAL;

	return 0;
}

static int extract_fec_header(dev_t dev, struct fec_header *fec,
				struct fec_ecc_metadata *ecc)
{
	u64 device_size;
	struct bio_read payload;
	int i, err = 0;
	struct file *bdev_file;
	struct block_device *bdev;

	bdev_file = bdev_file_open_by_dev(dev, BLK_OPEN_READ, NULL, NULL);

	if (IS_ERR_OR_NULL(bdev_file)) {
		DMERR("bdev get error");
		return PTR_ERR(bdev_file);
	}
	bdev = file_bdev(bdev_file);

	device_size = bdev_nr_bytes(bdev);

	/* fec metadata size is a power of 2 and PAGE_SIZE
	 * is a power of 2 as well.
	 */
	BUG_ON(FEC_BLOCK_SIZE > PAGE_SIZE);
	/* 512 byte sector alignment */
	BUG_ON(((device_size - FEC_BLOCK_SIZE) % (1 << SECTOR_SHIFT)) != 0);

	err = read_block_dev(&payload, bdev, (device_size -
		FEC_BLOCK_SIZE) / (1 << SECTOR_SHIFT), FEC_BLOCK_SIZE);
	if (err) {
		DMERR("Error while reading verity metadata");
		goto error;
	}

	BUG_ON(sizeof(struct fec_header) > PAGE_SIZE);
	memcpy(fec, page_address(payload.page_io[0]),
			sizeof(*fec));

	ecc->valid = true;
	if (validate_fec_header(fec, device_size - FEC_BLOCK_SIZE)) {
		/* Try the backup header */
		memcpy(fec, page_address(payload.page_io[0]) + FEC_BLOCK_SIZE
			- sizeof(*fec),
			sizeof(*fec));
		if (validate_fec_header(fec, device_size -
			sizeof(struct fec_header))) {
			ecc->valid = false;
			DMERR("ecc is not valid. Forgot to turn on CONFIG_DM_VERITY_FEC?");
			err = -EINVAL;
		}
	}

	if (ecc->valid)
		populate_fec_metadata(fec, ecc);

	for (i = 0; i < payload.number_of_pages; i++)
		__free_page(payload.page_io[i]);
	kfree(payload.page_io);

error:
	fput(bdev_file);
	return err;
}

static void find_metadata_offset(struct fec_header *fec,
		struct block_device *bdev, u64 *metadata_offset)
{
	u64 device_size;

	device_size = bdev_nr_bytes(bdev);

	if (le32_to_cpu(fec->magic) == FEC_MAGIC)
		*metadata_offset = le64_to_cpu(fec->inp_size);
	else
		*metadata_offset = device_size - VERITY_METADATA_SIZE;
}

static int verify_header(struct webos_metadata_header *header)
{
	int retval = -EINVAL;

	if (!(le32_to_cpu(header->magic_number) ==
			VERITY_METADATA_MAGIC_NUMBER)) {
		DMERR("Incorrect magic number");
		return retval;
	}

	if (le32_to_cpu(header->protocol_version) !=
			VERITY_METADATA_VERSION) {
		DMERR("Unsupported version %u",
			le32_to_cpu(header->protocol_version));
		return retval;
	}

	return 0;
}

static int extract_metadata(dev_t dev, struct fec_header *fec,
				struct webos_metadata **metadata)
{
	struct file *bdev_file;
	struct block_device *bdev;
	struct webos_metadata_header *header;
	int i;
	u32 table_length, signature_length, copy_length, offset;
	u64 metadata_offset;
	struct bio_read payload;
	int err = 0;

	bdev_file = bdev_file_open_by_dev(dev, BLK_OPEN_READ, NULL, NULL);

	if (IS_ERR_OR_NULL(bdev_file)) {
		DMERR("blkdev_get_by_dev failed");
		return -ENODEV;
	}

	bdev = file_bdev(bdev_file);

	find_metadata_offset(fec, bdev, &metadata_offset);

	/* Verity metadata size is a power of 2 and PAGE_SIZE
	 * is a power of 2 as well.
	 * PAGE_SIZE is also a multiple of 512 bytes.
	 */
	if (VERITY_METADATA_SIZE > PAGE_SIZE)
		BUG_ON(VERITY_METADATA_SIZE % PAGE_SIZE != 0);
	/* 512 byte sector alignment */
	BUG_ON(metadata_offset % (1 << SECTOR_SHIFT) != 0);

	err = read_block_dev(&payload, bdev, metadata_offset /
		(1 << SECTOR_SHIFT), VERITY_METADATA_SIZE);
	if (err) {
		DMERR("Error while reading verity metadata");
		goto blkdev_release;
	}

	header = kzalloc(sizeof(*header), GFP_KERNEL);
	if (!header) {
		DMERR("kzalloc failed for header");
		err = -ENOMEM;
		goto free_payload;
	}

	memcpy(header, page_address(payload.page_io[0]),
		sizeof(*header));

	DMINFO("bio magic_number:%u protocol_version:%d table_length:%u, signature_length:%u",
		le32_to_cpu(header->magic_number),
		le32_to_cpu(header->protocol_version),
		le32_to_cpu(header->table_length),
		le32_to_cpu(header->signature_length));

	err = verify_header(header);

	if (err)
		goto free_header;

	*metadata = kzalloc(sizeof(**metadata), GFP_KERNEL);
	if (!*metadata) {
		DMERR("kzalloc for metadata failed");
		err = -ENOMEM;
		goto free_header;
	}

	(*metadata)->header = header;
	table_length = le32_to_cpu(header->table_length);

	if (table_length == 0 ||
		table_length > (VERITY_METADATA_SIZE -
			sizeof(struct webos_metadata_header))) {
		DMERR("table_length too long");
		err = -EINVAL;
		goto free_metadata;
	}

	(*metadata)->verity_table = kzalloc(table_length + 1, GFP_KERNEL);

	if (!(*metadata)->verity_table) {
		DMERR("kzalloc verity_table failed");
		err = -ENOMEM;
		goto free_metadata;
	}

	if (sizeof(struct webos_metadata_header) +
			table_length <= PAGE_SIZE) {
		memcpy((*metadata)->verity_table,
			page_address(payload.page_io[0])
			+ sizeof(struct webos_metadata_header),
			table_length);
	} else {
		u32 tmp_table_length = table_length;

		copy_length = PAGE_SIZE -
			sizeof(struct webos_metadata_header);
		memcpy((*metadata)->verity_table,
			page_address(payload.page_io[0])
			+ sizeof(struct webos_metadata_header),
			copy_length);
		tmp_table_length -= copy_length;
		offset = copy_length;
		i = 1;
		while (tmp_table_length != 0) {
			if (tmp_table_length > PAGE_SIZE) {
				memcpy((*metadata)->verity_table + offset,
					page_address(payload.page_io[i]),
					PAGE_SIZE);
				offset += PAGE_SIZE;
				tmp_table_length -= PAGE_SIZE;
			} else {
				memcpy((*metadata)->verity_table + offset,
					page_address(payload.page_io[i]),
					tmp_table_length);
				tmp_table_length = 0;
			}
			i++;
		}
	}
	(*metadata)->verity_table[table_length] = '\0';

	DMINFO("verity_table: %s", (*metadata)->verity_table);

	signature_length = le32_to_cpu(header->signature_length);

	if (signature_length == 0 ||
		table_length > (VERITY_METADATA_SIZE -
			sizeof(struct webos_metadata_header))) {
		DMERR("signature_length too long");
		err = -EINVAL;
		goto free_metadata;
	}

	(*metadata)->signature = kzalloc(signature_length + 1, GFP_KERNEL);

	if (!(*metadata)->signature) {
		DMERR("kzalloc signature failed");
		err = -ENOMEM;
		goto free_veritytable;
	}

	if (sizeof(struct webos_metadata_header) +
			table_length + signature_length <= PAGE_SIZE) {
		memcpy((*metadata)->signature,
			page_address(payload.page_io[0])
			+ sizeof(struct webos_metadata_header) + table_length,
			signature_length);
	} else {
		if (sizeof(struct webos_metadata_header) + table_length
								<= PAGE_SIZE) {
			u32 tmp_signature_length = signature_length;

			copy_length = PAGE_SIZE
				- (sizeof(struct webos_metadata_header)
				+ table_length);

			memcpy((*metadata)->signature,
					page_address(payload.page_io[0])
					+ sizeof(struct webos_metadata_header)
					+ table_length,
					copy_length);
			tmp_signature_length -= copy_length;
			offset = copy_length;
			i = 1;
			while (tmp_signature_length != 0) {
				if (tmp_signature_length > PAGE_SIZE) {
					memcpy((*metadata)->signature + offset,
						page_address(payload.page_io[i]),
						PAGE_SIZE);
					offset += PAGE_SIZE;
					tmp_signature_length -= PAGE_SIZE;
				} else {
					memcpy((*metadata)->signature + offset,
						page_address(payload.page_io[i]),
						tmp_signature_length);
					tmp_signature_length = 0;
				}
				i++;
			}
		} else {
			u32 page_cnt =
				(sizeof(struct webos_metadata_header) + table_length)
				/ PAGE_SIZE;
			u32 page_reminder =
				(sizeof(struct webos_metadata_header)
				+ table_length) % PAGE_SIZE;
			u32 tmp_signature_length = signature_length;

			copy_length = PAGE_SIZE - page_reminder;
			memcpy((*metadata)->signature,
					page_address(payload.page_io[page_cnt])
					+ page_reminder,
					copy_length);
			tmp_signature_length -= copy_length;
			offset = copy_length;
			i = 1;
			while (tmp_signature_length != 0) {
				if (tmp_signature_length > PAGE_SIZE) {
					memcpy((*metadata)->signature + offset,
						page_address(payload.page_io[page_cnt+i]),
						PAGE_SIZE);
					offset += PAGE_SIZE;
					tmp_signature_length -= PAGE_SIZE;
				} else {
					memcpy((*metadata)->signature + offset,
						page_address(payload.page_io[page_cnt+i]),
						tmp_signature_length);
					tmp_signature_length = 0;
				}
				i++;
			}
		}
	}
	(*metadata)->signature[signature_length] = '\0';

	goto free_payload;

free_veritytable:
	kfree((*metadata)->verity_table);
free_metadata:
	kfree(*metadata);
free_header:
	kfree(header);
free_payload:
	for (i = 0; i < payload.number_of_pages; i++)
		if (payload.page_io[i])
			__free_page(payload.page_io[i]);
	kfree(payload.page_io);
blkdev_release:
	fput(bdev_file);
	return err;
}

static void handle_error(int isRW)
{
	if (!isRW)
		dm_webos_verity_error_handle(DM_VERITY_SIGNATURE_FAILURE, NULL);
}

static inline bool test_mult_overflow(sector_t a, u32 b)
{
	sector_t r = (sector_t)~0ULL;

	sector_div(r, b);
	return a > r;
}

static int (*lookup_bdev_func)(const char *path, dev_t *dev);;
/*
 * Target parameters:
 *	<block device>	The block device for which dm-verity is being setup.
 */
static int webos_verity_ctr(struct dm_target *ti, unsigned argc, char **argv)
{
	dev_t dev;
	struct webos_metadata *metadata = NULL;
	int err = 0, i;
	char *table_ptr, dummy, *target_device;
	char *verity_table_args[VERITY_TABLE_ARGS + 3 + VERITY_TABLE_OPT_FEC_ARGS];
	sector_t data_sectors;
	u32 data_block_size;
	unsigned int no_of_args = VERITY_TABLE_ARGS + 3
				+ VERITY_TABLE_OPT_FEC_ARGS;
	struct fec_header fec;
	struct fec_ecc_metadata ecc;
	char buf[FEC_ARG_LENGTH], *buf_ptr;
	unsigned long long tmpll;
	char *webos_verity_opt = NULL;
	unsigned int webos_verity_mode = DM_VERITY_DEFAULT;
	int isRW = 0;

	if (argc == 1) {
		target_device = argv[0];
	} else if (argc == 2 && !strcmp("rw", argv[1])) {
		target_device = argv[0];
		isRW = 1;
	} else {
		DMERR("Incorrect number of arguments");
		handle_error(isRW);
		return -EINVAL;
	}

	if (system_state < SYSTEM_RUNNING && lookup_bdev_func)
		lookup_bdev_func(target_device, &dev);
	else
		lookup_bdev(target_device, &dev);
	if (!dev) {
		DMERR("no dev found for %s", target_device);
		handle_error(isRW);
		return -EINVAL;
	}

	DMINFO("dev:%s", target_device);

	if (extract_fec_header(dev, &fec, &ecc)) {
		DMERR("Error while extracting fec header");
		handle_error(isRW);
		return -EINVAL;
	}

	err = extract_metadata(dev, &fec, &metadata);

	if (err) {
		/* Allow invalid metadata when the device is unlocked */
		DMERR("Error while extracting metadata");
		handle_error(isRW);
		goto free_metadata;
	}

#ifdef CONFIG_DM_VERITY_VERIFY_ROOTHASH_SIG
	err =  verity_verify_root_hash((const void *)metadata->verity_table,
			le32_to_cpu(metadata->header->table_length),
			metadata->signature,
			le32_to_cpu(metadata->header->signature_length));

	if (err < 0) {
		DMERR("Signature verification failed");
		handle_error(isRW);
		goto free_metadata;
	} else
		DMINFO("Signature verification success");
#endif
	table_ptr = metadata->verity_table;

	for (i = 0; i < VERITY_TABLE_ARGS; i++) {
		verity_table_args[i] = strsep(&table_ptr, " ");
		if (verity_table_args[i] == NULL)
			break;
	}

	if (i != VERITY_TABLE_ARGS) {
		DMERR("Verity table not in the expected format");
		err = -EINVAL;
		handle_error(isRW);
		goto free_metadata;
	}

	webos_verity_opt = strsep(&table_ptr, " ");

	if (webos_verity_opt != NULL) {
		// rw verity
		if (sscanf(webos_verity_opt, "%u%c", &webos_verity_mode, &dummy)
				!= 1) {
			DMERR("Verity table not in the expected format");
			handle_error(isRW);
			err = -EINVAL;
			goto free_metadata;
		}

	}

	if (webos_verity_mode > DM_VERITY_RW) {
		DMERR("<webos_verity_mode(%u)> unknown mode.",
			webos_verity_mode);
		handle_error(isRW);
		err = -EINVAL;
		goto free_metadata;
	}
	DMINFO("webos_verity_mode : %u", webos_verity_mode);

	if (webos_verity_mode == DM_VERITY_RW)
		isRW = 1;
	else
		isRW = 0;

	if (sscanf(verity_table_args[5], "%llu%c", &tmpll, &dummy)
							!= 1) {
		DMERR("Verity table not in the expected format");
		handle_error(isRW);
		err = -EINVAL;
		goto free_metadata;
	}

	if (tmpll > ULONG_MAX) {
		DMERR("<num_data_blocks> too large. Forgot to turn on CONFIG_LBDAF?");
		handle_error(isRW);
		err = -EINVAL;
		goto free_metadata;
	}

	data_sectors = tmpll;

	if (sscanf(verity_table_args[3], "%u%c", &data_block_size, &dummy)
								!= 1) {
		DMERR("Verity table not in the expected format");
		handle_error(isRW);
		err = -EINVAL;
		goto free_metadata;
	}

	if (test_mult_overflow(data_sectors, data_block_size >>
							SECTOR_SHIFT)) {
		DMERR("data_sectors too large");
		handle_error(isRW);
		err = -EOVERFLOW;
		goto free_metadata;
	}

	data_sectors *= data_block_size >> SECTOR_SHIFT;
	DMINFO("Data sectors %llu", (unsigned long long)data_sectors);

	/* update target length */
	ti->len = data_sectors;

	/*substitute data_dev and hash_dev*/
	verity_table_args[1] = target_device;
	verity_table_args[2] = target_device;

	/*select a crypto driver instead of the default driver*/
	if (crypto_has_alg(VERITY_HASH_ALG, 0, 0)) {
            verity_table_args[7] = VERITY_HASH_ALG;
	}

	if (webos_verity_mode == DM_VERITY_RW) {
		err = snprintf(buf, FEC_ARG_LENGTH,
				"%u " VERITY_TABLE_OPT_FEC_FORMAT,
				VERITY_TABLE_OPT_FEC_ARGS,
				target_device,
				ecc.start / FEC_BLOCK_SIZE, ecc.blocks,
				ecc.roots);
	} else {
		err = snprintf(buf, FEC_ARG_LENGTH,
				"%u %s " VERITY_TABLE_OPT_FEC_FORMAT,
				1 + VERITY_TABLE_OPT_FEC_ARGS,
				VERITY_TABLE_OPT_AT_MOST_ONCE,
				target_device,
				ecc.start / FEC_BLOCK_SIZE, ecc.blocks,
				ecc.roots);
	}

	if (err < 0 || err >= FEC_ARG_LENGTH)
		goto free_metadata;

	buf_ptr = buf;

	for (i = VERITY_TABLE_ARGS; i < (VERITY_TABLE_ARGS +
		VERITY_TABLE_OPT_FEC_ARGS + 3); i++) {
		verity_table_args[i] = strsep(&buf_ptr, " ");
		if (verity_table_args[i] == NULL) {
			no_of_args = i;
			break;
		}
	}

	err = verity_ctr(ti, no_of_args, verity_table_args);
	if (err)
		DMERR("webos-verity failed to create a verity target");
	else
		DMINFO("webos-verity created as verity target");

free_metadata:
	if (metadata) {
		kfree(metadata->header);
		kfree(metadata->verity_table);
		kfree(metadata->signature);
	}
	kfree(metadata);
	return err;
}

static int __init dm_webos_verity_init(void)
{
	int r;

	r = dm_register_target(&webos_verity_target);
	if (r < 0)
		DMERR("register failed %d", r);

	lookup_bdev_func = early_lookup_bdev;
	return r;
}

static void __exit dm_webos_verity_exit(void)
{
	dm_unregister_target(&webos_verity_target);
	lookup_bdev_func = NULL;
}

module_init(dm_webos_verity_init);
module_exit(dm_webos_verity_exit);
