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
 *  main configuration file for BE device
 *
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.02.07
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "be_cfg.h"
#include "os_util.h"
#include "be_dbg.h"
#include "hma_alloc.h"
#ifdef INCLUDE_KDRV_DE
#include "de_cfg.h"
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

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
BE_MEM_CFG_T gMemCfgBe[] =
{
	//[00] M14B0
	{
		{
			{	"fw_frc",	0x00000000,	0x00000000	},
			{	"fw_wcg",	0x00000000,	0x00004000	},
			{	"fw_led",	0x00000000,	0x00010000	},
			{	"fw_hdr",	0x00000000,	0x00008000	},
			{	"fw_ipc",	0x00000000,	0x00004000	},
			{	"fw_dnn",	0x00000000,	0x00000000	}
		},
		.frame_name = "BE_FRM",
		.frame_base = 0x00000000,
		.frame_size = 0x051E0000
	},

	//[01] H15
	{
		{
			{	"fw_frc",	0x00000000,	0x00000000	},
			{	"fw_wcg",	0x00000000,	0x00008000	},
			{	"fw_led",	0x00000000,	0x00010000	},
			{	"fw_hdr",	0x00000000,	0x00004000	},
			{	"fw_ipc",	0x00000000,	0x00300000	},
			{	"fw_dnn",	0x00000000,	0x00000000	}
		},
		.frame_name = "BE_FRM",
		.frame_base = 0x00000000,
		.frame_size = 0x00000000
	},

	//[02] M16, M17A0/B0
	{
		{
			{	"fw_frc",	0x00000000,	0x00000000	},
			{	"fw_wcg",	0x00000000,	0x00008000	},
			{	"fw_led",	0x00000000,	0x00010000	},
			{	"fw_hdr",	0x00000000,	0x00000000	},
			{	"fw_ipc",	0x00000000,	0x00000000	},
			{	"fw_dnn",	0x00000000,	0x00000000	}
		},
		.frame_name = "BE_FRM",
		.frame_base = 0x00000000,
		.frame_size = 0x00000000 // 0 MB
	},

	//[03] M17C0 - Not Used
	{
		{
			{	"fw_frc",	0x00000000,	0x00000000	},
			{	"fw_wcg",	0x00000000,	0x00040000	},
			{	"fw_led",	0x00000000,	0x00014000	},
			{	"fw_hdr",	0x00000000,	0x00004000	},
			{	"fw_ipc",	0x00000000,	0x00300000	},
			{	"fw_dnn",	0x00000000,	0x00000000	}
		},
		.frame_name = "BE_FRM",
		.frame_base = 0x00000000,
		.frame_size = 0x00000000 // 0 MB
	},

	//[04] L18
	{
		{
			{	"fw_frc",	0x00000000,	0x00000000	},
			{	"fw_wcg",	0x00000000,	0x00000000	},
			{	"fw_led",	0x00000000,	0x00000000	},
			{	"fw_hdr",	0x00000000,	0x00000000	},
			{	"fw_ipc",	0x00000000,	0x00300000	},
			{	"fw_dnn",	0x00000000,	0x00000000	}
		},
		.frame_name = "BE_FRM",
		.frame_base = 0x00000000,
		.frame_size = 0x00000000 // 0 MB
	},

	//[05] O18
	{
		{
			{	"fw_frc",	0x00000000,	0x00000000	},
			{	"fw_wcg",	0x00000000,	0x00180000	},
			{	"fw_led",	0x00000000,	0x00000000	},
			{	"fw_hdr",	0x00000000,	0x00004000	},
			{	"fw_ipc",	0x00000000,	0x00300000	},
			{	"fw_dnn",	0x00000000,	0x00000000	}
		},
		.frame_name = "BE_FRM",
		.frame_base = 0x00000000,
		.frame_size = 0x00000000 // 0 MB
	},

	//[06] O20/E60/O22/M23
	{
		{
			{	"fw_frc",	0x00000000,	0x00000000	},
			{	"fw_wcg",	0x00000000,	0x00180000	},
			{	"fw_led",	0x00000000,	0x00020000	},
			{	"fw_hdr",	0x00000000,	0x00008000	},
			{	"fw_ipc",	0x00000000,	0x00000000	},
			{	"fw_dnn",	0x00000000,	0x00000000	}
		},
		.frame_name = "BE_FRM",
		.frame_base = 0x00000000,
		.frame_size = 0x00000000
	}
};

