#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/printk.h>
#include <asm/io.h>

#include "REGISTER/register_o24.h"
#include "config.h"

extern uint32_t *REG_DPG0_M0_S, *REG_DPG0_M1_S;
extern uint32_t *REG_DPG1_M0_S, *REG_DPG1_M1_S;
extern uint32_t *REG_DPG2_M0_S, *REG_DPG2_M1_S;
extern uint32_t *REG_DPG3_M0_S, *REG_DPG3_M1_S;

static uint32_t pm_period;
static uint32_t em_period;
static uint32_t cut_width;

int o24_mon_status(void);
int o24_dmc_test(void);

/* DPG GEN */
#if 0
static int dmc_rc(uint32_t data, uint32_t expd)/*{{{*/
{
	if (data == expd)
		pr_info("dmc:  PASS!\n");
	else
		pr_info("dmc:  FAIL!\n");

	return data;
}

static void dpg_gen_start(uint32_t RW_SEL, uint32_t REG_BASE_FAST_ADDR, uint32_t Burst_SIZE, uint32_t Burst_LEN, uint32_t Start_ADDR, uint32_t End_ADDR, uint32_t Itr_Cnt, uint32_t Multi_Out, uint32_t INF_SW, uint32_t Bank_Fix, uint32_t User_Prt, uint32_t FAST_Pready)
{
	uint32_t rddata, status;

	rddata = REG_ARD(gpREG_DPG0_M0->dpg_mo_status);
	status = (rddata >> 16) & 0xFFFF;
	while (status != 0) {
		rddata = REG_ARD(gpREG_DPG0_M0->dpg_mo_status);
		status = (rddata >> 16) & 0xFFFF;
	}

	//REG_AWR(gpREG_DPG0_M0->ip_gating, 0x11); // IP Gating Enable
	//REG_AWR(gpREG_DPG0_M0->dpg_enable, 0x1); // DPG Enable
	REG_AWR(gpREG_DPG0_M0->dpg_wr_pattern,0x2); // DPG Pattern Selection (0:TestP, 1:!TestP, 2:AddrP, 3:PWBurstP

	if (INF_SW == 0) {
		//REG_AWR(gpREG_DPG0_M0->dpg_inf_ctrl, 0x00<<16); //  1: Iteration Count for NINF_AXI_TR
		//REG_AWR(gpREG_DPG0_M0->dpg_inf_ctrl, 0x01<<16); //  2: Iteration Count for NINF_AXI_TR
		//REG_AWR(gpREG_DPG0_M0->dpg_inf_ctrl, 0x0A<<16); // 10: Iteration Count for NINF_AXI_TR
		//REG_AWR(gpREG_DPG0_M0->dpg_inf_ctrl, 0x10<<16); // 16: Iteration Count for NINF_AXI_TR
		REG_AWR(gpREG_DPG0_M0->dpg_inf_ctrl, Itr_Cnt<<16); // 16: Iteration Count for NINF_AXI_TR
	} else {
		REG_AWR(gpREG_DPG0_M0->dpg_inf_ctrl, INF_SW); // INF_AXI_TR Enable
	}

	REG_AWR(gpREG_DPG0_M0->grp0_start_addr, Start_ADDR); // Start_Addr0
	REG_AWR(gpREG_DPG0_M0->gpr0_addr_inc_bnd, End_ADDR); // End_Addr0
	if ((INF_SW == 0x10) || (INF_SW == 0x11)) {
		REG_AWR(gpREG_DPG0_M0->grp1_start_addr, Start_ADDR); // Start_Addr1
		REG_AWR(gpREG_DPG0_M0->gpr1_addr_inc_bnd, End_ADDR); // End_Addr1
	}
	REG_AWR(gpREG_DPG0_M0->user_cmd_reg0, (RW_SEL<<3|Burst_SIZE)<<28|Burst_LEN<<24|Multi_Out<<16|User_Prt<<8);
	REG_AWR(gpREG_DPG0_M0->user_cmd_reg1, ((!RW_SEL)<<3|Burst_SIZE)<<28|Burst_LEN<<24|Multi_Out<<16|User_Prt<<8);
	REG_AWR(gpREG_DPG0_M0->start_mode, FAST_Pready); // PREADY_Mode
	if (Bank_Fix == 1) {
		REG_AWR(gpREG_DPG0_M0->direct_mode, 0x1);     // Direct_Mode (Direct_Mode0 Enable)
		REG_AWR(gpREG_DPG0_M0->fixed_mode0, 0x7<<12); // AAddr_Fixed_Mode
	} else {
		REG_AWR(gpREG_DPG0_M0->direct_mode, 0x0);     // Direct_Mode (Direct_Mode0 Disable)
		REG_AWR(gpREG_DPG0_M0->fixed_mode0, 0x0);     // AAddr_Fixed_Mode
	}

	//REG_WR(REG_DPG0_M0_S, 0x5A5A5A5A); // Start! (DPG_SET_DONE -> High)
	REG_WR(REG_DPG0_M0_S, 0x4000); // Start! (DPG_SET_DONE -> High)
	REG_AWR(gpREG_DPG0_M0->start_mode, FAST_Pready); // PREADY_Mode
	pr_info("dmc: [DMC_TEST]       DPG Register Setting Done!\n");
}/*}}}*/
#endif

