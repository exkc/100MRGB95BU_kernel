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
 *  @author	Kyungseok Hyun ( ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2015-01-27
 *  @note		Additional information.
 */

#if !CONFIG_LX_BOARD_FPGA
//#define LOAD_MCU_BIN
#endif

#include <lg1k/te/mcu.h>
#include <lg1k/te/ipc.h>
#include <lg1k/te/demod.h>

#include "te_impl.h"

#include "ipc/ipc.h"
#include "ipc/ipc_mcu.h"
#ifdef CONFIG_TE_MCU_VERIFY
#include "te_mcu_verify.h"
#endif

#ifdef LOAD_MCU_BIN
//#include "m16/te/fw/mcu0_b0_bin.h"
//#include "m16/te/fw/mcu1_bin.h"
#endif

#if CONFIG_LX_BOARD_FPGA
#define MCU_INIT_MAX_TIMEOUT		(1000*3)	/* 1000ms */
#define MCU_STATUS_CHECK_INTERVAL	(1000*3)
#else
#define MCU_INIT_MAX_TIMEOUT		1000	/* 1000ms */
#define MCU_STATUS_CHECK_INTERVAL	1000
#endif

#define MCU_RECOVERY_CHECK_COUNT	3

#define MCU_REG_OFFSET_PROC_CTRL	0x000
#define MCU_PROC_RUN_STALL_MASK		(0x1 <<  0)
#define MCU_PROC_DEBUG_MASK		(0x1 <<  2)
#define MCU_PROC_SW_RESET_MASK		(0x1 << 28)
#define MCU_PROC_HALT_MASK \
	(MCU_PROC_SW_RESET_MASK | MCU_PROC_RUN_STALL_MASK)

#ifdef TE_EMULATOR
#define reg_write(addr, val) \
	TE_EMUL_RegWrite((u32)(addr), val)
#define reg_read(addr) \
	({u32 _v_; TE_EMUL_RegRead((u32)(addr), &_v_); _v_;})
#else
#define reg_write(addr, val)		__raw_writel(val , addr)
#define reg_read(addr)			__raw_readl(addr)
#endif

#define mcu_reg_write(mcu, ofs,val)	reg_write((mcu)->reg_base+(ofs),val)
#define mcu_reg_read(mcu, ofs)		reg_read((mcu)->reg_base+(ofs))

struct mcu_config {
	u32 rom_size;		/* memory size for mcu f/w execution @ 0x50000000 */

	u8 num_func;
	enum te_mcu_func_type *funcs;
};

struct mcu_stats {
	u32 ipc_timeout_count;
	u32 status_check_error_count;	/* to reset mcu in abnormal case */

	u32 recovery_count;
	u32 ipc_total_errors;
};

struct mcu_status {
	u8 ready;

	u32 running_time;	/* seconds */
	u32 status_check_error_count;
	u32 recovery_count;
};

struct demod_ctrl {
	struct mutex mutex;
	bool enable; //only used for integrated demod case (M23)
	int (*suspend_func)(void *);
	void *suspend_arg;
	int (*resume_func)(void *);
	void *resume_arg;
};

struct te_dev_mcu {
	u8 num;
	char name[16];
	volatile bool ready;
	volatile bool stall;
	bool get_clk;
	u64 load_time;
	struct te_device *tdev;

	void *fw_binary;
	u32 fw_size;

	const struct mcu_config *cfg;
	struct te_mem_ctx *mem_ctx;

	u8 __iomem *reg_base;		/* ioremapped mcu reg base */
	te_phys_addr_t rom_addr;	/* physical address mapped @ MCU:0x50000000 */

	struct mcu_stats stats;

	struct ipc *ipc;

	struct list_head rcallback_head;
	struct mutex rcallback_mutex;

	struct mutex mutex;
	struct te_timer *status_check_timer;
	u8 abnormal_recovery_enable;
	bool status_timeout;

	struct demod_ctrl demod;
	struct work_struct init_done_work;
	struct te_debug_dir *debug_dir;
};

struct te_mcu_rcallback {
	enum te_mcu_func_type type;
	struct te_dev_mcu *mcu;
	int (*pre_func)(void *);
	int (*post_func)(void *);
	void *arg;
	struct list_head list;
};

/* below static te_device is used for demod extern apis
 * just reference the structure for access mcu struct
 */
static struct te_device *_tdev;

static enum te_mcu_func_type mcu0_funcs[] = {
	TE_MCU_FUNC_TYPE_IO,
	TE_MCU_FUNC_TYPE_ATSC3,
	TE_MCU_FUNC_TYPE_CIPLUS,
	TE_MCU_FUNC_TYPE_DSC,
	TE_MCU_FUNC_TYPE_ARIB2
};

static enum te_mcu_func_type y18_mcu0_funcs[] = {
	TE_MCU_FUNC_TYPE_IO,
	TE_MCU_FUNC_TYPE_ATSC3,
	TE_MCU_FUNC_TYPE_CIPLUS,
	TE_MCU_FUNC_TYPE_DSC
};

static enum te_mcu_func_type mcu1_funcs[] = {
	TE_MCU_FUNC_TYPE_FILTER
};

static enum te_mcu_func_type uni_mcu_funcs[] = {
	TE_MCU_FUNC_TYPE_IO,
	TE_MCU_FUNC_TYPE_ATSC3,
	TE_MCU_FUNC_TYPE_FILTER,
	TE_MCU_FUNC_TYPE_CIPLUS,
	TE_MCU_FUNC_TYPE_DEMOD,
	TE_MCU_FUNC_TYPE_DSC,
	TE_MCU_FUNC_TYPE_ARIB2
};

static const struct mcu_config mcu0_config_o18 = {
	.rom_size = 0x60000,	/* 384KB : load & execute at 0x50000000 */

	.num_func = ARRAY_SIZE(y18_mcu0_funcs),
	.funcs = y18_mcu0_funcs,
};

static const struct mcu_config mcu0_config_normal = {
	.rom_size = 0x60000,	/* 384KB : load & execute at 0x50000000 */

	.num_func = ARRAY_SIZE(mcu0_funcs),
	.funcs = mcu0_funcs,
};

static const struct mcu_config mcu1_config_normal = {
	.rom_size = 0x60000,	/* 384KB */

	.num_func = ARRAY_SIZE(mcu1_funcs),
	.funcs = mcu1_funcs,
};

/* unified mcu */
static const struct mcu_config uni_mcu_normal = {
	.rom_size = 0x60000,	/* 384KB : load & execute at 0x50000000 */

	.num_func = ARRAY_SIZE(uni_mcu_funcs),
	.funcs = uni_mcu_funcs,
};

static inline struct te_device *get_te_device(void)
{
	return _tdev;
}

static const struct mcu_config *get_config(int num)
{
	struct te_config *te_cfg = te_get_config();
	const struct mcu_config *cfg = NULL;

	if (te_cfg->num_mcu == 1) {
		if (num == 0) {
			cfg = &uni_mcu_normal;
		}
	} else {
		if (num == 0) {
			if (lx_chip() == LX_CHIP_O18)	//y18 (legacy)
				cfg = &mcu0_config_o18;
			else	// MCU0 M16P3 ~
				cfg = &mcu0_config_normal;
		} else if (num == 1) { //MCU1
			cfg = &mcu1_config_normal;
		}
	}

	return cfg;
}

static int load_mcu_fw(struct te_dev_mcu *mcu, const void *data, u32 size)
{
	void *fw_addr;
	u32 proc_ctrl;

	if (size > mcu->cfg->rom_size) {
		log_error("f/w size(%d) over rom size(%d)\n", size,
			  mcu->cfg->rom_size);
		return -EINVAL;
	}

	fw_addr = te_vmap(mcu->rom_addr, size, false);
	if (!fw_addr) {
		log_error("vmap_phys fail\n");
		return -ENOMEM;
	}

	log_mcu("Load %s F/W(%dbytes)\n", mcu->name, size);
	mcu->stats.status_check_error_count = 0;

	/* halt */
	mcu_reg_write(mcu, MCU_REG_OFFSET_PROC_CTRL, MCU_PROC_HALT_MASK);

	/* set rom base */
	mcu_reg_write(mcu, MCU_REG_OFFSET_SROM_OFFSET, mcu->rom_addr);

	memcpy(fw_addr, data, size);
	vunmap_phys(fw_addr);

	wmb();			// use wmb before mcu is awoken

	mcu->load_time = te_get_ms_tick();
	mcu->ready = true;

	/* reset */
	proc_ctrl = MCU_PROC_DEBUG_MASK;
	mcu_reg_write(mcu, MCU_REG_OFFSET_PROC_CTRL, proc_ctrl);
	mcu->stall = false;

	return 0;
}

static int wait_for_mcu_init(struct te_device *dev, u32 timeout)
{
	int i, ret, not_ready;
	unsigned long timeout_jiffies;
	struct te_dev_mcu *mcu;

	timeout_jiffies = jiffies + msecs_to_jiffies(timeout);
	while (time_is_after_jiffies(timeout_jiffies)) {
		not_ready = 0;
		for (i = 0; i < dev->num_mcu; i++) {
			mcu = dev->mcu[i];
			if (mcu->ready && !mcu->stall) {
				ret = _TE_IPC_CheckReady(mcu->ipc);
				if (ret) {
					not_ready = 1;
					break;
				}
			}
		}

		if (!not_ready)
			return 0;

		msleep(1);
	}

	return -ETIME;
}

static void mcu_halt(struct te_dev_mcu *mcu)
{
	if (!mcu->ready)
		return;

	_TE_IPC_Disable(mcu->ipc);

	/* halt mcu */
	mcu_reg_write(mcu, MCU_REG_OFFSET_PROC_CTRL, MCU_PROC_HALT_MASK);

	mcu->ready = false;
}

static void mcu_stall(struct te_dev_mcu *mcu, bool stall)
{
	struct te_config *cfg = te_get_config();

	if (!mcu->ready)
		return;

	if (!cfg->reg_clock_gate) {
		mcu->stall = stall; // assume mcu is stalled (actually not)
		return;
	}

	if (stall) {
		/* stall mcu */
		mcu_reg_write(mcu, MCU_REG_OFFSET_PROC_CTRL,
			      MCU_PROC_DEBUG_MASK | MCU_PROC_RUN_STALL_MASK);
	} else {
		/* recover mcu */
		mcu_reg_write(mcu, MCU_REG_OFFSET_PROC_CTRL,
			      MCU_PROC_DEBUG_MASK);
	}

	mcu->stall = stall;
}


static int mcu_reset(struct te_dev_mcu *mcu)
{
	_TE_IPC_Disable(mcu->ipc);

	/* halt mcu */
	mcu->ready = false;
	mcu_reg_write(mcu, MCU_REG_OFFSET_PROC_CTRL, MCU_PROC_HALT_MASK);

	_TE_IPC_Enable(mcu->ipc);

	return 0;
}

static int load_mcu_binary(struct te_dev_mcu *mcu, const void *data, u32 size)
{
	int ret;

	if (!mcu->get_clk) {
		te_clockgate_acquire_clock(mcu->tdev, TE_DEVICE_TYPE_MCU);
		mcu->get_clk = true;
	}

	if (mcu->fw_binary) {
		vfree(mcu->fw_binary);
		mcu->fw_binary = NULL;
		mcu->fw_size = 0;
	}

	ret = mcu_reset(mcu);
	CHECK_ERROR(ret, return ret, "Error in mcu_reset");

	ret = load_mcu_fw(mcu, data, size);
	CHECK_ERROR(ret, return ret, "Error in load_mcu_fw");

	/* copy mcu binary to recover in resume or recovery mode */
	mcu->fw_binary = vmalloc(size);
	CHECK_ERROR(!mcu->fw_binary, return -ENOMEM, "can't alloc memory");

	memcpy(mcu->fw_binary, data, size);
	mcu->fw_size = size;

	return 0;
}

static int get_mcu_binary(struct te_dev_mcu *mcu, const void **data, u32 *size)
{
	*data = NULL;
	*size = 0;

#ifdef LOAD_MCU_BIN
	// TODO: add binary as below
#if 0
	if (mcu->num == 0) {
		if (lx_chip() == LX_CHIP_M16) {
			*data = mcu0_b0_bin;
			*size = sizeof(mcu0_b0_bin);
		}
	} else {
		if (lx_chip() == LX_CHIP_M16) {
			*data = mcu1_bin;
			*size = sizeof(mcu1_bin);
		}
	}
#endif
#endif

	return 0;
}

static int mcu_recovery(struct te_dev_mcu *mcu)
{
	int ret;

	if (mcu->ready) {
		if (!mcu->get_clk) {
			struct te_device *tdev = mcu->tdev;

			te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_MCU);
			mcu->get_clk = true;
		}

		ret = mcu_reset(mcu);
		CHECK_ERROR(ret, return ret, "Error in mcu_reset");

		if (mcu->fw_binary) {
			ret = load_mcu_fw(mcu, mcu->fw_binary, mcu->fw_size);
			CHECK_ERROR(ret, return ret, "Error in load_mcu_fw");
		}
	}

	return 0;
}

