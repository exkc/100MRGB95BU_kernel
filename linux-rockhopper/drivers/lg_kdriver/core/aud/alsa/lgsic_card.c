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

/** @file card.c
 *
 *  ALSA card driver
 *
 *  @author Youngwoo Jin (youngwoo.jin@lge.com)
 *  @version    0.1
 *  @date       2019.12.26
 */

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/version.h>
#include <sound/soc.h>

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/
#define _print(fmt,args...) do { printk ("%s.%d: "fmt,__func__,__LINE__,##args); } while(0)
#define trace(fmt,args...)	do { if (log_level >= 6) _print (fmt,##args); } while(0)
#define debug(fmt,args...)	do { if (log_level >= 5) _print (fmt,##args); } while(0)
#define info(fmt,args...)	do { if (log_level >= 4) _print (fmt,##args); } while(0)
#define noti(fmt,args...)	do { if (log_level >= 3) _print (fmt,##args); } while(0)
#define warn(fmt,args...)	do { if (log_level >= 2) _print (fmt,##args); } while(0)
#define error(fmt,args...)	do { if (log_level >= 1) _print (fmt,##args); } while(0)

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    External Variables
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    global Variables
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Static Function Prototypes Declarations
------------------------------------------------------------------------------*/
static int pdev_probe (struct platform_device *pdev);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void pdev_remove (struct platform_device *pdev);
#else
static int pdev_remove (struct platform_device *pdev);
#endif

/*------------------------------------------------------------------------------
    Static Variables
------------------------------------------------------------------------------*/
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
SND_SOC_DAILINK_DEFS (mic,
    DAILINK_COMP_ARRAY (COMP_CPU ("lgsic-pdm0")),
    DAILINK_COMP_ARRAY (COMP_CODEC ("snd-soc-dummy", "snd-soc-dummy-dai")),
    DAILINK_COMP_ARRAY (COMP_PLATFORM ("lgsic-pdm0")));

SND_SOC_DAILINK_DEFS (spk,
    DAILINK_COMP_ARRAY (COMP_CPU ("lgsic-bc-sai0")),
    DAILINK_COMP_ARRAY (COMP_CODEC ("snd-soc-dummy", "snd-soc-dummy-dai")),
    DAILINK_COMP_ARRAY (COMP_PLATFORM ("lgsic-bc-sai0")));

SND_SOC_DAILINK_DEFS (mc,
    DAILINK_COMP_ARRAY (COMP_CPU ("lgsic-mc")),
    DAILINK_COMP_ARRAY (COMP_CODEC ("snd-soc-dummy", "snd-soc-dummy-dai")),
    DAILINK_COMP_ARRAY (COMP_PLATFORM ("lgsic-mc")));

SND_SOC_DAILINK_DEFS (sec,
    DAILINK_COMP_ARRAY (COMP_CPU ("lgsic-mc")),
    DAILINK_COMP_ARRAY (COMP_CODEC ("snd-soc-dummy", "snd-soc-dummy-dai")),
    DAILINK_COMP_ARRAY (COMP_PLATFORM ("lgsic-mc")));

SND_SOC_DAILINK_DEFS (btc,
    DAILINK_COMP_ARRAY (COMP_CPU ("lgsic-mc")),
    DAILINK_COMP_ARRAY (COMP_CODEC ("snd-soc-dummy", "snd-soc-dummy-dai")),
    DAILINK_COMP_ARRAY (COMP_PLATFORM ("lgsic-mc")));

#ifdef SUPPORT_SOUNDBAR
SND_SOC_DAILINK_DEFS (mic1,
    DAILINK_COMP_ARRAY (COMP_CPU ("lgsic-pdm1")),
    DAILINK_COMP_ARRAY (COMP_CODEC ("snd-soc-dummy", "snd-soc-dummy-dai")),
    DAILINK_COMP_ARRAY (COMP_PLATFORM ("lgsic-pdm1")));
#endif

