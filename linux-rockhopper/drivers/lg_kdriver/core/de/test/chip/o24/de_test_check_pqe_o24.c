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
#include "util/de_test_util_o24.h"

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
struct de_test_check_pqe_o24_func
{
    char *name;
    int (*func)(void);
    int done;
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
int de_test_check_pqe_o24_run(void);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int _de_test_check_pqe_o24_mcu0(void);
static int _de_test_check_pqe_o24_mcu1(void);
static int _de_test_check_pqe_o24_hdmi(void);
static int _de_test_check_pqe_o24_mvi(void);
static struct de_test_check_pqe_o24_func _g_de_test_check_pqe_o24_func[] = {
    {.done=0,.name="check_pqe_mcu0",.func=_de_test_check_pqe_o24_mcu0},
    {.done=0,.name="check_pqe_mcu1",.func=_de_test_check_pqe_o24_mcu1},
    {.done=0,.name="check_pqe_hdmi",.func=_de_test_check_pqe_o24_hdmi},
    {.done=0,.name="check_pqe_mvi", .func=_de_test_check_pqe_o24_mvi},
    {.name=NULL}
};

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
int de_test_check_pqe_o24_run(void)
{
    int ret = 0;
    struct de_test_check_pqe_o24_func *p_func = _g_de_test_check_pqe_o24_func;

    while (p_func->name)
    {
        if (!p_func->done && p_func->func)
        {
            DE_NOTI("(%s) run\n",p_func->name);
            if (0 == (ret = p_func->func()))
            {
                DE_NOTI("(%s) ok (go next)\n",p_func->name);
                p_func->done = 1;
                ret = 1;//continue
            }
            break;
        }
        else
        {
            p_func++;
        }
    }

    if (ret < 0)
    {
        DE_ERROR("(%s) ng\n",p_func->name);
    }

    return ret;
}

static int _de_test_check_pqe_o24_mcu0(void)
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

static int _de_test_check_pqe_o24_mcu1(void)
{
    DE_ERROR("not support\n");
    return 0;
}

static int _de_test_check_pqe_o24_hdmi(void)
{
    int ret = 1;
    static int start = 0;
    UINT32 pos_x=1920;
    UINT32 pos_y=1080;
    char **p;
    char *pat_str[] = {"white(rgb)","green(rgb)","red(rgb)","blue(rgb)","black(rgb)","white(yc)","green(yc)","red(yc)","blue(yc)","black(yc)",NULL};

    do {
        if (!start)
        {
            DE_NOTI("open\n");
            if (0 != (ret = de_test_util_o24_input_open("hdmi","4k","4k"))) {DE_ERROR("de_test_util_o24_input_open err\n");break;}
            start = 1;
            ret = 1;
            break;
        }

        if (0 != v4l2_vsc_getlocalmute(0))
        {
            DE_NOTI("local mute (%d)\n",v4l2_vsc_getlocalmute(0));
            if (++start>10)
            {
                DE_ERROR("local mute time out\n");
                ret = -1;
            }
            break;
        }

        p = pat_str;
        while (*p)
        {
            DE_NOTI("run(%s)\n",*p);
            if (0 != (ret = de_test_util_o24_cvi_pat_on(*p))) {DE_ERROR("de_test_util_o24_cvi_pat_on(%s) err\n",*p);break;}
            if (0 != (ret = de_test_util_o24_check_cvi_i_pixel(*p,pos_x,pos_y))) {DE_ERROR("de_test_util_o24_check_cvi_i_pixel(%s) err\n",*p);break;}
            if (0 != (ret = de_test_util_o24_check_cvi_o_pixel(*p,pos_x,pos_y))) {DE_ERROR("de_test_util_o24_check_cvi_o_pixel(%s) err\n",*p);break;}
            p++;
        }
    } while (0);

    if (ret<=0)
    {
        if (0 != de_test_util_o24_cvi_pat_off()) {DE_ERROR("de_test_util_o24_cvi_pat_off err\n");return -1;}
        if (0 != de_test_util_o24_input_close()) {DE_ERROR("de_test_util_o24_input_close err\n");return -1;}
        DE_NOTI("close\n");
        start = 0;
    }

    DE_NOTI("ret : %d\n",ret);
    return ret;
}

static int _de_test_check_pqe_o24_mvi(void)
{
    DE_ERROR("not support\n");
    return 0;
}
