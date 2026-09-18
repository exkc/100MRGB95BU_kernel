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

/** @file pe_kwrap_shp_sre.c
 *
 *	application interface functions for picture enhancement.
 *	These include following functions.
 *	- sharpness control (super resolution enhancement)
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
	External Function Prototype Declarations
----------------------------------------------------------------------------*/
extern UINT32 g_pe_kwrap_ver_mask;

/*----------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------*/
const LX_PE_SHP_SR_RE_CMN_T g_pe_kwrap_p_sr_re_cmn[PE_KWRAP_SHP_STEP] = {\
	{0,  0x0, 0x0, 0x0, 0x0, 0x1, 0x1, 0x1, 0x1,  0x0,  0x0,  0x0,  0x0,  0x0, \
	0x5, 0x0, 0x0, 0x0, 0x1A, 0x10, 0x05, 0x1A, 0x10, 0x05}, \
	{0,  0x0, 0x0, 0x0, 0x0, 0x1, 0x1, 0x1, 0x1,  0x0,  0x0,  0x0,  0x0,  0x0, \
	0x5, 0x0, 0x8, 0x8, 0x1A, 0x10, 0x05, 0x1A, 0x10, 0x05}, \
	{0, 0x14, 0x14, 0x14, 0x1d, 0x1, 0x1, 0x1, 0x1, 0x30, 0x2d, 0x1d, 0x0d, 0x0d, \
	0x5, 0x0, 0x8, 0x8, 0x1A, 0x10, 0x05, 0x1A, 0x10, 0x05}, \
	{0, 0x20, 0x20, 0x20, 0x20, 0x1, 0x1, 0x1, 0x1, 0x40, 0x40, 0x20, 0x10, 0x10, \
	0x1f, 0x0, 0x8, 0x8, 0x1A, 0x10, 0x05, 0x1A, 0x10, 0x05}, \
	{0, 0x30, 0x30, 0x30, 0x38, 0x1, 0x1, 0x1, 0x1, 0x8, 0x48, 0x28, 0x28, 0x28, \
	0x25, 0x0, 0x8, 0x8, 0x1A, 0x10, 0x05, 0x1A, 0x10, 0x05}
};

/* sr res hor */
const LX_PE_SHP_SR_RE_HOR_T g_pe_kwrap_p_sr_re_hor[PE_KWRAP_SHP_STEP] = {\
	{0, 0x02, 0x0,  0x0,  0x07,  0x0,  0x0, 0x28, 0x44, 0x03, 0x05}, \
	{0, 0x02, 0xA,  0xA,  0x07,  0x0,  0x0, 0x28, 0x44, 0x03, 0x05}, \
	{0, 0x02, 0x10, 0x10, 0x07,  0x16, 0x1a, 0x28, 0x44, 0x03, 0x05}, \
	{0, 0x02, 0x05, 0x05, 0x07,  0x20, 0x20, 0x28, 0x44, 0x03, 0x05}, \
	{0, 0x02, 0x10, 0x10, 0x07,  0x38, 0x38, 0x28, 0x44, 0x03, 0x05}
};

/* sr res ver */
const LX_PE_SHP_SR_RE_VER_T g_pe_kwrap_p_sr_re_ver[PE_KWRAP_SHP_STEP] = {\
	{0, 0x50, 0x0,  0x0,  0x0, 0x0,  0x0,  0x0, 0x28, 0x44}, \
	{0, 0x50, 0x0, 0x10, 0x10, 0x0,  0x0,  0x0, 0x28, 0x44}, \
	{0, 0x50, 0x0, 0x10, 0x10, 0x0, 0x10, 0x1a, 0x28, 0x44}, \
	{0, 0x50, 0x0, 0x10, 0x10, 0x0, 0x18, 0x20, 0x28, 0x44}, \
	{0, 0x50, 0x0, 0x10, 0x10, 0x0, 0x28, 0x38, 0x28, 0x44}
};

/* edge enhance */
const LX_PE_SHP_SR_EE_T g_pe_kwrap_p_sr_ee[PE_KWRAP_SHP_STEP] = {\
	{0,  0x0,  0x0,  0x0,  0x0}, \
	{0, 0x02, 0x02, 0x02, 0x02}, \
	{0, 0x05, 0x05, 0x05, 0x05}, \
	{0, 0x10, 0x10, 0x10, 0x10}, \
	{0, 0x20, 0x20, 0x20, 0x20}
};

/* sr detail enhance */
const LX_PE_SHP_SR_DE_T g_pe_kwrap_p_sr_de[PE_KWRAP_SHP_STEP] = {\
	{0,  0x0,  0x0,  0x0,  0x0}, \
	{0, 0x0a, 0x0a, 0x0a, 0x0a}, \
	{0, 0x15, 0x15, 0x15, 0x15}, \
	{0, 0x20, 0x20, 0x20, 0x20}, \
	{0, 0x2d, 0x2d, 0x2d, 0x2d}
};

/* res hor */
const LX_PE_SHP_SR_RE_MISC_T g_pe_kwrap_p_sr_re_misc[PE_KWRAP_SHP_FMT_NUM] = {\
	/* PE_KWRAP_SHP_FMT_SD */{0, \
	/* hor */0x01, 0x28, 0x20, \
	/* ver */0x01, 0x01, 0x01, \
	/* cmn */0x40, 0x40, 0x1, 0x1, 0x20,\
	/* djg */0x01, 0x01, 0x01, 0x01, 0xb0, 0x00, \
	/* djg */0x20, 0x80, 0x08, 0x14, 0x28, 0x08, \
	/* cmn pre*/0x02, 0x02, 0x0c, 0x30, \
	/* emp */0x00, 0x01, 0x20, 0x30, \
	/* emp */0x18, 0x00, 0x50, 0xff, \
	/* emp */0x00, 0x00, 0x80, 0xff, \
	/* emp */0x00, 0x00, 0xa0, 0xa0, \
	/* tmp */0x01, 0x01, 0x20, 0x08, \
	/* tmp */0x10, 0x00, 0x50, 0xff, \
	/* tmp */0x06, 0x00, 0x70, 0xff, \
	/* tmp */0x08, 0x00, 0x60, 0xa0, \
	/* blc */0x01, 0x00, 0x0c, 0x19, 0x20, 0x40, 0x80, \
	/* blc */0x01, 0x00, 0x10, 0x20, 0x20, 0x40, 0x80, \
	/* blc */0x40, 0x60, 0xd0, 0xd8, 0xff, 0xff, 0xff, \
	/* blc */0x38, 0x49, 0xd0, 0xd8, 0xff, 0xff, 0xff, \
	/* blc */0x40, 0x60, 0xd0, 0xd8, 0xff, 0xff, 0xff, \
	/* blc */0x38, 0x48, 0xd0, 0xd8, 0xff, 0xff, 0xff, \
	/* ptv */0x01, 0x01, 0x01, \
	/* pth */0x01, 0x01, 0x01, \
	/* sti */0x01, 0x01, 0x01, \
	/* tgn */0x00, 0x08, 0x02, 0x7f, 0x07, \
	/* tgn */0x0a, 0x04, 0x00, 0x02, 0x0a, \
	/* tgn */0x01, 0x01, 0x05, 0x00, 0x0f, \
	/* tgn */0x08, 0x0a, 0x0c, 0x0e, 0x0f, 0x0f, 0x0f, 0x0f}, \

	/* PE_KWRAP_SHP_FMT_HD */{0, \
	/* hor */0x01, 0x30, 0x20, \
	/* ver */0x01, 0x01, 0x01, \
	/* cmn */0x40, 0x40, 0x1, 0x1, 0x20,\
	/* djg */0x01, 0x01, 0x01, 0x01, 0xb0, 0x00, \
	/* djg */0x20, 0x80, 0x08, 0x14, 0x28, 0x08, \
	/* cmn pre*/0x02, 0x02, 0x0c, 0x30, \
	/* emp */0x00, 0x01, 0x20, 0x30, \
	/* emp */0x18, 0x00, 0x50, 0xff, \
	/* emp */0x00, 0x00, 0x80, 0x80, \
	/* emp */0x00, 0x00, 0xa0, 0x80, \
	/* tmp */0x01, 0x01, 0x20, 0x10, \
	/* tmp */0x10, 0x00, 0x50, 0xff, \
	/* tmp */0x06, 0x00, 0x70, 0x80, \
	/* tmp */0x08, 0x00, 0x60, 0xa0, \
	/* blc */0x01, 0x00, 0x10, 0x20, 0x20, 0x40, 0x80, \
	/* blc */0x01, 0x00, 0x10, 0x20, 0x20, 0x40, 0x80, \
	/* blc */0x40, 0x60, 0xd0, 0xd8, 0xff, 0xff, 0xff, \
	/* blc */0x38, 0x49, 0xd0, 0xd8, 0xff, 0xff, 0xff, \
	/* blc */0x40, 0x60, 0xd0, 0xd8, 0xff, 0xff, 0xff, \
	/* blc */0x38, 0x49, 0xd0, 0xd8, 0xff, 0xff, 0xff, \
	/* ptv */0x01, 0x01, 0x01, \
	/* pth */0x01, 0x01, 0x01, \
	/* sti */0x01, 0x01, 0x01, \
	/* tgn */0x00, 0x08, 0x02, 0x7f, 0x07, \
	/* tgn */0x0a, 0x04, 0x00, 0x02, 0x0a, \
	/* tgn */0x01, 0x01, 0x05, 0x00, 0x0f, \
	/* tgn */0x08, 0x0a, 0x0c, 0x0e, 0x0f, 0x0f, 0x0f, 0x0f}
};

/* sre */

const LX_PE_SHP_SR_RE2_CMN_T g_pe_kwrap_p_sr_re_cmn2[PE_KWRAP_SHP_STEP] = {\
	{0,\
	 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},\
	 {0x00,0x00,0x00},\
	 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
	}, \
	{0,\
	 {0x20,0x20,0x00,0x08,0x0f,0x00,0x08,0x0f,0x10,0x10,0x00,0x02,0x0f},\
	 {0x50,0x10,0x08}, \
	 {0x08,0x08,0x80,0x3c,0x10,0x12,0x08,0x10,0x12,0x08}
	}, \
	{0,\
	 {0x2f,0x2f,0x00,0x08,0x0f,0x00,0x08,0x0f,0x1f,0x1f,0x00,0x02,0x0f},\
	 {0x7f,0x1f,0x0f}, \
	 {0x1e,0x0e,0x80,0x3c,0x10,0x12,0x08,0x10,0x12,0x08}
	}, \
	{0,\
	 {0x34,0x34,0x00,0x08,0x0f,0x00,0x08,0x0f,0x24,0x24,0x00,0x02,0x0f},\
	 {0x80,0x24,0x14}, \
	 {0x24,0x14,0x80,0x3c,0x10,0x12,0x08,0x10,0x12,0x08}
	}, \
	{0,\
	 {0x38,0x38,0x00,0x08,0x0f,0x00,0x08,0x0f,0x28,0x28,0x00,0x02,0x0f},\
	 {0x80,0x28,0x18}, \
	 {0x28,0x18,0x80,0x3c,0x10,0x12,0x08,0x10,0x12,0x08}
	}
};

const LX_PE_SHP_SR_RE3_CMN_T g_pe_kwrap_p_sr_re_cmn3[PE_KWRAP_SHP_STEP] = {\
	{0,\
	 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},\
	 {0x00,0x00,0x00},\
	 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
	}, \
	{0,\
	 {0x04,0x10,0x10,0x00,0x04,0x02,0x02,0x01,0x00,0x04,0x04,0x00,0x04,0x01},\
	 {0x30,0x04,0x01}, \
	 {0x80,0x10,0x1a,0x04,0x00,0x1a,0x04,0x00}
	}, \
	{0,\
	 {0x0f,0x1f,0x1f,0x00,0x04,0x02,0x02,0x01,0x00,0x0f,0x0f,0x00,0x04,0x01},\
	 {0x7f,0x07,0x01}, \
	 {0xbf,0x3e,0x1a,0x04,0x00,0x1a,0x04,0x00}
	}, \
	{0,\
	 {0x10,0x20,0x20,0x00,0x04,0x02,0x02,0x01,0x00,0x10,0x10,0x00,0x04,0x01},\
	 {0x80,0x07,0x01}, \
	 {0xc0,0x3f,0x1a,0x04,0x00,0x1a,0x04,0x00}
	 
	}, \
	{0,\
	 {0x30,0x40,0x40,0x00,0x04,0x02,0x02,0x01,0x00,0x30,0x30,0x00,0x04,0x01},\
	 {0xa0,0x28,0x03}, \
	 {0xe0,0x3f,0x1a,0x04,0x00,0x1a,0x04,0x00}
	}
};