static void dbg_mon_init(uint32_t base_period, uint32_t emg_period, uint32_t dbg_period, uint32_t dbg_on, uint32_t pm_en, uint32_t max_lat_en, uint32_t dfs_emg_en)
{
	REG_DDRC_M0_PERFMON_T tmp_perfmon;
	REG_DDRC_M0_DFS_T tmp_dfs;

	pm_period = dbg_period;
	em_period = emg_period;

	pr_info("dmc:            (dbg_period: %d, emg_period: %d\n", dbg_period, emg_period);

	if      ((emg_period -1) >= 512) cut_width = 10;
	else if ((emg_period -1) >= 256) cut_width =  9;
	else if ((emg_period -1) >= 128) cut_width =  8;
	else if ((emg_period -1) >=  64) cut_width =  7;
	else if ((emg_period -1) >=  32) cut_width =  6;
	else if ((emg_period -1) >=  16) cut_width =  5;
	else if ((emg_period -1) >=   8) cut_width =  4;
	else if ((emg_period -1) >=   4) cut_width =  3;
	else if ((emg_period -1) >=   2) cut_width =  2;
	else if ((emg_period -1) >=   1) cut_width =  1;

	pr_info("dmc:            (cut_width: %d, pm_period: %d, em_period: %d\n", cut_width, pm_period, em_period);

	REG_AWR(gpREG_DDRC_M0->base_period, (base_period -1) & 0x3FF); // reg_base_period[9:0]
	REG_AWR(gpREG_DDRC_M0->debug_period, (dbg_period -1) & 0xFFFFF); // reg_debug_mon_period[19:0]
	REG_AWR(gpREG_DDRC_M0->mode_sel, dbg_on); // reg_bist_en[1] reg_op_mode[0]

	tmp_perfmon = gpREG_DDRC_M0->perfmon;
	tmp_perfmon.reg_emg_period = (emg_period -1) & 0x3FF;
	tmp_perfmon.reg_pm_en = pm_en;
	gpREG_DDRC_M0->perfmon = tmp_perfmon; // reg_emg_period[13:4] reg_pm_en[0]

	REG_AWR(gpREG_DDRC_M0->latmon, max_lat_en); // reg_max_lat_i[15:8] reg_max_lat_en[0]

	tmp_dfs = gpREG_DDRC_M0->dfs;
	tmp_dfs.reg_dfs_emg_en = dfs_emg_en & 0x1;
	gpREG_DDRC_M0->dfs = tmp_dfs; // reg_dfs_emg_en[1]

	pr_info("dmc: [DMC_TEST] Debug Monitor Register Setting Done!\n");
}

