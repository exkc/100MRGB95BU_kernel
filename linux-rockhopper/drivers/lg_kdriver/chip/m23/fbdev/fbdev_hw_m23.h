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

/** @file
 *
 *  driver interface header for fbdev device. ( used only within kdriver )
 *
 *  @author     raxis
 *  @version    1.0
 *  @date       2021-04-01
 *
 *  @addtogroup lg1150_fbdev
 *  @{
 */

#ifndef _FBDEV_HW_M23_H_
#define _FBDEV_HW_M23_H_

// 추가 작업이 필요한 부분에서 메시지 남겨 놓을것
#define FBDEV_M23_TODO(msg)

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/
// temporary config for O20 kdriver (fake) verification with O20+(LG1313)
#undef FBDEV_M23_FAKE_VERIFICATION

// enable/disable OSD header_ready_flag
// this feature is the important OSD HW control feature for preventing sync between SW and HW
// DO NOT disable unless you are in test mode
//
// M23 확인
//
#define FBDEV_M23_USE_HDR_RDY_REG

// enable/disable OSD visibility after boot logo
#define FBDEV_M23_KEEP_LOGO_LAYER

// set the system default OSD path
// this configuration will be changed if we have S.OSD fixed board.
#define FBDEV_M23_DEFAULT_OSD_PATH  LX_FBDEV_CONN_OSD_VIDEO_BLEND

// support webOS cursor behaviour temporarily (always 3840x2160 region regardless of blend/sep path)
#define FBDEV_M23_WEBOS_CURSOR_WORKAROUND

// support the cursor position outside (0,0)~(1920,1080)
// kdriver will accept the exceptional position such as (-100,-100), (3840,1080) etc.
// raxis.lim (2016/12/20)
// TV doesn't require unlimited cursor position to the right side. DISABLE this feature to prevent cursor image corruption
//
#define FBDEV_M23_USE_UNLIMITED_CURSOR_POSITION

// support FBC display
//
// FBC is key feature of O20/O20+. I can't disable this feature forever :)
#define FBDEV_M23_USE_FBC_CTRL

// support CROP
//
// I don't know what CTRL_CTRL means :(
#define FBDEV_M23_USE_CROP_CTRL

// support OSD SR (Super Reolution)
// remember that OSD SR is valid only when 2K OSD is upscaled to 4K OSD resolution
//
// TODO: enable it after bringup
#define FBDEV_M23_USE_SR_CTRL

// use some experimental/unknown paramters
//
// M23 확인
//
#define FBDEV_M23_USE_EXPERIMENTAL_CONFIG

// raxis.lim (2016/03/31)
// set current framebuffer address to osd_hdr_base (OSD header address in DDR) address
//
// this SW WA will prevent the different DDR access of osd_hdr from that of framebuffer
// this is fot critical error in normal cases BUT safe solution
//
#define FBDEV_M23_FIX_INVALID_OSD_HDR_ADDR_REG_ACCESS

// raxis.lim (2016/06/23) - http://clm.lge.com/issue/browse/SICDTV-974
// AFBC flags might be overwritten by VBE_DISP resume process
// I will add temporary workaround until out policy how to configure OSD register in VBE_DISP is fixed
//
#define FBDEV_M23_SW_RECOVERY_AFBC_FLAG_CORRUPTION

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
#define FBDEV_M23_USE_AFBC_READ_BW_SAVING

// 2개의 SHP 를 제어토록 합니다.
#undef FBDEV_M23_USE_DUALSHP_CTRL

// raxis.lim (2018/03/27)
// use CTOP regs to query some clk information in ASIC
#ifndef PLATFORM_FPGA
// CTOP 코드가 준비된 이후에만 아래 코드를 ON 함.
#define FBDEV_M23_USE_CTOP_REGS
#endif

// enable if you want to support 2K frame buffer on 4K OSD display environment
// #undef  FBDEV_M23_SUPPORT_4KOSD_UPSCALER

