// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2018 LG Electronics
 */

#include <linux/ekp.h>
#include "private.h"

bool ekp_started = false;

struct bpf_ptp_filter_info {
	unsigned long start;
	unsigned long end;
};

static struct bpf_ptp_filter_info ptp_filter;

void __init arch_ekp_ptp_setup(unsigned long start, unsigned long pages)
{
	ptp_filter.start = start;
	ptp_filter.end = start + (pages << PAGE_SHIFT);
}

void arch_ekp_start(void)
{
	if (!ekp_enabled())
		return;

	ekp_tunnel(EKP_START, arm64_kernel_unmapped_at_el0(),
		   ptp_filter.start, ptp_filter.end);

	ptp_filter.start = 0;
	ptp_filter.end = 0;

	ekp_started = true;
}
