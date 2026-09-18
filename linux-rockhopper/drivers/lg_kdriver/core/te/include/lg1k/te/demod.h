/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2022 by LG Electronics Inc.
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
 *  TE(Transport Engine) Header for DEMOD extern
 *
 *  @author	Ilkyu Kim(ilkyu.kim@lge.com)
 *  @version	1.0
 *  @date		2022-01-11
 *  @note		Additional information.
 */

#ifndef	_LG1K_TE_DEMOD_H_
#define	_LG1K_TE_DEMOD_H_

#include <linux/types.h>

enum te_mcu_status {
	TE_MCU_STATUS_NOT_READY = 0,
	TE_MCU_STATUS_READY,
	TE_MCU_STATUS_TIMEOUT, // mcu is not responding / reloading status
	TE_MCU_STSTUS_MAX
};

int te_mcu_register_demod_rcallback(int (*pre_func)(void *),
				    int (*post_func)(void *),
				    int (*suspend_func)(void *),
				    int (*resume_func)(void *),
				    void *arg);
bool te_mcu_get_demod_ready(void);
int te_mcu_set_demod_sram_addr(u32 addr, u32 size);
int te_mcu_enable_demod(bool en);
int te_mcu_get_demod_status(enum te_mcu_status *status);

#endif	/* _LG1K_TE_DEMOD_H_ */
