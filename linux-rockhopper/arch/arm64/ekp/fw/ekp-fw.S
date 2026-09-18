/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2020 LG Electronics
 */

#include <linux/init.h>
#include <asm/page.h>

#ifdef EKP_FW_IMAGE
#define EKP_ALIGN	.balign	4096
#define EKP_FW		.incbin EKP_FW_IMAGE
#else
#define EKP_ALIGN	.balign	8
#define EKP_FW
#endif /* EKP_FW_IMAGE */

	__INITRODATA

	.globl	__ekp_fw_header
	.globl	ekp_fw_blob_start
	.globl	ekp_fw_blob_size

	EKP_ALIGN
__ekp_fw_header:
	EKP_FW
	.balign	PAGE_SIZE, 0
__ekp_fw_end:

	.balign	8
ekp_fw_blob_start:
	.quad	__ekp_fw_header
ekp_fw_blob_size:
	.quad	__ekp_fw_end - __ekp_fw_header

	.end
