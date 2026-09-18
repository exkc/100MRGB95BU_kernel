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
 *  @author		raxis
 *  @version	1.0
 *  @date		2009.11.15
 *
 *  @addtogroup lg1150_fbdev
 *	@{
 */

#ifndef	_FBDEV_HW_E60_H_
#define	_FBDEV_HW_E60_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
// temporary config for E60 kdriver (fake) verification with E60+(LG1313)
#undef FBDEV_E60_FAKE_VERIFICATION

// enable/disable OSD header_ready_flag
// this feature is the important OSD HW control feature for preventing sync between SW and HW
// DO NOT disable unless you are in test mode
//
#define	FBDEV_E60_USE_HDR_RDY_REG

// Enable/disable the reverse screen mode.
// I think OSD reverse ctrl is not used anymore.
// This won't be used any more (obsolete)
#undef	FBDEV_E60_USE_REVERSE_HW_CTRL
#undef	FBDEV_E60_USE_REV_HW_CTRL

// enable/disable OSD visibility after boot logo
#define FBDEV_E60_KEEP_LOGO_LAYER

// set the system default OSD path
// this configuration will be changed if we have S.OSD fixed board.
#define FBDEV_E60_DEFAULT_OSD_PATH	LX_FBDEV_CONN_OSD_VIDEO_BLEND

// support webOS cursor behaviour temporarily (always 3840x2160 region regardless of blend/sep path)
#define	FBDEV_E60_WEBOS_CURSOR_WORKAROUND

// support the cursor position outside (0,0)~(1920,1080)
// kdriver will accept the exceptional position such as (-100,-100), (3840,1080) etc.
// raxis.lim (2016/12/20)
// TV doesn't require unlimited cursor position to the right side. DISABLE this feature to prevent cursor image corruption
//
#define FBDEV_E60_USE_UNLIMITED_CURSOR_POSITION

// support FBC display
//
// FBC is key feature of E60/E60+. I can't disable this feature forever :)
#define	FBDEV_E60_USE_FBC_CTRL

// support CROP
//
// I don't know what CTRL_CTRL means :(
#define	FBDEV_E60_USE_CROP_CTRL

// support OSD SR (Super Reolution)
// remember that OSD SR is valid only when 2K OSD is upscaled to 4K OSD resolution
//
// TODO: enable it after bringup
#undef	FBDEV_E60_USE_SR_CTRL

// use some experimental/unknown paramters
//
//
#define FBDEV_E60_USE_EXPERIMENTAL_CONFIG

// raxis.lim (2016/03/31)
// set current framebuffer address to osd_hdr_base (OSD header address in DDR) address
//
// this SW WA will prevent the different DDR access of osd_hdr from that of framebuffer
// this is fot critical error in normal cases BUT safe solution
//
#define	FBDEV_E60_FIX_INVALID_OSD_HDR_ADDR_REG_ACCESS

// raxis.lim (2016/06/23) - http://clm.lge.com/issue/browse/SICDTV-974
// AFBC flags might be overwritten by VBE_DISP resume process
// I will add temporary workaround until out policy how to configure OSD register in VBE_DISP is fixed
//
#define FBDEV_E60_SW_RECOVERY_AFBC_FLAG_CORRUPTION

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
#define FBDEV_E60_USE_AFBC_READ_BW_SAVING

// raxis.lim (2017/03/27)
// support HD(1366x768) OSD handler
// Because HALGAL will pass 1920x768 surface, I don't need to support HD display handler
#undef FBDEV_E60_USE_HD_DISP_HANDLER

// raxis.lim (2018/03/27)
// use CTOP regs to query some clk information in ASIC
// CTOP 코드가 준비된 이후에만 아래 코드를 ON 함.
#undef FBDEV_E60_USE_CTOP_REGS

// raxis.lim (2019/05/22)
// E60 supports 4K OSD through 2 AFBC reader
#define	FBDEV_E60_SUPPORT_4KOSD

// enable if you want to support 2K frame buffer on 4K OSD display environment
#undef	FBDEV_E60_SUPPORT_4KOSD_UPSCALER

// raxis.lim (2019/12/14)
// SHP 제어는 별도로 하지 않겠음. 차후 필요시 코드 정리하여 추가할것
#undef	FBDEV_E60_SUPPORT_SHP_CTRL

// raxis.lim (2019/12/14)
// B.OSD, S.OSD 에서 OSD 와 Video 의 mux order 등을 제어할때 사용할것
// 현재는 구현이 되어 있지 않음.
#undef	FBDEV_USE_MIXER_MUX

// raxis.lim (2019/12/16)
//
// 아직 driver 가 완벽하지 않아, HW 엔지이어에게서 입수한 default cmm 기반으로 초기화진행함
#undef	FBDEV_E60_USE_DEFAULT_CMM_INIT

// raxis.lim (2019/12/23)
//
// 실제 설정되는 register 를 디버깅하기 위하여, 필요시 아래 define 을 on 할것
// FBDEV_E60_REG_DEBUG logm 을 켜면 디버깅 가능함
#undef	FBDEV_E60_USE_REG_DEBUG

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

#include <asm/atomic.h>

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define E60_PQE_CCO_IP_TOP_BASE     0xC9030000

#define E60_CCO1_TOP_CTRL_BASE       (E60_PQE_CCO_IP_TOP_BASE+0x0000)    /* 0xC903_0000 */
#define E60_CCO2_TOP_CTRL_BASE      (E60_PQE_CCO_IP_TOP_BASE+0x3000)    /* 0xC901_3000 */
#define E60_CCO_BASE                (E60_PQE_CCO_IP_TOP_BASE+0x0400)    /* 0xC903_0400 */
#define E60_CCO_AFBC0_BASE          (E60_PQE_CCO_IP_TOP_BASE+0x1C00)    /* 0xC903_1C00 */
#define E60_CCO_AFBC1_BASE          (E60_PQE_CCO_IP_TOP_BASE+0x1D00)    /* 0xC903_1D00 */
#define E60_CCO_SHP0_BASE			(E60_PQE_CCO_IP_TOP_BASE+0x3400)    /* 0xC903_3400 */
#define E60_CCO_SHP1_BASE			(E60_PQE_CCO_IP_TOP_BASE+0x3C00)    /* 0xC903_3C00 */
#define E60_CCO_MERG0_BASE			(E60_PQE_CCO_IP_TOP_BASE+0x0E00)    /* 0xC903_0E00 */
#define E60_CCO_MERG1_BASE			(E60_PQE_CCO_IP_TOP_BASE+0x1200)    /* 0xC903_1200 */
#define E60_CCO_MIF0_BASE           (E60_PQE_CCO_IP_TOP_BASE+0x1600)    /* 0xC903_1600 */
#define E60_CCO_MIF1_BASE           (E60_PQE_CCO_IP_TOP_BASE+0x1800)    /* 0xC903_1800 */

// raxis.lim TODO(2019/12/14)
// E60 에서 SHP 는 Y,A,L 로 많이 바뀌어져 있어, 실제 사용을 하지 않는 이상 관련 코드 삭제하기로 함
//
#define CCO_CCO1_CTRL_BASE			E60_CCO1_TOP_CTRL_BASE
#define CCO_CCO2_CTRL_BASE			E60_CCO2_TOP_CTRL_BASE
#define CCO_MIF0_BASE				E60_CCO_MIF0_BASE
#define CCO_MIF1_BASE				E60_CCO_MIF1_BASE
#define CCO_OSD_BASE				E60_CCO_BASE
#define CCO_OSD_AFBC0_BASE			E60_CCO_AFBC0_BASE
#define CCO_OSD_AFBC1_BASE			E60_CCO_AFBC1_BASE
#define CCO_OSD_SHP0_BASE			E60_CCO_SHP0_BASE
#define CCO_OSD_SHP1_BASE			E60_CCO_SHP1_BASE
#define CCO_OSD_MERG0_BASE			E60_CCO_MERG0_BASE
#define CCO_OSD_MERG1_BASE			E60_CCO_MERG1_BASE
#define CCO_OSD_SCAN_BASE			E60_CCO_SCAN_BASE

// Actually E60 supports only one graphic plane & one cursor plane
// But the below MAX_OSD_NUM is used to share kdriver design with H15
//
// OSD0 offset : 0x200 --> osdx_ctrl[0]
// CRSR offset : 0x400 --> osdx_ctrl[4]
//
#define	FBDEV_E60_MAX_OSD_BLK_NUM		4

// maximum hardware OSD layer number connected to single FB device.
//
#define FBDEV_E60_MAX_XLST				2

// GMAU_WORD means that minimum bytes for gMAU to process the framebuffer simultaneouly
// this value has been 16 byte (ARGB 4 pixel) since H13.
// it means that OSD frame buffer should be multiple of OSD_WORD
// what will happen if we violates this limitation ?
// don't worry. HW never die.
// current OSD HW fix SW bug by removing low 3bits.
// but this might result in the invalid screen output.
#define	FBDEV_E60_GMAU_WORD_BYTES		16

// minimum showing region of cursor
// if cursor is located at the right cornet, mininum threshold value should be guraunteed.
// HW engineer (woonghyeon@kim) reported the recommended threshold pixel value is 16 (64byte)
// becuase HW reads 64 bytes simultaneously.
// According to the test, threshold 14 also works well => I will use 16 rather than 14.
//
// in E60+, I should also consider minimum viewing height.
// According to the board test, minimum value seems to 32.
//
// Remember that the below value is dependent on OSD output dimension.
// For example, E60+ doesn't need any external FRC, so output dimension alwyas is set to 3840x2160
//
#define FBDEV_E60_CSR_MIN_WIDTH				16
#define FBDEV_E60_CSR_MIN_HEIGHT			2 //32

// maximum retry for osd0 sync recovery
#define FBDEV_E60_SICDTV_4209_RETRY_MAX		10

// configure default POSD1 size
#define	FBDEV_E60_POSD_NUM					2
#define	FBDEV_E60_POSD0_WIDTH				0		/* auto */
#define	FBDEV_E60_POSD0_HEIGHT				0		/* auto */
#define	FBDEV_E60_POSD1_WIDTH				512		/* 512 by default */
#define	FBDEV_E60_POSD1_HEIGHT				2160	/* 2160 by default */

// support fb(1) single buffer EGL when externel render (F20) exits.
// default value = 1
// refer to http://clm.lge.com/issue/browse/SICDTV-7520
#define	FBDEV_E60_EXT_RENDER_EGL_FBDEV_NUM	1

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define FBDEV_E60_FIXME(msg)				1
#define FBDEV_E60_FIXME_NOTE(msg)
#define TODO_NOTE(msg)

#define	FBDEV_E60_FBC_DEBUG					FBDEV_HW0_DEBUG	/* b12 */
#define FBDEV_E60_HDR_DEBUG					FBDEV_HW1_DEBUG	/* b13 */
#define FBDEV_E60_REG_DEBUG					FBDEV_HW2_DEBUG	/* b14 */
#define FBDEV_E60_XXX_DEBUG					FBDEV_HW3_DEBUG /* b15 */
//#define FBDEV_E60_NOTI					FBDEV_HW_NOTI	/* b16 */

#define	FBDEV_E60_NOTE(reason)
#define FBDEV_E60_NOT_IMPL(reason)			0

#define FBDEV_E60_OSD_WORDS_2_BYTES(v)		((v)<<3)		/* OSD_WORD(8byte) -> byte */
#define FBDEV_E60_BYTES_2_OSD_WORDS(v)		((v)>>3)		/* byte -> OSD_WORD(8byte) */

#define FBDEV_E60_BYTES_2_PIXEL(v)			((v)>>2)		/* byte -> ARGB pxl */
#define FBDEV_E60_PIXEL_2_BYTES(v)			((v)<<2)		/* ARGB pxl -> byte */

#define FBDEV_E60_BITS_2_BYTES(v)			((v)>>3)		/* bits -> bytes */

#define FBDEV_E60_GMAU_ALIGNED_BYTES(v)	LX_CALC_ALIGNED_VALUE(v,4)	/* get 16byte algiend value */

#define FBDEV_E60_GET_HW_CTX()                  (FBDEV_E60_HW_CTX_T*)g_fbdev_hw_ctx.chip_priv_ctx
#define FBDEV_E60_GET_SR_CTRL(hw_ctx,fb_id)     &(hw_ctx->sr_ctrl[fb_id])
#define FBDEV_E60_GET_FBC_CTRL(hw_ctx,fb_id)    &(hw_ctx->fbc_ctrl[fb_id])
#define FBDEV_E60_GET_MIRROR_CTRL(hw_ctx)       &(hw_ctx->mirror_ctrl)
#define FBDEV_E60_GET_CONN_CTRL(hw_ctx,fb_id)   &(hw_ctx->conn_ctrl[fb_id])

#define	FBDEV_E60_GET_EXT_RENDER_CTRL(hw_ctx)	&(hw_ctx->ext_render_ctrl)
#define	FBDEV_E60_GET_OSD_SHP_AUTO_CFG_CTRL(hw_ctx)	&(hw_ctx->osd_shp_auto_cfg_ctrl)

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
	OSD_CTRL_XIDX_IMG 	= 0,
	OSD_CTRL_XIDX_IMG1 	= 1,		/* extra control id for 4K OSD */
	OSD_CTRL_XIDX_EST 	= 2,
	OSD_CTRL_XIDX_CRSR	= 3,

	OSD_CTRL_XIDX_MAX,
}
FBDEV_E60_OSD_CTRL_XIDX_T;

