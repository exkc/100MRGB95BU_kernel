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
 *  main driver implementation for gfx device.
 *  gfx device will teach you how to make device driver with new platform.
 *
 *  author      raxis.lim (raxis.lim@lge.com)
 *  version     1.0
 *  date        2009.12.30
 *  note        Additional information.
 *
 *  @addtogroup lg1150_gfx
 *  @{
 */

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/
#undef  SUPPORT_GFX_DEVICE_READ_WRITE_FOPS
#define SUPPORT_GFX_UNLOCKED_IOCTL

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <asm/cacheflush.h>
#include <linux/dma-mapping.h>
#include <linux/dmaengine.h>
#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/vmalloc.h>

#include <linux/delay.h>
#include <linux/list.h>
#include <linux/seq_file.h>
#include "os_util.h"
#include "base_device.h"
#include "gfx_impl.h"

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
#define report_runtime_status(level, ref_count, type, result)   \
    do {\
        GFX_NOTI("LowPower::%s::%s::%s::%d::%s-%s::%s::%s\n",\
            level,  \
            "groupother", \
            "gfx", \
            ref_count, \
            current->group_leader->comm, \
            current->comm, \
            type, \
            result);\
    } while(0)

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/* each gfx device context */
typedef struct
{
    dev_t                   devno;              ///< device number
    struct cdev             cdev;               ///< char device structure

    // add device specific data
}
GFX_DEVICE_T;


typedef struct
{
    UINT32  pid;
    UINT32  ref_cnt;
    char    psname[TASK_COMM_LEN];

    struct list_head list;
}
PID_REF_CNT_T;

/*----------------------------------------------------------------------------------------
    Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern  void    GFX_H13_InitHAL(GFX_HAL_T*  hal);    /* implemented at h13/gfx_drv_h13.c */
extern  void    GFX_M14_InitHAL(GFX_HAL_T*  hal);    /* implemented at m14/gfx_drv_m14.c */
extern  void    GFX_H14_InitHAL(GFX_HAL_T*  hal);    /* implemented at h14/gfx_drv_h14.c */
extern  void    GFX_H15_InitHAL(GFX_HAL_T*  hal);    /* implemented at h15/gfx_drv_h15.c */
extern  void    GFX_M16_InitHAL(GFX_HAL_T*  hal);    /* implemented at m16/gfx_drv_m16.c */
extern  void    GFX_M16P_InitHAL(GFX_HAL_T*  hal);   /* implemented at m16p/gfx_drv_m16.c */
extern  void    GFX_L18F_InitHAL(GFX_HAL_T*  hal);   /* implemented at l18f/gfx_drv_l18f.c */
extern  void    GFX_O18_InitHAL(GFX_HAL_T*  hal);    /* implemented at o18/gfx_drv_o18.c */
extern  void    GFX_M19_InitHAL(GFX_HAL_T*  hal);    /* implemented at m19/gfx_drv_m19.c */
extern  void    GFX_O20_InitHAL(GFX_HAL_T*  hal);    /* implemented at o20/gfx_drv_o20.c */
extern  void    GFX_E60_InitHAL(GFX_HAL_T*  hal);    /* implemented at e60/gfx_drv_e60.c */
extern  void    GFX_O22_InitHAL(GFX_HAL_T*  hal);    /* implemented at o22/gfx_drv_o22.c */
extern  void    GFX_M23_InitHAL(GFX_HAL_T*  hal);    /* implemented at o22/gfx_drv_o22.c */
extern  void    GFX_O24_InitHAL(GFX_HAL_T*  hal);    /* implemented at o24/gfx_drv_o24.c */
extern  void    GFX_O26_InitHAL(GFX_HAL_T*  hal);    /* implemented at o26/gfx_drv_o24.c */

int  GFX_probe(struct platform_device* pdev);
void GFX_PreInit(void);
int  GFX_Init(void);
void GFX_Cleanup(void);
void GFX_ReportPIDRefList(struct seq_file* m);
void GFX_ReportStatus(struct seq_file* m);
void GFX_ReportPMStatus(struct seq_file* m);

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/
int             g_gfx_major = GFX_MAJOR;
int             g_gfx_minor = GFX_MINOR;
int             g_gfx_debug_fd;
int             g_gfx_trace_depth;

LX_GFX_CFG_T    g_gfx_cfg;
GFX_HAL_T       g_gfx_hal;


static int g_gfx_safe_runtime_pm = 1;
module_param_named(gfx_safe_runtime_pm, g_gfx_safe_runtime_pm,  int, 0644);

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int      GFX_Open(struct inode* inode, struct file* filp);
static int      GFX_Close(struct inode* inode, struct file* file);
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)) || !defined(SUPPORT_GFX_UNLOCKED_IOCTL)
static int      GFX_Ioctl(struct inode* inode, struct file* filp, UINT32 cmd, ULONG arg);
#else
static long     GFX_Ioctl(struct file* filp, UINT32 cmd, ULONG arg);
#ifdef CONFIG_COMPAT
static long     GFX_Compat_Ioctl(struct file* filp, UINT32 cmd, ULONG arg);
#endif
#endif
static int      GFX_mmap(struct file* file, struct vm_area_struct* vma);
#ifdef SUPPORT_GFX_DEVICE_READ_WRITE_FOPS
static ssize_t  GFX_Read(struct file*, char*, size_t, loff_t*);
static ssize_t  GFX_Write(struct file*, const char*, size_t, loff_t*);
#endif

static int      GFX_IncPidRefCount(UINT32 pid);
static int      GFX_DecPidRefCount(UINT32 pid);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
static DEFINE_MUTEX(gfx_dev_mtx);
static GFX_DEVICE_T*        g_gfx_device;
static struct list_head     gfx_pid_ref_list;

/**
 * file I/O description for gfx device
 *
*/
static struct file_operations g_gfx_fops =
{
    .open   = GFX_Open,
    .release = GFX_Close,
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)) || !defined(SUPPORT_GFX_UNLOCKED_IOCTL)
    .ioctl  = GFX_Ioctl,
#else
    .unlocked_ioctl = GFX_Ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl   = GFX_Compat_Ioctl,
#endif
#endif
    .mmap   = GFX_mmap,
#ifdef SUPPORT_GFX_DEVICE_READ_WRITE_FOPS
    .read   = GFX_Read,
    .write  = GFX_Write,
#else
    .read   = NULL,
    .write  = NULL,
#endif
};


