// SPDX-License-Identifier: GPL-2.0-only
/*
 * kexec: init kexec_firmware_load
 *
 * Copyright (C) 2024 LG Electronics Inc.
 * Authors:
 *      Jaehyun Kim <jehn.kim@lge.com>
 */
#include <linux/module.h>
#include <linux/firmware.h>
#include <linux/kthread.h>
#include <linux/ima.h>
#include <linux/kexec.h>
#include <linux/vmalloc.h>
#include <linux/string.h>

#include "kexec_internal.h"

#define pr_fmt(fmt) "kdump: " fmt

static struct task_struct *kexec_fw_task;

static char kdump_args[100] __initdata =
	CONFIG_KEXEC_FIRMWARE_CMDLINE;

static char kdump_fw_name[256] = "";

static int __init parse_kdump_fw(char *str)
{
	if (!str)
		return -EINVAL;

	strncpy(kdump_fw_name, str, sizeof(kdump_fw_name) - 1);
	kdump_fw_name[sizeof(kdump_fw_name) - 1] = '\0';

	return 0;
}
early_param("kdump_fw", parse_kdump_fw);

/**
 * parse_kdumpargs - Parse additional kernel command line arguments for crash kernel
 * @str: Command line string from kdumpargs= boot parameter
 *
 * This function handles additional command line arguments that need to be passed
 * to the crash kernel. These arguments are appended to the base command line
 * defined in CONFIG_KEXEC_FIRMWARE_CMDLINE.
 *
 * Common use cases include:
 * - Additional kernel parameters specific to crash kernel environment
 * - FTP server configuration (e.g., "ftp=192.168.1.100:/path/to/dump")
 * - Network configuration for remote dump transfer
 * - Debug options for crash kernel
 *
 * Example usage:
 *   kdumpargs="ftp=id:pw@192.168.1.100:/vmcore loglevel=8 earlycon"
 *
 * Return: 0 on success, -EINVAL if str is NULL
 */
static int __init parse_kdumpargs(char *str)
{
	if (!str)
		return -EINVAL;

	strcat(kdump_args, str);

	return 0;
}
early_param("kdumpargs", parse_kdumpargs);

static const char *__init get_firmware_name(void)
{
	/* Use firmware name from boot cmdline if provided */
	if (kdump_fw_name[0] != '\0') {
		pr_info("Using firmware from cmdline: %s\n", kdump_fw_name);
		return kdump_fw_name;
	}

	/* Use default firmware name from config */
	pr_info("Using default firmware: %s\n", CONFIG_KEXEC_FIRMWARE_NAME);
	return CONFIG_KEXEC_FIRMWARE_NAME;
}

static int __init request_image(struct kimage *image)
{
	int ret;
	const struct firmware *fw;
	const char *fw_name = get_firmware_name();

	if (!fw_name) {
		pr_err("No firmware name available\n");
		return -EINVAL;
	}

	ret = request_firmware(&fw, fw_name, NULL);
	if ((ret < 0) || !fw)
		goto release;

	image->kernel_buf_len = fw->size;
	image->kernel_buf = vmalloc(fw->size);
	if (!image->kernel_buf) {
		ret = -ENOMEM;
		goto release;
	}

	memcpy(image->kernel_buf, fw->data, fw->size);

release:
	if (ret)
		pr_err("Failed to request %s firmware\n", fw_name);
	release_firmware(fw);
	return ret;
}

static int __init kimage_fw_prepare_segments(struct kimage *image,
					     unsigned flags)
{
	int ret;
	void *ldata;
	size_t cmdline_len;

	ret = request_image(image);
	if (ret)
		goto out;

	ret = kexec_image_probe_default(image, image->kernel_buf,
					image->kernel_buf_len);
	if (ret)
		goto out;

	cmdline_len = strlen(kdump_args) + 1;
	image->cmdline_buf = kmalloc(cmdline_len + 1, GFP_KERNEL);
	if (!image->cmdline_buf) {
		ret = -ENOMEM;
		goto out;
	}

	strncpy(image->cmdline_buf, kdump_args, cmdline_len);
	image->cmdline_buf_len = cmdline_len;

	/* command line should be a string with last byte null */
	if (image->cmdline_buf[cmdline_len - 1] != '\0') {
		ret = -EINVAL;
		goto out;
	}

	if (!image->fops || !image->fops->load) {
		ret = -ENOEXEC;
		goto out;
	}

	ldata = image->fops->load(image, image->kernel_buf,
				  image->kernel_buf_len, image->initrd_buf,
				  image->initrd_buf_len, image->cmdline_buf,
				  image->cmdline_buf_len);

	if (IS_ERR(ldata)) {
		ret = PTR_ERR(ldata);
		goto out;
	}

	image->image_loader_data = ldata;
out:
	if (ret) {
		pr_err("Failed to parpare kdump segments\n");
		kimage_file_post_load_cleanup(image);
	}
	return ret;
}

