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

#ifndef _FBDEV_HW_O26_H_
#define _FBDEV_HW_O26_H_

// 추가 작업이 필요한 부분에서 메시지 남겨 놓을것
#define FBDEV_O26_TODO(msg)

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/
// temporary config for O20 kdriver (fake) verification with O20+(LG1313)
#undef FBDEV_O26_FAKE_VERIFICATION

// (2025/02/19) use mixer mute to keep the black screen before the first OSD update
// if defined, boot logo migration is disabled.
//
#define FBDEV_O26_USE_MIXER_MUTE

// set the system default OSD path
// this configuration will be changed if we have S.OSD fixed board.
#define FBDEV_O26_DEFAULT_OSD_PATH  LX_FBDEV_CONN_OSD_VIDEO_BLEND

// support webOS cursor behaviour temporarily (always 3840x2160 region regardless of blend/sep path)
#define FBDEV_O26_WEBOS_CURSOR_WORKAROUND

// support the cursor position outside (0,0)~(1920,1080)
// kdriver will accept the exceptional position such as (-100,-100), (3840,1080) etc.
// raxis.lim (2016/12/20)
// TV doesn't require unlimited cursor position to the right side. DISABLE this feature to prevent cursor image corruption
//
#define FBDEV_O26_USE_UNLIMITED_CURSOR_POSITION

// support CROP based E-Streamer implementation
//
#undef FBDEV_O26_USE_CROP_CTRL

// raxis.lim (2010/10/08)
//
// reduce CCO bandwidth when AFBC OSD is set to OFF.
// refer to http://clm.lge.com/issue/browse/AVTASK-401?focusedCommentId=2022898&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-2022898
//
// setup afbc_init_en flag only when fb(0) is enabled(visible)
// - (TOP+0x0038) CTRL_AUTO_INIT_AFBC.reg_afbc0_auto_init_en = 1
// - (TOP+0x0038) CTRL_AUTO_INIT_AFBC.reg_afbc0_init_en = 1
//
// setup afbc_init_en flag only when fb(1) is enabled(visible)
// - (TOP+0x0038) CTRL_AUTO_INIT_AFBC.reg_afbc1_auto_init_en = 1
// - (TOP+0x0038) CTRL_AUTO_INIT_AFBC.reg_afbc1_init_en = 1
//
#define FBDEV_O26_USE_AFBC_READ_BW_SAVING

#if !defined BUILD_FEATURE_fpga
// CTOP 코드가 준비된 이후에만 아래 코드를 ON 함.
#define FBDEV_O26_USE_CTOP_REGS
#endif

// raxis.lim (2019/05/22)
// O20 supports 4K OSD through 2 AFBC reader
#define FBDEV_O26_SUPPORT_4KOSD

// support external render IPC
#define FBDEV_O26_USE_EXT_RENDERER_IPC

// O26 에서는 ARGB raw 모드를 지원하지 않는다.
// 따라서 일부 코드의 경우 항상 AFBC 를 가정하고 작성할 수 있다.

// O26 에서 최대 4개의 AFBC/AFRC 디코더를 사용할 수 있다.
#define MAX_FBC  4

// GLB 대상 OSD 갯수도 4 이다.
// see OSD_IN_OSC2 ~ OSD_ID_OSD2
#define GLB_LAYER_MAX 4

// OSD on/off 시에 GLB 의 layer on/off 제어 코드까지 하도록 한다.
#undef USE_GLB_PATH_CTRL

// MAX_BOSD, MAX_SOSD 는 코드에서 중요한 의미로 쓰이지는 않음.
#define MAX_BOSD 2
#define MAX_SOSD 0

// 실제 OSD 가 8 개는 아님. osdx_common_disp_size[8] 초기화를 위한 설정임
// OSD_POST 에서 실제로는 UI(0) 과 커서(4) 만 의미있음
#define MAX_PLT_OSD_NUM  8

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include <asm/atomic.h>

#include "PQE_GSC_GLB_reg.h"
#include "PQE_GSC_OSD_PRE_reg.h"
#include "PQE_TopCTRL_CCO_CTRL1_reg.h"
#include "PQE_TopCTRL_CCO_CTRL_reg.h"
#include "PQE_TopCTRL_GSC_CTRL_reg.h"

