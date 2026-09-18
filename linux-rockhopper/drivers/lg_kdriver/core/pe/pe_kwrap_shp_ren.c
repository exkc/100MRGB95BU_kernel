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

/** @file pe_kwrap_shp_ren.c
 *
 *	application interface functions for picture enhancement.
 *	These include following functions.
 *	- sharpness control (resolution enhancement)
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

#include "pe_shp.h"

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

/*----------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------*/
extern UINT32 g_pe_kwrap_ver_mask;

/*----------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------*/
/* res cmn */

const LX_PE_SHP_RE4_CMN_T g_pe_kwrap_p_re4_cmn[PE_KWRAP_SHP_STEP] = {\
	{0,\
	 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},\
	 {0x00,0x00,0x00},\
	 {0x06,0x00,0x00,0x00},\
	 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
	}, \
	{0,\
	 {0x20,0x20,0x00,0x08,0x0f,0x00,0x08,0x0f,0x10,0x10,0x00,0x02,0x0f},\
	 {0x50,0x10,0x08}, \
	 {0x06,0x10,0x02,0x02},\
	 {0x08,0x08,0x80,0x3c,0x10,0x12,0x08,0x10,0x12,0x08}
	}, \
	{0,\
	 {0x2f,0x2f,0x00,0x08,0x0f,0x00,0x08,0x0f,0x1f,0x1f,0x00,0x02,0x0f},\
	 {0x7f,0x1f,0x0f}, \
	 {0x06,0x29,0x06,0x06},\
	 {0x1e,0x0e,0x80,0x3c,0x10,0x12,0x08,0x10,0x12,0x08}
	}, \
	{0,\
	 {0x34,0x34,0x00,0x08,0x0f,0x00,0x08,0x0f,0x24,0x24,0x00,0x02,0x0f},\
	 {0x80,0x24,0x14}, \
	 {0x06,0x2d,0x10,0x0c},\
	 {0x24,0x14,0x80,0x3c,0x10,0x12,0x08,0x10,0x12,0x08}
	}, \
	{0,\
	 {0x38,0x38,0x00,0x08,0x0f,0x00,0x08,0x0f,0x28,0x28,0x00,0x02,0x0f},\
	 {0x80,0x28,0x18}, \
	 {0x06,0x32,0x0f,0x0f},\
	 {0x28,0x18,0x80,0x3c,0x10,0x12,0x08,0x10,0x12,0x08}
	}
};
const LX_PE_SHP_RE5_CMN_T g_pe_kwrap_p_re5_cmn[PE_KWRAP_SHP_STEP] = {\
	{0,\
	 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},\
	 {0x00,0x00,0x00},\
	 {0x00}
	}, \
	{0,\
	 {0x04,0x10,0x10,0x00,0x04,0x02,0x02,0x01,0x00,0x04,0x40,0x00,0x04,0x01},\
	 {0x30,0x04,0x01}, \
	 {0x08}
	}, \
	{0,\
	 {0x0f,0x1f,0x1f,0x00,0x04,0x02,0x02,0x01,0x00,0x0f,0x0f,0x00,0x04,0x01},\
	 {0x7f,0x07,0x01}, \
	 {0x13}
	}, \
	{0,\
	 {0x10,0x20,0x20,0x00,0x04,0x02,0x02,0x01,0x00,0x10,0x10,0x00,0x04,0x01},\
	 {0x90,0x18,0x02}, \
	 {0x24}
	}, \
	{0,\
	 {0x30,0x40,0x40,0x00,0x04,0x02,0x02,0x01,0x00,0x30,0x30,0x00,0x04,0x01},\
	 {0xa0,0x28,0x03}, \
	 {0x34}
	}
};
const LX_PE_SHP_RE6_CMN_T g_pe_kwrap_p_re6_cmn[PE_KWRAP_SHP_STEP] = {\
	{0,\
	 {0x0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
		0x00,0x00,0x00,0x00,0x00},\
	 {0x00,0x00,0x00},\
	 {0x30,0x3,0x30,0x00}
	}, \
	{0,\
	 {0x10,0x20,0x10,0x10,0x20,0x10,0x00,0x00,0x00,0x00,\
	  0x10,0x08,0x04,0x08,0x40,},\
	 {0x04,0x01,0x01}, \
	 {0x14,0x01,0x2A,0x05}
	}, \
	{0,\
	 {0x70,0xB0,0x40,0x30,0x60,0x30,0x00,0x04,0x08,0xE0,\
	  0x50,0x1C,0x10,0x1C,0xC0,},\
	 {0x0C,0x03,0x03}, \
	 {0x14,0x01,0x2A,0x05}
	}, \
	{0,\
	 {0x80,0xC0,0x50,0x40,0x70,0x40,0x00,0x04,0x08,0xE0,\
	  0x60,0x20,0x14,0x20,0xFF,},\
	 {0x10,0x04,0x04}, \
	 {0x14,0x01,0x2A,0x05}
	}, \
	{0,\
	 {0x88,0xC8,0x58,0x48,0x78,0x48,0x00,0x04,0x08,0xE0,\
	  0x60,0x20,0x14,0x20,0xFF,},\
	 {0x18,0x08,0x08}, \
	 {0x14,0x01,0x2A,0x05}
	}
};

const LX_PE_SHP_RE6_CMN_T g_pe_kwrap_p_re6_cmn2[PE_KWRAP_SHP_STEP] = {\
	{0,\
	 {0x0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
		0x00,0x00,0x00,0x00,0x00},\
	 {0x00,0x00,0x00},\
	 {0x30,0x30,0x30,0x00}
	}, \
	{0,\
	 {0x10,0x20,0x10,0x10,0x20,0x10,0x00,0x00,0x00,0x00,\
	  0x10,0x08,0x04,0x08,0x40,},\
	 {0x04,0x01,0x01}, \
	 {0x14,0x2A,0x2A,0x05}
	}, \
	{0,\
	 {0x70,0xB0,0x40,0x30,0x60,0x30,0x00,0x04,0x08,0xE0,\
	  0x50,0x1C,0x10,0x1C,0xC0,},\
	 {0x0C,0x03,0x03}, \
	 {0x14,0x2A,0x2A,0x05}
	}, \
	{0,\
	 {0x80,0xC0,0x50,0x40,0x70,0x40,0x00,0x04,0x08,0xE0,\
	  0x60,0x20,0x14,0x20,0xFF,},\
	 {0x10,0x04,0x04}, \
	 {0x14,0x2A,0x2A,0x05}
	}, \
	{0,\
	 {0x88,0xC8,0x58,0x48,0x78,0x48,0x00,0x04,0x08,0xE0,\
	  0x60,0x20,0x14,0x20,0xFF,},\
	 {0x18,0x08,0x08}, \
	 {0x14,0x2A,0x2A,0x05}
	}
};
const LX_PE_SHP_RE4_HOR_T g_pe_kwrap_p_re4_hor[PE_KWRAP_SHP_STEP] = {\
	{0,\
	{0x00,0x07,0x00,0x00,0x00,0x00,0x00}}, \
	{0,\
	{0x03,0x07,0x03,0x03,0x10,0x04,0x10}}, \
	{0,\
	{0x07,0x07,0x07,0x07,0x1f,0x0f,0x3f}}, \
	{0,\
	{0x08,0x07,0x08,0x08,0x20,0x10,0x40}}, \
	{0,\
	{0x28,0x07,0x28,0x28,0x40,0x30,0x60}}
};

