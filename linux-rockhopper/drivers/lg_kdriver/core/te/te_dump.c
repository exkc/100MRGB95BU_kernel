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
 *  @date		2018-07-09
 *  @note		Additional information.
 */


#include <linux/poll.h>
#include <lg1k/te/dump.h>
#include <lg1k/te/ipc.h>

#include "hma_alloc.h"
#include "te_impl.h"

#define DUMP_ATSC3_META_SIZE			16
#define DUMP_ATSC3_DATA_SIZE_PER_META		1024

#define DUMP_ARIB2_META_SIZE			16
#define DUMP_ARIB2_DATA_SIZE_PER_META		1024

#define DUMP_MSG_INTERVAL			1000	/* 1000ms */

#define INVALID_VALUE	0xFFFFFFFF

#define dprintf(fmt, args...)	seq_printf(m, fmt, ##args)
#define dprintf_str(n,v)	dprintf(n " : %s\n", v)
#define dprintf_size(n,v) \
	dprintf(n ": %d(%s)\n", v, te_get_readable_size(v))

enum {
	DEBUG_ID_MODULE = 0,
	DEBUG_ID_DUMP_MODE,
	DEBUG_ID_ATSC3_LAYER,
	DEBUG_ID_ATSC3_MODE,
	DEBUG_ID_TS_CLK_SRC,
	DEBUG_ID_TS_CLK_RES,
	DEBUG_ID_TS_MCU_LAYER,
	DEBUG_ID_ARIB2_MODE,
	DEBUG_ID_DVR_MODULE,
	DEBUG_ID_PORT,
	DEBUG_ID_PARAMS,
	DEBUG_ID_STATUS,
	DEBUG_ID_MESSAGE,
	DEBUG_ID_MAX_SIZE,
	DEBUG_ID_BUF_SIZE,
	DEBUG_ID_SIGNAL,
	DEBUG_ID_CI14_SYNCBYTE,
};

struct dump_info {
	enum te_dump_module module;
	enum te_dump_mode mode;
	u8 channel;
	u8 message;		/* 0:no debug msg, others:display progress staus */
	enum te_reg_atsc3_layer atsc3_layer;
	enum te_reg_dumper_mode atsc3_mode;

	enum te_reg_dumper_mode arib2_mode;	/* not support in swtlv */
	enum te_dump_dvr_module dvr_module;
	u8 ts_pid_bypass;
	enum te_dump_layer mcu_dump_layer;
	LX_SDEC_DUMP_TIMESRC_T ts_clk_src;
	LX_SDEC_DUMP_TIMERES_T ts_clk_res;
	u32 max_size;		/* 0:unlimited, others:dump until this size */
	char buffer_name[16];	/* hma pool name */
	u32 buffer_size;	/* used buffer size */
	u32 unit_size;		/* mcu send buffer info every this unit size */
	LX_TE_INPUT_PORT_T port;

	u8 ciplus_syncbyte;
};

struct dump_buffer {
	const char *hma_name;
	phys_addr_t addr;
	u32 size;
	struct te_hwbuf hbuf;
};

struct dump_ctrl {
	char name[32];
	struct te_dump_handle handle;
	struct dump_info info;
	struct te_dump_device *dev;
	struct dump_buffer data;
	struct dump_buffer meta;
	u32 written;
	int signal;
	unsigned long msg_jiffies;	/* time to display written bytes */
	struct te_debug_dir *debug_dir;
	struct list_head dump_node;
};


static DEFINE_MUTEX(dump_mutex);
static struct list_head device_list = LIST_HEAD_INIT(device_list);

