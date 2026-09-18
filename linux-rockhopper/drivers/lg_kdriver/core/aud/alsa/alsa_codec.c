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



/** @file alsa_codec.c
 *
 *  This is alsa codec driver.
 *
 *  @author	Won Chang Shin
 *  @version	0.1
 *  @date	2013.03.20
 *  @note	The functions for alsa codec driver.
 *
 *  @{
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <sound/soc.h>
#include <sound/pcm.h>
#include <sound/initval.h>

#include "os_util.h"
#include "base_device.h"
#include "debug_util.h"

#include "audio_kapi.h"

#include "alsa.h"
#include "alsa_codec.h"
#include "alsa_platform.h"
#include "alsa_decoder.h"
#include "alsa_sndout.h"
#include "alsa_se.h"
#include "alsa_capture.h"
#include "alsa_sif.h"

#include "log.h"

#ifndef __devinit
# define __devinit
#endif
#ifndef __devexit
# define __devexit
#endif
#ifndef __devexit_p
# define __devexit_p
#endif

#ifdef SUPPORT_SOUNDBAR
#define LG115x_SOC_CODEC_DAI(id) \
	{ \
		.name                   = CODEC_DAI_NAME "." #id, \
		.playback               = { \
			.stream_name    = "Playback." #id, \
			.channels_min   = 1, \
			.channels_max   = 12, \
			.rates          = LG115x_SUPPORT_PLAYBACK_RATE, \
			.formats        = LG115x_SUPPORT_PLAYBACK_FORMAT, \
		}, \
	}
#define LG115x_SOC_CAP_DAI(id) \
    { \
        .name                   = CODEC_DAI_NAME "." #id, \
        .capture            = { \
            .stream_name    = "Capture." #id, \
            .channels_min   = 1, \
            .channels_max   = 21, \
            .rates          = LG115x_SUPPORT_CAPTURE_RATE, \
            .formats        = LG115x_SUPPORT_CAPTURE_FORMAT, \
        }, \
    }
#else
#define LG115x_SOC_CODEC_DAI(id) \
	{ \
		.name                   = CODEC_DAI_NAME "." #id, \
		.playback               = { \
			.stream_name    = "Playback." #id, \
			.channels_min   = 1, \
			.channels_max   = 10, \
			.rates          = LG115x_SUPPORT_PLAYBACK_RATE, \
			.formats        = LG115x_SUPPORT_PLAYBACK_FORMAT, \
		}, \
	}
#define LG115x_SOC_CAP_DAI(id) \
	{ \
		.name                   = CODEC_DAI_NAME "." #id, \
        .capture            = { \
            .stream_name    = "Capture." #id, \
            .channels_min   = 1, \
            .channels_max   = 10, \
            .rates          = LG115x_SUPPORT_CAPTURE_RATE, \
            .formats        = LG115x_SUPPORT_CAPTURE_FORMAT, \
        }, \
	}
#endif /* SUPPORT_SOUNDBAR */
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
extern int snd_soc_register_codec (struct device *dev, const struct snd_soc_codec_driver *codec_drv,
    struct snd_soc_dai_driver *dai_drv, int num_dai);

#endif
extern int register_direct_audio_kcontrols (struct snd_soc_card *card);

extern struct snd_soc_card lg115x;

