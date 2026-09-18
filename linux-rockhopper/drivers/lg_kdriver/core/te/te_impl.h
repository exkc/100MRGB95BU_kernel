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
 *  @author	Kyungseok Hyun
 *  @version	1.0
 *  @date		2015-02-27
 *  @note		Additional information.
 */

#ifndef _TE_IMPL_H_
#define _TE_IMPL_H_

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/vmalloc.h>
#include <linux/delay.h>
#include <linux/kthread.h>

#include <lg1k/te/te.h>
#include <lg1k/te/io.h>
#include <lg1k/te/reg.h>
#include <lg1k/te/util.h>
#include <lg1k/te/debug.h>
#include <lg1k/te/mem.h>

#include "logm_kapi.h"
#include "base_types.h"
#include "os_util.h"

#define	TE_MODULE		"te"
#define TE_DEVICE_NAME		"lg1k-te"

#define MAX_TPI_NUM			6

#define MAX_TPI_PORT_NUM		MAX_TPI_NUM
#define MAX_CIPLUS_INPUT_PORT_NUM	3
#define MAX_CI_INPUT_PORT_NUM		1

#define LOG_LEVEL_ERROR 	LX_LOGM_LEVEL_ERROR	/* 0 */
#define	LOG_LEVEL_WARNING 	LX_LOGM_LEVEL_WARNING	/* 1 */
#define LOG_LEVEL_NOTI 		LX_LOGM_LEVEL_NOTI	/* 2 */
#define LOG_LEVEL_INFO 		LX_LOGM_LEVEL_INFO	/* 3 */
#define LOG_LEVEL_DEBUG 	LX_LOGM_LEVEL_DEBUG	/* 4 */
#define LOG_LEVEL_TRACE 	LX_LOGM_LEVEL_TRACE	/* 5 */
#define LOG_LEVEL_MEM 		LX_LOGM_LEVEL_TRACE + 1	/* 6 */
#define LOG_LEVEL_MCU 		LX_LOGM_LEVEL_TRACE + 2	/* 7 */
#define LOG_LEVEL_IPC 		LX_LOGM_LEVEL_TRACE + 3	/* 8 */
#define LOG_LEVEL_DEVICE 	LX_LOGM_LEVEL_TRACE + 4
#define LOG_LEVEL_CRYPTO 	LX_LOGM_LEVEL_TRACE + 5

