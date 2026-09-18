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
 *  sdec device driver
 *
 *  author		ks.hyun(ks.hyunlge.com)
 *  version		1.0
 *  date		2018.10.29
 *  note		Additional information.
 *
 */

#include <linux/platform_device.h>

#include "base_device.h"
#include "sdec_impl.h"

int g_sdec_debug_fd = -1;

int sdec_module_init(void);
void sdec_module_exit(void);

static void init_logm(void)
{
	if (g_sdec_debug_fd == -1) {
		g_sdec_debug_fd = LOGM_ObjRegister(SDEC_MODULE);
		LOGM_ObjBitMaskEnable(g_sdec_debug_fd, LOG_LEVEL_ERROR);
		LOGM_ObjBitMaskEnable(g_sdec_debug_fd, LOG_LEVEL_WARNING);
		LOGM_ObjBitMaskEnable(g_sdec_debug_fd, LOG_LEVEL_NOTI);

		LOGM_RegBitName(g_sdec_debug_fd, LOG_LEVEL_TRACE_EX,
				"TRACE_EX");
		LOGM_RegBitName(g_sdec_debug_fd, LOG_LEVEL_NORMAL, "NORMAL");
		LOGM_RegBitName(g_sdec_debug_fd, LOG_LEVEL_READ, "READ");
		LOGM_RegBitName(g_sdec_debug_fd, LOG_LEVEL_ISR, "ISR");
		LOGM_RegBitName(g_sdec_debug_fd, LOG_LEVEL_IO, "IO");
		LOGM_RegBitName(g_sdec_debug_fd, LOG_LEVEL_FILTER, "FILTER");
		LOGM_RegBitName(g_sdec_debug_fd, LOG_LEVEL_PCR, "PCR");
		LOGM_RegBitName(g_sdec_debug_fd, LOG_LEVEL_DESC, "DESC");
		LOGM_RegBitName(g_sdec_debug_fd, LOG_LEVEL_MM, "MM");
		LOGM_RegBitName(g_sdec_debug_fd, LOG_LEVEL_CLOCK, "CLOCK");
	}
}

static int register_dev_node(struct sdec_device *dev)
{
	int ret, i;
	dev_t devt;
	struct te_device *tdev = get_te_device(dev);

	devt = MKDEV(SDEC_MAJOR, 0);
	ret = register_chrdev_region(devt, 1 + dev->num_channel, SDEC_MODULE);
	CHECK_ERROR(ret, return ret, "Error(%d) in register_chrdev_region",
		    ret);

	/* initialize cdev structure with predefined variable */
	cdev_init(&dev->cdev, &sdec_dev_fops);
	dev->cdev.owner = THIS_MODULE;
	ret = cdev_add(&dev->cdev, devt, 1 + dev->num_channel);
	CHECK_ERROR(ret, return ret, "Error(%d) in cdev_add", ret);

	te_class_device_create(tdev, devt, dev, "%s0", SDEC_MODULE);
	for (i = 0; i < dev->num_channel; i++) {
		te_class_device_create(tdev, MKDEV(SDEC_MAJOR, 1 + i),
				       &dev->channels[i], "%s0c%d", SDEC_MODULE,
				       i);
	}

	return 0;
}

static void unregister_dev_node(struct sdec_device *dev)
{
	int i;
	struct te_device *tdev = get_te_device(dev);

	for (i = 0; i < dev->num_channel; i++) {
		te_class_device_destroy(tdev, MKDEV(SDEC_MAJOR, 1 + i));
	}
	te_class_device_destroy(tdev, MKDEV(SDEC_MAJOR, 0));
	cdev_del(&dev->cdev);

	unregister_chrdev_region(MKDEV(SDEC_MAJOR, 0), 1 + dev->num_channel);
}

static int probe(struct platform_device *pdev)
{
	int ret;
	struct sdec_config *cfg;
	struct sdec_device *dev;

	cfg = sdec_get_config();

	dev = devm_kzalloc(&pdev->dev,
			   sizeof(struct sdec_device) +
			   cfg->num_channel * sizeof(struct sdec_channel),
			   GFP_KERNEL);
	CHECK_ERROR(!dev, goto error, "no memory");

	platform_set_drvdata(pdev, dev);

	te_register_subdev(&pdev->dev, &dev->subdev);

	dev->cfg = cfg;
	dev->num_channel = cfg->num_channel;

	ret = sdec_device_init(dev);
	CHECK_ERROR(ret, goto error, "Error(%d) in sdec_init_device", ret);

	ret = register_dev_node(dev);
	CHECK_ERROR(ret, goto error, "Error(%d) in register_dev_node", ret);

	log_noti("sdec probe done\n");

	return 0;
error:
	panic("sdec probe failed\n");
}

static void remove(struct platform_device *pdev)
{
	struct sdec_device *dev = platform_get_drvdata(pdev);

	unregister_dev_node(dev);
	sdec_device_release(dev);
	log_noti("sdec remove done\n");
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
	struct sdec_device *dev = platform_get_drvdata(pdev);
	struct te_device *tdev = get_te_device(dev);

	te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_SDEC);

	printk("SDEC - suspend BEGIN\n");

	ret = sdec_device_suspend(dev);
	if (ret) {
		printk("SDEC - suspend failed\n");
		return ret;
	}

	printk("SDEC - suspend END\n");

	return 0;
}

static int resume(struct platform_device *pdev)
{
	int ret = 0;
	struct sdec_device *dev = platform_get_drvdata(pdev);
	struct te_device *tdev = get_te_device(dev);

	printk("SDEC - resume BEGIN\n");

	ret = sdec_device_resume(dev);
	if (ret) {
		printk("SDEC - resume failed\n");
		goto exit;
	}

	printk("SDEC - resume OK\n");

exit:
	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_SDEC);
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
		   .name = SDEC_DEVICE_NAME,
		   },
};

int sdec_module_init(void)
{
	int ret;

	init_logm();
	sdec_cfg_init();

	ret = platform_driver_register(&platform_driver);
	if (ret) {
		log_error("[%s] platform driver register failed\n",
			  SDEC_MODULE);
		return ret;
	}

	return 0;
}

void sdec_module_exit(void)
{
	platform_driver_unregister(&platform_driver);
}

#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv", sdec_module_init);
#else
module_init(sdec_module_init);
#endif
module_exit(sdec_module_exit);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION(SDEC_DEVICE_NAME " driver");
MODULE_LICENSE("GPL");
#endif

/** @} */
