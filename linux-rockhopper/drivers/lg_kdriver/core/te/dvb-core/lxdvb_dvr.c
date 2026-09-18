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
 *  @author	Kyungseok Hyun (ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2018-01-26
 *  @note		Additional information.
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

#include <lg1k/te/dump.h>

#include "lxdvb_impl.h"
#include "lxdvb_demux.h"
#include "lxdvb_dvr.h"

#define DVR_DN_BUF_SIZE		0x0107f640	/* 16.49MB LCM(192*188)*1917 */
#define DVR_DN_SHARED_BUF_SIZE	0x00bff280	/* 11.99MB LCM(192*188)*1394 */
#define DVR_DN_SHARED_ONLY_BUF_SIZE 0x009FDD40	/* 9.99MB LCM(192*188)*1139*/

#define DVR_UP_BUF_SIZE		0x005FF940	/* 5.998MB LCM(192,188)*697 */

#define NORMAL_UPLOAD_SPEED	100
#define SIZE_OF_CERT_DATA	32

#define _IOC_RW		(_IOC_READ | _IOC_WRITE)

#ifndef PVR_EXT_CID_SET_PKTLEN
#define PVR_EXT_CID_SET_PKTLEN 4
#endif

#define TIMESTAMP_USER_SIZE 4
#define LAST_TIMESTAMP_POS (TIMESTAMP_USER_SIZE - 1)
#define TP_SYNCBYTE 0x47

struct dvr_lge_control_param {
	u32 id;
	const char *name;
	u32 size;
	u32 dir;
};

static int dvr_ext_set_upload_rate(struct lxdvb_dvr_up *up, int speed);

static const struct dvr_lge_control_param dvr_lge_control_params[] = {
	{PVR_EXT_CID_RESET, "reset_upload", 0, _IOC_WRITE},
	{PVR_EXT_CID_SETRATE, "set_upload_rate", 0, _IOC_RW},	//need get rate?
	{PVR_EXT_CID_CERT, "write_download_data", SIZE_OF_CERT_DATA, _IOC_RW},
	{PVR_EXT_CID_SET_PKTLEN, "set_packet_length", 0, _IOC_WRITE},
};

static const struct dvr_lge_control_param *get_dvr_lge_control_param(u32 id)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(dvr_lge_control_params); i++) {
		if (dvr_lge_control_params[i].id == id)
			return &dvr_lge_control_params[i];
	}

	return NULL;
}

static const char *get_dvr_state_str(enum lxdvb_dvr_state state)
{
	const struct te_val_str list[] = {
		{LXDVB_DVR_STATE_IDLE, "idle"},
		{LXDVB_DVR_STATE_OPEN, "open"},
		{LXDVB_DVR_STATE_START, "start"},
	};
	return find_match_string(list, state, "unknown");
}

static enum lx_pvr_up_dest convert_idx_to_pvr_dest(int idx)
{
	switch (idx) {
	case 0:
		return LX_PVR_UP_DEST_SDEC_CH0;
	case 1:
		return LX_PVR_UP_DEST_SDEC_CH1;
	case 2:
		return LX_PVR_UP_DEST_SDEC_CH2;
	case 3:
		return LX_PVR_UP_DEST_SDEC_CH3;
	default:
		return LX_PVR_UP_DEST_ANY;
	}
}

static void buf_free(struct te_mem_ctx *mem, struct te_hwbuf *hbuf)
{
	te_phys_addr_t addr;

	addr = (te_phys_addr_t)te_hwbuf_addr(hbuf);

	te_hwbuf_release(hbuf);
	te_mem_free(mem, addr);
}

static int buf_alloc(struct te_hwbuf *hbuf, struct te_mem_ctx *mem, u32 size,
		     u32 flag)
{
	te_phys_addr_t addr;
	int ret;

	addr = te_mem_alloc(mem, size, "dvb_dvr");
	CHECK_ERROR(!addr, return -ENOMEM, "error in te_mem_alloc(0x%x)", size);

	ret = te_hwbuf_init(hbuf, addr, size, 0, flag);
	if (ret) {
		log_error("te_hwbuf_init failed(%d)", ret);
		goto err_hwbuf;
	}

	return 0;

err_hwbuf:
	te_mem_free(mem, addr);
	return -EIO;

}

static int dvr_dn_open(struct lxdvb_dvr_fh *fh,
		       struct lxdvb_dvr_channel *channel)
{
	struct lxdvb_dvr *dvr = channel->dvr;
	struct pvr_device *pvr_dev = dvr->pvr_dev;
	struct lxdvb_dvr_dn *dn = &channel->dn;
	struct te_hwbuf *hbuf;
	struct te_mem_ctx *mem;
	struct pvr_dn *dev;
	int ret, src, idx, use_shared_mem;
	u32 size;

	log_noti("%s(idx:%d)", __func__, channel->idx);

