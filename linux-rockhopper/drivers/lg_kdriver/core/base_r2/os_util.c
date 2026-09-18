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

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/ctype.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/vmalloc.h>
#include <linux/slab.h>
#include <linux/time.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/hardirq.h>
#include <linux/dma-mapping.h>
#include <linux/version.h>
#include <linux/mm.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/cacheflush.h>

#include "debug_util.h"
#include "os_util.h"
#include "debug_util.h"
#include "base_device.h"
#include "logm_drv.h"

#include "base_impl.h"

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/

/**
 * system failure processing
 *
 * This function is called when some system failure should be reported during runtime.
 * for debug stage, this function will show some useful information for debug.
 * for release stage, this function will reboot(?) the whole system.
 *
 * @note current implementation just report error message and do nothing.
 *
 */
#define OS_FAILURE()        do { } while(0)

#define OS_CHECK_ERROR(__checker,__if_action,fmt,args...)   \
            __CHECK_IF_ERROR(__checker, lg1k_logm_error, __if_action, fmt, ##args )

/*
 * critical resource lock/unlock
 */

#define MSEC2TICKS(msec)            ( ( (msec) * HZ) / 1000 )

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
struct os_device_private
{
    umode_t mode;
};

/*----------------------------------------------------------------------------------------
    Function Prototype Declarations
----------------------------------------------------------------------------------------*/
void* _vmap_phys(phys_addr_t addr, unsigned long size, pgprot_t pgprot);
void _vunmap_phys(void* addr);

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/
int lg1k_core_logm_fd = -1;
EXPORT_SYMBOL(lg1k_core_logm_fd);

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
// test_cmdline is used to parse variable or token for debug/test
static char* test_cmdline = NULL;
module_param(test_cmdline, charp, 0000);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,2,0)
static char* kdrv_dev_node_name(const struct device* dev, umode_t* mode)
#else
static char* kdrv_dev_node_name(struct device* dev, umode_t* mode)
#endif
{
    struct os_device_private* priv = dev_get_drvdata(dev);

    if (priv && priv->mode)
        *mode = priv->mode;

    return kasprintf(GFP_KERNEL, "lg/%s", dev_name(dev));
}

static struct class lg1k_kdrv_class = {  .name = "lg",
        .devnode = kdrv_dev_node_name,
    };

/*========================================================================================
    Implementation Group
========================================================================================*/
void    lg1k_os_frwk_init(void)
{
    int rc;

    /* create device class */
    rc = class_register(&lg1k_kdrv_class);

    if (rc)
    {
        pr_err("can't register class\n");
        return;
    }

    /* initialize logm driver to get log service */
    LOGM_Init();

    /* open debug(logm) handler */
    lg1k_core_logm_fd = LOGM_ObjRegister("lg1k-core");

    if (lg1k_core_logm_fd < 0)
    {
        pr_err("can't alloc logm(lg1k-core) system\n");
        return;
    }

    LOGM_ObjBitMaskEnable(lg1k_core_logm_fd, LX_LOGM_LEVEL_ERROR);
    LOGM_ObjBitMaskEnable(lg1k_core_logm_fd, LX_LOGM_LEVEL_WARNING);
    LOGM_ObjBitMaskEnable(lg1k_core_logm_fd, LX_LOGM_LEVEL_NOTI);

    lg1k_logm_noti("os_frwk initialized\n");

    /* initialize memcfg */
}

void  lg1k_os_frwk_cleanup(void)
{
    LOGM_ObjDeregister("lg1k-core");
    LOGM_Cleanup();


    /* destroy device class */
}

/*========================================================================================
    DEVICE REGISTER
========================================================================================*/
void     OS_CreateDeviceClass_mode(dev_t dev, umode_t mode, const char* fmt, ...)
{
    struct os_device_private* priv;
    va_list args;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,9,0)
    char buffer[128];
#endif

    priv = kzalloc(sizeof(*priv), GFP_KERNEL);

    if (!priv)
    {
        printk(KERN_ERR "%s.%d: no memory.\n", __func__, __LINE__);
        return;
    }

    priv->mode = mode;

    va_start(args, fmt);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,9,0)
    vsprintf(buffer, fmt, args);
    device_create(&lg1k_kdrv_class, NULL, dev, priv, buffer);
#else
    device_create_vargs(&lg1k_kdrv_class, NULL, dev, priv, fmt, args);
#endif

}
EXPORT_SYMBOL(OS_CreateDeviceClass_mode);

void     OS_CreateDeviceClass(dev_t dev, const char* fmt, ...)
{
    struct os_device_private* priv;
    va_list args;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,9,0)
    char buffer[128];
#endif

    priv = kzalloc(sizeof(*priv), GFP_KERNEL);

    if (!priv)
    {
        printk(KERN_ERR "%s.%d: no memory.\n", __func__, __LINE__);
        return;
    }

    priv->mode = 0666;

    va_start(args, fmt);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,9,0)
    vsprintf(buffer, fmt, args);
    device_create(&lg1k_kdrv_class, NULL, dev, priv, buffer);
#else
    device_create_vargs(&lg1k_kdrv_class, NULL, dev, priv, fmt, args);
#endif
}
EXPORT_SYMBOL(OS_CreateDeviceClass);

void     OS_DestroyDeviceClass(dev_t dev)
{
    device_destroy(&lg1k_kdrv_class, dev);
}
EXPORT_SYMBOL(OS_DestroyDeviceClass);

/*========================================================================================
    MUTEX OS API IMPLEMENTATION
========================================================================================*/
void os_mutex_init(OS_SEM_T* pSem, const char* name)
{
    OS_CHECK_ERROR(NULL == pSem, return, "null mutex error\n");

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39)
    init_MUTEX(&(pSem->sem));
#else
    sema_init(&(pSem->sem), 1);
#endif
    init_waitqueue_head(&(pSem->wq));

    if (name)
    {
        pSem->name = os_strdup(name, LX_STR_MAX);
    }
    else
    {
        pSem->name = kasprintf(GFP_KERNEL, "mtx-%04d", current->pid);
    }

    lg1k_logm_os_debug("mutex(%s) init ok\n", pSem->name);
}
EXPORT_SYMBOL(os_mutex_init);

static bool os_mutex_try_lock(OS_SEM_T* pSem)
{
    int ret = down_trylock(&(pSem->sem));

    return (!ret) ? true : false;
}