static struct dump_info dump_info = {
	.module = TE_DUMP_MODULE_SDEC,
	.mode = TE_DUMP_MODE_INPUT,
	.channel = 4,
	.message = 1,
	.atsc3_layer = ATSC3_DECODER_LAYER_BYPASS,
	.atsc3_mode = DUMPER_MODE_RAW,
	.arib2_mode = DUMPER_MODE_TLV,
	.mcu_dump_layer = TE_DUMP_LAYER_FE_MAIN,
	.ts_pid_bypass = 1,
	.ts_clk_src = LX_SDEC_DUMP_TIMESRC_AUTO,
	.ts_clk_res = LX_SDEC_DUMP_TIMESTAMP_27MHZ,
	.buffer_name = {TE_MEM_SHARED_NAME},
	.buffer_size = 6 * 1024 * 1024,	/* 192KB * 32 = 6 MB */
	.unit_size = 192 * 1024,	/* 192KB */
	.port = LX_TE_INPUT_PORT_NONE,
	.ciplus_syncbyte = 0,	/* use default value */
	.dvr_module = TE_DUMP_DVR_UP,
};

static const struct te_val_str dump_module_str[] = {
	{TE_DUMP_MODULE_SDEC, "SDEC"},
	{TE_DUMP_MODULE_ATSC3, "ATSC3"},
	{TE_DUMP_MODULE_ARIB2, "ARIB2"},
	{TE_DUMP_MODULE_CIPLUS, "CIPLUS"},
	{TE_DUMP_MODULE_DVR, "DVR"},
	{TE_DUMP_MODULE_CA, "CA"},
	{TE_DUMP_MODULE_DELIVERY, "DELIVERY"},
};

static const struct te_val_str dump_mode_str[] = {
	{TE_DUMP_MODE_INPUT, "INPUT"},
	{TE_DUMP_MODE_RAW, "RAW"},
	{TE_DUMP_MODE_USER, "USER"},
};

static const struct te_val_str atsc3_decoder_layer_str[] = {
	{ATSC3_DECODER_LAYER_BYPASS, "BYPASS"},
	{ATSC3_DECODER_LAYER_LGC, "LGC"},
	{ATSC3_DECODER_LAYER_BB, "BB"},
	{ATSC3_DECODER_LAYER_TIME_LGC, "TIME_LGC"},
};

static const struct te_val_str atsc3_mode_str[] = {
	{DUMPER_MODE_RAW, "RAW"},
	{DUMPER_MODE_PVR, "PVR"},
	{DUMPER_MODE_LGC, "LGC"},
};

static const struct te_val_str ts_clock_source_str[] = {
	{LX_SDEC_DUMP_TIMESRC_AUTO, "AUTO"},
	{LX_SDEC_DUMP_TIMESRC_STCC0, "STCC0"},
	{LX_SDEC_DUMP_TIMESRC_STCC1, "STCC1"},
	{LX_SDEC_DUMP_TIMESRC_STCC2, "STCC2"},
	{LX_SDEC_DUMP_TIMESRC_STCC3, "STCC3"},
	{LX_SDEC_DUMP_TIMESRC_GSTCC0, "GSTCC0"},
	{LX_SDEC_DUMP_TIMESRC_GSTCC1, "GSTCC1"},
	{LX_SDEC_DUMP_TIMESRC_GSTCC2, "GSTCC2"},
	{LX_SDEC_DUMP_TIMESRC_GSTCC3, "GSTCC3"},
};

static const struct te_val_str ts_clock_resolution_str[] = {
	{LX_SDEC_DUMP_TIMESTAMP_NOUSE, "NOUSE"},
	{LX_SDEC_DUMP_TIMESTAMP_27MHZ, "27M"},
	{LX_SDEC_DUMP_TIMESTAMP_90KHZ, "90K"},
};

static const struct te_val_str ts_mcu_dump_str[] = {
	{TE_DUMP_LAYER_FE_ISR,	"FE_ISR"},
	{TE_DUMP_LAYER_FE_MAIN, "FE_MAIN"},
	{TE_DUMP_LAYER_BE,	"BE"},
};

static const struct te_val_str arib2_mode_str[] = {
	{DUMPER_MODE_TLV, "TLV"},
	{DUMPER_MODE_RAW, "RAW"},
	{DUMPER_MODE_PVR, "PVR"},
};

static const struct te_val_str dvr_module_str[] = {
	{TE_DUMP_DVR_UP, "UP"},
	{TE_DUMP_DVR_DN, "DN"},
};

