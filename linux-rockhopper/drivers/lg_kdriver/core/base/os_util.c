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

/** @file
 *
 *  OS(Linux) kernal API wrapper
 *
 *  author      daeyoung lim ( raxis.lim@lge.com )
 *  @version    1.0
 *  @date       2009.11.18
 *
 *  @addtogroup lg1150_base
 *  @{
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
#include <linux/delay.h>
#include <linux/hardirq.h>
#include <linux/dma-mapping.h>
#include <linux/version.h>
#include <linux/mm.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/cacheflush.h>

#ifdef USE_TLSF_ALLOCATOR
#include "tlsf.h"
#endif
#include "debug_util.h"
#include "os_util.h"
#include "debug_util.h"
#include "base_device.h"
#include "base_impl.h"

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
static struct task_struct*  g_csOwner = NULL;

#define SET_CRITICAL()      do { g_csOwner = current; } while (0)
#define CLEAR_CRITICAL()    do { g_csOwner = NULL; } while (0)
#define CHECK_CRITICAL()    ( g_csOwner == current || in_interrupt() )

#define ASSERT_CRITICAL() do \
{\
    if ( !CHECK_CRITICAL() )\
    {\
        DBG_PRINT_ERROR("Error, must be in critical section to call %s\n", __FUNCTION__);\
        BKNI_Fail();\
    }\
} while (0)

#define ASSERT_NOT_CRITICAL() do \
{\
    if ( CHECK_CRITICAL() )\
    {\
        DBG_PRINT_ERROR("Error, must not be in critical section to call %s\n", __FUNCTION__);\
        OS_FAILURE();\
    }\
} while (0)

#define OS_CHECK_ERROR(__checker,__if_action,fmt,args...)   \
            __CHECK_IF_ERROR(__checker, printk, __if_action, fmt, ##args )


/*
 * critical resource lock/unlock
 */
//#define   OS_GLOBAL_LOCK()        do { if( CHECK_CRITICAL() ) spin_lock_irqsave(&_g_res_lock, flags);  } while(0)
//#define OS_GLOBAL_UNLOCK()        do { if( CHECK_CRITICAL() ) spin_unlock_irqrestore(&_g_res_lock, flags); } while(0)

#define OS_GLOBAL_LOCK()            do { spin_lock_irqsave(&_g_res_lock, flags);      } while(0)
#define OS_GLOBAL_UNLOCK()          do { spin_unlock_irqrestore(&_g_res_lock, flags); } while(0)

#define MSEC2TICKS(msec)            ( ( (msec) * HZ) / 1000 )

/*
 * OS internal debug macroes
*/
#if 1//default LOGM
#define OS_PRINT(format, args...)       DBG_PRINT(g_global_debug_fd,LX_LOGM_LEVEL_DEBUG,format, ##args)
#define OS_TRACE(format, args...)       DBG_PRINTX(g_global_debug_fd,LX_LOGM_LEVEL_TRACE,format, ##args)
#else
#define OS_PRINT(format, args...)       DBG_PRINT(0,DEBUG_IDX_OSUTIL_PRINT,format, ##args)
#define OS_TRACE(format, args...)       DBG_PRINTX(0,DEBUG_IDX_OSUTIL_PRINT,format, ##args)
#endif

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
extern int LOGM_Init(void);

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
static char* kdrv_dev_node_name(const struct device* dev, umode_t* mode)
{
    struct os_device_private* priv = dev_get_drvdata(dev);

    if (priv && priv->mode)
        *mode = priv->mode;

    return kasprintf(GFP_KERNEL, "lg/%s", dev_name(dev));
}

static struct class kdrv_dev_class = {  .name = "lg",
        .devnode = kdrv_dev_node_name,
    };

/**
 * spinlock for resource protection
 */

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39)
static  spinlock_t      _g_res_lock = SPIN_LOCK_UNLOCKED;
#else
static DEFINE_SPINLOCK(_g_res_lock);
#endif

/*========================================================================================
    Implementation Group
========================================================================================*/

/**
 *  Initialize OS core
 *
 */
void    OS_CORE_Init(void)
{
    /* create device class */
#if 0
    kdrv_dev_class = class_create(THIS_MODULE, "lg");
#else
    class_register(&kdrv_dev_class);
#endif

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
}

/**
 *  cleanup OS core
 *
 */
void    OS_CORE_Cleanup(void)
{
    /* destroy device class */
}

/**
 *  Initialize OS debug
 *
 */
void    OS_CORE_InitDebug(void)
{
    /* enable OS debug */
}

/**
 *  system failure handler
 *
 *  When system failure or system crash is detected by system, this function is called.
 *
 *  TODO : more analysis & implementation needed
 */

void    OS_FAILURE_Tag(const char* szFile, const char* szFunc, const int nLine)
{
    OS_DEBUG_PrintError_Tag(DBG_LEVEL_ERR, szFile, szFunc, nLine, "OS_FAILURE Issued...\n");
}

/*========================================================================================
    DEVICE REGISTER
========================================================================================*/
void     OS_CreateDeviceClass_mode(dev_t dev, umode_t mode, const char* fmt, ...)
{
    struct os_device_private* priv;
    va_list args;

    priv = kzalloc(sizeof(*priv), GFP_KERNEL);

    if (!priv)
    {
        printk(KERN_ERR "%s.%d: no memory.\n", __func__, __LINE__);
        return;
    }

    priv->mode = mode;

    va_start(args, fmt);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,9,0)
    {
        char buffer[128];
        vsprintf(buffer, fmt, args);
        device_create(&kdrv_dev_class, NULL, dev, priv, buffer);
    }
#else
    device_create_vargs(&kdrv_dev_class, NULL, dev, priv, fmt, args);
#endif
    va_end(args);
}
EXPORT_SYMBOL(OS_CreateDeviceClass_mode);

void     OS_CreateDeviceClass(dev_t dev, const char* fmt, ...)
{
    va_list args;
    char dev_name[LX_MAX_DEVICE_NAME];

    va_start(args, fmt);
    vsnprintf(dev_name, LX_MAX_DEVICE_NAME, fmt, args);
    va_end(args);

    device_create(&kdrv_dev_class, NULL, dev, NULL, dev_name);
}
EXPORT_SYMBOL(OS_CreateDeviceClass);

void     OS_DestroyDeviceClass(dev_t dev)
{
    device_destroy(&kdrv_dev_class, dev);
}
EXPORT_SYMBOL(OS_DestroyDeviceClass);

