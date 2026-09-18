// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2018 LG Electronics
 */

#include <linux/fault_notifier.h>
#include "private.h"

void ekp_ise_fault_handler(struct arm_smccc_res *res, const char *violation,
			   uint64_t count, unsigned long line)
{
	if (!ekp_started)
		return;

	fn_kernel_notify(FN_TYPE_ALL, "%s [%llu] - %ld %lx %lx",
			 violation, count, line, res->a2, res->a3);

	WARN_ON(1);
}
