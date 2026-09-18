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

#include "pvr_impl.h"

#define DEFAULT_MAX_JITTER	0x00A98AC7	/* 0.4 second */
#define DEFAULT_WAIT_CYCLE	0x1C77	/* 10MBytes/sec */
#define UP_POLL_INTERVAL	50	/* ms */

#define TRACE_PARAM_ENTER(up,fmt,args...) \
  log_trace("<== PVR_UP(%d) : %s("fmt")", up->idx, __FUNCTION__, ##args)
#define TRACE_PARAM_EXIT(up,fmt,args...) \
  log_trace("==> PVR_UP(%d) : %s("fmt")", up->idx, __FUNCTION__, ##args)

#define TRACE_EX_PARAM_ENTER(up,fmt,args...) \
  log_trace_ex("<== PVR_UP(%d) : %s("fmt")", up->idx, __FUNCTION__, ##args)
#define TRACE_EX_PARAM_EXIT(up,fmt,args...) \
  log_trace_ex("==> PVR_UP(%d) : %s("fmt")", up->idx, __FUNCTION__, ##args)

#define TRACE_ENTER(up)		TRACE_PARAM_ENTER(up,"")
#define TRACE_EXIT(up)		TRACE_PARAM_EXIT(up,"")

#define TRACE_EX_ENTER(up)	TRACE_EX_PARAM_ENTER(up,"")
#define TRACE_EX_EXIT(up)	TRACE_EX_PARAM_EXIT(up,"")



static struct pvr_up *up_open(struct pvr_device *dev, int idx)
{
	int i, ret;
	struct pvr_up *up = NULL;

	mutex_lock(&dev->mutex);

	if (idx < 0) {
		ret = -EBUSY;
		for (i = 0; i < dev->num_up; i++) {
			if (dev->up[i].state == PVR_UP_STATE_FREE) {
				ret = 0;
				up = &dev->up[i];
				break;
			}
		}
	} else {
		if (idx < dev->num_up) {
			if (dev->up[idx].state == PVR_UP_STATE_FREE) {
				ret = 0;
				up = &dev->up[idx];
			} else {
				ret = -EBUSY;
			}
		} else {
			ret = -EINVAL;
		}
	}
	if (ret)
		up = ERR_PTR(ret);
	else
		up->state = PVR_UP_STATE_IDLE;

	mutex_unlock(&dev->mutex);

	return up;
}


static void init_hw(struct pvr_up *up)
{
	TE_REG_SetUploadWaitCycle(up->idx, DEFAULT_WAIT_CYCLE);
	TE_REG_SetUploadMaxJitter(up->idx, DEFAULT_MAX_JITTER);
}

static const char *state_str(enum pvr_up_state state)
{
	const struct te_val_str list[] = {
		{PVR_UP_STATE_FREE, "free"},
		{PVR_UP_STATE_IDLE, "idle"},
		{PVR_UP_STATE_READY, "ready"},
		{PVR_UP_STATE_PLAY, "play"},
		{PVR_UP_STATE_PAUSE, "pause"},
	};

	return find_match_string(list, state, "unknown");
}

static enum te_reg_upload_ready_src dest_to_reg_ready_src(LX_PVR_UP_DEST_T dest)
{
	const struct te_type_conv list[] = {
		{LX_PVR_UP_DEST_SDEC_CH0, UPLOAD_READY_SRC_TSBUF0},
		{LX_PVR_UP_DEST_SDEC_CH1, UPLOAD_READY_SRC_TSBUF1},
		{LX_PVR_UP_DEST_SDEC_CH2, UPLOAD_READY_SRC_TSBUF2},
		{LX_PVR_UP_DEST_SDEC_CH3, UPLOAD_READY_SRC_TSBUF3},
		{LX_PVR_UP_DEST_SDEC_CH4, UPLOAD_READY_SRC_SUB_TSBUF0},
		{LX_PVR_UP_DEST_SDEC_CH5, UPLOAD_READY_SRC_SUB_TSBUF1},
		{LX_PVR_UP_DEST_TS_OUT0, UPLOAD_READY_SRC_TPO_BUF},
		{LX_PVR_UP_DEST_A3_CH0, UPLOAD_READY_SRC_A3_CH0},
		{LX_PVR_UP_DEST_A3_CH1, UPLOAD_READY_SRC_A3_CH1},
		{LX_PVR_UP_DEST_A3_CH2, UPLOAD_READY_SRC_A3_CH2},
		{LX_PVR_UP_DEST_A3_CH3, UPLOAD_READY_SRC_A3_CH3},
		{LX_PVR_UP_DEST_ANY, UPLOAD_READY_ALWAYS},
	};

	return convert_to_type1(list, dest, UPLOAD_READY_ALWAYS);
}

static void hwbuf_write_callback(void *arg, u32 idx)
{
	struct pvr_up *up = arg;
	phys_addr_t addr;

	/* wptr have to be aligned to 16bytes and packet length.
	 * packet length 192 is already aligned to 16 but 188 is not aligned.
	 */
	if (up->pkt_len == 188)
		idx -= (idx % (4 * 188));
	else
		idx -= (idx % 192);

	te_hwbuf_idx_to_paddr(up->hbuf, idx, &addr);
	TE_REG_SetUploadWptr(up->idx, addr);

	/* available state: PLAY & PAUSE */
	if (up->state >= PVR_UP_STATE_PLAY && up->first_time) {
		if (up->mode == LX_PVR_UPMODE_NORMAL && up->use_timestamp) {
			TE_REG_SetUploadIntrEnable(up->idx, UPLOAD_INTR_EMPTY,
						   true);
		}

		TE_REG_SetUploadEnable(up->idx, true);
		up->first_time = false;
	}
}

/**
 * Initialize pvr upload before uploading
 *
 * @def PVR_IOC_UP_INIT
 * @param	dev 	[in	] dev handle for pvr channel
 * @param	addr 	[in ] buffer base address
 * @param	size 	[in ] buffer size
 * @param	pkt_len [in ] packet length(188/192)
 * @return	if succeeded - 0, else - errno.
 */
static int up_init(struct pvr_up *up, struct te_hwbuf *buf, u8 pkt_len,
		   enum lx_pvr_up_dest dest)
{
	enum te_reg_upload_ready_src ready_src;
	u32 saddr, eaddr;

	CHECK_NULL_PARAM(buf);
	CHECK_PARAM(pkt_len != 188 && pkt_len != 192,
		    "invalid pkt_len(%d)", pkt_len);


	TRACE_PARAM_ENTER(up, "pkt_len=%d,dest=%d", pkt_len, dest);

	if (up->state != PVR_UP_STATE_IDLE && up->state != PVR_UP_STATE_READY) {
		log_warning("pvr(%d) upload state(%s) is not idle and ready\n",
			    up->idx, state_str(up->state));
		return -EBUSY;
	}

	/* Disable upload */
	TE_REG_SetUploadEnable(up->idx, false);

	/* Clear the Pause state just in case */
	TE_REG_SetUploadPause(up->idx, false);

	te_reg_upload_set_tlv_enable(up->idx, false);

#ifdef CONFIG_PHYS_ADDR_T_64BIT
	if (te_hwbuf_addr(buf) > U32_MAX) {
		log_error("addr(%llx) over 32bit\n", te_hwbuf_addr(buf));
		return -EINVAL;
	}
#endif
	/* Set Buffer with Physical Address */
	saddr = (u32)te_hwbuf_addr(buf);
	eaddr = (u32)te_hwbuf_eaddr(buf);

	TE_REG_SetUploadBuffer(up->idx, saddr, eaddr);

	// TODO: Reset the upload block for the new bound to take effect

	/*
	 * The packet length is memorized, and used when the upload
	 * is started after copying first block of data
	 */
	up->pkt_len = pkt_len;

	if (pkt_len == 188) {
		up->use_timestamp = false;
		TE_REG_SetUploadPacketType(up->idx, UPLOAD_PKT_TYPE_188BYTE);
		TE_REG_SetUploadWaitMode(up->idx, UPLOAD_WAIT_MODE_WAIT_CYCLE);
		TE_REG_SetUploadAutoCopyEn(up->idx, false);
	} else {		// 192
		up->use_timestamp = true;
		TE_REG_SetUploadPacketType(up->idx, UPLOAD_PKT_TYPE_192BYTE);
		TE_REG_SetUploadWaitMode(up->idx, UPLOAD_WAIT_MODE_TIMESTAMP);
		TE_REG_SetUploadAutoCopyEn(up->idx, true);
	}

	ready_src = dest_to_reg_ready_src(dest);
	TE_REG_SetUploadReadySel(up->idx, ready_src);

	up->hbuf = buf;
	up->dest = dest;

	te_hwbuf_set_write_callback(buf, hwbuf_write_callback, up);

	/* set trick mode to normal */
	up->mode = LX_PVR_UPMODE_NORMAL;
	TE_REG_SetUploadTrickMode(up->idx, UPLOAD_TRICK_MODE_NORMAL);

	up->state = PVR_UP_STATE_READY;
	return 0;
}


static void up_work(struct work_struct *work)
{
	u32 rptr;
	struct pvr_up *up = container_of(work, struct pvr_up, work.work);

	TE_REG_GetUploadRptr(up->idx, &rptr);
	te_hwbuf_set_rptr(up->hbuf, rptr);

	schedule_delayed_work(&up->work, msecs_to_jiffies(UP_POLL_INTERVAL));
}

/**
 * Start pvr upload module
 *
 * @def PVR_IOC_UP_CONTROL
 * @param	dev		[in	] dev handle for pvr channel
 * @return	if succeeded - 0, else - errno.
 */
static int up_start(struct pvr_up *up)
{
	TRACE_ENTER(up);

	if (up->state != PVR_UP_STATE_READY) {
		log_warning("pvr(%d) upload state(%s) is not in ready\n",
			    up->idx, state_str(up->state));
		return -EINVAL;
	}

	te_hwbuf_reset(up->hbuf);

	/* Reset the error variables */
	up->empty = false;

	up->stats.almost_empty = 0;
	up->stats.empty = 0;
	up->stats.sync_err = 0;

	TE_REG_ResetUpload(up->idx);

	/* This flag is for enabling the upload after data copy for first time */
	up->first_time = true;

	schedule_delayed_work(&up->work, msecs_to_jiffies(UP_POLL_INTERVAL));

	up->state = PVR_UP_STATE_PLAY;

	return 0;
}

/**
 * Stop pvr upload module
 *
 * @def PVR_IOC_UP_CONTROL
 * @param	dev 	[in	] dev handle for pvr channel
 * @return	if succeeded - 0, else - errno.
 */
static int up_stop(struct pvr_up *up)
{
	TRACE_ENTER(up);

	if (up->state < PVR_UP_STATE_PLAY) {
		log_warning("pvr(%d) upload state(%s) is not play\n",
			    up->idx, state_str(up->state));
		return -EINVAL;
	}

	cancel_delayed_work_sync(&up->work);

	TE_REG_SetUploadIntrEnable(up->idx, UPLOAD_INTR_EMPTY, false);	//Disable the interrupt

	TE_REG_SetUploadEnable(up->idx, false);

	up->state = PVR_UP_STATE_READY;

	return 0;
}

/**
 * Reset the buffer base, end, read/write pointers for upload buffer
 *
 * @def PVR_IOC_UP_CONTROL
 * @param	dev 	[in	] dev handle for pvr channel
 * @return	if succeeded - 0, else - errno.
 */
static int up_reset(struct pvr_up *up)
{
	TRACE_ENTER(up);

	if (up->state < PVR_UP_STATE_PLAY) {
		log_warning("pvr(%d) upload state(%s) is not play\n",
			    up->idx, state_str(up->state));
		return -EINVAL;
	}

	TE_REG_SetUploadEnable(up->idx, false);
	TE_REG_SetUploadIntrEnable(up->idx, UPLOAD_INTR_EMPTY, false);	//Disable the interrupt

	/* set the write pointer to the start of buffer */
	te_hwbuf_reset(up->hbuf);

	TE_REG_ResetUpload(up->idx);

	/* After resetting this pointers, enable the upload during the next data transfer */
	up->first_time = true;

	return 0;
}

/**
 * Set Upload Mode
 *
 * @def PVR_IOC_UP_CONTROL
 * @param	dev		[in	] PVR Ctrl
 * @param	mode		[in ] Normal/Trick
 * @return	if succeeded - 0, else - errno.
 */
static int up_set_mode(struct pvr_up *up, enum lx_pvr_up_mode mode)
{
	bool use_timestamp;
	enum te_reg_up_trick_mode trick_mode;

	CHECK_PARAM(mode >= LX_PVR_UPMODE_MAX, "invalid mode[%d]", mode);

	TRACE_PARAM_ENTER(up, "mode=%d", mode);

	if (up->pkt_len == 188)
		use_timestamp = false;
	else
		use_timestamp =
		    (mode == LX_PVR_UPMODE_TRICK_MODE) ? false : true;

	if (mode == LX_PVR_UPMODE_SLOW)
		trick_mode = UPLOAD_TRICK_MODE_1DIV2;
	else if (mode == LX_PVR_UPMODE_FAST2X)
		trick_mode = UPLOAD_TRICK_MODE_2X;
	else
		trick_mode = UPLOAD_TRICK_MODE_NORMAL;

	if (up->state == PVR_UP_STATE_IDLE) {

	} else if (up->state == PVR_UP_STATE_PLAY) {
		// TODO: How to change trick mode ?
	} else {		// PAUSE

	}

	/* set trick mode */
	TE_REG_SetUploadTrickMode(up->idx, trick_mode);

	if (use_timestamp) {
		TE_REG_SetUploadWaitMode(up->idx, UPLOAD_WAIT_MODE_TIMESTAMP);
		TE_REG_SetUploadAutoCopyEn(up->idx, true);
	} else {
		TE_REG_SetUploadWaitMode(up->idx, UPLOAD_WAIT_MODE_WAIT_CYCLE);
		TE_REG_SetUploadAutoCopyEn(up->idx, false);
	}

	/* available state: PLAY & PAUSE */
	if (up->state >= PVR_UP_STATE_PLAY && !up->first_time) {
		if (mode == LX_PVR_UPMODE_NORMAL && use_timestamp) {
			TE_REG_SetUploadIntrEnable(up->idx, UPLOAD_INTR_EMPTY,
						   true);
		} else {
			TE_REG_SetUploadIntrEnable(up->idx, UPLOAD_INTR_EMPTY,
						   false);
		}
	}

	up->mode = mode;
	up->use_timestamp = use_timestamp;

	return 0;
}

/**
 * Set Upload Speed
 * Only used if not using timestamp
 *
 * @def PVR_IOC_UP_CONTROL
 * @param	dev		[in	] dev handle for pvr channel
 * @param	speed		[in	] Upload Speed - bytes/sec
 * @return	if succeeded - 0, else - errno.
 */
static int up_set_speed(struct pvr_up *up, u32 speed)
{
	u32 kbps;
	u32 wait_cycle;
	u32 delta;

	TRACE_PARAM_ENTER(up, "speed=%d", speed);

	/*
	 * PacketLength * CLK / WaitCycle = Bytes/Sec
	 *
	 * WaitCycle =  (398000000 * PacketLength) / BPS
	 *           =  (388671.875 * PacketLength) / KBPS
	 *
	 * WaitCycle =  (480000000 * PacketLength) / BPS
	 *           =  (468750 * PacketLength) / KBPS
	 *
	 * if WaitCycle =  0x2000 and PacketLength = 192
	 *   DataRate = (192 * 398000000) /8192 = 8.895(MBytes/sec)
	 */

#define UPLOAD_SPEED_MIN	(10)	/* 1KBps */
#define UPLOAD_SPEED_MAX	(200*1024)	/* 200MBps */

#define DELTA_FOR_398MHZ	388672	/* M16 */
#define DELTA_FOR_480MHZ	468750	/* >= M16+ */

// TODO: add te clock in te_cfg
	delta = DELTA_FOR_480MHZ;

	kbps = speed >> 10;
	if (kbps < UPLOAD_SPEED_MIN) {
		log_warning("Too slow... Up to %dKBps", UPLOAD_SPEED_MIN);
		kbps = UPLOAD_SPEED_MIN;
	} else if (kbps > UPLOAD_SPEED_MAX) {
		log_warning("Too fast... Down to %dMBps",
			    UPLOAD_SPEED_MAX / 1024);
		kbps = UPLOAD_SPEED_MAX;
	}

	wait_cycle = (u32)(delta * up->pkt_len) / kbps;

	TE_REG_SetUploadWaitCycle(up->idx, wait_cycle);

	return 0;
}

/**
 * Pause PVR upload for specified PVR channel
 *
 * @def PVR_IOC_UP_CONTROL
 * @param	dev		[in	] dev handle for pvr channel
 * @return	if succeeded - 0, else - errno.
 */
static int up_pause(struct pvr_up *up)
{
	TRACE_ENTER(up);

	if (up->state < PVR_UP_STATE_PLAY) {
		log_warning("pvr(%d) upload state(%s) is not play\n",
			    up->idx, state_str(up->state));
		return -EINVAL;
	}

	/* Change to Pause state */
	TE_REG_SetUploadPause(up->idx, true);

	up->state = PVR_UP_STATE_PAUSE;

	return 0;
}

static int up_set_tlv(struct pvr_up *up, bool enable)
{
	int ret;

	TRACE_ENTER(up);

	if (up->state != PVR_UP_STATE_READY) {
		log_warning("pvr(%d) state(%s) is not ready\n",
			    up->idx, state_str(up->state));
		return -EINVAL;
	}

	ret = te_reg_upload_set_tlv_enable(up->idx, enable);

	return ret;
}

/**
 * Resume PVR upload for specified PVR channel
 *
 * @def PVR_IOC_UP_CONTROL
 * @param	dev		[in	] dev handle for pvr channel
 * @return	if succeeded - 0, else - errno.
 */
static int up_resume(struct pvr_up *up)
{

	TRACE_ENTER(up);

	if (up->state != PVR_UP_STATE_PAUSE) {
		log_warning("pvr(%d) upload state(%s) is not in pause\n",
			    up->idx, state_str(up->state));
		return -EINVAL;
	}

	/* Change to play state */
	TE_REG_SetUploadPause(up->idx, false);

	up->state = PVR_UP_STATE_PLAY;

	return 0;
}

static int up_release(struct pvr_up *up)
{
	if (up->state > PVR_UP_STATE_READY)
		up_stop(up);

	up->state = PVR_UP_STATE_IDLE;

	return 0;
}

static void up_close(struct pvr_up *up)
{
	up_release(up);
	up->state = PVR_UP_STATE_FREE;
}

/**
 * pvr_up_open - open pvr upload device
 * @idx: pvr upload device index or negative value to alloc any free device
 *
 * Return: struct pvr_up handle on success, or ERR_PTR on error.
 */
struct pvr_up *pvr_up_open(struct pvr_device *dev, int idx)
{
	return up_open(dev, idx);
}

/**
 * pvr_up_get_index - get pvr upload device index
 */
int pvr_up_get_index(struct pvr_up *up)
{
	return up->idx;
}

/**
 * pvr_up_init - Initialize pvr upload module
 * @buf: allocated h/w buffer
 * @pkt_len: 188 or 192
 * @dest: upload destination to prevent buffer overflow
 *
 * Return: 0 on success, or -EBUSY if state is not valid or -EINVAL
 */
int pvr_up_init(struct pvr_up *up, struct te_hwbuf *buf, u8 pkt_len,
		enum lx_pvr_up_dest dest)
{
	int ret;

	mutex_lock(&up->mutex);
	ret = up_init(up, buf, pkt_len, dest);
	mutex_unlock(&up->mutex);

	return ret;
}

int pvr_up_start(struct pvr_up *up)
{
	int ret;

	mutex_lock(&up->mutex);
	ret = up_start(up);
	mutex_unlock(&up->mutex);

	return ret;
}

int pvr_up_reset(struct pvr_up *up)
{
	int ret;

	mutex_lock(&up->mutex);
	ret = up_reset(up);
	mutex_unlock(&up->mutex);

	return ret;
}

int pvr_up_pause(struct pvr_up *up)
{
	int ret;

	mutex_lock(&up->mutex);
	ret = up_pause(up);
	mutex_unlock(&up->mutex);

	return ret;
}

int pvr_up_resume(struct pvr_up *up)
{
	int ret;

	mutex_lock(&up->mutex);
	ret = up_resume(up);
	mutex_unlock(&up->mutex);

	return ret;
}

int pvr_up_set_mode(struct pvr_up *up, enum lx_pvr_up_mode mode)
{
	int ret;

	mutex_lock(&up->mutex);
	ret = up_set_mode(up, mode);
	mutex_unlock(&up->mutex);

	return ret;
}

int pvr_up_set_tlv(struct pvr_up *up, bool enable)
{
	int ret;

	mutex_lock(&up->mutex);
	ret = up_set_tlv(up, enable);
	mutex_unlock(&up->mutex);

	return ret;
}

/**
 * pvr_up_set_speed - Set upload speed for tick mode
 * @speed: bytes/sec
 *
 */
int pvr_up_set_speed(struct pvr_up *up, u32 speed)
{
	int ret;

	mutex_lock(&up->mutex);
	ret = up_set_speed(up, speed);
	mutex_unlock(&up->mutex);

	return ret;
}

int pvr_up_stop(struct pvr_up *up)
{
	int ret;

	mutex_lock(&up->mutex);
	ret = up_stop(up);
	mutex_unlock(&up->mutex);

	return ret;
}

void pvr_up_close(struct pvr_up *up)
{
	mutex_lock(&up->mutex);
	up_close(up);
	mutex_unlock(&up->mutex);
}

static int pm_suspend(struct pvr_up *up)
{
	/*
	   up_stop.
	   In order to resume upload, do not change upload state.
	 */
	if (up->state != PVR_UP_STATE_IDLE) {
		TE_REG_SetUploadIntrEnable(up->idx, UPLOAD_INTR_EMPTY, false);
		TE_REG_SetUploadEnable(up->idx, false);
	}

	return 0;
}

static int pm_resume(struct pvr_up *up)
{
	u32 state, mode;
/*
	If upload state is idle, there is nothing to resume.
	Consider the case of "up_init -> Suspend & Resume -> up_start"
*/
	if (up->state < PVR_UP_STATE_READY)
		return 0;

	if (up->state == PVR_UP_STATE_READY) {
		up_init(up, up->hbuf, up->pkt_len, up->dest);
		return 0;
	}

	/*     backup configurations */
	state = up->state;
	mode = up->mode;

	/*      up_init, up_start work when state is IDLE */
	up->state = PVR_UP_STATE_IDLE;

	up_init(up, up->hbuf, up->pkt_len, up->dest);
	up_start(up);

	if (mode != LX_PVR_UPMODE_NORMAL)	//trick or slow
		up_set_mode(up, mode);

	if (state == PVR_UP_STATE_PAUSE)
		up_pause(up);

	return 0;
}

static void debug_show_status(struct pvr_device *dev, struct seq_file *m)
{
	int i;

	seq_printf(m, "UPLOAD\n");
	for (i = 0; i < dev->num_up; i++) {
		struct pvr_up *up = &dev->up[i];

		mutex_lock(&up->mutex);
		seq_printf(m, " %d state : %s\n", i, state_str(up->state));
		if (up->state > PVR_UP_STATE_READY) {
			seq_printf(m, "   range(0x%08x--0x%08x)\n",
				   (u32)te_hwbuf_addr(up->hbuf),
				   (u32)te_hwbuf_eaddr(up->hbuf));
			seq_printf(m, "   wptr:0x%08x, rptr:0x%08x\n",
				   (u32)te_hwbuf_wptr(up->hbuf),
				   (u32)te_hwbuf_rptr(up->hbuf));
			seq_printf(m, "   used:%d, total:%d\n",
				   te_hwbuf_avail_size(up->hbuf),
				   te_hwbuf_size(up->hbuf));
		}
		mutex_unlock(&up->mutex);
	}
	seq_printf(m, "\n");
}

static void init_debug(struct pvr_device *dev)
{
	pvr_debug_register_status_show(dev, PVR_DEBUG_STATUS_UP_DEV,
				       debug_show_status);
}

static int up_write_data(u8 *data, int size)
{
	u8 *msg = vmalloc(size + 1);
	int rc;

	if (!msg)
		return -ENOMEM;

	msg[0] = IPC_WRITE_DVR_UP;
	memcpy(&msg[1], data, size);

	rc = te_ipc_write_data(msg, size + 1);
	vfree(msg);

	return rc;
}

static int ioc_up_init(struct pvr_up_fh *fh, LX_PVR_UP_CFG_T *cfg)
{
	struct pvr_up *up = fh->dev;
	struct te_hwbuf *hbuf = &fh->hbuf;

	if (up_write_data(cfg->up_cert, 32)) {
		log_error("fail to write data");
		up->up_cert_passed = false;
		return -EPERM;
	}

	up->up_cert_passed = true;

	te_hwbuf_init(hbuf, cfg->addr, cfg->size, 0, TE_BUF_FLAG_UPLOAD_MODULE);

	return up_init(up, hbuf, cfg->pkt_len, cfg->dest);
}

static int ioc_up_control(struct pvr_up_fh *fh, LX_PVR_UP_CONTROL_T *ctl)
{
	int ret;
	struct pvr_up *up = fh->dev;

	switch (ctl->type) {
	case LX_PVR_UP_START:
		ret = up_start(up);
		break;

	case LX_PVR_UP_STOP:
		ret = up_stop(up);
		break;

	case LX_PVR_UP_RESET:	// Restart purpose
		ret = up_reset(up);
		break;

	case LX_PVR_UP_PAUSE:
		ret = up_pause(up);
		break;

	case LX_PVR_UP_RESUME:
		ret = up_resume(up);
		break;

	case LX_PVR_UP_SET_MODE:
		ret = up_set_mode(up, ctl->value);
		break;

	case LV_PVR_UP_SET_SPEED:
		ret = up_set_speed(up, ctl->value);
		break;

	case LX_PVR_UP_SET_TLV:
		ret = up_set_tlv(up, ctl->value);
		break;

	default:
		log_error("invalid upload control(%d)\n", ctl->type);
		ret = -EINVAL;
		break;
	}

	return ret;
}

/**
 * Set the new write pointers for upload buffer
 *
 * @def PVR_IOC_UP_SET_WRITE_PTR
 * @param	dev 	[in	] dev handle for pvr channel
 * @return	if succeeded - 0, else - errno.
 */
static int ioc_up_set_wptr(struct pvr_up_fh *fh, struct lx_pvr_buf_ptr *param)
{
	int ret;
	u32 idx;
	unsigned long flags;
	struct pvr_up *up = fh->dev;

	TRACE_EX_PARAM_ENTER(up, "wptr=0x%08x", param->wptr);

	if (up->state < PVR_UP_STATE_PLAY) {
		log_warning("pvr(%d) upload state(%s) is not play\n",
			    up->idx, state_str(up->state));
		return -EINVAL;
	}

	ret = te_hwbuf_paddr_to_idx(up->hbuf, param->wptr, &idx);
	if (ret) {
		log_error("invalid wptr(0x%x)", param->wptr);
		return ret;
	}

	/* wptr have to be aligned to 16bytes and packet length.
	 * packet length 192 is already aligned to 16 but 188 is not aligned.
	 */
	if (up->pkt_len == 188)
		idx -= (idx % (4 * 188));
	else
		idx -= (idx % 192);

	te_hwbuf_set_widx(up->hbuf, idx);

	spin_lock_irqsave(&up->spinlock, flags);
	if (up->empty)
		up->empty = false;	// clear value

	//Clear the state back to normal if no error
//	buf->status = LX_PVR_BUF_STAT_READY;
	spin_unlock_irqrestore(&up->spinlock, flags);

	return 0;
}

/**
 * Get the buffer write pointer for upload buffer
 *
 * @def PVR_IOC_UP_GET_BUF_INFO
 * @param	dev 	[in	] dev handle for pvr channel
 * @param	info 	[out] information
 * @return	if succeeded - 0, else - errno.
 */
static int ioc_up_get_buffer_info(struct pvr_up_fh *fh,
				  struct lx_pvr_buf_info *info)
{
	struct pvr_up *up = fh->dev;

	if (up->state < PVR_UP_STATE_PLAY) {
		log_warning("pvr(%d) upload state(%s) is not play\n",
			    up->idx, state_str(up->state));
		return -EINVAL;
	}

	info->ptr.rptr = te_hwbuf_rptr(up->hbuf);
	info->ptr.wptr = te_hwbuf_wptr(up->hbuf);
	info->status = 0;	// TODO: CHECK IT

	TRACE_EX_PARAM_EXIT(up, "wptr=0x%08x,rpt=0x%08x",
			    info->ptr.wptr, info->ptr.rptr);
	return 0;
}

static int ioctl_device(void *priv, unsigned int cmd, void *arg)
{
	int ret;
	struct pvr_fh *__fh = priv;
	struct pvr_up_fh *fh = &__fh->up;
	struct pvr_up *up = fh->dev;

	if (!up)
		return -EINVAL;

	mutex_lock(&up->mutex);

	if (cmd != PVR_IOC_UP_INIT && !up->up_cert_passed) {
		log_error("init cert failed");
		mutex_unlock(&up->mutex);
		return -EPERM;
	}

	switch (cmd) {
	case PVR_IOC_UP_INIT:
		ret = ioc_up_init(fh, arg);
		break;

	case PVR_IOC_UP_CONTROL:
		ret = ioc_up_control(fh, arg);
		break;

	case PVR_IOC_UP_SET_WRITE_PTR:
		ret = ioc_up_set_wptr(fh, arg);
		break;

	case PVR_IOC_UP_GET_BUF_INFO:
		ret = ioc_up_get_buffer_info(fh, arg);
		break;

	default:
		log_error("invalid command[0x%08x]. magic=0x%02X, num=%d",
			  cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));
		ret = -ENOTTY;
		break;
	}
	mutex_unlock(&up->mutex);

	return ret;
}

static int open_device(struct pvr_fh *fh)
{
	struct pvr_up *up;

	up = up_open(fh->dev, fh->idx);
	if (IS_ERR(up)) {
		log_error("can't open upload device(%d)\n", fh->idx);
		return PTR_ERR(up);
	}
	fh->up.dev = up;

	return 0;
}

static void close_device(struct pvr_fh *fh)
{
	if (fh->up.dev)
		up_close(fh->up.dev);
}

static struct pvr_node up_node = {
	.open = open_device,
	.close = close_device,
	.ioctl = ioctl_device,
};

static int init_device(struct pvr_device *dev)
{
	int i;

	dev->node[PVR_DEV_TYPE_UP] = &up_node;

	for (i = 0; i < dev->num_up; i++) {
		struct pvr_up *d = &dev->up[i];

		d->idx = i;
		d->state = PVR_UP_STATE_FREE;
		mutex_init(&d->mutex);
		spin_lock_init(&d->spinlock);
		INIT_DELAYED_WORK(&d->work, up_work);

		init_hw(d);
	}
	init_debug(dev);

	return 0;
}

static void release_device(struct pvr_device *dev)
{
	int i;

	for (i = 0; i < dev->num_up; i++) {
		struct pvr_up *up = &dev->up[i];
		up_close(up);
	}
}

static int suspend_device(struct pvr_device *dev)
{
	int i;

	for (i = 0; i < dev->num_up; i++) {
		struct pvr_up *up = &dev->up[i];

		if (up->state == PVR_UP_STATE_FREE)
			continue;

		pm_suspend(up);
	}

	return 0;
}

static int resume_device(struct pvr_device *dev)
{
	int i;

	for (i = 0; i < dev->num_up; i++) {
		struct pvr_up *up = &dev->up[i];

		init_hw(up);

		if (up->state == PVR_UP_STATE_FREE)
			continue;

		pm_resume(up);
	}

	return 0;
}

const struct pvr_sub_driver pvr_up_driver = {
	.name = "pvr_up",

	.init = init_device,
	.release = release_device,
	.suspend = suspend_device,
	.resume = resume_device,
};
