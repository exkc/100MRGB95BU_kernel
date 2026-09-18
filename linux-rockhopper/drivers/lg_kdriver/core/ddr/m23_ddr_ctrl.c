#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/printk.h>
#include <asm/io.h>

#include "REGISTER/register_m23.h"
#include "config.h"

extern uint32_t cut_width;
extern uint32_t em_period;
extern uint32_t pm_period;

static void performance_monitor(void);
static void qos_max_latency(void);
static void cmd_status(void);
static void hit_status(void);

int m23_mon_status(void)
{
	performance_monitor();
	qos_max_latency();
	cmd_status();
	hit_status();

	return 0;
}

static void performance_monitor(void)
{
	uint32_t r_pm_w0, r_pm_w1, r_pm_w2, r_pm_w3;
	uint32_t r_pm_r0, r_pm_r1, r_pm_r2, r_pm_r3;
	uint32_t r_pm_max;

	uint32_t pm_w0, pm_w1, pm_w2, pm_w3;
	uint32_t pm_r0, pm_r1, pm_r2, pm_r3;
	uint32_t pm_max;

	uint32_t pm_wtotal, pm_rtotal, pm_total;

	r_pm_w0  = REG_ARD(gpREG_DDRC_M0->perfmon_w0); // 0xC4F40210
	r_pm_w1  = REG_ARD(gpREG_DDRC_M0->perfmon_w1); // 0xC4F40214
	r_pm_w2  = REG_ARD(gpREG_DDRC_M0->perfmon_w2); // 0xC4F40218
	r_pm_w3  = REG_ARD(gpREG_DDRC_M0->perfmon_w3); // 0xC4F4021C
	r_pm_r0  = REG_ARD(gpREG_DDRC_M0->perfmon_r0); // 0xC4F40220
	r_pm_r1  = REG_ARD(gpREG_DDRC_M0->perfmon_r1); // 0xC4F40224
	r_pm_r2  = REG_ARD(gpREG_DDRC_M0->perfmon_r2); // 0xC4F40228
	r_pm_r3  = REG_ARD(gpREG_DDRC_M0->perfmon_r3); // 0xC4F4022C
	r_pm_max = REG_ARD(gpREG_DDRC_M0->perfmon_emg_max) & 0xFFF; // 0xC4F40204

	pm_w0  = r_pm_w0  * (1 << cut_width) * 16 / pm_period;
	pm_w1  = r_pm_w1  * (1 << cut_width) * 16 / pm_period;
	pm_w2  = r_pm_w2  * (1 << cut_width) * 16 / pm_period;
	pm_w3  = r_pm_w3  * (1 << cut_width) * 16 / pm_period;
	pm_r0  = r_pm_r0  * (1 << cut_width) * 16 / pm_period;
	pm_r1  = r_pm_r1  * (1 << cut_width) * 16 / pm_period;
	pm_r2  = r_pm_r2  * (1 << cut_width) * 16 / pm_period;
	pm_r3  = r_pm_r3  * (1 << cut_width) * 16 / pm_period;
	pm_max = r_pm_max * (1 << cut_width) * 16 / em_period;

	pm_wtotal = pm_w0 + pm_w1 + pm_w2 + pm_w3;
	pm_rtotal = pm_r0 + pm_r1 + pm_r2 + pm_r3;
	pm_total  = pm_wtotal + pm_rtotal;

	if (dbg->log.debug == 21) {
		pr_info("dmc: >> start\n");
	}
	if (dbg->log.debug == 21) {
		pr_info("dmc: r_pm_w %4d %4d %4d %4d  r_pm_r %4d %4d %4d %4d  r_pm_max %4d\n",
				r_pm_w0, r_pm_w1, r_pm_w2 , r_pm_w3,
				r_pm_r0, r_pm_r1, r_pm_r2 , r_pm_r3,
				r_pm_max);
	}

	/* Performance Monitor Statistics */
	if (dbg->log.debug == 21) {
		pr_info("dmc: pm_w %6d %4d %4d %4d  pm_r %6d %4d %4d %4d  pm_max %6d\n",
				pm_w0, pm_w1, pm_w2 , pm_w3,
				pm_r0, pm_r1, pm_r2 , pm_r3,
				pm_max);
	}
	/* 3500 MHz x 4 Byte = 14000 MB/s (100%) */
	if (dbg->log.debug == 21) {
		pr_info("dmc: pm_wtot %18d  pm_rtot %18d  pm_tot %6d MB/s  %2d %%\n",
				pm_wtotal, pm_rtotal, pm_total, (pm_total*100)/14000);
	}
}

static void qos_max_latency(void)
{
	REG_DDRC_M0_DEBUG_MAX_LAT_QOS_T tmp_debug_max_lat_qos; // 0xC4F45770

	uint32_t max_lat_3, max_lat_5, max_lat_7, max_lat_8;
	uint32_t max_lat;

	tmp_debug_max_lat_qos = gpREG_DDRC_M0->debug_max_lat_qos;

	max_lat_3 = tmp_debug_max_lat_qos.reg_debug_max_lat_3;
	max_lat_5 = tmp_debug_max_lat_qos.reg_debug_max_lat_5;
	max_lat_7 = tmp_debug_max_lat_qos.reg_debug_max_lat_7;
	max_lat_8 = tmp_debug_max_lat_qos.reg_debug_max_lat_8;

	max_lat = REG_ARD(gpREG_DDRC_M0->perfmon_emg_max); // 0xC4F40204
	max_lat = (max_lat >> 4) & 0x3FF;

	if (dbg->log.debug == 21) {
		pr_info("dmc: max_lat %3d %3d %3d %3d %6d\n",
				max_lat_3, max_lat_5, max_lat_7, max_lat_8, max_lat);
	}
}

