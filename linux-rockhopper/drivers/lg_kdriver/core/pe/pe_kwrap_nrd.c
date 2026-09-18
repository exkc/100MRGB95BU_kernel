/*
    SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
    Copyright(c) 2020 by LG Electronics Inc.

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    version 2 as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
*/

/** @file pe_kwrap_nrd.c
 *
 *	application interface functions for picture enhancement.
 *	These include following functions.
 *	- noise reduction (DNR)
 *
 *
 *	@author		Seung-Jun, Youm(sj.youm@lge.com)
 *	@modified	Kanthiraj, S(kanthiraj.s@lge.com)
 *	@version	0.1
 *	@note
 *	@date			2011.06.11
 *	@modified date	2015.05.20
 *	@see
 */

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <linux/interrupt.h>
#include <asm/io.h>
		
#include "base_types.h"
#include "os_util.h"
#include "debug_util.h"
		
#include "pe_def.h"

#include "pe_nrd.h"

#include "pe_kwrap.h"
#include "pe_kwrap_def.h"

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------*/
extern UINT32 g_pe_kwrap_ver_mask;

/*----------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------*/
/* dnr cmn */
const LX_PE_NRD_SUDO_DNR_CMN_T g_pe_kwrap_p_sudo_dnr_cmn[PE_KWRAP_NRD_NUM] = {\
	{0, \
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
	0x00, 0x00, 0x00}},
	{0, \
	{0x01, 0xD0, 0x01, 0x01, 0x01, 0x20, 0x10, 0x01, 0x01, \
	0x01, 0x01, 0x10}}, \
	{0, \
	{0x01, 0xFF, 0x01, 0x01, 0x01, 0x38, 0x0E, 0x01, 0x01, \
	0x01, 0x01, 0x1B}}, \
	{0, \
	{0x01, 0xFF, 0x01, 0x01, 0x01, 0x50, 0x18, 0x01, 0x01, \
	0x01, 0x01, 0x20}}, \
	{0, \
	{0x01, 0xFF, 0x01, 0x01, 0x01, 0x38, 0x0E, 0x01, 0x01, \
	0x01, 0x01, 0x1B}}
};
const LX_PE_NRD_DNR6_CMN_T g_pe_kwrap_p_dnr6_cmn[PE_KWRAP_NRD_NUM] = {\
	{0, \
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
	0x00, 0x00, 0x00, 0x00, 0x00}},
	{0, \
	{0x01, 0x01, 0x10, 0x10, 0x01, 0x01, 0x01, 0x01, 0x00, 0x10, \
	0x01, 0x60, 0x60, 0xd0, 0xd0}}, \
	{0, \
	{0x01, 0x01, 0x15, 0x15, 0x01, 0x01, 0x01, 0x01, 0x00, 0x15, \
	0x01, 0x80, 0x80, 0xd0, 0xd0}}, \
	{0, \
	{0x01, 0x01, 0x20, 0x20, 0x01, 0x01, 0x01, 0x01, 0x00, 0x20, \
	0x01, 0xff, 0xff, 0xd0, 0xd0}}, \
	{0, \
	{0x01, 0x01, 0x15, 0x15, 0x01, 0x01, 0x01, 0x01, 0x00, 0x15, \
	0x01, 0x80, 0x80, 0xd0, 0xd0}}
};
const LX_PE_NRD_DNR7_CMN_T g_pe_kwrap_p_dnr7_cmn[PE_KWRAP_NRD_NUM] = {\
	{0, \
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
	0x00, 0x00, 0x00}},
	{0, \
	{0x01, 0x01, 0x10, 0x10, 0x01, 0x01, 0x01, 0x01, 0x10, \
	0x01, 0xD0, 0x01}}, \
	{0, \
	{0x01, 0x01, 0x1B, 0x70, 0x01, 0x01, 0x01, 0x01, 0x1B, \
	0x01, 0xFF, 0x01}}, \
	{0, \
	{0x01, 0x01, 0x20, 0x80, 0x01, 0x01, 0x01, 0x01, 0x20, \
	0x01, 0xff, 0x01}}, \
	{0, \
	{0x01, 0x01, 0x1B, 0x70, 0x01, 0x01, 0x01, 0x01, 0x1B, \
	0x01, 0xFF, 0x01}}
};