#if !CONFIG_LX_BOARD_FPGA
static bool check_abnormal_status(struct te_dev_mcu *mcu)
{
	int ret;
	struct ipc *ipc = mcu->ipc;

	ret = _TE_IPC_CheckReady(ipc);
	if (!ret) {
		ret = _TE_IPC_CheckAlive(ipc);
		if (!ret) {
			log_debug("mcu[%d] is alive\n", mcu->num);
			mcu->stats.status_check_error_count = 0;
		} else {
			log_mcu("mcu[%d] not alive - error_count=%d\n",
				mcu->num, mcu->stats.status_check_error_count);
			mcu->stats.status_check_error_count++;
			mcu->stats.ipc_total_errors++;
		}
	} else {
		u32 elapsed = (u32)(te_get_ms_tick() - mcu->load_time);
		if (elapsed > MCU_INIT_MAX_TIMEOUT) {
			log_mcu("mcu[%d] not ready in %dms\n", mcu->num,
				elapsed);
			mcu->stats.status_check_error_count++;
		}
	}

	if (mcu->abnormal_recovery_enable &&
	    mcu->stats.status_check_error_count >=
	    mcu->abnormal_recovery_enable) {
		return true;	/* recovery mcu f/w */
	}

	return false;
}
#endif

static void recovery_pre_callback(struct te_dev_mcu *mcu)
{
	struct te_mcu_rcallback *c;

	mutex_lock(&mcu->rcallback_mutex);
	list_for_each_entry(c, &mcu->rcallback_head, list) {
		if (c->pre_func)
			c->pre_func(c->arg);
	}
	mutex_unlock(&mcu->rcallback_mutex);
}

