/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2021 by LG Electronics Inc.
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
 *  audio dsp control
 *
 *  author      Youngwoo Jin ( youngwoo.jin@lge.com )
 *  version     1.0
 *  date        2021.02.09
 *
 */

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/wait.h>
#include <linux/completion.h>
#include <linux/fault_notifier.h>
#include <linux/printk.h>
#include <linux/kthread.h>

#include "fwload.h"
#include "module/adec_module_list.h"
#include "common/ipc_reg_offs.h"
#include "hal/hal.h"
#include "hal/hal_ipc.h"
#include "kaimc.h"
#include "module/adec_module_list.h"    ///< ADEC_CORE_ARM
#include "common/module/uid.h"  ///< AUD_MODID_REGISTRY ()
#include "block_manager.h"
#include "dsp_control.h"
#include "regs.h"
#include "proc.h"
#include "blind.h"
#include "ipc_regs.h"
#include "hma_alloc.h"
#include "fwload_drv.h"

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/
#ifndef CHIP_TYPE_FPGA
#define MONITOR_TASK_WAIT_TIMEOUT   (200)
#else
#define MONITOR_TASK_WAIT_TIMEOUT   (200*88)    // O24 FPGA is 88 times slower than CHIP.
#endif
#define DSP_AUTO_RECOVERY_COUNT     (3) // 3 : 200 * 3 = 600 ms for ESD recovery,
                                        // 2011.11.02 after reset, audio outputs 200ms.
                                        // QE Spec. is 1 seconds.

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/
#define trace(fmt,args...)  logm_trace(aud_dsp,fmt,##args)
#define debug(fmt,args...)  logm_debug(aud_dsp,fmt,##args)
#define info(fmt,args...)   logm_info(aud_dsp,fmt,##args)
#define noti(fmt,args...)   logm_noti(aud_dsp,fmt,##args)
#define warn(fmt,args...)   logm_warning(aud_dsp,fmt,##args)
#define error(fmt,args...)  logm_error(aud_dsp,fmt,##args)

#define DSP_INFO(_num, _state)  {                           \
    .name = "aud" #_num,                                    \
    .state = _state,                                        \
    .ipc_offset = {                                         \
        .hb_cnt = AUD_IPCOFFS_DSP##_num##_GSTC,             \
        .reset_count = AUD_IPCOFFS_DBG_DSP##_num##_RESET,   \
        .runmod = AUD_IPCOFFS_DSP##_num##_RUNMOD,           \
    },                                                      \
}

#define WRITE_REG(reg, val) (*(volatile unsigned int *)(reg) = (val))

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
enum dsp_state
{ DSP_STATE_OFF, DSP_STATE_ON, DSP_STATE_RUN };

struct _dsp_info
{
    const char *name;
    enum dsp_state state;

    const struct
    {
        unsigned int hb_cnt;
        unsigned int reset_count;
        unsigned int runmod;
    } ipc_offset;

    uint32_t hb;
    uint32_t pre_hb;
    uint32_t gstc;
    uint32_t pre_gstc;
    unsigned int same_cnt;
};

/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    External Variables
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    global Variables
------------------------------------------------------------------------------*/
logm_define (aud_dsp, log_level_noti);

/*------------------------------------------------------------------------------
    Static Function Prototypes Declarations
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Static Variables
------------------------------------------------------------------------------*/
static DECLARE_COMPLETION (reset_completion);
static struct task_struct *monitor_task = NULL;
static int number_of_dsp = 0;
static struct _dsp_info dsp_infos[] = {
    DSP_INFO (0, DSP_STATE_ON),
    DSP_INFO (1, DSP_STATE_ON),
    DSP_INFO (2, DSP_STATE_ON),
#if (NUM_OF_DSP >= 4)
    DSP_INFO (3, DSP_STATE_ON),
#endif
};

struct task_struct *dump_ready_thread;
static int dsp_dump_ready_check_thread (void *data);
static DECLARE_WAIT_QUEUE_HEAD (dump_ready_wq);
static unsigned int aud_dsp_dump_ready_timeout = 100;

#ifndef CHIP_TYPE_FPGA
static unsigned int aud_dsp_boot_timeout = 600;
#else
static unsigned int aud_dsp_boot_timeout = 600 * 88;    // O24 FPGA is 88 times slower than CHIP.
#endif
module_param (aud_dsp_boot_timeout, uint, 0644);

