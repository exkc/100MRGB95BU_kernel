/*****************************************************************************************
 * SIC R&D LAB, LG ELECTRONICS INC., SEOUL, KOREA
 * COPYRIGHT(c) 2011,2012 by LG Electronics Inc.
 *
 * All rights reserved. No part of this work covered by this copyright hereon
 * may be reproduced, stored in a retrieval system, in any form
 * or by any means, electronic, mechanical, photocopying, recording
 * or otherwise, without the prior written  permission of LG Electronics.
 ****************************************************************************************/

/** @file
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author		raxis.lim
 *  @version	1.0
 *  @date		2021-03-31
 *  @note		Additional information.
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#ifndef INCLUDE_KDRV_VER_FPGA
#define PQEPM_M23_USE_CTOP_REGS
#endif

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "pqe_pm_impl.h"
#include "../sys/sys_io.h"

#ifdef PQEPM_M23_USE_CTOP_REGS
#include "../sys/sys_regs.h"
#endif

//#ifdef INCLUDE_KDRV_SYS
//#include "sys_drv.h"
//#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
struct pqe_pm_regs_entry
{
	char *name;
	UINT32 address;
	UINT32 data_suspend;
	UINT32 data_resume;
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
#ifdef INCLUDE_KDRV_DE
extern int vsc_suspend(int type);
extern int vsc_resume(int type);
#endif

extern void pqe_pm_register_hw_dbg_status(void(*status)(struct seq_file *));

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int _pqe_pm_m23_hw_handler(int cmd);
static void _pqe_pm_m23_hw_dbg_status(struct seq_file *m);
static void _pqe_pm_m23_hw_dbg_read_regs(char *prefix);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static int _g_pqe_pm_m23_enable = 1;
module_param_named(pqepm_m23, _g_pqe_pm_m23_enable, int, 0644);

static uint _g_pqe_pm_m23_cg = 0;
module_param_named(pqepm_m23_cg, _g_pqe_pm_m23_cg, uint, 0644);

/* cpu list (SICDTV-11139) */
#define PQE_PM_M23_HW_REG_TCON_CTRL  0xCC470004
#define PQE_PM_M23_HW_REG_C4TX_PDB   0xCC532020
#define PQE_PM_M23_HW_REG_DISP_PLL   0xCC922004
/* lockup check disable on demod path (see Adapter_Register) */
#define PQE_PM_M23_HW_REG_DEMOD_LKUP 0xC600301C
#define PQE_PM_M23_HW_REG_USB0_LKUP  0xC440201C
#define PQE_PM_M23_HW_REG_USB1_LKUP  0xC800201C
/* apb mask between cpu and demod (not used) */
#define PQE_PM_M23_HW_REG_CPU_DEMOD  0xC6000018
/* apb mask between cpu and hdmi_link (not used) */
#define PQE_PM_M23_HW_REG_CPU_HDMI   0xC8000018
/* apb mask between cpu and cco(osd) */
#define PQE_PM_M23_HW_REG_CPU_CCO    0xCC200018
/* apb mask between cpu and mcu */
#define PQE_PM_M23_HW_REG_CPU_PMCU0  0xCC201018
#define PQE_PM_M23_HW_REG_CPU_PMCU1  0xCC401018
#define PQE_PM_M23_HW_REG_CPU_PMCU2  0xCC801018
#define PQE_PM_M23_HW_REG_CPU_PMCU3  0xCCC01018
/* power */
#define PQE_PM_M23_HW_REG_POWER_00   0xC8513000
#define PQE_PM_M23_HW_REG_POWER_01   0xC8513004
#define PQE_PM_M23_HW_REG_POWER_02   0xC8513008
/* pic init list (SICDTV-15035) */
#define PQE_PM_M23_HW_PIC_INIT_FMC   0xCC8E1000
#define PQE_PM_M23_HW_PIC_INIT_GSC   0xCC830000
#define PQE_PM_M23_HW_PIC_INIT_VSD   0xCC4F0000
#define PQE_PM_M23_HW_PIC_INIT_CCO   0xCC4B0000
/* intr list (SICDTV-15078) */
#define PQE_PM_M23_HW_IPC_PQE_INTR   0xCC0A01E4
#define PQE_PM_M23_HW_IPC_VDEC_INTR  0xCC0A01F4
#define PQE_PM_M23_HW_MCU_EXT_EN     0xCC08000C
#define PQE_PM_M23_HW_MCU_INT_EN     0xCC08001C
#define PQE_PM_M23_HW_MCU_FLAG_EN    0xCC080064
#define PQE_PM_M23_HW_VSD_INTR_MASK  0xCC4F0014
#define PQE_PM_M23_HW_SRE_INTR_MASK  0xCC570014
#define PQE_PM_M23_HW_IMX_INTR_MASK  0xCC6D0014
#define PQE_PM_M23_HW_ME0_INTR_MASK  0xCC9C0014
#define PQE_PM_M23_HW_FMS_INTR_MASK  0xCC950014
#define PQE_PM_M23_HW_FMC_INTR_MASK  0xCC8E1014