BE_FRM_MEM_CFG_T gMemCfgBeFrc[] =
{
	// [0] M16Ax, M16Bx 1.5G
	{
		.frame_name = "BE_FRC_M16B_1_5G",
		.frame_base = 0x00000000,
		.frame_size = 0x01c00000 // 76 -> 28 MB
	},
	// [1] M16P
	{
		.frame_name = "BE_FRC_M16B_2G",
		.frame_base = 0x00000000,
		.frame_size = 0x00000000 // 192MB -> 0MB
	},
	// [2] O18_FPP, 96bit M0, 80bit M0
	{
		.frame_name = "BE_FRC_O18_FPP",
		.frame_base = 0x00000000,
		.frame_size = 0x01300000 // 19MB
	},
	// [3] O18_FRC0, 96bit M2, 80bit M2
	{
		.frame_name = "BE_FRC_O18_FRC0",
		.frame_base = 0x00000000,
		.frame_size = 0x01E00000 // 30MB
	},
	// [4] O18_FRC1, 96bit M2, 80bit M2
	{
		.frame_name = "BE_FRC_O18_FRC1",
		.frame_base = 0x00000000,
		.frame_size = 0x00900000 // 9MB
	},
	// [5] O18_FRC2, 96bit M1, 80bit M1
	{
		.frame_name = "BE_FRC_O18_FRC2",
		.frame_base = 0x00000000,
		.frame_size = 0x03000000 // 48MB
	},
	// [6] O20_FPP,  M0
	{
		.frame_name = "BE_FRC_O20_FPP",
		.frame_base = 0x00000000,
		.frame_size = 0x01E00000 // 30MB
	},
	// [7] O20_FRC0, M1
	{
		.frame_name = "BE_FRC_O20_FRC0",
		.frame_base = 0x00000000,
		.frame_size = 0x05200000 // 82MB
	},
	// [8] O20_FRC1, M1
	{
		.frame_name = "BE_FRC_O20_FRC1",
		.frame_base = 0x00000000,
		.frame_size = 0x00000000 // 0MB
	},
	// [9] O20_FRC2, M1
	{
		.frame_name = "BE_FRC_O20_FRC2",
		.frame_base = 0x00000000,
		.frame_size = 0x00000000 // 0MB
	},
	// [10] E60_FPP, M0
	{
		.frame_name = "BE_FRC_E60_FPP",
		.frame_base = 0x00000000,
		.frame_size = 0x00000000 // 0MB
	},
	// [11] E60_FRC0, M0
	{
		.frame_name = "BE_FRC_E60_FRC0",
		.frame_base = 0x00000000,
		.frame_size = 0x00000000 // 0MB
	},
	// [12] E60_FRC1, M1
	{
		.frame_name = "BE_FRC_E60_FRC1",
		.frame_base = 0x00000000,
		.frame_size = 0x01800000 // AVTASK-343, 85MB -> 70MB -> 64MB -> 24MB(SICDTV-8954)
	},
	// [13] E60_FRC2, M2
	{
		.frame_name = "BE_FRC_E60_FRC2",
		.frame_base = 0x00000000,
		.frame_size = 0x06400000 // AVTASK-343, 109MB -> 81MB -> 59MB -> 100MB(SICDTV-8954)
	},
	// [14] O20T_FPP,  M0
	{
		.frame_name = "BE_FRC_O20T_FPP",
		.frame_base = 0x00000000,
		.frame_size = 0x00E00000 // AVTASK-499, 14MB
	},
	// [15] O20T_FRC0, M1
	{
		.frame_name = "BE_FRC_O20_FRC0",
		.frame_base = 0x00000000,
		.frame_size = 0x04500000 // AVTASK-499, 69MB
	},
	// [16] E60_FRC3, M2
	{
		.frame_name = "BE_FRC_E60_FRC3",
		.frame_base = 0x00000000,
		.frame_size = 0x00000000 // 0MB
	}
};

