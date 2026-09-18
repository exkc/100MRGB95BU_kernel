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

#include <lg1k/te/io.h>
#include <lg1k/te/dump.h>
#include <lg1k/te/mcu.h>
#include <lg1k/te/ipc.h>

#include "sdec_impl.h"

#define INPUT_DUMP_WARNING_SIZE		30	/* if free size under 30% */

#define MONITOR_INTERVAL		500	/* 500ms */
#define MONITOR_MESSAGE_COUNT_MAX	10

#define TRACE_ENTER(fmt,args...)	log_io("@%s(" fmt ")", __func__, ##args)
#define TRACE_EXIT(fmt,args...)		log_io("~%s(" fmt ")", __func__, ##args)

static DEFINE_MUTEX(io_mutex);

static IPC_DUMP_TIMESTAMP_TYPE_T get_ipc_timestamp(LX_SDEC_DUMP_TIMERES_T res)
{
	switch (res) {
	case LX_SDEC_DUMP_TIMESTAMP_27MHZ:
		return IPC_TIMESTAMP_27MHZ_PRECISION;
	case LX_SDEC_DUMP_TIMESTAMP_90KHZ:
		return IPC_TIMESTAMP_90KHZ_PRECISION;
	case LX_SDEC_DUMP_TIMESTAMP_NOUSE:
	default:
		return IPC_TIMESTAMP_NO_USE;
	}
}

static IPC_DUMP_CLK_SRC_T get_ipc_time_source(LX_SDEC_DUMP_TIMESRC_T src)
{
	const struct te_type_conv list[] = {
		{LX_SDEC_DUMP_TIMESRC_STCC0, IPC_DUMP_CLK_STCC0},
		{LX_SDEC_DUMP_TIMESRC_STCC1, IPC_DUMP_CLK_STCC1},
		{LX_SDEC_DUMP_TIMESRC_STCC2, IPC_DUMP_CLK_STCC2},
		{LX_SDEC_DUMP_TIMESRC_STCC3, IPC_DUMP_CLK_STCC3},
		{LX_SDEC_DUMP_TIMESRC_GSTCC0, IPC_DUMP_CLK_GSTCC0},
		{LX_SDEC_DUMP_TIMESRC_GSTCC1, IPC_DUMP_CLK_GSTCC1},
		{LX_SDEC_DUMP_TIMESRC_GSTCC2, IPC_DUMP_CLK_GSTCC2},
		{LX_SDEC_DUMP_TIMESRC_GSTCC3, IPC_DUMP_CLK_GSTCC3},
	};

	return convert_to_type1(list, src, IPC_DUMP_CLK_GSTCC1);
}

/* monitor start */
struct sdec_channel_status {
	enum lx_te_input_port input_port;

	u32 pkt_count;	/* all packets including err_pkt */
	u32 err_count;	/* mcu error count */
	u32 ovf_count;	/* mcu overflow count */
};

static void detect_channel_input(struct sdec_channel_monitor *m,
				 struct sdec_channel_status *s)
{
	bool is_error;
	int msg_cnt;
#define log_packet(fmt, args...)  log_noti("%s - " fmt, m->name, ##args)

	if (m->pkt_count == s->pkt_count) {
		if (m->no_input == false) {
			log_packet("no input packet");

			m->no_input = true;
			m->message_count = 0;

			TE_REG_SetTsBufIntrEnable(m->intr, true);
		}
		return;
	}

	if (m->no_input == true) {
		log_packet("recover channel input");

		TE_REG_SetTsBufIntrEnable(m->intr, false);
		m->no_input = false;
	}

	msg_cnt = m->message_count;
	is_error = false;
	if (m->ovf_count != s->ovf_count || m->err_count != s->err_count) {
		if (msg_cnt < MONITOR_MESSAGE_COUNT_MAX) {
			log_packet("pkt:%u(%u/%u) ovf:%u(%u/%u) err:%u(%u/%u)",
				   s->pkt_count - m->pkt_count,
				   m->pkt_count, s->pkt_count,
				   s->ovf_count - m->ovf_count,
				   m->ovf_count, s->ovf_count,
				   s->err_count - m->err_count,
				   m->err_count, s->err_count);
		}
		is_error = true;
	}

	if (is_error) {
		if (msg_cnt < MONITOR_MESSAGE_COUNT_MAX) {
			msg_cnt++;
			if (msg_cnt == MONITOR_MESSAGE_COUNT_MAX) {
				log_packet("disable monitor message");
			}
		}
	} else {
		if (msg_cnt > 0) {
			if (msg_cnt == MONITOR_MESSAGE_COUNT_MAX) {
				log_packet("re-enable monitor message");
				msg_cnt = 0;
			} else {
				msg_cnt--;
			}
		}
	}

	m->message_count = msg_cnt;
}

static void get_channel_status(struct sdec_channel *channel,
			       struct sdec_channel_status *status)
{
	IPC_TS_CH_STATUS_T ts;
	u32 count;

	TE_REG_GetChannelPktCount(channel->num, &count);
	TE_IPC_GetChannelStatus(channel->num, &ts);

	status->pkt_count = count;
	status->ovf_count = ts.overflow_cnt;
	status->err_count = ts.syncbyte_errors;
}

static void check_channel_status(struct sdec_channel *channel)
{
	struct sdec_channel_status status;
	struct sdec_channel_monitor *m;

	m = &channel->monitor;

	get_channel_status(channel, &status);
	detect_channel_input(m, &status);

	m->pkt_count = status.pkt_count;
	m->err_count = status.err_count;
	m->ovf_count = status.ovf_count;
}

