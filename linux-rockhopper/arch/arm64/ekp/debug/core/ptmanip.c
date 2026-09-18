// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2023 LG Electronics
 */

#include <linux/mm.h>
#include <linux/seq_file.h>

#include "ptprot.h"
#include "ptmanip.h"

p4d_t *ekp_ptm_p4d(struct mm_struct *mm, unsigned long addr)
{
	pgd_t *pgd;

	pgd = pgd_offset(mm, addr);
	if (!pgd_present(READ_ONCE(*pgd)))
		return NULL;

	return p4d_offset(pgd, addr);
}

pud_t *ekp_ptm_pud(struct mm_struct *mm, unsigned long addr)
{
	pgd_t *pgd;
	p4d_t *p4d;

	pgd = pgd_offset(mm, addr);
	if (!pgd_present(READ_ONCE(*pgd)))
		return NULL;

	p4d = p4d_offset(pgd, addr);
	if (!p4d_present(READ_ONCE(*p4d)))
		return NULL;

	return pud_offset(p4d, addr);
}

pmd_t *ekp_ptm_pmd(struct mm_struct *mm, unsigned long addr)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;

	pgd = pgd_offset(mm, addr);
	if (!pgd_present(READ_ONCE(*pgd)))
		return NULL;

	p4d = p4d_offset(pgd, addr);
	if (!p4d_present(READ_ONCE(*p4d)))
		return NULL;

	pud = pud_offset(p4d, addr);
	if (!pud_present(READ_ONCE(*pud)))
		return NULL;

	return pmd_offset(pud, addr);
}

pte_t *ekp_ptm_pte(struct mm_struct *mm, unsigned long addr)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	pgd = pgd_offset(mm, addr);
	if (!pgd_present(READ_ONCE(*pgd)))
		return NULL;

	p4d = p4d_offset(pgd, addr);
	if (!p4d_present(READ_ONCE(*p4d)))
		return NULL;

	pud = pud_offset(p4d, addr);
	if (!pud_present(READ_ONCE(*pud)))
		return NULL;

	pmd = pmd_offset(pud, addr);
	if (!pmd_present(READ_ONCE(*pmd)))
		return NULL;

	return pte_offset_map(pmd, addr);
}

static inline u64 change_desc(u64 desc, struct ptmanip_req *req)
{
	desc &= ~pgprot_val(req->clear_mask);
	desc |= pgprot_val(req->set_mask);

	if (req->remap) {
		desc &= ~PTE_ADDR_MASK;
		desc |= __phys_to_pte_val(req->phys_addr);
	}

	return desc;
}

static int change_ptm_pgd(pgd_t *pgd, struct ptmanip_req *req)
{
	u64 val;

	if (!pgd)
		return -ENOMEM;

	val = change_desc(pgd_val(READ_ONCE(*pgd)), req);
	set_pgd(pgd, __pgd(val));

	return 0;
}

static int change_ptm_p4d(p4d_t *p4d, struct ptmanip_req *req)
{
	u64 val;

	if (!p4d)
		return -ENOMEM;

	val = change_desc(p4d_val(READ_ONCE(*p4d)), req);
	set_p4d(p4d, __p4d(val));

	return 0;
}

static int change_ptm_pud(pud_t *pud, struct ptmanip_req *req)
{
	u64 val;

	if (!pud)
		return -ENOMEM;

	val = change_desc(pud_val(READ_ONCE(*pud)), req);
	set_pud(pud, __pud(val));

	return 0;
}

static int change_ptm_pmd(pmd_t *pmd, struct ptmanip_req *req)
{
	u64 val;

	if (!pmd)
		return -ENOMEM;

	val = change_desc(pmd_val(READ_ONCE(*pmd)), req);
	set_pmd(pmd, __pmd(val));

	return 0;
}

static int change_ptm_pte(pte_t *pte, struct ptmanip_req *req)
{
	u64 val;

	if (!pte)
		return -ENOMEM;

	val = change_desc(pte_val(READ_ONCE(*pte)), req);
	set_pte(pte, __pte(val));

	return 0;
}