const LX_PE_SHP_SR_RE4_CMN_T g_pe_kwrap_p_sr_re_cmn4[PE_KWRAP_SHP_STEP] = {\
	{0,\
	 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
	 0x00},\
	 {0x00,0x00,0x00}
	}, \
	{0,\
	 {0x10,0x20,0x10,0x10,0x10,0x10,0x00,0x04,0x08,0x00,\
	 0x10},\
	 {0x10,0x10,0x01}
	}, \
	{0,\
	 {0x2C,0xB0,0x40,0x30,0x30,0x30,0x00,0x04,0x08,0xE0,\
	 0x30},\
	 {0x1C,0x1C,0x06}
	}, \
	{0,\
	 {0x30,0xC0,0x50,0x40,0x40,0x40,0x00,0x04,0x08,0xE0,\
	 0x40},\
	 {0x20,0x20,0x08}
	},\
	{0,\
	 {0x38,0xC8,0x58,0x48,0x48,0x48,0x00,0x04,0x08,0xE0,\
	 0x48},\
	 {0x28,0x28,0x10}
	}
};


const LX_PE_SHP_SR_RE2_HOR_T g_pe_kwrap_p_sr_re_hor2[PE_KWRAP_SHP_STEP] = {\
	{0,\
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}}, \
	{0,\
	{0x00,0x00,0x03,0x03,0x00,0x20,0x10,0x20,0x00,0x00,0x00,0x00}}, \
	{0,\
	{0x00,0x00,0x07,0x07,0x00,0x2f,0x1f,0x3f,0x00,0x00,0x00,0x00}}, \
	{0,\
	{0x00,0x00,0x0c,0x0c,0x00,0x34,0x24,0x40,0x00,0x00,0x00,0x00}}, \
	{0,\
	{0x00,0x00,0x10,0x10,0x00,0x38,0x28,0x3f,0x00,0x00,0x00,0x00}}
};

const LX_PE_SHP_SR_RE3_HOR_T g_pe_kwrap_p_sr_re_hor3[PE_KWRAP_SHP_STEP] = {\
	{0,\
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00}}, \
	{0,\
	{0x00,0x05,0x01,0x01,0x04,0x02,0x10}}, \
	{0,\
	{0x00,0x05,0x05,0x05,0x05,0x0f,0x7f}}, \
	{0,\
	{0x00,0x05,0x06,0x06,0x20,0x10,0x80}}, \
	{0,\
	{0x00,0x05,0x20,0x20,0x40,0x30,0xc0}}
};

const LX_PE_SHP_SR_RE4_HOR_T g_pe_kwrap_p_sr_re_hor4[PE_KWRAP_SHP_STEP] = {\
	{0,\
	{0x00,0x00,0x00,0x00,0x00,0x00}}, \
	{0,\
	{0x00,0x01,0x01,0x08,0x08,0x10}}, \
	{0,\
	{0x00,0x02,0x02,0x1C,0x1C,0x30}}, \
	{0,\
	{0x00,0x02,0x02,0x20,0x20,0x40}}, \
	{0,\
	{0x00,0x06,0x06,0x28,0x28,0x48}}
};

/* res ver */
const LX_PE_SHP_SR_RE2_VER_T g_pe_kwrap_p_sr_re_ver2[PE_KWRAP_SHP_STEP] = {\
	{0, {0x00,0x00,0x00,0x00,0x00,0x00}}, \
	{0, {0x00,0x08,0x08,0x00,0x10,0x20}}, \
	{0, {0x00,0x0f,0x0f,0x00,0x1f,0x3f}}, \
	{0, {0x00,0x14,0x14,0x00,0x24,0x40}}, \
	{0, {0x00,0x18,0x18,0x00,0x28,0x40}}
};
const LX_PE_SHP_SR_RE3_VER_T g_pe_kwrap_p_sr_re_ver3[PE_KWRAP_SHP_STEP] = {\
	{0, {0x00,0x00,0x00,0x00,0x00,0x00}}, \
	{0, {0x00,0x00,0x03,0x03,0x10,0x30}}, \
	{0, {0x00,0x00,0x07,0x07,0x1f,0x7f}}, \
	{0, {0x00,0x00,0x08,0x08,0x20,0x80}}, \
	{0, {0x00,0x00,0x18,0x18,0x40,0xc0}}
};
const LX_PE_SHP_SR_RE4_VER_T g_pe_kwrap_p_sr_re_ver4[PE_KWRAP_SHP_STEP] = {\
	{0, {0x00,0x00}}, \
	{0, {0x10,0x10}}, \
	{0, {0x1C,0x1C}}, \
	{0, {0x20,0x20}}, \
	{0, {0x28,0x28}}
};

const LX_PE_SHP_SR_RE2_MISC_T g_pe_kwrap_p_sr_re_misc2[PE_KWRAP_SHP_FMT_NUM] = {\
	/* PE_KWRAP_SHP_FMT_SD */{0, \
	{/*cmn*/
	 0x01, 0x10, 0x45, 0x55, 0xb5, 0x15, 0x25, 0x65, 0xff, 0x85,\
	 0x40, 0x00, 0x01, 0x20, 0x20, 0x01, 0x01, 0x10, 0x40, 0x01, \
	 0x00, 0x01, 0xb0, 0x00, 0x45, 0x85, 0x17, 0x14, 0x40, 0x1c},\
	 {/*map*/
	 0x01, 0x0e, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
	 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x03, 0x00, 0x10, 0x02,\
	 0x10, 0x00, 0x50, 0xff, 0x10, 0x00, 0x50, 0xff, 0x00, 0x10,\
	 0xff, 0x40, 0x01, 0x01, 0x08, 0x10, 0x10, 0x00, 0x50, 0xff,\
	 0x00, 0xff, 0x32, 0xff, 0x00, 0x20, 0x30, 0x60},\
	 {/*balance*/
	 0x01, 0x00, 0x01, 0x08, 0x01, 0x06, 0x80, 0x01, 0x00, 0x01,\
	 0x08, 0x01, 0x06, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
	 0x00, 0x00, 0x00, 0x00, 0x40, 0x60, 0x80, 0xc0, 0x80, 0xc0,\
	 0xff, 0x40, 0x60, 0x80, 0xc0, 0x80, 0xc0, 0xff, 0x40, 0x60,\
	 0x80, 0xc0, 0x80, 0xff, 0xff, 0x40, 0x60, 0x80, 0xc0, 0x80,\
	 0xc0, 0xff},\
	 {/*ti*/
	 0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00, 0x01,\
	 0x00, 0x00},\
	 {/*tgen*/
	 0x01, 0x10, 0x08, 0x10, 0x07, 0x02, 0x05, 0x02, 0x05, 0x0f,\
	 0x01, 0x01, 0x50, 0x0f, 0x0f, 0x04, 0x08, 0x0a, 0x0b, 0x0c,\
	 0x0d, 0x0f, 0x0f},\
	},\
	/* PE_KWRAP_SHP_FMT_HD */{0, \
	{/*cmn*/
	 0x01, 0x10, 0x40, 0x50, 0xb0, 0x10, 0x20, 0x60, 0xff, 0x80,\
	 0x40, 0x00, 0x01, 0x20, 0x20, 0x01, 0x01, 0x10, 0x40, 0x01, \
	 0x00, 0x01, 0xb0, 0x00, 0x40, 0x80, 0x17, 0x14, 0x40, 0x1c},\
	 {/*map*/
	 0x01, 0x0e, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
	 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x03, 0x00, 0x10, 0x02,\
	 0x10, 0x00, 0x50, 0xff, 0x10, 0x00, 0x50, 0xff, 0x00, 0x10,\
	 0xff, 0x40, 0x01, 0x01, 0x08, 0x10, 0x10, 0x00, 0x50, 0xff,\
	 0x00, 0xff, 0x32, 0xff, 0x00, 0x20, 0x30, 0x60},\
	 {/*balance*/
	 0x01, 0x00, 0x01, 0x08, 0x01, 0x06, 0x80, 0x01, 0x00, 0x01,\
	 0x08, 0x01, 0x06, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
	 0x00, 0x00, 0x00, 0x00, 0x40, 0x60, 0x80, 0xc0, 0x80, 0xc0,\
	 0xff, 0x40, 0x60, 0x80, 0xc0, 0x80, 0xc0, 0xff, 0x40, 0x60,\
	 0x80, 0xc0, 0x80, 0xff, 0xff, 0x40, 0x60, 0x80, 0xc0, 0x80,\
	 0xc0, 0xff},\
	 {/*ti*/
	 0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00, 0x01,\
	 0x00, 0x00},\
	 {/*tgen*/
	 0x01, 0x10, 0x08, 0x10, 0x07, 0x02, 0x05, 0x02, 0x05, 0x0f,\
	 0x01, 0x01, 0x50, 0x0f, 0x0f, 0x04, 0x08, 0x0a, 0x0b, 0x0c,\
	 0x0d, 0x0f, 0x0f}
	 }
};
const LX_PE_SHP_SR_RE3_MISC_T g_pe_kwrap_p_sr_re_misc3[PE_KWRAP_SHP_FMT_NUM] = {\
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
	 {/*tgen*/
	 0x01, 0x00, 0x04, 0x30, 0x04, 0x40, 0xff, 0x01, 0x00, 0x02,\
	 0x40, 0x04, 0x60, 0xff, 0x00, 0x01, 0x10, 0x30, 0xff, 0x10, \
	 0x20, 0x60, 0x50},\
	
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
	 {/*tgen*/
	 0x01, 0x00, 0x04, 0x30, 0x04, 0x40, 0xff, 0x01, 0x00, 0x02,\
	 0x40, 0x04, 0x60, 0xff, 0x00, 0x01, 0x10, 0x30, 0xff, 0x10, \
	 0x20, 0x60, 0x50},\
	}
};

const LX_PE_SHP_SR_RE4_MISC_T g_pe_kwrap_p_sr_re_misc4[PE_KWRAP_SHP_FMT_NUM] = {\
	/* PE_KWRAP_SHP_FMT_SD */{0, \
	{/*shp_cmn_4k*/
	 0x01,0x05,0x01,0x01,0x20,0x20,0x20,0x20,0x01,0x14,\
	 0xC8,0x30,0x01,0x01,0x02,0x01,0x01,0x03,0x01,0x00,\
	 0x02},\
	 {/*shp_map_cmn_4k*/
	 0x00,0x00,0x05,0x20,0x00,0x40,0x00,0x08,0xFF,0x10,\
	 0x08,0x10,0xFF,0x20,0x00,0x01,0x2C,0x3E,0x0C,0x06},\
	 {/*shp_balance_4k*/
	 0x00,0x00,0x02,0x20,0xFF,0x01,0x00,0x02,0x10,0x80,\
	 0x01,0x01,0x20,0x30,0x30,0x40,0xFF,0xFF,0x20,0x60,\
	 0xC0,0x20,0x60,0xC0,0x20,0x60,0xC0,0x20,0x60,0xC0},\
	 {/*shp_ti_cmn_4k*/
	 0x01,0x01,0x02,0x02,0x01,0x00,0x02,0x02,0x01,0x00,\
	 0x02,0x02},\
	 {/*shp_simple_snr_4k*/
	 0x00, 0x01, 0x04},\
	},\
	/* PE_KWRAP_SHP_FMT_HD */{0, \
	{/*shp_cmn_4k*/
	 0x01,0x05,0x01,0x01,0x20,0x20,0x20,0x20,0x01,0x14,\
	 0xC8,0x30,0x01,0x01,0x02,0x01,0x01,0x03,0x01,0x00,\
	 0x02},\
	 {/*shp_map_cmn_4k*/
	 0x00,0x00,0x05,0x20,0x00,0x40,0x00,0x08,0xFF,0x24,\
	 0x08,0x10,0xFF,0x10,0x01,0x01,0x2C,0x3E,0x04,0x02},\
	 {/*shp_balance_4k*/
	 0x00,0x00,0x02,0x20,0xFF,0x01,0x00,0x02,0x10,0x80,\
	 0x01,0x01,0x20,0x30,0x30,0x40,0xFF,0xFF,0x20,0x60,\
	 0xC0,0x20,0x60,0xC0,0x20,0x60,0xC0,0x20,0x60,0xC0},\
	 {/*shp_ti_cmn_4k*/
	 0x01,0x01,0x02,0x02,0x01,0x00,0x02,0x02,0x01,0x00,\
	 0x02,0x02},\
	 {/*shp_simple_snr_4k*/
	 0x00, 0x01, 0x04},\
	}
};

