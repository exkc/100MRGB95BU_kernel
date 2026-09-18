/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2017 LG Electronics
 */

#ifndef __ASM_EKP_DEBUG_H
#define __ASM_EKP_DEBUG_H

#ifdef p_fmt
#undef p_fmt
#endif

#define p_fmt(fmt) "ekp[" fmt "] "

#ifdef CONFIG_EKP_KERNEL_DEBUG_IN_ISE

#define DBG_RED	"\x1b[31m"
#define DBG_GRN	"\x1b[32m"
#define DBG_YEL	"\x1b[33m"
#define DBG_BLU	"\x1b[34m"
#define DBG_PUR	"\x1b[35m"
#define DBG_CYN	"\x1b[36m"
#define DBG_GRY	"\x1b[37m"
#define DBG_NON	"\x1b[0m"

extern void ekp_dbgprint(const char *fmt, ...);

#else /* !CONFIG_EKP_KERNEL_DEBUG_IN_ISE */

#define DBG_RED
#define DBG_GRN
#define DBG_YEL
#define DBG_BLU
#define DBG_PUR
#define DBG_CYN
#define DBG_GRY
#define DBG_NON

static inline void ekp_dbgprint(const char *fmt, ...) {}

#endif /* CONFIG_EKP_KERNEL_DEBUG_IN_ISE */

#endif /* __ASM_EKP_DEBUG_H */
