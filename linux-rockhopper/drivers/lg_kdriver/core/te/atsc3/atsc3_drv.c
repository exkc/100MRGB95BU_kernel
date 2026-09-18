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
 *  atsc3 device driver
 *
 *  @author		Yeonju Lee (yeonju.lee@lge.com)
 *  @version	1.0
 *  @date		2016-02-29
 *  @note		Additional information.
 */

#include <linux/platform_device.h>

#include "base_device.h"
#include "atsc3_impl.h"

int g_atsc3_debug_fd = -1;

int atsc3_module_init(void);
void atsc3_module_exit(void);

static void init_logm(void)
{
	if (g_atsc3_debug_fd != -1)
		return;

	g_atsc3_debug_fd = LOGM_ObjRegister(ATSC3_MODULE);
	LOGM_ObjBitMaskEnable(g_atsc3_debug_fd, LOG_LEVEL_ERROR);
	LOGM_ObjBitMaskEnable(g_atsc3_debug_fd, LOG_LEVEL_WARNING);
	LOGM_ObjBitMaskEnable(g_atsc3_debug_fd, LOG_LEVEL_NOTI);

	LOGM_RegBitName(g_atsc3_debug_fd, LOG_LEVEL_TRACE_EX, "TRACE_EX");
	LOGM_RegBitName(g_atsc3_debug_fd, LOG_LEVEL_FILTER, "FILTER");
	LOGM_RegBitName(g_atsc3_debug_fd, LOG_LEVEL_IO, "IO");
	LOGM_RegBitName(g_atsc3_debug_fd, LOG_LEVEL_CLOCK, "CLOCK");
}

static int register_dev_node(struct atsc3_device *dev)
{
	int ret, i;
	dev_t devt;
	struct te_device *tdev = get_te_device(dev);

	devt = MKDEV(ATSC3_MAJOR, 0);
	ret = register_chrdev_region(devt, 1 + dev->num_channel, ATSC3_MODULE);
	CHECK_ERROR(ret, return ret, "Error(%d) in register_chrdev_region",
		    ret);

	/* initialize cdev structure with predefined variable */
	cdev_init(&dev->cdev, &atsc3_dev_fops);
	dev->cdev.owner = THIS_MODULE;
	ret = cdev_add(&dev->cdev, devt, 1 + dev->num_channel);
	CHECK_ERROR(ret, return ret, "Error(%d) in cdev_add", ret);

	te_class_device_create(tdev, devt, dev, "%s", ATSC3_MODULE);
	for (i = 0; i < dev->num_channel; i++) {
		te_class_device_create(tdev, MKDEV(ATSC3_MAJOR, 1 + i),
				       &dev->channels[i], "%sc%d", ATSC3_MODULE,
				       i);
	}

	return 0;
}

static void unregister_dev_node(struct atsc3_device *dev)
{
	int i;
	struct te_device *tdev = get_te_device(dev);

	for (i = 0; i < dev->num_channel; i++) {
		te_class_device_destroy(tdev, MKDEV(ATSC3_MAJOR, 1 + i));
	}
	te_class_device_destroy(tdev, MKDEV(ATSC3_MAJOR, 0));
	cdev_del(&dev->cdev);

	unregister_chrdev_region(MKDEV(ATSC3_MAJOR, 0), 1 + dev->num_channel);
}

static int probe(struct platform_device *pdev)
{
	int ret;
	struct atsc3_config *cfg;
	struct atsc3_device *dev;

	cfg = atsc3_get_config();
	dev = devm_kzalloc(&pdev->dev,
			   sizeof(struct atsc3_device) +
			   cfg->num_ch * sizeof(struct atsc3_channel),
			   GFP_KERNEL);
	CHECK_ERROR(!dev, goto error, "no memory");

	platform_set_drvdata(pdev, dev);
	te_register_subdev(&pdev->dev, &dev->subdev);

	dev->cfg = cfg;
	dev->num_channel = cfg->num_ch;
	mutex_init(&dev->mutex);

	ret = atsc3_device_init(dev);
	CHECK_ERROR(ret, goto error, "Error(%d) in atsc3_device_init", ret);

	ret = register_dev_node(dev);
	CHECK_ERROR(ret, goto error, "Error(%d) in register_dev_node", ret);

	log_noti("atsc3 probe done\n");

	return 0;
error:
	panic("atsc3 probe failed\n");
}

static void remove(struct platform_device *pdev)
{
	struct atsc3_device *dev = platform_get_drvdata(pdev);

	unregister_dev_node(dev);

	atsc3_device_release(dev);

	log_noti("atsc3 remove done\n");
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
	struct atsc3_device *dev = platform_get_drvdata(pdev);
	struct te_device *tdev = get_te_device(dev);

	te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_ATSC3);

	printk("ATSC3 - suspend BEGIN\n");

	ret = atsc3_device_suspend(dev);
	if (ret) {
		printk("ATSC3 - suspend failed\n");
		return ret;
	}

	printk("ATSC3 - suspend END\n");

	return 0;
}

static int resume(struct platform_device *pdev)
{
	int ret = 0;
	struct atsc3_device *dev = platform_get_drvdata(pdev);
	struct te_device *tdev = get_te_device(dev);

	printk("ATSC3 - resume BEGIN\n");

	ret = atsc3_device_resume(dev);
	if (ret) {
		printk("ATSC3 - resume failed\n");
		goto exit;
	}

	printk("ATSC3 - resume OK\n");

exit:
	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_ATSC3);
	return ret;
}

static struct platform_driver platform_driver = {
	.probe = probe,
	.suspend = suspend,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 5, 0))
	.remove = remove,
#else
	.remove = legacy_remove,
#endif
	.resume = resume,
	.driver = {
		.name = ATSC3_DEVICE_NAME,
	},
};

int atsc3_module_init(void)
{
	int ret;

	init_logm();
	atsc3_cfg_init();

	ret = platform_driver_register(&platform_driver);
	if (ret) {
		log_error("[%s] platform driver register failed\n",
			  ATSC3_MODULE);
		return ret;
	}

	return 0;
}

void atsc3_module_exit(void)
{
	platform_driver_unregister(&platform_driver);
}

#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv", atsc3_module_init);
#else
module_init(atsc3_module_init);
#endif
module_exit(atsc3_module_exit);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION(ATSC3_DEVICE_NAME " driver");
MODULE_LICENSE("GPL");
#endif