BE_FRM_MEM_CFG_T gMemCfgBeChInf[] =
{
	// [0] O20
	{
		.frame_name = "BE_CHIP_INFO_O20",
		.frame_base = 0x00000000,
		.frame_size = 0x00100000 // 1MB
	},
	// [1] E60
	{
		.frame_name = "BE_CHIP_INFO_E60",
		.frame_base = 0x00000000,
		.frame_size = 0x00100000 // 1MB
	},
	// [2] O22
	{
		.frame_name = "BE_CHIP_INFO_O22",
		.frame_base = 0x00000000,
		.frame_size = 0x00100000 // 1MB
	}
};

BE_MEM_CFG_T *gpBeMem = NULL;
BE_FRM_MEM_CFG_T *gpBeChInfMem = NULL;
BE_FRM_MEM_CFG_T *gpBeFrcMem0 = NULL;
BE_FRM_MEM_CFG_T *gpBeFrcMem1 = NULL;
BE_FRM_MEM_CFG_T *gpBeFrcMem2 = NULL;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
void BE_PreInitCfg( void )
{
	if ( lx_chip_rev() >= LX_CHIP_REV(M17,C0) )
	{
		gMemCfgBe[2].fw[1].fw_size = 0x00040000; // fw_wcg size 
		gMemCfgBe[2].fw[2].fw_size = 0x00014000; // fw_led size
		gMemCfgBe[2].fw[3].fw_size = 0x00004000; // fw_hdr size
	}

	if ( lx_chip_rev() >= LX_CHIP_REV(M23,A0) )
	{
		gpBeMem = &gMemCfgBe[6];
	}
	else if ( lx_chip_rev() >= LX_CHIP_REV(O22,A0) )
	{
		gpBeMem = &gMemCfgBe[6];
	}
	else if ( lx_chip_rev() >= LX_CHIP_REV(O20,A0) )
	{
		gpBeMem = &gMemCfgBe[6];
	}
	else if ( lx_chip_rev() >= LX_CHIP_REV(M19,A0) )
	{
		gpBeMem = &gMemCfgBe[2];
	}
	else if ( lx_chip_rev() >= LX_CHIP_REV(O18,A0) )
	{
		gpBeMem = &gMemCfgBe[5];
	}
	else if ( lx_chip_rev() >= LX_CHIP_REV(M16,A0) )
	{
		gpBeMem = &gMemCfgBe[2];
	}

	/* BeChInf */
	if ( lx_chip_rev() >= LX_CHIP_REV(O22,A0) )
	{
#ifdef INCLUDE_KDRV_DE
		gpBeChInfMem = (BE_FRM_MEM_CFG_T *)&g_chipinfo;
#endif
	}
	else if ( lx_chip_rev() >= LX_CHIP_REV(E60,A0) )
	{
		gpBeChInfMem = &gMemCfgBeChInf[1];
	}
	else if ( lx_chip_rev() >= LX_CHIP_REV(O20,A0) )
	{
#ifdef INCLUDE_KDRV_DE
#ifdef PQE_NEW_MAP
		gpBeChInfMem = (BE_FRM_MEM_CFG_T *)&g_chipinfo;
#else
		gpBeChInfMem = &gMemCfgBeChInf[0];
#endif
#else
		gpBeChInfMem = &gMemCfgBeChInf[0];
#endif
	}

	/* BeMemFrc */
	if ( lx_chip_rev() >= LX_CHIP_REV(E60,A0) )
	{
		gpBeFrcMem0 = &gMemCfgBeFrc[11];
		gpBeFrcMem1 = &gMemCfgBeFrc[12];
		gpBeFrcMem2 = &gMemCfgBeFrc[13];

		if(lx_board_opt() & LX_BOARD_OPT_EXT_FRC)//AVTASK-516
		{
			gMemCfgBeFrc[12].frame_size = 35*1024*1024;//be_frc1:64 -> 35 ->  0 -> 35
			gMemCfgBeFrc[13].frame_size = 87*1024*1024;//be_frc2:59 -> 46 -> 87
			gMemCfgBeFrc[16].frame_size =  0*1024*1024;//be_frc3:41 -> 0 (SICDTV-8954)
		}
	}
	BE_NOTI("done\n");
}

