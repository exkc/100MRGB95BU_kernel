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
 *  sdec driver
 *
 *  @author	Jihoon Lee ( gaius.lee@lge.com)
 *  @author	Jinhwan Bae ( jinhwan.bae@lge.com) - modifier
 *  @version	1.0
 *  @date		2010-03-30
 *  @note		Additional information.
 */

#include <linux/mm.h>

#include "sdec_impl.h"

#define MAX_MSG_COUNT		256
#define MAX_MSG_ERR_COUNT	10	/* To prevent the message buffer overflow in abnormal case */

#define inode_to_sdec_device(inode) \
	container_of(inode->i_cdev, struct sdec_device, cdev)

#define inode_to_sdec_channel(dev,inode) \
({ \
	unsigned __n = iminor(inode); \
	__n ? &dev->channels[__n-1] : NULL; \
})

static DEFINE_MUTEX(node_lock);

static const struct sdec_sub_driver *sub_drivers[] = {
	&sdec_debug_driver,
	&sdec_mem_driver,
	&sdec_io_driver,
	&sdec_clock_driver,
	&sdec_desc_driver,
	&sdec_filter_driver,
	&sdec_temi_driver,
	&sdec_isr_driver,
};

struct sdec_device *sdec_get_device(struct te_device *dev)
{
	struct te_subdev *sd;

	sd = te_get_subdev(dev, SDEC_DEVICE_NAME);
	if (!sd)
		return NULL;

	return te_subdev_to_sdec_device(sd);
}

struct sdec_channel *sdec_get_channel(struct sdec_device *dev, u8 num)
{
	if (num < dev->num_channel)
		return &dev->channels[num];

	return NULL;
}

static void enable_interrupt(void)
{
	struct te_config *cfg = te_get_config();
	u32 intr = TOP_INTR_TSBUF | TOP_INTR_STCC;
	u32 fe_intr = FE_STCC_INTR_PCR_MASK | FE_STCC_INTR_DISCONT_MASK;

	if (!cfg->no_stcc_bug) {
		TE_REG_SetIntrEnable(intr, true);
		TE_REG_SetFeIntrEnable(fe_intr, true);
	} else {
		TE_REG_SetIntrEnable(TOP_INTR_TSBUF, true);
	}
}

static void disable_interrupt(void)
{
	struct te_config *cfg = te_get_config();
	u32 intr = TOP_INTR_TSBUF | TOP_INTR_STCC;
	u32 fe_intr = FE_STCC_INTR_PCR_MASK | FE_STCC_INTR_DISCONT_MASK;

	if (!cfg->no_stcc_bug) {
		TE_REG_SetFeIntrEnable(fe_intr, false);
		TE_REG_SetIntrEnable(intr, false);
	} else {
		TE_REG_SetIntrEnable(TOP_INTR_TSBUF, false);
	}
}

static int init_hw(struct sdec_device *dev)
{
	int i, num;

	log_noti("init_hw");

	for (i = 0; i < dev->num_channel; i++) {
		TE_REG_SetChannelSource(i, CH_SRC_DISABLE);
	}

	/*
	   pidfilter configuration of download index for main channel.

	   default value of download index is 0.
	   to prevent mis-operation caused from wrong call sequence,
	   change initial value as 1.
	 */
	num = dev->num_channel - dev->cfg->num_sub_channel;
	for (i = 0; i < num; i++) {
		TE_REG_SetChannelDownloadIdx(i, 1);
	}

	log_noti("HW Init Done");

	return 0;
}

static int debug_show_message(struct sdec_device *dev, struct seq_file *m)
{
	struct sdec_dev_message *mdev = &dev->msg;

	mutex_lock(&mdev->mutex);
	seq_printf(m, "MESSAGE STATUS\n");
	seq_printf(m, "count : %u\n", te_msgbuf_avail_count(&mdev->buf));
	seq_printf(m, "peak_count : %u\n", mdev->peak_count);
	seq_printf(m, "total_count : %u\n", mdev->total_count);
	seq_printf(m, "overflow_count : %u\n", mdev->overflow_count);
	seq_printf(m, "overflow_total_count : %u\n",
		   mdev->overflow_total_count);
	mutex_unlock(&mdev->mutex);

	return 0;
}

