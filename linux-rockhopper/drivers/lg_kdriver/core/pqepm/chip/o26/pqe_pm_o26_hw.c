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
#define PQEPM_O26_USE_CTOP_REGS
#endif

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "pqe_pm_impl.h"
#ifdef PQEPM_O26_USE_CTOP_REGS
#include "../sys/sys_io.h"
#include "../sys/sys_regs.h"
#endif

#ifdef INCLUDE_KDRV_SYS
#include "sys_drv.h"
#endif

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
	UINT32 addr;
	UINT32 suspend;
	UINT32 resume;
	UINT32 target;
	UINT32 backup;
};

union pqe_pm_cg {
	UINT32 udata32;
	struct {
	UINT32 reg_fme_sbw_clk_gate_en   :1; //( 0)
	UINT32 reg_srco_sbw_clk_gate_en  :1; //( 1)
	UINT32 reg_vsd_ipw_clk_gate_en   :1; //( 2)
	UINT32 reg_vdo_ipw_clk_gate_en   :1; //( 3)
	UINT32 reg_tcon_ipw_clk_gate_en  :1; //( 4)
	UINT32 reg_sre_ipw_clk_gate_en   :1; //( 5)
	UINT32 reg_npp_ipw_clk_gate_en   :1; //( 6)
	UINT32 reg_nd1_ipw_clk_gate_en   :1; //( 7)
	UINT32 reg_nd0_ipw_clk_gate_en   :1; //( 8)
	UINT32 reg_me1_ipw_clk_gate_en   :1; //( 9)
	UINT32 reg_me0_ipw_clk_gate_en   :1; //(10)
	UINT32 reg_lnx1_ipw_clk_gate_en  :1; //(11)
	UINT32 reg_lnx0_ipw_clk_gate_en  :1; //(12)
	UINT32 reg_led_ipw_clk_gate_en   :1; //(13)
	UINT32 reg_imx_ipw_clk_gate_en   :1; //(14)
	UINT32 reg_hdr_ipw_clk_gate_en   :1; //(15)
	UINT32 reg_gsc_ipw_clk_gate_en   :1; //(16)
	UINT32 reg_fms_ipw_clk_gate_en   :1; //(17)
	UINT32 reg_fmc_ipw_clk_gate_en   :1; //(18)
	UINT32 reg_dsc_ipw_clk_gate_en   :1; //(19)
	UINT32 reg_dnsr1_ipw_clk_gate_en :1; //(20)
	UINT32 reg_dnsr0_ipw_clk_gate_en :1; //(21)
	UINT32 reg_cvi_ipw_clk_gate_en   :1; //(22)
	UINT32 reg_cco_ipw_clk_gate_en   :1; //(23)
	UINT32 reg_pmcu_ipw_clk_gate_en  :1; //(24)
	UINT32 rsvd0                     :3; //(27:25)
	UINT32 dnsr0_sr_cg_en            :1; //(28) core clk only (SICDTV-14381)
	UINT32 dnsr1_sr_cg_en            :1; //(29) core clk only (SICDTV-14381)
	UINT32 rsvd1                     :2; //(31:02)
	};
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
static int _pqe_pm_o26_hw_handler(int cmd);
static void _pqe_pm_o26_hw_dbg_status(struct seq_file *m);
static void _pqe_pm_o26_hw_dbg_read_regs(char *prefix);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
#define PQE_PM_O26_HW_CG_CTRL_OFF  (0)
#define PQE_PM_O26_HW_CG_CTRL_IP   (1)
#define PQE_PM_O26_HW_CG_CTRL_CTOP (2)
#define PQE_PM_O26_HW_DBG_PRINT    (10)
static int _g_pqe_pm_o26_enable = 1;//0:cg ctrl off, 1:ip cg, 2:ctop cg
module_param_named(pqepm_o26_en, _g_pqe_pm_o26_enable, int, 0644);

static uint _g_pqe_pm_o26_cg = 0;
module_param_named(pqepm_o26_cg, _g_pqe_pm_o26_cg, uint, 0644);

/* list */
#define PQE_PM_O26_REG_C4TX_PDB       0xCC974024
#define PQE_PM_O26_REG_CLK_MUX_SEL    0xCC975060
#define PQE_PM_O26_SCRG_CTRL_DNSR0_02 0xCC490008
#define PQE_PM_O26_SCRG_CTRL_DNSR1_02 0xCC4B0008

/* ctop list (http://jira.lge.com/issue/browse/SICDTV-15933) */
#define PQE_PM_O26_APB0_CPU__PSLVERR_MASKING 0xC4000018
#define PQE_PM_O26_APB0_CPU___LOCKUP_MODE_EN 0xC400001C
#define PQE_PM_O26_APB0_CPUM__LOCKUP_MODE_EN 0xC400101C
#define PQE_PM_O26_APB1_CPU__PSLVERR_MASKING 0xC6000018
#define PQE_PM_O26_APB1_CPU___LOCKUP_MODE_EN 0xC600001C
#define PQE_PM_O26_APB2_CPU__PSLVERR_MASKING 0xC8000018
#define PQE_PM_O26_APB2_CPU___LOCKUP_MODE_EN 0xC800001C
#define PQE_PM_O26_APB2_BMC___LOCKUP_MODE_EN 0xC880201C
#define PQE_PM_O26_APB3_CPU__PSLVERR_MASKING 0xCA000018
#define PQE_PM_O26_APB3_CPU___LOCKUP_MODE_EN 0xCA00001C
#define PQE_PM_O26_APB3_CPUH__LOCKUP_MODE_EN 0xCA00101C
#define PQE_PM_O26_APB3_CPUM__LOCKUP_MODE_EN 0xCA00201C
#define PQE_PM_O26_APB3_WOC___LOCKUP_MODE_EN 0xCA00501C
#define PQE_PM_O26_PMCU_CPU__PSLVERR_MASKING 0xCC200018
#define PQE_PM_O26_PMCU_CPU___LOCKUP_MODE_EN 0xCC20001C
#define PQE_PM_O26_PMCU0_CPU_PSLVERR_MASKING 0xCC210018
#define PQE_PM_O26_PMCU0_CPU__LOCKUP_MODE_EN 0xCC21001C
#define PQE_PM_O26_PMCU0_CPUH_LOCKUP_MODE_EN 0xCC21101C
#define PQE_PM_O26_PMCU1_CPU_PSLVERR_MASKING 0xCC400018
#define PQE_PM_O26_PMCU1_CPU__LOCKUP_MODE_EN 0xCC40001C
#define PQE_PM_O26_PMCU2_CPU_PSLVERR_MASKING 0xCC800018
#define PQE_PM_O26_PMCU2_CPU__LOCKUP_MODE_EN 0xCC80001C
#define PQE_PM_O26_PMCU3_CPU_PSLVERR_MASKING 0xCCC00018
#define PQE_PM_O26_PMCU3_CPU__LOCKUP_MODE_EN 0xCCC0001C
#define PQE_PM_O26_VMCU_CPU__PSLVERR_MASKING 0xCE200018
#define PQE_PM_O26_VMCU_CPU___LOCKUP_MODE_EN 0xCE20001C
#define PQE_PM_O26_VMCU0_CPU_PSLVERR_MASKING 0xCE210018
#define PQE_PM_O26_VMCU0_CPU__LOCKUP_MODE_EN 0xCE21001C
#define PQE_PM_O26_VMCU0_CPUH_LOCKUP_MODE_EN 0xCE21101C
#define PQE_PM_O26_VMCU1_CPU_PSLVERR_MASKING 0xCE400018
#define PQE_PM_O26_VMCU1_CPU__LOCKUP_MODE_EN 0xCE40001C
#define PQE_PM_O26_CPU_PW_CTRL_POWER00       0xCA3A2000
#define PQE_PM_O26_CPU_PW_CTRL_POWER01       0xCA3A2010

/* pqe pic_init list */
#define PQE_PM_O26_FMC_CTRL_PIC_INIT 0xCCC41000
#define PQE_PM_O26_GSC_CTRL_PIC_INIT 0xCCC70000
#define PQE_PM_O26_VSD_CTRL_PIC_INIT 0xCC950000
#define PQE_PM_O26_CCI_CTRL_PIC_INIT 0xCC880000

/* pqe intr list */
#define PQE_PM_O26_INTR_IPC_PQE      0xCC0A01E4
#define PQE_PM_O26_INTR_IPC_VDEC     0xCC0A01F4
#define PQE_PM_O26_INTR_UART         0xCC000038
#define PQE_PM_O26_INTR_MCU_EXT_EN   0xCC08000C
#define PQE_PM_O26_INTR_MCU_INT_EN   0xCC08001C
#define PQE_PM_O26_INTR_MCU_FLAG_EN  0xCC080064
#define PQE_PM_O26_INTR2_AIBSP_EN    0xCC080070
#define PQE_PM_O26_INTR_CVI_MASK     0xCC4E0014
#define PQE_PM_O26_INTR_IMX_MASK     0xCCC10014
#define PQE_PM_O26_INTR_HDR_MASK     0xCC230014
#define PQE_PM_O26_INTR_ND0_MASK     0xCC290014
#define PQE_PM_O26_INTR_SRE_MASK     0xCCA00014
#define PQE_PM_O26_INTR_GSC_MASK     0xCCC70014
#define PQE_PM_O26_INTR_VSD_MASK     0xCC950014
#define PQE_PM_O26_INTR_CCO_MASK     0xCC880014

/* name(20%s), addr, suspend, resume */
struct pqe_pm_regs_entry _g_pqe_pm_o26_regs_table[] = {
{.name="C4TX_PDB                 ", .addr=PQE_PM_O26_REG_C4TX_PDB             , .suspend=0x00000000, .resume=0x0100ffff, .target=0},
{.name="CLK_MUX_SEL              ", .addr=PQE_PM_O26_REG_CLK_MUX_SEL          , .suspend=0x00000001, .resume=0x00000001, .target=0},
{.name="SCRG_CTRL_DNSR0_02       ", .addr=PQE_PM_O26_SCRG_CTRL_DNSR0_02       , .suspend=0x00000040, .resume=0x00000000, .target=0},
{.name="SCRG_CTRL_DNSR1_02       ", .addr=PQE_PM_O26_SCRG_CTRL_DNSR1_02       , .suspend=0x00000040, .resume=0x00000000, .target=0},
{.name="FW_FMC_CTRL_PIC_INIT     ", .addr=PQE_PM_O26_FMC_CTRL_PIC_INIT        , .suspend=0x00000000, .resume=0x00230000, .target=0},
{.name="FW_GSC_CTRL_PIC_INIT     ", .addr=PQE_PM_O26_GSC_CTRL_PIC_INIT        , .suspend=0x00000000, .resume=0x00630000, .target=0},
{.name="FW_VSD_CTRL_PIC_INIT     ", .addr=PQE_PM_O26_VSD_CTRL_PIC_INIT        , .suspend=0x00000000, .resume=0x000f0000, .target=0},
{.name="FW_CCI_CTRL_PIC_INIT     ", .addr=PQE_PM_O26_CCI_CTRL_PIC_INIT        , .suspend=0x00000000, .resume=0x00130000, .target=0},
{.name="FW_INTR_IPC_PQE          ", .addr=PQE_PM_O26_INTR_IPC_PQE             , .suspend=0x0000003f, .resume=0x0000003f, .target=0},
{.name="FW_INTR_IPC_VDEC         ", .addr=PQE_PM_O26_INTR_IPC_VDEC            , .suspend=0x0000003f, .resume=0x0000003f, .target=0},
{.name="FW_INTR_UART             ", .addr=PQE_PM_O26_INTR_UART                , .suspend=0x00000000, .resume=0x00000000, .target=0},
{.name="FW_INTR_MCU_EXT_EN       ", .addr=PQE_PM_O26_INTR_MCU_EXT_EN          , .suspend=0x50200000, .resume=0xdf7a0000, .target=0},
{.name="FW_INTR_MCU_INT_EN       ", .addr=PQE_PM_O26_INTR_MCU_INT_EN          , .suspend=0x00200000, .resume=0x00200000, .target=0},
{.name="FW_INTR_MCU_FLAG_EN      ", .addr=PQE_PM_O26_INTR_MCU_FLAG_EN         , .suspend=0x00000000, .resume=0x0108affe, .target=0},
{.name="FW_INTR2_AIBSP_EN        ", .addr=PQE_PM_O26_INTR2_AIBSP_EN           , .suspend=0x00000000, .resume=0xffffffff, .target=0},
{.name="FW_INTR_CVI_MASK         ", .addr=PQE_PM_O26_INTR_CVI_MASK            , .suspend=0xffffffff, .resume=0x7fffffff, .target=0},
{.name="FW_INTR_IMX_MASK         ", .addr=PQE_PM_O26_INTR_IMX_MASK            , .suspend=0xffffffff, .resume=0xffaf8afa, .target=0},
{.name="FW_INTR_HDR_MASK         ", .addr=PQE_PM_O26_INTR_HDR_MASK            , .suspend=0xffffffff, .resume=0x891dffff, .target=0},
{.name="FW_INTR_ND0_MASK         ", .addr=PQE_PM_O26_INTR_ND0_MASK            , .suspend=0xffffffff, .resume=0xfffffeff, .target=0},
{.name="FW_INTR_SRE_MASK         ", .addr=PQE_PM_O26_INTR_SRE_MASK            , .suspend=0xffffffff, .resume=0xffffbbff, .target=0},
{.name="FW_INTR_GSC_MASK         ", .addr=PQE_PM_O26_INTR_GSC_MASK            , .suspend=0xffffffff, .resume=0xfffffbff, .target=0},
{.name="FW_INTR_VSD_MASK         ", .addr=PQE_PM_O26_INTR_VSD_MASK            , .suspend=0xffffffff, .resume=0xfffefffc, .target=0},
{.name="FW_INTR_CCO_MASK         ", .addr=PQE_PM_O26_INTR_CCO_MASK            , .suspend=0xffffffff, .resume=0xffffffff, .target=0},
{.name="APB0_CPU__PSLVERR_MASKING", .addr=PQE_PM_O26_APB0_CPU__PSLVERR_MASKING, .suspend=0x00000011, .resume=0x00000010, .target=1},
{.name="APB0_CPU___LOCKUP_MODE_EN", .addr=PQE_PM_O26_APB0_CPU___LOCKUP_MODE_EN, .suspend=0x00000000, .resume=0x00000001, .target=1},
{.name="APB0_CPUM__LOCKUP_MODE_EN", .addr=PQE_PM_O26_APB0_CPUM__LOCKUP_MODE_EN, .suspend=0x00000000, .resume=0x00000001, .target=1},
{.name="APB1_CPU__PSLVERR_MASKING", .addr=PQE_PM_O26_APB1_CPU__PSLVERR_MASKING, .suspend=0x00000011, .resume=0x00000010, .target=1},
{.name="APB1_CPU___LOCKUP_MODE_EN", .addr=PQE_PM_O26_APB1_CPU___LOCKUP_MODE_EN, .suspend=0x00000000, .resume=0x00000001, .target=1},
{.name="APB2_CPU__PSLVERR_MASKING", .addr=PQE_PM_O26_APB2_CPU__PSLVERR_MASKING, .suspend=0x00000011, .resume=0x00000001, .target=1},//hdmi21
{.name="APB2_CPU___LOCKUP_MODE_EN", .addr=PQE_PM_O26_APB2_CPU___LOCKUP_MODE_EN, .suspend=0x00000000, .resume=0x00000001, .target=1},
{.name="APB2_BMC___LOCKUP_MODE_EN", .addr=PQE_PM_O26_APB2_BMC___LOCKUP_MODE_EN, .suspend=0x00000000, .resume=0x00000001, .target=1},
{.name="APB3_CPU__PSLVERR_MASKING", .addr=PQE_PM_O26_APB3_CPU__PSLVERR_MASKING, .suspend=0x00000011, .resume=0x00000010, .target=1},
{.name="APB3_CPU___LOCKUP_MODE_EN", .addr=PQE_PM_O26_APB3_CPU___LOCKUP_MODE_EN, .suspend=0x00000000, .resume=0x00000001, .target=1},
{.name="APB3_CPUH__LOCKUP_MODE_EN", .addr=PQE_PM_O26_APB3_CPUH__LOCKUP_MODE_EN, .suspend=0x00000000, .resume=0x00000001, .target=1},
{.name="APB3_CPUM__LOCKUP_MODE_EN", .addr=PQE_PM_O26_APB3_CPUM__LOCKUP_MODE_EN, .suspend=0x00000000, .resume=0x00000001, .target=1},
{.name="APB3_WOC___LOCKUP_MODE_EN", .addr=PQE_PM_O26_APB3_WOC___LOCKUP_MODE_EN, .suspend=0x00000000, .resume=0x00000001, .target=1},
{.name="PMCU_CPU__PSLVERR_MASKING", .addr=PQE_PM_O26_PMCU_CPU__PSLVERR_MASKING, .suspend=0x00000011, .resume=0x00000001, .target=1},//hdmi21
{.name="PMCU_CPU___LOCKUP_MODE_EN", .addr=PQE_PM_O26_PMCU_CPU___LOCKUP_MODE_EN, .suspend=0x00000000, .resume=0x00000001, .target=1},
{.name="PMCU0_CPU_PSLVERR_MASKING", .addr=PQE_PM_O26_PMCU0_CPU_PSLVERR_MASKING, .suspend=0x00000011, .resume=0x00000010, .target=1},
{.name="PMCU0_CPU__LOCKUP_MODE_EN", .addr=PQE_PM_O26_PMCU0_CPU__LOCKUP_MODE_EN, .suspend=0x00000000, .resume=0x00000001, .target=1},
{.name="PMCU0_CPUH_LOCKUP_MODE_EN", .addr=PQE_PM_O26_PMCU0_CPUH_LOCKUP_MODE_EN, .suspend=0x00000000, .resume=0x00000001, .target=1},
{.name="PMCU1_CPU_PSLVERR_MASKING", .addr=PQE_PM_O26_PMCU1_CPU_PSLVERR_MASKING, .suspend=0x00000011, .resume=0x00000010, .target=1},
{.name="PMCU1_CPU__LOCKUP_MODE_EN", .addr=PQE_PM_O26_PMCU1_CPU__LOCKUP_MODE_EN, .suspend=0x00000000, .resume=0x00000001, .target=1},
{.name="PMCU2_CPU_PSLVERR_MASKING", .addr=PQE_PM_O26_PMCU2_CPU_PSLVERR_MASKING, .suspend=0x00000011, .resume=0x00000010, .target=1},
{.name="PMCU2_CPU__LOCKUP_MODE_EN", .addr=PQE_PM_O26_PMCU2_CPU__LOCKUP_MODE_EN, .suspend=0x00000000, .resume=0x00000001, .target=1},
{.name="PMCU3_CPU_PSLVERR_MASKING", .addr=PQE_PM_O26_PMCU3_CPU_PSLVERR_MASKING, .suspend=0x00000011, .resume=0x00000010, .target=1},
{.name="PMCU3_CPU__LOCKUP_MODE_EN", .addr=PQE_PM_O26_PMCU3_CPU__LOCKUP_MODE_EN, .suspend=0x00000000, .resume=0x00000001, .target=1},
{.name="VMCU_CPU__PSLVERR_MASKING", .addr=PQE_PM_O26_VMCU_CPU__PSLVERR_MASKING, .suspend=0x00000011, .resume=0x00000011, .target=0},//lxboot
{.name="VMCU_CPU___LOCKUP_MODE_EN", .addr=PQE_PM_O26_VMCU_CPU___LOCKUP_MODE_EN, .suspend=0x00000000, .resume=0x00000001, .target=0},
{.name="VMCU0_CPU_PSLVERR_MASKING", .addr=PQE_PM_O26_VMCU0_CPU_PSLVERR_MASKING, .suspend=0x00000011, .resume=0x00000010, .target=0},
{.name="VMCU0_CPU__LOCKUP_MODE_EN", .addr=PQE_PM_O26_VMCU0_CPU__LOCKUP_MODE_EN, .suspend=0x00000000, .resume=0x00000001, .target=0},
{.name="VMCU0_CPUH_LOCKUP_MODE_EN", .addr=PQE_PM_O26_VMCU0_CPUH_LOCKUP_MODE_EN, .suspend=0x00000000, .resume=0x00000001, .target=0},
{.name="VMCU1_CPU_PSLVERR_MASKING", .addr=PQE_PM_O26_VMCU1_CPU_PSLVERR_MASKING, .suspend=0x00000011, .resume=0x00000010, .target=0},
{.name="VMCU1_CPU__LOCKUP_MODE_EN", .addr=PQE_PM_O26_VMCU1_CPU__LOCKUP_MODE_EN, .suspend=0x00000000, .resume=0x00000001, .target=0},
{.name="CPU_PW_CTRL_POWER00      ", .addr=PQE_PM_O26_CPU_PW_CTRL_POWER00      , .suspend=0x00001111, .resume=0x00001101, .target=0},//lxboot
{.name="CPU_PW_CTRL_POWER01      ", .addr=PQE_PM_O26_CPU_PW_CTRL_POWER01      , .suspend=0x00ffffff, .resume=0x00000000, .target=0}};

/*========================================================================================
	Implementation Group
========================================================================================*/
void pqe_pm_init_o26_hw_ctx(void)
{
	pqe_pm_register_hw_handler(_pqe_pm_o26_hw_handler);
	pqe_pm_register_enable(&_g_pqe_pm_o26_enable);
	pqe_pm_register_hw_dbg_status(_pqe_pm_o26_hw_dbg_status);
}

static int _pqe_pm_o26_hw_handler(int cmd)
{
	#ifdef PQEPM_O26_USE_CTOP_REGS
	int ret;
	static union pqe_pm_cg cg_backup = {.udata32 = 0};
	union pqe_pm_cg cg = {.udata32 = 0};
	#endif

	if (cmd == PQE_PM_HW_FW_SUSPEND)
	{
		#ifdef INCLUDE_KDRV_DE
		vsc_suspend(1);/* fw_stop */
		#endif

		if (_g_pqe_pm_o26_enable == PQE_PM_O26_HW_DBG_PRINT)
		{
			_pqe_pm_o26_hw_dbg_read_regs("FW_");
		}

		pqe_pm_noti("PQE_PM_HW_FW_SUSPEND done\n");
	}
	else if (cmd == PQE_PM_HW_CG_ON)
	{
		usleep_range(20000, 20000); // 20ms, see http://clm.lge.com/issue/browse/SICDTV-13478

		#ifdef PQEPM_O26_USE_CTOP_REGS
		if (_g_pqe_pm_o26_cg > 0) {
			cg.udata32 = _g_pqe_pm_o26_cg;
		} else {
			cg.udata32 = 0xFFFFFF;
			cg.dnsr0_sr_cg_en = 1;
			cg.dnsr1_sr_cg_en = 1;
		}

		/* sr_cg_en */
		CTOP_CTRL_O26Ax_RdFL(SCRG_CTRL_DNSR0,crg_dnsr002);
		CTOP_CTRL_O26Ax_Rd01(SCRG_CTRL_DNSR0,crg_dnsr002,reg_dnsr_sr_clk_gate_en,cg_backup.dnsr0_sr_cg_en);
		CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_DNSR0,crg_dnsr002,reg_dnsr_sr_clk_gate_en,cg.dnsr0_sr_cg_en);
		CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_DNSR0,crg_dnsr002);
		CTOP_CTRL_O26Ax_RdFL(SCRG_CTRL_DNSR1,crg_dnsr002);
		CTOP_CTRL_O26Ax_Rd01(SCRG_CTRL_DNSR1,crg_dnsr002,reg_dnsr_sr_clk_gate_en,cg_backup.dnsr1_sr_cg_en);
		CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_DNSR1,crg_dnsr002,reg_dnsr_sr_clk_gate_en,cg.dnsr1_sr_cg_en);
		CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_DNSR1,crg_dnsr002);
		pqe_pm_noti("sr_cg_en on(%d,%d)(backup:%d,%d)\n",\
			cg.dnsr0_sr_cg_en,cg.dnsr1_sr_cg_en,cg_backup.dnsr0_sr_cg_en,cg_backup.dnsr1_sr_cg_en);

		/* http://jira.lge.com/issue/browse/SICDTV-15933 */
		if (_g_pqe_pm_o26_enable == PQE_PM_O26_HW_CG_CTRL_CTOP) {
			#if 1
			struct pqe_pm_regs_entry *p_table;
			UINT32 i, number = sizeof(_g_pqe_pm_o26_regs_table)/sizeof(_g_pqe_pm_o26_regs_table[0]);

			for (i=0; i<number; i++) {
				p_table = &_g_pqe_pm_o26_regs_table[i];
				if (p_table->target == 1) {
					ret = SYS_IO_ReadRegArray(p_table->addr,4,&p_table->backup);
					ret = SYS_IO_WriteRegArray(p_table->addr,4,&p_table->suspend);
				}
			}
			pqe_pm_noti("pslverr_masking on, lockup chk off (backup)\n");
			#else
			UINT32 pslverr_masking, lockup_mode_en;
			/* pslverr_masking on, lockup chk off */
			pslverr_masking = 0x11;
			lockup_mode_en  = 0x0;
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB0_CPU__PSLVERR_MASKING,4,&pslverr_masking);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB0_CPU___LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB0_CPUM__LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB1_CPU__PSLVERR_MASKING,4,&pslverr_masking);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB1_CPU___LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB2_CPU__PSLVERR_MASKING,4,&pslverr_masking);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB2_CPU___LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB2_BMC___LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB3_CPU__PSLVERR_MASKING,4,&pslverr_masking);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB3_CPU___LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB3_CPUH__LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB3_CPUM__LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB3_WOC___LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_PMCU_CPU__PSLVERR_MASKING,4,&pslverr_masking);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_PMCU_CPU___LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_PMCU0_CPU_PSLVERR_MASKING,4,&pslverr_masking);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_PMCU0_CPU__LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_PMCU0_CPUH_LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_PMCU1_CPU_PSLVERR_MASKING,4,&pslverr_masking);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_PMCU1_CPU__LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_PMCU2_CPU_PSLVERR_MASKING,4,&pslverr_masking);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_PMCU2_CPU__LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_PMCU3_CPU_PSLVERR_MASKING,4,&pslverr_masking);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_PMCU3_CPU__LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_VMCU_CPU__PSLVERR_MASKING,4,&pslverr_masking);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_VMCU_CPU___LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_VMCU0_CPU_PSLVERR_MASKING,4,&pslverr_masking);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_VMCU0_CPU__LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_VMCU0_CPUH_LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_VMCU1_CPU_PSLVERR_MASKING,4,&pslverr_masking);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_VMCU1_CPU__LOCKUP_MODE_EN,4,&lockup_mode_en);
			pqe_pm_noti("pslverr_masking on, lockup chk off\n");
			#endif
		}

		if (_g_pqe_pm_o26_enable == PQE_PM_O26_HW_CG_CTRL_CTOP) {
			/* apb mask on */
			CTOP_CTRL_O26Ax_RdFL(CPU_PW_CTRL, power_00);
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_00, apb_lockup_chk_en, 1);//4
			CTOP_CTRL_O26Ax_WrFL(CPU_PW_CTRL, power_00);
			pqe_pm_noti("apb_lockup_chk_en on\n");

			/* cg on */
			CTOP_CTRL_O26Ax_RdFL(CPU_PW_CTRL, power_01);
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_fme_sbw_clk_gate_en  , cg.reg_fme_sbw_clk_gate_en  );//0
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_srco_sbw_clk_gate_en , cg.reg_srco_sbw_clk_gate_en );//1
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_vsd_ipw_clk_gate_en  , cg.reg_vsd_ipw_clk_gate_en  );//2
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_vdo_ipw_clk_gate_en  , cg.reg_vdo_ipw_clk_gate_en  );//3
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_tcon_ipw_clk_gate_en , cg.reg_tcon_ipw_clk_gate_en );//4
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_sre_ipw_clk_gate_en  , cg.reg_sre_ipw_clk_gate_en  );//5
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_npp_ipw_clk_gate_en  , cg.reg_npp_ipw_clk_gate_en  );//6
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_nd1_ipw_clk_gate_en  , cg.reg_nd1_ipw_clk_gate_en  );//7
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_nd0_ipw_clk_gate_en  , cg.reg_nd0_ipw_clk_gate_en  );//8
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_me1_ipw_clk_gate_en  , cg.reg_me1_ipw_clk_gate_en  );//9
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_me0_ipw_clk_gate_en  , cg.reg_me0_ipw_clk_gate_en  );//10
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_lnx1_ipw_clk_gate_en , cg.reg_lnx1_ipw_clk_gate_en );//11
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_lnx0_ipw_clk_gate_en , cg.reg_lnx0_ipw_clk_gate_en );//12
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_led_ipw_clk_gate_en  , cg.reg_led_ipw_clk_gate_en  );//13
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_imx_ipw_clk_gate_en  , cg.reg_imx_ipw_clk_gate_en  );//14
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_hdr_ipw_clk_gate_en  , cg.reg_hdr_ipw_clk_gate_en  );//15
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_gsc_ipw_clk_gate_en  , cg.reg_gsc_ipw_clk_gate_en  );//16
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_fms_ipw_clk_gate_en  , cg.reg_fms_ipw_clk_gate_en  );//17
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_fmc_ipw_clk_gate_en  , cg.reg_fmc_ipw_clk_gate_en  );//18
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_dsc_ipw_clk_gate_en  , cg.reg_dsc_ipw_clk_gate_en  );//19
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_dnsr1_ipw_clk_gate_en, cg.reg_dnsr1_ipw_clk_gate_en);//20
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_dnsr0_ipw_clk_gate_en, cg.reg_dnsr0_ipw_clk_gate_en);//21
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_cvi_ipw_clk_gate_en  , cg.reg_cvi_ipw_clk_gate_en  );//22
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_cco_ipw_clk_gate_en  , cg.reg_cco_ipw_clk_gate_en  );//23
			// CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_pmcu_ipw_clk_gate_en , cg.reg_pmcu_ipw_clk_gate_en );//24
			CTOP_CTRL_O26Ax_WrFL(CPU_PW_CTRL, power_01);
			pqe_pm_noti("cg on\n");
		}

		pqe_pm_noti("PQE_PM_HW_CG_ON done (cg:0x%08x)(bak:0x%08x)(dbg:0x%08x)\n",cg.udata32,cg_backup.udata32,_g_pqe_pm_o26_cg);
		#endif
	}
	else if (cmd == PQE_PM_HW_CG_OFF)
	{
		//20231121, remove here (see http://clm.lge.com/issue/browse/SICDTV-13415)
		//#ifdef INCLUDE_KDRV_SYS
		// see http://clm.lge.com/issue/browse/AVTASK-683
		//pqe_pm_noti("force SYS to make up\n");
		//SYS_RequestForceRuntimeResume();
		//#endif

		#ifdef PQEPM_O26_USE_CTOP_REGS
		/* http://jira.lge.com/issue/browse/SICDTV-15933 */
		if (_g_pqe_pm_o26_enable == PQE_PM_O26_HW_CG_CTRL_CTOP) {
			/* cg off */
			CTOP_CTRL_O26Ax_RdFL(CPU_PW_CTRL, power_01);
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_fme_sbw_clk_gate_en  , 0);//0
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_srco_sbw_clk_gate_en , 0);//1
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_vsd_ipw_clk_gate_en  , 0);//2
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_vdo_ipw_clk_gate_en  , 0);//3
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_tcon_ipw_clk_gate_en , 0);//4
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_sre_ipw_clk_gate_en  , 0);//5
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_npp_ipw_clk_gate_en  , 0);//6
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_nd1_ipw_clk_gate_en  , 0);//7
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_nd0_ipw_clk_gate_en  , 0);//8
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_me1_ipw_clk_gate_en  , 0);//9
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_me0_ipw_clk_gate_en  , 0);//10
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_lnx1_ipw_clk_gate_en , 0);//11
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_lnx0_ipw_clk_gate_en , 0);//12
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_led_ipw_clk_gate_en  , 0);//13
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_imx_ipw_clk_gate_en  , 0);//14
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_hdr_ipw_clk_gate_en  , 0);//15
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_gsc_ipw_clk_gate_en  , 0);//16
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_fms_ipw_clk_gate_en  , 0);//17
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_fmc_ipw_clk_gate_en  , 0);//18
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_dsc_ipw_clk_gate_en  , 0);//19
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_dnsr1_ipw_clk_gate_en, 0);//20
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_dnsr0_ipw_clk_gate_en, 0);//21
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_cvi_ipw_clk_gate_en  , 0);//22
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_cco_ipw_clk_gate_en  , 0);//23
			// CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_01, reg_pmcu_ipw_clk_gate_en , 0);//24
			CTOP_CTRL_O26Ax_WrFL(CPU_PW_CTRL, power_01);
			pqe_pm_noti("cg off\n");

			/* apb_lockup_chk_en off */
			CTOP_CTRL_O26Ax_RdFL(CPU_PW_CTRL, power_00);
			CTOP_CTRL_O26Ax_Wr01(CPU_PW_CTRL, power_00, apb_lockup_chk_en, 0);//4
			CTOP_CTRL_O26Ax_WrFL(CPU_PW_CTRL, power_00);
			pqe_pm_noti("apb_lockup_chk_en off\n");
		}

		if (_g_pqe_pm_o26_enable == PQE_PM_O26_HW_CG_CTRL_CTOP) {
			#if 1
			struct pqe_pm_regs_entry *p_table;
			UINT32 i, number = sizeof(_g_pqe_pm_o26_regs_table)/sizeof(_g_pqe_pm_o26_regs_table[0]);

			for (i=0; i<number; i++) {
				p_table = &_g_pqe_pm_o26_regs_table[i];
				if (p_table->target == 1) {
					ret = SYS_IO_WriteRegArray(p_table->addr,4,&p_table->backup);
				}
			}
			pqe_pm_noti("pslverr_masking off, lockup chk on (restore)\n");
			#else
			UINT32 pslverr_masking, lockup_mode_en;
			/* pslverr_masking off, lockup chk on */
			pslverr_masking = 0x10;
			lockup_mode_en  = 0x1;
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB0_CPU__PSLVERR_MASKING,4,&pslverr_masking);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB0_CPU___LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB0_CPUM__LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB1_CPU__PSLVERR_MASKING,4,&pslverr_masking);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB1_CPU___LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB2_CPU__PSLVERR_MASKING,4,&pslverr_masking);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB2_CPU___LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB2_BMC___LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB3_CPU__PSLVERR_MASKING,4,&pslverr_masking);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB3_CPU___LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB3_CPUH__LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB3_CPUM__LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_APB3_WOC___LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_PMCU_CPU__PSLVERR_MASKING,4,&pslverr_masking);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_PMCU_CPU___LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_PMCU0_CPU_PSLVERR_MASKING,4,&pslverr_masking);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_PMCU0_CPU__LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_PMCU0_CPUH_LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_PMCU1_CPU_PSLVERR_MASKING,4,&pslverr_masking);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_PMCU1_CPU__LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_PMCU2_CPU_PSLVERR_MASKING,4,&pslverr_masking);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_PMCU2_CPU__LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_PMCU3_CPU_PSLVERR_MASKING,4,&pslverr_masking);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_PMCU3_CPU__LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_VMCU_CPU__PSLVERR_MASKING,4,&pslverr_masking);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_VMCU_CPU___LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_VMCU0_CPU_PSLVERR_MASKING,4,&pslverr_masking);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_VMCU0_CPU__LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_VMCU0_CPUH_LOCKUP_MODE_EN,4,&lockup_mode_en);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_VMCU1_CPU_PSLVERR_MASKING,4,&pslverr_masking);
			ret = SYS_IO_WriteRegArray(PQE_PM_O26_VMCU1_CPU__LOCKUP_MODE_EN,4,&lockup_mode_en);
			pqe_pm_noti("pslverr_masking off, lockup chk on\n");
			#endif
		}

		/* sr_cg_en */
		CTOP_CTRL_O26Ax_RdFL(SCRG_CTRL_DNSR0,crg_dnsr002);
		CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_DNSR0,crg_dnsr002,reg_dnsr_sr_clk_gate_en,cg_backup.dnsr0_sr_cg_en);
		CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_DNSR0,crg_dnsr002);
		CTOP_CTRL_O26Ax_RdFL(SCRG_CTRL_DNSR1,crg_dnsr002);
		CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_DNSR1,crg_dnsr002,reg_dnsr_sr_clk_gate_en,cg_backup.dnsr1_sr_cg_en);
		CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_DNSR1,crg_dnsr002);
		pqe_pm_noti("sr_cg_en off(restore:%d,%d)\n",cg_backup.dnsr0_sr_cg_en,cg_backup.dnsr1_sr_cg_en);

		pqe_pm_noti("PQE_PM_HW_CG_OFF done (bak:0x%08x)\n",cg_backup.udata32);
		#endif
	}
	else if (cmd == PQE_PM_HW_FW_RESUME)
	{
		#ifdef INCLUDE_KDRV_DE
		vsc_resume(1);/* fw_start */
		#endif

		usleep_range(20000, 20000); // 20ms, It takes some time for interrupt to be enabled(AVTASK-1378)

		if (_g_pqe_pm_o26_enable == PQE_PM_O26_HW_DBG_PRINT)
		{
			_pqe_pm_o26_hw_dbg_read_regs("FW_");
		}

		pqe_pm_noti("PQE_PM_HW_FW_RESUME done\n");
	}
	else
	{
		pqe_pm_error("unknown cmd 0x%x\n", cmd);
	}

	return RET_OK;
}

