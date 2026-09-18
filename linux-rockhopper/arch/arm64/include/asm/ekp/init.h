/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2017 LG Electronics
 */

#ifndef __ASM_EKP_INIT_H
#define __ASM_EKP_INIT_H

#ifndef __ASSEMBLY__
#include <linux/types.h>

#ifdef CONFIG_EKP

extern void __init ekp_init(void);
extern void __init ekp_mark_primary_memory_ro(void);
extern void __init ekp_mark_rodata_ro(void);
extern void __init ekp_mark_init_pg_dir_ro(void);
extern void __init ekp_mark_reserved_romem_ro(phys_addr_t start,
					      phys_addr_t size);
extern int ekp_secondary_cpu_init(unsigned int cpu);

#else /* !CONFIG_EKP */

static inline void __init ekp_init(void) {}
static inline void __init ekp_mark_primary_memory_ro(void) {}
static inline void __init ekp_mark_rodata_ro(void) {}
static inline void __init ekp_mark_reserved_romem_ro(phys_addr_t start,
						     phys_addr_t size) {}
static inline int ekp_secondary_cpu_init(unsigned int cpu) { return 0; }

#endif /* CONFIG_EKP */

#ifdef CONFIG_EKP_MODULE_PROTECTION
extern uint64_t __init ekp_module_base(void);
#else
static inline uint64_t ekp_module_base(void) { return 0; }
#endif

#endif /* !__ASSEMBLY__*/

#endif /* __ASM_EKP_INIT_H */
