// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2023 LG Electronics
 */
#include <linux/cpu.h>
#include <linux/cpumask.h>
#include <linux/debugfs.h>
#include <linux/err.h>
#include <linux/memblock.h>
#include <linux/mm.h>
#include <linux/sched/mm.h>
#include <linux/sched/signal.h>
#include <linux/sched/task.h>
#include <linux/slab.h>
#include <linux/smp.h>
#include <linux/uaccess.h>
#include <linux/vmalloc.h>
#include <linux/set_memory.h>
#include <asm/page.h>

#include "debugfs.h"
#include "core/ptmanip.h"
#include "core/ptprot.h"

struct smp_test_result {
	bool passed;
};

static struct cpumask test_target_mask;

/*
 * /sys/kernel/debug/ekp/tests/target_cpus
 *
 * Set the target CPU list to test.
 *
 * CPU list format examples
 *   range
 *     0-4,9          ==> 0, 1, 2, 3, 4, 9
 *     0-2,7,12-14    ==> 0, 1, 2, 7, 12, 13, 14
 *   range:used_size/group_size
 *     0-1023:2/125   ==> 0, 1, 256, 257, 512, 513, 768, 769
 *   "none"           ==> clean test_target_mask
 */
static int target_cpus_show(struct seq_file *m)
{
	seq_printf(m, "EKP Test Target CPUs :");

	if (cpumask_empty(&test_target_mask)) {
		seq_printf(m, " none\n");
	} else {
		int cpu, last;

		last = cpumask_last(&test_target_mask);

		for_each_cpu(cpu, &test_target_mask) {
			if (cpu != last)
				seq_printf(m, " %d,", cpu);
			else
				seq_printf(m, " %d\n", cpu);
		}
	}

	return 0;
}

static int target_cpus_store(const char __user *buf, size_t size)
{
	struct cpumask tmp;
	char *str;
	int ret;

	str = kmalloc(size, GFP_KERNEL);
	if (!str)
		return -ENOMEM;

	if (copy_from_user(str, buf, size)) {
		kfree(str);
		return -EFAULT;
	}

	if (strncmp(str, "none", 4) == 0) {
		cpumask_clear(&test_target_mask);
		kfree(str);
		return 0;
	}

	cpumask_clear(&tmp);
	ret = cpulist_parse(str, &tmp);
	kfree(str);

	if (ret < 0 || cpumask_last(&tmp) >= nr_cpu_ids) {
		pr_err("[ERROR] Incorrect CPU range, possible 0-%u\n",
		       nr_cpu_ids - 1);
		return -EINVAL;
	}

	if (!cpumask_and(&test_target_mask, &tmp, cpu_present_mask)) {
		pr_err("[ERROR] No present CPU range\n");
		return -EINVAL;
	}

	return 0;
}

DEFINE_EKP_DEBUGFS_RW(target_cpus);

static void do_ekp_tunnel(void *info)
{
	struct smp_test_result *result = (struct smp_test_result *)info;
	int ret = ekp_tunnel(EKP_TEST_HVC_HANDLER);

	if (ret == 0)
		result->passed = true;
	else
		result->passed = false;
}

/*
 * /sys/kernel/debug/ekp/tests/cpu_ekp_tunnel
 *
 * Check whether ekp_tunnel() is working on given CPUs by target_cpus file.
 */
static int cpu_ekp_tunnel_show(struct seq_file *m)
{
	struct smp_test_result *result;
	int cpu;

	result = kzalloc(nr_cpu_ids, GFP_KERNEL);
	if (!result)
		return -ENOMEM;

	preempt_disable();
	for_each_cpu(cpu, &test_target_mask) {
		if (!cpu_online(cpu))
			cpu_device_up(get_cpu_device(cpu));

		smp_call_function_single(cpu, do_ekp_tunnel, &result[cpu], 1);
	}
	preempt_enable();

	for_each_cpu(cpu, &test_target_mask) {
		seq_printf(m, "CPU-%d: %s\n",
			   cpu, result[cpu].passed ? "passed" : "FAILED");
	}

	kfree(result);
	return 0;
}