typedef enum
{
	BOOT_LOGO_MODE_IMAGE_KEEP = 0,
	BOOT_LOGO_MODE_IMAGE_CLEAR,
}
FBDEV_E60_BOOT_LOGO_MODE_T;

/** E60 OSD header structure
 *
 *
 */
typedef struct
{
	UINT32									// OSD[0:3]_HDR0
	osd_hdr_ypos                    :13,	//  0:12
	                                : 3,	// 13:15 reserved
	osd_hdr_xpos                    :13,	// 16:28
	                                : 2,	// 29:30 reserved
	osd_hdr_color_key_en            : 1;	//    31			(cursor only?)

	UINT32					   				// OSD[0:3]_HDR1
	osd_hdr_h_mem                   :13,	//  0:12
	                                : 3,	// 13:15 reserved
	osd_hdr_w_mem                   :13;	// 16:28

	UINT32					   				// OSD[0:3]_HDR2
	osd_hdr_h_out                   :13,	//  0:12
	                                : 3,	// 13:15 reserved
	osd_hdr_w_out                   :13,	// 16:28
                          			: 2, 	// 28:30 reserved
	osd_hdr_pixel_order   			: 1; 	//    31

    UINT32									// OSD[0:3]_HDR3
    osd_hdr_wpl                    :16, 	//  0:15
    osd_hdr_global_alpha           : 8, 	// 16:23
    osd_hdr_format                 : 4, 	// 24:27
    osd_hdr_depth                  : 3, 	// 28:30
    osd_hdr_global_alpha_en        : 1; 	//    31

    UINT32									// OSD[0:3]_HDR4
    osd_hdr_color_key              ;    	// 31: 0

    UINT32									// OSD[0:3]_HDR5
    osd_hdr_ptr_plte               ;    	// 31: 0

    UINT32									// OSD[0:3]_HDR6
    osd_hdr_ptr_bmp                ;		// 31: 0
}
FBDEV_E60_OSD_HDR_T;