const LX_PE_SHP_RE5_HOR_T g_pe_kwrap_p_re5_hor[PE_KWRAP_SHP_STEP] = {\
	{0,\
	{0x00,0x00,0x00,0x00,0x00,0x00}}, \
	{0,\
	{0x00,0x01,0x01,0x10,0x02,0x08}}, \
	{0,\
	{0x00,0x04,0x04,0x1C,0x0C,0x3f}}, \
	{0,\
	{0x00,0x04,0x04,0x20,0x10,0x40}}, \
	{0,\
	{0x00,0x08,0x08,0x28,0x18,0x60}}
};

/* res ver */
const LX_PE_SHP_RE3_VER_T g_pe_kwrap_p_re3_ver[PE_KWRAP_SHP_STEP] = {\
	{0, {0x00,0x00,0x00,0x00,0x00,0x00}}, \
	{0, {0x00,0x08,0x08,0x00,0x10,0x20}}, \
	{0, {0x00,0x0f,0x0f,0x00,0x1f,0x3f}}, \
	{0, {0x00,0x14,0x14,0x00,0x24,0x40}}, \
	{0, {0x00,0x18,0x18,0x00,0x28,0x40}}
};
const LX_PE_SHP_RE4_VER_T g_pe_kwrap_p_re4_ver[PE_KWRAP_SHP_STEP] = {\
	{0, {0x00,0x00}}, \
	{0, {0x10,0x80}}, \
	{0, {0x18,0xa0}}, \
	{0, {0x20,0xff}}, \
	{0, {0x40,0xff}}
};
const LX_PE_SHP_RE5_VER_T g_pe_kwrap_p_re5_ver[PE_KWRAP_SHP_STEP] = {\
	{0, {0x00,0x00}}, \
	{0, {0x10,0x80}}, \
	{0, {0x18,0xa0}}, \
	{0, {0x20,0xff}}, \
	{0, {0x40,0xff}}
};

 /* edge enhance */
const LX_PE_SHP_EE3_T g_pe_kwrap_p_ee3[PE_KWRAP_SHP_STEP] = {\
   {0, { 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0}}, \
   {0, {0x04, 0x04, 0x04, 0x04, 0x03, 0x03, 0x03, 0x03}}, \
   {0, {0x0b, 0x0b, 0x0f, 0x0f, 0x07, 0x07, 0x07, 0x07}}, \
   {0, {0x0c, 0x0c, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08}}, \
   {0, {0x16, 0x16, 0x16, 0x16, 0x24, 0x24, 0x24, 0x24}},\
};

const LX_PE_SHP_EE4_T g_pe_kwrap_p_ee4[PE_KWRAP_SHP_STEP] = {\
	{0, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
	0x00,0x00,0x00,0x00}}, \
	{0, {0x10,0x10,0x02,0x01,0x02,0x02,0x04,0x02,0x10,0x02,\
	0x00,0x00,0x00,0x00}}, \
	{0, {0x1c,0x1c,0x06,0x03,0x0c,0x0c,0x14,0x06,0x1c,0x10,\
	0x00,0x00,0x00,0x00}}, \
	{0, {0x20,0x20,0x08,0x04,0x10,0x10,0x18,0x08,0x20,0x10,\
	0x00,0x00,0x00,0x00}}, \
	{0, {0x28,0x28,0x10,0x08,0x18,0x18,0x20,0x10,0x28,0x18,\
	0x00,0x00,0x00,0x00}}, \
};

/* detail enhance */
const LX_PE_SHP_DE3_T g_pe_kwrap_p_de3[PE_KWRAP_SHP_STEP] = {\
	{0, { 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0}}, \
	{0, {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10}}, \
	{0, {0x27, 0x27, 0x1f, 0x1f, 0x07, 0x07, 0x07, 0x07}}, \
	{0, {0x30, 0x30, 0x20, 0x20, 0x08, 0x08, 0x08, 0x08}}, \
	{0, {0x38, 0x38, 0x24, 0x24, 0x16, 0x16, 0x16, 0x16}}
};

/* detail enhance */
const LX_PE_SHP_DE4_T g_pe_kwrap_p_de4[PE_KWRAP_SHP_STEP] = {\
	{0, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
	0x00,0x00,0x00,0x00}}, \
	{0, {0x10,0x10,0x02,0x02,0x02,0x02,0x10,0x02,0x10,0x10,\
	0x10,0x10,0x10,0x10}}, \
	{0, {0x1C,0x1C,0x0C,0x0C,0x0C,0x0C,0x2C,0x0C,0x1C,0x1C,\
	0x38,0x1C,0x1C,0x1C}}, \
	{0, {0x20,0x20,0x10,0x10,0x10,0x10,0x30,0x10,0x20,0x20,\
	0x40,0x20,0x20,0x20}}, \
	{0, {0x28,0x28,0x18,0x18,0x18,0x18,0x38,0x18,0x28,0x28,\
	0x48,0x28,0x28,0x28}}, \
};