#include "PQE_OSD_AFBC_reg.h"
#include "PQE_OSD_AFRC_reg.h"
#include "PQE_OSD_reg.h"

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/
#define CCO_CTRL_REG_BASE       (0xCC880000)
#define CCO_CTRL1_REG_BASE      (0xCC880E00)
#define GSC_CTRL_REG_BASE       (0xCCC70000)

#define OSD_REG_BASE            (0xCC880100)
#define OSD_PRE_REG_BASE        (0xCCC71E00)
#define GLB_REG_BASE            (0xCCC72400)

#define AFBC_REG_BASE(i)        (0xCCC72600+(i)*0x200)
#define AFRC_REG_BASE(i)        (0xCCC72e00+(i)*0x200)

// Actually O20 supports only one graphic plane & one cursor plane
// But the below MAX_OSD_NUM is used to share kdriver design with H15
//
// OSD0 offset : 0x200 --> osdx_ctrl[0]
// CRSR offset : 0x400 --> osdx_ctrl[4]
//
#define FBDEV_O26_MAX_OSD_BLK_NUM       4

// maximum hardware OSD layer number connected to single FB device.
//
#define FBDEV_O26_MAX_XLST              2

// GMAU_WORD means that minimum bytes for gMAU to process the framebuffer simultaneouly
// this value has been 16 byte (ARGB 4 pixel) since H13.
// it means that OSD frame buffer should be multiple of OSD_WORD
// what will happen if we violates this limitation ?
// don't worry. HW never die.
// current OSD HW fix SW bug by removing low 3bits.
// but this might result in the invalid screen output.
#define FBDEV_O26_GMAU_WORD_BYTES       16

// minimum showing region of cursor
// if cursor is located at the right cornet, mininum threshold value should be guraunteed.
// HW engineer (woonghyeon@kim) reported the recommended threshold pixel value is 16 (64byte)
// becuase HW reads 64 bytes simultaneously.
// According to the test, threshold 14 also works well => I will use 16 rather than 14.
//
// in O20+, I should also consider minimum viewing height.
// According to the board test, minimum value seems to 32.
//
// Remember that the below value is dependent on OSD output dimension.
// For example, O20+ doesn't need any external FRC, so output dimension alwyas is set to 3840x2160
//
#define FBDEV_O26_CSR_MIN_WIDTH             16
#define FBDEV_O26_CSR_MIN_HEIGHT            2 //32

// maximum retry for osd0 sync recovery
#define FBDEV_O26_SICDTV_4209_RETRY_MAX     10

// configure default POSD size
#define FBDEV_O26_POSD0_WIDTH               0       /* auto */
#define FBDEV_O26_POSD0_HEIGHT              0       /* auto */
#define FBDEV_O26_POSD1_WIDTH               512     /* 512 by default */
#define FBDEV_O26_POSD1_HEIGHT              2160    /* 2160 by default */

// support fb(1) single buffer EGL when externel render (F20) exits.
// default value = 1
// refer to http://clm.lge.com/issue/browse/SICDTV-7520
#define FBDEV_O26_EXT_RENDER_EGL_FBDEV_NUM  1

#define FIXME(msg)                          1
#define FIXME_NOTE(msg)

#define FBDEV_O26_FBC_DEBUG                 FBDEV_HW0_DEBUG /* b12 */

#define FBDEV_O26_OSD_WORDS_2_BYTES(v)      ((v)<<3)        /* OSD_WORD(8byte) -> byte */
#define FBDEV_O26_BYTES_2_OSD_WORDS(v)      ((v)>>3)        /* byte -> OSD_WORD(8byte) */

#define FBDEV_O26_BYTES_2_PIXEL(v)          ((v)>>2)        /* byte -> ARGB pxl */
#define FBDEV_O26_PIXEL_2_BYTES(v)          ((v)<<2)        /* ARGB pxl -> byte */

#define FBDEV_O26_BITS_2_BYTES(v)           ((v)>>3)        /* bits -> bytes */

