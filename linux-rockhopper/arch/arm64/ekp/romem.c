// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2023 LG Electronics
 */

#define pr_fmt(fmt) "ekp:romem: " fmt

#include <linux/kernel.h>
#include <linux/memblock.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/ekp.h>

#include <asm/kernel-pgtable.h>
#include <asm/ekp/init.h>
#include <asm/ekp/mm.h>

#include "private.h"

struct reserved_romem_stat {
	phys_addr_t start;
	phys_addr_t end;
	phys_addr_t free_page_base;
};

struct ro_page {
	unsigned long addr;
	unsigned int order;
	phys_addr_t bitmap;
} ____cacheline_aligned;

struct romem_bitmaps {
	phys_addr_t forced_ro_bitmap;
	phys_addr_t memblock_memory_bitmap;
	phys_addr_t module_bitmap;
	phys_addr_t ropages_bitmap;
};

#define ROMEM_BITMAPS_NUM \
	(sizeof(struct romem_bitmaps) / sizeof(unsigned long *))

static unsigned long *ekp_ropages_bitmap __ro_after_init;

#ifdef CONFIG_EKP_DEBUGFS_CHECK_PROT
static unsigned long *ekp_module_bitmap __ro_after_init;
#endif

static struct reserved_romem_stat reserved_romem __initdata;
static struct romem_bitmaps romem_bitmaps __initdata;
static phys_addr_t protected_block_bitmap __initdata;

/*
 * Calculate the number of pages in the page table mapped to the linear memory.
 */
static phys_addr_t __init count_lm_pgtable_pages(phys_addr_t start,
						 phys_addr_t end)
{
	phys_addr_t size;
	phys_addr_t total_pages = 0;

	size = round_up(end, PGDIR_SIZE) - round_down(start, PGDIR_SIZE);
	total_pages += size >> PGDIR_SHIFT;

	if (CONFIG_PGTABLE_LEVELS > 3) {
		size = round_up(end, PUD_SIZE) - round_down(start, PUD_SIZE);
		total_pages += size >> PUD_SHIFT;
	}

	size = round_up(end, PMD_SIZE) - round_down(start, PMD_SIZE);
	total_pages += size >> PMD_SHIFT;

	return total_pages;
}

/*
 * Calculate the number of pages in the page table mapped to vmemmap area,
 * which consists of the array of 'struct page'.
 *
 * Currently, the EKP only supports pages in 4KB granularity, so we assume that
 * vmemmap area mpas 2MB block because of 'ARM64_SWAPPER_USES_SECTION_MAPS = 1'.
 */
static phys_addr_t __init count_vmemmap_pgtable_pages(phys_addr_t start,
						      phys_addr_t end)
{
	phys_addr_t size;
	phys_addr_t total_pages = 0;

	size = round_up(end, PGDIR_SIZE) - round_down(start, PGDIR_SIZE);
	total_pages += size >> PGDIR_SHIFT;

	if (CONFIG_PGTABLE_LEVELS > 3) {
		size = round_up(end, PUD_SIZE) - round_down(start, PUD_SIZE);
		total_pages += size >> PUD_SHIFT;
	}

	if (!IS_ENABLED(CONFIG_ARM64_4K_PAGES)) {
		size = round_up(end, PMD_SIZE) - round_down(start, PMD_SIZE);
		total_pages += size >> PMD_SHIFT;
	}

	return total_pages;
}

static inline phys_addr_t __init get_page_tables_size(void)
{
	phys_addr_t start = memblock_start_of_DRAM();
	phys_addr_t end = memblock_end_of_DRAM();
	phys_addr_t total_pages = 1;	/* 1 is for a guard page */

	total_pages += count_lm_pgtable_pages(start, end);
	total_pages += count_vmemmap_pgtable_pages(start, end);

	return total_pages << PAGE_SHIFT;
}

