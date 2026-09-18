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
 *  arib2 driver
 *
 *  @author		Yeonju Lee (yeonju.lee@lge.com)
 *  @version		1.0
 *  @date		2017-11-21
 *  @note		Additional information.
 */

#include <linux/platform_device.h>

#include "base_device.h"
#include "arib2_impl.h"

int g_arib2_debug_fd = -1;

int arib2_module_init(void);
void arib2_module_exit(void);

static void init_logm(void)
{
	if (g_arib2_debug_fd != -1)
		return;

	g_arib2_debug_fd = LOGM_ObjRegister(ARIB2_MODULE);
	LOGM_ObjBitMaskEnable(g_arib2_debug_fd, LOG_LEVEL_ERROR);
	LOGM_ObjBitMaskEnable(g_arib2_debug_fd, LOG_LEVEL_WARNING);
	LOGM_ObjBitMaskEnable(g_arib2_debug_fd, LOG_LEVEL_NOTI);

	LOGM_RegBitName(g_arib2_debug_fd, LOG_LEVEL_TRACE_EX, "TRACE_EX");
	LOGM_RegBitName(g_arib2_debug_fd, LOG_LEVEL_FILTER, "FILTER");
	LOGM_RegBitName(g_arib2_debug_fd, LOG_LEVEL_IO, "IO");
	LOGM_RegBitName(g_arib2_debug_fd, LOG_LEVEL_CLOCK, "CLOCK");
}

static int register_dev_node(struct arib2_device *dev)
{
	int ret, i;
	dev_t devt;
	struct te_device *tdev = get_te_device(dev);

	devt = MKDEV(ARIB2_MAJOR, 0);
	ret = register_chrdev_region(devt, 1 + dev->num_channel, ARIB2_MODULE);
	CHECK_ERROR(ret, return ret, "Error(%d) in register_chrdev_region",
		    ret);

	/* initialize cdev structure with predefined variable */
	cdev_init(&dev->cdev, &arib2_dev_fops);
	dev->cdev.owner = THIS_MODULE;
	ret = cdev_add(&dev->cdev, devt, 1 + dev->num_channel);
	CHECK_ERROR(ret, return ret, "Error(%d) in cdev_add", ret);

	te_class_device_create(tdev, devt, dev, "%s", ARIB2_MODULE);
	for (i = 0; i < dev->num_channel; i++) {
		te_class_device_create(tdev, MKDEV(ARIB2_MAJOR, 1 + i),
				       &dev->channels[i], "%sc%d", ARIB2_MODULE,
				       i);
	}

	return 0;
}

static void unregister_dev_node(struct arib2_device *dev)
{
	int i;
	struct te_device *tdev = get_te_device(dev);

	for (i = 0; i < dev->num_channel; i++) {
		te_class_device_destroy(tdev, MKDEV(ARIB2_MAJOR, 1 + i));
	}
	te_class_device_destroy(tdev, MKDEV(ARIB2_MAJOR, 0));
	cdev_del(&dev->cdev);

	unregister_chrdev_region(MKDEV(ARIB2_MAJOR, 0), 1 + dev->num_channel);
}

static int probe(struct platform_device *pdev)
{
	int ret;
	struct arib2_config *cfg;
	struct arib2_device *dev;

	cfg = arib2_get_config();
	dev = devm_kzalloc(&pdev->dev,
			   sizeof(struct arib2_device) +
			   cfg->num_ch * sizeof(struct arib2_channel),
			   GFP_KERNEL);
	CHECK_ERROR(!dev, goto error, "no memory");

	platform_set_drvdata(pdev, dev);
	te_register_subdev(&pdev->dev, &dev->subdev);

	dev->cfg = cfg;
	dev->num_channel = cfg->num_ch;
	dev->use_swtlv = cfg->swtlv;
	mutex_init(&dev->mutex);

	ret = arib2_dev_init(dev);
	CHECK_ERROR(ret, goto error, "Error(%d) in arib2_dev_init", ret);

	ret = register_dev_node(dev);
	CHECK_ERROR(ret, goto error, "Error(%d) in register_dev_node", ret);

	log_noti("arib2 probe done\n");

	return 0;
error:
	panic("arib2 probe failed\n");
}

static void remove(struct platform_device *pdev)
{
	struct arib2_device *dev = platform_get_drvdata(pdev);

	unregister_dev_node(dev);

	arib2_dev_release(dev);

	log_noti("arib2 remove done\n");
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
	struct arib2_device *dev = platform_get_drvdata(pdev);
	struct te_device *tdev = get_te_device(dev);

	te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_ARIB2);

	printk("ARIB2 - suspend BEGIN\n");

	ret = arib2_dev_suspend(dev);
	if (ret) {
		printk("ARIB2 - suspend failed\n");
		return ret;
	}

	printk("ARIB2 - suspend END\n");

	return 0;
}

static int resume(struct platform_device *pdev)
{
	int ret = 0;
	struct arib2_device *dev = platform_get_drvdata(pdev);
	struct te_device *tdev = get_te_device(dev);

	printk("ARIB2 - resume BEGIN\n");

	ret = arib2_dev_resume(dev);
	if (ret) {
		printk("ARIB2 - resume failed\n");
		goto exit;
	}

	printk("ARIB2 - resume OK\n");

exit:
	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_ARIB2);
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
		.name = ARIB2_DEVICE_NAME,
	},
};

int arib2_module_init(void)
{
	int ret;

	init_logm();
	arib2_cfg_init();

	ret = platform_driver_register(&platform_driver);
	if (ret) {
		log_error("[%s] platform driver register failed\n",
			  ARIB2_MODULE);
		return ret;
	}

	return 0;
}

void arib2_module_exit(void)
{
	platform_driver_unregister(&platform_driver);
}

#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv", arib2_module_init);
#else
module_init(arib2_module_init);
#endif
module_exit(arib2_module_exit);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION(ARIB2_DEVICE_NAME " driver");
MODULE_LICENSE("GPL");
#endif
