/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2017 LG Electronics
 */

#ifndef __ARM64_EKP_PRIVATE_H
#define __ARM64_EKP_PRIVATE_H

#include <linux/types.h>
#include <linux/module.h>

#include <asm/page.h>
#include <asm/pgtable.h>

#include "kinfo.h"
#include "version.h"
#include "fw/fw-ise.h"

/* Module base & end address to be passed to ekp-fw */
#define MODULE_BASE	(ekp_module_base())
#define MODULE_END	(MODULE_BASE + SZ_2G)

#ifdef CONFIG_KEXEC_FIRMWARE
extern char *__ekp_machine_kexec[];
#else
#define __ekp_machine_kexec	0ULL
#endif

#define NR_BM_PTE_TABLES \
	SPAN_NR_ENTRIES(FIXADDR_TOT_START, FIXADDR_TOP, PMD_SHIFT)

extern pte_t bm_pte[NR_BM_PTE_TABLES][PTRS_PER_PTE];
extern pmd_t bm_pmd[PTRS_PER_PMD];
extern pud_t bm_pud[PTRS_PER_PUD];

extern bool ekp_ise_enabled;
extern bool ekp_started;

extern int __init romem_reserve(void);
extern void __init empty_bitmap_reserve(void);
extern void __init romem_free(void);
extern void __init get_romem_info(struct ekp_init_info *info);

#ifdef CONFIG_EKP_FAULT_NOTIFIER
extern void ekp_ise_fault_handler(struct arm_smccc_res *res,
				  const char *violation,
				  uint64_t count, unsigned long line);
#else
static inline void ekp_ise_fault_handler(struct arm_smccc_res *res,
					 const char *violation,
					 uint64_t count, unsigned long line) {}
#endif

#ifdef CONFIG_EKP_DEBUGFS_CHECK_PROT
extern bool ekp_within_module_area(phys_addr_t phys);
#endif

#endif /* __ARM64_EKP_PRIVATE_H */