static void init_channel_status(struct sdec_channel *channel)
{
	struct sdec_channel_status status;
	struct sdec_channel_monitor *m;

	get_channel_status(channel, &status);

	m = &channel->monitor;
	m->no_input = true;
	m->message_count = 0;

	m->pkt_count = status.pkt_count;
	m->err_count = status.err_count;
	m->ovf_count = status.ovf_count;
}

static void channel_monitor_work(struct work_struct *work)
{
	struct sdec_channel_monitor *m;
	struct sdec_channel *channel;

	channel = container_of(to_delayed_work(work), struct sdec_channel,
			       monitor.work);

	m = &channel->monitor;

	mutex_lock(&m->mutex);
	if (m->enable == false) {
		/* input config is not set */
		mutex_unlock(&m->mutex);
		return;
	}

	if (m->enable_mask == 0) {
		/* av pid filter is not set */
		mutex_unlock(&m->mutex);
		return;
	}

	check_channel_status(channel);

	schedule_delayed_work(&m->work, msecs_to_jiffies(m->interval));

	mutex_unlock(&m->mutex);
}

static void control_channel_monitor(struct sdec_channel *channel, bool en)
{
	struct sdec_channel_monitor *m = &channel->monitor;
	enum te_reg_tpi_port tpi;

	mutex_lock(&m->mutex);

	TE_REG_SetTsBufIntrEnable(m->intr, false);

	m->enable = en;
	if (en) {
		tpi = te_input_port_to_reg_tpi_port(channel->input_port);
		snprintf(m->name, sizeof(m->name), "ch%u(%s/%s)", channel->num,
			 te_input_port_to_str(channel->input_port),
			 te_reg_tpi_port_to_str(tpi));
		init_channel_status(channel);
		schedule_delayed_work(&m->work, 0);
	} else {
		cancel_delayed_work(&m->work);
	}

	mutex_unlock(&m->mutex);
}

static int init_channel_monitor(struct sdec_device *dev)
{
	struct sdec_channel_monitor *m;
	int i;

	for (i = 0; i < dev->num_channel; i++) {
		m = &dev->channels[i].monitor;
		m->intr = (TSBUF_PACKET_INTR_CH0 << i);
		m->interval = MONITOR_INTERVAL;
		mutex_init(&m->mutex);

		INIT_DELAYED_WORK(&m->work, channel_monitor_work);
	}

	return 0;
}

/* for SDT channel */
void sdec_io_set_monitor_mask(struct sdec_channel *channel, u32 dest_mask,
			      bool enable)
{
	struct sdec_channel_monitor *m;
	u32 prev_mask;

	log_debug("%s(ch:%d,dest:0x%x,prev_dest:0x%x,en:%d)", __func__,
		  channel->num, dest_mask, channel->monitor.enable_mask,
		  enable);

	m = &channel->monitor;
	mutex_lock(&m->mutex);

	prev_mask = m->enable_mask;
	if (enable) {
		m->enable_mask |= dest_mask;
	} else {
		m->enable_mask &= ~dest_mask;
	}

	if (prev_mask != 0 && m->enable_mask == 0) {
		/* enable_mask becomes zero. disable monitor */
		TE_REG_SetTsBufIntrEnable(m->intr, false);
	} else if (prev_mask == 0 && m->enable_mask != 0) {
		/* A/V pidf is set. enable monitor */
		TE_REG_SetTsBufIntrEnable(m->intr, true);
	}
	mutex_unlock(&m->mutex);
}

/* isr function */
int sdec_io_irq_handler(struct sdec_channel *channel)
{
	struct sdec_channel_monitor *m;

	m = &channel->monitor;

	cancel_delayed_work(&m->work);
	schedule_delayed_work(&m->work, 0);

	return 0;
}

/* monitor end */
static int config_channel_input(struct sdec_channel *channel,
				LX_SDEC_CHANNEL_INPUT_CFG_T *cfg)
{
	enum te_reg_channel_src src;

	src = te_input_port_to_reg_ch_src(cfg->port);
	CHECK_PARAM(src == CH_SRC_INVALID, "Invalid input port:[%d]",
		    cfg->port);

	if (cfg->enable && cfg->port != LX_TE_INPUT_PORT_NONE) {
		if (cfg->reset || channel->input_port != cfg->port) {
			/* disable input port */
			TE_REG_SetChannelSource(channel->num, CH_SRC_DISABLE);

			/* reset pid filter */
			TE_REG_ResetPidFilter(channel->num);

			TE_IPC_ChannelReset(channel->num);

			channel->input_port = cfg->port;
		}

		/* FE Source Setting */
		TE_REG_SetChannelSource(channel->num, src);
		control_channel_monitor(channel, true);
	} else {
		control_channel_monitor(channel, false);
		/* disable input port */
		TE_REG_SetChannelSource(channel->num, CH_SRC_DISABLE);
		channel->input_port = LX_TE_INPUT_PORT_NONE;
	}

	return 0;

}

