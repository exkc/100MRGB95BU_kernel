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
 *  pvr device driver
 *
 *  author		ks.hyun(ks.hyunlge.com)
 *  version		1.0
 *  date		2018.10.29
 *  note		Additional information.
 *
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/platform_device.h>
#include <linux/freezer.h>

#include "base_device.h"
#include "pvr_impl.h"

#define inode_to_pvr_device(inode) \
	container_of(inode->i_cdev, struct pvr_device, cdev)

int pvr_module_init(void);
void pvr_module_exit(void);

int g_pvr_debug_fd = -1;

static DEFINE_MUTEX(node_lock);

static void init_logm(void)
{
	if (g_pvr_debug_fd == -1) {
		g_pvr_debug_fd = LOGM_ObjRegister(PVR_MODULE);

		LOGM_ObjBitMaskEnable(g_pvr_debug_fd, LOG_LEVEL_ERROR);
		LOGM_ObjBitMaskEnable(g_pvr_debug_fd, LOG_LEVEL_WARNING);
		LOGM_ObjBitMaskEnable(g_pvr_debug_fd, LOG_LEVEL_NOTI);

		LOGM_RegBitName(g_pvr_debug_fd, LOG_LEVEL_TRACE_EX, "TRACE_EX");
		LOGM_RegBitName(g_pvr_debug_fd, LOG_LEVEL_DRV, "DRV");
		LOGM_RegBitName(g_pvr_debug_fd, LOG_LEVEL_NORMAL, "NORMAL");
		LOGM_RegBitName(g_pvr_debug_fd, LOG_LEVEL_ISR, "ISR");
		LOGM_RegBitName(g_pvr_debug_fd, LOG_LEVEL_UPLOAD, "UPLOAD");
		LOGM_RegBitName(g_pvr_debug_fd, LOG_LEVEL_PIE, "PIE");
		LOGM_RegBitName(g_pvr_debug_fd, LOG_LEVEL_REG, "REG");
		LOGM_RegBitName(g_pvr_debug_fd, LOG_LEVEL_REG_EX, "REG_EX");
	}
}

/**
 * open handler for pvr device
 *
 */
static int open(struct inode *inode, struct file *file)
{
	int ret;
	u8 idx;
	struct pvr_fh *fh;
	struct pvr_node *node;
	enum pvr_dev_type type;
	struct pvr_device *dev = inode_to_pvr_device(inode);
	struct te_device *tdev = get_te_device(dev);
	unsigned minor = iminor(inode);

	if (minor == 0) {
		type = PVR_DEV_TYPE_CORE;
		idx = 0;
	} else if (minor < (1 + PVR_UP_MAX)) {
		type = PVR_DEV_TYPE_UP;
		idx = minor - 1;
	} else if (minor < (1 + PVR_UP_MAX + PVR_DN_MAX)) {
		type = PVR_DEV_TYPE_DN;
		idx = minor - PVR_UP_MAX - 1;
	} else {
		log_error("invalid node(%d)\n", minor);
		return -ENODEV;
	}

	fh = kzalloc(sizeof(*fh), GFP_KERNEL);
	if (!fh)
		return -ENOMEM;

	node = dev->node[type];

	fh->dev = dev;
	fh->node = node;
	fh->idx = idx;

	mutex_lock(&node_lock);

	te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_PVR);

	ret = node->open(fh);
	if (ret) {
		te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_PVR);
		mutex_unlock(&node_lock);
		kfree(fh);
		return ret;
	}
	node->users++;

	log_noti("%s (%d:%d) - users:%d\n", __func__, imajor(inode),
		 iminor(inode), node->users);

	mutex_unlock(&node_lock);

	file->private_data = fh;

	return 0;
}

/**
 * release handler for pvr device
 *
 */
static int close(struct inode *inode, struct file *file)
{
	struct pvr_fh *fh = file->private_data;
	struct pvr_node *node = fh->node;
	struct te_device *tdev = get_te_device(inode_to_pvr_device(inode));

	mutex_lock(&node_lock);

	node->users--;

	node->close(fh);

	log_noti("%s (%d:%d) - users:%d", __func__, imajor(inode),
		 iminor(inode), node->users);

	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_PVR);

	mutex_unlock(&node_lock);

	kfree(fh);

	return 0;
}

static long ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int ret;
	struct pvr_fh *fh = file->private_data;
	struct pvr_node *node = fh->node;

	ret = te_ioctl_usercopy(cmd, arg, node->ioctl, node->ioctl_param, fh);

	return ret;
}

static int mmap(struct file *file, struct vm_area_struct *vma)
{
	return te_user_mmap(vma, file->f_flags & O_DSYNC);
}

static struct file_operations fops = {
	.open = open,
	.release = close,
	.unlocked_ioctl = ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = ioctl,
#endif
	.mmap = mmap,
};

