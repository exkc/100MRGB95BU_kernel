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

#ifndef	_FBDEV_HW_M19_H_
#define	_FBDEV_HW_M19_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
// temporary config for M19 kdriver (fake) verification with M19+(LG1313)
#undef FBDEV_M19_FAKE_VERIFICATION

// enable/disable OSD header_ready_flag
// this feature is the important OSD HW control feature for preventing sync between SW and HW
// DO NOT disable unless you are in test mode
//
#define	FBDEV_M19_USE_HDR_RDY_REG

// enable/disable S3D OSD block
//
// FBDEV_M19_USE_3DOSD_S3D  - control S3D feature
// FBDEV_M19_USE_3DOSD_2D3D - control 2Dto3D feature
//
// raxis.lim (2016/03/28) -- disable 3DOSD for FPGA test
#undef	FBDEV_M19_USE_3DOSD_HW_CTRL

#ifdef	FBDEV_M19_USE_3DOSD_HW_CTRL
#define	FBDEV_M19_USE_3DOSD_S3D
#undef	FBDEV_M19_USE_3DOSD_2D3D
#endif

// Enable/disable the reverse screen mode.
// I think OSD reverse ctrl is not used anymore.
// This won't be used any more (obsolete)
#undef	FBDEV_M19_USE_REVERSE_HW_CTRL
#undef	FBDEV_M19_USE_REV_HW_CTRL

// enable/disable OSD visibility after boot logo
#define FBDEV_M19_KEEP_LOGO_LAYER

// set the system default OSD path
// this configuration will be changed if we have S.OSD fixed board.
#define FBDEV_M19_DEFAULT_OSD_PATH	LX_FBDEV_CONN_OSD_VIDEO_BLEND

// support webOS cursor behaviour temporarily (always 3840x2160 region regardless of blend/sep path)
#define	FBDEV_M19_WEBOS_CURSOR_WORKAROUND

// support the cursor position outside (0,0)~(1920,1080)
// kdriver will accept the exceptional position such as (-100,-100), (3840,1080) etc.
// raxis.lim (2016/12/20)
// TV doesn't require unlimited cursor position to the right side. DISABLE this feature to prevent cursor image corruption
//
#define FBDEV_M19_USE_UNLIMITED_CURSOR_POSITION

// support FBC display
//
// FBC is key feature of M19/M19+. I can't disable this feature forever :)
#define	FBDEV_M19_USE_FBC_CTRL

// support CROP
//
// I don't know what CTRL_CTRL means :(
#define	FBDEV_M19_USE_CROP_CTRL

// support OSD SR (Super Reolution)
// remember that OSD SR is valid only when 2K OSD is upscaled to 4K OSD resolution
//
// TODO: enable it after bringup
#define	FBDEV_M19_USE_SR_CTRL

// use some experimental/unknown paramters
//
//
#define FBDEV_M19_USE_EXPERIMENTAL_CONFIG

// raxis.lim (2016/03/31)
// set current framebuffer address to osd_hdr_base (OSD header address in DDR) address
//
// this SW WA will prevent the different DDR access of osd_hdr from that of framebuffer
// this is fot critical error in normal cases BUT safe solution
//
#define	FBDEV_M19_FIX_INVALID_OSD_HDR_ADDR_REG_ACCESS

// raxis.lim (2016/06/23) - http://clm.lge.com/issue/browse/SICDTV-974
// AFBC flags might be overwritten by VBE_DISP resume process
// I will add temporary workaround until out policy how to configure OSD register in VBE_DISP is fixed
//
#define FBDEV_M19_SW_RECOVERY_AFBC_FLAG_CORRUPTION

// raxis.lim (2016/07/14) - http://clm.lge.com/issue/browse/SICDTV-1009
// AFBC data path change should be done right after CCO HW reads all OSD data.
// it means the critical CCO TopCtrl should be set in interrupt context
// the most import data is CCO_TopCtrl.ctrl_dpath.osd0_afbc_en.
//
// raxis.lim (2016/07/29) - disable !!
// I don't know AFBC path change in ISR will fix the above issue or not
// more and more tests are required.
// I will disable this feature until SW satisfies all TV scenarioes.
//
#undef FBDEV_M19_USE_AFBC_DATA_PATH_CHANGE_ISR_HANDLER

// raxis.lim (2017/03/27)
// support HD(1366x768) OSD handler
// Because HALGAL will pass 1920x768 surface, I don't need to support HD display handler
#undef FBDEV_M19_USE_HD_DISP_HANDLER