static int config_in_out(LX_SDEC_IO_CFG_T *cfg)
{
	enum te_reg_tpi_port port;
	enum te_reg_out_clk clk;
	enum te_reg_tpo_mode mode;
	enum te_reg_port_dir dir;
	int ret;
	const struct te_type_conv clk_list[] = {
		{LX_SDEC_OUTPUT_CLK_198MHZ, OUTPUT_CLK_198MHZ},
		{LX_SDEC_OUTPUT_CLK_99MHZ, OUTPUT_CLK_99MHZ},
		{LX_SDEC_OUTPUT_CLK_66MHZ, OUTPUT_CLK_66MHZ},
		{LX_SDEC_OUTPUT_CLK_49MHZ, OUTPUT_CLK_49MHZ},
		{LX_SDEC_OUTPUT_CLK_33MHZ, OUTPUT_CLK_33MHZ},
		{LX_SDEC_OUTPUT_CLK_24MHZ, OUTPUT_CLK_24MHZ},
		{LX_SDEC_OUTPUT_CLK_12MHZ, OUTPUT_CLK_12MHZ},
		{LX_SDEC_OUTPUT_CLK_10MHZ, OUTPUT_CLK_10MHZ},
		{LX_SDEC_OUTPUT_CLK_8MHZ, OUTPUT_CLK_8MHZ},
		{LX_SDEC_OUTPUT_CLK_6MHZ, OUTPUT_CLK_6MHZ},
		{LX_SDEC_OUTPUT_CLK_4MHZ, OUTPUT_CLK_4MHZ},
		{LX_SDEC_OUTPUT_CLK_2MHZ, OUTPUT_CLK_2MHZ},
	};

	port = te_input_src_to_reg_tpi_port(cfg->src);
	CHECK_PARAM(port == TPI_INVALID, "invalid source[%d]", cfg->src);

	dir = (cfg->direction == LX_SDEC_IO_OUTPUT) ?
	    PORT_DIR_OUTPUT : PORT_DIR_INPUT;

	mode = (cfg->mode == LX_TE_IO_MODE_PARALLEL) ?
	    TPO_FORMAT_PARALLEL : TPO_FORMAT_SERIAL;

	clk = convert_to_type1(clk_list, cfg->clk, OUTPUT_CLK_INVALID);
	if (clk == OUTPUT_CLK_INVALID) {
		log_error("invalid clk[%d]", cfg->clk);
		return -EINVAL;
	}

	ret = TE_REG_SetInOutPort(port, dir, mode, clk);

	return ret;
}

static int config_output_port(LX_SDEC_OUTPUT_PORT_CFG_T *cfg)
{
	enum te_reg_channel_src src;
	enum te_reg_tpo_mode mode;

	mode = (cfg->mode == LX_TE_IO_MODE_SERIAL) ?
	    TPO_FORMAT_SERIAL : TPO_FORMAT_PARALLEL;

	src = te_input_port_to_reg_ch_src(cfg->port);
	CHECK_PARAM(src == CH_SRC_INVALID, "invalid port[%d]", cfg->port);

	TE_REG_SetOutputPort(src, mode, cfg->clk_inv, cfg->enable);

	return 0;
}

static int get_channel_input_status(struct sdec_channel *channel,
				    LX_SDEC_CHANNEL_INPUT_STATUS_T *status)
{
	LX_TE_INPUT_PORT_T port;
	enum te_reg_channel_src src;
	enum te_reg_tpi_port tpi0, tpi1;
	u32 val;

	memset(status, 0, sizeof(*status));

	TE_REG_GetChannelSource(channel->num, &src);
	port = te_reg_ch_src_to_input_port(src);

	/* Compare with actual tpi not port */
	tpi0 = te_input_port_to_reg_tpi_port(port);
	tpi1 = te_input_port_to_reg_tpi_port(channel->input_port);
	if (tpi0 != tpi1) {
		log_warning("ch[%d] different input_port: reg[%d] ctrl[%d]\n",
			    channel->num, port, channel->input_port);
		status->port = port;
	} else {
		status->port = channel->input_port; // for same tpi but different port
	}

	status->enable = (port == LX_TE_INPUT_PORT_NONE) ? false : true;

	TE_REG_GetChannelPktCount(channel->num, &val);
	status->pkt_count = val;
	status->time = (u32)te_get_ms_tick();

	return 0;
}

static int set_ci_input_source(struct sdec_device *dev, LX_TE_INPUT_SRC_T src)
{
	int ret;
	enum te_reg_ci_input ci_src;

	ci_src = te_input_src_to_reg_ci_input(src);
	CHECK_PARAM(ci_src == CI_INPUT_SRC_INVALID, "invalid source(%d)", src);

	ret = TE_REG_SetCiInput(ci_src);
	if (ret) {
		log_error("Err in TE_REG_SetCiInput(src=0x%x)", src);
	} else {
		dev->io.ci_src = src;
	}

	return ret;
}

static int get_ci_input_source(LX_TE_INPUT_SRC_T *src)
{
	int ret;
	enum te_reg_ci_input ci_src;

	ret = TE_REG_GetCiInput(&ci_src);
	if (!ret)
		*src = te_reg_ci_input_to_input_src(ci_src);

	return ret;
}

/* isr */
static int input_dump_callback(void *data, void *arg)
{
	int rc;
	u32 new_wptr;
	IPC_MSG_DEBUG_DUMP_DATA_T *msg = data;
	struct sdec_input_dump *dump = arg;
	struct te_hwbuf *buf = dump->buf;

	spin_lock(&dump->spinlock);

	if (dump->state == INPUT_DUMP_RUNNING) {
		new_wptr = msg->buf_wptr;
		if (msg->status == IPC_DATA_STATUS_OK) {
			if (!(dump->flags & SDEC_DUMP_FLAG_IGNORE_WARNING)) {
				/* Buffer allocation warning */
				u32 free_size = te_hwbuf_free_size(buf);
				if (free_size < dump->warning_size) {
					log_warning
					    ("buffer almost full(free=%u,total=%u)",
					     free_size, te_hwbuf_size(buf));
				}
			}
			rc = te_hwbuf_set_wptr(buf, new_wptr);
			CHECK_ERROR(rc < 0,,
				    "Error(%d) in te_hwbuf_set_wptr(0x%x)",
				    rc, new_wptr);
		} else if (msg->status == IPC_DATA_STATUS_OVERFLOW_OVERLAPS_PTR
			   || msg->status ==
			   IPC_DATA_STATUS_OVERFLOW_NOT_ENOUGH_BUF) {
			log_error("dump buffer overflow\n");
			te_hwbuf_set_error(buf, -ENOBUFS);
		} else {
			log_warning("Unknown status type[%d]", msg->status);
		}
	}
	spin_unlock(&dump->spinlock);

	return 0;
}

