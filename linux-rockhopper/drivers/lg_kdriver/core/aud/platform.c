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
 *  audio platform driver
 *
 *  author      Youngwoo Jin ( youngwoo.jin@lge.com )
 *  version     1.0
 *  date        2021.01.25
 *
 */

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/version.h>

#include "logm.h"
#include "hal/hal.h"
#include "dsp_control.h"
#include "platform.h"

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/
#define trace(fmt,args...)  logm_trace(aud_platform,fmt,##args)
#define debug(fmt,args...)  logm_debug(aud_platform,fmt,##args)
#define info(fmt,args...)   logm_info(aud_platform,fmt,##args)
#define noti(fmt,args...)   logm_noti(aud_platform,fmt,##args)
#define warn(fmt,args...)   logm_warning(aud_platform,fmt,##args)
#define error(fmt,args...)  logm_error(aud_platform,fmt,##args)

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
struct aud_drv_data
{
    bool is_suspended;
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
logm_define (aud_platform, log_level_noti);

/*------------------------------------------------------------------------------
    Static Function Prototypes Declarations
------------------------------------------------------------------------------*/
static int _suspend (struct platform_device *pdev);
static int _resume (struct platform_device *pdev);
static int aud_probe (struct platform_device *pdev);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void aud_remove (struct platform_device *pdev);
#else
static int aud_remove (struct platform_device *pdev);
#endif
static void aud_release (struct device *dev);
static int aud_prepare (struct device *dev);
static int aud_freeze (struct device *dev);
static int aud_freeze_late (struct device *dev);
static int aud_freeze_noirq (struct device *dev);
static int aud_thaw_noirq (struct device *dev);
static int aud_thaw_early (struct device *dev);
static int aud_thaw (struct device *dev);
static void aud_complete (struct device *dev);
static int aud_suspend (struct device *dev);
static int aud_suspend_late (struct device *dev);
static int aud_suspend_noirq (struct device *dev);
static int aud_resume_noirq (struct device *dev);
static int aud_resume_early (struct device *dev);
static int aud_resume (struct device *dev);
static int aud_poweroff (struct device *dev);
static int aud_restore_noirq (struct device *dev);
static int aud_restore_early (struct device *dev);
static int aud_restore (struct device *dev);
static int aud_poweroff_late (struct device *dev);
static int aud_poweroff_noirq (struct device *dev);
static int aud_runtime_suspend (struct device *dev);
static int aud_runtime_resume (struct device *dev);
static int aud_runtime_idle (struct device *dev);

/*------------------------------------------------------------------------------
    Static Variables
------------------------------------------------------------------------------*/
static struct dev_pm_ops pm_ops = {
    .prepare = aud_prepare,
    .complete = aud_complete,
    .suspend = aud_suspend,
    .resume = aud_resume,
    .freeze = aud_freeze,
    .thaw = aud_thaw,
    .poweroff = aud_poweroff,
    .restore = aud_restore,
    .suspend_late = aud_suspend_late,
    .resume_early = aud_resume_early,
    .freeze_late = aud_freeze_late,
    .thaw_early = aud_thaw_early,
    .poweroff_late = aud_poweroff_late,
    .restore_early = aud_restore_early,
    .suspend_noirq = aud_suspend_noirq,
    .resume_noirq = aud_resume_noirq,
    .freeze_noirq = aud_freeze_noirq,
    .thaw_noirq = aud_thaw_noirq,
    .poweroff_noirq = aud_poweroff_noirq,
    .restore_noirq = aud_restore_noirq,
    .runtime_suspend = aud_runtime_suspend,
    .runtime_resume = aud_runtime_resume,
    .runtime_idle = aud_runtime_idle,
};

static struct platform_driver aud_platform_driver = {
    .probe = aud_probe,
    .remove = aud_remove,
    .driver = {
            .name = "audio",
            .pm = &pm_ops,
        },
};

static struct platform_device aud_platform_device = {
    .name = "audio",
    .id = -1,
    .dev = {
            .release = aud_release,
        },
};

/*==============================================================================
    Implementation Group
==============================================================================*/
/**
 * suspending module.
 *
 * @param	struct platform_device *pdev pm_message_t state
 * @return	int 0 : OK , -1 : NOT OK
 */

static int _suspend (struct platform_device *pdev)
{
    struct aud_drv_data *drv_data = platform_get_drvdata (pdev);

    if (drv_data->is_suspended)
    {
        return -1;
    }

    drv_data->is_suspended = true;

    aud_dsp_halt ();

    printk ("%s\n", __func__);
    return 0;
}

/**
 * resuming module.
 *
 * @param	struct platform_device *
 * @return	int 0 : OK , -1 : NOT OK
 */
static int _resume (struct platform_device *pdev)
{
    struct aud_drv_data *drv_data = platform_get_drvdata (pdev);

    if (!drv_data->is_suspended)
    {
        return -1;
    }

    drv_data->is_suspended = false;

    _aud_dsp_reset ();

    printk ("%s\n", __func__);
    return 0;
}

/**
 * probing module.
 *
 * @param	struct platform_device *pdev
 * @return	int 0 : OK , -1 : NOT OK
 */
static int aud_probe (struct platform_device *pdev)
{
    struct aud_drv_data *drv_data;

    drv_data = (struct aud_drv_data *) kmalloc (sizeof (struct aud_drv_data), GFP_KERNEL);

    drv_data->is_suspended = false;
    platform_set_drvdata (pdev, drv_data);

    printk ("%s\n", __func__);
    return 0;
}

/**
 * module remove function. this function will be called in rmmod fbdev module.
 *
 * @param	struct platform_device
 * @return	int 0 : OK , -1 : NOT OK
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void aud_remove (struct platform_device *pdev)
#else
static int aud_remove (struct platform_device *pdev)
#endif
{
    struct aud_drv_data *drv_data = platform_get_drvdata (pdev);

    kfree ((void *) drv_data);

    printk ("%s\n", __func__);
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,5,0)
    return 0;
#endif
}

/**
 * module release function. this function will be called in rmmod module.
 *
 * @param	struct device *dev
 */
static void aud_release (struct device *dev)
{
    printk ("%s\n", __func__);
}

static int aud_prepare (struct device *dev)
{
    printk ("%s\n", __func__);
    return 0;
}

static int aud_freeze (struct device *dev)
{
    printk ("%s\n", __func__);
    return _suspend (to_platform_device (dev));
}

static int aud_freeze_late (struct device *dev)
{
    printk ("%s\n", __func__);
    return 0;
}

static int aud_freeze_noirq (struct device *dev)
{
    printk ("%s\n", __func__);
    return 0;
}

static int aud_thaw_noirq (struct device *dev)
{
    printk ("%s\n", __func__);
    return 0;
}

static int aud_thaw_early (struct device *dev)
{
    printk ("%s\n", __func__);
    return 0;
}

static int aud_thaw (struct device *dev)
{
    printk ("%s\n", __func__);
    return _resume (to_platform_device (dev));
}

static void aud_complete (struct device *dev)
{
    printk ("%s\n", __func__);
    return;
}

static int aud_suspend (struct device *dev)
{
    printk ("%s\n", __func__);
    return _suspend (to_platform_device (dev));
}

static int aud_suspend_late (struct device *dev)
{
    printk ("%s\n", __func__);
    return 0;
}

static int aud_suspend_noirq (struct device *dev)
{
    printk ("%s\n", __func__);
    return 0;
}

static int aud_resume_noirq (struct device *dev)
{
    printk ("%s\n", __func__);
    return 0;
}

static int aud_resume_early (struct device *dev)
{
    printk ("%s\n", __func__);
    return 0;
}

static int aud_resume (struct device *dev)
{
    printk ("%s\n", __func__);
    aud_hal_initHW ();
    return _resume (to_platform_device (dev));
}

static int aud_poweroff (struct device *dev)
{
    printk ("%s\n", __func__);
    return 0;
}

static int aud_restore_noirq (struct device *dev)
{
    printk ("%s\n", __func__);
    return 0;
}

static int aud_restore_early (struct device *dev)
{
    printk ("%s\n", __func__);
    return 0;
}

static int aud_restore (struct device *dev)
{
    printk ("%s\n", __func__);
    aud_hal_initHW ();
    return _resume (to_platform_device (dev));
}

static int aud_poweroff_late (struct device *dev)
{
    printk ("%s\n", __func__);
    return 0;
}

static int aud_poweroff_noirq (struct device *dev)
{
    printk ("%s\n", __func__);
    return 0;
}

static int aud_runtime_suspend (struct device *dev)
{
    printk ("%s\n", __func__);
    return 0;
}

static int aud_runtime_resume (struct device *dev)
{
    printk ("%s\n", __func__);
    return 0;
}

static int aud_runtime_idle (struct device *dev)
{
    printk ("%s\n", __func__);
    return 0;
}

int aud_platform_init (void)
{
    int ret;

    ret = platform_driver_register (&aud_platform_driver);
    if (ret < 0)
    {
        error ("platform driver register failed. %d\n", ret);
        return ret;
    }

    ret = platform_device_register (&aud_platform_device);
    if (ret < 0)
    {
        platform_driver_unregister (&aud_platform_driver);
        error ("platform device register failed. %d\n", ret);
    }

    //Enable async suspend and resume.
    device_enable_async_suspend (&aud_platform_device.dev);

    return 0;
}

void aud_platform_exit (void)
{
    platform_driver_unregister (&aud_platform_driver);
    platform_device_unregister (&aud_platform_device);
}
