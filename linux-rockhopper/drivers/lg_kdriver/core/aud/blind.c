/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2017 by LG Electronics Inc.
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

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/poll.h>

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/err.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/mutex.h>
#include <linux/wait.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#include "regs.h"
#include "blind.h"
#include "ablind.h"
#include "proc.h"

#include "log.h"

logm_define (ablind, log_level_debug);
#define trace(fmt,args...)  logm_trace(ablind,fmt,##args)
#define debug(fmt,args...)  logm_debug(ablind,fmt,##args)
#define info(fmt,args...)   logm_info(ablind,fmt,##args)
#define noti(fmt,args...)   logm_noti(ablind,fmt,##args)
#define error(fmt,args...)  logm_error(ablind,fmt,##args)

struct wait_return
{
    wait_queue_head_t wq;
    int ret;
    atomic_t users;
    bool done;
};

struct item_data
{
    unsigned int item_id;

#define FLAG_REQUIRE_RESPONSE   (1<<0)
#define FLAG_RESPONSE           (1<<1)
    unsigned int flags;

    unsigned int args_cnt;
    unsigned int name_len;

    // size of args_cnt*sizeof(int)
    int args[0];

    // size of name_len
    //char name[0];

    // padding, 4 byte align
};

struct item
{
    struct list_head list;

    struct wait_return *waitret;

    unsigned int size;
    struct item_data data;
};


struct priv
{
    struct list_head list;

    pid_t pid;

    struct list_head items;
    struct mutex items_lock;
    wait_queue_head_t wq;

    char **can_handle;
    unsigned can_handle_num;

    struct wait_return *waiting;
};

static int last_item_id;
static LIST_HEAD (readers);
static DEFINE_MUTEX (readers_lock);

static int major;
module_param_named (ablind_major, major, int, 0644);

static int ablind_open (struct inode *inode, struct file *filp)
{
    struct priv *priv;

    priv = kzalloc (sizeof (*priv), GFP_KERNEL);
    if (!priv)
        return -ENOMEM;
    priv->can_handle_num = 32;
    priv->can_handle = kzalloc (sizeof (priv->can_handle[0]) * priv->can_handle_num, GFP_KERNEL);
    priv->pid = task_pid_nr (current);

    INIT_LIST_HEAD (&priv->items);
    mutex_init (&priv->items_lock);
    init_waitqueue_head (&priv->wq);

    mutex_lock (&readers_lock);
    list_add (&priv->list, &readers);
    mutex_unlock (&readers_lock);

    filp->private_data = priv;

    info ("new blind. %p\n", priv);

    return 0;
}

static int wakeup_return (struct priv *priv, struct wait_return *waitret, int ret)
{
    waitret->done = true;
    waitret->ret = ret;
    wake_up (&waitret->wq);

    debug ("return %d\n", waitret->ret);
    if (atomic_dec_return (&waitret->users) == 0)
        kfree (waitret);

    return 0;
}

static int ablind_release (struct inode *inode, struct file *filp)
{
    struct priv *priv = filp->private_data;
    struct item *item, *tmp;
    int i;

    info ("del blind. %p\n", priv);

    mutex_lock (&readers_lock);
    list_del (&priv->list);
    mutex_unlock (&readers_lock);

    if (priv->waiting)
    {
        wakeup_return (priv, priv->waiting, -1);
        priv->waiting = NULL;
    }

    mutex_lock (&priv->items_lock);
    list_for_each_entry_safe (item, tmp, &priv->items, list)
    {
        if (item->waitret)
            wakeup_return (priv, item->waitret, -1);

        list_del (&item->list);
        kfree (item);
    }
    mutex_unlock (&priv->items_lock);

    for (i = 0; priv->can_handle[i]; i++)
        kfree (priv->can_handle[i]);
    kfree (priv->can_handle);
    kfree (priv);

    return 0;
}

static unsigned int ablind_poll (struct file *filp, struct poll_table_struct *pt)
{
    struct priv *priv = filp->private_data;

    poll_wait (filp, &priv->wq, pt);

    if (!list_empty (&priv->items))
        return POLLIN | POLLRDNORM;

    return 0;
}

