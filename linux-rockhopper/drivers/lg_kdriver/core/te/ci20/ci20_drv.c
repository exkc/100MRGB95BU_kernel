/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2020 by LG Electronics Inc.
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
 *  CI2.0 Driver for linux dvb_delivery
 *
 *  @author	Ilkyu Kim (ilkyu.kim@lge.com)
 *  @version	1.0
 *  @date	2020-08-05
 *  @note	Additional information.
 */

//#include <linux/delay.h>
//#include <linux/interrupt.h>
#include <linux/platform_device.h>
//#include <asm/io.h>
//#include <lg1k/te/reg.h>
#include <linux/poll.h>
#include <lg1k/te/buffer.h>
#include <lg1k/te/io.h>
#include <lg1k/te/ci20.h>

#include "os_util.h"
#include "ci20_impl.h"

#define te_subdev_to_ci20_device(sd)			\
	container_of(sd, struct ci20_device, subdev)
#define get_te_device(dev)		(dev->subdev.tdev)

#define CHANNEL_INTR_BITS(i)	\
	((DUMPER_INTR_DATA_UNIT_BUF_CH0<<(i)) |	\
	 (DUMPER_INTR_DATA_AL_FULL_CH0<<(i)))

#define META_SIZE		16
#define TS_PACKET_SIZE		188
#define TS_SYNCBYTE		0x47
#define SYNC_FOUND		3

#define dprintf(fmt, args...)	seq_printf(m, fmt, ##args)
#define dprintf1(fmt, args...)	dprintf("    " fmt, ##args)

int g_ci20_dvb_debug_fd = -1;
static struct ci20_cfg *config;

static struct ci20_cfg config_normal = {
	.num_ch = 4,
};

struct ci20_parse_info {
	struct te_split_buffer sbuf;
	int len;
	u32 sidx;
	u32 eidx;
};

static const char *get_input_dump_state_str(enum ci20_dump_state state)
{
	switch (state) {
	case INPUT_DUMP_IDLE:
		return "IDLE";
	case INPUT_DUMP_RUNNING:
		return "RUNNING";
	case INPUT_DUMP_SUSPEND:
		return "SUSPENDED";
	default:
		return "UNKNOWN";
	}
}

static int suspend_device(struct ci20_device *dev);
static int resume_device(struct ci20_device *dev);

static struct ci20_cfg *ci20_get_config(void)
{
	return config;
}

struct ci20_device *ci20_get_device(struct te_device *dev)
{
	struct te_subdev *sd;

	sd = te_get_subdev(dev, CI20_DEVICE_NAME);
	if (!sd)
		return NULL;

	return te_subdev_to_ci20_device(sd);
}

struct ci20_channel *ci20_get_channel(struct ci20_device *dev, u8 num)
{
	return num < dev->num_channel ? &dev->channels[num] : NULL;
}

static void init_logm(void)
{
	if (g_ci20_dvb_debug_fd == -1) {
		g_ci20_dvb_debug_fd = LOGM_ObjRegister("ci20");
		LOGM_ObjBitMaskEnable(g_ci20_dvb_debug_fd, LOG_LEVEL_ERROR);
		LOGM_ObjBitMaskEnable(g_ci20_dvb_debug_fd, LOG_LEVEL_WARNING);
		LOGM_ObjBitMaskEnable(g_ci20_dvb_debug_fd, LOG_LEVEL_NOTI);
	}
}

enum {
	DEBUG_ID_DUMP_STATUS = 0,
	DEBUG_ID_INSTANTBOOT,
	DEBUG_ID_MAX,
};

static void dump_data_read_callback(void *arg, u32 idx)
{
	struct ci20_input_dump *dump = arg;
	phys_addr_t ptr;

	te_hwbuf_idx_to_paddr(dump->data, idx, &ptr);
	te_reg_dumper_set_data_rptr(dump->ch, (u32)ptr);
}

