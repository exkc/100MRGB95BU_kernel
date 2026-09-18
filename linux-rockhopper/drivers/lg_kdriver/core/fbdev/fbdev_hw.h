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
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author     raxis.lim
 *  @version    1.0
 *  @date       2010-12-09
 *  @note       Additional information.
 */

#ifndef _FBDEV_HW_H_
#define _FBDEV_HW_H_

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
/** write OSD header to memory */
#define FBDEV_REG_MEMCPY(dst,src,cnt)                           \
{                                                               \
    register int i;                                             \
    volatile UINT32* dst_ptr = (volatile UINT32*)dst;           \
             UINT32* src_ptr = (UINT32*)src;                    \
    for ( i=cnt; i>0; i-- )  *dst_ptr++ = *src_ptr++;           \
}

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/* FBDEV regiseter configuration
 *
 */
typedef struct
{
    char*       chip_name;
    UINT32      reg_base_addr;
    UINT32      reg_size;
    UINT32      irq_num;

#define FBDEV_HDR_OP_MMIO   0
#define FBDEV_HDR_OP_REG    1
    UINT32      hdr_op_method: 1,       /* heaer operation method */
                : 31;
}
FBDEV_HW_IO_CFG_T;


/**
* pixel format enumeration
*/
typedef enum
{
    YCbCr655    = 0x00,//'0000b',
    AYCbCr2644,  //'0001b',
    AYCbCr4633,  //= '0010b',
    AYCbCr6433,  //= '0011b',
    YCbCr888,    //= '0100b',
    AYCbCr8655,  //= '0101b',
    AYCbCr8888,  //= '0110b',
    AYCbCr8888d, //= '0111b',
    RGB565,      //= '1000b',
    ARGB1555,    //= '1001b',
    ARGB4444,    //= '1010b',
    ARGB6343,    //= '1011b',
    RGB888,      //= '1100b',
    ARGB8565,    //= '1101b',
    ARGB8888    //= '1110b',
}
OSD_PixFormat;

typedef enum E_PIXEL_DEPTH
{
    PIX_DEPTH_1_BPP = 0,    /* 2 indexed colors */
    PIX_DEPTH_2_BPP,        /* 4 indexed colors */
    PIX_DEPTH_4_BPP,        /* 16 indexed colors */
    PIX_DEPTH_8_BPP,        /* 256 indexed colors */
    PIX_DEPTH_16_BPP,       /* 65536 real/true colors */
    PIX_DEPTH_24_BPP,       /* 2^24 real/true colors */
    PIX_DEPTH_32_BPP,       /* 2^32 real/true colors */
    PIX_DEPTH_MAX,
}
EPixelDepth;

/**
    enum definition
*/
typedef enum
{
    CRSR_INTR       = 0,
    OSD_2_INTR      = 1,
    OSD_1_INTR      = 2,
    OSD_0_INTR      = 3,
    MIXER_INTR      = 4,
    MIXER_INTR_EXT  = 5,    /* @note supported from H13B0 or later */
    ALL_INTR        = 6
}
INTERRUPT_INFORM_T;

/**
    structure
*/
typedef struct
{
    unsigned short  header; // (1<<0) : byte , (1<<1) : quarter word , (1<<2) : half word
    unsigned short  palette; // (1<<0) : byte , (1<<1) : quarter word , (1<<2) : half word
    unsigned short  image; // (1<<0) : byte , (1<<1) : quarter word , (1<<2) : half word
}
ENDIAN_INFORM_T;

typedef struct
{
    unsigned short  data;
    bool            rw_n;
    bool            bypass;
    bool            sel;
    unsigned short  out_ctrl;
    unsigned short  in_ctrl;
}
CSC_INFORM_T;


/** FRC connection ctrl
 *
 *  @note only valid for L9
 */
typedef struct
{
    BOOLEAN
    b_frc_sep_enable;       /* OSD separated mode : TRUE when enabled, FALSE when disabled or STD LVDS/UD mode */
    BOOLEAN                 b_frc_UD_enable;
    BOOLEAN                 b_frc_hdr_emul;         /* check if OSD should generate FRC3 header */
    BOOLEAN                 b_frc_osd_emul;         /* ? */

    BOOLEAN
    b_frc_720p_disp_enable; /* make 1280x1080 OSD to fix FRC3 jpeg line buffer issue. valid only for L9B1+FRCA1 */

    int                     frc_hdr_emul_dev;
}
FBDEV_FRC_CTRL_T;

extern  FBDEV_FRC_CTRL_T    g_fbdev_frc_ctrl;

/** VSYNC CLK
 *
 */
typedef enum
{
    FBDEV_VSYNC_CLK_60HZ    = 0,
    FBDEV_VSYNC_CLK_120HZ   = 1,
}
FBDEV_VSYNC_CLK_T;


