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
#define PQEPM_O24_USE_CTOP_REGS
#endif

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "pqe_pm_impl.h"
#include "../sys/sys_io.h"

#ifdef PQEPM_O24_USE_CTOP_REGS
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
static int _pqe_pm_o24_hw_handler(int cmd);
static void _pqe_pm_o24_hw_dbg_status(struct seq_file *m);
static void _pqe_pm_o24_hw_dbg_read_regs(char *prefix);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static int _g_pqe_pm_o24_enable = 1;
module_param_named(pqepm_o24_en, _g_pqe_pm_o24_enable, int, 0644);

static uint _g_pqe_pm_o24_cg = 0;
module_param_named(pqepm_o24_cg, _g_pqe_pm_o24_cg, uint, 0644);

/* list (AVTASK-975) */
#define PQE_PM_O24_HW_REG_C4TX_PDB  0xCC933024
#define PQE_PM_O24_HW_REG_DISP_CLK  0xCC932060
#define PQE_PM_O24_HW_REG_APB1_HUB0 0xC6000018
#define PQE_PM_O24_HW_REG_APB2_HUB0 0xC8000018
#define PQE_PM_O24_HW_REG_PMCU_HUBM 0xCC200018
#define PQE_PM_O24_HW_REG_PMCU0_CPU 0xCC210018
#define PQE_PM_O24_HW_REG_PMCU1_CPU 0xCC400018
#define PQE_PM_O24_HW_REG_PMCU2_CPU 0xCC800018
#define PQE_PM_O24_HW_REG_PMCU3_CPU 0xCCC00018
#define PQE_PM_O24_HW_REG_POWER_00  0xC63F3000
#define PQE_PM_O24_HW_REG_POWER_01  0xC63F3010
#define PQE_PM_O24_HW_REG_POWER_02  0xC63F3014

/* intr list (AVTASK-1378) */
#define PQE_PM_O24_HW_REG_INTR_IPC_PQE     0xCC0A01E4
#define PQE_PM_O24_HW_REG_INTR_IPC_VDEC    0xCC0A01F4
#define PQE_PM_O24_HW_REG_INTR_MCU_EXT_EN  0xCC08000C
#define PQE_PM_O24_HW_REG_INTR_MCU_INT_EN  0xCC08001C
#define PQE_PM_O24_HW_REG_INTR_CVI_MASK    0xCCCC0014
#define PQE_PM_O24_HW_REG_INTR_IMX_MASK    0xCC820014
#define PQE_PM_O24_HW_REG_INTR_HDR_MASK    0xCCC10014
#define PQE_PM_O24_HW_REG_INTR_ND0_MASK    0xCCC60014
#define PQE_PM_O24_HW_REG_INTR_SRE_MASK    0xCC620014
#define PQE_PM_O24_HW_REG_INTR_GSC_MASK    0xCC460014
#define PQE_PM_O24_HW_REG_INTR_VSD_MASK    0xCCA20014
#define PQE_PM_O24_HW_REG_INTR_CCO_MASK    0xCC860014

