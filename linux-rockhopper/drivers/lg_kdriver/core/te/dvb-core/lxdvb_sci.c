/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2018 by LG Electronics Inc.
 *
 * Parts of this file were based on sources as follows:
 *
 * dmxdev.c - DVB demultiplexer device
 *
 * Copyright (C) 2000 Ralph Metzler & Marcus Metzler
 *		      for convergence integrated media GmbH
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

/** @file
 *
 *  TE(Transport Engine) Driver for linux dvb(DEMUX)
 *
 *  @author	Yeonju lee (yeonju.lee@lge.com)
 *  @version	1.0
 *  @date	2019-04-15
 *  @note	Additional information.
 */

#include <linux/sched.h>
#include <linux/spinlock.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/module.h>
#include <linux/poll.h>
#include <linux/ioctl.h>
#include <linux/wait.h>
#include <linux/uaccess.h>
#include <linux/crc32.h>
#include <linux/freezer.h>
#include <linux/kthread.h>
#include <linux/sizes.h>
#include <linux/delay.h>

#include "lxdvb_impl.h"
#include "lxdvb_sci.h"

struct sci_lge_control_param {
	u32 id;
	const char *name;
	u32 size;
	u32 dir;
};

#define _IOC_RW			(_IOC_READ | _IOC_WRITE)
#define SIZE_OF_TRANSFER_APDU	sizeof(struct acas_ext_transfer_apdu)

static void debug_print_apdu(struct sci_transmit_param *param);
static u32 print_apdu_data = 0;

static const struct sci_lge_control_param sci_lge_control_params[] = {
	{ACAS_EXT_CID_INIT, "init", 0, _IOC_WRITE},
	{ACAS_EXT_CID_RESET, "reset", 0, _IOC_WRITE},
	{ACAS_EXT_CID_TRANSFER_APDU, "transfer_apdu", SIZE_OF_TRANSFER_APDU,
	_IOC_RW},
	{ACAS_EXT_CID_GET_RESET_TIME, "get_reset_time", 0, _IOC_READ},
};

static const struct sci_lge_control_param *get_sci_lge_control_param(u32 id)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(sci_lge_control_params); i++) {
		if (sci_lge_control_params[i].id == id)
			return &sci_lge_control_params[i];
	}

	return NULL;
}

static int dvb_sci_transfer_apdu(struct lxdvb_sci *sci,
				 struct acas_ext_transfer_apdu *apdu)
{
	struct sci_transmit_param param;
	void __user *user_ptr;
	int len, ret;

	CHECK_NULL_PARAM(apdu->command_apdu);
	CHECK_NULL_PARAM(apdu->response_apdu);
	CHECK_NULL_PARAM(apdu->response_apdu_len);

	CHECK_PARAM(apdu->command_apdu_len > MAX_CMD_APDU_LEN,
		    "invalid tx apdu len(%d)", apdu->command_apdu_len);
	CHECK_PARAM(apdu->max_response_apdu_len < APDU_HEADER_LEN,
		    "invalid max_res_len(%d)", apdu->max_response_apdu_len);

	if (apdu->max_response_apdu_len > MAX_APDU_DATA_LEN)
		apdu->max_response_apdu_len = MAX_APDU_DATA_LEN;

	len = apdu->command_apdu_len;
	user_ptr = te_ioctl_get_user_ptr(apdu->command_apdu);
	ret = copy_from_user(sci->tx, user_ptr, len);
	CHECK_ERROR(ret, return -EFAULT, "copy_from_user failed");

	param.tx.buf = sci->tx;
	param.tx.len = len;
	param.rx.buf = sci->rx;
	param.rx.len = apdu->max_response_apdu_len;

	ret = sci_dev_transfer_apdu(sci->dev, &param);
	CHECK_ERROR(ret, return ret, "sci_dev_transfer_apdu failed");

	len = param.rx.len;
	if (len > apdu->max_response_apdu_len) {
		log_error("length error(%d, %d)", len,
			  apdu->max_response_apdu_len);
		return -EIO;
	}

	if (print_apdu_data)
		debug_print_apdu(&param);

	user_ptr = te_ioctl_get_user_ptr(apdu->response_apdu);
	ret = copy_to_user(user_ptr, param.rx.buf, len);
	CHECK_ERROR(ret, return -EFAULT, "copy_to_user failed");

	user_ptr = te_ioctl_get_user_ptr(apdu->response_apdu_len);

	ret = copy_to_user(user_ptr, &len, sizeof(u32));
	CHECK_ERROR(ret, return -EFAULT, "copy_to_user failed");

