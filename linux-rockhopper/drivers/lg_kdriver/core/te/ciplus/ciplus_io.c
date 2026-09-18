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
 *  ciplus driver core functions
 *
 *  @author Ilkyu Kim ( ilkyukim@lge.com)
 *  @version	0.1
 *  @date		2015-07-07
 *  @note		Additional information.
 */

#include "ciplus_impl.h"
//#include "ciplus_dvb.h"
#include <lg1k/te/io.h>

#define INPUT_MONITOR_INTERVAL	100

static DEFINE_MUTEX(io_lock);

static int get_mode_from_dest(LX_CIPLUS_DEMUX_DEST_T cfg, bool *mode)
{
	switch (cfg) {
	case LX_CIPLUS_DEMUX_DEST_MCUONLY:
		*mode = true;
		break;
	case LX_CIPLUS_DEMUX_DEST_BOTH:
		*mode = false;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static void input_monitor_timer(void *arg)
{
	u32 pkt_cnt, time;
	u32 data_xfer, hi, lo;
	struct ciplus_input_monitor *monitor = arg;

	pkt_cnt = 0;

	mutex_lock(&io_lock);

	/* Get Current packet count and times */
	if (monitor->use_pktcnt) {
		TE_REG_GetCiplusTPOPacketCnt(&pkt_cnt);
	}

	time = (u32)te_get_ms_tick();

	if (monitor->last_pkt == pkt_cnt) {	//Prevent unnecessary calculation
		data_xfer = 0;
	} else {
		u32 elapsed = time - monitor->last_time;
		u32 count;
		if (!elapsed)
			elapsed = 1;	//Prevent DIV/0

		count = (u32)(pkt_cnt - monitor->last_pkt);
		if (count > 22845) {	/* consider overflow */
			// Represent over 4095 Mbps
			data_xfer = (count * 1000) / elapsed * 188;
		} else {
			data_xfer = count * 188 * 1000 / elapsed;
		}
	}

	/* Update last result */
	monitor->bitrate = data_xfer;

	monitor->last_pkt = pkt_cnt;
	monitor->last_time = time;

	mutex_unlock(&io_lock);

	if (data_xfer) {
		hi = data_xfer / 1024 / 1024;
		lo = (data_xfer % (1024 * 1024)) * 1000 / 1024 / 1024;
	} else {
		hi = 0;
		lo = 0;
	}

	log_bitrate("%2d.%03dMB/s (%d)", hi, lo, data_xfer);
}

static int init_input_monitor(struct ciplus_device *dev)
{
	struct te_device *tdev = get_te_device(dev);
	struct ciplus_input_monitor *m = &dev->input_monitor;

	m->timer = te_add_timer(tdev, INPUT_MONITOR_INTERVAL,
				input_monitor_timer, m);
	CHECK_ERROR(!m->timer, return -EIO, "Error in te_add_timer");

	m->use_pktcnt = dev->cfg->use_pktcnt;

	return 0;
}

static void set_host_player_mode(struct ciplus_channel *channel, bool mode)
{
	u8 ch = channel->num;

	if (mode)
		TE_REG_SetCiplusDemuxDestination(ch, CIP_DEMUX_DEST_MCU);
	else
		TE_REG_SetCiplusDemuxDestination(ch, CIP_DEMUX_DEST_BOTH);

	channel->host_player = mode;
}

static inline void get_host_player_mode(struct ciplus_channel *channel,
					bool *mode)
{
	*mode = channel->host_player;
}

static int init_channel_io(struct ciplus_channel *channel)
{
	u8 ch = channel->num;
	u8 syncbyte = TP_SYNCBYTE + ch;

	TE_REG_SetCiplusInbufSource(ch, CIP_SRC_DEMOD);
	TE_REG_SetCiplusInbufDestination(ch, CIP_INPUT_DEST_HW);
	TE_REG_SetCiplusInbufFullLevel(ch, 0x7);
	TE_REG_SetCiplusInbufWidx(ch, 0x0);	// Set to initial pointer

	TE_REG_SetCiplusInputBypass(ch, false);
	TE_REG_SetCiplusInputSyncbyte(ch, true, syncbyte);
	TE_REG_SetCiplusInputTeiDrop(ch, true);

	/* default: no host player  */
	set_host_player_mode(channel, false);
	TE_REG_SetCiplusDemuxSyncbyte(ch, syncbyte);

	// in TE_IO
//      TE_REG_SetCiplusInput(ch, TPI_DISABLE); // tpi (disable)

	TE_REG_SetCiplusQueueEnable(ch, false);	// False when initialized

	channel->inbuf.src = CIP_SRC_DEMOD;
	channel->inbuf.flevel = 0x7;
	channel->inbuf.layer = TE_DUMP_LAYER_FE_ISR;
	channel->inbuf.pid_bypass = false;
	channel->inbuf.teifilter = true;	//Drop Tei packet
	channel->sync_en = true;
	channel->syncbyte = syncbyte;

	channel->tpi = TPI_DISABLE;
	channel->en = false;

	channel->io_param.port = LX_TE_INPUT_PORT_NONE;
	channel->io_param.ip_play = false;
	channel->io_param.en = false;

	return 0;
}

static int recover_channel_io(struct ciplus_channel *channel)
{
	u8 ch = channel->num;

	TE_REG_SetCiplusInbufSource(ch, channel->inbuf.src);
	TE_REG_SetCiplusInbufDestination(ch, CIP_INPUT_DEST_HW);
	TE_REG_SetCiplusInbufFullLevel(ch, channel->inbuf.flevel);
	TE_REG_SetCiplusInbufWidx(ch, 0x0);	// Set to initial pointer

	TE_REG_SetCiplusInputBypass(ch, channel->inbuf.pid_bypass);
	TE_REG_SetCiplusInputTeiDrop(ch, channel->inbuf.teifilter);
	TE_REG_SetCiplusInputSyncbyte(ch, channel->sync_en, channel->syncbyte);

	set_host_player_mode(channel, channel->host_player);
	TE_REG_SetCiplusDemuxSyncbyte(ch, channel->syncbyte);

	/* Always reset when resumes */
	TE_REG_ResetCiplusInbuf(ch);
	TE_REG_ResetCiplusInput(ch);
	//TE_REG_ResetCiplusDemux(ch); //Reset Demux makes buffer sync error

	// in TE_IO
//      TE_REG_SetCiplusInput(ch, channel->tpi); //recover last tpi
	TE_REG_SetCiplusQueueEnable(ch, channel->en);	// Enable

	return 0;
}

static int suspend_channel_io(struct ciplus_channel *channel)
{
	return 0;
}

static int get_output_bitrate(struct ciplus_device *dev, u32 *bitrate)
{
	u16 val = 0;
	struct ciplus_input_monitor *m = &dev->input_monitor;

	if (m->use_pktcnt) {
		mutex_lock(&io_lock);
		*bitrate = m->bitrate * 8;
		mutex_unlock(&io_lock);
	} else {		//LEGACY Mode (for M16P)
		TE_REG_GetCiplusTPOBitrate(&val);
		*bitrate = (u32)val *1000;	//to ms to sec
	}

	log_debug("val=%d, bitrate= %d", val, *bitrate);

	return 0;
}

static int set_channel_enable(struct ciplus_channel *channel, bool en)
{
	u8 ch = channel->num;

	if (channel->en == en)
		return 0;

	if (en) {
		/* Reset before it starts */
		TE_REG_ResetCiplusInbuf(ch);
		TE_REG_ResetCiplusInput(ch);	// PIDF reset
		//TE_REG_ResetCiplusDemux(ch); //Prevent to use (sync lost)

		TE_REG_SetCiplusQueueEnable(ch, true);	// Enable
	} else {
		TE_REG_SetCiplusQueueEnable(ch, false);	// Enable
	}
	channel->en = en;

	return 0;
}

static int config_channel(struct ciplus_channel *channel, bool ip_play)
{
	u8 ch = channel->num;
	u8 flevel;
	bool breset = false;
	enum te_reg_cip_src src;

	src = (ip_play) ? CIP_SRC_MCU : CIP_SRC_DEMOD;

	/* Select Input Source */
	if (channel->en && channel->inbuf.src != src)
	{
		TE_REG_SetCiplusQueueEnable(ch, false);	//reset: DISABLE
		breset = true;
	}

	TE_REG_SetCiplusInbufSource(ch, src);

	/* Setting Full level (depend on the input source) */
	flevel = (src == CIP_SRC_MCU) ? 0x1 : 0x7;
	TE_REG_SetCiplusInbufFullLevel(ch, flevel);

	if (breset) { //reset: ENABLE
		log_debug("(DEBUG) Input Changes; Reset condition");

		/* Reset before it starts */
		TE_REG_ResetCiplusInbuf(ch);
		TE_REG_ResetCiplusInput(ch);	// PIDF reset
		//TE_REG_ResetCiplusDemux(ch); //Prevent to use (sync lost)

		TE_REG_SetCiplusQueueEnable(ch, true);	// Enable
	}

	/* Record current input settings for kdrv level control */
	channel->inbuf.src = src;
	channel->inbuf.flevel = flevel;

	return 0;
}

static int debug_show_bitrate(struct ciplus_device *dev, struct seq_file *m)
{
	int ret;
	u32 bitrate;
	u32 hi, lo;

	ret = get_output_bitrate(dev, &bitrate);

	if (ret)
		return ret;

	hi = bitrate / 1024 / 1024;
	lo = (bitrate % (1024 * 1024)) * 1000 / 1024 / 1024;

	seq_printf(m, "Current Bitrate: %2d.%03dMbit/s\n\n", hi, lo);

	return 0;
}

static void init_debug(struct ciplus_device *dev)
{
	ciplus_debug_register_status_show(dev, CIPLUS_DEBUG_STATUS_BITRATE,
					  debug_show_bitrate);
}

static int ioc_config_channel(struct ciplus_fh *fh, void *arg)
{
	int ret;
	LX_CIPLUS_CHANNEL_CFG_T *cfg = arg;
	bool ip_play;

	if (cfg->src == LX_TE_INPUT_SRC_IP0 || cfg->src == LX_TE_INPUT_SRC_IP1)
		ip_play= true;
	else
		ip_play = false;

	ret = config_channel(fh->channel, ip_play);

	return ret;
}

static int ioc_enable_channel(struct ciplus_fh *fh, void *arg)
{
	u8 *en = arg;

	return set_channel_enable(fh->channel, (*en) ? true : false);
}

static int ioc_get_bitrate(struct ciplus_fh *fh, void *arg)
{
	u32 *bitrate = arg;

	return get_output_bitrate(fh->dev, bitrate);
}

static int ioc_set_demuxdest(struct ciplus_fh *fh, void *arg)
{
	enum lx_ciplus_demux_dest *dst = arg;
	bool host_player;
	int rc;

	rc = get_mode_from_dest(*dst, &host_player);
	if (rc < 0) {
		log_error("invalid dest:%d", *dst);
		return rc;
	}

	set_host_player_mode(fh->channel, host_player);
	return 0;
}

static int do_ioctl(void *priv, unsigned int cmd, void *arg)
{
	const struct ciplus_ioctl_info ioctl_func[] = {
		IOC_INFO(CIPLUS_IO_CONFIG_CHANNEL, ioc_config_channel),
		IOC_INFO(CIPLUS_IO_ENABLE_CHANNEL, ioc_enable_channel),
		IOC_INFO(CIPLUS_IO_GET_BITRATE, ioc_get_bitrate, true, true),
		IOC_INFO(CIPLUS_IO_SET_DEMUXDEST, ioc_set_demuxdest),
	};

	return ciplus_do_ioctl(priv, cmd, arg, io_lock, ioctl_func);
}

static int suspend(struct ciplus_device *dev)
{
	int i;

	for (i = 0; i < dev->num_channel; i++) {
		suspend_channel_io(&dev->channels[i]);
	}

	return 0;
}

static int resume(struct ciplus_device *dev)
{
	int i;

	for (i = 0; i < dev->num_channel; i++) {
		recover_channel_io(&dev->channels[i]);
	}

	return 0;
}

static int init(struct ciplus_device *dev)
{
	int ret, i;

	dev->debug_mode = false;

	for (i = 0; i < dev->num_channel; i++) {
		struct ciplus_channel *channel = &dev->channels[i];

		ret = init_channel_io(channel);
		CHECK_ERROR(ret, return ret, "Error in init_channel_io");
	}

	ret = init_input_monitor(dev);
	CHECK_ERROR(ret, return ret, "Error in init_input_monitor");

	init_debug(dev);

	return 0;
}

static void release(struct ciplus_device *dev)
{

}

static const struct ciplus_ioctl ioctl_io = {
	.magic = CIPLUS_IOC_IO_MAGIC,
	.func = do_ioctl,
//      .get_user_param = io_ioctl_param,
};

const struct ciplus_sub_driver ciplus_io_driver = {
	.name = "ciplus_io",
	.init = init,
	.release = release,
	.suspend = suspend,
	.resume = resume,

	.ioctl = &ioctl_io,
};

// TE_KAPI function
static int set_camout_input(struct te_device *tdev, bool mode, bool ip)
{
	enum lx_te_input_port src_port;
	struct lx_te_tpi_cfg tpi;
	int rc;

	if (mode)
		src_port = LX_TE_INPUT_PORT_TPI_CI_INPUT;
	else
		src_port = LX_TE_INPUT_PORT_TPI_CI_OUTPUT;

	tpi.stream_type = LX_TE_STREAM_MPEG2TS;
	tpi.mode = LX_TE_IO_MODE_PARALLEL;
	tpi.sync_type = LX_TE_SYNC_SOP;
	tpi.s2p_sync_type = LX_TE_SYNC_SOP;
	tpi.num_of_sync_found = (ip) ? 0 : 3;
	tpi.num_of_sync_drop = (ip) ? 0: 3;

	rc = te_config_tpi(tdev, src_port, &tpi);
	if (rc < 0)
		return rc;

	rc = te_connect_input_port(tdev, LX_TE_INPUT_PORT_CI, src_port);
	if (!rc)
		return rc;

	return 0;
}

static bool check_contain_ip_path(struct ciplus_device *dev)
{
	int i;
	struct ciplus_channel *channel;

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];
		if (channel->io_param.ip_play)
			return true;
	}

	return false;
}