int ekp_ptm_pgtable_change(struct mm_struct *mm, struct ptmanip_req *req,
			   unsigned long addr, int level)
{
	unsigned long start, end;
	int ret;

	switch (level) {
	case PGTABLE_LEVEL_PGD:
		start = round_down(addr, PGDIR_SIZE);
		end = start + PGDIR_SIZE;
		ret = change_ptm_pgd(ekp_ptm_pgd(mm, addr), req);
		break;
	case PGTABLE_LEVEL_P4D:
		start = round_down(addr, P4D_SIZE);
		end = start + P4D_SIZE;
		ret = change_ptm_p4d(ekp_ptm_p4d(mm, addr), req);
		break;
	case PGTABLE_LEVEL_PUD:
		start = round_down(addr, PUD_SIZE);
		end = start + PUD_SIZE;
		ret = change_ptm_pud(ekp_ptm_pud(mm, addr), req);
		break;
	case PGTABLE_LEVEL_PMD:
		start = round_down(addr, PMD_SIZE);
		end = start + PMD_SIZE;
		ret = change_ptm_pmd(ekp_ptm_pmd(mm, addr), req);
		break;
	case PGTABLE_LEVEL_PTE:
		start = round_down(addr, PAGE_SIZE);
		end = start + PAGE_SIZE;
		ret = change_ptm_pte(ekp_ptm_pte(mm, addr), req);
		break;
	default:
		return -EINVAL;
	}

	if (ret < 0)
		return ret;

	flush_tlb_kernel_range(start, end);
	return 0;
}

static void dump_ptm_prot(struct seq_file *m, u64 val,
			  const struct prot_bits *bits, size_t count)
{
	size_t i;

	for (i = 0; i < count; ++i, ++bits) {
		const char *s;

		if ((val & bits->mask) == bits->val)
			s = bits->set;
		else
			s = bits->clear;

		if (s)
			seq_printf(m, " %s", s);
	}

	seq_printf(m, "\n");
}

static void __dump_ptm_pxd_prot(struct seq_file *m, pmd_t pmd)
{
	const struct prot_bits *bits;
	size_t bits_count;

	if (pmd_table(pmd)) {
		bits = table_prot_bits;
		bits_count = ARRAY_SIZE(table_prot_bits);
	} else if (pmd_sect(pmd)) {
		bits = page_prot_bits;
		bits_count = ARRAY_SIZE(page_prot_bits);
	} else {
		seq_printf(m, "\n");
		return;
	}

	dump_ptm_prot(m, pmd_val(pmd), bits, bits_count);
}

static inline void dump_ptm_pgd_prot(struct seq_file *m, pgd_t pgd)
{
	__dump_ptm_pxd_prot(m, __pmd(pgd_val(pgd)));
}

static inline void dump_ptm_p4d_prot(struct seq_file *m, p4d_t p4d)
{
	__dump_ptm_pxd_prot(m, __pmd(p4d_val(p4d)));
}

static inline void dump_ptm_pud_prot(struct seq_file *m, pud_t pud)
{
	__dump_ptm_pxd_prot(m, __pmd(pud_val(pud)));
}

static inline void dump_ptm_pmd_prot(struct seq_file *m, pmd_t pmd)
{
	__dump_ptm_pxd_prot(m, pmd);
}

static void dump_ptm_pte_prot(struct seq_file *m, pte_t pte)
{
	const struct prot_bits *bits;
	size_t bits_count;

	if (!pte_present(pte)) {
		seq_printf(m, "\n");
		return;
	}

	bits = page_prot_bits;
	bits_count = ARRAY_SIZE(page_prot_bits);

	dump_ptm_prot(m, pte_val(pte), bits, bits_count);
}

static void dump_ptm_pgd(struct seq_file *m, pgd_t *pgd)
{
	seq_printf(m, "pgd/*pgd: ");
	seq_printf(m, "0x%px/0x%016llx", pgd, pgd_val(READ_ONCE(*pgd)));
	dump_ptm_pgd_prot(m, READ_ONCE(*pgd));
}

