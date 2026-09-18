// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2023 LG Electronics
 */

#include <linux/mm.h>
#include <linux/pagewalk.h>
#include "ptprot.h"

struct check_state {
	u64 page_mask;
	u64 table_mask;
	bool nomap;
	bool set;
	bool skip;
};

static __always_inline void check_prot_pxd(struct check_state *st, u64 val)
{
	if (st->skip)
		return;

	if (val == 0) {
		st->nomap = true;
	} else if ((val & PTE_TABLE_BIT) == 0) {
		if ((val & st->page_mask) == st->page_mask)
			st->set = true;
		else
			st->set = false;
	} else {
		if (st->table_mask != 0) {
			if ((val & st->table_mask) == st->table_mask) {
				if (st->table_mask != PGTABLE_APTABLE_NOUSR)
					st->set = true;
				st->skip = true;
			}
		}
	}
}

static __always_inline void check_prot_pte(struct check_state *st, u64 val)
{
	if (st->skip)
		return;

	if (val == 0) {
		st->nomap = true;
	} else if ((val & st->page_mask) == st->page_mask)
		st->set = true;
	else
		st->set = false;
}

static int check_pgd_entry(pgd_t *pgd, unsigned long addr,
			   unsigned long next, struct mm_walk *walk)
{
	struct check_state *st = walk->private;
	check_prot_pxd(st, pgd_val(READ_ONCE(*pgd)));
	return 0;
}

static int check_p4d_entry(p4d_t *p4d, unsigned long addr,
			   unsigned long next, struct mm_walk *walk)
{
	struct check_state *st = walk->private;
	check_prot_pxd(st, p4d_val(READ_ONCE(*p4d)));
	return 0;
}

static int check_pud_entry(pud_t *pud, unsigned long addr,
			   unsigned long next, struct mm_walk *walk)
{
	struct check_state *st = walk->private;
	check_prot_pxd(st, pud_val(READ_ONCE(*pud)));
	return 0;
}

static int check_pmd_entry(pmd_t *pmd, unsigned long addr,
			   unsigned long next, struct mm_walk *walk)
{
	struct check_state *st = walk->private;
	check_prot_pxd(st, pmd_val(READ_ONCE(*pmd)));
	return 0;
}

static int check_pte_entry(pte_t *pte, unsigned long addr,
			   unsigned long next, struct mm_walk *walk)
{
	struct check_state *st = walk->private;
	check_prot_pte(st, pte_val(READ_ONCE(*pte)));
	return 0;
}

static struct mm_walk_ops check_ops = {
	.pgd_entry = check_pgd_entry,
	.p4d_entry = check_p4d_entry,
	.pud_entry = check_pud_entry,
	.pmd_entry = check_pmd_entry,
	.pte_entry = check_pte_entry,
};

static int check_prot(struct mm_struct *mm, unsigned long addr,
		      u64 page_mask, u64 table_mask, bool lockless)
{
	struct check_state st = {
		.page_mask = page_mask,
		.table_mask = table_mask,
		.nomap = false,
		.set = false,
		.skip = false,
	};
	unsigned long end = addr + 1;

	if (is_set_hpd1())
		st.table_mask = 0ULL;

	if (end == 0UL)
		end = ~0UL;

	if (!lockless)
		mmap_write_lock(mm);

	walk_page_range_novma(mm, addr, end, &check_ops, NULL, &st);

	if (!lockless)
		mmap_write_unlock(mm);

	if (st.nomap)
		return -EFAULT;

	if (st.set)
		return 1;

	return 0;
}

int check_kaddr_prot(unsigned long addr, u64 page_mask,
		     u64 table_mask, bool lockless)
{
	if ((addr >= PAGE_OFFSET) && (addr <= ~0UL))
		return check_prot(&init_mm, addr, page_mask,
				  table_mask, lockless);

	pr_err("%s: address v.%016lx is not the kernel address.\n",
	       __func__, addr);

	return -ERANGE;
}
