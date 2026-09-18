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
 *  @author		Yeonju Lee ( yeonju.lee@lge.com)
 *  @version    0.1
 *  @date       2016-02-25
 *  @note       Additional information.
 */

#include <linux/mm.h>

#include "atsc3_impl.h"

#define MAX_MSG_COUNT		256

#define inode_to_atsc3_device(inode) \
	container_of(inode->i_cdev, struct atsc3_device, cdev)

#define inode_to_channel_num(inode)	(iminor(inode) - 1)

#define inode_to_atsc3_channel(dev,inode) \
({ \
	unsigned __n = inode_to_channel_num(inode); \
	__n < dev->num_channel ? &dev->channels[__n] : NULL; \
})

static DEFINE_MUTEX(node_lock);

static const struct atsc3_sub_driver *sub_drivers[] = {
	&atsc3_debug_driver,
	&atsc3_mem_driver,
	&atsc3_io_driver,
	&atsc3_clock_driver,
	&atsc3_filter_driver,
	&atsc3_isr_driver,
};

struct atsc3_device *atsc3_get_device(struct te_device *dev)
{
	struct te_subdev *sd;

	sd = te_get_subdev(dev, ATSC3_DEVICE_NAME);
	if (!sd)
		return NULL;

	return te_subdev_to_atsc3_device(sd);
}

struct atsc3_channel *atsc3_get_channel(struct atsc3_device *dev, u8 num)
{
	return num < dev->num_channel ? &dev->channels[num] : NULL;
}

static void enable_interrupt(struct atsc3_device *dev)
{
	struct te_io_cfg *cfg = te_get_io_config();

	if (!cfg->num_dumper)
		TE_REG_SetIntrEnable(TOP_INTR_A3, true);
}

static void disable_interrupt(struct atsc3_device *dev)
{
	struct te_io_cfg *cfg = te_get_io_config();

	if (!cfg->num_dumper)
		TE_REG_SetIntrEnable(TOP_INTR_A3, false);
}

static int init_hw(void)
{
	return 0;
}

int atsc3_add_message(struct atsc3_device *dev, LX_ATSC3_MSG_T *msg)
{
	int ret;
	struct atsc3_dev_message *mdev = &dev->msg;
	struct te_msgbuf *mbuf = &mdev->buf;
	static int notify_max_errors = 10;	/* To prevent the message buffer overflow in abnormal case */

	mutex_lock(&mdev->mutex);

	if (te_msgbuf_free_count(mbuf)) {
		LX_ATSC3_MSG_T *m;
		te_msgbuf_raw_get_wbuf(mbuf, 0, (void **)&m);
		*m = *msg;
		te_msgbuf_raw_write_skip(mbuf, 1);
		ret = 0;
	} else {
		te_msgbuf_flush(mbuf);
		if (notify_max_errors > 0) {
			log_warning("Krdv->User Msg Queue is full(%u)",
				    notify_max_errors);
			notify_max_errors--;
		}
		ret = -ENOMEM;
	}

	mutex_unlock(&mdev->mutex);

	return ret;
}

int atsc3_add_msg_status(struct atsc3_device *dev, LX_ATSC3_MSG_TYPE_T type,
			 u16 idx, u32 status)
{
	struct atsc3_dev_message *mdev = &dev->msg;
	struct te_msgbuf *mbuf = &mdev->buf;
	LX_ATSC3_MSG_T *msg;
	u32 i, n;
	int count = 0;

	mutex_lock(&mdev->mutex);

	n = te_msgbuf_avail_count(mbuf);
	for (i = 0; i < n; i++) {
		te_msgbuf_raw_get_rbuf(mbuf, i, (void **)&msg);
		if (msg->type == type || msg->filter.index == idx) {
			msg->filter.status |= status;
			count++;
		}
	}

	mutex_unlock(&mdev->mutex);

	return count;
}

static int init_message(struct atsc3_device *dev)
{
	int ret;
	struct atsc3_dev_message *mdev = &dev->msg;

	ret = te_msgbuf_init(&mdev->buf, sizeof(LX_ATSC3_MSG_T),
			     MAX_MSG_COUNT, 0);
	CHECK_ERROR(ret, return ret, "Err in te_msgbuf_init");

	mutex_init(&mdev->mutex);

	return 0;
}