	CHECK_ERROR(dn->state != LXDVB_DVR_STATE_IDLE, return -EBUSY,
		    "already used");

	dev = pvr_dn_open(pvr_dev, -1);
	if (IS_ERR(dev)) {
		ret = PTR_ERR(dev);
		log_error("pvr_dn_open failed %d", ret);
		return ret;
	}

	src = channel->idx;
	idx = pvr_dn_get_index(dev);

	hbuf = &dn->hbuf;
	mem = dvr->mem[idx];

	use_shared_mem = pvr_is_shared_mem(pvr_dev);
	if (use_shared_mem) {
		size = DVR_DN_SHARED_ONLY_BUF_SIZE;
	} else {
		if (idx == 0)
			size = DVR_DN_BUF_SIZE;
		else
			size = DVR_DN_SHARED_BUF_SIZE;
	}

	ret = buf_alloc(hbuf, mem, size, TE_BUF_FLAG_VMAP_CACHED);
	CHECK_ERROR(ret, goto err_alloc, "buf_alloc fail(size:0x%x)", size);

// TODO: remove after bringup
#if CONFIG_LX_BOARD_FPGA
	dn->valid = true;
#else
	dn->valid = false;
#endif
	dn->dev = dev;
	dn->src = src;
	dn->mem = mem;
	dn->rsize = 0;
	dn->pkt_len = TIME_TS_PACKET_SIZE;
	dn->state = LXDVB_DVR_STATE_START;
	dn->usb_ci_mode = false;

	pvr_dn_init(dev, src, TIME_TS_PACKET_SIZE, hbuf);
	pvr_dn_start(dev);

	fh->channel = channel;
	fh->dn = dn;

	return 0;
err_alloc:
	pvr_dn_close(dev);

	return ret;
}

static int _up_start(struct lxdvb_dvr_up *up)
{
	pvr_up_init(up->dev, &up->hbuf, up->pkt_len, up->dst);
	pvr_up_start(up->dev);
#if 0
	/* default upload speed is 10MBytes/sec
	Need to adjust the playing speed? */

	if (up->pkt_len == TS_PACKET_SIZE)
		pvr_up_set_speed(up->dev, 2*1024*1024);

#endif
	up->state = LXDVB_DVR_STATE_START;
	if (up->speed != NORMAL_UPLOAD_SPEED) {
		dvr_ext_set_upload_rate(up, up->speed);
	}

	return 0;
}

static int dvr_up_open(struct lxdvb_dvr_fh *fh,
		       struct lxdvb_dvr_channel *channel)
{
	struct lxdvb_dvr *dvr = channel->dvr;
	struct pvr_device *pvr_dev = dvr->pvr_dev;
	struct pvr_up *dev;
	enum lx_pvr_up_dest dest;
	struct te_hwbuf *hbuf;
	struct te_mem_ctx *mem;
	int ret, idx;
	struct lxdvb_dvr_up *up = &channel->up;
	u32 flag;

	log_noti("%s(idx:%d)", __func__, channel->idx);

	CHECK_ERROR(up->state != LXDVB_DVR_STATE_IDLE, return -EBUSY,
		    "already used");

	dev = pvr_up_open(pvr_dev, -1);
	if (IS_ERR(dev)) {
		ret = PTR_ERR(dev);
		return ret;
	}

	idx = pvr_up_get_index(dev);
	hbuf = &up->hbuf;
	mem = dvr->mem[idx];
	flag = (TE_BUF_FLAG_VMAP_CACHED | TE_BUF_FLAG_UPLOAD_MODULE);

	ret = buf_alloc(hbuf, mem, DVR_UP_BUF_SIZE, flag);
	CHECK_ERROR(ret, goto err_alloc, "buf_alloc fail");

	dest = convert_idx_to_pvr_dest(channel->idx);

	lxdvb_demux_set_dvr_idx(channel->dmx, idx);

	up->dst = dest;
	up->state = LXDVB_DVR_STATE_OPEN;
	up->speed = NORMAL_UPLOAD_SPEED;
	up->dev = dev;
	up->mem = mem;
	up->wsize = 0;
	up->pkt_len = TIME_TS_PACKET_SIZE;
	up->usb_ci_mode = false;

	fh->channel = channel;
	fh->up = up;

	return 0;
err_alloc:
	pvr_up_close(dev);

	return ret;
}

