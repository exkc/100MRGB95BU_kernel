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
 *  driver interrupt service rouotine implementation for sci device.
 *	sci device will teach you how to make device driver with new platform.
 *
 *  author		bongrae.cho (bongrae.cho@lge.com)
 *  version		1.0
 *  date		2012.02.23
 *  note		Additional information.
 *
 *  @addtogroup lg1154_sci
 *	@{
 */

#include <linux/wait.h>
#include <linux/irq.h>
#include <linux/sched.h>
#include <linux/version.h>
#include <linux/jiffies.h>
#include <linux/interrupt.h>

#include "sci_impl.h"
#include "sci_reg.h"

#define TRACE_ENTER(fmt,args...)					\
do { 									\
	if (g_sci_isr_log_mask) {					\
		log_noti("@SCI_ISR: %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

#define TRACE_EXIT(fmt,args...)						\
do { 									\
	if (g_sci_isr_log_mask) {					\
		log_noti("~SCI_ISR: %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

static u32 g_sci_isr_log_mask;

static irqreturn_t irq_handler(int irq, void *dev_id)
{
	u8 status, mask, intr;
	u32 event, event_status;
	int remained;

	struct sci_dev *dev = dev_id;

	spin_lock(&dev->lock);

	status = sci_reg_get_interrupt_status();
	mask = sci_reg_get_interrupt_mask();
	intr = status & ~mask;

	TRACE_ENTER("status:0x%x, mask:0x%x, intr:0x%x", status, mask, intr);
	event = 0;
	if (intr & SCI_IRQ_CDPWR) {
		event |= SCI_EVENT_CARD_POWER;
	}
	if (intr & SCI_IRQ_ERR) {
		log_error("err status=0x%02x, status=0x%02x\n",
			  sci_reg_get_error_status(), sci_reg_get_status());
		if (dev->phase == SCI_PHASE_BLOCK_MESSAGE) {
			if (dev->xfer_state < XFER_STATE_TX_DONE)
				event |= SCI_EVENT_TX_ERROR;
			else
				event |= SCI_EVENT_RX_ERROR;
		}

	}
	if (intr & SCI_IRQ_FTE) {
		if (dev->phase == SCI_PHASE_BLOCK_MESSAGE) {
			if (dev->xfer_state == XFER_STATE_TX_WRITE) {
				struct block_frame *tx = &dev->tx_block;

				remained = tx->len - tx->idx;
				if (remained == 0) {
					dev->xfer_state =
					    XFER_STATE_TX_WRITE_DONE;
				} else {
					if (remained > MAX_TF_DEPTH)
						remained = MAX_TF_DEPTH;

					sci_reg_write_data(tx->inf + tx->idx,
							   remained);

					tx->idx += remained;
				}
			}
		}
	}
	if (intr & SCI_IRQ_EOT) {
		if (dev->phase == SCI_PHASE_BLOCK_MESSAGE) {
			struct block_frame *tx = &dev->tx_block;
			if (dev->xfer_state == XFER_STATE_TX_WRITE_DONE) {
				dev->num_tx++;
			} else {
				r_log
				    ("not tx yet. (%d/%d) status:0x%02x, state:%d ",
				     tx->idx, tx->len, sci_reg_get_status(),
				     dev->xfer_state);
			}
			dev->xfer_state = XFER_STATE_TX_DONE;
//                      sci_reg_command(CMD_RX_EN); /* it makes card status to DET */
		}
	}
	if (intr & SCI_IRQ_EOR) {
		if (dev->phase == SCI_PHASE_BLOCK_MESSAGE) {
			struct block_frame *rx = &dev->rx_block;

			if (dev->xfer_state == XFER_STATE_TX_DONE) {
				sci_reg_get_block_frame_header(&rx->nad,
							       &rx->pcb,
							       &rx->len);
				dev->xfer_state = XFER_STATE_RX_WAIT;
			}

			if (dev->xfer_state == XFER_STATE_RX_WAIT) {
				remained = rx->len - rx->idx;
				sci_reg_read_data(rx->inf + rx->idx, remained);
				rx->idx += remained;
				dev->xfer_state = XFER_STATE_RX_DONE;
				event |= SCI_EVENT_RX_DONE;
			} else {
				r_log("EOR but not received rx. status:0x%02x",
				      sci_reg_get_status());

				sci_reg_get_block_frame_header(&rx->nad,
							       &rx->pcb,
							       &rx->len);
				event |= SCI_EVENT_RX_DONE;
			}
			dev->num_rx++;

		} else if (dev->phase == SCI_PHASE_ATR) {

		}
	}

	if (intr & SCI_IRQ_FRNE) {
		if (dev->phase == SCI_PHASE_BLOCK_MESSAGE) {
			if (dev->xfer_state == XFER_STATE_TX_DONE) {
				struct block_frame *rx = &dev->rx_block;

				sci_reg_get_block_frame_header(&rx->nad,
							       &rx->pcb,
							       &rx->len);
				dev->xfer_state = XFER_STATE_RX_WAIT;
			}
		}
	}

	if (intr & SCI_IRQ_FRF) {
		if (dev->phase == SCI_PHASE_BLOCK_MESSAGE) {
			if (dev->xfer_state == XFER_STATE_RX_WAIT) {
				struct block_frame *rx = &dev->rx_block;

				remained = rx->len - rx->idx;

				if (remained < MAX_RF_DEPTH) {
					log_error("invalid length:%d",
						  remained);
				} else if (remained > MAX_RF_DEPTH) {
					remained = MAX_RF_DEPTH;
				} else {
					dev->xfer_state = XFER_STATE_RX_DONE;
					event |= SCI_EVENT_RX_DONE;
				}

				sci_reg_read_data(rx->inf + rx->idx, remained);
				rx->idx += remained;
			} else {
				log_error("xfer state error\n");
			}
		} else if (dev->phase == SCI_PHASE_ATR) {
			event |= SCI_EVENT_RXFIFO_FULL;
		}
	}

	event_status = event & dev->event_mask;
	if (event_status) {
		dev->event_status |= event_status;
		wake_up_interruptible(&dev->wq);
	}

	spin_unlock(&dev->lock);

	TRACE_EXIT("event_status:0x%x", event_status);

	return IRQ_HANDLED;
}

int sci_isr_init(struct sci_dev *dev)
{
	int rc;
	struct sci_cfg *cfg = sci_get_config();

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,4,0)
	rc = request_irq(cfg->hw_irq_num, irq_handler, 0, "SCI", dev);
#else
	rc = request_irq(cfg->hw_irq_num, irq_handler, IRQF_DISABLED, "SCI",
			 dev);
#endif
	if (rc) {
		log_error("Error(%d) in request_irq\n", rc);
		return rc;
	}
	return 0;
}

void sci_isr_cleanup(struct sci_dev *dev)
{
	struct sci_cfg *cfg = sci_get_config();

	free_irq(cfg->hw_irq_num, dev);
}

u32 sci_isr_get_log_mask(void)
{
	return g_sci_isr_log_mask;
}

void sci_isr_set_log_mask(int en)
{
	g_sci_isr_log_mask = (en == 0 ? 0 : 1);
}
