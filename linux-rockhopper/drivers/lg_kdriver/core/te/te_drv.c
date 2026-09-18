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
 *  @date		2015-02-27
 *  @note		Additional information.
 */

#include <linux/platform_device.h>
#include <linux/pm_runtime.h>

#include "base_device.h"
#include "te_impl.h"
#include "te_drv.h"

struct sub_module {
	const char *name;
	int (*init)(void);
	void (*exit)(void);
};

int g_te_debug_fd = -1;

// sub modules
int sdec_module_init(void);
int pvr_module_init(void);
int ciplus_module_init(void);
int atsc3_module_init(void);
int arib2_module_init(void);
int lxdvb_module_init(void);
int ci_module_init(void);
int sci_module_init(void);
int crypto_module_init(void);
int ci20_module_init(void);

void sdec_module_exit(void);
void pvr_module_exit(void);
void ciplus_module_exit(void);
void atsc3_module_exit(void);
void arib2_module_exit(void);
void lxdvb_module_exit(void);
void ci_module_exit(void);
void sci_module_exit(void);
void crypto_module_exit(void);
void ci20_module_exit(void);

static const struct sub_module sub_modules[] = {
#ifdef CONFIG_TE_CRYPTO
	{"CRYPTO", crypto_module_init, crypto_module_exit},
#endif
#ifdef INCLUDE_KDRV_SDEC
	{"SDEC", sdec_module_init, sdec_module_exit},
#endif
#ifdef INCLUDE_KDRV_PVR
	{"PVR", pvr_module_init, pvr_module_exit},
#endif
#ifdef INCLUDE_KDRV_SCI
	{"SCI", sci_module_init, sci_module_exit},
#endif
#ifdef INCLUDE_KDRV_CI
	{"CI", ci_module_init, ci_module_exit},
#endif
#ifdef INCLUDE_KDRV_CIPLUS
	{"CIPLUS", ciplus_module_init, ciplus_module_exit},
#endif
#ifdef INCLUDE_KDRV_ATSC3
	{"ATSC3", atsc3_module_init, atsc3_module_exit},
#endif
#ifdef INCLUDE_KDRV_ARIB2
	{"ARIB2", arib2_module_init, arib2_module_exit},
#endif
#ifdef INCLUDE_KDRV_CI20
	{"CI20", ci20_module_init, ci20_module_exit},
#endif
#ifdef CONFIG_TE_DVB
	{"DVB", lxdvb_module_init, lxdvb_module_exit},
#endif
};

static void init_logm(void)
{
	if (g_te_debug_fd == -1) {
		g_te_debug_fd = LOGM_ObjRegister(TE_MODULE);
		LOGM_ObjBitMaskEnable(g_te_debug_fd, LOG_LEVEL_ERROR);
		LOGM_ObjBitMaskEnable(g_te_debug_fd, LOG_LEVEL_WARNING);
		LOGM_ObjBitMaskEnable(g_te_debug_fd, LOG_LEVEL_NOTI);

		LOGM_ObjBitMaskEnable(g_te_debug_fd, LOG_LEVEL_MCU);

		LOGM_RegBitName(g_te_debug_fd, LOG_LEVEL_MEM, "MEM");
		LOGM_RegBitName(g_te_debug_fd, LOG_LEVEL_MCU, "MCU");
		LOGM_RegBitName(g_te_debug_fd, LOG_LEVEL_IPC, "IPC");
	}
}

static int init_sub_modules(struct platform_device *pdev)
{
	int i, rc;

	pm_runtime_get_sync(&pdev->dev);

	for (i = 0; i < ARRAY_SIZE(sub_modules); i++) {
		const struct sub_module *m = &sub_modules[i];

		rc = m->init();
		if (rc) {
			log_error("'%s' module init failed\n", m->name);
			pm_runtime_put_sync(&pdev->dev);
			return rc;
		}
	}

	pm_runtime_put_sync(&pdev->dev);

	return 0;
}

static void exit_sub_modules(void)
{
	int i;

	for (i = ARRAY_SIZE(sub_modules); i > 0; i--) {
		const struct sub_module *m = &sub_modules[i - 1];
		m->exit();
	}
}

static int suspend(struct device *dev)
{
	int ret;
	struct te_device *tdev = platform_get_drvdata(to_platform_device(dev));

	te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_TE);

	printk("TE - suspend BEGIN\n");

	ret = te_device_suspend(tdev);
	if (ret) {
		printk("TE - suspend failed\n");
		return ret;
	}

	printk("TE - suspend END\n");

	return 0;
}

static int resume(struct device *dev)
{
	int ret = 0;
	struct te_device *tdev = platform_get_drvdata(to_platform_device(dev));

	printk("TE - resume BEGIN\n");

	ret = te_device_resume(tdev);
	if (ret) {
		printk("TE - resume failed\n");
		goto exit;
	}

	printk("TE - resume OK\n");

exit:
	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_TE);
	return ret;
}

static int freeze(struct device *dev)
{
	return suspend(dev);
}

static int thaw(struct device *dev)
{
	return resume(dev);
}

static int restore(struct device *dev)
{
	return resume(dev);
}

