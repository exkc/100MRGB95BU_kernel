// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2023 LG Electronics
 */

#include <linux/debugfs.h>
#include <linux/efi.h>
#include <linux/err.h>
#include <linux/memblock.h>
#include <linux/mm.h>
#include <linux/rwlock.h>
#include <linux/sched/mm.h>
#include <linux/sched/signal.h>
#include <linux/slab.h>
#include <asm/memory.h>

#include "private.h"
#include "debugfs.h"
#include "core/ptdump.h"
#include "core/ptprot.h"

static pid_t sysinfo_target_user_pid __maybe_unused;

#ifdef CONFIG_EKP_DEBUGFS_PTDUMP
struct addr_marker {
	unsigned long start;
	const char *name;
};

static struct addr_marker *kernel_address_markers __ro_after_init;

static u64 get_prot_mask(const struct prot_bits *bits, size_t count)
{
	int i;
	u64 mask = 0;

	if (bits != NULL) {
		for (i = 0; i < count; ++i)
			mask |= bits[i].mask;
	}

	return mask;
}

static void dump_prot(struct seq_file *m, u64 prot,
		      const struct prot_bits *bits, size_t count)
{
	size_t i;

	for (i = 0; i < count; ++i, ++bits) {
		const char *s;

		if ((prot & bits->mask) == bits->val)
			s = bits->set;
		else
			s = bits->clear;

		if (s)
			seq_printf(m, " %s", s);
	}
}

static inline int dump_indent(int level)
{
	if (level == 3 && PTRS_PER_PMD == 1)
		level = 2;
	if (level == 2 && PTRS_PER_PUD == 1)
		level = 1;
	if (level == 1 && PTRS_PER_P4D == 1)
		level = 0;
	return (level * 3);
}

static void dump_desc(struct seq_file *m, int level,
		      unsigned long start, unsigned long end,
		      u64 prot, const struct prot_bits *bits,
		      size_t bits_count)
{
	static const char units[] = "KMGTPE";
	const char *unit = units;
	const char *name = ptdump_pgtable_names[level];
	unsigned long delta = (end - start) >> 10;
	char buf[16];

	seq_printf(m, "%*s%s [0x%016lx-0x%016lx] ",
		   dump_indent(level), "", name, start, end);

	while (!(delta & 1023) && unit[1]) {
		delta >>= 10;
		unit++;
	}

	if (bits == table_prot_bits) {
		snprintf(buf, sizeof(buf), "(%lu%c)", delta, *unit);
		seq_printf(m, "%13s", buf);
	} else {
		snprintf(buf, sizeof(buf), "%lu%c", delta, *unit);
		seq_printf(m, "%12s ", buf);
	}

	dump_prot(m, prot, bits, bits_count);
	seq_printf(m, "\n");
}

static inline void dump_as_needed(struct ekp_ptdump_state *st, int level,
				  unsigned long end, u64 val, u64 prot,
				  const struct prot_bits *bits,
				  size_t bits_count)
{
	unsigned long align = 0;

	if (val == 0)
		return;

	if (st->target_level == PTDUMP_LEVEL_ALL) {
		switch (level) {
		case PTDUMP_LEVEL_PTE:
			align = PMD_SIZE;
			break;
		case PTDUMP_LEVEL_PMD:
			align = PUD_SIZE;
			break;
		case PTDUMP_LEVEL_PUD:
			align = P4D_SIZE;
			break;
		default:
			return;
		}
	}

	if (IS_ALIGNED(end, align) || (end == st->range.end)) {
		dump_desc(st->seq, level, st->dump.start,
			  end, prot, bits, bits_count);

		st->dump.prot = 0;
	}
}

static inline bool should_dump(struct ekp_ptdump_state *st,
			       int level, unsigned long addr, u64 prot)
{
	if (st->dump.level != level)
		return true;

	if (st->dump.prot != prot)
		return true;

	if (st->dump.next != addr)
		return true;

	return false;
}

static void dump_prev_merged(struct ekp_ptdump_state *st, int level,
			     unsigned long addr, unsigned long next,
			     u64 prot, const struct prot_bits *bits,
			     size_t bits_count)
{
	if (st->dump.prot == 0) {
		st->dump.level = level;
		st->dump.prot = prot;
		st->dump.start = addr;
		st->dump.bits = bits;
		st->dump.bits_count = bits_count;
	} else if (should_dump(st, level, addr, prot)) {
		dump_desc(st->seq, st->dump.level, st->dump.start,
			  st->dump.next, st->dump.prot,
			  st->dump.bits, st->dump.bits_count);

		st->dump.level = level;
		st->dump.prot = prot;
		st->dump.start = addr;
		st->dump.bits = bits;
		st->dump.bits_count = bits_count;
	}

	st->dump.next = next;
}

static void note_pte(struct ekp_ptdump_state *st, int level,
		     unsigned long addr, unsigned long next, u64 val)
{
	const struct prot_bits *bits;
	size_t bits_count;
	u64 prot;

	if ((val != 0) && (val & PTE_TABLE_BIT) == 0) {
		if (val != 0x1ULL) {
			unsigned long end = addr + PAGE_SIZE;

			if (end == 0UL)
				end = ~0UL;

			seq_printf(st->seq, "[BUG] PTE [0x%016lx-0x%016lx]",
				   addr, end);
			seq_printf(st->seq, " 0x%016llx\n", val);
		}
		return;
	}

	bits = page_prot_bits;
	bits_count = ARRAY_SIZE(page_prot_bits);
	prot = val & get_prot_mask(bits, bits_count);

	dump_prev_merged(st, level, addr, next, prot, bits, bits_count);
	dump_as_needed(st, level, next, val, prot, bits, bits_count);
}