int ciplus_set_input(struct ciplus_channel *channel,
		     enum lx_te_input_port port, bool ip_play, bool en)
{
	int rc;
	struct te_device *tdev = get_te_device(channel->dev);
	enum lx_te_input_port cip_port;
	bool debug = channel->dev->debug_mode;
	bool dev_has_ip = false;

	log_noti("%s(ch[%d] - %s, ip:%d en:%d debug:%d)", __func__,
		  channel->num, te_input_port_to_str(port), ip_play, en, debug);

	mutex_lock(&io_lock);

	if (ip_play || check_contain_ip_path(channel->dev))
		dev_has_ip = true;

	/* camout setting */
	rc = set_camout_input(tdev, debug, dev_has_ip);
	if (rc < 0)
		goto fail;

	/* port connection */
	cip_port = LX_TE_INPUT_PORT_CIPLUS_IN0 + channel->num;
	rc = te_connect_input_port(tdev, cip_port, port);
	if (rc < 0)
		goto fail;

	/* ci+ channel connection */
	rc = config_channel(channel, ip_play);
	if (rc < 0)
		goto fail;

	rc = set_channel_enable(channel, en);
	if (rc < 0)
		goto fail;

	channel->io_param.port = port;
	channel->io_param.ip_play = ip_play;
	channel->io_param.en = en;

fail:
	mutex_unlock(&io_lock);
	return rc;
}