static const struct te_type_conv dump_module_list[] = {
	{TE_DUMP_MODULE_NONE, IPC_AUTH_NONE},
	{TE_DUMP_MODULE_SDEC, IPC_AUTH_DUMP_SDEC},
	{TE_DUMP_MODULE_ATSC3, IPC_AUTH_DUMP_ATSC3},
	{TE_DUMP_MODULE_ARIB2, IPC_AUTH_DUMP_ARIB2},
	{TE_DUMP_MODULE_CIPLUS, IPC_AUTH_DUMP_CIPLUS},
	{TE_DUMP_MODULE_DMX, IPC_AUTH_DUMP_DMX},
	{TE_DUMP_MODULE_DVR, IPC_AUTH_DUMP_DVR},
	{TE_DUMP_MODULE_CA, IPC_AUTH_DUMP_CA},
	{TE_DUMP_MODULE_DELIVERY, IPC_AUTH_DUMP_DELIVERY},
};

static const char *get_dump_module_str(u32 module)
{
	return find_match_string(dump_module_str, module, "NONE");
}

static u32 str_to_dump_module(const char *str)
{
	return find_match_value(dump_module_str, str, INVALID_VALUE);
}

static const char *get_dump_mode_str(u32 mode)
{
	return find_match_string(dump_mode_str, mode, "Invalid");
}

static u32 str_to_dump_mode(const char *str)
{
	return find_match_value(dump_mode_str, str, INVALID_VALUE);
}

static const char *get_atsc3_layer_str(u32 layer)
{
	return find_match_string(atsc3_decoder_layer_str, layer, "Invalid");
}

static const char *get_atsc3_mode_str(u32 mode)
{
	return find_match_string(atsc3_mode_str, mode, "Invalid");
}

static u32 str_to_atsc3_layer(const char *str)
{
	return find_match_value(atsc3_decoder_layer_str, str, INVALID_VALUE);
}

static u32 str_to_atsc3_mode(const char *str)
{
	return find_match_value(atsc3_mode_str, str, INVALID_VALUE);
}

static const char *get_ts_clk_src_str(u32 src)
{
	return find_match_string(ts_clock_source_str, src, "Invalid");
}

static u32 str_to_ts_clk_src(const char *str)
{
	return find_match_value(ts_clock_source_str, str, INVALID_VALUE);
}

static const char *get_ts_clk_res_str(u32 res)
{
	return find_match_string(ts_clock_resolution_str, res, "Invalid");
}

static u32 str_to_ts_clk_res(const char *str)
{
	return find_match_value(ts_clock_resolution_str, str, INVALID_VALUE);
}

static const char *get_mcu_dump_layer_str(u32 layer)
{
	return find_match_string(ts_mcu_dump_str, layer, "Invalid");
}

static u32 str_to_mcu_dump_layer(const char *str)
{
	return find_match_value(ts_mcu_dump_str, str, INVALID_VALUE);
}

static const char *get_arib2_mode_str(u32 mode)
{
	return find_match_string(arib2_mode_str, mode, "Invalid");
}

static u32 str_to_arib2_mode(const char *str)
{
	return find_match_value(arib2_mode_str, str, INVALID_VALUE);
}

static const char *get_dvr_module_str(u32 module)
{
	return find_match_string(dvr_module_str, module, "Invalid");
}

static u32 str_to_dvr_module(const char *str)
{
	return find_match_value(dvr_module_str, str, INVALID_VALUE);
}

static enum ipc_authority_module get_ipc_auth_module(enum te_dump_module module)
{
	const struct te_type_conv *l = dump_module_list;
	u32 n = ARRAY_SIZE(dump_module_list);

	return te_convert_to_type0(l, n, module, INVALID_VALUE);
}

static struct te_dump_device *get_dump_device(enum te_dump_module module)
{
	struct te_dump_device *dev;

	list_for_each_entry(dev, &device_list, list) {
		if (dev->module == module) {
			return dev;
		}
	}

	return NULL;
}

