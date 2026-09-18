// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2023 LG Electronics
 */

#include <linux/mm.h>
#include <linux/pagewalk.h>
#include "ptprot.h"

struct check_state {
	struct mm_struct *mm;
	bool ro;
	bool pxn;
	bool uxn;
	bool no_el0;
	void (*check)(unsigned long addr, struct check_state *st);
};

static void check_el1_ro_xn(unsigned long addr, struct check_state *st)
{
	if (st->mm == &init_mm) {
		/*
		 * In this case, it already write-locked for init_mm,
		 * thus we must not use write-lock to avoid a dead-lock.
		 */
		if (!kaddr_ro_lockless(addr))
			st->ro = false;

		if (!kaddr_pxn_lockless(addr))
			st->pxn = false;

		if (!kaddr_uxn_lockless(addr))
			st->uxn = false;

		if (kaddr_el0_lockless(addr))
			st->no_el0 = false;
	} else {
		if (!kaddr_ro(addr))
			st->ro = false;

		if (!kaddr_pxn(addr))
			st->pxn = false;

		if (!kaddr_uxn(addr))
			st->uxn = false;

		if (kaddr_el0(addr))
			st->no_el0 = false;
	}
}

static void check_ro(unsigned long addr, struct check_state *st)
{
	if (st->mm == &init_mm) {
		/*
		 * In this case, it already write-locked for init_mm,
		 * thus we must not use write-lock to avoid a dead-lock.
		 */
		if (!kaddr_ro_lockless(addr))
			st->ro = false;
	} else {
		if (!kaddr_ro(addr))
			st->ro = false;
	}
}

static void check_ro_using_bitmap(unsigned long addr, struct check_state *st)
{
	if (!ekp_va_readonly(addr))
		st->ro = false;
}

static void check_pxn(unsigned long addr, struct check_state *st)
{
	if (st->mm == &init_mm) {
		/*
		 * In this case, it already write-locked for init_mm,
		 * thus we must not use write-lock to avoid a dead-lock.
		 */
		if (!kaddr_pxn_lockless(addr))
			st->pxn = false;
	} else {
		if (!kaddr_pxn(addr))
			st->pxn = false;
	}
}

static void check_uxn(unsigned long addr, struct check_state *st)
{
	if (st->mm == &init_mm) {
		/*
		 * In this case, it already write-locked for init_mm,
		 * thus we must not use write-lock to avoid a dead-lock.
		 */
		if (!kaddr_uxn_lockless(addr))
			st->uxn = false;
	} else {
		if (!kaddr_uxn(addr))
			st->uxn = false;
	}
}

static void check_no_el0(unsigned long addr, struct check_state *st)
{
	if (st->mm == &init_mm) {
		/*
		 * In this case, it already write-locked for init_mm,
		 * thus we must not use write-lock to avoid a dead-lock.
		 */
		if (kaddr_el0_lockless(addr))
			st->no_el0 = false;
	} else {
		if (kaddr_el0(addr))
			st->no_el0 = false;
	}
}

static int check_pgtable_pgd_entry(pgd_t *pgd, unsigned long addr,
				   unsigned long next, struct mm_walk *walk)
{
	struct check_state *st = walk->private;

	if (st->check != NULL)
		st->check((unsigned long)pgd, st);

	return 0;
}

static int check_pgtable_p4d_entry(p4d_t *p4d, unsigned long addr,
				   unsigned long next, struct mm_walk *walk)
{
	struct check_state *st = walk->private;

	if (st->check != NULL)
		st->check((unsigned long)p4d, st);

	return 0;
}

static int check_pgtable_pud_entry(pud_t *pud, unsigned long addr,
				   unsigned long next, struct mm_walk *walk)
{
	struct check_state *st = walk->private;

	if (st->check != NULL)
		st->check((unsigned long)pud, st);

	return 0;
}

static int check_pgtable_pmd_entry(pmd_t *pmd, unsigned long addr,
				   unsigned long next, struct mm_walk *walk)
{
	struct check_state *st = walk->private;

	if (st->check != NULL)
		st->check((unsigned long)pmd, st);

	return 0;
}

static int check_pgtable_pte_entry(pte_t *pte, unsigned long addr,
				   unsigned long next, struct mm_walk *walk)
{
	struct check_state *st = walk->private;

	if (st->check != NULL)
		st->check((unsigned long)pte, st);

	return 0;
}

static struct mm_walk_ops check_pgtable_ops = {
	.pgd_entry = check_pgtable_pgd_entry,
	.p4d_entry = check_pgtable_p4d_entry,
	.pud_entry = check_pgtable_pud_entry,
	.pmd_entry = check_pgtable_pmd_entry,
	.pte_entry = check_pgtable_pte_entry,
};

static void check_prot(struct check_state *st)
{
	unsigned long start, end;

	/*
	 * The range from ~PAGE_OFFSET+1 to PAGE_OFFSET-1 is the hole.
	 */
	if (st->mm == &init_mm) {
		start = PAGE_OFFSET;
		end = ~0ULL;
	} else {
		start = 0ULL;
		end = -PAGE_OFFSET;
	}

	mmap_write_lock(st->mm);
	walk_page_range_novma(st->mm, start, end, &check_pgtable_ops, NULL, st);
	mmap_write_unlock(st->mm);
}

bool check_pgtable_bad(struct mm_struct *mm)
{
	struct check_state st = {
		.mm = mm,
		.ro = true,
		.pxn = true,
		.uxn = true,
		.no_el0 = true,
		.check = check_el1_ro_xn,
	};

	check_prot(&st);
	return !(st.ro && st.pxn && st.uxn && st.no_el0);
}

bool check_pgtable_ro(struct mm_struct *mm)
{
	struct check_state st = {
		.mm = mm,
		.ro = true,
		.check = check_ro,
	};

	check_prot(&st);
	return st.ro;
}

bool check_pgtable_ro_using_bitmap(struct mm_struct *mm)
{
	struct check_state st = {
		.mm = mm,
		.ro = true,
		.check = check_ro_using_bitmap,
	};

	check_prot(&st);
	return st.ro;
}

bool check_pgtable_pxn(struct mm_struct *mm)
{
	struct check_state st = {
		.mm = mm,
		.pxn = true,
		.check = check_pxn,
	};

	check_prot(&st);
	return st.pxn;
}

bool check_pgtable_uxn(struct mm_struct *mm)
{
	struct check_state st = {
		.mm = mm,
		.uxn = true,
		.check = check_uxn,
	};

	check_prot(&st);
	return st.uxn;
}

bool check_pgtable_no_el0(struct mm_struct *mm)
{
	struct check_state st = {
		.mm = mm,
		.no_el0 = true,
		.check = check_no_el0,
	};

	check_prot(&st);
	return st.no_el0;
}
