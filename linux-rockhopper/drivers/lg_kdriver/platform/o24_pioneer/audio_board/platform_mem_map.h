/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2023 by LG Electronics Inc.
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

#ifndef __O24_PIONEER_PLATFORM_H__
#define __O24_PIONEER_PLATFORM_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/
#define USE_FIXED_AUDIO_BASE

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
#define __MB(v)                     ((v)<<20)
#define __KB(v)                     ((v)<<10)

//----------------------------------------------------------------------------------------
// CAT0 for SLT, bringup for EVAL.BOARD (M0: 1.5GB, M1: 1.0GB, M2: 1.0GB)
//----------------------------------------------------------------------------------------
#define CAT0_RGN_BWB_BASE           0x30C00000
#define CAT0_RGN_M0_BASE            0x6F800000
#define CAT0_RGN_M1_BASE            0xAB400000
#define CAT0_RGN_SYS_BASE           0xBDC00000
#define CAT0_RGN_BWB_SZ             (CAT0_GRP_BWB_MEM_SZ)
#define CAT0_RGN_M0_SZ              (CAT0_GRP_M0_S_MEM_SZ+CAT0_GRP_M0_NS_MEM_SZ)
#define CAT0_RGN_M1_SZ              (CAT0_GRP_M1_S_MEM_SZ+CAT0_GRP_M1_NS_MEM_SZ)
#define CAT0_RGN_SYS_SZ             __MB( 36)

#define CAT0_GRP_BWB_MEM_SZ         (MOD_VPB4K_SZ+MOD_CAT0_VPB8K_SZ+MOD_CAT0_PQE_BWB_SZ)
#define CAT0_GRP_M0_S_MEM_SZ        __MB( 60)
#define CAT0_GRP_M0_NS_MEM_SZ       __MB(384)
#define CAT0_GRP_M1_S_MEM_SZ        __MB( 96)
#define CAT0_GRP_M1_NS_MEM_SZ       __MB(200)

//----------------------------------------------------------------------------------------
// CAT1 for AUDIO BOARD
//
// 1st map: http://clm.lge.com/issue/browse/SICDTV-13164
//          see also http://clm.lge.com/issue/browse/SICDTV-13105
//          see http://clm.lge.com/issue/browse/SICDTV-13799 (2024/04)
//----------------------------------------------------------------------------------------
#define CAT1_RGN_BWB_BASE           0x54C00000
#define CAT1_RGN_M0_BASE            0x70400000
#define CAT1_RGN_M1_BASE            0x8D000000
#define CAT1_RGN_SYS_BASE           0xBD400000
#define CAT1_RGN_BWB_SZ             (CAT1_GRP_BWB_MEM_SZ)
#define CAT1_RGN_M0_SZ              (CAT1_GRP_M0_S_MEM_SZ+CAT1_GRP_M0_NS_MEM_SZ)
#define CAT1_RGN_M1_SZ              (CAT1_GRP_M1_S_MEM_SZ+CAT1_GRP_M1_NS_MEM_SZ)
#define CAT1_RGN_SYS_SZ             __MB( 44)

#define CAT1_GRP_BWB_MEM_SZ         (MOD_VPB4K_SZ+MOD_CAT1_VPB8K_SZ+MOD_CAT1_PQE_BWB_SZ)
#define CAT1_GRP_M0_S_MEM_SZ        __MB(252)
#define CAT1_GRP_M0_NS_MEM_SZ       __MB(208)
#define CAT1_GRP_M1_S_MEM_SZ        __MB(104)
#define CAT1_GRP_M1_NS_MEM_SZ       __MB(156)

//----------------------------------------------------------------------------------------
// add new CATx for new model
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
//  MODULE size definition
//----------------------------------------------------------------------------------------
#define MOD_SURFACE_SZ              __MB(80)

#define MOD_CAT0_FREEMEM0_SZ        __MB(0)
#define MOD_CAT1_FREEMEM0_SZ        (__MB(7)+__KB(512))

#define MOD_CAT0_M0_DEBUG_SZ        __MB(0)     // SLT doesn't need to check minimail size
#define MOD_CAT0_M1_DEBUG_SZ        __MB(0)
#define MOD_CAT1_M0_DEBUG_SZ        __MB(25)    // see http://clm.lge.com/issue/browse/SICDTV-13880
#define MOD_CAT1_M1_DEBUG_SZ        __MB(50)

#define MOD_VPB4K_SZ                __MB(292)   // 4K VPB, BWB
#define MOD_CAT0_VPB8K_SZ           __MB(752)   // cat0 - 8K VPB, BWB
#define MOD_CAT1_VPB8K_SZ           __MB(0)     // cat1 - emtpy
#define MOD_VDEC_CPB_SZ             __MB(62)    // 4K CPB, ICOD, Photo, VENC
#define MOD_VDEC_GEN_SZ             __MB(2)     // VDEC general

#define MOD_CAT0_PQE_BWB_SZ         __MB(0)     // cat0 - empty
#define MOD_CAT1_PQE_BWB_SZ         __MB(148)   // cat1 - PQE BWB

#define MOD_CAT0_AUDIO0_SZ          __MB(0)     // 8K audio legacy model for FPGA, SLT etc
#define MOD_CAT0_AUDIO1_SZ          __MB(68)    // 8K audio legacy model for FPGA, SLT etc
#define MOD_CAT1_AUDIO0_SZ          __MB(64)    // 4K audio mem without lnx (secure)
#define MOD_CAT1_AUDIO1_SZ          __MB(12)    // 4K audio mem without lnx (non-secure)

#define MOD_AUDIO_LNX_SZ            __MB(9)     // dedicated mem for audio lnx

#define MOD_LNE_SZ                  __MB( 2)    // general mem for AI BSP operation
#define MOD_NPU0_SZ                 __MB(32)
#define MOD_NPU1_SZ                 (__MB(32)+__KB(512))

//----------------------------------------------------------------------------------------
//  ETC
//----------------------------------------------------------------------------------------

#endif                          /* __PLATFORM_O24_PIONEER_MAP_H__ */