/* dnr detail */
const LX_PE_NRD_DNR5_DETAIL_T g_pe_kwrap_p_dnr5_detail[PE_KWRAP_NRD_FMT_NUM] = {\
	/* PE_KWRAP_NRD_FMT_SD */{0, \
	/*dc_bnr*/0x01, 0x00, 0x01, 0x01, 0x01, 0xff, 0xff, 0x0d, 0x01, \
	/*dc_bnr*/0x05, 0x02, 0x05, 0x0a, 0x0a, 0x15, 0x25, 0x40, 0x80, \
	/*ac_bnr*/0x0b, 0x0b, 0x0b, 0x30, 0x10, 0x30, 0x10, 0x0a, 0x10, \
	/*ac_bnr*/0x30, 0x50, 0xfa, 0x96, 0x00, 0x00, 0xff, 0xb0, 0x60, \
	/*ac_bnr*/0x08, 0xff, 0x80, 0x40, 0x00, 0x40, 0x0a, 0x04, 0x04, \
	/*mnr   */0x01, 0x01, 0x24, 0x00, 0x48, 0x44, 0x38, 0x28, 0xff, \
	/*mnr   */0x00, 0x00, 0x00, 0x10, 0x30, 0x30, 0x20, 0xff, 0x00}, \
	/* PE_KWRAP_NRD_FMT_HD */{0, \
	/*dc_bnr*/0x01, 0x00, 0x01, 0x01, 0x01, 0xff, 0xff, 0x0d, 0x01, \
	/*dc_bnr*/0x05, 0x02, 0x05, 0x0a, 0x0a, 0x15, 0x25, 0x40, 0x80, \
	/*ac_bnr*/0x0b, 0x0b, 0x0b, 0x30, 0x10, 0x30, 0x10, 0x0a, 0x10, \
	/*ac_bnr*/0x30, 0x50, 0xfa, 0x96, 0x32, 0x01, 0xff, 0xb0, 0x60, \
	/*ac_bnr*/0x08, 0xff, 0x80, 0x40, 0x00, 0x40, 0x0a, 0x04, 0x04, \
	/*mnr   */0x01, 0x01, 0x24, 0x00, 0x48, 0x44, 0x38, 0x28, 0xff, \
	/*mnr   */0x00, 0x00, 0x00, 0x10, 0x30, 0x30, 0x20, 0xff, 0x00}
};
const LX_PE_NRD_DNR6_DETAIL_T g_pe_kwrap_p_dnr6_detail[PE_KWRAP_NRD_FMT_NUM] = {\
	/*PE_KWRAP_NRD_FMT_SD*/{0, \
	/*dc_bnr[00]*/{0x01, 0x00, 0x01, 0x01, 0x01, 0xFF, 0xFF, 0x0D, 0x01, 0x05, \
	/*dc_bnr[10]*/0x02, 0x05, 0x0A, 0x0A, 0x80, 0x40, 0x25, 0x15, 0x00, 0x40, \
	/*dc_bnr[20]*/0x0A, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x10}, \
	/*ac_bnr[00]*/{0x0B, 0x0B, 0x0B, 0x30, 0x30, 0x10, 0x10, 0x03, 0x50, 0x30, \
	/*ac_bnr[10]*/0x10, 0x0A, 0xFF, 0xA0, 0x60, 0x00, 0x00, 0x00, 0x00, 0x96, \
	/*ac_bnr[20]*/0xFA, 0x20, 0x60, 0xA0, 0xFF, 0x60, 0xA0, 0xA0}, \
	/*mosqnr[00]*/{0x02, 0x00, 0x24, 0x00, 0x48, 0x44, 0x38, 0x28, 0xFF, 0x00, \
	/*mosqnr[10]*/0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x30}}, \
	/*PE_KWRAP_NRD_FMT_HD*/{0, \
	/*dc_bnr[00]*/{0x01, 0x00, 0x01, 0x01, 0x01, 0xFF, 0xFF, 0x0D, 0x01, 0x05, \
	/*dc_bnr[10]*/0x02, 0x05, 0x0A, 0x0A, 0x80, 0x40, 0x25, 0x15, 0x00, 0x40, \
	/*dc_bnr[20]*/0x0A, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x10}, \
	/*ac_bnr[00]*/{0x0B, 0x0B, 0x0B, 0x30, 0x30, 0x10, 0x10, 0x03, 0x50, 0x30, \
	/*ac_bnr[10]*/0x10, 0x0A, 0xFF, 0xA0, 0x60, 0x00, 0x00, 0x01, 0x32, 0x96, \
	/*ac_bnr[20]*/0xFA, 0x08, 0x60, 0xB0, 0xFF, 0x40, 0x80, 0xFF}, \
	/*mosqnr[00]*/{0x02, 0x00, 0x24, 0x00, 0x48, 0x44, 0x38, 0x28, 0xFF, 0x00, \
	/*mosqnr[10]*/0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x30}}
};
const LX_PE_NRD_DNR7_DETAIL_T g_pe_kwrap_p_dnr7_detail[PE_KWRAP_NRD_FMT_NUM] = {\
	/*PE_KWRAP_NRD_FMT_SD*/{0, \
	/*dc_bnr[00]*/{0x01, 0x00, 0x01, 0x01, 0x01, 0x30, 0x10,  0x07, 0x0D, 0x04, \
	/*dc_bnr[10]*/ 0x15, 0x80, 0x40, 0x25, 0x15, 0x04, 0x04, 0x00, 0x40, 0x80, \
	/*dc_bnr[20]*/ 0xFF, 0x00, 0x02, 0x20}, \
	/*ac_bnr[00]*/{0x0B, 0x0B, 0x04, 0x60, 0x37, 0x40, 0x19, 0x00, 0x03, 0x60, \
	/*ac_bnr[10]*/ 0x40, 0x0A, 0x05, 0xFF, 0xC0, 0x80, 0x00, 0x07, 0x40, 0x0A, \
	/*ac_bnr[20]*/ 0x01, 0x32, 0x96, 0xFA, 0xA0, 0xC0, 0xD0, 0xE0, 0x80, 0xb0, \
	/*ac_bnr[30]*/ 0xC0}, \
	/*mosqnr[00]*/{0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00}}, \
	/*PE_KWRAP_NRD_FMT_HD*/{0, \
	/*dc_bnr[00]*/{0x01, 0x00, 0x01, 0x01, 0x01, 0x30, 0x10,  0x07, 0x0D, 0x04, \
	/*dc_bnr[10]*/ 0x15, 0x80, 0x40, 0x25, 0x15, 0x04, 0x04, 0x00, 0x40, 0x80, \
	/*dc_bnr[20]*/ 0xFF, 0x00, 0x02, 0x20}, \
	/*ac_bnr[00]*/{0x0B, 0x0B, 0x04, 0x60, 0x37, 0x40, 0x19, 0x00, 0x03, 0x60, \
	/*ac_bnr[10]*/ 0x40, 0x0A, 0x05, 0xFF, 0xC0, 0x80, 0x00, 0x07, 0x40, 0x0A, \
	/*ac_bnr[20]*/ 0x01, 0x32, 0x96, 0xFA, 0xA0, 0xC0, 0xD0, 0xE0, 0x80, 0xb0, \
	/*ac_bnr[30]*/ 0xC0}, \
	/*mosqnr[00]*/{0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00}}
};