// support SICDTV-7971 SW WA
// see http://clm.lge.com/issue/browse/SICDTV-7971
#undef  FBDEV_M23_SUPPORT_SW_WA_SICDTV_7971

// BUG: F22 에서 OSD 변경 감지 기능이 부족함. cursor on->off 상태를 감지하지 못함
//      OSD 변경 감지가 누락될 경우, 최종 화면 업데이트가 안됨

//      - F22 에서 OSD SR 은 M23 OSD 의 변화가 있는 경우에만 동작하여, 최종 프레임버퍼 생성
//      - M23 출력에서 이미지 주소값 혹은 좌표값이 바뀌는 경우만 체크함
//      - osd on/off 변경량을 감지하지 못함
//
// see http://clm.lge.com/issue/browse/SICDTV-10362
#define FBDEV_M23_SUPPORT_SW_WA_SICDTV_10362

// support AFBC (not ARGB) E-streamer
// see http://clm.lge.com/issue/browse/SICDTV-10314
// see also http://clm.lge.com/issue/browse/AVTASK-640 how to make 8K-Estreamer image format
// see also http://collab.lge.com/main/x/mLAuVw
//
// 기본적으로 AVASK-640 에서 요청하는 E-Streamer 이미지를 재조합해야 하고,
// AFBC 이미지 포맷에 대한 헤더 조작이므로, 관련 코드가 깔끔하지 않을 수 있음
//
// M23 확인
//
#define FBDEV_M23_USE_AFBC_ESTREAMER

// support OSD_CTRl by PQEFW such as orbit control
//
// M23 에서는 지원하지 않기 때문에, define 된 블럭은 미검증 상태임을 기억할것
#undef FBDEV_M23_SUPPORT_PQEFW_OSD_CTRL

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include <asm/atomic.h>



/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/
#define M23_CCO_TOP_CTRL_BASE       0xCC4B0000
#define M23_CCO_TOP_CTRL1_BASE      0xCC4B0E00
#define M23_CCO_BASE                0xCC4B0100
#define M23_CCO_AFBC0_BASE          0xCC4B0800
#define M23_CCO_MIF0_BASE           0xCC4B0C00

// below value is just to used to configure osdx_common_disp_size[8]
// remember that the valid OSD layer is only 0(UI), 1(4K UI EXT), 2(EST), 4(CSR)
#define FBDEV_M23_MAX_OSD_DISP_NUM      8

// Actually O20 supports only one graphic plane & one cursor plane
// But the below MAX_OSD_NUM is used to share kdriver design with H15
//
// OSD0 offset : 0x200 --> osdx_ctrl[0]
// CRSR offset : 0x400 --> osdx_ctrl[4]
//
#define FBDEV_M23_MAX_OSD_BLK_NUM       4

// maximum hardware OSD layer number connected to single FB device.
//
#define FBDEV_M23_MAX_XLST              2

// GMAU_WORD means that minimum bytes for gMAU to process the framebuffer simultaneouly
// this value has been 16 byte (ARGB 4 pixel) since H13.
// it means that OSD frame buffer should be multiple of OSD_WORD
// what will happen if we violates this limitation ?
// don't worry. HW never die.
// current OSD HW fix SW bug by removing low 3bits.
// but this might result in the invalid screen output.
#define FBDEV_M23_GMAU_WORD_BYTES       16

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
#define FBDEV_M23_CSR_MIN_WIDTH             16
#define FBDEV_M23_CSR_MIN_HEIGHT            2 //32

// maximum retry for osd0 sync recovery
#define FBDEV_M23_SICDTV_4209_RETRY_MAX     10

// configure default POSD size
#define FBDEV_M23_POSD0_WIDTH               0       /* auto */
#define FBDEV_M23_POSD0_HEIGHT              0       /* auto */
#define FBDEV_M23_POSD1_WIDTH               512     /* 512 by default */
#define FBDEV_M23_POSD1_HEIGHT              2160    /* 2160 by default */