static bool aud_monitor_dsp = true;
module_param (aud_monitor_dsp, bool, 0644);

static int aud_dsp_reset_count;
module_param (aud_dsp_reset_count, int, 0444);

static bool aud_monitor_gstc = true;
module_param (aud_monitor_gstc, bool, 0644);

static unsigned int aud_dsp_pre_gtsc = 0;

static bool aud_dsp_dump = true;
module_param (aud_dsp_dump, bool, 0644);

static int aud_dsp_dump_max = 1;
module_param (aud_dsp_dump_max, int, 0644);

static int aud_dsp_dump_timeout = 10;
module_param (aud_dsp_dump_timeout, int, 0644);

unsigned int aud_dsp_reset_debug_count[NUM_OF_DSP];
static void aud_set_dsp_reset_count (void)
{
    int i;

    for (i = 0; i < number_of_dsp; i++)
    {
        if (aud_dsp_reset_debug_count[i])
        {
            unsigned int offs[4] = {
                AUD_IPCOFFS_DBG_DSP0_RESET, AUD_IPCOFFS_DBG_DSP1_RESET,
                AUD_IPCOFFS_DBG_DSP2_RESET, AUD_IPCOFFS_DBG_DSP3_RESET,
            };

            AUD_IPCREG_OFFS (offs[i]) = aud_dsp_reset_debug_count[i];
            error ("reset dsp debug count... dsp%d : %d\n", i, aud_dsp_reset_debug_count[i]);
        }
    }
}

unsigned int aud_dsp_reset_num[NUM_OF_DSP];

struct dsp_dump_arg
{
    unsigned int dump_mask;
    spinlock_t lock;
    struct wait_queue_head wq;
};

static int dsp_dump_done (void *param, int size, void *cb_param)
{
    struct dsp_dump_arg *arg = cb_param;
    ADEC_CORE_TYPE core;
    unsigned int dspnum;
    unsigned long flag;

    if (size != sizeof (core))
    {
        error ("wrong param size. %d\n", size);
        return -1;
    }

    core = *(ADEC_CORE_TYPE *) param;
    dspnum = core - ADEC_CORE_DSP0;

    error ("dump done. dsp%d\n", dspnum);
    spin_lock_irqsave (&arg->lock, flag);
    arg->dump_mask &= ~(1U << dspnum);
    spin_unlock_irqrestore (&arg->lock, flag);

    if (arg->dump_mask == 0)
        wake_up (&arg->wq);

    return 0;
}

#define AUDIO_DUMP_POOL_NAME "audio_dump"
#define ALIGN_DOWN_1MB(size) (size & ~0xFFFFF)

static int dsp_dump_ready_check_thread (void *data)
{
    noti ("dsp_dump_ready_check_thread started");

    while (!kthread_should_stop ())
    {
        if (AUD_IPCREG (DSP_DUMP_READY))
        {
            wake_up (&dump_ready_wq);
        }
        msleep (1);
    }
    return 0;
}

static void _wait_dsp_dump_ready (unsigned int dsp_num, bool wait)
{
    if (wait)
    {
        AUD_IPCREG (DSP_DUMP_READY) = 0;
        aud_send_irq_cmd (dsp_num, 8);

        noti ("send suicide command to dsp_%d", dsp_num);

        dump_ready_thread = kthread_run (dsp_dump_ready_check_thread, NULL, "dump_ready_thread");

        noti ("wait ready to dump");
        wait_event_timeout (dump_ready_wq, AUD_IPCREG (DSP_DUMP_READY) == 1,
            msecs_to_jiffies (aud_dsp_dump_ready_timeout));

        if (AUD_IPCREG (DSP_DUMP_READY))
            noti ("dsp dump ready register updated");
        else
            noti ("timeout");

        kthread_stop (dump_ready_thread);
    }
    else
    {
        aud_send_irq_cmd (dsp_num, 0);

        noti ("send clear command to dsp_%d", dsp_num);
    }
}

