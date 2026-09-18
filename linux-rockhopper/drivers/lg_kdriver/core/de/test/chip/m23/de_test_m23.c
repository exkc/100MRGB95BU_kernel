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
#include <linux/kthread.h>
#include <linux/freezer.h>
#include <linux/time.h>
#include <linux/delay.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#include <linux/sched/signal.h>
#endif
#include "linux/v4l2-ext/v4l2-ext-renderer.h"
#include "linux/v4l2-ext/v4l2-ext-panel.h"

#include "os_util.h"
#include "base_device.h"
#include "de_ver_def.h"
#include "de_def.h"
#include "de_kapi.h"
#include "de_io.h"
#include "de_hal.h"
#include "v4l2_vsc_event.h"
#include "../../de_test.h"

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
struct de_test_m23_ctx
{
    int state;
    char *name;
    void *handler;
    struct task_struct *task;
    int (*func)(void *ptr);
};

struct de_test_m23_func
{
    char *name;
    int (*func)(void);
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern int v4l2_vsc_getlocalmute(int win);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/
int de_test_m23_handler(struct de_test_handler *ph);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int _de_test_m23_init(void);
static int _de_test_m23_run_unit(void *ptr);
static int _de_test_m23_task_unit(void *ptr);
static int _de_test_m23_check_mcu0(void);
static int _de_test_m23_check_mcu1(void);
static int _de_test_m23_check_hdmi(void);
static int _de_test_m23_check_mvi(void);
static int _de_test_m23_check_capture(void);
static int _de_test_m23_check_gpsdma(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static struct de_test_m23_ctx _g_de_test_m23_ctx[] = {
    {.name="run_test_pqe",.task=NULL,.func=_de_test_m23_run_unit},
    {.name=NULL}
};

static struct de_test_m23_func _g_de_test_m23_func[] = {
    {.name="check_mcu0",    .func=_de_test_m23_check_mcu0},
    {.name="check_mcu1",    .func=_de_test_m23_check_mcu1},
    {.name="check_hdmi",    .func=_de_test_m23_check_hdmi},
    {.name="check_mvi",     .func=_de_test_m23_check_mvi},
    {.name="check_gpsdma", .func=_de_test_m23_check_gpsdma},
    {.name="check_capture", .func=_de_test_m23_check_capture},
    {.name=NULL}
};

/*========================================================================================
	Implementation Group
========================================================================================*/
int de_test_m23_handler(struct de_test_handler *ph)
{
    int ret;
    struct de_test_m23_ctx *p = _g_de_test_m23_ctx;

    if (!ph)
    {
        DE_ERROR("ph null\n");
        return -1;
    }

    if (ph->type == de_test_handler_type_init)
    {
        return _de_test_m23_init();
    }

    while (p->name)
    {
        if (!strncasecmp(ph->str, p->name, strlen(p->name)))
        {
            if (p->func)
            {
                //DE_NOTI("(%s) type(%s) run func\n",p->name,ph->type);
                p->handler = (void *)ph;
                ret = p->func((void *)p);
            }
            break;
        }
        p++;
    }

    if (!p->name)
    {
        DE_ERROR("(%s) not support\n",ph->str);
        return 0;
    }

    return ret;
}

static int _de_test_m23_init(void)
{
    DE_NOTI("init done\n");
    return 0;
}

static int _de_test_m23_run_unit(void *ptr)
{
    LX_DE_TEST_CMD_T *p_cmd;
    struct de_test_handler *p_handler;
    struct de_test_m23_ctx *p_ctx = (struct de_test_m23_ctx *)ptr;

    if (!p_ctx)
    {
        DE_ERROR("p_ctx null\n");
        return -1;
    }

    p_handler = (struct de_test_handler *)p_ctx->handler;
    if (!p_handler)
    {
        DE_ERROR("p_handler null\n");
        return -1;
    }

    p_cmd = (LX_DE_TEST_CMD_T *)p_handler->cmd;
    if (!p_cmd)
    {
        DE_ERROR("p_cmd null\n");
        return -1;
    }

    //DE_NOTI("name (%s) type(%d) str(%s)\n",p_ctx->name,p_handler->type,p_handler->str);
    switch (p_handler->type)
    {
        case de_test_handler_type_start:
            if (p_ctx->task)
            {
                DE_ERROR("(%s) task already start\n",p_ctx->name);
                break;
            }
            p_ctx->state = 1;
            p_ctx->task = kthread_run(_de_test_m23_task_unit,(void *)p_ctx,"%s",p_handler->str);
            if (!p_ctx->task)
            {
                DE_ERROR("(%s) kthread_run err\n",p_ctx->name);
                break;
            }
            break;
        case de_test_handler_type_stop:
            if (!p_ctx->task)
            {
                DE_ERROR("(%s) task already stop\n",p_ctx->name);
                break;
            }
            if (p_ctx->state > 0)//still running
            {
                DE_NOTI("(%s) send stop\n",p_ctx->name);
                send_sig(SIGUSR1,p_ctx->task,0);
                kthread_stop(p_ctx->task);
            }
            p_ctx->task = NULL;
            break;
        case de_test_handler_type_state:
        default:
            break;
    }

    p_cmd->state = p_ctx->state;
    DE_NOTI("(%s) state (%d)\n",p_ctx->name,p_cmd->state);
    return 0;
}

static int _de_test_m23_task_unit(void *ptr)
{
    int ret = 0;
    struct de_test_m23_func *p_func = _g_de_test_m23_func;
    struct de_test_m23_ctx *p_ctx = (struct de_test_m23_ctx *)ptr;

    if (!p_ctx)
    {
        DE_ERROR("p_ctx null\n");
        return 0;
    }

    allow_signal(SIGUSR1);
    while (p_func->name)
    {
        if (kthread_should_stop())  {DE_NOTI("task stop\n");break;}
        msleep_interruptible(100);

        if (p_func->func)
        {
            DE_NOTI("state (%d) name (%s) run\n",p_ctx->state,p_func->name);
            ret = p_func->func();
            if (ret < 0)    {DE_ERROR("(%s) ng\n",p_func->name);break;}
            if (ret == 0)   {DE_NOTI("ok (go to next)\n");p_ctx->state=1;p_func++;}
            if (ret > 0 && p_ctx->state < 100) p_ctx->state++;//time out 10sec
        }
        else
        {
            p_func++;
        }
    }

    p_ctx->state = ret;
    DE_NOTI("state (%d) done\n",p_ctx->state);

    return 0;
}

static int _de_test_m23_check_mcu0(void)
{
    LX_DE_FIRMWARE_INFO_T param;

    if (0 == DE_HAL_IPCisAlive())
    {
        DE_ERROR("ipc is not alive\n");
        return -1;
    }

    memset(&param,0,sizeof(param));
    if (RET_OK != DE_IO_GetFirmwareInfo((unsigned long)(&param),1))
    {
        DE_ERROR("DE_IO_GetFirmwareInfo err\n");
        return -1;
    }

    DE_NOTI("fw ver: %d (%d/%d/%d) (cnt:%d)\n",param.version,param.date.year,param.date.month,param.date.day,param.ipc_count);

    if (param.version == 0)
    {
        DE_ERROR("ver err\n");
        return -1;
    }

    return 0;
}

static int _de_test_m23_check_mcu1(void)
{
    DE_ERROR("not support\n");
    return 0;
}

struct check_hdmi_ctx {
    UINT32 count;

    struct {
        UINT32 addr;
        volatile unsigned int *phy;
        union {
            UINT32 udata32;
            struct {						//0xCC690244 RW 0x0000_0000
            UINT32 pattern_type                     :3;	//(2:0,RW,0x00) //type of pattern	000 := bypass	001  = one color pattern	010  = horizontal color bar pattern 	011  = vertical color bar pattern	(Note! the first pixel's color of vertical line is different)	100  = cross hatch pattern	101  = moving horizontal color bar pattern	110  = moving vertical color bar pattern	111  = moving cross hatch pattern
            UINT32 pattern_csc                      :1;	//(3,RW,0x00) //0 := Y/Cb/Cr color pattern gen	1  = G/B/R color pattern gen
            UINT32 pattern_detail                   :4;	//(7:4,RW,0x00) //when pattern_type is 001	0000  = white	0001  = yellow	0010  = cyan	0011  = green	0100  = magenta	0101  = red	0110 := blue	0111  = black	1000  = horizontal gradation	1001  = vertical gradation	1010  = color gradation	1011  = Y/C gradation	1100  = black and white for deinter test	when pattern_type is 010 or 101	0000  = 2 pixel width	0001  = 4 pixel width	0010  = 8 pixel width	0011  = 16 pixel width	0100  = 32 pixel width	0101  = 64 pixel width	0110 := 128 pixel width	when pattern_type is 011 or 110	0000  = 1 line height	0001  = 2 line height	0010  = 4 line height	0011  = 8 line height	0100  = 16 line height	0101  = 32 line height	0110 := 64 line height
            UINT32 resvd0                           :24;
            };
        };
     } misc_ctrl;

    struct {
        UINT32 addr;
        volatile unsigned int *phy;
        union {
            UINT32 udata32;
            struct {						//0xCC620880 RW 0x0000_FFFF
            UINT32 r_pxl_rd_dbg_rcr                 :8;	//(7:0,RW,0xFF) //
            UINT32 r_pxl_rd_dbg_bcb                 :8;	//(15:8,RW,0xFF) //
            UINT32 r_pxl_rd_dbg_gyy                 :8;	//(23:16,RW,0x00) //
            UINT32 r_pxl_rd_mark_en                 :1;	//(24,RW,0x0) //
            UINT32 resvd0                           :3;
            UINT32 r_pxl_rd_sel                     :1;	//(28,RW,0x0) //0: Input RGB Pixel / 1 : Output RGB Pixel
            UINT32 resvd1                           :3;
            };
        };
     } hdr_pxl_rd_ctrl0;

    struct {
        UINT32 addr;
        volatile unsigned int *phy;
        union {
            UINT32 udata32;
            struct {						//0xCC620884 RW 0x0000_0000
            UINT32 r_pxl_rd_pos_x                   :13;	//(12:0,RW,0x0) //
            UINT32 resvd0                           :3;
            UINT32 r_pxl_rd_pos_y                   :13;	//(28:16,RW,0x0) //
            UINT32 resvd1                           :3;
            };
        };
    } hdr_pxl_rd_ctrl1;

    struct {
        UINT32 addr;
        volatile unsigned int *phy;
        union {
            UINT32 udata32;
            struct {						//0xCC620888 RO 0x0000_0000
            UINT32 pxl_read_rcr                     :10;	//(9:0,RO,0x00) //
            UINT32 pxl_read_bcb                     :10;	//(19:10,RO,0x00) //
            UINT32 pxl_read_gyy                     :10;	//(29:20,RO,0x00) //
            UINT32 resvd                            :2;
            };
        };
     } hdr_pxl_rd_data;

    struct {
        UINT32 addr;
        volatile unsigned int *phy;
        union {
            UINT32 udata32;
            struct {						//0xCC430540 RW 0x0000_0000
            UINT32 rp_v_pos                         :12;	//(11:0,RW,0x00) //vertical pixel position
            UINT32 resvd0                           :4;
            UINT32 rp_h_pos                         :12;	//(27:16,RW,0x00) //horizontal pixel position
            UINT32 resvd1                           :4;
            };
        };
     } ad_rp_hv_pos;

    struct {
        UINT32 addr;
        volatile unsigned int *phy;
        union {
            UINT32 udata32;
            struct {						//0xCC430548 RO 0x0000_0000
            UINT32 rd_pixel_r                       :14;	//(13:0,RO,0x0) //R value for a pixel
            UINT32 resvd                            :18;
            };
        };
     } ad_rp_r_value;

    struct {
        UINT32 addr;
        volatile unsigned int *phy;
        union {
            UINT32 udata32;
            struct {						//0xCC43054C RO 0x0000_0000
            UINT32 rd_pixel_g                       :14;	//(13:0,RO,0x0) //G value for a pixel
            UINT32 resvd                            :18;
            };
        };
     } ad_rp_g_value;

    struct {
        UINT32 addr;
        volatile unsigned int *phy;
        union {
            UINT32 udata32;
            struct {						//0xCC430550 RO 0x0000_0000
            UINT32 rd_pixel_b                       :14;	//(13:0,RO,0x0) //B value for a pixel
            UINT32 resvd                            :18;
            };
        };
     } ad_rp_b_value;
};

static int _de_test_m23_hdmi_map(struct check_hdmi_ctx *p_ctx)
{
    if (!p_ctx)
    {
        DE_ERROR("p_ctx null\n");
        return -1;
    }

    p_ctx->misc_ctrl.addr = 0xCC690244;//REG_CVI_A_MISC_CTRL_T
    p_ctx->hdr_pxl_rd_ctrl0.addr = 0xCC620880;//REG_HDR10_HDR_PXL_RD_CTRL0_T
    p_ctx->hdr_pxl_rd_ctrl1.addr = 0xCC620884;//REG_HDR10_HDR_PXL_RD_CTRL1_T
    p_ctx->hdr_pxl_rd_data.addr = 0xCC620888;//REG_HDR10_HDR_PXL_RD_DATA_T
    p_ctx->ad_rp_hv_pos.addr = 0xCC430540;//REG_LED_AD_RP_HV_POS_T
    p_ctx->ad_rp_r_value.addr = 0xCC430548;//REG_LED_AD_RP_R_VALUE_T
    p_ctx->ad_rp_g_value.addr = 0xCC43054C;//REG_LED_AD_RP_G_VALUE_T
    p_ctx->ad_rp_b_value.addr = 0xCC430550;//REG_LED_AD_RP_B_VALUE_T

    p_ctx->misc_ctrl.phy = (volatile unsigned int *)ioremap(p_ctx->misc_ctrl.addr,sizeof(unsigned int));
    if (!p_ctx->misc_ctrl.phy)    {DE_ERROR("ioremap err (misc_ctrl)\n");return -1;}

    p_ctx->hdr_pxl_rd_ctrl0.phy = (volatile unsigned int *)ioremap(p_ctx->hdr_pxl_rd_ctrl0.addr,sizeof(unsigned int));
    if (!p_ctx->hdr_pxl_rd_ctrl0.phy)    {DE_ERROR("ioremap err (hdr_pxl_rd_ctrl0)\n");return -1;}

    p_ctx->hdr_pxl_rd_ctrl1.phy = (volatile unsigned int *)ioremap(p_ctx->hdr_pxl_rd_ctrl1.addr,sizeof(unsigned int));
    if (!p_ctx->hdr_pxl_rd_ctrl1.phy)    {DE_ERROR("ioremap err (hdr_pxl_rd_ctrl1)\n");return -1;}

    p_ctx->hdr_pxl_rd_data.phy = (volatile unsigned int *)ioremap(p_ctx->hdr_pxl_rd_data.addr,sizeof(unsigned int));
    if (!p_ctx->hdr_pxl_rd_data.phy)    {DE_ERROR("ioremap err (hdr_pxl_rd_data)\n");return -1;}

    p_ctx->ad_rp_hv_pos.phy = (volatile unsigned int *)ioremap(p_ctx->ad_rp_hv_pos.addr,sizeof(unsigned int));
    if (!p_ctx->ad_rp_hv_pos.phy)    {DE_ERROR("ioremap err (ad_rp_hv_pos)\n");return -1;}

    p_ctx->ad_rp_r_value.phy = (volatile unsigned int *)ioremap(p_ctx->ad_rp_r_value.addr,sizeof(unsigned int));
    if (!p_ctx->ad_rp_r_value.phy)    {DE_ERROR("ioremap err (ad_rp_r_value)\n");return -1;}

    p_ctx->ad_rp_g_value.phy = (volatile unsigned int *)ioremap(p_ctx->ad_rp_g_value.addr,sizeof(unsigned int));
    if (!p_ctx->ad_rp_g_value.phy)    {DE_ERROR("ioremap err (ad_rp_g_value)\n");return -1;}

    p_ctx->ad_rp_b_value.phy = (volatile unsigned int *)ioremap(p_ctx->ad_rp_b_value.addr,sizeof(unsigned int));
    if (!p_ctx->ad_rp_b_value.phy)    {DE_ERROR("ioremap err (ad_rp_b_value)\n");return -1;}

    DE_NOTI("done\n");
    return 0;
}

static int _de_test_m23_hdmi_unmap(struct check_hdmi_ctx *p_ctx)
{
    if (!p_ctx)
    {
        DE_ERROR("p_ctx null\n");
        return -1;
    }

    if (p_ctx->misc_ctrl.phy) iounmap(p_ctx->misc_ctrl.phy);
    if (p_ctx->hdr_pxl_rd_ctrl0.phy) iounmap(p_ctx->hdr_pxl_rd_ctrl0.phy);
    if (p_ctx->hdr_pxl_rd_ctrl1.phy) iounmap(p_ctx->hdr_pxl_rd_ctrl1.phy);
    if (p_ctx->hdr_pxl_rd_data.phy) iounmap(p_ctx->hdr_pxl_rd_data.phy);
    if (p_ctx->ad_rp_hv_pos.phy) iounmap(p_ctx->ad_rp_hv_pos.phy);
    if (p_ctx->ad_rp_r_value.phy) iounmap(p_ctx->ad_rp_r_value.phy);

    return 0;
}

static int _de_test_m23_hdmi_open(struct check_hdmi_ctx *p_ctx, UINT32 pos_x, UINT32 pos_y)
{
    UINT32 mute;
    struct v4l2_ext_vsc_win_region info;
    struct v4l2_ext_vsc_connect_info input;

    if (!p_ctx)
    {
        DE_ERROR("p_ctx null\n");
        return -1;
    }

    memset(&input,0,sizeof(input));
    if (0 != vsc_set_input(1,0,&input)) {DE_ERROR("vsc_set_input(%d) err\n",input.in.src);return -1;}
    msleep(100);

    input.in.src = V4L2_EXT_VSC_INPUT_SRC_HDMI;
    input.out = V4L2_EXT_VSC_DEST_DISPLAY;
    if (0 != vsc_set_input(1,0,&input)) {DE_ERROR("vsc_set_input(%d) err\n",input.in.src);return -1;}
    msleep(100);

    memset(&info, 0, sizeof(info));
    info.in.res.w = 3840;
    info.in.res.h = 2160;
    info.in.crop.w = 3840;
    info.in.crop.h = 2160;
    info.out.w = 3840;
    info.out.h = 2160;
    if (0 != vsc_set_win_info(1,0,1,&info)) {DE_ERROR("vsc_set_win_info(%d) err\n",info.in.res.w);return -1;}

    mute = 0;
    if (0 != vsc_set_mute(1,0,&mute)) {DE_ERROR("vsc_set_mute(%d) err\n",mute);return -1;}
    msleep(100);

    #ifdef INCLUDE_KDRV_BE
    do {
        LX_BE_FRC_CMD_T cmd = {.str="psync 1 0 2"};
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

    /* set rd pos */
    p_ctx->hdr_pxl_rd_ctrl0.r_pxl_rd_sel = 0;
    *p_ctx->hdr_pxl_rd_ctrl0.phy = p_ctx->hdr_pxl_rd_ctrl0.udata32;

    p_ctx->hdr_pxl_rd_ctrl1.r_pxl_rd_pos_x = pos_x;
    p_ctx->hdr_pxl_rd_ctrl1.r_pxl_rd_pos_y = pos_y;
    *p_ctx->hdr_pxl_rd_ctrl1.phy = p_ctx->hdr_pxl_rd_ctrl1.udata32;

    p_ctx->ad_rp_hv_pos.rp_h_pos = pos_x;
    p_ctx->ad_rp_hv_pos.rp_v_pos = pos_y;
    *p_ctx->ad_rp_hv_pos.phy = p_ctx->ad_rp_hv_pos.udata32;

    //DE_NOTI("done\n");
    return 0;
}

static int _de_test_m23_hdmi_close(struct check_hdmi_ctx *p_ctx)
{
    struct v4l2_ext_vsc_connect_info input;

    if (!p_ctx)
    {
        DE_ERROR("p_ctx null\n");
        return -1;
    }

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

struct hdmi_pat {
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

static struct hdmi_pat _g_hdmi_pat[] = {
    {.name="white(rgb)",.type=1,.csc=1,.detail=0,.min_r=940,.max_r=1023,.min_g=940,.max_g=1023,.min_b=940,.max_b=1023},
    {.name="green(rgb)",.type=1,.csc=1,.detail=3,.min_r=0,  .max_r=64,  .min_g=940,.max_g=1023,.min_b=0,  .max_b=64  },
    {.name="red(rgb)",  .type=1,.csc=1,.detail=5,.min_r=940,.max_r=1023,.min_g=0,  .max_g=64,  .min_b=0,  .max_b=64  },
    {.name="blue(rgb)", .type=1,.csc=1,.detail=6,.min_r=0,  .max_r=64,  .min_g=0,  .max_g=64,  .min_b=940,.max_b=1023},
    {.name="black(rgb)",.type=1,.csc=1,.detail=7,.min_r=0,  .max_r=64,  .min_g=0,  .max_g=64,  .min_b=0,  .max_b=64  },
    {.name="white(yc)", .type=1,.csc=0,.detail=0,.min_r=768,.max_r=1023,.min_g=768,.max_g=1023,.min_b=768,.max_b=1023},
    {.name="green(yc)", .type=1,.csc=0,.detail=3,.min_r=0,  .max_r=256, .min_g=768,.max_g=1023,.min_b=0,  .max_b=256 },
    {.name="red(yc)",   .type=1,.csc=0,.detail=5,.min_r=768,.max_r=1023,.min_g=0,  .max_g=256, .min_b=0,  .max_b=256 },
    {.name="blue(yc)",  .type=1,.csc=0,.detail=6,.min_r=0,  .max_r=256, .min_g=0,  .max_g=256, .min_b=768,.max_b=1023},
    {.name="black(yc)", .type=1,.csc=0,.detail=7,.min_r=0,  .max_r=256, .min_g=0,  .max_g=256, .min_b=0,  .max_b=256 },
    {.name=NULL},
};

static struct hdmi_pat _g_hdmi_capture_pat[] = {
    {.name="capture_red(rgb)",  .type=1,.csc=1,.detail=5,.min_r=1000,.max_r=1023,.min_g=0,  .max_g=56,  .min_b=0,  .max_b=48  },
    {.name=NULL},
};


static int _de_test_m23_hdmi_pat(char *name, struct check_hdmi_ctx *p_ctx)
{
    struct hdmi_pat *p = _g_hdmi_pat;

    if (!name)
    {
        DE_ERROR("name null\n");
        return -1;
    }

    if (!p_ctx)
    {
        DE_ERROR("p_ctx null\n");
        return -1;
    }

    p_ctx->misc_ctrl.udata32 = 0;

    while (p->name)
    {
        if (!strncasecmp(name,p->name,strlen(p->name)))
        {
            #ifdef INCLUDE_KDRV_BE
            if (p->csc == 1)
            {
                LX_BE_FRC_CMD_T cmd = {.str="cscinfo 2 4"};
                DE_NOTI("cmd (%s)\n",cmd.str);
                if (0 != BE_FRC_HAL_RunCommand(&cmd)) {DE_ERROR("RunCommand(%s) err\n",cmd.str);return -1;}
            }
            else
            {
                LX_BE_FRC_CMD_T cmd = {.str="cscinfo 2 3"};
                DE_NOTI("cmd (%s)\n",cmd.str);
                if (0 != BE_FRC_HAL_RunCommand(&cmd)) {DE_ERROR("RunCommand(%s) err\n",cmd.str);return -1;}
            }
            #endif

            p_ctx->misc_ctrl.pattern_csc = p->csc;
            p_ctx->misc_ctrl.pattern_type = p->type;
            p_ctx->misc_ctrl.pattern_detail = p->detail;
            DE_NOTI("%-10s : pat csc,type,detail : %d, %d, %d\n",name,p->csc,p->type,p->detail);
            break;
        }
        p++;
    }

    if (!p->name)
    {
        #ifdef INCLUDE_KDRV_BE
        LX_BE_FRC_CMD_T cmd = {.str="cscinfo 2 0"};
        DE_NOTI("cmd (%s)\n",cmd.str);
        if (0 != BE_FRC_HAL_RunCommand(&cmd)) {DE_ERROR("RunCommand(%s) err\n",cmd.str);return -1;}
        #endif
        DE_NOTI("%-10s : pat off\n",name);
    }

    *p_ctx->misc_ctrl.phy = p_ctx->misc_ctrl.udata32;

    return 0;
}


static int _de_test_m23_hdmi_cap(char *name, struct check_hdmi_ctx *p_ctx)
{
    struct hdmi_pat *p = _g_hdmi_capture_pat;

    if (!name)
    {
        DE_ERROR("name null\n");
        return -1;
    }

    if (!p_ctx)
    {
        DE_ERROR("p_ctx null\n");
        return -1;
    }

    p_ctx->misc_ctrl.udata32 = 0;

    while (p->name)
    {
        if (!strncasecmp(name,p->name,strlen(p->name)))
        {
            #ifdef INCLUDE_KDRV_BE
            {
                LX_BE_FRC_CMD_T cmd = {.str="vtg 2 2"};
                DE_NOTI("cmd (%s)\n",cmd.str);
                if (0 != BE_FRC_HAL_RunCommand(&cmd)) {DE_ERROR("RunCommand(%s) err\n",cmd.str);return -1;}
            }
            {
                LX_BE_FRC_CMD_T cmd = {.str="view 8"};
                DE_NOTI("cmd (%s)\n",cmd.str);
                if (0 != BE_FRC_HAL_RunCommand(&cmd)) {DE_ERROR("RunCommand(%s) err\n",cmd.str);return -1;}
            }
            #endif
            msleep(500);

            p_ctx->misc_ctrl.pattern_csc = p->csc;
            p_ctx->misc_ctrl.pattern_type = p->type;
            p_ctx->misc_ctrl.pattern_detail = p->detail;
            DE_NOTI("%-10s : pat csc,type,detail : %d, %d, %d\n",name,p->csc,p->type,p->detail);
            break;
        }
        p++;
    }

    if (!p->name)
    {
        #ifdef INCLUDE_KDRV_BE
        LX_BE_FRC_CMD_T cmd = {.str="view 0"};
        DE_NOTI("cmd (%s)\n",cmd.str);
        if (0 != BE_FRC_HAL_RunCommand(&cmd)) {DE_ERROR("RunCommand(%s) err\n",cmd.str);return -1;}
        #endif
        DE_NOTI("%-10s : view off\n",name);
    }

    *p_ctx->misc_ctrl.phy = p_ctx->misc_ctrl.udata32;

    return 0;
}


static int _de_test_m23_hdmi_rp(char *name, struct check_hdmi_ctx *p_ctx)
{
    int ret = 0;
    int i;
    struct hdmi_pat *p = _g_hdmi_pat;

    if (!name)
    {
        DE_ERROR("name null\n");
        return -1;
    }

    if (!p_ctx)
    {
        DE_ERROR("p_ctx null\n");
        return -1;
    }

    while (p->name)
    {
        if (!strncasecmp(name,p->name,strlen(p->name)))
        {
            for (i=0; i<5; i++)
            {
                msleep(100);

                p_ctx->hdr_pxl_rd_data.udata32 = *((UINT32*)p_ctx->hdr_pxl_rd_data.phy);
                p_ctx->ad_rp_r_value.udata32 = *((UINT32*)p_ctx->ad_rp_r_value.phy);
                p_ctx->ad_rp_g_value.udata32 = *((UINT32*)p_ctx->ad_rp_g_value.phy);
                p_ctx->ad_rp_b_value.udata32 = *((UINT32*)p_ctx->ad_rp_b_value.phy);

                p_ctx->ad_rp_r_value.rd_pixel_r >>= 2;
                p_ctx->ad_rp_g_value.rd_pixel_g >>= 2;
                p_ctx->ad_rp_b_value.rd_pixel_b >>= 2;

                ret = (p_ctx->hdr_pxl_rd_data.pxl_read_rcr >= p->min_r && p_ctx->hdr_pxl_rd_data.pxl_read_rcr <= p->max_r && \
                    p_ctx->hdr_pxl_rd_data.pxl_read_gyy >= p->min_g && p_ctx->hdr_pxl_rd_data.pxl_read_gyy <= p->max_g && \
                    p_ctx->hdr_pxl_rd_data.pxl_read_bcb >= p->min_b && p_ctx->hdr_pxl_rd_data.pxl_read_bcb <= p->max_b && \
                    p_ctx->ad_rp_r_value.rd_pixel_r >= p->min_r && p_ctx->ad_rp_r_value.rd_pixel_r <= p->max_r && \
                    p_ctx->ad_rp_g_value.rd_pixel_g >= p->min_g && p_ctx->ad_rp_g_value.rd_pixel_g <= p->max_g && \
                    p_ctx->ad_rp_b_value.rd_pixel_b >= p->min_b && p_ctx->ad_rp_b_value.rd_pixel_b <= p->max_b)? (0):(-1);

                DE_NOTI("%-10s : r,g,b(10b) : (%4d ~ %4d) (%4d ~ %4d) (%4d ~ %4d)\n",name,p->min_r,p->max_r,p->min_g,p->max_g,p->min_b,p->max_b);
                DE_NOTI("%-10s : r,g,b(10b) : in : %4d, %4d, %4d, out : %4d, %4d, %4d -> %s (retry:%d)\n",name,\
                    p_ctx->hdr_pxl_rd_data.pxl_read_rcr,p_ctx->hdr_pxl_rd_data.pxl_read_gyy,p_ctx->hdr_pxl_rd_data.pxl_read_bcb,\
                    p_ctx->ad_rp_r_value.rd_pixel_r,p_ctx->ad_rp_g_value.rd_pixel_g,p_ctx->ad_rp_b_value.rd_pixel_b,(ret==0)? "ok":"ng",i);

                if (ret == 0)   break;
            }

            if (ret < 0)
            {
                DE_ERROR("%-10s : r,g,b(10b) : in : %4d, %4d, %4d, out : %4d, %4d, %4d -> %s (retry:%d)\n",name,\
                    p_ctx->hdr_pxl_rd_data.pxl_read_rcr,p_ctx->hdr_pxl_rd_data.pxl_read_gyy,p_ctx->hdr_pxl_rd_data.pxl_read_bcb,\
                    p_ctx->ad_rp_r_value.rd_pixel_r,p_ctx->ad_rp_g_value.rd_pixel_g,p_ctx->ad_rp_b_value.rd_pixel_b,"ng",i);
            }
            break;
        }
        p++;
    }

    if (!p->name)
    {
        DE_ERROR("%-10s : not support\n",name);
    }

    return ret;
}

static int _de_test_m23_hdmi_cap_rp(char *name, struct check_hdmi_ctx *p_ctx)
{
    int ret = 0;
    int i;
    struct hdmi_pat *p = _g_hdmi_capture_pat;

    if (!name)
    {
        DE_ERROR("name null\n");
        return -1;
    }

    if (!p_ctx)
    {
        DE_ERROR("p_ctx null\n");
        return -1;
    }
	DE_ERROR("%s", p->name);

    while (p->name)
    {
        if (!strncasecmp(name,p->name,strlen(p->name)))
        {
            for (i=0; i<5; i++)
            {
                msleep(100);

                p_ctx->hdr_pxl_rd_data.udata32 = *((UINT32*)p_ctx->hdr_pxl_rd_data.phy);
                p_ctx->ad_rp_r_value.udata32 = *((UINT32*)p_ctx->ad_rp_r_value.phy);
                p_ctx->ad_rp_g_value.udata32 = *((UINT32*)p_ctx->ad_rp_g_value.phy);
                p_ctx->ad_rp_b_value.udata32 = *((UINT32*)p_ctx->ad_rp_b_value.phy);

                p_ctx->ad_rp_r_value.rd_pixel_r >>= 2;
                p_ctx->ad_rp_g_value.rd_pixel_g >>= 2;
                p_ctx->ad_rp_b_value.rd_pixel_b >>= 2;

                ret = (/*p_ctx->hdr_pxl_rd_data.pxl_read_rcr >= p->min_r && p_ctx->hdr_pxl_rd_data.pxl_read_rcr <= p->max_r && \
                    p_ctx->hdr_pxl_rd_data.pxl_read_gyy >= p->min_g && p_ctx->hdr_pxl_rd_data.pxl_read_gyy <= p->max_g && \
                    p_ctx->hdr_pxl_rd_data.pxl_read_bcb >= p->min_b && p_ctx->hdr_pxl_rd_data.pxl_read_bcb <= p->max_b && \*/
                    p_ctx->ad_rp_r_value.rd_pixel_r >= p->min_r && p_ctx->ad_rp_r_value.rd_pixel_r <= p->max_r && \
                    p_ctx->ad_rp_g_value.rd_pixel_g >= p->min_g && p_ctx->ad_rp_g_value.rd_pixel_g <= p->max_g && \
                    p_ctx->ad_rp_b_value.rd_pixel_b >= p->min_b && p_ctx->ad_rp_b_value.rd_pixel_b <= p->max_b)? (0):(-1);

                DE_NOTI("%-10s : r,g,b(10b) : (%4d ~ %4d) (%4d ~ %4d) (%4d ~ %4d)\n",name,p->min_r,p->max_r,p->min_g,p->max_g,p->min_b,p->max_b);
                DE_NOTI("%-10s : r,g,b(10b) : out : %4d, %4d, %4d -> %s (retry:%d)\n",name,\
                    p_ctx->ad_rp_r_value.rd_pixel_r,p_ctx->ad_rp_g_value.rd_pixel_g,p_ctx->ad_rp_b_value.rd_pixel_b,(ret==0)? "ok":"ng",i);

                if (ret == 0)   break;
            }

            if (ret < 0)
            {
                DE_ERROR("%-10s : r,g,b(10b) : in : %4d, %4d, %4d, out : %4d, %4d, %4d -> %s (retry:%d)\n",name,\
                    p_ctx->hdr_pxl_rd_data.pxl_read_rcr,p_ctx->hdr_pxl_rd_data.pxl_read_gyy,p_ctx->hdr_pxl_rd_data.pxl_read_bcb,\
                    p_ctx->ad_rp_r_value.rd_pixel_r,p_ctx->ad_rp_g_value.rd_pixel_g,p_ctx->ad_rp_b_value.rd_pixel_b,"ng",i);
            }
            break;
        }
        p++;
    }

#ifdef INCLUDE_KDRV_BE
    do {
        LX_BE_FRC_CMD_T cmd = {.str="view 0"};
        DE_NOTI("cmd (%s)\n",cmd.str);
        if (0 != BE_FRC_HAL_RunCommand(&cmd)) {DE_ERROR("RunCommand(%s) err\n",cmd.str);return -1;}
    } while (0);
#endif

    if (!p->name)
    {
        DE_ERROR("%-10s : not support\n",name);
    }

    return ret;
}


static int _de_test_m23_check_hdmi(void)
{
    int ret;
    struct hdmi_pat *p = _g_hdmi_pat;
    static struct check_hdmi_ctx ctx = {.count=0};

    do {
        if (!ctx.count)
        {
            DE_NOTI("start\n");
            memset(&ctx,0,sizeof(ctx));
            if (0 != (ret = _de_test_m23_hdmi_map(&ctx))) {DE_ERROR("_de_test_m23_hdmi_map err\n");break;}
            if (0 != (ret = _de_test_m23_hdmi_open(&ctx, 1920, 1080))) {DE_ERROR("_de_test_m23_hdmi_open err\n");break;}
            ret = ctx.count = 1;
            break;
        }

        if (0 != v4l2_vsc_getlocalmute(0))
        {
            DE_NOTI("local mute (%d)\n",v4l2_vsc_getlocalmute(0));
            msleep(100);
            ret = ++ctx.count;
            break;
        }

        while (p->name)
        {
            DE_NOTI("check pat(%s)\n",p->name);
            if (0 != (ret = _de_test_m23_hdmi_pat(p->name, &ctx))) {DE_ERROR("_de_test_m23_hdmi_pat(%s) err\n",p->name);break;}
            if (0 != (ret = _de_test_m23_hdmi_rp(p->name, &ctx))) {DE_ERROR("_de_test_m23_hdmi_rp(%s) err\n",p->name);break;}
            p++;
        };
    } while (0);

    if (ret<=0)
    {
        ctx.count = 0;
        if (0 != _de_test_m23_hdmi_pat("off", &ctx)) {DE_ERROR("_de_test_m23_hdmi_pat(off) err\n");return -1;}
        if (0 != _de_test_m23_hdmi_close(&ctx)) {DE_ERROR("_de_test_m23_hdmi_close err\n");return -1;}
        if (0 != _de_test_m23_hdmi_unmap(&ctx)) {DE_ERROR("_de_test_m23_hdmi_unmap err\n");return -1;}
    }

    DE_NOTI("ret : %d\n",ret);
    return ret;
}

static int _de_test_m23_check_mvi(void)
{
    DE_ERROR("not support\n");
    return 0;
}

static int _de_test_m23_check_gpsdma(void)
{
	DE_ERROR("not support\n");
	return 0;
}

static int _de_test_m23_check_capture(void)
{
	int ret;
	 struct hdmi_pat *p = _g_hdmi_capture_pat;
	 static struct check_hdmi_ctx ctx = {.count=0};

	 do {
		 if (!ctx.count)
		 {
			 DE_NOTI("start\n");
			 memset(&ctx,0,sizeof(ctx));
			 if (0 != (ret = _de_test_m23_hdmi_map(&ctx))) {DE_ERROR("_de_test_m23_hdmi_map err\n");break;}
			 if (0 != (ret = _de_test_m23_hdmi_open(&ctx, 0, 0))) {DE_ERROR("_de_test_m23_hdmi_open err\n");break;}
			 ret = ctx.count = 1;
			 break;
		 }

		 if (0 != v4l2_vsc_getlocalmute(0))
		 {
			 DE_NOTI("local mute (%d)\n",v4l2_vsc_getlocalmute(0));
			 msleep(100);
			 ret = ++ctx.count;
			 break;
		 }

		 while (p->name)
		 {
			 DE_NOTI("check pat(%s)\n",p->name);
			 if (0 != (ret = _de_test_m23_hdmi_cap(p->name, &ctx))) {DE_ERROR("_de_test_m23_hdmi_cap(%s) err\n",p->name);break;}
			 if (0 != (ret = _de_test_m23_hdmi_cap_rp(p->name, &ctx))) {DE_ERROR("_de_test_m23_hdmi_cap_rp(%s) err\n",p->name);break;}
			 p++;
		 };
	 } while (0);

	 if (ret<=0)
	 {
		 ctx.count = 0;
		 if (0 != _de_test_m23_hdmi_pat("off", &ctx)) {DE_ERROR("_de_test_m23_hdmi_pat(off) err\n");return -1;}
		 if (0 != _de_test_m23_hdmi_close(&ctx)) {DE_ERROR("_de_test_m23_hdmi_close err\n");return -1;}
		 if (0 != _de_test_m23_hdmi_unmap(&ctx)) {DE_ERROR("_de_test_m23_hdmi_unmap err\n");return -1;}
	 }

	 DE_NOTI("ret : %d\n",ret);
	 return ret;
}