static void recovery_post_callback(struct te_dev_mcu *mcu)
{
	struct te_mcu_rcallback *c;

	mutex_lock(&mcu->rcallback_mutex);
	list_for_each_entry_reverse(c, &mcu->rcallback_head, list) {
		if (c->post_func)
			c->post_func(c->arg);
	}
	mutex_unlock(&mcu->rcallback_mutex);
}

// mcu initialization - disable demod if it was already trigerred
static void disable_demod(struct te_dev_mcu *mcu)
{
	if (mcu->demod.enable) {
		struct te_device *tdev = mcu->tdev;

		log_warning("Demod enabled; disabling");
		te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_DEMOD);
		mcu->demod.enable = false;
	}
}

#if !CONFIG_LX_BOARD_FPGA
static void status_check_handler(void *arg)
{
	struct te_dev_mcu *mcu = arg;
	bool recover = false;

//      LOG_DEBUG("mcu[%d] status check work\n", mcu->num);

	mutex_lock(&mcu->mutex);

	if (mcu->ready && !mcu->stall)
		recover = check_abnormal_status(mcu);
	if (recover)
		mcu->status_timeout = true;

	mutex_unlock(&mcu->mutex);

	if (recover) {
		log_mcu("recover mcu[%d] in abnormal status\n", mcu->num);

		recovery_pre_callback(mcu);

		mutex_lock(&mcu->mutex);
		disable_demod(mcu);
		mcu_recovery(mcu);
		mcu->status_timeout = false;
		mutex_unlock(&mcu->mutex);

		recovery_post_callback(mcu);

		mcu->stats.recovery_count++;
	}
}
#endif

static int get_status(struct te_dev_mcu *mcu, struct mcu_status *status)
{
	CHECK_NULL_PARAM(status);

	memset(status, 0, sizeof(*status));

	mutex_lock(&mcu->mutex);
	if (mcu->ready && !mcu->stall) {
		u64 running_time;

		status->ready = true;

		running_time = te_get_ms_tick() - mcu->load_time;
		do_div(running_time, 1000);
		status->running_time = running_time;

		status->status_check_error_count = mcu->stats.ipc_total_errors;
		status->recovery_count = mcu->stats.recovery_count;
	}
	mutex_unlock(&mcu->mutex);

	return 0;
}

static int fwload_from_binary(struct te_dev_mcu *mcu, const void *data,
			      u32 size)
{
	int ret;

	recovery_pre_callback(mcu);

	mutex_lock(&mcu->mutex);
	disable_demod(mcu);
	ret = load_mcu_binary(mcu, data, size);
	mutex_unlock(&mcu->mutex);

	recovery_post_callback(mcu);

	return ret;
}

static int fwload_from_file2(struct te_dev_mcu *mcu, const char *name)
{
	int ret, size;
	void *data = NULL;
	int siglen = 0;

	size = te_read_file_from_path(name, &data, 512 * 1024);
	if (size <= 0) {
		log_error("Can't read firmware from '%s'\n", name);
		return size;
	}

#ifdef CONFIG_TE_MCU_VERIFY
	siglen = MCU_SIGNATURE_LEN;
	ret = te_mcu_verify_mcu_binary(data, size);
	if (ret) {
		log_error("verify failed - %d", ret);
		vfree(data);
		return ret;
	}
#endif

	log_noti("Loading %s F/W(%dbytes)...\n", mcu->name, size - siglen);
	ret = fwload_from_binary(mcu, data, size - siglen);
	log_noti("%s\n", ret == 0 ? "SUCCESS" : "FAILED");

	vfree(data);

	return ret;
}

static int fwload_from_file(struct te_dev_mcu *mcu, const char *name)
{
#if 1
	int ret, size;
	void *data = NULL;

	size = te_read_file_from_path(name, &data, 512 * 1024);
	if (size <= 0) {
		log_error("Can't read firmware from '%s'\n", name);
		return size;
	}

	log_noti("Loading %s F/W(%dbytes)...\n", mcu->name, size);
	ret = fwload_from_binary(mcu, data, size);
	log_noti("%s\n", ret == 0 ? "SUCCESS" : "FAILED");

	vfree(data);

	return ret;
#else
	struct file *f;
	mm_segment_t fs;
	int ret, size;
	void *data;

	f = filp_open(name, O_RDONLY, 0644);
	if (IS_ERR(f)) {
		log_error("can't open file '%s'\n", name);
		return PTR_ERR(f);
	}

	fs = get_fs();
	set_fs(get_ds());

	size = vfs_llseek(f, 0, SEEK_END);
	vfs_llseek(f, 0, SEEK_SET);

	data = vmalloc(size);
	if (data) {
		ssize_t len;
		loff_t pos = f->f_pos;

		log_noti("Loading %s F/W(%dbytes)...\n", mcu->name, size);
		len = vfs_read(f, data, size, &pos);
		if (len != size) {
			log_noti("can't read file(%s) - size=%d,read=%zu\n",
				 name, size, len);
			ret = -EIO;
		} else {
			ret = fwload_from_binary(mcu, data, size);
		}
		vfree(data);
		log_noti("%s\n", ret == 0 ? "SUCCESS" : "FAILED");
	} else {
		ret = -ENOMEM;
		log_error("vmalloc failed\n");
	}
	set_fs(fs);

	filp_close(f, NULL);

	return ret;
#endif
}

int te_mcu_fwload(struct te_device *dev, u8 num, const void *data, u32 size)
{
	CHECK_NULL_PARAM(data);
	CHECK_PARAM(size == 0, "size is 0");

	if (num >= dev->num_mcu) {
		log_error("invalid mcu num(%d)\n", num);
		return -EINVAL;
	}

	return fwload_from_binary(dev->mcu[num], data, size);
}