static int init_dump_buffer(struct dump_buffer *buf, const char *hma_name,
			    u32 unit_size, u32 size, u32 flags)
{
	int rc;

	if (!size) {
		buf->addr = 0;
		buf->size = 0;
		return 0;
	}

	if (unit_size) {
		u32 remained = size % unit_size;
		if (remained)
			size -= remained;
	}

	buf->addr = hma_alloc_user(hma_name, size, 4096, "te.dump");
	if (buf->addr == 0)
		return -ENOMEM;

	rc = te_hwbuf_init(&buf->hbuf, buf->addr, size, unit_size, flags);
	if (rc) {
		hma_free(hma_name, buf->addr);
		buf->addr = 0;
		return rc;
	}
	buf->hma_name = hma_name;
	buf->size = size;

	return 0;
}

static void release_dump_buffer(struct dump_buffer *buf)
{
	if (buf->addr) {
		te_hwbuf_release(&buf->hbuf);
		hma_free(buf->hma_name, buf->addr);
		buf->addr = 0;
	}
}

static int init_buffer(struct dump_ctrl *ctrl, const char *hma_name,
		       u32 unit_size, u32 size, u32 meta_size)
{
	int rc;

	rc = init_dump_buffer(&ctrl->data, hma_name, unit_size, size,
			      TE_BUF_FLAG_VMAP_CACHED);
	if (rc) {
		return rc;
	}

	rc = init_dump_buffer(&ctrl->meta, hma_name, 0, meta_size, 0);
	if (rc) {
		release_dump_buffer(&ctrl->data);
		return rc;
	}

	return 0;
}

static void release_buffer(struct dump_ctrl *ctrl)
{
	release_dump_buffer(&ctrl->data);
	release_dump_buffer(&ctrl->meta);
}

static int dump_start(struct dump_ctrl *ctrl)
{
	int rc;
	struct te_dump_cfg cfg;
	struct dump_info *info = &ctrl->info;
	u32 meta_size;

	ctrl->dev = get_dump_device(info->module);
	if (!ctrl->dev)
		return -ENODEV;

	memset(&cfg, 0, sizeof(cfg));

	if (info->module == TE_DUMP_MODULE_SDEC) {
		cfg.sdec.layer = info->mcu_dump_layer;
		cfg.sdec.pid_bypass = info->ts_pid_bypass;
		cfg.sdec.clk_src = info->ts_clk_src;
		cfg.sdec.clk_res = info->ts_clk_res;
		meta_size = 0;
	} else if (info->module == TE_DUMP_MODULE_DVR) {
		meta_size = 0;
		cfg.dvr.module = info->dvr_module;
	} else if (info->module == TE_DUMP_MODULE_ATSC3) {
		cfg.atsc3.layer = info->atsc3_layer;
		cfg.atsc3.mode = info->atsc3_mode;
		meta_size = 4096;	/* dummy buffer */
	} else if (info->module == TE_DUMP_MODULE_ARIB2) {
		cfg.arib2.mode = info->arib2_mode;
		meta_size = 4096;	/* dummy buffer */
	} else if (info->module == TE_DUMP_MODULE_CIPLUS) {
		cfg.ci14.syncbyte = info->ciplus_syncbyte;
		meta_size = 0;
	} else if (info->module == TE_DUMP_MODULE_CA) {
		meta_size = 0;
	} else if (info->module == TE_DUMP_MODULE_DELIVERY) {
		meta_size = 0;
	} else {
		log_error("invalid module(%d)", info->module);
		return -EINVAL;
	}

	rc = init_buffer(ctrl, info->buffer_name, info->unit_size,
			 info->buffer_size, meta_size);
	if (rc)
		return rc;

	cfg.mode = info->mode;
	cfg.ch = info->channel;
	cfg.port = info->port;
	cfg.data = &ctrl->data.hbuf;
	if (meta_size)
		cfg.meta = &ctrl->meta.hbuf;
	cfg.flags = 0;

	rc = ctrl->dev->start(ctrl->dev, &ctrl->handle, &cfg);
	if (rc)
		release_buffer(ctrl);

	return rc;
}

