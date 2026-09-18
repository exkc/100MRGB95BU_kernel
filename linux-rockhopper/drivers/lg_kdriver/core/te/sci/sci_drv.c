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
 *  sci device driver
 *
 *  author		yeonju.lee (yeonju.lee@lge.com)
 *  version		1.0
 *  date		2019.04.22
 *  note		Additional information.
 *
 */

#include <linux/platform_device.h>

#include "base_device.h"
#include "sci_impl.h"
#include "sci_reg.h"

int g_sci_debug_fd = -1;

int sci_module_init(void);
void sci_module_exit(void);

static void init_logm(void)
{
	if (g_sci_debug_fd == -1) {
		g_sci_debug_fd = LOGM_ObjRegister(SCI_MODULE);
		LOGM_ObjBitMaskEnable(g_sci_debug_fd, LX_LOGM_LEVEL_ERROR);
		LOGM_ObjBitMaskEnable(g_sci_debug_fd, LX_LOGM_LEVEL_WARNING);
		LOGM_ObjBitMaskEnable(g_sci_debug_fd, LX_LOGM_LEVEL_NOTI);
	}
}

int sci_close(struct sci_dev *dev)
{
	if (dev->open_count) {
		dev->open_count--;
		if (!dev->open_count) {
			sci_deactivate(dev);
		}
	} else {
		log_noti("device is not opened");
	}

	log_noti("%s(%d) DONE", __func__, dev->open_count);

	return 0;
}

int sci_open(struct sci_dev *dev)
{
	if (dev->open_count == 0) {
		sci_ctop_select_smartcard();
		sci_ctop_external_inputmode();
	}

	dev->open_count++;

	log_noti("%s(%d) DONE", __func__, dev->open_count);

	return 0;
}

static int dev_init(struct sci_dev *dev)
{
	int rc;
	u32 clk;

	log_noti("sci_dev_init");

	spin_lock_init(&dev->lock);
	mutex_init(&dev->mutex);
	init_waitqueue_head(&dev->wq);

	dev->phase = SCI_PHASE_IDLE;

	sci_ctop_set_clock();

	clk = sci_ctop_get_clock();
	CHECK_ERROR(!clk, return -EIO, "clk is not set(un-known chip rev)");

	dev->clock_supplied_khz = clk;

	rc = sci_reg_init();
	CHECK_ERROR(rc, return rc, "sci_reg_init error(%d)", rc);

	sci_reg_set_default_value();

	rc = sci_isr_init(dev);
	CHECK_ERROR(rc, return rc, "sci_isr_init error(%d)", rc);

	rc = sci_debug_init(dev);
	CHECK_ERROR(rc, return rc, "sci_debug_init error(%d)", rc);

	log_noti("sci_dev_init done\n");

	return 0;
}

static int probe(struct platform_device *pdev)
{
	struct sci_dev *dev;
	int ret;

	log_noti("sci_probe");

	dev = devm_kzalloc(&pdev->dev, sizeof(struct sci_dev), GFP_KERNEL);
	CHECK_ERROR(!dev, goto error, "no memory");

	platform_set_drvdata(pdev, dev);

	te_register_subdev(&pdev->dev, &dev->subdev);

	ret = dev_init(dev);
	CHECK_ERROR(ret, goto error, "dev init failed");

	log_noti("sci_probe done\n");

	return 0;
error:
	panic("sci_probe failed\n");
}

static void remove(struct platform_device *pdev)
{
	struct sci_dev *dev = platform_get_drvdata(pdev);

	log_noti("sci_remove\n");

	sci_debug_release(dev);
	sci_isr_cleanup(dev);
	sci_reg_cleanup();

	log_noti("sci_remove done\n");
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
	return 0;
}

static int resume(struct platform_device *pdev)
{
	struct sci_dev *dev = platform_get_drvdata(pdev);

	printk("SCI - resume BEGIN\n");

	sci_ctop_set_clock();
	if (dev->open_count) {
		sci_ctop_select_smartcard();
		sci_ctop_external_inputmode();
	}

	sci_reg_set_default_value();

	dev->phase = SCI_PHASE_IDLE;

	printk("SCI - resume OK\n");

	return 0;
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
		.name = SCI_DEVICE_NAME,
	},
};

int sci_module_init(void)
{
	int ret;

	init_logm();
	sci_cfg_init();

	log_noti("%s", __func__);

	ret = platform_driver_register(&platform_driver);
	if (ret) {
		log_error("[%s] platform driver register failed\n", SCI_MODULE);
		return ret;
	}

	return 0;
}

void sci_module_exit(void)
{
	platform_driver_unregister(&platform_driver);

}

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv", sci_module_init);
#else
module_init(sci_module_init);
#endif
module_exit(sci_module_exit);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("SCI driver");
MODULE_LICENSE("GPL");
#endif

/** @} */