struct pqe_pm_regs_entry _g_pqe_pm_o24_regs_table[] = {
{"c4tx_pdb",  PQE_PM_O24_HW_REG_C4TX_PDB,   0x00000000,  0x01FFFFFF},
{"disp_clk",  PQE_PM_O24_HW_REG_DISP_CLK,   0x00000015,  0x00000005},
{"apb1_hub0", PQE_PM_O24_HW_REG_APB1_HUB0,  0x00000011,  0x00000010},
{"apb2_hub0", PQE_PM_O24_HW_REG_APB2_HUB0,  0x00000011,  0x00000010},
{"pmcu_hubm", PQE_PM_O24_HW_REG_PMCU_HUBM,  0x00000011,  0x00000010},
{"pmcu0_cpu", PQE_PM_O24_HW_REG_PMCU0_CPU,  0x00000011,  0x00000010},
{"pmcu1_cpu", PQE_PM_O24_HW_REG_PMCU1_CPU,  0x00000011,  0x00000010},
{"pmcu2_cpu", PQE_PM_O24_HW_REG_PMCU2_CPU,  0x00000011,  0x00000010},
{"pmcu3_cpu", PQE_PM_O24_HW_REG_PMCU3_CPU,  0x00000011,  0x00000010},
{"power_00",  PQE_PM_O24_HW_REG_POWER_00,   0x00001111,  0x00001101},
{"power_01",  PQE_PM_O24_HW_REG_POWER_01,   0x00FFFFFF,  0x00000000},
{"power_02",  PQE_PM_O24_HW_REG_POWER_02,   0x000001F7,  0x00000000},
{"intr_ipc_pqe",   PQE_PM_O24_HW_REG_INTR_IPC_PQE,     0x00000000,  0x0000003f},
{"intr_ipc_vdec",  PQE_PM_O24_HW_REG_INTR_IPC_VDEC,    0x00000000,  0x0000003f},
{"intr_mcu_ext",   PQE_PM_O24_HW_REG_INTR_MCU_EXT_EN,  0x50200000,  0xdf780000},
{"intr_mcu_int",   PQE_PM_O24_HW_REG_INTR_MCU_INT_EN,  0x00200000,  0x00200000},
{"intr_cvi_mask",  PQE_PM_O24_HW_REG_INTR_CVI_MASK,    0xffffffff,  0x7fffffff},
{"intr_imx_mask",  PQE_PM_O24_HW_REG_INTR_IMX_MASK,    0xffffffff,  0xffaf8afa},
{"intr_hdr_mask",  PQE_PM_O24_HW_REG_INTR_HDR_MASK,    0xffffffff,  0x891dffff},
{"intr_nd0_mask",  PQE_PM_O24_HW_REG_INTR_ND0_MASK,    0xffffffff,  0xfffffeff},
{"intr_sre_mask",  PQE_PM_O24_HW_REG_INTR_SRE_MASK,    0xffffffff,  0xffffbbff},
{"intr_gsc_mask",  PQE_PM_O24_HW_REG_INTR_GSC_MASK,    0xffffffff,  0xffffefff},
{"intr_vsd_mask",  PQE_PM_O24_HW_REG_INTR_VSD_MASK,    0xffffffff,  0xfffefffc},
{"intr_cco_mask",  PQE_PM_O24_HW_REG_INTR_CCO_MASK,    0xffffffff,  0xffffffff}};

/*========================================================================================
	Implementation Group
========================================================================================*/
void pqe_pm_init_o24_hw_ctx(void)
{
	pqe_pm_register_hw_handler(_pqe_pm_o24_hw_handler);
	pqe_pm_register_enable(&_g_pqe_pm_o24_enable);
	pqe_pm_register_hw_dbg_status(_pqe_pm_o24_hw_dbg_status);
}

