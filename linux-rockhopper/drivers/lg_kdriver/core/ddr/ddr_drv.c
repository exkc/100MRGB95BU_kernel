#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/printk.h>
#include <linux/vmalloc.h>
#include <asm/io.h>

#include "datatype.h"
#include "register.h"
#include "config.h"
#include "proc.h"

struct ddr_struct *prev;
struct ddr_struct *curr;
struct ddr_struct *next;
struct ddr_debug *dbg;

extern int reg_ddr_ioremap(void);
extern int ddr_run_init(void);

void DDR_PreInit(void);
int DDR_Init(void);
void DDR_Cleanup(void);

static int ddr_ioremap(void)
{
	int ret;

	ret = reg_ddr_ioremap();
	if (ret < 0)
		pr_info("dmc: ioremap unknown chip\n");

	return 0;
}

static int init_config(void)
{
	prev = vmalloc(sizeof(*prev));
	curr = vmalloc(sizeof(*curr));
	next = vmalloc(sizeof(*next));
	if (prev == NULL || curr == NULL || next == NULL)
		return -ENOMEM;

	dbg = vmalloc(sizeof(struct ddr_debug));
	if (dbg == NULL)
		return -ENOMEM;

	memset(prev, 0, sizeof(*prev));
	memset(curr, 0, sizeof(*curr));
	memset(next, 0, sizeof(*next));
	memset(dbg, 0, sizeof(*dbg));

	/* initialize configurations */
	dbg->ver.major = 0;
	dbg->ver.minor = 1;
	dbg->log.info = 0x0; // debug blog init (0xFF)

	*prev = *next;
	*curr = *next;

	return 0;
}

static int run_init(void)
{
	int ret;

	ret = ddr_run_init();
	if (ret < 0)
		pr_info("dmc: run_init unknown chip\n");

	return 0;
}

void DDR_PreInit(void)
{
	/* TODO: do someting */
}

int DDR_Init(void)
{
	pr_info("dmc: ddr_init\n");

	ddr_ioremap();

	init_config();

	init_ddr_proc();

	pr_info("dmc: ver %d.%d\n", dbg->ver.major, dbg->ver.minor);

	/* DE display interrupt registration */
	// de_sync_register(1, ddr_mon, "ddr-mon");

	run_init();

	return 0;
}

void DDR_Cleanup(void)
{
	pr_info("dmc: ddr_clean-up\n");

	// de_sync_register(0, ddr_mon, "ddr-mon");

	vfree(dbg);

	cleanup_ddr_proc();
}

module_init(DDR_Init);
module_exit(DDR_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("DDR driver");
MODULE_LICENSE("GPL");
