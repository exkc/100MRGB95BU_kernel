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

#define DN_UNIT_SIZE (188 * 1000) // about 184 KB
#define UP_UNIT_SIZE (188 * 1000) // about 184 KB

#define CIPLUS_UP_BUFSIZE (33465 * 188) // 6 MB
#define CIPLUS_UP_POLL_INTERVAL	50	/* ms */
#define CIPLUS_DN_BUFSIZE (66930 * 188)	// 12MB
#define CIPLUS_DN_POLL_INTERVAL	20	/* ms */

#include <lg1k/te/dump.h>
#include <lg1k/te/mcu.h>
#include <lg1k/te/ipc.h>

#include "ciplus_impl.h"
//#include "ciplus_dvb.h"

enum {
	IPD_DEVICE_IDLE = 0,
	IPD_DEVICE_RUNNING,
	IPD_DEVICE_SUSPEND,
};

struct data_callback {
	struct list_head list;
	IPC_MSG_CIP_IP_DATA_T data_msg;
};

struct upload_cfg {
	struct te_hwbuf *data;
	u8 syncbyte;
};

struct download_cfg {
	struct te_hwbuf *data;
	u8 syncbyte;

	u32 flags; //future use
};

static DEFINE_MUTEX(ipd_lock);

/* isr callback */
static int ipc_receive_callback(void *msg, void *arg)
{
	struct ciplus_channel *channel;
	struct data_callback *callback;
	IPC_MSG_CIP_IP_DATA_T *data = msg;
	struct ciplus_device *dev = arg;

	channel = ciplus_get_channel(dev, data->ch);
	CHECK_ERROR(!channel, return -EINVAL, "invalid ch(%d)", data->ch);

	callback = kmalloc(sizeof(*callback), GFP_ATOMIC);
	CHECK_ERROR(!callback, return -ENOMEM, "kmalloc failed");

	callback->data_msg = *data;

	spin_lock(&channel->callback_lock);
	list_add_tail(&callback->list, &channel->callback_head);
	spin_unlock(&channel->callback_lock);

	queue_work(system_freezable_wq, &channel->callback_work);

	return 0;
}

static int overflow_callback(struct ciplus_channel *channel,
			     IPC_MSG_CIP_IP_DATA_T *msg)
{
	struct ciplus_ipd_dev *dev;
	struct te_hwbuf *buf;

	if (msg->dir == IPC_CIP_DIR_UPSTREAM) {
		dev = &(channel->up_dev);

		mutex_lock(&dev->mutex);
		if (dev->state == IPD_DEVICE_RUNNING) {
			buf = dev->buf;
			log_error("upload buffer overflow (possible?)");
			te_hwbuf_set_error(buf, -ENOBUFS);
		}
		mutex_unlock(&dev->mutex);
	} else if (msg->dir == IPC_CIP_DIR_DNSTREAM) {
		dev = &(channel->dn_dev);

		mutex_lock(&dev->mutex);

		if (dev->state == IPD_DEVICE_RUNNING) {
			buf = dev->buf;
			log_error("download buffer overflow");
			te_hwbuf_set_error(buf, -ENOBUFS);
		}

		mutex_unlock(&dev->mutex);
	} else {
		log_error("Unknown DIR[%d]", msg->dir);
	}

	return 0;

}

static void process_dn_datacallback(struct ciplus_channel *channel,
				    IPC_MSG_CIP_IP_DATA_T *msg)
{
#if 0
	struct ciplus_ipd_dev *dev;
	int rc;

	dev = &(channel->dn_dev);

	mutex_lock(&dev->mutex);
	if (dev->state == IPD_DEVICE_RUNNING) {
		rc = te_hwbuf_set_wptr(dev->buf, msg->buf_addr);
		CHECK_ERROR(rc < 0,, "Err(%d) in te_hwbuf_set_wptr(0x%08x)",
			    rc, msg->buf_addr);
	}
	mutex_unlock(&dev->mutex);
#endif
}