static inline char*         GFX_IOC2STR(UINT32 ioc_cmd)
{
    switch (ioc_cmd)
    {
        case GFX_IO_RESET:                  return "GFX_IO_RESET";

        case GFX_IOR_CHIP_REV_INFO:         return "GFX_IOR_CHIP_REV_INFO";

        case GFX_IOR_GET_CFG:               return "GFX_IOR_GET_CFG";

        case GFX_IORW_ALLOC_SURFACE:        return "GFX_IORW_ALLOC_SURFACE";

        case GFX_IOW_FREE_SURFACE:          return "GFX_IOW_FREE_SURFACE";

        case GFX_IORW_QUERY_SURFACE_SETTING: return "GFX_IORW_QUERY_SURFACE_SETTING";

        case GFX_IOW_SET_SURFACE_PALETTE:   return "GFX_IOW_SET_SURFACE_PALETTE";

        case GFX_IOR_GET_SURFACE_PALETTE:   return "GFX_IOR_GET_SURFACE_PALETTE";

        case GFX_IORW_GET_SURFACE_MEM_INFO: return "GFX_IORW_GET_SURFACE_MEM_INFO";

        case GFX_IOW_BLEND:                 return "GFX_IOW_BLEND";

        case GFX_IOW_MANUAL_BLEND:          return "GFX_IOW_MANUAL_BLEND";

        case GFX_IOW_SET_CSC_CONV_TBL:      return "GFX_IOW_SET_CSC_CONV_TBL";

        case GFX_IOR_GET_CMD_DELAY:         return "GFX_IOR_GET_CMD_DELAY";

        case GFX_IOW_SET_CMD_DELAY:         return "GFX_IOW_SET_CMD_DELAY";

        case GFX_IOW_SET_BATCH_RUN_MODE:    return "GFX_IOW_SET_BATCH_RUN_MODE";

        case GFX_IOR_GET_BATCH_RUN_MODE:    return "GFX_IOR_GET_BATCH_RUN_MODE";

        case GFX_IOW_SET_GRAPHIC_SYNC_MODE: return "GFX_IOW_SET_GRAPHIC_SYNC_MODE";

        case GFX_IOW_WAIT_FOR_SYNC:         return "GFX_IOW_WAIT_FOR_SYNC";

        case GFX_IOR_GET_MEM_STAT:          return "GFX_IOR_GET_MEM_STAT";

        default:                            return "Unknown IOCTL";
    }
}

/** lock GFX device */
void            GFX_LockDevice(void)
{
    mutex_lock(&gfx_dev_mtx);
}

/** unlock GFX device */
void            GFX_UnlockDevice(void)
{
    mutex_unlock(&gfx_dev_mtx);
}

// 일부 프로세스에서의 과도한 open, close 호출 메시지를 막을 수 있도록 조치 필요함
static char* _pm_runtime_msg_ignore_taskcomm[] =
{
    "gal_renderd",
};

static int GFX_CheckRuntimeReportPermission(void)
{
    int i;

    for (i = 0; i < NELEMENTS(_pm_runtime_msg_ignore_taskcomm); i++)
    {
        if (!strncmp(current->group_leader->comm, _pm_runtime_msg_ignore_taskcomm[i], TASK_COMM_LEN))
        {
            return RET_ERROR;
        }
    }

    return RET_OK;
}

/*========================================================================================
    Implementation Group
========================================================================================*/
/** initialize HAL function list
 *
 */
static void    GFX_InitHAL(void)
{
    memset(&g_gfx_hal, 0x0, sizeof(GFX_HAL_T));

    /* initialize HAL (Hardware Abstraction Layer) */
    if (0)                         { /* do nothing */ }

#ifdef INCLUDE_M17_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_M16P) { GFX_M16P_InitHAL(&g_gfx_hal); }

#endif
#ifdef INCLUDE_L18_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_L18)  { GFX_L18F_InitHAL(&g_gfx_hal); }

#endif
#ifdef INCLUDE_O18_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_O18) { GFX_O18_InitHAL(&g_gfx_hal); }

#endif
#ifdef INCLUDE_M19_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_M19)  { GFX_M19_InitHAL(&g_gfx_hal); }

#endif
#ifdef INCLUDE_O20_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_O20)  { GFX_O20_InitHAL(&g_gfx_hal); }

#endif
#ifdef INCLUDE_E60_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_E60)  { GFX_E60_InitHAL(&g_gfx_hal); }

#endif
#ifdef INCLUDE_O22_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_O22)  { GFX_O22_InitHAL(&g_gfx_hal); }

#endif
#ifdef INCLUDE_M23_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_M23)  { GFX_M23_InitHAL(&g_gfx_hal); }

#endif
#ifdef INCLUDE_O24_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_O24)  { GFX_O24_InitHAL(&g_gfx_hal); }

#endif
#ifdef INCLUDE_O26_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_O26)  { GFX_O26_InitHAL(&g_gfx_hal); }

#endif
    else                                { GFX_ERROR("unknown chip 0x%x\n", lx_chip_rev()); }
}

/** initialize GFX environment before the real initialization
 *
 *  @note GFX_InitHAL should be called before calling any other functions.
 *  @note GFX_InitCFG should be called before calling any other functions.
 */
void    GFX_PreInit(void)
{
    GFX_InitHAL();
    GFX_InitCfg();
}

/*========================================================================================
    Implementation Group
========================================================================================*/
/**
 *
 * suspending module.
 *
 * @param   struct platform_device *pdev pm_message_t state
 * @return  int 0 : OK , -1 : NOT OK
 *
 */
static int GFX_suspend(struct device* dev)
{
#ifdef KDRV_CONFIG_PM_GFX
    GFX_PDEV_CTX_T* pdev_ctx = platform_get_drvdata(to_platform_device(dev));
    //int count = 0;

    printk("GFX - suspend BEGIN\n");

    // add here the suspend code
    /*
        while(1)
        {
            if(GFX_IsGfxIdle() == TRUE)
                break;
            if(count++ > 10)
                return -1;
            else
            {
                mdelay(10);
            }

        }

    */
    GFX_RunSuspend();
    pdev_ctx->is_suspended = 1;
    printk("GFX - suspend OK\n");
#endif
    return RET_OK;
}

/**
 *
 * resuming module.
 *
 * @param   struct platform_device *
 * @return  int 0 : OK , -1 : NOT OK
 *
 */
static int GFX_resume(struct device* dev)
{
#ifdef KDRV_CONFIG_PM_GFX
    GFX_PDEV_CTX_T* pdev_ctx = platform_get_drvdata(to_platform_device(dev));

    printk("GFX - resume BEGIN\n");

    if (!pdev_ctx->is_suspended)
    {
        printk("GFX - resume FAIL\n");
    }

    // add here the resume code
    GFX_RunResume();

    pdev_ctx->is_suspended = false;
    printk("GFX - resume OK\n");
#endif
    return RET_OK;
}

static int GFX_thaw(struct device* dev)
{
    /* do nothing */
    return RET_OK;
}

static int GFX_restore(struct device* dev)
{
    return GFX_resume(dev);
}

static int GFX_freeze(struct device* dev)
{
    /* do nothing */
    return RET_OK;
}

static int GFX_runtime_resume(struct device* dev)
{
    GFX_PDEV_CTX_T* pdev_ctx = platform_get_drvdata(to_platform_device(dev));

    GFX_PM_DEBUG("do runtime resume. open_count=%d, is_runtime_active=%d\n",
                 pdev_ctx->dev_open_count, pdev_ctx->is_runtime_active);

    GFX_CHECK_ERROR(pdev_ctx->is_runtime_active, return RET_OK, "device already runtime_active\n");
    GFX_CHECK_ERROR(pdev_ctx->dev_open_count > 1, /* nop */, "invalid call ? dev_open_count(%d) != 1\n",
                    pdev_ctx->dev_open_count);

    /* TODO: do clock gating off */
    GFX_PM_DEBUG("runtime resume HW clock gating <off>\n");
    GFX_RunClkOffCommand();

    pdev_ctx->is_runtime_active = true;
    GFX_PM_DEBUG("runtime resume completed. is_runtime_active=%d\n", pdev_ctx->is_runtime_active);

    report_runtime_status("info", pdev_ctx->dev_open_count, "resume", "ok");

    return RET_OK;
}

