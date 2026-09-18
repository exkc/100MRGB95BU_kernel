/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2025 by LG Electronics Inc.
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

#ifndef __O26_PIONEER_PLATFORM_H__
#define __O26_PIONEER_PLATFORM_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
#define __MB(v)                     ((v)<<20)
#define __KB(v)                     ((v)<<10)

#define MEMMAP_CAT0                 0 // SLT Board, SIGNAGE Board (future use)
#define MEMMAP_CAT1                 1 // webOS TV Board
#define MEMMAP_CATX                 2 // AI-POC Board

//----------------------------------------------------------------------------------------
// CAT0 for SLT, bringup for EVAL.BOARD (M0: 2GB, M1:1G)
//
// see the following jira for detail information,
// bringup: http://jira.lge.com/issue/browse/SICDTV-15358
//----------------------------------------------------------------------------------------
#define CAT0_RGN_BWB0_BASE          0x51400000
#define CAT0_RGN_BWB1_BASE          0x89800000
#define CAT0_RGN_M0_BASE            0x9D400000
#define CAT0_RGN_M1_BASE            0xB3400000
#define CAT0_RGN_SYS_BASE           0xBC400000

#define CAT0_RGN_BWB0_SZ            __MB(900)
#define CAT0_RGN_BWB1_SZ            __MB(316)
#define CAT0_RGN_M0_S_SZ            __MB(96)
#define CAT0_RGN_M0_NS_SZ           __MB(256)
#define CAT0_RGN_M1_S_SZ            __MB(4)
#define CAT0_RGN_M1_NS_SZ           __MB(140)
#define CAT0_RGN_SYS_SZ             __MB(60)

//----------------------------------------------------------------------------------------
// CAT1 for webOS TV (M0: 2GB,   M1:1GB)
//                   (M0: 1.5GB, M1:1.5GB)
//
// see the following jira for detail information,
// bringup: http://jira.lge.com/issue/browse/SICDTV-15358
// prod 1: http://jira.lge.com/issue/browse/SICDTV-15916
//----------------------------------------------------------------------------------------
#define CAT1_RGN_BWB0_BASE          0x68800000
#define CAT1_RGN_BWB1_BASE          0x8e000000
#define CAT1_RGN_M0_BASE            0x99c00000
#define CAT1_RGN_M1_BASE            0xB3000000
#define CAT1_RGN_SYS_BASE           0xBC400000

#define CAT1_RGN_BWB0_SZ            __MB(600)
#define CAT1_RGN_BWB1_SZ            __MB(188)
#define CAT1_RGN_M0_S_SZ            __MB(68)
#define CAT1_RGN_M0_NS_SZ           __MB(336)
#define CAT1_RGN_M1_S_SZ            __MB(4)
#define CAT1_RGN_M1_NS_SZ           __MB(144)
#define CAT1_RGN_SYS_SZ             __MB(60)

//----------------------------------------------------------------------------------------
// CAT2 for webOS Signage (M0: 2GB, M1:1GB)
//
// see the following jira for detail information,
// bringup: http://jira.lge.com/issue/browse/SICDTV-15358
//----------------------------------------------------------------------------------------

// <TBD>

//----------------------------------------------------------------------------------------
// CATX for 8GB AI POC (M0: 2GB, M1: 2GB)
//                     (M0: 4GB, M1: 4GB)
//
// see the following jira for detail information,
// http://jira.lge.com/issue/browse/SICDTV-15663
//----------------------------------------------------------------------------------------
#define CATX_RGN_BWB0_BASE          0x3E800000
#define CATX_RGN_BWB1_BASE          0x67800000
#define CATX_RGN_M0_BASE            0x71800000
#define CATX_RGN_M1_BASE            0x9C400000
#define CATX_RGN_SYS_BASE           0xBC400000

#define CATX_RGN_BWB0_SZ            __MB(656)
#define CATX_RGN_BWB1_SZ            __MB(160)
#define CATX_RGN_M0_S_SZ            __MB( 96)
#define CATX_RGN_M0_NS_SZ           __MB(588)
#define CATX_RGN_M1_S_SZ            __MB(  4)
#define CATX_RGN_M1_NS_SZ           __MB(508)
#define CATX_RGN_SYS_SZ             __MB( 60)

//----------------------------------------------------------------------------------------
// add new CATx for new model
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
//  MODULE size definition
//----------------------------------------------------------------------------------------
//
// module size for common
//
#define MOD_SURFACE_SZ              __MB(79)    // 80MB-1MB
#define MOD_VDEC_GEN_SZ             __MB(2)     // VDEC general
#define MOD_AUDIO0_SZ               __MB(64)
#define MOD_AUDIO1_SZ               __MB(12)
#define MOD_AUDIO_LNX_SZ            __MB(9)     // dedicated mem for audio lnx