static int register_kcontrols (struct snd_soc_card *card)
{
    static int sif_done = 0;
    static int decoder_done = 0, sndout_done = 0;
    static int se_done = 0;
    static int aenc_done = 0;
    int ret = RET_OK;

    if (!sif_done)
    {
        ret = register_sif_kcontrols (card);
        if (ret != RET_OK)
        {
            error ("register_sif_kcontrols is failed (ret %d) \n", ret);
            return ret;
        }
        sif_done = 1;
    }

    if (!decoder_done)
    {
        ret = register_decoder_kcontrols (card);
        if (ret != RET_OK)
        {
            error ("register_decoder_kcontrols is failed (ret %d) \n", ret);
            return ret;
        }
        decoder_done = 1;
    }

    if (!sndout_done)
    {
        ret = register_sndout_kcontrols (card);
        if (ret != RET_OK)
        {
            error ("register_sundout_kcontrols is failed (ret %d) \n", ret);
            return ret;
        }
        sndout_done = 1;
    }

    if (!se_done)
    {
        ret = register_se_kcontrols (card);
        if (ret != RET_OK)
        {
            error ("register_se_kcontrols is failed (ret %d) \n", ret);
            return ret;
        }
        se_done = 1;
    }

#ifdef USE_DIRECT_CODEC
    if (!direct_audio_done)
    {
        ret = register_direct_audio_kcontrols (card);
        if (ret != RET_OK)
        {
            error ("register_direct_audio_kcontrols is failed (ret %d) \n", ret);
            return ret;
        }
        direct_audio_done = 1;
    }
#endif

    if (!aenc_done)
    {
        ret = register_aenc_audio_kcontrols (card);
        if (ret != RET_OK)
        {
            error ("register_aenc_audio_kcontrols is failed (ret %d) \n", ret);
            return ret;
        }
        aenc_done = 1;
    }
    return ret;
}

static int lg115x_codec_probe (struct platform_device *pdev);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void lg115x_codec_remove (struct platform_device *pdev);
#else
static int lg115x_codec_remove (struct platform_device *pdev);
#endif
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static int lg115x_control_probe (struct snd_soc_component *component);
static void lg115x_control_remove (struct snd_soc_component *component);
#else
static int lg115x_control_probe (struct snd_soc_codec *codec);
static int lg115x_control_remove (struct snd_soc_codec *codec);
#endif


#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static struct snd_soc_component_driver lg115x_soc_component_driver = {
#else
static struct snd_soc_codec_driver lg115x_soc_codec_driver = {
#endif
    .probe = lg115x_control_probe,
    .remove = lg115x_control_remove,
};

static struct platform_driver lg115x_codec_driver = {
    .driver = {
            .name = CODEC_NAME,
            .owner = THIS_MODULE,
        },
    .probe = lg115x_codec_probe,
    .remove = __devexit_p (lg115x_codec_remove),
};

struct snd_soc_dai_driver lg115x_soc_codec_dai[] = {
    LG115x_SOC_CODEC_DAI (0),
    LG115x_SOC_CODEC_DAI (1),
    LG115x_SOC_CODEC_DAI (2),
    LG115x_SOC_CODEC_DAI (3),
    LG115x_SOC_CODEC_DAI (4),
    LG115x_SOC_CODEC_DAI (5),
    LG115x_SOC_CODEC_DAI (6),
    LG115x_SOC_CODEC_DAI (7),
    LG115x_SOC_CODEC_DAI (8),
    LG115x_SOC_CODEC_DAI (9),
    LG115x_SOC_CAP_DAI (10),
    LG115x_SOC_CAP_DAI (11),
    LG115x_SOC_CAP_DAI (12),
    LG115x_SOC_CAP_DAI (13),
    LG115x_SOC_CAP_DAI (14),
    LG115x_SOC_CAP_DAI (15),
#if 0
    {
            .name = "snd-soc-dummy-dai",
        },
#endif
};

static struct platform_device *lg115x_codec_device[ALSA_DEVICE_NUM + ALSA_CAP_DEVICE_NUM];


static int vol_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    struct snd_soc_component *component = snd_soc_kcontrol_component (kcontrol);
#else
    struct snd_soc_codec *codec = snd_soc_kcontrol_codec (kcontrol);
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    struct runtime_data *lg115x_data = snd_soc_component_get_drvdata (component);
#else
    struct runtime_data *lg115x_data = snd_soc_codec_get_drvdata (codec);
