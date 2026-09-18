/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2020 LG Electronics
 */

#ifndef _LINUX_EKP_H
#define _LINUX_EKP_H

#include <asm/ekp.h>

#ifndef __ASSEMBLY__

#include <linux/init.h>
#include <linux/alloc_tag.h>

#ifdef CONFIG_EKP

static __always_inline bool ekp_enabled(void)
{
	return arch_ekp_enabled();
}

static __always_inline bool ekp_pa_readonly(phys_addr_t addr)
{
	return arch_ekp_pa_readonly(addr);
}

static __always_inline bool ekp_va_readonly(unsigned long addr)
{
	return arch_ekp_va_readonly(addr);
}

static __always_inline bool ekp_page_readonly(struct page *page)
{
	return arch_ekp_page_readonly(page);
}

static __always_inline bool ekp_ptdesc_readonly(struct ptdesc *ptdesc)
{
	return arch_ekp_page_readonly(ptdesc_page(ptdesc));
}

static __always_inline void ekp_romemset_zero(phys_addr_t addr,
					      unsigned long size)
{
	arch_ekp_romemset_zero(addr, size);
}

static __always_inline void ekp_start(void)
{
	arch_ekp_start();
}

static __always_inline void ekp_cred_init(const phys_addr_t ro_cred, const phys_addr_t cred,
					  const void *ext, const bool override)
{
	arch_ekp_cred_init(ro_cred, cred, ext, override);
}

static __always_inline bool ekp_cred_validcaller(void)
{
	return arch_ekp_cred_validcaller();
}

static __always_inline void ekp_slab_set_fp(phys_addr_t addr, void *fp, void *p,
					    unsigned long random,
					    unsigned long ptr_addr)
{
	arch_ekp_slab_set_fp(addr, fp, p, random, ptr_addr);
}

static __always_inline void __init ekp_kasan_page_ro(void *ptr)
{
#ifdef CONFIG_KASAN
	arch_ekp_kasan_page_ro(ptr);
#endif
}

static __always_inline void ekp_module_protection_prepare(const void *mod)
{
#ifdef CONFIG_EKP_MODULE_PROTECTION
	if (likely(ekp_enabled()))
		arch_ekp_module_protection_prepare(mod);
#endif
}

static __always_inline void ekp_module_protection_enable(const void *mod)
{
#ifdef CONFIG_EKP_MODULE_PROTECTION
	if (likely(ekp_enabled()))
		arch_ekp_module_protection_enable(mod);
#endif
}

static __always_inline void ekp_module_protection_after_init(const void *mod)
{
#ifdef CONFIG_EKP_MODULE_PROTECTION
	if (likely(ekp_enabled()))
		arch_ekp_module_protection_after_init(mod);
#endif
}

static __always_inline void ekp_module_protection_disable(const void *mod)
{
#ifdef CONFIG_EKP_MODULE_PROTECTION
	if (likely(ekp_enabled()))
		arch_ekp_module_protection_disable(mod);
#endif
}

static __always_inline void ekp_module_protection_disable_init(const void *mod)
{
#ifdef CONFIG_EKP_MODULE_PROTECTION
	if (likely(ekp_enabled()))
		arch_ekp_module_protection_disable_init(mod);
#endif
}

static __always_inline void ekp_module_protection_disable_core(const void *mod)
{
#ifdef CONFIG_EKP_MODULE_PROTECTION
	if (likely(ekp_enabled()))
		arch_ekp_module_protection_disable_core(mod);
#endif
}

static __always_inline void * __meminit ekp_vmemmap_alloc_block_zero(
						unsigned long size, int node)
{
	return arch_ekp_vmemmap_alloc_block_zero(size, node);
}

static __always_inline struct page *ekp_alloc_ro_pages_noprof(
					gfp_t gfp_mask, unsigned int order)
{
	return arch_ekp_alloc_ro_pages_noprof(gfp_mask, order);
}