static int dvr_open(struct inode *inode, struct file *file)
{
	struct dvb_device *dvbdev = file->private_data;
	struct lxdvb_dvr_channel *channel = dvbdev->priv;
	struct lxdvb_dvr *dvr = channel->dvr;
	struct te_device *tdev = dvr->tdev;
	struct lxdvb_dvr_fh *fh;
	int ret;

	fh = kzalloc(sizeof(*fh), GFP_KERNEL);
	if (!fh)
		return -ENOMEM;

	te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_DVB_DVR);

	if ((file->f_flags & O_ACCMODE) == O_RDONLY) {
		ret = dvr_dn_open(fh, channel);
		CHECK_ERROR(ret != 0, goto error, "dvr_dn_open fail");

	} else if ((file->f_flags & O_ACCMODE) == O_WRONLY) {
		ret = dvr_up_open(fh, channel);
		CHECK_ERROR(ret != 0, goto error, "dvr_up_open fail");

	} else {
		ret = -EOPNOTSUPP;
		goto error;
	}

	file->private_data = fh;

	dvbdev->users++;

	log_trace("dvr_open - ch(%d) fh(%p) users(%d)\n",
		  channel->idx, fh, dvbdev->users);

	return 0;
error:
	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_DVB_DVR);
	kfree(fh);

	return ret;
}

static int dvr_release(struct inode *inode, struct file *file)
{
	struct lxdvb_dvr_fh *fh = file->private_data;
	struct lxdvb_dvr_channel *channel = fh->channel;
	struct dvb_device *dvbdev = channel->dvbdev;
	struct te_device *tdev = channel->dvr->tdev;

	if (fh->dn) {
		struct lxdvb_dvr_dn *dn = fh->dn;
		struct pvr_dn *dev;

		log_noti("%s(dn-idx:%d)", __func__, channel->idx);

		dev = dn->dev;
		dn->dev = NULL;

		pvr_dn_close(dev);
		buf_free(dn->mem, &dn->hbuf);

		dn->state = LXDVB_DVR_STATE_IDLE;
		fh->dn = NULL;

	} else {
		struct lxdvb_dvr_up *up = fh->up;
		struct pvr_up *dev;

		log_noti("%s(up-idx:%d)", __func__, channel->idx);

		dev = up->dev;
		up->dev = NULL;

		if (up->usb_ci_mode) { //recover to normal
			lxdvb_demux_set_usb_ci_mode(channel->dmx, false);
			up->usb_ci_mode = false;
		}

		pvr_up_close(dev);
		buf_free(up->mem, &up->hbuf);
		lxdvb_demux_set_dvr_idx(channel->dmx, -1);

		up->state = LXDVB_DVR_STATE_IDLE;
		fh->up = NULL;
	}

	kfree(fh);
	dvbdev->users--;
	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_DVB_DVR);

	log_trace("dvr_release - users(%d)\n", dvbdev->users);

	return 0;
}

static void debug_dump_write(struct dvr_debug_dump *dump,
			     const char __user *data, u32 size)
{
	int rc;

	mutex_lock(&dump->mutex);

	if (dump->running == false || te_hwbuf_error(dump->buf)) {
		mutex_unlock(&dump->mutex);
		return;
	}

	rc = te_hwbuf_cwrite_user(dump->buf, data, size);
	if (rc < 0)
		te_hwbuf_set_error(dump->buf, rc);

	mutex_unlock(&dump->mutex);
}

static int check_usb_ci_by_timestamp(const char __user *buf, size_t len,
				     bool *is_usb)
{
	int i, rc = 0;
	char p;

	*is_usb = true;

	for (i = 0; i < len; i += TIME_TS_PACKET_SIZE) {
		if (i + TIMESTAMP_USER_SIZE >= len) {
			log_error("not aligned to %d (len = %lu)",
				  TIME_TS_PACKET_SIZE, len);
			rc = -EINVAL;
			*is_usb = false;
			break;
		}

		if (copy_from_user(&p, buf + i + LAST_TIMESTAMP_POS, 1)) {
			log_error("copy_from_user failed[%d]", i);
			rc = -EFAULT;
			*is_usb = false;
			break;
		}

		if (p != 0x0) {
			*is_usb = false;
			break;
		}
	}

	return rc;
}

// TODO: wakeup when BLOCK mode
static ssize_t dvr_write(struct file *file, const char __user *buf,
			 size_t count, loff_t *ppos)
{
	struct lxdvb_dvr_fh *fh = file->private_data;
	struct te_hwbuf *hbuf;
	struct lxdvb_dvr_up *up = fh->up;
	int rc;
	int ret;
	bool detect_usb;

	if (!up)
		return -EINVAL;

	if (up->state == LXDVB_DVR_STATE_OPEN) {
		// TODO: change log level after verification.
		log_noti("start upload now(%d)", up->pkt_len);

		ret = _up_start(up);
		CHECK_ERROR(ret, return ret, "fail to start upload");
	}

	hbuf = &up->hbuf;

	mutex_lock(&up->mutex);
	up->writing = 1;
	mutex_unlock(&up->mutex);

	if (up->pkt_len == TIME_TS_PACKET_SIZE && !up->usb_ci_mode)  {
		rc = check_usb_ci_by_timestamp(buf, count, &detect_usb);
		CHECK_ERROR(rc , , "error in recover_usb_ci_syncbyte(%d)", rc);

		if (detect_usb) {
			log_warning("usb ci recording detected");
			lxdvb_demux_set_usb_ci_mode(fh->channel->dmx, true);
			up->usb_ci_mode = true;
		}
	}

	ret = te_hwbuf_io_write(hbuf, buf, count, file->f_flags & O_NONBLOCK);
	if (ret < 0) {
		log_error("ch[%d] te_hwbuf_io_write error(%d)",
			  fh->channel->idx, ret);
	} else {
		up->wsize += ret;
		debug_dump_write(&up->dump, buf, ret);
	}
	up->writing = 0;

	return ret;
}