typedef struct
{
	UINT8							bits_per_pixel;
	UINT32							img_stride;		/* real framebfufer size */
	UINT32							img_height;		/* real framebuffer size */
}
FBDEV_E60_OSD_EXHDR_T;

typedef struct
{
#define FBDEV_E60_FBC_STATUS_NONE			0x0000	/* non AFBC state */
#define FBDEV_E60_FBC_STATUS_HDR_SETUP		0x0001	/* AFBC state, AFBC header is setup & written to register */
#define FBDEV_E60_FBC_STATUS_PATH_CHANGE	0x0002	/* AFBC related path should be set in ISR handler */
	UINT32							status;

	LX_FBDEV_FBC_FORMAT_T			fbc_fmt;
}
FBDEV_E60_FBC_CTRL_T;

/* OSD SR supports 2K to 3K OSD scaler quality
 * only OSD0 supports OSD SR
 *
 * default coeff : 0x3fd, 0x83, 0x83, 0x3fd
 */
typedef struct
{
#define	FBDEV_E60_SR_STATUS_OFF		0x0000
#define	FBDEV_E60_SR_STATUS_ON		0x0001
	UINT32							status;

	int								ti_gain;	/* user-requsted TI_gain value (0x0 ~ 0xff) */
}
FBDEV_E60_SR_CTRL_T;

