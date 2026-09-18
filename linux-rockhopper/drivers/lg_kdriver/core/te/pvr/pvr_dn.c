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
 *  main driver implementation for pvr device.
 *	pvr device will teach you how to make device driver with new platform.
 *
 *  author		Kyungseok Hyun (ks.hyun@lge.com)
 *  version		1.0
 *  date		2015.03.09
 *  note		Additional information.
 *
 *  @addtogroup lg1150_pvr
 *	@{
 */

#include <lg1k/te/ipc.h>
#include "pvr_impl.h"

#define DN_BUF_WARNIG_LEVEL	20	/* Percentage */
#define DN_BUF_WARNIG_INTERVAL	1000	/* 1 seconds */
#define DN_POLL_INTERVAL	20	/* ms */
/* it should be aligned to 192bytes. not depend on the pkt_len*/
#define DN_SEGMENT_SIZE 	(TIME_TS_PACKET_SIZE * 512) /* 96KB */

#define TRACE_PARAM_ENTER(dn,fmt,args...) \
  log_trace("<== PVR_DN(%d) : %s("fmt")", (dn)->idx, __FUNCTION__, ##args)
#define TRACE_PARAM_EXIT(dn,fmt,args...) \
  log_trace("==> PVR_DN(%d) : %s("fmt")", (dn)->idx, __FUNCTION__, ##args)

#define TRACE_EX_PARAM_ENTER(dn,fmt,args...) \
  log_trace_ex("<== PVR_DN(%d) : %s("fmt")", (dn)->idx, __FUNCTION__, ##args)
#define TRACE_EX_PARAM_EXIT(dn,fmt,args...) \
  log_trace_ex("==> PVR_DN(%d) : %s("fmt")", (dn)->idx, __FUNCTION__, ##args)

#define TRACE_ENTER(dn)			TRACE_PARAM_ENTER(dn,"")
#define TRACE_EXIT(dn)			TRACE_PARAM_EXIT(dn,"")

#define TRACE_EX_ENTER(dn)		TRACE_EX_PARAM_ENTER(dn,"")
#define TRACE_EX_EXIT(dn)		TRACE_EX_PARAM_EXIT(dn,"")


static struct pvr_dn *dn_open(struct pvr_device *dev, int idx)
{
	int i, ret;
	struct pvr_dn *dn = NULL;
	struct pvr_config *cfg = pvr_get_config();

	if (cfg->no_download_support)
		return ERR_PTR(-EPERM);

	mutex_lock(&dev->mutex);

	if (idx < 0) {
		ret = -EBUSY;
		for (i = 0; i < dev->num_dn; i++) {
			if (dev->dn[i].state == PVR_DN_STATE_FREE) {
				ret = 0;
				dn = &dev->dn[i];
				break;
			}
		}
	} else {
		if (idx < dev->num_dn) {
			if (dev->dn[idx].state == PVR_DN_STATE_FREE) {
				ret = 0;
				dn = &dev->dn[idx];
			} else {
				ret = -EBUSY;
			}
		} else {
			ret = -EINVAL;
		}
	}
	if (ret)
		dn = ERR_PTR(ret);
	else
		dn->state = PVR_DN_STATE_IDLE;

	mutex_unlock(&dev->mutex);

	return dn;
}

static void init_hw(struct pvr_dn *dn)
{
	TE_REG_SetDownloadSegmentSize(dn->idx, dn->segment_size);
}

static const char *state_str(enum pvr_dn_state state)
{
	const struct te_val_str list[] = {
		{PVR_DN_STATE_FREE, "free"},
		{PVR_DN_STATE_IDLE, "idle"},
		{PVR_DN_STATE_READY, "ready"},
		{PVR_DN_STATE_RECORD, "record"},
	};

	return find_match_string(list, state, "unknown");
}

/* Picture Index Extractor */
static int pie_set_config(struct pvr_dn *dn, struct lx_pvr_pie_cfg *cfg)
{
	int i;
	u32 mask, val;
	LX_PVR_PIE_PATTERN_T *p;
	struct pvr_buf_info *pie_buf;

	log_noti("pvr(%d) pid:0x%04x, type=%d addr: %x, size: %x",
		 dn->idx, cfg->pid, cfg->type, cfg->addr, cfg->size);

	if (dn->no_pie) {
		log_warning("not supported h/w PIE");
		return 0;
	}

	if (dn->state > PVR_DN_STATE_READY) {
		log_warning("pvr(%d) download state(%s) is not in idle\n",
			    dn->idx, state_str(dn->state));
		return -EINVAL;
	}

	if (cfg->size == 0) {
		log_error("buffer was not allocated\n");
		return -ENOMEM;
	}

	pie_buf = &dn->pie.buf;
	pie_buf->base = cfg->addr;
	pie_buf->end = cfg->addr + cfg->size;
	pie_buf->size = cfg->size;

	TE_REG_SetPieBuffer(dn->idx, pie_buf->base, pie_buf->end);
	TE_REG_DisablePieDetect(dn->idx);	/* disable all pie detection field */
	TE_REG_SetPiePid(dn->idx, cfg->pid);

	switch (cfg->type) {
	case LX_PVR_PIE_TYPE_MPEG2TS:
		TE_REG_SetPieDetect(dn->idx, 0, 0xFF0000, 0xB30000, true);	// SPS
		TE_REG_SetPieDetect(dn->idx, 1, 0xFF0038, 0x000008, true);	// I [5:3] = 1
		TE_REG_SetPieDetect(dn->idx, 2, 0xFF0038, 0x000010, true);	// P [5:3] = 2
		TE_REG_SetPieDetect(dn->idx, 3, 0xFF0038, 0x000018, true);	// B [5:3] = 3
		break;

	case LX_PVR_PIE_TYPE_H264TS:
		TE_REG_SetPieDetect(dn->idx, 0, 0x1F0000, 0x070000, true);	// SPS
		TE_REG_SetPieDetect(dn->idx, 1, 0x1FFF00, 0x091000, true);	// AU Delimeter I
		TE_REG_SetPieDetect(dn->idx, 2, 0x1FFF00, 0x093000, true);	// AU Delimeter P
		TE_REG_SetPieDetect(dn->idx, 3, 0x1F0000, 0x090000, true);	// AU Delimeter B
		break;

	case LX_PVR_PIE_TYPE_HEVCTS:
		TE_REG_SetPieDetect(dn->idx, 1, 0x800000, 0x000000, true);	// NAL Unit Type
		break;

	case LX_PVR_PIE_TYPE_USER:
		for (i = 0; i < 4; i++) {
			p = &cfg->pattern[i];
			mask = p->mask[0] << 16 | p->mask[1] << 8 | p->mask[2];
			val = p->value[0] << 16 | p->value[1] << 8 |
			    p->value[2];
			TE_REG_SetPieDetect(dn->idx, i, mask, val, p->enable);
		}
		break;

	default:
		cfg->type = LX_PVR_PIE_TYPE_NONE;
		break;
	}
	dn->pie.type = cfg->type;

	return 0;
}

static int pie_start(struct pvr_dn *dn)
{
	struct pvr_buf_info *buf;
	u32 wptr;

	TRACE_PARAM_ENTER(dn, "");

	if (dn->no_pie)
		return 0;

	/* init pie buffer */
	buf = &dn->pie.buf;
	buf->rptr = buf->base;
	buf->wptr = buf->base;
	buf->status = LX_PVR_BUF_STAT_READY;

	if (dn->pie.type != LX_PVR_PIE_TYPE_NONE) {
		TE_REG_GetPieWptr(dn->idx, &wptr);
		dn->pie.last_wptr = wptr;	/* save last wptr to check the first received index */
		dn->pie.first_time = true;
		dn->pie.errmsg_enable = true;
		dn->pie.buf_ovf_level = dn->segment_size / PVR_DN_PKT_SIZE * 4;
	}

	return 0;
}

static int pie_stop(struct pvr_dn *dn)
{
	TRACE_PARAM_ENTER(dn, "");

	if (dn->no_pie)
		return 0;

	if (dn->pie.type != LX_PVR_PIE_TYPE_NONE) {
		TE_REG_DisablePieDetect(dn->idx);	/* disable all pie detection field */
		dn->pie.type = LX_PVR_PIE_TYPE_NONE;
	}

	return 0;
}


/*
 * ISR Function
 *
 * Function to calculate the current pie buffer level based on
 * memorized write and read pointers
 */
void pvr_pie_check_overflow(struct pvr_dn *dn)
{
	struct pvr_buf_info *buf = &dn->pie.buf;
	u32 size;

	size = (buf->rptr + buf->size - (buf->wptr + 1)) % buf->size;

	if (size <= dn->pie.buf_ovf_level) {
		buf->status = LX_PVR_BUF_STAT_FULL;
		if (dn->pie.errmsg_enable) {
			dn->pie.errmsg_enable = false;	//disable error message
			log_error
			    ("PIE Buffer Overflow. rptr=0x%08x, wptr=0x%08x size: %x/%x",
			     buf->rptr, buf->wptr, size, dn->pie.buf_ovf_level);
		}
	}
}

/**
 * dn_init - Initialize download module before downloading
 * @src: sdec channel number
 *
 * Return: 0 on success, or -EBUSY if state is not valid or -EINVAL
 */
static int dn_init(struct pvr_dn *dn, u32 src, u8 pkt_len, struct te_hwbuf *buf)
{
	int ret;
	u32 saddr, eaddr;

	CHECK_NULL_PARAM(buf);

	TRACE_PARAM_ENTER(dn, "src=%d", src);

	if (dn->state != PVR_DN_STATE_IDLE && dn->state != PVR_DN_STATE_READY) {
		log_warning("pvr(%d) download state(%s) is not idle or ready\n",
			    dn->idx, state_str(dn->state));
		return -EBUSY;
	}

#ifdef CONFIG_PHYS_ADDR_T_64BIT
	if (te_hwbuf_addr(buf) > U32_MAX) {
		log_error("addr(%llx) over 32bit\n", te_hwbuf_addr(buf));
		return -EINVAL;
	}
#endif
	if (pkt_len == TS_PACKET_SIZE) {
		ret = TE_REG_SetDownloadMode(dn->idx, DOWNLOAD_MODE_188BYTE);

	} else if (pkt_len == TIME_TS_PACKET_SIZE) {
		ret = TE_REG_SetDownloadMode(dn->idx, DOWNLOAD_MODE_192BYTE);
	} else {
		log_error("invalid packet length(%d)", pkt_len);
		ret = -EINVAL;
	}
	if (ret) {
		log_error("TE_REG_SetDownloadMode failed(%d)\n", ret);
		return ret;
	}

	saddr = (u32)te_hwbuf_addr(buf);
	eaddr = (u32)te_hwbuf_eaddr(buf);

	TE_REG_SetDownloadBuffer(dn->idx, saddr, eaddr);

	ret = TE_REG_SetChannelDownloadIdx(src, dn->idx);
	if (ret) {
		log_error("TE_REG_SetChannelDownloadIdx failed(%d)\n", ret);
		return ret;
	}

	dn->hbuf = buf;
	/* Save channel source to enable at start time */
	dn->src = src;
	dn->pkt_len = pkt_len;
	dn->state = PVR_DN_STATE_READY;

	return 0;
}



/*
 * ISR Function
 *
 * Function to calculate the current download buffer level based on
 * memorized write and read pointers
 */
void pvr_dn_check_overflow(struct pvr_dn *dn, u32 wptr)
{
#if 0
	struct pvr_buf_info *buf = &dn->buf;
	u32 size;

	size = (buf->rptr + buf->size - (wptr + 1)) % buf->size;
	if (size <= dn->overflow_bufsize) {	/* overflow */
		buf->status = LX_PVR_BUF_STAT_FULL;
		dn->stats.overflow++;
		if (dn->errmsg_enable) {
			/* In this case, the system was almost crashed */
			dn->errmsg_enable = false;	// disable error message
			log_error
			    ("Download Buffer Overflow. rptr=0x%08x, wptr=0x%08x",
			     buf->rptr, wptr);
		}
	} else if (size < dn->warn_bufsize) {
		if (dn->errmsg_enable) {
			u32 elapsed = jiffies_to_msecs(jiffies - dn->warn_time);
			if (elapsed >= dn->warn_interval) {
				log_warning
				    ("Download Buffer Almost Full - %dKbytes remained",
				     size / 1024);
				dn->warn_time = jiffies;
			}
		}
	}
#endif
}

static void dn_check_overflow(struct pvr_dn *dn)
{
	u32 size = te_hwbuf_free_size(dn->hbuf);

	if (size <= dn->overflow_bufsize) {	/* overflow */
		te_hwbuf_set_error(dn->hbuf, -ENOBUFS);
		dn->stats.overflow++;
		if (dn->errmsg_enable) {
			/* In this case, the system was almost crashed */
			dn->errmsg_enable = false;	// disable error message
			log_error("Download Buffer Overflow\n");
		}
	} else if (size < dn->warn_bufsize) {
		if (dn->errmsg_enable) {
			u32 elapsed = jiffies_to_msecs(jiffies - dn->warn_time);
			if (elapsed >= dn->warn_interval) {
				log_warning("Download Buffer Almost Full -"
					    "%dKbytes remained\n",
					     size / 1024);
				dn->warn_time = jiffies;
			}
		}
	}
}

static void dn_work(struct work_struct *work)
{
	int rc;
	u32 wptr, pie_wptr;
	struct pvr_dn *dn = container_of(work, struct pvr_dn, work.work);
	struct te_hwbuf *hbuf = dn->hbuf;

	TE_REG_GetDownloadWptr(dn->idx, &wptr);

	if (dn->first_time) {
		if (wptr != dn->last_wptr) {
			dn->first_time = false;
		} else {
			goto next;
		}
	}

	if (dn->pie.type != LX_PVR_PIE_TYPE_NONE) {
		u32 rptr = te_hwbuf_rptr(hbuf);
		u32 base = (u32)te_hwbuf_addr(hbuf);
		u32 dn_size, size = te_hwbuf_size(hbuf);
		u32 spare_pkt_size = 3 * dn->pkt_len;

		/*
		 * If the Picture Index exists in the end of the packet,
		 * it can be detected when the next packet is received.
		 * So, we have to return the write ptr minus packet size;
		 */
		dn_size = (wptr + size - rptr) % size;
		if (dn_size > spare_pkt_size) {
			if (wptr < (base + spare_pkt_size))
				wptr = wptr + size - spare_pkt_size;
			else
				wptr -= spare_pkt_size;
		} else {
			wptr = rptr;
		}

		TE_REG_GetPieWptr(dn->idx, &pie_wptr);
		if (dn->pie.first_time) {
			if (pie_wptr != dn->pie.last_wptr) {
				dn->pie.first_time = false;
			}
		} else {
			dn->pie.buf.wptr = pie_wptr;
			pvr_pie_check_overflow(dn);

		}
	}


	rc = te_hwbuf_set_wptr(dn->hbuf, wptr);
	if (rc > 0) {
		dn_check_overflow(dn);
		if (!te_hwbuf_error(dn->hbuf))
			dn->errmsg_enable = true;
	}


 next:
	schedule_delayed_work(&dn->work, msecs_to_jiffies(DN_POLL_INTERVAL));
}

/**
 * Start PVR download for specified PVR channel
 *
 * @def PVR_IOC_DN_CONTROL
 * @param	dev 		[in	] dev handle for pvr channel
 * @return	if succeeded - 0, else - errno.
 */
static int dn_start(struct pvr_dn *dn)
{
	u32 wptr;

	TRACE_ENTER(dn);

	if (dn->state != PVR_DN_STATE_READY) {
		log_warning("pvr(%d) download state(%s) is not in ready\n",
			    dn->idx, state_str(dn->state));
		return -EINVAL;
	}

	te_hwbuf_reset(dn->hbuf);
	TE_REG_GetDownloadWptr(dn->idx, &wptr);

	dn->first_time = true;
	dn->last_wptr = wptr;

	/* Reset the error variables */
	dn->stats.unitbuf = 0;
	dn->stats.overflow = 0;

	dn->overflow_bufsize = dn->segment_size * 3;
	dn->warn_bufsize = te_hwbuf_size(dn->hbuf) * DN_BUF_WARNIG_LEVEL / 100;
	dn->warn_interval = DN_BUF_WARNIG_INTERVAL;
	dn->warn_time = 0;
	dn->errmsg_enable = true;
	/* start PIE */
	pie_start(dn);

	/* Start download */
	TE_REG_SetChannelDownloadEnable(dn->idx, dn->src, true);

	schedule_delayed_work(&dn->work, msecs_to_jiffies(DN_POLL_INTERVAL));

	dn->state = PVR_DN_STATE_RECORD;

	return 0;
}

/**
 * Stop PVR download for specified PVR channel
 *
 * @def PVR_IOC_DN_CONTROL
 * @param	dev 		[in	] dev handle for pvr channel
 * @return	if succeeded - 0, else - errno.
 */
static int dn_stop(struct pvr_dn *dn)
{

	TRACE_ENTER(dn);

	if (dn->state < PVR_DN_STATE_RECORD) {
		log_warning("pvr(%d) download state(%s) is not record\n",
			    dn->idx, state_str(dn->state));
		return 0;
	}

	cancel_delayed_work_sync(&dn->work);

	/* Stop download */
	TE_REG_SetChannelDownloadEnable(dn->idx, dn->src, false);

	/* stop PIE */
	pie_stop(dn);

	dn->state = PVR_DN_STATE_READY;

	return 0;
}



static int dn_release(struct pvr_dn *dn)
{
	if (dn->state > PVR_DN_STATE_READY)
		dn_stop(dn);

	dn->state = PVR_DN_STATE_IDLE;

	return 0;
}

static void dn_close(struct pvr_dn *dn)
{
	dn_release(dn);
	dn->state = PVR_DN_STATE_FREE;
}



/**
 * pvr_dn_open - open pvr download device
 * @idx: pvr download device index or negative value to alloc any free device
 *
 * Return: struct pvr_dn handle on success, or ERR_PTR on error.
 */
struct pvr_dn *pvr_dn_open(struct pvr_device *dev, int idx)
{
	return dn_open(dev, idx);
}

/**
 * pvr_dn_get_index - get pvr download device index to connect sdec channel
 */
int pvr_dn_get_index(struct pvr_dn *dn)
{
	return dn->idx;
}

/**
 * pvr_dn_init - Initialize download module before downloading
 * @src: sdec channel number
 * @buf: allocated h/w buffer
 *
 * Return: 0 on success, or -EBUSY if state is not valid or -EINVAL
 */
int pvr_dn_init(struct pvr_dn *dn, u32 src, u8 pkt_len, struct te_hwbuf *buf)
{
	int ret;

	mutex_lock(&dn->mutex);
	ret = dn_init(dn, src, pkt_len, buf);
	mutex_unlock(&dn->mutex);

	return ret;
}

int pvr_dn_start(struct pvr_dn *dn)
{
	int ret;

	mutex_lock(&dn->mutex);
	ret = dn_start(dn);
	mutex_unlock(&dn->mutex);

	return ret;
}

int pvr_dn_stop(struct pvr_dn *dn)
{
	int ret;

	mutex_lock(&dn->mutex);
	ret = dn_stop(dn);
	mutex_unlock(&dn->mutex);

	return ret;
}

void pvr_dn_close(struct pvr_dn *dn)
{
	mutex_lock(&dn->mutex);
	dn_close(dn);
	mutex_unlock(&dn->mutex);
}

int pvr_dn_write_data(struct pvr_dn *dn, u8 *data, int size)
{
	int ret;
	u8 *msg = vmalloc(size+1);

	if (!msg)
		return -ENOMEM;

	msg[0] = IPC_WRITE_DVR_DN;
	memcpy(&msg[1], data, size);

	mutex_lock(&dn->mutex);
	ret = te_ipc_write_data(msg, size+1);
	mutex_unlock(&dn->mutex);

	vfree(msg);

	return ret;
}

static int pm_resume(struct pvr_dn *dn)
{
/*
	considered the case: dn_init -> Instant boot -> dn_start
*/
	if (dn->state == PVR_DN_STATE_READY) {
		dn_init(dn, dn->src, dn->pkt_len, dn->hbuf);
	}
	return 0;
}

/**
 * Stop download if it is progressing
 *
 * @param	dev 	[in	] dev handle for pvr channel
 * @return	if succeeded - 0, else - errno.
 */
static int pm_suspend(struct pvr_dn *dn)
{
	if (dn->state > PVR_DN_STATE_READY) {
		log_error("download is not stopped before suspend\n");
		dn_stop(dn);
	}

	return 0;
}

static void debug_show_status(struct pvr_device *dev, struct seq_file *m)
{
	int i;

	seq_printf(m, "DOWNLOAD\n");
	for (i = 0; i < dev->num_dn; i++) {
		struct pvr_dn *dn = &dev->dn[i];

		mutex_lock(&dn->mutex);
		seq_printf(m, " %d state : %s\n", i, state_str(dn->state));
		if (dn->state > PVR_DN_STATE_READY) {
			seq_printf(m, "   range(0x%08x--0x%08x)\n",
				   (u32)te_hwbuf_addr(dn->hbuf),
				   (u32)te_hwbuf_eaddr(dn->hbuf));
			seq_printf(m, "   wptr:0x%08x, rptr:0x%08x\n",
				   (u32)te_hwbuf_wptr(dn->hbuf),
				   (u32)te_hwbuf_rptr(dn->hbuf));
			seq_printf(m, "   used:%d, total:%d\n",
				   te_hwbuf_avail_size(dn->hbuf),
				   te_hwbuf_size(dn->hbuf));
			if(dn->stats.overflow)
				seq_printf(m, "   overflow:%d\n",
					   dn->stats.overflow);
		}
		mutex_unlock(&dn->mutex);
	}
	seq_printf(m, "\n");
}

static void init_debug(struct pvr_device *dev)
{
	pvr_debug_register_status_show(dev, PVR_DEBUG_STATUS_DN_DEV,
				       debug_show_status);
}

static int ioc_dn_init(struct pvr_dn_fh *fh, LX_PVR_DN_CFG_T *cfg)
{
	struct pvr_dn *dn = fh->dev;
	struct te_hwbuf *hbuf = &fh->hbuf;

	te_hwbuf_init(hbuf, cfg->addr, cfg->size, 0, 0);

	return dn_init(dn, cfg->src, TIME_TS_PACKET_SIZE, hbuf);
}

static int ioc_dn_control(struct pvr_dn_fh *fh, LX_PVR_DN_CONTROL_T *ctl)
{
	int ret;

	if (ctl->type == LX_PVR_DN_START)
		ret = dn_start(fh->dev);
	else if (ctl->type == LX_PVR_DN_STOP)
		ret = dn_stop(fh->dev);
	else {
		log_error("invalid download control(%d)\n", ctl->type);
		ret = -EINVAL;
	}

	return ret;
}

static int ioc_dn_get_buffer_info(struct pvr_dn_fh *fh,
				  LX_PVR_DN_BUF_INFO_T *info)
{
	struct pvr_dn *dn = fh->dev;
	LX_PVR_BUF_PTR_T *ptr = &info->ptr;

	if (dn->state < PVR_DN_STATE_RECORD) {
		log_error("pvr(%d) download state(%s) is not record\n",
			  dn->idx, state_str(dn->state));
		return -EINVAL;
	}

	ptr->rptr = te_hwbuf_rptr(dn->hbuf);
	ptr->wptr = te_hwbuf_wptr(dn->hbuf);

	// TODO: add buffer status processing if necessary
	if (te_hwbuf_error(dn->hbuf)) {
		info->status = LX_PVR_BUF_STAT_FULL;
	} else {
		info->status = LX_PVR_BUF_STAT_READY;
	}

	TRACE_EX_PARAM_EXIT(dn, "wptr=0x%08x, rptr=0x%08x", ptr->wptr,
			    ptr->rptr);

	return 0;
}

static int ioc_dn_set_rptr(struct pvr_dn_fh *fh, LX_PVR_BUF_PTR_T *param)
{
	int ret;
	u32 ridx;
	struct pvr_dn *dn = fh->dev;

	TRACE_EX_PARAM_ENTER(dn, "ptr=0x%08x", param->rptr);

	if (dn->state < PVR_DN_STATE_RECORD) {
		log_error("pvr(%d) download state(%s) is not record\n",
			  dn->idx, state_str(dn->state));
		return -EINVAL;
	}

	ret = te_hwbuf_paddr_to_idx(dn->hbuf, param->rptr, &ridx);
	if (ret) {
		log_error("out of range rptr(0x%08x)\n", param->rptr);
		return ret;
	}

	ridx -= (ridx % 192);

	te_hwbuf_set_ridx(dn->hbuf, ridx);

	return 0;
}

static int ioc_pie_set_config(struct pvr_dn_fh *fh, struct lx_pvr_pie_cfg *cfg)
{
	return pie_set_config(fh->dev, cfg);
}

static int ioc_pie_get_buffer_info(struct pvr_dn_fh *fh,
				   struct lx_pvr_buf_info *info)
{
	u32 wptr;
	struct pvr_dn *dn = fh->dev;
	LX_PVR_BUF_PTR_T *ptr = &info->ptr;
	struct pvr_buf_info *buf = &dn->pie.buf;

	if (dn->no_pie) {
		log_warning("not supported h/w pie");
		return 0;
	}

	if (dn->pie.type == LX_PVR_PIE_TYPE_NONE) {
		ptr->wptr = ptr->rptr = buf->base;
		info->status = LX_PVR_BUF_STAT_EMPTY;
		return 0;
	}

	TE_REG_GetPieWptr(dn->idx, &wptr);
	if (dn->pie.first_time) {	/* not received any index. wptr in register is the last value */
		if (wptr != dn->pie.last_wptr) {
			dn->pie.first_time = false;
		} else {
			wptr = buf->base;
		}
	}

	ptr->rptr = buf->rptr;
	ptr->wptr = wptr;

	info->status = buf->status;
	/* Reset the buffer state to normal */
	if (buf->status == LX_PVR_BUF_STAT_FULL) {
		buf->status = LX_PVR_BUF_STAT_READY;
	}

	TRACE_EX_PARAM_EXIT(dn, "wptr=0x%08x, rptr=0x%08x", ptr->wptr,
			    ptr->rptr);

	return 0;
}

static int ioc_pie_set_rptr(struct pvr_dn_fh *fh, LX_PVR_BUF_PTR_T *param)
{
	struct pvr_dn *dn = fh->dev;
	u32 rptr = param->rptr;
	struct pvr_buf_info *buf = &dn->pie.buf;

	TRACE_EX_PARAM_ENTER(dn, "ptr=0x%08x", rptr);

	if (dn->pie.type == LX_PVR_PIE_TYPE_NONE)
		return 0;

	if (!is_valid_addr(buf, rptr)) {
		log_error("out of range rptr(0x%08x)\n", rptr);
		return -EINVAL;
	}

	if (buf->status != LX_PVR_BUF_STAT_READY) {
		log_error("pvr(%d) download state(%d) is not in ready\n",
			  dn->idx, dn->state);
		return -EFAULT;
	}

	buf->rptr = rptr;

	return 0;
}

static int ioctl_device(void *priv, unsigned int cmd, void *arg)
{
	int ret;
	struct pvr_fh *__fh = priv;
	struct pvr_dn_fh *fh = &__fh->dn;
	struct pvr_dn *dn = fh->dev;

	if (!dn)
		return -EINVAL;

	mutex_lock(&dn->mutex);
	switch (cmd) {
	case PVR_IOC_DN_INIT: {
		struct lx_pvr_dn_cfg *p = arg;
		if (!pvr_device_check_paddr_range(__fh, p->addr, p->size)) {
			ret = -EFAULT;
			break;
		}

		ret = ioc_dn_init(fh, p);
		break;
	}
	case PVR_IOC_DN_CONTROL:
		ret = ioc_dn_control(fh, arg);
		break;

	case PVR_IOC_DN_GET_BUF_INFO:
		ret = ioc_dn_get_buffer_info(fh, arg);
		break;

	case PVR_IOC_DN_SET_READ_PTR:
		ret = ioc_dn_set_rptr(fh, arg);
		break;

	case PVR_IOC_DN_SET_PIE_CFG:
		ret = ioc_pie_set_config(fh, arg);
		break;

	case PVR_IOC_DN_GET_PIE_BUF_INFO:
		ret = ioc_pie_get_buffer_info(fh, arg);
		break;

	case PVR_IOC_DN_SET_PIE_READ_PTR:
		ret = ioc_pie_set_rptr(fh, arg);
		break;

	default:
		log_error("invalid command[0x%08x]. magic=0x%02X, num=%d",
			  cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));
		ret = -ENOTTY;
		break;
	}
	mutex_unlock(&dn->mutex);

	return ret;
}

static int open_device(struct pvr_fh *fh)
{
	struct pvr_dn *dn;

	dn = dn_open(fh->dev, -1);
	if (IS_ERR(dn)) {
		log_error("no avail download device\n");
		return PTR_ERR(dn);
	}
	fh->dn.dev = dn;

	return 0;
}

static void close_device(struct pvr_fh *fh)
{
	if (fh->dn.dev)
		dn_close(fh->dn.dev);
}

static struct pvr_node dn_node = {
	.open = open_device,
	.close = close_device,
	.ioctl = ioctl_device,
};

static int init_device(struct pvr_device *dev)
{
	int i;

	dev->node[PVR_DEV_TYPE_DN] = &dn_node;

	for (i = 0; i < dev->num_dn; i++) {
		struct pvr_dn *d = &dev->dn[i];

		d->idx = i;
		d->state = PVR_DN_STATE_FREE;
		mutex_init(&d->mutex);
		spin_lock_init(&d->spinlock);
		INIT_DELAYED_WORK(&d->work, dn_work);

		d->no_pie = dev->cfg->no_pie;
		d->segment_size = DN_SEGMENT_SIZE;

		init_hw(d);
	}
	init_debug(dev);

	return 0;
}

static void release_device(struct pvr_device *dev)
{
	int i;

	for (i = 0; i < dev->num_dn; i++) {
		struct pvr_dn *d = &dev->dn[i];
		dn_close(d);
	}
}

static int suspend_device(struct pvr_device *dev)
{
	int i;

	for (i = 0; i < dev->num_dn; i++) {
		struct pvr_dn *dn = &dev->dn[i];

		if (!dn->state == PVR_DN_STATE_FREE)
			continue;

		pm_suspend(dn);
	}

	return 0;
}

static int resume_device(struct pvr_device *dev)
{
	int i;

	for (i = 0; i < dev->num_dn; i++) {
		struct pvr_dn *dn = &dev->dn[i];

		init_hw(dn);
		if (!dn->state == PVR_DN_STATE_FREE)
			continue;

		pm_resume(dn);
	}

	return 0;
}

const struct pvr_sub_driver pvr_dn_driver = {
	.name = "pvr_dn",

	.init = init_device,
	.release = release_device,
	.suspend = suspend_device,
	.resume = resume_device,
};