/*========================================================================================
    MUTEX OS API IMPLEMENTATION
========================================================================================*/
void    OS_InitMutex_Tag(OS_SEM_T* pSem, UINT32 attr)
{
    PARAM_UNUSED(attr);

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39)
    init_MUTEX(&(pSem->sem));
#else
    sema_init(&(pSem->sem), 1);
#endif
    init_waitqueue_head(&(pSem->wq));
}
EXPORT_SYMBOL(OS_InitMutex_Tag);

int     OS_LockMutex_Tag(OS_SEM_T* pSem, UINT32 timeout,
                         const char* szFile, const char* szFunc, const int nLine)
{
    ULONG   flags;
    int     ret = RET_OK;

    /* interrupt handler should not lock mutex with wait option */
    if (timeout != 0 && CHECK_CRITICAL())
    {
        OS_DEBUG_PrintError_Tag(DBG_LEVEL_WRN, szFile, szFunc, nLine,
                                "Ooops. OS_LockMutex called at ISR. force timeout from %d to 0.\n", timeout);

        timeout = 0;
    }

    /* normally, ISR should call OS_LockMutex with zero timeout */
    if (timeout == 0x0)
    {
        ret = down_trylock(&(pSem->sem));

        if (RET_OK != ret)
        {
            OS_DEBUG_PrintError_Tag(DBG_LEVEL_WRN, szFile, szFunc, nLine,
                                    "OS_LockMutex timeout. ret=%d\n", ret);
        }
    }
    /* normal process seems to call OS_LockMutex with timoeut option */
    else if (timeout == OS_INFINITE_WAIT)
    {
        ret = down_interruptible(&(pSem->sem));

        if (RET_OK != ret)
        {
            OS_DEBUG_PrintError_Tag(DBG_LEVEL_ERR, szFile, szFunc, nLine,
                                    "OS_LockMutex failed. ret=%d\n", ret);
        }
    }
    else
        /* if timeout option is enabled, */
    {
        ULONG           ticks;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
        wait_queue_entry_t  wqe;
#else
        wait_queue_t    wqe;
#endif

        ticks = MSEC2TICKS(timeout);
        pSem->wait_loop = TRUE;

        /* make wait_queue */
        init_waitqueue_entry(&wqe, current);
        add_wait_queue(&(pSem->wq), &wqe);

        for (; ;)
        {
            /* normally, current task goes to sleep before checking condition.
             * when event is sent by another task or ISR, current task will escape from schedule_timeout().
             * this is what I want.
             */
            set_current_state(TASK_INTERRUPTIBLE);

            ret = down_trylock(&(pSem->sem));

            /* good, I've got semaphore */
            if (RET_OK == ret)
            {
                ret = RET_OK; break;
            }
            /* event not yet arrived, check timeout */
            else if (!ticks)
            {
                OS_DEBUG_PrintError_Tag(DBG_LEVEL_WRN, szFile, szFunc, nLine,
                                        "OS_LockMutex timeout. ret=%d\n", ret);
                ret = RET_TIMEOUT; break;
            }
            else
            {
                ticks = schedule_timeout(ticks);

                OS_PRINT("OS_LockMutex : timeout interrupt (ticks:%d)\n", (int)ticks);

                if (signal_pending(current))
                {
                    OS_DEBUG_PrintError_Tag(DBG_LEVEL_WRN, szFile, szFunc, nLine,
                                            "OS_LockMutex signal interrrupt.\n");
                    ret = RET_INTR_CALL; break;
                }
            }
        }

        set_current_state(TASK_RUNNING);
        remove_wait_queue(&(pSem->wq), &wqe);
    }

    if (RET_OK == ret)
    {
        OS_GLOBAL_LOCK();
        pSem->wait_loop = FALSE;
        OS_GLOBAL_UNLOCK();

        OS_PRINT("OS_LockMutex   (%p): done (tm:%d)\n", pSem, timeout);
    }

    return ret;
}
EXPORT_SYMBOL(OS_LockMutex_Tag);

/**
 * unlock all processes blocked by mutex
 *
 * @param pSem [IN] pointer to semaphore
 */
void    OS_UnlockMutex_Tag(OS_SEM_T* pSem,
                           const char* szFile, const char* szFunc, const int nLine)
{
    ULONG   flags;
    BOOLEAN is_wait_loop = FALSE;

    OS_GLOBAL_LOCK();
    is_wait_loop    = pSem->wait_loop;
    pSem->wait_loop = FALSE;
    OS_GLOBAL_UNLOCK();

    /* unlock mutex first and wake up the sleeping task */
    OS_PRINT("OS_UnlockMutex (%p): done (loop:%d)\n", pSem, is_wait_loop);
    up(&(pSem->sem));

    if (is_wait_loop) wake_up_interruptible(&(pSem->wq));
}
EXPORT_SYMBOL(OS_UnlockMutex_Tag);

/*========================================================================================
    EVENT OS API IMPLEMENTATION
========================================================================================*/
/*
 * init event structure
 */
void    OS_InitEvent_Tag(OS_EVENT_T* pEvnt)
{
    /* initialize event structure */
    pEvnt->ev = 0x0;
    init_waitqueue_head(&(pEvnt->wq));
    spin_lock_init(&pEvnt->spinlock);
}
EXPORT_SYMBOL(OS_InitEvent_Tag);

/*
 * fetch event
*/
static BOOLEAN  _OS_FetchEvent(OS_EVENT_T* pEvnt, UINT32 ev, UINT32* rEv, UINT32 option)
{
    ULONG   flags;
    BOOLEAN ret;

    spin_lock_irqsave(&pEvnt->spinlock, flags);

    if (pEvnt->ev)
    {
        /* check if any required event is received */
        if ((option == OS_EVENT_RECEIVE_ANY) && (pEvnt->ev & ev))
        {
            *rEv = (pEvnt->ev & ev);
            pEvnt->ev &= ~(pEvnt->ev & ev);
            ret = TRUE;
        }
        /* check if all required event is received */
        else if ((option == OS_EVENT_RECEIVE_ALL) && ((pEvnt->ev & ev) == ev))
        {
            *rEv = ev;
            pEvnt->ev &= ~ev;
            ret = TRUE;
        }
        /* event is found but requested event not found, return RET_TIMEOUT (timeout error) */
        else
        {
            ret = FALSE;
        }
    }
    /* event is not found, return RET_TIMEOUT (timeout error) */
    else
    {
        ret = FALSE;
    }

    spin_unlock_irqrestore(&pEvnt->spinlock, flags);

    return ret;
}

/**
 * receive event structure
 */