static void debug_show_channel_dump(struct ci20_channel *channel,
				    struct seq_file *m)
{
	struct timespec64 ts;
	struct ci20_input_dump *d;
	struct ci20_dump_stats *s;
	u32 size, avail;

#define dump_printf(t, fmt, args...) dprintf("    %-8s" fmt "\n", t, ##args)
#define dump_printf1(t, fmt, args...) dprintf1("    %-8s" fmt "\n", t, ##args)
	if (!channel)
		return;

	mutex_lock(&channel->mutex);
	d = &channel->dump;
	dprintf("CH[%d] - %s",
		channel->num, get_input_dump_state_str(d->state));

	if (d->state != INPUT_DUMP_RUNNING) {
		dprintf("\n");
		goto exit;
	}

	s = &d->stats;

	ktime_get_ts64(&ts);
	dprintf(" (%llu.%06usec)\n", ts.tv_sec, (u32)(ts.tv_nsec / 1000));
	dump_printf("PKT\t", "%d", s->pkt);
	dump_printf("SYNCDROP\t", "%d", s->sync_drop);
	dump_printf("OVERFLOW\t", "%d", s->overflow);

	size = te_hwbuf_size(d->data);
	avail = te_hwbuf_avail_size(d->data);

	dprintf1("HWBUF\n");
	dump_printf1("RANGE", "0x%08x-0x%08x (%s)", (u32)te_hwbuf_addr(d->data),
		     (u32)te_hwbuf_addr(d->data) + size,
		     te_get_readable_size(size));

	dump_printf1("PTR", "0x%08x-0x%08x (%s,%d%%)",
		     (u32)te_hwbuf_rptr(d->data), (u32)te_hwbuf_wptr(d->data),
		     te_get_readable_size(avail), (avail * 100) / size);

exit:
	mutex_unlock(&channel->mutex);
}

static int debug_show_dump_status(struct ci20_device *dev, struct seq_file *m)
{
	int i;

	dprintf("Input Dump Status\n");
	for (i = 0; i < dev->num_channel; i++) {
		if (i)
			dprintf("\n");
		debug_show_channel_dump(ci20_get_channel(dev, i), m);
	}

	return 0;
}


static int debug_show(struct te_debug_item *item, struct seq_file *m)
{
	struct ci20_device *dev = item->private;
	int rc = -EPERM;

	switch (item->flags) {
	case DEBUG_ID_DUMP_STATUS:
		rc = debug_show_dump_status(dev, m);
		break;
	default:
		break;
	}

	return rc;
}

static int debug_channel_show(struct te_debug_item *item, struct seq_file *m)
{
	struct ci20_channel *channel = item->private;
	int rc = -EPERM;

	switch (item->flags) {
	case DEBUG_ID_DUMP_STATUS:
		debug_show_channel_dump(channel, m);
		rc = 0;
		break;
	default:
		break;
	}

	return rc;
}

static int suspend_resume_ctrl(struct ci20_device *dev, u8 status)
{
	int ret;

	if (status == 0) {
		ret = suspend_device(dev);
	} else if (status == 1) {
		ret = resume_device(dev);
	} else {
		ret = -EPERM;
	}

	return ret;
}

static int debug_write(struct te_debug_item *item, char *str)
{
	struct ci20_device *dev = item->private;
	int rc;
	u32 val;

	switch (item->flags) {
	case DEBUG_ID_INSTANTBOOT:
		val = simple_strtoul(str, NULL, 0);
		rc = suspend_resume_ctrl(dev, val);
		break;
	default:
		rc = -EPERM;
		break;
	}

	return rc;
}

static int debug_channel_write(struct te_debug_item *item, char *str)
{
	int rc = -EPERM;

	return rc;
}

static const struct te_debug_simple_ops debug_ops = {
	.show = debug_show,
	.write = debug_write,
};

static const struct te_debug_simple_ops debug_channel_ops = {
	.show = debug_channel_show,
	.write = debug_channel_write,
};

static const struct te_debug_item_info debug_list[] = {
	DBGITM_SIM_R("dump", &debug_ops, DEBUG_ID_DUMP_STATUS),
	DBGITM_SIM_W("instantboot", &debug_ops, DEBUG_ID_INSTANTBOOT),
};

