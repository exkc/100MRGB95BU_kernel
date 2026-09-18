/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */
/**
 *  platform dependent memory configuration header
 *
 */
#ifndef __PLATFORM_MEM_MAP_H__
#define __PLATFORM_MEM_MAP_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
#define __MB(v)             ((v)<<20)
#define __KB(v)             ((v)<<10)

/*----------------------------------------------------------------------------------------
    COMMON MEMORY MAP
----------------------------------------------------------------------------------------*/
#define DDR_CALIB_RGN_SZ    0

#define DEV_MEM_END         0xC0000000
#define DEV_MEM_BASE        (KERNEL_SZ)
#define DEV_MEM_SZ          (DEV_MEM_END-DEV_MEM_BASE)

//----------------------------------------------------------------------------------------
//  4K UHD MEMORY MAP (ADVANCED Model 3.0GB)
//----------------------------------------------------------------------------------------
#define KERNEL_SZ           __MB(256)
#define FPGA_MEM0_BASE      0x10000000	// gfx, vdec cpb, et
#define FPGA_MEM1_BASE      0x1C000000	// vdec dpb
#define FPGA_MEM2_BASE      0x5C000000	// ven, lnx, te
#define FPGA_MEM3_BASE      0x68000000	// lnx2
#define FPGA_MEM4_BASE      0x6C000000	// audio, pqe m1
#define FPGA_MEM5_BASE      0x90000000	// pqe m2
#define FPGA_MEM6_BASE      0xB8000000	// pqe m0 & fw

//----------------------------------------------------------------------------------------
//  MODULE SIZE
//----------------------------------------------------------------------------------------
#define FPGA_GFXOSD_SZ      __MB(128)
#define FPGA_VPB_SZ         __MB(448)
#define FPGA_CPB_SZ         __MB(64)
#define FPGA_GEN_SZ         __MB(4)
//#define FPGA_VENC_SZ      __MB(128)
#define FPGA_AUDIO_SZ       __MB(80)
#define FPGA_AUDIO_LNX_SZ   __MB(30)

#define LNE_BUFFER_SZ       __MB(64)

#define M0_DEBUG_SZ         __MB(16)
#define M1_DEBUG_SZ         __MB(0)

//----------------------------------------------------------------------------------------
//  ETC
//----------------------------------------------------------------------------------------

#endif							/* __PLATFORM_MEM_MAP_H__ */