int os_mutex_lock(OS_SEM_T* pSem, u32 timeout)
{
    int     ret = RET_OK;

    OS_CHECK_ERROR(NULL == pSem, return RET_ERROR, "null mutex error\n");

    lg1k_logm_os_debug("mutex(%s) timeout=%dms, isr_ctx=%s\n", pSem->name, timeout, (in_interrupt()) ? "true" : "false");

    if (in_interrupt() && timeout > 0)
    {
        lg1k_logm_error("mutex(%s) ignore timeout(%d) in interrupt context\n", pSem->name, timeout);
        timeout = 0;
    }

    if (timeout == 0x0)
    {
        int rc = down_trylock(&(pSem->sem));

        if (rc)
        {
            lg1k_logm_warn("mutex(%s) timeout. case#1. set=RET_TIMEOUT\n", pSem->name);

            ret = RET_TIMEOUT;
        }
    }
    else if (timeout == OS_INFINITE_WAIT)
    {
        down(&(pSem->sem));

        lg1k_logm_os_debug("mutex(%s) lock ok. case#1\n", pSem->name);

        ret = RET_OK;
    }
    else
    {
        int rc;

        rc = wait_event_interruptible_timeout(pSem->wq, os_mutex_try_lock(pSem), usecs_to_jiffies(timeout * 1000));

        if (rc > 0) /* ok */
        {
            lg1k_logm_os_debug("mutex(%s) lock ok. case#2\n", pSem->name);

            ret = RET_OK;
        }
        else if (rc == 0) /* timeout */
        {
            lg1k_logm_warn("mutex(%s) timeout. case#2, set=RET_TIMEOUT\n", pSem->name);

            ret = RET_TIMEOUT;
        }
        else /* error */
        {
            lg1k_logm_error("mutex(%s) abort by signal. ret=RET_ERROR\n", pSem->name);

            ret = RET_ERROR;
        }
    }

    return ret;
}
EXPORT_SYMBOL(os_mutex_lock);

void os_mutex_unlock(OS_SEM_T* pSem)
{
    OS_CHECK_ERROR(NULL == pSem, return, "null mutex error\n");

    lg1k_logm_os_debug("mutex(%s) unlock ok\n", pSem->name);

    /* unlock mutex first and wake up the sleeping task */
    up(&(pSem->sem));

    wake_up_interruptible_all(&(pSem->wq));
}
EXPORT_SYMBOL(os_mutex_unlock);

/*========================================================================================
    EVENT OS API IMPLEMENTATION
========================================================================================*/
void os_event_init(OS_EVENT_T* pEvent, const char* name)
{
    OS_CHECK_ERROR(NULL == pEvent, return, "null event error\n");

    pEvent->ev = 0x0;
    init_waitqueue_head(&(pEvent->wq));
    spin_lock_init(&pEvent->spinlock);

    if (name)
    {
        pEvent->name = os_strdup(name, LX_STR_MAX);
    }
    else
    {
        pEvent->name = kasprintf(GFP_KERNEL, "ev-%04d", current->pid);
    }
}
EXPORT_SYMBOL(os_event_init);

static bool os_event_fetch(OS_EVENT_T* pEvent, u32 ev, u32* rEv, u32 option)
{
    ULONG flags;
    bool ret;

    spin_lock_irqsave(&pEvent->spinlock, flags);

    if (pEvent->ev)
    {
        // check if any required event is received
        if ((option == OS_EVENT_RECEIVE_ANY) && (pEvent->ev & ev))
        {
            *rEv = (pEvent->ev & ev);
            pEvent->ev &= ~(pEvent->ev & ev);
            ret = true;
        }
        // check if all required event is received
        else if ((option == OS_EVENT_RECEIVE_ALL) && ((pEvent->ev & ev) == ev))
        {
            *rEv = ev;
            pEvent->ev &= ~ev;
            ret = true;
        }
        // requested events are not fully received
        else
        {
            ret = false;
        }
    }
    // any event is not found
    else
    {
        ret = false;
    }

    spin_unlock_irqrestore(&pEvent->spinlock, flags);

    return ret;
}

int os_event_recv(OS_EVENT_T* pEvent, u32 ev, u32* rEv, u32 option, u32 timeout)
{
    int             ret;
    int             rc;

    *rEv = 0x0;
    ret  = 0;

    OS_CHECK_ERROR(NULL == pEvent, return RET_ERROR, "null event error\n");

    lg1k_logm_os_debug("event(%s) req_event=0x%08x, option=0x%x, timeout=%d\n",
                       pEvent->name, ev, option, timeout);

    if (timeout)
    {
        if (in_interrupt())
        {
            lg1k_logm_error("event(%s) you can't use timoeut(%d) inside intrrupt context\n", pEvent->name, timeout);
            return RET_ERROR;
        }
    }
    // handle no-wait mode, it may be inside ISR handler
    else
    {
        BOOLEAN rc = os_event_fetch(pEvent, ev, rEv, option);

        lg1k_logm_os_debug("event(%s) event fetch %s\n", pEvent->name, (rc) ? "ok" : "fail");

        return (rc) ? RET_OK : RET_TIMEOUT;
    }

    if (signal_pending(current))
    {
        return RET_INTR_CALL;
    }

    if (timeout < 10) timeout = 5;

    rc = wait_event_interruptible_timeout(pEvent->wq, os_event_fetch(pEvent, ev, rEv, option), msecs_to_jiffies(timeout));

    return (rc > 0) ? RET_OK : RET_TIMEOUT;
}
EXPORT_SYMBOL(os_event_recv);

void os_event_send(OS_EVENT_T* pEvent, u32 ev)
{
    ULONG flags;

    OS_CHECK_ERROR(NULL == pEvent, return, "null event error\n");

    spin_lock_irqsave(&pEvent->spinlock, flags);
    pEvent->ev |= ev;
    spin_unlock_irqrestore(&pEvent->spinlock, flags);

    wake_up_interruptible(&pEvent->wq);
}
EXPORT_SYMBOL(os_event_send);