// raxis.lim (2018/03/27)
// use CTOP regs to query some clk information in ASIC
#ifndef INCLUDE_KDRV_VER_FPGA
#define FBDEV_M19_USE_CTOP_REGS	// <-- FIXME : not ready
#endif

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
#ifdef FBDEV_M19_FAKE_VERIFICATION /* TEST MODE with M19+ */
#define CCO_CTRL_BASE           0xc9024000
#define CCO_MIF_BASE            0xc9024c00
#define CCO_OSD_BASE            0xc9024100
#define CCO_OSD_SHP_BASE        0xc9025c00
#define CCO_OSD_AFBC_BASE       0xc9024700
#define CCO_OSD_SCAN_BASE       0xC9012000
#else
#define CCO_CTRL_BASE           M19_PQE_TOP_CCO_CTRL_BASE	// M19+ 0xc902_4000 -> M19 0xc901_0000
#define CCO_MIF_BASE            M19_PQE_CCO_MIF_BASE		// M19+ 0xc902_4c00 -> M19 0xc901_0c00
#define CCO_OSD_BASE            M19_CCO_BASE				// M19+ 0xc902_4100 -> M19 0xc901_0100
#define CCO_OSD_SHP_BASE        M19_CCO_SHP_BASE			// M19+ 0xc902_5c00 -> M19 0xc901_1c00
#define CCO_OSD_AFBC_BASE       M19_CCO_AFBC_BASE           // M19+ 0xc902_4700 -> M19 0xc901_0700
#define CCO_OSD_SCAN_BASE       M19_CCO_SCAN_BASE
#endif

#define FBDEV_M19_FIXME(msg)			1

// Actually M19 supports only one graphic plane & one cursor plane
// But the below MAX_OSD_NUM is used to share kdriver design with H15
//
// OSD0 offset : 0x200 --> osdx_ctrl[0]
// CRSR offset : 0x400 --> osdx_ctrl[4]
//
#define	FBDEV_M19_MAX_OSD_BLK_NUM		8

// maximum hardware OSD layer number connected to single FB device.
// because M19 supports only one graphic plane, MAX_XLST is set to 1.
//
#define FBDEV_M19_MAX_XLST				1

// GMAU_WORD means that minimum bytes for gMAU to process the framebuffer simultaneouly
// this value has been 16 byte (ARGB 4 pixel) since H13.
// it means that OSD frame buffer should be multiple of OSD_WORD
// what will happen if we violates this limitation ?
// don't worry. HW never die.
// current OSD HW fix SW bug by removing low 3bits.
// but this might result in the invalid screen output.
#define	FBDEV_M19_GMAU_WORD_BYTES		16

// minimum showing region of cursor
// if cursor is located at the right cornet, mininum threshold value should be guraunteed.
// HW engineer (woonghyeon@kim) reported the recommended threshold pixel value is 16 (64byte)
// becuase HW reads 64 bytes simultaneously.
// According to the test, threshold 14 also works well => I will use 16 rather than 14.
//
// in M19+, I should also consider minimum viewing height.
// According to the board test, minimum value seems to 32.
//
// Remember that the below value is dependent on OSD output dimension.
// For example, M19+ doesn't need any external FRC, so output dimension alwyas is set to 3840x2160
//
#define FBDEV_M19_CSR_MIN_WIDTH				16
#define FBDEV_M19_CSR_MIN_HEIGHT			2 //32

// tune OSD freeze timeout value
// OSD freeze is used to keep boot logo to support very smooth scene change
// in some cases, boot logo display might fix OSD corruption BUT might be suffered from OSD flicker due to sync chnage.
// So I should choose freeze timeout carefully with many TV tests.
//
// related JIRA link:
// - http://clm.lge.com/issue/browse/SICDTV-3119
//
#define FBDEV_M19_BOOT_FREEZE_TIME			1000 	//1300 -> (1000) -> 500 -> 1000
#define FBDEV_M19_RESUME_FREEZE_TIME		300		//1000 -> 800 -> 500 -> 300


// maximum retry for osd0 sync recovery
#define FBDEV_M19_SICDTV_4209_RETRY_MAX		10

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define	FBDEV_M19_FBC_DEBUG					FBDEV_HW0_DEBUG
#define FBDEV_M19_HDR_DEBUG					FBDEV_HW1_DEBUG