static void note_pxd(struct ekp_ptdump_state *st, int level,
		     unsigned long addr, unsigned long next, u64 val)
{
	const struct prot_bits *bits;
	size_t bits_count;
	u64 prot;

	if ((val & PGD_TABLE_BIT) == 0) {
		bits = block_prot_bits;
		bits_count = ARRAY_SIZE(block_prot_bits);
		prot = val & get_prot_mask(bits, bits_count);

		dump_prev_merged(st, level, addr, next, prot, bits, bits_count);
		dump_as_needed(st, level, next, val, prot, bits, bits_count);
	} else {
		bits = table_prot_bits;
		bits_count = ARRAY_SIZE(table_prot_bits);
		prot = val & get_prot_mask(bits, bits_count);

		dump_prev_merged(st, level, addr, next, prot,
				 block_prot_bits, ARRAY_SIZE(block_prot_bits));

		dump_desc(st->seq, level, addr, next, prot, bits, bits_count);
		st->dump.prot = 0;
	}
}

static void note_pxd_single(struct ekp_ptdump_state *st, int level,
			    unsigned long addr, unsigned long next, u64 val)
{
	const struct prot_bits *bits;
	size_t bits_count;
	u64 prot;

	if ((val & PGD_TABLE_BIT) == 0) {
		bits = block_prot_bits;
		bits_count = ARRAY_SIZE(block_prot_bits);
	} else {
		bits = table_prot_bits;
		bits_count = ARRAY_SIZE(table_prot_bits);
	}

	prot = val & get_prot_mask(bits, bits_count);

	dump_prev_merged(st, level, addr, next, prot, bits, bits_count);
	dump_as_needed(st, level, next, val, prot, bits, bits_count);
}

static void note_page(struct ekp_ptdump_state *st, int level,
		      unsigned long addr, unsigned long next, u64 val)
{
	if (level == PTDUMP_LEVEL_PTE)
		note_pte(st, level, addr, next, val);
	else
		note_pxd(st, level, addr, next, val);
}

static void note_page_single(struct ekp_ptdump_state *st, int level,
			     unsigned long addr, unsigned long next, u64 val)
{
	if (level == PTDUMP_LEVEL_PTE)
		note_pte(st, level, addr, next, val);
	else
		note_pxd_single(st, level, addr, next, val);
}

static int __kernel_ptdump(struct seq_file *m, int target_level)
{
	struct ekp_ptdump_state st = {
		.seq = m,
		.mm = &init_mm,
		.target_level = target_level,
		.note_page = note_page,
	};

	int i = 0, ret;

	if (target_level != PTDUMP_LEVEL_ALL)
		st.note_page = note_page_single;

	seq_printf(m, "[[ Kernel Page Table Dump ]]\n");

	if (init_mm.pgd != swapper_pg_dir) {
		seq_printf(m, "ERROR: init_mm.pgd is not swapper_pg_dir\n");
		return -1;
	}

	seq_printf(m, "PGD(swapper_pg_dir): v.%px p.%016lx\n",
		   swapper_pg_dir, (unsigned long)__pa_symbol(swapper_pg_dir));

	if (ekp_enabled()) {
		seq_printf(m, "EKP: Enabled\n");
		seq_printf(m, "EKP: HPD1 clear [%s]\n",
			   is_set_hpd1() ? "X" : "O");
#ifdef CONFIG_EKP_DEBUGFS_CHECK_PROT
		seq_printf(m, "EKP: Page Tables Protection [%s]\n",
			   !check_pgtable_bad(&init_mm) ? "O" : "X");
		seq_printf(m, "EKP: Read-only Page Tables [%s]\n",
			   check_pgtable_ro_using_bitmap(&init_mm) ? "O" : "X");
#endif
	} else {
		seq_printf(m, "EKP: Disabled\n");
	}

	get_online_mems();
	mmap_write_lock(&init_mm);

	do {
		st.range.start = kernel_address_markers[i].start;
		st.range.end = kernel_address_markers[i + 1].start;
		st.dump.prot = 0;

		seq_printf(m, "--- [ %s ] ---\n",
			   kernel_address_markers[i].name);

		if (st.range.start == st.range.end)
			continue;

		ret = ekp_debug_ptdump_nolock(&st);
		if (ret < 0) {
			seq_printf(m, "ERROR: failed to dump page tables (%d)\n",
				   ret);
			break;
		}

		if (st.dump.prot != 0) {
			dump_desc(m, st.dump.level, st.dump.start,
				  st.dump.next, st.dump.prot,
				  st.dump.bits, st.dump.bits_count);
		}
	} while (i++, st.range.end != ~0UL);

	mmap_write_unlock(&init_mm);
	put_online_mems();

	return 0;
}

