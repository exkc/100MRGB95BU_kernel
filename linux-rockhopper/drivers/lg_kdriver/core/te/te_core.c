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
 *  @date		2018-10-17
 *  @note		Additional information.
 */

#include <lg1k/te/mcu.h>
#include <lg1k/te/ipc.h>

#include "te_impl.h"

//#include "lgbus_cfg.h"

#define inode_to_te_device(inode) \
	container_of(inode->i_cdev, struct te_device, cdev)

static const struct te_sub_driver *sub_drivers[] = {
	&te_debug_driver,
	&te_mem_driver,
	&te_reg_driver,
	&te_timer_driver,
	&te_irq_driver,
	&te_dumper_driver,
	&te_clk_driver,
	&te_io_driver,
	&te_dump_driver,
	&te_mcu_driver,
};

static DEFINE_MUTEX(node_lock);
static DEFINE_MUTEX(fwload_lock);

static int reset_gstcc(u8 idx)
{
	int ret;
	struct te_config *cfg = te_get_config();

	if (!cfg->no_stcc_bug) {
		ret = TE_REG_ResetGstcc(idx);
		CHECK_ERROR(ret, return ret, "Error in TE_REG_ResetGstcc");

		ret = TE_REG_SetGstccConf(idx, 1, 300, TRUE);	/* 90Khz */
		CHECK_ERROR(ret, return ret, "Error in TE_REG_SetGstccConf");
	} else {
		//nothing to do
	}

	return 0;
}

static int init_hw(struct te_device *dev)
{
	int i, ret;
	struct te_config *cfg = te_get_config();

	/* Hardware related initialization */
	TE_REG_CTOP_SetInitValue();
	TE_REG_SetBeAxiEndian(BE_AXI_BIG_ENDIAN, BE_AXI_LITTLE_ENDIAN);
	te_reg_dumper_set_init_value();

	for (i = 0; i < cfg->clk.num_gstcc; i++) {
		ret = reset_gstcc(i);
		if (ret)
			log_error("Failed to reset gstcc[%d]", i);
	}

	return 0;
}

static int init_mem_protector(void)
{
	return 0;
}

static void init_debug(struct te_device *dev)
{

}

static int load_mcu_binary(struct te_device *dev, LX_TE_MCU_FWLOAD_T *params)
{
	int ret = -EIO;
	void *data = NULL;
	void __user *user_ptr;

	CHECK_PARAM(params->data == NULL, "data is null");
	CHECK_PARAM(params->size == 0, "size is 0");
	CHECK_PARAM(params->size > (512 * 1024), "huge size[%d]", params->size);

	data = vmalloc(params->size);
	CHECK_ERROR(!data, return -ENOMEM, "vmalloc(%d) failed\n",
		    params->size);

	user_ptr = te_ioctl_get_user_ptr(params->data);
	ret = copy_from_user(data, user_ptr, params->size);
	if (ret) {
		log_error("copy_from_user failed\n");
		ret = -EFAULT;
		goto exit;
	}

	ret = te_mcu_fwload(dev, params->mcu, data, params->size);

 exit:
	vfree(data);

	return ret;
}

static int get_mcu_status(struct te_device *dev, struct lx_te_get_mcu_status *s)
{
	struct te_config *cfg = te_get_config();
	bool mcu_ready, ipc_ready;
	u32 ver;
	int i, rc;

	s->count = cfg->num_mcu;
	s->include_demod = cfg->include_demod;
	for (i = 0; i < s->count; i++) {
		struct lx_te_mcu_info *info = &s->mcu[i];

		info->status = LX_TE_MCU_STATUS_NOT_READY;
		rc = te_mcu_get_status(dev, i, &mcu_ready, &ipc_ready, &ver);
		if (rc)
			return rc;

		if (mcu_ready) {
			if (ipc_ready) {
				info->status = LX_TE_MCU_STATUS_READY;
				info->fw_ver = ver;
			} else {
				info->status = LX_TE_MCU_STATUS_LOADED;
			}
		}
	}

	return 0;
}

static int check_and_load_mcu_binary(struct te_device *dev,
				     struct lx_te_mcu_fwload *params)
{
	int rc;
	struct lx_te_get_mcu_status s;

	rc = get_mcu_status(dev, &s);
	if (rc)
		return rc;

	if (params->mcu > s.count)
		return -EFAULT;

