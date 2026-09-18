/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2017 LG Electronics
 */

#ifndef __ASM_EKP_MM_H
#define __ASM_EKP_MM_H

#ifndef __ASSEMBLY__
#ifdef CONFIG_EKP
#include <asm/fixmap.h>
#include <linux/ekp.h>

extern char *__ekp_rodata_start[];
extern char *__ekp_rodata_end[];

extern phys_addr_t __init ekp_romem_phys_alloc(phys_addr_t size);

static __always_inline void ekp_set_pte(pte_t *ptep, pte_t pte)
{
	if ((u64)ptep < __fix_to_virt(__end_of_fixed_addresses)) {
		ekp_perf_begin(EKP_SET_PTE);
		if (ekp_tunnel(EKP_SET_PTE, __pa(ptep), pte_val(pte)) < 0)
			pr_err("%s: failed to set pte.\n", __func__);
		ekp_perf_end(EKP_SET_PTE);
	} else {
		WRITE_ONCE(*ptep, pte);
	}
}

static __always_inline void ekp_set_pmd(pmd_t *pmdp, pmd_t pmd)
{
	if ((u64)pmdp < __fix_to_virt(__end_of_fixed_addresses)) {
		ekp_perf_begin(EKP_SET_PMD);
		if (ekp_tunnel(EKP_SET_PMD, __pa(pmdp), pmd_val(pmd)) < 0)
			pr_err("%s: failed to set pmd.\n", __func__);
		ekp_perf_end(EKP_SET_PMD);
	} else {
		WRITE_ONCE(*pmdp, pmd);
	}
}

static __always_inline void ekp_set_pud(pud_t *pudp, pud_t pud)
{
	if ((u64)pudp < __fix_to_virt(__end_of_fixed_addresses)) {
		ekp_perf_begin(EKP_SET_PUD);
		if (ekp_tunnel(EKP_SET_PUD, __pa(pudp), pud_val(pud)) < 0)
			pr_err("%s: failed to set pud.\n", __func__);
		ekp_perf_end(EKP_SET_PUD);
	} else {
		WRITE_ONCE(*pudp, pud);
	}
}

#define ekp_set_p4d(p4dp, p4d)	ekp_set_pgd((pgd_t *)p4dp, __pgd(p4d_val(p4d)))

static __always_inline void ekp_set_pgd(pgd_t *pgdp, pgd_t pgd)
{
	if ((u64)pgdp < __fix_to_virt(__end_of_fixed_addresses)) {
		ekp_perf_begin(EKP_SET_PGD);
		if (ekp_tunnel(EKP_SET_PGD, __pa(pgdp), pgd_val(pgd)) < 0)
			pr_err("%s: failed to set pgd.\n", __func__);
		ekp_perf_end(EKP_SET_PGD);
	} else {
		WRITE_ONCE(*pgdp, pgd);
	}
}

static __always_inline uint64_t __ekp_xchg_relaxed(volatile void *ptr,
						   uint64_t x)
{
	return ekp_tunnel(EKP_ARCH_XCHG, __pa(ptr), x);
}

static __always_inline uint64_t __ekp_cmpxchg_relaxed(volatile void *ptr,
						      uint64_t old,
						      uint64_t new)
{
	return ekp_tunnel(EKP_ARCH_CMPXCHG, __pa(ptr), old, new);
}

#define ekp_xchg_relaxed(ptr, v)					\
({									\
	__typeof__(*(ptr)) __ret;					\
	if (likely(ekp_enabled())) {					\
		__ret = (__typeof__(*(ptr)))				\
			__ekp_xchg_relaxed((ptr), (uint64_t)(v));	\
	} else {							\
		__ret = xchg_relaxed(ptr, v);				\
	}								\
	__ret;								\
})

#define ekp_cmpxchg_relaxed(ptr, o, n)					\
({									\
	__typeof__(*(ptr)) __ret;					\
	if (likely(ekp_enabled())) {					\
		__ret = (__typeof__(*(ptr)))				\
			__ekp_cmpxchg_relaxed((ptr), (uint64_t)(o),	\
					      (uint64_t)(n));		\
	} else {							\
		__ret = cmpxchg_relaxed(ptr, o, n);			\
	}								\
	__ret;								\
})

#endif /* CONFIG_EKP */
#endif /* !__ASSEMBLY__ */

#endif /* __ASM_EKP_MM_H */