static void process_up_datacallback(struct ciplus_channel *channel,
				    IPC_MSG_CIP_IP_DATA_T *msg)
{
#if 0
	struct ciplus_ipd_dev *dev;
	int rc;

	dev = &(channel->up_dev);

	mutex_lock(&dev->mutex);
	if (dev->state == IPD_DEVICE_RUNNING) {
		rc = te_hwbuf_set_rptr(dev->buf, msg->buf_addr);
		CHECK_ERROR(rc < 0,, "Err(%d) in te_hwbuf_set_rptr(0x%08x)",
			    rc, msg->buf_addr);
	}
	mutex_unlock(&dev->mutex);
#endif
}

static void data_callback_work(struct work_struct *work)
{
	struct ciplus_channel *channel;
	struct data_callback *callback;
	IPC_MSG_CIP_IP_DATA_T *msg;
	unsigned long flag;

	channel = container_of(work, struct ciplus_channel, callback_work);

	while (1) {
		spin_lock_irqsave(&channel->callback_lock, flag);
		callback = list_first_entry_or_null(&channel->callback_head,
						    struct data_callback,
						    list);
		if (callback)
			list_del(&callback->list);	/* remove from the head */
		spin_unlock_irqrestore(&channel->callback_lock, flag);
		if (!callback)
			break;

		msg = &callback->data_msg;
		if (msg->status == IPC_DATA_STATUS_OK) {
			if (msg->dir == IPC_CIP_DIR_DNSTREAM) {
				process_dn_datacallback(channel, msg);
			} else if (msg->dir == IPC_CIP_DIR_UPSTREAM) {
				process_up_datacallback(channel, msg);
			}
		} else if (msg->status == IPC_DATA_STATUS_OVERFLOW_OVERLAPS_PTR
			   || msg->status == IPC_DATA_STATUS_OVERFLOW_NOT_ENOUGH_BUF) {
			overflow_callback(channel, msg);
		}

		kfree(callback);
	}
}

static int reset_data_callback_work(struct ciplus_channel *channel)
{
	unsigned long flag;
	struct data_callback *callback;
	int count = 0;

	spin_lock_irqsave(&channel->callback_lock, flag);
	while (1) {
		callback = list_first_entry_or_null(&channel->callback_head,
						    struct data_callback,
						    list);
		if (!callback)
			break;

		list_del(&callback->list);
		kfree(callback);
		count++;
	}
	spin_unlock_irqrestore(&channel->callback_lock, flag);

	if (count)
		log_noti("ch[%d] removed %d callbacks", channel->num, count);

	return count;
}

static void dn_read_callback(void *arg, u32 idx)
{
	struct ciplus_ipd_dev *dev = arg;
	phys_addr_t ptr;

	te_hwbuf_idx_to_paddr(dev->buf, idx, &ptr);
	TE_IPC_UpdateCIPLUSDownloadRptr(dev->ch, (u32)ptr);
}

static struct ciplus_ipd_dev *start_download(struct ciplus_channel *channel,
					     struct download_cfg *param)
{
	u32 start, size, unit_size;
	u8 syncbyte;
	struct te_hwbuf *buf = param->data;
	struct ciplus_ipd_dev *dev;
	int ret;

	dev = &(channel->dn_dev);
	syncbyte = param->syncbyte ? param->syncbyte : channel->syncbyte;

	log_noti("start download ch[%d] syncbyte[0x%02x]",
		 channel->num, syncbyte);

	mutex_lock(&dev->mutex);

	if (dev->state != IPD_DEVICE_IDLE) {
		log_error("dump[%d] is running", channel->num);
		goto error;
	}

	start = (u32)te_hwbuf_addr(buf);
	size = te_hwbuf_size(buf);
	unit_size = te_hwbuf_unit_size(buf);