// M23 은 ext render 사용하지 않고, 일반 linuxfb 를 지원함. double buffer 지원토록 함
#define FBDEV_M23_EXT_RENDER_EGL_FBDEV_NUM  2

#define FBDEV_M23_BOSD_NUM                  1
#define FBDEV_M23_SOSD_NUM                  0

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
#define FBDEV_M23_FIXME(msg)                1
#define FBDEV_M23_FIXME_NOTE(msg)

#define FBDEV_M23_FBC_DEBUG                 FBDEV_HW0_DEBUG /* b12 */
#define FBDEV_M23_HDR_DEBUG                 FBDEV_HW1_DEBUG /* b13 */

#define FBDEV_M23_NOTE(reason)
#define FBDEV_M23_NOT_IMPL(reason)          0

#define FBDEV_M23_OSD_WORDS_2_BYTES(v)      ((v)<<3)        /* OSD_WORD(8byte) -> byte */
#define FBDEV_M23_BYTES_2_OSD_WORDS(v)      ((v)>>3)        /* byte -> OSD_WORD(8byte) */

#define FBDEV_M23_BYTES_2_PIXEL(v)          ((v)>>2)        /* byte -> ARGB pxl */
#define FBDEV_M23_PIXEL_2_BYTES(v)          ((v)<<2)        /* ARGB pxl -> byte */

#define FBDEV_M23_BITS_2_BYTES(v)           ((v)>>3)        /* bits -> bytes */

#define FBDEV_M23_GMAU_ALIGNED_BYTES(v) LX_CALC_ALIGNED_VALUE(v,4)  /* get 16byte algiend value */

#define FBDEV_M23_GET_HW_CTX()                  (FBDEV_M23_HW_CTX_T*)g_fbdev_hw_ctx.chip_priv_ctx
#define FBDEV_M23_GET_SR_CTRL(hw_ctx,fb_id)     &(hw_ctx->sr_ctrl[fb_id])
#define FBDEV_M23_GET_FBC_CTRL(hw_ctx,fb_id)    &(hw_ctx->fbc_ctrl[fb_id])
#define FBDEV_M23_GET_MIRROR_CTRL(hw_ctx)       &(hw_ctx->mirror_ctrl)
#define FBDEV_M23_GET_CONN_CTRL(hw_ctx,fb_id)   &(hw_ctx->conn_ctrl[fb_id])
#define FBDEV_M23_GET_EXT_RENDER_CTRL(hw_ctx)   &(hw_ctx->ext_render_ctrl)

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
    BOOT_LOGO_MODE_IMAGE_KEEP = 0,
    BOOT_LOGO_MODE_IMAGE_CLEAR,
}
FBDEV_M23_BOOT_LOGO_MODE_T;

/** O20 OSD header structure
 *
 *
 */