	/* Check MCU is loaded by other applications */
	if (s.mcu[params->mcu].status != LX_TE_MCU_STATUS_NOT_READY) {
		log_noti("MCU%d is already loaded, skip", params->mcu);
		return 0;
	}

	return load_mcu_binary(dev, params);
}

static int ioctl_func(void *priv, unsigned int cmd, void *arg)
{
	int ret;
	struct te_fh *fh = priv;
	union {
		void *value;
		LX_TE_STREAM_TYPE_T *stream_type;
		LX_TE_TPI_CFG_PARAM_T *tpi_cfg;
		LX_TE_TPI_STATUS_PARAM_T *tpi_status;
		LX_TE_INPUT_PORT_CONNECT_T *port_connect;
	} p;

	p.value = arg;

	switch (cmd) {
	case TE_IOC_MCU_FWLOAD:
		mutex_lock(&fwload_lock); //mutex for preventing deadlock
		ret = load_mcu_binary(fh->dev, arg);
		mutex_unlock(&fwload_lock);
		break;

	case TE_IOC_MCU_FW_CHECK_N_LOAD:
		mutex_lock(&fwload_lock); //mutex for preventing deadlock
		ret = check_and_load_mcu_binary(fh->dev, arg);
		mutex_unlock(&fwload_lock);
		break;

	case TE_IOC_GET_MCU_STATUS:
		ret = get_mcu_status(fh->dev, arg);
		break;

	case TE_IOC_GET_REG:
		ret = TE_REG_GetValue(arg);
		break;

	case TE_IOC_SET_REG:
		ret = TE_REG_SetValue(arg);
		break;

	case TE_IOC_SET_ENGINE:
		ret = te_set_engine_mode(fh->dev, *p.stream_type);
		break;

	case TE_IOC_CFG_TPI:
		ret = te_config_tpi(fh->dev, p.tpi_cfg->port, p.tpi_cfg->value);
		break;

	case TE_IOC_GET_TPI_STATUS:
		ret = te_get_tpi_status(fh->dev, p.tpi_status->port,
					p.tpi_status->value);
		break;

	case TE_IOC_CONNECT_INPUT_PORT:
		ret = te_connect_input_port(fh->dev, p.port_connect->port,
					    p.port_connect->src);
		break;

	default:
		log_error("invalid command[0x%08x]. magic=0x%02x, num=%d",
			  cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));
		ret = -ENOTTY;
		break;
	}

	return ret;
}

static int ioctl_user_ptr_param(void *priv, unsigned int cmd, void *arg,
				struct te_ioctl_ptr_param *param)
{
	if (cmd == TE_IOC_CFG_TPI) {
		LX_TE_TPI_CFG_PARAM_T *p = arg;

		param->user_ptr = te_ioctl_get_user_ptr(p->value);
		param->kernel_ptr = (void **)&p->value;
		param->size = sizeof(*p->value);
		param->dir = _IOC_WRITE;
	} else if (cmd == TE_IOC_GET_TPI_STATUS) {
		LX_TE_TPI_STATUS_PARAM_T *p = arg;

		param->user_ptr = te_ioctl_get_user_ptr(p->value);
		param->kernel_ptr = (void **)&p->value;
		param->size = sizeof(*p->value);
		param->dir = _IOC_READ;
	}

	return 0;
}

static const struct te_ioctl ioctl_core = {
	.magic = TE_IOC_MAGIC,
	.func = ioctl_func,
	.get_param = ioctl_user_ptr_param,
};


static const struct te_ioctl *get_ioctl(struct te_device *dev, char magic)
{
	int i;
	const struct te_ioctl *c;

	if (ioctl_core.magic == magic)
		return &ioctl_core;

	for (i = 0; i < ARRAY_SIZE(sub_drivers); i++) {
		c = sub_drivers[i]->ioctl;
		if (c && c->magic == magic)
			return c;
	}

	return NULL;
}