static int mcu_recovery_io_pre_callback(void *arg)
{
	struct sdec_device *dev = arg;
	struct sdec_channel *channel;
	int i;

	mutex_lock(&io_mutex);

	/* disable input ports before mcu reset.
	 * if the packet is arrived while mcu reset, it will make some errors */
	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];
		if (channel->input_port != LX_TE_INPUT_PORT_NONE) {
			TE_REG_SetChannelSource(channel->num, CH_SRC_DISABLE);
		}
	}

	return 0;
}

static int mcu_recovery_io_post_callback(void *arg)
{
	struct sdec_device *dev = arg;
	struct sdec_channel *channel;
	LX_SDEC_CHANNEL_INPUT_CFG_T cfg;
	int i;

	/* restore input ports after mcu reset */
	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];
		if (channel->input_port != LX_TE_INPUT_PORT_NONE) {
			cfg.port = channel->input_port;
			cfg.reset = true;
			cfg.enable = true;

			config_channel_input(channel, &cfg);
			log_noti("reconnected input(%s) to ch[%d]\n",
				 te_input_port_to_str(cfg.port), channel->num);
		}
	}

	mutex_unlock(&io_mutex);

	return 0;
}

static struct sdec_input_dump *alloc_input_dump(struct sdec_channel *channel)
{
	int i;
	struct sdec_input_dump *dump;
	struct sdec_device *dev = channel->dev;

	mutex_lock(&dev->mutex);

	/* do not allocate input dump if the channel is used */
	for (i = 0; i < MAX_INPUT_DUMP; i++) {
		dump = &dev->io.input_dump[i];
		if (dump->state != INPUT_DUMP_IDLE &&
		    dump->channel == channel) {
			mutex_unlock(&dev->mutex);
			return NULL;
		}
	}

	/* find unused input dump */
	for (i = 0; i < MAX_INPUT_DUMP; i++) {
		dump = &dev->io.input_dump[i];
		if (dump->state == INPUT_DUMP_IDLE) {
			dump->state = INPUT_DUMP_READY;
			dump->channel = channel;
			mutex_unlock(&dev->mutex);
			return dump;
		}
	}

	mutex_unlock(&dev->mutex);

	return NULL;
}

static void free_input_dump(struct sdec_input_dump *dump)
{
	unsigned long flag;

	spin_lock_irqsave(&dump->spinlock, flag);
	dump->state = INPUT_DUMP_IDLE;
	spin_unlock_irqrestore(&dump->spinlock, flag);
}

static void input_dump_read_callback(void *arg, u32 idx)
{
	struct sdec_input_dump *dump = arg;
	phys_addr_t ptr;

	te_hwbuf_idx_to_paddr(dump->buf, idx, &ptr);
	TE_IPC_SetInputDumpRptr(dump->channel->num, (u32)ptr);
}

static struct sdec_input_dump *start_input_dump(struct sdec_channel *channel,
						struct sdec_dump_cfg *param)
{
	int ret;
	IPC_ADAP_DEBUG_DUMP_INFO_T info;
	LX_SDEC_CHANNEL_INPUT_CFG_T input_cfg;
	u32 addr, size;
	struct sdec_input_dump *dump;
	struct te_hwbuf *buf = param->buf;
	u8 ch = channel->num;

	log_noti("%s(ch=%d,port=%s,flags=0x%x,size=0x%x,0x%x,clk=%d,%d,"
		 "bypass=%d,layer=%d)",
		 __func__, ch, te_input_port_to_str(param->port), param->flags,
		 te_hwbuf_size(buf), te_hwbuf_unit_size(buf), param->clk_src,
		 param->clk_res, param->pid_bypass, param->layer);

	dump = alloc_input_dump(channel);
	CHECK_ERROR(!dump, return NULL, "no avaiable input dump");

	input_cfg.enable = true;

	if (param->pid_bypass) {
		struct sdec_channel_info *ch_info = channel->info;

		if (ch_info->is_sub_channel) {
			ret = TE_REG_SetSubpidfBypass(ch_info->sub_ch_num,
						      PIDF_BYPASS_TYPE_192BYTE);
			CHECK_ERROR(ret, goto error,
				    "Error in TE_REG_SetSubpidfBypass(%d)",
				    ch_info->sub_ch_num);
		} else {
			ret = TE_REG_SetPidfBypass(channel->num,
						   PIDF_BYPASS_TYPE_192BYTE);
			CHECK_ERROR(ret, goto error,
				    "Error in TE_REG_SetPidfBypass(%d)",
				    channel->num);
		}

		if (param->port == LX_TE_INPUT_PORT_BYPASS) {
			input_cfg.port = channel->input_port;
		} else {
			input_cfg.port = param->port;
		}
		input_cfg.reset = true;
	} else {
		input_cfg.port = param->port;
		input_cfg.reset = false;
	}