static ssize_t ablind_read (struct file *filp, char __user * data, size_t size, loff_t * offs)
{
    struct priv *priv = filp->private_data;
    int ret;
    struct item *item;

    debug ("..\n");
    ret = wait_event_interruptible (priv->wq, !list_empty (&priv->items));
    if (ret < 0)
    {
        debug ("interrupt.. %d\n", ret);
        return ret;
    }

    mutex_lock (&priv->items_lock);
    ret = 0;
    item = list_first_entry_or_null (&priv->items, struct item, list);
    if (item)
    {
        if (size < item->size)
        {
            info ("not enough memory. %zd, require %d\n", size, item->size);
            ret = -ENOMEM;
        }
        else
        {
            debug ("copy %p(%d)\n", item, item->size);
            ret = copy_to_user (data, &item->data, item->size);
            if (ret)
                ret = -EFAULT;
            else
            {
                ret = item->size;

                if (priv->waiting)
                    error ("previous waiting return not processed\n");
                priv->waiting = item->waitret;

                list_del (&item->list);
                kfree (item);
            }
        }
    }
    else
        ret = -ENODATA;
    mutex_unlock (&priv->items_lock);

    debug ("done.. %d\n", ret);
    return ret;
}

static ssize_t ablind_write (struct file *filp, const char __user * data, size_t size,
    loff_t * offs)
{
    return 0;
}

static long ablind_ioctl (struct file *file, unsigned int cmd, unsigned long arg)
{
    union
    {
        struct ablind_canhandle canhandle;
    } a;
    struct priv *priv = file->private_data;
    int ret = 0;

    if (_IOC_TYPE (cmd) != ABLIND_IOCTL_TYPE)
    {
        error ("invalid magic. magic=0x%02x\n", _IOC_TYPE (cmd));
        return -ENOIOCTLCMD;
    }

    if (_IOC_SIZE (cmd) > sizeof (a))
    {
        error ("invalid ioctl size. size %d max_size %ld\n", _IOC_SIZE (cmd), sizeof (a));
        return -ENOIOCTLCMD;
    }

    if (_IOC_DIR (cmd) & _IOC_WRITE)
    {
        int r;

        debug ("copy %d bytes\n", _IOC_SIZE (cmd));
        r = copy_from_user (&a, (void *) arg, _IOC_SIZE (cmd));
        if (r)
        {
            error ("copy_from_user failed\n");
            return -EFAULT;
        }
    }

    switch (cmd)
    {
        case ABLIND_IOCTL_SET_CANHANDLE:
        {
            int i;

            if (a.canhandle.len > 256)
            {
                ret = -EINVAL;
                break;
            }

            for (i = 0; i < priv->can_handle_num - 1; i++)
                if (!priv->can_handle[i])
                    break;
            if (i == priv->can_handle_num - 1)
            {
                char **n;

                priv->can_handle_num += 32;
                n = kzalloc (sizeof (priv->can_handle[0]) * priv->can_handle_num, GFP_KERNEL);
                for (i = 0; priv->can_handle[i]; i++)
                    n[i] = priv->can_handle[i];

                kfree (priv->can_handle);
                priv->can_handle = n;
            }

            priv->can_handle[i] = kmalloc (a.canhandle.len + 1, GFP_KERNEL);
            ret = copy_from_user (priv->can_handle[i], a.canhandle.n.name, a.canhandle.len);
            if (ret)
            {
                kfree (priv->can_handle[i]);
                priv->can_handle[i] = NULL;
                ret = -EFAULT;
            }
            priv->can_handle[i][a.canhandle.len] = 0;
            debug ("can handle, %d, \"%s\"\n", i, priv->can_handle[i]);

            break;
        }

        case ABLIND_IOCTL_SET_RETURN:
            if (priv->waiting)
            {
                ret = wakeup_return (priv, priv->waiting, (int) arg);
                priv->waiting = NULL;
            }
            break;

        default:
            error ("unkonwn ioctl command, %08x\n", cmd);
            ret = -ENOIOCTLCMD;
            break;
    }

    if (ret < 0)
        error ("ioctl error %d for cmd %08x\n", ret, cmd);

    if (ret >= 0 && _IOC_DIR (cmd) & _IOC_READ)
    {
        int r;

        r = copy_to_user ((void *) arg, &a, _IOC_SIZE (cmd));
        if (r)
        {
            error ("copy_to_user failed\n");
            ret = -EFAULT;
        }
    }


    return ret;
}

#ifdef CONFIG_COMPAT
static long ablind_compat_ioctl (struct file *file, unsigned int cmd, unsigned long arg)
{
    return ablind_ioctl (file, cmd, arg);
}
#endif