/* tnr cmn */
const LX_PE_NRD_TNR5_CMN_T g_pe_kwrap_p_tnr5_cmn[PE_KWRAP_NRD_NUM] = {\
	{0, 0, \
	{0xB0008000, 0x60004B00, 0x3C002C00, 0x14000A00, 0xB0008000, 0x60004B00, 0x3C002C00, 0x14000A00, \
	0xB0008000, 0x60004B00, 0x3C002C00, 0x14000A00, 0xB0008000, 0x60004B00, 0x3C002C00, 0x14000A00}, \
	{0xB0008000, 0x60004B00, 0x3C002C00, 0x14000A00, 0xB0008000, 0x60004B00, 0x3C002C00, 0x14000A00, \
	0xB0008000, 0x60004B00, 0x3C002C00, 0x14000A00, 0xB0008000, 0x60004B00, 0x3C002C00, 0x14000A00}, \
	{0xB0008000, 0x60004B00, 0x3C002C00, 0x14000A00, 0xB0008000, 0x60004B00, 0x3C002C00, 0x14000A00, \
	0xB0008000, 0x60004B00, 0x3C002C00, 0x14000A00, 0xB0008000, 0x60004B00, 0x3C002C00, 0x14000A00}, \
	{0x18100804, 0x40302820, 0x00000000, 0x00000000, 0x18100804, 0x40302820, 0x00000000, 0x00000000}}, \
	{0, 1, \
	{0xB0008000, 0x60004B00, 0x3C402C50, 0x14900A98, 0xB0008000, 0x60004B00, 0x3C402C50, 0x14900A98, \
	0xB0008000, 0x60004B00, 0x3C402C50, 0x14900A98, 0xB0008000, 0x60004B00, 0x3C402C50, 0x14900A98}, \
	{0xB0008000, 0x60004B00, 0x3C402C50, 0x14900A98, 0xB0008000, 0x60004B00, 0x3C402C50, 0x14900A98, \
	0xB0008000, 0x60004B00, 0x3C402C50, 0x14900A98, 0xB0008000, 0x60004B00, 0x3C402C50, 0x14900A98}, \
	{0xB0008000, 0x60004B00, 0x3C402C50, 0x14900A98, 0xB0008000, 0x60004B00, 0x3C402C50, 0x14900A98, \
	0xB0008000, 0x60004B00, 0x3C402C50, 0x14900A98, 0xB0008000, 0x60004B00, 0x3C402C50, 0x14900A98}, \
	{0x18100804, 0x40302820, 0x08204058, 0x00000204, 0x18100804, 0x40302820, 0x20304070, 0x00000204}}, \
	{0, 2, \
	{0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4, 0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4, \
	0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4, 0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4}, \
	{0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4, 0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4, \
	0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4, 0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4}, \
	{0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4, 0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4, \
	0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4, 0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4}, \
	{0x18100804, 0x40302820, 0x0C33668C, 0x00000306, 0x18100804, 0x40302820, 0x334C66B3, 0x00000306}}, \
	{0, 3, \
	{0xB0008000, 0x60004B00, 0x3C702C90, 0x14A80AC0, 0xB0008000, 0x60004B00, 0x3C702C90, 0x14A80AC0, \
	0xB0008000, 0x60004B00, 0x3C702C90, 0x14A80AC0, 0xB0008000, 0x60004B00, 0x3C702C90, 0x14A80AC0}, \
	{0xB0008000, 0x60004B00, 0x3C702C90, 0x14A80AC0, 0xB0008000, 0x60004B00, 0x3C702C90, 0x14A80AC0, \
	0xB0008000, 0x60004B00, 0x3C702C90, 0x14A80AC0, 0xB0008000, 0x60004B00, 0x3C702C90, 0x14A80AC0}, \
	{0xB0008000, 0x60004B00, 0x3C702C90, 0x14A80AC0, 0xB0008000, 0x60004B00, 0x3C702C90, 0x14A80AC0, \
	0xB0008000, 0x60004B00, 0x3C702C90, 0x14A80AC0, 0xB0008000, 0x60004B00, 0x3C702C90, 0x14A80AC0}, \
	{0x18100804, 0x40302820, 0x104080B0, 0x00000408, 0x18100804, 0x40302820, 0x406080E0, 0x00000408}}, \
	{0, 4, \
	{0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4, 0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4, \
	0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4, 0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4}, \
	{0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4, 0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4, \
	0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4, 0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4}, \
	{0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4, 0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4, \
	0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4, 0xB0008000, 0x60004B00, 0x3C402C50, 0x149C0AB4}, \
	{0x18100804, 0x40302820, 0x0C33668C, 0x00000306, 0x18100804, 0x40302820, 0x334C66B3, 0x00000306}}
};
#if 0
const LX_PE_NRD_TNR7_CMN_T g_pe_kwrap_p_tnr7_cmn[PE_KWRAP_NRD_NUM] = {\
	{0, 0, \
	{0xB0008000, 0x60004000, 0x30402080, 0x109008a0, 0xb0008000, 0x60004000, 0x30402080, 0x109008a0, \
	0xB0008000, 0x60004000, 0x30402080, 0x109008a0, 0xb0008000, 0x60004000, 0x30402080, 0x109008a0}, \
	{0x00, 0x00, 0x00, 0x00, 0x00},\
	{0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,\
	0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,\
	0x00, 0x00}\
	}, \
	{0, 1, \
	{0xB0008000, 0x60004000, 0x30402080, 0x109008a0, 0xb0008000, 0x60004000, 0x30402080, 0x109008a0, \
	0xB0008000, 0x60004000, 0x30402080, 0x109008a0, 0xb0008000, 0x60004000, 0x30402080, 0x109008a0}, \
	{0x80, 0x80, 0x60, 0x60, 0x04},\
	{0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,\
	0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,\
	0x00, 0x00}\
	}, \
	{0, 2, \
	{0xB0008000, 0x60004000, 0x30402080, 0x109008a0, 0xb0008000, 0x60004000, 0x30402080, 0x109008a0, \
	0xB0008000, 0x60004000, 0x30402080, 0x109008a0, 0xb0008000, 0x60004000, 0x30402080, 0x109008a0}, \
	{0x80, 0x80, 0x80, 0x80, 0x04},\
	{0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,\
	0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,\
	0x00, 0x00}\
	}, \
	{0, 3, \
	{0xB0008000, 0x60004000, 0x30402080, 0x109008a0, 0xb0008000, 0x60004000, 0x30402080, 0x109008a0, \
	0xB0008000, 0x60004000, 0x30402080, 0x109008a0, 0xb0008000, 0x60004000, 0x30402080, 0x109008a0}, \
	{0x80, 0x80, 0xa0, 0xa0, 0x04},\
	{0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,\
	0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,\
	0x00, 0x00}\
	}, \
	{0, 4, \
	{0xB0008000, 0x60004000, 0x30402080, 0x109008a0, 0xb0008000, 0x60004000, 0x30402080, 0x109008a0, \
	0xB0008000, 0x60004000, 0x30402080, 0x109008a0, 0xb0008000, 0x60004000, 0x30402080, 0x109008a0}, \
	{0x80, 0x80, 0x80, 0x80, 0x04},\
	{0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,\
	0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,\
	0x00, 0x00}\
	} \
};
#endif


/* tnr detail */