	dev->ch = channel->num;
	dev->buf = param->data;
	dev->syncbyte = param->syncbyte;

	te_hwbuf_set_read_callback(buf, dn_read_callback, dev);
	ret = TE_IPC_StartCIPLUSDownload(channel->num, start, (start + size),
					 unit_size, syncbyte);
	CHECK_ERROR(ret, goto error, "Error in TE_IPC_StartCILUSDownload");

	dev->state = IPD_DEVICE_RUNNING;
	schedule_delayed_work(&dev->work,
			      msecs_to_jiffies(CIPLUS_DN_POLL_INTERVAL));

	mutex_unlock(&dev->mutex);

	return dev;

 error:
	mutex_unlock(&dev->mutex);

	return NULL;
}

static int ioc_start_download(struct ciplus_fh *fh, void *arg)
{
	struct download_cfg cfg;
	struct ciplus_ipd_dev *dev = NULL;
	struct te_hwbuf *buf;
	struct ciplus_dump_fh *dump;
	u32 sptr, size = CIPLUS_DN_BUFSIZE;

	CHECK_ERROR(fh->upload, return -EACCES,
		    "already upload[%d] is running (not permitted)",
		    fh->channel->num);

	dump = kmalloc(sizeof(*dump), GFP_KERNEL);
	CHECK_ERROR(!dump, return -ENOMEM, "no memory for user dump");

	buf = &dump->buf;

	sptr = te_mem_alloc(fh->dev->mem, size, "ioc.dn");
	CHECK_ERROR(!sptr, goto error, "Alloc failed(Download)");

	te_hwbuf_init(buf, sptr, size, 0, TE_BUF_FLAG_VMAP_CACHED);

	cfg.data = buf;
	cfg.flags = 0;
	cfg.syncbyte = 0;	//use default value

	dev = start_download(fh->channel, &cfg);
	CHECK_ERROR(!dev, goto error, "Error in start_download");

	dump->dev = dev;

	fh->dump = dump;

	return 0;

 error:
	if (sptr)
		te_mem_free(fh->dev->mem, sptr);
	if (dump)
		kfree(dump);

	return -EFAULT;
}

static int stop_download(struct ciplus_ipd_dev *dev)
{
	struct te_hwbuf *buf = dev->buf;
	int rc;

	log_noti("stop download ch[%d]", dev->ch);

	mutex_lock(&dev->mutex);

	if (dev->state == IPD_DEVICE_RUNNING) {
		cancel_delayed_work_sync(&dev->work);

		rc = TE_IPC_StopCIPLUSDownload(dev->ch);
		CHECK_ERROR(rc != 0,, "error in TE_IPC_StopCIPLUSDownload[%d]",
			    rc);

		te_hwbuf_set_read_callback(buf, NULL, NULL);
		te_hwbuf_set_error(buf, -ESHUTDOWN);

		dev->buf = NULL;
		dev->state = IPD_DEVICE_IDLE;
	}

	mutex_unlock(&dev->mutex);

	return 0;
}

static int ioc_reset_download(struct ciplus_fh *fh, void *arg)
{
	struct ciplus_dump_fh *dump;
	struct ciplus_ipd_dev *dev;
	struct download_cfg cfg;
	int rc;

	dump = fh->dump;
	CHECK_ERROR(!dump, return -EINVAL, "not started");

	rc = stop_download(dump->dev);
	CHECK_ERROR(rc != 0, return -EFAULT, "stop download failed (reset)");

	te_hwbuf_reset(&dump->buf);

	cfg.data = &dump->buf;
	cfg.flags = 0;
	cfg.syncbyte = 0;	//default

	dev = start_download(fh->channel, &cfg);
	CHECK_ERROR(!dev, return -EFAULT, "restart download failed (reset)");

	dump->dev = dev;

	return 0;
}

