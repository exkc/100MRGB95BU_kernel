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

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <sound/soc.h>

static int log_level = 4;
module_param (log_level, int, 0644);

#define trace(fmt,args...)	do{if (log_level >= 6) printk ("%s.%d: "fmt,__func__,__LINE__,##args);}while(0)
#define debug(fmt,args...)	do{if (log_level >= 5) printk ("%s.%d: "fmt,__func__,__LINE__,##args);}while(0)
#define info(fmt,args...)	do{if (log_level >= 4) printk ("%s.%d: "fmt,__func__,__LINE__,##args);}while(0)
#define noti(fmt,args...)	do{if (log_level >= 3) printk ("%s.%d: "fmt,__func__,__LINE__,##args);}while(0)
#define warn(fmt,args...)	do{if (log_level >= 2) printk ("%s.%d: "fmt,__func__,__LINE__,##args);}while(0)
#define error(fmt,args...)	do{if (log_level >= 1) printk ("%s.%d: "fmt,__func__,__LINE__,##args);}while(0)

static struct snd_soc_dai_driver codec_dai[] = {
    {
            .name = "lgsic-codec-pdmmic-dai",
            .capture = {
                    .stream_name = "PDM Mic Capture",
                    .channels_min = 2,
                    .channels_max = 2,
                    .rates = SNDRV_PCM_RATE_8000,
                    .formats = SNDRV_PCM_FMTBIT_S16_LE,
                },
        },
};

static struct snd_soc_codec_driver codec_driver;

static int pdev_probe (struct platform_device *pdev)
{
    int ret;

    info ("probe..\n");

    ret = snd_soc_register_codec (&pdev->dev, &codec_driver, codec_dai, ARRAY_SIZE (codec_dai));
    if (ret < 0)
    {
        error ("cannot register_codec(). %d\n", ret);
        return ret;
    }

    return 0;
}

static int pdev_remove (struct platform_device *pdev)
{
    snd_soc_unregister_codec (&pdev->dev);

    info ("done.\n");
    return 0;
}

static struct platform_driver pdev_driver = {
    .driver = {
            .name = "lgsic-codec-pdmmic",
        },
    .probe = pdev_probe,
    .remove = pdev_remove,
};

module_platform_driver (pdev_driver);

MODULE_AUTHOR ("LGE");
MODULE_DESCRIPTION ("LG SIC codec driver");
MODULE_LICENSE ("GPL");
