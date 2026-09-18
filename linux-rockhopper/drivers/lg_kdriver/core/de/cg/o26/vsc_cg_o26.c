/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2013 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.
*/


/** @file
 *
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author	  jaemo.kim (jaemo.kim@lge.com)
 * version	  1.0
 * date		  2011.02.18
 * note		  Additional information.
 *
 * @addtogroup lg1150_de
 * @{
 */

/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/seq_file.h>
#include <asm/io.h>

#include "base_types.h"
#include "debug_util.h"
#include "os_util.h"

#include "de_model.h"
#include "de_ver_def.h"
#include "de_def.h"
#include "cg/vsc_cg.h"
#ifdef USE_CTOP_CODES_FOR_O26
#include "sys_regs.h"
#endif

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
extern void vsc_cg_register_status(void(*status)(struct seq_file *));

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 global Functions
 *---------------------------------------------------------------------------------------*/
void vsc_cg_o26_init(void);

/*----------------------------------------------------------------------------------------
 *	 global Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/
static int _vsc_cg_o26_set_cfg(struct vsc_cg_cfg *p);
static void _vsc_cg_o26_status(struct seq_file *m);

/*----------------------------------------------------------------------------------------
 *	 Static Variables
 *---------------------------------------------------------------------------------------*/

/*========================================================================================
 *	 Implemontation Group
 *=======================================================================================*/
void vsc_cg_o26_init(void)
{
    vsc_cg_register_set_cfg(_vsc_cg_o26_set_cfg);
    vsc_cg_register_status(_vsc_cg_o26_status);
}

static int _vsc_cg_o26_set_cfg(struct vsc_cg_cfg *p)
{
    if (!p) return -1;
    if (!p->name) return -1;

    DE_NOTI("(%s) ip:0x%x en:%d (dbg:%d)\n",p->name,p->ip,p->en,p->dbg);
    if (p->dbg == 1) return 0;//skup

    if (p->ip == vsc_cg_ip_dnsr0) {
        #ifdef USE_CTOP_CODES_FOR_O26
        CTOP_CTRL_O26Ax_RdFL(SCRG_CTRL_DNSR0,crg_dnsr002);
        CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_DNSR0,crg_dnsr002,reg_dnsr_sr_clk_gate_en,(p->en)? 1:0);//SICDTV-14381:core clk only
        CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_DNSR0,crg_dnsr002);
        #endif
        DE_NOTI("(%s) dnsr0 sr_clk_gate_en done(%d)\n",p->name,p->dbg);
    }

    if (p->ip == vsc_cg_ip_dnsr1) {
        #ifdef USE_CTOP_CODES_FOR_O26
        CTOP_CTRL_O26Ax_RdFL(SCRG_CTRL_DNSR1,crg_dnsr002);
        CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_DNSR1,crg_dnsr002,reg_dnsr_sr_clk_gate_en,(p->en)? 1:0);//SICDTV-14381:core clk only
        CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_DNSR1,crg_dnsr002);
        #endif
        DE_NOTI("(%s) dnsr1 sr_clk_gate_en done(%d)\n",p->name,p->dbg);
    }

    return 0;
}

static void _vsc_cg_o26_status(struct seq_file *m)
{
    #ifdef USE_CTOP_CODES_FOR_O26
    UINT32 u32 = 0;
    u32 = CTOP_CTRL_O26Ax_Rd(SCRG_CTRL_DNSR0,crg_dnsr002);
    seq_printf(m, "0x%08x : %s\n",u32,"crg_dnsr0002(0xCC490008) [6]reg_dnsr0_sr_clk_gate_en");
    u32 = CTOP_CTRL_O26Ax_Rd(SCRG_CTRL_DNSR1,crg_dnsr002);
    seq_printf(m, "0x%08x : %s\n",u32,"crg_dnsr1002(0xCC4B0008) [6]reg_dnsr1_sr_clk_gate_en");
    #endif
}