/* HW control data */
typedef struct
{
    UINT32  gen[4];     // general paramter
    UINT64  genex[2];   // external paramter
}
FBDEV_HW_CMD_DATA_T;

/* HW control command */
typedef enum
{
    /* do some post initialization after each module initialization
     *
     * it's used during chip bringup stage.
     */
    FBDEV_HW_CMD_IO_POST_HW_INIT,

    /* notify POSD open/close to chip kdriver.
     *
     * this signal makes kdriver to track of the life-time with application.
     * for example, POSD_OPEN signal triggers the osd freeze timer for boot logo.
     *
     * data.gen[0] = fb_dev_id
     */
    FBDEV_HW_CMD_IO_POSD_OPEN,
    FBDEV_HW_CMD_IO_POSD_CLOSE,

    /* notify OSD resolution is changed by user (application)
     *
     * data.gen[0] = fb_dev_id
     */
    FBDEV_HW_CMD_IO_USER_POSD_RESOL_CHANGED,

    /* notify VSNC interrupt to chip kdriver.
     *
     *
     */
    FBDEV_HW_CMD_IO_VSYNC,

    /* notify PQE FW LOAD is completed
     *
     */
    FBDEV_HW_CMD_IO_PQE_FW_LOAD_DONE,

    /* read vsync latency. return data will be placed at gen[0]
     * return 60 if 50Hz or 60Hz, 120 if 100Hz or 120Hz
     */
    FBDEV_HW_CMD_RD_VSYNC_CLK,

    /* read the current OSD output window size */
    FBDEV_HW_CMD_RD_DISP_SIZE,

    /* read the current OSD resolution per each logical layer
     * data.gen[0] = fb_dev_id
     * data.gen[1] = 0(not supported) 1(ARGB), 2(AFBC)
     * data.gen[2] = 0(default), 1(single buffer), 2(double buffer), ...
     */
    FBDEV_HW_CMD_RD_POSD_MAX_RES_CAPS,

    /* read AFBC capability
     *
     * data.gen[0] = version (0x10=AFBC1.0, 0x11=AFBC1.1, 0x20=AFRC)
     */
#define FBDEV_HW_AFBC_VER_NONE  0x00
#define FBDEV_HW_AFBC_VER_1_0   0x10
#define FBDEV_HW_AFBC_VER_1_1   0x11
#define FBDEV_HW_AFBC_VER_AFRC  0x20
    FBDEV_HW_CMD_RD_AFBC_CAPS,

    /* notify PM command to chip kdriver with no argument */
    FBDEV_HW_CMD_WR_PM_PREPARE_FREEZE,
    FBDEV_HW_CMD_WR_PM_PREPARE_THAW,
    FBDEV_HW_CMD_WR_PM_PREPARE_SUSPEND,
    FBDEV_HW_CMD_WR_PM_PREPARE_RESTORE,
    FBDEV_HW_CMD_WR_PM_PREPARE_RESUME,
    FBDEV_HW_CMD_WR_PM_COMPLETE,

    /* lazy fb(0) init */
    FBDEV_HW_CMD_WR_USER_INITCALL_PREPARE,
    FBDEV_HW_CMD_WR_USER_INITCALL_COMPLETE,

    /* direct render request to external renderer */
    FBDEV_HW_CMD_RD_EXTERNAL_RENDERER_INFO,
    FBDEV_HW_CMD_WR_EXTERNAL_RENDERER_REQUEST_IMAGE,

    /* data.gen[0] = fb_dev_id;
     * data.gen[1] = LX_MAKE_RES(x,y);
     * data.gen[2] = LX_MAKE_RES(w,h);
     */
    FBDEV_HW_CMD_WR_EXTERNAL_RENDERER_CONFIGURE_CROP_REGION,

    /* request automatic OSD sharpness gain control using some misc information
     * data.gen[0] = fb_dev_id;
     * data.gen[1] = 0: off,  1:HD,  2:FHD,  3;UHD
     *
     * see http://clm.lge.com/issue/browse/SICDTV-8781?focusedCommentId=2605561&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-2605561
     */
    FBDEV_HW_CMD_WR_OSD_SHP_AUTO_CONFIG,

    /* request global alpha change
     * data.gen[0] = fb_dev_id;
     * data.gen[1] = on/off
     * data.gen[2] = galpha
     */
    FBDEV_HW_CMND_SET_GL_ALPHA,

    /* request PM runtime action
     * data.gen[0] = pqepm action command
     *
     * see http://collab.lge.com/main/pages/viewpage.action?pageId=1285711712
     */
    FBDEV_HW_CMD_WR_PQE_PM_RUNTIME_ACTION,
}
FBDEV_HW_CMD_T;

/** HW specific PROC handler definition
 *
 */
typedef enum
{
    FBDEV_HW_PROC_ID_DETAIL_INFO,
    FBDEV_HW_PROC_ID_OSD_HDR,
    FBDEV_HW_PROC_ID_REG_DUMP,          /* dump more HW registers */
}
FBDEV_HW_PROC_ID_T;