#define	FBDEV_M19_NOTE(reason)
#define FBDEV_M19_NOT_IMPL(reason)			0

#define FBDEV_M19_OSD_WORDS_2_BYTES(v)		((v)<<3)		/* OSD_WORD(8byte) -> byte */
#define FBDEV_M19_BYTES_2_OSD_WORDS(v)		((v)>>3)		/* byte -> OSD_WORD(8byte) */

#define FBDEV_M19_BYTES_2_PIXEL(v)			((v)>>2)		/* byte -> ARGB pxl */
#define FBDEV_M19_PIXEL_2_BYTES(v)			((v)<<2)		/* ARGB pxl -> byte */

#define FBDEV_M19_BITS_2_BYTES(v)			((v)>>3)		/* bits -> bytes */

#define FBDEV_M19_GMAU_ALIGNED_BYTES(v)	LX_CALC_ALIGNED_VALUE(v,4)	/* get 16byte algiend value */

#define FBDEV_M19_GET_HW_CTX()                  (FBDEV_M19_HW_CTX_T*)g_fbdev_hw_ctx.chip_priv_ctx
#define FBDEV_M19_GET_SR_CTRL(hw_ctx,fb_id)     &(hw_ctx->sr_ctrl[fb_id])
#define FBDEV_M19_GET_FBC_CTRL(hw_ctx,fb_id)    &(hw_ctx->fbc_ctrl[fb_id])
#define FBDEV_M19_GET_MIRROR_CTRL(hw_ctx)       &(hw_ctx->mirror_ctrl)
#define FBDEV_M19_GET_CONN_CTRL(hw_ctx,fb_id)   &(hw_ctx->conn_ctrl[fb_id])

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/** M19 OSD header structure
 *
 *
 */