static int __user_ptdump(struct seq_file *m, int target_level)
{
	struct ekp_ptdump_state st = {
		.seq = m,
		.target_level = target_level,
		.note_page = note_page,
	};

	struct task_struct *p, *t;
	pid_t target_pid = sysinfo_target_user_pid;
	int ret = 0;

	if (target_level != PTDUMP_LEVEL_ALL)
		st.note_page = note_page_single;

	/*
	 * The user addresses can be mapped from 0 to ~PAGE_OFFSET.
	 * The range from ~PAGE_OFFSET+1 to PAGE_OFFSET-1 is the hole.
	 * Thus, we use the range [0, -PAGE_OFFSET) to walk user page tables,
	 * where -PAGE_OFFSET is equal to ~PAGE_OFFSET+1.
	 */
	st.range.start = 0UL;
	st.range.end = -PAGE_OFFSET;

	seq_printf(m, "[[ User Page Table Dump ]]\n");

	read_lock(&tasklist_lock);
	for_each_process_thread(p, t) {
		if ((target_pid != 0) && (target_pid != t->pid))
			continue;

		if (t->mm == NULL)
			continue;

		st.mm = t->mm;
		st.dump.prot = 0;

		seq_printf(m, "--- [ Process: %s(%d) ] ---\n", t->comm, t->pid);

		seq_printf(m, "PGD: v.%px p.%016lx\n",
			   t->mm->pgd, (unsigned long)virt_to_phys(t->mm->pgd));

		if (ekp_enabled()) {
			seq_printf(m, "EKP: Enabled\n");
			seq_printf(m, "EKP: HPD0 clear [%s]\n",
				   is_set_hpd0() ? "X" : "O");
#ifdef CONFIG_EKP_DEBUGFS_CHECK_PROT
			seq_printf(m, "EKP: Page Tables Protection [%s]\n",
				   !check_pgtable_bad(t->mm) ? "O" : "X");
			seq_printf(m, "EKP: Read-only Page Tables [%s]\n",
				   check_pgtable_ro_using_bitmap(t->mm) ?
				   "O" : "X");
#endif
		} else {
			seq_printf(m, "EKP: Disabled\n");
		}

		ret = ekp_debug_ptdump(&st);
		if (ret < 0) {
			seq_printf(m, "ERROR: failed to dump page tables (%d)\n",
				   ret);
			break;
		}

		if (st.dump.prot != 0) {
			dump_desc(m, st.dump.level, st.dump.start,
				  st.dump.next, st.dump.prot,
				  st.dump.bits, st.dump.bits_count);
		}
	}
	read_unlock(&tasklist_lock);

	return 0;
}

#ifdef CONFIG_EFI
static int __efi_ptdump(struct seq_file *m, int target_level)
{
	struct ekp_ptdump_state st = {
		.seq = m,
		.target_level = target_level,
		.note_page = note_page,
	};

	int ret;

	if (target_level != PTDUMP_LEVEL_ALL)
		st.note_page = note_page_single;

	st.range.start = 0UL;
	st.range.end = -PAGE_OFFSET;

	if (efi_mm.pgd == NULL) {
		seq_printf(m, "The efi_mm.pgd is not allocated.\n");
		return 0;
	}

	seq_printf(m, "[[ UEFI Page Table Dump ]]\n");
	seq_printf(m, "PGD: v.%px p.%016llx\n", efi_mm.pgd, __pa(efi_mm.pgd));

	if (ekp_enabled()) {
		seq_printf(m, "EKP: Enabled\n");
		seq_printf(m, "EKP: HPD0 clear [%s]\n",
		is_set_hpd0() ? "X" : "O");
#ifdef CONFIG_EKP_DEBUGFS_CHECK_PROT
	seq_printf(m, "EKP: Page Tables Protection [%s]\n",
		   !check_pgtable_bad(&efi_mm) ? "O" : "X");
	seq_printf(m, "EKP: Read-only Page Tables [%s]\n",
		   check_pgtable_ro_using_bitmap(&efi_mm) ? "O" : "X");
#endif
	} else {
		seq_printf(m, "EKP: Disabled\n");
	}

	seq_printf(m, "--- [ UEFI runtime ] ---\n");

	ret = ekp_debug_ptdump(&st);
	if (ret < 0) {
		seq_printf(m, "ERROR: failed to dump page tables (%d)\n", ret);
		return 0;
	}

	if (st.dump.prot != 0) {
		dump_desc(m, st.dump.level, st.dump.start,
			  st.dump.next, st.dump.prot,
			  st.dump.bits, st.dump.bits_count);
	}

	return ret;
}
#endif /* CONFIG_EFI */

/*
 * /sys/kernel/debug/ekp/sysinfo/target_user_pid
 *
 * Set the PID of the user process which is a target to debug.
 */
static int target_user_pid_show(struct seq_file *m)
{
	if (sysinfo_target_user_pid == 0)
		seq_printf(m, "all\n");
	else
		seq_printf(m, "%d\n", sysinfo_target_user_pid);

	return 0;
}

static int target_user_pid_store(const char __user *buf, size_t size)
{
	int pid, ret;

	ret = kstrtoint_from_user(buf, size, 0, &pid);
	if (ret < 0)
		return ret;

	if (pid <= 0)
		sysinfo_target_user_pid = 0;
	else
		sysinfo_target_user_pid = pid;

	return 0;
}

DEFINE_EKP_DEBUGFS_RW(target_user_pid);

/*
 * /sys/kernel/debug/ekp/sysinfo/kernel_ptdump
 *
 * Show contents of swapper_pg_dir (page table for kernel).
 */
static int kernel_ptdump_show(struct seq_file *m)
{
	return __kernel_ptdump(m, PTDUMP_LEVEL_ALL);
}

DEFINE_EKP_DEBUGFS_RO(kernel_ptdump);

/*
 * /sys/kernel/debug/ekp/sysinfo/user_ptdump
 *
 * Show contents of user process page tables.
 * The PID of target can be set by target_user_pid file.
 *
 * target_user_pid
 *   0   : dump page tables of all user processes
 *   PID : dump page tables of a process which has a given PID
 */
static int user_ptdump_show(struct seq_file *m)
{
	return __user_ptdump(m, PTDUMP_LEVEL_ALL);
}

DEFINE_EKP_DEBUGFS_RO(user_ptdump);

#ifdef CONFIG_EFI
/*
 * /sys/kernel/debug/ekp/sysinfo/efi_ptdump
 *
 * Show contents of UEFI runtime process page tables.
 */
