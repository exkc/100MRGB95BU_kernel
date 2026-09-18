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
#define PQEPM_O22_USE_CTOP_REGS
#endif

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "pqe_pm_impl.h"
#include "../sys/sys_io.h"

#ifdef PQEPM_O22_USE_CTOP_REGS
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
static int _pqe_pm_o22_hw_handler(int cmd);
static void _pqe_pm_o22_hw_dbg_status(struct seq_file *m);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static int _g_pqe_pm_o22_enable = 1;
module_param_named(pqepm_o22, _g_pqe_pm_o22_enable, int, 0644);

/* add DDR ALP(AVTASK-683) */
struct pqe_pm_regs_entry _g_pqe_pm_o22_regs_table[] = {
{"C4TX Pow",0xcc432010,0x0,0x00000ff0},
{"**",0xcc432014,0x0,0x10000011},
{"DISP PLL",0xCC432058,0x010C7001,0x010f6002},
{"**",0xCC43205C,0x00A10063,0x00a14050},
{"**",0xCC432060,0x08343032,0x08111042},
{"ME1",0xCC310010,0x81,0x100},
{"**",0xCC310014,0x81,0x100},
{"**",0xCC310018,0x81,0x100},
{"FMS",0xCC350014,0x81,0x100},
{"**",0xCC350018,0x81,0x100},
{"**",0xCC35001C,0x81,0x100},
{"**",0xCC350020,0x81,0x100},
{"DNSR",0xCC390014,0x81,0x100},
{"**",0xCC390018,0x81,0x100},
{"**",0xCC39001C,0x81,0x100},
{"**",0xCC390020,0x81,0x100},
{"DNNR",0xCC3B0014,0x81,0x100},
{"**",0xCC3B0018,0x81,0x100},
{"**",0xCC3B001C,0x81,0x100},
{"**",0xCC3B0020,0x81,0x100},
{"GSC",0xCC510010,0x81,0x100},
{"**",0xCC510014,0x81,0x100},
{"**",0xCC510018,0x81,0x100},
{"ND0",0xCC810010,0x81,0x100},
{"**",0xCC810014,0x81,0x100},
{"**",0xCC810018,0x81,0x100},
{"CVI",0xCC850014,0x81,0x100},
{"**",0xCC850018,0x81,0x100},
{"**",0xCC85001C,0x81,0x100},
{"DNE",0xCC890014,0x81,0x100},
{"**",0xCC890018,0x81,0x100},
{"**",0xCC89001C,0x81,0x100},
{"IMX",0xCC8D0014,0x81,0x100},
{"**",0xCC8D0018,0x81,0x100},
{"**",0xCC8D001C,0x81,0x100},
{"ME0",0xCC9D0010,0x81,0x100},
{"**",0xCC9D0014,0x81,0x100},
{"**",0xCC9D0018,0x81,0x100},
{"ND1",0xCCC10010,0x81,0x100},
{"**",0xCCC10014,0x81,0x100},
{"**",0xCCC10018,0x81,0x100},
{"SRE",0xCCC50010,0x81,0x100},
{"**",0xCCC50014,0x81,0x100},
{"**",0xCCC50018,0x81,0x100},
{"VDO",0xCCC90014,0x81,0x100},
{"**",0xCCC90018,0x81,0x100},
{"**",0xCCC9001C,0x81,0x100},
{"**",0xCCC90020,0x81,0x100},
{"**",0xCCC90024,0x81,0x100},
{"**",0xCCC90028,0x81,0x100},
{"**",0xCCC9002C,0x81,0x100},
{"**",0xCCC90030,0x81,0x100},
{"HDR",0xCCCD0014,0x81,0x100},
{"**",0xCCCD0018,0x81,0x100},
{"TCON",0xCC450008,0xE,0x0},
{"DDR",0xC67C8050,0x000023D0,0x00002c78},
{"**",0xF3008050,0x000023D0,0x00002c78},
{"**",0xC67C300C,0x0500F101,0x0502f100},
{"**",0xC67C300C,0x0500F101,0x0502f100},
{"**",0xC67C0100,0x00000003,0x00000000},
{"**",0xF3000100,0x00000003,0x00000000}};