static void release_message(struct atsc3_device *dev)
{
	struct atsc3_dev_message *mdev = &dev->msg;

	te_msgbuf_release(&mdev->buf);
}

static void reset_message(struct atsc3_device *dev)
{
	struct atsc3_dev_message *mdev = &dev->msg;

	mutex_lock(&mdev->mutex);
	te_msgbuf_reset(&mdev->buf);
	mutex_unlock(&mdev->mutex);
}

static int ioc_get_notify_message(struct atsc3_fh *fh, void *arg)
{
	struct atsc3_device *dev = fh->dev;
	struct atsc3_dev_message *mdev = &dev->msg;
	struct te_msgbuf *mbuf = &mdev->buf;
	LX_ATSC3_MSG_PARAM_T *param = arg;
	LX_ATSC3_MSG_T __user *data;
	unsigned long timeout;
	int ret;

	if (param->timeout == LX_ATSC3_INFINITE_WAIT)
		timeout = TE_BUF_INFINITE_TIMEOUT;
	else
		timeout = param->timeout;

	ret = te_msgbuf_wait_wevent(mbuf, timeout);
	if (ret <= 0) {
		if (ret == -ETIME)
			ret = 0;
		return ret;
	}

	data = te_ioctl_get_user_ptr(param->data);

	mutex_lock(&mdev->mutex);
	ret = te_msgbuf_read_user(mbuf, data, param->max_count);
	mutex_unlock(&mdev->mutex);

	if (ret < 0) {
		log_error("Err(%d) in te_msgbuf_read_user\n", ret);
	}

	return ret;
}

static int get_chip_config(struct atsc3_device *dev,
			   struct lx_atsc3_chip_cfg *cfg)
{
	struct te_io_cfg *te_cfg = te_get_io_config();

	cfg->input_ver = te_cfg->version;
	cfg->num_channel = dev->cfg->num_ch;
	return 0;
}

int atsc3_get_chip_config(struct atsc3_device *dev,
			  struct lx_atsc3_chip_cfg *cfg)
{
	return get_chip_config(dev, cfg);
}

static int ioc_get_chip_config(struct atsc3_fh *fh, void *arg)
{
	LX_ATSC3_CHIP_CFG_T *param = arg;

	get_chip_config(fh->dev, param);

	return 0;
}

static int core_ioctl(void *priv, unsigned int cmd, void *arg)
{
	int ret;
	struct atsc3_fh *fh = priv;

	switch (cmd) {
	case ATSC3_IOC_GET_CHIPCFG:
		ret = ioc_get_chip_config(fh, arg);
		break;

	case ATSC3_IOC_GET_NOTIFY:
		ret = ioc_get_notify_message(fh, arg);
		break;

	default:
		log_error("invalid command[0x%08x]. magic=0x%02X, num=%d",
			  cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));
		ret = -ENOTTY;
		break;
	}

	return ret;
}

