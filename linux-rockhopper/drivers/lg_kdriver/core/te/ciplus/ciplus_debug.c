/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2017 by LG Electronics Inc.
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
 *  @author	Ilkyu Kim ( ilkyu.kim@lge.com)
 *  @version	1.0
 *  @date		2017-07-03
 *  @note		Additional information.
 */

#include <lg1k/te/ipc.h>
#include <lg1k/te/io.h>

#include "ciplus_impl.h"

enum {
	DEBUG_ID_VERSION	= 0,
	DEBUG_ID_MODE,
	DEBUG_ID_BYPASS,
	DEBUG_ID_MAX,
};

enum {
	STATUS_BITRATE		= (0x1 << CIPLUS_DEBUG_STATUS_BITRATE),
	STATUS_KDRV		= (0x1 << CIPLUS_DEBUG_STATUS_KDRV),
	STATUS_MCU		= (0x1 << CIPLUS_DEBUG_STATUS_MCU),
	STATUS_ALL		= 0xFFFFF,
};

static int debug_show_mcu_status(struct ciplus_device *dev, struct seq_file *m)
{
	int i;
	u32 rptr, wptr, pkt_cnt, ovf;

	seq_printf(m, "Upload Buffer Status(IPC)\n");
	seq_printf(m, "ch:rptr\t\twptr\t\tpkt_cnt\t\tovf_cnt\n");

	/* TODO: Consider Bitrate Calculation */
	for (i = 0; i < dev->num_channel; i++) {
		TE_IPC_GetCIPLUSUploadStatus(i, &rptr, &wptr, &pkt_cnt, &ovf);
		seq_printf(m, "%02d:0x%08x\t0x%08x\t%8d\t%8d\n", i, rptr, wptr,
			   pkt_cnt, ovf);
	}

	seq_printf(m, "\n\nDownload Buffer Status(IPC)\n");
	seq_printf(m, "ch:rptr\t\twptr\t\tpkt_cnt\t\tovf_cnt\n");

	/* TODO: Consider Bitrate Calculation */
	for (i = 0; i < dev->num_channel; i++) {
		TE_IPC_GetCIPLUSDownloadStatus(i, &rptr, &wptr, &pkt_cnt, &ovf);
		seq_printf(m, "%02d:0x%08x\t0x%08x\t%8d\t%8d\n", i, rptr, wptr,
			   pkt_cnt, ovf);
	}

	return 0;
}

//FIXME: Print logs should be similar with SDEC/DEMUX (PORT, TPI)
static int debug_show_kdrv_status(struct ciplus_device *dev, struct seq_file *m)
{
	struct ciplus_channel *channel;
	const char *dest;
	int i;

	seq_printf(m, "Channel Status\n");
	seq_printf(m, "ch: en      syncbyte src   tei dest PIDF\n");

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];

		seq_printf(m, "%02d: %-7s ", i,
			   (channel->en) ? "Enable" : "Disable");
		if (channel->en) {
			seq_printf(m, "0x%02x     %-5s %d   ",
				   channel->syncbyte,
				   (channel->inbuf.src) ? "IP" : "DEMOD",
				   channel->inbuf.teifilter);
			if (channel->host_player)
				dest = "MCU";
			else
				dest = "BOTH";

			seq_printf(m, "%-4s ", dest);

			if (channel->inbuf.pid_bypass)
				seq_printf(m, "BYPASS");
			else
				ciplus_pidf_show_status(channel, m);
		}
		seq_printf(m, "\n");
	}
	seq_printf(m, "\n");

	return 0;
}

static int debug_show(struct te_debug_item *item, struct seq_file *m)
{
	int ret = 0;

	switch (item->flags) {
	case DEBUG_ID_VERSION:
		seq_printf(m, "20181102.6\n");
		break;

	default:
		ret = -EPERM;
		break;
	}

	return ret;
}

static int debug_set_bypass(struct ciplus_device *dev, const char *cmd)
{
	int rc;
	int ch, en;
	struct ciplus_channel *channel;

	rc = sscanf(cmd, "%d %d", &ch, &en);
	if (rc != 2)
		return -EINVAL;

	channel = ciplus_get_channel(dev, ch);
	if (!channel)
		return -EINVAL;

	ciplus_pidf_enable_bypass(channel, en ? true : false);
	return 0;
}

static int debug_write(struct te_debug_item *item, char *str)
{
	struct ciplus_device *dev = item->private;
	int ret = 0;
	u32 val;

	switch (item->flags) {
	case DEBUG_ID_MODE:
		val = simple_strtoul(str, (char **)NULL, 0);
		ret = ciplus_set_debug_mode(dev, (val) ? true : false);
		break;
	case DEBUG_ID_BYPASS:
		ret = debug_set_bypass(dev, str);
		break;
	default:
		ret = -EPERM;
		break;
	}

	return ret;
}

static int debug_stat_show(struct te_debug_item *item, struct seq_file *m)
{
	int i;
	struct ciplus_device *dev = item->private;

	for (i = 0; i < CIPLUS_DEBUG_STATUS_MAX; i++) {
		if (item->flags & (0x1 << i)) {
			ciplus_debug_show_t func = dev->debug.show_status[i];
			if (func)
				func(dev, m);
		}
	}

	return 0;
}

int ciplus_debug_register_status_show(struct ciplus_device *dev,
				      enum ciplus_debug_status status,
				      ciplus_debug_show_t show)
{
	struct ciplus_debug *d = &dev->debug;

	if (status >= CIPLUS_DEBUG_STATUS_MAX)
		return -EINVAL;

	d->show_status[status] = show;

	return 0;
}

static const struct te_debug_simple_ops debug_ops = {
	.show = debug_show,
	.write = debug_write,
};

static const struct te_debug_simple_ops debug_stat_ops = {
	.show = debug_stat_show,
};

static const struct te_debug_item_info debug_list[] = {
	DBGITM_SIM_R("version", &debug_ops, DEBUG_ID_VERSION),
	DBGITM_SIM_W("debug_mode", &debug_ops, DEBUG_ID_MODE),
	DBGITM_SIM_W("bypass", &debug_ops, DEBUG_ID_BYPASS),

	DBGITM_SIM_R("bitrate", &debug_stat_ops, STATUS_BITRATE),
	DBGITM_SIM_R("status_kdrv", &debug_stat_ops, STATUS_KDRV),
	DBGITM_SIM_R("status_mcu", &debug_stat_ops, STATUS_MCU),
	DBGITM_SIM_R("status", &debug_stat_ops, STATUS_ALL),
};

static int debug_dev_init(struct ciplus_device *dev)
{
	int ret;
	struct ciplus_debug *d = &dev->debug;

	d->dir = te_debug_create_dir(CIPLUS_MODULE, NULL);
	CHECK_ERROR(!d->dir, return -EIO, "Err in te_debug_create_dir");

	ret = debug_create_item_files(debug_list, dev, d->dir);

	ciplus_debug_register_status_show(dev, CIPLUS_DEBUG_STATUS_KDRV,
					  debug_show_kdrv_status);

	ciplus_debug_register_status_show(dev, CIPLUS_DEBUG_STATUS_MCU,
					  debug_show_mcu_status);

	return ret;
}

static void debug_dev_release(struct ciplus_device *dev)
{
	te_debug_remove_dir(dev->debug.dir);
}

const struct ciplus_sub_driver ciplus_debug_driver = {
	.name = "ciplus_debug",
	.init = debug_dev_init,
	.release = debug_dev_release,
};

/** @} */