static void up_write_callback(void *arg, u32 idx)
{
	struct ciplus_ipd_dev *dev = arg;
	phys_addr_t ptr;

	te_hwbuf_idx_to_paddr(dev->buf, idx, &ptr);
	TE_IPC_UpdateCIPLUSUploadWptr(dev->ch, (u32)ptr);
}

static struct ciplus_ipd_dev *start_upload(struct ciplus_channel *channel,
					   struct upload_cfg *param)
{
	struct ciplus_ipd_dev *dev;
	struct te_hwbuf *buf = param->data;
	int rc;
	u32 start, size, unit_size;
	u8 syncbyte;

	dev = &(channel->up_dev);

	syncbyte = (param->syncbyte) ? param->syncbyte : channel->syncbyte;
	log_noti("start upload ch[%d] syncbyte[0x%02x]",
		 channel->num, syncbyte);

	mutex_lock(&dev->mutex);

	if (dev->state != IPD_DEVICE_IDLE) {
		log_error("upload[%d] is running", channel->num);
		goto error;
	}

	start = (u32)te_hwbuf_addr(buf);
	size = te_hwbuf_size(buf);
	unit_size = te_hwbuf_unit_size(buf);

	dev->ch = channel->num;
	dev->buf = param->data;

	te_hwbuf_set_write_callback(buf, up_write_callback, dev);
	rc = TE_IPC_StartCIPLUSUpload(channel->num, start, (start + size),
				      unit_size, syncbyte);
	CHECK_ERROR(rc != 0, goto error,
		    "Error in TE_IPC_StartCIPLUSUpload[%d]", rc);


	dev->state = IPD_DEVICE_RUNNING;
	dev->syncbyte = param->syncbyte;
	schedule_delayed_work(&dev->work,
			      msecs_to_jiffies(CIPLUS_UP_POLL_INTERVAL));

	mutex_unlock(&dev->mutex);

	return dev;

 error:
	mutex_unlock(&dev->mutex);

	return NULL;
}

static int ioc_start_upload(struct ciplus_fh *fh, void *arg)
{
	struct upload_cfg cfg;
	struct ciplus_ipd_dev *dev = NULL;
	struct te_hwbuf *buf;
	struct ciplus_upload_fh *upload;
	u32 sptr, size = CIPLUS_UP_BUFSIZE;

	CHECK_ERROR(fh->dump, return -EACCES,
		    "already download[%d] is running (not permitted)",
		    fh->channel->num);

	upload = kmalloc(sizeof(*upload), GFP_KERNEL);
	CHECK_ERROR(!upload, return -ENOMEM, "no memory for user upload");

	buf = &upload->buf;

	sptr = te_mem_alloc(fh->dev->mem, size, "ioc.up");
	CHECK_ERROR(!sptr, goto error, "Alloc failed(Upload)");

	te_hwbuf_init(buf, sptr, size, 0, TE_BUF_FLAG_VMAP_CACHED);

	cfg.data = buf;
	cfg.syncbyte = 0;	// use default value

	dev = start_upload(fh->channel, &cfg);
	CHECK_ERROR(!dev, goto error, "Error in start_upload");

	upload->dev = dev;

	fh->upload = upload;

	return 0;

 error:
	if (sptr)
		te_mem_free(fh->dev->mem, sptr);
	if (upload)
		kfree(upload);

	return -EFAULT;
}

static int stop_upload(struct ciplus_ipd_dev *dev)
{
	struct te_hwbuf *buf = dev->buf;
	int rc;

	log_noti("stop upload ch[%d]", dev->ch);

	mutex_lock(&dev->mutex);

	if (dev->state == IPD_DEVICE_RUNNING) {
		cancel_delayed_work_sync(&dev->work);

		rc = TE_IPC_StopCIPLUSUpload(dev->ch);
		CHECK_ERROR(rc != 0,, "error in TE_IPC_StopCIPLUsUpload[%d]",
			    rc);

		te_hwbuf_set_write_callback(buf, NULL, NULL);
		te_hwbuf_set_error(buf, -ESHUTDOWN);

		dev->buf = NULL;
		dev->state = IPD_DEVICE_IDLE;
	}

	mutex_unlock(&dev->mutex);

	return 0;
}