const LX_PE_NRD_TNR5_DETAIL_T g_pe_kwrap_p_tnr5_detail[PE_KWRAP_SHP_FMT_NUM] = {\
	/*PE_KWRAP_NRD_FMT_SD*/{0, \
	/*s_m[00]*/{0x01, 0x01, 0xC0, 0x01, 0x40, 0x16, 0x01, 0x03, 0x02, 0x01, \
	/*s_m[10]*/0x01, 0x01, 0x18, 0x14, 0x18, 0x00, 0x01, 0x00, 0x01, 0x10, \
	/*s_m[20]*/0x00, 0x01, 0x10, 0x02}, \
	/*edf[00]*/{0x20, 0x10, 0x10, 0x08, 0x00, 0x50, 0x90, 0x10, 0x00, 0x40, \
	/*edf[10]*/0xFF, 0x18, 0x00, 0xA0, 0xFF, 0x3C, 0x00, 0xC8, 0xFF, 0x30, \
	/*edf[20]*/0x00, 0x70, 0xFF, 0x20, 0x00, 0x70, 0xFF, 0x18, 0x00}, \
	/*m_c[00]*/{0x00, 0x00, 0x01, 0xFF, 0x14, 0x01, 0xFF, 0x01, 0x20, 0x18, \
	/*m_c[10]*/0x04, 0x04, 0x18, 0x00, 0x02, 0x1C, 0x01, 0x00, 0x00, 0x00, \
	/*m_c[20]*/0x00, 0x02, 0x18, 0x02, 0x00, 0x00, 0x00}}, \
	/*PE_KWRAP_NRD_FMT_HD*/{0, \
	/*s_m[00]*/{0x01, 0x01, 0x80, 0x01, 0x40, 0x08, 0x01, 0x02, 0x03, 0x01, \
	/*s_m[10]*/0x01, 0x01, 0x11, 0x13, 0x19, 0x00, 0x01, 0x00, 0x11, 0x10, \
	/*s_m[20]*/0x00, 0x01, 0x10, 0x00}, \
	/*edf[00]*/{0x20, 0x10, 0x10, 0x08, 0x00, 0x50, 0x90, 0x10, 0x00, 0x40, \
	/*edf[10]*/0xFF, 0x18, 0x00, 0xA0, 0xFF, 0x3C, 0x00, 0xC8, 0xFF, 0x30, \
	/*edf[20]*/0x00, 0x70, 0xFF, 0x20, 0x00, 0x70, 0xFF, 0x18, 0x00}, \
	/*m_c[00]*/{0x00, 0x00, 0x01, 0xFF, 0x14, 0x01, 0xFF, 0x00, 0x20, 0x18, \
	/*m_c[10]*/0x04, 0x04, 0x18, 0x00, 0x02, 0x1C, 0x01, 0x00, 0x00, 0x00, \
	/*m_c[20]*/0x00, 0x02, 0x18, 0x02, 0x00, 0x00, 0x00}}
};



/*----------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------*/
int KWRAP_PE_GetDnrDcntCmnParam(void *param);

/*----------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------*/

/*============================================================================
	Implementation Group
============================================================================*/