int te_mcu_stall(struct te_device *dev, u8 num, bool stall)
{
	struct te_dev_mcu *mcu;

	if (num >= dev->num_mcu) {
		log_error("invalid mcu num (%d)\n", num);
		return -EINVAL;
	}

	mcu = dev->mcu[num];

	mutex_lock(&mcu->mutex);

	if (mcu->ready) {
		mcu_stall(mcu, stall);
		log_noti("mcu%d %s", num, stall ? "stalled" : "recovered");
	}

	mutex_unlock(&mcu->mutex);
	return 0;
}

int te_mcu_get_status(struct te_device *dev, u8 num, bool *mcu_ready,
		      bool *ipc_ready, u32 *vers)
{
	struct te_dev_mcu *mcu;
	struct ipc_status s;

	CHECK_NULL_PARAM(mcu_ready);
	CHECK_NULL_PARAM(ipc_ready);
	CHECK_NULL_PARAM(vers);
	if (num >= dev->num_mcu)
		return -EINVAL;

	mcu = dev->mcu[num];

	*mcu_ready = false;
	*ipc_ready = false;
	*vers = 0;

	mutex_lock(&mcu->mutex);

	if (!mcu->ready)
		goto exit;
	*mcu_ready = true;

	if (_TE_IPC_CheckReady(mcu->ipc))
		goto exit;
	*ipc_ready = true;

	_TE_IPC_GetStatus(mcu->ipc, &s);
	*vers = s.fw_ver;

exit:
	mutex_unlock(&mcu->mutex);

	return 0;
}

static struct te_dev_mcu *get_mcu_from_func_type(struct te_device *dev,
						 enum te_mcu_func_type type)
{
	int i, j;
	struct te_dev_mcu *mcu;

	if (type >= TE_MCU_FUNC_TYPE_MAX)
		return NULL;

	for (i = 0; i < dev->num_mcu; i++) {
		mcu = dev->mcu[i];
		for (j = 0; j < mcu->cfg->num_func; j++) {
			if (mcu->cfg->funcs[j] == type)
				return mcu;
		}
	}

	return NULL;
}

struct te_mcu_rcallback *te_mcu_register_rcallback(struct te_device *dev,
						   enum te_mcu_func_type type,
						   int (*pre_func)(void *),
						   int (*post_func)(void *),
						   void *arg)
{
	struct te_dev_mcu *mcu;
	struct te_mcu_rcallback *c;
	struct te_mcu_rcallback *n;
	bool found;

	mcu = get_mcu_from_func_type(dev, type);
	CHECK_ERROR(!mcu, return NULL, "invalid type(%d)", type);

	n = kmalloc(sizeof(*n), GFP_KERNEL);
	CHECK_ERROR(!n, return NULL, "can't alloc memory");

	n->type = type;
	n->mcu = mcu;
	n->pre_func = pre_func;
	n->post_func = post_func;
	n->arg = arg;

	/* add recovery callback functions in order of type */
	mutex_lock(&mcu->rcallback_mutex);
	found = false;
	list_for_each_entry(c, &mcu->rcallback_head, list) {
		if (type < c->type) {
			list_add_tail(&n->list, &c->list);
			found = true;
			break;
		}
	}

	if (!found)
		list_add_tail(&n->list, &mcu->rcallback_head);

	mutex_unlock(&mcu->rcallback_mutex);

	return n;
}

int te_mcu_unregister_rcallback(struct te_device *dev,
				struct te_mcu_rcallback *callback)
{
	struct te_dev_mcu *mcu;
	struct te_mcu_rcallback *c;
	bool found;

	CHECK_NULL_PARAM(callback);

	mcu = callback->mcu;
	found = false;
	mutex_lock(&mcu->rcallback_mutex);
	list_for_each_entry(c, &mcu->rcallback_head, list) {
		if (c == callback) {
			list_del(&c->list);
			kfree(c);
			found = true;
			break;
		}
	}
	mutex_unlock(&mcu->rcallback_mutex);

	if (!found) {
		log_error("can't find callback(%p)\n", callback);
		return -EINVAL;
	}

	return 0;
}

/**
 * te_mcu_register_demod_rcallback - Register callback for mcu recovery
 * pre_func before mcu recovering, and post_fun for after recovering
 *
 * Return: 0 on success, -EFAULT if no device exists or fail registering
 */
int te_mcu_register_demod_rcallback(int (*pre_func)(void *),
				    int (*post_func)(void *),
				    int (*suspend_func)(void *),
				    int (*resume_func)(void *),
				    void *arg)
{
	struct te_device *tdev = get_te_device();
	struct te_mcu_rcallback *rcallback;
	struct te_dev_mcu *mcu;

	if (!tdev)
		return -ENODEV;

	mcu = get_mcu_from_func_type(tdev, TE_MCU_FUNC_TYPE_DEMOD);
	if (!mcu)
		return -ENODEV;

	rcallback = te_mcu_register_rcallback(tdev, TE_MCU_FUNC_TYPE_DEMOD,
					      pre_func, post_func, arg);
	if (!rcallback) {
		log_error("fail to register demod rcallback");
		return -EFAULT;
	}

	mutex_lock(&mcu->demod.mutex);

	mcu->demod.suspend_func = suspend_func;
	mcu->demod.suspend_arg = arg;
	mcu->demod.resume_func = resume_func;
	mcu->demod.resume_arg = arg;

	mutex_unlock(&mcu->demod.mutex);
	return 0;
}
EXPORT_SYMBOL(te_mcu_register_demod_rcallback);

/**
 * te_mcu_get_demod_status - Get MCU status for demod usage
 * see enum te_mcu_status in demod.h for detailed information
 *
 * Return: 0 on success, -EFAULT if status is NULL, -ENODEV if no device exists
 */
int te_mcu_get_demod_status(enum te_mcu_status *status)
{
	struct te_device *tdev = get_te_device();
	struct te_dev_mcu *mcu;
	int rc;

	if (!status)
		return -EFAULT;
	*status = TE_MCU_STATUS_NOT_READY;

	if (!tdev)
		return -ENODEV;

	mcu = get_mcu_from_func_type(tdev, TE_MCU_FUNC_TYPE_DEMOD);
	if (!mcu)
		return -ENODEV;

	mutex_lock(&mcu->mutex);

	if (mcu->stall) // mcu is gated
		goto fail;

	rc = _TE_IPC_CheckReady(mcu->ipc);
	if (rc)
		goto fail;

	if (!mcu->status_timeout)
		*status = TE_MCU_STATUS_READY;
	else
		*status = TE_MCU_STATUS_TIMEOUT;

	mutex_unlock(&mcu->mutex);
	return 0;

fail:
	mutex_unlock(&mcu->mutex);
	return 0;
}
EXPORT_SYMBOL(te_mcu_get_demod_status);