void os_event_clear(OS_EVENT_T* pEvent)
{
    ULONG flags;

    OS_CHECK_ERROR(NULL == pEvent, return, "null event error\n");

    spin_lock_irqsave(&pEvent->spinlock, flags);
    pEvent->ev = 0x0;
    spin_unlock_irqrestore(&pEvent->spinlock, flags);
}
EXPORT_SYMBOL(os_event_clear);

/*========================================================================================
    TIME/TICK OS API IMPLEMENTATION
========================================================================================*/
void os_sleep_ms(u32 msec)
{
    int usec = msec * 1000;
    usleep_range(usec, usec);
}
EXPORT_SYMBOL(os_sleep_ms);

void os_sleep_us(u32 usec)
{
    if (in_interrupt())
    {
        udelay(usec);
    }
    else
    {
        usleep_range(usec, usec);
    }
}
EXPORT_SYMBOL(os_sleep_us);

void os_delay_ns(u32 nsec)
{
    ndelay(nsec);
}
EXPORT_SYMBOL(os_delay_ns);

u64  os_get_ms_tick(void)
{
#if 0
    ktime_t t = ktime_get();
    struct timespec ts = ktime_to_timespec(t);
#else
    struct timespec64 ts;
    ktime_get_raw_ts64(&ts);
#endif

    return (u64)ts.tv_sec * 1000 + (u64)(ts.tv_nsec / 1000000);
}
EXPORT_SYMBOL(os_get_ms_tick);

u64 os_get_us_tick(void)
{
#if 0
    ktime_t t = ktime_get();
    struct timespec ts = ktime_to_timespec(t);
#else
    struct timespec64 ts;
    ktime_get_raw_ts64(&ts);
#endif

    return (u64)ts.tv_sec * 1000000 + (u64)(ts.tv_nsec / 1000);
}
EXPORT_SYMBOL(os_get_us_tick);

u64 os_get_ns_tick(void)
{
#if 0
    ktime_t t = ktime_get();
    struct timespec ts = ktime_to_timespec(t);
#else
    struct timespec64 ts;
    ktime_get_raw_ts64(&ts);
#endif

    return (u64)ts.tv_sec * 1000000000 + (u64)(ts.tv_nsec);
}
EXPORT_SYMBOL(os_get_ns_tick);

void os_get_ticks(u32* sec, u32* msec, u32* usec)
{
#if 0
    ktime_t t = ktime_get();
    struct timespec ts = ktime_to_timespec(t);
#else
    struct timespec64 ts;
    ktime_get_raw_ts64(&ts);
#endif

    if (sec) *sec = ts.tv_sec;

    if (msec) *msec = ts.tv_nsec / 1000000;

    if (usec) *usec = (ts.tv_nsec % 1000000) / 1000;
}
EXPORT_SYMBOL(os_get_ticks);


/*========================================================================================
    TIMER
========================================================================================*/
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static void os_timer_callback(struct timer_list* t)
#else
static void os_timer_callback(ULONG param)
#endif
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    OS_TIMER_T* pTimer = from_timer(pTimer, t, tmr);
#else
    OS_TIMER_T* pTimer = (OS_TIMER_T*)param;
#endif

    //  DBG_TRACE(" info (object:%px, callback:%px, option:%x, ticks:%4d )\n", pTimer, pTimer->callback, pTimer->option, pTimer->ticks );

    if (pTimer->callback)
    {
        pTimer->callback(pTimer->data);
    }

    /* if current timer is stopped or destroyed during timer callback, we should not do anything */
    if (pTimer->callback && (pTimer->option & OS_TIMER_TIMETICK))
    {
        mod_timer(&pTimer->tmr, get_jiffies_64() + pTimer->ticks);
    }
}

void os_timer_init(OS_TIMER_T* pTimer)
{
    memset(pTimer, 0x0, sizeof(OS_TIMER_T));
    spin_lock_init(&pTimer->spinlock);
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
    init_timer(&pTimer->tmr);
#endif
}
EXPORT_SYMBOL(os_timer_init);

void os_timer_start(OS_TIMER_T* pTimer, OS_TIMER_CALLBACK_T timer_callback, u32 option, u32 timeout, u32 data)
{
    ULONG   ticks;
    ULONG   flags;

    ticks = MSEC2TICKS(timeout);

    if (ticks == 0) ticks = 1;

    lg1k_logm_os_debug("timeout=%d, ticks=%d, option=0x%08x\n", timeout, (int)ticks, option);

    /* fill the basic information.
     * remember that timer_callback and data is stored to pTimer object, its pointer is passed to
     * add_timer() function.
     */
    spin_lock_irqsave(&(pTimer->spinlock), flags);
    pTimer->ticks   = ticks;
    pTimer->data    = data;
    pTimer->option  = option;
    pTimer->callback = timer_callback;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    timer_setup(&pTimer->tmr, os_timer_callback, 0);
#else
    pTimer->tmr.function = os_timer_callback;
    pTimer->tmr.data = (ULONG)pTimer;
#endif
    pTimer->tmr.expires = get_jiffies_64() + pTimer->ticks;
    spin_unlock_irqrestore(&(pTimer->spinlock), flags);

    mod_timer(&pTimer->tmr, get_jiffies_64() + pTimer->ticks);
}
EXPORT_SYMBOL(os_timer_start);

void os_timer_stop(OS_TIMER_T* pTimer)
{
    ULONG flags;

    spin_lock_irqsave(&(pTimer->spinlock), flags);
    pTimer->option  = 0x0;
    pTimer->callback = 0x0;
    spin_unlock_irqrestore(&(pTimer->spinlock), flags);

    del_timer_sync(&pTimer->tmr);
}
EXPORT_SYMBOL(os_timer_stop);

/*========================================================================================
    FILE
========================================================================================*/
int os_file_open(OS_FILE_T* filep, char* fname, int flags, mode_t mode)
{
    OS_CHECK_ERROR(!filep, return RET_ERROR, "null file error\n");
    OS_CHECK_ERROR(!fname, return RET_ERROR, "null file name error\n");

    filep->name = os_strdup(fname, LX_STR_MAX);
    OS_CHECK_ERROR(!filep->name, return RET_ERROR, "alloc error\n");

    filep->fd = filp_open(fname, flags, mode);

    if (IS_ERR(filep->fd))
    {
        lg1k_logm_error("file open error. name=%s, flags=%x, mode=%x\n", fname, flags, mode);

        filep->fd = NULL;
        return RET_ERROR;
    }

    lg1k_logm_os_debug("file open ok. name=%s, flags=0x%x, mode=%o\n", fname, flags, mode);

    return RET_OK;
}
EXPORT_SYMBOL(os_file_open);

