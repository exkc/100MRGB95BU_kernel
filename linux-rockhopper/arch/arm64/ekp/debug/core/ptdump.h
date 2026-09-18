/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __EKP_DEBUG_CORE_PTDUMP_H
#define __EKP_DEBUG_CORE_PTDUMP_H

#include <linux/seq_file.h>
#include <linux/types.h>
#include <asm/page.h>

#define PTDUMP_LEVEL_ALL	(-1)
#define PTDUMP_LEVEL_PGD	(0)
#define PTDUMP_LEVEL_P4D	(1)
#define PTDUMP_LEVEL_PUD	(2)
#define PTDUMP_LEVEL_PMD	(3)
#define PTDUMP_LEVEL_PTE	(4)

struct ekp_ptdump_state {
	struct seq_file *seq;
	struct mm_struct *mm;
	int target_level;
	void *data;
	bool pass;

	struct {
		unsigned long start;
		unsigned long end;
	} range;

	struct {
		int level;
		u64 prot;
		unsigned long start;
		unsigned long next;
		const struct prot_bits *bits;
		size_t bits_count;
	} dump;

	void (*note_page)(struct ekp_ptdump_state *st,
			  int level, unsigned long addr,
			  unsigned long next, u64 val);
};

static const char *ptdump_pgtable_names[] __maybe_unused = {
	"PGD",
	"P4D",
	"PUD",
	"PMD",
	"PTE"
};

extern int ekp_debug_ptdump_nolock(struct ekp_ptdump_state *st);
extern int ekp_debug_ptdump(struct ekp_ptdump_state *st);

#endif /* __EKP_DEBUG_CORE_PTDUMP_H */
