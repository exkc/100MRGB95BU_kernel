/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2017 LG Electronics
 */

#ifndef __ASM_EKP_CMD_H
#define __ASM_EKP_CMD_H

#include <linux/arm-smccc.h>

/*
 * SMCCC Function ID
 */
#define ARM_SMCCC_EKP_FUNC_ID(x)		\
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_FAST_CALL,	\
			   ARM_SMCCC_SMC_64,	\
			   ARM_SMCCC_OWNER_OEM,	\
			   (x))

#define FUNC_ISE_CALL	ARM_SMCCC_EKP_FUNC_ID(1)	// 0xC3000001U
#define FUNC_ISE_TEST	ARM_SMCCC_EKP_FUNC_ID(2)	// 0xC3000002U
#define FUNC_ISE_LVER	ARM_SMCCC_EKP_FUNC_ID(3)	// 0xC3000003U

/*
 * EKP Tunneling Commands
 */

/* EKP init & start */
#define EKP_INIT		(0x01)
#define EKP_POST_INIT		(0x02)
#define EKP_START		(0x03)

/* Page table updates */
#define EKP_SET_PGD		(0x10)
#define EKP_SET_P4D		(0x11)
#define EKP_SET_PUD		(0x12)
#define EKP_SET_PMD		(0x13)
#define EKP_SET_PTE		(0x14)

/* Creds */
#define EKP_CRED_INIT		(0x40)

/* Modules */
#define EKP_LKMP_PREPARE	(0x50)
#define EKP_LKMP_ENABLE		(0x51)
#define EKP_LKMP_AFTER_INIT	(0x52)
#define EKP_LKMP_DISABLE	(0x53)
#define EKP_LKMP_DISABLE_INIT	(0x54)
#define EKP_LKMP_DISABLE_CORE	(0x55)

/* Read-only memory */
#define EKP_SET_ROMEM		(0x61)
#define EKP_CLEAR_ROMEM		(0x62)
#define EKP_SLAB_SET_FP		(0x63)

/* Kernel debugging */
#define EKP_DBG_PUTS		(0x70)

/* Kexec crash dump */
#define EKP_KEXEC_PREPARE	(0x80)

/* Arch-specific */
#define EKP_ARCH_CMPXCHG	(0xA0)
#define EKP_ARCH_XCHG		(0xA1)

/* Snapshot & suspend */
#define EKP_HIBERNATION		(0xB0)
#define EKP_SUSPEND		(0xB1)

/* 0xE0 ~ 0xEF are reserved for debugging */
/* 0xF0 ~ 0xFE are reserved for testing/hacking */
#define EKP_TEST_HVC_HANDLER    (0xF0)

#define EKP_CMD_MAX	(0xFF)

#ifndef __ASSEMBLY__
#include <linux/init.h>

#ifdef CONFIG_EKP
extern int64_t ekp_tunnel_handler(uint64_t cmd,
				  uint64_t arg1, uint64_t arg2, uint64_t arg3,
				  uint64_t arg4, uint64_t arg5, uint64_t arg6);

#define __ekp_tunnel_0(cmd) \
	ekp_tunnel_handler(cmd, 0, 0, 0, 0, 0, 0)

#define __ekp_tunnel_1(cmd, a1) \
	ekp_tunnel_handler(cmd, a1, 0, 0, 0, 0, 0)

#define __ekp_tunnel_2(cmd, a1, a2) \
	ekp_tunnel_handler(cmd, a1, a2, 0, 0, 0, 0)

#define __ekp_tunnel_3(cmd, a1, a2, a3) \
	ekp_tunnel_handler(cmd, a1, a2, a3, 0, 0, 0)

#define __ekp_tunnel_4(cmd, a1, a2, a3, a4) \
	ekp_tunnel_handler(cmd, a1, a2, a3, a4, 0, 0)

#define __ekp_tunnel_5(cmd, a1, a2, a3, a4, a5) \
	ekp_tunnel_handler(cmd, a1, a2, a3, a4, a5, 0)

#define __VA_GENERIC_ekp_tunnel(cmd, _1, _2, _3, _4, _5, _6, x, ...) x

/*
 * ekp_tunnel(cmd, arguments)
 * Note that the number of arguments for cmd can be up to 6.
 */
#define ekp_tunnel(cmd, ...)		\
	__VA_GENERIC_ekp_tunnel(	\
		cmd,			\
		##__VA_ARGS__,		\
		ekp_tunnel_handler,	\
		__ekp_tunnel_5,		\
		__ekp_tunnel_4,		\
		__ekp_tunnel_3,		\
		__ekp_tunnel_2,		\
		__ekp_tunnel_1,		\
		__ekp_tunnel_0		\
	) (cmd, ##__VA_ARGS__)

#else /* !CONFIG_EKP */

static __always_inline int64_t ekp_tunnel(uint64_t cmd, ...) { return -EPERM; }

#endif /* CONFIG_EKP */

#endif /* !__ASSEMBLY__ */

#endif /* __ASM_EKP_CMD_H */