static void dump_stop(struct dump_ctrl *ctrl)
{
	ctrl->dev->stop(ctrl->dev, &ctrl->handle);
	release_buffer(ctrl);
}

static void show_dump_params(struct dump_info *di, struct seq_file *m)
{
	dprintf_str("module", get_dump_module_str(di->module));
	dprintf("channel : %d\n", di->channel);
	dprintf_str("port", te_input_port_to_str(di->port));
	dprintf_str("mode", get_dump_mode_str(di->mode));
	dprintf("message : %d\n", di->message);
	dprintf_size("max_size", di->max_size);
	dprintf("buffer name : %s\n", dump_info.buffer_name);
	dprintf_size("buffer size", di->buffer_size);
	dprintf_size("unit size", di->unit_size);
	dprintf_str("atsc3 layer", get_atsc3_layer_str(di->atsc3_layer));
	dprintf_str("atsc3 mode", get_atsc3_mode_str(di->atsc3_mode));
	dprintf_str("arib2 mode", get_arib2_mode_str(di->arib2_mode));
	dprintf_str("dvr module", get_dvr_module_str(di->dvr_module));
	dprintf("ts pid bypass : %d\n", di->ts_pid_bypass);
	dprintf_str("ts clock source", get_ts_clk_src_str(di->ts_clk_src));
	dprintf_str("ts clock resolution", get_ts_clk_res_str(di->ts_clk_res));
	dprintf_str("ts mcu layer", get_mcu_dump_layer_str(di->mcu_dump_layer));
	dprintf("ciplus syncbyte : 0x%02x\n", di->ciplus_syncbyte);
}

static int dump_show(struct te_debug_item *item, struct seq_file *m)
{
	struct dump_ctrl *ctrl = item->private;

	switch (item->flags) {
	case DEBUG_ID_STATUS:
		show_dump_params(&ctrl->info, m);
		dprintf_size("written size", ctrl->written);
		break;

	default:
		return -EPERM;
	}

	return 0;
}

static int dump_write(struct te_debug_item *item, char *str)
{
	struct dump_ctrl *ctrl = item->private;

	switch (item->flags) {
	case DEBUG_ID_MESSAGE:
		ctrl->info.message = simple_strtoul(str, (char **)NULL, 0);
		break;

	case DEBUG_ID_MAX_SIZE:
		ctrl->info.max_size = te_parse_size(str);
		break;

	case DEBUG_ID_SIGNAL:
		ctrl->signal = 1;
		te_hwbuf_set_error(&ctrl->data.hbuf, -ESHUTDOWN);
		break;

	default:
		return -EPERM;
	}

	return 0;
}

static const struct te_debug_simple_ops status_ops = {
	.show = dump_show,
	.write = dump_write,
};

static const struct te_debug_item_info status_list[] = {
	DBGITM_SIM_R("status", &status_ops, DEBUG_ID_STATUS),
	DBGITM_SIM_W("message", &status_ops, DEBUG_ID_MESSAGE),
	DBGITM_SIM_W("max_size", &status_ops, DEBUG_ID_MAX_SIZE),
	DBGITM_SIM_W("signal", &status_ops, DEBUG_ID_SIGNAL),
};

static bool is_exist_dump_name(struct te_dev_dump *dump, const char *name)
{
	struct dump_ctrl *ctrl;

	list_for_each_entry(ctrl, &dump->dump_list, dump_node) {
		if (!strcmp(ctrl->name, name))
			return true;
	}
	return false;
}

static void create_debug_status(struct te_device *dev, struct dump_ctrl *ctrl)
{
	int i;

	/* search unused name */
	for (i = 0; i < 10; i++) {
		snprintf(ctrl->name, sizeof(ctrl->name), "%d", i);
		if (!is_exist_dump_name(&dev->dump, ctrl->name))
			break;
	}

	if (i == 10)
		snprintf(ctrl->name, sizeof(ctrl->name), "%p", (void *)ctrl);

	ctrl->debug_dir = te_debug_create_dir(ctrl->name, dev->dump.debug_dir);
	if (!ctrl->debug_dir) {
		log_error("can't te_debug_create_dir(%s)\n", ctrl->name);
		return;
	}

	debug_create_item_files(status_list, ctrl, ctrl->debug_dir);

	log_noti("create dump node(%s)\n", ctrl->name);
}

