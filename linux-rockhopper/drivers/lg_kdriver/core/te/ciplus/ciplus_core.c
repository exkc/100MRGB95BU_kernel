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
 *  ciplus driver core functions
 *
 *  @author Ilkyu Kim ( ilkyukim@lge.com)
 *  @version	0.1
 *  @date		2015-07-07
 *  @note		Additional information.
 */

#include <linux/mm.h>

#include "ciplus_impl.h"

#define inode_to_ciplus_device(inode) \
	container_of(inode->i_cdev, struct ciplus_device, cdev)

#define inode_to_ciplus_channel(dev,inode) \
({ \
	unsigned __n = iminor(inode); \
	__n ? &dev->channels[__n-1] : NULL; \
})

static DEFINE_MUTEX(node_lock);

static const struct ciplus_sub_driver *sub_drivers[] = {
	&ciplus_debug_driver,
	&ciplus_mem_driver,
	&ciplus_io_driver,
	&ciplus_pidf_driver,
	&ciplus_ipd_driver,
	&ciplus_isr_driver,
};

struct ciplus_device *ciplus_get_device(struct te_device *dev)
{
	struct te_subdev *sd;

	sd = te_get_subdev(dev, CIPLUS_DEVICE_NAME);
	if (!sd)
		return NULL;

	return te_subdev_to_ciplus_device(sd);
}

struct ciplus_channel *ciplus_get_channel(struct ciplus_device *dev, u8 num)
{
	return num < dev->num_channel ? &dev->channels[num] : NULL;
}


int ciplus_get_channel_info(struct ciplus_device *dev,
			    int *num_ch, int *num_pidf)
{
	struct ciplus_config *cfg = ciplus_get_config();

	if (!cfg)
		return -EFAULT;

	*num_ch = cfg->num_ch;
	*num_pidf = cfg->num_pidf;

	return 0;
}

struct te_mem_ctx *ciplus_get_mem_ctx(struct ciplus_device *dev)
{
	return dev->mem;
}

static int init_hw(void)
{
	log_noti("init_hw");

	/* Set CIOUT Clock to 12.375 Mhz */
	TE_REG_SetCiOutClk(OUTPUT_CLK_12MHZ);

	/* Set Endian Type (default: byte swap) */
	TE_REG_SetCiplusEndian(CIP_ENDIAN_BYTESWAP);
	TE_REG_SetCiplusOutbufFullLevel(0x7);
	TE_REG_SetCiplusOutbufSource(CIP_SRC_DEMOD);
	TE_REG_SetCiplusOutbufDestination(CIP_INPUT_DEST_HW);
	TE_REG_ResetCiplusOutbuf();

	log_noti("HW Init Done");

	return 0;
}

static int get_chip_config(LX_CIPLUS_CHIP_CFG_T *chip_cfg)
{
	struct ciplus_config *conf = ciplus_get_config();

	chip_cfg->num_ch = conf->num_ch;
	chip_cfg->num_pidf = conf->num_pidf;
	chip_cfg->use_cinport = conf->use_cinport;

	return 0;
}

static int core_ioctl(void *priv, unsigned int cmd, void *arg)
{
	int ret;
	struct ciplus_fh *fh = priv;
	struct ciplus_device *dev = fh->dev;

	mutex_lock(&dev->mutex);

	switch (cmd) {
	case CIPLUS_CORE_INIT:
		//ret = CIPLUS_InitDevice();
		ret = 0;
		break;

	case CIPLUS_CORE_GET_CHIPCFG:
		ret = get_chip_config(arg);
		break;

	case CIPLUS_CORE_GET_BASEADDRESS:
		log_error("not supported anymore");
		ret = -EPERM;
		break;

	default:
		log_error("invalid command[0x%08x]. magic=0x%02X, num=%d",
			  cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));
		ret = -ENOTTY;
		break;
	}

	mutex_unlock(&dev->mutex);

	return ret;
}