static int runtime_suspend(struct device *dev)
{
	int ret;
	struct te_device *tdev = platform_get_drvdata(to_platform_device(dev));

	pmlog_info(tdev, 0, "suspend", "BEGIN");

	ret = te_clockgate_do_clockgate(tdev, true);
	if (ret) {
		pmlog_error(tdev, ret, "suspend", "clockgate failed");
		return ret;
	}

	pmlog_info(tdev, 0, "suspend", "END");
	return 0;
}

static int runtime_resume(struct device *dev)
{
	int ret;
	struct te_device *tdev = platform_get_drvdata(to_platform_device(dev));

	pmlog_info(tdev, 0, "resume", "BEGIN");

	ret = te_clockgate_do_clockgate(tdev, false);
	if (ret) {
		pmlog_error(tdev, ret, "resume", "clockgate failed");
		return ret;
	}

	pmlog_info(tdev, 0, "resume", "END");
	return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 2, 0))
static char *devnode_callback(const struct device *dev, umode_t *mode)
#else
static char *devnode_callback(struct device *dev, umode_t *mode)
#endif
{
	return kasprintf(GFP_KERNEL, "lg/%s", dev_name(dev));
}

static int register_dev_node(struct te_device *dev)
{
	int ret;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 9, 0))
	dev->class = class_create("te");
#else
	dev->class = class_create(THIS_MODULE, "te");
#endif
	if (IS_ERR(dev->class)) {
		log_error("class_create failed\n");
		return PTR_ERR(dev->class);
	}
	dev->class->devnode = devnode_callback;

	dev->devt = MKDEV(TE_MAJOR, 0);
	ret = register_chrdev_region(dev->devt, 1, TE_MODULE);
	CHECK_ERROR(ret, return ret, "Error(%d) in register_chrdev_region",
		    ret);

	/* initialize cdev structure with predefined variable */
	cdev_init(&dev->cdev, &te_dev_fops);
	dev->cdev.owner = THIS_MODULE;
	ret = cdev_add(&dev->cdev, dev->devt, 1);
	CHECK_ERROR(ret, return ret, "Error(%d) in cdev_add", ret);

	device_create(dev->class, NULL, dev->devt, dev, "%s0", TE_MODULE);

	return 0;
}

static void unregister_dev_node(struct te_device *dev)
{
	device_destroy(dev->class, dev->devt);

	cdev_del(&dev->cdev);
	unregister_chrdev_region(dev->devt, 1);
	class_destroy(dev->class);
}

static int probe(struct platform_device *pdev)
{
	int ret;
	struct te_device *dev;

	dev = devm_kzalloc(&pdev->dev, sizeof(*dev), GFP_KERNEL);
	CHECK_ERROR(!dev, goto error, "no memory");

	dev->pdev = pdev;

	platform_set_drvdata(pdev, dev);

	ret = te_device_init(dev);
	CHECK_ERROR(ret, goto error, "Error in te_device_init");

	ret = register_dev_node(dev);
	CHECK_ERROR(ret, goto error, "Error(%d) in register_dev_node", ret);

	return 0;
error:
	panic("te drv probe failed\n");
}

static void remove(struct platform_device *pdev)
{
	struct te_device *dev = platform_get_drvdata(pdev);

	unregister_dev_node(dev);
	te_device_release(dev);
}

#if (LINUX_VERSION_CODE < KERNEL_VERSION(6, 5, 0))
static int legacy_remove(struct platform_device *pdev)
{
	remove(pdev);
	return 0;
}
#endif

static struct dev_pm_ops pm_ops =
{
	.freeze = freeze,
	.thaw = thaw,
	.restore = restore,
	.suspend = suspend,
	.resume = resume,
	.runtime_suspend = runtime_suspend,
	.runtime_resume = runtime_resume,
};

static struct platform_driver te_pdrv = {
	.probe = probe,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 5, 0))
	.remove = remove,
#else
	.remove = legacy_remove,
#endif
	.driver = {
		.name = TE_DEVICE_NAME,
		.pm = &pm_ops,
	},
};

static int te_module_init(void)
{
	int ret;

	ret = platform_driver_register(&te_pdrv);
	if (ret) {
		log_error("[%s] platform driver register failed\n", TE_MODULE);
		return ret;
	}

	return 0;
}

static void te_module_exit(void)
{
	platform_driver_unregister(&te_pdrv);
}

/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and
 *	 memory size adjustment
 */
void TE_PreInit(void)
{
	init_logm();
	te_cfg_prepare();
}

int TE_Init(void)
{
	int ret;
	struct platform_device *pdev;

	pdev = te_register_devices();
	CHECK_ERROR(!pdev, goto error, "te_register_devices failed");

	ret = te_module_init();
	CHECK_ERROR(ret, goto error, "te_module_init failed(%d)", ret);

	ret = init_sub_modules(pdev);
	CHECK_ERROR(ret, goto error, "init_sub_modules failed(%d)", ret);

	return 0;
error:
	panic("TE_Init failed");
}

void TE_Cleanup(void)
{
	exit_sub_modules();
	te_module_exit();

	te_unregister_devices();
}

/** @} */