int o24_mon_status(void)
{
	uint32_t dbg_rdata;
	uint32_t r_pm_max;
	uint32_t r_pm_w0, r_pm_w1, r_pm_w2, r_pm_w3;
	uint32_t r_pm_r0, r_pm_r1, r_pm_r2, r_pm_r3;
	uint32_t pm_max;
	uint32_t pm_w0, pm_w1, pm_w2, pm_w3;
	uint32_t pm_r0, pm_r1, pm_r2, pm_r3;
	uint32_t pm_wtotal, pm_rtotal, pm_total;

	uint32_t max_lat;
	uint32_t max_lat_3, max_lat_5, max_lat_7, max_lat_8;

	uint32_t dfs;
	uint32_t nidle, nrd, nrdl, nwr, nmwr, nwrl, nap, nref, nact, nrw_swc, nr_urg_swc;

	uint32_t r_req_row, r_req, r_urg_row, r_urg, r_row, r_lucky;
	uint32_t w_req_row, w_req, w_urg_row, w_urg, w_row, w_lucky, w_urg_swc;

	r_pm_w0     = REG_ARD(gpREG_DDRC_M0->perfmon_w0);
	r_pm_w1     = REG_ARD(gpREG_DDRC_M0->perfmon_w1);
	r_pm_w2     = REG_ARD(gpREG_DDRC_M0->perfmon_w2);
	r_pm_w3     = REG_ARD(gpREG_DDRC_M0->perfmon_w3);
	r_pm_r0     = REG_ARD(gpREG_DDRC_M0->perfmon_r0);
	r_pm_r1     = REG_ARD(gpREG_DDRC_M0->perfmon_r1);
	r_pm_r2     = REG_ARD(gpREG_DDRC_M0->perfmon_r2);
	r_pm_r3     = REG_ARD(gpREG_DDRC_M0->perfmon_r3);
	dbg_rdata   = REG_ARD(gpREG_DDRC_M0->perfmon_emg_max);
	r_pm_max    = dbg_rdata & 0xFFF;

	pr_info("dmc:            r_pm_w  :  %8d | %8d | %8d | %8d \n", r_pm_w0, r_pm_w1, r_pm_w2 , r_pm_w3);
	pr_info("dmc:            r_pm_r  :  %8d | %8d | %8d | %8d \n", r_pm_r0, r_pm_r1, r_pm_r2 , r_pm_r3);
	pr_info("dmc:            r_pm_max:  %8d                   \n", r_pm_max);

	pm_w0     = r_pm_w0  * (1 << cut_width) * 16 / pm_period;
	pm_w1     = r_pm_w1  * (1 << cut_width) * 16 / pm_period;
	pm_w2     = r_pm_w2  * (1 << cut_width) * 16 / pm_period;
	pm_w3     = r_pm_w3  * (1 << cut_width) * 16 / pm_period;
	pm_r0     = r_pm_r0  * (1 << cut_width) * 16 / pm_period;
	pm_r1     = r_pm_r1  * (1 << cut_width) * 16 / pm_period;
	pm_r2     = r_pm_r2  * (1 << cut_width) * 16 / pm_period;
	pm_r3     = r_pm_r3  * (1 << cut_width) * 16 / pm_period;
	pm_max    = r_pm_max * (1 << cut_width) * 16 / em_period;

	pm_wtotal = pm_w0 + pm_w1 + pm_w2 + pm_w3;
	pm_rtotal = pm_r0 + pm_r1 + pm_r2 + pm_r3;
	pm_total  = pm_wtotal + pm_rtotal;

	pr_info("dmc:            [Performance Monitor Statistics]\n");
	pr_info("dmc:            (cut_width: %d, pm_period: %d, em_period: %d\n", cut_width, pm_period, em_period);
	pr_info("dmc:            ================================================\n");
	pr_info("dmc:               BW |    Write |     Read |    Total [MByte/s]\n");
	pr_info("dmc:            ------------------------------------------------\n");
	pr_info("dmc:            Port0 | %8d | %8d | %8d \n", pm_w0, pm_r0, (pm_w0 + pm_r0));
	pr_info("dmc:            Port1 | %8d | %8d | %8d \n", pm_w1, pm_r1, (pm_w1 + pm_r1));
	pr_info("dmc:            Port2 | %8d | %8d | %8d \n", pm_w2, pm_r2, (pm_w2 + pm_r2));
	pr_info("dmc:            Port3 | %8d | %8d | %8d \n", pm_w3, pm_r3, (pm_w3 + pm_r3));
	pr_info("dmc:            ------------------------------------------------\n");
	pr_info("dmc:            Total | %8d | %8d | %8d \n", pm_wtotal, pm_rtotal, pm_total);
	pr_info("dmc:             M.BW | %8d | %8d | %8d \n",     0,     0, pm_max);
	pr_info("dmc:            ================================================\n");

	dbg_rdata = REG_ARD(gpREG_DDRC_M0->debug_max_lat_qos);
	max_lat_3 = (dbg_rdata      ) & 0xFF;
	max_lat_5 = (dbg_rdata >>  8) & 0xFF;
	max_lat_7 = (dbg_rdata >> 16) & 0xFF;
	max_lat_8 = (dbg_rdata >> 24) & 0xFF;
	dbg_rdata = REG_ARD(gpREG_DDRC_M0->perfmon_emg_max);
	max_lat   = (dbg_rdata >> 4) & 0x3FF;

	pr_info("dmc:                   QOS | 1~3 | 4~5 | 6~7 | >8 |M.Latency \n");
	pr_info("dmc:            ---------------------------------------------\n");
	pr_info("dmc:            M.LAT Value|%5d|%5d|%5d|%4d|%9d\n",
			max_lat_3, max_lat_5, max_lat_7, max_lat_8, max_lat);
	pr_info("dmc:            =============================================\n");

	dfs        = REG_ARD(gpREG_DDRC_M0->debug_dfs);
	nidle      = REG_ARD(gpREG_DDRC_M0->debug_idle_cnt);
	nrd        = REG_ARD(gpREG_DDRC_M0->debug_rd_cnt);
	nrdl       = REG_ARD(gpREG_DDRC_M0->debug_rdl_cnt);
	nwr        = REG_ARD(gpREG_DDRC_M0->debug_rwr_cnt);
	nmwr       = REG_ARD(gpREG_DDRC_M0->debug_mwr_cnt);
	nwrl       = REG_ARD(gpREG_DDRC_M0->debug_wrl_cnt);
	nap        = REG_ARD(gpREG_DDRC_M0->debug_prg_cnt);
	nref       = REG_ARD(gpREG_DDRC_M0->debug_ref_cnt);
	nact       = REG_ARD(gpREG_DDRC_M0->debug_act_cnt);
	nrw_swc    = REG_ARD(gpREG_DDRC_M0->debug_rw_swc_cnt);
	nr_urg_swc = REG_ARD(gpREG_DDRC_M0->debug_r_urg_swc_cnt);

	pr_info("dmc:               CG |dfs|   nidle|    nact|     nrd|    nrdl|     nwr|    nmwr|    nwrl|     nap| nref|nrw_swc|nr_urg_swc \n");
	pr_info("dmc:            ------------------------------------------------------------------------------------\n");
	pr_info("dmc:            Count |%3d|%8d|%8d|%8d|%8d|%8d|%8d|%8d|%8d|%8d|%8d|%10d \n",
			dfs,nidle, nact, nrd , nrdl, nwr , nmwr, nwrl, nap , nref,nrw_swc,nr_urg_swc);
	pr_info("dmc:               BW |   |        |        |%8d|%8d|%8d|%8d|%8d|        |        |        |           \n",
			(nrd  *  64 / pm_period),
			(nrdl * 128 / pm_period),
			(nwr  *  64 / pm_period),
			(nmwr *  64 / pm_period),
			(nwrl * 128 / pm_period));
	pr_info("dmc:            ====================================================================================\n");


	r_req_row  = REG_ARD(gpREG_DDRC_M0->debug_r_req_row_hit_cnt);
	r_req      = REG_ARD(gpREG_DDRC_M0->debug_r_req_hit_cnt);
	r_urg_row  = REG_ARD(gpREG_DDRC_M0->debug_r_urg_row_hit_cnt);
	r_urg      = REG_ARD(gpREG_DDRC_M0->debug_r_urg_hit_cnt);
	r_row      = REG_ARD(gpREG_DDRC_M0->debug_r_row_hit_cnt);
	r_lucky    = REG_ARD(gpREG_DDRC_M0->debug_r_lucky_hit_cnt);
	w_urg_swc  = REG_ARD(gpREG_DDRC_M0->debug_w_urg_swc_cnt);
	w_req_row  = REG_ARD(gpREG_DDRC_M0->debug_w_req_row_hit_cnt);
	w_req      = REG_ARD(gpREG_DDRC_M0->debug_w_req_hit_cnt);
	w_urg_row  = REG_ARD(gpREG_DDRC_M0->debug_w_urg_row_hit_cnt);
	w_urg      = REG_ARD(gpREG_DDRC_M0->debug_w_urg_hit_cnt);
	w_row      = REG_ARD(gpREG_DDRC_M0->debug_w_row_hit_cnt);
	w_lucky    = REG_ARD(gpREG_DDRC_M0->debug_w_lucky_hit_cnt);

	pr_info("dmc:              HIT |req_row| req |urg_row| urg | row |lucky| w_urg_swc \n");
	pr_info("dmc:            ------------------------------------------------------------------------------------\n");
	pr_info("dmc:            Read  |%7d|%5d|%7d|%5d|%5d|%5d|    \n",
			r_req_row,r_req,r_urg_row,r_urg,r_row,r_lucky );
	pr_info("dmc:            Write |%7d|%5d|%7d|%5d|%5d|%5d|%9d \n",
			w_req_row,w_req,w_urg_row,w_urg,w_row,w_lucky,w_urg_swc);
	pr_info("dmc:            ====================================================================================\n");

	return 0;
}