static int sub_device_open(struct ciplus_fh *fh)
{
	int i, j, ret;
	const struct ciplus_sub_driver *s;

	for (i = 0; i < ARRAY_SIZE(sub_drivers); i++) {
		s = sub_drivers[i];
		if (s->open) {
			log_device("'%s' - open start\n", s->name);
			ret = s->open(fh);
			if (ret) {
				log_error("'%s' open failed\n", s->name);
				for (j = i; j > 0; j--) {
					s = sub_drivers[j - 1];
					if (s->close)
						s->close(fh);
				}
				return ret;
			}
			log_device("'%s' - open done\n", s->name);
		}
	}

	return 0;
}

static const struct ciplus_ioctl ioctl_core = {
	.magic = CIPLUS_IOC_CORE_MAGIC,
	.func = core_ioctl,
};

static const struct ciplus_ioctl *get_ioctl(struct ciplus_device *dev,
					    char magic)
{
	int i;
	const struct ciplus_ioctl *c;

	if (ioctl_core.magic == magic)
		return &ioctl_core;

	for (i = 0; i < ARRAY_SIZE(sub_drivers); i++) {
		c = sub_drivers[i]->ioctl;
		if (c && c->magic == magic)
			return c;
	}

	return NULL;
}

static void sub_device_close(struct ciplus_fh *fh)
{
	int i;
	const struct ciplus_sub_driver *s;

	for (i = ARRAY_SIZE(sub_drivers); i > 0; i--) {
		s = sub_drivers[i - 1];
		if (s->close) {
			log_device("'%s' - close start\n", s->name);
			s->close(fh);
			log_device("'%s' - close done\n", s->name);
		}
	}
}

static int sub_device_resume(struct ciplus_device *dev)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(sub_drivers); i++) {
		const struct ciplus_sub_driver *s = sub_drivers[i];

		if (s->resume) {
			log_device("'%s' - resume start\n", s->name);
			ret = s->resume(dev);
			if (ret) {
				log_error("'%s' resume failed\n", s->name);
				return ret;
			}
			log_device("'%s' - resume done\n", s->name);
		}
	}

	return 0;
}

static int sub_device_suspend(struct ciplus_device *dev)
{
	int i, ret;

	for (i = ARRAY_SIZE(sub_drivers); i > 0; i--) {
		const struct ciplus_sub_driver *s = sub_drivers[i - 1];

		if (s->suspend) {
			log_device("'%s' - suspend start\n", s->name);
			ret = s->suspend(dev);
			if (ret) {
				log_error("'%s' suspend failed\n", s->name);
				return ret;
			}
			log_device("'%s' - suspend done\n", s->name);
		}
	}

	return 0;
}

static int sub_device_early_init(struct ciplus_device *dev)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(sub_drivers); i++) {
		const struct ciplus_sub_driver *s = sub_drivers[i];

		if (s->early_init) {
			log_device("'%s' - early_init start\n", s->name);
			ret = s->early_init(dev);
			if (ret) {
				log_error("'%s' early_init failed\n", s->name);
				return ret;
			}
			log_device("'%s' - early_init done\n", s->name);
		}
	}

	return 0;
}

static int sub_device_init(struct ciplus_device *dev)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(sub_drivers); i++) {
		const struct ciplus_sub_driver *s = sub_drivers[i];

		if (s->init) {
			log_device("'%s' - init start\n", s->name);
			ret = s->init(dev);
			if (ret) {
				log_error("'%s' init failed\n", s->name);
				return ret;
			}
			log_device("'%s' - init done\n", s->name);
		}
	}

	return 0;
}

static void sub_device_release(struct ciplus_device *dev)
{
	int i;

	for (i = ARRAY_SIZE(sub_drivers); i > 0; i--) {
		const struct ciplus_sub_driver *s = sub_drivers[i - 1];

		if (s->release) {
			log_device("'%s' - release start\n", s->name);
			s->release(dev);
			log_device("'%s' - release done\n", s->name);
		}
	}
}

/**
 * open handler for ciplus device
 *
 */