static int efi_ptdump_show(struct seq_file *m)
{
	return __efi_ptdump(m, PTDUMP_LEVEL_ALL);
}

DEFINE_EKP_DEBUGFS_RO(efi_ptdump);
#endif /* CONFIG_EFI */

/*
 * /sys/kernel/debug/ekp/sysinfo/kernel_ptdump_pgd
 *
 * Show PGD's contents of swapper_pg_dir (page table for kernel).
 */
static int kernel_ptdump_pgd_show(struct seq_file *m)
{
	return __kernel_ptdump(m, PTDUMP_LEVEL_PGD);
}

DEFINE_EKP_DEBUGFS_RO(kernel_ptdump_pgd);

/*
 * /sys/kernel/debug/ekp/sysinfo/user_ptdump_pgd
 *
 * Show PGD's contents of user process page tables.
 * The PID of target can be set by target_user_pid file.
 *
 * target_user_pid
 *   0   : dump PGD of all user processes
 *   PID : dump PGD of a process which has a given PID
 */
static int user_ptdump_pgd_show(struct seq_file *m)
{
	return __user_ptdump(m, PTDUMP_LEVEL_PGD);
}

DEFINE_EKP_DEBUGFS_RO(user_ptdump_pgd);

#ifndef __PAGETABLE_P4D_FOLDED
/*
 * /sys/kernel/debug/ekp/sysinfo/kernel_ptdump_p4d
 *
 * Show P4D's contents of swapper_pg_dir (page table for kernel).
 */
static int kernel_ptdump_p4d_show(struct seq_file *m)
{
	return __kernel_ptdump(m, PTDUMP_LEVEL_P4D);
}

DEFINE_EKP_DEBUGFS_RO(kernel_ptdump_p4d);

/*
 * /sys/kernel/debug/ekp/sysinfo/user_ptdump_p4d
 *
 * Show P4D's contents of user process page tables.
 * The PID of target can be set by target_user_pid file.
 *
 * target_user_pid
 *   0   : dump P4D of all user processes
 *   PID : dump P4D of a process which has a given PID
 */
static int user_ptdump_p4d_show(struct seq_file *m)
{
	return __user_ptdump(m, PTDUMP_LEVEL_P4D);
}

DEFINE_EKP_DEBUGFS_RO(user_ptdump_p4d);
#endif	/* __PAGETABLE_P4D_FOLDED */

#ifndef __PAGETABLE_PUD_FOLDED
/*
 * /sys/kernel/debug/ekp/sysinfo/kernel_ptdump_pud
 *
 * Show PUD's contents of swapper_pg_dir (page table for kernel).
 */
static int kernel_ptdump_pud_show(struct seq_file *m)
{
	return __kernel_ptdump(m, PTDUMP_LEVEL_PUD);
}

DEFINE_EKP_DEBUGFS_RO(kernel_ptdump_pud);

/*
 * /sys/kernel/debug/ekp/sysinfo/user_ptdump_pud
 *
 * Show PUD's contents of user process page tables.
 * The PID of target can be set by target_user_pid file.
 *
 * target_user_pid
 *   0   : dump PUD of all user processes
 *   PID : dump PUD of a process which has a given PID
 */
static int user_ptdump_pud_show(struct seq_file *m)
{
	return __user_ptdump(m, PTDUMP_LEVEL_PUD);
}

DEFINE_EKP_DEBUGFS_RO(user_ptdump_pud);
#endif	/* __PAGETABLE_PUD_FOLDED */

#ifndef __PAGETABLE_PMD_FOLDED
/*
 * /sys/kernel/debug/ekp/sysinfo/kernel_ptdump_pmd
 *
 * Show PMD's contents of swapper_pg_dir (page table for kernel).
 */
static int kernel_ptdump_pmd_show(struct seq_file *m)
{
	return __kernel_ptdump(m, PTDUMP_LEVEL_PMD);
}

DEFINE_EKP_DEBUGFS_RO(kernel_ptdump_pmd);

/*
 * /sys/kernel/debug/ekp/sysinfo/user_ptdump_pmd
 *
 * Show PMD's contents of user process page tables.
 * The PID of target can be set by target_user_pid file.
 *
 * target_user_pid
 *   0   : dump PMD of all user processes
 *   PID : dump PMD of a process which has a given PID
 */
static int user_ptdump_pmd_show(struct seq_file *m)
{
	return __user_ptdump(m, PTDUMP_LEVEL_PMD);
}

DEFINE_EKP_DEBUGFS_RO(user_ptdump_pmd);
#endif	/* __PAGETABLE_PMD_FOLDED */

/*
 *
 * Show PTE's contents of swapper_pg_dir (page table for kernel).
 */
static int kernel_ptdump_pte_show(struct seq_file *m)
{
	return __kernel_ptdump(m, PTDUMP_LEVEL_PTE);
}

DEFINE_EKP_DEBUGFS_RO(kernel_ptdump_pte);

/*
 * /sys/kernel/debug/ekp/sysinfo/user_ptdump_pte
 *
 * Show PTE's contents of user process page tables.
 * The PID of target can be set by target_user_pid file.
 *
 * target_user_pid
 *   0   : dump PTE of all user processes
 *   PID : dump PTE of a process which has a given PID
 */
static int user_ptdump_pte_show(struct seq_file *m)
{
	return __user_ptdump(m, PTDUMP_LEVEL_PTE);
}

DEFINE_EKP_DEBUGFS_RO(user_ptdump_pte);

