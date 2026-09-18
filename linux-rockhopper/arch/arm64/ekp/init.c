// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2018 LG Electronics
 */

#define pr_fmt(fmt) "ekp: " fmt

#include <linux/cma.h>
#include <linux/cpumask.h>
#include <linux/memblock.h>
#include <linux/kexec.h>
#include <linux/panic.h>

#include <asm/pgtable.h>
#include <asm/kernel-pgtable.h>
#include <asm/ekp/init.h>

#include "private.h"

bool ekp_ise_enabled __ro_after_init = false;

static struct ekp_debug_info ekp_debug __initdata;
struct ekp_init_info ekp_info __initdata;
static struct memory_layout ekp_memlayout __initdata __aligned(PAGE_SIZE);
static struct memory_block_info ekp_mblock[MAX_MEMORY_BLOCK] __initdata;

#define CMA_MEMBLOCK_REGIONS	128
struct memblock_region cma_regions[CMA_MEMBLOCK_REGIONS] __initdata __aligned(PAGE_SIZE);

static int feature_enabled __initdata = 1;

static int __init feature_enable(char *str)
{
	if (!IS_ENABLED(CONFIG_EKP_FORCE_ENABLE)) {
		bool enabled;

		if (kstrtobool(str, &enabled) < 0)
			return 0;

		feature_enabled = enabled ? 1 : 0;
	}

	return 0;
}
early_param("ekp", feature_enable);

#ifdef CONFIG_EKP_CRED_PROTECTION
#define ekp_cred_offset(x)	offsetof(struct cred, x)
#else
#define ekp_cred_offset(x)	0
#endif

static void __init init_ekp_info(void)
{
	struct ekp_init_info *info = &ekp_info;

	memset(info, 0, sizeof(struct ekp_init_info));

	/* page tables */
	info->idmap_pg_dir_size = PAGE_SIZE;
	info->idmap_pg_dir = __pa_symbol(idmap_pg_dir);
#ifdef CONFIG_UNMAP_KERNEL_AT_EL0
	info->tramp_pg_dir = __pa_symbol(tramp_pg_dir);
#endif
	info->swapper_pg_dir = __pa_symbol(swapper_pg_dir);
	info->init_pg_dir = __pa_symbol(init_pg_dir);
	info->init_pg_end = __pa_symbol(init_pg_end);

	/* kernel read-only range */
	info->kernel_ro_start = __pa_symbol(_stext);
	info->kernel_ro_end = __pa_symbol(__init_begin);
	info->ekp_rodata_start = __pa_symbol(__ekp_rodata_start);
	info->ekp_rodata_end = __pa_symbol(__ekp_rodata_end);

	/* virtual addresses */
	info->vmemmap_start = VMEMMAP_START;
#ifdef CONFIG_KEXEC_CORE
	info->kexec_crash_image = (unsigned long)&kexec_crash_image;
#endif

	/* romem information */
	get_romem_info(info);

	/* physical offset */
	info->phys_offset = PHYS_OFFSET;

	/* kernel offset */
	info->kimage_voffset = kimage_voffset;
	info->vabits = vabits_actual;

	/* credentials */
	info->cred_size = sizeof(struct cred);
	if (IS_ENABLED(CONFIG_EKP_CRED_PROTECTION)) {
		info->cred_ext_offset = ekp_cred_offset(ext);
		info->cred_override_offset = ekp_cred_offset(override);
	}
	if (IS_ENABLED(CONFIG_SECURITY)) {
		info->cred_security_offset = offsetof(struct cred, security);
	}

	/* page table level */
	info->pgtable_level = CONFIG_PGTABLE_LEVELS;

	/* LSE atomics */
	info->lse_atomics = IS_ENABLED(CONFIG_ARM64_LSE_ATOMICS);

	/* system_state information */
	info->system_state = __pa_symbol(&system_state);
	info->system_suspend = SYSTEM_SUSPEND;

	/* memblock end pfn */
	info->pfn_end = __phys_to_pfn(memblock_end_of_DRAM());

	/* etc. */
	info->panic_cpu = __pa_symbol(&panic_cpu);
	info->hyp_stub_vectors = __pa_symbol(__hyp_stub_vectors);

	/* ekp_debug_info physical address */
	info->debug = __pa_symbol(&ekp_debug);
}