#define _KWRAP_PE_NRD_
#if 0
/**
 * get digital noise reduction common default settings
 *	- input data : see PE_KWRAP_NRD_TYPE
 *
 * @param   *param [in/out] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetDnrCmnDefaultSettings(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	UINT32 param_data = 0;
	__attribute__((unused)) UINT8 *pd;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		const LX_PE_NRD_DNR9_CMN_T *p_val=NULL;
		do {
			CHECK_KNULL(ret, param);
			CHECK_KNULL(ret, param->st_data);
			param_data = (param->data<PE_KWRAP_NRD_NUM)? \
				param->data:PE_KWRAP_NRD_OFF;
			//p_val = &(g_pe_kwrap_p_dnr9_cmn[param_data]);
			PE_KWRAP_DBG_PRINT(NRD, \
				"wid:%d, data:%d\n", param->wid, param->data);
			memcpy(param->st_data, p_val, sizeof(LX_PE_NRD_DNR9_CMN_T));
			pd = (UINT8 *)p_val->dnr______ui;
			PE_KWRAP_DBG_PRINT(NRD, \
				"[%d]:\n"\
				"dnr______ui    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"dnr______ui    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"dnr______ui    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
				p_val->win_id, \
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
				pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
				pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28]);
		}while (0);
	}
	else if(PE_KDRV_VER_M17)
	{
		const LX_PE_NRD_DNR8_CMN_T *p_val=NULL;
		do {
			CHECK_KNULL(ret, param);
			CHECK_KNULL(ret, param->st_data);
			param_data = (param->data<PE_KWRAP_NRD_NUM)? \
				param->data:PE_KWRAP_NRD_OFF;
			p_val = &(g_pe_kwrap_p_dnr8_cmn[param_data]);
			PE_KWRAP_DBG_PRINT(NRD, \
				"wid:%d, data:%d\n", param->wid, param->data);
			memcpy(param->st_data, p_val, sizeof(LX_PE_NRD_DNR8_CMN_T));
			PE_KWRAP_DBG_PRINT(NRD, \
				"[%d]:\n"\
				"data[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"data[10]0x%02X,0x%02X,0x%02X\n", \
				p_val->win_id, \
				p_val->data[0],  p_val->data[1],  p_val->data[2],  p_val->data[3],  p_val->data[4], \
				p_val->data[5],  p_val->data[6],  p_val->data[7],  p_val->data[8],  p_val->data[9], \
				p_val->data[10], p_val->data[11], p_val->data[12]);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
#endif
/**
 * set digital noise reduction common parameter by specific value
 *	- input data : see PE_KWRAP_NRD_TYPE
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDnrCmnCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20)
	{
		ret = KWRAP_PE_SetDnrCmnBspDB(param);
	}
	else if(PE_KDRV_VER_M17)
	{
		LX_PE_NRD_DNR8_CMN_T ctrl;
		ret = KWRAP_PE_SetDefaultParam(param, \
			PE_KWRAP_DFLT_PARAM_DNR_CMN, (void *)&ctrl, __F__, __L__);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set digital noise reduction common parameter
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDnrCmnParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	// static UINT32 chk = 0x0;
	#endif
	// UINT8 *pd;
	PE_CHECK_KWRAP_FUNC_ON(NRD);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20 )
	{
		LX_PE_NRD_DNR_CMN_T *pp = (LX_PE_NRD_DNR_CMN_T *)param;
		do {
			CHECK_KNULL(ret, param);
			ret = KWRAP_PE_CheckDnrCmnParam(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]check_dnr_cmn.\n", __F__, __L__);
			PE_CHECK_ACTION(pp->win_id>LX_PE_WIN_ALL, ret=RET_OK;break);
			ret = PE_NRD_SetDnrCmnCtrl(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get digital noise reduction common parameter
 * - use input struct LX_PE_NRD_DNR6_CMN_T for H15
 * - use input struct LX_PE_NRD_DNR4_CMN_T for M14BX
 * - use input struct LX_PE_NRD_DNR3_CMN_T for H14AX
 * - use input struct LX_PE_NRD_DNR2_CMN_T for M14AXBX
 * - use input struct LX_PE_NRD_DNR0_CMN_T for H13AX
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetDnrCmnParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = PE_KWRAP_IOCTL(LX_PE_NRD_DNR_CMN_T, param, GET, NRD);
	}
	else if(PE_KDRV_VER_M17)
	{
		ret = PE_KWRAP_IOCTL(LX_PE_NRD_DNR8_CMN_T, param, GET, NRD);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set decontour common parameter by specific value
 *	- input data : see PE_KWRAP_NRD_TYPE
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDnrDcntCmnCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_O18)
	{
		ret = KWRAP_PE_SetDnrDcntCmnBspDB(param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set digital noise reduction common parameter
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDnrDcntCmnParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(NRD);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20)
	{
		LX_PE_NRD_DCNT_CMN_T *pp = (LX_PE_NRD_DCNT_CMN_T *)param;
		do {
			CHECK_KNULL(ret, param);
			ret = KWRAP_PE_CheckDnrDcntCmnParam(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]check_dnr_dcnt_cmn.\n", __F__, __L__);
			PE_CHECK_ACTION(pp->win_id>LX_PE_WIN_ALL, ret=RET_OK;break);
			ret = PE_NRD_SetDnrDcntCmnCtrl(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get digital noise reduction common parameter
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetDnrDcntCmnParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = PE_KWRAP_IOCTL(LX_PE_NRD_DCNT_CMN_T, param, GET, NRD);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}

/**
 * set decontour common parameter by specific value
 *	- input data : see PE_KWRAP_NRD_TYPE
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetLedDcntCmnCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_O18)
	{
		ret = KWRAP_PE_SetLedDcntCmnBspDB(param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}

/**
 * set digital noise reduction common parameter
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetLedDnrCmnParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif
	__attribute__((unused)) UINT8 *pd;
	PE_CHECK_KWRAP_FUNC_ON(NRD);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_LED_DCNT_CMN_T *pp = (LX_PE_LED_DCNT_CMN_T *)param;
		do {
			CHECK_KNULL(ret, param);
			ret = KWRAP_PE_CheckLedDcntCmnParam(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]check_dnr_cmn.\n", __F__, __L__);
			PE_CHECK_ACTION(pp->win_id>LX_PE_WIN_ALL, ret=RET_OK;break);
			ret = PE_KWRAP_IOCTL(LX_PE_LED_DCNT_CMN_T, param, SET, NRD);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}

/**
 * get digital noise reduction common parameter
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetLedDnrCmnParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18)
	{
		ret = PE_KWRAP_IOCTL(LX_PE_LED_DCNT_CMN_T, param, GET, NRD);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set led decontour common parameter
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetLedDcntCmnParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif
	__attribute__((unused)) UINT8 *pd;
	PE_CHECK_KWRAP_FUNC_ON(NRD);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20)
	{
		LX_PE_LED_DCNT_CMN_T *pp = (LX_PE_LED_DCNT_CMN_T *)param;
		do {
			CHECK_KNULL(ret, param);
			ret = KWRAP_PE_CheckLedDcntCmnParam(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]check_dnr_cmn.\n", __F__, __L__);
			PE_CHECK_ACTION(pp->win_id>LX_PE_WIN_ALL, ret=RET_OK;break);
			ret = PE_NRD_SetLedDcntCmnCtrl(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get led decontour common parameter
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetLedDcntCmnParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18)
	{
		ret = PE_KWRAP_IOCTL(LX_PE_LED_DCNT_CMN_T, param, GET, NRD);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set digital noise reduction detail by specific value
 *	- input data : see PE_KWRAP_NRD_FMT_TYPE
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDnrDetailCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = KWRAP_PE_SetDnrDetailBspDB(param);
	}
	else if (PE_KDRV_VER_M17)
	{
		LX_PE_NRD_DNR8_DETAIL_T ctrl;
		ret = KWRAP_PE_SetDefaultParam(param, \
			PE_KWRAP_DFLT_PARAM_DNR_DTL, (void *)&ctrl, __F__, __L__);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set digital noise reduction detail parameter
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDnrDetailParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(NRD);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_M19 || PE_KDRV_VER_O20)
	{
		LX_PE_NRD_DNR_DETAIL_T *pp = (LX_PE_NRD_DNR_DETAIL_T *)param;
		do {
			CHECK_KNULL(ret, param);
			ret = KWRAP_PE_CheckDnrDetailParam(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]check_dnr_cmn.\n", __F__, __L__);
			PE_CHECK_ACTION(pp->win_id>LX_PE_WIN_ALL, ret=RET_OK;break);
			ret = PE_NRD_SetDnrDetailCtrl(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else if (PE_KDRV_VER_M17)
	{
		LX_PE_NRD_DNR8_DETAIL_T *pp = NULL;
		UINT8 *pd = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_NRD_DNR8_DETAIL_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_NRD_DNR8_DETAIL_T *)param;
			pd = pp->dc_bnr;
			PE_KWRAP_DBG_PRINT(NRD, \
				"[%d]:\n"\
				"dc_bnr[00]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
				"dc_bnr[10]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
				"dc_bnr[20]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
				"dc_bnr[30]%3d,%3d,%3d,%3d,%3d,%3d,%3d\n", \
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19], \
				pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29], \
				pd[30], pd[31], pd[32], pd[33], pd[34], pd[35], pd[36]);
			pd = pp->ac_bnr;
			PE_KWRAP_DBG_PRINT(NRD, \
				"[%d]:\n"\
				"ac_bnr[00]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
				"ac_bnr[10]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
				"ac_bnr[20]%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,\n"\
				"ac_bnr[30]%3d\n", \
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19], \
				pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29], \
				pd[30]);
			pd = pp->mosqnr;
			PE_KWRAP_DBG_PRINT(NRD, \
				"[%d]:\n"\
				"mosqnr[00]%3d,%3d,%3d,%3d,%3d,%3d\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5]);
			pd = pp->decont;
			PE_KWRAP_DBG_PRINT(NRD, \
				"[%d]:\n"\
				"decont[00]%3d,%3d,%3d,%3d,%3d\n", \
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_NRD_DNR8_DETAIL_T, NRD);
			#endif
			ret = PE_KWRAP_IOCTL(LX_PE_NRD_DNR8_DETAIL_T, param, SET, NRD);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get digital noise reduction detail parameter
 * - use input struct LX_PE_NRD_DNR6_DETAIL_T for H15
 * - use input struct LX_PE_NRD_DNR4_DETAIL_T for M14BX
 * - use input struct LX_PE_NRD_DNR2_DETAIL_T for M14AXBX
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetDnrDetailParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = PE_KWRAP_IOCTL(LX_PE_NRD_DNR_DETAIL_T, param, GET, NRD);
	}
	else if (PE_KDRV_VER_M17)
	{
		ret = PE_KWRAP_IOCTL(LX_PE_NRD_DNR8_DETAIL_T, param, GET, NRD);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set digital noise reduction detail parameter
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetLedDnrDetailParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(NRD);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18)
	{
		LX_PE_LED_DNR_DETAIL_T *pp = NULL;
		UINT16 *pd = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_LED_DNR_DETAIL_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_LED_DNR_DETAIL_T *)param;
			pd = pp->dnrled_dcnt;
			PE_KWRAP_DBG_PRINT(NRD, \
			"[%d]:\n"\
			"dnrled_dcnt    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"dnrled_dcnt    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"dnrled_dcnt    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"dnrled_dcnt    [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"dnrled_dcnt    [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"dnrled_dcnt    [50]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"dnrled_dcnt    [60]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"dnrled_dcnt    [70]0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29],\
			pd[30], pd[31], pd[32], pd[33], pd[34], pd[35], pd[36], pd[37], pd[38], pd[39],\
			pd[40], pd[41], pd[42], pd[43], pd[44], pd[45], pd[46], pd[47], pd[48], pd[49],\
			pd[50], pd[51], pd[52], pd[53], pd[54], pd[55], pd[56], pd[57], pd[58], pd[59],\
			pd[60], pd[61], pd[62], pd[63], pd[64], pd[65], pd[66], pd[67], pd[68], pd[69],\
			pd[70]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_LED_DNR_DETAIL_T, NRD);
			#endif
			ret = PE_KWRAP_IOCTL(LX_PE_LED_DNR_DETAIL_T, param, SET, NRD);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get digital noise reduction detail parameter
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetLedDnrDetailParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18)
	{
		ret = PE_KWRAP_IOCTL(LX_PE_LED_DCNT_DETAIL_T, param, GET, NRD);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}

/**
 * set digital noise reduction detail parameter
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDnrDcntDetailParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(NRD);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20)
	{
		LX_PE_NRD_DCNT_DETAIL_T *pp = (LX_PE_NRD_DCNT_DETAIL_T *)param;
		do {
			CHECK_KNULL(ret, param);
			ret = KWRAP_PE_CheckDnrDcntDetailParam(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]check_dnr_cmn.\n", __F__, __L__);
			PE_CHECK_ACTION(pp->win_id>LX_PE_WIN_ALL, ret=RET_OK;break);
			ret = PE_NRD_SetDnrDcntDetailCtrl(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get digital noise reduction detail parameter
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetDnrDcntDetailParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = PE_KWRAP_IOCTL(LX_PE_NRD_DCNT_DETAIL_T, param, GET, NRD);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}

/**
 * set led decontour detail parameter
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetLedDcntDetailParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(NRD);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20)
	{
		LX_PE_LED_DCNT_DETAIL_T *pp = (LX_PE_LED_DCNT_DETAIL_T *)param;
		do {
			CHECK_KNULL(ret, param);
			ret = KWRAP_PE_CheckLedDcntDetailParam(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]check_dnr_cmn.\n", __F__, __L__);
			PE_CHECK_ACTION(pp->win_id>LX_PE_WIN_ALL, ret=RET_OK;break);
			ret = PE_NRD_SetLedDcntDetailCtrl(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get  led decontour detail parameter
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetLedDcntDetailParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O18)
	{
		ret = PE_KWRAP_IOCTL(LX_PE_LED_DCNT_DETAIL_T, param, GET, NRD);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set temporal noise reduction common by specific value
 *	- input data : see PE_KWRAP_NRD_TYPE
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetTnrCmnCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20)
	{
		ret = KWRAP_PE_SetTnrCmnBspDB(param);
	}
	else if (PE_KDRV_VER_M17)
	{
		LX_PE_NRD_TNR7_CMN_T ctrl;
		ret = KWRAP_PE_SetDefaultParam(param, \
			PE_KWRAP_DFLT_PARAM_TNR_CMN, (void *)&ctrl, __F__, __L__);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set temporal noise reduction common parameter
 * - use input struct LX_PE_NRD_TNR5_CMN_T for H15
 * - use input struct LX_PE_NRD_TNR4_CMN_T for M14BX
 * - use input struct LX_PE_NRD_TNR3_CMN_T for H14
 * - use input struct LX_PE_NRD_TNR2_CMN_T for M14AX, H13BX
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetTnrCmnParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(NRD);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20)
	{
		LX_PE_NRD_TNR_CMN_T *pp = (LX_PE_NRD_TNR_CMN_T *)param;
		do {
			CHECK_KNULL(ret, param);
			ret = KWRAP_PE_CheckTnrCmnParam(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]check_dnr_cmn.\n", __F__, __L__);
			PE_CHECK_ACTION(pp->win_id>LX_PE_WIN_ALL, ret=RET_OK;break);
			ret = PE_NRD_SetTnrCmnCtrl(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else if (PE_KDRV_VER_M17)
	{
		LX_PE_NRD_TNR7_CMN_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_NRD_TNR7_CMN_T prev[LX_PE_WIN_NUM];
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_NRD_TNR7_CMN_T *)param;
			PE_KWRAP_DBG_PRINT(NRD, \
				"[%d]tnr_en:%d\n", pp->win_id, pp->tnr_en);
			PE_KWRAP_DBG_PRINT(NRD, \
			"tnr_lut[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr_lut[08]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n", \
			pp->tnr_lut[0],  pp->tnr_lut[1],  pp->tnr_lut[2],  pp->tnr_lut[3], \
			pp->tnr_lut[4],  pp->tnr_lut[5],  pp->tnr_lut[6],  pp->tnr_lut[7], \
			pp->tnr_lut[8],  pp->tnr_lut[9],  pp->tnr_lut[10], pp->tnr_lut[11], \
			pp->tnr_lut[12], pp->tnr_lut[13], pp->tnr_lut[14], pp->tnr_lut[15]);
			PE_KWRAP_DBG_PRINT(NRD, \
			"tnr_lut_gain[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X\n",\
			pp->tnr_lut_gain[0],  pp->tnr_lut_gain[1],  pp->tnr_lut_gain[2],  pp->tnr_lut_gain[3], \
			pp->tnr_lut_gain[4]);
			PE_KWRAP_DBG_PRINT(NRD, \
			"tnr_lut_buff[00]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr_lut_buff[10]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr_lut_buff[20]0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,0x%08X,\n"\
			"tnr_lut_buff[30]0x%08X,0x%08X\n",\
			pp->tnr_lut_buff[0],  pp->tnr_lut_buff[1],  pp->tnr_lut_buff[2],  pp->tnr_lut_buff[3], \
			pp->tnr_lut_buff[4],  pp->tnr_lut_buff[5],  pp->tnr_lut_buff[6],  pp->tnr_lut_buff[7], \
			pp->tnr_lut_buff[8],  pp->tnr_lut_buff[9],  pp->tnr_lut_buff[10], pp->tnr_lut_buff[11], \
			pp->tnr_lut_buff[12], pp->tnr_lut_buff[13], pp->tnr_lut_buff[14], pp->tnr_lut_buff[15], \
			pp->tnr_lut_buff[16],  pp->tnr_lut_buff[17],  pp->tnr_lut_buff[18],  pp->tnr_lut_buff[19], \
			pp->tnr_lut_buff[20],  pp->tnr_lut_buff[21],  pp->tnr_lut_buff[22],  pp->tnr_lut_buff[23], \
			pp->tnr_lut_buff[24],  pp->tnr_lut_buff[25],  pp->tnr_lut_buff[26],  pp->tnr_lut_buff[27], \
			pp->tnr_lut_buff[28],  pp->tnr_lut_buff[29],  pp->tnr_lut_buff[30],  pp->tnr_lut_buff[31]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_NRD_TNR7_CMN_T, NRD);
			#endif
			ret = PE_KWRAP_IOCTL(LX_PE_NRD_TNR7_CMN_T, param, SET, NRD);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get temporal noise reduction common parameter
 * - use input struct LX_PE_NRD_TNR5_CMN_T for H15
 * - use input struct LX_PE_NRD_TNR4_CMN_T for M14BX
 * - use input struct LX_PE_NRD_TNR3_CMN_T for H14
 * - use input struct LX_PE_NRD_TNR2_CMN_T for M14AX, H13BX
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetTnrCmnParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = PE_NRD_GetTnrCmnCtrl(param);
	}
	else if (PE_KDRV_VER_M17)
	{
		ret = PE_KWRAP_IOCTL(LX_PE_NRD_TNR7_CMN_T, param, GET, NRD);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}

/**
 * set temporal noise reduction detail by specific value
 *	- input data : see PE_KWRAP_NRD_FMT_TYPE
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetTnrDetailCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = KWRAP_PE_SetTnrDetailBspDB(param);
	}
	else if (PE_KDRV_VER_M17)
	{
		LX_PE_NRD_TNR6_DETAIL_T ctrl;
		ret = KWRAP_PE_SetDefaultParam(param, \
			PE_KWRAP_DFLT_PARAM_TNR_DTL, (void *)&ctrl, __F__, __L__);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set temporal noise reduction detail parameter
 * - use input struct LX_PE_NRD_TNR7_DETAIL_T for O18, M16P3
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetTnrDetailParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(NRD);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	do {
		LX_PE_NRD_TNR_DETAIL_T *pp = (LX_PE_NRD_TNR_DETAIL_T *)param;
		CHECK_KNULL(ret, param);
		ret = KWRAP_PE_CheckTnrDetailParam(pp);
		PE_CHECK_CODE(ret!=RET_OK, break, \
		"[%s,%d]check_dnr_cmn.\n", __F__, __L__);
		PE_CHECK_ACTION(pp->win_id>LX_PE_WIN_ALL, ret=RET_OK;break);
		ret = PE_NRD_SetTnrDetailCtrl(param);
		PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
	}while (0);
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get temporal noise reduction detail parameter
 * - use input struct LX_PE_NRD_TNR5_DETAIL_T for H15
 * - use input struct LX_PE_NRD_TNR4_DETAIL_T for M14BX
 * - use input struct LX_PE_NRD_TNR2_DETAIL_T for M14AXBX
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetTnrDetailParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = PE_NRD_GetTnrDetailCtrl(param);
	}
	else if (PE_KDRV_VER_M17)
	{
		ret = PE_KWRAP_IOCTL(LX_PE_NRD_TNR6_DETAIL_T, param, GET, NRD);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}


/**
 * set temporal noise reduction common by specific value
 *	- input data : see PE_KWRAP_NRD_TYPE
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetTnr2ndCmnCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = KWRAP_PE_SetTnr2ndCmnBspDB(param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set temporal noise reduction common parameter
 * - use input struct LX_PE_NRD_TNR5_CMN_T for H15
 * - use input struct LX_PE_NRD_TNR4_CMN_T for M14BX
 * - use input struct LX_PE_NRD_TNR3_CMN_T for H14
 * - use input struct LX_PE_NRD_TNR2_CMN_T for M14AX, H13BX
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetTnr2ndCmnParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(NRD);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	do {
		LX_PE_NRD_TNR2ND_CMN_T *pp = (LX_PE_NRD_TNR2ND_CMN_T *)param;
		CHECK_KNULL(ret, param);
		ret = KWRAP_PE_CheckTnr2ndCmnParam(pp);
		PE_CHECK_CODE(ret!=RET_OK, break, \
		"[%s,%d]KWRAP_PE_CheckTnr2ndCmnParam.\n", __F__, __L__);
		PE_CHECK_ACTION(pp->win_id>LX_PE_WIN_ALL, ret=RET_OK;break);
		ret = PE_NRD_SetTnr2ndCmnCtrl(param);
		PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
	}while (0);
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get temporal noise reduction common parameter
 * - use input struct LX_PE_NRD_TNR5_CMN_T for H15
 * - use input struct LX_PE_NRD_TNR4_CMN_T for M14BX
 * - use input struct LX_PE_NRD_TNR3_CMN_T for H14
 * - use input struct LX_PE_NRD_TNR2_CMN_T for M14AX, H13BX
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetTnr2ndCmnParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = PE_NRD_GetTnr2ndCmnCtrl(param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}

/**
 * set temporal noise reduction detail by specific value
 *	- input data : see PE_KWRAP_NRD_FMT_TYPE
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetTnr2ndDetailCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = KWRAP_PE_SetTnr2ndDetailBspDB(param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set temporal noise reduction detail parameter
 * - use input struct LX_PE_NRD_TNR5_DETAIL_T for H15
 * - use input struct LX_PE_NRD_TNR4_DETAIL_T for M14BX
 * - use input struct LX_PE_NRD_TNR2_DETAIL_T for M14AXBX
 * - use input struct LX_PE_NRD_TNR1_DETAIL_T for L9BX
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetTnr2ndDetailParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(NRD);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	do {
		LX_PE_NRD_TNR2ND_DETAIL_T *pp = (LX_PE_NRD_TNR2ND_DETAIL_T *)param;
		CHECK_KNULL(ret, param);
		ret = KWRAP_PE_CheckTnr2ndDetailParam(pp);
		PE_CHECK_CODE(ret!=RET_OK, break, \
		"[%s,%d]KWRAP_PE_CheckTnr2ndDetailParam.\n", __F__, __L__);
		PE_CHECK_ACTION(pp->win_id>LX_PE_WIN_ALL, ret=RET_OK;break);
		ret = PE_NRD_SetTnr2ndDetailCtrl(param);
		PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
	}while (0);
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get temporal noise reduction detail parameter
 * - use input struct LX_PE_NRD_TNR5_DETAIL_T for H15
 * - use input struct LX_PE_NRD_TNR4_DETAIL_T for M14BX
 * - use input struct LX_PE_NRD_TNR2_DETAIL_T for M14AXBX
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetTnr2ndDetailParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = PE_NRD_GetTnr2ndDetailCtrl(param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set digital noise reduction sqm common parameter by specific value
 *	- input data : see PE_KADP_NRD_TYPE
 *
 * @param   *param [in] PE_KADP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDnrSqmCmnCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_O20 || PE_KWRAP_VER_M19)
	{
		ret = KWRAP_PE_SetDnrSqmCmnBspDB(param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}

/**
 * set digital noise reduction common parameter
 * - use input struct LX_PE_NRD_DNR_SQM1_CMN_T for O18
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDnrSqmCmnParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(NRD);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	do {
		LX_PE_NRD_DNR_SQM_CMN_T *pp = (LX_PE_NRD_DNR_SQM_CMN_T *)param;
		CHECK_KNULL(ret, param);
		ret = KWRAP_PE_CheckDnrSqmCmnParam(pp);
		PE_CHECK_CODE(ret!=RET_OK, break, \
		"[%s,%d]check_dnr_cmn.\n", __F__, __L__);
		PE_CHECK_ACTION(pp->win_id>LX_PE_WIN_ALL, ret=RET_OK;break);
		ret = PE_NRD_SetDnrSqmCmnCtrl(param);
		PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
	}while (0);
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set temporal noise reduction sqm common parameter by specific value
 *	- input data : see PE_KADP_NRD_TYPE
 *
 * @param   *param [in] PE_KADP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetTnrSqmCmnCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KWRAP_VER_M19)
	{
		ret = KWRAP_PE_SetTnrSqmCmnBspDB(param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}

/**
 * set digital noise reduction common parameter
 * - use input struct LX_PE_NRD_DNR_SQM1_CMN_T for O18
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetTnrSqmCmnParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif
	__attribute__((unused)) UINT8 *pd;
	PE_CHECK_KWRAP_FUNC_ON(NRD);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	do {
		LX_PE_NRD_TNR_SQM_CMN_T *pp = (LX_PE_NRD_TNR_SQM_CMN_T *)param;
		CHECK_KNULL(ret, param);
		ret = KWRAP_PE_CheckTnrSqmCmnParam(pp);
		PE_CHECK_CODE(ret!=RET_OK, break, \
		"[%s,%d]check_dnr_cmn.\n", __F__, __L__);
		PE_CHECK_ACTION(pp->win_id>LX_PE_WIN_ALL, ret=RET_OK;break);
		ret = PE_NRD_SetTnrSqmCmnCtrl(param);
		PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
	}while (0);
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set digital noise reduction common parameter
 * - use input struct LX_PE_NRD_DNR_SQM1_CMN_T for O18
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetTnr2ndSqmCmnParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif
	__attribute__((unused)) UINT8 *pd;
	PE_CHECK_KWRAP_FUNC_ON(NRD);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	do {
		LX_PE_NRD_TNR2ND_SQM_CMN_T *pp = (LX_PE_NRD_TNR2ND_SQM_CMN_T *)param;
		CHECK_KNULL(ret, param);
		ret = KWRAP_PE_CheckTnr2ndSqmCmnParam(pp);
		PE_CHECK_CODE(ret!=RET_OK, break, \
		"[%s,%d]check_dnr_cmn.\n", __F__, __L__);
		PE_CHECK_ACTION(pp->win_id>LX_PE_WIN_ALL, ret=RET_OK;break);
		ret = PE_NRD_SetTnr2ndSqmCmnCtrl(param);
		PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
	}while (0);
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set digital noise reduction common parameter
 * - use input struct LX_PE_NRD_DNR_SQM1_CMN_T for O18
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDnrDcntSqmCmnParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif
	__attribute__((unused)) UINT8 *pd;
	PE_CHECK_KWRAP_FUNC_ON(NRD);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20)
	{
		LX_PE_NRD_DCNT_SQM_CMN_T *pp = (LX_PE_NRD_DCNT_SQM_CMN_T *)param;
		do {
			CHECK_KNULL(ret, param);
			ret = KWRAP_PE_CheckDnrDcntSqmCmnParam(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]check_dnr_cmn.\n", __F__, __L__);
			PE_CHECK_ACTION(pp->win_id>LX_PE_WIN_ALL, ret=RET_OK;break);
			ret = PE_NRD_SetDnrDcntSqmCmnCtrl(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_NRD_DCNT_SQM_CMN_T *pp = (LX_PE_NRD_DCNT_SQM_CMN_T *)param;
		do {
			CHECK_KNULL(ret, param);
			ret = KWRAP_PE_CheckDnrDcntSqmCmnParam(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]check_dnr_cmn.\n", __F__, __L__);
			PE_CHECK_ACTION(pp->win_id>LX_PE_WIN_ALL, ret=RET_OK;break);
			ret = PE_KWRAP_IOCTL(LX_PE_NRD_DCNT_SQM_CMN_T, param, SET, NRD);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set digital noise reduction common parameter
 * - use input struct LX_PE_NRD_DNR_SQM1_CMN_T for O18
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetLedDcntSqmCmnParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif
	__attribute__((unused)) UINT8 *pd;
	PE_CHECK_KWRAP_FUNC_ON(NRD);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20)
	{
		LX_PE_LED_DCNT_SQM_CMN_T *pp = (LX_PE_LED_DCNT_SQM_CMN_T *)param;
		do {
			CHECK_KNULL(ret, param);
			ret = KWRAP_PE_CheckLedDcntSqmCmnParam(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]check_dnr_cmn.\n", __F__, __L__);
			PE_CHECK_ACTION(pp->win_id>LX_PE_WIN_ALL, ret=RET_OK;break);
			ret = PE_NRD_SetLedDcntSqmCmnCtrl(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}

/**
 * set temporal noise reduction common parameter
 * - use input struct LX_PE_NRD_TNR_ALL_CMN_T for F20
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetTnrCmnAllParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(NRD);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O20 || PE_KDRV_VER_E60)
	{
		// LX_PE_NRD_TNR_CMN_T *pp = (LX_PE_NRD_TNR_CMN_T *)param;
		do {
			CHECK_KNULL(ret, param);
			ret = PE_NRD_SetTnrCmnAllCtrl(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}

/**
 * set digital noise reduction common parameter
 * - use input struct LX_PE_NRD_DNR_ALL_CMN_T for F20
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDnrCmnAllParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(NRD);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O20 || PE_KDRV_VER_E60)
	{
		// LX_PE_NRD_DNR_CMN_T *pp = (LX_PE_NRD_DNR_CMN_T *)param;
		do {
			CHECK_KNULL(ret, param);
			ret = PE_NRD_SetDnrCmnAllCtrl(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}

/**
 * set decontour common parameter
 * - use input struct LX_PE_NRD_DCNT_ALL_CMN_T for F20
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDnrDcntCmnAllParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(NRD);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O20 || PE_KDRV_VER_E60)
	{
		// LX_PE_NRD_DCNT_CMN_T *pp = (LX_PE_NRD_DCNT_CMN_T *)param;
		do {
			CHECK_KNULL(ret, param);
			ret = PE_NRD_SetDnrDcntCmnAllCtrl(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}