void BE_InitCfg ( void )
{
	int ret = RET_OK;
	UINT64 base_addr;
	int alloc_size;

	#ifdef INCLUDE_KDRV_DE
	if ( lx_chip_rev() >= LX_CHIP_REV(M23,A0) ) {
		gpBeMem->fw[1].fw_base = g_be_wcg.base;
		gpBeMem->fw[1].fw_size = g_be_wcg.size;
		gpBeMem->fw[2].fw_base = g_be_led.base;
		gpBeMem->fw[2].fw_size = g_be_led.size;
		gpBeMem->fw[3].fw_base = g_be_phdr.base;
		gpBeMem->fw[3].fw_size = g_be_phdr.size;
	}
	else if ( lx_chip_rev() >= LX_CHIP_REV(O22,A0) ) {
		gpBeMem->fw[1].fw_base = g_be_wcg.base;
		gpBeMem->fw[1].fw_size = g_be_wcg.size;
		gpBeMem->fw[2].fw_base = g_be_led.base;
		gpBeMem->fw[2].fw_size = g_be_led.size;
		gpBeMem->fw[3].fw_base = g_be_phdr.base;
		gpBeMem->fw[3].fw_size = g_be_phdr.size;
	}
	#ifdef PQE_NEW_MAP
	else if (lx_chip() == LX_CHIP_O20) {
		gpBeMem->fw[1].fw_base = g_be_wcg.base;
		gpBeMem->fw[1].fw_size = g_be_wcg.size;
		gpBeMem->fw[2].fw_base = g_be_led.base;
		gpBeMem->fw[2].fw_size = g_be_led.size;
		gpBeMem->fw[3].fw_base = g_be_phdr.base;
		gpBeMem->fw[3].fw_size = g_be_phdr.size;
	}
	#endif
	#endif

	if (gpBeFrcMem0 != NULL)
	{
		base_addr = (UINT64)gpBeFrcMem0->frame_base;
		alloc_size = gpBeFrcMem0->frame_size;
		if (base_addr > 0 && alloc_size > 0)
		{
			ret = hma_pool_register_type("be-frc-m0",(phys_addr_t)base_addr,alloc_size,HMA_POOL);
			BE_NOTI("be-frc-m0"" : base[0x%08llx] size = %dKB ret = %d\n",base_addr,(alloc_size>>10),ret);
		}
	}

	if (gpBeFrcMem1 != NULL)
	{
		base_addr = (UINT64)gpBeFrcMem1->frame_base;
		alloc_size = gpBeFrcMem1->frame_size;
		if (base_addr > 0 && alloc_size > 0)
		{
			ret = hma_pool_register_type("be-frc-m1",(phys_addr_t)base_addr,alloc_size,HMA_POOL);
			BE_NOTI("be-frc-m1"" : base[0x%08llx] size = %dKB ret = %d\n",base_addr,(alloc_size>>10),ret);
		}
	}

	if (gpBeFrcMem2 != NULL)
	{
		base_addr = (UINT64)gpBeFrcMem2->frame_base;
		alloc_size = gpBeFrcMem2->frame_size;
		if (base_addr > 0 && alloc_size > 0)
		{
			ret = hma_pool_register_type("be-frc-m2",(phys_addr_t)base_addr,alloc_size,HMA_POOL);
			BE_NOTI("be-frc-m2"" : base[0x%08llx] size = %dKB ret = %d\n",base_addr,(alloc_size>>10),ret);
		}
	}

	#if 0
	ret = hma_pool_info("be-frc-m0",(phys_addr_t *)&base_addr,&alloc_size);
	if (!ret)	BE_NOTI("be-frc-m0"" pool_info : base[0x%08llx] size = %dKB\n",base_addr,(alloc_size>>10));
	ret = hma_pool_info("be-frc-m1",(phys_addr_t *)&base_addr,&alloc_size);
	if (!ret)	BE_NOTI("be-frc-m1"" pool_info : base[0x%08llx] size = %dKB\n",base_addr,(alloc_size>>10));
	ret = hma_pool_info("be-frc-m2",(phys_addr_t *)&base_addr,&alloc_size);
	if (!ret)	BE_NOTI("be-frc-m2"" pool_info : base[0x%08llx] size = %dKB\n",base_addr,(alloc_size>>10));
	#endif

	BE_NOTI("done\n");
}

/** @} */


