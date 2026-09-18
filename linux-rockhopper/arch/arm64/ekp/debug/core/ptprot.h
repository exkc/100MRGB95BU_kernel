/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __EKP_DEBUG_CORE_PTPROT_H
#define __EKP_DEBUG_CORE_PTPROT_H

#include <linux/const.h>

#include <asm/pgtable.h>
#include <asm/sysreg.h>

#define PGTABLE_APTABLE_RO	(_AT(u64, 1) << 62)
#define PGTABLE_APTABLE_NOUSR	(_AT(u64, 1) << 61)
#define PGTABLE_UXNTABLE	(_AT(u64, 1) << 60)
#define PGTABLE_PXNTABLE	(_AT(u64, 1) << 59)

#define PROT_BITS(_mask, _val, _set, _clear)	\
{						\
	.mask	= _mask,			\
	.val	= _val,				\
	.set	= _set,				\
	.clear	= _clear,			\
}

#define PROT_ATTRINDX(indx, set)	\
	PROT_BITS(PTE_ATTRINDX_MASK, PTE_ATTRINDX(indx), set, NULL)

struct prot_bits {
	u64 mask;
	u64 val;
	const char *set;
	const char *clear;
};

static const struct prot_bits table_prot_bits[] = {
	PROT_BITS(PTE_VALID, PTE_VALID, " ", "F"),
	PROT_BITS(PTE_TABLE_BIT, PTE_TABLE_BIT, "TABLE", "     "),
	PROT_BITS(PGTABLE_APTABLE_NOUSR, PGTABLE_APTABLE_NOUSR, "KNL", "   "),
	PROT_BITS(PGTABLE_APTABLE_RO, PGTABLE_APTABLE_RO, "ro", "  "),
	PROT_BITS(PGTABLE_PXNTABLE, PGTABLE_PXNTABLE, "PXN", "---"),
	PROT_BITS(PGTABLE_UXNTABLE, PGTABLE_UXNTABLE, "UXN", "---"),
};

static const struct prot_bits page_prot_bits[] = {
	PROT_BITS(PTE_VALID, PTE_VALID, " ", "F"),
	PROT_BITS(PTE_TABLE_BIT, PTE_TABLE_BIT, "PAGE ", "BLOCK"),
	PROT_BITS(PTE_USER, PTE_USER, "USR", "   "),
	PROT_BITS(PTE_RDONLY, PTE_RDONLY, "ro", "RW"),
	PROT_BITS(PTE_PXN, PTE_PXN, "PXN", "px-"),
	PROT_BITS(PTE_UXN, PTE_UXN, "UXN", "ux-"),
	PROT_BITS(PTE_SHARED, PTE_SHARED, "SHD", "   "),
	PROT_BITS(PTE_AF, PTE_AF, "AF", "  "),
	PROT_BITS(PTE_NG, PTE_NG, "NG", "  "),
	PROT_BITS(PTE_CONT, PTE_CONT, "CON", "   "),
	PROT_BITS(PTE_GP, PTE_GP, "GP", "   "),
	PROT_ATTRINDX(MT_DEVICE_nGnRnE, "DEVICE/nGnRnE"),
	PROT_ATTRINDX(MT_DEVICE_nGnRE, "DEVICE/nGnRE"),
	PROT_ATTRINDX(MT_NORMAL_NC, "MEM/NORMAL-NC"),
	PROT_ATTRINDX(MT_NORMAL, "MEM/NORMAL"),
	PROT_ATTRINDX(MT_NORMAL_TAGGED, "MEM/NORMAL-TAGGED"),
};

#define block_prot_bits		page_prot_bits

/*
 * Check HPD0 and HPD1 bits of TCR_EL1 register.
 *
 * HPD0, bit[41]: Hierarchical Permission Disables for TTBR0_EL1
 * HPD1, bit[42]: Hierarchical Permission Disables for TTBR1_EL1
 *
 *
 * If HPD{0,1} bit set to 1 then APTable, PXNTable, and UXNTable are ignored.
 */
static __always_inline bool is_set_hpd0(void)
{
	if ((read_sysreg(tcr_el1) & TCR_HPD0) == TCR_HPD0)
		return true;

	return false;
}

static __always_inline bool is_set_hpd1(void)
{
	if ((read_sysreg(tcr_el1) & TCR_HPD1) == TCR_HPD1)
		return true;

	return false;
}

extern bool check_pgtable_bad(struct mm_struct *mm);
extern bool check_pgtable_ro(struct mm_struct *mm);
extern bool check_pgtable_ro_using_bitmap(struct mm_struct *mm);
extern bool check_pgtable_pxn(struct mm_struct *mm);
extern bool check_pgtable_uxn(struct mm_struct *mm);
extern bool check_pgtable_no_el0(struct mm_struct *mm);

extern int check_kaddr_prot(unsigned long addr, u64 page_mask,
			    u64 table_mask, bool lockless);

static __always_inline bool kaddr_nomap_lockless(unsigned long addr)
{
	if (check_kaddr_prot(addr, 0ULL, 0ULL, true) == -EFAULT)
		return true;

	return false;
}

static __always_inline bool kaddr_nomap(unsigned long addr)
{
	if (check_kaddr_prot(addr, 0ULL, 0ULL, false) == -EFAULT)
		return true;

	return false;
}

static __always_inline bool kaddr_ro_lockless(unsigned long addr)
{
	if (check_kaddr_prot(addr, PTE_RDONLY, PGTABLE_APTABLE_RO, true) == 1)
		return true;

	return false;
}

static __always_inline bool kaddr_ro(unsigned long addr)
{
	if (check_kaddr_prot(addr, PTE_RDONLY, PGTABLE_APTABLE_RO, false) == 1)
		return true;

	return false;
}

static __always_inline bool kaddr_pxn_lockless(unsigned long addr)
{
	if (check_kaddr_prot(addr, PTE_PXN, PGTABLE_PXNTABLE, true) == 1)
		return true;

	return false;
}

static __always_inline bool kaddr_pxn(unsigned long addr)
{
	if (check_kaddr_prot(addr, PTE_PXN, PGTABLE_PXNTABLE, false) == 1)
		return true;

	return false;
}

static __always_inline bool kaddr_uxn_lockless(unsigned long addr)
{
	if (check_kaddr_prot(addr, PTE_UXN, PGTABLE_UXNTABLE, true) == 1)
		return true;

	return false;
}

static __always_inline bool kaddr_uxn(unsigned long addr)
{
	if (check_kaddr_prot(addr, PTE_UXN, PGTABLE_UXNTABLE, false) == 1)
		return true;

	return false;
}

static __always_inline bool kaddr_el0_lockless(unsigned long addr)
{
	if (check_kaddr_prot(addr, PTE_USER, PGTABLE_APTABLE_NOUSR, true) == 1)
		return true;

	return false;
}

static __always_inline bool kaddr_el0(unsigned long addr)
{
	if (check_kaddr_prot(addr, PTE_USER, PGTABLE_APTABLE_NOUSR, false) == 1)
		return true;

	return false;
}

#endif /* __EKP_DEBUG_CORE_PTPROT_H */
