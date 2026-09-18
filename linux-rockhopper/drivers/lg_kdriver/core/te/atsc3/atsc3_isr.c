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
 *  atsc3 driver
 *
 *  @author	Yeonju Lee (yeonju.lee@lge.com)
 *  @version	1.0
 *  @date		2016-03-09
 *  @note		Additional information.
 */

#include <linux/interrupt.h>

#include "atsc3_impl.h"

static int irq_handler(u32 status, void *dev_id)
{
	u32 status2;
	struct atsc3_device *dev = dev_id;

	te_reg_dumper_get_intr_status(&status2);
	te_reg_dumper_clear_intr(status2);	/* clear 2nd level interrupt */

	atsc3_clock_irq_handler(dev, status2);
	atsc3_io_irq_handler(dev, status2);

	return 0;
}

static void dumper_handler(u32 status2, void *arg)
{
	struct atsc3_device *dev = arg;

	atsc3_clock_irq_handler(dev, status2);
	atsc3_io_irq_handler(dev, status2);
}

static int isr_dev_init(struct atsc3_device *dev)
{
	int ret;
	struct te_io_cfg *cfg = te_get_io_config();
	struct te_device *tdev = get_te_device(dev);

	if (!cfg->num_dumper) {	//TODO: remove after m16p3 maintenance is over
		ret = te_request_irq(tdev, ATSC3_MODULE, TOP_INTR_A3,
				     irq_handler, dev);
		if (ret) {
			log_error("Error(%d) in te_request_irq\n", ret);
			return ret;
		}
	} else {
		te_dumper_register_isr_callback(tdev, TE_DUMPER_MODE_ATSC3,
						dumper_handler, dev);
	}

	return 0;
}

static void isr_dev_release(struct atsc3_device *dev)
{
	struct te_io_cfg *cfg = te_get_io_config();
	struct te_device *tdev = get_te_device(dev);

	if (!cfg->num_dumper) {
		te_free_irq(tdev, ATSC3_MODULE);
	} else {
		te_dumper_register_isr_callback(tdev, TE_DUMPER_MODE_ATSC3,
						NULL, NULL);
	}
}

const struct atsc3_sub_driver atsc3_isr_driver = {
	.name = "atsc3_isr",
	.init = isr_dev_init,
	.release = isr_dev_release,
};