static void remove_debug_status(struct dump_ctrl *ctrl)
{
	if (ctrl->debug_dir) {
		te_debug_remove_dir(ctrl->debug_dir);
	}
}

static int dump_open(struct inode *inode, struct file *file)
{
	int rc;
	struct dump_ctrl *ctrl;
	struct te_debug_item *item = te_debug_get_inode_private(inode);
	struct te_device *dev = item->private;
	enum ipc_authority_module auth_module;

	auth_module = get_ipc_auth_module(dump_info.module);
	rc = te_get_authority(auth_module);
	if (rc)
		return rc;

	ctrl = kzalloc(sizeof(*ctrl), GFP_KERNEL);
	if (!ctrl)
		return -ENOMEM;

	mutex_lock(&dump_mutex);
	ctrl->info = dump_info;	/* TODO: no lock for dump_info */

	rc = dump_start(ctrl);
	if (rc) {
		kfree(ctrl);
	} else {
		create_debug_status(dev, ctrl);
		list_add_tail(&ctrl->dump_node, &dev->dump.dump_list);
		ctrl->msg_jiffies =
		    jiffies + msecs_to_jiffies(DUMP_MSG_INTERVAL);
		file->private_data = ctrl;
	}
	mutex_unlock(&dump_mutex);

	return rc;
}

static int dump_release(struct inode *inode, struct file *file)
{
	struct dump_ctrl *ctrl = file->private_data;

	mutex_lock(&dump_mutex);
	list_del(&ctrl->dump_node);
	remove_debug_status(ctrl);
	dump_stop(ctrl);
	mutex_unlock(&dump_mutex);

	kfree(ctrl);

	return 0;
}

static ssize_t dump_read(struct file *file, char __user *data, size_t size,
			 loff_t *off)
{
	int rc;
	struct dump_ctrl *ctrl = file->private_data;
	struct dump_info *info = &ctrl->info;

	if (info->max_size && ctrl->written >= info->max_size) {
		log_noti("reached max size(%d)...", info->max_size);
		return 0;
	}

	if (ctrl->signal) {
		log_noti("detected signal by user (STOP)");
		return 0;
	}

	rc = te_hwbuf_io_read(&ctrl->data.hbuf, data, size,
			      file->f_flags & O_NONBLOCK);
	if (rc > 0)
		ctrl->written += rc;
	else if (rc == -EIO) {
		int err = te_hwbuf_error(&ctrl->data.hbuf);
		if (err == -ESHUTDOWN) {
			rc = 0;
		} else if (err == -ENOBUFS) {
			log_error("detected overflow");
			te_hwbuf_flush(&ctrl->data.hbuf);
		} else {
			log_error("dump error detected - %d", err);
		}
	}

	if (info->message) {
		if (time_is_before_jiffies(ctrl->msg_jiffies)) {
			log_noti("written(#%s): %s\n", ctrl->name,
				 te_get_readable_size(ctrl->written));
			ctrl->msg_jiffies =
			    jiffies + msecs_to_jiffies(DUMP_MSG_INTERVAL);
		}
	}

	return rc;
}

static unsigned int dump_poll(struct file *file, struct poll_table_struct *wait)
{
	struct dump_ctrl *ctrl = file->private_data;
	struct te_hwbuf *buf;
	unsigned int mask = 0;
	int rc;

	if (ctrl->signal)
		mask |= POLLERR;

	buf = &ctrl->data.hbuf;
	rc = te_hwbuf_read_condition(buf);
	if (rc) {
		mask |= (POLLIN | POLLRDNORM | POLLPRI);
		if (rc < 0)
			mask |= POLLERR;
	}

	poll_wait(file, te_hwbuf_wq(buf), wait);

	return mask;
}

