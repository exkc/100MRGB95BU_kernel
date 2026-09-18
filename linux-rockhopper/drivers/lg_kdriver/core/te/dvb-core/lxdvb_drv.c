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
 *  TE(Transport Engine) Driver for linux dvb(DEMUX&CA)
 *
 *  @author	Kyungseok Hyun (ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2018-01-26
 *  @note		Additional information.
 */

#include "lxdvb_impl.h"

int lxdvb_module_init(void);
void lxdvb_module_exit(void);

int g_lxdvb_debug_fd = -1;

static void init_logm(void)
{
	if (g_lxdvb_debug_fd == -1) {
		g_lxdvb_debug_fd = LOGM_ObjRegister("lxdvb");
		LOGM_ObjBitMaskEnable(g_lxdvb_debug_fd, LOG_LEVEL_ERROR);
		LOGM_ObjBitMaskEnable(g_lxdvb_debug_fd, LOG_LEVEL_WARNING);
		LOGM_ObjBitMaskEnable(g_lxdvb_debug_fd, LOG_LEVEL_NOTI);
	}
}

static int probe(struct platform_device *pdev)
{
	int ret;
	struct lxdvb_device *dev;

	dev = devm_kzalloc(&pdev->dev, sizeof(*dev), GFP_KERNEL);
	CHECK_ERROR(!dev, goto error, "no memory");

	dev->pdev = pdev;
	platform_set_drvdata(pdev, dev);
	te_register_subdev(&pdev->dev, &dev->subdev);

	ret = lxdvb_device_init(dev);
	CHECK_ERROR(ret, goto error, "Error in lxdvb_device_init");

	log_noti("%s probe done\n", LXDVB_DEVICE_NAME);

	return 0;

error:
	panic("%s probe failed\n", LXDVB_DEVICE_NAME);
}

static void remove(struct platform_device *pdev)
{
	struct lxdvb_device *dev = platform_get_drvdata(pdev);

	lxdvb_device_release(dev);

	log_noti("%s remove done\n", LXDVB_DEVICE_NAME);
}

#if (LINUX_VERSION_CODE < KERNEL_VERSION(6, 5, 0))
static int legacy_remove(struct platform_device *pdev)
{
	remove(pdev);
	return 0;
}
#endif

static int suspend(struct platform_device *pdev, pm_message_t state)
{
	int ret;
	struct lxdvb_device *dev = platform_get_drvdata(pdev);

	printk("%s - suspend BEGIN\n", LXDVB_MODULE);

	ret = lxdvb_device_suspend(dev);
	if (ret) {
		printk("%s - suspend failed\n", LXDVB_MODULE);
		return ret;
	}

	printk("%s - suspend END\n", LXDVB_MODULE);

	return 0;
}

static int resume(struct platform_device *pdev)
{
	int ret;
	struct lxdvb_device *dev = platform_get_drvdata(pdev);

	printk("%s - resume BEGIN\n", LXDVB_MODULE);

	ret = lxdvb_device_resume(dev);
	if (ret) {
		printk("%s - resume failed\n", LXDVB_MODULE);
		return ret;
	}

	printk("%s - resume OK\n", LXDVB_MODULE);

	return 0;
}

static struct platform_driver platform_driver = {
	.probe = probe,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 5, 0))
	.remove = remove,
#else
	.remove = legacy_remove,
#endif
	.suspend = suspend,
	.resume = resume,
	.driver = {
		.name = LXDVB_DEVICE_NAME,
	},
};

int lxdvb_module_init(void)
{
	int ret;

	init_logm();

	ret = platform_driver_register(&platform_driver);
	if (ret) {
		log_error("[%s] platform driver register failed\n",
			  LXDVB_DEVICE_NAME);
		return ret;
	}

	return 0;
}

void lxdvb_module_exit(void)
{
	platform_driver_unregister(&platform_driver);
}

/** @} */