bool te_mcu_get_demod_ready(void)
{
	int rc;
	enum te_mcu_status status;

	rc = te_mcu_get_demod_status(&status);
	if (rc)
		return false;

	if (status == TE_MCU_STATUS_READY)
		return true;
	else
		return false;
}
EXPORT_SYMBOL(te_mcu_get_demod_ready);

/**
 * te_mcu_set_demod_sram_addr - Register sram slot for demod usage
 *
 * Return: 0 on success, -EINVAL for parameter error, -EFAULT if no device
 * exists
 */
int te_mcu_set_demod_sram_addr(u32 addr, u32 size)
{
#define DEMOD_SRAM_SLOT_NUM 2
	struct te_device *tdev = get_te_device();
	struct te_dev_mcu *mcu;
	int ret;

	if(!addr || !size) {
		log_error("invalid addr:0x%08x size:0x%08x", addr, size);
		return -EINVAL;
	}

	if (!tdev)
		return -EFAULT;

	mcu = get_mcu_from_func_type(tdev, TE_MCU_FUNC_TYPE_DEMOD);
	if (!mcu) {
		log_error("demod func is not registered");
		return -ENODEV;
	}

	mutex_lock(&mcu->mutex);

	if (mcu->stall) {
		log_error("mcu is stalled (gated)");
		ret = -EFAULT;
		goto fail;
	}

	ret = te_ipc_set_predef_addr(mcu->ipc, DEMOD_SRAM_SLOT_NUM, addr, size);
	if (ret) {
		log_error("fail to set addr:0x%08x size:0x%08x - %d", addr,
			  size, ret);
		goto fail;
	}

	mutex_unlock(&mcu->mutex);
	log_noti("set demod_mcu addr:0x%08x size:0x%08x", addr, size);
	return 0;

fail:
	mutex_unlock(&mcu->mutex);
	return ret;

}
EXPORT_SYMBOL(te_mcu_set_demod_sram_addr);

int te_mcu_enable_demod(bool en)
{
	struct te_device *tdev = get_te_device();
	struct te_dev_mcu *mcu;
	int rc;

	if (!tdev)
		return -EFAULT;

	mcu = get_mcu_from_func_type(tdev, TE_MCU_FUNC_TYPE_DEMOD);
	if (!mcu)
		return -ENODEV;

	log_noti("%s - %s", __func__, (en) ? "true" : "false");

	mutex_lock(&mcu->demod.mutex);

	if (en) {
		if (mcu->demod.enable) {
			log_error("already enabled");
			mutex_unlock(&mcu->demod.mutex);
			return -EBUSY;
		}

		te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_DEMOD);

		rc = te_ipc_enable_demod(en);
		CHECK_ERROR(rc, goto enable_fail, "enable failed - %d", rc);

		mcu->demod.enable = true;
	} else {
		if (!mcu->demod.enable) {
			log_warning("already disabled");
			mutex_unlock(&mcu->demod.mutex);
			return 0;
		}

		rc = te_ipc_enable_demod(en);
		CHECK_ERROR(rc, goto disable_fail, "disable failed - %d", rc);

		mcu->demod.enable = false;
		te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_DEMOD);
	}

	mutex_unlock(&mcu->demod.mutex);
	return 0;

enable_fail:
	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_DEMOD);
	mutex_unlock(&mcu->demod.mutex);
	return rc;

disable_fail:
	mutex_unlock(&mcu->demod.mutex);
	return rc;
}
EXPORT_SYMBOL(te_mcu_enable_demod);

/*----------------------------------------------------------------------------------------
 * DEBUG FUNCTIONS
 *---------------------------------------------------------------------------------------*/
enum {
	DEBUG_ID_VERSION = 0,
	DEBUG_ID_FWLOAD,
	DEBUG_ID_FWLOAD2,
	DEBUG_ID_REG_DUMP,
	DEBUG_ID_JTAG,
	DEBUG_ID_UART,
	DEBUG_ID_CONSOLE,
	DEBUG_ID_LOGMASK,
	DEBUG_ID_RECOVERY,
	DEBUG_ID_REGDUMP,
	DEBUG_ID_STATUS,
	DEBUG_ID_HALT,
	DEBUG_ID_STALL,
	DEBUG_ID_MAIN_PERF,
	DEBUG_ID_DEMOD_ENABLE,
};

#define dprintf(fmt, args...)	seq_printf(m, fmt, ##args)

#define LOG_MODULE_NAME(a,b)	[IPC_LOG_MODULE_##a] = {#a,b}

static const struct {
	const char *name;
	char c;
} log_module[IPC_LOG_MODULE_MAX] = {
	LOG_MODULE_NAME(BASE, 'e'),
	LOG_MODULE_NAME(FE, 'f'),
	LOG_MODULE_NAME(DSC, 'd'),
	LOG_MODULE_NAME(CIPLUS, 'c'),
	LOG_MODULE_NAME(SECTION, 's'),
	LOG_MODULE_NAME(DVR, 'v'),
	LOG_MODULE_NAME(A3_PLP, 'p'),
	LOG_MODULE_NAME(A3_BB, 'b'),
	LOG_MODULE_NAME(A3_ALP, 'a'),
	LOG_MODULE_NAME(A3_ROHC, 'h'),
	LOG_MODULE_NAME(A3_IPUDP, 'i'),
	LOG_MODULE_NAME(A3_LLS, 'l'),
	LOG_MODULE_NAME(A3_ROUTE, 'r'),
	LOG_MODULE_NAME(A3_MMT, 'm'),
	LOG_MODULE_NAME(DEMOD, 'o'),
	LOG_MODULE_NAME(ARIB_TLV, 't'),
	LOG_MODULE_NAME(ARIB_CIP, 'x'),
	LOG_MODULE_NAME(ARIB_MMT, 'n'),
};

static void debug_show_logmask(struct te_dev_mcu *mcu, struct seq_file *m)
{
	int rc, i;
	UINT16 val;

#define GET_BIT(v,bit)	(((v) >> (bit)) & 0x1)

	dprintf("%9s(_) : e w n i d\n", "module");
	dprintf("------------------------\n");
	for (i = 0; i < ARRAY_SIZE(log_module); i++) {
		rc = _TE_IPC_GetLogLevel(mcu->ipc, i, &val);
		if (rc != 0)
			break;

		dprintf("%9s(%c) : %d %d %d %d %d\n",
			log_module[i].name, log_module[i].c,
			GET_BIT(val, 0), GET_BIT(val, 1), GET_BIT(val, 2),
			GET_BIT(val, 3), GET_BIT(val, 4));
	}
}