#define FBDEV_O26_GMAU_ALIGNED_BYTES(v)     ALIGN(v,16)     /* get 16byte algiend value */

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
#define FBDEV_PLT_GET_HW_CTX()                  (FBDEV_O26_HW_CTX_T*)g_fbdev_hw_ctx.chip_priv_ctx
#define FBDEV_PLT_GET_FBC_CTRL(hw_ctx,fb_id)    &(hw_ctx->fbc_ctrl[fb_id])
#define FBDEV_PLT_GET_MIRROR_CTRL(hw_ctx)       &(hw_ctx->mirror_ctrl)
#define FBDEV_PLT_GET_CONN_CTRL(hw_ctx,fb_id)   &(hw_ctx->conn_ctrl[fb_id])
#define FBDEV_PLT_GET_GLB_CTRL(hw_ctx)          &(hw_ctx->glb_ctrl)
#define FBDEV_PLT_GET_EXT_RENDER_CTRL(hw_ctx)   &(hw_ctx->ext_render_ctrl)

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

// O26 에서 OSD 로 판단할 수 있는 레이어는 총 5개이다. 커서 제외 4개임.
// OSC 2/3 은 PQE 와 공유할 수 있으나, 실제로 공유하는 상황은 없을 것으로 판단한다.
// 실제 OSD 는 OSD_IN_OSD0 와 OSD_IN_OSD1 총 2개이다.
// HW 구조에 의하여 OSD0/1 과 커서는 서로 상이한 제어를 해야 한다.
// 아래 매핑된 숫자는 실제 GLB 의 input port no 와 일치하며, 연결된 AFBC/AFRC decoder no 이기도 하다.
// 현재 구현은 input 을 그대로 output 으로 내보내므로, input no 와 output no 이 일치한다.
// 단 추후 이 부분은 동적 변수로 수정되어져야 한다.
enum
{
    OSD_IN_OSC2 = 0, // GLB input 0, alias OSD_ID_OSD2
    OSD_IN_OSC3 = 1, // GLB input 1, alias OSD_ID_OSD3
    OSD_IN_OSD0 = 2, // GLB input 2
    OSD_IN_OSD1 = 3, // GLB input 3

    OSD_IN_CSR0 = 4, // OSD POST cursor
    OSD_ID_MAX,

    OSD_ID_OSD2 = OSD_IN_OSC2,
    OSD_ID_OSD3 = OSD_IN_OSC3,
};

typedef enum
{
    BOOT_LOGO_MODE_IMAGE_KEEP = 0,
    BOOT_LOGO_MODE_IMAGE_CLEAR,
    BOOT_LOGO_MODE_IMAGE_NONE,
}
FBDEV_PLT_BOOT_LOGO_MODE_T;

/** O20 OSD header structure
 *
 *
 */
typedef struct
{
    UINT32                                  // OSD[0:3]_HDR0
    osd_hdr_ypos                    : 12,   //  0:11
                                    : 4,    // 12:15 reserved
                                    osd_hdr_xpos                  : 12,   // 16:27
                                    : 3,    // 28:30 reserved
                                    osd_hdr_color_key_en          : 1;    //    31

    UINT32                                  // OSD[0:3]_HDR1
    osd_hdr_h_mem                   : 12,   //  0:11
                                    : 4,    // 12:15 reserved
                                    osd_hdr_w_mem                 : 12;   // 16:27

    UINT32                                  // OSD[0:3]_HDR2
    osd_hdr_h_out                   : 12,   //  0:11
                                    : 4,    // 12:15 reserved
                                    osd_hdr_w_out                 : 12,   // 16:27
                                    : 3,    // 28:30 reserved
                                    osd_hdr_pixel_order           : 1;    //    31

    UINT32                                  // OSD[0:3]_HDR3
    osd_hdr_wpl                    : 16,    //  0:15
                                   osd_hdr_global_alpha           : 8,     // 16:23
                                   osd_hdr_format                 : 4,     // 24:27
                                   osd_hdr_depth                  : 3,     // 28:30
                                   osd_hdr_global_alpha_en        : 1;     //    31

    UINT32                                  // OSD[0:3]_HDR4
    osd_hdr_color_key              ;        // 31: 0

    UINT32                                  // OSD[0:3]_HDR5
    osd_hdr_ptr_plte               ;        // 31: 0

    UINT32                                  // OSD[0:3]_HDR6
    osd_hdr_ptr_bmp                ;        // 31: 0
}
FBDEV_PLT_OSD_HDR_T;

typedef struct
{
    UINT8                          bits_per_pixel;
    UINT32                         img_stride;     /* real framebfufer size */
    UINT32                         img_height;     /* real framebuffer size */
}
FBDEV_PLT_OSD_EXHDR_T;

