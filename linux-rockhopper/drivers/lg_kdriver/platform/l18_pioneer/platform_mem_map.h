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
#ifndef	__PLATFORM_MEM_MAP_H__
#define __PLATFORM_MEM_MAP_H__

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define __MB(v)						((v)<<20)
#define __KB(v)						((v)<<10)

/*----------------------------------------------------------------------------------------
	COMMON MEMORY MAP
----------------------------------------------------------------------------------------*/
#define DDR_CALIB_RGN_SZ    		__KB(0)
#define DDR_RSVD_RGN_SZ			 	(__MB(3)+SYS_MEM_SZ)

//----------------------------------------------------------------------------------------
//	256MB DDR
//----------------------------------------------------------------------------------------
#define	M0_256M_DEV_RGN_BASE		0x05c00000
#define	M0_256M_DEV_RGN_SZ			(M0_256M_DEV_RGN_END-M0_256M_DEV_RGN_BASE)
#define M0_256M_DEV_RGN_END			(0x10000000-DDR_RSVD_RGN_SZ)

//----------------------------------------------------------------------------------------
//	512MB DDR
//----------------------------------------------------------------------------------------
#define	M0_512M_DEV_RGN_BASE		0x05c00000
#define	M0_512M_DEV_RGN_SZ			(M0_DEV_512M_RGN_END-M0_512M_DEV_RGN_BASE)
#define M0_512M_DEV_RGN_END			(0x20000000-DDR_RSVD_RGN_SZ)

//----------------------------------------------------------------------------------------
// SYSTEM RGN
//----------------------------------------------------------------------------------------
#define M0_STATIC_DEV_RGN_BASE		(0x80000000-DDR_RSVD_RGN_SZ)
#define M0_STATIC_DEV_RGN_SZ   		DDR_RSVD_RGN_SZ

//----------------------------------------------------------------------------------------
//	MODULE SIZE
//----------------------------------------------------------------------------------------
#define	GFXOSD_MEM_SZ				(__MB(31) + __KB(256))
#define VDEC0_MEM_SZ				__MB(54)
#define SYS_MEM_SZ					__KB(512)

//----------------------------------------------------------------------------------------
//	ETC
//----------------------------------------------------------------------------------------

#endif /* __PLATFORM_MEM_MAP_H__ */


