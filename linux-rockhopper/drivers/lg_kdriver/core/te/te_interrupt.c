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

#include <linux/interrupt.h>

#include "te_impl.h"

struct te_irq_action {
	const char *name;
	te_irq_handler_t handler;
	void *dev_id;
	unsigned long mask;
	unsigned long count;
	struct list_head list;
};

int te_request_irq(struct te_device *dev, const char *name, u32 mask,
		   te_irq_handler_t handler, void *dev_id)
{
	struct te_irq_action *act, *x;

	act = kzalloc(sizeof(*act), GFP_KERNEL);
	if (!act) {
		return -ENOMEM;
	}

	act->name = name;
	act->mask = mask;
	act->handler = handler;
	act->dev_id = dev_id;

	mutex_lock(&dev->mutex);

	list_for_each_entry(x, &dev->irq.list, list) {
		if (!strcmp(x->name, name) || (x->mask & mask)) {
			log_error("already registered irq(%s:0x%lx)\n", x->name,
				  x->mask);
			kfree(act);
			mutex_unlock(&dev->mutex);
			return -EBUSY;
		}
	}

	spin_lock_irq(&dev->irq.spinlock);
	list_add_tail(&act->list, &dev->irq.list);
	spin_unlock_irq(&dev->irq.spinlock);

	log_debug("registered irq(%s) mask(0x%x)\n", name, mask);

	mutex_unlock(&dev->mutex);

	return 0;
}

void te_free_irq(struct te_device *dev, const char *name)
{
	struct te_irq_action *act;
	bool found = false;

	mutex_lock(&dev->mutex);
	list_for_each_entry(act, &dev->irq.list, list) {
		if (!strcmp(act->name, name)) {
			found = true;
			break;
		}
	}

	if (found) {
		spin_lock_irq(&dev->irq.spinlock);
		list_del(&act->list);
		spin_unlock_irq(&dev->irq.spinlock);
		kfree(act);
	} else {
		log_error("no irq(%s)\n", name);
	}
	mutex_unlock(&dev->mutex);
}

static irqreturn_t irq_handler(int irq, void *dev_id)
{
	struct te_irq_action *act;
	struct te_device *dev = dev_id;
	u32 status, mask = 0;

	TE_REG_GetIntrStatus(&status);
	if (!status)
		return IRQ_NONE;

	dev->irq.count++;

	spin_lock(&dev->irq.spinlock);
	list_for_each_entry(act, &dev->irq.list, list) {
		if (act->mask & status) {
			act->count++;
			act->handler(status, act->dev_id);

			mask |= act->mask;
			if (!(status & ~mask))
				break;
		}
	}
	spin_unlock(&dev->irq.spinlock);

	/* 1st level interrupt is not cleard if 2nd level interrupt was raised */
	TE_REG_ClearIntr(status);	/* clear interrupt */

	return IRQ_HANDLED;
}

static const struct te_val_str intr_bit_str[] = {
	{TOP_INTR_FE_BIT, "FE"},
	{TOP_INTR_TSBUF_BIT, "TSBUF"},
	{TOP_INTR_STCC_BIT, "STCC"},
	{TOP_INTR_UPLOAD0_BIT, "UPLOAD0"},
	{TOP_INTR_UPLOAD1_BIT, "UPLOAD1"},
	{TOP_INTR_DSC0_BIT, "DSC0"},
	{TOP_INTR_DSC1_BIT, "DSC1"},
	{TOP_INTR_BE_BIT, "BE"},
	{TOP_INTR_CIPLUS_BIT, "CIPLUS"},
	{TOP_INTR_A3_BIT, "ATSC3"},
	{TOP_INTR_DUMPER_BIT, "DUMPER"},
	{TOP_INTR_ARIB2_BIT, "ARIB2"},
};

const char *te_reg_top_intr_bit_to_str(enum te_reg_top_intr_bit bit)
{
	return find_match_string(intr_bit_str, bit, "INVALID");
}

static int debug_show(struct te_debug_item *item, struct seq_file *m)
{
	struct te_irq_action *act;
	struct te_device *dev = item->private;
	int bit;

	mutex_lock(&dev->mutex);

	list_for_each_entry(act, &dev->irq.list, list) {
		seq_printf(m, "%8s %10lu", act->name, act->count);
		for_each_set_bit(bit, &act->mask, TOP_INTR_BIT_MAX) {
			seq_printf(m, " %s", te_reg_top_intr_bit_to_str(bit));
		}
		seq_printf(m, "\n");
	}
	seq_printf(m, "%8s %10lu\n", "total", dev->irq.count);

	mutex_unlock(&dev->mutex);

	return 0;
}

static const struct te_debug_item_info debug_list[] = {
	DBGITM_SHOW("interrupts", debug_show, 0),
};

static void init_debug(struct te_device *dev)
{
	debug_create_item_files(debug_list, dev, dev->debug.dir);
}

static int irq_dev_init(struct te_device *dev)
{
	int ret;

	spin_lock_init(&dev->irq.spinlock);
	INIT_LIST_HEAD(&dev->irq.list);

	ret = request_irq(dev->cfg->hw_irq_num, irq_handler, 0, "TE_HW", dev);
	if (ret) {
		log_error("Error(%d) in request_irq\n", ret);
		return ret;
	}

	init_debug(dev);

	return 0;
}

static void irq_dev_release(struct te_device *dev)
{
	free_irq(dev->cfg->hw_irq_num, dev);
}

const struct te_sub_driver te_irq_driver = {
	.name = "te_irq",
	.init = irq_dev_init,
	.release = irq_dev_release,
};