static int init_message(struct sdec_device *dev)
{
	struct sdec_dev_message *mdev = &dev->msg;
	int ret;

	ret = te_msgbuf_init(&mdev->buf, sizeof(LX_SDEC_MSG_T),
			     MAX_MSG_COUNT, 0);
	CHECK_ERROR(ret, return ret, "Err in te_msgbuf_init");

	mutex_init(&mdev->mutex);

	mdev->total_count = 0;
	mdev->peak_count = 0;
	mdev->overflow_count = 0;
	mdev->overflow_total_count = 0;
	mdev->max_overflow_msg = MAX_MSG_ERR_COUNT;

	sdec_debug_register_status_show(dev, SDEC_DEBUG_STATUS_NOTI,
					debug_show_message);

	return 0;
}

static void release_message(struct sdec_device *dev)
{
	struct sdec_dev_message *mdev = &dev->msg;

	te_msgbuf_release(&mdev->buf);
}

static void reset_message(struct sdec_device *dev)
{
	struct sdec_dev_message *mdev = &dev->msg;

	mutex_lock(&mdev->mutex);

	te_msgbuf_reset(&mdev->buf);
	mdev->total_count = 0;
	mdev->overflow_count = 0;
	mutex_unlock(&mdev->mutex);
}

int sdec_add_message(struct sdec_device *dev, LX_SDEC_MSG_T *msg)
{
	int ret;
	struct sdec_dev_message *mdev = &dev->msg;
	struct te_msgbuf *mbuf = &mdev->buf;

	mutex_lock(&mdev->mutex);

	if (te_msgbuf_free_count(mbuf)) {
		LX_SDEC_MSG_T *m;
		te_msgbuf_raw_get_wbuf(mbuf, 0, (void **)&m);
		*m = *msg;
		te_msgbuf_raw_write_skip(mbuf, 1);
		ret = 0;
	} else {
		te_msgbuf_flush(mbuf);
		if (mdev->overflow_count <= mdev->max_overflow_msg) {
			mdev->overflow_count++;
			log_warning("Krdv->User Msg Queue is full(%u)",
				    mdev->overflow_count);
		}
		mdev->overflow_total_count++;
		ret = -ENOMEM;
	}

	mutex_unlock(&mdev->mutex);

	return ret;
}

int sdec_add_filter_msg_status(struct sdec_device *dev, u16 idx, u32 status)
{
	int count = 0;
	LX_SDEC_FILTER_MSG_T *fmsg;
	struct sdec_dev_message *mdev = &dev->msg;
	struct te_msgbuf *mbuf = &mdev->buf;
	LX_SDEC_MSG_T *msg;
	u32 i, n;

	mutex_lock(&mdev->mutex);

	n = te_msgbuf_avail_count(mbuf);
	for (i = 0; i < n; i++) {
		te_msgbuf_raw_get_rbuf(mbuf, i, (void **)&msg);
		if (msg->type == LX_SDEC_MSG_TYPE_FILTER) {
			fmsg = &msg->filter;
			if (fmsg->index == idx) {
				fmsg->status |= status;
				count++;
			}
		}
	}

	mutex_unlock(&mdev->mutex);

	return count;
}

/**
 * Get chip configuration
 *
 * @def SDEC_IOC_GET_CHIPCFG
 * @param	ch_ctrl 	[in	] handle for sdec channel
 * @return	if succeeded - 0, else - errno.
 */
static int get_chip_config(struct sdec_device *dev,
			   struct lx_sdec_chip_cfg *cfg)
{
	struct te_io_cfg *io_cfg = te_get_io_config();
	struct sdec_config *sdec_cfg = dev->cfg;

	cfg->num_channel = sdec_cfg->num_channel;
	cfg->num_sub_channel = sdec_cfg->num_sub_channel;
	cfg->num_vdec_out = sdec_cfg->num_vdec_out;
	cfg->num_adec_out = sdec_cfg->num_adec_out;
	cfg->num_pid_filter = sdec_cfg->num_pid_filter;
	cfg->num_stream_filter = sdec_cfg->num_stream_filter;
	cfg->num_temi_filter = sdec_cfg->num_temi_filter;

