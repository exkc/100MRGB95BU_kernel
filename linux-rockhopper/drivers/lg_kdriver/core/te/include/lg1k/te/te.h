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
 *  @date	2018-10-12
 *  @note	Additional information.
 */

#ifndef	_LG1K_TE_H_
#define	_LG1K_TE_H_

#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/ioctl.h>
#include <linux/compat.h>

#include <lg1k/te/reg.h>
#include <lg1k/te/ipc.h>
#include <lg1k/te/debug.h>

#include "te_kapi.h"

#define TE_MAX_MCU	2
#define TE_MAX_UPLOAD	2
#define TE_MAX_DSC	2

struct te_device;

/* configurations */

struct te_io_cfg {
	u8 version; 		/* deprecated */
	u8 num_dumper;
	u8 num_tpi_input;	/* number of tpi input port */
	const LX_TE_INPUT_PORT_T *tpi_info;

	u8 num_ci_input;	/* number of ci input port(from M16+) */
	u8 num_ciplus_input;	/* number of ciplus input port */
	u8 num_ciplus_demux;	/* number of ciplus demux */
};

struct te_clk_cfg {
	u8 num_stcc;
	u8 num_gstcc;
	u32 divider;	/* FPGA */
};

struct te_reg_addr_cfg {
	u32 base;
	u32 dumper;	/* >= O20 */
	u32 atsc3;		/* >= M17 && < O20 */
	u32 arib2;		/* >= M19 && < O20 */
	u32 tpi;		/* >= M17 */
	u32 top;
	u32 pidf;
	u32 tsbuf;
	u32 stcc;
	u32 be;
	u32 dsc[TE_MAX_DSC];
	u32 upload[TE_MAX_UPLOAD];
	u32 mcu[TE_MAX_MCU];
	u32 ciplus;
};

struct te_config {
	struct te_reg_addr_cfg reg_addr;
	struct te_io_cfg io;
	struct te_clk_cfg clk;

	int hw_irq_num;
	int mcu_irq_num[TE_MAX_MCU];
	int num_mcu;
	int num_dsc;
	int num_upload;

	bool no_stcc_bug;
	bool reg_clock_gate;
	bool include_demod;
	bool no_pvr_download;
	bool use_ion;
};

struct te_subdev {
	struct device *dev;
	struct te_device *tdev;
	struct list_head list;	/* list of subdev */
	void *private;
};

struct te_config *te_get_config(void);

static inline struct te_io_cfg *te_get_io_config(void)
{
	struct te_config *cfg = te_get_config();
	return &cfg->io;
}

static inline struct te_reg_addr_cfg *te_get_reg_addr_config(void)
{
	struct te_config *cfg = te_get_config();
	return &cfg->reg_addr;
}

int te_register_subdev(struct device *dev, struct te_subdev *sd);
struct te_subdev *te_get_subdev(struct te_device *tdev, const char *name);



/* ioctl */

#ifdef CONFIG_COMPAT
#define te_ioctl_get_user_ptr(ptr)				\
({								\
	void __user *uptr = (void __user*)(ptr);		\
	if(is_compat_task()) {					\
		compat_uptr_t cptr = ptr_to_compat(uptr);	\
		uptr = compat_ptr(cptr);			\
	}							\
	uptr;							\
})
#else
#define te_ioctl_get_user_ptr(ptr)	(void __user*)(ptr)
#endif

struct te_ioctl_ptr_param {
	void __user *user_ptr;	/* buffer pointer in ioctl param */
	void **kernel_ptr;	/* address of buffer pointer variable  */
	size_t size;		/* size of buffer in ioctl param */
	int dir;		/* _IOC_READ or _IOC_WRITE */
};

typedef int (*te_ioctl_func_t)(void *priv, unsigned int cmd, void *arg);
typedef int (*te_ioctl_param_func_t)(void *priv, unsigned int cmd,
				     void *arg,
				     struct te_ioctl_ptr_param *param);

struct te_ioctl {
	char magic;
	te_ioctl_func_t func;
	te_ioctl_param_func_t get_param;
};