static int ioc_reset_upload(struct ciplus_fh *fh, void *arg)
{
	struct ciplus_upload_fh *upload;
	struct ciplus_ipd_dev *dev;
	struct upload_cfg cfg;
	int rc;

	upload = fh->upload;
	CHECK_ERROR(!upload, return -EINVAL, "not started");

	rc = stop_upload(upload->dev);
	CHECK_ERROR(rc != 0, return -EFAULT, "stop upload failed (reset)");

	te_hwbuf_reset(&upload->buf);

	cfg.data = &upload->buf;
	cfg.syncbyte = 0;	// default

	dev = start_upload(fh->channel, &cfg);
	CHECK_ERROR(!dev, return -EFAULT, "restart upload failed (reset)");

	upload->dev = dev;

	return 0;
}

static int recover_channel_ipd(struct ciplus_channel *channel)
{
	struct ciplus_ipd_dev *dev, *d;

	/* restart CI+ IPD path */
	/* Download recover */
	dev = &(channel->dn_dev);
	if (dev->state == IPD_DEVICE_SUSPEND)	//protect by ipd_lock
	{
		struct download_cfg cfg;

		te_hwbuf_reset(dev->buf);

		cfg.data = dev->buf;
		cfg.flags = 0;
		cfg.syncbyte = dev->syncbyte;
		if (dev->syncbyte) {
			log_warning("custom syncbyte: 0x%02x (DOWNLOAD)",
				    dev->syncbyte);
		}

		d = start_download(channel, &cfg);
		if (!d) {
			log_error("restart download failed");
			//return -EFAULT;
		}
	}

	/* Upload recover */
	dev = &(channel->up_dev);
	if (dev->state == IPD_DEVICE_SUSPEND) {
		struct upload_cfg cfg;

		te_hwbuf_reset(dev->buf);

		cfg.data = dev->buf;
		cfg.syncbyte = dev->syncbyte;
		if (dev->syncbyte) {
			log_warning("custom syncbyte: 0x%02x (UPLOAD)",
				    dev->syncbyte);
		}

		d = start_upload(channel, &cfg);
		if (!d) {
			log_error("restart upload failed");
			//return -EFAULT;
		}
	}

	return 0;
}

static int suspend_channel_ipd(struct ciplus_channel *channel)
{
	struct ciplus_ipd_dev *dev;
	int ret;

	/* Stop MCU Upload to suspend */
	dev = &(channel->up_dev);
	if (dev->state == IPD_DEVICE_RUNNING) {	//protect by ipd_lock
		ret = stop_upload(dev);
		CHECK_ERROR(ret != 0,, "suspend upload failed");

		dev->state = IPD_DEVICE_SUSPEND;
	}

	/* Stop MCU Download */
	dev = &(channel->dn_dev);
	if (dev->state == IPD_DEVICE_RUNNING) {
		ret = stop_download(dev);
		CHECK_ERROR(ret != 0,, "suspend download failed");

		dev->state = IPD_DEVICE_SUSPEND;
	}

	return 0;
}

static int mcu_recovery_pre_callback(void *arg)
{
	int i;
	struct ciplus_device *dev = arg;

	mutex_lock(&ipd_lock);
	for (i = 0; i < dev->num_channel; i++) {
		suspend_channel_ipd(&dev->channels[i]);
	}

	return 0;
}

static int mcu_recovery_post_callback(void *arg)
{
	int i;
	struct ciplus_device *dev = arg;

	for (i = 0; i < dev->num_channel; i++) {
		recover_channel_ipd(&dev->channels[i]);
	}
	mutex_unlock(&ipd_lock);

	return 0;
}