static const struct te_debug_item_info debug_channel_list[] = {
	DBGITM_SIM_R("dump", &debug_channel_ops, DEBUG_ID_DUMP_STATUS),
};

static int ci20_cfg_init(void)
{
	config = &config_normal;
	return 0;
}

static int ci20_debug_init(struct ci20_device *dev)
{
	int i;

	dev->debug_dir = te_debug_create_dir("ci20", NULL);
	CHECK_ERROR(!dev->debug_dir, return -EIO, "Err in te_debug_create_dir");
	debug_create_item_files(debug_list, dev, dev->debug_dir);

	for (i = 0; i < dev->num_channel; i++) {
		struct ci20_channel *c = ci20_get_channel(dev, i);
		struct te_debug_dir *p = dev->debug_dir;

		if (!c)
			continue;
		snprintf(c->debug_name, sizeof(c->debug_name), "%d", i);
		c->debug_dir = te_debug_create_dir(c->debug_name, p);
		debug_create_item_files(debug_channel_list, c, c->debug_dir);
	}

	return 0;
}

static void ci20_debug_release(struct ci20_device *dev)
{
	te_debug_remove_dir(dev->debug_dir);
}


static void irq_handler(struct ci20_device *dev, u8 i, u32 val)
{
	struct ci20_channel *channel;
	struct ci20_input_dump *dump;
	struct ci20_dump_stats *s;
	u32 v, wptr;
	int rc;

	if (!(val & CHANNEL_INTR_BITS(i)))
		return;

	channel = ci20_get_channel(dev, i);
	if (!channel)
		return;

	v = DUMPER_INTR_DATA_AL_FULL_CH0 << i;
	if (val & v) {
		te_reg_dumper_set_intr_enable(v, false);
		log_warning("ch[%d] DATA ALMOST FULL IRQ", i);
	}

	dump = &channel->dump;
	s = &dump->stats;

	spin_lock(&dump->spinlock);

	if (dump->state != INPUT_DUMP_RUNNING) {
		spin_unlock(&dump->spinlock);
		return;
	}

	if (val & (DUMPER_INTR_DATA_AL_FULL_CH0 << i)) {
		te_hwbuf_set_error(dump->data, -ENOBUFS);
		s->overflow++;
	}

	if (val & (DUMPER_INTR_DATA_UNIT_BUF_CH0 << i)) {
		te_reg_dumper_get_data_wptr(i, &wptr);
		rc = te_hwbuf_set_wptr(dump->data, wptr);
		if (rc == -EOVERFLOW) {
			te_hwbuf_set_error(dump->data, -ENOBUFS);
			s->overflow++;
		}
	}

	spin_unlock(&dump->spinlock);
}

static void dumper_handler(u32 status2, void *arg)
{
	struct ci20_device *dev = arg;
	int i;

	for (i = 0; i < dev->num_channel; i++) {
		irq_handler(dev, i, status2);
	}
}

static int ci20_device_init(struct ci20_device *dev)
{
	int i;
	struct te_device *tdev = get_te_device(dev);
	struct ci20_channel *c;
	struct ci20_input_dump *d;

	for (i = 0; i< dev->num_channel; i++) {
		c = ci20_get_channel(dev, i);
		if (!c)
			continue;
		c->num = i;
		mutex_init(&c->mutex);
		c->dev = dev;

		d = &c->dump;
		d->ch = i;
		d->state = INPUT_DUMP_IDLE;
		spin_lock_init(&d->spinlock);
	}

	//TODO: add input monitor
	te_dumper_register_isr_callback(tdev, TE_DUMPER_MODE_CI20,
					dumper_handler, dev);

	return 0;
}

static void ci20_device_remove(struct ci20_device *dev)
{
	struct te_device *tdev = get_te_device(dev);

	te_dumper_register_isr_callback(tdev, TE_DUMPER_MODE_CI20, NULL, NULL);
}