typedef struct
{
#define	FBDEV_E60_MIRROR_NONE		0x0000
#define FBDEV_E60_V_MIRROR_ON		0x0001
	UINT32							status;
}
FBDEV_E60_MIRROR_CTRL_T;

typedef struct
{
#define	FBDEV_OS0_EXT_RENDER_REG_BASE	0xC902E300

	UINT32							fbmem_phys[2];

	struct
	{
		UINT32						phys_y;		// BASE +0x00
		UINT32						size;		// BASE	+0x04
		union
		{
			struct
			{
				UINT32				xoffset:16,	//  0:15
									enable:1,	// 16:16
									rsvd:2,		// 17:29
									yoffset:13;	// 20:31 see http://hlm.lge.com/issue/browse/WEBOSHWBS-429
			};
			UINT32					command;	// BASE	+0x08
		};

		UINT32						tx_count;	// BASE	+0x0c


		union
		{
			struct
			{
				UINT32				crop_x:16,
									crop_y:16;
			};
			UINT32					crop_xy;	// BASE +0x10
		};

		union
		{
			struct
			{
				UINT32				crop_w:16,
									crop_h:16;
			};
			UINT32					crop_wh;	// BASE +0x14
		};
	}
	hwparam;

	struct
	{
		UINT64						interval_tick_us;
		UINT64						request_tick_us;
	}
	swsync;
}
FBDEV_E60_EXT_RENDER_CTRL_T;

