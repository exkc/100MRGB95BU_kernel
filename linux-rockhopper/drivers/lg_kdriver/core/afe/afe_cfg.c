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
 *  CVD LDrv file for afe device
 *	afe device will teach you how to make device driver with new platform.
 *
 *  author		wonsik.do (wonsik.do@lge.com)
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_afe
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "afe_cfg.h"
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
void    AFE_InitCfg ( void );

void 	AFE_GetMemCfg( UINT32* mem_base_comb_buffer, UINT32* mem_size_comb_buffer, UINT32* mem_base_cvd_reg, UINT32* mem_size_cvd_reg);
/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/**
Vport Register configuration.
*/
LX_CVD_REG_T gRegCfgVport[] =
{
	// for M16P, M16++, M19
	{
		.chip_name	= "CVD_M16/O18/M19x/O20/E60",
		.vport_reg_base_addr 	= 0xc9000600,
		.vport_reg_size			= 0x00000894,
		.vport_qemu_base_addr	= 0x04008000,
		.chbcvd_reg_base_addr	= 0x0,
		.chbcvd_reg_size	= 	0x0,
	},
	// for M16P, M16++, M19
	{
		.chip_name	= "CVD_O22",
		.vport_reg_base_addr 	= 0xcc840700,
		.vport_reg_size			= 0x00000894,
		.vport_qemu_base_addr	= 0x04008000,
		.chbcvd_reg_base_addr	= 0x0,
		.chbcvd_reg_size	= 	0x0,
	},
	{
		.chip_name	= "CVD_M23",
		.vport_reg_base_addr 	= 0xcc690700,
		.vport_reg_size			= 0x00000894,
		.vport_qemu_base_addr	= 0x04008000,
		.chbcvd_reg_base_addr	= 0x0,
		.chbcvd_reg_size	= 	0x0,
	},
	{
		.chip_name	= "CVD_O24",
		.vport_reg_base_addr 	= 0xcccc0700,
		.vport_reg_size			= 0x00000894,
		.vport_qemu_base_addr	= 0x04008000,
		.chbcvd_reg_base_addr	= 0x0,
		.chbcvd_reg_size	= 	0x0,
	},
	{
		.chip_name	= "CVD_O26",
		.vport_reg_base_addr 	= 0xcc4e1700,
		.vport_reg_size			= 0x00000894,
		.vport_qemu_base_addr	= 0x04008000,
		.chbcvd_reg_base_addr	= 0x0,
		.chbcvd_reg_size	= 	0x0,
	},
};

LX_CVD_REG_T *pVportRegCfg = NULL;

// CVD 3D Comb Filter Memory
LX_CVD_MEM_CFG_T gMemCfgCvd[] =
{
	{
	.memory_name = "cvd_3dcomb_buf",
	.memory_base = 0x0,	
	.memory_size = 0x00580000,
	}
};

LX_CVD_MEM_CFG_T*	gpCvdMemCfg = NULL;
LX_CVD_MEM_CFG_T	gCvdMemCfg = {0,};

BOOLEAN gADCSupport = FALSE;
BOOLEAN g_CVD_CMA_POOL = FALSE;
BOOLEAN g_CVD_USE_TE_SHARED_POOL = FALSE;
/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/