typedef struct
{
	UINT32									// OSD[0:3]_HDR0
	osd_hdr_ypos		   			:12,	//  0:11
                       	   			: 4,	// 12:15 reserved
	osd_hdr_xpos           			:12,	// 16:27
                   		   			: 3,	// 28:30 reserved
	osd_hdr_color_key_en   			: 1;	//    31

	UINT32					   				// OSD[0:3]_HDR1
	osd_hdr_h_mem         			:12, 	//  0:11
           			      			: 4, 	// 12:15 reserved
	osd_hdr_w_mem         			:12; 	// 16:27

	UINT32					   				// OSD[0:3]_HDR2
	osd_hdr_h_out         			:12, 	//  0:11
		                  			: 4, 	// 12:15 reserved
	osd_hdr_w_out         			:12, 	// 16:27
                          			: 3, 	// 28:30 reserved
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
FBDEV_M19_OSD_HDR_T;

typedef struct
{
	UINT8							bits_per_pixel;

	UINT32							img_stride;
}
FBDEV_M19_OSD_EXHDR_T;

typedef struct
{
#define FBDEV_M19_FBC_STATUS_NONE			0x0000	/* non AFBC state */
#define FBDEV_M19_FBC_STATUS_HDR_SETUP		0x0001	/* AFBC state, AFBC header is setup & written to register */
#define FBDEV_M19_FBC_STATUS_PATH_CHANGE	0x0002	/* AFBC related path should be set in ISR handler */
	UINT32							status;

	LX_FBDEV_FBC_FORMAT_T			fbc_fmt;
}
FBDEV_M19_FBC_CTRL_T;

/* OSD SR supports 2K to 3K OSD scaler quality
 * only OSD0 supports OSD SR
 *
 * default coeff : 0x3fd, 0x83, 0x83, 0x3fd
 */
typedef struct
{
#define	FBDEV_M19_SR_STATUS_OFF		0x0000
#define	FBDEV_M19_SR_STATUS_ON		0x0001
	UINT32							status;
	UINT32							coeff[4];	/* obsolete, not used anymore */

	int								ti_gain;	/* user-requsted TI_gain value (0x0 ~ 0xff) */
}
FBDEV_M19_SR_CTRL_T;

typedef struct
{
#define	FBDEV_M19_MIRROR_NONE		0x0000
#define FBDEV_M19_V_MIRROR_ON		0x0001
	UINT32							status;
}
FBDEV_M19_MIRROR_CTRL_T;

typedef struct
{
	int 	(*M19_InitHW)			(void);

	int		(*M19_SetViewCtrl)		(LX_FBDEV_VIEW_CTRL_T*);
	int 	(*M19_SetConnCtrl)		(LX_FBDEV_CONN_CTRL_T*);

	int 	(*M19_WriteOSDHeader)	(struct scanvas*);
    int		(*M19_SetOSDEnable)		(int,int);
    int		(*M19_GetOSDEnable)		(int);
}
FBDEV_M19_HW_FUNC_T;

/** M19 OSD specific hardware workaround flag */
enum
{
	FBDEV_M19_HW_WA_1X_CSR_DISP_ON_BLEND_PATH 	= (1<<0),	/* do not support 2x cursor sacle on blend path */
	FBDEV_M19_HW_WA_OSD0_SYNC_ASYNC_WR_ERROR	= (1<<1),	/* OSD0_SYNC async behavior (SICDTV-4209) */

	FBDEV_M19_HW_WA_PQEFW_OSD0_OUT_CTRL			= (1<<2),	/* OSD0 out_win is controlled by PQE (SICDTV-4359) to support OSD orbit */
	FBDEV_M19_HW_WA_PAUSE_PQEFW_OSD0_OUT_CTRL	= (1<<3),	/* pause PQE's out_win controll temporarily */
};

typedef struct
{
	struct
	{
		UINT32						in_width;
		UINT32						in_height;
		UINT32						out_width;
		UINT32						out_height;

		UINT32						pulse_timer_dly;

		BOOLEAN						b_2x_cursor_disp;
	}
	bosd_disp;														/* display size for B.OSD. fixed to 3840x2160 */

	struct
	{
		UINT32						in_width;
		UINT32						in_height;
		UINT32						out_width;
		UINT32						out_height;

		UINT32						pulse_timer_dly;
	}
	sosd_disp;														/* display size for S.OSD. fixed to 1920x1080 */

	BOOLEAN							b_keep_hw_conn_type;			/* DO NOT change OSD connection automatically
																	 * if the HW conn type is set to B.OSD, it means that HW doesn't have S.OSD path.
																	 * so we should now change OSD connection when the initial path is B.OSD.
																	 */
	BOOLEAN							b_support_3dosd;				/* support 3D OSD */

	UINT32							hw_conn_type;					/* current OSD HW connection */

	UINT32							hw_disp_width;					/* current OSD HW disp_width (output)) */
	UINT32							hw_disp_height;					/* current OSD HW disp_height output) */
	UINT32							hw_gfx_width;					/* maximum active area of OSD HW (input) */
	UINT32							hw_gfx_height;					/* maximum active area of OSD HW (input) */

	UINT32							hw_wa_flag;

	UINT32							intr_req_sav;					/* N/A */
	FBDEV_M19_OSD_HDR_T				osd_hdr_sav[LX_FBDEV_ID_MAX];	/* last osd header written */

	LX_FBDEV_CONN_CTRL_T			conn_ctrl[LX_FBDEV_ID_MAX];		/* layer conn ctrl */
	FBDEV_M19_FBC_CTRL_T			fbc_ctrl[LX_FBDEV_ID_MAX];		/* FBC ctrl */
	FBDEV_M19_SR_CTRL_T				sr_ctrl[LX_FBDEV_ID_MAX];		/* SR ctrl */
	FBDEV_M19_MIRROR_CTRL_T			mirror_ctrl;					/* OSD mirror control */

	FBDEV_M19_HW_FUNC_T				func;
}
FBDEV_M19_HW_CTX_T;

typedef enum
{
	FBDEV_M19_HW_STATUS_AFBC	= 0,
}
FBDEV_M19_HW_STATUS_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration (M19_CMN)
----------------------------------------------------------------------------------------*/
/* return physical OSD block index by fb_dev_id
 *
 */

#define INVALID_XNUM(x)         ((x)<=0||(x)>FBDEV_M19_MAX_XLST) 	/* if xnum <= 0 */
#define INVALID_XIDX(x)         ((x)<0)         					/* if xidx = -1 */
extern int		FBDEV_M19_CMN_GetHWXList		(int fb_dev_id, int xlst[2] );

extern void		FBDEV_M19_CMN_WriteHdrRegs		(int fb_dev_id, FBDEV_M19_OSD_HDR_T* osd_hdr, FBDEV_M19_OSD_EXHDR_T* osd_exhdr );
extern void		FBDEV_M19_CMN_WriteFRCHeader	(void );

extern int		FBDEV_M19_CMN_InitHW			(void );
extern int		FBDEV_M19_CMN_InitOSDLayer		(int layer );

extern int      FBDEV_M19_CMN_ExecHWCommand     (FBDEV_HW_CMD_T cmd, FBDEV_HW_CMD_DATA_T* data);

extern int		FBDEV_M19_CMN_SetOSDEnable		(int layer , int enable);
extern int		FBDEV_M19_CMN_GetOSDEnable		(int layer);

extern int		FBDEV_M19_CMN_SetViewCtrl		(LX_FBDEV_VIEW_CTRL_T* ctrl );
extern int		FBDEV_M19_CMN_SetConnCtrl		(LX_FBDEV_CONN_CTRL_T* ctrl);

extern void		FBDEV_M19_CMN_HandleVOSD		(int fb_dev_id, struct scanvas* hCanvans, FBDEV_M19_OSD_HDR_T* osd_hdr );
extern void		FBDEV_M19_CMN_Handle3DOSD		(int fb_dev_id, struct scanvas* hCanvans, FBDEV_M19_OSD_HDR_T* osd_hdr );
extern void     FBDEV_M19_CMN_ISRHook 			(void );
extern void		FBDEV_M19_CMN_HandleReverseOSD	(int fb_dev_id, struct scanvas* hCanvas, FBDEV_M19_OSD_HDR_T* osd_hdr );

extern void		FBDEV_M19_CMN_DoOSDMerge		(int fb_dev_id, BOOLEAN b_flip );

extern int		FBDEV_M19_CMN_RunSuspend		(void);
extern int		FBDEV_M19_CMN_RunResume			(void);

extern void		FBDEV_M19_CMN_ProcHandler		(FBDEV_HW_PROC_ID_T proc_id, struct seq_file* m, void* data);

extern void		FBDEV_M19_CMN_RunBootLogoTimer	(UINT32 ms, BOOLEAN bForce);

extern void		FBDEV_M19_InitOSDZOrder			(void);

extern BOOLEAN	FBDEV_M19_CMN_IsUHDDispMode		(void);

extern int		FBDEV_M19_CMN_SRCtrl			(BOOLEAN onoff);
extern void		FBDEV_M19_CMN_DiagHW			(struct seq_file* m);

extern int		FBDEV_M19_CMN_GetHWStatus		(FBDEV_M19_HW_STATUS_T status, UINT32 opt[3]);

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration (M19 Platform Function)
----------------------------------------------------------------------------------------*/
extern int		FBDEV_M19_InitHW				(void);
extern int		FBDEV_M19_ShutdownHW			(void);
extern int		FBDEV_M19_SetOSDEnable			(int layer , int enable);
extern int		FBDEV_M19_GetOSDEnable			(int layer);
extern int		FBDEV_M19_InitOSDLayer			(int layer);
extern int		FBDEV_M19_WriteOSDHeader		(struct scanvas  *pstCanvas);

extern int		FBDEV_M19_GetZList				(LX_FBDEV_ZLIST_T* zList );
extern int		FBDEV_M19_SetZList				(LX_FBDEV_ZLIST_T* zList );

extern int		FBDEV_M19_WriteOSDEndian		(int layer, ENDIAN_INFORM_T *endian);
extern int		FBDEV_M19_WriteOSDCSC			(int layer, CSC_INFORM_T *csc);
extern int		FBDEV_M19_GetInterruptStatus	(INTERRUPT_INFORM_T intr);
extern int		FBDEV_M19_SetInterruptClear	(INTERRUPT_INFORM_T intr);
extern int		FBDEV_M19_SetInterruptEnable	(INTERRUPT_INFORM_T intr , int enable);
extern int		FBDEV_M19_DownloadPalette		(unsigned int addr , unsigned int size , void *data);

extern int		FBDEV_M19_SetViewCtrl			(LX_FBDEV_VIEW_CTRL_T* ctrl);
extern int		FBDEV_M19_SetConnCtrl			(LX_FBDEV_CONN_CTRL_T* ctrl);

extern	void	FBDEV_M19_CreateProc			(struct proc_dir_entry* parent);

#ifdef	FBDEV_M19_CPB_BW_TEST
extern void		FBDEV_M19TEST_InitCPBTest		(void);
extern void		FBDEV_M19TEST_ISRHandler		(void);
extern BOOLEAN	FBDEV_M19TEST_IsCPBTestMode		(void);
#endif

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _FBDEV_HW_M19_H_ */

/** @} */