static void debug_set_logmask(struct te_dev_mcu *mcu, const char *command)
{
	int rc, i;
	char m[16];
	char v[16];
	char *s;
	UINT16 module_mask;
	UINT16 level_mask;

	rc = sscanf(command, "%15s %15s", m, v);
	if (rc != 2)
		goto usage;

	module_mask = 0;
	s = m;
	while (*s) {
		for (i = 0; i < IPC_LOG_MODULE_MAX; i++) {
			if (*s == '0' || *s == log_module[i].c) {
				module_mask |= (0x1 << i);
				if (*s != '0')
					break;
			}
		}
		s++;
	}
	if (!module_mask)
		goto usage;

	s = v;
	if (*s == '+' || *s == '-') {
		int add = (*s == '+') ? 1 : 0;

		level_mask = 0;
		s++;
		while (*s) {
			switch (*s) {
			case '0' ... '9':
				level_mask |= (1 << (*s - '0'));
				break;
			case 'A' ... 'F':
				level_mask |= (1 << (*s - 'A' + 10));
				break;
			case 'e':
				level_mask |= (1 << IPC_LOG_LEVEL_ERROR);
				break;
			case 'w':
				level_mask |= (1 << IPC_LOG_LEVEL_WARN);
				break;
			case 'n':
				level_mask |= (1 << IPC_LOG_LEVEL_NOTI);
				break;
			case 'i':
				level_mask |= (1 << IPC_LOG_LEVEL_INFO);
				break;
			case 'd':
				level_mask |= (1 << IPC_LOG_LEVEL_DEBUG);
				break;
			default:
				break;
			}
			s++;
		}
		if (add)
			_TE_IPC_EnableLogMask(mcu->ipc, module_mask,
					      level_mask);
		else
			_TE_IPC_DisableLogMask(mcu->ipc, module_mask,
					       level_mask);
	} else {
		level_mask = simple_strtoul(v, (char **)NULL, 16);
		_TE_IPC_SetLogMask(mcu->ipc, module_mask, level_mask);
	}
	return;

usage:
	printk(KERN_ERR "\n");
	printk(KERN_ERR "usage> module value\n");
	printk(KERN_ERR "module:\n");
	for (i = 0; i < IPC_LOG_MODULE_MAX; i++) {
		if (log_module[i].c)
			printk(KERN_ERR "  %c(%s)\n", log_module[i].c,
			       log_module[i].name);
	}
	printk(KERN_ERR "  0(ALL)\n");
	printk(KERN_ERR "value:\n");
	printk(KERN_ERR "  [+-][ewnid0...9A...F] or level_mask\n");
}

static void debug_set_console(struct te_dev_mcu *mcu, const char *command)
{
	int rc;
	u32 val;
	enum te_reg_uart_type uart;

	val = simple_strtoul(command, (char **)NULL, 0);

	if (!val)
		uart = TE_UART_CPU;
	else
		uart = (mcu->num == 0) ? TE_UART_MCU0 : TE_UART_MCU1;

	if (uart == TE_UART_CPU) {
		/* disable */
		TE_REG_SelectUart(uart);
		_TE_IPC_SetConsoleEnable(mcu->ipc, false);
	} else {
		rc = _TE_IPC_SetConsoleEnable(mcu->ipc, true);
		if (rc == 0) {
			/* change uart mux to mcu if mcu support console */
			TE_REG_SelectUart(uart);
		}
	}
}

static void debug_show_status(struct te_dev_mcu *mcu, struct seq_file *m)
{
	struct mcu_status st;

	dprintf("%s STATUS\n", mcu->name);

	get_status(mcu, &st);
	dprintf("mcu ready : %d\n", st.ready);
	if (st.ready) {
		struct ipc_status s;

		dprintf("running time : %u sec\n", st.running_time);
		dprintf("status check error count  : %u\n",
			st.status_check_error_count);
		dprintf("recovery count : %u\n", st.recovery_count);

		_TE_IPC_GetStatus(mcu->ipc, &s);
		dprintf("ipc ready : %d\n", s.ready);
		if (s.ready) {
			dprintf("fw version : %x\n", s.fw_ver);
			dprintf("ipc version : %x\n", s.ipc_ver);

			dprintf("ipc send msg count : %u\n", s.send_msg_count);
			dprintf("ipc recv msg count : %u\n", s.recv_msg_count);
			dprintf("ipc timeout count : %u\n", s.timeout_count);

			dprintf("send queue overflow : %u\n",
				s.send_queue_overflow);
			dprintf("recv queue[0] overflow : %u\n",
				s.recv_queue_overflow[0]);
			dprintf("recv queue[1] overflow : %u\n",
				s.recv_queue_overflow[1]);
			dprintf("mcu int queue overflow : %u\n",
				s.mcu_int_queue_overflow);
		}

		if (mcu->num == 0) {
			int i;
			IPC_TS_CH_STATUS_T s;
			u32 full_count[IPC_TS_CH_COUNT];
			u32 overflow_count[IPC_TS_CH_COUNT];
			u32 syncbyte_errors[IPC_TS_CH_COUNT];

			for (i = 0; i < IPC_TS_CH_COUNT; i++) {
				TE_IPC_GetChannelStatus(i, &s);
				full_count[i] = s.full_cnt;
				overflow_count[i] = s.overflow_cnt;
				syncbyte_errors[i] = s.syncbyte_errors;
			}
			dprintf("%-15s : ", "full count");
			for (i = 0; i < IPC_TS_CH_COUNT; i++)
				dprintf("%u ", full_count[i]);
			dprintf("\n");

			dprintf("%-15s : ", "overflow count");
			for (i = 0; i < IPC_TS_CH_COUNT; i++)
				dprintf("%u ", overflow_count[i]);
			dprintf("\n");

			dprintf("%-15s : ", "syncbyte errors");
			for (i = 0; i < IPC_TS_CH_COUNT; i++)
				dprintf("%u ", syncbyte_errors[i]);
			dprintf("\n");
		}
	}
	dprintf("\n");
}

static const struct te_val_str mcu_perf_str[] = {
	{IPC_MAIN_PERF_TYPE_SYS, "sys"},
	{IPC_MAIN_PERF_TYPE_IPC, "ipc"},
	{IPC_MAIN_PERF_TYPE_FILTER, "filter"},
	{IPC_MAIN_PERF_TYPE_CIPLUS, "ciplus"},
	{IPC_MAIN_PERF_TYPE_ATSC3, "atsc3"},
	{IPC_MAIN_PERF_TYPE_FE, "fe"},
	{IPC_MAIN_PERF_TYPE_DSC, "dsc"},
	{IPC_MAIN_PERF_TYPE_DEBUG, "debug"},
	{IPC_MAIN_PERF_TYPE_DEMOD, "demod"},
};