static void __init init_ekp_debug(void)
{
	struct ekp_debug_info *debug = &ekp_debug;

	/* special pages*/
	debug->empty_zero_page = __pa_symbol(empty_zero_page);
	debug->bm_pud = __pa_symbol(bm_pud);
	debug->bm_pmd = __pa_symbol(bm_pmd);
	debug->bm_pte = __pa_symbol(bm_pte);
	debug->ptrs_pud = PTRS_PER_PUD;
	debug->ptrs_pmd = PTRS_PER_PMD;
	debug->ptrs_pte = PTRS_PER_PTE;
	debug->nr_bm_pte_table = NR_BM_PTE_TABLES;

	/* virtual addresses */
	debug->vmalloc_start = VMALLOC_START;
	debug->vmalloc_end = VMALLOC_END;
	debug->fixaddr_top = FIXADDR_TOP;
	debug->fixaddr_start = FIXADDR_START;
	debug->pci_io_start = PCI_IO_START;
	debug->pci_io_end = PCI_IO_END;
	debug->vmemmap_end = VMEMMAP_START + VMEMMAP_SIZE;

	/* kernel image offset */
	debug->kimage_vaddr = (u64)&_text;
}

static int __init ekp_check_cma_range(struct cma *cma, void *data)
{
	struct memblock_type *type = (struct memblock_type *)data;
	struct memblock_region *region;
	phys_addr_t base, size;
	int nid;

	BUG_ON(type->cnt >= type->max);

	base = cma_get_base(cma);
	size = cma_get_size(cma);
	nid = memory_add_physaddr_to_nid(base);

	if (type->cnt > 0) {
		region = &type->regions[type->cnt - 1];
		if (base == (region->base + region->size)) {
			region->size += size;
			type->total_size += size;
			return 0;
		}
	}

	region = &type->regions[type->cnt];
	region->base = base;
	region->size = size;
	region->flags = MEMBLOCK_NONE;
	memblock_set_region_node(region, nid);
	type->cnt++;
	type->total_size += size;

	return 0;
}

static void __init memblock_cma_setup(struct memblock_type *type,
				      struct memblock_region *regions,
				      int max)
{
	type->cnt = 0;
	type->max = max;
	type->name = "cma";
	type->total_size = 0;
	type->regions = regions;

	memset(regions, 0, sizeof(struct memblock_region) * max);

	cma_for_each_area(ekp_check_cma_range, type);
}

#define for_each_mem_range_except_type(i, type, p_start, p_end)		 \
	__for_each_mem_range(i, &memblock.memory, type, NUMA_NO_NODE,	 \
			     MEMBLOCK_HOTPLUG | MEMBLOCK_DRIVER_MANAGED, \
			     p_start, p_end, NULL)

static __always_inline void __init __memlayout_setup(struct memory_layout *m,
						     phys_addr_t end,
						     phys_addr_t *base,
						     phys_addr_t *size,
						     phys_addr_t granule,
						     unsigned int flag,
						     unsigned int mmap_type)
{
	if (WARN_ON(m->count >= CONFIG_EKP_MAX_MEMBLOCK_COUNT)) {
		pr_err("Increase CONFIG_EKP_MAX_MEMBLOCK_COUNT\n");
		return;
	}

	m->block[m->count].start = *base;
	m->block[m->count].end = round_down(end, granule);
	m->block[m->count].flag = flag;
	m->block[m->count].mmap_type = mmap_type;

	*base = m->block[m->count].end;
	*size = end - (*base);

	m->count++;
}

static void __init memlayout_setup(struct memory_layout *m, phys_addr_t start,
				   phys_addr_t end, unsigned int flag)
{
	phys_addr_t base = start;
	phys_addr_t size = end - start;

	if (size >= SZ_1G) {
		__memlayout_setup(m, end, &base, &size, SZ_1G,
				  flag, MMAP_TYPE_BLOCK_1G);
	}

	if (size >= SZ_2M) {
		__memlayout_setup(m, end, &base, &size, SZ_2M,
				  flag, MMAP_TYPE_BLOCK_2M);
	}

	if (size > 0) {
		__memlayout_setup(m, end, &base, &size, SZ_4K,
				  flag, MMAP_TYPE_PAGE_4K);
	}
}

static void __init memory_layout_info_setup(struct memory_layout *m,
					    struct memory_block_info *block)
{
	phys_addr_t start = block->start;
	phys_addr_t end = block->end;
	phys_addr_t boundary;
	unsigned int flag = block->flag;

	if (IS_ALIGNED(start, SZ_1G)) {
		memlayout_setup(m, start, end, flag);
		return;
	}

	if (IS_ALIGNED(start, SZ_2M)) {
		boundary = round_up(start, SZ_1G);

		if (boundary < end) {
			memlayout_setup(m, start, boundary, flag);
			memlayout_setup(m, boundary, end, flag);
		} else {
			memlayout_setup(m, start, end, flag);
		}
		return;
	}