static int sub_device_open(struct atsc3_fh *fh)
{
	int i, j, ret;
	const struct atsc3_sub_driver *s;

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

static const struct atsc3_ioctl ioctl_core = {
	.magic = ATSC3_IOC_CORE_MAGIC,
	.func = core_ioctl,
};

static const struct atsc3_ioctl *get_ioctl(struct atsc3_device *dev, char magic)
{
	int i;
	const struct atsc3_ioctl *c;

	if (ioctl_core.magic == magic)
		return &ioctl_core;

	for (i = 0; i < ARRAY_SIZE(sub_drivers); i++) {
		c = sub_drivers[i]->ioctl;
		if (c && c->magic == magic)
			return c;
	}

	return NULL;
}

static void sub_device_close(struct atsc3_fh *fh)
{
	int i;
	const struct atsc3_sub_driver *s;

	for (i = ARRAY_SIZE(sub_drivers); i > 0; i--) {
		s = sub_drivers[i - 1];
		if (s->close) {
			log_device("'%s' - close start\n", s->name);
			s->close(fh);
			log_device("'%s' - close done\n", s->name);
		}
	}
}

static int sub_device_resume(struct atsc3_device *dev)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(sub_drivers); i++) {
		const struct atsc3_sub_driver *s = sub_drivers[i];

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

static int sub_device_suspend(struct atsc3_device *dev)
{
	int i, ret;

	for (i = ARRAY_SIZE(sub_drivers); i > 0; i--) {
		const struct atsc3_sub_driver *s = sub_drivers[i - 1];

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

static int sub_device_early_init(struct atsc3_device *dev)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(sub_drivers); i++) {
		const struct atsc3_sub_driver *s = sub_drivers[i];

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

static int sub_device_init(struct atsc3_device *dev)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(sub_drivers); i++) {
		const struct atsc3_sub_driver *s = sub_drivers[i];

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

static void sub_device_release(struct atsc3_device *dev)
{
	int i;

	for (i = ARRAY_SIZE(sub_drivers); i > 0; i--) {
		const struct atsc3_sub_driver *s = sub_drivers[i - 1];

		if (s->release) {
			log_device("'%s' - release start\n", s->name);
			s->release(dev);
			log_device("'%s' - release done\n", s->name);
		}
	}
}

/**
 * open handler for atsc3 device
 *
 */
static int dev_open(struct inode *inode, struct file *file)
{
	int ret;
	struct atsc3_fh *fh;
	struct atsc3_device *dev = inode_to_atsc3_device(inode);
	struct atsc3_channel *channel = inode_to_atsc3_channel(dev, inode);
	struct atsc3_channel *fixup_channel = NULL;
	struct te_device *tdev = get_te_device(dev);

	if (channel && dev->cfg->fixup_dumper) {
		unsigned num = inode_to_channel_num(inode);
		int m = dev->num_channel / 2;
		if (num >= m)
			return -ENODEV;

		fixup_channel = &dev->channels[num + m];
	}

	fh = kzalloc(sizeof(*fh), GFP_KERNEL);
	if (!fh)
		return -ENOMEM;

	fh->dev = dev;
	fh->channel = channel;
	fh->fixup_channel = fixup_channel;

	mutex_lock(&node_lock);

	te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_ATSC3);

	ret = sub_device_open(fh);
	if (ret) {
		te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_ATSC3);
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
 * release handler for atsc3 device
 *
 */
static int dev_close(struct inode *inode, struct file *file)
{
	struct atsc3_fh *fh = file->private_data;
	struct atsc3_device *dev = fh->dev;
	struct atsc3_channel *channel = fh->channel;
	struct te_device *tdev = get_te_device(dev);

	mutex_lock(&node_lock);

	dev->users--;
	if (channel)
		channel->users--;

	sub_device_close(fh);

	log_device("device closed (%d:%d)\n", imajor(inode), iminor(inode));

	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_ATSC3);

	mutex_unlock(&node_lock);

	kfree(fh);

	return 0;
}

/**
 * ioctl handler for atsc3 device.
 */
static long dev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct atsc3_fh *fh = file->private_data;
	const struct atsc3_ioctl *c;

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

struct file_operations atsc3_dev_fops = {
	.open = dev_open,
	.release = dev_close,
	.unlocked_ioctl = dev_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = dev_ioctl,
#endif
	.mmap = dev_mmap,
};

int atsc3_device_suspend(struct atsc3_device *dev)
{
	int ret;

	disable_interrupt(dev);
	ret = sub_device_suspend(dev);

	return ret;
}

int atsc3_device_resume(struct atsc3_device *dev)
{
	int ret;

	reset_message(dev);
	init_hw();

	ret = sub_device_resume(dev);
	if (ret)
		return ret;

	enable_interrupt(dev);

	return 0;
}

int atsc3_device_init(struct atsc3_device *dev)
{
	int i, ret;

	/* init channel variables */
	for (i = 0; i < dev->num_channel; i++) {
		struct atsc3_channel *channel = &dev->channels[i];

		channel->num = i;
		channel->dev = dev;
		spin_lock_init(&channel->spinlock);
	}

	ret = sub_device_early_init(dev);
	CHECK_ERROR(ret, return ret, "Error in sub_device_early_init");

	ret = init_message(dev);
	CHECK_ERROR(ret, return ret, "Error in init_message");

	init_hw();

	ret = sub_device_init(dev);
	CHECK_ERROR(ret, return ret, "Error in sub_device_init");

	enable_interrupt(dev);

	return 0;
}

void atsc3_device_release(struct atsc3_device *dev)
{
	disable_interrupt(dev);

	sub_device_release(dev);

	release_message(dev);
}
