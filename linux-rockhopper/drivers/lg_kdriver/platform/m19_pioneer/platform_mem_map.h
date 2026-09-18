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
 *	platform dependent memory configuration header
 *
 */
#ifndef __PLATFORM_MEM_MAP_H__
#define __PLATFORM_MEM_MAP_H__

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#undef		USE_TEST_RGN_MAP
//#define	USE_DEMOD_DEDICATED_MEMORY	/* by default, demod 12MB will be allocated from TE shared memory */
#define  	USE_AUDIO_STATIC_RGN

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define __MB(v)						((v)<<20)
#define __KB(v)						((v)<<10)

#define	__RGN_BASE(a0,b0)			(lx_chip_rev() < LX_CHIP_REV(M17,C0))? (a0):(b0)

/*----------------------------------------------------------------------------------------
	COMMON MEMORY MAP
----------------------------------------------------------------------------------------*/
// real DDR calibration size is 32 bye, but I will reserve 16 KB for address alignment.
//
#define DDR_CALIB_RGN_SZ			__KB(16)

// set the memory size for the static address-assigned deivces.
// this region is composed of:
//
// - M0:  1 MB sized general purpose region
// - M0: 15 MB sized TZ/SE region
//
// - M1: 64 KB sized demod fw load region
//
#define M0_SYSTEM_RGN_SZ			__MB(24)
#define M1_SYSTEM_RGN_SZ			DDR_CALIB_RGN_SZ

#define LM_DEV_RGN_END				0x80000000
#define GM_DEV_RGN_END				0xC0000000

//----------------------------------------------------------------------------------------
//	4K UHD MEMORY MAP (ADVANCED Model 3.0GB)
//
//	SICDTV-5366 : r3.1 BSP memory map
//----------------------------------------------------------------------------------------
#define	LM_3_0GB_DEV_RGN_A0_BASE	0x50800000
#define	GM_3_0GB_DEV_RGN_A0_BASE	0xa7000000

//----------------------------------------------------------------------------------------
//	4K UHD MEMORY MAP (ADVANCED Model 2.0GB)
//
//	SICDTV-5366 : r3.1 BSP memory map
//	SICDTV-5477 : r3.3 BSP memory map
//	SICDTV-5549 : r4.2 BSP memory map
//	SICDTV-5788 : r4.3 BSP memory map
//	SICDTV-6782 : r4.4 BSP memory map
//----------------------------------------------------------------------------------------
#define	LM_2_0GB_DEV_RGN_A0_BASE	0x4F400000
#define	GM_2_0GB_DEV_RGN_A0_BASE	0xAF000000

//----------------------------------------------------------------------------------------
//	4K UHD MEMORY MAP (MODULE SIZE)
//----------------------------------------------------------------------------------------
#define	UHD_GFXOSD_SZ				(__MB(124))
#define UHD_VDEC0_HMA_SZ			(UHD_VDEC0_DPB_SZ+UHD_VDEC0_HFR_SZ)	// VDEC DPB+HFR
#define	UHD_VDEC1_HMA_SZ			(UHD_VDEC1_CPB_SZ+UHD_VDEC1_MCU_SZ)	// VDEC CPB+MCU


#define UHD_VDEC0_DPB_SZ			((g_model_ctx.ddr_size==MODEL_OPT_DDR_3_0_GB_ADV)? __MB(360):__MB(316) - UHD_VDEC0_HFR_SZ)
#define	UHD_VDEC0_HFR_SZ			(__MB(0)) //(__MB(49))				// support SICDTV-5504
#define UHD_VDEC1_CPB_SZ			(__MB(24))
#define UHD_VDEC1_MCU_SZ			(__MB(28))

#define UHD_AUDIO_SZ				(__MB(53) + __KB(512))

//----------------------------------------------------------------------------------------
//	ETC
//----------------------------------------------------------------------------------------

#endif /* __PLATFORM_MEM_MAP_H__ */


