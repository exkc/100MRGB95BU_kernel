// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2018 LG Electronics
 */

#define pr_fmt(fmt) "ekp: " fmt

#include <linux/ekp.h>
#include "private.h"

#define CREATE_TRACE_POINTS
#include "trace.h"

static const char *violation[] = {
	"INIT_AFTER_START",
	"SET_PGD_VIOLATION",
	"SET_P4D_VIOLATION",
	"SET_PUD_VIOLATION",
	"SET_PMD_VIOLATION",
	"SET_PTE_VIOLATION",
	"EMUL_SCTLR_VIOLATION",
	"EMUL_TTBR0_VIOLATION",
	"EMUL_TTBR1_VIOLATION",
	"EMUL_TCR_VIOLATION",
	"SLAB_SET_FP_VIOLATION",
	"CRED_INIT_VIOLATION",
	"CRED_SECURITY_VIOLATION",
	"LKMP_PREPARE_VIOLATION",
	"LKMP_ENABLE_VIOLATION",
	"LKMP_AFTER_INIT_VIOLATION",
	"LKMP_DISABLE_VIOLATION",
	"LKMP_DISABLE_INIT_VIOLATION",
	"LKMP_DISABLE_CORE_VIOLATION",
	"SET_ROMEM_VIOLATION",
	"ARCH_CMD_VIOLATION",
	"DUPLICATED_RO_VIOLATION",
	"FORCED_RO_VIOLATION",
	"HIBERNATION_VIOLATION",
	"SUSPEND_VIOLATION",
	"UNKNOWN_VIOLATION"
};

static uint64_t ise_fault_count[EKP_ISE_VIOLATION_MAX + 1];

static int parse_fw_violation(uint64_t cmd, struct arm_smccc_res *res)
{
	uint64_t idx = 0;
	unsigned long line;
	int ret;

	switch (res->a0) {
	case EKP_ISE_CMD_NOT_SUPPORT:
		ret = -ENODEV;
		break;
	case EKP_ISE_DETECT_VIOLATION:
		idx = __ffs(res->a1 >> 32);
		if (idx > EKP_ISE_VIOLATION_MAX) {
			idx = EKP_ISE_VIOLATION_MAX;
		}

		if (ise_fault_count[idx] == ~0ULL)
			ise_fault_count[idx] = 0;

		ise_fault_count[idx]++;
		line = res->a1 & 0xFFFFFFFFUL;

		pr_err("\x1b[31m%s [%llu] has been detected -\x1b[0m",
		       violation[idx], ise_fault_count[idx]);
		pr_cont("\x1b[31m %ld %lx %lx\x1b[0m\n",
			line, res->a2, res->a3);

		ekp_ise_fault_handler(res, violation[idx],
				      ise_fault_count[idx], line);

		BUG();

		if ((res->a1 & ROMEM_VIOLATION_MASK) != 0)
			ret = -EPERM;
		else
			ret = 0; /* To prevent fall-back */
		break;
	case EKP_ISE_PANIC_VIOLATION:
		idx = __ffs(res->a1 >> 32);
		line = res->a1 & 0xFFFFFFFFUL;
		panic("\x1b[31mPanic is requested from EKP FW [%s]:"
		      " %llx(line: %ld)\n\x1b[0m", violation[idx], cmd, line);
	default:
		ret = -ENODEV;
		break;
	}

	return ret;
}

noinline int64_t ekp_tunnel_handler(uint64_t cmd,
				    uint64_t arg1, uint64_t arg2, uint64_t arg3,
				    uint64_t arg4, uint64_t arg5, uint64_t arg6)
{
	struct arm_smccc_res res;

	arm_smccc_hvc(FUNC_ISE_CALL, cmd,
		      arg1, arg2, arg3, arg4, arg5, arg6, &res);

	if (unlikely(res.a0 != EKP_ISE_OK))
		return parse_fw_violation(cmd, &res);

	trace_ekp_cmd(cmd, arg1, arg2, arg3, arg4, arg5,
		      arg6, res.a0, res.a1, res.a2, res.a3);

	return res.a1;
}
