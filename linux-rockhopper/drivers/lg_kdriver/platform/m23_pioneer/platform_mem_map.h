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
#ifndef __PLATFORM_MEM_MAP_H__
#define __PLATFORM_MEM_MAP_H__

//----------------------------------------------------------------------------------------
// Control Constants
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Macro Definitions
//----------------------------------------------------------------------------------------
#define __MB(v)                 ((v)<<20)
#define __KB(v)                 ((v)<<10)

//----------------------------------------------------------------------------------------
// COMMON MEMORY MAP
//----------------------------------------------------------------------------------------
#define R0_SYSTEM_RGN_SZ        __MB(0)

//----------------------------------------------------------------------------------------
// 4K UHD MEMORY MAP (1.5GB)
//----------------------------------------------------------------------------------------
#define M0_1_5_GB_DEV_END       0x5dc00000
#define M0_1_5_GB_DEV_BASE      (KERNEL_SZ)
#define M0_1_5_GB_DEV_SZ        (M0_1_5_GB_DEV_END-M0_1_5_GB_DEV_BASE)

#define EXT_DEV_END             0xc0000000
#define EXT_DEV_BASE            0xbdc00000
#define EXT_DEV_SZ              (EXT_DEV_END-EXT_DEV_BASE)

//----------------------------------------------------------------------------------------
// GROUP SIZE
// see http://clm.lge.com/issue/browse/SICDTV-10771 (bringup)
// see http://clm.lge.com/issue/browse/SICDTV-11284 (production map 1.x)
// see http://clm.lge.com/issue/browse/SICDTV-13372 (production map 3)
//
//----------------------------------------------------------------------------------------
#define KERNEL_SZ               __MB(908)
#define M0_S_MEM0_GRP_SZ        __MB(204)       // dynamic secure/non-secure mem
#define M0_S_MEM1_GRP_SZ        __MB(88)        // static secure mem
#define M0_NS_MEM_GRP_SZ        __MB(276)       // non-secure mem
#define M0_RSVD_MEM_GRP_SZ      __MB(24)        // rsvd (dbeug)
#define M0_SYS_MEM_GRP_SZ       __MB(36)        // static sys region

//----------------------------------------------------------------------------------------
//      MODULE SIZE
//----------------------------------------------------------------------------------------
#define SURFACE_SZ              __MB(78)

#define M0_DEBUG_SZ             __MB(10)        // see http://clm.lge.com/issue/browse/SICDTV-13880

#define UHD_VPB4K_SZ            __MB(204)       // VPB(204MB)
#define VDEC_MPB_SZ             __MB(19)        // sub VPB for multi-instarnce
#define VDEC_GEN_SZ             __MB(2)         // VDEC general
#define VDEC_MCU_SZ             __MB(14)        // VDEC mcu (16-2)

#define AUDIO_BUFFER_SZ         __MB(38)
//#define LNE_BUFFER_SZ           __MB(0)       // LNE 버퍼는 동적으로 설정토록 함

//----------------------------------------------------------------------------------------
//      ETC
//----------------------------------------------------------------------------------------

#endif /* __PLATFORM_MMAP_MAP_H__ */
