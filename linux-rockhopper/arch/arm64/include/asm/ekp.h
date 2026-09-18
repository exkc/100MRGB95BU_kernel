/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2017 LG Electronics
 */

#ifndef __ASM_EKP_H
#define __ASM_EKP_H

#include <asm/ekp_ops.h>
#include <asm/ekp/cmd.h>

#ifndef __ASSEMBLY__
#ifdef CONFIG_EKP

extern void * __ref vmemmap_alloc_ro_block_zero(unsigned long size);

__FORTIFY_INLINE bool arch_ekp_enabled(void)
{
	extern bool ekp_ise_enabled;
	return ekp_ise_enabled;
}

__FORTIFY_INLINE void arch_ekp_romemset_zero(phys_addr_t addr,
					     unsigned long size)
{
	ekp_tunnel(EKP_CLEAR_ROMEM, addr, size);
}

__FORTIFY_INLINE void arch_ekp_cred_init(const phys_addr_t ro_cred, const phys_addr_t cred,
					 const void *ext, const bool override)
{
	ekp_tunnel(EKP_CRED_INIT, ro_cred, cred,
		   (unsigned long)ext, (unsigned long)override);
}

__FORTIFY_INLINE void arch_ekp_slab_set_fp(phys_addr_t addr, void *fp, void *p,
					   unsigned long random,
					   unsigned long ptr_addr)
{
	ekp_tunnel(EKP_SLAB_SET_FP, addr, (unsigned long)fp, (unsigned long)p,
		   random, ptr_addr);
}

__FORTIFY_INLINE void * __meminit arch_ekp_vmemmap_alloc_block_zero(
						unsigned long size, int node)
{
	return vmemmap_alloc_ro_block_zero(size);
}

#ifndef CONFIG_EKP_CRED_PROTECTION
__FORTIFY_INLINE bool arch_ekp_cred_validcaller(void) { return true; }
#endif

__FORTIFY_INLINE void arch_ekp_perf_begin(int ekp_cmd) {}
__FORTIFY_INLINE void arch_ekp_perf_end(int ekp_cmd) {}

#endif	/* CONFIG_EKP */
#endif	/* !__ASSEMBLY__ */

#endif	/* __ASM_EKP_H */
