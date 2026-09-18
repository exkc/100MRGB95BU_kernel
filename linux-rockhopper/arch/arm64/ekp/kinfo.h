/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2017 LG Electronics
 */

#ifndef __ARM64_EKP_KINFO_H
#define __ARM64_EKP_KINFO_H

/*
 * Kernel information useful for debugging EKP
 */
struct ekp_debug_info {
	/* special pages*/
	phys_addr_t empty_zero_page;
	phys_addr_t bm_pud;
	phys_addr_t bm_pmd;
	phys_addr_t bm_pte;
	unsigned long ptrs_pud;
	unsigned long ptrs_pmd;
	unsigned long ptrs_pte;
	unsigned long nr_bm_pte_table;

	/* virtual addresses */
	unsigned long vmalloc_start;
	unsigned long vmalloc_end;
	unsigned long fixaddr_top;
	unsigned long fixaddr_start;
	unsigned long pci_io_start;
	unsigned long pci_io_end;
	unsigned long vmemmap_end;

	/* kernel image offset */
	uint64_t kimage_vaddr;
} __packed;

/*
 * EKP initial information for kernel interface
 */
struct ekp_init_info {
	/* page tables */
	uint32_t idmap_pg_dir_size;
	phys_addr_t idmap_pg_dir;
	phys_addr_t tramp_pg_dir;
	phys_addr_t swapper_pg_dir;
	phys_addr_t init_pg_dir;
	phys_addr_t init_pg_end;

	/* kernel read-only range */
	phys_addr_t kernel_ro_start;
	phys_addr_t kernel_ro_end;
	phys_addr_t ekp_rodata_start;
	phys_addr_t ekp_rodata_end;

	/* virtual addresses */
	unsigned long vmemmap_start;
	unsigned long kexec_crash_image;

	/* romem information */
	phys_addr_t romem_start;
	phys_addr_t romem_end;
	phys_addr_t protected_block_bitmap;
	phys_addr_t forced_ro_bitmap;
	phys_addr_t memblock_memory_bitmap;
	phys_addr_t module_bitmap;
	phys_addr_t ropages_bitmap;

	/* physical Offset */
	phys_addr_t phys_offset;

	/* kernel image offset */
	uint64_t kimage_voffset;
	uint64_t vabits;

	/* credentials */
	uint32_t cred_size;
	uint32_t cred_ext_offset;
	uint32_t cred_override_offset;
	uint32_t cred_security_offset;

	/* page table level */
	uint32_t pgtable_level;

	/* LSE atomics */
	uint32_t lse_atomics;

	/* system_state information */
	uint64_t system_state;
	uint32_t system_suspend;

	/* memblock end pfn */
	unsigned long pfn_end;

	/* etc. */
	phys_addr_t panic_cpu;
	phys_addr_t hyp_stub_vectors;

	/* ekp_debug_info physical address */
	phys_addr_t debug;
} __packed;

enum {
	MEMFLAG_NORMAL = 0,
	MEMFLAG_SECURE = 1,
};

enum {
	MMAP_TYPE_BLOCK_1G = 0,
	MMAP_TYPE_BLOCK_2M,
	MMAP_TYPE_PAGE_4K,
};

#define MAX_MEMORY_BLOCK	(CONFIG_EKP_MAX_MEMBLOCK_COUNT)

struct memory_block_info {
	phys_addr_t start;
	phys_addr_t end;
	unsigned int flag;
	unsigned int mmap_type;
};

struct memory_layout {
	unsigned int count;
	struct memory_block_info block[MAX_MEMORY_BLOCK];
};

extern struct ekp_init_info ekp_info;
extern char __hyp_stub_vectors[];

#endif /* __ARM64_EKP_KINFO_H */
