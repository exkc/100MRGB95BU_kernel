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
 *  main configuration file for ovi device
 *	
 *  author		dj911.kim
 *  version		1.0
 *  date		2012.10.08
 *  note		Additional information.
 *
 *  @addtogroup ovi
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "ovi_cfg.h"
#include "os_util.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
LX_MEMCFG_T gMemCfgOviTcon[] = 
{
	// [0] M14B0, L18F
	{
		.name = "OVI_TCON_FRM",
		.base = 0,
		.size = 0x00100000
	},

	// [1] M16, M17, M19
	{
		.name = "OVI_TCON_FRM",
		.base = 0,
		.size = 0x00400000
	}, 

	// [2] O20, E60, O22
	{
		.name = "OVI_TCON_FRM",
		.base = 0,
		.size = 0x00000000
	},
	// [3] M23
	{
		.name = "OVI_TCON_FRM",
		.base = 0,
		.size = 0x00600000
	},
	// [4] O24
	{
		.name = "OVI_TCON_FRM_5M",
		.base = 0,
		.size = 0x00500000
	}
};

LX_MEMCFG_T *gpOviTconMem = NULL;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
void OVI_InitCfg ( void )
{
	if ( lx_chip_rev() >= LX_CHIP_REV(M23,A0) )
	{
		#if !(defined BUILD_FEATURE_slt) && (defined BUILD_FEATURE_ddr_96bit) // ddr_96bit TV/signage (non-SLT platform)
		if (lx_chip() == LX_CHIP_O24)
		{
			gpOviTconMem = &gMemCfgOviTcon[4];//ODC:4,DEMURA:1(SICDTV-13665,SCDCRID-3662)
		}
		else
		#endif
		if (lx_chip_plt() == LX_CHIP_PLT_HD || lx_chip_plt() == LX_CHIP_PLT_FHD)
		{
			gpOviTconMem = &gMemCfgOviTcon[2];
		}
		else
		{
			gpOviTconMem = &gMemCfgOviTcon[3];
		}
	}
	else if ( lx_chip_rev() >= LX_CHIP_REV(O22,A0) )
	{
		gpOviTconMem = &gMemCfgOviTcon[2];
	}
	else if ( lx_chip_rev() >= LX_CHIP_REV(O20,A0) )
	{
		gpOviTconMem = &gMemCfgOviTcon[2];
	}
	else if ( lx_chip_rev() >= LX_CHIP_REV(M16,A0) )
	{
		gpOviTconMem = &gMemCfgOviTcon[1];
	}
	else
	{
		gpOviTconMem = &gMemCfgOviTcon[0];
	}
}

/** @} */


