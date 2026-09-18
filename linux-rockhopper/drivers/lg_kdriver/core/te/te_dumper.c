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
 *  TE(Transport Engine) Dumper Driver
 *
 *  @author	Ilkyu Kim (ilkyu.kim@lge.com)
 *  @version	0.1
 *  @date		2018-09-12
 *  @note		Additional information.
 */

#include "te_impl.h"

#define dumper_exist(dev)	(dev->cfg->io.num_dumper)

static const struct te_val_str dumper_mode_str[] = {
	{TE_DUMPER_MODE_ATSC3, "ATSC3"},
	{TE_DUMPER_MODE_ARIB2, "ARIB2"},
};

static const char *get_dumper_mode_str(enum te_dumper_mode mode)
{
	return find_match_string(dumper_mode_str, mode, "Invalid");
}

static enum te_dumper_mode str_to_dumper_mode(const char *str)
{
	return find_match_value(dumper_mode_str, str, TE_DUMPER_MODE_MAX);
}

static int irq_handler(u32 status, void *dev_id)
{
	u32 status2;
	struct te_device *dev = dev_id;
	struct te_dev_dumper *d = &dev->dumper;

	te_reg_dumper_get_intr_status(&status2);
	te_reg_dumper_clear_intr(status2);	/* clear 2nd level interrupt */

	spin_lock(&d->spinlock);

	if (d->mode == TE_DUMPER_MODE_ATSC3) {
		if (d->atsc3.func)
			d->atsc3.func(status2, d->atsc3.arg);
	} else if (d->mode == TE_DUMPER_MODE_CI20) {
		if (d->ci20.func)
			d->ci20.func(status2, d->ci20.arg);
	} else {
		if (d->arib2.func)
			d->arib2.func(status2, d->arib2.arg);
	}

	spin_unlock(&d->spinlock);

	return 0;
}

static void enable_interrupt(void)
{
	TE_REG_SetIntrEnable(TOP_INTR_DUMPER, true);
}

static void disable_interrupt(void)
{
	TE_REG_SetIntrEnable(TOP_INTR_DUMPER, false);
}

static void enable_packet_monitor(struct te_device *dev)
{
	int i;
	struct te_reg_dumper_pkt_mon conf;

	conf.enable = true;
	conf.sop_mode = false;
	conf.unit_byte = 0;	// 1byte unit

	for (i = 0; i < dev->cfg->io.num_dumper; i++) {
		te_reg_dumper_set_packet_monitor(i, &conf);
	}
}

static int get_dumper_status(u8 ch, struct te_dumper_status *s)
{
	struct te_reg_dumper_status status;
	u32 val;

	te_reg_dumper_get_channel_status(ch, &status);
	s->mode = status.mode;
	s->enable = status.enable;

	TE_REG_GetEngineChannelSource(ch, &s->src);

	te_reg_dumper_get_packet_count(ch, &val);
	s->bytes = val;

	s->time = (u32)te_get_ms_tick();

	return 0;
}

static int set_engine_mode(enum te_dumper_mode mode)
{
	int ret;
	enum te_reg_engine_mode engine;

	if (mode == TE_DUMPER_MODE_ARIB2) {
		engine = ENGINE_MODE_ARIB2;
	} else if (mode == TE_DUMPER_MODE_CI20) {
		engine = ENGINE_MODE_CI20;
	} else {
		engine = ENGINE_MODE_ATSC3;
	}

	ret = te_reg_dumper_set_engine(engine);
	CHECK_ERROR(ret, return ret, "Error in TE_REG_SetEngineMode");

	return 0;
}

int te_dumper_set_mode(struct te_device *dev, enum te_dumper_mode mode)
{
	int ret;

	if (dev->dumper.mode != mode) {
		ret = set_engine_mode(mode);
		if (ret)
			return ret;

		dev->dumper.mode = mode;
	}

	return 0;
}

enum te_dumper_mode te_dumper_get_mode(struct te_device *dev)
{
	enum te_reg_engine_mode engine;
	enum te_dumper_mode mode;

	te_reg_dumper_get_engine(&engine);
	if (engine == ENGINE_MODE_ARIB2)
		mode = TE_DUMPER_MODE_ARIB2;
	else
		mode = TE_DUMPER_MODE_ATSC3;

	if (dev->dumper.mode != mode) {
		log_warning("engine is changed to [%d]", mode);
		dev->dumper.mode = mode;
	}

	return mode;
}

int te_dumper_register_isr_callback(struct te_device *dev,
				    enum te_dumper_mode mode,
				    void (*callback)(u32 status2, void *arg),
				    void *arg)
{
	unsigned long flag;
	struct te_dev_dumper *d = &dev->dumper;

	spin_lock_irqsave(&d->spinlock, flag);

	if (mode == TE_DUMPER_MODE_ATSC3) {
		d->atsc3.func = callback;
		d->atsc3.arg = arg;
	} else if (mode == TE_DUMPER_MODE_CI20) {
		d->ci20.func = callback;
		d->ci20.arg = arg;
	} else {
		d->arib2.func = callback;
		d->arib2.arg = arg;
	}

	spin_unlock_irqrestore(&d->spinlock, flag);

	return 0;
}