void ciplus_get_input(struct ciplus_channel *channel,
		      enum lx_te_input_port *port, bool *ip_play, bool *en)
{
	mutex_lock(&io_lock);
	*port = channel->io_param.port;
	*ip_play = channel->io_param.ip_play;
	*en = channel->io_param.en;
	mutex_unlock(&io_lock);
}

void ciplus_set_hostplayer(struct ciplus_channel *channel, bool host_player)
{
	log_noti("%s(ch[%d] - host_player:%d)", __func__,
		  channel->num, host_player);

	mutex_lock(&io_lock);
	set_host_player_mode(channel, host_player);
	mutex_unlock(&io_lock);
}

void ciplus_get_hostplayer(struct ciplus_channel *channel, bool *host_player)
{
	mutex_lock(&io_lock);
	get_host_player_mode(channel, host_player);
	mutex_unlock(&io_lock);
}

/* ciplus_get_outputrates - Get CI+ byterates for device
 *  Return: 0 when succeed or
 */
int ciplus_get_outputrates(struct ciplus_channel *channel, s64 *rates)
{
	struct ciplus_input_monitor *m;

	m = &channel->dev->input_monitor;

	if (!m->use_pktcnt) //not possible (~M16P)
		return -EOPNOTSUPP;

	mutex_lock(&io_lock);
	*rates = m->bitrate;
	mutex_unlock(&io_lock);

	return 0;
}

int ciplus_set_debug_mode(struct ciplus_device *dev, bool mode)
{
	struct te_device *tdev = get_te_device(dev);
	int rc;
	bool dev_has_ip = false;

	log_warning("(DEBUG only) LOOPBACK mode:%d", mode);

	mutex_lock(&io_lock);

	if (check_contain_ip_path(dev))
		dev_has_ip = true;

	rc = set_camout_input(tdev, mode, dev_has_ip);
	if (rc < 0)
		goto error;

	dev->debug_mode = mode;

error:
	mutex_unlock(&io_lock);
	return rc;
}

void ciplus_get_debug_mode(struct ciplus_device *dev, bool *mode)
{
	mutex_lock(&io_lock);
	*mode = dev->debug_mode;
	mutex_unlock(&io_lock);
}