static int GFX_runtime_suspend(struct device* dev)
{
    GFX_PDEV_CTX_T* pdev_ctx = platform_get_drvdata(to_platform_device(dev));

    GFX_PM_DEBUG("do runtime suspend. open_count=%d, is_runtime_active=%d\n",
                 pdev_ctx->dev_open_count, pdev_ctx->is_runtime_active);

    GFX_CHECK_ERROR(!pdev_ctx->is_runtime_active, return RET_OK, "device already runtime_suspend\n");

    if (g_gfx_safe_runtime_pm)
    {
        /* just return error !!! don't worry about app's stability */
        GFX_CHECK_ERROR(pdev_ctx->dev_open_count > 0, return -EBUSY, "invalid call ? dev_open_count(%d) != 0\n",
                        pdev_ctx->dev_open_count);
    }

    /* TODO: do clock gating on */
    GFX_PM_DEBUG("runtime resume HW clock gating <on>\n");
    GFX_RunClkOnCommand();

    pdev_ctx->is_runtime_active = false;
    GFX_PM_DEBUG("runtime suspend completed. is_runtime_active=%d\n", pdev_ctx->is_runtime_active);

    report_runtime_status("info", pdev_ctx->dev_open_count, "suspend", "ok");

    return RET_OK;
}

/**
 *
 * probing module.
 *
 * @param   struct platform_device *pdev
 * @return  int 0 : OK , -1 : NOT OK
 *
 */
int /*__init*/ GFX_probe(struct platform_device* pdev)
{
    GFX_PDEV_CTX_T* pdev_ctx = (GFX_PDEV_CTX_T*)vzalloc(sizeof(GFX_PDEV_CTX_T));

    GFX_CHECK_ERROR(NULL == pdev_ctx, return RET_ERROR, "alloc error\n");

    pdev_ctx->is_suspended = false;
    pdev_ctx->is_runtime_active = true;

    platform_set_drvdata(pdev, pdev_ctx);

    INIT_LIST_HEAD(&gfx_pid_ref_list);

    // TODO: add here driver registering code & allocating resource code

    return RET_OK;
}

/**
 *
 * module remove function. this function will be called in rmmod fbdev module.
 *
 * @param   struct platform_device
 * @return  int 0 : OK , -1 : NOT OK
 *
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void  GFX_remove(struct platform_device* pdev)
#else
static int  GFX_remove(struct platform_device* pdev)
#endif
{
    GFX_PDEV_CTX_T* pdev_ctx;

    // add here driver unregistering code & deallocating resource code

    pdev_ctx = platform_get_drvdata(pdev);
    kfree(pdev_ctx);

    GFX_NOTI("gfx dev remove\n");

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
    // void, do nothing
#else
    return RET_OK;
#endif
}

/**
 *
 * module release function. this function will be called in rmmod module.
 *
 * @param   struct device *dev
 * @return  int 0 : OK , -1 : NOT OK
 *
 */
static void  GFX_release(struct device* dev)
{
    GFX_NOTI("gfx dev release\n");
}


/*
 *  module platform driver structure
 */
static struct dev_pm_ops gfx_pm_ops =
{
    .freeze     = GFX_freeze,         // SNAPSHOT suspend
    .thaw       = GFX_thaw,           // SNAPSHOT resume right after making
    .restore    = GFX_restore,        // SNAPSHOT boot

    .suspend    = GFX_suspend,        // IBOOT suspend
    .resume     = GFX_resume,         // IBOOT boot(resume)

    .runtime_suspend = GFX_runtime_suspend,
    .runtime_resume = GFX_runtime_resume,
};

static struct platform_driver platform_driver =
{
    .probe  = GFX_probe,
    .remove = GFX_remove,
    .driver =
    {
        .name   = GFX_MODULE,
        .pm     = &gfx_pm_ops
    },
};

static struct platform_device platform_device =
{
    .name = GFX_MODULE,
    .id = 0,
    .id = -1,
    .dev = {
        .release = GFX_release,
    },
};

/** initialize GFX deivce. this function is called from base_dev_cfg.c for the large single kernel driver
 *
 *
 */
int     GFX_Init(void)
{
    int         i;
    int         err;
    dev_t       dev;

    /* Get the handle of debug output for gfx device.
     *
     * Most module should open debug handle before the real initialization of module.
     * As you know, debug_util offers 4 independent debug outputs for your device driver.
     * So if you want to use all the debug outputs, you should initialize each debug output
     * using OS_DEBUG_EnableModuleByIndex() function.
     */
    g_gfx_trace_depth   = 0;
    g_gfx_debug_fd      = DBG_OPEN(GFX_MODULE);

    if (g_gfx_debug_fd < 0)
    {
        printk("[GFX] can't get debug handle\n");
    }
    else
    {
        OS_DEBUG_EnableModule(g_gfx_debug_fd);
        OS_DEBUG_EnableModuleByIndex(g_gfx_debug_fd, LX_LOGM_LEVEL_ERROR, DBG_COLOR_RED);        // error
        OS_DEBUG_EnableModuleByIndex(g_gfx_debug_fd, LX_LOGM_LEVEL_WARNING, DBG_COLOR_YELLOW);       // warn

        OS_DEBUG_EnableModuleByIndex(g_gfx_debug_fd, 10, DBG_COLOR_YELLOW);
    }

    /* register linux platform driver */
    GFX_CHECK_ERROR(platform_driver_register(&platform_driver) < 0, return RET_ERROR, "gfx platform drv reg fail\n");
    GFX_CHECK_ERROR(RET_OK != platform_device_register(&platform_device), return RET_ERROR, "gfx platform dev reg fail\n");

    /* enable PM runtime */
    pm_runtime_set_active(&platform_device.dev);
    pm_runtime_enable(&platform_device.dev);
    /* set control mode to "on" not "auto" */
    pm_runtime_forbid(&platform_device.dev);

    /* register N charactor device */
    g_gfx_device = (GFX_DEVICE_T*)OS_Malloc(sizeof(GFX_DEVICE_T) * GFX_MAX_DEVICE);
    GFX_CHECK_ERROR(NULL == g_gfx_device, return -ENOMEM, "out of memory. can't alloc %lld bytes\n",
                    (u64)(sizeof(GFX_DEVICE_T) * GFX_MAX_DEVICE));
    memset(g_gfx_device, 0x0, sizeof(GFX_DEVICE_T)* GFX_MAX_DEVICE);

    if (g_gfx_major)
    {
        dev = MKDEV(g_gfx_major, g_gfx_minor);
        err = register_chrdev_region(dev, GFX_MAX_DEVICE, GFX_MODULE);
    }
    else
    {
        err = alloc_chrdev_region(&dev, g_gfx_minor, GFX_MAX_DEVICE, GFX_MODULE);
        g_gfx_major = MAJOR(dev);
    }

    GFX_CHECK_ERROR(err < 0, return RET_ERROR, "gfx dev reg fail\n");

    /* TODO : initialize your module not specific minor device */

    GFX_InitHW();               /* initialize H/W for GFX to be used from kdriver initialization */
    GFX_InitSurfaceMemory();    /* initialize dynamic surface memory */
    GFX_SetCommandDelay(0x0);   /* set default cmd delay. the value came from verification test */

    for (i = 0; i < GFX_MAX_DEVICE; i++)
    {
        /* initialize cdev structure with predefined variable */
        dev = MKDEV(g_gfx_major, g_gfx_minor + i);
        cdev_init(&(g_gfx_device[i].cdev), &g_gfx_fops);
        g_gfx_device[i].devno       = dev;
        g_gfx_device[i].cdev.owner  = THIS_MODULE;
        g_gfx_device[i].cdev.ops    = &g_gfx_fops;

        /* TODO: initialize minor device */

        /* END */
        GFX_CHECK_ERROR(RET_OK != cdev_add(&(g_gfx_device[i].cdev), dev, 1), return RET_ERROR, "can't add gfx device (%d.%d)\n",
                        MAJOR(dev), MINOR(dev));
        OS_CreateDeviceClass(g_gfx_device[i].devno, "%s%d", GFX_MODULE, i);
    }

    /* initialize proc system */
    GFX_PROC_Init();

    GFX_NOTI("gfx dev initialized\n");
    return RET_OK;
}