DEFINE_EKP_DEBUGFS_RO(cpu_ekp_tunnel);

/*
 * /sys/kernel/debug/ekp/tests/vmalloc_test
 *
 * Allocate memory of a given size as a vmalloc.
 *
 * This is used to find bugs in the policy used by EKP F/W when
 * mapping new memory allocated by vmalloc into page tables.
 */
static int vmalloc_test_store(const char __user *buf, size_t size)
{
	void *buffer = NULL;
	unsigned long size_mb;
	int ret;

	ret = kstrtoul_from_user(buf, size, 0, &size_mb);
	if (ret < 0)
		return -EINVAL;

	pr_emerg("[EKP TEST] start to vmalloc (size: %ld MB)\n", size_mb);

	buffer = vmalloc(SZ_1M * size_mb);
	if (!buffer) {
		pr_emerg("[EKP TEST] failure of vmalloc()\n");
		return 0;
	}

	vfree(buffer);
	pr_emerg("[EKP TEST] done of vmalloc (size: %ld MB)\n", size_mb);

	return 0;
}

DEFINE_EKP_DEBUGFS_WO(vmalloc_test);

/*
 * /sys/kernel/debug/ekp/tests/vmalloc_ro
 *
 * Allocate or free read-only memory of a given page count as a vmalloc.
 *
 * This is used to find bugs in the policy used by EKP F/W when mapping
 * read-only memory allocated by vmalloc into page tables.
 */
static void *buffer_ro = NULL;
static unsigned int ropage_count;

static int vmalloc_ro_store(const char __user *buf, size_t size)
{
	unsigned int count;
	int ret;

	ret = kstrtouint_from_user(buf, size, 0, &count);
	if (ret < 0)
		return -EINVAL;

	if (count == 0) {
		if (buffer_ro) {
			pr_emerg("[EKP TEST] free read-only vmalloc\n");
			set_memory_rw((unsigned long)buffer_ro, ropage_count);
			vfree(buffer_ro);
			buffer_ro = NULL;
			ropage_count = count;
		}
	} else {
		if (!buffer_ro) {
			pr_emerg("[EKP TEST] allocate read-only vmalloc"
				 " (%d %s)\n",
				 count, count > 1 ? "pages" : "page");
			buffer_ro = vmalloc(PAGE_SIZE * count);
			set_memory_ro((unsigned long)buffer_ro, count);
			ropage_count = count;
		} else {
			pr_emerg("[EKP TEST] already allocated\n");
		}
	}

	return 0;
}

DEFINE_EKP_DEBUGFS_WO(vmalloc_ro);

static struct ekp_debugfs_attr ekp_test_helper_attrs[] __initdata = {
	{
		.name = "target_cpus",
		.ops = &target_cpus,
	},
	{
		.name = "cpu_ekp_tunnel",
		.ops = &cpu_ekp_tunnel,
	},
	{
		.name = "vmalloc_test",
		.ops = &vmalloc_test,
	},
	{
		.name = "vmalloc_ro",
		.ops = &vmalloc_ro,
	},
};

#ifdef CONFIG_EKP_DEBUGFS_TEST_AGAINST_ATTACK
static pid_t ekp_test_target_pid;
static unsigned long ekp_test_target_vaddr;

/*
 * /sys/kernel/debug/ekp/tests/target_pid
 *
 * Set or show the PID of target process to test.
 */
static int target_pid_show(struct seq_file *m)
{
	seq_printf(m, "%d\n", ekp_test_target_pid);
	return 0;
}