static int debug_show(struct te_debug_item *item, struct seq_file *m)
{
	struct dump_info *di = &dump_info;

	switch (item->flags) {
	case DEBUG_ID_MODULE:
		dprintf("%s\n", get_dump_module_str(di->module));
		break;

	case DEBUG_ID_DUMP_MODE:
		dprintf("%s\n", get_dump_mode_str(di->mode));
		break;

	case DEBUG_ID_ATSC3_LAYER:
		dprintf("%s\n", get_atsc3_layer_str(di->atsc3_layer));
		break;

	case DEBUG_ID_ATSC3_MODE:
		dprintf("%s\n", get_atsc3_mode_str(di->atsc3_mode));
		break;

	case DEBUG_ID_ARIB2_MODE:
		dprintf("%s\n", get_arib2_mode_str(di->arib2_mode));
		break;

	case DEBUG_ID_TS_CLK_SRC:
		dprintf("%s\n", get_ts_clk_src_str(di->ts_clk_src));
		break;

	case DEBUG_ID_TS_CLK_RES:
		dprintf("%s\n", get_ts_clk_res_str(di->ts_clk_res));
		break;

	case DEBUG_ID_TS_MCU_LAYER:
		dprintf("%s\n", get_mcu_dump_layer_str(di->mcu_dump_layer));
		break;

	case DEBUG_ID_PORT:
		dprintf("%s\n", te_input_port_to_str(di->port));
		break;

	case DEBUG_ID_PARAMS:
		show_dump_params(di, m);
		break;

	case DEBUG_ID_MAX_SIZE:
		dprintf("%u\n", di->max_size);
		break;

	case DEBUG_ID_BUF_SIZE:
		dprintf("%u\n", di->buffer_size);
		break;

	default:
		return -EPERM;
	}

	return 0;
}

static int debug_write(struct te_debug_item *item, char *str)
{
	int ret = 0;
	u32 v;
	struct dump_info *di = &dump_info;

	switch (item->flags) {
	case DEBUG_ID_MODULE:
		v = str_to_dump_module(str);
		if (v == INVALID_VALUE)
			ret = -EINVAL;
		else
			di->module = v;
		break;

	case DEBUG_ID_DUMP_MODE:
		v = str_to_dump_mode(str);
		if (v == INVALID_VALUE)
			ret = -EINVAL;
		else
			di->mode = v;
		break;

	case DEBUG_ID_ATSC3_LAYER:
		v = str_to_atsc3_layer(str);
		if (v == INVALID_VALUE)
			ret = -EINVAL;
		else
			di->atsc3_layer = v;
		break;

	case DEBUG_ID_ATSC3_MODE:
		v = str_to_atsc3_mode(str);
		if (v == INVALID_VALUE)
			ret = -EINVAL;
		else
			di->atsc3_mode = v;
		break;

	case DEBUG_ID_ARIB2_MODE:
		v = str_to_arib2_mode(str);
		if (v == INVALID_VALUE)
			ret = -EINVAL;
		else
			di->arib2_mode = v;
		break;
	case DEBUG_ID_DVR_MODULE:
		v = str_to_dvr_module(str);
		if (v == INVALID_VALUE)
			ret = -EINVAL;
		else
			di->dvr_module = v;
		break;
	case DEBUG_ID_TS_CLK_SRC:
		v = str_to_ts_clk_src(str);
		if (v == 0xFFFFFFFF)
			ret = -EINVAL;
		else
			di->ts_clk_src = v;
		break;

	case DEBUG_ID_TS_CLK_RES:
		v = str_to_ts_clk_res(str);
		if (v == 0xFFFFFFFF)
			ret = -EINVAL;
		else
			di->ts_clk_res = v;
		break;

	case DEBUG_ID_TS_MCU_LAYER:
		v = str_to_mcu_dump_layer(str);
		if (v == 0xFFFFFFFF)
			ret = -EINVAL;
		else
			di->mcu_dump_layer = v;
		break;

	case DEBUG_ID_PORT:
		v = te_str_to_input_port(str);
		if (v == LX_TE_INPUT_PORT_INVALID)
			ret = -EINVAL;
		else
			di->port = v;
		break;

	case DEBUG_ID_MAX_SIZE:
		di->max_size = te_parse_size(str);
		break;

	case DEBUG_ID_BUF_SIZE:
		di->buffer_size = te_parse_size(str);
		break;

	default:
		ret = -EPERM;
	}

	return ret;
}


