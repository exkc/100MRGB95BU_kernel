#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/printk.h>

#include "register.h"
#include "config.h"

extern int dmc_test(void);
extern int dmc_status(void);

int ddr_mon(void)
{
	int ret;

	/* update configuration */
	*prev = *curr;
	*curr = *next;

	/* system count */
	next->sys.start++;
	if (next->sys.start > 0x30000000)
		next->sys.start = 0x1E0;

	if (dbg->log.debug == 11)
		pr_info("dmc: sys 0x%x\n", next->sys.start);

	/* dmc status */
	if (curr->ctrl.monitor == MON_ON && prev->ctrl.monitor == MON_OFF) {
		ret = dmc_test();
		if (ret < 0)
			pr_info("dmc: dmc_test unknown chip\n");
	}

	if (curr->ctrl.monitor == MON_ON) {
		ret = dmc_status();
		if (ret != 0)
			pr_info("dmc: status error; num %d\n", ret);
	}

	return 0;
}
