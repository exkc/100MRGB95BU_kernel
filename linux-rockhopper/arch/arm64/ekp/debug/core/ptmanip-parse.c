// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2023 LG Electronics
 */

#include <linux/string.h>
#include <asm/pgtable.h>

#include "ptmanip.h"
#include "ptprot.h"

#define __PTMPROT_BITS(_name, _set, _clear)	\
{						\
	.name		= _name,		\
	.set_mask	= _set,			\
	.clear_mask	= _clear,		\
}

#define PTMPROT_SET(_name, _set)	__PTMPROT_BITS(_name, _set, 0)
#define PTMPROT_CLEAR(_name, _clear)	__PTMPROT_BITS(_name, 0, _clear)

struct ptm_prot_bits {
	const char *name;
	u64 set_mask;
	u64 clear_mask;
};

static const char *ptm_prot[] = {
	"t", "table", "b", "block",
	"ro", "rw", "user", "nouser",
	"pxn", "uxn", "xn", "nx", "px", "ux", "x",
};

static const struct ptm_prot_bits table_ptm_prot_bits[] = {
	PTMPROT_SET("t", PTE_TABLE_BIT),
	PTMPROT_SET("table", PTE_TABLE_BIT),
	PTMPROT_SET("ro", PGTABLE_APTABLE_RO),
	PTMPROT_SET("nouser", PGTABLE_APTABLE_NOUSR),
	PTMPROT_SET("pxn", PGTABLE_PXNTABLE),
	PTMPROT_SET("uxn", PGTABLE_UXNTABLE),
	PTMPROT_SET("xn", PGTABLE_PXNTABLE | PGTABLE_UXNTABLE),
	PTMPROT_SET("nx", PGTABLE_PXNTABLE | PGTABLE_UXNTABLE),
	PTMPROT_CLEAR("rw", PGTABLE_APTABLE_RO),
	PTMPROT_CLEAR("user", PGTABLE_APTABLE_NOUSR),
	PTMPROT_CLEAR("px", PGTABLE_PXNTABLE),
	PTMPROT_CLEAR("ux", PGTABLE_UXNTABLE),
	PTMPROT_CLEAR("x", PGTABLE_PXNTABLE | PGTABLE_UXNTABLE),
	__PTMPROT_BITS(NULL, 0, 0),
};

static const struct ptm_prot_bits block_ptm_prot_bits[] = {
	PTMPROT_SET("ro", PTE_RDONLY),
	PTMPROT_SET("user", PTE_USER),
	PTMPROT_SET("pxn", PTE_PXN),
	PTMPROT_SET("uxn", PTE_UXN),
	PTMPROT_SET("xn", PTE_PXN | PTE_UXN),
	PTMPROT_SET("nx", PTE_PXN | PTE_UXN),
	PTMPROT_CLEAR("b", PTE_TABLE_BIT),
	PTMPROT_CLEAR("block", PTE_TABLE_BIT),
	PTMPROT_CLEAR("rw", PTE_RDONLY),
	PTMPROT_CLEAR("nouser", PTE_USER),
	PTMPROT_CLEAR("px", PTE_PXN),
	PTMPROT_CLEAR("ux", PTE_UXN),
	PTMPROT_CLEAR("x", PTE_PXN | PTE_UXN),
	__PTMPROT_BITS(NULL, 0, 0),
};

static const struct ptm_prot_bits page_ptm_prot_bits[] = {
	PTMPROT_SET("ro", PTE_RDONLY),
	PTMPROT_SET("user", PTE_USER),
	PTMPROT_SET("pxn", PTE_PXN),
	PTMPROT_SET("uxn", PTE_UXN),
	PTMPROT_SET("xn", PTE_PXN | PTE_UXN),
	PTMPROT_SET("nx", PTE_PXN | PTE_UXN),
	PTMPROT_CLEAR("rw", PTE_RDONLY),
	PTMPROT_CLEAR("nouser", PTE_USER),
	PTMPROT_CLEAR("px", PTE_PXN),
	PTMPROT_CLEAR("ux", PTE_UXN),
	PTMPROT_CLEAR("x", PTE_PXN | PTE_UXN),
	PTMPROT_CLEAR("nouser", PTE_USER),
	__PTMPROT_BITS(NULL, 0, 0),
};

static int count_ptm_option(const char *str)
{
	char *s = (char *)str;
	int count = 1;

	while (1) {
		s = strchr(s, '/');
		if (!s)
			break;
		++s;
		++count;
	}

	return count;
}