#if defined(CONFIG_EKP_SYSMEM_PHYS_BASE) && (CONFIG_EKP_SYSMEM_PHYS_BASE != 0)
static __always_inline phys_addr_t phys_to_offset(phys_addr_t phys)
{
	if (phys >= CONFIG_EKP_SYSMEM_PHYS_BASE)
		return phys - CONFIG_EKP_SYSMEM_PHYS_BASE;

	return phys;
}

static __always_inline unsigned long phys_to_pfn_offset(phys_addr_t phys)
{
	return __phys_to_pfn(phys_to_offset(phys));
}

static __always_inline unsigned long virt_to_pfn_offset(unsigned long addr)
{
	return __phys_to_pfn(phys_to_offset(__virt_to_phys(addr)));
}

#define SYSTEM_PHYS_BASE_PFN	(__phys_to_pfn(CONFIG_EKP_SYSMEM_PHYS_BASE))

static __always_inline unsigned long page_to_pfn_offset(struct page *page)
{
	unsigned long pfn = page_to_pfn(page);

	if (pfn >= SYSTEM_PHYS_BASE_PFN)
		return pfn - SYSTEM_PHYS_BASE_PFN;

	return pfn;
}
#else	/* !CONFIG_EKP_SYSMEM_PHYS_BASE || CONFIG_EKP_SYSMEM_PHYS_BASE == 0 */
static __always_inline phys_addr_t phys_to_offset(phys_addr_t phys)
{
	return phys;
}

static __always_inline unsigned long phys_to_pfn_offset(phys_addr_t phys)
{
	return __phys_to_pfn(phys);
}

static __always_inline unsigned long virt_to_pfn_offset(unsigned long addr)
{
	return virt_to_pfn((const void *)addr);
}

static __always_inline unsigned long page_to_pfn_offset(struct page *page)
{
	return page_to_pfn(page);
}
#endif

/*
 *  |<----  __bitmap_size() ---->|
 *  +--------------------+-------+--------------------+-------+
 *  |      bitmap[]      | guard |      bitmap[]      | guard | ...
 *  +--------------------+-------+--------------------+-------+
 */
static inline phys_addr_t __init __bitmap_size(phys_addr_t size,
					       phys_addr_t shift)
{
	phys_addr_t end = phys_to_offset(memblock_end_of_DRAM());
	phys_addr_t len = BITS_TO_LONGS(round_up(end, size) >> shift);

	return round_up(len * sizeof(unsigned long), PAGE_SIZE) + PAGE_SIZE;
}

static inline phys_addr_t __init get_bitmaps_size(void)
{
	phys_addr_t size;

	size = PAGE_SIZE; /* for the first guard page */
	size += __bitmap_size(PAGE_SIZE, PAGE_SHIFT) * ROMEM_BITMAPS_NUM;
	size += __bitmap_size(PMD_SIZE, PMD_SHIFT);

	return size;
}

static void __init bitmaps_init(phys_addr_t base, phys_addr_t size)
{
	phys_addr_t total_pages = size >> PAGE_SHIFT;
	phys_addr_t bitmap_size = __bitmap_size(PAGE_SIZE, PAGE_SHIFT);
	phys_addr_t phys = base;

	while (total_pages) {
		void *ptr = pte_set_fixmap(phys);
		clear_page(ptr);
		pte_clear_fixmap();
		phys += PAGE_SIZE;
		total_pages--;
	}

	phys = base + PAGE_SIZE;

	romem_bitmaps.forced_ro_bitmap = phys;
	phys += bitmap_size;

	romem_bitmaps.memblock_memory_bitmap = phys;
	phys += bitmap_size;

	romem_bitmaps.module_bitmap = phys;
#ifdef CONFIG_EKP_DEBUGFS_CHECK_PROT
	ekp_module_bitmap = __va(phys);
#endif
	phys += bitmap_size;

	romem_bitmaps.ropages_bitmap = phys;
	ekp_ropages_bitmap = __va(phys);
	phys += bitmap_size;

	protected_block_bitmap = phys;
}

