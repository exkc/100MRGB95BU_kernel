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
#define	USE_FIXED_AUDIO_BASE

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define __MB(v)						((v)<<20)
#define __KB(v)						((v)<<10)

/*----------------------------------------------------------------------------------------
	COMMON MEMORY MAP
----------------------------------------------------------------------------------------*/

//----------------------------------------------------------------------------------------
// 4K UHD MEMORY MAP (2.5GB)
//----------------------------------------------------------------------------------------
#define UHD_M0_2_5_GB_DEV_END		0x91800000
#define UHD_M1_2_5_GB_DEV_END		0x9D400000
#define	UHD_M2_2_5_GB_DEV_END		0xC0000000

#define	UHD_M0_2_5_GB_DEV_BASE		0x56C00000
#define	UHD_M0_2_5_GB_DEV_SZ		(UHD_M0_2_5_GB_DEV_END-UHD_M0_2_5_GB_DEV_BASE)
#define	UHD_M1_2_5_GB_DEV_BASE		0x91800000
#define	UHD_M1_2_5_GB_DEV_SZ		(UHD_M1_2_5_GB_DEV_END-UHD_M1_2_5_GB_DEV_BASE)
#define	UHD_M2_2_5_GB_DEV_BASE		0xBD400000
#define	UHD_M2_2_5_GB_DEV_SZ		(UHD_M2_2_5_GB_DEV_END-UHD_M2_2_5_GB_DEV_BASE)

//----------------------------------------------------------------------------------------
// 8K UHD MEMORY MAP (3.5GB)
//----------------------------------------------------------------------------------------
#define UHD_M0_3_5_GB_DEV_END		0xAA000000
#define UHD_M1_3_5_GB_DEV_END		0xBC400000
#define	UHD_SYS_3_5_GB_DEV_END		0xC0000000

#define	UHD_M0_3_5_GB_DEV_BASE		0x55800000
#define	UHD_M0_3_5_GB_DEV_SZ		(UHD_M0_3_5_GB_DEV_END-UHD_M0_3_5_GB_DEV_BASE)
#define	UHD_M1_3_5_GB_DEV_BASE		0xAA000000
#define	UHD_M1_3_5_GB_DEV_SZ		(UHD_M1_3_5_GB_DEV_END-UHD_M1_3_5_GB_DEV_BASE)

#define	UHD_M2_3_5_GB_DEV_BASE		0xBC400000
#define	UHD_M2_3_5_GB_DEV_SZ		(UHD_SYS_3_5_GB_DEV_END-UHD_M2_3_5_GB_DEV_BASE)

//----------------------------------------------------------------------------------------
// GROUP SIZE
// see http://clm.lge.com/issue/browse/SICDTV-9433  (initial)
// see http://clm.lge.com/issue/browse/SICDTV-10109 (r1.x)
// see http://clm.lge.com/issue/browse/SICDTV-10309 (r2.x)
// see http://clm.lge.com/issue/browse/SICDTV-10435 (r3.2)
// see http://clm.lge.com/issue/browse/SICDTV-13023 (r4.1)
// see http://clm.lge.com/issue/browse/SICDTV-13162 (r5.6)
//----------------------------------------------------------------------------------------
#define	BWB_MEM_GRP_4K_SZ			(UHD_VPB4K_SZ+UHD_VPB8K_4K_SZ) // 280+128
#define	M0_S_MEM_GRP_4K_SZ			__MB( 68)
#define	M0_NS_MEM_GRP_4K_SZ			__MB(424)
#define	M1_S_MEM_GRP_4K_SZ			__MB( 84)
#define	M1_NS_MEM_GRP_4K_SZ			__MB(104)

#define	BWB_MEM_GRP_8K_SZ			(UHD_VPB4K_SZ+UHD_VPB8K_8K_SZ) // 280+780
#define	M0_S_MEM_GRP_8K_SZ			__MB( 52)
#define	M0_NS_MEM_GRP_8K_SZ			__MB(240)
#define	M1_S_MEM_GRP_8K_SZ			__MB( 64)
#define	M1_NS_MEM_GRP_8K_SZ			__MB(228)

//----------------------------------------------------------------------------------------
//	MODULE SIZE
//----------------------------------------------------------------------------------------
#define	GFXOSD_SURFACE_4K_SZ		__MB(79)
#define	GFXOSD_SURFACE_8K_SZ		__MB(128+8)

#define M0_DEBUG_4K_SZ				__MB(70)    // general purpose CMA region (minimal size)
#define M1_DEBUG_4K_SZ				__MB(20)    // general purpose CMA region (minimal size)
#define M0_DEBUG_8K_SZ				__MB(49)    // general purpose CMA region (minimal size)
#define M1_DEBUG_8K_SZ				__MB(20)    // general purpose CMA region (minimal size)

#define	UHD_VPB8K_4K_SZ				__MB(148)	// not for VDEC, only for PQE
#define	UHD_VPB8K_8K_SZ				__MB(760)	// 8K VPB
#define	UHD_VPB4K_SZ				__MB(300)	// 4K VPB, BWB
#define	UHD_VDEC_CPB_SZ				__MB(66)	// 4K CPB, ICOD, Photo, VENC
#define	UHD_VDEC_GEN_SZ				__MB(2)		// VDEC general

#define	VENC_SZ						__MB(10)	/* VENC non Secure */
#define	VENC_S_SZ			    	__MB(12)	/* VENC Secure */
#define	AUDIO_BUFFER_SZ_0			__MB(76)	/* audio mem with lne */
#define LNE_BUFFER_SZ				__MB(2)		/* lne buffer memory */
#define	NPU_BUFFER_SZ				__MB(15)	/* npu(dne) buffer memory */

//----------------------------------------------------------------------------------------
//	ETC
//----------------------------------------------------------------------------------------

#endif /* __PLATFORM_MM2_MAP_H__ */