int      OS_RecvEvent_Tag(OS_EVENT_T* pEvnt, UINT32 ev, UINT32* rEv, UINT32 option, UINT32 timeout,
                          const char* szFile, const char* szFunc, const int nLine)
{
    int             ret;
    int             rc;

    PARAM_UNUSED(szFile);
    PARAM_UNUSED(szFunc);
    PARAM_UNUSED(nLine);

    *rEv = 0x0;
    ret  = 0;

    /* if ISR handler, timeout should be 0 */
    if (timeout)
    {
        ASSERT_NOT_CRITICAL();
    }
    else if (CHECK_CRITICAL())
    {
        BOOLEAN rc = _OS_FetchEvent(pEvnt, ev, rEv, option);

        return (rc) ? RET_OK : RET_TIMEOUT;
    }

    if (signal_pending(current))
    {
        return RET_INTR_CALL;
    }

    if (timeout < 10) timeout = 5;

    rc = wait_event_interruptible_timeout(pEvnt->wq, _OS_FetchEvent(pEvnt, ev, rEv, option), msecs_to_jiffies(timeout));

    //  if ( rc>0 ) printk("^g^[evnt] ok %d/%d(%d) (%d)\n", rc, msecs_to_jiffies(timeout), timeout, msecs_to_jiffies(timeout) - rc );
    //  else        printk("^g^[evnt] Event timeout..\n");
    //  if ( rc<=0 ) { OS_DEBUG_PrintError_Tag( DBG_LEVEL_WRN, szFile, szFunc, nLine, "Event timeout. req %d ms\n", timeout ); }

    return (rc > 0) ? RET_OK : RET_TIMEOUT;
}
EXPORT_SYMBOL(OS_RecvEvent_Tag);

/*
 * send event
 */
void      OS_SendEvent_Tag(OS_EVENT_T* pEvnt, UINT32 ev,
                           const char* szFile, const char* szFunc, const int nLine)
{
    ULONG   flags;

    PARAM_UNUSED(szFile);
    PARAM_UNUSED(szFunc);
    PARAM_UNUSED(nLine);

    spin_lock_irqsave(&pEvnt->spinlock, flags);
    pEvnt->ev |= ev;
    spin_unlock_irqrestore(&pEvnt->spinlock, flags);

    wake_up_interruptible(&pEvnt->wq);
}
EXPORT_SYMBOL(OS_SendEvent_Tag);

/**
 * clear event
 */
void    OS_ClearEvent_Tag(OS_EVENT_T* pEvnt, const char* szFile, const char* szFunc, const int nLine)
{
    ULONG   flags;

    PARAM_UNUSED(szFile);
    PARAM_UNUSED(szFunc);
    PARAM_UNUSED(nLine);

    spin_lock_irqsave(&pEvnt->spinlock, flags);
    pEvnt->ev = 0x0;
    spin_unlock_irqrestore(&pEvnt->spinlock, flags);
}
EXPORT_SYMBOL(OS_ClearEvent_Tag);

/*========================================================================================
    TIME/TICK OS API IMPLEMENTATION
========================================================================================*/
int     OS_MsecSleep(UINT32 msec)
{
    msleep(msec);
    return RET_OK;
}
EXPORT_SYMBOL(OS_MsecSleep);

void    OS_NsecDelay(UINT32 nsec)
{
    ndelay(nsec);
}
EXPORT_SYMBOL(OS_NsecDelay);

void    OS_UsecDelay(UINT32 usec)
{
    udelay(usec);
}
EXPORT_SYMBOL(OS_UsecDelay);

/* get mili seconds */
UINT64  OS_GetMsecTicks(void)
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
EXPORT_SYMBOL(OS_GetMsecTicks);

/* get micro seconds */
UINT64  OS_GetUsecTicks(void)
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
EXPORT_SYMBOL(OS_GetUsecTicks);

/* get nano seconds */
UINT64  OS_GetNsecTicks(void)
{
#if 0
    ktime_t t = ktime_get();
    UINT64 ns = ktime_to_ns(t);

    return ns;
#else
    struct timespec64 ts;
    ktime_get_raw_ts64(&ts);

    return (u64)ts.tv_sec * 1000000000 + (u64)(ts.tv_nsec);
#endif
}
EXPORT_SYMBOL(OS_GetNsecTicks);

/* get current (sec, msec, usec) information.
 * for the exact time information, all argument should be valid
 */
void    OS_GetCurrentTicks(UINT32* sec, UINT32* msec, UINT32* usec)
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
EXPORT_SYMBOL(OS_GetCurrentTicks);

/*========================================================================================
    TIMER OS API IMPLEMENTATION
========================================================================================*/
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static void _OS_TimerCallback(struct timer_list* t)
#else
static void _OS_TimerCallback(ULONG param)
#endif
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    OS_TIMER_T* pTimer = from_timer(pTimer, t, tmr);
#else
    OS_TIMER_T* pTimer = (OS_TIMER_T*)param;
#endif

    //  DBG_TRACE(" info (object:%p, callback:%p, option:%x, ticks:%4d )\n", pTimer, pTimer->callback, pTimer->option, pTimer->ticks );

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

void        OS_InitTimer(OS_TIMER_T* pTimer)
{
    memset(pTimer, 0x0, sizeof(OS_TIMER_T));
    spin_lock_init(&pTimer->spinlock);
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
    init_timer(&pTimer->tmr);
#endif
}
EXPORT_SYMBOL(OS_InitTimer);

void        OS_StartTimer(OS_TIMER_T* pTimer, OS_TIMER_CALLBACK_T timer_callback, UINT32 option, UINT32 timeout,
                          UINT32 data)
{
    ULONG   ticks;
    ULONG   flags;

    //  DBG_TRACE("timer - msec = %d, tick = %d, HZ = %d\n", timeout, ticks, HZ );

    ticks = MSEC2TICKS(timeout);

    if (ticks == 0)    ticks = 1;


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
    timer_setup(&pTimer->tmr, _OS_TimerCallback, 0);
#else
    pTimer->tmr.function = _OS_TimerCallback;
    pTimer->tmr.data    = (ULONG)pTimer;
#endif
    pTimer->tmr.expires = get_jiffies_64() + pTimer->ticks;
    spin_unlock_irqrestore(&(pTimer->spinlock), flags);

    mod_timer(&pTimer->tmr, get_jiffies_64() + pTimer->ticks);
}
EXPORT_SYMBOL(OS_StartTimer);

