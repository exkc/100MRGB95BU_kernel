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
 *  main configuration file for de device
 *  de device will teach you how to make device driver with new platform.
 *
 *  author      dongho7.park (dongho7.park@lge.com)
 *  version     1.0
 *  date        2009.12.30
 *  note        Additional information.
 *
 *  @addtogroup lg1150_de
 *  @{
 */

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <linux/seq_file.h>
#include "os_util.h"
#include "hma_alloc.h"
#include "de_ver_def.h"
#include "de_cfg.h"
#include "de_def.h"
//#ifdef PLATFORM_FPGA
#ifndef INCLUDE_KDRV_BE
#include "../be/be_cfg.h"
#endif
#ifndef INCLUDE_KDRV_PE
#include "../pe/pe_cfg.h"
#endif
#ifdef USE_KDRV_CODES_FOR_M17
#include "m17/de/de_cfg_m17.h"
#endif
#ifdef USE_KDRV_CODES_FOR_L18
#include "l18/de/de_cfg_l18.h"
#endif
#ifdef USE_KDRV_CODES_FOR_O18
#include "o18/de/de_cfg_o18.h"
#endif
#ifdef USE_KDRV_CODES_FOR_M19
#include "m19/de/de_cfg_m19.h"
#endif
#ifdef USE_KDRV_CODES_FOR_O20
#include "o20/de/de_cfg_o20.h"
#endif
#ifdef USE_KDRV_CODES_FOR_E60
#include "e60/de/de_cfg_e60.h"
#endif
#ifdef USE_KDRV_CODES_FOR_O22
#include "o22/de/de_cfg_o22.h"
#endif
#ifdef USE_KDRV_CODES_FOR_M23
#include "m23/de/de_cfg_m23.h"
#endif
#ifdef USE_KDRV_CODES_FOR_O24
#include "o24/de/de_cfg_o24.h"
#endif
#ifdef USE_KDRV_CODES_FOR_O26
#include "o26/de/de_cfg_o26.h"
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
struct de_cfg_ctx
{
	int (*preinit)(void);
	int (*init)(void);
	int (*cleanup)(void);
};

/*----------------------------------------------------------------------------------------
    External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/
LX_DE_MEM_CFG_T gMemCfgDe[] =
{
	// [0] for m17
	{
#ifdef USE_KDRV_CODES_FOR_M17
		{
			{   "fw_led", 0, VIDEO_M17_FIRMWARE_MEM_SIZE_OF_LED } ,
			{   "fw_ipc", 0, VIDEO_M17_FIRMWARE_MEM_SIZE_OF_IPC } ,
			{   "fw_de",  0, VIDEO_M17_FIRMWARE_MEM_SIZE_OF_DE  } ,
		},
		.frame_name = "DE_FRM",
		.frame_base = 0,
		.frame_size = VIDEO_M17_MEM_SIZE_OF_FRAME_DE,
#else
	.frame_name = "",
	.frame_base = 0,
	.frame_size = 0
#endif
	},

	// [1] for m17 1.5GB
	{
#ifdef USE_KDRV_CODES_FOR_M17
		{
			{   "fw_led", 0, VIDEO_M17_FIRMWARE_MEM_SIZE_OF_LED } ,
			{   "fw_ipc", 0, VIDEO_M17_FIRMWARE_MEM_SIZE_OF_IPC } ,
			{   "fw_de",  0, VIDEO_M17_FIRMWARE_MEM_SIZE_OF_DE  } ,
		},
		.frame_name = "DE_FRM",
		.frame_base = 0,
		.frame_size = VIDEO_M17_MEM_SIZE_OF_FRAME_DE_15GB,
#else
	.frame_name = "",
	.frame_base = 0,
	.frame_size = 0
#endif
	},

	// [2] for l18
	{
#ifdef USE_KDRV_CODES_FOR_L18
		{
			{   "fw_de",  0, VIDEO_L18_FIRMWARE_MEM_SIZE_OF_DE  } ,
		},
		.frame_name = "DE_FRM",
		.frame_base = 0,
		.frame_size = VIDEO_L18_MEM_SIZE_OF_FRAME_DE,
#else
	.frame_name = "",
	.frame_base = 0,
	.frame_size = 0
#endif
	},

	// [3] for O18 FPGA
	{
#ifdef USE_KDRV_CODES_FOR_O18
		{
			{   "fw_led", 0, VIDEO_O18_FIRMWARE_MEM_SIZE_OF_LED } ,
			{   "fw_ipc", 0, VIDEO_O18_FIRMWARE_MEM_SIZE_OF_IPC } ,
			{   "fw_de",  0, VIDEO_O18_FIRMWARE_MEM_SIZE_OF_DE  } ,
		},
		.frame_name = "DE_FRM",
		.frame_base = 0,
		.frame_size = VIDEO_O18_MEM_SIZE_OF_FRAME_DE,
#else
	.frame_name = "",
	.frame_base = 0,
	.frame_size = 0
#endif
	},

	// [4] for M19 FPGA
	{
#ifdef USE_KDRV_CODES_FOR_M19
		{
			{   "fw_led", 0, VIDEO_M19_FIRMWARE_MEM_SIZE_OF_LED } ,
			{   "fw_ipc", 0, VIDEO_M19_FIRMWARE_MEM_SIZE_OF_IPC } ,
			{   "fw_de",  0, VIDEO_M19_FIRMWARE_MEM_SIZE_OF_DE  } ,
		},
		.frame_name = "DE_FRM",
		.frame_base = 0,
		.frame_size = VIDEO_M19_MEM_SIZE_OF_FRAME_DE,
#else
	.frame_name = "",
	.frame_base = 0,
	.frame_size = 0
#endif
	},

};

LX_DE_MEM_CFG_T gMemCfgDeFrameC[] =
{
    // for chroma buffer on E bus.
	{
#ifdef USE_KDRV_CODES_FOR_O18
		{
			{   "fw_led", 0, VIDEO_O18_FIRMWARE_MEM_SIZE_OF_LED } ,
			{   "fw_ipc", 0, VIDEO_O18_FIRMWARE_MEM_SIZE_OF_IPC } ,
			{   "fw_de",  0, VIDEO_O18_FIRMWARE_MEM_SIZE_OF_DE  } ,
		},

		.frame_name = "DE_FRAME_C",
		.frame_base = 0x0,
		.frame_size = VIDEO_O18_MEM_SIZE_OF_FRAME_C,
#endif
	},
};

LX_DE_CH_MEM_T gMemCfgDePreW[] =
{
	// for m17 1.5GB model
	{
#ifdef USE_KDRV_CODES_FOR_M17
		.fw_name = "DE_PreW",
		.fw_base = 0x0,
		.fw_size = VIDEO_M17_MEM_SIZE_OF_FRAME_PREW_15GB,
#endif
#ifdef USE_KDRV_CODES_FOR_M19
		.fw_name = "DE_PreW",
		.fw_base = 0x0,
		.fw_size = VIDEO_M19_MEM_SIZE_OF_FRAME_PREW_15GB,
#endif

	},
	// for m17 2GB/3GB model
	{
#ifdef USE_KDRV_CODES_FOR_M17
		.fw_name = "DE_PreW",
		.fw_base = 0x0,
		.fw_size = VIDEO_M17_MEM_SIZE_OF_FRAME_PREW,
#endif
#ifdef USE_KDRV_CODES_FOR_M19
		.fw_name = "DE_PreW",
		.fw_base = 0x0,
		.fw_size = VIDEO_M19_MEM_SIZE_OF_FRAME_PREW,
#endif

	},
};

LX_DE_CH_MEM_T gMemCfgDeFW[] =
{
	// [0] 
	{
#if defined(USE_KDRV_CODES_FOR_O18) || defined(USE_KDRV_CODES_FOR_M19)
		.fw_name = "DE_FW_LBUS",
		.fw_base = 0x0,
		.fw_size = 0x100000,// 1 MB
#else
		.fw_name = "DE_FW_LBUS",
		.fw_base = 0,
		.fw_size = 0,
#endif
	},

	// [1]  for  M1 MCU1 + shared mem
	{
#ifdef USE_KDRV_CODES_FOR_O18
		.fw_name = "DE_FW_MCU1",
		.fw_base = 0x0,
		.fw_size = 0x400000,// 4 MB
#else
		.fw_name = "DE_FW_MCU1",
		.fw_base = 0,
		.fw_size = 0,
#endif
	},

	// [2] for  M1 MCU0
	{
#if defined(USE_KDRV_CODES_FOR_O18) || defined(USE_KDRV_CODES_FOR_M19)
		.fw_name = "DE_FW_MCU0",
		.fw_base = 0x0,
		.fw_size = 0x400000,// 4 MB
#else
		.fw_name = "DE_FW_MCU0",
		.fw_base = 0,
		.fw_size = 0,
#endif
	},

	// [3] for O18 M0 MCU resereved
	{
#ifdef USE_KDRV_CODES_FOR_O18
		.fw_name = "DE_FW_MCU",
		.fw_base = 0x0,
		.fw_size = 0x100000,//
#else
		.fw_name = "DE_FW_MCU",
		.fw_base = 0,
		.fw_size = 0,
#endif
	},
};

/* AVTASK-343 */
LX_DE_CH_MEM_T gMemCfgDeFwO20[] =
{
	// [0] for MCU0
	{
		.fw_name = "DE_FW_O20_MCU0",
		.fw_base = 0x0,
		.fw_size = 0x00400000,// 4 MB
	},
	// [1] for MCU1
	{
		.fw_name = "DE_FW_O20_MCU1",
		.fw_base = 0x0,
		.fw_size = 0x00400000,// 4 MB
	},
	// [2] for MCU2
	{
		.fw_name = "DE_FW_O20_MCU2",
		.fw_base = 0x0,
		.fw_size = 0x01600000,//22 MB
	},
	// [3] for MCU3
	{
		.fw_name = "DE_FW_O20_MCU3",
		.fw_base = 0x0,
		.fw_size = 0x00200000,// 2 MB
	},
	// [4] for SHARED
	{
		.fw_name = "DE_FW_O20_SHARED",
		.fw_base = 0x0,
		.fw_size = 0x00200000,// 2 MB
	},
	// [5] for DNN
	{
		.fw_name = "DE_FW_O20_DNN",
		.fw_base = 0x0,
		.fw_size = 0x01800000,// 24MB : 20190611:AVTASK-343 19MB -> 23MB(+4),20190905:AVTASK-343 23MB -> 24MB(+1)
	},
	// [6] for MCU4
	{
		.fw_name = "DE_FW_O20_MCU4",
		.fw_base = 0x0,
		.fw_size = 0x00200000,// 2 MB : 20190611:new
	},
};

/* AVTASK-343 */
LX_DE_CH_MEM_T gMemCfgDeFwE60[] =
{
	// [0] for MCU0
	{
		.fw_name = "DE_FW_E60_MCU0",
		.fw_base = 0x0,
		.fw_size = 0x00400000,// 4 MB
	},
	// [1] for MCU1
	{
		.fw_name = "DE_FW_E60_MCU1",
		.fw_base = 0x0,
		.fw_size = 0x00400000,// 4 MB
	},
	// [2] for MCU2
	{
		.fw_name = "DE_FW_E60_MCU2",
		.fw_base = 0x0,
		.fw_size = 0x00A00000,//10 MB : 20200527:22MB->10MB(-12)
	},
	// [3] for MCU3
	{
		.fw_name = "DE_FW_E60_MCU3",
		.fw_base = 0x0,
		.fw_size = 0x00200000,// 2 MB
	},
	// [4] for SHARED
	{
		.fw_name = "DE_FW_E60_SHARED",
		.fw_base = 0x0,
		.fw_size = 0x00200000,// 2 MB
	},
	// [5] for DNN
	{
		.fw_name = "DE_FW_E60_DNN",
		.fw_base = 0x0,
		.fw_size = 0x00A00000,//10 MB : 20190611:19MB->23MB(+4),20190905:23MB->24MB(+1),20200527:24MB->10MB(-14)
	},
	// [6] for MCU4
	{
		.fw_name = "DE_FW_E60_MCU4",
		.fw_base = 0x0,
		.fw_size = 0x00000000,// 0 MB : 20190611:new,20200527:2MB->0MB(-2)
	},
};

LX_DE_MEM_CFG_T gMemCfgHDR[] =
{
    {
#ifdef USE_KDRV_CODES_FOR_M17
        .frame_name = "HDR",
        .frame_base = 0,
		.frame_size = VIDEO_M17_HDR_IPC_MEM_SIZE,
#elif defined(USE_KDRV_CODES_FOR_M19)
        .frame_name = "HDR",
        .frame_base = 0,
		.frame_size = VIDEO_M19_HDR_IPC_MEM_SIZE,
#else
		.frame_name = "HDR",
		.frame_base = 0,
		.frame_size = 0,
#endif
	},
	{
#ifdef USE_KDRV_CODES_FOR_O18
        .frame_name = "HDR",
        .frame_base = 0,
		.frame_size = VIDEO_O18_HDR_IPC_MEM_SIZE,
#else
		.frame_name = "HDR",
		.frame_base = 0,
		.frame_size = 0,
#endif
	},
	{
#ifdef USE_KDRV_CODES_FOR_O20
        .frame_name = "HDR",
        .frame_base = 0,
		.frame_size = VIDEO_O20_HDR_IPC_MEM_SIZE,
#else
		.frame_name = "HDR",
		.frame_base = 0,
		.frame_size = 0,
#endif
	},
	{
#ifdef USE_KDRV_CODES_FOR_E60
        .frame_name = "HDR",
        .frame_base = 0,
		.frame_size = VIDEO_E60_HDR_IPC_MEM_SIZE,
#else
		.frame_name = "HDR",
		.frame_base = 0,
		.frame_size = 0,
#endif
	}

};

LX_DE_MEM_CFG_T gMemCfgBT_CMA[] =
{
    {
#ifdef USE_KDRV_CODES_FOR_M17
        .frame_name = "BT",
        .frame_base = 0,
        .frame_size = VIDEO_M17_MEM_SIZE_OF_FRAME_DELAY,
#elif defined(USE_KDRV_CODES_FOR_M19)
        .frame_name = "BT",
        .frame_base = 0,
        .frame_size = VIDEO_M19_MEM_SIZE_OF_FRAME_DELAY,
#else
		.frame_name = "BT",
		.frame_base = 0,
		.frame_size = 0,
#endif
	},

    {
#ifdef USE_KDRV_CODES_FOR_O18
        .frame_name = "BT",
        .frame_base = 0,
        .frame_size = VIDEO_O18_MEM_SIZE_OF_FRAME_DELAY,
#else
		.frame_name = "BT",
		.frame_base = 0,
		.frame_size = 0,
#endif
	}

};

LX_DE_MEM_CFG_T gMemCfgVT_CMA[] =
{
	{
#ifdef USE_KDRV_CODES_FOR_M17
		.frame_name = "VT2K",
		.frame_base = 0,
		.frame_size = VIDEO_M17_MEM_SIZE_OF_VT_2K,
#elif defined(USE_KDRV_CODES_FOR_M19)
		.frame_name = "VT2K",
		.frame_base = 0,
		.frame_size = VIDEO_M19_MEM_SIZE_OF_VT_2K,
#else
		.frame_name = "VT",
		.frame_base = 0,
		.frame_size = 0,
#endif
	},

    {
#ifdef USE_KDRV_CODES_FOR_M17
        .frame_name = "VT4K",
        .frame_base = 0,
        .frame_size = VIDEO_M17_MEM_SIZE_OF_VT_4K,
#elif defined(USE_KDRV_CODES_FOR_M19)
        .frame_name = "VT4K",
        .frame_base = 0,
        .frame_size = VIDEO_M19_MEM_SIZE_OF_VT_4K,
#else
		.frame_name = "VT",
		.frame_base = 0,
		.frame_size = 0,
#endif
	},

	{
#ifdef USE_KDRV_CODES_FOR_O18
		.frame_name = "VT2K",
		.frame_base = 0,
		.frame_size = VIDEO_O18_MEM_SIZE_OF_VT_2K,
#else
		.frame_name = "VT",
		.frame_base = 0,
		.frame_size = 0,
#endif
	},

    {
#ifdef USE_KDRV_CODES_FOR_O18
        .frame_name = "VT4K",
        .frame_base = 0,
        .frame_size = VIDEO_O18_MEM_SIZE_OF_VT_4K,
#else
		.frame_name = "VT",
		.frame_base = 0,
		.frame_size = 0,
#endif
	}

};

LX_DE_CH_MEM_T gMemCfgO18[] =
{
#ifdef USE_KDRV_CODES_FOR_O18
	// [0] de_prew_m0_96
    {
        .fw_name = "DE_PREW_M0_96",
        .fw_base = 0,
        .fw_size = O18_DE_MEM_SIZE_PREW_M0_96,
	},
	// [1] de_frm_m1_96
	{
		.fw_name = "DE_FRM_M1_96",
		.fw_base = 0,
		.fw_size = O18_DE_MEM_SIZE_FRM_M1_96,
	},
	// [2] de_frm_m2_96
	{
		.fw_name = "DE_FRM_M2_96",
		.fw_base = 0,
		.fw_size = O18_DE_MEM_SIZE_FRM_M2_96,
	},
	// [3] de_prew_m0_80
	{
        .fw_name = "DE_PREW_M0_80",
        .fw_base = 0,
        .fw_size = O18_DE_MEM_SIZE_PREW_M0_80,
	},
	// [4] de_frm_m1_80
	{
        .fw_name = "DE_FRM_M1_80",
        .fw_base = 0,
        .fw_size = O18_DE_MEM_SIZE_FRM_M1_80,
	},
	// [5] de_frm_m2_80
	{
        .fw_name = "DE_FRM_M1_80",
        .fw_base = 0,
        .fw_size = O18_DE_MEM_SIZE_FRM_M2_80,
	},
	// [6] de_bt_m1
	{
        .fw_name = "DE_BT_M1",
        .fw_base = 0,
        .fw_size = O18_DE_MEM_SIZE_BT_M1,
	},
	// [7] de_bt_m2
	{
        .fw_name = "DE_BT_M2",
        .fw_base = 0,
        .fw_size = O18_DE_MEM_SIZE_BT_M2,
	},
	// [8] de_vt_m1
	{
        .fw_name = "DE_VT_M1",
        .fw_base = 0,
        .fw_size = O18_DE_MEM_SIZE_VT_M1,
	},
	// [9] de_vt_m2
	{
        .fw_name = "DE_VT_M2",
        .fw_base = 0,
        .fw_size = O18_DE_MEM_SIZE_VT_M2,
	},
#endif
};

LX_DE_CH_MEM_T gMemCfgM19[] =
{
#ifdef USE_KDRV_CODES_FOR_M19
	// [0] de_prew_m0
    {
        .fw_name = "DE_PREW_M0",
        .fw_base = 0,
        .fw_size = M19_DE_MEM_SIZE_PREW_M0 + M19_DE_MEM_SIZE_FRC_M0,
	},
	// [1] de_frm_m0
	{
		.fw_name = "DE_FRM_M0",
		.fw_base = 0,
		.fw_size = M19_DE_MEM_SIZE_FRM_M0,
	},
	// [2] de_frm_m1
	{
		.fw_name = "DE_FRM_M1",
		.fw_base = 0,
		.fw_size = M19_DE_MEM_SIZE_FRM_M1,
	},
	// [3] de_bt_m0
	{
        .fw_name = "DE_BT_M0",
        .fw_base = 0,
        .fw_size = M19_DE_MEM_SIZE_BT_M0,
	},
	// [4] de_bt_m1
	{
        .fw_name = "DE_BT_M1",
        .fw_base = 0,
        .fw_size = M19_DE_MEM_SIZE_BT_M1,
	},
	// [5] de_vt_m0
	{
        .fw_name = "DE_VT_M0",
        .fw_base = 0,
        .fw_size = M19_DE_MEM_SIZE_VT_M0,
	},
	// [6] de_vt_m1
	{
        .fw_name = "DE_VT_M1",
        .fw_base = 0,
        .fw_size = M19_DE_MEM_SIZE_VT_M1,
	},
#endif
};

LX_DE_CH_MEM_T gMemCfgO20[] =
{
#ifdef USE_KDRV_CODES_FOR_O20
	// [0] de_prew_m0
    {
        .fw_name = "DE_PREW_M0",
        .fw_base = 0,
        .fw_size = O20_DE_MEM_SIZE_PREW_M0,
	},
	// [1] de_frm_m0
	{
		.fw_name = "DE_FRM_M0",
		.fw_base = 0,
		.fw_size = O20_DE_MEM_SIZE_FRM_M0,
	},
	// [2] de_frm_m1
	{
		.fw_name = "DE_FRM_M1",
		.fw_base = 0,
		.fw_size = O20_DE_MEM_SIZE_FRM_M1,
	},
	// [3] de_bt_m0
	{
        .fw_name = "DE_BT_M0",
        .fw_base = 0,
        .fw_size = O20_DE_MEM_SIZE_BT_M0,
	},
	// [4] de_bt_m1
	{
        .fw_name = "DE_BT_M1",
        .fw_base = 0,
        .fw_size = O20_DE_MEM_SIZE_BT_M1,
	},
	// [5] de_vt_m0
	{
        .fw_name = "DE_VT_M0",
        .fw_base = 0,
        .fw_size = O20_DE_MEM_SIZE_VT_M0,
	},
	// [6] de_vt_m1
	{
        .fw_name = "DE_VT_M1",
        .fw_base = 0,
        .fw_size = O20_DE_MEM_SIZE_VT_M1,
	},
#endif
};

LX_DE_CH_MEM_T gMemCfgO20T[] =
{
#ifdef USE_KDRV_CODES_FOR_O20
	// [0] de_prew_m0
    {
        .fw_name = "DE_PREW_M0",
        .fw_base = 0,
        .fw_size = O20_DE_MEM_SIZE_PREW_M0,
	},
	// [1] de_frm_m0
	{
		.fw_name = "DE_FRM_M0",
		.fw_base = 0,
		.fw_size = O20T_DE_MEM_SIZE_FRM_M0,
	},
	// [2] de_frm_m1
	{
		.fw_name = "DE_FRM_M1",
		.fw_base = 0,
		.fw_size = O20T_DE_MEM_SIZE_FRM_M1,
	},
	// [3] de_bt_m0
	{
        .fw_name = "DE_BT_M0",
        .fw_base = 0,
        .fw_size = O20T_DE_MEM_SIZE_BT_M0,
	},
	// [4] de_bt_m1
	{
        .fw_name = "DE_BT_M1",
        .fw_base = 0,
        .fw_size = O20T_DE_MEM_SIZE_BT_M1,
	},
	// [5] de_vt_m0
	{
        .fw_name = "DE_VT_M0",
        .fw_base = 0,
        .fw_size = O20T_DE_MEM_SIZE_VT_M0,
	},
	// [6] de_vt_m1
	{
        .fw_name = "DE_VT_M1",
        .fw_base = 0,
        .fw_size = O20T_DE_MEM_SIZE_VT_M1,
	},
#endif
};

LX_DE_CH_MEM_T gMemCfgE60[] =
{
#ifdef USE_KDRV_CODES_FOR_E60
	// [0] de_prew_m0
    {
        .fw_name = "DE_PREW_M0",
        .fw_base = 0,
        .fw_size = E60_DE_MEM_SIZE_PREW_M0,
	},
	// [1] de_frm_m1
	{
		.fw_name = "DE_FRM_M1",
		.fw_base = 0,
		.fw_size = E60_DE_MEM_SIZE_FRM_M1,
	},
	// [2] de_frm_m2
	{
		.fw_name = "DE_FRM_M2",
		.fw_base = 0,
		.fw_size = E60_DE_MEM_SIZE_FRM_M2,
	},
	// [3] de_bt_m0
	{
        .fw_name = "DE_BT_M0",
        .fw_base = 0,
        .fw_size = E60_DE_MEM_SIZE_BT_M0,
	},
	// [4] de_bt_m1
	{
        .fw_name = "DE_BT_M1",
        .fw_base = 0,
        .fw_size = E60_DE_MEM_SIZE_BT_M1,
	},
	// [5] de_vt_m1
	{
        .fw_name = "DE_VT_M1",
        .fw_base = 0,
        .fw_size = (E60_DE_MEM_SIZE_VT_M1_VTG+E60_DE_MEM_SIZE_VT_M1_GAV),
	},
	// [6] de_vt_m2
	{
        .fw_name = "DE_VT_M2",
        .fw_base = 0,
        .fw_size = (E60_DE_MEM_SIZE_VT_M2_VTG+E60_DE_MEM_SIZE_VT_M2_GAV),
	},
#endif
};


LX_DE_MEM_CFG_T *gpDeMem = &gMemCfgDe[2];
LX_DE_MEM_CFG_T *gpDeMemC = &gMemCfgDeFrameC[0];   // for C buffer

#ifndef INCLUDE_KDRV_BE
BE_MEM_CFG_T gMemCfgBe[] =
{
	//[00]
	{
		{
			{	"fw_frc",	0x00000000,	0x00000000	},
			{	"fw_wcg",	0x00000000,	0x00180000	},
			{	"fw_led",	0x00000000,	0x00018000	},
			{	"fw_hdr",	0x00000000,	0x00008000	},
			{	"fw_ipc",	0x00000000,	0x00000000	},
			{	"fw_dnn",	0x00000000,	0x00000000	}
		},
		.frame_name = "BE_FRM",
		.frame_base = 0x00000000,
		.frame_size = 0x00000000
	},
};

BE_FRM_MEM_CFG_T gMemCfgBeFrc[] =
{
	// [0]
	{
		.frame_name = "be_fpp",
		.frame_base = 0x00000000,
		.frame_size = 0x00000000
	},
	// [1]
	{
		.frame_name = "be_frc0",
		.frame_base = 0x00000000,
		.frame_size = 0x00000000
	},
	// [2]
	{
		.frame_name = "be_frc1",
		.frame_base = 0x00000000,
		.frame_size = 0x00000000
	},
	// [3]
	{
		.frame_name = "be_frc2",
		.frame_base = 0x00000000,
		.frame_size = 0x00000000
	},
	// [4]
	{
		.frame_name = "be_frc3",
		.frame_base = 0x00000000,
		.frame_size = 0x00000000
	},
};

BE_FRM_MEM_CFG_T gMemCfgBeChInf[] =
{
	// [0]
	{
		.frame_name = "chipinfo",
		.frame_base = 0x00000000,
		.frame_size = 0x00100000
	}
};

BE_MEM_CFG_T *gpBeMem = NULL;
BE_FRM_MEM_CFG_T *gpBeChInfMem = NULL;
#endif

#ifndef INCLUDE_KDRV_PE
PE_MEM_CFG_T gMemCfgPe[] =
{
	//[00]
	{
		{
			{	"pe_db0",	0x00000000,	0x00200000},//2MB, NR,SCL,SR
			{	"pe_db1",	0x00000000,	0x00100000},//1MB, HDR
			{	"pe_db2",	0x00000000,	0x00000000},
			{	"pe_db3",	0x00000000,	0x00000000}
		},
	},
};
#endif

LX_MEMCFG_T g_m0_pqe_svp = {.name = "g_m0_pqe_svp",.base = 0,.size = 0};
LX_MEMCFG_T g_m0_pqe_svp_end = {.name = "g_m0_pqe_svp_end",.base = 0,.size = 0};

LX_MEMCFG_T g_m0_pqe_nsv = {.name = "g_m0_pqe_nsv",.base = 0,.size = 0};
LX_MEMCFG_T g_m0_pqe_nsv_end = {.name = "g_m0_pqe_nsv_end",.base = 0,.size = 0};

LX_MEMCFG_T g_m0_pqe_usr = {.name = "g_m0_pqe_usr",.base = 0,.size = 0};
LX_MEMCFG_T g_m0_pqe_usr_end = {.name = "g_m0_pqe_usr_end",.base = 0,.size = 0};

LX_MEMCFG_T g_m1_pqe_svp = {.name = "g_m1_pqe_svp",.base = 0,.size = 0};
LX_MEMCFG_T g_m1_pqe_svp_end = {.name = "g_m1_pqe_svp_end",.base = 0,.size = 0};

LX_MEMCFG_T g_m1_pqe_nsv = {.name = "g_m1_pqe_nsv",.base = 0,.size = 0};
LX_MEMCFG_T g_m1_pqe_nsv_end = {.name = "g_m1_pqe_nsv_end",.base = 0,.size = 0};

LX_MEMCFG_T g_m1_pqe_usr = {.name = "g_m1_pqe_usr",.base = 0,.size = 0};
LX_MEMCFG_T g_m1_pqe_usr_end = {.name = "g_m1_pqe_usr_end",.base = 0,.size = 0};

LX_MEMCFG_T g_m2_pqe_svp = {.name = "g_m2_pqe_svp",.base = 0,.size = 0};
LX_MEMCFG_T g_m2_pqe_svp_end = {.name = "g_m2_pqe_svp_end",.base = 0,.size = 0};

LX_MEMCFG_T g_m2_pqe_nsv = {.name = "g_m2_pqe_nsv",.base = 0,.size = 0};
LX_MEMCFG_T g_m2_pqe_nsv_end = {.name = "g_m2_pqe_nsv_end",.base = 0,.size = 0};

LX_MEMCFG_T g_m2_pqe_usr = {.name = "g_m2_pqe_usr",.base = 0,.size = 0};
LX_MEMCFG_T g_m2_pqe_usr_end = {.name = "g_m2_pqe_usr_end",.base = 0,.size = 0};

LX_MEMCFG_T g_fw_mcu0 = {.name = "g_fw_mcu0",.base = 0,.size = 0};
LX_MEMCFG_T g_de_svp_m0 = {.name = "g_de_svp_m0",.base = 0,.size = 0};
LX_MEMCFG_T g_de_svp_m1 = {.name = "g_de_svp_m1",.base = 0,.size = 0};
LX_MEMCFG_T g_de_svp_m2 = {.name = "g_de_svp_m2",.base = 0,.size = 0};
LX_MEMCFG_T g_de_nsvp_m1 = {.name = "g_de_nsvp_m1",.base = 0,.size = 0};
LX_MEMCFG_T g_de_nsvp_m2 = {.name = "g_de_nsvp_m2",.base = 0,.size = 0};
LX_MEMCFG_T g_de_vt_m1 = {.name = "g_de_vt_m1",.base = 0,.size = 0};
LX_MEMCFG_T g_de_vt_m2 = {.name = "g_de_vt_m2",.base = 0,.size = 0};
LX_MEMCFG_T g_de_hdr = {.name = "g_de_hdr",.base = 0,.size = 0};
LX_MEMCFG_T g_be_fpp = {.name = "g_be_fpp",.base = 0,.size = 0};
LX_MEMCFG_T g_be_frc0 = {.name = "g_be_frc0",.base = 0,.size = 0};
LX_MEMCFG_T g_be_frc1 = {.name = "g_be_frc1",.base = 0,.size = 0};
LX_MEMCFG_T g_be_frc2 = {.name = "g_be_frc2",.base = 0,.size = 0};
LX_MEMCFG_T g_be_wcg = {.name = "g_be_wcg",.base = 0,.size = 0};
LX_MEMCFG_T g_pe_db = {.name = "g_pe_db",.base = 0,.size = 0};
LX_MEMCFG_T g_pe_hdr = {.name = "g_pe_hdr",.base = 0,.size = 0};
LX_MEMCFG_T g_fw_dnn = {.name = "g_fw_dnn",.base = 0,.size = 0};
LX_MEMCFG_T g_fw_mcu1 = {.name = "g_fw_mcu1",.base = 0,.size = 0};
LX_MEMCFG_T g_fw_mcu2 = {.name = "g_fw_mcu2",.base = 0,.size = 0};
LX_MEMCFG_T g_fw_mcu3 = {.name = "g_fw_mcu3",.base = 0,.size = 0};
LX_MEMCFG_T g_fw_shared = {.name = "g_fw_shared",.base = 0,.size = 0};
LX_MEMCFG_T g_fw_mcu4 = {.name = "g_fw_mcu4",.base = 0,.size = 0};
LX_MEMCFG_T g_be_led = {.name = "g_be_led",.base = 0,.size = 0};
LX_MEMCFG_T g_be_phdr = {.name = "g_be_phdr",.base = 0,.size = 0};
LX_MEMCFG_T g_chipinfo = {.name = "g_chipinfo",.base = 0,.size = 0};
LX_MEMCFG_T g_de_dbg_m1 = {.name = "g_de_dbg_m1",.base = 0,.size = 0};
LX_MEMCFG_T g_de_dbg_m2 = {.name = "g_de_dbg_m2",.base = 0,.size = 0};
LX_MEMCFG_T g_mcu0_dbg = {.name = "g_mcu0_dbg",.base = 0,.size = 0};
LX_MEMCFG_T g_mcu1_dbg = {.name = "g_mcu1_dbg",.base = 0,.size = 0};

UINT32 g_de_vt_m1_cma_size = 0;
UINT32 g_de_vt_m2_cma_size = 0;
UINT32 g_de_vpb8k_cma_size = 0;
UINT32 g_de_vdec_shared_size = 0;
UINT32 g_de_pqe_bwb_size = 0;

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
static struct de_cfg_ctx _g_de_cfg_ctx;

/*========================================================================================
    Implementation Group
========================================================================================*/
int de_cfg_preinit(void)
{
	int ret = 0;

	memset(&_g_de_cfg_ctx,0,sizeof(_g_de_cfg_ctx));

	if (0) { }
	#ifdef USE_KDRV_CODES_FOR_O26
	else if (lx_chip() == LX_CHIP_O26)
	{
		_g_de_cfg_ctx.preinit = de_cfg_o26_preinit;
		_g_de_cfg_ctx.init    = de_cfg_o26_init;
		_g_de_cfg_ctx.cleanup = de_cfg_o26_cleanup;
	}
	#endif
	#ifdef USE_KDRV_CODES_FOR_O24
	else if (lx_chip() == LX_CHIP_O24)
	{
		_g_de_cfg_ctx.preinit = de_cfg_o24_preinit;
		_g_de_cfg_ctx.init    = de_cfg_o24_init;
		_g_de_cfg_ctx.cleanup = de_cfg_o24_cleanup;
	}
	#endif
	#ifdef USE_KDRV_CODES_FOR_M23
	else if (lx_chip() == LX_CHIP_M23)
	{
		_g_de_cfg_ctx.preinit = de_cfg_m23_preinit;
		_g_de_cfg_ctx.init    = de_cfg_m23_init;
		_g_de_cfg_ctx.cleanup = de_cfg_m23_cleanup;
	}
	#endif
	#ifdef USE_KDRV_CODES_FOR_O22
	else if (lx_chip() == LX_CHIP_O22)
	{
		_g_de_cfg_ctx.preinit = de_cfg_o22_preinit;
		_g_de_cfg_ctx.init    = de_cfg_o22_init;
		_g_de_cfg_ctx.cleanup = de_cfg_o22_cleanup;
	}
	#endif
	#ifdef USE_KDRV_CODES_FOR_O20
	#ifdef PQE_NEW_MAP
	else if (lx_chip() == LX_CHIP_O20)
	{
		_g_de_cfg_ctx.preinit = de_cfg_o20_preinit;
		_g_de_cfg_ctx.init    = de_cfg_o20_init;
		_g_de_cfg_ctx.cleanup = de_cfg_o20_cleanup;
	}
	#endif
	#endif
	else
	{
		DE_NOTI("not support (chip:0x%x)\n", lx_chip());
	}

	if(_g_de_cfg_ctx.preinit)
	{
		ret = _g_de_cfg_ctx.preinit();
	}
	return ret;
}

int de_cfg_init(void)
{
	int ret = 0;
	if(_g_de_cfg_ctx.init)
	{
		ret = _g_de_cfg_ctx.init();
	}
	return ret;
}

int de_cfg_cleanup(void)
{
	int ret = 0;
	if(_g_de_cfg_ctx.cleanup)
	{
		ret = _g_de_cfg_ctx.cleanup();
	}
	return ret;
}

void de_cfg_print_status(struct seq_file *m)
{
	if (0) { }
	#ifdef USE_KDRV_CODES_FOR_O26
	else if (lx_chip() == LX_CHIP_O26)
	{
		extern void de_cfg_o26_print_status(struct seq_file *m);
		de_cfg_o26_print_status(m);
	}
	#endif
	#ifdef USE_KDRV_CODES_FOR_O24
	else if (lx_chip() == LX_CHIP_O24)
	{
		extern void de_cfg_o24_print_status(struct seq_file *m);
		de_cfg_o24_print_status(m);
	}
	#endif
	#ifdef USE_KDRV_CODES_FOR_M23
	else if (lx_chip() == LX_CHIP_M23)
	{
		extern void de_cfg_m23_print_status(struct seq_file *m);
		de_cfg_m23_print_status(m);
	}
	#endif
	#ifdef USE_KDRV_CODES_FOR_O22
	else if (lx_chip() == LX_CHIP_O22)
	{
		extern void de_cfg_o22_print_status(struct seq_file *m);
		de_cfg_o22_print_status(m);
	}
	#endif
	#ifdef USE_KDRV_CODES_FOR_O20
	#ifdef PQE_NEW_MAP
	else if (lx_chip() == LX_CHIP_O20)
	{
		extern void de_cfg_o20_print_status(struct seq_file *m);
		de_cfg_o20_print_status(m);
	}
	#endif
	#endif
	else
	{
		seq_printf(m, "not support (chip:0x%x)\n", lx_chip());
	}
}

/* see SCDCR-5249, AVTASK-967 */
/* if complete, ret 0, else -1 */
int de_cfg_check_force_hma_pool(const char *pool_name, UINT32 pool_type, UINT32 base_addr, int alloc_size)
{
	char hma_name[32];

	if (!pool_name)
	{
		DE_ERROR("pool_name null\n");
		return -1;
	}

	if ((pool_type == HMA_POOL) || (false == check_force_hma_pool(pool_name)))
	{
		return -1;//do nothing
	}

	if (base_addr == 0)
	{
		DE_ERROR("base_addr error\n");
		return -1;
	}

	if (alloc_size <= 0)
	{
		DE_ERROR("alloc_size error\n");
		return -1;
	}

	memset(hma_name,0,32);
	snprintf(hma_name,32,"%s_hma",pool_name);

	if (hma_pool_register_type(hma_name,base_addr,alloc_size,CMA_POOL) < 0)
	{
		DE_ERROR("hma_pool_register_type error\n");
		return -1;
	}

	if (hma_alloc(hma_name,alloc_size,(1<<14)) == 0)
	{
		DE_ERROR("hma_alloc error\n");
		return -1;
	}

	DE_NOTI("%s is forced to set as HMA (%s)(0x%08x)(%d kB)\n",pool_name,hma_name,base_addr,alloc_size>>10);

	return 0;
}

int de_cfg_disply(void)
{
	int ret = RET_OK;
	int idx = 0;
	char *fw_name[5] = { NULL }, *frame_name = 0;
	int  fw_base[5] = { 0 },  frame_base = 0;
	int  fw_size[5] = { 0 },  frame_size = 0;

	fw_name[0] = gMemCfgDe[idx].fw[0].fw_name;
	fw_base[0] = gMemCfgDe[idx].fw[0].fw_base;
	fw_size[0] = gMemCfgDe[idx].fw[0].fw_size;
	fw_name[1] = gMemCfgDe[idx].fw[1].fw_name;
	fw_base[1] = gMemCfgDe[idx].fw[1].fw_base;
	fw_size[1] = gMemCfgDe[idx].fw[1].fw_size;
	fw_name[2] = gMemCfgDe[idx].fw[2].fw_name;
	fw_base[2] = gMemCfgDe[idx].fw[2].fw_base;
	fw_size[2] = gMemCfgDe[idx].fw[2].fw_size;

	frame_name = gMemCfgDe[idx].frame_name;
	frame_base = gMemCfgDe[idx].frame_base;
	frame_size = gMemCfgDe[idx].frame_size;

	DE_PRINT("List of memory map\n");
	DE_PRINT("\tframe name : %s\n", frame_name);
	DE_PRINT("\tframe base : 0x%08x\n", frame_base);
	DE_PRINT("\tframe size : %d\n", frame_size);
	DE_PRINT("\t  fw[0]\n");
	DE_PRINT("\t    name : %s\n", fw_name[0]);
	DE_PRINT("\t    base : 0x%08x\n", fw_base[0]);
	DE_PRINT("\t    size : %d\n", fw_size[0]);
	DE_PRINT("\t  fw[1]\n");
	DE_PRINT("\t    name : %s\n", fw_name[1]);
	DE_PRINT("\t    base : 0x%08x\n", fw_base[1]);
	DE_PRINT("\t    size : %d\n", fw_size[1]);
	DE_PRINT("\t  fw[2]\n");
	DE_PRINT("\t    name : %s\n", fw_name[2]);
	DE_PRINT("\t    base : 0x%08x\n", fw_base[2]);
	DE_PRINT("\t    size : %d\n", fw_size[2]);
#ifdef USE_DE_FIRMWARE_DOWNLOAD_FROM_LBUS
	DE_PRINT("\t  fw is running on L-BUS\n");
#else
	DE_PRINT("\t  fw is running on G-BUS\n");
#endif
	if(fw_size[3])
	{
		DE_PRINT("\tframe name : %s\n", fw_name[3]);
		DE_PRINT("\tframe base : 0x%08x\n", fw_base[3]);
		DE_PRINT("\tframe size : %d\n", fw_size[3]);
	}
	else
	{
		DE_PRINT("\tframe name : %s isn't allocated on external frame memory\n",\
				fw_name[3]);
	}
	if(fw_size[4])
	{
		DE_PRINT("\tframe name : %s\n", fw_name[4]);
		DE_PRINT("\tframe base : 0x%08x\n", fw_base[4]);
		DE_PRINT("\tframe size : %d\n", fw_size[4]);
	}
	else
	{
		DE_PRINT("\tframe name : %s isn't allocated on external frame memory\n",\
				fw_name[3]);
	}

	return ret;
}

int de_cfg_get_sharedmem(UINT32 page_offset, UINT32 *mem0, UINT32 *mem1, UINT32 *size)
{
	int ret = RET_OK;

	{
#ifdef USE_KDRV_CODES_FOR_M17
		*mem0 = gMemCfgDeFW[0].fw_base;
		*mem1 = gMemCfgDeFW[0].fw_base + gMemCfgDeFW[0].fw_size;
		*size = gMemCfgDeFW[0].fw_size;
#endif
#ifdef USE_KDRV_CODES_FOR_M19
		*mem0 = gMemCfgDeFW[0].fw_base;
		*mem1 = gMemCfgDeFW[0].fw_base + gMemCfgDeFW[0].fw_size;
		*size = gMemCfgDeFW[0].fw_size;
#endif
#ifdef USE_KDRV_CODES_FOR_L18
		*mem0 = VIDEO_L18_FIRMWARE_MEM_BASE_OF_DE;
		*mem1 = VIDEO_L18_FIRMWARE_MEM_BASE_OF_DE + 2 * 1024 * 1024;
		*size = 2 * 1024 * 1024;
#endif
#ifdef USE_KDRV_CODES_FOR_O18
		*mem0 = gMemCfgDeFW[1].fw_base;
		*mem1 = gMemCfgDeFW[1].fw_base + gMemCfgDeFW[1].fw_size;
		*size = gMemCfgDeFW[1].fw_size;
#endif
	}

	return ret;
}

/** @} */