	if (param->layer == TE_DUMP_LAYER_FE_MAIN) {
		info.type = IPC_DUMP_TYPE_FE_MAIN;
	} else if (param->layer == TE_DUMP_LAYER_FE_ISR) {
		info.type = IPC_DUMP_TYPE_FE_ISR;
	} else if (param->layer == TE_DUMP_LAYER_BE) {
		info.type = IPC_DUMP_TYPE_BE;
	}

	dump->org_port = channel->input_port;
	if (input_cfg.port != LX_TE_INPUT_PORT_BYPASS) {
		config_channel_input(channel, &input_cfg);
	}

	/* Register message info, except buf status addr */
	info.use_timestamp = get_ipc_timestamp(param->clk_res);
	if (param->clk_src == LX_SDEC_DUMP_TIMESRC_AUTO) {
		struct sdec_config *cfg = sdec_get_config();
		info.clock_src = get_ipc_time_source(cfg->default_dump_clk);
	} else {
		info.clock_src = get_ipc_time_source(param->clk_src);
	}
	addr = (u32)te_hwbuf_addr(buf);
	size = te_hwbuf_size(buf);

	info.unit_size = te_hwbuf_unit_size(buf);
	info.saddr = addr;
	info.eaddr = addr + size;

	dump->pid_bypass = param->pid_bypass;
	dump->layer = param->layer;
	dump->flags = param->flags;
	dump->port = param->port;
	dump->buf = buf;
	dump->wptr = te_hwbuf_addr(buf);

	te_hwbuf_set_read_callback(buf, input_dump_read_callback, dump);
	TE_IPC_RegisterDumpUpdateCallback(ch, input_dump_callback, dump);

	ret = TE_IPC_StartInputDump(ch, &info);
	CHECK_ERROR(ret, goto error, "Err in TE_IPC_StartInputDump");

	if (size > (0xFFFFFFFF / 100))
		dump->warning_size = (size / 100) * INPUT_DUMP_WARNING_SIZE;
	else
		dump->warning_size = (size * INPUT_DUMP_WARNING_SIZE) / 100;

	dump->state = INPUT_DUMP_RUNNING;

	return dump;

error:
	free_input_dump(dump);
	return NULL;
}

static int stop_input_dump(struct sdec_input_dump *dump)
{
	int ret;
	struct sdec_channel *channel;
	LX_SDEC_CHANNEL_INPUT_CFG_T input_cfg;

	if (!dump || dump->state != INPUT_DUMP_RUNNING) {
		log_error("not running");
		return -EINVAL;
	}
	channel = dump->channel;

	log_noti("%s(%d) bypass:%d, layer:%d", __func__, channel->num,
		 dump->pid_bypass, dump->layer);

	input_cfg.port = dump->org_port;
	input_cfg.enable = true;
	if (dump->pid_bypass) {
		struct sdec_channel_info *ch_info = channel->info;

		if (ch_info->is_sub_channel)
			TE_REG_SetSubpidfBypass(ch_info->sub_ch_num,
						PIDF_BYPASS_DISABLE);
		else
			TE_REG_SetPidfBypass(channel->num, PIDF_BYPASS_DISABLE);

		input_cfg.reset = true;
	} else {
		input_cfg.reset = false;
	}

	config_channel_input(channel, &input_cfg);

	TE_IPC_RegisterDumpUpdateCallback(channel->num, NULL, NULL);

	ret = TE_IPC_StopInputDump(channel->num);
	if (ret != 0 && ret != -ERESTARTSYS) {
		log_error("Error(%d) in TE_IPC_StopInputDump", ret);
	}

	mutex_lock(&dump->mutex);
	free_input_dump(dump);
	mutex_unlock(&dump->mutex);

	return 0;
}

/**
 * wait_for_input_dump - wait for hardware wptr update
 *
 * It waits for hw wptr moving until timeout elapsed.
 * If the wptr is updated, notify the ptr to user (legacy kapi dump call)
 *
 * Return: 0 on success,
 * -EIO for dump error, -ETIME for timeout, -ERESTARTSYS for signal interrupt
 */
static int wait_for_input_dump(struct sdec_input_dump *dump, u32 *ptr,
			       unsigned long timeout)
{
	int ret;
	phys_addr_t wptr;

	mutex_lock(&dump->mutex);
	if (dump->state != INPUT_DUMP_RUNNING) {
		log_error("not running\n");
		mutex_unlock(&dump->mutex);
		return -EIO;
	}

	ret = te_hwbuf_wait_wevent(dump->buf, timeout);
	if (ret < 0) {
		if (ret == -EIO) {
			te_hwbuf_flush(dump->buf);
		}
	} else {
		wptr = te_hwbuf_wptr(dump->buf);
		if (dump->flags & SDEC_DUMP_FLAG_AUTO_PTR_UPDATE) {
			if (dump->wptr != wptr) {
				te_hwbuf_set_rptr(dump->buf, wptr);
				dump->wptr = wptr;
			}
		}
		*ptr = (u32)wptr;
		ret = 0;
	}
	mutex_unlock(&dump->mutex);

	return ret;
}

int sdec_set_input_mux(struct sdec_device *dev, enum te_reg_input_mux type)
{
	int ret = 0;

	mutex_lock(&io_mutex);
	ret = TE_REG_SetInputMux(type);
	if (ret == 0)
		dev->io.mux = type;
	mutex_unlock(&io_mutex);

	return ret;
}

int sdec_config_channel_input(struct sdec_channel *channel,
			      struct lx_sdec_channel_input_cfg *cfg)
{
	int ret;

	mutex_lock(&io_mutex);
	ret = config_channel_input(channel, cfg);
	mutex_unlock(&io_mutex);

	return ret;
}