static void _dump_dsp (unsigned int dsp_num)
{
    int i;
    int ret = 0, callret = 0;
    struct dsp_dump_arg arg;
    int dump_done_event = 0;
    static unsigned int dsp_dump_timeout = 600;
    phys_addr_t paddr = 0;
    phys_addr_t ram_addr = 0;
    unsigned int ram_size = 0;
    char *user_name = NULL;
    phys_addr_t pool_addr;
    int pool_size, alloc_size, cnt = 0;

    if (!aud_hal_secure_loading_supported ())
    {
        aud_send_irq_cmd (dsp_num, 8);

        ret = ablind_call_timeout (HZ * aud_dsp_dump_timeout, &callret, "dspdump", 1, dsp_num);
        if (ret == 1)
            noti ("\"dspdump\" done. callret %d\n", callret);
        else if (ret <= 0)
            error ("\"dspdump\" not handled. ret %d\n", ret);
        else
            error ("\"dspdump\" timeout. ret %d\n", ret);

        // clear suicide command
        aud_send_irq_cmd (dsp_num, 0);
    }
    else
    {
        _wait_dsp_dump_ready (dsp_num, true);

        memset (&arg, 0, sizeof (arg));
        init_waitqueue_head (&arg.wq);
        spin_lock_init (&arg.lock);

        dump_done_event = aimc_register_named_event (&arg, dsp_dump_done,
            AUD_MODID_REGISTRY (ADEC_CORE_ARM), "dsp-dump-done", true);
        if (dump_done_event <= 0)
        {
            error ("aimc_register_named_event() failed %d.\n", dump_done_event);
            return;
        }

        user_name = kasprintf (GFP_KERNEL, "dsp%d_ram", dsp_num);

        ret = fwload_get_dsp_memory_info (dsp_infos[dsp_num].name, "ram", &ram_addr, &ram_size);
        if (ret < 0)
        {
            error ("fwload_get_dsp_memory_info failed.\n");
            goto clean_up;
        }

        hma_pool_info (AUDIO_DUMP_POOL_NAME, &pool_addr, &pool_size);
        while (ram_size)
        {
            // align 1MB unit
            alloc_size = (ram_size > pool_size) ? ALIGN_DOWN_1MB (pool_size) : ram_size;
            ram_size = ram_size - alloc_size;
            noti ("alloc_size %d ram_size %d", alloc_size, ram_size);
            paddr = hma_alloc_user (AUDIO_DUMP_POOL_NAME, alloc_size, 0x1000, user_name);
            if (paddr == 0)
            {
                error ("no mem for dump dsp ram area. %d\n", alloc_size);
                goto clean_up;
            }

            AUD_IPCREG (MEM_DEBUG_BASE) = aud_phys_to_lgbus (paddr);
            AUD_IPCREG (DSP_RAM_START) = aud_phys_to_lgbus (ram_addr);
            AUD_IPCREG (DSP_RAM_SIZE) = alloc_size;

            for (i = 0; i < number_of_dsp; i++)
            {
                if (!aud_dsp_reset_num[i])
                {
                    aud_send_irq_cmd (i, 10 + dsp_num);
                    error ("send irq cmd %d to dsp%d\n", 10 + dsp_num, i);
                    arg.dump_mask |= 1U << i;
                    break;
                }
            }

            if (i == number_of_dsp)
            {
                error ("all dsp are dead!\n");
                ram_size = 0;
                goto end_while;
            }

            info ("wait event from dsp to complete dump memory ");
            ret = wait_event_interruptible_timeout (arg.wq, (arg.dump_mask == 0),
                msecs_to_jiffies (dsp_dump_timeout));
            if (ret == 0)
            {
                error ("dsp dump timeout. 0x%x\n", arg.dump_mask);
                ram_size = 0;
                goto end_while;
            }
            else if (ret < 0)
            {
                error ("dsp dump waiting interrupted. 0x%x\n", arg.dump_mask);
                ram_size = 0;
                goto end_while;
            }

            info ("wait dsp%d dump done\n", dsp_num);

            fwload_add_dsp_ram_area (dsp_infos[dsp_num].name, paddr, alloc_size);

            ret =
                ablind_call_timeout (HZ * aud_dsp_dump_timeout, &callret, "dspdump", 1,
                dsp_num + cnt * 10);
            cnt++;

            if (ret == 1)
                noti ("dspdump done. callret %d\n", callret);
            else if (ret <= 0)
            {
                error ("dspdump is not handled. ret %d\n", ret);
                ram_size = 0;
            }
            else
            {
                error ("dspdump timeout. ret %d\n", ret);
                ram_size = 0;
            }

            fwload_delete_dsp_ram_area (dsp_infos[dsp_num].name);

          end_while:
            if (paddr)
                hma_free (AUDIO_DUMP_POOL_NAME, paddr);
        }
      clean_up:
        if (dump_done_event > 0)
            aimc_unregister_named_event (dump_done_event);
        if (user_name)
            kfree (user_name);

        _wait_dsp_dump_ready (dsp_num, false);
    }
}

