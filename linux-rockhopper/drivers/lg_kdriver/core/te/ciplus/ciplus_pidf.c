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

static DEFINE_MUTEX(pidf_lock);

enum ciplus_pidf_owner {
	PIDF_OWNER_NULL = 0,
	PIDF_OWNER_LEGACY,
	PIDF_OWNER_DVB,
	PIDF_OWNER_MAX,
};

struct ciplus_pidf {
	bool enabled;
	u8 ch;
	u8 idx;
	u16 pid;
	enum ciplus_pidf_owner owner;
};

static struct ciplus_pidf *get_pid_matched_filter(struct ciplus_channel
						  *channel, u16 pid)
{
	int i;
	struct ciplus_pidf *f;

	/* search unused pid filter */
	for (i = 0; i < channel->num_pidf; i++) {
		f = &channel->pidf[i];

		if (f->pid == pid)
			return f;
	}
	return NULL;
}

static struct ciplus_pidf *get_free_filter(struct ciplus_channel *channel)
{
	int i;
	struct ciplus_pidf *f;

	/* search unused pid filter */
	for (i = 0; i < channel->num_pidf; i++) {
		f = &channel->pidf[i];
		if (!f->enabled) {
			f->idx = i;	/* register h/w index */
			f->enabled = true;
			return f;
		}
	}

	return NULL;
}

static struct ciplus_pidf
*get_legacy_filter_by_idx(struct ciplus_channel *channel,
			  u8 idx)
{
	struct ciplus_pidf *f;

	if (idx >= channel->num_pidf) {
		log_error("wrong idx [%d]", idx);
		return ERR_PTR(-EINVAL);
	}

	f = &channel->pidf[idx];
	if (f->owner == PIDF_OWNER_LEGACY) {
		return &channel->pidf[idx];
	} else {
		log_error("[%d]different owner [%d]", idx, f->owner);
		return ERR_PTR(-EBUSY);
	}
}

//in the mutex
static int suspend_pidfilter(struct ciplus_channel *channel)
{
	// Do something (if it is required)
	return 0;
}

//in the mutex
static int recover_pidfilter(struct ciplus_channel *channel)
{
	int i;
	struct ciplus_pidf *f;
	u8 ch = channel->num;

	/* Recover enabled PIDF */
	for (i = 0; i < channel->num_pidf; i++) {
		f = &channel->pidf[i];
		if (f->enabled) {
			log_debug("DEBUG: Recover [%d] = 0x%04x", f->idx,
				  f->pid);
			TE_REG_SetCiplusPIDF(ch, f->idx, f->pid, true);
		}
	}

	TE_REG_SetCiplusInputBypass(ch, channel->inbuf.pid_bypass);

	return 0;
}

static int set_pidfilter(struct ciplus_pidf *f)
{
	return TE_REG_SetCiplusPIDF(f->ch, f->idx, f->pid, true);
}

static struct ciplus_pidf *alloc_filter_by_pid(struct ciplus_channel *channel,
					       u16 pid,
					       enum ciplus_pidf_owner owner)
{
	struct ciplus_pidf *f;

	f = get_pid_matched_filter(channel, pid);
	if (f) {
		log_error("pid 0x%04x is already allocated in idx[%d]",
			  pid, f->idx);
		return ERR_PTR(-EPERM);
	}

	f = get_free_filter(channel);
	if (!f) {
		log_error("no more slot for ciplus pid");
		return ERR_PTR(-EBUSY);
	}
	f->pid = pid;
	f->owner = owner;

	return f;
}
static void free_pidfilter(struct ciplus_pidf *f)
{
	TE_REG_SetCiplusPIDF(f->ch, f->idx, 0x1fff, false);
}

static void release_filter(struct ciplus_channel *channel, struct ciplus_pidf *f)
{
	f->enabled = false;
	f->pid = 0x1fff;
	f->owner = PIDF_OWNER_NULL;
}

static void clear_all_filter(struct ciplus_channel *channel)
{
	struct ciplus_pidf *f;
	int i;

	for (i = 0; i < channel->num_pidf; i++) {
		f = &channel->pidf[i];
		if (f->enabled) {
			free_pidfilter(f);
			release_filter(channel, f);
		}
	}
}

static int enable_bypass(struct ciplus_channel *channel, bool en)
{
	u8 ch = channel->num;

	TE_REG_SetCiplusInputBypass(ch, en);
	channel->inbuf.pid_bypass = en;

	return 0;
}

// TODO: make a debug function here
int ciplus_pidf_show_status(struct ciplus_channel *channel, struct seq_file *m)
{
	struct ciplus_pidf *f;
	int i;

	for (i = 0; i < channel->num_pidf; i++) {
		f = &channel->pidf[i];
		if (f->enabled)
			seq_printf(m, "[0x%04x]", f->pid);
	}

	return 0;
}

