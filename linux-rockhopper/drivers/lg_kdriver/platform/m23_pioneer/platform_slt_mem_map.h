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
#ifndef __PLATFORM_SLT_MEM_MAP_H__
#define __PLATFORM_SLT_MEM_MAP_H__

// SLT 메모리맵에 맞게 수정되는 부분만 표기함
// 하지만 SLT 맵 레이아웃의 경우, 어느순간 양산맵과 달라질 수 있으므로 가급적 변수 값을
// 공유하지 않도록 한다. 특히 BSP 메모리 영역의 시작/끝 및 각 메모리 속성 영역의 경우는
// 무조건 분기 처리한다.

//----------------------------------------------------------------------------------------
// Control Constants
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Macro Definitions
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// COMMON MEMORY MAP
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// 4K UHD MEMORY MAP (1.5GB)
//----------------------------------------------------------------------------------------

#define SLT_M0_1_5_GB_DEV_END       0x5e400000
#define SLT_M0_1_5_GB_DEV_BASE      (SLT_KERNEL_SZ)
#define SLT_M0_1_5_GB_DEV_SZ        (SLT_M0_1_5_GB_DEV_END-SLT_M0_1_5_GB_DEV_BASE)

#define SLT_EXT_DEV_END             0xc0000000
#define SLT_EXT_DEV_BASE            0xbe400000
#define SLT_EXT_DEV_SZ              (SLT_EXT_DEV_END-SLT_EXT_DEV_BASE)

//----------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------
// SLT 맵 특징
//
// vdec vpb, lne 크기 변경에 따라 kernel size 는 감소, S mem 증가, NS mem 증가
// 실제 증가량은 128+35 MB 이지만, audio, TE 의 align 제약 사항 고려하여 120+32 MB 증액한다.
// RSVD 메모리에서 어느정도 커버된다.
//
#define SLT_KERNEL_SZ               __MB(764)       // 916-128-24
#define SLT_M0_S_MEM0_GRP_SZ        __MB(204+128)   // dynamic secure/non-secure mem
#define SLT_M0_S_MEM1_GRP_SZ        __MB(88)        // static secure mem
#define SLT_M0_NS_MEM_GRP_SZ        __MB(276+24)    // non-secure mem
#define SLT_M0_RSVD_MEM_GRP_SZ      __MB(24)        // rsvd (dbeug)

//----------------------------------------------------------------------------------------
//      MODULE SIZE
//----------------------------------------------------------------------------------------
// SLT 맵 특징
//
// HDMI 와 VDEC 디코딩이 동시에 처리될 수 있도록 vdec vpb 메모리맵을 +128 MB 증액한다.
// 실제는 64MB 만 증액해도 되지만, 추가 변경 사항에 대비하여 좀 더 증액한다.
//
// SURFACE 는 변경이 없으나, 나중에 필요시 메모리 크기를 변경 가능할 수 있도록 준비한다.
//
// LNE 는 IP 검증 목적으로 SLT 에서 35MB 할당이 필요하다
//
// TE, AUDIO 의 align 조건 만족을 위하여 VDEC MPB 를 +3MB 증액 조치한다.
//
// see http://clm.lge.com/issue/browse/SICDTV-11571
//
#define SLT_GFXOSD_SURFACE_SZ       __MB(78)
#define SLT_UHD_VPB4K_SZ            __MB(204+128)  // VPB(204MB) + HDMI(64) + alpha
#define SLT_LNE_BUFFER_SZ           __MB(35)

//----------------------------------------------------------------------------------------
//      ETC
//----------------------------------------------------------------------------------------

#endif /* __PLATFORM_MMAP_MAP_H__ */