typedef enum
{
    OSDX_DESC_FLAG_CTRL_MAIN = 0x0001,

    OSDX_DESC_FLAG_SWAP = 0x0002,
    OSDX_DESC_FLAG_PDEC = 0x0004,

    // base_addr 는 미사용 레지스터이므로 OSD 초기화 싯점에 1회만 surface 풀의 base 로
    // 초기화 진행함. OSD mem_prot 에러 방지용
    OSDX_DESC_FLAG_ADDR = 0x0008,

    // osd_hdr_2 (PRE) 는 OSD 독자적으로 자유롭게 쓸 수 있다.
    //
    // osd_hdr_5 는 미사용 레지스터이므로 OSD 초기화 싯점에 1회만 surface 풀의 base 로
    // 초기화 진행함. OSD mem_prot 에러 방지용
    OSDX_DESC_FLAG_HDR_ALL = 0x0010,
    OSDX_DESC_FLAG_HDR_2 = 0x0020,
    OSDX_DESC_FLAG_HDR_5 = 0x0040,

    OSDX_DESC_FLAG_SYNC_0 = 0x0100,
    OSDX_DESC_FLAG_SYNC_1 = 0x0200,
    OSDX_DESC_FLAG_SCALER = 0x0400,

    OSDX_DESC_FLAG_ALL = 0xFFFF,
}
OSDX_DESC_FLAG;

// OSD0,1, CSR0 의 레지스터 위치 및 내부 필드가 미묘하게 틀리다.
// 규칙이 없어 기존처럼 배열처럼 접급할수 없다.
// FBDEV_O26_CMN_ReadOSDXDesc, FBDEV_O26_CMN_WriteOSDXDesc 함수를 구현한다.
// 좀 불편하긴 하지만, 코드가 너저분해지는 것은 막을 수 있다.
//
// (note) osd_ctrl_sync0 은 OSD_POST 에 있다. 따라서 커서를 제외한 OSD 입력에 대해서는
// 같은 osd0_ctrl_sync0 을 읽고 쓰게 된다.
//
typedef struct
{
    OSD_PRE_OSD0_CTRL_MAIN osd_ctrl_main;
    OSD_PRE_OSD0_BASE_ADDR osd_base_addr;
    OSD_PRE_OSD0_CTRL_SWAP osd_ctrl_swap;
    OSD_PRE_OSD0_CTRL_PDEC osd_ctrl_pdec;
    OSD_PRE_OSD0_CTRL_HDR0 osd_ctrl_hdr0;
    OSD_PRE_OSD0_CTRL_HDR1 osd_ctrl_hdr1;
    OSD_PRE_OSD0_CTRL_HDR2 osd_ctrl_hdr2;
    OSD_PRE_OSD0_CTRL_HDR3 osd_ctrl_hdr3;
    OSD_PRE_OSD0_CTRL_HDR4 osd_ctrl_hdr4;
    OSD_PRE_OSD0_CTRL_HDR5 osd_ctrl_hdr5;
    OSD_PRE_OSD0_CTRL_HDR6 osd_ctrl_hdr6;

    OSD0_CTRL_SYNC0        osd_ctrl_sync0;
    OSD0_CTRL_SYNC1        osd_ctrl_sync1;
    union
    {
        OSD0_CTRL_SCALER   osd_ctrl_scaler;
        OSD4_CTRL_SCALER   csr_ctrl_scaler;
    };
}
OSDX_DESC_T;

typedef struct
{
#define FBDEV_O26_FBC_STATUS_NONE           0x0000  /* non FBC state */
#define FBDEV_O26_FBC_STATUS_HDR_SETUP      0x0001  /* FBC state, FBC header is setup & written to register */
#define FBDEV_O26_FBC_STATUS_PATH_CHANGE    0x0002  /* FBC related path should be set in ISR handler */
    UINT32                          status;

    LX_FBDEV_FBC_FORMAT_T           fbc_fmt;
}
FBDEV_PLT_FBC_CTRL_T;

typedef struct
{
#define FBDEV_O26_MIRROR_NONE       0x0000
#define FBDEV_O26_V_MIRROR_ON       0x0001
    UINT32                          status;
}
FBDEV_PLT_MIRROR_CTRL_T;