/* debug functions */

#define dprintf(fmt, args...)	seq_printf(m, fmt, ##args)

enum {
	DEBUG_ID_MODE = 0,
};


/**
 * te_debug_get_dumper_status - Get status for all dumper
 *
 * It allocates memory for all dumper and gets the current status.
 * And you must call @te_debug_free_dumper_status to free allocated memory
 *
 * Return: allocated @struct te_dumper_status on success, or ERR_PTR on error
 */
struct te_dumper_status *te_debug_get_dumper_status(struct te_device *dev)
{
	int i;
	struct te_io_cfg *cfg = te_get_io_config();
	struct te_dumper_status *s;

	if (!cfg->num_dumper)
		return ERR_PTR(-ENODEV);

	s = kcalloc(cfg->num_dumper, sizeof(*s), GFP_KERNEL);
	if (!s)
		return ERR_PTR(-ENOMEM);

	for (i = 0; i < cfg->num_dumper; i++) {
		get_dumper_status(i, &s[i]);
	}

	return s;
}

/**
 * te_debug_show_dumper_status - Show dumper status through @struct seq_file
 * @old: previous dumper status from @te_debug_get_dumper_status
 */
void te_debug_show_dumper_status(struct te_device *dev, struct seq_file *m,
				 struct te_dumper_status *old)
{
	int i;
	struct te_dumper_status s;
	struct te_io_cfg *cfg = te_get_io_config();
	u32 bytes, elapsed;
	char *rate;

	dprintf("%3s %12s %2s %7s %17s %13s\n",
		"Num", "Source", "En", "Mode", "Packet", "Speed");

	for (i = 0; i < cfg->num_dumper; i++) {
		get_dumper_status(i, &s);

		dprintf("[%d] %12s  %c %7s ", i,
			te_reg_channel_src_to_str(s.src),
			s.enable ? 'O' : 'X',
			te_reg_dumper_mode_to_str(s.mode));

		bytes = s.bytes - old[i].bytes;
		elapsed = s.time - old[i].time;
		rate = get_bitrate_str(bytes, 1, elapsed);

		dprintf("%08x/%08x %13s\n", old[i].bytes, s.bytes, rate);
	}
}

void te_debug_free_dumper_status(struct te_dumper_status *status)
{
	kfree(status);
}

static int debug_show(struct te_debug_item *item, struct seq_file *m)
{
	int ret = 0;
	struct te_device *dev = item->private;
	enum te_dumper_mode mode;

	switch (item->flags) {
	case DEBUG_ID_MODE:
		mode = te_dumper_get_mode(dev);
		seq_printf(m, "%s\n", get_dumper_mode_str(mode));
		break;

	default:
		ret = -EPERM;
		break;
	}

	return ret;
}

static int debug_write(struct te_debug_item *item, char *str)
{
	int ret = 0;
	struct te_device *dev = item->private;
	enum te_dumper_mode mode;

	switch (item->flags) {
	case DEBUG_ID_MODE:
		mode = str_to_dumper_mode(str);
		if (mode == TE_DUMPER_MODE_MAX)
			ret = -EINVAL;
		else
			ret = te_dumper_set_mode(dev, mode);
		break;

	default:
		ret = -EPERM;
		break;
	}

	return ret;
}

static const struct te_debug_simple_ops debug_ops = {
	.show = debug_show,
	.write = debug_write,
};

static const struct te_debug_item_info debug_list[] = {
	DBGITM_SIM("dumper", &debug_ops, DEBUG_ID_MODE),
};

static void init_debug(struct te_device *dev)
{
	debug_create_item_files(debug_list, dev, dev->debug.dir);
}

static int dev_suspend(struct te_device *dev)
{
	if (dumper_exist(dev))
		disable_interrupt();

	return 0;
}

static int dev_resume(struct te_device *dev)
{
	set_engine_mode(dev->dumper.mode);

	if (dumper_exist(dev)) {
		enable_interrupt();
		enable_packet_monitor(dev);
	}

	return 0;
}

static int dev_init(struct te_device *dev)
{
	int ret;
	struct te_dev_dumper *d = &dev->dumper;

	spin_lock_init(&d->spinlock);

	d->mode = TE_DUMPER_MODE_ATSC3;
	set_engine_mode(d->mode);

	if (dumper_exist(dev)) {
		ret = te_request_irq(dev, "dumper", TOP_INTR_DUMPER,
				     irq_handler, dev);
		if (ret) {
			log_error("Err(%d) in te_request_irq\n", ret);
			return ret;
		}
		enable_interrupt();
		enable_packet_monitor(dev);
	}
	init_debug(dev);

	return 0;
}

static void dev_release(struct te_device *dev)
{
	if (dumper_exist(dev)) {
		disable_interrupt();
		te_free_irq(dev, "dumper");
	}
}

const struct te_sub_driver te_dumper_driver = {
	.name = "te_dumper",
	.init = dev_init,
	.release = dev_release,
	.suspend = dev_suspend,
	.resume = dev_resume,
};
