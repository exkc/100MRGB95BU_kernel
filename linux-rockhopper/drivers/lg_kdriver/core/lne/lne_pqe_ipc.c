/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2020 by LG Electronics Inc.
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
 *  pqe shared lne device driver
 *
 *  author      Youngwoo Jin ( youngwoo.jin@lge.com )
 *  version     1.0
 *  date        2020.06.18
 *
 */

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/completion.h>
#include <linux/workqueue.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/ktime.h>
#include <asm/io.h>

#include "hma_alloc.h"
#include "logm.h"

#include "lne_drv.h"

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/
#define QUEUE_LENGTH        (4)
#define CHECK_PERIOD        (5)
#define DONE_TIMEOUT        (1000)      // ms

#define PQE_STATUS_READY    (0xABCD1234)
#define PQE_STATUS_BUSY     (0xABCD1235)
#define PQE_STATUS_WAIT_SRC (0xABCD1236)
#define PQE_STATUS_WAIT_WR  (0xABCD1237)
#define PQE_STATUS_LOCKUP   (0xABCD1238)

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/
#define trace(fmt,args...)  logm_trace (lne_pqe_ipc, fmt, ##args)
#define debug(fmt,args...)  logm_debug (lne_pqe_ipc, fmt, ##args)
#define info(fmt,args...)   logm_info (lne_pqe_ipc, fmt, ##args)
#define noti(fmt,args...)   logm_noti (lne_pqe_ipc, fmt, ##args)
#define warn(fmt,args...)   logm_warning (lne_pqe_ipc, fmt, ##args)
#define error(fmt,args...)  logm_error (lne_pqe_ipc, fmt, ##args)

#define next_offset(_offset)    ((_offset + 1) % QUEUE_LENGTH)

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
struct lne_run
{
    unsigned int firmware_address;
    unsigned int weight_address;
    unsigned int input_address;
    unsigned int output_address;
};

struct lne_interface
{
    // MCU to CPU
    unsigned int magic_header;
    unsigned int read_offset;

    // CPU to MCU
    unsigned int write_offset;
    struct lne_run lne_run_queue[QUEUE_LENGTH];
    struct lne_run lne_run_queue2;      // for second firmware
    unsigned int net_onoff;
};

struct buffer
{
    void *buffer;
    unsigned int size;
};

struct lne_hw_pqe_ipc
{
    bool ipc_ready;
    unsigned int read_offset;
    unsigned int write_offset;
    bool done[QUEUE_LENGTH];

    bool timeout;