//
// module size for CAT0 group
//
#define MOD_LNE_SZ                  __MB( 2)    // general mem for AI BSP operation
#define MOD_NPU_AIPQ_SZ             __MB(24)
#define CAT0_MOD_BWB0_FREE_SZ       __MB(244)   // reserved size of BWB0
#define CAT0_MOD_BWB1_FREE_SZ       __MB( 50)   // reserved size of BWB0
#define CAT0_MOD_M0_S_FREE_SZ       __MB(0)     // reserved size of M0 secure mem
#define CAT0_MOD_M1_S_FREE_SZ       __MB(0)     // reserved size of M1 secure mem
#define CAT0_MOD_M0_NS_FREE_SZ      __MB(0)     // reserved size of M0 non-secure mem
#define CAT0_MOD_M1_NS_FREE_SZ      __MB(0)     // reserved size of M1 non-secure mem
#define CAT0_MOD_M0_DEBUG_SZ        __MB(30)    // reserved size of M0 debug
#define CAT0_MOD_M1_DEBUG_SZ        __MB(54)    // reserved size of M1 debug

#define CAT0_MOD_VPB4K_SZ           __MB(292)   // 4K VPB, BWB
#define CAT0_MOD_VPB8K_SZ           __MB(0)     // cat0 - 8K VPB, BWB
#define CAT0_MOD_VDEC_CPB_SZ        __MB(80)    // 4K CPB, ICOD, Photo, VENC

#define CAT0_MOD_PQE_BWB_SVP_SZ     __MB(364)
#define CAT0_MOD_PQE_BWB_NSV_SZ     __MB(160)

#define CAT0_MOD_NPU0_SZ            __MB(32)
#define CAT0_MOD_NPU1_SZ            (__MB(32)+__KB(512))


//
// module size for CAT1 group
//
#define CAT1_MOD_BWB0_FREE_SZ       __MB(0)     // reserved size of BWB0
#define CAT1_MOD_BWB1_FREE_SZ       __MB(4)     // reserved size of BWB0. future use if necessary
#define CAT1_MOD_M0_S_FREE_SZ       __MB(0)     // reserved size of M0 secure mem
#define CAT1_MOD_M1_S_FREE_SZ       __MB(0)     // reserved size of M1 secure mem
#define CAT1_MOD_M0_NS_FREE_SZ      __MB(0)     // reserved size of M0 non-secure mem
#define CAT1_MOD_M1_NS_FREE_SZ      __MB(0)     // reserved size of M1 non-secure mem
#define CAT1_MOD_M0_DEBUG_SZ        __MB(30)    // reserved size of M0 debug
#define CAT1_MOD_M1_DEBUG_SZ        __MB(54)    // reserved size of M1 debug

#define CAT1_MOD_VPB4K_SZ           __MB(292)   // 4K VPB, BWB
#define CAT1_MOD_VPB8K_SZ           __MB(0)     // cat0 - 8K VPB, BWB
#define CAT1_MOD_VDEC_CPB_SZ        __MB(80)    // 4K CPB, ICOD, Photo, VENC

#define CAT1_MOD_PQE_BWB_SVP_SZ     __MB(308)   // see http://jira.lge.com/issue/browse/SICDTV-15916
#define CAT1_MOD_PQE_BWB_NSV_SZ     __MB(160)

#define CAT1_MOD_NPU0_SZ            __MB(32)
#define CAT1_MOD_NPU1_SZ            (__MB(32)+__KB(512))


//
// module size for CATX group
//
#define CATX_MOD_BWB0_FREE_SZ       __MB(0)
#define CATX_MOD_BWB1_FREE_SZ       __MB(0)
#define CATX_MOD_M0_S_FREE_SZ       __MB(0)
#define CATX_MOD_M1_S_FREE_SZ       __MB(0)
#define CATX_MOD_M0_NS_FREE_SZ      __MB(0)
#define CATX_MOD_M1_NS_FREE_SZ      __MB(0)
#define CATX_MOD_M0_DEBUG_SZ        __MB(25)
#define CATX_MOD_M1_DEBUG_SZ        __MB(50)

#define CATX_MOD_VPB4K_SZ           __MB(292)
#define CATX_MOD_VPB8K_SZ           __MB(0)
#define CATX_MOD_VDEC_CPB_SZ        __MB(80)

#define CATX_MOD_PQE_BWB_SVP_SZ     __MB(364)
#define CATX_MOD_PQE_BWB_NSV_SZ     __MB(160)

#define CATX_MOD_NPU0_SZ            __MB(300)
#define CATX_MOD_NPU1_SZ            __MB(400)

//----------------------------------------------------------------------------------------
//  ETC
//----------------------------------------------------------------------------------------

#endif                          /* __PLATFORM_O26_PIONEER_MAP_H__ */
