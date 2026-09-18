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



/** @file alsa_platform_dai.c
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
#include <linux/slab.h>
#include <linux/dma-mapping.h>
#include <asm/uaccess.h>
#include <sound/soc.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>

#include "os_util.h"
#include "base_device.h"
#include "debug_util.h"

#include "audio_kapi.h"

#include "alsa.h"
#include "alsa_platform.h"

logm_define (alsa, log_level_noti);

#ifndef __devinit
# define __devinit
#endif
#ifndef __devexit
# define __devexit
#endif
#ifndef __devexit_p
# define __devexit_p
#endif

#if (LINUX_VERSION_CODE < KERNEL_VERSION(6 ,9, 0))
#ifdef SUPPORT_SOUNDBAR
#define LG115x_DAI(id) \
    { \
        .name = DAI_NAME "." #id, \
        .probe = lg115x_i2s_id_probe, \
        .playback = { \
            .stream_name = "Playback." #id, \
            .channels_min   = 1, \
            .channels_max   = 12, \
            .rates          = LG115x_SUPPORT_PLAYBACK_RATE, \
            .formats        = LG115x_SUPPORT_PLAYBACK_FORMAT, \
        }, \
        .ops = &lg115x_dai_ops, \
    }
#define LG115x_CAP_DAI(id) \
    { \
        .name = DAI_NAME "." #id, \
        .probe = lg115x_i2s_id_probe, \
        .capture = { \
            .stream_name = "Capture." #id, \
            .channels_min   = 1, \
            .channels_max   = 21, \
            .rates          = LG115x_SUPPORT_CAPTURE_RATE, \
            .formats        = LG115x_SUPPORT_CAPTURE_FORMAT, \
        }, \
        .ops = &lg115x_dai_ops, \
    }
#else
#define LG115x_DAI(id) \
    { \
        .name = DAI_NAME "." #id, \
        .probe = lg115x_i2s_id_probe, \
        .playback = { \
            .stream_name = "Playback." #id, \
            .channels_min   = 1, \
            .channels_max   = 10, \
            .rates          = LG115x_SUPPORT_PLAYBACK_RATE, \
            .formats        = LG115x_SUPPORT_PLAYBACK_FORMAT, \
        }, \
        .ops = &lg115x_dai_ops, \
    }

#define LG115x_CAP_DAI(id) \
    { \
        .name = DAI_NAME "." #id, \
        .probe = lg115x_i2s_id_probe, \
        .capture = { \
            .stream_name = "Capture." #id, \
            .channels_min   = 1, \
            .channels_max   = 10, \
            .rates          = LG115x_SUPPORT_CAPTURE_RATE, \
            .formats        = LG115x_SUPPORT_CAPTURE_FORMAT, \
        }, \
        .ops = &lg115x_dai_ops, \
    }
#endif
#else
#ifdef SUPPORT_SOUNDBAR
#define LG115x_DAI(id) \
    { \
        .name = DAI_NAME "." #id, \
        .playback = { \
            .stream_name = "Playback." #id, \
            .channels_min   = 1, \
            .channels_max   = 12, \
            .rates          = LG115x_SUPPORT_PLAYBACK_RATE, \
            .formats        = LG115x_SUPPORT_PLAYBACK_FORMAT, \
        }, \
        .ops = &lg115x_dai_ops, \
    }

#define LG115x_CAP_DAI(id) \
    { \
        .name = DAI_NAME "." #id, \
        .capture = { \
            .stream_name = "Capture." #id, \
            .channels_min   = 1, \
            .channels_max   = 21, \
            .rates          = LG115x_SUPPORT_CAPTURE_RATE, \
            .formats        = LG115x_SUPPORT_CAPTURE_FORMAT, \
        }, \
        .ops = &lg115x_dai_ops, \
    }
#else
#define LG115x_DAI(id) \
    { \
        .name = DAI_NAME "." #id, \
        .playback = { \
            .stream_name = "Playback." #id, \
            .channels_min   = 1, \
            .channels_max   = 10, \
            .rates          = LG115x_SUPPORT_PLAYBACK_RATE, \
            .formats        = LG115x_SUPPORT_PLAYBACK_FORMAT, \
        }, \
        .ops = &lg115x_dai_ops, \
    }

#define LG115x_CAP_DAI(id) \
    { \
        .name = DAI_NAME "." #id, \
        .capture = { \
            .stream_name = "Capture." #id, \
            .channels_min   = 1, \
            .channels_max   = 10, \
            .rates          = LG115x_SUPPORT_CAPTURE_RATE, \
            .formats        = LG115x_SUPPORT_CAPTURE_FORMAT, \
        }, \
        .ops = &lg115x_dai_ops, \
    }
#endif
#endif

#if (LINUX_VERSION_CODE < KERNEL_VERSION(6 ,9, 0))
static int lg115x_i2s_id_probe (struct snd_soc_dai *dai);
#endif

static int lg115x_dai_set_sysclk (struct snd_soc_dai *dai, int clk_id, unsigned int freq, int dir);
static int lg115x_dai_startup (struct snd_pcm_substream *substream, struct snd_soc_dai *dai);
static void lg115x_dai_shutdown (struct snd_pcm_substream *substream, struct snd_soc_dai *dai);
static int lg115x_dai_set_fmt (struct snd_soc_dai *dai, unsigned int fmt);
static int lg115x_dai_hw_params (struct snd_pcm_substream *substream,
    struct snd_pcm_hw_params *params, struct snd_soc_dai *dai);
static int lg115x_dai_trigger (struct snd_pcm_substream *substream, int cmd,
    struct snd_soc_dai *dai);

static int __devinit lg115x_dai_probe (struct platform_device *pdev);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void __devexit lg115x_dai_remove (struct platform_device *pdev);
#else
static int __devexit lg115x_dai_remove (struct platform_device *pdev);
#endif

static struct snd_soc_dai_ops lg115x_dai_ops = {
    .set_sysclk = lg115x_dai_set_sysclk,
    .startup = lg115x_dai_startup,
    .shutdown = lg115x_dai_shutdown,
    .set_fmt = lg115x_dai_set_fmt,
    .hw_params = lg115x_dai_hw_params,
    .trigger = lg115x_dai_trigger,
};

struct snd_soc_dai_driver lg115x_dai[] = {
    LG115x_DAI (0),
    LG115x_DAI (1),
    LG115x_DAI (2),
    LG115x_DAI (3),
    LG115x_DAI (4),
    LG115x_DAI (5),
    LG115x_DAI (6),
    LG115x_DAI (7),
    LG115x_DAI (8),
    LG115x_DAI (9),
    LG115x_CAP_DAI (10),
    LG115x_CAP_DAI (11),
    LG115x_CAP_DAI (12),
    LG115x_CAP_DAI (13),
    LG115x_CAP_DAI (14),
    LG115x_CAP_DAI (15),
#if 0
    {
            .name = "lgsic-mc2.0",
            .probe = lg115x_i2s_id_probe,
            .ops = &lg115x_dai_ops,
        },
#endif
};

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
static const struct snd_soc_component_driver lg115x_dai_component[] = {
    {.name = "lg115x_dai_component.0",},
    {.name = "lg115x_dai_component.1",},
    {.name = "lg115x_dai_component.2",},
    {.name = "lg115x_dai_component.3",},
    {.name = "lg115x_dai_component.4",},
    {.name = "lg115x_dai_component.5",},
    {.name = "lg115x_dai_component.6",},
    {.name = "lg115x_dai_component.7",},
    {.name = "lg115x_dai_component.8",},
    {.name = "lg115x_dai_component.9",},
    {.name = "lg115x_dai_component.10",},
    {.name = "lg115x_dai_component.11",},
    {.name = "lg115x_dai_component.12",},
    {.name = "lg115x_dai_component.13",},
    {.name = "lg115x_dai_component.14",},
    {.name = "lg115x_dai_component.15",},
};
#endif

static struct platform_driver lg115x_dai_driver = {
    .driver = {
            .name = DAI_NAME,
            .owner = THIS_MODULE,
        },
    .probe = lg115x_dai_probe,
    .remove = __devexit_p (lg115x_dai_remove),
};

static struct platform_device *lg115x_dai_device;


#if (LINUX_VERSION_CODE < KERNEL_VERSION(6 ,9, 0))
static int lg115x_i2s_id_probe (struct snd_soc_dai *dai)
{
    debug ("completed.\n");
    return RET_OK;
}
#endif

static int lg115x_dai_set_sysclk (struct snd_soc_dai *dai, int clk_id, unsigned int freq, int dir)
{
    debug ("completed.\n");
    return RET_OK;
}

static int lg115x_dai_startup (struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
    debug ("completed.\n");
    return RET_OK;
}

static void lg115x_dai_shutdown (struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
    debug ("completed.\n");
    return;
}

static int lg115x_dai_set_fmt (struct snd_soc_dai *dai, unsigned int fmt)
{
    debug ("completed.\n");
    return RET_OK;
}

static int lg115x_dai_hw_params (struct snd_pcm_substream *substream,
    struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
    debug ("completed.\n");
    return RET_OK;
}

static int lg115x_dai_trigger (struct snd_pcm_substream *substream, int cmd,
    struct snd_soc_dai *dai)
{
    debug ("completed.\n");
    return RET_OK;
}


static __devinit int lg115x_dai_probe (struct platform_device *pdev)
{
    int ret = RET_OK;

    info ("entered. %d", pdev->id);

    if ((pdev->id < 0) || (pdev->id >= ARRAY_SIZE (lg115x_dai)))
    {
        error ("ID(%d) is out of range.\n", pdev->id);
        return -EINVAL;
    }

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0)
    ret = snd_soc_register_dai (&pdev->dev, &lg115x_dai[pdev->id]);
#else
    ret =
        snd_soc_register_component (&pdev->dev, &lg115x_dai_component[pdev->id],
        &lg115x_dai[pdev->id], 1);
#endif

    if (ret != RET_OK)
    {
        ret = -ENOMEM;
        error ("Could not register DAI(%d).\n", ret);
        goto err_register;
    }

    info ("completed.\n");
    return ret;

  err_register:
    error ("Return Value(%d).\n", ret);
    return ret;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void  __devexit lg115x_dai_remove (struct platform_device *pdev)
#else
static int __devexit lg115x_dai_remove (struct platform_device *pdev)
#endif
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0)
    snd_soc_unregister_dai (&pdev->dev);
#else
    snd_soc_unregister_component (&pdev->dev);
#endif

    debug ("completed.\n");
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,5,0)
    return RET_OK;
#endif
}


SINT32 ALSA_PLATFORM_DAI_Init (void)
{
    int ret = RET_OK;
    int i;

    /* Add and Register a DAI driver. */
    ret = platform_driver_register (&lg115x_dai_driver);
    if (ret != RET_OK)
    {
        error ("Can not register dai driver.\n");
        goto out;
    }

    for (i = 0; i < ALSA_DEVICE_NUM; i++)
    {
        lg115x_dai_device = platform_device_alloc (DAI_NAME, i);
        if (!lg115x_dai_device)
        {
            error ("Can not allocate dai device.\n");
            ret = -ENOMEM;
            goto out;
        }

        ret = platform_device_add (lg115x_dai_device);
        if (ret != RET_OK)
        {
            error ("Can not register dai device.\n");
            goto out;
        }
    }

    for (i = 0; i < ALSA_CAP_DEVICE_NUM; i++)
    {
        lg115x_dai_device = platform_device_alloc (DAI_NAME, i + ALSA_DEVICE_NUM);

        if (!lg115x_dai_device)
        {
            error ("Can not allocate dai device.\n");
            ret = -ENOMEM;
            goto out;
        }

        ret = platform_device_add (lg115x_dai_device);
        if (ret != RET_OK)
        {
            error ("Can not register dai device.\n");
            goto out;
        }
    }

    debug ("completed.\n");
    return ret;

  out:
    error ("Error Return Value(%d).\n", ret);
    return ret;
}

void ALSA_PLATFORM_DAI_Cleanup (void)
{
    unsigned int i;

    /* Delete and unregister a Platform DAI driver. */
    for (i = 0; i < ALSA_DEVICE_NUM; i++)
    {
        platform_device_del (lg115x_dai_device);
        platform_driver_unregister (&lg115x_dai_driver);
    }

    for (i = 0; i < ALSA_CAP_DEVICE_NUM; i++)
    {
        platform_device_del (lg115x_dai_device);
        platform_driver_unregister (&lg115x_dai_driver);
    }

    noti ("completed.\n");
    return;
}