void    OS_StopTimer(OS_TIMER_T* pTimer)
{
    ULONG   flags;

    spin_lock_irqsave(&(pTimer->spinlock), flags);
    pTimer->option  = 0x0;
    pTimer->callback = 0x0;
    spin_unlock_irqrestore(&(pTimer->spinlock), flags);

    del_timer_sync(&pTimer->tmr);
}
EXPORT_SYMBOL(OS_StopTimer);

/*========================================================================================
    FILE OS API IMPLEMENTATION
========================================================================================*/
int      OS_OpenFile_Tag(OS_FILE_T* filep, char* fname, int flags, mode_t mode,
                         const char* szFile, const char* szFunc, const int nLine)
{
    OS_CHECK_ERROR(!filep, return RET_ERROR, "null file error\n");
    OS_CHECK_ERROR(!fname, return RET_ERROR, "null file name error\n");

    filep->name = kstrdup(fname, GFP_KERNEL);
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
EXPORT_SYMBOL(OS_OpenFile_Tag);

int      OS_SeekFile_Tag(OS_FILE_T* filep, off_t offset, int whence,
                         const char* szFile, const char* szFunc, const int nLine)
{
    off_t offval;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,9,0)

    OS_CHECK_ERROR(!filep, return -1, "null file error\n");
    OS_CHECK_ERROR(!filep->fd, return -1, "invalid file error\n");

    offval = vfs_llseek(filep->fd, offset, whence);

    return -1;
#else
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

    lg1k_logm_os_debug("file seek ok. name=%s, offset=%ld, whence=%x, offval=%ld\n",
                       filep->name, offset, whence, offval);

    return offval;
#endif
}
EXPORT_SYMBOL(OS_SeekFile_Tag);

int      OS_SizeOfFile_Tag(OS_FILE_T* filep,
                           const char* szFile, const char* szFunc, const int nLine)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    loff_t file_size = i_size_read(file_inode(filep->fd));
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

    return (int)file_size;
}
EXPORT_SYMBOL(OS_SizeOfFile_Tag);

int      OS_WriteFile_Tag(OS_FILE_T* filep, char* buffer, int count,
                          const char* szFile, const char* szFunc, const int nLine)
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
EXPORT_SYMBOL(OS_WriteFile_Tag);

int      OS_ReadFile_Tag(OS_FILE_T* filep, char* buffer, int count,
                         const char* szFile, const char* szFunc, const int nLine)
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
EXPORT_SYMBOL(OS_ReadFile_Tag);

int      OS_CloseFile_Tag(OS_FILE_T* filep,
                          const char* szFile, const char* szFunc, const int nLine)
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
        kfree(filep->name);
        filep->name = NULL;
    }

    return RET_OK;
}
EXPORT_SYMBOL(OS_CloseFile_Tag);

/*========================================================================================
    MEMORY OS API IMPLEMENTATION
========================================================================================*/
void*   OS_KMalloc_Tag(size_t size, const char* szFile, const char* szFunc, const int nLine)
{
    void* ptr = NULL;
    PARAM_UNUSED(szFile);
    PARAM_UNUSED(szFunc);
    PARAM_UNUSED(nLine);

    ASSERT_NOT_CRITICAL();

    ptr = kzalloc(size, GFP_KERNEL);

    if (!ptr)
    {
        OS_DEBUG_PrintError_Tag(DBG_LEVEL_WRN, szFile, szFunc, nLine, "can't kmalloc %d\n", (int)size);
        return NULL;
    }

    return ptr;
}
EXPORT_SYMBOL(OS_KMalloc_Tag);

void    OS_KFree_Tag(void* ptr, const char* szFile, const char* szFunc, const int nLine)
{
    PARAM_UNUSED(szFile);
    PARAM_UNUSED(szFunc);
    PARAM_UNUSED(nLine);

    if (ptr)  kfree(ptr);
}
EXPORT_SYMBOL(OS_KFree_Tag);

#ifdef USE_HMA_ALLOCATOR

#include "hma_alloc.h"

static int  OS_InitRegionHMA(char* name, OS_RGN_T* pRgn, OS_RGN_MGR_TYPE_T mgr_type, const void* phys_addr,
                             const int size, const int block_size,
                             const char* szFile, const char* szFunc, const int nLine)
{
    char* poolname;

    pRgn->mgr_type      = mgr_type;
    pRgn->block_size    = block_size;
    pRgn->block_num     = size / block_size;
    pRgn->mem_pool_size = size;
    pRgn->phys_mem_addr = (void*)phys_addr;
    pRgn->virt_mem_addr = NULL; // ??
    pRgn->mem_alloc_cnt = 0;
    pRgn->mem_alloc_size = 0;
    pRgn->mem_manager   = poolname = (char*)kmalloc(HMA_POOL_LEN, GFP_KERNEL);

    if (name)
    {
        snprintf(poolname, HMA_POOL_LEN, name);
    }
    else
    {
        snprintf(poolname, HMA_POOL_LEN, "osmem-%p", phys_addr);
    }

    if (hma_pool_register_type(poolname, (unsigned long)phys_addr, pRgn->mem_pool_size, CMA_POOL) < 0)
    {
        printk("hma_pool_register failed.\n");
        kfree(poolname);
        return -1;
    }

    return 0;
}

static int  OS_CleanupRegionHMA(OS_RGN_T* pRgn, const char* szFile, const char* szFunc, const int nLine)
{
    char* poolname = pRgn->mem_manager;

    hma_pool_unregister(poolname);

    kfree(poolname);

    return 0;
}

static void* OS_MallocRegionHMA(OS_RGN_T* pRgn, size_t size, const char* szFile, const char* szFunc, const int nLine)
{
    char* poolname = pRgn->mem_manager;
    void* ret;

    ret = (void*)hma_alloc(poolname, size, pRgn->block_size);

    if (ret)
    {
        pRgn->mem_alloc_cnt++;
        //      pRgn->mem_alloc_size += size;
    }
    else
    {
        OS_DEBUG_PrintError_Tag(DBG_LEVEL_WRN, szFile, szFunc, nLine, "Ooops. OS_MallocRegion failed. Can't allocate %d byte\n",
                                (int)size);
    }

    return ret;
}

static int  OS_FreeRegionHMA(OS_RGN_T* pRgn, void* phys_addr, const char* szFile, const char* szFunc, const int nLine)
{
    char* poolname = pRgn->mem_manager;

    if (phys_addr)
    {
        pRgn->mem_alloc_cnt--;
        //      pRgn->mem_alloc_size--; // FIXME: ??
    }
    else
    {
        OS_DEBUG_PrintError_Tag(DBG_LEVEL_WRN, szFile, szFunc, nLine, "Ooops. OS_FreeRegion failed. Null pointer\n");
    }

    hma_free(poolname, (unsigned long)phys_addr);

    return 0;
}

