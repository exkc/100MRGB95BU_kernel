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

#include "os_util.h"
#include "base_device.h"
#include "de_ver_def.h"
#include "de_def.h"
#include "de_kapi.h"
#include "vsc_fw.h"
#include "vsc_wdog.h"
#include "resource_mgr.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* ver, yyyy/mm/dd/hh:mm */
#define VSC_WDOG_VER		"2023/01/27/14:22"

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
struct vsc_wdog_ctx {
    char *name;
    unsigned int msec;
    pid_t tid;
    pid_t pid;

    union {
        unsigned int u32;
        struct {
            unsigned int reset : 1;//[0:0]
        };
    } dbg;
};

struct vsc_wdog_entry {
    char *name;
    struct vsc_wdog_ctx ctx;
    struct task_struct *task;
    int (*thread_fn)(void *ptr);
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
static int vsc_wdog_mcu1(void *ptr);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static struct vsc_wdog_entry _g_vsc_wdog_entry[] = {
    {.name="mcu1_reset", .task=NULL, .thread_fn=vsc_wdog_mcu1},
    {.name=NULL}
};

/*========================================================================================
	Implementation Group
========================================================================================*/
int vsc_wdog_start(char *name, unsigned int msec)
{
    struct vsc_wdog_entry *p = _g_vsc_wdog_entry;

    if (!name)
    {
        DE_ERROR("no name\n");
        return 0;
    }

    while (p->name)
    {
        if (!strncmp(name,p->name,strlen(p->name)))
        {
            p->ctx.msec = msec;

            if (p->task)
            {
                DE_NOTI("already run (%s)\n",p->name);
                break;
            }

            p->ctx.name = p->name;
            p->ctx.tid = task_tgid_nr(current);
            p->ctx.pid = task_pid_nr(current);
            p->ctx.dbg.u32 = 0;
            p->task = kthread_run(p->thread_fn,(void *)&p->ctx,"%s-%05d%05d",p->ctx.name,p->ctx.tid,p->ctx.pid);
            if (!p->task)
            {
                DE_ERROR("%s-%05d%05d fail\n",p->ctx.name,p->ctx.tid,p->ctx.pid);
                break;
            }

            DE_NOTI("(%s-%s) %s-%05d%05d msec:%d run\n",current->group_leader->comm,current->comm,p->ctx.name,p->ctx.tid,p->ctx.pid,p->ctx.msec);
            break;
        }
        p++;
    }

    return 0;
}

int vsc_wdog_stop(char *name)
{
    struct vsc_wdog_entry *p = _g_vsc_wdog_entry;

    if (!name)
    {
        DE_ERROR("no name\n");
        return 0;
    }

    while (p->name)
    {
        if (!strncmp(name,p->name,strlen(p->name)))
        {
            if (!p->task)
            {
                DE_NOTI("already stop (%s)\n",p->name);
                break;
            }

            send_sig(SIGUSR1,p->task,0);
            kthread_stop(p->task);
            p->task = NULL;

            DE_NOTI("(%s-%s) %s-%05d%05d stop\n",current->group_leader->comm,current->comm,p->ctx.name,p->ctx.tid,p->ctx.pid);
            break;
        }
        p++;
    }

    return 0;
}

int vsc_wdog_status(char* buffer)
{
    int len = 0;
    struct vsc_wdog_entry *p = _g_vsc_wdog_entry;

    if (!buffer)	return 0;

    len += sprintf( buffer+len, "---------------------------------------------------------------------\n");
    len += sprintf( buffer+len, "%s : %s\n","ver",VSC_WDOG_VER);
    len += sprintf( buffer+len, "---------------------------------------------------------------------\n");
    while (p->name)
    {
        len += sprintf( buffer+len, "%s : task:%p, thread_fn:%p\n",(p->name)? p->name:"null",p->task,p->thread_fn);
        len += sprintf( buffer+len, "ctx:%s, msec:%d, tid:%05d, pid:%05d, dbg:%x\n",(p->ctx.name)? p->ctx.name:"null",p->ctx.msec,p->ctx.tid,p->ctx.pid,p->ctx.dbg.u32);
        len += sprintf( buffer+len, "---------------------------------------------------------------------\n");
        p++;
    }

    len += sprintf( buffer+len, "usage:\n");
    len += sprintf( buffer+len, "echo [%s] %s [%s] > /proc/lg/de/wdog\n","name","start","delay(msec)");
    len += sprintf( buffer+len, "echo [%s] %s > /proc/lg/de/wdog\n","name","stop");
    len += sprintf( buffer+len, "echo [%s] %s [%s] > /proc/lg/de/wdog\n","name","dbg","number(bit)");
    len += sprintf( buffer+len, "---------------------------------------------------------------------\n");

    return len;
}

int vsc_wdog_command(char* command)
{
    char *tok, *sav_tok;
    char delim[] = "= \t\n";
    struct vsc_wdog_entry *p = _g_vsc_wdog_entry;

    if (!command)	return 0;

    tok=simple_strtok(command, delim, &sav_tok);
    if (!tok)   return 0;

    while (p->name)
    {
        if (!strncmp(tok,p->name,strlen(p->name)))
        {
            tok=simple_strtok(NULL, delim, &sav_tok);

            while(tok)
            {
                if (!strncasecmp(tok, "start", strlen("start")))
                {
                    unsigned int msec = 1000;
                    tok=simple_strtok(NULL, delim, &sav_tok);
                    if(tok)
                    {
                        if(1 != sscanf(tok, "%d", &msec))
                        {
                            DE_NOTI("invalid param\n");
                        }
                    }
                    DE_NOTI("vsc_wdog_start(%s,%d)\n",p->name,msec);
                    vsc_wdog_start(p->name, msec);
                    break;
                }

                if (!strncasecmp(tok, "stop", strlen("stop")))
                {
                    DE_NOTI("vsc_wdog_stop(%s)\n",p->name);
                    vsc_wdog_stop(p->name);
                    break;
                }

                if (!strncasecmp(tok, "dbg", strlen("dbg")))
                {
                    unsigned int dbg = 0;
                    tok=simple_strtok(NULL, delim, &sav_tok);
                    if(tok)
                    {
                        if(1 != sscanf(tok, "%x", &dbg))
                        {
                            DE_NOTI("invalid param\n");
                        }
                    }
                    p->ctx.dbg.u32 = dbg;
                    DE_NOTI("(%s) dbg:%x\n",p->name,p->ctx.dbg.u32);
                    break;
                }

                tok=simple_strtok(NULL, delim, &sav_tok);
            }

            break;
        }
        p++;
    }

    return 0;
}

static int vsc_wdog_mcu1(void *ptr)
{
    int ret;
    bool was_frozen;
    unsigned int cur_cnt;
    static unsigned int pre_cnt;
    volatile unsigned int *p_addr = NULL;
    struct vsc_wdog_ctx *p = (struct vsc_wdog_ctx *)ptr;

    if (!p)
    {
        DE_ERROR("p : null\n");
        return 0;
    }

    if (0) { }
    #ifdef USE_KDRV_CODES_FOR_O22
    else if (lx_chip() == LX_CHIP_O22)
    {
        p_addr = (volatile unsigned int *)ioremap(0xCC8C0D4C,sizeof(unsigned int));//REG_IMX_VERI_SYS_VERI_19_T
    }
    #endif
    else
    {
        DE_NOTI("not support (chip:0x%x)\n",lx_chip());
        return 0;
    }

    if (!p_addr)
    {
        DE_ERROR("p_addr : null\n");
        return 0;
    }

    allow_signal(SIGUSR1);
    set_freezable();

    DE_NOTI("%s-%05d%05d msec:%d start\n",p->name,p->tid,p->pid,p->msec);

    while (!kthread_freezable_should_stop(&was_frozen))
    {
        if (was_frozen) DE_NOTI("wakes up\n");
        if (kthread_should_stop())  break;

        msleep_interruptible(p->msec);

        cur_cnt = *((unsigned int *)p_addr);
        if ((pre_cnt > 0 && pre_cnt == cur_cnt) || (p->dbg.reset == 1))
        {
            LX_DE_FW_DWLD_T fw = {.inx=1,.size=0,.pData=NULL};
            DE_NOTI("%s-%05d%05d reset\n",p->name,p->tid,p->pid);

            fw.cfg = DE_FW_CFG_DOWNLOAD_HEADER;
            ret = vsc_fw_io_download((void *)&fw,CALL_FROM_KERNEL);
            if (ret)    DE_WARN("load err\n");

            pre_cnt = 0;
            p->dbg.reset = 0;
        }
        else
        {
            DE_NOTI("%s-%05d%05d cnt:%08x -> %08x\n",p->name,p->tid,p->pid,pre_cnt,cur_cnt);
            pre_cnt = cur_cnt;
        }
    }

    if (p_addr) iounmap((void *)p_addr);

    DE_NOTI("%s-%05d%05d stop\n",p->name,p->tid,p->pid);

    return 0;
}
