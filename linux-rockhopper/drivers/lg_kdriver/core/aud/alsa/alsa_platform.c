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



/** @file alsa_platform.c
 *
 *  This is alsa platform driver.
 *
 *  @author	Won Chang Shin(wonchang.shin@lge.com)
 *  @version	0.1
 *  @date	2013.03.20
 *  @note	The functions for alsa platform driver.
 *
 *  @{
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/workqueue.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <sound/soc.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>

#include "os_util.h"
#include "base_device.h"
#include "debug_util.h"

#include "audio_kapi_decoder.h"
#include "audio_kapi_renderer.h"
#include "audio_kapi_capturer.h"

#include "alsa.h"
#include "alsa_platform.h"
#include "linux/alsa-ext/alsa-ext-broadcast.h"
#include "linux/alsa-ext/alsa-ext-renderer.h"

#include "alsa_decoder.h"

#include "log.h"

//define for audio ALSA Buffer size
#define ALSA_BUFFER_BYTES_MAX   (PAGE_SIZE * 4) //16384
#define ALSA_PERIOD_BYTES_MAX   (PAGE_SIZE)     // 4096

#define ALSA_PRINT_DURATION	    5   //seconds

#define MAX_COUNT_RECOVERY      3

#define ALSA_DEC_DEV_ID         8

#define SIZE_OF_AENC_DATA_T (sizeof (aenc_data_t))

#ifndef __devinit
# define __devinit
#endif
#ifndef __devexit
# define __devexit
#endif
#ifndef __devexit_p
# define __devexit_p
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int lg115x_pcm_open (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int lg115x_pcm_open (struct snd_pcm_substream *substream)
#endif
{
    int ret = RET_OK;

    info ("entered.\n");

    return ret;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int lg115x_pcm_close (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int lg115x_pcm_close (struct snd_pcm_substream *substream)
#endif
{
    int ret = RET_OK;

    info ("entered.\n");

    return ret;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int lg115x_pcm_lib_ioctl (struct snd_soc_component *component, struct snd_pcm_substream *substream, unsigned int cmd, void *arg)
#else
static int lg115x_pcm_lib_ioctl (struct snd_pcm_substream *substream, unsigned int cmd, void *arg)
#endif
{
    debug ("completed.(device:%d, cmd:%d)\n", substream->pcm->device, cmd);

    return RET_OK;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int lg115x_pcm_hw_params (struct snd_soc_component *component, struct snd_pcm_substream *substream,
    struct snd_pcm_hw_params *params)
#else
static int lg115x_pcm_hw_params (struct snd_pcm_substream *substream,
    struct snd_pcm_hw_params *params)
#endif
{
    int ret = RET_OK;

#if (LINUX_VERSION_CODE < KERNEL_VERSION(5, 5, 0))
    info ("completed.(device:%d, params:%d)\n", substream->pcm->device, params_format (params));
#endif
    return ret;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int lg115x_pcm_prepare (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int lg115x_pcm_prepare (struct snd_pcm_substream *substream)
#endif
{
    int ret = RET_OK;

    info ("entered.\n");

    return ret;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int lg115x_pcm_hw_free (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int lg115x_pcm_hw_free (struct snd_pcm_substream *substream)
#endif
{
    int ret = RET_OK;

    return ret;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int lg115x_pcm_trigger (struct snd_soc_component *component, struct snd_pcm_substream *substream, int cmd)
#else
static int lg115x_pcm_trigger (struct snd_pcm_substream *substream, int cmd)
#endif
{
    int ret = RET_OK;

    info ("entered.\n");

    return ret;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static snd_pcm_uframes_t lg115x_pcm_pointer (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static snd_pcm_uframes_t lg115x_pcm_pointer (struct snd_pcm_substream *substream)
#endif
{
    info ("entered.\n");

    return 0;
}

#if (LINUX_VERSION_CODE < KERNEL_VERSION(5, 5, 0))
static int lg115x_pcm_copy (struct snd_pcm_substream *substream,
    int channel, snd_pcm_uframes_t pos, void __user * buf, snd_pcm_uframes_t count)
{
    int ret = RET_OK;

    return ret;
}

static int lg115x_pcm_silence (struct snd_pcm_substream *substream, int channel,
    snd_pcm_uframes_t pos, snd_pcm_uframes_t count)
{
    int ret = RET_OK;


    return ret;
}
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int lg115x_pcm_mmap (struct snd_soc_component *component, struct snd_pcm_substream *substream, struct vm_area_struct *vma)
#else
static int lg115x_pcm_mmap (struct snd_pcm_substream *substream, struct vm_area_struct *vma)
#endif
{
    info ("completed.\n");

    return RET_OK;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int lg115x_pcm_new (struct snd_soc_component *component, struct snd_soc_pcm_runtime *rtd)
#else
static int lg115x_pcm_new (struct snd_soc_pcm_runtime *rtd)
#endif
{
    debug ("completed.\n");
    return RET_OK;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static void lg115x_pcm_free (struct snd_soc_component *component, struct snd_pcm *pcm)
#else
static void lg115x_pcm_free (struct snd_pcm *pcm)
#endif
{
    info ("completed.\n");
    return;
}

static int __devinit lg115x_platform_probe (struct platform_device *pdev);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void __devexit lg115x_platform_remove (struct platform_device *pdev);
#else
static int __devexit lg115x_platform_remove (struct platform_device *pdev);
#endif

#if (LINUX_VERSION_CODE < KERNEL_VERSION(5, 5, 0))
static struct snd_pcm_ops lg115x_pcm_ops = {
    .open = lg115x_pcm_open,
    .close = lg115x_pcm_close,
    .ioctl = lg115x_pcm_lib_ioctl,
    .hw_params = lg115x_pcm_hw_params,
    .hw_free = lg115x_pcm_hw_free,
    .prepare = lg115x_pcm_prepare,
    .trigger = lg115x_pcm_trigger,
    .pointer = lg115x_pcm_pointer,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    .copy_user = lg115x_pcm_copy,
    .fill_silence = lg115x_pcm_silence,
#else
    .copy = lg115x_pcm_copy,
    .silence = lg115x_pcm_silence,
#endif
    /*.page */
    .mmap = lg115x_pcm_mmap,
    /*.ack  */
};
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static struct snd_soc_component_driver lg115x_soc_component_driver = {
#else
static struct snd_soc_platform_driver lg115x_soc_platform_driver = {
#endif
#if (LINUX_VERSION_CODE < KERNEL_VERSION(5, 5, 0))
    .ops = &lg115x_pcm_ops,
    .pcm_new = lg115x_pcm_new,
    .pcm_free = lg115x_pcm_free,
#else
    .pcm_construct = lg115x_pcm_new,
    .pcm_destruct = lg115x_pcm_free,
    .open = lg115x_pcm_open,
    .close = lg115x_pcm_close,
    .ioctl = lg115x_pcm_lib_ioctl,
    .hw_params = lg115x_pcm_hw_params,
    .hw_free = lg115x_pcm_hw_free,
    .prepare = lg115x_pcm_prepare,
    .trigger = lg115x_pcm_trigger,
    .pointer = lg115x_pcm_pointer,
    /*.page */
    .mmap = lg115x_pcm_mmap,
    /*.ack  */
#endif
};


static struct platform_driver lg115x_platform_driver = {
    .driver = {
            .name = PLATFORM_NAME,
            .owner = THIS_MODULE,
        },
    .probe = lg115x_platform_probe,
    .remove = __devexit_p (lg115x_platform_remove),
};

static struct platform_device *lg115x_platform_device;

static int __devinit lg115x_platform_probe (struct platform_device *pdev)
{
    int ret = RET_OK;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    ret = snd_soc_register_component (&pdev->dev, &lg115x_soc_component_driver, NULL, 0);
#else
    ret = snd_soc_register_platform (&pdev->dev, &lg115x_soc_platform_driver);
#endif
    if (ret != RET_OK)
    {
        ret = -ENOMEM;
        error ("Could not register Platform: %d.\n", ret);
        goto err_register;
    }

    noti ("completed.\n");
    return RET_OK;

  err_register:
    error ("Return Value(%d).\n", ret);
    return ret;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void __devexit lg115x_platform_remove (struct platform_device *pdev)
#else
static int __devexit lg115x_platform_remove (struct platform_device *pdev)
#endif
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    snd_soc_unregister_component (&pdev->dev);
#else
    snd_soc_unregister_platform (&pdev->dev);
#endif

    info ("completed.\n");
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,5,0)
    return RET_OK;
#endif
}

int ALSA_PLATFORM_Init (void)
{
    int ret = RET_OK;

    /* Add and Register a Platform driver. */
    ret = platform_driver_register (&lg115x_platform_driver);
    if (ret != RET_OK)
    {
        error ("Can not register platform driver.\n");
        goto out;
    }

    lg115x_platform_device = platform_device_alloc (PLATFORM_NAME, -1);
    if (!lg115x_platform_device)
    {
        error ("Can not allocate platform device.\n");
        ret = -ENOMEM;
        goto out;
    }

    ret = platform_device_add (lg115x_platform_device);
    if (ret != RET_OK)
    {
        error ("Can not register platform device.\n");
        goto out;
    }

    info ("completed.\n");
    return ret;

  out:
    error ("Error Return Value(%d).\n", ret);
    return ret;
}

void ALSA_PLATFORM_Cleanup (void)
{
    /* Delete and unregister a Platform PCM driver. */
    platform_device_del (lg115x_platform_device);
    platform_driver_unregister (&lg115x_platform_driver);

    info ("completed.\n");
    return;
}
