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
 *  CIPLUS Driver
 *
 *  @author	Ilkyu Kim (ilkyu.kim@lge.com)
 *  @version	1.0
 *  @date		2015-06-03
 *  @note		Additional information.
 */

#include <linux/platform_device.h>

#include "base_device.h"
#include "ciplus_impl.h"

int g_ciplus_debug_fd = -1;

int ciplus_module_init(void);
void ciplus_module_exit(void);

static void init_logm(void)
{
	g_ciplus_debug_fd = LOGM_ObjRegister(CIPLUS_MODULE);
	LOGM_ObjBitMaskEnable(g_ciplus_debug_fd, LOG_LEVEL_ERROR);
	LOGM_ObjBitMaskEnable(g_ciplus_debug_fd, LOG_LEVEL_WARNING);
	LOGM_ObjBitMaskEnable(g_ciplus_debug_fd, LOG_LEVEL_NOTI);
}

static int register_dev_node(struct ciplus_device *dev)
{
	int ret, i;
	dev_t devt;
	struct te_device *tdev = get_te_device(dev);

	devt = MKDEV(CIPLUS_MAJOR, 0);
	ret = register_chrdev_region(devt, 1 + dev->num_channel, CIPLUS_MODULE);
	CHECK_ERROR(ret, return ret, "Error:%d in register_chrdev_region", ret);

	/* initialize cdev structure with predefined variable */
	cdev_init(&dev->cdev, &ciplus_dev_fops);
	dev->cdev.owner = THIS_MODULE;
	ret = cdev_add(&dev->cdev, devt, 1 + dev->num_channel);
	CHECK_ERROR(ret, return ret, "Error(%d) in cdev_add", ret);

	te_class_device_create(tdev, devt, dev, "%s0", CIPLUS_MODULE);
	for (i = 0; i < dev->num_channel; i++) {
		te_class_device_create(tdev, MKDEV(CIPLUS_MAJOR, 1 + i),
				       &dev->channels[i], "%s0c%d",
				       CIPLUS_MODULE, i);
	}

	return 0;
}

static void unregister_dev_node(struct ciplus_device *dev)
{
	int i;
	struct te_device *tdev = get_te_device(dev);

	for (i = 0; i < dev->num_channel; i++) {
		te_class_device_destroy(tdev, MKDEV(CIPLUS_MAJOR, 1 + i));
	}
	te_class_device_destroy(tdev, MKDEV(CIPLUS_MAJOR, 0));
	cdev_del(&dev->cdev);

	unregister_chrdev_region(MKDEV(CIPLUS_MAJOR, 0), 1 + dev->num_channel);
}

static int probe(struct platform_device *pdev)
{
	int ret, size;
	struct ciplus_config *cfg;
	struct ciplus_device *dev;

	cfg = ciplus_get_config();

	size = sizeof(*dev) + cfg->num_ch * sizeof(struct ciplus_channel);
	dev = devm_kzalloc(&pdev->dev, size, GFP_KERNEL);
	CHECK_ERROR(!dev, goto error, "no memory");

	platform_set_drvdata(pdev, dev);
	te_register_subdev(&pdev->dev, &dev->subdev);

	dev->cfg = cfg;
	dev->num_channel = cfg->num_ch;

	ret = ciplus_device_init(dev);
	CHECK_ERROR(ret, goto error, "Error(%d) in ciplus_device_init", ret);

	ret = register_dev_node(dev);
	CHECK_ERROR(ret, goto error, "Error(%d) in register_dev_node", ret);

	log_noti("ciplus probe done\n");

	return 0;
error:
	panic("ciplus probe failed\n");
}

static void remove(struct platform_device *pdev)
{
	struct ciplus_device *dev = platform_get_drvdata(pdev);

	unregister_dev_node(dev);

	ciplus_device_release(dev);

	log_noti("ciplus remove done\n");
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
	struct ciplus_device *dev = platform_get_drvdata(pdev);
	struct te_device *tdev = get_te_device(dev);

	te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_CI14);

	printk("CIPLUS - suspend BEGIN\n");

	ret = ciplus_device_suspend(dev);
	if (ret) {
		printk("CIPLUS - suspend failed\n");
		return ret;
	}

	printk("CIPLUS - suspend END\n");

	return 0;
}

static int resume(struct platform_device *pdev)
{
	int ret = 0;
	struct ciplus_device *dev = platform_get_drvdata(pdev);
	struct te_device *tdev = get_te_device(dev);

	printk("CIPLUS - resume BEGIN\n");

	ret = ciplus_device_resume(dev);
	if (ret) {
		printk("CIPLUS - resume failed\n");
		goto exit;
	}

	printk("CIPLUS - resume OK\n");

exit:
	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_CI14);
	return ret;
}

/*
 *	module platform driver structure
 */
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
		.name = CIPLUS_DEVICE_NAME,
	},
};

int ciplus_module_init(void)
{
	int ret;

	init_logm();
	ciplus_cfg_init();

	ret = platform_driver_register(&platform_driver);
	if (ret) {
		log_error("%s platform driver register failed:%d\n",
			  CIPLUS_MODULE, ret);
		return ret;
	}

	return 0;
}

void ciplus_module_exit(void)
{
	platform_driver_unregister(&platform_driver);
}

#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv", ciplus_module_init);
#else
module_init(ciplus_module_init);
#endif
module_exit(ciplus_module_exit);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION(CIPLUS_DEVICE_NAME " driver");
MODULE_LICENSE("GPL");
#endif

/** @} */