const LX_PE_SHP_RE6_MISC_T g_pe_kwrap_p_re6_misc[PE_KWRAP_SHP_FMT_NUM] = {\
	/* PE_KWRAP_SHP_FMT_SD */{0, \
	{/*cmn*/
	 0x01, 0x10, 0x20, 0x50, 0xc0, 0x00, 0x10, 0x40, 0xff, 0x01,\
	 0x01, 0x70, 0x40, 0x00, 0x01, 0x20, 0x01, 0x00, 0x18, 0x10, \
	 0x01, 0x00, 0x01, 0x00, 0x00, 0x40, 0x08, 0x14, 0x20, 0x08},\
	 {/*map*/
	 0x01, 0x0e, 0x30, 0x01, 0x01, 0x03, 0x00, 0x20, 0x30, 0x18,\
	 0x10, 0x30, 0x00, 0x50, 0x02, 0x02, 0x02, 0x03, 0x01, 0x08,\
	 0x00, 0x08, 0x00, 0xc0, 0xff, 0x10, 0x00, 0x40, 0xff, 0x08,\
	 0x08, 0x50, 0x80, 0x01, 0x01, 0x10, 0x08, 0x10, 0x00, 0x50,\
	 0xff, 0x00, 0x20, 0x80, 0xff, 0x00, 0x20, 0x48, 0x50},\
	 {/*balance*/
	 0x01, 0x00, 0x04, 0x30, 0x04, 0x40, 0xff, 0x01, 0x00, 0x02,\
	 0x40, 0x04, 0x60, 0xff, 0x00, 0x01, 0x10, 0x30, 0xff, 0x10, \
	 0x20, 0x60, 0x50, 0xff, 0xff, 0x18, 0x38, 0x58, 0xc0, 0xff,\
	 0xff, 0xff, 0x18, 0x38, 0x58, 0xc0, 0xff, 0xff, 0xff, 0x18,\
	 0x38, 0x58, 0xc0, 0x20, 0x60, 0xc0, 0x18, 0x38, 0x58, 0xc0,\
	 0x20, 0x60, 0xc0},\
	 {/*ti*/
	 0x00, 0x01, 0x02, 0x02, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00,\
	 0x02, 0x02},\
	 {/*simple_snr*/
	 0x00, 0x00, 0x00},\
	 { /*cti*/
	 0x00,  0x00,  0x00, 0x00, 0x01, 0x21, 0x02},\
	 {/*motion*/
	 0x01, 0x00, 0x40, 0x6e, 0xff, 0xff, 0xc0, 0x80, 0x40},\
	 {/*chroma*/
	 0x00, 0x00, 0x00, 0x00, 0x00},\
	},\
	/* PE_KWRAP_SHP_FMT_HD */{0, \
	{/*cmn*/
	 0x01, 0x10, 0x20, 0x50, 0xc0, 0x00, 0x10, 0x40, 0xff, 0x01,\
	 0x01, 0x70, 0x40, 0x00, 0x01, 0x20, 0x01, 0x00, 0x18, 0x10, \
	 0x01, 0x00, 0x01, 0x00, 0x00, 0x40, 0x08, 0x14, 0x20, 0x08},\
	 {/*map*/
	 0x01, 0x0e, 0x30, 0x01, 0x01, 0x03, 0x00, 0x20, 0x30, 0x18,\
	 0x10, 0x30, 0x00, 0x50, 0x02, 0x02, 0x02, 0x03, 0x01, 0x08,\
	 0x00, 0x08, 0x00, 0xc0, 0xff, 0x10, 0x00, 0x40, 0xff, 0x08,\
	 0x08, 0x50, 0x80, 0x01, 0x01, 0x10, 0x08, 0x10, 0x00, 0x50,\
	 0xff, 0x00, 0x20, 0x80, 0xff, 0x00, 0x20, 0x48, 0x50},\
	 {/*balance*/
	 0x01, 0x00, 0x04, 0x30, 0x04, 0x40, 0xff, 0x01, 0x00, 0x02,\
	 0x40, 0x04, 0x60, 0xff, 0x00, 0x01, 0x10, 0x30, 0xff, 0x10, \
	 0x20, 0x60, 0x50, 0xff, 0xff, 0x18, 0x38, 0x58, 0xc0, 0xff,\
	 0xff, 0xff, 0x18, 0x38, 0x58, 0xc0, 0xff, 0xff, 0xff, 0x18,\
	 0x38, 0x58, 0xc0, 0x20, 0x60, 0xc0, 0x18, 0x38, 0x58, 0xc0,\
	 0x20, 0x60, 0xc0},\
	 {/*ti*/
	 0x00, 0x01, 0x02, 0x02, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00,\
	 0x02, 0x02},\
	 {/*simple_snr*/
	 0x00, 0x00, 0x00},\
	 { /*cti*/
	 0x00,  0x00,  0x00, 0x00, 0x01, 0x21, 0x02},\
	 {/*motion*/
	 0x01, 0x00, 0x40, 0x6e, 0xff, 0xff, 0xc0, 0x80, 0x40},\
	 {/*chroma*/
	 0x00, 0x00, 0x00, 0x00, 0x00},\
	}
};
const LX_PE_SHP_RE7_MISC_T g_pe_kwrap_p_re7_misc[PE_KWRAP_SHP_FMT_NUM] = {\
	/* PE_KWRAP_SHP_FMT_SD */{0, \
	{/*shp_cmn_vsd*/
	 0x01,0x01,0x01,0x01,0x20,0x20,0x10,0x10,0x01,0x20,\
	 0xC0,0xA0,0x01,0x01,0x03,0x01,0x01,0x03,0x01,0x01,\
	 0x03,0x00,0x0A},\
	 {/*shp_djg_vsd*/
	 0x01,0x01,0x01,0x10,0x80,0x01,0x00,0x80},\
	 {/*shp_map_cmn_vsd*/
	 0x00,0x00,0x05,0x20,0x00,0x40,0x00,0x00,0xFF,0x05,\
	 0x08,0x0C,0x40,0x20,0x00,0x00,0x2C,0x3E,0x0C,0x06},\
	 {/*shp_balance_vsd*/
	 0x01,0x00,0x04,0x40,0x80,0x01,0x00,0x04,0x60,0x80,\
	 0x00,0x01,0x00,0x10,0x14,0xC0,0xFF,0xFF,0x20,0x60,\
	 0xC0,0x20,0x60,0xC0,0x20,0x60,0xC0,0x20,0x60,0xC0},\
	 {/*shp_ti_cmn_vsd*/
	 0x01,0x01,0x02,0x02,0x01,0x00,0x02,0x02,0x01,0x00,\
	 0x02,0x02},\
	 {/*shp_simple_snr_vsd*/
	 0x01, 0x00, 0x01},\
	 { /*shp_cti_cmn_vsd*/
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06},\
	 {/*shp_motion_vsd*/
	 0x00,0xFF,0x80,0x40,0x00,0xFF,0x80,0x40,0x00},\
	 {/*shp_chroma_vsd*/
	 0x01,0x00,0x01,0xFF,0x00},\
	},\
	/* PE_KWRAP_SHP_FMT_HD */{0, \
	{/*shp_cmn_vsd*/
	 0x01,0x01,0x01,0x01,0x20,0x20,0x10,0x10,0x01,0x20,\
	 0xC0,0xC0,0x01,0x01,0x03,0x01,0x01,0x03,0x01,0x00,\
	 0x03,0x00,0x0A},\
	 {/*shp_djg_vsd*/
	 0x01,0x00,0x00,0x18,0x10,0x01,0x01,0x40},\
	 {/*shp_map_cmn_vsd*/
	 0x01,0x01,0x10,0x30,0x00,0x50,0x00,0x04,0xFF,0x10,\
	 0x08,0x10,0x40,0x20,0x01,0x01,0x2C,0x3E,0x04,0x01},\
	 {/*shp_balance_vsd*/
	 0x01,0x00,0x04,0x40,0xFF,0x01,0x00,0x04,0x02,0x04,\
	 0x01,0x01,0x01,0x08,0x10,0xC0,0xFF,0xF6,0x20,0x60,\
	 0xC0,0x20,0x60,0xC0,0x20,0x60,0xC0,0x20,0x60,0xC0},\
	 {/*shp_ti_cmn_vsd*/
	 0x00,0x01,0x02,0x02,0x01,0x00,0x02,0x02,0x01,0x01,\
	 0x00,0x00},\
	 {/*shp_simple_snr_vsd*/
	 0x01, 0x00, 0x01},\
	 { /*shp_cti_cmn_vsd*/
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06},\
	 {/*shp_motion_vsd*/
	 0x01,0x90,0x70,0x60,0x40,0x90,0x70,0x60,0x40},\
	 {/*shp_chroma_vsd*/
	 0x01,0x00,0x01,0xFF,0x00},\
	}
};