struct pqe_pm_regs_entry _g_pqe_pm_m23_regs_table[] = {
{"tcon_ctrl"  , PQE_PM_M23_HW_REG_TCON_CTRL , 0x00000024, 0x00000025},
{"c4tx_pdb"   , PQE_PM_M23_HW_REG_C4TX_PDB  , 0x00000000, 0x010000ff},
{"disp_pll"   , PQE_PM_M23_HW_REG_DISP_PLL  , 0x07b12180, 0x07b12180},
{"demod_lkup" , PQE_PM_M23_HW_REG_DEMOD_LKUP, 0x00000000, 0x00000001},
{"usb0_lkup"  , PQE_PM_M23_HW_REG_USB0_LKUP , 0x00000000, 0x00000001},
{"usb1_lkup"  , PQE_PM_M23_HW_REG_USB1_LKUP , 0x00000000, 0x00000001},
{"cpu_demod"  , PQE_PM_M23_HW_REG_CPU_DEMOD , 0x00000000, 0x00000000},
{"cpu_hdmi"   , PQE_PM_M23_HW_REG_CPU_HDMI  , 0x00000000, 0x00000000},
{"cpu_cco"    , PQE_PM_M23_HW_REG_CPU_CCO   , 0x00000001, 0x00000000},
{"cpu_pmcu0"  , PQE_PM_M23_HW_REG_CPU_PMCU0 , 0x00000001, 0x00000000},
{"cpu_pmcu1"  , PQE_PM_M23_HW_REG_CPU_PMCU1 , 0x00000001, 0x00000000},
{"cpu_pmcu2"  , PQE_PM_M23_HW_REG_CPU_PMCU2 , 0x00000001, 0x00000000},
{"cpu_pmcu3"  , PQE_PM_M23_HW_REG_CPU_PMCU3 , 0x00000001, 0x00000000},
{"power_00"   , PQE_PM_M23_HW_REG_POWER_00  , 0x00000011, 0x00000001},
{"power_01"   , PQE_PM_M23_HW_REG_POWER_01  , 0x07FEF800, 0x00000000},
{"power_02"   , PQE_PM_M23_HW_REG_POWER_02  , 0x00000000, 0x00000000},
{"fw_pic_fmc" , PQE_PM_M23_HW_PIC_INIT_FMC  , 0x00000000, 0x00230000},
{"fw_pic_gsc" , PQE_PM_M23_HW_PIC_INIT_GSC  , 0x00000000, 0x00c30000},
{"fw_pic_vsd" , PQE_PM_M23_HW_PIC_INIT_VSD  , 0x00000000, 0x00030000},
{"fw_pic_cco" , PQE_PM_M23_HW_PIC_INIT_CCO  , 0x00000000, 0x00130000},
{"fw_ipc_pqe" , PQE_PM_M23_HW_IPC_PQE_INTR  , 0x00000000, 0x0000003f},
{"fw_vdec_pqe", PQE_PM_M23_HW_IPC_VDEC_INTR , 0x00000000, 0x0000003f},
{"fw_mcu_ext" , PQE_PM_M23_HW_MCU_EXT_EN    , 0x00000000, 0x9f780000},
{"fw_mcu_int" , PQE_PM_M23_HW_MCU_INT_EN    , 0x00000000, 0x00200000},
{"fw_mcu_flag", PQE_PM_M23_HW_MCU_FLAG_EN   , 0x00000000, 0x0000f146},
{"fw_vsd_intr", PQE_PM_M23_HW_VSD_INTR_MASK , 0x00000000, 0xfffefffc},
{"fw_sre_intr", PQE_PM_M23_HW_SRE_INTR_MASK , 0x00000000, 0xffffbfff},
{"fw_imx_intr", PQE_PM_M23_HW_IMX_INTR_MASK , 0x00000000, 0xffffabfe},
{"fw_me0_intr", PQE_PM_M23_HW_ME0_INTR_MASK , 0x00000000, 0xfffffcff},
{"fw_fms_intr", PQE_PM_M23_HW_FMS_INTR_MASK , 0x00000000, 0xfffffeff},
{"fw_fmc_intr", PQE_PM_M23_HW_FMC_INTR_MASK , 0x00000000, 0xfffff0ff}};

