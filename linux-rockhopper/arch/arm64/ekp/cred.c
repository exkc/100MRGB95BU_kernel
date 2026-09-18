// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2018 LG Electronics
 */

#include <linux/ekp.h>
#include <linux/sched.h>
#include <linux/sched/task_stack.h>
#include <linux/stacktrace.h>

#define EKP_CALLER_DEBUG 0
#if EKP_CALLER_DEBUG
#define kdebug(fmt, ...)	\
	pr_crit("\x1b[33m" fmt "\x1b[0m\n", ##__VA_ARGS__)
#else
#define kdebug(fmt, ...)	do {} while (0)
#endif

#define STACK_DEPTH	4

struct cred_caller_info {
	unsigned long count;
	unsigned long limit;
	unsigned long start;
	unsigned long end;
};

static bool check_caller_valid(void *arg, unsigned long pc)
{
	struct cred_caller_info *caller_info = arg;

	if ((pc < caller_info->start) || (pc > caller_info->end))
		return false;

	caller_info->count++;

	if (caller_info->count < caller_info->limit)
		return true;

	return false;
}

static unsigned long __get_callstack(struct task_struct *p)
{
	struct cred_caller_info caller_info = {
		.count = 0,
		.limit = STACK_DEPTH,
		.start = (unsigned long)_text,
		.end = (unsigned long)__exittext_end,
	};

	if (!try_get_task_stack(p))
		return 0;

	arch_stack_walk(check_caller_valid, &caller_info, p, NULL);

	put_task_stack(p);

	return caller_info.count;
}

bool arch_ekp_cred_validcaller(void)
{
	struct task_struct *p = current;
	unsigned long count;

	if (!ekp_enabled())
		return true;

	raw_spin_lock_irq(&p->pi_lock);
	count = __get_callstack(p);
	raw_spin_unlock_irq(&p->pi_lock);

	if (count == STACK_DEPTH)
		return true;

	return false;
}