typedef struct
{
    UINT32                                  // OSD[0:3]_HDR0
    osd_hdr_ypos                    : 12,   //  0:11
                                    : 4,    // 12:15 reserved
                                    osd_hdr_xpos                    : 12,   // 16:27
                                    : 3,    // 28:30 reserved
                                    osd_hdr_color_key_en            : 1;    //    31

    UINT32                                  // OSD[0:3]_HDR1
    osd_hdr_h_mem                   : 12,   //  0:11
                                    : 4,    // 12:15 reserved
                                    osd_hdr_w_mem                   : 12;   // 16:27

    UINT32                                  // OSD[0:3]_HDR2
    osd_hdr_h_out                   : 12,   //  0:11
                                    : 4,    // 12:15 reserved
                                    osd_hdr_w_out                   : 12,   // 16:27
                                    : 3,    // 28:30 reserved
                                    osd_hdr_pixel_order             : 1;    //    31

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
FBDEV_M23_OSD_HDR_T;

typedef struct
{
    UINT8                           bits_per_pixel;
    UINT32                          img_stride;     /* real framebfufer size */
    UINT32                          img_height;     /* real framebuffer size */
}
FBDEV_M23_OSD_EXHDR_T;

typedef struct
{
#define FBDEV_M23_FBC_STATUS_NONE           0x0000  /* non AFBC state */
#define FBDEV_M23_FBC_STATUS_HDR_SETUP      0x0001  /* AFBC state, AFBC header is setup & written to register */
#define FBDEV_M23_FBC_STATUS_PATH_CHANGE    0x0002  /* AFBC related path should be set in ISR handler */
    UINT32                          status;

    LX_FBDEV_FBC_FORMAT_T           fbc_fmt;
}
FBDEV_M23_FBC_CTRL_T;

typedef struct
{
#define FBDEV_M23_MIRROR_NONE       0x0000
#define FBDEV_M23_V_MIRROR_ON       0x0001
    UINT32                          status;
}
FBDEV_M23_MIRROR_CTRL_T;

typedef struct
{
    struct
    {
        UINT16  xoffset;
        UINT16  yoffset;
        UINT16  crop_x;
        UINT16  crop_y;
        UINT16  crop_w;
        UINT16  crop_h;
    }
    hwparam;

    struct
    {
        UINT64  interval_tick_us;
        UINT64  request_tick_us;
    }
    swsync;
}
FBDEV_M23_EXT_RENDER_CTRL_T;

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
FBDEV_M23_USER_INITCALL_CTRL_T;

typedef struct
{
    int (*M23_InitHW)(void);
}
FBDEV_M23_HW_FUNC_T;

/** O20 OSD specific hardware workaround flag */
enum
{
    FBDEV_M23_HW_WA_1X_CSR_DISP_ON_BLEND_PATH   = (1 << 0), /* do not support 2x cursor sacle on blend path */
    FBDEV_M23_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR    = (1 << 1), /* OSD0_SYNC async behavior (SICDTV-4209) */

    FBDEV_M23_HW_WA_PQEFW_OSD0_OUT_CTRL         = (1 << 2), /* OSD0 out_win is controlled by PQE (SICDTV-4359) to support OSD orbit */
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

        BOOLEAN                     b_2x_cursor_disp;
    }
    bosd_disp;                                                      /* display size for B.OSD. fixed to 3840x2160 */


    // M23 에서는 S.OSD 미지원으로 sosd_disp 설정/사용하지 않음
#if 0
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
    sosd_disp;                                                      /* display size for S.OSD. fixed to 1920x1080 */
#endif

    UINT32                          b_keep_hw_conn_type: 1,          /* DO NOT change OSD connection automatically
                                                                     * if the HW conn type is set to B.OSD, it means that HW doesn't have S.OSD path.
                                                                     * so we should now change OSD connection when the initial path is B.OSD.
                                                                     */
                                    b_support_4kosd: 1,             /* support 4K OSD */
                                    b_support_fb1: 1,               /* support another graphic layer */
                                    b_support_ext_frc: 1,           /* support EXT_FRC */
                                    b_rsvd,                         /* support external render for fb(1) */
                                    rsvd: 27;

    UINT32                          hw_conn_type;                   /* current OSD HW connection */

    UINT16                          hw_disp_width;                  /* current OSD HW disp_width (output)) */
    UINT16                          hw_disp_height;                 /* current OSD HW disp_height output) */
    UINT16                          hw_fb0_width;                   /* maximum active area of OSD HW (input) */
    UINT16                          hw_fb0_height;                  /* maximum active area of OSD HW (input) */
    UINT16                          hw_fb1_width;                   /* maximum active area of OSD HW (input) */
    UINT16                          hw_fb1_height;                  /* maximum active area of OSD HW (input) */

    UINT16                          hw_osd0_owner;                  /* fb0, fb1 shares osd0 */
    UINT16                          hw_ext_render_swsync_hz;        /* 83333us = 12Hz, 66666us = 15Hz */

    UINT32                          hw_wa_flag;

    UINT32                          intr_req_sav;                   /* N/A */
    FBDEV_M23_OSD_HDR_T             osd_hdr_sav[LX_FBDEV_ID_MAX];   /* last osd header written */

    LX_FBDEV_CONN_CTRL_T            conn_ctrl[LX_FBDEV_ID_MAX];     /* layer conn ctrl */
    FBDEV_M23_FBC_CTRL_T            fbc_ctrl[LX_FBDEV_ID_MAX];      /* FBC ctrl */
    FBDEV_M23_MIRROR_CTRL_T         mirror_ctrl;                    /* OSD mirror control */
    FBDEV_M23_EXT_RENDER_CTRL_T     ext_render_ctrl;                /* external OSD (e-streamer) render control */

    FBDEV_M23_USER_INITCALL_CTRL_T  user_initcall_ctrl;             /* OSD initialization by user frame update */

    FBDEV_M23_HW_FUNC_T             func;
}
FBDEV_M23_HW_CTX_T;

