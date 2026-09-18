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
 *  arib2 driver core functions
 *
 *  @author		Yeonju Lee (yeonju.lee@lge.com)
 *  @version		0.1
 *  @date		2017-11-21
 *  @note		Additional information.
 */

#include <linux/mm.h>

#include "arib2_impl.h"

#define inode_to_arib2_device(inode) \
	container_of(inode->i_cdev, struct arib2_device, cdev)

#define inode_to_arib2_channel(dev,inode) \
({ \
	unsigned __n = iminor(inode); \
	__n ? &dev->channels[__n-1] : NULL; \
})

static DEFINE_MUTEX(node_mutex);
static DEFINE_MUTEX(core_mutex);

static const struct arib2_sub_driver *sub_drivers[] = {
	&arib2_debug_driver,
	&arib2_mem_driver,
	&arib2_io_driver,
	&arib2_clock_driver,
#ifdef USE_ARIB2_HW_FILTER
	&arib2_filter_driver,	// DISABLED
#endif
	&arib2_isr_driver,
};

struct arib2_device *arib2_get_device(struct te_device *dev)
{
	struct te_subdev *sd;

	sd = te_get_subdev(dev, ARIB2_DEVICE_NAME);
	if (!sd)
		return NULL;

	return te_subdev_to_arib2_device(sd);
}

struct arib2_channel *arib2_get_channel(struct arib2_device *dev, u8 num)
{
	return num < dev->num_channel ? &dev->channels[num] : NULL;
}

static void enable_interrupt(struct arib2_device *dev)
{
	struct te_io_cfg *cfg = te_get_io_config();

	if (dev->use_swtlv)
		return;

	if (!cfg->num_dumper)
		TE_REG_SetIntrEnable(TOP_INTR_ARIB2, true);
}

static void disable_interrupt(struct arib2_device *dev)
{
	struct te_io_cfg *cfg = te_get_io_config();

	if (dev->use_swtlv)
		return;

	if (!cfg->num_dumper)
		TE_REG_SetIntrEnable(TOP_INTR_ARIB2, false);
}

static int init_hw(struct arib2_device *dev)
{
	if (dev->use_swtlv)
		return 0;

	return 0;
}

static int ioc_get_chip_config(struct arib2_fh *fh, void *arg)
{
	LX_ARIB2_CHIP_CFG_T *param = arg;
	struct te_io_cfg *cfg = te_get_io_config();

	param->input_ver = cfg->version;

	return 0;
}

/*_________________________ BEGIN - NOTI _____________________________________*/

#ifdef USE_ARIB2_HW_FILTER
static int init_notifier(struct arib2_device *dev)
{
	struct arib2_notifier *noti;

	if (dev->use_swtlv)	//Not supported in swtlv
		return 0;

	noti = kcalloc(1, sizeof(*noti), GFP_KERNEL);
	CHECK_ERROR(!noti, return -ENOMEM, "out of memory");

	mutex_init(&noti->lock);
	init_waitqueue_head(&noti->wq);

	dev->noti = noti;

	return 0;
}

static void reset_notifier(struct arib2_device *dev)
{
	struct arib2_notifier *noti = dev->noti;

	if (!noti)		//swtlv mode
		return;

	mutex_lock(&noti->lock);
	noti->widx = 0;
	noti->ridx = 0;
	mutex_unlock(&noti->lock);
}

static int get_noti_count(struct arib2_device *dev)
{
	struct arib2_notifier *noti = dev->noti;
	u32 widx, ridx;
	int count;
	int noti_max;

	if (dev->use_swtlv)
		return 0;

	mutex_lock(&noti->lock);

	widx = noti->widx;
	ridx = noti->ridx;
	noti_max = LX_ARIB2_MAX_NOTIFY_DATA;

	if (widx == ridx)
		count = 0;
	else
		count = (widx + noti_max - ridx) % noti_max;

	mutex_unlock(&noti->lock);

	return count;
}

#define COPY_TO_USER(to,from,n,fail_action)					\
{															\
	if (copy_to_user((void __user*)to, (void *)from, n)) {	\
		log_error("copy_to_user(%p,%p,%u)\n", to, from, (unsigned int)(n)); \
		fail_action;										\
	}														\
}