static int dump_start(struct te_dump_device *dev, struct te_dump_handle *h,
		      struct te_dump_cfg *cfg)
{
	struct ciplus_ipd_dev *d;
	struct ciplus_device *cdev = dev->private;
	struct ciplus_channel *channel;
	struct download_cfg param;

	mutex_lock(&ipd_lock);
	channel = ciplus_get_channel(cdev, cfg->ch);
	if (!channel) {
		log_error("no channel(%d)", cfg->ch);
		mutex_unlock(&ipd_lock);
		return -EIO;
	}

	param.data = cfg->data;
	param.syncbyte = cfg->ci14.syncbyte;
	param.flags = cfg->flags;

	d = start_download(channel, &param);
	h->dev_handle = d;
	mutex_unlock(&ipd_lock);

	return d ? 0 : -EIO;
}

static void dump_stop(struct te_dump_device *dev, struct te_dump_handle *h)
{
	if (h->dev_handle) {
		mutex_lock(&ipd_lock);
		stop_download(h->dev_handle);
		h->dev_handle = NULL;
		mutex_unlock(&ipd_lock);
	}
}

static struct te_dump_device dump_device = {
	.module = TE_DUMP_MODULE_CIPLUS,
	.start = dump_start,
	.stop = dump_stop,
};

static void up_work(struct work_struct *work)
{
	struct ciplus_ipd_dev *up;
	u32 rptr;

	up = container_of(to_delayed_work(work), struct ciplus_ipd_dev, work);

	TE_IPC_GetCIPLUSUploadRptr(up->ch, &rptr);
	te_hwbuf_set_rptr(up->buf, rptr);

	schedule_delayed_work(&up->work,
			      msecs_to_jiffies(CIPLUS_UP_POLL_INTERVAL));
}

static void dn_work(struct work_struct *work)
{
	struct ciplus_ipd_dev *dn;
	u32 wptr;

	dn = container_of(to_delayed_work(work), struct ciplus_ipd_dev, work);

	TE_IPC_GetCIPLUSDownloadWptr(dn->ch, &wptr);
	te_hwbuf_set_wptr(dn->buf, wptr);

	schedule_delayed_work(&dn->work,
			      msecs_to_jiffies(CIPLUS_DN_POLL_INTERVAL));
}

static int init_channel_ipd(struct ciplus_channel *channel)
{
	struct ciplus_ipd_dev *up, *dn;

	up = &(channel->up_dev);
	up->ch = channel->num;
	up->state = IPD_DEVICE_IDLE;
	spin_lock_init(&up->spinlock);
	mutex_init(&up->mutex);
	INIT_DELAYED_WORK(&up->work, up_work);

	dn = &(channel->dn_dev);
	dn->ch = channel->num;
	dn->state = IPD_DEVICE_IDLE;
	spin_lock_init(&dn->spinlock);
	mutex_init(&dn->mutex);
	INIT_DELAYED_WORK(&dn->work, dn_work);

	INIT_LIST_HEAD(&channel->callback_head);
	spin_lock_init(&channel->callback_lock);
	INIT_WORK(&channel->callback_work, data_callback_work);

	return 0;

}

static int suspend(struct ciplus_device *dev)
{
	int i;
	struct ciplus_channel *channel;

	/* disconnect data callback */
	TE_IPC_RegisterCIPLUSDataCallback(NULL, NULL);

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];
		suspend_channel_ipd(channel);

		/* remove remained callback works */
		reset_data_callback_work(channel);
	}

	return 0;
}

static int resume(struct ciplus_device *dev)
{
	int i;
	struct ciplus_channel *channel;

	/* reconnect filter callback */
	TE_IPC_RegisterCIPLUSDataCallback(ipc_receive_callback, dev);

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];
		recover_channel_ipd(channel);
	}

	return 0;
}

