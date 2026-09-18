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
 *  @author	Kyungseok Hyun (ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2015-02-04
 *  @note		Additional information.
 */

#ifndef _LG1K_TE_MCU_H_
#define _LG1K_TE_MCU_H_

#include <lg1k/te/te.h>

#define MCU_MEM_NAME			"te_mcu"

struct te_mcu_rcallback;

enum te_mcu_func_type {		// Arranged by suspend order
	TE_MCU_FUNC_TYPE_ATSC3 = 0,
	TE_MCU_FUNC_TYPE_FILTER,
	TE_MCU_FUNC_TYPE_IO,
	TE_MCU_FUNC_TYPE_CIPLUS,
	TE_MCU_FUNC_TYPE_DEMOD,	/* FOR L18F DEMOD */
	TE_MCU_FUNC_TYPE_DSC,
	TE_MCU_FUNC_TYPE_ARIB2,
	TE_MCU_FUNC_TYPE_MAX,
};

struct te_mcu_rcallback *te_mcu_register_rcallback(struct te_device *dev,
						   enum te_mcu_func_type type,
						   int (*pre_func)(void *),
						   int (*post_func)(void *),
						   void *arg);

int te_mcu_unregister_rcallback(struct te_device *dev,
				struct te_mcu_rcallback *callback);

int te_mcu_fwload(struct te_device *dev, u8 num, const void *data, u32 size);
int te_mcu_stall(struct te_device *dev, u8 num, bool stall);
int te_mcu_get_status(struct te_device *dev, u8 num, bool *mcu_ready,
		      bool *ipc_ready, u32 *vers);

#endif				/* _LG1K_TE_MCU_H_ */
