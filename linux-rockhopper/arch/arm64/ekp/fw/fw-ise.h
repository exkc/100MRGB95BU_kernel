/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2017 LG Electronics
 */

#ifndef __ARM64_EKP_FW_ISE_H
#define __ARM64_EKP_FW_ISE_H

#include <linux/init.h>
#include <linux/errno.h>

#include <asm/ekp/cmd.h>

/*
 * Error codes from EKP ISE F/W
 * These values should be the same as the values in error.h for ISE F/W
 */
#define EKP_ISE_OK			(0)
#define EKP_ISE_CMD_NOT_SUPPORT		(1)
#define EKP_ISE_DETECT_VIOLATION	(2)
#define EKP_ISE_PANIC_VIOLATION		(3)

/* Sub return values */
#define UPPER_BIT(x)			(1ULL << ((x) + 32))
#define INIT_AFTER_START		UPPER_BIT(0)
#define SET_PGD_VIOLATION		UPPER_BIT(1)
#define SET_P4D_VIOLATION		UPPER_BIT(2)
#define SET_PUD_VIOLATION		UPPER_BIT(3)
#define SET_PMD_VIOLATION		UPPER_BIT(4)
#define SET_PTE_VIOLATION		UPPER_BIT(5)
#define EMUL_SCTLR_VIOLATION		UPPER_BIT(6)
#define EMUL_TTBR0_VIOLATION		UPPER_BIT(7)
#define EMUL_TTBR1_VIOLATION		UPPER_BIT(8)
#define EMUL_TCR_VIOLATION		UPPER_BIT(9)
#define SLAB_SET_FP_VIOLATION		UPPER_BIT(10)
#define CRED_INIT_VIOLATION		UPPER_BIT(11)
#define CRED_SECURITY_VIOLATION		UPPER_BIT(12)
#define LKMP_PREPARE_VIOLATION		UPPER_BIT(13)
#define LKMP_ENABLE_VIOLATION		UPPER_BIT(14)
#define LKMP_AFTER_INIT_VIOLATION	UPPER_BIT(15)
#define LKMP_DISABLE_VIOLATION		UPPER_BIT(16)
#define LKMP_DISABLE_INIT_VIOLATION	UPPER_BIT(17)
#define LKMP_DISABLE_CORE_VIOLATION	UPPER_BIT(18)
#define SET_ROMEM_VIOLATION		UPPER_BIT(19)
#define ARCH_CMD_VIOLATION		UPPER_BIT(20)
#define DUPLICATED_RO_VIOLATION		UPPER_BIT(21)
#define FORCED_RO_VIOLATION		UPPER_BIT(22)
#define HIBERNATION_VIOLATION		UPPER_BIT(23)
#define SUSPEND_VIOLATION		UPPER_BIT(24)
#define UNKNOWN_VIOLATION		UPPER_BIT(25)
#define EKP_ISE_VIOLATION_MAX		(25)

#define ROMEM_VIOLATION_MASK	\
	(DUPLICATED_RO_VIOLATION | FORCED_RO_VIOLATION)

/* EKP-FW header */
struct ekp_fw_header {
	uint64_t magic;		/* magic code : define at build time */
	uint32_t version;	/* EKP F/W version */
	uint32_t size_kb;	/* EKP F/W size in KB */
	uint32_t stack_size;	/* EKP F/W stack size */
} __packed;

extern struct ekp_fw_header __ekp_fw_header __initconst;

#define ekp_fw_magic		__ekp_fw_header.magic
#define ekp_fw_version		__ekp_fw_header.version
#define ekp_fw_size_kb		__ekp_fw_header.size_kb
#define ekp_fw_stack_size	__ekp_fw_header.stack_size

extern unsigned long ekp_fw_blob_start __initconst;
extern unsigned long ekp_fw_blob_size __initconst;

extern bool __init ekp_fw_available(void);
extern int __init ekp_fw_init(struct ekp_init_info *info,
			      struct ekp_debug_info *debug,
			      struct memory_layout *mlayout);
extern int ekp_fw_init_secondary_cpus(unsigned int cpu);
#endif /* __ARM64_EKP_FW_ISE_H */