#define IOC_INFO(cmd, func, args...) \
	[_IOC_NR(cmd)] = {cmd, func, #cmd, ##args}

#define IOC_INFO_NOLOCK(cmd, func) \
	[_IOC_NR(cmd)] = {cmd, func, #cmd, false, true}

#define IOC_INFO_DEV(cmd, func, args...)	\
	[_IOC_NR(cmd)] = {cmd, func, #cmd, true, ##args}




#define __do_ioctl(fh, ioc, arg, mtx)					\
({									\
	int __ret;							\
	if (fh->channel || ioc->dev_node) {				\
		if (ioc->no_lock) {					\
			__ret = ioc->func(fh, arg);			\
		} else {						\
			mutex_lock(&(mtx));				\
			__ret = ioc->func(fh, arg);			\
			mutex_unlock(&(mtx));				\
		}							\
		if (__ret < 0) {					\
			log_error("%s failed[%d]\n", ioc->name, __ret);	\
		}							\
	} else {							\
		__ret = -ENOTTY;					\
	}								\
	__ret;								\
})

#define te_do_ioctl(m, priv, cmd, arg, mtx, ioctls)			\
({									\
	int __ret = -ENOTTY;						\
	struct m##_fh *__fh = priv;					\
	u32 __num = _IOC_NR(cmd);					\
	if (__num < ARRAY_SIZE(ioctls)) {				\
		const struct m##_ioctl_info *__ioc = &ioctls[__num];	\
		if (__ioc->cmd == cmd) {				\
			__ret = __do_ioctl(__fh, __ioc, arg, mtx);	\
		}							\
	}								\
	if (__ret == -ENOTTY)						\
		log_error("invalid command[0x%08x]('%c',%d)\n",		\
			   cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));		\
	__ret;								\
})

int te_ioctl_usercopy(unsigned int cmd, unsigned long arg,
		      te_ioctl_func_t func,
		      te_ioctl_param_func_t get_user_ptr, void *priv);

int te_ioctl_cache_ctrl(LX_TE_CACHE_CTRL_T *ctrl);

/* timer */
struct te_timer;

struct te_timer *te_add_timer(struct te_device *dev, u32 interval,
			      void (*func)(void *), void *arg);

struct te_timer *te_add_oneshot_timer(struct te_device *dev, u32 timeout,
				      void (*func)(void *), void *arg);

struct te_timer *te_add_workqueue_timer(struct te_device *dev, u32 time,
					void (*func)(void *), void *arg);
struct te_timer *te_add_oneshot_workqueue_timer(struct te_device *dev, u32 time,
						void (*func)(void *),
						void *arg);
void te_del_timer(struct te_timer *timer);
void te_halt_timer(struct te_device *dev, bool halt);

/* dumper */
enum te_dumper_mode {
	TE_DUMPER_MODE_ATSC3 = 0,
	TE_DUMPER_MODE_ARIB2,
	TE_DUMPER_MODE_CI20,
	TE_DUMPER_MODE_MAX
};

struct te_dumper_status {
	enum te_reg_channel_src src;
	enum te_reg_dumper_mode mode;
	bool enable;
	u32 bytes;	/* received packets in bytes */
	u32 time;	/* capture time - ms unit */
};

int te_dumper_set_mode(struct te_device *dev, enum te_dumper_mode mode);
enum te_dumper_mode te_dumper_get_mode(struct te_device *dev);

int te_dumper_register_isr_callback(struct te_device *dev,
				    enum te_dumper_mode mode,
				    void (*callback)(u32 status2, void *arg),
				    void *arg);

struct te_dumper_status *te_debug_get_dumper_status(struct te_device *dev);
void te_debug_show_dumper_status(struct te_device *dev, struct seq_file *m,
				 struct te_dumper_status *old);
void te_debug_free_dumper_status(struct te_dumper_status *status);

/* debug */
int te_get_authority(enum ipc_authority_module module);
struct te_debug_dir *te_get_debug_dir(struct te_device *dev);

/* interrupt */
typedef int (*te_irq_handler_t)(u32 status1, void *dev_id);

int te_request_irq(struct te_device *dev, const char *name, u32 mask,
		   te_irq_handler_t handler, void *dev_id);
void te_free_irq(struct te_device *dev, const char *name);


/* device */
enum te_device_type {
	TE_DEVICE_TYPE_TE = 0,
	TE_DEVICE_TYPE_ARIB2,
	TE_DEVICE_TYPE_ATSC3,
	TE_DEVICE_TYPE_CI14,
	TE_DEVICE_TYPE_CRYPTO,
	TE_DEVICE_TYPE_DVB_CI14,
	TE_DEVICE_TYPE_DVB_DELIVERY,
	TE_DEVICE_TYPE_DVB_DEMUX,
	TE_DEVICE_TYPE_DVB_DVR,
	TE_DEVICE_TYPE_PVR,
	TE_DEVICE_TYPE_SDEC,
	TE_DEVICE_TYPE_MCU,
	TE_DEVICE_TYPE_CI,
	TE_DEVICE_TYPE_CI20,
	TE_DEVICE_TYPE_DEMOD, //
	TE_DEVICE_TYPE_MAX,
};
int te_clockgate_acquire_clock(struct te_device *dev, enum te_device_type type);
int te_clockgate_release_clock(struct te_device *dev, enum te_device_type type);

__printf(4, 5)
struct device *te_class_device_create(struct te_device *tdev,
				      dev_t devt, void *drvdata,
				      const char *fmt, ...);
void te_class_device_destroy(struct te_device *tdev, dev_t devt);

#endif				/* _LG1K_TE_H_ */

/** @} */
