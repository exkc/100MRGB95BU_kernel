#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/printk.h>
#include <asm/io.h>

#include "REGISTER/register_m23.h"
#include "config.h"

uint32_t cut_width;
uint32_t em_period;
uint32_t pm_period;

static void ddrc_mon_enable(uint32_t base_period, uint32_t emg_period, uint32_t dbg_period);

int reg_m23_ioremap(void)
{
	/* DDR Register */
	gpREG_DDRT_M0 = (REG_DDRT_M0_T *)ioremap(APB_DDRT_M0_BASE, sizeof(REG_DDRT_M0_T));
	gpREG_DDRC_M0 = (REG_DDRC_M0_T *)ioremap(APB_DDRC_M0_BASE, sizeof(REG_DDRC_M0_T));
	gpREG_DDRP_M0 = (REG_DDRP_M0_T *)ioremap(APB_DDRP_M0_BASE, sizeof(REG_DDRP_M0_T));

	pr_info("dmc: m23_ioremap\n");

	return 0;
}

int m23_dmc_test(void)
{
	uint32_t base_period, emg_period, dbg_period;

	/* ddrc monitor enable */
	base_period = 875;  // 1 us
	emg_period = 1000;  // 1 ms < max.1023us
	dbg_period = 16700; // 16.7 ms

	ddrc_mon_enable(base_period, emg_period, dbg_period);

	return 0;
}

int m23_run_init(void)
{
	//m23_dmc_test();

	pr_info("dmc: m23_run_init\n");

	return 0;
}

static void ddrc_mon_enable(uint32_t base_period, uint32_t emg_period, uint32_t dbg_period)
{
	REG_DDRC_M0_PERFMON_T tmp_perfmon;
	REG_DDRC_M0_DFS_T tmp_dfs;

	if ((emg_period -1) >= 512)
		cut_width = 10;
	else if ((emg_period -1) >= 256)
		cut_width =  9;
	else if ((emg_period -1) >= 128)
		cut_width =  8;
	else if ((emg_period -1) >= 64)
		cut_width =  7;
	else if ((emg_period -1) >= 32)
		cut_width =  6;
	else if ((emg_period -1) >= 16)
		cut_width =  5;
	else if ((emg_period -1) >= 8)
		cut_width =  4;
	else if ((emg_period -1) >= 4)
		cut_width =  3;
	else if ((emg_period -1) >= 2)
		cut_width =  2;
	else if ((emg_period -1) >= 1)
		cut_width =  1;

	em_period = emg_period;
	pm_period = dbg_period;

	pr_info("dmc: cut_width %d, em_period %d, pm_period %d\n", cut_width, emg_period, dbg_period);

	REG_AWR(gpREG_DDRC_M0->base_period, (base_period -1) & 0x3FF);   // reg_base_period[9:0]
	REG_AWR(gpREG_DDRC_M0->debug_period, (dbg_period -1) & 0xFFFFF); // reg_debug_mon_period[19:0]
	REG_AWR(gpREG_DDRC_M0->mode_sel, 0x1); // reg_op_mode[0]

	tmp_perfmon = gpREG_DDRC_M0->perfmon;
	tmp_perfmon.reg_pm_en = 0x1;
	tmp_perfmon.reg_emg_period = (emg_period -1) & 0x3FF;
	gpREG_DDRC_M0->perfmon = tmp_perfmon;

	REG_AWR(gpREG_DDRC_M0->latmon, 0x1); // max latency monitor enable[0]

	tmp_dfs = gpREG_DDRC_M0->dfs;
	tmp_dfs.reg_dfs_emg_en = 0x1;
	gpREG_DDRC_M0->dfs = tmp_dfs;

	if (dbg->log.info & DDR_INFO) {
		pr_info("dmc: base_period  0x%X\n", REG_ARD(gpREG_DDRC_M0->base_period));
		pr_info("dmc: debug_period 0x%X\n", REG_ARD(gpREG_DDRC_M0->debug_period));
		pr_info("dmc: mode_sel     0x%X\n", REG_ARD(gpREG_DDRC_M0->mode_sel));
		pr_info("dmc: perfmon      0x%X\n", REG_ARD(gpREG_DDRC_M0->perfmon));
		pr_info("dmc: latmon       0x%X\n", REG_ARD(gpREG_DDRC_M0->latmon));
		pr_info("dmc: dfs          0x%X\n", REG_ARD(gpREG_DDRC_M0->dfs));
	}
}
