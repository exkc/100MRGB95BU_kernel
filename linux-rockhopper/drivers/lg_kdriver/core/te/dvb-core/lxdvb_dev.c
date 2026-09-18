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
 *  TE(Transport Engine) Driver for linux dvb(DEMUX&CA)
 *
 *  @author	Kyungseok Hyun (ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2018-01-26
 *  @note		Additional information.
 */

#include "lxdvb_impl.h"

//Test Code
DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);
//static short adapter_nr[DVB_MAX_ADAPTERS] = { 1, };

static const struct lxdvb_sub_driver *sub_drivers[] = {
#ifdef CONFIG_TE_DVB_DEMUX
	&lxdvb_demux_driver,
#endif
#ifdef CONFIG_TE_DVB_DVR
	&lxdvb_dvr_driver,
#endif
#ifdef CONFIG_TE_DVB_CI
	&lxdvb_ca_driver,
#endif
#ifdef CONFIG_TE_DVB_CIPLUS
	&lxdvb_ci14_driver,
#endif
#ifdef CONFIG_TE_DVB_SCI
	&lxdvb_sci_driver,
#endif
#ifdef CONFIG_TE_DVB_DELIVERY
	&lxdvb_delivery_driver,
#endif
};


static int sub_device_init(struct lxdvb_device *dev)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(sub_drivers); i++) {
		const struct lxdvb_sub_driver *s = sub_drivers[i];

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

static void sub_device_release(struct lxdvb_device *dev)
{
	int i;

	for (i = ARRAY_SIZE(sub_drivers); i > 0; i--) {
		const struct lxdvb_sub_driver *s = sub_drivers[i - 1];

		if (s->release) {
			log_device("'%s' - release start\n", s->name);
			s->release(dev);
			log_device("'%s' - release done\n", s->name);
		}
	}
}

static int sub_device_resume(struct lxdvb_device *dev)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(sub_drivers); i++) {
		const struct lxdvb_sub_driver *s = sub_drivers[i];

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

static int sub_device_suspend(struct lxdvb_device *dev)
{
	int i, ret;

	for (i = ARRAY_SIZE(sub_drivers); i > 0; i--) {
		const struct lxdvb_sub_driver *s = sub_drivers[i - 1];

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

int lxdvb_device_suspend(struct lxdvb_device *dev)
{
	int ret;

	ret = sub_device_suspend(dev);

	return ret;
}

int lxdvb_device_resume(struct lxdvb_device *dev)
{
	int ret;

	ret = sub_device_resume(dev);

	return ret;
}

int lxdvb_device_init(struct lxdvb_device *dev)
{
	int ret;

	ret = dvb_register_adapter(&dev->adapter, LXDVB_DEVICE_NAME,
				   THIS_MODULE, &dev->pdev->dev, adapter_nr);
	CHECK_ERROR(ret < 0, return ret, "Err in dvb_register_adapter");

	log_noti("registered %s adapter(%d)\n", dev->adapter.name,
		 dev->adapter.num);

	dev->adapter.priv = dev;

	dev->debug_dir = te_debug_create_dir(LXDVB_MODULE, NULL);
	CHECK_ERROR(!dev->debug_dir, return -EIO, "Err in te_debug_create_dir");

	ret = lxdvb_proc_init(dev);
	CHECK_ERROR(ret, return ret, "Error in lxdvb_proc_init");

	ret = sub_device_init(dev);
	CHECK_ERROR(ret, return ret, "Error in sub_device_init");

	return 0;
}

void lxdvb_device_release(struct lxdvb_device *dev)
{
	sub_device_release(dev);

	te_debug_remove_dir(dev->debug_dir);
	dvb_unregister_adapter(&dev->adapter);
}

/** @} */
