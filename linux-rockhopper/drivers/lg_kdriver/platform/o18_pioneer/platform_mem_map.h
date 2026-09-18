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
#ifndef __PLATFORM_MM2_MAP_H__
#define __PLATFORM_MM2_MAP_H__

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#undef	USE_MEMORY_STUFF0			/* SICDTV-4143 */
#define USE_MTEST_RGN				/* SICDTV-4235 */

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define __MB(v)						((v)<<20)
#define __KB(v)						((v)<<10)

/*----------------------------------------------------------------------------------------
	COMMON MM2ORY MAP
----------------------------------------------------------------------------------------*/
// real DDR calibration size is 32 bye, but I will reserve 16 KB for address alignment.
//
#define DDR_CALIB_RGN_SZ    		__KB(16)

// set the memory size for the static address-assigned deivces.
// this region is composed of:
//
// - M0:  1 MB sized general purpose region
// - M0: 23 MB sized TZ/SE region
//
// - M1: 64 KB sized demod fw load region
//
#define M0_SYSTEM_RGN_SZ       		__MB(24)
#define M1_SYSTEM_RGN_SZ			DDR_CALIB_RGN_SZ
#define M2_SYSTEM_RGN_SZ			DDR_CALIB_RGN_SZ

//----------------------------------------------------------------------------------------
// 4K UHD MM2ORY MAP (3.0GB)
//----------------------------------------------------------------------------------------
#define UHD_M0_DEV_RGN_END			0x80000000
#define UHD_M1_DEV_RGN_END			0xAAC00000
#define UHD_M2_DEV_RGN_END			0xC0000000

#define	UHD_M0_3_0_GB_DEV_RGN_BASE	0x4F400000
#define	UHD_M0_3_0_GB_DEV_RGN_SZ	(UHD_M0_DEV_RGN_END-UHD_M0_3_0_GB_DEV_RGN_BASE)
#define	UHD_M1_3_0_GB_DEV_RGN_BASE	0x96800000
#define	UHD_M1_3_0_GB_DEV_RGN_SZ	(UHD_M1_DEV_RGN_END-UHD_M1_3_0_GB_DEV_RGN_BASE)
#define	UHD_M2_3_0_GB_DEV_RGN_BASE	0xAAC00000
#define	UHD_M2_3_0_GB_DEV_RGN_SZ	(UHD_M2_DEV_RGN_END-UHD_M2_3_0_GB_DEV_RGN_BASE)

//----------------------------------------------------------------------------------------
// 8K UHD MM2ORY MAP (3.0GB)
//----------------------------------------------------------------------------------------
#define QUHD_M0_DEV_RGN_END			0x80000000
#define QUHD_M1_DEV_RGN_END			0xACC00000	// fix
#define QUHD_M2_DEV_RGN_END			0xC0000000

#define	QUHD_M0_3_0_GB_DEV_RGN_BASE	0x3A400000
#define	QUHD_M0_3_0_GB_DEV_RGN_SZ	(QUHD_M0_DEV_RGN_END-QUHD_M0_3_0_GB_DEV_RGN_BASE)
#define	QUHD_M1_3_0_GB_DEV_RGN_BASE	0x99800000
#define	QUHD_M1_3_0_GB_DEV_RGN_SZ	(QUHD_M1_DEV_RGN_END-QUHD_M1_3_0_GB_DEV_RGN_BASE)
#define	QUHD_M2_3_0_GB_DEV_RGN_BASE	0xACC00000
#define	QUHD_M2_3_0_GB_DEV_RGN_SZ	(QUHD_M2_DEV_RGN_END-QUHD_M2_3_0_GB_DEV_RGN_BASE)

//----------------------------------------------------------------------------------------
//	MODULE SIZE
//----------------------------------------------------------------------------------------
#define	GFXOSD_MEM_SZ				__MB(124)
#define	AUDIO_MEM_SZ				__MB(48)

#define	UHD_VDEC0_DPB_SZ			__MB(360)
#define	UHD_VDEC0_DPB8K_SZ			__MB(0)
#define	UHD_VDEC0_CPB_SZ			__MB(24)
#define	UHD_VDEC0_MCU_SZ			__MB(20)

#define	QUHD_VDEC0_DPB_SZ			__MB(340)
#define	QUHD_VDEC0_DPB8K_SZ			__MB(384)
#define	QUHD_VDEC0_CPB_SZ			__MB(24)
#define	QUHD_VDEC0_MCU_SZ			__MB(20)

//----------------------------------------------------------------------------------------
//	ETC
//----------------------------------------------------------------------------------------

#endif /* __PLATFORM_MM2_MAP_H__ */