// see http://clm.lge.com/issue/browse/SICDTV-8781
typedef struct
{
#define	FBDEV_OS0_SHP_AUTO_CFG_REG_BASE	0xC902E31C

	UINT32						xxxx;		// dummy

	struct
	{
		union
		{
			struct
			{
				UINT32			osd_res:3,	// 0: 2
								rsvd:29;	// 3:31
			};
			UINT32				command;
		};

	}
	hwparam;
}
FBDEV_E60_OSD_SHP_AUTO_CFG_CTRL_T;

typedef struct
{
	UINT32		ready;				/* if first user frame is requested, ready is set to 1 */

	union
	{
		UINT32	data32;
		struct 
		{
			UINT32	osd_init_done:1,
					osd_v_mirror:1,
					osd_estreamer:1;
		};
	} status;
}
FBDEV_E60_USER_INITCALL_CTRL_T;

typedef struct
{
	int 	(*E60_InitHW)			(void);

	int		(*E60_SetViewCtrl)		(LX_FBDEV_VIEW_CTRL_T*);
	int 	(*E60_SetConnCtrl)		(LX_FBDEV_CONN_CTRL_T*);

	int 	(*E60_WriteOSDHeader)	(struct scanvas*);
    int		(*E60_SetOSDEnable)		(int,int);
    int		(*E60_GetOSDEnable)		(int);
}
FBDEV_E60_HW_FUNC_T;

/** E60 OSD specific hardware workaround flag */
enum
{
	FBDEV_E60_HW_WA_1X_CSR_DISP_ON_BLEND_PATH 	= (1<<0),	/* do not support 2x cursor sacle on blend path */
	FBDEV_E60_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR	= (1<<1),	/* OSD0_SYNC async behavior (SICDTV-4209) */

	FBDEV_E60_HW_WA_PQEFW_OSD0_OUT_CTRL			= (1<<2),	/* OSD0 out_win is controlled by PQE (SICDTV-4359) to support OSD orbit */
	FBDEV_E60_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL	= (1<<3),	/* pause PQE's out_win controll temporarily */
};

