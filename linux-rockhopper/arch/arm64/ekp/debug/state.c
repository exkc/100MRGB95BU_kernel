// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2023 LG Electronics
 */

#include <linux/cred.h>
#include <linux/ekp.h>
#include <linux/mm.h>
#include <linux/sched/task.h>
#include <linux/sched/signal.h>

#include "debugfs.h"
#include "core/ptprot.h"

#define CFG_STATE(__config)	IS_ENABLED(__config) ? "O" : "X"

static void report_ekp_config(struct seq_file *m)
{
	seq_printf(m, "ekp:\n");
	seq_printf(m, "ekp: ====== Configurations ======\n");
	seq_printf(m, "ekp: Forcedly enabled [%s]\n",
		   CFG_STATE(CONFIG_EKP_FORCE_ENABLE));
	seq_printf(m, "ekp: Read-only credentials [%s]\n",
		   CFG_STATE(CONFIG_EKP_CRED_PROTECTION));
#ifdef CONFIG_EKP_CRED_TAG
	seq_printf(m, "ekp: Credentials TAG [%s]\n",
		   CFG_STATE(CONFIG_EKP_CRED_TAG));
#endif
	seq_printf(m, "ekp: Kernel module protection [%s]\n",
		   CFG_STATE(CONFIG_EKP_MODULE_PROTECTION));
	seq_printf(m, "ekp:\n");
}

static inline bool has_writable_pgd(struct mm_struct *mm)
{
	return !ekp_va_readonly((unsigned long)mm->pgd);
}

static inline bool has_writable_cred(struct task_struct *t)
{
#ifdef CONFIG_EKP_CRED_PROTECTION
	if (!cred_readonly(t->real_cred) || !cred_readonly(t->cred))
		return true;
#endif
	return false;
}

static inline bool has_pgd_pxntable(struct task_struct *t)
{
	const pgd_t *pgd = t->mm->pgd;
	pgdval_t desc;
	int i;

	for (i = 0; i < PTRS_PER_PGD; ++i, ++pgd) {
		desc = pgd_val(*pgd);

		if (desc == 0)
			continue;

		if ((desc & PGTABLE_PXNTABLE) == 0)
			return false;
	}

	return true;
}

struct report_stat {
	unsigned int total;
	unsigned int good;
	unsigned int bad;
};

static void ekp_printf(struct seq_file *m, const char *msg,
		       bool flag, struct report_stat *stat)
{
	seq_printf(m, "%s [%s]\n", msg, flag ? "OK" : "FAIL");

	stat->total++;

	if (flag)
		stat->good++;
	else
		stat->bad++;
}

static void report_kernel(struct seq_file *m)
{
	struct report_stat stat = {0, 0, 0};

	seq_printf(m, "ekp: ====== Kernel ======\n");

	ekp_printf(m, "ekp: Read-only PGD", !has_writable_pgd(&init_mm), &stat);
	ekp_printf(m, "ekp: HPD1 is clear", !is_set_hpd1(), &stat);

	seq_printf(m, "ekp: Total: %d, Good: %d, Bad: %d\n",
		   stat.total, stat.good, stat.bad);
	seq_printf(m, "ekp:\n");
}

static void report_user_processes(struct seq_file *m)
{
	struct task_struct *p, *t;
	struct report_stat stat = {0, 0, 0};

	bool ro_pgd = true;
	bool ro_cred = true;
	bool pxntable = true;

	read_lock(&tasklist_lock);

	for_each_process_thread(p, t) {
		if (!t->mm)
			continue;

		/* User process should have read-only PGD. */
		if (has_writable_pgd(t->mm))
			ro_pgd = false;

		if (IS_ENABLED(CONFIG_EKP_CRED_PROTECTION)) {
			/* User process should have read-only credentials. */
			if (has_writable_cred(t))
				ro_cred = false;
		}

		/* All valid PGD entries should have PXNTable bit. */
		if (!has_pgd_pxntable(t))
			pxntable = false;
	}

	read_unlock(&tasklist_lock);

	seq_printf(m, "ekp: ====== User processes ======\n");

	ekp_printf(m, "ekp: Read-only PGD", ro_pgd, &stat);
	ekp_printf(m, "ekp: HPD0 is clear", !is_set_hpd0(), &stat);

	if (IS_ENABLED(CONFIG_EKP_CRED_PROTECTION))
		ekp_printf(m, "ekp: Read-only credentials", ro_cred, &stat);
	else
		seq_printf(m, "ekp: Read-only credentials [NOT SUPPORT]\n");

	ekp_printf(m, "ekp: PGD PXNTable bits", pxntable, &stat);

	seq_printf(m, "ekp: Total: %d, Good: %d, Bad: %d\n",
		   stat.total, stat.good, stat.bad);
	seq_printf(m, "ekp:\n");
}

static void  report_general_info(struct seq_file *m)
{
	struct report_stat stat = {0, 0, 0};

	seq_printf(m, "ekp: ====== General ======\n");

	ekp_printf(m, "ekp: Read-only empty_zero_page",
		   ekp_pa_readonly(__pa_symbol(empty_zero_page)), &stat);

	seq_printf(m, "ekp: Total: %d, Good: %d, Bad: %d\n",
		   stat.total, stat.good, stat.bad);
	seq_printf(m, "ekp:\n");
}

/*
 * /sys/kernel/debug/ekp/report
 *
 * Show current EKP kernel configurations and state of user
 * processes protection.
 */
static int ekp_report_show(struct seq_file *m)
{
	report_ekp_config(m);
	report_kernel(m);
	report_user_processes(m);
	report_general_info(m);

	return 0;
}

DEFINE_EKP_DEBUGFS_RO(ekp_report);

static struct ekp_debugfs_attr ekp_state_attrs[] __initdata = {
	{
		.name = "report",
		.ops = &ekp_report,
	},
};

void __init ekp_debugfs_state_init(struct dentry *parent)
{
	ekp_debugfs_create(parent, ekp_state_attrs);
}