static int register_dev_node(struct pvr_device *dev)
{
	int ret, i;
	struct te_device *tdev = get_te_device(dev);
	dev_t devt = MKDEV(PVR_MAJOR, 0);
	int num_node = 1 + PVR_UP_MAX + PVR_DN_MAX;

	ret = register_chrdev_region(devt, num_node, PVR_MODULE);
	CHECK_ERROR(ret, return ret, "Err in register_chrdev_region");

	/* initialize cdev structure with predefined variable */
	cdev_init(&dev->cdev, &fops);
	dev->cdev.owner = THIS_MODULE;
	ret = cdev_add(&dev->cdev, devt, num_node);
	CHECK_ERROR(ret, return ret, "Err in cdev_add");

	/* core device node */
	te_class_device_create(tdev, devt, dev, "%s0", PVR_MODULE);

	/* upload device node */
	for (i = 0; i < PVR_UP_MAX; i++) {
		devt = MKDEV(PVR_MAJOR, 1 + i);
		te_class_device_create(tdev, devt, dev,
				       "%s0up%d", PVR_MODULE, i);
	}

	/* download device node */
	for (i = 0; i < PVR_DN_MAX; i++) {
		devt = MKDEV(PVR_MAJOR, 1 + PVR_UP_MAX + i);
		te_class_device_create(tdev, devt, dev,
				       "%s0dn%d", PVR_MODULE, i);
	}

	return 0;
}

static void unregister_dev_node(struct pvr_device *dev)
{
	int i;
	struct te_device *tdev = get_te_device(dev);
	int num_node = 1 + PVR_UP_MAX + PVR_DN_MAX;

	for (i = 0; i < num_node; i++)
		te_class_device_destroy(tdev, MKDEV(PVR_MAJOR, i));

	cdev_del(&dev->cdev);
	unregister_chrdev_region(MKDEV(PVR_MAJOR, 0), num_node);
}

static int probe(struct platform_device *pdev)
{
	int ret;
	struct pvr_config *cfg;
	struct pvr_device *dev;

	cfg = pvr_get_config();
	dev = devm_kzalloc(&pdev->dev, sizeof(struct pvr_device), GFP_KERNEL);
	CHECK_ERROR(!dev, goto error, "no memory");

	platform_set_drvdata(pdev, dev);

	te_register_subdev(&pdev->dev, &dev->subdev);

	dev->cfg = cfg;
	dev->num_up = (cfg->num_up < PVR_UP_MAX) ? cfg->num_up : PVR_UP_MAX;
	dev->num_dn = (cfg->num_dn < PVR_DN_MAX) ? cfg->num_dn : PVR_DN_MAX;

	ret = pvr_device_init(dev);
	CHECK_ERROR(ret, goto error, "Error in pvr_device_init");

	ret = register_dev_node(dev);
	CHECK_ERROR(ret, goto error, "Error(%d) in register_dev_node", ret);

	log_noti("pvr probe done\n");

	return 0;
error:
	panic("pvr probe failed\n");
}

static void remove(struct platform_device *pdev)
{
	struct pvr_device *dev = platform_get_drvdata(pdev);

	unregister_dev_node(dev);
	pvr_device_release(dev);

	log_trace("pvr remove done\n");
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
	struct pvr_device *dev = platform_get_drvdata(pdev);
	struct te_device *tdev = get_te_device(dev);

	te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_PVR);

	printk("PVR - suspend BEGIN\n");

	ret = pvr_device_suspend(dev);
	if (ret) {
		printk("PVR - suspend failed\n");
		return ret;
	}

	printk("PVR - suspend OK\n");

	return 0;
}

static int resume(struct platform_device *pdev)
{
	int ret = 0;
	struct pvr_device *dev = platform_get_drvdata(pdev);
	struct te_device *tdev = get_te_device(dev);

	printk("PVR - resume BEGIN\n");

	ret = pvr_device_resume(dev);
	if (ret) {
		printk("PVR - resume failed\n");
		goto exit;
	}

	printk("PVR - resume OK\n");

exit:
	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_PVR);
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
		.name = PVR_DEVICE_NAME,
	},
};

int pvr_module_init(void)
{
	int ret;

	init_logm();
	pvr_cfg_init();

	ret = platform_driver_register(&platform_driver);
	if (ret) {
		log_error("[%s] platform driver register failed\n", PVR_MODULE);
		return ret;
	}

	return 0;
}

void pvr_module_exit(void)
{
	platform_driver_unregister(&platform_driver);
}

#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv", pvr_module_init);
#else
module_init(pvr_module_init);
#endif
module_exit(pvr_module_exit);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION(PVR_DEVICE_NAME " driver");
MODULE_LICENSE("GPL");
#endif

/** @} */