static ssize_t read_noti_msg(struct arib2_device *dev, char __user *data,
			     size_t size)
{
	int ret, count, ret_size, noti_max;
	u32 widx, ridx, wsize, remained;
	struct arib2_notifier *noti;

	noti = dev->noti;
	noti_max = LX_ARIB2_MAX_NOTIFY_DATA;

	mutex_lock(&noti->lock);

	/* update widx, ridx */
	widx = noti->widx;
	ridx = noti->ridx;

	count = (widx + noti_max - ridx) % noti_max;
	if (!count) {
		ret = -EAGAIN;
		log_noti("zero count; widx[%d] ridx[%d]", widx, ridx);
		goto fail;
	}

	ret_size = 0;
	ret = -EFAULT;

	if (count > noti->peak_count)
		noti->peak_count = (u32)count;

	remained = size / sizeof(LX_ARIB2_NOTIFY_MESSAGE_T);	//number of msgs

	if (widx < ridx) {	/* wrap around */

		count = MIN(noti_max - ridx, remained);

		wsize = sizeof(LX_ARIB2_NOTIFY_DATA_T) * count;
		COPY_TO_USER(data, &noti->param[ridx], wsize, goto fail);

		ret_size = wsize;
		remained -= count;
		noti->total_count += count;

		if (remained && widx > 0) {	//next round
			data += wsize;
			count = MIN(widx, remained);

			wsize = sizeof(LX_ARIB2_NOTIFY_DATA_T) * count;
			COPY_TO_USER(data, &noti->param[0], wsize, goto fail);

			ret_size += wsize;
			noti->total_count += count;
			ridx = count;	//move ridx
		} else {
			ridx = (ridx + count) & noti_max;
		}
	} else {		//normal case (ridx < widx)

		count = MIN(count, remained);

		wsize = sizeof(LX_ARIB2_NOTIFY_DATA_T) * count;
		COPY_TO_USER(data, &noti->param[ridx], wsize, goto fail);

		ret_size = wsize;
		ridx += count;
		noti->total_count += count;
	}

	noti->ridx = ridx;

	mutex_unlock(&noti->lock);
	return ret_size;

 fail:
	mutex_unlock(&noti->lock);
	return ret;

}

/*TODO: will be deprecated */
static int ioc_get_noti_msg(struct arib2_fh *fh, void *arg)
{
	LX_ARIB2_NOTIFY_MESSAGE_T *param = arg;
	struct arib2_notifier *noti = fh->dev->noti;
	LX_ARIB2_NOTIFY_DATA_T *data;
	u32 widx, ridx, remained, count, wcount;
	int ret, rc;
	struct arib2_config *chip_cfg = arib2_get_config();

	CHECK_ERROR(chip_cfg->swtlv, return -EPERM,
		    "can't use noti message (in swtlv)");

	ret = -EFAULT;

	if (param->timeout == LX_ARIB2_INFINITE_WAIT) {
		rc = wait_event_interruptible(noti->wq,
					      noti->widx != noti->ridx);
		if (rc != 0) {
			return rc;
		}
	} else if (param->timeout > 0) {
		rc = wait_event_interruptible_timeout(noti->wq,
						      noti->widx != noti->ridx,
						      msecs_to_jiffies
						      (param->timeout));
		if (rc <= 0) {
			return rc;
		}
	}

	mutex_lock(&noti->lock);

	widx = noti->widx;
	ridx = noti->ridx;

	if (widx == ridx) {
		ret = 0;
		goto exit;
	}

	data = te_ioctl_get_user_ptr(param->data);
	remained = param->max_count;	//given size

	if (widx < ridx) {	/* wrap around case */
		count = LX_ARIB2_MAX_NOTIFY_DATA - ridx;
		wcount = MIN(remained, count);

		COPY_TO_USER(data, &noti->param[ridx],
			     wcount * sizeof(LX_ARIB2_NOTIFY_DATA_T),
			     goto exit);
		rc = wcount;
		remained -= wcount;

		if (remained && widx > 0)	//one more
		{
			data += wcount;
			wcount = MIN(remained, widx);

			COPY_TO_USER(data, &noti->param[0],
				     wcount * sizeof(LX_ARIB2_NOTIFY_DATA_T),
				     goto exit);

			rc += wcount;
			ridx = wcount;
		} else {
			ridx = (ridx + wcount) % LX_ARIB2_MAX_NOTIFY_DATA;
		}
	} else			//normal case
	{
		count = widx - ridx;
		wcount = MIN(remained, count);

		COPY_TO_USER(data, &noti->param[ridx],
			     wcount * sizeof(LX_ARIB2_NOTIFY_DATA_T),
			     goto exit);
		rc = wcount;
		ridx += wcount;
	}

	noti->ridx = ridx;
	ret = rc;

 exit:
	mutex_unlock(&noti->lock);
	return ret;

}