void GFX_Cleanup(void)
{
    int i;
    dev_t dev = MKDEV(g_gfx_major, g_gfx_minor);

    // added by SC Jung for quick booting
    platform_driver_unregister(&platform_driver);
    platform_device_unregister(&platform_device);

    /* cleanup proc system */
    GFX_PROC_Cleanup();

    /* remove all minor devicies and unregister current device */
    for (i = 0; i < GFX_MAX_DEVICE; i++)
    {
        /* TODO: cleanup each minor device */


        /* END */
        cdev_del(&(g_gfx_device[i].cdev));
    }

    /* TODO : cleanup your module not specific minor device */

    unregister_chrdev_region(dev, GFX_MAX_DEVICE);

    OS_Free(g_gfx_device);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  GFX PID reference counter management
//
///////////////////////////////////////////////////////////////////////////////////////////////////
static void* alloc_pid_ref_cnt(void)
{
    return vmalloc(sizeof(PID_REF_CNT_T));
}

static void free_pid_ref_cnt(PID_REF_CNT_T* obj)
{
    if (obj) vfree(obj);
}

static int GFX_IncPidRefCount(UINT32 pid)
{
    PID_REF_CNT_T* obj;
    int ref_cnt = -1;

    list_for_each_entry(obj, &gfx_pid_ref_list, list)
    {
        if (obj->pid == pid)
        {
            ref_cnt = ++obj->ref_cnt; goto func_exit;
        }
    }

    obj = (PID_REF_CNT_T*)alloc_pid_ref_cnt();
    GFX_CHECK_ERROR(!obj, goto func_exit, "can't alloc %d bytes\n", (int)sizeof(PID_REF_CNT_T));

    obj->pid = pid;
    obj->ref_cnt = 1;
    get_task_comm(obj->psname, current);

    ref_cnt = obj->ref_cnt;

    list_add_tail(&obj->list, &gfx_pid_ref_list);

func_exit:
    GFX_NOTI("gfx ref_cnt(+) pid=%05d, cnt=%d\n", pid, ref_cnt);
    return ref_cnt;
}

static int GFX_DecPidRefCount(UINT32 pid)
{
    PID_REF_CNT_T* obj;
    int ref_cnt = -1;
    int found = 0;

    list_for_each_entry(obj, &gfx_pid_ref_list, list)
    {
        if (obj->pid == pid)
        {
            found = 1;
            ref_cnt = --(obj->ref_cnt);
            break;
        }
    }

    GFX_CHECK_ERROR(!found, /* do nothing */, "invalid pid %d\n", pid);

    if (found && obj->ref_cnt <= 0)
    {
        list_del(&obj->list);
        free_pid_ref_cnt(obj);
    }

    GFX_NOTI("gfx ref_cnt(-) pid=%05d, cnt=%d\n", pid, ref_cnt);
    return ref_cnt;
}

void GFX_ReportPIDRefList(struct seq_file* m)
{
    PID_REF_CNT_T* obj;

    list_for_each_entry(obj, &gfx_pid_ref_list, list)
    {
        seq_printf(m, "%05d(%s) %d\n", obj->pid, obj->psname, obj->ref_cnt);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  GFX PID reference counter management
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void GFX_ExecuteUserCommand(char* command)
{
    char* tok, *sav_tok;
    char delim[] = " ,:=\t\n";

    struct device* dev = &platform_device.dev;

#define SURFACE_PIDREF_DETATCH_CMD  "surface.pidref.detatch"

    tok = simple_strtok(command, delim, &sav_tok);

    while (tok)
    {
        if (!strncasecmp(command, SURFACE_PIDREF_DETATCH_CMD, strlen(SURFACE_PIDREF_DETATCH_CMD)))
        {
            UINT32 surface_fd;
            tok = simple_strtok(NULL, delim, &sav_tok);

            if (!tok) break;

            surface_fd = simple_strtoul(tok, NULL, 16);

            GFX_LockDevice();
            GFX_DetatchProcessSurface(surface_fd);
            GFX_UnlockDevice();
        }
        else if (!strncasecmp(command, "pm_runtime_get", strlen("pm_runtime_get")))
        {
            GFX_PM_DEBUG("+ test get_sync\n");
            pm_runtime_get_sync(dev);
        }
        else if (!strncasecmp(command, "pm_runtime_put", strlen("pm_runtime_put")))
        {
            GFX_PM_DEBUG("+ test put_sync\n");
            pm_runtime_put_sync(dev);
        }
        else if (!strncasecmp(command, "pm_runtime_set_active", strlen("pm_runtime_set_active")))
        {
            GFX_PM_DEBUG("+ test set_actvie\n");
            pm_runtime_set_active(dev);
        }

        tok = simple_strtok(NULL, delim, &sav_tok);
    }
}

void GFX_ReportStatus(struct seq_file* m)
{
    extern LX_GFX_REG_CFG_T* gpGfxRegCfg;

    GFX_CMD_QUEUE_CTRL_T status;
    GFX_GetComQueueStatus(&status);

    seq_printf(m, "chip.chip_name: %s\n", gpGfxRegCfg->chip_name);
    seq_printf(m, "chip.reg_base_addr: 0x%08x\n", gpGfxRegCfg->reg_base_addr);
    seq_printf(m, "chip.irq_num: %d\n", gpGfxRegCfg->irq_num);
    seq_printf(m, "\n");
    seq_printf(m, "chip.clk: %s\n", (GFX_ClkCheck()) ? "on" : "off");
    seq_printf(m, "\n");
    seq_printf(m, "status.usLine: 0x%x\n", status.usLine);
    seq_printf(m, "status.bStatus: 0x%x\n", status.bStatus);
    seq_printf(m, "status.usRemainSpace: 0x%x\n", status.usRemainSpace);
    seq_printf(m, "status.bFull: 0x%x\n", status.bFull);
    seq_printf(m, "status.usRemainParam: 0x%x\n", status.usRemainParam);
    seq_printf(m, "status.bBatchStatus: 0x%x\n", status.bBatchStatus);
}

void GFX_ReportPMStatus(struct seq_file* m)
{
    struct device* dev = &platform_device.dev;
    GFX_PDEV_CTX_T* pdev_ctx = platform_get_drvdata(&platform_device);

    seq_printf(m, "pm_runtime.status: %s\n", (pdev_ctx->is_runtime_active) ? "active" : "suspend");
    seq_printf(m, "pm_runtime.usage_count: %d\n", atomic_read(&dev->power.usage_count));
    seq_printf(m, "dev_open_count: %d\n", pdev_ctx->dev_open_count);

    GFX_ReportPIDRefList(m);
}

void GFX_ExecutePMTest(char* command)
{
    int i;
    GFX_PDEV_CTX_T* pdev_ctx = platform_get_drvdata(&platform_device);

    if (!strncasecmp(command, "runtime_suspend", strlen("runtime_suspend")))
    {
        int open_count = pdev_ctx->dev_open_count;
        struct device* dev = &platform_device.dev;
        int old_usage_count = atomic_read(&dev->power.usage_count);

        GFX_PM_DEBUG("+ test put_sync (%d times)\n", open_count);

        for (i = 0; i < open_count; i++)
        {
            pm_runtime_put_sync(dev);
        }

        GFX_PM_DEBUG("+ usage_count = %d -> %d\n", old_usage_count, atomic_read(&dev->power.usage_count));
    }
    else if (!strncasecmp(command, "runtime_resume", strlen("runtime_resume")))
    {
        int open_count = pdev_ctx->dev_open_count;
        struct device* dev = &platform_device.dev;
        int old_usage_count = atomic_read(&dev->power.usage_count);

        GFX_PM_DEBUG("+ test gut_sync (%d times)\n", open_count);

        for (i = 0; i < open_count; i++)
        {
            pm_runtime_get_sync(dev);
        }

        GFX_PM_DEBUG("+ usage_count = %d -> %d\n", old_usage_count, atomic_read(&dev->power.usage_count));
    }
    else
    {
        // add addtional command
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * open handler for gfx device
 *
 */
static int GFX_Open(struct inode* inode, struct file* filp)
{
    GFX_FILE_CTX_T* dev_ctx;
    int             major, minor;
    struct cdev*    cdev;
    GFX_DEVICE_T*   my_dev;
    GFX_PDEV_CTX_T* pdev_ctx = platform_get_drvdata(&platform_device);

    major   = imajor(inode);
    minor   = iminor(inode);
    cdev    = inode->i_cdev;
    my_dev  = container_of(cdev, GFX_DEVICE_T, cdev);

    GFX_PM_DEBUG("opening device. pid=%05d, tid=%05d\n", (UINT32)current->tgid, (UINT32)current->pid);

    /* TODO : add your device specific code */
    if (pdev_ctx->dev_open_count == 0)
    {
        /* do nothing */
    }

    pdev_ctx->dev_open_count++;

    pm_runtime_get_sync(&platform_device.dev);

    /* allocate device context */
    dev_ctx = kcalloc(1, sizeof(GFX_FILE_CTX_T), GFP_KERNEL);
    GFX_CHECK_ERROR(NULL == dev_ctx, /* nop */, "out of memory\n");
    dev_ctx->cached_mmap    = FALSE;
    filp->private_data      = dev_ctx;

    GFX_LockDevice();
    GFX_IncPidRefCount((UINT32)current->tgid);
    GFX_UnlockDevice();

    GFX_PRINT("gfx device opened (%d:%d)\n", major, minor);

    if (RET_OK == GFX_CheckRuntimeReportPermission())
    {
        report_runtime_status("info", pdev_ctx->dev_open_count, "open", "ok");
    }

    return RET_OK;
}

/**
 * release handler for gfx device
 *
 */
static int GFX_Close(struct inode* inode, struct file* file)
{
    int                 major, minor;
    GFX_FILE_CTX_T*     file_ctx;
    GFX_DEVICE_T*       my_dev;
    struct cdev*        cdev;
    GFX_PDEV_CTX_T*     pdev_ctx = platform_get_drvdata(&platform_device);

    GFX_PM_DEBUG("closing device. pid=%05d, tid=%05d\n", (UINT32)current->tgid, (UINT32)current->pid);

    major   = imajor(inode);
    minor   = iminor(inode);
    cdev    = inode->i_cdev;
    my_dev  = container_of(cdev, GFX_DEVICE_T, cdev);
    file_ctx = (GFX_FILE_CTX_T*)file->private_data;

    if (pdev_ctx->dev_open_count > 0)
    {
        pdev_ctx->dev_open_count--;
    }

    /* TODO : add your device specific code */
    if (file_ctx)
    {
        kfree(file_ctx);
    }

    /* END */

    GFX_LockDevice();

    if (0 >= GFX_DecPidRefCount((UINT32)current->tgid))
    {
        GFX_FreeProcessSurface((UINT32)current->tgid);
    }

    GFX_UnlockDevice();

    pm_runtime_put_sync(&platform_device.dev);

    /* some debug */
    GFX_PRINT("gfx device closed (%d:%d)\n", major, minor);

    if (RET_OK == GFX_CheckRuntimeReportPermission())
    {
        report_runtime_status("info", pdev_ctx->dev_open_count, "close", "ok");
    }

    return RET_OK;
}

/**
 * memory mapping to virtual region
 *
 */
static int GFX_mmap(struct file* file, struct vm_area_struct* vma)
{
    int ret;
    GFX_PRINT("%s : BEGIN\n", __F__);
    ret = GFX_SurfaceMmap(file, vma);
    GFX_PRINT("%s : END\n", __F__);

    return ret;
}

/**
 * ioctl handler for gfx device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)) || !defined(SUPPORT_GFX_UNLOCKED_IOCTL)
static int GFX_Ioctl(struct inode* inode, struct file* filp, UINT32 cmd, ULONG arg)
#else
static long GFX_Ioctl(struct file* filp, UINT32 cmd, ULONG arg)
#endif
{
    int ret = RET_ERROR;
    int err = 0;

    GFX_FILE_CTX_T* file_ctx;
    GFX_PDEV_CTX_T* pdev_ctx;

    /*
     * get current gfx device object
     */
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)) || !defined(SUPPORT_GFX_UNLOCKED_IOCTL)
    struct cdev* cdev;
    cdev    = inode->i_cdev;
    file_ctx = container_of(cdev, GFX_FILE_CTX_T, cdev);
#else
    file_ctx = (GFX_FILE_CTX_T*)filp->private_data;
#endif
    pdev_ctx = platform_get_drvdata(&platform_device);

    GFX_TRACE_BEGIN();

    /*
     * check if IOCTL command is valid or not.
     * - if magic value doesn't match, return error (-ENOTTY)
     * - if command is out of range, return error (-ENOTTY)
     *
     * note) -ENOTTY means "Inappropriate ioctl for device.
     */
    if (_IOC_TYPE(cmd) != GFX_IOC_MAGIC)
    {
        GFX_WARN("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd));
        GFX_TRACE_END();
        return -ENOTTY;
    }

    if (_IOC_NR(cmd) > GFX_IOC_MAXNR)
    {
        GFX_WARN("out of ioctl command. cmd_idx=%d\n", _IOC_NR(cmd));
        GFX_TRACE_END();
        return -ENOTTY;
    }

    /* TODO : add some check routine for your device */

    /*
     * check if user memory is valid or not.
     * if memory can't be accessed from kernel, return error (-EFAULT)
     */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)

    if (_IOC_DIR(cmd) & (_IOC_READ | _IOC_WRITE))
        err = !access_ok((void __user*)arg, _IOC_SIZE(cmd));

#else

    if (_IOC_DIR(cmd) & _IOC_READ)
        err = !access_ok(VERIFY_WRITE, (void __user*)arg, _IOC_SIZE(cmd));
    else if (_IOC_DIR(cmd) & _IOC_WRITE)
        err =  !access_ok(VERIFY_READ, (void __user*)arg, _IOC_SIZE(cmd));

#endif

    if (err)
    {
        GFX_WARN("memory access error. cmd_idx=%d, rw=%c%c, memptr=%p\n",
                 _IOC_NR(cmd),
                 (_IOC_DIR(cmd) & _IOC_READ) ? 'r' : '-',
                 (_IOC_DIR(cmd) & _IOC_WRITE) ? 'w' : '-',
                 (void*)arg);
        GFX_TRACE_END();
        return -EFAULT;
    }

    GFX_PRINT("%s : IOC 0x%08x (%s:%d)\n", __F__, cmd, GFX_IOC2STR(cmd), _IOC_NR(cmd));

    if (g_gfx_safe_runtime_pm)
    {
        if (!pdev_ctx->is_runtime_active)
        {
            GFX_WARN("ioctl rejected. pm.runtime.status: suspended, dev.open_count: %d\n", pdev_ctx->dev_open_count);
            GFX_TRACE_END();
            return RET_ERROR;
        }
    }

    switch (cmd)
    {
        case GFX_IO_RESET:
        {
            GFX_PRINT("reset ok\n");

            ret = RET_OK; /* all work done */
        }
        break;

        case GFX_IOR_CHIP_REV_INFO:
        {
            LX_CHIP_REV_INFO_T  rev_info;

            rev_info.version = 0x100;
            rev_info.date[0] = 15;  /* 2015/01/01 */
            rev_info.date[1] = 1;
            rev_info.date[2] = 1;

            err = copy_to_user((void __user*)arg, &rev_info, sizeof(CHIP_REV_INFO_T));
            GFX_CHECK_ERROR(err > 0, goto func_exit, "copy error\n");

            ret = RET_OK; /* all work done */
        }
        break;

        case GFX_IOR_GET_CFG:
        {
            err = copy_to_user((void __user*)arg, (void*)&g_gfx_cfg, sizeof(LX_GFX_CFG_T));
            GFX_CHECK_ERROR(err > 0, goto func_exit, "copy error\n");

            ret = RET_OK; /* all work done */
        }
        break;

        case GFX_IOW_DEV_FILE_CTRL:
        {
            LX_GFX_DEV_FILE_CTRL_T  dev_ctrl;

            err = copy_from_user((void*)&dev_ctrl, (void __user*)arg, sizeof(LX_GFX_DEV_FILE_CTRL_T));
            GFX_CHECK_ERROR(err > 0, goto func_exit, "copy error\n");

            file_ctx->cached_mmap = (dev_ctrl.opmask & LX_GFX_DEV_CTRL_MMAP_CACHED) ? TRUE : FALSE;
            ret = RET_OK; /* all work done */
        }
        break;

        case GFX_IOW_SURFACE_CACHE_CTRL:
        {
            LX_GFX_SURFACE_CACHE_CTRL_T cache_ctrl;

            err = copy_from_user((void*)&cache_ctrl, (void __user*)arg, sizeof(LX_GFX_SURFACE_CACHE_CTRL_T));
            GFX_CHECK_ERROR(err > 0, goto func_exit, "copy error\n");

            GFX_CHECK_ERROR(!file_ctx->cached_mmap, goto func_exit, "surface cache op not enabled\n");

            switch (cache_ctrl.op)
            {
                case LX_GFX_SURFACE_CACHE_OP_INVAL:
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0)
                {
                    unsigned long start, pstart, size;

                    start = (unsigned long)cache_ctrl.virt_addr;
                    pstart = (unsigned long)cache_ctrl.phys_addr;
                    size = (unsigned long)cache_ctrl.length;

                    dcache_inval_poc(start, start + size);

#ifndef __aarch64__
                    outer_inv_range(pstart, pstart + size);
#endif
                }

#else // LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0)

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,4,3)
                __dma_map_area((void*)((uintptr_t)cache_ctrl.virt_addr), cache_ctrl.length, DMA_FROM_DEVICE);//v7_dma_inv_range
#else
                dmac_map_area((void*)cache_ctrl.virt_addr, cache_ctrl.length, DMA_FROM_DEVICE);//v7_dma_inv_range
#endif
#ifndef __aarch64__
                outer_inv_range((phys_addr_t)cache_ctrl.phys_addr, (phys_addr_t)cache_ctrl.phys_addr + cache_ctrl.length);
#endif

#endif // LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0)

                break;

                case LX_GFX_SURFACE_CACHE_OP_CLEAN:
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0)
                {
                    unsigned long start, pstart, size;
                    start = (unsigned long)cache_ctrl.virt_addr;
                    pstart = (unsigned long)cache_ctrl.phys_addr;
                    size = (unsigned long)cache_ctrl.length;

                    dcache_clean_poc(start, start + size);
#ifndef __aarch64__
                    outer_clean_range(pstart, pstart + size);
#endif
                }

#else // LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0)

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,4,3)
                __dma_map_area((void*)((uintptr_t)cache_ctrl.virt_addr), cache_ctrl.length, DMA_TO_DEVICE);//v7_dma_clean_range
#else
                dmac_map_area((void*)cache_ctrl.virt_addr, cache_ctrl.length, DMA_TO_DEVICE);//v7_dma_clean_range
#endif
#ifndef __aarch64__
                outer_clean_range((phys_addr_t)cache_ctrl.phys_addr, (phys_addr_t)cache_ctrl.phys_addr + cache_ctrl.length);
#endif

#endif // LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0)
                break;

                default:
                    GFX_ERROR("invalid cache op 0x%x\n", cache_ctrl.op);
            }

            ret = RET_OK; /* all work done */
        }
        break;

        case GFX_IORW_ALLOC_SURFACE :
        {
            LX_GFX_SURFACE_SETTING_PARAM_T param;
            err = copy_from_user((void*)&param, (void __user*)arg, sizeof(LX_GFX_SURFACE_SETTING_PARAM_T));

            GFX_LockDevice();
            err = GFX_AllocSurface(&param);
            GFX_UnlockDevice();

            GFX_CHECK_ERROR(RET_OK != err, goto func_exit, "GFX_AllocSurface failed\n");

            err = copy_to_user((void __user*)arg, (void*)&param, sizeof(LX_GFX_SURFACE_SETTING_PARAM_T));
            GFX_CHECK_ERROR(err > 0, goto func_exit, "copy error\n");

            ret = RET_OK; /* all work done */
        }
        break;

        case GFX_IOW_FREE_SURFACE :
        {
            UINT32  surface_fd;

            err = copy_from_user((void*)&surface_fd, (void __user*)arg, sizeof(UINT32));
            GFX_CHECK_ERROR(err > 0, goto func_exit, "copy error\n");

            GFX_LockDevice();
            err = GFX_FreeSurface(surface_fd);
            GFX_UnlockDevice();
            GFX_CHECK_ERROR(RET_OK != err, goto func_exit, "GFX_FreeSurface failed\n");

            ret = RET_OK; /* all work done */
        }
        break;

        case GFX_IORW_QUERY_SURFACE_SETTING:
        {
            LX_GFX_SURFACE_QUERY_PARAM_T param;

            err = copy_from_user((void*)&param, (void __user*)arg, sizeof(LX_GFX_SURFACE_QUERY_PARAM_T));
            GFX_CHECK_ERROR(err > 0, goto func_exit, "copy error\n");

            GFX_LockDevice();
            err = GFX_QuerySurface(&param);
            GFX_UnlockDevice();
            GFX_CHECK_CODE(RET_OK != err, goto func_exit, "GFX_QuerySurface failed\n");

            err = copy_to_user((void __user*)arg, (void*)&param, sizeof(LX_GFX_SURFACE_QUERY_PARAM_T));
            GFX_CHECK_ERROR(err > 0, goto func_exit, "copy error\n");

            ret = RET_OK; /* all work done */
        }
        break;

        case GFX_IOW_SET_SURFACE_PALETTE :
        {
            LX_GFX_SURFACE_PALETTE_PARAM_T      param;
            LX_GFX_SURFACE_PALETTE_PARAM_T*     input_param;
            UINT32*                             palette_data;

            LX_GFX_SURFACE_PALETTE_PARAM_T      arg_buf;

            err = copy_from_user((void*)&arg_buf, (void __user*)arg, sizeof(LX_GFX_SURFACE_PALETTE_PARAM_T));
            GFX_CHECK_ERROR(err > 0, goto func_exit, "copy error, from user\n");

            input_param = &arg_buf;

            /*  raxis.lim (2010/06/05)
             *  --  palette data is passed as pointer, so we should copy it from user space
             */
            param.palette.palette_data  = (UINT32*)OS_Malloc(sizeof(UINT32) * 256);
            GFX_CHECK_ERROR(NULL == param.palette.palette_data, goto func_exit, "palette alloc error\n");

            param.surface_fd = input_param->surface_fd;

            param.palette.palette_num = input_param->palette.palette_num;
            GFX_CHECK_ERROR(param.palette.palette_num > 256, goto func_exit,
                            "invalid palette_num=%d\n", param.palette.palette_num);

            /* get user palette pointer */
            palette_data = input_param->palette.palette_data;

            err = copy_from_user((void*)param.palette.palette_data, (void __user*)palette_data,
                                 sizeof(UINT32) * param.palette.palette_num);

            GFX_CHECK_ERROR(err > 0, OS_Free(param.palette.palette_data); goto func_exit, "copy error\n");

            GFX_LockDevice();
            GFX_SetSurfacePalette(param.surface_fd, param.palette.palette_num, param.palette.palette_data);
            GFX_UnlockDevice();

            OS_Free(param.palette.palette_data);
            ret = RET_OK; /* all work done */
        }
        break;

        case GFX_IOR_GET_SURFACE_PALETTE :
        {
            LX_GFX_SURFACE_PALETTE_PARAM_T      param;
            LX_GFX_SURFACE_PALETTE_PARAM_T*     input_param;
            UINT32*                             palette_data;

            LX_GFX_SURFACE_PALETTE_PARAM_T      arg_buf;

            err = copy_from_user((void*)&arg_buf, (void __user*)arg, sizeof(LX_GFX_SURFACE_PALETTE_PARAM_T));
            GFX_CHECK_ERROR(err > 0, goto func_exit, "copy error, from user\n");

            input_param = &arg_buf;

            param.palette.palette_data  = (UINT32*)OS_Malloc(sizeof(UINT32) * 256);
            param.palette.palette_num   = 256;
            GFX_CHECK_ERROR(NULL == param.palette.palette_data, goto func_exit, "palette alloc error\n");

            param.surface_fd = input_param->surface_fd;

            param.palette.palette_num = input_param->palette.palette_num;

            palette_data = input_param->palette.palette_data;

            GFX_LockDevice();
            GFX_GetSurfacePalette(param.surface_fd, param.palette.palette_num, param.palette.palette_data);
            GFX_UnlockDevice();

            err = copy_to_user((void __user*)palette_data, (void*)param.palette.palette_data,
                               sizeof(UINT32) * param.palette.palette_num);

            GFX_CHECK_ERROR(err > 0, OS_Free(param.palette.palette_data); goto func_exit, "copy error\n");

            OS_Free(param.palette.palette_data);
            ret = RET_OK; /* all work done */
        }
        break;

        case GFX_IOW_BLEND :
        case GFX_IOW_MANUAL_BLEND :
        {
            int retry;
            LX_GFX_MANUAL_BLEND_CTRL_PARAM_T manual_blend;

            memset(&manual_blend, 0x0, sizeof(LX_GFX_MANUAL_BLEND_CTRL_PARAM_T));
            err = copy_from_user((void*)&manual_blend, (void __user*)arg, sizeof(LX_GFX_MANUAL_BLEND_CTRL_PARAM_T));
            GFX_CHECK_ERROR(err > 0, goto func_exit, "copy error\n");

            GFX_LockDevice();

            for (retry = g_gfx_cfg.sync_fail_retry_count ; retry > 0 ; retry--)
            {
                err = GFX_RunBlendOp(&manual_blend, g_gfx_cfg.surface_blit_cmd_delay);

                /* when batch mode is auto, driver automatically flush queue (start batch run) */
                if (GFX_GetRunCommand() == LX_GFX_BATCH_RUN_MODE_AUTO)
                {
                    GFX_RunFlushCommand();
                }

                /* raxis.lim (2011/05/21)
                 * since there is some bugs in L9A0 scaler read/write timing problem, I should add s/w workaround
                 * to do "soft reset" for GFX block every scaler request.
                 * [NOTE] check if L9B0 fixes this bug
                 *
                 * raxis.lim (2012/12/27)
                 * GFX soft reset is moved into GFX_WaitSyncCommand.
                 * GFX soft reset will be done after every GFX operation.
                 */
                if (GFX_GetGraphicSyncMode() == LX_GFX_GRAPHIC_SYNC_MODE_AUTO)
                {
                    UINT32  timeout = GFX_CalcSyncTimeout(&manual_blend, g_gfx_cfg.sync_wait_timeout);
                    GFX_DEBUG("gfx_sync_wait_timeout=%d\n", timeout);
                    err = GFX_WaitSyncCommand(timeout);

#if 0

                    if (GFX_WADesc(scaler_read_buf_stuck) && manual_blend.scaler.mode)
                    {
                        GFX_SwResetCommand();
                    }

#endif
                }

                /* if GFX operation failed, retry it */
                if (err == RET_OK) break;
            }

            GFX_UnlockDevice();

            ret = RET_OK; /* all work done */
        }
        break;

        case GFX_IOW_SET_CSC_CONV_TBL:
        {
            LX_GFX_CSC_TBL_T csc_conv;

            err = copy_from_user((void*)&csc_conv, (void __user*)arg, sizeof(LX_GFX_CSC_TBL_T));
            GFX_CHECK_ERROR(err > 0, goto func_exit, "copy error\n");

            err = GFX_SetColorSpace(csc_conv.coef);
            GFX_CHECK_CODE(err != RET_OK, goto func_exit, "GFX_SetColorSpace error\n");

            ret = RET_OK; /* all work done */
        }
        break;

        case GFX_IOR_GET_CMD_DELAY :
        {
            UINT32  cmd_delay;

            GFX_GetCommandDelay(&cmd_delay);

            err = copy_to_user((void __user*)arg, (void*)&cmd_delay, sizeof(UINT32));
            GFX_CHECK_CODE(err > 0, goto func_exit, "copy error\n");

            ret = RET_OK; /* all work done */
        }
        break;

        case GFX_IOW_SET_CMD_DELAY :
        {
            UINT32  cmd_delay;

            err = copy_from_user((void*)&cmd_delay, (void __user*)arg, sizeof(UINT32));
            GFX_CHECK_ERROR(err > 0, goto func_exit, "copy error\n");

            GFX_SetCommandDelay(cmd_delay);

            ret = RET_OK; /* all work done */
        }
        break;

        case GFX_IORW_GET_SURFACE_MEM_INFO:
        {
            LX_GFX_SURFACE_MEM_INFO_PARAM_T mem_info;

            err = copy_from_user((void*)&mem_info, (void __user*)arg, sizeof(LX_GFX_SURFACE_MEM_INFO_PARAM_T));
            GFX_CHECK_ERROR(err > 0, goto func_exit, "copy error\n");

            GFX_LockDevice();
            err = GFX_GetSurfaceMemory(&mem_info);
            GFX_UnlockDevice();
            GFX_CHECK_CODE(err != RET_OK, goto func_exit, "GFX_GetSurfaceMemory error\n");

            err = copy_to_user((void __user*)arg, (void*)&mem_info, sizeof(LX_GFX_SURFACE_MEM_INFO_PARAM_T));
            GFX_CHECK_ERROR(err > 0, goto func_exit, "copy error\n");

            ret = RET_OK; /* all work done */
        }
        break;

        case GFX_IOW_SET_BATCH_RUN_MODE:
        {
            LX_GFX_BATCH_RUN_MODE_T run_mode;

            err = copy_from_user((void*)&run_mode, (void __user*)arg, sizeof(LX_GFX_BATCH_RUN_MODE_T));
            GFX_CHECK_ERROR(err > 0, goto func_exit, "copy error\n");

            err = GFX_SetRunCommand(&run_mode);
            GFX_CHECK_CODE(err != RET_OK, goto func_exit, "GFX_SetRunCommand error\n");

            ret = RET_OK; /* all work done */
        }
        break;

        case GFX_IOR_GET_BATCH_RUN_MODE:
        {
            LX_GFX_BATCH_RUN_MODE_T run_mode;

            run_mode = GFX_GetRunCommand();

            err = copy_to_user((void __user*)arg, (void*)&run_mode, sizeof(LX_GFX_BATCH_RUN_MODE_T));
            GFX_CHECK_ERROR(err > 0, goto func_exit, "copy error\n");

            ret = RET_OK; /* all work done */
        }
        break;

        case GFX_IO_START_BATCH_RUN:
        {
            err = GFX_RunFlushCommand();
            GFX_CHECK_CODE(err != RET_OK, goto func_exit, "GFX_RunFlushCommand error\n");

            ret = RET_OK; /* all work done */
        }
        break;

        case GFX_IOW_SET_GRAPHIC_SYNC_MODE:
        {
            LX_GFX_GRAPHIC_SYNC_MODE_T  mode;

            err = copy_from_user((void*)&mode, (void __user*)arg, sizeof(LX_GFX_GRAPHIC_SYNC_MODE_T));
            GFX_CHECK_ERROR(err > 0, goto func_exit, "copy error\n");

            err = GFX_SetGraphicSyncMode(mode);
            GFX_CHECK_CODE(err != RET_OK, goto func_exit, "GFX_SetGraphicSyncMode error\n");

            ret = RET_OK; /* all work done */
        }
        break;

        case GFX_IOW_WAIT_FOR_SYNC:
        {
            UINT32  msec_tm;

            err = copy_from_user((void*)&msec_tm, (void __user*)arg, sizeof(UINT32));
            GFX_CHECK_CODE(err > 0, goto func_exit, "copy error\n");

            err = GFX_WaitSyncCommand(msec_tm);
            GFX_CHECK_CODE(err != RET_OK, goto func_exit, "GFX_WaitSyncCommand error\n");

            ret = RET_OK; /* all work done */
        }
        break;

        case GFX_IOR_GET_MEM_STAT:
        {
            LX_GFX_MEM_STAT_T   mem_stat;
            (void)GFX_GetSurfaceMemoryStat(&mem_stat);

            err = copy_to_user((void __user*)arg, (void*)&mem_stat, sizeof(LX_GFX_MEM_STAT_T));
            GFX_CHECK_ERROR(err > 0, goto func_exit, "copy error\n");

            ret = RET_OK; /* all work done */
        }
        break;

        default:
        {
            /* redundant check but it seems more readable */
            ret = -ENOTTY;
        }
    }

