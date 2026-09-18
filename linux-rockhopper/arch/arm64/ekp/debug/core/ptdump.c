// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2023 LG Electronics
 */

#include <linux/pagewalk.h>
#include "ptdump.h"

static bool should_note(struct ekp_ptdump_state *st, int level)
{
	if (st->note_page) {
		if (st->target_level == PTDUMP_LEVEL_ALL)
			return true;

		if (st->target_level == level)
			return true;
	}

	return false;
}

static int ptdump_pgd_entry(pgd_t *pgd, unsigned long addr,
			    unsigned long next, struct mm_walk *walk)
{
	struct ekp_ptdump_state *st = walk->private;
	pgd_t val = READ_ONCE(*pgd);

	if (should_note(st, PTDUMP_LEVEL_PGD))
		st->note_page(st, PTDUMP_LEVEL_PGD, addr, next, pgd_val(val));

	if (pgd_leaf(val))
		walk->action = ACTION_CONTINUE;

	return 0;
}

static int ptdump_p4d_entry(p4d_t *p4d, unsigned long addr,
			    unsigned long next, struct mm_walk *walk)
{
	struct ekp_ptdump_state *st = walk->private;
	p4d_t val = READ_ONCE(*p4d);

	if (mm_p4d_folded(st->mm))
		return 0;

	if (should_note(st, PTDUMP_LEVEL_P4D))
		st->note_page(st, PTDUMP_LEVEL_P4D, addr, next, p4d_val(val));

	if (p4d_leaf(val))
		walk->action = ACTION_CONTINUE;

	return 0;
}

static int ptdump_pud_entry(pud_t *pud, unsigned long addr,
			    unsigned long next, struct mm_walk *walk)
{
	struct ekp_ptdump_state *st = walk->private;
	pud_t val = READ_ONCE(*pud);

	if (mm_pud_folded(st->mm))
		return 0;

	if (should_note(st, PTDUMP_LEVEL_PUD))
		st->note_page(st, PTDUMP_LEVEL_PUD, addr, next, pud_val(val));

	if (pud_leaf(val))
		walk->action = ACTION_CONTINUE;

	return 0;
}

static int ptdump_pmd_entry(pmd_t *pmd, unsigned long addr,
			    unsigned long next, struct mm_walk *walk)
{
	struct ekp_ptdump_state *st = walk->private;
	pmd_t val = READ_ONCE(*pmd);

	if (mm_pmd_folded(st->mm))
		return 0;

	if (should_note(st, PTDUMP_LEVEL_PMD))
		st->note_page(st, PTDUMP_LEVEL_PMD, addr, next, pmd_val(val));

	if (pmd_leaf(val))
		walk->action = ACTION_CONTINUE;

	return 0;
}

static int ptdump_pte_entry(pte_t *pte, unsigned long addr,
			    unsigned long next, struct mm_walk *walk)
{
	struct ekp_ptdump_state *st = walk->private;
	pte_t val = ptep_get_lockless(pte);

	if (should_note(st, PTDUMP_LEVEL_PTE))
		st->note_page(st, PTDUMP_LEVEL_PTE, addr, next, pte_val(val));

	return 0;
}

static struct mm_walk_ops ptdump_ops = {
	.pgd_entry = ptdump_pgd_entry,
	.p4d_entry = ptdump_p4d_entry,
	.pud_entry = ptdump_pud_entry,
	.pmd_entry = ptdump_pmd_entry,
	.pte_entry = ptdump_pte_entry,
};

int ekp_debug_ptdump_nolock(struct ekp_ptdump_state *st)
{
	return walk_page_range_novma(st->mm, st->range.start,
				     st->range.end, &ptdump_ops, NULL, st);
}

int ekp_debug_ptdump(struct ekp_ptdump_state *st)
{
	int ret;

	mmap_write_lock(st->mm);
	ret = ekp_debug_ptdump_nolock(st);
	mmap_write_unlock(st->mm);

	return ret;
}