	boundary = round_up(block->start, SZ_2M);

	if (boundary < end) {
		memlayout_setup(m, start, boundary, flag);

		start = boundary;
		boundary = round_up(start, SZ_1G);

		if (boundary < end) {
			memlayout_setup(m, start, boundary, flag);
			memlayout_setup(m, boundary, end, flag);
		} else {
			memlayout_setup(m, start, end, flag);
		}
	} else {
		memlayout_setup(m, start, end, flag);
	}
}

static void __init init_memory_layout(void)
{
	struct memory_layout *m = &ekp_memlayout;
	phys_addr_t start, end;
	struct memblock_type cma;
	uint64_t i;
	int n, cnt = 0;

	memblock_cma_setup(&cma, cma_regions, CMA_MEMBLOCK_REGIONS);

	for_each_mem_range_except_type(i, &cma, &start, &end) {
		BUG_ON(!PAGE_ALIGNED(start));
		BUG_ON(!PAGE_ALIGNED(end));

		if (start >= end)
			break;

		if (WARN_ON(cnt >= CONFIG_EKP_MAX_MEMBLOCK_COUNT)) {
			pr_err("Increase CONFIG_EKP_MAX_MEMBLOCK_COUNT\n");
			break;
		}

		if (cnt > 0) {
			if (ekp_mblock[cnt - 1].end >= start) {
				ekp_mblock[cnt - 1].end = end;
				continue;
			}
		}

		ekp_mblock[cnt].start = start;
		ekp_mblock[cnt].end = end;
		ekp_mblock[cnt].flag = MEMFLAG_NORMAL;
		cnt++;
	}

	for (n = 0; n < cnt; ++n)
		memory_layout_info_setup(m, &ekp_mblock[n]);

	for (n = 0; n < m->count; ++n) {
		pr_info("memlayout[%02u]:0x%08llx-0x%08llx (flag=%d, mmap_type=%d)\n",
			n, m->block[n].start, m->block[n].end,
			m->block[n].flag, m->block[n].mmap_type);
	}
}

void __init ekp_init(void)
{
	if (!feature_enabled)
		goto ekp_init_error;

	if (!is_hyp_mode_available()) {
		pr_err("Not all CPU(s) started at EL2.\n");
		pr_err("To enable EKP, all CPU(s) must be started at EL2.\n");
		goto ekp_init_error;
	}

	if (is_kernel_in_hyp_mode()) {
		pr_err("EKP not available with VHE.\n");
		goto ekp_init_error;
	}

	if (!ekp_fw_available()) {
		pr_err("EKP firmware is not available.\n");
		goto ekp_init_error;
	}

	if (romem_reserve() < 0)
		goto ekp_init_error;

	init_ekp_info();
	init_ekp_debug();
	init_memory_layout();

	if (ekp_fw_init(&ekp_info, &ekp_debug, &ekp_memlayout) < 0) {
		romem_free();
		goto ekp_init_error;
	}

	ekp_ise_enabled = true;

	return;

ekp_init_error:
	empty_bitmap_reserve();
}

int ekp_secondary_cpu_init(unsigned int cpu)
{
	if (!ekp_ise_enabled)
		return 0;
	return ekp_fw_init_secondary_cpus(cpu);
}

static __always_inline void bug_not_support_vhe(void)
{
	pr_emerg("***********************************************************\n");
	pr_emerg("*** Add bootargs 'kvm-arm.mode=nvhe' to kernel cmdline! ***\n");
	pr_emerg("*** To enable EKP, kernel must be running in NVHE mode. ***\n");
	pr_emerg("*** However, kernel is running in VHE mode currently.   ***\n");
	pr_emerg("***********************************************************\n");
	BUG();
}

static __always_inline void note_rodataoff_ignore(void)
{
	pr_emerg("**********************************************************\n");
	pr_emerg("*** CONFIG_EKP=y, it ignores the 'rodata=off' bootarg. ***\n");
	pr_emerg("**********************************************************\n");
}

static int __init ekp_post_init(void)
{
	if (is_kernel_in_hyp_mode())
		bug_not_support_vhe();

	if (arm64_test_sw_feature_override(ARM64_SW_FEATURE_OVERRIDE_RODATA_OFF))
		note_rodataoff_ignore();

	if (ekp_enabled()) {
		ekp_tunnel(EKP_POST_INIT, MODULE_BASE, MODULE_END,
			   (u64)__ekp_machine_kexec);
	}

	return 0;
}
subsys_initcall_sync(ekp_post_init);
