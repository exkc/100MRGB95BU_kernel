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
 *  sdec driver
 *
 *  @author	Jihoon Lee ( gaius.lee@lge.com)
 *  @author	Jinhwan Bae ( jinhwan.bae@lge.com) - modifier
 *  @version	1.0
 *  @date		2010-03-30
 *  @note		Additional information.
 */

#include "sdec_impl.h"

static void stcc_isr_handler(struct sdec_device *dev)
{
	u32 status;

	TE_REG_GetFeIntrStatus(&status);
	TE_REG_ClearFeIntr(status);	/* clear interrupt */

	/* PCR Arrival */
	if ((status & FE_STCC_INTR_PCR_MASK)) {
		u32 pcr_mask[4] = {
			FE_STCC_INTR_CH0_PCR, FE_STCC_INTR_CH1_PCR,
			FE_STCC_INTR_CH2_PCR, FE_STCC_INTR_CH3_PCR
		};
		struct sdec_channel *channel;
		int i;

//		LOG_PCR("PCR Interrupt(0x%x)\n", status);
		for (i = 0; i < 4; i++) {
			if (status & pcr_mask[i]) {
				if (i >= dev->num_channel)
					break;

				channel = &dev->channels[i];
				sdec_clock_irq_handler(channel);
			}
		}
	}
	if ((status & FE_STCC_INTR_DISCONT_MASK)) {
		log_isr("PCR DISCONTINUITY INTERRUPT %s%s%s%s\n",
			(status & FE_STCC_INTR_CH0_DISCONT) ? "CH0 " : "",
			(status & FE_STCC_INTR_CH1_DISCONT) ? "CH1 " : "",
			(status & FE_STCC_INTR_CH2_DISCONT) ? "CH2 " : "",
			(status & FE_STCC_INTR_CH3_DISCONT) ? "CH3 " : "");
	}
	if ((status & FE_STCC_INTR_GTIMER0)) {
		log_isr("GTIMER0 INTERRUPT !!!\n");
	}

	if ((status & FE_STCC_INTR_GTIMER1)) {
		log_isr("GTIMER1 INTERRUPT !!!\n");
	}

}

static void tsbuf_isr_handler(struct sdec_device *dev)
{
	struct sdec_channel *channel;
	int i;
	u32 status;

	u32 pkt_mask[4] = {
		TSBUF_PACKET_INTR_CH0, TSBUF_PACKET_INTR_CH1,
		TSBUF_PACKET_INTR_CH2, TSBUF_PACKET_INTR_CH3
	};

	TE_REG_GetTsBufIntrStatus(&status);
	TE_REG_SetTsBufIntrEnable(status, false);
	TE_REG_ClearTsBufIntr(status);

	for (i = 0; i < ARRAY_SIZE(pkt_mask); i++) {
		if (status & pkt_mask[i]) {
			channel = sdec_get_channel(dev, i);
			if (!channel)
				break;
			sdec_io_irq_handler(channel);
		}
	}
}

static int irq_handler(u32 status, void *dev_id)
{
	struct sdec_device *dev = dev_id;

	if (status & TOP_INTR_STCC) {
		stcc_isr_handler(dev);
	}
	if (status & TOP_INTR_TSBUF) {
		tsbuf_isr_handler(dev);
	}
	return 0;
}

static int isr_dev_init(struct sdec_device *dev)
{
	int ret;
	u32 mask;
	struct te_device *tdev = get_te_device(dev);

	mask = TOP_INTR_STCC | TOP_INTR_TSBUF;
	ret = te_request_irq(tdev, SDEC_MODULE, mask, irq_handler, dev);
	if (ret) {
		log_error("Error(%d) in te_request_irq\n", ret);
		return ret;
	}

	return 0;
}

static void isr_dev_release(struct sdec_device *dev)
{
	struct te_device *tdev = get_te_device(dev);

	te_free_irq(tdev, SDEC_MODULE);
}

const struct sdec_sub_driver sdec_isr_driver = {
	.name = "sdec_isr",
	.init = isr_dev_init,
	.release = isr_dev_release,
};