static int _pqe_pm_o24_hw_handler(int cmd)
{
	#ifdef PQEPM_O24_USE_CTOP_REGS
	int ret;
	//unsigned int flags;
	unsigned int data;
	union {
		UINT32 udata32;
		MICOM_PW_CTRL_POWER_01_O24A0_T p;//micom:0xF33F3010,mcu:0xCC3F3010,cpu:0xC63F3010
	} cg;
	static unsigned int apb2_hub0 = 0x10;
	#endif

	if (cmd == PQE_PM_HW_FW_SUSPEND)
	{
		#ifdef INCLUDE_KDRV_DE
		vsc_suspend(1);/* fw_stop */
		#endif

		if (_g_pqe_pm_o24_enable == 10)
		{
			_pqe_pm_o24_hw_dbg_read_regs("intr_");
		}

		pqe_pm_noti("PQE_PM_HW_FW_SUSPEND done\n");
	}
	else if (cmd == PQE_PM_HW_CG_ON)
	{
		usleep_range(20000, 20000); // 20ms, see http://clm.lge.com/issue/browse/SICDTV-13478

		#ifdef PQEPM_O24_USE_CTOP_REGS
		/************************************************************************/
		/* guide from SICDTV-12981 */
		/************************************************************************/
		ret = SYS_IO_ReadRegArray(PQE_PM_O24_HW_REG_APB2_HUB0,4,&apb2_hub0);
		data = apb2_hub0 | 0x1;
		ret = SYS_IO_WriteRegArray(PQE_PM_O24_HW_REG_APB2_HUB0,4,&data);//add dsc masking to avoid lockup on hdmi 144 input when CG on(AVTASK-1376)
		pqe_pm_noti("[CG_ON] APB2_HUB0 PSLVERR_MASKING(0x%08x)(pre:0x%08x)\n",data,apb2_hub0);

		data = 0x11;
		ret = SYS_IO_WriteRegArray(PQE_PM_O24_HW_REG_APB1_HUB0,4,&data);
		ret = SYS_IO_WriteRegArray(PQE_PM_O24_HW_REG_PMCU_HUBM,4,&data);
		ret = SYS_IO_WriteRegArray(PQE_PM_O24_HW_REG_PMCU0_CPU,4,&data);
		ret = SYS_IO_WriteRegArray(PQE_PM_O24_HW_REG_PMCU1_CPU,4,&data);
		ret = SYS_IO_WriteRegArray(PQE_PM_O24_HW_REG_PMCU2_CPU,4,&data);
		ret = SYS_IO_WriteRegArray(PQE_PM_O24_HW_REG_PMCU3_CPU,4,&data);

		//CTOP_CTRL_EnterCriticalSection("pqepm_cg",flags);

		/* apb mask on */
		CTOP_CTRL_O24Ax_RdFL(CPU_PW_CTRL, power_00);
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_00, apb_lockup_chk_en, 1);//4
		CTOP_CTRL_O24Ax_WrFL(CPU_PW_CTRL, power_00);

		if (_g_pqe_pm_o24_cg > 0)
		{
			cg.udata32 = _g_pqe_pm_o24_cg;
		}
		else//normal
		{
			cg.udata32 = 0xFFFFFF;
			//cg.p.reg_lnx1_ipw_clk_gate_en = 0;
			//cg.p.reg_lnx0_ipw_clk_gate_en = 0;
		}

		/* cg on */
		CTOP_CTRL_O24Ax_RdFL(CPU_PW_CTRL, power_01);
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_mefms_sbw_clk_gate_en, cg.p.reg_mefms_sbw_clk_gate_en);//0
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_imvd_sbw_clk_gate_en , cg.p.reg_imvd_sbw_clk_gate_en );//1
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_fmgse_sbw_clk_gate_en, cg.p.reg_fmgse_sbw_clk_gate_en);//2
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_vsd_ipw_clk_gate_en  , cg.p.reg_vsd_ipw_clk_gate_en  );//3
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_vdo_ipw_clk_gate_en  , cg.p.reg_vdo_ipw_clk_gate_en  );//4
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_tcon_ipw_clk_gate_en , cg.p.reg_tcon_ipw_clk_gate_en );//5
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_sre_ipw_clk_gate_en  , cg.p.reg_sre_ipw_clk_gate_en  );//6
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_nd1_ipw_clk_gate_en  , cg.p.reg_nd1_ipw_clk_gate_en  );//7
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_nd0_ipw_clk_gate_en  , cg.p.reg_nd0_ipw_clk_gate_en  );//8
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_me1_ipw_clk_gate_en  , cg.p.reg_me1_ipw_clk_gate_en  );//9
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_me0_ipw_clk_gate_en  , cg.p.reg_me0_ipw_clk_gate_en  );//10
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_lnx1_ipw_clk_gate_en , cg.p.reg_lnx1_ipw_clk_gate_en );//11
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_lnx0_ipw_clk_gate_en , cg.p.reg_lnx0_ipw_clk_gate_en );//12
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_led_ipw_clk_gate_en  , cg.p.reg_led_ipw_clk_gate_en  );//13
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_imx_ipw_clk_gate_en  , cg.p.reg_imx_ipw_clk_gate_en  );//14
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_hdr_ipw_clk_gate_en  , cg.p.reg_hdr_ipw_clk_gate_en  );//15
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_gsc_ipw_clk_gate_en  , cg.p.reg_gsc_ipw_clk_gate_en  );//16
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_fms_ipw_clk_gate_en  , cg.p.reg_fms_ipw_clk_gate_en  );//17
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_fmc_ipw_clk_gate_en  , cg.p.reg_fmc_ipw_clk_gate_en  );//18
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_dsc_ipw_clk_gate_en  , cg.p.reg_dsc_ipw_clk_gate_en  );//19
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_dnsr_ipw_clk_gate_en , cg.p.reg_dnsr_ipw_clk_gate_en );//20
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_dnnr_ipw_clk_gate_en , cg.p.reg_dnnr_ipw_clk_gate_en );//21
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_cvi_ipw_clk_gate_en  , cg.p.reg_cvi_ipw_clk_gate_en  );//22
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_cco_ipw_clk_gate_en  , cg.p.reg_cco_ipw_clk_gate_en  );//23
		//CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_pmcu_ipw_clk_gate_en , cg.p.reg_pmcu_ipw_clk_gate_en );//24
		CTOP_CTRL_O24Ax_WrFL(CPU_PW_CTRL, power_01);

		//CTOP_CTRL_ExitCriticalSection("pqepm_cg",flags);
		#endif

		pqe_pm_noti("PQE_PM_HW_CG_ON done (cg:0x%08x)(dbg:0x%08x)\n",cg.udata32,_g_pqe_pm_o24_cg);
	}
	else if (cmd == PQE_PM_HW_CG_OFF)
	{
		//20231121, remove here (see http://clm.lge.com/issue/browse/SICDTV-13415)
		//#ifdef INCLUDE_KDRV_SYS
		// see http://clm.lge.com/issue/browse/AVTASK-683
		//pqe_pm_noti("force SYS to make up\n");
		//SYS_RequestForceRuntimeResume();
		//#endif

		#ifdef PQEPM_O24_USE_CTOP_REGS
		/************************************************************************/
		/* guide from SICDTV-12981 */
		/************************************************************************/
		//CTOP_CTRL_EnterCriticalSection("pqepm_cg",flags);

		/* cg off */
		CTOP_CTRL_O24Ax_RdFL(CPU_PW_CTRL, power_01);
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_mefms_sbw_clk_gate_en, 0);//0
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_imvd_sbw_clk_gate_en , 0);//1
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_fmgse_sbw_clk_gate_en, 0);//2
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_vsd_ipw_clk_gate_en  , 0);//3
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_vdo_ipw_clk_gate_en  , 0);//4
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_tcon_ipw_clk_gate_en , 0);//5
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_sre_ipw_clk_gate_en  , 0);//6
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_nd1_ipw_clk_gate_en  , 0);//7
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_nd0_ipw_clk_gate_en  , 0);//8
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_me1_ipw_clk_gate_en  , 0);//9
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_me0_ipw_clk_gate_en  , 0);//10
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_lnx1_ipw_clk_gate_en , 0);//11
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_lnx0_ipw_clk_gate_en , 0);//12
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_led_ipw_clk_gate_en  , 0);//13
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_imx_ipw_clk_gate_en  , 0);//14
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_hdr_ipw_clk_gate_en  , 0);//15
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_gsc_ipw_clk_gate_en  , 0);//16
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_fms_ipw_clk_gate_en  , 0);//17
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_fmc_ipw_clk_gate_en  , 0);//18
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_dsc_ipw_clk_gate_en  , 0);//19
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_dnsr_ipw_clk_gate_en , 0);//20
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_dnnr_ipw_clk_gate_en , 0);//21
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_cvi_ipw_clk_gate_en  , 0);//22
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_cco_ipw_clk_gate_en  , 0);//23
		//CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_01, reg_pmcu_ipw_clk_gate_en , 0);//24
		CTOP_CTRL_O24Ax_WrFL(CPU_PW_CTRL, power_01);

		/* apb mask off */
		CTOP_CTRL_O24Ax_RdFL(CPU_PW_CTRL, power_00);
		CTOP_CTRL_O24Ax_Wr01(CPU_PW_CTRL, power_00, apb_lockup_chk_en, 0);//4
		CTOP_CTRL_O24Ax_WrFL(CPU_PW_CTRL, power_00);

		//CTOP_CTRL_ExitCriticalSection("pqepm_cg",flags);

		ret = SYS_IO_WriteRegArray(PQE_PM_O24_HW_REG_APB2_HUB0,4,&apb2_hub0);
		pqe_pm_noti("[CG_OFF] APB2_HUB0 PSLVERR_MASKING(0x%08x)\n",apb2_hub0);

		data = 0x10;
		ret = SYS_IO_WriteRegArray(PQE_PM_O24_HW_REG_APB1_HUB0,4,&data);
		ret = SYS_IO_WriteRegArray(PQE_PM_O24_HW_REG_PMCU_HUBM,4,&data);
		ret = SYS_IO_WriteRegArray(PQE_PM_O24_HW_REG_PMCU0_CPU,4,&data);
		ret = SYS_IO_WriteRegArray(PQE_PM_O24_HW_REG_PMCU1_CPU,4,&data);
		ret = SYS_IO_WriteRegArray(PQE_PM_O24_HW_REG_PMCU2_CPU,4,&data);
		ret = SYS_IO_WriteRegArray(PQE_PM_O24_HW_REG_PMCU3_CPU,4,&data);

		#endif

		pqe_pm_noti("PQE_PM_HW_CG_OFF done\n");
	}
	else if (cmd == PQE_PM_HW_FW_RESUME)
	{
		#ifdef INCLUDE_KDRV_DE
		vsc_resume(1);/* fw_start */
		#endif

		usleep_range(20000, 20000); // 20ms, It takes some time for interrupt to be enabled(AVTASK-1378)

		if (_g_pqe_pm_o24_enable == 10)
		{
			_pqe_pm_o24_hw_dbg_read_regs("intr_");
		}

		pqe_pm_noti("PQE_PM_HW_FW_RESUME done\n");
	}
	else
	{
		pqe_pm_error("unknown cmd 0x%x\n", cmd);
	}

	return RET_OK;
}

