/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2018 by LG Electronics Inc.
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
 *  CI+ 1.4 Driver for linux dvb_ca(DEMUX&CA1/2/3)
 *
 *  @author	Ilkyu Kim (ilkyu.kim@lge.com)
 *  @version	1.0
 *  @date		2018-11-01
 *  @note		Additional information.
 */

#include "lxdvb_ci14.h"

#include "lxdvb_impl.h"
#include <lg1k/te/mem.h>
#include "te_dvb_ci14_kapi.h"
#include <lg1k/te/io.h>

#define _IOC_RW		(_IOC_READ | _IOC_WRITE)
#define DN_UNIT_SIZE (188 * 1000) // about 184 KB
#define UP_UNIT_SIZE (188 * 1000) // about 184 KB

#define CIPLUS_UP_BUFSIZE (33465 * 188) // 6 MB
#define CIPLUS_DN_BUFSIZE (66930 * 188)	// 12MB

static struct ci14_lge_control_param {
	u32 id;
	const char *name;
	u32 size;
	u32 dir;
} ci14_lge_control_params[] = {
	{CA_EXT_CID_PLUS14_INPUTSOURCE, "inputsource",
	 sizeof(struct ca_ext_source), _IOC_RW},
	{CA_EXT_CID_PLUS14_NUM_OF_PID_FILTER_PER_CH, "num_pidf", 0, _IOC_READ},
	{CA_EXT_CID_PLUS14_START_RECEIVING_DATA, "start_down", 0, _IOC_WRITE},
	{CA_EXT_CID_PLUS14_STOP_RECEIVING_DATA, "stop_down", 0, _IOC_WRITE},
	{CA_EXT_CID_PLUS14_START_SENDING_DATA, "start_up", 0, _IOC_WRITE},
	{CA_EXT_CID_PLUS14_STOP_SENDING_DATA, "stop_up", 0, _IOC_WRITE},
	{CA_EXT_CID_PLUS14_DOWNLOAD_MODE, "set_hostplay", 0, _IOC_RW},
	{CA_EXT_CID_PLUS14_ADD_PID_FILTER, "set_pidf", 0, _IOC_WRITE},
	{CA_EXT_CID_PLUS14_REMOVE_PID_FILTER, "free_pidf", 0, _IOC_WRITE},
	{CA_EXT_CID_PLUS14_CICAM_IN_BITRATE, "in_bitrate", 0, _IOC_READ},
	{CA_EXT_CID_PLUS14_CICAM_OUT_BITRATE, "out_bitrate", 0, _IOC_READ},
	{CA_EXT_CID_CTS_IO_BYPASS_MODE, "cam_bypass", 0, _IOC_RW},
};

static struct ci14_lge_control_param *get_ci14_lge_control_param(u32 id)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(ci14_lge_control_params); i++) {
		if (ci14_lge_control_params[i].id == id)
			return &ci14_lge_control_params[i];
	}

	return NULL;
}

static int get_kapi_user_ptr(void *priv, unsigned int cmd, void *arg,
			     struct te_ioctl_ptr_param *param)
{
	return 0;
}

static int get_user_ptr(void *priv, unsigned int cmd, void *arg,
			struct te_ioctl_ptr_param *param)
{
	int dir;
	struct ca_ext_control *p;
	struct ci14_lge_control_param *c;

	if (_IOC_TYPE(cmd) == TE_DVB_CI14_MAGIC)
		return get_kapi_user_ptr(priv, cmd, arg, param);