#define TE_LOG(type,fmt,args...) \
  LOGM_PRINT( g_te_debug_fd, (LOG_LEVEL_##type), fmt, ##args)

#define log_error(fmt,args...)		TE_LOG(ERROR,fmt,##args)
#define log_warning(fmt,args...)	TE_LOG(WARNING,fmt,##args)
#define log_noti(fmt,args...)		TE_LOG(NOTI,fmt,##args)
#define log_info(fmt,args...)		TE_LOG(INFO,fmt,##args)
#define log_debug(fmt,args...)		TE_LOG(DEBUG,fmt,##args)
#define log_trace(fmt,args...)		TE_LOG(TRACE,fmt,##args)
#define log_mem(fmt,args...)		TE_LOG(MEM,fmt,##args)
#define log_mcu(fmt,args...)		TE_LOG(MCU,fmt,##args)
#define log_ipc(fmt,args...)		TE_LOG(IPC,fmt,##args)
#define log_device(fmt,args...)		TE_LOG(DEVICE,fmt,##args)
#define log_crypto(fmt,args...)		TE_LOG(CRYPTO,fmt,##args)

#define TE_PMLOG(level, tedev, result, type, log) \
    do { \
        pr_info("LowPower::%s::broadcast::te::%d::%s-%s::%s::%s::%s\n", \
		level, \
		atomic_read(&(tedev)->pdev->dev.power.usage_count), \
                (current->group_leader?current->group_leader->comm:"-"), \
		current->comm, \
                type, (result) ? "error" : "ok", log); \
    } while(0)

#define pmlog_error(tedev, result, type, log) \
	TE_PMLOG("error", tedev, result, type, log)
#define pmlog_info(tedev, result, type, log) \
	TE_PMLOG("info", tedev, result, type, log)
#define pmlog_debug(tedev, result, type, log) \
	TE_PMLOG("debug", tedev, result, type, log)

#define FUNC_TRACE_ENTER()		log_trace("<--%s", __FUNCTION__)
#define FUNC_TRACE_EXIT()		log_trace("-->%s", __FUNCTION__)

#define CHECK_ERROR(__checker,__if_action,fmt,args...)   \
  __CHECK_IF_ERROR(__checker, log_error, __if_action , fmt, ##args )

#define CHECK_NULL_PARAM(param) \
  CHECK_ERROR((param) == NULL, return -EINVAL, "parameter(" #param ") is null")

#define CHECK_PARAM(__checker,fmt,args...) \
  CHECK_ERROR(__checker, return -EINVAL, "invalid parameter : " fmt, ##args)

/* Register Access Macros */
#define TE_WRITE32(addr, val)	__raw_writel(val , (void __iomem *)(addr))
#define TE_READ32(addr)		__raw_readl((void __iomem  *)(addr))


struct te_dev_mcu;

struct te_tpi_monitor {
	char name[32];
	bool enable;
	bool ready;		/* TRUE : after getting 1st status */
	bool first_check;	/* Check first result (initial checker) */
	u32 no_input_count;	/* no input count of tpi */
	u32 input_msg_count;	/* To disable verbose message */
	u32 pkt_count;		/* all packets from demod */
	u32 tei_count;		/* transport error indicator count */
	u32 print_time;		/* jiffies */
	u32 warn_time;		/* jiffies */
};

struct te_dev_tpi {
	enum te_reg_tpi_port port;	/* TPI_INT_DEMOD, TPI_EXT_DEMOD0 ... */
	struct lx_te_tpi_cfg cfg;
	struct te_tpi_monitor monitor;
};

struct te_suspend_data {
	/* For Suspend / Resume data */
	struct lx_te_tpi_cfg tpi[MAX_TPI_PORT_NUM];
	enum te_reg_tpi_port ciplus_input[MAX_CIPLUS_INPUT_PORT_NUM];
	enum te_reg_tpi_port ci_input;
};

struct te_dev_io {
	struct te_debug_dir *debug_dir;
};

struct te_dev_clk {
	struct te_debug_dir *debug_dir;
};

struct te_dev_dump {
	struct te_debug_dir *debug_dir;
	struct list_head dump_list;
};

struct te_dev_timer {
	struct task_struct *thread;
	struct list_head list;

	bool halt;
};

struct te_dumper_callback {
	void (*func)(u32 status2, void *arg);
	void *arg;
};

struct te_dev_dumper {
	enum te_dumper_mode mode;
	struct te_dumper_callback atsc3;
	struct te_dumper_callback arib2;
	struct te_dumper_callback ci20;
	spinlock_t spinlock;
};

struct te_dev_irq {
	spinlock_t spinlock;
	struct list_head list;
	unsigned long count;
};

/* ION */

#define TE_ION_TPI_NUM 2
#define TE_ION_CH_NUM 2

enum te_ion_tpi_type {
	ION_TPI_TS = 0,
	ION_TPI_TLV,
	ION_TPI_LGC,
	ION_TPI_MAX
};

struct te_dev_ion_tpi {
	u8 idx;
	bool en;
	enum te_ion_tpi_type type;
	bool parallel;
	struct mutex tpi_lock;
};

struct te_dev_ion_debug_reg {
	u8 dev;
	u8 ch;
	struct te_debug_dir *debug_dir;
	struct te_dev_ion *ion;
};


struct te_dev_ion_ucom_func {
	u32 (*read)(u32 addr);
	int (*write)(u32 addr, u32 val);
};

struct te_dev_ion_pkt_monitor {
	u32 pkt_incr; //tp packet increment
	u32 tei_incr; //tei increment

	bool ready;
};

struct te_dev_ion {
	struct mutex spi_lock;
	struct te_debug_dir *debug_dir;
	struct te_dev_ion_debug_reg reg[4];
	const struct te_dev_ion_ucom_func *ucom_func;

	u8 ci_spi_ch;
	//u32 ci_spi_clk; //note: prepare for future use

	u32 spi_clk;
	struct te_dev_ion_tpi tpi[TE_ION_TPI_NUM];
	struct te_dev_ion_pkt_monitor ci_in;
	struct te_dev_ion_pkt_monitor ci_out;
	u8 tei_abnormal_cnt;
	u8 no_packet_cnt;
};

struct te_mem_cfg {
	struct te_mem_region_info region[TE_MEM_REGION_MAX];
	struct te_mem_region_info total;
};

struct te_dev_debug {
	struct te_debug_dir *dir;
};

struct te_dev_clockgate {
	bool disabled;
	u32 ref_cnt;
	u32 dev_cnt[TE_DEVICE_TYPE_MAX];
};

struct te_device {
	struct cdev cdev;
	dev_t devt;
	int users;

	struct class *class;
	struct list_head subdevs;

	struct mutex mutex;
	struct te_suspend_data *data;

	struct te_config *cfg;
	struct te_mem_cfg *mem_cfg;

	struct te_dev_tpi tpi[MAX_TPI_PORT_NUM];
	struct te_timer *tpi_timer;	//for tpi monitor

	enum te_reg_tpi_port ciplus_input[MAX_CIPLUS_INPUT_PORT_NUM];
	enum te_reg_tpi_port ci_input;
	struct te_dev_tpi *ci_src_tpi; // get ci source port info

	struct te_dev_debug debug;

	struct te_dev_io io;
	struct te_dev_clk clk;
	struct te_dev_dump dump;
	struct te_dev_timer timer;
	struct te_dev_dumper dumper;
	struct te_dev_irq irq;
	struct te_dev_ion ion;

	u8 num_mcu;
	struct te_dev_clockgate clockgate;

	struct te_dev_mcu *mcu[TE_MAX_MCU];
	struct work_struct init_done_work[TE_MAX_MCU];

	struct platform_device *pdev;
};

/* file handle for TE */
struct te_fh {
	struct te_device *dev;
};

struct te_sub_driver {
	const char *name;

	int (*early_init)(struct te_device *dev);
	int (*init)(struct te_device *dev);
	void (*release)(struct te_device *dev);

	int (*suspend)(struct te_device *dev);
	int (*resume)(struct te_device *dev);

	int (*open)(struct te_fh *fh);
	void (*close)(struct te_fh *fh);
	const struct te_ioctl *ioctl;
};


/* CONFIG */
void te_cfg_prepare(void);
void te_cfg_init(struct te_device *dev);

/* CORE */
int te_device_init(struct te_device *dev);
void te_device_release(struct te_device *dev);
int te_device_suspend(struct te_device *dev);
int te_device_resume(struct te_device *dev);

int te_clockgate_init(struct te_device *dev);
int te_clockgate_suspend(struct te_device *dev);
int te_clockgate_resume(struct te_device *dev);
int te_clockgate_do_clockgate(struct te_device *dev, bool disable);

extern struct file_operations te_dev_fops;

/* DEVICE */
struct platform_device *te_register_devices(void);
void te_unregister_devices(void);

/* MM */

/* REG */

/* TIMER */

/* IO */

/* DUMP */

/* MCU */

/* DUMPER */

/* DEBUG */

extern int g_te_debug_fd;
extern u32 g_te_reg_log_mask;

extern const struct te_sub_driver te_debug_driver;
extern const struct te_sub_driver te_mem_driver;
extern const struct te_sub_driver te_reg_driver;
extern const struct te_sub_driver te_timer_driver;
extern const struct te_sub_driver te_irq_driver;
extern const struct te_sub_driver te_dumper_driver;
extern const struct te_sub_driver te_io_driver;
extern const struct te_sub_driver te_clk_driver;
extern const struct te_sub_driver te_dump_driver;
extern const struct te_sub_driver te_mcu_driver;

#endif