static int ioc_get_capability(struct sdec_fh *fh, void *arg)
{
	struct sdec_channel *channel = fh->channel;
	LX_SDEC_CAP_T *cap = arg;
	struct sdec_channel_info *info;

	info = channel->info;

	cap->num_pidf = info->num_pidf;
	cap->num_secf = info->num_secf;

	return 0;
}

static int ioc_config_channel_input(struct sdec_fh *fh, void *arg)
{
	int rc;
	struct sdec_channel *channel = fh->channel;
	LX_SDEC_CHANNEL_INPUT_CFG_T *cfg = arg;

	TRACE_ENTER("ch=%d,port=0x%x,reset=%d,enable=%d",
		    channel->num, cfg->port, cfg->reset, cfg->enable);

	rc = config_channel_input(channel, cfg);

	return rc;
}

static int ioc_channel_input_status(struct sdec_fh *fh, void *arg)
{
	int rc;
	struct sdec_channel *channel = fh->channel;
	LX_SDEC_CHANNEL_INPUT_STATUS_T *param = arg;

	rc = get_channel_input_status(channel, param);

	return rc;
}

static int ioc_config_inout(struct sdec_fh *fh, void *arg)
{
	int rc;
	LX_SDEC_IO_CFG_T *cfg = arg;

	rc = config_in_out(cfg);

	return rc;
}

static int ioc_config_output_port(struct sdec_fh *fh, void *arg)
{
	int rc;
	LX_SDEC_OUTPUT_PORT_CFG_T *cfg = arg;

	rc = config_output_port(cfg);

	return rc;
}

static int ioc_set_ci_input(struct sdec_fh *fh, void *arg)
{
	int ret;
	LX_TE_INPUT_SRC_T *input_src = arg;

	TRACE_ENTER("src=%d", *input_src);

	ret = set_ci_input_source(fh->dev, *input_src);

	return ret;
}

static int ioc_get_ci_input(struct sdec_fh *fh, void *arg)
{
	int rc;
	LX_TE_INPUT_SRC_T *src = arg;

	rc = get_ci_input_source(src);

	return rc;
}

static int check_dump_paddr_range(u32 paddr, u32 size)
{
	struct te_mem_ctx *ctx;
	struct te_mem_region_info *info;
	int rc;

	info = te_get_mem_region_info(TE_MEM_PVR);
	if (info->size) { // search pvr memory
		ctx = te_mem_open(TE_MEM_PVR_NAME);
		if (!ctx) // possible?
			goto next;

		rc = te_mem_check_paddr_range(ctx, paddr, size);
		if (!rc) {
			te_mem_close(ctx);
			return 0;
		}
	}

next:
	// search te_shared memory
	ctx = te_mem_open(TE_MEM_SHARED_NAME);
	if (!ctx) // possible?
		return -EFAULT;

	rc = te_mem_check_paddr_range(ctx, paddr, size);

	te_mem_close(ctx);
	return rc;
}

static int ioc_start_dump(struct sdec_fh *fh, void *arg)
{
	LX_SDEC_INPUT_DUMP_T *param = arg;
	struct sdec_dump_fh *df;
	struct sdec_dump_cfg cfg;
	struct sdec_channel *channel;
	u32 size;
	int rc;

	CHECK_ERROR(fh->dump != NULL, return -EBUSY, "already used");

	channel = sdec_get_channel(fh->dev, param->ch);
	CHECK_PARAM(!channel, "invalid channel(%d)", param->ch);

	size = param->buf_end - param->buf_start;
	rc = check_dump_paddr_range(param->buf_start, size);
	if (rc)
		return rc;

	df = kmalloc(sizeof(*df), GFP_KERNEL);
	CHECK_ERROR(!df, return -ENOMEM, "no mem");

	te_hwbuf_init(&df->buf, param->buf_start, size, param->unit_size, 0);

	cfg.pid_bypass = true;
	cfg.layer = TE_DUMP_LAYER_FE_MAIN;
	cfg.buf = &df->buf;
	cfg.port = param->port;
	cfg.clk_src = param->clk_src;
	cfg.clk_res = param->clk_res;
	cfg.flags = SDEC_DUMP_FLAG_AUTO_PTR_UPDATE;

	df->dump = start_input_dump(channel, &cfg);
	if (!df->dump) {
		kfree(df);
		return -EIO;
	}
	fh->dump = df;

	return 0;
}

static int ioc_stop_dump(struct sdec_fh *fh, void *arg)
{
	struct sdec_dump_fh *df = fh->dump;

	if (!df)
		return 0;

	stop_input_dump(df->dump);
	kfree(df);

	fh->dump = NULL;

	return 0;
}

static int ioc_get_dump_buf_info(struct sdec_fh *fh, void *arg)
{
	struct sdec_dump_fh *df = fh->dump;
	LX_SDEC_DUMP_BUF_INFO_T *param = arg;
	u32 wptr;
	int rc;

	if (!df)
		return -EINVAL;

	rc = wait_for_input_dump(df->dump, &wptr, 0);
	if (!rc)
		param->wptr = wptr;
	else
		param->wptr = 0;

	return rc;
}

static int dump_start(struct te_dump_device *dev, struct te_dump_handle *h,
		      struct te_dump_cfg *cfg)
{
	struct sdec_dump_cfg param;
	struct sdec_device *sdev = dev->private;
	struct sdec_channel *channel = sdec_get_channel(sdev, cfg->ch);

	CHECK_PARAM(!channel, "invalid channel[%d]", cfg->ch);