typedef struct
{
#define FBDEV_OSD_EXT_RENDER_FBMEM_NUM      2
#define FBDEV_OSD_EXT_RENDER_REG_BASE       0x0 // FIXME: not defined yet
#define FBDEV_O26_EXT_RENDER_BYTE_PER_PIXEL 4

    UINT32                          fbmem_phys[FBDEV_OSD_EXT_RENDER_FBMEM_NUM];
    int                             fbmem_buf_idx;

    struct
    {
        UINT32                      phys_y;     // not used
        UINT32                      size;       // not used
        union
        {
            struct
            {
                UINT32              xoffset: 16, //  0:15
                                    enable: 1,  // 16:16
                                    yoffset: 15; // 17:31
            };
            UINT32                  command;    // 0xCC482230
        };

        UINT32                      tx_count;   // not used

        union
        {
            struct
            {
                UINT32              crop_x: 16,
                                    crop_y: 16;
            };
            UINT32                  crop_xy;    // 0xcc482234 (+4)
        };

        union
        {
            struct
            {
                UINT32              crop_w: 16,
                                    crop_h: 16;
            };
            UINT32                  crop_wh;    // 0xcc482238 (+8)
        };
    }
    hwparam;

    struct
    {
        UINT64                      interval_tick_us;
        UINT64                      request_tick_us;
    }
    swsync;
}
FBDEV_PLT_EXT_RENDER_CTRL_T;

// GLB 는 원칙적으로 출력 제어를 담당하기 때문에, GLB IN 기반으로 표현하는
// 아래 구조체는 잘못되었다. 추후에 OUT 를 표현할 수 있도록 재구성되어야 한다.
typedef struct
{
    struct
    {
        UINT32  osd_en: 1,
                galpha_en: 1,   // if 1, use global alpha
                zorder: 2,      // valid range 0~3
                : 2,
                galpha: 10;     // 0 ~ 1023
        LX_RECT_T coord;
    }
    mux[GLB_LAYER_MAX];

    UINT16  canvas_w;
    UINT16  canvas_h;
}
FBDEV_PLT_GLB_CTRL_T;

typedef struct
{
    UINT32      ready;              /* if first user frame is requested, ready is set to 1 */

    union
    {
        UINT32  data32;
        struct
        {
            UINT32  osd_init_done: 1,
                    osd_v_mirror: 1,
                    osd_estreamer: 1;
        };
    } status;
}
FBDEV_PLT_USER_INITCALL_CTRL_T;

typedef struct
{
    int (*O26_InitHW)(void);
}
FBDEV_PLT_HW_FUNC_T;


/** OSD specific hardware workaround flag */
enum
{
    //  FBDEV_O26_HW_WA_1X_CSR_DISP_ON_BLEND_PATH   = (1 << 0), /* do not support 2x cursor sacle on blend path */
    //  FBDEV_O26_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR    = (1 << 1), /* OSD0_SYNC async behavior (SICDTV-4209) */
    FBDEV_O26_HW_WA_PQEFW_OSD0_OUT_CTRL         = (1 << 2), /* OSD0 out_win is controlled by PQE (SICDTV-4359) to support OSD orbit */
};