static int config_channel_input(struct ci20_channel *channel,
				 enum lx_te_input_port port,
				 bool reset, bool enable)
{
	int rc;
	enum te_reg_channel_src src;

	log_noti("ch %d, port: %s -> %s, enable: %d, reset: %d",
		 channel->num, te_input_port_to_str(channel->input_port),
		 te_input_port_to_str(port), enable, reset);

	src = te_input_port_to_reg_ch_src(port);
	CHECK_ERROR(src == CH_SRC_INVALID, return -EINVAL,
		    "invalid input port:[%d]", port);

	log_noti("ci20_src: %s", te_ch_src_type_to_str(src));

	if (enable) {
		if (reset || channel->input_port != port) {
			/* reset input port if input source is changed */
			TE_REG_SetEngineChannelSource(channel->num,
						      CH_SRC_DISABLE);
		}

		rc = TE_REG_SetEngineChannelSource(channel->num, src);
		CHECK_ERROR(rc, return rc,
			    "Error in TE_REG_SetEngineChannelSource - %d", rc);

		channel->input_port = port;
	} else {
		/* disable input port */
		TE_REG_SetEngineChannelSource(channel->num, CH_SRC_DISABLE);

		channel->input_port = LX_TE_INPUT_PORT_NONE;
	}

	return 0;
}

int ci20_config_channel_input(struct ci20_channel *channel,
			      enum lx_te_input_port port,
			      bool reset, bool enable)
{
	int ret;

	mutex_lock(&channel->mutex);
	ret = config_channel_input(channel, port, reset, enable);
	mutex_unlock(&channel->mutex);

	return ret;
}

static int start_input_dump_device(struct ci20_input_dump *d)
{
	int rc;
	u8 ch = d->ch;
	u32 addr, size, unit_size, full_level;
	u32 intr;

	te_hwbuf_reset(d->data);

	/* data buffer setting */
	addr = (u32) te_hwbuf_addr(d->data);
	size = te_hwbuf_size(d->data);
	unit_size = te_hwbuf_unit_size(d->data);
	if (unit_size) {
		intr = ((DUMPER_INTR_DATA_AL_FULL_CH0 << ch) |
			(DUMPER_INTR_DATA_UNIT_BUF_CH0 << ch));
		full_level = unit_size * 2;
	} else {
		intr = (DUMPER_INTR_DATA_AL_FULL_CH0 << ch);
		full_level = 64 * 1024;
	}

	te_reg_dumper_set_data_buf(ch, addr, addr + size);
	te_reg_dumper_set_data_rptr(ch, addr);
	te_reg_dumper_set_data_unitbuf_size(ch, unit_size);
	te_reg_dumper_set_data_almostfull_level(ch, full_level);

	te_hwbuf_set_read_callback(d->data, dump_data_read_callback, d);

	rc = te_reg_dumper_set_channel_enable(ch, true);
	CHECK_ERROR(rc != 0,, "Error in set channel enable[%d]", rc);

	te_reg_dumper_set_intr_enable(intr, true);
	d->intr = intr;

	return 0;
}

static struct ci20_input_dump *start_input_dump(struct ci20_channel *channel,
						struct ci20_dump_cfg *cfg)
{
	struct ci20_input_dump *dump;
	int ret;

	log_noti("(ch=%d,addr=0x%08x++0x%x,unit=0x%x)", channel->num,
		 (u32)te_hwbuf_addr(cfg->data), te_hwbuf_size(cfg->data),
		 te_hwbuf_unit_size(cfg->data));

	dump = &channel->dump;
	if (dump->state != INPUT_DUMP_IDLE) {
		log_error("dump[%d] is running", dump->ch);
		return NULL;
	}

	dump->data = cfg->data;
	dump->sync = false;

	ret = start_input_dump_device(dump);
	CHECK_ERROR(ret, return NULL,
		    "Error in start_input_dump_device(%d)", ret);

	memset(&dump->stats, 0, sizeof(struct ci20_dump_stats));

	dump->state = INPUT_DUMP_RUNNING;

	return dump;
}

struct ci20_input_dump *ci20_start_input_dump(struct ci20_channel *channel,
					      struct ci20_dump_cfg *cfg)
{
	struct ci20_input_dump *dump;

	mutex_lock(&channel->mutex);