static void show_perf_result(struct te_dev_mcu *mcu, struct seq_file *m)
{
	int i, rc;
	IPC_DEBUG_MAIN_PERF_T s;
	const char *str;
	u32 avg;

	dprintf("%6s: %5s %5s %5s\n", "name", "curr", "max", "avg");
	for (i = 0; i < IPC_MAIN_PERF_TYPE_MAX; i++) {
		str = te_find_match_string(mcu_perf_str,
					   ARRAY_SIZE(mcu_perf_str), i,
					   "invalid");

		rc = te_ipc_get_main_perf_status(mcu->ipc, i, &s);
		if (!rc && s.en) {
			avg = (s.count) ? (s.total/s.count) : 0;

			dprintf("%6s: %5u %5u %5u", str, s.curr, s.max, avg);
			dprintf(" (%u / %u)\n", s.total, s.count);
		} else {
			dprintf("%6s: disable\n", str);
		}
	}
	dprintf("\n");
}

static int debug_show(struct te_debug_item *item, struct seq_file *m)
{
	int ret = 0;
	struct ipc_status s;
	LX_TE_BLOCK_T b;
	struct te_dev_mcu *mcu = (struct te_dev_mcu *)item->private;

	switch (item->flags) {
	case DEBUG_ID_VERSION:
		_TE_IPC_GetStatus(mcu->ipc, &s);
		dprintf("0x%08x\n", s.fw_ver);
		break;

	case DEBUG_ID_RECOVERY:
		dprintf("%d\n", mcu->abnormal_recovery_enable);
		break;

	case DEBUG_ID_LOGMASK:
		debug_show_logmask(mcu, m);
		break;

	case DEBUG_ID_REGDUMP:
		b = (mcu->num == 0) ? LX_TE_BLOCK_MCU0 : LX_TE_BLOCK_MCU1;
		te_reg_dump_seq_file(b, m);
		break;

	case DEBUG_ID_STATUS:
		debug_show_status(mcu, m);
		break;

	case DEBUG_ID_STALL:
		dprintf("%d\n", mcu->stall);
		break;

	case DEBUG_ID_MAIN_PERF:
		show_perf_result(mcu, m);
		break;

	case DEBUG_ID_DEMOD_ENABLE:
		dprintf("%d\n", mcu->demod.enable);
		break;

	default:
		ret = -EPERM;
		break;
	}

	return ret;
}

static int debug_write(struct te_debug_item *item, char *str)
{
	int ret = 0;
	struct te_dev_mcu *mcu = (struct te_dev_mcu *)item->private;
	u32 val, v2;

	switch (item->flags) {
	case DEBUG_ID_FWLOAD:
		ret = fwload_from_file(mcu, str);
		break;
	case DEBUG_ID_FWLOAD2:
		ret = fwload_from_file2(mcu, str);
		break;

	case DEBUG_ID_JTAG:
		val = simple_strtoul(str, (char **)NULL, 0);
		if (!val)
			v2 = TE_JTAG_CPU;
		else
			v2 = (mcu->num == 0) ? TE_JTAG_MCU0 : TE_JTAG_MCU1;
		TE_REG_SelectJtag(v2);
		break;

	case DEBUG_ID_UART:
		val = simple_strtoul(str, (char **)NULL, 0);
		if (!val)
			v2 = TE_UART_CPU;
		else
			v2 = (mcu->num == 0) ? TE_UART_MCU0 : TE_UART_MCU1;
		TE_REG_SelectUart(v2);
		break;

	case DEBUG_ID_CONSOLE:
		debug_set_console(mcu, str);
		break;

	case DEBUG_ID_LOGMASK:
		debug_set_logmask(mcu, str);
		break;

	case DEBUG_ID_RECOVERY:
		val = simple_strtoul(str, (char **)NULL, 0);
		mcu->abnormal_recovery_enable = val;
		break;

	case DEBUG_ID_HALT:
		val = simple_strtoul(str, (char **)NULL, 0);
		if (val) {
			mutex_lock(&mcu->mutex);
			mcu_halt(mcu);
			mutex_unlock(&mcu->mutex);
		}
		break;

	case DEBUG_ID_STALL:
		val = simple_strtoul(str, (char **)NULL, 0);

		mutex_lock(&mcu->mutex);
		mcu_stall(mcu, (val) ? true : false);
		mutex_unlock(&mcu->mutex);
		break;

	case DEBUG_ID_DEMOD_ENABLE:
		val = simple_strtoul(str, (char **)NULL, 0);
		ret = te_mcu_enable_demod((val) ? true : false);
		break;

	default:
		ret = -EPERM;
		break;
	}

	return ret;
}

static const struct te_debug_simple_ops debug_ops = {
	.show = debug_show,
	.write = debug_write,
};

static const struct te_debug_item_info debug_list[] = {
	DBGITM_SIM_R("version", &debug_ops, DEBUG_ID_VERSION),
	DBGITM_SIM_W("fwload", &debug_ops, DEBUG_ID_FWLOAD),
	DBGITM_SIM_W("fwload2", &debug_ops, DEBUG_ID_FWLOAD2),
	DBGITM_SIM_W("jtag", &debug_ops, DEBUG_ID_JTAG),
	DBGITM_SIM_W("uart", &debug_ops, DEBUG_ID_UART),
	DBGITM_SIM_W("console", &debug_ops, DEBUG_ID_CONSOLE),
	DBGITM_SIM("logmask", &debug_ops, DEBUG_ID_LOGMASK),
	DBGITM_SIM("recovery", &debug_ops, DEBUG_ID_RECOVERY),
	DBGITM_SIM_R("regdump", &debug_ops, DEBUG_ID_REGDUMP),
	DBGITM_SIM_R("status", &debug_ops, DEBUG_ID_STATUS),
	DBGITM_SIM_W("halt", &debug_ops, DEBUG_ID_HALT),
	DBGITM_SIM("stall", &debug_ops, DEBUG_ID_STALL),
	DBGITM_SIM_R("perf", &debug_ops, DEBUG_ID_MAIN_PERF),
	DBGITM_SIM("demod_enable", &debug_ops, DEBUG_ID_DEMOD_ENABLE),
};

static int init_debug(struct te_debug_dir *root, struct te_dev_mcu *mcu)
{
	int ret;
	char name[8];

	snprintf(name, sizeof(name), "mcu%u", mcu->num);

	mcu->debug_dir = te_debug_create_dir(name, root);
	if (!mcu->debug_dir) {
		log_error("can't create '%s' debug dir\n", name);
		return -EIO;
	}

	ret = debug_create_item_files(debug_list, mcu, mcu->debug_dir);

	return ret;
}

static void mcu_destroy(struct te_dev_mcu *mcu)
{
	if (mcu->ipc) {
		// TODO: ipc release
	}

	if (mcu->mem_ctx)
		te_mem_close(mcu->mem_ctx);

	kfree(mcu);
}

static struct te_dev_mcu *mcu_create(u8 num)
{
	struct te_dev_mcu *mcu;
	char name[16];
	const struct mcu_config *cfg;
	LX_TE_BLOCK_T block;

	mcu = kzalloc(sizeof(struct te_dev_mcu), GFP_KERNEL);
	CHECK_ERROR(!mcu, return NULL, "can't alloc memory");