static int  OS_GetRegionInfoHMA(OS_RGN_T* pRgn, OS_RGN_INFO_T* pMemInfo, const char* szFile, const char* szFunc,
                                const int nLine)
{
    pMemInfo->phys_mem_addr = pRgn->phys_mem_addr;
    pMemInfo->block_size    = pRgn->block_size;
    pMemInfo->length        = pRgn->block_size * pRgn->block_num;

    pMemInfo->mem_alloc_cnt = pRgn->mem_alloc_cnt;
    pMemInfo->mem_alloc_size = 0x0; //pRgn->mem_alloc_size;
    pMemInfo->mem_free_size = 0x0; //pMemInfo->length - pMemInfo->mem_alloc_size - pRgn->block_size * pRgn->mem_alloc_cnt;

    return 0;
}

#endif

#ifdef USE_TLSF_ALLOCATOR
typedef struct
{
    void*   addr;
    size_t  size;
}
TLSF_MEM_INFO_T;

#define TLSF_PHYS_ALIGN         12                      /** 2**12 = 4096 */
#define TLSF_VIRT_ALIGN         3                       /** 2**3  = 8 */
#define TLSF_PHYS_BLK_SZ        (1<<TLSF_PHYS_ALIGN)    /** 4096 */
#define TLSF_VIRT_BLK_SZ        (1<<TLSF_VIRT_ALIGN)    /** 8 */
#define TLSF_HDR_SIZE           3216                    /** TLSF header size is fixed */

#define TLSF_MEM_CONV_P2V(pRgn,val) ((LX_CALC_ALIGNED_VALUE(val,12))>>9)
#define TLSF_MEM_CONV_V2P(pRgn,val) ((LX_CALC_ALIGNED_VALUE(val,3 ))<<9)

static int      OS_InitRegionTLSF(OS_RGN_T* pRgn, OS_RGN_MGR_TYPE_T mgr_type, const void* phys_addr, const int size,
                                  const int block_size,
                                  const char* szFile, const char* szFunc, const int nLine)
{
    void*   ptr;
    int     block_num     = size / block_size;
    int     virt_mem_pool_sz = (TLSF_HDR_SIZE * 2) + TLSF_VIRT_BLK_SZ * block_num;

    //  OS_GLOBAL_LOCK();  <-- disable spinlock since it is called at the startup

    memset(pRgn, 0x0, sizeof(OS_RGN_T));

    pRgn->mem_manager   = vmalloc(virt_mem_pool_sz);

    if (!pRgn->mem_manager)
    {
        OS_DEBUG_PrintError_Tag(DBG_LEVEL_WRN, szFile, szFunc, nLine,
                                "Ooops. Out of kernel memory. Can't allocate %d byte for (virt) mem managern", virt_mem_pool_sz);
        memset(pRgn, 0x0, sizeof(OS_RGN_T));
        //OS_GLOBAL_UNLOCK();
        return RET_ERROR;
    }

    pRgn->mgr_type      = mgr_type;
    pRgn->mem_pool_size = size;
    pRgn->block_size    = block_size;
    pRgn->block_num     = block_num;
    pRgn->phys_mem_addr = (void*)phys_addr;
    pRgn->mem_alloc_cnt = 0;
    pRgn->mem_alloc_size = 0;

    init_memory_pool(virt_mem_pool_sz, pRgn->mem_manager);

    OS_PRINT("mem_manager create with %d bytes\n", pRgn->mem_pool_size);

    /* get the base offset for virtual memory space */
    ptr = malloc_ex(TLSF_VIRT_BLK_SZ, pRgn->mem_manager);
    pRgn->virt_mem_addr = ptr;
    free_ex(ptr, pRgn->mem_manager);

    //  OS_GLOBAL_UNLOCK();

    return RET_OK;
}

static int  OS_CleanupRegionTLSF(OS_RGN_T* pRgn, const char* szFile, const char* szFunc, const int nLine)
{
    ULONG flags;
    int ret = RET_OK;

    OS_GLOBAL_LOCK();

    /* If some memory is not freed, report that condition */
    if (pRgn->mem_alloc_cnt)
    {
        OS_DEBUG_PrintError_Tag(DBG_LEVEL_WRN, szFile, szFunc, nLine,
                                "Ooops. Error detected during OS_CleanupRegion. %d memory(s) is(are) not freed\n", pRgn->mem_alloc_cnt);
    }

    destroy_memory_pool(pRgn->mem_manager);
    vfree(pRgn->mem_manager);
    memset(pRgn, 0x0, sizeof(OS_RGN_T));

    OS_GLOBAL_UNLOCK();

    return ret;
}

static void*    OS_MallocRegionTLSF(OS_RGN_T* pRgn, size_t size, const char* szFile, const char* szFunc,
                                    const int nLine)
{
    ULONG   flags;
    size_t  virt_size;
    UINT32  virt_offset;
    UINT32  phys_offset;
    void*   virt_memptr;
    UINT32  phys_memptr = 0x0;

    OS_GLOBAL_LOCK();

    /* convert size to PAGE aligned value */
    size        = LX_CALC_ALIGNED_VALUE(size, TLSF_PHYS_ALIGN);

    /* convert physical size to virtual size */
    virt_size   = TLSF_MEM_CONV_P2V(pRgn, size);
    size        = TLSF_MEM_CONV_V2P(pRgn, virt_size);

    /* get the virtual memory from memory manager, calculate virtual offset and convert it to physical offset */
    virt_memptr = malloc_ex(virt_size, pRgn->mem_manager);

    if (virt_memptr)
    {
        TLSF_MEM_INFO_T mem_info;

        virt_offset = (UINT32)virt_memptr - (UINT32)pRgn->virt_mem_addr;
        phys_offset = TLSF_MEM_CONV_V2P(pRgn, virt_offset);
        phys_memptr = (UINT32)pRgn->phys_mem_addr + phys_offset;

        /* record allocation history */
        pRgn->mem_alloc_size += size;
        pRgn->mem_alloc_cnt++;

        /* record physical address information. this data is used to confirm physical address when FREE request */
        mem_info.addr = (void*)phys_memptr;
        mem_info.size = size;
        memcpy((void*)virt_memptr, &mem_info, sizeof(TLSF_MEM_INFO_T));

        OS_PRINT("%s : virt_memptr %p, virt_size %d, virt_offset 0x%x, phys_offset 0x%x\n", __F__, (UINT32*)virt_memptr,
                 virt_size, virt_offset, phys_offset);
    }
    else
    {
        OS_DEBUG_PrintError_Tag(DBG_LEVEL_WRN, szFile, szFunc, nLine, "Ooops. OS_MallocRegion failed. Can't allocate %d byte\n",
                                size);
        phys_memptr = 0x0;
    }

    OS_GLOBAL_UNLOCK();

    return (void*)phys_memptr;
}

