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
 *  TE(Transport Engine) Driver
 *
 *  @author	Kyungseok Hyun (ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2018-10-17
 *  @note		Additional information.
 */

#include <linux/platform_device.h>

#include "te_impl.h"

static void dev_release(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);

	printk("%s - device released\n", pdev->name);
}

static struct platform_device te_pdev = {
	.name = "lg1k-te",
	.id = PLATFORM_DEVID_NONE,
	.dev = {
		.release = dev_release,
	},
};

static struct platform_device sub_devices[] = {
	{
		.name = "lg1k-crypto",
		.id = PLATFORM_DEVID_NONE,
		.dev = {
			.parent = &te_pdev.dev,
			.release = dev_release,
		},
	},
	{
		.name = "lg1k-sdec",
		.id = PLATFORM_DEVID_NONE,
		.dev = {
			.parent = &te_pdev.dev,
			.release = dev_release,
			.platform_data = NULL,	// TODO: add configuration here !!!
		},
	},
	{
		.name = "lg1k-pvr",
		.id = PLATFORM_DEVID_NONE,
		.dev = {
			.parent = &te_pdev.dev,
			.release = dev_release,
		},
	},
	{
		.name = "lg1k-ci",
		.id = PLATFORM_DEVID_NONE,
		.dev = {
			.parent = &te_pdev.dev,
			.release = dev_release,
		},
	},
	{
		.name = "lg1k-sci",
		.id = PLATFORM_DEVID_NONE,
		.dev = {
			.parent = &te_pdev.dev,
			.release = dev_release,
		},
	},
	{
		.name = "lg1k-ciplus",
		.id = PLATFORM_DEVID_NONE,
		.dev = {
			.parent = &te_pdev.dev,
			.release = dev_release,
		},
	},
	{
		.name = "lg1k-atsc3",
		.id = PLATFORM_DEVID_NONE,
		.dev = {
			.parent = &te_pdev.dev,
			.release = dev_release,
		},
	},
	{
		.name = "lg1k-arib2",
		.id = PLATFORM_DEVID_NONE,
		.dev = {
			.parent = &te_pdev.dev,
			.release = dev_release,
		},
	},
	{
		.name = "lg1k-ci20",
		.id = PLATFORM_DEVID_NONE,
		.dev = {
			.parent = &te_pdev.dev,
			.release = dev_release,
		},
	},
	{
		.name = "lg1k-dvb",
		.id = PLATFORM_DEVID_NONE,
		.dev = {
			.parent = &te_pdev.dev,
			.release = dev_release,
		},
	},
};

#ifdef INCLUDE_M23_CHIP_KDRV
static struct platform_device demod_device = {
	.name = "demod",
	.id = PLATFORM_DEVID_NONE,
	.dev = {
		.parent = &te_pdev.dev,
		.release = dev_release,
	}
};
#endif

struct platform_device *te_register_devices(void)
{
	int rc, i;
	struct platform_device *pdev;
#ifdef INCLUDE_M23_CHIP_KDRV
	struct te_config *cfg = te_get_config();
#endif

	rc = platform_device_register(&te_pdev);
	if (rc) {
		log_error("[%s] platform device register failed\n",
			  te_pdev.name);
		return NULL;
	}
	device_enable_async_suspend(&te_pdev.dev);

	for (i = 0; i < ARRAY_SIZE(sub_devices); i++) {
		pdev = &sub_devices[i];

		rc = platform_device_register(pdev);
		if (rc) {
			log_error("[%s] platform device register failed\n",
				  pdev->name);
		} else {
			log_trace("[%s] platform register done\n", pdev->name);
		}
	}

#ifdef INCLUDE_M23_CHIP_KDRV
	if (cfg->include_demod) {
		pdev = &demod_device;

		rc = platform_device_register(pdev);
		if (rc) {
			log_error("[%s] platform device register failed\n",
				  pdev->name);
		} else {
			log_trace("[%s] platform register done\n", pdev->name);
		}
	}
#endif

	return &te_pdev;
}

void te_unregister_devices(void)
{
	int i, count;

	count = ARRAY_SIZE(sub_devices);
	for (i = 0; i < count; i++) {
		struct platform_device *pdev = &sub_devices[count - i - 1];
		platform_device_unregister(pdev);
	}
	platform_device_unregister(&te_pdev);
}

/******************************************************************************/

int te_register_subdev(struct device *dev, struct te_subdev *sd)
{
	struct device *parent = dev->parent;
	struct platform_device *pdev;
	struct te_device *tdev;

	if (!parent || strcmp(dev_name(parent), "lg1k-te")) {
		log_error("not TE device\n");
		return -EINVAL;
	}

	pdev = to_platform_device(parent);
	tdev = platform_get_drvdata(pdev);

	sd->dev = dev;
	sd->tdev = tdev;

	// TODO: add mutex
	list_add_tail(&sd->list, &tdev->subdevs);

	log_noti("registered TE sub device - '%s'\n", dev_name(dev));

	return 0;
}

struct te_subdev *te_get_subdev(struct te_device *tdev, const char *name)
{
	struct te_subdev *subdev;

	list_for_each_entry(subdev, &tdev->subdevs, list) {
		if (!strcmp(dev_name(subdev->dev), name))
			return subdev;
	}

	return NULL;
}
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
struct device *te_class_device_create(struct te_device *tdev,
				      dev_t devt, void *drvdata,
				      const char *fmt, ...)
{
	va_list vargs;
	struct device *dev;

	va_start(vargs, fmt);
	dev = device_create_vargs(tdev->class, NULL, devt, drvdata, fmt, vargs);
	va_end(vargs);

	return dev;
}
#else
struct device *te_class_device_create(struct te_device *tdev,
				      dev_t devt, void *drvdata,
				      const char *fmt, ...)
{
	va_list vargs;
	struct device *dev;
	char buffer[128];

	va_start(vargs, fmt);
	vsprintf(buffer, fmt, vargs);
	dev = device_create(tdev->class, NULL, devt, drvdata, buffer);
	va_end(vargs);

	return dev;
}
#endif
void te_class_device_destroy(struct te_device *tdev, dev_t devt)
{
	device_destroy(tdev->class, devt);
}