/* Mark PVR results as USB CI by discard eight lower timestamp bits
 * See SICDTV-11565 to see why eight bits are sufficient
 */
static int change_usb_ci_timestamp(char __user *buf, size_t len)
{
	int i, rc = 0;
	const char p = 0;

	if (len < TIME_TS_PACKET_SIZE)
		return -EAGAIN;

	for (i = 0; i < len; i += TIME_TS_PACKET_SIZE) {
		if (i + TIMESTAMP_USER_SIZE >= len) {
			log_error("not aligned to %d (len = %lu)",
				  TIME_TS_PACKET_SIZE, len);
			rc = -EINVAL;
			goto exit;
		}

#if 0 // template for 2bit discard
		if (copy_from_user(&p, buf + i + LAST_TIMESTAMP_POS, 1)) {
			log_error("copy_from_user failed[%d]", i);
			rc = -EFAULT;
			goto exit;
		}

		p &= 0xFC;
#endif
		//discard timestamp 8 bits for indicate usb ci
		if (copy_to_user(buf + i + LAST_TIMESTAMP_POS, &p, 1)) {
			log_error("copy_to_user failed[%d]", i);
			rc = -EFAULT;
			goto exit;
		}
	}

exit:
	return rc;
}

static ssize_t dvr_read(struct file *file, char __user *buf, size_t count,
			loff_t *ppos)
{
	struct lxdvb_dvr_fh *fh = file->private_data;
	struct lxdvb_dvr_channel *channel;
	struct te_hwbuf *hbuf;
	struct lxdvb_dvr_dn *dn = fh->dn;
	int ret, rc, err;
	bool usb_ci;

	if (!dn)
		return -EINVAL;

	if (dn->valid == false) {
		log_error("invalid user\n");
		return -EIO;
	}

	mutex_lock(&dn->mutex);
	dn->reading = 1;
	mutex_unlock(&dn->mutex);

	hbuf = &dn->hbuf;
	ret = te_hwbuf_io_read(hbuf, buf, count, file->f_flags & O_NONBLOCK);
	if (ret < 0) {
		channel = fh->channel;
		if (ret == -EIO) {
			err = te_hwbuf_error(hbuf);
			if (err == -ENOBUFS) {
				log_error("ch[%d] download overflow",
					  channel->idx);
				te_hwbuf_flush(hbuf);
			} else {
				log_error("ch[%d] error detected(err:%d)",
					  channel->idx, err);
			}
		} else if (ret == -EWOULDBLOCK) {
			/* non_block mode only. no stream to read */
		} else {
			log_error("ch[%d] te_hwbuf_io_read failed(ret:%d)",
				  channel->idx, ret);
		}
	} else {
		dn->rsize += ret;
		if (!dn->usb_ci_mode) {
			lxdvb_demux_check_usb_ci_recording(fh->channel->dmx,
							   &usb_ci);
			if (usb_ci) {
				log_warning("changes to usb_ci_mode");
				dn->usb_ci_mode = true;
			}
		}

		if (dn->usb_ci_mode) {
			rc = change_usb_ci_timestamp(buf, ret);
			CHECK_ERROR(rc, , "error in change_usb_ci_synyte(%d)",
				    rc);
		}

		debug_dump_write(&dn->dump, buf, ret);
	}

	dn->reading = 0;

	return ret;
}

static int dvr_ext_set_upload_rate(struct lxdvb_dvr_up *up, int speed)
{
	int rc;

	log_noti("%s(%s),speed:%d", __func__,
		get_dvr_state_str(up->state), speed);

	if (up->state < LXDVB_DVR_STATE_START) {
		up->speed = speed;

		return 0;
	}

	if (speed == 0) {
		rc = pvr_up_pause(up->dev);
		CHECK_ERROR(rc != 0, return rc, "err in pvr_up_pause(%d)", rc);
	} else {
		enum lx_pvr_up_mode mode;

		if (speed == NORMAL_UPLOAD_SPEED) {
			mode = LX_PVR_UPMODE_NORMAL;
		} else if (speed == NORMAL_UPLOAD_SPEED * 2) {
			mode = LX_PVR_UPMODE_FAST2X;
		} else if (speed > 0 && speed < NORMAL_UPLOAD_SPEED) {
			mode = LX_PVR_UPMODE_SLOW;
		} else {
			mode = LX_PVR_UPMODE_TRICK_MODE;
		}
		rc = pvr_up_set_mode(up->dev, mode);
		CHECK_ERROR(rc != 0, return rc,
			    "err in pvr_up_set_mode(%d)", rc);

		if (up->speed == 0)
			pvr_up_resume(up->dev);
	}
	up->speed = speed;

	return rc;

}