static int do_ioctl(void *priv, unsigned int cmd, void *arg)
{
	const struct ciplus_ioctl_info ioctl_func[] = {
		IOC_INFO(CIPLUS_IPD_START_DOWNLOAD, ioc_start_download),
		IOC_INFO(CIPLUS_IPD_RESET_DOWNLOAD, ioc_reset_download),
		IOC_INFO(CIPLUS_IPD_START_UPLOAD, ioc_start_upload),
		IOC_INFO(CIPLUS_IPD_RESET_UPLOAD, ioc_reset_upload),
	};

	return ciplus_do_ioctl(priv, cmd, arg, ipd_lock, ioctl_func);
}

ssize_t ciplus_ipd_ioc_read(struct file *file, char __user *data, size_t size,
			loff_t *off)
{
	struct ciplus_fh *fh = file->private_data;
	struct ciplus_dump_fh *dump;
	struct ciplus_ipd_dev *dev;
	struct te_hwbuf *buf;
	int ret;

	dump = fh->dump;
	CHECK_ERROR(!dump, return 0, "not started");

	dev = dump->dev;
	buf = &dump->buf;

	ret = te_hwbuf_io_read(buf, data, size, file->f_flags & O_NONBLOCK);
	if (ret < 0) {
		if (ret == -EIO) {
			int err = te_hwbuf_error(buf);
			if (err == -ENOBUFS) {
				log_error("ch[%d] download overflow", dev->ch);
				te_hwbuf_flush(buf);
			} else {
				log_error("ch[%d] error detected(err:%d)",
					  dev->ch, err);
			}
		} else {
			log_error("ch[%d] error detected - %d", dev->ch, ret);
		}
	}
	return ret;
}

ssize_t ciplus_ipd_ioc_write(struct file *file,
			 const char __user *data, size_t size, loff_t *off)
{
	struct ciplus_fh *fh = file->private_data;
	struct ciplus_upload_fh *upload;
	struct ciplus_ipd_dev *dev;
	struct te_hwbuf *buf;
	int rc;

	upload = fh->upload;
	CHECK_ERROR(!upload, return 0, "not started");

	dev = upload->dev;
	buf = &upload->buf;

	rc = te_hwbuf_io_write(buf, data, size, file->f_flags & O_NONBLOCK);
	if (rc < 0)
		log_error("ch[%d] error detected - %d", dev->ch, rc);

	return rc;
}

unsigned int ciplus_ipd_ioc_poll(struct file *file, poll_table * wait)
{
	struct ciplus_fh *fh = file->private_data;
	struct ciplus_dump_fh *dump;
	struct ciplus_ipd_dev *dev;
	struct te_hwbuf *buf;
	unsigned int mask = 0;
	int rc;

	dump = fh->dump;
	CHECK_ERROR(!dump, return POLLERR, "not started");

	/* Download poll */
	if (dump) {
		dev = dump->dev;
		buf = &dump->buf;

		rc = te_hwbuf_read_condition(buf);
		if (rc < 0) {
			if (rc == -EIO) {
				int err = te_hwbuf_error(buf);
				if (err == -ENOBUFS) {
					log_error("ch[%d] download overflow",
						  dev->ch);
				} else {
					log_error("ch[%d] buffer error(%d)",
						  dev->ch, err);
				}
				te_hwbuf_flush(buf);
			} else {
				log_error("ch[%d] error detected - %d", dev->ch,
					  rc);
			}

			return POLLERR;
		} else if (rc > 0) {
			mask |= (POLLIN | POLLRDNORM | POLLPRI);
		}
		poll_wait(file, te_hwbuf_wq(buf), wait);
	} else {
		log_debug("(DEBUG) no download");
		return POLLERR;
	}

	/* Upload poll: Not supported */
	return mask;
}