typedef enum
{
    FBDEV_M23_HW_STATUS_AFBC    = 0,
    FBDEV_M23_HW_STATUS_VISIBLE,
    FBDEV_M23_HW_STATUS_SR_GAIN,
}
FBDEV_M23_HW_STATUS_T;

/*----------------------------------------------------------------------------------------
    Extern Function Prototype Declaration (M23_CMN)
----------------------------------------------------------------------------------------*/
/* return physical OSD block index by fb_dev_id
 *
 */
#define INVALID_XNUM(x)         ((x)<=0||(x)>FBDEV_M23_MAX_XLST)            /* xnum 0, 1 valid */
//#define INVALID_XIDX(x)       ((x)<0 || (x)>=FBDEV_M23_MAX_OSD_BLK_NUM)   /* xidx 0,1,2,3 valid */
#define INVALID_XIDX(x)         ((x)<0)
#define VALID_XIDX(x)           ((x)>=0 && (x)<FBDEV_M23_MAX_OSD_BLK_NUM)   /* xidx 0,2,2,3 valid */
#define INVALID_AFBC_XIDX(x)    ((x)<0 ||(x)>2)

extern int      FBDEV_M23_CMN_GetHWXList(int fb_dev_id, int xlst[2]);
extern int      FBDEV_M23_CMN_GetHWXListEx(int fb_dev_id, int xlst[2], int afbc_xlst[2]);

extern void     FBDEV_M23_CMN_WriteHdrRegs(int fb_dev_id, FBDEV_M23_OSD_HDR_T* osd_hdr,
        FBDEV_M23_OSD_EXHDR_T* osd_exhdr);
extern void     FBDEV_M23_CMN_WriteFRCHeader(void);

extern int      FBDEV_M23_CMN_InitHW(void);
extern int      FBDEV_M23_CMN_InitOSDLayer(int layer);

extern int      FBDEV_M23_CMN_ExecHWCommand(FBDEV_HW_CMD_T cmd, FBDEV_HW_CMD_DATA_T* data);

extern int      FBDEV_M23_CMN_SetOSDEnable(int layer, int enable);
extern int      FBDEV_M23_CMN_GetOSDEnable(int layer);

extern int      FBDEV_M23_CMN_WriteOSDHeader(struct scanvas* pCanvas);

extern int      FBDEV_M23_CMN_SetViewCtrl(LX_FBDEV_VIEW_CTRL_T* ctrl);
extern int      FBDEV_M23_CMN_SetConnCtrl(LX_FBDEV_CONN_CTRL_T* ctrl);

extern int      FBDEV_M23_CMN_SetInterruptEnable(INTERRUPT_INFORM_T intr, int enable);
extern int      FBDEV_M23_CMN_GetInterruptStatus(INTERRUPT_INFORM_T intr);
extern int      FBDEV_M23_CMN_SetInterruptClear(INTERRUPT_INFORM_T intr);