static int dvr_ext_set_upload_reset(struct lxdvb_dvr_up *up)
{
	int rc;

	log_noti("%s (writing:%d)", __func__, up->writing);

	if (up->writing == 1)
		return -EBUSY;

	if (up->state < LXDVB_DVR_STATE_START)
		return 0;

	rc = pvr_up_reset(up->dev);

	return rc;
}

static int dvr_ext_set_upload_pktlen(struct lxdvb_dvr_up *up, int pktlen)
{
	// TODO: change log level after verification.

	log_noti("%s (pktlen:%d->%d)", __func__, up->pkt_len, pktlen);

	if (up->state != LXDVB_DVR_STATE_OPEN) {
		log_error("can't change pakcet length");
		return -EIO;
	}

	if (pktlen != TS_PACKET_SIZE && pktlen != TIME_TS_PACKET_SIZE) {
		log_error("invalid pakcet length(%d)", pktlen);
		return -EPERM;
	}

	if (pktlen != up->pkt_len) {
		up->pkt_len = pktlen;
	}

	return 0;
}

static int dvr_ext_set_download_pktlen(struct lxdvb_dvr_dn *dn, int pktlen)
{
	int ret;

	log_noti("%s(%d)", __func__, pktlen);

	if (pktlen != TS_PACKET_SIZE && pktlen != TIME_TS_PACKET_SIZE) {
		log_error("invalid packet length(%d)", pktlen);
		return -EPERM;
	}

	if (pktlen != dn->pkt_len) {
		if (dn->state == LXDVB_DVR_STATE_START) {
			if (dn->reading == 1) {
				log_error("dvr_read is in progress.");
				return -EBUSY;
			}
			pvr_dn_stop(dn->dev);
			ret = pvr_dn_init(dn->dev, dn->src, pktlen, &dn->hbuf);
			if (ret) {
				log_error("pvr_dn_init failed(%d)", ret);
				return ret;
			}

			pvr_dn_start(dn->dev);
		}
		dn->pkt_len = pktlen;
	}

	return 0;

}

static int dvr_ext_write_data(struct lxdvb_dvr_dn *dn,
			      u8 *data, int size)
{
	int ret;

	log_noti("%s", __func__);

	ret = pvr_dn_write_data(dn->dev, data, size);
	if (!ret)
		dn->valid = true;

	return ret;
}

static int dvb_dvr_set_up_control(struct lxdvb_dvr_up *up,
				  struct pvr_ext_control *control)
{
	int ret;

	if (mutex_lock_interruptible(&up->mutex))
		return -ERESTARTSYS;

	switch (control->id) {
	case PVR_EXT_CID_SETRATE:
		ret = dvr_ext_set_upload_rate(up, (u32)control->value64);
		break;
	case PVR_EXT_CID_RESET:
		ret = dvr_ext_set_upload_reset(up);
		break;
	case PVR_EXT_CID_SET_PKTLEN:
		ret = dvr_ext_set_upload_pktlen(up, (u32)control->value64);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	mutex_unlock(&up->mutex);

	return ret;
}

static int dvb_dvr_set_dn_control(struct lxdvb_dvr_dn *dn,
				  struct pvr_ext_control *control)
{
	int ret;

	if (mutex_lock_interruptible(&dn->mutex))
		return -ERESTARTSYS;

	switch (control->id) {
	case PVR_EXT_CID_CERT:
		ret = dvr_ext_write_data(dn, (void __force *)control->ptr, control->size);
		break;
	case PVR_EXT_CID_SET_PKTLEN:
		ret = dvr_ext_set_download_pktlen(dn, (u32)control->value64);
		break;
	default:
		ret = -EINVAL;
		break;

	}
	mutex_unlock(&dn->mutex);

	return ret;
}

static int dvb_dvr_get_up_control(struct lxdvb_dvr_up *up,
				  struct pvr_ext_control *control)
{
	int ret;
	if (mutex_lock_interruptible(&up->mutex))
		return -ERESTARTSYS;

	switch (control->id) {
	default:
		ret = -EINVAL;
		break;
	}
	mutex_unlock(&up->mutex);

	return ret;
}

static int dvb_dvr_get_dn_control(struct lxdvb_dvr_dn *dn,
				  struct pvr_ext_control *control)
{
	int ret;

	if (mutex_lock_interruptible(&dn->mutex))
		return -ERESTARTSYS;