	param.pid_bypass = cfg->sdec.pid_bypass;
	param.layer = cfg->sdec.layer;
	param.buf = cfg->data;
	param.port = cfg->port;
	param.clk_src = cfg->sdec.clk_src;
	param.clk_res = cfg->sdec.clk_res;
	param.flags = 0;

	mutex_lock(&io_mutex);
	h->dev_handle = start_input_dump(channel, &param);
	mutex_unlock(&io_mutex);

	return h->dev_handle ? 0 : -EIO;
}

static void dump_stop(struct te_dump_device *dev, struct te_dump_handle *h)
{
	stop_input_dump(h->dev_handle);
	h->dev_handle = NULL;
}

static struct te_dump_device dump_device = {
	.module = TE_DUMP_MODULE_SDEC,
	.start = dump_start,
	.stop = dump_stop,
};

static int init_input_dump(struct sdec_device *dev)
{
	int i, ret;

	for (i = 0; i < MAX_INPUT_DUMP; i++) {
		struct sdec_input_dump *dump = &dev->io.input_dump[i];
		dump->state = INPUT_DUMP_IDLE;
		mutex_init(&dump->mutex);
		spin_lock_init(&dump->spinlock);
	}

	dump_device.private = dev;
	ret = te_dump_register_device(&dump_device);
	CHECK_ERROR(ret, return ret, "Error in te_dump_register_device");

	return 0;
}

/* debug functions */
#define dprintf(fmt, args...)	seq_printf(m, fmt, ##args)

enum {
	IO_DEBUG_ID_CHANNEL_INPUT = 0,
	IO_DEBUG_ID_MAX,
};

static u32 input_mtime = 500;	/* ms unit */

static int debug_show_input_status(struct sdec_device *dev, struct seq_file *m)
{
	int i;
	struct sdec_channel *channel;
	struct te_device *tdev = get_te_device(dev);
	LX_TE_INPUT_SRC_T src;
	LX_SDEC_CHANNEL_INPUT_STATUS_T *channel_status;
	struct lx_te_tpi_status *tpi_status;
	enum te_reg_tpi_port tpi;

	/* alloc status buffer to calculate the input bitrate */
	channel_status = kcalloc(dev->num_channel,
				 sizeof(LX_SDEC_CHANNEL_INPUT_STATUS_T),
				 GFP_KERNEL);
	if (!channel_status) {
		return -ENOMEM;
	}

	tpi_status = te_debug_get_tpi_status(tdev);
	if (IS_ERR(tpi_status)) {
		kfree(channel_status);
		return PTR_ERR(tpi_status);
	}

	/* get channel input status */
	mutex_lock(&io_mutex);
	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];
		get_channel_input_status(channel, &channel_status[i]);
	}
	mutex_unlock(&io_mutex);

	/* Wait for the packets to calculate the input bitrate */
	msleep(input_mtime);

	dprintf("CHANNEL INPUT STATUS\n");
	dprintf("%s %12s %12s   %8s %8s %17s %12s\n",
		"Num", "Port", "TPI", "Overflow", "SyncErr", "Packet", "Speed");

	mutex_lock(&io_mutex);
	for (i = 0; i < dev->num_channel; i++) {
		char *rate;
		IPC_TS_CH_STATUS_T ts;
		LX_SDEC_CHANNEL_INPUT_STATUS_T s2;
		LX_SDEC_CHANNEL_INPUT_STATUS_T *s1 = &channel_status[i];

		channel = &dev->channels[i];
		get_channel_input_status(channel, &s2);
		TE_IPC_GetChannelStatus(i, &ts);
		tpi = te_input_port_to_reg_tpi_port(s2.port);

		dprintf("[%d] %12s %12s   %08x %08x ", channel->num,
			te_input_port_to_str(s2.port),
			te_reg_tpi_port_to_str(tpi),
			ts.overflow_cnt, ts.syncbyte_errors);

		rate = te_get_readable_bitrate(s2.pkt_count - s1->pkt_count,
					       188, s2.time - s1->time);
		dprintf("%08x/%08x %s\n", s1->pkt_count, s2.pkt_count, rate);
	}
	mutex_unlock(&io_mutex);
	kfree(channel_status);

	dprintf("\n");

	dprintf("INPUT PORT STATUS\n");
	te_debug_show_tpi_status(tdev, m, tpi_status);
	te_debug_free_tpi_status(tpi_status);

	get_ci_input_source(&src);
	dprintf("\nCI INPUT: %s ", te_input_source_to_str(src));

	if (src != LX_TE_INPUT_SRC_TE) {
		tpi = te_input_src_to_reg_tpi_port(src);
		dprintf("tpi: %s\n", te_reg_tpi_port_to_str(tpi));
	} else {
		dprintf("\n");
	}

	return 0;
}

static int debug_set_channel_input(struct sdec_channel *channel, char *name)
{
	int ret;
	struct lx_sdec_channel_input_cfg cfg;

	cfg.port = te_str_to_input_port(name);
	if (cfg.port == LX_TE_INPUT_PORT_INVALID)
		return -EINVAL;

	if (cfg.port == LX_TE_INPUT_PORT_NONE) {
		cfg.enable = false;
	} else {
		cfg.enable = true;
		cfg.reset = false;
	}

	mutex_lock(&io_mutex);
	ret = config_channel_input(channel, &cfg);
	mutex_unlock(&io_mutex);

	return ret;
}

static int debug_channel_show(struct te_debug_item *item, struct seq_file *m)
{
	int ret = 0;
	struct sdec_channel *channel = item->private;

	switch (item->flags) {
	case IO_DEBUG_ID_CHANNEL_INPUT:
		mutex_lock(&io_mutex);
		dprintf("%s\n", te_input_port_to_str(channel->input_port));
		mutex_unlock(&io_mutex);
		break;

	default:
		ret = -EPERM;
		break;
	}

	return ret;
}