static struct ekp_debugfs_attr ekp_sysinfo_ptdump_attrs[] __initdata = {
	{
		.name = "target_user_pid",
		.ops = &target_user_pid,
	},
#ifdef CONFIG_EFI
	{
		.name = "efi_ptdump",
		.ops = &efi_ptdump,
	},
#endif
	{
		.name = "kernel_ptdump",
		.ops = &kernel_ptdump,
	},
	{
		.name = "user_ptdump",
		.ops = &user_ptdump,
	},
	{
		.name = "kernel_ptdump_pgd",
		.ops = &kernel_ptdump_pgd,
	},
	{
		.name = "user_ptdump_pgd",
		.ops = &user_ptdump_pgd,
	},
#ifndef __PAGETABLE_P4D_FOLDED
	{
		.name = "kernel_ptdump_p4d",
		.ops = &kernel_ptdump_p4d,
	},
	{
		.name = "user_ptdump_p4d",
		.ops = &user_ptdump_p4d,
	},
#endif
#ifndef __PAGETABLE_PUD_FOLDED
	{
		.name = "kernel_ptdump_pud",
		.ops = &kernel_ptdump_pud,
	},
	{
		.name = "user_ptdump_pud",
		.ops = &user_ptdump_pud,
	},
#endif
#ifndef __PAGETABLE_PMD_FOLDED
	{
		.name = "kernel_ptdump_pmd",
		.ops = &kernel_ptdump_pmd,
	},
	{
		.name = "user_ptdump_pmd",
		.ops = &user_ptdump_pmd,
	},
#endif
	{
		.name = "kernel_ptdump_pte",
		.ops = &kernel_ptdump_pte,
	},
	{
		.name = "user_ptdump_pte",
		.ops = &user_ptdump_pte,
	},
};
#endif	/* CONFIG_EKP_DEBUGFS_PTDUMP */

#ifdef CONFIG_EKP_DEBUGFS_CHECK_PROT
static void dump_pgtable_prot(struct seq_file *m, struct mm_struct *mm)
{
	seq_printf(m, "Checked page table mappings: %s\n",
		   check_pgtable_bad(mm) ? "FAILED" : "passed");
	seq_printf(m, "RO [%s], ", check_pgtable_ro(mm) ? "O" : "X");
	seq_printf(m, "RO(bitmap) [%s], ",
		   check_pgtable_ro_using_bitmap(mm) ? "O" : "X");
	seq_printf(m, "PXN [%s], ", check_pgtable_pxn(mm) ? "O" : "X");
	seq_printf(m, "UXN [%s], ", check_pgtable_uxn(mm) ? "O" : "X");
	seq_printf(m, "EL1 only [%s]\n", check_pgtable_no_el0(mm) ? "O" : "X");
}

/*
 * /sys/kernel/debug/ekp/sysinfo/kernel_pgtable_prot
 *
 * Show the protection information of swapper_pg_dir (page table for kernel).
 */
static int kernel_pgtable_prot_show(struct seq_file *m)
{
	seq_printf(m, "--- [ swapper_pg_dir ] ---\n");
	dump_pgtable_prot(m, &init_mm);

	return 0;
}

DEFINE_EKP_DEBUGFS_RO(kernel_pgtable_prot);

/*
 * /sys/kernel/debug/ekp/sysinfo/user_pgtable_prot
 *
 * Show the protection information of user page tables.
 * The PID of target can be set by target_user_pid file.
 *
 * target_user_pid
 *   0   : show information of all user process
 *   PID : show information of a process which has a given PID
 */
static int user_pgtable_prot_show(struct seq_file *m)
{
	pid_t target_pid = sysinfo_target_user_pid;
	struct task_struct *p, *t;

	read_lock(&tasklist_lock);
	for_each_process_thread(p, t) {
		if ((target_pid != 0) && (target_pid != t->pid))
			continue;

		if (t->mm == NULL)
			continue;

		seq_printf(m, "--- [ Process: %s(%d) ] ---\n", t->comm, t->pid);
		dump_pgtable_prot(m, t->mm);
	}
	read_unlock(&tasklist_lock);

	return 0;
}

DEFINE_EKP_DEBUGFS_RO(user_pgtable_prot);

#ifdef CONFIG_EFI
/*
 * /sys/kernel/debug/ekp/sysinfo/efi_pgtable_prot
 *
 * Show the protection information of UEFI runtime process page tables.
 */
static int efi_pgtable_prot_show(struct seq_file *m)
{
	if (efi_mm.pgd == NULL) {
		seq_printf(m, "The efi_mm.pgd is not allocated.\n");
		return 0;
	}

	seq_printf(m, "--- [ UEFI runtime ] ---\n");
	dump_pgtable_prot(m, &efi_mm);

	return 0;
}

DEFINE_EKP_DEBUGFS_RO(efi_pgtable_prot);
#endif /* CONFIG_EFI */

static __always_inline bool invalid_or_table_type(struct ekp_ptdump_state *st,
						  int level, unsigned long addr,
						  u64 val)
{
	if (val == 0)
		return true;

	if (level == PTDUMP_LEVEL_PTE) {
		if ((val & PTE_TABLE_BIT) == 0) {
			if (val != 0x1ULL) {
				unsigned long end = addr + PAGE_SIZE;

				if (end == 0UL)
					end = ~0UL;

				seq_printf(st->seq, "[BUG] PTE ");
				seq_printf(st->seq, "[0x%016lx", addr);
				seq_printf(st->seq, "-0x%016lx] ", end);
				seq_printf(st->seq, "0x%016llx\n", val);
			}
			return true;
		}
	} else {
		if ((val & PTE_TABLE_BIT) != 0)
			return true;
	}

	return false;
}