	switch (control->id) {
	default:
		ret = -EINVAL;
		break;
	}
	mutex_unlock(&dn->mutex);

	return ret;
}

static int dvr_do_ioctl(void *priv, unsigned int cmd, void *parg)
{

	struct lxdvb_dvr_fh *fh = priv;
	int ret;

	switch (cmd) {
	case PVR_EXT_S_CTL:
		if (fh->up) {
			ret = dvb_dvr_set_up_control(fh->up, parg);
		} else {
			ret = dvb_dvr_set_dn_control(fh->dn, parg);
		}
		break;
	case PVR_EXT_G_CTL:
		if (fh->up) {
			ret = dvb_dvr_get_up_control(fh->up, parg);
		} else {
			ret = dvb_dvr_get_dn_control(fh->dn, parg);
		}
		break;
	default:
		ret = -EINVAL;
		break;
	}

	if (ret < 0) {
		log_error("command[0x%08x]. magic=0x%02X, num=%d - error %d",
			   cmd, _IOC_TYPE(cmd), _IOC_NR(cmd), ret);
	}

	return ret;
}

static int dvr_get_user_ptr(void *priv, unsigned int cmd, void *arg,
			    struct te_ioctl_ptr_param *param)
{
	int dir;
	struct pvr_ext_control *p;
	const struct dvr_lge_control_param *c;