static void _check_heartbeat (void)
{
    int i;
    bool reset_required;
    unsigned int dump_dsp;

    /* check dsp heartbeat */
    reset_required = false;
    dump_dsp = 0;

    for (i = 0; i < number_of_dsp; i++)
        aud_dsp_reset_num[i] = 0;

    for (i = 0; i < number_of_dsp; i++)
    {
        struct _dsp_info *dsp_info = dsp_infos + i;

        if (dsp_info->state != DSP_STATE_RUN)
        {
            continue;
        }

        dsp_info->hb = aud_hal_ipc_read (dsp_info->ipc_offset.hb_cnt);

        trace ("[%d] heart beat count %08x, %08x\n", i, dsp_info->hb, dsp_info->pre_hb);

        if (dsp_info->hb == dsp_info->pre_hb)
        {
            uint32_t runmod;
            uint32_t debugpc;

            runmod = aud_hal_ipc_read (dsp_info->ipc_offset.runmod);
            debugpc = aud_hal_get_dsp_pc (i);

            noti ("dsp%d heartbeat count not changed. %08x, runmod 0x%x(%s), debugpc 0x%08x\n", i,
                dsp_info->hb, runmod, ModuleList_GetModuleName (runmod), debugpc);

            dsp_info->same_cnt++;

            if (dsp_info->same_cnt < DSP_AUTO_RECOVERY_COUNT)
            {
                aud_send_irq_cmd (i, 3);
            }
            else
            {
                uint32_t reg_reset_count = aud_hal_ipc_read (dsp_info->ipc_offset.reset_count);

                aud_hal_ipc_write (dsp_info->ipc_offset.reset_count, reg_reset_count + 1);
                aud_hal_ipc_write (AUD_IPCOFFS_IRQ_COMMAND, 0);

                error ("reset... dsp%d\n", i);
                reset_required = true;
                dump_dsp = i;
                aud_dsp_reset_num[i] = 1;
                aimc_set_dsp_dead (i, true);    // noti to kaimc that don't send command to dead dsp...
            }
        }
        else
        {
            dsp_info->same_cnt = 0;
        }

        dsp_info->pre_hb = dsp_info->hb;
    }

    if (reset_required)
    {
        error ("Reset Audio(count = %d)\n", aud_dsp_reset_count);
        if (aud_dsp_reset_count < INT_MAX)
            aud_dsp_reset_count++;

        if (aud_dsp_dump && aud_dsp_reset_count <= aud_dsp_dump_max)
        {
            noti ("do dspdump... dsp %d\n", dump_dsp);
            _dump_dsp (dump_dsp);
        }

        if (aud_dsp_reset_count == 1)
        {
            int i;
            char dsp_reset_msg[64];
            char dsp_reset_num[32];
            char dsp_reset_all[32];

            dsp_reset_num[0] = '\0';
            dsp_reset_all[0] = '\0';

            for (i = 0; i < number_of_dsp; i++)
            {
                if (aud_dsp_reset_num[i])
                {
                    if (dsp_reset_num[0] != '\0')
                        sprintf (dsp_reset_num, ", %d", i);
                    else
                        sprintf (dsp_reset_num, "%d", i);

                    strcat (dsp_reset_all, dsp_reset_num);
                }
            }

            error ("Report audio DSP reset to fault manager\n");
#ifdef SUPPORT_SOUNDBAR
            sprintf (dsp_reset_msg, "DSP %s", dsp_reset_all);
#else
            sprintf (dsp_reset_msg, "Audio DSP Reset(Number : %s)", dsp_reset_all);
#endif
            fn_kdriver_notify (dsp_reset_msg);
        }

        aud_dsp_reset ();

        for (i = 0; i < number_of_dsp; i++)
            dsp_infos[i].same_cnt = 0;

    }
}

static void _check_gstc (void)
{
    unsigned int gstc = aud_hal_get_gstc ();

    trace ("gstc : %08x -> %08x\n", aud_dsp_pre_gtsc, gstc);

    /* check if gstc is runnging */
    if (gstc == aud_dsp_pre_gtsc)
    {
        error ("gst is not changed %08x\n", gstc);
    }
    aud_dsp_pre_gtsc = gstc;
}