int __init romem_reserve(void)
{
	phys_addr_t bitmaps_size = get_bitmaps_size();
	phys_addr_t base, total_size;

	total_size = bitmaps_size + get_page_tables_size();

	base = memblock_phys_alloc_range(total_size, PAGE_SIZE, 0,
					 MEMBLOCK_ALLOC_NOLEAKTRACE);
	if (base == 0) {
		pr_crit("%s: cannot allocate read-only memory pool "
			"(size:0x%llx)\n",
			__func__, total_size);
		return -ENOMEM;
	}

	reserved_romem.start = base;
	reserved_romem.end = base + total_size;
	reserved_romem.free_page_base = base + bitmaps_size;

	bitmaps_init(base, bitmaps_size);

	return 0;
}

static void __init empty_bitmap_init(phys_addr_t base, phys_addr_t size)
{
	phys_addr_t total_pages = size >> PAGE_SHIFT;
	phys_addr_t phys = base;

	while (total_pages) {
		void *ptr = pte_set_fixmap(phys);
		clear_page(ptr);
		pte_clear_fixmap();
		phys += PAGE_SIZE;
		total_pages--;
	}

	phys = base + PAGE_SIZE;
	ekp_ropages_bitmap = __va(phys);
}

void __init empty_bitmap_reserve(void)
{
	phys_addr_t size = __bitmap_size(PAGE_SIZE, PAGE_SHIFT) + PAGE_SIZE;
	phys_addr_t base;

	base = memblock_phys_alloc_range(size, PAGE_SIZE, 0,
					 MEMBLOCK_ALLOC_NOLEAKTRACE);
	if (base == 0) {
		pr_crit("%s: cannot allocate bitmaps (size:0x%llx)\n",
			__func__, size);
		return;
	}

	empty_bitmap_init(base, size);
}

void __init romem_free(void)
{
	memblock_phys_free(reserved_romem.start,
			   reserved_romem.end - reserved_romem.start);
}

void __init get_romem_info(struct ekp_init_info *info)
{
	info->romem_start = reserved_romem.start;
	info->romem_end = reserved_romem.end;
	info->protected_block_bitmap = protected_block_bitmap;
	info->forced_ro_bitmap = romem_bitmaps.forced_ro_bitmap;
	info->memblock_memory_bitmap = romem_bitmaps.memblock_memory_bitmap;
	info->module_bitmap = romem_bitmaps.module_bitmap;
	info->ropages_bitmap = romem_bitmaps.ropages_bitmap;
}

bool arch_ekp_pa_readonly(phys_addr_t addr)
{
	return test_bit(phys_to_pfn_offset(addr), ekp_ropages_bitmap);
}

bool arch_ekp_va_readonly(unsigned long addr)
{
	return test_bit(virt_to_pfn_offset(addr), ekp_ropages_bitmap);
}

bool arch_ekp_page_readonly(struct page *page)
{
	return test_bit(page_to_pfn_offset(page), ekp_ropages_bitmap);
}

#ifdef CONFIG_EKP_DEBUGFS_CHECK_PROT
bool ekp_within_module_area(phys_addr_t phys)
{
	return test_bit(phys_to_pfn_offset(phys), ekp_module_bitmap);
}
#endif

phys_addr_t __init ekp_romem_phys_alloc(phys_addr_t size)
{
	phys_addr_t phys = reserved_romem.free_page_base;
	BUG_ON(!phys);

	if (WARN(!PAGE_ALIGNED(size), "size is not page-aligned.\n"))
		size = round_up(size, PAGE_SIZE);

	if (likely((phys + size) <= reserved_romem.end)) {
		reserved_romem.free_page_base += size;
		return phys;
	}

	pr_crit("%s: not enough reserved read-only memory. "
		"(size = 0x%016llx)\n", __func__, size);

	return 0;
}

void __init ekp_mark_primary_memory_ro(void)
{
	if (IS_ENABLED(CONFIG_EKP) && ekp_enabled()) {
		phys_addr_t start = reserved_romem.start;
		phys_addr_t size = reserved_romem.end - start;

		ekp_mark_rodata_ro();
		ekp_mark_init_pg_dir_ro();
		ekp_mark_reserved_romem_ro(start, size);
	}
}