static void _pqe_pm_o26_hw_dbg_status(struct seq_file *m)
{
	int ret;
	UINT32 curr_data, i, entry_size, number;
	struct pqe_pm_regs_entry *p_table;

	entry_size = sizeof(_g_pqe_pm_o26_regs_table);
	number = entry_size/sizeof(_g_pqe_pm_o26_regs_table[0]);

	seq_printf(m, "pqepm_o26_en:%d pqepm_o26_cg:%d entry_size:%d\n",_g_pqe_pm_o26_enable,_g_pqe_pm_o26_cg,entry_size);
	seq_printf(m, "[i ] %-25s %-10s %-10s %-10s %-10s %-3s %-3s %-10s\n","name","addr","suspend","curr","resume","typ","tgt","backup");

	#ifdef PQEPM_O26_USE_CTOP_REGS
	for (i=0; i<number; i++) {
		p_table = &_g_pqe_pm_o26_regs_table[i];
		ret = SYS_IO_ReadRegArray(p_table->addr,4,&curr_data);
		seq_printf(m, "[%02d] %-25s 0x%08x 0x%08x 0x%08x 0x%08x %-3s %-3s 0x%08x\n",\
			i,p_table->name,p_table->addr,p_table->suspend,curr_data,p_table->resume,\
			(curr_data==p_table->resume)? "(R)":(curr_data==p_table->suspend)? "(S)":"(?)",\
			(p_table->target==1)? "(o)":"(x)",p_table->backup);
	}
	#endif
}

