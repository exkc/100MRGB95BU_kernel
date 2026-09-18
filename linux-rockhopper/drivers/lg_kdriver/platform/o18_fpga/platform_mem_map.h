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

/*----------------------------------------------------------------------------------------
	COMMON MEMORY MAP
----------------------------------------------------------------------------------------*/
// real DDR calibration size is 32 bye, but I will reserve 16 KB for address alignment.
//
#define DDR_CALIB_RGN_SZ    		__KB(16)

// set the memory size for the static address-assigned deivces.
// this region is composed of:
//
// - M0:  1 MB sized general purpose region
// - M0: 15 MB sized TZ/SE region
//
// - M1: 64 KB sized demod fw load region
//
#define M0_SYSTEM_RGN_SZ       		__MB(16)
#define M1_SYSTEM_RGN_SZ			DDR_CALIB_RGN_SZ


#define UHD_LM_DEV_RGN_END			0x80000000
#define UHD_GM_DEV_RGN_END			0xC0000000

//----------------------------------------------------------------------------------------
//	4K UHD MEMORY MAP (ADVANCED Model 3.0GB)
//----------------------------------------------------------------------------------------
#define	UHD_LM_3_0GB_DEV_RGN_BASE	0x51800000
#define	UHD_LM_3_0GB_DEV_RGN_SZ		(UHD_LM_DEV_RGN_END-UHD_LM_3_0GB_DEV_RGN_BASE)
#define	UHD_GM_3_0GB_DEV_RGN_BASE	0xa8c00000
#define	UHD_GM_3_0GB_DEV_RGN_SZ		(UHD_GM_DEV_RGN_END-UHD_GM_3_0GB_DEV_RGN_BASE)

//----------------------------------------------------------------------------------------
//	4K UHD MEMORY MAP (ADVANCED Model 2.0GB)
//----------------------------------------------------------------------------------------
#define	UHD_LM_2_0GB_DEV_RGN_BASE	0x30000000	//0x58000000
#define	UHD_LM_2_0GB_DEV_RGN_SZ		(UHD_LM_DEV_RGN_END-UHD_LM_2_0GB_DEV_RGN_BASE)
#define	UHD_GM_2_0GB_DEV_RGN_BASE	0x80000000	//0xa8c00000
#define	UHD_GM_2_0GB_DEV_RGN_SZ		(UHD_GM_DEV_RGN_END-UHD_GM_2_0GB_DEV_RGN_BASE)

//----------------------------------------------------------------------------------------
//	4K UHD MEMORY MAP (STANDARD Model 1.5GB)
//----------------------------------------------------------------------------------------
#define	UHD_LM_1_5GB_DEV_RGN_BASE	0x61400000
#define	UHD_LM_1_5GB_DEV_RGN_SZ		(UHD_LM_DEV_RGN_END-UHD_LM_1_5GB_DEV_RGN_BASE)
#define	UHD_GM_1_5GB_DEV_RGN_BASE	0xae000000
#define	UHD_GM_1_5GB_DEV_RGN_SZ		(UHD_GM_DEV_RGN_END-UHD_GM_1_5GB_DEV_RGN_BASE)

//----------------------------------------------------------------------------------------
//	4K UHD MEMORY MAP (STANDARD Model 1.5GB /w DolbyHDR support)
//----------------------------------------------------------------------------------------
#define	UHD_LM_1_5GB_TINY_HDR_DEV_RGN_BASE		0x5d000000	/* FIXME : tune new base address (raxis.lim@2016/09/21) */
#define	UHD_LM_1_5GB_TINY_HDR_DEV_RGN_SZ		(UHD_LM_DEV_RGN_END-UHD_LM_1_5GB_TINY_HDR_DEV_RGN_BASE)
#define	UHD_GM_1_5GB_TINY_HDR_DEV_RGN_BASE		UHD_GM_1_5GB_DEV_RGN_BASE
#define	UHD_GM_1_5GB_TINY_HDR_DEV_RGN_SZ		(UHD_GM_DEV_RGN_END-UHD_GM_1_5GB_TINY_HDR_DEV_RGN_BASE)

//----------------------------------------------------------------------------------------
//	4K UHD MEMORY MAP (MODULE SIZE)
//----------------------------------------------------------------------------------------
#define	UHD_GFXOSD_SZ					__MB(124)
#define	UHD_VDEC_4K_4K_HMA_SZ			__MB(480)	/* fix value after lxboot change */
#define	UHD_VDEC_4K_2K_HMA_SZ			__MB(376)
#define	UHD_VDEC_4K_HMA_SZ				__MB(272)

#define	UHD_VDEC_4K_TINY_HDR_HMA0_SZ	__MB(272)
#define	UHD_VDEC_4K_TINY_HDR_HMA1_SZ	__MB(64)

//----------------------------------------------------------------------------------------
//	ETC
//----------------------------------------------------------------------------------------

#endif /* __PLATFORM_MEM_MAP_H__ */