static struct file_operations ablind_fops = {
    .owner = THIS_MODULE,
    .open = ablind_open,
    .release = ablind_release,
    .poll = ablind_poll,
    .read = ablind_read,
    .write = ablind_write,
    .unlocked_ioctl = ablind_ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl = ablind_compat_ioctl,
#endif
};

static int _post (struct wait_return *wret, const char *name, int num_args, int *args)
{
    int name_len = strlen (name) + 1 /* tailing zero */ ;
    struct priv *priv;
    struct item *item;
    int item_size, data_size;
    int item_id;
    int posted = 0;
    int ret = 0;

    data_size = sizeof (struct item_data) + num_args * sizeof (int) + ALIGN (name_len, 4);
    item_size = offsetof (struct item, data) + data_size;
    info ("post \"%s\", item_size %d\n", name, item_size);

    mutex_lock (&readers_lock);
    last_item_id++;
    item_id = last_item_id;

    list_for_each_entry (priv, &readers, list)
    {
        int i;

        for (i = 0; priv->can_handle[i]; i++)
            if (!strcmp (name, priv->can_handle[i]))
                break;
        if (!priv->can_handle[i])
            continue;

        item = kzalloc (item_size, GFP_KERNEL);
        if (!item)
        {
            error ("no mem. \"%s\", %d\n", name, num_args);
            ret = -ENOMEM;
            break;
        }

        item->waitret = wret;
        item->size = data_size;
        item->data.item_id = item_id;
        item->data.flags = 0;
        item->data.args_cnt = num_args;
        item->data.name_len = name_len;

        for (i = 0; i < num_args; i++)
            item->data.args[i] = args[i];

        memcpy (item->data.args + num_args, name, name_len);

        if (wret)
            atomic_inc (&wret->users);

        mutex_lock (&priv->items_lock);
        list_add (&item->list, &priv->items);
        mutex_unlock (&priv->items_lock);

        posted++;
        wake_up (&priv->wq);

        if (wret)
            break;
    }
    mutex_unlock (&readers_lock);

    if (ret < 0)
        return ret;

    return posted;
}

/* returns:
 *    < 0 : internal error.
 *   == 0 : no one listening. not processed.
 *    > 0 : number of clients that posted.
 */
int ablind_post (const char *name, unsigned int num_args, ...)
{
    int ret;
    va_list ap;
    int *args = NULL;
    int i;

    if (num_args > 0)
    {
        args = kmalloc (sizeof (args[0]) * num_args, GFP_KERNEL);
        if (!args)
            return -ENOMEM;
    }

    va_start (ap, num_args);
    for (i = 0; i < num_args; i++)
        args[i] = va_arg (ap, int);
    va_end (ap);

    ret = _post (NULL, name, num_args, args);

    kfree (args);
    return ret;
}

EXPORT_SYMBOL (ablind_post);

/* returns:
 *    < 0 : internal error.
 *   == 0 : no one listening. not processed.
 *   == 1 : call handled by a client.
 *   == 2 : timeout.
 */
int ablind_callv_timeout (int timeout, int *callret, const char *name, int num_args, int *args)
{
    int ret;
    struct wait_return *waitret;

    waitret = kzalloc (sizeof (*waitret), GFP_KERNEL);
    if (!waitret)
        return -ENOMEM;

    init_waitqueue_head (&waitret->wq);
    atomic_set (&waitret->users, 1);

    info ("call %s ...\n", name);

    ret = _post (waitret, name, num_args, args);
    if (ret <= 0)
    {
        if (ret == 0)
            info ("no one cares\n");
        kfree (waitret);
        return ret;
    }

    if (timeout > 0)
    {
        debug ("waiting return.. timeout %d\n", timeout);
        ret = wait_event_interruptible_timeout (waitret->wq, waitret->done, timeout);
        if (ret <= 0)
        {
            if (ret == 0)
            {
                debug ("timeout.. %d\n", ret);
                ret = 2;
            }
            else
                debug ("interrupt.. %d\n", ret);
            if (atomic_dec_return (&waitret->users) == 0)
                kfree (waitret);
            return ret;
        }
    }
    else
    {
        debug ("waiting return..\n");
        ret = wait_event_interruptible (waitret->wq, waitret->done);
        if (ret < 0)
        {
            debug ("interrupt.. %d\n", ret);
            if (atomic_dec_return (&waitret->users) == 0)
                kfree (waitret);
            return ret;
        }
    }

    info ("got return. %d\n", waitret->ret);
    if (callret)
        *callret = waitret->ret;

    if (atomic_dec_return (&waitret->users) == 0)
        kfree (waitret);

    return 1;
}