#define ekp_alloc_ro_pages(...)	\
	alloc_hooks(ekp_alloc_ro_pages_noprof(__VA_ARGS__))

static __always_inline unsigned long __ekp_get_free_ro_pages(gfp_t gfp_mask,
							     unsigned int order)
{
	return __arch_ekp_get_free_ro_pages(gfp_mask, order);
}

static __always_inline void __ekp_free_ro_pages(struct page *page,
						unsigned int order)
{
	__arch_ekp_free_ro_pages(page, order);
}

static __always_inline void ekp_free_ro_pages(unsigned long addr,
					      unsigned int order)
{
	arch_ekp_free_ro_pages(addr, order);
}

static __always_inline void __init ekp_ptp_setup(unsigned long start,
						 unsigned long pages)
{
#ifndef CONFIG_BPF_JIT_ALWAYS_ON
	arch_ekp_ptp_setup(start, pages);
#endif
}

/* Performance Test */
static __always_inline void ekp_perf_begin(int ekp_cmd)
{
	arch_ekp_perf_begin(ekp_cmd);
}

static __always_inline void ekp_perf_end(int ekp_cmd)
{
	arch_ekp_perf_end(ekp_cmd);
}

#else /* !CONFIG_EKP */

static inline bool ekp_enabled(void) { return false; }
static inline bool ekp_pa_readonly(phys_addr_t a) { return false; }
static inline bool ekp_va_readonly(unsigned long a) { return false; }
static inline bool ekp_page_readonly(struct page *p) { return false; }
static inline bool ekp_ptdesc_readonly(struct ptdesc *p) {return false; }
static inline void ekp_romemset_zero(phys_addr_t addr, unsigned long size) {}
static inline void ekp_start(void) {}

static inline void ekp_cred_init(const phys_addr_t ro_cred, const phys_addr_t cred,
				 const void *ext, const bool override) {}

static inline bool ekp_cred_validcaller(void) { return true; }

static inline void ekp_slab_set_fp(phys_addr_t phys, void *fp, void *p,
				   unsigned long random,
				   unsigned long ptr_addr) {}

static inline void __init ekp_kasan_page_ro(void *ptr) {}

static inline void ekp_module_protection_prepare(const void *mod) {}
static inline void ekp_module_protection_enable(const void *mod) {}
static inline void ekp_module_protection_after_init(const void *mod) {}
static inline void ekp_module_protection_disable(const void *mod) {}
static inline void ekp_module_protection_disable_init(const void *mod) {}
static inline void ekp_module_protection_disable_core(const void *mod) {}

static inline void * __meminit ekp_vmemmap_alloc_block_zero(
				unsigned long size, int node) { return NULL; }

static inline struct page *ekp_alloc_ro_pages_noprof(
					gfp_t gfp_mask,
					unsigned int order) { return NULL; }

#define ekp_alloc_ro_pages(...)	\
	ekp_alloc_ro_pages_noprof(__VA_ARGS__)

static inline unsigned long __ekp_get_free_ro_pages(
					gfp_t gfp_mask,
					unsigned int order) { return 0; }

static inline void __ekp_free_ro_pages(struct page *page, unsigned int order) {}
static inline void ekp_free_ro_pages(unsigned long addr, unsigned int order) {}

static inline void __init ekp_ptp_setup(unsigned long start,
					unsigned long pages) {}

/* Performance Test */
static inline void ekp_perf_begin(int ekp_cmd) {}
static inline void ekp_perf_end(int ekp_cmd) {}

#endif /* CONFIG_EKP */

#define __ekp_get_free_ro_page(gfp)	__ekp_get_free_ro_pages(gfp, 0)
#define __ekp_free_ro_page(page)	__ekp_free_ro_pages(page, 0)
#define ekp_free_ro_page(addr)		ekp_free_ro_pages(addr, 0)

#endif /* !__ASSEMBLY__ */

#endif /* _LINUX_EKP_H */