/* edge enhance */
const LX_PE_SHP_SR_EE2_T g_pe_kwrap_p_sr_ee2[PE_KWRAP_SHP_STEP] = {\
	{0, { 0x0,  0x0,  0x0,  0x0,  0x0,  0x0}}, \
	{0, {0x04, 0x04, 0x04, 0x04, 0x08, 0x08}}, \
	{0, {0x0f, 0x0f, 0x0f, 0x0f, 0x18, 0x18}}, \
	{0, {0x13, 0x13, 0x13, 0x13, 0x22, 0x22}}, \
	{0, {0x16, 0x16, 0x16, 0x16, 0x24, 0x24}}
};
/* edge enhance */
const LX_PE_SHP_SR_EE3_T g_pe_kwrap_p_sr_ee3[PE_KWRAP_SHP_STEP] = {\
	{0, { 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0}}, \
	{0, {0x02, 0x01, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00}}, \
	{0, {0x17, 0x0f, 0x17, 0x17, 0x1f, 0x1f, 0x01, 0x02, 0x00, 0x00}}, \
	{0, {0x18, 0x10, 0x18, 0x18, 0x20, 0x20, 0x01, 0x01, 0x00, 0x00}}, \
	{0, {0x38, 0x30, 0x38, 0x38, 0x40, 0x40, 0x03, 0x03, 0x00, 0x00}}
};
/* edge enhance */
const LX_PE_SHP_SR_EE4_T g_pe_kwrap_p_sr_ee4[PE_KWRAP_SHP_STEP] = {\
	{0x00,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
	 0x00,0x00,0x00,0x00}}, \
	{0x10,{0x10,0x04,0x02,0x10,0x10,0x01,0x01,0x02,0x02,\
	 0x00,0x00,0x00,0x00}}, \
	{0x1C,{0x1C,0x14,0x0C,0x1C,0x1C,0x01,0x01,0x0C,0x0C,\
	 0x00,0x00,0x00,0x00}}, \
	{0x20,{0x20,0x18,0x10,0x20,0x20,0x01,0x01,0x10,0x10,\
	 0x00,0x00,0x00,0x00}}, \
	{0x28,{0x28,0x20,0x18,0x28,0x28,0x01,0x01,0x18,0x18,\
	 0x00,0x00,0x00,0x00}}
};

/* detail enhance */
const LX_PE_SHP_SR_DE2_T g_pe_kwrap_p_sr_de2[PE_KWRAP_SHP_STEP] = {\
	{0, { 0x0,  0x0,  0x0,  0x0,  0x0,  0x0}}, \
	{0, {0x10, 0x10, 0x10, 0x10, 0x10, 0x10}}, \
	{0, {0x2f, 0x2f, 0x14, 0x14, 0x0f, 0x0f}}, \
	{0, {0x34, 0x34, 0x20, 0x20, 0x13, 0x13}}, \
	{0, {0x38, 0x38, 0x24, 0x24, 0x16, 0x16}}
};
/* detail enhance */
const LX_PE_SHP_SR_DE3_T g_pe_kwrap_p_sr_de3[PE_KWRAP_SHP_STEP] = {\
	{0, { 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0}}, \
	{0, {0x10, 0x10, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10}}, \
	{0, {0x1f, 0x1f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f}}, \
	{0, {0x20, 0x20, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20}}, \
	{0, {0x40, 0x40, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40}}
};
/* detail enhance */
const LX_PE_SHP_SR_DE4_T g_pe_kwrap_p_sr_de4[PE_KWRAP_SHP_STEP] = {\
	{0x00,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
	 0x00,0x00,0x00,0x00}}, \
	{0x10,{0x02,0x01,0x01,0x02,0x02,0x02,0x02,0x10,0x10,\
	 0x02,0x02,0x02,0x02}}, \
	{0x1C,{0x0C,0x06,0x04,0x0C,0x0C,0x0C,0x0C,0x1C,0x1C,\
	 0x0C,0x0C,0x0C,0x0C}}, \
	{0x20,{0x10,0x08,0x04,0x10,0x10,0x10,0x10,0x20,0x20,\
	 0x10,0x10,0x10,0x10}}, \
	{0x28,{0x18,0x10,0x08,0x18,0x18,0x18,0x18,0x28,0x28,\
	 0x18,0x18,0x18,0x18}}
};


/*2k*/