/*========================================================================================
	Implementation Group
========================================================================================*/
void    AFE_InitCfg ( void )
{

	printk("Main CVD Initialize Start... DTVSoC Chip Verstion [0x%x]\n", lx_chip_rev() );
	/*-----------------------------------------------------------------------------------
	 * CVD Memory configuration
	 *----------------------------------------------------------------------------------*/
    if( lx_chip_rev( ) >= LX_CHIP_REV(O26,A0) )
	{
		// 3D Comb Buffer Memory Address
		//gpCvdMemCfg = &gMemCfgCvd[3];
		gCvdMemCfg = gMemCfgCvd[0];
		gpCvdMemCfg = &gCvdMemCfg;
		// CVD Register Base Address
		pVportRegCfg = &gRegCfgVport[4];	// for Real.
		gADCSupport = FALSE;
		g_CVD_CMA_POOL = TRUE;
		g_CVD_USE_TE_SHARED_POOL = TRUE;
	}
	else if( lx_chip_rev( ) >= LX_CHIP_REV(O24,A0) )
	{
		// 3D Comb Buffer Memory Address
		//gpCvdMemCfg = &gMemCfgCvd[3];
		gCvdMemCfg = gMemCfgCvd[0];
		gpCvdMemCfg = &gCvdMemCfg;
		// CVD Register Base Address
		pVportRegCfg = &gRegCfgVport[3];	// for Real.
		gADCSupport = FALSE;
		g_CVD_CMA_POOL = TRUE;
		g_CVD_USE_TE_SHARED_POOL = TRUE;
	}
    else if( lx_chip_rev( ) >= LX_CHIP_REV(M23,A0) )
	{
		// 3D Comb Buffer Memory Address
		//gpCvdMemCfg = &gMemCfgCvd[3];
		gCvdMemCfg = gMemCfgCvd[0];
		gpCvdMemCfg = &gCvdMemCfg;
		// CVD Register Base Address
		pVportRegCfg = &gRegCfgVport[2];	// for Real.
		gADCSupport = FALSE;
		g_CVD_CMA_POOL = TRUE;
		g_CVD_USE_TE_SHARED_POOL = TRUE;
	}
    else if( lx_chip_rev( ) >= LX_CHIP_REV(O22,A0) )
	{
		// 3D Comb Buffer Memory Address
		//gpCvdMemCfg = &gMemCfgCvd[3];
		gCvdMemCfg = gMemCfgCvd[0];
		gpCvdMemCfg = &gCvdMemCfg;
		// CVD Register Base Address
		pVportRegCfg = &gRegCfgVport[1];	// for Real.
		gADCSupport = FALSE;
		g_CVD_CMA_POOL = TRUE;				//230920 : qsm fail issue
		g_CVD_USE_TE_SHARED_POOL = TRUE;	//230811 : webos4tv
	}
    else if( lx_chip_rev( ) >= LX_CHIP_REV(E60,A0) )
	{
		// 3D Comb Buffer Memory Address
		//gpCvdMemCfg = &gMemCfgCvd[3];
		gCvdMemCfg = gMemCfgCvd[0];
		gpCvdMemCfg = &gCvdMemCfg;
		// CVD Register Base Address
		pVportRegCfg = &gRegCfgVport[0];	// for Real.
		gADCSupport = TRUE;
		g_CVD_CMA_POOL = FALSE;
		g_CVD_USE_TE_SHARED_POOL = FALSE;
	}
	else if( lx_chip_rev( ) >= LX_CHIP_REV(O20,A0) )
	{
		// 3D Comb Buffer Memory Address
		//gpCvdMemCfg = &gMemCfgCvd[3];
		gCvdMemCfg = gMemCfgCvd[0];
		gpCvdMemCfg = &gCvdMemCfg;
		// CVD Register Base Address
		pVportRegCfg = &gRegCfgVport[0];	// for Real.
		gADCSupport = TRUE;
		g_CVD_CMA_POOL = FALSE;
		g_CVD_USE_TE_SHARED_POOL = FALSE;
	}
    else
    {
    }

}

void 	AFE_GetMemCfg( UINT32* mem_base_comb_buffer, UINT32* mem_size_comb_buffer, UINT32* mem_base_cvd_reg, UINT32* mem_size_cvd_reg)
{
	*mem_base_comb_buffer = gpCvdMemCfg->memory_base;
	*mem_size_comb_buffer = gpCvdMemCfg->memory_size;

	*mem_base_cvd_reg = pVportRegCfg->vport_reg_base_addr;
	*mem_size_cvd_reg = pVportRegCfg->vport_reg_size;

	return;
}



/** @} */