    struct mutex lock;
    struct work_struct work;
    wait_queue_head_t wait_done;
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
logm_define (lne_pqe_ipc, log_level_noti);

/*------------------------------------------------------------------------------
    Static Function Prototypes Declarations
------------------------------------------------------------------------------*/
static int _lne_pqe_ipc_module_init (void);
static void _lne_pqe_ipc_module_exit (void);
static int _lne_pqe_ipc_init (struct lne_hw *hw);
static int _lne_pqe_ipc_reset (struct lne_hw *hw);
static int _lne_pqe_ipc_run (struct lne_hw *hw, struct lne_run_param *param);
static int _lne_pqe_ipc_set (struct lne_run_param *param);
static int _lne_pqe_ipc_net_en (unsigned int onoff);

/*------------------------------------------------------------------------------
    Static Variables
------------------------------------------------------------------------------*/
static struct lne_interface *_lne_ipc;
static struct lne_hw_pqe_ipc _lne_hw_pqe_ipc;
static struct lne_hw _lne_pqe_ipc = {
    .name = "pqe_ipc",
    .init = _lne_pqe_ipc_init,
    .reset = _lne_pqe_ipc_reset,
    .run = _lne_pqe_ipc_run,
    .set = _lne_pqe_ipc_set,
    .net_en = _lne_pqe_ipc_net_en,
    .private = (void *) &_lne_hw_pqe_ipc,
};

/*==============================================================================
    Implementation Group
==============================================================================*/

static void _lne_pqe_ipc_work (struct work_struct *work)
{
    struct lne_hw_pqe_ipc *lne_hw_pqe_ipc =
        container_of ((struct work_struct *) work, struct lne_hw_pqe_ipc, work);
    struct timespec64 timeout, now;

    ktime_get_ts64  (&timeout);
    timespec64_add_ns  (&timeout, DONE_TIMEOUT * 1000000);

    trace ("work start\n");

    mutex_lock (&lne_hw_pqe_ipc->lock);
    do
    {
        unsigned int prev_read_offset;

        mutex_unlock (&lne_hw_pqe_ipc->lock);

        msleep (CHECK_PERIOD);

        trace ("check: wr:%d(%d) rd:%d(%d)\n",
            lne_hw_pqe_ipc->write_offset, _lne_ipc->write_offset,
            lne_hw_pqe_ipc->read_offset, _lne_ipc->read_offset);

        mutex_lock (&lne_hw_pqe_ipc->lock);
        prev_read_offset = lne_hw_pqe_ipc->read_offset;

        if (lne_hw_pqe_ipc->write_offset != _lne_ipc->write_offset)
        {
            _lne_ipc->write_offset = lne_hw_pqe_ipc->write_offset;
        }

        if (prev_read_offset != _lne_ipc->read_offset)
        {
            lne_hw_pqe_ipc->read_offset = _lne_ipc->read_offset;

            do
            {
                prev_read_offset = next_offset (prev_read_offset);
                lne_hw_pqe_ipc->done[prev_read_offset] = true;
            }
            while (prev_read_offset != lne_hw_pqe_ipc->read_offset);

            wake_up_interruptible (&lne_hw_pqe_ipc->wait_done);

            ktime_get_ts64  (&timeout);
            timespec64_add_ns  (&timeout, DONE_TIMEOUT * 1000000);
        }

        ktime_get_ts64 (&now);
        if (timespec64_compare (&timeout, &now) < 0)
        {
            info ("timeout\n");

            lne_hw_pqe_ipc->timeout = true;
            lne_hw_pqe_ipc->write_offset = lne_hw_pqe_ipc->read_offset;
            wake_up_interruptible (&lne_hw_pqe_ipc->wait_done);
            break;
        }
    }
    while (lne_hw_pqe_ipc->read_offset != lne_hw_pqe_ipc->write_offset);
    mutex_unlock (&lne_hw_pqe_ipc->lock);

    trace ("work end\n");
}

static int _lne_pqe_ipc_init (struct lne_hw *hw)
{
    struct lne_hw_pqe_ipc *lne_hw_pqe_ipc = (struct lne_hw_pqe_ipc *) hw->private;

    info ("init %s", hw->name);

    mutex_init (&lne_hw_pqe_ipc->lock);
    INIT_WORK (&lne_hw_pqe_ipc->work, _lne_pqe_ipc_work);
    init_waitqueue_head (&lne_hw_pqe_ipc->wait_done);
    lne_hw_pqe_ipc->ipc_ready = false;

    if (_lne_ipc->write_offset >= QUEUE_LENGTH)
    {
        _lne_ipc->write_offset = 0;
    }

    if ((_lne_ipc->read_offset < QUEUE_LENGTH) && (_lne_ipc->read_offset == _lne_ipc->write_offset))
    {
        lne_hw_pqe_ipc->read_offset = _lne_ipc->read_offset;
        lne_hw_pqe_ipc->write_offset = _lne_ipc->write_offset;
        lne_hw_pqe_ipc->ipc_ready = true;

        noti ("ipc ready\n");
    }

    info ("init done\n");

    return 0;
}

static int _lne_pqe_ipc_reset (struct lne_hw *hw)
{
    struct lne_hw_pqe_ipc *lne_hw_pqe_ipc = (struct lne_hw_pqe_ipc *) hw->private;

    info ("set %s read/write pointer: %d/%d\n", hw->name, _lne_ipc->read_offset,
        _lne_ipc->write_offset);

    _lne_ipc->write_offset = _lne_ipc->read_offset;

    if (_lne_ipc->write_offset >= QUEUE_LENGTH)
    {
        lne_hw_pqe_ipc->ipc_ready = false;
        _lne_ipc->write_offset = 0;

        warn ("ipc not ready\n");
    }

    mutex_lock (&lne_hw_pqe_ipc->lock);
    lne_hw_pqe_ipc->read_offset = _lne_ipc->read_offset;
    lne_hw_pqe_ipc->write_offset = _lne_ipc->write_offset;
    mutex_unlock (&lne_hw_pqe_ipc->lock);

    info ("reset done\n");

    return 0;
}

static int _lne_pqe_ipc_run (struct lne_hw *hw, struct lne_run_param *param)
{
    struct lne_hw_pqe_ipc *lne_hw_pqe_ipc = (struct lne_hw_pqe_ipc *) hw->private;
    struct lne_run *lne_run_queue;
    bool run_work = false;
    unsigned int next_write_offset;

    debug ("run %s\n", hw->name);

    mutex_lock (&lne_hw_pqe_ipc->lock);
    if (lne_hw_pqe_ipc->ipc_ready == false)
    {
        if ((_lne_ipc->read_offset < QUEUE_LENGTH) &&
            (_lne_ipc->read_offset == _lne_ipc->write_offset))
        {
            lne_hw_pqe_ipc->read_offset = _lne_ipc->read_offset;
            lne_hw_pqe_ipc->write_offset = _lne_ipc->write_offset;
            lne_hw_pqe_ipc->ipc_ready = true;

            noti ("ipc ready\n");
        }
        else
        {
            mutex_unlock (&lne_hw_pqe_ipc->lock);

            warn ("run fail - ipc not ready\n");
            return -1;
        }
    }

    while (next_offset (lne_hw_pqe_ipc->write_offset) == lne_hw_pqe_ipc->read_offset)
    {
        mutex_unlock (&lne_hw_pqe_ipc->lock);

        msleep (1);

        mutex_lock (&lne_hw_pqe_ipc->lock);
    }

    if (lne_hw_pqe_ipc->write_offset == lne_hw_pqe_ipc->read_offset)
    {
        run_work = true;
    }

    next_write_offset = next_offset (lne_hw_pqe_ipc->write_offset);

    lne_run_queue = &_lne_ipc->lne_run_queue[next_write_offset];

    lne_run_queue->firmware_address = param->firmware.phys_addr;
    lne_run_queue->weight_address = param->weight.phys_addr;
    lne_run_queue->input_address = param->input.phys_addr;
    lne_run_queue->output_address = param->output.phys_addr;

    lne_hw_pqe_ipc->write_offset = next_write_offset;
    lne_hw_pqe_ipc->done[next_write_offset] = false;


    if (run_work)
    {
        lne_hw_pqe_ipc->timeout = false;
        schedule_work (&lne_hw_pqe_ipc->work);
    }

    trace ("wait complete: %d/%d\n", lne_hw_pqe_ipc->read_offset, lne_hw_pqe_ipc->write_offset);

    while (!lne_hw_pqe_ipc->done[next_write_offset])
    {
        mutex_unlock (&lne_hw_pqe_ipc->lock);

        if (wait_event_interruptible (lne_hw_pqe_ipc->wait_done,
                lne_hw_pqe_ipc->done[next_write_offset] || lne_hw_pqe_ipc->timeout))
        {
            warn ("interrupt...\n");
            return -1;
        }

        debug ("wakeup %d\n", lne_hw_pqe_ipc->done[next_write_offset]);

        mutex_lock (&lne_hw_pqe_ipc->lock);
        if (lne_hw_pqe_ipc->timeout)
        {
            unsigned int pqe_status;

            mutex_unlock (&lne_hw_pqe_ipc->lock);

            pqe_status = _lne_ipc->magic_header;

            switch (pqe_status)
            {
                case PQE_STATUS_READY:
                case PQE_STATUS_WAIT_WR:
                case PQE_STATUS_LOCKUP:
                    info ("timeout: no response(0x%08X/%d/%d)\n", pqe_status,
                        _lne_ipc->read_offset, _lne_ipc->write_offset);
                    break;

                case PQE_STATUS_BUSY:
                    info ("timeout: busy\n");
                    break;

                case PQE_STATUS_WAIT_SRC:
                    info ("timeout: no input\n");
                    break;

                default:
                    info ("timeout: invalid header(0x%08X)\n", pqe_status);
                    break;
            }

            return -1;
        }
    }
    mutex_unlock (&lne_hw_pqe_ipc->lock);

    debug ("run done\n");

    return 0;
}

static int _lne_pqe_ipc_set (struct lne_run_param *param)
{
    _lne_ipc->lne_run_queue2.firmware_address = param->firmware2.phys_addr;
    _lne_ipc->lne_run_queue2.weight_address = param->weight2.phys_addr;
    _lne_ipc->lne_run_queue2.output_address = param->output2.phys_addr;
    _lne_ipc->net_onoff = 0;

    debug ("queue2 addr set done\n");
    return 0;
}

static int _lne_pqe_ipc_net_en (unsigned int onoff)
{
    _lne_ipc->net_onoff = onoff;

    debug ("net_onoff is set to [%d]\n", _lne_ipc->net_onoff);
    return 0;
}

/**
 * initialize pqe shared lne device.
*/
static int _lne_pqe_ipc_module_init (void)
{
    int ret;
    phys_addr_t base_addr = 0x00;
    int size = 0;

    noti ("initialize LNE PQE IPC device\n");

    ret = hma_pool_info ("pqe-lne", &base_addr, &size);
    if (ret < 0)
    {
        error ("hma_pool_info(\"pqe-lne\") failed. %d\n", ret);
    }

    if (size < sizeof (struct lne_interface))
    {
        error ("not enough interface memory size %d %lu\n", size, sizeof (struct lne_interface));
        return -1;
    }

    _lne_ipc = (struct lne_interface *) hma_map (base_addr, sizeof (struct lne_interface));
    if (!_lne_ipc)
    {
        error ("ioremap for shared memory fail\n");
        return -1;
    }

    lne_hw_register (&_lne_pqe_ipc);

    return 0;
}

/**
 * cleanup pqe lne device.
*/
static void _lne_pqe_ipc_module_exit (void)
{
    noti ("exit LNE shared device\n");

    if (_lne_ipc)
    {
        hma_unmap ((void *) _lne_ipc);
    }

    return;
}

module_init (_lne_pqe_ipc_module_init);
module_exit (_lne_pqe_ipc_module_exit);

MODULE_AUTHOR ("LGE");
MODULE_DESCRIPTION ("PQE Shared LNE driver");
MODULE_LICENSE ("GPL");
