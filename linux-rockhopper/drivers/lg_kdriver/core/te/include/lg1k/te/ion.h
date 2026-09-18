/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2024 by LG Electronics Inc.
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
 *  ION CI SPI Interface for ION hardware
 *
 *  @author	Ilkyu Kim
 *  @version	1.0
 *  @date	2024-05-03
 *  @note	Additional information.
 */

#ifndef _LG1K_TE_ION_H_
#define _LG1K_TE_ION_H_

#include <linux/types.h>

struct te_device;

#ifdef CONFIG_TE_ION
int ion_init_device(struct te_device *dev);
void ion_release_device(struct te_device *dev);

int ion_ci_init(struct te_device *dev);
int ion_ci_smc_write32(struct te_device *dev, u32 val, u32 addr);
int ion_ci_smc_read32(struct te_device *dev, u32 *val, u8 addr);
int ion_ci_cireg_write16(struct te_device *dev, u16 val, u8 addr);
int ion_ci_cireg_read16(struct te_device *dev, u16 *val, u8 addr);
int ion_ci_read_attribute_mem(struct te_device *dev, u8 *val, u16 addr);
int ion_ci_write_attribute_mem(struct te_device *dev, u8 val, u16 addr);
int ion_ci_read_cam_control(struct te_device *dev, u8 *val, u8 addr);
int ion_ci_write_cam_control(struct te_device *dev, u8 val, u8 addr);
int ion_ci_read_io_data(struct te_device *dev, u8 *buf, u32 len);
int ion_ci_write_io_data(struct te_device *dev, u8 *buf, u32 len);
int ion_ci_reset(struct te_device *dev);
int ion_ci_reset_tp(struct te_device *dev);

/* SLT */
int ion_ci_init_tp_checker(struct te_device *dev, u16 pkt_cnt);
int ion_ci_start_tp_checker(struct te_device *dev, u16 pkt_cnt);

int ion_io_hw_init(struct te_device *dev);
int ion_io_hw_suspend(struct te_device *dev);
int ion_io_hw_resume(struct te_device *dev);
int ion_io_write32(struct te_device *dev, u8 ch, u32 val, u32 addr);
int ion_io_read32(struct te_device *dev, u8 ch, u32 *val, u32 addr);
int ion_io_enable_tpi(struct te_device *dev, u8 ext_num, bool en);
int ion_io_set_tp(struct te_device *dev, u8 ext_num, bool parallel);
int ion_io_set_tlv(struct te_device *dev, u8 ext_num, bool parallel);
int ion_io_set_lgc(struct te_device *dev, u8 ext_num, bool parallel);
#else
static inline int ion_init_device(struct te_device *dev)
{
	return -ENODEV;
}
static inline void ion_release_device(struct te_device *dev) { }
static inline int ion_ci_init(struct te_device *dev)
{
	return -ENODEV;
}
static inline int ion_ci_smc_write32(struct te_device *dev, u32 val, u32 addr)
{
	return -ENODEV;
}
static inline int ion_ci_smc_read32(struct te_device *dev, u32 *val, u8 addr)
{
	return -ENODEV;
}
static inline int ion_ci_cireg_write16(struct te_device *dev, u16 val, u8 addr)
{
	return -ENODEV;
}
static inline int ion_ci_cireg_read16(struct te_device *dev, u16 *val, u8 addr)
{
	return -ENODEV;
}
static inline int ion_ci_read_attribute_mem(struct te_device *dev, u8 *val, u16 addr)
{
	return -ENODEV;
}
static inline int ion_ci_write_attribute_mem(struct te_device *dev, u8 val, u16 addr)
{
	return -ENODEV;
}
static inline int ion_ci_read_cam_control(struct te_device *dev, u8 *val, u8 addr)
{
	return -ENODEV;
}
static inline int ion_ci_write_cam_control(struct te_device *dev, u8 val, u8 addr)
{
	return -ENODEV;
}
static inline int ion_ci_read_io_data(struct te_device *dev, u8 *buf, u32 len)
{
	return -ENODEV;
}
static inline int ion_ci_write_io_data(struct te_device *dev, u8 *buf, u32 len)
{
	return -ENODEV;
}
static inline int ion_ci_reset(struct te_device *dev)
{
	return -ENODEV;
}
static inline int ion_ci_reset_tp(struct te_device *dev)
{
	return -ENODEV;
}
/* SLT */
static inline int ion_ci_init_tp_checker(struct te_device *dev, u16 pkt_cnt)
{
	return -ENODEV;
}
static inline int ion_ci_start_tp_checker(struct te_device *dev, u16 pkt_cnt)
{
	return -ENODEV;
}

static inline int ion_io_hw_init(struct te_device *dev)
{
	return -ENODEV;
}
static inline int ion_io_hw_suspend(struct te_device *dev)
{
	return -ENODEV;
}
static inline int ion_io_hw_resume(struct te_device *dev)
{
	return -ENODEV;
}
static inline int ion_io_write32(struct te_device *dev, u32 val, u32 addr)
{
	return -ENODEV;
}
static inline int ion_io_read32(struct te_device *dev, u32 *val, u32 addr)
{
	return -ENODEV;
}
static inline int ion_io_set_tp(struct te_device *dev, u8 ext_num, bool parallel)
{
	return -ENODEV;
}
static inline int ion_io_set_tlv(struct te_device *dev, u8 ext_num, bool parallel)
{
	return -ENODEV;
}
static inline int ion_io_set_lgc(struct te_device *dev, u8 ext_num, bool parallel)
{
	return -ENODEV;
}
#endif		// CONFIG_TE_ION
#endif		// _LG1K_TE_ION_H_