#endif

    if (lg115x_data == NULL)
    {
        error ("lg115x_data is NULL.\n");
        return -1;
    }

    /* Get a mix volume from local memory. */
    ucontrol->value.integer.value[0] = (long) lg115x_data->volume;


#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    info ("completed(id:%d)(val0:0x%lx).\n", component->id, ucontrol->value.integer.value[0]);
#else
    info ("completed(id:%d)(val0:0x%lx).\n", codec->component.id, ucontrol->value.integer.value[0]);
#endif
    return 0;
}

static int vol_put (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
#if 0
    int ret = RET_OK;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    struct snd_soc_component *component = snd_soc_kcontrol_component (kcontrol);
    struct runtime_data *lg115x_data = snd_soc_component_get_drvdata (component);
#else
    struct snd_soc_codec *codec = snd_soc_kcontrol_codec (kcontrol);
    struct runtime_data *lg115x_data = snd_soc_codec_get_drvdata (codec);
#endif
    struct aud_dev_info *master;

    LX_AUD_MASTER_CONFIG_MIXER_VOLUME_T mixerVolumeConfig;

    if (lg115x_data == NULL)
    {
        error ("lg115x_data is NULL.\n");
        return -1;
    }

    /* Set a mix volume to local memory. */
    lg115x_data->volume = (unsigned int) ucontrol->value.integer.value[0];

    master = AUDIO_OpenMaster ();
    if (IS_ERR (master))
    {
        error ("no master\n");
        return PTR_ERR (master);
    }

    /* Set a mixer volume. */
    mixerVolumeConfig.mixer = LX_AUD_MASTER_MIXER_0;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    mixerVolumeConfig.ui32Port = ALSA_GET_INDEX (component->id);
#else
    mixerVolumeConfig.ui32Port = ALSA_GET_INDEX (codec->component.id);
#endif
    mixerVolumeConfig.ui32Volume = lg115x_data->volume;

    /* Sets audio mix volume that is before mixing main audio. */
    ret = AUDIO_SetMixerVolume (&mixerVolumeConfig);
    AUDIO_CloseMaster (master);
    if (ret != RET_OK)
    {
        error ("KADP_AUDIO_SetMixerVolume is failed.\n");
        return -1;
    }

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    info ("completed(id:%d)(render_volume:0x%X).\n", component->id, lg115x_data->volume);
#else
    info ("completed(id:%d)(render_volume:0x%X).\n", codec->component.id, lg115x_data->volume);
#endif
#endif
    return 0;
}

static const struct snd_kcontrol_new dev0_cont[] = {
    SOC_SINGLE_EXT ("Master Playback Volume", 0, 0, ADEC_DSP_MIX_VOLUME_GAIN_0DB, 0, vol_get,
        vol_put),
    SOC_SINGLE_EXT ("Volume0", 0, 0, ADEC_DSP_MIX_VOLUME_GAIN_0DB, 0, vol_get, vol_put),
};

static const struct snd_kcontrol_new dev1_cont[] = {
    SOC_SINGLE_EXT ("Volume1", 0, 0, ADEC_DSP_MIX_VOLUME_GAIN_0DB, 0, vol_get, vol_put),
};

static const struct snd_kcontrol_new dev2_cont[] = {
    SOC_SINGLE_EXT ("Volume2", 0, 0, ADEC_DSP_MIX_VOLUME_GAIN_0DB, 0, vol_get, vol_put),
};

static const struct snd_kcontrol_new dev3_cont[] = {
    SOC_SINGLE_EXT ("Volume3", 0, 0, ADEC_DSP_MIX_VOLUME_GAIN_0DB, 0, vol_get, vol_put),
};

static const struct snd_kcontrol_new dev4_cont[] = {
    SOC_SINGLE_EXT ("Volume4", 0, 0, ADEC_DSP_MIX_VOLUME_GAIN_0DB, 0, vol_get, vol_put),
};