static int sub_device_open(struct te_fh *fh)
{
	int i, j, ret;
	const struct te_sub_driver *s;

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

static void sub_device_close(struct te_fh *fh)
{
	int i;
	const struct te_sub_driver *s;

	for (i = ARRAY_SIZE(sub_drivers); i > 0; i--) {
		s = sub_drivers[i - 1];
		if (s->close) {
			log_device("'%s' - close start\n", s->name);
			s->close(fh);
			log_device("'%s' - close done\n", s->name);
		}
	}
}

static int sub_device_resume(struct te_device *dev)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(sub_drivers); i++) {
		const struct te_sub_driver *s = sub_drivers[i];

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

static int sub_device_suspend(struct te_device *dev)
{
	int i, ret;

	for (i = ARRAY_SIZE(sub_drivers); i > 0; i--) {
		const struct te_sub_driver *s = sub_drivers[i - 1];

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

static int sub_device_early_init(struct te_device *dev)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(sub_drivers); i++) {
		const struct te_sub_driver *s = sub_drivers[i];

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

static int sub_device_init(struct te_device *dev)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(sub_drivers); i++) {
		const struct te_sub_driver *s = sub_drivers[i];

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

static void sub_device_release(struct te_device *dev)
{
	int i;

	for (i = ARRAY_SIZE(sub_drivers); i > 0; i--) {
		const struct te_sub_driver *s = sub_drivers[i - 1];

		if (s->release) {
			log_device("'%s' - release start\n", s->name);
			s->release(dev);
			log_device("'%s' - release done\n", s->name);
		}
	}
}

static int dev_open(struct inode *inode, struct file *file)
{
	int ret;
	struct te_device *dev = inode_to_te_device(inode);
	struct te_fh *fh;

	fh = kzalloc(sizeof(*fh), GFP_KERNEL);
	if (!fh)
		return -ENOMEM;

	fh->dev = dev;

	mutex_lock(&node_lock);

	te_clockgate_acquire_clock(dev, TE_DEVICE_TYPE_TE);

	ret = sub_device_open(fh);
	if (ret) {
		te_clockgate_release_clock(dev, TE_DEVICE_TYPE_TE);
		mutex_unlock(&node_lock);
		return ret;
	}

	dev->users++;

	file->private_data = fh;

	log_trace("device opened (%d:%d)\n", imajor(inode), iminor(inode));

	mutex_unlock(&node_lock);

	return 0;
}

static int dev_close(struct inode *inode, struct file *file)
{
	struct te_fh *fh = file->private_data;
	struct te_device *dev = fh->dev;

	mutex_lock(&node_lock);
	dev->users--;

	sub_device_close(fh);

	te_clockgate_release_clock(dev, TE_DEVICE_TYPE_TE);
	kfree(fh);
	log_trace("device closed (%d:%d)\n", imajor(inode), iminor(inode));

	mutex_unlock(&node_lock);

	return 0;
}

static long dev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct te_fh *fh = file->private_data;
	const struct te_ioctl *c;

	c = get_ioctl(fh->dev, _IOC_TYPE(cmd));
	if (!c) {
		log_error("invalid magic. magic='%c'\n", _IOC_TYPE(cmd));
		return -ENOTTY;
	}

	return te_ioctl_usercopy(cmd, arg, c->func, c->get_param, fh);
}

struct file_operations te_dev_fops = {
	.open = dev_open,
	.release = dev_close,
	.unlocked_ioctl = dev_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = dev_ioctl,
#endif
};

int te_device_suspend(struct te_device *dev)
{
	dev->data = vmalloc(sizeof(*dev->data));
	CHECK_ERROR(!dev->data, return -ENOMEM, "can't alloc memory");

	sub_device_suspend(dev);
	te_clockgate_suspend(dev);

	return 0;
}

int te_device_resume(struct te_device *dev)
{
	te_clockgate_resume(dev);
	init_mem_protector();
	init_hw(dev);

	sub_device_resume(dev);

	vfree(dev->data);

	return 0;
}

int te_device_init(struct te_device *dev)
{
	int ret;

	te_cfg_init(dev);
	init_mem_protector();

	mutex_init(&dev->mutex);
	INIT_LIST_HEAD(&dev->subdevs);

	ret = sub_device_early_init(dev);
	CHECK_ERROR(ret, return ret, "Error in sub_device_early_init");

	init_hw(dev);
	init_debug(dev);

	ret = sub_device_init(dev);
	CHECK_ERROR(ret, return ret, "Error in sub_device_init");

	ret = te_clockgate_init(dev);
	CHECK_ERROR(ret, return ret, "Error in te_clockgate_init");

	return 0;
}

void te_device_release(struct te_device *dev)
{
	sub_device_release(dev);

}
