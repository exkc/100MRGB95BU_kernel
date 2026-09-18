/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __EKP_DEBUG_CORE_PTMANIP_H
#define __EKP_DEBUG_CORE_PTMANIP_H

#include <linux/mm_types.h>
#include <linux/types.h>
#include <linux/pgtable.h>

#define PGTABLE_LEVEL_ALL	(-1)
#define PGTABLE_LEVEL_PGD	(0)
#define PGTABLE_LEVEL_P4D	(1)
#define PGTABLE_LEVEL_PUD	(2)
#define PGTABLE_LEVEL_PMD	(3)
#define PGTABLE_LEVEL_PTE	(4)

#ifdef CONFIG_ARM64_PA_BITS_52
#define PTE_ADDR_MASK	PHYS_TO_PTE_ADDR_MASK
#else
#define PTE_ADDR_MASK	PTE_ADDR_LOW
#endif

struct ptmanip_req {
	bool remap;
	phys_addr_t phys_addr;
	pgprot_t set_mask;
	pgprot_t clear_mask;
	pgprot_t current_prot;
};

static inline pgd_t *ekp_ptm_pgd(struct mm_struct *mm, unsigned long addr)
{
	return pgd_offset(mm, addr);
}

extern p4d_t *ekp_ptm_p4d(struct mm_struct *mm, unsigned long addr);
extern pud_t *ekp_ptm_pud(struct mm_struct *mm, unsigned long addr);
extern pmd_t *ekp_ptm_pmd(struct mm_struct *mm, unsigned long addr);
extern pte_t *ekp_ptm_pte(struct mm_struct *mm, unsigned long addr);

static inline pgprot_t ekp_ptm_pgd_prot(struct mm_struct *mm,
					unsigned long addr)
{
	pgd_t *pgd = ekp_ptm_pgd(mm, addr);
	if (pgd == NULL)
		return __pgprot(0);

	return __pgprot(pgd_val(READ_ONCE(*pgd)) & ~PTE_ADDR_MASK);
}

static inline pgprot_t ekp_ptm_p4d_prot(struct mm_struct *mm,
					unsigned long addr)
{
	p4d_t *p4d = ekp_ptm_p4d(mm, addr);
	if (p4d == NULL)
		return __pgprot(0);

	return __pgprot(p4d_val(READ_ONCE(*p4d)) & ~PTE_ADDR_MASK);
}

static inline pgprot_t ekp_ptm_pud_prot(struct mm_struct *mm,
					unsigned long addr)
{
	pud_t *pud = ekp_ptm_pud(mm, addr);
	if (pud == NULL)
		return __pgprot(0);

	return __pgprot(pud_val(READ_ONCE(*pud)) & ~PTE_ADDR_MASK);
}

static inline pgprot_t ekp_ptm_pmd_prot(struct mm_struct *mm,
					unsigned long addr)
{
	pmd_t *pmd = ekp_ptm_pmd(mm, addr);
	if (pmd == NULL)
		return __pgprot(0);

	return __pgprot(pmd_val(READ_ONCE(*pmd)) & ~PTE_ADDR_MASK);
}

static inline pgprot_t ekp_ptm_pte_prot(struct mm_struct *mm,
					unsigned long addr)
{
	pte_t *pte = ekp_ptm_pte(mm, addr);
	if (pte == NULL)
		return __pgprot(0);

	return __pgprot(pte_val(READ_ONCE(*pte)) & ~PTE_ADDR_MASK);
}

extern int ekp_ptm_pgtable_change(struct mm_struct *mm,
				  struct ptmanip_req *req,
				  unsigned long addr, int level);

extern void ekp_ptm_pgtable_dump(struct seq_file *m, struct mm_struct *mm,
				 unsigned long addr, int level);

extern void ekp_parse_ptm_option(struct mm_struct *mm, unsigned long addr,
				 int level, const char *str,
				 struct ptmanip_req *req);

extern bool ekp_ptm_option_valid(const char *str);
extern void ekp_ptm_execute_shellcode(void *mem);

#endif	/* __EKP_DEBUG_CORE_PTMANIP_H */
