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
 *  CI+ ISR Driver
 *
 *  @author	Ilkyu Kim ( ilkyu.kim@lge.com)
 *  @version	0.1
 *  @date		2015-07-10
 *  @note		Additional information.
 */

#include "ciplus_impl.h"

static int irq_handler(u32 status, void *dev_id)
{

// TODO: make ciplus intr reg ctrl function

#if 0
	status2 = CIPLUS_REG_READ32(ad_intr_stat_cpu);
	CIPLUS_REG_WRITE32(ad_intr_clr_cpu, status2);	/* clear interrupt */
#endif
	//TODO: construct irq_handler below lines

	return 0;
}

static int isr_dev_init(struct ciplus_device *dev)
{
	int ret;
	struct te_device *tdev = get_te_device(dev);

	ret = te_request_irq(tdev, CIPLUS_MODULE, TOP_INTR_CIPLUS, irq_handler,
			     dev);
	if (ret) {
		log_error("Error(%d) in te_request_irq\n", ret);
		return ret;
	}

	return 0;
}

static void isr_dev_release(struct ciplus_device *dev)
{
	struct te_device *tdev = get_te_device(dev);

	te_free_irq(tdev, CIPLUS_MODULE);
}

const struct ciplus_sub_driver ciplus_isr_driver = {
	.name = "ciplus_isr",
	.init = isr_dev_init,
	.release = isr_dev_release,
};
