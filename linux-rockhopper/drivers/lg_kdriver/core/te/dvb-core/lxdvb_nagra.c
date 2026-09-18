/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2024 by LG Electronics Inc.
 *
 */

/** @file
 *
 *  TE(Transport Engine) Driver for linux dvb(DEMUX)
 *
 *  @author	Ilkyu Kim
 *  @version	1.0
 *  @date	2024-09-23
 *  @note	Additional information.
 */

#include "lxdvb_demux.h"
#include "lxdvb_nagra.h"
#include "lxdvb_impl.h"
#include "te_nagra_kapi.h"

#undef DEBUG_NAGRA_NONCE

static int set_desc_type(struct lxdvb_dmx_channel *channel,
			 enum dmx_ext_dscrmb_type type,
			 enum lx_sdec_desc_mode desc_mode)
{
	struct lx_sdec_desc_config p = {0};
	const u8 *str;
	int rc;

	switch (type) {
	case DMX_EXT_DSCRMB_TYPE_EMB_AES_ATIS:
		str = "AES_ATIS";

		p.cas_type = LX_SDEC_AES;
		p.blk_mode = LX_SDEC_CBC;
		p.res_mode = LX_SDEC_OFB;
		p.key_size = LX_SDEC_KEY_128BIT;
		p.desc_mode = desc_mode;
		break;
	case DMX_EXT_DSCRMB_TYPE_EMB_CSA_V2:
		str = "CSA_V2";

		p.cas_type = LX_SDEC_CSA;
		p.blk_mode = LX_SDEC_CBC;
		p.res_mode = LX_SDEC_CLEAR;
		p.key_size = LX_SDEC_KEY_64BIT;
		p.desc_mode = desc_mode;
		break;
	default:
		log_error("invalid type(%u)", type);
		return -EINVAL;
	}

	p.cas_mode = LX_SDEC_DESC_CAS_NAGRA;

	log_desc("%s(type:%s)", __func__, str);

	if (desc_mode == LX_SDEC_DESC_MODE_PID)
		lxdvb_demux_desc_disable_all_pid(channel);

	rc = sdec_init_descrambler(channel->dev, &p);
	CHECK_ERROR(rc, return rc, "sdec_init_descrambler failed(%d)", rc);

	return 0;
}

int dmx_nagra_set_desc_type(struct lxdvb_dmx_channel *channel,
			    struct dmx_ext_nagra_algo *param)
{
	int rc;
	enum lx_sdec_desc_mode desc_mode;

	if (channel->desc_type == param->desc_type) // preventing pid clear
		return 0;

	desc_mode = (param->channel_mode == 1) ?
		    LX_SDEC_DESC_MODE_CHANNEL : LX_SDEC_DESC_MODE_PID;

	rc = set_desc_type(channel, param->desc_type, desc_mode);
	if (rc)
		return rc;

	channel->desc_type = param->desc_type;
	channel->desc_mode = desc_mode;
	channel->algo_mode = DEMUX_ALGO_NAGRA;

	return 0;
}

int dmx_nagra_resume_desc_type(struct lxdvb_dmx_channel *channel,
			       enum dmx_ext_dscrmb_type type)
{
	return set_desc_type(channel, type, channel->desc_mode);
}

static int check_input_validation(struct lxdvb_dmx_fh *fh,
				  struct dmx_ext_nagra_key *key)
{
	struct lxdvb_dmx_channel *channel = fh->channel;

	CHECK_ERROR(channel->algo_mode != DEMUX_ALGO_NAGRA, return -EPERM,
		    "invalid algo - %u", channel->algo_mode);
	CHECK_ERROR(!key->data, return -EINVAL, "Null Data");
	CHECK_ERROR(key->key_size == 0 || key->key_size > 16, return -EINVAL,
		    "invalid key size %u", key->key_size);
	CHECK_ERROR(key->iv_size > 16, return -EINVAL, "invalid iv size %u",
						       key->iv_size);

	return 0;
}

static int check_pid_validation(struct lxdvb_dmx_filter *f)
{
	struct lxdvb_dmx_filter *dmxf;
	struct list_head *dvb_list;

	/* PID Filter check */
	CHECK_ERROR(!f, return -EFAULT, "dmx filter not allocated");

	dvb_list = &f->pid_filter->dvb_filters;
	list_for_each_entry (dmxf, dvb_list, pid_filter_entry) {
		if (f != dmxf && dmxf->nagra_desc_enable) {
			log_error("pid 0x%04x already has keys by other fh",
				  f->pid);
			return -EBUSY;
		}
	}

	return 0;
}

static int set_desc_key(struct lxdvb_dmx_channel *channel,
			struct dmx_ext_nagra_key *key, u16 pid)
{
	struct sdec_desc_nagra_key_param p;
	int rc;

