/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2013 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.
*/


/** @file
 *
 *	main driver implementation for de device.
 *	de device will teach you how to make device driver with new platform.
 *
 *	author
 *	version
 *	date
 *	note
 *
 *	@addtogroup
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/version.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include "linux/v4l2-ext/v4l2-ext-renderer.h"

#include "os_util.h"
#include "base_device.h"
#include "de_ver_def.h"
#include "de_def.h"
#include "de_kapi.h"
#include "de_io.h"
#include "de_hal.h"
#include "v4l2_vsc_event.h"
#include "de_test_util_o26.h"

#include "be_kapi.h"
#include "../../../../be/be_def.h"
#include "../../../../be/frc/frc_hal.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
struct de_test_util_o26_reg {
    UINT32 is_map;

    struct {
        UINT32 addr;
        volatile unsigned int *phy;
        union {
            UINT32 udata32;
            struct {						//0xCC4E0244 RW 0x0000_0000
            UINT32 pattern_type                     :3;	//(2:0,RW,0x00) //type of pattern	000 := bypass	001  = one color pattern	010  = horizontal color bar pattern 	011  = vertical color bar pattern	(Note! the first pixel's color of vertical line is different)	100  = cross hatch pattern	101  = moving horizontal color bar pattern	110  = moving vertical color bar pattern	111  = moving cross hatch pattern
            UINT32 pattern_csc                      :1;	//(3,RW,0x00) //0 := Y/Cb/Cr color pattern gen	1  = G/B/R color pattern gen
            UINT32 pattern_detail                   :4;	//(7:4,RW,0x00) //when pattern_type is 001	0000  = white	0001  = yellow	0010  = cyan	0011  = green	0100  = magenta	0101  = red	0110 := blue	0111  = black	1000  = horizontal gradation	1001  = vertical gradation	1010  = color gradation	1011  = Y/C gradation	1100  = black and white for deinter test	when pattern_type is 010 or 101	0000  = 2 pixel width	0001  = 4 pixel width	0010  = 8 pixel width	0011  = 16 pixel width	0100  = 32 pixel width	0101  = 64 pixel width	0110 := 128 pixel width	when pattern_type is 011 or 110	0000  = 1 line height	0001  = 2 line height	0010  = 4 line height	0011  = 8 line height	0100  = 16 line height	0101  = 32 line height	0110 := 64 line height
            UINT32 resvd0                           :24;
            };
        };
     } misc_ctrl;//REG_CVI_A_MISC_CTRL_T

    struct {
        UINT32 addr;
        volatile unsigned int *phy;
        union {
            UINT32 udata32;
            struct {						//0xCC230880 RW 0x0000_FFFF
            UINT32 r_pxl_rd_dbg_rcr                 :8;	//(7:0,RW,0xFF) //
            UINT32 r_pxl_rd_dbg_bcb                 :8;	//(15:8,RW,0xFF) //
            UINT32 r_pxl_rd_dbg_gyy                 :8;	//(23:16,RW,0x00) //
            UINT32 r_pxl_rd_mark_en                 :1;	//(24:24,RW,0x0) //
            UINT32 resvd0                           :3;
            UINT32 r_pxl_rd_sel                     :1;	//(28:28,RW,0x0) //0: Input RGB Pixel / 1 : Output RGB Pixel
            UINT32 resvd1                           :3;
            };
        };
     } hdr_pxl_rd_ctrl0;//REG_HDR10_E_HDR_PXL_RD_CTRL0_T

    struct {
        UINT32 addr;
        volatile unsigned int *phy;
        union {
            UINT32 udata32;
            struct {						//0xCC230884 RW 0x0000_0000
            UINT32 r_pxl_rd_pos_x                   :13;	//(12:0,RW,0x0) //
            UINT32 resvd0                           :3;
            UINT32 r_pxl_rd_pos_y                   :13;	//(28:16,RW,0x0) //
            UINT32 resvd1                           :3;
            };
        };
    } hdr_pxl_rd_ctrl1;//REG_HDR10_E_HDR_PXL_RD_CTRL1_T

    struct {
        UINT32 addr;
        volatile unsigned int *phy;
        union {
            UINT32 udata32;
            struct {						//0xCC230888 RO 0x0000_0000
            UINT32 pxl_read_rcr                     :12;	//(11:0,RO,0x00) //
            UINT32 resvd0                           :4;
            UINT32 pxl_read_bcb                     :12;	//(27:16,RO,0x00) //
            UINT32 resvd1                           :4;
            };
        };
     } hdr_pxl_rd_data0;//REG_HDR10_E_HDR_PXL_RD_DATA0_T

    struct {
        UINT32 addr;
        volatile unsigned int *phy;
        union {
            UINT32 udata32;
            struct {						//0xCC23088C RO 0x0000_0000
            UINT32 pxl_read_gyy                     :12;	//(11:0,RO,0x00) //
            UINT32 resvd                            :20;
            };
        };
     } hdr_pxl_rd_data1;//REG_HDR10_E_HDR_PXL_RD_DATA1_T

    struct {
        UINT32 addr;
        volatile unsigned int *phy;
        union {
            UINT32 udata32;
            struct {						//0xCC900540 RW 0x0000_0000
            UINT32 rp_v_pos                         :12;	//(11:0,RW,0x00) //vertical pixel position
            UINT32 resvd0                           :4;
            UINT32 rp_h_pos                         :12;	//(27:16,RW,0x00) //horizontal pixel position
            UINT32 resvd1                           :4;
            };
        };
     } ad_rp_hv_pos;//REG_LED_AD_RP_HV_POS_T

    struct {
        UINT32 addr;
        volatile unsigned int *phy;
        union {
            UINT32 udata32;
            struct {						//0xCC900548 RO 0x0000_0000
            UINT32 rd_pixel_r                       :14;	//(13:0,RO,0x0) //R value for a pixel
            UINT32 resvd                            :18;
            };
        };
     } ad_rp_r_value;//REG_LED_AD_RP_R_VALUE_T

    struct {
        UINT32 addr;
        volatile unsigned int *phy;
        union {
            UINT32 udata32;
            struct {						//0xCC90054C RO 0x0000_0000
            UINT32 rd_pixel_g                       :14;	//(13:0,RO,0x0) //G value for a pixel
            UINT32 resvd                            :18;
            };
        };
     } ad_rp_g_value;//REG_LED_AD_RP_G_VALUE_T

    struct {
        UINT32 addr;
        volatile unsigned int *phy;
        union {
            UINT32 udata32;
            struct {						//0xCC900550 RO 0x0000_0000
            UINT32 rd_pixel_b                       :14;	//(13:0,RO,0x0) //B value for a pixel
            UINT32 resvd                            :18;
            };
        };
     } ad_rp_b_value;//REG_LED_AD_RP_B_VALUE_T
};

struct de_test_util_o26_pat_cvi {
    char *name;
    UINT32 type;//0:off,1:full
    UINT32 csc;//0:yc,1:rgb
    UINT32 detail;//0:white,3:green,5:red,6:blue,7:black
    UINT32 min_r;//10b
    UINT32 max_r;//10b
    UINT32 min_g;//10b
    UINT32 max_g;//10b
    UINT32 min_b;//10b
    UINT32 max_b;//10b
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int _de_test_util_o26_map(void);
static int _de_test_util_o26_unmap(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static struct de_test_util_o26_reg _g_de_test_util_o26_reg = {.is_map=0};

static struct de_test_util_o26_pat_cvi _g_de_test_util_o26_pat_cvi[] = {
    {.name="white(rgb)",  .type=1,.csc=1,.detail=0,.min_r=940,.max_r=1023,.min_g=940,.max_g=1023,.min_b=940,.max_b=1023},
    {.name="green(rgb)",  .type=1,.csc=1,.detail=3,.min_r=0,  .max_r=64,  .min_g=940,.max_g=1023,.min_b=0,  .max_b=64  },
    {.name="red(rgb)",    .type=1,.csc=1,.detail=5,.min_r=940,.max_r=1023,.min_g=0,  .max_g=64,  .min_b=0,  .max_b=64  },
    {.name="blue(rgb)",   .type=1,.csc=1,.detail=6,.min_r=0,  .max_r=64,  .min_g=0,  .max_g=64,  .min_b=940,.max_b=1023},
    {.name="black(rgb)",  .type=1,.csc=1,.detail=7,.min_r=0,  .max_r=64,  .min_g=0,  .max_g=64,  .min_b=0,  .max_b=64  },
    {.name="white(yc)",   .type=1,.csc=0,.detail=0,.min_r=768,.max_r=1023,.min_g=768,.max_g=1023,.min_b=768,.max_b=1023},
    {.name="green(yc)",   .type=1,.csc=0,.detail=3,.min_r=0,  .max_r=256, .min_g=768,.max_g=1023,.min_b=0,  .max_b=256 },
    {.name="red(yc)",     .type=1,.csc=0,.detail=5,.min_r=768,.max_r=1023,.min_g=0,  .max_g=256, .min_b=0,  .max_b=256 },
    {.name="blue(yc)",    .type=1,.csc=0,.detail=6,.min_r=0,  .max_r=256, .min_g=0,  .max_g=256, .min_b=768,.max_b=1023},
    {.name="black(yc)",   .type=1,.csc=0,.detail=7,.min_r=0,  .max_r=256, .min_g=0,  .max_g=256, .min_b=0,  .max_b=256 },
    {.name="red(rgb)_cap",.type=1,.csc=1,.detail=5,.min_r=999,.max_r=1023,.min_g=0,  .max_g=56,  .min_b=0,  .max_b=48  },
    {.name=NULL},
};

static int _g_de_test_util_o26_ready = 0;

/*========================================================================================
	Implementation Group
========================================================================================*/
int de_test_util_o26_input_open(char *src_name,char *src_size,char *out_size)
{
    UINT32 mute,port,s_id,o_id;
    struct v4l2_ext_vsc_connect_info input;
    struct v4l2_ext_vsc_win_region win_info;
    struct v4l2_ext_vsc_orbit_window orbit_w;
    struct v4l2_ext_vsc_orbit_move orbit_m;
    UINT32 win_w[2] = {3840,1920};
    UINT32 win_h[2] = {2160,1080};

    if (!src_name)  {DE_ERROR("src_name null\n");return -1;}
    if (!src_size)  {DE_ERROR("src_size null\n");return -1;}
    if (!out_size)  {DE_ERROR("out_size null\n");return -1;}

    if (!_g_de_test_util_o26_ready) {
        return DE_TEST_NOT_READY;
    }

    memset(&input,0,sizeof(input));
    if (0 != vsc_set_input(1,0,&input)) {DE_ERROR("vsc_set_input(%d) err\n",input.in.src);return -1;}

    msleep(100);

    input.out = V4L2_EXT_VSC_DEST_DISPLAY;
    input.in.src = V4L2_EXT_VSC_INPUT_SRC_VDEC;
    if (!strncmp(src_name,"hdmi",strlen("hdmi")))
    {
        port = 0;
        if (!strncmp(src_name,"hdmi1",strlen("hdmi1")))         port = 1;
        else if (!strncmp(src_name,"hdmi2",strlen("hdmi2")))    port = 2;
        else if (!strncmp(src_name,"hdmi3",strlen("hdmi3")))    port = 3;

        input.in.src = V4L2_EXT_VSC_INPUT_SRC_HDMI;
        input.in.index = port;
        input.in.attr = port;
    }

    if (0 != vsc_set_input(1,0,&input)) {DE_ERROR("vsc_set_input(%s) err\n",src_name);return -1;}

    msleep(100);

    memset(&win_info, 0, sizeof(win_info));
    s_id = 0;
    if (!strncmp(src_size,"2k",strlen("2k")))   s_id = 1;
    o_id = 0;
    if (!strncmp(out_size,"2k",strlen("2k")))   o_id = 1;

    win_info.in.res.w = win_w[s_id];
    win_info.in.res.h = win_h[s_id];
    win_info.in.crop.w = win_w[s_id];
    win_info.in.crop.h = win_h[s_id];
    win_info.out.w = win_w[o_id];
    win_info.out.h = win_h[o_id];
    if (0 != vsc_set_win_info(1,0,1,&win_info)) {DE_ERROR("vsc_set_win_info(%s)(%s) err\n",src_size,out_size);return -1;}

    memset(&orbit_w, 0, sizeof(orbit_w));
    orbit_w.video_input.w = win_info.in.crop.w;
    orbit_w.video_input.h = win_info.in.crop.h;
    orbit_w.video_output.w = win_info.out.w;
    orbit_w.video_output.h = win_info.out.h;
    if (0 != vsc_set_orbit_window(1,0,&orbit_w)) {DE_ERROR("vsc_set_orbit_window(%s)(%s) err\n",src_size,out_size);return -1;}

    memset(&orbit_m, 0, sizeof(orbit_m));
    orbit_m.video_input.w = win_info.out.w;
    orbit_m.video_input.h = win_info.out.h;
    orbit_m.video_output.w = win_info.out.w;
    orbit_m.video_output.h = win_info.out.h;
    if (0 != vsc_set_orbit_move(1,0,&orbit_m)) {DE_ERROR("vsc_set_orbit_move(%s)(%s) err\n",src_size,out_size);return -1;}

    mute = 0;
    if (0 != vsc_set_mute(1,0,&mute)) {DE_ERROR("vsc_set_mute(%d) err\n",mute);return -1;}
    msleep(100);

    #ifdef INCLUDE_KDRV_BE
    do {
        LX_BE_FRC_CMD_T cmd = {.str="psync 4 0 2 0 0"};
        if (input.in.src != V4L2_EXT_VSC_INPUT_SRC_HDMI)   break;
        DE_NOTI("cmd (%s)\n",cmd.str);
        if (0 != BE_FRC_HAL_RunCommand(&cmd)) {DE_ERROR("RunCommand(%s) err\n",cmd.str);return -1;}
    } while (0);
    #endif
    msleep(100);

    #ifdef INCLUDE_KDRV_BE
    do {
        LX_BE_FRC_CMD_T cmd = {.str="osd 0"};
        DE_NOTI("cmd (%s)\n",cmd.str);
        if (0 != BE_FRC_HAL_RunCommand(&cmd)) {DE_ERROR("RunCommand(%s) err\n",cmd.str);return -1;}
    } while (0);
    #endif
    msleep(100);

    //DE_NOTI("done\n");
    return 0;
}

