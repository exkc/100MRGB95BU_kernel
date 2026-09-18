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
 *  arib2 driver
 *
 *  @author	Yeonju Lee (yeonju.lee@lge.com)
 *  @version	1.0
 *  @date	2017-11-23
 *  @note	Additional information.
 */

#include "arib2_impl.h"

static int irq_handler(u32 status, void *dev_id)
{
	u32 status2;
	struct arib2_device *dev = dev_id;

	te_reg_dumper_get_intr_status(&status2);
	te_reg_dumper_clear_intr(status2);	/* clear 2nd level interrupt */

	arib2_clock_irq_handler(dev, status2);
	arib2_io_irq_handler(dev, status2);

	return 0;
}

static void arib2_dumper_handler(u32 status2, void *arg)
{
	arib2_clock_irq_handler(arg, status2);
	arib2_io_irq_handler(arg, status2);
}

static int isr_dev_init(struct arib2_device *dev)
{
	int ret;
	struct te_io_cfg *cfg = te_get_io_config();
	struct te_device *tdev = get_te_device(dev);

	if (dev->use_swtlv)
		return 0;

	if (!cfg->num_dumper) {	//TODO: remove after m16p3 maintenance is over
		ret = te_request_irq(tdev, ARIB2_MODULE, TOP_INTR_ARIB2,
				     irq_handler, dev);
		if (ret) {
			log_error("Error(%d) in te_request_irq\n", ret);
			return ret;
		}
	} else {
		te_dumper_register_isr_callback(tdev, TE_DUMPER_MODE_ARIB2,
						arib2_dumper_handler, dev);
	}

	return 0;
}

static void isr_dev_release(struct arib2_device *dev)
{
	struct te_io_cfg *cfg = te_get_io_config();
	struct te_device *tdev = get_te_device(dev);

	if (dev->use_swtlv)
		return;

	if (!cfg->num_dumper) {
		te_free_irq(tdev, ARIB2_MODULE);
	} else {
		te_dumper_register_isr_callback(tdev, TE_DUMPER_MODE_ARIB2,
						NULL, NULL);
	}
}

const struct arib2_sub_driver arib2_isr_driver = {
	.name = "arib2_isr",
	.init = isr_dev_init,
	.release = isr_dev_release,
};