const LX_PE_SHP_RE_PSEUDO_CMN_T g_pe_kwrap_p_re_pseudo_cmn[PE_KWRAP_SHP_STEP] = {
	{ 0, { 0x00, 0x00, 0x00, 0x00 } },
	{ 0, { 0x10, 0x10, 0x10, 0x10 } },
	{ 0, { 0x20, 0x20, 0x20, 0x20 } },
	{ 0, { 0x40, 0x40, 0x40, 0x40 } },
	{ 0, { 0x7f, 0x7f, 0x7f, 0x7f } }
};

const LX_PE_SHP_RE_PSEUDO_HOR_T g_pe_kwrap_p_re_pseudo_hor[PE_KWRAP_SHP_STEP] = {
	{ 0, { 0x00, 0x00 } },
	{ 0, { 0x10, 0x10 } },
	{ 0, { 0x20, 0x20 } },
	{ 0, { 0x40, 0x40 } },
	{ 0, { 0xff, 0xff } }
};

const LX_PE_SHP_RE_PSEUDO_VER_T g_pe_kwrap_p_re_pseudo_ver[PE_KWRAP_SHP_STEP] = {
	{ 0, { 0x00, 0x00 } },
	{ 0, { 0x10, 0x00 } },
	{ 0, { 0x18, 0x00 } },
	{ 0, { 0x40, 0x00 } },
	{ 0, { 0xff, 0x00 } }
};

const LX_PE_SHP_PSEUDO_EE_T g_pe_kwrap_p_pseudo_ee[] = {
	{ 0, { 0x00, 0x00, 0x00, 0x00 } },
	{ 0, { 0x18, 0x18, 0x20, 0x20 } }
};

const LX_PE_SHP_PSEUDO_DE_T g_pe_kwrap_p_pseudo_de[PE_KWRAP_SHP_STEP] = {
	{ 0, { 0x00, 0x00, 0x00, 0x00 } },
	{ 0, { 0x10, 0x10, 0x00, 0x00 } },
	{ 0, { 0x48, 0x1b, 0x00, 0x00 } },
	{ 0, { 0x40, 0x40, 0x40, 0x40 } },
	{ 0, { 0x7f, 0x7f, 0x7f, 0x7f } }
};

