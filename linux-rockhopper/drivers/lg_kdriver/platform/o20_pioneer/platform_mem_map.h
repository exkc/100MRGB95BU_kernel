/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2019 by LG Electronics Inc.
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
 *	refer to below JIRA if you need detail information
 *
 *	O20 r1 : http://clm.lge.com/issue/browse/SICDTV-6499
 *
 *
 *
 */
#ifndef __PLATFORM_MM2_MAP_H__
#define __PLATFORM_MM2_MAP_H__

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#define USE_MTEST_RGN				/* SICDTV-4235 */

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
// - M0: 31 MB sized TZ/SE region
//
// - M1: 64 KB sized demod fw load region
//
#define M0_SYSTEM_RGN_SZ       		__MB(48)
#define M1_SYSTEM_RGN_SZ			DDR_CALIB_RGN_SZ

//----------------------------------------------------------------------------------------
// 4K UHD MEMORY MAP (3.0GB)
//----------------------------------------------------------------------------------------
#define UHD_M0_DEV_RGN_END			0x80000000
#define UHD_M1_DEV_RGN_END			0xc0000000

#define	UHD_M0_3_0_GB_DEV_RGN_BASE	0x33800000
#define	UHD_M0_3_0_GB_DEV_RGN_SZ	(UHD_M0_DEV_RGN_END-UHD_M0_3_0_GB_DEV_RGN_BASE)
#define	UHD_M1_3_0_GB_DEV_RGN_BASE	0xa9800000
#define	UHD_M1_3_0_GB_DEV_RGN_SZ	(UHD_M1_DEV_RGN_END-UHD_M1_3_0_GB_DEV_RGN_BASE)

//----------------------------------------------------------------------------------------
// 8K UHD MEMORY MAP (3.0GB)
//----------------------------------------------------------------------------------------
#define QUHD_M0_DEV_RGN_END			UHD_M0_DEV_RGN_END
#define QUHD_M1_DEV_RGN_END			UHD_M1_DEV_RGN_END

#define	QUHD_M0_3_0_GB_DEV_RGN_BASE	UHD_M0_3_0_GB_DEV_RGN_BASE
#define	QUHD_M0_3_0_GB_DEV_RGN_SZ	(QUHD_M0_DEV_RGN_END-QUHD_M0_3_0_GB_DEV_RGN_BASE)
#define	QUHD_M1_3_0_GB_DEV_RGN_BASE	UHD_M1_3_0_GB_DEV_RGN_BASE
#define	QUHD_M1_3_0_GB_DEV_RGN_SZ	(QUHD_M1_DEV_RGN_END-QUHD_M1_3_0_GB_DEV_RGN_BASE)

//----------------------------------------------------------------------------------------
//	MODULE SIZE
//----------------------------------------------------------------------------------------
#define	GFXOSD_MEM_SZ				__MB(124)
#define	STATIC_BSP_MEM_SZ			__MB(130)	/* TE + (demod) + audio + rsvd */

#define	UHD_VDEC_DPB_SZ				__MB(320)	/* secure DPB 288MB + secure CPB 24MB. refer to SICDTV-7374 */
#define	UHD_VDEC_CPB_SZ				__MB(12)	/* non-secure 12 MB x 2 = 24 MB */
#define	UHD_VDEC_PHOTO_SZ			__MB(192)	/* non-secure framebuffer for 8K photo. refer to SICDTV-7374 */
#define	UHD_VDEC_MCU_SZ				__MB(28)
#define	VENC_SZ					__MB(6)

#define	AUDIO_BUFFER_SZ				__MB(40)	/* audio buffer memory */

#define LNE_BUFFER_SZ				__MB(2)		/* lne buffer memory */

//----------------------------------------------------------------------------------------
//	ETC
//----------------------------------------------------------------------------------------

#endif /* __PLATFORM_MM2_MAP_H__ */