int de_test_util_o26_input_close(void)
{
    struct v4l2_ext_vsc_connect_info input;

    #ifdef INCLUDE_KDRV_BE
    do {
        LX_BE_FRC_CMD_T cmd = {.str="osd 1"};
        DE_NOTI("cmd (%s)\n",cmd.str);
        if (0 != BE_FRC_HAL_RunCommand(&cmd)) {DE_ERROR("RunCommand(%s) err\n",cmd.str);return -1;}
    } while (0);
    #endif
    msleep(100);

    #ifdef INCLUDE_KDRV_BE
    do {
        LX_BE_FRC_CMD_T cmd = {.str="psync 0"};
        DE_NOTI("cmd (%s)\n",cmd.str);
        if (0 != BE_FRC_HAL_RunCommand(&cmd)) {DE_ERROR("RunCommand(%s) err\n",cmd.str);return -1;}
    } while (0);
    #endif
    msleep(100);

    memset(&input,0,sizeof(input));
    if (0 != vsc_set_input(1,0,&input)) {DE_ERROR("vsc_set_input(%d) err\n",input.in.src);return -1;}

    //DE_NOTI("done\n");
    return 0;
}

int de_test_util_o26_cvi_pat_on(char *name)
{
    struct de_test_util_o26_reg *p_reg = &_g_de_test_util_o26_reg;
    struct de_test_util_o26_pat_cvi *p_cvi = _g_de_test_util_o26_pat_cvi;

    if (!name)
    {
        DE_ERROR("name null\n");
        return -1;
    }

    while (p_cvi->name)
    {
        if (!strncasecmp(name,p_cvi->name,strlen(p_cvi->name)))
        {
            _de_test_util_o26_map();

            if (p_reg->is_map == 1)
            {
                #ifdef INCLUDE_KDRV_BE
                do {
                    LX_BE_FRC_CMD_T cmd;
                    snprintf(cmd.str,12,"cscinfo 2 %d",(p_cvi->csc == 0)? 3:4);//0:YCbCr,1:RGB
                    DE_NOTI("cmd (%s)\n",cmd.str);
                    if (0 != BE_FRC_HAL_RunCommand(&cmd)) {DE_ERROR("RunCommand(%s) err\n",cmd.str);return -1;}
                } while(0);
                #endif

                p_reg->misc_ctrl.udata32 = 0;
                p_reg->misc_ctrl.pattern_csc = p_cvi->csc;
                p_reg->misc_ctrl.pattern_type = p_cvi->type;
                p_reg->misc_ctrl.pattern_detail = p_cvi->detail;
                *p_reg->misc_ctrl.phy = p_reg->misc_ctrl.udata32;
                DE_NOTI("%-16s : pat csc,type,detail : %d, %d, %d\n",name,p_cvi->csc,p_cvi->type,p_cvi->detail);
            }
            break;
        }
        p_cvi++;
    }

    if (!p_cvi->name)
    {
        DE_ERROR("%-16s : unknown\n",name);
        return -1;
    }

    return 0;
}