	return 0;
}

static int dvb_sci_set_control(struct lxdvb_sci *sci,
			       struct acas_ext_control *control)
{
	int i, ret;
	switch (control->id) {
	case ACAS_EXT_CID_INIT:
		ret = 0;
		break;
	case ACAS_EXT_CID_RESET:
		/* SCI_IO_ACTIVATE */
		for (i = 0; i < 3; i++) {
			ret = sci_activate(sci->dev);
			if (ret == 0)
				break;

			msleep(100); /* 100ms */
		}

		if (i != 0) {
			log_noti("#%d tried for activate(%d)", i, ret);
		}

		break;
	case ACAS_EXT_CID_TRANSFER_APDU:
		ret = dvb_sci_transfer_apdu(sci, (void __force *)control->ptr);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}

static int dvb_sci_get_control(struct lxdvb_sci *sci,
			       struct acas_ext_control *control)
{
	int ret;

	switch (control->id) {
	case ACAS_EXT_CID_GET_RESET_TIME:
		ret = sci_get_reset_time(sci->dev, &control->value64);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}

static int lxdvb_sci_do_ioctl(void *priv, unsigned int cmd, void *parg)
{
	struct lxdvb_sci_fh *fh = priv;
	struct lxdvb_sci *sci = fh->sci;

	int ret;

	if (mutex_lock_interruptible(&sci->ioctl_mutex))
		return -ERESTARTSYS;

	switch (cmd) {
	case ACAS_EXT_S_CTL:
		ret = dvb_sci_set_control(sci, parg);
		break;
	case ACAS_EXT_G_CTL:
		ret = dvb_sci_get_control(sci, parg);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	mutex_unlock(&sci->ioctl_mutex);

	if (ret < 0) {
		log_error("command[0x%08x]. magic=0x%02X, num=%d - error %d",
			   cmd, _IOC_TYPE(cmd), _IOC_NR(cmd), ret);
	}
	return ret;
}

static int lxdvb_sci_get_user_ptr(void *priv, unsigned int cmd, void *arg,
				  struct te_ioctl_ptr_param *param)
{
	int dir;
	struct acas_ext_control *p;
	const struct sci_lge_control_param *c;

	switch (cmd) {
	case ACAS_EXT_S_CTL:
	case ACAS_EXT_G_CTL:
		p = arg;
		c = get_sci_lge_control_param(p->id);
		dir = (cmd == ACAS_EXT_S_CTL) ? _IOC_WRITE : _IOC_READ;

		if (!c) {
			log_error("invalid acas_ext_control id(%u)", p->id);
			return -EINVAL;
		}

		if (c->size != p->size) {
			log_error("size %u != %u of acas_ext_control(%s)",
				  p->size, c->size, c->name);
			return -EINVAL;
		}

		if (!(c->dir & dir)) {
			log_error("invalid command of acas_ext_control(%s)",
				  c->name);
			return -EINVAL;
		}
		if (p->size > 0) {
			param->user_ptr = te_ioctl_get_user_ptr(p->ptr);
			param->kernel_ptr = (void **)&p->ptr;
			param->size = p->size;
			param->dir = dir;
		}
		break;
	default:
		break;

	}

	return 0;
}

static long lxdvb_sci_ioctl(struct file *file, unsigned int cmd,
			    unsigned long arg)
{
	return te_ioctl_usercopy(cmd, arg, lxdvb_sci_do_ioctl,
				 lxdvb_sci_get_user_ptr, file->private_data);

}

static int lxdvb_sci_release(struct inode *inode, struct file *file)
{
	struct lxdvb_sci_fh *fh = file->private_data;
	struct lxdvb_sci *sci = fh->sci;
	int ret;

	ret = sci_close(sci->dev);
	CHECK_ERROR(ret, return -EIO, "error sci_close(%d)", ret);

	sci->dvbdev->users--;

	log_noti("%s users:%d", __func__, sci->dvbdev->users);

	return 0;
}

static int lxdvb_sci_open(struct inode *inode, struct file *file)
{
	struct dvb_device *dvbdev = file->private_data;
	struct lxdvb_sci *sci = dvbdev->priv;
	struct lxdvb_sci_fh *fh;
	int ret;

	fh = kzalloc(sizeof(*fh), GFP_KERNEL);
	if (!fh)
		return -ENOMEM;

	ret = sci_open(sci->dev);
	CHECK_ERROR(ret, goto error, "error sci_open(%d)", ret);

	dvbdev->users++;

	fh->sci = sci;

	file->private_data = fh;

	log_noti("%s users:%d", __func__, sci->dvbdev->users);

	return 0;

error:
	kfree(fh);
	return -EIO;
}

/*--------------------------- DEBUG START ------------------------------------*/

static const struct te_debug_item_info debug_list[] = {
	DBGITM_NUM("print_apdu", &print_apdu_data),
};

static void debug_print_apdu(struct sci_transmit_param *param)
{
	int i, len, size;
	struct sci_transmit *tb, *rb;
	char *str;

	size = 1024;
	str = kcalloc(1, size, GFP_KERNEL);
	CHECK_ERROR(!str, return, "no memory");

	tb = &param->tx;
	rb = &param->rx;

	len = snprintf(str, size, "tx:%02x - ", tb->len);
	for (i = 0; i < tb->len; i++) {
		len += snprintf(str + len, size - len, "%02x ", tb->buf[i]);
		if (len >= size)
			break;
	}
	log_noti("%s", str);

	len = snprintf(str, size, "rx:%02x - ", rb->len);
	for (i = 0; i < rb->len; i++) {
		len += snprintf(str + len, size - len, "%02x ", rb->buf[i]);
		if (len >= size)
			break;
	}
	log_noti("%s", str);

	kfree(str);
}

static void init_debug(struct lxdvb_device *dev, struct lxdvb_sci *sci)
{
	sci->debug_dir = te_debug_create_dir("sci", dev->debug_dir);
	CHECK_ERROR(!sci->debug_dir, return ,"error in te_debug_create_dir");

	debug_create_item_files(debug_list, sci, sci->debug_dir);
}

/*--------------------------- DEBUG END --------------------------------------*/

static const struct file_operations lxdvb_sci_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = lxdvb_sci_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = lxdvb_sci_ioctl,
#endif
	.open = lxdvb_sci_open,
	.release = lxdvb_sci_release,
};

static const struct dvb_device sci_dvbdev = {
	.priv = NULL,
#if defined(CONFIG_MEDIA_CONTROLLER_DVB)
	.name = "dvb-sci",
#endif
	.fops = &lxdvb_sci_fops,
};

static int dev_init(struct lxdvb_device *dev)
{
	struct lxdvb_sci *sci;
	struct te_device *tdev = get_te_device(dev);
	struct sci_dev *sci_dev;
	int ret;

	log_noti("sci_%s", __func__);

	sci_dev = sci_get_device(tdev);
	CHECK_ERROR(!sci_dev, return -EFAULT, "sci_get_device failed");

	sci = devm_kzalloc(&dev->pdev->dev, sizeof(*sci), GFP_KERNEL);
	CHECK_ERROR(!sci, return -ENOMEM, "no memory");

	sci->tx = kcalloc(1, MAX_CMD_APDU_LEN, GFP_KERNEL);
	CHECK_ERROR(!sci->tx, return -ENOMEM, "no memory");

	sci->rx = kcalloc(1, MAX_APDU_DATA_LEN, GFP_KERNEL);
	if (!sci->rx) {
		log_error("no memory");
		ret = -ENOMEM;
		goto err_rx_alloc;
	}

	mutex_init(&sci->ioctl_mutex);

	sci->dev = sci_dev;

	ret = dvb_register_device(&dev->adapter, &sci->dvbdev,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
				  &sci_dvbdev, sci, DVB_DEVICE_ACAS, 0);
#else
				  &sci_dvbdev, sci, DVB_DEVICE_ACAS);
#endif
	CHECK_ERROR(ret, goto err_dvb_reg, "dvb_register_device failed");

	init_debug(dev, sci);

	dev->sci = sci;

	return 0;

err_dvb_reg:
	kfree(sci->rx);
err_rx_alloc:
	kfree(sci->tx);

	return ret;
}

static void dev_release(struct lxdvb_device *dev)
{
	struct lxdvb_sci *sci;

	log_noti("%s", __func__);

	sci = dev->sci;

	if (sci->tx)
		kfree(sci->tx);
	if (sci->rx)
		kfree(sci->rx);

	dvb_unregister_device(sci->dvbdev);

	dev->sci = NULL;
}

static int dev_suspend(struct lxdvb_device *dev)
{
	return 0;
}

static int dev_resume(struct lxdvb_device *dev)
{
	return 0;
}

const struct lxdvb_sub_driver lxdvb_sci_driver = {
	.name = "lxdvb_sci",
	.init = dev_init,
	.release = dev_release,
	.suspend = dev_suspend,
	.resume = dev_resume,
};