static int do_ioctl(void *priv, unsigned int cmd, void *arg)
{
	int ret;
	struct ciplus_fh *fh = priv;
	struct lx_ciplus_pidf_cfg *cfg;
	u8 *en;
	struct ciplus_pidf *f = NULL;

	if (!fh->channel)
		return -ENOTTY;

	mutex_lock(&pidf_lock);

	switch (cmd) {
	case CIPLUS_PIDF_SET:
		cfg = arg;
		f = alloc_filter_by_pid(fh->channel, cfg->pid,
					PIDF_OWNER_LEGACY);
		if (IS_ERR(f)) {
			ret = PTR_ERR(f);
			break;
		}
		ret = set_pidfilter(f);
		if (ret < 0)
			release_filter(fh->channel, f);
		cfg->idx = f->idx;
		break;
	case CIPLUS_PIDF_FREE:
		cfg = arg;
		f = get_legacy_filter_by_idx(fh->channel, cfg->idx);
		if (IS_ERR(f)) {
			ret = PTR_ERR(f);
			break;
		}
		free_pidfilter(f);
		release_filter(fh->channel, f);
		ret = 0;
		break;
	case CIPLUS_PIDF_CLEANALL:
		clear_all_filter(fh->channel);
		ret = 0;
		break;
	case CIPLUS_PIDF_BYPASS:
		en = arg;
		ret = enable_bypass(fh->channel, en ? true : false);
		break;
	default:
		log_error("invalid command[0x%08x]. magic=0x%02X, num=%d",
			  cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));
		ret = -ENOTTY;
		break;
	}

	mutex_unlock(&pidf_lock);
	return ret;
}

static int suspend(struct ciplus_device *dev)
{
	int i;

	mutex_lock(&pidf_lock);

	for (i = 0; i < dev->num_channel; i++) {
		suspend_pidfilter(&dev->channels[i]);
	}

	mutex_unlock(&pidf_lock);

	return 0;
}

static int resume(struct ciplus_device *dev)
{
	int i;

	mutex_lock(&pidf_lock);

	for (i = 0; i < dev->num_channel; i++) {
		recover_pidfilter(&dev->channels[i]);
	}

	mutex_unlock(&pidf_lock);

	return 0;
}

static int init(struct ciplus_device *dev)
{
	int i, j;
	struct ciplus_config *cfg = dev->cfg;
	struct ciplus_channel *channel;
	struct ciplus_pidf *f;

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];

		channel->num_pidf = cfg->num_pidf;
		channel->pidf = kcalloc(cfg->num_pidf, sizeof(*f), GFP_KERNEL);
		CHECK_ERROR(!channel->pidf, return -ENOMEM,
			    "can't alloc memory");

		for (j = 0; j < cfg->num_pidf; j++) {
			f = &channel->pidf[j];
			f->ch = channel->num;
			f->pid = 0x1fff;
			f->enabled = false;
		}
	}

	return 0;
}

static void release(struct ciplus_device *dev)
{
	int i;

	for (i = 0; i < dev->num_channel; i++) {
		struct ciplus_channel *channel = &dev->channels[i];
		kfree(channel->pidf);
	}
}

static const struct ciplus_ioctl ioctl_pidf = {
	.magic = CIPLUS_IOC_PIDF_MAGIC,
	.func = do_ioctl,
//      .get_user_param = io_ioctl_param,
};

const struct ciplus_sub_driver ciplus_pidf_driver = {
	.name = "ciplus_pidf",
	.init = init,
	.release = release,
	.suspend = suspend,
	.resume = resume,

	.ioctl = &ioctl_pidf,
};

/**
 * ciplus_set_pid - Alloc pid filter from the channel and set pid filter hw
 * @pfilter - pointer for hw pidfilter (use for release/clean it self)
 *
 * return: 0 on success, or -EPERM if the same pid is allocated or -EBUSY if
 * there is no pid filter available
 */
int ciplus_set_pid(struct ciplus_channel *channel, u16 pid,
		   struct ciplus_pidf **pfilter)
{
	struct ciplus_pidf *f;
	int ret;

	log_noti("ch[%d] Add pidf[0x%04x]", channel->num, pid);

	mutex_lock(&pidf_lock);
	f = alloc_filter_by_pid(channel, pid, PIDF_OWNER_DVB);
	if (IS_ERR(f)) {
		ret = PTR_ERR(f);
		goto exit;
	}

	ret = set_pidfilter(f);
	if (ret < 0) {
		free_pidfilter(f);
		goto exit;
	}

	*pfilter = f;
exit:
	mutex_unlock(&pidf_lock);
	return ret;
}

/**
 * ciplus_free_pid - Free pid filter from the pid filter hw ptr
 * filter - pointer for hw pidfilter (use for release/clean it self)
 *
 * no returns
 */
void ciplus_free_pid(struct ciplus_channel *channel,
		     struct ciplus_pidf *filter)
{
	log_noti("ch[%d] Free pidf[0x%04x]", channel->num, filter->pid);

	mutex_lock(&pidf_lock);
	free_pidfilter(filter);
	release_filter(channel, filter);
	mutex_unlock(&pidf_lock);
}

void ciplus_pidf_enable_bypass(struct ciplus_channel *channel, bool en)
{
	log_noti("ch[%d] pidf bypass %s", channel->num, en ? "on" : "off");

	mutex_lock(&pidf_lock);
	enable_bypass(channel, en);
	mutex_unlock(&pidf_lock);
}