typedef struct
{
	struct
	{
		UINT16						fb0_width;
		UINT16						fb0_height;
		UINT16						fb1_width;
		UINT16						fb1_height;
		UINT16						fb3_width;
		UINT16						fb3_height;
		UINT16						out_width;
		UINT16						out_height;

		UINT32						fb_scale_mode;					/* 0: x4, 1: x2, 2: none */
		UINT32						pulse_timer_dly;
	}
	bosd_disp;														/* display size for B.OSD. fixed to 7680x4320 */

	struct
	{
		UINT16						fb0_width;
		UINT16						fb0_height;
		UINT16						fb1_width;
		UINT16						fb1_height;
		UINT16						fb3_width;
		UINT16						fb3_height;
		UINT16						out_width;
		UINT16						out_height;

		UINT32						fb_scale_mode;					/* 0: x4, 1: x2, 2: none */
		UINT32						pulse_timer_dly;
	}
	sosd_disp;														/* display size for S.OSD. fixed to 1920x1080 */

	UINT32							b_keep_hw_conn_type:1, 			/* DO NOT change OSD connection automatically
																	 * if the HW conn type is set to B.OSD, it means that HW doesn't have S.OSD path.
																	 * so we should now change OSD connection when the initial path is B.OSD.
																	 */
									b_support_4kosd:1,				/* support 4K OSD */
									b_support_fb1:1,				/* support another graphic layer */
									b_support_ext_frc:1,			/* support EXT_FRC */
									b_support_ext_render:1,	/* support external renderer for fb(1) */
//									b_ext_fb1_renderer_osd_path:1,	/* support external renderer to display via OSD path */
									b_ext_fb1_renderer_test_mode:1,	/* if defined, ext_fb1_renderer runs with debug mode */
									rsvd:26;

	UINT32							hw_conn_type;					/* current OSD HW connection */

	UINT16							hw_disp_width;					/* current OSD HW disp_width (output)) */
	UINT16							hw_disp_height;					/* current OSD HW disp_height output) */

	UINT16							hw_fb0_width;					/* maximum active area of OSD HW (input) */
	UINT16							hw_fb0_height;					/* maximum active area of OSD HW (input) */
	UINT16							hw_fb1_width;					/* maximum active area of OSD HW (input) */
	UINT16							hw_fb1_height;					/* maximum active area of OSD HW (input) */
	UINT16							hw_fb3_width;					/* maximum active area of OSD HW (input) */
	UINT16							hw_fb3_height;					/* maximum active area of OSD HW (input) */

#define	FB_E60_SCALE_MODE_NONE		2
#define	FB_E60_SCALE_MODE_X2		1
#define	FB_E60_SCALE_MODE_X4		0
	UINT32							hw_fb_scale_mode;


	// (2020/08/06)
	// E60 only model displays E-streamer via PQE path
	// E60+F20 displays E-streamer via OSD path (F20 FW reads E-streamer by reading OSD data)
	// see SICDTV-8669 for detail information
#define FB_E60_EXT_RENDER_PQE_PATH	0x0001
#define FB_E60_EXT_RENDER_OSD_PATH	0x0002
	UINT32							hw_ext_render_output_path;		/* path configuration of external render */
	UINT16							hw_ext_render_width;			/* maximum active area of external render (output) */
	UINT16							hw_ext_render_height;			/* maximum active area of external render (output) */
	UINT32							hw_ext_render_swsync_hz;		/* 83333us = 12Hz, 66666us = 15Hz */
	UINT32							hw_ext_render_bpp;				/* byte per pixel 3(RGB=reoder_method=0) 4(ARGB=reoder_method=1) */

	UINT32							hw_ext_render_debug_xoffset;	/* user defined fixed xoffset (debug only) */
	UINT32							hw_ext_render_debug_osd_output;	/* re-direct ext_render image to OSD (debug only) */

	UINT32							hw_wa_flag;

	UINT32							intr_req_sav;					/* N/A */
	FBDEV_E60_OSD_HDR_T				osd_hdr_sav[LX_FBDEV_ID_MAX];	/* last osd header written */

	LX_FBDEV_CONN_CTRL_T			conn_ctrl[LX_FBDEV_ID_MAX];		/* layer conn ctrl */
	FBDEV_E60_FBC_CTRL_T			fbc_ctrl[LX_FBDEV_ID_MAX];		/* FBC ctrl */
	FBDEV_E60_SR_CTRL_T				sr_ctrl[LX_FBDEV_ID_MAX];		/* SR ctrl */
	FBDEV_E60_MIRROR_CTRL_T			mirror_ctrl;					/* OSD mirror control */

	FBDEV_E60_EXT_RENDER_CTRL_T		ext_render_ctrl;				/* external OSD renderer control */
	FBDEV_E60_OSD_SHP_AUTO_CFG_CTRL_T osd_shp_auto_cfg_ctrl;		/* PQE FW controlled osd sharpness control mode */

	FBDEV_E60_USER_INITCALL_CTRL_T	user_initcall_ctrl;				/* OSD initialization by user frame update */

	FBDEV_E60_HW_FUNC_T				func;
}
FBDEV_E60_HW_CTX_T;

