/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2023 LG Electronics
 */

#ifndef __ASM_GENERIC_EKP_OPS_H
#define __ASM_GENERIC_EKP_OPS_H

#ifndef __ASSEMBLY__

#include <linux/init.h>
#include <linux/mm_types.h>

#define __ekp_rodata	__section(".ekp.rodata") __aligned(PAGE_SIZE)

#define __FORTIFY_INLINE extern __always_inline __attribute__((gnu_inline))

extern bool arch_ekp_enabled(void);
extern bool arch_ekp_pa_readonly(phys_addr_t phys);
extern bool arch_ekp_va_readonly(unsigned long addr);
extern bool arch_ekp_page_readonly(struct page *page);
extern void arch_ekp_romemset_zero(phys_addr_t addr, unsigned long size);
extern void arch_ekp_start(void);

extern void arch_ekp_cred_init(const phys_addr_t ro_cred, const phys_addr_t cred,
			       const void *ext, const bool override);

extern bool arch_ekp_cred_validcaller(void);

extern void arch_ekp_slab_set_fp(phys_addr_t addr, void *fp, void *p,
				 unsigned long random,
				 unsigned long ptr_addr);

extern void __init arch_ekp_kasan_page_ro(void* addr);
extern void arch_ekp_module_protection_prepare(const void *mod);
extern void arch_ekp_module_protection_enable(const void *mod);
extern void arch_ekp_module_protection_after_init(const void *mod);
extern void arch_ekp_module_protection_disable(const void *mod);
extern void arch_ekp_module_protection_disable_init(const void *mod);
extern void arch_ekp_module_protection_disable_core(const void *mod);

extern void * __meminit arch_ekp_vmemmap_alloc_block_zero(
						unsigned long size, int node);

extern struct page *arch_ekp_alloc_ro_pages_noprof(gfp_t gfp_mask,
						   unsigned int order);
extern unsigned long __arch_ekp_get_free_ro_pages(gfp_t gfp_mask,
						  unsigned int order);
extern void __arch_ekp_free_ro_pages(struct page *page, unsigned int order);
extern void arch_ekp_free_ro_pages(unsigned long addr, unsigned int order);

extern void __init arch_ekp_ptp_setup(unsigned long start, unsigned long pages);

/* Performance Test */
extern void arch_ekp_perf_begin(int ekp_cmd);
extern void arch_ekp_perf_end(int ekp_cmd);

#endif /* !__ASSEMBLY__ */

#endif /* __ASM_GENERIC_EKP_OPS_H */
