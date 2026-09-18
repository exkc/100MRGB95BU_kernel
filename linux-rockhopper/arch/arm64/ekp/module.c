// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2018 LG Electronics
 */

#include <linux/module.h>
#include <linux/vmalloc.h>

#include <asm/ekp/cmd.h>

void arch_ekp_module_protection_prepare(const void *mod)
{
	/*
	 * Get rid of potentially aliasing lazily unmapped vm areas that may
	 * have permissions set that deviate from the ones we are setting here.
	 */
	vm_unmap_aliases();

	ekp_tunnel(EKP_LKMP_PREPARE,
		   (unsigned long)mod,
		   offsetof(struct module, mem),
		   0,
		   sizeof(struct module_memory));
}

void arch_ekp_module_protection_enable(const void *mod)
{
	/*
	 * Get rid of potentially aliasing lazily unmapped vm areas that may
	 * have permissions set that deviate from the ones we are setting here.
	 */
	vm_unmap_aliases();

	ekp_tunnel(EKP_LKMP_ENABLE,
		   (unsigned long)mod,
		   offsetof(struct module, mem),
		   0,
		   sizeof(struct module_memory));
}

void arch_ekp_module_protection_after_init(const void *mod)
{
	/*
	 * Get rid of potentially aliasing lazily unmapped vm areas that may
	 * have permissions set that deviate from the ones we are setting here.
	 */
	vm_unmap_aliases();

	ekp_tunnel(EKP_LKMP_AFTER_INIT,
		   (unsigned long)mod,
		   offsetof(struct module, mem),
		   0,
		   sizeof(struct module_memory));
}

void arch_ekp_module_protection_disable(const void *mod)
{
	/*
	 * Get rid of potentially aliasing lazily unmapped vm areas that may
	 * have permissions set that deviate from the ones we are setting here.
	 */
	vm_unmap_aliases();

	ekp_tunnel(EKP_LKMP_DISABLE,
		   (unsigned long)mod,
		   offsetof(struct module, mem),
		   0,
		   sizeof(struct module_memory));
}

void arch_ekp_module_protection_disable_init(const void *mod)
{
	/*
	 * Get rid of potentially aliasing lazily unmapped vm areas that may
	 * have permissions set that deviate from the ones we are setting here.
	 */
	vm_unmap_aliases();

	ekp_tunnel(EKP_LKMP_DISABLE_INIT,
		   (unsigned long)mod,
		   offsetof(struct module, mem),
		   0,
		   sizeof(struct module_memory));
}

void arch_ekp_module_protection_disable_core(const void *mod)
{
	/*
	 * Get rid of potentially aliasing lazily unmapped vm areas that may
	 * have permissions set that deviate from the ones we are setting here.
	 */
	vm_unmap_aliases();

	ekp_tunnel(EKP_LKMP_DISABLE_CORE,
		   (unsigned long)mod,
		   offsetof(struct module, mem),
		   0,
		   sizeof(struct module_memory));
}