#endif
struct snd_soc_dai_link lgsic_dai_link[] = {
    /* *INDENT-OFF* */
    {
        .name = "PDMMic",
        .stream_name = "WoV PDM Mic",
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
        SND_SOC_DAILINK_REG(mic),
#else
        .platform_name = "lgsic-pdm0",
        .cpu_name = "lgsic-pdm0",
        .cpu_dai_name = "lgsic-pdm0",
        .codec_dai_name = "snd-soc-dummy-dai",
        .codec_name = "snd-soc-dummy",
#endif
        .capture_only = true,
    },
    {
        .name = "SpeakerFeedback",
        .stream_name = "SpeakerFeedback",
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
        SND_SOC_DAILINK_REG(spk),
#else
        .platform_name = "lgsic-bc-sai0",
        .cpu_name = "lgsic-bc-sai0",
        .cpu_dai_name = "lgsic-bc-sai0",
        .codec_dai_name = "snd-soc-dummy-dai",
        .codec_name = "snd-soc-dummy",
#endif
        .capture_only = true,
    },
    {
        .name = "MixerCapture",
        .stream_name = "MixerCapture",
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
        SND_SOC_DAILINK_REG(mc),
#else
        .platform_name = "lgsic-mc",
        .cpu_name = "lgsic-mc",
        .cpu_dai_name = "lgsic-mc",
        .codec_dai_name = "snd-soc-dummy-dai",
        .codec_name = "snd-soc-dummy",
#endif
        .capture_only = true,
    },
    {
        .name = "SoundEngineCapture",
        .stream_name = "SoundEngineCapture",
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
        SND_SOC_DAILINK_REG(sec),
#else
        .platform_name = "lgsic-mc",
        .cpu_name = "lgsic-mc",
        .cpu_dai_name = "lgsic-mc",
        .codec_dai_name = "snd-soc-dummy-dai",
        .codec_name = "snd-soc-dummy",
#endif
        .capture_only = true,
    },
    {
        .name = "BluetoothCapture",
        .stream_name = "BluetoothCapture",
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
        SND_SOC_DAILINK_REG(btc),
#else
        .platform_name = "lgsic-mc",
        .cpu_name = "lgsic-mc",
        .cpu_dai_name = "lgsic-mc",
        .codec_dai_name = "snd-soc-dummy-dai",
        .codec_name = "snd-soc-dummy",
#endif
        .capture_only = true,
    },

#ifdef SUPPORT_SOUNDBAR
    {
        .name = "PDMMic1",
        .stream_name = "WoV PDM Mic1",
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
        SND_SOC_DAILINK_REG(mic1),
#else
        .platform_name = "lgsic-pdm1",
        .cpu_name = "lgsic-pdm1",
        .cpu_dai_name = "lgsic-pdm1",
        .codec_dai_name = "snd-soc-dummy-dai",
        .codec_name = "snd-soc-dummy",
#endif
        .capture_only = true,
    },
#endif

    /* *INDENT-ON* */
};

static struct snd_soc_card card_data = {
    .name = "LGSIC",
    .owner = THIS_MODULE,
    .dai_link = lgsic_dai_link,
    .num_links = ARRAY_SIZE (lgsic_dai_link),
};

static struct platform_driver pdev_driver = {
    .driver = {
            .name = "lgsic-audio",
            .pm = &snd_soc_pm_ops,
        },
    .probe = pdev_probe,
    .remove = pdev_remove,
};

static int log_level = 4;
module_param (log_level, int, 0644);

/*==============================================================================
    Implementation Group
==============================================================================*/

static int pdev_probe (struct platform_device *pdev)
{
    struct snd_soc_card *card = &card_data;
    int ret;

    info ("probe.. card..\n");

    card->dev = &pdev->dev;

    ret = snd_soc_register_card (card);
    if (ret < 0)
    {
        error ("cannot register_card(). %d\n", ret);
        return ret;
    }

    return 0;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void pdev_remove (struct platform_device *pdev)
#else
static int pdev_remove (struct platform_device *pdev)
#endif
{
    struct snd_soc_card *card = platform_get_drvdata (pdev);

    snd_soc_unregister_card (card);

    info ("done.\n");
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,5,0)
    return 0;
#endif
}

module_platform_driver (pdev_driver);

MODULE_AUTHOR ("LGE");
MODULE_DESCRIPTION ("LG SIC codec driver");
MODULE_LICENSE ("GPL");
