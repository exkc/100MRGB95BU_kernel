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

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <asm/io.h>
#include "pqe_pm_impl.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PQE_PM_REG_WR(_addr,_data)   \
	do{\
		volatile UINT32 *__p_mapped=(volatile UINT32 *)ioremap(_addr, sizeof(UINT32));\
		if(__p_mapped == NULL) break;\
		*__p_mapped = _data;\
		iounmap((void *)__p_mapped);\
	}while(0)

#define PQE_PM_REG_RD(_addr,_data)   \
	do{\
		volatile UINT32 *__p_mapped = (volatile UINT32 *)ioremap(_addr, sizeof(UINT32));\
		if(__p_mapped == NULL) {_data = 0; break;}\
		_data = *__p_mapped;\
		iounmap((void *)__p_mapped);\
	}while(0)

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
#ifdef INCLUDE_KDRV_DE
extern int vsc_suspend(int type);
extern int vsc_resume(int type);
#endif

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int _pqe_pm_o20_hw_handler(int cmd);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static int _g_pqe_pm_o20_enable = 0;
module_param_named(pqepm_o20, _g_pqe_pm_o20_enable, int, 0644);

/*========================================================================================
	Implementation Group
========================================================================================*/
void pqe_pm_init_o20_hw_ctx(void)
{
	pqe_pm_register_hw_handler(_pqe_pm_o20_hw_handler);
	pqe_pm_register_enable(&_g_pqe_pm_o20_enable);
}

static int _pqe_pm_o20_hw_handler(int cmd)
{
	// FW suspend, stall 에 준하는 동작을 한니다.
	if (cmd == PQE_PM_HW_FW_SUSPEND)
	{
		#if 0	//see BE_TOP_HW_O20_SetPmMode
		/* AVTASK-571, clear picinit */
		//PQE_PM_REG_WR(0xC9014000,0x0);//IMX_CTRL - PIC_INIT
		//PQE_PM_REG_WR(0xC9014100,0x0);//IMX_CTRL1 - PIC_INIT
		//PQE_PM_REG_WR(0xC9003000,0x0);//HDR_CTRL - PIC_INIT
		PQE_PM_REG_WR(0xC9037000,0x0);//FMC_CTRL - PIC_INIT
		PQE_PM_REG_WR(0xC9007000,0x0);//GSC_CTRL - PIC_INIT
		PQE_PM_REG_WR(0xC900B000,0x0);//VSD_CTRL - PIC_INIT
		PQE_PM_REG_WR(0xC9010000,0x0);//CCO_CTRL - PIC_INIT
		PQE_PM_REG_WR(0xC9023D00,0x0);//LED_CTRL - PIC_INIT
		#endif
		#ifdef INCLUDE_KDRV_DE
		vsc_suspend(1);/* fw_stop */
		#endif

		pqe_pm_noti("PQE_PM_HW_FW_SUSPEND done\n");
	}
	// PQ 전체 CG ON 을 합니다.
	else if (cmd == PQE_PM_HW_CG_ON)
	{
		/* AVTASK-570, sync gen disable */
		PQE_PM_REG_WR(0xC930D028,0x10);//CTOP_SYN - gsc - BND_CTRL01 - [4]reg_sync_gen_disable

		/* AVTASK-570, cg on de,disp */
		/* CTOP_SYN - cco - CRG_CCO00 - [8]reg_cco__disp_clk_gate_en,[7]reg_cco__de_clk_gate_en */
		PQE_PM_REG_WR(0xC930C000,0x00000180);//[4]reg_cco__disp_osd_clk_gate_en ??? (confirm OSD off)
		/* CTOP_SYN - fmc - CRG_FMC00 - [4]reg_fmc__de_clk_gate_en */
		PQE_PM_REG_WR(0xC9304000,0x00000010);
		/* CTOP_SYN - gsc - CRG_GSC00 - [3]reg_gsc__de_clk_gate_en */
		PQE_PM_REG_WR(0xC930D000,0x00000008);
		/* CTOP_SYN - lgsr - CRG_LGSR00 - [14]reg_lgsr__de_soc_clk_gate_en */
		PQE_PM_REG_WR(0xC9302000,0x00004000);//lne,wov conflict ???
		/* CTOP_SYN - nd0 - CRG_ND000 - [2]reg_nd0__de_clk_gate_en */
		PQE_PM_REG_WR(0xC9307000,0x00000004);
		/* CTOP_SYN - nd1 - CRG_ND100 - [2]reg_nd1__de_clk_gate_en */
		PQE_PM_REG_WR(0xC9308000,0x00000004);

		pqe_pm_noti("PQE_PM_HW_CG_ON done\n");
	}
	// PQ 전체에 대한 CG OFF 를 합니다.
	else if (cmd == PQE_PM_HW_CG_OFF)
	{
		/* AVTASK-570, cg off de,disp */
		/* CTOP_SYN - cco - CRG_CCO00 */
		PQE_PM_REG_WR(0xC930C000,0x0);
		/* CTOP_SYN - fmc - CRG_FMC00 */
		PQE_PM_REG_WR(0xC9304000,0x0);
		/* CTOP_SYN - gsc - CRG_GSC00 */
		PQE_PM_REG_WR(0xC930D000,0x0);
		/* CTOP_SYN - lgsr - CRG_LGSR00 */
		PQE_PM_REG_WR(0xC9302000,0x0);
		/* CTOP_SYN - nd0 - CRG_ND000 */
		PQE_PM_REG_WR(0xC9307000,0x0);
		/* CTOP_SYN - nd1 - CRG_ND100 */
		PQE_PM_REG_WR(0xC9308000,0x0);

		/* AVTASK-570, sync gen enable */
		PQE_PM_REG_WR(0xC930D028,0x0);//CTOP_SYN - gsc - BND_CTRL01 - [4] reg_sync_gen_disable

		pqe_pm_noti("PQE_PM_HW_CG_OFF done\n");
	}
	// FW 를 restart 합니다.
	else if (cmd == PQE_PM_HW_FW_RESUME)
	{
		#ifdef INCLUDE_KDRV_DE
		vsc_resume(1);/* fw_start */
		#endif

		#if 0	//see BE_TOP_HW_O20_SetPmMode
		/* AVTASK-571, restore picinit */
		PQE_PM_REG_WR(0xC9010000,0x00FF0000);//CCO_CTRL - PIC_INIT//move to each module
		#endif

		pqe_pm_noti("PQE_PM_HW_FW_RESUME done\n");
	}
	else
	{
		pqe_pm_error("unknown cmd 0x%x\n", cmd);
	}

	return RET_OK;
}