static void close(struct ciplus_fh *fh)
{
	struct ciplus_dump_fh *dump = fh->dump;
	struct ciplus_upload_fh *upload = fh->upload;
	u32 sptr;

	mutex_lock(&ipd_lock);

	if (dump) {
		sptr = te_hwbuf_addr(&dump->buf);	//for free allocated memory

		stop_download(dump->dev);

		te_hwbuf_release(&dump->buf);

		if (sptr)
			te_mem_free(fh->dev->mem, sptr);

		kfree(dump);
	}

	if (upload) {
		sptr = te_hwbuf_addr(&upload->buf);

		stop_upload(upload->dev);

		te_hwbuf_release(&upload->buf);

		if (sptr)
			te_mem_free(fh->dev->mem, sptr);

		kfree(upload);
	}

	mutex_unlock(&ipd_lock);
}

static int init(struct ciplus_device *dev)
{
	int i, ret;

	for (i = 0; i < dev->num_channel; i++) {
		struct ciplus_channel *channel = &dev->channels[i];

		ret = init_channel_ipd(channel);
		CHECK_ERROR(ret, return ret, "Error in init_channel_ipd");
	}

	TE_IPC_RegisterCIPLUSDataCallback(ipc_receive_callback, dev);
	te_mcu_register_rcallback(get_te_device(dev),
				  TE_MCU_FUNC_TYPE_CIPLUS,
				  mcu_recovery_pre_callback,
				  mcu_recovery_post_callback, dev);

	dump_device.private = dev;
	ret = te_dump_register_device(&dump_device);
	CHECK_ERROR(ret, return ret, "Error in te_dump_register_device");

	return 0;
}

static void release(struct ciplus_device *dev)
{

}

static const struct ciplus_ioctl ioctl_ipd = {
	.magic = CIPLUS_IOC_IPD_MAGIC,
	.func = do_ioctl,
//      .get_user_param = io_ioctl_param,
};

const struct ciplus_sub_driver ciplus_ipd_driver = {
	.name = "ciplus_ipd",
	.init = init,
	.release = release,
	.suspend = suspend,
	.resume = resume,

	.close = close,
	.ioctl = &ioctl_ipd,
};

int ciplus_start_upload(struct ciplus_channel *channel,
			struct te_hwbuf *buf,
			struct ciplus_ipd_dev **pdev)
{
	struct upload_cfg cfg;
	struct ciplus_ipd_dev *dev = NULL;
	int rc;

	mutex_lock(&ipd_lock);

	cfg.data = buf;
	cfg.syncbyte = 0;

	dev = start_upload(channel, &cfg);
	if (!dev) {
		rc = -EFAULT;
		log_error("error in start_upload");
		goto error_start;
	}

	*pdev = dev;

	mutex_unlock(&ipd_lock);
	return 0;

error_start:
	mutex_unlock(&ipd_lock);
	return rc;
}

void ciplus_stop_upload(struct ciplus_channel *channel,
			struct ciplus_ipd_dev *dev)
{
	mutex_lock(&ipd_lock);
	stop_upload(dev);
	mutex_unlock(&ipd_lock);
}

int ciplus_start_download(struct ciplus_channel *channel,
			  struct te_hwbuf *buf,
			  struct ciplus_ipd_dev **pdev)
{
	struct download_cfg cfg;
	struct ciplus_ipd_dev *dev = NULL;
	int rc;

	mutex_lock(&ipd_lock);

	cfg.data = buf;
	cfg.flags = 0;
	cfg.syncbyte = 0;

	dev = start_download(channel, &cfg);
	if (!dev) {
		rc = -EFAULT;
		log_error("error in start_download");
		goto error_start;
	}

	*pdev = dev;

	mutex_unlock(&ipd_lock);
	return 0;

error_start:
	mutex_unlock(&ipd_lock);
	return rc;
}

void ciplus_stop_download(struct ciplus_channel *channel,
			  struct ciplus_ipd_dev *dev)
{
	mutex_lock(&ipd_lock);
	stop_download(dev);
	mutex_unlock(&ipd_lock);
}