	dump = start_input_dump(channel, cfg);
	if (!dump) {
		mutex_unlock(&channel->mutex);
		return NULL;
	}

	mutex_unlock(&channel->mutex);
	return dump;
}

static void stop_input_dump_device(struct ci20_input_dump *dump)
{
	te_hwbuf_set_read_callback(dump->data, NULL, NULL);

	te_reg_dumper_set_intr_enable(dump->intr, false);
	te_reg_dumper_set_channel_enable(dump->ch, false);
}

static int stop_input_dump(struct ci20_input_dump *dump)
{
	unsigned long flag;

	log_noti("(ch=%d)", dump->ch);

	if (dump->state != INPUT_DUMP_RUNNING) {
		log_warning("already stopped");
		return 0;
	}

	/* Prevent running on irq handler first */
	spin_lock_irqsave(&dump->spinlock, flag);
	dump->state = INPUT_DUMP_IDLE;
	spin_unlock_irqrestore(&dump->spinlock, flag);

	stop_input_dump_device(dump);
	te_hwbuf_set_error(dump->data, -ESHUTDOWN);

	return 0;
}

int ci20_stop_input_dump(struct ci20_input_dump *dump)
{
	struct ci20_channel *channel;
	int rc;

	channel = container_of(dump, struct ci20_channel, dump);

	mutex_lock(&channel->mutex);
	rc = stop_input_dump(dump);
	mutex_unlock(&channel->mutex);

	return 0;
}

// NOTE: does not have length checker
static inline unsigned char get_byte(struct te_split_buffer *sb, u32 ofs)
{
	if (sb->b[0].size > ofs)
		return sb->b[0].data[ofs];
	else
		return sb->b[1].data[(ofs - sb->b[0].size)];
}

static bool find_valid_ts_packets(struct ci20_channel *channel,
				  struct ci20_parse_info *info,
				  u32 *offset)
{
	struct ci20_dump_stats *stats = &channel->dump.stats;
	struct te_split_buffer *sb = &info->sbuf;
	int pos = *offset;
	int i;
	u8 c;
	bool found = false;

	if (!channel->dump.sync) {
		/* Find start point */
		while (pos + (TS_PACKET_SIZE * SYNC_FOUND) <= info->len) {
			for (i = 0; i < SYNC_FOUND; i++) {
				c = get_byte(sb, pos + (TS_PACKET_SIZE * i));
				if (c != TS_SYNCBYTE)
					break;
			}
			if (i == SYNC_FOUND) {
				found = true;
				break;
			}
			pos++;
		}

		if (!found) {
			log_error("sync not found - skip %d bytes", pos);
			*offset = pos;
			return false;
		}

		if (pos > *offset)
			log_warning("sync found - skip %d bytes", pos - *offset);

		info->sidx = pos;
		pos += (TS_PACKET_SIZE * SYNC_FOUND);
		stats->pkt += SYNC_FOUND;
		channel->dump.sync = true;
	} else {
		/* Just resume sync check */
		info->sidx = pos;
	}

	/* Find sync drop point */
	while (pos + TS_PACKET_SIZE <= info->len) {
		c = get_byte(sb, pos);
		if (c != TS_SYNCBYTE) {
			stats->sync_drop++;
			log_warning("sync drop - stop at %d bytes", pos);
			channel->dump.sync = false;
			break;
		}

		pos += TS_PACKET_SIZE;
		stats->pkt++;
		found = true;
	}

	info->eidx = pos;
	*offset = pos;

	return found;
}

static int copy_ts_packets(struct ci20_parse_info *info, char __user *buf)
{
	u8 __user *dst = buf;
	u32 eidx = info->eidx;
	u32 sidx = info->sidx;
	int len = eidx - sidx;
	struct te_split_buffer *sb = &info->sbuf;
	u8 *src;

	if (eidx <= sb->b[0].size) {
		src = sb->b[0].data + sidx;
		if (copy_to_user(dst, src, len))
			return -EFAULT;
	} else if (sidx >= sb->b[0].size) {
		src = sb->b[1].data + (sidx - sb->b[0].size);
		if (copy_to_user(dst, src, len))
			return -EFAULT;
	} else { //split overlap case
		src = sb->b[0].data + sidx;
		len = sb->b[0].size - sidx;
		if (copy_to_user(dst, src, len))
			return -EFAULT;

		dst += len;
		src = sb->b[1].data;
		len = eidx - sb->b[0].size;
		if (copy_to_user(dst, src, len))
			return -EFAULT;
	}

	return (eidx - sidx);
}