int de_test_util_o26_cvi_pat_off(void)
{
    struct de_test_util_o26_reg *p_reg = &_g_de_test_util_o26_reg;

    if (p_reg->is_map == 1)
    {
        #ifdef INCLUDE_KDRV_BE
        do {
            LX_BE_FRC_CMD_T cmd = {.str="cscinfo 2 0"};
            DE_NOTI("cmd (%s)\n",cmd.str);
            if (0 != BE_FRC_HAL_RunCommand(&cmd)) {DE_ERROR("RunCommand(%s) err\n",cmd.str);return -1;}
        } while (0);
        #endif

        *p_reg->misc_ctrl.phy = 0x0;
    }

    _de_test_util_o26_unmap();

    return 0;
}

int de_test_util_o26_check_cvi_i_pixel(char *name, UINT32 pos_x, UINT32 pos_y)
{
    int ret = 0;
    int i;
    UINT32 pxl_rd_sel = 0;//default input
    struct de_test_util_o26_pat_cvi *p_cvi = _g_de_test_util_o26_pat_cvi;
    struct de_test_util_o26_reg *p_reg = &_g_de_test_util_o26_reg;

    if (!name)
    {
        DE_ERROR("name null\n");
        return -1;
    }

    if (p_reg->is_map == 0)
    {
        DE_ERROR("p_reg not ready\n");
        return -1;
    }

    if (strstr(name,"hdr_o"))
    {
        pxl_rd_sel = 1;
    }

    /* set rd pos */
    p_reg->hdr_pxl_rd_ctrl0.r_pxl_rd_sel = pxl_rd_sel;
    *p_reg->hdr_pxl_rd_ctrl0.phy = p_reg->hdr_pxl_rd_ctrl0.udata32;

    p_reg->hdr_pxl_rd_ctrl1.r_pxl_rd_pos_x = pos_x;
    p_reg->hdr_pxl_rd_ctrl1.r_pxl_rd_pos_y = pos_y;
    *p_reg->hdr_pxl_rd_ctrl1.phy = p_reg->hdr_pxl_rd_ctrl1.udata32;

    while (p_cvi->name)
    {
        if (!strncasecmp(name,p_cvi->name,strlen(p_cvi->name)))
        {
            for (i=0; i<5; i++)
            {
                msleep(100);

                p_reg->hdr_pxl_rd_data0.udata32 = *((UINT32*)p_reg->hdr_pxl_rd_data0.phy);
                p_reg->hdr_pxl_rd_data1.udata32 = *((UINT32*)p_reg->hdr_pxl_rd_data1.phy);

                ret = (p_reg->hdr_pxl_rd_data0.pxl_read_rcr >= p_cvi->min_r && p_reg->hdr_pxl_rd_data0.pxl_read_rcr <= p_cvi->max_r && \
                    p_reg->hdr_pxl_rd_data1.pxl_read_gyy >= p_cvi->min_g && p_reg->hdr_pxl_rd_data1.pxl_read_gyy <= p_cvi->max_g && \
                    p_reg->hdr_pxl_rd_data0.pxl_read_bcb >= p_cvi->min_b && p_reg->hdr_pxl_rd_data0.pxl_read_bcb <= p_cvi->max_b)? (0):(-1);

                DE_NOTI("%-16s : r,g,b(10b) : (%4d ~ %4d) (%4d ~ %4d) (%4d ~ %4d)\n",name,p_cvi->min_r,p_cvi->max_r,p_cvi->min_g,p_cvi->max_g,p_cvi->min_b,p_cvi->max_b);
                DE_NOTI("%-16s : r,g,b(10b) : %4d, %4d, %4d -> %s (retry:%d)\n",name,p_reg->hdr_pxl_rd_data0.pxl_read_rcr,p_reg->hdr_pxl_rd_data1.pxl_read_gyy,p_reg->hdr_pxl_rd_data0.pxl_read_bcb,(ret==0)? "ok":"ng",i);

                if (ret == 0)   break;
            }

            if (ret < 0)
            {
                DE_ERROR("%-16s : r,g,b(10b) : %4d, %4d, %4d -> %s (retry:%d)\n",name,p_reg->hdr_pxl_rd_data0.pxl_read_rcr,p_reg->hdr_pxl_rd_data1.pxl_read_gyy,p_reg->hdr_pxl_rd_data0.pxl_read_bcb,"ng",i);
            }
            break;
        }
        p_cvi++;
    }

    if (!p_cvi->name)
    {
        DE_ERROR("%-16s : not support\n",name);
        return -1;
    }

    return ret;
}

