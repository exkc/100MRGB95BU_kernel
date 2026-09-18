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
//#define M0_ONLY_AUDIO_MAP

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
#define __MB(v)                     ((v)<<20)
#define __KB(v)                     ((v)<<10)

//----------------------------------------------------------------------------------------
// CAT0 for AUDIO soundbar
//
//----------------------------------------------------------------------------------------
#define CAT0_RGN_BWB0_BASE          0x2b800000
#define CAT0_RGN_BWB1_BASE          0x2b800000
#define CAT0_RGN_M0_BASE            0x2b800000
#define CAT0_RGN_SYS_BASE           0xBC400000

#define CAT0_RGN_BWB0_SZ            __MB(0)
#define CAT0_RGN_BWB1_SZ            __MB(0)
#define CAT0_RGN_M0_S_SZ            __MB(152)
#define CAT0_RGN_M0_NS_SZ           __MB(116)
#define CAT0_RGN_SYS_SZ             __MB(60)

//----------------------------------------------------------------------------------------
//  MODULE size definition
//----------------------------------------------------------------------------------------
//
// module size for CAT0 group & common size
//
#define MOD_SURFACE_SZ              __MB(0)     // 80MB-1MB

#define CAT0_MOD_BWB0_FREE_SZ       __MB(0)     // reserved size of BWB0
#define CAT0_MOD_BWB1_FREE_SZ       __MB(0)     // reserved size of BWB1
#define CAT0_MOD_M0_S_FREE_SZ       __MB(0)     // reserved size of M0 secure mem
#define CAT0_MOD_M0_NS_FREE_SZ      __MB(0)     // reserved size of M0 non-secure mem
#define CAT0_MOD_M0_DEBUG_SZ        __MB(60)    // reserved size of M0 debug

#define CAT0_MOD_VPB4K_SZ           __MB(0)     // 4K VPB, BWB
#define CAT0_MOD_VPB8K_SZ           __MB(0)     // cat0 - 8K VPB, BWB
#define CAT0_MOD_VDEC_CPB_SZ        __MB(0)     // 4K CPB, ICOD, Photo, VENC
#define MOD_VDEC_GEN_SZ             __MB(0)     // VDEC general

#define CAT0_MOD_PQE_BWB_SVP_SZ     __MB(0)
#define CAT0_MOD_PQE_BWB_NSV_SZ     __MB(0)

#define MOD_AUDIO0_SZ               __MB(60)
#define MOD_AUDIO1_SZ               __MB(12)
#define MOD_AUDIO_LNX_SZ            __MB(12)
#define MOD_AUDIO_FW_BIN            __MB(10)
#define MOD_AUDIO_DUMP              __MB(60)    // DSPx's Max Size(DSP0 : 26MB)

#define MOD_LNE_SZ                  __MB(0)     // general mem for AI BSP operation
#define MOD_NPU_AIPQ_SZ             __MB(0)
#define CAT0_MOD_NPU0_SZ            __MB(0)
#define CAT0_MOD_NPU1_SZ            __MB(0)

//----------------------------------------------------------------------------------------
//  ETC
//----------------------------------------------------------------------------------------

#endif                          /* __PLATFORM_O26_PIONEER_MAP_H__ */
