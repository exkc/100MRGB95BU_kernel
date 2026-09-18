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
#ifndef __PLATFORM_MEM_MAP_H__
#define __PLATFORM_MEM_MAP_H__

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

// set the memory size for the static address-assigned deivces.
// this region is composed of:
//
// - M0:  1 MB sized general purpose region
// - M0: 47 MB sized TZ/SE region
//
#define R0_SYSTEM_RGN_SZ       		__MB(0)

//----------------------------------------------------------------------------------------
// 4K UHD MEMORY MAP (3.0GB)
//----------------------------------------------------------------------------------------
#define	DDR_RGN0_BASE			0x10000000UL
#define	DDR_RGN0_SZ				(__MB(64)*2)
#define DDR_RGN0_END			(DDR_RGN0_BASE+DDR_RGN0_SZ)

#define	DDR_RGN1_BASE			0x18000000UL
#define	DDR_RGN1_SZ				(__MB(64)*20)
#define DDR_RGN1_END			(DDR_RGN1_BASE+DDR_RGN1_SZ)

#define	DDR_RGN2_BASE			0x68000000UL
#define	DDR_RGN2_SZ				(__MB(64)*2)
#define DDR_RGN2_END			(DDR_RGN2_BASE+DDR_RGN2_SZ)

#define	DDR_RGN3_BASE			0x70000000UL
#define	DDR_RGN3_SZ				(__MB(64)*18)
#define DDR_RGN3_END			(DDR_RGN3_BASE+DDR_RGN3_SZ)

#define	DDR_RGN4_BASE			0xB8000000UL
#define	DDR_RGN4_SZ				(__MB(64)*2)
#define DDR_RGN4_END			(DDR_RGN4_BASE+DDR_RGN4_SZ)

//----------------------------------------------------------------------------------------
//	BLK/MODULE SIZE
//----------------------------------------------------------------------------------------
#define	GFXOSD_MEM_SZ			__MB(120)	/* surface (fixed) */

#define	VDEC_VPB0_SZ			__MB(372)	/* secure CPB*3, 4K+2K secure DPB. see SICDTV-8002 */
#define	VDEC_VPB1_SZ			__MB(824)	/* non-secure/secure DPB. see SICDTV-8002 */
#define	VDEC_CPB_SZ				__MB(12)	/* none-seucre CPB. not used. see SICDTV-8002 */
#define	VDEC_MCU_SZ				__MB(28)	/* vdec MCU + COMMON */
#define	VDEC_PHOTO_SZ			__MB(192)	/* non-secure framebuffer for 8K photo. not used. see SICDTV-8002 */

#define	AUDIO_BUFFER_SZ			(__MB(38) + __KB(512))       /* audio buffer memory */

#define LNE_BUFFER_SZ			__MB(2)         /* lne buffer memory */

//----------------------------------------------------------------------------------------
//	ETC
//----------------------------------------------------------------------------------------

#endif /* __PLATFORM_MEM_MAP_H__ */