	mcu->num = num;
	sprintf(mcu->name, "MCU%u", num);

	cfg = get_config(num);
	CHECK_ERROR(!cfg, goto error, "can't get config");

	mcu->cfg = cfg;
	mcu->ready = false;

	mutex_init(&mcu->mutex);
	mutex_init(&mcu->demod.mutex);
	INIT_LIST_HEAD(&mcu->rcallback_head);
	mutex_init(&mcu->rcallback_mutex);

	block = (num == 0) ? LX_TE_BLOCK_MCU0 : LX_TE_BLOCK_MCU1;
	mcu->reg_base = TE_REG_GetBaseAddr(block);

	/* mcu halt */
	mcu_reg_write(mcu, MCU_REG_OFFSET_PROC_CTRL, MCU_PROC_HALT_MASK);

	mcu->mem_ctx = te_mem_open(MCU_MEM_NAME);
	CHECK_ERROR(!mcu->mem_ctx, goto error, "can't open mm");

	sprintf(name, "mcu%u_rom", mcu->num);
	mcu->rom_addr = te_mem_alloc(mcu->mem_ctx, cfg->rom_size, name);
	CHECK_ERROR(!mcu->rom_addr, goto error, "can't alloc memory(%s)\n",
		    name);

	mcu->ipc = te_mcu_create_ipc(num);
	CHECK_ERROR(!mcu->ipc, goto error, "Error in te_mcu_create_ipc\n");

	return mcu;

error:
	mcu_destroy(mcu);

	return NULL;
}

static void init_done_work(struct work_struct *work)
{
	struct te_dev_mcu *mcu;
	mcu = container_of(work, struct te_dev_mcu, init_done_work);

	log_noti("mcu[%d] init done", mcu->num);

	mutex_lock(&mcu->mutex);

	te_clockgate_release_clock(mcu->tdev, TE_DEVICE_TYPE_MCU);
	mcu->get_clk = false;

	mutex_unlock(&mcu->mutex);
}

/* isr */
static int init_done_callback(void *data, void *arg)
{
	struct te_device *dev = arg;
	u8 *num = data;
	struct te_dev_mcu *mcu = dev->mcu[*num];

	queue_work(system_freezable_wq, &mcu->init_done_work);
	return 0;
}

static int mcu_dev_init(struct te_device *dev)
{
	int ret, i;
	struct te_dev_mcu *mcu;
#if !defined(TE_EMULATOR) && !CONFIG_LX_BOARD_FPGA
	struct te_timer *timer;
#endif
	struct te_config *cfg = te_get_config();
	struct te_mem_region_info *minfo = te_get_mem_region_info(TE_MEM_MCU);
	const void *data;
	u32 size;

	if (cfg->num_mcu > TE_MAX_MCU) {
		log_error("cfg->num_mcu(%d) over max\n", cfg->num_mcu);
		dev->num_mcu = TE_MAX_MCU;
	} else {
		dev->num_mcu = cfg->num_mcu;
	}

	ret = te_mem_register(MCU_MEM_NAME, minfo->addr, minfo->size,
			    TE_MEM_TYPE_NORMAL);
	CHECK_ERROR(ret, return ret, "Error in te_mem_register");

	for (i = 0; i < dev->num_mcu; i++) {
		mcu = mcu_create(i);
		CHECK_ERROR(!mcu, goto error, "Error in mcu_create(%d)", i);

		init_debug(dev->debug.dir, mcu);

#if !defined(TE_EMULATOR) && !CONFIG_LX_BOARD_FPGA
		timer = te_add_timer(dev, MCU_STATUS_CHECK_INTERVAL,
				 status_check_handler, mcu);
		CHECK_ERROR(!timer,, "can't add timer(%d)\n", i);

		mcu->status_check_timer = timer;
		mcu->abnormal_recovery_enable = MCU_RECOVERY_CHECK_COUNT;
#endif
		mcu->tdev = dev;
		INIT_WORK(&mcu->init_done_work, init_done_work);
		dev->mcu[i] = mcu;

		/* load the included mcu binary if exists */
		ret = get_mcu_binary(mcu, &data, &size);
		if (!ret && data != NULL) {
			ret = load_mcu_binary(mcu, data, size);
			CHECK_ERROR(ret, goto error,
				    "Error in load_mcu_binary(%d)", i);
		}
		te_ipc_register_init_done_callback(mcu->ipc, init_done_callback,
						   dev);
	}

	/* for demod access */
	_tdev = dev;

	return 0;

error:
	for (i = 0; i < dev->num_mcu; i++) {
		mcu = dev->mcu[i];
		if (mcu) {
			if (mcu->status_check_timer)
				te_del_timer(mcu->status_check_timer);
			mcu_destroy(mcu);
			dev->mcu[i] = NULL;
		}
	}
	te_mem_unregister(MCU_MEM_NAME);
	_tdev = NULL;

	return -EIO;
}

static void mcu_dev_release(struct te_device *dev)
{
	struct te_dev_mcu *mcu;
	int i;

	for (i = 0; i < dev->num_mcu; i++) {
		mcu = dev->mcu[i];
		if (mcu) {
			if (mcu->status_check_timer)
				te_del_timer(mcu->status_check_timer);
			mcu_destroy(mcu);
			dev->mcu[i] = NULL;
		}
	}
	te_mem_unregister(MCU_MEM_NAME);
	_tdev = NULL;
}

static int mcu_dev_suspend(struct te_device *dev)
{
	int i;
	struct te_dev_mcu *mcu;

	for (i = 0; i < dev->num_mcu; i++) {
		mcu = dev->mcu[i];

		_TE_IPC_Disable(mcu->ipc);

		/* halt mcu */
		mcu_reg_write(mcu, MCU_REG_OFFSET_PROC_CTRL,
			      MCU_PROC_HALT_MASK);

		if (mcu->demod.suspend_func)
			mcu->demod.suspend_func(mcu->demod.suspend_arg);
		disable_demod(mcu);
	}

	return 0;
}

static int mcu_dev_resume(struct te_device *dev)
{
	int i, ret;
	struct te_dev_mcu *mcu;

	for (i = 0; i < dev->num_mcu; i++) {
		mcu = dev->mcu[i];

		if (mcu->demod.resume_func)
			mcu->demod.resume_func(mcu->demod.resume_arg);
		mcu_recovery(mcu);
	}

	log_mcu("wait for mcu init");
	ret = wait_for_mcu_init(dev, MCU_INIT_MAX_TIMEOUT);
	if (ret) {
		log_error("mcu init timeout !!!");
		return -ETIME;
	}
	log_mcu("all mcu init done");

	return 0;
}

const struct te_sub_driver te_mcu_driver = {
	.name = "te_mcu",
	.init = mcu_dev_init,
	.release = mcu_dev_release,
	.suspend = mcu_dev_suspend,
	.resume = mcu_dev_resume,
};
