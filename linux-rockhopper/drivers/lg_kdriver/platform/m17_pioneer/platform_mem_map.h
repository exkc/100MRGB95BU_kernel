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
#undef	USE_DEMOD_DEDICATED_MEMORY	/* by default, demod 12MB will be allocated from TE shared memory */
#undef	USE_AUDIO_STATIC_RGN		/* use static address region for AUDIO if necessary */
#define	USE_HEVC_4K_HFR_MEM_MAP		/* support memory map for HEVC 4K120 decoding */

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


#define LM_DEV_RGN_END				0x80000000
#define GM_DEV_RGN_END				0xC0000000

//----------------------------------------------------------------------------------------
//	4K UHD MEMORY MAP (ADVANCED Model 3.0GB)
//----------------------------------------------------------------------------------------
#define	LM_3_0GB_DEV_RGN_A0_BASE	0x4fc00000
#define	GM_3_0GB_DEV_RGN_A0_BASE	0xa8800000

#define	LM_3_0GB_DEV_RGN_C0_BASE	0x57000000
#define	GM_3_0GB_DEV_RGN_C0_BASE	0x9e400000

//----------------------------------------------------------------------------------------
//	4K UHD MEMORY MAP (ADVANCED Model 2.0GB)
//----------------------------------------------------------------------------------------
#define	LM_2_0GB_DEV_RGN_A0_BASE	0x56400000
#define	GM_2_0GB_DEV_RGN_A0_BASE	0xa8800000

#define	LM_2_0GB_DEV_RGN_C0_BASE	0x57000000
#define	GM_2_0GB_DEV_RGN_C0_BASE	0x9e400000

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
#define	UHD_GFXOSD_SZ				__MB(124)
#define	UHD_VDEC_4K_2K_HMA_SZ		__MB(376)	/* 4K + 2K */
#define	UHD_VDEC_4K_2K_DPB_SZ		__MB(332)	/* vdec DPB for 4K+2K */
#define	UHD_VDEC_4K_HMA_SZ			__MB(272)	/* 4K single */
#define	UHD_VDEC_4K_DPB_SZ			__MB(228)	/* vdec DPB for 4K single */

#define	UHD_VDEC_4K_2K_HFR_HMA_SZ	__MB(396)	/* 4K + 2K with HFR support */
#define	UHD_VDEC_4K_2K_HFR_DPB_SZ	__MB(352)	/* vdec DPB for 4K+2K with HFR support */
#define	UHD_VDEC_4K_HFR_EXT_HMA_SZ	__MB(124)	/* ext DPB for HFR support */

#define	UHD_VDEC_CPB_SZ				__MB(24)	/* vdec CPB */
#define	UHD_VDEC_MCU_SZ				__MB(19)	/* vdec MCU */

#define	UHD_AUDIO_STD_SZ			__MB(36)	/* 35.6 MB (obsoleted) */
#define	UHD_AUDIO_ADV_SZ			__MB(48)	/* 70.x MB (obsoleted) */

//----------------------------------------------------------------------------------------
//	ETC
//----------------------------------------------------------------------------------------
#ifdef SUPPORT_4_MEDIA_DECODER_TEST
	#undef UHD_GFXOSD_SZ
	#undef UHD_VDEC_CPB_SZ
	#undef UHD_VDEC_4K_2K_HMA_SZ
	#undef UHD_VDEC_4K_2K_HFR_HMA_SZ

	#define	UHD_GFXOSD_SZ				__MB(100)	/*124-24*/
	#define UHD_VDEC_4K_2K_HMA_SZ		__MB(400)	/*376+24*/
	#define UHD_VDEC_4K_2K_HFR_HMA_SZ	__MB(420)	/*396+24*/
	#define	UHD_VDEC_CPB_SZ				__MB(48)	/*24+24*/
#endif

#endif /* __PLATFORM_MEM_MAP_H__ */


