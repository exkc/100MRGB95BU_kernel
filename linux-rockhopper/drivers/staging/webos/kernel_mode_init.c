// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2024 LG Electronics
 *
 * Author : Jaehyun Kim <jehn.kim@lge.com>
 */

#include <linux/init.h>
#include <linux/err.h>
#include <linux/printk.h>
#include <linux/sched.h>

static unsigned int is_kmo;

static int (*register_cb_fn)(void) = NULL;

static int set_kmo(char *str)
{
	is_kmo = 1;
	return 1;
}
__setup("kernel_mode_only", set_kmo);

int register_kernel_mode_init(int (*callback)(void))
{
	if (register_cb_fn) {
                pr_err("kmo: kmo is already registered\n");
                return -EBUSY;
        }

        register_cb_fn = callback;
        pr_info("kmo: kmo registered successfully\n");

	return 0;
}

bool is_kernel_mode_only(void)
{
        if (!is_kmo || !register_cb_fn)
                return false;

        return true;
}

void kernel_mode_init(void)
{
        if (!is_kernel_mode_only()) {
                pr_err("kmo: no kmo func registered\n");
                return;
        }

        register_cb_fn();

        set_current_state(TASK_INTERRUPTIBLE);
        schedule();
}