int os_file_seek(OS_FILE_T* filep, off_t offset, int whence)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,9,0)
    off_t offval;

    OS_CHECK_ERROR(!filep, return -1, "null file error\n");
    OS_CHECK_ERROR(!filep->fd, return -1, "invalid file error\n");

    offval = vfs_llseek(filep->fd, offset, whence);
#else
    off_t offval;
    mm_segment_t old_fs;

    OS_CHECK_ERROR(!filep, return -1, "null file error\n");
    OS_CHECK_ERROR(!filep->fd, return -1, "invalid file error\n");

    old_fs = get_fs();
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    set_fs(KERNEL_DS);
#else
    set_fs(get_ds());
#endif

    offval = vfs_llseek(filep->fd, offset, whence);

    set_fs(old_fs);
#endif

    lg1k_logm_os_debug("file seek ok. name=%s, offset=%ld, whence=%x, offval=%ld\n",
                       filep->name, offset, whence, offval);

    return offval;
}
EXPORT_SYMBOL(os_file_seek);

int os_file_get_size(OS_FILE_T* filep)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    loff_t file_size;

    OS_CHECK_ERROR(NULL == filep, return -1, "null file error\n");
    OS_CHECK_ERROR(!filep->fd, return -1, "invalid file error\n");

    file_size = i_size_read(file_inode(filep->fd));

    return (int)file_size;
#else
    mm_segment_t old_fs;
    struct kstat stat;
    int rc;

    OS_CHECK_ERROR(NULL == filep, return -1, "null file error\n");
    OS_CHECK_ERROR(!filep->fd, return -1, "invalid file error\n");

    old_fs = get_fs();
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    set_fs(KERNEL_DS);
#else
    set_fs(get_ds());
#endif

    rc = vfs_stat(filep->name, &stat);

    set_fs(old_fs);

    if (rc)
    {
        lg1k_logm_error("file=%s, stat error\n", filep->name);
        return RET_ERROR;
    }

    lg1k_logm_os_debug("file=%s, size=%d\n", filep->name, (int)stat.size);

    return stat.size;
#endif
}
EXPORT_SYMBOL(os_file_get_size);

int os_file_write(OS_FILE_T* filep, char* buffer, int count)
{
    int tx;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    OS_CHECK_ERROR(NULL == filep, return -1, "null file error\n");
    OS_CHECK_ERROR(!filep->fd, return -1, "invalid file error\n");

    tx = kernel_write(filep->fd, buffer, count, &filep->fd->f_pos);
#else
    mm_segment_t old_fs;

    OS_CHECK_ERROR(NULL == filep, return -1, "null file error\n");
    OS_CHECK_ERROR(!filep->fd, return -1, "invalid file error\n");

    old_fs = get_fs();
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    set_fs(KERNEL_DS);
#else
    set_fs(get_ds());
#endif

    tx = kernel_write(filep->fd, buffer, count, &filep->fd->f_pos);

    set_fs(old_fs);
#endif

    lg1k_logm_os_debug("(%s) write buffer=%px, count=%d, tx=%d\n",
                       filep->name, buffer, count, tx);

    return tx;
}
EXPORT_SYMBOL(os_file_write);

int os_file_read(OS_FILE_T* filep, char* buffer, int count)
{
    int rx;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    OS_CHECK_ERROR(NULL == filep, return -1, "null file error\n");
    OS_CHECK_ERROR(!filep->fd, return -1, "invalid file error\n");

    rx = kernel_read(filep->fd, buffer, count, &filep->fd->f_pos);
#else
    mm_segment_t old_fs;

    OS_CHECK_ERROR(NULL == filep, return -1, "null file error\n");
    OS_CHECK_ERROR(!filep->fd, return -1, "invalid file error\n");

    old_fs = get_fs();
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    set_fs(KERNEL_DS);
#else
    set_fs(get_ds());
#endif

    rx = kernel_read(filep->fd, buffer, count, &filep->fd->f_pos);

    set_fs(old_fs);
#endif

    lg1k_logm_os_debug("(%s) read buffer=%px, count=%d, rx=%d\n",
                       filep->name, buffer, count, rx);

    return rx;
}
EXPORT_SYMBOL(os_file_read);

int os_file_close(OS_FILE_T* filep)
{
    OS_CHECK_ERROR(NULL == filep, return RET_ERROR, "null file error\n");

    if (filep->fd)
    {
        filp_close(filep->fd, NULL);
        filep->fd = NULL;
    }

    lg1k_logm_os_debug("file=%s close ok\n", filep->name);

    if (filep->name)
    {
        os_vfree(filep->name);
        filep->name = NULL;
    }

    return RET_OK;
}
EXPORT_SYMBOL(os_file_close);

/*========================================================================================
    MEMORY
========================================================================================*/
void*   os_kmalloc_ex(size_t size, const char* szFunc, const int nLine)
{
    void* ptr = NULL;

    if (in_interrupt())
    {
        ptr = kzalloc(size, GFP_ATOMIC);
    }
    else
    {
        ptr = kzalloc(size, GFP_KERNEL);
    }

    if (!ptr)
    {
        lg1k_logm_error("kmalloc error from %s:%d\n", szFunc, nLine);
        return NULL;
    }

    return ptr;
}
EXPORT_SYMBOL(os_kmalloc_ex);

void    os_kfree_ex(void* ptr, const char* szFunc, const int nLine)
{
    PARAM_UNUSED(szFunc);
    PARAM_UNUSED(nLine);

    if (ptr)  kfree(ptr);
}
EXPORT_SYMBOL(os_kfree_ex);

void*   os_vmalloc_ex(size_t size, const char* szFunc, const int nLine)
{
    void* ptr = NULL;

    size = ALIGN(size, 8);

    ptr = vmalloc(size);

    if (!ptr)
    {
        lg1k_logm_error("vmalloc error from %s:%d\n", szFunc, nLine);
        return NULL;
    }

    memset(ptr, 0x0, size);

    return ptr;
}
EXPORT_SYMBOL(os_vmalloc_ex);