static int __init kimage_fw_alloc_init(struct kimage **rimage,
				       unsigned long flags)
{
	int ret;
	struct kimage *image;
	bool kexec_on_panic = flags & KEXEC_FILE_ON_CRASH;

	image = do_kimage_alloc_init();
	if (!image)
		return -ENOMEM;

	image->file_mode = 1;

#ifdef CONFIG_CRASH_DUMP
	if (kexec_on_panic) {
		image->control_page = crashk_res.start;
		image->type = KEXEC_TYPE_CRASH;
	}
#endif

	ret = kimage_fw_prepare_segments(image, flags);
	if (ret)
		goto out_free_image;

	ret = sanity_check_segment_list(image);
	if (ret)
		goto out_free_post_load_bufs;

	ret = -ENOMEM;
	image->control_code_page = kimage_alloc_control_pages(image,
					get_order(KEXEC_CONTROL_PAGE_SIZE));
	if (!image->control_code_page) {
		pr_err("Could not allocate control_code_buffer\n");
		goto out_free_post_load_bufs;
	}

	if (!kexec_on_panic) {
		image->swap_page = kimage_alloc_control_pages(image, 0);
		if (!image->swap_page) {
			pr_err("Could not allocate swap buffer\n");
			goto out_free_control_pages;
		}
	}

	*rimage = image;
	return 0;
out_free_control_pages:
	kimage_free_page_list(&image->control_pages);
out_free_post_load_bufs:
	kimage_file_post_load_cleanup(image);
out_free_image:
	pr_err("Failed to alloc kdump initialization");
	kfree(image);
	return ret;
}

static int __init thread_fn(void *unused)
{
	int ret = 0, i;
	unsigned long flags = (KEXEC_ARCH | KEXEC_FILE_ON_CRASH | KEXEC_ON_CRASH);
	struct kimage **dest_image, *image;

	image = NULL;

	if (!kexec_trylock())
		return -EBUSY;

	dest_image = &kexec_crash_image;
#ifdef CONFIG_CRASH_DUMP
	if (kexec_crash_image)
		arch_kexec_unprotect_crashkres();
#endif

	ret = kimage_fw_alloc_init(&image, flags);
	if (ret)
		goto out;

	ret = machine_kexec_prepare(image);
	if (ret)
		goto out;

	ret = kimage_crash_copy_vmcoreinfo(image);
	if (ret)
		goto out;

	//ret = kexec_calculate_store_digests(image);
	//if (ret)
	//	goto out;

	for (i = 0; i < image->nr_segments; i++) {
		struct kexec_segment *ksegment;

		ksegment = &image->segment[i];
		pr_debug("segment[%d]: buf=0x%p bufsz=0x%zx mem=0x%lx memsz=0x%zx\n",
			 i, ksegment->buf, ksegment->bufsz, ksegment->mem,
			 ksegment->memsz);

		ret = kimage_load_segment(image, &image->segment[i]);
		if (ret)
			goto out;
	}

	kimage_terminate(image);

	ret = machine_kexec_post_load(image);
	if (ret)
		goto out;

	pr_debug("kexec_fw_load: type:%u, start:0x%lx head:0x%lx flags:0x%lx\n",
		 image->type, image->start, image->head, flags);

	kimage_file_post_load_cleanup(image);

	image = xchg(dest_image, image);
out:
	if (ret)
		pr_err("Failed to load kdump image\n");

#ifdef CONFIG_CRASH_DUMP
	if (kexec_crash_image)
		arch_kexec_protect_crashkres();
#endif
	kexec_unlock();
	kimage_free(image);
	return ret;
}

static int __init kexec_fw_init(void)
{
#ifdef CONFIG_CRASH_DUMP
	if (!crashk_res.start || !crashk_res.end)
		return -EINVAL;
#endif

	kexec_fw_task = kthread_run(thread_fn, NULL, "kexec_fw_load");
	if (IS_ERR(kexec_fw_task)) {
		pr_err("Failed to execute kdump kthread\n");
		return PTR_ERR(kexec_fw_task);
	}

	pr_info("creating thread for built-in kdump\n");

	return 0;
}

static void __exit kexec_fw_exit(void)
{
	if (kexec_fw_task)
		kthread_stop(kexec_fw_task);

	pr_info("built-in kdump unloaded\n");
}

fs_initcall(kexec_fw_init);
module_exit(kexec_fw_exit);