typedef enum
{
	FBDEV_E60_HW_STATUS_AFBC	= 0,
	FBDEV_E60_HW_STATUS_VISIBLE,
	FBDEV_E60_HW_STATUS_SR_GAIN,
}
FBDEV_E60_HW_STATUS_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration (E60_CMN)
----------------------------------------------------------------------------------------*/
/* return physical OSD block index by fb_dev_id
 *
 */
#define INVALID_XNUM(x)         ((x)<=0||(x)>FBDEV_E60_MAX_XLST) 			/* xnum 0, 1 valid */
//#define INVALID_XIDX(x)       ((x)<0 || (x)>=FBDEV_E60_MAX_OSD_BLK_NUM) 	/* xidx 0,1,2,3 valid */
#define INVALID_XIDX(x)         ((x)<0)
#define	VALID_XIDX(x)			((x)>=0 && (x)<FBDEV_E60_MAX_OSD_BLK_NUM)	/* xidx 0,2,2,3 valid */
#define INVALID_AFBC_XIDX(x)	((x)<0 ||(x)>2)

extern int		FBDEV_E60_CMN_GetHWXList		(int fb_dev_id, int xlst[2]);
extern int		FBDEV_E60_CMN_GetHWXListEx		(int fb_dev_id, int xlst[2], int afbc_xlst[2]);

extern void		FBDEV_E60_CMN_WriteHdrRegs		(int fb_dev_id, FBDEV_E60_OSD_HDR_T* osd_hdr, FBDEV_E60_OSD_EXHDR_T* osd_exhdr );
extern void		FBDEV_E60_CMN_WriteFRCHeader	(void );

extern int		FBDEV_E60_CMN_InitHW			(void);
extern int		FBDEV_E60_CMN_InitOSDLayer		(int layer );

#define			HWSETUP_PIC_INIT				0x000
#define			HWSETUP_OSD_SYNC				0x002
#define			HWSETUP_OSD_MIF					0x003

#define			HWSETUP_OSD_PREP_TOP			0x100
#define			HWSETUP_OSD_POST_TOP			0x101
#define			HWSETUP_OSD_MIXER				0x102

#define			HWSETUP_OSD_LAYER				0x200		/* initialize osd common layer */
#define			HWSETUP_OSD_VIEW_CTRL			0x201		/* on/off osd view */

 #define		HWSETUP_IMG_LOADER				0x300
 #define		HWSETUP_IMG_PRE_TOP				0x301
 #define		HWSETUP_IMG_OSDSR				0x302
 #define		HWSETUP_IMG_OSDSHP				0x303
 #define		HWSETUP_IMG_SCALER				0x304
 #define		HWSETUP_IMG_SCALER_COEF			0x305
 #define		HWSETUP_IMG_SR_MERGE_BUF		0x306
 #define		HWSETUP_IMG_POST_SCALER			0x307
 #define		HWSETUP_IMG_POST_TOP			0x308
 #define		HWSETUP_IMG_POST_CORE			0x309
 #define		HWSETUP_IMG_4KOSD				0x30a
 #define		HWSETUP_IMG_AFBC				0x30b

#define			HWSETUP_IMG1_LOADER				0x400

#define			HWSETUP_EST_LOADER				0x500
#define			HWSETUP_EST_PRE_TOP				0x501
#define			HWSETUP_EST_POST_CORE			0x502

#define			HWSETUP_CSR_LOADER				0x600
 #define		HWSETUP_CSR_SCALER				0x601
 #define		HWSETUP_CSR_POST_CORE			0x602


extern void		FBDEV_E60_CMN_SetupHWFunc		(int cfgId, UINT32 param, UINT32 paramex[4]);

extern int      FBDEV_E60_CMN_ExecHWCommand     (FBDEV_HW_CMD_T cmd, FBDEV_HW_CMD_DATA_T* data);

extern int		FBDEV_E60_CMN_SetOSDEnable		(int layer , int enable);
extern int		FBDEV_E60_CMN_GetOSDEnable		(int layer);

extern int		FBDEV_E60_CMN_SetViewCtrl		(LX_FBDEV_VIEW_CTRL_T* ctrl );
extern int		FBDEV_E60_CMN_SetConnCtrl		(LX_FBDEV_CONN_CTRL_T* ctrl);