static __always_inline int mark_pages_ro(struct page *page, unsigned int order)
{
	struct ro_page ro_page;

	ro_page.addr = (unsigned long)page_address(page);
	ro_page.order = order;
	ro_page.bitmap = __pa(ekp_ropages_bitmap);

	return ekp_tunnel(EKP_SET_ROMEM, (uint64_t)&ro_page);
}

static __always_inline int mark_pages_rw(struct page *page, unsigned int order)
{
	struct ro_page ro_page;

	ro_page.addr = ~((unsigned long)(page_address(page)));
	ro_page.order = order;
	ro_page.bitmap = __pa(ekp_ropages_bitmap);

	return ekp_tunnel(EKP_SET_ROMEM, (uint64_t)&ro_page);
}

static __always_inline struct page *ekp_alloc_romem_pages_noprof(
					gfp_t gfp_mask, unsigned int order)
{
	struct page *page;

	page = alloc_pages_noprof(gfp_mask & ~__GFP_ZERO, order);
	if (!page)
		return NULL;

	/* Read-only pages must be initialized to zero in EKP f/w. */
	if (unlikely(mark_pages_ro(page, compound_order(page)) < 0)) {
		__free_pages(page, compound_order(page));
		return NULL;
	}

	/* Ensure the zeroing is observed by page table walks. */
	dsb(ishst);

	return page;
}

void __init arch_ekp_kasan_page_ro(void* addr)
{
	struct ro_page ro_page;

	ro_page.addr = (unsigned long)addr;
	ro_page.order = 0;
	ro_page.bitmap = __pa(ekp_ropages_bitmap);

	ekp_tunnel(EKP_SET_ROMEM, (uint64_t)&ro_page);
}

#define ekp_alloc_romem_pages(...) \
	alloc_hooks(ekp_alloc_romem_pages_noprof(__VA_ARGS__))

static __always_inline void ekp_free_romem_pages(struct page *page,
						 unsigned int order)
{
	/* Read-only pages must be initialized to zero in EKP f/w. */
	if (unlikely(mark_pages_rw(page, compound_order(page)) < 0))
		return;

	__free_pages(page, compound_order(page));
}

struct page *arch_ekp_alloc_ro_pages_noprof(gfp_t gfp_mask, unsigned int order)
{
	return ekp_alloc_romem_pages_noprof(gfp_mask, order);
}

unsigned long __arch_ekp_get_free_ro_pages(gfp_t gfp_mask, unsigned int order)
{
	struct page *page;

	page = ekp_alloc_romem_pages(gfp_mask & ~__GFP_HIGHMEM, order);
	if (!page)
		return 0;

	return (unsigned long)page_address(page);
}

void __arch_ekp_free_ro_pages(struct page *page, unsigned int order)
{
	ekp_free_romem_pages(page, order);
}

void arch_ekp_free_ro_pages(unsigned long addr, unsigned int order)
{
	if (addr != 0) {
		VM_BUG_ON(!virt_addr_valid((void *)addr));
		ekp_free_romem_pages(virt_to_page((void *)addr), order);
	}
}

void * __ref vmemmap_alloc_ro_block_zero(unsigned long size)
{
	if (slab_is_available()) {
		gfp_t gfp_mask = GFP_KERNEL|__GFP_RETRY_MAYFAIL|__GFP_NOWARN;
		struct page *page;

		/*
		 * The page is initialized to zero by EKP f/w
		 */
		page = ekp_alloc_romem_pages(gfp_mask, get_order(size));
		if (!page)
			return NULL;

		return page_address(page);
	} else {
		phys_addr_t phys = ekp_romem_phys_alloc(size);
		if (unlikely(!phys))
			return NULL;

		arch_ekp_romemset_zero(phys, size);
		return __va(phys);
	}
}
