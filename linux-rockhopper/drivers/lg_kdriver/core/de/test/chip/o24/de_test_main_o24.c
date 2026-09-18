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
//#include "linux/v4l2-ext/v4l2-ext-renderer.h"
//#include "linux/v4l2-ext/v4l2-ext-panel.h"

#include "os_util.h"
#include "base_device.h"
#include "de_ver_def.h"
#include "de_def.h"
#include "de_kapi.h"
#include "../../de_test.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
struct de_test_o24_ctx
{
    int state;
    char *name;
    void *handler;
    struct task_struct *task;
    int (*func)(void);
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
int de_test_o24_handler(struct de_test_handler *ph);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int _de_test_o24_init(void);
static int _de_test_o24_run(void *ptr);
static int _de_test_o24_task(void *ptr);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
extern int de_test_check_pqe_o24_run(void);
extern int de_test_check_vsc_o24_run(void);
extern int de_test_check_gps_o24_run(void);
extern int de_test_check_cap_o24_run(void);
static struct de_test_o24_ctx _g_de_test_o24_ctx[] = {
    {.name="run_test_pqe",.task=NULL,.func=de_test_check_pqe_o24_run},
    {.name="run_test_vsc",.task=NULL,.func=de_test_check_vsc_o24_run},
    {.name="run_test_gps",.task=NULL,.func=de_test_check_gps_o24_run},
    {.name="run_test_cap",.task=NULL,.func=de_test_check_cap_o24_run},
    {.name=NULL}
};

/*========================================================================================
	Implementation Group
========================================================================================*/
int de_test_o24_handler(struct de_test_handler *ph)
{
    int ret;
    struct de_test_o24_ctx *p_ctx = _g_de_test_o24_ctx;

    if (!ph)
    {
        DE_ERROR("ph null\n");
        return -1;
    }

    if (ph->type == de_test_handler_type_init)
    {
        return _de_test_o24_init();
    }

    while (p_ctx->name)
    {
        if (!strncasecmp(ph->str, p_ctx->name, strlen(p_ctx->name)))
        {
            //DE_NOTI("(%s) type(%s) run func\n",p->name,ph->type);
            p_ctx->handler = (void *)ph;
            ret = _de_test_o24_run((void *)p_ctx);
            break;
        }
        p_ctx++;
    }

    if (!p_ctx->name)
    {
        DE_ERROR("(%s) not support\n",ph->str);
        return 0;
    }

    return ret;
}

static int _de_test_o24_init(void)
{
    DE_NOTI("init done\n");
    return 0;
}

static int _de_test_o24_run(void *ptr)
{
    LX_DE_TEST_CMD_T *p_cmd;
    struct de_test_handler *p_handler;
    struct de_test_o24_ctx *p_ctx = (struct de_test_o24_ctx *)ptr;

    if (!p_ctx)
    {
        DE_ERROR("p_ctx null\n");
        return -1;
    }

    if (!p_ctx->func)
    {
        DE_ERROR("(%s) p_ctx->func null\n",p_ctx->name);
        return -1;
    }

    p_handler = (struct de_test_handler *)p_ctx->handler;
    if (!p_handler)
    {
        DE_ERROR("(%s) p_handler null\n",p_ctx->name);
        return -1;
    }

    p_cmd = (LX_DE_TEST_CMD_T *)p_handler->cmd;
    if (!p_cmd)
    {
        DE_ERROR("(%s) p_cmd null\n",p_ctx->name);
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
            p_ctx->task = kthread_run(_de_test_o24_task,(void *)p_ctx,"%s",p_handler->str);
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

static int _de_test_o24_task(void *ptr)
{
    int ret = 0;
    struct de_test_o24_ctx *p_ctx = (struct de_test_o24_ctx *)ptr;

    if (!p_ctx)
    {
        DE_ERROR("p_ctx null\n");
        return 0;
    }

    if (!p_ctx->func)
    {
        DE_ERROR("(%s) p_ctx->func null\n",p_ctx->name);
        return -1;
    }

    allow_signal(SIGUSR1);
    while (p_ctx->name)
    {
        if (kthread_should_stop())  {DE_NOTI("task stop\n");break;}
        msleep_interruptible(100);

        ret = p_ctx->func();
        if (ret <= 0)   {DE_ERROR("(%s) result %s\n",p_ctx->name,(ret==0)? "ok":"ng");break;}
        if (p_ctx->state < 100) p_ctx->state++;//time out 10sec
    }

    p_ctx->state = ret;
    DE_NOTI("state (%d) done\n",p_ctx->state);

    return 0;
}