int arib2_add_noti(struct arib2_device *dev, LX_ARIB2_NOTIFY_DATA_T *data)
{
	int ret;
	u32 ridx, widx, next_widx;
	static int notify_max_errors = 10;	/* To prevent the message buffer overflow in abnormal case */
	struct arib2_notifier *noti = dev->noti;

	if (!noti) {
		log_error("not supported noti in swtlv (abnormal status)\n");
		return -EINVAL;
	}

	mutex_lock(&noti->lock);

	/* Check overflow */
	ridx = noti->ridx;
	widx = noti->widx;
	next_widx = (widx + 1) % LX_ARIB2_MAX_NOTIFY_DATA;

	/* full condition, add tail */
	if (next_widx == ridx) {
		/* reset to zero (full) */
		noti->widx = 0;
		noti->ridx = 0;

		if (notify_max_errors > 0) {
			log_warning("Kdrv->User Msg Queue Full [10/%02d]",
				    notify_max_errors);
			notify_max_errors--;
			if (notify_max_errors == 0) {
				log_error
				    ("Disable warning message! (abnormal status)");
			}
		}
		ret = -ENOMEM;
	} else {
		noti->param[widx] = *data;
		noti->widx = next_widx;
		ret = 0;
		wake_up_interruptible(&noti->wq);
	}

	mutex_unlock(&noti->lock);

	return ret;
}

int arib2_add_noti_status(struct arib2_device *dev, LX_ARIB2_NOTIFY_TYPE_T type,
			  u8 idx, u32 status)
{
	LX_ARIB2_NOTIFY_DATA_T *data;
	u32 widx, ridx;
	int count = 0;
	struct arib2_notifier *noti = dev->noti;

	if (!noti) {
		log_error("not supported noti in swtlv (abnormal status)\n");
		return -EINVAL;
	}

	mutex_lock(&noti->lock);

	ridx = noti->ridx;
	widx = noti->widx;

	/* overwrite filter status */
	while (ridx != widx) {
		data = &noti->param[idx];
		if (data->type == type && data->filter.idx == idx) {
			data->filter.status |= status;
			count++;
		}

		ridx = (ridx + 1) & LX_ARIB2_MAX_NOTIFY_DATA;
	}

	mutex_unlock(&noti->lock);

	return count;
}
#else
static int init_notifier(struct arib2_device *dev)
{
	return 0;
}

static void reset_notifier(struct arib2_device *dev)
{
}
#endif

/*__________________________________________ END - NOTI __________________________________________*/

static const struct arib2_ioctl_info ioctls[] = {
	IOC_INFO(ARIB2_IOC_GET_CHIPCFG, ioc_get_chip_config, true, true),
#ifdef USE_ARIB2_HW_FILTER
	IOC_INFO(ARIB2_IOC_GET_NOTIFY, ioc_get_noti_msg, true, true),
#endif
};

static int core_ioctl(void *priv, unsigned int cmd, void *arg)
{
	return arib2_do_ioctl(priv, cmd, arg, core_mutex, ioctls);
}