static void __note_prot(struct ekp_ptdump_state *st, int level,
			unsigned long addr, u64 val, u64 mask, const char *name)
{
	if (invalid_or_table_type(st, level, addr, val))
		return;

	if ((val & mask) == 0) {
		if (st->pass) {
			st->pass = false;
			seq_printf(st->seq, "FAILED\n");
		}
		seq_printf(st->seq, "*** Found insecure %s mapping at ", name);
		seq_printf(st->seq, "v.%016lx/p.%016llx\n",
			   addr, __pte_to_phys(__pte(val)));
	}
}

static void note_prot_uxw(struct ekp_ptdump_state *st, int level,
			  unsigned long addr, unsigned long next, u64 val)
{
	__note_prot(st, level, addr, val, PTE_RDONLY | PTE_UXN, "W+X");
}

static void note_prot_pxw(struct ekp_ptdump_state *st, int level,
			  unsigned long addr, unsigned long next, u64 val)
{
	__note_prot(st, level, addr, val, PTE_RDONLY | PTE_PXN, "W+X");
}

static void note_prot_uxn(struct ekp_ptdump_state *st, int level,
			  unsigned long addr, unsigned long next, u64 val)
{
	__note_prot(st, level, addr, val, PTE_UXN, "non-UXN");
}

static void note_prot_pxn(struct ekp_ptdump_state *st, int level,
			  unsigned long addr, unsigned long next, u64 val)
{
	__note_prot(st, level, addr, val, PTE_PXN, "non-PXN");
}

static void dump_map_prot(struct ekp_ptdump_state *st)
{
	if (st->mm == &init_mm) {
		st->range.start = PAGE_OFFSET;
		st->range.end = ~0UL;
	} else {
		st->range.start = 0UL;
		st->range.end = -PAGE_OFFSET;
	}

	st->target_level = PTDUMP_LEVEL_ALL;

	if (ekp_debug_ptdump(st) < 0)
		seq_printf(st->seq, "ERROR: failed to check page tables\n");
}

static void dump_map_prot_wx(struct seq_file *m, struct mm_struct *mm)
{
	struct ekp_ptdump_state st = {
		.seq = m,
		.mm = mm,
		.pass = true,
		.note_page = note_prot_uxw,
	};

	if (mm == &init_mm)
		st.note_page = note_prot_pxw;

#ifdef CONFIG_EFI
	if (mm == &efi_mm)
		st.note_page = note_prot_pxw;
#endif

	seq_printf(m, "Checked W+X mappings: ");

	dump_map_prot(&st);

	if (st.pass)
		seq_printf(m, "passed, no W+X pages found\n");
}

static void dump_map_prot_uxn(struct seq_file *m, struct mm_struct *mm)
{
	struct ekp_ptdump_state st = {
		.seq = m,
		.mm = mm,
		.pass = true,
		.note_page = note_prot_uxn,
	};

	seq_printf(m, "Checked UXN mappings: ");

	dump_map_prot(&st);

	if (st.pass)
		seq_printf(m, "passed, no non-UXN pages found\n");
}

static void dump_map_prot_pxn(struct seq_file *m, struct mm_struct *mm)
{
	struct ekp_ptdump_state st = {
		.seq = m,
		.mm = mm,
		.pass = true,
		.note_page = note_prot_pxn,
	};

	seq_printf(m, "Checked PXN mappings: ");

	dump_map_prot(&st);

	if (st.pass)
		seq_printf(m, "passed, no non-PXN pages found\n");
}

/*
 * /sys/kernel/debug/ekp/sysinfo/kernel_map_prot
 *
 * Check whether the kernel addresses are mapped with W+X
 * and non-UXN permissions.
 */
static int kernel_map_prot_show(struct seq_file *m)
{
	if (init_mm.pgd != swapper_pg_dir) {
		seq_printf(m, "ERROR: init_mm.pgd is not swapper_pg_dir\n");
		return -1;
	}

	seq_printf(m, "--- [ swapper_pg_dir ] ---\n");
	dump_map_prot_wx(m, &init_mm);
	dump_map_prot_uxn(m, &init_mm);

	return 0;
}

DEFINE_EKP_DEBUGFS_RO(kernel_map_prot);

/*
 * /sys/kernel/debug/ekp/sysinfo/user_map_prot
 *
 * Check whether the user addresses are mapped with W+X
 * and non-PXN permissions. The PID of target can be set
 * by target_user_pid file.
 *
 * target_user_pid
 *   0   : check for all user processes
 *   PID : check for a process which has a given PID
 */
static int user_map_prot_show(struct seq_file *m)
{
	pid_t target_pid = sysinfo_target_user_pid;
	struct task_struct *p, *t;

	read_lock(&tasklist_lock);
	for_each_process_thread(p, t) {
		if ((target_pid != 0) && (target_pid != t->pid))
			continue;

		if (t->mm == NULL)
			continue;

		seq_printf(m, "--- [ Process: %s(%d) ] ---\n", t->comm, t->pid);
		dump_map_prot_wx(m, t->mm);
		dump_map_prot_pxn(m, t->mm);
	}
	read_unlock(&tasklist_lock);

	return 0;
}

DEFINE_EKP_DEBUGFS_RO(user_map_prot);

#ifdef CONFIG_EFI
/*
 * /sys/kernel/debug/ekp/sysinfo/efi_map_prot
 *
 * Check whether the UEFI runtime addresses are mapped with
 * W+X and non-UXN permissions.
 */
static int efi_map_prot_show(struct seq_file *m)
{
	if (efi_mm.pgd == NULL) {
		seq_printf(m, "The efi_mm.pgd is not allocated.\n");
		return 0;
	}

	seq_printf(m, "--- [ UEFI runtime ] ---\n");
	dump_map_prot_wx(m, &efi_mm);
	dump_map_prot_uxn(m, &efi_mm);

	return 0;
}