static int _monitor_task (void *param)
{
#ifdef CHIP_TYPE_FPGA
    bool bInit = false;
#endif
    info ("Audio DSP monitor task is created\n");

#ifndef CHIP_TYPE_FPGA
    if (console_loglevel >= 7)  //KERN_DEBUG = 7, CONSOLE_LOGLEVEL_DEBUG = 10
    {
        noti ("monitor start timeout %6d mili-seconds\n", MONITOR_TASK_WAIT_TIMEOUT * 100);     //20 seconds
        msleep (MONITOR_TASK_WAIT_TIMEOUT * 100);
    }
#endif

    while (!kthread_should_stop ())
    {
        msleep (MONITOR_TASK_WAIT_TIMEOUT);
        if (bm_get_suspended ())
            continue;

        if (aud_monitor_dsp)
        {
#ifdef CHIP_TYPE_FPGA
            if (!bInit)
            {
                msleep (MONITOR_TASK_WAIT_TIMEOUT);
                bInit = true;
            }
#endif
            _check_heartbeat ();
        }

        if (aud_monitor_gstc)
            _check_gstc ();
    }

    info ("Audio Monitor Task - exit!\n");

    return 0;
}

int __init aud_dsp_control_init (void)
{
#ifndef CHIP_TYPE_FPGA
    noti ("console_loglevel %d\n", console_loglevel);

    if (console_loglevel >= 7)  //KERN_DEBUG = 7, CONSOLE_LOGLEVEL_DEBUG = 10
    {
        aud_dsp_boot_timeout *= 10;
        noti ("aud_dsp_boot_timeout  %6d mili-seconds\n", aud_dsp_boot_timeout);        //6 seconds
    }
#endif

    number_of_dsp = aud_hal_get_number_of_dsp ();
    monitor_task = kthread_run (_monitor_task, NULL, "audio-kdrv-task");

    return 0;
}

void __exit aud_dsp_control_exit (void)
{
    if (monitor_task)
    {
        kthread_stop (monitor_task);
        monitor_task = NULL;
    }
}

struct dsp_booting_arg
{
    unsigned int booting_mask;
    spinlock_t lock;
    struct wait_queue_head wq;
};

static int dsp_boot_done (void *param, int size, void *cb_param)
{
    struct dsp_booting_arg *arg = cb_param;
    ADEC_CORE_TYPE core;
    unsigned int dspnum;
    unsigned long flag;

    if (size != sizeof (core))
    {
        error ("wrong param size. %d\n", size);
        return -1;
    }

    core = *(ADEC_CORE_TYPE *) param;
    dspnum = core - ADEC_CORE_DSP0;

    info ("boot done. dsp%d\n", dspnum);
    spin_lock_irqsave (&arg->lock, flag);
    arg->booting_mask &= ~(1U << dspnum);
    spin_unlock_irqrestore (&arg->lock, flag);

    if (arg->booting_mask == 0)
        wake_up (&arg->wq);

    return 0;
}

// aud_dsp_halt() should be called before _aud_dsp_reset()
//
// TODO:
// bm_suspend(), bm_resume() 가 dsp reset 과 함께 관리되고 있다. aud_dsp_halt()
// _aud_dsp_reset(), 함수 사용할 때 bm_suspend(), bm_resume() 의 관계를
// 확인해야 한다.
int _aud_dsp_reset (void)
{
    struct dsp_booting_arg arg;
    int boot_done_event;
    int ret;
    int i;

    info ("reset dsp\n");

    memset (&arg, 0, sizeof (arg));
    init_waitqueue_head (&arg.wq);
    spin_lock_init (&arg.lock);

    boot_done_event = aimc_register_named_event (&arg, dsp_boot_done,
        AUD_MODID_REGISTRY (ADEC_CORE_ARM), "firmware-init-done", true);
    if (boot_done_event <= 0)
    {
        error ("aimc_register_named_event() failed %d.\n", boot_done_event);
        return -1;
    }

    // TODO:
    // 아래 동작 확인 필요
    aimc_stop ();
    aimc_start ();

    arg.booting_mask = 0;

    for (i = 0; i < number_of_dsp; i++)
    {
        fwload_load_backup_image (dsp_infos[i].name, "rom");
    }

    for (i = 0; i < number_of_dsp; i++)
    {
        unsigned long flag;

        if (dsp_infos[i].state == DSP_STATE_OFF)
            continue;

        spin_lock_irqsave (&arg.lock, flag);
        arg.booting_mask |= 1U << i;
        spin_unlock_irqrestore (&arg.lock, flag);

        fwload_reset (dsp_infos[i].name);
    }

    for (i = 0; i < number_of_dsp; i++)
    {
        fwload_unload_backup_image (dsp_infos[i].name, "rom");
    }

    info ("waiting dsps... 0x%x\n", arg.booting_mask);
    ret = wait_event_interruptible_timeout (arg.wq, (arg.booting_mask == 0),
        msecs_to_jiffies (aud_dsp_boot_timeout));
    if (ret == 0)
    {
        error ("dsp boot timeout. 0x%x\n", arg.booting_mask);
        aregs_dump_control_registers ();
        ret = -EIO;
    }
    else if (ret < 0)
        error ("dsp boot waiting interrupted. 0x%x\n", arg.booting_mask);

    aimc_unregister_named_event (boot_done_event);

    bm_resume ();

    // let heartbeat monitor reset the dsp
    for (i = 0; i < number_of_dsp; i++)
        if (dsp_infos[i].state != DSP_STATE_OFF)
            dsp_infos[i].state = DSP_STATE_RUN;

    aud_hal_set_axi_gk ();

    info ("done\n");

    return ret;
}

