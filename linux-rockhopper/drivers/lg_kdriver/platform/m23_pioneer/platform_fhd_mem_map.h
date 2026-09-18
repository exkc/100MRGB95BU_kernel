/*
        SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
        Copyright(c) 2019 by LG Electronics Inc.

        This program is free software; you can redistribute it and/or
        modify it under the terms of the GNU General Public License
        version 2 as published by the Free Software Foundation.

        This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
        GNU General Public License for more details.
*/
#ifndef __PLATFORM_FHD_MEM_MAP_H__
#define __PLATFORM_FHD_MEM_MAP_H__

//----------------------------------------------------------------------------------------
// Control Constants
//----------------------------------------------------------------------------------------
#define INCLUDE_FHD_DUMMY

//----------------------------------------------------------------------------------------
// Macro Definitions
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// COMMON MEMORY MAP
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// FHD MEMORY MAP (1.5GB)
//----------------------------------------------------------------------------------------
// <temporary> not offcial
#define FHD_M0_1_5_GB_DEV_END               0x5e400000
#define FHD_M0_1_5_GB_DEV_BASE              (FHD_1_5_GB_KERNEL_SZ)
#define FHD_M0_1_5_GB_DEV_SZ                (FHD_M0_1_5_GB_DEV_END-FHD_M0_1_5_GB_DEV_BASE)

// official
#define FHD_M0_1_0_GB_DEV_END               0x3e400000
#define FHD_M0_1_0_GB_DEV_BASE              (FHD_1_0_GB_KERNEL_SZ)
#define FHD_M0_1_0_GB_DEV_SZ                (FHD_M0_1_0_GB_DEV_END-FHD_M0_1_0_GB_DEV_BASE)

//----------------------------------------------------------------------------------------
// GROUP SIZE
// see http://clm.lge.com/issue/browse/SICDTV-11799 (FHD map)
//
// (노트)
// 1.5GB 맵은 기존 보드 사용을 위한 테스트용 값임. 1.5GB UHD 맵과 동일한 레이아웃으로 설정됨
//----------------------------------------------------------------------------------------
#define FHD_1_5_GB_KERNEL_SZ                __MB(916)   // (1.5GB) kernel
#define FHD_M0_1_5_GB_S_MEM0_GRP_SZ         __MB(204)   // (1.5GB) dynamic secure/non-secure mem
#define FHD_M0_1_5_GB_S_MEM1_GRP_SZ         __MB(88)    // (1.5GB) static secure mem
#define FHD_M0_1_5_GB_NS_MEM_GRP_SZ         __MB(276)   // (1.5GB) non-secure mem

#define FHD_1_0_GB_KERNEL_SZ                __MB(720)   // (1.0GB) kernel
#define FHD_M0_1_0_GB_S_MEM0_GRP_SZ         __MB(60)    // (1.0GB)
#define FHD_M0_1_0_GB_S_MEM1_GRP_SZ         __MB(38+2)  // (1.0GB)
#define FHD_M0_1_0_GB_NS_MEM_GRP_SZ         __MB(176)   // (1.0GB)

//----------------------------------------------------------------------------------------
//      MODULE SIZE
//----------------------------------------------------------------------------------------
#define FHD_SURFACE_SZ                      __MB(45)    // surface 45MB
#define FHD_VPB4K_SZ                        __MB(60)    // VPB 60+2MB

#endif /* __PLATFORM_FHD_MMAP_MAP_H__ */