	switch (key->key_type) {
	case DMX_EXT_DSCRMB_KEY_TYPE_EVEN:
		p.key_type = LX_SDEC_KEY_TYPE_EVEN;
		break;
	case DMX_EXT_DSCRMB_KEY_TYPE_ODD:
		p.key_type = LX_SDEC_KEY_TYPE_ODD;
		break;
	default:
		log_error("invalid key_type %u", key->key_type);
		return -EINVAL;
	}

	p.desc_mode = channel->desc_mode;
	p.pid = pid;
	p.key_len = key->key_size;
	p.data = key->data;
	p.key_encrypted = (key->key_encrypted) ? true : false;
	if (key->iv_size) {
		p.iv_len = key->iv_size;
		p.iv = key->iv;
		p.iv_encrypted = (key->iv_encrypted) ? true : false;
	} else {
		p.iv_len = 0;
		p.iv = NULL;
		p.iv_encrypted = false;
	}
	p.comm_iv = key->comm_iv;

	rc = sdec_desc_set_nagra_key(channel->dev, &p);
	if (rc) {
		log_error("sdec_desc_set_nagra_key failed %d", rc);
		return -EPERM;
	}

	return 0;
}

int dmx_nagra_set_desc_key(struct lxdvb_dmx_fh *fh,
			   struct dmx_ext_nagra_key *key)
{
	struct lxdvb_dmx_channel *channel = fh->channel;
	int rc;

	rc = check_input_validation(fh, key);
	if (rc)
		return rc;

	if (channel->desc_mode == LX_SDEC_DESC_MODE_PID) {
		struct lxdvb_dmx_filter *f = fh->filter;
		rc = check_pid_validation(f);
		if (rc)
			return rc;

		rc = set_desc_key(channel, key, f->pid);
		if (rc)
			return rc;

		f->nagra_desc_enable = true;

		return 0;
	} else {
		return set_desc_key(channel, key, 0x0);
	}
}

void dmx_nagra_cancel_desc_pid(struct lxdvb_dmx_filter *f)
{
	struct lxdvb_dmx_channel *channel = f->channel;

	sdec_desc_cancel_nagra_pid(channel->dev, f->pid);
	f->nagra_desc_enable = false;
}

static bool get_nagra_desc_enable(struct lxdvb_dmx_filter *f)
{
	return f->nagra_desc_enable;
}

int dmx_nagra_get_desc_key_inserted(struct lxdvb_dmx_fh *fh, s64 *status)
{
	struct lxdvb_dmx_channel *channel = fh->channel;
	struct lxdvb_dmx_filter *f;

	*status = 0;

	if (channel->algo_mode == DEMUX_ALGO_NAGRA &&
	    channel->desc_mode == LX_SDEC_DESC_MODE_CHANNEL) {
		// cannot check pid status in channel mode
		*status = 1;
		return 0;
	}

	f = fh->filter;
	CHECK_ERROR(!f, return -EFAULT, "dmx filter not allocated");

	*status = (get_nagra_desc_enable(f)) ? 1 : 0;
	return 0;
}

//TODO: use this for lxdvb_demux filter status
bool dmx_nagra_get_desc_enable(struct lxdvb_dmx_filter *f)
{
	if (!f)
		return false;

	return get_nagra_desc_enable(f);
}

#ifdef DEBUG_NAGRA_NONCE
static void debug_print_nagra_nonce(u8 *nonce)
{
	u8 buf[64] = {0, };
	u8 pos = 0;
	int i;

	for (i = 0; i < DMX_NAGRA_NONCE_LEN; i++) {
		pos += snprintf(buf + pos, 64 - pos, "%02x ", nonce[i]);
	}

	log_noti("nonce: 0x%s", buf);
}
#endif //DEBUG_NAGRA_NONCE

int dmx_nagra_get_nonce(struct lxdvb_dmx_fh *fh,
			struct dmx_ext_nagra_nonce *param)
{
	struct lxdvb_dmx_channel *channel = fh->channel;
	int rc;

	CHECK_ERROR(channel->algo_mode != DEMUX_ALGO_NAGRA, return -EPERM,
		    "invalid algo - %u", channel->algo_mode);

	rc = sdec_desc_get_nagra_nonce(channel->dev, param->nonce);
	if (rc) {
		log_error("error in sdec_desc_get_nagra_nonce %d", rc);
		return rc;
	}

#ifdef DEBUG_NAGRA_NONCE
	debug_print_nagra_nonce(param->nonce);
#endif
	return 0;
}

int dmx_nagra_set_state(struct lxdvb_dmx_fh *fh,
			struct dmx_ext_nagra_state *param)
{
	struct lxdvb_dmx_channel *channel = fh->channel;
	int rc;

	CHECK_ERROR(channel->algo_mode != DEMUX_ALGO_NAGRA, return -EPERM,
		    "invalid algo - %u", channel->algo_mode);

	rc = sdec_desc_set_nagra_state(channel->dev, param->data,
				       param->comm_iv);
	if (rc) {
		log_error("error in sdec_desc_set_nagra_state %d", rc);
		return rc;
	}

	return 0;
}