int de_test_util_o26_check_cvi_o_pixel(char *name, UINT32 pos_x, UINT32 pos_y)
{
    int ret = 0;
    int i;
    struct de_test_util_o26_pat_cvi *p_cvi = _g_de_test_util_o26_pat_cvi;
    struct de_test_util_o26_reg *p_reg = &_g_de_test_util_o26_reg;

    if (!name)
    {
        DE_ERROR("name null\n");
        return -1;
    }

    if (p_reg->is_map == 0)
    {
        DE_ERROR("p_reg not ready\n");
        return -1;
    }

    /* set rd pos */
    p_reg->ad_rp_hv_pos.rp_h_pos = pos_x;
    p_reg->ad_rp_hv_pos.rp_v_pos = pos_y;
    *p_reg->ad_rp_hv_pos.phy = p_reg->ad_rp_hv_pos.udata32;

    while (p_cvi->name)
    {
        if (!strncasecmp(name,p_cvi->name,strlen(p_cvi->name)))
        {
            for (i=0; i<5; i++)
            {
                msleep(100);

                p_reg->ad_rp_r_value.udata32 = *((UINT32*)p_reg->ad_rp_r_value.phy);
                p_reg->ad_rp_g_value.udata32 = *((UINT32*)p_reg->ad_rp_g_value.phy);
                p_reg->ad_rp_b_value.udata32 = *((UINT32*)p_reg->ad_rp_b_value.phy);

                p_reg->ad_rp_r_value.rd_pixel_r >>= 2;
                p_reg->ad_rp_g_value.rd_pixel_g >>= 2;
                p_reg->ad_rp_b_value.rd_pixel_b >>= 2;

                ret = (p_reg->ad_rp_r_value.rd_pixel_r >= p_cvi->min_r && p_reg->ad_rp_r_value.rd_pixel_r <= p_cvi->max_r && \
                    p_reg->ad_rp_g_value.rd_pixel_g >= p_cvi->min_g && p_reg->ad_rp_g_value.rd_pixel_g <= p_cvi->max_g && \
                    p_reg->ad_rp_b_value.rd_pixel_b >= p_cvi->min_b && p_reg->ad_rp_b_value.rd_pixel_b <= p_cvi->max_b)? (0):(-1);

                DE_NOTI("%-16s : r,g,b(10b) : (%4d ~ %4d) (%4d ~ %4d) (%4d ~ %4d)\n",name,p_cvi->min_r,p_cvi->max_r,p_cvi->min_g,p_cvi->max_g,p_cvi->min_b,p_cvi->max_b);
                DE_NOTI("%-16s : r,g,b(10b) : %4d, %4d, %4d -> %s (retry:%d)\n",name,p_reg->ad_rp_r_value.rd_pixel_r,p_reg->ad_rp_g_value.rd_pixel_g,p_reg->ad_rp_b_value.rd_pixel_b,(ret==0)? "ok":"ng",i);

                if (ret == 0)   break;
            }

            if (ret < 0)
            {
                DE_ERROR("%-16s : r,g,b(10b) : %4d, %4d, %4d -> %s (retry:%d)\n",name,p_reg->ad_rp_r_value.rd_pixel_r,p_reg->ad_rp_g_value.rd_pixel_g,p_reg->ad_rp_b_value.rd_pixel_b,"ng",i);
            }
            break;
        }
        p_cvi++;
    }

    if (!p_cvi->name)
    {
        DE_ERROR("%-16s : not support\n",name);
        return -1;
    }

    return ret;
}