static int debug_channel_write(struct te_debug_item *item, char *str)
{
	int ret = 0;
	struct sdec_channel *channel = item->private;

	switch (item->flags) {
	case IO_DEBUG_ID_CHANNEL_INPUT:
		ret = debug_set_channel_input(channel, str);
		break;

	default:
		ret = -EPERM;
		break;
	}

	return ret;
}

static const struct te_debug_simple_ops debug_channel_ops = {
	.show = debug_channel_show,
	.write = debug_channel_write,
};

static const struct te_debug_item_info debug_list[] = {
	DBGITM_NUM("input_mtime", &input_mtime),
};

static const struct te_debug_item_info debug_channel_list[] = {
	DBGITM_SIM("input", &debug_channel_ops, IO_DEBUG_ID_CHANNEL_INPUT),
};

static void init_debug(struct sdec_device *dev)
{
	int i;

	debug_create_item_files(debug_list, dev, dev->debug.dir);

	for (i = 0; i < dev->num_channel; i++) {
		struct sdec_channel *c = &dev->channels[i];
		debug_create_item_files(debug_channel_list, c, c->debug_dir);
	}

	sdec_debug_register_status_show(dev, SDEC_DEBUG_STATUS_INPUT,
					debug_show_input_status);
}

/* sdec sub device functions */

static const struct sdec_ioctl_info ioctls[] = {
	IOC_INFO(SDEC_IOC_GET_CAPABILITY, ioc_get_capability),
	IOC_INFO(SDEC_IOC_CFG_CHANNEL_INPUT, ioc_config_channel_input),
	IOC_INFO(SDEC_IOC_CHANNEL_INPUT_STATUS, ioc_channel_input_status),

	IOC_INFO(SDEC_IOC_SET_CI_INPUT, ioc_set_ci_input, true),
	IOC_INFO(SDEC_IOC_GET_CI_INPUT, ioc_get_ci_input, true),

	IOC_INFO(SDEC_IOC_DUMP_START, ioc_start_dump, true),
	IOC_INFO(SDEC_IOC_DUMP_STOP, ioc_stop_dump, true),
	IOC_INFO(SDEC_IOC_GET_DUMP_BUF_INFO, ioc_get_dump_buf_info, true),

	IOC_INFO(SDEC_IOC_CFG_IN_OUT, ioc_config_inout, true),
	IOC_INFO(SDEC_IOC_CFG_OUTPUT_PORT, ioc_config_output_port, true),
};

static int io_dev_ioctl(void *priv, unsigned int cmd, void *arg)
{
	return sdec_do_ioctl(priv, cmd, arg, io_mutex, ioctls);
}

static int io_dev_init(struct sdec_device *dev)
{
	int ret;

	te_mcu_register_rcallback(get_te_device(dev),
				  TE_MCU_FUNC_TYPE_IO,
				  mcu_recovery_io_pre_callback,
				  mcu_recovery_io_post_callback, dev);

	ret = init_input_dump(dev);
	CHECK_ERROR(ret, return ret, "Error in init_input_dump");

	init_debug(dev);

	ret = init_channel_monitor(dev);
	CHECK_ERROR(ret, return ret, "Error in init_channel_monitor");

	return 0;
}

static void io_dev_release(struct sdec_device *dev)
{

}

static void io_dev_close(struct sdec_fh *fh)
{
	struct sdec_dump_fh *df = fh->dump;

	if (!df)
		return;

	stop_input_dump(df->dump);
	kfree(df);
	fh->dump = NULL;
}

static int io_dev_suspend(struct sdec_device *dev)
{
	struct sdec_channel *channel;
	int i;

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];
		if (channel->input_port != LX_TE_INPUT_PORT_NONE) {
			control_channel_monitor(channel, false);
		}

	}

	return 0;
}

static int resume_ci_input(struct sdec_device *dev)
{
	int ret;

	if (dev->io.ci_src != LX_TE_INPUT_SRC_NONE) {
		ret = set_ci_input_source(dev, dev->io.ci_src);
		if (ret) {
			log_error("set_ci_input_source(src=%d) failed",
				  dev->io.ci_src);
			return ret;
		}
	}

	return 0;
}

static int io_dev_resume(struct sdec_device *dev)
{
	int i, ret;
	LX_SDEC_CHANNEL_INPUT_CFG_T cfg_param;
	struct sdec_channel *channel;

	ret = resume_ci_input(dev);
	CHECK_ERROR(ret, return ret, "Error in resume_ci_input");

	TE_REG_SetInputMux(dev->io.mux);

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];

		/* config_channel_input */
		cfg_param.port = channel->input_port;
		if (cfg_param.port == LX_TE_INPUT_PORT_NONE)
			cfg_param.enable = false;
		else
			cfg_param.enable = true;

		cfg_param.reset = true;	//Try to reset for new settings after resume

		ret = config_channel_input(channel, &cfg_param);
		CHECK_ERROR(ret, return ret, "Error in config_channel_input");
	}

	return 0;
}

static const struct sdec_ioctl ioctl_io = {
	.magic = SDEC_IOC_IO_MAGIC,
	.func = io_dev_ioctl,
};

const struct sdec_sub_driver sdec_io_driver = {
	.name = "sdec_io",
	.init = io_dev_init,
	.release = io_dev_release,
	.suspend = io_dev_suspend,
	.resume = io_dev_resume,

	.close = io_dev_close,
	.ioctl = &ioctl_io,
};