/*========================================================================================
	Implementation Group
========================================================================================*/
void pqe_pm_init_m23_hw_ctx(void)
{
	pqe_pm_register_hw_handler(_pqe_pm_m23_hw_handler);
	pqe_pm_register_enable(&_g_pqe_pm_m23_enable);
	pqe_pm_register_hw_dbg_status(_pqe_pm_m23_hw_dbg_status);
}

static int _pqe_pm_m23_hw_handler(int cmd)
{
	#ifdef PQEPM_M23_USE_CTOP_REGS
	int ret;
	unsigned int flags;
	unsigned int data;
	union {
		UINT32 udata32;
		MICOM_POWER_CTRL_POWER_01_M23A0_T p;//micom:0xF3513004,cpu:0xC8513004
	} cg;
	#endif

	if (cmd == PQE_PM_HW_FW_SUSPEND)
	{
		#ifdef INCLUDE_KDRV_DE
		vsc_suspend(1);/* fw_stop */
		#endif

		if (_g_pqe_pm_m23_enable == 10) {
			_pqe_pm_m23_hw_dbg_read_regs("fw_");//print only those that start with "fw_"
		}

		pqe_pm_noti("PQE_PM_HW_FW_SUSPEND done\n");
	}
	else if (cmd == PQE_PM_HW_CG_ON)
	{
		usleep_range(20000, 20000); // 20ms, see http://clm.lge.com/issue/browse/SICDTV-13478

		/**
		see http://jira.lge.com/issue/browse/SICDTV-11139
		AR suspend sequence
		wr 0xC600301C, 0x0  // Demod path apb lockup check disable
		wr 0xC440201C, 0x0  // Usb0 path apb lockup check disable
		wr 0xC800201C, 0x0  // Usb1 path apb lockup check disable
		wr 0xCC200018, 0x1
		wr 0xCC201018, 0x1
		wr 0xCC401018, 0x1
		wr 0xCC801018, 0x1
		wr 0xCCC01018, 0x1
		rdata = 0xC8513000
		wr 0xC8513000, (data | 0x0010)
		wr 0xC8513004, 0x07FEF800
		*/

		pqe_pm_noti("PQE_PM_HW_CG_ON start\n");
		#ifdef PQEPM_M23_USE_CTOP_REGS
		// ret = SYS_IO_ReadRegArray(PQE_PM_M23_HW_REG_CPU_HDMI,4,&cpu_hdmi);
		// data = cpu_hdmi | 0x1;
		// ret = SYS_IO_WriteRegArray(PQE_PM_M23_HW_REG_CPU_HDMI,4,&data);//add dsc masking to avoid lockup on hdmi 144 input when CG on(AVTASK-1376)
		// pqe_pm_noti("pqepm_cg_on cpu_hdmi pslverr_masking(0x%08x)(pre:0x%08x)\n",data,cpu_hdmi);

		data = 0x0;
		ret = SYS_IO_WriteRegArray(PQE_PM_M23_HW_REG_DEMOD_LKUP,4,&data);
		ret = SYS_IO_WriteRegArray(PQE_PM_M23_HW_REG_USB0_LKUP,4,&data);
		ret = SYS_IO_WriteRegArray(PQE_PM_M23_HW_REG_USB1_LKUP,4,&data);

		data = 0x1;
		// ret = SYS_IO_WriteRegArray(PQE_PM_M23_HW_REG_CPU_DEMOD,4,&data);
		ret = SYS_IO_WriteRegArray(PQE_PM_M23_HW_REG_CPU_CCO,4,&data);
		ret = SYS_IO_WriteRegArray(PQE_PM_M23_HW_REG_CPU_PMCU0,4,&data);
		ret = SYS_IO_WriteRegArray(PQE_PM_M23_HW_REG_CPU_PMCU1,4,&data);
		ret = SYS_IO_WriteRegArray(PQE_PM_M23_HW_REG_CPU_PMCU2,4,&data);
		ret = SYS_IO_WriteRegArray(PQE_PM_M23_HW_REG_CPU_PMCU3,4,&data);

		CTOP_CTRL_EnterCriticalSection("pqepm_cg_on",flags);

		/* apb mask on */
		CTOP_CTRL_M23Ax_RdFL(CPU_POWER_CTRL, power_00);
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_00, apb_lockup_chk_en, 1);//4
		CTOP_CTRL_M23Ax_WrFL(CPU_POWER_CTRL, power_00);

		if (_g_pqe_pm_m23_cg > 0)
		{
			cg.udata32 = _g_pqe_pm_m23_cg;
		}
		else//normal
		{
			cg.udata32 = 0x07FEF800;
		}

		/* cg on */
		CTOP_CTRL_M23Ax_RdFL(CPU_POWER_CTRL, power_01);
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_tcon_ipw_clk_gate_en, cg.p.reg_tcon_ipw_clk_gate_en);//11
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_vsd_ipw_clk_gate_en , cg.p.reg_vsd_ipw_clk_gate_en );//12
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_vdo_ipw_clk_gate_en , cg.p.reg_vdo_ipw_clk_gate_en );//13
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_sre_ipw_clk_gate_en , cg.p.reg_sre_ipw_clk_gate_en );//14
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_nd_ipw_clk_gate_en  , cg.p.reg_nd_ipw_clk_gate_en  );//15
		// CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_lne_ipw_clk_gate_en , cg.p.reg_lne_ipw_clk_gate_en );//16 (aud)
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_led_ipw_clk_gate_en , cg.p.reg_led_ipw_clk_gate_en );//17
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_imx_ipw_clk_gate_en , cg.p.reg_imx_ipw_clk_gate_en );//18
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_hdr_ipw_clk_gate_en , cg.p.reg_hdr_ipw_clk_gate_en );//19
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_gsc_ipw_clk_gate_en , cg.p.reg_gsc_ipw_clk_gate_en );//20
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_me_ipw_clk_gate_en  , cg.p.reg_me_ipw_clk_gate_en  );//21
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_fms_ipw_clk_gate_en , cg.p.reg_fms_ipw_clk_gate_en );//22
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_fmc_ipw_clk_gate_en , cg.p.reg_fmc_ipw_clk_gate_en );//23
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_dne_ipw_clk_gate_en , cg.p.reg_dne_ipw_clk_gate_en );//24
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_cvi_ipw_clk_gate_en , cg.p.reg_cvi_ipw_clk_gate_en );//25
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_cco_ipw_clk_gate_en , cg.p.reg_cco_ipw_clk_gate_en );//26
		// CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_pmcu_ipw_clk_gate_en, cg.p.reg_pmcu_ipw_clk_gate_en);//27
		CTOP_CTRL_M23Ax_WrFL(CPU_POWER_CTRL, power_01);

		CTOP_CTRL_ExitCriticalSection("pqepm_cg_on",flags);
		#endif
		pqe_pm_noti("PQE_PM_HW_CG_ON done (cg:0x%08x)(dbg:0x%08x)\n",cg.udata32,_g_pqe_pm_m23_cg);
	}
	else if (cmd == PQE_PM_HW_CG_OFF)
	{
		/**
		see http://jira.lge.com/issue/browse/SICDTV-11139
		AR resume sequence
		wr 0xC8513004, 0x0
		wr 0xC8513000, rdata
		wr 0xCC200018, 0x0
		wr 0xCC201018, 0x0
		wr 0xCC401018, 0x0
		wr 0xCC801018, 0x0
		wr 0xCCC01018, 0x0
		wr 0xC600301C, 0x1
		wr 0xC440201C, 0x1
		wr 0xC800201C, 0x1
		*/

		#ifdef PQEPM_M23_USE_CTOP_REGS
		CTOP_CTRL_EnterCriticalSection("pqepm_cg_off",flags);

		/* cg off */
		CTOP_CTRL_M23Ax_RdFL(CPU_POWER_CTRL, power_01);
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_tcon_ipw_clk_gate_en, 0);//11
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_vsd_ipw_clk_gate_en , 0);//12
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_vdo_ipw_clk_gate_en , 0);//13
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_sre_ipw_clk_gate_en , 0);//14
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_nd_ipw_clk_gate_en  , 0);//15
		// CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_lne_ipw_clk_gate_en , 0);//16 (aud)
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_led_ipw_clk_gate_en , 0);//17
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_imx_ipw_clk_gate_en , 0);//18
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_hdr_ipw_clk_gate_en , 0);//19
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_gsc_ipw_clk_gate_en , 0);//20
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_me_ipw_clk_gate_en  , 0);//21
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_fms_ipw_clk_gate_en , 0);//22
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_fmc_ipw_clk_gate_en , 0);//23
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_dne_ipw_clk_gate_en , 0);//24
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_cvi_ipw_clk_gate_en , 0);//25
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_cco_ipw_clk_gate_en , 0);//26
		// CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_01, reg_pmcu_ipw_clk_gate_en, 0);//27
		CTOP_CTRL_M23Ax_WrFL(CPU_POWER_CTRL, power_01);

		/* apb mask on */
		CTOP_CTRL_M23Ax_RdFL(CPU_POWER_CTRL, power_00);
		CTOP_CTRL_M23Ax_Wr01(CPU_POWER_CTRL, power_00, apb_lockup_chk_en, 0);//4
		CTOP_CTRL_M23Ax_WrFL(CPU_POWER_CTRL, power_00);

		CTOP_CTRL_ExitCriticalSection("pqepm_cg_off",flags);

		// ret = SYS_IO_WriteRegArray(PQE_PM_M23_HW_REG_CPU_HDMI,4,&cpu_hdmi);
		// pqe_pm_noti("pqepm_cg_off cpu_hdmi pslverr_masking(0x%08x)\n",cpu_hdmi);

		data = 0x0;
		// ret = SYS_IO_WriteRegArray(PQE_PM_M23_HW_REG_CPU_DEMOD,4,&data);
		ret = SYS_IO_WriteRegArray(PQE_PM_M23_HW_REG_CPU_CCO,4,&data);
		ret = SYS_IO_WriteRegArray(PQE_PM_M23_HW_REG_CPU_PMCU0,4,&data);
		ret = SYS_IO_WriteRegArray(PQE_PM_M23_HW_REG_CPU_PMCU1,4,&data);
		ret = SYS_IO_WriteRegArray(PQE_PM_M23_HW_REG_CPU_PMCU2,4,&data);
		ret = SYS_IO_WriteRegArray(PQE_PM_M23_HW_REG_CPU_PMCU3,4,&data);

		data = 0x1;
		ret = SYS_IO_WriteRegArray(PQE_PM_M23_HW_REG_DEMOD_LKUP,4,&data);
		ret = SYS_IO_WriteRegArray(PQE_PM_M23_HW_REG_USB0_LKUP,4,&data);
		ret = SYS_IO_WriteRegArray(PQE_PM_M23_HW_REG_USB1_LKUP,4,&data);
		#endif

		pqe_pm_noti("PQE_PM_HW_CG_OFF done\n");
	}
	else if (cmd == PQE_PM_HW_FW_RESUME)
	{
		#ifdef INCLUDE_KDRV_DE
		vsc_resume(1);/* fw_start */
		#endif

		usleep_range(20000, 20000); // 20ms, It takes some time for interrupt to be enabled(AVTASK-1378)

		if (_g_pqe_pm_m23_enable == 10) {
			_pqe_pm_m23_hw_dbg_read_regs("fw_");//print only those that start with "fw_"
		}

		pqe_pm_noti("PQE_PM_HW_FW_RESUME done\n");
	}
	else
	{
		pqe_pm_error("unknown cmd 0x%x\n", cmd);
	}

	return RET_OK;
}