static const struct snd_kcontrol_new dev5_cont[] = {
    SOC_SINGLE_EXT ("Volume5", 0, 0, ADEC_DSP_MIX_VOLUME_GAIN_0DB, 0, vol_get, vol_put),
};

static const struct snd_kcontrol_new dev6_cont[] = {
    SOC_SINGLE_EXT ("Volume6", 0, 0, ADEC_DSP_MIX_VOLUME_GAIN_0DB, 0, vol_get, vol_put),
};

static const struct snd_kcontrol_new dev7_cont[] = {
    SOC_SINGLE_EXT ("Volume7", 0, 0, ADEC_DSP_MIX_VOLUME_GAIN_0DB, 0, vol_get, vol_put),
};

static const struct
{
    const struct snd_kcontrol_new *controls;
    int count;
} controls[ALSA_DEVICE_NUM + ALSA_CAP_DEVICE_NUM] =
{
    /* *INDENT-OFF* */
    { dev0_cont, ARRAY_SIZE (dev0_cont),},
    { dev1_cont, ARRAY_SIZE (dev1_cont),},
    { dev2_cont, ARRAY_SIZE (dev2_cont),},
    { dev3_cont, ARRAY_SIZE (dev3_cont),},
    { dev4_cont, ARRAY_SIZE (dev4_cont),},
    { dev5_cont, ARRAY_SIZE (dev5_cont),},
    { dev6_cont, ARRAY_SIZE (dev6_cont),},
    { dev7_cont, ARRAY_SIZE (dev7_cont),},
    /* *INDENT-ON* */
};

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static int lg115x_control_probe (struct snd_soc_component *component)
#else
static void lg115x_control_probe (struct snd_soc_codec *codec)
#endif
{
    int ret = RET_OK;

    struct runtime_data *lg115x_data;

    info ("enter");

    /* Sanity Check. */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    if (component->id >= ALSA_DEVICE_NUM + ALSA_CAP_DEVICE_NUM)
#else
    if (codec->component.id >= ALSA_DEVICE_NUM + ALSA_CAP_DEVICE_NUM)
#endif
    {

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
        error ("id(%d) is not supported.\n", component->id);
#else
        error ("id(%d) is not supported.\n", codec->component.id);
#endif
        return -ENOMEM;
    }

    /* Add and Register a Codec Control driver. */
    lg115x_data = kzalloc (sizeof (struct runtime_data), GFP_KERNEL);
    if (lg115x_data == NULL)
    {
        error ("Cannot allocate memory.\n");
        return -ENOMEM;
    }

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    snd_soc_component_set_drvdata (component, lg115x_data);
#else
    snd_soc_codec_set_drvdata (codec, lg115x_data);
#endif
#if 1
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    ret = snd_soc_add_component_controls (component,
        controls[component->id].controls, controls[component->id].count);
#else
    ret = snd_soc_add_codec_controls (codec,
        controls[codec->component.id].controls, controls[codec->component.id].count);
#endif
    if (ret != RET_OK)
    {
        kfree (lg115x_data);
        error ("snd_soc_add_codec_controls fail (ret:%d).\n", ret);
        return RET_ERROR;
    }
#endif
    ret = register_kcontrols (&lg115x);
    if (ret != RET_OK)
    {
        error ("register_kcontrols is failed. (ret %d) \n", ret);
        return RET_ERROR;
    }

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    info ("completed(id:%d).\n", component->id);
#else
    info ("completed(id:%d).\n", codec->component.id);
#endif
    return RET_OK;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static void lg115x_control_remove (struct snd_soc_component *component)
#else
static int lg115x_control_remove (struct snd_soc_codec *codec)
#endif
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    struct runtime_data *lg115x_data = snd_soc_component_get_drvdata (component);
#else
    struct runtime_data *lg115x_data = snd_soc_codec_get_drvdata (codec);
#endif

    if (lg115x_data != NULL)
    {
        kfree (lg115x_data);
    }

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    info ("completed(id:%d).\n", component->id);
    return;
#else
    info ("completed(id:%d).\n", codec->component.id);
    return 0;
#endif
}

