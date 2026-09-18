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
 *  author		won.hur (won.hur@lge.com)
 *  version		1.0
 *  date		2012.04.18
 *  note		Additional information.
 *
 *  @addtogroup lg115x_vbi
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "os_util.h"
#include "vbi_cfg.h"
#include "vbi_drv.h"
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

//CPU_VBI_IP_TOP

LX_VBI_REG_CFG_T gstVbiRegCfgVBIRev[] =
{
    {
		.vbi_register_name = "M16Cx_VBI_IP",
		.vbi_register_base = 0xC9207000,
		.vbi_register_size = 0x800,
	},
    {
		.vbi_register_name = "O22_VBI_IP",
		.vbi_register_base = 0xC8860000,
		.vbi_register_size = 0x800,
	},
    {
		.vbi_register_name = "M23_VBI_IP",
		.vbi_register_base = 0xC4600000,
		.vbi_register_size = 0x800,
	},
    {
		.vbi_register_name = "O24_VBI_IP",
		.vbi_register_base = 0xC8D60000,
		.vbi_register_size = 0x800,
	},
    {
		.vbi_register_name = "O26_VBI_IP",
		.vbi_register_base = 0xC8760000,
		.vbi_register_size = 0x800,
	},
};


LX_VBI_MEM_CFG_T gstBufMemCfgVBIRev[] =
{
    {
		.buf_memory_name = "vbi_phys_memory",
		.buf_memory_base = 0,
#if USE_VBI_DEVICE_DRIVER_MEMORY
		.buf_memory_size = 0x00001000,
#else
		.buf_memory_size = 0x00000000,
#endif
	},
    {
		.buf_memory_name = "vbi_kernel_memory",
		.buf_memory_base = 0,
		.buf_memory_size = 0x00080000,
	},
};

LX_VBI_MEM_CFG_T* 	gstMemCfgVBI	= NULL;
LX_VBI_REG_CFG_T* 	gstRegCfgVBI	= NULL;


/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/


/*========================================================================================
	Implementation Group
========================================================================================*/
void    VBI_InitCfg ( void )
{

	/*-----------------------------------------------------------------------------------
	 * [M23/O22] configuration
	 *----------------------------------------------------------------------------------*/
	if( lx_chip_rev( ) >= LX_CHIP_REV(O26, A0) )	//O24
    {
		gstMemCfgVBI = &gstBufMemCfgVBIRev[1];
		gstRegCfgVBI = &gstVbiRegCfgVBIRev[4];
    }
	else if( lx_chip_rev( ) >= LX_CHIP_REV(O24, A0) )	//O24
    {
		gstMemCfgVBI = &gstBufMemCfgVBIRev[1];
		gstRegCfgVBI = &gstVbiRegCfgVBIRev[3];
    }
	else if( lx_chip_rev( ) >= LX_CHIP_REV(M23, A0) )	//M23
    {
		gstMemCfgVBI = &gstBufMemCfgVBIRev[1];
		gstRegCfgVBI = &gstVbiRegCfgVBIRev[2];
    }
	else if( lx_chip_rev( ) >= LX_CHIP_REV(O22, A0) )	//O22
    {
		gstMemCfgVBI = &gstBufMemCfgVBIRev[1];
		gstRegCfgVBI = &gstVbiRegCfgVBIRev[1];
    }
	else if( lx_chip_rev( ) >= LX_CHIP_REV(M16, C0) )	//M16++, M16P3, O18, O20, E60
    {
		gstMemCfgVBI = &gstBufMemCfgVBIRev[1];
		gstRegCfgVBI = &gstVbiRegCfgVBIRev[0];
    }
    else
    {
    }
}



/** @} */