int o24_dmc_test(void)
{
	uint32_t base_period = 875;  // 1 us
	uint32_t emg_period = 1000;  // 1 ms < max. 1023us
	uint32_t dbg_period = 16700; //16.7ms

	pr_info("dmc: [DMC_TEST]=================================================\n");
	dbg_mon_init(base_period, emg_period, dbg_period, 1, 1, 1, 1);

	/* DPG TEST */
#if 0
	pr_info("dmc: [DPG_TEST]=================================================\n");/*{{{*/

	pr_info("dmc: [DMC_TEST][DPG0] NONINF-1CMD (Write) *********************\n");
	pr_info("dmc: [DMC_TEST][DPG0] 128KB = 16Iter x 32Mot x 5 Burst x 16Byte\n");
	dpg_gen_start(0,APB_DPG0_M0_BASE,0x4,0x4,0x002,0x003,0x10,0x1F,0x0,0x0,0xA,0x0);
	//DPG0 NONINF 1CMD Read
	pr_info("dmc: [DMC_TEST][DPG0] NONINF-1CMD (Read) **********************\n");
	dpg_gen_start(1,APB_DPG0_M0_BASE,0x4,0x4,0x002,0x003,0x10,0x1F,0x0,0x0,0xA,0x0);

	pr_info("dmc: [DMC_TEST]       data : ");
	dmc_rc(REG_ARD(gpREG_DPG0_M0->dpg_rdata_err_status), 0x0);
	pr_info("dmc: [DMC_TEST]       bid  : ");
	dmc_rc(REG_ARD(gpREG_DPG0_M0->dpg_bch_err_status), 0x0);
	pr_info("dmc: [DMC_TEST]       rid  : ");
	dmc_rc(REG_ARD(gpREG_DPG0_M0->dpg_rch_err_status), 0x0);

	REG_AWR(gpREG_DPG0_M0->dpg_rdata_err_status, 0x10000000); // rddata err_flag clear
	REG_AWR(gpREG_DPG0_M0->dpg_bch_err_status, 0x10001000); // bid & bresp err_flag clear
	REG_AWR(gpREG_DPG0_M0->dpg_rch_err_status, 0x10001000); // rid & rresp err_flag clear}}}
#endif

	return 0;
}