static int lg115x_codec_probe (struct platform_device *pdev)
{
    int ret = RET_OK;

    info ("enter");

    ret =
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
        snd_soc_register_component (&pdev->dev, &lg115x_soc_component_driver, lg115x_soc_codec_dai,
#else
        snd_soc_register_codec (&pdev->dev, &lg115x_soc_codec_driver, lg115x_soc_codec_dai,
#endif
        ARRAY_SIZE (lg115x_soc_codec_dai));

    if (ret != RET_OK)
    {
        ret = -ENOMEM;
        error ("Could not register codec.(ret:%d).\n", ret);
        return ret;
    }

    info ("completed(id=%d name=%s).\n", pdev->id, pdev->name);
    return RET_OK;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void lg115x_codec_remove (struct platform_device *pdev)
#else
static int lg115x_codec_remove (struct platform_device *pdev)
#endif
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    snd_soc_unregister_component (&pdev->dev);
#else
    snd_soc_unregister_codec (&pdev->dev);
#endif
    platform_set_drvdata (pdev, NULL);

    info ("completed.\n");
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,5,0)
    return RET_OK;
#endif
}


int ALSA_CODEC_Init (void)
{
    int ret = RET_OK;

    unsigned int i, j;

    /* Add and Register a Codec driver. */
    ret = platform_driver_register (&lg115x_codec_driver);
    if (ret != RET_OK)
    {
        error ("Can not codec driver (ret %d)\n", ret);
        goto out;
    }

    for (i = 0; i < ALSA_DEVICE_NUM; i++)
    {
        lg115x_codec_device[i] = platform_device_alloc (CODEC_NAME, i);
        if (!lg115x_codec_device[i])
        {
            error ("Can not allocate codec device.\n");
            ret = -ENOMEM;
            goto out;
        }

        ret = platform_device_add (lg115x_codec_device[i]);
        if (ret != RET_OK)
        {
            for (j = 0; j <= i; j++)
            {
                platform_device_del (lg115x_codec_device[j]);
            }

            platform_driver_unregister (&lg115x_codec_driver);
            error ("Can not register codec device (ret %d)\n", ret);
            goto out;
        }
    }

    for (i = 0; i < ALSA_CAP_DEVICE_NUM; i++)
    {
        lg115x_codec_device[i + ALSA_DEVICE_NUM] =
            platform_device_alloc (CODEC_NAME, i + ALSA_DEVICE_NUM);

        if (!lg115x_codec_device[i + ALSA_DEVICE_NUM])
        {
            error ("Can not allocate codec device.\n");
            ret = -ENOMEM;
            goto out;
        }

        ret = platform_device_add (lg115x_codec_device[i + ALSA_DEVICE_NUM]);
        if (ret != RET_OK)
        {
            for (j = 0; j <= i; j++)
            {
                platform_device_del (lg115x_codec_device[j + ALSA_DEVICE_NUM]);
            }

            platform_driver_unregister (&lg115x_codec_driver);
            error ("Can not register codec device (ret %d)\n", ret);
            goto out;
        }
    }

    info ("completed.\n");
    return RET_OK;

  out:
    error ("Error Return Value(%d).\n", ret);
    return ret;
}

void ALSA_CODEC_Cleanup (void)
{
    unsigned int i;

    /* Delete and unregister a Codec driver. */
    for (i = 0; i < ALSA_DEVICE_NUM; i++)
    {
        platform_device_del (lg115x_codec_device[i]);
        platform_driver_unregister (&lg115x_codec_driver);
    }

    for (i = 0; i < ALSA_CAP_DEVICE_NUM; i++)
    {
        platform_device_del (lg115x_codec_device[i + ALSA_DEVICE_NUM]);
        platform_driver_unregister (&lg115x_codec_driver);
    }

    info ("completed.\n");
    return;
}
