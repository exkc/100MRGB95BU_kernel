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
 *  lne kdriver main
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
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/proc_fs.h>
#include <linux/mutex.h>
#include <linux/kthread.h>
#include <linux/workqueue.h>
#include <linux/wait.h>
#include <linux/poll.h>
#include <linux/list.h>
#include <linux/mutex.h>

#include "os_util.h"
#include "base_device.h"
#include "hma_alloc.h"
#include "logm.h"

#include "lne.h"
#include "lne_drv.h"

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/
#define MODULE_NAME             "lne"
#define LNE_MAJOR               (0)
#define LNE_MINOR               (0)
#define LNE_NAME_PREFIX         "lne_"
#define LNE_HMA_POOL_NAME       "lne_buffer"
#define LNE_FIRMWARE_NULL_SIZE  (0x200)

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/
#define trace(fmt,args...)      logm_trace (lne_drv, fmt, ##args)
#define debug(fmt,args...)      logm_debug (lne_drv, fmt, ##args)
#define info(fmt,args...)       logm_info (lne_drv, fmt, ##args)
#define noti(fmt,args...)       logm_noti (lne_drv, fmt, ##args)
#define warn(fmt,args...)       logm_warning (lne_drv, fmt, ##args)
#define error(fmt,args...)      logm_error (lne_drv, fmt, ##args)

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
struct lne_buffer_info
{
    struct list_head list;

    struct lne_buffer buffer;
    unsigned int written;
};

struct lne_info
{
    struct lne_hw_control *hw_control;

    struct mutex lock;

    struct lne_run_param run_param;

    struct list_head input_list;
    struct list_head output_list;
    unsigned int input_size;
    unsigned int output_size;
    unsigned int input_size2;
    unsigned int output_size2;

    struct task_struct *task;
    wait_queue_head_t wait_input;
    wait_queue_head_t wait_output;
};

struct lne_hw_control
{
    struct lne_hw *lne_hw;

    struct platform_device pdev;