static const struct te_debug_simple_ops debug_ops = {
	.show = debug_show,
	.write = debug_write,
};

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,11,0)
static const struct proc_ops reader_fops = {
	.proc_open = dump_open,
	.proc_read = dump_read,
	.proc_release = dump_release,
	.proc_poll = dump_poll
};
#else
static const struct file_operations reader_fops = {
	.open = dump_open,
	.read = dump_read,
	.release = dump_release,
	.poll = dump_poll,
};
#endif

static const struct te_debug_item_info config_list[] = {
	DBGITM_SIM("module", &debug_ops, DEBUG_ID_MODULE),
	DBGITM_SIM("mode", &debug_ops, DEBUG_ID_DUMP_MODE),
	DBGITM_SIM("atsc3_layer", &debug_ops, DEBUG_ID_ATSC3_LAYER),
	DBGITM_SIM("atsc3_mode", &debug_ops, DEBUG_ID_ATSC3_MODE),
	DBGITM_SIM("arib2_mode", &debug_ops, DEBUG_ID_ARIB2_MODE),
	DBGITM_SIM("dvr_module", &debug_ops, DEBUG_ID_DVR_MODULE),
	DBGITM_SIM("ts_clk_src", &debug_ops, DEBUG_ID_TS_CLK_SRC),
	DBGITM_SIM("ts_clk_res", &debug_ops, DEBUG_ID_TS_CLK_RES),
	DBGITM_NUM("ts_pid_bypass", &dump_info.ts_pid_bypass),
	DBGITM_SIM("ts_mcu_layer", &debug_ops, DEBUG_ID_TS_MCU_LAYER),
	DBGITM_SIM("port", &debug_ops, DEBUG_ID_PORT),
	DBGITM_SIM_R("params", &debug_ops, DEBUG_ID_PARAMS),
	DBGITM_NUM("channel", &dump_info.channel),
	DBGITM_NUM("message", &dump_info.message),
	DBGITM_SIM("max_size", &debug_ops, DEBUG_ID_MAX_SIZE),
	DBGITM_STR("buffer_name", dump_info.buffer_name),
	DBGITM_SIM("buffer_size", &debug_ops, DEBUG_ID_BUF_SIZE),
	DBGITM_NUM("unit_size", &dump_info.unit_size),
	DBGITM_HEX("ciplus_syncbyte", &dump_info.ciplus_syncbyte),
	DBGITM_FOPS("reader", &reader_fops, 0),
};

int te_dump_register_device(struct te_dump_device *dev)
{
	struct te_dump_device *cur;

	mutex_lock(&dump_mutex);
	list_for_each_entry(cur, &device_list, list) {
		if (cur->module == dev->module) {
			mutex_unlock(&dump_mutex);
			return -EEXIST;
		}
	}
	list_add_tail(&dev->list, &device_list);
	mutex_unlock(&dump_mutex);

	return 0;
}

static int dump_dev_init(struct te_device *dev)
{
	int ret;
	struct te_dev_dump *d = &dev->dump;

	INIT_LIST_HEAD(&d->dump_list);

	d->debug_dir = te_debug_create_dir("dump", dev->debug.dir);
	CHECK_ERROR(!d->debug_dir, return -EIO, "Error in te_debug_create_dir");

	ret = debug_create_item_files(config_list, dev, d->debug_dir);
	CHECK_ERROR(ret, return ret, "Err in debug_create_item_files");

	return 0;
}

static void dump_dev_release(struct te_device *dev)
{

}

const struct te_sub_driver te_dump_driver = {
	.name = "te_dump",
	.init = dump_dev_init,
	.release = dump_dev_release,
};