static int  OS_FreeRegionTLSF(OS_RGN_T* pRgn, void* phys_addr, const char* szFile, const char* szFunc, const int nLine)
{
    ULONG   flags;
    UINT32  virt_offset;
    UINT32  virt_memptr;
    UINT32  phys_offset;
    UINT32  phys_memptr = (UINT32)phys_addr;

    int     ret = RET_OK;

    if (phys_memptr)
    {
        TLSF_MEM_INFO_T mem_info;

        OS_GLOBAL_LOCK();

        /* calculate offset */
        phys_offset = phys_memptr - (UINT32)pRgn->phys_mem_addr;
        virt_offset = TLSF_MEM_CONV_P2V(pRgn, phys_offset);

        OS_PRINT("%s : virt_offset %d, phys_offset %d\n", __F__, virt_offset, phys_offset);

        virt_memptr = (UINT32)pRgn->virt_mem_addr + virt_offset;

        /* check if physical address is the same as the recorded one */
        memcpy(&mem_info, (void*)virt_memptr, sizeof(TLSF_MEM_INFO_T));

        OS_PRINT("%s : virt_memptr %p, phys_addr %p, size %d\n", __F__, (UINT32*)virt_memptr, (UINT32*)mem_info.addr,
                 mem_info.size);
        OS_PRINT("%s : virt_offset 0x%x, phys_offset 0x%x\n", __F__, virt_offset, phys_offset);

        if (mem_info.addr == phys_addr)
        {
            pRgn->mem_alloc_cnt--;
            pRgn->mem_alloc_size -= mem_info.size;

            free_ex((void*)virt_memptr, pRgn->mem_manager);
        }
        else
        {
            OS_DEBUG_PrintError_Tag(DBG_LEVEL_WRN, szFile, szFunc, nLine,
                                    "Ooops. OS_FreeRegion failed. Invalid phys address %p. Actual address seems %p.\n", phys_addr, mem_info.addr);
            ret = RET_ERROR;
        }

        OS_GLOBAL_UNLOCK();
    }
    else
    {
        OS_DEBUG_PrintError_Tag(DBG_LEVEL_WRN, szFile, szFunc, nLine,
                                "Ooops. OS_FreeRegion failed. Null pointer\n");
        ret = RET_ERROR;
    }

    return ret;
}

static int  OS_GetRegionInfoTLSF(OS_RGN_T* pRgn, OS_RGN_INFO_T* pMemInfo, const char* szFile, const char* szFunc,
                                 const int nLine)
{
    ULONG   flags;
    PARAM_UNUSED(szFile);
    PARAM_UNUSED(szFunc);
    PARAM_UNUSED(nLine);

    OS_GLOBAL_LOCK();

    pMemInfo->phys_mem_addr = pRgn->phys_mem_addr;
    pMemInfo->block_size    = pRgn->block_size;
    pMemInfo->length        = pRgn->block_size * pRgn->block_num;

    pMemInfo->mem_alloc_cnt = pRgn->mem_alloc_cnt;
    pMemInfo->mem_alloc_size = pRgn->mem_alloc_size;
    pMemInfo->mem_free_size = pRgn->mem_pool_size - pRgn->mem_alloc_size;

    OS_GLOBAL_UNLOCK();

    return RET_OK;
}
#endif

int      OS_InitRegionEx_Tag(char* name, OS_RGN_T* pRgn, OS_RGN_MGR_TYPE_T mgr_type, const void* phys_addr,
                             const int size, const int block_size,
                             const char* szFile, const char* szFunc, const int nLine)
{
#ifdef USE_TLSF_ALLOCATOR

    if (mgr_type == OS_RGN_MGR_TYPE_TLSF)
        return OS_InitRegionTLSF(name, pRgn, mgr_type, phys_addr, size, block_size, szFile, szFunc, nLine);

#endif
#ifdef USE_HMA_ALLOCATOR

    if (mgr_type == OS_RGN_MGR_TYPE_HMA)
        return OS_InitRegionHMA(name, pRgn, mgr_type, phys_addr, size, block_size, szFile, szFunc, nLine);

#endif
    return RET_NOT_SUPPORTED;
}
EXPORT_SYMBOL(OS_InitRegionEx_Tag);

int     OS_CleanupRegion_Tag(OS_RGN_T* pRgn, const char* szFile, const char* szFunc, const int nLine)
{
    OS_RGN_MGR_TYPE_T mgr_type = pRgn->mgr_type;

#ifdef USE_TLSF_ALLOCATOR

    if (mgr_type == OS_RGN_MGR_TYPE_TLSF)
        return OS_CleanupRegionTLSF(pRgn, szFile, szFunc, nLine);

#endif
#ifdef USE_HMA_ALLOCATOR

    if (mgr_type == OS_RGN_MGR_TYPE_HMA)
        return OS_CleanupRegionHMA(pRgn, szFile, szFunc, nLine);

#endif
    return RET_NOT_SUPPORTED;
}
EXPORT_SYMBOL(OS_CleanupRegion_Tag);

void*   OS_MallocRegion_Tag(OS_RGN_T* pRgn, size_t size, const char* szFile, const char* szFunc, const int nLine)
{
    OS_RGN_MGR_TYPE_T mgr_type = pRgn->mgr_type;
#ifdef USE_TLSF_ALLOCATOR

    if (mgr_type == OS_RGN_MGR_TYPE_TLSF)
        return OS_MallocRegionTLSF(pRgn, size, szFile, szFunc, nLine);

#endif
#ifdef USE_HMA_ALLOCATOR

    if (mgr_type == OS_RGN_MGR_TYPE_HMA)
        return OS_MallocRegionHMA(pRgn, size, szFile, szFunc, nLine);

#endif
    return NULL;
}
EXPORT_SYMBOL(OS_MallocRegion_Tag);