int aud_dsp_reset (void)
{
    int i = 0;

    aud_dsp_halt ();

    for (i = 0; i < number_of_dsp; i++)
        aimc_set_dsp_dead (i, false);   // now, kaimc can send command...

    return _aud_dsp_reset ();
}

void aud_dsp_turn_on (int dsp_num)
{
    struct dsp_booting_arg arg;
    int boot_done_event;
    int ret;
    unsigned long flag;

    info ("turn dsp%d on \n", dsp_num);

    if (dsp_num >= number_of_dsp)
    {
        error ("Invalid dsp number %d : %d", dsp_num, number_of_dsp);
        return;
    }

    if (dsp_infos[dsp_num].state != DSP_STATE_OFF)
    {
        error ("dsp is already on.\n");
        return;
    }

    memset (&arg, 0, sizeof (arg));
    init_waitqueue_head (&arg.wq);
    spin_lock_init (&arg.lock);

    boot_done_event = aimc_register_named_event (&arg, dsp_boot_done,
        AUD_MODID_REGISTRY (ADEC_CORE_ARM), "firmware-init-done", true);
    if (boot_done_event <= 0)
    {
        error ("aimc_register_named_event() failed %d.\n", boot_done_event);
        return;
    }

    arg.booting_mask = 0;

    spin_lock_irqsave (&arg.lock, flag);
    arg.booting_mask |= 1U << dsp_num;
    spin_unlock_irqrestore (&arg.lock, flag);

    dsp_infos[dsp_num].state = DSP_STATE_ON;

    fwload_reset (dsp_infos[dsp_num].name);

    info ("waiting dsps... 0x%x\n", arg.booting_mask);
    ret = wait_event_interruptible_timeout (arg.wq, (arg.booting_mask == 0),
        msecs_to_jiffies (aud_dsp_boot_timeout));
    if (ret == 0)
    {
        error ("dsp boot timeout. 0x%x\n", arg.booting_mask);
        aregs_dump_control_registers ();
        ret = -EIO;
    }
    else if (ret < 0)
        error ("dsp boot waiting interrupted. 0x%x\n", arg.booting_mask);

    aimc_unregister_named_event (boot_done_event);

    dsp_infos[dsp_num].state = DSP_STATE_RUN;

    info ("done\n");
}

void aud_dsp_turn_off (int dsp_num)
{
    info ("turn dsp%d off\n", dsp_num);

    if (dsp_num >= number_of_dsp)
    {
        error ("Invalid dsp number %d : %d", dsp_num, number_of_dsp);
        return;
    }

    dsp_infos[dsp_num].state = DSP_STATE_OFF;
    fwload_halt (dsp_infos[dsp_num].name, true);
    fwload_unload_image (dsp_infos[dsp_num].name, "rom");
}

void aud_dsp_halt (void)
{
    int i;

    aimc_unregister_bin_event_handler ();

    bm_suspend ();

    aud_hal_exit ();

    for (i = 0; i < number_of_dsp; i++)
    {
        struct _dsp_info *dsp_info = dsp_infos + i;

        dsp_info->state = (dsp_info->state == DSP_STATE_OFF) ? DSP_STATE_OFF : DSP_STATE_ON;
        fwload_halt (dsp_info->name, true);
    }

    info ("halt dsp\n");
}