	cfg->num_ci_input = io_cfg->num_ci_input;
	cfg->num_ci_plus_input = io_cfg->num_ciplus_input;
	cfg->input_ver = io_cfg->version;
	cfg->num_tpi_input = io_cfg->num_tpi_input;
	if (io_cfg->num_tpi_input) {
		memcpy(cfg->tpi_table, io_cfg->tpi_info,
		       sizeof(LX_TE_INPUT_PORT_T) * io_cfg->num_tpi_input);
	}

	return 0;
}

int sdec_get_chip_config(struct sdec_device *dev, struct lx_sdec_chip_cfg *cfg)
{
	return get_chip_config(dev, cfg);
}

int sdec_get_channel_capability(struct sdec_channel *channel,
				struct lx_sdec_cap *cap)
{
	struct sdec_channel_info *info = channel->info;

	cap->num_pidf = info->num_pidf;
	cap->num_secf = info->num_secf;

	return 0;
}

static int core_ioctl(void *priv, unsigned int cmd, void *arg)
{
	int ret;
	struct sdec_fh *fh = priv;

	switch (cmd) {
	case SDEC_IOC_GET_CHIPCFG:
		ret = get_chip_config(fh->dev, arg);
		break;

	default:
		log_error("invalid command[0x%08x]. magic=0x%02X, num=%d",
			  cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));
		ret = -ENOTTY;
		break;
	}

	return ret;
}

static const struct sdec_ioctl ioctl_core = {
	.magic = SDEC_IOC_CORE_MAGIC,
	.func = core_ioctl,
};

static const struct sdec_ioctl *get_ioctl(struct sdec_device *dev, char magic)
{
	int i;
	const struct sdec_ioctl *c;

	if (ioctl_core.magic == magic)
		return &ioctl_core;

	for (i = 0; i < ARRAY_SIZE(sub_drivers); i++) {
		c = sub_drivers[i]->ioctl;
		if (c && c->magic == magic)
			return c;
	}

	return NULL;
}

static int sub_device_open(struct sdec_fh *fh)
{
	int i, j, ret;
	const struct sdec_sub_driver *s;

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

static void sub_device_close(struct sdec_fh *fh)
{
	int i;
	const struct sdec_sub_driver *s;

	for (i = ARRAY_SIZE(sub_drivers); i > 0; i--) {
		s = sub_drivers[i - 1];
		if (s->close) {
			log_device("'%s' - close start\n", s->name);
			s->close(fh);
			log_device("'%s' - close done\n", s->name);
		}
	}
}

static int sub_device_resume(struct sdec_device *dev)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(sub_drivers); i++) {
		const struct sdec_sub_driver *s = sub_drivers[i];

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

static int sub_device_suspend(struct sdec_device *dev)
{
	int i, ret;

	for (i = ARRAY_SIZE(sub_drivers); i > 0; i--) {
		const struct sdec_sub_driver *s = sub_drivers[i - 1];

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

static int sub_device_early_init(struct sdec_device *dev)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(sub_drivers); i++) {
		const struct sdec_sub_driver *s = sub_drivers[i];

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

static int sub_device_init(struct sdec_device *dev)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(sub_drivers); i++) {
		const struct sdec_sub_driver *s = sub_drivers[i];

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

static void sub_device_release(struct sdec_device *dev)
{
	int i;

	for (i = ARRAY_SIZE(sub_drivers); i > 0; i--) {
		const struct sdec_sub_driver *s = sub_drivers[i - 1];

		if (s->release) {
			log_device("'%s' - release start\n", s->name);
			s->release(dev);
			log_device("'%s' - release done\n", s->name);
		}
	}
}

/**
 * open handler for sdec device
 *
 */
static int dev_open(struct inode *inode, struct file *file)
{
	int ret;
	struct sdec_fh *fh;
	struct sdec_device *dev = inode_to_sdec_device(inode);
	struct sdec_channel *channel = inode_to_sdec_channel(dev, inode);
	struct te_device *tdev = get_te_device(dev);

	fh = kzalloc(sizeof(*fh), GFP_KERNEL);
	if (!fh)
		return -ENOMEM;

	fh->dev = dev;
	fh->channel = channel;

	mutex_lock(&node_lock);

	te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_SDEC);

	ret = sub_device_open(fh);
	if (ret) {
		te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_SDEC);
		mutex_unlock(&node_lock);
		kfree(fh);
		return ret;
	}

	dev->users++;
	if (channel)
		channel->users++;

	log_trace("device opened (%d:%d)\n", imajor(inode), iminor(inode));

	mutex_unlock(&node_lock);

	file->private_data = fh;

	return 0;
}

/**
 * release handler for sdec device
 *
 */
static int dev_close(struct inode *inode, struct file *file)
{
	struct sdec_fh *fh = file->private_data;
	struct sdec_device *dev = fh->dev;
	struct sdec_channel *channel = fh->channel;
	struct te_device *tdev = get_te_device(dev);

	mutex_lock(&node_lock);

	dev->users--;
	if (channel)
		channel->users--;

	sub_device_close(fh);

	log_trace("device closed (%d:%d)\n", imajor(inode), iminor(inode));

	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_SDEC);
	mutex_unlock(&node_lock);

	kfree(fh);

	return 0;
}