DEFINE_EKP_DEBUGFS_RO(efi_map_prot);
#endif /* CONFIG_EFI */

static phys_addr_t memblock_start __ro_after_init;
static phys_addr_t memblock_end __ro_after_init;

static void compare_based_on_bitmap(struct seq_file *m, bool *pass)
{
	phys_addr_t start = round_down(memblock_start, PAGE_SIZE);
	phys_addr_t phys;

	for (phys = start; phys < memblock_end; phys += PAGE_SIZE) {
		if (ekp_pa_readonly(phys)) {
			unsigned long addr = __phys_to_virt(phys);

			if (!kaddr_ro(addr) && !kaddr_nomap(addr)) {
				if (*pass) {
					*pass = false;
					seq_printf(m, "FAILED\n");
				}
				seq_printf(m, "*** [s:rw] Found the mapping ");
				seq_printf(m, "mismatched at ");
				seq_printf(m, "v.%016lx (p.%016llx)\n",
					   addr, phys);
			}
		}
	}
}

static __always_inline bool within_fixmap_fdt(unsigned long addr)
{
	unsigned long start = __fix_to_virt(FIX_FDT);
	unsigned long end = __fix_to_virt(FIX_FDT_END);

	if ((addr >= start) && (addr < end))
		return true;

	return false;
}

static __always_inline bool should_check_phys(struct ekp_ptdump_state *st,
					      phys_addr_t phys)
{
	unsigned long *vmalloc_bitmap = (unsigned long *)st->data;

	if (vmalloc_bitmap) {
		if (test_bit(__phys_to_pfn(phys), vmalloc_bitmap))
			return false;
	}

	return true;
}

static inline phys_addr_t __bitmap_size(void)
{
	phys_addr_t end = memblock_end_of_DRAM();
	phys_addr_t len = BITS_TO_LONGS(round_up(end, PAGE_SIZE) >> PAGE_SHIFT);

	return round_up(len * sizeof(unsigned long), PAGE_SIZE) + PAGE_SIZE;
}

static void note_compare(struct ekp_ptdump_state *st, int level,
			 unsigned long addr, unsigned long next, u64 val)
{
	if (within_fixmap_fdt(addr)) {
		/*
		 * The kernel has read-only mappings for the FDT region of
		 * the fixmap, but their linear aliases are not read-only.
		 *
		 * Futhermore, the DTB(device tree blob) is loaded into the
		 * FDT region of the fixmap at every boot, so EKP does not
		 * need to protect that region yet.
		 *
		 * For these reason, we skip checking the FDT region of the
		 * fixmap here.
		 */
		return;
	}

	if (invalid_or_table_type(st, level, addr, val))
		return;

	if ((val & PTE_RDONLY) == PTE_RDONLY) {
		phys_addr_t phys = __pte_to_phys(__pte(val));

		if (should_check_phys(st, phys) && !ekp_pa_readonly(phys)) {
			if (st->pass) {
				st->pass = false;
				seq_printf(st->seq, "FAILED\n");
			}
			seq_printf(st->seq, "*** [c:ro] Found the mapping ");
			seq_printf(st->seq, "mismatched at ");
			seq_printf(st->seq, "v.%016lx (p.%016llx)\n",
				   addr, phys);
		}
	}
}

static void compare_based_on_pgtable(struct seq_file *m, bool *pass,
				     unsigned long *vmalloc_bitmap)
{
	struct ekp_ptdump_state st = {
		.seq = m,
		.pass = *pass,
		.data = (void *)vmalloc_bitmap,
		.note_page = note_compare,
	};

	if (init_mm.pgd != swapper_pg_dir) {
		seq_printf(m, "ERROR: init_mm.pgd is not swapper_pg_dir\n");
		return;
	}

	st.mm = &init_mm;
	st.target_level = PTDUMP_LEVEL_ALL;
	st.range.start = PAGE_OFFSET;
	st.range.end = ~0UL;

	if (ekp_debug_ptdump(&st) < 0)
		seq_printf(m, "ERROR: failed to check page tables\n");

	*pass = st.pass;
}

static bool device_memory_type(u64 val)
{
	if ((val & PTE_ATTRINDX_MASK) == PTE_ATTRINDX(MT_DEVICE_nGnRnE))
		return true;

	if ((val & PTE_ATTRINDX_MASK) == PTE_ATTRINDX(MT_DEVICE_nGnRE))
		return true;

	return false;
}

static void note_bitmap(struct ekp_ptdump_state *st, int level,
			unsigned long addr, unsigned long next, u64 val)
{
	unsigned long *bitmap = (unsigned long *)st->data;

	if (device_memory_type(val))
		return;

	if (invalid_or_table_type(st, level, addr, val))
		return;

	if (ekp_within_module_area(__pte_to_phys(__pte(val))))
		return;

	bitmap_set(bitmap, pte_pfn(__pte(val)), 1);
}

static void prepare_vmalloc_bitmap(struct seq_file *m, unsigned long *bitmap)
{
	struct ekp_ptdump_state st = {
		.seq = m,
		.data = (void *)bitmap,
		.note_page = note_bitmap,
	};

	if (init_mm.pgd != swapper_pg_dir) {
		seq_printf(m, "ERROR: init_mm.pgd is not swapper_pg_dir\n");
		return;
	}

	st.mm = &init_mm;
	st.target_level = PTDUMP_LEVEL_PTE;
	st.range.start = VMALLOC_START;
	st.range.end = VMALLOC_END;

	if (ekp_debug_ptdump(&st) < 0)
		seq_printf(m, "ERROR: failed to check page tables\n");
}