static inline bool __parse_u64_str(const char *str,
				   const char *prefix, u64 *val)
{
	char buf[17];
	char *s;
	size_t len;
	int ret;

	s = strstr(str, prefix);
	if (!s)
		return false;

	s += strlen(prefix);
	len = strcspn(s, "/");
	strncpy(buf, s, len);
	buf[len] = '\0';

	ret = kstrtoull(buf, 16, val);
	if (ret < 0)
		return false;

	return true;
}

static bool parse_prot_str(const char *str, u64 *val)
{
	u64 desc;

	if (__parse_u64_str(str, "0x", &desc)) {
		*val = desc & ~PTE_ADDR_MASK;
		return true;
	}

	return false;
}

static bool parse_phys_str(const char *str, phys_addr_t *addr)
{
	u64 val;

	if (__parse_u64_str(str, "0x", &val)) {
		*addr = __pte_to_phys(__pte(val));
		return true;
	}

	return __parse_u64_str(str, "p.", addr);
}

static bool parse_str(const char *str, const char *opt)
{
	while (*str) {
		if (!strncmp(str, opt, strlen(opt))) {
			str += strlen(opt);
			if (!*str || *str == '/')
				return true;
		}

		while (*str && *str != '/')
			++str;

		if (*str == '/')
			++str;
	}

	return false;
}

static inline void __parse_prot(const char *str, struct ptmanip_req *req,
				const struct ptm_prot_bits *prot_bits)
{
	const struct ptm_prot_bits *bits;

	for (bits = prot_bits; bits->name != NULL; ++bits) {
		if (parse_str(str, bits->name)) {
			pgprot_val(req->set_mask) |= bits->set_mask;
			pgprot_val(req->clear_mask) |= bits->clear_mask;
		}
	}
}

static void parse_table_prot(const char *str, struct ptmanip_req *req)
{
	__parse_prot(str, req, table_ptm_prot_bits);
}

static void parse_block_prot(const char *str, struct ptmanip_req *req)
{
	__parse_prot(str, req, block_ptm_prot_bits);
}

static void parse_page_prot(const char *str, struct ptmanip_req *req)
{
	__parse_prot(str, req, page_ptm_prot_bits);
}

static void __parse_pxd_option(const char *str,
			       struct ptmanip_req *req,
			       u64 phys_mask)
{
	phys_addr_t phys;
	u64 val;

	if (parse_phys_str(str, &phys)) {
		req->phys_addr = phys & phys_mask;
		req->remap = true;
	} else {
		req->remap = false;
	}

	if (count_ptm_option(str) == 1) {
		if (parse_prot_str(str, &val)) {
			req->set_mask = __pgprot(val);
			req->clear_mask = __pgprot(~0ULL);
			return;
		}
	}

	if (parse_str(str, "t") || parse_str(str, "table")) {
		parse_table_prot(str, req);
		return;
	}

	if (parse_str(str, "b") || parse_str(str, "block")) {
		parse_block_prot(str, req);
		return;
	}

	if ((pgprot_val(req->current_prot) & PTE_TABLE_BIT) == PTE_TABLE_BIT) {
		parse_table_prot(str, req);
		return;
	}

	parse_block_prot(str, req);
}

static inline void parse_pgd_option(const char *str, struct ptmanip_req *req)
{
	__parse_pxd_option(str, req, PGDIR_MASK);
}

static inline void parse_p4d_option(const char *str, struct ptmanip_req *req)
{
	__parse_pxd_option(str, req, P4D_MASK);
}

static inline void parse_pud_option(const char *str, struct ptmanip_req *req)
{
	__parse_pxd_option(str, req, PUD_MASK);
}

static inline void parse_pmd_option(const char *str, struct ptmanip_req *req)
{
	__parse_pxd_option(str, req, PMD_MASK);
}

static void parse_pte_option(const char *str, struct ptmanip_req *req)
{
	phys_addr_t phys;
	u64 val;

	if (parse_phys_str(str, &phys)) {
		req->phys_addr = phys & PAGE_MASK;
		req->remap = true;
	} else {
		req->remap = false;
	}

	if (count_ptm_option(str) == 1) {
		if (parse_prot_str(str, &val)) {
			req->set_mask = __pgprot(val);
			req->clear_mask = __pgprot(~0ULL);
			return;
		}
	}

	parse_page_prot(str, req);
}