static int target_pid_store(const char __user *buf, size_t size)
{
	int pid, ret;

	ret = kstrtoint_from_user(buf, size, 0, &pid);
	if (ret < 0)
		return ret;

	if (pid <= 0)
		ekp_test_target_pid = 0;
	else
		ekp_test_target_pid = pid;

	return 0;
}

DEFINE_EKP_DEBUGFS_RW(target_pid);

/*
 * /sys/kernel/debug/ekp/tests/target_vaddr
 *
 * Set or show the virtual address of target page memory to test.
 * This virtual address will be rounded down to PAGE_SIZE.
 *
 * Note that 0 means null in this test, so a test will be skipped.
 */
static int target_vaddr_show(struct seq_file *m)
{
	if (ekp_test_target_vaddr == 0)
		seq_printf(m, "null\n");
	else
		seq_printf(m, "0x%016lx\n", ekp_test_target_vaddr);

	return 0;
}

static int target_vaddr_store(const char __user *buf, size_t size)
{
	unsigned long addr;
	int ret;

	ret = kstrtoul_from_user(buf, size, 0, &addr);
	if (ret < 0)
		return ret;

	ekp_test_target_vaddr = round_down(addr, PAGE_SIZE);

	return 0;
}

DEFINE_EKP_DEBUGFS_RW(target_vaddr);

/*
 * /sys/kernel/debug/ekp/tests/rw64_target_vaddr
 *
 * Read/write 64-bit size from/to the target_vaddr.
 */
static int rw64_target_vaddr_show(struct seq_file *m)
{
	uint64_t *p = (uint64_t *)ekp_test_target_vaddr;

	seq_printf(m, "0x%016llx\n", *p);

	return 0;
}

static int rw64_target_vaddr_store(const char __user *buf, size_t size)
{
	uint64_t *p = (uint64_t *)ekp_test_target_vaddr;
	uint64_t val;
	int ret;

	ret = kstrtoull_from_user(buf, size, 0, &val);
	if (ret < 0)
		return ret;

	*p = val;

	return 0;
}

DEFINE_EKP_DEBUGFS_RW(rw64_target_vaddr);

/*
 * /sys/kernel/debug/ekp/tests/execute_sc
 *
 * Show the result after trying to execute the shellcode where the target_vaddr.
 */
static int test_execute_sc_show(struct seq_file *m)
{
	void *mem = (void *)ekp_test_target_vaddr;

	ekp_ptm_execute_shellcode(mem);
	seq_printf(m, "Succeed to execute the shellcode\n");

	return 0;
}

DEFINE_EKP_DEBUGFS_RO(test_execute_sc);

/*
 * /sys/kernel/debug/ekp/tests/ptdump
 *
 * Show the contents of page tables for target_vaddr of target_pid.
 */
static int test_ptdump_show(struct seq_file *m)
{
	unsigned long vaddr = ekp_test_target_vaddr;
	pid_t pid = ekp_test_target_pid;
	struct task_struct *task = NULL;
	struct mm_struct *mm = NULL;

	if (vaddr == 0) {
		pr_emerg("[ERROR] target_vaddr is null\n");
		return 0;
	}

	if (pid != 0) {
		task = find_get_task_by_vpid(pid);
		if (!task)
			return -ESRCH;

		mm = get_task_mm(task);
		if (!mm) {
			put_task_struct(task);
			return -EFAULT;
		}

		task_lock(task);
		seq_printf(m, "[user: v.%016lx]\n", vaddr);
	} else {
		mm = &init_mm;
		seq_printf(m, "[kernel: v.%016lx]\n", vaddr);
	}

	ekp_ptm_pgtable_dump(m, mm, vaddr, PGTABLE_LEVEL_ALL);

	if (pid != 0) {
		task_unlock(task);
		mmput(mm);
		put_task_struct(task);
	}

	return 0;
}

DEFINE_EKP_DEBUGFS_RO(test_ptdump);