typedef struct
{
    struct
    {
        UINT16                      fb0_width;
        UINT16                      fb0_height;
        UINT16                      fb1_width;
        UINT16                      fb1_height;
        UINT16                      out_width;
        UINT16                      out_height;

        UINT32                      pulse_timer_dly;
    }
    bosd_disp;                                                      /* display size for B.OSD. fixed to 3840x2160 */

    UINT32                          b_keep_hw_conn_type: 1,          /* DO NOT change OSD connection automatically
                                                                     * if the HW conn type is set to B.OSD, it means that HW doesn't have S.OSD path.
                                                                     * so we should now change OSD connection when the initial path is B.OSD.
                                                                     */
                                    b_support_4kosd: 1,             /* support 4K OSD */
                                    b_support_fb1: 1,               /* support another graphic layer */
                                    b_support_ext_frc: 1,           /* support EXT_FRC */
                                    b_support_ext_render,           /* support external render for fb(1) */
                                    rsvd: 27;

    UINT32                          hw_conn_type;                   /* current OSD HW connection */

    UINT16                          hw_disp_width;                  /* current OSD HW disp_width (output)) */
    UINT16                          hw_disp_height;                 /* current OSD HW disp_height output) */
    UINT16                          hw_fb0_width;                   /* maximum active area of OSD HW (input) */
    UINT16                          hw_fb0_height;                  /* maximum active area of OSD HW (input) */
    UINT16                          hw_fb1_width;                   /* maximum active area of OSD HW (input) */
    UINT16                          hw_fb1_height;                  /* maximum active area of OSD HW (input) */

    UINT16                          hw_osd0_owner;                  /* fb0, fb1 shares osd0 */
    UINT16                          hw_ext_render_width;            /* maximum active area of EXT render (output) */
    UINT16                          hw_ext_render_height;           /* maximum active area of EXT render (output) */
    UINT16                          hw_ext_render_swsync_hz;        /* 83333us = 12Hz, 66666us = 15Hz */

    UINT32                          hw_wa_flag;
    UINT32                          intr_req_sav;                   /* N/A */

    FBDEV_PLT_OSD_HDR_T             osd_hdr_sav[LX_FBDEV_ID_MAX];   /* last osd header written */
    LX_FBDEV_CONN_CTRL_T            conn_ctrl[LX_FBDEV_ID_MAX];     /* layer conn ctrl */
    FBDEV_PLT_FBC_CTRL_T            fbc_ctrl[LX_FBDEV_ID_MAX];      /* FBC ctrl */

    FBDEV_PLT_MIRROR_CTRL_T         mirror_ctrl;                    /* OSD mirror control */
    FBDEV_PLT_GLB_CTRL_T            glb_ctrl;                       /* GLB control */
    FBDEV_PLT_USER_INITCALL_CTRL_T  user_initcall_ctrl;             /* OSD initialization by user frame update */

    FBDEV_PLT_EXT_RENDER_CTRL_T     ext_render_ctrl;                /* external OSD render control */

    FBDEV_PLT_HW_FUNC_T             func;
}
FBDEV_O26_HW_CTX_T;

typedef enum
{
    // return 1 if AFBC
    FBDEV_O26_HW_STATUS_AFBC    = 0,

    // return 1 if AFRC
    FBDEV_O26_HW_STATUS_AFRC,

    // return LX_FBDEV_FBC_FORMAT_T
    FBDEV_O26_HW_STATUS_FBC,

    // return 1 if visible
    FBDEV_O26_HW_STATUS_VISIBLE,

    // return v mirror
    FBDEV_O26_HW_STATUS_VMIRROR,
}
FBDEV_O26_HW_STATUS_T;

/*----------------------------------------------------------------------------------------
    Extern Function Prototype Declaration (O26_CMN)
----------------------------------------------------------------------------------------*/
/* return physical OSD block index by fb_dev_id
 *
 */
#define INVALID_XNUM(x)         ((x)<=0||(x)>FBDEV_O26_MAX_XLST)            /* xnum 0, 1 valid */
#define INVALID_XIDX(x)         ((x)<0)
#define VALID_XIDX(x)           ((x)>=0 && (x)<OSD_ID_MAX)
#define INVALID_AFBC_XIDX(x)    ((x)<0 ||(x)>MAX_AFBC)
#define INVALID_AFRC_XIDX(x)    ((x)<0 ||(x)>MAX_AFRC)
#define INVALID_FBC_XIDX(x)     (INVALID_AFBC_XIDX(x) || INVALID_AFRC_XIDX(x))

extern int FBDEV_O26_CMN_GetHWXList(int fb_dev_id, int xlst[2]);
extern int FBDEV_O26_CMN_GetHWXListEx(int fb_dev_id, int xlst[2], int afbc_xlst[2]);

extern void FBDEV_O26_CMN_WriteHdrRegs(int fb_dev_id, FBDEV_PLT_OSD_HDR_T* osd_hdr, FBDEV_PLT_OSD_EXHDR_T* osd_exhdr);
extern void FBDEV_O26_CMN_WriteFRCHeader(void);

extern int FBDEV_O26_CMN_InitHW(void);
extern int FBDEV_O26_CMN_InitOSDLayer(int layer);

extern int FBDEV_O26_CMN_ExecHWCommand(FBDEV_HW_CMD_T cmd, FBDEV_HW_CMD_DATA_T* data);
extern int  FBDEV_O26_CMN_GetHWStatus(FBDEV_O26_HW_STATUS_T status, UINT32 opt);