const LX_PE_SHP_RE_EASY_CMN_T g_pe_kwrap_p_re_easy_cmn[PE_KWRAP_SHP_STEP] = {
	{ 0, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{ 0, {0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10}},
	{ 0, {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18}},
	{ 0, {0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20}},
	{ 0, {0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30}}
};

const LX_PE_SHP_RE_EASY_DE_T g_pe_kwrap_p_re_easy_de[PE_KWRAP_SHP_STEP] = {
	{ 0, {0x00,0x00,0x00,0x00}},
	{ 0, {0x04,0x04,0x10,0x10}},
	{ 0, {0x17,0x17,0x1f,0x1f}},
	{ 0, {0x18,0x18,0x20,0x20}},
	{ 0, {0x20,0x20,0x28,0x28}}
};

/*----------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------*/
int KWRAP_PE_SetObcStereo(void *param);

/*----------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------*/

/*============================================================================
	Implementation Group
============================================================================*/

#define _KWRAP_PE_SHP_
/**
 * get resolution enhance common default settings
 *	- input data : 0~50
 *
 * @param   *param [in/out] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetRenCmnDefaultSettings(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	LX_PE_SHP_RE_EASY_CMN_T ctrl;
	const LX_PE_SHP_RE_EASY_CMN_T *p_data_tbl=NULL;
	UINT8 in=0, out_tbl[PE_KWRAP_SHP_STEP];
	UINT8 in_tbl[PE_KWRAP_SHP_STEP]={0, 10, 25, 30, 50};
	do {
		CHECK_KNULL(ret, param);
		CHECK_KNULL(ret, param->st_data);
		in = (param->data>50)? 50:(UINT8)param->data;
		p_data_tbl = g_pe_kwrap_p_re_easy_cmn;
		PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_vsd[0]);
		PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_vsd[1]);
		PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_vsd[2]);
		PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_vsd[3]);
		PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_vsd[4]);
		PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_vsd[5]);
		PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_vsd[6]);
		PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_vsd[7]);
		PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_vsd[8]);
		PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_vsd[9]);
		PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_vsd[10]);
		PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_vsd[11]);
		PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_vsd[12]);
		PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_vsd[13]);
		PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_vsd[14]);
		PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_vsd[15]);
		PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_vsd[16]);
		PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_vsd[17]);
		PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_vsd[18]);
		PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_vsd[19]);
		memcpy(param->st_data, &ctrl, sizeof(LX_PE_SHP_RE_EASY_CMN_T));
	}while (0);
	return ret;
}
/**
 * set resolution enhance common control by specific value
 *	- input data : 0~50
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetRenCmnCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;

	LX_PE_SHP_RE_EASY_CMN_T ctrl;
	ret = KWRAP_PE_SetDefaultParam(param, \
		PE_KWRAP_DFLT_PARAM_REN_CMN, (void *)&ctrl, __F__, __L__);

	return ret;
}
/**
 * set resolution enhance common parameter
 * - use input struct LX_PE_SHP_RE2_CMN_T for H15, M14BX
 * - use input struct LX_PE_SHP_RE1_CMN_T for H13AX
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetRenCmnParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif

	PE_CHECK_KWRAP_FUNC_ON(SHP);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();

	if(PE_KDRV_VER_E60 || PE_KDRV_VER_O20)
	{
		LX_PE_SHP_RE1_CMN_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_RE1_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_RE1_CMN_T *)param;
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_RE1_CMN_T, SHP);
			#endif
			ret = PE_SHP_SetReCmnCtrl(pp);
			PE_CHECK_CODE(ret != RET_OK, break, \
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
 * get resolution enhance common parameter
 * - use input struct LX_PE_SHP_RE2_CMN_T for H15, M14BX
 * - use input struct LX_PE_SHP_RE1_CMN_T for H13AX
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetRenCmnParam(void *param)
{
	int ret = RET_OK;

	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();

	if (PE_KDRV_VER_M19)
	{
		ret = PE_SHP_GetReCmnCtrl((LX_PE_SHP_RE_EASY_CMN_T *)param);
	}
	else if (PE_KDRV_VER_O18)
	{
		ret = PE_SHP_GetReCmnCtrl((LX_PE_SHP_RE6_CMN_T *)param);
	}
	else if (PE_KDRV_VER_M17)
	{
		ret = PE_SHP_GetReCmnCtrl((LX_PE_SHP_RE5_CMN_T *)param);
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
 * get resolution enhance horizontal default settings
 *	- input data : 0~50
 *
 * @param   *param [in/out] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetRenHorDefaultSettings(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;

	if (PE_KDRV_VER_E60 ||PE_KDRV_VER_O20 ||PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_RE5_HOR_T ctrl;
		const LX_PE_SHP_RE5_HOR_T *p_data_tbl = NULL;
		UINT8 in = 0, out_tbl[PE_KWRAP_SHP_STEP];
		UINT8 in_tbl[PE_KWRAP_SHP_STEP] = {0, 10, 25, 30, 50};

		do {
			CHECK_KNULL(ret, param);
			CHECK_KNULL(ret, param->st_data);

			in = (param->data > 50) ? 50 : param->data;
			p_data_tbl = g_pe_kwrap_p_re5_hor;

			PE_KWRAP_DBG_PRINT(SHP, "set[%d] : in = %f\n", param->wid,	in);

			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_h_main_vsd[0]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_h_main_vsd[1]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_h_main_vsd[2]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_h_main_vsd[3]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_h_main_vsd[4]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_h_main_vsd[5]);

			memcpy(param->st_data, &ctrl, sizeof(ctrl));
		} while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}

/**
 * set resolution enhance horizontal by specific value
 *	- input data : 0~50
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetRenHorCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;

	if (PE_KDRV_VER_O20|| PE_KWRAP_VER_M19 || PE_KWRAP_VER_O18)
	{
		LX_PE_SHP_RE5_HOR_T ctrl;
		ret = KWRAP_PE_SetDefaultParam(param, \
			PE_KWRAP_DFLT_PARAM_REN_HOR, (void *)&ctrl, __F__, __L__);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set resolution enhance horizontal parameter
 * - use input struct LX_PE_SHP_RE2_HOR_T for H15, M14BX
 * - use input struct LX_PE_SHP_RE1_HOR_T for H13AX
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetRenHorParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif

	PE_CHECK_KWRAP_FUNC_ON(SHP);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();

	if (PE_KDRV_VER_O20|| PE_KWRAP_VER_M19 || PE_KWRAP_VER_O18)
	{
		LX_PE_SHP_RE5_HOR_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_RE5_HOR_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif

		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_RE5_HOR_T *)param;
			pd = pp->shp_ui_h_main_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_ui_h_main_vsd\n"\
			"shp_ui_h_main_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_RE5_HOR_T, SHP);
			#endif
			ret = PE_SHP_SetReHorCtrl(pp);
			PE_CHECK_CODE(ret != RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		} while (0);
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
 * get resolution enhance horizontal parameter
 * - use input struct LX_PE_SHP_RE2_HOR_T for H15, M14BX
 * - use input struct LX_PE_SHP_RE1_HOR_T for H13AX
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetRenHorParam(void *param)
{
	int ret = RET_OK;

	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();

	if (PE_KWRAP_VER_M19 || PE_KWRAP_VER_O18)
	{
		ret = PE_SHP_GetReHorCtrl((LX_PE_SHP_RE5_HOR_T *)param);
	}
	else if (PE_KDRV_VER_M17)
	{
		ret = PE_SHP_GetReHorCtrl((LX_PE_SHP_RE4_HOR_T *)param);
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
 * get resolution enhance vertical default settings
 *	- input data : 0~50
 *
 * @param   *param [in/out] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetRenVerDefaultSettings(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;

	if (PE_KDRV_VER_O20 || PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_RE5_VER_T ctrl;
		const LX_PE_SHP_RE5_VER_T *p_data_tbl = NULL;
		UINT8 in = 0, out_tbl[PE_KWRAP_SHP_STEP];
		UINT8 in_tbl[PE_KWRAP_SHP_STEP] = { 0, 10, 25, 30, 50 };

		do {
			CHECK_KNULL(ret, param);
			CHECK_KNULL(ret, param->st_data);
			in = (param->data > 50) ? 50 : param->data;
			PE_KWRAP_DBG_PRINT(SHP, "set[%d] : in = %f\n", param->wid,	in);

			p_data_tbl = g_pe_kwrap_p_re5_ver;
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_v_main_vsd[0]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_v_main_vsd[1]);
			memcpy(param->st_data, &ctrl, sizeof(ctrl));
		} while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set resolution enhance vertical by specific value
 *	- input data : 0~50
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetRenVerCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;

	if (PE_KDRV_VER_O20 || PE_KWRAP_VER_M19 || PE_KWRAP_VER_O18)
	{
		LX_PE_SHP_RE5_VER_T ctrl;
		ret = KWRAP_PE_SetDefaultParam(param, \
			PE_KWRAP_DFLT_PARAM_REN_VER, (void *)&ctrl, __F__, __L__);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}

	return ret;
}
/**
 * set resolution enhance vertical parameter
 * - use input struct LX_PE_SHP_RE2_VER_T for H15, M14BX
 * - use input struct LX_PE_SHP_RE1_VER_T for H13AX
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetRenVerParam(void *param)
{
	int ret = RET_OK;
#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
#endif

	PE_CHECK_KWRAP_FUNC_ON(SHP);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();

	if (PE_KDRV_VER_O20|| PE_KWRAP_VER_M19 || PE_KWRAP_VER_O18)
	{
		LX_PE_SHP_RE5_VER_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_RE5_VER_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_RE5_VER_T *)param;
			pd = pp->shp_ui_v_main_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_ui_v_main_vsd\n"
			"shp_ui_v_main_vsd    [00]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_RE5_VER_T, SHP);
			#endif
			ret = PE_SHP_SetReVerCtrl(pp);
			PE_CHECK_CODE(ret != RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		} while (0);
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
 * get resolution enhance vertical parameter
 * - use input struct LX_PE_SHP_RE2_VER_T for H15, M14BX
 * - use input struct LX_PE_SHP_RE1_VER_T for H13AX
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetRenVerParam(void *param)
{
	int ret = RET_OK;

	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();

	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = PE_SHP_GetReVerCtrl((LX_PE_SHP_RE5_VER_T *)param);
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
 * get resolution enhance misc default settings
 *	- input data : see PE_KWRAP_SHP_FMT_TYPE
 *
 * @param   *param [in/out] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetRenMiscDefaultSettings(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	UINT32 param_data = 0;
	if (PE_KWRAP_VER_M19 || PE_KWRAP_VER_O18)
	{
		const LX_PE_SHP_RE7_MISC_T *pp=NULL;
		do {
			const UINT8 *pd;
			CHECK_KNULL(ret, param);
			CHECK_KNULL(ret, param->st_data);
			param_data = (param->data<PE_KWRAP_SHP_FMT_NUM)? \
				param->data:PE_KWRAP_SHP_FMT_SD;
			pp = &(g_pe_kwrap_p_re7_misc[param_data]);
			memcpy(param->st_data, pp, sizeof(LX_PE_SHP_RE7_MISC_T));
			pd = pp->shp_cmn_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] : shp_cmn_vsd\n"\
			"shp_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_vsd    [20]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22]);

			pd = pp->shp_djg_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] : shp_djg_vsd\n"\
			"shp_djg_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

			pd = pp->shp_map_cmn_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] : shp_map_cmn_vsd\n"\
			"shp_map_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19]);

			pd = pp->shp_balance_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] : shp_balance_vsd\n"\
			"shp_balance_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_vsd    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);

			pd = pp->shp_ti_cmn_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] : shp_ti_cmn_vsd\n"\
			"shp_ti_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_vsd    [10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);

			pd = pp->shp_simple_snr_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] : shp_simple_snr_vsd\n"\
			"shp_simple_snr_vsd    [00]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2]);

			pd = pp->shp_cti_cmn_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] : shp_cti_cmn_vsd\n"\
			"shp_cti_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

			pd = pp->shp_motion_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] : shp_motion_vsd\n"\
			"shp_motion_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8]);

			pd = pp->shp_chroma_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] : shp_chroma_vsd\n"\
			"shp_chroma_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4]);

		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set resolution enhance misc by specific value
 *	- input data : see PE_KWRAP_SHP_FMT_TYPE
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetRenMiscCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KWRAP_VER_M19 || PE_KWRAP_VER_O18)
	{
		LX_PE_SHP_RE7_MISC_T ctrl;
		ret = KWRAP_PE_SetDefaultParam(param, \
			PE_KWRAP_DFLT_PARAM_REN_MIS, (void *)&ctrl, __F__, __L__);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set resolution enhance misc parameter
 * - use input struct LX_PE_SHP_RE3_MISC_T for H15, M14BX
 * - use input struct LX_PE_SHP_RE2_MISC_T for M14AXBX
 * - use input struct LX_PE_SHP_RE1_MISC_T for H13AX
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetRenMiscParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(SHP);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20)
	{
		LX_PE_SHP_RE1_MISC_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_RE1_MISC_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_RE1_MISC_T *)param;
			pd = pp->shp_cmn_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] : shp_cmn_vsd\n"\
			"shp_cmn_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_vsd	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24]);

			pd = pp->shp_djg_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] : shp_djg_vsd\n"\
			"shp_djg_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

			pd = pp->shp_map_cmn_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] : shp_map_cmn_vsd\n"\
			"shp_map_cmn_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_vsd	[10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);
			pd = pp->shp_balance_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] : shp_balance_vsd\n"\
			"shp_balance_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_vsd	[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_vsd	[20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);

			pd = pp->shp_ti_cmn_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] : shp_ti_cmn_vsd\n"\
			"shp_ti_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);

			pd = pp->shp_chroma_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] : shp_chroma_vsd\n"\
			"shp_chroma_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_RE1_MISC_T, SHP);
			#endif
			ret = PE_SHP_SetReMiscCtrl(pp);
			PE_CHECK_CODE(ret != RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_RE7_MISC_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_RE7_MISC_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_RE7_MISC_T *)param;
			pd = pp->shp_cmn_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] : shp_cmn_vsd\n"\
			"shp_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_vsd    [20]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22]);

			pd = pp->shp_djg_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] : shp_djg_vsd\n"\
			"shp_djg_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

			pd = pp->shp_map_cmn_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] : shp_map_cmn_vsd\n"\
			"shp_map_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19]);

			pd = pp->shp_balance_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] : shp_balance_vsd\n"\
			"shp_balance_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_vsd    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);

			pd = pp->shp_ti_cmn_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] : shp_ti_cmn_vsd\n"\
			"shp_ti_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_vsd    [10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);

			pd = pp->shp_simple_snr_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] : shp_simple_snr_vsd\n"\
			"shp_simple_snr_vsd    [00]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2]);

			pd = pp->shp_cti_cmn_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] : shp_cti_cmn_vsd\n"\
			"shp_cti_cmn_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7]);

			pd = pp->shp_motion_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] : shp_motion_vsd\n"\
			"shp_motion_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8]);

			pd = pp->shp_chroma_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] : shp_chroma_vsd\n"\
			"shp_chroma_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_RE7_MISC_T, SHP);
			#endif
			ret = PE_SHP_SetReMiscCtrl(pp);
			PE_CHECK_CODE(ret != RET_OK, break, \
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
 * get resolution enhance misc parameter
 * - use input struct LX_PE_SHP_RE3_MISC_T for H15, M14BX
 * - use input struct LX_PE_SHP_RE2_MISC_T for M14AXBX
 * - use input struct LX_PE_SHP_RE1_MISC_T for H13AX
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetRenMiscParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = PE_SHP_GetReMiscCtrl((LX_PE_SHP_RE7_MISC_T *)param);
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
 * get edge enhancemen default settings
 *	- input data : 0~50
 *
 * @param   *param [in/out] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetEdgeEnhanceDefaultSettings(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;

	if (PE_KDRV_VER_O20|| PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_EE4_T ctrl;
		const LX_PE_SHP_EE4_T *p_data_tbl=NULL;
		UINT8 in=0, out_tbl[PE_KWRAP_SHP_STEP];
		UINT8 in_tbl[PE_KWRAP_SHP_STEP]={0, 10, 25, 30, 50};
		do {
			CHECK_KNULL(ret, param);
			CHECK_KNULL(ret, param->st_data);
			in = (param->data>50)? 50:param->data;
			p_data_tbl = g_pe_kwrap_p_ee4;
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_vsd[0]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_vsd[1]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_vsd[2]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_vsd[3]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_vsd[4]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_vsd[5]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_vsd[6]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_vsd[7]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_vsd[8]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_vsd[9]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_vsd[10]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_vsd[11]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_vsd[12]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_vsd[13]);
			memcpy(param->st_data, &ctrl, sizeof(LX_PE_SHP_EE4_T));
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}

	return ret;
}
/**
 * set edge enhancement by specific value
 *	- input data : 0~50
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetEdgeEnhanceCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;

	if (PE_KDRV_VER_O20|| PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_EE4_T ctrl;
		ret = KWRAP_PE_SetDefaultParam(param, \
			PE_KWRAP_DFLT_PARAM_REN_EDG, (void *)&ctrl, __F__, __L__);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}

	return ret;
}
/**
 * set edge enhancement parameter
 * - use input struct LX_PE_SHP_EE1_T for H15, M14
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetEdgeEnhanceParam(void *param)
{
	int ret = RET_OK;
#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
#endif

	PE_CHECK_KWRAP_FUNC_ON(SHP);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60 || PE_KDRV_VER_O20)
	{
		LX_PE_SHP_EE1_T *pp = NULL;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_EE1_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	#endif
		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_EE1_T *)param;
			pd = pp->shp_ee_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_ee_post\n"\
			"shp_ee_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27]);
			
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_EE1_T, SHP);
		#endif
			ret = PE_SHP_SetEdgeEnhanceCtrl(pp);
			PE_CHECK_CODE(ret != RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_EE4_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_EE4_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_EE4_T *)param;
			pd = pp->shp_ee_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_ee_post\n"\
			"shp_ee_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);
			
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_EE4_T, SHP);
			#endif
			ret = PE_SHP_SetEdgeEnhanceCtrl(pp);
			PE_CHECK_CODE(ret != RET_OK, break, \
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
 * set edge enhancement parameter
 * - use input struct LX_PE_SHP_EE1_T for H15, M14
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetEdgeEnhanceParam(void *param)
{
	int ret = RET_OK;

	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();

	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = PE_SHP_GetEdgeEnhanceCtrl((LX_PE_SHP_EE4_T *)param);
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
 * get detail enhancemen default settings
 *	- input data : 0~50
 *
 * @param   *param [in/out] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetDetailEnhanceDefaultSettings(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;

	LX_PE_SHP_DE4_T ctrl;
	const LX_PE_SHP_DE4_T *data_tbl=NULL;
	UINT8 in=0, out_tbl[PE_KWRAP_SHP_STEP];
	UINT8 in_tbl[PE_KWRAP_SHP_STEP]={0, 10, 25, 30, 50};
	do {
		CHECK_KNULL(ret, param);
		CHECK_KNULL(ret, param->st_data);
		in = (param->data>50)? 50:param->data;
		data_tbl = g_pe_kwrap_p_de4;
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_vsd[0]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_vsd[1]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_vsd[2]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_vsd[3]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_vsd[4]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_vsd[5]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_vsd[6]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_vsd[7]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_vsd[8]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_vsd[9]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_vsd[10]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_vsd[11]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_vsd[12]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_vsd[13]);
		memcpy(param->st_data, &ctrl, sizeof(LX_PE_SHP_DE4_T));
	}while (0);
	return ret;
}
/**
 * set detail enhancement by specific value
 *	- input data : 0~50
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDetailEnhanceCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;

	if (PE_KDRV_VER_M19)
	{
		LX_PE_SHP_RE_EASY_DE_T ctrl;
		ret = KWRAP_PE_SetDefaultParam(param, \
			PE_KWRAP_DFLT_PARAM_REN_DTL, (void *)&ctrl, __F__, __L__);
	}
	else if (PE_KDRV_VER_O18)
	{
		LX_PE_SHP_DE4_T ctrl;
		ret = KWRAP_PE_SetDefaultParam(param, \
			PE_KWRAP_DFLT_PARAM_REN_DTL, (void *)&ctrl, __F__, __L__);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set detail enhancement parameter
 * - use input struct LX_PE_SHP_DE1_T for H15, M14
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetDetailEnhanceParam(void *param)
{
	int ret = RET_OK;
#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
#endif

	PE_CHECK_KWRAP_FUNC_ON(SHP);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();

	do {
		LX_PE_SHP_DE4_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_DE4_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		__attribute__((unused)) UINT8 *pd;
		CHECK_KNULL(ret, param);
		pp = (LX_PE_SHP_DE4_T *)param;
		pd = pp->shp_de_vsd;
		PE_KWRAP_DBG_PRINT(SHP, \
		"set[%d] : shp_ee_post\n"\
		"shp_de_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_de_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13]);
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		PE_KWRAP_CHECK_WINID(LX_PE_SHP_DE4_T, SHP);
		#endif
		ret = PE_SHP_SetDetailEnhanceCtrl(pp);
		PE_CHECK_CODE(ret != RET_OK, break, \
			"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
	}while (0);
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * get detail enhancement parameter
 * - use input struct LX_PE_SHP_DE1_T for H15, M14
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetDetailEnhanceParam(void *param)
{
	int ret = RET_OK;

	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();

	if (PE_KDRV_VER_M19)
	{
		ret = PE_SHP_GetDetailEnhanceCtrl((LX_PE_SHP_RE_EASY_DE_T *)param);
	}
	else if (PE_KDRV_VER_O18)
	{
		ret = PE_SHP_GetDetailEnhanceCtrl((LX_PE_SHP_DE4_T *)param);
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
 * set psp parameter
 * - use input struct LX_PE_SHP_PSP_T for M16+
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetPspParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(SHP);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_PSP_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_PSP_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_PSP_T *)param;
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_PSP_T, SHP);
			#endif
			ret = PE_SHP_SetPspCtrl(pp);
			PE_CHECK_CODE(ret != RET_OK, break, \
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
 * set psp parameter
 * - use input struct LX_PE_SHP_PSP_T for M16+
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetPspParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = PE_SHP_GetPspCtrl((LX_PE_SHP_PSP_T *)param);
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
 * set psp parameter
 * - use input struct LX_PE_VSD_OBC_CONT_T for M16+
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetObcParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(SHP);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60)
	{
		LX_PE_VSD_OBC3_CONT_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_VSD_OBC3_CONT_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_VSD_OBC3_CONT_T *)param;
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_VSD_OBC3_CONT_T, SHP);
			#endif
			ret = PE_SHP_SetObcCtrl(pp);
			PE_CHECK_CODE(ret != RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else if (PE_KDRV_VER_M19)
	{
		LX_PE_VSD_OBC1_CONT_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_VSD_OBC1_CONT_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_VSD_OBC1_CONT_T *)param;
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_VSD_OBC1_CONT_T, SHP);
			#endif
			ret = PE_SHP_SetObcCtrl(pp);
			PE_CHECK_CODE(ret != RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else if (PE_KDRV_VER_O20)
	{
		LX_PE_VSD_OBC2_CONT_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_VSD_OBC2_CONT_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_VSD_OBC2_CONT_T *)param;
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_VSD_OBC2_CONT_T, SHP);
			#endif
			ret = PE_SHP_SetObcCtrl(pp);
			PE_CHECK_CODE(ret != RET_OK, break, \
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
 * set psp parameter
 * - use input struct LX_PE_SHP_PSP_T for M16+
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetObcParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19)
	{
		ret = PE_SHP_GetObcCtrl((LX_PE_VSD_OBC1_CONT_T *)param);
	}
	else if (PE_KDRV_VER_O18)
	{
		ret = PE_SHP_GetObcCtrl((LX_PE_VSD_OBC_CONT_T *)param);
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
 * set psp parameter
 * - use input struct LX_PE_VSD_OBC_LUT_T for M16+
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetObcLUT(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(SHP);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_E60)
	{
		LX_PE_VSD_OBC2_LUT_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_VSD_OBC2_LUT_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_VSD_OBC2_LUT_T *)param;
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_VSD_OBC2_LUT_T, SHP);
			#endif
			ret = PE_SHP_SetObcLUT(pp);
			PE_CHECK_CODE(ret != RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else if (PE_KDRV_VER_O20)
	{
		LX_PE_VSD_OBC1_LUT_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_VSD_OBC1_LUT_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_VSD_OBC1_LUT_T *)param;
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_VSD_OBC1_LUT_T, SHP);
			#endif
			ret = PE_SHP_SetObcLUT(pp);
			PE_CHECK_CODE(ret != RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else if (PE_KDRV_VER_M19)
	{
		LX_PE_VSD_OBC_LUT_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_VSD_OBC_LUT_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_VSD_OBC_LUT_T *)param;
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_VSD_OBC_LUT_T, SHP);
			#endif
			ret = PE_SHP_SetObcLUT(pp);
			PE_CHECK_CODE(ret != RET_OK, break, \
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
 * set psp parameter
 * - use input struct LX_PE_VSD_OBC_LUT_T for M16+
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetObcLUT(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KWRAP_VER_M19 || PE_KWRAP_VER_O18)
	{
		ret = PE_SHP_GetObcLUT((LX_PE_VSD_OBC_LUT_T *)param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}

int KWRAP_PE_SetRenSqmCmnCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;

	if (PE_KWRAP_VER_M19)
	{
		ret = KWRAP_PE_SetRenSqmCmnBspDB(param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}

	return ret;
}

/**
 * set resolution sqm ui enhance common parameter
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetRenSqmCmnParam(void *param)
{
	int ret = RET_OK;
#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
#endif
	__attribute__((unused)) UINT8 *pd;
	PE_CHECK_KWRAP_FUNC_ON(SHP);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	do {
		LX_PE_SHP_RE_SQM_CMN_T *pp = (LX_PE_SHP_RE_SQM_CMN_T *)param;
		CHECK_KNULL(ret, param);
		ret = KWRAP_PE_CheckResSqmCmnParam((void *)pp);
		PE_CHECK_CODE(ret!=RET_OK, break, \
		"[%s,%d]check_dnr_cmn.\n", __F__, __L__);
		PE_CHECK_ACTION(pp->win_id>LX_PE_WIN_ALL, ret=RET_OK;break);
		ret = PE_SHP_SetSqmCmnCtrl((void *)pp);
		PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
	}while (0);
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}

/**
 * set resolution sqm enhance common parameter
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetRenSqmDetailParam(void *param)
{
	int ret = RET_OK;
#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
#endif
	__attribute__((unused)) UINT8 *pd;
	PE_CHECK_KWRAP_FUNC_ON(SHP);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	do {
		LX_PE_SHP_RE_SQM_DETAIL_T *pp = (LX_PE_SHP_RE_SQM_DETAIL_T *)param;
		CHECK_KNULL(ret, param);
		ret = KWRAP_PE_CheckResSqmDetailParam((void *)pp);
		PE_CHECK_CODE(ret!=RET_OK, break, \
		"[%s,%d]check_dnr_cmn.\n", __F__, __L__);
		PE_CHECK_ACTION(pp->win_id>LX_PE_WIN_ALL, ret=RET_OK;break);
		ret = PE_SHP_SetSqmDetailCtrl((void *)pp);
		PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
	}while (0);
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set resolution enhance common parameter
 * - use input struct LX_PE_SHP_RE2_CMN_T for H15, M14BX
 * - use input struct LX_PE_SHP_RE1_CMN_T for H13AX
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetRenEasyCmnParam(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif

	LX_PE_SHP_RE_EASY_CMN_T *pp = NULL;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	static LX_PE_SHP_RE_EASY_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	#endif

	PE_CHECK_KWRAP_FUNC_ON(SHP);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();

	do {
		__attribute__((unused)) UINT8 *pd;
		CHECK_KNULL(ret, param);
		pp = (LX_PE_SHP_RE_EASY_CMN_T *)param;
		pd = pp->shp_ui_vsd;
		PE_KWRAP_DBG_PRINT(SHP, \
		"set[%d] : shp_ui_main_vsd\n"\
		"shp_ui_main_vsd    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_main_vsd    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13], pd[14]);
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		//PE_KWRAP_CHECK_WINID(LX_PE_SHP_RE_EASY_CMN_T, SHP);
		#endif
		ret = PE_SHP_SetReEasyCmnCtrl(pp);
		PE_CHECK_CODE(ret != RET_OK, break, \
			"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
	}while (0);

	PE_TRACE_END();
	PE_UNLOCK();

	return ret;
}

/**
 * set psp parameter
 * - use input struct LX_PE_VSD_OBC_LUT_T for M16+
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetObcStereo(void *param)
{
	int ret = RET_OK;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
	#endif
	PE_CHECK_KWRAP_FUNC_ON(SHP);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_O20)
	{
		LX_PE_VSD_OBC_LUT_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_VSD_OBC_LUT_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_VSD_OBC_LUT_T *)param;
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_VSD_OBC_LUT_T, SHP);
			#endif
			ret = PE_SHP_SetObcLUT(pp);
			PE_CHECK_CODE(ret != RET_OK, break, \
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
 * set f20 resolution enhance all parameter
 * - use input struct LX_PE_SHP_ALL_CMN_T for F20
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetReAllParam(void *param)
{
	int ret = RET_OK;
#ifdef PE_KWRAP_CHK_VALID_WIN_ID
	__attribute__((unused)) static UINT32 chk = 0x0;
#endif
	PE_CHECK_KWRAP_FUNC_ON(SHP);
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();

	if(PE_KDRV_VER_O20)
	{
		LX_PE_SHP_ALL_CMN_T *pp = NULL;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_ALL_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_ALL_CMN_T *)param;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_ALL_CMN_T, SHP);
		#endif
			ret = PE_SHP_SetReAllCtrl(pp);
			PE_CHECK_CODE(ret != RET_OK, break, \
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


