#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/printk.h>
#include <linux/of.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include "datatype.h"
#include "register.h"
#include "config.h"
#include "proc.h"

extern int de_sync_register(BOOLEAN flag, int (*func)(void), char *str);

#ifndef INCLUDE_KDRV_DE
int de_sync_register(BOOLEAN flag, int (*func)(void), char *str)
{
	pr_info("dmc: error on %s\n", __func__);
	return 0;
}
#endif
extern int ddr_mon(void);

static int bitlog(char *cmd)
{
	char *token;
	int argc = 0;
	char *argv[4] = {0};

	while ((token = strsep(&cmd, " ")) != NULL) {
		if (argc == 0)
			argv[argc] = token;
		argc++;
	}
	if (argc != 1)
		return -EINVAL;

	dbg->log.info = strtoui(argv[0]);

	pr_info("dmc: bit_log 0x%x\n", dbg->log.info);

	return 0;
}

static int numlog(char *cmd)
{
	char *token;
	int argc = 0;
	char *argv[4] = {0};

	while ((token = strsep(&cmd, " ")) != NULL) {
		if (argc == 0)
			argv[argc] = token;
		argc++;
	}
	if (argc != 1)
		return -EINVAL;

	dbg->log.debug = strtoui(argv[0]);

	pr_info("dmc: num_log %d\n", dbg->log.debug);

	return 0;
}

static int monitor(char *cmd)
{
	char *token;
	int ret;

	token = strsep(&cmd, " ");
	if (token != NULL) {
		if (!strcmp(token, "on")) {
			/* DE display interrupt registration */
			ret = de_sync_register(1, ddr_mon, "ddr-mon");
			pr_info("dmc: mon intr on; num %d\n", ret);
			next->ctrl.monitor = MON_ON;
		}
		else if (!strcmp(token, "off")) {
			ret = de_sync_register(0, ddr_mon, "ddr-mon");
			pr_info("dmc: mon intr off; num %d\n", ret);
			next->ctrl.monitor = MON_OFF;
		}
		else {
			pr_info("dmc: Invalid Command\n");
		}
	}

	return 0;
}

int ddr_cmd(char *cmd)
{
	char *token;

	token = strsep(&cmd, " ");
	if (token != NULL) {
		if (!strcmp(token, "blog"))
			return bitlog(cmd);
		if (!strcmp(token, "nlog"))
			return numlog(cmd);
		if (!strcmp(token, "mon"))
			return monitor(cmd);
	}

	return -EINVAL;
}

// lgtv-driver/ddr/ddr_info
int get_ddr_info(struct ddr_info *dev)
{
	/* device node path from /proc/device-tree/ */
	char *path = "/soc/hw-info/ddr";
	struct device_node *node;

	node = of_find_node_by_path(path);
	if (!node) {
		pr_info("/soc/hw-info/ddr node not found\n");
		return -ENODEV;
	}

	of_property_read_string(node, "size", &dev->size);
	of_property_read_string(node, "clock", &dev->clock);

	return 0;
}