/*========================================================================================
	Implementation Group
========================================================================================*/
void pqe_pm_init_o22_hw_ctx(void)
{
	pqe_pm_register_hw_handler(_pqe_pm_o22_hw_handler);
	pqe_pm_register_enable(&_g_pqe_pm_o22_enable);
	pqe_pm_register_hw_dbg_status(_pqe_pm_o22_hw_dbg_status);
}

static int _pqe_pm_o22_hw_handler(int cmd)
{
	if (cmd == PQE_PM_HW_FW_SUSPEND)
	{
		#ifdef INCLUDE_KDRV_DE
		vsc_suspend(1);/* fw_stop */
		#endif

		pqe_pm_noti("PQE_PM_HW_FW_SUSPEND done\n");
	}
	else if (cmd == PQE_PM_HW_CG_ON)
	{
		#ifdef PQEPM_O22_USE_CTOP_REGS
		/************************************************************************/
		/* guide from SICDTV-10053 */
		/************************************************************************/
		//IP	details			low power			normal
		//DISP PLL	AIOPLL_DISP 1/16 freq. down	wr 0xCC432058 0x010C7001	wr 0xCC432058 0x010f6002
		//**	AIOPLL_DISP 1/16 freq. down	wr 0xCC43205C 0x00A10063	wr 0xCC43205C 0x00a14050
		//**	AIOPLL_DISP 1/16 freq. down	wr 0xCC432060 0x08343032	wr 0xCC432060 0x08111042
		//ME1	1/64 Freq. down	wr 0xCC310010 0x81	wr 0xCC310010 0x100
		//**	1/64 Freq. down	wr 0xCC310014 0x81	wr 0xCC310014 0x100
		//**	1/64 Freq. down	wr 0xCC310018 0x81	wr 0xCC310018 0x100
		//FMS	1/64 Freq. down	wr 0xCC350014 0x81	wr 0xCC350014 0x100
		//**	1/64 Freq. down	wr 0xCC350018 0x81	wr 0xCC350018 0x100
		//**	1/64 Freq. down	wr 0xCC35001C 0x81	wr 0xCC35001C 0x100
		//**	1/64 Freq. down	wr 0xCC350020 0x81	wr 0xCC350020 0x100
		//DNSR	1/64 Freq. down	wr 0xCC390014 0x81	wr 0xCC390014 0x100
		//**	1/64 Freq. down	wr 0xCC390018 0x81	wr 0xCC390018 0x100
		//**	1/64 Freq. down	wr 0xCC39001C 0x81	wr 0xCC39001C 0x100
		//**	1/64 Freq. down	wr 0xCC390020 0x81	wr 0xCC390020 0x100
		//DNNR	1/64 Freq. down	wr 0xCC3B0014 0x81	wr 0xCC3B0014 0x100
		//**	1/64 Freq. down	wr 0xCC3B0018 0x81	wr 0xCC3B0018 0x100
		//**	1/64 Freq. down	wr 0xCC3B001C 0x81	wr 0xCC3B001C 0x100
		//**	1/64 Freq. down	wr 0xCC3B0020 0x81	wr 0xCC3B0020 0x100
		//GSC	1/64 Freq. down	wr 0xCC510010 0x81	wr 0xCC510010 0x100
		//**	1/64 Freq. down	wr 0xCC510014 0x81	wr 0xCC510014 0x100
		//**	1/64 Freq. down	wr 0xCC510018 0x81	wr 0xCC510018 0x100
		//ND0	1/64 Freq. down	wr 0xCC810010 0x81	wr 0xCC810010 0x100
		//**	1/64 Freq. down	wr 0xCC810014 0x81	wr 0xCC810014 0x100
		//**	1/64 Freq. down	wr 0xCC810018 0x81	wr 0xCC810018 0x100
		//CVI	1/64 Freq. down	wr 0xCC850014 0x81	wr 0xCC850014 0x100
		//**	1/64 Freq. down	wr 0xCC850018 0x81	wr 0xCC850018 0x100
		//**	1/64 Freq. down	wr 0xCC85001C 0x81	wr 0xCC85001C 0x100
		//DNE	1/64 Freq. down	wr 0xCC890014 0x81	wr 0xCC890014 0x100
		//**	1/64 Freq. down	wr 0xCC890018 0x81	wr 0xCC890018 0x100
		//**	1/64 Freq. down	wr 0xCC89001C 0x81	wr 0xCC89001C 0x100
		//IMX	1/64 Freq. down	wr 0xCC8D0014 0x81	wr 0xCC8D0014 0x100
		//**	1/64 Freq. down	wr 0xCC8D0018 0x81	wr 0xCC8D0018 0x100
		//**	1/64 Freq. down	wr 0xCC8D001C 0x81	wr 0xCC8D001C 0x100
		//ME0	1/64 Freq. down	wr 0xCC9D0010 0x81	wr 0xCC9D0010 0x100
		//**	1/64 Freq. down	wr 0xCC9D0014 0x81	wr 0xCC9D0014 0x100
		//**	1/64 Freq. down	wr 0xCC9D0018 0x81	wr 0xCC9D0018 0x100
		//ND1	1/64 Freq. down	wr 0xCCC10010 0x81	wr 0xCCC10010 0x100
		//**	1/64 Freq. down	wr 0xCCC10014 0x81	wr 0xCCC10014 0x100
		//**	1/64 Freq. down	wr 0xCCC10018 0x81	wr 0xCCC10018 0x100
		//SRE	1/64 Freq. down	wr 0xCCC50010 0x81	wr 0xCCC50010 0x100
		//**	1/64 Freq. down	wr 0xCCC50014 0x81	wr 0xCCC50014 0x100
		//**	1/64 Freq. down	wr 0xCCC50018 0x81	wr 0xCCC50018 0x100
		//VDO	1/64 Freq. down	wr 0xCCC90014 0x81	wr 0xCCC90014 0x100
		//**	1/64 Freq. down	wr 0xCCC90018 0x81	wr 0xCCC90018 0x100
		//**	1/64 Freq. down	wr 0xCCC9001C 0x81	wr 0xCCC9001C 0x100
		//**	1/64 Freq. down	wr 0xCCC90020 0x81	wr 0xCCC90020 0x100
		//**	1/64 Freq. down	wr 0xCCC90024 0x81	wr 0xCCC90024 0x100
		//**	1/64 Freq. down	wr 0xCCC90028 0x81	wr 0xCCC90028 0x100
		//**	1/64 Freq. down	wr 0xCCC9002C 0x81	wr 0xCCC9002C 0x100
		//**	1/64 Freq. down	wr 0xCCC90030 0x81	wr 0xCCC90030 0x100
		//HDR	1/64 Freq. down	wr 0xCCCD0014 0x81	wr 0xCCCD0014 0x100
		//**	1/64 Freq. down	wr 0xCCCD0018 0x81	wr 0xCCCD0018 0x100
		//TCON	Clock Gating	wr 0xCC450008 0xE	wr 0xCC450008 0x0

		//DISP PLL - set by OVI_HW_O22_SetPmMode
		//CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE,disp_aiopll_r00,0x010C7001);
		//CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE,disp_aiopll_r00);
		//CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE,disp_aiopll_r01,0x00A10063);
		//CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE,disp_aiopll_r01);
		//CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE,disp_aiopll_r02,0x08343032);
		//CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE,disp_aiopll_r02);
		//ME1
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ME1,crg_me104);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ME1,crg_me104,reg_apb_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ME1,crg_me104);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ME1,crg_me105);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ME1,crg_me105,reg_axi_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ME1,crg_me105);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ME1,crg_me106);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ME1,crg_me106,reg_de_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ME1,crg_me106);
		//msleep(500);pqe_pm_noti("done\n");
		//FMS
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_FMS,crg_fms05);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_FMS,crg_fms05,reg_apb_fms_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_FMS,crg_fms05);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_FMS,crg_fms06);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_FMS,crg_fms06,reg_axi_fms_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_FMS,crg_fms06);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_FMS,crg_fms07);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_FMS,crg_fms07,reg_de_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_FMS,crg_fms07);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_FMS,crg_fms08);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_FMS,crg_fms08,reg_fms_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_FMS,crg_fms08);
		//msleep(500);pqe_pm_noti("done\n");
		//DNSR
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_DNSR,crg_dnsr05);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_DNSR,crg_dnsr05,reg_apb_sr_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_DNSR,crg_dnsr05);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_DNSR,crg_dnsr06);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_DNSR,crg_dnsr06,reg_axi_sr_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_DNSR,crg_dnsr06);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_DNSR,crg_dnsr07);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_DNSR,crg_dnsr07,reg_mem_sr_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_DNSR,crg_dnsr07);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_DNSR,crg_dnsr08);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_DNSR,crg_dnsr08,reg_sr_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_DNSR,crg_dnsr08);
		//msleep(500);pqe_pm_noti("done\n");
		//DNNR
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_DNNR,crg_dnnr05);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_DNNR,crg_dnnr05,reg_apb_nr_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_DNNR,crg_dnnr05);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_DNNR,crg_dnnr06);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_DNNR,crg_dnnr06,reg_axi_nr_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_DNNR,crg_dnnr06);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_DNNR,crg_dnnr07);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_DNNR,crg_dnnr07,reg_mem_nr_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_DNNR,crg_dnnr07);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_DNNR,crg_dnnr08);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_DNNR,crg_dnnr08,reg_nr_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_DNNR,crg_dnnr08);
		//msleep(500);pqe_pm_noti("done\n");
		//GSC
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_GSC,crg_gsc04);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_GSC,crg_gsc04,reg_apb_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_GSC,crg_gsc04);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_GSC,crg_gsc05);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_GSC,crg_gsc05,reg_axi_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_GSC,crg_gsc05);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_GSC,crg_gsc06);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_GSC,crg_gsc06,reg_de_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_GSC,crg_gsc06);
		//msleep(500);pqe_pm_noti("done\n");
		//ND0
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ND0,crg_nd004);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ND0,crg_nd004,reg_apb_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ND0,crg_nd004);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ND0,crg_nd005);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ND0,crg_nd005,reg_axi_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ND0,crg_nd005);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ND0,crg_nd006);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ND0,crg_nd006,reg_de_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ND0,crg_nd006);
		//msleep(500);pqe_pm_noti("done\n");
		//CVI
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_CVI,crg_cvi05);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_CVI,crg_cvi05,reg_apb_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_CVI,crg_cvi05);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_CVI,crg_cvi06);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_CVI,crg_cvi06,reg_axi_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_CVI,crg_cvi06);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_CVI,crg_cvi07);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_CVI,crg_cvi07,reg_de_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_CVI,crg_cvi07);
		//msleep(500);pqe_pm_noti("done\n");
		//DNE
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_DNE,crg_dne05);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_DNE,crg_dne05,reg_apb_dne_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_DNE,crg_dne05);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_DNE,crg_dne06);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_DNE,crg_dne06,reg_axi_dne_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_DNE,crg_dne06);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_DNE,crg_dne07);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_DNE,crg_dne07,reg_dne_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_DNE,crg_dne07);
		//msleep(500);pqe_pm_noti("done\n");
		//IMX
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_IMX,crg_imx05);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_IMX,crg_imx05,reg_apb_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_IMX,crg_imx05);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_IMX,crg_imx06);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_IMX,crg_imx06,reg_axi_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_IMX,crg_imx06);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_IMX,crg_imx07);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_IMX,crg_imx07,reg_de_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_IMX,crg_imx07);
		//msleep(500);pqe_pm_noti("done\n");
		//ME0
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ME0,crg_me004);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ME0,crg_me004,reg_apb_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ME0,crg_me004);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ME0,crg_me005);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ME0,crg_me005,reg_axi_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ME0,crg_me005);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ME0,crg_me006);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ME0,crg_me006,reg_de_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ME0,crg_me006);
		//msleep(500);pqe_pm_noti("done\n");
		//ND1
		#if 0	//excluded from freq down(AVTASK-571)
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ND1,crg_nd104);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ND1,crg_nd104,reg_apb_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ND1,crg_nd104);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ND1,crg_nd105);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ND1,crg_nd105,reg_axi_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ND1,crg_nd105);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ND1,crg_nd106);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ND1,crg_nd106,reg_de_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ND1,crg_nd106);
		#endif
		//msleep(500);pqe_pm_noti("done\n");
		//SRE
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_SRE,crg_sre04);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_SRE,crg_sre04,reg_apb_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_SRE,crg_sre04);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_SRE,crg_sre05);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_SRE,crg_sre05,reg_axi_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_SRE,crg_sre05);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_SRE,crg_sre06);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_SRE,crg_sre06,reg_de_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_SRE,crg_sre06);
		//msleep(500);pqe_pm_noti("done\n");
		//VDO
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_VDO,crg_vdo05);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_VDO,crg_vdo05,reg_apb_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_VDO,crg_vdo05);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_VDO,crg_vdo06);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_VDO,crg_vdo06,reg_axi_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_VDO,crg_vdo06);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_VDO,crg_vdo07);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_VDO,crg_vdo07,reg_bodp0_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_VDO,crg_vdo07);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_VDO,crg_vdo08);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_VDO,crg_vdo08,reg_bodp1_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_VDO,crg_vdo08);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_VDO,crg_vdo09);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_VDO,crg_vdo09,reg_de_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_VDO,crg_vdo09);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_VDO,crg_vdo10);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_VDO,crg_vdo10,reg_vdo0_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_VDO,crg_vdo10);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_VDO,crg_vdo11);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_VDO,crg_vdo11,reg_vdo1_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_VDO,crg_vdo11);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_VDO,crg_vdo12);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_VDO,crg_vdo12,reg_vdo2_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_VDO,crg_vdo12);
		//msleep(500);pqe_pm_noti("done\n");
		//HDR
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_HDR,crg_hdr05);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_HDR,crg_hdr05,reg_apb_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_HDR,crg_hdr05);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_HDR,crg_hdr06);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_HDR,crg_hdr06,reg_de_clk_skip_ctrl,0x81);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_HDR,crg_hdr06);
		//msleep(500);pqe_pm_noti("done\n");
		//TCON
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_TCON,crg_tcon02);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_TCON,crg_tcon02,reg_pix_clk_gate_en,1);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_TCON,crg_tcon02,reg_pix2_clk_gate_en,1);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_TCON,crg_tcon02,reg_op_clk_gate_en,1);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_TCON,crg_tcon02);
		#if 0	//setting guide required
		/************************************************************************/
		/* AVTASK-570, sync gen disable */
		/************************************************************************/
		CTOP_CTRL_O22Ax_RdFL(VSD_IPW_TOP,ipw_vsd_002);
		CTOP_CTRL_O22Ax_Wr01(VSD_IPW_TOP,ipw_vsd_002,sync_gen_disable,1);
		CTOP_CTRL_O22Ax_WrFL(VSD_IPW_TOP,ipw_vsd_002);
		/************************************************************************/

		/************************************************************************/
		/* AVTASK-570, cg on de,disp */
		/************************************************************************/
		//wr 0x CC490008 0x14
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_CCO,crg_cco02);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_CCO,crg_cco02,reg_de_clk_gate_en,1);//[2]reg_de_clk_gate_en
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_CCO,crg_cco02,reg_disp_clk_gate_en,1);//[4]reg_de_clk_gate_en
		//CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_CCO,crg_cco02,reg_disp_osd_clk_gate_en,1);//??? [6](confirm OSD off)
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_CCO,crg_cco02);

		//wr 0x CC4D0008 0x4
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_FMC,crg_fmc02);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_FMC,crg_fmc02,reg_de_clk_gate_en,1);//[2]reg_de_clk_gate_en
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_FMC,crg_fmc02);

		//wr 0x CC510008 0x4
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_GSC,crg_gsc02);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_GSC,crg_gsc02,reg_de_clk_gate_en,1);//[2]reg_de_clk_gate_en
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_GSC,crg_gsc02);

		//wr 0x CC810008 0x4
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ND0,crg_nd002);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ND0,crg_nd002,reg_de_clk_gate_en,1);//[2]reg_de_clk_gate_en
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ND0,crg_nd002);

		//wr 0x CCC10008 0x4 -> can not use ipc
		//CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ND1,crg_nd102);
		//CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ND1,crg_nd102,reg_de_clk_gate_en,1);//[2]reg_de_clk_gate_en
		//CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ND1,crg_nd102);

		/* setting guide required : SCRG_CTRL_DNSR,SCRG_CTRL_DNNR,SCRG_CTRL_LNE */
		//TODO
		/************************************************************************/
		#endif
		#endif

		pqe_pm_noti("PQE_PM_HW_CG_ON done\n");
	}
	else if (cmd == PQE_PM_HW_CG_OFF)
	{

		#ifdef INCLUDE_KDRV_SYS
		// see http://clm.lge.com/issue/browse/AVTASK-683
		pqe_pm_noti("force SYS to make up\n");
		SYS_RequestForceRuntimeResume();
		#endif

		#ifdef PQEPM_O22_USE_CTOP_REGS
		#if 0	//setting guide required
		/************************************************************************/
		/* AVTASK-570, cg off de,disp */
		/************************************************************************/
		//wr 0xCC490008 0x0
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_CCO,crg_cco02);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_CCO,crg_cco02,reg_de_clk_gate_en,0);//[2]reg_de_clk_gate_en
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_CCO,crg_cco02,reg_disp_clk_gate_en,0);//[4]reg_de_clk_gate_en
		//CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_CCO,crg_cco02,reg_disp_osd_clk_gate_en,0);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_CCO,crg_cco02);

		//wr 0xCC4D0008 0x0
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_FMC,crg_fmc02);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_FMC,crg_fmc02,reg_de_clk_gate_en,0);//[2]reg_de_clk_gate_en
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_FMC,crg_fmc02);

		//wr 0xCC510008 0x0
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_GSC,crg_gsc02);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_GSC,crg_gsc02,reg_de_clk_gate_en,0);//[2]reg_de_clk_gate_en
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_GSC,crg_gsc02);

		//wr 0xCC810008 0x0
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ND0,crg_nd002);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ND0,crg_nd002,reg_de_clk_gate_en,0);//[2]reg_de_clk_gate_en
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ND0,crg_nd002);

		//wr 0xCCC10008 0x0
		//CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ND1,crg_nd102);
		//CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ND1,crg_nd102,reg_de_clk_gate_en,0);//[2]reg_de_clk_gate_en
		//CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ND1,crg_nd102);

		/* setting guide required : SCRG_CTRL_DNSR,SCRG_CTRL_DNNR,SCRG_CTRL_LNE */
		//TODO
		/************************************************************************/

		/************************************************************************/
		/* AVTASK-570, sync gen enable */
		/************************************************************************/
		CTOP_CTRL_O22Ax_RdFL(VSD_IPW_TOP,ipw_vsd_002);
		CTOP_CTRL_O22Ax_Wr01(VSD_IPW_TOP,ipw_vsd_002,sync_gen_disable,0);
		CTOP_CTRL_O22Ax_WrFL(VSD_IPW_TOP,ipw_vsd_002);
		/************************************************************************/
		#endif
		/************************************************************************/
		/* guide from SICDTV-10053 */
		/************************************************************************/

		//DISP PLL - set by OVI_HW_O22_SetPmMode
		//CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE,disp_aiopll_r00,0x010f6002);
		//CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE,disp_aiopll_r00);
		//CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE,disp_aiopll_r01,0x00a14050);
		//CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE,disp_aiopll_r01);
		//CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE,disp_aiopll_r02,0x08111042);
		//CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE,disp_aiopll_r02);
		//ME1
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ME1,crg_me104);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ME1,crg_me104,reg_apb_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ME1,crg_me104);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ME1,crg_me105);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ME1,crg_me105,reg_axi_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ME1,crg_me105);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ME1,crg_me106);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ME1,crg_me106,reg_de_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ME1,crg_me106);
		//msleep(500);pqe_pm_noti("done\n");
		//FMS
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_FMS,crg_fms05);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_FMS,crg_fms05,reg_apb_fms_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_FMS,crg_fms05);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_FMS,crg_fms06);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_FMS,crg_fms06,reg_axi_fms_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_FMS,crg_fms06);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_FMS,crg_fms07);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_FMS,crg_fms07,reg_de_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_FMS,crg_fms07);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_FMS,crg_fms08);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_FMS,crg_fms08,reg_fms_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_FMS,crg_fms08);
		//msleep(500);pqe_pm_noti("done\n");
		//DNSR
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_DNSR,crg_dnsr05);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_DNSR,crg_dnsr05,reg_apb_sr_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_DNSR,crg_dnsr05);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_DNSR,crg_dnsr06);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_DNSR,crg_dnsr06,reg_axi_sr_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_DNSR,crg_dnsr06);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_DNSR,crg_dnsr07);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_DNSR,crg_dnsr07,reg_mem_sr_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_DNSR,crg_dnsr07);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_DNSR,crg_dnsr08);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_DNSR,crg_dnsr08,reg_sr_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_DNSR,crg_dnsr08);
		//msleep(500);pqe_pm_noti("done\n");
		//DNNR
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_DNNR,crg_dnnr05);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_DNNR,crg_dnnr05,reg_apb_nr_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_DNNR,crg_dnnr05);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_DNNR,crg_dnnr06);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_DNNR,crg_dnnr06,reg_axi_nr_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_DNNR,crg_dnnr06);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_DNNR,crg_dnnr07);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_DNNR,crg_dnnr07,reg_mem_nr_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_DNNR,crg_dnnr07);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_DNNR,crg_dnnr08);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_DNNR,crg_dnnr08,reg_nr_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_DNNR,crg_dnnr08);
		//msleep(500);pqe_pm_noti("done\n");
		//GSC
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_GSC,crg_gsc04);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_GSC,crg_gsc04,reg_apb_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_GSC,crg_gsc04);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_GSC,crg_gsc05);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_GSC,crg_gsc05,reg_axi_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_GSC,crg_gsc05);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_GSC,crg_gsc06);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_GSC,crg_gsc06,reg_de_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_GSC,crg_gsc06);
		//msleep(500);pqe_pm_noti("done\n");
		//ND0
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ND0,crg_nd004);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ND0,crg_nd004,reg_apb_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ND0,crg_nd004);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ND0,crg_nd005);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ND0,crg_nd005,reg_axi_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ND0,crg_nd005);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ND0,crg_nd006);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ND0,crg_nd006,reg_de_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ND0,crg_nd006);
		//msleep(500);pqe_pm_noti("done\n");
		//CVI
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_CVI,crg_cvi05);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_CVI,crg_cvi05,reg_apb_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_CVI,crg_cvi05);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_CVI,crg_cvi06);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_CVI,crg_cvi06,reg_axi_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_CVI,crg_cvi06);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_CVI,crg_cvi07);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_CVI,crg_cvi07,reg_de_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_CVI,crg_cvi07);
		//msleep(500);pqe_pm_noti("done\n");
		//DNE
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_DNE,crg_dne05);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_DNE,crg_dne05,reg_apb_dne_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_DNE,crg_dne05);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_DNE,crg_dne06);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_DNE,crg_dne06,reg_axi_dne_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_DNE,crg_dne06);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_DNE,crg_dne07);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_DNE,crg_dne07,reg_dne_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_DNE,crg_dne07);
		//msleep(500);pqe_pm_noti("done\n");
		//IMX
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_IMX,crg_imx05);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_IMX,crg_imx05,reg_apb_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_IMX,crg_imx05);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_IMX,crg_imx06);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_IMX,crg_imx06,reg_axi_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_IMX,crg_imx06);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_IMX,crg_imx07);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_IMX,crg_imx07,reg_de_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_IMX,crg_imx07);
		//msleep(500);pqe_pm_noti("done\n");
		//ME0
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ME0,crg_me004);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ME0,crg_me004,reg_apb_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ME0,crg_me004);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ME0,crg_me005);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ME0,crg_me005,reg_axi_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ME0,crg_me005);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ME0,crg_me006);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ME0,crg_me006,reg_de_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ME0,crg_me006);
		//msleep(500);pqe_pm_noti("done\n");
		//ND1
		#if 0	//excluded from freq down(AVTASK-571)
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ND1,crg_nd104);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ND1,crg_nd104,reg_apb_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ND1,crg_nd104);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ND1,crg_nd105);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ND1,crg_nd105,reg_axi_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ND1,crg_nd105);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_ND1,crg_nd106);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_ND1,crg_nd106,reg_de_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_ND1,crg_nd106);
		#endif
		//msleep(500);pqe_pm_noti("done\n");
		//SRE
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_SRE,crg_sre04);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_SRE,crg_sre04,reg_apb_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_SRE,crg_sre04);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_SRE,crg_sre05);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_SRE,crg_sre05,reg_axi_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_SRE,crg_sre05);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_SRE,crg_sre06);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_SRE,crg_sre06,reg_de_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_SRE,crg_sre06);
		//msleep(500);pqe_pm_noti("done\n");
		//VDO
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_VDO,crg_vdo05);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_VDO,crg_vdo05,reg_apb_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_VDO,crg_vdo05);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_VDO,crg_vdo06);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_VDO,crg_vdo06,reg_axi_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_VDO,crg_vdo06);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_VDO,crg_vdo07);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_VDO,crg_vdo07,reg_bodp0_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_VDO,crg_vdo07);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_VDO,crg_vdo08);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_VDO,crg_vdo08,reg_bodp1_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_VDO,crg_vdo08);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_VDO,crg_vdo09);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_VDO,crg_vdo09,reg_de_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_VDO,crg_vdo09);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_VDO,crg_vdo10);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_VDO,crg_vdo10,reg_vdo0_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_VDO,crg_vdo10);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_VDO,crg_vdo11);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_VDO,crg_vdo11,reg_vdo1_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_VDO,crg_vdo11);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_VDO,crg_vdo12);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_VDO,crg_vdo12,reg_vdo2_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_VDO,crg_vdo12);
		//msleep(500);pqe_pm_noti("done\n");
		//HDR
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_HDR,crg_hdr05);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_HDR,crg_hdr05,reg_apb_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_HDR,crg_hdr05);
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_HDR,crg_hdr06);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_HDR,crg_hdr06,reg_de_clk_skip_ctrl,0x100);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_HDR,crg_hdr06);
		//msleep(500);pqe_pm_noti("done\n");
		//TCON
		CTOP_CTRL_O22Ax_RdFL(SCRG_CTRL_TCON,crg_tcon02);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_TCON,crg_tcon02,reg_pix_clk_gate_en,0);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_TCON,crg_tcon02,reg_pix2_clk_gate_en,0);
		CTOP_CTRL_O22Ax_Wr01(SCRG_CTRL_TCON,crg_tcon02,reg_op_clk_gate_en,0);
		CTOP_CTRL_O22Ax_WrFL(SCRG_CTRL_TCON,crg_tcon02);
		#endif

		pqe_pm_noti("PQE_PM_HW_CG_OFF done\n");
	}
	else if (cmd == PQE_PM_HW_FW_RESUME)
	{
		#ifdef INCLUDE_KDRV_DE
		vsc_resume(1);/* fw_start */
		#endif

		pqe_pm_noti("PQE_PM_HW_FW_RESUME done\n");
	}
	else
	{
		pqe_pm_error("unknown cmd 0x%x\n", cmd);
	}

	return RET_OK;
}

static void _pqe_pm_o22_hw_dbg_status(struct seq_file *m)
{
	int ret;
	UINT32 curr_data, i, number;
	struct pqe_pm_regs_entry *p_table;

	number = sizeof(_g_pqe_pm_o22_regs_table)/sizeof(_g_pqe_pm_o22_regs_table[0]);

	seq_printf(m, "[i ] %-10s %-10s %-10s %-10s %-10s\n","name","address","suspend","curr","resume");

	for (i=0; i<number; i++) {
		p_table = &_g_pqe_pm_o22_regs_table[i];
		ret = SYS_IO_ReadRegArray(p_table->address,4,&curr_data);
		seq_printf(m, "[%02d] %-10s 0x%08x 0x%08x 0x%08x 0x%08x\n",\
			i,p_table->name,p_table->address,p_table->data_suspend,curr_data,p_table->data_resume);
	}
}