static ssize_t read_ts_data(struct ci20_channel *channel,
			    char __user *buf, size_t size)
{
	struct ci20_input_dump *dump = &channel->dump;
	int rc, len, pos = 0;
	struct ci20_parse_info info;
	bool found;
	int written = 0;
	char __user *b = buf;

	rc = te_hwbuf_read_condition(dump->data);
	if (rc < 0) {
		if (rc == -EIO) {
			int err = te_hwbuf_error(dump->data);
			u32 v = DUMPER_INTR_DATA_AL_FULL_CH0 << channel->num;

			if (err == -ENOBUFS) {
				log_error("ch[%d] overflow", channel->num);
			} else {
				log_error("ch[%d] buffer error - %d",
					   channel->num, err);
			}
			te_hwbuf_flush(dump->data);
			te_reg_dumper_set_intr_enable(v, true);
		} else {
			log_error("ch[%d] error detected - %d",
				  channel->num, rc);
		}

		return rc;
	} else if (rc == 0) {
		return 0;
	}

	len = te_hwbuf_avail_size(dump->data);
	if (len == 0)
		return len;

	if (len > size)
		len = size;

	info.len = len;
	te_hwbuf_raw_get_split_rbuf(dump->data, len, &info.sbuf);

	while (pos + (TS_PACKET_SIZE * SYNC_FOUND) <= len) {
		found = find_valid_ts_packets(channel, &info, &pos);

		if (found) {
			rc = copy_ts_packets(&info, b);
			if (rc < 0) {
				written = rc; //error return
				break;
			}
			written += rc;
			b += rc;
		}
	}

	te_hwbuf_read_skip(dump->data, pos);
	return written;
}


ssize_t ci20_read_data(struct ci20_channel *channel, char __user *buf,
		       size_t size)
{
	return read_ts_data(channel, buf, size);
}

static unsigned int poll_data(struct ci20_channel *channel, struct file *file,
			      struct poll_table_struct *wait)
{
	struct te_hwbuf *buf = channel->dump.data;
	int rc;
	unsigned int mask = 0;

	if (channel->dump.state != INPUT_DUMP_RUNNING)
		return POLLERR;

	rc = te_hwbuf_read_condition(buf);
	if (rc) {
		mask = (POLLIN | POLLRDNORM | POLLPRI);
		if (rc < 0)
			mask |= POLLERR;
	}
	log_debug("poll result = %d", rc);

	poll_wait(file, te_hwbuf_wq(buf), wait);

	return mask;
}

unsigned int ci20_wait_data(struct ci20_channel *channel, struct file *file,
			    struct poll_table_struct *wait)
{
	return poll_data(channel, file, wait);
}

/* ************************************************************************** */
/* Initialisation/shutdown functions */
static int probe(struct platform_device *pdev)
{
	struct ci20_device *dev;
	struct ci20_cfg *cfg = ci20_get_config();
	int rc;

	dev = devm_kzalloc(&pdev->dev, sizeof(struct ci20_device) +
			   cfg->num_ch * sizeof(struct ci20_channel),
			   GFP_KERNEL);
	CHECK_ERROR(!dev, goto error, "no memory");

	platform_set_drvdata(pdev, dev);
	te_register_subdev(&pdev->dev, &dev->subdev);

	dev->cfg = cfg;
	dev->num_channel = cfg->num_ch;

	rc = ci20_device_init(dev);
	CHECK_ERROR(rc, goto error, "ci20_device_init");

	ci20_debug_init(dev);

	log_noti("ci20_device probe done");

	return 0;
error:
	panic("ci20_device probe failed\n");
}