static void _pqe_pm_o26_hw_dbg_read_regs(char *prefix)
{
	int ret;
	UINT32 curr_data, i, number;
	UINT32 prefix_size = 0;
	struct pqe_pm_regs_entry *p_table;

	if (prefix)
	{
		prefix_size = strlen(prefix);
	}

	number = sizeof(_g_pqe_pm_o26_regs_table)/sizeof(_g_pqe_pm_o26_regs_table[0]);

	pqe_pm_noti("[i ] %-25s %-10s %-10s %-10s %-10s %-3s %-3s %-10s\n","name","addr","suspend","curr","resume","typ","tgt","backup");
	#ifdef PQEPM_O26_USE_CTOP_REGS
	for (i=0; i<number; i++) {
		p_table = &_g_pqe_pm_o26_regs_table[i];

		if (prefix_size > 0)
		{
			if (0 != strncmp(p_table->name,prefix,prefix_size))//no matching
			{
				continue;
			}
		}

		ret = SYS_IO_ReadRegArray(p_table->addr,4,&curr_data);
		pqe_pm_noti("[%02d] %-25s 0x%08x 0x%08x 0x%08x 0x%08x %-3s %-3s 0x%08x\n",\
			i,p_table->name,p_table->addr,p_table->suspend,curr_data,p_table->resume,\
			(curr_data==p_table->resume)? "(R)":(curr_data==p_table->suspend)? "(S)":"(?)",\
			(p_table->target==1)? "(o)":"(x)",p_table->backup);
	}
	#endif
}