static int read_page_table(struct seq_file *m, int level)
{
	unsigned long vaddr = ekp_test_target_vaddr;
	pid_t pid = ekp_test_target_pid;
	struct task_struct *task = NULL;
	struct mm_struct *mm = NULL;
	int ret = 0;

	if (vaddr == 0) {
		pr_emerg("[ERROR] target_vaddr is null\n");
		return 0;
	}

	if (pid != 0) {
		task = find_get_task_by_vpid(pid);
		if (!task)
			return -ESRCH;

		mm = get_task_mm(task);
		if (!mm) {
			put_task_struct(task);
			return -EFAULT;
		}

		task_lock(task);
		seq_printf(m, "[user: v.%016lx]\n", vaddr);
	} else {
		mm = &init_mm;
		seq_printf(m, "[kernel: v.%016lx]\n", vaddr);
	}

	ekp_ptm_pgtable_dump(m, mm, vaddr, level);

	if (pid != 0) {
		task_unlock(task);
		mmput(mm);
		put_task_struct(task);
	}

	return ret;
}

static phys_addr_t memblock_start __ro_after_init;
static phys_addr_t memblock_end __ro_after_init;

static inline bool within_physmem(phys_addr_t addr)
{
	if ((addr < memblock_start) || (addr >= memblock_end))
		return false;

	return true;
}

static int change_page_table(const char __user *buf, size_t size, int level)
{
	pid_t pid = ekp_test_target_pid;
	unsigned long vaddr = ekp_test_target_vaddr;
	struct task_struct *task = NULL;
	struct mm_struct *mm = NULL;
	char str[256];
	int ret = 0;

	struct ptmanip_req req = {
		.phys_addr = 0,
		.set_mask = __pgprot(0),
		.clear_mask = __pgprot(0),
		.current_prot = __pgprot(0),
	};

	if (vaddr == 0) {
		pr_emerg("[ERROR] target_vaddr is null\n");
		return 0;
	}

	if (size > 256)
		return -EINVAL;

	if (copy_from_user(str, buf, size))
		return -EINVAL;

	strreplace(str, '\n', '\0');

	if (pid != 0) {
		task = find_get_task_by_vpid(pid);
		if (!task)
			return -ESRCH;

		mm = get_task_mm(task);
		if (!mm) {
			put_task_struct(task);
			return -EFAULT;
		}

		task_lock(task);
	} else {
		mm = &init_mm;
	}

	if (ekp_ptm_option_valid(str)) {
		ekp_parse_ptm_option(mm, vaddr, level, str, &req);

		if (!req.remap || within_physmem(req.phys_addr)) {
			if (ekp_ptm_pgtable_change(mm, &req, vaddr, level) < 0)
				pr_emerg("FAILED\n");
			else
				pr_emerg("succeeded\n");
		} else {
			pr_emerg("[ERROR] phys address must be within ");
			pr_cont("[0x%016llx, 0x%016llx)\n",
				memblock_start, memblock_end);
		}
	} else {
		ret = -EINVAL;
	}

	if (pid != 0) {
		task_unlock(task);
		mmput(mm);
		put_task_struct(task);
	}

	return ret;
}

/*
 * /sys/kernel/debug/ekp/tests/pgd
 *
 * Set or show the current PGD value for target_vaddr of target_pid.
 */
static int test_pgd_show(struct seq_file *m)
{
	return read_page_table(m, PGTABLE_LEVEL_PGD);
}

static int test_pgd_store(const char __user *buf, size_t size)
{
	return change_page_table(buf, size, PGTABLE_LEVEL_PGD);
}

DEFINE_EKP_DEBUGFS_RW(test_pgd);

#ifndef __PAGETABLE_P4D_FOLDED
/*
 * /sys/kernel/debug/ekp/tests/p4d
 *
 * Set or show the current P4D value for target_vaddr of target_pid.
 */
static int test_p4d_show(struct seq_file *m)
{
	return read_page_table(m, PGTABLE_LEVEL_P4D);
}

