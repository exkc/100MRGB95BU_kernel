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
 *  TE crypto device driver
 *
 *  author	Kyungseok Hyun (ks.hyun@lge.com)
 *  version	1.0
 *  date	2020.01.07
 *  note
 *
 */

#include <linux/platform_device.h>

#include "base_device.h"
#include "crypto_impl.h"

int crypto_module_init(void);
void crypto_module_exit(void);

int g_crypto_logm_fd = -1;

static void init_logm(void)
{
	if (g_crypto_logm_fd == -1) {
		g_crypto_logm_fd = LOGM_ObjRegister(CRYPTO_MODULE);
		LOGM_ObjBitMaskEnable(g_crypto_logm_fd, LX_LOGM_LEVEL_ERROR);
		LOGM_ObjBitMaskEnable(g_crypto_logm_fd, LX_LOGM_LEVEL_WARNING);
		LOGM_ObjBitMaskEnable(g_crypto_logm_fd, LX_LOGM_LEVEL_NOTI);
	}
}

static int register_dev_node(struct te_crypto_device *dev)
{
	int ret, i;
	dev_t devt;
	struct te_device *tdev = get_te_device(dev);

	devt = MKDEV(CRYPTO_MAJOR, 0);
	ret = register_chrdev_region(devt, dev->num_channel, CRYPTO_MODULE);
	CHECK_ERROR(ret, return ret, "register_chrdev_region failed(%d)", ret);

	/* initialize cdev structure with predefined variable */
	cdev_init(&dev->cdev, &crypto_dev_fops);
	dev->cdev.owner = THIS_MODULE;
	ret = cdev_add(&dev->cdev, devt, dev->num_channel);
	CHECK_ERROR(ret, return ret, "cdev_add failed(%d)", ret);

	for (i = 0; i < dev->num_channel; i++) {
		te_class_device_create(tdev, MKDEV(CRYPTO_MAJOR, i),
				       &dev->channels[i], "%s%d",
				       CRYPTO_MODULE, i);
	}

	return 0;
}

static void unregister_dev_node(struct te_crypto_device *dev)
{
	int i;
	struct te_device *tdev = get_te_device(dev);

	for (i = 0; i < dev->num_channel; i++) {
		te_class_device_destroy(tdev, MKDEV(CRYPTO_MAJOR, i));
	}
	cdev_del(&dev->cdev);
	unregister_chrdev_region(MKDEV(CRYPTO_MAJOR, 0), dev->num_channel);
}

static int probe(struct platform_device *pdev)
{
	int ret;
	struct te_crypto_device *dev;
	struct te_config *cfg = te_get_config();
	u8 num_channel;

	if (cfg->num_dsc < 2)
		return -ENODEV;

	num_channel = cfg->num_dsc - 1;

	dev = devm_kzalloc(&pdev->dev,
			   sizeof(struct te_crypto_device) +
			   (num_channel * sizeof(struct te_crypto_channel)),
			   GFP_KERNEL);
	CHECK_ERROR(!dev, goto error, "no memory");

	platform_set_drvdata(pdev, dev);
	te_register_subdev(&pdev->dev, &dev->subdev);

	dev->num_channel = num_channel;

	ret = crypto_device_init(dev);
	CHECK_ERROR(ret, goto error, "crypto_device_init failed(%d)", ret);

	ret = register_dev_node(dev);
	CHECK_ERROR(ret, goto error, "register_dev_node failed(%d)", ret);

	log_noti("crypto probe done\n");

	return 0;
error:
	panic("crypto probe failed\n");
}

static void remove(struct platform_device *pdev)
{
	struct te_crypto_device *dev = platform_get_drvdata(pdev);

	unregister_dev_node(dev);
	crypto_device_release(dev);

	log_noti("crypto remove done\n");
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
	struct te_crypto_device *dev = platform_get_drvdata(pdev);
	struct te_device *tdev = get_te_device(dev);

	te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_CRYPTO);

	printk("CRYPTO - suspend BEGIN\n");

	ret = crypto_device_suspend(dev);
	if (ret) {
		printk("CRYPTO - suspend failed\n");
		return ret;
	}

	printk("CRYPTO - suspend END\n");

	return 0;
}

static int resume(struct platform_device *pdev)
{
	int ret = 0;
	struct te_crypto_device *dev = platform_get_drvdata(pdev);
	struct te_device *tdev = get_te_device(dev);

	printk("CRYPTO - resume BEGIN\n");

	ret = crypto_device_resume(dev);
	if (ret) {
		printk("CRYPTO - resume failed\n");
		goto exit;
	}

	printk("CRYPTO - resume OK\n");

exit:
	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_CRYPTO);
	return 0;
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
		.name = CRYPTO_DEVICE_NAME,
	},
};

int crypto_module_init(void)
{
	int ret;
	struct te_config *cfg = te_get_config();

	// TODO: add configuration if necessary, now we just use te_cofnig

	// only support DSC1(DSC0 for MCU)
	if (cfg->num_dsc < 2)
		return 0;

	init_logm();

	ret = platform_driver_register(&platform_driver);
	if (ret) {
		log_error("platform_driver_register failed(%d)", ret);
		return ret;
	}

	return 0;
}

void crypto_module_exit(void)
{
	struct te_config *cfg = te_get_config();

	if (cfg->num_dsc < 2)
		return;

	platform_driver_unregister(&platform_driver);
}

#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv", crypto_module_init);
#else
module_init(crypto_module_init);
#endif
module_exit(crypto_module_exit);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION(CRYPTO_DEVICE_NAME " driver");
MODULE_LICENSE("GPL");
#endif

/** @} */