void    os_vfree_ex(void* ptr, const char* szFunc, const int nLine)
{
    PARAM_UNUSED(szFunc);
    PARAM_UNUSED(nLine);

    if (ptr)  vfree(ptr);
}
EXPORT_SYMBOL(os_vfree_ex);

char* os_strdup(const char* s, size_t max)
{
    size_t len;
    char* buf;

    max -= 1;

    if (!s)
        return NULL;

    len = strnlen(s, max);
    buf = os_vmalloc(len + 1);

    if (buf)
    {
        memcpy(buf, s, len);
        buf[len] = '\0';
    }

    return buf;
}
EXPORT_SYMBOL(os_strdup);

/*========================================================================================
   REGS/MEM
========================================================================================*/
int os_wr_reg(u32 regAddr, u32 val)
{
    void* vaddr = ioremap(regAddr, 4);

    if (!vaddr)
    {
        lg1k_logm_error("ioremap error for reg=%08x\n", regAddr);
        return RET_ERROR;
    }

    __raw_writel(val, (volatile void*)vaddr);
    iounmap((volatile void*)vaddr);

    lg1k_logm_os_debug("0x%08x = 0x%08x\n", regAddr, val);

    return RET_OK;
}
EXPORT_SYMBOL(os_wr_reg);

int os_rd_reg(u32 regAddr, u32* pVal)
{
    u32 val = 0x0;
    void* vaddr = ioremap(regAddr, 4);

    if (!vaddr)
    {
        lg1k_logm_error("ioremap error for reg=%08x\n", regAddr);
        return RET_ERROR;
    }

    val = __raw_readl((volatile void*)vaddr);
    iounmap((void*)vaddr);

    lg1k_logm_os_debug("0x%08x = 0x%08x\n", regAddr, val);

    *pVal = val;
    return RET_OK;
}
EXPORT_SYMBOL(os_rd_reg);

int os_wr_reg_list(u32 reg_list[], u32 val_list[], int num)
{
    int i;
    int error_cnt = 0;

    for (i = 0; i < num; i++)
    {
        if (RET_OK != OS_WrReg(reg_list[i], val_list[i])) error_cnt++;
    }

    if (unlikely(error_cnt > 0))
    {
        lg1k_logm_error("total_cnt=%d, error_cnt=%d\n", num, error_cnt);
        return RET_ERROR;
    }

    return RET_OK;
}
EXPORT_SYMBOL(os_wr_reg_list);

int os_rd_reg_list(u32 reg_list[], u32 val_list[], int num)
{
    int i;
    int error_cnt = 0;

    for (i = 0; i < num; i++)
    {
        if (RET_OK != OS_RdReg(reg_list[i], &val_list[i])) error_cnt++;
    }

    if (unlikely(error_cnt > 0))
    {
        lg1k_logm_error("total_cnt=%d, error_cnt=%d\n", num, error_cnt);
        return RET_ERROR;
    }

    return RET_OK;
}
EXPORT_SYMBOL(os_rd_reg_list);

int os_wr_mem(u32 phys_addr, u32* data_list, int num_data)
{
    int i;
    void* vaddr = (void*)vmap_phys(phys_addr, (u32)(num_data * sizeof(u32)));

    if (unlikely(!vaddr))
    {
        lg1k_logm_error("vmap_phys error. paddr=0x%08x data_num=%d\n", phys_addr, num_data);
        return RET_ERROR;
    }

    for (i = 0; i < num_data; i++)
    {
        __raw_writel(data_list[i], (volatile void*)((u32*)vaddr + i));
    }

    vunmap_phys((void*)vaddr);

    wmb();

    return RET_OK;
}
EXPORT_SYMBOL(os_wr_mem);

int os_rd_mem(u32 phys_addr, u32* data_list, int num_data)
{
    int i;
    void* vaddr = (void*)vmap_phys(phys_addr, (u32)(num_data * sizeof(u32)));

    if (unlikely(!vaddr))
    {
        lg1k_logm_error("vmap_phys error. paddr=0x%08x data_num=%d\n", phys_addr, num_data);
        return RET_ERROR;
    }

    for (i = 0; i < num_data; i++)
    {
        data_list[i] = __raw_readl((volatile void*)((u32*)vaddr + i));
    }

    vunmap_phys((void*)vaddr);

    return RET_OK;
}
EXPORT_SYMBOL(os_rd_mem);

u32 os_random(void)
{
    return get_random_u32();
}
EXPORT_SYMBOL(os_random);

u64 os_random64(void)
{
    return get_random_u64();
}
EXPORT_SYMBOL(os_random64);

/*========================================================================================
    CMEM
========================================================================================*/
int os_cmem_open(OS_CACHE_MAP_T* pMap, ULONG phys_addr, u32 length)
{
    OS_CHECK_ERROR(NULL == pMap, return RET_ERROR, "null param\n");
    OS_CHECK_ERROR(0x0 == phys_addr || 0 == length, return RET_ERROR, "invalid addr info\n");

    length = LX_CALC_ALIGNED_VALUE(length, 12);

    pMap->phys_addr = phys_addr;
    pMap->length    = length;
    pMap->virt_addr = vmap_phys_cache(phys_addr, length);

    lg1k_logm_os_debug("paddr=0x%08lx, vaddr=%px, length=%d(0x%08x) open\n",
                       pMap->phys_addr, pMap->virt_addr, length, length);

    return (pMap->virt_addr) ? RET_OK : RET_ERROR;
}
EXPORT_SYMBOL(os_cmem_open);

int os_cmem_close(OS_CACHE_MAP_T* pMap)
{
    OS_CHECK_ERROR(NULL == pMap, return RET_ERROR, "null param\n");
    OS_CHECK_ERROR(0x0 == pMap->virt_addr || 0 == pMap->length, return RET_ERROR, "invalid addr info\n");

    vunmap_phys((void*)pMap->virt_addr);

    lg1k_logm_os_debug("paddr=0x%08lx close\n", pMap->phys_addr);

    return RET_OK;
}
EXPORT_SYMBOL(os_cmem_close);