static int test_p4d_store(const char __user *buf, size_t size)
{
	return change_page_table(buf, size, PGTABLE_LEVEL_P4D);
}

DEFINE_EKP_DEBUGFS_RW(test_p4d);
#endif /* !__PAGETABLE_P4D_FOLDED */

#ifndef __PAGETABLE_PUD_FOLDED
/*
 * /sys/kernel/debug/ekp/tests/pud
 *
 * Set or show the current PUD value for target_vaddr of target_pid.
 */
static int test_pud_show(struct seq_file *m)
{
	return read_page_table(m, PGTABLE_LEVEL_PUD);
}

static int test_pud_store(const char __user *buf, size_t size)
{
	return change_page_table(buf, size, PGTABLE_LEVEL_PUD);
}

DEFINE_EKP_DEBUGFS_RW(test_pud);
#endif /* !__PAGETABLE_PUD_FOLDED */

#ifndef __PAGETABLE_PMD_FOLDED
/*
 * /sys/kernel/debug/ekp/tests/pmd
 *
 * Set or show the current PMD value for target_vaddr of target_pid.
 */
static int test_pmd_show(struct seq_file *m)
{
	return read_page_table(m, PGTABLE_LEVEL_PMD);
}

static int test_pmd_store(const char __user *buf, size_t size)
{
	return change_page_table(buf, size, PGTABLE_LEVEL_PMD);
}

DEFINE_EKP_DEBUGFS_RW(test_pmd);
#endif /* !__PAGETABLE_PMD_FOLDED */

/*
 * /sys/kernel/debug/ekp/tests/pte
 *
 * Set or show the current PTE value for target_vaddr of target_pid.
 */
static int test_pte_show(struct seq_file *m)
{
	return read_page_table(m, PGTABLE_LEVEL_PTE);
}

static int test_pte_store(const char __user *buf, size_t size)
{
	return change_page_table(buf, size, PGTABLE_LEVEL_PTE);
}

DEFINE_EKP_DEBUGFS_RW(test_pte);

static struct ekp_debugfs_attr ekp_test_against_attack_attrs[] __initdata = {
	{
		.name = "target_pid",
		.ops = &target_pid,
	},
	{
		.name = "target_vaddr",
		.ops = &target_vaddr,
	},
	{
		.name = "rw64_target_vaddr",
		.ops = &rw64_target_vaddr,
	},
	{
		.name = "execute_sc",
		.ops = &test_execute_sc,
	},
	{
		.name = "ptdump",
		.ops = &test_ptdump,
	},
	{
		.name = "pgd",
		.ops = &test_pgd,
	},
#ifndef __PAGETABLE_P4D_FOLDED
	{
		.name = "p4d",
		.ops = &test_p4d,
	},
#endif
#ifndef __PAGETABLE_PUD_FOLDED
	{
		.name = "pud",
		.ops = &test_pud,
	},
#endif
#ifndef __PAGETABLE_PMD_FOLDED
	{
		.name = "pmd",
		.ops = &test_pmd,
	},
#endif
	{
		.name = "pte",
		.ops = &test_pte,
	},
};
#endif /* CONFIG_EKP_DEBUGFS_TEST_AGAINST_ATTACK */

void __init ekp_debugfs_test_helpers_init(struct dentry *parent)
{
	struct dentry *dentry;

	dentry = debugfs_create_dir("tests", parent);
	if (IS_ERR_OR_NULL(dentry)) {
		pr_err("%s: cannot create debugfs entry\n", __func__);
		return;
	}

	ekp_debugfs_create(dentry, ekp_test_helper_attrs);

#ifdef CONFIG_EKP_DEBUGFS_TEST_AGAINST_ATTACK
	ekp_debugfs_create(dentry, ekp_test_against_attack_attrs);

	memblock_start = memblock_start_of_DRAM();
	memblock_end = memblock_end_of_DRAM();
#endif
}
