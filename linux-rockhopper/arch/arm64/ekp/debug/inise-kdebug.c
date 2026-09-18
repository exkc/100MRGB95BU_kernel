// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2018 LG Electronics
 */

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/sched/clock.h>
#include <linux/spinlock.h>
#include <linux/ekp.h>

#include <asm/ekp/debug.h>
#include "private.h"

#define RAW_BUFSZ	(256)
#define PREFIX_MAX	(20)

static char ekp_log_buff[RAW_BUFSZ];

static int make_time(u64 ts, char *buf)
{
	unsigned long rem_nsec = do_div(ts, 1000000000);

	return (sprintf(buf, "[%5lu.%06lu] ",
		       (unsigned long)ts, rem_nsec / 1000)+1);
}

static __always_inline void ekp_debug_tunnel(uint64_t str)
{
	if (!ekp_enabled())
		return;
	(void)ekp_tunnel(EKP_DBG_PUTS, str);
}

void ekp_dbgprint(const char *fmt, ...)
{
	static DEFINE_SPINLOCK(log_lock);
	va_list ap, aq;
	char *logbuf, *ptr;
	unsigned int cnt, test, max;
	char time_prefix[PREFIX_MAX];
	u64 ts_nsec = local_clock();
	int time_size = 0;

	if (!ekp_ise_enabled)
		return;

	spin_lock(&log_lock);

	va_start(ap, fmt);

	va_copy(aq, ap);
	test = vsnprintf(NULL, 0, fmt, aq);
	va_end(aq);

	if (IS_ENABLED(CONFIG_PRINTK_TIME))
		time_size = make_time(ts_nsec, &time_prefix[0]);

	logbuf = kmalloc_track_caller(time_size + test + 1, GFP_KERNEL);

	if (logbuf) {
		max = time_size + test + 1;
		strncpy(logbuf, &time_prefix[0], time_size);
		ptr = logbuf;
	} else {
		max = RAW_BUFSZ;
		strncpy(&ekp_log_buff[0], &time_prefix[0], time_size);
		ptr = &ekp_log_buff[0];
	}
	cnt = vsnprintf(&ptr[time_size], max-time_size, fmt, ap);

	if (IS_ENABLED(CONFIG_PRINTK_TIME))
		ptr[time_size -1] =' ';
	ekp_debug_tunnel(__pa(ptr));

	va_end(ap);

	if (logbuf)
		kfree(logbuf);

	spin_unlock(&log_lock);
}
EXPORT_SYMBOL(ekp_dbgprint);