static void remove(struct platform_device *pdev)
{
	struct ci20_device *dev = platform_get_drvdata(pdev);

	ci20_debug_release(dev);
	ci20_device_remove(dev);

	log_noti("ci20_device remove done");
}

#if (LINUX_VERSION_CODE < KERNEL_VERSION(6, 5, 0))
static int legacy_remove(struct platform_device *pdev)
{
	remove(pdev);
	return 0;
}
#endif

static void suspend_input_dump(struct ci20_input_dump *d)
{
	unsigned long flag;

	if (d->state != INPUT_DUMP_RUNNING)
		return;

	spin_lock_irqsave(&d->spinlock, flag);
	d->state = INPUT_DUMP_SUSPEND;
	spin_unlock_irqrestore(&d->spinlock, flag);

	stop_input_dump_device(d);
	log_noti("Suspend ch[%d]", d->ch);
}

static int resume_input_dump(struct ci20_input_dump *d)
{
	int rc;

	if (d->state != INPUT_DUMP_SUSPEND)
		return 0;

	log_noti("Resume (ch=%d,addr=0x%08x++0x%x,unit=0x%x)", d->ch,
		 (u32)te_hwbuf_addr(d->data), te_hwbuf_size(d->data),
		 te_hwbuf_unit_size(d->data));

	rc = start_input_dump_device(d);
	if (rc) {
		log_error("Error in start_input_dump_device - %d", rc);
		stop_input_dump_device(d);
		d->state = INPUT_DUMP_IDLE;
	} else {
		d->state = INPUT_DUMP_RUNNING;
	}

	return rc;
}

static int suspend_device(struct ci20_device *dev)
{
	struct ci20_channel *channel;
	int i;

	for (i = 0; i < dev->num_channel; i++) {
		channel = ci20_get_channel(dev, i);
		if (!channel)
			continue;

		mutex_lock(&channel->mutex);

		suspend_input_dump(&channel->dump);

		mutex_unlock(&channel->mutex);
	}

	return 0;
}

static int suspend(struct platform_device *pdev, pm_message_t state)
{
	struct ci20_device *dev = platform_get_drvdata(pdev);
	struct te_device *tdev = get_te_device(dev);

	te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_CI20);

	printk("ci20_device - suspend BEGIN\n");

	suspend_device(dev);

	printk("ci20_device - suspend END\n");

	return 0;
}

static int resume_device(struct ci20_device *dev)
{
	struct ci20_channel *channel;
	int i, rc;

	for (i = 0; i < dev->num_channel; i++) {
		channel = ci20_get_channel(dev, i);
		if (!channel)
			continue;

		mutex_lock(&channel->mutex);

		if (channel->input_port != LX_TE_INPUT_PORT_NONE) {
			rc = config_channel_input(channel, channel->input_port,
						  true, true);
			if (rc) {
				log_error("Error in config_channel_input(%d) "
					  "- %d", channel->num, rc);
			}
		}

		rc = resume_input_dump(&channel->dump);
		if (rc) {
			log_error("Error in resume_input_dump(%d) - %d",
				  channel->num, rc);
		}

		mutex_unlock(&channel->mutex);
	}

	return 0;
}

static int resume(struct platform_device *pdev)
{
	struct ci20_device *dev = platform_get_drvdata(pdev);
	struct te_device *tdev = get_te_device(dev);

	printk("ci20_device - resume BEGIN\n");

	resume_device(dev);

	printk("ci20_device - resume END\n");

	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_CI20);

	return 0;
}

static struct platform_driver platform_driver = {
	.probe = probe,
	.suspend = suspend,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 5, 0))
	.remove = remove,
#else
	.remove = legacy_remove,
#endif
	.resume = resume,
	.driver = {
		.name = CI20_DEVICE_NAME,
	},
};

int ci20_module_init(void)
{
	int ret;

	init_logm();
	ci20_cfg_init();

	ret = platform_driver_register(&platform_driver);
	if (ret) {
		log_error("%s platform driver register failed:%d",
			  CI20_DEVICE_NAME, ret);
		return ret;
	}

	return 0;
}

void ci20_module_exit(void)
{
	platform_driver_unregister(&platform_driver);
}