int     OS_FreeRegion_Tag(OS_RGN_T* pRgn, void* phys_addr, const char* szFile, const char* szFunc, const int nLine)
{
    OS_RGN_MGR_TYPE_T mgr_type = pRgn->mgr_type;
#ifdef USE_TLSF_ALLOCATOR

    if (mgr_type == OS_RGN_MGR_TYPE_TLSF)
        return OS_FreeRegionTLSF(pRgn, phys_addr, szFile, szFunc, nLine);

#endif
#ifdef USE_HMA_ALLOCATOR

    if (mgr_type == OS_RGN_MGR_TYPE_HMA)
        return OS_FreeRegionHMA(pRgn, phys_addr, szFile, szFunc, nLine);

#endif
    return RET_NOT_SUPPORTED;
}
EXPORT_SYMBOL(OS_FreeRegion_Tag);

int     OS_GetRegionInfo_Tag(OS_RGN_T* pRgn, OS_RGN_INFO_T* pMemInfo, const char* szFile, const char* szFunc,
                             const int nLine)
{
    OS_RGN_MGR_TYPE_T mgr_type = pRgn->mgr_type;

#ifdef USE_TLSF_ALLOCATOR

    if (mgr_type == OS_RGN_MGR_TYPE_TLSF)
        return OS_GetRegionInfoTLSF(pRgn, pMemInfo, szFile, szFunc, nLine);

#endif
#ifdef USE_HMA_ALLOCATOR

    if (mgr_type == OS_RGN_MGR_TYPE_HMA)
        return OS_GetRegionInfoHMA(pRgn, pMemInfo, szFile, szFunc, nLine);

#endif
    return RET_NOT_SUPPORTED;
}
EXPORT_SYMBOL(OS_GetRegionInfo_Tag);

/*========================================================================================
    REGS OS API IMPLEMENTATION
========================================================================================*/
int     OS_WrReg(UINT32 regAddr, UINT32 val)
{
    void* vaddr = ioremap(regAddr, 4);

    if (!vaddr)
    {
        printk("ioremap error. reg 0x%08x \n", regAddr);
        return RET_ERROR;
    }

    __raw_writel(val, (volatile void*)vaddr);
    iounmap((volatile void*)vaddr);

    //  printk("[wr_reg] 0x%08x = 0x%08x (ok?)\n", regAddr, val );

    return RET_OK;
}
EXPORT_SYMBOL(OS_WrReg);

int     OS_RdReg(UINT32 regAddr, UINT32* pVal)
{
    UINT32 val = 0x0;
    void* vaddr = ioremap(regAddr, 4);

    if (!vaddr)
    {
        printk("ioremap error. reg 0x%08x \n", regAddr);
        return RET_ERROR;
    }

    val = __raw_readl((volatile void*)vaddr);
    iounmap((void*)vaddr);

    *pVal = val;
    return RET_OK;
}
EXPORT_SYMBOL(OS_RdReg);

int     OS_WrRegList(UINT32 regList[], UINT32 valList[], int num)
{
    int i;
    int errCnt = 0;

    for (i = 0; i < num; i++)
    {
        if (RET_OK != OS_WrReg(regList[i], valList[i])) errCnt++;
    }

    return (0 == errCnt) ? RET_OK : RET_ERROR;
}
EXPORT_SYMBOL(OS_WrRegList);

int     OS_RdRegList(UINT32 regList[], UINT32 valList[], int num)
{
    int i;
    int errCnt = 0;

    for (i = 0; i < num; i++)
    {
        if (RET_OK != OS_RdReg(regList[i], &valList[i])) errCnt++;
    }

    return (0 == errCnt) ? RET_OK : RET_ERROR;
}
EXPORT_SYMBOL(OS_RdRegList);

int     OS_WrData(UINT32 phys_addr, UINT32* data_list, int num_data)
{
    int     i;
    void*   vaddr = (void*)vmap_phys(phys_addr, (UINT32)(num_data * sizeof(UINT32)));

    if (!vaddr)
    {
        printk("ioremap error. phys_addr 0x%08x len %d\n", phys_addr, (int)sizeof(UINT32)*num_data);
        return RET_ERROR;
    }

    for (i = 0; i < num_data; i++)
    {
        __raw_writel(data_list[i], (volatile void*)((UINT32*)vaddr + i));
    }

    vunmap_phys((void*)vaddr);

    wmb();

    return RET_OK;
}
EXPORT_SYMBOL(OS_WrData);

int     OS_RdData(UINT32 phys_addr, UINT32* data_list, int num_data)
{
    int     i;
    void*   vaddr = (void*)vmap_phys(phys_addr, (UINT32)(num_data * sizeof(UINT32)));

    if (!vaddr)
    {
        printk("ioremap error. phys_addr 0x%08x len %d\n", phys_addr, (int)sizeof(UINT32)*num_data);
        return RET_ERROR;
    }

    for (i = 0; i < num_data; i++)
    {
        data_list[i] = __raw_readl((volatile void*)((UINT32*)vaddr + i));
    }

    vunmap_phys((void*)vaddr);

    return RET_OK;
}
EXPORT_SYMBOL(OS_RdData);

int     OS_HexDumpEx(UINT32 disp_addr, void* data_ptr, UINT32 data_cnt, char* output_buf)
{
    int output_len = 0;

    if (data_cnt > 0)
    {
        int width = 16;
        int j, i = 0;

        char*   str = (char*)data_ptr;
        char*   buf_ptr = (char*)OS_Malloc(160);
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
            printk("--------------------------------------------------------------------------------\n");
            printk("address     00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F  0123456789ABCDEF\n");
            printk("--------------------------------------------------------------------------------\n");
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
                printk("%s\n", buf_ptr);
            }
        }

        OS_Free(buf_ptr);
    }

    return output_len;
}
EXPORT_SYMBOL(OS_HexDumpEx);

/*========================================================================================
    IOMAP OS API IMPLEMENTATION
========================================================================================*/
int      OS_OpenCacheMap(OS_CACHE_MAP_T* pMap, ULONG phys_addr, UINT32 length)
{
    OS_CHECK_ERROR(NULL == pMap, return RET_ERROR, "null param\n");
    OS_CHECK_ERROR(0x0 == phys_addr || 0 == length, return RET_ERROR, "invalid addr info\n");

    length = LX_CALC_ALIGNED_VALUE(length, 12);

    pMap->phys_addr = phys_addr;
    pMap->length    = length;
    pMap->virt_addr = vmap_phys_cache(phys_addr, length);
    return (pMap->virt_addr) ? RET_OK : RET_ERROR;
}