static int _de_test_util_o26_map(void)
{
    struct de_test_util_o26_reg *p_reg = &_g_de_test_util_o26_reg;

    if (p_reg->is_map == 1)
    {
        DE_NOTI("already map\n");
        return 0;
    }

    p_reg->misc_ctrl.addr        = 0xCC4E0244;//REG_CVI_A_MISC_CTRL_T
    p_reg->hdr_pxl_rd_ctrl0.addr = 0xCC230880;//REG_HDR10_E_HDR_PXL_RD_CTRL0_T
    p_reg->hdr_pxl_rd_ctrl1.addr = 0xCC230884;//REG_HDR10_E_HDR_PXL_RD_CTRL1_T
    p_reg->hdr_pxl_rd_data0.addr = 0xCC230888;//REG_HDR10_E_HDR_PXL_RD_DATA0_T
    p_reg->hdr_pxl_rd_data1.addr = 0xCC23088C;//REG_HDR10_E_HDR_PXL_RD_DATA1_T
    p_reg->ad_rp_hv_pos.addr     = 0xCC900540;//REG_LED_AD_RP_HV_POS_T
    p_reg->ad_rp_r_value.addr    = 0xCC900548;//REG_LED_AD_RP_R_VALUE_T
    p_reg->ad_rp_g_value.addr    = 0xCC90054C;//REG_LED_AD_RP_G_VALUE_T
    p_reg->ad_rp_b_value.addr    = 0xCC900550;//REG_LED_AD_RP_B_VALUE_T

    p_reg->misc_ctrl.phy = (volatile unsigned int *)ioremap(p_reg->misc_ctrl.addr,sizeof(unsigned int));
    if (!p_reg->misc_ctrl.phy)    {DE_ERROR("ioremap err (misc_ctrl)\n");return -1;}

    p_reg->hdr_pxl_rd_ctrl0.phy = (volatile unsigned int *)ioremap(p_reg->hdr_pxl_rd_ctrl0.addr,sizeof(unsigned int));
    if (!p_reg->hdr_pxl_rd_ctrl0.phy)    {DE_ERROR("ioremap err (hdr_pxl_rd_ctrl0)\n");return -1;}

    p_reg->hdr_pxl_rd_ctrl1.phy = (volatile unsigned int *)ioremap(p_reg->hdr_pxl_rd_ctrl1.addr,sizeof(unsigned int));
    if (!p_reg->hdr_pxl_rd_ctrl1.phy)    {DE_ERROR("ioremap err (hdr_pxl_rd_ctrl1)\n");return -1;}

    p_reg->hdr_pxl_rd_data0.phy = (volatile unsigned int *)ioremap(p_reg->hdr_pxl_rd_data0.addr,sizeof(unsigned int));
    if (!p_reg->hdr_pxl_rd_data0.phy)    {DE_ERROR("ioremap err (hdr_pxl_rd_data0)\n");return -1;}

    p_reg->hdr_pxl_rd_data1.phy = (volatile unsigned int *)ioremap(p_reg->hdr_pxl_rd_data1.addr,sizeof(unsigned int));
    if (!p_reg->hdr_pxl_rd_data1.phy)    {DE_ERROR("ioremap err (hdr_pxl_rd_data1)\n");return -1;}

    p_reg->ad_rp_hv_pos.phy = (volatile unsigned int *)ioremap(p_reg->ad_rp_hv_pos.addr,sizeof(unsigned int));
    if (!p_reg->ad_rp_hv_pos.phy)    {DE_ERROR("ioremap err (ad_rp_hv_pos)\n");return -1;}

    p_reg->ad_rp_r_value.phy = (volatile unsigned int *)ioremap(p_reg->ad_rp_r_value.addr,sizeof(unsigned int));
    if (!p_reg->ad_rp_r_value.phy)    {DE_ERROR("ioremap err (ad_rp_r_value)\n");return -1;}

    p_reg->ad_rp_g_value.phy = (volatile unsigned int *)ioremap(p_reg->ad_rp_g_value.addr,sizeof(unsigned int));
    if (!p_reg->ad_rp_g_value.phy)    {DE_ERROR("ioremap err (ad_rp_g_value)\n");return -1;}

    p_reg->ad_rp_b_value.phy = (volatile unsigned int *)ioremap(p_reg->ad_rp_b_value.addr,sizeof(unsigned int));
    if (!p_reg->ad_rp_b_value.phy)    {DE_ERROR("ioremap err (ad_rp_b_value)\n");return -1;}

    p_reg->is_map = 1;
    DE_NOTI("done\n");
    return 0;
}

