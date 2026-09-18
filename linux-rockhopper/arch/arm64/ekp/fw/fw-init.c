// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2018 LG Electronics
 */

#include <linux/cpuhotplug.h>
#include <linux/cpumask.h>
#include <linux/memblock.h>
#include <linux/printk.h>
#include <linux/suspend.h>
#include <linux/syscore_ops.h>

#include <asm/cacheflush.h>
#include <asm/memory.h>
#include <asm/virt.h>

#include "private.h"

#define ekp_err(fmt, ...) \
	printk(KERN_ERR "\033[31;1m[ERROR] " fmt "\033[m\n", ##__VA_ARGS__)

#ifdef CONFIG_HIBERNATION
extern int in_suspend;
static bool in_hibernation __nosavedata = false;
#else
#define in_suspend	0
#define in_hibernation	false
#endif

/* Ascii values for string "EKP-HISE" */
static const uint64_t EKP_FW_MAGIC __initconst = 0x455349482D504B45;

static phys_addr_t init_vector __ro_after_init;

static __always_inline void ekp_dcache_flush(void *base, size_t size)
{
	unsigned long start = (unsigned long)base;
	unsigned long end = start + (unsigned long)size;

	dcache_clean_inval_poc(start, end);
}

static phys_addr_t __init calculate_ekp_ise_size(struct memory_layout *m)
{
	phys_addr_t start, end, new_start, new_end;
	phys_addr_t size = 0;
	int i;

	start = 0;
	end = 0;

	for (i = 0; i < m->count; ++i) {
		if (m->block[i].mmap_type != MMAP_TYPE_BLOCK_1G) {
			new_start = round_down(m->block[i].start, SZ_1G);
			new_end = round_up(m->block[i].end, SZ_1G);

			if ((start != new_start) || (end != new_end)) {
				start = new_start;
				end = new_end;
				size += SZ_4K;
			}
		}
	}

	start = 0;
	end = 0;

	for (i = 0; i < m->count; ++i) {
		if (m->block[i].mmap_type == MMAP_TYPE_PAGE_4K) {
			new_start = round_down(m->block[i].start, SZ_2M);
			new_end = round_up(m->block[i].end, SZ_2M);

			if ((start != new_start) || (end != new_end)) {
				start = new_start;
				end = new_end;
				size += SZ_4K;
			}
		}
	}

	size += (phys_addr_t)ekp_fw_size_kb * SZ_1K;
	size += (phys_addr_t)ekp_fw_stack_size;

	/*
	 * +------------------------+-------+----------+-------+-------+-------+
	 * | EKP ISE (.text ~ .bss) | guard | pgtables | guard | stack | guard |
	 * +------------------------+-------+----------+-------+-------+-------+
	 */
	size += SZ_4K * 3;	/* guard pages */

	return PAGE_ALIGN(size);
}

static void __init ekp_fw_relocate(phys_addr_t dest, phys_addr_t size)
{
	unsigned long src = ekp_fw_blob_start;
	phys_addr_t total_pages = size >> PAGE_SHIFT;

	while (total_pages) {
		void *to = pte_set_fixmap(dest);
		void *from = (void *)src;
		copy_page(to, from);
		ekp_dcache_flush(to, PAGE_SIZE);
		pte_clear_fixmap();
		dest += PAGE_SIZE;
		src += PAGE_SIZE;
		total_pages--;
	}
}

static void __init ekp_fw_clear(phys_addr_t base, phys_addr_t size)
{
	phys_addr_t total_pages = size >> PAGE_SHIFT;

	while (total_pages) {
		void *ptr = pte_set_fixmap(base);
		clear_page(ptr);
		pte_clear_fixmap();
		base += PAGE_SIZE;
		total_pages--;
	}
}

static noinline int __ekp_fw_init(unsigned int cpu,
				  phys_addr_t kinfo, phys_addr_t mlayout,
				  phys_addr_t ise_base, phys_addr_t ise_size)
{
	struct arm_smccc_res res;

	arm_smccc_hvc(cpu, kinfo, mlayout, ise_base, ise_size, 0, 0, 0, &res);
	if (res.a0 != 0)
		return -EPERM;

	return 0;
}

#ifdef CONFIG_HIBERNATION
static int ekp_pm_notify(struct notifier_block *nb,
			 unsigned long action, void *data)
{
	switch (action) {
	case PM_HIBERNATION_PREPARE:
		in_hibernation = true;
		ekp_tunnel(EKP_HIBERNATION, true);
		return NOTIFY_OK;
	case PM_POST_HIBERNATION:
		in_hibernation = false;
		ekp_tunnel(EKP_HIBERNATION, false);
		return NOTIFY_OK;
	default:
		break;
	}
	return NOTIFY_DONE;
}

static struct notifier_block ekp_pm_nb = {
	.notifier_call = ekp_pm_notify,
};
#endif /* CONFIG_HIBERNATION */

static int ekp_fw_suspend(void)
{
	if (in_hibernation) {
		/*
		 * In this case, the syscore_suspend() function is called
		 * at the create_image() functrion before it creates the
		 * hibernation image in kernel/power/hibernate.c file.
		 *
		 * Note that we can not use the in_suspend variable here
		 * to distinguish whether this function is called from
		 * suspend or hibernate state. Because, the in_suspend is
		 * 0 at this time, and the in_suspend is set to 1 after
		 * this function is done by the create_image() function.
		 */
		return 0;
	}

	ekp_tunnel(EKP_SUSPEND);
	return 0;
}

static void ekp_fw_resume(void)
{
	if (in_suspend) {
		/*
		 * In this case, the syscore_resume() function is called
		 * at the create_image() function after it creates the
		 * hibernation image in kernel/power/hibernate.c file.
		 *
		 * Note that we can not use the in_hibernation variable here.
		 * The in_hibernation is marked as __nosavedata assuming it
		 * will keep the resume kernel's 'false' value, but this does
		 * not happen. The in_suspend variable is used here because
		 * it is explicitly set to 0 when the kernel is resume (to
		 * avoid this problem) before this function is called.
		 */
		return;
	}

	if (init_vector == 0)
		return;

	__hyp_set_vectors(init_vector);

	if (__ekp_fw_init(smp_processor_id(), 0, 0, 0, 0) < 0)
		pr_err("%s: [ERROR] ekp-fw init failed\n", __func__);
}

static struct syscore_ops ekp_syscore_ops = {
	.suspend = ekp_fw_suspend,
	.resume = ekp_fw_resume,
};

bool __init ekp_fw_available(void)
{
	if (ekp_fw_blob_size == 0)
		return false;

	if (ekp_fw_magic != EKP_FW_MAGIC)
		return false;

	fw_ver = (unsigned int)ekp_fw_version;

	if ((ekp_fw_version & (~0xFF)) != EKP_VERSION) {
		ekp_err("%s: version mismatched (kernel: v%u.%u.x, fw: v%u.%u.%u)",
			__func__, EKP_VER_MAJOR, EKP_VER_MINOR,
			ekp_ver_major(ekp_fw_version),
			ekp_ver_minor(ekp_fw_version),
			ekp_ver_revision(ekp_fw_version));
		return false;
	}

	return true;
}

int ekp_fw_init_secondary_cpus(unsigned int cpu)
{
	int ret;

	if (init_vector == 0)
		return -EPERM;

	__hyp_set_vectors(init_vector);

	ret = __ekp_fw_init(cpu, 0, 0, 0, 0);
	if (ret < 0) {
		pr_err("%s: [ERROR] ekp-fw init failed(cpu #%d)\n", __func__, cpu);
		return ret;
	}

	return 0;
}

int __init ekp_fw_init(struct ekp_init_info *info,
		       struct ekp_debug_info *debug,
		       struct memory_layout *mlayout)
{
	phys_addr_t size = calculate_ekp_ise_size(mlayout);
	phys_addr_t reloc_base;
	int ret;

	if (WARN_ON(size < ekp_fw_blob_size)) {
		ekp_err("%s: EKP-HISE runtime size is not enough!", __func__);
		return -ENOMEM;
	}

	reloc_base = memblock_phys_alloc(size, SZ_2M);
	if (reloc_base == 0) {
		ekp_err("%s: memblock allocation failed!", __func__);
		return -ENOMEM;
	}

	ekp_fw_relocate(reloc_base, (phys_addr_t)ekp_fw_blob_size);
	init_vector = reloc_base + SZ_4K;

	ekp_dcache_flush(mlayout, sizeof(struct memory_layout));
	ekp_dcache_flush(info, sizeof(struct ekp_init_info));
	if (info->debug)
		ekp_dcache_flush(debug, sizeof(struct ekp_debug_info));

	__hyp_set_vectors(init_vector);

	ret = __ekp_fw_init(smp_processor_id(), __pa_symbol(info),
			    __pa_symbol(mlayout), reloc_base, size);
	if (ret < 0) {
		ekp_err("%s: EKP firmware init failed!", __func__);
		ekp_fw_clear(reloc_base, size);
		memblock_phys_free(reloc_base, size);
		return ret;
	}

#ifdef CONFIG_HIBERNATION
	ret = register_pm_notifier(&ekp_pm_nb);
	if (ret < 0) {
		ekp_fw_clear(reloc_base, size);
		memblock_phys_free(reloc_base, size);
		return ret;
	}
#endif

	register_syscore_ops(&ekp_syscore_ops);

	return 0;
}