static int dev_open(struct inode *inode, struct file *file)
{
	int ret;
	struct ciplus_fh *fh;
	struct ciplus_device *dev = inode_to_ciplus_device(inode);
	struct ciplus_channel *channel = inode_to_ciplus_channel(dev, inode);
	struct te_device *tdev = get_te_device(dev);

	fh = kzalloc(sizeof(*fh), GFP_KERNEL);
	if (!fh)
		return -ENOMEM;

	fh->dev = dev;
	fh->channel = channel;

	mutex_lock(&node_lock);

	te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_CI14);

	ret = sub_device_open(fh);
	if (ret) {
		te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_CI14);
		mutex_unlock(&node_lock);
		kfree(fh);
		return ret;
	}

	dev->users++;
	if (channel)
		channel->users++;

	log_device("device opened (%d:%d)\n", imajor(inode), iminor(inode));

	mutex_unlock(&node_lock);

	file->private_data = fh;

	return 0;
}

/**
 * release handler for ciplus device
 *
 */
static int dev_close(struct inode *inode, struct file *file)
{
	struct ciplus_fh *fh = file->private_data;
	struct ciplus_device *dev = fh->dev;
	struct ciplus_channel *channel = fh->channel;
	struct te_device *tdev = get_te_device(dev);

	mutex_lock(&node_lock);

	dev->users--;
	if (channel)
		channel->users--;

	sub_device_close(fh);

	log_device("device closed (%d:%d)(users:%d)\n", imajor(inode),
		   iminor(inode), dev->users);

	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_CI14);

	mutex_unlock(&node_lock);

	kfree(fh);

	return 0;
}

/**
 * ioctl handler for ciplus device.
 */
static long dev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct ciplus_fh *fh = file->private_data;

	const struct ciplus_ioctl *c;

	c = get_ioctl(fh->dev, _IOC_TYPE(cmd));
	if (!c) {
		log_error("invalid magic. magic='%c'\n", _IOC_TYPE(cmd));
		return -ENOTTY;
	}

	return te_ioctl_usercopy(cmd, arg, c->func, c->get_user_param, fh);
}

static int dev_mmap(struct file *file, struct vm_area_struct *vma)
{
	return te_user_mmap(vma, file->f_flags & O_DSYNC);
}

struct file_operations ciplus_dev_fops = {
	.open = dev_open,
	.release = dev_close,
	.unlocked_ioctl = dev_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = dev_ioctl,
#endif
	.mmap = dev_mmap,
	.read = ciplus_ipd_ioc_read,
	.write = ciplus_ipd_ioc_write,
	.poll = ciplus_ipd_ioc_poll,
};

/**
 * Suspend
 *
 * @return	if succeeded - 0, else - errno.
 */
int ciplus_device_suspend(struct ciplus_device *dev)
{
	int ret;

	TE_REG_SetIntrEnable(TOP_INTR_CIPLUS, false);

	ret = sub_device_suspend(dev);

	return ret;
}

int ciplus_device_resume(struct ciplus_device *dev)
{
	int ret;

	/* Hardware Reinitialzation */
	init_hw();

	ret = sub_device_resume(dev);
	if (ret)
		return ret;

	/* enable interrupts */
	TE_REG_SetIntrEnable(TOP_INTR_CIPLUS, true);

	return 0;
}

int ciplus_device_init(struct ciplus_device *dev)
{
	int ret, i;

	//mutex init
	mutex_init(&dev->mutex);

	for (i = 0; i < dev->num_channel; i++) {
		struct ciplus_channel *channel = &dev->channels[i];
		channel->num = i;
		channel->dev = dev;
	}

	ret = sub_device_early_init(dev);
	CHECK_ERROR(ret, return ret, "Error sub_device_early_init");

	init_hw();

	ret = sub_device_init(dev);
	CHECK_ERROR(ret, return ret, "Error sub_device_init");

	/* enable interrupts */
	TE_REG_SetIntrEnable(TOP_INTR_CIPLUS, true);

	return 0;
}

void ciplus_device_release(struct ciplus_device *dev)
{
	TE_REG_SetIntrEnable(TOP_INTR_CIPLUS, false);

	sub_device_release(dev);
}