    struct lne_hw_control *next;
    char name[0];
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
logm_define (lne_drv, log_level_noti);

/*------------------------------------------------------------------------------
    Static Function Prototypes Declarations
------------------------------------------------------------------------------*/
static int _lne_drv_open (struct inode *inode, struct file *file);
static long _lne_drv_ioctl (struct file *file, unsigned int cmd, unsigned long arg);
#ifdef CONFIG_COMPAT
static long _lne_drv_compat_ioctl (struct file *file, unsigned int cmd, unsigned long arg);
#endif
static int _lne_drv_finalize (struct lne_info *lne_info);
static int _lne_drv_release (struct inode *inode, struct file *file);
static ssize_t _lne_drv_read (struct file *file, char __user * data, size_t size, loff_t * off);
static ssize_t _lne_drv_write (struct file *file, const char __user * data,
    size_t size, loff_t * off);
static unsigned int _lne_drv_poll (struct file *filp, struct poll_table_struct *pt);
static int _lne_probe (struct platform_device *pdev);
static int _lne_module_init (void);
static void _lne_module_exit (void);

/*------------------------------------------------------------------------------
    Static Variables
------------------------------------------------------------------------------*/
static struct proc_dir_entry *_lne_proc_root;
static struct dev_pm_ops _lne_pm_ops = {
};

static struct platform_driver _lne_platform_driver = {
    .probe = _lne_probe,
    .driver = {
            .name = MODULE_NAME,
            .pm = &_lne_pm_ops,
        },
};

static struct file_operations _lne_fops = {
    .open = _lne_drv_open,
    .unlocked_ioctl = _lne_drv_ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl = _lne_drv_compat_ioctl,
#endif
    .release = _lne_drv_release,
    .read = _lne_drv_read,
    .write = _lne_drv_write,
    .poll = _lne_drv_poll,
};

static struct cdev _cdev;
static struct lne_hw_control *lne_hw_controls = NULL;
static int _lne_major = LNE_MAJOR;
static int _lne_minor = LNE_MINOR;
static unsigned int lne_run_cnt = 1;
static unsigned int prev_lne_run_cnt = 0;
module_param (_lne_major, int, 0440);

/*==============================================================================
    Implementation Group
==============================================================================*/

int lne_hw_register (struct lne_hw *hw)
{
    struct lne_hw_control *control;
    dev_t dev;
    struct platform_device *pdev;
    int ret;

    /* register char. dev. */
    if (_lne_major)
    {
        dev = MKDEV (_lne_major, _lne_minor);
        ret = register_chrdev_region (dev, 1, MODULE_NAME);
    }
    else
    {
        ret = alloc_chrdev_region (&dev, _lne_minor, 1, MODULE_NAME);
        _lne_major = MAJOR (dev);
    }

    cdev_init (&_cdev, &_lne_fops);
    _cdev.owner = THIS_MODULE;

    ret = cdev_add (&_cdev, dev, 1);
    if (ret)
    {
        error ("adding lne device (%d.%d) failed, %d\n", MAJOR (dev), MINOR (dev), ret);
        return -EIO;
    }

    control = kzalloc (sizeof (struct lne_hw_control) + strlen (hw->name) +
        sizeof (LNE_NAME_PREFIX) + 1, GFP_KERNEL);
    if (!control)
    {
        error ("no mem\n");
        return -ENOMEM;
    }

    sprintf (control->name, LNE_NAME_PREFIX "%s", hw->name);
    control->lne_hw = hw;
    control->next = lne_hw_controls;
    lne_hw_controls = control;

    pdev = &control->pdev;
    pdev->name = control->name;
    pdev->id = PLATFORM_DEVID_NONE;
    device_initialize (&pdev->dev);
    pdev->driver_override = MODULE_NAME;
    pdev->dev.devt = MKDEV (_lne_major, _lne_minor);
    ret = platform_device_add (pdev);
    if (ret < 0)
    {
        error ("cannot add device %s\n", hw->name);
        return ret;
    }
    _lne_minor++;

    ret = hw->init (hw);
    if (ret < 0)
    {
        error ("%s init failed. %d\n", hw->name, ret);
    }

    info ("%s initialized.\n", hw->name);

    return ret;
}

EXPORT_SYMBOL (lne_hw_register);

static int _alloc_buffer (struct lne_buffer *buf, int size, const char *name)
{
    if (buf->mapped)
    {
        hma_unmap (buf->mapped);
    }

    if (buf->phys_addr)
    {
        hma_free (LNE_HMA_POOL_NAME, buf->phys_addr);
    }

    buf->phys_addr = hma_alloc_user (LNE_HMA_POOL_NAME, size, 4096, name);
    if (!buf->phys_addr)
    {
        error ("no mem for %s. %d\n", name, size);
        return -ENOMEM;
    }

    buf->mapped = hma_map (buf->phys_addr, size);
    if (!buf->mapped)
    {
        hma_free (LNE_HMA_POOL_NAME, buf->phys_addr);
        buf->phys_addr = 0;
        error ("map fail %s. %d\n", name, size);
        return -EFAULT;
    }

    buf->size = size;

    return 0;
}

static void _free_buffer (struct lne_buffer *buf)
{
    if (buf->mapped)
    {
        hma_unmap (buf->mapped);
        buf->mapped = NULL;
    }

    if (buf->phys_addr)
    {
        hma_free (LNE_HMA_POOL_NAME, buf->phys_addr);
        buf->phys_addr = 0;
    }
}

static void _copy_buffer (struct lne_buffer *to, struct lne_buffer *from)
{
    to->phys_addr = from->phys_addr;
    to->mapped = from->mapped;
    to->size = from->size;
}

static bool _lne_have_input (struct lne_info *lne_info)
{
    struct lne_buffer_info *buffer_info = NULL;

    mutex_lock (&lne_info->lock);
    buffer_info = list_first_entry_or_null (&lne_info->input_list, struct lne_buffer_info, list);
    if ((buffer_info == NULL) || (buffer_info->written < buffer_info->buffer.size))
    {
        mutex_unlock (&lne_info->lock);
        return false;
    }
    mutex_unlock (&lne_info->lock);

    return true;
}

static bool _lne_have_output (struct lne_info *lne_info)
{
    struct lne_buffer_info *buffer = NULL;

    mutex_lock (&lne_info->lock);
    buffer = list_first_entry_or_null (&lne_info->output_list, struct lne_buffer_info, list);
    if ((buffer == NULL) || (buffer->written == 0))
    {
        mutex_unlock (&lne_info->lock);
        return false;
    }

    mutex_unlock (&lne_info->lock);
    return true;
}

static int _lne_run_task (void *data)
{
    struct lne_info *lne_info = (struct lne_info *) data;
    struct lne_hw *lne_hw = lne_info->hw_control->lne_hw;

    info ("lne run task is created\n");

    while (!kthread_should_stop ())
    {
        struct lne_buffer_info *in_buf_info = NULL;
        struct lne_buffer_info *out_buf_info = NULL;

        if (wait_event_interruptible (lne_info->wait_input,
                _lne_have_input (lne_info) || kthread_should_stop ()) < 0)
        {
            info ("interrupt [%lu / %lu ]\n", _lne_have_input (lne_info), kthread_should_stop ());
            continue;
        }

        if (kthread_should_stop ())
        {
            break;
        }

        mutex_lock (&lne_info->lock);
        in_buf_info =
            list_first_entry_or_null (&lne_info->input_list, struct lne_buffer_info, list);
        if (in_buf_info == NULL)
        {
            mutex_unlock (&lne_info->lock);
            error ("Oops!!\n");
            continue;
        }

        out_buf_info = kzalloc (sizeof (struct lne_buffer_info), GFP_KERNEL);
        if (out_buf_info == NULL)
        {
            warn ("no memory\n");
            continue;
        }

        if (_alloc_buffer (&out_buf_info->buffer, lne_info->output_size, "output"))
        {
            warn ("output buffer allocation fail - %d\n", lne_info->output_size);
            kfree (out_buf_info);
            continue;
        }

        out_buf_info->written = 0;

        _copy_buffer (&lne_info->run_param.input, &in_buf_info->buffer);
        _copy_buffer (&lne_info->run_param.output, &out_buf_info->buffer);

        list_del (&in_buf_info->list);
        mutex_unlock (&lne_info->lock);

        if (lne_hw->run (lne_hw, &lne_info->run_param) == 0)
        {
            info ("run done\n");

            mutex_lock (&lne_info->lock);
            out_buf_info->written = lne_info->output_size;
            list_add_tail (&out_buf_info->list, &lne_info->output_list);
            mutex_unlock (&lne_info->lock);

            wake_up_interruptible (&lne_info->wait_output);
        }
        else
        {
            lne_hw->reset (lne_hw);

            _free_buffer (&out_buf_info->buffer);
            kfree (out_buf_info);
        }

        lne_run_cnt++;
        _free_buffer (&in_buf_info->buffer);
        kfree (in_buf_info);
        debug ("input buf mem is freed \n");
    }

    info ("lne run task - exit\n");

    return 0;

}

static int _lne_init (struct lne_info *lne_info, struct lne_init_param *param)
{
    int ret = 0;

    info ("initialize\n");

    /* 1. first network */
    if (param->firmware_size != 0 && param->weight_size != 0)
    {
        ret = _alloc_buffer (&lne_info->run_param.firmware,
            param->firmware_size + LNE_FIRMWARE_NULL_SIZE, "firmware");
        if (ret)
        {
            error ("firmware buffer allocation fail - %d\n", param->firmware_size);
            goto GOTO_ERROR;
        }

        ret = _alloc_buffer (&lne_info->run_param.weight, param->weight_size, "weight");
        if (ret)
        {
            error ("weight buffer allocation fail - %d\n", param->weight_size);
            goto GOTO_ERROR;
        }

        lne_info->input_size = param->number_of_input * sizeof (short);
        lne_info->output_size = param->number_of_output * sizeof (short);

        memset (lne_info->run_param.firmware.mapped, 0, LNE_FIRMWARE_NULL_SIZE);
        ret =
            copy_from_user (lne_info->run_param.firmware.mapped +
            LNE_FIRMWARE_NULL_SIZE, param->firmware, param->firmware_size);
        if (ret)
        {
            error ("copy_from_user failed\n");
            ret = -EFAULT;
            goto GOTO_ERROR;
        }

        ret = copy_from_user (lne_info->run_param.weight.mapped, param->weight, param->weight_size);
        if (ret)
        {
            error ("copy_from_user failed\n");
            ret = -EFAULT;
            goto GOTO_ERROR;
        }
    }


    /* 2. second network */
    if (param->firmware2_size != 0 && param->weight2_size != 0)
    {
        int dummy_size = 0x04;
        struct lne_hw *lne_hw = lne_info->hw_control->lne_hw;

        lne_info->input_size2 = param->number_of_input2;
        lne_info->output_size2 = param->number_of_output2;

        ret = _alloc_buffer (&lne_info->run_param.firmware2, param->firmware2_size, "firmware2");
        if (ret)
        {
            error ("firmware2 buffer allocation fail - %d\n", param->firmware2_size);
            goto GOTO_ERROR;
        }

        ret = _alloc_buffer (&lne_info->run_param.weight2, param->weight2_size, "weight2");
        if (ret)
        {
            error ("weight2 buffer allocation fail - %d\n", param->weight2_size);
            goto GOTO_ERROR;
        }

        ret = _alloc_buffer (&lne_info->run_param.output2, param->number_of_output2, "output2");
        if (ret)
        {
            error ("number_of_output2 buffer allocation fail - %d\n", param->number_of_output2);
            goto GOTO_ERROR;
        }

        ret = copy_from_user (lne_info->run_param.firmware2.mapped,
            param->firmware2, param->firmware2_size);
        if (ret)
        {
            error ("copy_from_user failed[%x]\n", ret);
            ret = -EFAULT;
            goto GOTO_ERROR;
        }

        ret = copy_from_user (lne_info->run_param.weight2.mapped,
            param->weight2, param->weight2_size);
        if (ret)
        {
            error ("copy_from_user failed\n");
            ret = -EFAULT;
            goto GOTO_ERROR;
        }

        // write firmware2/weight2 address
        lne_hw->set (&lne_info->run_param);
    }

    mutex_init (&lne_info->lock);
    lne_info->run_param.instance = lne_info;

    init_waitqueue_head (&lne_info->wait_input);
    init_waitqueue_head (&lne_info->wait_output);

    lne_info->task = kthread_run (_lne_run_task, lne_info, "lne_run");

    if (!lne_info->task)
    {
        error ("lne task creation fail\n");
        ret = -EFAULT;
    }

    info ("initialize done\n");

  GOTO_ERROR:
    if (ret < 0)
    {
        _free_buffer (&lne_info->run_param.firmware);
        _free_buffer (&lne_info->run_param.weight);
        _free_buffer (&lne_info->run_param.firmware2);
        _free_buffer (&lne_info->run_param.weight2);
        _free_buffer (&lne_info->run_param.output2);
    }

    return ret;
}

static int _lne_drv_open (struct inode *inode, struct file *file)
{
    int minor = iminor (inode);
    struct lne_info *lne_info;
    struct lne_hw_control *control = lne_hw_controls;

    info ("open %d \n", minor);

    lne_info = kzalloc (sizeof (struct lne_info), GFP_KERNEL);
    if (!lne_info)
    {
        error ("no mem\n");
        return -ENOMEM;
    }

    while (control)
    {
        if (MINOR (control->pdev.dev.devt) == minor)
        {
            lne_info->hw_control = control;
            break;
        }

        control = control->next;
    }

    if (!control)
    {
        error ("no such lne_hw for minor %d\n", minor);
        return -ENODEV;
    }

    INIT_LIST_HEAD (&lne_info->input_list);
    INIT_LIST_HEAD (&lne_info->output_list);

    file->private_data = lne_info;

    noti ("open done \n");

    return 0;
}

static long _lne_drv_ioctl (struct file *file, unsigned int cmd, unsigned long arg)
{
    struct lne_info *lne_info = file->private_data;
    union
    {
        struct lne_init_param init_param;
        unsigned int data;
    } param;
    int ret = 0;

    if (_IOC_TYPE (cmd) != LNE_IOCTL_TYPE)
    {
        error ("invalid magic. magic=0x%02x\n", _IOC_TYPE (cmd));
        return -ENOIOCTLCMD;
    }

    if (_IOC_DIR (cmd) & _IOC_WRITE)
    {
        debug ("copy %d bytes\n", _IOC_SIZE (cmd));
        ret = copy_from_user (&param, (void *) arg, _IOC_SIZE (cmd));
        if (ret)
        {
            error ("copy_from_user failed\n");
            return -EFAULT;
        }
    }

    switch (cmd)
    {
        case LNE_IOCTL_RESET:
            break;

        case LNE_IOCTL_INITIALIZE:
            ret = _lne_init (lne_info, &param.init_param);
            break;

        case LNE_IOCTL_FINALIZE:
            ret = _lne_drv_finalize (lne_info);
            break;

        case LNE_IOCTL_NET_ONOFF:
            ret = lne_info->hw_control->lne_hw->net_en (param.data);
            break;

        default:
            error ("unkonwn ioctl command, %08x\n", cmd);
            return -ENOIOCTLCMD;
    }

    if (ret < 0)
    {
        error ("ioctl error %d for cmd %08x\n", ret, cmd);
    }

    if (ret >= 0 && _IOC_DIR (cmd) & _IOC_READ)
    {
        debug ("copy %d bytes\n", _IOC_SIZE (cmd));
        ret = copy_to_user ((void *) arg, &param, _IOC_SIZE (cmd));
        if (ret)
        {
            error ("copy_to_user failed\n");
            return -EFAULT;
        }
    }

    return ret;
}

#ifdef CONFIG_COMPAT
static long _lne_drv_compat_ioctl (struct file *file, unsigned int cmd, unsigned long arg)
{
    long ret;

    switch (cmd)
    {
        case LNE_IOCTL_INITIALIZE:
        {
            struct lne_init_param arg_buf;

            ret = copy_from_user (&arg_buf, (void __user *) arg, sizeof (struct lne_init_param));
            if (ret)
            {
                return -EINVAL;
            }

            arg_buf.firmware = (const unsigned char *) (uintptr_t) arg_buf.compat_firmware;
            arg_buf.weight = (const unsigned char *) (uintptr_t) arg_buf.compat_weight;

            arg_buf.firmware2 = (const unsigned char *) (uintptr_t) arg_buf.compat_firmware2;
            arg_buf.weight2 = (const unsigned char *) (uintptr_t) arg_buf.compat_weight2;

            ret = copy_to_user ((void __user *) arg, &arg_buf, sizeof (struct lne_init_param));

            if (ret)
            {
                return -EINVAL;
            }

            break;
        }

        default:
        {
            break;
        }
    }

    ret = _lne_drv_ioctl (file, cmd, arg);

    return ret;
}
#endif

static int _lne_drv_finalize (struct lne_info *lne_info)
{
    struct lne_buffer_info *buffer, *temp;

    info ("finalize\n");
    if (lne_info == NULL)
    {
        info ("lne_info is null \n");
        return 0;
    }

#if 0
    if (lne_info->task)
    {
        kthread_stop (lne_info->task);
    }

    _free_buffer (&lne_info->run_param.firmware);
    _free_buffer (&lne_info->run_param.weight);
    _free_buffer (&lne_info->run_param.firmware2);
    _free_buffer (&lne_info->run_param.weight2);
    _free_buffer (&lne_info->run_param.output2);

    list_for_each_entry_safe (buffer, temp, &lne_info->input_list, list)
    {
        list_del (&buffer->list);

        _free_buffer (&buffer->buffer);
        kfree (buffer);
    }

    list_for_each_entry_safe (buffer, temp, &lne_info->output_list, list)
    {
        list_del (&buffer->list);

        _free_buffer (&buffer->buffer);
        kfree (buffer);
    }

    kfree (lne_info);
    lne_info = NULL;
#endif

    noti ("finalize done\n");

    return 0;
}

static int _lne_drv_release (struct inode *inode, struct file *file)
{
    struct lne_info *lne_info = file->private_data;
    struct lne_buffer_info *buffer, *temp;

    info ("release\n");

#if 1
    if (lne_info->task)
    {
        kthread_stop (lne_info->task);
    }

    _free_buffer (&lne_info->run_param.firmware);
    _free_buffer (&lne_info->run_param.weight);
    _free_buffer (&lne_info->run_param.firmware2);
    _free_buffer (&lne_info->run_param.weight2);
    _free_buffer (&lne_info->run_param.output2);

    list_for_each_entry_safe (buffer, temp, &lne_info->input_list, list)
    {
        list_del (&buffer->list);

        _free_buffer (&buffer->buffer);
        kfree (buffer);
    }

    list_for_each_entry_safe (buffer, temp, &lne_info->output_list, list)
    {
        list_del (&buffer->list);

        _free_buffer (&buffer->buffer);
        kfree (buffer);
    }

    kfree (lne_info);
    lne_info = NULL;

    noti ("release done\n");
#endif

    return 0;
}

static ssize_t _lne_drv_read (struct file *file, char __user * data, size_t size, loff_t * off)
{
    struct lne_info *lne_info = file->private_data;
    struct lne_buffer_info *buffer_info = NULL;
    void *read_pointer = NULL;

    if (*off != 0 || ((size % sizeof (short)) > 0))
    {
        warn ("Invalid parameters %lu %lld\n", size, *off);
        return -EINVAL;
    }

    mutex_lock (&lne_info->lock);
    buffer_info = list_first_entry_or_null (&lne_info->output_list, struct lne_buffer_info, list);
    if (buffer_info == NULL)
    {
        mutex_unlock (&lne_info->lock);
        return 0;
    }

    if (size >= buffer_info->written)
    {
        size = buffer_info->written;
        list_del (&buffer_info->list);
    }

    read_pointer = buffer_info->buffer.mapped;
    read_pointer += buffer_info->buffer.size - buffer_info->written;

    buffer_info->written -= size;
    mutex_unlock (&lne_info->lock);

    if (copy_to_user (data, read_pointer, size))
    {
        return -EFAULT;
    }

    if (buffer_info->written == 0)
    {
        _free_buffer (&buffer_info->buffer);
        kfree (buffer_info);
    }

    info ("Read done %lu\n", size);

    return size;
}

static ssize_t _lne_drv_write (struct file *file, const char __user * data,
    size_t size, loff_t * off)
{
    ssize_t ret_val = 0;
    struct lne_info *lne_info = file->private_data;
    struct lne_buffer_info *buffer_info = NULL;
    void *write_pointer = NULL;

    if (lne_run_cnt == prev_lne_run_cnt)
    {
        debug ("lne run count is not increased. prev/cur [%lu/%lu]\n",
            prev_lne_run_cnt, lne_run_cnt);
        return -1;
    }
    prev_lne_run_cnt = lne_run_cnt;

    if (*off != 0 || ((size % sizeof (short)) > 0))
    {
        warn ("Invalid parameters %lu %lld\n", size, *off);
        ret_val = -EINVAL;
        goto GOTO_ERROR;
    }

    mutex_lock (&lne_info->lock);
    buffer_info = list_last_entry (&lne_info->input_list, struct lne_buffer_info, list);

    if (list_empty (&lne_info->input_list) || (buffer_info->written >= buffer_info->buffer.size))
    {
        mutex_unlock (&lne_info->lock);

        buffer_info = kzalloc (sizeof (struct lne_buffer_info), GFP_KERNEL);
        if (buffer_info == NULL)
        {
            warn ("no memory\n");
            ret_val = -ENOMEM;
            goto GOTO_ERROR;
        }

        if (_alloc_buffer (&buffer_info->buffer, lne_info->input_size, "input"))
        {
            error ("input buffer allocation fail - %d\n", lne_info->input_size);
            ret_val = -ENOMEM;
            goto GOTO_ERROR;
        }

        buffer_info->written = 0;

        mutex_lock (&lne_info->lock);
        list_add_tail (&buffer_info->list, &lne_info->input_list);
        debug ("input buf mem is allocated \n");
    }

    write_pointer = buffer_info->buffer.mapped + buffer_info->written;

    if (size > (buffer_info->buffer.size - buffer_info->written))
    {
        size = buffer_info->buffer.size - buffer_info->written;
    }

    buffer_info->written += size;
    mutex_unlock (&lne_info->lock);

    if (copy_from_user (write_pointer, data, size))
    {
        if (buffer_info != NULL)
        {
            list_del (&buffer_info->list);
            _free_buffer (&buffer_info->buffer);
            kfree (buffer_info);
            buffer_info = NULL;
            debug ("copy_from_user fail \n");
            return -EFAULT;
        }
    }

    wake_up_interruptible (&lne_info->wait_input);

    info ("write done %lu\n", size);

    ret_val = size;

  GOTO_ERROR:
    if (ret_val < 0 && (buffer_info != NULL))
    {
        _free_buffer (&buffer_info->buffer);
        kfree (buffer_info);
        debug ("memory err occured. \n");
    }

    return ret_val;
}

static unsigned int _lne_drv_poll (struct file *file, struct poll_table_struct *pt)
{
    struct lne_info *lne_info = file->private_data;

    info ("poll\n");

    if (_lne_have_output (lne_info))
    {
        info ("poll done\n");

        return POLLIN | POLLRDNORM;
    }

    info ("poll wait\n");
    poll_wait (file, &lne_info->wait_output, pt);

    if (_lne_have_output (lne_info))
    {
        info ("poll done\n");

        return POLLIN | POLLRDNORM;
    }

    info ("poll done\n");

    return 0;
}

/**
 * probe lne device.
*/
static int _lne_probe (struct platform_device *pdev)
{
    struct lne_hw_control *control;
    struct lne_hw *hw;

    control = container_of (pdev, struct lne_hw_control, pdev);
    hw = control->lne_hw;

    noti ("%s probed\n", hw->name);

    return 0;
}

/**
 * initialize lne device.
*/
static int _lne_module_init (void)
{
    int ret;

    noti ("lne init.\n");

    _lne_proc_root = proc_mkdir (MODULE_NAME, NULL);

    ret = platform_driver_register (&_lne_platform_driver);
    if (ret)
    {
        error ("platform_driver_register failed, %d\n", ret);
        return ret;
    }

    return 0;
}

/**
 * cleanup lne device.
*/
static void _lne_module_exit (void)
{
    dev_t dev = MKDEV (_lne_major, LNE_MINOR);

    remove_proc_entry (MODULE_NAME, NULL);
    platform_driver_unregister (&_lne_platform_driver);
    cdev_del (&_cdev);
    unregister_chrdev_region (dev, 1);
}

module_init (_lne_module_init);
module_exit (_lne_module_exit);

MODULE_AUTHOR ("LGE");
MODULE_DESCRIPTION ("LNE driver");
MODULE_LICENSE ("GPL");