/**
 * ioctl handler for sdec device.
 */
static long dev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct sdec_fh *fh = file->private_data;
	const struct sdec_ioctl *c;

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

static ssize_t dev_read(struct file *file, char __user *data, size_t size,
			loff_t *off)
{
	struct sdec_fh *fh = file->private_data;
	struct sdec_device *dev = fh->dev;
	struct sdec_dev_message *mdev = &dev->msg;
	struct te_msgbuf *mbuf = &mdev->buf;
	int ret, count;

	ret = te_msgbuf_wait_wevent(mbuf, TE_BUF_INFINITE_TIMEOUT);
	if (ret <= 0)
		return ret;

	if (ret > mdev->peak_count)
		mdev->peak_count = ret;

	count = size / sizeof(LX_SDEC_MSG_T);

	/* no need mutex if sdec_add_filter_msg_status not used */
	mutex_lock(&mdev->mutex);
	ret = te_msgbuf_read_user(mbuf, data, count);
	mutex_unlock(&mdev->mutex);

	if (ret < 0) {
		log_error("Err(%d) in te_msgbuf_read_user\n", ret);
		return ret;
	}
	mdev->total_count += ret;

	return ret * sizeof(LX_SDEC_MSG_T);
}

const struct file_operations sdec_dev_fops = {
	.open = dev_open,
	.release = dev_close,
	.unlocked_ioctl = dev_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = dev_ioctl,
#endif
	.read = dev_read,
	.mmap = dev_mmap,
};

int sdec_device_suspend(struct sdec_device *dev)
{
	dev->data = vmalloc(sizeof(struct sdec_data));
	CHECK_ERROR(!dev->data, return -ENOMEM, "can't alloc memory");

	disable_interrupt();

	sub_device_suspend(dev);

	return 0;
}

int sdec_device_resume(struct sdec_device *dev)
{
	reset_message(dev);

	init_hw(dev);

	sub_device_resume(dev);

	enable_interrupt();

	vfree(dev->data);

	return 0;
}

int sdec_device_init(struct sdec_device *dev)
{
	int ret, i;

	mutex_init(&dev->mutex);

	/* init channel variables */
	for (i = 0; i < dev->num_channel; i++) {
		struct sdec_channel *channel = &dev->channels[i];

		channel->num = i;
		channel->dev = dev;
		channel->info = &dev->cfg->ch_info[i];
		channel->input_port = LX_TE_INPUT_PORT_NONE;
	}

	ret = sub_device_early_init(dev);
	CHECK_ERROR(ret, return ret, "Error in sub_device_early_init");

	/* initialize message */
	ret = init_message(dev);
	CHECK_ERROR(ret, return ret, "Error in init_message");

	init_hw(dev);

	ret = sub_device_init(dev);
	CHECK_ERROR(ret, return ret, "Error in sub_device_init");

	/* enable interrupts */
	enable_interrupt();

	return 0;
}

void sdec_device_release(struct sdec_device *dev)
{
	disable_interrupt();

	sub_device_release(dev);

	release_message(dev);
}
