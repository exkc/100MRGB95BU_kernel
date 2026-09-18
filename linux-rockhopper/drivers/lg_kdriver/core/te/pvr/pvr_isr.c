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
 *  pvr device driver
 *
 *  author		ks.hyun(ks.hyunlge.com)
 *  version		1.0
 *  date		2018.10.29
 *  note		Additional information.
 *
 */

#include <linux/interrupt.h>

#include "pvr_impl.h"

static void upload_isr_handler(struct pvr_device *dev, u8 idx)
{
	u32 status;

	TE_REG_GetUploadIntrStatus(idx, &status);
	TE_REG_ClearUploadIntr(idx, status);

	if (status & UPLOAD_INTR_EMPTY) {
		struct pvr_up *up = &dev->up[idx];

		spin_lock(&up->spinlock);
		up->empty = true;
		up->stats.empty++;
		spin_unlock(&up->spinlock);

		log_noti("UPLOAD[%d] Buffer Empty", idx);
	}
}

static void be_isr_handler(struct pvr_device *dev)
{
	u32 status;

	TE_REG_GetBeIntrStatus(&status);
	TE_REG_ClearBeIntr(status);	/* clear interrupt */

	if (status & BE_INTR_PIE_DETECT) {
	}

	if (status & BE_INTR_SEGMENT_DN0) {
	}

	if (status & BE_INTR_SEGMENT_DN1) {
	}
}

static int irq_handler(u32 status, void *dev_id)
{
	struct pvr_device *dev = dev_id;

	if (status & TOP_INTR_BE)	/* DOWNLOAD */
		be_isr_handler(dev);

	if (status & TOP_INTR_UPLOAD0)	/* UPLOAD0 */
		upload_isr_handler(dev, 0);

	if (status & TOP_INTR_UPLOAD1)	/* UPLOAD1 */
		upload_isr_handler(dev, 1);

	return 0;
}

static int init_device(struct pvr_device *dev)
{
	int ret;
	u32 mask;
	struct te_device *tdev = get_te_device(dev);

	mask = TOP_INTR_UPLOAD0 | TOP_INTR_UPLOAD1 | TOP_INTR_BE;
	ret = te_request_irq(tdev, PVR_MODULE, mask, irq_handler, dev);
	if (ret) {
		log_error("Error(%d) in te_request_irq\n", ret);
		return ret;
	}

	return 0;
}

static void release_device(struct pvr_device *dev)
{
	struct te_device *tdev = get_te_device(dev);

	te_free_irq(tdev, PVR_MODULE);
}

const struct pvr_sub_driver pvr_isr_driver = {
	.name = "pvr_isr",

	.init = init_device,
	.release = release_device,
};