static void dump_ptm_p4d(struct seq_file *m, p4d_t *p4d)
{
	seq_printf(m, "p4d/*p4d: ");

	if (p4d == NULL) {
		seq_printf(m, "(null)/----   no-map\n");
		return;
	}

	seq_printf(m, "0x%px/0x%016llx", p4d, p4d_val(READ_ONCE(*p4d)));
	dump_ptm_p4d_prot(m, READ_ONCE(*p4d));
}

static void dump_ptm_pud(struct seq_file *m, pud_t *pud)
{
	seq_printf(m, "pud/*pud: ");

	if (pud == NULL) {
		seq_printf(m, "(null)/----   no-map\n");
		return;
	}

	seq_printf(m, "0x%px/0x%016llx", pud, pud_val(READ_ONCE(*pud)));
	dump_ptm_pud_prot(m, READ_ONCE(*pud));
}

static void dump_ptm_pmd(struct seq_file *m, pmd_t *pmd)
{
	seq_printf(m, "pmd/*pmd: ");

	if (pmd == NULL) {
		seq_printf(m, "(null)/----   no-map\n");
		return;
	}

	seq_printf(m, "0x%px/0x%016llx", pmd, pmd_val(READ_ONCE(*pmd)));
	dump_ptm_pmd_prot(m, READ_ONCE(*pmd));
}

static void dump_ptm_pte(struct seq_file *m, pte_t *pte)
{
	seq_printf(m, "pte/*pte: ");

	if (pte == NULL) {
		seq_printf(m, "(null)/----   no-map\n");
		return;
	}

	seq_printf(m, "0x%px/0x%016llx", pte, pte_val(READ_ONCE(*pte)));
	dump_ptm_pte_prot(m, READ_ONCE(*pte));
}

static void dump_ptm_pgtable(struct seq_file *m,
			     struct mm_struct *mm, unsigned long addr)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	pgd = pgd_offset(mm, addr);
	dump_ptm_pgd(m, pgd);
	if (!pgd_present(READ_ONCE(*pgd)) || pgd_leaf(READ_ONCE(*pgd)))
		return;

	p4d = p4d_offset(pgd, addr);
	dump_ptm_p4d(m, p4d);
	if (!p4d_present(READ_ONCE(*p4d)) || p4d_leaf(READ_ONCE(*p4d)))
		return;

	pud = pud_offset(p4d, addr);
	dump_ptm_pud(m, pud);
	if (!pud_present(READ_ONCE(*pud)) || pud_leaf(READ_ONCE(*pud)))
		return;

	pmd = pmd_offset(pud, addr);
	dump_ptm_pmd(m, pmd);
	if (!pmd_present(READ_ONCE(*pmd)) || pmd_leaf(READ_ONCE(*pmd)))
		return;

	dump_ptm_pte(m, pte_offset_map(pmd, addr));
}

void ekp_ptm_pgtable_dump(struct seq_file *m, struct mm_struct *mm,
			  unsigned long addr, int level)
{
	switch (level) {
	case PGTABLE_LEVEL_PGD:
		dump_ptm_pgd(m, ekp_ptm_pgd(mm, addr));
		break;
	case PGTABLE_LEVEL_P4D:
		dump_ptm_p4d(m, ekp_ptm_p4d(mm, addr));
		break;
	case PGTABLE_LEVEL_PUD:
		dump_ptm_pud(m, ekp_ptm_pud(mm, addr));
		break;
	case PGTABLE_LEVEL_PMD:
		dump_ptm_pmd(m, ekp_ptm_pmd(mm, addr));
		break;
	case PGTABLE_LEVEL_PTE:
		dump_ptm_pte(m, ekp_ptm_pte(mm, addr));
		break;
	case PGTABLE_LEVEL_ALL:
		dump_ptm_pgtable(m, mm, addr);
		break;
	default:
		break;
	}
}
