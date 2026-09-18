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
 *  driver interface header for ci device. ( used only within kdriver )
 *	ci device will teach you how to make device driver with new platform.
 *
 *  @author		Srinivasan Shanmugam	(srinivasan.shanmugam@lge.com)
 *  @author		Hwajeong Lee (hwajeong.lee@lge.com)
 *  @author		Jinhwan Bae (jinhwan.bae@lge.com) - modifier
 *  @author		Hyunho Kim (hyunho747.kim@lge.com) - modifier
 *  @version	1.0
 *  @date		2009.12.30
 *
 *  @addtogroup lg1150_ci
 *	@{
 */

#ifndef	_CI_DEV_H_
#define	_CI_DEV_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
//#define POD_ON_INIT

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/cdev.h>
#include <linux/fs.h>

#include "ci_cfg.h"
#include "ci_kapi.h"

#include "ci_util.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

//struct ci_proc;
//struct ci_dev_cis_info;

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define	CI_MAX_NAME		32
#define CI_IO_ERR_HIS_MAX_CNT	10

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

#define ci_is_flag(_cidev)				(_cidev->cflags.is_flag)
#define ci_is_probe_done(_cidev)		(((_ci_is_flags *)(&(_cidev->cflags.is_flag)))->is_probe_done)
#define ci_is_init_done(_cidev)			(((_ci_is_flags *)(&(_cidev->cflags.is_flag)))->is_init_done)
#define ci_is_card_detected(_cidev)		(((_ci_is_flags *)(&(_cidev->cflags.is_flag)))->is_card_detected)
#define ci_is_power_restart(_cidev)		(((_ci_is_flags *)(&(_cidev->cflags.is_flag)))->is_power_restart)
#define ci_is_cam_init_done(_cidev)		(((_ci_is_flags *)(&(_cidev->cflags.is_flag)))->is_cam_init_done)
#define ci_is_cam_cis_done(_cidev)		(((_ci_is_flags *)(&(_cidev->cflags.is_flag)))->is_cam_cis_done)
#define ci_is_cam_cor_done(_cidev)		(((_ci_is_flags *)(&(_cidev->cflags.is_flag)))->is_cam_cor_done)
#define ci_is_cam_nego_done(_cidev)		(((_ci_is_flags *)(&(_cidev->cflags.is_flag)))->is_cam_nego_done)
#define ci_is_pcap_dump_on(_cidev)		(((_ci_is_flags *)(&(_cidev->cflags.is_flag)))->is_pcap_dump_on)
#define ci_is_suspended(_cidev)			(((_ci_is_flags *)(&(_cidev->cflags.is_flag)))->is_suspended)

#define ci_opt_flag(_cidev)				(_cidev->cflags.opt_flag)
#define ci_opt_cd_pol(_cidev)			(((_ci_opt_flags *)(&(_cidev->cflags.opt_flag)))->opt_cd_pol)
#define ci_opt_io_mode_on(_cidev)		(((_ci_opt_flags *)(&(_cidev->cflags.opt_flag)))->opt_io_mode_on)
#define ci_opt_io_mode(_cidev)			(((_ci_opt_flags *)(&(_cidev->cflags.opt_flag)))->opt_io_mode)
#define ci_opt_io_time_show(_cidev)		(((_ci_opt_flags *)(&(_cidev->cflags.opt_flag)))->opt_io_time_show)
#define ci_opt_burst_mode(_cidev)		(((_ci_opt_flags *)(&(_cidev->cflags.opt_flag)))->opt_burst_mode)
#define ci_opt_os_proc_base(_cidev)		(((_ci_opt_flags *)(&(_cidev->cflags.opt_flag)))->opt_os_proc_base)

#define ci_mutex_init(_cidev)					mutex_init(&_cidev->mutex)

#define CI_MUTEX_LOCK(dev)			mutex_lock(&(dev)->mutex);
#define CI_MUTEX_UNLOCK(dev)		mutex_unlock(&(dev)->mutex);

#define ci_lock_init(_cidev)					spin_lock_init(&_cidev->lock);
#define ci_lock(_cidev)							spin_lock(&_cidev->lock);
#define ci_unlock(_cidev)						spin_unlock(&_cidev->lock);
#define ci_lock_irqsave(_cidev, _flags)			spin_lock_irqsave(&_cidev->lock, _flags);
#define ci_unlock_irqrestore(_cidev, _flags)	spin_unlock_irqrestore(&_cidev->lock, _flags);

#define ci_io_lock_init(_cidev)					spin_lock_init(&_cidev->io.lock);
#define ci_io_lock(_cidev)						spin_lock(&_cidev->io.lock);
#define ci_io_unlock(_cidev)					spin_unlock(&_cidev->io.lock);
#define ci_io_lock_irqsave(_cidev, _flags)		spin_lock_irqsave(&_cidev->io.lock, _flags);
#define ci_io_unlock_irqrestore(_cidev, _flags)	spin_unlock_irqrestore(&_cidev->io.lock, _flags);

#define ci_dev_name(_cidev)						(_cidev->name)

#define ci_get_io_rd_err_cnt(_cidev)	\
	__ci_get_io_xx_err_cnt(_cidev, CI_IO_ERR_TYPE_RD)
#define ci_get_io_wr_err_cnt(_cidev)	\
	__ci_get_io_xx_err_cnt(_cidev, CI_IO_ERR_TYPE_WR)

#define ci_get_io_rd_err_code(_cidev, _idx)	\
	__ci_get_io_xx_err_code(_cidev, CI_IO_ERR_TYPE_RD, _idx)
#define ci_get_io_wr_err_code(_cidev, _idx)	\
	__ci_get_io_xx_err_code(_cidev, CI_IO_ERR_TYPE_WR, _idx)

#define ci_set_io_rd_err_code(_cidev, _code)	\
	__ci_set_io_xx_err_code(_cidev, CI_IO_ERR_TYPE_RD, _code)
#define ci_set_io_wr_err_code(_cidev, _code)	\
	__ci_set_io_xx_err_code(_cidev, CI_IO_ERR_TYPE_WR, _code)

#define ci_get_io_rd_err_time(_cidev, _idx)	\
	__ci_get_io_xx_err_time(_cidev, CI_IO_ERR_TYPE_RD, _idx)
#define ci_get_io_wr_err_time(_cidev, _idx)	\
	__ci_get_io_xx_err_time(_cidev, CI_IO_ERR_TYPE_WR, _idx)


#define ci_nego_buff_size(_cidev)				(_cidev->nego_info.buff_size)
#define ci_nego_step(_cidev)					(_cidev->nego_info.step)

#define ci_bus_speed(_cidev)					(_cidev->bus_speed.speed)
#define ci_bus_param_1(_cidev)					(_cidev->bus_speed.param_1)
#define ci_bus_param_2(_cidev)					(_cidev->bus_speed.param_2)

#define ci_get_delay_param(_cidev, _param)				(_cidev->cfg->delays[_param])

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

enum {
	CI_NEGO_STEP_NONE		= 0,
	CI_NEGO_STEP_START,
	CI_NEGO_STEP_SOFT_RESET,
	CI_NEGO_STEP_GET_BUFF_SIZE,
	CI_NEGO_STEP_FIX_BUFF_SIZE,
	CI_NEGO_STEP_SET_BUFF_SIZE,
	CI_NEGO_STEP_MAX
};

enum {
	CI_IO_ERR_NONE					= 0x00,
	//
	CI_IO_ERR_RD_1ST_CHK_DA			= 0x01,
	CI_IO_ERR_RD_1ST_BYTE			= 0x02,
	CI_IO_ERR_RD_MIDDLE_RE			= 0x03,
	CI_IO_ERR_RD_BURST_PRE_RE		= 0x04,
	CI_IO_ERR_RD_BURST_MIDDLE_RE	= 0x05,
	CI_IO_ERR_RD_LAST_RE			= 0x06,
	//
	CI_IO_ERR_WR_1ST_CHK_DA			= 0x10,
	CI_IO_ERR_WR_1ST_CHK_FR			= 0x11,
	CI_IO_ERR_WR_1ST_BYTE			= 0x12,
	CI_IO_ERR_WR_MIDDLE_WE			= 0x13,
	CI_IO_ERR_WR_BURST_PRE_WE		= 0x14,
	CI_IO_ERR_WR_BURST_MIDDLE_WE	= 0x15,
	CI_IO_ERR_WR_LAST_WE			= 0x16,
};


enum {
	CI_IO_ERR_TYPE_RD				= 0,
	CI_IO_ERR_TYPE_WR,
};

typedef struct
{
	UINT32						speed;
	UINT32						param_1;
	UINT32						param_2;
} CI_BUS_INFO_T;

typedef struct
{
	ktime_t					time[CI_IO_ERR_HIS_MAX_CNT];
	int						code[CI_IO_ERR_HIS_MAX_CNT];
	int						cnt;
} CI_IO_ERR_INFO_T;

typedef struct
{
	UINT8					*buf;
	CI_IO_ERR_INFO_T		rd;
	CI_IO_ERR_INFO_T		wr;
	spinlock_t				lock;
} CI_IO_T;

typedef struct
{
	UINT32						buff_size;
	UINT32						step;
} CI_NEGO_INFO_T;

typedef struct
{
	UINT32			is_flag;
	UINT32			opt_flag;
} CI_FLAG_INFO_T;

typedef struct
{
	s64						r_size;
	s64						w_size;
	ktime_t					r_time;
	ktime_t					w_time;
} CI_DBG_TIME_T;

typedef struct
{
	UINT8						*buf;
	UINT32						buf_size;
	/* */
	CI_DBG_TIME_T			time_test;
	CI_DBG_TIME_T			time_perf;
} CI_DBG_T;


/**
 *	main control block for ci device.
 *	each minor device has unique control block
 *
 */
typedef struct ci_device
{
	/* Command Device */
	int						dev_open_count;		///< check if device is opened or not
	dev_t					devno;				///< device number
	struct cdev				cdev;				///< char device structure

	/* Device Specific Data */
	struct platform_device	*pdev;
	struct device			*parent;

	char					name[CI_MAX_NAME];
	int						idx;
	int						irq;

	UINT32					chip_rev;	//lx_chip_rev()
	UINT32					chip_sub;	//0xA0, 0xB0, 0xC0, ...

	void *					smc_addr;
	void *					reg_addr;
	void *					mod_addr;
	CI_BUS_INFO_T			bus_speed;

	CI_IO_T					io;

	CI_CFG_T				*cfg;

	struct file_operations	*fops;

	struct ci_dev_cis_info	*cis_info;
	CI_NEGO_INFO_T			nego_info;

	struct mutex 			mutex;
	spinlock_t				lock;
	CI_FLAG_INFO_T			cflags;
	CI_DBG_T				debug;

	struct ci_proc			*proc;

	void					*priv;

	struct completion		completion;
	struct mutex			access_mutex;

	UINT8					power_on;
	UINT8					off_count;
	UINT8					on_init;

	unsigned long private[0];// ____cacheline_aligned;

} CI_DEV_T;

typedef struct
{
	char 			*name;
	int				major;
	int				minor;
	int				num;
} ci_chrdev_data_t;


typedef struct
{
	UINT32		is_probe_done		:1,
				is_init_done		:1,
				is_card_detected	:1,
				is_power_restart	:1,
				is_cam_init_done	:1,
				is_cam_cis_done		:1,
				is_cam_cor_done		:1,
				is_cam_nego_done	:1,
				//
				is_pcap_dump_on		:1,
				is_rsvd09			:1,
				is_rsvd0A			:1,
				is_rsvd0B			:1,
				is_rsvd0C			:1,
				is_rsvd0D			:1,
				is_rsvd0E			:1,
				is_suspended		:1,
				//
				_rsvd				:(32-16);
} _ci_is_flags;


typedef struct
{
	UINT32		opt_cd_pol			:1,
				opt_io_mode_on		:1,
				opt_io_mode			:2,
				opt_rsvd04			:1,
				opt_rsvd05			:1,
				opt_rsvd06			:1,
				opt_io_time_show	:1,
				//
				opt_burst_mode		:2,
				opt_rsvd0A			:1,
				opt_rsvd0B			:1,
				opt_rsvd0C			:1,
				opt_rsvd0D			:1,
				opt_rsvd0E			:1,
				opt_os_proc_base	:1,
				//
				_rsvd				:(32-16);
} _ci_opt_flags;

typedef struct
{
	int 		(*probe)(CI_DEV_T *cidev);
	int			(*remove)(CI_DEV_T *cidev);
} ci_platform_driver_t;


/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/

static inline void ci_is_flag_reset_for_cam(CI_DEV_T *cidev)
{
	ci_is_cam_init_done(cidev) = 0;
	ci_is_cam_cis_done(cidev) = 0;
	ci_is_cam_cor_done(cidev) = 0;
	ci_is_cam_nego_done(cidev) = 0;
}

static inline int __ci_get_io_xx_err_cnt(CI_DEV_T *cidev, int type)
{
	return (type == CI_IO_ERR_TYPE_WR)? cidev->io.wr.cnt : cidev->io.rd.cnt;
}

static inline int __ci_get_io_xx_err_code(CI_DEV_T *cidev, int type, int idx)
{
	return (idx >= CI_IO_ERR_HIS_MAX_CNT)? CI_IO_ERR_NONE :	\
			((type == CI_IO_ERR_TYPE_WR)? cidev->io.wr.code[idx] :	\
			cidev->io.rd.code[idx]);
}

static inline void __ci_set_io_xx_err_code(CI_DEV_T *cidev, int type, int code)
{
	CI_IO_ERR_INFO_T *err;

	if (code == CI_IO_ERR_NONE)
		return;

	err = (type == CI_IO_ERR_TYPE_WR)? &cidev->io.wr : &cidev->io.rd;
	ci_io_lock(cidev);
	if (err->cnt < CI_IO_ERR_HIS_MAX_CNT) {
		err->time[err->cnt] = ktime_get();
		err->code[err->cnt] = code;
		err->cnt++;
	}
	ci_io_unlock(cidev);
}

static inline ktime_t __ci_get_io_xx_err_time(CI_DEV_T *cidev, int type, int idx)
{
	return (idx >= CI_IO_ERR_HIS_MAX_CNT)? (ktime_t){ .tv64 = 0 } :	\
		(type == CI_IO_ERR_TYPE_WR)? cidev->io.wr.time[idx] : cidev->io.rd.time[idx];
}

static inline int ci_cal_mbps(s64 size, ktime_t time_t)
{
	volatile s64 _size, _time;

	if (!time_t.tv64) {
		return 0;
	}

	_size = (size * 1000L)<<3L;
	_time = ktime_to_us(time_t);
	do_div(_size, _time);
	return _size;
}

static inline void __ci_dbg_time_reset(CI_DBG_TIME_T *ci_time)
{
	memset((void *)ci_time, 0x00, sizeof(CI_DBG_TIME_T));
}

static inline void __ci_dbg_get_data(CI_DBG_TIME_T *ci_time,
									ktime_t *w_time, s64 *w_size,
									ktime_t *r_time, s64 *r_size)
{
	w_time->tv64 = ci_time->w_time.tv64;
	(*w_size) = ci_time->w_size;

	r_time->tv64 = ci_time->r_time.tv64;
	(*r_size) = ci_time->r_size;
}

static inline void __ci_dbg_time_r_data(CI_DBG_TIME_T *ci_time,
									ktime_t start_t, ktime_t end_t,
									int rsize)
{
	ktime_t _sub, _new, _old;

	_sub = ktime_sub(end_t, start_t);
	_old.tv64 = ci_time->r_time.tv64;
	_new = ktime_add(_old, _sub);
	if (_new.tv64 < _old.tv64) {
		ci_time->r_size = (s64)rsize;
		ci_time->r_time.tv64 = _sub.tv64;
	} else {
		ci_time->r_size += (s64)rsize;
		ci_time->r_time.tv64 = _new.tv64;
	}
}

static inline void __ci_dbg_time_w_data(CI_DBG_TIME_T *ci_time,
									ktime_t start_t, ktime_t end_t,
									int wsize)
{
	ktime_t _sub, _new, _old;

	_sub = ktime_sub(end_t, start_t);
	_old.tv64 = ci_time->w_time.tv64;
	_new = ktime_add(_old, _sub);
	if (_new.tv64 < _old.tv64) {
		ci_time->w_size = (s64)wsize;
		ci_time->w_time.tv64 = _sub.tv64;
	} else {
		ci_time->w_size += (s64)wsize;
		ci_time->w_time.tv64 = _new.tv64;
	}
}

static inline void ci_dbg_test_reset(CI_DEV_T *cidev)
{
	__ci_dbg_time_reset(&cidev->debug.time_test);
}

static inline void ci_dbg_perf_reset(CI_DEV_T *cidev)
{
	__ci_dbg_time_reset(&cidev->debug.time_perf);
}

static inline void ci_dbg_perf_get_data(CI_DEV_T *cidev,
										ktime_t *w_time, s64 *w_size,
										ktime_t *r_time, s64 *r_size)
{
	__ci_dbg_get_data(&cidev->debug.time_perf,
					w_time, w_size, r_time, r_size);
}

static inline void ci_dbg_perf_r_data(CI_DEV_T *cidev,
									ktime_t start_t, ktime_t end_t,
									int rsize)
{
	__ci_dbg_time_r_data(&cidev->debug.time_perf,
						start_t, end_t, rsize);
}

static inline void ci_dbg_perf_w_data(CI_DEV_T *cidev,
									ktime_t start_t, ktime_t end_t,
									int wsize)
{
	__ci_dbg_time_w_data(&cidev->debug.time_perf,
						start_t, end_t, wsize);
}


/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int CI_DEBUG_Uninit(void);
void CI_DEBUG_Init(void);
int CI_DEBUG_SetLog(CI_DEV_T *cidev, UINT32 mask);

void *ci_get_cidev(struct inode *inode);

void ci_uninit_chrdev_region(ci_chrdev_data_t *chrdev_data);
int ci_init_chrdev_region(ci_chrdev_data_t *chrdev_data);

void ci_del_chrdev(CI_DEV_T *ci_devs, ci_chrdev_data_t *chrdev_data);
int ci_add_chrdev(CI_DEV_T *ci_devs, ci_chrdev_data_t *chrdev_data);

int ci_free_irq(CI_DEV_T *cidev);
int ci_release_irq(CI_DEV_T *cidev);
int ci_request_irq(CI_DEV_T *cidev);

void ci_free_devs(CI_DEV_T *ci_devs, ci_chrdev_data_t *chrdev_data);
CI_DEV_T *ci_alloc_devs(ci_chrdev_data_t *chrdev_data);

void ci_uninit_platform(void *pdriver_priv,
							void *pdevices_priv,
							CI_DEV_T *ci_devs,
							ci_chrdev_data_t *chrdev_data);
int ci_init_platform(void *pdriver_priv,
							void *pdevices_priv,
							CI_DEV_T *ci_devs,
							ci_chrdev_data_t *chrdev_data);

void ci_uninit_delay_op(CI_DEV_T *cidev);
int ci_init_delay_op(CI_DEV_T *cidev);

//TODO: Not proper prototype location
CI_DEV_T* CI_GetDevs(void);
int CI_InitMonitor(void);
int CI_StopMonitor(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _CI_DEV_H_ */