extern void     FBDEV_M23_CMN_HandleVOSD(int fb_dev_id, struct scanvas* hCanvans, FBDEV_M23_OSD_HDR_T* osd_hdr);
extern void     FBDEV_M23_CMN_Handle3DOSD(int fb_dev_id, struct scanvas* hCanvans, FBDEV_M23_OSD_HDR_T* osd_hdr);
extern void     FBDEV_M23_CMN_ISRHook(void);
extern void     FBDEV_M23_CMN_HandleReverseOSD(int fb_dev_id, struct scanvas* hCanvas, FBDEV_M23_OSD_HDR_T* osd_hdr);

extern void     FBDEV_M23_CMN_DoOSDMerge(int fb_dev_id, BOOLEAN b_flip);

extern int      FBDEV_M23_CMN_RunSuspend(void);
extern int      FBDEV_M23_CMN_RunResume(void);

extern void     FBDEV_M23_CMN_ProcHandler(FBDEV_HW_PROC_ID_T proc_id, struct seq_file* m, void* data);

extern void     FBDEV_M23_CMN_RunBootLogoTimer(UINT32 ms, BOOLEAN bForce);

extern void     FBDEV_M23_InitOSDZOrder(void);

extern BOOLEAN  FBDEV_M23_CMN_IsUHDDispMode(void);

extern int      FBDEV_M23_CMN_SRCtrl(BOOLEAN onoff);
extern void     FBDEV_M23_CMN_DiagHW(struct seq_file* m);

extern int      FBDEV_M23_CMN_GetHWStatus(FBDEV_M23_HW_STATUS_T status, UINT32 opt);

extern void     FBDEV_M23_CMN_SetBootFreezeTimeout(int val);

extern void     FBDEV_M23_CMN_MigrateBootLogo(FBDEV_M23_BOOT_LOGO_MODE_T mode);

/*----------------------------------------------------------------------------------------
    Extern Function Prototype Declaration (O20 Platform Function)
----------------------------------------------------------------------------------------*/
extern int      FBDEV_M23_InitHW(void);
extern int      FBDEV_M23_ShutdownHW(void);
extern int      FBDEV_M23_SetOSDEnable(int layer, int enable);
extern int      FBDEV_M23_GetOSDEnable(int layer);
extern int      FBDEV_M23_InitOSDLayer(int layer);
extern int      FBDEV_M23_WriteOSDHeader(struct scanvas*  pstCanvas);

extern int      FBDEV_M23_GetZList(LX_FBDEV_ZLIST_T* zList);
extern int      FBDEV_M23_SetZList(LX_FBDEV_ZLIST_T* zList);

extern int      FBDEV_M23_WriteOSDEndian(int layer, ENDIAN_INFORM_T* endian);
extern int      FBDEV_M23_WriteOSDCSC(int layer, CSC_INFORM_T* csc);
extern int      FBDEV_M23_GetInterruptStatus(INTERRUPT_INFORM_T intr);
extern int      FBDEV_M23_SetInterruptClear(INTERRUPT_INFORM_T intr);
extern int      FBDEV_M23_SetInterruptEnable(INTERRUPT_INFORM_T intr, int enable);
extern int      FBDEV_M23_DownloadPalette(unsigned int addr, unsigned int size, void* data);

extern int      FBDEV_M23_SetViewCtrl(LX_FBDEV_VIEW_CTRL_T* ctrl);
extern int      FBDEV_M23_SetConnCtrl(LX_FBDEV_CONN_CTRL_T* ctrl);

extern  void    FBDEV_M23_CreateProc(struct proc_dir_entry* parent);

#ifdef  FBDEV_M23_CPB_BW_TEST
extern void     FBDEV_M23TEST_InitCPBTest(void);
extern void     FBDEV_M23TEST_ISRHandler(void);
extern BOOLEAN  FBDEV_M23TEST_IsCPBTestMode(void);
#endif

/*----------------------------------------------------------------------------------------
    Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* _FBDEV_HW_M23_H_ */

/** @} */
