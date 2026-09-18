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
#undef	USE_TEST_RGN_MAP
#undef	USE_DEMOD_DEDICATED_MEMORY	/* by default, demod 12MB will be allocated from TE shared memory */

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define __MB(v)						((v)<<20)
#define __KB(v)						((v)<<10)

#define	__RGN_BASE(a0,b0)				(lx_chip_rev() < LX_CHIP_REV(M17,C0))? (a0):(b0)

/*----------------------------------------------------------------------------------------
	COMMON MEMORY MAP
----------------------------------------------------------------------------------------*/
// real DDR calibration size is 32 bye, but I will reserve 16 KB for address alignment.
//
//#define DDR_CALIB_RGN_SZ    		__KB(16)
#define DDR_CALIB_RGN_SZ    		0

// set the memory size for the static address-assigned deivces.
// this region is composed of:
//
// - M0:  1 MB sized general purpose region
// - M0: 15 MB sized TZ/SE region
//
// - M1: 64 KB sized demod fw load region
//
//#define M0_SYSTEM_RGN_SZ       		__MB(16)
#define M0_SYSTEM_RGN_SZ       		0
#define M1_SYSTEM_RGN_SZ			DDR_CALIB_RGN_SZ


#define LM_DEV_RGN_END			0x80000000
#define GM_DEV_RGN_END			0xC0000000

//----------------------------------------------------------------------------------------
//	4K UHD MEMORY MAP (ADVANCED Model 3.0GB)
//----------------------------------------------------------------------------------------
#define	LM_3_0GB_DEV_RGN_A0_BASE	0x4fc00000
#define	GM_3_0GB_DEV_RGN_A0_BASE	0xa8800000

#define	LM_3_0GB_DEV_RGN_C0_BASE	0x4fc00000
#define	GM_3_0GB_DEV_RGN_C0_BASE	0xa5c00000

//----------------------------------------------------------------------------------------
//	4K UHD MEMORY MAP (ADVANCED Model 2.0GB)
//----------------------------------------------------------------------------------------
//#define	LM_2_0GB_DEV_RGN_A0_BASE	0x72C00000
#define	LM_2_0GB_DEV_RGN_A0_BASE	0x10000000  //nalm
//#define	GM_2_0GB_DEV_RGN_A0_BASE	0x8E400000
#define	GM_2_0GB_DEV_RGN_A0_BASE	0x80000000      //nalm
//#define	LM_2_0GB_DEV_RGN_A0_BASE	0x56400000
//#define	GM_2_0GB_DEV_RGN_A0_BASE	0xa8800000

#define	LM_2_0GB_DEV_RGN_C0_BASE	0x10000000      //nalm
#define	GM_2_0GB_DEV_RGN_C0_BASE	0x80000000      //nalm
//#define	LM_2_0GB_DEV_RGN_C0_BASE	0x56400000
//#define	GM_2_0GB_DEV_RGN_C0_BASE	0xa5c00000

//----------------------------------------------------------------------------------------
//	4K UHD MEMORY MAP (STANDARD Model 1.5GB)
//----------------------------------------------------------------------------------------
#define	LM_1_5GB_DEV_RGN_A0_BASE	0x61400000
#define	GM_1_5GB_DEV_RGN_A0_BASE	0xadc00000

#define	LM_1_5GB_DEV_RGN_C0_BASE	0x61400000
#define	GM_1_5GB_DEV_RGN_C0_BASE	0xadc00000

//----------------------------------------------------------------------------------------
//	4K UHD MEMORY MAP (MODULE SIZE)
//----------------------------------------------------------------------------------------
#define	UHD_GFXOSD_SZ					__MB(124)
//#define	UHD_GFXOSD_SZ					__MB(64)
#define	UHD_VDEC_4K_4K_HMA_SZ			__MB(480)
//#define	UHD_VDEC_4K_2K_HMA_SZ			__MB(376)
#define	UHD_VDEC_4K_2K_HMA_SZ			__MB(1024)      //nalm
#define	UHD_VDEC_4K_HMA_SZ				__MB(272)

#define	UHD_VDEC_4K_4K_DPB_SZ			__MB(436)
//#define	UHD_VDEC_4K_2K_DPB_SZ			__MB(332)
#define	UHD_VDEC_4K_2K_DPB_SZ			__MB(960)   //nalm
#define	UHD_VDEC_4K_DPB_SZ				__MB(228)
#define	UHD_VDEC_CPB_SZ					__MB(24)

#define	UHD_AUDIO_STD_SZ				__MB(36)	/* 35.6 MB */
//#define	UHD_AUDIO_ADV_SZ				__MB(71)	/* 70.x MB */
#define	UHD_AUDIO_ADV_SZ				__MB(64)	/* 64 MB */

//----------------------------------------------------------------------------------------
//	ETC
//----------------------------------------------------------------------------------------

#endif /* __PLATFORM_MEM_MAP_H__ */