extern int FBDEV_O26_CMN_SetOSDEnable(int layer, int enable);
extern int FBDEV_O26_CMN_GetOSDEnable(int layer);

extern int FBDEV_O26_CMN_WriteOSDHeader(struct scanvas* pCanvas);

extern int FBDEV_O26_CMN_SetViewCtrl(LX_FBDEV_VIEW_CTRL_T* ctrl);
extern int FBDEV_O26_CMN_SetConnCtrl(LX_FBDEV_CONN_CTRL_T* ctrl);
extern int FBDEV_O26_CMN_MirrorCtrl(bool vmirror_en);

extern int FBDEV_O26_CMN_SetInterruptEnable(INTERRUPT_INFORM_T intr, int enable);
extern int FBDEV_O26_CMN_GetInterruptStatus(INTERRUPT_INFORM_T intr);
extern int FBDEV_O26_CMN_SetInterruptClear(INTERRUPT_INFORM_T intr);

extern void FBDEV_O26_CMN_ISRHook(void);
extern void FBDEV_O26_CMN_HandleReverseOSD(int fb_dev_id, struct scanvas* hCanvas, FBDEV_PLT_OSD_HDR_T* osd_hdr);

extern int  FBDEV_O26_CMN_RunSuspend(void);
extern int  FBDEV_O26_CMN_RunResume(void);

extern void FBDEV_O26_InitOSDZOrder(void);

extern bool FBDEV_O26_CMN_IsUHDDispMode(void);

extern void FBDEV_O26_CMN_RunBootLogoTimer(UINT32 ms, bool bForce);
extern void FBDEV_O26_CMN_MigrateBootLogo(FBDEV_PLT_BOOT_LOGO_MODE_T mode);
extern void FBDEV_O26_CMN_FreeBootLogoFrameBuffer(void);

extern void FBDEV_O26_CMN_SetMixerMute(BOOLEAN en, UINT32 color);

extern void FBDEV_O26_CMN_ReadOSDXDesc(int xidx, OSDX_DESC_T* desc, OSDX_DESC_FLAG flag);
extern void FBDEV_O26_CMN_WriteOSDXDesc(int xidx, OSDX_DESC_T* desc, OSDX_DESC_FLAG flag);

extern void FBDEV_O26_CMN_DiagHW(struct seq_file* m);
extern void FBDEV_O26_CMN_ProcHandler(FBDEV_HW_PROC_ID_T proc_id, struct seq_file* m, void* data);

/*----------------------------------------------------------------------------------------
    Extern Function Prototype Declaration (O20 Platform Function)
----------------------------------------------------------------------------------------*/
extern int FBDEV_O26_InitHW(void);
extern int FBDEV_O26_ShutdownHW(void);
extern int FBDEV_O26_SetOSDEnable(int layer, int enable);
extern int FBDEV_O26_GetOSDEnable(int layer);
extern int FBDEV_O26_InitOSDLayer(int layer);
extern int FBDEV_O26_WriteOSDHeader(struct scanvas*  pstCanvas);

extern int FBDEV_O26_GetZList(LX_FBDEV_ZLIST_T* zList);
extern int FBDEV_O26_SetZList(LX_FBDEV_ZLIST_T* zList);

extern int FBDEV_O26_WriteOSDEndian(int layer, ENDIAN_INFORM_T* endian);
extern int FBDEV_O26_WriteOSDCSC(int layer, CSC_INFORM_T* csc);
extern int FBDEV_O26_GetInterruptStatus(INTERRUPT_INFORM_T intr);
extern int FBDEV_O26_SetInterruptClear(INTERRUPT_INFORM_T intr);
extern int FBDEV_O26_SetInterruptEnable(INTERRUPT_INFORM_T intr, int enable);
extern int FBDEV_O26_DownloadPalette(unsigned int addr, unsigned int size, void* data);

extern int FBDEV_O26_SetViewCtrl(LX_FBDEV_VIEW_CTRL_T* ctrl);
extern int FBDEV_O26_SetConnCtrl(LX_FBDEV_CONN_CTRL_T* ctrl);

extern void FBDEV_O26_CreateProc(struct proc_dir_entry* parent);

/*----------------------------------------------------------------------------------------
    Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* _FBDEV_HW_O26_H_ */

/** @} */