static int _de_test_util_o26_unmap(void)
{
    struct de_test_util_o26_reg *p_reg = &_g_de_test_util_o26_reg;

    if (p_reg->is_map == 0)
    {
        DE_NOTI("already unmap\n");
        return 0;
    }

    if (p_reg->misc_ctrl.phy) iounmap(p_reg->misc_ctrl.phy);
    if (p_reg->hdr_pxl_rd_ctrl0.phy) iounmap(p_reg->hdr_pxl_rd_ctrl0.phy);
    if (p_reg->hdr_pxl_rd_ctrl1.phy) iounmap(p_reg->hdr_pxl_rd_ctrl1.phy);
    if (p_reg->hdr_pxl_rd_data0.phy) iounmap(p_reg->hdr_pxl_rd_data0.phy);
    if (p_reg->hdr_pxl_rd_data1.phy) iounmap(p_reg->hdr_pxl_rd_data1.phy);
    if (p_reg->ad_rp_hv_pos.phy) iounmap(p_reg->ad_rp_hv_pos.phy);
    if (p_reg->ad_rp_r_value.phy) iounmap(p_reg->ad_rp_r_value.phy);
    if (p_reg->ad_rp_g_value.phy) iounmap(p_reg->ad_rp_g_value.phy);
    if (p_reg->ad_rp_b_value.phy) iounmap(p_reg->ad_rp_b_value.phy);

    p_reg->is_map = 0;
    DE_NOTI("done\n");
    return 0;
}
