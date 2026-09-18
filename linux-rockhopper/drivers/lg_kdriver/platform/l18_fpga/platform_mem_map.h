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
// real DDR calibration size is 32 bye, but I will reserve 16 KB for address alignment.
//
#define DDR_CALIB_RGN_SZ    		__KB(16)

// set the memory size for the static address-assigned deivces.
// this region is composed of:
//
#define M0_SYSTEM_RGN_SZ       		__MB(0)

#define M0_256M_DEV_RGN_END			0x10000000
//#define M0_256M_DEV_RGN_END			0x08000000
#define M0_512M_DEV_RGN_END			0x20000000

//----------------------------------------------------------------------------------------
//	256MB BSP
//----------------------------------------------------------------------------------------
#define	M0_256M_DEV_RGN_BASE		0x06000000	
#define	M0_256M_DEV_RGN_SZ			(M0_256M_DEV_RGN_END-M0_256M_DEV_RGN_BASE)

//----------------------------------------------------------------------------------------
//	512MB BSP
//----------------------------------------------------------------------------------------
#define	M0_512M_DEV_RGN_BASE		0x02000000
#define	M0_512M_DEV_RGN_SZ			(M0_DEV_512M_RGN_END-M0_512M_DEV_RGN_BASE)

//----------------------------------------------------------------------------------------
//	MODULE SIZE
//----------------------------------------------------------------------------------------
#define	GFXOSD_MEM_SZ				__MB(24)
#define VDEC0_MEM_SZ				__MB(64)
#define SYS_MEM_SZ					__MB(0)

//----------------------------------------------------------------------------------------
//	ETC
//----------------------------------------------------------------------------------------

#endif /* __PLATFORM_MEM_MAP_H__ */