static void _pqe_pm_o24_hw_dbg_status(struct seq_file *m)
{
	int ret;
	UINT32 curr_data, i, number;
	struct pqe_pm_regs_entry *p_table;

	number = sizeof(_g_pqe_pm_o24_regs_table)/sizeof(_g_pqe_pm_o24_regs_table[0]);

	seq_printf(m, "[i ] %-20s %-10s %-10s %-10s %-10s\n","name","address","suspend","curr","resume");

	for (i=0; i<number; i++) {
		p_table = &_g_pqe_pm_o24_regs_table[i];
		ret = SYS_IO_ReadRegArray(p_table->address,4,&curr_data);
		seq_printf(m, "[%02d] %-20s 0x%08x 0x%08x 0x%08x 0x%08x\n",\
			i,p_table->name,p_table->address,p_table->data_suspend,curr_data,p_table->data_resume);
	}
}

static void _pqe_pm_o24_hw_dbg_read_regs(char *prefix)
{
	int ret;
	UINT32 curr_data, i, number;
	UINT32 prefix_size = 0;
	struct pqe_pm_regs_entry *p_table;

	if (prefix)
	{
		prefix_size = strlen(prefix);
	}

	number = sizeof(_g_pqe_pm_o24_regs_table)/sizeof(_g_pqe_pm_o24_regs_table[0]);

	pqe_pm_noti("[i ] %-20s %-10s %-10s %-10s %-10s\n","name","address","suspend","curr","resume");
	for (i=0; i<number; i++) {
		p_table = &_g_pqe_pm_o24_regs_table[i];

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