extern void		FBDEV_E60_CMN_HandleVOSD		(int fb_dev_id, struct scanvas* hCanvans, FBDEV_E60_OSD_HDR_T* osd_hdr );
extern void		FBDEV_E60_CMN_Handle3DOSD		(int fb_dev_id, struct scanvas* hCanvans, FBDEV_E60_OSD_HDR_T* osd_hdr );
extern void     FBDEV_E60_CMN_ISRHook 			(void );
extern void		FBDEV_E60_CMN_HandleReverseOSD	(int fb_dev_id, struct scanvas* hCanvas, FBDEV_E60_OSD_HDR_T* osd_hdr );

extern void		FBDEV_E60_CMN_DoOSDMerge		(int fb_dev_id, BOOLEAN b_flip );

extern void		FBDEV_E60_CMN_RunBootLogoTimer	(UINT32 ms, BOOLEAN bForce);

extern void		FBDEV_E60_InitOSDZOrder			(void);

extern BOOLEAN	FBDEV_E60_CMN_IsUHDDispMode		(void);

extern int		FBDEV_E60_CMN_SRCtrl			(BOOLEAN onoff);

extern int		FBDEV_E60_CMN_RunSuspend		(void);
extern int		FBDEV_E60_CMN_RunResume			(void);

extern int		FBDEV_E60_CMN_GetHWStatus		(FBDEV_E60_HW_STATUS_T status, UINT32 opt);
extern void		FBDEV_E60_CMN_ProcHandler		(FBDEV_HW_PROC_ID_T proc_id, struct seq_file* m, void* data);
extern void		FBDEV_E60_CMN_DiagHW			(struct seq_file* m);

#ifdef FBDEV_E60_USE_REG_DEBUG
#define FBDEV_E60_CMN_RegDebug(base,off,val)	FBDEV_E60_CMN_RegDebugTag(base,off,val,__FUNCTION__,__LINE__)
extern void		FBDEV_E60_CMN_RegDebugTag		(UINT32 base, UINT32 off, UINT32 val, const char* func, const int line);
#endif

extern void FBDEV_E60_CMN_MigrateBootLogo		(FBDEV_E60_BOOT_LOGO_MODE_T mode);

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration (E60 Platform Function)
----------------------------------------------------------------------------------------*/
extern int		FBDEV_E60_InitHW				(void);
extern int		FBDEV_E60_ShutdownHW			(void);
extern int		FBDEV_E60_SetOSDEnable			(int layer , int enable);
extern int		FBDEV_E60_GetOSDEnable			(int layer);
extern int		FBDEV_E60_InitOSDLayer			(int layer);
extern int		FBDEV_E60_WriteOSDHeader		(struct scanvas  *pstCanvas);

extern int		FBDEV_E60_GetZList				(LX_FBDEV_ZLIST_T* zList );
extern int		FBDEV_E60_SetZList				(LX_FBDEV_ZLIST_T* zList );

extern int		FBDEV_E60_WriteOSDEndian		(int layer, ENDIAN_INFORM_T *endian);
extern int		FBDEV_E60_WriteOSDCSC			(int layer, CSC_INFORM_T *csc);
extern int		FBDEV_E60_GetInterruptStatus	(INTERRUPT_INFORM_T intr);
extern int		FBDEV_E60_SetInterruptClear	(INTERRUPT_INFORM_T intr);
extern int		FBDEV_E60_SetInterruptEnable	(INTERRUPT_INFORM_T intr , int enable);
extern int		FBDEV_E60_DownloadPalette		(unsigned int addr , unsigned int size , void *data);

extern int		FBDEV_E60_SetViewCtrl			(LX_FBDEV_VIEW_CTRL_T* ctrl);
extern int		FBDEV_E60_SetConnCtrl			(LX_FBDEV_CONN_CTRL_T* ctrl);

extern	void	FBDEV_E60_CreateProc			(struct proc_dir_entry* parent);

#ifdef	FBDEV_E60_CPB_BW_TEST
extern void		FBDEV_E60TEST_InitCPBTest		(void);
extern void		FBDEV_E60TEST_ISRHandler		(void);
extern BOOLEAN	FBDEV_E60TEST_IsCPBTestMode		(void);
#endif

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _FBDEV_HW_E60_H_ */

/** @} */