int os_cmem_inval(OS_CACHE_MAP_T* pMap, u32 off, u32 length)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 19, 0))
    unsigned long start, pstart, size;

    OS_CHECK_ERROR(NULL == pMap, return RET_ERROR, "null param\n");
    OS_CHECK_ERROR(0x0 == pMap->virt_addr || 0 == pMap->length, return RET_ERROR, "invalid addr info\n");

    start = (unsigned long)pMap->virt_addr + off;
    pstart = (unsigned long)pMap->phys_addr + off;
    size = (unsigned long)length;

    dcache_inval_poc(start, start + size);

#ifndef __aarch64__
    outer_inv_range(pstart, pstart + size);
#endif

    return RET_OK;

#else

#ifndef __aarch64__
    ULONG phys_addr = pMap->phys_addr + off;
#endif
    void* virt_addr = (void*)((uintptr_t)pMap->virt_addr + (uintptr_t)off);

    OS_CHECK_ERROR(off >= pMap->length, return RET_ERROR, "invalid off\n");
    OS_CHECK_ERROR(off + length > pMap->length, return RET_ERROR, "invalid off+len\n");

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,4,3)
    __dma_map_area((void*)virt_addr, length, DMA_FROM_DEVICE);
#else
    dmac_map_area((void*)virt_addr, length, DMA_FROM_DEVICE);
#endif
#ifndef __aarch64__
    outer_inv_range(phys_addr, phys_addr + length);
#endif

    return RET_OK;
#endif
}
EXPORT_SYMBOL(os_cmem_inval);

int os_cmem_clean(OS_CACHE_MAP_T* pMap, u32 off, u32 length)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 19, 0))
    unsigned long start, pstart, size;

    OS_CHECK_ERROR(NULL == pMap, return RET_ERROR, "null param\n");
    OS_CHECK_ERROR(0x0 == pMap->virt_addr || 0 == pMap->length, return RET_ERROR, "invalid addr info\n");

    start = (unsigned long)pMap->virt_addr + off;
    pstart = (unsigned long)pMap->phys_addr + off;
    size = (unsigned long)length;

    dcache_clean_poc(start, start + size);

#ifndef __aarch64__
    outer_clean_range(pstart, pstart + size);
#endif

    return RET_OK;
#else

#ifndef __aarch64__
    ULONG phys_addr = pMap->phys_addr + off;
#endif
    void* virt_addr = (void*)((uintptr_t)pMap->virt_addr + (uintptr_t)off);

    OS_CHECK_ERROR(off >= pMap->length, return RET_ERROR, "invalid off\n");
    OS_CHECK_ERROR(off + length > pMap->length, return RET_ERROR, "invalid off+len\n");

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,4,3)
    __dma_map_area((void*)virt_addr, length, DMA_TO_DEVICE);
#else
    dmac_map_area((void*)virt_addr, length, DMA_TO_DEVICE);
#endif
#ifndef __aarch64__
    outer_clean_range(phys_addr, phys_addr + length);
#endif

    return RET_OK;
#endif
}
EXPORT_SYMBOL(os_cmem_clean);

/*========================================================================================
    UTIL/LIB
========================================================================================*/
char* simple_strtok(char* s, const char* delim, char** save_ptr)
{
    char* token;

    token = 0;                  /* Initialize to no token. */

    if (s == 0)                 /* If not first time called... */
    {
        s = *save_ptr;          /* restart from where we left off. */
    }

    if (s != 0)                 /* If not finished... */
    {
        *save_ptr = 0;

        s += strspn(s, delim);  /* Skip past any leading delimiters. */

        if (*s != '\0')         /* We have a token. */
        {
            token = s;
            *save_ptr = strpbrk(token, delim); /* Find token's end. */

            if (*save_ptr != 0)
            {
                /* Terminate the token and make SAVE_PTR point past it.  */
                *(*save_ptr)++ = '\0';
            }
        }
    }

    return token;
}
EXPORT_SYMBOL(simple_strtok);

u32 os_strhash(const char* str)
{
    int i;
    u32 k = 0;
    int len = strlen(str);

    for (i = 0 ; i < len ; i++)
    {
        k = 31 * k + str[i];
    }

    return k;
}
EXPORT_SYMBOL(os_strhash);

int os_hexdump(u32 disp_addr, void* data_ptr, unsigned int data_cnt, char* output_buf)
{
    int output_len = 0;

    if (data_cnt > 0)
    {
        int width = 16;
        int j, i = 0;

        char*   str = (char*)data_ptr;
        char*   buf_ptr = (char*)os_vmalloc(200); // enough to hold single line
        int     buf_len = 0;

        if (output_buf)
        {
            output_len += sprintf(output_buf + output_len,
                                  "--------------------------------------------------------------------------------\n");
            output_len += sprintf(output_buf + output_len,
                                  "address     00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F  0123456789ABCDEF\n");
            output_len += sprintf(output_buf + output_len,
                                  "--------------------------------------------------------------------------------\n");
        }
        else
        {
            lg1k_logm_noti("--------------------------------------------------------------------------------\n");
            lg1k_logm_noti("address     00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F  0123456789ABCDEF\n");
            lg1k_logm_noti("--------------------------------------------------------------------------------\n");
        }

        while (i < data_cnt)
        {
            buf_len = 0;
            buf_len += snprintf(buf_ptr + buf_len, 16, "0x%08x  ", i + disp_addr);

            if (1)
            {
                for (j = 0; j < width; j++)
                {
                    if (i + j < data_cnt)
                    {
                        buf_len += snprintf(buf_ptr + buf_len, 8, "%02x ", (UINT8)str[j]);
                    }
                    else
                    {
                        buf_len += snprintf(buf_ptr + buf_len, 8, "%s", "   ");
                    }

                    if ((j + 1) % (width / 2) == 0)
                        buf_len += snprintf(buf_ptr + buf_len, 8, "%s", " ");
                }
            }

            for (j = 0; j < width; j++)
            {
                if (i + j < data_cnt)
                    buf_len += snprintf(buf_ptr + buf_len, 8, "%c", isprint(str[j]) ? str[j] : '.');
                else
                    buf_len += snprintf(buf_ptr + buf_len, 8, "%s", " ");
            }

            str += width;
            i += j;

            if (output_buf)
            {
                output_len += snprintf(output_buf + output_len, 160, "%s\n", buf_ptr);
            }
            else
            {
                lg1k_logm_noti("%s\n", buf_ptr);
            }
        }

        os_vfree(buf_ptr);
    }

    return output_len;
}
EXPORT_SYMBOL(os_hexdump);

