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

#include <linux/delay.h>
#include <linux/crc32.h>

#include <lg1k/te/mcu.h>
#include <lg1k/te/ipc.h>

#include "sdec_impl.h"

#define MAX_FILTER_CALLBACK 1024

#define log_ferr(f, fmt, args...)                                          \
	log_error("CH[%d] FIDX[%d] PID[0x%04x] - " fmt, (f)->channel->num, \
		  (f)->idx, (f)->pidf->pid, ##args)

#define add_ferr(f, fmt, args...)                             \
	do {                                                  \
		if ((f)->errors < max_log_cnt)                \
			log_ferr(f, fmt, ##args);             \
		(f)->errors++;                                \
		if ((f)->errors == max_log_cnt)               \
			log_ferr(f, "disable error message"); \
	} while (0)

#define is_pidf_dest_vdec(d) \
	((d) >= LX_SDEC_PFLT_DEST_VDEC0 && (d) <= LX_SDEC_PFLT_DEST_VDEC3)

#define is_pidf_dest_adec(d) \
	((d) >= LX_SDEC_PFLT_DEST_ADEC0 && (d) <= LX_SDEC_PFLT_DEST_ADEC1)

#define is_pidf_dest_av(d) (is_pidf_dest_vdec(d) || is_pidf_dest_adec(d))

#define is_pidf_dest_mask_vdec(m)                                         \
	((m) &                                                            \
	 (LX_SDEC_PFLT_DEST_MASK(VDEC0) | LX_SDEC_PFLT_DEST_MASK(VDEC1) | \
	  LX_SDEC_PFLT_DEST_MASK(VDEC2) | LX_SDEC_PFLT_DEST_MASK(VDEC3)))

#define is_pidf_dest_mask_adec(m) \
	((m) & (LX_SDEC_PFLT_DEST_MASK(ADEC0) | LX_SDEC_PFLT_DEST_MASK(ADEC1)))

#define is_pidf_dest_mask_av(m) \
	((m) &                                                            \
	 (LX_SDEC_PFLT_DEST_MASK(VDEC0) | LX_SDEC_PFLT_DEST_MASK(VDEC1) | \
	  LX_SDEC_PFLT_DEST_MASK(VDEC2) | LX_SDEC_PFLT_DEST_MASK(VDEC3) | \
	  LX_SDEC_PFLT_DEST_MASK(ADEC0) | LX_SDEC_PFLT_DEST_MASK(ADEC1)))

#define is_pidf_dest_mask_dvr(m) \
	((m) & (LX_SDEC_PFLT_DEST_MASK(DVR0) | LX_SDEC_PFLT_DEST_MASK(DVR1)))

#define is_pidf_dest_mask_buffer(m) ((m) & (LX_SDEC_PFLT_DEST_MASK(BUFFER)))

#define is_pidf_dest_mask_stc(m) \
	((m) & (LX_SDEC_PFLT_DEST_MASK(STC0) | LX_SDEC_PFLT_DEST_MASK(STC1)))

#define is_pidf_dest_mask_temi(m) ((m) & (LX_SDEC_PFLT_DEST_MASK(TEMI)))

#define is_pidf_dest_mask_tsheader(m) ((m) & (LX_SDEC_PFLT_DEST_MASK(TSHEADER)))

#define get_channel_of_tsh_filter(f) \
	container_of(f, struct sdec_channel, filter.ts_header)

enum filter_state {
	FILTER_STATE_FREE = 0,
	FILTER_STATE_ALLOCATED,
	FILTER_STATE_GO,
	FILTER_STATE_DONE,
};

struct sdec_pid_filter {
	enum filter_state state;
	enum sdec_filter_owner owner;
	enum lx_sdec_payload_type payload_type;

	u16 pid;
	u16 idx; /* hw index */
	u32 dest_mask;

	struct sdec_channel *channel;
	struct list_head list;
};

struct sdec_stream_filter {
	enum filter_state state;
	enum sdec_filter_owner owner;
	enum lx_sdec_stream_type stream_type;
	u8 req_num; /* ipc requested num */
	u16 errors;
	u16 idx; /* hw index */
	u16 flags;
	void *priv; /* user priv data */
	u32 count;

	struct sdec_channel *channel;
	struct list_head list;
	struct sdec_pid_filter *pidf;
	struct te_hwbuf *hbuf;
	struct lx_sdec_filter_pattern pattern; /* only used in section */

	sdec_stream_filter_callback_t callback;
};

enum filter_callback_type {
	FILTER_CALLBACK_STREAM = 0,
	FILTER_CALLBACK_TS_HEADER,
	FILTER_CALLBACK_TYPE_MAX
};

struct filter_callback {
	struct sdec_channel *channel;
	enum filter_callback_type type;
	union {
		IPC_MSG_FILTER_DATA_T filter_data;
		IPC_MSG_TS_HEADER_DATA_T ts_header;
	};
};

static int max_log_cnt = 5;
module_param_named(sdec_filter_log_cnt, max_log_cnt, int, 0644);

static DEFINE_MUTEX(filter_mutex);

static const struct te_val_str pidf_dest_str_list[] = {
	{ LX_SDEC_PFLT_DEST_VDEC0, "VDEC0" },
	{ LX_SDEC_PFLT_DEST_VDEC1, "VDEC1" },
	{ LX_SDEC_PFLT_DEST_VDEC2, "VDEC2" },
	{ LX_SDEC_PFLT_DEST_VDEC3, "VDEC3" },
	{ LX_SDEC_PFLT_DEST_ADEC0, "ADEC0" },
	{ LX_SDEC_PFLT_DEST_ADEC1, "ADEC1" },
	{ LX_SDEC_PFLT_DEST_DVR0, "DVR0" },
	{ LX_SDEC_PFLT_DEST_DVR1, "DVR1" },
	{ LX_SDEC_PFLT_DEST_STC, "STC" },
	{ LX_SDEC_PFLT_DEST_BUFFER, "BUFFER" },
	{ LX_SDEC_PFLT_DEST_PIE, "PIE" },
	{ LX_SDEC_PFLT_DEST_TEMI, "TEMI" },
	{ LX_SDEC_PFLT_DEST_TSHEADER, "TSHEADER" },
	{ LX_SDEC_PFLT_DEST_NONE, "NONE" }, //FIXME: deprecated
};

const char *sdec_pid_filter_dest_str(enum lx_sdec_pid_filter_dest dest)
{
	return find_match_string(pidf_dest_str_list, dest, "Invalid");
}

static LX_SDEC_PFLT_DEST_T str_to_pid_filter_dest(const char *str)
{
	return find_match_value(pidf_dest_str_list, str,
				LX_SDEC_PFLT_DEST_NONE);
}

const char *sdec_stream_type_str(enum lx_sdec_stream_type type)
{
	const struct te_val_str list[] = {
		{ LX_SDEC_STREAM_TYPE_SECTION, "SECTION" },
		{ LX_SDEC_STREAM_TYPE_PES, "PES" },
		{ LX_SDEC_STREAM_TYPE_RAWTS, "RAWTS" },
		{ LX_SDEC_STREAM_TYPE_NONE, "NONE" },
	};

	return find_match_string(list, type, "Invalid");
}

static struct sdec_pid_filter *get_free_pid_filter(struct sdec_device *dev)
{
	int i;
	struct sdec_pid_filter *f;
	struct sdec_dev_filter *fdev = &dev->filter;

	/* search unused pid filter */
	for (i = 0; i < fdev->num_pidf; i++) {
		f = &fdev->pidf[i];
		if (f->state == FILTER_STATE_FREE) {
			f->idx = i; /* register h/w index */
			return f;
		}
	}

	return NULL;
}

/**
 * Get the idx matched pid filter from filters in channel
 */
static struct sdec_pid_filter *
get_pid_filter_from_idx(struct sdec_channel *channel, u16 idx)
{
	struct sdec_pid_filter *f;

	list_for_each_entry (f, &channel->filter.pid_list, list) {
		if (f->idx == idx)
			return f;
	}
	return NULL;
}

/**
 * Get the pid matched pid filter from device
 */
static struct sdec_pid_filter *get_pid_filter(struct sdec_channel *channel,
					      u16 pid)
{
	struct sdec_pid_filter *f;

	list_for_each_entry (f, &channel->filter.pid_list, list) {
		if (f->pid == pid)
			return f;
	}
	return NULL;
}

/**
 * Allocate not dupulicated and unused pid filter
 */
static int alloc_pid_filter(struct sdec_channel *channel, u16 pid, u8 owner,
			    struct sdec_pid_filter **filter)
{
	struct sdec_pid_filter *f;

	/* check duplicated pid */
	f = get_pid_filter(channel, pid);
	if (f) {
		log_error("ch[%d] - same pid(0x%04x) exist in idx[%d]\n",
			  channel->num, pid, f->idx);
		return -EINVAL;
	}

	/* get unused pid filter */
	f = get_free_pid_filter(channel->dev);
	if (!f) {
		log_error("ch[%d] - no empty pid filter\n", channel->num);
		return -EBUSY;
	}

	f->state = FILTER_STATE_ALLOCATED;
	f->owner = owner;
	f->channel = channel;
	f->pid = pid;

	list_add_tail(&f->list, &channel->filter.pid_list);

	*filter = f;

	return 0;
}

static int free_pid_filter(struct sdec_pid_filter *f)
{
	u32 av_dest_mask = is_pidf_dest_mask_av(f->dest_mask);
	TE_REG_ClearPidFilter(f->idx);

	if (av_dest_mask) {
		sdec_io_set_monitor_mask(f->channel, av_dest_mask, false);
	}

	f->state = FILTER_STATE_FREE;
	list_del(&f->list);

	return 0;
}

/* Check that every entry is set with any if branches */
static int set_pid_filter(struct sdec_pid_filter *f,
			  LX_SDEC_PAYLOAD_TYPE_T type, u32 dest)
{
	u8 idx;
	struct te_reg_pidf_conf pidf_conf;
	u8 ch = f->channel->num;

	log_filter("set_pid_filter(%d,0x%04x,%d,%d,%08x)\n", ch, f->pid, f->idx,
		   type, dest);

	/* set pid & channel */
	pidf_conf.ch = ch;

	/* set pid type & output */
	if (is_pidf_dest_mask_vdec(dest)) {
		struct sdec_config *cfg = sdec_get_config();
		struct te_config *te_cfg = te_get_config();
		u32 av_dest_mask = is_pidf_dest_mask_av(dest);

		if (dest & LX_SDEC_PFLT_DEST_MASK(VDEC0))
			idx = 0;
		else if (dest & LX_SDEC_PFLT_DEST_MASK(VDEC1))
			idx = 1;
		else {
			log_error("invalid vdec dest(0x%x)\n", dest);
			return -EINVAL;
		}

		if (idx >= cfg->num_vdec_out) {
			log_error("vdec idx(%d) out of max(%d)\n", idx,
				  cfg->num_vdec_out);
			return -EINVAL;
		}

		pidf_conf.type = PIDF_TYPE_VIDEO;
		pidf_conf.out_en = true;
		pidf_conf.out_idx = idx;

		/* set stcc source channel */
		if (!te_cfg->no_stcc_bug) {
			TE_REG_SetStccSource((PES_DEST_VIDEO | idx), ch);
		} else {
			te_ipc_set_stcc_source(ch, IPC_CLK_PES_DEST_VD0 + idx);
		}

		sdec_io_set_monitor_mask(f->channel, av_dest_mask, true);

		log_filter("  VID%d", idx);
	} else if (is_pidf_dest_mask_adec(dest)) {
		struct sdec_config *cfg = sdec_get_config();
		struct te_config *te_cfg = te_get_config();
		u32 av_dest_mask = is_pidf_dest_mask_av(dest);

		if (dest & LX_SDEC_PFLT_DEST_MASK(ADEC0))
			idx = 0;
		else if (dest & LX_SDEC_PFLT_DEST_MASK(ADEC1))
			idx = 1;
		else {
			log_error("invalid adec dest(0x%x)\n", dest);
			return -EINVAL;
		}

		if (idx >= cfg->num_adec_out) {
			log_error("adec idx(%d) out of max(%d)\n", idx,
				  cfg->num_adec_out);
			return -EINVAL;
		}

		pidf_conf.type = PIDF_TYPE_AUDIO;
		pidf_conf.out_en = true;
		pidf_conf.out_idx = idx;

		/* set stcc source channel */
		if (!te_cfg->no_stcc_bug) {
			TE_REG_SetStccSource((PES_DEST_AUDIO | idx), ch);
		} else {
			te_ipc_set_stcc_source(ch, IPC_CLK_PES_DEST_AD0 + idx);
		}

		sdec_io_set_monitor_mask(f->channel, av_dest_mask, true);

		log_filter("  AUD%d", idx);
	} else if (is_pidf_dest_mask_buffer(dest)) {
		if (type == LX_SDEC_PAYLOAD_SECTION)
			pidf_conf.type = PIDF_TYPE_SECTION;
		else
			pidf_conf.type = PIDF_TYPE_DATA;

		pidf_conf.out_en = false;
		log_filter(" BUFFER");
	} else {
		if (is_pidf_dest_mask_tsheader(dest)) {
			pidf_conf.type = PIDF_TYPE_TSHEADER;
		} else {
			/* mcu1 process all data if type is section or data
			 * To ignore it, set type as video and disable output
			 */
			pidf_conf.type = PIDF_TYPE_VIDEO;
		}
		pidf_conf.out_idx = 3;
		pidf_conf.out_en = false;
	}

	/* set download */
	if (is_pidf_dest_mask_dvr(dest)) {
		pidf_conf.dn_en = true;
		log_filter(" DOWNLOAD");
	} else {
		pidf_conf.dn_en = false;
	}

	if (is_pidf_dest_mask_temi(dest)) {
		pidf_conf.temi_en = true;
	} else {
		pidf_conf.temi_en = false;
	}

	pidf_conf.pid = (f->pid) & 0x1FFF;
	pidf_conf.en = true;

	f->payload_type = type;
	f->dest_mask = dest;

	TE_REG_SetPidFilter(f->idx, &pidf_conf);

	f->state = FILTER_STATE_GO;

	return 0;
}

int sdec_change_stcc_dest(struct sdec_channel *channel, u32 mask)
{
	struct te_config *te_cfg = te_get_config();
	enum te_reg_pes_dest dest;
	enum pes_dest_type ipc_dest;
	int rc;

	if (mask & LX_SDEC_PFLT_DEST_MASK(VDEC0)) {
		log_noti("VD0 change stcc dest:%d", channel->num);
		dest = PES_DEST_VIDEO0;
		ipc_dest = IPC_CLK_PES_DEST_VD0;
	} else if (mask & LX_SDEC_PFLT_DEST_MASK(VDEC1)) {
		log_noti("VD1 change stcc dest:%d", channel->num);
		dest = PES_DEST_VIDEO1;
		ipc_dest = IPC_CLK_PES_DEST_VD1;
	} else if (mask & LX_SDEC_PFLT_DEST_MASK(ADEC0)) {
		log_noti("AD0 change stcc dest:%d", channel->num);
		dest = PES_DEST_AUDIO0;
		ipc_dest = IPC_CLK_PES_DEST_AD0;
	} else if (mask & LX_SDEC_PFLT_DEST_MASK(ADEC1)) {
		log_noti("AD1 change stcc dest:%d", channel->num);
		dest = PES_DEST_AUDIO1;
		ipc_dest = IPC_CLK_PES_DEST_AD1;
	} else {
		log_error("invalid mask:0x%02x", mask);
		return -EINVAL;
	}

	mutex_lock(&filter_mutex);

	if (!te_cfg->no_stcc_bug)
		rc = TE_REG_SetStccSource(dest, channel->num);
	else
		rc = te_ipc_set_stcc_source(channel->num, ipc_dest);

	mutex_unlock(&filter_mutex);

	return rc;
}


static int get_pid_filter_status(struct sdec_pid_filter *f,
				 LX_SDEC_PFLT_STATUS_T *status)
{
	int i, j, max;
	int sub_filters;
	struct te_reg_pidf_status pidf_conf;
	struct sdec_stream_filter *stream_filter;
	struct sdec_dev_filter *fdev = &f->channel->dev->filter;

	/* get reg value */
	TE_REG_GetPidFilter(f->idx, &pidf_conf);

	/* output */
	status->pid = f->pid;
	status->enabled = pidf_conf.en;
	status->payload = f->payload_type;

	/* get sub filters linked in this filter */
	memset(status->subfilter, 0, sizeof(status->subfilter));
	max = MIN(sizeof(status->subfilter) * 8, fdev->num_streamf);

	/* search linked filter */
	sub_filters = 0;
	for (i = 0; i < (max / 32); i++) {
		for (j = 0; j < 32; j++) {
			stream_filter = &fdev->streamf[i * 32 + j];
			if (stream_filter->state != FILTER_STATE_FREE &&
			    stream_filter->pidf == f) {
				status->subfilter[i] |= (0x1 << j);
				sub_filters++;
			}
		}
	}

	status->dest_mask = 0;
	if (pidf_conf.dn_en) {
		status->dest_mask |= LX_SDEC_PFLT_DEST_MASK(DVR);
	}

	if (pidf_conf.temi_en)
		status->dest_mask |= LX_SDEC_PFLT_DEST_MASK(TEMI);

	switch (pidf_conf.type) {
	case PIDF_TYPE_AUDIO:
		if (pidf_conf.out_en) {
			switch (pidf_conf.out_idx) {
			case 0:
				status->dest_mask |=
					LX_SDEC_PFLT_DEST_MASK(ADEC0);
				break;
			case 1:
				status->dest_mask |=
					LX_SDEC_PFLT_DEST_MASK(ADEC1);
				break;
			default:
				break;
			}
		}
		break;

	case PIDF_TYPE_VIDEO:
		if (pidf_conf.out_en) {
			switch (pidf_conf.out_idx) {
			case 0:
				status->dest_mask |=
					LX_SDEC_PFLT_DEST_MASK(VDEC0);
				break;
			case 1:
				status->dest_mask |=
					LX_SDEC_PFLT_DEST_MASK(VDEC1);
				break;
			case 2:
				status->dest_mask |=
					LX_SDEC_PFLT_DEST_MASK(VDEC2);
				break;
			case 3:
				status->dest_mask |=
					LX_SDEC_PFLT_DEST_MASK(VDEC3);
				break;
			default:
				break;
			}
		}
		break;

	case PIDF_TYPE_SECTION:
		//status->dest_mask |= LX_SDEC_PFLT_DEST_MASK(BUFFER);
		break;

	case PIDF_TYPE_DATA:
		//status->dest_mask |= LX_SDEC_PFLT_DEST_MASK(BUFFER);
		break;

	case PIDF_TYPE_TSHEADER:
		status->dest_mask |= LX_SDEC_PFLT_DEST_MASK(TSHEADER);
		break;

	default:
		break;
	}

	if (sub_filters > 0) {
		status->dest_mask |= LX_SDEC_PFLT_DEST_MASK(BUFFER);
	}

	status->state = 0; // not used
	status->reg_value = pidf_conf.val;

	return 0;
}

/**
 * sdec_alloc_pid_filter - Allocate a new pid filter with pid from the channel
 * @filter: pointer to the place where the new struct sdec_pid_filter will be
 * stored
 *
 * Return: 0 on success, or -EINVAL if same pid exists or -EBUSY if
 * no available pid filter exists
 */
int sdec_alloc_pid_filter(struct sdec_channel *channel, u16 pid,
			  struct sdec_pid_filter **filter)
{
	int ret;
	struct sdec_pid_filter *f;

	mutex_lock(&filter_mutex);
	ret = alloc_pid_filter(channel, pid, FILTER_OWNER_KDRV, &f);
	mutex_unlock(&filter_mutex);
	if (ret) {
		log_error("alloc_pid_filter(0x%x) failed\n", pid);
		return ret;
	}
	*filter = f;

	return 0;
}

/*
 * sdec_set_pid_filter - Set pid filter attributes
 *
 * Return: 0 on success or -EINVAL
 */
int sdec_set_pid_filter(struct sdec_pid_filter *filter,
			enum lx_sdec_payload_type payload_type, u32 dest_mask)
{
	int ret;

	mutex_lock(&filter_mutex);
	ret = set_pid_filter(filter, payload_type, dest_mask);
	mutex_unlock(&filter_mutex);

	return ret;
}

int sdec_free_pid_filter(struct sdec_pid_filter *filter)
{
	int ret;

	mutex_lock(&filter_mutex);
	ret = free_pid_filter(filter);
	mutex_unlock(&filter_mutex);

	return ret;
}

static int send_filter_data(struct sdec_channel *channel, void *data,
			    bool is_filter)
{
	IPC_MSG_FILTER_SEND_DATA_T ipc;

	if (!data)
		return -EFAULT;

	ipc.ch = channel->num;
	ipc.data_type = (is_filter) ?
		   IPC_FILTER_SENDTYPE_PES : IPC_FILTER_SENDTYPE_NOTI;
	memcpy(ipc.data, data, IPC_SEND_DATA_MSG_SIZE);

	return te_ipc_send_filter_data(&ipc);
}

int sdec_filter_noti_data_info(struct sdec_channel *channel, void *msg,
			       bool is_filter)
{
	void *data;
#ifdef USE_FIXEDMEM_STATUS
	data = dev->pmem;
#else
	data = msg;
#endif
	return send_filter_data(channel, data, is_filter);
}

static int set_xcas_senddata(struct sdec_channel *channel,
			     struct sdec_send_noti_param *param)
{
	IPC_MSG_FILTER_SEND_DATA_T ipc;
	size_t len = param->len;

	if (len > IPC_SEND_DATA_XCAS_MSG_SIZE)
		len = IPC_SEND_DATA_XCAS_MSG_SIZE;

	//data type is fixed to pes, there is no return (mcu0 handles)
	ipc.ch = channel->num;
	memcpy(ipc.data, param->data, len);

	return te_ipc_send_filter_xcas_data(&ipc);
}

int sdec_filter_noti_xcas_data(struct sdec_channel *channel,
			       struct sdec_send_noti_param *param)
{
	int ret;

	mutex_lock(&filter_mutex);
	ret = set_xcas_senddata(channel, param);;
	mutex_unlock(&filter_mutex);

	return ret;
}

/**
 * Free pid filter
 *
 * @def SDEC_IOC_PFLT_ALLOC
 * @param	ch_ctrl 		[in	] ch_ctrl handle for sdec channel
 * @param	arg 		[in ] LX_SDEC_PFLT_ALLOC_T
 * @return	if succeeded - 0, else - errno.
 */
static int ioc_pid_filter_alloc(struct sdec_fh *fh, void *arg)
{
	int ret;
	struct sdec_pid_filter *f;
	LX_SDEC_PFLT_ALLOC_T *param = arg;
	struct sdec_channel *channel = fh->channel;

	ret = alloc_pid_filter(channel, param->pid, FILTER_OWNER_USER, &f);
	if (ret) {
		log_error("alloc_pid_filter failed\n");
		return ret;
	}

	log_filter("Allocated PidFilter: CH[%d] IDX[%d] PID[0x%04x]",
		   channel->num, f->idx, param->pid);

	return f->idx;
}

/**
 * Get the index matched pid filter which owner is USER from filters in channel
 */
static struct sdec_pid_filter *get_user_pid_filter(struct sdec_channel *channel,
						   u16 idx)
{
	struct sdec_pid_filter *f;

	f = get_pid_filter_from_idx(channel, idx);
	if (!f || f->owner != FILTER_OWNER_USER)
		return NULL;

	return f;
}

/**
 * Free pid filter
 *
 * @def SDEC_IOC_PFLT_FREE
 * @param	ch_ctrl 	[in	] handle for sdec channel
 * @param	arg 		[in ] LX_SDEC_PFLT_FREE_T
 * @return	if succeeded - 0, else - errno.
 */
static int ioc_pid_filter_free(struct sdec_fh *fh, void *arg)
{
	int rc;
	LX_SDEC_PFLT_FREE_T *param = arg;
	struct sdec_pid_filter *f;

	log_filter("Free PidFilter: CH[%d] IDX[%d]", fh->channel->num,
		   param->flt_id);

	/* search matched filter */
	f = get_user_pid_filter(fh->channel, param->flt_id);
	CHECK_ERROR(!f, return -EINVAL, "no matched filter(%d)", param->flt_id);

	rc = free_pid_filter(f);

	return 0;
}

/**
 * Set pid filter
 *
 * @def SDEC_IOC_PFLT_SET
 * @param	ch_ctrl 	[in	] handle for sdec channel
 * @param	arg 		[in ] LX_SDEC_PFLT_CONFIG_T
 * @return	if succeeded - 0, else - errno.
 */
static int ioc_pid_filter_set(struct sdec_fh *fh, void *arg)
{
	int ret;
	struct sdec_pid_filter *f;
	LX_SDEC_PFLT_CONFIG_T *param = arg;

	f = get_user_pid_filter(fh->channel, param->flt_id);
	CHECK_ERROR(!f, return -EINVAL, "no matched filter(%d)", param->flt_id);

	ret = set_pid_filter(f, param->payload_type, param->dest_mask);

	return ret;
}

/**
 * Get pid filter status
 *
 * @def SDEC_IOC_PFLT_GET_STATUS
 * @param	ch_ctrl 	[in	] handle for sdec channel
 * @param	arg 		[in ] LX_SDEC_PFLT_STATUS_PARAM_T
 * @return	if succeeded - 0, else - errno.
 */
static int ioc_pid_filter_get_status(struct sdec_fh *fh, void *arg)
{
	int ret;
	struct sdec_pid_filter *f;
	LX_SDEC_PFLT_STATUS_PARAM_T *param = arg;

	f = get_user_pid_filter(fh->channel, param->flt_id);
	CHECK_ERROR(!f, return -EINVAL, "no matched filter(%d)", param->flt_id);

	ret = get_pid_filter_status(f, param->status);

	return ret;
}

/* workqueue */
static int tsh_filter_callback_work(struct sdec_channel *channel,
				    IPC_MSG_TS_HEADER_DATA_T *header)
{
	struct sdec_tsh_filter *f = &channel->filter.ts_header;
	int ret;

	if (!f->enabled || f->pid != header->pid) {
		log_warning("maybe previous request(pid=0x%x)\n", header->pid);
		return -EINVAL;
	}

	ret = f->callback(f, SDEC_FILTER_STATUS_OK, header->data, f->priv);

	return ret;
}

/* isr function */
static struct filter_callback *
filter_callback_alloc(struct sdec_dev_filter *fdev)
{
	struct filter_callback *callback;
	u32 free;

	free = te_msgbuf_free_count(&fdev->callback_buf);
	if (free) {
		te_msgbuf_raw_get_wbuf(&fdev->callback_buf, 0,
				       (void **)&callback);
		if (free < fdev->callback_min_free) {
			fdev->callback_min_free = free;
		}
	} else {
		callback = NULL; // buffer overflow .....
	}

	if (!callback) {
		if (fdev->callback_errors <= max_log_cnt) {
			log_error("can't alloc callback\n");
			if (fdev->callback_errors == max_log_cnt) {
				log_error("disable error log\n");
			}
		}
		fdev->callback_errors++;
	}

	return callback;
}

static inline void filter_callback_add(struct sdec_dev_filter *fdev,
				       struct filter_callback *callback)
{
	te_msgbuf_raw_write_skip(&fdev->callback_buf, 1);
	queue_work(system_freezable_wq, &fdev->callback_work);
}

static inline struct filter_callback *
filter_callback_get(struct sdec_dev_filter *fdev)
{
	struct filter_callback *callback;

	if (!te_msgbuf_avail_count(&fdev->callback_buf))
		return NULL;

	te_msgbuf_raw_get_rbuf(&fdev->callback_buf, 0, (void **)&callback);

	return callback;
}

static inline void filter_callback_free(struct sdec_dev_filter *fdev,
					struct filter_callback *callback)
{
	te_msgbuf_raw_read_skip(&fdev->callback_buf, 1);
}

/* isr callback */
static int tsh_filter_callback(void *msg, void *arg)
{
	struct filter_callback *callback;
	struct sdec_channel *channel;
	struct sdec_dev_filter *fdev;
	IPC_MSG_TS_HEADER_DATA_T *header = msg;
	struct sdec_device *dev = arg;

	channel = sdec_get_channel(dev, header->ch);
	CHECK_ERROR(!channel, return -EINVAL, "invalid ch(%d)", header->ch);

	fdev = &dev->filter;
	callback = filter_callback_alloc(fdev);
	if (!callback)
		return -ENOMEM;

	callback->channel = channel;
	callback->type = FILTER_CALLBACK_TS_HEADER;
	callback->ts_header = *header;

	filter_callback_add(fdev, callback);

	return 0;
}

static int request_ts_header(struct sdec_channel *channel, u16 pid,
			     enum sdec_filter_owner owner,
			     sdec_tsh_filter_callback_t callback, void *priv,
			     struct sdec_tsh_filter **filter)
{
	int ret;
	IPC_MSG_TS_HEADER_REQUEST_T msg;
	struct sdec_tsh_filter *f = &channel->filter.ts_header;

	CHECK_PARAM(pid >= NULL_PACKET_PID, "invalid pid(0x%04x)", pid);

	if (f->enabled)
		return -EBUSY;

	msg.ch = channel->num;
	msg.cnt = 1;
	msg.pid = pid;
	msg.flag = IPC_TS_HEADER_FLAG_PUSI;

	ret = TE_IPC_RequestTsHeader(&msg);
	CHECK_ERROR(ret, return ret, "TE_IPC_RequestTsHeader failed(%d)", ret);

	f->enabled = true;
	f->owner = owner;
	f->pid = pid;
	f->callback = callback;
	f->priv = priv;

	*filter = f;

	return 0;
}

static int cancel_ts_header(struct sdec_tsh_filter *f)
{
	int ret;
	IPC_MSG_TS_HEADER_CANCEL_T msg;
	struct sdec_channel *channel = get_channel_of_tsh_filter(f);

	if (!f->enabled)
		return -EINVAL;

	msg.ch = channel->num;
	msg.pid = f->pid;

	ret = TE_IPC_CancelTsHeader(&msg);
	if (ret) {
		log_warning("TE_IPC_CancelTsHeader failed(%d)", ret);
		// WHAT TO DO ??? just ignore ipc error
	}
	f->enabled = false;

	return 0;
}

int sdec_request_tsh_filter(struct sdec_channel *channel,
			    struct sdec_tsh_filter_param *param,
			    struct sdec_tsh_filter **filter)
{
	int ret;
	struct sdec_tsh_filter *f;

	mutex_lock(&filter_mutex);

	ret = request_ts_header(channel, param->pid, FILTER_OWNER_KDRV,
				param->callback, param->priv, &f);
	if (ret)
		log_error("request_ts_header failed(%d)", ret);
	else
		*filter = f;

	mutex_unlock(&filter_mutex);

	return ret;
}

int sdec_cancel_tsh_filter(struct sdec_tsh_filter *filter)
{
	int ret;

	mutex_lock(&filter_mutex);
	ret = cancel_ts_header(filter);
	mutex_unlock(&filter_mutex);

	return ret;
}

static int __ioc_tsh_filter_callback(struct sdec_tsh_filter *f,
				     enum sdec_filter_status status, u32 data,
				     void *priv)
{
	struct lx_sdec_msg msg;
	struct lx_sdec_ts_header_msg *tmsg = &msg.ts_header;
	struct sdec_channel *channel = get_channel_of_tsh_filter(f);
	int ret;

	/* make message */
	msg.type = LX_SDEC_MSG_TYPE_TS_HEADER;
	tmsg->ch = channel->num;
	tmsg->pid = f->pid;
	tmsg->priv = f->priv;
	memcpy(tmsg->data, &data, 4);

	ret = sdec_add_message(channel->dev, &msg);

	return ret;
}

static int ioc_set_ts_header(struct sdec_fh *fh, void *arg)
{
	struct sdec_tsh_filter *f;
	struct sdec_channel *channel = fh->channel;
	struct lx_sdec_pflt_ts_header *param = arg;
	int rc;

	if (param->enable) {
		rc = request_ts_header(channel, param->pid, FILTER_OWNER_USER,
				       __ioc_tsh_filter_callback, NULL, &f);
		CHECK_ERROR(rc, return rc, "request_ts_header failed(%d)", rc);
	} else {
		f = &channel->filter.ts_header;
		if (!f->enabled || f->owner != FILTER_OWNER_USER ||
		    f->pid != param->pid)
			return -EINVAL;

		rc = cancel_ts_header(f);
		CHECK_ERROR(rc, return rc, "cancel_ts_header failed(%d)", rc);
	}

	return 0;
}

//from here for section filter

static struct sdec_stream_filter *
get_free_stream_filter(struct sdec_device *dev)
{
	int i;
	struct sdec_stream_filter *f;
	struct sdec_dev_filter *fdev = &dev->filter;

	/* search unused stream filter */
	for (i = 0; i < fdev->num_streamf; i++) {
		f = &fdev->streamf[i];
		if (f->state == FILTER_STATE_FREE) {
			f->idx = i; /* register h/w index */
			return f;
		}
	}

	return NULL;
}

/**
 * Get the idx matched pid filter from device
 */
static struct sdec_stream_filter *
get_stream_filter_from_idx(struct sdec_channel *channel, u16 idx)
{
	struct sdec_stream_filter *f;

	list_for_each_entry (f, &channel->filter.stream_list, list) {
		if (f->idx == idx)
			return f;
	}
	return NULL;
}

static int alloc_stream_filter(struct sdec_channel *channel,
			       struct sdec_pid_filter *pidf,
			       enum lx_sdec_stream_type type, void *priv,
			       enum sdec_filter_owner owner,
			       struct sdec_stream_filter **filter)
{
	struct sdec_stream_filter *f;

	/* get unused stream filter */
	f = get_free_stream_filter(channel->dev);
	CHECK_ERROR(!f, return -EBUSY, "no empty stream filter slot !!!\n");

	f->state = FILTER_STATE_ALLOCATED;
	f->owner = owner;
	f->channel = channel;

	f->pidf = pidf;
	f->stream_type = type;
	f->priv = priv;
	f->req_num++;

	f->flags = 0x0;
	f->count = 0;
	f->errors = 0;

	list_add_tail(&f->list, &channel->filter.stream_list);

	*filter = f;

	return 0;
}

/* isr callback */
static int stream_filter_callback(void *msg, void *arg)
{
	struct filter_callback *callback;
	struct sdec_channel *channel;
	struct sdec_dev_filter *fdev;
	IPC_MSG_FILTER_DATA_T *data = msg;
	struct sdec_device *dev = arg;

	channel = sdec_get_channel(dev, data->ch);
	CHECK_ERROR(!channel, return -EINVAL, "invalid ch(%d)", data->ch);

	fdev = &dev->filter;
	callback = filter_callback_alloc(fdev);
	if (!callback)
		return -ENOMEM;

	callback->channel = channel;
	callback->type = FILTER_CALLBACK_STREAM;
	callback->filter_data = *data;

	filter_callback_add(fdev, callback);

	return 0;
}

static void stream_filter_read_callback(void *arg, u32 ridx)
{
	int ret;
	u32 rptr;
	struct sdec_stream_filter *f = arg;

	rptr = (u32)te_hwbuf_addr(f->hbuf) + ridx;
	ret = TE_IPC_SetStreamFilterRptr(f->idx, rptr);
	if (ret) {
		log_ferr(f, "TE_IPC_SetStreamFilterRptr(0x%x)", rptr);
	}
}

static int ipc_request_stream_filter(struct sdec_stream_filter *f)
{
	int ret;
	IPC_ADAP_FILTER_REQUEST_T msg;
	u32 addr, size;
	u8 ch = f->channel->num;

#ifdef CONFIG_PHYS_ADDR_T_64BIT
	if (te_hwbuf_addr(f->hbuf) > U32_MAX) {
		log_error("addr(%llx) over 32bit\n", te_hwbuf_addr(f->hbuf));
		return -EINVAL;
	}
	addr = (u32)te_hwbuf_addr(f->hbuf);
#else
	addr = te_hwbuf_addr(f->hbuf);
#endif
	size = te_hwbuf_size(f->hbuf);

	msg.flt_idx = f->idx;
	msg.req_num = f->req_num;
	msg.pid = f->pidf->pid;
	msg.gpb_saddr = addr;
	msg.gpb_eaddr = addr + size;
	msg.crc = 0; /* Not support crc checking */
	msg.one_shot = (f->flags & LX_SDEC_SFLT_FLAG_ONESHOT) ? 1 : 0;

	if (f->stream_type == LX_SDEC_STREAM_TYPE_SECTION) {
		msg.type = IPC_FILTER_REQUEST_SECTION;

		memcpy(msg.value, f->pattern.value, sizeof(msg.value));
		memcpy(msg.mask, f->pattern.mask, sizeof(msg.mask));
		memcpy(msg.noteq, f->pattern.noteq, sizeof(msg.noteq));
	} else if (f->stream_type == LX_SDEC_STREAM_TYPE_PES) {
		msg.type = IPC_FILTER_REQUEST_PES;
	} else if (f->stream_type == LX_SDEC_STREAM_TYPE_RAWTS) {
		msg.type = IPC_FILTER_REQUEST_RAWTS;
	} else {
		log_error("invalid stream type(%d)", f->stream_type);
		return -EINVAL;
	}

	/* request to mcu */
	ret = TE_IPC_RequestStreamFilter(ch, &msg);
	if (ret == -EBUSY) { // Replace already allocated flt_idx (in MCU)
		/* Retry Filter Request (Cancel + Request with same idx) */
		log_warning("Replace existed idx[%d]", f->idx);

		ret = TE_IPC_CancelStreamFilter(ch, f->idx);
		if (ret) {
			log_error("Err(%d) TE_IPC_CancelStreamFilter(%d)\n",
				  ret, f->idx);
		}

		ret = TE_IPC_RequestStreamFilter(ch, &msg);
	}

	if (ret) {
		log_error("Err(%d) TE_IPC_RequestStreamFilter(%d)\n", ret,
			  f->idx);
		return ret;
	}

	return 0;
}

static int request_stream_filter(struct sdec_stream_filter *f, u32 flags,
				 struct te_hwbuf *hbuf,
				 struct lx_sdec_filter_pattern *pattern,
				 sdec_stream_filter_callback_t callback)
{
	int ret;

	log_filter("request_stream_filter(%d,%d,%d,%x)\n", f->channel->num,
		   f->idx, f->stream_type, f->flags);

	/* save requested info */
	f->flags = flags;
	f->hbuf = hbuf;
	if (f->stream_type == LX_SDEC_STREAM_TYPE_SECTION) {
		f->pattern = *pattern;
	}
	f->callback = callback;

	te_hwbuf_set_read_callback(f->hbuf, stream_filter_read_callback, f);

	ret = ipc_request_stream_filter(f);
	CHECK_ERROR(ret, return ret, "Err(%d) ipc_request_stream_filter", ret);

	f->state = FILTER_STATE_GO;

	return 0;
}

static int cancel_stream_filter(struct sdec_stream_filter *f)
{
	int ret;

	if (f->state > FILTER_STATE_ALLOCATED) {
		u8 ch = f->channel->num;

		log_filter("cancel_stream_filter(%d,%d)\n", ch, f->idx);

		ret = TE_IPC_CancelStreamFilter(ch, f->idx);
		if (ret) {
			log_error("Err(%d) TE_IPC_CancelStreamFilter(%d,%d)",
				  ret, ch, f->idx);
		}

		f->state = FILTER_STATE_ALLOCATED;
	}

	return 0;
}

static int restart_stream_filter(struct sdec_stream_filter *f)
{
	int ret;

	if (f->state != FILTER_STATE_GO)
		return 0;

	cancel_stream_filter(f);

	te_hwbuf_reset(f->hbuf);

	ret = ipc_request_stream_filter(f);
	CHECK_ERROR(ret, return ret, "Err(%d) ipc_request_stream_filter", ret);

	f->state = FILTER_STATE_GO;

	return 0;
}

static int free_stream_filter(struct sdec_stream_filter *f)
{
	if (f->state != FILTER_STATE_FREE) {
		cancel_stream_filter(f);
		f->state = FILTER_STATE_FREE;
		list_del(&f->list);
	}

	return 0;
}

static int get_stream_filter_buf_info(struct sdec_stream_filter *f,
				      struct lx_sdec_sflt_buffer_info *info)
{
	struct te_hwbuf_info hinfo;

	te_hwbuf_get_info(f->hbuf, &hinfo);

	info->rptr = (u32)hinfo.addr + hinfo.ridx;
	info->wptr = (u32)hinfo.addr + hinfo.widx;

	return 0;
}

static int get_stream_filter_status(struct sdec_stream_filter *f,
				    struct lx_sdec_sflt_status *status)
{
	/* Get Linked PID Filter */
	status->pidf_id = f->pidf->idx;
	status->flags = f->flags;
	status->buf.addr = (u32)te_hwbuf_addr(f->hbuf);
	status->buf.size = te_hwbuf_size(f->hbuf);
	status->state = 0; // not used
	status->pattern = f->pattern;
	status->priv = f->priv;

	return 0;
}

static int get_stream_filter_wptr(struct sdec_stream_filter *f, u32 *ptr)
{
	int ret;

	ret = TE_IPC_GetStreamFilterWptr(f->idx, ptr);
	if (ret) {
		*ptr = 0;
		return ret;
	}

	return 0;
}

static int stream_filter_recovery(struct sdec_device *dev)
{
	int i, ret;
	u32 count;
	struct sdec_stream_filter *f;
	struct sdec_dev_filter *fdev = &dev->filter;

	/* Recall Sections from the saved lists */
	/* search allocated stream filter and recall them for recover mcu1 */
	count = 0;
	for (i = 0; i < fdev->num_streamf; i++) {
		f = &fdev->streamf[i];
		if (f->state != FILTER_STATE_GO)
			continue;

		te_hwbuf_reset(f->hbuf);

		ret = ipc_request_stream_filter(f);
		if (ret) {
			log_warning("Err ipc_request_stream_filter(%d,%d)\n",
				    f->channel->num, f->idx);
		}
		count++;
	}

	if (count)
		log_noti("%d filter recovered\n", count);

	return 0;
}

static int mcu_recovery_filter_pre_callback(void *arg)
{
	mutex_lock(&filter_mutex);

	return 0;
}

static int mcu_recovery_filter_post_callback(void *arg)
{
	int rc;
	struct sdec_device *dev = arg;

	rc = stream_filter_recovery(dev);

	mutex_unlock(&filter_mutex);

	return rc;
}

/**
 * sdec_request_stream_filter - Request stream filter
 * @filter: pointer to the place where the new struct sdec_stream_filter will be
 * stored
 *
 * Return: 0 on success, or -EINVAL if same pid exists or -EBUSY if
 * no available pid filter exists
 */
int sdec_request_stream_filter(struct sdec_channel *channel,
			       struct sdec_stream_filter_param *param,
			       struct sdec_stream_filter **filter)
{
	int ret;
	struct sdec_stream_filter *f;

	mutex_lock(&filter_mutex);

	ret = alloc_stream_filter(channel, param->pidf, param->stream_type,
				  param->priv, FILTER_OWNER_KDRV, &f);
	if (ret) {
		log_error("alloc_stream_filter failed\n");
		goto err_alloc;
	}

	ret = request_stream_filter(f, param->flags, param->hbuf,
				    param->pattern, param->callback);
	if (ret) {
		log_ferr(f, "request_stream_filter failed(%d)", ret);
		goto err_req;
	}
	mutex_unlock(&filter_mutex);

	*filter = f;

	return 0;

err_req:
	free_stream_filter(f);
err_alloc:
	mutex_unlock(&filter_mutex);

	return ret;
}

int sdec_cancel_stream_filter(struct sdec_stream_filter *filter)
{
	int ret;

	mutex_lock(&filter_mutex);
	ret = free_stream_filter(filter);
	mutex_unlock(&filter_mutex);

	return ret;
}

static struct sdec_stream_filter *
get_user_stream_filter(struct sdec_channel *channel, u16 idx)
{
	struct sdec_stream_filter *f;

	f = get_stream_filter_from_idx(channel, idx);
	if (!f || f->owner != FILTER_OWNER_USER)
		return NULL;

	return f;
}

/**
 * Set read pointer
 *
 * @def SDEC_IOC_SFLT_SET_RPTR
 * @param	ch_ctrl 		[in	] ch_ctrl handle for sdec channel
 * @return	if succeeded - 0, else - errno.
 */
static int ioc_stream_filter_set_rptr(struct sdec_fh *fh, void *arg)
{
	int ret;
	struct sdec_stream_filter *f;
	LX_SDEC_SFLT_SET_RPTR_T *param = arg;

	f = get_user_stream_filter(fh->channel, param->flt_id);
	if (!f) {
		log_error("no matched stream filter(%d)", param->flt_id);
		return -EINVAL;
	}

	ret = te_hwbuf_set_rptr(f->hbuf, param->rptr);
	if (ret < 0) {
		log_ferr(f, "invalid rptr(0x%x)", param->rptr);
		return ret;
	}

	return 0;
}

static int __ioc_stream_filter_callback(struct sdec_stream_filter *f,
					enum sdec_filter_status status,
					u32 sidx, u32 eidx, void *priv)
{
	int ret;

	if (status == SDEC_FILTER_STATUS_OK) {
		struct lx_sdec_msg msg;
		struct lx_sdec_filter_msg *fmsg = &msg.filter;
		u32 addr = (u32)te_hwbuf_addr(f->hbuf);

		msg.type = LX_SDEC_MSG_TYPE_FILTER;
		fmsg->ch = f->channel->num;
		fmsg->index = f->idx;
		fmsg->rptr = addr + sidx;
		fmsg->wptr = addr + eidx;
		fmsg->status = LX_SDEC_SFLT_STATE_DATAREADY;
		fmsg->msec = te_get_ms_tick();
		fmsg->priv = priv;

		ret = sdec_add_message(f->channel->dev, &msg);
		if (ret) {
			te_hwbuf_set_ridx(f->hbuf, eidx);
		}
	} else if (status == SDEC_FILTER_STATUS_OVERFLOW) {
		/* Mark previous noti as overflow */
		sdec_add_filter_msg_status(f->channel->dev, f->idx,
					   LX_SDEC_SFLT_STATE_OVERFLOW);
		te_hwbuf_set_ridx(f->hbuf, eidx);
	}

	return 0;
}

static int check_filter_paddr_range(struct sdec_fh *fh, u32 addr, u32 size)
{
	struct te_mem_ctx *mem, *temp_mem = NULL;
	int rc;

	if (fh->mem) {
		mem = fh->mem;
	} else {
		temp_mem = te_mem_open(TE_MEM_SDEC_NAME);
		if (!temp_mem)
			return -EIO;
		mem = temp_mem;
	}

	rc = te_mem_check_paddr_range(mem, addr, size);

	if (temp_mem)
		te_mem_close(temp_mem);

	return rc;
}

/**
 * Request section filter
 *
 * @def SDEC_IOC_SFLT_REQUEST
 * @param	ch_ctrl 	[in	] handle for sdec channel
 * @return filter index	if succeeded, else - errno.
 */
static int ioc_stream_filter_request(struct sdec_fh *fh, void *arg)
{
	int ret;
	LX_SDEC_SFLT_CONFIG_T *param = arg;
	struct sdec_stream_filter *f;
	struct sdec_pid_filter *pidf;
	struct te_hwbuf *hbuf;

	ret = check_filter_paddr_range(fh, param->buf.addr, param->buf.size);
	if (ret)
		return ret;

	pidf = get_pid_filter_from_idx(fh->channel, param->pidf_id);
	if (!pidf) {
		log_error("not allocated pid filter(%d)", param->pidf_id);
		return -EINVAL;
	}

	ret = alloc_stream_filter(fh->channel, pidf, param->stream_type,
				  param->priv, FILTER_OWNER_USER, &f);
	if (ret) {
		log_error("can't alloc stream filter");
		return ret;
	}

	hbuf = kmalloc(sizeof(*hbuf), GFP_KERNEL);
	if (!hbuf) {
		ret = -ENOMEM;
		goto err_malloc;
	}

	te_hwbuf_init(hbuf, param->buf.addr, param->buf.size, 0, 0);

	ret = request_stream_filter(f, param->flags, hbuf, &param->pattern,
				    __ioc_stream_filter_callback);
	if (ret) {
		log_error("request_stream_filter failed(%d)\n", ret);
		goto err_req;
	}

	return f->idx;

err_req:
	te_hwbuf_release(hbuf);
	kfree(hbuf);
err_malloc:
	free_stream_filter(f);

	return ret;
}

/**
 * Cancel section filter
 *
 * @def SDEC_IOC_SFLT_CANCEL
 * @param	ch_ctrl 	[in	] handle for sdec channel
 * @return	if succeeded - 0, else - errno.
 */
static int ioc_stream_filter_cancel(struct sdec_fh *fh, void *arg)
{
	int ret;
	LX_SDEC_SFLT_ID_T *param = arg;
	struct sdec_stream_filter *f;
	struct te_hwbuf *hbuf;

	f = get_stream_filter_from_idx(fh->channel, param->id);
	if (!f || f->owner != FILTER_OWNER_USER) {
		log_error("no matched stream filter(%d)", param->id);
		return -EINVAL;
	}

	ret = cancel_stream_filter(f);
	if (ret) {
		log_ferr(f, "cancel_stream_filter failed(%d)", ret);
		return ret;
	}

	/* delete msg in notify queue */
	sdec_add_filter_msg_status(f->channel->dev, f->idx,
				   LX_SDEC_SFLT_STATE_DELETED);

	hbuf = f->hbuf; /* backup hwbuffer pointer before releasing stream filter */

	free_stream_filter(f);

	te_hwbuf_release(hbuf);
	kfree(hbuf);

	return 0;
}

/**
 * Get buffer status
 *
 * @def SDEC_IOC_SFLT_GET_STATUS
 * @param	ch_ctrl 	[in	] handle for sdec channel
 * @return	if succeeded - 0, else - errno.
 */
static int ioc_stream_filter_get_status(struct sdec_fh *fh, void *arg)
{
	int ret;
	struct sdec_stream_filter *f;
	LX_SDEC_SFLT_STATUS_PARAM_T *param = arg;

	f = get_user_stream_filter(fh->channel, param->flt_id);
	CHECK_ERROR(!f, return -EINVAL, "no matched filter(%d)", param->flt_id);

	ret = get_stream_filter_status(f, param->status);

	return ret;
}

/**
 * Get buffer information
 *
 * @def SDEC_IOC_SFLT_GET_BUFFER_INFO
 * @param	ch_ctrl 		[in	] handle for sdec channel
 * @return	if succeeded - 0, else - errno.
 */
static int ioc_stream_filter_get_buf_info(struct sdec_fh *fh, void *arg)
{
	int ret;
	struct sdec_stream_filter *f;
	LX_SDEC_SFLT_BUFFER_INFO_PARAM_T *param = arg;

	f = get_user_stream_filter(fh->channel, param->flt_id);
	CHECK_ERROR(!f, return -EINVAL, "no matched filter(%d)", param->flt_id);

	ret = get_stream_filter_buf_info(f, param->info);

	return ret;
}

static int reset_callback(struct sdec_dev_filter *fdev)
{
	int count;

	count = te_msgbuf_avail_count(&fdev->callback_buf);
	te_msgbuf_reset(&fdev->callback_buf);
	fdev->callback_errors = 0;
	if (count)
		log_noti("removed %d filter callbacks\n", count);

	return count;
}

static void stream_filter_error_message(struct sdec_stream_filter *f,
					IPC_MSG_FILTER_DATA_T *data)
{
	struct te_hwbuf_info hinfo;

	te_hwbuf_get_info(f->hbuf, &hinfo);
	if (data->status == IPC_DATA_STATUS_OVERFLOW_OVERLAPS_PTR) {
		add_ferr(f, "Overflow(%08x--%08x) last(0x%08x--0x%08x)",
			 data->data_saddr, data->data_eaddr,
			 (u32)hinfo.addr + hinfo.ridx,
			 (u32)hinfo.addr + hinfo.widx);
	} else if (data->status == IPC_DATA_STATUS_OVERFLOW_NOT_ENOUGH_BUF) {
		add_ferr(f, "Not Enough Buffer (0x%08x++0x%08x)",
			 (u32)hinfo.addr, hinfo.size);
	}
}

static int stream_filter_callback_work(struct sdec_channel *channel,
				       IPC_MSG_FILTER_DATA_T *data)
{
	struct sdec_stream_filter *f;
	enum sdec_filter_status status;
	u32 sidx, eidx, wptr;
	int ret;

	f = get_stream_filter_from_idx(channel, data->flt_idx);
	if (!f) {
		log_warning("unused filter index(%d)", data->flt_idx);
		return -EINVAL;
	}

	if (f->state != FILTER_STATE_GO)
		return 0;

	if (f->req_num != data->req_num) {
		add_ferr(f, "not matched request num(%d):callback(%d)",
			 f->req_num, data->req_num);
		return -EINVAL;
	}

	ret = te_hwbuf_paddr_to_idx(f->hbuf, data->data_saddr, &sidx);
	if (ret) {
		add_ferr(f, "invalid saddr(%08x) buffer(%08x--%08x)",
			 data->data_saddr, (u32)te_hwbuf_addr(f->hbuf),
			 (u32)te_hwbuf_eaddr(f->hbuf));
		return ret;
	}

	ret = te_hwbuf_paddr_to_idx(f->hbuf, data->data_eaddr, &eidx);
	if (ret) {
		add_ferr(f, "invalid eaddr(%08x) buffer(%08x--%08x)",
			 data->data_eaddr, (u32)te_hwbuf_addr(f->hbuf),
			 (u32)te_hwbuf_eaddr(f->hbuf));
		return ret;
	}

	switch (data->status) {
	case IPC_DATA_STATUS_OK:
		if (sidx == eidx) {
			log_ferr(f, "data size is 0");
			return -EINVAL;
		}
		f->count++;
		status = SDEC_FILTER_STATUS_OK;
		break;
	case IPC_DATA_STATUS_OVERFLOW_OVERLAPS_PTR:
		stream_filter_error_message(f, data);
		status = SDEC_FILTER_STATUS_OVERFLOW;
		break;
	case IPC_DATA_STATUS_OVERFLOW_NOT_ENOUGH_BUF:
		stream_filter_error_message(f, data);
		status = SDEC_FILTER_STATUS_NO_BUF;
		break;
	default:
		log_ferr(f, "invalid status(%d)", data->status);
		return -EINVAL;
	}

	/* update current wptr as ipc status value */
	get_stream_filter_wptr(f, &wptr);
	ret = te_hwbuf_set_wptr(f->hbuf, wptr);
	if (ret < 0) {
		add_ferr(f, "Err(%d) in te_hwbuf_set_wptr(0x%x)", ret, wptr);
		// ignore it
	}

	ret = f->callback(f, status, sidx, eidx, f->priv);
	if (ret == -EAGAIN) {
		if (f->flags & LX_SDEC_SFLT_FLAG_ONESHOT) {
			log_ferr(f, "restart filter again\n");
			restart_stream_filter(f);
		}
	} else if (ret == -ECANCELED) {
		cancel_stream_filter(f);
	}

	return ret;
}

static void process_filter_callback(struct filter_callback *cb)
{
	switch (cb->type) {
	case FILTER_CALLBACK_STREAM:
		stream_filter_callback_work(cb->channel, &cb->filter_data);
		break;
	case FILTER_CALLBACK_TS_HEADER:
		tsh_filter_callback_work(cb->channel, &cb->ts_header);
		break;
	default:
		log_warning("invalid cb type(%d)\n", cb->type);
		break;
	}
}

static void filter_callback_work(struct work_struct *work)
{
	struct filter_callback *callback;
	struct sdec_dev_filter *fdev;

	fdev = container_of(work, struct sdec_dev_filter, callback_work);
	while (1) {
		callback = filter_callback_get(fdev);
		if (!callback)
			break;

		mutex_lock(&filter_mutex);
		process_filter_callback(callback);
		mutex_unlock(&filter_mutex);

		filter_callback_free(fdev, callback);
	}
}

/* debug functions */
#define dprintf(fmt, args...) seq_printf(m, fmt, ##args)
#define dprintf1(fmt, args...) dprintf("      " fmt, ##args)

enum filter_debug_id {
	FILTER_DEBUG_ID_PID = 0,
	FILTER_DEBUG_ID_MAX,
};

static void show_pid_filter_status(struct sdec_pid_filter *f,
				   struct seq_file *m)
{
	int i, j;
	struct lx_sdec_pflt_status s;
	u32 mask;

#define pes_dest_printf(__mask, __str)                          \
	do {                                                    \
		if (mask & LX_SDEC_PFLT_DEST_MASK(__mask))      \
			dprintf(TE_COLOR_PURPLE __str TE_COLOR_NONE); \
	} while (0)

#define dest_printf(__mask, __str)                         \
	do {                                               \
		if (mask & LX_SDEC_PFLT_DEST_MASK(__mask)) \
			dprintf(__str);                    \
	} while (0)

	get_pid_filter_status(f, &s);
	mask = s.dest_mask;

	dprintf("[%03d] CH[%d]", f->idx, f->channel->num);

	dprintf(TE_COLOR_CYAN " PID" TE_COLOR_NONE "[0x%04x]", s.pid);
	dprintf(TE_COLOR_GREEN " REG" TE_COLOR_NONE "[%08x]", s.reg_value);

	dprintf("%s", s.enabled ? "[EN]" : "[--]");

	/* Section Filter Enabled */
	if (s.payload == LX_SDEC_PAYLOAD_SECTION) {
		dprintf(TE_COLOR_YELLOW "[SEC]" TE_COLOR_NONE);
	} else if (s.payload == LX_SDEC_PAYLOAD_PES) {
		dprintf("[PES]");

		pes_dest_printf(ADEC0, "[AD0]");
		pes_dest_printf(ADEC1, "[AD1]");
		pes_dest_printf(ADEC2, "[AD2]");
		pes_dest_printf(ADEC3, "[AD3]");
		pes_dest_printf(VDEC0, "[VD0]");
		pes_dest_printf(VDEC1, "[VD1]");
		pes_dest_printf(VDEC2, "[VD2]");
		pes_dest_printf(VDEC3, "[VD3]");
	}

	dest_printf(DVR0, "[DN0]");
	dest_printf(DVR1, "[DN1]");
	dest_printf(DVR2, "[DN2]");
	dest_printf(DVR3, "[DN3]");
	dest_printf(TEMI, "[TEMI]");
	dest_printf(TSHEADER, "[TSHEADER]");

	if (mask & LX_SDEC_PFLT_DEST_MASK(BUFFER)) {
		dprintf("[GPB]");
		for (i = 0; i < sizeof(s.subfilter) / 4; i++) {
			for (j = 0; j < 32; j++) {
				if (s.subfilter[i] & (0x1 << j)) {
					dprintf("[%02d]", i * 32 + j);
				}
			}
		}
	}
	dprintf("\n");
}

static void show_stream_filter_status(struct sdec_stream_filter *f,
				      struct seq_file *m)
{
	struct te_hwbuf_info hinfo;

	te_hwbuf_get_info(f->hbuf, &hinfo);

	dprintf("[%03d] %s\n", f->idx, sdec_stream_type_str(f->stream_type));

	dprintf1("CHANNEL\t\t%d\n", f->channel->num);
	dprintf1("PIDF\t\tIDX[%d] PID[0x%04X]\n", f->pidf->idx, f->pidf->pid);
	dprintf1("BUFFER\t\t[0x%08x--0x%x] %dKB\n", (u32)hinfo.addr,
		 (u32)(hinfo.addr + hinfo.size), hinfo.size >> 10);
	dprintf1("DATA\t\tW[0x%x] R[0x%x] SIZE[%d] COUNT[%u]\n", hinfo.widx,
		 hinfo.ridx,
		 (hinfo.widx + hinfo.size - hinfo.ridx) % hinfo.size, f->count);
	dprintf1("FLAGS\t\t%s,%s\n",
		 (f->flags & LX_SDEC_SFLT_FLAG_ONESHOT) ? "ONE_SHOT" :
							  "CONTINUOUS",
		 (f->flags & LX_SDEC_SFLT_FLAG_NO_CRC_CHECK) ? "NO_CRC" :
							       "CRC");

	if (f->stream_type == LX_SDEC_STREAM_TYPE_SECTION) {
		struct lx_sdec_filter_pattern *p = &f->pattern;

		dprintf1("VALUE\t\t%08X %08X\n", TE_GET32(&p->value[0]),
			 TE_GET32(&p->value[4]));
		dprintf1("MASK\t\t%08X %08X\n", TE_GET32(&p->mask[0]),
			 TE_GET32(&p->mask[4]));
		dprintf1("NOTEQUAL\t\t%08X %08X\n", TE_GET32(&p->noteq[0]),
			 TE_GET32(&p->noteq[4]));
	}
	dprintf("\n");
}

static int debug_show_pid_filter(struct sdec_device *dev, struct seq_file *m)
{
	int i;
	struct sdec_pid_filter *f;
	struct sdec_dev_filter *fdev = &dev->filter;

	dprintf("PID FILTER STATUS\n");

	mutex_lock(&filter_mutex);
	for (i = 0; i < fdev->num_pidf; i++) {
		f = &fdev->pidf[i];
		if (f->state == FILTER_STATE_GO) {
			show_pid_filter_status(f, m);
		}
	}
	mutex_unlock(&filter_mutex);

	return 0;
}

static void debug_show_channel_pid_filter(struct sdec_channel *channel,
					  struct seq_file *m)
{
	struct sdec_pid_filter *f;

	mutex_lock(&filter_mutex);
	list_for_each_entry (f, &channel->filter.pid_list, list) {
		show_pid_filter_status(f, m);
	}
	mutex_unlock(&filter_mutex);
}

static int debug_show_stream_filter(struct sdec_device *dev, struct seq_file *m)
{
	int i;
	struct sdec_stream_filter *f;
	struct sdec_dev_filter *fdev = &dev->filter;

	dprintf("STREAM FILTER STATUS\n");

	mutex_lock(&filter_mutex);
	for (i = 0; i < fdev->num_streamf; i++) {
		f = &fdev->streamf[i];
		if (f->state != FILTER_STATE_FREE) {
			show_stream_filter_status(f, m);
		}
	}
	mutex_unlock(&filter_mutex);

	dprintf("FILTER CALLBACK STATUS\n");
	dprintf1("size: %u\n", MAX_FILTER_CALLBACK);
	dprintf1("min_free: %u\n", fdev->callback_min_free);
	dprintf1("errors: %u\n", fdev->callback_errors);

	return 0;
}

static int debug_show_mcu_filter(struct sdec_device *dev, struct seq_file *m)
{
	int i, ret;
	IPC_FILTER_STATUS_T status;
	struct sdec_dev_filter *fdev = &dev->filter;

	dprintf("MCU STREAM FILTER STATUS\n");

	mutex_lock(&filter_mutex);
	for (i = 0; i < fdev->num_streamf; i++) {
		ret = TE_IPC_GetStreamFilterStatus(i, &status);
		if (ret || status.state == IPC_FILTER_STATE_IDLE)
			continue;

		dprintf("[%03d] REQ[%02x] WPTR[0x%08x] RPTR[0x%08x] "
			"OVERFLOW[%d] STATE[%d]\n",
			i, status.req_num, status.gpb_wptr, status.gpb_rptr,
			status.overflow, status.state);
	}
	mutex_unlock(&filter_mutex);

	return 0;
}

static int debug_set_pid(struct sdec_channel *channel, u16 pid,
			 enum lx_sdec_pid_filter_dest dest)
{
	int ret;
	u32 mask;
	struct sdec_pid_filter *f;

	f = get_pid_filter(channel, pid);
	if (!f) {
		ret = alloc_pid_filter(channel, pid, FILTER_OWNER_USER, &f);
		if (ret)
			return ret;

		mask = 0x1 << dest;
	} else {
		if (f->payload_type != LX_SDEC_PAYLOAD_PES)
			return -EBUSY;

		mask = f->dest_mask | (0x1 << dest);
	}

	ret = set_pid_filter(f, LX_SDEC_PAYLOAD_PES, mask);

	return ret;
}

static int debug_cancel_pid(struct sdec_channel *channel, u16 pid,
			    enum lx_sdec_pid_filter_dest dest)
{
	int ret;
	u32 mask;
	struct sdec_pid_filter *f;

	f = get_pid_filter(channel, pid);
	if (!f) {
		printk(KERN_ERR "no pid(0x%x)\n", pid);
		return -EINVAL;
	}

	mask = f->dest_mask & ~(0x1 << dest);
	if (mask)
		ret = set_pid_filter(f, LX_SDEC_PAYLOAD_PES, mask);
	else
		ret = free_pid_filter(f);

	return ret;
}

static int debug_write_pid(struct sdec_channel *channel, char *command)
{
	int ret;
	u32 pid;
	char dest_str[16];
	char op_str[16];
	enum lx_sdec_pid_filter_dest dest;
	bool is_set = true;

	ret = sscanf(command, "%i %15s %15s", &pid, dest_str, op_str);
	if (ret != 2 && ret != 3)
		return -EINVAL;

	if (ret == 3) {
		if (!strcasecmp("cancel", op_str))
			is_set = false;
		else if (!strcasecmp("set", op_str))
			is_set = true;
		else
			return -EINVAL;
	}

	dest = str_to_pid_filter_dest(dest_str);
	if (pid >= 0x1FFF || dest == LX_SDEC_PFLT_DEST_NONE)
		return -EINVAL;

	mutex_lock(&filter_mutex);
	if (is_set) {
		ret = debug_set_pid(channel, pid, dest);
	} else {
		ret = debug_cancel_pid(channel, pid, dest);
	}
	mutex_unlock(&filter_mutex);

	return ret;
}

static int debug_channel_show(struct te_debug_item *item, struct seq_file *m)
{
	int ret = 0;
	struct sdec_channel *channel = item->private;

	switch (item->flags) {
	case FILTER_DEBUG_ID_PID:
		debug_show_channel_pid_filter(channel, m);
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
	case FILTER_DEBUG_ID_PID:
		ret = debug_write_pid(channel, str);
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

static const struct te_debug_item_info debug_channel_list[] = {
	DBGITM_SIM("pid", &debug_channel_ops, FILTER_DEBUG_ID_PID),
};

static void init_debug(struct sdec_device *dev)
{
	int i;

	for (i = 0; i < dev->num_channel; i++) {
		struct sdec_channel *c = &dev->channels[i];
		debug_create_item_files(debug_channel_list, c, c->debug_dir);
	}

	sdec_debug_register_status_show(dev, SDEC_DEBUG_STATUS_PID_FILTER,
					debug_show_pid_filter);

	sdec_debug_register_status_show(dev, SDEC_DEBUG_STATUS_STREAM_FILTER,
					debug_show_stream_filter);

	sdec_debug_register_status_show(dev, SDEC_DEBUG_STATUS_MCU_FILTER,
					debug_show_mcu_filter);
}

/* sdec sub device functions */

static int filter_dev_suspend(struct sdec_device *dev)
{
	int i;
	struct sdec_data *data = dev->data;
	struct te_reg_pidf_status status;

	for (i = 0; i < dev->filter.num_pidf; i++) {
		TE_REG_GetPidFilter(i, &status);
		data->pidf[i].en = status.en;
		if (status.en) {
			data->pidf[i].pid = status.pid;
			data->pidf[i].ch = status.ch;
			data->pidf[i].type = status.type;
			data->pidf[i].out_en = status.out_en;
			data->pidf[i].out_idx = status.out_idx;
			data->pidf[i].dn_en = status.dn_en;
			data->pidf[i].temi_en = status.temi_en;
		}
	}

	//TODO: Main PIDF Bypass read

	for (i = 0; i < dev->filter.num_sub_channel; i++) {
		TE_REG_GetSubPidFilter(i, &status);
		data->sub_pidf[i].en = status.en;
		data->sub_pidf[i].pid = status.pid;
		data->sub_bypass[i] = status.bypass_mode;
	}

	/* disconnect stream filter callback */
	TE_IPC_RegisterStreamFilterCallback(NULL, NULL);

	/* remove remained callback works */
	reset_callback(&dev->filter);

	return 0;
}

static int filter_dev_resume(struct sdec_device *dev)
{
	int i, ret;
	struct sdec_data *data = dev->data;
	struct te_reg_pidf_conf *conf;

	/* reconnect stream filter callback */
	TE_IPC_RegisterStreamFilterCallback(stream_filter_callback, dev);

	/* Restore PID Registers */
	for (i = 0; i < dev->filter.num_pidf; i++) {
		conf = &data->pidf[i];
		if (conf->en) {
			TE_REG_SetPidFilter(i, conf);
		}
	}
	//TODO: Main PIDF Bypass recover

	for (i = 0; i < dev->filter.num_sub_channel; i++) {
		conf = &data->sub_pidf[i];

		TE_REG_SetSubpidfBypass(i, data->sub_bypass[i]);
		if (conf->en)
			TE_REG_SetSubPidFilter(i, conf);
	}

	ret = stream_filter_recovery(dev);

	return ret;
}

static int filter_dev_ioctl_param(void *priv, unsigned int cmd, void *arg,
				  struct te_ioctl_ptr_param *param)
{
	if (cmd == SDEC_IOC_PFLT_GET_STATUS) {
		LX_SDEC_PFLT_STATUS_PARAM_T *p = arg;

		param->user_ptr = te_ioctl_get_user_ptr(p->status);
		param->kernel_ptr = (void **)&p->status;
		param->size = sizeof(*p->status);
		param->dir = _IOC_READ;
	} else if (cmd == SDEC_IOC_SFLT_GET_STATUS) {
		LX_SDEC_SFLT_STATUS_PARAM_T *p = arg;

		param->user_ptr = te_ioctl_get_user_ptr(p->status);
		param->kernel_ptr = (void **)&p->status;
		param->size = sizeof(*p->status);
		param->dir = _IOC_READ;
	} else if (cmd == SDEC_IOC_SFLT_GET_BUF_INFO) {
		LX_SDEC_SFLT_BUFFER_INFO_PARAM_T *p = arg;

		param->user_ptr = te_ioctl_get_user_ptr(p->info);
		param->kernel_ptr = (void **)&p->info;
		param->size = sizeof(*p->info);
		param->dir = _IOC_READ;
	}

	return 0;
}

static const struct sdec_ioctl_info ioctls[] = {
	IOC_INFO(SDEC_IOC_PFLT_ALLOC, ioc_pid_filter_alloc),
	IOC_INFO(SDEC_IOC_PFLT_FREE, ioc_pid_filter_free),
	IOC_INFO(SDEC_IOC_PFLT_SET, ioc_pid_filter_set),
	IOC_INFO(SDEC_IOC_PFLT_GET_STATUS, ioc_pid_filter_get_status),
	IOC_INFO(SDEC_IOC_PFLT_REQ_TS_HEADER, ioc_set_ts_header),
	IOC_INFO(SDEC_IOC_SFLT_REQUEST, ioc_stream_filter_request),
	IOC_INFO(SDEC_IOC_SFLT_CANCEL, ioc_stream_filter_cancel),
	IOC_INFO(SDEC_IOC_SFLT_SET_RPTR, ioc_stream_filter_set_rptr),
	IOC_INFO(SDEC_IOC_SFLT_GET_STATUS, ioc_stream_filter_get_status),
	IOC_INFO(SDEC_IOC_SFLT_GET_BUF_INFO, ioc_stream_filter_get_buf_info),
};

static int filter_dev_ioctl(void *priv, unsigned int cmd, void *arg)
{
	return sdec_do_ioctl(priv, cmd, arg, filter_mutex, ioctls);
}

static int init_callback(struct sdec_dev_filter *fdev)
{
	int ret;

	ret = te_msgbuf_init(&fdev->callback_buf,
			     sizeof(struct filter_callback),
			     MAX_FILTER_CALLBACK, TE_BUF_FLAG_NO_EVENT);
	if (ret)
		return ret;

	INIT_WORK(&fdev->callback_work, filter_callback_work);
	fdev->callback_min_free = MAX_FILTER_CALLBACK;
	fdev->callback_errors = 0;

	return 0;
}

static int filter_dev_init(struct sdec_device *dev)
{
	int i, ret = -ENOMEM;
	struct sdec_dev_filter *fdev = &dev->filter;

	fdev->num_sub_channel = dev->cfg->num_sub_channel;
	fdev->num_pidf = dev->cfg->num_pid_filter;
	fdev->num_streamf = dev->cfg->num_stream_filter;

	fdev->pidf = vzalloc(fdev->num_pidf * sizeof(struct sdec_pid_filter));
	CHECK_ERROR(!fdev->pidf, goto err_pidf, "can't alloc memory");

	fdev->streamf =
		vzalloc(fdev->num_streamf * sizeof(struct sdec_stream_filter));
	CHECK_ERROR(!fdev->streamf, goto err_streamf, "can't alloc memory");

	ret = init_callback(fdev);
	CHECK_ERROR(ret, goto err_callback, "init_callback failed");

	for (i = 0; i < dev->num_channel; i++) {
		struct sdec_filter_channel *f = &dev->channels[i].filter;

		INIT_LIST_HEAD(&f->pid_list);
		INIT_LIST_HEAD(&f->stream_list);
	}

	TE_IPC_RegisterStreamFilterCallback(stream_filter_callback, dev);
	TE_IPC_RegisterTsHeaderCallback(tsh_filter_callback, dev);

	te_mcu_register_rcallback(get_te_device(dev), TE_MCU_FUNC_TYPE_FILTER,
				  mcu_recovery_filter_pre_callback,
				  mcu_recovery_filter_post_callback, dev);

	init_debug(dev);

	return 0;

err_callback:
	vfree(fdev->streamf);
err_streamf:
	vfree(fdev->pidf);
err_pidf:

	return ret;
}

static void filter_dev_release(struct sdec_device *dev)
{
	struct sdec_dev_filter *fdev = &dev->filter;

	vfree(fdev->streamf);
	vfree(fdev->pidf);
}

static const struct sdec_ioctl ioctl_filter = {
	.magic = SDEC_IOC_FLT_MAGIC,
	.func = filter_dev_ioctl,
	.get_user_param = filter_dev_ioctl_param,
};

const struct sdec_sub_driver sdec_filter_driver = {
	.name = "sdec_filter",
	.init = filter_dev_init,
	.release = filter_dev_release,
	.suspend = filter_dev_suspend,
	.resume = filter_dev_resume,

	.ioctl = &ioctl_filter,
};