int      OS_CloseCacheMap(OS_CACHE_MAP_T* pMap)
{
    OS_CHECK_ERROR(NULL == pMap, return RET_ERROR, "null param\n");
    OS_CHECK_ERROR(0x0 == pMap->virt_addr || 0 == pMap->length, return RET_ERROR, "invalid addr info\n");

    vunmap_phys((void*)pMap->virt_addr);
    return RET_OK;
}

int      OS_InvalCacheMap(OS_CACHE_MAP_T* pMap, UINT32 off, UINT32 length)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 19, 0))

    unsigned long start = (unsigned long)(pMap->virt_addr + off);  //phys_to_virt(pMap->phys_addr + off);
    unsigned long pstart = (unsigned long)(pMap->phys_addr + off);  //phys_to_virt(pMap->phys_addr + off);
    unsigned long size = (unsigned long)length;

    dcache_inval_poc(start, start + size);

#ifndef __aarch64__
    outer_inv_range(pstart, pstart + size);
#endif

    return RET_OK;
#else

#ifndef __aarch64__
    ULONG   phys_addr = pMap->phys_addr + off;
#endif
    void*   virt_addr = (void*)((uintptr_t)pMap->virt_addr + (uintptr_t)off);

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

int      OS_CleanCacheMap(OS_CACHE_MAP_T* pMap, UINT32 off, UINT32 length)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 19, 0))

    unsigned long start = (unsigned long)(pMap->virt_addr + off);  //phys_to_virt(pMap->phys_addr + off);
    unsigned long pstart = (unsigned long)(pMap->phys_addr + off);  //phys_to_virt(pMap->phys_addr + off);
    unsigned long size = (unsigned long)length;

    dcache_clean_poc(start, start + size);

#ifndef __aarch64__
    outer_clean_range(pstart, pstart + length);
#endif

    return RET_OK;
#else

#ifndef __aarch64__
    ULONG   phys_addr = pMap->phys_addr + off;
#endif
    void*   virt_addr = (void*)((uintptr_t)pMap->virt_addr + (uintptr_t)off);

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

#endif
    return RET_OK;
}

/*========================================================================================
    SIMPLE CODE LIB IMPLEMENTATION
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

char* os_strdup(const char* s, size_t max)
{
    size_t len;
    char* buf;

    max -= 1;

    if (!s)
        return NULL;

    len = strnlen(s, max);
    buf = vmalloc(len + 1);

    if (buf)
    {
        memcpy(buf, s, len);
        buf[len] = '\0';
    }

    return buf;
}
EXPORT_SYMBOL(os_strdup);

int OS_ScanKernelCmdline(const char* fmt_str, char* val_str)
{
    int     ret = RET_ERROR;
    char*   cmd_buf = NULL;
    int     cmd_buf_sz = 4095;

    char* tok, *sav_tok;
    char delim[] = " \t\n";

    if (NULL == (cmd_buf = OS_Malloc(cmd_buf_sz + 1)))
    {
        printk("<error> can't alloc cmd_buf\n"); goto func_exit;
    }

#ifdef MODULE  //raxis.lim (2013/09/16) -- kernel exports saved_command_line symbol..
    {
        OS_FILE_T file;

        if (RET_OK != OS_OpenFile(&file, "/proc/cmdline", O_RDONLY | O_LARGEFILE, 0666))
        {
            printk("<error> can't open /proc/cmdline\n"); goto func_exit;
        }

        if (0 >= OS_ReadFile(&file, cmd_buf, cmd_buf_sz))
        {
            OS_CloseFile(&file);
            printk("<error> can't read /proc/cmdline\n"); goto func_exit;
        }

        OS_CloseFile(&file);
    }
#else
    {
#ifdef HWOPT_PARSE_TEST
        printk("hwopt test mode !!!\n");
        cmd_buf_sz = snprintf(cmd_buf, cmd_buf_sz, "%s", test_command_line);
#else
        extern char* saved_command_line;
        cmd_buf_sz = snprintf(cmd_buf, cmd_buf_sz, "%s", saved_command_line);
#endif
    }
#endif

    tok = simple_strtok(cmd_buf, delim, &sav_tok);

    while (tok)
    {
        if (1 == sscanf(tok, fmt_str, val_str)) { ret = RET_OK; break; }

        tok = simple_strtok(NULL, delim, &sav_tok);
    }

func_exit:

    if (cmd_buf) OS_Free(cmd_buf);

    return ret;
}
EXPORT_SYMBOL(OS_ScanKernelCmdline);

int OS_ScanKernelCmdlineToken(const char* token)
{
    int     ret = RET_ERROR;
    char*   cmd_buf = NULL;
    int     cmd_buf_sz = 4095;

    char* tok, *sav_tok;
    char delim[] = " \t\n";

    if (NULL == (cmd_buf = OS_Malloc(cmd_buf_sz + 1)))
    {
        printk("<error> can't alloc cmd_buf\n"); goto func_exit;
    }

#ifdef MODULE  //raxis.lim (2013/09/16) -- kernel exports saved_command_line symbol..
    {
        OS_FILE_T file;

        if (RET_OK != OS_OpenFile(&file, "/proc/cmdline", O_RDONLY | O_LARGEFILE, 0666))
        {
            printk("<error> can't open /proc/cmdline\n"); goto func_exit;
        }

        if (0 >= OS_ReadFile(&file, cmd_buf, cmd_buf_sz))
        {
            OS_CloseFile(&file);
            printk("<error> can't read /proc/cmdline\n"); goto func_exit;
        }

        OS_CloseFile(&file);
    }
#else
    {
#ifdef HWOPT_PARSE_TEST
        printk("hwopt test mode !!!\n");
        cmd_buf_sz = snprintf(cmd_buf, cmd_buf_sz, "%s", test_command_line);
#else
        extern char* saved_command_line;
        cmd_buf_sz = snprintf(cmd_buf, cmd_buf_sz, "%s", saved_command_line);
#endif
    }
#endif

    tok = simple_strtok(cmd_buf, delim, &sav_tok);

    while (tok)
    {
        if (!strncasecmp(tok, token, strlen(token))) { ret = RET_OK; break; }

        tok = simple_strtok(NULL, delim, &sav_tok);
    }

func_exit:

    if (cmd_buf) OS_Free(cmd_buf);

    return ret;
}
EXPORT_SYMBOL(OS_ScanKernelCmdlineToken);


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
        pr_warn("vmap: address is not-page-aligned %pap\n", &addr);
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
        pr_warn("vunmap: address is not-page-aligned vaddr:%p\n", addr);

    vaddr = (void*)((unsigned long)addr & PAGE_MASK);

    if (VMALLOC_START <= vaddr && vaddr < VMALLOC_END)
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



/** @} */