static void _pqe_pm_m23_hw_dbg_status(struct seq_file *m)
{
	int ret;
	UINT32 curr_data, i, number;
	struct pqe_pm_regs_entry *p_table;

	number = sizeof(_g_pqe_pm_m23_regs_table)/sizeof(_g_pqe_pm_m23_regs_table[0]);

	seq_printf(m, "[i ] %-15s %-10s %-10s %-10s %-10s\n","name","address","suspend","curr","resume");

	for (i=0; i<number; i++) {
		p_table = &_g_pqe_pm_m23_regs_table[i];
		if (p_table->address == 0x0)	continue;
		ret = SYS_IO_ReadRegArray(p_table->address,4,&curr_data);
		seq_printf(m, "[%02d] %-15s 0x%08x 0x%08x 0x%08x 0x%08x\n",\
			i,p_table->name,p_table->address,p_table->data_suspend,curr_data,p_table->data_resume);
	}
}

static void _pqe_pm_m23_hw_dbg_read_regs(char *prefix)
{
	int ret;
	UINT32 curr_data, i, number;
	UINT32 prefix_size = 0;
	struct pqe_pm_regs_entry *p_table;

	if (prefix)
	{
		prefix_size = strlen(prefix);
	}

	number = sizeof(_g_pqe_pm_m23_regs_table)/sizeof(_g_pqe_pm_m23_regs_table[0]);

	pqe_pm_noti("[i ] %-20s %-10s %-10s %-10s %-10s\n","name","address","suspend","curr","resume");
	for (i=0; i<number; i++) {
		p_table = &_g_pqe_pm_m23_regs_table[i];

		if (prefix_size > 0)
		{
			if (0 != strncmp(p_table->name,prefix,prefix_size))//no matching
			{
				continue;
			}
		}

		ret = SYS_IO_ReadRegArray(p_table->address,4,&curr_data);
		pqe_pm_noti("[%02d] %-20s 0x%08x 0x%08x 0x%08x 0x%08x\n",\
			i,p_table->name,p_table->address,p_table->data_suspend,curr_data,p_table->data_resume);
	}
}