void ekp_parse_ptm_option(struct mm_struct *mm, unsigned long addr,
			  int level, const char *str, struct ptmanip_req *req)
{
	switch (level) {
	case PGTABLE_LEVEL_PGD:
		req->current_prot = ekp_ptm_pgd_prot(mm, addr);
		parse_pgd_option(str, req);
		break;
	case PGTABLE_LEVEL_P4D:
		req->current_prot = ekp_ptm_p4d_prot(mm, addr);
		parse_p4d_option(str, req);
		break;
	case PGTABLE_LEVEL_PUD:
		req->current_prot = ekp_ptm_pud_prot(mm, addr);
		parse_pud_option(str, req);
		break;
	case PGTABLE_LEVEL_PMD:
		req->current_prot = ekp_ptm_pmd_prot(mm, addr);
		parse_pmd_option(str, req);
		break;
	case PGTABLE_LEVEL_PTE:
		req->current_prot = ekp_ptm_pte_prot(mm, addr);
		parse_pte_option(str, req);
		break;
	default:
		break;
	}
}

static inline bool __ptm_prot_unknonw(const char *str)
{
	const char *prot;
	int i = 0;
	bool found = false;

	for (i = 0; i < ARRAY_SIZE(ptm_prot); ++i) {
		prot = ptm_prot[i];

		if (strlen(str) != strlen(prot))
			continue;

		if (!strncmp(str, prot, strlen(str))) {
			found = true;
			break;
		}
	}

	return !found;
}

static bool ptm_option_unknown(const char *opt)
{
	char buf[32];
	const char *str = opt;
	size_t len;

	if (*str == '/')
		++str;

	while (*str) {
		len = strcspn(str, "/");
		if (len > 31)
			len = 31;

		strncpy(buf, str, len);
		str += len;
		buf[len] = '\0';

		if (!strncmp(buf, "p.", 2) || !strncmp(buf, "0x", 2)) {
			if (len > 18) {
				pr_emerg("[ERROR] %s is unknown\n", buf);
				return true;
			}
		} else {
			if (len > 6) {
				pr_emerg("[ERROR] %s is unknown\n", buf);
				return true;
			}

			if (__ptm_prot_unknonw(buf)) {
				pr_emerg("[ERROR] %s is unknown\n", buf);
				return true;
			}
		}

		if (*str == '/')
			++str;
	}

	return false;
}

static bool ptm_option_hex64_invalid(const char *opt)
{
	const char *prefix[] = {NULL, "p.", "0x"};
	char *str, *tmp;
	int found = 0, i;

	for (i = 1; i < 3; ++i) {
		tmp = strstr(opt, prefix[i]);
		if (tmp != NULL) {
			str = tmp;
			found += i;
		}
	}

	if (found == 0) {
		if (parse_str(opt, "t"))
			return true;
		if (parse_str(opt, "b"))
			return true;
		if (parse_str(opt, "table"))
			return true;
		if (parse_str(opt, "block"))
			return true;
		return false;
	}

	if (found == 3)
		return  true;

	str += strlen(prefix[found]);

	if (strspn(str, "0123456789abcdefABCDEF") != strcspn(str, "/"))
		return true;

	return false;
}

static bool ptm_option_type_invalid(const char *opt)
{
	if (parse_str(opt, "t") || parse_str(opt, "table")) {
		if (parse_str(opt, "b"))
			return true;
		if (parse_str(opt, "block"))
			return true;
	}

	return false;
}

static bool ptm_option_ap_invalid(const char *opt)
{
	if (parse_str(opt, "ro") && parse_str(opt, "rw"))
		return true;

	if (parse_str(opt, "user") && parse_str(opt, "nouser"))
		return true;

	return false;
}

static bool ptm_option_exec_invalid(const char *opt)
{
	if (parse_str(opt, "pxn")) {
		if (parse_str(opt, "px") || parse_str(opt, "x"))
			return true;
	}

	if (parse_str(opt, "uxn")) {
		if (parse_str(opt, "ux") || parse_str(opt, "x"))
			return true;
	}

	if (parse_str(opt, "xn") || parse_str(opt, "nx")) {
		if (parse_str(opt, "px") || parse_str(opt, "x"))
			return true;
		if (parse_str(opt, "ux") || parse_str(opt, "x"))
			return true;
	}

	return false;
}

bool ekp_ptm_option_valid(const char *str)
{
	if (strlen(str) == 0)
		return false;

	if (ptm_option_unknown(str))
		return false;

	if (ptm_option_hex64_invalid(str))
		return false;

	if (ptm_option_type_invalid(str))
		return false;

	if (ptm_option_ap_invalid(str))
		return false;

	if (ptm_option_exec_invalid(str))
		return false;

	return true;
}