EXPORT_SYMBOL (ablind_callv_timeout);

/* returns:
 *    < 0 : internal error.
 *   == 0 : no one listening. not processed.
 *   == 1 : call handled by a client.
 */
int ablind_callv (int *callret, const char *name, int num_args, int *args)
{
    return ablind_callv_timeout (0, callret, name, num_args, args);
}

EXPORT_SYMBOL (ablind_callv);

/* returns:
 *    < 0 : internal error.
 *   == 0 : no one listening. not processed.
 *   == 1 : call handled by a client.
 *   == 2 : timeout.
 */
int ablind_call_timeout (int timeout, int *callret, const char *name, int num_args, ...)
{
    int ret;
    va_list ap;
    int *args = NULL;
    int i;

    if (num_args > 0)
    {
        args = kmalloc (sizeof (args[0]) * num_args, GFP_KERNEL);
        if (!args)
            return -ENOMEM;
    }

    va_start (ap, num_args);
    for (i = 0; i < num_args; i++)
        args[i] = va_arg (ap, int);
    va_end (ap);

    ret = ablind_callv_timeout (timeout, callret, name, num_args, args);

    kfree (args);
    return ret;
}

EXPORT_SYMBOL (ablind_call_timeout);

/* returns:
 *    < 0 : internal error.
 *   == 0 : no one listening. not processed.
 *   == 1 : call handled by a client.
 */
int ablind_call (int *callret, const char *name, int num_args, ...)
{
    int ret;
    va_list ap;
    int *args = NULL;
    int i;

    if (num_args > 0)
    {
        args = kmalloc (sizeof (args[0]) * num_args, GFP_KERNEL);
        if (!args)
            return -ENOMEM;
    }

    va_start (ap, num_args);
    for (i = 0; i < num_args; i++)
        args[i] = va_arg (ap, int);
    va_end (ap);

    ret = ablind_callv (callret, name, num_args, args);

    kfree (args);
    return ret;
}

EXPORT_SYMBOL (ablind_call);

static int debug_call (int argc, const char **argv)
{
    int *args = NULL;
    int callret;
    int ret;
    int i;

    if (argc - 1 > 0)
    {
        args = kmalloc (sizeof (args[0]) * (argc - 1), GFP_KERNEL);
        if (!args)
            return -ENOMEM;
    }

    info ("call \"%s\"\n", argv[0]);
    ret = 0;
    for (i = 1; i < argc; i++)
    {
        if ((ret = kstrtoint (argv[i], 0, &args[i - 1])) < 0)
        {
            error ("cannot get argument. %s\n", argv[i]);
            break;
        }
        info ("  arg%d : %d(0x%x)\n", i, args[i - 1], args[i - 1]);
    }
    if (i != argc)
    {
        kfree (args);
        return ret;
    }

    ret = ablind_callv (&callret, argv[0], argc - 1, args);
    if (ret <= 0)
    {
        if (ret < 0)
            error ("call failed. %d\n", ret);
        else
            noti ("no one cares\n");
        kfree (args);
        return ret;
    }

    info ("return %d\n", callret);

    kfree (args);
    return callret;
}

static int show_readers (struct seq_file *m, void *data)
{
    struct priv *priv;

    mutex_lock (&readers_lock);
    list_for_each_entry (priv, &readers, list)
    {
        int i;

        seq_printf (m, "reader %p, pid %d:\n", priv, (int) priv->pid);
        seq_printf (m, "  can handle :\n");
        for (i = 0; priv->can_handle[i]; i++)
            seq_printf (m, "    \"%s\"\n", priv->can_handle[i]);
        seq_printf (m, "  waiting : %p\n", priv->waiting);
    }
    mutex_unlock (&readers_lock);

    return 0;
}

static struct class *ablind_cls;

int __init ablind_init (void)
{
    int err;

    err = register_chrdev (major, "ablind", &ablind_fops);
    if (err < 0)
    {
        error ("err %d\n", err);
        return err;
    }
    if (!major && err > 0)
        major = err;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
    ablind_cls = class_create ("ablind");
#else
    ablind_cls = class_create (THIS_MODULE, "ablind");
#endif
    device_create (ablind_cls, NULL, MKDEV (major, 0), NULL, "aud_blind");

    proc_create_data ("blind_call", 0640, aproc_root, &aaudio_args_fops, debug_call);
    proc_create_data ("blind_readers", 0440, aproc_root, &aaudio_seq_show_fops, show_readers);

    return 0;
}