static int sub_device_open(struct arib2_fh *fh)
{
	int i, j, ret;
	const struct arib2_sub_driver *s;

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

static const struct arib2_ioctl ioctl_core = {
	.magic = ARIB2_IOC_CORE_MAGIC,
	.func = core_ioctl,
};

static const struct arib2_ioctl *get_ioctl(struct arib2_device *dev, char magic)
{
	int i;
	const struct arib2_ioctl *c;

	if (ioctl_core.magic == magic)
		return &ioctl_core;

	for (i = 0; i < ARRAY_SIZE(sub_drivers); i++) {
		c = sub_drivers[i]->ioctl;
		if (c && c->magic == magic)
			return c;
	}

	return NULL;
}

static void sub_device_close(struct arib2_fh *fh)
{
	int i;
	const struct arib2_sub_driver *s;

	for (i = ARRAY_SIZE(sub_drivers); i > 0; i--) {
		s = sub_drivers[i - 1];
		if (s->close) {
			log_device("'%s' - close start\n", s->name);
			s->close(fh);
			log_device("'%s' - close done\n", s->name);
		}
	}
}

static int sub_device_resume(struct arib2_device *dev)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(sub_drivers); i++) {
		const struct arib2_sub_driver *s = sub_drivers[i];

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

static int sub_device_suspend(struct arib2_device *dev)
{
	int i, ret;

	for (i = ARRAY_SIZE(sub_drivers); i > 0; i--) {
		const struct arib2_sub_driver *s = sub_drivers[i - 1];

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

static int sub_device_early_init(struct arib2_device *dev)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(sub_drivers); i++) {
		const struct arib2_sub_driver *s = sub_drivers[i];

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

static int sub_device_init(struct arib2_device *dev)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(sub_drivers); i++) {
		const struct arib2_sub_driver *s = sub_drivers[i];

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

static void sub_device_release(struct arib2_device *dev)
{
	int i;

	for (i = ARRAY_SIZE(sub_drivers); i > 0; i--) {
		const struct arib2_sub_driver *s = sub_drivers[i - 1];

		if (s->release) {
			log_device("'%s' - release start\n", s->name);
			s->release(dev);
			log_device("'%s' - release done\n", s->name);
		}
	}
}

/**
 * open handler for arib2 device
 *
 */
static int dev_open(struct inode *inode, struct file *file)
{
	int ret;
	struct arib2_fh *fh;
	struct arib2_device *dev = inode_to_arib2_device(inode);
	struct arib2_channel *channel = inode_to_arib2_channel(dev, inode);
	struct te_device *tdev = get_te_device(dev);

	fh = kzalloc(sizeof(*fh), GFP_KERNEL);
	if (!fh)
		return -ENOMEM;

	fh->dev = dev;
	fh->channel = channel;

	mutex_lock(&node_mutex);

	te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_ARIB2);

	ret = sub_device_open(fh);
	if (ret) {
		te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_ARIB2);
		mutex_unlock(&node_mutex);
		kfree(fh);
		return ret;
	}

	dev->users++;
	if (channel)
		channel->users++;

	log_device("device opened (%d:%d)\n", imajor(inode), iminor(inode));

	mutex_unlock(&node_mutex);

	file->private_data = fh;

	return 0;
}

/**
 * release handler for arib2 device
 *
 */
static int dev_close(struct inode *inode, struct file *file)
{
	struct arib2_fh *fh = file->private_data;
	struct arib2_device *dev = fh->dev;
	struct arib2_channel *channel = fh->channel;
	struct te_device *tdev = get_te_device(dev);

	mutex_lock(&node_mutex);

	dev->users--;
	if (channel)
		channel->users--;

	sub_device_close(fh);

	log_device("device closed (%d:%d)\n", imajor(inode), iminor(inode));

	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_ARIB2);

	mutex_unlock(&node_mutex);

	kfree(fh);

	return 0;
}

/**
 * ioctl handler for arib2 device.
 */
static long dev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct arib2_fh *fh = file->private_data;
	const struct arib2_ioctl *c;

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

static ssize_t arib2_read_noti_msg(struct arib2_device *dev, char __user *data,
				   size_t size, unsigned int flags)
{
#ifdef USE_ARIB2_HW_FILTER
	if (dev->cfg->swtlv)
		return -EPERM;	//only support on hw mode

	if (get_noti_count(dev) == 0) {
		struct arib2_notifier *noti = dev->noti;
		int ret;

		if (flags & O_NONBLOCK)
			return -EWOULDBLOCK;	//Support Non-blocking

		ret = wait_event_interruptible(noti->wq,
					       get_noti_count(dev) != 0);
		if (ret) {
			if (ret == -ERESTARTSYS) {
				if (freezing(current))
					log_noti("freezing in dev_read");
				else
					log_noti
					    ("signal is received in dev_read");
			} else {
				log_error
				    ("error(%d) in wait_event_interruptible",
				     ret);
			}
			return ret;
		}
	}

	return read_noti_msg(dev, data, size);
#else
	return -EPERM;
#endif
}

