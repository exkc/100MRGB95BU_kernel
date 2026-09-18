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



/** @file alsa_machine.c
 *
 *  This is alsa machine driver.
 *
 *  @author	Won Chang Shin(wonchang.shin@lge.com)
 *  @version	0.1
 *  @date	2013.03.20
 *  @note	The functions for alsa machin driver.
 *
 *  @{
 */

#include <linux/module.h>
#include <sound/soc.h>
#include <sound/pcm_params.h>

#include "os_util.h"
#include "base_device.h"
#include "debug_util.h"

#include "audio_kapi.h"
#include "alsa.h"
#include "alsa_codec.h"
#include "alsa_platform.h"
#include "alsa_machine.h"
#define CARD_NAME       "lg115x"

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)

#define LG115X_SND_SOC_DAILINK_DEFS(id) \
SND_SOC_DAILINK_DEFS(dai##id, \
        DAILINK_COMP_ARRAY(COMP_CPU(DAI_NAME "." #id)), \
        DAILINK_COMP_ARRAY(COMP_CODEC(CODEC_NAME "." #id, CODEC_DAI_NAME "." #id)), \
        DAILINK_COMP_ARRAY(COMP_PLATFORM("lgsic-aplayback"))); \

#define LG115X_SND_SOC_DAILINK_DEFS_CAP(id) \
SND_SOC_DAILINK_DEFS(dai##id, \
        DAILINK_COMP_ARRAY(COMP_CPU(DAI_NAME "." #id)), \
        DAILINK_COMP_ARRAY(COMP_CODEC(CODEC_NAME "." #id, CODEC_DAI_NAME "." #id)), \
        DAILINK_COMP_ARRAY(COMP_PLATFORM("lgsic-acapture"))); \

/* *INDENT-OFF* */
LG115X_SND_SOC_DAILINK_DEFS (0)
LG115X_SND_SOC_DAILINK_DEFS (1)
LG115X_SND_SOC_DAILINK_DEFS (2)
LG115X_SND_SOC_DAILINK_DEFS (3)
LG115X_SND_SOC_DAILINK_DEFS (4)
LG115X_SND_SOC_DAILINK_DEFS (5)
LG115X_SND_SOC_DAILINK_DEFS (6)
LG115X_SND_SOC_DAILINK_DEFS (7)
LG115X_SND_SOC_DAILINK_DEFS (8)
LG115X_SND_SOC_DAILINK_DEFS (9)
LG115X_SND_SOC_DAILINK_DEFS_CAP (10)
LG115X_SND_SOC_DAILINK_DEFS_CAP (11)
LG115X_SND_SOC_DAILINK_DEFS_CAP (12)
LG115X_SND_SOC_DAILINK_DEFS_CAP (13)
LG115X_SND_SOC_DAILINK_DEFS_CAP (14)
LG115X_SND_SOC_DAILINK_DEFS_CAP (15)
/* *INDENT-ON* */
#endif
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#define LG115x_DAI_LINK(id) \
		{ \
			.name 		= CARD_NAME "." #id, \
			.stream_name 	= CARD_NAME "." #id, \
			SND_SOC_DAILINK_REG(dai##id), \
			.nonatomic 	= TRUE, \
		}
#else
#define LG115x_DAI_LINK(id) \
		{ \
			.name 		= CARD_NAME "." #id, \
			.stream_name 	= CARD_NAME "." #id, \
			.cpu_dai_name 	= DAI_NAME "." #id, \
			.codec_dai_name = CODEC_DAI_NAME "." #id, \
			.platform_name 	= /*PLATFORM_NAME*/"lgsic-aplayback", \
			.codec_name 	= CODEC_NAME "." #id, \
			.nonatomic 	= TRUE, \
		}
#endif
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#define LG115x_CAP_DAI_LINK(id) \
		{ \
			.name 		= CARD_NAME "." #id, \
			.stream_name 	= CARD_NAME "." #id, \
			SND_SOC_DAILINK_REG(dai##id), \
			.nonatomic 	= TRUE, \
		}
#else
#define LG115x_CAP_DAI_LINK(id) \
		{ \
			.name 		= CARD_NAME "." #id, \
			.stream_name 	= CARD_NAME "." #id, \
			.cpu_dai_name 	= DAI_NAME "." #id, \
			.codec_dai_name = CODEC_DAI_NAME "." #id, \
			.platform_name 	= "lgsic-acapture"/*PLATFORM_NAME*/, \
			.codec_name 	= CODEC_NAME "." #id, \
			.nonatomic 	= TRUE, \
		}
#endif
struct snd_soc_dai_link lg115x_dai_link[] = {
    LG115x_DAI_LINK (0),
    LG115x_DAI_LINK (1),
    LG115x_DAI_LINK (2),
    LG115x_DAI_LINK (3),
    LG115x_DAI_LINK (4),
    LG115x_DAI_LINK (5),
    LG115x_DAI_LINK (6),
    LG115x_DAI_LINK (7),
    LG115x_DAI_LINK (8),
    LG115x_DAI_LINK (9),
    LG115x_CAP_DAI_LINK (10),
    LG115x_CAP_DAI_LINK (11),
    LG115x_CAP_DAI_LINK (12),
    LG115x_CAP_DAI_LINK (13),
    LG115x_CAP_DAI_LINK (14),
    LG115x_CAP_DAI_LINK (15),
};

struct snd_soc_card lg115x = {
    .name = CARD_NAME,
    .owner = THIS_MODULE,
    .dai_link = lg115x_dai_link,
    .num_links = ARRAY_SIZE (lg115x_dai_link),
};

static struct platform_device *lg115x_audio_device;


int ALSA_MACHINE_Init (void)
{
    int ret = RET_OK;

    /* Initializes ALSA Platform DAI driver. */
    ret = ALSA_PLATFORM_DAI_Init ();
    if (ret != RET_OK)
    {
        error ("ALSA_PLATFORM_DAI_Init is failed.\n");
        return ret;
    }

    /* Initializes ALSA Codec driver. */
    ret = ALSA_CODEC_Init ();
    if (ret != RET_OK)
    {
        error ("ALSA_CODEC_Init is failed.\n");
        return ret;
    }

    ret = ALSA_PLATFORM_Init ();
    if (ret != RET_OK)
    {
        error ("ALSA_PLATFORM_Init is failed.\n");
        return ret;
    }

    ret = acapture_init ();
    if (ret != RET_OK)
    {
        error ("acapture_init is failed.\n");
        return ret;
    }

    ret = aplayback_init ();
    if (ret != RET_OK)
    {
        error ("aplayback_init is failed.\n");
        return ret;
    }

    /* Add and Register a platform device driver. */
    lg115x_audio_device = platform_device_alloc ("soc-audio", -1);
    if (!lg115x_audio_device)
    {
        error ("platform_device_alloc is failed.\n");
        return -ENOMEM;
    }

    noti ("alloc OK");

    /* Do not use snd_soc_register_card(This function should be called kernel function.) */
    platform_set_drvdata (lg115x_audio_device, &lg115x);

    noti ("set drvdata OK");

    /* Add a platform device. */
    ret = platform_device_add (lg115x_audio_device);
    if (ret != RET_OK)
    {
        /* Delete a platform device if error is found. */
        platform_device_del (lg115x_audio_device);
        error ("platform_device_add is failed. ret %d \n", ret);
        return -ENOMEM;
    }

    info ("completed.\n");
    return ret;
}

void ALSA_MACHINE_Cleanup (void)
{
    /* Delete and unregister a Platform PCM driver. */
    platform_device_del (lg115x_audio_device);
    platform_set_drvdata (lg115x_audio_device, NULL);

    /* Cleanup a Codec Driver. */
    ALSA_CODEC_Cleanup ();

    /* Cleanup a Platform DAI Driver. */
    ALSA_PLATFORM_DAI_Cleanup ();

    aplayback_cleanup ();

    acapture_cleanup ();

    noti ("completed.\n");
    return;
}