int os_scan_kernel_cmdline(const char* fmt_str, char* val_str)
{
    int     ret = RET_ERROR;
    char*   cmd_buf = NULL;
    int     cmd_buf_sz = (1 << 10);

    char* tok, *sav_tok;
    char delim[] = " \t\n";

    if (val_str)
    {
        lg1k_logm_debug("scan_type=fmt, fmt_str=(%s)\n", fmt_str);
    }
    else
    {
        lg1k_logm_debug("scan_type=token, token_str=(%s)\n", fmt_str);
    }

    if (NULL == (cmd_buf = os_vmalloc(cmd_buf_sz)))
    {
        lg1k_logm_error("can't alloc %d for cmd_buf\n", cmd_buf_sz);
        goto func_exit;
    }

    // test parser if test_cmdline is not NULL
    if (test_cmdline)
    {
        cmd_buf_sz = snprintf(cmd_buf, cmd_buf_sz, "%s", test_cmdline);
    }
    else
#ifdef MODULE // kernel exports saved_command_line symbol..
    {
        OS_FILE_T file;

        if (RET_OK != os_file_open(&file, "/proc/cmdline", O_RDONLY | O_LARGEFILE, 0666))
        {
            lg1k_logm_error("can't open /proc/cmdline\n");
            goto func_exit;
        }

        if (0 >= os_file_read(&file, cmd_buf, cmd_buf_sz))
        {
            os_file_close(&file);
            lg1k_logm_error("can't read /proc/cmdline\n");
            goto func_exit;
        }

        os_file_close(&file);
    }

#else
    {
        extern char* saved_command_line;
        cmd_buf_sz = snprintf(cmd_buf, cmd_buf_sz, "%s", saved_command_line);
    }
#endif

    tok = simple_strtok(cmd_buf, delim, &sav_tok);

    while (tok)
    {
        // scan "variable=value" format
        if (val_str)
        {
            if (1 == sscanf(tok, fmt_str, val_str))
            {
                lg1k_logm_debug("fmt_str(%s) found. val_str=%s\n", fmt_str, val_str);
                ret = RET_OK;
                break;
            }
        }
        // scan "token" type
        else
        {
            const char* token = fmt_str;

            if (!strncasecmp(tok, token, strlen(token)))
            {
                lg1k_logm_debug("token_str(%s) found\n", token);
                ret = RET_OK;
                break;
            }
        }

        tok = simple_strtok(NULL, delim, &sav_tok);
    }

func_exit:

    if (cmd_buf) os_vfree(cmd_buf);

    return ret;
}
EXPORT_SYMBOL(os_scan_kernel_cmdline);


void* _vmap_phys(phys_addr_t addr, unsigned long size, pgprot_t pgprot)
{
    unsigned int n_pages;
    void* vaddr;
    size_t page_offset = 0;
    struct page** pages;
    unsigned int start_pfn, i;

    if (!IS_ALIGNED((unsigned long)addr, PAGE_SIZE))
    {
        page_offset = addr & ~PAGE_MASK;
        size += page_offset;
        pr_warn("vmap: address is not-page-aligned %pxap\n", &addr);
    }

    start_pfn = __phys_to_pfn(addr & PAGE_MASK);

    WARN(!pfn_valid(start_pfn), "pfn is not valid");

    n_pages = PAGE_ALIGN(size) >> PAGE_SHIFT;
    pages =  vmalloc(sizeof(struct page*) * n_pages);

    for (i = 0; i < n_pages; i++)
    {
        pages[i] = pfn_to_page(start_pfn + i);
    }

    vaddr = vmap(pages, n_pages, VM_MAP, pgprot) + page_offset;

    vfree(pages);
    return vaddr;
}
EXPORT_SYMBOL(_vmap_phys);

void _vunmap_phys(void* addr)
{
    void* vaddr;

    if (!IS_ALIGNED((unsigned long)addr, PAGE_SIZE))
        pr_warn("vunmap: address is not-page-aligned vaddr:%px\n", addr);

    vaddr = (void*)((unsigned long)addr & PAGE_MASK);

    if (VMALLOC_START <= (u64)vaddr && (u64)vaddr < VMALLOC_END)
        vunmap(vaddr);
}
EXPORT_SYMBOL(_vunmap_phys);

void* vmap_phys(phys_addr_t addr, unsigned long size)
{
    if (!pfn_valid(__phys_to_pfn(addr)))
        return ioremap_wc(addr, size);
    else
        return _vmap_phys(addr, size, pgprot_writecombine(PAGE_KERNEL));
}
EXPORT_SYMBOL(vmap_phys);

void* vmap_phys_cache(phys_addr_t addr, unsigned long size)
{
    if (!pfn_valid(__phys_to_pfn(addr)))
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,13,0))
        return ioremap_cache(addr, size);

#else
        return ioremap_cached(addr, size);
#endif
    else
        return _vmap_phys(addr, size, PAGE_KERNEL);
}
EXPORT_SYMBOL(vmap_phys_cache);

void vunmap_phys(void* addr)
{
    _vunmap_phys(addr);
}
EXPORT_SYMBOL(vunmap_phys);

/*========================================================================================
    for LEGACY INTERFACE
========================================================================================*/
int OS_OpenFile(OS_FILE_T* pFile, char* fname, int flags, mode_t mode)
{
    return os_file_open(pFile, fname, flags, mode);
}
EXPORT_SYMBOL(OS_OpenFile);

int OS_SeekFile(OS_FILE_T* pFile, off_t offset, int whence)
{
    return os_file_seek(pFile, offset, whence);
}
EXPORT_SYMBOL(OS_SeekFile);

int OS_SizeOfFile(OS_FILE_T* pFile)
{
    return os_file_get_size(pFile);
}
EXPORT_SYMBOL(OS_SizeOfFile);

int OS_WriteFile(OS_FILE_T* pFile, char* buffer, int count)
{
    return os_file_write(pFile, buffer, count);
}
EXPORT_SYMBOL(OS_WriteFile);

int OS_ReadFile(OS_FILE_T* pFile, char* buffer, int count)
{
    return os_file_read(pFile, buffer, count);
}
EXPORT_SYMBOL(OS_ReadFile);

int OS_CloseFile(OS_FILE_T* pFile)
{
    return os_file_close(pFile);
}
EXPORT_SYMBOL(OS_CloseFile);