	switch (cmd) {
	case PVR_EXT_S_CTL:
	case PVR_EXT_G_CTL:
		p = arg;
		c = get_dvr_lge_control_param(p->id);
		dir = (cmd == PVR_EXT_S_CTL) ? _IOC_WRITE : _IOC_READ;

		if (!c) {
			log_error("invalid dvr_ext_control id(%u)", p->id);
			return -EINVAL;
		}

		if (c->size != p->size) {
			log_error("size %u != %u of pvr_ext_control(%s)",
				  p->size, c->size, c->name);
			return -EINVAL;
		}

		if (!(c->dir & dir)) {
			log_error("invalid command of pvr_ext_control(%s)",
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

static long dvr_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	return te_ioctl_usercopy(cmd, arg, dvr_do_ioctl, dvr_get_user_ptr,
				 file->private_data);
}

static unsigned int dvr_poll(struct file *file, poll_table * wait)
{
	struct lxdvb_dvr_fh *fh = file->private_data;
	struct te_hwbuf *hbuf;
	unsigned int mask = 0;

	if (fh->dn) {
		hbuf = &fh->dn->hbuf;

		poll_wait(file, te_hwbuf_wq(hbuf), wait);

		if (te_hwbuf_avail_size(hbuf) > 0) {
			mask |= (POLLIN | POLLRDNORM | POLLPRI);
		}
	} else {
		hbuf = &fh->up->hbuf;

		poll_wait(file, te_hwbuf_wq(hbuf), wait);

		if (te_hwbuf_free_size(hbuf)) {
			mask |= (POLLOUT | POLLWRNORM | POLLPRI);
		}
	}
	return mask;
}

static const struct file_operations dvr_fops = {
	.owner = THIS_MODULE,
	.read = dvr_read,
	.write = dvr_write,
	.unlocked_ioctl = dvr_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = dvr_ioctl,
#endif
	.open = dvr_open,
	.release = dvr_release,
	.poll = dvr_poll,
	.llseek = default_llseek,
};

static const struct dvb_device dvbdev = {
	.priv = NULL,
	.readers = 1,
	.writers = 1,
#if defined(CONFIG_MEDIA_CONTROLLER_DVB)
	.name = "dvb-dvr",
#endif
	.fops = &dvr_fops
};

/* debug functions */
#define dprintf(fmt, args...)	seq_printf(m, fmt, ##args)
#define dprintf1(fmt, args...)	dprintf("       " fmt, ##args)

static void debug_buf_status(struct te_hwbuf *hbuf, struct seq_file *m)
{
	u32 asize, tsize;

	dprintf1("range(0x%x--0x%x)\n", (u32)te_hwbuf_addr(hbuf),
		 (u32)te_hwbuf_eaddr(hbuf));
	dprintf1("w:0x%x, r:0x%x\n", (u32)te_hwbuf_wptr(hbuf),
		 (u32)te_hwbuf_rptr(hbuf));

	asize = te_hwbuf_avail_size(hbuf);
	tsize = te_hwbuf_size(hbuf);
	dprintf1("used:%d(%s) total:%d(%s)\n",
		 asize, te_get_readable_size(asize),
		 tsize, te_get_readable_size(tsize));
}

static void debug_channel_dvr_status(struct lxdvb_dvr_channel *channel,
				     struct seq_file *m)
{
	struct lxdvb_dvr_up *up = &channel->up;
	struct lxdvb_dvr_dn *dn = &channel->dn;

	if (up->state != LXDVB_DVR_STATE_IDLE) {
		dprintf("[UP %d] state:%s, pktlen:%d, speed:%d\n",
			pvr_up_get_index(up->dev), get_dvr_state_str(up->state),
			up->pkt_len, up->speed);

		debug_buf_status(&up->hbuf, m);
	}
	if (dn->state != LXDVB_DVR_STATE_IDLE) {
		dprintf("[DN %d] state:%s src:%d\n",
			pvr_dn_get_index(dn->dev), get_dvr_state_str(dn->state),
			dn->src);

		debug_buf_status(&dn->hbuf, m);
	}
}

static int debug_channel_status(struct te_debug_item *item, struct seq_file *m)
{
	int i;
	struct lxdvb_dvr *dvr = item->private;

	for (i = 0; i < dvr->num_channel; i++) {
		debug_channel_dvr_status(&dvr->channels[i], m);
	}

	return 0;
}

static const struct te_debug_item_info debug_list[] = {
	DBGITM_SHOW("status", debug_channel_status, 0),
};

static void show_dvr_status(struct lxdvb_dvr_channel *channel,
			    struct seq_file *m)
{
	struct lxdvb_dvr_dn *dn = &channel->dn;
	struct lxdvb_dvr_up *up = &channel->up;
	u32 asize, tsize;

	dprintf("down-ch%d\n", channel->idx);
	dprintf("status : %s\n", get_dvr_state_str(dn->state));

	if (dn->state != LXDVB_DVR_STATE_IDLE) {
		tsize = te_hwbuf_size(&dn->hbuf);
		asize = te_hwbuf_avail_size(&dn->hbuf);
		dprintf("total:%d(%s), occupy:%d(%s)\n",
			tsize, te_get_readable_size(tsize),
			asize, te_get_readable_size(asize));
		dprintf("read size:%u(%s)\n", dn->rsize,
			te_get_readable_size(dn->rsize));
	}
	dprintf("\n");

	dprintf("up-ch%d\n", channel->idx);
	dprintf("status : %s\n", get_dvr_state_str(up->state));
	if (up->state != LXDVB_DVR_STATE_IDLE) {
		tsize = te_hwbuf_size(&up->hbuf);
		asize = te_hwbuf_avail_size(&up->hbuf);
		dprintf("buffer : total %d(%s), occupy %d(%s)\n",
			tsize, te_get_readable_size(tsize),
			asize, te_get_readable_size(asize));
		dprintf("play speed: %d\n", up->speed);
		dprintf("write size:%u(%s)\n", up->wsize,
			te_get_readable_size(up->wsize));
	}
	dprintf("\n");

}

/* webos linuxtv proc */

enum {
	DEBUG_ID_STATUS = 0,
	DEBUG_ID_BW_CAPA,
	DEBUG_ID_ES_TYPE,
};

static int proc_show_status(struct lxdvb_proc_item *item, struct seq_file *m)
{
	int i;
	struct lxdvb_dvr *dvr = item->private;

	switch (item->flags) {
	case DEBUG_ID_STATUS:
		for (i = 0; i < dvr->num_channel; i++)
			show_dvr_status(&dvr->channels[i], m);

		break;
	case DEBUG_ID_BW_CAPA:
	case DEBUG_ID_ES_TYPE:
		dprintf("0\n");
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static struct lxdvb_proc_item_info proc_list[] = {
	LXDVB_PROC_ITEM_SHOW("status", proc_show_status, DEBUG_ID_STATUS),
	LXDVB_PROC_ITEM_SHOW("prop_bw_capa", proc_show_status,
	DEBUG_ID_BW_CAPA),
	LXDVB_PROC_ITEM_SHOW("prop_es_type", proc_show_status,
	DEBUG_ID_ES_TYPE),
};

static int debug_dump_start(struct te_dump_device *dev,
			    struct te_dump_handle *h, struct te_dump_cfg *cfg)
{
	struct lxdvb_dvr *dvr = dev->private;
	u8 ch = cfg->ch;
	struct dvr_debug_dump *dump;

	if (ch >= dvr->num_channel) {
		log_error("invalid channel(%d)", ch);
		return -EPERM;
	}

	if (cfg->dvr.module == TE_DUMP_DVR_UP)
		dump = &dvr->channels[ch].up.dump;
	else
		dump = &dvr->channels[ch].dn.dump;

	if (dump->running == true) {
		log_error("already started\n");
		return -EBUSY;
	}

	dump->buf = cfg->data;
	dump->running = true;

	h->dev_handle = dump;

	return 0;
}

static void debug_dump_stop(struct te_dump_device *dev,
			    struct te_dump_handle *h)
{
	struct dvr_debug_dump *dump = h->dev_handle;

	mutex_lock(&dump->mutex);
	dump->running = false;
	mutex_unlock(&dump->mutex);

	h->dev_handle = NULL;
}

static struct te_dump_device dump_device = {
	.module = TE_DUMP_MODULE_DVR,
	.start = debug_dump_start,
	.stop = debug_dump_stop,
};

static void init_debug(struct lxdvb_device *dev, struct lxdvb_dvr *dvr)
{
	int rc;

	dump_device.private = dvr;
	rc = te_dump_register_device(&dump_device);
	CHECK_ERROR(rc < 0, return, "Error in te_dump_register_device");

	dvr->debug_dir = te_debug_create_dir("dvr", dev->debug_dir);
	CHECK_ERROR(!dvr->debug_dir, return, "te_debug_create_dir failed");
	debug_create_item_files(debug_list, dvr, dvr->debug_dir);

	dvr->proc_dir = lxdvb_proc_create_dir("dvb_dvr", NULL);
	CHECK_ERROR(!dvr->proc_dir, return, "lxdvb_proc_create_dir failed");
	lxdvb_proc_create_files(proc_list, dvr, dvr->proc_dir);
}

static int init_dvr_channel(struct lxdvb_device *dev,
			    struct lxdvb_dvr_channel *channel)
{
	int rc;

	rc = dvb_register_device(&dev->adapter, &channel->dvbdev,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
				 &dvbdev, channel, DVB_DEVICE_DVR, 0);
#else
				 &dvbdev, channel, DVB_DEVICE_DVR);
#endif
	if (rc)
		goto err_register;

	return 0;

err_register:
	return rc;
}

static void release_dvr_channel(struct lxdvb_dvr_channel *channel)
{
	dvb_unregister_device(channel->dvbdev);
}

static int dev_init(struct lxdvb_device *dev)
{
	struct lxdvb_dvr *dvr;
	struct lxdvb_dvr_channel *channel;
	struct te_device *tdev = get_te_device(dev);
	struct pvr_device *pvr = pvr_get_device(tdev);
	struct te_mem_ctx *mem;
	const char *name[2];
	u8 num_channel;
	int i, ret, use_shared_mem;

	log_noti("%s", __func__);

	if (!pvr) {
		log_error("pvr device not exist\n");
		return -ENODEV;
	}

	if (!dev->dmx) {
		log_error("no demux device\n");
		return -ENODEV;
	}

	num_channel = dev->dmx->num_channel;

	dvr = devm_kzalloc(&dev->pdev->dev,
			   sizeof(*dvr) +
			   num_channel * sizeof(struct lxdvb_dvr_channel),
			   GFP_KERNEL);
	if (!dvr)
		return -ENOMEM;

	dvr->tdev = tdev;
	dvr->num_channel = num_channel;
	dvr->pvr_dev = pvr;

	for (i = 0; i < num_channel; i++) {
		channel = &dvr->channels[i];
		channel->idx = i;
		channel->dvr = dvr;
		channel->dmx = &dev->dmx->channels[i];
		ret = init_dvr_channel(dev, channel);

		mutex_init(&channel->up.mutex);
		mutex_init(&channel->dn.mutex);
		mutex_init(&channel->up.dump.mutex);
		mutex_init(&channel->dn.dump.mutex);
	}

	use_shared_mem = pvr_is_shared_mem(pvr);
	if (use_shared_mem) {
		name[0] = TE_MEM_SHARED_NAME;
		name[1] = TE_MEM_SHARED_NAME;
	} else {
		name[0] = TE_MEM_PVR_NAME;
		name[1] = TE_MEM_SHARED_NAME;
	}

	for (i = 0; i < 2; i++) {
		mem = te_mem_open(name[i]);
		if (!mem) {
			log_error("te_mem_open failed (%s)\n", name[i]);
			if (i == 1)
				te_mem_close(dvr->mem[0]);

			return -EIO;
		}
		dvr->mem[i] = mem;
	}
	dev->dvr = dvr;

	init_debug(dev, dvr);

	return 0;
}

static void dev_release(struct lxdvb_device *dev)
{
	struct lxdvb_dvr *dvr = dev->dvr;
	struct lxdvb_dvr_channel *channel;
	int i;

	log_noti("%s", __func__);

	for (i = 0; i < 2; i++) {
		te_mem_close(dvr->mem[i]);
	}

	for (i = 0; i < dvr->num_channel; i++) {
		channel = &dvr->channels[i];
		release_dvr_channel(channel);
	}

}

static int dev_suspend(struct lxdvb_device *dev)
{
	struct te_device *tdev = get_te_device(dev);

	te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_DVB_DVR);

	return 0;
}

static int dev_resume(struct lxdvb_device *dev)
{
	struct te_device *tdev = get_te_device(dev);

	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_DVB_DVR);

	return 0;
}

const struct lxdvb_sub_driver lxdvb_dvr_driver = {
	.name = "lxdvb_dvr",
	.init = dev_init,
	.release = dev_release,
	.suspend = dev_suspend,
	.resume = dev_resume,
};