/** chip depdendent data & handler definition -> hardware context
 *
 */
typedef struct
{
    void*                       chip_priv_ctx;  /* chip dependent ctx */

    struct
    {
        LX_FBDEV_TRID_CTRL_T    trid_ctrl;
    }
    fb[LX_FBDEV_ID_MAX];

    LX_FBDEV_CFG_T* (*GetCfg)(void);

    int (*InitHW)(void);
    int (*ShutdownHW)(void);
    int (*RunSuspend)(void);
    int (*RunResume)(void);

    int (*ExecHWCommand)(FBDEV_HW_CMD_T cmd, FBDEV_HW_CMD_DATA_T* cmd_data);

    int (*SetOSDEnable)(int layer, int enable);
    int (*GetOSDEnable)(int layer);

    int (*InitOSDLayer)(int layer);
    int (*WriteOSDHeader)(struct scanvas*  pstCanvas);

    int (*GetZList)(LX_FBDEV_ZLIST_T* zList);
    int (*SetZList)(LX_FBDEV_ZLIST_T* zList);

    int (*WriteOSDEndian)(int layer, ENDIAN_INFORM_T* endian);
    int (*WriteOSDCSC)(int layer, CSC_INFORM_T* csc);

    int (*GetInterruptStatus)(INTERRUPT_INFORM_T intr);
    int (*SetInterruptClear)(INTERRUPT_INFORM_T intr);
    int (*SetInterruptEnable)(INTERRUPT_INFORM_T intr, int enable);

    int (*SetViewCtrl)(LX_FBDEV_VIEW_CTRL_T* ctrl);
    int (*SetConnCtrl)(LX_FBDEV_CONN_CTRL_T* pConnCtrl);

    void (*CreateProc)(struct proc_dir_entry* parent);
    void (*ProcHandler)(FBDEV_HW_PROC_ID_T proc_id, struct seq_file* m, void* data);
}
FBDEV_HW_CTX_T;

/*----------------------------------------------------------------------------------------
    Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int FBDEV_InitHardware(void);
int FBDEV_ExitHardware(void);

int FBDEV_RunResume(void);
int FBDEV_RunSuspend(void);
int FBDEV_SetOSDEnable(int layer, int enable);
int FBDEV_GetOSDEnable(int layer);

int FBDEV_ExecHWCommand(FBDEV_HW_CMD_T cmd, FBDEV_HW_CMD_DATA_T* data);

int FBDEV_InitOSDLayer(int layer);

int FBDEV_WriteOSDHeader(struct scanvas*  pstCanvas);

int FBDEV_GetZList(LX_FBDEV_ZLIST_T* zList);
int FBDEV_SetZList(LX_FBDEV_ZLIST_T* zList);
int FBDEV_SetVideoMixerCtrl(LX_FBDEV_VIDEO_MIXER_CTRL_T* ctrl);

int FBDEV_SetViewCtrl(LX_FBDEV_VIEW_CTRL_T* ctrl);
int FBDEV_SetConnCtrl(LX_FBDEV_CONN_CTRL_T* ctrl);
int FBDEV_SetTridCtrl(int layer, LX_FBDEV_TRID_CTRL_T* ctrl);
int FBDEV_SetPivotCtrl(LX_FBDEV_PIVOT_CTRL_T* ctrl);

int FBDEV_WriteOSDEndian(int layer, ENDIAN_INFORM_T* endian);
int FBDEV_WriteOSDCSC(int layer, CSC_INFORM_T* csc);
int FBDEV_GetInterruptStatus(INTERRUPT_INFORM_T intr);
int FBDEV_SetInterruptClear(INTERRUPT_INFORM_T intr);
int FBDEV_SetInterruptEnable(INTERRUPT_INFORM_T intr, int enable);
int FBDEV_DownloadPalette(unsigned int addr, unsigned int size, void* data);


/** get the right OSD pixel format value based on bits_per_pixel
 *
 *  @note current FB always assume ARGB pixel format
 */
UINT8   FBDEV_GetOSDPxlFmt(int bits_per_pixel);

/** get the rigth OSD pixel depth value based on bits_per_pixel
 *
 *  @note current FB always assume ARGB pixel format
 */
UINT8   FBDEV_GetOSDPxlDepth(int bits_per_pixel);

/** get OSD HW context
 *  @note use FBDEV_GET_HW_CTX() rater than global variable, because I will remove global variable soon.
 */
#define FBDEV_GET_HW_CTX()      &g_fbdev_hw_ctx
extern  FBDEV_HW_CTX_T          g_fbdev_hw_ctx;

#define FBDEV_GET_HW_IO_CFG()   g_fbdev_hwio_cfg
extern  FBDEV_HW_IO_CFG_T*      g_fbdev_hwio_cfg;       /** FBDEV register I/O context */

/*----------------------------------------------------------------------------------------
    Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