ssize_t arib2_read_data(struct arib2_channel *channel, char __user *buf,
			size_t size)
{
	struct arib2_data *arib2_data = &channel->data;
	struct te_pktbuf *pbuf = &arib2_data->pbuf;
	int ret;

	mutex_lock(&arib2_data->mutex);
	if (!arib2_data->start) {
		ret = -EIO;
		goto exit;
	}

	ret = te_pktbuf_read_user_timeout(pbuf, buf, size, arib2_data->timeout);
	if (ret == -EIO) {
		int err = te_pktbuf_error(pbuf);
		if (err == -ESHUTDOWN) {
			ret = 0;
			goto exit;
		} else {
			te_pktbuf_flush(pbuf);
		}
	} else if (ret == -ETIME) {
		ret = 0;
		goto exit;
	}
	arib2_data->last_read_time = te_get_us_tick();

exit:
	mutex_unlock(&arib2_data->mutex);
	return ret;
}

static ssize_t dev_read(struct file *file, char __user *data, size_t size,
			loff_t *off)
{
	int ret;
	struct arib2_fh *fh = file->private_data;

	if (fh->channel) {
		if (!fh->dump) {
			log_error("not started\n");
			return -EINVAL;
		}
		ret = arib2_read_data(fh->channel, data, size);
		if (ret > 0)
			arib2_debug_user_read_callback(fh->channel, data, ret);

		return ret;
	} else {
		return arib2_read_noti_msg(fh->dev, data, size, file->f_flags);
	}
}

static unsigned int dev_poll(struct file *file, poll_table * wait)
{
#ifdef USE_ARIB2_HW_FILTER
	struct arib2_fh *fh = file->private_data;
	struct arib2_device *dev = fh->dev;

	if (fh->channel || dev->use_swtlv)
		return POLLERR;	//only support on hw mode

	if (get_noti_count(dev))
		return (POLLIN | POLLRDNORM | POLLPRI);

	/* wait for something is happen */
	poll_wait(file, &dev->noti->wq, wait);

	return 0;
#else
	return POLLERR;
#endif
}

struct file_operations arib2_dev_fops = {
	.open = dev_open,
	.release = dev_close,
	.unlocked_ioctl = dev_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = dev_ioctl,
#endif
	.mmap = dev_mmap,
	.read = dev_read,
	.poll = dev_poll,
};

int arib2_dev_suspend(struct arib2_device *dev)
{
	int ret;

	disable_interrupt(dev);

	ret = sub_device_suspend(dev);

	return ret;
}

int arib2_dev_resume(struct arib2_device *dev)
{
	int ret;

	reset_notifier(dev);
	init_hw(dev);

	ret = sub_device_resume(dev);
	if (ret)
		return ret;

	enable_interrupt(dev);

	return 0;
}

int arib2_dev_init(struct arib2_device *dev)
{
	int i, ret;

	/* mutex_init */
	mutex_init(&dev->mutex);

	/* init channel variables */
	for (i = 0; i < dev->num_channel; i++) {
		struct arib2_channel *channel = &dev->channels[i];
		channel->num = i;
		channel->dev = dev;
		spin_lock_init(&channel->spinlock);
	}

	ret = sub_device_early_init(dev);
	CHECK_ERROR(ret, return ret, "Error in sub_device_early_init");

	init_hw(dev);

	ret = init_notifier(dev);
	CHECK_ERROR(ret, return ret, "Error in init_notifier");

	ret = sub_device_init(dev);
	CHECK_ERROR(ret, return ret, "Error in sub_device_init");

	enable_interrupt(dev);

	return 0;
}

void arib2_dev_release(struct arib2_device *dev)
{
	disable_interrupt(dev);
	sub_device_release(dev);
}