	switch (cmd) {
	case CA_EXT_S_CTL:
	case CA_EXT_G_CTL:
		p = arg;
		c = get_ci14_lge_control_param(p->id);
		dir = (cmd == CA_EXT_S_CTL) ? _IOC_WRITE : _IOC_READ;

		if (!c) {
			log_error("invalid ca_ext_control id(%u)", p->id);
			return -EINVAL;
		}

		if (c->size != p->size) {
			log_error("size %u != %u of ca_ext_control(%s)",
				  p->size, c->size, c->name);
			return -EINVAL;
		}

		if (!(c->dir & dir)) {
			log_error("invalid command of ca_ext_control(%s)",
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

static int convert_to_legacy_param(struct ca_ext_source *param,
				   enum lx_te_input_port *port,
				   bool *ip_play, bool *en)
{
	enum ca_src_type type = param->input_src_type;

	/* default vaule */
	*ip_play = false;
	*en = true;

	switch (type) {
	case CA_EXT_SRC_TYPE_IN_DEMOD:
		if (param->input_port_num > 0)
			return -EINVAL;
		*port = LX_TE_INPUT_PORT_TPI_IN_DEMOD0;
		break;
	case CA_EXT_SRC_TYPE_EXT_DEMOD:
		if (param->input_port_num > 1)
			return -EINVAL;
		*port = LX_TE_INPUT_PORT_TPI_EXT_INPUT0 + param->input_port_num;
		break;
	case CA_EXT_SRC_TYPE_MEM:
		if (param->input_port_num > 1)
			return -EINVAL;
		*port = LX_TE_INPUT_PORT_NONE;
		*ip_play= true;
		break;
	case CA_EXT_SRC_TYPE_NULL:
		*port = LX_TE_INPUT_PORT_NONE;
		*en = false;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static int convert_to_ca_ext_param(struct ca_ext_source *param,
				   enum lx_te_input_port port,
				   bool ip_play, bool en)
{
	if (!en) {
		param->input_src_type = CA_EXT_SRC_TYPE_NULL;
		param->input_port_num = 0;
	} else if (ip_play) {
		param->input_src_type = CA_EXT_SRC_TYPE_MEM;
		param->input_port_num = 0;
	} else {
		switch (port) {
		case LX_TE_INPUT_PORT_TPI_IN_DEMOD0:
			param->input_src_type = CA_EXT_SRC_TYPE_IN_DEMOD;
			param->input_port_num = 0;
			break;
		case LX_TE_INPUT_PORT_TPI_EXT_INPUT0:
			param->input_src_type = CA_EXT_SRC_TYPE_EXT_DEMOD;
			param->input_port_num = 0;
			break;
		case LX_TE_INPUT_PORT_TPI_EXT_INPUT1:
			param->input_src_type = CA_EXT_SRC_TYPE_EXT_DEMOD;
			param->input_port_num = 1;
			break;
		default:
			return -EINVAL;
		}
	}

	return 0;
}

static int set_input_config(struct lxdvb_ci14_channel *channel,
			    struct ca_ext_source *cfg)
{
	enum lx_te_input_port port;
	bool ip_play, en;

	log_noti("ci14 %s(%d,%d,%d)", __func__, channel->idx,
		 cfg->input_src_type, cfg->input_port_num);

	if (convert_to_legacy_param(cfg, &port, &ip_play, &en) < 0) {
		log_error("invalid setting: type%d num%d",
			  cfg->input_src_type, cfg->input_port_num);
		return -EINVAL;
	}

	return ciplus_set_input(channel->dev, port, ip_play, en);
}

static int get_input_config(struct lxdvb_ci14_channel *channel,
			    struct ca_ext_source *cfg)
{
	enum lx_te_input_port port;
	bool ip_play, en;

	ciplus_get_input(channel->dev, &port, &ip_play, &en);

	return convert_to_ca_ext_param(cfg, port, ip_play, en);
}

static int start_upload(struct lxdvb_ci14_channel *channel,
			struct lxdvb_ci14_up_fh *up)
{
	u32 sptr;
	int rc;

	up->mem_ctx = ciplus_get_mem_ctx(channel->ci14->dev);
	if (!up->mem_ctx)
		return -ENOMEM;

	sptr = te_mem_alloc(up->mem_ctx, CIPLUS_UP_BUFSIZE, "dvb_cipd.up");
	if (!sptr)
		return -ENOMEM;

	rc = te_hwbuf_init(&up->buf, sptr ,CIPLUS_UP_BUFSIZE, 0,
			   TE_BUF_FLAG_VMAP_CACHED | TE_BUF_FLAG_UPLOAD_MODULE);
	if (rc < 0)
		goto error_init;

	rc = ciplus_start_upload(channel->dev, &up->buf, &up->ip_dev);
	if (rc < 0)
		goto error_start;

	return 0;

error_start:
	te_hwbuf_release(&up->buf);
error_init:
	te_mem_free(up->mem_ctx, sptr);
	return rc;
}

static void stop_upload(struct lxdvb_ci14_channel *channel,
		       struct lxdvb_ci14_up_fh *up)
{
	u32 sptr = te_hwbuf_addr(&up->buf);

	ciplus_stop_upload(channel->dev, up->ip_dev);
	te_hwbuf_release(&up->buf);
	if (sptr)
		te_mem_free(up->mem_ctx, sptr);
}

static int start_download(struct lxdvb_ci14_channel *channel,
			  struct lxdvb_ci14_dn_fh *dn)
{
	u32 sptr;
	int rc;

	dn->mem_ctx = ciplus_get_mem_ctx(channel->ci14->dev);
	if (!dn->mem_ctx)
		return -ENOMEM;

	sptr = te_mem_alloc(dn->mem_ctx, CIPLUS_DN_BUFSIZE, "dvb_cipd.dn");
	if (!sptr)
		return -ENOMEM;

	rc = te_hwbuf_init(&dn->buf, sptr, CIPLUS_DN_BUFSIZE, 0,
			   TE_BUF_FLAG_VMAP_CACHED);
	if (rc < 0)
		goto error_init;

	rc = ciplus_start_download(channel->dev, &dn->buf, &dn->ip_dev);
	if (rc < 0)
		goto error_start;

	return 0;

error_start:
	te_hwbuf_release(&dn->buf);
error_init:
	te_mem_free(dn->mem_ctx, sptr);
	return rc;
}

static void stop_download(struct lxdvb_ci14_channel *channel,
		       struct lxdvb_ci14_dn_fh *dn)
{
	u32 sptr = te_hwbuf_addr(&dn->buf);

	ciplus_stop_download(channel->dev, dn->ip_dev);
	te_hwbuf_release(&dn->buf);
	if (sptr)
		te_mem_free(dn->mem_ctx, sptr);
}

static int set_host_player(struct lxdvb_ci14_channel *channel, bool host_player)
{
	ciplus_set_hostplayer(channel->dev, host_player);
	return 0;
}

static void get_host_player(struct lxdvb_ci14_channel *channel,
			    bool *host_player)
{
	ciplus_get_hostplayer(channel->dev, host_player);
}

static int set_debug_mode(struct lxdvb_ci14_channel *channel, bool mode)
{
	return ciplus_set_debug_mode(channel->ci14->dev, mode);
}

static void get_debug_mode(struct lxdvb_ci14_channel *channel, bool *mode)
{
	ciplus_get_debug_mode(channel->ci14->dev, mode);
}

static struct lxdvb_ci14_pidf
*alloc_free_pid_filter_slot(struct lxdvb_ci14_channel *channel)
{
	int i;
	struct lxdvb_ci14_pidf *f;

	for (i = 0; i < channel->num_pidf; i++) {
		f = &channel->pidf[i];
		if (!f->used) {
			f->used = true;
			return f;
		}
	}

	return ERR_PTR(-EBUSY);
}

static inline void release_pid_filter_slot(struct lxdvb_ci14_pidf *filter)
{
	filter->used = false;
}

static int set_pidf(struct lxdvb_ci14_fh *fh, s64 pid)
{
	struct lxdvb_ci14_channel *channel = fh->channel;
	struct lxdvb_ci14_pidf *f;
	int rc;

	if (pid < 0 || pid >= 0x1fff) {
		log_error("invalid pid 0x%llx", pid);
		return -EINVAL;
	}

	f = alloc_free_pid_filter_slot(channel);
	if (IS_ERR(f))
		return PTR_ERR(f);

	f->pid = pid;

	rc = ciplus_set_pid(channel->dev, pid, &f->filter);
	if (rc)
		goto fail;

	list_add_tail(&f->list, &fh->pid_filters);

	return 0;

fail:
	release_pid_filter_slot(f);
	return rc;
}

static struct lxdvb_ci14_pidf *
get_ci14_pid_filter(struct lxdvb_ci14_fh *fh, u16 pid)
{
	struct lxdvb_ci14_pidf *f;

	list_for_each_entry(f, &fh->pid_filters, list) {
		if (f->pid == pid)
			return f;
	}

	return NULL;
}

static int free_pidf(struct lxdvb_ci14_fh *fh, s64 pid)
{
	struct lxdvb_ci14_channel *channel = fh->channel;
	struct lxdvb_ci14_pidf *f;

	if (pid < 0 || pid >= 0x1fff) {
		log_error("invalid pid 0x%llx", pid);
		return -EINVAL;
	}

	f = get_ci14_pid_filter(fh, pid);
	if (!f) {
		log_warning("no match pid 0x%llx", pid);
		return -EINVAL;
	}

	ciplus_free_pid(channel->dev, f->filter);

	list_del(&f->list);
	release_pid_filter_slot(f);

	return 0;
}

static void clear_pidf_list(struct lxdvb_ci14_fh *fh)
{
	struct lxdvb_ci14_channel *channel = fh->channel;
	struct lxdvb_ci14_pidf *f;
	int cnt = 0;

	while (1) {
		f = list_first_entry_or_null(&fh->pid_filters,
					     struct lxdvb_ci14_pidf, list);

		if (!f)
			break;

		ciplus_free_pid(channel->dev, f->filter);

		list_del(&f->list);
		release_pid_filter_slot(f);
		cnt++;
	}

	if (cnt)
		log_noti("ch[%d] - clear %d pid filters", channel->idx, cnt);
}

static int set_control(struct lxdvb_ci14_fh *fh, struct ca_ext_control *control)
{
	struct lxdvb_ci14_channel *channel = fh->channel;
	int ret = 0;

	switch (control->id) {
	case CA_EXT_CID_PLUS14_INPUTSOURCE:
		ret = set_input_config(channel, (void __force *)control->ptr);
		break;
	case CA_EXT_CID_PLUS14_START_SENDING_DATA:
		if (fh->dn) {
			log_error("both up&down are not supported");
			return -EPERM;
		}
		if (fh->up) {
			log_error("upload already started");
			return -EBUSY;
		}
		fh->up = kmalloc(sizeof(struct lxdvb_ci14_up_fh), GFP_KERNEL);
		if (!fh->up)
			return -ENOMEM;

		ret = start_upload(channel, fh->up);
		if (ret < 0) {
			kfree(fh->up);
			fh->up = NULL;
			return ret;
		}
		break;
	case CA_EXT_CID_PLUS14_STOP_SENDING_DATA:
		if (!fh->up) {
			log_error("upload not started");
			return -EPERM;
		}
		stop_upload(channel, fh->up);
		kfree(fh->up);
		fh->up = NULL;
		break;
	case CA_EXT_CID_PLUS14_START_RECEIVING_DATA:
		if (fh->up) {
			log_error("both up&down are not supported");
			return -EPERM;
		}
		if (fh->dn) {
			log_error("download already started");
			return -EBUSY;
		}
		fh->dn = kmalloc(sizeof(struct lxdvb_ci14_dn_fh), GFP_KERNEL);
		if (!fh->dn)
			return -ENOMEM;
		ret = start_download(channel, fh->dn);
		if (ret < 0) {
			kfree(fh->dn);
			fh->dn = NULL;
			return ret;
		}
		break;
	case CA_EXT_CID_PLUS14_STOP_RECEIVING_DATA:
		if (!fh->dn) {
			log_error("download not started");
			return -EPERM;
		}
		stop_download(channel, fh->dn);
		kfree(fh->dn);
		fh->dn = NULL;
		break;
	case CA_EXT_CID_PLUS14_DOWNLOAD_MODE:
		ret = set_host_player(channel, control->value64 ? true : false);
		break;
	case CA_EXT_CID_PLUS14_ADD_PID_FILTER:
		ret = set_pidf(fh, control->value64);
		break;
	case CA_EXT_CID_PLUS14_REMOVE_PID_FILTER:
		ret = free_pidf(fh, control->value64);
		break;
	case CA_EXT_CID_CTS_IO_BYPASS_MODE:
		ret = set_debug_mode(channel, control->value64 ? true : false);
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}

static int get_control(struct lxdvb_ci14_fh *fh, struct ca_ext_control *control)
{
	struct lxdvb_ci14_channel *channel = fh->channel;
	int ret = 0;
	bool mode;

	switch (control->id) {
	case CA_EXT_CID_PLUS14_INPUTSOURCE: //TODO: CA_EXT_CID_INPUTSOURCE
		ret = get_input_config(channel, (void __force *)control->ptr);
		break;
	case CA_EXT_CID_PLUS14_DOWNLOAD_MODE:
		get_host_player(channel, &mode);
		control->value64 = mode ? 1 : 0;
		break;
	case CA_EXT_CID_PLUS14_NUM_OF_PID_FILTER_PER_CH:
		control->value64 = channel->num_pidf;
		break;
	case CA_EXT_CID_PLUS14_CICAM_IN_BITRATE:
	case CA_EXT_CID_PLUS14_CICAM_OUT_BITRATE:
		ret = ciplus_get_outputrates(channel->dev, &control->value64);
		break;
	case CA_EXT_CID_CTS_IO_BYPASS_MODE:
		get_debug_mode(channel, &mode);
		control->value64 = mode ? 1 : 0;
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}


static int do_kapi_ioctl(void *priv, unsigned int cmd, void *parg)
{
	struct lxdvb_ci14_fh *fh = priv;
	struct lxdvb_ci14_channel *channel = fh->channel;
	int ret;

	if (mutex_lock_interruptible(&channel->mutex))
		return -ERESTARTSYS;

	switch (cmd) {
	default:
		log_error("invalid command[0x%08x]. magic=0x%02X, num=%d",
			   cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));
		ret = -ENOTTY;
		break;
	}

	mutex_unlock(&channel->mutex);
	return ret;
}

/**
 * ioctl implementation.
 *
 * @file: File concerned.
 * @cmd: IOCTL command.
 * @arg: Associated argument.
 *
 * @return 0 on success, <0 on error.
 */
static int do_ioctl(void *priv, unsigned int cmd, void *parg)
{
	struct lxdvb_ci14_fh *fh = priv;
	struct lxdvb_ci14_channel *channel = fh->channel;
	int ret;

	if (_IOC_TYPE(cmd) == TE_DVB_CI14_MAGIC)
		return do_kapi_ioctl(priv, cmd ,parg);

	if (mutex_lock_interruptible(&channel->mutex))
		return -ERESTARTSYS;

	switch (cmd) {
	case CA_EXT_S_CTL:
		ret = set_control(fh, parg);
		break;

	case CA_EXT_G_CTL:
		ret = get_control(fh, parg);
		break;

	default:
		ret = -EINVAL;
		break;
	}

	mutex_unlock(&channel->mutex);

	if (ret < 0) {
		log_error("command[0x%08x]. magic=0x%02X, num=%d - error %d",
			   cmd, _IOC_TYPE(cmd), _IOC_NR(cmd), ret);
	}
	return ret;
}

/**
 * Wrapper for ioctl implementation.
 *
 * @inode: Inode concerned.
 * @file: File concerned.
 * @cmd: IOCTL command.
 * @arg: Associated argument.
 *
 * @return 0 on success, <0 on error.
 */
static long io_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct lxdvb_ci14_fh *fh = file->private_data;

	return te_ioctl_usercopy(cmd, arg, do_ioctl, get_user_ptr, fh);
}

/**
 * Implementation of write() syscall.
 *
 * @file: File structure.
 * @buf: Source buffer.
 * @count: Size of source buffer.
 * @ppos: Position in file (ignored).
 *
 * @return Number of bytes read, or <0 on error.
 */
static ssize_t io_write(struct file *file,
			const char __user *data, size_t count, loff_t *ppos)
{
	struct lxdvb_ci14_fh *fh = file->private_data;
	struct lxdvb_ci14_channel *channel = fh->channel;
	struct lxdvb_ci14_up_fh *up = fh->up;
	int ret = 0;

	if (!up)
		return -EPERM;

	if (channel->exit)
		return -ENODEV;

	if (mutex_lock_interruptible(&channel->mutex))
		return -ERESTARTSYS;

	ret = te_hwbuf_io_write(&up->buf, data, count,
				file->f_flags & O_NONBLOCK);
	if (ret < 0)
		log_error("ch[%d] error detected - %d", channel->idx, ret);

	mutex_unlock(&channel->mutex);

	return ret;
}

/**
 * Implementation of read() syscall.
 *
 * @file: File structure.
 * @buf: Destination buffer.
 * @count: Size of destination buffer.
 * @ppos: Position in file (ignored).
 *
 * @return Number of bytes read, or <0 on error.
 */
static ssize_t io_read(struct file *file, char __user *data,
		       size_t count, loff_t *ppos)
{
	struct lxdvb_ci14_fh *fh = file->private_data;
	struct lxdvb_ci14_channel *channel = fh->channel;
	struct lxdvb_ci14_dn_fh *dn = fh->dn;
	int ret = 0;

	if (!dn)
		return -EPERM;

	if (channel->exit)
		return -ENODEV;

	if (mutex_lock_interruptible(&channel->mutex))
		return -ERESTARTSYS;

	ret = te_hwbuf_io_read(&dn->buf, data, count,
			       file->f_flags & O_NONBLOCK);
	if (ret < 0) {
		if (ret == -EIO) {
			int err = te_hwbuf_error(&dn->buf);
			if (err == -ENOBUFS) {
				log_error("ch[%d] download overflow",
					  channel->idx);
				te_hwbuf_flush(&dn->buf);
			} else {
				log_error("ch[%d] error detected(err:%d)",
					  channel->idx, err);
			}
		} else {
			log_error("ch[%d] error detected - %d", channel->idx,
				  ret);
		}
	}

	mutex_unlock(&channel->mutex);
	return ret;
}

/**
 * Implementation of file open syscall.
 *
 * @inode: Inode concerned.
 * @file: File concerned.
 *
 * @return 0 on success, <0 on failure.
 */
static int io_open(struct inode *inode, struct file *file)
{
	struct dvb_device *dvbdev = file->private_data;
	struct lxdvb_ci14_channel *channel = dvbdev->priv;
	struct lxdvb_ci14_fh *fh;
	struct te_device *tdev = channel->ci14->tdev;

	fh = kzalloc(sizeof(struct lxdvb_ci14_fh), GFP_KERNEL);
	if (!fh)
		return -ENOMEM;

	if (mutex_lock_interruptible(&channel->mutex)) {
		kfree(fh);
		return -ERESTARTSYS;
	}

	te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_DVB_CI14);

	dvbdev->users++;

	fh->channel = channel;
	INIT_LIST_HEAD(&fh->pid_filters);

	file->private_data = fh;

	log_trace("ci14_open - fh(%p) users(%d)", fh, dvbdev->users);

	mutex_unlock(&channel->mutex);

	return 0;
}

/**
 * Implementation of file close syscall.
 *
 * @inode: Inode concerned.
 * @file: File concerned.
 *
 * @return 0 on success, <0 on failure.
 */
static int io_release(struct inode *inode, struct file *file)
{
	struct lxdvb_ci14_fh *fh = file->private_data;
	struct lxdvb_ci14_channel *channel = fh->channel;
	struct te_device *tdev = channel->ci14->tdev;

	log_trace("ci14_release - fh (%p)", fh);

	mutex_lock(&channel->mutex);

	if (fh->up) {
		stop_upload(channel, fh->up);
		kfree(fh->up);
	}
	if (fh->dn) {
		stop_download(channel, fh->dn);
		kfree(fh->dn);
	}

	clear_pidf_list(fh);

	kfree(fh);

	channel->dvbdev->users--;
	if (channel->dvbdev->users == 0 && channel->exit == 1) {
		mutex_unlock(&channel->mutex);
		wake_up(&channel->dvbdev->wait_queue);
	} else {
		mutex_unlock(&channel->mutex);
	}

	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_DVB_CI14);

	return 0;
}

/**
 * Implementation of poll() syscall.
 *
 * @file: File concerned.
 * @wait: poll wait table.
 *
 * @return Standard poll mask.
 */
static unsigned int io_poll(struct file *file, poll_table * wait)
{
	struct lxdvb_ci14_fh *fh = file->private_data;
	struct lxdvb_ci14_channel *channel = fh->channel;
	struct te_hwbuf *buf;
	unsigned int mask = 0;
	int rc;

	if (!fh->dn && !fh->up) {
		log_debug("(DEBUG) no up / dn");
		return POLLERR;
	}

	if (fh->dn) {
		buf = &(fh->dn->buf);

		rc = te_hwbuf_read_condition(buf);
		if (rc < 0) {
			if (rc == -EIO) {
				int err = te_hwbuf_error(buf);
				if (err == -ENOBUFS) {
					log_error("ch[%d] download overflow",
						  channel->idx);
				} else {
					log_error("ch[%d] buffer error(%d)",
						  channel->idx, err);
				}
				te_hwbuf_flush(buf); //TODO: check
			} else {
				log_error("ch[%d] error detected - %d",
					  channel->idx, rc);
			}

			return POLLERR;
		} else if (rc > 0) {
			mask |= (POLLIN | POLLRDNORM | POLLPRI);
		}

		poll_wait(file, te_hwbuf_wq(buf), wait);
	} else {
		buf = &(fh->up->buf);
		if (te_hwbuf_free_size(buf))
			mask |= (POLLOUT | POLLWRNORM | POLLPRI);

		poll_wait(file, te_hwbuf_wq(buf), wait);
	}

	return mask;
}

static const struct file_operations dvb_ci14_fops = {
	.owner = THIS_MODULE,
	.read = io_read,
	.write = io_write,
	.unlocked_ioctl = io_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = io_ioctl,
#endif
	.open = io_open,
	.release = io_release,
	.poll = io_poll,
	.llseek = noop_llseek,
};

static const struct dvb_device dvbdev_ci14 = {
	.priv = NULL,
	.readers = 1,
	.writers = 1,
#if defined(CONFIG_MEDIA_CONTROLLER_DVB)
	.name = "dvb-ci14",
#endif
	.fops = &dvb_ci14_fops,
};


/*
 * Initialisation/shutdown functions
 * return 0 when succeeds,
 * -EFAULT if fails to get ciplus device
 * -ENOMEM for no memory
 * log print when dvb_register_device fails
 */
static int dev_init(struct lxdvb_device *dev)
{
	int ret;
	struct lxdvb_ci14 *ci14;
	struct lxdvb_ci14_channel *channel;
	int num_ch, num_pidf;
	int i, j;
	struct ciplus_device *ciplus_device;
	struct te_device *tdev = get_te_device(dev);

	ciplus_device = ciplus_get_device(dev->subdev.tdev);
	if (ciplus_device == NULL)
		return -EFAULT;

	ret = ciplus_get_channel_info(ciplus_device, &num_ch, &num_pidf);
	if (ret)
		return ret;

	/* initialise the system data */
	ci14 = devm_kzalloc(&dev->pdev->dev,
			    sizeof(struct lxdvb_ci14) +
			    num_ch * sizeof(struct lxdvb_ci14_channel),
			    GFP_KERNEL);
	if (ci14 == NULL)
		return -ENOMEM;

	ci14->dev = ciplus_device;
	ci14->tdev = tdev;
	mutex_init(&ci14->mutex);
	spin_lock_init(&ci14->spinlock);
	ci14->num_channel = num_ch;

	for (i = 0; i < num_ch; i++) {
		channel = &ci14->channels[i];
		channel->idx = i;
		channel->num_pidf = num_pidf;
		channel->ci14 = ci14;
		channel->dev = ciplus_get_channel(ci14->dev, i);

		channel->pidf = vzalloc(num_pidf *
					sizeof(struct lxdvb_ci14_pidf));
		if (!channel->pidf) {
			ret = -ENOMEM;
			goto fail;
		}

		mutex_init(&channel->mutex);
		/* register the DVB device */
		ret = dvb_register_device(&dev->adapter, &channel->dvbdev,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
					  &dvbdev_ci14, channel, DVB_DEVICE_CA,0);
#else
					  &dvbdev_ci14, channel, DVB_DEVICE_CA);
#endif
		if (ret) {
			log_error("dvb_register_device failed[%d]", ret);
			vfree(channel->pidf);
			goto fail;
		}

	}

	dev->ci14 = ci14;

	log_noti("lxdvb ciplus init done");

	return 0;

fail:
	for (j = i -1; j >= 0; j--) {
		channel = &ci14->channels[j];
		dvb_unregister_device(channel->dvbdev);
		vfree(channel->pidf);
	}
	kfree(ci14);
	return ret;
}

static void dev_release(struct lxdvb_device *dev)
{
	struct lxdvb_ci14 *ci14 = dev->ci14;
	struct lxdvb_ci14_channel *channel;
	int i;

	log_debug("%s", __func__);

	for (i = 0; i < ci14->num_channel; i++) {
		channel = &ci14->channels[i];

		mutex_lock(&channel->mutex);
		channel->exit = true;
		mutex_unlock(&channel->mutex);

		if (channel->dvbdev->users > 0)
			wait_event(channel->dvbdev->wait_queue,
				   channel->dvbdev->users == 0);

		dvb_unregister_device(channel->dvbdev);
		vfree(channel->pidf);
	}

	//devm_kfree(&dev->pdev->dev, ci14);

	dev->ci14 = NULL;
}

static int dev_suspend(struct lxdvb_device *dev)
{
	struct te_device *tdev = get_te_device(dev);

	te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_DVB_CI14);

	return 0;
}

static int dev_resume(struct lxdvb_device *dev)
{
	struct te_device *tdev = get_te_device(dev);

	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_DVB_CI14);

	return 0;
}

const struct lxdvb_sub_driver lxdvb_ci14_driver = {
	.name = "lxdvb_ci14",
	.init = dev_init,
	.release = dev_release,
	.suspend = dev_suspend,
	.resume = dev_resume,
};