const LX_PE_SHP_SR2K_RE_CMN_T g_pe_kwrap_p_sr_2k_re_cmn[PE_KWRAP_SHP_STEP] = {\
	{0,\
	 {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
	 0x00},\
	 {0x00,0x00,0x00}
	}, \
	{0,\
	 {0x10,0x1C,0x08,0x40,0x10,0x00,0x00,0x00,0x00,0x04,\
	 0x04,0x02,0x04,0x10},\
	 {0x10,0x10,0x00}
	}, \
	{0,\
	 {0x3C,0x4C,0x2C,0x70,0x24,0x00,0x02,0x06,0xC0,0x1C,\
	 0x1C,0x10,0x1C,0x38},\
	 {0x1C,0x1C,0x00}
	}, \
	{0,\
	 {0x40,0x50,0x30,0x80,0x28,0x00,0x02,0x06,0xC0,0x20,\
	 0x20,0x14,0x20,0x40},\
	 {0x20,0x20,0x00}
	},\
	{0,\
	 {0x48,0x58,0x38,0x88,0x30,0x00,0x02,0x06,0xC0,0x20,\
	 0x20,0x14,0x20,0x48},\
	 {0x28,0x28,0x00}
	}
};
const LX_PE_SHP_SR2K_RE_HOR_T g_pe_kwrap_p_sr_2k_re_hor[PE_KWRAP_SHP_STEP] = {\
	{0,\
	{0x00,0x00,0x00,0x00,0x00,0x00}}, \
	{0,\
	{0x00,0x01,0x01,0x10,0x10,0x40}}, \
	{0,\
	{0x00,0x04,0x42,0x1C,0x1C,0x70}}, \
	{0,\
	{0x00,0x04,0x04,0x20,0x10,0x80}}, \
	{0,\
	{0x00,0x08,0x08,0x28,0x18,0x88}}
};
const LX_PE_SHP_SR2K_RE_VER_T g_pe_kwrap_p_sr_2k_re_ver[PE_KWRAP_SHP_STEP] = {\
	{0, {0x00,0x00}}, \
	{0, {0x02,0x10}}, \
	{0, {0x0C,0x1C}}, \
	{0, {0x10,0x20}}, \
	{0, {0x18,0x28}}
};
const LX_PE_SHP_SR2K_RE_MISC_T g_pe_kwrap_p_sr_2k_re_misc[PE_KWRAP_SHP_FMT_NUM] = {\
	/* PE_KWRAP_SHP_FMT_SD */{0, \
	{/*shp_cmn_2k*/
	 0x01,0x04,0x01,0x01,0x20,0x20,0x10,0x10,0x01,0x01,\
	 0x03,0x01,0x01,0x03,0x00,0x01,0x02,0x00,0x08},\
	 {/*shp_djg_2k*/
	 0x00,0x01,0x01,0x10,0x80,0x01,0x00,0x80},\
	 {/*shp_map_cmn_2k*/
	 0x00,0x00,0x05,0x20,0x00,0x40,0x00,0x04,0x80,0x08,\
	 0x00,0x1C,0xFF,0x28,0x01,0x01,0x2E,0x3E,0x0A,0x00},\
	 {/*shp_balance_2k*/
	 0x01,0x00,0x10,0x30,0x80,0x01,0x00,0x03,0x10,0x80,\
	 0x00,0x01,0x20,0x30,0x30,0x40,0xFF,0xFF,0x20,0x60,\
	 0xC0,0x20,0x60,0xC0,0x20,0x60,0xC0,0x20,0x60,0xC0},\
	 {/*shp_ti_cmn_2k*/
	 0x01,0x00,0x01,0x01,0x00,0x00,0x01,0x01,0x01,0x00,\
	 0x03,0x03},\
	 {/*shp_simple_snr_2k*/
	 0x00, 0x00, 0x01},\
	},\
	/* PE_KWRAP_SHP_FMT_HD */{0, \
	{/*shp_cmn_2k*/
	 0x01,0x04,0x01,0x01,0x20,0x20,0x10,0x10,0x01,0x01,\
	 0x03,0x01,0x01,0x03,0x01,0x01,0x02,0x00,0x08},\
	 {/*shp_djg_2k*/
	 0x01,0x01,0x01,0x10,0x80,0x01,0x00,0x80},\
	 {/*shp_map_cmn_2k*/
	 0x00,0x00,0x05,0x20,0x00,0x40,0x00,0x0C,0x90,0x40,\
	 0x00,0x10,0xFF,0x10,0x01,0x01,0x2E,0x3E,0x04,0x01},\
	 {/*shp_balance_2k*/
	 0x00,0x00,0x10,0x02,0x02,0x01,0x00,0x03,0x10,0xFF,\
	 0x00,0x01,0x20,0x30,0x30,0x40,0xFF,0xFF,0x20,0x60,\
	 0xC0,0x20,0x60,0xC0,0x20,0x60,0xC0,0x20,0x60,0xC0},\
	 {/*shp_ti_cmn_2k*/
	 0x01,0x00,0x01,0x01,0x00,0x00,0x01,0x01,0x01,0x00,\
	 0x03,0x03},\
	 {/*shp_simple_snr_2k*/
	 0x00, 0x00, 0x01},\
	}
};
/* edge enhance */
const LX_PE_SHP_SR2K_EE_T g_pe_kwrap_p_sr_2k_ee[PE_KWRAP_SHP_STEP] = {\
	{0x00,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
	 0x00,0x00,0x00,0x00}}, \
	{0x10,{0x02,0x04,0x02,0x10,0x10,0x01,0x01,0x01,0x01,\
	 0x00,0x00,0x00,0x00}}, \
	{0x1C,{0x0C,0x14,0x06,0x1C,0x1C,0x01,0x01,0x03,0x03,\
	 0x00,0x00,0x00,0x00}}, \
	{0x20,{0x10,0x18,0x08,0x20,0x20,0x01,0x01,0x04,0x04,\
	 0x00,0x00,0x00,0x00}}, \
	{0x28,{0x18,0x20,0x10,0x28,0x28,0x01,0x01,0x08,0x08,\
	 0x00,0x00,0x00,0x00}}
};
/* detail enhance */
const LX_PE_SHP_SR2K_DE_T g_pe_kwrap_p_sr_2k_de[PE_KWRAP_SHP_STEP] = {\
	{0x00,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
	 0x00,0x00,0x00,0x00}}, \
	{0x10,{0x02,0x02,0x02,0x00,0x00,0x02,0x02,0x02,0x02,\
	 0x10,0x10,0x04,0x04}}, \
	{0x1C,{0x0C,0x0C,0x06,0x00,0x00,0x06,0x06,0x0C,0x0C,\
	 0x1C,0x1C,0x14,0x14}}, \
	{0x20,{0x10,0x10,0x08,0x00,0x00,0x08,0x08,0x10,0x10,\
	 0x20,0x20,0x18,0x18}}, \
	{0x28,{0x18,0x18,0x10,0x00,0x00,0x10,0x10,0x18,0x18,\
	 0x28,0x28,0x20,0x20}}
};
const LX_PE_SHP_RE_EASY_CMN_T g_pe_kwrap_p_sr_easy_cmn[PE_KWRAP_SHP_STEP] = {
	{ 0, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{ 0, {0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10}},
	{ 0, {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18}},
	{ 0, {0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20}},
	{ 0, {0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30}}
};


/*----------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------*/

/*============================================================================
	Implementation Group
============================================================================*/

/**
 * get sr resolution enhance common default settings
 *	- input data : 0~50
 *
 * @param   *param [in/out] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSreRenCmnDefaultSettings(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_SR_RE4_CMN_T ctrl;
		const LX_PE_SHP_SR_RE4_CMN_T *p_data_tbl=NULL;
		UINT8 in=0, out_tbl[PE_KWRAP_SHP_STEP];
		UINT8 in_tbl[PE_KWRAP_SHP_STEP]={0, 10, 25, 30, 50};
		do {
			CHECK_KNULL(ret, param);
			CHECK_KNULL(ret, param->st_data);
			in = (param->data>50)? 50:(UINT8)param->data;
			p_data_tbl = g_pe_kwrap_p_sr_re_cmn4;
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_main_4k[0]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_main_4k[1]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_main_4k[2]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_main_4k[3]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_main_4k[4]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_main_4k[5]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_main_4k[6]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_main_4k[7]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_main_4k[8]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_main_4k[9]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_main_4k[10]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ti_ui_main_4k[0]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ti_ui_main_4k[1]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ti_ui_main_4k[2]);
			memcpy(param->st_data, &ctrl, sizeof(LX_PE_SHP_SR_RE4_CMN_T));
		}while (0);
	}
	else if (PE_KDRV_VER_M17)
	{
		LX_PE_SHP_SR_RE3_CMN_T ctrl;
		const LX_PE_SHP_SR_RE3_CMN_T *p_data_tbl=NULL;
		UINT8 in=0, out_tbl[PE_KWRAP_SHP_STEP];
		UINT8 in_tbl[PE_KWRAP_SHP_STEP]={0, 10, 25, 30, 50};
		do {
			CHECK_KNULL(ret, param);
			CHECK_KNULL(ret, param->st_data);
			in = (param->data>50)? 50:(UINT8)param->data;
			p_data_tbl = g_pe_kwrap_p_sr_re_cmn3;
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_main_pre[0]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_main_pre[1]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_main_pre[2]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_main_pre[3]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_main_pre[4]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_main_pre[5]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_main_pre[6]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_main_pre[7]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_main_pre[8]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_main_pre[9]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_main_pre[10]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_main_pre[11]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_main_pre[12]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_main_pre[13]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ti_ui_main_pre[0]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ti_ui_main_pre[1]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ti_ui_main_pre[2]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_tgen_ui_main_pre[0]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_tgen_ui_main_pre[1]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_tgen_ui_main_pre[2]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_tgen_ui_main_pre[3]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_tgen_ui_main_pre[4]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_tgen_ui_main_pre[5]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_tgen_ui_main_pre[6]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_tgen_ui_main_pre[7]);
			memcpy(param->st_data, &ctrl, sizeof(LX_PE_SHP_SR_RE3_CMN_T));
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set sr resolution enhance common control by specific value
 *	- input data : 0~50
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSreRenCmnCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_SR_RE4_CMN_T ctrl;
		do {
			CHECK_KNULL(ret, param);
			PE_KWRAP_DBG_PRINT(SHP, \
				"wid:%d, data:%d\n", param->wid, param->data);
			param->st_data = (void *)&ctrl;
			ret = KWRAP_PE_GetSreRenCmnDefaultSettings(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_GetSreRenCmnDefaultSettings.\n", __F__, __L__);
			ctrl.win_id = (param->wid>LX_PE_WIN_NUM)? \
				LX_PE_WIN_0:(LX_PE_WIN_ID)param->wid;
			ret = KWRAP_PE_SetSreRenCmnParam((void *)&ctrl);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_SetSreRenCmnParam.\n", __F__, __L__);
		}while (0);
	}
	else if (PE_KDRV_VER_M17)
	{
		LX_PE_SHP_SR_RE3_CMN_T ctrl;
		do {
			CHECK_KNULL(ret, param);
			PE_KWRAP_DBG_PRINT(SHP, \
				"wid:%d, data:%d\n", param->wid, param->data);
			param->st_data = (void *)&ctrl;
			ret = KWRAP_PE_GetSreRenCmnDefaultSettings(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_GetSreRenCmnDefaultSettings.\n", __F__, __L__);
			ctrl.win_id = (param->wid>LX_PE_WIN_NUM)? \
				LX_PE_WIN_0:(LX_PE_WIN_ID)param->wid;
			ret = KWRAP_PE_SetSreRenCmnParam((void *)&ctrl);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_SetSreRenCmnParam.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set sr resolution enhance common parameter
 * - use input struct LX_PE_SHP_SR_RE_CMN_T for H15X
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSreRenCmnParam(void *param)
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
		LX_PE_SHP_SR_RE4_CMN_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_SR_RE4_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_SR_RE4_CMN_T *)param;
			pd = pp->shp_ui_main_4k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_ui_main_pre\n"\
			"shp_ui_main_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_main_4k    [10]0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10]);
			pd = pp->shp_ti_ui_main_4k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_ti_ui_main_pre\n"\
			"shp_ti_ui_main_4k    [00]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_SR_RE4_CMN_T, SHP);
			#endif
			ret = PE_SHP_SetSreReCmnCtrl(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else if (PE_KDRV_VER_M17)
	{
		LX_PE_SHP_SR_RE3_CMN_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_SR_RE3_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_SR_RE3_CMN_T *)param;
			pd = pp->shp_ui_main_pre;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_ui_main_pre\n"\
			"shp_ui_main_pre     [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_main_pre     [10]0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
			pd[10], pd[11], pd[12], pd[13]);
			pd = pp->shp_ti_ui_main_pre;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_ti_ui_main_pre\n"\
			"shp_ti_ui_main_pre  [00]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2]);
			pd = pp->shp_tgen_ui_main_pre;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_tgen_ui_main_pre\n"\
			"shp_tgen_ui_main_pre[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_SR_RE3_CMN_T, SHP);
			#endif
			ret = PE_SHP_SetSreReCmnCtrl(pp);
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
 * get sr resolution enhance common parameter
 * - use input struct LX_PE_SHP_SR_RE_CMN_T for H15X
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSreRenCmnParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = PE_SHP_GetSreReCmnCtrl((LX_PE_SHP_SR_RE4_CMN_T *)param);
	}
	else if(PE_KDRV_VER_M17)
	{
		ret = PE_SHP_GetSreReCmnCtrl((LX_PE_SHP_SR_RE3_CMN_T *)param);
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
 * get sr resolution enhance horizontal default settings
 *	- input data : 0~50
 *
 * @param   *param [in/out] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSreRenHorDefaultSettings(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_SR_RE4_HOR_T ctrl;
		const LX_PE_SHP_SR_RE4_HOR_T *p_data_tbl=NULL;
		UINT8 in=0, out_tbl[PE_KWRAP_SHP_STEP];
		UINT8 in_tbl[PE_KWRAP_SHP_STEP]={0, 10, 25, 30, 50};
		do {
			CHECK_KNULL(ret, param);
			CHECK_KNULL(ret, param->st_data);
			in = (param->data>50)? 50:(UINT8)param->data;
			p_data_tbl = g_pe_kwrap_p_sr_re_hor4;
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_h_main_4k[0]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_h_main_4k[1]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_h_main_4k[2]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_h_main_4k[3]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_h_main_4k[4]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_h_main_4k[5]);
			memcpy(param->st_data, &ctrl, sizeof(LX_PE_SHP_SR_RE4_HOR_T));
		}while (0);
	}
	else if (PE_KDRV_VER_M17)
	{
		LX_PE_SHP_SR_RE3_HOR_T ctrl;
		const LX_PE_SHP_SR_RE3_HOR_T *p_data_tbl=NULL;
		UINT8 in=0, out_tbl[PE_KWRAP_SHP_STEP];
		UINT8 in_tbl[PE_KWRAP_SHP_STEP]={0, 10, 25, 30, 50};
		do {
			CHECK_KNULL(ret, param);
			CHECK_KNULL(ret, param->st_data);
			in = (param->data>50)? 50:(UINT8)param->data;
			p_data_tbl = g_pe_kwrap_p_sr_re_hor3;
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_h_main_pre[0]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_h_main_pre[1]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_h_main_pre[2]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_h_main_pre[3]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_h_main_pre[4]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_h_main_pre[5]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_h_main_pre[6]);
			memcpy(param->st_data, &ctrl, sizeof(LX_PE_SHP_SR_RE3_HOR_T));
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set sr resolution enhance horizontal by specific value
 *	- input data : 0~50
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSreRenHorCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_SR_RE4_HOR_T ctrl;
		ret = KWRAP_PE_SetDefaultParam(param, \
			PE_KWRAP_DFLT_PARAM_SRS_HOR, (void *)&ctrl, __F__, __L__);
	}
	else if (PE_KDRV_VER_M17)
	{
		LX_PE_SHP_SR_RE3_HOR_T ctrl;
		ret = KWRAP_PE_SetDefaultParam(param, \
			PE_KWRAP_DFLT_PARAM_SRS_HOR, (void *)&ctrl, __F__, __L__);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set sr resolution enhance horizontal parameter
 * - use input struct LX_PE_SHP_RE2_HOR_T for H15, M14BX
 * - use input struct LX_PE_SHP_RE1_HOR_T for H13AX
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSreRenHorParam(void *param)
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
		LX_PE_SHP_SR_RE4_HOR_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_SR_RE4_HOR_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_SR_RE4_HOR_T *)param;
			pd = pp->shp_ui_h_main_4k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_ui_h_main_k\n"\
			"shp_ui_h_main_4k	 [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_SR_RE4_HOR_T, HST);
			#endif
			ret = PE_SHP_SetSreReHorCtrl(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else if (PE_KDRV_VER_M17)
	{
		LX_PE_SHP_SR_RE3_HOR_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_SR_RE3_HOR_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_SR_RE3_HOR_T *)param;
			pd = pp->shp_ui_h_main_pre;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_ui_h_main_pre\n"\
			"shp_ui_h_main_pre[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n", \
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_SR_RE3_HOR_T, HST);
			#endif
			ret = PE_SHP_SetSreReHorCtrl(pp);
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
 * get sr resolution enhance horizontal parameter
 * - use input struct LX_PE_SHP_RE2_HOR_T for H15, M14BX
 * - use input struct LX_PE_SHP_RE1_HOR_T for H13AX
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSreRenHorParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = PE_SHP_GetSreReHorCtrl((LX_PE_SHP_SR_RE4_HOR_T *)param);
	}
	else if (PE_KDRV_VER_M17)
	{
		ret = PE_SHP_GetSreReHorCtrl((LX_PE_SHP_SR_RE3_HOR_T *)param);
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
 * get sr resolution enhance vertical default settings
 *	- input data : 0~50
 *
 * @param   *param [in/out] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSreRenVerDefaultSettings(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_SR_RE4_VER_T ctrl;
		const LX_PE_SHP_SR_RE4_VER_T *p_data_tbl=NULL;
		UINT8 in=0, out_tbl[PE_KWRAP_SHP_STEP];
		UINT8 in_tbl[PE_KWRAP_SHP_STEP]={0, 10, 25, 30, 50};
		do {
			CHECK_KNULL(ret, param);
			CHECK_KNULL(ret, param->st_data);
			in = (param->data>50)? 50:(UINT8)param->data;
			p_data_tbl = g_pe_kwrap_p_sr_re_ver4;
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_v_main_4k[0]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_v_main_4k[1]);
			memcpy(param->st_data, &ctrl, sizeof(LX_PE_SHP_SR_RE4_VER_T));
		}while (0);
	}
	else if (PE_KDRV_VER_M17)
	{
		LX_PE_SHP_SR_RE3_VER_T ctrl;
		const LX_PE_SHP_SR_RE3_VER_T *p_data_tbl=NULL;
		UINT8 in=0, out_tbl[PE_KWRAP_SHP_STEP];
		UINT8 in_tbl[PE_KWRAP_SHP_STEP]={0, 10, 25, 30, 50};
		do {
			CHECK_KNULL(ret, param);
			CHECK_KNULL(ret, param->st_data);
			in = (param->data>50)? 50:(UINT8)param->data;
			p_data_tbl = g_pe_kwrap_p_sr_re_ver3;
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_v_main_pre[0]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_v_main_pre[1]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_v_main_pre[2]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_v_main_pre[3]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_v_main_pre[4]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_v_main_pre[5]);
			memcpy(param->st_data, &ctrl, sizeof(LX_PE_SHP_SR_RE3_VER_T));
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set sr resolution enhance vertical by specific value
 *	- input data : 0~50
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSreRenVerCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_SR_RE4_VER_T ctrl;
		do {
			CHECK_KNULL(ret, param);
			PE_KWRAP_DBG_PRINT(SHP, \
				"wid:%d, data:%d\n", param->wid, param->data);
			param->st_data = (void *)&ctrl;
			ret = KWRAP_PE_GetSreRenVerDefaultSettings(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_GetSreRenVerDefaultSettings.\n", __F__, __L__);
			ctrl.win_id = (param->wid>LX_PE_WIN_NUM)? \
				LX_PE_WIN_0:(LX_PE_WIN_ID)param->wid;
			ret = KWRAP_PE_SetSreRenVerParam((void *)&ctrl);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_SetSreRenVerParam.\n", __F__, __L__);
		}while (0);
	}
	else if (PE_KDRV_VER_M17)
	{
		LX_PE_SHP_SR_RE3_VER_T ctrl;
		do {
			CHECK_KNULL(ret, param);
			PE_KWRAP_DBG_PRINT(SHP, \
				"wid:%d, data:%d\n", param->wid, param->data);
			param->st_data = (void *)&ctrl;
			ret = KWRAP_PE_GetSreRenVerDefaultSettings(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_GetSreRenVerDefaultSettings.\n", __F__, __L__);
			ctrl.win_id = (param->wid>LX_PE_WIN_NUM)? \
				LX_PE_WIN_0:(LX_PE_WIN_ID)param->wid;
			ret = KWRAP_PE_SetSreRenVerParam((void *)&ctrl);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_SetSreRenVerParam.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set sr resolution enhance vertical parameter
 * - use input struct LX_PE_SHP_SR_RE_VER_T for H15X
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSreRenVerParam(void *param)
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
		LX_PE_SHP_SR_RE4_VER_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_SR_RE4_VER_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_SR_RE4_VER_T *)param;
			pd = pp->shp_ui_v_main_4k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_ui_v_main_4k\n"\
			"shp_ui_v_main_4k	 [00]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_SR_RE4_VER_T, SHP);
			#endif
			ret = PE_SHP_SetSreReVerCtrl(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else if (PE_KDRV_VER_M17)
	{
		LX_PE_SHP_SR_RE3_VER_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_SR_RE3_VER_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_SR_RE3_VER_T *)param;
			pd = pp->shp_ui_v_main_pre;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_ui_v_main_pre\n"\
			"shp_ui_v_main_pre[00] 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],pd[2],  pd[3],pd[4],  pd[5]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_SR_RE3_VER_T, SHP);
			#endif
			ret = PE_SHP_SetSreReVerCtrl(pp);
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
 * get sr resolution enhance vertical parameter
 * - use input struct LX_PE_SHP_SR_RE_VER_T for H15X
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSreRenVerParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = PE_SHP_GetSreReVerCtrl((LX_PE_SHP_SR_RE4_VER_T *)param);
	}
	else if (PE_KDRV_VER_M17)
	{
		ret = PE_SHP_GetSreReVerCtrl((LX_PE_SHP_SR_RE3_VER_T *)param);
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
 * get sr resolution enhance misc default settings
 *	- input data : see PE_KWRAP_SHP_FMT_TYPE
 *
 * @param   *param [in/out] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSreRenMiscDefaultSettings(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	UINT32 param_data = 0;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		const LX_PE_SHP_SR_RE4_MISC_T *pp=NULL;
		do {
			const UINT8 *pd;
			CHECK_KNULL(ret, param);
			CHECK_KNULL(ret, param->st_data);
			param_data = (param->data<PE_KWRAP_SHP_FMT_NUM)? \
				param->data:PE_KWRAP_SHP_FMT_SD;
			pp = &(g_pe_kwrap_p_sr_re_misc4[param_data]);
			memcpy(param->st_data, pp, sizeof(LX_PE_SHP_SR_RE4_MISC_T));
			pd = pp->shp_cmn_4k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] :  resolution misc ctrl\n"\
			"shp_cmn_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_4k    [20]0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20]);
			pd = pp->shp_map_cmn_4k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] :  resolution misc ctrl\n"\
			"shp_map_cmn_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19]);
			pd = pp->shp_balance_4k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] :  resolution misc ctrl\n"\
			"shp_balance_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_4k    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);
			pd = pp->shp_ti_cmn_4k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] :  resolution misc ctrl\n"\
			"shp_ti_cmn_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_4k    [10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);
			pd = pp->shp_simple_snr_4k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] :  resolution misc ctrl\n"\
			"shp_simple_snr_4k    [00]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2]);
		}while (0);
	}
	else if (PE_KDRV_VER_M17)
	{
		const LX_PE_SHP_SR_RE3_MISC_T *pp=NULL;
		do {
			const UINT8 *pd;
			CHECK_KNULL(ret, param);
			CHECK_KNULL(ret, param->st_data);
			param_data = (param->data<PE_KWRAP_SHP_FMT_NUM)? \
				param->data:PE_KWRAP_SHP_FMT_SD;
			pp = &(g_pe_kwrap_p_sr_re_misc3[param_data]);
			memcpy(param->st_data, pp, sizeof(LX_PE_SHP_SR_RE3_MISC_T));
			pd = pp->shp_cmn_pre;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] :  resolution misc ctrl\n"\
			"shp_cmn_pre	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_pre	  [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_pre	  [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
				pp->win_id, \
				pd[0],	pd[1],	pd[2],	pd[3],	pd[4],	pd[5],	pd[6],	pd[7],	pd[8],	pd[9], \
				pd[10], pd[11], pd[12], pd[13],  pd[14],  pd[15],  pd[16],	pd[17],  pd[18],  pd[19], \
				pd[20], pd[21], pd[22], pd[23],  pd[24],  pd[25],  pd[26],	pd[27],  pd[28],  pd[29]);
			pd = pp->shp_map_cmn_pre;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] :  resolution misc ctrl\n"\
			"shp_map_cmn_pre [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_pre [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_pre [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_pre [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_pre [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n", \
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11], pd[12],	pd[13],  pd[14],  pd[15],  pd[16],  pd[17],  pd[18],  pd[19], \
				pd[20], pd[21], pd[22],	pd[23],  pd[24],  pd[25],  pd[26],  pd[27],  pd[28],  pd[29], \
				pd[30], pd[31], pd[32],	pd[33],  pd[34],  pd[35],  pd[36],  pd[37],  pd[38],  pd[39], \
				pd[40], pd[41], pd[42],	pd[43],  pd[44],  pd[45],  pd[46],  pd[47],  pd[48]);
			pd = pp->shp_balance_pre;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] :  resolution misc ctrl\n"\
			"shp_balance_pre [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_pre [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_pre [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_pre [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_pre [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_pre [50]0x%02X,0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],   pd[4],   pd[5],   pd[6],   pd[7],   pd[8],   pd[9], \
				pd[10], pd[11], pd[12],	pd[13],  pd[14],  pd[15],  pd[16],  pd[17],  pd[18],  pd[19], \
				pd[20], pd[21], pd[22],	pd[23],  pd[24],  pd[25],  pd[26],  pd[27],  pd[28],  pd[29], \
				pd[30], pd[31], pd[32],	pd[33],  pd[34],  pd[35],  pd[36],  pd[37],  pd[38],  pd[39], \
				pd[40], pd[41], pd[42],	pd[43],  pd[44],  pd[45],  pd[46],  pd[47],  pd[48],  pd[49], \
				pd[50], pd[51], pd[52]);
			pd = pp->shp_ti_cmn_pre;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] :  resolution misc ctrl\n"\
			"shp_ti_cmn_pre  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_pre  [10]0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11]);
			pd = pp->shp_tgen_cmn_pre;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] :  resolution misc ctrl\n"\
			"shp_tgen_cmn_pre [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_tgen_cmn_pre [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_tgen_cmn_pre [20]0x%02X,0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],   pd[4],   pd[5],   pd[6],   pd[7],   pd[8],   pd[9], \
				pd[10], pd[11], pd[12],	pd[13],  pd[14],  pd[15],  pd[16],  pd[17],  pd[18],  pd[19], \
				pd[20], pd[21], pd[22]);
			
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}

/**
 * set sr resolution enhance misc by specific value
 *	- input data : see PE_KWRAP_SHP_FMT_TYPE
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSreRenMiscCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_SR_RE4_MISC_T ctrl;
		do {
			CHECK_KNULL(ret, param);
			PE_KWRAP_DBG_PRINT(SHP, \
				"wid:%d, data:%d\n", param->wid, param->data);
			param->st_data = (void *)&ctrl;
			ret = KWRAP_PE_GetSreRenMiscDefaultSettings(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_GetRenMiscDefaultSettings.\n", __F__, __L__);
			ctrl.win_id = (param->wid>LX_PE_WIN_NUM)? \
				LX_PE_WIN_0:(LX_PE_WIN_ID)param->wid;
			ret = KWRAP_PE_SetSreRenMiscParam((void *)&ctrl);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_SetSreRenMiscParam.\n", __F__, __L__);
		}while (0);
	}
	else if (PE_KDRV_VER_M17)
	{
		LX_PE_SHP_SR_RE3_MISC_T ctrl;
		do {
			CHECK_KNULL(ret, param);
			PE_KWRAP_DBG_PRINT(SHP, \
				"wid:%d, data:%d\n", param->wid, param->data);
			param->st_data = (void *)&ctrl;
			ret = KWRAP_PE_GetSreRenMiscDefaultSettings(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_GetRenMiscDefaultSettings.\n", __F__, __L__);
			ctrl.win_id = (param->wid>LX_PE_WIN_NUM)? \
				LX_PE_WIN_0:(LX_PE_WIN_ID)param->wid;
			ret = KWRAP_PE_SetSreRenMiscParam((void *)&ctrl);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_SetSreRenMiscParam.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set sr resolution enhance misc parameter
 * - use input struct LX_PE_SHP_SR_RE_MISC_T for H15X
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSreRenMiscParam(void *param)
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
		LX_PE_SHP_SR_RE4_MISC_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_SR_RE4_MISC_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_SR_RE4_MISC_T *)param;
			pd = pp->shp_cmn_4k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] :  resolution misc ctrl\n"\
			"shp_cmn_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_4k    [20]0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20]);
			pd = pp->shp_map_cmn_4k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] :  resolution misc ctrl\n"\
			"shp_map_cmn_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19]);
			pd = pp->shp_balance_4k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] :  resolution misc ctrl\n"\
			"shp_balance_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_4k    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);
			pd = pp->shp_ti_cmn_4k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] :  resolution misc ctrl\n"\
			"shp_ti_cmn_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_4k    [10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);
			pd = pp->shp_simple_snr_4k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] :  resolution misc ctrl\n"\
			"shp_simple_snr_4k    [00]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_SR_RE4_MISC_T, SHP);
			#endif
			ret = PE_SHP_SetSreReMiscCtrl(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else if (PE_KDRV_VER_M17)
	{
		LX_PE_SHP_SR_RE3_MISC_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_SR_RE3_MISC_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_SR_RE3_MISC_T *)param;
			pd = pp->shp_cmn_pre;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] :  resolution misc ctrl\n"\
			"shp_cmn_pre     [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_pre     [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_pre     [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11], pd[12],	pd[13],  pd[14],  pd[15],  pd[16],  pd[17],  pd[18],  pd[19], \
				pd[20], pd[21], pd[22],	pd[23],  pd[24],  pd[25],  pd[26],  pd[27],  pd[28],  pd[29]);
			pd = pp->shp_map_cmn_pre;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] :  resolution misc ctrl\n"\
			"shp_map_cmn_pre [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_pre [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_pre [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_pre [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_pre [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n", \
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11], pd[12],	pd[13],  pd[14],  pd[15],  pd[16],  pd[17],  pd[18],  pd[19], \
				pd[20], pd[21], pd[22],	pd[23],  pd[24],  pd[25],  pd[26],  pd[27],  pd[28],  pd[29], \
				pd[30], pd[31], pd[32],	pd[33],  pd[34],  pd[35],  pd[36],  pd[37],  pd[38],  pd[39], \
				pd[40], pd[41], pd[42],	pd[43],  pd[44],  pd[45],  pd[46],  pd[47]);
			pd = pp->shp_balance_pre;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] :  resolution misc ctrl\n"\
			"shp_balance_pre [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_pre [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_pre [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_pre [30]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_pre [40]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_pre [50]0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],   pd[4],   pd[5],   pd[6],   pd[7],   pd[8],   pd[9], \
				pd[10], pd[11], pd[12],	pd[13],  pd[14],  pd[15],  pd[16],  pd[17],  pd[18],  pd[19], \
				pd[20], pd[21], pd[22],	pd[23],  pd[24],  pd[25],  pd[26],  pd[27],  pd[28],  pd[29], \
				pd[30], pd[31], pd[32],	pd[33],  pd[34],  pd[35],  pd[36],  pd[37],  pd[38],  pd[39], \
				pd[40], pd[41], pd[42],	pd[43],  pd[44],  pd[45],  pd[46],  pd[47],  pd[48],  pd[49], \
				pd[50], pd[51]);
			pd = pp->shp_ti_cmn_pre;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] :  resolution misc ctrl\n"\
			"shp_ti_cmn_pre  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_pre  [10]0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11]);
			pd = pp->shp_tgen_cmn_pre;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] :  resolution misc ctrl\n"\
			"shp_tgen_cmn_pre[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_tgen_cmn_pre[10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_tgen_cmn_pre[20]0x%02X,0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9], \
				pd[10], pd[11], pd[12],	pd[13],  pd[14],  pd[15],  pd[16],  pd[17],  pd[18],  pd[19], \
				pd[20], pd[21], pd[22]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_SR_RE3_MISC_T, SHP);
			#endif
			ret = PE_SHP_SetSreReMiscCtrl(pp);
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
 * get sr resolution enhance misc parameter
 * - use input struct LX_PE_SHP_SR_RE_MISC_T for H15X
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSreRenMiscParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = PE_SHP_GetSreReMiscCtrl((LX_PE_SHP_SR_RE4_MISC_T *)param);
	}
	else if (PE_KDRV_VER_M17)
	{
		ret = PE_SHP_GetSreReMiscCtrl((LX_PE_SHP_SR_RE3_MISC_T *)param);
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
 * get sr edge enhancemen default settings
 *	- input data : 0~50
 *
 * @param   *param [in/out] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSreEdgeEnhanceDefaultSettings(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_SR_EE4_T ctrl;
		const LX_PE_SHP_SR_EE4_T *p_data_tbl=NULL;
		UINT8 in=0, out_tbl[PE_KWRAP_SHP_STEP];
		UINT8 in_tbl[PE_KWRAP_SHP_STEP]={0, 10, 25, 30, 50};
		do {
			CHECK_KNULL(ret, param);
			CHECK_KNULL(ret, param->st_data);
			in = (param->data>50)? 50:(UINT8)param->data;
			p_data_tbl = g_pe_kwrap_p_sr_ee4;
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_4k[0]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_4k[1]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_4k[2]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_4k[3]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_4k[4]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_4k[5]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_4k[6]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_4k[7]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_4k[8]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_4k[9]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_4k[10]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_4k[11]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_4k[12]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_4k[13]);
			memcpy(param->st_data, &ctrl, sizeof(LX_PE_SHP_SR_EE4_T));
		}while (0);
	}
	else if (PE_KDRV_VER_M17)
	{
		LX_PE_SHP_SR_EE3_T ctrl;
		const LX_PE_SHP_SR_EE3_T *p_data_tbl=NULL;
		UINT8 in=0, out_tbl[PE_KWRAP_SHP_STEP];
		UINT8 in_tbl[PE_KWRAP_SHP_STEP]={0, 10, 25, 30, 50};
		do {
			CHECK_KNULL(ret, param);
			CHECK_KNULL(ret, param->st_data);
			in = (param->data>50)? 50:(UINT8)param->data;
			p_data_tbl = g_pe_kwrap_p_sr_ee3;
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_pre[0]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_pre[1]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_pre[2]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_pre[3]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_pre[4]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_pre[5]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_pre[6]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_pre[7]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_pre[8]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_pre[9]);
			memcpy(param->st_data, &ctrl, sizeof(LX_PE_SHP_SR_EE3_T));
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set sr edge enhancement by specific value
 *	- input data : 0~50
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSreEdgeEnhanceCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_SR_EE4_T ctrl;
		do {
			CHECK_KNULL(ret, param);
			PE_KWRAP_DBG_PRINT(SHP, \
				"wid:%d, data:%d\n", param->wid, param->data);
			param->st_data = (void *)&ctrl;
			ret = KWRAP_PE_GetSreEdgeEnhanceDefaultSettings(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_GetSreEdgeEnhanceDefaultSettings.\n", __F__, __L__);
			ctrl.win_id = (param->wid>LX_PE_WIN_NUM)? \
				LX_PE_WIN_0:(LX_PE_WIN_ID)param->wid;
			ret = KWRAP_PE_SetSreEdgeEnhanceParam((void *)&ctrl);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_SetSreEdgeEnhanceParam.\n", __F__, __L__);
		}while (0);
	}
	else if (PE_KDRV_VER_M17)
	{
		LX_PE_SHP_SR_EE3_T ctrl;
		do {
			CHECK_KNULL(ret, param);
			PE_KWRAP_DBG_PRINT(SHP, \
				"wid:%d, data:%d\n", param->wid, param->data);
			param->st_data = (void *)&ctrl;
			ret = KWRAP_PE_GetSreEdgeEnhanceDefaultSettings(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_GetSreEdgeEnhanceDefaultSettings.\n", __F__, __L__);
			ctrl.win_id = (param->wid>LX_PE_WIN_NUM)? \
				LX_PE_WIN_0:(LX_PE_WIN_ID)param->wid;
			ret = KWRAP_PE_SetSreEdgeEnhanceParam((void *)&ctrl);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_SetSreEdgeEnhanceParam.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set sr edge enhancement parameter
 * - use input struct LX_PE_SHP_SR_EE_T for H15X
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSreEdgeEnhanceParam(void *param)
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
		LX_PE_SHP_SR_EE4_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_SR_EE4_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_SR_EE4_T *)param;
			pd = pp->shp_ee_4k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_ee_pre\n"\
			"shp_ee_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_SR_EE4_T, SHP);
			#endif
			ret = PE_SHP_SetSreEdgeEnhanceCtrl(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else if (PE_KDRV_VER_M17)
	{
		LX_PE_SHP_SR_EE3_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_SR_EE3_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_SR_EE3_T *)param;
			pd = pp->shp_ee_pre;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_ee_pre\n"\
			"shp_ee_pre[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_SR_EE3_T, SHP);
			#endif
			ret = PE_SHP_SetSreEdgeEnhanceCtrl(pp);
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
 * set sr edge enhancement parameter
 * - use input struct LX_PE_SHP_SR_EE_T for H15X
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSreEdgeEnhanceParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = PE_SHP_GetSreEdgeEnhanceCtrl((LX_PE_SHP_SR_EE4_T *)param);
	}
	else if (PE_KDRV_VER_M17)
	{
		ret = PE_SHP_GetSreEdgeEnhanceCtrl((LX_PE_SHP_SR_EE3_T *)param);
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
 * get sre detail enhancemen default settings
 *	- input data : 0~50
 *
 * @param   *param [in/out] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSreDetailEnhanceDefaultSettings(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_SR_DE4_T ctrl;
		const LX_PE_SHP_SR_DE4_T *data_tbl=NULL;
		UINT8 in=0, out_tbl[PE_KWRAP_SHP_STEP];
		UINT8 in_tbl[PE_KWRAP_SHP_STEP]={0, 10, 25, 30, 50};
		do {
			CHECK_KNULL(ret, param);
			CHECK_KNULL(ret, param->st_data);
			in = (param->data>50)? 50:(UINT8)param->data;
			data_tbl = g_pe_kwrap_p_sr_de4;
			PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_4k[0]);
			PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_4k[1]);
			PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_4k[2]);
			PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_4k[3]);
			PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_4k[4]);
			PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_4k[5]);
			PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_4k[6]);
			PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_4k[7]);
			PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_4k[8]);
			PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_4k[9]);
			PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_4k[10]);
			PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_4k[11]);
			PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_4k[12]);
			PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_4k[13]);
			memcpy(param->st_data, &ctrl, sizeof(LX_PE_SHP_SR_DE4_T));
		}while (0);
	}
	else if (PE_KDRV_VER_M17)
	{
		LX_PE_SHP_SR_DE3_T ctrl;
		const LX_PE_SHP_SR_DE3_T *data_tbl=NULL;
		UINT8 in=0, out_tbl[PE_KWRAP_SHP_STEP];
		UINT8 in_tbl[PE_KWRAP_SHP_STEP]={0, 10, 25, 30, 50};
		do {
			CHECK_KNULL(ret, param);
			CHECK_KNULL(ret, param->st_data);
			in = (param->data>50)? 50:(UINT8)param->data;
			data_tbl = g_pe_kwrap_p_sr_de3;
			PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_pre[0]);
			PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_pre[1]);
			PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_pre[2]);
			PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_pre[3]);
			PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_pre[4]);
			PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_pre[5]);
			PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_pre[6]);
			PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_pre[7]);
			PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_pre[8]);
			PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_pre[9]);
			memcpy(param->st_data, &ctrl, sizeof(LX_PE_SHP_SR_DE3_T));
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set sr detail enhancement by specific value
 *	- input data : 0~50
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSreDetailEnhanceCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_SR_DE4_T ctrl;
		ret = KWRAP_PE_SetDefaultParam(param, \
			PE_KWRAP_DFLT_PARAM_SRS_DTL, (void *)&ctrl, __F__, __L__);
	}
	else if (PE_KDRV_VER_M17)
	{
		LX_PE_SHP_SR_DE3_T ctrl;
		ret = KWRAP_PE_SetDefaultParam(param, \
			PE_KWRAP_DFLT_PARAM_SRS_DTL, (void *)&ctrl, __F__, __L__);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set sr detail enhancement parameter
 * - use input struct LX_PE_SHP_DE1_T for H15x
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSreDetailEnhanceParam(void *param)
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
		LX_PE_SHP_SR_DE4_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_SR_DE4_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_SR_DE4_T *)param;
			pd = pp->shp_de_4k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_ee_pre\n"\
			"shp_de_4k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_de_4k    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_SR_DE4_T, SHP);
			#endif
			ret = PE_SHP_SetSreDetailEnhanceCtrl(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else if (PE_KDRV_VER_M17)
	{
		LX_PE_SHP_SR_DE3_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_SR_DE3_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_SR_DE3_T *)param;
			pd = pp->shp_de_pre;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_ee_pre\n"\
			"shp_ee_pre[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",\
			pp->win_id, \
			pd[0],  pd[1],  pd[2],  pd[3],  pd[4],  pd[5],  pd[6],  pd[7],  pd[8],  pd[9]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_SR_DE3_T, SHP);
			#endif
			ret = PE_SHP_SetSreDetailEnhanceCtrl(pp);
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
 * get detail enhancement parameter
 * - use input struct LX_PE_SHP_DE1_T for H15X
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSreDetailEnhanceParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = PE_SHP_GetSreDetailEnhanceCtrl((LX_PE_SHP_SR_DE4_T *)param);
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
 * get sr resolution enhance common default settings
 *	- input data : 0~50
 *
 * @param   *param [in/out] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSre2KRenCmnDefaultSettings(PE_KWRAP_CTRL_T *param)
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
		p_data_tbl = g_pe_kwrap_p_sr_easy_cmn;
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
 * set sr resolution enhance common control by specific value
 *	- input data : 0~50
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSre2KRenCmnCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	LX_PE_SHP_RE_EASY_CMN_T ctrl;
	do {
		CHECK_KNULL(ret, param);
		PE_KWRAP_DBG_PRINT(SHP, \
			"wid:%d, data:%d\n", param->wid, param->data);
		param->st_data = (void *)&ctrl;
		ret = KWRAP_PE_GetSre2KRenCmnDefaultSettings(param);
		PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]KWRAP_PE_GetSre2KRenCmnDefaultSettings.\n", __F__, __L__);
		ctrl.win_id = (param->wid>LX_PE_WIN_NUM)? \
			LX_PE_WIN_0:(LX_PE_WIN_ID)param->wid;
		ret = KWRAP_PE_SetSre2KRenEasyCmnParam((void *)&ctrl);
		PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]KWRAP_PE_SetSre2KRenCmnParam.\n", __F__, __L__);
	}while (0);
	return ret;
}
/**
 * set sr resolution enhance common parameter
 * - use input struct LX_PE_SHP_SR_RE_CMN_T for H15X
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSre2KRenCmnParam(void *param)
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
		LX_PE_SHP_SR2K_RE2_CMN_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_SR2K_RE2_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_SR2K_RE2_CMN_T *)param;
			pd = pp->shp_ui_main_2k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_ui_main_2k\n"\
				"shp_ui_main_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_ui_main_vsd	[10]0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
				pd[10], pd[11]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_SR2K_RE2_CMN_T, SHP);
			#endif
			ret = PE_SHP_SetSre2KReCmnCtrl(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else if(PE_KDRV_VER_O20)
	{
		LX_PE_SHP_SR2K_RE1_CMN_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_SR2K_RE1_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_SR2K_RE1_CMN_T *)param;
			pd = pp->shp_ui_main_2k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_ui_main_2k\n"\
				"shp_ui_main_vsd	[00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
				"shp_ui_main_vsd	[10]0x%02X,0x%02X\n",\
				pp->win_id, \
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
				pd[10], pd[11]);
			pd = (UINT8 *)pp->shp_dnn_sr_vsd;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_dnn_sr_vsd\n"\
				"shp_dnn_sr_vsd	 [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
				pp->win_id, \
				pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_SR2K_RE1_CMN_T, SHP);
			#endif
			ret = PE_SHP_SetSre2KReCmnCtrl(pp);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_SR2K_RE_CMN_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_SR2K_RE_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_SR2K_RE_CMN_T *)param;
			pd = pp->shp_ui_main_2k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_ui_main_2k\n"\
			"shp_ui_main_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ui_main_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);
			pd = pp->shp_ti_ui_main_2k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_ti_ui_main_2k\n"\
			"shp_ti_ui_main_2k    [00]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_SR2K_RE_CMN_T, SHP);
			#endif
			ret = PE_SHP_SetSre2KReCmnCtrl(pp);
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
 * get sr resolution enhance common parameter
 * - use input struct LX_PE_SHP_SR_RE_CMN_T for H15X
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSre2KRenCmnParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = PE_SHP_GetSre2KReCmnCtrl(param);
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
 * get sr resolution enhance horizontal default settings
 *	- input data : 0~50
 *
 * @param   *param [in/out] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSre2KRenHorDefaultSettings(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_SR2K_RE_HOR_T ctrl;
		const LX_PE_SHP_SR2K_RE_HOR_T *p_data_tbl=NULL;
		UINT8 in=0, out_tbl[PE_KWRAP_SHP_STEP];
		UINT8 in_tbl[PE_KWRAP_SHP_STEP]={0, 10, 25, 30, 50};
		do {
			CHECK_KNULL(ret, param);
			CHECK_KNULL(ret, param->st_data);
			in = (param->data>50)? 50:(UINT8)param->data;
			p_data_tbl = g_pe_kwrap_p_sr_2k_re_hor;
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_h_main_2k[0]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_h_main_2k[1]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_h_main_2k[2]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_h_main_2k[3]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_h_main_2k[4]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_h_main_2k[5]);
			memcpy(param->st_data, &ctrl, sizeof(LX_PE_SHP_SR2K_RE_HOR_T));
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set sr resolution enhance horizontal by specific value
 *	- input data : 0~50
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSre2KRenHorCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_SR2K_RE_HOR_T ctrl;
		do {
			CHECK_KNULL(ret, param);
			PE_KWRAP_DBG_PRINT(SHP, \
				"wid:%d, data:%d\n", param->wid, param->data);
			param->st_data = (void *)&ctrl;
			ret = KWRAP_PE_GetSre2KRenHorDefaultSettings(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_GetSre2KRenHorDefaultSettings.\n", __F__, __L__);
			ctrl.win_id = (param->wid>LX_PE_WIN_NUM)? \
				LX_PE_WIN_0:(LX_PE_WIN_ID)param->wid;
			ret = KWRAP_PE_SetSre2KRenHorParam((void *)&ctrl);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_SetSre2KRenHorParam.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set sr resolution enhance horizontal parameter
 * - use input struct LX_PE_SHP_RE2_HOR_T for H15, M14BX
 * - use input struct LX_PE_SHP_RE1_HOR_T for H13AX
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSre2KRenHorParam(void *param)
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
		LX_PE_SHP_SR2K_RE_HOR_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_SR2K_RE_HOR_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_SR2K_RE_HOR_T *)param;
			pd = pp->shp_ui_h_main_2k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_ui_h_main_2k\n"\
			"shp_ui_h_main_2k	 [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_SR2K_RE_HOR_T, HST);
			#endif
			ret = PE_SHP_SetSre2KReHorCtrl(param);
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
 * get sr resolution enhance horizontal parameter
 * - use input struct LX_PE_SHP_RE2_HOR_T for H15, M14BX
 * - use input struct LX_PE_SHP_RE1_HOR_T for H13AX
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSre2KRenHorParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = PE_SHP_GetSre2KReHorCtrl(param);
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
 * get sr resolution enhance vertical default settings
 *	- input data : 0~50
 *
 * @param   *param [in/out] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSre2KRenVerDefaultSettings(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_SR2K_RE_VER_T ctrl;
		const LX_PE_SHP_SR2K_RE_VER_T *p_data_tbl=NULL;
		UINT8 in=0, out_tbl[PE_KWRAP_SHP_STEP];
		UINT8 in_tbl[PE_KWRAP_SHP_STEP]={0, 10, 25, 30, 50};
		do {
			CHECK_KNULL(ret, param);
			CHECK_KNULL(ret, param->st_data);
			in = (param->data>50)? 50:(UINT8)param->data;
			p_data_tbl = g_pe_kwrap_p_sr_2k_re_ver;
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_v_main_2k[0]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ui_v_main_2k[1]);
			memcpy(param->st_data, &ctrl, sizeof(LX_PE_SHP_SR2K_RE_VER_T));
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set sr resolution enhance vertical by specific value
 *	- input data : 0~50
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSre2KRenVerCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_SR2K_RE_VER_T ctrl;
		do {
			CHECK_KNULL(ret, param);
			PE_KWRAP_DBG_PRINT(SHP, \
				"wid:%d, data:%d\n", param->wid, param->data);
			param->st_data = (void *)&ctrl;
			ret = KWRAP_PE_GetSre2KRenVerDefaultSettings(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_GetSre2KRenVerDefaultSettings.\n", __F__, __L__);
			ctrl.win_id = (param->wid>LX_PE_WIN_NUM)? \
				LX_PE_WIN_0:(LX_PE_WIN_ID)param->wid;
			ret = KWRAP_PE_SetSre2KRenVerParam((void *)&ctrl);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_SetSre2KRenVerParam.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set sr resolution enhance vertical parameter
 * - use input struct LX_PE_SHP_SR_RE_VER_T for H15X
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSre2KRenVerParam(void *param)
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
		LX_PE_SHP_SR2K_RE_VER_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_SR2K_RE_VER_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_SR2K_RE_VER_T *)param;
			pd = pp->shp_ui_v_main_2k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_ui_v_main_4k\n"\
			"shp_ui_v_main_2k	 [00]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_SR2K_RE_VER_T, SHP);
			#endif
			ret = PE_SHP_SetSre2KReVerCtrl((void *)pp);
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
 * get sr resolution enhance vertical parameter
 * - use input struct LX_PE_SHP_SR_RE_VER_T for H15X
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSre2KRenVerParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = PE_SHP_GetSre2KReVerCtrl(param);
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
 * get sr resolution enhance misc default settings
 *	- input data : see PE_KWRAP_SHP_FMT_TYPE
 *
 * @param   *param [in/out] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSre2KRenMiscDefaultSettings(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	UINT32 param_data = 0;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		const LX_PE_SHP_SR2K_RE_MISC_T *pp=NULL;
		do {
			const UINT8 *pd;
			CHECK_KNULL(ret, param);
			CHECK_KNULL(ret, param->st_data);
			param_data = (param->data<PE_KWRAP_SHP_FMT_NUM)? \
				param->data:PE_KWRAP_SHP_FMT_SD;
			pp = &(g_pe_kwrap_p_sr_2k_re_misc[param_data]);
			memcpy(param->st_data, pp, sizeof(LX_PE_SHP_SR2K_RE_MISC_T));
			pd = pp->shp_cmn_2k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] :  resolution misc ctrl\n"\
			"shp_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18]);
			pd = pp->shp_map_cmn_2k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] :  resolution misc ctrl\n"\
			"shp_map_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19]);
			pd = pp->shp_balance_2k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] :  resolution misc ctrl\n"\
			"shp_balance_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_2k    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);
			pd = pp->shp_ti_cmn_2k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] :  resolution misc ctrl\n"\
			"shp_ti_cmn_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_2k	  [10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);
			pd = pp->shp_simple_snr_2k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"get[%d] :  resolution misc ctrl\n"\
			"shp_simple_snr_2k	  [00]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2]);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}

/**
 * set sr resolution enhance misc by specific value
 *	- input data : see PE_KWRAP_SHP_FMT_TYPE
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSre2KRenMiscCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_SR2K_RE_MISC_T ctrl;
		do {
			CHECK_KNULL(ret, param);
			PE_KWRAP_DBG_PRINT(SHP, \
				"wid:%d, data:%d\n", param->wid, param->data);
			param->st_data = (void *)&ctrl;
			ret = KWRAP_PE_GetSre2KRenMiscDefaultSettings(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_GetRenMiscDefaultSettings.\n", __F__, __L__);
			ctrl.win_id = (param->wid>LX_PE_WIN_NUM)? \
				LX_PE_WIN_0:(LX_PE_WIN_ID)param->wid;
			ret = KWRAP_PE_SetSre2KRenMiscParam((void *)&ctrl);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_SetSre2KRenMiscParam.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set sr resolution enhance misc parameter
 * - use input struct LX_PE_SHP_SR_RE_MISC_T for H15X
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSre2KRenMiscParam(void *param)
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
		LX_PE_SHP_SR2K_RE1_MISC_T *pp = NULL;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_SR2K_RE1_MISC_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	#endif
		do {
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_SR2K_RE1_MISC_T *)param;
			#if 0
			UINT8 *pd = pp->shp_cmn_2k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] :  resolution misc ctrl\n"\
			"shp_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18]);
			pd = pp->shp_map_cmn_2k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] :  resolution misc ctrl\n"\
			"shp_map_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19]);
			pd = pp->shp_balance_2k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] :  resolution misc ctrl\n"\
			"shp_balance_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_2k    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);
			pd = pp->shp_ti_cmn_2k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] :  resolution misc ctrl\n"\
			"shp_ti_cmn_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_2k	  [10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);
			pd = pp->shp_simple_snr_2k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] :  resolution misc ctrl\n"\
			"shp_simple_snr_2k	  [00]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2]);
			#endif
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_SR2K_RE1_MISC_T, SHP);
		#endif
			ret = PE_SHP_SetSre2KReMiscCtrl(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_SR2K_RE_MISC_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_SR2K_RE_MISC_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_SR2K_RE_MISC_T *)param;
			pd = pp->shp_cmn_2k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] :  resolution misc ctrl\n"\
			"shp_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_cmn_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18]);
			pd = pp->shp_map_cmn_2k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] :  resolution misc ctrl\n"\
			"shp_map_cmn_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_map_cmn_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19]);
			pd = pp->shp_balance_2k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] :  resolution misc ctrl\n"\
			"shp_balance_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_balance_2k    [20]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13], pd[14], pd[15], pd[16], pd[17], pd[18], pd[19],\
			pd[20], pd[21], pd[22], pd[23], pd[24], pd[25], pd[26], pd[27], pd[28], pd[29]);
			pd = pp->shp_ti_cmn_2k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] :  resolution misc ctrl\n"\
			"shp_ti_cmn_2k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ti_cmn_2k	  [10]0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11]);
			pd = pp->shp_simple_snr_2k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] :  resolution misc ctrl\n"\
			"shp_simple_snr_2k	  [00]0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_SR2K_RE_MISC_T, SHP);
			#endif
			ret = PE_SHP_SetSre2KReMiscCtrl(param);
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
 * get sr resolution enhance misc parameter
 * - use input struct LX_PE_SHP_SR_RE_MISC_T for H15X
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSre2KRenMiscParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = PE_SHP_GetSre2KReMiscCtrl(param);
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
 * get sr edge enhancemen default settings
 *	- input data : 0~50
 *
 * @param   *param [in/out] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSre2KEdgeEnhanceDefaultSettings(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_SR2K_EE_T ctrl;
		const LX_PE_SHP_SR2K_EE_T *p_data_tbl=NULL;
		UINT8 in=0, out_tbl[PE_KWRAP_SHP_STEP];
		UINT8 in_tbl[PE_KWRAP_SHP_STEP]={0, 10, 25, 30, 50};
		do {
			CHECK_KNULL(ret, param);
			CHECK_KNULL(ret, param->st_data);
			in = (param->data>50)? 50:(UINT8)param->data;
			p_data_tbl = g_pe_kwrap_p_sr_2k_ee;
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_2k[0]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_2k[1]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_2k[2]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_2k[3]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_2k[4]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_2k[5]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_2k[6]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_2k[7]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_2k[8]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_2k[9]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_2k[10]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_2k[11]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_2k[12]);
			PE_KWRAP_INTERPOL(ctrl, p_data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_ee_2k[13]);
			memcpy(param->st_data, &ctrl, sizeof(LX_PE_SHP_SR2K_EE_T));
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set sr edge enhancement by specific value
 *	- input data : 0~50
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSre2KEdgeEnhanceCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_SR2K_EE_T ctrl;
		do {
			CHECK_KNULL(ret, param);
			PE_KWRAP_DBG_PRINT(SHP, \
				"wid:%d, data:%d\n", param->wid, param->data);
			param->st_data = (void *)&ctrl;
			ret = KWRAP_PE_GetSre2KEdgeEnhanceDefaultSettings(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_GetSre2KEdgeEnhanceDefaultSettings.\n", __F__, __L__);
			ctrl.win_id = (param->wid>LX_PE_WIN_NUM)? \
				LX_PE_WIN_0:(LX_PE_WIN_ID)param->wid;
			ret = KWRAP_PE_SetSre2KEdgeEnhanceParam((void *)&ctrl);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_SetSre2KEdgeEnhanceParam.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set sr edge enhancement parameter
 * - use input struct LX_PE_SHP_SR_EE_T for H15X
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSre2KEdgeEnhanceParam(void *param)
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
		LX_PE_SHP_SR2K_EE1_T *pp = NULL;
	#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_SR2K_EE1_T prev[LX_PE_WIN_NUM] __attribute__((unused));
	#endif
		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_SR2K_EE1_T *)param;
			pd = pp->shp_ee_2k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_ee_pre\n"\
			"shp_ee_4k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_4k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_SR2K_EE1_T, SHP);
		#endif
			ret = PE_SHP_SetSre2KEdgeEnhanceCtrl(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
		}while (0);
	}
	else if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_SR2K_EE_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_SR2K_EE_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		do {
			__attribute__((unused)) UINT8 *pd;
			CHECK_KNULL(ret, param);
			pp = (LX_PE_SHP_SR2K_EE_T *)param;
			pd = pp->shp_ee_2k;
			PE_KWRAP_DBG_PRINT(SHP, \
			"set[%d] : shp_ee_pre\n"\
			"shp_ee_4k	  [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
			"shp_ee_4k	  [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
			pp->win_id, \
			pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
			pd[10], pd[11], pd[12], pd[13]);
			#ifdef PE_KWRAP_CHK_VALID_WIN_ID
			PE_KWRAP_CHECK_WINID(LX_PE_SHP_SR2K_EE_T, SHP);
			#endif
			ret = PE_SHP_SetSre2KEdgeEnhanceCtrl(param);
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
 * set sr edge enhancement parameter
 * - use input struct LX_PE_SHP_SR_EE_T for H15X
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSre2KEdgeEnhanceParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = PE_SHP_GetSre2KEdgeEnhanceCtrl(param);
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
 * get sre detail enhancemen default settings
 *	- input data : 0~50
 *
 * @param   *param [in/out] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSre2KDetailEnhanceDefaultSettings(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	LX_PE_SHP_SR2K_DE_T ctrl;
	const LX_PE_SHP_SR2K_DE_T *data_tbl=NULL;
	UINT8 in=0, out_tbl[PE_KWRAP_SHP_STEP];
	UINT8 in_tbl[PE_KWRAP_SHP_STEP]={0, 10, 25, 30, 50};
	do {
		CHECK_KNULL(ret, param);
		CHECK_KNULL(ret, param->st_data);
		in = (param->data>50)? 50:(UINT8)param->data;
		data_tbl = g_pe_kwrap_p_sr_2k_de;
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_2k[0]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_2k[1]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_2k[2]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_2k[3]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_2k[4]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_2k[5]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_2k[6]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_2k[7]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_2k[8]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_2k[9]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_2k[10]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_2k[11]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_2k[12]);
		PE_KWRAP_INTERPOL(ctrl, data_tbl, PE_KWRAP_SHP_STEP, UINT8, shp_de_2k[13]);
		memcpy(param->st_data, &ctrl, sizeof(LX_PE_SHP_SR2K_DE_T));
	}while (0);
	return ret;
}
/**
 * set sr detail enhancement by specific value
 *	- input data : 0~50
 *
 * @param   *param [in] PE_KWRAP_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSre2KDetailEnhanceCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		LX_PE_SHP_SR2K_DE_T ctrl;
		do {
			CHECK_KNULL(ret, param);
			PE_KWRAP_DBG_PRINT(SHP, \
				"wid:%d, data:%d\n", param->wid, param->data);
			param->st_data = (void *)&ctrl;
			ret = KWRAP_PE_GetSre2KDetailEnhanceDefaultSettings(param);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_GetSre2KDetailEnhanceDefaultSettings.\n", __F__, __L__);
			ctrl.win_id = (param->wid>LX_PE_WIN_NUM)? \
				LX_PE_WIN_0:(LX_PE_WIN_ID)param->wid;
			ret = KWRAP_PE_SetSre2KDetailEnhanceParam((void *)&ctrl);
			PE_CHECK_CODE(ret!=RET_OK, break, \
				"[%s,%d]KWRAP_PE_SetSre2KDetailEnhanceParam.\n", __F__, __L__);
		}while (0);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	return ret;
}
/**
 * set sr detail enhancement parameter
 * - use input struct LX_PE_SHP_DE1_T for H15x
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSre2KDetailEnhanceParam(void *param)
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
		LX_PE_SHP_SR2K_DE_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_SR2K_DE_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		__attribute__((unused)) UINT8 *pd;
		CHECK_KNULL(ret, param);
		pp = (LX_PE_SHP_SR2K_DE_T *)param;
		pd = pp->shp_de_2k;
		PE_KWRAP_DBG_PRINT(SHP, \
		"set[%d] : shp_ee_pre\n"\
		"shp_de_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_de_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13]);
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		PE_KWRAP_CHECK_WINID(LX_PE_SHP_SR2K_DE_T, SHP);
		#endif
		ret = PE_SHP_SetSre2KDetailEnhanceCtrl(param);
		PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
	}while (0);
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}

/**
 * get detail enhancement parameter
 * - use input struct LX_PE_SHP_DE1_T for H15X
 *
 * @param   *param [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_GetSre2KDetailEnhanceParam(void *param)
{
	int ret = RET_OK;
	PE_CHECK_OPENED();
	PE_LOCK();
	PE_TRACE_BEGIN();
	if (PE_KDRV_VER_M19 || PE_KDRV_VER_O18)
	{
		ret = PE_SHP_GetSre2KDetailEnhanceCtrl(param);
	}
	else
	{
		PE_KWRAP_NOTI_NOT_SUPPORTED();
	}
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}

int KWRAP_PE_SetSre2KSqmCmnCtrl(PE_KWRAP_CTRL_T *param)
{
	int ret = RET_OK;

	if (PE_KWRAP_VER_M19)
	{
		ret = KWRAP_PE_SetSre2KSqmCmnBspDB(param);
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
int KWRAP_PE_SetSre2KSqmCmnParam(void *param)
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
		LX_PE_SHP_SR2K_SQM_CMN_T *pp = (LX_PE_SHP_SR2K_SQM_CMN_T *)param;
		CHECK_KNULL(ret, param);
		ret = KWRAP_PE_CheckSre2KSqmCmnParam(pp);
		PE_CHECK_CODE(ret!=RET_OK, break, \
		"[%s,%d]check_dnr_cmn.\n", __F__, __L__);
		PE_CHECK_ACTION(pp->win_id>LX_PE_WIN_ALL, ret=RET_OK;break);
		ret = PE_SHP_SetSre2KSqmCmnCtrl(param);
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
int KWRAP_PE_SetSre2KRenSqmDetailParam(void *param)
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
		LX_PE_SHP_SR2K_SQM_DETAIL_T *pp = (LX_PE_SHP_SR2K_SQM_DETAIL_T *)param;
		CHECK_KNULL(ret, param);
		ret = KWRAP_PE_CheckSre2KSqmDetailParam(pp);
		PE_CHECK_CODE(ret!=RET_OK, break, \
		"[%s,%d]check_dnr_cmn.\n", __F__, __L__);
		PE_CHECK_ACTION(pp->win_id>LX_PE_WIN_ALL, ret=RET_OK;break);
		ret = PE_SHP_SetSre2KSqmDetailCtrl(param);
		PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
	}while (0);
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}
/**
 * set sr resolution enhance common parameter
 * - use input struct LX_PE_SHP_SR_RE_CMN_T for H15X
 *
 * @param   *param [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		func. description
 * @author
 */
int KWRAP_PE_SetSre2KRenEasyCmnParam(void *param)
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
		LX_PE_SHP_RE_EASY_CMN_T *pp = NULL;
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		static LX_PE_SHP_RE_EASY_CMN_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		#endif
		__attribute__((unused)) UINT8 *pd;
		CHECK_KNULL(ret, param);
		pp = (LX_PE_SHP_RE_EASY_CMN_T *)param;
		pd = pp->shp_ui_vsd;
		PE_KWRAP_DBG_PRINT(SHP, \
		"set[%d] : shp_ui_main_2k\n"\
		"shp_ui_main_2k    [00]0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,\n"\
		"shp_ui_main_2k    [10]0x%02X,0x%02X,0x%02X,0x%02X,\n",\
		pp->win_id, \
		pd[0], pd[1], pd[2], pd[3], pd[4], pd[5], pd[6], pd[7], pd[8], pd[9],\
		pd[10], pd[11], pd[12], pd[13]);
		#ifdef PE_KWRAP_CHK_VALID_WIN_ID
		PE_KWRAP_CHECK_WINID(LX_PE_SHP_RE_EASY_CMN_T, SHP);
		#endif
		ret = PE_SHP_SetSre2KReEasyCmnCtrl(pp);
		PE_CHECK_CODE(ret!=RET_OK, break, \
			"[%s,%d]PE_KWRAP_IOCTL.\n", __F__, __L__);
	}while (0);
	PE_TRACE_END();
	PE_UNLOCK();
	return ret;
}