void* OS_KMalloc_Tag(size_t size, const char* szFile, const char* szFunc, const int nLine)
{
    return os_kmalloc_ex(size, szFunc, nLine);
}
EXPORT_SYMBOL(OS_KMalloc_Tag);

void OS_KFree_Tag(void* ptr, const char* szFile, const char* szFunc, const int nLine)
{
    os_kfree_ex(ptr, szFunc, nLine);
}
EXPORT_SYMBOL(OS_KFree_Tag);

int OS_OpenCacheMap(OS_CACHE_MAP_T* pMap, ULONG paddr, u32 length)
{
    return os_cmem_open(pMap, paddr, length);
}
EXPORT_SYMBOL(OS_OpenCacheMap);

int OS_CloseCacheMap(OS_CACHE_MAP_T* pMap)
{
    return os_cmem_close(pMap);
}
EXPORT_SYMBOL(OS_CloseCacheMap);

int OS_InvalCacheMap(OS_CACHE_MAP_T* pMap, u32 offset, u32 length)
{
    return os_cmem_inval(pMap, offset, length);
}
EXPORT_SYMBOL(OS_InvalCacheMap);

int OS_CleanCacheMap(OS_CACHE_MAP_T* pMap, u32 offset, u32 length)
{
    return os_cmem_clean(pMap, offset, length);
}
EXPORT_SYMBOL(OS_CleanCacheMap);

int  OS_WrReg(u32 regAddr, u32 val)
{
    return os_wr_reg(regAddr, val);
}
EXPORT_SYMBOL(OS_WrReg);

int     OS_RdReg(u32 regAddr, u32* pVal)
{
    return os_rd_reg(regAddr, pVal);
}
EXPORT_SYMBOL(OS_RdReg);

int     OS_WrRegList(u32 reg_list[], u32 val_list[], int num)
{
    return os_wr_reg_list(reg_list, val_list, num);
}
EXPORT_SYMBOL(OS_WrRegList);

int     OS_RdRegList(u32 reg_list[], u32 val_list[], int num)
{
    return os_rd_reg_list(reg_list, val_list, num);
}
EXPORT_SYMBOL(OS_RdRegList);

int     OS_WrData(u32 phys_addr, u32* data_list, int num_data)
{
    return os_wr_mem(phys_addr, data_list, num_data);
}
EXPORT_SYMBOL(OS_WrData);

int OS_RdData(u32 phys_addr, u32* data_list, int num_data)
{
    return os_rd_mem(phys_addr, data_list, num_data);
}
EXPORT_SYMBOL(OS_RdData);

void OS_InitTimer(OS_TIMER_T* pTimer)
{
    os_timer_init(pTimer);
}
EXPORT_SYMBOL(OS_InitTimer);

void OS_StopTimer(OS_TIMER_T* pTimer)
{
    os_timer_stop(pTimer);
}
EXPORT_SYMBOL(OS_StopTimer);

void OS_StartTimer(OS_TIMER_T* pTimer, OS_TIMER_CALLBACK_T timer_callback, u32 option, u32 timeout, u32 data)
{
    os_timer_start(pTimer, timer_callback, option, timeout, data);
}
EXPORT_SYMBOL(OS_StartTimer);

int OS_ScanKernelCmdline(const char* fmt_str, char* val_str)
{
    return os_scan_kernel_cmdline(fmt_str, val_str);
}
EXPORT_SYMBOL(OS_ScanKernelCmdline);

int OS_ScanKernelCmdlineToken(const char* token)
{
    return os_scan_kernel_cmdline(token, NULL);
}
EXPORT_SYMBOL(OS_ScanKernelCmdlineToken);

int     OS_MsecSleep(u32 msec)
{
    os_sleep_ms(msec);
    return RET_OK;
}
EXPORT_SYMBOL(OS_MsecSleep);

void    OS_NsecDelay(u32 nsec)
{
    os_delay_ns(nsec);
}
EXPORT_SYMBOL(OS_NsecDelay);

void    OS_UsecDelay(u32 usec)
{
    os_sleep_us(usec);
}
EXPORT_SYMBOL(OS_UsecDelay);

u64  OS_GetMsecTicks(void)
{
    return os_get_ms_tick();
}
EXPORT_SYMBOL(OS_GetMsecTicks);

u64  OS_GetUsecTicks(void)
{
    return os_get_us_tick();
}
EXPORT_SYMBOL(OS_GetUsecTicks);

u64  OS_GetNsecTicks(void)
{
    return os_get_ns_tick();
}
EXPORT_SYMBOL(OS_GetNsecTicks);

void    OS_GetCurrentTicks(u32* pSec, u32* pMSec, u32* pUSec)
{
    os_get_ticks(pSec, pMSec, pUSec);
}
EXPORT_SYMBOL(OS_GetCurrentTicks);

void    OS_InitEvent(OS_EVENT_T* pEvent)
{
    os_event_init(pEvent, NULL);
}
EXPORT_SYMBOL(OS_InitEvent);

int     OS_RecvEvent(OS_EVENT_T* pEvent, u32 ev, u32* rEv, u32 option, u32 timeout)
{
    return os_event_recv(pEvent, ev, rEv, option, timeout);
}
EXPORT_SYMBOL(OS_RecvEvent);

void    OS_SendEvent(OS_EVENT_T* pEvent, u32 ev)
{
    os_event_send(pEvent, ev);
}
EXPORT_SYMBOL(OS_SendEvent);

void    OS_ClearEvent(OS_EVENT_T* pEvent)
{
    os_event_clear(pEvent);
}
EXPORT_SYMBOL(OS_ClearEvent);

void    OS_InitMutex(OS_SEM_T* pSem, u32 attr)
{
    PARAM_UNUSED(attr);

    os_mutex_init(pSem, NULL);
}
EXPORT_SYMBOL(OS_InitMutex);

int __must_check OS_LockMutexEx(OS_SEM_T* pSem, u32 timeout)
{
    return os_mutex_lock(pSem, timeout);
}
EXPORT_SYMBOL(OS_LockMutexEx);

void OS_UnlockMutex(OS_SEM_T* pSem)
{
    return os_mutex_unlock(pSem);
}
EXPORT_SYMBOL(OS_UnlockMutex);

/** @} */