/*
 * /sys/kernel/debug/ekp/sysinfo/ekp_ropages_bitmap
 *
 * Check whether the bits in the ekp_ropages_bitmap match the
 * attributes in the page tables.
 *
 * Note that the ekp_ropages_bitmap includes module ranges,
 * but it does not include other vmalloc ranges.
 */
static int ekp_ropages_bitmap_show(struct seq_file *m)
{
	bool pass = true;
	unsigned long *vmalloc_bitmap;

	vmalloc_bitmap = kzalloc(__bitmap_size(), GFP_KERNEL);
	if (!vmalloc_bitmap)
		return -ENOMEM;

	prepare_vmalloc_bitmap(m, vmalloc_bitmap);

	seq_printf(m, "Checked ekp_ropages_bitmap: ");

	compare_based_on_bitmap(m, &pass);
	compare_based_on_pgtable(m, &pass, vmalloc_bitmap);

	if (pass)
		seq_printf(m, "passed, all bits are set correctly\n");

	kfree(vmalloc_bitmap);

	return 0;
}

DEFINE_EKP_DEBUGFS_RO(ekp_ropages_bitmap);

/*
 * /sys/kernel/debug/ekp/sysinfo/full_ropages_bitmap
 *
 * Check whether the bits in the ropages_bitmap match the
 * attributes in the page tables for kernel address space
 * without fixmap fdt.
 */
static int full_ropages_bitmap_show(struct seq_file *m)
{
	bool pass = true;

	seq_printf(m, "Checked ekp_ropages_bitmap: ");

	compare_based_on_bitmap(m, &pass);
	compare_based_on_pgtable(m, &pass, NULL);

	if (pass)
		seq_printf(m, "passed, all bits are set correctly\n");

	return 0;
}

DEFINE_EKP_DEBUGFS_RO(full_ropages_bitmap);

static struct ekp_debugfs_attr ekp_sysinfo_prot_attrs[] __initdata = {
	{
		.name = "kernel_pgtable_prot",
		.ops = &kernel_pgtable_prot,
	},
	{
		.name = "user_pgtable_prot",
		.ops = &user_pgtable_prot,
	},
	{
		.name = "kernel_map_prot",
		.ops = &kernel_map_prot,
	},
	{
		.name = "user_map_prot",
		.ops = &user_map_prot,
	},
	{
		.name = "ekp_ropages_bitmap",
		.ops = &ekp_ropages_bitmap,
	},
	{
		.name = "full_ropages_bitmap",
		.ops = &full_ropages_bitmap,
	},
#ifdef CONFIG_EFI
	{
		.name = "efi_pgtable_prot",
		.ops = &efi_pgtable_prot,
	},
	{
		.name = "efi_map_prot",
		.ops = &efi_map_prot,
	},
#endif
};
#endif /* CONFIG_EKP_DEBUGFS_CHECK_PROT */

#ifdef CONFIG_EKP_DEBUGFS_PTDUMP
static void __init ekp_debugfs_ptdump_init(struct dentry *parent)
{
	u64 page_offset = _PAGE_OFFSET(vabits_actual);
	u64 vmemmap_start = (u64)virt_to_page((void *)page_offset);
	struct addr_marker m[] = {
		{ PAGE_OFFSET,		"Linear Mapping start" },
		{ PAGE_END,		"Linear Mapping end" },
#if defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS)
		{ KASAN_SHADOW_START,	"Kasan shadow start" },
		{ KASAN_SHADOW_END,	"Kasan shadow end" },
#endif
		{ MODULES_VADDR,	"Modules start" },
		{ MODULES_END,		"Modules end" },
		{ VMALLOC_START,	"vmalloc() area" },
		{ VMALLOC_END,		"vmalloc() end" },
		{ vmemmap_start,	"vmemmap start" },
		{ VMEMMAP_END,		"vmemmap end" },
		{ PCI_IO_START,		"PCI I/O start" },
		{ PCI_IO_END,		"PCI I/O end" },
		{ FIXADDR_TOT_START,	"Fixmap start" },
		{ FIXADDR_TOP,		"Fixmap end" },
		{ ~0UL,			NULL },
	};
	static struct addr_marker address_markers[ARRAY_SIZE(m)] __ro_after_init;

	kernel_address_markers = memcpy(address_markers, m, sizeof(m));
	ekp_debugfs_create(parent, ekp_sysinfo_ptdump_attrs);
}
#else /* !CONFIG_EKP_DEBUGFS_PTDUMP */
static inline void __init ekp_debugfs_ptdump_init(struct dentry *parent) {}
#endif /* CONFIG_EKP_DEBUGFS_PTDUMP */

#ifdef CONFIG_EKP_DEBUGFS_CHECK_PROT
static void __init ekp_debugfs_prot_init(struct dentry *parent)
{
	if (ekp_enabled())
		ekp_debugfs_create(parent, ekp_sysinfo_prot_attrs);

	memblock_start = memblock_start_of_DRAM();
	memblock_end = memblock_end_of_DRAM();
}
#else /* !CONFIG_EKP_DEBUGFS_CHECK_PROT */
static inline void __init ekp_debugfs_prot_init(struct dentry *parent) {}
#endif /* CONFIG_EKP_DEBUGFS_CHECK_PROT */

void __init ekp_debugfs_sysinfo_init(struct dentry *parent)
{
	struct dentry *dentry;

	dentry = debugfs_create_dir("sysinfo", parent);
	if (IS_ERR_OR_NULL(dentry)) {
		pr_err("%s: cannot create debugfs entry\n", __func__);
		return;
	}

	ekp_debugfs_ptdump_init(dentry);
	ekp_debugfs_prot_init(dentry);
}