func_exit:
    GFX_PRINT("%s : IOC 0x%08x (%s:%d) -- ret %d\n", __F__, cmd, GFX_IOC2STR(cmd), _IOC_NR(cmd), ret);
    GFX_TRACE_END();

    return ret;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36)) && defined(SUPPORT_GFX_UNLOCKED_IOCTL)
#ifdef CONFIG_COMPAT
static long GFX_Compat_Ioctl(struct file* filp, UINT32 cmd, ULONG arg)
{
    long ret;

    switch (cmd)
    {
        case GFX_IORW_ALLOC_SURFACE:
        {
            LX_GFX_SURFACE_SETTING_PARAM_T arg_buf;
            ret = copy_from_user(&arg_buf, (void __user*)arg,
                                 sizeof(LX_GFX_SURFACE_SETTING_PARAM_T));

            if (ret)
            {
                return -EINVAL;
            }

            arg_buf.surface_setting.mmap_ptr =
                (void*)(uintptr_t)arg_buf.surface_setting.compat_mmap_ptr;

            ret = copy_to_user((void __user*)arg, &arg_buf,
                               sizeof(LX_GFX_SURFACE_SETTING_PARAM_T));

            if (ret)
            {
                return -EINVAL;
            }

            break;
        }

        case GFX_IOW_SET_SURFACE_PALETTE:
        case GFX_IOR_GET_SURFACE_PALETTE:
        {
            LX_GFX_SURFACE_PALETTE_PARAM_T arg_buf;

            ret = copy_from_user(&arg_buf, (void __user*)arg,
                                 sizeof(LX_GFX_SURFACE_PALETTE_PARAM_T));

            if (ret)
            {
                return -EINVAL;
            }

            arg_buf.palette.palette_data =
                (UINT32*)(uintptr_t)arg_buf.palette.compat_palette_data;

            ret = copy_to_user((void __user*)arg, &arg_buf,
                               sizeof(LX_GFX_SURFACE_PALETTE_PARAM_T));

            if (ret)
            {
                return -EINVAL;
            }

            break;
        }

        default:
            break;
    }

    ret = GFX_Ioctl(filp, cmd, arg);

    return ret;
}
#endif
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv", GFX_Init);
#else
module_init(GFX_Init);
#endif
module_exit(GFX_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("GFX driver");
MODULE_LICENSE("GPL");
#endif

/** @} */

