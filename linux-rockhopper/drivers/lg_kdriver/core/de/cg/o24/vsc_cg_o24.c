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
#ifdef USE_CTOP_CODES_FOR_O24
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
void vsc_cg_o24_init(void);

/*----------------------------------------------------------------------------------------
 *	 global Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/
static int _vsc_cg_o24_set_cfg(struct vsc_cg_cfg *p);
static void _vsc_cg_o24_status(struct seq_file *m);

/*----------------------------------------------------------------------------------------
 *	 Static Variables
 *---------------------------------------------------------------------------------------*/

/*========================================================================================
 *	 Implemontation Group
 *=======================================================================================*/
void vsc_cg_o24_init(void)
{
    vsc_cg_register_set_cfg(_vsc_cg_o24_set_cfg);
    vsc_cg_register_status(_vsc_cg_o24_status);
}

static int _vsc_cg_o24_set_cfg(struct vsc_cg_cfg *p)
{
    if (!p) return -1;
    if (!p->name) return -1;

    DE_NOTI("(%s) ip:0x%x en:%d (dbg:%d)\n",p->name,p->ip,p->en,p->dbg);
    if (p->dbg == 1) return 0;//skup

    if (p->ip == vsc_cg_ip_dnsr0) {
        #ifdef USE_CTOP_CODES_FOR_O24
        CTOP_CTRL_O24Ax_RdFL(SCRG_CTRL_DNSR,crg_dnsr2);
        CTOP_CTRL_O24Ax_Wr01(SCRG_CTRL_DNSR,crg_dnsr2,reg_sr_clk_gate_en,(p->en)? 1:0);//SICDTV-14381 0xCC670008 [3] core clk only
        CTOP_CTRL_O24Ax_WrFL(SCRG_CTRL_DNSR,crg_dnsr2);
        #endif
        DE_NOTI("(%s) done(%d)\n",p->name,p->dbg);
    }

    if (p->ip == vsc_cg_ip_dnsr1) {
        //do nothing
        DE_NOTI("(%s) done(%d)\n",p->name,p->dbg);
    }

    return 0;
}

static void _vsc_cg_o24_status(struct seq_file *m)
{
    #ifdef USE_CTOP_CODES_FOR_O24
    UINT32 u32 = 0;
    CTOP_CTRL_O24Ax_RdFL(SCRG_CTRL_DNSR,crg_dnsr2);//0xCC670008
    u32 = CTOP_CTRL_O24Ax_Rd(SCRG_CTRL_DNSR,crg_dnsr2);
    seq_printf(m, "0x%08x : %s\n",u32,"crg_dnsr2(0xCC670008) [3]reg_sr_clk_gate_en");
    #endif
}