static void cmd_status(void)
{
	uint32_t dfs;
	uint32_t nidle, nrd, nrdl, nwr, nmwr, nwrl;
	uint32_t nap, nref, nact, nrw_swc, nr_urg_swc;

	dfs        = REG_ARD(gpREG_DDRC_M0->debug_dfs);           // 0x5600
	nidle      = REG_ARD(gpREG_DDRC_M0->debug_idle_cnt);      // 0x5700
	nrd        = REG_ARD(gpREG_DDRC_M0->debug_rd_cnt);        // 0x5704
	nrdl       = REG_ARD(gpREG_DDRC_M0->debug_rdl_cnt);       // 0x5708
	nwr        = REG_ARD(gpREG_DDRC_M0->debug_rwr_cnt);       // 0x5710
	nmwr       = REG_ARD(gpREG_DDRC_M0->debug_mwr_cnt);       // 0x5714
	nwrl       = REG_ARD(gpREG_DDRC_M0->debug_wrl_cnt);       // 0x5718
	nap        = REG_ARD(gpREG_DDRC_M0->debug_prg_cnt);       // 0x5720
	nref       = REG_ARD(gpREG_DDRC_M0->debug_ref_cnt);       // 0x5724
	nact       = REG_ARD(gpREG_DDRC_M0->debug_act_cnt);       // 0x5728
	nrw_swc    = REG_ARD(gpREG_DDRC_M0->debug_rw_swc_cnt);    // 0x572C
	nr_urg_swc = REG_ARD(gpREG_DDRC_M0->debug_r_urg_swc_cnt); // 0x5730

	if (dbg->log.debug == 21) {
		pr_info("dmc: cmd_cnt %3d %8d %8d %8d %8d %8d %8d %8d %8d %8d %8d %8d\n",
				dfs, nidle, nact, nrd, nrdl, nwr, nmwr, nwrl,
			   	nap, nref, nrw_swc, nr_urg_swc);
	}
	if (dbg->log.debug == 21) {
		pr_info("dmc: cmd_bw %31d %8d %8d %8d %8d\n",
				(nrd * 64 / pm_period), (nrdl * 128 / pm_period),
				(nwr * 64 / pm_period), (nmwr *  64 / pm_period), (nwrl * 128 / pm_period));
	}
}

static void hit_status(void)
{
	uint32_t r_req_row, r_req, r_urg_row, r_urg, r_row, r_lucky;
	uint32_t w_req_row, w_req, w_urg_row, w_urg, w_row, w_lucky, w_urg_swc;

	r_req_row  = REG_ARD(gpREG_DDRC_M0->debug_r_req_row_hit_cnt); // 0x5734
	r_req      = REG_ARD(gpREG_DDRC_M0->debug_r_req_hit_cnt);     // 0x5738
	r_urg_row  = REG_ARD(gpREG_DDRC_M0->debug_r_urg_row_hit_cnt); // 0x573C
	r_urg      = REG_ARD(gpREG_DDRC_M0->debug_r_urg_hit_cnt);     // 0x5740
	r_row      = REG_ARD(gpREG_DDRC_M0->debug_r_row_hit_cnt);     // 0x5744
	r_lucky    = REG_ARD(gpREG_DDRC_M0->debug_r_lucky_hit_cnt);   // 0x5748
	w_urg_swc  = REG_ARD(gpREG_DDRC_M0->debug_w_urg_swc_cnt);     // 0x5750
	w_req_row  = REG_ARD(gpREG_DDRC_M0->debug_w_req_row_hit_cnt); // 0x5754
	w_req      = REG_ARD(gpREG_DDRC_M0->debug_w_req_hit_cnt);     // 0x5758
	w_urg_row  = REG_ARD(gpREG_DDRC_M0->debug_w_urg_row_hit_cnt); // 0x575C
	w_urg      = REG_ARD(gpREG_DDRC_M0->debug_w_urg_hit_cnt);     // 0x5760
	w_row      = REG_ARD(gpREG_DDRC_M0->debug_w_row_hit_cnt);     // 0x5764
	w_lucky    = REG_ARD(gpREG_DDRC_M0->debug_w_lucky_hit_cnt);   // 0x5768

	if (dbg->log.debug == 21) {
		pr_info("dmc: hit_r %5d %4d %4d %4d %8d %8d\n",
				r_req_row, r_req, r_urg_row, r_urg, r_row, r_lucky);
	}
	if (dbg->log.debug == 21) {
		pr_info("dmc: hit_w %5d %4d %4d %4d %8d %8d %4d\n",
				w_req_row, w_req, w_urg_row, w_urg, w_row, w_lucky, w_urg_swc);
	}
	if (dbg->log.debug == 21) {
		pr_info("dmc: << end\n");
	}
}
